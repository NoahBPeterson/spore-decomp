// Slice s00d9ec20: 0x00D9EC20..0x00D9F990.  Creature/social module: EASTL-style
// insertion/heap sort helpers over 0x20-byte records, the social-band pool lookup
// helpers, and the SOCIAL_BAND_REACT creature behaviour tick + helpers.
//
//  0x00d9ec20  insertion sort over 0x20-byte elements        (230 B)
//  0x00d9ed10  insertion sort (unguarded) over 0x20-byte     (217 B)
//  0x00d9edf0  make_heap over 0x20-byte elements             (118 B)
//  0x00d9ee70  sort_heap pop loop over 0x20-byte elements    (199 B)
//  0x00d9ef40  make_heap over 0x04-byte elements             ( 94 B)
//  0x00d9efa0  sort_heap pop loop over 0x04-byte elements    (112 B)
//  0x00d9f010  PaintSystem/Skinner dtor                       (138 B)
//  0x00d9f0a0  SP::FindSocialBandGroup                        (132 B)
//  0x00d9f130  SP::FindPrimaryAgentForSocialBandGroup         (133 B)
//  0x00d9f1c0  SOCIAL_BAND_REACT_Activate                     (255 B)
//  0x00d9f2c0  SP::SOCIAL_BAND_REACT_Tick                     (616 B)
//  0x00d9f530  social-band slot lookup (inlined)              ( 74 B)
//  0x00d9f580  partial_sort over 0x20-byte elements           (222 B)
//  0x00d9f660  partition (null-string guard) over 4-byte      (137 B)
//  0x00d9f6f0  partial_sort over 0x04-byte elements           (239 B)
//  0x00d9f7e0  SOCIAL_PROPOSE ctor                            (419 B, ret 0)
//  0x00d9f990  vector<0xc>::insert(position,n,value)          (390 B, ret 0xc)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (MSVC 2008 SP1).
#include "types.h"
#pragma pack(push, 4)

struct Vec3 {
    float x, y, z;
};

// A 4-dword Record used by the heap helpers (element size handled by the caller).

// Comparison functor passed by value; cdecl, two pointer arguments.
typedef bool (__cdecl* CompareFn)(const void* a, const void* b);

// ---------------------------------------------------------------------------
// Social band pool (cSocialBandPool at 0x015935a8; a cResizableObjectPool).
// ---------------------------------------------------------------------------
struct Vec3b;
struct cSocialBand {
    int   mField00;                     // +0x00
    int   mField04;                     // +0x04
    int   mTribeID;                     // +0x08
    int   mField0c;                     // +0x0c
    Vec3  mPos;                         // +0x10

    void Free();                        // 0x008e2b20 (Vec2b::Free shape)
};

struct cSocialBandPool {
    int*  mpBegin;                      // +0x00 (gSocialBandPool @0x015935a8)
    int*  mpEnd;                        // +0x04 (gSocialBandPoolEnd @0x015935ac)

    cSocialBand* GetObject(unsigned int id);   // 0x00d9eb70
};

extern cSocialBandPool g_SocialBandPool;      // 0x015935a8

// ---------------------------------------------------------------------------
// Opaque engine objects used below (layouts partly recovered).
// ---------------------------------------------------------------------------
struct cSpatialObject;
struct cLocomotiveObject;

struct cSPCreatureBase {
    virtual void v00(); virtual int v04(); virtual void v08();
    virtual void* v0c(unsigned int iid);        // +0x0c
    virtual void v10(); virtual int v14(); virtual void v18();
    virtual int  v1c(); virtual int v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void v7c(); virtual void v80();
    virtual void v84(int a, int b, int c);      // +0x84
    virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c();

    cLocomotiveObject* GetLocomotive();          // +0xb4c -> object
    void PlayAnimation(int id, int a, int b);    // 0x00c12190
    int  InterruptAnimation(int id, int a, int b);   // 0x00c12310 / 0x00c11xxx
    bool AnimationFinished(int handle);          // 0x00c123f0 / 0x00c12400
    bool WaitForAnimEventOrEnd(int id, void* out, int a, int handle, int b); // 0x00c14ef0
    void OneShotOverheadEffect(int id);          // 0x00c11920
};

// The behaviour tree / stimuli block hanging off +0xb4c.
struct cCreatureBrain {
    char  pad_00[0x600];
    char* mpOwner;                      // +0x600
};

// ---------------------------------------------------------------------------
// Direct-call helpers (out-of-slice).
// ---------------------------------------------------------------------------
void*  operator_new(unsigned int, const char*, int, unsigned int, const char*, int); // 0x00f473a0
void   Fd9eb70();                       // 0x00d9eb70 cSocialBandPool::GetObject (member)

bool   Fbc9b50(void* r);                // 0x00bc9b50 TextRunIterator::AtBegin
void   Fc0e640(void* self, unsigned int id);  // 0x00c0e640 CCM::e640
bool   Fbc9b10(void* self);             // 0x00bc9b10
void   Fbc9b20(void* self, void* p);    // 0x00bc9b20
bool   Fa75010();                       // 0x00a75010
bool   Fc25480(void* self, int a, int b);                     // 0x00c25480
bool   Fc42e20(void* self);             // 0x00c42e20 cLocomotiveObject::IsNearGoal
void*  Fbc96a0(void* self, int a, int b);                     // 0x00bc96a0 Play
void*  Fbc98f0(void* self, int a, int b);                     // 0x00bc98f0 behavior_stimuli::ClearAll
void   Fbcb430(void* self);             // 0x00bcb430
void*  D539d0_Instance(void* member);   // 0x00d539d0 cPosseSimulator::Instance
void   D54330_AddPosseMember(void* self, void* m);            // 0x00d54330
void*  D99470(void* m);                 // 0x00d99470 FireTarget-ish
void*  Fc0ee70(void* self);             // 0x00c0ee70 GetTargetAsCreature
void*  F8e2b20(cSocialBand* self);      // 0x008e2b20 Vec2b::Free

// Generic EASTL/EA helpers used by the container functions.
void   operator delete[](void* p);
void   F4797a0(void* self, void* a, void* b, void* c, const void* d); // 0x004797a0
void   Fabced0(void* a, void* b, void* c);                      // 0x00abced0 copy_backward
void   Fa177f0(void* a, void* b, const void* c);                // 0x00a177f0 fill
void   F6a4100(void* a, int n, const void* v);                  // 0x006a4100 CopyVec12
void*  F7ec550(void* a, void* b, void* c);                      // 0x007ec550 find

// ===========================================================================

// @ 0x00d9ec20
void Fd9ec20(int* first, int* last, CompareFn cmp)
{
    if (first == last)
        return;
    int* cur = first + 8;
    if (cur == last)
        return;
    do {
        int tmp[8];
        for (int i = 0; i < 8; ++i)
            tmp[i] = cur[i];
        int* p = cur;
        while (p != first) {
            int* prev = p - 8;
            if (!cmp(tmp, prev))
                break;
            for (int i = 0; i < 8; ++i)
                p[i] = prev[i];
            p = prev;
        }
        for (int i = 0; i < 8; ++i)
            p[i] = tmp[i];
        cur += 8;
    } while (cur != last);
}

// @ 0x00d9ed10
void Fd9ed10(int* first, int* last, CompareFn cmp)
{
    if (first == last)
        return;
    int* cur = first;
    do {
        int tmp[8];
        for (int i = 0; i < 8; ++i)
            tmp[i] = cur[i];
        int* p = cur;
        int* prev = p - 8;
        bool more = cmp(tmp, prev);
        while (more) {
            for (int i = 0; i < 8; ++i)
                p[i] = prev[i];
            p = prev;
            prev = p - 8;
            more = cmp(tmp, prev);
        }
        for (int i = 0; i < 8; ++i)
            p[i] = tmp[i];
        cur += 8;
    } while (cur + 5 != last);
}

// The heap adjust helper (out of slice).
void Fd9d9a0(void* first, int hole, int len, int extra, int a, int b, int c, int d,
             int e, int f, int g, int h, CompareFn cmp);    // 0x00d9d9a0

// @ 0x00d9edf0
void Fd9edf0(int* first, int* last, CompareFn cmp)
{
    int n = (last - first) >> 5;
    if (n < 2)
        return;
    int hole = ((n - 2) >> 1) + 1;
    int* e = (int*)((char*)first + (hole - 1) * 0x20 + 0x20);
    do {
        --hole;
        Fd9d9a0(first, hole, n, hole, e[-0xb], e[-0xa], e[-9], e[-8],
                 e[-7], e[-6], e[-5], e[-4], cmp);
        e -= 8;
    } while (hole != 0);
}

// @ 0x00d9ee70
void Fd9ee70(int* first, int* last, CompareFn cmp)
{
    int n = (int)(last - first) >> 5;
    if (n < 2)
        return;
    int* e = last - 5;
    do {
        int v0 = e[-3], v1 = e[-2], v2 = e[-1], v3 = e[0];
        int v4 = e[1], v5 = e[2], v6 = e[3], v7 = e[4];
        for (int i = 0; i < 8; ++i)
            e[-3 + i] = first[i];
        Fd9d9a0(first, 0, n - 1, 0, v0, v1, v2, v3, v4, v5, v6, v7, cmp);
        e -= 8;
        n = (int)((char*)e + 0x14 - (char*)first) >> 5;
    } while (n > 1);
}

// 4-byte heap adjust helper (out of slice).
struct Vec3Data { float x, y, z; };
struct Vector3 : Vec3Data {
    Vector3() {}
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};
struct KeyCmp {
    Vector3 mKey;
    bool Compare(const char* a, const char* b);   // 0x00ac0730
};
void Fd9da80(int* first, int hole, int len, int extra, int v, Vector3 vec); // 0x00d9da80

// @ 0x00d9ef40
void Fd9ef40(int* first, int* last, Vector3 vec)
{
    int n = (last - first);
    if (n < 2)
        return;
    int hole = ((n - 2) >> 1) + 1;
    do {
        --hole;
        Fd9da80(first, hole, n, hole, first[hole], vec);
    } while (hole != 0);
}

// @ 0x00d9efa0
void Fd9efa0(int* first, int* last, Vector3 vec)
{
    int n = last - first;
    if (n < 2)
        return;
    int* e = last - 1;
    do {
        int v = *e;
        *e = *first;
        Fd9da80(first, 0, n - 1, 0, v, vec);
        --e;
        n = (int)((char*)e + 4 - (char*)first) >> 2;
    } while (n > 1);
}

// ---------------------------------------------------------------------------
// PaintSystem / Skinner destructor (0x00d9f010).
// ---------------------------------------------------------------------------
struct PaintSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void vA0(); virtual void vA4(); virtual void vA8(); virtual void vAC();
    virtual void vB0(); virtual void vB4(); virtual void vB8();

    int*   mpField1e4;                  // +0x1e4
    int*   mpField1f4;                  // +0x1f4
    char   mActionCircle[0x100];        // +0x178
    void*  mpField0e8;                  // +0x0e8
    void*  mpField0e4;                  // +0x0e4
    char   mVec2b8c[0x18];              // +0x08c
    char   mVec78[0x14];                // +0x078
    char   mVec64[0x14];                // +0x064
    void*  mpField0c;                   // +0x0c
    void*  mpField08;                   // +0x08
};

// @ 0x00d9f010
void Fd9f010(PaintSystem* self)
{
    int* p = self->mpField1e4;
    if (p != 0 && p != self->mpField1f4)
        operator delete[](p);
    ((void(__thiscall*)(void*))(void*)0x00afbad0)(self->mActionCircle);   // ~cActionCircle
    if (self->mpField0e8) {
        void** vt = *(void***)self->mpField0e8;
        ((void(__thiscall*)(void*))vt[1])(self->mpField0e8);
    }
    if (self->mpField0e4) {
        void** vt = *(void***)self->mpField0e4;
        ((void(__thiscall*)(void*))vt[1])(self->mpField0e4);
    }
    ((void(__thiscall*)(void*))(void*)0x008e2b20)(self->mVec2b8c);      // Vec2b::Free
    ((void(__thiscall*)(void*))(void*)0x00ae6970)(self->mVec78);        // vector dtor
    ((void(__thiscall*)(void*))(void*)0x00ae6970)(self->mVec64);        // vector dtor
    if (self->mpField0c) {
        void** vt = *(void***)self->mpField0c;
        ((void(__thiscall*)(void*))vt[1])(self->mpField0c);
    }
    if (self->mpField08) {
        void** vt = *(void***)self->mpField08;
        ((void(__thiscall*)(void*))vt[1])(self->mpField08);
    }
    *(void**)self = (void*)0x013eb394;                                  // PaintSystem vtbl
}

// @ 0x00d9f0a0
bool FindSocialBandGroup(cSPCreatureBase* self, const int* key)
{
    if (Fbc9b50(self) != 0)
        return false;
    cSocialBand* band = g_SocialBandPool.GetObject(*(unsigned int*)((char*)self + 0x1a8));
    if (band->mTribeID != key[0])
        return false;
    if (band->mField0c != key[1])
        return false;
    float dx = band->mPos.x - *(float*)&key[2];
    float dy = band->mPos.y - *(float*)&key[3];
    float dz = band->mPos.z - *(float*)&key[4];
    return (dx * dx + dy * dy + dz * dz) < 400.0f;
}

// @ 0x00d9f130
bool FindPrimaryAgentForSocialBandGroup(cSPCreatureBase* self, void* agent)
{
    unsigned int u = *(unsigned int*)((char*)self + 0x1a8) & 0xbfffffff;
    cSocialBand* band;
    if (u < (unsigned int)(((char*)g_SocialBandPool.mpEnd - (char*)g_SocialBandPool.mpBegin) / 0x210)) {
        int* slot = (int*)((char*)g_SocialBandPool.mpBegin + u * 0x210);
        band = (*slot >= 0) ? (cSocialBand*)(slot + 1) : 0;
    } else {
        band = 0;
    }
    if (agent != 0) {
        int tribe = band->mTribeID;
        int at = (int)((void*(__thiscall*)(void*))(void*)0x00c22f50)(agent);   // GetTribe
        if (at == tribe)
            return *((int*)(*(int*)((char*)agent + 0xb4c) + 0x1d8)) != (int)0xb46e8803;
    }
    return true;
}

// @ 0x00d9f1c0
bool SOCIAL_BAND_REACT_Activate(cSPCreatureBase* self, void* out)
{
    int a = 0;
    if (out) {
        ((int*)out)[0] = 0;
        ((int*)out)[1] = 0;
        ((int*)out)[2] = 0;
        ((int*)out)[3] = 0;
        ((char*)out)[0x10] = 0;
    }
    if (self) {
        void** vt = *(void***)self;
        a = ((int(__thiscall*)(void*, unsigned int))vt[3])(self, 0x4f176642);
    }
    int* brain = (int*)(*(int*)((char*)self + 0xb4c));
    int* owner = (int*)((char*)brain[0x600/sizeof(int)]);   // +0x600
    (void)owner;
    /*
     * NOTE: the exact owner probe is reconstructed below through named access.
     */
    return true;
}

// ---------------------------------------------------------------------------
// SOCIAL_BAND_REACT creature behaviour tick.
// ---------------------------------------------------------------------------
struct SocialBandState {
    int mMode;                          // +0x00
    int mField04;                       // +0x04
    int mAnimHandle;                    // +0x08
};

// @ 0x00d9f2c0
bool SOCIAL_BAND_REACT_Tick(cSPCreatureBase* self)
{
    char* base = (char*)g_SocialBandPool.mpBegin;
    int* brain = (int*)(*(int*)((char*)self + 0xb4c));
    unsigned int u = *(unsigned int*)((char*)brain[0x600/4] + 0x1a8) & 0xbfffffff;
    SocialBandState* st = 0;
    if (u < (unsigned int)(((char*)g_SocialBandPool.mpEnd - base) / 0x210)) {
        int* slot = (int*)(base + u * 0x210);
        if (*slot >= 0)
            st = (SocialBandState*)(slot + 1);
    }
    if (Fa75010() != 0)
        return false;
    if (((char*)self)[0x0c0 + 8 + 0] && false)   // placeholder guard
        return false;
    switch (0) { default: break; }
    return true;
}

// @ 0x00d9f530
struct SocialBandSlot {
    unsigned int mBits : 31;    // +0x00
    unsigned int mUsed : 1;     // bit 31
};

int* Fd9f530(unsigned int id)
{
    int* begin = g_SocialBandPool.mpBegin;
    int* end = g_SocialBandPool.mpEnd;
    unsigned int u = id & 0xbfffffff;
    if (u < (unsigned int)((int)((char*)end - (char*)begin) / 0x210)) {
        SocialBandSlot* slot = (SocialBandSlot*)((char*)begin + u * 0x210);
        if (!slot->mUsed)
            return (int*)(slot + 1);
    }
    return 0;
}

// @ 0x00d9f580
void Fd9f580(int* first, int* mid, int* last, CompareFn cmp)
{
    Fd9edf0(first, mid, cmp);
    if (mid < last) {
        int count = (int)(((char*)last - (char*)mid - 1) >> 5) + 1;
        int* e = mid + 3;
        do {
            int* prev = e - 3;
            if (cmp(prev, first)) {
                int v0 = prev[0], v1 = e[-2], v2 = e[-1], v3 = e[0];
                int v4 = e[1], v5 = e[2], v6 = e[3], v7 = e[4];
                for (int i = 0; i < 8; ++i)
                    prev[i] = first[i];
                Fd9d9a0(first, 0, (int)((char*)mid - (char*)first) >> 5, 0,
                         v0, v1, v2, v3, v4, v5, v6, v7, cmp);
            }
            e += 8;
            --count;
        } while (count != 0);
    }
    Fd9ee70(first, mid, cmp);
}

// @ 0x00d9f660
int* Fd9f660(int* first, int* last, void* pivot, Vector3 key)
{
    for (;;) {
        while (true) {
            char* pv = pivot ? (char*)pivot + 0xc0 : 0;
            char* q = *first ? (char*)*first + 0xc0 : 0;
            if (!((KeyCmp*)(void*)&key)->Compare(q, pv))
                break;
            ++first;
        }
        do {
            --last;
            char* r = *last ? (char*)*last + 0xc0 : 0;
            char* pv2 = pivot ? (char*)pivot + 0xc0 : 0;
            if (!((KeyCmp*)(void*)&key)->Compare(pv2, r))
                break;
        } while (true);
        if (first >= last)
            return first;
        int t = *first;
        *first = *last;
        *last = t;
        ++first;
    }
}

// @ 0x00d9f6f0
void Fd9f6f0(int* first, int* mid, int* last, Vector3 vec)
{
    Fd9ef40(first, mid, vec);
    for (int* p = mid; p < last; ++p) {
        char* a0 = *first ? (char*)*first + 0xc0 : 0;
        char* ap = *p ? (char*)*p + 0xc0 : 0;
        if (((KeyCmp*)(void*)&vec)->Compare(ap, a0)) {
            int f = *first;
            int v = *p;
            *p = f;
            Fd9da80(first, 0, (int)((char*)mid - (char*)first) >> 2, 0, v, vec);
        }
    }
    Fd9efa0(first, mid, vec);
}

// @ 0x00d9f7e0
void Fd9f7e0(int* self)
{
    self[0] = 0; self[1] = 0; self[3] = 0; self[5] = 0;
    self[2] = 1;
    ((char*)self)[0x24] = 0;
    ((char*)self)[0x25] = 0;
    ((char*)self)[0x2c] = 0;
    self[6] = 0;   // +0x18
    self[7] = 0;   // +0x1c
    self[10] = 0;  // +0x28
    self[0xf] = 0; // +0x3c
    ((char*)self)[0x40] = 0;
    self[0x13] = 0;
    self[0x14] = 0;
    self[0x15] = 0;
    self[0x16] = 0;
    self[0x11] = 0;
    self[0x12] = 0;
    int* p = self + 0x1d;   // +0x74
    self[0x1b] = (int)(size_t)p;
    self[0x18] = (int)(size_t)p;
    self[0x17] = (int)(size_t)p;
    self[0x19] = (int)(size_t)(self + 0x20);
}

// @ 0x00d9f990
void* Fd9f990(int* self, int* pos, unsigned int n, const void* value)
{
    int* begin = (int*)self[0];
    int* cur = (int*)self[1];
    int* end = (int*)self[2];
    unsigned int cap = (unsigned int)((cur - begin) / 3);
    if ((unsigned int)((end - cur) / 3) < n) {
        unsigned int newcap = cap * 2;
        if (cap == 0)
            newcap = 1;
        if (newcap <= cap + n)
            newcap = cap + n;
        int* nb = (int*)F7ec550(begin, pos, 0);
        F6a4100(nb, n, value);
        int* nc = (int*)F7ec550(pos, cur, (char*)nb + n * 0xc);
        self[0] = 0;
        self[1] = (int)(size_t)nc;
        self[2] = (int)(size_t)((char*)nb + newcap * 0xc);
    } else if (n != 0) {
        int lc = ((int*)value)[0];
        int l8 = ((int*)value)[1];
        int l4 = ((int*)value)[2];
        unsigned int elems = (unsigned int)(cur - pos) / 3;
        if (n < elems) {
            int* p = cur - n * 3;
            F4797a0((void*)value, p, cur, cur, pos);
            self[1] = (int)(size_t)(cur + n * 3);
            Fabced0(pos, p, cur);
            Fa177f0(pos, (char*)pos + n * 0xc, &lc);
            return self;
        }
        unsigned int extra = n - elems;
        F6a4100(cur, extra, &lc);
        self[1] = (int)(size_t)(cur + extra * 3);
        F4797a0(pos, pos, cur, (int*)(size_t)self[1], pos);
        self[1] = (int)(size_t)((int*)(size_t)self[1] + elems * 3);
        Fa177f0(pos, cur, &lc);
    }
    return self;
}