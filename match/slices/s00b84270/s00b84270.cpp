// s00b84270 (gold7): cModelTestCheat::Execute plus the eastl vector / hash-map
// helpers it uses.  Retail member offsets are read from the disassembly; objects
// are modelled locally with role-named members at those offsets.
//
//   00b84270  cModelTestCheat::Execute            (thiscall, bool)
//   00b848f0  HashMap::Insert                     (thiscall, ret 0xc)
//   00b849e0  U16Vec::Reserve                     (thiscall, ret 4)
//   00b84b10  Vec18Vec::CopyCtor                  (thiscall, ret 4)
//   00b84cb0  Vec0CVec::insert(pos,first,last)    (thiscall, ret 0x10)
//   00b84e90  Vec18Vec::insert(pos,count,value)   (thiscall, ret 0xc)
//   00b850c0  UninitCopy1C                        (cdecl)
//   00b85110  ScalarList::~ScalarList             (thiscall)
//   00b85220  Vec18Vec::insert(pos,value)         (thiscall, ret 8)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <new>

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;

#pragma warning(disable: 4100)

#define VTC(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

// --------------------------------------------------------------- extern decls
extern "C" void *operator_new(u32 n, const char *pFile, int a, int b,
                              const char *pAlloc, int line);            // 0x00f473a0
#define OPERATOR_NEW(n) operator_new((n), "Simulator", 0, 0, (const char *)0x013ebb38, 0xd1)
extern "C" void  operator_delete_array(void *p);                        // 0x00f47380
extern "C" void *memcpy(void *d, const void *s, u32 n);                 // 0x011e0744
extern "C" void *memset(void *d, int c, u32 n);                         // 0x011e073e

// eastl uninitialised_copy over an output iterator: writes the advanced dest to
// *out (5th arg is a tag the retail callee ignores).
extern "C" void  FUN_00b7f5c0(void *out, void *first, void *last, void *dst, void *tag); // 0x00b7f5c0
// eastl fill_n of 0x18-byte elements: *dst++ = *src for count elements.
extern "C" void  FUN_00b7f860(void *dst, u32 count, const void *src, void *tag);          // 0x00b7f860
// eastl copy of 0x18-byte elements [first,last) -> dst, returns advanced dst.
extern "C" void *FUN_00b7f630(const void *first, const void *last, void *dst);            // 0x00b7f630
// eastl copy_backward of 0x18-byte elements.
extern "C" void  FUN_00cc8b50(void *first, void *last, void *dstEnd);                     // 0x00cc8b50
// eastl fill of 0x18-byte elements [first,last) with *src.
extern "C" void  FUN_007144b0(void *first, void *last, const void *src);                  // 0x007144b0
// eastl uninitialised_copy of 0xc-byte elements.
extern "C" void  FUN_00898b80(void *out, void *first, void *last, void *dst, void *tag);  // 0x00898b80
// eastl copy_backward of 0xc-byte elements.
extern "C" void  FUN_00abced0(void *first, void *last, void *dstEnd);                     // 0x00abced0
// eastl copy of 0xc-byte elements [first,last) -> dst.
extern "C" void  FUN_00b84c80(void *first, void *last, void *dst);                        // 0x00b84c80
// copy [first,last) into dst, returns the advanced dst.
extern "C" void *FUN_00a11310(void *first, void *last, void *dst);                        // 0x00a11310
// hash-table node allocation (node pool free-list / operator_new).
extern "C" void *FUN_00b83b70(void *self, const void *src);                               // 0x00b83b70
// rehash the bucket array.
extern "C" void  FUN_00b7f510(void *self, u32 n);                                         // 0x00b7f510
// eastl prime_rehash_policy::calcRehash (thiscall on the policy at +0x10).
extern "C" void  FUN_00921440(void *self, void *out, u32 bucketCount, u32 elementCount, int arg); // 0x00921440

// -------------------------------------------------------- scalar-list dtor helper
// eastl::vector<IntVectorElem>::~vector([begin,end)); the image models it as a
// __thiscall on the embedded vector (ecx = the vector), so it is declared as a
// member of IntVec below to reproduce the exact direct call.

static inline bool BlockIsOurs(const void *p)
{
    return p != 0 && ((const u32 *)p)[-1] != 0;
}

// ---------------------------------------------------------------------------
// element types
// ---------------------------------------------------------------------------
struct Vec3f { float x, y, z; };

// 0x18-byte ragged element: {int; float; float; float; char; char; <pad2>; int}
struct Elem18 {
    u32   m0;      // +0x00
    float f4;      // +0x04
    float f8;      // +0x08
    float fc;      // +0x0c
    u8    b10;     // +0x10
    u8    b11;     // +0x11
    u16   pad12;   // +0x12
    u32   m14;     // +0x14
};

// 0xc-byte element.
struct Elem0C { u32 m0, m4, m8; };

// ===========================================================================
// 0x00b848f0  eastl hashtable::insert (unique key), key = 3 dwords
// ===========================================================================
struct HashNode {
    u32 m0, m4, m8, mc, m10, m14, m18, m1c;
    HashNode *mpNext;          // +0x20
};

struct RehashPolicy {
    float mfMaxLoadFactor;     // +0x00
    float mfGrowthFactor;      // +0x04
    u32   mnNextResize;        // +0x08
    void CalcRehash(void *out, u32 bucketCount, u32 elementCount, int arg);  // modelled 0x00921440
};

struct RehashResult {
    u8  mbFlag;                // +0x00
    u8  pad01[3];
    u32 mnNewBucketCount;      // +0x04
};

struct InsertResult {
    HashNode  *mpNode;         // +0x00
    HashNode **mpBucket;       // +0x04
    u8         mbInserted;     // +0x08
};

struct HashMap {
    u32        mField00;       // +0x00
    HashNode **mpBuckets;      // +0x04
    u32        mnBucketCount;  // +0x08
    u32        mnElementCount; // +0x0c
    RehashPolicy mPolicy;      // +0x10
    u32        mField1c;       // +0x1c

    void Insert(InsertResult *out, const u32 *key, void *unused);   // 0x00b848f0
    void *AllocNode(const void *src);                               // modelled 0x00b83b70
    void Rehash(u32 n);                                             // modelled 0x00b7f510
};

// @ 0x00b848f0
void HashMap::Insert(InsertResult *out, const u32 *key, void *unused)
{
    u32 h = key[0] * 0x25 + key[1] + key[2] * 0xfd;
    u32 n = h % mnBucketCount;
    HashNode **pBucket = mpBuckets + n;
    HashNode *pNode = *pBucket;
    while (pNode != 0) {
        if (pNode->m0 == key[0] && pNode->m4 == key[1] && pNode->m8 == key[2])
            break;
        pNode = pNode->mpNext;
    }
    if (pNode == 0) {
        RehashResult rr;
        mPolicy.CalcRehash(&rr, mnBucketCount, mnElementCount, 1);
        pNode = (HashNode *)AllocNode(key);
        if (rr.mbFlag) {
            n = h % rr.mnNewBucketCount;
            Rehash(rr.mnNewBucketCount);
        }
        HashNode **pSlot = mpBuckets + n;
        pNode->mpNext = *pSlot;
        *pSlot = pNode;
        ++mnElementCount;
        out->mpNode = pNode;
        out->mbInserted = 1;
        out->mpBucket = pSlot;
    } else {
        out->mpNode = pNode;
        out->mbInserted = 0;
        out->mpBucket = pBucket;
    }
}

// ===========================================================================
// 0x00b849e0  eastl vector<u16>::reserve(n)
// ===========================================================================
struct U16Vec {
    u16 *mpBegin;      // +0x00
    u16 *mpEnd;        // +0x04
    u16 *mpCap;        // +0x08

    void Reserve(u32 n);   // 0x00b849e0
};

// @ 0x00b849e0
void U16Vec::Reserve(u32 n)
{
    u32 capCount = (u32)(mpCap - mpBegin);
    if (n > capCount) {
        u16 *pNew;
        if (n != 0)
            pNew = (u16 *)OPERATOR_NEW(n * 2);
        else
            pNew = 0;
        memcpy(pNew, mpBegin, (u32)((u8 *)mpEnd - (u8 *)mpBegin));
        if (BlockIsOurs(mpBegin))
            operator_delete_array(mpBegin);
        u32 size = (u32)(mpEnd - mpBegin);
        mpBegin = pNew;
        mpEnd = pNew + size;
        mpCap = pNew + n;
    }
}

// ===========================================================================
// 0x00b84b10  eastl vector<Elem18>::vector(const vector&)  (copy ctor)
// ===========================================================================
struct Vec18Vec {
    Elem18 *mpBegin;   // +0x00
    Elem18 *mpEnd;     // +0x04
    Elem18 *mpCap;     // +0x08

    Vec18Vec *CopyCtor(Vec18Vec *pSrc);                             // 0x00b84b10
    void      insert(Elem18 *pos, u32 count, Elem18 *pValue);       // 0x00b84e90
    void      insert(Elem18 *pos, Elem18 *pVal);                    // 0x00b85220
};

// @ 0x00b84b10
Vec18Vec *Vec18Vec::CopyCtor(Vec18Vec *pSrc)
{
    u32 count = (u32)(pSrc->mpEnd - pSrc->mpBegin);
    Elem18 *pNew;
    if (count != 0)
        pNew = (Elem18 *)OPERATOR_NEW(count * 0x18);
    else
        pNew = 0;
    mpCap = pNew + count;
    mpBegin = pNew;
    mpEnd = pNew;
    Vec18Vec *p = pSrc;
    FUN_00b7f5c0(&p, p->mpBegin, p->mpEnd, pNew, p);
    mpEnd = (Elem18 *)p;
    return this;
}

// ===========================================================================
// 0x00b84cb0  eastl vector<Elem0C>::insert(pos, first, last)
// ===========================================================================
struct Vec0CVec {
    Elem0C *mpBegin;   // +0x00
    Elem0C *mpEnd;     // +0x04
    Elem0C *mpCap;     // +0x08

    void insert(Elem0C *pos, Elem0C *first, Elem0C *last);   // 0x00b84cb0
};

// @ 0x00b84cb0
void Vec0CVec::insert(Elem0C *pos, Elem0C *first, Elem0C *last)
{
    if (first == last)
        return;
    Elem0C *end = mpEnd;
    u32 count = (u32)(last - first);
    if (count <= (u32)(mpCap - end)) {
        u32 avail = (u32)(end - pos);
        if (count < avail) {
            Elem0C *split = end - count;
            Elem0C *out;
            FUN_00898b80(&out, split, end, end, first);
            mpEnd = mpEnd + count;
            FUN_00abced0(pos, split, end);
            FUN_00b84c80(first, last, pos);
            return;
        }
        Elem0C *mid = first + avail;
        Elem0C *p = pos;
        FUN_00898b80(&last, mid, last, end, first);
        mpEnd = mpEnd + (count - avail);
        FUN_00898b80(&pos, pos, end, mpEnd, first);
        mpEnd = mpEnd + avail;
        FUN_00abced0(first, mid, p + avail);
        return;
    }

    u32 size = (u32)(end - mpBegin);
    u32 newCap = size * 2;
    if (size == 0)
        newCap = 1;
    u32 need = size + count;
    if (need > newCap)
        newCap = need;
    Elem0C *pNew;
    if (newCap != 0)
        pNew = (Elem0C *)OPERATOR_NEW(newCap * 0xc);
    else
        pNew = 0;
    Elem0C *p1 = (Elem0C *)FUN_00a11310(mpBegin, pos, pNew);
    FUN_00898b80(&first, first, last, p1, first);
    Elem0C *p2 = (Elem0C *)FUN_00a11310(pos, mpEnd, first);
    if (BlockIsOurs(mpBegin))
        operator_delete_array(mpBegin);
    mpBegin = pNew;
    mpEnd = p2;
    mpCap = pNew + newCap;
}

// ===========================================================================
// 0x00b84e90  eastl vector<Elem18>::insert(pos, count, value)
// ===========================================================================
// @ 0x00b84e90
void Vec18Vec::insert(Elem18 *pos, u32 count, Elem18 *pValue)
{
    Elem18 *end = mpEnd;
    if ((u32)(mpCap - end) < count) {
        // grow
        u32 size = (u32)(end - mpBegin);
        u32 newCap = size * 2;
        if (size == 0)
            newCap = 1;
        u32 need = size + count;
        if (need > newCap)
            newCap = need;
        Elem18 *pNew;
        if (newCap != 0)
            pNew = (Elem18 *)OPERATOR_NEW(newCap * 0x18);
        else
            pNew = 0;
        Elem18 *p1 = (Elem18 *)FUN_00b7f630(mpBegin, pos, pNew);
        FUN_00b7f860(p1, count, pValue, pos);
        Elem18 *p2 = (Elem18 *)FUN_00b7f630(pos, mpEnd, p1 + count);
        if (BlockIsOurs(mpBegin))
            operator_delete_array(mpBegin);
        mpBegin = pNew;
        mpEnd = p2;
        mpCap = pNew + newCap;
        return;
    }
    if (count == 0)
        return;
    Elem18 value = *pValue;
    u32 avail = (u32)(end - pos);
    if (count < avail) {
        Elem18 *split = end - count;
        Elem18 *out;
        FUN_00b7f5c0(&out, split, end, end, pos);
        mpEnd = mpEnd + count;
        FUN_00cc8b50(pos, split, end);
        FUN_007144b0(pos, pos + count, &value);
        return;
    }
    u32 extra = count - avail;
    FUN_00b7f860(end, extra, &value, pos);
    Elem18 *p = pos;
    mpEnd = mpEnd + extra;
    FUN_00b7f5c0(&pos, pos, end, mpEnd, pos);
    mpEnd = mpEnd + avail;
    FUN_007144b0(p, end, &value);
}

// ===========================================================================
// 0x00b850c0  eastl uninitialised_copy of 0x1c-byte {u32,u32,Vec20B} elements
// ===========================================================================
struct Vec20B {
    u32 m0, m4, m8, mc, m10;
    void ctor(const Vec20B *src);    // modelled 0x00473460
};

struct Elem1C {
    u32    m0;      // +0x00
    u32    m4;      // +0x04
    Vec20B vec;     // +0x08
};

// @ 0x00b850c0
Elem1C *UninitCopy1C(const Elem1C *first, const Elem1C *last, Elem1C *dst)
{
    while (first != last) {
        if (dst != 0) {
            dst->m0 = first->m0;
            dst->m4 = first->m4;
            Vec20B *pvec = &dst->vec;
            pvec->ctor(&first->vec);
        }
        ++first;
        ++dst;
    }
    return dst;
}

// ===========================================================================
// 0x00b85110  destructor of the scalar-list owner
// ===========================================================================
struct IntVec {
    void *mpBegin;   // +0x00
    void *mpEnd;     // +0x04
    void  dtor(void *begin, void *end);   // modelled 0x01023030
};

struct ScalarList {
    void   *mpVtbl;    // +0x00
    u8      pad04[4];  // +0x04
    void   *mp08;      // +0x08
    IntVec  mVec0c;    // +0x0c
    u8      pad14[0xc];// +0x14
    IntVec  mVec20;    // +0x20
    u8      pad28[0xc];// +0x28
    void   *mp34;      // +0x34

    void Dtor();       // 0x00b85110
};

// @ 0x00b85110
void ScalarList::Dtor()
{
    if (BlockIsOurs(mp34))
        operator_delete_array(mp34);
    {
        IntVec *v = &mVec20;
        v->dtor(v->mpBegin, v->mpEnd);
        if (BlockIsOurs(v->mpBegin))
            operator_delete_array(v->mpBegin);
    }
    {
        IntVec *v = &mVec0c;
        v->dtor(v->mpBegin, v->mpEnd);
        if (BlockIsOurs(v->mpBegin))
            operator_delete_array(v->mpBegin);
    }
    if (mp08 != 0)
        ((void (__thiscall *)(void *))VTC(mp08, 8))(mp08);
    mpVtbl = (void *)0x013ef094;
}

// ===========================================================================
// 0x00b85220  eastl vector<Elem18>::insert(pos, value)
// ===========================================================================
// @ 0x00b85220
void Vec18Vec::insert(Elem18 *pos, Elem18 *pVal)
{
    Elem18 *end = mpEnd;
    if (end != mpCap) {
        if (pVal >= pos && pVal < end)
            ++pVal;
        if (end != 0) {
            end->m0  = (end - 1)->m0;
            end->f4  = (end - 1)->f4;
            end->f8  = (end - 1)->f8;
            end->fc  = (end - 1)->fc;
            end->b10 = (end - 1)->b10;
            end->b11 = (end - 1)->b11;
            end->m14 = (end - 1)->m14;
        }
        FUN_00cc8b50(pos, mpEnd - 1, mpEnd);
        *pos = *pVal;
        mpEnd += 1;
        return;
    }

    u32 size = (u32)(end - mpBegin);
    u32 newCap;
    if (size == 0)
        newCap = 1;
    else
        newCap = size * 2;
    Elem18 *pNew;
    if (newCap != 0)
        pNew = (Elem18 *)OPERATOR_NEW(newCap * 0x18);
    else
        pNew = 0;
    Elem18 *pMid = (Elem18 *)FUN_00b7f630(mpBegin, pos, pNew);
    if (pMid != 0) {
        pMid->m0  = pVal->m0;
        pMid->f4  = pVal->f4;
        pMid->f8  = pVal->f8;
        pMid->fc  = pVal->fc;
        pMid->b10 = pVal->b10;
        pMid->b11 = pVal->b11;
        pMid->m14 = pVal->m14;
    }
    Elem18 *pNewEnd = (Elem18 *)FUN_00b7f630(pos, mpEnd, pMid + 1);
    if (BlockIsOurs(mpBegin))
        operator_delete_array(mpBegin);
    mpEnd = pNewEnd;
    mpBegin = pNew;
    mpCap = pNew + newCap;
}

// ===========================================================================
// 0x00b84270  cModelTestCheat::Execute
// ===========================================================================
struct cTerrainMapSet {
    char  pad00[0x34];
    float f34;            // +0x34
    float f38;            // +0x38
    char  pad3c[0x18];
    float f54;            // +0x54
};

struct cITerrainSphere {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual cTerrainMapSet *s3();      // +0x0c
};

struct cPlanetModel {
    char   pad00[0x18];
    Vec3f  mBase;                      // +0x18
    char   pad24[0x924 - 0x24];
    u32    m924;                       // +0x924
};

struct PropItem {
    char  pad00[0x0c];
    Vec3f mDir;                        // +0x0c
    char  pad18[0x90 - 0x18];
    void *mpProp;                      // +0x90
};

struct cModelTestCheat {
    char           pad00[0x20];
    cPlanetModel  *mp20;               // +0x20
    cITerrainSphere *mp24;             // +0x24
    char           pad28[0x2c - 0x28];
    Vec3f          m2c;                // +0x2c
    u16           *mp38;               // +0x38
    u16           *mp3c;               // +0x3c
    char           pad40[0x48 - 0x40];
    u8             m48;                // +0x48
    char           pad49[0x4c - 0x49];
    u32           *mp4c;               // +0x4c
    char           pad50[0x78 - 0x50];
    u8             m78;                // +0x78
    char           pad79[0x7c - 0x79];
    void          *mp7c;               // +0x7c
    char           pad80[0xa8 - 0x80];
    void          *mpA8;               // +0xa8

    bool Execute();                    // 0x00b84270
};

extern "C" void *GetActiveTerrainSphere();               // 0x00f48aa0
extern "C" void  FUN_00f48af0(void *p);                  // 0x00f48af0
extern "C" void  FUN_00b7e0b0(void *p);                  // 0x00b7e0b0
extern "C" void *TerrainEditor();                         // 0x00f48a70
extern "C" char  FUN_00f678a0(void *p);                  // 0x00f678a0
extern "C" void *MessageServer();                         // 0x0067dcc0
extern "C" void *FUN_0067dd50();                          // 0x0067dd50
extern "C" void *GonzagoModelWorld();                     // 0x00b3d520
extern "C" void *FUN_00b33f40();                          // 0x00b33f40
extern "C" void *FUN_0067de00();                          // 0x0067de00
extern "C" void *ModelManager();                          // 0x0067dd80
extern "C" void *Memset32(void *d, int c, u32 n);         // 0x0092cb00
extern "C" float *FUN_0041ea70(void *p);                  // 0x0041ea70
extern "C" float  FUN_00c9eb60();                         // 0x00c9eb60
extern "C" void   FUN_00b83c40(void *self, const float *dir, float radius,
                               u32 flags, void *cb);      // 0x00b83c40

extern void *g_15fd918;         // 0x015fd918
extern void *g_167ea54;         // 0x0167ea54

extern const float kMaxFloat;   // 0x01465438 (+FLT_MAX)
extern const float kMinFloat;   // 0x013f51ac (-FLT_MAX)
extern const float kBoxHalf;    // 0x013f1cac (50.0f)
extern const Vec3f kBoxCenter;  // 0x016881f0 (x,y,z)
extern const float kRadiusA;    // 0x013ec4d0 (100.0f)
extern const float kRadiusB;    // 0x01488774 (0.1f)
extern const float kPropDefault;// 0x013ebc68

// @ 0x00b84270
bool cModelTestCheat::Execute()
{
    cPlanetModel *p20 = mp20;
    cITerrainSphere *p24 = mp24;
    void *pBase = (char *)p20 + 0x18;

    if (p24 != (cITerrainSphere *)GetActiveTerrainSphere())
        FUN_00f48af0(p24);
    FUN_00b7e0b0(p24);
    ((void (__thiscall *)(void *, int))VTC(p20, 0x98))(p20, 1);

    if (!FUN_00f678a0(TerrainEditor())) {
        void *g = g_167ea54;
        ((void (__thiscall *)(void *, u32))VTC(g, 0x3c))(g, p20->m924);
    }

    if (m48 == 0) {
        m48 = 1;
        void *ms = MessageServer();
        ((void (__thiscall *)(void *, void *, int))VTC(ms, 0x20))(ms, this, 0x1b537e5);
        ms = MessageServer();
        ((void (__thiscall *)(void *, void *, int))VTC(ms, 0x20))(ms, this, 0x182c582);
        ms = MessageServer();
        ((void (__thiscall *)(void *, void *, int))VTC(ms, 0x20))(ms, this, 0x44448ed);
        ms = MessageServer();
        ((void (__thiscall *)(void *, void *, int))VTC(ms, 0x20))(ms, this, 0x45fe992);
    }

    cTerrainMapSet *map = p24->s3();
    float H = map->f38 * map->f54 + map->f34 + kBoxHalf;

    float box[6];
    box[0] = kBoxCenter.x - H;
    box[1] = kBoxCenter.y - H;
    box[2] = kBoxCenter.z - H;
    box[3] = kBoxCenter.x + H;
    box[4] = kBoxCenter.y + H;
    box[5] = kBoxCenter.z + H;

    void *world = GonzagoModelWorld();
    if (world != 0)
        ((void (__thiscall *)(void *))VTC(world, 0))(world);
    ((void (__thiscall *)(void *, void *, float, float))VTC(world, 0x150))(
        world, box, kRadiusB, kRadiusA);

    void *g = g_15fd918;
    int *pSub = *(int **)((char *)g + 0x3c);
    if (*(int *)((char *)pSub + 0xf0) != 0) {
        void *o = FUN_0067de00();
        ((void (__thiscall *)(void *, void *, float, float))VTC(o, 0xa4))(
            o, box, kRadiusB, kRadiusA);
    }

    m2c.x = *(float *)pBase;
    m2c.y = *((float *)pBase + 1);
    m2c.z = *((float *)pBase + 2);

    if (mp38 != mp3c) {
        *mp38 = 0;
        mp3c = mp38;
    }
    m78 = 1;
    Memset32(mp7c, 0, 0x3000);
    {
        u32 *p = mp4c;
        for (int i = 0; i < 0x18000; ++i)
            p[i] &= 0xc3ffffff;
    }

    if (p24 != 0) {
        void *prop = mpA8;
        if (*((u8 *)prop + 0x28) == 0) {
            void *s = FUN_0067dd50();
            ((void (__thiscall *)(void *, void *, int, int))VTC(s, 0x4c))(s, prop, 9, 0);
            s = FUN_0067dd50();
            ((void (__thiscall *)(void *, void *, int, int))VTC(s, 0x4c))(s, prop, 0x19, 0);
        }
        *((u8 *)prop + 0x28) = 1;

        ((void (__thiscall *)(void *, void *, int))VTC(p24, 0xe4))(
            p24, GonzagoModelWorld(), 5);
        ((void (__thiscall *)(void *, void *, int))VTC(p24, 0xf0))(
            p24, FUN_00b33f40(), 5);

        void *gg = g_15fd918;
        if (((char (__thiscall *)(void *, u32))0x006a25a0)(gg, 0x5404855)) {
            void *mm = ModelManager();
            void *res = ((void *(__thiscall *)(void *, u32))VTC(mm, 0x1c))(mm, 0x3fbae24);
            ((void (__thiscall *)(void *, void *, int))VTC(p24, 0xe4))(p24, res, 1);
        }

        PropItem **arr = 0;
        int count = ((int (__thiscall *)(void *, PropItem ***))VTC(p24, 0xb0))(p24, &arr);
        for (int i = 0; i < count; ++i) {
            PropItem *item = arr[i];
            if (item == 0)
                continue;
            void *prop2 = item->mpProp;
            if (prop2 != 0) {
                void *p = 0;
                if (((char (__thiscall *)(void *, u32, void **))VTC(prop2, 0x24))(
                        prop2, 0x3f6d22a, &p) && *(short *)((char *)p + 0x12) == 1) {
                    void *q = p;
                    if ((*((u8 *)p + 0x10) & 0x30) != 0)
                        q = *(void **)p;
                    if (*(u8 *)q != 0)
                        continue;
                }
            }
            float r = kPropDefault;
            if (prop2 != 0) {
                void *p = 0;
                if (((char (__thiscall *)(void *, u32, void **))VTC(prop2, 0x24))(
                        prop2, 0x254cf89, &p) && *(short *)((char *)p + 0x12) == 0xd) {
                    r = *FUN_0041ea70(p);
                }
            }
            FUN_00b83c40(this, &item->mDir.x, r, 0x10000000, 0);

            float r2 = 0.0f;
            if (prop2 != 0) {
                void *p = 0;
                if (((char (__thiscall *)(void *, u32, void **))VTC(prop2, 0x24))(
                        prop2, 0x254cf97, &p) && *(short *)((char *)p + 0x12) == 0xd) {
                    r2 = *FUN_0041ea70(p);
                }
            }
            if (FUN_00c9eb60() <= r2) {
                if (prop2 != 0) {
                    void *p = 0;
                    if (((char (__thiscall *)(void *, u32, void **))VTC(prop2, 0x24))(
                            prop2, 0x254cf8f, &p) && *(short *)((char *)p + 0x12) == 0xd) {
                        r = *FUN_0041ea70(p);
                    }
                }
                FUN_00b83c40(this, &item->mDir.x, r, 0x20000000, 0);
            }
        }
    }

    ((void (__thiscall *)(void *))VTC(world, 4))(world);
    return mp24 != 0;
}
