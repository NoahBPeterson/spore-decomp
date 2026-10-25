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
    const char** MainArguments(int n);                  // 0x00838320
    const char** MainArguments(int* pCount, int min, int max);
    const char** OptionArguments(const char* name, int n);  // 0x00838330
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
    cActions();                        // 0x007e2600
    ~cActions();                       // 0x007e2680
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
    __declspec(noinline) void push_back(const cActionMessage* m);   // 0x007e3d90
    void grow(cActionMessage* pos, const cActionMessage* m);  // 0x007e32c0
};

struct cAppState {
    char pad00[0x14];
    int  field14;            // +0x14
    char pad18[0x14];
    AMVecFull mMsgs;         // +0x2c  (begin/end/cap at +0x2c/+0x30/+0x34)
    AMVecFull mExitMsgs;     // +0x40
    char pad54[0x2c];
    uint8_t field80;         // +0x80
    uint8_t field81;         // +0x81
    void AddAction(EA::ArgScript::cArguments* args, RefObj* msg);
    void AddMessage(EA::ArgScript::cArguments* args, RefObj* msg, char c);
};

void AMVecFull_push_back(AMVecFull* v, const cActionMessage* m);  // 0x007e3d90

// @ 0x007e40d0
void cAppState::AddAction(EA::ArgScript::cArguments* args, RefObj* msg) {
    cAppState* self = this;
    bool exitPath = (args && args->HasFlag("onExit")) || self->field80;
    cActionMessage m;
    m.p = msg;
    if (msg)
        ((void(__thiscall*)(RefObj*))(*(void***)msg)[1])(msg);
    m.flag = 0;
    if (exitPath)
        self->mExitMsgs.push_back(&m);
    else
        self->mMsgs.push_back(&m);
    if (m.p)
        ((void(__thiscall*)(RefObj*))(*(void***)m.p)[2])(m.p);
}

// @ 0x007e4190
void cAppState::AddMessage(EA::ArgScript::cArguments* args, RefObj* msg, char c) {
    cAppState* self = this;
    bool exitPath = (args && args->HasFlag("onExit")) || self->field80 || c;
    cActionMessage m;
    m.p = msg;
    if (msg)
        ((void(__thiscall*)(RefObj*))(*(void***)msg)[1])(msg);
    m.flag = 1;
    if (exitPath)
        self->mExitMsgs.push_back(&m);
    else
        self->mMsgs.push_back(&m);
    if (m.p)
        ((void(__thiscall*)(RefObj*))(*(void***)m.p)[2])(m.p);
}

// @ 0x007e3d90
void AMVecFull::push_back(const cActionMessage* m) {
    cActionMessage* end = mpEnd;
    if (end >= mpCapacity) {
        grow(end, m);
        return;
    }
    mpEnd = end + 1;
    if (end) {
        end->p = m->p;
        if (end->p)
            ((void(__thiscall*)(RefObj*))(*(void***)end->p)[1])(end->p);
        end->flag = m->flag;
    }
}

// ===========================================================================
// Reworked functions (this pass): the four cluster members are reconstructed
// in full; HandleMessage keeps a documented skeleton (see the fixlog).
// ===========================================================================

// ---------------------------------------------------------------------------
// Helper call targets.  Their definitions live in other translation units, so
// every call below is a masked relocation; the trailing comment is the retail
// image address the call must land on.
// ---------------------------------------------------------------------------
void  __cdecl FUN_008df050(void* first, void* last, void* result);   // 0x008df050 eastl copy_backward
void* __cdecl FUN_007e1830(void* first, void* last, void* dst);      // 0x007e1830 move range -> dst end
void  __cdecl FUN_007e18d0(void* first, void* last, void* dst);      // 0x007e18d0 destroy range
uint32_t __cdecl HashString(const char* s, uint32_t seed, int n);    // 0x00932e80 FNV-1, seed 0x811c9dc5
extern "C" unsigned int __cdecl strlen(const char* s);               // intrinsic

struct cMessageServer;
struct cIParser;
struct cAppStateManager;

// error object used by the state/transition parsers (0x0052df30, cdecl: the
// destination object pointer is the first pushed argument).
struct cError_ArgScript {
    uint32_t pad[4];
    cError_ArgScript(const char* fmt, ...);            // 0x0052df30
    cError_ArgScript(const cError_ArgScript&);
};

// ---------------------------------------------------------------------------
// state-action hash map (lives at manager+0xb8): buckets + bucket count
// ---------------------------------------------------------------------------
struct cStateActionsMap {
    void*   mpNodeAllocator;   // +0xb8
    void**  mpBucketArray;     // +0xbc
    int     mnBucketCount;     // +0xc0
    void find(void** out, const uint32_t* key);        // 0x00645ed0 __thiscall ret 8
};

// ---------------------------------------------------------------------------
// The eastl vectors embedded in the manager are 0x14 bytes each.
// ---------------------------------------------------------------------------
struct UintVec {
    uint32_t* mpBegin;         // +0x00
    uint32_t* mpEnd;           // +0x04
    uint32_t* mpCapacity;      // +0x08
    void*     mpExtra0;        // +0x0c
    void*     mpExtra1;        // +0x10
    void DoInsertValue(uint32_t* pos, const uint32_t* value);  // 0x004558a0 ret 8
    void push_back(uint32_t value) {
        uint32_t* e = mpEnd;
        if (e >= mpCapacity) {
            DoInsertValue(e, &value);
            return;
        }
        mpEnd = e + 1;
        if (e)
            *e = value;
    }
};

struct ActionsVec {                 // vector<cActions> slot at manager+0xa4
    void* mpBegin; void* mpEnd; void* mpCapacity;
    void* mpExtra0; void* mpExtra1;
};

// ---------------------------------------------------------------------------
// message server (singleton accessor 0x0067dcc0)
// ---------------------------------------------------------------------------
struct cMessageServer {
    virtual void v0() {} virtual void v1() {} virtual void v2() {}
    virtual void v3() {} virtual void v4() {}
    virtual void Send(uint32_t id, void* msg, void* a) {}          // +0x14 slot 5
    virtual void Post(uint32_t id, void* msg, void* a, void* b) {} // +0x18 slot 6
};
cMessageServer* __cdecl MessageServer();                           // 0x0067dcc0

// ---------------------------------------------------------------------------
// StateChangeMessage (0x40 bytes): base vptr/refcount, old+new state id, owner.
// The two vptr stores in the retail ctor are the base then the derived ctor.
// ---------------------------------------------------------------------------
struct MessageRC {
    virtual void mr0() {}                    // slot 0
    virtual int  AddRef() { return ++mRefCount; }   // slot 1 (+0x04)
    virtual int  Release() { return --mRefCount; }  // slot 2 (+0x08)
    int mRefCount;                           // +0x04
    MessageRC() : mRefCount(0) {}
};
struct StateChangeMessage : MessageRC {
    uint32_t mOld;        // +0x08
    uint32_t mPad0c;      // +0x0c
    uint32_t mNew;        // +0x10
    uint32_t mPad14;      // +0x14
    void*    mMgr;        // +0x18
    char     mPad1c[0x14];// +0x1c
    uint32_t mField30;    // +0x30
    uint32_t mPad34;      // +0x34
    uint32_t mField38;    // +0x38
    uint32_t mPad3c;      // +0x3c
    StateChangeMessage() { mField30 = 0; mField38 = 0; }
};

// ---------------------------------------------------------------------------
// cIParser: 35 leading virtuals, Notify at +0x8c (slot 35) and
// StateIdFromString at +0xa0 (slot 40).  Declarations only: never instantiated.
// ---------------------------------------------------------------------------
struct cIParser {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34();
    virtual void Notify(void* cmd);                    // +0x8c slot 35
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual uint32_t StateIdFromString(const char* s); // +0xa0 slot 40
};

// ---------------------------------------------------------------------------
// cAppStateManager: main vtable at +0x00 (17 slots, StateIDFromName at +0x38),
// the IHandlerRC vtable at +0x04, refcount at +0x08, then the retail fields.
// ---------------------------------------------------------------------------
struct cAppStateManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual uint32_t StateIDFromName(const char* name);   // +0x38 slot 14
    virtual void v15(); virtual void v16();

    void*    mHandlerVtbl;             // +0x04  (IHandlerRC vtable)
    int      mRefCount;                // +0x08
    char     mPad0c[8];                // +0x0c
    int      mDispatchMethod;          // +0x14  0 = kPost, 1 = kSend
    eastl::EString mCurrentName;       // +0x18
    uint32_t mCurrentStateID;          // +0x28
    cActions mCurrentActions;          // +0x2c
    uint32_t mChainState;              // +0x7c
    uint8_t  mOnExit;                  // +0x80
    uint8_t  mSendTransitionMessages;  // +0x81
    char     mPad82[2];                // +0x82
    uint32_t mCheatName;               // +0x84
    uint32_t mCurrentState;            // +0x88
    uint32_t mNextState;               // +0x8c
    UintVec  mPreviousStates;          // +0x90
    ActionsVec mActionsList;           // +0xa4
    cStateActionsMap mStateActionsMap; // +0xb8

    void LeaveState(uint32_t s);                   // 0x007e2810 __thiscall ret 4
    void SetStates(uint32_t from, uint32_t to);    // 0x007e30a0 __thiscall ret 8
    void ActionAdded(uint32_t id);                 // 0x007e2ce0 __thiscall ret 4
    bool SwitchToState(uint32_t next);             // 0x007e3b40 __thiscall ret 4
};

// the message-handler base that sits at manager+0x4 (HandleMessage receives
// `this` = manager+4 and reaches the main vtable through this[-1]).
struct IHandlerRC {
    int HandleMessage(uint32_t id, void* msg);     // 0x007e3610
};

// command objects: vptr+0, parser+4, refcount+8, manager+0x30 (0x3c bytes)
struct cCommandBase {
    void*  mCommandVtbl;       // +0x00
    cIParser* mParser;         // +0x04
    int    mRefCount;          // +0x08
    char   mPad0c[0x24];       // +0x0c
    cAppStateManager* mMgr;    // +0x30
};
struct cTransitionCommand : cCommandBase {
    uint32_t mFrom;            // +0x34
    uint32_t mTo;              // +0x38
    void Execute(EA::ArgScript::cArguments* args);   // 0x007e34f0
};
struct cStateCommand : cCommandBase {
    void Execute(EA::ArgScript::cArguments* args);   // 0x007e3f00
};

// eastl allocator file name used by the in-line vector growth (retail string)
static const char kEaStlAllocH[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// 8-byte cActionMessage vector (layout-identical to AMVecFull, but a distinct
// type so the existing AMVecFull::push_back keeps calling the original 0x007e32c0)
struct AMMsgVec {
    cActionMessage* mpBegin;    // +0x00
    cActionMessage* mpEnd;      // +0x04
    cActionMessage* mpCapacity; // +0x08
    cActionMessage* mpExtra0;   // +0x0c
    cActionMessage* mpExtra1;   // +0x10
    void grow(cActionMessage* pos, const cActionMessage* value);   // 0x007e32c0
};

// ---------------------------------------------------------------------------
// @ 0x007e32c0  vector<cActionMessage>::insert/grow
// ---------------------------------------------------------------------------
void AMMsgVec::grow(cActionMessage* pos, const cActionMessage* value) {
    cActionMessage* e = mpEnd;
    if (e != mpCapacity) {
        // in place: make room by copying the last element up, shift, overwrite
        if (pos <= value && value < e)
            ++value;
        if (e) {
            RefObj* last = (RefObj*)e[-1].p;
            e->p = last;
            if (last)
                ((void(__thiscall*)(RefObj*))(*(void***)last)[1])(last);
            e->flag = e[-1].flag;
        }
        FUN_008df050(pos, e - 1, e);
        RefObj* nv = (RefObj*)value->p;
        RefObj* ov = (RefObj*)pos->p;
        if (nv != ov) {
            if (nv)
                ((void(__thiscall*)(RefObj*))(*(void***)nv)[1])(nv);
            pos->p = nv;
            if (ov)
                ((void(__thiscall*)(RefObj*))(*(void***)ov)[2])(ov);
        }
        pos->flag = value->flag;
        mpEnd = e + 1;
        return;
    }
    // grow: allocate 2x (or 1), move [begin,pos) and [pos,end), free the old block
    int n = (int)(mpEnd - mpBegin);
    int newCap = n ? n * 2 : 1;
    cActionMessage* newBegin;
    if (newCap)
        newBegin = (cActionMessage*)operator new((size_t)newCap * 8, "App", 0, 0, kEaStlAllocH, 0xd1);
    else
        newBegin = 0;
    cActionMessage* slot = (cActionMessage*)FUN_007e1830(mpBegin, pos, newBegin);
    FUN_007e18d0(mpBegin, pos, newBegin);
    if (slot) {
        RefObj* np = (RefObj*)value->p;
        slot->p = np;
        if (np)
            ((void(__thiscall*)(RefObj*))(*(void***)np)[1])(np);
        slot->flag = value->flag;
    }
    cActionMessage* e2 = mpEnd;
    cActionMessage* newEnd = (cActionMessage*)FUN_007e1830(pos, e2, slot + 1);
    FUN_007e18d0(pos, e2, slot + 1);
    if (mpBegin && ((int*)mpBegin)[-1])
        operator delete[](mpBegin);
    mpEnd = newEnd;
    mpBegin = newBegin;
    mpCapacity = newBegin + newCap;
}

// ---------------------------------------------------------------------------
// @ 0x007e34f0  cTransitionCommand::Execute
// ---------------------------------------------------------------------------
void cTransitionCommand::Execute(EA::ArgScript::cArguments* args) {
    if (mMgr->mCurrentName.mpBegin != mMgr->mCurrentName.mpEnd)
        throw cError_ArgScript("can't nest states or transitions");
    const char** argv = args->MainArguments(2);
    mFrom = mMgr->StateIDFromName(argv[0]);
    mTo   = mMgr->StateIDFromName(argv[1]);
    if (mFrom == 0xffffffff)
        throw cError_ArgScript("unknown from state");
    if (mTo == 0xffffffff)
        throw cError_ArgScript("unknown to state");
    cActions tmp;
    mMgr->mCurrentActions = tmp;
    mParser->Notify(this);
}

// ---------------------------------------------------------------------------
// @ 0x007e3f00  cStateCommand::Execute
// ---------------------------------------------------------------------------
void cStateCommand::Execute(EA::ArgScript::cArguments* args) {
    if (mMgr->mCurrentName.mpBegin != mMgr->mCurrentName.mpEnd)
        throw cError_ArgScript("can't nest states or transitions");
    const char** argv = args->MainArguments(1);
    mMgr->mCurrentName.assign(argv[0], argv[0] + strlen(argv[0]));
    mMgr->mCurrentActions = cActions();
    mMgr->mCurrentActions.mName.assign(argv[0], argv[0] + strlen(argv[0]));
    const char** opt = args->OptionArguments("id", 1);
    uint32_t id;
    if (opt)
        id = mParser->StateIdFromString(opt[0]);
    else
        id = HashString(mMgr->mCurrentName.mpBegin, 0x811c9dc5, 1);
    mMgr->mCurrentStateID = id;
    void* out;
    mMgr->mStateActionsMap.find(&out, &mMgr->mCurrentStateID);
    if (out != mMgr->mStateActionsMap.mpBucketArray[mMgr->mStateActionsMap.mnBucketCount])
        throw cError_ArgScript("A state with this ID already exists");
    mParser->Notify(this);
}

// ---------------------------------------------------------------------------
// @ 0x007e3b40  cAppStateManager::SwitchToState
// ---------------------------------------------------------------------------
bool cAppStateManager::SwitchToState(uint32_t next) {
    if (mCurrentState == next)
        return true;
    if (mSendTransitionMessages) {
        StateChangeMessage* m = new ("App", 0, 0, 0, 0) StateChangeMessage;
        if (m)
            m->AddRef();
        m->mOld = mCurrentState;
        m->mNew = next;
        m->mMgr = this;
        cMessageServer* srv = MessageServer();
        if (mDispatchMethod == 0)
            srv->Post(0x2319914, m, 0, 0);
        else if (mDispatchMethod == 1)
            srv->Send(0x2319914, m, 0);
        if (m)
            m->Release();
    }
    LeaveState(mCurrentState);
    mNextState = 0xffffffff;
    SetStates(mCurrentState, next);
    {
        void* out;
        mStateActionsMap.find(&out, &next);
        if (out != mStateActionsMap.mpBucketArray[mStateActionsMap.mnBucketCount])
            ActionAdded(*(uint32_t*)((char*)out + 4));
    }
    if (mSendTransitionMessages) {
        StateChangeMessage* m = new ("App", 0, 0, 0, 0) StateChangeMessage;
        if (m)
            m->AddRef();
        m->mOld = mCurrentState;
        m->mNew = next;
        m->mMgr = this;
        cMessageServer* srv = MessageServer();
        if (mDispatchMethod == 0)
            srv->Post(0x2319915, m, 0, 0);
        else if (mDispatchMethod == 1)
            srv->Send(0x2319915, m, 0);
        if (m)
            m->Release();
    }
    if (mCurrentState != 0xffffffff)
        mPreviousStates.push_back(mCurrentState);
    mCurrentState = next;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x007e3610  IHandlerRC::HandleMessage  (SKELETON -- see the fixlog)
//
// The retail body (1320 bytes) is a message-id switch that fans out to the
// manager, the effects/cheat/model managers and the app property lists.  A
// faithful rewrite needs interfaces this slice cannot declare from its own
// text, so only the dispatch gate is modelled here: the two ids the retail
// switch falls through to `return 1` are answered with 1, everything else 0.
// ---------------------------------------------------------------------------
int IHandlerRC::HandleMessage(uint32_t id, void* msg) {
    (void)msg;
    if (id == 0xe11331 || id == 0xcef220dd)
        return 1;
    return 0;
}
