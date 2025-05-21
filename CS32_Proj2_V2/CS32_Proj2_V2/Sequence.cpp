//
//  Sequence.cpp
//  CS32_Proj2
//
//  Created by Cait on 4/21/23.
//

#include "Sequence.h"
#include <iostream>


Sequence::Sequence()
{
    mSize = 0; //initialize size, should be empty
    head = new Node; //initialize head
    head->forward = head; //points to itself
    head->back = head; //points to itself
}

Sequence::Sequence(const Sequence& other) //copy constructor
{
    head = new Node; //initialize head
    head->forward = head; //points to itself
    head->back = head; //points to itself
    mSize = 0; 
    //placeholder for copying over values
    Node* placeholder = other.head->forward;
    for(; placeholder != other.head; placeholder = placeholder->forward)
    {
        insert(placeholder->mValue);
    }
}

Sequence::~Sequence()
{
    //this is our placeholder
    Node* placeholder = head;
    //we want to mark the end of the loop by making the next pointer of the last item to nullptr
    head->back->forward = nullptr;
    while(placeholder != nullptr)
    {
        Node* placeholder2 = placeholder->forward; //this holds onto the address of the next item
        delete placeholder; //deletes placeholder things
        placeholder = placeholder2; //we get back the address of the next item (from before we deleted it)
    }
}

Sequence& Sequence::operator=(const Sequence& rhs)
{
    //copied from lecture
//    if(this != &rhs)
//    {
//        Sequence placeholder(rhs);
//        swap(placeholder);
//    }
//    return *this;
    //clear lefthand side
    while(!empty())
    {
        erase(0);
    }
    //fill with values from right hand side
    for(int i = 0; i < rhs.mSize; i++)
    {
        ItemType placeholder;
        rhs.get(i,placeholder);
        insert(i, placeholder);
    }
    return *this;
}

bool Sequence::empty() const
{
    if(mSize == 0) //size == 0 when list is empty
    {
        return true;
    }
    return false;
}

int Sequence::size() const
{
    return mSize;
}

int Sequence::insert(int pos, const ItemType &value)
{
    if(pos < 0 || pos > size()) //if pos is greater than size, we can't traverse nodes that don't exist
    {
        return -1;
    }
    Node* addedVal = new Node;
    Node* iterator = head->forward; //this will hold our positions, get our pointers, and we will use later anyways
    for(int i = 0; i < pos; i++) //get to position to collect the pointers there
    {
        iterator = iterator->forward; //keeps on moving
    }
    
    addedVal->forward = iterator; //the next node from this new one is the current node iterator points to
    addedVal->back = iterator->back; //the back of our new node is the back of the iterator
    iterator->back->forward = addedVal; //the forward belonging to the node of iterator becomes the address of our new node
    iterator->back = addedVal; //the back of the iterator becomes our new node
    addedVal->mValue = value; //insert value
    mSize++;
    
    return pos;
}

int Sequence::insert(const ItemType &value)
{
    
    //find where value <= other items
    int p = 0;
    Node* iterator;
    for(iterator = head->forward; iterator != head && value > iterator->mValue; iterator = iterator->forward)
    {
        p++;
    }
    //now we have the address
    Node* addedVal = new Node;
    addedVal->mValue = value;
    //adjust pointers
    addedVal->back = iterator->back;
    iterator->back->forward = addedVal;
    addedVal->forward = iterator;
    iterator->back = addedVal;
    mSize++;
    return p;
}

bool Sequence::erase(int pos)
{
    if(pos < 0 || pos >= size()) //cannot be out of bounds of list
    {
        return false;
    }
    Node* iterator = head->forward;
    for(int i = 0; i < pos; i++)
    {
        iterator = iterator->forward;
    }
    iterator->back->forward = iterator->forward; //skips over the node in question
    iterator->forward->back = iterator->back; //skips over the node in question
    delete iterator;
    mSize--; //decrease size by 1
    return true;
}

int Sequence::remove(const ItemType &value)
{
    Node* iterator=head->forward;
    int pos; //tracks our position to give to erase function
    int tracker = 0; //tracks number of times erase is called
    for(pos = 0; pos < size(); pos++)
    {
        if(value == iterator->mValue)
        {
            Node* placeholder = iterator->forward;
            iterator->back->forward = iterator->forward; //skips over the node in question
            iterator->forward->back = iterator->back; //skips over the node in question
            tracker++;
            delete iterator;
            iterator = placeholder;
            mSize--;
        }
        else
        {
            iterator = iterator->forward;
        }
    }
    return tracker;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if((pos < 0) || (pos >= size())) //cannot be outside bounds
    {
        return false;
    }
    //make placeholder to get address at position
    Node* placeholder = head->forward;
    for(int i = 0; i < pos; i++)
    {
        placeholder = placeholder->forward;
    }
    value = placeholder->mValue; //we leave loop with address needed, make value == val @ address
    return true;
}
bool Sequence::set(int pos, const ItemType& value)
{
    if((pos < 0) || pos >= size())
    {
        return false;
    }
    else
    {
        Node* iterator = new Node;
        iterator = head->forward;
        for(int i = 0; i < pos; i++)
        {
            iterator = iterator->forward;
        }
        iterator->mValue = value;
        return true;
    }
}
int Sequence::find(const ItemType& value) const
{
    int pos = 0;
    Node* iterator = head->forward;
    for(; iterator != head; iterator = iterator->forward)
    {
        if(value == iterator->mValue)
        {
            return pos;
        }
        pos++;
    }
    return -1;
}
void Sequence::swap(Sequence& other)
{
    //trade lengths
    int placeholdSize = other.mSize;
    other.mSize = mSize;
    mSize = placeholdSize;
    
    //now switch heads (and this is it?)
    Node* placeholdPoint = other.head;
    other.head = head;
    head = placeholdPoint;
}
void Sequence::dump() const
{
    std::cerr << "forward:" << std::endl;
    for(Node* placeholder = head->forward; placeholder != head; placeholder = placeholder ->forward) //printing forward (normal direction)
    {
        std::cerr << placeholder->mValue << " ";
    }
    std::cerr << std::endl; //newline
    std::cerr << "backward:" << std::endl;
    for(Node* placeholder = head->back; placeholder != head; placeholder = placeholder->back) //prints backwards (not normal)
    {
        std::cerr << placeholder->mValue << " ";
    }
    std::cerr << std::endl; //newline
    std::cerr << "size of sequence is: " << mSize << std::endl << std::endl;
}
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if((seq2.empty()) || (seq1.size() < seq2.size()))
    {
        return -1;
    }
    //initialize 2 variables that will hold the value at whatever position in both seqs to compare after
    ItemType compare1;
    ItemType compare2;
    //hold where the sequence begins
    int seqPosition = -1;
    //determines what we return
    bool seqExists = false;
    for(int i = 0; i < seq1.size(); i++) //interate through seq1 (sad we can't use Node* interator = seq1.head->forward because it's private)
        //we run through seq1 and compare every item to the first item to seq2 because it would indicate whether or not there is potentially a loop
    {
        seq1.get(i,compare1); //gets value of i of seq 1...
        seq2.get(0, compare2); //gets 1st value of seq 2....
        if(compare1 == compare2) //sees if they are the same (could be a sign of a sequence)
        {
            seqExists = true;
            seqPosition = i; //saves sequence beginning if we find something that matches
            for(int seq2Pos = 0, seqBeginning = i; seq2Pos < seq2.size(); seq2Pos++, seqBeginning++) //now begin iterating from whatever value we marked as the beginning of a potential sequence
            {
                seq1.get(seqBeginning, compare1); //gets value of seq 1 at point
                seq2.get(seq2Pos, compare2); //gets value of seq 2
                if(compare1 != compare2)
                {
                    seqExists = false; //this portion of seq1 is NOT a sequence
                    break; //don't continue to iterate through loop if values are not equivalent before we iterate through entirety of seq 2
                    //we set seqExists to false and continue through main for loop that runs through seq1
                }
            }
            if(seqExists) //if we iterate through entirety of seq2, then the sequence exists and we return the position we marked
            {
                return seqPosition;
            }
        }
    }
    return -1; //otherwise, we return -1 if we've gone through all of seq1 with no sequence
}
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence placeholder;
    ItemType toAdd;
    for(int i = seq1.size()-1, j = 0; i >= 0; i--, j++)
    {
        seq1.get(i,toAdd);
        placeholder.insert(j,toAdd);
    }
    result = placeholder;
    ItemType toAdd2;
    for(int i = seq2.size()-1, j = placeholder.size(); i >= 0; i--, j++)
    {
        seq2.get(i,toAdd2);
        placeholder.insert(j,toAdd2);
    }
    result = placeholder;
    return;
}

