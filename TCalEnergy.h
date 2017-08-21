/***************************************************************************
 *            TCalEnergy.h
 *
 *  Fri Sep  8 16:57:01 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/

#ifndef _TCALENERGY_H
#define _TCALENERGY_H

#include <wx/wx.h>

class TCalEnergy: public wxDialog {

private:
    wxStaticText * Instruction;
    wxTextCtrl * ValueEdit;
    wxButton *ok_button;
    wxButton *cancel_button;
    void FormShow();
    void ValueEditChange(wxCommandEvent &event);
    void do_layout();

  public:
    TCalEnergy(wxWindow* parent, int id, const wxString& title=_(""), const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);
    double Energy;
    DECLARE_EVENT_TABLE()
  };


#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#endif /* _TCALENERGY_H */
