#ifndef TGraphHelpers_h
#define TGraphHelpers_h
#include "TGraph.h"

void PrintGraph(TGraph * g)
{
   cout << g->GetName() << endl;
   for (int ib=0;ib<g->GetN();++ib) {
      double x=0, y=0, errYL=0, errYH =0;
      g->GetPoint(ib,x,y);
      errYH = g->GetErrorYhigh(ib);
      cout << "x: " << x << " y: " << y << " yerr: " << errYH << endl;
   }
   cout << endl;
}

void PrintGraphAndSys(TGraph * g, double * sys)
{
   cout << g->GetName() << endl;
   for (int ib=0;ib<g->GetN();++ib) {
      double x=0, y=0, errYL=0, errYH =0;
      g->GetPoint(ib,x,y);
      errYH = g->GetErrorYhigh(ib);
      cout << "x: " << x << " y: " << y << " yerr: " << errYH << " ysys: " << y*sys[ib] << endl;
   }
   cout << endl;
}
#endif