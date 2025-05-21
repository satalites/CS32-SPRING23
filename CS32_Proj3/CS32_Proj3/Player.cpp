//
//  Player.cpp
//  CS32_Proj3
//
//  Created by Cait on 5/17/23.
//
#include <iostream>
#include "Player.h"
#include "Side.h"

//BEGINNING WITH BASE CLASS
Player::Player(std::string name)
{
    mName = name;
}

std::string Player::name() const
{
    return mName;
}

bool Player::isInteractive() const
{
    return false;
}

Player::~Player()
{}

//HUMAN PLAYER CLASS
HumanPlayer::HumanPlayer(std::string name) : Player(name)
{}

bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board &b, Side s) const
{
    //get a variable to take in our inputted value
    int chosenHole = -1;
    //beginnign a turn, if there's no beans on our side we cant do antyhing
    if(b.beansInPlay(s) == 0)
    {
        return chosenHole;
    }
    //have a loop that takes our value til it's valid(?) and move
    bool chosen = false;
    while(!chosen)
    {
        std::cout << "Player " << Player::name() << ", choose a hole: ";
        std::cin >> chosenHole;
        if(chosenHole <= 0 || chosenHole > b.holes())
        {
            std::cout << "That is not a valid hole. Pick from numbers between 1 and " << b.holes() << std::endl;
        }
        if(b.beans(s, chosen) == 0)
        {
            std::cout << "Hole is empty. Pick again." << std::endl;
        }
        else
        {
            std::cout << "Player " << Player::name() << " chooses Hole " << chosenHole << std::endl;
            chosen = true;
        }
    }
    return chosenHole;
}

HumanPlayer::~HumanPlayer()
{}

//BAD PLAYER CLASS
BadPlayer::BadPlayer(std::string name) : Player(name)
{}

int BadPlayer::chooseMove(const Board &b, Side s) const
{
    //get a variable to take in our inputted value
    int chosenHole = -1;
    //beginnign a turn, if there's no beans on our side we cant do antyhing
    if(b.beansInPlay(s) == 0)
    {
        return chosenHole;
    }
    //now find the first hole that is not empty
    for(int i = 1; i <= b.holes(); i++)
    {
        if(b.beans(s, i) > 0)
        {
            chosenHole = i;
//            std::cout << "Player " << Player::name() << " chooses Hole " << chosenHole << std::endl;
            break;
        }
    }
    return chosenHole;
}

BadPlayer::~BadPlayer()
{}

//SMART PLAYER CLASS
SmartPlayer::SmartPlayer(std::string name) : Player(name)
{
    
}

SmartPlayer::~SmartPlayer()
{}

int SmartPlayer::chooseMove(const Board &b, Side s) const
{
    Board copiedBoard = Board(b);
    int deep = 0;
    int value = 0;
    int goodMove = 0;
    int maxTime = 4980;
    Timer clock;
    double allowedTime = maxTime/b.holes();
    evaluateMove(copiedBoard, s, deep, value, goodMove, clock, maxTime, allowedTime);
    return goodMove;
}

// Find move that results in first friendly win
void SmartPlayer::evaluateMove(Board& b, Side s, int depth, int &goodnessVal, int& goodHole, Timer& clock, const int maxTime, double allowedTime) const
{
    if(clock.elapsed() >= maxTime)
    {
        goodnessVal = (rateMove(b, s));
        goodHole = -1;
        return;
    }
    //cut off at some depth
    if(depth > 8) //maybe take this out?
    {
        goodnessVal = (rateMove(b, s));
        goodHole = -1;
        return;
    }
    //if we can't make a move because there's no beans on our side, we can't make ANY move
    if(b.beansInPlay(s) == 0)
    {
        goodnessVal = (rateMove(b, s));
        goodHole = -1;
        return;
    }
    //track the current hole that returns starting from 1 (not pot)
    int firstHoleValid = 1;
    //find allowed time to give to each depth
    allowedTime = (maxTime-clock.elapsed())/(b.holes());
    //now iterate through
    for(int hole = 1; hole <= b.holes(); hole++)
    {
        //make copy of board & initialize vars
        Board copy = Board(b);
        int valH;
        int oppHole;
        int ourHole;
        Side endS;
        int endH;
        if(copy.beans(s, hole) == 0)
        {
            firstHoleValid++;
            continue;
        }
        if(makeMove(copy, s, hole, endS, endH))
        {
            //opponent
            evaluateMove(copy, opponent(s), depth + 1, valH, oppHole, clock, maxTime, allowedTime);
        }
        else
        {
            //ours
            evaluateMove(copy, s, depth, valH, ourHole, clock, maxTime, allowedTime);
        }
        if(hole == firstHoleValid)
        {
            goodHole = hole;
            goodnessVal = valH;
        }
        if(s == SOUTH)
        {
            if(valH > goodnessVal)
            {
                goodnessVal = valH;
                goodHole = hole;
            }
        }
        else //if it is north
        {
            if(valH < goodnessVal)
            {
                goodnessVal = valH;
                goodHole = hole;
            }
        }
    }
    return;
    // Itterate over all the possible next moves
    // Call evaluateMove on each of these states

//    int best_goodnesss = __INT_MAX__;
//    int best_move_pos = __INT_MAX__;
//    for (auto move : moves) {
//        int this_goodness = __INT_MAX__;
//        int this_move = evaluateMove(b, s, depth, this_goodness);
//        if (this_goodness < best_goodnesss){
//            best_goodnesss = this_goodness;
//            best_move_pos = this_movep;
//        }
//
//    }
//
//    goodnessVal = best_goodnesss + 1;
//    return best_move_pos;
}

int SmartPlayer::rateMove(Board& b, Side s) const //we are on south's side (max), north is our min
{
    //a BIG THANK YOU to help from the TAs for this
    //if there's a win condition...
    if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0)
    {
        if ((b.beans(SOUTH, 0) + b.beansInPlay(SOUTH)) > (b.beans(NORTH, 0) + b.beansInPlay(NORTH)))
        {
            return 2500;
        }
        else if ((b.beans(SOUTH, 0) + b.beansInPlay(SOUTH)) < (b.beans(NORTH, 0) + b.beansInPlay(NORTH)))
        {
            return -2500;
        }
        else
        {
            //if they're equal, it's a tie
            return 0;
        }
    }
    //if there is no win condition, south - north beans
    return (b.beans(SOUTH, 0) + b.beansInPlay(SOUTH) - b.beans(NORTH, 0) - b.beansInPlay(NORTH));
}

bool SmartPlayer::makeMove(Board& b, Side s, int hole, Side& endS, int& endH) const
{
    if (b.sow(s, hole, endS, endH)) //if the move can be made
    {
        if (endH == 0) //ending on our pot means we get another turn, so false means it is NOT the opponent's turn
        {
            return false;
        }
        else if (endS == s)
        {
            if (b.beans(opponent(s), endH) > 0 && b.beans(s, endH) == 1) //if the hole we landed on was previously empty and on our side, we get the same hole but on the opponent's side
            {
                //we take these beans
                b.moveToPot(opponent(s), endH, s);
                b.moveToPot(s, endH, s);
                return true; //we don't end on our pot. it is true that it is our opponent's turn
            }
        }
        return true;
    }
    return true; //idk
}












//            D I S R E G A R D ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
//this is the graveyard of my various attempts to write the SmartPlayer functions. i kept them here as a reminder

//SmartPlayer::Node* SmartPlayer::makeMoveTree(Board &b, Side s, int hole, int depth, Node* root) const
//{
//    //return when depth hits 3
//    if(depth >= 3)
//    {
//
//    }
//    else //if we haven't hit our limit
//    {
//        if(depth == 0)
//        {
//            Node* top =  new Node(b, s);
//            root = top;
//            return root;
//        }
//        for(int i = 1; i <= b.holes(); i++)
//        {
//
//        }
//    }
//    //if depth 0, root is a new node and we return root
//int SmartPlayer::evaluateMoves(Board& b, Side s, int depth, int& goodnessOfMove) const
//{
//    Side opponent = s; //holding opposite side for later
//    if(s == SOUTH)
//    {
//        opponent = NORTH;
//    }
//    else
//    {
//        opponent = SOUTH;
//    }
//    //if depth goes too far
//    if(depth > 3)
//    {
//
//        return 0; //return as if it was a tie?
//    }
//    //if s is not south, then it's north and we've initialized variable opponent correctly
//    //vector to hold our results
//
//    std::vector<int> res;
//    //vector to tell if hole is valid/invalid
//    std::vector<bool> validity;
//    //fill with zeros & false
//    for(int i = 1; i <= b.holes(); i++)
//    {
//        res.push_back(0);
//        validity.push_back(true);
//    }
//    for(int j = 1; j <= b.holes(); j++)
//    {
//        Board copy = Board(b); //make copy of board
//        if(copy.beans(s,j) != 0) //if a given hole is not empty...
//        {
//            Side endS;
//            int endH;
//            bool determineTurn = makeMove(copy, s, j, endS, endH); //make a move and then begins evaluating from here
//            int goodness = didMoveWinQuestionMark(copy, s); //gives a value
//            if(goodness == 1 || goodness == 0) //if we win or have a tie
//            {
//                res[j] = goodness * (b.holes() - depth);
//            }
//            if(determineTurn) //if determineTurn returns true, it means the opponent will go
//            {
//                int val = 0;
//                evaluateMoves(copy, opponent, depth+1, val);
//                res[j] = val*-1; //push a negative value because it's the opposing side
//            }
//            else //otherwise it'll still be our turn
//            {
//                evaluateMoves(copy, s, depth+1, goodness);
//            }
//        }
//        else
//        {
//            // set valid to false (no beans to move here)
//            validity[j] = false;
//        }
//    }
//    int bestHole = -1;
//    int biggestHoleNum = -10000;
//    for(int k = 0; k < b.holes(); k++)
//    {
//        if(validity[k] == true)
//        {
//            if((res[k]) >= biggestHoleNum && b.beans(s, k) != 0)
//            {
//                bestHole = k;
//                biggestHoleNum = res[k];
//            }
//        }
//    }
//
//
//    return bestHole;
//}
//
//
//int SmartPlayer::didMoveWinQuestionMark(Board& b, Side s) const //where south is "our" side
//{
//    // if no beans left on the board
//    // evaluate who won (or tied)
//    // return
//    //see if board passed is in winning state for either
//    //else, score  for south would be south beans minus north beans
//    if(b.beansInPlay(SOUTH) > 0 && b.beansInPlay(NORTH) > 0)
//    {
//        //we have not finished the game
//        return (b.beansInPlay(SOUTH) - b.beansInPlay(NORTH));
//    }
//    if(b.beans(SOUTH, 0) == b.beans(NORTH, 0))
//    {
//        return 0;
//    }
//    //does south win?
//    if(b.beans(SOUTH, 0) > b.beans(NORTH, 0))
//    {
//
//        return 1000;
//    }
//    //does north win?
//    if(b.beans(SOUTH, 0) < b.beans(NORTH, 0))
//    {
//        return -1000;
//    }
//    return 0;
//}
