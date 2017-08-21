

#include "TConstants.h"
/* A comment */
// Another comment
TConstants::TConstants(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
    // begin wxGlade: Constants::Constants
    label_3 = new wxStaticText(this, -1, wxT("Atom name"));
    const wxString combo_box_1_choices[] = {
        wxT("Hydrogen"),
        wxT("Helium"),
        wxT("Lithium"),
        wxT("Beryllium"),
        wxT("Boron"),
        wxT("Carbon"),
        wxT("Nitrogen"),
        wxT("Oxygen"),
        wxT("Fluorine"),
        wxT("Neon"),
        wxT("Sodium"),
        wxT("Magnesium"),
        wxT("Aluminium"),
        wxT("Silicon"),
        wxT("Phosphorus"),
        wxT("Sulfur"),
        wxT("Chlorine"),
        wxT("Argon"),
        wxT("Potassium"),
        wxT("Calcium"),
        wxT("Scandium"),
        wxT("Titanium"),
        wxT("Vanadium"),
        wxT("Chromium"),
        wxT("Manganese"),
        wxT("Iron"),
        wxT("Cobalt"),
        wxT("Nickel"),
        wxT("Copper"),
        wxT("Zinc"),
        wxT("Gallium"),
        wxT("Germanium"),
        wxT("Arsenic"),
        wxT("Selenium"),
        wxT("Bromine"),
        wxT("Krypton"),
        wxT("Rubidium"),
        wxT("Strontium"),
        wxT("Yttrium"),
        wxT("Zirconium"),
        wxT("Niobium"),
        wxT("Molybdenum"),
        wxT("Technetium"),
        wxT("Ruthenium"),
        wxT("Rhodium"),
        wxT("Palladium"),
        wxT("Silver"),
        wxT("Cadmium"),
        wxT("Indium"),
        wxT("Tin"),
        wxT("Antimony"),
        wxT("Tellurium"),
        wxT("Iodine"),
        wxT("Xenon"),
        wxT("Caesium"),
        wxT("Barium"),
        wxT("Lanthanum"),
        wxT("Cerium"),
        wxT("Praesodymium"),
        wxT("Neodimium"),
        wxT("Promethium"),
        wxT("Samarium"),
        wxT("Europium"),
        wxT("Gadolinium"),
        wxT("Terbium"),
        wxT("Dysprosium"),
        wxT("Holmium"),
        wxT("Erbium"),
        wxT("Thulium"),
        wxT("Ytterbium"),
        wxT("Lutetium"),
        wxT("Hafnium"),
        wxT("Tantalum"),
        wxT("Tungsten"),
        wxT("Rhenium"),
        wxT("Osmium"),
        wxT("Iridium"),
        wxT("Platinum"),
        wxT("Gold"),
        wxT("Mercury"),
        wxT("Thallium"),
        wxT("Lead"),
        wxT("Bismuth"),
        wxT("Polonium"),
        wxT("Astatine"),
        wxT("Radon"),
        wxT("Francium"),
        wxT("Radium"),
        wxT("Actinium"),
        wxT("Thorium"),
        wxT("Protactinium"),
        wxT("Uranium"),
        wxT("Neptunium"),
        wxT("Plutonium"),
        wxT("Americium"),
        wxT("Curium"),
        wxT("Berkelium"),
        wxT("Californium"),
        wxT("Einsteinium"),
        wxT("Fermium"),
        wxT("Mendelevium"),
        wxT("Nobelium"),
        wxT("Lawrencium"),
        wxT("Rutherfordium"),
        wxT("Unnilquadium"),
        wxT("Hahnium"),
        wxT("Unnilpentium"),
        wxT("Unnilhexium")
    };
    AtomEdit = new wxComboBox(this, CONST_ATOM, wxT(""), wxDefaultPosition, wxDefaultSize, 105, combo_box_1_choices, wxCB_DROPDOWN);
    label_4 = new wxStaticText(this, -1, wxT("Edge Type"));
    const wxString combo_box_2_choices[] = {
        wxT("K"),
        wxT("L1"),
        wxT("L2"),
        wxT("L3"),
        wxT("M1"),
        wxT("M2"),
        wxT("M3"),
        wxT("M4"),
        wxT("M5")
    };
    EdgeEdit = new wxComboBox(this, CONST_EDGE, wxT(""), wxDefaultPosition, wxDefaultSize, 9, combo_box_2_choices, wxCB_DROPDOWN);
    label_5 = new wxStaticText(this, -1, wxT("E0 energy"));
    E0Edit = new wxTextCtrl(this, CONST_E0, wxT(""));
    ok_button = new wxButton(this, wxID_OK);

    set_properties();
    do_layout();
    // end wxGlade
}

BEGIN_EVENT_TABLE(TConstants,wxDialog)
	EVT_TEXT(CONST_ATOM,TConstants::AtomEditChange)
	EVT_TEXT(CONST_EDGE,TConstants::EdgeEditChange)
	EVT_TEXT(CONST_E0,TConstants::E0EditChange)
END_EVENT_TABLE();

void TConstants::set_properties()
{
    // begin wxGlade: Constants::set_properties
    SetTitle(wxT("Select E0"));
    AtomEdit->SetSelection(-1);
    EdgeEdit->SetSelection(-1);
    // end wxGlade
}


void TConstants::do_layout()
{
    // begin wxGlade: Constants::do_layout
    wxBoxSizer* sizer_8 = new wxBoxSizer(wxVERTICAL);
    wxGridSizer* grid_sizer_1 = new wxGridSizer(3, 2, 0, 0);
    grid_sizer_1->Add(label_3, 0, wxALL|wxADJUST_MINSIZE, 5);
    grid_sizer_1->Add(AtomEdit, 0, wxALL|wxADJUST_MINSIZE, 5);
    grid_sizer_1->Add(label_4, 0, wxALL|wxADJUST_MINSIZE, 5);
    grid_sizer_1->Add(EdgeEdit, 0, wxALL|wxADJUST_MINSIZE, 5);
    grid_sizer_1->Add(label_5, 0, wxALL|wxADJUST_MINSIZE, 5);
    grid_sizer_1->Add(E0Edit, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_8->Add(grid_sizer_1, 1, wxEXPAND, 0);
    sizer_8->Add(ok_button, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 5);
    SetAutoLayout(true);
    SetSizer(sizer_8);
    sizer_8->Fit(this);
    sizer_8->SetSizeHints(this);
    Layout();
    // end wxGlade
}

void TConstants::SetOK (bool ChangeE0)
{
  double CE0 = GetE0 ((const char*) Atom.mb_str(),
	                  (const char*) Edge.mb_str());

  VicOK = (Success() > 3);

  if (ChangeE0 && (CE0 > 0))
  {
    E0 = CE0;

    E0Edit->SetValue(wxString::Format (_("%.2f"), E0));
  }

  ok_button->Enable ((E0 > 0) && (CE0 >= 0) && 
                (E0 >= Emin) && (E0 <= Emax));
}


void TConstants::E0EditChange (wxCommandEvent & event)
{
  wxString raw_data = E0Edit->GetValue();
  bool OK = raw_data.ToDouble(&E0);
  SetOK (FALSE);
}


void TConstants::FormShow ()
{
  AtomEdit->SetValue(Atom);
  EdgeEdit->SetValue(Edge);

  E0Edit->SetValue(wxString::Format(_("%.2f"), E0));

  SetOK (E0 <= 0);
}

void TConstants::AtomEditChange (wxCommandEvent & event)
{
  gl_Atom = Atom = AtomEdit->GetValue();
  
  SetOK (TRUE);
}


void TConstants::EdgeEditChange (wxCommandEvent & event)
{
  gl_Edge = Edge = EdgeEdit->GetValue();
  SetOK (TRUE);
}
