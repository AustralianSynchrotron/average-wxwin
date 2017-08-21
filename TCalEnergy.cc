/***************************************************************************
 *            TCalEnergy.cc
 *
 *  Fri Sep  8 16:57:14 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/
#include "TCalEnergy.h"

/* This is the little dialog box that pops up when the user is
ready to calibrate energy */

TCalEnergy::TCalEnergy(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
    Instruction = new wxStaticText(this, -1, wxT("Energy at calibration point"));
    ValueEdit = new wxTextCtrl(this, wxID_ANY, wxT(""));
    ok_button = new wxButton(this, wxID_OK);
	cancel_button = new wxButton(this,wxID_CANCEL);
	do_layout();
}

void TCalEnergy::do_layout()
{
	wxBoxSizer* sizer_8 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer_8->Add(Instruction, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_8->Add(ValueEdit, 0, wxALL|wxADJUST_MINSIZE, 5);
	button_sizer->Add(ok_button,0,wxALL|wxADJUST_MINSIZE,5);
	button_sizer->Add(cancel_button,0,wxALL|wxADJUST_MINSIZE,5);
	sizer_8->Add(button_sizer,0);
    SetAutoLayout(true);
    SetSizer(sizer_8);
    sizer_8->Fit(this);
    sizer_8->SetSizeHints(this);
    Layout();
}

BEGIN_EVENT_TABLE(TCalEnergy,wxDialog)
	EVT_TEXT(wxID_ANY,TCalEnergy::ValueEditChange)
END_EVENT_TABLE();

void TCalEnergy::FormShow ()
{
  ok_button->Enable(FALSE);
  if (Energy != 0)

    ValueEdit->SetValue(wxString::Format (_("%.2f"), Energy));

  else

    ValueEdit->SetValue(_(""));
}

void TCalEnergy::ValueEditChange (wxCommandEvent & event)
{
  bool O =  (ValueEdit->GetValue().ToDouble(&Energy));
  ok_button->Enable(O);
}
