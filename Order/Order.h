#pragma once

#include"Discount.h"
#include"Delivery.h"
#include"Product.h"
#include"OrderStatus.h"

#include<string>
#include<vector>

class Order{
    private:
    int id_;
    static int nextId_;
    std::string customer_;
    std::vector<std::shared_ptr<Product>> items_;
    OrderStatus status_;
    std::shared_ptr<Delivery> delivery_;
    std::vector<std::shared_ptr<Discount>> discounts_;
    double totalDiscount_;
    double bonusBalance_;

    public:
    Order(const std::string& customer, const OrderStatus& status);
    void addItem(const std::shared_ptr<Product>& item);
    void removeItem(const std::shared_ptr<Product>& item);
    int getTotalWeight() const;
    double getTotalPrice() const;
    void setStatus(const OrderStatus& newStatus);
    const std::vector<std::shared_ptr<Product>>& getItems()const;
    void applyDiscount(const std::shared_ptr<Discount>& discount);
    void setDelivery(const std::shared_ptr<Delivery>& newDelivery);
    void addDiscountAmount(double amount);
    void addBonusBalanceAmount(double amount);
};


Order& operator+(Order&, const Discount&);
Order& operator<<(Delivery&, Order&);