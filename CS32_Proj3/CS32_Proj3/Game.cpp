//
//  Game.cpp
//  CS32_Proj3
//
//  Created by Cait on 5/17/23.
//

#include "Game.h"
#include <iostream>

Game::Game(const Board& b, Player* south, Player* north) : mBoard(b), mSouthP(south), mNorthP(north)
{
    //Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
    mTurn = SOUTH; //south first
}

void Game::display() const
{
    //Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
    
    //print out north name
    std::cout << "North: " << mNorthP->name() << std::endl;
    
    //print out north holes
    std::cout << "    "; //tab
    for(int i = 1; i <= mBoard.holes(); i++)
    {
        std::cout << mBoard.beans(NORTH, i) << "  ";
    }
    std::cout << std::endl; //move to next line and then...
    
    //print out north pot
    std::cout << mBoard.beans(NORTH, 0);
    
    //gap for south pot
    for(int i = 1; i <= mBoard.holes(); i++)
    {
        std::cout << "    "; //print out gap...
    }
    
    //print out south pot and end line
    std::cout << mBoard.beans(SOUTH, 0) << std::endl;
    
    //print out south holes
    std::cout << "    "; //tab
    for(int i = 1; i <= mBoard.holes(); i++)
    {
        std::cout << mBoard.beans(SOUTH, i) << "  ";
    }
    std::cout << std::endl << "South: " << mSouthP->name() << std::endl; //moved to next line and printed south name
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    //If the game is over (i.e., the move member function has been called and returned false), set over to true; otherwise, set over to false and do not change anything else. If the game is over, set hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
    //first we determine if the game is over
    if(mBoard.beansInPlay(SOUTH) > 0 && mBoard.beansInPlay(NORTH) > 0)
    {
        over = false;
        hasWinner = false;
        return;
    }
    //so then it must be over
    else
    {
        over = true;
    }
    //now we must either crown a winner or determine if there's a tie
    //is there a tie?
    if(mBoard.beans(SOUTH, 0) == mBoard.beans(NORTH, 0))
    {
        hasWinner = false;
        return;
    }
    //does south win?
    if(mBoard.beans(SOUTH, 0) > mBoard.beans(NORTH, 0))
    {
        hasWinner = true;
        winner = SOUTH;
        return;
    }
    //does north win?
    if(mBoard.beans(SOUTH, 0) < mBoard.beans(NORTH, 0))
    {
        hasWinner = true;
        winner = NORTH;
        return;
    }
}

bool Game::move(Side s)
{
    //Attempt to make a complete move for the player playing side s. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. Whenever the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening. If the move can be completed, return true; if not, because the move is not yet completed but side s has no holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that opponent's pot and return false.
    //vars for functions being called
    Side endS;
    int endH;
    //if it's south's move..
    if(s == SOUTH)
    {
        //get our move
        int moveHole = mSouthP->chooseMove(mBoard, SOUTH);
        std::cout << "Player " << mSouthP->name() << " picks hole " << moveHole << std::endl;
        
        if(mBoard.sow(SOUTH, moveHole, endS, endH)) //if we can make the move, we check if it's a capture/additional turn
        {
            
            if(endH == 0) //if we land back in pot
            {
                display(); //show board
                std::cout << std::endl;
                //see if there ar ebeans
                if(mBoard.beansInPlay(SOUTH) != 0)
                {
                    std::cout << "Player " << mSouthP->name() << " gets an additional turn" << std::endl;
                    return move(SOUTH); //we call function again to go again
                }
            }
                //see if we have a capture
            if(endS == SOUTH && mBoard.beans(SOUTH, endH) == 1 && mBoard.beans(NORTH, endH) > 0)
            {
                mBoard.moveToPot(NORTH, endH, SOUTH);
                mBoard.moveToPot(SOUTH, endH, SOUTH);
            }
            else if(mBoard.beansInPlay(SOUTH) != 0 && mBoard.beansInPlay(NORTH) != 0)
            {
                display();
            }
        }
    }
    else
    {
        int moveHole = mNorthP->chooseMove(mBoard, NORTH);
        std::cout << "Player " << mNorthP->name() << " picks hole " << moveHole << std::endl;
        
        
        if(mBoard.sow(NORTH, moveHole, endS, endH))
        {
            
            if(endH == 0)
            {
                display();
                std::cout << std::endl;
                if(mBoard.beansInPlay(NORTH) != 0)
                {
                    std::cout << "Player " << mNorthP->name() << " gets an additional turn" << std::endl;
                    
                    return move(NORTH);
                }
            }
            if(endS == NORTH && mBoard.beans(NORTH, endH) == 1 && mBoard.beans(SOUTH, endH) > 0)
            {
                mBoard.moveToPot(SOUTH, endH, NORTH);
                mBoard.moveToPot(NORTH, endH, NORTH);
            }
            else if(mBoard.beansInPlay(SOUTH) != 0 && mBoard.beansInPlay(NORTH) != 0)
            {
                display();
            }
        }
    }
    //if we run out of beans on a side, we sweep & return false
    if(mBoard.beansInPlay(SOUTH) == 0)
    {
//        display();
        std::cout << std::endl;
        std::cout << "We are out of beans, sweeping into North pot" << std::endl;
        for(int i = 1; i <= mBoard.holes(); i++)
        {
            mBoard.moveToPot(NORTH, i, NORTH);
        }
        return false;
    }
    if(mBoard.beansInPlay(NORTH) == 0)
    {
//        display();
        std::cout << std::endl; //at this point i think im just writing endl randomly to get better spacing for display
        std::cout << "We are out of beans, sweeping into North pot" << std::endl;
        for(int i = 1; i <= mBoard.holes(); i++)
        {
            mBoard.moveToPot(SOUTH, i, SOUTH);
        }
        return false;
    }
    return true;
}

void Game::play()
{
    //Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function.
    bool over = false;
    bool haveWin = false;
    Side winner = mTurn;
    std::cout << "GAME START!" << std::endl;
    display();
    std::cout << std::endl;
    while(!over)
    {
        move(mTurn);
        
        if(!mSouthP->isInteractive() && !mNorthP->isInteractive())
        {
            std::cout << "Press enter to continue.";
            std::cin.ignore(10000, '\n'); //for enter
            std::cout << std::endl;
        }
        status(over, haveWin, winner);
        mTurn = opponent(mTurn);
    }
    
    if (haveWin)
    {
        if (winner == SOUTH)
        {
            std::cout << "The winner is South player " + mSouthP->name() << std::endl;
        }
        else
        {
            std::cout << "The winner is North player " + mNorthP->name() << std::endl;
        }
    }
    else
    {
        std::cout << "Players tie." << std::endl;
    }
}

int Game::beans(Side s, int hole) const
{
    //Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
    if(hole < 0 || hole > mBoard.holes())
    {
        return -1;
    }
    return mBoard.beans(s, hole);
} //straightforward function
