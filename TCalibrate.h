/***************************************************************************
 *            TCalibrate.h
 *
 *  Wed Sep  6 16:10:21 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/

#ifndef _TCALIBRATE_H
#define _TCALIBRATE_H

#include <wx/wx.h>
#include <wx/plotctrl/plotctrl.h>
#include "tfile.h"

#define CALIB_TOP 345
#define use_check 346
#define enecal_check 347

class TCalibrate: public wxDialog {
public:
    TCalibrate(PFileArray * newfiles, wxWindow* parent, int id=CALIB_TOP, const wxString& title=_(""), const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);
    void FormCreate    ();
    void DrawPaint     (wxPaintEvent &event);
    void CancelClick   (wxCommandEvent &event);
    void OverlapClick  (wxCommandEvent &event);
    void FormShow      ();
    void OKClick       (wxCommandEvent &event);
    void DrawDraw      (int mode);
    void TrackMouse    (long X);
    void UseDataClick  (wxCommandEvent &event);
    void EneCalClick  (wxCommandEvent &event);
    void CalButClick(wxCommandEvent &event);
    double Calibration ();
    void SetFiles (PFileArray * NewFiles);

private:
    WData * lCoData;
    double lEmin, lEmax;
    Columnvector * lD;
    double FCalibration;
    double FCalibrationPoint, FOldCalibrationPoint;
    double FCalibrationActual;
    bool FButtonDown;
    PFileArray * lFiles;
    bool getFoil();
    bool getD();
    void setUseData (bool Use);
    void set_properties();
    void do_layout();
    void do_initialise();

protected:
    wxPlotCtrl * draw_pane;
    wxPlotData curve_data;
    wxPlotData deriv_data;
    wxPlotMarker calib_mark;
    wxPlotMarker old_mark;
    wxCheckBox * checkbox_use;
    wxCheckBox * checkbox_enecal;
    wxButton * help_button;
    wxButton * ok_button;
    wxButton * cancel_button;
    wxButton * drift_button;
    wxButton * calibrate_button;
    wxStatusBar * statusbar;
    DECLARE_EVENT_TABLE()
};

enum {ID_DRIFT=200,
      ID_CALIB,
	  CALIB_WIN
     };

/*  We intercept mouse events to the drawing pane in order to avoid having
	 to subclass. */
	 
class PaneEventHandler: public wxEvtHandler 
{
	public:
	    PaneEventHandler() {right_is_down=FALSE;}
		void RightMouseDown(wxMouseEvent &event);
		void RightMouseUp(wxMouseEvent &event);
		void RightMouseMoving(wxMouseEvent &event);
	private:
	    bool right_is_down;
    DECLARE_EVENT_TABLE()
};
	
#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#endif /* _TCALIBRATE_H */
