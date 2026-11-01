#pragma once

class OrderEvent;

class IObserver{
    public:
    virtual ~IObserver() = default;
    virtual void onOrderEvent(const OrderEvent&) = 0;
};