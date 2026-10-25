// src/game/SPGonzago/SPTribeGameBehaviorParty.cpp -- migrated from slice(s) s00d78ad0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeGameBehaviorParty.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void FUN_00F47380(void* p);                        // operator delete (cdecl-1)
extern void* gVTable147BF60;      // 0x147bf60
extern void* gVTable147BF4C;      // 0x147bf4c

// ---- items of slice s00d78ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char    U8;
typedef unsigned int     U32;
typedef unsigned __int64 U64;
struct VT {
    virtual void  q00();                       // +0x00
    virtual void* q01(int id);                 // +0x04
    virtual void* q02(int id);                 // +0x08
    virtual void  q03();                       // +0x0c
    virtual void  q04();                       // +0x10
    virtual void  q05();                       // +0x14
    virtual void  q06();                       // +0x18
    virtual void  q07();                       // +0x1c
    virtual void  q08();                       // +0x20
    virtual void  q09();                       // +0x24
    virtual void  q10();                       // +0x28
    virtual void* q11();                       // +0x2c  -> Vector3*
    virtual U32   q12();                       // +0x30
    virtual void  q13();                       // +0x34
    virtual void  q14();                       // +0x38
    virtual void  q15();                       // +0x3c
    virtual void  q16();                       // +0x40
    virtual void  q17();                       // +0x44
    virtual void  q18();                       // +0x48
    virtual void  q19();                       // +0x4c
    virtual void  q20();                       // +0x50
    virtual void  q21();                       // +0x54
    virtual void* q22();                       // +0x58
    virtual void  q23();                       // +0x5c
    virtual void  q24();                       // +0x60
    virtual void  q25();                       // +0x64
    virtual void  q26();                       // +0x68
    virtual void  q27();                       // +0x6c
    virtual void  q28();                       // +0x70
    virtual float q29();                       // +0x74
    virtual void  q30();                       // +0x78
    virtual void  q31();                       // +0x7c
    virtual void  q32();                       // +0x80
    virtual void  q33();                       // +0x84
    virtual void  q34();                       // +0x88
    virtual void  q35();                       // +0x8c
    virtual void  q36();                       // +0x90
    virtual void  q37();                       // +0x94
    virtual void  q38();                       // +0x98
    virtual void  q39();                       // +0x9c
    virtual void  q40();                       // +0xa0
    virtual void  q41();                       // +0xa4
    virtual void  q42();                       // +0xa8
    virtual void* q43();                       // +0xac
    virtual void  q44();                       // +0xb0
    virtual void  q45();                       // +0xb4
    virtual void  q46();                       // +0xb8
    virtual void  q47();                       // +0xbc
    virtual void  q48();                       // +0xc0
    virtual void  q49();                       // +0xc4
    virtual void  q50();                       // +0xc8
    virtual void  q51();                       // +0xcc
    virtual void  q52();                       // +0xd0
    virtual void  q53();                       // +0xd4
    virtual void  q54();                       // +0xd8
    virtual void  q55(void* pGoal);            // +0xdc
    virtual void  q56();                       // +0xe0
    virtual void  q57();                       // +0xe4
    virtual void  q58();                       // +0xe8
    virtual void  q59();                       // +0xec
    virtual void  q60();                       // +0xf0
    virtual void  q61();                       // +0xf4
    virtual char  q62();                       // +0xf8
    virtual void  q63();                       // +0xfc
};
struct FnC22F50  { void*  __thiscall f(); };
struct FnC14750  { void   __thiscall f(int); };
struct FnC232C0  { char   __thiscall f(); };
struct FnC8E7C0  { char   __thiscall f(); };
struct FnC9D9E0  { void*  __thiscall f(); };
struct FnC8E7D0  { void   __thiscall f(int); };
struct FnC8F6E0  { void*  __thiscall f(int); };
struct FnD79FD0  { void   __thiscall f(); };
struct FnD7A010  { char   __thiscall f(void* pObj); };
struct FnABF320  { void   __thiscall f(); };
struct FnAFBA10  { void   __thiscall f(); };
struct FnAFBAD0  { void   __thiscall f(); };
struct FnC2E4E0  { void   __thiscall f(); };
extern "C" void FUN_00F47380(void* p);                        // operator delete (cdecl-1)
extern "C" void  FUN_00572020(void* pObj, U32 arg);
extern void* gVTable147BF60;      // 0x147bf60
extern void* gVTable147BF4C;      // 0x147bf4c
struct RBNodeBase {
    RBNodeBase* mpLeft;      // +0x00
    RBNodeBase* mpRight;     // +0x04
    RBNodeBase* mpParent;    // +0x08
    U32         mColor;      // +0x0c
};
struct RBTree {
    U32         mHeader;     // +0x00
    RBNodeBase  mAnchor;     // +0x04  (sentinel; mpParent holds the root)
    U32         mSize;       // +0x14
    U32         mField18;    // +0x18

    U32* InsertOrFind(const U32* pKey);
    void DoInsertValue(RBNodeBase** ppOut, RBNodeBase* pParent, const U64* pValue, const U32* pKey);  // 0x0101280
    void DoNukeSubtree(RBNodeBase* pNode);
};
struct SegEntry {
    void* mpUnk00;           // +0x00
    void* mpBuffer;          // +0x04
};
struct ActionCircle {
    U8 mPad00[0x64];
};
struct cTribeGameBehaviorParty : VT {
    void*   mpVTable2;               // +0x04
    U32     mPad08;                  // +0x08
    void**  mpBlocks;                // +0x0c  target-list block array
    U32     mPad10;                  // +0x10
    U32     mPad14;                  // +0x14
    U32     mPad18;                  // +0x18
    U32     mPad1C;                  // +0x1c
    U32     mPad20;                  // +0x20
    U32     mFreeChain;              // +0x24  target-list free-chain index
    U8      mPad28[0x74 - 0x28];
    RBTree  mAgentTree;              // +0x74
    void*   mpField90;               // +0x90
    U32     mField94;                // +0x94
    float   mField98;                // +0x98
    ActionCircle mCircle9C;          // +0x9c
    U8      mByte100;                // +0x100

    void* Init();
    cTribeGameBehaviorParty* Destroy(U8 flag);
    char CanJoin(void* pAgent, U32 unused);
    void PreAction();
    void PostAction();
    void RemoveAgent(void** ppBlocks, U32 idx, U32 a3, U32 a4, U32 a5, U32 a6);
    char AddAgent(void* pAgent);
};
struct SpatialObject : VT {};
struct Creature : VT {
    U8            mPad04[0xc0 - 0x04];
    SpatialObject mSpatial;          // +0xc0
    U8            mPadC4[0xb58 - 0xc4];
    U32           mFlagsB58;         // +0xb58
};
struct Comparator {
    char __thiscall FUN_00AC0730(void* pA, void* pB);
};
// ---- items of slice s00d78ad0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void  FUN_00572020(void* pObj, U32 arg);

// @ 0x00d78e20
void FUN_00d78e20(void** pFirst, void** pLast, Comparator rComp)
{
    for (void** i = pFirst; i != pLast; ++i) {
        void* value = *i;
        void** j = i;
        void** p = i - 1;
        while (rComp.FUN_00AC0730(value ? (void*)((char*)value + 0xc0) : 0,
                                  *p    ? (void*)((char*)*p    + 0xc0) : 0)) {
            *j = *p;
            --j;
            --p;
        }
        *j = value;
    }
}

// @ 0x00d78e90
char cTribeGameBehaviorParty::CanJoin(void* pAgent, U32 unused)
{
    void* citizen;
    if (pAgent != 0) {
        citizen = ((VT*)pAgent)->q02(0x4f176642);
        if (citizen == 0) goto haveCitizen;
        if (((FnC232C0*)citizen)->f() != 0) goto haveCitizen;
    }
    citizen = 0;
haveCitizen:
    if (mFreeChain != 0x3fffffff) {
        SegEntry* pEntry = (SegEntry*)((char*)mpBlocks[mFreeChain >> 7] + (mFreeChain & 0x7f) * 8);
        void* pBuf = pEntry->mpBuffer;
        if (pBuf != 0) {
            void* pObj = ((VT*)pBuf)->q01(0x116d858);
            if (pObj != 0) {
                if (reinterpret_cast<U32>(((VT*)pObj)->q22()) == 10 && citizen != 0) {
                    if (((FnC22F50*)citizen)->f() != 0) {
                        if (((FnC8E7C0*)((FnC22F50*)citizen)->f())->f() == 0) {
                            void* pA = ((FnC9D9E0*)pObj)->f();
                            void* pB = ((FnC22F50*)citizen)->f();
                            return (pB == pA) ? 1 : 0;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// @ 0x00d78f50
void cTribeGameBehaviorParty::PreAction()
{
    mField94 = 0;
    mField98 = 0.0f;
    mByte100 = 1;
    ((FnC2E4E0*)this)->f();

    void* pCitizen;
    void* pField = ((VT*)this)->q22();
    if (pField != 0) {
        pCitizen = ((VT*)pField)->q02(0x4f176642);
    } else {
        pCitizen = 0;
    }

    void* pObj;
    if (mFreeChain != 0x3fffffff) {
        SegEntry* pEntry = (SegEntry*)((char*)mpBlocks[mFreeChain >> 7] + (mFreeChain & 0x7f) * 8);
        void* pBuf = pEntry->mpBuffer;
        if (pBuf != 0) {
            pObj = ((VT*)pBuf)->q01(0x116d858);
        } else {
            pObj = 0;
        }
    } else {
        pObj = 0;
    }

    if (pCitizen != 0) {
        if (((FnC232C0*)pCitizen)->f() != 0) {
            void* pTribe = ((FnC22F50*)pCitizen)->f();
            if (pTribe != 0 && pObj == 0) {
                ((FnC8F6E0*)pTribe)->f(10);
            }
        }
    }
}

// @ 0x00d79000
void cTribeGameBehaviorParty::PostAction()
{
    if (mFreeChain != 0x3fffffff) {
        SegEntry* pEntry = (SegEntry*)((char*)mpBlocks[mFreeChain >> 7] + (mFreeChain & 0x7f) * 8);
        void* pBuf = pEntry->mpBuffer;
        if (pBuf != 0) {
            void* pObj = ((VT*)pBuf)->q01(0x116d858);
            if (pObj != 0) {
                void* pRef = ((FnC9D9E0*)pObj)->f();
                if (pRef != 0) {
                    ((FnC8E7D0*)pRef)->f(0);
                }
            }
        }
    }
    ((FnC2E4E0*)this)->f();
    if (mpField90 != 0) {
        FUN_00572020(mpField90, 0);
        mpField90 = 0;
    }
}

// @ 0x00d791a0
void* cTribeGameBehaviorParty::Init()
{
    ((FnABF320*)this)->f();                       // base-class constructor
    *reinterpret_cast<void**>(static_cast<VT*>(this)) = &gVTable147BF60;
    mpVTable2 = &gVTable147BF4C;

    mAgentTree.mAnchor.mpRight  = 0;              // +0x7c
    mAgentTree.mAnchor.mpParent = 0;              // +0x80
    mAgentTree.mAnchor.mColor   = 0;              // +0x84
    mAgentTree.mAnchor.mpParent = 0;              // +0x80
    *reinterpret_cast<U8*>(&mAgentTree.mAnchor.mColor) = 0;   // +0x84
    mAgentTree.mSize            = 0;              // +0x88
    mAgentTree.mAnchor.mpLeft   = &mAgentTree.mAnchor;        // +0x78
    mAgentTree.mAnchor.mpRight  = &mAgentTree.mAnchor;        // +0x7c
    mpField90                   = 0;              // +0x90
    ((FnAFBA10*)&mCircle9C)->f();                 // construct the action circle
    return this;
}

// @ 0x00d791f0
cTribeGameBehaviorParty* cTribeGameBehaviorParty::Destroy(U8 flag)
{
    *reinterpret_cast<void**>(static_cast<VT*>(this)) = &gVTable147BF60;
    mpVTable2 = &gVTable147BF4C;
    ((FnAFBAD0*)&mCircle9C)->f();                 // destroy the action circle
    RBNodeBase* pRoot = mAgentTree.mAnchor.mpParent;
    mAgentTree.DoNukeSubtree(pRoot);
    ((FnD79FD0*)this)->f();
    if ((flag & 1) != 0) {
        FUN_00F47380(this);
    }
    return this;
}

// @ 0x00d793e0
char cTribeGameBehaviorParty::AddAgent(void* pAgent)
{
    char result = 0;
    if (((FnD7A010*)this)->f(pAgent) != 0 && pAgent != 0) {
        void* pCitizen = ((VT*)pAgent)->q02(0x4f176642);
        if (pCitizen != 0 && ((FnC232C0*)pCitizen)->f() != 0) {
            void* pKey = (char*)pCitizen + 0x58;
            U32* pSlot = mAgentTree.InsertOrFind(reinterpret_cast<const U32*>(&pKey));
            *pSlot = 0;
            SpatialObject* pSpatial = &((Creature*)pCitizen)->mSpatial;
            U8 flag = (pSpatial->q62() == 0) ? 1 : 0;
            ((FnC14750*)pCitizen)->f(flag);
            ((VT*)pSpatial)->q59();
        }
    }
    return result;
}
