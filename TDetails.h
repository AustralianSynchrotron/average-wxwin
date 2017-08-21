/***************************************************************************
 *            TDetails.h
 *
 *  Wed Oct  4 18:26:21 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/

#ifndef _TDETAILS_H
#define _TDETAILS_H
#include <wx/wx.h>
#include "tfile.h"
#include "TMono.h"

class TDetails : public wxDialog {
  public:
	TDetails(TFile * target_obj,wxWindow * parent,int id=wxID_ANY, const wxString &title=_(""), 
	     const wxPoint &pos=wxDefaultPosition, const wxSize &size= wxDefaultSize, long int style=wxDEFAULT_FRAME_STYLE);

  private:
    wxStaticText * Mono;
    wxStaticText * Cal;
    wxStaticText * DT;
    wxStaticText * Trans;
    wxStaticText * Fluor;
    wxStaticText * ERange;
    // Separate: TBevel;
    wxStaticText * MonoD;
    wxStaticText * CalD;
    wxStaticText * DTD;
    wxStaticText * TransD;
    wxStaticText * FluorD;
    wxStaticText * ERangeD;
    wxButton * MonoBut;
    wxButton * CalBut;
    wxButton * DTBut;
    wxButton * E0But;
    wxButton * Cancel_But;
    wxButton * Help_But;
    wxButton * OK_But;
    wxStaticText * E0Label;
    wxStaticText * E0D;
    // Buttons:  TPanel;
    // Bevel1:   TBevel;

    void FormShow     ();
	void do_layout();
    void FormCreate   ();
    void MonoDblClick (wxCommandEvent & event);
    void CalDblClick  (wxCommandEvent & event);
    void DTDblClick   (wxCommandEvent & event);
    void CancelClick  (wxCommandEvent & event);
    void E0DblClick   (wxCommandEvent & event);
    void FormPaint    ();

    TFile * lObj;

    double loMono, loDT, loCal, loE0;

  //published
  //  property Obj:  TFile  read lObj  write lObj;
    DECLARE_EVENT_TABLE();
  };

// Defines for buttons
#define MONOBUT 300
#define CALBUT  301
#define DTBUT   302
#define E0BUT   303

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#endif /* _TDETAILS_H */
