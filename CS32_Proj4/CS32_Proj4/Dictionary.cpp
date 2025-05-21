//
//  Dictionary.cpp
//  CS32_Proj4
//
//  Created by Cait on 6/4/23.
//

#include "Dictionary.h"

// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl(int maxBuckets);
    ~DictionaryImpl();
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
  private:
    struct Entry
    {
        Entry(string word, size_t key)
        {
            mWord = word;
            mKey = key;
            next = nullptr;
        }
        string mWord;
        size_t mKey;
        Entry* next;
    };
    Entry** hashTable; //holds pointers to our entries
    //originally used a vector of linked lists but i couldn't figure out how to mash together the syntax to make it do what i want
    size_t hashFunction(const string word) const;
    int max_Buckets;
};

size_t DictionaryImpl::hashFunction(const string word) const
{
    string wordSort = word;
    sort(wordSort.begin(), wordSort.end());
    
    hash<string> hashval;
    return ((hashval(wordSort))%max_Buckets);
}

DictionaryImpl::DictionaryImpl(int maxBuckets)
{
    max_Buckets = maxBuckets;
    hashTable = new Entry*[max_Buckets];
    for(int i = 0; i < maxBuckets; i++)
    {
        hashTable[i] = nullptr;
    }
}

DictionaryImpl::~DictionaryImpl()
{
    for (int i = 0; i < max_Buckets; i++)
    {
        Entry* pos = hashTable[i];
        while (pos != nullptr)
        {
            Entry* currentPos = pos;
            pos = pos->next;
            delete currentPos;
        }
    }
    delete [] hashTable;
}

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if(word.empty())
    {
        return;
    }
    else
    {
        //initialize new entry by getting key and constructing
        size_t key = hashFunction(word);
        Entry* newEntry = new Entry(word, key);
        //see if the position in dictionary is free. if it is, just make that position the pointer to the new entry
        if(hashTable[key] == nullptr)
        {
            hashTable[key] = newEntry;
            return;
        }
        else
        {
            Entry* current = hashTable[key];
            Entry* previous = current;
            while(current != nullptr)
            {
                previous = current;
                current = current->next;
            }
            if(current == nullptr)
            {
                previous->next = newEntry;
                return;
            }
        }
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if(callback == nullptr)
    {
        return;
    }
    if(letters.empty())
    {
        return;
    }
    removeNonLetters(letters);
    size_t pos = hashFunction(letters);
    string sortedLetters = letters;
    sort(sortedLetters.begin(), sortedLetters.end());
    Entry* posPtr = hashTable[pos];
    while (posPtr != nullptr)
    {
        string placehold = posPtr->mWord;
        sort(placehold.begin(),placehold.end());
        if(sortedLetters == placehold)
        {
            callback(posPtr->mWord);
        }
        //and then move onto next node til end of list
        posPtr = posPtr->next;
    }
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

  // Each successive call to this function generates the next permutation of the
  // characters in the parameter.  For example,
  //    string s = "eel";
  //    generateNextPermutation(s);  // now s == "ele"
  //    generateNextPermutation(s);  // now s == "lee"
  //    generateNextPermutation(s);  // now s == "eel"
  // You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}



