#pragma once

#include<string>
#include<memory>
#include<unordered_map>

class ProductType{
    private:
    std::string category;
    int baseWeight;
    double basePrice;
    static std::unordered_map<std::string, std::shared_ptr<ProductType>> pool_;
};