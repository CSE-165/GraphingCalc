#include "graphobject.h"

GraphObject::GraphObject()
{
    this-> xPoints = QVector<double>();
    this-> yPoints = QVector<double>();

}

void GraphObject::calculateFromEquation()
{
    //do nothing
}

GraphObject::GraphObject(QVector<double>& _xPoints, QVector<double>& _yPoints){
    this->xPoints = _xPoints;
    this->yPoints = _yPoints;
}

GraphObject::GraphObject(const GraphObject& object){
    this->xPoints = object.xPoints;
    this->yPoints = object.yPoints;
}
