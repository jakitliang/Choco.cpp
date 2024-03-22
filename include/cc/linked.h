//
// Created by liangjie on 2024/3/18.
//

#ifndef CHOCO_CPP_LINKED_H
#define CHOCO_CPP_LINKED_H

#include "cc/list.h"
#include <iostream>

using namespace std;

namespace CC {
    template<typename T>
    struct Linked : IList<T> {
        struct Node {
            Node * next;
            T object;

            T & operator*() {
                return this->object;
            }

            const T & operator*() const {
                return this->object;
            }

            Node * Concat(const T * element) {
                next = Alloc(element);
                return next;
            }

            Node * Concat(T * element) {
                next = Alloc(element);
                return next;
            }

            static Node * Alloc(const T * element) {
                auto node = CC::Alloc<Node>();
                node->next = nullptr;
                CC::CopyConstruct<T>(&node->object, 0, element, 1);
                return node;
            }

            static Node * Alloc(T * element) {
                auto node = CC::Alloc<Node>();
                node->next = nullptr;
                CC::MoveConstruct<T>(&node->object, 0, element, 1);
                return node;
            }

            bool Release() {
                Destruct(&object);
                return CC::Release(this);
            }
        };

        Node * object;
        Node * lastObject;
        Size count;

        Linked() : object(nullptr), lastObject(nullptr), count(0) {}

        Linked(const Linked & list) : object(nullptr), lastObject(nullptr), count(0) {
            for (auto item : list) {
                this->Push(item);
            }
        }

        Linked(Linked && list) : object(list.object), lastObject(list.lastObject), count(list.count) {
            list.object = nullptr;
            list.lastObject = nullptr;
            list.count = 0;
        }

        ~Linked() {
            if (object != nullptr) {
                object->Release();
                object = nullptr;
            }

            if (lastObject != nullptr) {
                lastObject->Release();
                lastObject = nullptr;
            }

            count = 0;
        }

        template<typename E>
        void Insert(Size index, E * elements, Size cnt) {
            cout << sizeof(E) << endl;
            if (cnt < 1) return;

            if (index > count) {
                index = count; // Fix insert position
            }

            if (object == nullptr) {
                object = Node::Alloc(elements);
                elements += 1;
                lastObject = object;

                for (int i = 1; i < cnt; ++i) {
                    lastObject = lastObject->Concat(&elements[i]);
                }

            } else {
                if (index == count) {
                    // Append to end
                    for (int i = 0; i < cnt; ++i)
                        lastObject = lastObject->Concat(&elements[i]);

                } else {
                    // Insert to index
                    // Get last
                    Node * cur = object;
                    Node * next = nullptr;
                    for (int i = 0; i < index; ++i) {
                        cur = cur->next;
                    }
                    next = cur->next;
                    for (int i = 0; i < cnt; ++i) {
                        cur = cur->Concat(&elements[i]);
                    }
                    cur->next = next;
                }
            }

            count += cnt;
        }

        void CopyInsert(Size index, const T * elements, Size cnt) override {
            Insert(index, elements, cnt);
        }

        void MoveInsert(Size index, T * elements, Size cnt) override {
            Insert(index, elements, cnt);
        }

        void Delete(Size index, Size cnt) override {
            int i = 0;
            Node * cur = nullptr;
            Node * prev = nullptr;
            Node * next = nullptr;

            if (cnt < 1) return;
            if (index >= count) return;

            // Erase
            // Part 1             Part 2              // Part 3
            // data[0 .. index] + erase[0 .. count] + data[index .. last]
            // Part 1                                 // Part 3
            // data[0 .. index]         +             data[index .. last]
            auto indexEnd = index + cnt;

            cur = object;
            for (i = 0; i < index; ++i) {
                prev = cur;
                cur = cur->next;
            }

            for (i = 0; i < cnt; ++i) {
                next = cur->next;

                // Case 1: From head remove to the data.end
                // x: place to remove
                // |?|?|x|x|x|
                if (next == lastObject->next) {
                    cur->Release();

                    // Case 2: Remove all nodes
                    // x: place to remove
                    // |x|x|x|x|x|
                    if (prev == nullptr) {
                        object = lastObject = nullptr;
                        count = 0;
                        return;
                    }

                    lastObject = prev;
                    lastObject->next = nullptr;
                    count -= i + 1;
                    return;
                }

                cur->Release();
                cur = next;
            }

            // Case 3: From head remove to the data.end
            // x: place to remove
            // |x|x|?|?|?|
            if (prev == nullptr) {
                object = next;
                count -= i + 1;
                return;
            }

            // Case 4: From head remove to the data.end
            // x: place to remove
            // | |x|x|x| |
            prev->next = next;
            count -= i + 1;
        }

        Size Count() const override {
            return count;
        }

        T & operator[](Size index) override {
            if (index >= count) abort();
            auto cur = object;
            for (int i = 0; i < index; ++i) {
                cur = cur->next;
            }
            return **cur;
        }

        const T & operator[](Size index) const override {
            if (index >= count) abort();
            auto cur = object;
            for (int i = 0; i < index; ++i) {
                cur = cur->next;
            }
            return **cur;
        }

        struct Iterator {
            Iterator() : cur(nullptr), prev(nullptr) {};

            Iterator(const Iterator & iterator) : cur(iterator.cur), prev(iterator.prev) {}

            Iterator(Iterator && iterator) noexcept : cur(iterator.cur), prev(iterator.prev) {}

            explicit Iterator(Node * node) : cur(node) {}

            // Incrementing means going through the list
            Iterator & operator++() {
                if (cur != nullptr) {
                    prev = cur;
                    cur = cur->next;
                }

                return *this;
            }

            // Post fixing is bad in general, but it has its usages
            Iterator operator++(int) {
                Iterator temp(static_cast<Iterator &&>(*this)); // Make a copy of the iterator
                ++(*this);                                      // Increment
                return static_cast<Iterator &&>(temp);          // Return the copy before increment
            }

            bool operator!=(Iterator &other) {
                return this->cur != other.cur;
            }

            // It needs to be able to compare nodes
            bool operator!=(const Iterator &other) {
                return this->cur != other.cur;
            }

            // Return the data from the node (dereference operator)
            T & operator*() {
                return **this->cur;
            }

            const T & operator*() const {
                return **this->cur;
            }

            Node * prev = nullptr;
            Node * cur = nullptr;
        };

        Iterator begin() {
            return Iterator(this->object);
        }

        Iterator end() {
            return Iterator();
        }
    };
}

#endif //CHOCO_CPP_LINKED_H
