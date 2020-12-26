#ifndef PRACTICE_LSTACK_H
#define PRACTICE_LSTACK_H

#include <stdio.h>
#include "Link.h"

template<typename E>
class LStack {
private:
    Link<E> *top;
    int size;
public:
    LStack() {
        top = nullptr;
        size = 0;
    }

    void clear() {
        while (top != nullptr) {
            Link<E> *temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }

    void push(E it) {
        Link<E> *node;
        node = new Link<E>(it, top);
        top = node;
        size++;
    }

    void pop() {
        if (top != nullptr) {
            Link<E> *temp = top;
            top = top->next;
            delete temp;
            size--;
        }
    }

    E topValue() {
        if (top != nullptr) {
            return top->element;
        } else {
            return NULL;
        }
    }

    int length() {
        return size;
    }
};

#endif
