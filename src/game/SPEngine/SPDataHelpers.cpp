// src/game/SPEngine/SPDataHelpers.cpp -- migrated from slice(s) s006870a0, s006860e0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPDataHelpers.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/ResourceMan/KeyFilter.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* MemsetT(void*, int, uint32_t);                   // 0x011e073e
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t); // 0x0f473a0
extern "C" char  g_allocTag[];                    // 0x013ebc58 "App"
extern "C" char  g_fileEASTL[];                   // 0x013ebb38
extern "C" void __cdecl ReadInt32(void*, void*, int, int);        // 0x093a780
extern "C" int*  __cdecl GetManager();                            // 0x067dcd0

// ---- SP/EA intrusive hashtable (shared by the global map at 0x0152b5f8) ----
struct HashIter {
    void*  mpNode;      // +0x00
    void** mpBucket;    // +0x04
};
struct HashIterPair {
    HashIter first;     // +0x00
    uint8_t  second;    // +0x08
    uint8_t  pad[3];
};
struct Hashtable {
    char pad00[0x04];   // +0x00
    void** mpBucket;    // +0x04
    int    mnBucket;    // +0x08
    int    mnCount;     // +0x0c
    char pad10[0x08];   // +0x10..+0x17
    void FreeNodes();                       // 0x0685ed0
    HashIter find(const void* key);         // 0x0685f30
    HashIter erase(HashIter i);             // 0x06859b0
    HashIterPair insert(const void* value, const void* hint); // 0x0685f90
};

// ---- items of slice s006860e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  EASTL_dealloc(void*);                            // 0x0f47380
extern "C" bool __cdecl ReadByte2(void*, void*, int, int);        // 0x093a700
extern const wchar_t kSlash[];   // 0x013fa030 L"/"
static inline void** VT(void* p) { return *(void***)p; }
extern "C" bool __cdecl ReadInt32_s0068_60e0(void*, void*, int, int);        // 0x093a780
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCap;
    uint32_t mAlloc;
    void assign(const wchar_t* first, const wchar_t* last);  // 0x0423650 (out-of-slice)
    WStr& operator=(const WStr& x) {
        if (&x != this) assign(x.mpBegin, x.mpEnd);
        return *this;
    }
};
struct Elem {
    uint8_t flag;       // +0x00
    uint8_t pad[3];
    uint32_t f4;        // +0x04
    WStr a;             // +0x08
    WStr b;             // +0x18
    __forceinline Elem& operator=(const Elem& x) {
        flag = x.flag; f4 = x.f4; a = x.a; b = x.b;
        return *this;
    }
};
struct cPropertyList {
    void* vtbl;                 // +0x00
    volatile int mRef;          // +0x04
    uint32_t f08, f0c, f10, f14;
    uint32_t f18[6];            // +0x18 (mPropertyMap)
    void* mModCount;            // +0x30 (retail: pointer to a refcounted object)
    uint32_t f34;               // +0x34
    bool Read(void* stream);    // 0x006a2f60
    cPropertyList();            // 0x006a1c40 (Editor::cPropertyList ctor, out of slice)
    ~cPropertyList();
};
struct HashMap {
    uint32_t f0;
    int* buckets;               // +0x04
    int bucketCount;            // +0x08
    int* operator[](const int* key);
};
struct WFixed {
    wchar_t* mpBegin;           // +0
    wchar_t* mpEnd;             // +4
    WFixed* Append(const wchar_t* s);
    void append(const wchar_t* first, const wchar_t* last);   // 0x042f9d0 (out-of-slice)
};
struct VecBuf {
    int* b; int* e; int* c;
    uint32_t padc, pad10;                    // allocator (0x14-byte object)
    int* Init(uint32_t n, void* tag);
    ~VecBuf() { if (b && b[-1]) EASTL_dealloc(b); }
};
void __cdecl SHA1(const void* data, int len, void* md);                            // 0x0117b180
void* __cdecl FUN_01179f50();                                                      // 0x01179f50 (RSA_new)
void* __cdecl FUN_0117ac80(const void* s, int len, void* ret);                     // 0x0117ac80 (BN_bin2bn)
int  __cdecl BN_dec2bn(void** a, const char* str);                                 // 0x0117a720
int  __cdecl FUN_0117a150(int type, const void* m, uint32_t mlen, void* sig, uint32_t siglen, void* rsa); // 0x0117a150 (RSA_verify)
struct RSAKey { uint32_t pad[4]; void* n; void* e; };                              // +0x10 n, +0x14 e
void* operator new(unsigned size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0
bool __cdecl GetPropertyAsUint32(cPropertyList*, uint32_t id, uint32_t* out);      // 0x004af210
struct ResKey { uint32_t instance, type, group; };
bool __cdecl GetPropertyAsKey(cPropertyList*, uint32_t id, ResKey* out);          // 0x006a1250
bool __cdecl GetBoolProperty(cPropertyList*, uint32_t id, bool* out);             // 0x00407190
bool __cdecl GetPropertyAsUint32Array(cPropertyList*, uint32_t id, int* count, uint32_t** out); // 0x006a0840
uint32_t* __cdecl FindU32(uint32_t* first, uint32_t* last, const uint32_t& v);     // 0x005c1cc0
uint32_t __cdecl SPIDFromName(const char*);                                        // 0x00571cf0
void __cdecl FullPath(wchar_t* out, const wchar_t* in, int a, int b);              // 0x00930670
uint32_t __cdecl DriveHash(uint32_t drive);                                        // 0x006b8ca0
uint32_t __cdecl FNV1_String16(const wchar_t* s, uint32_t seed, int a);            // 0x00932f30
bool __cdecl RegGetU32(uint32_t root, const wchar_t* path, const wchar_t* name, uint32_t* out); // 0x006ab6c0
bool __cdecl ISteamApps(uint32_t appId);                                           // 0x006b4f40
int* __cdecl MessageServer();                                                      // 0x0067dcc0
bool __cdecl GetPropertyAsString16(cPropertyList*, uint32_t id, WStr* out);      // 0x006a1400
struct Property { char pad[0x12]; uint16_t type; int* GetInt(); uint32_t* GetUInt(); };      // 0x41e990 / 0x41ea00
struct PLPtr {
    cPropertyList* p;
    PLPtr() : p(0) {}
    void Assign(cPropertyList* q);
    ~PLPtr() { if (p) ((void (__thiscall*)(void*))VT(p)[1])(p); }
};
struct RecPtr {
    void* p;
    RecPtr() : p(0) {}
    void** Addr();                                                                          // 0x00c463d0
    ~RecPtr() { if (p) ((void (__thiscall*)(void*))VT(p)[2])(p); }
};
struct KeyFilter {
    void* vtbl;
    int f4, f8, fc, f10, f14, f18, f1c, f20;
    int* begin; int* end; int* cap;
    KeyFilter() {
        begin = 0; end = 0; cap = 0;
        vtbl = (void*)0x013eb898;
        f4 = -1;
        f8 = *(int*)0x0152b544;
        f10 = -1;
        f14 = 0xb1b104;
    }
    ~KeyFilter() {
        vtbl = (void*)0x013eb394;
        if (begin && begin[-1]) EASTL_dealloc(begin);
    }
};
struct WStrL : WStr {
    WStrL() { mpBegin = (wchar_t*)0x1667bac; mpEnd = (wchar_t*)0x1667bac; mpCap = (wchar_t*)0x1667bae; }
    ~WStrL();                                                                               // 0x00933960
};
static inline void RecClose(void* r) { ((void (__thiscall*)(void*))VT(r)[0x24 / 4])(r); }
static inline bool SrcOpen(void* src, void* key, void** out) {
    return ((bool (__thiscall*)(void*, void*, void**, int, int, int, int))VT(src)[0x34 / 4])
        (src, key, out, 1, 6, 1, 0);
}
__declspec(noinline) unsigned char DecodeRecord(void* rd, uint32_t key, uint32_t size, uint8_t flag);  // 0x00686520 (defined below; used by a stub's inline body)
static inline void* RecStream(void* r);  // 0x006866f0 (defined below; used by a stub's inline body)
bool ReadPropRecords(void* src, int dflt) {
    PLPtr pl;
    uint32_t key = 0;
    bool ok = false;
    KeyFilter flt;
    int st = ((int (__thiscall*)(void*, void*, void*))VT(src)[0x30 / 4])(src, &flt.begin, &flt);
    bool success = false;
    if (st == 0) {
        success = true;
    } else if (st == 1) {
        RecPtr r1;
        if (SrcOpen(src, flt.begin, &r1.p)) {
            if (DecodeRecord(RecStream(r1.p), 0x1402de0, 0x80, 0)) {
                pl.Assign(new ("App", 0, 0, 0, 0) cPropertyList());
                ok = ((bool (__thiscall*)(void*, void*))VT(pl.p)[0x3c / 4])(pl.p, RecStream(r1.p));
                ResKey K = {0, 0, 0};
                GetPropertyAsUint32(pl.p, 0x6ef59e7, &key);
                if (!GetPropertyAsUint32(pl.p, 0x6ef59e7, &key)) {
                    if (GetPropertyAsKey(pl.p, 0x6ef59e7, &K))
                        key = K.instance;
                }
                if (ok) {
                    bool b;
                    if (*(uint32_t**)0x152b548 != *(uint32_t**)0x152b54c) {
                        if (GetBoolProperty(pl.p, 0x6ef59eb, &b) && b)
                            ok = FindU32(*(uint32_t**)0x152b548, *(uint32_t**)0x152b54c, key) != *(uint32_t**)0x152b54c;
                    }
                    if (ok) {
                        if (*(uint32_t**)0x152b5a0 != *(uint32_t**)0x152b5a4) {
                            uint32_t* arr; int cnt;
                            if (GetPropertyAsUint32Array(pl.p, 0x6ef59e6, &cnt, &arr)) {
                                ok = false;
                                for (int i = 0; i < cnt; i++) {
                                    if (FindU32(*(uint32_t**)0x152b5a0, *(uint32_t**)0x152b5a4, arr[i]) != *(uint32_t**)0x152b5a4) {
                                        ok = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (ok) {
                        if (GetBoolProperty(pl.p, 0x6ef59e8, &b) && b) {
                            ok = false;
                            ResKey B;
                            B.instance = SPIDFromName("Bless");
                            B.type = 0xb1b104;
                            B.group = 0x40004000;
                            RecPtr r2;
                            if (SrcOpen(src, &B, r2.Addr())) {
                                cPropertyList plB;
                                if (DecodeRecord(RecStream(r2.p), 0x1402e60, 0x80, 0) &&
                                    plB.Read(RecStream(r2.p))) {
                                    uint32_t u32 = 0;
                                    WStrL S1;
                                    WStrL S2;
                                    if (GetPropertyAsUint32(&plB, 0x6ef59e8, &u32) &&
                                        GetPropertyAsString16(&plB, 0x6ef59ea, &S1) &&
                                        GetPropertyAsString16(&plB, 0x6ef59e9, &S2)) {
                                        wchar_t buf[260];
                                        FullPath(buf, ((const wchar_t* (__thiscall*)(void*))VT(src)[0x28 / 4])(src), 0, 4);
                                        uint32_t seed = 0x811c9dc5;
                                        if (buf[1] == 0x3a && (buf[2] == 0x5c || buf[2] == 0x2f))
                                            seed = DriveHash(*(uint32_t*)buf);
                                        uint32_t h = FNV1_String16(S1.mpBegin, FNV1_String16(S2.mpBegin, seed, 0), 0) ^ u32;
                                        uint32_t bid;
                                        if (RegGetU32(0x80000002, S1.mpBegin, L"BlessID", &bid))
                                            ok = (h == bid);
                                    }
                                }
                                RecClose(r2.p);
                            } else {
                                if (((bool (__thiscall*)(void*, uint32_t))VT(pl.p)[0x1c / 4])(pl.p, 0x7634d70)) {
                                    void* prop = ((void* (__thiscall*)(void*, uint32_t))VT(pl.p)[0x28 / 4])(pl.p, 0x7634d70);
                                    ok = ISteamApps(*((Property*)prop)->GetUInt());
                                }
                            }
                        }
                    }
                }
            }
            RecClose(r1.p);
        }
        success = ok;
    }
    if (success) {
        int v = dflt;
        if (st == 1 && pl.p) {
            Property* pr;
            if (((bool (__thiscall*)(void*, uint32_t, Property**))VT(pl.p)[0x24 / 4])(pl.p, 0x6ef59e5, &pr) && pr->type == 9)
                v = *pr->GetInt();
        }
        int* mgr = GetManager();
        ((void (__thiscall*)(void*, int, void*, int))VT(mgr)[0x50 / 4])(mgr, 1, src, v);
        if (pl.p) {
            int* ms = MessageServer();
            ((void (__thiscall*)(void*, uint32_t, int, int, int))VT(ms)[0x18 / 4])(ms, 0x6f20a6d, 0, 0, 0);
        }
        return true;
    }
    if (key != 0) {
        for (int i = 0; i <= *(int*)0x0152b348; i++) {
            Elem* a = *(Elem**)0x015fea00;
            if (a[i].flag != 0 && a[i].f4 == key) a[i].flag = 0;
        }
    }
    ((void (__thiscall*)(void*))VT(src)[2])(src);
    return false;
}
struct IRefSub { virtual void AddRef(); virtual void Release(); };
struct DPFile {
    void* vtbl;          // +0
    IRefSub sub;         // +4
    char pad08[0x388 - 8];
    DPFile(const wchar_t* path, void* alloc);                                   // 0x008d9f80
    static void* operator new(size_t, const char*, int, int, int, int);         // 0x00926020
    static void operator delete(void*, const char*, int, int, int, int);
};
struct DPFile;
struct RefGuard {
    DPFile* p;
    RefGuard(DPFile* q);
    ~RefGuard();
};
struct WPath {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap;
    WPath(const wchar_t* s) : mpBegin(0), mpEnd(0), mpCap(0) { RangeInitialize(s); }
    ~WPath() { if ((int)(((char*)mpCap - (char*)mpBegin) & 0xfffffffe) > 2 && mpBegin) EASTL_dealloc(mpBegin); }
    void RangeInitialize(const wchar_t* s);                                     // 0x00579a90
    void Append(const wchar_t* first, const wchar_t* last);                     // 0x00429580
    WPath& operator+=(const wchar_t* s) {
        const wchar_t* e = s;
        while (*e) ++e;
        int n = (int)(e - s);
        Append(s, s + n);
        return *this;
    }
};
struct WEmpty {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap;
    WEmpty() : mpBegin((wchar_t*)0x1667bac), mpEnd((wchar_t*)0x1667bac), mpCap((wchar_t*)0x1667bae) {}
    ~WEmpty() { if ((int)(((char*)mpCap - (char*)mpBegin) & 0xfffffffe) > 2 && mpBegin) EASTL_dealloc(mpBegin); }
};
void __cdecl SPNameFromKeyW(const ResKey* key, void* outStr, const wchar_t* sfx);   // 0x0068d0d0
bool ReadPropRecords(void* src, int dflt);   // 0x006866f0
inline RefGuard::RefGuard(DPFile* q) : p(q) { p->sub.AddRef(); }
inline RefGuard::~RefGuard() { p->sub.Release(); }
// ---- items of slice s006860e0 end

// ---- items of slice s006870a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char __cdecl FUN_00685710(const wchar_t*, void*);       // 0x0685710
extern "C" int  g_count;                    // 0x0152b348
extern "C" char* g_array;                   // 0x015fea00
extern "C" void* GetDefaultAllocatorX();                           // 0x00925cb0
extern "C" void* ZoneObject_new(int, const char*, int, int, int, int); // 0x00926020
extern "C" void  FUN_00685770(void*, const wchar_t*, int);         // 0x00685770
extern "C" const wchar_t* GetDirFromID(uint32_t);                  // 0x006886b0
extern "C" bool  Directory_Exists(const wchar_t*);                 // 0x009322b0
typedef char (__cdecl *PkgFilter)(const wchar_t*, void*);
extern "C" int  __cdecl RegisterPackages(void*, const void*, PkgFilter, void*, int); // 0x06872f0
struct Elem28 {
    uint8_t flag;
    uint8_t pad[3];
    uint32_t f4;
    uint32_t a[4];
    uint32_t b[4];
    Elem28(const Elem28& x);   // 0x00685a60 (thiscall, ret 4)
    ~Elem28();                 // 0x00d167e0
};
struct Elem28Out {
    Elem28* p;
    Elem28Out(Elem28* x) : p(x) {}
};
Elem28Out __cdecl UninitCopy28(Elem28* first, Elem28* last, Elem28* dest);       // 0x00685b40
void      __cdecl UninitFillN28(Elem28* first, uint32_t n, const Elem28& v);     // 0x00685bc0
Elem28*   __cdecl UninitReloc28(Elem28* first, Elem28* last, Elem28* dest);      // 0x00685c40
Elem28*   __cdecl DestroyRange28(Elem28* first, Elem28* last, Elem28* out);      // 0x00685cd0
Elem28*   __cdecl CopyBack28(Elem28* first, Elem28* last, Elem28* dstLast);      // 0x00686150
void      __cdecl Fill28(Elem28* first, Elem28* last, const Elem28& v);          // 0x00686290
struct Vec28 {
    Elem28* b; Elem28* e; Elem28* c;
    void ResizeLoop(Elem28* position, uint32_t n, const Elem28& value);   // 0x06870a0
    void DestroyRangeChunk(char* first, char* last);   // 0x0687050
    void Reserve(uint32_t n);                          // 0x0687ab0 (below)
};
struct DequeIter { void* mpCurrent; void* mpBegin; void* mpEnd; void* mpCurrentArrayPtr; };
struct DirDeque {
    void**   mpPtrArray;      // +0x00
    uint32_t mnPtrArraySize;  // +0x04
    DequeIter mItBegin;       // +0x08
    DequeIter mItEnd;         // +0x18
    void*    mAlloc;          // +0x28
    void*    mAllocCtx;       // +0x2c
    DirDeque() {
        mpPtrArray = 0;
        mnPtrArraySize = 0;
        mItBegin.mpCurrent = mItBegin.mpBegin = mItBegin.mpEnd = mItBegin.mpCurrentArrayPtr = 0;
        mItEnd.mpCurrent = mItEnd.mpBegin = mItEnd.mpEnd = mItEnd.mpCurrentArrayPtr = 0;
        mAlloc = GetDefaultAllocatorX();
        mAllocCtx = 0;
        Init(0);
    }
    ~DirDeque() { Destroy(); }
    void Init(uint32_t n);   // 0x005f8840  (DequeBase::DoInit)
    void Destroy();          // 0x005f96c0  (DequeBase dtor)
};
struct DirectoryIterator {
    void* f0; void* f4; void* f8; void* fc;
    void Read(const wchar_t* path, void* out, const wchar_t* pattern,
              int a, int b, int c);                                // 0x0092ef40
};
struct WideFixedBuf {
    wchar_t* mBegin;
    wchar_t* mEnd;
    wchar_t* mCapacity;
    uint32_t mPad;
    wchar_t* mFixed;
    wchar_t  mBuf[256];
    WideFixedBuf() {
        mBegin = mBuf; mEnd = mBuf; mFixed = mBuf; mCapacity = mBuf + 256; mBuf[0] = 0;
    }
    ~WideFixedBuf() {
        if ((int)(((unsigned)mCapacity - (unsigned)mBegin) & ~1u) > 2 && mBegin && mBegin != mFixed)
            EASTL_dealloc(mBegin);
    }
    WideFixedBuf& assign(const wchar_t* p) {
        if (mBegin != p) {
            if (mBegin != mEnd) { *mBegin = 0; mEnd = mBegin; }
            const wchar_t* e = p;
            while (*e) ++e;
            append(p, e);
        }
        return *this;
    }
    WideFixedBuf& append(const wchar_t* pBegin, const wchar_t* pEnd);  // 0x0042f9d0
};
struct DirEntry {
    uint32_t f0;            // +0x00
    wchar_t* name;          // +0x04
    uint32_t f8, fc, f10, f14, f18, f1c, f20, f24, f28, f2c;
};
struct IRefCounted { virtual void AddRef(); virtual void Release(); };
struct DPFBase {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual bool v6(int, int, int);
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void v11(const wchar_t*);
};
struct DatabasePackedFile : DPFBase, IRefCounted {
    void Construct(const wchar_t* name, void* alloc);            // 0x008d9f80
};
extern "C" void* GetManager_s0068_70a0();                                     // 0x0067dcd0
struct cDirectPropertyList {
    bool GetDescription(uint32_t) const;                           // 0x006a25a0
};
extern "C" cDirectPropertyList* g_propList;                        // 0x015fd918
struct WStrT {
    wchar_t* mBegin;
    wchar_t* mEnd;
    wchar_t* mCap;
    void*    mAlloc;
    void RangeInitialize(const wchar_t* s);                        // 0x00579a90
    WStrT& Append(const wchar_t* pBegin, const wchar_t* pEnd);     // 0x00429580
    ~WStrT() {
        if ((int)(((unsigned)mCap - (unsigned)mBegin) & ~1u) > 2 && mBegin)
            EASTL_dealloc(mBegin);
    }
};
struct VecWStrT {
    WStrT*   mBegin;
    WStrT*   mEnd;
    WStrT*   mCap;
    uint32_t mPad;
    WStrT    mBuf[8];
    VecWStrT() { mBegin = mEnd = mBuf; mCap = mBuf + 8; mPad = 0; }
    ~VecWStrT() {
        DoDestroyValues(mBegin, mEnd);
        if (mBegin && *(uint32_t*)((char*)mBegin - 4) != 0)
            EASTL_dealloc(mBegin);
    }
    void push_back(const WStrT* v);                                // 0x00553f10
    void DoDestroyValues(WStrT* first, WStrT* last);               // 0x0084aad0
};
struct PkgCtx { const wchar_t* base; void* names; };
struct DDFBase {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual bool v6(int, int, int);
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void v11(const wchar_t*);
};
struct DatabaseDirectoryFiles : DDFBase, IRefCounted {
    void Construct(const wchar_t* dir, void* alloc);               // 0x008d7400
};
typedef void (__thiscall *MgrSlot50)(void*, int, void*, int);
typedef void (__thiscall *MgrSlot90)(void*, int, const wchar_t*);
// ---- items of slice s006870a0 end

// @ 0x00686380
int* HashMap::operator[](const int* key)
{
    HashIter it = ((Hashtable*)this)->find(key);
    if (it.mpNode == (void*)(*(int*)((char*)buckets + bucketCount * 4))) {
        int value[3];
        value[0] = *key;
        value[1] = 0;
        value[2] = 0;
        it = ((Hashtable*)this)->insert(value, key).first;
    }
    return (int*)((char*)it.mpNode + 4);
}

// @ 0x006863e0
WFixed* WFixed::Append(const wchar_t* s)
{
    if (mpBegin != s) {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
        const wchar_t* p = s;
        while (*p) ++p;
        int n = (int)(p - s);
        append(s, s + n);
    }
    return this;
}

// @ 0x00686430
int* VecBuf::Init(uint32_t n, void* tag)
{
    (void)tag;
    void* p = n ? EASTL_alloc6(n, g_allocTag, 0, 0, g_fileEASTL, 0xd1) : 0;
    b = (int*)p;
    e = (int*)p;
    c = (int*)((char*)p + n);
    if (n > 0)
        MemsetT(p, 0, n);
    e = (int*)((char*)b + n);
    return (int*)this;
}

// @ 0x00686490
extern "C" int OpenRecordAsStream(int arg)
{
    int* mgr = GetManager();
    if (mgr == 0) return -1;
    int* rec = (int*)((void* (__thiscall*)(void*, int))VT(mgr)[0x58 / 4])(mgr, arg);
    if (rec == 0) return -1;
    char buf[8];
    char ok = ((char (__thiscall*)(void*, int, void*, int, int, int))VT(rec)[0x34 / 4])
                  (rec, arg, buf, 1, 6, 1);
    if (ok) {
        int* ctr = (int*)0x015fe7b8;
        *ctr = *ctr + 1;
        int* slot = ((HashMap*)0x0152b5f8)->operator[](ctr);
        slot[0] = (int)rec;
        slot[1] = 1;
        int v = ((int (__thiscall*)(void*))VT(rec)[0x18 / 4])(rec);
        *(int*)(buf + 4) = v;
        return *ctr;
    }
    return -1;
}

// @ 0x00686520
__declspec(noinline) unsigned char DecodeRecord(void* rd, uint32_t key, uint32_t size, uint8_t flag)
{
    uint32_t b0, b1, ver, zero, n0, n1;
    if (!ReadInt32_s0068_60e0(rd, &ver, 1, 0))
        goto done;
    if (!ReadInt32_s0068_60e0(rd, &zero, 1, 0))
        goto done;
    if (zero != 0)
        goto done;
    flag = 0;
    {
        ReadByte2(rd, &b0, 1, 0);
        ReadByte2(rd, &b1, 1, 0);
        ReadInt32_s0068_60e0(rd, &n0, 1, 0);
        ReadInt32_s0068_60e0(rd, &n1, 1, 0);
        uint32_t sz = n0 * n1;
        if (sz != size)
            goto done;
        VecBuf data;
        data.Init(sz, &flag);
        if (((int (__thiscall*)(void*, void*, int))VT(rd)[0x30 / 4])(rd, data.b, (int)sz) == (int)sz) {
            int m = -((int (__thiscall*)(void*, int))VT(rd)[0x24 / 4])(rd, 2);
            {
                VecBuf sig;
                sig.Init((uint32_t)m, &flag);
                ((int (__thiscall*)(void*, void*, int))VT(rd)[0x30 / 4])(rd, sig.b, m);
                unsigned char digest[20];
                SHA1(sig.b, m, digest);
                RSAKey* rsa = (RSAKey*)FUN_01179f50();
                rsa->n = FUN_0117ac80((const void*)key, (int)size, 0);
                BN_dec2bn(&rsa->e, "65537");
                if (FUN_0117a150(0x40, digest, 0x14, data.b, sz, rsa) != 0)
                    flag = 1;
            }
        }
    }
done:
    ((void (__thiscall*)(void*, int, int))VT(rd)[0x28 / 4])(rd, 0, 0);
    return flag;
}

// @ 0x006866f0
static inline void* RecStream(void* r)
{ return ((void* (__thiscall*)(void*))VT(r)[0x18 / 4])(r); }

// @ 0x00686d90
bool OpenPackageRecord(const ResKey* key, void* src, DPFile** pOut, int dflt, bool process)
{
    RecPtr rec;
    if (SrcOpen(src, (void*)key, &rec.p)) {
    DPFile* dpf = new ("App/DatabasePackedFile", 0, 0, 0, 0) DPFile(0, 0);
    if (dpf)
        dpf->sub.AddRef();
    RefGuard guard(dpf);
    *pOut = dpf;
    bool result = ((bool (__thiscall*)(void*))VT(dpf)[1])(dpf);
    WPath path(((const wchar_t* (__thiscall*)(void*))VT(src)[0x28 / 4])(src));
    WEmpty name;
    SPNameFromKeyW(key, &name, 0);
    path += kSlash;
    path.Append(name.mpBegin, name.mpEnd);
    ((void (__thiscall*)(void*, const wchar_t*))VT(dpf)[0x2c / 4])(dpf, path.mpBegin);
    ((void (__thiscall*)(void*, void*))VT(dpf)[0x50 / 4])(dpf, RecStream(rec.p));
    if (((bool (__thiscall*)(void*, int, int, int))VT(dpf)[0x18 / 4])(dpf, 1, 3, 0)) {
        if (process)
            ReadPropRecords(dpf, dflt);
    } else {
        result = false;
        ((void (__thiscall*)(void*))VT(dpf)[2])(dpf);
    }
    return result;
    }
    return false;
}

// @ 0x006870a0
void Vec28::ResizeLoop(Elem28* position, uint32_t n, const Elem28& value)
{
    {
        if ((uint32_t)(c - e) >= n) {
          if (n != 0) {
            const Elem28 temp(value);
            const uint32_t nElementsAfter = (uint32_t)(e - position);
            Elem28* pOldEnd = e;
            if (nElementsAfter > n) {
                UninitCopy28(e - n, e, e);
                e += n;
                CopyBack28(position, pOldEnd - n, pOldEnd);
                Fill28(position, position + n, temp);
            } else {
                UninitFillN28(e, n - nElementsAfter, temp);
                e += n - nElementsAfter;
                UninitCopy28(position, pOldEnd, e);
                e += nElementsAfter;
                Fill28(position, pOldEnd, temp);
            }
          }
        } else {
            const uint32_t nPrevSize = (uint32_t)(e - b);
            const uint32_t nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
            const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
            Elem28* pNewData = nNewSize ? (Elem28*)EASTL_alloc6(nNewSize * sizeof(Elem28), g_allocTag, 0, 0, g_fileEASTL, 0xd1) : 0;
            Elem28* pNewEnd = UninitReloc28(b, position, pNewData);
            DestroyRange28(b, position, pNewData);
            UninitFillN28(pNewEnd, n, value);
            pNewEnd += n;
            pNewEnd = UninitReloc28(position, e, pNewEnd);
            DestroyRange28(position, e, pNewEnd);
            if (b && ((int*)b)[-1] != 0)
                EASTL_dealloc(b);
            b = pNewData;
            e = pNewEnd;
            c = pNewData + nNewSize;
        }
    }
}

// @ 0x006872f0
extern "C" int RegisterPackagesDef(void* mgr, const wchar_t* base, PkgFilter cb, void* ctx, int flag)
{
    (void)mgr;
    DirDeque dq;
    DirectoryIterator di = { 0, 0, 0, 0 };
    WideFixedBuf path;

    di.Read(base, &dq, L"*.package", 2, 0x100000, 0);

    void* cur = dq.mItBegin.mpCurrent;
    void* blkEnd = dq.mItBegin.mpEnd;
    void** blk = (void**)dq.mItBegin.mpCurrentArrayPtr;
    void* endCur = dq.mItEnd.mpCurrent;

    while (cur != endCur) {
        path.assign(base);
        wchar_t* nm = ((DirEntry*)cur)->name;
        const wchar_t* nmEnd = nm;
        while (*nmEnd) ++nmEnd;
        path.append(nm, nmEnd);

        if (cb == 0 || cb(path.mBegin, ctx)) {
            DatabasePackedFile* pkg =
                (DatabasePackedFile*)ZoneObject_new(0x388, "App/DatabasePackedFile", 0, 0, 0, 0);
            if (pkg) pkg->Construct(0, 0);
            if (pkg) pkg->AddRef();
            pkg->v1();
            pkg->v11(path.mBegin);
            if (pkg->v6(1, 6, 0))
                ReadPropRecords(pkg, flag);
            else
                pkg->v2();
            pkg->Release();
        }

        cur = (char*)cur + 0x30;
        if (cur == blkEnd) {
            ++blk;
            blkEnd = (char*)*blk + 0xc0;
            cur = *blk;
        }
    }
    return 1;
}

// @ 0x00687590
extern "C" void Thunk_687590(void* a, void* b, int c)
{
    RegisterPackages(a, b, 0, 0, c);
}

// @ 0x006875b0
extern "C" void IteratePackages(void* param)
{
    int i = 0;
    if (g_count >= 0) {
        do {
            char* e = g_array + i * 0x28;
            if (e[0] != 0 && *(int*)(e + 8) != *(int*)(e + 0xc)) {
                int flag;
                switch (i) {
                case 1: flag = 1; break;
                case 2: flag = 100; break;
                default: flag = 0; break;
                }
                RegisterPackages(param, *(void**)(e + 8), 0, 0, flag);
            }
            ++i;
        } while (i <= g_count);
    }
}

// @ 0x00687610
extern "C" int SetupResources(const wchar_t* base, void* p2, void* p3, char flag)
{
    (void)p2; (void)p3;
    void* mgr = GetManager_s0068_70a0();
    VecWStrT vec0;
    VecWStrT vec1;

    {
        WStrT t;
        t.RangeInitialize(L"Locale");
        vec1.push_back(&t);
    }
    {
        WStrT t;
        t.RangeInitialize(L"Preload.package");
        vec0.push_back(&t);
    }

    PkgCtx ctx;
    ctx.base = base;
    ctx.names = &vec0;
    int n = flag ? 0x66 : 2;
    int loadLevel = flag ? 0x65 : 1;
    RegisterPackages(mgr, base, &FUN_00685710, &ctx, flag ? 100 : 0);

    {
        WStrT t;
        t.RangeInitialize(base);
        t.Append(L"Preload.package", L"Preload.package" + 15);
        FUN_00685770(mgr, t.mBegin, loadLevel);
    }

    g_propList->GetDescription(0xce1c9372);
    const wchar_t* dir = GetDirFromID(0xa0214f);
    n += 100;

    if (Directory_Exists(dir)) {
        DatabaseDirectoryFiles* ddf =
            (DatabaseDirectoryFiles*)ZoneObject_new(0x168, "App", 0, 0, 0, 0);
        if (ddf) ddf->Construct(dir, 0);
        if (ddf) ddf->AddRef();
        ddf->v1();
        if (ddf->v6(1, 6, 0)) {
            void** mvt = *(void***)mgr;
            ((MgrSlot90)mvt[0x90 / 4])(mgr, 0xb1b104, L"prop");
            ((MgrSlot50)mvt[0x50 / 4])(mgr, 1, ddf, n);
            ddf->Release();
            return 1;
        }
        ddf->v2();
        ddf->Release();
        return 0;
    }
    return 1;
}
