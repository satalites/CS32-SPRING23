//
//  badlist.cpp
//  Homework4
//
//caitlin nguyen 605943983
//
  // Remove the restaurants in li with 2 or fewer stars and destroy them.
  // It is acceptable if the order of the remaining restaurants is not
  // the same as in the original list.
void removeBad(list<Restaurant*>& li)
{
    list<Restaurant*>::iterator iter;
    for(iter = li.begin(); iter != li.end();)
    {
        if((*iter)->stars() <= 2)
        {
            (*iter)->~Restaurant();
            iter = li.erase(iter);
        }
        else
            iter++;
    }
}
