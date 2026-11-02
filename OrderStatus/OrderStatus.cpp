#include"OrderStatus.h"

#include<string>

std::string statusToString(OrderStatus status){
    switch (status)
    {
    case OrderStatus::Cancelled:
        return "Cancelled";
    case OrderStatus::Delivered:
        return "Delivered";
    case OrderStatus::Paid:
        return "Paid";
    case OrderStatus::Pending:
        return "Pending";
    case OrderStatus::Shipped:
        return "Shipped";
    default: return "Wrong status";
    }
}
