#pragma once 

class Order;

class Discount {
    public:
    virtual void apply(Order&);
};