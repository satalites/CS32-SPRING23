//
//  evenvector.cpp
//  Homework4
//
//caitlin nguyen 605943983
//


void removeEven(vector<int>& v)
{
    vector<int>::iterator iter;
    for(iter = v.begin(); iter != v.end();)
    {
        if(*iter%2 == 0)
        {
            iter = v.erase(iter);
        }
        else
          iter++;
    }
}
