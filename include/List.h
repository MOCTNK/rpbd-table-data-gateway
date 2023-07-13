#pragma once
#include <iostream>
using namespace std;

template<typename T> class List {
    class Element {
    private:
        T data;
    public:
        Element *next = NULL;
        T getData() { return data; };
        void setData(T data) { this->data = data; };
    };
public:
    List();
    ~List();
    List<T>& operator=(List<T>& other) {
        this->clearList();
        for(int i = 0; i < other.getSize(); i++) {
            this->addElement(other.getDataById(i+1));
        }
        return *this;
    }
    void addElement(T data);
    void deleteElementById(int id);
    void deleteBegin();
    void deleteEnd();
    void clearList();
    int getSize();
    void getList();
    T getDataById(int id);
    bool isEmpty();
    Element *getElementById(int id) {
        Element *e = begin;
        for(int i = 0; i < id-1; i++) {
            e = e->next;
        }
        return e;
    };
private:
    int size = 0;
    Element *begin = NULL;
    Element *end = NULL;
};

template<typename T> List<T>::List()
{
    //ctor
}

template<typename T> List<T>::~List()
{
    clearList();
}

template<typename T> void List<T>::addElement(T data) {
    Element *e = new Element();
    e->setData(data);
    if(isEmpty()) {
        begin = e;
        end = e;
    } else {
        end->next = e;
        end = e;
    }
    size++;
}

template<typename T> void List<T>::deleteElementById(int id) {
    if(!isEmpty()) {
        Element *b = begin;
        Element *prev = begin;
        for(int i = 0; i < size; i++) {
            if(i+1 == id) {
                if(id == 1) {
                    begin = b->next;
                }
                if(id == size) {
                    end = prev;
                    end->next = NULL;
                }
                prev->next = b->next;
                delete b;
                size--;
                break;
            }
            prev = b;
            b = b->next;
        }
    }
}

template<typename T> void List<T>::deleteBegin() {
    deleteElementById(1);
}

template<typename T> void List<T>::deleteEnd() {
    deleteElementById(size);
}

template<typename T> void List<T>::clearList() {
    Element *b = begin;
    while(!isEmpty()) {
        Element *e = b->next;
        delete b;
        b = e;
        size--;
    }
    begin = NULL;
    end = NULL;
}

template<typename T> int List<T>::getSize() {
    return size;
}

template<typename T> void List<T>::getList() {
    cout << "List: ";
    if(!isEmpty()) {
        Element *b = begin;
        for(int i = 0; i < size; i++) {
            cout << b->getData() << " ";
            b = b->next;
        }
        cout << endl;
    } else {
        cout << "is empty!" << endl;
    }
}

template<typename T> T List<T>::getDataById(int id) {
    Element *e = getElementById(id);
    return e->getData();
}

template<typename T> bool List<T> ::isEmpty() {
    if(size <= 0) {
        return true;
    } else {
        return false;
    }
}
