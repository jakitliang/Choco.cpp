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

CC::Variant<void *>::~Variant() {
    Release(object);
    object = nullptr;
}

CC::Variant<void *>::Type CC::Variant<void *>::Element(Size index) {
    return (Byte *) object + SizeOfElement() * index;
}

CC::Variant<void *>::ImmutableType CC::Variant<void *>::Element(Size index) const {
    return (const Byte *) object + SizeOfElement() * index;
}

CC::Size CC::Variant<void *>::SizeOfElement() const {
    Page * page = nullptr;

    if (object == nullptr) return 0;

    page = reinterpret_cast<Page *>(object) - 1;

    return page->SizeOfObject;
}

CC::Size CC::Variant<void *>::Length() const {
    Page * page = nullptr;

    if (object == nullptr) return 0;

    page = reinterpret_cast<Page *>(object) - 1;

    return (UIntPtr) page->End - (UIntPtr) object;
}

CC::Size CC::Variant<void *>::Count() const {
    return Length() / SizeOfElement();
}

void CC::Variant<void *>::ReplaceElements(CC::Size index, ImmutableType elements, CC::Size count) {
    if (object == nullptr) return;

    memmove((Byte *) object + SizeOfElement() * index, elements, SizeOfElement() * count);
}

CC::Pointer &CC::Variant<void *>::operator=(Type const &p) {
    object = p;
    return *this;
}

CC::Variant<void *>::operator void *() {
    return object;
}

CC::Variant<void *>::operator const void *() const {
    return object;
}

CC::Variant<void *>::Type CC::Variant<void *>::Alloc(Size size, Size count) {
    auto page = static_cast<Page *>(malloc(sizeof(Page) + size * count + 1));
    Type begin = nullptr;

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

CC::Variant<void *>::Type CC::Variant<void *>::ReAlloc(Type object, Size count) {
    Page * page = nullptr;
    Type begin = nullptr;
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

CC::Variant<void *>::Type CC::Variant<void *>::Retain(Type object) {
    Page * page = nullptr;

    if (object == nullptr) return nullptr;

    page = reinterpret_cast<Page *>(object) - 1;
    page->Ref += 1;

    cout << "Retain <" << object << "> size[" << page->SizeOfObject << "] "
         << "count[" << ((UIntPtr) page->End - (UIntPtr) object) / page->SizeOfObject << "] "
         << "ref[" << page->Ref << "]" << endl;

    return object;
}

bool CC::Variant<void *>::Release(Type object) {
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

CC::Variant<void *>::Type CC::Variant<void *>::Element(Type object, Size index) {
    return (Byte *) object + SizeOfElement(object) * index;
}

CC::Variant<void *>::ImmutableType CC::Variant<void *>::Element(ImmutableType object, Size index) {
    return (const Byte *) object + SizeOfElement(object) * index;
}

CC::Size CC::Variant<void *>::SizeOfElement(ImmutableType object) {
    const Page * page = nullptr;

    if (object == nullptr) return 0;

    page = reinterpret_cast<const Page *>(object) - 1;

    return page->SizeOfObject;
}

CC::Size CC::Variant<void *>::Count(ImmutableType object) {
    return Length(object) / SizeOfElement(object);
}

CC::Size CC::Variant<void *>::Length(ImmutableType object) {
    const Page * page = nullptr;

    if (object == nullptr) return 0;

    page = reinterpret_cast<const Page *>(object) - 1;

    return (UIntPtr) page->End - (UIntPtr) object;
}

void CC::Variant<void *>::ReplaceElements(Type object, CC::Size index, ImmutableType elements, CC::Size count) {
    memmove((Byte *) object + SizeOfElement(object) * index,
            elements,
            SizeOfElement(object) * count);
}

void CC::Variant<void *>::BlockCopy(Type object, Size objectOffset, ImmutableType elements, Size elementsOffset, Size count) {
    memmove(Element(object, objectOffset), Element(elements, elementsOffset), count);
}
