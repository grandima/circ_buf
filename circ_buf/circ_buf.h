//
//  circ_buf.h
//  circ_buf
//
//  Created by dmytro.medynsky on 6/1/16.
//  Copyright © 2016 dmytro.medynsky. All rights reserved.
//

#include "circ_buff_realization.h"
/**
 *  If you initialize buffer with size == n. Actual buffer size will be n - 1. In this realization
 *  I uses one extra value for differentiation full buffer and empty. 
 *  Full buffer: head + 1 == tail. Empty buffer: head == tail.
 *  To create a buffer: circ_buf<int> ringBuffer = circ_buf<int>(); 
 */
template <typename T>
struct circ_buf {
public:
    
	circ_buf() {
        isPowerOfTwo(size) ? buff = new opt_circ_buff<T>(size) : buff = new general_circ_buff<T>(size);
    }

    ~circ_buf() {delete buff;}

	int count() {return buff->count();}

	int space() {return buff->space();}
    
    T get_item() {return buff->get_item();}
    
    void put_item(T item) {buff->put_item(item);}
    
	int count_to_end() {return buff->count_to_end();}

    int space_to_end() {return buff->space_to_end();}

    bool is_empty() {return buff->is_empty();}
    
	bool is_full() {return buff->is_full();}
private:
    circ_buff_interface<T> *buff;
    
	const int size = 7;
    
    bool isPowerOfTwo (int x) {
        while (((x % 2) == 0) && x > 1)
            x /= 2;
        return (x == 1);
    }
};

