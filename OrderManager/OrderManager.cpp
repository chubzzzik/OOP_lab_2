#include"OrderManager.h"
#include"OrderEvent.h"
#include"OrderStatus.h"
#include"Order.h"

#include<iostream>
#include<algorithm>
#include<stdexcept>
#include<memory>
#include<string>

Order* OrderManager::createOrder(const std::string& customer, const std::string& region){
    int orderCounter = 0;
    for(auto& t : orders_){
        if(t->getCustomer() == customer && (t->getStatus() != OrderStatus::Delivered && t->getStatus() != OrderStatus::Cancelled)){
            orderCounter++;
        }

    }
    if(orderCounter >= maxActiveOrders_){
        throw std::runtime_error("У этого клиента уже " + std::to_string(maxActiveOrders_) +  " активных заказов");
    }
    auto order = std::make_unique<Order>(customer, OrderStatus::Pending, region);
    order->subscribe(this);
    Order* raw = order.get();
    orders_.push_back(std::move(order));
    
    activeOrders_++;

    auto newCustomer = std::find(customers_.begin(), customers_.end(), customer);
    if(newCustomer == customers_.end()){
        customers_.push_back(customer);
    }
    
    return raw;
}

void OrderManager::updateStatus(int orderId, OrderStatus newStatus){
    for(auto& t : orders_){
        if(t->getId() == orderId){
            t->setStatus(newStatus);
            return;
        }
    }
    std::cout << "[OrderManager] WARNING: заказ №" << orderId << " не найден" << "\n";
}

double OrderManager::getTurnover() const{
    return turnover_;
}

size_t OrderManager::getCustomerCount() const{
    return customers_.size();
}

void OrderManager::onOrderEvent(const OrderEvent& event){
    if(event.getNewStatus() == OrderStatus::Paid){
        for(const auto& t : orders_){
            if(t->getId() == event.getId()){
                turnover_ += t->getTotalPrice();
                std::cout << "[OrderManager] INFO: заказ №" << event.getId() << " оплачен, оборот = " << turnover_ << "\n"; 
                return; 
            }
        }
        std::cout << "[OrderManager] WARNING: событие Paid от неизвестного заказа №" << event.getId() << ", оборот не обновлён" << "\n";
    }

    else if(event.getNewStatus() == OrderStatus::Cancelled){
        if(activeOrders_ == 0){
            std::cout << "[OrderManager] WARNING: отмена при нулевом счётчике активных заказов — рассинхрон состояния" << "\n";
            return;
        }
        activeOrders_--;
        std::cout << "[OrderManager] INFO: заказ отменён, активных заказов: "<< activeOrders_ <<  "\n";
    }

    else if(event.getNewStatus() == OrderStatus::Delivered){
        if(activeOrders_ == 0){
            std::cout << "[OrderManager] WARNING: доставка при нулевом счётчике активных заказов — рассинхрон состояния" << "\n";
            return;
        }
        activeOrders_--;
        std::cout << "[OrderManager] INFO: заказ доставлен, активных заказов: "<< activeOrders_ <<  "\n";
    }
}