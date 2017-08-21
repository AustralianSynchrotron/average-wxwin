/***************************************************************************
 *            TCalibrate::cc
 *
 *  Wed Sep  6 16:10:35 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/
#include "TCalibrate.h"
#include "TCalEnergy.h"
#include "TDrift.h"

BEGIN_EVENT_TABLE(TCalibrate, wxDialog)
	EVT_PAINT(TCalibrate::DrawPaint)
	EVT_CHECKBOX(use_check,TCalibrate::UseDataClick)
	EVT_CHECKBOX(enecal_check,TCalibrate::EneCalClick)
	EVT_BUTTON(wxID_OK,TCalibrate::OKClick)
	EVT_BUTTON(ID_DRIFT,TCalibrate::OverlapClick)
	EVT_BUTTON(ID_CALIB,TCalibrate::CalButClick)
END_EVENT_TABLE();

void PaneEventHandler::RightMouseDown(wxMouseEvent &event)
{
	// printf("Intercepted right mouse down, id is %d\n",event.GetId());
	// Pass the event to the calibrate window 
	right_is_down = TRUE;
	// wxWindow * top_level = wxWindow::FindWindowById(CALIB_TOP);
	// wxPostEvent(top_level,event);
}

void PaneEventHandler::RightMouseUp(wxMouseEvent &event)
{
	// printf("Intercepted right mouse up, id is %d\n",event.GetId());
	right_is_down = FALSE;
	// wxWindow * top_level = wxWindow::FindWindowById(CALIB_TOP);
	// wxPostEvent(top_level,event);
}

void PaneEventHandler::RightMouseMoving(wxMouseEvent &event)
{
	if(right_is_down) {
	    // printf("Top: Mouse moving: now at %ld\n",event.GetX());
	    TCalibrate * top_level = dynamic_cast<TCalibrate *>(wxWindow::FindWindowById(CALIB_TOP));
	    if(top_level)
	    top_level->TrackMouse (event.GetX());
	    else
		    printf("Unable to dynamic cast to TCalibrate *\n");
	}
	event.Skip();
}

BEGIN_EVENT_TABLE(PaneEventHandler,wxEvtHandler)
    EVT_RIGHT_DOWN(PaneEventHandler::RightMouseDown)
    EVT_RIGHT_UP(PaneEventHandler::RightMouseUp)
    EVT_MOTION(PaneEventHandler::RightMouseMoving)
END_EVENT_TABLE();

TCalibrate::TCalibrate(PFileArray * newfiles, wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, 
	     wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
{
    draw_pane = new wxPlotCtrl(this, CALIB_WIN,wxDefaultPosition,wxSize(600,300));
    checkbox_use = new wxCheckBox(this, use_check, wxT("Use Data"));
    checkbox_enecal = new wxCheckBox(this, enecal_check, wxT("Use energy"));
    help_button = new wxButton(this, -1, wxT("Help"));
    ok_button = new wxButton(this, wxID_OK, wxT("OK"));
    cancel_button = new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    drift_button = new wxButton(this,ID_DRIFT,wxT("Drift"));
    calibrate_button = new wxButton(this,ID_CALIB,wxT("Calibrate"));
    statusbar = new wxStatusBar(this, -1);
    FormCreate();
    set_properties();
    do_layout();
    SetFiles(newfiles);   //not earlier as Form_Create nullifies everything
    FormShow();
}


void TCalibrate::set_properties()
{
	wxColourDatabase cdb;
    SetTitle(wxT("Calibrate"));
	statusbar->SetFieldsCount(3);
    int statusbar_widths[] = {-1,-1,-1 };
    statusbar->SetStatusWidths(3, statusbar_widths);
    const wxString statusbar_fields[] = {
        wxT("None"), wxT("None"),wxT("None")
    };
    for(int i = 0; i < statusbar->GetFieldsCount(); ++i) {
        statusbar->SetStatusText(statusbar_fields[i], i);
    }
    draw_pane -> SetBorderColour(*wxLIGHT_GREY);
    draw_pane -> SetGridColour(*wxLIGHT_GREY);
    draw_pane -> SetBackgroundColour(cdb.Find(_("MIDNIGHT BLUE")));
    draw_pane -> SetAxisLabelColour(*wxBLACK);
    draw_pane -> SetAxisColour(*wxBLACK);
    draw_pane -> SetDrawSymbols(FALSE);  //no dots at each point
    checkbox_use->SetToolTip(_("Use foil or data for calibration"));
    checkbox_enecal->SetToolTip(_("Calibration using energy or angular scale"));
}


void TCalibrate::do_layout()
{
    // { wxGlade: TCalibrate::do_layout
    wxBoxSizer* sizer_complete = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_6 = new wxBoxSizer(wxHORIZONTAL);
    sizer_complete->Add(draw_pane, 1, wxEXPAND, 5);
    sizer_complete->SetItemMinSize((wxWindow *)draw_pane,400,300);
    sizer_5->Add(checkbox_use, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_5->Add(checkbox_enecal, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_5->Add(calibrate_button, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_5->Add(drift_button, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_6->Add(help_button, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_6->Add(cancel_button,0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_6->Add(ok_button, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_5->Add(sizer_6, 1, wxEXPAND, 0);
    sizer_complete->Add(sizer_5, 0, wxEXPAND, 0);
    sizer_complete->Add(statusbar,0,wxEXPAND,0);
    SetAutoLayout(true);
    SetSizer(sizer_complete);
    sizer_complete->Fit(this);
    sizer_complete->SetSizeHints(this);
    Layout();
}

void TCalibrate::FormCreate ()
{
  FCalibration=0;

  FButtonDown=FALSE;

  lFiles=NULL;

  lCoData=NULL;

  lD=NULL;

  // Now intercept wxPlotCtrl mouse events
  wxWindow *tt = draw_pane->GetPlotArea();
  PaneEventHandler * tv = new PaneEventHandler();
  tt->PushEventHandler(tv);
}


void TCalibrate::SetFiles (PFileArray * NewFiles)
{

    // Save the file list 

  lFiles=NewFiles;
}


  // Calculate the derivative

bool TCalibrate::getD()
{
  lD=CDerivative (3, lCoData->E, lCoData->Data);

  if (lD != NULL) return(TRUE);
  else return (FALSE);
}


bool TCalibrate::getFoil()
{
  WData ** Data;
  WData * CCData;
  TFile * CFile;
  int C;
  bool OK;

    // Calculate the average foil }

  if (lCoData==NULL)

    lCoData=GData();

  Data = (WData **) malloc ((lFiles->GetCount() + 1) * sizeof (WData *));

  int FoilCt = 0;         //Keep track of foil data

  CFile=(*lFiles)[0];

  for(C=0;C<lFiles->GetCount() && CFile != NULL;C++)
  {
	CFile = (*lFiles)[C];
    CCData=CFile->Foil();

    if ((CCData != NULL) && (CCData->Use != 0))
    {
      Data [FoilCt]=CCData;

      FoilCt++;
    }

  }

  Data [FoilCt]=NULL;

  OK=CData (Data, lCoData) > 0;

  free(Data);

    // Get the limits 

  lD=NULL;

  if (OK)
  {
    lEmin=(*(lCoData->E))(1);
    lEmax=(*(lCoData->E))(lCoData->E->Nrows());

    OK=getD();
  }

  return(OK);
}


void TCalibrate::DrawDraw (int Mode)
{
  double D;
  int C;
  double Emin, Emax, Fmin, Fmax, Dmin, Dmax;
    if (lCoData != NULL)
    {
       
      if (Mode > 1)
      {
		if (draw_pane->GetCurveCount()>0 )
		  draw_pane->DeleteCurve(-1);     //remove old curves
         

          // Get the limits
        Fmin= 1E300;
        Fmax=-1E300;

        Dmin= 1E300;
        Dmax=-1E300;
        for (C=1; C< lCoData->E->Nrows();C++)

          if (((*(lCoData->E))(C) > lEmin) && ((*(lCoData->E))(C) < lEmax))
          {
            if ((*(lD))(C) > Dmax)

              Dmax=(*(lD))(C);

            if ((*(lD))(C) < Dmin)

              Dmin=(*(lD))(C);

            if ((*(lCoData->Data))(C) > Fmax)

              Fmax=(*(lCoData->Data))(C);

            if ((*(lCoData->Data))(C) < Fmin)

              Fmin=(*(lCoData->Data))(C);
          }

        if ((Dmin < 1E300) && (Dmax > -1E300))
        {
          
          std::cout << "Fmax, Dmax " << Fmax << " , " << Dmax << std::endl;
          if(Fmax/Dmax > 1.25)
             {
             std::cout << "Rescaling derivative by " << Fmax/Dmax << std::endl;
          // scale lD data to bring close to averaged data
              (*lD) =  (*lD)* Fmax/Dmax;
             }
	  // We maintain ownership of the data
          curve_data = wxPlotData(lCoData->E->Store(),lD->Store(),
	            lCoData->E->Nrows(),TRUE);
		  curve_data.SetPen(wxPLOTPEN_NORMAL,wxGenericPen(wxGenericColour(0,255,255),2));
          draw_pane->AddCurve(curve_data);
        }

        if ((Fmin < 1E300) && (Fmax > -1E300))
        {
          /* Xmin=Emin;
          Xmax=Emax;

          Ymin=Fmin;
          Ymax=Fmax;

          Border (0.05, 0.1, 0);

          Pen.Color=clYellow; */
          curve_data = wxPlotData(lCoData->E->Store(),
	                        lCoData->Data->Store(),
	                        lCoData->E->Nrows(),TRUE);
	      curve_data.SetPen(wxPLOTPEN_NORMAL,wxGenericPen(wxGenericColour(_("YELLOW")),2));
          curve_data.SetPen(wxPLOTPEN_ACTIVE,wxGenericPen(wxGenericColour(_("YELLOW")),2));

          draw_pane->AddCurve (curve_data);

        }
      }

      if (Mode > 0)          //Draw marker
      {
       /*  Pen.Color=clRed;
        Pen.Mode=pmXor; */
        draw_pane->ClearMarkers();
	    calib_mark.CreateVertLineMarker(FCalibrationPoint,wxGenericPen(wxGenericColour(_("LIME GREEN"))));
 	    draw_pane->AddMarker(calib_mark);
      }
    draw_pane->Redraw(wxPLOTCTRL_REDRAW_PLOT);
    }
}


void TCalibrate::DrawPaint (wxPaintEvent &event)
{
  wxPaintDC(this);
  DrawDraw (2);
}

void TCalibrate::CancelClick (wxCommandEvent &event)
{
  FCalibration=0;
  Close();
}


void TCalibrate::CalButClick (wxCommandEvent &event)
{
  TCalEnergy * CalEnergy = new TCalEnergy((wxWindow *)this,wxID_ANY);
  CalEnergy->Energy=FCalibrationPoint;
  if (FCalibrationActual > 0)

      CalEnergy->Energy=FCalibrationActual;

  if (CalEnergy->ShowModal()==wxID_OK)

    {
      FCalibrationActual=CalEnergy->Energy;

      statusbar->SetStatusText(wxString::Format (_("Actual: %.2f"),
                                         FCalibrationActual),2);

      ok_button->Enable(TRUE);
    }
  CalEnergy->Destroy();
}


void TCalibrate::TrackMouse (long X)
{

      FCalibrationPoint=draw_pane->GetPlotCoordFromClientX(X);

      statusbar->SetStatusText(wxString::Format (_("Calibration: %.2f"),
                                         FCalibrationPoint),1);

      DrawDraw (1);
}

void TCalibrate::OverlapClick (wxCommandEvent &event)
{

    // Compensate for mono drift relative to scan 1 

  drift_button->Enable(FALSE);

  TDrift * drift_dlg = new TDrift(lFiles,this,wxID_ANY);

  drift_dlg->ShowModal();

  drift_button->Enable(TRUE);

  drift_dlg->Destroy();
}

void TCalibrate::FormShow ()
{
  FCalibrationPoint=0;
  FCalibrationActual=0;
  checkbox_enecal->SetValue((*lFiles)[0]->getCaltype()==1);

  checkbox_use->Enable(TRUE);

  setUseData (checkbox_use->IsChecked());

  if (!getFoil())
  {
    setUseData (! checkbox_use->IsChecked());

    checkbox_use->Enable(FALSE);

    checkbox_use->SetValue(!checkbox_use->IsChecked());

    if (!getFoil())

      Close(TRUE);
  }

  FCalibrationPoint=lEmin;
  statusbar->SetStatusText(wxString::Format (_("Calibration: %.2f"),FCalibrationPoint),1);
  statusbar->SetStatusText(wxString::Format(_("Actual: unknown")),2);

  ok_button->Enable(FALSE);
}

void TCalibrate::OKClick (wxCommandEvent &event)
{
int     C;
double mono_d,delta_th;

  // We set the calibration value depending on 
  // whether or not we are calibrating according
  // to energy or angle. 

  FCalibration=FCalibrationActual - FCalibrationPoint;
  if (!(checkbox_enecal -> IsChecked()))    // use angle 
      {
      // Convert the energy shift into an angular offset,
      // using the mono d spacing of each file 
      for(C=0;C<lFiles->GetCount() && (*lFiles)[C] != NULL;C++)
          {
          mono_d = (*lFiles)[C]->getMonoD();    
          if(mono_d > 0) {
              delta_th = asin(12398.42/(2.0*mono_d*FCalibrationActual)) - asin(12398.42/(2.0*mono_d*FCalibrationPoint));
              delta_th = 180.0*M_1_PI*delta_th;
              std::cout << "Converted " << FCalibration << " eV shift to " << delta_th << " degree shift (File # " << C << ")" << std::endl;
              FCalibration = delta_th;
              }
          else {
              std::cout << "Mono d spacing error: got " << mono_d << " , not calibrating" << std::endl;
              FCalibration = 0.0;
              }
          }
      }
  EndModal(wxID_OK);
}

double TCalibrate::Calibration()
{
	return FCalibration;
}

void TCalibrate::setUseData (bool Use)
{
  TFile *CFile;

  CFile=(*lFiles)[0];

  while (CFile != NULL)
  {
    CFile->setlUFoil(!Use);

    CFile=CFile->Next();
  }
}


void TCalibrate::UseDataClick (wxCommandEvent &event)
{
  setUseData (checkbox_use->IsChecked());

  if (!getFoil())
  {
    setUseData (!checkbox_use->IsChecked());

    checkbox_use->Enable(FALSE);

    checkbox_use->SetValue(!checkbox_use->IsChecked());
  }

  DrawDraw(1);
}

void TCalibrate::EneCalClick(wxCommandEvent &event)
{
  TFile * CFile;
  int C;

  CFile=(*lFiles)[0];

  for(C=0;C<lFiles->GetCount() && CFile != NULL;C++)
    {
    if (checkbox_enecal -> IsChecked())    // use energy
        (*lFiles)[C]->setCaltype(1);
    else
        (*lFiles)[C]->setCaltype(0);
    }
}
