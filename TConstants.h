
#ifndef TCONSTANTS_H
#define TCONSTANTS_H
#include <wx/wx.h>
#include <wx/image.h>
#include "avelib.h"

// begin wxGlade: ::dependencies
// end wxGlade

extern wxString gl_Atom;   //defined in FileDetails.cpp
extern wxString gl_Edge;

class TConstants: public wxDialog {
public:
    // begin wxGlade: Constants::ids
    // end wxGlade

    TConstants(wxWindow* parent, int id, const wxString& title=_(""), const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);
    void FormShow       (void);
    void FormCreate     (void);
    void E0EditChange   (wxCommandEvent & event);
    void AtomEditChange (wxCommandEvent & event);
    void EdgeEditChange (wxCommandEvent & event);

  private:
    void SetOK (bool ChangeE0);

  public:
    double E0;
    wxString Atom;
    wxString Edge;
    double Emin, Emax;
    bool VicOK;

private:
    // begin wxGlade: Constants::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: Constants::attributes
    wxStaticText* label_3;
    wxComboBox* AtomEdit;
    wxStaticText* label_4;
    wxComboBox* EdgeEdit;
    wxStaticText* label_5;
    wxTextCtrl* E0Edit;
    wxButton* ok_button;
    // end wxGlade
    DECLARE_EVENT_TABLE()
}; // wxGlade: end class

#define CONST_OK 1
#define CONST_NOT_OK 0

#define CONST_ATOM 400
#define CONST_EDGE 401
#define CONST_E0   402
#endif
