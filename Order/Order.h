#pragma once

#include"Discount.h"
#include"Delivery.h"

#include<string>
#include<vector>

class Order{
    private:
    int id;
    std::string customer;
    std::vector<std::string> items_;
    std::string status;
    std::string delivery_;
    std::vector<std::string> discounts_;
    double totalPrice;

};


Order& operator+(Order&, const Discount&);
Order& operator<<(Delivery&, Order&);