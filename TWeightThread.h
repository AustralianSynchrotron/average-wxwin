/***************************************************************************
 *            TWeightThread.h
 *
 *  Fri Aug 18 21:51:23 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/

#ifndef _TWEIGHTTHREAD_H
#define _TWEIGHTTHREAD_H

#include <wx/wx.h>

#include "cvector.h"
#include "weight.h"
#include "avelib.h"

// forward declaration for function pointer

class TInspect;
	
class TWeightNoThread {
  private:
    WData ** lData;
    int lEntries;
    int lMode;
    int lC;
    int lDone;
    int lCC;
    bool lInt;
    wxStatusBar *lPanel;
    TInspect * lInspect;   //For callback
    void Working();
    void Finished();
    void Done();
    void (TInspect::*lOnDone)(WData * WD);
  
  public:
    void Clear();
    void Int();
    bool  Interrupted();
    void Include (WData * Data, int Mo);
    int  Entries();
    WData *  Data (int Entry);
    WData * lCoData;        // should be private...

    TWeightNoThread (WData *CoData,wxStatusBar *lPanel,TInspect * view);
    ~TWeightNoThread();

    void Execute();

  // published
    void setOnDone(void (TInspect::*ondone)(WData * WD));
    void (*getOnDone())();
    int getMode();
    void setMode (int Mo);

  //  property OnDone: TWDataEvent read lOnDone write lOnDone;
  //
  //  property Mode:   Integer read lMode  write setMode;
  };


#endif /* _TWEIGHTTHREAD_H */
