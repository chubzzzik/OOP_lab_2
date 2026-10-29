#include"Order.h"

#include<algorithm>
#include<stdexcept>

int Order::nextId_ = 1;

Order::Order(const std::string& customer, const OrderStatus& status):id_(nextId_),customer_(customer),status_(status),totalDiscount_(0),bonusBalance_(0){
    nextId_ += 1;
}

void Order::addItem(const std::shared_ptr<Product>& item){
    if(item == nullptr){
        throw std::invalid_argument("This item doesn`t exist");
    }
    items_.push_back(item);
}

void Order::removeItem(const std::shared_ptr<Product>& item){
    auto it = std::find(items_.begin(),items_.end(), item);
    if(it == items_.end()){
        throw std::invalid_argument("Can`t find this item");
    }
    else{
        items_.erase(it);
    }
}

int Order::getTotalWeight() const{
    int total = 0;
    for(auto t : items_){
        total += t->getWeight();
    }
    return total;
}

double Order::getTotalPrice() const{
    double total = 0;
    for(auto t : items_){
        total += t->getTotalPrice();
    }
    return total - totalDiscount_;
}

void Order::setStatus(const OrderStatus& newStatus){
    status_ = newStatus;
}

const std::vector<std::shared_ptr<Product>>& Order::getItems()const{
    return items_;
}

void Order::applyDiscount(const std::shared_ptr<Discount>& discount){
    if(discount == nullptr){
        throw std::invalid_argument("This discount doesn`t exist");
    }
    discounts_.push_back(discount);
}

void Order::setDelivery(const std::shared_ptr<Delivery>& newDelivery){
    if(newDelivery == nullptr){
        throw std::invalid_argument("This delivery doesn`t exist");
    }
    delivery_ = newDelivery;
}

void Order::addDiscountAmount(double amount){
    if(amount<0){
        throw std::invalid_argument("Discount can`t be negative");
    }
    else{
        totalDiscount_ += amount;
    }
}

void Order::addBonusBalanceAmount(double amount){
    if(amount < 0){
        throw std::invalid_argument("Amount can`t be negative");
    }
    else{
        bonusBalance_ += amount;
    }
}