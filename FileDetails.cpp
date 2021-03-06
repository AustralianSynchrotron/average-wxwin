// -*- C++ -*- generated by wxGlade 0.4.1 on Mon Jul 31 13:34:58 2006

#include "FileDetails.h"

// Store these to be globally visible
wxString gl_Atom;       //Atom name, info only
wxString gl_Edge;       //Edge value, info only


FileDetails::FileDetails(const wxString& title, const wxPoint& pos, const wxSize& size):
    wxFrame((wxFrame *) NULL, -1, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
    // begin wxGlade: FileDetails::FileDetails
    LoadButton = new wxButton(this, wxID_OPEN);
    CalibrateButton = new wxButton(this,CAL_BUTTON, wxT("Calibrate"));
    SaveButton = new wxButton(this, wxID_SAVE);
    FilePanel = new wxPanel(this, -1,wxDefaultPosition,wxDefaultSize,wxVSCROLL);
    CloseButton = new wxButton(this, wxID_EXIT);

    set_properties();
    do_layout();
    // end wxGlade
	// start our changes
	// config_data = new wxFileConfig();
    lOpenFile.Atom  = NULL;
    lOpenFile.Edge  = NULL;
    lOpenFile.Data  = NULL;
    lOpenFile.Foil  = NULL;
    lOpenFile.E0    = 0;
    lOpenFile.FileD = NULL;
	// initialise global energy values
    gl_Atom = _("");
    gl_Edge = _("");

    SaveButton->SetEvtHandlerEnabled(FALSE);
    CalibrateButton->SetEvtHandlerEnabled(FALSE);
}


BEGIN_EVENT_TABLE(FileDetails, wxFrame)
    // begin wxGlade: FileDetails::event_table
    EVT_BUTTON(wxID_OPEN, FileDetails::LoadButtonClick)
    EVT_BUTTON(CAL_BUTTON, FileDetails::CalButtonClick)
    EVT_BUTTON(wxID_SAVE, FileDetails::SaveButtonClick)
    EVT_BUTTON(wxID_EXIT, FileDetails::CloseButtonClick)
    // end wxGlade
END_EVENT_TABLE();

void FileDetails::set_properties()
{
    // begin wxGlade: FileDetails::set_properties
    SetTitle(wxT("Average 2.0.6"));
    FilePanel->SetMinSize(wxSize(434, 100));
    // end wxGlade
}


void FileDetails::do_layout()
{
    // begin wxGlade: FileDetails::do_layout
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_3 = new wxBoxSizer(wxHORIZONTAL);
	file_sizer = new wxBoxSizer(wxVERTICAL);  //for the rows of lights
	FilePanel->SetSizer(file_sizer);
    sizer_3->Add(LoadButton, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_3->Add(CalibrateButton, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_3->Add(SaveButton, 0, wxALL|wxADJUST_MINSIZE, 5);
    sizer_3->Add(20, 20, 1, wxADJUST_MINSIZE, 0);
    sizer_2->Add(sizer_3, 0, wxADJUST_MINSIZE, 0);
    sizer_2->Add(FilePanel, 1, wxEXPAND, 0);
    sizer_2->Add(CloseButton, 0, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM|wxADJUST_MINSIZE, 5);
    SetAutoLayout(true);
    SetSizer(sizer_2);
    sizer_2->Fit(this);
    sizer_2->SetSizeHints(this);
    Layout();
    // end wxGlade
}

void FileDetails::LoadButtonClick(wxCommandEvent &event)
{
	wxArrayString paths;
        char * fname;
    wxFileDialog * fileselect;
	LoadButton->SetEvtHandlerEnabled(FALSE);
	fileselect = new wxFileDialog((wxWindow *)NULL,_("Choose input files"),
	                                  _(""),_(""),
	                                  _("*.*"),
	                                  wxOPEN|wxMULTIPLE|wxCHANGE_DIR);
	int result = fileselect->ShowModal();
	if(result==wxID_OK) {
		fileselect->GetPaths(paths);
		int n = paths.GetCount();
		for(int i=0;i<n;i++) {
		    printf("%s\n",(const char *) paths[i].mb_str(wxConvUTF8));
		}
		paths.Sort();
		if(lOpenFile.FileD)
		{
			for(int c=0;c<lOpenFile.Files;c++)
				free (lOpenFile.FileD[c].Name);
			free (lOpenFile.FileD);
		}
		lOpenFile.FileD = (TAvFileInfo *) malloc(paths.GetCount()*sizeof(TAvFileInfo));
		lOpenFile.E0 = 0;
		for (int c=0;c<paths.GetCount();c++) {
			TAvFileInfo * d = &(lOpenFile.FileD[c]);
			// copy the string into heap storage
                        int outlen = paths[c].Len()+1;  //+1 for trailing null
                        fname = (char *) malloc(outlen*sizeof(char));
                        // Done this way because other ways gave junk strings
                        snprintf(fname, outlen, "%s",(const char *) paths[c].mb_str(wxConvUTF8));
			lOpenFile.FileD[c].Name = (char *) malloc(outlen*sizeof(char));
			strcpy(lOpenFile.FileD[c].Name,fname);
                        free(fname);
			d->D = 0;
			d->Calibration = 0;
			d->DT = 0;
			d->Weight = NULL;
		}
		lOpenFile.Files = paths.GetCount();
		lOpenCount = 0;
		OpenFileDone();
	}
	fileselect->Destroy();
	LoadButton->SetEvtHandlerEnabled(TRUE);
}

// This is where we read in the actual data.

void FileDetails::OpenFileDone()
{
	int curwid,curheight,cfwid,cfheight;
	TFile *CurrentFile;
	for(int filect=0;filect<lOpenFile.Files;filect++)
	  {
	  AddFile(); //Create new light array in File Panel
	  CurrentFile = FFiles.Last();  //The one we just added
	  file_sizer->Add(CurrentFile);
	  file_sizer->Layout();
	  /*FilePanel->GetSize(&curwid,&curheight);
	  CurrentFile->GetSize(&cfwid,&cfheight);
	  FilePanel->SetSize(curwid,FFiles.GetCount()*cfheight);
	  CurrentFile->SetPosition(wxPoint(0,filect*22));*/
	  if (filect == 0) {          //First time
			//Disable all buttons
			LoadButton->SetEvtHandlerEnabled(FALSE);
			CalibrateButton->SetEvtHandlerEnabled(FALSE);
			SaveButton->SetEvtHandlerEnabled(FALSE);
	  }
	  // Was thread initialise (thread local data)
	  FFile = CurrentFile;   //The one we just added
	  lD = lOpenFile.FileD[filect];
      lE0 = lOpenFile.E0;
	// In delphi this is thread execute
	FFile->Read(lD.Name);
	FFile->setlE0(lE0);
	FFile->setlMonoD(lD.D);
	FFile->setlDT(lD.DT);
	FFile->setlCalibration(lD.Calibration);
	// Thread update
	if (FFile->E0() == 0)
	// Note differing behaviour; Delphi used previous
        // file's value for E0
        FFile->setlE0(FFiles[0]->E0());
        FFile->Update();
	Layout();    //In case the file_sizer has expanded

        FFile->setlUF(TRUE);

        if (lD.Weight != NULL)

            for (int C = 0; C<lD.Weight->Nrows();C++)

               FFile->ChannelUse (FFile->UF(), C, (*(lD.Weight))(C+1) > 0);
		// Now the head part of Delphi OpenFileThreadDone
      if (FFile->OK()) {
        int Count = 0;
        if (FFile->Transmission() >= 2) Count = 1;
        if ((FFile->Transmission() >= 1) &&
           (FFile->Fluorescence() > Count)) Count = FFile->Fluorescence();
		/* wxRect pos = FilePanel->GetRect();
        if (186 + 20 * Count > pos.width)
		{
          pos.width = 186 + 20 * Count;
		  FilePanel->SetSize(pos);
		} */
        Show();
        FilePanel->Layout();
	Layout();    //In case the file_sizer has expanded
	}
    else           //Try to read as averaged file
    {
        wxString LName = FFile->getName();
        if (FFiles.GetCount() == 1)
            FFiles.clear();

          // Try to read the file as an average output

        //if (!ReadGDF (LName))
        {
          // StatusBar.Panels [0].Text := SName + ' is not a valid data file';

          // MessageDlg (StatusBar.Panels [0].Text, mtInformation, [mbOk], 0);
        }
	}
}
    SaveButton->SetEvtHandlerEnabled(TRUE);
    CalibrateButton->SetEvtHandlerEnabled(TRUE);
    LoadButton->SetEvtHandlerEnabled(TRUE);
}

void FileDetails::AddFile()
{
  TFile * CFile;
  CFile = new TFile(FilePanel);

  //with CFile do
  //begin
  //  Visible := False;
  //  Parent  := FilePanel;
  //  Align   := alTop;
  //  GS      := Grey.Checked;
  //end;
  
  //Duplicate the linked list in the original; this is
  // useful for the forward/backward buttons
  if(FFiles.GetCount()>0) FFiles.Last()->Append(CFile);
  FFiles.Add(CFile);
  SaveButton->SetEvtHandlerEnabled(TRUE);
  CalibrateButton->SetEvtHandlerEnabled(TRUE);
}

void FileDetails::CalButtonClick(wxCommandEvent &event)
{
  int Count;
  TFile * Fixed;
  TFile * CFile;
  CalibrateButton->Enable(FALSE);

    // Call the calibration form

  TCalibrate * cal_dialog = new TCalibrate(&FFiles,(wxWindow *) this);

  if(cal_dialog->ShowModal()==wxID_OK)

    // Add the calibration to all files

  {
    CFile = FFiles[0];
    Count = 0;

    while (CFile != NULL)
    {
      Count++;

      CFile->setlCalibration(CFile->getlCalibration() +
                                       cal_dialog->Calibration());
      CFile->Update();

      CFile = CFile->Next();
    }
  }

  cal_dialog->Destroy();
  CalibrateButton->Enable(TRUE);
}

void FileDetails::SaveButtonClick(wxCommandEvent &event)
{
  int C, Channel, Channels;
  TAvInfo Info;
  TFile * CFile;
  wxCharBuffer item_as_mbstr;
  WData * CoData, *CoFoil, *CData;
  bool OKData, OKFoil;
  wxFileDialog * filesave;


  // Run the save dialog

  SaveButton->SetEvtHandlerEnabled(FALSE);

  filesave = new wxFileDialog((wxWindow *)NULL,_("Save file name"),
	                                  _(""),_(""),
	                                  _("*.*"),
	                                  wxSAVE|wxOVERWRITE_PROMPT|
	                                  wxCHANGE_DIR);

  int result = filesave->ShowModal();
  if (result==wxID_OK)
  {
	  wxString newfilename = filesave->GetPath();
	  if (newfilename.Len() > 0)
	  {

      // Create the averaged data: a / foil / ff

      CoData = NULL;
      CoFoil = NULL;

      Info.Data = NULL;
      Info.Foil = NULL;
      // convert to simple characters
      int alen = gl_Atom.Len()+1;
	  item_as_mbstr = gl_Atom.mb_str();
      Info.Atom = strdup ((const char *) item_as_mbstr);
      // snprintf((char *) Info.Atom,alen,"%s",(const char *) item_as_mbstr);
      alen = gl_Edge.Len()+1;
	  item_as_mbstr = gl_Edge.mb_str();
	  Info.Edge = strdup( (const char *) item_as_mbstr);
    //snprintf((char *) Info.Edge,alen,"%s",(const char *) item_as_mbstr);
      OKData = Calculate (&CoData, FALSE);
      OKFoil = Calculate (&CoFoil, TRUE);

    if (OKData)

      Info.Data = CoData;

    if (OKFoil)

      Info.Foil = CoFoil;

      // Allocate space to save the array of information

    Info.FileD = (TAvFileInfo *) malloc ((lOpenFile.Files + 1) * sizeof (TAvFileInfo));

    C = 0;

    CFile = FFiles[C];

    for(C=0;(C<FFiles.GetCount()) && (CFile != NULL);C++)
    {

        // Copy the information from each file
      CFile = FFiles[C];
      Info.E0 = CFile->E0();

      {
		TAvFileInfo * d = &(Info.FileD[C]);
	wxString fname;
        fname = CFile->getName();
        int fnlen = fname.Len()+1;
        d->Name = (char *) malloc (fnlen*sizeof(char));
	snprintf(d->Name,fnlen,"%s",(const char *) fname.mb_str());
        d->D           = CFile->getMonoD();
        d->Calibration = CFile->getlCalibration();
        d->DT          = CFile->getDT();

        Channels = 1;

        if (CFile->UF())

          Channels = CFile->Channels (CFile->UF());

        d->Weight = MakeVector (Channels);

        for (Channel = 0;Channel < Channels;Channel++)
        {
          CData = CFile->Channel (CFile->UF(), Channel);

		// Note that the Columnvector () operator counts from 1, not zero

          if (CData == NULL)

           (*(d->Weight))(Channel+1) = -1;

          else

           (*(d->Weight))(Channel+1) = CData->Use;
	  }
      }

  }

    Info.Files = FFiles.GetCount();

    int fnamelen = newfilename.Len()+1;
    char * simple_fname = (char *) malloc(fnamelen*sizeof(char*));
    snprintf(simple_fname,fnamelen,newfilename.mb_str());
    SaveAverage (&Info,simple_fname);

      // Free the average data

    if (CoData != NULL)

      FData (CoData);

    if (CoFoil != NULL)

      FData (CoFoil);

      // Free the weights

    for (C = 0; C < Info.Files;C++)

	{
	  free (Info.FileD[C].Name);

      FreeVector (Info.FileD [C].Weight);
	}

      // Free the array

    free (Info.FileD);
}
}
  SaveButton->SetEvtHandlerEnabled(TRUE);
}

bool FileDetails::Calculate (WData ** CoData, bool UFoil)
{
  TFile *CFile;
  int CChannel, CChannels;
  WData * CCData;
  int C, Csum;
  int CC;
  WData ** Data;
  bool OK;

  // Count the channels

  Csum = 1;

  CFile = FFiles[0];

  for (CC=0;CC<FFiles.GetCount() && (CFile != NULL) ;CC++)
  {
    CFile->setlUF(TRUE);
    CFile->setlUFoil(TRUE);
    CChannels = 1;
    if (!UFoil && CFile->UF())

      CChannels = CFile->Channels (CFile->UF());

    Csum = Csum + CChannels;   //Total number of channels+1

    // Not needed because of bounds check CFile = FFiles[CC+1];
  }

  Data = (WData **) malloc (Csum * sizeof (WData *));


    // Add all the data

  CFile = FFiles[0];

  C = 0;      //Count of active channels

  for (CC=0;CC<FFiles.GetCount() && CFile!=NULL;CC++)
  {
	CFile = FFiles[CC];
    CChannels = 1;

    if ((!UFoil) && CFile->UF())

      CChannels = CFile->Channels (CFile->UF());

    for (CChannel = 0; CChannel < CChannels; CChannel++)
    {
      if (UFoil)

        CCData = CFile->Channel (FALSE, 1);

      else

        CCData = CFile->Channel (CFile->UF(), CChannel);

      if (CCData != NULL)

        if (CCData->Use != 0)
        {
          Data [C] = CCData;

          C++;
        }
    }
  }

  Data [C] = NULL;   //sentinel at end

    // Calculate the average

  if (*CoData == NULL)

    *CoData = GData();

  OK = CData (Data, *CoData) > 0;

  free (Data);

  return(OK);
}

void FileDetails::CloseButtonClick(wxCommandEvent &event)
{
  wxFileName outfile;
  wxString cwd,localdata;
  wxFileConfig * config_data;
  wxStandardPaths pathlist;
  // Write the current directory to the INI file
  // localdata = pathlist.GetUserDataDir();
  // wxFileName::Mkdir(localdata,0777,wxPATH_MKDIR_FULL);
  // outfile = wxFileName(localdata,_("XFIT.INI"));
  /*Note the use of the USE_NO_ESCAPE_CHARs style: this is because, on Windows,
    our INNO setup installer writes to the .INI file, and it can't do the double
    backslash for auto-substituted constands (e.g. {app} */
  config_data = new wxFileConfig(_("XFIT"),
		                 _(""),
				 _("XFIT.INI"),
		                 _(""),
				 wxCONFIG_USE_LOCAL_FILE|wxCONFIG_USE_NO_ESCAPE_CHARACTERS);
  cwd = wxGetCwd();
  config_data->SetPath (_("/Average"));
  config_data->Write(_("CurrentDirectory"), cwd);
  delete config_data;
  Close(TRUE);
}


// wxGlade: add FileDetails event handlers
