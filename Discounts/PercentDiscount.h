#pragma once

#include"Discount.h"

class PercentDiscount:public Discount{
    public:
    void apply(Order&) override;
};