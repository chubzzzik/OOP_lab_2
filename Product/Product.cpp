#include"Product.h"

#include<stdexcept>
int Product::nextId_ = 1;

Product::Product(int quant, double currPrice, const std::shared_ptr<ProductType>& type):id_(nextId_),quantity_(quant),currentPrice_(currPrice),type_(type){
    if(!type){
        throw std::invalid_argument("Product: type is null");
    }
    if(quant <= 0){
        throw std::invalid_argument("Product: quantity must be positive");
    }
    if(currPrice < 0.0){
        throw std::invalid_argument("Product: price can't be negative");   
    }
    nextId_ += 1;
}

int Product::getWeight() const{
    return (type_->getBaseWeight())*quantity_;
}

double Product::getTotalPrice() const{
    return currentPrice_*quantity_;
}

void Product::changeQuantity(int newQuant){
    if(newQuant <= 0){
        throw std::invalid_argument("Product::changeQuantity: quantity must be positive");
    }
    else{
        quantity_ = newQuant;
    }
}