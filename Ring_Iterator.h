#include "Ring_implementation.h"

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator& Ring<Key, Info>::Iterator::operator++(){
    itr = itr->next;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator& Ring<Key, Info>::Iterator::operator++(int){
    itr = itr->next;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator& Ring<Key, Info>::Iterator::operator--(){
    itr = itr->prev;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator& Ring<Key, Info>::Iterator::operator--(int){
    itr = itr->prev;
    return *this;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::Iterator::operator==(const Iterator& x){
    return itr == x.itr;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::Iterator::operator!=(const Iterator& x){
    return itr != x.itr;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Node& Ring<Key, Info>::Iterator::operator*()const{
    return *itr;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator& Ring<Key, Info>::Iterator::operator+=(int x){
    for(int i=0; i<x; i++){
        itr = itr->next;
    }
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator& Ring<Key, Info>::Iterator::operator-=(int x){
    for(int i=0; i<x ;i++){
        itr = itr->prev;
    }
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator& Ring<Key, Info>::Iterator::operator=(const Info& info){
    itr->info = info;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator& Ring<Key, Info>::Iterator::setKey(const Key& key){
    itr->key = key;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator& Ring<Key, Info>::Iterator::operator[](int index){
    Iterator* temp = new Iterator;
    *temp = *this;
    return (*temp += index);
}
