/***************************************************************************
 *            tlight.cc
 *
 *  Wed Aug  2 11:50:40 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/
#include "tlight.h"
TLight::TLight (wxWindow * parent)
    : wxPanel (parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxSIMPLE_BORDER)
{
  // Font style -> bold
  Raise(); Show();
  ChangeValid (FALSE);
}

BEGIN_EVENT_TABLE(TLight, wxPanel)
  EVT_LEFT_UP    (TLight::SetLightClicked)
  EVT_LEFT_DCLICK(TLight::SetLightClicked)
END_EVENT_TABLE()

void TLight::ChangeColour (wxColour NewColour)
  {
  FColour = NewColour;
  if (FValid) ChangeValid (FValid);
}

void TLight::ChangeValid (bool NewValid)
{
  FValid = NewValid;
  Enable(FValid);      //Enable/disable for user input
  if (FValid)
  {
    Caption = _("");
    SetBackgroundColour(FColour);
  }
  else
  {
    Caption = _("I");
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
  }
  Refresh();
}

void TLight::SetLightClicked(wxMouseEvent &event)
{
	printf("Individual light clicked at %d\n",event.GetId());
	GetParent()->AddPendingEvent(event);
	event.Skip();
}

BEGIN_EVENT_TABLE(TLights, wxPanel)
  EVT_LEFT_UP    (TLights::SetLightClicked)
  EVT_LEFT_DCLICK(TLights::SetLightClicked)
END_EVENT_TABLE()

void TLights::SetLightClicked (wxMouseEvent &event)
  {
  int Count;
  FLightClicked = -1;
  Count = 0;
  printf("Light clicked at %d\n",event.GetId());
  while (Count < Lights.GetCount())
    {
      if (Lights[Count] == event.GetEventObject())
	  {
          printf("Identified as light number %d\n",Count);		  
	      FLightClicked = Count;
	  }
      Count++;
    }	
  GetParent()->AddPendingEvent(event);  //pass on up!
  event.Skip();
  }

void TLights::LightClick (wxMouseEvent &event)
{
  SetLightClicked (event);
  //inherited Click   -> in wxWidgets this is automatic
}

void TLights::Click()
{
  FLightClicked = 0;
  //inherited Click;
}

void TLights::LightDblClick (wxMouseEvent &event)
{
  SetLightClicked (event);
  //inherited DblClick;
}

void TLights::DblClick()
{
  FLightClicked = 0;
  //inherited DblClick;
}

TLights::TLights (wxWindow * parent)
    : wxPanel((wxPanel *) parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
  // inherited Create (AOwner);
  Lights.Empty();
  FLightWidth = 20;
  SetNumber (0);
}

TLights::~TLights()
  {
	  SetNumber (0);
  // inherited Destroy;
  }

int TLights::GetNumber()
  {
	  return Lights.GetCount();
  }
  
  //To do: we need to set the event handling properly...
void TLights::SetNumber (int NewNumber)
{
  int Count;
// First release storage in our lights array.  Was allocated
	// by new, so we use delete
  for (Count = 0;Count < Lights.GetCount();Count++)
  {
	  delete Lights[Count];
  }
  Lights.Empty();
  // Height = FLightWidth;
  if (NewNumber > 0)
  {
    for (Count= 0; Count < NewNumber; Count++)
    {
      Lights.Add(new TLight(this));
      TLight* templight = Lights[Count];
      {
        templight->Tag = Count;
        templight->SetSize(Count * FLightWidth + 1,1,FLightWidth - 2, FLightWidth -2);
        // templight->OnClick = LightClick;
        // templight.OnDblClick = LightDblClick;
      }
  }
    // Width = FLightWidth * NewNumber;
    SetSize(FLightWidth*NewNumber+1,FLightWidth);
    SetMinSize(wxSize(FLightWidth*NewNumber+1,FLightWidth));
    printf("Set flight array width to %d\n",FLightWidth*NewNumber+1);
  }
}


TLight* TLights::Light (int LightNumber)
{
  if ((LightNumber < 0) || (LightNumber >= Lights.GetCount())) return(0);
  else return(Lights[LightNumber]);
}

int TLights::LightClicked()
{
	return FLightClicked;
}
