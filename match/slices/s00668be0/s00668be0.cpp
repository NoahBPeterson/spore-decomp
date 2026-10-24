// Slice s00668be0: SP::cSPUIFeedListItem - GetHeaderMessage, feed iteration helpers and
// the asset-list queries (GetAssetList/QueryNumItems wrappers).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void  (__thiscall *FnVoidII)(void*, int, int);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

int __cdecl WStr_Format(wchar_t* dst, const wchar_t* fmt, ...);   // 0x0041e050
void __cdecl EASTL_allocator_deallocate(void* p);                 // 0x00f47380
void* __cdecl FUN_0067de90(void* a);                              // 0x0067de90
void* __cdecl FUN_007eb100(void* a);                              // 0x007eb100
void* __cdecl EA_GetManager();                                    // 0x0067dcd0
void* __cdecl FUN_004aa350(void* self, int count, void* p);       // 0x004aa350
void* __cdecl DoInsertValue0066(void* dst, void* src, int nbytes); // 0x011e0744
void  __cdecl FUN_00642c70(void* self, int n);                    // 0x00642c70
void  __cdecl FUN_006431b0(void* self, void* item, void* end);    // 0x006431b0

extern wchar_t gFmt13f5c04[];   // 0x013f5c04
extern int gVt14002a8;          // 0x014002a8

struct Vec { void* begin; void* end; void* cap; };

// --- helpers used by GetAssetList (0x00668d90) -------------------------------
// SP::FunctionalMatch::Constraint - a 0x24-byte node: {tag, kind, lo, hi,
// vector<Constraint> children, ...}; the vector is at +0x10 (the destructor
// walks it and every child is itself 0x24 bytes).
struct Constraint {
    uint32_t tag;         // +0x00
    uint32_t kind;        // +0x04  (0x2e1a9d3 "set" / 0x2e1a75d "equal|range")
    int32_t  lo;          // +0x08
    int32_t  hi;          // +0x0c
    void*    cb;          // +0x10
    void*    ce;          // +0x14
    void*    cc;          // +0x18
    uint32_t w1c;         // +0x1c
    uint32_t w20;         // +0x20
    Constraint& InitSet(int type);                                   // 0x00558830
    Constraint& InitEqual(uint32_t tagv, int ec, int value);         // 0x00558960
    Constraint& InitRange(uint32_t tagv, int rc, int lov, int hiv);  // 0x005589c0
    void Destroy();                                                  // 0x006066f0
};

struct DateTime {
    int64_t mValue;
    void Set(int mode);          // 0x0092e3d0
};

// The two vector helpers below are __thiscall in the original (the vector is
// passed in ecx); the __cdecl prototypes further up belong to the neighbouring
// FUN_00668c80, so these same-address twins keep both call sites faithful.
// They are declared on a dummy holder because cl rejects __thiscall on free
// functions (C3865), and are only declared, never defined.
struct VecOps {
    void Reserve(int n);                       // 0x00642c70
    void PushItem(void* pos, void* item);      // 0x006431b0
};
void* __cdecl ObjectTemplateDBPtr(void);                              // 0x0067cb40
extern "C" uint64_t __cdecl FUN_011e0970(uint64_t a, uint64_t b);     // 0x011e0970 _aulldiv
extern int gVt13eb394;                                                // 0x013eb394

struct QueryObj {             // SP resource-query object handed to the manager
    void* vt;                 // +0x00
    void* vb;                 // +0x04
    void* ve;                 // +0x08
    void* vc;                 // +0x0c
    char  pad10[8];           // +0x10 (left uninitialised by the original)
    void* m18;                // +0x18
    char  pad1c[0x14];        // +0x1c spare
};

// Declared-only twin of FUN_00668d90, annotated with the original address. The original
// QueryNumItems was compiled in a different TU than GetAssetList, so cl could not reuse a
// zero register across the call and zeroes the vector / tests the guard with immediates
// (never touching edx). A same-TU call lets cl keep edx==0 across the call; calling the
// declared-only twin restores the original codegen. The definition of FUN_00668d90 below
// is unchanged.
struct AssetListSource { void GetAssetList(Vec* out); };  // 0x00668d90

struct FeedItem {
    bool FUN_00668be0(wchar_t* dst);
    void FUN_00668c80(void* a1, void* c);
    void FUN_00668d90(Vec* out);
    int  FUN_006693c0();
    void FUN_00669410();
};

// -----------------------------------------------------------------------------
// @ 0x00668be0  SP::cSPUIFeedListItem::GetHeaderMessage
// -----------------------------------------------------------------------------
bool FeedItem::FUN_00668be0(wchar_t* dst) {
    const wchar_t* name = *(wchar_t**)((char*)this + 0x18);
    if (name) {
        const wchar_t* author = *(wchar_t**)((char*)this + 0x28);
        if (author) {
            switch (*(int*)((char*)this + 0x13c)) {
            case 1:
                WStr_Format(dst, L"Sporecast \"%s\" by %s", name, author);
                return true;
            case 2:
                WStr_Format(dst, L"Creations by %s", author);
                return true;
            case 3:
                WStr_Format(dst, L"Content tagged \"%s\"", name);
                return true;
            default:
                WStr_Format(dst, gFmt13f5c04, name);
                return true;
            }
        }
    }
    return false;
}

// -----------------------------------------------------------------------------
// @ 0x00668c80  iterate the resource list and append entries to a vector
// -----------------------------------------------------------------------------
struct Item { int a; int b; int c; void* d; };

void FeedItem::FUN_00668c80(void* a1, void* c) {
    (void)a1;
    void* list = FUN_007eb100(c);
    if (!list) return;
    int count = 0;
    void** node = (void**)*(void**)list;
    void** head = (void**)list;
    while (node != head) { ++count; node = (void**)*node; }
    FUN_00642c70(this, count);

    int idx = 1;
    node = (void**)*head;
    while (node != head) {
        void* e = node[5];
        int loc1c = *(int*)((char*)e + 8);
        int loc14 = *(int*)((char*)e + 0xc);
        int loc18 = *(int*)((char*)e + 4);
        void** puVar7 = node + 2;
        int next = idx;
        if (loc1c == 0) {
        use:
            {
                int m28 = *(int*)((char*)(node[5]) + 0x28);
                Item tmp;
                tmp.a = idx;
                tmp.b = m28;
                tmp.c = 0;
                tmp.d = puVar7;
                void* end = *(void**)((char*)this + 4);
                next = idx + 1;
                if (end < *(void**)((char*)this + 8)) {
                    *(void**)((char*)this + 4) = (char*)end + 0x10;
                    if (end) {
                        *(int*)((char*)end + 0) = idx;
                        *(int*)((char*)end + 4) = m28;
                        *(int*)((char*)end + 8) = 0;
                        *(void**)((char*)end + 0xc) = puVar7;
                    }
                } else {
                    FUN_006431b0(this, &tmp, end);
                }
            }
        } else {
            void* mgr = EA_GetManager();
            char ok = ((char(__thiscall*)(void*, void*, int, int, int, int, int))VT(mgr)[3])
                          (mgr, &loc1c, 0, 0, 0, 0, 0);
            next = idx;
            if (ok) goto use;
        }
        idx = next;
        node = (void**)*node;
    }
}

// -----------------------------------------------------------------------------
// @ 0x00668d90  FeedItem::FUN_00668d90  (SP::cSPUIFeedListItem::GetAssetList)
// Walks the managed-asset database for the feed's type id, collecting 16-byte
// {a, b, c, d} entries into `out`.  Three feed kinds, selected by this+0x178.
// -----------------------------------------------------------------------------
__declspec(noinline) void FeedItem::FUN_00668d90(Vec* out) {
    int tag178 = *(int*)((char*)this + 0x178);

    if (tag178 == 0xe8104769) {
        // ---- feed kind 3: reuse the cached list, one entry per bucket --------
        switch (*(int*)((char*)this + 0x144)) {
        case 0x9407af6f:
            FUN_00668c80(out, (void*)8);
            break;
        case 0x845bd9f4:
            ((FeedItem*)out)->FUN_00668c80(out, (void*)7);
            break;
        case 0x88e3177e:
            FUN_00668c80(out, (void*)0xb);
            break;
        case 0xf4d527ca:
            ((FeedItem*)out)->FUN_00668c80(out, (void*)0xa);
            break;
        case 0xfd39c05c:
            FUN_00668c80(out, (void*)9);
            break;
        default:
            break;
        }
        return;
    }

    if (tag178 == 0x11f44f6b) {
        // ---- feed kind 2: constraint query against the template database ----
        Vec local;
        local.begin = 0;
        local.end = 0;
        local.cap = 0;

        switch (*(int*)((char*)this + 0x138)) {
        case 0xc0640133: {
            void** db = (void**)ObjectTemplateDBPtr();
            Constraint c1; c1.InitSet(0);
            Constraint c2; c2.InitRange(0x2dc9d1e, 0, (int)0x80000000, 0x7fffffff);
            ((void(__cdecl*)(void*, Vec*, Constraint, Constraint))VT(db)[0x34 / 4])
                (db, &local, c2, c1);
            c2.Destroy();
            c1.Destroy();
            break;
        }
        case 0xbadc8636: {
            DateTime dt;
            dt.Set(1);
            uint64_t t = (uint64_t)dt.mValue + 0xfffffff140f326f0ULL;
            int n = (int)(uint32_t)FUN_011e0970(t, 3600);

            void** db = (void**)ObjectTemplateDBPtr();
            Constraint c1; c1.InitSet(0);
            Constraint c2; c2.InitEqual(0x5fb4759, 0, 0);
            Constraint c3; c3.InitRange(0x61ef9b1, 0, n - 0x30, n + 1);
            ((void(__cdecl*)(void*, Vec*, Constraint, Constraint, Constraint))VT(db)[0x34 / 4])
                (db, &local, c3, c2, c1);
            c3.Destroy();
            c2.Destroy();
            c1.Destroy();
            break;
        }
        case 0xb0449ead: {
            void** db = (void**)ObjectTemplateDBPtr();
            Constraint c1; c1.InitSet(0);
            Constraint c2; c2.InitEqual(0x3cc89b1, 0, *(int*)((char*)this + 0x134));
            ((void(__cdecl*)(void*, Vec*, Constraint, Constraint))VT(db)[0x34 / 4])
                (db, &local, c2, c1);
            c2.Destroy();
            c1.Destroy();
            break;
        }
        case 0xc84ea7b6: {
            void** db = (void**)ObjectTemplateDBPtr();
            Constraint c1; c1.InitSet(0);
            Constraint c2; c2.InitEqual(0x5fb4759, 0, 1);
            ((void(__cdecl*)(void*, Vec*, Constraint, Constraint))VT(db)[0x34 / 4])
                (db, &local, c2, c1);
            c2.Destroy();
            c1.Destroy();
            break;
        }
        case 0xe04bb957: {
            void** db = (void**)ObjectTemplateDBPtr();
            Constraint c1; c1.InitSet(0);
            Constraint c2; c2.InitEqual(0x3cc89b1, 0, (int)0x913b23be);
            ((void(__cdecl*)(void*, Vec*, Constraint, Constraint))VT(db)[0x34 / 4])
                (db, &local, c2, c1);
            c2.Destroy();
            c1.Destroy();
            break;
        }
        case 0x7f6198d6: {
            void** db = (void**)ObjectTemplateDBPtr();
            Constraint c1; c1.InitSet(0);
            Constraint c2; c2.InitEqual(0x3cc89b1, 0, (int)0xa86067e7);
            ((void(__cdecl*)(void*, Vec*, Constraint, Constraint))VT(db)[0x34 / 4])
                (db, &local, c2, c1);
            c2.Destroy();
            c1.Destroy();
            break;
        }
        default:
            break;
        }

        // ---- shared tail: transfer the 12-byte query hits into `out` --------
        int n = (int)((char*)local.end - (char*)local.begin) / 12;
        ((VecOps*)out)->Reserve(n);

        void* p = local.begin;
        void* stop = local.end;
        while (p != stop) {
            Item tmp;
            tmp.a = *(int*)((char*)p + 0x0);
            tmp.b = *(int*)((char*)p + 0x4);
            tmp.c = *(int*)((char*)p + 0x8);
            tmp.d = 0;
            void* end = *(void**)((char*)out + 4);
            if (end < *(void**)((char*)out + 8)) {
                *(void**)((char*)out + 4) = (char*)end + 0x10;
                if (end) {
                    *(int*)((char*)end + 0x0) = tmp.a;
                    *(int*)((char*)end + 0x4) = tmp.b;
                    *(int*)((char*)end + 0x8) = tmp.c;
                    *(void**)((char*)end + 0xc) = tmp.d;
                }
            } else {
                ((VecOps*)out)->PushItem(end, &tmp);
            }
            p = (char*)p + 12;
        }

        if (local.begin != 0 && *(int*)((char*)local.begin - 4) != 0)
            EASTL_allocator_deallocate(local.begin);
        return;
    }

    if (tag178 != 0x48a6f111)
        return;

    // ---- feed kind 1: manager query -------------------------------------------------
    Vec local;
    local.begin = 0;
    local.end = 0;
    local.cap = 0;

    QueryObj q;
    q.vt = &gVt14002a8;
    q.vb = 0;
    q.ve = 0;
    q.vc = 0;
    q.m18 = *(void**)((char*)this + 0x148);

    void* mgr = EA_GetManager();
    ((void(__thiscall*)(void*, Vec*, QueryObj*, int))VT(mgr)[0x38 / 4])(mgr, &local, &q, 0);

    int n = (int)((char*)local.end - (char*)local.begin) / 12;
    ((VecOps*)out)->Reserve(n);

    void* p = local.begin;
    void* stop = local.end;
    while (p != stop) {
        Item tmp;
        tmp.a = *(int*)((char*)p + 0x0);
        tmp.b = *(int*)((char*)p + 0x4);
        tmp.c = *(int*)((char*)p + 0x8);
        tmp.d = 0;
        void* end = *(void**)((char*)out + 4);
        if (end < *(void**)((char*)out + 8)) {
            *(void**)((char*)out + 4) = (char*)end + 0x10;
            if (end) {
                *(int*)((char*)end + 0x0) = tmp.a;
                *(int*)((char*)end + 0x4) = tmp.b;
                *(int*)((char*)end + 0x8) = tmp.c;
                *(void**)((char*)end + 0xc) = tmp.d;
            }
        } else {
            ((VecOps*)out)->PushItem(end, &tmp);
        }
        p = (char*)p + 12;
    }

    // inlined destructors of `q` then `local` (reverse declaration order)
    if (q.vb != 0 && *(int*)((char*)q.vb - 4) != 0)
        EASTL_allocator_deallocate(q.vb);
    q.vt = &gVt13eb394;
    if (local.begin != 0 && *(int*)((char*)local.begin - 4) != 0)
        EASTL_allocator_deallocate(local.begin);
}

// -----------------------------------------------------------------------------
// @ 0x00669360  vector-copy constructor helper
// -----------------------------------------------------------------------------
struct Vec4 { void* begin; void* end; void* cap; void reserve(int count, void* p); };

struct Obj9360 {
    void* vt;        // +0x00
    Vec4  v;         // +0x04
    char  pad10[8];  // +0x10
    void* m18;       // +0x18
    Obj9360* init(int p2, Vec* p3);
};

Obj9360* Obj9360::init(int p2, Vec* p3) {
    vt = &gVt14002a8;
    int count = (int)((char*)p3->end - (char*)p3->begin) >> 2;
    v.reserve(count, (char*)p3 + 0xc);
    int nbytes = (int)((char*)p3->end - (char*)p3->begin);
    void* r = DoInsertValue0066(v.begin, p3->begin, nbytes);
    v.end = (char*)r + (nbytes >> 2) * 4;
    m18 = (void*)p2;
    return this;
}

// -----------------------------------------------------------------------------
// @ 0x006693c0  count assets returned by GetAssetList
// -----------------------------------------------------------------------------
__declspec(noinline) int FeedItem::FUN_006693c0() {
    Vec v;
    v.begin = 0;
    v.end = 0;
    v.cap = 0;
    ((AssetListSource*)this)->GetAssetList(&v);
    int n = (int)((char*)v.end - (char*)v.begin);
    if (v.begin && *(int*)((char*)v.begin - 4) != 0)
        EASTL_allocator_deallocate(v.begin);
    return n >> 4;
}

// -----------------------------------------------------------------------------
// @ 0x00669410  refresh the cached item count
// -----------------------------------------------------------------------------
void __fastcall FUN_00669410(void* self) {
    int n = ((FeedItem*)self)->FUN_006693c0();
    *(int*)((char*)self + 0x60) = n;
    if (n != *(int*)((char*)self + 0x64))
        *(uint8_t*)((char*)self + 0x86) = 1;
}
