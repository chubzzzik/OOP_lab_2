#pragma once

#include"Delivery.h"

#include<memory>

class DeliveryProxy:public Delivery{
    private:
    std::shared_ptr<Delivery> realDelivery_;


};