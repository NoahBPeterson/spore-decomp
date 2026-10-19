// Slice s006870a0: SP package/resource registration helpers (0x006870a0..0x00687bc0).
// Module compiled /O2 /MD /Gy /EHsc /TP (no SSE).
#include "types.h"

static inline void** VT(void* p) { return *(void***)p; }

extern "C" void* MemcpyT(void*, const void*, uint32_t);           // 0x011e0744
extern "C" void  EASTL_dealloc(void*);                            // 0x0f47380
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t); // 0x0f473a0
extern "C" char  g_allocTag[];   // 0x013ebc58 "App"
extern "C" char  g_fileEASTL[];  // 0x013ebb38
typedef char (__cdecl *PkgFilter)(const wchar_t*, void*);
extern "C" int  __cdecl RegisterPackages(void*, const void*, PkgFilter, void*, int); // 0x06872f0
extern "C" char __cdecl FUN_00685710(const wchar_t*, void*);       // 0x0685710
extern "C" void __cdecl AppendWide(void*, const wchar_t*, const wchar_t*); // 0x042f9d0

// globals used by these helpers
extern "C" int  g_count;                    // 0x0152b348
extern "C" char* g_array;                   // 0x015fea00
extern "C" char* g_arrayEnd;                // 0x015fea04

// =====================================================================
// 0x006870a0  vector<Elem28>::DoInsertValues(position, n, value)
// Elem28 = {u8 flag, u32, two 16-byte wide strings}, 0x28 bytes.
// =====================================================================
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

// @ 0x006870a0
void Vec28::ResizeLoop(Elem28* position, uint32_t n, const Elem28& value) {
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

// =====================================================================
// anonymous_namespace::RegisterPackages -- directory scan / package dispatch
// =====================================================================
// Scans a directory for "*.package" files.  EA::IO::DirectoryIterator::Read
// fills an eastl::deque of directory entries; for every entry whose name the
// filter callback accepts a DatabasePackedFile is constructed, registered and
// its property records are read.
extern "C" void* GetDefaultAllocatorX();                           // 0x00925cb0
extern "C" void* ZoneObject_new(int, const char*, int, int, int, int); // 0x00926020
extern "C" void  ReadPropRecords(void*, int);                      // 0x006866f0

// The directory scan destination: an eastl::deque<DirectoryEntry> (DequeBase layout).
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

// eastl::wstring with an inline 256-wchar fixed buffer (the "WideFixedBuf" used
// by the package-path builder).
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

// Directory scan entry: a name string (begin/end/cap at +4/+8/+0xc) inside a 0x30 stride.
struct DirEntry {
    uint32_t f0;            // +0x00
    wchar_t* name;          // +0x04
    uint32_t f8, fc, f10, f14, f18, f1c, f20, f24, f28, f2c;
};

// A reference-counted package object with a primary and a secondary (IRefCounted) vtable.
struct IRefCounted { virtual void AddRef(); virtual void Release(); };
struct DPFBase {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual bool v6(int, int, int);
    virtual void v7();  virtual void v8();  virtual void v9();  virtual void v10();
    virtual void v11(const wchar_t*);
};
struct DatabasePackedFile : DPFBase, IRefCounted {
    void Construct(const wchar_t* name, void* alloc);            // 0x008d9f80
};

// @ 0x006872f0
extern "C" int RegisterPackagesDef(void* mgr, const wchar_t* base, PkgFilter cb,
                                   void* ctx, int flag) {
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

// =====================================================================
// @ 0x00687590  thin thunk: RegisterPackages(a,b,0,0,c)
// =====================================================================
extern "C" void Thunk_687590(void* a, void* b, int c) {
    RegisterPackages(a, b, 0, 0, c);
}

// =====================================================================
// @ 0x006875b0  iterate array, register each populated entry
// =====================================================================
extern "C" void IteratePackages(void* param) {
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

// =====================================================================
// SP::SetupResources -- register the package files under a directory
// =====================================================================
// Registers the "*.package" files below the given directory (excluding the
// names collected in vec0), then adds the "Preload.package" database and
// (when present) the ResourceMan database directory.
extern "C" void* GetManager();                                     // 0x0067dcd0
extern "C" void  FUN_00685770(void*, const wchar_t*, int);         // 0x00685770
extern "C" const wchar_t* GetDirFromID(uint32_t);                  // 0x006886b0
extern "C" bool  Directory_Exists(const wchar_t*);                 // 0x009322b0

struct cDirectPropertyList {
    bool GetDescription(uint32_t) const;                           // 0x006a25a0
};
extern "C" cDirectPropertyList* g_propList;                        // 0x015fd918

// eastl::basic_string<wchar_t, eastl::allocator>.
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

// eastl::vector<WStrT, sp_vector_allocator> with 8 inline elements.
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

// DatabaseDirectoryFiles shares the ref-counted package vtable layout.
struct DDFBase {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual bool v6(int, int, int);
    virtual void v7();  virtual void v8();  virtual void v9();  virtual void v10();
    virtual void v11(const wchar_t*);
};
struct DatabaseDirectoryFiles : DDFBase, IRefCounted {
    void Construct(const wchar_t* dir, void* alloc);               // 0x008d7400
};

// The manager is a large interface; only the slots at +0x50 and +0x90 are used.
typedef void (__thiscall *MgrSlot50)(void*, int, void*, int);
typedef void (__thiscall *MgrSlot90)(void*, int, const wchar_t*);

// @ 0x00687610
extern "C" int SetupResources(const wchar_t* base, void* p2, void* p3, char flag) {
    (void)p2; (void)p3;
    void* mgr = GetManager();
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

// =====================================================================
// @ 0x00687a00  append range to global vector
// =====================================================================
struct VecU32G { uint32_t* b; uint32_t* e; uint32_t* c;
    void InsertRange(uint32_t* first, uint32_t* last, uint32_t* dst); // 0x06ad970
};
extern "C" void Thunk_687a00(int n, uint32_t* base) {
    ((VecU32G*)0x0152b5a0)->InsertRange(base, base + n, base);
}

// =====================================================================
// @ 0x00687a20  iterate array, push strings/ids into two vectors
// =====================================================================
struct VecWStr { void* b; void* e; void* c;
    void push_back(const void* p);          // 0x0553f10
};
struct VecU32 { uint32_t* b; uint32_t* e; uint32_t* c;
    void DoIns(uint32_t* pos, const uint32_t* val); // 0x04558a0
};
extern "C" void Iterate2(VecWStr* v0, VecU32* v1) {
    if (g_count >= 0) {
        for (int i = 0; i <= g_count; ++i) {
            char* e = g_array + i * 0x28;
            if (e[0] != 0 && *(int*)(e + 4) != 0 &&
                *(int*)(e + 0x18) != *(int*)(e + 0x1c)) {
                v0->push_back(e + 0x18);
                uint32_t val = *(uint32_t*)(e + 4);
                uint32_t* p = v1->e;
                if (p < v1->c) {
                    v1->e = p + 1;
                    if (p) *p = val;
                } else {
                    v1->DoIns(p, &val);
                }
            }
        }
    }
}

// =====================================================================
// @ 0x00687ab0  reserve n 0x28-stride elements
// =====================================================================
// The reserve path default-constructs a scratch Elem28 (two empty eastl
// wstrings with the shared empty-buffer sentinel 0x1667bac / 0x1667bae) and
// destroys it on both normal and exceptional exit, hence the EH frame.
extern "C" wchar_t g_emptyW[];   // 0x01667bac (shared 1-wchar empty buffer)
struct WStrRes {
    wchar_t* mBegin;
    wchar_t* mEnd;
    wchar_t* mCap;
    uint32_t mAlloc;
    WStrRes() { mBegin = g_emptyW; mEnd = g_emptyW; mCap = g_emptyW + 1; }
    ~WStrRes() {
        if ((int)(((unsigned)mCap - (unsigned)mBegin) & ~1u) > 2 && mBegin)
            EASTL_dealloc(mBegin);
    }
};
struct ElemRes {
    uint8_t flag;
    uint8_t pad[3];
    uint32_t f4;
    WStrRes a;
    WStrRes b;
    ElemRes() : flag(0), f4(0) {}
};
void Vec28::Reserve(uint32_t n) {
    if (n > (uint32_t)((int)((char*)e - (char*)b) / 0x28)) {
        ElemRes tmp;
        ResizeLoop(e, n - (uint32_t)((int)((char*)e - (char*)b) / 0x28), *(Elem28*)&tmp);
    } else {
        DestroyRangeChunk((char*)b + n * 0x28, (char*)e);
    }
}

// =====================================================================
// @ 0x00687bc0  set element count cap; returns index or -1
// =====================================================================
extern "C" int SetCount(int n) {
    if (n > g_count) {
        ((Vec28*)&g_array)->Reserve((uint32_t)(n + 1));
        g_count = n;
    }
    if (n == 2) return -1;
    int r = -1;
    int count = (int)(g_arrayEnd - g_array) / 0x28;
    if (n < count) r = n;
    return r;
}
