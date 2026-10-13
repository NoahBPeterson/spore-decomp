// src/game/UTFSpore_Win32/Expression.cpp -- migrated from slice(s) s0083f140, s0083e1c0, s0083d3d0, s0083c900 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Expression.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cExpression.h"
#include "eastl/allocator.h"
#include "EA/ArgScript/cExprFunction.h"
#include "SP/cHashFunction.h"
#include <math.h>
#include "EA/ArgScript/cIParser.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" __declspec(dllimport) int   __cdecl isspace(int);
extern char gEmptyString[];

// ---- items of slice s0083c900 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" __declspec(dllimport) int   __cdecl isspace(int);
extern char gEmptyString[];
// Stub types of slice s0083c900 renamed `*_s0083_c900`: the module TU now also includes the canonical
// eastl/allocator.h and eastl/string.h (via later slices), so the slice's local stubs must not redefine
// eastl::allocator / eastl::string8. Pure rename: layout and codegen are unchanged.
namespace eastl {
struct allocator_s0083_c900 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0083_c900 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator_s0083_c900 mAllocator;
    string8_s0083_c900() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void assign(const char* first, const char* last);   // 0x00454cb0
    void assign(const char* p);                         // 0x006a4380
    void RangeInitialize(unsigned n);                   // 0x00475ab0
    string8_s0083_c900(const string8_s0083_c900& x);     // 0x0057cb10
    ~string8_s0083_c900();
};
}
void  __cdecl ThrowCError(void* out, const char* fmt, ...);                // 0x0052df30
float __cdecl EvalRealExpression(void* self, const char** p);              // 0x0083e470
struct PairCtorStub { void CtorA(const eastl::string8_s0083_c900* s, int** ref); void CtorB(const void* src); };
struct ExprStub { void EvalRealParentheses4(const char** p, float* a, float* b); };
// ---- items of slice s0083c900 end

// ---- items of slice s0083d3d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00f47380(void* p);                          // operator delete(void*)
extern "C" double __cdecl asin(double);
extern "C" double __cdecl acos(double);
extern "C" double __cdecl atan(double);
extern "C" double __cdecl atan2(double, double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl tan(double);
extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl exp(double);
extern "C" double __cdecl log(double);
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl pow(double, double);
#pragma intrinsic(asin, acos, atan, atan2, sin, cos, tan, sqrt, exp, log, fabs, pow)
namespace eastl {
struct allocator_s0083_d3d0 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0083_d3d0 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator_s0083_d3d0 mAllocator;
    string8_s0083_d3d0() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void assign(const char* first, const char* last);   // 0x00454cb0
    void assign(const char* p);                         // 0x006a4380
    void RangeInitialize(unsigned n);                   // 0x00475ab0
    string8_s0083_d3d0(const string8_s0083_d3d0& x);                          // 0x0057cb10
    string8_s0083_d3d0(const char* first, unsigned n, const allocator_s0083_d3d0& a);   // 0x005e96a0
    ~string8_s0083_d3d0() { if ((mpCapacity - mpBegin) > 1 && mpBegin) FUN_00f47380(mpBegin); }
};
}
extern "C" void  __cdecl DiscardWhiteSpace(const char** p);            // 0x0083ce90
void  __cdecl DoFreeNodesExpr(void* bucketArray, int n);    // 0x0083dd00
int   __cdecl EvalIntExpression(void* self, const char** p); // 0x0083eb00
namespace EA {
namespace ArgScript {
struct cExprFunction_s0083_d3d0 { virtual float Eval(const char** p, void* expr) = 0; };
}
}
namespace EA {
namespace ArgScript {
struct cExpression_s0083_d3d0 {
    struct Node { eastl::string8_s0083_d3d0 key; cExprFunction_s0083_d3d0* fn; Node* next; };
    void* mAlloc;                                               // +0
    Node** mpBucketArray;                                       // +4
    unsigned mnBucketCount;                                     // +8
    unsigned mnElementCount;                                    // +0xc
    Node** find(Node** out, const eastl::string8_s0083_d3d0& key);         // 0x007e2ea0 (hashtable::find)
    float EvalRealParentheses2(const char** p);                 // 0x0083e560
    void  EvalRealParentheses(const char** p, float* a, float* b);  // 0x0083d2f0
    float EvalRealNumber(const char** p);                       // 0x0083d3d0
    int   EvalIntParentheses(const char** p);                   // 0x0083db70
    void  EvalString(const char** p, eastl::string8_s0083_d3d0* out);      // 0x0083dc00
    long double EvalSignedRealNumber(const char** p);           // 0x0083dd70
    long double EvalRealFactor(const char** p);                 // 0x0083e160
};
}
}
// ---- items of slice s0083d3d0 end

// ---- items of slice s0083e1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line); // 0x00f473a0
extern "C" __declspec(dllimport) void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern void* gEmptyBucketArray[];       // 0x0154df28
extern float gOne;                      // 0x01485720
extern float gTwo;                      // 0x01470f1c
typedef unsigned long ulong32;
struct cError {
    cError(const char* fmt, ...);          // 0x0052df30 (variadic ctor, this pushed)
    cError(const cError&);
};
static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";
namespace eastl {
struct allocator_s0083_e1c0 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0083_e1c0 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator_s0083_e1c0 mAllocator;
    string8_s0083_e1c0() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    string8_s0083_e1c0(const char* first, const char* last) {
        unsigned n = (unsigned)(last - first) + 1;
        if (n <= 1) {
            mpBegin = gEmptyString;
            mpCapacity = gEmptyString + 1;
        } else {
            mpBegin = (char*)EASTL_allocator_allocate(n, g_allocName, 0, 0, g_allocFile, 0xd1);
            mpCapacity = mpBegin + n;
        }
        memcpy(mpBegin, first, (unsigned)(last - first));
        mpEnd = mpBegin + (last - first);
        *mpEnd = 0;
    }
    ~string8_s0083_e1c0(); // 0x00530670
};
}
struct cExpression;
struct ExprIter { void* mpNode; void* mpBucket; };
struct cExpression {
    char pad0[0x04];             // +0x00
    void** mpBucketArray;        // +0x04
    int    mnBucketCount;        // +0x08
    int    mnElementCount;       // +0x0c
    float  mfMaxLoadFactor;      // +0x10
    float  mfGrowthFactor;       // +0x14
    int    pad18;                // +0x18
    char pad1c[0x04];            // +0x1c

    cExpression();                                    // 0x0083e430
    ExprIter find(const eastl::string8_s0083_e1c0& key) const;   // 0x007e2ea0

    long double EvalRealNumber(const char** p);         // 0x0083d3d0
    long double EvalSignedRealNumber(const char** p);   // 0x0083dd70
    long double EvalRealFactor(const char** p);         // 0x0083e160
    int  EvalIntParentheses(const char** p);            // 0x0083db70
    unsigned char EvalChar(const char** p);             // 0x0083f480

    float EvalRealTerm(const char** p);                 // 0x0083e1c0
    float EvalRealExpression(const char** p);           // 0x0083e470
    float ParseReal(const char* s);                     // 0x0083e4f0
    float EvalRealParentheses2(const char** p);         // 0x0083e560
    ulong32 EvalIntNumber(const char** p);              // 0x0083e5f0
    int  EvalSignedIntNumber(const char** p);           // 0x0083e9d0
    int  EvalIntFactor(const char** p);                 // 0x0083ea10
    int  EvalIntTerm(const char** p);                   // 0x0083ea70
    int  EvalIntExpression(const char** p);             // 0x0083eb00
    unsigned char EvalBool(const char** p);             // 0x0083eb70
    int  ParseInt(const char* s);                       // 0x0083edc0
    unsigned EvalRelExpression(const char** p);         // 0x0083ee30
    unsigned EvalBoolFactor(const char** p);            // 0x0083efd0
};
// ---- items of slice s0083e1c0 end

// ---- items of slice s0083f140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int EvalBoolExpression(const char** p);      // 0x0083f2e0
namespace EA {
namespace ArgScript {
struct cExpression_s0083_f140 { int EvalChar(const char** p); };   // 0x0083f480 (stub receiver)
}
}
// ---- items of slice s0083f140 end

// @ 0x0083ce90
extern "C" void DiscardWhiteSpace(const char** p)
{
    while (isspace((unsigned char)**p))
        ++*p;
}








// @ 0x0083ced0
void ReleaseRefCount(int** p)
{
    int* obj = *p;
    if (obj) {
        if (--obj[1] == 0)
            EASTL_allocator_deallocate(obj);
    }
}








// @ 0x0083cef0
void PairCtorStub::CtorA(const eastl::string8_s0083_c900* s, int** ref)
{
    void* self = this;
    eastl::string8_s0083_c900* str = (eastl::string8_s0083_c900*)self;
    str->mpBegin = 0; str->mpEnd = 0; str->mpCapacity = 0;
    int len = (int)(s->mpEnd - s->mpBegin);
    str->RangeInitialize((unsigned)(len + 1));
    for (int i = 0; i < len; ++i) str->mpBegin[i] = s->mpBegin[i];
    str->mpEnd = str->mpBegin + len;
    *str->mpEnd = 0;
    int* obj = *ref;
    *(int**)((char*)self + 0x10) = obj;
    if (obj) ++obj[1];
}








// @ 0x0083d020
void PairCtorStub::CtorB(const void* src)
{
    void* self = this;
    eastl::string8_s0083_c900* str = (eastl::string8_s0083_c900*)self;
    const eastl::string8_s0083_c900* s = (const eastl::string8_s0083_c900*)src;
    str->mpBegin = 0; str->mpEnd = 0; str->mpCapacity = 0;
    int len = (int)(s->mpEnd - s->mpBegin);
    str->RangeInitialize((unsigned)(len + 1));
    for (int i = 0; i < len; ++i) str->mpBegin[i] = s->mpBegin[i];
    str->mpEnd = str->mpBegin + len;
    *str->mpEnd = 0;
    int* obj = *(int**)((char*)src + 0x10);
    *(int**)((char*)self + 0x10) = obj;
    if (obj) ++obj[1];
}








// @ 0x0083d080
void __cdecl PairStringExprDtor(void* self)
{
    int* obj = *(int**)((char*)self + 0x10);
    if (obj) {
        if (--obj[1] == 0)
            EASTL_allocator_deallocate(obj);
    }
    eastl::string8_s0083_c900* str = (eastl::string8_s0083_c900*)self;
    if ((str->mpCapacity - str->mpBegin) > 1 && str->mpBegin)
        EASTL_allocator_deallocate(str->mpBegin);
}








// @ 0x0083d240
void EvalExpectCharThrow(const char** p, char c)
{
    DiscardWhiteSpace(p);
    if (**p != c) {
        char buf[16];
        ThrowCError(buf, "Expected '%c'", (int)c);
        _CxxThrowException(buf, (_ThrowInfo*)0);
    }
    ++*p;
}








// @ 0x0083d290
unsigned char EvalContinueChar(const char** p, char c)
{
    DiscardWhiteSpace(p);
    char ch = **p;
    if (ch == 0)
        return 0;
    if (ch != c) {
        char buf[16];
        ThrowCError(buf, "Expected '%c'", (int)c);
        _CxxThrowException(buf, (_ThrowInfo*)0);
    }
    ++*p;
    return 1;
}








// @ 0x0083d2f0
void ExprStub::EvalRealParentheses4(const char** p, float* a, float* b)
{
    void* self = this;
    EvalExpectCharThrow(p, '(');
    *a = EvalRealExpression(self, p);
    EvalExpectCharThrow(p, ',');
    *b = EvalRealExpression(self, p);
    EvalExpectCharThrow(p, ')');
}







// @ 0x0083db70
int EA::ArgScript::cExpression_s0083_d3d0::EvalIntParentheses(const char** p)
{
    DiscardWhiteSpace(p);
    if (**p != '(') {
        char buf[16];
        ThrowCError(buf, "Expected '%c'", 0x28);
    }
    ++*p;
    int v = EvalIntExpression(this, p);
    DiscardWhiteSpace(p);
    if (**p != ')') {
        char buf[16];
        ThrowCError(buf, "Expected '%c'", 0x29);
    }
    ++*p;
    return v;
}






// @ 0x0083dd00
void __cdecl DoFreeNodesExpr(void* bucketArray, int bucketCount)
{
    for (int i = 0; i < bucketCount; ++i) {
        char* node = *(char**)((char*)bucketArray + i * 4);
        while (node) {
            char* next = *(char**)(node + 0x14);
            int* ref = *(int**)(node + 0x10);
            if (ref) { if (--ref[1] == 0) EASTL_allocator_deallocate(ref); }
            eastl::string8_s0083_d3d0* s = (eastl::string8_s0083_d3d0*)node;
            if ((s->mpCapacity - s->mpBegin) > 1 && s->mpBegin)
                EASTL_allocator_deallocate(s->mpBegin);
            EASTL_allocator_deallocate(node);
            node = next;
        }
        *(void**)((char*)bucketArray + i * 4) = 0;
    }
}






// @ 0x0083e140
void __fastcall ExprTableClear(void* self)
{
    DoFreeNodesExpr(*(void**)((char*)self + 4), *(int*)((char*)self + 8));
    *(int*)((char*)self + 0xc) = 0;
}





// @ 0x0083e1c0
float EA::ArgScript::cExpression::EvalRealTerm(char const *& p)
{
    float acc = (float)EvalRealFactor(p);
    for (;;) {
        while (isspace((unsigned char)*p))
            ++p;
        char c = *p;
        if (c == '%') {
            ++p;
            while (isspace((unsigned char)*p))
                ++p;
            float d;
            if (*p == '+') { ++p; d = (float)EvalSignedRealNumber(p); }
            else if (*p == '-') { ++p; d = -(float)EvalSignedRealNumber(p); }
            else d = (float)EvalRealNumber(p);
            while (isspace((unsigned char)*p))
                ++p;
            if (*p == '^') {
                ++p;
                d = (float)pow((double)d, (double)EvalRealFactor(p));
            }
            float q = acc / d;
            float r = (float)(floor((double)q) * (double)d);
            acc = acc - r;
        } else if (c == '*') {
            ++p;
            while (isspace((unsigned char)*p))
                ++p;
            float d;
            if (*p == '+') { ++p; d = (float)EvalSignedRealNumber(p); }
            else if (*p == '-') { ++p; d = -(float)EvalSignedRealNumber(p); }
            else d = (float)EvalRealNumber(p);
            while (isspace((unsigned char)*p))
                ++p;
            if (*p == '^') {
                ++p;
                d = (float)pow((double)d, (double)EvalRealFactor(p));
            }
            acc = acc * d;
        } else if (c == '/') {
            ++p;
            float d = (float)EvalSignedRealNumber(p);
            while (isspace((unsigned char)*p))
                ++p;
            if (*p == '^') {
                ++p;
                d = (float)pow((double)d, (double)EvalRealFactor(p));
            }
            acc = acc / d;
        } else {
            return acc;
        }
    }
}



// @ 0x0083e430
cExpression::cExpression()
: mfMaxLoadFactor(gOne), mfGrowthFactor(gTwo) {
    mnBucketCount = 1;
    mpBucketArray = gEmptyBucketArray;
    mnElementCount = 0;
    pad18 = 0;
}



// @ 0x0083e470
float EA::ArgScript::cExpression::EvalRealExpression(char const *& p)
{
    float result = EvalRealTerm(p);
    for (;;) {
        while (isspace((unsigned char)*p))
            ++p;
        switch (*p) {
        case '+':
            ++p;
            result = result + (float)EvalRealTerm(p);
            break;
        case '-':
            ++p;
            result = result - (float)EvalRealTerm(p);
            break;
        default:
            return result;
        }
    }
}



// @ 0x0083e4f0
float cExpression::ParseReal(const char* s)
{
    if (*s == 0)
        throw cError("empty expression");
    float v = EvalRealExpression(&s);
    if (*s != 0)
        throw cError("Garbage at end of real expression");
    return v;
}



// @ 0x0083e560
float cExpression::EvalRealParentheses2(const char** p)
{
    DiscardWhiteSpace(p);
    if (**p != '(')
        throw cError("Expected '%c'", '(');
    ++*p;
    float v = EvalRealExpression(p);
    DiscardWhiteSpace(p);
    if (**p != ')')
        throw cError("Expected '%c'", ')');
    ++*p;
    return v;
}



// @ 0x0083ea10
int cExpression::EvalIntFactor(const char** p)
{
    int base = EvalSignedIntNumber(p);
    DiscardWhiteSpace(p);
    if (**p != '^')
        return base;
    ++*p;
    int exp = EvalIntFactor(p);
    int result = 1;
    for (; exp > 0; exp >>= 1) {
        if (exp & 1)
            result *= base;
        base *= base;
    }
    return result;
}



// @ 0x0083ea70
int EA::ArgScript::cExpression::EvalIntTerm(char const *& p)
{
    int result = EvalIntFactor(p);
    for (;;) {
        while (isspace((unsigned char)*p))
            ++p;
        switch (*p) {
        case '%':
            ++p;
            result %= EvalIntFactor(p);
            break;
        case '*':
            ++p;
            result *= EvalIntFactor(p);
            break;
        case '/':
            ++p;
            result /= EvalIntFactor(p);
            break;
        default:
            return result;
        }
    }
}



// @ 0x0083eb00
int EA::ArgScript::cExpression::EvalIntExpression(char const *& p)
{
    int result = EvalIntTerm(p);
    for (;;) {
        while (isspace((unsigned char)*p))
            ++p;
        switch (*p) {
        case '+':
            ++p;
            result += EvalIntTerm(p);
            break;
        case '-':
            ++p;
            result -= EvalIntTerm(p);
            break;
        default:
            return result;
        }
    }
}



// @ 0x0083edc0
int cExpression::ParseInt(const char* s)
{
    if (*s == 0)
        throw cError("empty expression");
    int v = EvalIntExpression(&s);
    if (*s != 0)
        throw cError("Garbage at end of integer expression");
    return v;
}



// @ 0x0083ee30
unsigned cExpression::EvalRelExpression(const char** p)
{
    unsigned v = EvalBool(p);
    for (;;) {
        while (isspace((unsigned char)**p))
            ++*p;
        switch (**p) {
        case '!':
            ++*p;
            if (**p != '=')
                throw cError("Illegal operator %c%c", '!', **p);
            ++*p;
            v = (unsigned)(v != EvalRelExpression(p));
            break;
        case '<':
            ++*p;
            if (**p == '=') {
                ++*p;
                v = (unsigned)((int)v <= (int)EvalRelExpression(p));
            } else {
                v = (unsigned)((int)v < (int)EvalRelExpression(p));
            }
            break;
        case '>':
            ++*p;
            if (**p == '=') {
                ++*p;
                v = (unsigned)((int)EvalRelExpression(p) <= (int)v);
            } else {
                v = (unsigned)((int)EvalRelExpression(p) < (int)v);
            }
            break;
        case '=':
            ++*p;
            if (**p != '=')
                throw cError("Illegal operator %c%c", '=', **p);
            ++*p;
            v = (unsigned)(v == EvalRelExpression(p));
            break;
        default:
            return v;
        }
    }
}


// @ 0x0083f480
int EA::ArgScript::cExpression_s0083_f140::EvalChar(const char** p)
{
    DiscardWhiteSpace(p);
    if (**p != '(')
        throw cError("Expected '%c'", '(');
    ++*p;
    int v = EvalBoolExpression(p);
    DiscardWhiteSpace(p);
    if (**p != ')')
        throw cError("Expected '%c'", ')');
    ++*p;
    return v;
}

// @ 0x0083f510
bool __cdecl ParseBool(const char* s)
{
    if (*s == 0)
        throw cError("empty expression");
    int v = EvalBoolExpression(&s);
    if (*s != 0)
        throw cError("Garbage at end of bool expression");
    return v != 0;
}
