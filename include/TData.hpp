#ifndef TDATA_H
#define TDATA_H
#include <vector>
class TData
{
  public:
    TData ();
    ~TData ();
    void Zero (void);
    inline double GetEabs_calor (void) { return eabs_calor; }
    inline double GetE_begin (void) { return e_begin; }
    inline double GetZ (void) { return z; }
    inline double GetY (void) { return y; }
    inline double GetX (void) { return x; }

    inline void SetEabs_calor (double Eabs_calor) { eabs_calor = Eabs_calor; }
    inline void SetE_begin (double E_begin) { e_begin = E_begin; }
    inline void SetZ (double Z) { z=Z; }
    inline void SetY (double Y) { y=Y; }
    inline void SetY (double X) { x=X; }    

    double eabs_calor;
    double e_begin;
    std::vector <double> e_abs;
    double x, y, z;
};

#endif
