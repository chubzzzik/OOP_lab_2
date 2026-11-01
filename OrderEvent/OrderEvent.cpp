#include"OrderEvent.h"

#include<ctime>
#include<string>

OrderEvent::OrderEvent(int id, OrderStatus oldSt, OrderStatus newSt):orderId_(id),oldStatus_(oldSt),newStatus_(newSt){
    std::time_t time = std::time(nullptr);
    timestamp_ = std::ctime(&time);
    timestamp_.pop_back();
}

int OrderEvent::getId()const{
    return orderId_;
}

OrderStatus OrderEvent::getOldStatus() const{
    return oldStatus_;
}

OrderStatus OrderEvent::getNewStatus() const{
    return newStatus_;
}

const std::string& OrderEvent::getTimeStamp() const{
    return timestamp_;
}