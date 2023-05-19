//
//  RainfallList.cpp
//  HW1
//
//  Created by Cait on 4/17/23.
//

#include "RainfallList.h"
#include "Sequence.h"
#include <limits>

RainfallList::RainfallList():rf_sequence()
{
    // Create an empty rainfall list.
    //empty
}

bool RainfallList::add(unsigned long rainfall)
{
    // If the rainfall is valid (a value from 0 to 400) and the rainfall list
    // has room for it, add it to the rainfall list and return true.
    // Otherwise, leave the rainfall list unchanged and return false.
    if((0 <= rainfall) && (400 >= rainfall))
    {
        rf_sequence.insert(rainfall);
        return true;
    }
    return false;
}

bool RainfallList::remove(unsigned long rainfall)
{
    // Remove one instance of the specified rainfall from the rainfall list.
    // Return true if a rainfall was removed; otherwise false.
    bool success = rf_sequence.remove(rainfall);
    return success;
}

int RainfallList::size() const
{
    return rf_sequence.size();
}

unsigned long RainfallList::minimum() const
{
    // Return the lowest-valued rainfall in the rainfall list.  If the list is
    // empty, return NO_RAINFALLS.
    if(rf_sequence.empty())
    {
        return NO_RAINFALLS;
    }
    else
    {
        unsigned long min;
        rf_sequence.get(0, min); //sequences are kept in order
        return min;
    }
}

unsigned long RainfallList::maximum() const
{
    // Return the highest-valued rainfall in the rainfall list.  If the list is
    // empty, return NO_RAINFALLS.
    if(rf_sequence.empty())
    {
        return NO_RAINFALLS;
    }
    else
    {
        unsigned long max;
        int pos = rf_sequence.size()-1;
        rf_sequence.get(pos, max);
        max = max;
        return max;
    }
}

