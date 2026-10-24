// Slice s00b45170: Spore engine routines.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

// --------------------------------------------------------------- callees

extern "C" void     FUN_00f47380(void* p);
extern "C" void*    FUN_00f473a0(unsigned size, void* name, int p1, int p2, void* file, int line);
extern "C" void*    FUN_0067dcc0();
extern "C" void     FUN_00b4d720();
extern "C" void     FUN_00b5a390();
extern "C" void     FUN_00b54340(void* a, void* b, void* c);
extern "C" void     FUN_00b544c0(void* a, void* b);
extern "C" void     FUN_00b544f0(void* a, void* b);
extern "C" void     FUN_00b3f260(void** outEnd, void* first, void* last, void* mem, void* src);
extern "C" unsigned FUN_00b54520(void* a);

extern void*         gHashOwner;      // 0x0167eb70
extern unsigned char gFlag167eb75;    // 0x0167eb75

// ----------------------------------------------------------------- types

struct V3f { float x, y, z; };

struct cIter {
    void*         mNode;      // 0x00
    void**        mBucket;    // 0x04
    unsigned char mInserted;  // 0x08
};

struct cRehashResult {
    unsigned char mFlag;      // 0x00
    char          mPad01[3];
    int           mNewCount;  // 0x04
};

struct cHtNode {
    void* mKey;               // 0x00
    void* mNext;              // 0x04
};

struct cValNode {
    void* mKey;               // 0x00
    void* mValue;             // 0x04
};

struct cVal {
    int           mPad00;     // 0x00
    int           mPad04;     // 0x04
    int           mPad08;     // 0x08
    int           mPad0c;     // 0x0c
    int           mPad10;     // 0x10
    int           mPad14;     // 0x14
    int           mPad18;     // 0x18
    float         mF1c;       // 0x1c
    float         mF20;       // 0x20
    float         mF24;       // 0x24
    int           mPad28;     // 0x28
    int           mPad2c;     // 0x2c
    int           mPad30;     // 0x30
    unsigned char mFlag34;    // 0x34
    char          mPad35[3];
    int           mField38;   // 0x38
    int           mField3c;   // 0x3c

    void SetValue(void* p);                // 0x00b3dec0
};

struct cValH {
    void Register(void* a, void* b);       // 0x00c446d0
};

struct cRehash16 {
    int mPad00;               // 0x00
    int mPad04;               // 0x04
    int mPad08;               // 0x08

    void Make(void* out, int bucketCount, int nodeCount, int flag);  // 0x00921440
};

struct cHash16 {
    int    mPad00;            // 0x00
    void** mBuckets;          // 0x04
    int    mBucketCount;      // 0x08
    int    mNodeCount;        // 0x0c
    int    mPad10;            // 0x10
    int    mPad14;            // 0x14
    int    mPad18;            // 0x18

    void Destroy();                            // 0x00c2e4e0
    void SetBuckets(void* buckets, int count); // 0x00693230
    void FreeNodes(void* buckets, int count);  // 0x007611f0
    void Find(void* out, void* key);           // 0x00645ed0
};

struct cHash30 {
    int       mPad00;         // 0x00
    void**    mBuckets;       // 0x04
    int       mBucketCount;   // 0x08
    int       mNodeCount;     // 0x0c
    cRehash16 mRehash;        // 0x10
    void*     mFreeList;      // 0x1c
    int       mPad20;         // 0x20
    void*     mPoolLo;        // 0x24
    void*     mPoolHi;        // 0x28
    int       mPad2c;         // 0x2c
    void*     mSentinel;      // 0x30

    int   Remove(void* keyPtr);               // 0x00b45ab0
    cIter Insert(void* keyPtr, void* arg2);   // 0x00b45b50
    void* NewNode(void* keyPtr);              // 0x00b41dc0
    void  Resize(int count);                  // 0x00ef7c00
};

struct cObj42760 {
    int GetVec(V3f* dst, V3f* src, void* arg);   // 0x00b42760
};

struct cVec3c {
    void* mBegin;             // 0x00
    void* mEnd;               // 0x04
    void* mCap;               // 0x08

    void* InitCopy(const cVec3c* src);        // 0x00b45c10
};

// stub vtables (target slot reached by offset/4)
struct cIface2c {
    virtual void d00() {} virtual void d01() {} virtual void d02() {} virtual void d03() {}
    virtual void d04() {} virtual void d05() {} virtual void d06() {} virtual void d07() {}
    virtual void d08() {} virtual void d09() {} virtual void d10() {}
    virtual void Send(void* sender, int msg, int param) {}
};

struct cIfaceB8 {
    virtual void d00() {} virtual void d01() {} virtual void d02() {} virtual void d03() {}
    virtual void d04() {} virtual void d05() {} virtual void d06() {} virtual void d07() {}
    virtual void d08() {} virtual void d09() {} virtual void d10() {} virtual void d11() {}
    virtual void d12() {} virtual void d13() {} virtual void d14() {} virtual void d15() {}
    virtual void d16() {} virtual void d17() {} virtual void d18() {} virtual void d19() {}
    virtual void d20() {} virtual void d21() {} virtual void d22() {} virtual void d23() {}
    virtual void d24() {} virtual void d25() {} virtual void d26() {} virtual void d27() {}
    virtual void d28() {} virtual void d29() {} virtual void d30() {} virtual void d31() {}
    virtual void d32() {} virtual void d33() {} virtual void d34() {} virtual void d35() {}
    virtual void d36() {} virtual void d37() {} virtual void d38() {} virtual void d39() {}
    virtual void d40() {} virtual void d41() {} virtual void d42() {} virtual void d43() {}
    virtual void d44() {} virtual void d45() {}
    virtual void* Get(int param) { return 0; }
};

struct cKeyObj {
    virtual void d00() {} virtual void d01() {} virtual void d02() {} virtual void d03() {}
    virtual void d04() {} virtual void d05() {} virtual void d06() {} virtual void d07() {}
    virtual void d08() {} virtual void d09() {} virtual void d10() {} virtual void d11() {}
    virtual void d12() {} virtual void d13() {} virtual void d14() {} virtual void d15() {}
    virtual void d16() {} virtual void d17() {} virtual void d18() {} virtual void d19() {}
    virtual void d20() {} virtual void d21() {} virtual void d22() {} virtual void d23() {}
    virtual void d24() {} virtual void d25() {} virtual void d26() {} virtual void d27() {}
    virtual void d28() {} virtual void d29() {} virtual void d30() {} virtual void d31() {}
    virtual void d32() {} virtual void d33() {} virtual void d34() {} virtual void d35() {}
    virtual void d36() {} virtual void d37() {} virtual void d38() {} virtual void d39() {}
    virtual void d40() {} virtual void d41() {} virtual void d42() {} virtual void d43() {}
    virtual void d44() {} virtual void d45() {} virtual void d46() {} virtual void d47() {}
    virtual void Destroy() {}
};

struct cObj45170 {
    char     mPad00[8];       // 0x00 .. 0x07
    cHash16  mSub08;          // 0x08 .. 0x23
    void*    mPtr24;          // 0x24
    char     mPad28[0x14];    // 0x28 .. 0x3b
    cHash16  mSub3c;          // 0x3c .. 0x57
    cHash16  mSub58;          // 0x58 .. 0x73
    char     mPad74[4];       // 0x74
    void*    mPtr78;          // 0x78
    char     mPad7c[0x14];    // 0x7c .. 0x8f
    void*    mPtr90;          // 0x90

    void Destroy();                          // 0x00b45170
};

struct cObj451f0 {
    char     mPad00[0x3c];    // 0x00 .. 0x3b
    cHash16  mHash3c;         // 0x3c

    void OnEvent();                          // 0x00b451f0
};

struct cObj452b0 {
    char     mPad00[0x40];    // 0x00 .. 0x3f
    cHash16  mHash40;         // 0x40

    void F();                                // 0x00b452b0
};

struct cObj452xx {
    char mPad00[0x20];        // 0x00 .. 0x1f
    int  mMode20;             // 0x20

    void     Dispatch(void* p2, void* p3, void* p4);   // 0x00b452f0
    void     Mode0A(void* p2);                         // 0x00b453a0
    void     Mode0B(void* p2);                         // 0x00b45410
    unsigned GetFlag(void* p2);                        // 0x00b45480
};

struct cFOut {
    V3f  v0;                  // 0x000 .. 0x00b
    char mPad0c[0xb4];        // 0x00c .. 0x0bf
    V3f  vc0;                 // 0x0c0 .. 0x0cb
    char mPadcc[0xb4];        // 0x0cc .. 0x17f
    union {
        int   i;
        float f;
    }    mField180;           // 0x180
    V3f  v184;                // 0x184
    V3f  v190;                // 0x190
    V3f  v19c;                // 0x19c
};

struct cObj45540 {
    int  mPad00;              // 0x000
    V3f  mFirst[0x20];        // 0x004 .. 0x183
    V3f  mSecond[0x20];       // 0x184 .. 0x303
    int  mCount1;             // 0x304
    int  mCount2;             // 0x308
    int  mPad30c;             // 0x30c

    bool  Build(void* p2, void* p3, float* p4, float* p5, cFOut* p6);   // 0x00b45540
    int Sub860(V3f* a, V3f* b, V3f* c, void* d, void* e);            // 0x00b3e860
    int Sub980(V3f* a, V3f* b, V3f* c, V3f* d, void* e, void* f);    // 0x00b3e980
    int Sub1900(V3f* a, int n, V3f* b, int m, void* c, void* d);     // 0x00b41900
};

// ------------------------------------------------------------ 0x00b45170

// @ 0x00b45170  (116 bytes)
void cObj45170::Destroy()
{
    if (mPtr90 != 0) FUN_00f47380(mPtr90);
    if (mPtr78 != 0) FUN_00f47380(mPtr78);

    mSub58.SetBuckets(mSub58.mBuckets, mSub58.mBucketCount);
    mSub58.mNodeCount = 0;
    if ((unsigned)mSub58.mBucketCount > 1u) FUN_00f47380(mSub58.mBuckets);

    mSub3c.Destroy();
    if (mPtr24 != 0) FUN_00f47380(mPtr24);
    mSub08.Destroy();
}

// ------------------------------------------------------------ 0x00b451f0

// @ 0x00b451f0  (178 bytes)
void cObj451f0::OnEvent()
{
    if (FUN_0067dcc0() != 0)
    {
        void* sender = (char*)this - 4;

        cIface2c* o = (cIface2c*)FUN_0067dcc0();
        o->Send(sender, 0x182c582, 0xffffd8f1);
        o = (cIface2c*)FUN_0067dcc0();
        o->Send(sender, 0x1a0219e, 0xffffd8f1);
        o = (cIface2c*)FUN_0067dcc0();
        o->Send(sender, 0x25630b7, 0xffffd8f1);
        o = (cIface2c*)FUN_0067dcc0();
        o->Send(sender, 0x31018b9, 0xffffd8f1);
        o = (cIface2c*)FUN_0067dcc0();
        o->Send(sender, 0xf62def, 0xffffd8f1);
    }

    FUN_00b4d720();

    mHash3c.FreeNodes(mHash3c.mBuckets, mHash3c.mBucketCount);
    mHash3c.mNodeCount = 0;
}

// ------------------------------------------------------------ 0x00b452b0

// @ 0x00b452b0  (51 bytes)
void cObj452b0::F()
{
    if (gFlag167eb75 != 0) gFlag167eb75 = 0;

    FUN_00b5a390();

    mHash40.FreeNodes(mHash40.mBuckets, mHash40.mBucketCount);
    mHash40.mNodeCount = 0;
}

// ------------------------------------------------------------ 0x00b452f0

// @ 0x00b452f0  (172 bytes)
void cObj452xx::Dispatch(void* p2, void* p3, void* p4)
{
    if (mMode20 == 0)
    {
        FUN_00b54340(p2, p3, p4);
        return;
    }

    if (p2 != 0)
    {
        void* r = ((cIfaceB8*)p2)->Get(0x116dd1b);
        if (r != 0)
        {
            ((cValH*)r)->Register(p3, 0);
            return;
        }
    }

    if (mMode20 == 1)
    {
        cHash16* ht = (cHash16*)((char*)gHashOwner + 0x58);
        void* node = 0;
        ht->Find(&node, &p2);
        if (node != ht->mBuckets[ht->mBucketCount])
        {
            cVal* v = (cVal*)((cValNode*)node)->mValue;
            v->SetValue(p3);
            v->mFlag34 = 0;
        }
    }
}

// ------------------------------------------------------------ 0x00b453a0

// @ 0x00b453a0  (103 bytes)
void cObj452xx::Mode0A(void* p2)
{
    int m = mMode20;

    if (m == 0)
    {
        FUN_00b544c0(p2, 0);
        return;
    }
    if (m - 1 != 0) return;

    cHash16* ht = (cHash16*)((char*)gHashOwner + 0x58);
    void* node = 0;
    ht->Find(&node, &p2);
    if (node != ht->mBuckets[ht->mBucketCount])
    {
        cVal* v = (cVal*)((cValNode*)node)->mValue;
        v->mField38 = v->mField3c;
    }
}

// ------------------------------------------------------------ 0x00b45410

// @ 0x00b45410  (104 bytes)
void cObj452xx::Mode0B(void* p2)
{
    int m = mMode20;

    if (m == 0)
    {
        FUN_00b544f0(p2, 0);
        return;
    }
    if (m - 1 != 0) return;

    cHash16* ht = (cHash16*)((char*)gHashOwner + 0x58);
    void* node = 0;
    ht->Find(&node, &p2);
    if (node != ht->mBuckets[ht->mBucketCount])
    {
        cVal* v = (cVal*)((cValNode*)node)->mValue;
        v->mField38 = 0;
    }
}

// ------------------------------------------------------------ 0x00b45480

// @ 0x00b45480  (180 bytes)
unsigned cObj452xx::GetFlag(void* p2)
{
    int m = mMode20;

    if (m == 0) return FUN_00b54520(p2);

    unsigned r = (unsigned)(m - 1);

    if (r == 0)
    {
        cHash16* ht = (cHash16*)((char*)gHashOwner + 0x58);
        void* node = 0;
        ht->Find(&node, &p2);
        if (node != ht->mBuckets[ht->mBucketCount])
        {
            cVal* v = (cVal*)((cValNode*)node)->mValue;
            float s = v->mF1c * v->mF1c + v->mF20 * v->mF20 + v->mF24 * v->mF24;
            return (s > 1.52587890625e-05f) ? 1u : 0u;
        }
        r = (unsigned)node;
    }

    return r & 0xffffff00u;
}

// ------------------------------------------------------------ 0x00b45540

// @ 0x00b45540  (1391 bytes)
bool cObj45540::Build(void* p2, void* p3, float* p4, float* p5, cFOut* p6)
{
    V3f neg;
    neg.x = -p6->v184.x;
    neg.y = -p6->v184.y;
    neg.z = -p6->v184.z;

    int c1 = ((cObj42760*)p2)->GetVec(&neg, &mFirst[0], p3);
    mCount1 = c1;
    int c2 = ((cObj42760*)p3)->GetVec(&p6->v184, &mSecond[0], p2);
    mCount2 = c2;

    for (int i = 0; i < mCount1; i++)
    {
        float f = p6->v190.x;
        mFirst[i].x += p4[0] * f;
        mFirst[i].y += p4[1] * f;
        mFirst[i].z += p4[2] * f;
    }

    for (int i = 0; i < mCount2; i++)
    {
        float f = p6->v190.x;
        mSecond[i].x += p5[0] * f;
        mSecond[i].y += p5[1] * f;
        mSecond[i].z += p5[2] * f;
    }

    c1 = mCount1;
    c2 = mCount2;

    if (c1 == 1)
    {
        if (c2 == 1)
        {
            p6->v0 = mFirst[0];
            p6->vc0 = mSecond[0];
            p6->mField180.i = 1;
            return true;
        }

        if (c2 == 2)
        {
            p6->mField180.i = Sub860(&mFirst[0], &mSecond[0], &mSecond[1], p6, &p6->vc0);
            return true;
        }

        // cross-product block (V1 = mSecond[1], V2 = mSecond[2], V3 = mSecond[0])
        V3f& V1 = mSecond[1];
        V3f& V2 = mSecond[2];
        V3f& V3 = mSecond[0];
        V3f& A  = mFirst[0];

        float dx = V2.x - V1.x;
        float dy = V2.y - V1.y;
        float dz = V2.z - V1.z;
        float ex = V1.x - V3.x;
        float ey = V1.y - V3.y;
        float ez = V1.z - V3.z;

        float py = ez * dx - dz * ex;
        float pz = dy * ex - ey * dx;
        float px = dz * ey - dy * ez;

        double s2 = (double)pz * pz + (double)py * py + (double)px * px;
        float n = (float)(1.0 / sqrt(s2));
        px *= n;
        py *= n;
        pz *= n;

        float dot = ((A.x * px + A.z * pz) + A.y * py) - ((V3.z * pz + V3.y * py) + V3.x * px);

        p6->v0.x = A.x;
        p6->v0.y = A.y;
        p6->v0.z = A.z;
        p6->vc0.x = A.x - px * dot;
        p6->vc0.y = A.y - py * dot;
        p6->vc0.z = A.z - pz * dot;
        p6->mField180.i = 1;
        return true;
    }

    if (c1 == 2)
    {
        if (c2 == 1)
        {
            p6->mField180.i = Sub860(&mSecond[0], &mFirst[0], &mFirst[1], &p6->vc0, p6);
            return true;
        }

        if (c2 == 2)
        {
            p6->mField180.i = Sub980(&mFirst[0], &mFirst[1], &mSecond[0], &mSecond[1], p6, &p6->vc0);
            return true;
        }

        p6->mField180.i = Sub1900(&mSecond[0], c2, &mFirst[0], 2, &p6->vc0, p6);
        return true;
    }

    if (c2 == 1)
    {
        // cross-product block (V1 = mFirst[1], V2 = mFirst[2], V3 = mSecond[0])
        V3f& V1 = mFirst[1];
        V3f& V2 = mFirst[2];
        V3f& V3 = mSecond[0];
        V3f& A  = mFirst[0];

        float dx = V2.x - V1.x;
        float dy = V2.y - V1.y;
        float dz = V2.z - V1.z;
        float ex = V1.x - V3.x;
        float ey = V1.y - V3.y;
        float ez = V1.z - V3.z;

        float py = ez * dx - dz * ex;
        float pz = dy * ex - ey * dx;
        float px = dz * ey - dy * ez;

        double s2 = (double)pz * pz + (double)py * py + (double)px * px;
        float n = (float)(1.0 / sqrt(s2));
        px *= n;
        py *= n;
        pz *= n;

        float dot = ((V3.z * pz + V3.y * py) + V3.x * px) - ((A.z * pz + A.y * py) + px * A.x);

        p6->vc0.x = V3.x;
        p6->vc0.y = V3.y;
        p6->vc0.z = V3.z;
        p6->v0.x = V3.x - px * dot;
        p6->v0.y = V3.y - py * dot;
        p6->v0.z = V3.z - pz * dot;
        p6->mField180.i = 1;
        return true;
    }

    p6->mField180.i = Sub1900(&mFirst[0], c1, &mSecond[0], c2, p6, &p6->vc0);
    return true;
}

// ------------------------------------------------------------ 0x00b45ab0

// @ 0x00b45ab0  (153 bytes)
int cHash30::Remove(void* keyPtr)
{
    int   before = mNodeCount;
    void* key    = *(void**)keyPtr;

    void** slot = &mBuckets[(unsigned)key % (unsigned)mBucketCount];
    void*  node = *slot;

    while (node != 0)
    {
        cHtNode* n = (cHtNode*)node;

        if (n->mKey == key)
        {
            *slot = n->mNext;

            if (n->mKey != 0) ((cKeyObj*)n->mKey)->Destroy();

            if (node != mSentinel)
            {
                if (node < mPoolLo || node >= mPoolHi)
                {
                    FUN_00f47380(node);
                }
                else
                {
                    n->mKey     = mFreeList;
                    mFreeList   = node;
                }
            }

            mNodeCount--;
            node = *slot;
            continue;
        }

        slot = &n->mNext;
        node = *slot;
    }

    return before - mNodeCount;
}

// ------------------------------------------------------------ 0x00b45b50

// @ 0x00b45b50  (186 bytes)
cIter cHash30::Insert(void* keyPtr, void* arg2)
{
    cIter out;

    void* key = *(void**)keyPtr;

    unsigned idx  = (unsigned)key % (unsigned)mBucketCount;
    cHtNode* node = (cHtNode*)mBuckets[idx];

    while (node != 0)
    {
        if (node->mKey == key)
        {
            out.mNode     = node;
            out.mBucket   = &mBuckets[idx];
            out.mInserted = 0;
            return out;
        }
        node = (cHtNode*)node->mNext;
    }

    cRehashResult r;
    mRehash.Make(&r, mBucketCount, mNodeCount, 1);

    cHtNode* nn  = (cHtNode*)NewNode(keyPtr);
    unsigned idx2 = idx;

    if (r.mFlag != 0)
    {
        idx2 = (unsigned)key % (unsigned)r.mNewCount;
        Resize(r.mNewCount);
    }

    nn->mNext      = mBuckets[idx2];
    mBuckets[idx2] = nn;
    mNodeCount++;

    out.mNode     = nn;
    out.mBucket   = &mBuckets[idx2];
    out.mInserted = 1;
    return out;
}

// ------------------------------------------------------------ 0x00b45c10

// @ 0x00b45c10  (137 bytes)
void* cVec3c::InitCopy(const cVec3c* src)
{
    unsigned count = (unsigned)((int)((char*)src->mEnd - (char*)src->mBegin) / 0x3c);
    void*    mem   = 0;

    if (count != 0)
    {
        mem = FUN_00f473a0(count * 0x3c, (void*)0x13f09b4, 0, 0, (void*)0x13ebb38, 0xd1);
    }

    mCap   = (char*)mem + count * 0x3c;
    mBegin = mem;
    mEnd   = mem;

    void* out = (void*)src;
    FUN_00b3f260(&out, src->mBegin, src->mEnd, mem, (void*)src);
    mEnd = out;

    return this;
}