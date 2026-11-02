#include"IObservable.h"
#include"IObserver.h"

#include<algorithm>
#include<stdexcept>

void IObservable::subscribe(IObserver* observer){
    auto it = std::find(subs_.begin(), subs_.end(), observer);
    if(it == subs_.end()){
        subs_.push_back(observer);
    }
}

void IObservable::unsubscribe(IObserver* observer){
    auto it = std::find(subs_.begin(), subs_.end(), observer);
    if(it == subs_.end()){
        throw std::invalid_argument("IObservable::unsubscribe: observer not found");
    }
    subs_.erase(it);
}

void IObservable::notify(const OrderEvent& event){
    for(auto* sub : subs_){
        sub->onOrderEvent(event);
    }
}