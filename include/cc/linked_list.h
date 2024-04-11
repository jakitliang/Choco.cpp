//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/18.
//

#ifndef CHOCO_CPP_LINKED_LIST_H
#define CHOCO_CPP_LINKED_LIST_H

#include "cc/list.h"
#include <iostream>

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

        ~Linked() override {
            if (object == nullptr) return;
            Node * cur = object;
            Node * next;
            for (int i = 0; i < count; ++i) {
                next = cur->next;
                cur->Release();
                cur = next;
            }
            lastObject = nullptr;

            count = 0;
        }

        template<typename E>
        void Insert(Size index, E * elements, Size cnt) {
            int i = 0;
            if (cnt < 1) return;

            if (index > count) {
                index = count; // Fix insert position
            }

            if (object == nullptr) {
                object = Node::Alloc(elements);
                lastObject = object;

                for (i = 1; i < cnt; ++i) {
                    lastObject = lastObject->Concat(&elements[i]);
                }

            } else {
                if (index == count) {
                    // Append to end
                    for (i = 0; i < cnt; ++i)
                        lastObject = lastObject->Concat(&elements[i]);

                } else {
                    // Insert to index
                    // Get last
                    Node * prev = nullptr;
                    Node * next = object;

                    for (i = 0; i < index; ++i) {
                        prev = next;
                        next = next->next;
                    }

                    i = 0;

                    if (prev == nullptr) {
                        object = Node::Alloc(elements);
                        prev = object;
                        i = 1;
                    }

                    for (; i < cnt; ++i) {
                        prev = prev->Concat(&elements[i]);
                    }

                    prev->next = next;
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

        T & Last() override {
            if (count == 0) abort();
            return **lastObject;
        }

        void Delete(Size index, Size cnt) override {
            int i = 0;
            Node * cur = nullptr;
            Node * prev = nullptr;
            Node * next = nullptr;

            if (cnt < 1) return;
            if (index >= count) return;

            auto indexEnd = index + cnt;
            count = indexEnd >= count ? index : count - cnt;

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
                        return;
                    }

                    lastObject = prev;
                    lastObject->next = nullptr;
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
                return;
            }

            // Case 4: From head remove to the data.end
            // x: place to remove
            // | |x|x|x| |
            prev->next = next;
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

            Iterator(Iterator && iterator) noexcept : cur(iterator.cur), prev(iterator.prev) {
                iterator.cur = nullptr;
                iterator.prev = nullptr;
            }

            explicit Iterator(Node * node) : cur(node), prev(nullptr) {}

            Iterator & operator=(const Iterator & iterator) {
                if (this == &iterator) return *this;

                cur = iterator.cur;
                prev = iterator.prev;
                return *this;
            }

            Iterator & operator=(Iterator && iterator) noexcept {
                if (this == &iterator) return *this;

                cur = iterator.cur;
                prev = iterator.prev;

                iterator.cur = nullptr;
                iterator.prev = nullptr;

                return *this;
            }

            // Incrementing means going through the list
            Iterator & operator++() {
                if (cur == nullptr) return *this;

                prev = cur;
                cur = cur->next;

                return *this;
            }

            Iterator & operator+(Size index) {
                if (cur == nullptr) return *this;

                for (Size i = 0; i < index; ++i) {
                    if (cur == nullptr) break;

                    prev = cur;
                    cur = cur->next;
                }

                return *this;
            }

            // It needs to be able to compare nodes
            bool operator!=(const Iterator &other) {
                return this->cur != other.cur;
            }

            bool operator==(const Iterator &other) {
                return this->cur == other.cur;
            }

            // Return the data from the node (dereference operator)
            T & operator*() {
                return **this->cur;
            }

            const T & operator*() const {
                return **this->cur;
            }

            template<typename OS>
            friend OS & operator<<(OS & os, const Iterator & iterator) {
                return os << *iterator;
            }

            Node * prev;
            Node * cur;
        };

        Iterator begin() {
            return Iterator(this->object);
        }

        Iterator end() {
            return Iterator();
        }
    };

    template<typename T>
    using LinkedList = List<Linked<T>>;
}

#endif //CHOCO_CPP_LINKED_LIST_H
