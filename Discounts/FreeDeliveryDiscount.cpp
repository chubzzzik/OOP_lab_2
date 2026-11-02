#include"FreeDeliveryDiscount.h"
#include"Order.h"

void FreeDeliveryDiscount::apply(Order& order) const {
    order.setFreeDelivery();
}