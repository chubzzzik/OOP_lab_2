#pragma once

#include<string>

class Order;

class Delivery{ 
    public:
    virtual double getCost(const Order&) const = 0;
    virtual std::string getEstimatedTime() const = 0;
    virtual bool isAvailable(const Order&) const = 0;
};