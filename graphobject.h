#ifndef GRAPHOBJECT_H
#define GRAPHOBJECT_H
#include <QVector>

//a base obbject that describes any type of graph
class GraphObject
{
public:
    //vars
    QVector<double> xPoints;
    QVector<double> yPoints;

    //constructors
    GraphObject();
    GraphObject(QVector<double>&, QVector<double>&);
    GraphObject(const GraphObject&);

    //templates
    virtual void calculateFromEquation();
private:

};

#endif // GRAPHOBJECT_H
