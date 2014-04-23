#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include "participant.h"

class Association
{
public:
    Association(Participant*,Participant*);
    ~Association();

    double GetCost();
    bool IsValide();
    void ComputeCost();
    Participant* GetDriver();
    Participant* GetPassenger();

private:
    Participant* _driver;
    Participant* _passenger;
    double _cost;

    double GetCostDistance();
    double GetCostTime();

};

#endif // ASSOCIATION_H
