// Slice s00d78ad0 -- SP module: the "tribe game behaviour party" behaviour
// (Simulator behaviour set), the tribe-in-heat navigation tick and the eastl
// red-black-tree node-insert helpers.  Reconstructed from disassembly.  Only
// primitive types are used so the file is self-contained; every modelled field
// carries a name and every external callee is declared with the calling
// convention the original call site used (MSVC __thiscall callees pop their
// stack arguments, __cdecl callers clean them up).

typedef unsigned char    U8;
typedef unsigned short   U16;
typedef unsigned int     U32;
typedef int              S32;
typedef unsigned __int64 U64;

struct Vector3 { float mX; float mY; float mZ; };

// ---------------------------------------------------------------------------
// Shared virtual-dispatch view.  The objects handled by this module are
// unrelated classes, but the vtable slots that are actually *called* live at
// disjoint offsets, so a single view class with 64 slots covers all of them.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// External callees modelled as stub types so that a call through the stub is
// emitted as a normal member call (__thiscall: `this` in ECX, callee pops).
// ---------------------------------------------------------------------------
struct FnC0BA30  { char   __thiscall f(); };
struct FnC263E0  { void   __thiscall f(int); };
struct FnC22A70  { U32    __thiscall f(); };
struct FnC22F50  { void*  __thiscall f(); };
struct FnC22F50B { void*  __thiscall f(void* pOut, int unused); };
struct FnC91190  { void*  __thiscall f(); };
struct FnC14750  { void   __thiscall f(int); };
struct FnC0CFF0  { void   __thiscall f(int); };
struct FnC0E0C0  { char   __thiscall f(int); };
struct FnC12190  { void   __thiscall f(int, int, int); };
struct FnC42E20  { char   __thiscall f(); };
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
struct Fn9A9600  { void   __thiscall f(void* pNode); };
struct FnC2E4E0  { void   __thiscall f(); };
struct FnE5C780  { void   __thiscall f(void** ppOut, void** pKey); };

// The argument block handed to the base space behaviour's RemoveAgent: it is
// the party function's own stack argument block passed straight through.
struct AgentArgs {
    void* mpBlocks;          // +0x00
    U32   mIndex;            // +0x04
    U32   m4;                // +0x08
    U32   m8;                // +0x0c
    U32   mC;                // +0x10
    U32   m10;               // +0x14
};

struct FnD7A020  { void   __thiscall f(AgentArgs args); };

extern "C" void FUN_00F47380(void* p);                        // operator delete (cdecl-1)
extern "C" void* FUN_00F473A0(U32 size, const char* pName, int flags,
                              int debugFlags, const char* pFile, int line);
extern "C" void* FUN_0059AED0(void* pOut, const void* pTable, U32 key);
extern "C" void  __stdcall FUN_00436CE0(void* pOut, const void* pIn);  // callee pops
extern "C" void  FUN_009216A0(void* pNode, void* pParent, void* pHeader, U32 side);
extern "C" void  FUN_00921580(void* pNode);
extern "C" void  FUN_00921880(void* pNode, void* pHeader);
extern "C" void  FUN_00572020(void* pObj, U32 arg);
extern "C" void  FUN_00DA6270(void* pObj, int arg);

extern const char  gSimulatorName[];   // 0x13f09b4  ("Simulator")
extern const char  gAllocFileName;     // 0x13ebb38

extern float gFloat_147B9F0;      // 0x147b9f0
extern float gFloat_1470F1C;      // 0x1470f1c  (2.0f)
extern float gFloat_1572070;      // 0x1572070
extern U8    gTable169EFD4;       // 0x169efd4
extern U8    gTable169EFE0;       // 0x169efe0
extern void* gVTable147BF60;      // 0x147bf60
extern void* gVTable147BF4C;      // 0x147bf4c

// ---------------------------------------------------------------------------
// eastl red-black tree: node base { left, right, parent, colour }, then the
// keyed pair.  The tree object holds a 4-byte header, the sentinel node and
// the element count.
// ---------------------------------------------------------------------------
struct RBNodeBase {
    RBNodeBase* mpLeft;      // +0x00
    RBNodeBase* mpRight;     // +0x04
    RBNodeBase* mpParent;    // +0x08
    U32         mColor;      // +0x0c
};

struct RBNode {
    RBNodeBase mBase;        // +0x00
    U32        mKey;         // +0x10
    U64        mValue;       // +0x14
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

// 16-byte-pair tree variant (a different instantiation with its own node size).
struct RBValue16 {
    U32 mKey;                // +0x00
    U32 mV0;                 // +0x04
    U32 mV1;                 // +0x08
    U32 mV2;                 // +0x0c
};

struct RBNode16 {
    RBNodeBase mBase;        // +0x00
    RBValue16  mPair;        // +0x10
};

struct RBTree16 {
    U32         mHeader;     // +0x00
    RBNodeBase  mAnchor;     // +0x04
    U32         mSize;       // +0x14

    void InsertNode(RBNode16** ppOut, RBNodeBase* pParent,
                    const RBValue16* pValue, char leftmost);
};

// ---------------------------------------------------------------------------
// The segmented target list embedded in the behaviour party (an eastl-style
// block array of 8-byte records with a free-chain index).
// ---------------------------------------------------------------------------
struct SegEntry {
    void* mpUnk00;           // +0x00
    void* mpBuffer;          // +0x04
};

// cActionCircle occupies 0x64 bytes starting at party+0x9c.
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

struct TribeSub : VT {};

struct TribeObj : VT {
    U8       mPad04[0x34 - 0x04];
    TribeSub mSub34;                 // +0x34
};

struct Tribe : VT {};

// The sort comparator used by FUN_00d78e20.
struct Comparator {
    char __thiscall FUN_00AC0730(void* pA, void* pB);
};

// A scoped holder for the keyed vector lookup's result.
struct ScopedLookup {
    Vector3* mpVec;                  // +0x00
    ~ScopedLookup() {
        if (mpVec != 0 && ((U32*)mpVec)[-1] != 0) {
            FUN_00F47380(mpVec);
        }
    }
};

// ---------------------------------------------------------------------------
// 00d78e20 -- in-place insertion sort over an array of object pointers.  The
// comparison is delegated to the caller-supplied comparator and is applied to
// the objects' +0xc0 sub-objects.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 00d78e90 -- decide whether a candidate agent may join the party.  The
// candidate is asked for its "citizen" sub-object (a behaviour lookup keyed by
// 0x4f176642) which must exist and must not already be flagged busy, and the
// party's current target must be a citizen whose tribe matches the candidate's
// tribe (or whose tribe is accepted directly by FUN_00c8e7c0).
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 00d78f50 -- pick up the next target for the "in heat" behaviour: clear the
// per-action scratch state, let the base interaction install its own handler,
// resolve the current target's citizen, and if that citizen belongs to a tribe
// and no current target object exists, ask the tribe for its tool of type 10.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 00d79000 -- let the current target finish: if there is a target object whose
// citizen has a live reference, release it, then hand control back to the base
// interaction and tear down the scratch object held at +0x90.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 00d79080 -- allocate a tree node for a 16-byte keyed value, decide on which
// side of the parent it belongs, link it into the tree and hand it back through
// the out pointer.
// ---------------------------------------------------------------------------
// @ 0x00d79080
void RBTree16::InsertNode(RBNode16** ppOut, RBNodeBase* pParent, const RBValue16* pValue, char leftmost)
{
    U32 side;
    if (leftmost == 0 && pParent != &mAnchor &&
        pValue->mKey >= ((RBNode16*)pParent)->mPair.mKey) {
        side = 1;
    } else {
        side = 0;
    }
    RBNode16* pNode = (RBNode16*)FUN_00F473A0(0x20, gSimulatorName, 0, 0, &gAllocFileName, 0xd1);
    RBValue16* pDst = &pNode->mPair;
    if (pDst != 0) {
        *pDst = *pValue;
    }
    FUN_009216A0(pNode, pParent, &mAnchor, side);
    mSize++;
    *ppOut = pNode;
}

// ---------------------------------------------------------------------------
// 00d79270 -- remove an agent from the party: look the agent's citizen up in
// the party's agent tree, erase the node (releasing the object) when present
// and forward the removal to the base space behaviour.
// ---------------------------------------------------------------------------
// @ 0x00d79270
void cTribeGameBehaviorParty::RemoveAgent(void** ppBlocks, U32 idx, U32 a3, U32 a4, U32 a5, U32 a6)
{
    SegEntry* pEntry = (SegEntry*)((char*)(((void**)*ppBlocks)[idx >> 7]) + (idx & 0x7f) * 8);
    void* pBuf = pEntry->mpBuffer;
    void* pKey = 0;
    if (pBuf != 0) {
        void* pCitizen = ((VT*)pBuf)->q02(0x4f176642);
        if (pCitizen != 0) {
            ((FnC14750*)pCitizen)->f(0);
            FUN_00DA6270(pCitizen, 0xc);
            pKey = (char*)pCitizen + 0x58;
        }
    }
    RBNodeBase* pFound = 0;
    ((FnE5C780*)&mAgentTree)->f((void**)&pFound, &pKey);
    if (pFound != &mAgentTree.mAnchor) {
        mAgentTree.mSize--;
        FUN_00921580(pFound);
        FUN_00921880(pFound, &mAgentTree.mAnchor);
        FUN_00F47380(pFound);
    }
    ((FnD7A020*)this)->f(*reinterpret_cast<AgentArgs*>(&ppBlocks));
}

// ---------------------------------------------------------------------------
// 00d79350 -- look the key up in the tree; when the key is present return the
// address of its stored value, otherwise insert a zero value for it and return
// the address of the new value.
// ---------------------------------------------------------------------------
// @ 0x00d79350
U32* RBTree::InsertOrFind(const U32* pKey)
{
    RBNodeBase* pNode = mAnchor.mpParent;
    RBNodeBase* pParent = &mAnchor;
    if (pNode != 0) {
        do {
            if (((RBNode16*)pNode)->mPair.mKey < *pKey) {
                pNode = pNode->mpLeft;
            } else {
                pParent = pNode;
                pNode = pNode->mpRight;
            }
        } while (pNode != 0);
    }
    if (pParent != &mAnchor && *pKey >= ((RBNode16*)pParent)->mPair.mKey) {
        return &((RBNode16*)pParent)->mPair.mKey + 1;
    }
    U32 key = *pKey;
    U64 value = 0;
    RBNodeBase* pResult = 0;
    DoInsertValue(&pResult, pParent, &value, pKey);
    return (U32*)((char*)pResult + 0x14);
}

// ---------------------------------------------------------------------------
// 00d793e0 -- admit an agent to the party: the base behaviour must accept it
// and the agent must expose a valid citizen; the citizen is then registered in
// the party's agent tree and its spatial object is refreshed.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 00d78ad0 -- the "tribe in heat" navigation tick.  Called with the acting
// creature (arg1) and, in arg6, a pointer to the behaviour's state word.  While
// the state is 0 a destination is derived from the tribe's mating-interest
// keyed-vector tables and a navigation goal is armed; in states 1 and 2 the
// creature is steered towards that goal and the state is advanced.
// ---------------------------------------------------------------------------
struct NavigationGoal {
    void* mpBuffer;                  // +0x00  owned keyed-vector buffer
    U8    mPad04[0x54];
    void __thiscall InitToward(const Vector3* pFrom, const Vector3* pTo,
                               float speed, float turn);
};

// @ 0x00d78ad0
char FUN_00d78ad0(Creature* pCreature, U32 a2, U32 a3, U32 a4, U32 a5, U32* pState)
{
    if (((pCreature->mFlagsB58 >> 4) & 1) == 0) {
        return 0;
    }
    if (((FnC0BA30*)pCreature)->f() != 0) {
        return 0;
    }
    if (*pState == 0) {
        ((FnC263E0*)pCreature)->f(0);
        if (((FnC22A70*)pCreature)->f() != 0) {
            return 1;
        }
        void* pTribe = ((FnC22F50*)pCreature)->f();
        TribeObj* pObj = (TribeObj*)((VT*)pTribe)->q43();
        TribeSub* pSub = &pObj->mSub34;

        Vector3 a = *((Vector3*)pSub->q11());
        pSub->q29();
        Vector3 r1;
        FUN_0059AED0(&r1, &gTable169EFD4, pSub->q12());
        Vector3 r2;
        FUN_0059AED0(&r2, &gTable169EFE0, pSub->q12());

        float d0 = ((r2.mX + r1.mX) * gFloat_147B9F0 + a.mX) - a.mX;
        float d1 = ((r2.mY + r1.mY) * gFloat_147B9F0 + a.mY) - a.mY;
        float d2 = ((r2.mZ + r1.mZ) * gFloat_147B9F0 + a.mZ) - a.mZ;
        if ((d0 * r1.mX + d2 * r1.mZ) + d1 * r1.mY < 0.0f) {
            float s = ((d0 * r1.mX + d2 * r1.mZ) + d1 * r1.mY) * gFloat_1470F1C;
            d0 -= r1.mX * s;
            d1 -= r1.mY * s;
            d2 -= r1.mZ * s;
        }
        Vector3 d;
        d.mX = d0 + a.mX;
        d.mY = d1 + a.mY;
        d.mZ = d2 + a.mZ;

        Vector3 pos;
        ((FnC22F50B*)pCreature)->f(&pos, 0);
        Vector3 src = *((Vector3*)((FnC91190*)pTribe)->f());
        Vector3 dir;
        dir.mX = src.mX - d.mX;
        dir.mY = src.mY - d.mY;
        dir.mZ = src.mZ - d.mZ;
        Vector3 norm;
        FUN_00436CE0(&norm, &dir);

        NavigationGoal goal;
        goal.mpBuffer = 0;
        goal.InitToward(&d, &norm, gFloat_1572070, 2.0f);
        ((FnC14750*)pCreature)->f(1);
        ((VT*)&pCreature->mSpatial)->q55(&goal);
        ((FnC0CFF0*)pCreature)->f(2);
        *pState = 1;
        if (goal.mpBuffer != 0 && ((U32*)goal.mpBuffer)[-1] != 0) {
            FUN_00F47380(goal.mpBuffer);
        }
        return 1;
    }
    if (*pState - 1 <= 1) {
        if (((FnC42E20*)&pCreature->mSpatial)->f() != 0) {
            if (((FnC0E0C0*)pCreature)->f(0x915f7deb) == 0) {
                ((FnC12190*)pCreature)->f(0x915f7deb, 1, -1);
            }
        }
        *pState = 2;
    }
    return 1;
}