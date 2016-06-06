//
//  main.cpp
//  circ_buf
//
//  Created by dmytro.medynsky on 6/3/16.
//  Copyright © 2016 dmytro.medynsky. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "circ_buf.h"

using namespace std;
struct S {
    virtual void f(){};
    virtual ~S(){};
};

struct S1: S {
    void f() override {
        cout << "override" << endl;
    }
};
int main()
{
    circ_buf<int> ringBuffer = circ_buf<int>();
    
    ringBuffer.put_item(3);
    ringBuffer.put_item(6);
    ringBuffer.put_item(7);
    ringBuffer.put_item(2);
    //ringBuffer.put_item(2);
    //ringBuffer.put_item(2);
//    cout<< ringBuffer.space() << endl;
//        ringBuffer.space();



    

    
//    for (int i = 0; i < ringBuffer.count(); i++){
//        cout << ringBuffer.get_item() << endl;
//    }
    
    cout << "\n\n";
    
    system("PAUSE");
    
    return 0;
}