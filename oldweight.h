
#if !defined WEIGHT_H

#define WEIGHT_H

#include <utility>
#include <list>

// Cal_energy means calibrations are performed in terms of energy
// otherwise the angular scale is shifted

#define CAL_ENERGY      1
#define CAL_ANGLE       2

#if defined TESTDLL_CPP

struct WData {

  double Calibration, Scale, E0, Emax, Order, Weight, CalWeight;
  
  Columnvector * E;
  Columnvector * Data;
  Columnvector * Convoluted;
  Columnvector * Noise;
  Columnvector * KScale;
  Columnvector * Signal;

  int Scheme, Average, Fixed, Use, Pending, Time;

    // Unspecified associated data

  void * DataPointer;

  int UF, Channel;
  
  };

#else

class WData {

  public:
  
    double Calibration, Scale, E0, Emax, Order, Weight, CalWeight;
  
    Columnvector * E;
    Columnvector * Data;
    Columnvector * Convoluted;
    Columnvector * Noise;
    Columnvector * KScale;
    Columnvector * Signal;

      // For implementing excluded regions

    std::list<std::pair<double,double> > excluded_list;

    int Scheme, Average, Fixed, Use, Pending, Time;

      // Unspecified associated data

    void * PFile;

    int UF, Channel;

    double CE0, CEmax, COrder;

    static int CTime;   //JRH: Used to remember last update

                        WData ();
                       ~WData ();
  
		       WData&         operator = (const WData&);
    int Clear ();

    int CAverage (WData ** D);

    int CNoise ();

    int CScale (WData& A);

    int CSignal (double E0, double Emax, double Order);

    double CCalibration (WData& A);   //Calibrate against E

    double ACalibration (WData& A,double mono_D); //Calibrate against angle

    double CWeight (WData& A);

    // For implementing excluded regions

    bool is_excluded(double data_point);

  };


inline WData::WData () {

  //E          = new Columnvector(0);
  E          = NULL;
  Data       = NULL;
  Convoluted = NULL;
  Noise      = NULL;
  KScale     = NULL;
  Signal     = NULL;

  PFile = NULL;

  UF = Channel = 0;
  
  Clear ();

  }


inline WData::~WData () {

  Clear ();

  /* delete E;
  delete Data;
  delete Convoluted;
  delete Noise;
  delete KScale;
  delete Signal; */

  }


inline int WData::Clear () {

  if (E)

    E->ReSize(0);
    
  if (Data)

    Data->ReSize(0);
    
  if (Convoluted)

    Convoluted->ReSize(0);
    
  if (Noise)

    Noise->ReSize(0);
    
  if (KScale)

    KScale->ReSize(0);

  if (Signal)

    Signal->ReSize(0);
  
  E = NULL;
  Data = NULL;
  Convoluted = NULL;
  Noise = NULL;
  KScale = NULL;
  Signal = NULL;

  Calibration = 0;
  Scale       = 1;
  E0          = 0;
  Emax        = 0;
  Order       = 0;
  Weight      = 1;
  CalWeight   = 1;
    
  Scheme  = 0;
  Average = 0;
  Fixed   = 0;
  Use     = 1;
  Pending = 0;

  CE0    = 0;
  CEmax  = 0;
  COrder = 0;
    
  return Time = CTime++;

  }

#endif

#endif // WEIGHT_H

