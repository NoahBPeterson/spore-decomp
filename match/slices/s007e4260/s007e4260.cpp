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

namespace EA { namespace ArgScript {
class cArguments {
public:
    const char** MainArguments(int n);
    const char** MainArguments(int* pCount, int min, int max);
    const char** OptionArguments(const char* name, int n);
    const char** OptionArgumentsPtr(const void* name, int n);
    bool HasFlag(const char* name);
};
struct cICommand {
    virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3();
    virtual void i4(); virtual void i5();
};
struct cCommandBase : cICommand {
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
void SPKeyFromName(void* out, const void* name, int a, int b);       // 0x0068d840
namespace EA { void ConvertToString16Impl(void* out, const char* s, unsigned len); }  // 0x0093c5a0
void cErrorCtor(int* out, const char* text);                          // 0x0052df30  (does not return)
void PushStr_553cc0(void* self, void* node);                          // 0x00553cc0  (__thiscall)

struct cArgumentSpec {                                     // 0xc8 bytes
    char o[0xc8];
    cArgumentSpec(bool hasArgs);                           // 0x0083a9f0
};
void cArgumentSpecConstruct(cArgumentSpec* spec, const char* desc, const char* usage, void* str,
                            const char* d1, const char* f1, int t1,
                            const char* d2, const char* f2, int t2,
                            const char* d3, const char* f3, int t3,
                            const char* d4, const char* f4, int t4,
                            const char* d5, int t5);        // 0x0083bcd0

struct AMVecU32 {
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap;
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
    int           mPad0c;      // +0x0c
    cAppState*    mOwner;      // +0x10
    cArgumentSpec mArgSpec;    // +0x14
    char          mStr[0x40];  // +0xdc
    cAppStateCheat(cAppState* owner);
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
// @ 0x007e4bc0
void FUN_007e4bc0(void* a) { (void)a; }
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
SP::cAppStateCheat::cAppStateCheat(cAppState* owner) : mOwner(owner), mArgSpec(true) {
    cArgumentSpecConstruct(&mArgSpec,
        "State manager control. With no arguments lists current state.",
        "[<state:cstring>]", (void*)mStr,
        "Switch to given state.", "-list^", 0,
        "List all states", "-next^", 1,
        "Move to next state", "-prev^", 2,
        "Move to previous state", "-reload^", 3,
        "Force script file to reload", 0);
}
// @ 0x007e4f40
void FUN_007e4f40(void* a, void* b) { (void)a; (void)b; }

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
