#pragma once

#include"Discount.h"

class GiftDiscount:public Discount{
    public:
    void apply(Order&) override;
};