#pragma once

#include"OrderStatus.h"

#include<string>

class OrderEvent{
    private:
    int orderId_;
    OrderStatus oldStatus_;
    OrderStatus newStatus_;
    std::string timestamp_;
    
    public:
    OrderEvent(int id, OrderStatus oldSt, OrderStatus newSt);
    int getId() const;
    OrderStatus getOldStatus() const;
    OrderStatus getNewStatus() const;
    const std::string& getTimeStamp() const;
};