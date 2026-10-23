// Slice s00a6a2f0: record copy constructors, ref-counted pointer containers
// (0x14-byte slots, 0x84-byte records), a string-keyed hashtable node insert,
// and 0x58/0x24-stride record teardown loops.
// flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);  // 0x00f473a0
void  __cdecl operator_delete__(void*);                                       // 0x00f47380
void* __cdecl SporeMemcpy(void*, const void*, unsigned);                      // 0x011e0744
extern const char kEastlAllocFile[];  // 0x013ebb38
extern const char kEastlTag[];        // 0x013f2150
extern void* (__cdecl* g_pMemmove)(void*, const void*, unsigned);             // 0x013cc480

// out-of-slice helpers (relocations are masked: only arg count/order matters)
void* __cdecl DoCopy12(void* first, void* last, void* dest);                              // 0x00b84c80
void  __cdecl UninitCopy12(void** out, void* first, void* last, void* dest, void* src);   // 0x00898b80
void  __cdecl UninitCopy84(void** out, void* first, void* last, void* dest, void* src);   // 0x00a6a9c0
void* __cdecl MoveBack12(void* first, void* last, void* dest);                            // 0x00d3b3c0
void* __cdecl DestroySlotRange3(void* first, void* last, void* out);                      // 0x00a69d60
void* __cdecl MoveSlotRange84(void* first, void* mid, void* last);                        // 0x00a6a7d0
void* __cdecl FillSlotTail(void* first, void* last, const void* value);                   // 0x00a6aee0
void  __cdecl Fill8Impl(void** out, void* dest, unsigned n, const void* value);           // 0x00594290
void  __cdecl Fill8Range(void* first, void* last, const void* value);                     // 0x00594260
int   __cdecl NodeKeyEq(const void* keyp, const void* node);                              // 0x00554fb0

// ---------------------------------------------------------------------------
struct RefObject {
    virtual void Release(int flag);   // vtable slot 0
    virtual void Destroy();           // vtable slot 1
    int mnRefCount;                   // +0x04
};

struct EString {
    char* b; char* e; char* cap; void* alloc;
    void assign(const char* first, const char* last);   // 0x00454cb0
};

struct HTNode {
    EString  mKey;      // +0x00
    unsigned mHash;     // +0x10
    HTNode*  mpNext;    // +0x14
    HTNode*  init(const EString* keyp);   // 0x009fc440
};

struct HTInsertOut {
    HTNode*  mpNode;      // +0x00
    HTNode** mpSlot;      // +0x04
    uint8_t  mbInserted;  // +0x08
};

struct RehashResult { uint8_t changed; uint8_t pad[3]; unsigned newSize; };

struct RehashPolicy {
    void rehash(RehashResult* out, unsigned* pCount, unsigned size, int flag);  // 0x00921440
};

struct HashTable {
    unsigned  mx00;            // +0x00
    HTNode**  mpBuckets;       // +0x04
    unsigned  muBucketCount;   // +0x08
    unsigned  muSize;          // +0x0c
    RehashPolicy mPolicy;      // +0x10
    void find_as(void** out, const char** keyp, unsigned a2, unsigned a3);          // 0x00a69c80
    HashTable* insert_node(HTInsertOut* out, const EString* keyp, unsigned unused); // 0x00a6a810
    void rehashTail(unsigned newSize);                                              // 0x00a694d0
};

struct HashKeyMap {
    char mPad[0x48];
    HashTable mSub;    // +0x48
    bool HasKey(EString* target, unsigned key);   // 0x00a6ae00
};

// ---------------------------------------------------------------------------
struct M33 { float m[9]; M33(const M33& o); };   // 0x24

struct Slot20 {                                  // 0x14
    int* b; int* e; int* cap;
    unsigned d10; unsigned d14;
    Slot20(const Slot20& o);   // 0x00a3d5b0
};

struct Trans {           // 0x38
    char x[0x38];
    Trans* Assign(const void* src);   // 0x00537dc0
};

struct Vec12 {           // 0x0c
    char* b; char* e; char* cap;
    char* AllocCopy12(unsigned n, char* first, char* last);   // 0x00a3d520
    Vec12& assign(const Vec12& o);                            // 0x00a6a6a0
};

struct VecRec84 {        // 0x0c
    char* b; char* e; char* cap;
    VecRec84& assign(const VecRec84& o);   // 0x00a6af10
};

struct IntVec {          // 0x10
    int* b; int* e; int* cap; void* mAlloc;
    void reserve(unsigned n, void** alloc);   // 0x004aa350
};

struct T8 { unsigned lo; unsigned hi; };   // 8-byte element

struct Vec8 {            // 0x0c
    T8* b; T8* e; T8* cap;
    void insert_n(T8* pos, unsigned count, const T8* value);   // 0x00a6aaa0
    void resize(unsigned n);                                   // 0x00a6b080
};

struct SlotVec {         // 0x0c
    char* b; char* e; char* cap;
    SlotVec* init(unsigned n, unsigned unused);                        // 0x00a6afe0
    void insert_n(Slot20* pos, unsigned count, const Slot20* value);      // 0x00a6b400
};

struct RefVec {          // 0x0c
    RefObject** b; RefObject** e; RefObject** cap;
    void DestroyRange(RefObject** first, RefObject** last);             // 0x00a693f0
    void insert(RefObject** pos, RefObject** value);                    // 0x00a69f90
    void insert_n(RefObject** pos, unsigned n, RefObject** value);      // 0x00a6a120
    void resize(unsigned n);                                           // 0x00a6ae70
};

struct Rec84 {           // 0x84: copied by 0x00a6a2f0
    int i00, i04;
    uint16_t w08; int16_t w0a;
    float f0c, f10, f14, f18;
    M33 mMat;                        // +0x1c
    uint8_t c40, c41;
    Slot20 mSlot;                    // +0x44
    float f58, f5c, f60, f64, f68, f6c;
    int i70, i74;
    int16_t w78; uint16_t w7a;
    float f7c;
    int i80;
    Rec84(const Rec84& o);           // 0x00a6a2f0
};

struct Rec84B {          // 0x84: copied by 0x00a6ac70
    int m00, m04;
    Trans mTr;                       // +0x08
    uint8_t c40, c41;
    Vec12 mVec;                      // +0x44
    int m50, m54;                    // +0x50 (copied flag only, not the value)
    float f58, f5c, f60, f64, f68, f6c;
    int i70, i74;
    int16_t w78; uint16_t w7a;
    float f7c;
    int i80;
    Rec84B(const Rec84B& o);         // 0x00a6ac70
};

struct BigRec {          // 0x50: copied by 0x00a6b290
    int i0, i4, i8;
    float f0c, f10, f14;
    uint8_t c18;
    IntVec mV;                       // +0x1c
    int x2c;
    float f30, f34, f38, f3c;
    int i40;
    VecRec84 mRecs;                  // +0x44
    BigRec(const BigRec& o);         // 0x00a6b290
};

struct ListOwner0c {     // holds a pointer to an array of 0x14-byte list slots
    char mPad[0xc];
    char* mpList;        // +0x0c
    int InsertAt(int idx, RefObject* value);   // 0x00a6ad00
};

struct ListOwner20 {
    char mPad[0x20];
    char* mpList;        // +0x20
    int InsertAt(int idx, RefObject* value);   // 0x00a6ad80
};

// ===========================================================================
// 0x00a6a2f0
// @ 0x00a6a2f0
Rec84::Rec84(const Rec84& o)
 : i00(o.i00), i04(o.i04), w08(o.w08), w0a(o.w0a),
   f0c(o.f0c), f10(o.f10), f14(o.f14), f18(o.f18),
   mMat(o.mMat), c40(o.c40), c41(o.c41), mSlot(o.mSlot),
   f58(o.f58), f5c(o.f5c), f60(o.f60), f64(o.f64), f68(o.f68), f6c(o.f6c),
   i70(o.i70), i74(o.i74), w78(o.w78), w7a(o.w7a), f7c(o.f7c), i80(o.i80)
{
}

// ===========================================================================
// 0x00a6a400
// @ 0x00a6a400
Slot20** __cdecl CopySlots20(Slot20** dstRef, Slot20* first, Slot20* last, Slot20* init, Slot20* unused)
{
    *dstRef = init;
    while (first != last) {
        Slot20* p = *dstRef;
        if (p != 0) {
            int n = (int)(first->e - first->b);
            int* buf = 0;
            if (n != 0)
                buf = (int*)operator_new(n * 4, kEastlTag, 0, 0, kEastlAllocFile, 0xd1);
            p->b = buf;
            p->e = buf;
            p->cap = buf + n;
            int* s = first->b;
            int* se = first->e;
            for (; s != se; ++s) {
                if (buf != 0) {
                    int v = *s;
                    *buf = v;
                    if (v != 0)
                        ++*(int*)(v + 4);
                }
                ++buf;
            }
            p->e = buf;
        }
        first = (Slot20*)((char*)first + 0x14);
        *dstRef = (Slot20*)((char*)*dstRef + 0x14);
    }
    return dstRef;
}

// ===========================================================================
// 0x00a6a4c0
// @ 0x00a6a4c0
int* __cdecl DestroyRecs24(int* p, int* end, int* out)
{
    while (p != end) {
        RefObject* o = (RefObject*)p[8];
        if (o != 0)
            o->Destroy();
        int v = p[4];
        if (1 < p[6] - v && v != 0)
            operator_delete__((void*)v);
        v = p[0];
        if (1 < p[2] - v && v != 0)
            operator_delete__((void*)v);
        p += 9;
        out += 9;
    }
    return out;
}

// ===========================================================================
// 0x00a6a530
// @ 0x00a6a530
Slot20* __cdecl FillSlots20(Slot20* first, Slot20* last, Slot20* dest)
{
    for (; first != last; first = (Slot20*)((char*)first + 0x14), dest = (Slot20*)((char*)dest + 0x14)) {
        if (dest != 0) {
            int n = (int)(first->e - first->b);
            int* buf = n != 0 ? (int*)operator_new(n * 4, kEastlTag, 0, 0, kEastlAllocFile, 0xd1) : 0;
            dest->b = buf;
            dest->e = buf;
            dest->cap = buf + n;
            int* se = first->e;
            int* s = first->b;
            for (; s != se; ++s) {
                if (buf != 0) {
                    int v = *s;
                    *buf = v;
                    if (v != 0)
                        ++*(int*)(v + 4);
                }
                ++buf;
            }
            dest->e = buf;
        }
    }
    return dest;
}

// ===========================================================================
// 0x00a6a610
// @ 0x00a6a610
char* __cdecl FreeRecs58(char* p, char* end, char* out)
{
    while (p != end) {
        char* uEnd = *(char**)(p + 0x48);
        char* u = *(char**)(p + 0x44);
        for (; u < uEnd; u += 0x84) {
            int* v = *(int**)(u + 0x44);
            if (v != 0 && v[-1] != 0)
                operator_delete__(v);
        }
        int* q = *(int**)(p + 0x44);
        if (q != 0 && q[-1] != 0)
            operator_delete__(q);
        q = *(int**)(p + 0x1c);
        if (q != 0 && q[-1] != 0)
            operator_delete__(q);
        p += 0x58;
        out += 0x58;
    }
    return out;
}

// ===========================================================================
// 0x00a6a6a0
// @ 0x00a6a6a0
Vec12& Vec12::assign(const Vec12& o)
{
    if (&o == this)
        return *this;
    unsigned n = (unsigned)((o.e - o.b) / 0xc);
    if ((unsigned)((cap - b) / 0xc) < n) {
        char* nb = AllocCopy12(n, o.b, o.e);
        if (b != 0 && *(int*)(b - 4) != 0)
            operator_delete__(b);
        cap = nb + n * 0xc;
        b = nb;
        e = nb;
    } else {
        unsigned have = (unsigned)((e - b) / 0xc);
        if (have < n) {
            DoCopy12(o.b, o.b + have * 0xc, b);
            char* tmp = o.e;
            UninitCopy12((void**)&tmp, o.b + have * 0xc, tmp, e, tmp);
            e = b + n * 0xc;
        } else {
            DoCopy12(o.b, o.e, b);
            e = b + n * 0xc;
        }
    }
    return *this;
}

// ===========================================================================
// 0x00a6a810
// @ 0x00a6a810
HashTable* HashTable::insert_node(HTInsertOut* out, const EString* keyp, unsigned unused)
{
    const char* p = keyp->b;
    unsigned h = 0x811c9dc5;
    while (*p)
        h = (h * 0x1000193) ^ (unsigned)(unsigned char)*p++;
    unsigned idx = h % muBucketCount;
    HTNode** slot = &mpBuckets[idx];
    HTNode* node = *slot;
    for (;;) {
        if (node == 0) {
            RehashResult r;
            ((RehashPolicy*)((char*)this + 0x10))->rehash(&r, &muBucketCount, muSize, 1);
            node = (HTNode*)operator_new(0x18, kEastlTag, 0, 0, kEastlAllocFile, 0xd1);
            if (node != 0)
                node->init(keyp);
            node->mpNext = 0;
            if (r.changed != 0) {
                idx = h % r.newSize;
                rehashTail(r.newSize);
            }
            node->mpNext = mpBuckets[idx];
            mpBuckets[idx] = node;
            ++muSize;
            out->mpNode = node;
            out->mpSlot = &mpBuckets[idx];
            out->mbInserted = 1;
            return this;
        }
        if (NodeKeyEq(keyp, node) != 0) {
            out->mpNode = node;
            out->mpSlot = slot;
            out->mbInserted = 0;
            return this;
        }
        node = node->mpNext;
    }
}

// ===========================================================================
// 0x00a6a940
// @ 0x00a6a940
void __stdcall FreeRecs58Std(unsigned p, unsigned end)
{
    for (; p < end; p += 0x58) {
        char* r = (char*)p;
        char* uEnd = *(char**)(r + 0x48);
        char* u = *(char**)(r + 0x44);
        for (; u < uEnd; u += 0x84) {
            int* v = *(int**)(u + 0x44);
            if (v != 0 && v[-1] != 0)
                operator_delete__(v);
        }
        int* q = *(int**)(r + 0x44);
        if (q != 0 && q[-1] != 0)
            operator_delete__(q);
        q = *(int**)(r + 0x1c);
        if (q != 0 && q[-1] != 0)
            operator_delete__(q);
    }
}

// ===========================================================================
// 0x00a6aa00
// @ 0x00a6aa00
void __cdecl FillSlots20N(Slot20* dest, unsigned n, const Slot20* src, Slot20* unused)
{
    if (n == 0)
        return;
    do {
        if (dest != 0) {
            int cnt = (int)(src->e - src->b);
            int* buf = 0;
            if (cnt != 0)
                buf = (int*)operator_new(cnt * 4, kEastlTag, 0, 0, kEastlAllocFile, 0xd1);
            dest->b = buf;
            dest->e = buf;
            dest->cap = buf + cnt;
            int* s = src->b;
            int* se = src->e;
            for (; s != se; ++s) {
                if (buf != 0) {
                    int v = *s;
                    *buf = v;
                    if (v != 0)
                        ++*(int*)(v + 4);
                }
                ++buf;
            }
            dest->e = buf;
        }
        --n;
        dest = (Slot20*)((char*)dest + 0x14);
    } while (n != 0);
}

// ===========================================================================
// 0x00a6aaa0
// @ 0x00a6aaa0
void Vec8::insert_n(T8* pos, unsigned count, const T8* value)
{
    unsigned avail = (unsigned)(((char*)cap - (char*)e) >> 3);
    if (avail < count) {
        unsigned oldCnt = (unsigned)(((char*)e - (char*)b) >> 3);
        unsigned newCap = oldCnt != 0 ? oldCnt * 2 : 1;
        if (newCap < oldCnt + count)
            newCap = oldCnt + count;
        T8* buf = (T8*)operator_new(newCap * 8, kEastlTag, 0, 0, kEastlAllocFile, 0xd1);
        char* p = (char*)SporeMemcpy(buf, b, (unsigned)((char*)pos - (char*)b));
        char* mid = p + ((unsigned)((char*)pos - (char*)b) >> 3) * 8;
        void* out;
        Fill8Impl(&out, mid, count, value);
        unsigned tail = (unsigned)((char*)e - (char*)pos);
        SporeMemcpy(mid + count * 8, pos, tail);
        if (b != 0 && *(int*)((char*)b - 4) != 0)
            operator_delete__(b);
        b = buf;
        e = (T8*)(p + (tail >> 3) * 8);
        cap = buf + newCap;
    } else {
        T8 local = *value;
        unsigned after = (unsigned)(((char*)e - (char*)pos) >> 3);
        char* oldEnd = (char*)e;
        if (count < after) {
            char* src = oldEnd - count * 8;
            SporeMemcpy(e, src, count * 8);
            g_pMemmove(oldEnd - (src - (char*)pos), pos, (unsigned)(src - (char*)pos));
            e = (T8*)(oldEnd + count * 8);
            Fill8Range(pos, (char*)pos + count * 8, &local);
        } else {
            void* out;
            Fill8Impl(&out, oldEnd, count - after, &local);
            char* mid = oldEnd + (count - after) * 8;
            SporeMemcpy(mid, pos, (unsigned)(oldEnd - (char*)pos));
            e = (T8*)(mid + after * 8);
            Fill8Range(pos, oldEnd, &local);
        }
    }
}

// ===========================================================================
// 0x00a6ac70
// @ 0x00a6ac70
Rec84B::Rec84B(const Rec84B& o)
{
    m00 = o.m00;
    m04 = o.m04;
    mTr.Assign(&o.mTr);
    c40 = o.c40;
    c41 = o.c41;
    mVec.assign(o.mVec);
    f58 = o.f58;
    f5c = o.f5c;
    f60 = o.f60;
    f64 = o.f64;
    f68 = o.f68;
    f6c = o.f6c;
    i70 = o.i70;
    i74 = o.i74;
    w78 = o.w78;
    w7a = o.w7a;
    f7c = o.f7c;
    i80 = o.i80;
}

// ===========================================================================
// 0x00a6ad00
// @ 0x00a6ad00
int ListOwner0c::InsertAt(int idx, RefObject* value)
{
    RefVec* v = (RefVec*)(mpList + idx * 0x14);
    int n = (int)(v->e - v->b);
    RefObject* val = value;
    if (value != 0)
        ++value->mnRefCount;
    if (v->e < v->cap) {
        RefObject** e = v->e;
        v->e = e + 1;
        if (e != 0) {
            *e = value;
            if (value != 0)
                ++value->mnRefCount;
        }
    } else {
        v->insert(v->e, &val);
    }
    if (val != 0) {
        int rc = val->mnRefCount - 1;
        val->mnRefCount = rc;
        if (rc == 0) {
            val->mnRefCount = 1;
            val->Release(1);
        }
    }
    return n;
}

// ===========================================================================
// 0x00a6ad80
// @ 0x00a6ad80
int ListOwner20::InsertAt(int idx, RefObject* value)
{
    RefVec* v = (RefVec*)(mpList + idx * 0x14);
    int n = (int)(v->e - v->b);
    RefObject* val = value;
    if (value != 0)
        ++value->mnRefCount;
    if (v->e < v->cap) {
        RefObject** e = v->e;
        v->e = e + 1;
        if (e != 0) {
            *e = value;
            if (value != 0)
                ++value->mnRefCount;
        }
    } else {
        v->insert(v->e, &val);
    }
    if (val != 0) {
        int rc = val->mnRefCount - 1;
        val->mnRefCount = rc;
        if (rc == 0) {
            val->mnRefCount = 1;
            val->Release(1);
        }
    }
    return n;
}

// ===========================================================================
// 0x00a6ae00
// @ 0x00a6ae00
bool HashKeyMap::HasKey(EString* target, unsigned key)
{
    unsigned k = key;
    unsigned m = key & 0xffffff00;
    void* out[2];
    mSub.find_as(out, (const char**)&k, m, m);
    HTNode* node = (HTNode*)out[0];
    if (out[0] != (void*)mSub.mpBuckets[mSub.muBucketCount]) {
        if ((void*)node != (void*)target)
            target->assign(node->mKey.b, node->mKey.e);
        return true;
    }
    return false;
}

// ===========================================================================
// 0x00a6ae70
// @ 0x00a6ae70
void RefVec::resize(unsigned n)
{
    int have = (int)(e - b);
    if (n > (unsigned)have) {
        RefObject* zero = 0;
        insert_n(e, n - have, &zero);
    } else {
        RefObject** cut = b + n;
        RefObject** res = (RefObject**)MoveBack12(e, e, cut);
        DestroyRange(res, e);
        e -= e - cut;
    }
}

// ===========================================================================
// 0x00a6af10
// @ 0x00a6af10
VecRec84& VecRec84::assign(const VecRec84& o)
{
    int n = (int)((o.e - o.b) / 0x84);
    char* buf = 0;
    if (n != 0)
        buf = (char*)operator_new(n * 0x84, kEastlTag, 0, 0, kEastlAllocFile, 0xd1);
    b = buf;
    e = buf;
    cap = buf + n * 0x84;
    char* tmp;
    UninitCopy84((void**)&tmp, o.b, o.e, buf, (void*)&o);
    e = tmp;
    return *this;
}

// ===========================================================================
// 0x00a6afe0
// @ 0x00a6afe0
SlotVec* SlotVec::init(unsigned n, unsigned unused)
{
    char* buf = 0;
    if (n != 0)
        buf = (char*)operator_new(n * 0x14, kEastlTag, 0, 0, kEastlAllocFile, 0xd1);
    cap = buf + n * 0x14;
    b = buf;
    e = buf;
    RefVec local;
    local.b = 0;
    local.e = 0;
    local.cap = 0;
    FillSlots20N((Slot20*)buf, n, (const Slot20*)&local, (Slot20*)n);
    local.DestroyRange((RefObject**)0, (RefObject**)0);
    e = b + n * 0x14;
    return this;
}

// ===========================================================================
// 0x00a6b080
// @ 0x00a6b080
void Vec8::resize(unsigned n)
{
    int have = (int)(e - b);
    if (n > (unsigned)have) {
        unsigned long long zero = 0;
        insert_n(e, n - have, (const T8*)&zero);
    } else {
        T8* cut = b + n;
        SporeMemcpy(cut, e, (unsigned)(e - e));
        e -= e - cut;
    }
}

// ===========================================================================
// 0x00a6b290
// @ 0x00a6b290
BigRec::BigRec(const BigRec& o)
{
    i0 = o.i0;
    i4 = o.i4;
    i8 = o.i8;
    f0c = o.f0c;
    f10 = o.f10;
    f14 = o.f14;
    c18 = o.c18;
    unsigned n = (unsigned)(((char*)o.mV.e - (char*)o.mV.b) >> 2);
    mV.reserve(n, (void**)&o.mV.mAlloc);
    int* p = (int*)SporeMemcpy(mV.b, o.mV.b, n * 4);
    mV.e = p + n;
    f30 = o.f30;
    f34 = o.f34;
    f38 = o.f38;
    f3c = o.f3c;
    i40 = o.i40;
    mRecs.assign(o.mRecs);
}

// ===========================================================================
// 0x00a6b400
// @ 0x00a6b400
void SlotVec::insert_n(Slot20* pos, unsigned count, const Slot20* value)
{
    unsigned oldCnt = (unsigned)(((char*)e - (char*)b) / 0x14);
    unsigned avail = (unsigned)(((char*)cap - (char*)e) / 0x14);
    if (count > avail) {
        unsigned newCap = oldCnt != 0 ? oldCnt * 2 : 1;
        if (newCap < oldCnt + count)
            newCap = oldCnt + count;
        char* buf = newCap != 0 ? (char*)operator_new(newCap * 0x14, kEastlTag, 0, 0, kEastlAllocFile, 0xd1) : 0;
        Slot20* p1 = FillSlots20((Slot20*)b, pos, (Slot20*)buf);
        DestroySlotRange3(b, pos, buf);
        FillSlots20N(p1, count, value, p1);
        Slot20* mid = (Slot20*)((char*)p1 + count * 0x14);
        Slot20* p2 = FillSlots20(pos, (Slot20*)e, mid);
        DestroySlotRange3(pos, e, mid);
        if (b != 0 && *(int*)(b - 4) != 0)
            operator_delete__(b);
        b = buf;
        e = (char*)p2;
        cap = buf + newCap * 0x14;
    }
    else if (count != 0) {
        Slot20 local(*value);
        char* oldEnd = e;
        unsigned after = (unsigned)(((char*)oldEnd - (char*)pos) / 0x14);
        if (count < after) {
            Slot20* mid = (Slot20*)((char*)oldEnd - count * 0x14);
            Slot20* dest = mid;
            CopySlots20(&dest, mid, (Slot20*)oldEnd, (Slot20*)oldEnd, pos);
            e = oldEnd + count * 0x14;
            MoveSlotRange84(pos, mid, e);
            FillSlotTail(pos, (char*)pos + count * 0x14, &local);
        } else {
            FillSlots20N((Slot20*)oldEnd, count - after, &local, pos);
            Slot20* mid = (Slot20*)((char*)oldEnd + (count - after) * 0x14);
            Slot20* dest = pos;
            CopySlots20(&dest, pos, (Slot20*)oldEnd, mid, pos);
            e = (char*)mid + after * 0x14;
            FillSlotTail(pos, oldEnd, &local);
        }
        ((RefVec*)&local)->DestroyRange((RefObject**)local.b, (RefObject**)local.e);
        if (local.b != 0 && local.b[-1] != 0)
            operator_delete__(local.b);
    }
}
