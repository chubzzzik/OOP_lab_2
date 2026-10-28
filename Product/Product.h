#pragma once

#include"ProductType.h"

#include<memory>

class Product{
    private:
    static int nextId_;
    int id_;
    int quantity_;
    double currentPrice_;
    std::shared_ptr<ProductType> type_;

    public:
    Product(int quant, double currPrice, const std::shared_ptr<ProductType>& type);
    int getWeight() const;
    double getTotalPrice() const;
    void changeQuantity(int newQuant);
};