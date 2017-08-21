/***************************************************************************
 *            TDrift.h
 *
 *  Sun Sep 10 14:48:35 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/

#ifndef _TDRIFT_H
#define _TDRIFT_H

#include <wx/wx.h>
#include "tfile.h"

class TDrift: public wxDialog
{
	private: 
    wxButton * abort_btn;
    wxStaticText * info;
    wxButton * start_btn;
	void do_layout();
	int lResult;        //Modal dialog result

    void AbortClick (wxCommandEvent &event);
    void StartClick (wxCommandEvent &event);

    PFileArray * lFiles;
    TFile * lFixed;

    void CalibrateDone ();
	void DoCalibrate();

  public:
    TDrift(PFileArray * filelist, wxWindow* parent, int id, const wxString& title=_(""), const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);
    void SetFiles (PFileArray * NewFiles);
  DECLARE_EVENT_TABLE()
};

#define DRIFT_ABORT 333
#define ID_START 334

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#endif /* _TDRIFT_H */
