//
//  linear.cpp
//  Homework3
//
//  Created by Cait on 5/6/23.
//

bool somePredicate(string s)
{
    if(s == "beep")
        return true;
    return false;
}

bool allTrue(const string a[], int n)
{
    // Return false if the somePredicate function returns false for at
    // least one of the array elements; return true otherwise.
    if(n <= 0)
    {
        return true;
    }
    if(!somePredicate(a[0]))
    {
        return false;
    }
    return allTrue(a+1, n-1);
}

int countTrue(const string a[], int n)
{
    // Return the number of elements in the array for which the
    // somePredicate function returns true.
    if(n <= 0)
    {
        return 0;
    }
    if(somePredicate(a[0]))
    {
        return countTrue(a+1, n-1) + 1;
    }
    return countTrue(a+1, n-1);
}

int firstTrue(const string a[], int n)
{
    // Return the subscript of the first element in the array for which
    // the somePredicate function returns true.  If there is no such
    // element, return -1.
    if(n <= 0)
    {
        return -1;
    }
    if(somePredicate(a[0])) //we've found our first true
    {
        return 0;
    }
    else
    {
        int count = firstTrue(a+1, n-1); //begin a counter
        //now we see what we should return
        if(count == -1)
        {
            return count;
        }
        return count + 1; //plus one because when we find true, it return 0 and thus doesnt increase counter
    }
}

int positionOfMax(const string a[], int n)
{
    // Return the subscript of the first string in the array that is >= all
    // strings in the array (i.e., return the smallest subscript m such
    // that a[m] >= a[k] for all k from 0 to n-1).  If the function is told
    // that no strings are to be considered to be in the array, return -1.
    if(n <= 0)
    {
        return -1;
    }
    int count = positionOfMax(a+1, n-1) + 1;
    if(a[0] >= a[count])
    {
        return 0;
    }
    else
    {
        return count;
    }
}

bool contains(const string a1[], int n1, const string a2[], int n2)
{
    // If all n2 elements of a2 appear in the n1 element array a1, in
    // the same order (though not necessarily consecutively), then
    // return true; otherwise (i.e., if the array a1 does not include
    // a2 as a not-necessarily-contiguous subsequence), return false.
    // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
    // For example, if a1 is the 7 element array
    //    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
    // then the function should return true if a2 is
    //    "sonia" "ketanji" "samuel"
    // or
    //    "sonia" "elena" "elena"
    // and it should return false if a2 is
    //    "sonia" "samuel" "ketanji"
    // or
    //    "john" "ketanji" "ketanji"
    if(n2 <= 0)
    {
        return true;
    }
    if(n1 <= 0 && n2 != 0)
    {
        return false;
    }
    if(a1[0] == a2[0])
    {
        return contains(a1+1, n1-1, a2+1, n2-1); //move up in both arrays
    }
    else
    {
        return contains(a1+1, n1-1, a2, n2); //move up in a1 but not a2
    }
}


//int main()
//{
//    string beep1[3];
//    beep1[0] = "beep";
//    beep1[1] = "beep";
//    beep1[2] = "beep";
//    string beep2[3];
//    beep2[0] = "boop";
//    beep2[1] = "beep";
//    beep2[2] = "beep";
//    string beep3[3];
//    beep3[0] = "beep";
//    beep3[1] = "boop";
//    beep3[2] = "beep";
//    string beep4[3];
//    beep4[0] = "beep";
//    beep4[1] = "beep";
//    beep4[2] = "boop";
//    string beep5[3];
//    beep5[0] = "beep";
//    beep5[1] = "boop";
//    beep5[2] = "boop";
//    string beep6[3];
//    beep6[0] = "boop";
//    beep6[1] = "boop";
//    beep6[2] = "boop";
//
//    assert( allTrue(beep1, 3) );
//    assert( !allTrue(beep2, 3) );
//    assert( !allTrue(beep3, 3) );
//    assert( !allTrue(beep4, 3) );
//    assert( allTrue(beep4, 0) );
//
//    assert( countTrue(beep1, 3) == 3 );
//    assert( countTrue(beep2, 3) == 2 );
//    assert( countTrue(beep3, 3) == 2 );
//    assert( countTrue(beep4, 3) == 2 );
//    assert( countTrue(beep5, 3) == 1 );
//    assert( countTrue(beep6, 3) == 0 );
//    assert( countTrue(beep6, 0) == 0 );
//
//    assert( firstTrue(beep1, 3) == 0 );
//    assert( firstTrue(beep2, 3) == 1 );
//    assert( firstTrue(beep3, 3) == 0 );
//    assert( firstTrue(beep4, 3) == 0 );
//    assert( firstTrue(beep5, 3) == 0 );
//    assert( firstTrue(beep6, 3) == -1 );
//    assert( firstTrue(beep6, 0) == -1 );
//
//    string ind[3];
//    ind[0] = "10";
//    ind[1] = "20";
//    ind[2] = "30";
//    string ind2[3];
//    ind[0] = "20";
//    ind[1] = "30";
//    ind[2] = "5";
//    string ind3[3];
//    ind3[0] = "30";
//    ind3[1] = "5";
//    ind3[2] = "10";
//    assert( positionOfMax(ind, 3) == 2 );
//
//    string zerothIndex[3] = {"a", "b", "c"};
//    string firstIndex[3] = {"b", "a", "c"};
//    string secondIndex[3] = {"c", "b", "a"};
//    string secondIndex2[3] = {"b", "b", "a"};
//    string firstIndex2[3] = {"b", "a", "a"};
//    string firstIndex3[5] = {"b", "a", "a", "b", "a"};
//
//    assert( positionOfMax(zerothIndex, 3) == 2 );
//    assert( positionOfMax(firstIndex, 3) == 2 );
//    assert( positionOfMax(secondIndex, 3) == 0 );
//    assert( positionOfMax(secondIndex2, 3) == 0 );
//    assert( positionOfMax(secondIndex2, 0) == -1 );
//    assert( positionOfMax(firstIndex2, 3) == 0 );
//    assert( positionOfMax(firstIndex3, 5) == 0 );
//
//    string ar[7] = {"john", "sonia", "elena", "ketanji", "sonia", "elena", "samuel"};
//    string arc1[3] = {"sonia", "ketanji", "samuel"};
//    string arc2[3] = {"sonia", "elena", "elena"};
//    string arc3[3] = {"sonia", "samuel", "ketanji"};
//    string arc4[3] = {"john", "ketanji", "ketanji"};
//    assert(contains(ar, 7, arc1, 3));
//    assert(contains(ar, 7, arc2, 3));
//    assert(!contains(ar, 7, arc3, 3));
//    assert(!contains(ar, 7, arc4, 3));
//
//    cout << "passed all asserts" << endl;
//}
