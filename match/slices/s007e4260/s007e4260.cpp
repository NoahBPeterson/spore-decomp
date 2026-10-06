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
long  _InterlockedExchange(volatile long* target, long value);

namespace EA { namespace ArgScript {
class cArguments {
public:
    const char** MainArguments(int n);
    const char** MainArguments(int* pCount, int min, int max);
    const char** OptionArguments(const char* name, int n);
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
    ~cCommandBase();
};
struct OptionParser {
    virtual void o0(); virtual void o1(); virtual void o2();
    ~OptionParser();
};
}}

void SetMessageString8(void* msg, int a, const char* s);   // 0x00618bd0
void* cAppStateManager_AddAction(void* self, EA::ArgScript::cArguments* args, void* msg); // 0x007e40d0

// UI::BehaviorMessage (0x40 bytes; two polymorphic levels).
struct BehaviorMessageBase {
    virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3();
    int mRefCount;          // +0x4
};
struct BehaviorMessage : BehaviorMessageBase {
    virtual void b4();      // gives the derived level its own vtable
    char pad08[0x28];
    int  field30;           // +0x30 message id
    int  field34;           // +0x34
    int  field38;           // +0x38
    BehaviorMessage() : field30(0), field38(0) { _InterlockedExchange((volatile long*)&mRefCount, 0); }
};

static inline BehaviorMessage* NewBehaviorMessage(int msgid) {
    BehaviorMessage* m = new ("App", 0, 0, 0, 0) BehaviorMessage();
    m->field30 = msgid;
    return m;
}

struct cAppStateCmd : EA::ArgScript::cCommandBase {
    void* mpState;   // +0xc
};

// @ 0x007e4260  cGotoStateCommand::Execute
void FUN_007e4260(cAppStateCmd* self, EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xe11330);
    SetMessageString8(m, 0, av[0]);
    cAppStateManager_AddAction(self->mpState, args, m);
}

// @ 0x007e46f0  cCheatCommand::Execute
void FUN_007e46f0(cAppStateCmd* self, EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xcef220e1);
    SetMessageString8(m, 0, av[0]);
    cAppStateManager_AddAction(self->mpState, args, m);
}

// @ 0x007e48f0  cLightingCommand::Execute
void FUN_007e48f0(cAppStateCmd* self, EA::ArgScript::cArguments* args) {
    BehaviorMessage* m = NewBehaviorMessage(0x6f188ef2);
    const char** av = args->MainArguments(1);
    SetMessageString8(m, 0, av[0]);
    cAppStateManager_AddAction(self->mpState, args, m);
}

// @ 0x007e4970  cCameraCommand::Execute
void FUN_007e4970(cAppStateCmd* self, EA::ArgScript::cArguments* args) {
    BehaviorMessage* m = NewBehaviorMessage(0x6f188ef8);
    const char** av = args->MainArguments(1);
    SetMessageString8(m, 0, av[0]);
    cAppStateManager_AddAction(self->mpState, args, m);
}

// @ 0x007e4550  cKillEffectCommand::Execute
void FUN_007e4550(cAppStateCmd* self, EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xcef220e0);
    SetMessageString8(m, 0, av[0]);
    m->field34 = args->HasFlag("softStop") ? 1 : 0;
    cAppStateManager_AddAction(self->mpState, args, m);
}

// @ 0x007e45e0  cModeCommand::Execute
void FUN_007e45e0(cAppStateCmd* self, EA::ArgScript::cArguments* args) {
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xe11333);
    SetMessageString8(m, 0, av[0]);
    (void)self;
    (void)av;
    (void)m;
}

// ===========================================================================
// Remaining functions (best-effort / skeletons).
// ===========================================================================
// @ 0x007e42d0
void FUN_007e42d0(void* a, void* b) { (void)a; (void)b; }
// @ 0x007e44c0
void FUN_007e44c0(void* a) { (void)a; }
// @ 0x007e4760
void FUN_007e4760(void* a, void* b) { (void)a; (void)b; }
// @ 0x007e49f0
void FUN_007e49f0(void* a, void* b) { (void)a; (void)b; }
// @ 0x007e4a80
void FUN_007e4a80(void* a, void* b) { (void)a; (void)b; }
// @ 0x007e4b20
void FUN_007e4b20(void* a, void* b) { (void)a; (void)b; }
// @ 0x007e4bc0
void FUN_007e4bc0(void* a) { (void)a; }
// @ 0x007e4e00
void FUN_007e4e00(void* a, void* b) { (void)a; (void)b; }
// @ 0x007e4e90
void FUN_007e4e90(void* a) { (void)a; }
// @ 0x007e4f40
void FUN_007e4f40(void* a, void* b) { (void)a; (void)b; }

// @ 0x007e51c0  scalar deleting destructor for an option-carrying command
struct cOptionCommand : EA::ArgScript::cCommandBase {
    void* pad0c;
    void* pad10;
    EA::ArgScript::OptionParser mOptions;   // +0x14
    virtual ~cOptionCommand() {}
};
void* ForceOptionCommand() { return new cOptionCommand(); }
