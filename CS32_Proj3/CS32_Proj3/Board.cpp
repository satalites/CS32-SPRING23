//
//  Board.cpp
//  CS32_Proj3
//
//  Created by Cait on 5/17/23.
//
#include "Side.h"
#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
{
    //    Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
    if(nHoles >= 0)
        mHoles = nHoles;
    else
        mHoles = 1;
    if(nInitialBeansPerHole >= 0)
        mInitialBeansPerHole = nInitialBeansPerHole;
    else
        mInitialBeansPerHole = 0;
    //now put all the beans into the holes, but pots MUST be empty
    northBoard.push_back(0);
    southBoard.push_back(0);
    //bean in hole for all holes
    for(int i = 1; i <= nHoles; i++)
    {
        northBoard.push_back(mInitialBeansPerHole);
        southBoard.push_back(mInitialBeansPerHole);
    }
}

Board::Board(const Board &rhs) : northBoard(rhs.northBoard), southBoard(rhs.southBoard)
{
    //copy constructor
    mHoles = rhs.mHoles;
    mInitialBeansPerHole = rhs.mInitialBeansPerHole;
}

int Board::holes() const
{
    //    Return the number of holes on a side (not counting the pot).
    return mHoles;
}

int Board::beans(Side s, int hole) const
{
    //    Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
    if(hole < 0 || hole > mHoles) //checking validity
    {
        return -1;
    }
    //checking side and then returning desired count
    if(s == SOUTH)
    {
        return southBoard.at(hole);
    }
    else //if not south, it has to be north
    {
        return northBoard.at(hole);
    }
}

int Board::beansInPlay(Side s) const
{
    //    Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
    int total = 0;
    if(s == SOUTH)
    {
        for(int i = 1; i <= mHoles; i++)
            total += southBoard.at(i);
        return total;
    }
    else
    {
        for(int j = 1; j <= mHoles; j++)
            total += northBoard.at(j);
        return total;
    }
}

int Board::totalBeans() const
{
    //    Return the total number of beans in the game, including any in the pots.
    int total = 0;
    for(int i =  0; i <= mHoles; i++)
    {
        total += northBoard.at(i); //add from north side
        total += southBoard.at(i); //add from south side
    }
    return total;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    //    If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The function sets the parameters endSide and endHole to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
    if(hole <= 0 || hole > mHoles)
    {
        return false;
    }
    //check if there are beans in hole. if not, return false
    //for south
    if(s == SOUTH)
    {
        if(southBoard.at(hole) == 0)
            return false;
    }
    //for north
    if(s == NORTH)
    {
        if(northBoard.at(hole) == 0)
            return false;
    }
    // !!!!!!!!!!!!
    //IMPORTANT: TRAVERSE THROUGH NORTH BACKWARDS, TRAVERSE THROUGH SOUTH FORWARDS
    // !!!!!!!!!!!!
    //so our input for hole is valid, now we move the beans :3
    //make separate variables for current values
    int thisHole = hole;
    Side thisSide = s;
    //if we begin at south side...
    if(s == SOUTH)
    {
        //tells us how many beans are in our hand
        int thisBeans = southBoard.at(hole);
        //take beans out of same hole
        southBoard.at(hole) = 0;
        //and then we drop off beans one by one until we run out of beanz
        while(thisBeans != 0) //
        {
            //run through south, deposit in south pot too
            for(int i = hole+1; i <= holes(); i++) //hole + 1 because we want to start the adding AFTER the original hole
            {
                //add a bean to hole
                southBoard.at(i)++;
                //take a bean from our hand
                thisBeans--;
                //change our thisSide var appropriately
                thisHole = i;
                //check if we've run out of beans
                if(thisBeans == 0)
                {
                    endSide = thisSide;
                    endHole = i;
                    return true;
                }
            }
            //after traversing through south til end, come back and add a bean to south
            if(thisBeans > 0)
            {
                //add a lil bean to south
                southBoard.at(0)++;
                //take a bean from our hand
                thisBeans--;
                //check if we dropped our last bean into the south pot
                if(thisBeans == 0)
                {
                    endSide = SOUTH;
                    endHole = 0; //because pot
                    return true;
                }
            }
            //now we run through north side
            //WE RUN THROUGH NORTH BACKWARDS
            for(int j = holes(); j > 0; j--)
            {
                //add a bean to hole
                northBoard.at(j)++;
                //take a bean from our hand
                thisBeans--;
                //check if we ran outta beans
                if(thisBeans == 0)
                {
                    endSide = NORTH;
                    endHole = j;
                    return true;
                }
            }
        }
        return true;
    }
    //otherwise, if we start in north...
    else
    {
        //tells us how many beans are in our hand
        int thisBeans = northBoard.at(hole);
        northBoard.at(hole) = 0;
        //and then we drop off beans one by one until we run out of beanz
        while(thisBeans != 0) //
        {
            //run through north, deposit in north pot too
            for(int i = hole-1; i > 0; i--)
            {
                //add a bean to hole
                northBoard.at(i)++;
                //take a bean from our hand
                thisBeans--;
                //change our thisSide var appropriately
                thisHole = i;
                //check if we've run out of beans
                if(thisBeans == 0)
                {
                    endSide = thisSide;
                    endHole = i;
                    return true;
                }
            }
            //after traversing through north til end, come back and add a bean to north pot
            if(thisBeans > 0)
            {
                //add a lil bean to north pot
                northBoard.at(0)++;
                //take a bean from our hand
                thisBeans--;
                //check if we dropped our last bean into the north pot
                if(thisBeans == 0)
                {
                    endSide = NORTH;
                    endHole = 0; //because pot
                    return true;
                }
            }
            //now we run through south side
            //WE RUN THROUGH SOUTH FORWARDS
            for(int j = 1; j <= holes(); j++)
            {
                //add a bean to hole
                southBoard.at(j)++;
                //take a bean from our hand
                thisBeans--;
                //check if we ran outta beans
                if(thisBeans == 0)
                {
                    endSide = SOUTH;
                    endHole = j;
                    return true;
                }
            }
        }
        return true;
    }
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    //    If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
    if(hole <= 0 || hole > mHoles)
    {
        return false;
    }
    if(s == SOUTH)
    {
        if(potOwner == SOUTH)
        {
            southBoard.at(0) += southBoard.at(hole);
            southBoard.at(hole) = 0;
            return true;
        }
        else
        {
            northBoard.at(0) += southBoard.at(hole);
            southBoard.at(hole) = 0;
            return true;
        }
    }
    else
    {
        if(potOwner == SOUTH)
        {
            southBoard.at(0) += northBoard.at(hole);
            northBoard.at(hole) = 0;
            return true;
        }
        else
        {
            northBoard.at(0) += northBoard.at(hole);
            northBoard.at(hole) = 0;
            return true;
        }
    }
}

bool Board::setBeans(Side s, int hole, int beans)
{
    //    If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This could change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
    if(hole < 0 || hole > mHoles || beans < 0)
    {
        return false;
    }
    if(s == SOUTH)
    {
        southBoard.at(hole) = beans;
        return true;
    }
    else
    {
        northBoard.at(hole) = beans;
        return true;
    }
}
