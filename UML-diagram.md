# UML-диаграмма архитектуры системы заказов и доставки

## Диаграмма классов

```mermaid
classDiagram
    class OrderManager {
        -vector~unique_ptr~Order~~ orders_
        -vector~string~ customers_
        -double turnover_
        -int maxActiveOrders_
        +createOrder(customer, items) unique_ptr~Order~
        +updateStatus() void
        +getTurnover() double
        +getCustomerCount() int
    }

    class Order {
        -int id
        -string customer
        -vector~Product~ items_
        -string status
        -Delivery delivery_
        -vector~Discount~ discounts_
        -double totalPrice
    }

    class Product {
        -int id
        -int quantity
        -double currentPrice
    }

    class ProductType {
        -string category
        -int baseWeight
        -double basePrice
        -unordered_map pool_$
    }

    class Delivery {
        <<interface>>
        +getCost(Order&) double
        +getEstimatedTime() string
        +isAvailable(Order&) bool
    }

    class CourierDelivery
    class PickupDelivery
    class PostDelivery

    class DeliveryProxy {
        -shared_ptr~Delivery~ realDelivery_
    }

    class Discount {
        <<interface>>
        +apply(Order&) void
    }

    class PercentDiscount
    class CashbackDiscount
    class FreeDeliveryDiscount
    class GiftDiscount

    OrderManager "1" *-- "0..*" Order : orders_
    Order "1" o-- "0..*" Product : items_
    Product "0..*" --> "1" ProductType : тип (Легковес)
    Order "1" --> "0..1" Delivery : delivery_
    Order "1" o-- "0..*" Discount : discounts_

    Delivery <|.. CourierDelivery
    Delivery <|.. PickupDelivery
    Delivery <|.. PostDelivery
    Delivery <|.. DeliveryProxy
    DeliveryProxy --> "1" Delivery : realDelivery_

    Discount <|.. PercentDiscount
    Discount <|.. CashbackDiscount
    Discount <|.. FreeDeliveryDiscount
    Discount <|.. GiftDiscount

    Delivery ..> Order : getCost, isAvailable
    Discount ..> Order : apply
```

## Описание связей

| Связь | Тип | Описание |
|---|---|---|
| `OrderManager` → `Order` | композиция | менеджер владеет заказами (`orders_`) и отвечает за их создание |
| `Order` → `Product` | агрегация | заказ содержит список товаров (`items_`) |
| `Product` → `ProductType` | ассоциация | много товаров одной категории ссылаются на один общий объект типа из статического пула (паттерн «Легковес») |
| `Order` → `Delivery` | ассоциация | у заказа один выбранный способ доставки (`delivery_`) |
| `Order` → `Discount` | агрегация | к заказу применяется список акций (`discounts_`) |
| `CourierDelivery`, `PickupDelivery`, `PostDelivery` → `Delivery` | реализация | конкретные способы доставки (паттерн «Стратегия») |
| `DeliveryProxy` → `Delivery` | реализация | заместитель сам является `Delivery` |
| `DeliveryProxy` → `Delivery` | ассоциация | заместитель хранит реальный способ доставки (`realDelivery_`) и делегирует ему вызовы (паттерн «Прокси») |
| `PercentDiscount`, `CashbackDiscount`, `FreeDeliveryDiscount`, `GiftDiscount` → `Discount` | реализация | конкретные акции (паттерн «Стратегия») |
| `Delivery` → `Order`, `Discount` → `Order` | зависимость | методы принимают заказ как параметр (`getCost`, `isAvailable`, `apply`) |

## Перегруженные операторы

Операторы объявлены как свободные функции вне классов и работают с `Order`:

- `Order& operator+(Order&, const Discount&)` — применить акцию к заказу;
- `Order& operator<<(Delivery&, Order&)` — назначить заказу способ доставки.
