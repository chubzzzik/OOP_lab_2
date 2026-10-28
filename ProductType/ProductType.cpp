#include"ProductType.h"

#include<stdexcept>

std::unordered_map<std::string, std::shared_ptr<ProductType>> ProductType::pool_;

ProductType::ProductType(const std::string& ctg, int w, double p):category_(ctg),baseWeight_(w),basePrice_(p){
    if(w <= 0){
        throw std::invalid_argument("Weight must be positive");
    }
    if(p <= 0.0){
        throw std::invalid_argument("Price must be positive");
    }
}

std::shared_ptr<ProductType> ProductType::getType(const std::string& category){
    auto type = pool_.find(category);
    if(type == pool_.end()){
        throw std::invalid_argument("This category doesn`t exist");
    }
    else{
        return type->second; // первое поле - ключ, второе - значение
    }
}

int ProductType::getBaseWeight() const{
    return baseWeight_;
}

double ProductType::getBasePrice() const{
    return basePrice_;
}