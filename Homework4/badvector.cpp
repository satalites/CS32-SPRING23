//
//  badvector.cpp
//  Homework4
//
//caitlin nguyen 605943983
//


void removeBad(vector<Restaurant*>& v)
{
    vector<Restaurant*>::iterator iter;
    for(iter = v.begin(); iter != v.end();)
    {
        if((*iter)->stars() <= 2)
        {
            (*iter)->~Restaurant();
            iter = v.erase(iter);
        }
        else
            iter++;
    }
}
