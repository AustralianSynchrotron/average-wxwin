/***************************************************************************
 *            tfile.cc
 *
 *  Wed Aug  2 13:22:27 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/
#include "tfile.h"

bool TFile::OK()
{
  if (lOP == 0) return(FALSE);
	  else
    return(((Fluorescence() > 0) || (Transmission() > 0)) && (lE != 0));
  }


void TFile::Append (TFile * AFile)
{
  TFile * LFile;
  LFile = Last();
  if (LFile != 0)
  {
    LFile->lNext = AFile;
    AFile->lPrev = LFile;
    AFile->lNext = 0;
  }
}


TFile *TFile::First()
{
  TFile * CFile;
  CFile = this;
  while (CFile->lPrev != 0)
  {
    CFile = CFile->lPrev;
  }
  return(CFile);
}


TFile *TFile::Last()
{
  TFile *CFile;
  CFile = this;
  while (CFile->lNext != 0)
    CFile = CFile->lNext;
  return(CFile);
}


TFile * TFile::Next()
{
  return(lNext);
}


TFile *TFile::Prev()
{
  return(lPrev);
}


int TFile::Files()
{
  TFile *CFile;
  int Count;
  CFile = First();
  Count = 0;
  while (CFile)
  {
    Count++;
    CFile = CFile->lNext;
  }
  return (Count);
}


  // Set the light colour

void TFile::ULight (bool UF, int CN)
{
  TLight *Light;
  wxColour Col;
  double W;
  bool Use, OK;
  int WE;
  WData * cData;
  wxColour ColC[] = {*wxWHITE,
                                   *wxWHITE,
                                   wxColour(0,0,1),
                                   wxColour(0,1,1),
                                   wxColour(0,1,0),
                                   wxColour(1,1,0),
                                   wxColour(1,0,0),
                                   wxColour(1,0,1),
                                   wxColour(1,1,1),
                                   wxColour(1,1,1)};


    // Get Parameters

  cData = Channel (UF, CN);

  OK    = FALSE;
  Use   = FALSE;

  if (cData)
  {
    OK = TRUE;
    Use = (cData->Use != 0);
    W = (cData->Weight);
  }
  std::cout << "ULight: Chan " << CN << " OK= " << OK;
  std::cout << "Use = " << Use << " W = " << W << std::endl;

  /* The colour depends on W and Use:

        Use == False: Black

        W < -1: Black
        W ==  0: Red
        W ==  1: Green
        W ==  2: Blue
        W >  3: White
*/
  Col = wxColour(*wxWHITE);
  if (Use)
    if (lGrey)
    {
      if (W >= 2)
        Col = wxColour(*wxBLACK);
      else
      if (W > 0) {
		int gradation = (int) (sqrt(W/2.0)*255.0);
        Col = wxColour (gradation, gradation, gradation);
	  }
    }
    else   // calculate gradations between the various colours
    {
      W = W * 2 + 3;

      if (W < 1) W = 1;

      if (W > 9) W = 9;

      WE = (int) trunc (W);  //integer colour; 

      W = W - WE;      //remainder
      int fact1 = (int) (255 * (1-W));
	  int fact2 = (int) (254 * W);
	  int nblue = (int) (fact1 * ColC[WE].Blue() + fact2 * ColC[WE+1].Blue());
      int nred = (int) (fact1 * ColC[WE].Red() + fact2 * ColC[WE+1].Red());
	  int ngreen = (int) (fact1 * ColC[WE].Green() + fact2 * ColC[WE+1].Green());
	  Col = wxColour(nred,ngreen,nblue);
    }

  Light = 0;

  if (UF)

    Light = FFLight->Light (CN);

  else

    if (CN == 0)

      Light = SDLight;

    else

      if (CN == 1)

        Light = FDLight;

  if (Light != 0)
  {
    Light->ChangeColour(Col);
    Light->ChangeValid(OK);
  }
}


bool TFile::ChannelUse (bool UF, int CN, bool Use)
{
  WData * cData;
  int oUse;
  bool Changed;
  cData = Channel (UF, CN);
  Changed = FALSE;
  if (cData != 0)
  {
    oUse = cData->Use;
    if (Use)
      cData->Use = 1;
    else
      cData->Use = 0;
    Changed = (oUse != cData->Use);
    ULight (UF, CN);
  }
  return(Changed);
}


void TFile::ChannelW (bool UF, int CN, double W)
{
  WData * cData;
  // std::cout << "Weighting channel " << CN << " with " << W << std::endl;
  cData = Channel (UF, CN);
  if (cData != 0)
  {
    cData->Weight = W;
    // std::cout << "Correcting channel " << CN << " to " << W << std::endl;
    ULight (UF, CN);
  }
}

BEGIN_EVENT_TABLE(TFile,wxPanel)
  EVT_LEFT_UP    (TFile::lightDblClick)
  EVT_LEFT_DCLICK(TFile::lightDblClick)
  EVT_BUTTON     (wxID_PROPERTIES,TFile::PanelDblClick)
END_EVENT_TABLE()

void TFile::lightDblClick (wxMouseEvent &event)
{
  printf("Got a click!\n");
  TInspect * myInspect = new TInspect(this,-1,_(""));
  myInspect->setObj(this);
  myInspect->setUF(TRUE);
  myInspect->setChannel(FFLight->LightClicked());

  if (event.GetId() == SDLight->GetId())
  {
    myInspect->setUF(FALSE);
    myInspect->setChannel(0);
  }

  if (event.GetId() == FDLight->GetId())
  {
    myInspect->setUF(FALSE);
    myInspect->setChannel(1);
  }

  // In Delphi, the following method called automatically...
  myInspect->FormShow();
  myInspect->ShowModal();
	// printf("Request to view data for channel %d\n",FFLight->LightClicked());
  myInspect->Destroy();
}

void TFile::PanelDblClick (wxCommandEvent &event)
{
  TDetails * td = new TDetails(this,this,wxID_ANY);
  td->ShowModal(); 
  td->Destroy();
}


TFile::TFile (wxWindow * parent) :
    wxPanel(parent,wxID_ANY,wxDefaultPosition,wxSize(400,20),wxRAISED_BORDER)
{
    // Initial values 

  lOP = NULL;
  lFileName = wxFileName();
  lMonoD    = 0;
  lDT       = 0;
  lE0       = 0;
  lEmin     = 0;
  lEmax     = 0;
  lCalibration = 0;
  lCaltype  = 0;   // 0 = angle, 1 = energy

    // Data

  lChannels  = 0;      //number of channels, counting from 1
  lData      = NULL;
  lCoData    = NULL;
  lFoil      = NULL;
  lE         = NULL;

    // Controls

  lUF        = TRUE;
  lUFoil     = TRUE;
  lGrey      = FALSE;

    // Setup the panel

  // Caption    = _("");
  // BevelOuter = bvNone;
  // Event table...
  // OnDblClick = PanelDblClick;
  // Alignment  = taLeftJustify;

// Create the overall sizer
  wxBoxSizer * sizer_1 = new wxBoxSizer(wxHORIZONTAL);
  sizer_1->SetMinSize(400,20);
  info_button = new wxButton(this,wxID_PROPERTIES);
  Caption = new wxStaticText(this,wxID_ANY,_("None"),wxPoint(0,0),wxSize(100,20),wxALIGN_LEFT);
  Caption->Wrap(-1);
// Create the status lights 
  sizer_1->Add(info_button,0,wxALL,5);
  sizer_1->Add(Caption,1,wxEXPAND|wxALL,5);
  // LightPanel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxRAISED_BORDER);
  SDLight = new TLight(this);
  FDLight = new TLight(this);
  FFLight = new TLights(this);
  SDLight->SetSize(-1,-1,18,18);
  FDLight->SetSize(-1,-1,18,18);
  FFLight->SetSize(-1,-1,18,18);
  sizer_1->Add(SDLight,0,wxALL,5);
  sizer_1->Add(FDLight,0,wxALL,5);
  sizer_1->Add(FFLight,0,wxALL,5);
// File name label
// Use a sizer so that the label never overlaps the lights
  SDLight->SetToolTip(_("Sample transmission data"));
  FDLight->SetToolTip(_("Foil transmission data"));
  FFLight->SetToolTip(_("Fluorescence data"));

  //SDlight.ShowHint = True;
  //FDlight.ShowHint = True;
  //FFlight.ShowHint = True;

  // SDLight->SetSize(25,1,18,18);
  // FDLight->SetSize(55,1,18,18);
  // FFLight->SetSize(85,0,18,18);
  //SDlight.Parent = Self;
  //FDlight.Parent = Self;
  //FFlight.Parent = Self;

  // Event table stuff...
  // SDlight.OnDblClick = lightDblClick;
  // FDlight.OnDblClick = lightDblClick;
  // FFlight.OnDblClick = lightDblClick;

  // Height = 20;

  lNext = 0;
  lPrev = 0;

  SetSizer(sizer_1);
  Layout();
  Clear();
}


  // Destruct a file object

TFile::~TFile()
{
  Clear();
  if (lNext != 0)
    lNext->lPrev = lPrev;
  if (lPrev != 0)
    lPrev->lNext = lNext;
  lNext = 0;
  lPrev = 0;
}


  // Clear a file object 

void TFile::Clear()
{
  int C;
  int x,y;
  int width,height;
  
  Caption->SetLabel(_("None"));
    // Remove any lights 
  if (FFLight->GetNumber() > 0)
    FFLight->SetNumber(0);
  FFLight->GetPosition(&x,&y);
  GetSize(&width,&height);
  // SetSize(x,height);
    // Set the default values }

  lFileName = wxFileName();
  lMonoD = 0;
  lDT = 0;

    // Data 

  if (lFoil != 0) FData (lFoil);

  if (lData != 0)
    {
      for (C = 0; C < lChannels; C++)

        FData (lData[C]);

      free (lData);   // when did we assign this?
    }

  if (lE != 0)

    FreeVector (lE);

  lChannels  = 0;

  lData      = 0;
  lCoData    = 0;
  lFoil      = 0;
  lE         = 0;

    // Controls 

  lUF    = TRUE;
  lUFoil = TRUE;

    // Free the file object

  if (lOP != NULL)
      Command (CM_FREE, (char *) lOP);

  lOP = 0;
}


  // Return the number of transmission channels

int TFile::Transmission()
{
  int Count = 0;

  if (lChannels > 0)
  {
    if (lData [0] != NULL)

      Count = 1;

    if (lData [1] != NULL)

      Count = 2;
  }
  return (Count);
}


  // Return the number of fluorescence channels; should be two
  // less than total number of channels (i.e. lChannels)

int TFile::Fluorescence()
{
  if (lChannels > 0)

    return (lChannels - 2);

  else

    return (0);
}


  // Use the transmission or fluorescence data. Works
  // such that you can request transmission/fluorescence,
  // but the actual value will depend on what is available

void TFile::setlUF (bool Use)
{
  lUF = Use;
  if (Transmission() < 1)

    lUF = TRUE;

  if (Fluorescence() < 1)

    lUF = FALSE;
}


  // Use the second transmission channel or the data as foil.
  // True -> use foil data
  

void TFile::setlUFoil (bool Use)
{
  lUFoil = Use;
  if (Channels (lUF) < 1)

    lUFoil = TRUE;
}


  // Return the current average

WData * TFile::OCoData()
{
  return (lCoData);
}

  // Return the average

WData * TFile::CoData (bool UF)
{
  WData ** Data;
  bool OK;
  WData * CCData;
  int C, CN;
  if (lCoData == 0)
    lCoData = GData();
  OK = TRUE;
  if (UF)
	  {

      // Combine the fluorescence channels

    Data = (WData **) malloc (((Channels (UF) + 1) * sizeof (WData *)));

    C = 0;
    for (CN = 0;CN < Channels (UF); CN++)
    {

      CCData = Channel (UF, CN);

      if (CCData != 0)

        if (CCData->Use != 0)
        {
          Data [C] = CCData;

          C++;
        }
    }

    Data [C] = 0;

    OK = (CData (Data, lCoData) > 0);

    free (Data);
  }
  else
  {

    // Copy the first transmission channel

    Data = (WData **) malloc (2 * sizeof (WData *));

    Data [0] = Channel (UF, 0);

    if (Data [0]->Use == 0)

      Data [0] = NULL;

    Data [1] = NULL;

    OK = (CData (Data, lCoData) > 0);

    free (Data);
  }

  if (!OK)
  {
    FData (lCoData);
    lCoData = NULL;
  }

  return(lCoData);
}


  // Return the current foil

WData * TFile::OFoil()
{
  return(lFoil);
}


// Return the foil

WData * TFile::Foil()
{
  WData * CData;
  CData = 0;
  if (lUFoil)         // using real foil data

      // Copy the second transmission channel

    CData = Channel (FALSE, 1);

  else

      // Copy the data 

    CData = CoData (lUF);

  FData (lFoil);   //This will ignore null pointers

  lFoil = NULL;

  // Note below that we must physically copy the data,
  // otherwise, when we free the pointer, the destructor
  // for WData will clear everything else as well
  
  if (CData != NULL)
  {
    lFoil = GData();
	lFoil->E = MakeVector(CData->E->Nrows());
    *(lFoil->E)    = *(CData->E);
	lFoil->Data = MakeVector(CData->E->Nrows());
    *(lFoil->Data) = *(CData->Data);
  }
  return(lFoil);
}


  // Return the indicated data channel, counting
  // from zero.  lChannels is the maximum channel
  // number, starting at one

WData * TFile::Channel (bool UF, int CN)
{
  WData * cData = NULL;
  if (lChannels > 0)
  {
    if (UF)
    {
      if ((CN >= 0) && (CN+2 < lChannels))
        cData = lData[CN+2];
    }
    else
    {
      if ((CN == 0) || (CN == 1))
        cData = lData[CN];
    }
  }

  if (cData != NULL)
  {
    cData->PFile = this;  //Is accessed by Inspect object...

    if (UF)

      cData->UF = 1;

    else

      cData->UF = 0;

    cData->Channel = CN;
  }

  return(cData);
}


  // Return the number of channels

int TFile::Channels (bool UF)
{
  if (UF)      // fluorescence channels
  {
    if (lChannels > 2)

      return(lChannels - 2);

    else

      return(0);
  }
  else
  {
    if (lChannels > 1)

      return(2);

    else

      return(lChannels);
  }
}


  // Read a file 

void TFile::Read (const char * FileName)
{
	 int height,width;
     lFileName = wxFileName(wxString(FileName,*wxConvCurrent));
	 Caption->SetLabel(lFileName.GetFullName());
	 Caption->SetMinSize(Caption->GetSize());
	 Layout();   //If sizes have changed...
     lOP = Command (CM_OPEN, FileName);
}


wxString TFile::getName()
{
        return(lFileName.GetFullName());
}


  // Update the file parameters.  This is an important routine in
  // that it is called in order to read or re-read a file

void TFile::Update()
{
  int cChannel, cChannels;
  Columnvector * cData;
  if (lOP != NULL)
  {

      // Get the parameters

    if (lMonoD == 0)

      lMonoD = GetValue (lOP, MONOCHROMATOR_D);

    if (lDT == 0)

      lDT = GetValue (lOP, DEAD_TIME);

      // Get the energy scale

    getE();

    if (lChannels == 0)
    {
        // Count (from one) fluorescence channels

      cChannels = (int) (GetValue (lOP, FLUORESCENCE_CHANNELS));

        // Create all fluorescence plus two transmission

      lChannels = cChannels + 2;

      lData = (WData **) malloc ((lChannels + 1) * sizeof (WData *));

      for (cChannel = 0;cChannel<=lChannels;cChannel++)

        lData[cChannel] = NULL;  
      for (cChannel = 0;cChannel < cChannels; cChannel++)
      {
        cData = GetVector (lOP, FLUORESCENCE_CHANNEL, cChannel);
        if (cData != NULL)
        {
          lData[cChannel + 2] = GData();
          lData [cChannel + 2]->E     = lE;
          lData [cChannel + 2]->Data  = cData;
          lData [cChannel + 2]->E0    = lE0;
          lData [cChannel + 2]->Order = lOrder;
          lData [cChannel + 2]->Time = 0;
        }
      }

        // Get a copy of each transmission channel

      cChannels = (int) (GetValue (lOP, TRANSMISSION_CHANNELS));

      if (cChannels > 2)

        cChannels = 2;

      for (cChannel = 0;cChannel<cChannels;cChannel++)
      {
        cData = GetVector (lOP, TRANSMISSION_CHANNEL, cChannel);
        if (cData != NULL)
        {
          lData[cChannel] = GData();

          lData [cChannel]->E     = lE;
          lData [cChannel]->Data  = cData;
          lData [cChannel]->E0    = lE0;
          lData [cChannel]->Order = lOrder;

          lData [cChannel]->Time = 0;
        }
      }

        // Use a foil if it exists

      setlUFoil(TRUE);

        // Use fluorescence data by default

      setlUF(TRUE);
    }


      // Set the lights based on the data used

    if (FFLight->GetNumber() != Fluorescence())
    {
      FFLight->SetNumber(Fluorescence());
      Layout();
    }

    ChannelW (FALSE, 0, 1);  //Weight transmission channels
    ChannelW (FALSE, 1, 1);

	// Weight fluorescence channels

    for (cChannel = 0;cChannel<Fluorescence();cChannel++)
      ChannelW (TRUE, cChannel, 1);
  }
}

void TFile::setlMonoD (double D)
{
  int cChannel;
  if ((D != 0) && ((D != lMonoD) || (lE == NULL)))
  {
    lMonoD = D;

    SetValue (lOP, MONOCHROMATOR_D, lMonoD);

    FreeVector (lE);

    lE = GetVector (lOP, ENERGY, 0);

    if (lE != NULL)
    {

        // Get the maximum and minimum values 

      lEmin = 0;
      lEmax = 0;

      if (lE->Nrows() > 0)
      {
        lEmin = (*lE)(1);
        lEmax = (*lE)(lE->Nrows());
      }

        // Set Calibration to 0

      setlCalibration(0);

        // Copy the energy scale to all the channels

      for (cChannel = 0; cChannel<lChannels; cChannel++)

        if (lData [cChannel] != NULL)
        {
          lData [cChannel]->E = lE;
          lData [cChannel]->Time = 0;
        }
    }
  }
}


void TFile::setlDT (double D)
{
  int cChannel;
  int cUse;
  double cW;
  if ((D != 0) && (D != lDT))
  {
    lDT = D;
    SetValue (lOP, DEAD_TIME, lDT);
      // Get the new fluorescence data 

    for (cChannel = 2;cChannel < lChannels;cChannel++)

      if (lData[cChannel] != NULL)
      {
        FreeVector (lData[cChannel]->Data);

        cUse = lData[cChannel]->Use;
        cW   = lData [cChannel]->Weight;

        FData (lData [cChannel]);

        lData [cChannel] = GData();

        lData[cChannel]->Use = cUse;
        lData[cChannel]->Weight = cW;
        lData[cChannel]->E = lE;
        lData[cChannel]->Data =
                GetVector (lOP, FLUORESCENCE_CHANNEL, cChannel - 2);
        lData [cChannel]->E0    = lE0;
        lData [cChannel]->Order = lOrder;

        lData [cChannel]->Time = 0;
      }
  }
}


void TFile::setlOrder (double D)
{
  int cChannel;
  if (D != lOrder)
  {
    lOrder = D;

      // Change the Order value for all data

    for (cChannel = 0;cChannel<lChannels; cChannel++)
      if (lData [cChannel] != NULL)
      {
        lData [cChannel]->Order = lOrder;
        lData [cChannel]->Time = 0;
      }
  }
}

// Delphi 'property' functions

double TFile::E0()
{
	return lE0;
}

bool TFile::UF()
{
	return lUF;
}

void TFile::setlE0 (double D)
{
  int cChannel;
  if ((D != 0) && (D != lE0))
  {
    lE0 = D;

      // Change the E0 value for all data

    for (cChannel = 0;cChannel < lChannels;cChannel++)

      if (lData [cChannel] != NULL)
      {
        lData [cChannel]->E0 = lE0;
        lData [cChannel]->Time = 0;
      }
  }
}
double TFile::getMonoD()
{
	return lMonoD;
}

double TFile::getDT()
{
	return lDT;
}

double TFile::getlCalibration()
{
	return lCalibration;
}

int TFile::getCaltype()
{
        return lCaltype;
}

void TFile::setCaltype(int caltype)
{
// Undo the old calibration first
        setlCalibration (0.0);
        lCaltype = caltype;
}

// When setting the calibration, we distinguish between a
// simple translation of the energy scale, and a simple
// translation of the angular scale.  Which is in use is
// defined by the lCaltype flag.  If it represents an
// angular shift, it is given in degrees

void TFile::setlCalibration (double D)
{
  /* Note that D is notionally relative to the raw data, however
  all the callers of this routine appear to have operated on the
  already-calibrated data, so simply add in the previous calibration
  before calling this routine.*/

  D = D - getlCalibration();  

  if ((D != 0) && (lE != NULL))
  {

    if(lCaltype > 0)          //i.e. use energy scale
        {
        std::cout << "Calibrating: adding " << D << "to energy scale" <<std::endl;
        for (int C = 0;C<lE->Nrows();C++)

           (*lE)(C+1) = (*lE) (C+1) + D;
        lEmin = lEmin + D;
        lEmax = lEmax + D;
        }
    else if(lCaltype == 0)
        {
        double omega_shifted,d_rad;
        std::cout << "Calibrating: adding " << D << "to angular scale" <<std::endl;
        d_rad = D * M_PI / 180.0;
        for (int C = 0;C<lE->Nrows();C++)
           {
           omega_shifted = asin(12398.42/(lMonoD*2.0*(*lE)(C+1))) + d_rad;
           (*lE)(C+1) = 12398.42/(2.0*lMonoD*sin(omega_shifted));
           }
        omega_shifted = asin(12398.42/(lMonoD*2.0*lEmin)) + d_rad;
        std::cout << "Emin: " << lEmin << "-> ";
        lEmin = 12398.42/(2.0*lMonoD*sin(omega_shifted));
        std::cout << lEmin << std::endl;
        omega_shifted = asin(12398.42/(lMonoD*2.0*lEmax)) + d_rad;
        std::cout << "Emax: " << lEmax << "-> ";
        lEmax = 12398.42/(2.0*lMonoD*sin(omega_shifted));
        std::cout << lEmax << std::endl;
        }

    lCalibration = lCalibration + D;

  }
}

double TFile::Emin()
{
	return lEmin;
}

double TFile::Emax()
{
	return lEmax;
}

bool TFile::getUFoil()
{
	return lUFoil;
}

void TFile::getE()
{
  if (lMonoD == 0)
  {
	wxMessageBox(_("No monochromator setting implemented"));
	  /*
    Monochromator.FName = Name;

    if (!Monochromator.All)

      Monochromator.ShowModal();

    setlMonoD (Monochromator.D);
	  */
  }
  else

    setlMonoD (lMonoD);

  if (lE == NULL)

    wxMessageBox (_("The file ") + getName() + _(" lacks an energy scale"));
};


  // Energy-calibrate one file relative to another

  // Fixed is assumed to be the first file calibrated

void TFile::ECalibrate (TFile * Fixed)
{
  WData *CFoil;
  bool OK;
  CFoil = Foil();

  OK = (CFoil != NULL);

  if (OK)

    OK = (CFoil->Use != 0);

  if (!OK)

    wxMessageBox (getName() + _(" has no valid foil"));

  else
    {
    // We use the third argument of the OData call to flag whether
    // or not we want angle-based calibration; zero means use the
    // energy scale
    double send_mono;
    if(lCaltype == 0) send_mono = lMonoD;
    else send_mono = 0;
    if (OData (CFoil, Fixed->OFoil(),send_mono) != 0)

      setlCalibration(getlCalibration() + CFoil->Calibration);
    }
}
