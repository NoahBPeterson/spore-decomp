// Slice s00664c90: SP::cSPUIFeedListCategory, its item list and helpers.
// UI module: /O2 /MD /Gy /TP /arch:SSE2 (no /EHsc).
#include "types.h"

typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPi)(void*, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void*(__thiscall* FnRetP)(void*);
typedef int(__thiscall* FnRetI)(void*);
typedef bool(__thiscall* FnGetProp)(void*, int, int, void**);
typedef bool(__thiscall* FnGetSubProp)(void*, int, void**);
typedef unsigned __int64(__thiscall* FnGetU64)(void*);

static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }

extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* CopyImpl(void* first, void* last, void* dest); // 0x006782c0 eastl CopyImpl::do_copy
extern "C" void  FUN_00646d70(void* first, void* last);
extern "C" void  EA_Messaging_RemoveHandler(void* a, void* b, void* c, void* d, void* e);
extern "C" void* SP_PropertyManager();  // 0x0067de30
extern "C" void* FUN_0067cb30();        // 0x0067cb30
extern "C" void* FUN_00607a60();        // 0x00607a60 SP::Pollen::AuthManager
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
extern "C" void __stdcall FUN_00601b40(void* pos, void* val);
extern "C" void  FUN_00b2af00(int* a, int* b);
extern "C" void  FUN_00ac97a0(void* a, void* b, void* c);
extern "C" void  FUN_006657f0(void* first, void* last, void* feed);  // 0x006657f0
extern "C" void  FUN_009512c0();
extern "C" void* FUN_009512d0(int a, int b, const char* name, int c);

extern int gVtA, gVtB, gVtC, gVtD, gVtE, gVtF, gVtG, gVtH;
extern "C" void* FUN_00660b30(void*, void*, void*);

// ---------------------------------------------------------------------------
struct Vec8 {
    void* begin; void* end; void* cap;
    void push_back(void* val);
};
struct VecAutoRef4 {
    void* begin; void* end; void* cap;
    void erase(void* first, void* last);
    void FUN_006650c0(void* pos, void* value);
};

// ---------------------------------------------------------------------------
// SP::cSPUIFeedListItem, refcounted handle and the feed comparator.
struct FeedItem {
    virtual int  AddRef();             // +0x00
    virtual int  Release();            // +0x04
    char     pad08[8];
    void*    m0c;                      // +0x0c
    int      m10;                      // +0x10
    bool     m14;                      // +0x14
    char     m15;                      // +0x15  visited marker used by RefreshAll
    char     pad16[2];
    wchar_t* mName;                    // +0x18
    char     pad1c[0xc0 - 0x1c];
    char     mC0;                      // +0xc0
    char     padc1[3];
    int      mGroup;                   // +0xc4
    char     padc8[0x134 - 0xc8];
    int      m134;                     // +0x134
};

struct AutoRefCountT {
    FeedItem* mpObject;
    AutoRefCountT() : mpObject(0) {}
    AutoRefCountT(const AutoRefCountT& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCountT() { if (mpObject) mpObject->Release(); }
    AutoRefCountT& operator=(const AutoRefCountT& o) {
        FeedItem* old = mpObject;
        if (o.mpObject != old) {
            if (o.mpObject) o.mpObject->AddRef();
            mpObject = o.mpObject;
            if (old) old->Release();
        }
        return *this;
    }
    AutoRefCountT& operator=(FeedItem* o) {
        FeedItem* old = mpObject;
        if (o != old) {
            if (o) o->AddRef();
            mpObject = o;
            if (old) old->Release();
        }
        return *this;
    }
    FeedItem* operator->() const { return mpObject; }
    operator FeedItem*() const { return mpObject; }
};

struct AlphabeticalFeedSort {
    bool operator()(const FeedItem* a, const FeedItem* b) const {
        if (a && b) {
            if (a->mGroup == b->mGroup)
                return a->mName && b->mName && _wcsicmp(a->mName, b->mName) < 0;
            return a->mGroup < b->mGroup;
        }
        return false;
    }
};

// One entry of the Pollen feed-directory arrays (+0xc8/+0xcc and +0xb4/+0xb8, stride 0x70).
struct FeedDirEntry {
    char             pad00[0x10];
    unsigned __int64 mAuth;            // +0x10
    char             pad18[0x68 - 0x18];
    int              mCategory;        // +0x68
    char             pad6c[4];         // -> 0x70
};

// Property objects returned by the property-list manager.
struct FeedProp {
    char           pad00[0x10];
    unsigned short mFlags;             // +0x10
    unsigned short mType;              // +0x12
};

// { property value, feed id } pushed on the category's Vec8 at +0xa0.
struct FeedPair {
    int value;
    int id;
};

// Heap primitives from the sort helper slices (comparator passed by value).
void FUN_00665000(AutoRefCountT* first, AutoRefCountT* last, AlphabeticalFeedSort compare); // 0x00665000 make_heap
void FUN_00664ad0(AutoRefCountT* first, int top, int heapSize, int pos, AutoRefCountT value,
                  AlphabeticalFeedSort compare); // 0x00664ad0 adjust_heap
void FUN_00665050(AutoRefCountT* first, AutoRefCountT* last, AlphabeticalFeedSort compare); // 0x00665050 sort_heap

// ---------------------------------------------------------------------------
// Cross-function helpers (fastcall keeps the original ecx argument; the dummy
// int/second parameter stands in for the non-stack register).
void __fastcall FUN_00669410(void* p);          // 0x00669410
bool __fastcall FUN_00666450(void* p);          // 0x00666450  IsKnownState
void __fastcall FUN_006664f0(void* p);          // 0x006664f0  Teardown
int  __fastcall FUN_005467e0(void* p);          // 0x005467e0
void* __fastcall FUN_006676f0(void* p);         // 0x006676f0  cSPUIFeedListItem ctor
bool __fastcall cSPUIFeedListItem_Init(void* self, int, void* a, void* b, void* c, void* d, void* e); // 0x00669f50
int* __fastcall PropDataPtr(void* prop);        // 0x0041e990  Property::GetInt

extern "C" char  FUN_006a1360(void* obj, int k, void* out);
extern "C" char  FUN_006a0ae0(void* obj, int k, void** ptr, int* count);

static FeedItem* NewFeedItem() {
    FeedItem* item = (FeedItem*)EASTL_allocator_allocate(
        0x190, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (item) item = (FeedItem*)FUN_006676f0(item);
    return item;
}

// Push an AutoRefCount onto the child vector at +0x88 (inline fast path, insert on realloc).
static void PushChild(char* p, FeedItem* item) {
    char* v = p + 0x88;
    char* end = *(char**)(v + 4);
    if (end < *(char**)(v + 8)) {
        *(char**)(v + 4) = end + 4;
        if (end) {
            *(FeedItem**)end = item;
            if (item) item->AddRef();
        }
    } else {
        FeedItem* value = item;
        ((VecAutoRef4*)v)->FUN_006650c0(end, &value);
    }
}

// @ 0x00665330
void Vec8::push_back(void* val) {
    char* e = (char*)end;
    if (e < (char*)cap) {
        end = e + 8;
        if (e) { *(uint32_t*)e = *(uint32_t*)val; *((uint32_t*)e + 1) = ((uint32_t*)val)[1]; }
        return;
    }
    FUN_00601b40(e, val);
}

// ---------------------------------------------------------------------------
struct cSPUIFeedListCategory {
    char  vt[0xc];                     // 0x00
    char  b0c[8];                      // 0x0c..0x13
    char  m14;                         // 0x14
    char  m15;                         // 0x15
    char  pad16[2];
    void* p18; void* p1c; void* p20;   // cString
    char  pad24[0x34];                 // 0x24..0x57
    float f58; float f5c;              // 0x58,0x5c
    void* p60; void* p64; void* p68; void* p6c;
    void* p70; void* p74; void* p78; void* p7c;
    void* p80; void* p84;
    void* childBegin;                  // 0x88
    void* childEnd;                    // 0x8c
    void* childCap;                    // 0x90
    void* p94; void* p98;
    char  m9c;                         // 0x9c
    char  pad9d[3];
    void* pA0; void* pA4; void* pA8;   // vector<pair8>
    void* padAc;                       // 0xac
    char  padB0[4];                    // 0xb0 (padding: pB4 really starts at 0xb4)
    void* pB4;
    void* pB8; void* pBc; void* pC0;
    void* pC4; void* pC8; void* pCc;
    char  mD0;                         // 0xd0
    char  padD1[3];
    void* pD4;

    void* Ctor();
    void  Dtor();
    __declspec(noinline) void  ShutdownChildren();
    __declspec(noinline) void  Populate();
    __declspec(noinline) void* Refresh(int id, int* group);
};

__declspec(dllexport) void keepalive75(cSPUIFeedListCategory* c, Vec8* v, VecAutoRef4* r) {
    c->Ctor();
    c->Dtor();
    c->ShutdownChildren();
    c->Populate();
    c->Refresh(0, 0);
    v->push_back(0);
    r->erase(0, 0);
}

struct CatChild { void FUN_006664f0(); };

// @ 0x00664c90
void* cSPUIFeedListCategory::Ctor() {
    char* p = (char*)this;
    *(void* volatile*)&p[4] = &gVtA;
    *(void* volatile*)&p[8] = &gVtB;
    *(void**)&p[0xc] = &gVtC;
    *(int*)(p + 0x10) = 0;
    *(void**)(p + 0) = &gVtD;
    *(void**)(p + 4) = &gVtE;
    *(void**)(p + 8) = &gVtF;
    *(void**)(p + 0xc) = &gVtG;
    *(char*)(p + 0x14) = 0;
    *(char*)(p + 0x15) = 0;
    *(void**)(p + 0x20) = (void*)0x1667bae;
    *(void**)(p + 0x18) = (void*)0x1667bac;
    *(void**)(p + 0x1c) = (void*)0x1667bac;
    *(float*)(p + 0x58) = 0.0f;
    *(float*)(p + 0x5c) = 0.0f;
    *(void**)(p + 0x60) = 0; *(void**)(p + 0x64) = 0; *(void**)(p + 0x68) = 0;
    *(void**)(p + 0x6c) = 0; *(void**)(p + 0x70) = 0; *(void**)(p + 0x74) = 0;
    *(void**)(p + 0x78) = 0; *(void**)(p + 0x7c) = 0; *(void**)(p + 0x80) = 0;
    *(void**)(p + 0x84) = 0; *(void**)(p + 0x88) = 0; *(void**)(p + 0x8c) = 0;
    *(void**)(p + 0x90) = 0;
    *(char*)(p + 0x9c) = 1;
    *(void**)(p + 0xa0) = 0; *(void**)(p + 0xa4) = 0; *(void**)(p + 0xa8) = 0;
    *(void**)(p + 0xb4) = 0; *(void**)(p + 0xb8) = 0; *(void**)(p + 0xbc) = 0;
    *(void**)(p + 0xc0) = 0; *(void**)(p + 0xc4) = 0; *(void**)(p + 0xc8) = 0;
    *(void**)(p + 0xcc) = 0;
    *(char*)(p + 0xd0) = 0;
    *(void**)(p + 0xd4) = 0;
    return p;
}

// @ 0x00664dc0
void cSPUIFeedListCategory::Dtor() {
    char* p = (char*)this;
    *(void**)(p + 0) = &gVtD;
    *(void**)(p + 4) = &gVtE;
    *(void**)(p + 8) = &gVtF;
    *(void**)(p + 0xc) = &gVtG;
    void* a = *(void**)(p + 0xd4);
    if (a) (*(FnP)Vslot(a, 8))(a);
    void* h = *(void**)(p + 0xbc);
    if (h) { *(void**)(p + 0xbc) = 0; EA_Messaging_RemoveHandler(h, *(void**)(p + 0xc0), *(void**)(p + 0xc4), *(void**)(p + 0xc8), *(void**)(p + 0xcc)); }
    a = *(void**)(p + 0xb8); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0xa0); if (a && *(int*)((char*)a - 4) != 0) EASTL_allocator_deallocate(a);
    { void* v = p + 0x88; (*(void(__thiscall*)(void*))0xae6970)(v); }
    a = *(void**)(p + 0x84); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x80); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x7c); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x78); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x74); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x70); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x6c); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x68); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x64); if (a) (*(FnP)Vslot(a, 8))(a);
    a = *(void**)(p + 0x60); if (a) (*(FnP)Vslot(a, 4))(a);
    { char* b = *(char**)(p + 0x18); int d = *(int*)(p + 0x20) - (int)b; d &= ~1; if (d > 2 && b) EASTL_allocator_deallocate(b); }
    *(void**)(p + 0xc) = &gVtC;
    *(void**)(p + 4) = &gVtH;
    *(void**)(p + 0) = &gVtB;
}

// Swap helper for the partition step (the original calls the out-of-line swap).
__declspec(noinline) void swapT(AutoRefCountT& a, AutoRefCountT& b) {
    AutoRefCountT t(a);
    a = b;
    b = t;
}

// @ 0x00664f30  eastl get_partition<AutoRefCountT*, AlphabeticalFeedSort>
AutoRefCountT* PartitionByFeed(AutoRefCountT* first, AutoRefCountT* last,
                               AutoRefCountT pivotValue, AlphabeticalFeedSort& compare) {
    for (;; ++first) {
        while (compare(*first, pivotValue)) ++first;
        --last;
        while (compare(pivotValue, *last)) --last;
        if (first >= last) return first;
        swapT(*first, *last);
    }
}

// @ 0x006650c0  vector<AutoRefCount4>::insert(position, value)
void VecAutoRef4::FUN_006650c0(void* pos, void* value) {
    char* p = (char*)this;
    char* end = *(char**)(p + 4);
    if (end != *(char**)(p + 8)) {
        char* val = (char*)value;
        if (pos <= val && val < end) val += 4;
        if (end) {
            void* last = *(void**)(end - 4);
            *(void**)end = last;
            if (last) (*(FnP)Vslot(last, 0))(last);
        }
        FUN_00ac97a0(pos, end - 4, end);
        void* v = *(void**)value;
        void* old = *(void**)pos;
        if (v != old) {
            if (v) (*(FnP)Vslot(v, 0))(v);
            *(void**)pos = v;
            if (old) (*(FnP)Vslot(old, 4))(old);
        }
        *(char**)(p + 4) = end + 4;
        return;
    }
    int n = (int)(end - *(char**)p) >> 2;
    int nc = n ? n * 2 : 1;
    void* buf = 0;
    if (nc) buf = EASTL_allocator_allocate(nc * 4, "Editor", 0, 0, (const char*)0x13ebb38, 0xd1);
    if (buf) {
        char* begin = *(char**)p;
        char* posc = (char*)pos;
        char* e = *(char**)(p + 4);
        char* d = (char*)buf;
        for (char* s = begin; s < posc; s += 4, d += 4) *(void**)d = *(void**)s;
        { void* v = *(void**)value; *(void**)d = v; if (v) (*(FnP)Vslot(v, 0))(v); d += 4; }
        for (char* s = posc; s < e; s += 4, d += 4) *(void**)d = *(void**)s;
        if (begin && *(int*)(begin - 4) != 0) EASTL_allocator_deallocate(begin);
        *(char**)(p + 4) = (char*)buf + (int)(end - begin);
        *(void**)p = buf;
        *(char**)(p + 8) = (char*)buf + nc * 4;
    }
}

// @ 0x00665210  eastl::partial_sort<AutoRefCountT*, AlphabeticalFeedSort>
void FUN_00665210(AutoRefCountT* first, AutoRefCountT* middle, AutoRefCountT* last,
                  AlphabeticalFeedSort compare) {
    FUN_00665000(first, middle, compare);
    for (AutoRefCountT* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const AutoRefCountT temp(*i);
            *i = *first;
            FUN_00664ad0(first, 0, (int)(middle - first), 0, temp, compare);
        }
    }
    FUN_00665050(first, middle, compare);
}

// @ 0x006657a0
void cSPUIFeedListCategory::ShutdownChildren() {
    char* v = (char*)this + 0x88;
    int n = (int)((*(char**)(v + 4) - *(char**)v) >> 2);
    for (int i = 0; i < n; ++i)
        ((CatChild*)(*(void**)(*(int*)v + i * 4)))->FUN_006664f0();
    ((VecAutoRef4*)v)->erase(*(void**)v, *(void**)(v + 4));
}

// @ 0x00665410  SP::cSPUIFeedListCategory::Refresh
void* cSPUIFeedListCategory::Refresh(int id, int* groupArg) {
    char* p = (char*)this;
    int group = (int)groupArg;
    if (groupArg == (int*)-1)
        group = (int)((*(char**)(p + 0x8c) - *(char**)(p + 0x88)) >> 2);

    AutoRefCountT itemRef;
    AutoRefCountT propRef;
    FeedPair pair;

    void* pm = SP_PropertyManager();
    propRef = 0;
    if (((FnGetProp)Vslot(pm, 0x2c))(pm, id, 0x4e5892eb, (void**)&propRef)) {
        bool didLoops = false;
        FeedProp* prop = 0;
        if (propRef.mpObject &&
            ((FnGetSubProp)Vslot(propRef.mpObject, 0x24))(propRef.mpObject, 0x744717c7, (void**)&prop) &&
            prop->mType == 9) {
            pair.value = *PropDataPtr(prop);
            if (pair.value > 0) {
                didLoops = true;
                pair.id = id;
                ((Vec8*)(p + 0xa0))->push_back(&pair);

                char* mgr = (char*)FUN_0067cb30();
                FeedDirEntry* e = *(FeedDirEntry**)(mgr + 0xc8);
                FeedDirEntry* eEnd = *(FeedDirEntry**)(mgr + 0xcc);
                for (; e != eEnd; e = (FeedDirEntry*)((char*)e + 0x70)) {
                    if (e->mCategory != pair.value) continue;
                    FeedItem* item = NewFeedItem();
                    itemRef = item;
                    cSPUIFeedListItem_Init(item, 0, *(void**)(p + 0x7c), *(void**)(p + 0x6c), (void*)id, this, e);
                    item->mGroup = group;
                    PushChild(p, item);
                }

                mgr = (char*)FUN_0067cb30();
                e = *(FeedDirEntry**)(mgr + 0xb4);
                eEnd = *(FeedDirEntry**)(mgr + 0xb8);
                for (; e != eEnd; e = (FeedDirEntry*)((char*)e + 0x70)) {
                    int cat = e->mCategory;
                    if (cat == 1) {
                        void* am = FUN_00607a60();
                        unsigned __int64 auth = ((FnGetU64)Vslot(am, 0x40))(am);
                        if (e->mAuth == auth) cat = 8;
                    }
                    if (cat != pair.value) continue;
                    FeedItem* item = NewFeedItem();
                    itemRef = item;
                    cSPUIFeedListItem_Init(item, 0, *(void**)(p + 0x7c), *(void**)(p + 0x6c), (void*)id, this, e);
                    item->mGroup = group;
                    PushChild(p, item);
                }
            }
        }

        if (!didLoops) {
            FeedItem* item = NewFeedItem();
            itemRef = item;
            if (cSPUIFeedListItem_Init(itemRef.mpObject, 0, *(void**)(p + 0x7c), *(void**)(p + 0x6c), (void*)id, this, 0)) {
                itemRef->mGroup = group;
                PushChild(p, itemRef.mpObject);
            }
        }
    }

    FeedItem* ret = itemRef.mpObject;
    return ret;
}

// @ 0x00665870  SP::cSPUIFeedListCategory::RefreshAll
void __fastcall FUN_00665870(char* self, int) {
    char* p = self;
    char* children = p + 0x88;

    int n = (int)((*(char**)(children + 4) - *(char**)children) >> 2);
    for (int i = 0; i < n; ++i) {
        FeedItem* child = *(FeedItem**)(*(char**)children + i * 4);
        if (*(char*)((char*)child + 0xc0)) FUN_00669410(child);
        child->m15 = 0;
    }

    FeedDirEntry* lastA1;              // original reads this uninitialised when there are no pairs
    if (*(char**)(p + 0xa0) != *(char**)(p + 0xa4)) {
        char* mgr1 = (char*)FUN_0067cb30();
        char* mgr2 = (char*)FUN_0067cb30();
        FeedDirEntry* a1b = *(FeedDirEntry**)(mgr1 + 0xc8);
        FeedDirEntry* a1e = *(FeedDirEntry**)(mgr1 + 0xcc);
        FeedDirEntry* a2b = *(FeedDirEntry**)(mgr2 + 0xb4);
        FeedDirEntry* a2e = *(FeedDirEntry**)(mgr2 + 0xb8);
        lastA1 = a1e;

        int pairCount = (int)((*(char**)(p + 0xa4) - *(char**)(p + 0xa0)) >> 3);
        FeedDirEntry* e = a1b;
        if (e == a1e) e = a2b;
        while (e != a2e) {
            int cat = e->mCategory;
            if (cat == 1) {
                void* am = FUN_00607a60();
                unsigned __int64 auth = ((FnGetU64)Vslot(am, 0x40))(am);
                if (e->mAuth == auth) cat = 8;
            }
            for (int j = 0; j < pairCount; ++j) {
                FeedPair* pairs = (FeedPair*)*(char**)(p + 0xa0);
                if (cat != pairs[j].value) continue;

                bool found = false;
                int cn = (int)((*(char**)(children + 4) - *(char**)children) >> 2);
                for (int k = 0; k < cn; ++k) {
                    FeedItem* child = *(FeedItem**)(*(char**)children + k * 4);
                    if (FUN_005467e0(e) == child->m134) {
                        found = true;
                        child->m15 = 1;
                    }
                }
                if (found) continue;

                AutoRefCountT itemRef;
                FeedItem* item = NewFeedItem();
                itemRef = item;
                PushChild(p, item);
                cSPUIFeedListItem_Init(item, 0, *(void**)(p + 0x7c), *(void**)(p + 0x6c),
                                       (void*)pairs[j].id, p, e);
                item->m15 = 1;

                void* feed = 0;
                int count = 0;
                if (FUN_006a0ae0(*(void**)(p + 0xb8), 0x744717c1, &feed, &count)) {
                    for (int q = 0; q < count; ++q) {
                        AutoRefCountT propRef;
                        void* pm = SP_PropertyManager();
                        propRef = 0;
                        int pid = *(int*)((char*)feed + q * 0xc);
                        if (((FnGetProp)Vslot(pm, 0x2c))(pm, pid, 0x4e5892eb, (void**)&propRef) &&
                            propRef.mpObject) {
                            FeedProp* prop = 0;
                            if (((FnGetSubProp)Vslot(propRef.mpObject, 0x24))(propRef.mpObject,
                                                                             0x744717c7, (void**)&prop) &&
                                prop->mType == 9) {
                                if (*(unsigned char*)((char*)prop + 0x10) & 0x30)
                                    prop = *(FeedProp**)prop;
                                if (pairs[j].value == *(int*)prop)
                                    item->mGroup = q;
                            }
                        }
                    }
                }
            }
            e = (FeedDirEntry*)((char*)e + 0x70);
            if (e == a1e) e = a2b;
        }
    }

    char* v = p + 0x88;
    char* pos = *(char**)v;
    char* end = *(char**)(v + 4);
    while (pos != end) {
        FeedItem* child = *(FeedItem**)pos;
        if (FUN_00666450(child) && !child->m15) {
            FUN_006664f0(child);
            if (pos + 4 < end) CopyImpl(pos + 4, end, pos);
            end -= 4;
            *(char**)(v + 4) = end;
            FeedItem* stale = *(FeedItem**)end;
            if (stale) stale->Release();
        } else {
            pos += 4;
        }
    }

    FUN_006657f0(*(void**)v, *(void**)(v + 4), lastA1);
}

struct cStringLocal {                   // SP::cString (0x14 bytes), used as a stack buffer
    void* p00; void* p04; void* p08; void* p0c; unsigned int p10;
    void        FUN_006b5060();         // @ 0x006b5060  ctor
    void        FUN_006b5240();         // @ 0x006b5240  dtor
    const char* FUN_006b55c0();         // @ 0x006b55c0  c_str
};

// @ 0x00665c50
void cSPUIFeedListCategory::Populate() {
    if (!p7c || !pB8) return;
    cStringLocal str;
    str.FUN_006b5060();
    if (p78) {
        if (FUN_006a1360(pB8, 0x744717c2, &str)) {
            const char* s = str.FUN_006b55c0();
            ((void(__thiscall*)(void*, const char*))Vslot(p78, 0x80))(p78, s);
        }
    }
    void* ptr = 0;
    int count = 0;
    if (FUN_006a0ae0(pB8, 0x744717c1, &ptr, &count)) {
        for (int i = 0; i < count; ++i)
            Refresh(*(int*)((char*)ptr + i * 0xc), 0);
    }
    FUN_006657f0(childBegin, childEnd, ptr);
    str.FUN_006b5240();
}
