//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/5.
//

#ifndef CC_DEFINES_H
#define CC_DEFINES_H

#ifdef __cplusplus
#define CC_EXT     extern "C"
#define CC_C_BEGIN CC_EXT {
#define CC_C_END   };
#define CC_CPP
#else
#define CC_EXT
#define CC_C_BEGIN
#define CC_C_END
#endif

#ifdef _WIN32
#define CC_API __declspec(dllexport)
#define CC_DECL __cdecl
#define CC_ALIGN_DECL(align_, decl) __declspec(align(align_)) decl
#else
#define CC_API __attribute__((visibility("default")))
#define CC_DECL __cdecl
#define CC_ALIGN_DECL(align, decl) decl __attribute__ ((aligned(align)))
#endif

#define CC_ENUM(_type, _name) _type _name; enum

#ifdef NDEBUG
#define CC_ASSERT(condition) ((void) 0)
#define CC_STATIC_ASSERT(condition, ...) ((void) 0)
#else
#define CC_ASSERT(condition) assert(condition)
#define CC_STATIC_ASSERT(condition, ...) static_assert(condition, "" # __VA_ARGS__)
#endif

#ifdef _WIN64
#define CC_64
#elif defined(_WIN32)
#define CC_32
#else
#define CC_64
#endif

#endif //CC_DEFINES_H
