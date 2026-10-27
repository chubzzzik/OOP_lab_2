#pragma once

#include"Order.h"

#include<vector>
#include<memory>
#include<string>

class OrderManager{
    private:
    std::vector<std::unique_ptr<Order>> orders_;
    std::vector<std::string> customers_;
    double turnover_;
    int maxActiveOrders_;

    public:
    std::unique_ptr<Order> createOrder(const std::string& customer, const std::vector<std::string>& items);
    void updateStatus();
    double getTurnover() const;
    int getCustomerCount() const;
};