#include"OrderManager.h"
#include"Order.h"
#include"ProductType.h"
#include"PercentDiscount.h"
#include"CashbackDiscount.h"
#include"FreeDeliveryDiscount.h"
#include"GiftDiscount.h"
#include"CourierDelivery.h"
#include"PickupDelivery.h"
#include"PostDelivery.h"
#include"DeliveryProxy.h"

#include<iostream>
#include<memory>
#include<cstdlib>
#include<limits>
#include<stdexcept>

void clearScreen(){
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void printMainMenu(){
    std::cout << "==============================\n";
    std::cout << "   ДЕМОНСТРАЦИОННЫЕ СЦЕНАРИИ\n";
    std::cout << "==============================\n";
    std::cout << "   1. Создание заказа через OrderManager, добавление товаров, применение процентной скидки через order + discount\n";
    std::cout << "   2. Выбор способа доставки через delivery << order, проверка доступности через DeliveryProxy\n";
    std::cout << "   3. Смена статуса заказа, уведомление OrderManager через Observer, обновление оборота\n";
    std::cout << "   4. Применение нескольких скидок к одному заказу, проверка итоговой цены\n";
    std::cout << "   5. Отмена заказа, освобождение лимита активных заказов, обновление статистики клиентов\n";
    std::cout << "------------------------------\n";
    std::cout << "   0. Выход\n";
    std::cout << "==============================\n";
    std::cout << "Ваш выбор: ";
}

void waitForEnter(){
    std::cout << "\nНажмите Enter, чтобы продолжить...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void scenario1();
void scenario2();
void scenario3();
void scenario4();
void scenario5();

int main(){
    std::string status;

    while(true){
        clearScreen();
        if(!status.empty()){
            std::cout << status << "\n\n";
            status.clear();
        }
        printMainMenu();

        int choice;
        if(!(std::cin >> choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            status = "Введите число от 0 до 5";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(choice){
            case 0: return 0;
            case 1: clearScreen(); scenario1(); waitForEnter(); break;
            case 2: clearScreen(); scenario2(); waitForEnter(); break;
            case 3: clearScreen(); scenario3(); waitForEnter(); break;
            case 4: clearScreen(); scenario4(); waitForEnter(); break;
            case 5: clearScreen(); scenario5(); waitForEnter(); break;
            default: status = "Нет такого пункта";
        }
    }
}

// Сценарий 1: создание заказа, добавление товаров, процентная скидка через order + discount
void scenario1(){
    OrderManager manager;
    PercentDiscount percentDiscount;
    Order* order = manager.createOrder("Сёма Бакин","Irkutsk");
    auto item1 = std::make_shared<Product>(1, 267.0, ProductType::getType("хачапури", 1, 267.0));
    auto item2 = std::make_shared<Product>(20, 30000.0, ProductType::getType("компик", 20, 30000.0));
    order->addItem(item1);
    order->addItem(item2);
    std::cout << order->getTotalPrice() << " (цена до скидки)" << "\n";
    *order + percentDiscount;
    std::cout << order->getTotalPrice() << " (цена после скидки в 10%)" << "\n";
}

// Вспомогательная функция сценария 2: создаёт доставку по выбору пользователя
std::shared_ptr<Delivery> createDeliveryByChoice(int choice){
    switch(choice){
        case 1: return std::make_shared<CourierDelivery>();
        case 2: return std::make_shared<PickupDelivery>();
        case 3: return std::make_shared<PostDelivery>();
        default: return nullptr;
    }
}

// Сценарий 2: выбор доставки через delivery << order, проверка доступности через DeliveryProxy
void scenario2(){
    OrderManager manager;
    Order* order = manager.createOrder("Сёма Бакин", "Irkutsk");
    // 15 кг: курьер (до 20 кг) пропустит, почта (до 10 кг) — откажет
    order->addItem(std::make_shared<Product>(3, 2000.0, ProductType::getType("Гантеля", 5, 2000.0)));
    std::cout << *order;

    while(true){
        std::cout << "\nВыберите способ доставки:\n";
        std::cout << "  1. Курьер (500 руб., 1-2 дня, до 20 кг)\n";
        std::cout << "  2. Самовывоз (бесплатно, 1-3 дня, без ограничений)\n";
        std::cout << "  3. Почта (200 руб., 5-10 дней, до 10 кг)\n";
        std::cout << "Ваш выбор: ";

        int choice;
        if(!(std::cin >> choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите число от 1 до 3\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        auto delivery = createDeliveryByChoice(choice);
        if(delivery == nullptr){
            std::cout << "Нет такого способа доставки\n";
            continue;
        }

        auto proxy = std::make_shared<DeliveryProxy>(delivery, "Irkutsk");
        if(proxy->isAvailable(*order)){
            *proxy << *order; // оператор назначает доставку заказу
            std::cout << "\nДоставка назначена. Ориентировочное время: " << proxy->getEstimatedTime() << "\n";
            std::cout << *order; // цена выросла на стоимость доставки
            break;
        }
        std::cout << "Этот способ недоступен для вашего заказа, выберите другой\n";
    }
}

// Сценарий 3: смена статуса, уведомление OrderManager через Observer, обновление оборота
void scenario3(){
    OrderManager manager;
    Order* order = manager.createOrder("Сёма Бакин", "Irkutsk");
    order->addItem(std::make_shared<Product>(2, 1500.0, ProductType::getType("Книга", 1, 1500.0)));

    std::cout << "Оборот до оплаты: " << manager.getTurnover() << "\n\n";
    manager.updateStatus(order->getId(), OrderStatus::Paid); // Observer сам обновит оборот
    std::cout << "\nОборот после оплаты: " << manager.getTurnover() << "\n";

    manager.updateStatus(order->getId(), OrderStatus::Shipped);
    manager.updateStatus(order->getId(), OrderStatus::Delivered); // слот активного заказа освободится
}

// Сценарий 4: применение нескольких скидок к одному заказу, проверка итоговой цены
void scenario4(){
    OrderManager manager;
    Order* order = manager.createOrder("Сёма Бакин", "Irkutsk");
    order->addItem(std::make_shared<Product>(2, 5000.0, ProductType::getType("Наушники", 1, 5000.0)));

    auto courier = std::make_shared<CourierDelivery>();
    *courier << *order;
    std::cout << "Товары + доставка: " << order->getTotalPrice() << "\n"; // 10000 + 500

    PercentDiscount percent;
    CashbackDiscount cashback;
    FreeDeliveryDiscount freeDelivery;
    GiftDiscount gift;

    *order + percent;
    std::cout << "После скидки 10%: " << order->getTotalPrice() << "\n";

    *order + freeDelivery;
    std::cout << "После бесплатной доставки: " << order->getTotalPrice() << "\n";

    *order + cashback; // 5% уйдёт на бонусный счёт (цену не меняет)
    std::cout << "После кешбэка (цена та же, бонусы начислены): " << order->getTotalPrice() << "\n";

    *order + gift; // бесплатный товар в заказ
    std::cout << "Товаров в заказе после подарка: " << order->getItems().size() << "\n";
    std::cout << "Итоговая цена: " << order->getTotalPrice() << "\n";
}

// Сценарий 5: отмена заказа, освобождение лимита активных заказов, обновление статистики клиентов
void scenario5(){
    OrderManager manager;

    // Забиваем лимит: 5 активных заказов одного клиента
    Order* first = nullptr;
    for(int i = 0; i < 5; i++){
        Order* created = manager.createOrder("Сёма Бакин", "Irkutsk");
        if(first == nullptr){
            first = created;
        }
    }
    std::cout << "Создано 5 активных заказов. Клиентов: " << manager.getCustomerCount() << "\n";

    // Шестой должен упасть по лимиту
    try{
        manager.createOrder("Сёма Бакин", "Irkutsk");
        std::cout << "ОШИБКА ДЕМО: лимит не сработал\n";
    }
    catch(const std::exception& e){
        std::cout << "Лимит сработал: " << e.what() << "\n";
    }

    // Отменяем первый заказ — слот освобождается (Observer уменьшит счётчик)
    manager.updateStatus(first->getId(), OrderStatus::Cancelled);

    // Теперь создание снова возможно
    try{
        Order* order = manager.createOrder("Сёма Бакин", "Irkutsk");
        std::cout << "После отмены заказ создан: id = " << order->getId() << "\n";
    }
    catch(const std::exception& e){
        std::cout << "ОШИБКА ДЕМО: после отмены лимит не освободился: " << e.what() << "\n";
    }
}