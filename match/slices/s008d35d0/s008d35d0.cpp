// slice s008d35d0 -- TSI type-supplier / glyph-run list + sort utilities.
// Compile: /O2 /MD /Gy /EHsc /TP
#include "types.h"

struct TSI;
struct OwnerNode;

// ---------------------------------------------------------------------------
// Shared layouts
// ---------------------------------------------------------------------------

// One entry of the glyph-run table (0x1c bytes).
struct RunRec {
    OwnerNode*     mpOwner;   // +0x00
    int            mKey4;     // +0x04
    int            mKey8;     // +0x08
    int            mKeyC;     // +0x0c
    float          mf10;      // +0x10
    signed char    mb14;      // +0x14
    signed char    mb15;      // +0x15
    unsigned short mFlags16;  // +0x16
    unsigned short mDup18;    // +0x18
};

typedef void (*RunNotifyFn)(int, RunRec*, void*);

// Per-node provider interface (slot4 at vtable +0x04, slotC at +0x0c).
struct IRunProvider {
    virtual void* slot0();
    virtual void* slot4(void* key, void* a, void* b);   // vtable +0x04
    virtual void* slot8();
    virtual char  slotC(void* data, void* container);   // vtable +0x0c
};

// One node of TSI's intrusive list (0x1c bytes).
struct OwnerNode {
    OwnerNode*    mpNext;   // +0x00
    OwnerNode*    mpPrev;   // +0x04
    int           mKey8;    // +0x08
    IRunProvider* mpIface;  // +0x0c
    RunNotifyFn   mpFn;     // +0x10
    void*         mpData;   // +0x14
    unsigned char mFlag;    // +0x18
};

// eastl allocator interface (vtable +0x08 allocate, +0x0c deallocate).
struct VAlloc {
    virtual void  s0();
    virtual void  s4();
    virtual void* allocate(unsigned n, int a, void* name);
    virtual void  deallocate(void* p, unsigned n);
};

// {begin,end,cap,alloc,name} vector core over 0x10-byte elements.
struct VecCore {
    void*   begin;   // +0x00
    void*   end;     // +0x04
    void*   cap;     // +0x08
    VAlloc* alloc;   // +0x0c
    void*   name;    // +0x10
    void grow(void* p, void* value);   // 0x008d4400
};

extern "C" void* FUN_00c7ea30(void* first, void* last, void* dest);
extern "C" void  FUN_00edba80(void* first, void* last, void* dest);
extern "C" char  PTR_FUN_01435990;
extern "C" char  PTR_FUN_01435980;

// ---------------------------------------------------------------------------
// TSI: two overlapping views of the same object.
//   * glyph container: intrusive-list links at +0/+4, RunRec[0x20] at +8.
//   * run table:       vtable at +0, two VecCore members at +4 and +0x18.
// ---------------------------------------------------------------------------
struct TSI {
    union {
        struct {
            TSI*   mpNext;        // +0x000
            TSI*   mpPrev;        // +0x004
            RunRec mRuns[0x20];   // +0x008 (stride 0x1c)
            int    mCount;        // +0x388
            char   mFlag;         // +0x38c
        };
        struct {
            void*   mVtbl;        // +0x00
            VecCore mKeys;        // +0x04 (0x10-byte entries)
            VecCore mRects;       // +0x18 (0x14-byte entries)
            char    mDirty;       // +0x2c
        };
    };

    void       FUN_008d35d0(RunRec* rec, int arg);                      // 0x008d35d0
    void       FUN_008d3690(RunRec* rec);                               // 0x008d3690
    char       FUN_008d36f0(int a, int b, int c);                       // 0x008d36f0
    RunRec*    FUN_008d3530(int key, int b14, int b15);                 // 0x008d3530
    RunRec*    FUN_008d3580(int key, int b14, int b15, unsigned mask);  // 0x008d3580
    int        FUN_008d3ad0(int i);                                     // 0x008d3ad0
    int        FUN_008d3ae0(int key);                                   // 0x008d3ae0
    void       FUN_008d3b10(OwnerNode* node);                           // 0x008d3b10
    TSI*       FUN_008d3c60(VAlloc* alloc);                             // 0x008d3c60
    void       FUN_008d3ca0();                                          // 0x008d3ca0
    bool       FUN_008d3d30(int key, TSI* container);                   // 0x008d3d30
    TSI*       FUN_008d3da0();                                          // 0x008d3da0
    OwnerNode* FUN_008d3dc0(void* key, int* pOut, void* a4, void* a5);  // 0x008d3dc0
    void       FUN_008d3e30(RunRec* rec, unsigned flags);               // 0x008d3e30
    void       FUN_008d41b0(OwnerNode* node);                           // 0x008d41b0
};

// Free helpers / non-matching slice functions.
void      FUN_008d3750(unsigned* a, unsigned* b);
void      FUN_008d3820(unsigned* a, unsigned* b);
unsigned* FUN_008d38d0(unsigned* a, unsigned* b, unsigned* c);
void*     FUN_008d3a10(int base, int start, int idx, unsigned k0, unsigned k1,
                       unsigned k2, unsigned k3);
void      FUN_008d3b70(int a, int b, int c, int d, unsigned e, unsigned f,
                       unsigned g, unsigned h, int i);
void* FUN_008d4040(void** pOut, void* head, void* tail, void* key, void* unused);
void      FUN_008d40b0(int a, int b, int c);
void      FUN_008d4110(unsigned* a, int b, int c);
void      FUN_008d4250(unsigned* a, unsigned* b, unsigned c, unsigned d, unsigned e);
void      FUN_008d4320(unsigned* a, unsigned* b, unsigned* c, int d);

// ---------------------------------------------------------------------------
// @ 0x008d35d0
// Remove one run from the table, notify its owner, then free matching children.
// ---------------------------------------------------------------------------
void TSI::FUN_008d35d0(RunRec* rec, int arg)
{
    RunRec local = *rec;
    --mCount;
    RunRec* last = &mRuns[mCount];
    if ((unsigned)last > (unsigned)rec)
        *rec = *last;

    OwnerNode* owner = local.mpOwner;
    if (owner != 0) {
        if (owner->mpFn != 0 && (local.mFlags16 & 0x2000) == 0)
            owner->mpFn(arg, &local, owner->mpData);
    }
    if (local.mKey8 != 0 && (local.mFlags16 & 0x1000) == 0) {
        RunRec* r = FUN_008d3580(local.mKey8, local.mb14, local.mb15, 0x1000);
        if (r != 0)
            FUN_008d35d0(r, arg);
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d3690
// Set the duplicate flag from the number of matching runs, then unlink rec.
// ---------------------------------------------------------------------------
void TSI::FUN_008d3690(RunRec* rec)
{
    unsigned c = 0;
    int n = mCount;
    if (n != 0) {
        RunRec* p = mRuns;
        do {
            if (p->mKey4 == rec->mKey4 && p->mpOwner == rec->mpOwner &&
                p->mKeyC == rec->mKeyC)
                c++;
            p++;
            n--;
        } while (n != 0);
    }
    rec->mDup18 = (unsigned short)(1 < c);
    FUN_008d35d0(rec, 0x5ece0001);
}

// ---------------------------------------------------------------------------
// @ 0x008d36f0
// ---------------------------------------------------------------------------
char TSI::FUN_008d36f0(int param_2, int param_3, int param_4)
{
    if (param_2 != 0) {
        unsigned u = 0;
        unsigned cnt = (unsigned)mCount;
        if (u < cnt) {
            RunRec* p = mRuns;
            do {
                if (p->mKey4 == param_2 && (param_3 == -2 || param_3 == p->mb15) &&
                    (param_4 == 7 || param_4 == p->mb14))
                    return 1;
                u++;
                p++;
            } while (u < cnt);
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x008d3750 (non-matching: register allocation / branch layout differ)
// ---------------------------------------------------------------------------
void FUN_008d3750(unsigned* param_1, unsigned* param_2)
{
    unsigned u1, u2, u3, u4;
    unsigned *p5, *p6, *p7, *p8;
    bool b;
    unsigned short us;
    p6 = param_1;
    if (param_1 != param_2) {
        while ((p6 = p6 + 4) != param_2) {
            u1 = p6[1]; u2 = p6[3]; u3 = p6[2]; u4 = *p6;
            p7 = p6;
            if (p6 != param_1) {
                us = (unsigned short)(u3 >> 0x10);
                p5 = p6;
                do {
                    p8 = p5 - 4;
                    b = u4 < *p8;
                    if (u4 == *p8) {
                        b = *(unsigned short*)((int)p5 - 6) <= us;
                        if (us == *(unsigned short*)((int)p5 - 6)) {
                            if ((unsigned short)u3 == (unsigned short)p5[-2])
                                b = u1 < p5[-3];
                            else
                                b = (unsigned short)p5[-2] < (unsigned short)u3;
                        }
                    }
                    if (!b) break;
                    *p7 = *p8; p7[1] = p5[-3]; p7[2] = p5[-2]; p7[3] = p5[-1];
                    p7 = p7 - 4;
                    p5 = p8;
                } while (p7 != param_1);
            }
            *p7 = u4; p7[1] = u1; p7[2] = u3; p7[3] = u2;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d3820 (non-matching)
// ---------------------------------------------------------------------------
void FUN_008d3820(unsigned* param_1, unsigned* param_2)
{
    unsigned u1, u2, u3, u4;
    unsigned *p5, *p6, *p7;
    bool b;
    unsigned short us;
    for (; param_1 != param_2; param_1 = param_1 + 4) {
        u1 = param_1[1]; u2 = param_1[2]; u3 = param_1[3]; u4 = *param_1;
        us = (unsigned short)(u2 >> 0x10);
        p7 = param_1;
        p5 = param_1;
        while (true) {
            p6 = p5 - 4;
            b = u4 < *p6;
            if (u4 == *p6) {
                b = *(unsigned short*)((int)p5 - 6) <= us;
                if (us == *(unsigned short*)((int)p5 - 6)) {
                    if ((unsigned short)u2 == (unsigned short)p5[-2])
                        b = u1 < p5[-3];
                    else
                        b = (unsigned short)p5[-2] < (unsigned short)u2;
                }
            }
            if (!b) break;
            *p7 = *p6; p7[1] = p5[-3]; p7[2] = p5[-2]; p7[3] = p5[-1];
            p7 = p7 - 4;
            p5 = p6;
        }
        *p7 = u4; p7[1] = u1; p7[2] = u2; p7[3] = u3;
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d38d0 (non-matching)
// ---------------------------------------------------------------------------
unsigned* FUN_008d38d0(unsigned* param_1, unsigned* param_2, unsigned* param_3)
{
    unsigned u1, u2, u3;
    bool b;
    u1 = *param_1;
    u2 = *param_2;
    b = u1 < u2;
    if (u1 == u2) {
        b = *(unsigned short*)((int)param_2 + 10) <= *(unsigned short*)((int)param_1 + 10);
        if (*(unsigned short*)((int)param_1 + 10) == *(unsigned short*)((int)param_2 + 10)) {
            b = (unsigned short)param_2[2] <= (unsigned short)param_1[2];
            if ((unsigned short)param_1[2] == (unsigned short)param_2[2])
                b = param_1[1] < param_2[1];
        }
    }
    u3 = *param_3;
    if (b) {
        b = u2 < u3;
        if (u2 == u3) {
            b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_2 + 10);
            if (*(unsigned short*)((int)param_2 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                b = (unsigned short)param_3[2] <= (unsigned short)param_2[2];
                if ((unsigned short)param_2[2] == (unsigned short)param_3[2])
                    b = param_2[1] < param_3[1];
            }
        }
        if (!b) {
            b = u1 < u3;
            if (u1 == u3) {
                b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_1 + 10);
                if (*(unsigned short*)((int)param_1 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                    b = (unsigned short)param_3[2] <= (unsigned short)param_1[2];
                    if ((unsigned short)param_1[2] == (unsigned short)param_3[2])
                        b = param_1[1] < param_3[1];
                }
            }
            if (!b) return param_1;
            return param_3;
        }
    } else {
        b = u1 < u3;
        if (u1 == u3) {
            b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_1 + 10);
            if (*(unsigned short*)((int)param_1 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                b = (unsigned short)param_3[2] <= (unsigned short)param_1[2];
                if ((unsigned short)param_1[2] == (unsigned short)param_3[2])
                    b = param_1[1] < param_3[1];
            }
        }
        if (b) return param_1;
        b = *param_2 < u3;
        if (*param_2 == u3) {
            b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_2 + 10);
            if (*(unsigned short*)((int)param_2 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                b = (unsigned short)param_3[2] <= (unsigned short)param_2[2];
                if ((unsigned short)param_2[2] == (unsigned short)param_3[2])
                    b = param_2[1] < param_3[1];
            }
        }
        if (b) return param_3;
    }
    return param_2;
}

// ---------------------------------------------------------------------------
// @ 0x008d3a10
// Sift one 0x10-byte key up into the heap rooted at base[start..idx].
// Returns the address of the destination slot.
// ---------------------------------------------------------------------------
void* FUN_008d3a10(int base, int start, int idx, unsigned k0, unsigned k1,
                   unsigned k2, unsigned k3)
{
    while (start < idx) {
        int parent = (idx - 1) >> 1;
        unsigned* p = (unsigned*)((char*)base + parent * 0x10);
        unsigned p0 = p[0];
        bool less = p0 < k0;
        if (p0 == k0) {
            less = (unsigned short)(k2 >> 0x10) <= *(unsigned short*)((char*)p + 0xa);
            if (*(unsigned short*)((char*)p + 0xa) == (unsigned short)(k2 >> 0x10)) {
                less = (unsigned short)k2 <= (unsigned short)p[2];
                if ((unsigned short)p[2] == (unsigned short)k2)
                    less = p[1] < k1;
            }
        }
        if (!less)
            break;
        unsigned* dst = (unsigned*)((char*)base + idx * 0x10);
        dst[0] = p[0]; dst[1] = p[1]; dst[2] = p[2]; dst[3] = p[3];
        idx = parent;
    }
    unsigned* dst = (unsigned*)((char*)base + idx * 0x10);
    dst[0] = k0; dst[1] = k1; dst[2] = k2; dst[3] = k3;
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x008d3ad0
// ---------------------------------------------------------------------------
int TSI::FUN_008d3ad0(int param_2)
{
    return param_2 * 0x10 + (int)mKeys.begin;
}

// ---------------------------------------------------------------------------
// @ 0x008d3ae0
// ---------------------------------------------------------------------------
int TSI::FUN_008d3ae0(int param_2)
{
    int p = (int)mKeys.begin;
    int e = (int)mKeys.end;
    while (true) {
        if (p == e)
            return 0;
        if (*(int*)(p + 4) == param_2) break;
        p = p + 0x10;
    }
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x008d3b10
// Unlink node from the intrusive list, then purge every run owned by it.
// ---------------------------------------------------------------------------
void TSI::FUN_008d3b10(OwnerNode* node)
{
    OwnerNode* p = (OwnerNode*)mpNext;
    for (;;) {
        if (p == (OwnerNode*)this)
            break;
        if (p == node) {
            OwnerNode* pv = node->mpPrev;
            OwnerNode* nx = node->mpNext;
            pv->mpNext = nx;
            nx->mpPrev = pv;
            node->mpNext = 0;
            node->mpPrev = 0;
            break;
        }
        p = p->mpNext;
    }

    unsigned u = 0;
    if ((unsigned)mCount > 0) {
        RunRec* r = mRuns;
        do {
            if ((OwnerNode*)r->mpOwner == node)
                FUN_008d35d0(r, 0x5ece0002);
            else {
                u++;
                r++;
            }
        } while (u < (unsigned)mCount);
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d3b70 (non-matching)
// ---------------------------------------------------------------------------
void FUN_008d3b70(int param_1, int param_2, int param_3, int param_4, unsigned param_5,
                  unsigned param_6, unsigned param_7, unsigned param_8, int param_9)
{
    unsigned u;
    int i2, i3, i4, i6;
    unsigned* p;
    bool b;
    (void)param_9;
    while (true) {
        i4 = param_4 * 2;
        i6 = i4 + 2;
        if (param_3 <= i6) break;
        i2 = i6 * 0x10;
        u = *(unsigned*)(i2 - 0x10 + param_1);
        i3 = i2 + param_1;
        b = *(unsigned*)(i2 + param_1) < u;
        if (*(unsigned*)(i2 + param_1) == u) {
            b = *(unsigned short*)(i3 - 6) <= *(unsigned short*)(i3 + 10);
            if (*(unsigned short*)(i3 + 10) == *(unsigned short*)(i3 - 6)) {
                b = *(unsigned short*)(i3 - 8) <= *(unsigned short*)(i3 + 8);
                if (*(unsigned short*)(i3 + 8) == *(unsigned short*)(i3 - 8))
                    b = *(unsigned*)(i3 + 4) < *(unsigned*)(i3 - 0xc);
            }
        }
        if (b) i6 = i4 + 1;
        i4 = i6 * 0x10 + param_1;
        p = (unsigned*)(param_4 * 0x10 + param_1);
        p[0] = *(unsigned*)(i6 * 0x10 + param_1);
        p[1] = *(unsigned*)(i4 + 4);
        p[2] = *(unsigned*)(i4 + 8);
        p[3] = *(unsigned*)(i4 + 0xc);
        param_4 = i6;
    }
    if (i6 == param_3) {
        p = (unsigned*)(i6 * 0x10 - 0x10 + param_1);
        *(unsigned*)(param_4 * 0x10 + param_1) = p[0];
        i6 = param_4 * 0x10 + param_1;
        *(unsigned*)(i6 + 4) = p[1];
        *(unsigned*)(i6 + 8) = p[2];
        *(unsigned*)(i6 + 0xc) = p[3];
        param_4 = i4 + 1;
    }
    FUN_008d3a10(param_1, param_2, param_4, param_5, param_6, param_7, param_8);
}

// ---------------------------------------------------------------------------
// @ 0x008d3c60
// Run-table constructor: install the vtable, two empty vectors and the
// allocator.
// ---------------------------------------------------------------------------
TSI* TSI::FUN_008d3c60(VAlloc* alloc)
{
    mVtbl = &PTR_FUN_01435990;
    mKeys.begin = 0;
    mKeys.end = 0;
    mKeys.cap = 0;
    mKeys.alloc = alloc;
    mKeys.name = 0;
    mRects.begin = 0;
    mRects.end = 0;
    mRects.cap = 0;
    mRects.alloc = alloc;
    mRects.name = 0;
    mDirty = 0;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x008d3ca0
// Run-table destructor: release both vectors through their allocators.
// ---------------------------------------------------------------------------
void TSI::FUN_008d3ca0()
{
    mVtbl = &PTR_FUN_01435990;
    if (mRects.begin != 0)
        mRects.alloc->deallocate(mRects.begin,
            (unsigned)((((int)mRects.cap - (int)mRects.begin) / 0x14) * 0x14));
    if (mKeys.begin != 0)
        mKeys.alloc->deallocate(mKeys.begin,
            (unsigned)((((int)mKeys.cap - (int)mKeys.begin) >> 4) << 4));
    mVtbl = &PTR_FUN_01435980;
}

// ---------------------------------------------------------------------------
// @ 0x008d3d30
// True when every non-zero key of the rect entry is present in container's runs.
// ---------------------------------------------------------------------------
bool TSI::FUN_008d3d30(int param_2, TSI* param_3)
{
    int* r = (int*)mRects.begin;
    int* e = (int*)mRects.end;
    if (r == e)
        return false;
    do {
        if (*r == param_2)
            break;
        r += 5;
    } while (r != e);
    if (r == e)
        return false;

    unsigned u = 0;
    int* field = r + 1;
    do {
        int v = *field;
        if (v != 0) {
            if ((unsigned)param_3->mCount == 0)
                return false;
            unsigned i = 0;
            int* k = &param_3->mRuns[0].mKey4;
            while (*k != v) {
                i++;
                k += 7;
                if ((unsigned)param_3->mCount <= i)
                    return false;
            }
        }
        u++;
        field++;
    } while (u < 4);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x008d3da0
// Initialise the intrusive-list sentinel and count.
// ---------------------------------------------------------------------------
TSI* TSI::FUN_008d3da0()
{
    mpPrev = this;
    mpNext = this;
    mCount = 0;
    mFlag = 1;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x008d3dc0
// Walk the list calling each node's provider; return the first node that
// produces a run, storing the run pointer in *pOut.
// ---------------------------------------------------------------------------
OwnerNode* TSI::FUN_008d3dc0(void* key, int* pOut, void* a4, void* a5)
{
    OwnerNode* first = (OwnerNode*)mpNext;
    if ((OwnerNode*)this == first)
        return 0;
    OwnerNode* p = (OwnerNode*)this;
    for (;;) {
        OwnerNode* node = p->mpPrev;
        if (node->mpIface != 0) {
            void* r = node->mpIface->slot4(key, a4, a5);
            *pOut = (int)r;
            if (r != 0)
                return node;
        }
        if (node->mFlag & 1)
            return 0;
        p = p->mpPrev;
        if (p == first)
            return 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d3e30
// Add one run to the table: merge duplicates, notify the owner and descend.
// ---------------------------------------------------------------------------
void TSI::FUN_008d3e30(RunRec* rec, unsigned flags)
{
    if ((char)flags == 0) {
        RunRec* r = FUN_008d3530(rec->mKeyC, rec->mb14, rec->mb15);
        if (r != 0) {
            FUN_008d3690(r);
            return;
        }
    } else if ((unsigned)mCount < 0x20) {
        int local_24 = rec->mKey8;
        OwnerNode* i4 = rec->mpOwner;
        int local_20 = rec->mKey4;
        flags = rec->mFlags16;
        if (i4 == 0 || local_20 == 0)
            i4 = FUN_008d3dc0(rec, &local_20, &flags, &local_24);
        if (i4 != 0 && i4->mpFn != 0) {
            RunRec* dst = &mRuns[mCount];
            *dst = *rec;
            dst->mDup18 = 0;

            unsigned u = 0;
            if (mCount != 0) {
                RunRec* p = mRuns;
                do {
                    if (rec->mKeyC == p->mKeyC && rec->mb14 == p->mb14 &&
                        rec->mb15 == p->mb15)
                        return;
                    if (p->mKey4 == local_20 && p->mpOwner == i4 &&
                        p->mb14 == rec->mb14 && p->mb15 == rec->mb15)
                        dst->mDup18 = 1;
                    u++;
                    p++;
                } while (u < (unsigned)mCount);
            }

            dst->mpOwner = i4;
            dst->mKey4 = local_20;
            dst->mKey8 = local_24;
            dst->mFlags16 = (unsigned short)flags;
            if (flags & 0x800)
                dst->mf10 = -dst->mf10;
            mCount++;
            if ((flags & 0x2000) == 0)
                i4->mpFn(0x5ece0000, dst, i4->mpData);
            if (local_24 != 0 && (flags & 0x1000) == 0) {
                char c = i4->mpIface->slotC((void*)local_24, this);
                if (c != 0) {
                    RunRec tmp;
                    tmp.mpOwner = i4;
                    tmp.mKey4 = local_24;
                    tmp.mKey8 = local_24;
                    tmp.mKeyC = 0;
                    tmp.mf10 = 0.0f;
                    tmp.mb14 = dst->mb14;
                    tmp.mb15 = dst->mb15;
                    tmp.mFlags16 = 0x1000;
                    tmp.mDup18 = 0;
                    FUN_008d3e30(&tmp, 1);
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d4040
// Binary search an intrusive list ordered by each node's key at +8.
// ---------------------------------------------------------------------------
void* FUN_008d4040(void** pOut, void* head, void* tail, void* key, void* unused)
{
    int n = 0;
    for (void* p = head; p != tail; p = *(void**)p)
        n++;
    if (n > 0) {
        int half;
        do {
            half = n >> 1;
            int i = half;
            void* p = head;
            if (half < 0) {
                i = -half;
                do {
                    i--;
                    p = *((void**)p + 1);
                } while (i != 0);
            } else {
                for (; i != 0; i--)
                    p = *(void**)p;
            }
            if (*(int*)((char*)p + 8) <= *(int*)((char*)key + 8)) {
                head = *(void**)p;
                half = n + (-1 - half);
            }
            n = half;
        } while (half > 0);
    }
    *pOut = head;
    (void)unused;
    return pOut;
}

// ---------------------------------------------------------------------------
// @ 0x008d40b0 (non-matching)
// ---------------------------------------------------------------------------
void FUN_008d40b0(int param_1, int param_2, int param_3)
{
    int i1, i2, i3;
    i1 = param_2 - param_1 >> 4;
    if (2 <= i1) {
        i3 = (i1 - 2 >> 1) + 1;
        i2 = i3 * 0x10 + param_1;
        do {
            i3 = i3 - 1;
            FUN_008d3b70(param_1, i3, i1, i3,
                         *(unsigned*)(i2 - 0x10), *(unsigned*)(i2 - 0xc),
                         *(unsigned*)(i2 - 8), *(unsigned*)(i2 - 4), param_3);
            i2 = i2 - 0x10;
        } while (i3 != 0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d4110 (non-matching)
// ---------------------------------------------------------------------------
void FUN_008d4110(unsigned* param_1, int param_2, int param_3)
{
    unsigned u1, u2, u3, u4;
    int i5;
    unsigned* p6;
    i5 = param_2 - (int)param_1 >> 4;
    if (1 < i5) {
        p6 = (unsigned*)(param_2 - 0x10);
        do {
            u1 = p6[3]; u2 = p6[0]; u3 = p6[1]; u4 = p6[2];
            p6[0] = param_1[0]; p6[1] = param_1[1]; p6[2] = param_1[2]; p6[3] = param_1[3];
            FUN_008d3b70((int)param_1, 0, i5 - 1, 0, u2, u3, u4, u1, param_3);
            p6 = p6 - 4;
            i5 = (0x10 - (int)param_1) + (int)p6 >> 4;
        } while (1 < i5);
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d41b0
// Reinsert a run node in key order, then drop every run it no longer matches.
// ---------------------------------------------------------------------------
void TSI::FUN_008d41b0(OwnerNode* node)
{
    OwnerNode* orig = node;
    FUN_008d4040((void**)&node, (void*)mpNext, (void*)this, (void*)orig, (void*)orig);

    OwnerNode* ins = node;
    OwnerNode* pv = ins->mpPrev;
    ins->mpPrev = orig;
    pv->mpNext = orig;
    orig->mpPrev = pv;
    orig->mpNext = ins;

    unsigned u = 0;
    if (mCount != 0) {
        RunRec* r = mRuns;
        do {
            int localA, localB;
            OwnerNode* found = FUN_008d3dc0(r, (int*)&node, &localA, &localB);
            if ((OwnerNode*)r->mpOwner == found && (OwnerNode*)r->mKey4 == node) {
                u++;
                r++;
            } else {
                FUN_008d35d0(r, 0x5ece0002);
            }
        } while (u < (unsigned)mCount);
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d4250 (non-matching)
// ---------------------------------------------------------------------------
void FUN_008d4250(unsigned* param_1, unsigned* param_2, unsigned param_3, unsigned param_4,
                 unsigned param_5)
{
    unsigned u1, u2, u3, u4;
    unsigned* p5;
    unsigned short u6;
    bool b;
    while (true) {
        while (true) {
            b = *param_1 < param_3;
            u6 = (unsigned short)param_5;
            if (*param_1 == param_3) {
                b = (unsigned short)(param_5 >> 0x10) <= *(unsigned short*)((int)param_1 + 10);
                if (*(unsigned short*)((int)param_1 + 10) == (unsigned short)(param_5 >> 0x10)) {
                    b = u6 <= (unsigned short)param_1[2];
                    if ((unsigned short)param_1[2] == u6)
                        b = param_1[1] < param_4;
                }
            }
            if (!b) break;
            param_1 = param_1 + 4;
        }
        do {
            p5 = param_2;
            param_2 = p5 - 4;
            b = param_3 < p5[-4];
            if (param_3 == p5[-4]) {
                b = *(unsigned short*)((int)p5 - 6) <= (unsigned short)(param_5 >> 0x10);
                if ((unsigned short)(param_5 >> 0x10) == *(unsigned short*)((int)p5 - 6)) {
                    if (u6 == (unsigned short)p5[-2])
                        b = param_4 < p5[-3];
                    else
                        b = (unsigned short)p5[-2] < u6;
                }
            }
        } while (b);
        if (param_2 <= param_1) break;
        u1 = *param_1; u2 = param_1[1]; u3 = param_1[2]; u4 = param_1[3];
        *param_1 = *param_2;
        param_1[1] = p5[-3]; param_1[2] = p5[-2]; param_1[3] = p5[-1];
        *param_2 = u1;
        p5[-3] = u2; p5[-2] = u3; p5[-1] = u4;
        param_1 = param_1 + 4;
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d4320 (non-matching)
// ---------------------------------------------------------------------------
void FUN_008d4320(unsigned* param_1, unsigned* param_2, unsigned* param_3, int param_4)
{
    unsigned u1, u2, u3, u4;
    unsigned* p5;
    bool b;
    FUN_008d40b0((int)param_1, (int)param_2, param_4);
    for (p5 = param_2; p5 < param_3; p5 = p5 + 4) {
        b = *p5 < *param_1;
        if (*p5 == *param_1) {
            b = *(unsigned short*)((int)param_1 + 10) <= *(unsigned short*)((int)p5 + 10);
            if (*(unsigned short*)((int)p5 + 10) == *(unsigned short*)((int)param_1 + 10)) {
                b = (unsigned short)param_1[2] <= (unsigned short)p5[2];
                if ((unsigned short)p5[2] == (unsigned short)param_1[2])
                    b = p5[1] < param_1[1];
            }
        }
        if (b) {
            u1 = *p5; u2 = p5[1]; u3 = p5[2]; u4 = p5[3];
            *p5 = *param_1;
            p5[1] = param_1[1]; p5[2] = param_1[2]; p5[3] = param_1[3];
            FUN_008d3b70((int)param_1, 0, ((int)param_2 - (int)param_1) >> 4, 0, u1, u2, u3, u4,
                         param_4);
        }
    }
    FUN_008d4110(param_1, (int)param_2, param_4);
}

// ---------------------------------------------------------------------------
// @ 0x008d4400
// Grow (or shift within) the 0x10-byte-element vector core.
// ---------------------------------------------------------------------------
void VecCore::grow(void* p, void* value)
{
    void* e = end;
    if (e != cap) {
        if (p <= value && value < e)
            value = (char*)value + 0x10;
        if (e != 0) {
            ((int*)e)[0] = ((int*)e)[-4];
            ((int*)e)[1] = ((int*)e)[-3];
            ((int*)e)[2] = ((int*)e)[-2];
            ((int*)e)[3] = ((int*)e)[-1];
        }
        FUN_00edba80(p, (char*)end - 0x10, end);
        ((int*)p)[0] = ((int*)value)[0];
        ((int*)p)[1] = ((int*)value)[1];
        ((int*)p)[2] = ((int*)value)[2];
        ((int*)p)[3] = ((int*)value)[3];
        end = (char*)end + 0x10;
        return;
    }

    int n = (int)((char*)e - (char*)begin) >> 4;
    int cap2;
    if (n == 0) {
        n = 1;
        cap2 = (int)alloc->allocate((unsigned)(n << 4), 0, name);
    } else {
        n = n * 2;
        if (n == 0)
            cap2 = 0;
        else
            cap2 = (int)alloc->allocate((unsigned)(n << 4), 0, name);
    }
    void* dst = FUN_00c7ea30(begin, p, (void*)cap2);
    if (dst != 0) {
        ((int*)dst)[0] = ((int*)value)[0];
        ((int*)dst)[1] = ((int*)value)[1];
        ((int*)dst)[2] = ((int*)value)[2];
        ((int*)dst)[3] = ((int*)value)[3];
    }
    void* ne = FUN_00c7ea30(p, end, (char*)dst + 0x10);
    if (begin != 0)
        alloc->deallocate(begin, (unsigned)((((int)cap - (int)begin) >> 4) << 4));
    end = ne;
    cap = (char*)cap2 + (n << 4);
    begin = (void*)cap2;
}
