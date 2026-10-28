#pragma once

#include<string>
#include<memory>
#include<unordered_map>

class ProductType{
    private:
    std::string category_;
    int baseWeight_;
    double basePrice_;
    static std::unordered_map<std::string, std::shared_ptr<ProductType>> pool_;

    public:
    ProductType(const std::string& ctg, int w, double p);
    static std::shared_ptr<ProductType> getType(const std::string& category);
    int getBaseWeight() const;
    double getBasePrice() const;
};