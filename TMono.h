/***************************************************************************
 *            TMono.h
 *
 *  Wed Oct 18 11:56:56 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/

#ifndef _TMONO_H
#define _TMONO_H
#include <wx/wx.h>

  class TMonochromator : public wxDialog
  {
  public:
	wxString FName;
    double D;
    bool All;
    TMonochromator(wxString filename, double d_spacing, 
      wxWindow* parent, int id=wxID_ANY, const wxString& title=_(""), 
      const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, 
      long style=wxDEFAULT_FRAME_STYLE);
  private:
	wxButton *ForAllButton;
    wxComboBox *MonoComboBox;
    wxStaticText * MonoLabel;
    wxStaticText * FileLabel;
    wxButton * OKButton;

    void OKButtonClick      (wxCommandEvent &event);
    void MonoComboBoxChange (wxCommandEvent &event);
    void FormCreate         ();
    void ForAllButtonClick  (wxCommandEvent &event);
    void do_layout          ();

  DECLARE_EVENT_TABLE();
  };

#define FORALLBUT  300
  
#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#endif /* _TMONO_H */
