// Slice s00c75e70 -- SPGameData.obj: the STL/eastl container writers, cPlayer's war-price helpers,
// the cSpacePlayerWarData constructors and several eastl container internals (hashtable rehash/erase,
// rbtree/hashtable iteration, copy loops).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned int   U32;
typedef unsigned char  U8;
typedef unsigned __int64 U64;

// ---------------------------------------------------------------------------------- EA::IO
struct EA_IO_Stream;                                                       // opaque IO stream
void __cdecl IO_WriteUint32(EA_IO_Stream* s, const U32* p, U32 n, U32 flags);   // 0x0093aa70
bool __cdecl IO_WriteBool8(EA_IO_Stream* s, const bool* p, U32 n);              // 0x0093a9a0

// ---------------------------------------------------------------------------------- serializer
struct ISerializerStream {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual EA_IO_Stream* GetStream();              // +0x18
};

struct ISerializer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual void EndItem();                         // +0x1c
    virtual ISerializerStream* GetStreamHolder();   // +0x20
};

template <typename T>
struct cVector {
    T* mpBegin;     // +0x00
    T* mpEnd;       // +0x04
    T* mpCap;       // +0x08
};

// ---------------------------------------------------------------------------------- misc externs
struct cRBNodeBase {
    cRBNodeBase* mpNodeRight;   // +0x00
    cRBNodeBase* mpNodeLeft;    // +0x04
    cRBNodeBase* mpNodeParent;  // +0x08
    U8           mbColor;       // +0x0c
};

cRBNodeBase* __cdecl RBTreeIncrement(const cRBNodeBase* pNode);            // 0x00921580

// eastl::rbtree<U32, ...> head: comparator, node anchor (end() == &anchor), size
struct cRBTreeU32 {
    U32          mCompare;  // +0x00
    cRBNodeBase  mAnchor;   // +0x04
    U32          mnSize;    // +0x14
    void __thiscall Find(cRBNodeBase** ppResult, const U32* pKey);   // 0x00e5c780
};

// object the fixup helpers register their members with
struct IRegisterHost {
    void __thiscall Register(void* pValue, U32* pData, const wchar_t* pName);  // 0x00695b40
};

void* __cdecl operator_new(U32 size, const char* pName, int a, int b, const char* pAlloc, U32 line); // 0x00f473a0
void  __cdecl operator_delete(void* p);                                                  // 0x00f47380

extern const char  g_szSimulator[];        // 0x013f09b4 "Simulator"
extern const char  g_szAllocator[];        // 0x013ebb38 eastl allocator.h path
extern U32         g_1579600;              // 0x01579600
extern U32         g_1579858;              // 0x01579858
extern float       g_f0p001;               // 0x013f9428, 0.001f
extern U32         g_vtblTimerBase;        // 0x01465d54
extern U32         g_vtblTimer;            // 0x01464450
extern U32         g_vtblWarData;          // 0x01472cc8
extern U32         g_f13f4fd0;             // 0x013f4fd0, 2^31 (unsigned int -> float fixup)

void __cdecl FUN_00ae2e40(ISerializer* pWriter, void* pElem);            // 0x00ae2e40
void __cdecl FUN_00c75ba0(ISerializer* pWriter, void* pElem);            // 0x00c75ba0

// ---------------------------------------------------------------------------------- timer
struct cSPTimer {
    U32 mpVftblBase;    // +0x00
    U32 mRefCount;      // +0x04
    U64 mElapsed;       // +0x08
    U64 mBase;          // +0x10
    U8  mbRunning;      // +0x18
    U8  pad19[3];       // +0x19
    U32 mpFn;           // +0x1c
    U64 __thiscall GetElapsedTime();                 // 0x00bc3190
    void __thiscall Write(ISerializer* pWriter);     // 0x00b638d0
};

// pair<U32, cGonzagoTimer> inside the eastl vectors (0x28 bytes)
struct cTimerPair {
    U32        mId;         // +0x00
    U32        pad04;       // +0x04
    cSPTimer   mTimer;      // +0x08
};

// the Gonzago timer embedded in a sequence element (its copy ctor skips the vtable/refcount)
struct cGonzagoTimerC {
    U32 mdVtbl;     // +0x00
    U32 mnRef;      // +0x04
    U64 mElapsed;   // +0x08
    U64 mBase;      // +0x10
    U8  mbRunning;  // +0x18
    U8  pad19[3];   // +0x19
    U32 mpFn;       // +0x1c
};

// 0x28-byte element used by the sequence writers (0x20-byte payload)
struct CElemTimer {
    U32            mId;     // +0x00
    U32            pad04;   // +0x04
    cGonzagoTimerC mTimer;  // +0x08
};

// @ 0x00c75e70
void __cdecl WriteTimerSequence(ISerializer* pWriter, cVector<cTimerPair>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (cTimerPair* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem) {
        U32 nId = pItem->mId;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nId, 1, 0);
        pItem->mTimer.Write(pWriter);
    }
    pWriter->EndItem();
}

// ---------------------------------------------------------------------------------- embassy map
struct cEmbassyData {
    U32 mInt00;     // +0x00
    U32 mInt04;     // +0x04
};

struct cEmbassyNode {
    cRBNodeBase  mBase;     // +0x00
    U32          mKey;      // +0x10
    cEmbassyData mData;     // +0x14
};

struct cEmbassyMap {
    U32          mCompare;  // +0x00
    cRBNodeBase  mAnchor;   // +0x04
    U32          mnSize;    // +0x14
};

// @ 0x00c75f10
void __cdecl WriteEmbassyMap(ISerializer* pWriter, cEmbassyMap& map)
{
    U32 nCount = map.mnSize;
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    cEmbassyNode* pEnd = (cEmbassyNode*)&map.mAnchor;
    for (cEmbassyNode* pNode = (cEmbassyNode*)map.mAnchor.mpNodeLeft; pNode != pEnd;
         pNode = (cEmbassyNode*)RBTreeIncrement(&pNode->mBase)) {
        U32 nKey = pNode->mKey;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nKey, 1, 0);
        pWriter->EndItem();
        U32 nInt04 = pNode->mData.mInt04;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nInt04, 1, 0);
        U32 nInt00 = pNode->mData.mInt00;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nInt00, 1, 0);
        pWriter->EndItem();
    }
    pWriter->EndItem();
}

// ---------------------------------------------------------------------------------- key/bool pairs
struct IWritable {
    virtual void Write(ISerializer* pWriter);       // +0x00
};

// one element of the vector_map<EA::ResourceMan::Key, bool> (0xb0 bytes, value object at +0x08)
struct cKeyBoolPair {
    U32        mKey;        // +0x00
    U32        pad04;       // +0x04
    IWritable  mValue;      // +0x08
    U8         pad00c[0xa4];
};

// @ 0x00c76010
void __cdecl WriteKeyBoolMap(ISerializer* pWriter, cVector<cKeyBoolPair>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (cKeyBoolPair* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem) {
        U32 nKey = pItem->mKey;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nKey, 1, 0);
        pWriter->EndItem();
        pItem->mValue.Write(pWriter);
        pWriter->EndItem();
    }
    pWriter->EndItem();
}

// @ 0x00c760c0
bool __cdecl FixupPlayerPlanetData(void* pCtx, cVector<cKeyBoolPair>& items)
{
    for (cKeyBoolPair* pItem = items.mpBegin; pItem != items.mpEnd; ++pItem) {
        if (&pItem->mValue != 0)
            ((IRegisterHost*)pCtx)->Register(&pItem->mValue, &g_1579600, L"PlayerPlanetData");
    }
    return true;
}

// ---------------------------------------------------------------------------------- 0x14 / 4-byte vectors
struct CElem20 {
    U32 md000[5];
};

// @ 0x00c76100
void __cdecl WriteElem20Vector(ISerializer* pWriter, cVector<CElem20>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (CElem20* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem)
        FUN_00c75ba0(pWriter, pItem);
    pWriter->EndItem();
}

// object whose Write lives at virtual slot +0x1c
struct IWritable7 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual void Write(ISerializer* pWriter);       // +0x1c
};

// an element holding an eastl vector of objects
struct CObjectList {
    IWritable7** mpBegin;   // +0x00
    IWritable7** mpEnd;     // +0x04
    U32*         mpCap;     // +0x08
    U32          mInt0c;    // +0x0c
    U32          mInt10;    // +0x10
};

// @ 0x00c76170
bool __cdecl WriteObjectLists(ISerializer* pWriter, cVector<CObjectList>& items)
{
    for (CObjectList* pList = items.mpBegin; pList != items.mpEnd; ++pList) {
        for (U32 i = 0; i < (U32)(pList->mpEnd - pList->mpBegin); ++i)
            pList->mpBegin[i]->Write(pWriter);
    }
    return true;
}

// @ 0x00c761c0
void __cdecl WriteU32Vector(ISerializer* pWriter, cVector<U32>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (U32* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem) {
        U32 nValue = *pItem;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nValue, 1, 0);
    }
    pWriter->EndItem();
}

// 0x10-byte element: id + 0x20-byte payload + trailing flag at +0x0c
struct CElem16 {
    U32 mId;        // +0x00
    U32 md004;      // +0x04
    U32 md008;      // +0x08
    U8  mb00c;      // +0x0c
    U8  pad00d[3];  // +0x0d
};

// @ 0x00c76250
void __cdecl WriteElem16Vector(ISerializer* pWriter, cVector<CElem16>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (CElem16* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem) {
        FUN_00ae2e40(pWriter, pItem);
        pWriter->EndItem();
        bool bValue = pItem->mb00c != 0;
        IO_WriteBool8(pWriter->GetStreamHolder()->GetStream(), &bValue, 1);
        pWriter->EndItem();
    }
    pWriter->EndItem();
}

// 8-byte element: id + flag at +0x04
struct CElem8 {
    U32 mId;        // +0x00
    U8  mb004;      // +0x04
    U8  pad005[3];  // +0x05
};

// @ 0x00c76300
void __cdecl WriteElem8Vector(ISerializer* pWriter, cVector<CElem8>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (CElem8* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem) {
        U32 nId = pItem->mId;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nId, 1, 0);
        pWriter->EndItem();
        bool bValue = pItem->mb004 != 0;
        IO_WriteBool8(pWriter->GetStreamHolder()->GetStream(), &bValue, 1);
        pWriter->EndItem();
    }
    pWriter->EndItem();
}

// ---------------------------------------------------------------------------------- hashtable (A)
// node: key@0, hash@8, chain link@0xc
struct cHashNodeA {
    U32 mKey;           // +0x00
    U32 mInt04;         // +0x04
    U32 mInt08;         // +0x08 (xor-ed with the key to form the bucket index)
    U32 mpNext0c;       // +0x0c
};

struct cHashTableA {
    U32          md000;       // +0x00
    cHashNodeA** mpBuckets;   // +0x04
    U32          mnBuckets;   // +0x08
    U32          pad00c;      // +0x0c
    U32          pad010[3];   // +0x10
    U32          mpFreeList;  // +0x1c
    U32          pad020;      // +0x20
    U32          mpAllocBegin;// +0x24
    U32          mpAllocEnd;  // +0x28
    U32          pad02c;      // +0x2c
    U32          mpSentinel;  // +0x30

    void __thiscall Rehash(U32 nBuckets);   // 0x00c76440
};

cHashNodeA** __cdecl AllocBucketArray(U32 nBuckets);      // 0x00c763d0

// @ 0x00c76440
void __thiscall cHashTableA::Rehash(U32 nBuckets)
{
    cHashNodeA** pNewBuckets = AllocBucketArray(nBuckets);
    for (U32 i = 0; i < mnBuckets; ++i) {
        cHashNodeA* pNode = mpBuckets[i];
        while (pNode != 0) {
            U32 nIndex = (pNode->mInt08 ^ pNode->mKey) % nBuckets;
            mpBuckets[i] = (cHashNodeA*)pNode->mpNext0c;
            pNode->mpNext0c = (U32)pNewBuckets[nIndex];
            pNewBuckets[nIndex] = pNode;
            pNode = mpBuckets[i];
        }
    }
    cHashNodeA** pOldBuckets = mpBuckets;
    if (mnBuckets > 1 && pOldBuckets != (cHashNodeA**)mpSentinel) {
        if ((U32)pOldBuckets >= mpAllocBegin && (U32)pOldBuckets < mpAllocEnd) {
            *pOldBuckets = (cHashNodeA*)mpFreeList;
            mpFreeList = (U32)pOldBuckets;
            mpBuckets = pNewBuckets;
            mnBuckets = nBuckets;
            return;
        }
        operator_delete(pOldBuckets);
    }
    mpBuckets = pNewBuckets;
    mnBuckets = nBuckets;
}

// ---------------------------------------------------------------------------------- cPlayer war data
struct cWarRecord {
    U32        mId;         // +0x00
    U32        pad04;       // +0x04
    cSPTimer   mTimer;      // +0x08
};

// rbtree node of the player's per-enemy war map
struct cWarNode {
    cRBNodeBase mBase;      // +0x00
    U32         mKey;       // +0x10
    U32         mInt14;     // +0x14
    U32         pad018[4];  // +0x18
    cSPTimer    mTimer;     // +0x28
    U32         pad048;     // +0x48
    U32         mInt4c;     // +0x4c
    U32         mInt50;     // +0x50
    U32         mInt54;     // +0x54
};

struct cWarMap {
    U32          mCompare;  // +0x00
    cRBNodeBase  mAnchor;   // +0x04
    U32          mnSize;    // +0x14
    void __thiscall Find(cRBNodeBase** ppResult, const U32* pKey);   // 0x00e5c780
};

struct cPlayer {
    U32     md000[0x84 / 4];    // +0x000
    U32     mEmpireId;          // +0x084
    U32     pad088[0x1170 / 4]; // +0x088 .. +0x11f7
    cWarMap mWars;              // +0x11f8

    void  __thiscall AddWarCaptureIncrement(U32 a, U32 b);      // 0x00c76790
    int   __thiscall GetPeacePriceForPlayer(cPlayer* pEnemy);   // 0x00c76800
    float __thiscall GetPlayerWarElapsedSeconds(cPlayer* pOther); // 0x00c769b0
    int   __thiscall GetPlayerWarCaptureDelta(cPlayer* pOther);   // 0x00c76a30
};

U32   __cdecl GetPlayerEmpireID();                          // 0x01021090
void* __cdecl FUN_01021300();                               // 0x01021300
void* __cdecl EconomyTuning();                              // 0x0102f810
int   __cdecl RoundFloat(float f);                          // 0x011e0810
void* __fastcall FUN_00c308d0(void* pEmpire);               // 0x00c308d0 (cEmpire::GetStars)
void* __cdecl RelationshipManager();                        // 0x00b3d2c0
void* __cdecl StarManager(void* p);                         // 0x00b3d2a0
void* __fastcall FUN_00baf700(void* pThis);                 // 0x00baf700
float __cdecl FUN_010307a0(void* p, U32 a, U32 b);          // 0x010307a0

struct IEconTuning {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual float GetPeacePriceElapsedSecondsFactor();  // +0x10
    virtual float GetPeacePricePlayerSizeFactor();      // +0x14
    virtual float GetPeacePriceEnemySizeFactor();       // +0x18
    virtual float GetPeacePriceCaptureFactor();         // +0x1c
    virtual float GetPeacePriceRelationshipFactor();    // +0x20
};

struct IRelationshipManager {
    virtual void r0(); virtual void r1(); virtual void r2();
    virtual float GetRelationship(void* pOther, U32 nEmpireId, int nFlag);   // +0x0c
};

struct cStarList {
    U32* mpBegin;   // +0x00
    U32* mpEnd;     // +0x04
    U32* mpCap;     // +0x08
};

// @ 0x00c76790
void __thiscall cPlayer::AddWarCaptureIncrement(U32 nAttacker, U32 nDefender)
{
    U32 nPlayer = GetPlayerEmpireID();
    if (nAttacker == nPlayer || nDefender == nPlayer) {
        U32 nOther = nAttacker;
        if (nAttacker == nPlayer)
            nOther = nDefender;
        cRBNodeBase* pFound;
        mWars.Find(&pFound, &nOther);
        if (pFound != (cRBNodeBase*)&mWars.mAnchor) {
            cWarNode* pNode = (cWarNode*)pFound;
            if (nAttacker == nPlayer)
                ++pNode->mInt50;
            else
                ++pNode->mInt4c;
        }
    }
}

// @ 0x00c76800
int __thiscall cPlayer::GetPeacePriceForPlayer(cPlayer* pEnemy)
{
    cRBNodeBase* pFound;
    U32 nEnemyId = pEnemy->mEmpireId;
    mWars.Find(&pFound, &nEnemyId);
    if (pFound == (cRBNodeBase*)&mWars.mAnchor)
        return -1;

    cWarNode* pNode = (cWarNode*)pFound;
    cPlayer* pMe = (cPlayer*)FUN_01021300();

    U64 nElapsed = pNode->mTimer.GetElapsedTime();
    float fElapsed = (float)nElapsed * g_f0p001;
    int nElapsedPrice = RoundFloat(((IEconTuning*)EconomyTuning())->GetPeacePriceElapsedSecondsFactor() * fElapsed);

    cStarList* pMyStars = (cStarList*)FUN_00c308d0(pMe);
    int nMyStarCount = (int)(pMyStars->mpEnd - pMyStars->mpBegin);
    int nMySizePrice = RoundFloat(((IEconTuning*)EconomyTuning())->GetPeacePricePlayerSizeFactor() * (float)nMyStarCount);

    cStarList* pEnemyStars = (cStarList*)FUN_00c308d0(pEnemy);
    int nEnemyStarCount = (int)(pEnemyStars->mpEnd - pEnemyStars->mpBegin);
    int nEnemySizePrice = RoundFloat(((IEconTuning*)EconomyTuning())->GetPeacePriceEnemySizeFactor() * (float)nEnemyStarCount);

    int nCaptureDelta = (int)pNode->mInt50 - (int)pNode->mInt54;
    int nCapturePrice = RoundFloat(((IEconTuning*)EconomyTuning())->GetPeacePriceCaptureFactor() * nCaptureDelta);

    float fRelationship = ((IRelationshipManager*)RelationshipManager())->GetRelationship(pEnemy, pMe->mEmpireId, 0);
    int nRelationshipPrice = RoundFloat(((IEconTuning*)EconomyTuning())->GetPeacePriceRelationshipFactor() * fRelationship);

    int nTotal = nRelationshipPrice + nCapturePrice + nEnemySizePrice + nMySizePrice + nElapsedPrice;

    void* pStarRec = FUN_00baf700(StarManager(pEnemy));
    float fScale = FUN_010307a0(pStarRec, 0x686e2a4, 0x686e2a8) * nTotal;
    return RoundFloat(fScale);
}

// @ 0x00c769b0
float __thiscall cPlayer::GetPlayerWarElapsedSeconds(cPlayer* pOther)
{
    cRBNodeBase* pFound;
    U32 nEnemyId = pOther->mEmpireId;
    mWars.Find(&pFound, &nEnemyId);
    if (pFound != (cRBNodeBase*)&mWars.mAnchor) {
        cWarNode* pNode = (cWarNode*)pFound;
        U64 nElapsed = pNode->mTimer.GetElapsedTime();
        return (float)nElapsed * g_f0p001;
    }
    return 0.0f;
}

// @ 0x00c76a30
int __thiscall cPlayer::GetPlayerWarCaptureDelta(cPlayer* pOther)
{
    cRBNodeBase* pFound;
    U32 nEnemyId = pOther->mEmpireId;
    mWars.Find(&pFound, &nEnemyId);
    if (pFound != (cRBNodeBase*)&mWars.mAnchor) {
        cWarNode* pNode = (cWarNode*)pFound;
        return (int)pNode->mInt50 - (int)pNode->mInt54;
    }
    return 0;
}

// ---------------------------------------------------------------------------------- hashtable (B) erase
// node: key@0, next@8
struct cHashNodeB {
    U32 mKey;       // +0x00
    U32 mInt04;     // +0x04
    U32 mpNext08;   // +0x08
};

struct cHashTableB {
    U32          md000;       // +0x00
    cHashNodeB** mpBuckets;   // +0x04
    U32          mnBuckets;   // +0x08
    U32          mnElements;  // +0x0c
    U32          pad010[3];   // +0x10
    U32          mpFreeList;  // +0x1c
    U32          pad020;      // +0x20
    U32          mpAllocBegin;// +0x24
    U32          mpAllocEnd;  // +0x28
    U32          pad02c;      // +0x2c
    U32          mpSentinel;  // +0x30

    int __thiscall Erase(const U32* pKey);   // 0x00c76be0
};

// @ 0x00c76be0
int __thiscall cHashTableB::Erase(const U32* pKey)
{
    int nOldCount = (int)mnElements;
    U32 nIndex = *pKey % mnBuckets;
    cHashNodeB** pSlot = &mpBuckets[nIndex];

    if (*pSlot != 0) {
        cHashNodeB* pNode;
        do {
            pNode = *pSlot;
            if (*pKey == pNode->mKey)
                break;
            pSlot = (cHashNodeB**)&pNode->mpNext08;
        } while (pNode->mpNext08 != 0);

        while (*pSlot != 0) {
            pNode = *pSlot;
            if (*pKey != pNode->mKey)
                break;
            *pSlot = (cHashNodeB*)pNode->mpNext08;
            if (pNode != (cHashNodeB*)mpSentinel) {
                if ((U32)pNode >= mpAllocBegin && (U32)pNode < mpAllocEnd) {
                    pNode->mKey = mpFreeList;
                    mpFreeList = (U32)pNode;
                } else {
                    operator_delete(pNode);
                }
            }
            --mnElements;
        }
    }
    return nOldCount - (int)mnElements;
}

// ---------------------------------------------------------------------------------- hashtable write
struct cHashNodeC {
    U32 mKey;       // +0x00
    U32 mInt04;     // +0x04
    U32 mInt08;     // +0x08
    U32 mpNext0c;   // +0x0c
};

struct cHashTableC {
    U32          md000;       // +0x00
    cHashNodeC** mpBuckets;   // +0x04
    U32          mnBuckets;   // +0x08
    U32          mnElements;  // +0x0c
};

// @ 0x00c76c70
void __cdecl WriteHashMap(ISerializer* pWriter, cHashTableC& table)
{
    U32 nCount = table.mnElements;
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);

    cHashNodeC** pBucket = table.mpBuckets;
    cHashNodeC* pNode = *pBucket;
    if (pNode == 0) {
        do {
            ++pBucket;
        } while (*pBucket == 0);
        pNode = *pBucket;
    }
    cHashNodeC* pEnd = table.mpBuckets[table.mnBuckets];
    while (pNode != pEnd) {
        FUN_00ae2e40(pWriter, pNode);
        pWriter->EndItem();
        pNode = (cHashNodeC*)pNode->mpNext0c;
        if (pNode == 0) {
            do {
                ++pBucket;
                pNode = *pBucket;
            } while (pNode == 0);
        }
    }
    pWriter->EndItem();
}

// ---------------------------------------------------------------------------------- second tree map
struct IWritable2 {
    virtual void v0(); virtual void v1();
    virtual void Write(ISerializer* pWriter);        // +0x08
};

struct cU32Node {
    cRBNodeBase mBase;      // +0x00
    U32         mKey;       // +0x10
    U32         pad014;     // +0x14
    IWritable2  mValue;     // +0x18
};

struct cU32Map {
    U32          mCompare;  // +0x00
    cRBNodeBase  mAnchor;   // +0x04
    U32          mnSize;    // +0x14
};

// @ 0x00c76d60
void __cdecl WriteU32Map(ISerializer* pWriter, cU32Map& map)
{
    U32 nCount = map.mnSize;
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    cU32Node* pEnd = (cU32Node*)&map.mAnchor;
    for (cU32Node* pNode = (cU32Node*)map.mAnchor.mpNodeLeft; pNode != pEnd;
         pNode = (cU32Node*)RBTreeIncrement(&pNode->mBase)) {
        U32 nKey = pNode->mKey;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nKey, 1, 0);
        pWriter->EndItem();
        pNode->mValue.Write(pWriter);
        pWriter->EndItem();
    }
    pWriter->EndItem();
}

// ---------------------------------------------------------------------------------- war-data fixup
struct cWarDataNode {
    cRBNodeBase        mBase;      // +0x00
    U32                mKey;       // +0x10
    U32                pad014;     // +0x14
    struct cWarDataRec* mpValue;   // +0x18 -> value object at +0x18
};

// @ 0x00c76e10
bool __cdecl FixupWarData(void* pCtx, cWarMap& map)
{
    cWarDataNode* pEnd = (cWarDataNode*)&map.mAnchor;
    for (cWarDataNode* pNode = (cWarDataNode*)map.mAnchor.mpNodeLeft; pNode != pEnd;
         pNode = (cWarDataNode*)RBTreeIncrement(&pNode->mBase)) {
        if (&pNode->mpValue != 0)
            ((IRegisterHost*)pCtx)->Register(&pNode->mpValue, &g_1579858, L"cSpacePlayerWarData");
    }
    return true;
}

// ---------------------------------------------------------------------------------- war data objects
// record with the timer at +0x08 (the tree-node payload)
struct cWarRec {
    U32        mInt00;      // +0x00
    U32        mInt04;      // +0x04
    cSPTimer   mTimer;      // +0x08

    cWarRec* __thiscall CopyFrom(const cWarRec& src);   // 0x00c76f10
};

// the standalone war-data object (timer at +0x10)
struct cSpacePlayerWarData {
    U32        mpVftbl00;         // +0x00
    U32        mInt04;            // +0x04
    U32        mEnemyEmpireID;    // +0x08
    U32        mInt0c;            // +0x0c
    cSPTimer   mTimer;            // +0x10
    U32        mPlayerStartStars; // +0x30
    U32        mEnemyStartStars;  // +0x34
    U32        mPlayerCaptured;   // +0x38
    U32        mEnemyCaptured;    // +0x3c

    cSpacePlayerWarData* __thiscall ctor(const cSpacePlayerWarData& src);   // 0x00c76f60
};

// @ 0x00c76f10
cWarRec* __thiscall cWarRec::CopyFrom(const cWarRec& src)
{
    mInt00 = src.mInt00;
    mTimer.mpVftblBase = (U32)&g_vtblTimerBase;
    mTimer.mRefCount = 0;
    mTimer.mElapsed = src.mTimer.mElapsed;
    mTimer.mBase = src.mTimer.mBase;
    mTimer.mbRunning = src.mTimer.mbRunning;
    mTimer.mpFn = src.mTimer.mpFn;
    mTimer.mpVftblBase = (U32)&g_vtblTimer;
    return this;
}

// @ 0x00c76f60
cSpacePlayerWarData* __thiscall cSpacePlayerWarData::ctor(const cSpacePlayerWarData& src)
{
    mpVftbl00 = (U32)&g_vtblWarData;
    mEnemyEmpireID = src.mEnemyEmpireID;
    mTimer.mpVftblBase = (U32)&g_vtblTimerBase;
    mTimer.mRefCount = 0;
    mTimer.mElapsed = src.mTimer.mElapsed;
    mTimer.mBase = src.mTimer.mBase;
    mTimer.mbRunning = src.mTimer.mbRunning;
    mTimer.mpFn = src.mTimer.mpFn;
    mTimer.mpVftblBase = (U32)&g_vtblTimer;
    mPlayerStartStars = src.mPlayerStartStars;
    mEnemyStartStars = src.mEnemyStartStars;
    mPlayerCaptured = src.mPlayerCaptured;
    mEnemyCaptured = src.mEnemyCaptured;
    return this;
}

// ---------------------------------------------------------------------------------- eastl copy helpers
void* __cdecl FUN_00bdaa40(void* pDst, void* pSrcBegin, void* pSrcEnd, void* pNew, void* pExtra); // 0x00bdaa40

// a 0x14-byte element holding an eastl vector of U32
struct CSubList {
    U32* mpBegin;   // +0x00
    U32* mpEnd;     // +0x04
    U32* mpCap;     // +0x08
    U32  mInt0c;    // +0x0c
    U32  mInt10;    // +0x10
};

// @ 0x00c77020
CSubList** __cdecl FUN_00c77020(CSubList** ppOut, CSubList* pSrcBegin, CSubList* pSrcEnd, CSubList* pDst, CSubList* pEnd)
{
    *ppOut = pEnd;
    for (; pSrcBegin != pSrcEnd; ++pSrcBegin) {
        CSubList* pItem = *ppOut;
        if (pItem != 0) {
            U32 nCount = (U32)(pSrcBegin->mpEnd - pSrcBegin->mpBegin);
            U32* pNew;
            if (nCount != 0)
                pNew = (U32*)operator_new(nCount * 4, g_szSimulator, 0, 0, g_szAllocator, 0xd1);
            else
                pNew = 0;
            pItem->mpBegin = pNew;
            pItem->mpEnd = pNew;
            pItem->mpCap = pNew + nCount;
            CSubList* pResult;
            FUN_00bdaa40(&pResult, pSrcBegin->mpBegin, pSrcBegin->mpEnd, pNew, pEnd);
            pItem->mpEnd = pResult->mpEnd;
        }
        *ppOut += 1;
    }
    return ppOut;
}

// @ 0x00c770d0
void __cdecl FUN_00c770d0(CSubList* pDst, U32 nCount, CSubList* pSrc)
{
    if (nCount == 0)
        return;
    CSubList* pItem = pDst;
    do {
        if (pItem != (CSubList*)4) {
            U32 nSub = (U32)(pSrc->mpEnd - pSrc->mpBegin);
            U32* pNew;
            if (nSub != 0)
                pNew = (U32*)operator_new(nSub * 4, g_szSimulator, 0, 0, g_szAllocator, 0xd1);
            else
                pNew = 0;
            pItem->mpBegin = pNew;
            pItem->mpEnd = pNew;
            pItem->mpCap = pNew + nSub;
            CSubList* pResult;
            FUN_00bdaa40(&pResult, pSrc->mpBegin, pSrc->mpEnd, pNew, (void*)nCount);
            pItem->mpEnd = pResult->mpEnd;
        }
        --nCount;
        ++pItem;
    } while (nCount != 0);
}

// @ 0x00c77160
CElemTimer* __cdecl FUN_00c77160(const CElemTimer* pSrcBegin, const CElemTimer* pSrcEnd, CElemTimer* pDst)
{
    if (pSrcBegin == pSrcEnd)
        return pDst;
    for (; pSrcBegin != pSrcEnd; ++pSrcBegin, ++pDst) {
        if (pDst != 0) {
            pDst->mId = pSrcBegin->mId;
            pDst->mTimer.mdVtbl = (U32)&g_vtblTimerBase;
            pDst->mTimer.mnRef = 0;
            pDst->mTimer.mElapsed = pSrcBegin->mTimer.mElapsed;
            pDst->mTimer.mBase = pSrcBegin->mTimer.mBase;
            pDst->mTimer.mbRunning = pSrcBegin->mTimer.mbRunning;
            pDst->mTimer.mpFn = pSrcBegin->mTimer.mpFn;
            pDst->mTimer.mdVtbl = (U32)&g_vtblTimer;
        }
    }
    return pDst;
}

// @ 0x00c771e0
CElemTimer* __cdecl FUN_00c771e0(const CElemTimer* pSrcBegin, const CElemTimer* pSrcEnd, CElemTimer* pDst)
{
    if (pSrcBegin == pSrcEnd)
        return pDst;
    for (; pSrcBegin != pSrcEnd; ++pSrcBegin, ++pDst) {
        pDst->mId = pSrcBegin->mId;
        pDst->mTimer.mElapsed = pSrcBegin->mTimer.mElapsed;
        pDst->mTimer.mBase = pSrcBegin->mTimer.mBase;
        pDst->mTimer.mbRunning = pSrcBegin->mTimer.mbRunning;
        pDst->mTimer.mpFn = pSrcBegin->mTimer.mpFn;
    }
    return pDst;
}

// @ 0x00c77250
CElemTimer* __cdecl FUN_00c77250(const CElemTimer* pFirst, const CElemTimer* pLast, CElemTimer* pResult)
{
    if (pFirst == pLast)
        return pResult;
    do {
        --pLast;
        --pResult;
        pResult->mId = pLast->mId;
        pResult->mTimer.mElapsed = pLast->mTimer.mElapsed;
        pResult->mTimer.mBase = pLast->mTimer.mBase;
        pResult->mTimer.mbRunning = pLast->mTimer.mbRunning;
        pResult->mTimer.mpFn = pLast->mTimer.mpFn;
    } while (pLast != pFirst);
    return pResult;
}

// ---------------------------------------------------------------------------------- small hash helpers
// the hash-set sub-object living at +0x111c of the owning table
struct cHashSubD {
    U32 mDummy;   // +0x00 (sub-object state, not touched by the thunks below)

    void __thiscall FUN_006b6740(U32* pKey);   // 0x006b6740
};

struct cHashTableD {
    U32       md000[0x111c / 4];   // +0x000
    cHashSubD mSub;                // +0x111c
    U32       mpBuckets;           // +0x1120
    U32       mnBuckets;           // +0x1124

    bool __thiscall Contains(U32 nKey);       // 0x00c772c0
    void __thiscall FUN_00c77300(U32 nKey);   // 0x00c77300
};

struct cHashNodeD {
    U32 mKey;       // +0x00
    U32 mpNext04;   // +0x04
};

// @ 0x00c772c0
bool __thiscall cHashTableD::Contains(U32 nKey)
{
    int nCount = 0;
    cHashNodeD* pNode = (cHashNodeD*)(*(U32*)(mpBuckets + (nKey % mnBuckets) * 4));
    while (pNode != 0) {
        if (nKey == pNode->mKey)
            ++nCount;
        pNode = (cHashNodeD*)pNode->mpNext04;
    }
    return nCount != 0;
}

// @ 0x00c77300
void __thiscall cHashTableD::FUN_00c77300(U32 nKey)
{
    mSub.FUN_006b6740(&nKey);
}
