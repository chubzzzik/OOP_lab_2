#pragma once

#include"Order.h"
#include"IObserver.h"

#include<vector>
#include<memory>
#include<string>

class OrderManager:public IObserver{
    private:
    std::vector<std::unique_ptr<Order>> orders_;
    std::vector<std::string> customers_;
    double turnover_ = 0.0;
    int maxActiveOrders_ = 5;
    int activeOrders_ = 0;

    public:
    Order* createOrder(const std::string& customer, const std::string& region);
    void updateStatus(int orderId, OrderStatus newStatus);
    double getTurnover() const;
    size_t getCustomerCount() const;
    void onOrderEvent(const OrderEvent& event) override;

    OrderManager() = default;
    OrderManager(const OrderManager&) = delete;
    OrderManager& operator=(const OrderManager&) = delete;
};