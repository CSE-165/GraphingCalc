#include "line.h"
#include <iostream>

Line::Line()
{
    this->b = 0;
    this->m = 1;
    this->upperBound = 10;
    this->lowerBound = 0;
}

Line::Line(double slope, double yIntercept){
    this->m = slope;
    this->b = yIntercept;
    this->upperBound =100;
    this->lowerBound = -100;

}

Line::Line(double slope, double yIntercept, double lowerBound, double upperBound){
    this->m = slope;
    this->b = yIntercept;
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;
}

void Line::calculateFromEquation()
{
    //create all x points
    double tempLower = this->lowerBound;

    while(tempLower < this->upperBound){
        this->xPoints.push_back(tempLower+this->increments);
        tempLower += this->increments;

    }

    //calculate the y from the xPoints

    for (double x : this->xPoints){
        this->yPoints.push_back((this->m*x)+this->b);
    }
}
