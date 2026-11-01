#include"IObservable.h"
#include"IObserver.h"

#include<algorithm>
#include<stdexcept>

void IObservable::subscribe(IObserver* suber){
    auto it = std::find(subs_.begin(),subs_.end(),suber);
    if(it == subs_.end()){
        subs_.push_back(suber);
    }
}

void IObservable::unsubscribe(IObserver* suber){
    auto it = std::find(subs_.begin(),subs_.end(), suber);
    if(it == subs_.end()){
        throw std::invalid_argument("Can`t find this item");
    }
    else{
        subs_.erase(it);
    }
}

void IObservable::notify(const OrderEvent& event){
    for(auto* sub : subs_){
        sub->onOrderEvent(event);
    }
}