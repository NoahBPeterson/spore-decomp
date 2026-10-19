// src/game/UTFSpore_Win32/Expression.cpp -- migrated from slice(s) s0083f140, s0083e1c0, s0083d3d0, s0083c900 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Expression.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cExpression.h"
#include "EA/ArgScript/cError.h"
#include "eastl/allocator.h"
#include "eastl/string.h"
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
    string8_s0083_c900(const string8_s0083_c900& x);                          // 0x0057cb10
    ~string8_s0083_c900();
};
}
void  __cdecl ThrowCError(void* out, const char* fmt, ...);                // 0x0052df30
float __cdecl EvalRealExpression(void* self, const char** p);              // 0x0083e470
struct PairCtorStub { void CtorA(const eastl::string8_s0083_c900* s, int** ref); void CtorB(const void* src); };
struct ExprStub { void EvalRealParentheses4(const char** p, float* a, float* b); };
// ---- items of slice s0083c900 end

// ---- items of slice s0083d3d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl isdigit(int);
extern "C" __declspec(dllimport) int __cdecl isalpha(int);
extern "C" __declspec(dllimport) int __cdecl isalnum(int);
extern "C" double __cdecl floor(double);
double __cdecl ParseReal(const char* s, const char** end);     // 0x0092dc50 (strtod-style)
float  __cdecl CeilF(float x);                                  // 0x0083ce70
float  __cdecl ExpF(float x);                                   // 0x00571cc0
static const float kPi = 3.1415927f;
static const float kDegToRad = 0.0055555557f;                   // 1/180
static const float kRadToDeg = 180.0f;
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
typedef unsigned int   uint32;
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
void  __cdecl DiscardWhiteSpace(const char** p);            // 0x0083ce90
void  __cdecl DoFreeNodesExpr(void* bucketArray, int n);    // 0x0083dd00
int   __cdecl EvalIntExpression(void* self, const char** p); // 0x0083eb00
void  __cdecl EvalExpectChar(const char** p, char c);       // 0x0083d240
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
namespace eastl {
 bool operator==(const string8_s0083_d3d0& a, const char* b);   // 0x00555020
}
struct ExprNode { eastl::string8_s0083_d3d0 key; int* fn; ExprNode* next; };
struct ExprPair {                                               // pair<const string8, AutoRefCount<cExprFunction> >
    char* mpBegin; char* mpEnd; char* mpCapacity; unsigned mAlloc; int* fn;   // string8 layout, no ctor
    ExprPair* Ctor(const eastl::string8_s0083_d3d0* k, int** ref);         // 0x0083cef0
    ~ExprPair() {
        if (fn && --fn[1] == 0) FUN_00f47380(fn);
        if ((mpCapacity - mpBegin) > 1 && mpBegin) FUN_00f47380(mpBegin);
    }
};
bool __cdecl StrEqS(const eastl::string8_s0083_d3d0& a, const eastl::string8_s0083_d3d0& b);    // 0x00554fb0
struct InsTag { bool b; };                                                 // eastl bool tag, passed by value
struct ExprTable {
    void* mAlloc;
    ExprNode** mpBucketArray;
    unsigned mnBucketCount;
    unsigned mnElementCount;
    void find(ExprNode** out, const eastl::string8_s0083_d3d0& key);                 // 0x007e2ea0
    void insert(ExprNode** out, ExprPair* v, InsTag tag);                     // 0x0083d140
    int** IndexRef(const eastl::string8_s0083_d3d0& key);                            // 0x0083ddb0
    int   erase(const eastl::string8_s0083_d3d0& key);                               // 0x0083dea0
    void  Register(const char* name, int* ref);                           // 0x0083df90
};
extern "C" long double __cdecl CIpow();
// ---- items of slice s0083d3d0 end

// ---- items of slice s0083e1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line); // 0x00f473a0
extern "C" __declspec(dllimport) unsigned long __cdecl strtoul(const char* s, char** end, int base);
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
namespace eastl {
bool operator==(const string8_s0083_e1c0& s, const char* lit);   // 0x00555020
}
struct cExpression;
struct cExprFunction {
    virtual void          EvalReal(const char** p, cExpression* e);
    virtual int           EvalInt(const char** p, cExpression* e);
    virtual unsigned char EvalBool(const char** p, cExpression* e);
    virtual void          EvalString(const char** p, cExpression* e);
    int mRefCount;   // +0x4
};
struct ExprIter { void* mpNode; void* mpBucket; };
struct cExprNode { eastl::string8_s0083_e1c0 key; cExprFunction* value; void* mpNext; };
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
extern "C" int EvalBoolFactor(const char** p);          // 0x0083efd0 (slice 47)
extern "C" int EvalBoolExpression(const char** p);      // 0x0083f2e0
extern "C" int EvalBoolTerm(const char** p);            // 0x0083f140
namespace eastl {
struct allocator_s0083_f140 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0083_f140 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator_s0083_f140 mAllocator;
    string8_s0083_f140() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    string8_s0083_f140(const char* first, const char* last) {
        unsigned n = (unsigned)(last - first) + 1;
        if (n <= 1) { mpBegin = gEmptyString; mpCapacity = gEmptyString + 1; }
        else { mpBegin = (char*)EASTL_allocator_allocate(n, g_allocName, 0, 0, g_allocFile, 0xd1); mpCapacity = mpBegin + n; }
        memcpy(mpBegin, first, (unsigned)(last - first));
        mpEnd = mpBegin + (last - first);
        *mpEnd = 0;
    }
    void RangeInitialize(unsigned n);
    void assign(const string8_s0083_f140& x);
    ~string8_s0083_f140(); // 0x00530670
};
}
namespace eastl {
bool operator==(const string8_s0083_f140& s, const char* lit);   // 0x00555020
}
namespace EA {
namespace ArgScript {
struct cExpression_s0083_f140 { int EvalChar(const char** p); };   // 0x0083f480 (stub receiver)
}
}
// ---- items of slice s0083f140 end

// @ 0x0083ce90
void DiscardWhiteSpace(const char** p)
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

// @ 0x0083d3d0
float EA::ArgScript::cExpression_s0083_d3d0::EvalRealNumber(const char** p)
{
    DiscardWhiteSpace(p);
    if (isdigit((unsigned char)**p) || **p == '.') {
        const char* end;
        double v = ParseReal(*p, &end);
        *p = end;
        return (float)v;
    }
    if (**p == '(')
        return EvalRealParentheses2(p);
    if (!isalpha((unsigned char)**p))
        throw EA::ArgScript::cError("Bad real expression");
    const char* start = *p;
    ++*p;
    for (;;) {
        char c = **p;
        if (!isalnum((unsigned char)c) && c != '_') break;
        ++*p;
    }
    eastl::string8_s0083_d3d0 name(start, *p - start, eastl::allocator_s0083_d3d0());
    if (name == "pi") return kPi;
    if (name == "e") return (float)exp(1.0f);
    if (name == "sqrt") return (float)sqrt(EvalRealParentheses2(p));
    if (name == "exp") return ExpF(EvalRealParentheses2(p));
    if (name == "log") return (float)log(EvalRealParentheses2(p));
    if (name == "abs") return (float)fabs(EvalRealParentheses2(p));
    if (name == "sin") return (float)sin(EvalRealParentheses2(p));
    if (name == "cos") return (float)cos(EvalRealParentheses2(p));
    if (name == "tan") return (float)tan(EvalRealParentheses2(p));
    if (name == "asin") return (float)asin(EvalRealParentheses2(p));
    if (name == "acos") return (float)acos(EvalRealParentheses2(p));
    if (name == "atan") return (float)atan(EvalRealParentheses2(p));
    if (name == "sind") return (float)sin(EvalRealParentheses2(p) * kPi * kDegToRad);
    if (name == "cosd") return (float)cos(EvalRealParentheses2(p) * kPi * kDegToRad);
    if (name == "tand") return (float)tan(EvalRealParentheses2(p) * kPi * kDegToRad);
    if (name == "dasin") return (float)(asin(EvalRealParentheses2(p)) / kPi * kRadToDeg);
    if (name == "dacos") return (float)(acos(EvalRealParentheses2(p)) / kPi * kRadToDeg);
    if (name == "datan") return (float)(atan(EvalRealParentheses2(p)) / kPi * kRadToDeg);
    if (name == "floor") return (float)floor(EvalRealParentheses2(p));
    if (name == "ceil") return CeilF(EvalRealParentheses2(p));
    if (name == "sqr") { float x = EvalRealParentheses2(p); return x * x; }
    if (name == "pow") { float x, y; EvalRealParentheses(p, &x, &y); return (float)pow(x, y); }
    if (name == "atan2") { float x, y; EvalRealParentheses(p, &x, &y); return (float)atan2(x, y); }
    if (name == "datan2") { float x, y; EvalRealParentheses(p, &x, &y); return (float)(atan2(x, y) / kPi * kRadToDeg); }
    Node* it;
    Node** r = find(&it, name);
    if (*r == mpBucketArray[mnBucketCount])
        throw EA::ArgScript::cError("Unknown function '%s'", name.mpBegin);
    return (*r)->fn->Eval(p, this);
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

// @ 0x0083dc00
void EA::ArgScript::cExpression::EvalString(char const *& p, eastl::basic_string<char, eastl::allocator> * out)
{
    DiscardWhiteSpace(&p);
    DiscardWhiteSpace(&p);
    if (*p == '(') {
        ++p;
        EvalString(p, out);
        DiscardWhiteSpace(&p);
        if (*p != ')') {
            char buf[16];
            ThrowCError(buf, "Expected '%c'", 0x29);
        }
        ++p;
        return;
    }
    DiscardWhiteSpace(&p);
    const char* start = p;
    char c = *start;
    if (c == '"') {
        const char* q = start + 1;
        p = q;
        while (*q != 0 && *q != '"') { ++q; p = q; }
        out->assign(start + 1, p);
        // consume closing quote via EvalBoolParentheses(p,'"')
        EvalExpectChar(&p, '"');
        return;
    }
    while (c != 0) {
        c = *p;
        if (c == ')' || c == ' ' || c == ',') break;
        p = p + 1;
        c = *p;
    }
    out->assign(start, p);
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

// @ 0x0083dd70
float EA::ArgScript::cExpression::EvalSignedRealNumber(char const *& p)
{
    char c;
    for (;;) {
        DiscardWhiteSpace(&p);
        c = *p;
        if (c != '+') break;
        p = p + 1;
    }
    if (c != '-')
        return (long double)EvalRealNumber(p);
    ++p;
    long double v = EvalSignedRealNumber(p);
    return -v;
}

// @ 0x0083ddb0
int** ExprTable::IndexRef(const eastl::string8_s0083_d3d0& key)
{
    ExprNode* it;
    find(&it, key);
    if (it != mpBucketArray[mnBucketCount])
        return &it->fn;
    int* dflt = 0;
    ExprPair v;
    ExprPair* pv = v.Ctor(&key, &dflt);
    InsTag tag;
    tag.b = false;
    insert(&it, pv, tag);
    return &it->fn;
}

// @ 0x0083dea0
int ExprTable::erase(const eastl::string8_s0083_d3d0& key)
{
    const unsigned char* p = (const unsigned char*)key.mpBegin;
    uint32 h = 0x811c9dc5;
    uint32 c = *p;
    while (c) { ++p; h = h * 0x1000193 ^ c; c = *p; }
    unsigned n = h % mnBucketCount;
    unsigned saved = mnElementCount;
    ExprNode** slot = &mpBucketArray[n];
    if (*slot) {
        ExprNode* node;
        do {
            node = *slot;
            if (StrEqS(key, node->key)) break;
            slot = &node->next;
        } while (node->next);
        while (*slot) {
            ExprNode* nd = *slot;
            if (!StrEqS(key, nd->key)) break;
            *slot = nd->next;
            int* r = nd->fn;
            if (r && --r[1] == 0) FUN_00f47380(r);
            char* sb = nd->key.mpBegin;
            if ((nd->key.mpCapacity - sb) > 1 && sb)
                FUN_00f47380(sb);
            FUN_00f47380(nd);
            --mnElementCount;
        }
    }
    return saved - mnElementCount;
}

// @ 0x0083e140
void __fastcall ExprTableClear(void* self)
{
    DoFreeNodesExpr(*(void**)((char*)self + 4), *(int*)((char*)self + 8));
    *(int*)((char*)self + 0xc) = 0;
}

// @ 0x0083e160
float EA::ArgScript::cExpression::EvalRealFactor(char const *& p)
{
    long double base = EvalSignedRealNumber(p);
    DiscardWhiteSpace(&p);
    if (*p == '^') {
        ++p;
        long double exp = EvalRealFactor(p);
        return CIpow();
    }
    (void)base;
    return base;
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
float EA::ArgScript::cExpression::ParseReal(char const * s)
{
    if (*s == 0)
        throw EA::ArgScript::cError("empty expression");
    float v = EvalRealExpression(s);
    if (*s != 0)
        throw EA::ArgScript::cError("Garbage at end of real expression");
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

// @ 0x0083e5f0
ulong32 cExpression::EvalIntNumber(const char** p)
{
    DiscardWhiteSpace(p);
    if (isdigit((unsigned char)**p)) {
        while (**p == '0' && isdigit((unsigned char)(*p)[1]))
            ++*p;
        return strtoul(*p, (char**)p, 0);
    }
    if (**p == '(')
        return (ulong32)EvalIntParentheses(p);
    if (!isalpha((unsigned char)**p))
        throw cError("Bad integer expression");
    const char* start = *p;
    ++*p;
    while (isalnum((unsigned char)**p) || **p == '_')
        ++*p;
    eastl::string8_s0083_e1c0 name(start, *p);

    if (name == "abs") {
        int v = EvalIntParentheses(p);
        return (ulong32)(v < 0 ? -v : v);
    }
    if (name == "floor") {
        float x = EvalRealParentheses2(p);
        int i = (int)x;
        if (x < (float)i)
            --i;
        return (ulong32)i;
    }
    if (name == "ceil") {
        float x = EvalRealParentheses2(p);
        int i = (int)x;
        if ((float)i < x)
            ++i;
        return (ulong32)i;
    }
    if (name == "round")
        return (ulong32)(int)EvalRealParentheses2(p);
    if (name == "sqr") {
        int v = EvalIntParentheses(p);
        return (ulong32)(v * v);
    }
    if (name == "true" || name == "on")
        return 1;
    if (name == "false" || name == "off")
        return 0;

    ExprIter it = find(name);
    if (it.mpNode != mpBucketArray[mnBucketCount]) {
        cExprFunction* f = ((cExprNode*)it.mpNode)->value;
        return (ulong32)f->EvalInt(p, this);
    }
    throw cError("Unknown int function '%s'", name.mpBegin);
}

// @ 0x0083e9d0
#pragma inline_depth(0)
int EA::ArgScript::cExpression::EvalSignedIntNumber(char const *& p)
{
    for (;;) {
        DiscardWhiteSpace(&p);
        switch (*p) {
        case '+':
            ++p;
            break;
        case '-':
            ++p;
            return -EvalSignedIntNumber(p);
        default:
            return EvalIntNumber(p);
        }
    }
}
#pragma inline_depth()

// @ 0x0083ea10
int EA::ArgScript::cExpression::EvalIntFactor(char const *& p)
{
    int base = EvalSignedIntNumber(p);
    DiscardWhiteSpace(&p);
    if (*p != '^')
        return base;
    ++p;
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

// @ 0x0083eb70
unsigned char cExpression::EvalBool(const char** p)
{
    if (**p == '(')
        return EvalChar(p);
    if (isalpha((unsigned char)**p)) {
        const char* start = *p;
        ++*p;
        while (isalnum((unsigned char)**p) || **p == '_')
            ++*p;
        eastl::string8_s0083_e1c0 name(start, *p);
        if (name == "true" || name == "on")
            return 1;
        if (name == "false" || name == "off")
            return 0;
        ExprIter it = find(name);
        if (it.mpNode != mpBucketArray[mnBucketCount]) {
            cExprFunction* f = ((cExprNode*)it.mpNode)->value;
            return f->EvalBool(p, this);
        }
    }
    return (unsigned char)EvalIntExpression(p);
}

// @ 0x0083edc0
int EA::ArgScript::cExpression::ParseInt(char const * s)
{
    if (*s == 0)
        throw EA::ArgScript::cError("empty expression");
    int v = EvalIntExpression(s);
    if (*s != 0)
        throw EA::ArgScript::cError("Garbage at end of integer expression");
    return v;
}

// @ 0x0083ee30
int EA::ArgScript::cExpression::EvalRelExpression(char const *& p)
{
    unsigned v = EvalBool(p);
    for (;;) {
        while (isspace((unsigned char)*p))
            ++p;
        switch (*p) {
        case '!':
            ++p;
            if (*p != '=')
                throw EA::ArgScript::cError("Illegal operator %c%c", '!', *p);
            ++p;
            v = (unsigned)(v != EvalRelExpression(p));
            break;
        case '<':
            ++p;
            if (*p == '=') {
                ++p;
                v = (unsigned)((int)v <= (int)EvalRelExpression(p));
            } else {
                v = (unsigned)((int)v < (int)EvalRelExpression(p));
            }
            break;
        case '>':
            ++p;
            if (*p == '=') {
                ++p;
                v = (unsigned)((int)EvalRelExpression(p) <= (int)v);
            } else {
                v = (unsigned)((int)EvalRelExpression(p) < (int)v);
            }
            break;
        case '=':
            ++p;
            if (*p != '=')
                throw EA::ArgScript::cError("Illegal operator %c%c", '=', *p);
            ++p;
            v = (unsigned)(v == EvalRelExpression(p));
            break;
        default:
            return v;
        }
    }
}

// @ 0x0083efd0
unsigned cExpression::EvalBoolFactor(const char** p)
{
    DiscardWhiteSpace(p);
    if (isalpha((unsigned char)**p)) {
        const char* start = *p;
        ++*p;
        while (isalpha((unsigned char)**p))
            ++*p;
        eastl::string8_s0083_e1c0 name(start, *p);
        if (name == "not") {
            int v = EvalBoolFactor(p);
            return (unsigned)(v == 0);
        }
        *p = start;
    }
    return EvalRelExpression(p);
}

// @ 0x0083f140
int __cdecl EvalBoolTerm(const char** p)
{
    int result = EvalBoolFactor(p);
    for (;;) {
        while (isspace((unsigned char)**p))
            ++*p;
        if (!isalpha((unsigned char)**p))
            break;
        const char* start = *p;
        ++*p;
        while (isalpha((unsigned char)**p))
            ++*p;
        eastl::string8_s0083_f140 name(start, *p);
        if (name == "and") {
            int v = EvalBoolFactor(p);
            result = (v != 0) && (result != 0);
            continue;
        }
        *p = start;
        break;
    }
    return result;
}

// @ 0x0083f2e0
int __cdecl EvalBoolExpression(const char** p)
{
    int result = EvalBoolTerm(p);
    for (;;) {
        while (isspace((unsigned char)**p))
            ++*p;
        if (!isalpha((unsigned char)**p))
            break;
        const char* start = *p;
        ++*p;
        while (isalpha((unsigned char)**p))
            ++*p;
        eastl::string8_s0083_f140 name(start, *p);
        if (name == "or") {
            int v = EvalBoolTerm(p);
            result = (v != 0) || (result != 0);
            continue;
        }
        *p = start;
        break;
    }
    return result;
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
