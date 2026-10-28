#include"Product.h"

#include<stdexcept>
int Product::nextId_ = 1;

Product::Product(int quant, double currPrice, std::shared_ptr<ProductType> type):id_(nextId_),quantity_(quant),currentPrice_(currPrice),type_(type){
    nextId_ += 1;
    if(!type){
        throw std::invalid_argument("This type doesn`t exist");
    }
    if(quant <= 0){
        throw std::invalid_argument("Quantity must be positiv");
    }
    if(currPrice <= 0.0){
        throw std::invalid_argument("Price must be positive");   
    }

}

int Product::getWeight() const{
    return (type_->getBaseWeight())*quantity_;
}

double Product::getTotalPrice() const{
    return (type_->getBasePrice())*quantity_;
}

void Product::changeQuantity(int newQuant){
    if(newQuant < 0){
        throw std::invalid_argument("Quantity can`t be negative");
    }
    else{
        quantity_ = newQuant;
    }
}