#pragma once 

class Order;

class Discount {
    public:
    virtual ~Discount() = default;
    virtual void apply(Order&) = 0;
};