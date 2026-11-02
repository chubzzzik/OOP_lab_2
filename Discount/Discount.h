#pragma once 

class Order;

class Discount {
    public:
    virtual ~Discount() = default;
    virtual void apply(Order&) const = 0;
};