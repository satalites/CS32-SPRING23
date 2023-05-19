//
//  testRainfallList.cpp
//  HW1
//
//  Created by Cait on 4/17/23.
//

#include "RainfallList.h"
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    RainfallList r;
    assert(r.size()==0);
    cout << r.size() << endl;
    assert(!r.add(500));
    cout << r.size() << endl;
    r.add(245);
    cout << r.size() << endl;
    assert(r.remove(245));
    cout << r.size() << endl;
    assert(r.remove(200) == 0);
    cout << r.size() << endl;
    r.add(200);
    cout << r.size() << endl;
    r.add(255);
    cout << r.size() << endl;
    r.add(400);
    cout << r.size() << endl;
    r.add(20);
    cout << r.size() << endl;
    assert(r.size()==4);
    assert(r.minimum() == 20);
    assert(r.maximum() == 400);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
