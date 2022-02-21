#include <iostream>
using namespace std;

template <typename Key, typename Info>
class AVLTree{
private:
    struct Node{
        Key key;
        Info info;
        Node* left;
        Node* right;
        int height;
    };
    Node* root;
    
    // helping methods
    Node* insert(Key key, Info info, Node* node);
    Node* RightRotation(Node* &node);
    Node* LeftRotation(Node* &node);
    Node* DoubleRightRotation(Node* &node);
    Node* DoubleLeftRotation(Node* &node);
    Node* remove(Key key, Node* node);
    
    Node* findMin(Node* node); // method to find the inorder predecessor
    Node* findMax(Node* node); // method to find the inorder successor
    
    int getHeight(Node* node);
    int getBalance(Node* node);
    void print(Node* node);
    void printReverse(Node* node);
    void clear(Node* node);
    bool find(Key key, Node* node, Info& info);
    void insertAll(Node* node);
public:
    class Iterator{
        friend class AVLTree<Key, Info>;
    private:
        stack<Node*> it;
    public:
        void next(){
            Node* current = it.top()->right;
            it.pop();
            while (current != NULL)
                it.push(current), current = current->left;
        }
        bool IsEnd(){
            return !(it.size());
        }
        bool hasNext() {
             return !it.empty();
        }
        Node* current(){
            return it.top();
        }
        Iterator(Node* root){
            // Initializing stack
            Node* current = root;
            while (current != NULL)
                it.push(current), current = current->left;
        }
        void Begin(Node* root){
            while (!it.empty()) {
                it.pop();
            }
            Node* current = root;
            while (current != NULL)
                it.push(current), current = current->left;
        }
        Key getKey(){return current()->key;};
        Info getInfo(){return current()->info;};
    };
    AVLTree();
    ~AVLTree();
    AVLTree(const AVLTree<Key,Info>& Tree);
    AVLTree& operator=(const AVLTree<Key,Info>& Tree);
    
    Node* getRoot() const {return this->root;};
    
    AVLTree<Info,Key> insertAllreverse(const AVLTree<Key,Info>& Tree) const;
    void insert(Key key, Info info);
    void remove(Key key);
    void print(); // printing the tree
    void printReverse(); // printing the tree reverse
    void clear(); // deleting the whole tree
    Info getInfo(Key key); // method that returns Info
    void printInfo(Key key); // printing Info by it's key
    bool find(Key key); // finding Info by it's key
};
