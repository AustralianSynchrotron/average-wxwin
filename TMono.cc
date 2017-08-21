/***************************************************************************
 *            TMono.cc
 *
 *  Wed Oct 18 11:57:10 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/
#include "TMono.h"

TMonochromator::TMonochromator(wxString filename, double d_spacing, 
    wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
	D = d_spacing;
	MonoLabel = new wxStaticText(this, -1, wxT("What monochromator crystal was used for "));
        FileLabel = new wxStaticText(this, -1, filename);
    const wxString mono_choices[] = {
		wxT("Si(400):    1.357736A"),
        wxT("Si(220):    1.920128A"),
        wxT("Si(111):    3.135556A"),
		wxT("Si(311):    TBD")
	};
    MonoComboBox = new wxComboBox(this,-1,_(""),wxDefaultPosition,wxDefaultSize,4,mono_choices,wxCB_DROPDOWN);
    OKButton = new wxButton(this,wxID_OK,_(""));
	ForAllButton = new wxButton(this,wxID_ANY,_("Apply to All"));
	do_layout();
	FormCreate();
	}

BEGIN_EVENT_TABLE(TMonochromator,wxDialog)
	EVT_TEXT(-1,TMonochromator::MonoComboBoxChange)
	EVT_BUTTON(FORALLBUT,TMonochromator::ForAllButtonClick)
	EVT_BUTTON(wxID_OK,TMonochromator::OKButtonClick)
END_EVENT_TABLE();

void TMonochromator::do_layout()
	{
	wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* h_sizer_1 = new wxBoxSizer(wxHORIZONTAL); //for question
	wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL); //for buttons
    h_sizer_1->Add(MonoLabel, 0, wxALL|wxADJUST_MINSIZE, 5);
    h_sizer_1->Add(FileLabel, 0, wxALL|wxADJUST_MINSIZE, 5);
    top_sizer->Add(h_sizer_1, 1, wxEXPAND, 0);
	top_sizer->Add(MonoComboBox,1,wxALL|wxADJUST_MINSIZE,5);
	button_sizer->Add(OKButton,1,wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 5);
    button_sizer->Add(ForAllButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 5);
    top_sizer->Add(button_sizer,1,wxEXPAND,0);
	SetAutoLayout(true);
    SetSizer(top_sizer);
    top_sizer->Fit(this);
    top_sizer->SetSizeHints(this);
    Layout();
	}
	
void TMonochromator::MonoComboBoxChange (wxCommandEvent & event)
{
  int E;
  double Scale;
  wxString Text;
  bool OK;

  Text = MonoComboBox->GetValue().AfterLast(':');

  Scale = 1;

  E = Text.Find(_("Å"));

  if (E == 0)

    E = Text.Find (_("pm"));

  if (E == 0)

    E = Text.Find (_("nm"));

  Scale = 1;

  if (E > 0)
  {
    if (Text [E] == 'p')

      Scale = 0.01;

    else

      if (Text [E] == 'n')

        Scale = 10;

    Text = Text.Left (E - 1);
  }

  OK = Text.ToDouble (&D);

  D = D * Scale;

  OKButton->Enable(TRUE);
  ForAllButton->Enable(TRUE);
}

void TMonochromator::FormCreate ()
{
  OKButton->Enable(FALSE);
  ForAllButton->Enable(FALSE);
  All = FALSE;
}

void TMonochromator::ForAllButtonClick (wxCommandEvent & event)
{
  All = TRUE;
  EndModal(wxID_OK);
}

void TMonochromator::OKButtonClick (wxCommandEvent & event)
{
  All = FALSE;
  EndModal(wxID_OK);
}
