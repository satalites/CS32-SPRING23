//
//  main.cpp
//  Homework4
//
//caitlin nguyen 605943983
//

  // Remove the even integers from li.
  // It is acceptable if the order of the remaining even integers is not
  // the same as in the original list.
void removeEven(list<int>& li)
{
    list<int>::iterator iter;
    for(iter = li.begin(); iter != li.end();)
    {
        if(*iter % 2 == 0)
        {
            iter = li.erase(iter);
        }
        else
            iter++;
    }
}

