// Slice s007ea440.
#include "../s007e5220/s007e5220.h"
#include <intrin.h>

extern "C" void operator_delete__(void* p);

struct DateTime { int a; int b; void Set(int kind); };

// @ 0x007EAEF0
struct ObjAE {
    char pad[0x30];
    int  f30;   // +0x30
    int  f34;   // +0x34
    void FUN_007eaef0();
};
void ObjAE::FUN_007eaef0() {
    DateTime dt;
    dt.Set(2);
    f30 = dt.a;
    f34 = dt.b;
}

// @ 0x007EAF30
struct ObjAF {
    void* Cast(int id);
};
void* ObjAF::Cast(int id) {
    if (id == 0x45a9b42)
        return (char*)this - 8;
    return 0;
}

// @ 0x007EB060  (copy ints [first,last) to dst)
void FUN_007eb060(int first, int last, int* dst) {
    if (first != last) {
        int off = first - (int)dst;
        do {
            if (dst)
                *dst = *(int*)(off + (int)dst);
            ++dst;
        } while (off + (int)dst != last);
    }
}

// @ 0x007EB090  (rbtree node count)
struct ObjB0 { int FUN_007eb090(); };
int ObjB0::FUN_007eb090() {
    int self = (int)this;
    int* bucket = *(int**)(self + 0x10);
    int node = *bucket;
    int count = 0;
    if (node == 0) {
        ++bucket;
        node = *bucket;
        while (node == 0) {
            ++bucket;
            node = *bucket;
        }
    }
    int end = *(int*)(*(int*)(self + 0x10) + *(int*)(self + 0x14) * 4);
    while (node != end) {
        int n = 0;
        for (int* p = *(int**)(node + 4); p != (int*)(node + 4); p = (int*)*p)
            ++n;
        count += n;
        node = *(int*)(node + 0x10);
        while (node == 0) {
            ++bucket;
            node = *bucket;
        }
    }
    return count;
}

// @ 0x007EB100  (hashtable find)
struct HashTable {
    char pad0[4];
    int* mpBucketArray;   // +4
    int  mnBucketCount;   // +8
    void find(void* out, void* key);
};
struct ObjB1 {
    char pad[0xc];
    HashTable ht;         // +0xc
    int FUN_007eb100(int key);
};
int ObjB1::FUN_007eb100(int key) {
    int local;
    ht.find(&local, (void*)key);
    if (local != ht.mpBucketArray[ht.mnBucketCount])
        return local + 4;
    return 0;
}

// @ 0x007EB360  (vector assign from another)
struct VecB { int* begin; int* end; int* cap; };
struct ObjB3 {
    int* begin; int* end; int* cap;
    void FUN_007eb000(int n, void* tag);
    ObjB3* FUN_007eb360(VecB* src);
};
ObjB3* ObjB3::FUN_007eb360(VecB* src) {
    FUN_007eb000((src->end - src->begin) >> 2, src + 1);
    int* s = src->begin;
    int* d = begin;
    while (s != src->end) {
        if (d)
            *d = *s;
        ++s; ++d;
    }
    end = d;
    return this;
}

// @ 0x007EB3B0  (copy [src,..) backwards)
struct ObjB3b { int* begin; int* end; void copyDown(int* dst, int* src); };
void ObjB3b::copyDown(int* dst, int* src) {
    int* d = dst;
    for (int* s = src; s != end; ++s) {
        *d = *s;
        ++d;
    }
    end += ((int)src - (int)dst >> 2) * -4;
}

// @ 0x007EB3F0  (free list nodes)
struct ObjB3f { int* first; void freeNodes(); };
void ObjB3f::freeNodes() {
    int* node = *(int**)this;
    while (node != (int*)this) {
        int p = node[5];
        int* next = (int*)*node;
        if (p && *(int*)(p - 4))
            operator_delete__((void*)p);
        operator_delete__(node);
        node = next;
    }
}

// ---------------------------------------------------------------------------
// 0x007EAA10  SP::cAppSystem::InitGraphics
// ---------------------------------------------------------------------------
static inline void** VT(void* p) { return *(void***)p; }

extern "C" void operator_delete__(void* p);                                  // 0x00f47380
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d); // 0x00f473a0
extern const wchar_t gEmptyString16[];                                       // 0x01667bac
extern const wchar_t g_str_0141420c;                                         // "pix" switch name
extern void* const g_vtbl_01413930;                                          // QuitCheat command vtable

struct CmdLine {
    int FindSwitch(const wchar_t* name, int a, int b, int c);                // 0x0092b300
};
void FUN_00c2e4e0(int a, int b);                                             // 0x00c2e4e0
void FUN_0067df50(void* p);                                                  // 0x0067df50
void* __fastcall FUN_007c3f70(void* p, void* edx);                           // 0x007c3f70 cViewer ctor
bool __fastcall FUN_007c4dd0(void* viewer, void* edx, bool b);               // 0x007c4dd0 cViewer::Init
void __fastcall FUN_007c4b50(void* viewer, void* edx, float f);              // 0x007c4b50
void* FUN_0067dd50();                                                        // 0x0067dd50
bool FUN_00688830(int id, void* out, int b);                                 // 0x00688830
void FUN_004e0850(void* str, const wchar_t* fmt, void* obj);                 // 0x004e0850
void __fastcall FUN_00599bb0(void* str, void* edx, const wchar_t* s);        // 0x00599bb0 operator+=
bool FUN_00931fa0(const wchar_t* path);                                      // 0x00931fa0 File::Exists
void* FUN_0067dd70();                                                        // 0x0067dd70 MaterialManager
void* FUN_0093c570(void* dst, const void* src);                              // 0x0093c570 ConvertToString8
void* FUN_00a72bc0();                                                        // 0x00a72bc0
void* FUN_0067ddf0();                                                        // 0x0067ddf0
void FUN_0067dff0(void* p);                                                  // 0x0067dff0
void FUN_007e6210(void* p);                                                  // 0x007e6210 LoadGameInfoProperties
void* FUN_0067de00();                                                        // 0x0067de00
void __fastcall FUN_007e66a0(void* p, void* edx);                            // 0x007e66a0 PropWatcher::Check
void __fastcall FUN_007e9a00(void* p, void* edx);                            // 0x007e9a00 LoadEffectCollections
void FUN_00a74fd0(void* p);                                                  // 0x00a74fd0
void FUN_00a73ec0(void* p);                                                  // 0x00a73ec0
void* FUN_0067de20();                                                        // 0x0067de20 CheatManager
void __fastcall FUN_0083c800(void* p, void* edx);                            // 0x0083c800 cCommandBase ctor
void __fastcall FUN_007ea2f0(void* p, void* edx);                            // 0x007ea2f0
extern void* g_0153f85c;                                                     // 0x0153f85c

struct WStr16 {
    const wchar_t* mpBegin;      // +0
    const wchar_t* mpEnd;        // +4
    const wchar_t* mpCapacity;   // +8
    WStr16() {
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCapacity = gEmptyString16 + 1;
    }
    ~WStr16() {
        if ((((int)((char*)mpCapacity - (char*)mpBegin)) & ~1) > 2 && mpBegin)
            operator_delete__((void*)mpBegin);
    }
};
struct CStr8 {
    char* mpBegin;       // +0
    char* mpEnd;         // +4
    char* mpCapacity;    // +8
    void* mAllocator;    // +0xc
};

// cAppSystem member layout used here (fields from +0x58 on)
struct InitObj {
    char pad00[0x14];
    void* mpMessageServer;      // +0x14
    char pad18[0x40];
    void* mpViewer;             // +0x58
    void* mpGraphics;           // +0x5c
    void* mpEffectsManager;     // +0x60
    void* mpEffectsParser;      // +0x64
    char  mEffectProperties[0x20];  // +0x68
    char  mPropWatcher[0x40];       // +0x88
    void* mpPluginLibraries;    // +0xc8
    char  pad_cc[0x0c];
    float mfD8;                 // +0xd8
    int   mDC;                  // +0xdc
    void* mpE0;                 // +0xe0
    int   mE4;                  // +0xe4
    bool InitGraphics(void* commandLine);
};

// @ 0x007EAA10
bool InitObj::InitGraphics(void* commandLine)
{
    CmdLine* const cmd = (CmdLine*)commandLine;

    if (cmd->FindSwitch(L"dumpShaders", 0, 0, 0) != -1) {
        FUN_00c2e4e0(1, 0);
        FUN_00c2e4e0(1, 0);
    }
    if (cmd->FindSwitch(L"dumpShadersForPIX", 0, 0, 0) != -1 ||
        cmd->FindSwitch(&g_str_0141420c, 0, 0, 0) != -1) {
        FUN_00c2e4e0(1, 1);
        FUN_00c2e4e0(1, 1);
    }
    if (cmd->FindSwitch(L"dumpFragmentShaders", 0, 0, 0) != -1)
        FUN_00c2e4e0(1, 0);
    if (cmd->FindSwitch(L"dumpDirectShaders", 0, 0, 0) != -1)
        FUN_00c2e4e0(1, 0);

    bool noScripts = cmd->FindSwitch(L"noScripts", 0, 0, 0) != -1;
    bool noMaterial = noScripts ? true : (cmd->FindSwitch(L"noMaterialScripts", 0, 0, 0) != -1);
    if (!(noMaterial && noScripts))
        cmd->FindSwitch(L"noEffectScripts", 0, 0, 0);

    FUN_0067df50(mpGraphics);
    if (mpGraphics != 0)
        ((void (__thiscall*)(void*))VT(mpGraphics)[0x0c / 4])(mpGraphics);

    void* const mem = operator new(0x174, "App", 0, 0, 0, 0);
    void* viewer = mem != 0 ? FUN_007c3f70(mem, 0) : 0;
    mpViewer = viewer;
    FUN_007c4dd0(viewer, 0, false);
    ((unsigned char*)mpViewer)[0x16c] = 0;

    {
        void* const info = FUN_0067dd50();
        const int* const dims = (const int*)((void* (__thiscall*)(void*))VT(info)[0x1c / 4])(info);
        FUN_007c4b50(mpViewer, 0, *(const float*)((const char*)dims + 0x1c) *
                                     ((float)dims[0] / (float)dims[1]));
    }

    ((void (__thiscall*)(void*))VT(mpPluginLibraries)[0x0c / 4])(mpPluginLibraries);
    ((void (__thiscall*)(void*, void*))VT(mpPluginLibraries)[0x54 / 4])(mpPluginLibraries, mpViewer);

    WStr16 smt;
    if (!noMaterial) {
        if (FUN_00688830(0xa0214e, &smt, 0)) {
            if (cmd != 0)
                FUN_004e0850(&smt, L"%hs.smt", cmd);
            else
                FUN_00599bb0(&smt, 0, L"config.smt");
            if (FUN_00931fa0(smt.mpBegin)) {
                void* const matMgr = FUN_0067dd70();
                CStr8 name8;
                FUN_0093c570(&name8, &smt);
                ((void (__thiscall*)(void*, char*))VT(matMgr)[0x18 / 4])(matMgr, name8.mpBegin);
                if ((name8.mpCapacity - name8.mpBegin) > 1 && name8.mpBegin)
                    operator_delete__(name8.mpBegin);
            }
        }
    }

    {
        void* const fxNew = FUN_00a72bc0();
        void* const fxOld = mpEffectsManager;
        if (fxNew != fxOld) {
            if (fxNew != 0)
                ((void (__thiscall*)(void*))VT(fxNew)[0x08 / 4])(fxNew);
            mpEffectsManager = fxNew;
            if (fxOld != 0)
                ((void (__thiscall*)(void*))VT(fxOld)[0x0c / 4])(fxOld);
        }
    }
    ((void (__thiscall*)(void*, void*))VT(mpEffectsManager)[0x10 / 4])(mpEffectsManager, FUN_0067ddf0());
    ((void (__thiscall*)(void*))VT(mpEffectsManager)[0x00 / 4])(mpEffectsManager);
    FUN_0067dff0(mpEffectsManager);
    FUN_007e6210(mEffectProperties);
    ((void (__thiscall*)(void*, void*))VT(mpEffectsManager)[0xa8 / 4])(mpEffectsManager, mEffectProperties);

    {
        void* const libs = FUN_0067de00();
        void* const r1 = ((void* (__thiscall*)(void*))VT(mpPluginLibraries)[0x50 / 4])(mpPluginLibraries);
        void* const r2 = ((void* (__thiscall*)(void*, void*))VT(mpPluginLibraries)[0x58 / 4])(mpPluginLibraries, r1);
        ((void (__thiscall*)(void*, void*))VT(libs)[0x84 / 4])(libs, r2);
    }
    ((void (__thiscall*)(void*, void*))VT(mpEffectsManager)[0x18 / 4])(mpEffectsManager, FUN_0067de00());
    FUN_007e66a0(mPropWatcher, 0);
    FUN_007e9a00(this, 0);

    if (mpEffectsParser != 0) {
        if (cmd->FindSwitch(L"noDevEffects", 0, 0, 0) != -1)
            ((void (__thiscall*)(void*, int, int))VT(mpEffectsParser)[0x10 / 4])(mpEffectsParser, 4, 1);
    }

    FUN_00a74fd0(mpEffectsManager);
    FUN_00a73ec0(mpEffectsManager);

    {
        void* const obj = FUN_0067dd50();
        if (obj != 0) {
            void* const r = ((void* (__thiscall*)(void*))VT(mpPluginLibraries)[0x58 / 4])(mpPluginLibraries);
            ((void (__thiscall*)(void*, int, void*))VT(obj)[0x2c / 4])(obj, 0, r);
        }
    }

    {
        void* const ms = mpMessageServer;
        ((void (__thiscall*)(void*, void*, int))VT(ms)[0x20 / 4])(ms, (char*)this + 4, 0xf62add);
        ((void (__thiscall*)(void*, void*, int))VT(ms)[0x20 / 4])(ms, (char*)this + 4, 0xae1cfe73);
        ((void (__thiscall*)(void*, void*, int))VT(ms)[0x20 / 4])(ms, (char*)this + 4, 0x255abf5);
        ((void (__thiscall*)(void*, void*, int))VT(ms)[0x20 / 4])(ms, (char*)this + 4, 0x212d3e7);
    }

    {
        void* const p = operator new(0x10, "App", 0, 0, 0, 0);
        if (p != 0) {
            FUN_0083c800(p, 0);
            *(void**)p = (void*)&g_vtbl_01413930;
        }
        void* const cheats = FUN_0067de20();
        ((void (__thiscall*)(void*, void*, void*, int))VT(cheats)[0x18 / 4])(cheats, g_0153f85c, p, 0);
    }

    {
        void* const q = operator new(0xe8, "App", 0, 0, 0, 0);
        if (q != 0)
            FUN_007ea2f0(q, 0);
    }
    FUN_0067de20();
    return true;
}

// ---------------------------------------------------------------------------
// 0x007EB140  SP::cTelemetry::Write  (serializer interface)
// ---------------------------------------------------------------------------
bool FUN_0093aa70(void* stream, const void* p, int n, int flags);   // EA::IO::WriteUint32
bool FUN_0093ab10(void* stream, const void* p, int n, int flags);   // EA::IO::WriteUint64

struct TDataVec {
    float* mpBegin;       // +0x0
    float* mpEnd;         // +0x4
    float* mpCapacity;    // +0x8
    void*  mpName;        // +0xc
    uint32_t mFlags;      // +0x10
};
struct TItemValue {
    int64_t  mSystemTime;  // +0x0
    uint32_t mType;        // +0x8
    TDataVec mData;        // +0xc
};
struct TItemListNode {
    TItemListNode* mpNext;   // +0x0
    TItemListNode* mpPrev;   // +0x4
    TItemValue     mValue;   // +0x8
};
struct TItemList {
    TItemListNode* mpNext;   // +0x0  sentinel
    TItemListNode* mpPrev;   // +0x4
    uint32_t mnSize;         // +0x8
};
struct TItemMapNode {
    uint32_t mKey;           // +0x0
    TItemList mList;         // +0x4
    TItemMapNode* mpNext;    // +0x10
};
struct TItemMap {
    uint32_t mHash;               // +0x0
    TItemMapNode** mpBucketArray; // +0x4
    uint32_t mnBucketCount;       // +0x8
    uint32_t mnElementCount;      // +0xc
    float mfMaxLoadFactor;        // +0x10
    float mfGrowthFactor;         // +0x14
    uint32_t mnNextResize;        // +0x18
    uint32_t mAllocator;          // +0x1c
    struct Iterator {
        TItemMapNode* mpNode;     // +0x0
        TItemMapNode** mpBucket;  // +0x4
    };
    Iterator find(uint32_t key) {
        uint32_t n = key % mnBucketCount;
        for (TItemMapNode* p = mpBucketArray[n]; p != 0; p = p->mpNext) {
            if (p->mKey == key) {
                Iterator it = { p, mpBucketArray + n };
                return it;
            }
        }
        Iterator it = { mpBucketArray[mnBucketCount], mpBucketArray + mnBucketCount };
        return it;
    }
};
// the cISerializableObject subobject of SP::cTelemetry (mStats begins at +4 here)
struct CTelemetryObj {
    void* mpVtbl;        // +0x0
    TItemMap mStats;     // +0x4
    int      mPad24;     // +0x24
    int64_t  mSession;   // +0x28
    bool Write(void* writer);
};

// serializer: v8() returns the object whose v6() is the byte stream, v13 writes raw bytes
struct IWriterObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void* v6();                       // +0x18
};
struct IWriter {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual IWriterObj* v8();                 // +0x20
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual bool v13(const void* p, int n);   // +0x34
};

// @ 0x007EB140
bool CTelemetryObj::Write(void* writer)
{
    IWriter* const w = (IWriter*)writer;
    int magic = 0x45a9b42;
    FUN_0093aa70(w->v8()->v6(), &magic, 1, 0);

    for (uint32_t key = 7; key <= 0xc; ++key) {
        TItemMap::Iterator it = mStats.find(key);
        TItemList* pList = it.mpNode == mStats.mpBucketArray[mStats.mnBucketCount]
                               ? 0
                               : (TItemList*)((char*)it.mpNode + 4);
        int n = 0;
        if (pList != 0) {
            for (TItemListNode* p = pList->mpNext; p != (TItemListNode*)pList; p = p->mpNext)
                ++n;
        }
        FUN_0093aa70(w->v8()->v6(), &n, 1, 0);
        if (pList == 0)
            continue;
        for (TItemListNode* p = pList->mpNext; p != (TItemListNode*)pList; p = p->mpNext) {
            int count = (int)(p->mValue.mData.mpEnd - p->mValue.mData.mpBegin);
            FUN_0093aa70(w->v8()->v6(), &p->mValue.mType, 1, 0);
            FUN_0093ab10(w->v8()->v6(), &p->mValue.mSystemTime, 1, 0);
            FUN_0093aa70(w->v8()->v6(), &count, 1, 0);
            w->v13(p->mValue.mData.mpBegin, count << 2);
        }
    }
    int64_t session = mSession;
    FUN_0093ab10(w->v8()->v6(), &session, 1, 0);
    return true;
}

// ---------------------------------------------------------------------------
// 0x007EA440  ArgScript property-dump command handler (thiscall, 1 stack arg)
// ---------------------------------------------------------------------------
void __cdecl Output(void* out, const char* fmt, ...);                       // 0x00841000 EA::ArgScript::Output
char __cdecl FUN_00685520(int index);                                       // 0x00685520 IsWorldLayoutFlagSet
int  __cdecl FUN_00685500(int index);                                       // 0x00685500 world
void __cdecl FUN_00687a20(void* names, void* ids);                           // 0x00687a20 Iterate2
void* __cdecl FUN_0067de30();                                                // 0x0067de30 SP::PropertyManager
void* __cdecl FUN_0067dd00();                                                // 0x0067dd00 SP::AppSystem
void* __cdecl FUN_0067dcc0();                                                // 0x0067dcc0 SP::MessageServer
bool __cdecl GetPropertyAsKey(void* list, uint32_t id, void* out);           // 0x006a1250 (out = ResourceKey{instance,type,group})
bool __cdecl GetPropertyAsText(void* list, uint32_t id, void* out);          // 0x006a1360 (out = cString)
WStr16* __cdecl FUN_0093c5a0(WStr16* out, const void* src, int len);        // 0x0093c5a0 EA::ConvertToString16
extern char gDocSep[];                                                       // 0x01401b70 (1-char record separator)

struct ArgArgs {                       // EA::ArgScript::cArguments
    char* mpBegin;                     // +0x0
    char* mpEnd;                       // +0x4
    char* mpCap;                       // +0x8
    int  NumArguments();               // 0x00837f30
    char* operator[](int i);           // 0x00837f20
};
struct cArgumentSpec {                 // EA::ArgScript::cArgumentSpec
    char pad[0x10];
    const char* HelpString(const char* name, int style);                     // 0x0083a2f0
    void Parse(ArgArgs* args, void* output);                                 // 0x0083b9d0
};
struct CString16 {                     // SP::cString (EASTL wstring + allocator)
    wchar_t* mpBegin;                  // +0x0
    wchar_t* mpEnd;                    // +0x4
    wchar_t* mpCapacity;               // +0x8
    void*    mpAllocator;              // +0xc
    void ctor();                       // 0x006b5060
    void dtor();                       // 0x006b5240
    const wchar_t* GetText();          // 0x006b55c0
};
struct ResKey { uint32_t instance; uint32_t type; uint32_t group; };

// a property value: vtable, [+0x10] storage flags, [+0x12] type tag
struct Property {
    uint32_t* mpValue;                 // +0x0 (heap value when mFlags & 0x30)
    char pad04[0xc];
    uint8_t  mFlags;                   // +0x10
    char pad11;
    uint16_t mType;                    // +0x12
};
static inline const void* PropByte(const Property* p) {
    return (p->mFlags & 0x30) ? (const void*)p->mpValue : (const void*)p;
}
static inline bool PropGet(Property* p, uint32_t id, Property** out) {
    return ((bool (__thiscall*)(Property*, uint32_t, Property**))VT(p)[0x24 / 4])(p, id, out);
}
static inline bool PropIsSigned(Property* p) {
    return ((bool (__thiscall*)(Property*, int))VT(p)[0x1c / 4])(p, 0);
}

struct WStr16L {                       // 16-byte EASTL wide string element
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mpAllocator;
};
struct WStrVecL {
    WStr16L* mpBegin;
    WStr16L* mpEnd;
    WStr16L* mpCapacity;
    WStrVecL() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~WStrVecL() {
        for (WStr16L* p = mpBegin; p != mpEnd; ++p) {
            if ((((int)((char*)p->mpCapacity - (char*)p->mpBegin)) & ~1) > 2 && p->mpBegin)
                operator_delete__(p->mpBegin);
        }
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};
struct U32VecL {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    U32VecL() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~U32VecL() {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};

// cAppSystem subobject owning the dump handler (vtbl +0, output +4, spec +0x10)
struct DumpObj {
    void* mpVtbl;                      // +0x0
    void* mpOutput;                    // +0x4
    char  pad08[8];
    cArgumentSpec mSpec;               // +0x10
    char  pad20[0x80 - 0x20];
    uint32_t mFlags;                   // +0x80
    char  pad84[0xd8 - 0x84];
    float mfD8;                        // +0xd8
    int   mDC;                         // +0xdc
    void* mpE0;                        // +0xe0
    int   mE4;                         // +0xe4
    void DumpProperties(void* args);
};

// @ 0x007EA440
void DumpObj::DumpProperties(void* argsRaw)
{
    ArgArgs* const args = (ArgArgs*)argsRaw;
    if (args->NumArguments() == 1) {
        Output(mpOutput, mSpec.HelpString((*args)[0], 1));
        return;
    }
    mSpec.Parse(args, mpOutput);

    if ((mFlags >> 1) & 1) {
        for (int i = 0; i < 3; i++) {
            if (FUN_00685520(i))
                Output(mpOutput, "%02d = 0x%08x\n", i, FUN_00685500(i));
        }
        WStrVecL names;
        U32VecL ids;
        FUN_00687a20(&names, &ids);
        int n = (int)(names.mpEnd - names.mpBegin);
        for (int i = 0; i < n; i++) {
            WStr16L key = names.mpBegin[i];
            Output(mpOutput, "Add-on 0x%08x has key %ls\n", ids.mpBegin[i], key.mpBegin);
        }
    }

    if (mFlags & 1) {
        void* const pm = FUN_0067de30();
        U32VecL ids;
        ((void (__thiscall*)(void*, uint32_t, void*))VT(pm)[0x48 / 4])(pm, 0x40404000, &ids);
        int n = (int)(ids.mpEnd - ids.mpBegin);
        Property* prev = 0;
        for (int i = 0; i < n; i++) {
            uint32_t id = ids.mpBegin[i];
            if (id == 1)
                continue;
            if (prev != 0)
                ((void (__thiscall*)(void*))VT(prev)[4 / 4])(prev);
            if (!((bool (__thiscall*)(void*, uint32_t, uint32_t, Property**))
                      VT(pm)[0x2c / 4])(pm, id, 0x40404000, &prev))
                continue;

            ResKey K = { 0, 0, 0 };
            CString16 text;
            text.ctor();
            uint32_t key = 0;
            Property* pk = 0;
            if (prev != 0 && PropGet(prev, 0x6ef59e7, &pk) && pk->mType == 10)
                key = *(const uint32_t*)PropByte(pk);
            else if (GetPropertyAsKey(prev, 0x6ef59e7, &K))
                key = K.instance;

            GetPropertyAsText(prev, 0x6ef59e4, &text);
            Output(mpOutput, "%3d. 0x%08x  %ls (0x%08x)", i, id, text.GetText(), key);

            if (PropIsSigned(prev))
                Output(mpOutput, "[signed]");

            if (prev != 0) {
                Property* pb = 0;
                if (PropGet(prev, 0x6ef59e8, &pb) && pb->mType == 1 &&
                    *(const char*)PropByte(pb) != 0)
                    Output(mpOutput, "[bless]");
                Property* pe = 0;
                if (PropGet(prev, 0x6ef59eb, &pe) && pe->mType == 1 &&
                    *(const char*)PropByte(pe) != 0)
                    Output(mpOutput, "[entitle]");
            }
            Output(mpOutput, gDocSep);
            text.dtor();
        }
        if (prev != 0)
            ((void (__thiscall*)(void*))VT(prev)[4 / 4])(prev);
    }

    if ((mFlags >> 2) & 1) {
        void* const a = FUN_0067dd00();
        ((void (__thiscall*)(void*))VT(a)[0x2c / 4])(a);
    }
    if ((mFlags >> 3) & 1) {
        void* const a = FUN_0067dd00();
        ((void (__thiscall*)(void*))VT(a)[0x30 / 4])(a);
    }
    if ((mFlags >> 4) & 1) {
        void* const m = FUN_0067dcc0();
        ((void (__thiscall*)(void*, int, int, int, int))VT(m)[0x18 / 4])(m, 0x153c326, 0, 0, 0);
    }
    if ((mFlags >> 5) & 1) {
        void* const a = FUN_0067dd00();
        ((void (__thiscall*)(void*, float))VT(a)[0x38 / 4])(a, mfD8);
    }
    if ((mFlags >> 6) & 1) {
        void* const a = FUN_0067dd00();
        ((void (__thiscall*)(void*, int))VT(a)[0x3c / 4])(a, mDC);
    }
    if ((mFlags >> 7) & 1) {
        void* const a = FUN_0067dd00();
        ((void (__thiscall*)(void*))VT(a)[0x6c / 4])(a);
    }
    if ((mFlags >> 8) & 1) {
        void* const a = FUN_0067dd00();
        ((void (__thiscall*)(void*))VT(a)[0x70 / 4])(a);
    }
    if ((mFlags >> 9) & 1) {
        void* const a = FUN_0067dd00();
        ((void (__thiscall*)(void*))VT(a)[0x60 / 4])(a);
    }
    if ((mFlags >> 0xa) & 1) {
        void* const a = FUN_0067dd00();
        WStr16 tmp;
        FUN_0093c5a0(&tmp, mpE0, -1);
        ((void (__thiscall*)(void*, const wchar_t*))VT(a)[0x5c / 4])(a, tmp.mpBegin);
    }
    if ((mFlags >> 0xb) & 1) {
        void* const a = FUN_0067dd00();
        ((void (__thiscall*)(void*))VT(a)[0x8c / 4])(a);
    }
    if ((mFlags >> 0xc) & 1)
        operator new((unsigned)(mE4 << 0x14), "App", 0, 0, 0, 0);
}
