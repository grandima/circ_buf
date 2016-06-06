//
//  Buffer_realization.hpp
//  circ_buf
//
//  Created by Dima Medynsky on 6/5/16.
//  Copyright © 2016 dmytro.medynsky. All rights reserved.
//

#include <cstdlib>
#include <assert.h>
using namespace std;

#pragma mark - Private concrete buffer interface
template <typename T>
struct circ_buff_interface {
    
    virtual int count() = 0;
    virtual int space() = 0;
    virtual T get_item() = 0;
    virtual void put_item(T ) = 0;
    virtual int count_to_end() = 0;
    virtual int space_to_end() = 0;
    virtual bool is_empty() = 0;
    virtual bool is_full() = 0;
    
    virtual ~circ_buff_interface(){};
private:
    virtual int next(int index) = 0;
};

#pragma mark - Optimal buffer realization

/**
 *  This struct implements a circular buffer interface for optimized size case (when size is power of 2).
 */
template <typename T>
struct opt_circ_buff: circ_buff_interface<T> {
    
    opt_circ_buff(int new_size)  {
        size = new_size;
        buffer = new T[size];
        head = tail = 0;
    }
    
    int count() override {
        assert(head >= tail);
        int count = 0;
        count = (head - tail) & (size - 1);
        cout << "Count: " << count << endl;
        return count;
    }
    
    int space() override {
        assert (tail > head);
        int space = 0;
        space = (tail - (head + 1)) & (size - 1);
        
        cout << "head: " << head << "\t tail: " << tail <<endl;
        cout << "Space: " << space << endl;
        return space;
    }
    
    T get_item() override {
        assert(head != tail);
        T t = buffer[tail];
        tail = next(tail);
        return t;
    }
    
    void put_item(T item) override {
        assert(!is_full());
        buffer[head] = item;
        head = next(head);
    }
    
    int count_to_end() override {
        int count = 0;
        int end = size - tail;
        int n = (head + end) & (size-1);
        count = n < end ? n : end;
        cout << "Count to end: " << count << endl;
        return count;
    }
    
    int space_to_end() override {
        cout << "Head: " << head << "\tTail: " << tail << endl;
        int space = 0;
        int end = size - 1 - head;
        int n = (end + tail) & (size - 1);
        space =  n <= end ? n : end+1;
        
        cout << "Space to end: " << space << endl;
        return space;
        
    }
    
    bool is_empty() override {
        return head == tail;
    }
    
    bool is_full() override {
        int next = 0;
        
        next = (head + 1) & (size - 1);
        
        bool full = (next == tail);
        cout << "Is full: " << full << endl;
        return full;
    }
    ~opt_circ_buff() {
        delete []buffer;
    }
    
private:
    T* buffer;
    int head;
    int tail;
    int size;
    
    int next(int index) override {
        return (index + 1) & (size - 1);
    }
    
};

#pragma mark - General buffer realization

/**
 *  This struct implements a circular buffer interface for general size case (when size is NOT power of 2).
 */
template <typename T>
struct general_circ_buff: circ_buff_interface<T> {
    general_circ_buff(int new_size)  {
        size = new_size;
        buffer = new T[size];
        head = tail = 0;
    }
    
    int count() override {
        assert(head >= tail);
        int count = 0;
        count = (head - tail) % size;
        cout << "Count: " << count << endl;
        return count;
    }
    
    int space() override {
        assert (tail > head);
        int space = 0;
        space = (tail - (head + 1)) % size;
        
        cout << "head: " << head << "\t tail: " << tail <<endl;
        cout << "Space: " << space << endl;
        return space;
    }
    
    T get_item() override {
        assert(head != tail);
        T t = buffer[tail];
        tail = next(tail);
        return t;
    }
    
    void put_item(T item) override {
        assert(!is_full());
        buffer[head] = item;
        head = next(head);
    }
    
    int count_to_end() override {
        int count = 0;
        int end = size - tail;
        int n = (head + end) % size;
        count = n < end ? n : end;
        cout << "Count to end: " << count << endl;
        return count;
    }
    
    int space_to_end() override {
        cout << "Head: " << head << "\tTail: " << tail << endl;
        int space = 0;
        int end = size - 1 - head;
        int n = (end + tail) % size;
        space =  n <= end ? n : end+1;
        
        cout << "Space to end: " << space << endl;
        return space;
        
    }
    
    bool is_empty() override {
        return head == tail;
    }
    
    bool is_full() override {
        int next = 0;
        
        next = (head + 1) % size;
        
        bool full = (next == tail);
        cout << "Is full: " << full << endl;
        return full;
    }
    ~general_circ_buff() {
        delete []buffer;
    }
    
private:
    T* buffer;
    int head;
    int tail;
    int size;
    
    int next(int index) override {
        return(index + 1) % size;
    }
};
