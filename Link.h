
#ifndef PRACTICE_LINK_H
#define PRACTICE_LINK_H

template<typename E>
class Link {
public:
    E element;
    Link *next;

    Link(E value, Link *nextNode) {
        element = value;
        next = nextNode;
    }

    explicit Link(Link *nextNode) { next = nextNode; }
};

#endif