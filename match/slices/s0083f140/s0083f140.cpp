// Slice s0083f140 (batch w2g7). ArgScript bool evaluators, cFileParser and the
// FileChangeNotification hashtable/vector helpers. /O2 /MD /Gy /EHsc /TP /GS-.

typedef unsigned int   uint32;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef int            int32;
typedef unsigned long  ulong32;

extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line); // 0x00f473a0
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
__declspec(dllimport) int __cdecl isspace(int);
__declspec(dllimport) int __cdecl isalpha(int);
__declspec(dllimport) int __cdecl isalnum(int);
void* __cdecl memcpy(void* dst, const void* src, unsigned n);
void  __cdecl DiscardWhiteSpace(const char** p);          // 0x0083ce90
void  __cdecl GetElapsedTimeFloat();
}
inline void* operator new(unsigned, void* p) { return p; }
inline void  operator delete(void*, void*) {}

static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";

extern char gEmptyString[]; // 0x01667bac
extern void* gEmptyBucketArray[];

struct cError {
    cError(const char* fmt, ...);
    cError(const cError&);
};

// hashtable<cFileNotify> helpers (other slices / in-between helper code)
void  __cdecl HashNodeAlloc(void* out, int nBuckets, int nElem, int flag);  // 0x00921440
void* __cdecl MakeFileNotifyNode(int* key);                         // 0x0083fb40
void  __cdecl HashDoRehash(void* bucketArray, int n);                       // 0x0083f9b0
void  __cdecl HashFindFileNotify(void* self, void* out, void* key);   // 0x007e2ea0
int   __cdecl HashFindNode(const void* key, void* node);                   // 0x00554fb0

namespace eastl {
struct allocator { unsigned char pad[4]; };
struct sp_vector_allocator : allocator {};
struct string8 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator mAllocator;
    string8() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    string8(const char* first, const char* last) {
        unsigned n = (unsigned)(last - first) + 1;
        if (n <= 1) { mpBegin = gEmptyString; mpCapacity = gEmptyString + 1; }
        else { mpBegin = (char*)EASTL_allocator_allocate(n, g_allocName, 0, 0, g_allocFile, 0xd1); mpCapacity = mpBegin + n; }
        memcpy(mpBegin, first, (unsigned)(last - first));
        mpEnd = mpBegin + (last - first);
        *mpEnd = 0;
    }
    void RangeInitialize(unsigned n);
    void assign(const string8& x);
    ~string8(); // 0x00530670
};
bool operator==(const string8& s, const char* lit);   // 0x00555020
}  // namespace eastl

// ---------------------------------------------------------------------------
// ArgScript bool expression evaluators
// ---------------------------------------------------------------------------
extern "C" int EvalBoolFactor(const char** p);          // 0x0083efd0 (slice 47)
extern "C" int EvalBoolExpression(const char** p);      // 0x0083f2e0
extern "C" int EvalBoolTerm(const char** p);            // 0x0083f140

// ===========================================================================
// 0x0083f140  EA::ArgScript::cExpression::EvalBoolTerm  ("and")
// ===========================================================================
// @ 0x0083f140
int __cdecl EvalBoolTerm(const char** p) {
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
        eastl::string8 name(start, *p);
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

// ===========================================================================
// 0x0083f2e0  EA::ArgScript::cExpression::EvalBoolExpression  ("or")
// ===========================================================================
// @ 0x0083f2e0
int __cdecl EvalBoolExpression(const char** p) {
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
        eastl::string8 name(start, *p);
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

// ===========================================================================
// 0x0083f480  EA::ArgScript::cExpression::EvalChar
// ===========================================================================
// @ 0x0083f480
int __cdecl EvalChar(const char** p) {
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

// ===========================================================================
// 0x0083f510  EA::ArgScript::cExpression::ParseBool
// ===========================================================================
// @ 0x0083f510
bool __cdecl ParseBool(const char* s) {
    if (*s == 0)
        throw cError("empty expression");
    int v = EvalBoolExpression(&s);
    if (*s != 0)
        throw cError("Garbage at end of bool expression");
    return v != 0;
}

// ---------------------------------------------------------------------------
// cFileParser / IHandlerRC / messaging
// ---------------------------------------------------------------------------
struct cIParser { void** vftable; };
struct IHandler { void** vftable; };
struct IHandlerRC { IHandler base; };
struct RefObject { void** vftable; int mRefCount; char pad[0x234]; };  // refcount at +0x240 dword

extern "C" void* __cdecl Messaging_GetServer();
extern "C" cIParser* __cdecl CreateParser();

// ===========================================================================
// 0x0083f580  `anonymous namespace'::FileMessageCallback
// ===========================================================================
// @ 0x0083f580
void __cdecl FileMessageCallback(void* arg) {
    int* server = (int*)Messaging_GetServer();
    if (server) {
        void* p = (arg == 0) ? 0 : (char*)arg + 4;
        ((void(__thiscall*)(int*, int, int, int, void*))(*(void***)server)[6])(server, 0x6f41f272, 0, 0, p);
        return;
    }
    if (arg) {
        int P = *(int*)((char*)arg + 4);
        ((void(__cdecl*)(int, int))(*(void**)(P + 4)))(0x6f41f272, 0);
    }
}

// ===========================================================================
// 0x0083f5e0  EA::ArgScript::cFileParser::Release
// ===========================================================================
// @ 0x0083f5e0
int __fastcall FileParser_Release(int* self) {
    int* rc = self + 2;           // mRefCount at +0x8
    *rc = *rc - 1;
    int r = *rc;
    if (r == 0) {
        ((void(__thiscall*)(int*, int))(*(void***)((char*)self + 4))[0])((int*)((char*)self + 4), 1);
        r = 0;
    }
    return r;
}

// ===========================================================================
// 0x0083f600  EA::ArgScript::cFileParser::HandleMessage
// ===========================================================================
// @ 0x0083f600
unsigned char __fastcall FileParser_HandleMessage(int* self, int, int msg, int) {
    if (msg != 0x6f41f272)
        return 0;
    *((unsigned char*)self + 0x24) = 1;      // mFilesModified
    if (*((unsigned char*)self + 0x25))      // mAutoParseEnabled
        ((void(__thiscall*)(int*))(*(void***)((char*)self - 4))[8])((int*)((char*)self - 4));
    return 1;
}

// ===========================================================================
// 0x0083f630  EA::ArgScript::cFileParser::Init
// ===========================================================================
// @ 0x0083f630
int __fastcall FileParser_Init(int* self) {
    if (*((unsigned char*)self + 0xc) == 0) {
        *((unsigned char*)self + 0xc) = 1;
        int* server = (int*)Messaging_GetServer();
        if (server)
            ((void(__thiscall*)(int*, int*, int))(*(void***)server)[8])(server, self + 1, 0x6f41f272);
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x0083f680  EA::ArgScript::cFileParser::Shutdown
// ===========================================================================
// @ 0x0083f680
int __fastcall FileParser_Shutdown(int* self) {
    if (*((unsigned char*)self + 0xc)) {
        *((unsigned char*)self + 0xc) = 0;
        int* server = (int*)Messaging_GetServer();
        if (server)
            ((void(__thiscall*)(int*, int*, int, int))(*(void***)server)[11])(server, self + 1, 0x6f41f272, 0xffffd8f1);
        if (self[4]) {
            ((void(__thiscall*)(int*))(*(void***)self[4])[3])((int*)self[4]);
            int* p = (int*)self[4];
            if (p) {
                self[4] = 0;
                ((void(__thiscall*)(int*))(*(void***)p)[1])(p);
            }
        }
        ((void(__thiscall*)(int*))(*(void***)self[0])[6])(self);
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x0083f6f0  EA::ArgScript::cFileParser::SetParser
// ===========================================================================
// @ 0x0083f6f0
void __fastcall FileParser_SetParser(int* self, int, cIParser* p) {
    cIParser* old = (cIParser*)self[4];
    if (old)
        ((void(__thiscall*)(cIParser*))(*(void***)old->vftable)[3])(old);
    old = (cIParser*)self[4];
    if (p != old) {
        if (p)
            ((void(__thiscall*)(cIParser*))(*(void***)p->vftable)[0])(p);
        self[4] = (int)p;
        if (old)
            ((void(__thiscall*)(cIParser*))(*(void***)old->vftable)[1])(old);
    }
    old = (cIParser*)self[4];
    if (old)
        ((void(__thiscall*)(cIParser*))(*(void***)old->vftable)[2])(old);
}

// ===========================================================================
// 0x0083f740  EA::ArgScript::cFileParser::Parser
// ===========================================================================
// @ 0x0083f740
cIParser* __fastcall FileParser_Parser(int* self) {
    if (self[4] == 0) {
        cIParser* p = CreateParser();
        cIParser* old = (cIParser*)self[4];
        if (p != old) {
            if (p)
                ((void(__thiscall*)(cIParser*))(*(void***)p->vftable)[0])(p);
            self[4] = (int)p;
            if (old)
                ((void(__thiscall*)(cIParser*))(*(void***)old->vftable)[1])(old);
        }
        ((void(__thiscall*)(cIParser*))(*(void***)((cIParser*)self[4])->vftable)[2])((cIParser*)self[4]);
    }
    return (cIParser*)self[4];
}

// ===========================================================================
// 0x0083f790  EA::ArgScript::cFileParser::ParseFiles
// ===========================================================================
// @ 0x0083f790
bool __fastcall FileParser_ParseFiles(int* self) {
    cIParser* parser = (cIParser*)self[4];
    if (parser != 0) {
        ((void(__thiscall*)(cIParser*))(*(void***)parser->vftable)[12])(parser);
        int* specsBegin = (int*)self[5];      // vector begin at +0x14
        int* specsEnd = (int*)self[6];
        unsigned count = (unsigned)((char*)specsEnd - (char*)specsBegin) / 0x14;
        for (unsigned i = 0; i < count; ++i) {
            ((void(__thiscall*)(cIParser*, void*))(*(void***)((cIParser*)self[4])->vftable)[14])(
                (cIParser*)self[4], (void*)specsBegin[i * 5]);
        }
        int* server = (int*)Messaging_GetServer();
        if (server) {
            int flag = 1;
            ((void(__thiscall*)(int*, int, int*, int))(*(void***)server)[5])(server, 0x4b3bc676, &flag, 0);
        }
    }
    return false;
}

// ===========================================================================
// 0x0083f8f0  AutoRefCount<RefCounted<FileChangeNotification>>::Release
// ===========================================================================
// @ 0x0083f8f0
void __fastcall RefRelease(int** p) {
    int* o = *p;
    if (o && --*(int*)((char*)o + 0x240) == 0) {
        *(int*)((char*)o + 0x240) = 1;
        ((void(__thiscall*)(int*, int))(*(void***)o)[0])(o, 1);
    }
}

// ===========================================================================
// 0x0083f940  AutoRefCount<RefCounted<FileChangeNotification>>::operator=
// ===========================================================================
// @ 0x0083f940
int** __fastcall RefAssign(int** self, int, int** other) {
    int* n = (int*)*other;
    int* o = (int*)*self;
    if (n != o) {
        if (n)
            (*(int*)((char*)n + 0x240))++;
        *self = n;
        if (o && --*(int*)((char*)o + 0x240) == 0) {
            *(int*)((char*)o + 0x240) = 1;
            ((void(__thiscall*)(int*, int))(*(void***)o)[0])(o, 1);
        }
    }
    return self;
}

// ===========================================================================
// 0x0083f990  pair<string,AutoRefCount<RefCounted>> copy ctor (from RefCounted*)
// ===========================================================================
// @ 0x0083f990
void** __fastcall PairCtorRef(void** self, int, void** src) {
    self[0] = 0; self[1] = 0; self[2] = 0;
    char* s = (char*)src[0];
    unsigned n = (unsigned)((char*)src[1] - s);
    ((eastl::string8*)self)->RangeInitialize(n + 1);
    ((eastl::string8*)self)->assign(*(eastl::string8*)src);
    int* o = (int*)src[4];
    self[4] = o;
    if (o)
        (*(int*)((char*)o + 0x240))++;
    return self;
}

// ===========================================================================
// 0x0083fa00  hashtable<pair<string,AutoRefCount<RefCounted>>>::hash_node dtor
// ===========================================================================
// @ 0x0083fa00
void __fastcall HashNodeDtorRef(int* self) {
    int* o = (int*)self[4];
    if (o && --*(int*)((char*)o + 0x240) == 0) {
        *(int*)((char*)o + 0x240) = 1;
        ((void(__thiscall*)(int*, int))(*(void***)o)[0])(o, 1);
    }
    int b = self[0];
    if ((self[2] - b) > 1 && b)
        EASTL_allocator_deallocate((void*)b);
}

// ===========================================================================
// 0x0083fa80  pair ctor (string + RefCounted*)
// ===========================================================================
// @ 0x0083fa80
void** __fastcall PairCtorRefPtr(void** self, int, void** src, int* val) {
    self[0] = 0; self[1] = 0; self[2] = 0;
    char* s = (char*)src[0];
    unsigned n = (unsigned)((char*)src[1] - s);
    ((eastl::string8*)self)->RangeInitialize(n + 1);
    ((eastl::string8*)self)->assign(*(eastl::string8*)src);
    int* o = (int*)val;
    self[4] = o;
    if (o)
        (*(int*)((char*)o + 0x240))++;
    return self;
}

// ===========================================================================
// 0x0083fae0  cInputFileSpec copy ctor
// ===========================================================================
// @ 0x0083fae0
void** __fastcall InputFileSpecCopy(void** self, int, void** src) {
    self[0] = 0; self[1] = 0; self[2] = 0;
    char* s = (char*)src[0];
    unsigned n = (unsigned)((char*)src[1] - s);
    ((eastl::string8*)self)->RangeInitialize(n + 1);
    ((eastl::string8*)self)->assign(*(eastl::string8*)src);
    *(uint16*)(self + 4) = *(uint16*)(src + 4);
    return self;
}

// ===========================================================================
// 0x0083fbc0  eastl::uninitialized_copy<cInputFileSpec*>
// ===========================================================================
// @ 0x0083fbc0
int* __cdecl UninitCopySpecs(int* first, int* last, int* dst) {
    if (first == last)
        return dst;
    do {
        if (dst) {
            dst[0] = 0; dst[1] = 0; dst[2] = 0;
            void* s = (void*)first[0];
            unsigned n = (unsigned)(first[1] - (int)s) + 1;
            if (n < 2) {
                dst[0] = (int)gEmptyString;
                dst[1] = (int)gEmptyString;
                dst[2] = (int)(gEmptyString + 1);
            } else {
                int p = (int)EASTL_allocator_allocate(n, g_allocName, 0, 0, g_allocFile, 0xd1);
                dst[0] = p; dst[1] = p; dst[2] = p + n;
            }
            memcpy((void*)dst[0], s, n - 1);
            ((char*)dst[0])[n - 1] = 0;
            dst[1] = dst[0] + (n - 1);
            *(uint16*)(dst + 4) = *(uint16*)(first + 4);
        }
        first += 5;
        dst += 5;
    } while (first != last);
    return dst;
}

// ===========================================================================
// 0x0083fcd0  eastl::copy_backward_impl<0>::do_copy<cInputFileSpec*>
// ===========================================================================
// @ 0x0083fcd0
int* __cdecl CopyBackwardSpecs(int* first, int* last, int* dst) {
    if (first == last)
        return dst;
    do {
        if (first != dst)
            ((eastl::string8*)dst)->assign(*(eastl::string8*)first);
        *(uint16*)(dst + 4) = *(uint16*)(first + 4);
        first += 5;
        dst += 5;
    } while (first != last);
    return dst;
}

// ===========================================================================
// 0x0083fd20  copy_backward of cInputFileSpec (back to front)
// ===========================================================================
// @ 0x0083fd20
int* __cdecl CopyBackwardSpecsRev(int* first, int* last, int* dst) {
    if (last == first)
        return dst;
    int* f;
    int* d;
    do {
        f = last - 5;
        d = dst - 5;
        if (f != d)
            ((eastl::string8*)f)->assign(*(eastl::string8*)d);
        *(uint16*)(dst - 1) = *(uint16*)(last - 1);
        last = f;
        dst = d;
    } while (f != first);
    return d;
}

// ===========================================================================
// 0x0083fde0  hashtable<...FileChangeNotification...>::DoInsertValue
// ===========================================================================
// @ 0x0083fde0
void __fastcall HashInsertFileNotify(int* self, int, int* outIt, int* key) {
    const unsigned char* p = (const unsigned char*)*key;
    uint32 h = 0x811c9dc5;
    unsigned char c = *p;
    while (c) { ++p; h = h * 0x1000193 ^ c; c = *p; }
    unsigned n = h % *(unsigned*)((char*)self + 8);
    char** slot = (char**)(*(char**)((char*)self + 4) + n * 4);
    char* node = *slot;
    char* chain = (char*)slot;
    for (;;) {
        if (node == 0) {
            int changed = 0;
            HashNodeAlloc(&changed, *(int*)((char*)self + 8), *(int*)((char*)self + 0xc), 1);
            node = (char*)MakeFileNotifyNode(key);
            if ((char)changed) {
                n = h % *(unsigned*)((char*)self + 0xc);
                HashDoRehash(*(void**)((char*)self + 4), *(int*)((char*)self + 0xc));
            }
            *(char**)(node + 0x14) = *(char**)(*(char**)((char*)self + 4) + n * 4);
            *(char**)(*(char**)((char*)self + 4) + n * 4) = node;
            ++*(int*)((char*)self + 0xc);
            *(char**)outIt = node;
            *((char**)outIt + 1) = (char*)*(void**)((char*)self + 4) + n * 4;
            *((unsigned char*)outIt + 8) = 1;
            return;
        }
        if (HashFindNode(key, node)) {
            *(char**)outIt = node;
            *((char**)outIt + 1) = chain;
            *((unsigned char*)outIt + 8) = 0;
            return;
        }
        chain = node + 0x14;
        node = *(char**)(node + 0x14);
    }
}

// ===========================================================================
// 0x0083fee0  hashtable<...FileChangeNotification...>::DoFreeNodes
// ===========================================================================
// @ 0x0083fee0
void __cdecl DoFreeNodesFileNotify(char** bucketArray, unsigned bucketCount) {
    for (unsigned i = 0; i < bucketCount; ++i) {
        char* n = *(char**)((char*)bucketArray + i * 4);
        while (n) {
            char* next = *(char**)(n + 0x14);
            HashNodeDtorRef((int*)n);
            EASTL_allocator_deallocate(n);
            n = next;
        }
        *(char**)((char*)bucketArray + i * 4) = 0;
    }
}

// ===========================================================================
// 0x0083ff30  hash_map<...FileChangeNotification...>::operator[]
// ===========================================================================
// @ 0x0083ff30
int __fastcall HashmapFileNotifyLookup(int* self, int, int key) {
    int out[8];
    HashFindFileNotify(self, out, (void*)key);
    if ((int)out[0] != *(int*)(*(int*)((char*)self + 4) + *(int*)((char*)self + 8) * 4))
        return out[0] + 0x10;
    int zero = 0;
    int val = (int)PairCtorRefPtr((void**)out, 0, (void**)key, &zero);
    HashInsertFileNotify(self, 0, out, (int*)key);
    return out[0] + 0x10 + (val - val);
}

// ===========================================================================
// 0x0083fff0  vector<cInputFileSpec>::insert/emplace at position
// ===========================================================================
// @ 0x0083fff0
void* __fastcall VectorSpecInsert(int* self, int, void* pos, void* val) {
    char* end = (char*)self[1];
    if (end != (char*)self[2]) {
        if ((char*)pos <= (char*)val && (char*)val < end)
            val = (char*)val + 0x14;
        if (end)
            InputFileSpecCopy((void**)end - 5, 0, (void**)(end - 0x14));
        CopyBackwardSpecsRev((int*)pos, (int*)(self[1] - 0x14), (int*)self[1]);
        if (val != pos)
            ((eastl::string8*)val)->assign(*(eastl::string8*)pos);
        *(uint16*)((char*)val + 0x10) = *(uint16*)((char*)pos + 0x10);
        self[1] += 0x14;
        return pos;
    }
    int cap = (int)((char*)end - (char*)self[0]) / 0x14;
    if (cap == 0)
        cap = 1;
    else
        cap *= 2;
    char* buf = cap ? (char*)EASTL_allocator_allocate(cap * 0x14, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
    int* mid = UninitCopySpecs((int*)self[0], (int*)pos, (int*)buf);
    if (mid)
        InputFileSpecCopy((void**)mid, 0, (void**)val);
    int* mid2 = UninitCopySpecs((int*)pos, (int*)self[1], mid + 5);
    if (self[0] && *(int*)((char*)self[0] - 4))
        EASTL_allocator_deallocate((void*)self[0]);
    self[1] = (int)mid2;
    self[0] = (int)buf;
    self[2] = (int)(buf + cap * 0x14);
    return pos;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct eastl {
    void RangeInitialize(unsigned int); // 0x00475ab0
};
struct string8 {
    ~string8(); // 0x00530670
};
}
