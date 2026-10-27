#pragma once

#include<string>

class OrderEvent{
    private:
    int orderId;
    std::string oldStatus;
    std::string newStatus;
    std::string timestamp;
};