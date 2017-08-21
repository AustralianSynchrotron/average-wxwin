/***************************************************************************
 *            TDrift.cc
 *
 *  Sun Sep 10 14:48:47 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/
#include "TDrift.h"

BEGIN_EVENT_TABLE(TDrift, wxDialog)
	EVT_BUTTON(ID_START,TDrift::StartClick)
END_EVENT_TABLE();

TDrift::TDrift(PFileArray * newfiles, wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
	{
  TFile * CFile;
  abort_btn = new wxButton(this,wxID_CANCEL);
  info = new wxStaticText(this,wxID_ANY,_("Info"));
  start_btn = new wxButton(this,ID_START,_("Start"));
  info->Wrap(200);    //In case of big file names
  do_layout();
  SetFiles(newfiles);
  lResult = DRIFT_ABORT;

    // Find the first file with a foil 

  lFixed = NULL;

  CFile = (*lFiles)[0];

  while ((CFile != NULL) && (lFixed == NULL))
  {
    if (CFile->Foil() != NULL)

      lFixed = CFile;

    CFile = CFile->Next();
  }

  if (lFixed == NULL)
  {
    wxMessageBox (_("There are no files with valid foil data"));

    CalibrateDone();
  }
  else
  {
    info->SetLabel(wxString::Format (_("%d files will be calibrated relative to "),
                                     lFiles->GetCount()) + lFixed->getName());

    info->SetMinSize(info->GetSize());
	Layout();
	Fit();
	start_btn->Enable(TRUE);
  }
}

void TDrift::do_layout()
{
	wxBoxSizer* sizer_8 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer_8->Add(info, 0, wxALL|wxADJUST_MINSIZE, 5);
	button_sizer->Add(start_btn,0,wxALL|wxADJUST_MINSIZE,5);
	button_sizer->Add(abort_btn,0,wxALL|wxADJUST_MINSIZE,5);
	sizer_8->Add(button_sizer,0);
    SetAutoLayout(true);
    SetSizer(sizer_8);
    sizer_8->Fit(this);
    sizer_8->SetSizeHints(this);
    Layout();
}

void TDrift::SetFiles(PFileArray * newfiles)
{
	lFiles = newfiles;
}

void TDrift::DoCalibrate ()
{
  TFile * CFile = (*lFiles)[0];
  while (CFile != NULL)
  {
    TFile * lCalFile = CFile;
    CFile = CFile->Next();
	info->SetLabel(_("Calibrating ")+ lCalFile->GetName() + _(" relative to ") + lFixed->GetName());
    info->SetMinSize(info->GetSize());
	Layout();Fit();
	lCalFile->ECalibrate (lFixed);
    lCalFile->Update();
  }
  lResult = wxID_OK;
  CalibrateDone();
}

void TDrift::CalibrateDone ()
{
  SetReturnCode(lResult);
  EndModal(lResult);
}



void TDrift::AbortClick (wxCommandEvent &event)
{
    CalibrateDone ();
}


void TDrift::StartClick (wxCommandEvent &event)
{
  start_btn->Enable(FALSE);
  DoCalibrate ();
}
