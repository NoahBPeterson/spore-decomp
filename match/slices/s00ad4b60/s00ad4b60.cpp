// Slice s00ad4b60: the SP::Simulator ArgScript "actor" command family from
// SPAppStateManager.obj -- the addActor / moveActor command constructors, the
// addActor execution path (simulator command + behaviour message + editor
// resource graph) and the 0x50-byte actor-info object constructor.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char byte;

// ------------------------------------------------------------------ externs
void* EAAllocate(unsigned int size, const char* tag, int a, int b, int c, int d);  // 0x00f473a0
unsigned __cdecl FNV1_String8(const char* s, unsigned seed, int x);                // 0x00932e80
void* __fastcall EditorResourceCtor(void* p);                                      // 0x00ad7c30
void FUN_00ad4b60();                                                               // 0x00ad4b60
extern "C" long _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

// placement new (the EA allocator supplies the storage)
inline void* operator new(unsigned int, void* p) { return p; }

// vtable symbols that are stored as plain data fields
extern char vtbl_CmdAddActor[];    // 0x0145a87c
extern char vtbl_CmdMoveActor[];   // 0x0145ab74

// default basis triples
extern float g_v4bc;   // 0x0167a4bc
extern float g_v4c0;   // 0x0167a4c0
extern float g_v4c4;   // 0x0167a4c4

// argument-type defaults (":actorType" / ":positionType" enumerations)
extern const char* const g_pstrAvatar;   // 0x01566338
extern const char* const g_pstrEffect;   // 0x015662e0

// vtable-slot call helpers (AddRef = slot 0, Release = slot 1)
#define VCALL0(p, off) \
    ((void (__thiscall*)(void*))(*(void***)(p))[(off) / 4])(p)

struct Vec3 { float x, y, z; };

// ------------------------------------------------------------- base classes
struct CmdBase {
    void* mpVt;       // +0x00
    void* mParser;    // +0x04
    int   mRef;       // +0x08
    CmdBase();        // 0x0083c800
};

struct ArgumentSpec {                 // 0xc8 bytes of parsed-argument state
    byte  pad[0x70];
    unsigned mPosUsed       : 1;      // +0x70 bit 0  (-initialRelativePosition / position)
    unsigned mArchetypeUsed : 1;      // +0x70 bit 1  (-archetype)
    unsigned mHighLODUsed   : 1;      // +0x70 bit 2  (-highLOD)
    unsigned mTribeUsed     : 1;      // +0x70 bit 3  (-tribe)
    unsigned mRest          : 28;     // +0x70 bits 4..31
    byte  pad74[0xc8 - 0x74];
    void Init(int respectHelp);                            // 0x0083a9f0 thiscall ret 4
    void ParseThrowing(void* args, void* parser);          // 0x0083b9d0 thiscall ret 8
};
void BuildArgumentSpec(ArgumentSpec* pSpec, const char* name, ...);   // 0x0083bcd0 cdecl

// Secondary polymorphic base: vptr first, then the reference count. Its inline
// constructor is what puts the base vtable into the object before the derived
// class overwrites it (mirrors the original's two consecutive vptr stores).
struct RefCountBaseV {
    int mRef;                          // +0x04 (relative to this base)
    RefCountBaseV() : mRef(0) {}
    virtual int AddRef();              // slot 0
    virtual int Release();             // slot 1
};

// ------------------------------------------------------- addActor command
struct CmdAddActor : CmdBase {
    void* mpAppState;      // +0x0c
    ArgumentSpec mSpec;    // +0x10
    char* mActorType;      // +0xd8  "<type:actorType>"
    char* mActorName;      // +0xdc  "<actorName:cstring>"
    char* mArchetype;      // +0xe0  "-archetype"
    char* mTribe;          // +0xe4  "-tribe"
    char* mPosType;        // +0xe8  "-initialRelativePosition" posType
    char* mPosName;        // +0xec  "-initialRelativePosition" posName
    Vec3  mInitialPos;     // +0xf0  "-initialRelativePosition" position
    CmdAddActor();         // @ 0x00ad5590
    void Execute(void* args);   // @ 0x00ad5670
};

// ------------------------------------------------------ moveActor command
struct CmdMoveActor : CmdBase {
    void* mpAppState;      // +0x0c
    ArgumentSpec mSpec;    // +0x10
    char* mActorName;      // +0xd8  "<actorName:cstring>"
    Vec3  mPosition;       // +0xdc  "<position:vector3>"
    float mStopDistance;   // +0xe8  "[stopDistance:float]"
    char* mPosType;        // +0xec  "-relative" posType
    char* mPosName;        // +0xf0  "-relative" posName
    char* mFacingType;     // +0xf4  "-face" facingType
    char* mFacingName;     // +0xf8  "-face" facingName
    Vec3  mFacingOffset;   // +0xfc  "-face" facingOffset
    CmdMoveActor();        // @ 0x00ad5900
};

// ------------------------------------------------- actor info (0x50 bytes)
struct ActorInfoBase {                 // primary polymorphic base, no data
    virtual int v0();
};

struct ActorInfo : ActorInfoBase, RefCountBaseV {
    int   mHash;       // +0x0c
    Vec3  mPos;        // +0x10
    Vec3  mPos2;       // +0x1c
    float mZero;       // +0x28
    int   mMode;       // +0x2c
    void* mP30;        // +0x30
    void* mP34;        // +0x34
    void* mP38;        // +0x38
    byte  mB3c;        // +0x3c
    byte  mB3d;        // +0x3d
    int   mKind;       // +0x40
    Vec3  mBasis;      // +0x44
    ActorInfo();       // @ 0x00ad59e0
};

// ------------------------------------------- simulator command (0x38 bytes)
struct SimCommandBase {                // primary polymorphic base, no data
    virtual int v0();
    virtual int v1();
    virtual int v2();
};

struct SimCommand : SimCommandBase, RefCountBaseV {
    int   mActorType;      // +0x0c
    int   mNameHash;       // +0x10
    int   mArchetypeHash;  // +0x14
    int   mTribeHash;      // +0x18
    int   mPosType;        // +0x1c
    int   mPosNameHash;    // +0x20
    int   mKind;           // +0x24
    Vec3  mPosition;       // +0x28
    byte  mHighLOD;        // +0x34
    __forceinline SimCommand()
    {
        mActorType     = 0;
        mNameHash      = 0;
        mArchetypeHash = 0;
        mTribeHash     = 0;
        mPosType       = 0;
        mKind          = 3;
        mPosition.x    = g_v4bc;
        mPosition.y    = g_v4c0;
        mPosition.z    = g_v4c4;
        mHighLOD       = 0;
    }
};

// ----------------------------------------- behaviour message (0x40 bytes)
struct BehaviorMessageBase {           // primary polymorphic base
    volatile long mRef;                // +0x04
    void*         mRefSlot;            // +0x08  (owned RefHandle, released on replace)
    int           mF0c;                // +0x0c
    int           mF10;                // +0x10
    int           mF14;                // +0x14
    int           mF18;                // +0x18
    int           mF1c;                // +0x1c
    int           mF20;                // +0x20
    int           mF24;                // +0x24
    int           mF28;                // +0x28
    int           mF2c;                // +0x2c
    int           mKind30;             // +0x30
    __forceinline BehaviorMessageBase() : mKind30(0)
    {
        _InterlockedExchange(&mRef, 0);
    }
    virtual int v0();
    virtual int v1();
    virtual int v2();
};

struct BehaviorMessage : BehaviorMessageBase {
    int      mF34;                     // +0x34
    uint32_t mFlags;                   // +0x38
    int      mF3c;                     // +0x3c
    __forceinline BehaviorMessage() : mFlags(0) {}
};

// --------------------------------------------------- editor resource graph
struct RefHandle {                     // refcounted handle embedded at +0x08
    void* mpObject;                    // +0x04 (relative to the handle)
    virtual int AddRef();              // slot 0
    virtual int Release();             // slot 1
};

struct EditorResource {                // 0x14 bytes
    void*     mVt;                     // +0x00
    void*     mVt2;                    // +0x04
    RefHandle mHandle;                 // +0x08
    void*     mCallback;               // +0x10
};

// App state that receives the built message (0x007e4190).
struct cAppState {
    void AddMessage(void* args, BehaviorMessage* msg, char flag);
};

// ===========================================================================
// @ 0x00ad5590
// ===========================================================================
CmdAddActor::CmdAddActor()
{
    mpVt = vtbl_CmdAddActor;
    mSpec.Init(1);
    BuildArgumentSpec(&mSpec,
        "Adds a controllable actor",
        ":actorType", &g_pstrAvatar,
        ":positionType", &g_pstrEffect,
        "-highLOD^", 2, "makes the actor highLOD",
        "<actorName:cstring>", &mActorName, "actor identifier (name)",
        "<type:actorType>", &mActorType, "the type of actor to add",
        "-tribe^ <tribe:cstring>", 3, &mTribe, "tribe",
        "-archetype^ <archetype:cstring>", 1, &mArchetype, "archetype file",
        "-initialRelativePosition^ <posType:positionType> <posName:cstring> <position:vector3>",
        0, &mPosType, &mPosName, &mInitialPos, "initial position",
        0);
}

// ===========================================================================
// @ 0x00ad5670
// ===========================================================================
void CmdAddActor::Execute(void* pArgs)
{
    mActorName  = 0;
    mArchetype  = 0;
    mActorType  = 0;
    mSpec.ParseThrowing(pArgs, mParser);

    SimCommand* pCmd = (SimCommand*)EAAllocate(sizeof(SimCommand), "Simulator", 0, 0, 0, 0);
    if (pCmd) {
        new (pCmd) SimCommand();
        VCALL0(pCmd, 0x00);
    }

    pCmd->mNameHash  = (int)FNV1_String8(mActorName, 0x811c9dc5, 1);
    pCmd->mActorType = (int)mActorType;

    if (mSpec.mArchetypeUsed) {
        if (mArchetype)
            pCmd->mArchetypeHash = (int)FNV1_String8(mArchetype, 0x811c9dc5, 1);
    }
    if (mSpec.mTribeUsed) {
        if (mTribe)
            pCmd->mTribeHash = (int)FNV1_String8(mTribe, 0x811c9dc5, 1);
    }
    if (mSpec.mHighLODUsed)
        pCmd->mHighLOD = 1;
    if (mSpec.mPosUsed) {
        pCmd->mPosition    = mInitialPos;
        pCmd->mPosType     = (int)mPosType;
        pCmd->mPosNameHash = (int)FNV1_String8(mPosName, 0x811c9dc5, 1);
    }

    BehaviorMessage* pMsg = (BehaviorMessage*)EAAllocate(0x40, "Simulator", 0, 0, 0, 0);
    if (pMsg) {
        new (pMsg) BehaviorMessage();
        VCALL0(pMsg, 0x04);
    }
    pMsg->mKind30 = 0x4470a41;

    EditorResource* pRes = (EditorResource*)EAAllocate(0x14, "Simulator", 0, 0, 0, 0);
    if (pRes) {
        pRes = (EditorResource*)EditorResourceCtor(pRes);
        if (pRes) VCALL0(&pRes->mHandle, 0x00);
    }

    void* pOld = pRes->mHandle.mpObject;
    if (pCmd != pOld) {
        VCALL0(pCmd, 0x00);
        pRes->mHandle.mpObject = pCmd;
        if (pOld) VCALL0(pOld, 0x04);
    }
    pRes->mCallback = (void*)&FUN_00ad4b60;

    RefHandle* pHandle = &pRes->mHandle;
    if (pMsg->mFlags & 1) {
        void* pPrev = pMsg->mRefSlot;
        if (pPrev) VCALL0(pPrev, 0x04);
    }
    pMsg->mRefSlot = pHandle;
    if (pHandle) VCALL0(pHandle, 0x00);
    pMsg->mFlags |= 1;

    ((cAppState*)mpAppState)->AddMessage(pArgs, pMsg, 0);

    VCALL0(pHandle, 0x04);
    VCALL0(pMsg, 0x08);
    VCALL0(pCmd, 0x04);
}

// ===========================================================================
// @ 0x00ad5900
// ===========================================================================
CmdMoveActor::CmdMoveActor()
{
    mpVt = vtbl_CmdMoveActor;
    mSpec.Init(1);
    BuildArgumentSpec(&mSpec,
        "Creates a move actor command to be processed later",
        ":positionType", &g_pstrEffect,
        "<actorName:cstring>", &mActorName, "actor identifier (name)",
        "<position:vector3> [stopDistance:float]", &mPosition, &mStopDistance,
        "relative position and optional stop distance (if no options specified, then relative to the actor)",
        "-relative^ <posType:positionType> <posName:cstring>", 0, &mPosType, &mPosName,
        "relative to a position",
        "-face^ <facingType:positionType> <facingName:cstring> [facingOffset:vector3]", 1,
        &mFacingType, &mFacingName, &mFacingOffset, "face a position with an optional offset",
        "-noWait^", 2, "state does not wait for routing to finish",
        "-snap^", 3, "warps the actor into position",
        "-useFootprintRadius^", 4, "uses the foot radius of the actor as an offset multiplier",
        "-useTargetWidth^", 5, "uses the max width of the target object as an offset multiplier",
        "-useTargetHeight^", 6, "uses the height of the target object as an offset multiplier",
        0);
}

// ===========================================================================
// @ 0x00ad59e0
// ===========================================================================
ActorInfo::ActorInfo()
{
    mHash   = 0;
    mPos.x  = g_v4bc;
    mPos.y  = g_v4c0;
    mPos.z  = g_v4c4;
    mPos2.x = g_v4bc;
    mPos2.y = g_v4c0;
    mPos2.z = g_v4c4;
    mZero   = 0.0f;
    mMode   = 1;
    mP30    = 0;
    mP34    = 0;
    mP38    = 0;
    mB3c    = 0;
    mB3d    = 0;
    mKind   = 3;
    mBasis.x = g_v4bc;
    mBasis.y = g_v4c0;
    mBasis.z = g_v4c4;
}
