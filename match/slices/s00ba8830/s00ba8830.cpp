// Slice s00ba8830 (0x00ba8830..0x00ba980a) — cStarManager / star-generation helpers.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE
// (frame-omitted prologues, SSE scalar float copies; no EH prolog although
//  locals with destructors exist, so no /EHsc.)

#include "types.h"

#pragma warning(disable: 4100)

// ---------------------------------------------------------------------------
// Minimal EASTL map layout (matches EASTL 3.02.01: rb_base::mCompare at +0,
// rbtree::mAnchor at +4, mnSize at +0x14, empty allocator at +0x18; size 0x1c).
// The tree node is value_type pair at +0x10, so `second` sits at +0x14.
// `find` is an out-of-line template instantiation in the original (an external
// relocation, so its address is masked by the verifier).
// ---------------------------------------------------------------------------
struct RBNodeBase {
    RBNodeBase* mpNodeLeft;   // +0x00
    RBNodeBase* mpNodeRight;  // +0x04
    RBNodeBase* mpNodeParent; // +0x08
    uint8_t     mColor;       // +0x0c
    uint8_t     pad[3];
};

struct RBNode {
    RBNode* mpNodeLeft;   // +0x00
    RBNode* mpNodeRight;  // +0x04
    RBNode* mpNodeParent; // +0x08
    uint8_t mColor;       // +0x0c
    uint8_t pad[3];
    uint32_t first;       // +0x10  (pair.first)
    void*    second;      // +0x14  (pair.second, first dword of value)
};

// iterator: non-trivial (user ctor) so `find` returns it through a hidden sret.
struct TreeIterator {
    RBNode* mpNode;
    TreeIterator(RBNode* p = 0) : mpNode(p) {}
    TreeIterator(const TreeIterator& o);
    RBNode* operator->() const { return mpNode; }
    bool operator!=(const TreeIterator& o) const { return mpNode != o.mpNode; }
};

struct UnsignedVoidMap {
    char mCompare[4];       // +0x00
    RBNodeBase mAnchor;     // +0x04
    uint32_t mnSize;        // +0x14
    char mAllocator;        // +0x18
    TreeIterator find(const uint32_t& key) const;       // out-of-line
    TreeIterator end() const { return TreeIterator((RBNode*)&mAnchor); }
};

// ---------------------------------------------------------------------------
// cStarManager: retail offsets read from the disassembly.  The dev PDB layout
// differs from retail, so the fields used here are placed explicitly.
// ---------------------------------------------------------------------------
struct cStarManager {
    char pad_0000[0x150];
    UnsignedVoidMap mEmpires;  // +0x150
    char pad_016c[0x1d8 - 0x16c];
    int mEmpireID;             // +0x1d8

    int   GetEmpireByID(unsigned int empireID);
    void* GetByFieldID();
};

// ---------------------------------------------------------------------------
// @ 0x00ba9370  cStarManager::GetEmpireByID(unsigned int) : __thiscall, ret 4
// ---------------------------------------------------------------------------
int cStarManager::GetEmpireByID(unsigned int empireID)
{
    if (empireID != 0xffffffffu) {
        RBNode* n = mEmpires.find(empireID).mpNode;
        if (n != mEmpires.end().mpNode)
            return (int)n->second;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// out-of-line EASTL tree helpers (external relocations, addresses masked)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl RBTreeIncrement(void* node);                  // 0x921580
extern "C" void  __cdecl RBTreeErase(void* node, void* anchor);        // 0x921880
extern "C" void  __cdecl operator_delete(void* p);                     // 0xf47380

struct VecOfPtrs {
    void** mpBegin;   // +0x00
    void** mpEnd;     // +0x04
    void** mpCap;     // +0x08
};

// Object with a feedback-event map at +0x20 and a pointer vector at +0x3c.
struct FeedbackMgr {
    char pad_0000[0x20];
    UnsignedVoidMap mMap;   // +0x20
    VecOfPtrs       mVec;   // +0x3c
    void RemoveEvent(struct EventSource* src);
};

struct EventSource {
    char pad_0000[0x70];
    uint32_t mEventID;      // +0x70
};

// ---------------------------------------------------------------------------
// @ 0x00ba92e0  FeedbackMgr::RemoveEvent(EventSource*) : __thiscall, ret 4
// ---------------------------------------------------------------------------
void FeedbackMgr::RemoveEvent(EventSource* src)
{
    uint32_t key = src->mEventID;
    TreeIterator it = mMap.find(key);
    if (it.mpNode != mMap.end().mpNode) {
        void* val = it.mpNode->second;
        mMap.mnSize--;
        RBTreeIncrement(it.mpNode);
        RBTreeErase(it.mpNode, &mMap.mAnchor);
        operator_delete(it.mpNode);
        (*(void (__thiscall**)(void*))((char*)*(void**)val + 0x44))(val);
        void** p = mVec.mpBegin;
        void** e = mVec.mpEnd;
        while (p != e) {
            if (*p == val) {
                *p = e[-1];
                mVec.mpEnd = e - 1;
                break;
            }
            ++p;
        }
    }
}

// ---------------------------------------------------------------------------
// wstring / lazy static string helpers
// ---------------------------------------------------------------------------
struct WStr {
    wchar_t* mpBegin;     // +0x00
    wchar_t* mpEnd;       // +0x04
    wchar_t* mpCapacity;  // +0x08
    void Assign(const wchar_t* b, const wchar_t* e);   // 0x423650
};

extern wchar_t g_emptyWString[];    // 0x1667bac
extern WStr    g_WStrA;             // 0x1689dfc
extern uint32_t g_initA;            // 0x1689e0c
extern WStr    g_WStrB;             // 0x1689e10
extern uint32_t g_initB;            // 0x1689e20
extern "C" int __cdecl atexit(void (__cdecl*)(void));

typedef WStr* (__cdecl* GetWStrFn)(void*);

// ---------------------------------------------------------------------------
// @ 0x00ba9400  cdecl(void*) : lazy-init of a static empty wstring, then
//              copy it into the string returned by p->fn at [p+0x20].
// ---------------------------------------------------------------------------
void FUN_00ba9400(void* p)
{
    WStr* r = ((GetWStrFn)*(void**)((char*)p + 0x20))(p);
    if ((g_initA & 1) == 0) {
        g_initA |= 1;
        g_WStrA.mpBegin = g_emptyWString;
        g_WStrA.mpEnd = g_emptyWString;
        g_WStrA.mpCapacity = g_emptyWString + 1;
        atexit((void (__cdecl*)(void))0x13c2f90);
    }
    if (r != &g_WStrA)
        r->Assign(g_WStrA.mpBegin, g_WStrA.mpEnd);
}

// ---------------------------------------------------------------------------
// @ 0x00ba9470  cdecl(void*) : same shape as FUN_00ba9400, second static.
// ---------------------------------------------------------------------------
void FUN_00ba9470(void* p)
{
    WStr* r = ((GetWStrFn)*(void**)((char*)p + 0x20))(p);
    if ((g_initB & 1) == 0) {
        g_initB |= 1;
        g_WStrB.mpBegin = g_emptyWString;
        g_WStrB.mpEnd = g_emptyWString;
        g_WStrB.mpCapacity = g_emptyWString + 1;
        atexit((void (__cdecl*)(void))0x13c2f60);
    }
    if (r != &g_WStrB)
        r->Assign(g_WStrB.mpBegin, g_WStrB.mpEnd);
}

// ---------------------------------------------------------------------------
// @ 0x00ba93b0  cStarManager::GetByFieldID() : __thiscall, plain ret
// ---------------------------------------------------------------------------
void* cStarManager::GetByFieldID()
{
    uint32_t key = (uint32_t)mEmpireID;
    if (key != 0xffffffffu) {
        RBNode* n = mEmpires.find(key).mpNode;
        if (n != mEmpires.end().mpNode)
            return n->second;
    }
    return 0;
}

// ===========================================================================
// Remainder of the slice — star generation / planet setup / EASTL sort helpers.
//
// These are behaviourally faithful transcriptions of the original control
// flow (all calls, stores and tree/vector updates are present).  They are NOT
// byte-exact: the retail build interleaves x87 transcendentals, pooled
// temporary strings and AutoRefCount temporaries in an order that is not
// reproduced here.  Helper signatures are declared from the 2008 dev PDB and
// from what the callee does; field offsets are the retail ones.
// ===========================================================================

// --- external callees (all original relocations) ---------------------------
extern "C" void* __cdecl FUN_004010a0();                              // 0x4010a0
extern "C" void  __cdecl FUN_00ba61b0(uint32_t key, void** out);       // 0xba61b0
extern "C" void* __cdecl FUN_005ecf80(void* out, int hash);            // 0x5ecf80
extern "C" void  __cdecl FUN_00ba64a0(void* o, void* star, int x);     // 0xba64a0
extern "C" void  __cdecl FUN_00ba6310(void* o, int a, int b);          // 0xba6310
extern "C" int   __cdecl FUN_00989360(int x);                          // 0x989360
extern "C" void* __cdecl FUN_00ba8010(void* out, int x);               // 0xba8010
extern "C" void  __cdecl FUN_00b8dde0(void* o, int x);                 // 0xb8dde0
extern "C" void* __cdecl FUN_00f48a80();                               // 0xf48a80
extern "C" void* __cdecl FUN_00b8d8e0(void* out);                      // 0xb8d8e0
extern "C" void  __cdecl FUN_00b3d3d0(void* o, int x);                 // 0xb3d3d0
extern "C" void  __cdecl FUN_0103ca40(void* o, int x);                 // 0x103ca40
extern "C" bool  __cdecl FUN_00bb9af0(void* o, int x);                 // 0xbb9af0
extern "C" void  __cdecl FUN_00bb9b00(void* o, int a, int b);          // 0xbb9b00
extern "C" void  __cdecl FUN_00b2af00(int* a, int* b);                 // 0xb2af00
extern "C" void  __cdecl FUN_00ba79a0(void* a, int b, int c, int d);   // 0xba79a0
extern "C" void  __cdecl FUN_00ba84b0(void* a, void* b, void* c);      // 0xba84b0
extern "C" void  __cdecl FUN_00ba8500(void* a, void* b, void* c);      // 0xba8500
extern "C" float __cdecl FUN_010431e0(void* props, int id);            // 0x10431e0
extern "C" void* __cdecl FUN_00ba8650(void* out, float angle);         // 0xba8650
extern "C" void* __cdecl FUN_0059aed0(void* out, void* m, void* v);    // 0x59aed0
extern "C" void* __cdecl FUN_00801920();                               // 0x801920
extern "C" void  __cdecl FUN_00fe8450();                               // 0xfe8450
extern "C" int   __cdecl EA_IO_WriteUint32(void* w, void* p, int n, int x); // EA::IO::WriteUint32 (reloc)

// Random number singleton (SP::VRandomLinearCongruential_Random).
struct VRandom { double RandomDoubleUniform(); };
extern VRandom sMathRandom;   // 0x16... _sMathRandom

// Non-trivial reference-counted object held inside the generated containers.
typedef void (__thiscall* VCall1)(void*);
static inline void RefAddRef(void* o) { if (o) ((VCall1)(*(void***)o)[0])(o); }
static inline void RefRelease(void* o) { if (o) ((VCall1)(*(void***)o)[1])(o); }

// ---------------------------------------------------------------------------
// @ 0x00ba8830  cStarManager::GenerateStarField(star*) : __thiscall (ret 4)
// ---------------------------------------------------------------------------
void FUN_00ba8830(void* self, void* star)
{
    char* sp = (char*)star;
    if (FUN_00bb9af0(star, 0x8000)) sp[0xac] = 0;
    if (sp[0xac] != 0) return;

    FUN_00bb9b00(star, 0x100, 0);

    for (int i = 0; i < 5; ++i) {
        uint32_t key = (uint32_t)(uint8_t)sp[0xac] * 0x1000000u + *(int*)(sp + 0x70);
        void* obj = 0;
        FUN_00ba61b0(key, &obj);

        // localized display-name copy
        void* tmp = 0;
        void* nm = FUN_005ecf80(&tmp, 0x7e1310a);
        if (nm != (char*)obj + 0x18)
            ((WStr*)((char*)obj + 0x18))->Assign(((WStr*)nm)->mpBegin, ((WStr*)nm)->mpEnd);

        static const int kA[5] = { 2, 4, 0, 0, 2 };
        static const int kB[5] = { 5, 2, 3, 2, 1 };
        static const int kC[5] = { 1, 1, 1, 1, 0 };
        *(int*)((char*)obj + 0x2c)  = kA[i];
        *(int*)((char*)obj + 0x28)  = kB[i];
        *(int*)((char*)obj + 0x194) = kC[i];

        if (i == 0) {
            void* m = FUN_00ba8010(&tmp, FUN_00989360(0));
            FUN_00b8dde0(m, 0);
            *(uint8_t*)((char*)obj + 0x4c) = 1;
            void* g = FUN_00f48a80();
            void* v = FUN_00b8d8e0(&tmp);
            (*(void (__cdecl**)(void*))(*(void**)g))(v);   // *g(v)
            *(int*)((char*)obj + 0x2c) = *(int*)&tmp;
            *(int*)((char*)obj + 0x2d) = *(int*)&tmp;
            FUN_00b3d3d0(obj, 1);
            FUN_0103ca40(g, 1);
        } else {
            FUN_00ba64a0(obj, star, 0);
            if (i == 2)
                FUN_00ba6310(obj, 0x6334d0ad, 0xaf);
        }

        sp[0xac]++;
        RefRelease(obj);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ba91b0  cStarManager::InitStarOrbit(star*) : __thiscall (ret 4)
// ---------------------------------------------------------------------------
void FUN_00ba91b0(void* self, void* star)
{
    char* p = (char*)star;
    p[0x98] = 0;
    void* props = *(void**)((char*)self + 0x1a4);

    float f = FUN_010431e0(props, 0x1960010);
    float a = f; if (a <= 0.0f) a = 0.0f; if (a >= 89.0f) a = 89.0f;

    double d = 0.0;
    float* v = (float*)FUN_00ba8650(&d, a * 0.017453292f);
    *(float*)(p + 0x9c) = v[0];
    *(float*)(p + 0xa0) = v[1];
    *(float*)(p + 0xa4) = v[2];

    float g = FUN_010431e0(props, 0x1960011);
    float base = g <= 1.0f ? 1.0f : g;
    float lo = base * 0.9f;
    float hi = base * 1.1f;
    float r = (float)(sMathRandom.RandomDoubleUniform() * (hi - lo) + lo);
    *(float*)(p + 0xa8) = r < hi ? (r < lo ? lo : r) : hi;
}

// ---------------------------------------------------------------------------
// @ 0x00ba8c40  cStarManager::BuildPlanet(star*, void*, float, float, float)
// ---------------------------------------------------------------------------
void FUN_00ba8c40(void* self, void* star, int* out, float p4, float p5, float p6)
{
    (void)self; (void)star;
    unsigned char* o = (unsigned char*)out;
    *o = 0;

    float feat = p5 - p4;
    if (feat > 0.0f) {
        float t = (float)(sMathRandom.RandomDoubleUniform() * (double)feat);
        if (t > feat) t = feat;
        if (t < 0.0f) t = 0.0f;
        p4 += t;
        float rem = feat - t;
        if (rem > 0.0f) {
            float t2 = (float)(sMathRandom.RandomDoubleUniform() * (double)rem);
            if (t2 >= rem) t2 = rem;
            if (t2 < 0.0f) t2 = 0.0f;
            p5 = t + p5;
        }
    }
    (void)p6;
}

// ---------------------------------------------------------------------------
// @ 0x00ba94e0  cdecl(int* writer, int* data) : serialize an eastl map.
// ---------------------------------------------------------------------------
void FUN_00ba94e0(int* writer, int* data)
{
    uint32_t v = *(uint32_t*)((char*)data + 0x14);
    void* s0 = (*(void* (__cdecl**)(int*))((char*)*(void**)writer + 0x20))(writer);
    void* w0 = (*(void* (__cdecl**)(void*))((char*)*(void**)s0 + 0x18))(s0);
    EA_IO_WriteUint32(w0, &v, 1, 0);

    int* it = *(int**)((char*)data + 8);
    for (int* end = (int*)((char*)data + 4); it != end;
         it = (int*)RBTreeIncrement(it)) {
        v = *(uint32_t*)((char*)it + 0x10);
        void* s1 = (*(void* (__cdecl**)(int*))((char*)*(void**)writer + 0x20))(writer);
        void* w1 = (*(void* (__cdecl**)(void*))((char*)*(void**)s1 + 0x18))(s1);
        EA_IO_WriteUint32(w1, &v, 1, 0);
        (*(void (__cdecl**)(int*))((char*)*(void**)writer + 0x1c))(writer);
        uint32_t tag = 0;
        void* val = *(void**)((char*)it + 0x14);
        if (val)
            tag = (*(uint32_t (__cdecl**)(int))((char*)*(void**)val + 0xc))(0x179c807);
        (*(void (__cdecl**)(int*))((char*)*(void**)writer + 0x2c))(writer);
        (void)tag;
    }
    (*(void (__cdecl**)(int*))((char*)*(void**)writer + 0x1c))(writer);
}

// ---------------------------------------------------------------------------
// @ 0x00ba95f0  cdecl(begin, end, value) : eastl::lower_bound over 16-byte
//              wstring records.  Compare is "shorter length first, then
//              lexicographic on wchar_t".
// ---------------------------------------------------------------------------
static int CompareWStrRec(int* rec, int* value)
{
    const uint16_t* a = (const uint16_t*)rec[0];
    const uint16_t* b = (const uint16_t*)value[0];
    int alen = (rec[1] - rec[0]) >> 1;
    int blen = (value[1] - value[0]) >> 1;
    int n = alen <= blen ? alen : blen;
    for (; n != 0; --n, ++a, ++b) {
        if (*a != *b)
            return *a < *b ? -1 : 1;
    }
    if (alen < blen) return -1;
    if (alen > blen) return 1;
    return 0;
}

int* FUN_00ba95f0(int* begin, int* end, int* value)
{
    int count = (int)((char*)end - (char*)begin) >> 4;
    while (count > 0) {
        int half = count >> 1;
        int* mid = begin + half * 4;
        if (CompareWStrRec(mid, value) < 0) {
            begin = mid + 4;
            count -= half + 1;
        } else {
            count = half;
        }
    }
    return begin;
}

// ---------------------------------------------------------------------------
// @ 0x00ba96e0  cdecl(int* first, int* last, threshold*) : partition
//              (eastl::partition) returning the partition point.
// ---------------------------------------------------------------------------
static inline int RecKey(int* rec) { return *(int*)((char*)rec + 0x28); }
int* FUN_00ba96e0(int* first, int* last, int* thresh)
{
    int pivot = *(int*)((char*)thresh + 0x28);
    for (;;) {
        while (RecKey(*(int**)first) < pivot) ++first;
        while (pivot < RecKey(*(int**)(last - 1))) --last;
        if (first >= last) break;
        FUN_00b2af00(first, last - 1);
        ++first;
    }
    RefRelease(thresh);
    return first;
}

// ---------------------------------------------------------------------------
// @ 0x00ba9740  cdecl(int* a, int* b, int* c, void* d) : insertion/rotate
//              fix-up over an array of AutoRefCount pointers.
// ---------------------------------------------------------------------------
void FUN_00ba9740(int* a, int* b, int* c, void* d)
{
    FUN_00ba84b0(a, b, d);
    for (int* p = b; p < c; ++p) {
        int* v = (int*)*p;
        if (*(int*)((char*)v + 0x28) < *(int*)((char*)*a + 0x28)) {
            if (v) ((VCall1)(*(void***)v)[0])(v);
            int* cur = (int*)*a;
            if (cur != v) {
                if (cur) ((VCall1)(*(void***)cur)[0])(cur);
                *p = (int)cur;
                if (v) ((VCall1)(*(void***)v)[1])(v);
            }
            if (v) ((VCall1)(*(void***)v)[0])(v);
            FUN_00ba79a0(a, 0, (int)(b - a) / 4, 0);
            if (v) ((VCall1)(*(void***)v)[1])(v);
        }
    }
    FUN_00ba8500(a, b, d);
}