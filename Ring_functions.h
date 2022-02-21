#include "Ring_Iterator.h"

template <typename Key, typename Info>
void split_pos (const Ring <Key, Info>& ring, int start_pos, bool direct, int count,
                Ring <Key, Info>& ring1, bool direct1, int len1,
                Ring <Key, Info>& ring2, bool direct2, int len2)
{
    if(start_pos < 0 || count < 0 || len1 < 0 || len2 < 0){
        cerr << "Error: Negative values" << endl;
        return;
    }
    auto it = ring.begin();
    while (start_pos-- > 0) {
        ++it;
    }
    while (count-- > 0) {
        for (int i = 0; i < len1; ++i) {
            if (direct1)
                ring1.insert(it.getKey(), it.getInfo());
            else
                ring1.ReverseInsert(it.getKey(), it.getInfo());
            if (direct)
                it++;
            else
                it--;
        }
        for (auto i = 0; i < len2; ++i) {
            if (direct2)
                ring2.insert(it.getKey(), it.getInfo());
            else
                ring2.ReverseInsert(it.getKey(), it.getInfo());
            if (direct)
                it++;
            else
                it--;
        }
    }
}

template <typename Key, typename Info>
void split_key (const Ring <Key, Info>& ring, const Key& start_key, int start_occ,
                bool direct, int count,
                Ring <Key, Info>& ring1, bool direct1, int len1,
                Ring <Key, Info>& ring2, bool direct2, int len2)
{
    if(start_occ < 1 || count < 0 || len1 < 0 || len2 < 0){
        cerr << "Error: Negative values" << endl;
        return;
    }
    else if(!ring.CheckIfKeyExists(start_key)){
        cerr << "Error: The Key doesn't exist in the given ring" << endl;
        return;
    }
    auto it = ring.begin();
    int x = 0;
    int start_pos;
    while(true){
        if(it.getKey() == start_key){
            if(start_occ == 1){
                start_pos = x % ring.getSize();
                break;
            }
            start_occ--;
        }
        it++;
        x++;
    }
    split_pos(ring, start_pos, direct, count, ring1, direct1, len1, ring2, direct2, len2);
}
