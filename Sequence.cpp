#include <iostream>
using namespace std;

template <typename Key, typename Info>
class Sequence {
    struct Node {
        Key key;
        Info info;
        Node *next;
    };
    Node *head;
    int size;
    
    bool find(Node *current, Node *previous, const Key& k, int occurance = 1);
    void removeAtBeggining();
    void removeAtEnd();
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence<Key, Info>& seq);
    Sequence<Key, Info>& operator=(const Sequence<Key, Info>& seq);
    Sequence<Key, Info> operator+ (const Sequence<Key, Info>& seq) const;
    
    void InsertAtBeginning(const Key& k, const Info& inf);
    void InsertAtEnd(const Key& k, const Info& inf);
    bool InsertAfter(const Key& k, const Info& inf, const Key& where, int occurance = 1);
    bool remove(const Key& k, int occurance = 1);
    bool removeAllWithKey(const Key& k);
    bool find(const Key& k, int occurance = 1);
    void clear();
    void print();
    int getSize(){return size;}
//    bool find(Node *current, int index = 1);
    
    // we need these to methods for produce function
    bool CutBeginning(int toIndex);
    bool CutTheEnd(int length);
    bool CutTheSequence(int startIndex, int lenght);
    
    bool get_Info(Info& result, Key& k, int occurance = 1);
    void set_Info(const Key& k, Info& inf);
    Info get_Info(const Key& k, int occurance = 1);
};
