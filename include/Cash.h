#pragma once
#include <iostream>
using namespace std;

template<typename T> class Cash {
    class Element {
    private:
        T data;
    public:
        Element *next = NULL;
        Element *prev = NULL;
        T getData() { return data; };
        void setData(T data) { this->data = data; };
    };
public:
    Cash();
    ~Cash();
    void addToEnd(T data);
    void addToBegin(T data);
    int getSize();
    void getCash();
    T getNow();
    bool isNextNull();
    bool isPrevNull();
    void Next();
    void Prev();
    bool isEmpty();
    void delToBegin();
    void delToEnd();
    void toBegin();
    void clear();
    T getElementDataById(int id);
    void setElementDataById(int id, T data);
private:
    Element *begin = NULL;
    Element *end = NULL;
    Element *now = NULL;
    int size = 0;
    int maxSize = 3;
};

template<typename T> Cash<T>::Cash()
{
    //ctor
}

template<typename T> Cash<T>::~Cash()
{
    clear();
}

template<typename T> void Cash<T>::addToEnd(T data) {
    Element *e = new Element();
    e->setData(data);
    if(isEmpty()) {
        begin = e;
        end = e;
    } else {
        if(size >= maxSize) {
            delToBegin();
        }
        end->next = e;
        e->prev = end;
        end = e;
    }
    size++;
    now = e;
}

template<typename T> void Cash<T>::addToBegin(T data) {
    Element *e = new Element();
    e->setData(data);
    if(isEmpty()) {
        begin = e;
        end = e;
    } else {
        if(size >= maxSize) {
            delToEnd();
        }
        begin->prev = e;
        e->next = begin;
        begin = e;
    }
    size++;
    now = e;
}

template<typename T> void Cash<T>::delToBegin() {
    if(!isEmpty()) {
        Element *e = begin->next;
        delete begin;
        begin = e;
        if(size == 1) {
            end = NULL;
        }
        if(begin != NULL) {
            begin->prev = NULL;
        }
        size--;
    }
}

template<typename T> void Cash<T>::delToEnd() {
    if(!isEmpty()) {
        Element *e = end->prev;
        delete end;
        end = e;
        if(size == 1) {
            begin = NULL;
        }
        if(end != NULL) {
            end->next = NULL;
        }
        size--;
    }
}

template<typename T> int Cash<T>::getSize() {
    return size;
}

template<typename T> void Cash<T>::getCash() {
    cout << "Cash: ";
    if(!isEmpty()) {
        Element *b = begin;
        for(int i = 0; i < size; i++) {
            //cout << b->getData() << " ";
            cout << i << " ";
            b = b->next;
        }
        cout << endl;
    } else {
        cout << "is empty!" << endl;
    }
}

template<typename T> T Cash<T>::getNow() {
    return now->getData();
}

template<typename T> bool Cash<T>::isNextNull() {
    if(now->next == NULL) {
        return true;
    } else {
        return false;
    }
}

template<typename T> bool Cash<T>::isPrevNull() {
    if(now->prev == NULL) {
        return true;
    } else {
        return false;
    }
}

template<typename T> void Cash<T>::Next() {
    if(now->next != NULL) {
        now = now->next;
    }
}

template<typename T> void Cash<T>::Prev() {
    if(now->prev != NULL) {
        now = now->prev;
    }
}

template<typename T> bool Cash<T>::isEmpty() {
    if(size <= 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T> void Cash<T>::toBegin() {
    if(begin != NULL) {
        now = begin;
    }
}

template<typename T> void Cash<T>::clear() {
    Element *b = begin;
    while(!isEmpty()) {
        Element *e = b->next;
        delete b;
        b = e;
        size--;
    }
    begin = NULL;
    end = NULL;
    now = NULL;
}

template<typename T> T Cash<T>::getElementDataById(int id) {
    Element *b = begin;
    for(int i = 0; i < size; i++) {
        if(i == id) {
            break;
        }
        b = b->next;
    }
    return b->getData();
}

template<typename T> void Cash<T>::setElementDataById(int id, T data) {
    Element *b = begin;
    for(int i = 0; i < size; i++) {
        if(i == id) {
            break;
        }
        b = b->next;
    }
    b->setData(data);
}
