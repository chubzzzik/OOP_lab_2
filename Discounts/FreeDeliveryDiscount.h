#pragma once

#include"Discount.h"

class FreeDeliveryDiscount:public Discount{
    public:
    void apply(Order&) override;
};