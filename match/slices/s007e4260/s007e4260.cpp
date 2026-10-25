// Slice s007e4260 (w2g5 slice 29).  cAppStateManager command Execute cluster.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

void* operator new(size_t size, const char* name, int a, int b, const char* file, int line);
void* operator new[](size_t size);
void  operator delete(void* p);
void  operator delete[](void* p);
void  __cdecl EFree(void* p);
void* __cdecl EAlloc6(int size, const char* name, int a, int b, const char* file, int line);
extern "C" long _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(_InterlockedExchange)
__declspec(dllimport) int __cdecl isalpha(int);

namespace EA { namespace ArgScript {
class cArguments {
public:
    const char** MainArguments(int n);
    const char** MainArguments(int* pCount, int min, int max);
    const char** OptionArguments(const char* name, int n);
    const char** OptionArgumentsPtr(const void* name, int n);
    bool HasFlag(const char* name);
};
class cICommand { public:
    virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3();
    virtual void i4(); virtual void i5();
};
class cCommandBase : public cICommand { public:
    virtual void AddCommand(void* key, void* cmd);
    void* mParser;
    int   mRefCount;
    virtual ~cCommandBase();
};
struct OptionParser {
    virtual void o0(); virtual void o1(); virtual void o2();
    ~OptionParser();
};
}}

struct cStrW {
    char* mpBegin; char* mpEnd; char* mpCapacity; void* mAllocator;
    ~cStrW() { if ((((int)(mpEnd - mpBegin) & ~1) > 2) && mpBegin != 0) operator delete(mpBegin); }
};

// eastl::string (retail 16-byte layout, no small-string buffer).
struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
};
// eastl::vector<eastl::string, sp_vector_allocator>: 16-byte elements.
struct EStringVec {
    EString* mpBegin; EString* mpEnd; EString* mpCap;
    EStringVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    void FUN_006a4950(EString* begin, EString* end);   // destroys the element range
    ~EStringVec() {
        FUN_006a4950(mpBegin, mpEnd);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0) operator delete(mpBegin);
    }
    int Size() const { return (int)(mpEnd - mpBegin); }
    EString& operator[](int i) const { return mpBegin[i]; }
};
void SPKeyFromName(void* out, const void* name, int a, int b);       // 0x0068d840
namespace EA { void ConvertToString16Impl(void* out, const char* s, unsigned len); }  // 0x0093c5a0
void cErrorCtor(int* out, const char* text);                          // 0x0052df30  (does not return)
void PushStr_553cc0(void* self, void* node);                          // 0x00553cc0  (__thiscall)

struct cArgumentSpec {                                     // 0xc8 bytes
    char     pad00[0x70];
    unsigned mFlags;                                       // +0x70 (option presence bits)
    char     pad74[0xc8 - 0x74];
    cArgumentSpec(bool hasArgs);                           // 0x0083a9f0
    void Parse(EA::ArgScript::cArguments* args, void* parser);  // 0x0083b9d0
};
void cArgumentSpecConstruct(cArgumentSpec* spec, const char* desc, const char* usage, void* str,
                            const char* d1, const char* f1, int t1,
                            const char* d2, const char* f2, int t2,
                            const char* d3, const char* f3, int t3,
                            const char* d4, const char* f4, int t4,
                            const char* d5, int t5);        // 0x0083bcd0

struct AMVecU32 {
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap;
    AMVecU32() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~AMVecU32() { if (mpBegin && *(int*)((char*)mpBegin - 4) != 0) operator delete(mpBegin); }
    void DoInsertValue(unsigned* pos, const unsigned& v);   // 0x004558a0
    void push_back(const unsigned& v) {
        if (mpEnd >= mpCap) { DoInsertValue(mpEnd, v); return; }
        *mpEnd++ = v;
    }
};
struct cStateHash {                       // eastl hashtable owner
    char      pad00[0xfc];
    void**    mpBuckets;                  // +0xfc
    int       mnBucketCount;              // +0x100
    void EnumStrings(void* ctx, AMVecU32* out);
};

// ---------------------------------------------------- cAppStateManager layout
// Primary state-manager interface.  Only the slots used by the cheat command
// are named; the rest keep their positions.
struct AppStateVt0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual bool SetState(int id);                  // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34();
    virtual int  StateIDFromName(const char* name); // +0x38
    virtual const char* CurrentStateName();         // +0x3c
};
// Secondary handler/refcount sub-object at cAppStateManager + 4.
struct AppStateVt1 {
    virtual void w00();                             // +0x00
    virtual void Notify(unsigned msg, void* arg);   // +0x04
};
// Object reached through cAppStateManager + 0x154 (and its siblings).  The
// destructor releases through slots +4/+0x10; the cheat calls slot +0x24.
struct Vt24 {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20();
    virtual void Call24();                          // +0x24
};
// Argument parser interface: slot +0x9c turns a name into a state id.
struct cArgParserVt {
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20(); virtual void p24(); virtual void p28(); virtual void p2c();
    virtual void p30(); virtual void p34(); virtual void p38(); virtual void p3c();
    virtual void p40(); virtual void p44(); virtual void p48(); virtual void p4c();
    virtual void p50(); virtual void p54(); virtual void p58(); virtual void p5c();
    virtual void p60(); virtual void p64(); virtual void p68(); virtual void p6c();
    virtual void p70(); virtual void p74(); virtual void p78(); virtual void p7c();
    virtual void p80(); virtual void p84(); virtual void p88(); virtual void p8c();
    virtual void p90(); virtual void p94(); virtual void p98();
    virtual int  ParseStateName(const char* name);  // +0x9c
};

struct cActions { char o[0x50]; void FUN_007e2680(); };            // +0x2c
struct cActionsVec { char o[0x14]; void FUN_007e3250(); };         // +0xa4
struct Obj118 { char o[0x14]; void FUN_004b5440(); };               // +0x118
struct Obj12c { char o[0x14]; void FUN_004b5440(); };               // +0x12c

// eastl hashtable common header: buckets at +4, element count at +8, and the
// occupied-bucket count at +0xc (zeroed by the destructor).
struct HTableActions {                                              // +0xb8
    char  pad0[4]; void* mpBuckets; int mnCount; int mnSize; char pad10[0x10];
    void FUN_00693230(void* buckets, int count);
};
struct HTableTrans {                                                // +0xd8
    char  pad0[4]; void* mpBuckets; int mnCount; int mnSize; char pad10[0x10];
    void FUN_0093dc70(void* buckets, int count);
};
struct HTableNames {                                                // +0xf8
    char  pad0[4]; void* mpBuckets; int mnCount; int mnSize; char pad10[0x10];
    void FUN_006a85b0(void* buckets, int count);
};
struct HandlerGroup {                                               // +0x140
    void* mpHandler; void* mpA; void* mpB; void* mpC; void* mpD;
};
void __cdecl RemoveHandler(void* h, void* a, void* b, void* c, void* d);  // 0x00571db0

namespace SP {
struct cAppStateManager {
    void*         mpVtbl0;          // +0x00
    AppStateVt1*  mpVtbl1;          // +0x04 (secondary sub-object vtable)
    void*         mpVtbl2;          // +0x08
    char          pad0c[0x0c];
    EString       mCurrentName;     // +0x18
    char          pad28[4];
    cActions      mCurrentActions;  // +0x2c
    char          pad7c[0x14];
    void*         mpPrevStates;     // +0x90
    char          pad94[0x10];
    cActionsVec   mActionStack;     // +0xa4
    HTableActions mStateActions;    // +0xb8
    HTableTrans   mTransitionActions; // +0xd8
    HTableNames   mStateNames;      // +0xf8
    Obj118        mObj118;          // +0x118
    Obj12c        mObj12c;          // +0x12c
    HandlerGroup  mHandlers;        // +0x140
    Vt24*         mState154;        // +0x154
    Vt24*         mState158;        // +0x158
    Vt24*         mState15c;        // +0x15c
    Vt24*         mState160;        // +0x160
    EString       mNames164;        // +0x164

    // Vtable dispatch helpers (this is passed unchanged; the vptr at +0).
    bool SetState(int id) { return ((AppStateVt0*)this)->SetState(id); }
    int  StateIDFromName(const char* name) { return ((AppStateVt0*)this)->StateIDFromName(name); }
    const char* CurrentStateName() { return ((AppStateVt0*)this)->CurrentStateName(); }
    void Notify(unsigned msg) { mpVtbl1->Notify(msg, 0); }
    void EnumStrings(EStringVec* names, AMVecU32* ids) {
        ((cStateHash*)this)->EnumStrings(names, ids);
    }

    ~cAppStateManager();            // 0x007e4bc0
};
struct cAppStateCheat;
}

// Thrown by cAppStateCheat::Execute for an unknown state name.
struct cError { EString mMessage; cError(const char* fmt, ...); cError(const cError&); };
namespace EA { namespace ArgScript {
void __cdecl Output(int* parser, const char* fmt, ...);          // 0x00841000
}}

// The parser sub-object sits right behind the command vtable
// (cAppStateCmd -> cCommandBase -> cICommand); the property getters live at
// fixed vtable slots, so VSLOT loads the slot and calls through it.
#define VSLOT(type, p, off)  (*(type*)((char*)*(void***)(p) + (off)))
typedef int   (__thiscall *PFnPropInt)(void*, const char*);
typedef bool  (__thiscall *PFnPropBool)(void*, const char*);
typedef float (__thiscall *PFnPropFloat)(void*, const char*);
void SetMessageString8(void* msg, int a, const char* s);   // 0x00618bd0

struct BehaviorMessageBase;
struct cActionMessage;
struct AMVecFull {                        // 0x007e3d90 push_back
    char o[0x14];
    void push_back(const cActionMessage* msg);
};
struct cAppState {
    void* AddAction(EA::ArgScript::cArguments* args, void* msg);   // +0x00  0x007e40d0
    char      pad04[0x2c];
    AMVecFull vec2c;        // +0x2c
    AMVecFull vec40;        // +0x40
    char      pad54[0x80 - 0x54];
    char      field80;      // +0x80
};

// UI::BehaviorMessage (0x40 bytes; two polymorphic levels).  The id field and
// the atomic refcount live in the base so the base constructor emits the
// [0x30]=0 / vtable / xchg refcount sequence the original has.
struct BehaviorMessageBase {
    virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3();
    int  mRefCount;         // +0x04
    int  field08;           // +0x08
    int  field0c;           // +0x0c
    int  field10;           // +0x10 (int / bool / float depending on the command)
    int  pad14;             // +0x14
    int  field18;           // +0x18
    int  pad1c;             // +0x1c
    int  field20;           // +0x20
    int  pad24;             // +0x24
    int  pad28;             // +0x28
    int  pad2c;             // +0x2c
    int  field30;           // +0x30 message id
    int  field34;           // +0x34
    BehaviorMessageBase() : field30(0) { _InterlockedExchange((volatile long*)&mRefCount, 0); }
};
struct BehaviorMessage : BehaviorMessageBase {
    virtual void b4();      // gives the derived level its own vtable
    int  field38;           // +0x38
    char pad3c[4];          // +0x3c padding; keeps the object at 0x40 bytes
    BehaviorMessage() : field38(0) {}
};


static __forceinline BehaviorMessage* NewBehaviorMessage(int msgid) {
    BehaviorMessage* m = new ("App", 0, 0, 0, 0) BehaviorMessage();
    m->field30 = msgid;
    return m;
}

struct BehaviorMessageBase;
struct cActionMessage { void* mpMessage; int mFlag; };

namespace SP {
struct cAppStateCheat : EA::ArgScript::cCommandBase {
    int               mPad0c;      // +0x0c
    cAppStateManager* mOwner;      // +0x10
    cArgumentSpec     mArgSpec;    // +0x14
    char*             mStateName;  // +0xdc parsed state name (owned by the spec)
    cAppStateCheat(cAppStateManager* owner);
    void Execute(EA::ArgScript::cArguments* args);
};
}
struct cAppStateCmd : EA::ArgScript::cCommandBase {
    cAppState* mpState;   // +0xc
};

// The three property commands are __thiscall members: `ecx` is the command and
// the argument list arrives as the sole stack parameter.  Each gets its own
// class so the three definitions land in separate COMDATs.
struct cBoolPropCommand : cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cGotoStateCommand : cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cCheatCommand     : cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cLightingCommand  : cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cCameraCommand    : cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cKillEffectCommand: cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cModeCommand      : cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cEffectCommand    : cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cIntPropCommand  : cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cFloatPropCommand: cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cMessageCommand     : cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };
struct cLoadResourceCommand: cAppStateCmd { void Execute(EA::ArgScript::cArguments* args); };

// @ 0x007e4260  cGotoStateCommand::Execute
void cGotoStateCommand::Execute(EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xe11330);
    SetMessageString8(m, 0, av[0]);
    mpState->AddAction(args, m);
}

// @ 0x007e46f0  cCheatCommand::Execute
void cCheatCommand::Execute(EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xcef220e1);
    SetMessageString8(m, 0, av[0]);
    mpState->AddAction(args, m);
}

// @ 0x007e48f0  cLightingCommand::Execute
void cLightingCommand::Execute(EA::ArgScript::cArguments* args) {
    BehaviorMessage* m = NewBehaviorMessage(0x6f188ef2);
    const char** av = args->MainArguments(1);
    SetMessageString8(m, 0, av[0]);
    mpState->AddAction(args, m);
}

// @ 0x007e4970  cCameraCommand::Execute
void cCameraCommand::Execute(EA::ArgScript::cArguments* args) {
    BehaviorMessage* m = NewBehaviorMessage(0x6f188ef8);
    const char** av = args->MainArguments(1);
    SetMessageString8(m, 0, av[0]);
    mpState->AddAction(args, m);
}

// @ 0x007e4550  cKillEffectCommand::Execute
void cKillEffectCommand::Execute(EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xcef220e0);
    SetMessageString8(m, 0, av[0]);
    m->field34 = args->HasFlag("softStop") ? 1 : 0;
    mpState->AddAction(args, m);
}

// @ 0x007e45e0  cModeCommand::Execute
void cModeCommand::Execute(EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = new ("App", 0, 0, 0, 0) BehaviorMessage();
    m->field30 = 0xe11333;
    SetMessageString8(m, 0, av[0]);
    cActionMessage cm;
    cm.mpMessage = m;
    m->b1();                                    // AddRef
    if (args != 0 && args->HasFlag("onExit")) {
        cm.mFlag = 0;
        mpState->vec40.push_back(&cm);
    } else if (mpState->field80 == 0) {
        cm.mFlag = 1;
        mpState->vec2c.push_back(&cm);
    } else {
        cm.mFlag = 0;
        mpState->vec40.push_back(&cm);
    }
    if (cm.mpMessage != 0)
        ((BehaviorMessageBase*)cm.mpMessage)->b2();     // Release
}

// ===========================================================================
// Remaining functions (best-effort / skeletons).
// ===========================================================================
// @ 0x007e42d0  `anonymous namespace'::cMessageCommand::Execute
void cMessageCommand::Execute(EA::ArgScript::cArguments* args) {
    BehaviorMessage* m = new ("App", 0, 0, 0, 0) BehaviorMessage();
    args->MainArguments(0);
    const char** a = args->OptionArgumentsPtr((const void*)0x013fc890, 1);
    if (a != 0)
        m->field30 = VSLOT(PFnPropInt, this->mParser, 0xa0)(this->mParser, a[0]);
    a = args->OptionArguments("data1", 1);
    if (a != 0)
        m->field08 = VSLOT(PFnPropInt, this->mParser, 0xa0)(this->mParser, a[0]);
    a = args->OptionArguments("data2", 1);
    if (a != 0)
        m->field10 = VSLOT(PFnPropInt, this->mParser, 0xa0)(this->mParser, a[0]);
    a = args->OptionArguments("data3", 1);
    if (a != 0)
        m->field18 = VSLOT(PFnPropInt, this->mParser, 0xa0)(this->mParser, a[0]);
    a = args->OptionArguments("data4", 1);
    if (a != 0)
        m->field20 = VSLOT(PFnPropInt, this->mParser, 0xa0)(this->mParser, a[0]);
    a = args->OptionArguments("string", 1);
    if (a != 0)
        SetMessageString8(m, 4, a[0]);
    cActionMessage cm;
    cm.mpMessage = m;
    if (m != 0) m->b1();                        // AddRef
    if (args != 0 && args->HasFlag("onExit")) {
        cm.mFlag = 0;
        this->mpState->vec40.push_back(&cm);
    } else if (this->mpState->field80 == 0) {
        cm.mFlag = 1;
        this->mpState->vec2c.push_back(&cm);
    } else {
        cm.mFlag = 0;
        this->mpState->vec40.push_back(&cm);
    }
    if (cm.mpMessage != 0)
        ((BehaviorMessageBase*)cm.mpMessage)->b2();     // Release
}

// @ 0x007e4760  `anonymous_namespace'::cLoadResourceCommand::Execute
void cLoadResourceCommand::Execute(EA::ArgScript::cArguments* args) {
    int n = 1;
    const char** av = args->MainArguments(&n, 1, 4);
    int d0 = 0, d1 = 0, d2 = 0;
    if (n == 1) {
        cStrW tmp;
        EA::ConvertToString16Impl(&tmp, av[0], 0xffffffffu);
        SPKeyFromName(&d0, *(void**)&tmp, 0, 0);
    } else if (n == 2) {
        cErrorCtor((int*)&d0, (const char*)0x14135f0);
    } else {
        d0 = VSLOT(PFnPropInt, this->mParser, 0x9c)(this->mParser, av[0]);
        d1 = VSLOT(PFnPropInt, this->mParser, 0x9c)(this->mParser, av[1]);
        d2 = VSLOT(PFnPropInt, this->mParser, 0x9c)(this->mParser, av[2]);
    }
    BehaviorMessage* m = new ("App", 0, 0, 0, 0) BehaviorMessage();
    m->field30 = 0x8f1496c0;
    m->field08 = d1;
    m->field10 = d2;
    m->field18 = d0;
    if (n > 3)
        m->field20 = VSLOT(PFnPropInt, this->mParser, 0x9c)(this->mParser, av[3]);
    this->mpState->AddAction(args, m);
}
// @ 0x007e44c0  `anonymous namespace'::cEffectCommand::Execute
void cEffectCommand::Execute(EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = new ("App", 0, 0, 0, 0) BehaviorMessage();
    m->field30 = (args->HasFlag("noStop") ? 1 : 0) + 0xcef220dd;
    SetMessageString8(m, 0, av[0]);
    mpState->AddAction(args, m);
}

// @ 0x007e49f0  `anonymous namespace'::cBoolPropCommand::Execute
void cBoolPropCommand::Execute(EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(2);
    BehaviorMessage* m = NewBehaviorMessage(0x280151c);
    m->field08 = VSLOT(PFnPropInt, this->mParser, 0xa0)(this->mParser, av[0]);
    m->field10 = VSLOT(PFnPropBool, this->mParser, 0x94)(this->mParser, av[1]);  // bool -> movzx
    this->mpState->AddAction(args, m);
}
// @ 0x007e4a80  `anonymous namespace'::cIntPropCommand::Execute
void cIntPropCommand::Execute(EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(2);
    BehaviorMessage* m = NewBehaviorMessage(0x280151d);
    m->field08 = VSLOT(PFnPropInt, this->mParser, 0xa0)(this->mParser, av[0]);
    const char** av2 = args->MainArguments(1);
    m->field10 = VSLOT(PFnPropInt, this->mParser, 0x9c)(this->mParser, av2[0]);
    this->mpState->AddAction(args, m);
}
// @ 0x007e4b20  `anonymous namespace'::cFloatPropCommand::Execute
void cFloatPropCommand::Execute(EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(2);
    BehaviorMessage* m = NewBehaviorMessage(0x280151e);
    m->field08 = VSLOT(PFnPropInt, this->mParser, 0xa0)(this->mParser, av[0]);
    const char** av2 = args->MainArguments(1);
    *(float*)&m->field10 = VSLOT(PFnPropFloat, this->mParser, 0x98)(this->mParser, av2[0]);
    this->mpState->AddAction(args, m);
}
// @ 0x007e4bc0  SP::cAppStateManager::~cAppStateManager
SP::cAppStateManager::~cAppStateManager() {
    mpVtbl0 = (void*)0x1413628;
    mpVtbl1 = (AppStateVt1*)0x1413614;
    mpVtbl2 = (void*)0x1413610;

    // +0x164: eastl string buffer
    if ((mNames164.mpCapacity - mNames164.mpBegin) > 1 && mNames164.mpBegin)
        operator delete(mNames164.mpBegin);

    // +0x160 / +0x15c: reset, +0x158 / +0x154: release
    if (mState160) mState160->a10();
    if (mState15c) mState15c->a10();
    if (mState158) mState158->a04();
    if (mState154) mState154->a04();

    // +0x140: message handler registration
    if (mHandlers.mpHandler) {
        void* h = mHandlers.mpHandler;
        mHandlers.mpHandler = 0;
        RemoveHandler(h, mHandlers.mpA, mHandlers.mpB, mHandlers.mpC, mHandlers.mpD);
    }

    mObj12c.FUN_004b5440();                 // +0x12c
    mObj118.FUN_004b5440();                 // +0x118

    {                                       // +0xf8 state-name map
        int n = mStateNames.mnCount;
        mStateNames.FUN_006a85b0(mStateNames.mpBuckets, n);
        mStateNames.mnSize = 0;
        if (n > 1) operator delete(mStateNames.mpBuckets);
    }
    {                                       // +0xd8 transition-action map
        int n = mTransitionActions.mnCount;
        mTransitionActions.FUN_0093dc70(mTransitionActions.mpBuckets, n);
        mTransitionActions.mnSize = 0;
        if (n > 1) operator delete(mTransitionActions.mpBuckets);
    }
    {                                       // +0xb8 state-action map
        int n = mStateActions.mnCount;
        mStateActions.FUN_00693230(mStateActions.mpBuckets, n);
        mStateActions.mnSize = 0;
        if (n > 1) operator delete(mStateActions.mpBuckets);
    }

    mActionStack.FUN_007e3250();            // +0xa4 action vector

    // +0x90 previous-state buffer (allocator refcount lives at -4)
    if (mpPrevStates && *(int*)((char*)mpPrevStates - 4) != 0)
        operator delete(mpPrevStates);

    mCurrentActions.FUN_007e2680();         // +0x2c

    // +0x18: current name buffer
    if ((mCurrentName.mpCapacity - mCurrentName.mpBegin) > 1 && mCurrentName.mpBegin)
        operator delete(mCurrentName.mpBegin);

    // back to the base vtables
    mpVtbl2 = (void*)0x13ef094;
    mpVtbl1 = (AppStateVt1*)0x13eb394;
    mpVtbl0 = (void*)0x13eb938;
}
// @ 0x007e4e00  hashtable node walk -> vector of state names
void cStateHash::EnumStrings(void* ctx, AMVecU32* out) {
    void** bp = mpBuckets;
    void* node = *bp;
    if (node == 0) {
        do { node = *++bp; } while (node == 0);
    }
    void* end = mpBuckets[mnBucketCount];
    while (node != end) {
        PushStr_553cc0(ctx, node);
        out->push_back(*(unsigned*)((char*)node + 0x10));
        node = *(void**)((char*)node + 0x14);
        while (node == 0) { node = *++bp; }
    }
}
// @ 0x007e4e90  SP::cAppStateCheat::cAppStateCheat
SP::cAppStateCheat::cAppStateCheat(cAppStateManager* owner) : mOwner(owner), mArgSpec(true) {
    cArgumentSpecConstruct(&mArgSpec,
        "State manager control. With no arguments lists current state.",
        "[<state:cstring>]", (void*)&mStateName,
        "Switch to given state.", "-list^", 0,
        "List all states", "-next^", 1,
        "Move to next state", "-prev^", 2,
        "Move to previous state", "-reload^", 3,
        "Force script file to reload", 0);
}
// @ 0x007e4f40  SP::cAppStateCheat::Execute
void SP::cAppStateCheat::Execute(EA::ArgScript::cArguments* args) {
    mStateName = 0;
    mArgSpec.Parse(args, this->mParser);

    if (mStateName != 0) {
        if (isalpha((unsigned char)*mStateName)) {
            int id = mOwner->StateIDFromName(mStateName);
            if (id == -1)
                throw cError("no such state");
            mOwner->SetState(id);
            return;
        }

        int id = ((cArgParserVt*)this->mParser)->ParseStateName(mStateName);
        if (!mOwner->SetState(id))
            throw cError("no such state");
    } else {
        if ((mArgSpec.mFlags >> 3) & 1) {
            if (mOwner->mState154) {
                mOwner->mState154->Call24();
                return;
            }
        }
        if ((mArgSpec.mFlags >> 1) & 1)
            mOwner->Notify(0xe1132d);
        if ((mArgSpec.mFlags >> 2) & 1)
            mOwner->Notify(0xe1132e);
        if (mArgSpec.mFlags & 1) {
            EStringVec names;
            AMVecU32   ids;
            mOwner->EnumStrings(&names, &ids);
            int n = names.Size();
            for (int i = 0; i < n; i++)
                EA::ArgScript::Output((int*)this->mParser, "  %-40.40s [0x%08x]\n",
                                      names[i], ids.mpBegin[i]);
        }
        EA::ArgScript::Output((int*)this->mParser, "Current state: '%s'\n",
                              mOwner->CurrentStateName());
    }
}

struct cArgSpecStub {
    uint32_t raw[7];
    ~cArgSpecStub();    // 0x00405050 EA::ArgScript::cArgumentSpec::~cArgumentSpec
};
struct cOptionCommand : EA::ArgScript::cCommandBase {
    void* pad0c;
    void* pad10;
    cArgSpecStub mOptions;   // +0x14
};
// @ 0x007e51c0  scalar deleting destructor for an option-carrying command
void* ForceOptionCommand() { return new cOptionCommand(); }
void ForceOptionCommandDel(cOptionCommand* p) { delete p; }
