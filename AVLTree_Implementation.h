#include "AVLTree.h"

template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree(){
    root = nullptr;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::~AVLTree(){
    clear();
}

template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree(const AVLTree<Key,Info>& Tree){
    root = nullptr;
    if(Tree.root == nullptr)
        root = nullptr;
    else{
        insertAll(Tree.root);
    }
}

template <typename Key, typename Info>
AVLTree<Key, Info>& AVLTree<Key, Info>::operator=(const AVLTree<Key,Info>& Tree){
    if(root)
        clear();
    else if(Tree.root == nullptr)
        root = nullptr;
    else{
        insertAll(Tree.root);
    }
    return *this;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::insertAll(Node* node){
    if(!node)
        return;
    insertAll(node->left);
    insert(node->key, node->info);
    insertAll(node->right);
}

template <typename Key, typename Info>
AVLTree<Info, Key> AVLTree<Key, Info>::insertAllreverse(const AVLTree<Key,Info>& Tree) const{
    AVLTree<Info, Key> result;
//    result.insertAll(Tree.root);
    return result;
}

//template <typename Key, typename Info>
//void AVLTree<Key, Info>::insertAllreverse(Node* node){
//    if(!node)
//        return;
//    insertAll(node->left);
//    insert(node->info, node->key);
//    insertAll(node->right);
//}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::insert(Key key, Info info, Node* node){
    if(!node){
        node = new Node;
        node->key = key;
        node->info = info;
        node->height = 0;
        node->left = node->right = nullptr;
    }
    else if(key < node->key){
        node->left = insert(key, info, node->left);
        if(getHeight(node->left) - getHeight(node->right) == 2){
            if(key < node->left->key)
                node = RightRotation(node);
            else
                node = DoubleRightRotation(node);
        }
    }
    else if(key > node->key){
        node->right = insert(key, info, node->right);
        if(getHeight(node->right) - getHeight(node->left) == 2){
            if(key > node->right->key)
                node = LeftRotation(node);
            else
                node = DoubleLeftRotation(node);
        }
    }
    // if the key already exists, the data is being replaced
    else if (key == node->key){
        node->info = info;
    }

    node->height = max(getHeight(node->left), getHeight(node->right))+1;
    return node;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::RightRotation(Node* &node){
    if (node->left){
        Node* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        temp->height = max(getHeight(temp->left), node->height) + 1;
        return temp;
    }
    return node;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::LeftRotation(Node* &node){
    if (node->right){
        Node* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        temp->height = max(getHeight(temp->right), node->height) + 1;
        return temp;
    }
    return node;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::DoubleRightRotation(Node* &node){
    node->left = LeftRotation(node->left);
    return RightRotation(node);
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::DoubleLeftRotation(Node* &node){
    node->right = RightRotation(node->right);
    return LeftRotation(node);
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::remove(Key key, Node* node){
    Node* temp;

    // Element not found
    if(!node)
        return nullptr;

    // Searching for element
    else if(key < node->key)
        node->left = remove(key, node->left);
    else if(key > node->key)
        node->right = remove(key, node->right);

    // Element found
    // With 2 children
    else if(node->left && node->right)
    {
        temp = findMin(node->right);
        node->key = temp->key;
        node->info = temp->info;
        node->right = remove(node->key, node->right);
    }
    // With one or zero child
    else
    {
        temp = node;
        if(node->left == nullptr)
            node = node->right;
        else if(node->right == nullptr)
            node = node->left;
        delete temp;
    }
    if(node == nullptr)
        return node;

    node->height = max(getHeight(node->left), getHeight(node->right))+1;

    // If node is unbalanced
    // If left node is deleted, right case
    if(getHeight(node->left) - getHeight(node->right) == -2)
    {
        // right right case
        if(getHeight(node->right->right) - getHeight(node->right->left) == 1)
            return LeftRotation(node);
        // right left case
        else
            return DoubleLeftRotation(node);
    }
    // If right node is deleted, left case
    else if(getHeight(node->right) - getHeight(node->left) == 2)
    {
        // left left case
        if(getHeight(node->left->left) - getHeight(node->left->right) == 1){
            return RightRotation(node);
        }
        // left right case
        else
            return DoubleRightRotation(node);
    }
    return node;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::findMin(Node* node){
    if(!node)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::findMax(Node* node){
    if(!node)
        return nullptr;
    else if(node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}

template <typename Key, typename Info>
int AVLTree<Key, Info>::getHeight(Node* node){
    return (node == nullptr ? -1 : node->height);
}

template <typename Key, typename Info>
int AVLTree<Key, Info>::getBalance(Node* node){
    if(node == nullptr)
        return 0;
    else
        return getHeight(node->left) - getHeight(node->right);
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::insert(Key key, Info info){
    root = insert(key, info, root);
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::remove(Key key){
    root = remove(key, root);
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::print(Node* node){
    if(!node)
        return;
    print(node->left);
    cout << "Word: " << node->key << "\t\t\t\t\tOccurrence: " << node->info << endl;
    print(node->right);
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::printReverse(Node* node){
    if(!node)
        return;
    printReverse(node->right);
    cout << "Occurrence: " << node->key << "\t\t\t\t\tWord: " << node->info << endl;
    printReverse(node->left);
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::print(){
    print(root);
    cout << endl;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::printReverse(){
    printReverse(root);
    cout << endl;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::clear(Node* node){
    if(!node)
        return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::clear(){
    clear(root);
    root = nullptr;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::find(Key key, Node* node, Info& info){
    if (!node)
        return false;
    else if(node->key == key){
        info = node->info;
        return true;
    }
    else if(key < node->key)
        return find(key, node->left, info);
    else
        return find(key, node->right, info);
}

template <typename Key, typename Info>
Info AVLTree<Key, Info>::getInfo(Key key){
    Info dummy;
    find(key, root, dummy);
    return dummy;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::printInfo(Key key){
    Info dummy;
    if(find(key, root, dummy))
        cout << "Word: " << key << "\t\t\t\t\tOccurrence: " << dummy << endl;
    else
        cout << "There is no info with key: " << key << endl;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::find(Key key){
    Info dummy;
    return find(key, root, dummy);
}
