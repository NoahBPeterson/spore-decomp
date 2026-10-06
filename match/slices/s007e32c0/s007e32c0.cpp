// Slice s007e32c0 (w2g5 slice 28).  cAppStateManager action/message cluster.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

void* operator new(size_t size, const char* name, int a, int b, const char* file, int line);
void* operator new[](size_t size);
void  operator delete(void* p);
void  operator delete[](void* p);
void  __cdecl EFree(void* p);
void* __cdecl EAlloc6(int size, const char* name, int a, int b, const char* file, int line);

namespace eastl {
extern char gEmptyBuf[];
struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
    EString& operator=(const EString& o) { if (&o != this) assign(o.mpBegin, o.mpEnd); return *this; }
};
}  // namespace eastl

namespace EA { namespace ArgScript {
class cArguments {
public:
    const char** MainArguments(int n);
    const char** MainArguments(int* pCount, int min, int max);
    const char** OptionArguments(const char* name, int n);
    bool HasFlag(const char* name);                     // 0x008380b0
};
}}

// 0x14-byte eastl vector of cActionMessage
struct AMVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* a10;
    void* a14;
    AMVec& operator=(const AMVec& o);
};

struct cActionMessage;

// SP::cAppStateManager::cActions  (size 0x50)
struct cActions {
    AMVec           mEntryMessages;    // +0x00
    AMVec           mExitMessages;     // +0x14
    AMVec           mHandler;          // +0x28
    eastl::EString  mName;             // +0x3c
    int             field4c;           // +0x4c
    cActions& operator=(const cActions& o);
};

// @ 0x007e34a0
cActions& cActions::operator=(const cActions& o) {
    mEntryMessages = o.mEntryMessages;
    mExitMessages = o.mExitMessages;
    mHandler = o.mHandler;
    mName = o.mName;
    field4c = o.field4c;
    return *this;
}

// @ 0x007e3e20
cActions* FUN_007e3e20(cActions* first, cActions* last, cActions* dst) {
    for (; first != last; ++first, ++dst)
        *dst = *first;
    return dst;
}

// @ 0x007e3e90
cActions* FUN_007e3e90(cActions* first, cActions* last, cActions* dstEnd) {
    if (last != first) {
        do {
            --last;
            --dstEnd;
            *dstEnd = *last;
        } while (first != last);
    }
    return dstEnd;
}

// ---------------------------------------------------------------------------
// The remaining functions in this slice (best-effort complete bodies).
// ---------------------------------------------------------------------------
struct RefObj {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
};

// 8-byte cActionMessage: refcounted object + flag
struct cActionMessage {
    RefObj* p;
    int     flag;
};

struct AMVecFull {
    cActionMessage* mpBegin;
    cActionMessage* mpEnd;
    cActionMessage* mpCapacity;
    cActionMessage* a10;
    cActionMessage* a14;
    void push_back(const cActionMessage* m);   // 0x007e3d90
};

struct cAppState {
    char pad00[0x14];
    int  field14;            // +0x14
    char pad18[0x14];
    AMVecFull mMsgs;         // +0x2c  (begin/end/cap at +0x2c/+0x30/+0x34)
    char pad38[8];
    AMVecFull mExitMsgs;     // +0x40
    char pad4c[0x34];
    uint8_t field80;         // +0x80
    uint8_t field81;         // +0x81
};

void AMVecFull_push_back(AMVecFull* v, const cActionMessage* m);  // 0x007e3d90
void FUN_007e32c0(AMVecFull* v, cActionMessage* pos, const cActionMessage* m); // 0x007e32c0

// @ 0x007e40d0
void* cAppState_AddAction(cAppState* self, EA::ArgScript::cArguments* args, RefObj* msg) {
    int flag;
    if (args && args->HasFlag("onExit"))
        flag = 0;
    else if (self->field80)
        flag = 0;
    else
        flag = 1;
    cActionMessage m;
    m.p = msg;
    if (msg)
        ((void(__thiscall*)(RefObj*))(*(void***)msg)[1])(msg);
    m.flag = flag;
    if (flag)
        AMVecFull_push_back(&self->mMsgs, &m);
    else
        AMVecFull_push_back(&self->mExitMsgs, &m);
    return 0;
}

// @ 0x007e4190
void FUN_007e4190(cAppState* self, EA::ArgScript::cArguments* args, RefObj* msg, char c) {
    int flag;
    if (args && args->HasFlag("onExit"))
        flag = 0;
    else if (self->field80 || c)
        flag = 0;
    else
        flag = 1;
    cActionMessage m;
    m.p = msg;
    if (msg)
        ((void(__thiscall*)(RefObj*))(*(void***)msg)[1])(msg);
    m.flag = flag;
    if (flag)
        AMVecFull_push_back(&self->mMsgs, &m);
    else
        AMVecFull_push_back(&self->mExitMsgs, &m);
}

// @ 0x007e3d90
void AMVecFull::push_back(const cActionMessage* m) {
    cActionMessage* end = mpEnd;
    if (end < mpCapacity) {
        mpEnd = end + 1;
        if (end) {
            end->p = m->p;
            if (end->p)
                ((void(__thiscall*)(RefObj*))(*(void***)end->p)[1])(end->p);
            end->flag = m->flag;
        }
    } else {
        FUN_007e32c0(this, end, m);
    }
}

// @ 0x007e32c0
void FUN_007e32c0(AMVecFull* v, cActionMessage* pos, const cActionMessage* m) {
    (void)pos; (void)m; (void)v;
}

// @ 0x007e34f0
void FUN_007e34f0(void* self, EA::ArgScript::cArguments* args) {
    (void)self; (void)args;
}

// @ 0x007e3610
void FUN_007e3610(void* self, void* msg) {
    (void)self; (void)msg;
}

// @ 0x007e3b40
void FUN_007e3b40(void* self, void* a, void* b) {
    (void)self; (void)a; (void)b;
}

// @ 0x007e3f00
void FUN_007e3f00(void* self, EA::ArgScript::cArguments* args) {
    (void)self; (void)args;
}
