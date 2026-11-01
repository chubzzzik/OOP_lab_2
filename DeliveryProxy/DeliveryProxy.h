#pragma once

#include"Delivery.h"

#include<memory>

class DeliveryProxy:public Delivery{
    private:
    std::shared_ptr<Delivery> realDelivery_;
    std::string availableRegion_;
    mutable int cachedWeight_ = -1; // вес не бывает отрицательным
    mutable double cachedPrice_ = -1.0; // такая же логика

    public:
    DeliveryProxy(const std::shared_ptr<Delivery>& delivery, const std::string& reg);
    double getCost(const Order& order) const override;
    std::string getEstimatedTime() const override;
    bool isAvailable(const Order&) const override;
};