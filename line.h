#ifndef LINE_H
#define LINE_H

#include "graphobject.h"

class Line : public GraphObject
{
    //y-intrcept
    double b;
    //slope
    double m;

    double upperBound;

    double lowerBound;

    double increments = 0.1;
public:
    Line() ;
    Line(double , double ) ;
    Line(double,double,double,double) ;
    void calculateFromEquation();
};

#endif // LINE_H
