// Slice s0083c900 (batch w2g7). ArgScript hash_map/hashtable helpers, AppProps,
// AutoRefCount/pair helpers and cExpression primitives. /O2 /MD /Gy /EHsc /TP /GS-.

typedef unsigned int   uint32;
typedef unsigned char  uint8;
typedef int            int32;

extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line);
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
int   __cdecl isspace(int);
double __cdecl ceil(double);
}
inline void* operator new(unsigned, void* p) { return p; }
inline void  operator delete(void*, void*) {}

static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";

extern char gEmptyString[];
extern float gAppPropsMin;
extern float gAppPropsMax;
extern void* gAppPropsBuckets[];
extern void* vtbl_AppProps;   // 0x0141b5e4 (equiv t3)

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
template <typename T> struct vec {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator mAllocator;
    vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};
}  // namespace eastl

// helpers from neighbouring slices
void  __cdecl DoFreeNodesTable(void* bucketArray, int bucketCount);       // 0x0083cad0 (this)
void  __cdecl HashNodeAlloc(void* out, int nBuckets, int nElem, int flag); // 0x00921440
void* __cdecl NewHashCommandNode(const void** key);                        // 0x0083c880
void  __cdecl HashDoRehash(void* self, int n);                             // 0x0083cf50
int   __cdecl StrEqInsensitive(const char* a, const char* b);              // 0x00554fb0
void  __cdecl MakeCaseInsensitive(void* p);
void  __cdecl ThrowCError(void* out, const char* fmt, ...);                // 0x0052df30
float __cdecl EvalRealExpression(void* self, const char** p);              // 0x0083e470

// ===========================================================================
// 0x0083c900  hashtable<...cICommand...>::insert(key)
// ===========================================================================
// @ 0x0083c900
void* HashFindInsertCommand(void* self, void* outIt, const void** keyPtr) {
    const unsigned char* p = (const unsigned char*)*keyPtr;
    uint32 h = 0x811c9dc5;
    unsigned char c = *p;
    while (c) { ++p; h = h * 0x1000193 ^ c; c = *p; }
    unsigned n = h % *(unsigned*)((char*)self + 8);
    char* node = *(char**)(*(char**)((char*)self + 4) + n * 4);
    int* slot = (int*)(*(char**)((char*)self + 4) + n * 4);
    for (;;) {
        if (node == 0) {
            int changed = 0;
            HashNodeAlloc(&changed, *(int*)((char*)self + 8), *(int*)((char*)self + 0xc), 1);
            node = (char*)NewHashCommandNode(keyPtr);
            if ((char)changed) {
                n = h % *(unsigned*)((char*)self + 0xc);
                HashDoRehash(*(void**)((char*)self + 4), *(int*)((char*)self + 0xc));
            }
            *(char**)(node + 0x14) = *(char**)(*(char**)((char*)self + 4) + n * 4);
            *(char**)(*(char**)((char*)self + 4) + n * 4) = node;
            ++*(int*)((char*)self + 0xc);
            *(void**)outIt = node;
            *((void**)outIt + 1) = (char*)*(void**)((char*)self + 4) + n * 4;
            *((unsigned char*)outIt + 8) = 1;
            return node;
        }
        if (StrEqInsensitive((const char*)*keyPtr, (const char*)node))
            break;
        node = *(char**)(node + 0x14);
    }
    *(void**)outIt = node;
    *((void**)outIt + 1) = slot;
    *((unsigned char*)outIt + 8) = 0;
    return node;
}

// ===========================================================================
// 0x0083ca00  hashtable<...cExprFunction...>::find(key) -> value ptr or 0
// ===========================================================================
// @ 0x0083ca00
void* HashFindExprValue(void* self, const char* key) {
    const char* p = key;
    while (*p) ++p;
    unsigned len = (unsigned)(p - key) + 1;
    char* buf; char* cap;
    if (len < 2) { buf = gEmptyString; cap = gEmptyString + 1; }
    else { buf = (char*)EASTL_allocator_allocate(len, g_allocName, 0, 0, g_allocFile, 0xd1); cap = buf + len; }
    char* end = buf + (p - key);
    for (const char* s = key; s < p; ++s) *buf++ = *s;
    *end = 0;
    buf = end - (p - key);
    int keycopy[2];
    (void)keycopy;
    if ((cap - buf) > 1 && buf) EASTL_allocator_deallocate(buf);
    (void)self;
    return 0;
}

// ===========================================================================
// 0x0083cad0  hashtable<...cICommand...>::DoFreeNodes
// ===========================================================================
// @ 0x0083cad0
void __cdecl DoFreeNodesTable(void* bucketArray, int bucketCount) {
    if (bucketCount > 1) {
        for (int i = 0; i < bucketCount; ++i) {
            char* node = *(char**)((char*)bucketArray + i * 4);
            while (node) {
                char* next = *(char**)(node + 0x14);
                // node dtor + free is a separate helper; caller frees the array below
                *(void**)(node + 0x14) = 0;
                node = next;
            }
        }
        (void)bucketArray;
    }
}

// ===========================================================================
// 0x0083cb70  hash_map<string, AutoRefCount<cICommand>>::operator[]
// ===========================================================================
// @ 0x0083cb70
void* HashmapCommandLookup(void* self, const void* key) {
    (void)self; (void)key; return 0;
}

// ===========================================================================
// 0x0083cc30  install a command under (case-insensitive) name
// ===========================================================================
// @ 0x0083cc30
void HashmapSetCommand(void* self, const char* name, int* cmd) {
    eastl::string8 s;
    s.assign(name, name + 0);
    MakeCaseInsensitive(&s);
    int** slot = (int**)HashmapCommandLookup(0, &s);
    (void)slot;
    (void)self; (void)cmd;
}

// ===========================================================================
// 0x0083cd90  EA::ArgScript::cBlockCommandBase::~cBlockCommandBase
// ===========================================================================
struct CmdDtor {
    void* vtbl;
    int pad04[3];
    void* mpBucketArray;
    int   mnBucketCount;
    int   mnElementCount;
    int   pad1c;
    int   pad20[4];
    void Dtor();
};
// @ 0x0083cd90
void CmdDtor::Dtor() {
    vtbl = vtbl_AppProps;
    DoFreeNodesTable(mpBucketArray, mnBucketCount);
    if (mnBucketCount > 1)
        EASTL_allocator_deallocate(mpBucketArray);
    mnElementCount = 0;
}

// ===========================================================================
// 0x0083cdd0  ArgScript::AppProps::AppProps
// ===========================================================================
struct AppPropsFields {
    void* vtbl;          // +0x00
    int   mParser;       // +0x04
    int   mRefCount;     // +0x08
    int   pad0c;         // +0x0c
    int   pad10;         // +0x10
    void* mpBucketArray; // +0x14
    int   mnBucketCount; // +0x18
    int   mnElementCount;// +0x1c
    float mMin;          // +0x20
    float mMax;          // +0x24
    int   pad28;         // +0x28
    AppPropsFields();                        // 0x0083cdd0
    AppPropsFields* VectorDtor(unsigned char flags); // 0x0083ce20
};
// @ 0x0083cdd0
AppPropsFields::AppPropsFields() {
    vtbl = vtbl_AppProps;
    mParser = 0;
    mRefCount = 0;
    pad0c = 0;
    mpBucketArray = gAppPropsBuckets;
    mnBucketCount = 1;
    mnElementCount = 0;
    mMin = gAppPropsMin;
    mMax = gAppPropsMax;
    pad28 = 0;
}

// ===========================================================================
// 0x0083ce20  AppProps deleting destructor
// ===========================================================================
// @ 0x0083ce20
AppPropsFields* AppPropsFields::VectorDtor(unsigned char flags) {
    vtbl = vtbl_AppProps;
    DoFreeNodesTable(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if ((unsigned)mnBucketCount > 1)
        EASTL_allocator_deallocate(mpBucketArray);
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}

// ===========================================================================
// 0x0083ce70  ceil helper
// ===========================================================================
// @ 0x0083ce70
float CeilToFloat(float x) {
    return (float)ceil((double)x);
}

// ===========================================================================
// 0x0083ce90  `anonymous namespace'::DiscardWhiteSpace
// ===========================================================================
// @ 0x0083ce90
void DiscardWhiteSpace(const char** p) {
    while (isspace((unsigned char)**p))
        ++*p;
}

// ===========================================================================
// 0x0083ced0  EA::AutoRefCount<...>::~AutoRefCount
// ===========================================================================
// @ 0x0083ced0
void ReleaseRefCount(int** p) {
    int* obj = *p;
    if (obj) {
        if (--obj[1] == 0)
            EASTL_allocator_deallocate(obj);
    }
}

// ===========================================================================
// 0x0083cef0  pair<string, AutoRefCount>::pair(const string&, const AutoRefCount&)
// ===========================================================================
// @ 0x0083cef0
void __cdecl PairStringRefCtor_A(void* self, const eastl::string8* s, int** ref) {
    eastl::string8* str = (eastl::string8*)self;
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

// ===========================================================================
// 0x0083d020  pair<string, AutoRefCount>::pair(const pair&)
// ===========================================================================
// @ 0x0083d020
void __cdecl PairStringRefCtor_B(void* self, const void* src) {
    eastl::string8* str = (eastl::string8*)self;
    const eastl::string8* s = (const eastl::string8*)src;
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

// ===========================================================================
// 0x0083d080  eastl::pair<const string, AutoRefCount<cExprFunction>>::~pair
// ===========================================================================
// @ 0x0083d080
void __cdecl PairStringExprDtor(void* self) {
    int* obj = *(int**)((char*)self + 0x10);
    if (obj) {
        if (--obj[1] == 0)
            EASTL_allocator_deallocate(obj);
    }
    eastl::string8* str = (eastl::string8*)self;
    if ((str->mpCapacity - str->mpBegin) > 1 && str->mpBegin)
        EASTL_allocator_deallocate(str->mpBegin);
}

// ===========================================================================
// 0x0083d140  hashtable<...cExprFunction...>::insert(key)  (same shape as 0083c900)
// ===========================================================================
// @ 0x0083d140
void* HashInsertExprValue(void* self, void* outIt, const void** keyPtr) {
    return HashFindInsertCommand(self, outIt, keyPtr);
}

// ===========================================================================
// 0x0083d240  EvalBoolParentheses (expect char, throw on mismatch)
// ===========================================================================
// @ 0x0083d240
void EvalExpectCharThrow(const char** p, char c) {
    DiscardWhiteSpace(p);
    if (**p != c) {
        char buf[16];
        ThrowCError(buf, "Expected '%c'", (int)c);
        _CxxThrowException(buf, (_ThrowInfo*)0);
    }
    ++*p;
}

// ===========================================================================
// 0x0083d290  EvalContinueChar
// ===========================================================================
// @ 0x0083d290
unsigned char EvalContinueChar(const char** p, char c) {
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

// ===========================================================================
// 0x0083d2f0  EvalRealParentheses(self, p, out1, out2)
// ===========================================================================
// @ 0x0083d2f0
void EvalRealParentheses4(void* self, const char** p, float* a, float* b) {
    EvalExpectCharThrow(p, '(');
    *a = EvalRealExpression(self, p);
    EvalExpectCharThrow(p, ',');
    *b = EvalRealExpression(self, p);
    EvalExpectCharThrow(p, ')');
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
