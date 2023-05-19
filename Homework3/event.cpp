//
//  main.cpp
//  Homework3
//
//  Created by Cait on 5/3/23.
//

#include <iostream>
#include <string>

using namespace std;

class Event
{
private:
    string mName;
    
public:
    Event(string name) : mName(name)
    {}
    virtual ~Event()
    {}
    string name() const
    {
        return mName;
    }
    virtual bool isSport() const
    {
        return true;
    }
    virtual string need() const
    {
        return "";
    }
};

class BasketballGame : public Event
{
public:
    BasketballGame(string name) : Event(name)
    {}
    virtual ~BasketballGame()
    {
        cout << "Destroying the " << name() << " basketball game" << endl;
    }
    virtual string need() const
    {
        return "hoops";
    }
};

class Concert : public Event
{
private:
    string mGenre;
    
public:
    Concert(string name, string genre) : Event(name), mGenre(genre)
    {}
    string genre() const
    {
        return mGenre;
    }
    virtual ~Concert()
    {
        cout << "Destroying the " << name() << " " << genre() << " concert" << endl;
    }
    virtual bool isSport() const
    {
        return false;
    }
    virtual string need() const
    {
        return "a stage";
    }
};

class HockeyGame : public Event
{
public:
    HockeyGame(string name) : Event(name)
    {}
    virtual ~HockeyGame()
    {
        cout << "Destroying the " << name() << " hockey game" << endl;
    }
    virtual string need() const
    {
        return "ice";
    }
};

void display(const Event* e)
{
    cout << e->name() << ": ";
    if (e->isSport())
    cout << "(sport) ";
    cout << "needs " << e->need() << endl;
}

//int main()
//{
//    Event* events[4];
//    events[0] = new BasketballGame("Lakers vs. Warriors");
//      // Concerts have a name and a genre.
//    events[1] = new Concert("Ricardo Arjona", "Latin pop");
//    events[2] = new Concert("Erykah Badu", "neo soul");
//    events[3] = new HockeyGame("Kings vs. Oilers");
//
//    cout << "Here are the events." << endl;
//    for (int k = 0; k < 4; k++)
//    display(events[k]);
//
//      // Clean up the events before exiting
//    cout << "Cleaning up." << endl;
//    for (int k = 0; k < 4; k++)
//    delete events[k];
//}


//        THE FOLLOWING SHOULD BE DISPLAYED
//Here are the events.
//Lakers vs. Warriors: (sport) needs hoops
//Ricardo Arjona: needs a stage
//Erykah Badu: needs a stage
//Kings vs. Flames: (sport) needs ice
//Cleaning up.
//Destroying the Lakers vs. Warriors basketball game
//Destroying the Ricardo Arjona Latin pop concert
//Destroying the Erykah Badu neo soul concert
//Destroying the Kings vs. Oilers hockey game
