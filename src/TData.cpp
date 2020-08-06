#include "TData.hpp"

TData::TData ()
{
  e_abs.resize();
}

TData::~TData ()
{
}
void TData::Zero (void)
{
  e_begin = 0;
  eabs_calor = 0;
  z = 160;
  y = 0;
  x = 0; 
  for (int i = 0;i < e_abs.size(); i++)
  {
    e_abs[i] = 0;
  }
}
