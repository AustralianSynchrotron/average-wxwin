/***************************************************************************
 *            TWeightThread.cc
 *
 *  Fri Aug 18 21:51:09 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/
#include "TWeightThread.h"

void TWeightNoThread::setMode (int Mo)
{
  lMode = Mo;
}

void TWeightNoThread::Clear()
{
  if (lData != NULL)

    free (lData);

  lData = NULL;
  lEntries = 0;     // number of datasets
}


int TWeightNoThread::Entries()
{
  return(lEntries);
}

//Entry counts from zero

WData * TWeightNoThread::Data (int Entry)
{
  if ((Entry >= 0) && (Entry < Entries()))

    return (lData [Entry]);

  else

    return (NULL);
}

// Add data to the average calculation, called before
// executing.  We allocate memory in blocks of 64 to
// save time in malloc

void TWeightNoThread::Include (WData * Data, int Mo)
{
  WData ** cData;
  int E;
  int maxEntries = (div(lEntries + 63 , 64)).quot * 64;

	// Expand data storage array
  if (maxEntries < lEntries + 2)     //We need lEntries plus NULL sentinel
  {
    cData = (WData **) malloc ((maxEntries + 64) * sizeof (WData *));

    for (E = 0;E<lEntries;E++)

      cData [E] = lData [E];

    if (lData != NULL) free (lData);

    lData = cData;
  }

  lData [lEntries] = Data;
  lData [lEntries + 1] = NULL;

  lEntries++;

    // Mark as pending 

  if (Mo < 2)

    Data->Pending = 1;
}


void TWeightNoThread::Int()
{
  lInt = TRUE;
}


bool TWeightNoThread::Interrupted()
{
  return (lInt);
}


TWeightNoThread::~TWeightNoThread()
{
  Clear();
}


TWeightNoThread::TWeightNoThread (WData * CoData,
                                  wxStatusBar * Panel,
                                  TInspect * view)
{
  lPanel   = Panel;
  lCoData  = CoData;
  lInspect = view;
  lData    = NULL;
  lEntries = 0;
  lC       = -1;
  lDone    = -1;
  lInt     = FALSE;
}


void TWeightNoThread::Finished()
{
  lPanel->SetStatusText(_(""),0);
}


void TWeightNoThread::Working()
{
  lPanel->SetStatusText(wxString::Format (_("Calculating: %.1f%%"), 100 * lCC / (Entries() + 1)),0);
}

/* private variable lDone counts how many calculations have
been done.  We set to -1 so that the first time through the
average data is displayed */

void TWeightNoThread::Done()
{
  if (lOnDone)   //show result

    if (lDone== -1)
    {
      lCoData->Pending = 0;

      (lInspect->*lOnDone) (lCoData);
    }
    else
    {
      lData [lDone]->Pending = 0;

      (lInspect->*lOnDone) (lData [lDone]);
    }

  lDone++;
}

int TWeightNoThread::getMode()
{
	return lMode;
}

void TWeightNoThread::Execute()
{
	int Time;

    /* Mode: 0 CData  UData
            1 CData  UData (Don't recalculate the scale)
            2 CData }
    CData calculates the average; UData calculates weights
	before averaging.
    { First check the combined data }
   */
  bool OK = CData (lData, lCoData) > 0;

  if (OK)
  {

      /* Update all the data.  The first time through,
      lC = -1 and UData is run on lCoData.  The next
      time through, lC runs from 0 to Entries(); if we
      are in mode 2, we do not recalculate any weights,
      and so we break in this condition. */	  

    lC = -1;

    while (lC < Entries())
    {
      if ((lMode >= 2) && (lC== 0))

        break;

      if (lInt)

        break;

      lCC = lC;

      Working();

      if (lC== -1)  //First time
      {
        UData (lCoData, lCoData);

        Done();
      }
      else  //Force a recalculation
      {
        Time = lCoData->Time;

        if (lMode== 1)

          lCoData->Time = -1;

        UData (lData [lC], lCoData);

        lCoData->Time = Time;

        Done();
      }

      lC++;
    }
  }

  Finished();
}

void TWeightNoThread::setOnDone(void (TInspect::*ondone)(WData *))
{
	lOnDone = ondone;
}
