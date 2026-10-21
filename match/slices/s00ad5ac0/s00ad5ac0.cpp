// Slice s00ad5ac0: the SP::Simulator ArgScript "actor" command family of
// SPAppStateManager.obj -- the refcounted command/info/result object graph
// (Editor::cEditorResource + EA::RefCountVTemplate<int> multiple inheritance),
// four cCommandBase-derived command ctors + their Execute bodies, and the
// fixed_pool ctor of the resource object.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned char byte;

// ------------------------------------------------------------------ externs
void* EAAllocate(unsigned int size, const char* tag, int a, int b, int c, int d);  // 0x00f473a0
void  operator_delete(void* p);                                   // 0x00f47380
unsigned __cdecl FNV1_String8(const char* s, unsigned seed, int x);  // 0x00932e80
void __cdecl VecHelper(void* a, void* b, void* c);                // 0x011e0744 (eastl vector erase helper)
extern "C" long _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

// vtable symbols (only their addresses matter; relocations are masked)
extern char vtbl_ResBase[];          // 0x0145ad38
extern char vtbl_ResRefCount[];      // 0x0145ad28
extern char vtbl_ActorInfo[];        // 0x0145ab8c
extern char vtbl_RefCountV[];        // 0x0149bad8
extern char vtbl_VigInfo[];          // 0x0145ae28
extern char vtbl_FlagInfo[];         // 0x0145aed0
extern char vtbl_BehaviorMessage[];  // 0x013eb90c
extern char vtbl_BehaviorMessageB[]; // 0x013eb844
extern char vtbl_RefCountBase[];     // 0x013ec458
extern char vtbl_EditorResource[];   // 0x013eb938
extern char vtbl_CmdActor[];         // 0x0145ad10
extern char vtbl_CmdVig[];           // 0x0145ae10
extern char vtbl_CmdObjC[];          // 0x0145aeb8
extern char vtbl_CmdObjP[];          // 0x0145af64

// default basis triples
extern float g_v4bc;   // 0x0167a4bc
extern float g_v4c0;   // 0x0167a4c0
extern float g_v4c4;   // 0x0167a4c4

struct Vec3 { float x, y, z; };
struct ResKey { unsigned a, b, c; };
struct IntVec { void* begin; void* end; void* cap; };

struct ResObj { void* ScalarDtor(unsigned flags); };

// ------------------------------------------------------------------ base classes
struct cICommand {
    virtual void Execute(void* args);
    virtual void Description();
    virtual void OnRegister();
    virtual int  AddRef();
    virtual int  Release();
};

struct CmdBase : cICommand {
    void* mParser;    // +0x04
    int   mRefCount;  // +0x08
    CmdBase();        // 0x0083c800
};

struct ArgumentSpec {
    char pad[0xc8];
    void Init(bool respectHelp);                  // 0x0083a9f0
    void ParseThrowing(int argc, void* p);        // 0x0083b9d0
    int  ConstructSpec(const char* name, ...);    // 0x0083bcd0
};

struct cArguments;
struct RefObj;
struct cAppState {
    void AddMessage(cArguments* a, RefObj* b, char c);  // 0x007e4190
};

// 0x50-byte "actor info" object (ctor 0xad59e0)
struct ActorInfo {
    virtual int v0(); virtual int v1();
    int   mRef;       // +0x08
    int   mHash;      // +0x0c
    Vec3  mPos;       // +0x10
    Vec3  mPos2;      // +0x1c
    int   mF28;       // +0x28
    int   mFlags;     // +0x2c
    void* mP30;       // +0x30
    void* mP34;       // +0x34
    void* mP38;       // +0x38
    byte  mB3c;       // +0x3c
    byte  mB3d;       // +0x3d
    int   mMode;      // +0x40
};

// BehaviorMessage (0x40 bytes)
struct BehaviorMessage {
    virtual int v0(); virtual int v1(); virtual int v2();
    int   mField04;  // +0x04
    int   mRef;      // +0x08
    int   mTag;      // +0x0c
    int   mF14;      // +0x14
    int   mHandle;   // +0x1c
    int   mF20;      // +0x20
    int   mKind;     // +0x38
    byte  mB3c;      // +0x3c
    byte  mB3d;      // +0x3d
    byte  mB3e;      // +0x3e
    byte  mB3f;      // +0x3f
};

// EditorRes (0x14 bytes, ctor 0xad7c30)
struct EditorRes {
    virtual int v0(); virtual int v1();
    void* mSub4;      // +0x04
    void* mSub8;      // +0x08
    void* mPayload;   // +0x0c
    void* mCallback;  // +0x10
};

// 0x54-byte info object (ctor 0xad6320)
struct VigInfo {
    virtual int v0(); virtual int v1();
    int    mRef;      // +0x08
    int    mHash;     // +0x0c
    int    mHash2;    // +0x10
    ResKey mKey;      // +0x14
    Vec3   mPos;      // +0x20
    Vec3   mPos2;     // +0x2c
    int    mI38;      // +0x38
    int    mI3c;      // +0x3c
    int    mI40;      // +0x40
    int    mI44;      // +0x44
    byte   mB48;      // +0x48
    int    mMode;     // +0x4c
    int    mI50;      // +0x50
};

// 0x88-byte info object (ctor 0xad5ec0)
struct VigInfo0 {
    virtual int v0(); virtual int v1();
    int   mRef;      // +0x08
    int   mHash;     // +0x0c
    IntVec mVec10;   // +0x10
    int   mP1c;      // +0x1c
    int   mP20;      // +0x20
    int   mP24;      // +0x24
    int   mP28;      // +0x28
    int   mP2c;      // +0x2c
    int   mP30;      // +0x30
    int   mP34;      // +0x34
    int   mP38;      // +0x38
    char  mPad3c[0x34];  // +0x3c .. +0x70
    byte  mB70;      // +0x70
    int   mF74;      // +0x74
    int   mF78;      // +0x78
    int   mFourCC;   // +0x80
    byte  mB84;      // +0x84
};

// 0x14-byte info object (used by 0xad6740)
struct FlagInfo {
    virtual int v0(); virtual int v1();
    int   mRef;    // +0x08
    int   mHash;   // +0x0c
    byte  mB10;    // +0x10
};

// fixed_pool_base (0x14 bytes)
struct FixedPoolBase {
    void* mpHead;     // +0x00
    void* mPad04;     // +0x04
    void* mpBegin;    // +0x08
    void* mpEnd;      // +0x0c
    unsigned mNum;    // +0x10
    void init(void* pBuffer, unsigned n, unsigned size, unsigned align, unsigned off);  // 0x00921260
};

// forward decls of callees
extern "C" void FUN_00ad4550();
extern "C" void FUN_00ad3f70();
extern "C" void FUN_00ad2880();
extern "C" void FUN_00ad33d0();
EditorRes* __fastcall FUN_00ad7c30(EditorRes* p);        // 0x00ad7c30
VigInfo0*  __fastcall FUN_00ad5ec0(VigInfo0* p);         // 0x00ad5ec0
ActorInfo* __fastcall FUN_00ad59e0(ActorInfo* p);        // 0x00ad59e0
VigInfo*   __fastcall FUN_00ad6320(VigInfo* p);          // 0x00ad6320
char*      __fastcall ResCtor30(char* self);             // 0x00ad5e40
bool __cdecl SPKeyFromName(ResKey* out, const char* name, unsigned a, unsigned b); // 0x0068d5a0
extern "C" void __fastcall PoolFreeNodes(void* p);        // 0x00a222c0

// ===========================================================================
// command classes
// ===========================================================================
struct CmdActor : CmdBase {
    void* mpAppState;  // +0x0c
    ArgumentSpec mSpec;// +0x10
    char* mActorName;  // +0xd8
    int   mZero[3];    // +0xdc  ("animations:int[]" target, zeroed)
    float mF0e8;       // +0xe8
    int   mI0ec;       // +0xec
    char* mStrF0;      // +0xf0
    char* mStrF4;      // +0xf4
    char* mStrF8;      // +0xf8
    int   mFourCC;     // +0xfc  (also basis.x)
    int   mBasisY;     // +0x100
    int   mBasisZ;     // +0x104
    CmdActor();
    void Execute(void* args);
};

struct CmdVig : CmdBase {
    void* mpAppState;  // +0x0c
    ArgumentSpec mSpec;// +0x10
    char* mActorName;  // +0xd8
    char* mVigName;    // +0xdc
    Vec3  mPos;        // +0xe0
    char* mStrEc;      // +0xec  "-relative" posName
    char* mStrF0;      // +0xf0  "-relative" posType
    char* mStrF4;      // +0xf4  "-face" facingName
    char* mStrF8;      // +0xf8  "-face" facingType
    char* mStrFC;      // +0xfc  "-face" facingOffset
    CmdVig();
    void Execute(void* args);
};

struct CmdVig2 : CmdBase {
    void* mpAppState;  // +0x0c
    ArgumentSpec mSpec;// +0x10
    char* mActorName;  // +0xd8
    IntVec mVec;       // +0xdc
    byte  mBf0;        // +0xf0
    char* mStrf4;      // +0xf4
    char* mStrf8;      // +0xf8
    char* mStrfC;      // +0xfc
    void Execute(void* args);
};

struct CmdObjC : CmdBase {
    void* mpAppState;  // +0x0c
    ArgumentSpec mSpec;// +0x10
    char* mObject;     // +0xd8
    byte  mFlag;       // +0xdc
    CmdObjC();
};

struct CmdObjP : CmdBase {
    void* mpAppState;  // +0x0c
    ArgumentSpec mSpec;// +0x10
    char* mObject;     // +0xd8
    byte  mFlag;       // +0xdc
    CmdObjP();
    void Execute(void* args);
};

// ===========================================================================
// @ 0x00ad5ac0
// ===========================================================================
void CmdActor::Execute(void* args) {
    char* self = (char*)this;
    *(char**)(self + 0xd8) = 0;
    *(int*)(self + 0xdc) = g_v4bc;
    *(int*)(self + 0xe0) = g_v4c0;
    *(int*)(self + 0xe4) = g_v4c4;
    *(float*)(self + 0xe8) = 0.0f;
    *(int*)(self + 0xf0) = 0;
    *(int*)(self + 0xf4) = 0;
    *(int*)(self + 0xf8) = 0;
    *(int*)(self + 0xec) = 1;
    *(int*)(self + 0xfc) = g_v4bc;
    *(int*)(self + 0x100) = g_v4c0;
    *(int*)(self + 0x104) = g_v4c4;
    mSpec.ParseThrowing(*(int*)&args, mParser);

    ActorInfo* info;
    ActorInfo* tmp = (ActorInfo*)EAAllocate(0x50, "Simulator", 0, 0, 0, 0);
    if (tmp == 0) {
        info = 0;
    } else {
        info = FUN_00ad59e0(tmp);
        if (info) info->v0();
    }
    unsigned f = *(unsigned*)(self + 0x80);
    info->mHash = FNV1_String8(*(const char**)(self + 0xd8), 0x811c9dc5, 1);
    info->mPos.x = *(float*)(self + 0xdc);
    info->mPos.y = *(float*)(self + 0xe0);
    info->mPos.z = *(float*)(self + 0xe4);
    info->mF28 = *(int*)(self + 0xe8);
    if (f & 1) {
        info->mFlags = *(int*)(self + 0xec);
        info->mP30 = (void*)FNV1_String8(*(const char**)(self + 0xf0), 0x811c9dc5, 1);
    }
    if ((f >> 1) & 1) {
        info->mP34 = (void*)FNV1_String8(*(const char**)(self + 0xf8), 0x811c9dc5, 1);
        info->mP38 = 0;
        info->mP30 = (void*)FNV1_String8(*(const char**)(self + 0xf4), 0x811c9dc5, 1);
    }
    info->mB3c = (byte)((f >> 2) & 1);
    info->mB3d = (byte)((f >> 3) & 1);
    {
        int mode;
        if (f & 0x10) mode = 0;
        else if (f & 0x20) mode = 1;
        else mode = (((byte)~(byte)(f >> 6)) & 1) | 2;
        info->mMode = mode;
    }

    BehaviorMessage* msg;
    BehaviorMessage* mt = (BehaviorMessage*)EAAllocate(0x40, "Simulator", 0, 0, 0, 0);
    if (mt == 0) {
        msg = 0;
    } else {
        mt->mTag = 0;
        *(void**)mt = (void*)&vtbl_BehaviorMessage;
        _InterlockedExchange((long volatile*)((char*)mt + 4), 0);
        *(void**)mt = (void*)&vtbl_BehaviorMessageB;
        msg = mt;
        msg->mKind = 0;
        msg->v1();
    }
    msg->mTag = 0x4470a41;
    EditorRes* res = 0;
    EditorRes* rt = (EditorRes*)EAAllocate(0x14, "Simulator", 0, 0, 0, 0);
    if (rt != 0) {
        res = FUN_00ad7c30(rt);
        if (res) res->v0();
    }
    void* old = res->mPayload;
    if (info != old) {
        info->v0();
        res->mPayload = info;
        if (old) (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    res->mCallback = (void*)&FUN_00ad33d0;
    void* sub = (char*)res + 8;
    if ((*(byte*)((char*)msg + 0x38) & 1) && msg->mRef) {
        (*(void(__thiscall**)(void*))((char*)*(void**)msg->mRef + 4))((void*)msg->mRef);
    }
    *(int*)((char*)msg + 8) = (int)sub;
    if (sub) (*(void(__thiscall**)(void*))(*(void**)sub))(sub);
    *(int*)((char*)msg + 0x38) |= 1;
    ((cAppState*)mpAppState)->AddMessage(0, 0, 0);
}

// ===========================================================================
// @ 0x00ad5d90
// ===========================================================================
CmdActor::CmdActor() {
    *(void**)this = (void*)&vtbl_CmdActor;
    mSpec.Init(true);
    mSpec.ConstructSpec(
        "Adds a controllable actor", ":positionType", (void*)0x15662e0,
        "<actor:cstring>", &mActorName, "actor name",
        "<animations:int[]>", (mZero[0] = 0, mZero[1] = 0, mZero[2] = 0, mZero), "animations guids to play",
        "-noWait^", 0, "wait for animation to finish before moving on",
        "-target^ <targetType:positionType> <target:cstring> ", 1, &mStrF4, &mStrF8,
        "target context for animation",
        "-processAnimEventsUsingTarget^", 2, "uses the animation target for processing animation events",
        "-fourCC^ <fourcc:cstring>", 3, &mFourCC, "sets the fourCC level on the animation", 0);
}

// ===========================================================================
// @ 0x00ad5e40
// ===========================================================================
char* __fastcall ResCtor30(char* self) {
    FixedPoolBase tmp;
    FixedPoolBase* poolA = (FixedPoolBase*)(self + 8);
    tmp.mpHead = 0;
    tmp.init(self + 0x1c, 0x18, 0xc, 4, 0);
    void* head = tmp.mpHead;
    *(int*)self = 0;
    *(int*)(self + 4) = 0;
    poolA->mpHead = 0;
    poolA->init(head, 0x18, 0xc, 4, 0);
    poolA->mpBegin = head;
    poolA->mpEnd = (char*)head + 0x18;
    poolA->mNum = 0x0c;
    *(void**)self = self;
    *(void**)(self + 4) = self;
    return self;
}

// ===========================================================================
// @ 0x00ad5ec0
// ===========================================================================
VigInfo0* __fastcall FUN_00ad5ec0(VigInfo0* p) {
    char* self = (char*)p;
    *(void* volatile*)(self + 4) = (void*)&vtbl_RefCountBase;
    *(int*)(self + 8) = 0;
    *(void**)self = (void*)&vtbl_ResBase;
    *(void**)(self + 4) = (void*)&vtbl_ResRefCount;
    *(int*)(self + 0xc) = 0;
    *(void**)(self + 0x10) = self + 0x28;
    *(void**)(self + 0x14) = self + 0x28;
    *(int*)(self + 0x24) = 0;
    *(void**)(self + 0x18) = (char*)*(void**)(self + 0x10) + 8;
    ResCtor30((char*)*(void**)(self + 0x18));
    *(int*)(self + 0x78) = 0;
    *(int*)(self + 0x7c) = 3;
    return p;
}

// ===========================================================================
// @ 0x00ad5f40
// ===========================================================================
void* ResObj::ScalarDtor(unsigned flags) {
    char* self = (char*)this;
    *(void**)self = (void*)&vtbl_ResBase;
    *(void**)(self + 4) = (void*)&vtbl_ResRefCount;
    PoolFreeNodes(self + 0x30);
    void* q = *(void**)(self + 0x10);
    if (q != 0) {
        if (*(int*)((char*)q - 4) != 0) operator_delete(q);
    }
    *(void**)(self + 4) = (void*)&vtbl_RefCountBase;
    *(void**)self = (void*)&vtbl_EditorResource;
    if (flags & 1) operator_delete(self);
    return self;
}

// ===========================================================================
// @ 0x00ad5fa0
// ===========================================================================
void CmdVig2::Execute(void* args) {
    char* self = (char*)this;
    *(char**)(self + 0xd8) = 0;
    VecHelper(mVec.begin, mVec.end, 0);
    mVec.end = (char*)mVec.end - ((int)mVec.end - (int)mVec.begin);
    mBf0 = 0;
    *(int*)(self + 0xf4) = 0;
    *(int*)(self + 0xf8) = 0;
    mSpec.ParseThrowing(*(int*)&args, mParser);
    if (*(unsigned*)(self + 0x80) & 1) mBf0 = 1;

    VigInfo0* info;
    VigInfo0* tmp = (VigInfo0*)EAAllocate(0x88, "Simulator", 0, 0, 0, 0);
    if (tmp == 0) {
        info = 0;
    } else {
        info = FUN_00ad5ec0(tmp);
        if (info) info->v0();
    }
    unsigned f = *(unsigned*)(self + 0x80);
    info->mHash = FNV1_String8(*(const char**)(self + 0xd8), 0x811c9dc5, 1);
    info->mVec10 = mVec;
    info->mB70 = mBf0;
    info->mB84 = 0;
    VecHelper(mVec.begin, mVec.end, 0);
    mVec.end = (char*)mVec.end - ((int)mVec.end - (int)mVec.begin);
    if ((f >> 3) & 1) {
        unsigned char* q = *(unsigned char**)(self + 0xfc);
        unsigned v = (unsigned)q[3] << 8 | q[2];
        v = (v << 8) | q[1];
        v = (v << 8) | q[0];
        info->mFourCC = v;
    } else {
        info->mFourCC = 0;
    }
    if ((f >> 1) & 1) {
        info->mF74 = *(int*)(self + 0xf4);
        info->mF78 = (int)FNV1_String8(*(const char**)(self + 0xf8), 0x811c9dc5, 1);
    }
    if (((f >> 2) & 1) && info->mF78) info->mB84 = 1;

    BehaviorMessage* msg;
    BehaviorMessage* mt = (BehaviorMessage*)EAAllocate(0x40, "Simulator", 0, 0, 0, 0);
    if (mt == 0) {
        msg = 0;
    } else {
        mt->mTag = 0;
        *(void**)mt = (void*)&vtbl_BehaviorMessage;
        _InterlockedExchange((long volatile*)((char*)mt + 4), 0);
        *(void**)mt = (void*)&vtbl_BehaviorMessageB;
        msg = mt;
        msg->mKind = 0;
        msg->v1();
    }
    msg->mTag = 0x4470a41;
    EditorRes* res = 0;
    EditorRes* rt = (EditorRes*)EAAllocate(0x14, "Simulator", 0, 0, 0, 0);
    if (rt != 0) {
        res = FUN_00ad7c30(rt);
        if (res) res->v0();
    }
    void* old = res->mPayload;
    if (info != old) {
        info->v0();
        res->mPayload = info;
        if (old) (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    res->mCallback = (void*)&FUN_00ad4550;
    void* sub = (char*)res + 8;
    if ((*(byte*)((char*)msg + 0x38) & 1) && msg->mRef) {
        (*(void(__thiscall**)(void*))((char*)*(void**)msg->mRef + 4))((void*)msg->mRef);
    }
    *(int*)((char*)msg + 8) = (int)sub;
    if (sub) (*(void(__thiscall**)(void*))(*(void**)sub))(sub);
    *(int*)((char*)msg + 0x38) |= 1;
    ((cAppState*)mpAppState)->AddMessage(0, 0, 0);
}

// ===========================================================================
// @ 0x00ad6240
// ===========================================================================
CmdVig::CmdVig() {
    *(void**)this = (void*)&vtbl_CmdVig;
    mSpec.Init(true);
    mSpec.ConstructSpec(
        "Creates a vignette command to be processed later", ":positionType", (void*)0x15662e0,
        "<actor:cstring>", &mActorName, "actor name",
        "<vignetteName:cstring>", &mVigName, "vignette identifier (name)",
        "<position:vector3>", &mPos,
        "relative position (if no options specified, then relative to the actor)",
        "-relative^ <posType:positionType> <posName:cstring>", 0, &mStrEc, &mStrF0,
        "relative to a position",
        "-face^ <facingType:positionType> <facingName:cstring> [facingOffset:v", 1, &mStrF4, &mStrF8, &mStrFC,
        "face a position with an optional offset",
        "-noWait^", 2, "state does not wait for routing to finish",
        "-useFootprintRadius^", 4, "uses the foot radius of the actor as an offset multiplier",
        "-useTargetWidth^", 5, "uses the max width of the target object as an offset multiplier",
        "-useTargetHeight^", 6, "uses the height of the target object as an offset multiplier", 0);
}

// ===========================================================================
// @ 0x00ad6320
// ===========================================================================
VigInfo* __fastcall FUN_00ad6320(VigInfo* p) {
    char* self = (char*)p;
    *(void* volatile*)(self + 4) = (void*)&vtbl_RefCountBase;
    *(int* volatile*)(self + 8) = 0;
    *(void**)self = (void*)&vtbl_VigInfo;
    *(void**)(self + 4) = (void*)&vtbl_RefCountV;
    *(int*)(self + 0x14) = 0;
    *(int*)(self + 0x18) = 0;
    *(int*)(self + 0x1c) = 0;
    *(float*)(self + 0x20) = g_v4bc;
    *(float*)(self + 0x24) = g_v4c0;
    *(float*)(self + 0x28) = g_v4c4;
    *(float*)(self + 0x2c) = g_v4bc;
    *(float*)(self + 0x30) = g_v4c0;
    *(float*)(self + 0x34) = g_v4c4;
    *(int*)(self + 0x38) = 1;
    *(int*)(self + 0x3c) = 0;
    *(int*)(self + 0x40) = 0;
    *(int*)(self + 0x44) = 0;
    *(byte*)(self + 0x48) = 0;
    *(int*)(self + 0x4c) = 3;
    *(int*)(self + 0x50) = -1;
    return p;
}

// ===========================================================================
// @ 0x00ad63e0
// ===========================================================================
void CmdVig::Execute(void* args) {
    char* self = (char*)this;
    *(char**)(self + 0xd8) = 0;
    *(char**)(self + 0xdc) = 0;
    *(int*)(self + 0xe0) = g_v4bc;
    *(int*)(self + 0xe4) = g_v4c0;
    *(int*)(self + 0xe8) = g_v4c4;
    *(int*)(self + 0xf0) = 0;
    *(int*)(self + 0xf4) = 0;
    *(int*)(self + 0xf8) = 0;
    *(int*)(self + 0xec) = 1;
    *(int*)(self + 0xfc) = g_v4bc;
    *(int*)(self + 0x100) = g_v4c0;
    *(int*)(self + 0x104) = g_v4c4;
    mSpec.ParseThrowing(*(int*)&args, mParser);

    VigInfo* info;
    VigInfo* tmp = (VigInfo*)EAAllocate(0x54, "Simulator", 0, 0, 0, 0);
    if (tmp == 0) {
        info = 0;
    } else {
        info = FUN_00ad6320(tmp);
        if (info) info->v0();
    }
    unsigned f = *(unsigned*)(self + 0x80);
    info->mHash = (int)FNV1_String8(*(const char**)(self + 0xd8), 0x811c9dc5, 1);
    info->mHash2 = (int)FNV1_String8(*(const char**)(self + 0xdc), 0x811c9dc5, 1);
    SPKeyFromName(&info->mKey, *(const char**)(self + 0xdc), 0, 0);
    info->mPos.x = *(float*)(self + 0xe0);
    info->mPos.y = *(float*)(self + 0xe4);
    info->mPos.z = *(float*)(self + 0xe8);
    if (f & 1) {
        info->mI38 = *(int*)(self + 0xec);
        info->mI3c = (int)FNV1_String8(*(const char**)(self + 0xf0), 0x811c9dc5, 1);
    }
    if ((f >> 1) & 1) {
        info->mI40 = *(int*)(self + 0xf4);
        info->mI44 = (int)FNV1_String8(*(const char**)(self + 0xf8), 0x811c9dc5, 1);
        info->mPos2.x = *(float*)(self + 0xfc);
        info->mPos2.y = *(float*)(self + 0x100);
        info->mPos2.z = *(float*)(self + 0x104);
    }
    info->mB48 = (byte)((f >> 2) & 1);
    {
        int mode;
        if (f & 0x10) mode = 0;
        else if (f & 0x20) mode = 1;
        else mode = (((byte)~(byte)(f >> 6)) & 1) | 2;
        info->mMode = mode;
    }

    BehaviorMessage* msg;
    BehaviorMessage* mt = (BehaviorMessage*)EAAllocate(0x40, "Simulator", 0, 0, 0, 0);
    if (mt == 0) {
        msg = 0;
    } else {
        mt->mTag = 0;
        *(void**)mt = (void*)&vtbl_BehaviorMessage;
        _InterlockedExchange((long volatile*)((char*)mt + 4), 0);
        *(void**)mt = (void*)&vtbl_BehaviorMessageB;
        msg = mt;
        msg->mKind = 0;
        msg->v1();
    }
    msg->mTag = 0x4470a41;
    EditorRes* res = 0;
    EditorRes* rt = (EditorRes*)EAAllocate(0x14, "Simulator", 0, 0, 0, 0);
    if (rt != 0) {
        res = FUN_00ad7c30(rt);
        if (res) res->v0();
    }
    void* old = res->mPayload;
    if (info != old) {
        info->v0();
        res->mPayload = info;
        if (old) (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    res->mCallback = (void*)&FUN_00ad3f70;
    void* sub = (char*)res + 8;
    if ((*(byte*)((char*)msg + 0x38) & 1) && msg->mRef) {
        (*(void(__thiscall**)(void*))((char*)*(void**)msg->mRef + 4))((void*)msg->mRef);
    }
    *(int*)((char*)msg + 8) = (int)sub;
    if (sub) (*(void(__thiscall**)(void*))(*(void**)sub))(sub);
    *(int*)((char*)msg + 0x38) |= 1;
    ((cAppState*)mpAppState)->AddMessage(0, 0, 0);
}

// ===========================================================================
// @ 0x00ad66c0
// ===========================================================================
CmdObjC::CmdObjC() {
    *(void**)this = (void*)&vtbl_CmdObjC;
    mSpec.Init(true);
    mSpec.ConstructSpec(
        "Enables/disables collisions for object",
        "<object:cstring>", &mObject, "object name",
        "<collisionsEnabled:bool>", &mFlag, "enables/disables collisions", 0);
}

// ===========================================================================
// @ 0x00ad6740
// ===========================================================================
void CmdObjP::Execute(void* args) {
    char* self = (char*)this;
    *(char**)(self + 0xd8) = 0;
    mFlag = 1;
    mSpec.ParseThrowing(*(int*)&args, mParser);
    char* info = (char*)EAAllocate(0x14, "Simulator", 0, 0, 0, 0);
    if (info == 0) {
        info = 0;
    } else {
        *(void**)(info + 4) = (void*)&vtbl_RefCountBase;
        *(int*)(info + 8) = 0;
        *(void**)info = (void*)&vtbl_FlagInfo;
        *(void**)(info + 4) = (void*)&vtbl_RefCountV;
        *(int*)(info + 0xc) = 0;
        *(byte*)(info + 0x10) = 1;
        ((FlagInfo*)info)->v0();
    }
    info = info;
    *(int*)(info + 0xc) = (int)FNV1_String8(*(const char**)(self + 0xd8), 0x811c9dc5, 1);
    *(byte*)(info + 0x10) = mFlag;

    BehaviorMessage* msg;
    BehaviorMessage* mt = (BehaviorMessage*)EAAllocate(0x40, "Simulator", 0, 0, 0, 0);
    if (mt == 0) {
        msg = 0;
    } else {
        mt->mTag = 0;
        *(void**)mt = (void*)&vtbl_BehaviorMessage;
        _InterlockedExchange((long volatile*)((char*)mt + 4), 0);
        *(void**)mt = (void*)&vtbl_BehaviorMessageB;
        msg = mt;
        msg->mKind = 0;
        msg->v1();
    }
    msg->mTag = 0x4470a41;
    EditorRes* res = 0;
    EditorRes* rt = (EditorRes*)EAAllocate(0x14, "Simulator", 0, 0, 0, 0);
    if (rt != 0) {
        res = FUN_00ad7c30(rt);
        if (res) res->v0();
    }
    void* old = res->mPayload;
    if (info != old) {
        (*(void(__thiscall**)(void*))(*(void**)info))(info);
        res->mPayload = info;
        if (old) (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    res->mCallback = (void*)&FUN_00ad2880;
    void* sub = (char*)res + 8;
    if ((*(byte*)((char*)msg + 0x38) & 1) && msg->mRef) {
        (*(void(__thiscall**)(void*))((char*)*(void**)msg->mRef + 4))((void*)msg->mRef);
    }
    *(int*)((char*)msg + 8) = (int)sub;
    if (sub) (*(void(__thiscall**)(void*))(*(void**)sub))(sub);
    *(int*)((char*)msg + 0x38) |= 1;
    ((cAppState*)mpAppState)->AddMessage(0, 0, 0);
}

// ===========================================================================
// @ 0x00ad68e0
// ===========================================================================
CmdObjP::CmdObjP() {
    *(void**)this = (void*)&vtbl_CmdObjP;
    mSpec.Init(true);
    mSpec.ConstructSpec(
        "Enables/disables plumping for object",
        "<object:cstring>", &mObject,
        "planetary artifact(rare) or ufo name",
        "<allowPlumping:bool>", &mFlag,
        "enables/disables plumping", 0);
}
