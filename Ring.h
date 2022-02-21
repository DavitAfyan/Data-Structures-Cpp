#include <iostream>
using namespace std;

template <typename Key, typename Info>
class Ring{
    friend class Iterator;
private:
    struct Node{
        Key key;
        Info info;
        
        Node* prev;
        Node* next;
    };
    Node* any;
    int size;
public:
    class Iterator{
        friend class Ring<Key, Info>;
    private:
        Node* itr;
    public:
        
        // overloading the operators
        Iterator& operator++();
        Iterator& operator++(int);
        Iterator& operator--();
        Iterator& operator--(int);
        bool operator==(const Iterator& x);
        bool operator!=(const Iterator& x);
        Node& operator*()const;
        Iterator& operator+=(int x);
        Iterator& operator-=(int x);
        Iterator& operator=(const Info& info);
        Iterator& operator[](int index);
        friend ostream& operator<<(ostream &os, const Iterator &itr){
            os << "Key: " << itr.itr->key << "\t" << "Info: " << itr.itr->info;
            return os;
        }
        // we also should have some getter and setter methods
        Info getInfo() const {return itr->info;}
        Key getKey() const {return itr->key;}
        Iterator& setKey(const Key& key);
    };
    
    Ring();
    Ring(const Ring<Key,Info>& x);
    Ring& operator=(const Ring<Key,Info>& x);
    ~Ring();
    
    void ReverseInsert(const Key& key, const Info& info); // changes the "any" after insert to the new element
    void insert(const Key& key, const Info& info); // inserts at the end || before "any"
    bool remove(const Key& key, int occurance = 1); // removes with key and it's occurance
    void RemoveAny(); // deletes the element to which points "any"
    bool CheckIfKeyExists(const Key& key) const; // checks if there is element with given key in the ring
    
    Iterator begin(){
        Iterator* itr = new Iterator;
        itr->itr = any;
        return *itr;
    }
    
    Iterator begin() const{
        Iterator* itr = new Iterator;
        itr->itr = any;
        return *itr;
    }
    
    Iterator end(){
        Iterator* itr = new Iterator;
        itr->itr = any->prev;
        return *itr;
    }
    
    bool isEmpty(){return any;}
    int getSize() const {return size;}
    void print(); // prints all the elemenst in the ring
    void clearAll(); // clears all the elemenst in the ring
};

