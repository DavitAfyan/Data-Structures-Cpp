#include "Sequence.h"

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(){
    head = nullptr;
    size = 0;
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence(){
    clear();
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info> &seq){
    Node *temp = seq.head;
    Node *current = head;
    Node *previous = nullptr;
    if (seq.head == nullptr){
        head = nullptr;
        size = 0;
    }
    else {
        Node *new_node = new Node;
        new_node->info = temp->info;
        new_node->key = temp->key;
        new_node->next = nullptr;
        current = new_node;
        head = current;
        temp = temp->next;
        previous = current;
        current = current->next;
        while (temp != nullptr){
            Node *new_node = new Node;
            new_node->info = temp->info;
            new_node->key = temp->key;
            new_node->next = nullptr;
            current = new_node;
            previous->next = current;
            temp = temp->next;
            previous = current;
            current = current->next;
        }
        size = seq.size;
    }
}

template <typename Key, typename Info>
Sequence<Key, Info> & Sequence<Key, Info>::operator=(const Sequence<Key, Info>& seq){
    if (head) {
        clear();
    }
    Node *temp = seq.head;
    Node *current = head;
    Node *previous = nullptr;
    if (seq.head == nullptr){
        head = nullptr;
        size = 0;
    }
    else {
        Node *new_node = new Node;
        new_node->info = temp->info;
        new_node->key = temp->key;
        new_node->next = nullptr;
        current = new_node;
        head = current;
        temp = temp->next;
        previous = current;
        current = current->next;
        while (temp != nullptr){
            Node *new_node = new Node;
            new_node->info = temp->info;
            new_node->key = temp->key;
            new_node->next = nullptr;
            current = new_node;
            previous->next = current;
            temp = temp->next;
            previous = current;
            current = current->next;
        }
        size = seq.size;
    }
    return *this;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::InsertAtBeginning(const Key& k, const Info& inf){
    Node *newNode;
    newNode = new Node();
    newNode->key = k;
    newNode->info = inf;
    newNode->next = head;
    head = newNode;
    size++;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::InsertAtEnd(const Key& k, const Info& inf){
    Node *newNode = new Node();
    newNode->key = k;
    newNode->info = inf;
    newNode->next = nullptr;
    
    if (!head)
        head = newNode;
    else{
        Node *current = head;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::InsertAfter(const Key& k, const Info& inf, const Key& where, int occurance){
    if (head == nullptr || occurance <= 0)
        return false;
    Node *current = head;
    while (current->next != nullptr){
        if (current->key == where){
            occurance--;
            if (occurance == 0){
                Node *newNode;
                newNode = new Node();
                newNode->key = k;
                newNode->info = inf;
                newNode->next = nullptr;
                
                Node *after = current->next;
                current->next = newNode;
                if(after != nullptr){
                    newNode->next = after;
                    return true;
                }
                size++;
                return true;
            }
        }
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::remove(const Key& k, int occurance){
    if (head == nullptr || occurance <= 0)
        return false;
    
    Node *current = head;
    Node *previous = nullptr;
    while (current != nullptr){
        if (current->key == k){
            if (occurance == 1){
                if (current == head) {
                    head = current->next;
                    delete current;
                }
                else{
                    previous->next = current->next;
                    delete current;
                }
                size--;
                return true;
            }
            else
                occurance--;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::removeAllWithKey(const Key& k){
    int x = 0;
    while (remove(k)){
        x++;
        continue;
    }
    if (x)
        return true;
    else
        return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::find (const Key& k, int occurance){
    if (head == nullptr || occurance <= 0)
        return false;
    
    Node *current = head;
    while (current != nullptr){
        if (current->key == k){
            if (occurance == 1)
                return true;
            else
                occurance--;
        }
        current = current->next;
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::find (Node *current, Node *previous, const Key& k, int occurance){
    if (head == nullptr || occurance <= 0)
        return false;
    
    current = head;
    current->next = nullptr;
    previous = nullptr;
    
    while (current != nullptr){
        if (current->key == k){
            if (occurance == 1)
                return true;
            else
                occurance--;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::get_Info(Info& result, Key& k, int occurance) {
    Node* current = head;
    Node* previous = nullptr;
    if (find(current, previous, k, occurance)){
        result = current->info;
        return true;
    }
    else
        return false;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::removeAtBeggining(){
    if (head){
        Node *newNode = head;
        head = head->next;
        delete newNode;
        size--;
    }
}

template <typename Key, typename Info>
void Sequence<Key, Info>::removeAtEnd(){
    if (head){
        Node *current = head;
        Node *previous = nullptr;
        while(current->next != nullptr){
            previous = current;
            current = current->next;
        }
        if (previous)
            previous->next = nullptr;
        delete current;
        size--;
    }
}

template <typename Key, typename Info>
void Sequence<Key, Info>::clear(){
    while (head){
        removeAtBeggining();
    }
}

template <typename Key, typename Info>
void Sequence<Key, Info>::print(){
    if (head){
        Node* node = head;
        for (int i = 0; i < size; i++){
            cout << "key: " << node->key << "\t info: " << node->info << endl;
            node = node->next;
        }
    }
    else{
        cout << "The sequence is empty" << endl;
    }
}

template <typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::operator+ (const Sequence<Key, Info>& seq) const {
    Sequence *result = new Sequence;
    Node *temp;
    temp = seq.head;
    if (seq.head == nullptr) {
        *result = *this;
    }
    else if (head == nullptr) {
        *result = seq;
    }
    else {
        *result = *this;
        while (temp != nullptr) {
            result->InsertAtEnd(temp->key, temp->info);
            temp=temp->next;
        }
    }
    return *result;
}
