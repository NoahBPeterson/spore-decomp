// Slice s00664c90: SP::cSPUIFeedListCategory, its item list and helpers.
// UI module: /O2 /MD /Gy /TP /arch:SSE2 (no /EHsc).
#include "types.h"

typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPi)(void*, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void*(__thiscall* FnRetP)(void*);
typedef int(__thiscall* FnRetI)(void*);

static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }

extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p);
extern "C" void* CopyImpl(void* first, void* last, void* dest);
extern "C" void  FUN_00646d70(void* first, void* last);
extern "C" void  EA_Messaging_RemoveHandler(void* a, void* b, void* c, void* d, void* e);
extern "C" void* SP_PropertyManager();
extern "C" void* FUN_0067cb30();
extern "C" void* FUN_00607a60();
extern "C" void* FUN_005467e0();
extern "C" int   __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
extern "C" void __stdcall FUN_00601b40(void* pos, void* val);
extern "C" void  FUN_00b2af00(int* a, int* b);
extern "C" void  FUN_00ac97a0(void* a, void* b, void* c);
extern "C" void  FUN_005467e0_v();
extern "C" char  FUN_00666450(void* p);
extern "C" void  FUN_006664f0(void* p);
extern "C" void  FUN_006657f0(void* a, void* b, void* c);
extern "C" void  FUN_00669410(void* p);
extern "C" void* FUN_006676f0(void* p);
extern "C" char  cSPUIFeedListItem_Init(void* self, void* a, void* b, void* c, void* d, void* e);
extern "C" void  FUN_009512c0();
extern "C" void* FUN_009512d0(int a, int b, const char* name, int c);

extern int gVtA, gVtB, gVtC, gVtD, gVtE, gVtF, gVtG, gVtH;
extern "C" void  FUN_00665000(void*, void*, void*);
extern "C" void  FUN_00665050(void*, void*, void*);
extern "C" void  FUN_00664ad0(void*, int, int, int);
extern "C" void* FUN_00660b30(void*, void*, void*);

// ---------------------------------------------------------------------------
struct Vec8 {
    void* begin; void* end; void* cap;
    void push_back(void* val);
};
struct VecAutoRef4 {
    void* begin; void* end; void* cap;
    void erase(void* first, void* last);
};

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
    void* padAc;
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
    __declspec(noinline) void* Refresh(int param, int* count);
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
    *(void**)(p + 0xc) = &gVtC;
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

// @ 0x00664f30  partition-by-comparator helper
int* PartitionByFeed(int* first, int* last, int* key) {
    int* lo = first;
    do {
        while (lo < last) {
            int* v = (int*)*lo;
            if (!v || !key) break;
            int* kv = (int*)0;
            (void)kv;
            if (v[0x31] != *(int*)((char*)key + 0xc4)) { break; }
            const wchar_t* sa = (const wchar_t*)v[6];
            const wchar_t* sb = (const wchar_t*)key[6];
            if (!sa || !sb) break;
            if (_wcsicmp(sa, sb) < 0) { ++lo; break; }
            break;
        }
        while (last > lo) {
            int* v = (int*)*(last - 1);
            if (!key || !v) break;
            if (key[0x31] != *(int*)((char*)v + 0xc4)) { break; }
            const wchar_t* sa = (const wchar_t*)key[6];
            const wchar_t* sb = (const wchar_t*)v[6];
            if (!sa || !sb) break;
            if (_wcsicmp(sa, sb) < 0) { --last; continue; }
            break;
        }
        if (lo >= last) break;
        FUN_00b2af00(lo, last - 1);
        ++lo;
    } while (true);
    if (key) (*(FnP)Vslot(key, 4))(key);
    return lo;
}

// @ 0x006650c0  vector<AutoRefCount4>::insert(position, value)
void FUN_006650c0(void* self, void* pos, void* value) {
    char* p = (char*)self;
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

// @ 0x00665210  partial_sort
void FUN_00665210(void* first, void* mid, void* last, void* cmp) {
    FUN_00665000(first, mid, cmp);
    while (mid < last) {
        void* v = *(void**)mid;
        void* f = *(void**)first;
        bool less = false;
        if (v && f) {
            int a = *(int*)((char*)v + 0xc4), b = *(int*)((char*)f + 0xc4);
            if (a != b) less = a < b;
            else {
                const wchar_t* sa = *(const wchar_t**)((char*)v + 0x18);
                const wchar_t* sb = *(const wchar_t**)((char*)f + 0x18);
                if (sa && sb && _wcsicmp(sa, sb) < 0) less = true;
            }
        }
        if (less) {
            FUN_00664ad0(first, 0, ((char*)mid - (char*)first) >> 2, 0);
        }
        mid = (char*)mid + 4;
    }
    FUN_00665050(first, mid, cmp);
}

// @ 0x006657a0
void cSPUIFeedListCategory::ShutdownChildren() {
    char* v = (char*)this + 0x88;
    int n = (int)((*(char**)(v + 4) - *(char**)v) >> 2);
    for (int i = 0; i < n; ++i)
        ((CatChild*)(*(void**)(*(int*)v + i * 4)))->FUN_006664f0();
    ((VecAutoRef4*)v)->erase(*(void**)v, *(void**)(v + 4));
}

// @ 0x00665410  Refresh
void* cSPUIFeedListCategory::Refresh(int param, int* count) {
    char* p = (char*)this;
    (void)count;
    int n = (int)((*(char**)(p + 0x8c) - *(char**)(p + 0x88)) >> 2);
    (void)n;
    if (param == -1) param = (*(int*)(p + 0x8c) - *(int*)(p + 0x88)) >> 2;
    void* pm = SP_PropertyManager();
    void* local = 0;
    (*(char(__thiscall*)(void*, int, void**))Vslot(pm, 0x2c))(pm, 0x4e5892eb, &local);
    return 0;
}

// @ 0x00665870  RefreshAll
void FUN_00665870(char* p) {
    for (int i = 0; i < (int)((*(char**)(p + 0x8c) - *(char**)(p + 0x88)) >> 2); ++i)
        FUN_00669410(p);
}

extern "C" void  FUN_006b5060(void* self);
extern "C" void  FUN_006b5240(void* self);
extern "C" void  FUN_006b55c0(void* self);
extern "C" char  FUN_006a1360(void* obj, int k, void* out);
extern "C" char  FUN_006a0ae0(void* obj, int k, int* count, void** ptr);

// @ 0x00665c50
void cSPUIFeedListCategory::Populate() {
    char* p = (char*)this;
    if (!*(void**)(p + 0x7c) || !*(void**)(p + 0xb8)) return;
    char str[0x14];
    FUN_006b5060(str);
    if (*(void**)(p + 0x78)) {
        if (FUN_006a1360(*(void**)(p + 0xb8), 0x744717c2, str))
            FUN_006b55c0(str);
    }
    int a = 0;
    void* b = 0;
    if (FUN_006a0ae0(*(void**)(p + 0xb8), 0x744717c1, &a, &b)) {
        for (int i = 0; i < a; ++i)
            Refresh(*(int*)((char*)b + i * 0xc), 0);
    }
    FUN_006657f0(*(void**)(p + 0x8c), *(void**)(p + 0x88), b);
    FUN_006b5240(str);
}
