#include <iostream>
#include <string>
#include <fstream>
#include "AVLTree_Implementation.h"
using namespace std;

/* Function that takes text files name as input and outputs AVL Tree
 where every word and it's occurancy is listed in phonetical order*/
AVLTree <string, int> counter(const string& fileName){
    AVLTree<string, int> result;
    ifstream file;
    string filename = fileName;
    filename.append(".txt");
    file.open (filename);
    if (!file.is_open()){
        cout << "ERROR: file can't be opened" << endl;
        return result;
    }

    string word;
    while (file >> word)
    {
        // deleting the punctuation except the <'>
        for (auto c : word)
            if (ispunct(c) && c != '\'')
                word.erase(word.find_first_of(c));
        
        // converting capital letters to lower case letters
        for (int j=0; j < word.length(); j++)
            word[j] = tolower(word[j]);
        // inserting the words to data structure
        if(result.find(word))
            result.insert(word, result.getInfo(word) + 1);
        else
            result.insert(word, 1);
    }
    return result;
}

/* Function that takes AVL Tree as input (from previous function) and
 outputs the words by their occurance from high to low */
void listing(const AVLTree <string, int>& Tree){
    AVLTree<string, int> result = Tree;
    AVLTree<string, int>::Iterator it(result.getRoot());
    int x = 0;
    int size = 0;
    while(!it.IsEnd()){
        if(it.getInfo() > x)
            x = it.getInfo();
        it.next();
        size++;
    }
    
    bool isdeleted = false;
    while(size != 0){
        it.Begin(result.getRoot());
        while(!it.IsEnd()){
            if(it.current()->info == x /*&& result.find(it.current()->key)*/){
                cout << "Occurrence: " << it.current()->info << "\t\t\t\t\tWord: " << it.current()->key << endl;
                result.remove(it.current()->key);
                size--;
                isdeleted = true;
            }
            if(isdeleted){
                it.Begin(result.getRoot());
                isdeleted = false;
            }
            else
                it.next();
        }
        x--;
    }
}
