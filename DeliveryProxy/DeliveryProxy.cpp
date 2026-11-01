#include"DeliveryProxy.h"
#include"Order.h"

#include<memory>
#include<stdexcept>
#include<iostream>

constexpr int kgMaxDeliveryWeight = 1500;

DeliveryProxy::DeliveryProxy(const std::shared_ptr<Delivery>& delivery, const std::string& reg):availableRegion_(reg){
    if(delivery == nullptr){
        throw std::invalid_argument("DeliveryProxy: real delivery must not be null");
    }
    realDelivery_ = delivery;
}

double DeliveryProxy::getCost(const Order& order) const{
    int input = order.getTotalWeight();
    std::cout << "[DeliveryProxy] getCost: запрос для заказа, вес = " << input << "\n";
    double out;
    if(input == cachedWeight_){
        out = cachedPrice_;
        std::cout << "[DeliveryProxy] getCost: cache hit, из кеша = " << out << "\n";
    }
    else{
        out = realDelivery_->getCost(order);
        std::cout << "[DeliveryProxy] getCost: cache miss, делегировано = " << out << "\n";
        cachedWeight_ = input;
        cachedPrice_ = out;
    }
    return out;
}

std::string DeliveryProxy::getEstimatedTime() const{
    return realDelivery_->getEstimatedTime();
}

bool DeliveryProxy::isAvailable(const Order& order) const{
    int weight = order.getTotalWeight();
    std::cout << "[DeliveryProxy] isAvailable: запрос для заказа, вес = " << weight << "\n";
    if(weight >= kgMaxDeliveryWeight){
        std::cout << "[DeliveryProxy] isAvailable: отказано - превышен максимальный вес" << "\n";
        return false;
    }
    if(order.getRegion() != availableRegion_){
        std::cout << "[DeliveryProxy] isAvailable: отказано - недоступный регион доставки" << "\n";
        return false;
    }
    std::cout << "[DeliveryProxy] isAvailable: делегировано, доставка доступна" << "\n";
    return realDelivery_->isAvailable(order);
}