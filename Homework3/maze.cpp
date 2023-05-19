//
//  maze.cpp
//  Homework3
//
//  Created by Cait on 5/7/23.
//

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
//    If the start location is equal to the ending location, then we've
//        solved the maze, so return true.
//    Mark the start location as visted.
//    For each of the four directions,
//        If the location one step in that direction (from the start
//            location) has no wall and is unvisited,
//                then call pathExists starting from that location (and
//                            ending at the same ending location as in the
//                            current call).
//                     If that returned true,
//                         then return true.
//    Return false.
    if(sr == er && sc == ec)
    {
        return true;
    }
    maze[sr][sc] = '+';
    //North
    if(maze[sr-1][sc] == '.')
    {
        if(pathExists(maze, sr-1, sc, er, ec))
        {
            return true;
        }
    }
    //East
    if(maze[sr][sc+1] == '.')
    {
        if(pathExists(maze, sr, sc+1, er, ec))
        {
            return true;
        }
    }
    //South
    if(maze[sr+1][sc] == '.')
    {
        if(pathExists(maze, sr+1, sc, er, ec))
        {
            return true;
        }
    }
    //West
    if(maze[sr][sc-1] == '.')
    {
        if(pathExists(maze, sr, sc-1, er, ec))
        {
            return true;
        }
    }
    return false;
}
