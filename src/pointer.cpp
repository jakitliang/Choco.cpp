//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/7.
//

#include "cc/pointer.h"
#include "cc/intptr.h"

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

using Page = struct {
    void *End;
    CC::Size SizeOfObject;
    CC::Size Ref;
    CC::Byte Flags[8];
};

CC::Pointer::Pointer(void *const &p) {
    ptr = p;
}

CC::Pointer::Pointer(CC::Object *const &object) {
    ptr = object;
}

void * CC::Pointer::Element(Size index) {
    return (Byte *) ptr + SizeOfElement() * index;
}

const void * CC::Pointer::Element(Size index) const {
    return (const Byte *) ptr + SizeOfElement() * index;
}

CC::Size CC::Pointer::SizeOfElement() const {
    Page * page = nullptr;

    if (ptr == nullptr) return 0;

    page = reinterpret_cast<Page *>(ptr) - 1;

    return page->SizeOfObject;
}

CC::Size CC::Pointer::Length() const {
    Page * page = nullptr;

    if (ptr == nullptr) return 0;

    page = reinterpret_cast<Page *>(ptr) - 1;

    return (UIntPtr) page->End - (UIntPtr) ptr;
}

CC::Size CC::Pointer::Count() const {
    return Length() / SizeOfElement();
}

void CC::Pointer::ReplaceElements(CC::Size index, const void *elements, CC::Size count) {
    if (ptr == nullptr) return;

    memmove((Byte *) ptr + SizeOfElement() * index, elements, SizeOfElement() * count);
}

CC::Pointer &CC::Pointer::operator=(void *const &p) {
    ptr = p;
    return *this;
}

CC::Pointer::operator void *() {
    return ptr;
}

CC::Pointer::operator const void *() const {
    return ptr;
}

void * CC::Pointer::Alloc(Size size, Size count) {
    auto page = static_cast<Page *>(malloc(sizeof(Page) + size * count + 1));
    void * begin = nullptr;

    if (page == nullptr) return nullptr;

    begin = page + 1;
    page->End = (Byte *) begin + size * count;
    page->SizeOfObject = size;
    page->Ref = 1;

    memset(page->End, 0, 1);
    memset(page->Flags, 0, sizeof(page->Flags));

    cout << "Alloc <" << begin << "> size[" << page->SizeOfObject << "] "
         << "count[" << ((UIntPtr) page->End - (UIntPtr) begin) / page->SizeOfObject << "] "
         << "ref[" << page->Ref << "]" << endl;

    return begin;
}

void * CC::Pointer::ReAlloc(void * object, Size count) {
    Page * page = nullptr;
    void * begin = nullptr;
    Page * newPage = nullptr;

    if (object == nullptr) return nullptr;

    begin = object;
    page = static_cast<Page *>(begin) - 1;
    newPage = static_cast<Page *>(realloc(page, sizeof(Page) + page->SizeOfObject * count + 1));

    if (newPage == nullptr) return nullptr;

    cout << "ReAlloc <" << begin << "> -> ";

    page = newPage;
    begin = page + 1;
    page->End = (Byte *) begin + page->SizeOfObject * count;

    memset(page->End, 0, 1);

    cout << "<" << begin << "> size[" << page->SizeOfObject << "] "
         << "count[" << ((UIntPtr) page->End - (UIntPtr) begin) / page->SizeOfObject << "] "
         << "ref[" << page->Ref << "]" << endl;

    return begin;
}

void * CC::Pointer::Retain(void * object) {
    Page * page = nullptr;

    if (object == nullptr) return nullptr;

    page = reinterpret_cast<Page *>(object) - 1;
    page->Ref += 1;

    cout << "Retain <" << object << "> size[" << page->SizeOfObject << "] "
         << "count[" << ((UIntPtr) page->End - (UIntPtr) object) / page->SizeOfObject << "] "
         << "ref[" << page->Ref << "]" << endl;

    return object;
}

bool CC::Pointer::Release(void * object) {
    Page * page = nullptr;

    if (object == nullptr) return false;

    page = static_cast<Page *>(object) - 1;

    if (page->Ref == 0) return false;

    page->Ref -= 1;

    cout << "Release <" << object << "> size[" << page->SizeOfObject << "] "
         << "count[" << ((UIntPtr) page->End - (UIntPtr) object) / page->SizeOfObject << "] "
         << "ref[" << page->Ref << "]" << endl;

    if (page->Ref != 0) return false;

    free(page);

    return true;
}

void * CC::Pointer::Element(void * object, Size index) {
    return (Byte *) object + SizeOfElement(object) * index;
}

const void * CC::Pointer::Element(const void * object, Size index) {
    return (const Byte *) object + SizeOfElement(object) * index;
}

CC::Size CC::Pointer::SizeOfElement(const void * object) {
    const Page * page = nullptr;

    if (object == nullptr) return 0;

    page = reinterpret_cast<const Page *>(object) - 1;

    return page->SizeOfObject;
}

CC::Size CC::Pointer::Count(const void * object) {
    return Length(object) / SizeOfElement(object);
}

CC::Size CC::Pointer::Length(const void * object) {
    const Page * page = nullptr;

    if (object == nullptr) return 0;

    page = reinterpret_cast<const Page *>(object) - 1;

    return (UIntPtr) page->End - (UIntPtr) object;
}

void CC::Pointer::ReplaceElements(void *object, CC::Size index, const void *elements, CC::Size count) {
    memmove((Byte *) object + SizeOfElement(object) * index,
            elements,
            SizeOfElement(object) * count);
}
