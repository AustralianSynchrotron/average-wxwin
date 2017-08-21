#ifndef _TFILE_H
#define _TFILE_H

#include <wx/wx.h>
#include <wx/filename.h>
#include <iostream>
#include "tlight.h"
#include "avelib.h"
#include "cvector.h"
#include "TInspect.h"
#include "TDetails.h"

// Definitions for the TFile type, which is derived from wxPanel
// and stores all the data for each file
	
class TFile: public wxPanel {
    private:

      // Status lights 

    TLight * SDLight;
    TLight * FDLight;
    TLights * FFLight;

	// File name label
	wxStaticText * Caption;
	wxButton * info_button;
	
      // Current values

    void * lOP; 
    wxFileName lFileName;
    double lMonoD,lDT,lE0,lEmin,lEmax,lOrder;

    Columnvector * lE;
    double lCalibration;
    int    lCaltype;              //0=angle, other=energy

    int lChannels;
    WData ** lData;               //array of per-channel data
    WData * lCoData;
    WData * lFoil;

    bool lUF,lUFoil,lGrey;
    TFile *lNext, *lPrev;          //Linked list


      // Private methods

    void Clear();

    

    void lightDblClick (wxMouseEvent &event);

  public:

    TFile(wxWindow * parent = (wxWindow *)0);
    TFile(const TFile&);    //copy
    ~TFile();

    void   Read (const char * FileName);
    void   Update();
    int    Transmission();
    int    Fluorescence();
    wxString  getName();
    WData  * Channel (bool UF, int CN);
    WData  * CoData (bool UF);
    WData  * OCoData ();
    WData  * Foil();
    WData  * OFoil();
    int    Channels (bool UF);
    void   ECalibrate (TFile *Fixed);
    void   ULight (bool UF, int CN);
    bool   ChannelUse (bool UF, int CN, bool Use);
    void   ChannelW (bool UF, int CN, double W);
    void PanelDblClick (wxCommandEvent &event);
    void setlUF (bool Use);
    void setlGrey (bool Grey);
    void setlUFoil (bool Use);
    void setlMonoD (double D);
    void setlDT (double D);
    void setlE0 (double D);
    void setlOrder (double D);
    void setlCalibration (double D);
    void setCaltype (int caltype);
    int  getCaltype ();
    void getE();
    bool getUFoil();
    bool   OK();
    void   Append (TFile * AFile);
    TFile *  First();
    TFile *  Last();
    TFile *  Next();
    TFile *  Prev();
    int      Files();
    // property E:               CVector  read  lE;

    // property FullName:        string   read  lFileName;
    // property Name:            string   read  getName;
    // {moved this to the public area, as we cant publish a
    // pointer value
    // property E:               CVector  read  lE; }
	double getMonoD();
    // property MonoD:           Double   read  lMonoD
//                                       write setlMonoD;
    // property Calibration:     Double   read  lCalibration
	double getlCalibration();
  //                                     write setlCalibration;
    // property DT:              Double   read  lDT
    //   
    double getDT();
    double E0 ();
      //                                 write setlE0;
    // property UFoil:           Boolean  read  lUFoil
        //                               write setlUFoil;
     bool UF();
          //                             write setlUF;
    // property GS:              Boolean  read  lGrey
          //                             write setlGrey;
    // property Emin:            Double   read  lEmin;
	double Emin();            
    double Emax();           // Double   read  lEmax;
    // property Order:           Double   read  lOrder
            //                           write setlOrder;
	DECLARE_EVENT_TABLE()
};

#define TFILE_PANEL 334

// This was originally in separate file UFiles.pas

WX_DEFINE_ARRAY(TFile *,PFileArray);

#endif /* _TFILE_H */
