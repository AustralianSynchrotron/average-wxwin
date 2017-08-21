#ifndef _TLIGHT_H
#define _TLIGHT_H
#include <wx/wx.h>

class TLight : public wxPanel {
  private:
    bool FValid;
    wxColour FColour;
    wxString Caption;    //replaces Delphi caption property
    void SetLightClicked(wxMouseEvent &event);
  public:
    TLight (wxWindow * parent);
    int Tag;   //For event reporting?
    void ChangeValid (bool NewValid);
    void ChangeColour (wxColour NewColour);
 // property Valid: Boolean  read FValid  write ChangeValid;
    // property Color: TColor   read FColor  write ChangeColor;
    DECLARE_EVENT_TABLE()
  };

  WX_DEFINE_ARRAY(TLight *, TLightArray);

  class TLights: public wxPanel {
  private:
    TLightArray Lights;
    int FLightWidth;
    int FLightClicked;
    
    void SetLightClicked (wxMouseEvent &event);
    void LightClick (wxMouseEvent &event);
    void LightDblClick (wxMouseEvent &event);
  public:
    TLight*  Light(int LightNumber);
    int LightClicked();
    void Click();
    void DblClick();
    int GetNumber();  // handled by wxArray, becomes GetCount
    void SetNumber (int NewNumber);
    TLights (wxWindow * parent);
    ~TLights();
    // property Number: Integer  read GetNumber  write SetNumber;
  DECLARE_EVENT_TABLE()
  };

#endif /* _TLIGHT_H */
