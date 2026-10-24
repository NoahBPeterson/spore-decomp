// Slice s00b75f70: Simulator-module algorithm/container internals
// (0xb75f70-0xb76ee8): the quicksort partition + median-of-three and heap
// selection helpers, the EASTL fixed-hashtable erase/erase-key/operator[]
// members, the fixed-vector growth helper, and the Sim high-LOD per-planet
// init / resource-key walks that share the translation unit.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

// ---------------------------------------------------------------- external callees
void  __cdecl FUN_00b75750(void* base, void* cur, Vec3 p);      // 0xb75750
void  __cdecl FUN_00b757b0(void* base, void* cur, Vec3 p);      // 0xb757b0
void  __cdecl FUN_00b74d60(void* base, int a, int b, int c, void* o, Vec3 p); // 0xb74d60
void  __cdecl FUN_00b75c60(void* first, void* last, void* buf, void* a4);     // 0xb75c60
void  __cdecl FUN_00b74c20(void* buf, void* end, void* uninit); // 0xb74c20
void  __cdecl FUN_00b754d0(void* first, void* last, void* last2, void* comp); // 0xb754d0
void* __cdecl FUN_00b75620(void* first, void* last, void* pivot);             // 0xb75620
void* __cdecl FUN_00b734e0(void* first, void* mid, void* last, Vec3 a, Vec3 b); // 0xb734e0
void* __cdecl FUN_00b749c0(void* begin, void* end, float x, float y, float z); // 0xb749c0
void* __cdecl EAAllocate(unsigned int sz, const char* name, int a, int b, int c, int d); // 0xf473a0
void  __cdecl opdel(void* p);                                   // 0xf47380  ??3@YAXPAX@Z
void  __cdecl FUN_0102c7f0(void* a, int b);                     // 0x102c7f0
char  __cdecl FUN_00ae5530(void* a, int b, void* c, const wchar_t* d); // 0xae5530
void* __cdecl FUN_00401010();                                   // 0x401010
void  __cdecl FUN_00407190(void* comp, unsigned key, void* out); // 0x407190
void* __cdecl FUN_00b3d2a0();                                   // 0xb3d2a0
void* __cdecl FUN_00b3d520();                                   // 0xb3d520
void* __cdecl FUN_00b3d350();                                   // 0xb3d350
void  __cdecl FUN_0093c5a0(void* out, const char* s, int n);    // 0x93c5a0
struct C579a90 {
    void __thiscall RangeInitialize(int n);                     // 0x579a90
};
struct C56e2d0 {
    void __thiscall Copy(const void* src);                      // 0x56e2d0
};

extern const float g_14650a4;
extern char g_1601760;                                          // +0x1601760 RNG global object
struct Var {
    char pad_0[0x10];                                           // +0x00
    unsigned short mFlags;                                      // +0x10
    unsigned short mTypeId;                                     // +0x12
};
struct C5dd750 {
    Var* __thiscall SetBool(const unsigned char* src);          // 0x5dd750
};
struct CVariant {
    void __thiscall Destruct(bool b);                           // 0x93db80
};
struct C5765e0 {
    void __thiscall Release();                                  // 0x5765e0
};
struct C478db0 {
    void* __thiscall Assign(void* p);                           // 0x478db0
};
struct C537dc0 {
    void* __thiscall Assign(const void* src);                   // 0x537dc0
};
struct C72520 {
    void __thiscall Rotate(float x, float y, float z);          // 0xb72520
};
struct CRandomGlob {
    double __thiscall RandomDoubleUniform();                    // 0x9360d0
};
struct CStarManager {
    void* __thiscall GetUFO();                                  // 0xba93b0
};
struct CEmpire {
    int* __thiscall GetUFOKey();                                // 0xc326b0
};
struct CSubObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void v14(unsigned key, void* val);
};

// thiscall callees modelled as members of dummy classes so the call carries ecx.
struct C74860 {
    void __thiscall Find(int* out, int* key);                   // 0xb74860
};
struct C75910 {
    void __thiscall Next(void* out, void* it);                  // 0xb75910
};
struct C75a30 {
    void __thiscall Grow(void* end, const void* v);             // 0xb75a30
};
struct C752f0 {
    void __thiscall Insert(void* out, const void* v, int z);    // 0xb752f0
};
struct C75890 {
    int* __thiscall InsertKey(const void* k);                   // 0xb75890
};
struct C74f80 {
    void __thiscall Notify(void* o, float a, float b);          // 0xb74f80
};
struct C75c00 {
    void __thiscall DoFreeNodes(void* buckets, int nb);         // 0xa1b6c0
};
struct C82060 {
    void __thiscall Run(const Vec3* d, const Vec3* a, const Vec3* dir); // 0xb82060
};
struct CXForm {
    void __thiscall BackTransform(Vec3* p);                     // 0x4ff6d0
};
struct CVec3v {
    void** begin;                                               // +0x00
    void** end;                                                 // +0x04
    void** cap;                                                 // +0x08
    void  __thiscall DoInsertValue(void* at, const Vec3* v);    // 0x4b5ad0
};

extern const float g_1687ad4, g_1687ad8, g_1687adc;
extern const float g_16880e0, g_16880e4, g_16880e8;
extern int g_13f6254;
extern const float g_1464fdc;

// ============================================================ 0xb75f70
// @ 0x00b75f70
Vec3* __cdecl FUN_00b75f70(Vec3* first, Vec3* last, Vec3 pivot,
                           bool (__cdecl* comp)(const Vec3*, const Vec3*)) {
    for (;;) {
        while (comp(first, &pivot)) ++first;
        do { --last; } while (comp(&pivot, last));
        if (first >= last) return first;
        Vec3 tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
}

// ============================================================ 0xb76020
struct Blob { char pad[0x38]; float x, y, z; };                 // x@0x38 y@0x3c z@0x40
// @ 0x00b76020
void __cdecl FUN_00b76020(void** base, void** cur, void** end, Vec3 p) {
    FUN_00b75750(base, cur, p);
    for (void** i = cur; i < end; ++i) {
        Blob* o = (Blob*)*i;
        Blob* b = (Blob*)*base;
        float dz = p.z - o->z;
        float az = p.z - b->z;
        float dx = p.x - o->x;
        float dy = p.y - o->y;
        float ay = p.y - b->y;
        float ax = p.x - b->x;
        if ((dz * dz + dx * dx) + dy * dy < (az * az + ay * ay) + ax * ax) {
            *i = b;
            FUN_00b74d60(base, 0, (int)(cur - base), 0, o, p);
        }
    }
    FUN_00b757b0(base, cur, p);
}

// ============================================================ 0xb76400
// EASTL fixed hash_map<u32, float>::operator[] : find, else insert 0.0f.
struct NodeF { int key; float val; };
struct ItF { NodeF* n; NodeF** b; };
struct VTF { int key; float val; };
struct PF { ItF it; bool b; };
struct ZF { bool b; };
struct MF {
    int pad;              // +0x00
    NodeF** buckets;      // +0x04
    unsigned nb;          // +0x08
    ItF find(const int& k);              // 0x645ed0
    PF insertz(const VTF& v, ZF z);      // 0xc15fd0
};
// @ 0x00b76400
float* __fastcall FUN_00b76400(MF* m, int, const int& k) {
    NodeF* n;
    { ItF it = m->find(k); n = it.n; }
    if (n == m->buckets[m->nb]) {
        VTF v = { k, 0 };
        ZF z; z.b = false;
        PF r = m->insertz(v, z);
        return &r.it.n->val;
    }
    return &n->val;
}

// ============================================================ 0xb76460
// same shape, but an existing entry short-circuits and the inserted temporary
// value is released through its vtable.
struct RefVal { virtual void AddRef(); virtual void Release(); };
struct NRef { int key; RefVal* val; };
struct ItR { NRef* n; NRef** b; };
struct VTR { int key; RefVal* val; };
struct PR { ItR it; bool b; };
struct MR {
    int pad;
    NRef** buckets;
    unsigned nb;
    ItR find(const int& k);              // 0x645ed0
    PR insertr(const VTR& v, ZF z);     // 0xb752f0
};
// @ 0x00b76460
RefVal** __fastcall FUN_00b76460(MR* m, int, const int& k) {
    NRef* n;
    { ItR it = m->find(k); n = it.n; }
    if (n != m->buckets[m->nb]) return &n->val;
    VTR v; v.key = k; v.val = 0;
    ZF z; z.b = false;
    PR r = m->insertr(v, z);
    if (v.val) v.val->Release();
    return &r.it.n->val;
}

// ============================================================ 0xb764e0
struct It8 { void* n; void* b; };
struct C764e0 {
    It8 __thiscall Next(It8 i);                                   // 0xb75910
    It8 __thiscall Advance(It8 first, It8 last);
};
// @ 0x00b764e0
It8 C764e0::Advance(It8 first, It8 last) {
    while (first.n != last.n) first = Next(first);
    return first;
}

// ============================================================ 0xb76530
struct El18 { float a, b, c, d; char e; int f; };                  // 0x18
struct C76530 {
    char pad[4];
    El18* mEnd;                                                    // +0x04
    El18* mCap;                                                    // +0x08
    void __thiscall Grow(El18* end, const El18* v);                // 0xb75a30
    void __thiscall Push(const El18& v);
};
// @ 0x00b76530
void C76530::Push(const El18& v) {
    El18* p = mEnd;
    if (p < mCap) {
        mEnd = p + 1;
        if (p) {
            p->a = v.a; p->b = v.b; p->c = v.c; p->d = v.d;
            p->e = v.e; p->f = v.f;
        }
        return;
    }
    Grow(p, &v);
}

// ============================================================ 0xb76580
// hashtable erase(iterator): mpNext lives at +0xc70 and each node owns a
// heap buffer at +0x58 that is freed first.
struct HTN70 { char pad[0xc70]; HTN70* mpNext; };
struct HT70 {
    struct iterator { HTN70* mpNode; HTN70** mpBucket; };
    int pad0[3];                                         // +0x00..0x08
    unsigned mnElementCount;                             // +0x0c
    iterator erase(iterator i);
};
// @ 0x00b76580
HT70::iterator HT70::erase(iterator i) {
    HTN70* const n = i.mpNode;
    HTN70** const b = i.mpBucket;
    iterator next;
    next.mpBucket = b;
    next.mpNode = n->mpNext;
    while (next.mpNode == 0) { ++next.mpBucket; next.mpNode = *next.mpBucket; }
    HTN70* pNode = *b;
    if (pNode == n) {
        *b = pNode->mpNext;
    } else {
        HTN70* pNext = pNode->mpNext;
        while (pNext != n) { pNode = pNext; pNext = pNext->mpNext; }
        pNode->mpNext = pNext->mpNext;
    }
    void* buf = *(void**)((char*)n + 0x58);
    if (buf != 0 && *(int*)((char*)buf - 4) != 0) opdel(buf);
    opdel(n);
    --mnElementCount;
    return next;
}

// ============================================================ 0xb76620
// hashtable erase(key) returning the number of removed elements.
struct HTN68 { unsigned key; char pad[0xc68 - 4]; HTN68* mpNext; };
struct HT68 {
    int pad0;
    HTN68** buckets;                                     // +0x04
    unsigned nb;                                         // +0x08
    unsigned mnElementCount;                             // +0x0c
    int eraseKey(const unsigned* k);
};
// @ 0x00b76620
int HT68::eraseKey(const unsigned* kp) {
    unsigned key = *kp;
    int old = mnElementCount;
    HTN68** b = &buckets[key % nb];
    HTN68* p;
    while ((p = *b) != 0) {
        if (p->key == key) break;
        b = &p->mpNext;
    }
    if (*b) {
        do {
            p = *b;
            if (p->key != key) break;
            *b = p->mpNext;
            void* buf = *(void**)((char*)p + 0x50);
            if (buf != 0 && *(int*)((char*)buf - 4) != 0) opdel(buf);
            opdel(p);
            --mnElementCount;
        } while (*b);
    }
    return old - (int)mnElementCount;
}

// ============================================================ 0xb766b0
struct HTN68b { char pad[0xc68]; HTN68b* mpNext; };
struct HT68b {
    struct iterator { HTN68b* mpNode; HTN68b** mpBucket; };
    int pad0[3];
    unsigned mnElementCount;
    iterator erase(iterator i);
};
// @ 0x00b766b0
HT68b::iterator HT68b::erase(iterator i) {
    HTN68b* const n = i.mpNode;
    HTN68b** const b = i.mpBucket;
    iterator next;
    next.mpBucket = b;
    next.mpNode = n->mpNext;
    while (next.mpNode == 0) { ++next.mpBucket; next.mpNode = *next.mpBucket; }
    HTN68b* pNode = *b;
    if (pNode == n) {
        *b = pNode->mpNext;
    } else {
        HTN68b* pNext = pNode->mpNext;
        while (pNext != n) { pNode = pNext; pNext = pNext->mpNext; }
        pNode->mpNext = pNext->mpNext;
    }
    void* buf = *(void**)((char*)n + 0x50);
    if (buf != 0 && *(int*)((char*)buf - 4) != 0) opdel(buf);
    opdel(n);
    --mnElementCount;
    return next;
}

// ============================================================ 0xb768d0
// sort a 0xc-byte element range through a temporary scratch buffer.
// @ 0x00b768d0
void __cdecl FUN_00b768d0(void* first, void* last, void* a3, void* a4) {
    int n = (int)((char*)last - (char*)first) / 0xc;
    if (n > 1) {
        char* buf = (char*)EAAllocate(n * 0xc, "Simulator", 0, 0, 0x13ebb38, 0xd1);
        char uninit[12];
        FUN_00b74c20(buf, buf + n * 0xc, uninit);
        FUN_00b75c60(first, last, buf, a4);
        opdel(buf);
    }
}

// ============================================================ 0xb76950
// quicksort: median-of-three pivot, Hoare partition via FUN_00b75f70, then
// recurse on the right and iterate on the left.  Small ranges fall back to
// insertion sort when the depth budget is exhausted.
typedef bool (__cdecl* Cmp3)(const Vec3*, const Vec3*);
// @ 0x00b76950
void __cdecl FUN_00b76950(Vec3* first, Vec3* last, int depth, Cmp3 comp) {
    int n = (int)((char*)last - (char*)first) / 0xc;
    for (;;) {
        if (n <= 0x1c || depth <= 0) {
            if (depth == 0) FUN_00b754d0(first, last, last, (void*)comp);
            return;
        }
        Vec3* mid = (Vec3*)((char*)first + (n / 2) * 0xc);
        Vec3* pv;
        if (comp(first, mid)) {
            if (comp(mid, last - 1)) pv = mid;
            else if (comp(first, last - 1)) pv = last - 1;
            else pv = first;
        } else {
            if (comp(first, last - 1)) pv = first;
            else if (comp(mid, last - 1)) pv = last - 1;
            else pv = mid;
        }
        Vec3 pivot = *pv;
        Vec3* cut = FUN_00b75f70(first, last, pivot, comp);
        --depth;
        FUN_00b76950(cut, last, depth, comp);
        last = cut;
        n = (int)((char*)cut - (char*)first) / 0xc;
    }
}

// ============================================================ 0xb76a60
// pointer-element Quicksort with a by-value pivot; small ranges finish with
// the heap-selection pass FUN_00b76020.
// @ 0x00b76a60
void __cdecl FUN_00b76a60(void** first, void** last, int depth, Vec3 p) {
    int n = (int)((char*)last - (char*)first);
    if ((n & ~3) > 0x70) {
        do {
            if (depth <= 0) break;
            void** mid = first + n / 8;
            void** pv = (void**)FUN_00b734e0(first, mid, last - 1, p, p);
            void** cut = (void**)FUN_00b75620(first, last, *pv);
            --depth;
            FUN_00b76a60(cut, last, depth, p);
            last = cut;
            n = (int)((char*)last - (char*)first);
        } while ((n & ~3) > 0x70);
    }
    if (depth == 0) FUN_00b76020(first, last, last, p);
}

// ============================================================ 0xb76b80
// direction from a to b, projected into the planet model frame and pushed as a
// back-transformed point onto the caller's vector.
// @ 0x00b76b80
void __cdecl FUN_00b76b80(const Vec3* a, const Vec3* b, void* vec, void* xf) {
    Vec3 d;
    d.x = b->x - a->x;
    d.y = b->y - a->y;
    d.z = b->z - a->z;
    float len = (d.y * d.y + (d.x * d.x + d.z * d.z)) + 1e-08f;
    float inv = 1.0f / sqrtf(len);
    Vec3 dir;
    dir.x = inv * d.x;
    dir.y = inv * d.y;
    dir.z = inv * d.z;
    C82060* pm = (C82060*)FUN_00b3d350();
    pm->Run(&d, a, &dir);
    if (d.x != g_1687ad4 || d.y != g_1687ad8 || d.z != g_1687adc) {
        ((CXForm*)xf)->BackTransform(&d);
        CVec3v* v = (CVec3v*)vec;
        void** e = v->end;
        if (e < v->cap) {
            v->end = e + 3;
        } else {
            v->DoInsertValue(e, &d);
        }
        float* last3 = (float*)((char*)v->end - 0xc);
        float dot = (d.y * g_16880e4 + d.z * g_16880e8) + d.x * g_16880e0;
        last3[0] = d.x - dot * g_16880e0;
        last3[1] = d.y - dot * g_16880e4;
        last3[2] = d.z - dot * g_16880e8;
    }
}

// ============================================================ 0xb76d20
// push a point onto the Sim high-LOD vertex vector (self+0x4908) unless the
// point is the global "invalid" marker or already present.
struct C76d20 {
    void __thiscall Push(float* p, float a3, int a4, char a5, char a6);
};
// @ 0x00b76d20
void __fastcall FUN_00b76d20(char* self, int, float* p, float a3, int a4, char a5, char a6) {
    if (p[0] == g_1687ad4 && p[1] == g_1687ad8 && p[2] == g_1687adc) return;
    char* vv = self + 0x4908;
    if (FUN_00b749c0(*(void**)(self + 0x4908), *(void**)(self + 0x490c), p[0], p[1], p[2])
            != *(void**)(self + 0x490c))
        return;
    if (a6) a3 = *(float*)(self + 0x54a4);
    El18 local;
    local.a = p[0];
    local.b = p[1];
    local.c = p[2];
    local.d = a3;
    local.e = a5;
    local.f = a4;
    ((C76530*)vv)->Push(local);
}

// ============================================================ 0xb76e00
// walk every node of the hashtable at self+0x49e4, notify it and store it into
// the map at self+0x49e0, then free the table.
// @ 0x00b76e00
void __fastcall FUN_00b76e00(char* self, int, float k1, float k2) {
    int ht = (int)(self + 0x49e0);
    int** buckets = *(int***)(self + 0x49e4);
    int nb = *(int*)(self + 0x49e8);
    int* node = *buckets;
    int** bp = buckets;
    if (!node) { ++bp; while (!*bp) ++bp; node = *bp; }
    if (node != buckets[nb]) {
        do {
            void* o = (void*)*node;
            ((C74f80*)self)->Notify(o, *(float*)((char*)node + 4), k2);
            int local = *(int*)((char*)o + 0x24);
            RefVal** p = FUN_00b76460((MR*)ht, 0, (const int&)local);
            RefVal* old = (RefVal*)*p;
            if ((void*)o != (void*)old) {
                ((RefVal*)o)->AddRef();
                *p = (RefVal*)o;
                if (old) old->Release();
            }
            node = *(int**)((char*)node + 8);
            if (!node) { ++bp; while (!*bp) ++bp; node = *bp; }
        } while (node != buckets[nb]);
    }
    ((C75c00*)ht)->DoFreeNodes(buckets, nb);
    *(int*)(self + 0x49ec) = 0;
}

// ============================================================ 0xb76160
// SP::cSPSimPlanetHighLOD::InitForPlanet - scan the Sim high-LOD object list
// and (re)create the model for each entry that resolves to the wanted noun.
struct VObj24 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool Slot24(unsigned key, void* out);
};
struct PropId {
    char pad0[0x12];
    unsigned short kind;                                 // +0x12
    char pad1[2];
    unsigned* GetUInt();                                 // 0x41ea00
};
struct CGonzago {
    virtual void g00(); virtual void g04(); virtual void g08();
    virtual int  g0c(int a, int b, int c);
};
struct CSink4c {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48();
    virtual void s4c(void* a, void* b);
};
// @ 0x00b76160
void __fastcall FUN_00b76160(char* self) {
    int n = (*(int*)(self + 0x55ac) - *(int*)(self + 0x55a8)) >> 2;
    for (int i = 0; i < n; ++i) {
        int e = ((int*)*(int*)(self + 0x55a8))[i];
        if (!e) continue;
        int comp = *(int*)(e + 0x90);
        if (!comp) continue;
        if (!((*(unsigned*)(e + 4) >> 0xf) & 1)) continue;
        int local40 = 0;
        if (!((VObj24*)comp)->Slot24(0x4ce873a, &local40)) continue;
        if (*(unsigned short*)(local40 + 0x12) != 0xa) continue;
        if (*((PropId*)local40)->GetUInt() != 0x153f84a3) continue;

        int* piVar3 = (int*)(comp + 8);
        int s28 = piVar3[0], s24 = piVar3[1], s20 = piVar3[2];
        int ai30[2];
        ((C74860*)(self + 0x56c0))->Find(ai30, piVar3);
        if (ai30[0] == *(int*)(*(int*)(self + 0x56c4) + *(int*)(self + 0x56c8) * 4)) {
            if (((CRandomGlob*)&g_1601760)->RandomDoubleUniform() <= (double)g_1464fdc) {
                FUN_0102c7f0(&s28, 0);
            } else {
                void* sm = FUN_00b3d2a0();
                void* emp = ((CStarManager*)sm)->GetUFO();
                int* key = ((CEmpire*)emp)->GetUFOKey();
                s28 = key[0]; s24 = key[1]; s20 = key[2];
            }
            int* dst = ((C75890*)(self + 0x56c0))->InsertKey(piVar3);
            dst[0] = s28; dst[1] = s24; dst[2] = s20;
        } else {
            s28 = *(int*)(ai30[0] + 0xc);
            s24 = *(int*)(ai30[0] + 0x10);
            s20 = *(int*)(ai30[0] + 0x14);
        }
        if (s28 != piVar3[0] || s24 != piVar3[1] || s20 != piVar3[2]) {
            CSink4c* obj = (CSink4c*)FUN_00401010();
            unsigned param[2];
            param[0] = 0x2ea8fb98;
            param[1] = 0x40000;
            obj->s4c(&s28, param);
            CGonzago* gw = (CGonzago*)FUN_00b3d520();
            int created = gw->g0c(ai30[0], s28, 4);
            if (created) {
                ++*(int*)(created + 0x40);
                *(unsigned*)(e + 4) &= ~1u;
                unsigned char flag = 0;
                FUN_00407190(*(void**)(e + 0x90), 0x3eb2e21, &flag);
                ((C537dc0*)(created + 8))->Assign((void*)(e + 8));
                ((C72520*)(created + 8))->Rotate(0.0f, g_14650a4, 0.0f);
                ((C478db0*)&((int*)*(int*)(self + 0x55a8))[i])->Assign((void*)created);
                int* sub = (int*)*(int*)(created + 0x90);
                Var v;
                Var* vp = ((C5dd750*)&v)->SetBool(&flag);
                ((CSubObj*)sub)->v14(0x3eb2e21, vp);
                if (v.mFlags & 4) ((CVariant*)&v)->Destruct(false);
            }
            ((C5765e0*)&created)->Release();
        }
    }
}

// ============================================================ 0xb76750
// EA::ResourceMan key walk: build the wide string for a resource key, notify
// the sink for each table node until the sink rejects one, then notify again.
struct WStr { wchar_t* begin; wchar_t* end; wchar_t* cap; };
struct ResTable {
    uint32_t pad_0;                                          // +0x00
    void**   mpBuckets;                                      // +0x04
    uint32_t mnBucketCount;                                  // +0x08
    uint32_t mnElementCount;                                 // +0x0c
};
struct ResTableNode {
    char pad_0[0xc];                                         // +0x00
    char mKey[0xc];                                          // +0x0c (payload)
    ResTableNode* mpNext;                                    // +0x18
};
struct ResSink {
    virtual void v00(const void* t);
    virtual void v04(const void* t);
};
// @ 0x00b76750
bool __cdecl FUN_00b76750(int* sink, const char* name, ResTable* table) {
    bool result = true;
    if (table->mnElementCount == 0) return result;
    WStr s;
    if (name != 0) {
        WStr t;
        FUN_0093c5a0(&t, name, -1);
        ((C56e2d0*)&s)->Copy(&t);
        if (t.begin != 0 && (((int)((char*)t.cap - (char*)t.begin)) & 0xfffffffe) > 2)
            opdel(t.begin);
    } else {
        WStr t;
        t.begin = 0; t.end = 0; t.cap = 0;
        ((C579a90*)&t)->RangeInitialize(0);
        ((C56e2d0*)&s)->Copy(&t);
        if (t.begin != 0 && (((int)((char*)t.cap - (char*)t.begin)) & 0xfffffffe) > 2)
            opdel(t.begin);
    }
    void** buckets = table->mpBuckets;
    void** bucket = buckets;
    ResTableNode* node = (ResTableNode*)*bucket;
    if (node == 0) {
        ++bucket;
        while (*bucket == 0) ++bucket;
        node = (ResTableNode*)*bucket;
    }
    const void* text = (s.begin == s.end) ? (const void*)&g_13f6254 : (const void*)s.begin;
    ((ResSink*)sink)->v00(text);
    ResTableNode* end = (ResTableNode*)buckets[table->mnBucketCount];
    while (node != end) {
        result = result && (FUN_00ae5530(sink, 0, node->mKey, L"EA::ResourceMan::Key") != 0);
        node = node->mpNext;
        while (node == 0) { ++bucket; node = (ResTableNode*)*bucket; }
    }
    const void* text2 = (s.begin == s.end) ? (const void*)&g_13f6254 : (const void*)s.begin;
    ((ResSink*)sink)->v04(text2);
    if (s.begin != 0 && (((int)((char*)s.cap - (char*)s.begin)) & 0xfffffffe) > 2)
        opdel(s.begin);
    return result;
}
