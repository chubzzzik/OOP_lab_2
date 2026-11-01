#pragma once

#include"IObserver.h"

#include<vector>

class OrderEvent;

class IObservable{
    private:
    std::vector<IObserver*> subs_;

    public:
    virtual ~IObservable() = default;
    void subscribe(IObserver*);
    void unsubscribe(IObserver*);
    void notify(const OrderEvent&);
};