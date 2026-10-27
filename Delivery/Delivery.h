#pragma once

#include<string>

class Order;

class Delivery{ 
    public:
    virtual double getCost(Order&)const;
    virtual std::string getEstimatedTime()const;
    virtual bool isAvailable(Order&) const;
};