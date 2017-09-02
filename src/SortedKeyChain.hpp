/* 
 * File:   SortedKeyChain.hpp
 * Author: ANTOINE
 *
 * Created on 22 juin 2016, 20:33
 */
#pragma once

#ifndef SORTEDKEYCHAIN_HPP
#define	SORTEDKEYCHAIN_HPP

#ifndef TYPES_H
#include "Types.h"
#endif

class KeyLink {
public:

    KeyLink(float key, void* value, KeyLink* next) {
        this->key = key;
        this->value = value;
        this->next = next;
    }

    ~KeyLink() {
        delete next;
    }
    float key;
    void* value;
    KeyLink* next;
};

class SortedKeyChain {
public:

    SortedKeyChain() {
        first = null;
        count = 0;
    }

    ~SortedKeyChain() {
        clear();
        std::cout << "SortedKeyChain deleted." << std::endl;
    }

    void add(float key, void* value) {
        if (first == null) // empty, set as first
            first = new KeyLink(key, value, null);
        else if (first->key < key) // smaller than first, set as first
            first = new KeyLink(key, value, first);
        else {
            KeyLink* current = first;
            while (current->next != null) {
                if (current->next->key < key)
                    break;
                current = current->next;
            }
            current->next = new KeyLink(key, value, current->next);
        }
        count++;
    }

    void clear() {
        delete first;
        first = null;
        count = 0;
    }
    KeyLink* first;
    UInt count;
};

#endif	/* SORTEDKEYCHAIN_HPP */

