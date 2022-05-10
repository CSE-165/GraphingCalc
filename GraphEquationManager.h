#ifndef GRAPHEQUATIONMANAGER_H
#define GRAPHEQUATIONMANAGER_H

//includes
#include <QVector>
#include "graphobject.h"
#include "line.h"

//Manages the objects of a graph
class GraphEquationManager {


    //TODO: Linear
 public:
    QVector<GraphObject> list;
    GraphEquationManager();
    void addObject(GraphObject& object);
    void clearGraph();
private:


};
#endif // GRAPHEQUATIONMANAGER_H
