// match/slices/s00c21090/s00c21090.cpp
// Object file: SPGonzago/SPCreatureBase.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
//
// Local stub class for SP::cSPCreatureBase, re-laid to the retail offsets the
// disassembly shows.  Only the members this slice touches are named; the rest
// are uint32_t pad gaps.

#include "game/types.h"
#include <new>

// ---- extern constants referenced by the originals ---------------------------
extern float g_13ef74c;         // 0x013ef74c  0.15f
extern float g_13f9428;         // 0x013f9428  0.001f
extern float g_13f4fd0;         // 0x013f4fd0  2^32 (float)
extern float g_146a32c;         // 0x0146a32c  FLT_MAX
extern float g_13eb8b0;         // 0x013eb8b0  sign mask (0x80000000)
extern float g_1571768;         // 0x01571768  identity quat x
extern float g_157176c;         // 0x0157176c  identity quat y
extern float g_1571770;         // 0x01571770  identity quat z
extern float g_1571774;         // 0x01571774  identity quat w
extern const void* g_1654c05;   // 0x01654c05  game-mode tag

// ---- free / non-member callees ----------------------------------------------
void* __cdecl FUN_00c0ff80(void* pA, void* pB, void* pC);          // 0x00c0ff80
void  __cdecl FUN_00c0fea0(uint32_t* pDst, uint32_t* pSrc);         // 0x00c0fea0
void* __cdecl SP_GetCurrentGameMode();                              // 0x00b5b800
void* __cdecl FUN_00b3d240();                                       // 0x00b3d240
void* __cdecl FUN_00b33f40();                                       // 0x00b33f40
void  __cdecl FUN_009b3410(float f);                                // 0x009b3410
void* __cdecl FUN_004d9050(void* pAnim);                            // 0x004d9050
void* __cdecl FUN_004d9030(void* pAnim);                            // 0x004d9030
void  __cdecl FUN_009b7b10(int a, int b);                           // 0x009b7b10
int   __cdecl FUN_009b2340(void* pOut, int nMax, void* pObj, void* pFlags, int, int); // 0x009b2340
void  __cdecl EA_IO_ReadInt32(void* pStream, int* pValue, uint32_t n, int f);         // 0x0093a780
void* __cdecl FUN_00f47380(void* p);                                // 0x00f47380 (operator delete)
void  __cdecl FUN_00c15fd0(void* pOut, void* pKeyValue, uint32_t bFlag); // 0x00c15fd0
void  __cdecl FUN_00b77780(void* pOut, void* pArgA, void* pArgB);   // 0x00b77780 (map ctor)
void* __cdecl FUN_009cb5a0(uint32_t* pOut, void* pMe, void* pNodeA, void* pNodeB,
                           uint32_t nKey, uint32_t zero);           // 0x009cb5a0 (AttachEffect)
void* __cdecl FUN_009cb3f0(void* pOut, void* pArg);                 // 0x009cb3f0 (EraseEffect)
void  __cdecl FUN_00a04af0(void* pAnim, void* pArg);                // 0x00a04af0 (SetAttachments)
void  __cdecl FUN_00a04c80(void* pObj);                             // 0x00a04c80
void  __cdecl FUN_00a04ca0(void* pObj, int v);                      // 0x00a04ca0
void  __cdecl FUN_00a04ad0(void* pObj, int v);                      // 0x00a04ad0
void  __cdecl FUN_00a04cc0(void* pObj, int v);                      // 0x00a04cc0
void  __cdecl FUN_00a05270(void* pAnim);                            // 0x00a05270 (Release)
void* __cdecl FUN_0059acb0(void* pThis, void* pArg);                // 0x0059acb0 (AutoRefCount::operator=)
void* __cdecl eastl_hashtable_find(void* pOut, void* pKey);         // 0x00645ed0
void  __cdecl eastl_DoFreeNodes(void* pBucket, uint32_t n);          // 0x00a1b6c0
void  __cdecl CCurvePoint_Read(void* pStream, void* pPoint);         // 0x00c141b0

// ---- helper types ------------------------------------------------------------
typedef void*  (__thiscall **FnPtr)(void*);
typedef void   (__thiscall **FnVoid)(void*);
typedef void   (__thiscall **FnVoidI)(void*, int);
typedef void   (__thiscall **FnVoidP)(void*, void*);
typedef float  (__thiscall **FnFloat)(void*);
typedef uint32_t (__thiscall **FnUInt)(void*);
typedef bool   (__thiscall **FnBool)(void*);

// Fetch a vtable slot from an object whose first word is the vtable.  glibc-free
// substitute for (*(fn**)obj)[slot] with the byte-offset spelled out.
inline uint32_t* vtab(void* pObj)
{
    return *(uint32_t**)pObj;
}
inline void* vcall_p(void* pObj, int nByteOffset)
{
    return ((void*(__thiscall*)(void*))vtab(pObj)[nByteOffset / 4])(pObj);
}
inline void vcall_v(void* pObj, int nByteOffset)
{
    ((void(__thiscall*)(void*))vtab(pObj)[nByteOffset / 4])(pObj);
}
inline void vcall_vi(void* pObj, int nByteOffset, int a)
{
    ((void(__thiscall*)(void*, int))vtab(pObj)[nByteOffset / 4])(pObj, a);
}
inline void vcall_vii(void* pObj, int nByteOffset, int a, int b)
{
    ((void(__thiscall*)(void*, int, int))vtab(pObj)[nByteOffset / 4])(pObj, a, b);
}
inline bool vcall_b(void* pObj, int nByteOffset)
{
    return ((bool(__thiscall*)(void*))vtab(pObj)[nByteOffset / 4])(pObj);
}
inline int vcall_i(void* pObj, int nByteOffset)
{
    return ((int(__thiscall*)(void*))vtab(pObj)[nByteOffset / 4])(pObj);
}
inline float vcall_f(void* pObj, int nByteOffset)
{
    return ((float(__thiscall*)(void*))vtab(pObj)[nByteOffset / 4])(pObj);
}

// ---- cCurvePoint (0x24 bytes) -----------------------------------------------
class cCurvePoint {
public:
    uint32_t mn00;               // +0x00
    uint32_t mn04;               // +0x04
    uint32_t mn08;               // +0x08
    uint32_t mn0c;               // +0x0c
    uint32_t mn10;               // +0x10
    float    mf14;               // +0x14
    uint8_t  mb18;               // +0x18
    uint8_t  pad19[3];
    uint32_t mn1c;               // +0x1c
    void*    mp20;               // +0x20

    cCurvePoint()
        : mn00(0xffffffff), mn04(0), mn08(0), mn0c(0), mn10(0),
          mb18(0), mn1c(0), mp20(0) {}

    cCurvePoint(const cCurvePoint& o)
        : mn00(o.mn00), mn04(o.mn04), mn08(o.mn08), mn0c(o.mn0c),
          mn10(o.mn10), mf14(o.mf14), mb18(o.mb18), mn1c(o.mn1c), mp20(o.mp20) {
        if (mp20 != 0)
            (*(FnVoid)(*(char**)mp20 + 0xbc))(mp20);
    }

    ~cCurvePoint() {
        if (mp20 != 0)
            (*(FnVoid)(*(char**)mp20 + 0xc0))(mp20);
    }
};

// ---- eastl vector of cCurvePoint --------------------------------------------
class cCurvePointVector {
public:
    cCurvePoint* mpBegin;        // +0x00
    cCurvePoint* mpEnd;          // +0x04
    cCurvePoint* mpCap;          // +0x08

    void   FUN_00c144b0(cCurvePoint* pA, cCurvePoint* pB); // 0x00c144b0 (ret 8)
    void   FUN_00c19aa0(uint32_t nCount);            // 0x00c19aa0
    void   FUN_00c1f650();                           // 0x00c1f650
    void   FUN_00c1b990(cCurvePoint* pPos, cCurvePoint* pVal); // 0x00c1b990

    __forceinline void push_back(const cCurvePoint& v) {
        cCurvePoint* p = mpEnd;
        if (p < mpCap) {
            mpEnd = p + 1;
            if (p != 0) {
                p->mn00 = v.mn00;
                p->mn04 = v.mn04;
                p->mn08 = v.mn08;
                p->mn0c = v.mn0c;
                p->mn10 = v.mn10;
                p->mf14 = v.mf14;
                p->mb18 = v.mb18;
                p->mn1c = v.mn1c;
                p->mp20 = v.mp20;
                if (v.mp20 != 0)
                    (*(FnVoid)(*(char**)v.mp20 + 0xbc))(v.mp20);
            }
        } else {
            FUN_00c1b990(p, (cCurvePoint*)&v);
        }
    }
};

// ---- a 0x2bc-byte animation record ------------------------------------------
class cAnimRecord {
public:
    uint8_t  pad00[0x104];
    int      mn104;              // +0x104
    int      mn108;              // +0x108
    float    mf10c;              // +0x10c
    float    mf110;              // +0x110
    float    mf114;              // +0x114
    uint8_t  pad118[0x138 - 0x118];
    float    mf138;              // +0x138
    float    mf13c;              // +0x13c
    float    mf140;              // +0x140
    uint8_t  pad144[0x2bc - 0x144];
};

// ---- hashtable node (key, value, next) --------------------------------------
struct cHashNode {
    uint32_t    mnKey;           // +0x00
    uint32_t    mnValue;         // +0x04
    cHashNode*  mpNext;          // +0x08
};

// ---- a simple eastl-style hashtable with fixed inline buckets ---------------
// Layout matches what 00c214a0 sets up on the stack: a bucket-count, a bucket
// pointer array, and an inline-storage region for small maps.
class cIntMap {
public:
    uint32_t     mnBucketCount;  // +0x00
    uint8_t      pad04[4];
    cHashNode**  mppBuckets;     // +0x08
    uint8_t      pad0c[0x40];

    cHashNode* Find(uint32_t nKey);              // 0x00645ed0
    void       Insert(uint32_t nKey, uint32_t nValue); // 0x00c15fd0
    cHashNode* Sentinel() { return mppBuckets[mnBucketCount]; }
};

// ---- cCreatureInstanceData (animating creature +0x17c) ----------------------
class cCreatureInstanceData {
public:
    void*    mpFirst;            // +0x000  (payload pointer; first field)
    uint8_t  pad04[0x2e4 - 0x04];
    cAnimRecord** mpAnimData;    // +0x2e4  (array of pointers to 0x2bc-byte records)
    cAnimRecord** mpAnimDataEnd; // +0x2e8
    uint8_t  pad2ec[0x17a4 - 0x2ec];
    cHashNode** mppBuckets;      // +0x17a4
    int      mnBucketCount;      // +0x17a8

    int NumRecords() const { return (int)(mpAnimDataEnd - mpAnimData); }

    void* AttachEffect(uint32_t* pOut, void* pNodeA, void* pNodeB,
                       uint32_t nKey, uint32_t zero);   // 0x009cb5a0
    void* EraseEffect(void* pOut, void* pArg);          // 0x009cb3f0
};

// ---- cAnimatingCreature (creature+0xb54) ------------------------------------
class cAnimatingCreature {
public:
    uint8_t  pad0[0x17c];
    cCreatureInstanceData* mpInstanceData; // +0x17c

    void SetAttachments(void* pArg);   // 0x00a04af0
    void Release();                    // 0x00a05270
};

// ---- cSpeciesProfile (creature+0xb20) ---------------------------------------
class cSpeciesProfile {
public:
    uint8_t  pad0[0x504];
    uint32_t mn504;              // +0x504
    uint32_t mn508;              // +0x508
    uint32_t mn50c;              // +0x50c
    uint32_t mn510;              // +0x510
    uint32_t mn514;              // +0x514
    uint32_t mn518;              // +0x518
    uint8_t  pad51c[0x53c - 0x51c];
    uint32_t mn53c;              // +0x53c
    uint8_t  pad540[0x590 - 0x540];
    float    mf590;              // +0x590
    float    mf594;              // +0x594
};

// ---- cSpeciesArchetype (creature+0xe84) -------------------------------------
class cSpeciesArchetype {
public:
    uint8_t  pad0[0x388];
    uint8_t  mb388;              // +0x388
};

// ---- cObjB48 (creature+0xb48) -----------------------------------------------
class cObjB48 {
public:
    void Tick(float fTime);      // 0x00bca350
};

// ---- cSPCreatureBase, retail layout -----------------------------------------
class cSPCreatureBase {
public:
    uint8_t  pad00[0xc0];
    uint8_t  mloco[0x110 - 0xc0];// +0x0c0  base_cLocomotiveObject (vtable at +0xc0)
    uint8_t  pad110[0x2b0 - 0x110];
    uint8_t  pad2b0[0xb20 - 0x2b0];
    cSpeciesProfile* mpSpeciesProfile; // +0xb20
    uint32_t mn0B24;             // +0xb24
    uint8_t  padB28[0xb34 - 0xb28];
    uint32_t mn0B34;             // +0xb34
    uint8_t  padB38[0xb48 - 0xb38];
    cObjB48* mpB48;              // +0xb48
    uint8_t  padB4c[0xb54 - 0xb4c];
    cAnimatingCreature* mpAnimatingCreature; // +0xb54
    uint32_t mn0B58;             // +0xb58
    uint8_t  padB5c[0xb5e - 0xb5c];
    uint8_t  mbB5E;              // +0xb5e
    uint8_t  padB5f[0xb63 - 0xb5f];
    uint8_t  mbB63;              // +0xb63
    uint8_t  padB64[0xb65 - 0xb64];
    uint8_t  mbB65;              // +0xb65
    uint8_t  padB66[0xe40 - 0xb66];
    cCurvePointVector mItemInventory;    // +0xe40
    uint8_t  padE4c[0xe84 - 0xe4c];
    cSpeciesArchetype* mpArchetype;      // +0xe84
    uint8_t  padE88[0xf80 - 0xe88];
    uint32_t mnF80;              // +0xf80
    uint8_t  padF84[0xf98 - 0xf84];
    uint32_t mnF98;              // +0xf98
    uint8_t  padF9c[0xfa4 - 0xf9c];
    uint32_t mnFA4;              // +0xfa4

    void   FUN_00c0d240();                          // 0x00c0d240
    void   FUN_00c19940(bool bFlag);                // 0x00c19940 (clears mItemInventory)
    float  FUN_00c0ce80(int a, int b);              // 0x00c0ce80 (ret 8)
    void   FUN_00c1cdd0(int n);                     // 0x00c1cdd0
    void   FUN_00c1aad0(int n);                     // 0x00c1aad0
    void   FUN_00c201a0(uint8_t a, uint32_t b, uint32_t c); // 0x00c201a0 (ret 0xc)
    void   FUN_00c12310(uint32_t a, uint32_t b, uint32_t c); // 0x00c12310 (ret 0xc)
    void   FUN_00c12080(void* pEffect, bool bFlag); // 0x00c12080 (ret 8)
    void   FUN_00c24280();                          // 0x00c24280
    void   FUN_00c0c200(float f);                   // 0x00c0c200 (ret 4)

    void FUN_00c21090();
    void FUN_00c213d0(int nElapsed);                // 0x00c213d0
    void FUN_00c214a0(cAnimatingCreature* pOther, int param_3); // 0x00c214a0
    bool CheckCreatureModel(char param_2, int param_3);          // 0x00c21bf0
};

// =============================================================================================
// definitions

// @ 0x00c21090
void cSPCreatureBase::FUN_00c21090()
{
    FUN_00c19940(false);

    cCurvePointVector* pVec = &mItemInventory;
    cCurvePoint* pBeg = pVec->mpBegin;
    cCurvePoint* pEnd = pVec->mpEnd;
    void* pRet = FUN_00c0ff80(pEnd, pEnd, pBeg);
    pVec->FUN_00c144b0((cCurvePoint*)pRet, pVec->mpEnd);
    pVec->mpEnd += (pEnd - pBeg);

    cSpeciesProfile* pProfile = mpSpeciesProfile;
    if (pProfile == 0)
        return;
    float fA = pProfile->mf590;
    if (!(fA > 0.0f) && !(pProfile->mf594 > 0.0f))
        return;

    uint32_t nTag = 0x70737267;
    if (!(fA > 0.0f))
        nTag = 0x74756f6d;

    uint32_t** pList;
    if (!(fA > 0.0f))
        pList = (uint32_t**)FUN_004d9030(mpAnimatingCreature);
    else
        pList = (uint32_t**)FUN_004d9050(mpAnimatingCreature);

    uint32_t nCount = (uint32_t)(pList[1] - pList[0]);
    pVec->FUN_00c19aa0(nCount);

    for (uint32_t i = 0; i < nCount; ++i) {
        pVec->FUN_00c1f650();
        uint32_t nId = pList[0][i];
        cCurvePoint* pTail = pVec->mpEnd;
        pTail[-1].mn00 = nId;
        cAnimRecord* pRec = *(cAnimRecord**)((char*)mpAnimatingCreature->mpInstanceData->mpAnimData + nId * 0x2bc);
        float fB = (pRec->mf140 + pRec->mf13c + pRec->mf138) * g_13ef74c;
        pTail[-1].mb18 = (uint8_t)(pRec->mf10c <= fB ? 1 : 0);
    }

    if (nCount <= 1)
        return;

    uint32_t aFlags[4] = { 0x4000, nTag, 0, 0 };
    int aOut[255];
    int nRes = FUN_009b2340(aOut, 0xff, *(void**)mpAnimatingCreature->mpInstanceData, aFlags, 0, 0);
    if (nRes != 1)
        return;

    cCurvePoint* p = pVec->mpBegin;
    cCurvePoint* e = pVec->mpEnd;
    if (p == e)
        return;
    while (p->mn00 != (uint32_t)aOut[0]) {
        p += 1;
        if (p == e)
            break;
    }
    if (p != e)
        FUN_00c0fea0((uint32_t*)pVec->mpBegin, (uint32_t*)p);
}

// @ 0x00c21260
// Serialization read handler for cSPCreatureBase::mItemInventory (creature+0xe40);
// registered as Read_00c21260(stream, void*) and called with the member address.
void FUN_00c21260(void* pStream, cCurvePointVector* pVec)
{
    cCurvePoint* pBeg = pVec->mpBegin;
    cCurvePoint* pEnd = pVec->mpEnd;
    void* pRet = FUN_00c0ff80(pEnd, pEnd, pBeg);
    pVec->FUN_00c144b0((cCurvePoint*)pRet, pVec->mpEnd);
    pVec->mpEnd += (pEnd - pBeg);

    // Read the count via the read stream, then reserve that many points.
    int nCount = 0;
    void* pReader = (*(FnPtr)(*(char**)pStream + 0x20))(pStream);
    void* pStream2 = (*(FnPtr)(*(char**)pReader + 0x18))(pReader);
    EA_IO_ReadInt32(pStream2, &nCount, 1, 0);
    pVec->FUN_00c19aa0((uint32_t)nCount);

    for (uint32_t i = 0; i < (uint32_t)nCount; ++i) {
        cCurvePoint point;
        CCurvePoint_Read(pStream, &point);
        pVec->push_back(point);
    }

    (*(FnVoid)(*(char**)pStream + 0x1c))(pStream);
}

// @ 0x00c213d0
void cSPCreatureBase::FUN_00c213d0(int nElapsed)
{
    mnF80 += (uint32_t)nElapsed;
    if (mbB63) {
        char* p = (char*)this;
        (*(FnVoidI)(*(char**)p + 0xc8))(p, 1);
        return;
    }
    float f = (float)(uint32_t)nElapsed;
    f *= g_13f9428;
    mpB48->Tick(f);
    FUN_00c1cdd0(nElapsed);
    FUN_00c1aad0(nElapsed);
    char* loco = (char*)this + 0xc0;
    if ((*(FnBool)(*(char**)loco + 0x58))(loco)) {
        uint8_t b = (uint8_t)((mnFA4 >> 5) & 1);
        FUN_00c201a0(b, 0xe55dc391, 0x35052b7);
    }
    (*(FnVoidI)(*(char**)this + 0x6c))(this, nElapsed);
    if (!mbB5E)
        FUN_00c0c200(f);
}

// @ 0x00c214a0
// Full eastl-hashtable pass over both creatures' animation records: recompute,
// for every record of the *other* creature, the index of the nearest matching
// record on *this one; sync the effect table; flush stale effects.
void cSPCreatureBase::FUN_00c214a0(cAnimatingCreature* pOther, int param_3)
{
    cAnimatingCreature* pSelf = mpAnimatingCreature;
    if (pOther == 0 || pSelf == 0)
        return;

    cCreatureInstanceData* pSelfData = pSelf->mpInstanceData;
    cCreatureInstanceData* pOtherData = pOther->mpInstanceData;

    cIntMap map;             // stack hashtable (int -> int)
    int nSelfCount = pSelfData->NumRecords();
    int nOtherCount = pOtherData->NumRecords();

    for (int i = 0; i < nOtherCount; ++i) {
        cAnimRecord* pOtherRec = pOtherData->mpAnimData[i];
        float fBest = g_146a32c;   // FLT_MAX
        uint32_t nBest = 0;
        bool bFound = false;

        for (int j = 0; j < nSelfCount; ++j) {
            cAnimRecord* pSelfRec = pSelfData->mpAnimData[j];
            if (pSelfRec->mn104 != pOtherRec->mn104)
                continue;
            if (pSelfRec->mn108 != pOtherRec->mn108)
                continue;
            float dx = pSelfRec->mf110 - pOtherRec->mf110;
            float dy = pSelfRec->mf10c - pOtherRec->mf10c;
            float dz = pSelfRec->mf114 - pOtherRec->mf114;
            float d = dz * dz + dx * dx + dy * dy;
            if (d < fBest) {
                bFound = true;
                fBest = d;
                nBest = (uint32_t)j;
            }
        }

        if (bFound)
            map.Insert((uint32_t)i, nBest);
    }

    // If asked, walk the other creature's live effect table and attach the
    // matching effect on this creature, or erase it.
    if ((uint8_t)param_3 != 0) {
        cHashNode** ob = pOtherData->mppBuckets;
        int obCount = pOtherData->mnBucketCount;
        cHashNode* pNode = ob[0];
        if (pNode == 0) {
            // skip empty buckets
            cHashNode** pp = ob + 1;
            while (*pp == 0)
                ++pp;
            pNode = *pp;
        }
        while (pNode != ob[obCount]) {
            uint32_t nKey = pNode->mnKey;
            cHashNode* pEntry = (cHashNode*)pNode->mpNext;
            uint32_t nVal = 0xffffffff;
            cHashNode* pFound = map.Find(nKey);
            if (pFound != map.Sentinel())
                nVal = pFound->mnValue;

            void* e = pEntry->mpNext;   // effect pointer stored at node+8
            if ((*(uint8_t*)((char*)pEntry + 0x30)) == 0) {
                uint32_t aIt[2];
                aIt[0] = nKey;
                aIt[1] = 0;
                void* pRes = pOtherData->AttachEffect(aIt, pNode, pEntry, nVal, 0);
                pNode = *(cHashNode**)pRes;
                e = ((cHashNode*)pRes)->mpNext;
            } else {
                e = 0;
            }
            (void)e;
            // advance to next node
            cHashNode* pNext = pNode->mpNext;
            if (pNext == 0) {
                cHashNode** pp = (cHashNode**)((char*)pNode + 8);
                while (*pp == 0)
                    ++pp;
                pNext = *pp;
            }
            pNode = pNext;
        }
    }

    // Walk this creature's effect table, detaching any body effects.
    if (pOtherData != 0) {
        cHashNode** ob = pOtherData->mppBuckets;
        int obCount = pOtherData->mnBucketCount;
        while (true) {
            cHashNode* pNode = ob[0];
            if (pNode == 0) {
                cHashNode** pp = ob + 1;
                while (*pp == 0)
                    ++pp;
                pNode = *pp;
            }
            if (pNode == ob[obCount])
                break;
            void* pData = (void*)pNode->mnValue;
            if (pData != 0)
                FUN_00c12080(pData, 1);
            pOtherData->EraseEffect(&map, (void*)pNode);
        }
    }

    // Re-sync this creature's inventory ids from its own effect table, and if
    // anything was dropped, re-derive the inventory.
    cCurvePoint* p = mItemInventory.mpBegin;
    cCurvePoint* e = mItemInventory.mpEnd;
    bool bDropped = false;
    while (p != e) {
        if (p->mn00 != 0xffffffff) {
            cHashNode* pFound = map.Find(p->mn00);
            if (pFound == map.Sentinel())
                bDropped = true;
            else
                p->mn00 = pFound->mnValue;
        }
        p += 1;
    }
    if (bDropped)
        FUN_00c21090();

    FUN_00c24280();
    eastl_DoFreeNodes(map.mppBuckets, map.mnBucketCount);
}

// @ 0x00c21bf0
bool cSPCreatureBase::CheckCreatureModel(char param_2, int param_3)
{
    cAnimatingCreature* pOld = mpAnimatingCreature;
    cSpeciesProfile* pProfile = mpSpeciesProfile;

    // Fast path: nothing changed and no force flag.
    if (pOld != 0) {
        if (pProfile != 0 && pProfile->mn53c != mn0B24)
            goto rebuild;
        if (param_2 == 0)
            goto tail;
    }

rebuild:
    FUN_00c0d240();

    pOld = mpAnimatingCreature;
    if (pOld != 0) {
        mpAnimatingCreature = 0;
        pOld->Release();
    }

    uint32_t nName = 0, nArg2 = 0, nArg3 = 0;
    if (pProfile != 0) {
        if (mn0B34 == 0) {
            if (pProfile->mn510 == 0)
                goto done;
            nName = pProfile->mn510;
            nArg2 = pProfile->mn514;
            nArg3 = pProfile->mn518;
        } else {
            if (pProfile->mn504 == 0)
                goto done;
            nName = pProfile->mn504;
            nArg2 = pProfile->mn508;
            nArg3 = pProfile->mn50c;
        }

        if (nName != 0) {
            uint8_t* c0 = (uint8_t*)this + 0xc0;
            // this->mloco.vtable[0x30]() -> float[4] current orientation
            float* q = (float*)vcall_p(c0, 0x30);
            float qx = -q[0];
            float qy = q[1];
            float qz = -q[2];
            float qw = q[3];

            float aStack[4];
            aStack[0] = qx; aStack[1] = qy; aStack[2] = qz; aStack[3] = qw;

            if (((mn0B58 >> 9) & 1) != 0 && SP_GetCurrentGameMode() == g_1654c05) {
                void* pMgr = FUN_00b3d240();
                void* pSub = vcall_p(pMgr, 0x74);
                if (pSub != 0) {
                    uint32_t aLocal = 0;
                    (void)aLocal;
                    (void)pSub;
                }
            } else {
                void* pMgr = FUN_00b33f40();
                if (pMgr != 0) {
                    (void)pMgr;
                }
            }

            (void)nName; (void)nArg2; (void)nArg3;

            if (mpAnimatingCreature != 0) {
                float q45 = vcall_f(c0, 0x34);
                *(float*)((char*)mpAnimatingCreature + 0x3c) = q45;
                SP_GetCurrentGameMode();
                float fw = g_1571774;
                float fx = g_1571768;
                float fy = g_157176c;
                float fz = g_1571770;
                if (mbB65) {
                    float* pv = (float*)vcall_p(this, 0xe0);
                    fx = pv[0];
                    fy = pv[1];
                    fz = pv[2];
                }
                float* pTgt = (float*)((char*)mpAnimatingCreature + 0x74);
                pTgt[0] = fx;
                pTgt[1] = fy;
                pTgt[2] = fz;
                pTgt[3] = fw;
                *((uint8_t*)mpAnimatingCreature + 0x84) = mbB65;
                mpAnimatingCreature->SetAttachments(this);
                if (mpSpeciesProfile != 0) {
                    mn0B24 = pProfile->mn53c;
                    if (mpAnimatingCreature->mpInstanceData != 0) {
                        float fv = FUN_00c0ce80(2, 1);
                        FUN_009b3410(fv);
                    }
                }
                if (((mn0B58 >> 9) & 1) != 0) {
                    void* pA = vcall_p(mpAnimatingCreature, 0x70);
                    vcall_vii(pA, 0x40, 2, 1);
                }
                FUN_00c12310(0x2481de5, 0xffffffff, 0);
            }
        }
    }

done:
    FUN_00c214a0(pOld, param_3);
    if (pOld != 0) {
        int r = vcall_i(pOld, 0x70);
        if (r != 0) {
            pOld->SetAttachments(0);
            void* p = vcall_p(pOld, 0x70);
            vcall_v(p, 0x3c);
        }
    }

tail:
    if (mpAnimatingCreature != 0) {
        *((uint8_t*)mpAnimatingCreature + 0x151) = (uint8_t)((mn0B58 >> 9) & 1);
        void* pA = vcall_p(this, 0xd8);
        FUN_00a04c80(pA);
        FUN_00a04ca0(mpAnimatingCreature, mn0B34 == 1);
        FUN_00a04ad0(mpAnimatingCreature, (int)mnF98);
        FUN_00a04cc0(mpAnimatingCreature, (mpArchetype != 0 && mpArchetype->mb388 != 0) ? 1 : 0);
        if (mpArchetype != 0 && mpArchetype->mb388 != 0 &&
            mpAnimatingCreature->mpInstanceData != 0) {
            FUN_009b7b10(0, 0);
        }
    }

    return (mpAnimatingCreature != 0 && mpAnimatingCreature->mpInstanceData != 0) ? true : false;
}
