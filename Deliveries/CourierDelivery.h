#pragma once 

#include"Delivery.h"

class CourierDelivery:public Delivery{
    public:
    double getCost(Order&)const override;
    std::string getEstimatedTime()const override;
    bool isAvailable(Order&) const override;
};