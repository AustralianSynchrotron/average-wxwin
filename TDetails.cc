/***************************************************************************
 *            TDetails.cc
 *
 *  Wed Oct  4 18:25:41 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/
#include "TDetails.h"

BEGIN_EVENT_TABLE(TDetails, wxDialog)
	EVT_BUTTON(MONOBUT,TDetails::MonoDblClick)
	EVT_BUTTON(CALBUT,TDetails::CalDblClick)
	EVT_BUTTON(DTBUT,TDetails::DTDblClick)
//	EVT_BUTTON(E0BUT,TDetails::E0DblClick)
END_EVENT_TABLE();

TDetails::TDetails(TFile * target_obj, wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, 
	     wxDEFAULT_DIALOG_STYLE)
	{
	lObj = target_obj;        //set this to get any action
	Mono = new wxStaticText(this,wxID_ANY,_("Mono d-spacing"));
	Cal = new wxStaticText(this,wxID_ANY,_("Calibration"));
	DT = new wxStaticText(this,wxID_ANY,_("Deadtime"));
        E0Label = new wxStaticText(this,wxID_ANY,_("E0"));
	Trans = new wxStaticText(this,wxID_ANY,_("Transmission channels"));
	Fluor = new wxStaticText(this,wxID_ANY,_("Fluorescence channels"));
	ERange = new wxStaticText(this,wxID_ANY,_("Energy range"));
	MonoD = new wxStaticText(this,wxID_ANY,_("0.0"));
	CalD = new wxStaticText(this,wxID_ANY,_("0.0"));
	E0D = new wxStaticText(this,wxID_ANY,_("0.0"));
	DTD = new wxStaticText(this,wxID_ANY,_("0.0"));
	TransD = new wxStaticText(this,wxID_ANY,_("0"));
	FluorD = new wxStaticText(this,wxID_ANY,_("0"));
	ERangeD = new wxStaticText(this,wxID_ANY,_("0"));
	MonoBut = new wxButton(this,MONOBUT,_("Change"));
	CalBut = new wxButton(this,CALBUT,_("Change"));
	E0But = new wxButton(this,E0BUT,_("Change"));
	DTBut = new wxButton(this,DTBUT,_("Change"));
        Cancel_But = new wxButton(this,wxID_CANCEL);
        OK_But = new wxButton(this,wxID_OK);
	FormPaint();   // fill in the values
	do_layout();
	FormShow();
	}
	
void TDetails::do_layout()
	{
		wxBoxSizer * top_sizer = new wxBoxSizer(wxVERTICAL);
		wxGridSizer * info_sizer = new wxGridSizer(8,3,3,3);
		info_sizer->Add(Mono,1,wxALL|wxEXPAND,5);
		info_sizer->Add(MonoD,1,wxALL|wxEXPAND,5);
		info_sizer->Add(MonoBut,0,wxALL|wxEXPAND,5);
		info_sizer->Add(Cal,1,wxALL|wxEXPAND,5);
		info_sizer->Add(CalD,1,wxALL|wxEXPAND,5);
		info_sizer->Add(CalBut,0,wxALL|wxEXPAND,5);
		info_sizer->Add(E0Label,1,wxALL|wxEXPAND,5);
		info_sizer->Add(E0D,1,wxALL|wxEXPAND,5);
		info_sizer->Add(E0But,0,wxALL|wxEXPAND,5);
		info_sizer->Add(DT,1,wxALL|wxEXPAND,5);
		info_sizer->Add(DTD,1,wxALL|wxEXPAND,5);
		info_sizer->Add(DTBut,0,wxALL|wxEXPAND,5);
		info_sizer->Add(Trans,1,wxALL|wxEXPAND,5);
		info_sizer->Add(TransD,1,wxALL|wxEXPAND,5);
		info_sizer->Add(1,1,1);
		info_sizer->Add(Fluor,1,wxALL|wxEXPAND,5);
		info_sizer->Add(FluorD,1,wxALL|wxEXPAND,5);
		info_sizer->Add(1,1,1);
		info_sizer->Add(ERange,1,wxALL|wxEXPAND,5);
		info_sizer->Add(ERangeD,1,wxALL|wxEXPAND,5);
		info_sizer->Add(1,1,1);
		wxBoxSizer * button_sizer = new wxBoxSizer(wxHORIZONTAL);
		button_sizer->Add(Cancel_But,1,wxALL|wxEXPAND,5);
		button_sizer->Add(OK_But,1,wxALL|wxEXPAND,5);
		//put them all together
		top_sizer->Add(info_sizer);
		top_sizer->Add(button_sizer);
		SetAutoLayout(true);
        SetSizer(top_sizer);
        top_sizer->Fit(this);
        top_sizer->SetSizeHints(this);
        Layout();
	}
	
void TDetails::FormShow ()
{
  if (lObj == NULL) 

    Destroy();

  else          //store original values in case of cancel button click
  {
    loMono = lObj->getMonoD();
    loDT   = lObj->getDT();
    loCal  = lObj->getlCalibration();
    loE0   = lObj->E0();
  }
}

void TDetails::MonoDblClick (wxCommandEvent &event)
{

    // Run the mono spacing dialog
  TMonochromator * md;
  md = new TMonochromator(lObj->getName(),lObj->getMonoD(),this);

  if (md->ShowModal() == wxID_OK) 
  {
    lObj->setlMonoD(md->D);
    FormPaint ();
  }
  md->Destroy();
}


void TDetails::CalDblClick (wxCommandEvent &event)
{
  double calval;
  wxString message = _("Enter the calibration correction for ") + lObj->getName() + _(" in ");
  if(lObj->getCaltype()==0)
      message += _("deg");
  else
      message += _("eV");
  wxString retval = wxGetTextFromUser(message, _("Calibration"),wxString::Format(_("%8.5f"),lObj->getlCalibration()));

  if (retval.ToDouble(&calval)) 
  {
    lObj->setlCalibration(calval);
    FormPaint ();
  }
}


void TDetails::DTDblClick (wxCommandEvent &event)
{
  double new_dt;
  wxString message = _("Enter the detector dead time in µs for ") + lObj->getName();
  wxString retval = wxGetTextFromUser(message,_("Deadtime"),
	             wxString::Format(_("%8.3f"),lObj->getDT()/1E-6));

  if (retval.ToDouble(&new_dt)) 
  {
    TFile * CFile = lObj->First();

    while (CFile !=NULL)
    {
      CFile->setlDT(new_dt * 1E-6);

      CFile = CFile->Next();
    }

    FormPaint ();
  }
}


void TDetails::CancelClick (wxCommandEvent &event)
{

  TFile * CFile;
    //Reset the parameters

  if (lObj->getMonoD() != loMono) 

    lObj->setlMonoD(loMono);

  if (loDT != lObj->getDT()) 
  {

    CFile = lObj->First();

    while (CFile !=NULL)
    {
      CFile->setlDT(loDT);

      CFile = CFile->Next();
    }
  }

  if (lObj->getlCalibration() != loCal) 

    lObj->setlCalibration(loCal);

  if (lObj->E0() != loE0) 
  {

    CFile = lObj->First();

    while (CFile !=NULL)
    {
      CFile->setlE0(loE0);

      CFile = CFile->Next();
    }
  }
}


void TDetails::E0DblClick (wxCommandEvent &event)
{

  TFile * CFile;
  TConstants * const_dialog;

  const_dialog = new TConstants((wxWindow *) NULL,-1);
  const_dialog->Emin= 0;
  const_dialog->Emax= 1E6;

  if (const_dialog->ShowModal() == wxID_OK) 
  {
    CFile = lObj->First();

    while (CFile !=NULL)
    {
      CFile->setlE0(const_dialog->E0);

      CFile = CFile->Next();
    }

    FormPaint ();
  }
  const_dialog->Destroy();
}


void TDetails::FormPaint ()
{
  SetTitle(lObj->getName());

    // Copy the data to the labels
	
  wxString calformat;        // ev or deg depending on type of calibration
  MonoD->SetLabel  (wxString::Format (_("%.6fÅ"),       lObj->getMonoD()));
  if(lObj->getCaltype()==0)
      calformat = _("%.5f deg");
  else
      calformat = _("%.3f eV");
  CalD->SetLabel   (wxString::Format (calformat,       lObj->getlCalibration()));
  TransD->SetLabel (wxString::Format (_("%d"),          lObj->Transmission()));
  FluorD->SetLabel (wxString::Format (_("%d"),          lObj->Fluorescence()));
  ERangeD->SetLabel(wxString::Format (_("%.1f-%.1feV"), lObj->Emin(), lObj->Emax()));
  E0D->SetLabel    (wxString::Format (_("%.1feV"),      lObj->E0()));

  if (lObj->getDT() > 1E-6) 

    DTD->SetLabel  (wxString::Format (_("%.2fµs"), lObj->getDT() * 1E6));

  else

    DTD->SetLabel  (wxString::Format (_("%.2fns"), lObj->getDT() * 1E9));
}
