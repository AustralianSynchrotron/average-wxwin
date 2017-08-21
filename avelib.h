#ifndef _AVELIB_H
#define _AVELIB_H

#include "cvector.h"  // From the average DLL
#include "weight.h"   // From the average DLL
#include "commands.h" // From the average DLL

typedef struct {

  //wxString       * Name;   //SaveAverage needs this to be a char *
  char        *  Name;
  double         D;
  double         Calibration;
  double         DT;

  Columnvector * Weight;

  } TAvFileInfo;

typedef struct  {

  const char *   Atom;
  const char *   Edge;

  WData *        Data;
  WData *        Foil;
  double         E0;
  int            Files;
  TAvFileInfo *   FileD;
  int            calibration_type;
} TAvInfo;

#ifdef __cplusplus
extern "C"
{
#endif
extern double GetE0(const char * Atom, const char * edge);
extern int Success();
extern void FData(WData * WD);
extern void FreeVector(Columnvector * CV);
extern Columnvector * MakeVector(int size);
extern Columnvector * GetVector(void * obj, int index, int channel);
extern WData * GData();
extern int UData(WData * WD, WData * WDa);
extern void * Command(int command,const char * value);
extern int CData(WData ** wdl,WData *);
extern int OData(WData * wd, WData *wda, double mono_d);
extern double GetValue(void * obj,int index);
extern void SetValue(void *obj, int index, double value);
extern void SaveAverage(TAvInfo * info, const char * filename);
extern Columnvector * CDerivative(int Order, Columnvector *X, Columnvector *Y);

#ifdef __cplusplus
}
#endif

#endif
