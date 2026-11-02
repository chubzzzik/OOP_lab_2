#include"GiftDiscount.h"
#include"Order.h"
#include"ProductType.h"
#include"Product.h"

#include<memory>

void GiftDiscount::apply(Order& order) const {
    auto giftType = ProductType::getType("бонусный подарок", 0, 0.0);
    auto gift = std::make_shared<Product>(1, 0.0, giftType);
    order.addItem(gift);
}