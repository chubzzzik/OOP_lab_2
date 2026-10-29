#pragma once 

#include"Delivery.h"

class PickupDelivery:public Delivery{
    public:
    double getCost(const Order&) const override;
    std::string getEstimatedTime() const override;
    bool isAvailable(const Order&) const override;
};