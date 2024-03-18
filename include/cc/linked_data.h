//
// Created by liangjie on 2024/3/18.
//

#ifndef CHOCO_CPP_LIST_DATA_H
#define CHOCO_CPP_LIST_DATA_H

#include "cc/zone.h"

namespace CC {
    template<typename T>
    struct LinkedData {
        struct Node {
            Node * next;

            T & operator*() {
                return *reinterpret_cast<T *>(this + 1);
            }

            void Concat(const T * elements, Size count) {
                for (int i = 0; i < count; ++i) {

                }
                CC::CopyConstruct<T>(reinterpret_cast<T *>(this + 1), 0, elements, 1);
            }

            void Concat(T * elements, Size count) {
                CC::MoveConstruct<T>(reinterpret_cast<T *>(this + 1), 0, elements, 1);
            }

            static Node * Alloc(const T * element) {
                auto ptr = Zone::Alloc(sizeof(Node) + sizeof(T));
                CC::CopyConstruct<T>(&(**reinterpret_cast<Node *>(ptr)), 0, element, 1);
                return reinterpret_cast<Node *>(ptr);
            }

            static Node * Alloc(T * element) {
                auto ptr = Zone::Alloc(sizeof(Node) + sizeof(T));
                CC::MoveConstruct<T>(&(**reinterpret_cast<Node *>(ptr)), 0, element, 1);
                return reinterpret_cast<Node *>(ptr);
            }

            Node * Retain() {
                return reinterpret_cast<Node *>(Zone::Retain(this));
            }

            bool Release() {
                return Zone::Release(this);
            }
        };

        Node * object;
        Size Count;

        LinkedData() : object(nullptr), Count(0) {}

        template<typename E>
        void Insert(Size index, E * elements, Size cnt) {
            if (cnt < 1) return;

            auto indexEnd = Count + cnt;

            if (index > Count) {
                index = Count; // Fix insert position
            }

            if (object == nullptr) {
                object = Node::Alloc(elements);
                elements += 1;
                cnt -= 1;
                auto current = object;

                object->Concat()
            }


        }
    };
}

#endif //CHOCO_CPP_LIST_DATA_H
