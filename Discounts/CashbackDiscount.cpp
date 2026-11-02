#include"CashbackDiscount.h"
#include"Order.h"

void CashbackDiscount::apply(Order& order) const {
    double value = (order.getTotalPrice())*0.05;
    order.addBonusBalanceAmount(value);
}