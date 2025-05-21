//
//  Player.hpp
//  CS32_Proj3
//
//  Created by Cait on 5/17/23.
//

#ifndef Player_h
#define Player_h

#include <string>
#include "Side.h"
#include "Board.h"
#include <vector>
//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

class Timer
{
  public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {
        std::chrono::duration<double, std::milli> diff =
                          std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
  private:
    std::chrono::high_resolution_clock::time_point m_time;
};

class Player
{
private:
    std::string mName;
public:
    Player(std::string name);
    //Create a Player with the indicated name.
    std::string name() const;
    //Return the name of the player.
    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const = 0;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~Player();
    //Since this class is designed as a base class, it should have a virtual destructor.
};

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~HumanPlayer();
};

class BadPlayer : public Player
{
public:
    BadPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~BadPlayer();
};

class SmartPlayer : public Player
{
public:
    SmartPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~SmartPlayer();
private:
    bool makeMove(Board& b, Side s, int hole, Side& endS, int& endH) const;
    int rateMove(Board& b, Side s) const;
    void evaluateMove(Board& b, Side s, int depth, int &goodnessVal, int& goodHole, Timer& clock, const int maxTime, double allowedTime) const;

// D I S R E G A R D !!!!!!!!!
    //everything after this is kept here as a reminder of previous attempts (what worked/didn't work)
//    int evaluate(Board& b, Side s) const;
//    int evaluateMoves(Board& b, Side s, int depth, int& goodnessOfMove) const;
//    int didMoveWinQuestionMark(Board& b, Side s) const;
//    struct Node
//    {
//        Node(Board& b, Side s);
//        Board currentBoard;
//        Side currentSide;
//        int score = 0;
//        std::vector<Node*> children;
//    };
//    Node* root;
//    Node* makeMoveTree(Board& b, Side s, int hole, int depth, Node* root) const;
//    int minimax
};

#endif /* Player_h */
