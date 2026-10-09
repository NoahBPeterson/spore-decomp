// Slice s0083e1c0 (batch w2g7). EA::ArgScript::cExpression recursive-descent
// real/int/bool expression evaluators plus the cExpression hash_map init.
// Compiled /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast (see manifest).

#include <math.h>

typedef unsigned int  uint32;
typedef unsigned char uint8;
typedef int           int32;
typedef unsigned long ulong32;

extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line); // 0x00f473a0
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
__declspec(dllimport) int   __cdecl isspace(int);
__declspec(dllimport) int   __cdecl isdigit(int);
__declspec(dllimport) int   __cdecl isalpha(int);
__declspec(dllimport) int   __cdecl isalnum(int);
__declspec(dllimport) unsigned long __cdecl strtoul(const char* s, char** end, int base);
__declspec(dllimport) void* __cdecl memcpy(void* dst, const void* src, unsigned n);
void  __cdecl DiscardWhiteSpace(const char** p);              // 0x0083ce90
}

struct cError {
    cError(const char* fmt, ...);          // 0x0052df30 (variadic ctor, this pushed)
    cError(const cError&);
};
inline void* operator new(unsigned, void* p) { return p; }
inline void  operator delete(void*, void*) {}

static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";

extern char gEmptyString[]; // 0x01667bac
extern void* gEmptyBucketArray[];       // 0x0154df28
extern float gOne;                      // 0x01485720
extern float gTwo;                      // 0x01470f1c
extern char __TI1_AVcError_ArgScript_EA__[];   // 0x014f9174

namespace eastl {
struct allocator { unsigned char pad[4]; };
struct string8 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator mAllocator;
    string8() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    string8(const char* first, const char* last) {
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
    ~string8(); // 0x00530670
};
bool operator==(const string8& s, const char* lit);   // 0x00555020
}  // namespace eastl

struct cExpression;
struct cExprFunction {
    virtual void          EvalReal(const char** p, cExpression* e);
    virtual int           EvalInt(const char** p, cExpression* e);
    virtual unsigned char EvalBool(const char** p, cExpression* e);
    virtual void          EvalString(const char** p, cExpression* e);
    int mRefCount;   // +0x4
};

struct ExprIter { void* mpNode; void* mpBucket; };
struct cExprNode { eastl::string8 key; cExprFunction* value; void* mpNext; };

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
    ExprIter find(const eastl::string8& key) const;   // 0x007e2ea0

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

// ===========================================================================
// 0x0083e430  cExpression::cExpression  (hash_map default init)
// ===========================================================================
// @ 0x0083e430
cExpression::cExpression() : mfMaxLoadFactor(gOne), mfGrowthFactor(gTwo) {
    mnBucketCount = 1;
    mpBucketArray = gEmptyBucketArray;
    mnElementCount = 0;
    pad18 = 0;
}

// ===========================================================================
// 0x0083e1c0  EA::ArgScript::cExpression::EvalRealTerm
// ===========================================================================
// @ 0x0083e1c0
float cExpression::EvalRealTerm(const char** p) {
    float acc = (float)EvalRealFactor(p);
    for (;;) {
        while (isspace((unsigned char)**p))
            ++*p;
        char c = **p;
        if (c == '%') {
            ++*p;
            while (isspace((unsigned char)**p))
                ++*p;
            float d;
            if (**p == '+') { ++*p; d = (float)EvalSignedRealNumber(p); }
            else if (**p == '-') { ++*p; d = -(float)EvalSignedRealNumber(p); }
            else d = (float)EvalRealNumber(p);
            while (isspace((unsigned char)**p))
                ++*p;
            if (**p == '^') {
                ++*p;
                d = (float)pow((double)d, (double)EvalRealFactor(p));
            }
            float q = acc / d;
            float r = (float)(floor((double)q) * (double)d);
            acc = acc - r;
        } else if (c == '*') {
            ++*p;
            while (isspace((unsigned char)**p))
                ++*p;
            float d;
            if (**p == '+') { ++*p; d = (float)EvalSignedRealNumber(p); }
            else if (**p == '-') { ++*p; d = -(float)EvalSignedRealNumber(p); }
            else d = (float)EvalRealNumber(p);
            while (isspace((unsigned char)**p))
                ++*p;
            if (**p == '^') {
                ++*p;
                d = (float)pow((double)d, (double)EvalRealFactor(p));
            }
            acc = acc * d;
        } else if (c == '/') {
            ++*p;
            float d = (float)EvalSignedRealNumber(p);
            while (isspace((unsigned char)**p))
                ++*p;
            if (**p == '^') {
                ++*p;
                d = (float)pow((double)d, (double)EvalRealFactor(p));
            }
            acc = acc / d;
        } else {
            return acc;
        }
    }
}

// ===========================================================================
// 0x0083e470  EA::ArgScript::cExpression::EvalRealExpression
// ===========================================================================
// @ 0x0083e470
float cExpression::EvalRealExpression(const char** p) {
    float result = EvalRealTerm(p);
    for (;;) {
        while (isspace((unsigned char)**p))
            ++*p;
        switch (**p) {
        case '+':
            ++*p;
            result = result + (float)EvalRealTerm(p);
            break;
        case '-':
            ++*p;
            result = result - (float)EvalRealTerm(p);
            break;
        default:
            return result;
        }
    }
}

// ===========================================================================
// 0x0083e4f0  EA::ArgScript::cExpression::ParseReal
// ===========================================================================
// @ 0x0083e4f0
float cExpression::ParseReal(const char* s) {
    if (*s == 0)
        throw cError("empty expression");
    float v = EvalRealExpression(&s);
    if (*s != 0)
        throw cError("Garbage at end of real expression");
    return v;
}

// ===========================================================================
// 0x0083e560  EA::ArgScript::cExpression::EvalRealParentheses2
// ===========================================================================
// @ 0x0083e560
float cExpression::EvalRealParentheses2(const char** p) {
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

// ===========================================================================
// 0x0083e5f0  EA::ArgScript::cExpression::EvalIntNumber
// ===========================================================================
// @ 0x0083e5f0
ulong32 cExpression::EvalIntNumber(const char** p) {
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
    eastl::string8 name(start, *p);

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

// ===========================================================================
// 0x0083e9d0  EA::ArgScript::cExpression::EvalSignedIntNumber
// ===========================================================================
// @ 0x0083e9d0
int cExpression::EvalSignedIntNumber(const char** p) {
    for (;;) {
        DiscardWhiteSpace(p);
        switch (**p) {
        case '+':
            ++*p;
            break;
        case '-':
            ++*p;
            return -EvalSignedIntNumber(p);
        default:
            return EvalIntNumber(p);
        }
    }
}

// ===========================================================================
// 0x0083ea10  EA::ArgScript::cExpression::EvalIntFactor
// ===========================================================================
// @ 0x0083ea10
int cExpression::EvalIntFactor(const char** p) {
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

// ===========================================================================
// 0x0083ea70  EA::ArgScript::cExpression::EvalIntTerm
// ===========================================================================
// @ 0x0083ea70
int cExpression::EvalIntTerm(const char** p) {
    int result = EvalIntFactor(p);
    for (;;) {
        while (isspace((unsigned char)**p))
            ++*p;
        switch (**p) {
        case '%':
            ++*p;
            result %= EvalIntFactor(p);
            break;
        case '*':
            ++*p;
            result *= EvalIntFactor(p);
            break;
        case '/':
            ++*p;
            result /= EvalIntFactor(p);
            break;
        default:
            return result;
        }
    }
}

// ===========================================================================
// 0x0083eb00  EA::ArgScript::cExpression::EvalIntExpression
// ===========================================================================
// @ 0x0083eb00
int cExpression::EvalIntExpression(const char** p) {
    int result = EvalIntTerm(p);
    for (;;) {
        while (isspace((unsigned char)**p))
            ++*p;
        switch (**p) {
        case '+':
            ++*p;
            result += EvalIntTerm(p);
            break;
        case '-':
            ++*p;
            result -= EvalIntTerm(p);
            break;
        default:
            return result;
        }
    }
}

// ===========================================================================
// 0x0083eb70  EA::ArgScript::cExpression::EvalBool
// ===========================================================================
// @ 0x0083eb70
unsigned char cExpression::EvalBool(const char** p) {
    if (**p == '(')
        return EvalChar(p);
    if (isalpha((unsigned char)**p)) {
        const char* start = *p;
        ++*p;
        while (isalnum((unsigned char)**p) || **p == '_')
            ++*p;
        eastl::string8 name(start, *p);
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

// ===========================================================================
// 0x0083edc0  EA::ArgScript::cExpression::ParseInt
// ===========================================================================
// @ 0x0083edc0
int cExpression::ParseInt(const char* s) {
    if (*s == 0)
        throw cError("empty expression");
    int v = EvalIntExpression(&s);
    if (*s != 0)
        throw cError("Garbage at end of integer expression");
    return v;
}

// ===========================================================================
// 0x0083ee30  EA::ArgScript::cExpression::EvalRelExpression
// ===========================================================================
// @ 0x0083ee30
unsigned cExpression::EvalRelExpression(const char** p) {
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

// ===========================================================================
// 0x0083efd0  EA::ArgScript::cExpression::EvalBoolFactor
// ===========================================================================
// @ 0x0083efd0
unsigned cExpression::EvalBoolFactor(const char** p) {
    DiscardWhiteSpace(p);
    if (isalpha((unsigned char)**p)) {
        const char* start = *p;
        ++*p;
        while (isalpha((unsigned char)**p))
            ++*p;
        eastl::string8 name(start, *p);
        if (name == "not") {
            int v = EvalBoolFactor(p);
            return (unsigned)(v == 0);
        }
        *p = start;
    }
    return EvalRelExpression(p);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct string8 {
    ~string8(); // 0x00530670
};
}
