////
////  mazequeue
////  Homework2
////
////  Created by Cait on 4/27/23.
////605943983
//#include <iostream>
//#include <queue>
//using namespace std;
//
//class Coord
//{
//public:
//    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
//    int r() const { return m_r; }
//    int c() const { return m_c; }
//private:
//    int m_r;
//    int m_c;
//};
//
//bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
//{
//    //following pseudocode given
//    queue<Coord> coordQueue;
//    //push starting coordinate (sr, sc) onto coordinate queue
//    coordQueue.push(Coord(sr,sc));
//    //update maze[sr][sc] to indicate that the algorithm has encountered it (set maze[sr][sc] to have a value other than '.'
//    maze[sr][sc] = '+';
//    //while the queue is not empty...
//    while(!coordQueue.empty())
//    {
//        //pop the top coordinate off the queue. this gives current (r,c) location that algorithm is exploring
//        Coord topCoord = coordQueue.front();
//        //cout << "(" << topCoord.r() << "," << topCoord.c() << ")" << endl;
//        coordQueue.pop();
//        //if the current (r,c) coordinate is equal to ending coordinate, then we've solved the maze, so return true
//        if((topCoord.r() == er) && (topCoord.c() == ec))
//        {
//            return true;
//        }
//        //check each place you can move from current cell!!
//        //     SOUTH:
//        //if you can move SOUTH and haven't enountered that cell yet, then push coordinate (r+1, c) onto the queue and update maze[r+1][c] to indicate the algorithm has enountered it
//        if(maze[topCoord.r()+1][topCoord.c()] == '.')
//        {
//            coordQueue.push(Coord(topCoord.r()+1, topCoord.c()));
//            maze[topCoord.r()+1][topCoord.c()] = '+';
//        }
//        //     EAST:
//        //if you can move EAST and haven't encountered that cell yet, then push coordinate (r, c+1) onto the queue and update maze[r][c+1] to indicate algorithm encountered it
//        if(maze[topCoord.r()][topCoord.c()+1] == '.')
//        {
//            coordQueue.push(Coord(topCoord.r(), topCoord.c()+1));
//            maze[topCoord.r()][topCoord.c()+1] = '+';
//        }
//        //     NORTH:
//        if(maze[topCoord.r()-1][topCoord.c()] == '.')
//        {
//            coordQueue.push(Coord(topCoord.r()-1, topCoord.c()));
//            maze[topCoord.r()-1][topCoord.c()] = '+';
//        }
//        //     WEST:
//        if(maze[topCoord.r()][topCoord.c()-1] == '.')
//        {
//            coordQueue.push(Coord(topCoord.r(), topCoord.c()-1));
//            maze[topCoord.r()][topCoord.c()-1] = '+';
//        }
//    }
//    return false;
//}
//
