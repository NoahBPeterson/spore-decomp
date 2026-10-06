// Slice s0083d3d0 (batch w2g7). ArgScript cExpression primitives and the
// cExprFunction hashtable helpers. /O2 /MD /Gy /EHsc /TP /GS-.

typedef unsigned int   uint32;
typedef unsigned char  uint8;
typedef int            int32;

extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line);
void  __cdecl EASTL_allocator_deallocate(void* p);
long double __cdecl CIpow();
}
inline void* operator new(unsigned, void* p) { return p; }
inline void  operator delete(void*, void*) {}

static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";
extern char gEmptyString[];

namespace eastl {
struct allocator { unsigned char pad[4]; };
struct sp_vector_allocator : allocator {};
struct string8 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator mAllocator;
    string8() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void assign(const char* first, const char* last);   // 0x00454cb0
    void assign(const char* p);                         // 0x006a4380
    void RangeInitialize(unsigned n);                   // 0x00475ab0
    string8(const string8& x);                          // 0x0057cb10
    ~string8();
};
}  // namespace eastl

void  __cdecl DiscardWhiteSpace(const char** p);            // 0x0083ce90
void  __cdecl ThrowCError(void* out, const char* fmt, ...); // 0x0052df30
void  __cdecl DoFreeNodesExpr(void* bucketArray, int n);    // 0x0083dd00
void* __cdecl HashFindExprNode(const void* key, void* node);// 0x007e2ea0
void* __cdecl MakeExprNode(const void* key, int* refOut);   // 0x0083ddb0
void* __cdecl HashInsertExpr(void* self, void* out, const void* key);  // 0x0083dea0
int*  __cdecl ExprFindOrInsert(void* self, const void* key);           // 0x0083ddb0
int   __cdecl ExprFind(int* out, const void* key);          // 0x007e2ea0
int   __cdecl EvalIntExpression(void* self, const char** p); // 0x0083eb00
void  __cdecl EvalExpectChar(const char** p, char c);       // 0x0083d240

// ===========================================================================
// 0x0083d3d0  EA::ArgScript::cExpression::EvalRealNumber   (partial)
// ===========================================================================
// @ 0x0083d3d0
// 1942-byte number-literal parser (hex/float/decimal, exponents). Kept as a
// compiling stub; see partial.txt.
float __cdecl EvalRealNumber(void* self, const char** p) {
    (void)self; (void)p;
    return 0.0f;
}

// ===========================================================================
// 0x0083db70  EA::ArgScript::cExpression::EvalIntParentheses
// ===========================================================================
// @ 0x0083db70
int __cdecl EvalIntParentheses(void* self, const char** p) {
    DiscardWhiteSpace(p);
    if (**p != '(') {
        char buf[16];
        ThrowCError(buf, "Expected '%c'", 0x28);
    }
    ++*p;
    int v = EvalIntExpression(self, p);
    DiscardWhiteSpace(p);
    if (**p != ')') {
        char buf[16];
        ThrowCError(buf, "Expected '%c'", 0x29);
    }
    ++*p;
    return v;
}

// ===========================================================================
// 0x0083dc00  EA::ArgScript::cExpression::EvalString
// ===========================================================================
// @ 0x0083dc00
void EvalString(void* self, const char** p, eastl::string8* out) {
    DiscardWhiteSpace(p);
    DiscardWhiteSpace(p);
    if (**p == '(') {
        ++*p;
        EvalString(self, p, out);
        DiscardWhiteSpace(p);
        if (**p != ')') {
            char buf[16];
            ThrowCError(buf, "Expected '%c'", 0x29);
        }
        ++*p;
        return;
    }
    DiscardWhiteSpace(p);
    const char* start = *p;
    char c = *start;
    if (c == '"') {
        const char* q = start + 1;
        *p = q;
        while (*q != 0 && *q != '"') { ++q; *p = q; }
        out->assign(start + 1, *p);
        // consume closing quote via EvalBoolParentheses(p,'"')
        EvalExpectChar(p, '"');
        return;
    }
    while (c != 0) {
        c = **p;
        if (c == ')' || c == ' ' || c == ',') break;
        *p = *p + 1;
        c = **p;
    }
    out->assign(start, *p);
}

// ===========================================================================
// 0x0083dd00  hashtable<...cExprFunction...>::DoFreeNodes
// ===========================================================================
// @ 0x0083dd00
void __cdecl DoFreeNodesExpr(void* bucketArray, int bucketCount) {
    for (int i = 0; i < bucketCount; ++i) {
        char* node = *(char**)((char*)bucketArray + i * 4);
        while (node) {
            char* next = *(char**)(node + 0x14);
            int* ref = *(int**)(node + 0x10);
            if (ref) { if (--ref[1] == 0) EASTL_allocator_deallocate(ref); }
            eastl::string8* s = (eastl::string8*)node;
            if ((s->mpCapacity - s->mpBegin) > 1 && s->mpBegin)
                EASTL_allocator_deallocate(s->mpBegin);
            EASTL_allocator_deallocate(node);
            node = next;
        }
        *(void**)((char*)bucketArray + i * 4) = 0;
    }
}

// ===========================================================================
// 0x0083dd70  EA::ArgScript::cExpression::EvalSignedRealNumber
// ===========================================================================
// @ 0x0083dd70
long double __cdecl EvalSignedRealNumber(void* self, const char** p) {
    char c;
    for (;;) {
        DiscardWhiteSpace(p);
        c = **p;
        if (c != '+') break;
        *p = *p + 1;
    }
    if (c != '-')
        return (long double)EvalRealNumber(self, p);
    ++*p;
    long double v = EvalSignedRealNumber(self, p);
    return -v;
}

// ===========================================================================
// 0x0083ddb0  expr table lookup-or-create under key
// ===========================================================================
// @ 0x0083ddb0
int* __cdecl ExprFindOrInsert(void* self, const void* key) {
    (void)self; (void)key;
    return 0;
}

// ===========================================================================
// 0x0083dea0  hashtable<...cExprFunction...>::erase(key)
// ===========================================================================
// @ 0x0083dea0
int __cdecl HashEraseExpr(void* self, const void** keyPtr) {
    const unsigned char* p = (const unsigned char*)*keyPtr;
    uint32 h = 0x811c9dc5;
    unsigned char c = *p;
    while (c) { ++p; h = h * 0x1000193 ^ c; c = *p; }
    unsigned n = h % *(unsigned*)((char*)self + 8);
    int prevCount = *(int*)((char*)self + 0xc);
    char** slot = (char**)(*(char**)((char*)self + 4) + n * 4);
    if (*slot) {
        while (*slot) {
            char* node = *slot;
            if (HashFindExprNode(keyPtr[1], node)) {
                *slot = *(char**)(node + 0x14);
                int* ref = *(int**)(node + 0x10);
                if (ref) { if (--ref[1] == 0) EASTL_allocator_deallocate(ref); }
                eastl::string8* s = (eastl::string8*)node;
                if ((s->mpCapacity - s->mpBegin) > 1 && s->mpBegin)
                    EASTL_allocator_deallocate(s->mpBegin);
                EASTL_allocator_deallocate(node);
                --*(int*)((char*)self + 0xc);
            } else {
                slot = (char**)(node + 0x14);
            }
        }
    }
    return prevCount - *(int*)((char*)self + 0xc);
}

// ===========================================================================
// 0x0083df90  `anonymous namespace'::cIfCommand::cIfCommand  (partial)
// ===========================================================================
// @ 0x0083df90
// 417-byte command ctor building the "if" command table. Kept as a compiling
// stub; see partial.txt.
void __cdecl cIfCommand_ctor(int* self, const char* name, int cmd) {
    (void)self; (void)name; (void)cmd;
}

// ===========================================================================
// 0x0083e140  hashtable<...cExprFunction...> node/dtor reset
// ===========================================================================
// @ 0x0083e140
void __fastcall ExprTableClear(void* self) {
    DoFreeNodesExpr(*(void**)((char*)self + 4), *(int*)((char*)self + 8));
    *(int*)((char*)self + 0xc) = 0;
}

// ===========================================================================
// 0x0083e160  EA::ArgScript::cExpression::EvalRealFactor
// ===========================================================================
// @ 0x0083e160
long double __cdecl EvalRealFactor(void* self, const char** p) {
    long double base = EvalSignedRealNumber(self, p);
    DiscardWhiteSpace(p);
    if (**p == '^') {
        ++*p;
        long double exp = EvalRealFactor(self, p);
        return CIpow();
    }
    (void)base;
    return base;
}
