#include"ProductType.h"

#include<stdexcept>

std::unordered_map<std::string, std::shared_ptr<ProductType>> ProductType::pool_;

ProductType::ProductType(const std::string& ctg, int w, double p):category_(ctg),baseWeight_(w),basePrice_(p){
    if(w < 0){
        throw std::invalid_argument("ProductType: weight can't be negative");
    }
    if(p < 0.0){
        throw std::invalid_argument("ProductType: price cant't be negative");
    }
}

std::shared_ptr<ProductType> ProductType::getType(const std::string& category, int w, double p){
    auto type = pool_.find(category);
    if(type == pool_.end()){
        std::shared_ptr<ProductType> newType(new ProductType(category, w, p));
        pool_.emplace(category, newType);
        return newType;
    }
    else{
        return type->second; // первое поле - ключ, второе - значение
    }
    
}

int ProductType::getBaseWeight()const{
    return baseWeight_;
}