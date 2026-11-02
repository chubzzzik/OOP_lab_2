#pragma once

#include<string>

enum class OrderStatus{Pending, Paid, Shipped, Delivered, Cancelled};

std::string statusToString(OrderStatus status);