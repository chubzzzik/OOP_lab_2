#include"PercentDiscount.h"
#include"Order.h"

void PercentDiscount::apply(Order& order){
    double value = (order.getTotalPrice())*0.1;
    order.addDiscountAmount(value);
}