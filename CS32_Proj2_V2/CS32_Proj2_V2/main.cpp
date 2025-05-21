//caitlin nguyen
//605943983


#include "Sequence.h"
#include <type_traits>

#define CHECKTYPE(c, f, r, a)  \
{  \
 static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
     "You did not declare " #c "::" #f " as the Project 2 spec does");  \
 auto p = static_cast<r (c::*)a>(&c::f);  \
 (void) p;  \
}
#define CHECKTYPENONMEMBER(f, r, a)  \
{  \
 static_assert(std::is_same<decltype(&f), r (*)a>::value, \
     "You did not declare " #f " as the Project 2 spec does");  \
 auto p = static_cast<r (*)a>(f);  \
 (void) p;  \
}

static_assert(std::is_default_constructible<Sequence>::value,
        "Sequence must be default-constructible.");
static_assert(std::is_copy_constructible<Sequence>::value,
        "Sequence must be copy-constructible.");
static_assert(std::is_copy_assignable<Sequence>::value,
        "Sequence must be assignable.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(Sequence, empty,  bool, () const);
    CHECKTYPE(Sequence, size,   int,  () const);
    CHECKTYPE(Sequence, erase,  bool, (int));
    CHECKTYPE(Sequence, remove, int,  (const ItemType&));
    CHECKTYPE(Sequence, get,    bool, (int, ItemType&) const);
    CHECKTYPE(Sequence, set,    bool, (int, const ItemType&));
    CHECKTYPE(Sequence, find,   int,  (const ItemType&) const);
    CHECKTYPE(Sequence, swap,   void, (Sequence&));
    //CHECKTYPENONMEMBER(subsequence,   int,  (const Sequence&, const Sequence&));
    //CHECKTYPENONMEMBER(concatReverse, void, (const Sequence&, const Sequence&, Sequence&));
    { auto p = static_cast<int (Sequence::*)(int, const ItemType&)>(&Sequence::insert); (void) p; }
    { auto p = static_cast<int (Sequence::*)(const ItemType&)>(&Sequence::insert); (void) p; }
}

int main()
{}
//
//#include <iostream>
//#include <cassert>
//#include <string>
//#include "Sequence.h"
//
//using namespace std;
//
//void test()
//{
////        Sequence my_list;
////
////        assert(my_list.find("w") == -1);
////
////        assert(my_list.insert(0, "a") == 0);
////
////        assert(my_list.insert(1, "b") == 1);
////
////        assert(my_list.insert(2, "b") == 2);
////
////        assert(my_list.insert(3, "e") == 3);
////
////        my_list.dump();
////
////        assert(my_list.remove("b") == 2);
////
////        my_list.dump();
////
////        assert(my_list.size() == 2);
////
////        assert(my_list.insert(2, "w") == 2);
////
////        my_list.dump();
////
////        assert(my_list.insert(".") == 0);
////
////        my_list.dump();
////
////        assert(my_list.erase(0));
////
////        my_list.dump();
////
////        assert(my_list.erase(1));
////
////        my_list.dump();
////
////        assert(my_list.insert(90, "raptor") == -1);
//
//
//
//    ItemType x;
//    Sequence ss;
//    assert(ss.insert("pita") == 0);
//    assert(ss.insert("roti") == 1);
//    assert(ss.size() == 2);
//    x = "laobing";
//    assert(ss.get(0, x)  &&  x == "pita");
//    assert(ss.get(1, x)  &&  x == "roti");
//    //
//    Sequence sss;
//    sss.insert("ccc");
//    sss.insert("aaa");
//    sss.insert("bbb");
//    x = "xxx";
//    assert(!sss.get(3, x)  &&  x == "xxx");
//    assert(sss.get(1, x)  &&  x == "bbb");
//    assert(sss.find("bbb") == 1);
//
//    Sequence s4;
//    s4.insert(0, "a");
//     s4.insert(1, "b");
//     s4.insert(2, "e");
//     s4.insert(3, "b");
//     s4.insert(4, "c");
//     assert(s4.remove("b") == 2);
//     assert(s4.size() == 3);
//     assert(s4.get(0, x)  &&  x == "a");
//     assert(s4.get(1, x)  &&  x == "e");
//    s4.dump();
//     assert(s4.get(2, x)  &&  x == "c");
//
//    Sequence subs1;
//    Sequence subs2;
//    subs1.insert(0,"30");
//    subs1.insert(1, "21");
//    subs1.insert(2, "63");
//    subs1.insert(3, "42");
//    subs1.insert(4, "17");
//    subs1.insert(5, "63");
//    subs1.insert(6, "17");
//    subs1.insert(7, "29");
//    subs1.insert(8, "8");
//    subs1.insert(9, "32");
//    subs1.dump();
//    subs2.insert(0, "63");
//    subs2.insert(1, "17");
//    subs2.insert(2, "29");
//    assert(subsequence(subs1, subs2) == 5);
//
//    Sequence concat1;
//    Sequence concat2;
//    Sequence result;
//    concat1.insert(0, "p");
//    concat1.insert(1, "a");
//    concat1.insert(2, "r");
//    concat2.insert(0, "r");
//    concat2.insert(1, "o");
//    concat2.insert(2, "t");
//    concatReverse(concat1, concat2, result);
//    result.dump();
//
//    Sequence cc;
//    Sequence cc2;
//    concatReverse(cc, cc2, cc);
//    cc.dump();
//
//    Sequence cc3;
//    Sequence cc4;
//    cc3.insert("1");
//    cc3.insert("2");
//    cc3.insert("3");
//    cc3.dump();
//    cc4.insert("a");
//    cc4.insert("b");
//    cc4.insert("c");
//    concatReverse(cc3, cc4, cc3);
//    cc3.dump();
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}
