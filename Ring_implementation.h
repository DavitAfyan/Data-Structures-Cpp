#include "Ring.h"

template<typename Key, typename Info>
Ring<Key,Info>::Ring(){
    any = nullptr;
    size = 0;
}

template<typename Key, typename Info>
Ring<Key,Info>::Ring(const Ring<Key,Info>& x){
    if (any){
        clearAll();
    }
    size = 0;

    Node* temp = x.any;
    
    if(x.any == nullptr){
        any = nullptr;
    }
    else{
        do{
            insert(temp->key, temp->info);
            temp = temp->next;
        }while(temp != x.any);
    }
}

template<typename Key, typename Info>
Ring<Key,Info>::~Ring(){
    clearAll();
}

template<typename Key, typename Info>
bool Ring<Key,Info>::remove(const Key& key, int occurance){
    if (!any || occurance < 1){
        return false;
    }
    else{
        Node* current = any;
        do{
            if (current->key == key){
                if (occurance == 1){
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    size--;
                    return true;
                }
                occurance--;
            }
            current = current->next;
        }while(current != any);
    }
    return false;
}

template<typename Key, typename Info>
void Ring<Key,Info>::RemoveAny(){
    Node* current = any;
    any = any->next;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    size--;
}

template<typename Key, typename Info>
void Ring<Key,Info>::clearAll(){
    while(size != 0){
        RemoveAny();
    }
    any = nullptr;
    size = 0;
}

template<typename Key, typename Info>
void Ring<Key,Info>::ReverseInsert(const Key& key,const Info& info){
    Node* new_node = new Node;
    new_node->key = key;
    new_node->info = info;
    if(!any){
        any = new_node;
        new_node->next = any;
        new_node->prev = any;
    }
    else{
        new_node->next = any;
        any->prev->next = new_node;
        new_node->prev = any->prev;
        any->prev = new_node;
        any = new_node;
    }
    size++;
}

template<typename Key, typename Info>
void Ring<Key,Info>::insert(const Key& key,const Info& info){
    Node* new_node = new Node;
    new_node->key = key;
    new_node->info = info;
    if(!any){
        any = new_node;
        new_node->next = any;
        new_node->prev = any;
    }
    else{
        new_node->next = any;
        any->prev->next = new_node;
        new_node->prev = any->prev;
        any->prev = new_node;
    }
    size++;
}

template<typename Key, typename Info>
void Ring<Key,Info>::print(){
    if (!any){
        cout << "The Ring is empty" << endl;
    }
    else{
        Node* current = any;
        do{
            cout << "Key: " << current->key << "\t" << "Info: " << current->info << endl;
            current = current->next;
        }while(current != any);
        cout << endl;
    }
}

template<typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring<Key,Info>& x){
    if (any){
        clearAll();
    }
    size = 0;

    Node* temp = x.any;
    
    if(x.any == nullptr){
        any = nullptr;
    }
    else{
        do{
            insert(temp->key, temp->info);
            temp = temp->next;
        }while(temp != x.any);
    }
    return *this;
}

template<typename Key, typename Info>
bool Ring<Key,Info>::CheckIfKeyExists(const Key& key) const{
    Node* current = any;
    do{
        if(current->key == key)
            return true;
        current = current->next;
    }while(current != any);
    return false;
}
