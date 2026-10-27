#pragma once

#include"Discount.h"

class CashbackDiscount:public Discount{
    public:
    void apply(Order&) override;
};