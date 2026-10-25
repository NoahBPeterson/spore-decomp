// Slice s00acc140: SP::cCityVisualizer helpers + vector copy/erase utilities.
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar;

static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }

// ---------------------------------------------------------------- types
struct Vec3 { float x, y, z; };

struct Key3 { int a, b, c; };
struct KeyVec {                         // vector header passed to LoadSelector
    Key3* mpBegin;                      // +0x00
    Key3* mpEnd;                        // +0x04
    Key3* mpCap;                        // +0x08
    void reserve(int n);                // 0x0041e4d0
    void pushSlow(void* end, void* value); // 0x004e3e10
};

struct RareEntry {                      // 0x2c record appended to planet+0x134
    uint          mUnk00;               // +0x00 (not written by sGetClosestRare)
    Vec3          mPos;                 // +0x04
    unsigned short mUnk10;              // +0x10 (not written)
    uchar         mUnk12;               // +0x12 (not written)
    uchar         mUnk13;               // +0x13
    uint          mUnk14;               // +0x14 (not written)
    int           mZero18;              // +0x18
    Vec3          mOther;               // +0x1c
    uchar         mKind28;              // +0x28
    uchar         mPad29[3];
};

struct Planet {
    uchar      mPad00[0xd0];            // +0x000
    Key3*      mpKeyBegin;              // +0x0d0
    Key3*      mpKeyEnd;                // +0x0d4
    uchar      mPadD8[0x5c];            // +0x0d8
    RareEntry* mpRareBegin;             // +0x134
    RareEntry* mpRareEnd;               // +0x138
    RareEntry* mpRareCap;               // +0x13c
};

struct LivingUniverse {
    uchar  mPad00[0x13c];               // +0x000
    Planet* mpPlanet;                   // +0x13c
};

struct StageRec {                       // 0x0c record in a sorted map node
    int   mPad0;                        // +0x00
    uchar mActive;                      // +0x04
    uchar mPad5[3];
    void* mpStage;                      // +0x08
};

struct MapNode {                        // 0x20 sorted key node at this+0x88
    int        mKey;                    // +0x00
    uchar      mPad04[4];               // +0x04
    uchar      mFlag8;                  // +0x08
    uchar      mFlag9;                  // +0x09
    uchar      mPad0a[2];
    StageRec*  mpRecordsBegin;          // +0x0c
    StageRec*  mpRecordsEnd;            // +0x10
    StageRec*  mpRecordsCap;            // +0x14
    uchar      mPad18[8];               // +0x18
};

struct StageGroup {                     // list of stage objects under one hash node
    uchar  mPad00[0x40];                // +0x00
    void** mpStagesBegin;               // +0x40
    void** mpStagesEnd;                 // +0x44
};

struct HashNode {                       // 0x6c bucket-chain node at this+0xc4
    uchar       mPad00[0x54];           // +0x00
    void**      mpBegin;                // +0x54
    void**      mpEnd;                  // +0x58
    void**      mpCap;                  // +0x5c
    uchar       mPad60[8];              // +0x60
    HashNode*   mpNext;                 // +0x68
};

struct StageList {                      // 0x18 block in the vector at this+0xa8
    void*   mpOwner;                    // +0x00
    void**  mpBegin;                    // +0x04
    void**  mpEnd;                      // +0x08
    void**  mpCap;                      // +0x0c
    uchar   mPad10[8];                  // +0x10
};

struct PtrVecHdr {                      // begin/end/cap triple
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCap;                       // +0x08
};

struct CountMap {
    uchar mOpaque[4];                   // map at this+0xe0; only its address is used
    int*  slot(int* key);               // 0x007c3a90
    void  erase(int* key);              // 0x00a460d0
};
struct StageTemp {                      // 0x74 temporary built by 0x00ac9850
    void* mpAllocated;                  // +0x00
    uint  mRest[0x1c];                  // +0x04
    void  ctor();                       // 0x00ac9850
};

typedef void  (__thiscall *VoidFn)(void*);
typedef void* (__thiscall *PtrFn)(void*);
typedef int   (__thiscall *IntFn)(void*);
typedef void  (__thiscall *Void1Fn)(void*, void*);
typedef void* (__thiscall *PtrIntFn)(void*, int);
typedef void  (__thiscall *VoidIntFn)(void*, int);
typedef void  (__thiscall *VoidFloatFn)(void*, float);
typedef void  (__thiscall *Void2Fn)(void*, void*, void*);
typedef void  (__thiscall *Void2IntFn)(void*, void*, int);

static int   objType(void* o)                 { return ((IntFn)vc(o, 0x20))(o); }
static void  objAddRef(void* o)               { ((VoidFn)vc(o, 0x00))(o); }
static void  objRelease(void* o)              { ((VoidFn)vc(o, 0x04))(o); }
static void* objFind(void* o, int id)         { return ((PtrIntFn)vc(o, 0x0c))(o, id); }
static void  vcall0(void* o, int slot)        { ((VoidFn)vc(o, slot))(o); }
static void* vcall0p(void* o, int slot)       { return ((PtrFn)vc(o, slot))(o); }
static void  vcall1(void* o, int slot, void* a) { ((Void1Fn)vc(o, slot))(o, a); }
static void  vcall2(void* o, int slot, void* a, void* b) { ((Void2Fn)vc(o, slot))(o, a, b); }
static void  vcall2i(void* o, int slot, void* a, int b)  { ((Void2IntFn)vc(o, slot))(o, a, b); }
static void  vcalli(void* o, int slot, int a) { ((VoidIntFn)vc(o, slot))(o, a); }
static void  vcallf(void* o, int slot, float a) { ((VoidFloatFn)vc(o, slot))(o, a); }

void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);
void  __cdecl operator_delete(void*);
void  __cdecl FUN_00ac97f0(void* a, void* b, void* c);
void  __cdecl FUN_00ac89a0(void* a, void* b, void* c);
void* __cdecl FUN_00ac95a0(void* a, void* b, void* c);
void  __cdecl FUN_00ac94c0(void* a, void* b, void* c, void* d, void* e);
void* __cdecl FUN_00ac89e0(void* a, void* b, void* c);
MapNode* __cdecl FUN_00aca1f0(MapNode* begin, MapNode* end, int* key, int mode);
void* __cdecl FUN_00b33f40();
void* __cdecl FUN_00b3d260();
void* __cdecl FUN_00b3d310();
void* __cdecl FUN_00b5b800();
void* __cdecl FUN_01021260();

// Retail callees that take their object in ECX.  MSVC rejects __thiscall on
// free functions, so each one is a declared-only member of a small stub type.
struct CStage {
    uchar mPad00[0x24];               // +0x000 (vtable pointer and unknown fields)
    int   mKey24;                     // +0x024
    uchar mPad28[0x49];               // +0x028..+0x070
    uchar mFlag71;                    // +0x071
    uchar mPad72[3];                  // +0x072..+0x074
    uchar mFlag75;                    // +0x075
    uchar mPad76[0x4a];               // +0x076..+0x0bf
    uchar mSubC0[4];                  // +0x0c0 subobject with its own vtable
    uchar mPadC4[0xa90];              // +0x0c4..+0xb53
    void* mpFieldB54;                 // +0xb54
    uchar mPadB58[0x2fc];             // +0xb58..+0xe53
    uint  mCountE54;                  // +0xe54

    char  canDo();                    // 0x00c0c0e0
    void* getFrame();                 // 0x00c0bc00
    char  hasA();                     // 0x00c232b0
    char  hasB();                     // 0x00c232c0
    void* getHerd();                  // 0x00c04590
    void  setHerd(void* p);           // 0x00c045a0
};
struct Herd {
    uchar mPad00[0x40];               // +0x00
    int*  mpVecBegin;                 // +0x40 (vector header address)
    uchar mPad44[0x20];               // +0x44..+0x63
    uchar mFlag64;                    // +0x64
};
struct LinkObj {                      // object returned through stage vtable +0xac
    void* mpOwner;                    // +0x00
    uint  mFlags;                     // +0x04
};
struct Singleton {                    // object returned by 0x00b3d310
    uchar mPad00[0x20];               // +0x00
    int   mValue20;                   // +0x20
};
struct AllocHeader { int mSize; };    // eastl allocation header (at mem-4)
struct CUnknown48770 { void apply(void* p, int one); };   // 0x00b48770
struct CUnknownCff0  { void set(int a); };                // 0x00c0cff0
struct CUnknown2b00  { void set(int a); };                // 0x00a02b00
struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
    void   pushSlow(void** end, void** value);            // 0x00aea5d0
};
struct RareVec {
    RareEntry* mpBegin;
    RareEntry* mpEnd;
    RareEntry* mpCap;
    void grow(RareEntry* end, RareEntry* value);          // 0x00acb810
};

extern "C" void* DAT_01654c04;
extern "C" void* DAT_01654c02;

struct XC {
    void  FUN_00acbd90();
    void  FUN_01011cc0(void*);
    void  FUN_00ac97f0(void*, void*);
    void  FUN_00ac89a0(void*, void*);
    void* FUN_00ac95a0(void*);
    void  FUN_00acb680(void*, void*);
    void  FUN_00acb810(void*);
    void  FUN_00acb930(void*, int, void*);
    void  FUN_00acb7c0(void*, void*);
    void  FUN_00c232b0();
    void  FUN_00c232c0();
    int   FUN_00c0c0e0();
    void* FUN_00c0bc00();
    void  FUN_00a05270();
};

// thiscall member functions of the vector owner
struct VO {
    int* v;                        // +0x00
    uchar  mPad04[0x84];           // +0x04
    MapNode* mpMapBegin;           // +0x88
    MapNode* mpMapEnd;             // +0x8c
    uchar  mPad90[0x0c];           // +0x90
    uchar  mMapMode;               // +0x9c
    uchar  mPad9d[0x0b];           // +0x9d
    StageList* mpListsBegin;       // +0xa8
    StageList* mpListsEnd;         // +0xac
    uchar  mPadB0[0x14];           // +0xb0
    HashNode** mpBuckets;          // +0xc4
    uint   mBucketEnd;             // +0xc8
    uchar  mPadCC[0x14];           // +0xcc
    CountMap mCountMap;            // +0xe0

    void  FUN_00acc140(uchar* pos, uchar* val);
    void  FUN_00acc610(void* p);
    void  FUN_00acc700(void* p, float a, float b);
    void  FUN_00acc770();
    void  FUN_00acc9b0(uint n);
    void  FUN_00acc390();
    bool  FUN_00accf80(void* p);
    void  FUN_00acd210();
    void  FUN_00acd2d0(void* p);
    void  FUN_00acd410(void* p);
    void  FUN_00ac84f0(void* p);   // 0x00ac84f0, defined in another slice
};

// free functions
void  __stdcall FUN_00acc800(KeyVec* v);
void  FUN_00accd70(int arr, uint n);
int*  FUN_00acc2d0(int* p, int* end, int* out);
int*  FUN_00acc330(int end, int begin, int* out);
void* FUN_00accec0(uchar* p, uchar* end, uchar* out);
void* FUN_00accf20(int end, int begin, int out);
bool  FUN_00acca00(int* vec, int* val);

// @ 0x00acc2d0
int* FUN_00acc2d0(int* p, int* end, int* out) {
    if (p == end) return out;
    do {
        int* a = (int*)*p;
        int* b = (int*)*out;
        if (a != b) {
            if (a) ((void (__thiscall*)(void*))vc(a, 0))(a);
            *out = (int)a;
            if (b) ((void (__thiscall*)(void*))vc(b, 4))(b);
        }
        ((XC*)(p + 1))->FUN_01011cc0(out + 1);
        p += 6; out += 6;
    } while (p != end);
    return out;
}

// @ 0x00acc330
int* FUN_00acc330(int end, int begin, int* out) {
    if (begin == end) return out;
    int nxt;
    do {
        int* a = *(int**)(end - 0x18);
        int* b = (int*)out[-6];
        int nxt = end - 0x18;
        out -= 6;
        if (a != b) {
            if (a) ((void (__thiscall*)(void*))vc(a, 0))(a);
            *out = (int)a;
            if (b) ((void (__thiscall*)(void*))vc(b, 4))(b);
        }
        ((XC*)(end - 0x14))->FUN_01011cc0(out + 1);
        end = nxt;
    } while (nxt != begin);
    return out;
}

// @ 0x00accec0
void* FUN_00accec0(uchar* p, uchar* end, uchar* out) {
    if (p != end) {
        uchar* o = out;
        do {
            *(int*)o = *(int*)p;
            *(o + 8) = *(p + 8);
            *(o + 9) = *(p + 9);
            ((XC*)(o + 0xc))->FUN_00acbd90();
            p += 0x20; o += 0x20;
        } while (p != end);
        return o;
    }
    return out;
}

// @ 0x00accf20
void* FUN_00accf20(int end, int begin, int out) {
    if (end != begin) {
        uchar* s = (uchar*)(end + 9);
        uchar* d = (uchar*)(out + 9);
        do {
            *(int*)(out - 0x20) = *(int*)(end - 0x20);
            end -= 0x20; out -= 0x20;
            d[-0x21] = s[-0x21];
            d[-0x20] = s[-0x20];
            ((XC*)(d - 0x1d))->FUN_00acbd90();
            s -= 0x20; d -= 0x20;
        } while (end != begin);
        return d;
    }
    return (void*)out;
}

// @ 0x00acca00
bool FUN_00acca00(int* vec, int* val) {
    int* p = (int*)*vec;
    int* end = (int*)vec[1];
    if (p != end) {
        do {
            if (*p == *val) {
                if (p + 1 < end) {
                    // shift left
                    int* d = p;
                    int* s = p + 1;
                    for (; s < end; s++, d++) *d = *s;
                }
                vec[1] -= 4;
                int* last = (int*)vec[1];
                if (*last) ((void (__thiscall*)(void*))vc((void*)*last, 4))((void*)*last);
                return 1;
            }
            p++;
        } while (p != end);
    }
    return 0;
}

// @ 0x00acc140
void VO::FUN_00acc140(uchar* pos, uchar* val) {
    int* p = (int*)this;
    uchar* cur = (uchar*)p[1];
    if (cur != (uchar*)p[2]) {
        if (pos <= val && val < cur) val += 0xc;
        if (cur) {
            *(void**)cur = (void*)0x145a158;
            *(cur + 4) = *(cur - 8);
            void* o = *(void**)(cur - 4);
            *(void**)(cur + 8) = o;
            if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
        }
        FUN_00ac97f0(pos, (void*)(p[1] - 0xc), (void*)p[1]);
        *(pos + 4) = *(val + 4);
        void* a = *(void**)(val + 8);
        void* b = *(void**)(pos + 8);
        if (a != b) {
            if (a) ((void (__thiscall*)(void*))vc(a, 0))(a);
            *(void**)(pos + 8) = a;
            if (b) ((void (__thiscall*)(void*))vc(b, 4))(b);
        }
        p[1] += 0xc;
        return;
    }
    int n = (int)(cur - (uchar*)p[0]) / 0xc;
    int cap = n ? n * 2 : 1;
    uchar* mem = cap ? (uchar*)operator_new(cap * 0xc, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    int old = p[0];
    void* e1 = FUN_00ac95a0((void*)old, pos, mem);
    FUN_00ac89a0((void*)old, pos, mem);
    if (e1) {
        *(void**)e1 = (void*)0x145a158;
        *(uchar*)((uchar*)e1 + 4) = *(uchar*)(val + 4);
        void* o = *(void**)(val + 8);
        *(void**)((uchar*)e1 + 8) = o;
        if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
    }
    int oldend = p[1];
    void* e2 = FUN_00ac95a0(pos, (void*)oldend, (uchar*)e1 + 0xc);
    FUN_00ac89a0(pos, (void*)oldend, (uchar*)e1 + 0xc);
    if (old && *(int*)(old - 4) != 0) operator_delete((void*)old);
    p[1] = (int)e2;
    p[0] = (int)mem;
    p[2] = (int)(mem + cap * 0xc);
}

// @ 0x00acc610  (remove from vector of 0x18 blocks)
void VO::FUN_00acc610(void* p) {
    if (!p) return;
    if (objType(p) != 0x18eb4b7) return;
    int n = (int)(mpListsEnd - mpListsBegin);
    if (n <= 0) return;

    StageList* b = mpListsBegin;
    for (int i = 0; i < n; i++, b++) {
        void** a = b->mpBegin;
        void** e = b->mpEnd;
        while (a != e && *a != p) a++;
        if (a == e) continue;

        // remove every occurrence of p; the tail is then released
        void** out = a;
        for (void** s = a + 1; s != e; s++) {
            if (*s != p) {
                *out = *s;
                out++;
            }
        }
        for (void** s = out; s != e; s++)
            if (*s) objRelease(*s);
        b->mpEnd = out;
        vcall2i(b->mpOwner, 0x9c, p, 1);
        return;
    }
}

// @ 0x00acc700
void VO::FUN_00acc700(void* p, float a, float b) {
    int* v = (int*)this;
    uchar* cur = (uchar*)v[9];
    if (cur < (uchar*)v[10]) {
        v[9] = (int)(cur + 0x14);
    } else {
        uchar local[0x14];
        ((XC*)(v + 8))->FUN_00acb680(cur, local);
    }
    uchar* e = (uchar*)(*(int*)((uchar*)this + 0x24) - 0x14);
    *(int*)e = *(int*)p;
    *(int*)(e + 4) = *(int*)((uchar*)p + 4);
    *(int*)(e + 8) = *(int*)((uchar*)p + 8);
    *(float*)(e + 0xc) = a * a;
    *(float*)(e + 0x10) = b * b;
}

// @ 0x00acc770
void VO::FUN_00acc770() {
    uchar* p = (uchar*)this;
    int n = (*(int*)(p + 0x11c) - *(int*)(p + 0x118)) >> 2;
    for (int i = 0; i < n; i++) {
        int* o = (int*)FUN_00b33f40();
        ((void (__thiscall*)(void*, int))vc(o, 0x3c))(o, *(int*)(*(int*)(p + 0x118) + i * 4));
    }
    int b = *(int*)(p + 0x118);
    int e = *(int*)(p + 0x11c);
    int* it = (int*)FUN_00ac89e0((void*)e, (void*)e, (void*)b);
    int* end = *(int**)(p + 0x11c);
    for (; it < end; it++) if (*it) ((XC*)*it)->FUN_00a05270();
    *(int*)(p + 0x11c) -= (e - b) >> 2 << 2;
}

// @ 0x00acc800  (LoadSelector)
void __stdcall FUN_00acc800(KeyVec* v) {
    LivingUniverse* lu = (LivingUniverse*)FUN_01021260();
    if (!lu) return;

    Planet* planet = lu->mpPlanet;
    int n = (int)(planet->mpKeyEnd - planet->mpKeyBegin);
    void* mode = FUN_00b5b800();
    if (mode == DAT_01654c04) n = 5;

    v->reserve((int)(v->mpEnd - v->mpBegin) + n);
    if (n <= 0) return;

    Key3* src = planet->mpKeyBegin;
    for (int i = 0; i < n; i++, src++) {
        if (v->mpEnd < v->mpCap)
            *v->mpEnd++ = *src;
        else
            v->pushSlow(v->mpEnd, src);
    }
}

// @ 0x00acc9b0
void VO::FUN_00acc9b0(uint n) {
    int* v = (int*)this;
    int* b = (int*)v[0];
    int* e = (int*)v[1];
    if ((uint)(e - b) < n) {
        int add = n - (int)(e - b);
        int z = 0;
        ((XC*)v)->FUN_00acb930(e, add, &z);
        return;
    }
    ((XC*)v)->FUN_00acb7c0(b + n, e);
}

// @ 0x00accf80  (SetupCultureStages)
bool VO::FUN_00accf80(void* p) {
    if (!p) return false;

    int key = objType(p);
    MapNode* found = FUN_00aca1f0(mpMapBegin, mpMapEnd, &key, mMapMode);
    MapNode* node = mpMapEnd;
    if (found != mpMapEnd && found->mKey <= key) node = found;
    if (node == mpMapEnd) return false;

    int n = (int)(node->mpRecordsEnd - node->mpRecordsBegin);
    if (n <= 0) return false;

    StageRec* rec = node->mpRecordsBegin;
    for (int i = 0; i < n; i++, rec++) {
        if (rec->mpStage != p) continue;

        rec->mActive = 0;

        if (node->mFlag9) {
            void* child = p ? objFind(p, 0x11c0ba3) : 0;
            vcall0(child, 0x34);
            void* bm = FUN_00b3d260();
            vcall1(bm, 0x3c, child);
        }

        if (node->mFlag8) {
            void* child = objFind(p, 0x116dd1b);
            if (child) {
                ((CStage*)child)->mFlag71 = 1;
                ((CStage*)child)->mFlag75 = 0;
                vcall1(child, 0x38, (void*)0x167a390);

                StageTemp temp;
                temp.ctor();
                vcall1(child, 0xdc, &temp);
                void* mem = temp.mpAllocated;
                if (mem && ((AllocHeader*)mem)[-1].mSize != 0)
                    operator_delete(mem);

                void* q = ((PtrIntFn)vc(child, 0xb8))(child, 0xce9f6639);
                if (q)
                    ((CUnknownCff0*)q)->set(0);
                else
                    vcallf(child, 0xc4, 0.0f);

                vcall0(child, 0xf4);

                void* r = vcall0p(child, 0xac);
                if (r) {
                    LinkObj* link = (LinkObj*)r;
                    link->mFlags &= 0xfffffffeu;
                    vcall2(link->mpOwner, 0x16c, r, (void*)0);
                }

                void* s = FUN_00b3d310();
                if (((Singleton*)s)->mValue20 == 1) {
                    void* s2 = FUN_00b3d310();
                    ((CUnknown48770*)s2)->apply(p, 1);
                }
            }
        }

        if (p) {
            void* q = objFind(p, 0xce9f6639);
            if (q) {
                vcall0(q, 0xc4);
                Herd* h = (Herd*)((CStage*)q)->mpFieldB54;
                if (h) {
                    h->mFlag64 = 0;
                    ((CUnknown2b00*)h)->set(1);
                }
                ++((CStage*)q)->mCountE54;
            }

            if (objType(p) == 0x18eb45e) {
                objAddRef(p);
                Herd* herd = (Herd*)((CStage*)p)->getHerd();
                if (herd) {
                    objAddRef(herd);
                    FUN_00acca00((int*)&herd->mpVecBegin, (int*)&p);
                    ((CStage*)p)->setHerd(0);
                    objRelease(herd);
                }
                objRelease(p);
            }
        }
        return true;
    }
    return false;
}

// @ 0x00acd210
void VO::FUN_00acd210() {
    int key = 0x18eb4b7;
    MapNode* found = FUN_00aca1f0(mpMapBegin, mpMapEnd, &key, mMapMode);
    MapNode* node = mpMapEnd;
    if (found != mpMapEnd && found->mKey <= key) node = found;
    if (node == mpMapEnd) return;

    int n = (int)(node->mpRecordsEnd - node->mpRecordsBegin);
    if (n <= 0) return;

    StageRec* rec = node->mpRecordsBegin;
    for (int i = 0; i < n; i++, rec++) {
        void* stage = rec->mpStage;
        void* q = stage ? objFind(stage, 0x4f176642) : 0;
        if (((CStage*)q)->hasA())
            FUN_00accf80(stage);
    }
}

// @ 0x00acd2d0  (property-change handler)
void VO::FUN_00acd2d0(void* p) {
    switch (objType(p)) {
    case 0x18eb45e: {
        int key = ((CStage*)p)->mKey24;
        int* slot = mCountMap.slot(&key);
        ++*slot;
        return;
    }
    case 0x18eb4b7:
        if (((CStage*)p)->hasA()) {
            FUN_00ac84f0(p);
            return;
        }
        if (!((CStage*)p)->hasB()) return;

        {
            int n = (int)(mpListsEnd - mpListsBegin);
            for (int i = 0; i < n; i++) {
                StageList* b = mpListsBegin + i;
                PtrVecHdr* vec = (PtrVecHdr*)vcall0p(b->mpOwner, 0x90);
                void** a = vec->mpBegin;
                void** e = vec->mpEnd;
                while (a != e && *a != p) a++;
                if (a == e) continue;

                void* tmp = p;
                objAddRef(p);
                if (b->mpEnd < b->mpCap) {
                    *b->mpEnd++ = p;
                    objAddRef(p);
                } else {
                    ((PtrVec*)&b->mpBegin)->pushSlow(b->mpEnd, &tmp);
                }
                if (tmp) objRelease(tmp);
                return;
            }
        }
        return;
    default:
        return;
    }
}

// @ 0x00acd410  (property-change handler dispatch)
void VO::FUN_00acd410(void* p) {
    switch (objType(p)) {
    case 0x18eb45e: {
        int key = ((CStage*)p)->mKey24;
        mCountMap.erase(&key);
        break;
    }
    case 0x18eb4b7:
        if (((CStage*)p)->hasA()) {
            FUN_00ac84f0(p);
            FUN_00accf80(p);
            return;
        }
        if (((CStage*)p)->hasB()) {
            FUN_00acc610(p);
            FUN_00accf80(p);
            return;
        }
        break;
    default:
        break;
    }
    FUN_00accf80(p);
}

// @ 0x00acc390  (sGetClosestRare)
void VO::FUN_00acc390() {
    LivingUniverse* lu = (LivingUniverse*)FUN_01021260();
    Planet* planet = lu->mpPlanet;

    // Stable compaction: drop entries whose +0x28 byte has bit 2 set.
    uint kept = 0;
    while (kept < (uint)(planet->mpRareEnd - planet->mpRareBegin)) {
        RareEntry* cur = planet->mpRareBegin + kept;
        if ((cur->mKind28 & 4) == 0) {
            kept++;
        } else {
            *cur = *(planet->mpRareEnd - 1);
            planet->mpRareEnd--;
        }
    }

    HashNode** slot = mpBuckets;
    HashNode* node = *slot;
    if (!node) {
        do {
            slot++;
            node = *slot;
        } while (!node);
    }
    HashNode* stop = mpBuckets[mBucketEnd];

    while (node != stop) {
        int n = (int)(node->mpEnd - node->mpBegin);
        for (int i = 0; i < n; i++) {
            StageGroup* g = (StageGroup*)node->mpBegin[i];
            for (void** it = g->mpStagesBegin; it != g->mpStagesEnd; it++) {
                void* stage = *it;
                if (!stage || !((CStage*)stage)->canDo()) continue;

                Vec3* a = (Vec3*)vcall0p(&((CStage*)stage)->mSubC0, 0x2c);
                Vec3* b = (Vec3*)((CStage*)stage)->getFrame();

                RareEntry e;
                e.mPos = *a;
                e.mZero18 = 0;
                e.mOther = *b;
                e.mKind28 = 0x24;

                if (planet->mpRareEnd < planet->mpRareCap)
                    *planet->mpRareEnd++ = e;
                else
                    ((RareVec*)&planet->mpRareBegin)->grow(planet->mpRareEnd, &e);
            }
        }

        node = node->mpNext;
        while (!node) {
            slot++;
            node = *slot;
        }
    }
}

// @ 0x00accd70
void FUN_00accd70(int arr, uint n) {
    for (uint i = 0; i < n; i++) {
        int node = *(int*)(arr + i * 4);
        while (node != 0) {
            int next = *(int*)(node + 0x68);
            *(void**)(node + 4) = (void*)0x145a184;
            int* e = *(int**)(node + 0x58);
            for (int* it = *(int**)(node + 0x54); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            int b = *(int*)(node + 0x54);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            e = *(int**)(node + 0x44);
            for (int* it = *(int**)(node + 0x40); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            b = *(int*)(node + 0x40);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            e = *(int**)(node + 0x30);
            for (int* it = *(int**)(node + 0x2c); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            b = *(int*)(node + 0x2c);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            e = *(int**)(node + 0x1c);
            for (int* it = *(int**)(node + 0x18); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            b = *(int*)(node + 0x18);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            operator_delete((void*)node);
            node = next;
        }
        *(int*)(arr + i * 4) = 0;
    }
}
// --- equivalence checker address annotations
    void operator_delete(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
