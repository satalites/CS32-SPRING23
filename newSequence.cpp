//
//  newSequence.cpp
//  HW1
//
//  Created by Cait on 4/17/23.
//

#include "newSequence.h"
#include <string>

Sequence::Sequence() //empty
{
    mSequence = new ItemType[DEFAULT_MAX_ITEMS];
    mLimit = DEFAULT_MAX_ITEMS;
}

Sequence::Sequence(int size) //given size
{
    //what to do if int < 0?
    mSequence = new ItemType[size];
    mLimit = size;
    mSize = 0;
}

Sequence::Sequence(const Sequence& other) //copy constructor, from lecture sort of
{
    mSize = other.mSize;
    mLimit = other.mLimit;
    mSequence = new ItemType[mLimit];
    //fill w other sequence
    for(int i = 0; i < mSize; i++)
    {
        mSequence[i] = other.mSequence[i];
    }
}

Sequence& Sequence::operator=(Sequence &sq) //stolen from lecture!
{
    if(this != &sq)
    {
        Sequence placeholder(sq);
        swap(placeholder);
    }
    return *this;
}

Sequence::~Sequence()
{
    delete [] mSequence;
}

bool Sequence::empty() const
{
    if(mSize == 0)
    {
        return true;
    }
    return false;
}

int Sequence::size() const
{
    return mSize;
}

int Sequence::insert(int pos, const ItemType& value) //pretty much copy-pasted from original sequence
{
    // Insert value into the sequence so that it becomes the item at
    // position pos.  The original item at position pos and those that
    // follow it end up at positions one greater than they were at before.
    // Return pos if 0 <= pos <= size() and the value could be
    // inserted.  (It might not be, if the sequence has a fixed capacity,
    // e.g., because it's implemented using a fixed-size array.)  Otherwise,
    // leave the sequence unchanged and return -1.  Notice that
    // if pos is equal to size(), the value is inserted at the end.
    if((0 <= pos) && (pos <= size()) && (size() < mLimit))
    {
        if(size() == pos)
        {
            mSize++;
            mSequence[pos] = value;
            return pos;
        }
        else
        {
            for(int i = size(); i > pos; i--) //move everything up one space, i tried to do it starting from position but that needed 2(?) placeholder variables and it hurt my brain
            {
                mSequence[i] = mSequence[i-1];
            }
            mSequence[pos] = value; //then insert at position
            mSize++;
            return pos;
        }
    }
    return -1;
}

int Sequence::insert(const ItemType &value)
{
    // Let p be the smallest integer such that value <= the item at
    // position p in the sequence; if no such item exists (i.e.,
    // value > all items in the sequence), let p be size().  Insert
    // value into the sequence so that it becomes the item in position
    // p.  The original item in position p and those that follow it end
    // up at positions one greater than before.  Return p if the value
    // was actually inserted.  Return -1 if the value was not inserted
    // (perhaps because the sequence has a fixed capacity and is full).
    if(size() >= mLimit) //value won't be able to be inserted
    {
        return -1;
    }
    int p=0; //initialize int p before loop to save it
    for(int i = 0; i < size(); i++)
    {
        if(value <= mSequence[i])
        {
            p=i;
            insert(p, value);
            return p;
        }
    }
    //if whole loop is done and still not inserted, put at end
    p = size();
    insert(p, value);
    return p;
}

bool Sequence::erase(int pos)
{
    // If 0 <= pos < size(), remove the item at position pos from
    // the sequence (so that all items that followed that item end up at
    // positions one lower than they were at before), and return true.
    // Otherwise, leave the sequence unchanged and return false.
    if((0 <= pos) && (pos < size()))
    {
        for(int i = pos; i < size(); i++)
        {
            mSequence[i] = mSequence[i+1];
        }
        mSize--;
        return true;
    }
    return false;
}

int Sequence::remove(const ItemType &value)
{
    // Erase all items from the sequence that == value.  Return the
    // number of items removed (which will be 0 if no item == value).
    int num = 0;
    for(int i = 0; i < size(); i++)
    {
        if(mSequence[i] == value)
        {
            erase(i);
            i--;
            num++;
        }
    }
    return num;
}

bool Sequence::get(int pos, ItemType& value) const
{
    // If 0 <= pos < size(), copy into value the item in position pos
    // of the sequence and return true.  Otherwise, leave value unchanged
    // and return false.
    if((0 <= pos) && (pos < size()))
    {
        value = mSequence[pos];
        return true;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType &value)
{
    // If 0 <= pos < size(), replace the item at position pos in the
    // sequence with value and return true.  Otherwise, leave the sequence
    // unchanged and return false.
    if((0 <= pos) && (pos < size()))
    {
        mSequence[pos] = value;
        return true;
    }
    return false;
}

int Sequence::find(const ItemType& value) const
{
    // Let p be the smallest integer such that value == the item at
    // position p in the sequence; if no such item exists, let p be -1.
    // Return p.
    int p = -1;
    for(int i = 0; i < size(); i++)
    {
        if(mSequence[i] == value)
        {
            p = i;
            return p;
        }
    }
    return p;
}

void Sequence::swap(Sequence &other)
{
    // Exchange the contents of this sequence with the other one.
    //initialize variables
    ItemType* placeholdSequence;
    placeholdSequence = mSequence;
    int placeholdSize = mSize;
    int placeholdLimit = mLimit;
    
    //swap items
    mSequence = other.mSequence;
    other.mSequence = placeholdSequence;
    
    //swap size
    mSize = other.mSize;
    other.mSize = placeholdSize;
    
    //swap limits
    mLimit = other.mLimit;
    other.mLimit = placeholdLimit;
    
//    delete placeholdSequence;
}
