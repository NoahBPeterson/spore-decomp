// ===========================================================================
// slice s00c96950 -- resource-collection cluster (module 0x00c9xxxx).
// Reconstructed from work/SporeApp.analysis.bin.
//
//   0x00c96950  FUN_00c96950   keyed lookup + insert
//   0x00c96a00  FUN_00c96a00   keyed erase from a bucket chain
//   0x00c96a80  FUN_00c96a80   full object teardown
//   0x00c96e80  FUN_00c96e80   thin notify wrapper
//   0x00c96e90  FUN_00c96e90   unregister / prune one entry
//   0x00c97020  FUN_00c97020   collect + rebuild the position list
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// ===========================================================================

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#pragma warning(disable: 4100 4189 4244 4311 4312 4244)

#include <math.h>

struct Vec3 { float x, y, z; };
struct Vec2 { void* pBeg; void* pEnd; void* pCap; };

// ---- cdecl / free callees ------------------------------------------------
void* FUN_00c929a0(u32* pOut, void* pArg);                     // 0x00c929a0
void  FUN_00c93750(void* pOut, void* pIn);                     // 0x00c93750
void  FUN_00f47380(void* p);                                   // 0x00f47380
void* FUN_0067dcc0();                                          // 0x0067dcc0
void* FUN_00b3d300();                                          // 0x00b3d300
void* FUN_00b3d330();                                          // 0x00b3d330
void* FUN_00b3d350();                                          // 0x00b3d350
void* FUN_00b3d440(void* a);                                   // 0x00b3d440
void* FUN_011e073e(void* p, u32 v, u32 n);                     // 0x011e073e  memset
void  FUN_004b5ad0(void* a, void* b);                          // 0x004b5ad0
void  FUN_00c95980(void* a, void* b, Vec3 v);                  // 0x00c95980

// ---- thiscall callees (ecx = the receiver passed as pSelf) ----------------
struct CalleeSet {
    void  FUN_00ca09f0(u32 a);                        // 0x00ca09f0
    void  FUN_00c94d60(void* a, void* b, u32 c);      // 0x00c94d60
    void  FUN_00abf900();                             // 0x00abf900  sub-object dtor
    void  FUN_00cee7e0();                             // 0x00cee7e0
    void  FUN_00e25bd0(void* beg, void* end);         // 0x00e25bd0  vector clear
    void  FUN_00b225d0(void* a);                      // 0x00b225d0
    void  FUN_00b48e40(void* beg, void* end);         // 0x00b48e40
    void  FUN_00ac0450();                             // 0x00ac0450
    void  FUN_00afafd0();                             // 0x00afafd0
    void  FUN_00c93700(void* a, void* b);             // 0x00c93700
    void  FUN_00ce0a20(u32 a);                        // 0x00ce0a20
    void  FUN_00c95930(void* beg, void* end);         // 0x00c95930
    void  FUN_00b6ee10();                             // 0x00b6ee10
    void  FUN_00c8b2e0();                             // 0x00c8b2e0
    void  FUN_00c01e80();                             // 0x00c01e80
    void  FUN_00421cf0();                             // 0x00421cf0
    void  FUN_00b21410(void* a);                      // 0x00b21410
    float FUN_00b7e390();                             // 0x00b7e390
    void* FUN_00b09340();                             // 0x00b09340
    void* FUN_00fcc210();                             // 0x00fcc210
    void  FUN_00afa0a0();                             // 0x00afa0a0
    void  FUN_00c95d70(void* a, u32 b);               // 0x00c95d70
    void  FUN_00c96a00(void* pKey);                   // 0x00c96a00
};
#define SELF(o) ((CalleeSet*)(o))

// ---- vtable dispatch through a member pointer (thiscall) ------------------
struct VtblObj {
    void  C0(); void  C1(void*); void  C2(void*, void*); void  C3(void*, void*, void*);
    void* R0(); void* R1(void*); void* R2(void*, void*); void* R3(void*, void*, void*);
    float FR0();
};
typedef void  (VtblObj::*PMF0)();
typedef void  (VtblObj::*PMF1)(void*);
typedef void  (VtblObj::*PMF2)(void*, void*);
typedef void  (VtblObj::*PMF3)(void*, void*, void*);
typedef void* (VtblObj::*PMR0)();
typedef void* (VtblObj::*PMR2)(void*, void*);
typedef float (VtblObj::*PMFR0)();

inline void  VCall0(void* p, u32 o)                            { (((VtblObj*)p)->*(*(PMF0*)((u8*)*(void**)p + o)))(); }
inline void  VCall1(void* p, u32 o, void* a)                   { (((VtblObj*)p)->*(*(PMF1*)((u8*)*(void**)p + o)))(a); }
inline void  VCall2(void* p, u32 o, void* a, void* b)          { (((VtblObj*)p)->*(*(PMF2*)((u8*)*(void**)p + o)))(a, b); }
inline void  VCall3(void* p, u32 o, void* a, void* b, void* c) { (((VtblObj*)p)->*(*(PMF3*)((u8*)*(void**)p + o)))(a, b, c); }
inline void* VRet0(void* p, u32 o)                             { return (((VtblObj*)p)->*(*(PMR0*)((u8*)*(void**)p + o)))(); }
inline void* VRet2(void* p, u32 o, void* a, void* b)           { return (((VtblObj*)p)->*(*(PMR2*)((u8*)*(void**)p + o)))(a, b); }
inline float VFRet0(void* p, u32 o)                            { return (((VtblObj*)p)->*(*(PMFR0*)((u8*)*(void**)p + o)))(); }

// ring node used by the +0x4e4 hash-set sub-object
struct HashNode { u32 mKey; u8 mGap04[0x2c]; HashNode* pNext; };
// the +0x4e4 hash-set sub-object (also the receiver of FUN_00c96950/c96a00)
struct CHash {
    u8      mGap00[0x04];      // +0x00
    void*   mpBuckets;         // +0x04
    u32     mW08;              // +0x08  bucket slot count
    u32     mW0c;              // +0x0c  element count

    void* FUN_00c96950(void* pArg);
    u32   FUN_00c96a00(void* pKey);
};
// the +0x394 sub-object: bucket array and its slot count
struct Bkt394 { void** mpBuckets; u32 mWSlots; void** mpSentinel; };
// the +0x120 embedded sub-object
struct Sub120 { void** mv; };
// result of 0x00b3d350()
struct G350 { u8 mGap00[0x24]; void* mp24; };

// the collection object this cluster lives on
struct CRes {
    void**  mv;                // +0x000  vtable
    void*   mp04;              // +0x004
    u32     mW08;              // +0x008
    u32     mW0c;              // +0x00c
    u8      mGap10[0x110];     // +0x010 .. 0x120
    Sub120  mSub120;           // +0x120
    u8      mGap124[0xd0];     // +0x124 .. 0x1f4
    u8      mSub1f4[0x18];     // +0x1f4
    u8      mSub20c[0x24];     // +0x20c .. 0x230
    u8      mSub230[0x30];     // +0x230 .. 0x260
    void*   mp260;             // +0x260
    u8      mGap264[0x2c];     // +0x264 .. 0x290
    void*   mp290;             // +0x290
    u8      mGap294[0x40];     // +0x294 .. 0x2d4
    void*   mp2d4;             // +0x2d4
    u8      mGap2d8[0x29];     // +0x2d8 .. 0x301
    u8      mB301;             // +0x301
    u8      mGap302[0x12];     // +0x302 .. 0x314
    Vec2    mVec314;           // +0x314  Vec3 / ptr list
    u8      mGap320[0x20];     // +0x320 .. 0x340
    Vec2    mVec340;           // +0x340
    u8      mGap34c[0x08];     // +0x34c .. 0x354
    Vec2    mVec354;           // +0x354
    u8      mGap360[0x08];     // +0x360 .. 0x368
    void*   mp368;             // +0x368
    Vec2    mVec36c;           // +0x36c
    u8      mGap378[0x08];     // +0x378 .. 0x380
    Vec2    mVec380;           // +0x380
    u8      mGap38c[0x08];     // +0x38c .. 0x394
    Bkt394  mBkt394;           // +0x394
    u8      mGap3a0[0x14];     // +0x3a0 .. 0x3b4
    u8      mSub3b4[0x50];     // +0x3b4
    Vec2    mVec404;           // +0x404  0x18-stride records
    u8      mGap410[0xd4];     // +0x410 .. 0x4e4
    CHash   mHash4e4;          // +0x4e4  hash-set sub-object
    u8      mGap4f0[0x13dc];   // +0x4f0 .. 0x18cc
    u8      mArr18cc[0x38];    // +0x18cc
    u8      mGap1904[0xc0];    // +0x1904 .. 0x19c4
    void*   mp19c4;            // +0x19c4
    void*   mp19c8;            // +0x19c8
    void*   mp19cc;            // +0x19cc
    void*   mp19d0;            // +0x19d0
    void*   mp19d4;            // +0x19d4

    void* FUN_00c96950(void* pArg);
    u32   FUN_00c96a00(void* pKey);
    void  FUN_00c96a80();
    void  FUN_00c96e80(u32 a);
    void  FUN_00c96e90(void* pArg);
    void* FUN_00c97020();
};

// @ 0x00c96950
void* CHash::FUN_00c96950(void* pArg)
{
    u32 slot = 0;
    void* r = FUN_00c929a0(&slot, pArg);
    if (slot != (u32)(size_t)((u8**)mpBuckets)[mW08])
        return (u8*)r + 4;

    u8 probe[0x2c];
    for (int i = 0; i < 0x2c; ++i)
        probe[i] = 0;
    SELF(probe)->FUN_00ca09f0(0);

    u8 keyBlob[0x40];
    for (int i = 0; i < 0x40; ++i)
        keyBlob[i] = 0;
    *(u32*)keyBlob = *(u32*)pArg;
    FUN_00c93750(&keyBlob[0x34], &keyBlob[0x00]);

    u8 outBlob[0x2c];
    SELF(probe)->FUN_00c94d60(&outBlob[0x00], &keyBlob[0x00], 0);
    SELF(&keyBlob[0x34])->FUN_00abf900();
    SELF(&keyBlob[0x00])->FUN_00abf900();
    return (u8*)&outBlob[0x00];
}

// @ 0x00c96a00
u32 CHash::FUN_00c96a00(void* pKey)
{
    u32 before = mW0c;
    u32 key = *(u32*)pKey;
    u32 b = key % mW08;
    HashNode** buckets = (HashNode**)mpBuckets;
    HashNode** link = &buckets[b];
    if (*link == 0)
        return before - mW0c;

    while ((u32)(size_t)*link != 0 && (*link)->mKey != key)
        link = &(*link)->pNext;
    if (*link == 0)
        return before - mW0c;

    while ((u32)(size_t)*link != 0) {
        HashNode* cur = *link;
        if (cur->mKey != key)
            break;
        *link = cur->pNext;
        SELF(&cur->mGap04[0x00])->FUN_00abf900();
        FUN_00f47380(cur);
        --mW0c;
    }
    return before - mW0c;
}

// @ 0x00c96a80
void CRes::FUN_00c96a80()
{
    u32 tag = 0x01e8c9df;
    u8* me = (u8*)this;
    (void)tag;

    u8 desc[0x30];
    for (int i = 0; i < 0x30; ++i)
        desc[i] = 0;
    *(u32*)(desc + 0x00) = 0x13eb844;
    *(u8**)(desc + 0x08) = me;

    void* sys = FUN_0067dcc0();
    VCall3(sys, 0x14, (void*)0, desc, (void*)0);

    SELF(me + 0x20c)->FUN_00cee7e0();
    SELF(me + 0x380)->FUN_00e25bd0(mVec380.pBeg, mVec380.pEnd);

    while (mVec36c.pBeg != mVec36c.pEnd) {
        void* obj = *(void**)((u8*)mVec36c.pEnd - 4);
        if (obj)
            VCall0(obj, 0x00);
        mVec36c.pEnd = (u8*)mVec36c.pEnd - 4;
        void* e2 = *(void**)mVec36c.pEnd;
        if (e2)
            VCall0(e2, 0x04);
        SELF(FUN_00b3d300())->FUN_00b225d0(obj);
        if (obj)
            VCall0(obj, 0x04);
    }
    SELF(me + 0x36c)->FUN_00e25bd0(mVec36c.pBeg, mVec36c.pEnd);

    SELF(me + 0x354)->FUN_00b48e40(mVec354.pBeg, mVec354.pEnd);
    SELF(me + 0x1f4)->FUN_00ac0450();

    while (((u8*)mVec340.pEnd - (u8*)mVec340.pBeg) > 0) {
        void* obj = *(void**)((u8*)mVec340.pEnd - 4);
        VCall1(me, 0xa0, obj);
    }
    SELF(me + 0x340)->FUN_00e25bd0(mVec340.pBeg, mVec340.pEnd);

    if (mp368) {
        VCall0(mp368, 0x44);
        SELF(FUN_00b3d300())->FUN_00b225d0(mp368);
        void* p = mp368;
        mp368 = 0;
        if (p)
            VCall0(p, 0x04);
    }
    if (mp2d4) {
        void* p = mp2d4;
        mp2d4 = 0;
        VCall0(p, 0x04);
    }

    {
        int n = (int)(((u8*)mBkt394.mpSentinel - (u8*)mBkt394.mpBuckets) >> 2);
        for (int i = 0; i < n; ++i) {
            void* p = ((void**)mBkt394.mpBuckets)[i];
            if (!p)
                continue;
            SELF((u8*)p + 4)->FUN_00afafd0();
        }
    }
    (void)tag;
    SELF(me + 0x3b4)->FUN_00afafd0();

    if (mp290) {
        void* g = FUN_00b3d330();
        VCall1(g, 0x54, mp290);
        SELF(mp290)->FUN_00ce0a20((u32)(size_t)mp290);
        if (mp290) {
            void* p = mp290;
            mp290 = 0;
            VCall0(p, 0x08);
        }
    }
    if (mp260) {
        SELF(FUN_00b3d300())->FUN_00b225d0(mp260);
        if (mp260) {
            void* p = mp260;
            mp260 = 0;
            VCall0(p, 0x04);
        }
    }
    FUN_011e073e(mArr18cc, 0, 0x38);

    if (mp19d4) {
        void* g = FUN_00b3d350();
        void* h = g ? ((G350*)g)->mp24 : 0;
        if (h) {
            VCall2(h, 0x58, (void*)0, mp19d4);
            mp19d4 = 0;
        }
    }
    if (mp19c4) {
        SELF(FUN_00b3d300())->FUN_00b225d0(mp19c4);
        void* p = mp19c4;
        if (p) { mp19c4 = 0; VCall0(p, 0x04); }
    }
    if (mp19c8) {
        SELF(FUN_00b3d300())->FUN_00b225d0(mp19c8);
        void* p = mp19c8;
        if (p) { mp19c8 = 0; VCall0(p, 0x04); }
    }
    if (mp19cc) {
        SELF(FUN_00b3d300())->FUN_00b225d0(mp19cc);
        void* p = mp19cc;
        if (p) { mp19cc = 0; VCall0(p, 0x04); }
    }
    if (mp19d0) {
        SELF(FUN_00b3d300())->FUN_00b225d0(mp19d0);
        void* p = mp19d0;
        if (p) { mp19d0 = 0; VCall0(p, 0x04); }
    }

    SELF(&mHash4e4)->FUN_00c95930(mHash4e4.mpBuckets, (void*)(size_t)mHash4e4.mW08);
    mHash4e4.mW0c = 0;
    SELF(FUN_00b3d300())->FUN_00b21410(me + 0x120);
    SELF(me + 0x230)->FUN_00b6ee10();
    SELF(me + 0x1f4)->FUN_00ac0450();
    SELF(me + 0x120)->FUN_00c8b2e0();
    SELF(me)->FUN_00c01e80();
    SELF(&desc[0x28])->FUN_00421cf0();
}

// @ 0x00c96e80
void CRes::FUN_00c96e80(u32 a)
{
    SELF(this)->FUN_00c95d70((void*)(size_t)a, 1);
}

// @ 0x00c96e90
void CRes::FUN_00c96e90(void* pArg)
{
    void* g = VRet0(pArg, 0x58);
    u8* arr = (u8*)this;

    {
        int n = (int)(((u8*)mVec404.pEnd - (u8*)mVec404.pBeg) / 0x18);
        for (int i = 0; i < n; ++i) {
            u8* rec = (u8*)mVec404.pBeg + i * 0x18;
            if (SELF(rec)->FUN_00fcc210() == pArg)
                SELF(rec)->FUN_00afa0a0();
        }
    }

    {
        u8* p = (u8*)mVec380.pBeg;
        u8* e = (u8*)mVec380.pEnd;
        while (p != e && *(void**)p != pArg)
            p += 4;
        if (p != e) {
            u8 tmpKey[4];
            *(void**)tmpKey = pArg;
            FUN_004b5ad0(e, p);
        }
        SELF(arr + 0x380)->FUN_00e25bd0(mVec380.pBeg, mVec380.pEnd);
    }

    {
        int cnt = (int)(((u8*)mVec36c.pEnd - (u8*)mVec36c.pBeg) >> 2);
        int i;
        for (i = 0; i < cnt; ++i)
            if (*(void**)((u8*)mVec36c.pBeg + i * 4) == pArg)
                break;
        if (i < cnt) {
            void* victim = *(void**)((u8*)mVec36c.pBeg + i * 4);
            void* keep = *(void**)((u8*)mVec36c.pBeg + (cnt - 1) * 4);
            if (keep != victim) {
                if (keep)
                    VCall0(keep, 0x00);
                *(void**)((u8*)mVec36c.pBeg + i * 4) = keep;
                if (victim)
                    VCall0(victim, 0x04);
            }
            mVec36c.pEnd = (u8*)mVec36c.pEnd - 4;
            void* e2 = *(void**)mVec36c.pEnd;
            if (e2)
                VCall0(e2, 0x04);
            VCall0(pArg, 0x44);
            SELF(FUN_00b3d300())->FUN_00b225d0(victim);
        }
    }

    {
        u8 tmpKey[4];
        *(void**)tmpKey = g;
        SELF(&mHash4e4)->FUN_00c96a00(tmpKey);
    }
}

// @ 0x00c97020
void* CRes::FUN_00c97020()
{
    u8* me = (u8*)this;
    if (mB301 != 0)
        return me + 0x314;

    u32 g1 = *(u32*)0x158128c;
    float k0 = *(float*)0x13f1cac;
    (void)g1; (void)k0;

    float d0 = SELF(FUN_00b3d350())->FUN_00b7e390();
    d0 = d0 * d0;
    (void)d0;

    void* sub = me + 0x120;
    void* probe = VRet0(sub, 0x2c);
    mB301 = 1;
    float k1 = *(float*)0x1581260;
    (void)k1;

    void* list = SELF(FUN_00b3d440(probe))->FUN_00b09340();

    {
        u8* p = (u8*)mVec314.pBeg;
        u8* end = (u8*)mVec314.pEnd;
        for (; p != end; p += 4) {
            Vec3* v = *(Vec3**)p;
            float d2 = v->x * v->x + v->y * v->y + v->z * v->z;
            if (!(d2 > 0.0f))
                continue;
            Vec3* t = (Vec3*)list;
            float dx = v->x - t->x;
            float dy = v->y - t->y;
            float dz = v->z - t->z;
            float dd = dx * dx + dy * dy + dz * dz;
            if (!(dd > 0.0f))
                continue;
            u8* w = (u8*)mVec314.pEnd;
            if (w < (u8*)mVec314.pCap) {
                mVec314.pEnd = w + 0xc;
                if (w) {
                    *(float*)(w + 0x0) = v->x;
                    *(float*)(w + 0x4) = v->y;
                    *(float*)(w + 0x8) = v->z;
                }
            } else {
                FUN_004b5ad0(w, v);
            }
        }
    }

    {
        Vec3 pos;
        pos.x = VFRet0(me, 0x2c);
        pos.y = pos.x;
        pos.z = pos.x;
        u8 tmp[0x10];
        FUN_00c95980(mVec314.pBeg, mVec314.pEnd, pos);
        if (*(void**)&tmp[0x4]) {
            if (*(u32*)((u8*)(*(void**)&tmp[0x4]) - 4) != 0)
                FUN_00f47380(*(void**)&tmp[0x4]);
        }
    }
    return me + 0x314;
}