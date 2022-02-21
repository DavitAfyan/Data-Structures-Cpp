#include "Sequence_implementation.h"

template <typename Key, typename Info>
Sequence <Key, Info> produce (const Sequence <Key, Info>& seq1, int start1, int dl1,
                              const Sequence <Key, Info>& seq2, int start2, int dl2,
                              int limit){
    Sequence<Key, Info> product;
    
    Sequence<Key, Info> newSeq1(seq1);
    Sequence<Key, Info> newSeq2(seq2);
    
    if (limit <= 0 ||
        (dl1 <= 0 && dl2 <= 0) ||
        (start1 < 0 && start2 < 0) ||
        (start1 > newSeq1.getSize() && start2 > newSeq2.getSize()) ||
        (start1 > newSeq1.getSize() && start2 < 0) ||
        (start1 < 0 && start2 > newSeq2.getSize()))
        return product; // returning empty sequence
    else if (dl1 <= 0 || start1 > newSeq1.getSize() || start1 < 0){
        newSeq1.CutTheEnd(limit);
        return newSeq1;
    }
    else if (dl2 <= 0 || start2 > newSeq2.getSize() || start2 < 0){
        newSeq2.CutTheEnd(limit);
        return newSeq2;
    }

    newSeq1.CutTheSequence(start1, dl1);
    newSeq2.CutTheSequence(start2, dl2);

    product = (newSeq1 + newSeq2);
    
    product.CutTheEnd(limit);
    
    return product;
}

/* this function will remove the forst elements if the seqience
so that it will start form the given index */
template <typename Key, typename Info>
bool Sequence<Key, Info>::CutBeginning(int toIndex){
    if (!head || toIndex <= 0)
        return false;
    
    // I am starting to count the elements from 1
    while (toIndex != 1){
        removeAtBeggining();
        toIndex--;
    }
    return true;
}

/* this function will calculate the given lenght and cut off the last
elements if the lenght is smaller than the size of the sequence */
template <typename Key, typename Info>
bool Sequence<Key, Info>::CutTheEnd(int lenght){
    if (!head || lenght < 0)
        return false;
    
    int numberOfNodes;
    
    // calculating the number of nodes that have to be removed
    if (lenght > size)
        numberOfNodes = 0;
    else
        numberOfNodes = size - lenght;
    
    // it could be that the lenght is 0 so we should consider empty sequence
    /* I did this only to optimize the code a little bit so that it won't
     have to remove every single element form the end of the sequence*/
    if (numberOfNodes == size)
        clear();
    else{
        while (numberOfNodes != 0){
            removeAtEnd();
            numberOfNodes--;
        }
    }
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::CutTheSequence(int startIndex, int lenght){
//    if (CutBeginning(startIndex)){
//        CutTheEnd(lenght);
//        return true;
//    }
//    else{
//        if (CutTheEnd(lenght))
//            return true;
//        else
//            return false;
//    }
    CutBeginning(startIndex);
    CutTheEnd(lenght);
    return true;
}
