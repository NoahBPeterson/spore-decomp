// Read_00c7aef0 - deserialise the war-data rbtree at SP::cPlayer+0x11f8.
// It is registered in the object-database factory table beside Write_00c76d60;
// the writer walks the same map and writes (u32 key, cSpacePlayerWarData)
// pairs, so this is the matching reader.
//
// Layouts come from the reconstructions of this subsystem in
// src/game/SPGonzago/SPPlayer.cpp (cWarDataNode, cSpacePlayerWarData::ctor
// 0x00c76f60) plus the retail disassembly of this function:
//
//   value : vptr +0x00, mEnemyEmpireID +0x08, cSPTimer +0x10 (0x20 bytes),
//           four star counters at +0x30..+0x3c            (size 0x40)
//   node  : rbtree base +0x00, pair key +0x10, pair value +0x18
//
// Construction is explicit (EASTL Construct/Destroy convention): retail calls
// the timer ctor/dtor directly for both the value temporary and the pair
// temporary, and the function has no unwind frame.  The value is a plain
// aggregate (no default constructor) so the locals keep declaration order.
//
// The build has no /GS cookie in the prologue (no local array is spilled), so
// the function is compiled with /GS- like the rest of its original module:
// Flags: /O2 /MD /Gy /EHsc /TP /Isrc/game/include /GS-
#include "game/types.h"

// ---------------------------------------------------------------------------------------------
// image data (retail addresses; not defined here)
// ---------------------------------------------------------------------------------------------
extern unsigned char g_vtblWarData[];           // 0x01472cc8  SP::cSpacePlayerWarData vtable
extern unsigned char g_vtblTimer[];             // 0x01464450  SP::cSPTimer vtable

// ---------------------------------------------------------------------------------------------
// external helpers (retail addresses; not defined here)
// ---------------------------------------------------------------------------------------------
bool __cdecl ReadInt32(void* pStream, void* pDst, unsigned nCount, int nEndian);  // 0x0093a780

// ---------------------------------------------------------------------------------------------
// SP::cSPTimer (0x20 bytes; the 64-bit members give it 8-byte alignment)
// ---------------------------------------------------------------------------------------------
class cWarTimer {
public:
    void*              mpVtbl;                  // +0x00
    int                mRefCount;               // +0x04
    unsigned __int64   mElapsed;                // +0x08
    unsigned __int64   mBase;                   // +0x10
    unsigned char      mbRunning;               // +0x18
    unsigned char      mPad19[3];               // +0x19
    void*              mpFn;                    // +0x1c

    void Construct();                           // 0x00b63890
    void Destroy();                             // 0x00b638b0
};

// ---------------------------------------------------------------------------------------------
// SP::cSpacePlayerWarData (0x40 bytes)
// ---------------------------------------------------------------------------------------------
class cWarValue {
public:
    void*              mpVtbl;                  // +0x00
    unsigned           mInt04;                  // +0x04 (padding in retail)
    int                mEnemyEmpireID;          // +0x08
    unsigned           mInt0c;                  // +0x0c (padding in retail)
    cWarTimer          mTimer;                  // +0x10
    int                mPlayerStartStars;       // +0x30
    int                mEnemyStartStars;        // +0x34
    int                mPlayerCaptured;         // +0x38
    int                mEnemyCaptured;          // +0x3c

    // EASTL Destroy(): the inlined teardown re-installs the class vptr and then
    // releases the timer (retail emits exactly that store before the dtor call).
    void Destroy()
    {
        mpVtbl = g_vtblWarData;
        mTimer.Destroy();
    }

    // 0x00c76f60 inlined: copy construction installs both vtables and resets
    // the timer reference count.  (A named helper rather than a copy ctor keeps
    // the class's implicit default constructor, so the local stays a plain
    // aggregate and keeps declaration order in the frame.)
    void CopyFrom(const cWarValue& src)
    {
        mpVtbl = g_vtblWarData;
        mEnemyEmpireID = src.mEnemyEmpireID;
        mTimer.mRefCount = 0;
        mTimer.mElapsed = src.mTimer.mElapsed;
        mTimer.mBase = src.mTimer.mBase;
        mTimer.mbRunning = src.mTimer.mbRunning;
        mTimer.mpFn = src.mTimer.mpFn;
        mTimer.mpVtbl = g_vtblTimer;
        mPlayerStartStars = src.mPlayerStartStars;
        mEnemyStartStars = src.mEnemyStartStars;
        mPlayerCaptured = src.mPlayerCaptured;
        mEnemyCaptured = src.mEnemyCaptured;
    }
};

// one map element: u32 key followed (8-byte aligned) by the war-data value
struct cWarPair {
    unsigned   mKey;                            // +0x00
    unsigned   mPad04;                          // +0x04
    cWarValue  mValue;                          // +0x08

    cWarPair(unsigned nKey, const cWarValue& value) : mKey(nKey) { mValue.CopyFrom(value); }
};

// eastl rbtree node base
struct cRBNode {
    cRBNode*       mpLeft;                      // +0x00
    cRBNode*       mpRight;                     // +0x04
    cRBNode*       mpParent;                    // +0x08
    unsigned char  mColor;                      // +0x0c
    unsigned char  mPad0d[3];                   // +0x0d
};

struct cWarNode {
    cRBNode   mBase;                            // +0x00
    cWarPair  mPair;                            // +0x10

    // A duplicate key overwrites the stored value: every cSpacePlayerWarData
    // field except the vptr and the two padding words (retail writes +0x20..+0x54).
    // Spelled on the node so cl folds the value's +0x18 into each displacement
    // instead of materialising `this` (`add eax,0x18`); see keep.md lever 3.
    void AssignFrom(const cWarValue& src)
    {
        mPair.mValue.mEnemyEmpireID = src.mEnemyEmpireID;
        mPair.mValue.mTimer.mElapsed = src.mTimer.mElapsed;
        mPair.mValue.mTimer.mBase = src.mTimer.mBase;
        mPair.mValue.mTimer.mbRunning = src.mTimer.mbRunning;
        mPair.mValue.mTimer.mpFn = src.mTimer.mpFn;
        mPair.mValue.mPlayerStartStars = src.mPlayerStartStars;
        mPair.mValue.mEnemyStartStars = src.mEnemyStartStars;
        mPair.mValue.mPlayerCaptured = src.mPlayerCaptured;
        mPair.mValue.mEnemyCaptured = src.mEnemyCaptured;
    }
};

// the insert tag passed by value to the rbtree helper: eastl::true_type is an
// empty class, so MSVC zeroes the argument slot's first byte and passes the
// dword (retail: `mov byte [esp+0x58],0; mov ecx,[esp+0x58]; push ecx`).
struct cWarInsertTag {
};

// the standalone rbtree helper writes its result through this struct
struct cWarInsertResult {
    cWarNode*  mpNode;                          // +0x00
    bool       mbInserted;                      // +0x04
};

// the tree as stored in SP::cPlayer: compare flag, anchor node, element count
class cWarMap {
public:
    unsigned  mCompare;                         // +0x00
    cRBNode   mAnchor;                          // +0x04
    unsigned  mnSize;                           // +0x14

    void Destroy(cWarNode* pHead);                                           // 0x00c77b10
    void InsertUnique(cWarInsertResult* pResult, const cWarPair* pValue,
                      cWarInsertTag tag);                                    // 0x00c79810
};

// ---------------------------------------------------------------------------------------------
// the serialisation stream and the IO provider it hands out
// ---------------------------------------------------------------------------------------------
class ISerializerReadStream {
public:
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual bool  v1c();                        // element marker
    virtual void* v20();                        // returns the active IO provider
};

class IIOProviderRead {
public:
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void  v10();
    virtual void  v14();
    virtual void* v18();                        // EA::IO stream
};

static void* GetIOStream(ISerializerReadStream* pStream)
{
    return ((IIOProviderRead*)pStream->v20())->v18();
}

// ---------------------------------------------------------------------------------------------
// 0x00c7aef0 - clear the map, then read the count and one (key, value) pair
// per element; a duplicate key overwrites the value already stored in the tree.
// ---------------------------------------------------------------------------------------------
// @ 0x00c7aef0
bool __cdecl Read_00c7aef0(ISerializerReadStream* pStream, cWarMap* pData)
{
    pData->Destroy((cWarNode*)pData->mAnchor.mpParent);

    pData->mAnchor.mpLeft = &pData->mAnchor;
    pData->mAnchor.mpRight = &pData->mAnchor;
    pData->mAnchor.mpParent = 0;
    pData->mAnchor.mColor = 0;
    pData->mnSize = 0;

    unsigned nCount = 0;
    {
        void* pReader = GetIOStream(pStream);
        ReadInt32(pReader, &nCount, 1, 0);
    }

    for (unsigned i = 0; i < nCount; ++i) {
        cWarValue value;
        value.mpVtbl = g_vtblWarData;
        value.mEnemyEmpireID = -1;
        value.mTimer.Construct();
        value.mPlayerStartStars = -1;
        value.mEnemyStartStars = -1;
        value.mPlayerCaptured = -1;
        value.mEnemyCaptured = -1;

        unsigned nKey;
        void* pReader = GetIOStream(pStream);
        ReadInt32(pReader, &nKey, 1, 0);
        pStream->v1c();
        ((bool (__thiscall*)(void*, void*))((void**)value.mpVtbl)[2])(&value, pStream);
        pStream->v1c();

        cWarInsertResult result;
        {
            cWarPair entry(nKey, value);
            pData->InsertUnique(&result, &entry, cWarInsertTag());
            entry.mValue.Destroy();
        }

        if (!result.mbInserted)
            result.mpNode->AssignFrom(value);

        value.Destroy();
    }

    return pStream->v1c();
}
