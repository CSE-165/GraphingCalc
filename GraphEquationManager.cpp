#ifndef GRAPHEQUATIONMANAGER_CPP
#define GRAPHEQUATIONMANAGER_CPP
#include <QVector>
#include "GraphEquationManager.h"
#include "graphobject.h"




#endif // GRAPHEQUATIONMANAGER_CPP





GraphEquationManager::GraphEquationManager()
{
    list = QVector<GraphObject>();
}

void GraphEquationManager::addObject(GraphObject &object)
{
    this->list.push_back(object);
}

void GraphEquationManager::clearGraph()
{
    this->list.clear();
}
