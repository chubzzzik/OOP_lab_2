#pragma once 

#include"Delivery.h"

class PostDelivery:public Delivery{
    public:
    double getCost(Order&)const override;
    std::string getEstimatedTime()const override;
    bool isAvailable(Order&) const override;
};