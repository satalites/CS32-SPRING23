////
////  HW1
////
////  Created by Cait on 4/16/23.
////
//
////#include <iostream>
////#include "Sequence.h"
////
////using namespace std;
////
////int main()
////{
////    Sequence s;
////    s.insert(0, "a");
////    s.insert(1, "b");
////    s.insert(2, "e");
////    s.insert(3, "b");
////    s.insert(4, "c");
////    assert(s.remove("b") == 2);
////    assert(s.size() == 3);
////    string x;
////    assert(s.get(0, x)  &&  x == "a");
////    assert(s.get(1, x)  &&  x == "e");
////    assert(s.get(2, x)  &&  x == "c");
////
////    Sequence s1;
////    s1.insert(0, "paratha");
////    s1.insert(0, "focaccia");
////    //focaccia parantha
////    Sequence s2;
////    s2.insert(0, "roti");
////    //roti
////    s1.swap(s2);
////    assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  && s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
////
////        Sequence s;
////        s.insert(0, "lavash");
////        s.insert(0, "tortilla");
////        assert(s.size() == 2);
////        ItemType x = "injera";
////        assert(s.get(0, x) && x == "tortilla");
////        assert(s.get(1, x) && x == "lavash");
////}
//
////#include "Sequence.h"
////#include <iostream>
////#include <cassert>
////using namespace std;
////
////void test()
////{
////    Sequence s;
////    s.insert(0, 10);
////    s.insert(0, 20);
////    assert(s.size() == 2);
////    ItemType x = 999;
////    assert(s.get(0, x) && x == 20);
////    assert(s.get(1, x) && x == 10);
////}
////
////int main()
////{
////    test();
////    cout << "Passed all tests" << endl;
////}

#include "Sequence.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//// To test a Sequence of unsigned long, leave the #define line commented out;
//// to test a Sequence of string, remove the "//".
//
// #define TEST_WITH_STRING

#ifdef TEST_WITH_STRING
  const ItemType VAL[3] = { "injera", "lavash", "tortilla" };
#else // assume unsigned long
  const ItemType VAL[3] = { 999, 10, 20 };
#endif

void test()
{
    Sequence s;
    s.insert(0, VAL[1]);
    s.insert(0, VAL[2]);
    assert(s.size() == 2);
    ItemType x = VAL[0];
    assert(s.get(0, x) && x == VAL[2]);
    assert(s.get(1, x) && x == VAL[1]);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
