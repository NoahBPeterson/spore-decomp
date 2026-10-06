// Slice s007e17a0 (w2g5 slice 27).  Swarm transition-command / EASTL container
// helpers around 0x7e17a0.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

void* operator new(size_t size, const char* name, int a, int b, const char* file, int line);
void* operator new[](size_t size);
void  operator delete(void* p);
void  operator delete[](void* p);
void  __cdecl EFree(void* p);                       // 0x00f47380
void* __cdecl EAlloc6(int size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0

// ------------------------------------------------------------------- EASTL
namespace eastl {

extern char gEmptyBuf[];

struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
    EString() : mpBegin(gEmptyBuf), mpEnd(gEmptyBuf), mpCapacity(gEmptyBuf + 1), mAllocator(0) {}
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
    ~EString() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EFree(mpBegin); }
};

}  // namespace eastl

// ---------------------------------------------------------------- ArgScript
namespace EA {
namespace ArgScript {

class cArguments {
public:
    const char** MainArguments(int n);                              // 0x00838320
    const char** MainArguments(int* pCount, int min, int max);      // 0x00838020
    const char** OptionArguments(const char* name, int n);          // 0x00838330
};

struct cIParser {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36();                                            // +0x90
    virtual char  v37(const char* s);                              // +0x94
    virtual float v38(const char* s);                              // +0x98
    virtual int   v39(const char* s);                              // +0x9c
    virtual int   v40(const char* s);                              // +0xa0
};

struct cICommand {
    virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3();
    virtual void i4(); virtual void i5();
};

struct cCommandBase : cICommand {
    virtual void AddCommand(void* key, void* cmd);                  // +0x18
    cIParser* mParser;      // +0x4
    int       mRefCount;    // +0x8
};

struct cBlockCommandBase : cCommandBase {
    void* mChildState;      // +0xc
    char  mCommands[0x20];  // +0x10
};

void MakeCaseInsensitive(eastl::EString* s);                        // 0x008409b0

}  // namespace ArgScript
}  // namespace EA

// ------------------------------------------------------------ refcount auto
struct RefObj {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
};

// 8-byte element: refcounted pointer + dword
struct AutoRef {
    RefObj* p;
    int     field4;
};

struct AutoRefVal {
    AutoRef* mpBegin;
    AutoRef* mpEnd;
    AutoRef* mpCapacity;
    void DoInsertValue(AutoRef* pos, const AutoRef* v);   // 0x007e1340
};

static inline void AddRefObj(RefObj* p) {
    if (p) ((void(__thiscall*)(RefObj*))(*(void***)p)[1])(p);
}
static inline void ReleaseObj(RefObj* p) {
    if (p) ((void(__thiscall*)(RefObj*))(*(void***)p)[2])(p);
}
static inline void ReleaseRef(RefObj* p) {
    if (p) ((void(__thiscall*)(RefObj*))(*(void***)p)[0])(p);
}

// =============================================================== 0x007e17a0
// @ 0x007e17a0
AutoRef* FUN_007e17a0(AutoRef* dst, const AutoRef* first, const AutoRef* last) {
    for (; first != last; ++first) {
        if (dst) {
            dst->p = first->p;
            AddRefObj(first->p);
            dst->field4 = first->field4;
        }
        ++dst;
    }
    return dst;
}

// =============================================================== 0x007e1830
// @ 0x007e1830
AutoRef* FUN_007e1830(const AutoRef* first, const AutoRef* last, AutoRef* dst) {
    for (; first != last; ++first) {
        if (dst) {
            dst->p = first->p;
            AddRefObj(first->p);
            dst->field4 = first->field4;
        }
        ++dst;
    }
    return dst;
}

// =============================================================== 0x007e1910
struct cStateFlagCommand : EA::ArgScript::cCommandBase {
    void* mpState;   // +0xc
    void Execute(EA::ArgScript::cArguments& args);
};
// @ 0x007e1910
void cStateFlagCommand::Execute(EA::ArgScript::cArguments& args) {
    args.MainArguments(0);
    *(uint8_t*)((char*)mpState + 0x80) = 0;
}

// =============================================================== 0x007e1930
struct cStateFlag2Command : EA::ArgScript::cCommandBase {
    void* mpState;
    void Execute(EA::ArgScript::cArguments& args);
};
// @ 0x007e1930
void cStateFlag2Command::Execute(EA::ArgScript::cArguments& args) {
    args.MainArguments(0);
    *(uint8_t*)((char*)mpState + 0x80) = 1;
}

// =============================================================== 0x007e1a10
struct cSetStateCommand : EA::ArgScript::cCommandBase {
    void* mpState;
    void Execute(EA::ArgScript::cArguments& args);
};
// @ 0x007e1a10
void cSetStateCommand::Execute(EA::ArgScript::cArguments& args) {
    args.MainArguments(0);
    *(int*)((char*)mpState + 0x7c) = -1;
}

// =============================================================== 0x007e1950
struct HashTable {
    char pad0[4];
    int*   mpBuckets;      // +0x4
    int    mnBucketCount;  // +0x8
    int    mnElementCount; // +0xc
    void   rehash(int n);
};

void EAllocAndZero(void* dst, int zero, unsigned size);  // 0x011e073e

// @ 0x007e1950
void HashTable::rehash(int n) {
    unsigned size = n * 4;
    char* p = (char*)EAlloc6((int)(size + 4), "App", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    EAllocAndZero(p, 0, size);
    *(uint32_t*)(p + size) = 0xffffffff;
    unsigned i = 0;
    if (mnBucketCount != 0) {
        do {
            char* link = (char*)mpBuckets + i * 4;
            char* node = *(char**)link;
            while (node) {
                unsigned h = (*(uint32_t*)(node + 4) ^ *(uint32_t*)node) % n;
                *(char**)link = *(char**)(node + 0xc);
                *(char**)(node + 0xc) = *(char**)(p + h * 4);
                *(char**)(p + h * 4) = node;
                node = *(char**)link;
            }
            ++i;
        } while (i < (unsigned)mnBucketCount);
    }
    if (mnBucketCount > 1)
        EFree(mpBuckets);
    mpBuckets = (int*)p;
    mnBucketCount = n;
}

// =============================================================== 0x007e1a80
struct SomeDesc {
    char*  a0;  char* a1;    // +0x0  string1 (begin/end)
    char*  a8;  char* ac;    // +0x8  string2
    int    a10; void* a14; void* a18;   // +0x10 vector
    void*  p20;              // +0x20
    ~SomeDesc();
};
// @ 0x007e1a80
SomeDesc::~SomeDesc() {
    ReleaseRef((RefObj*)p20);
    if (a10 && a18 && (int)((char*)a18 - (char*)a10) > 1)
        EFree((void*)a10);
    if (a0 && a8 && (int)((char*)a8 - (char*)a0) > 1)
        EFree((void*)a0);
}

// =============================================================== 0x007e1b00
// @ 0x007e1b00
AutoRef* FUN_007e1b00(AutoRef* first, AutoRef* last, AutoRef* dst) {
    if (first == last)
        return dst;
    do {
        RefObj* src = first->p;
        RefObj* oldp = dst->p;
        if (src != oldp) {
            AddRefObj(src);
            dst->p = src;
            ReleaseObj(oldp);
        }
        dst->field4 = first->field4;
        ++first;
        ++dst;
    } while (first != last);
    return dst;
}

// =============================================================== 0x007e1b60
// cTransitionCommand::OnRegister - registers 16 empty sub-commands.
#define CMDCLASS(Name) struct Name : EA::ArgScript::cCommandBase {}
CMDCLASS(CmdEntry);
CMDCLASS(CmdExit);
CMDCLASS(CmdGotoState);
CMDCLASS(CmdMessage);
CMDCLASS(CmdEffect);
CMDCLASS(CmdKillEffect);
CMDCLASS(CmdEffectFlag);
CMDCLASS(CmdMode);
CMDCLASS(CmdDescription);
CMDCLASS(CmdCheat);
CMDCLASS(CmdLoadResource);
CMDCLASS(CmdLighting);
CMDCLASS(CmdCamera);
CMDCLASS(CmdBoolProp);
CMDCLASS(CmdIntProp);
CMDCLASS(CmdFloatProp);
#undef CMDCLASS

extern void* g_kEntry;   // 0x153f5f8
extern void* g_kExit;    // 0x153f5fc
extern void* g_kGoto;    // 0x153f600
extern void* g_kMessage; // 0x153f604
extern void* g_kEffect;  // 0x153f608
extern void* g_kKill;    // 0x153f60c
extern void* g_kEffFlag; // 0x153f610
extern void* g_kMode;    // 0x153f614
extern void* g_kDesc;    // 0x153f618
extern void* g_kCheat;   // 0x153f61c
extern void* g_kLoad;    // 0x153f620
extern void* g_kLight;   // 0x153f624
extern void* g_kCam;     // 0x153f628
extern void* g_kBool;    // 0x153f62c
extern void* g_kInt;     // 0x153f630
extern void* g_kFloat;   // 0x153f634

struct cTransitionCommand : EA::ArgScript::cBlockCommandBase {
    void OnRegister(void* a, void* childState);
};
void* operator new(size_t, const char*, int, int, int, int);

// @ 0x007e1b60
void cTransitionCommand::OnRegister(void* a, void* childState) {
    mChildState = childState ? (void*)((char*)childState - 0x10) : 0;
    ((void(__thiscall*)(void*, void*, void*))0)(this, a, childState);
    AddCommand(g_kEntry,    new ("ArgScript/Entry",0,0,0,0) CmdEntry());
    AddCommand(g_kExit,     new ("ArgScript/Exit",0,0,0,0) CmdExit());
    AddCommand(g_kGoto,     new ("ArgScript/GotoState",0,0,0,0) CmdGotoState());
    AddCommand(g_kMessage,  new ("ArgScript/Message",0,0,0,0) CmdMessage());
    AddCommand(g_kEffect,   new ("ArgScript/Effect",0,0,0,0) CmdEffect());
    AddCommand(g_kKill,     new ("ArgScript/KillEffect",0,0,0,0) CmdKillEffect());
    AddCommand(g_kEffFlag,  new ("ArgScript/EffectFlag",0,0,0,0) CmdEffectFlag());
    AddCommand(g_kMode,     new ("ArgScript/Mode",0,0,0,0) CmdMode());
    AddCommand(g_kDesc,     new ("ArgScript/Description",0,0,0,0) CmdDescription());
    AddCommand(g_kCheat,    new ("ArgScript/Cheat",0,0,0,0) CmdCheat());
    AddCommand(g_kLoad,     new ("ArgScript/LoadResource",0,0,0,0) CmdLoadResource());
    AddCommand(g_kLight,    new ("ArgScript/Lighting",0,0,0,0) CmdLighting());
    AddCommand(g_kCam,      new ("ArgScript/Camera",0,0,0,0) CmdCamera());
    AddCommand(g_kBool,     new ("ArgScript/BoolProp",0,0,0,0) CmdBoolProp());
    AddCommand(g_kInt,      new ("ArgScript/IntProp",0,0,0,0) CmdIntProp());
    AddCommand(g_kFloat,    new ("ArgScript/FloatProp",0,0,0,0) CmdFloatProp());
}

// =============================================================== 0x007e29d0
struct HashTable2 {
    char pad0[4];
    int* mpBuckets;      // +0x4
    int  mnBucketCount;  // +0x8
    int  mnElementCount; // +0xc
};
void* FUN_00921440(void* out, void* ecx_holder, int a, int b);   // 0x00921440
void* HashInsert(void* self, void* out, const AutoRef* key, int* hint); // 0x007e29d0
// @ 0x007e29d0
void* HashInsert(void* self, void* out, const AutoRef* key, int* hint) {
    HashTable2* t = (HashTable2*)self;
    char* dummy = 0;
    unsigned h = ((uint32_t)key->p ^ (uint32_t)key->field4) % t->mnBucketCount;
    char* node = *(char**)((char*)t->mpBuckets + h * 4);
    while (node) {
        if (*(uint32_t*)node == (uint32_t)key->p && *(uint32_t*)(node + 4) == (uint32_t)key->field4)
            break;
        node = *(char**)(node + 0xc);
    }
    (void)hint; (void)dummy; (void)out;
    return node;
}

// =============================================================== 0x007e2fb0
struct cTransitionListCommand : EA::ArgScript::cCommandBase {
    void* mpState;
    void Execute(EA::ArgScript::cArguments& args);
};
// @ 0x007e2fb0
void cTransitionListCommand::Execute(EA::ArgScript::cArguments& args) {
    const char** av = args.MainArguments(2);
    int a = mParser->v39(av[0]);
    char b = mParser->v37(av[1]);
    char* vec = (char*)mpState + 0x54;
    AutoRef* end = *(AutoRef**)(vec + 4);
    if (end < *(AutoRef**)(vec + 8)) {
        *(AutoRef**)(vec + 4) = end + 1;
        if (end) {
            *(uint32_t*)end = (uint32_t)a;
            *(uint32_t*)((char*)end + 4) = (uint32_t)(uint8_t)b;
        }
    } else {
        AutoRef tmp;
        tmp.p = (RefObj*)a;
        tmp.field4 = (uint8_t)b;
        ((AutoRefVal*)vec)->DoInsertValue(end, &tmp);
    }
}

// =============================================================== 0x007e3030
struct cStateNameMap {
    char pad0[4];
    int* mpBuckets;      // +0x4
    int  mnBucketCount;  // +0x8
    int  mnElementCount; // +0xc
};
struct cAppStateManagerX {
    char pad00[0xf8];
    cStateNameMap mMap;         // +0xf8
    char pad104[0x60];
    eastl::EString mName;       // +0x164
    int StateIDFromName(const char* name);
};
void hashtablefind(void* out, void* table, eastl::EString* key);  // 0x007e2ea0
// @ 0x007e3030
int cAppStateManagerX::StateIDFromName(const char* name) {
    const char* e = name;
    while (*e) ++e;
    mName.assign(name, e);
    EA::ArgScript::MakeCaseInsensitive(&mName);
    int it[2];
    hashtablefind(it, &mMap, &mName);
    if (it[0] != mMap.mpBuckets[mMap.mnBucketCount])
        return *(int*)((char*)it[0] + 0x10);
    return -1;
}

// =============================================================== 0x007e30a0
void FUN_007e2ce0(void* thisp, int idx);   // 0x007e2ce0
void hashfind2(void* out, void* table, void* key); // 0x007e2960
// @ 0x007e30a0
void FUN_007e30a0(void* self, int a, int b) {
    int key[2];
    key[0] = a;
    key[1] = b;
    int it[2];
    char* tbl = (char*)self + 0xd8;
    hashfind2(it, tbl, key);
    if (it[0] != *(int*)(tbl + 4 + *(int*)(tbl + 8) * 4))
        FUN_007e2ce0(self, *(int*)((char*)it[0] + 8));
}

// =============================================================== 0x007e2ae0
void FUN_007e2520(void* a, void* b);              // 0x007e2520
void FUN_006a40a0(int n, void* a);                // 0x006a40a0
void* eastl_copy(void* out, void* f, void* l, void* d, void* a); // 0x0076ffd0
void RangeInitialize(eastl::EString* s, unsigned n); // 0x00475ab0
void VectorBoolInsert(void* pos, void* f, unsigned n); // 0x011e0744
// @ 0x007e2ae0
cAppStateManagerX* FUN_007e2ae0(cAppStateManagerX* self, char* src) {
    FUN_007e2520(self, src);
    FUN_007e2520((char*)self + 0x14, src + 0x14);
    FUN_006a40a0((*(int*)(src + 0x2c) - *(int*)(src + 0x28)) >> 3, src + 0x34);
    eastl_copy(0, src + 0x28, src + 0x2c, 0, 0);
    *(void**)((char*)self + 0x2c) = 0;
    *(void**)((char*)self + 0x3c) = 0;
    *(void**)((char*)self + 0x40) = 0;
    *(void**)((char*)self + 0x44) = 0;
    unsigned n = *(int*)(src + 0x40) - *(int*)(src + 0x3c);
    eastl::EString* s = (eastl::EString*)((char*)self + 0x3c);
    RangeInitialize(s, n + 1);
    VectorBoolInsert(*(void**)((char*)self + 0x40), *(void**)(src + 0x3c), n);
    *(int*)((char*)self + 0x4c) = *(int*)(src + 0x4c);
    return self;
}

// =============================================================== 0x007e2ce0
void* MessageServer();                             // 0x0067dcc0
void* EffectsManager();                            // 0x0067ddd0
void SetMessageString8(void* msg, int a, void* s); // 0x00618bd0
// @ 0x007e2ce0
void FUN_007e2ce0(void* self, int idx) {
    char* piVar5 = (char*)(*(int*)((char*)self + 0xa4) + idx * 0x50);
    MessageServer();
    unsigned n = (*(int*)(piVar5 + 4) - *(int*)piVar5) >> 3;
    unsigned i = 0;
    if (n != 0) {
        do {
            char* e = *(char**)piVar5 + i * 8;
            int iVar1 = *(int*)e;
            void* piVar2 = MessageServer();
            if ((e[4] & 1) == 0) {
                int p2 = *(int*)(iVar1 + 0x30);
                if (*(int*)((char*)self + 0x14) == 0)
                    ((void(__thiscall*)(void*, int, int, int, int))(*(void***)piVar2)[6])(piVar2, p2, iVar1, 0, (int)self + 4);
                else if (*(int*)((char*)self + 0x14) == 1)
                    ((void(__thiscall*)(void*, int, int, int))(*(void***)piVar2)[5])(piVar2, p2, iVar1, (int)self + 4);
            } else {
                int p2 = *(int*)(iVar1 + 0x30);
                if (*(int*)((char*)self + 0x14) == 0)
                    ((void(__thiscall*)(void*, int, int, int, int))(*(void***)piVar2)[6])(piVar2, p2, iVar1, 0, 0);
                else if (*(int*)((char*)self + 0x14) == 1)
                    ((void(__thiscall*)(void*, int, int, int))(*(void***)piVar2)[5])(piVar2, p2, iVar1, 0);
            }
            ++i;
        } while (i < (unsigned)((*(int*)(piVar5 + 4) - *(int*)piVar5) >> 3));
    }
    void* em = EffectsManager();
    if (em) {
        unsigned k = 0;
        unsigned m = (*(int*)(piVar5 + 0x2c) - *(int*)(piVar5 + 0x28)) >> 3;
        while (k < m) {
            char* e = *(char**)(piVar5 + 0x28) + k * 8;
            ((void(__thiscall*)(void*, int, uint8_t))(*(void***)em)[0x98 / 4])(em, *(int*)e, (uint8_t)e[4]);
            ++k;
        }
    }
    int f = *(int*)(piVar5 + 0x4c);
    if (f != -1)
        *(int*)((char*)self + 0x8c) = f;
    if (*(char*)((char*)self + 0x81) && *(int*)(piVar5 + 0x3c) != *(int*)(piVar5 + 0x40)) {
        void* msg = EAlloc6(0x40, "App", 0, 0, 0, 0);
        if (msg) {
            *(int*)((char*)msg + 0x30) = 0;
            *(void**)msg = (void*)0x13eb90c;
            *(int*)((char*)msg + 4) = 0;
            *(int*)((char*)msg + 0x38) = 0;
            *(void**)msg = (void*)0x13eb844;
        }
        SetMessageString8(msg, 0, (void*)*(int*)(piVar5 + 0x3c));
        *(void**)((char*)msg + 0x10) = self;
        void* ms = MessageServer();
        if (*(int*)((char*)self + 0x14) == 0)
            ((void(__thiscall*)(void*, int, void*, int, int))(*(void***)ms)[6])(ms, 0xe11331, msg, 0, 0);
        else if (*(int*)((char*)self + 0x14) == 1)
            ((void(__thiscall*)(void*, int, void*, int))(*(void***)ms)[5])(ms, 0xe11331, msg, 0);
    }
}

// =============================================================== 0x007e3160
struct AVec {
    AutoRef* mpBegin;
    AutoRef* mpEnd;
    AutoRef* mpCapacity;
};
extern "C" void* FUN_007e25a0(unsigned n, void* a, void* b); // 0x007e25a0
extern "C" void  FUN_007e1a50(void* a, void* b);             // 0x007e1a50
// @ 0x007e3160
AutoRef* AVec_assign(AVec* self, const AVec* o) {
    if (o == self)
        return self->mpBegin;
    unsigned n = (unsigned)((o->mpEnd - o->mpBegin));
    unsigned cap = (unsigned)((self->mpCapacity - self->mpBegin));
    if (cap < n) {
        AutoRef* p = (AutoRef*)FUN_007e25a0(n, o->mpBegin, o->mpEnd);
        FUN_007e1a50(self->mpBegin, self->mpEnd);
        if (self->mpBegin && *(int*)((char*)self->mpBegin - 4))
            EFree(self->mpBegin);
        self->mpCapacity = p + n;
        self->mpEnd = p + n;
        self->mpBegin = p;
        return p;
    }
    unsigned have = (unsigned)(self->mpEnd - self->mpBegin);
    if (have < n) {
        FUN_007e1b00(o->mpBegin, o->mpBegin + have, self->mpBegin);
        FUN_007e17a0(self->mpBegin + have, o->mpBegin + have, o->mpEnd);
        self->mpEnd = self->mpBegin + n;
        return self->mpBegin;
    }
    AutoRef* e = FUN_007e1b00(o->mpBegin, o->mpEnd, self->mpBegin);
    FUN_007e1a50(e, self->mpEnd);
    self->mpEnd = self->mpBegin + n;
    return self->mpBegin;
}
