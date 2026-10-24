// match/slices/s00d47630/s00d47630.cpp
// Slice s00d47630 -- SP::cCreatureModeStrategy::Init, the anonymous-namespace
// cCreatureTriggerSystem trigger lookup/evaluation helpers, the tr1
// ContentValidationSummarizer node-pool teardown and the creature-mode
// collectable-item roll helper.
// Reconstructed from work/match/scratch_s00d47630_card.txt.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast

typedef unsigned int     u32;
typedef signed   int     i32;
typedef unsigned char    u8;
typedef unsigned short   u16;
typedef unsigned __int64 u64;
typedef float            f32;
typedef double           f64;

// ---------------------------------------------------------------------------
// Free helpers / globals referenced by absolute address.
// ---------------------------------------------------------------------------
void FUN_00f47380(void* p);                 // operator delete (0x00f47380)
void FUN_00f473a0(void* p);                 // operator delete (0x00f473a0, pool entry)
void FUN_00f14270(void* dst, void* src);     // sp_vector slow push_back (0x00f14270)
void FUN_00b534c0(void* container, void* v); // global key/value list grow (0x00b534c0)
void FUN_00d38f40();                         // 0x00d38f40 (ecx = this)
void FUN_00d472a0();                         // 0x00d472a0 (ecx = cTriggersInfo + 4)
void FUN_00d47510();                         // 0x00d47510 (ecx = cTriggerMap)


// ---------------------------------------------------------------------------
// The node pool embedded in the content-validation summarizer (+0x08).
// ---------------------------------------------------------------------------
struct cNodePool {
    u8      pad_00[4];                          // +0x00
    void*   mpTail;                             // +0x04  first detached node
    u32     mCount;                             // +0x08  live node count
    u32     mField_0c;                          // +0x0c  reset to 0 on teardown
    u8      pad_10[0x0c];                       // +0x10
    void*   mpFreeHead;                         // +0x1c  free-list head
    u8      pad_20[4];                          // +0x20
    u8*     mpPoolLo;                           // +0x24  pool range begin
    u8*     mpPoolHi;                           // +0x28  pool range end
    u8      pad_2c[4];                          // +0x2c
    void*   mpSentinel;                         // +0x30
    void  FreeLists(void* first, u32 count);    // 0x00d3f9e0
};

struct cContentValidationSummarizer {
    void*     mVtbl_00;                         // +0x00
    u8        pad_04[4];                        // +0x04
    cNodePool mPool;                            // +0x08

    void FUN_00d47850();                        // 0x00d47850
};

// ===========================================================================
// @ 0x00d47850
// ===========================================================================
void cContentValidationSummarizer::FUN_00d47850()
{
    cNodePool* pool = &mPool;
    mVtbl_00 = (void*)0x147adf8;
    pool->FreeLists(pool->mpTail, pool->mCount);
    u8* p = (u8*)pool->mpTail;
    pool->mField_0c = 0;
    if (pool->mCount > 1 && p != (u8*)pool->mpSentinel) {
        if (p >= pool->mpPoolLo && p < pool->mpPoolHi) {
            *(void**)p = pool->mpFreeHead;
            pool->mpFreeHead = p;
            mVtbl_00 = (void*)0x13ec458;
            return;
        }
        FUN_00f473a0(p);
    }
    mVtbl_00 = (void*)0x13ec458;
}

// ---------------------------------------------------------------------------
// Trigger records (stride 0x2c) and the objects they hang off.
// ---------------------------------------------------------------------------
struct cTriggerRef;                             // ref-counted object (declared below)
struct cTriggerRec {
    cTriggerRef* mpRef_00;                      // +0x00  AutoRefCount<cTriggerRef> slot
    u8      pad_04[4];                          // +0x04
    u8      mFlag_08;                           // +0x08
    u8      pad_09[3];                          // +0x09
    u32     mKind_0c;                           // +0x0c  ria id / event id
    u8      pad_10[0x1c];                       // +0x10
};

struct cTriggerOwner {                          // event carrier passed by pointer
    void**  mVtbl_00;                           // +0x00
    u8      pad_04[0x20];                       // +0x04
    u32     mKey_24;                            // +0x24  owner key / event type
    void*   mpObj_28;                           // +0x28  related object
};

struct cTriggerEvent {                          // the event object itself
    void*   mpObject_00;                        // +0x00  object whose +0xb58 flags are read
    void*   mpOwner_04;                         // +0x04
};

struct cNounManager {
    u8* Find(void* key);                        // 0x00b21000
};

struct cPropertyManager {                       // opaque property manager
    void**  mVtbl_00;                           // +0x00
};

struct cTriggerRef {                            // ref-counted object
    void**  mVtbl_00;                           // +0x00
    void AddRef();                              // 0x00 (vtable slot 0x00)
    void Release();                             // 0x00 (vtable slot 0x04)
};

struct cTrigFindCtx {                           // 3-dword context for 0x00d47510
    u32                mKey_00;                 // +0x00
    u32                mZero_04;                // +0x04
    cPropertyManager*  mpManager_08;            // +0x08
};

struct cTrigNodeList {                          // element returned by the map lookup
    u8           pad_00[8];                     // +0x00
    cTriggerRec* mpBegin_08;                    // +0x08
    cTriggerRec* mpEnd_0c;                      // +0x0c
};

struct cTrigSlots {                             // sp_vector<cTriggerRec> at info+0x04
    cTriggerRec* mpBegin_00;                    // +0x00
    cTriggerRec* mpEnd_04;                      // +0x04
    u8           pad_08[4];                     // +0x08
    void Append();                              // 0x00d472a0 (ecx = this)
};

struct cTriggersInfo {
    cTriggerRef* mpOwner_00;                    // +0x000
    cTrigSlots   mSlots;                        // +0x004
    u8           pad_0c[0x170];                 // +0x00c
    u8           mFlag_17c;                     // +0x17c
};

struct cTriggerMap {
    u8      pad_00[4];                          // +0x00
    u8**    mpBegin;                            // +0x04  element pointer table
    u32     mCount;                             // +0x08
    void  Find(u8** ppIter, const u32* key);    // 0x00d46b70
    cTriggersInfo* NewInfo(cTrigFindCtx* ctx);  // 0x00d47510 (ecx = this)
};

void GetPropertyAsUint32Array(void* prop, u32 key, i32* count, u32** array); // 0x006a0840
cNounManager*     SP_NounManager();             // 0x00b3d300
cPropertyManager* SP_PropertyManager();         // 0x0067de30

// vtable slot helpers (ecx = first argument)
typedef void* (__thiscall *cOwnerVirt20)(cTriggerOwner*, void*);      // slot 0x20
typedef void  (__thiscall *cRefVirt)(cTriggerRef*);                   // slots 0x00 / 0x04
typedef bool  (__thiscall *cPropMgrVirt2c)(cPropertyManager*, u32, u32, cTriggerRef**);

inline void cTriggerRef::AddRef()  { ((cRefVirt)mVtbl_00[0x00 / 4])(this); }
inline void cTriggerRef::Release() { ((cRefVirt)mVtbl_00[0x04 / 4])(this); }

struct cCreatureTriggerSystem {
    u8        pad_00[8];                        // +0x00
    cTriggerMap mMap;                           // +0x08

    cTriggerRec* GetTrigger(u32 eventType, cTriggerOwner* owner);      // 0x00d47630
    bool         EvaluateEvent(u32 eventID, cTriggerEvent* ev);        // 0x00d478b0
    bool         EvaluateTrigger(cTriggerRec* t, void* owner, void* obj); // 0x00d46c30
    void         ReadTrigger(cTriggerRec* rec);                        // 0x00d46730
};

// ===========================================================================
// @ 0x00d478b0
// ===========================================================================
bool cCreatureTriggerSystem::EvaluateEvent(u32 eventID, cTriggerEvent* ev)
{
    void* owner = ev->mpOwner_04;
    if (owner == 0)
        return false;
    switch (eventID) {
    case 0xd335362b:
    case 0xd335362c:
    case 0xd335362d:
    case 0xd335362e:
    case 0xd3353636:
    case 0xd3353638: {
        cTriggerRec* t = GetTrigger(eventID, (cTriggerOwner*)owner);
        if (t == 0)
            return false;
        if (t->mFlag_08 != 0) {
            u32 flags = *(u32*)((u8*)ev->mpObject_00 + 0xb58);
            if (((u8)(flags >> 9) & 1) == 0)
                return false;
        }
        return EvaluateTrigger(t, owner, ev->mpObject_00);
        }
    }
    return false;
}

// ===========================================================================
// @ 0x00d47630
// ===========================================================================
cTriggerRec* cCreatureTriggerSystem::GetTrigger(u32 eventType, cTriggerOwner* owner)
{
    if (owner == 0)
        return 0;

    u32 key = owner->mKey_24;
    u8* it = 0;
    mMap.Find(&it, &key);
    if (it != (u8*)mMap.mpBegin[mMap.mCount]) {
        cTrigNodeList* node = (cTrigNodeList*)it;
        cTriggerRec* p = node->mpBegin_08;
        cTriggerRec* e = node->mpEnd_0c;
        while (p != e) {
            if (p->mKind_0c == 0xa07dde8f)
                return p;
            if (p->mKind_0c == eventType)
                return p;
            p = (cTriggerRec*)((u8*)p + 0x2c);
        }
    }

    u32* array = 0;
    i32 count = 0;
    cNounManager* mgr = SP_NounManager();
    if (owner->mpObj_28 != 0) {
        void* v = ((cOwnerVirt20)owner->mVtbl_00[0x20 / 4])(owner, owner->mpObj_28);
        u8* r = (u8*)mgr->Find(v);
        if (r != 0 && *(void**)(r + 0x0c) != 0)
            GetPropertyAsUint32Array(*(void**)(r + 0x0c), 0x3d03b03, &count, &array);
    }
    if (array == 0 || count <= 0)
        return 0;

    cTriggerRec* result = 0;
    cTriggerRef* temp = 0;
    cPropertyManager* manager = SP_PropertyManager();
    cTrigFindCtx ctx;
    ctx.mKey_00 = owner->mKey_24;
    ctx.mZero_04 = 0;
    ctx.mpManager_08 = manager;
    cTriggersInfo* info = mMap.NewInfo(&ctx);

    cTriggerRef* old = info->mpOwner_00;
    if ((cTriggerRef*)owner != old) {
        ((cTriggerRef*)owner)->AddRef();
        info->mpOwner_00 = (cTriggerRef*)owner;
        if (old != 0)
            old->Release();
    }
    info->mFlag_17c = 0;

    for (i32 i = 0; i < count; i++) {
        u32 id = array[i];
        if (id == 0)
            continue;
        if (temp != 0) {
            cTriggerRef* dead = temp;
            temp = 0;
            dead->Release();
        }
        if (((cPropMgrVirt2c)manager->mVtbl_00[0x2c / 4])(manager, id, 0x3cddc79, &temp)) {
            info->mSlots.Append();
            cTriggerRec* slot = info->mSlots.mpEnd_04 - 1;
            cTriggerRef* prev = slot->mpRef_00;
            if (temp != prev) {
                if (temp != 0)
                    temp->AddRef();
                slot->mpRef_00 = temp;
                if (prev != 0)
                    prev->Release();
            }
            ReadTrigger(slot);
            info->mFlag_17c |= (slot->mKind_0c == 0x6ab2cd38);
            if (slot->mKind_0c == 0xa07dde8f || slot->mKind_0c == eventType)
                result = slot;
        }
    }

    if (temp != 0) {
        cTriggerRef* dead = temp;
        temp = 0;
        dead->Release();
    }
    return result;
}

// ---------------------------------------------------------------------------
// Creature-mode strategy: Init (0x00d47960) and the collectable roll (0x00d47ea0).
// ---------------------------------------------------------------------------
struct cCollectableItems {                      // big stack container built by 0x00598470
    cNodePool mPool;                            // +0x000
    u8        pad_34[0x888 - 0x34];             // +0x034
    void Ctor(u8* a, u8* b);                    // 0x00598470
    void Deinit(void* first, u32 count);        // 0x00597b30
};

struct cItemSource {                            // argA of FUN_00d47ea0
    u8   Init(cCollectableItems* obj, void* f, void* b);        // 0x00597f00
    u8   Commit(void* g, u32 lo, u32 hi, void* f);              // 0x005976d0
};

struct cRandomGlobal {                          // global object at 0x01601760
    f64 RandomDouble();                         // 0x009360d0
};

struct cAppObj {
    void** mVtbl_00;                            // +0x00
    void* V_50();                               // slot 0x50
};
struct cAppInterface {
    void** mVtbl_00;                            // +0x00
    void Reg_20(u32 msgId, void* handler);      // slot 0x20
};

void*       SP_App();                           // 0x0067dd10
void*       GetMessagingServer();               // 0x00883860
void        FUN_00d2a600();                     // 0x00d2a600 message handler
void        FUN_00d38f40();                     // 0x00d38f40 (ecx = this)
void*       operator_new(u32 size, const char* tag, i32 a, i32 b, i32 c, i32 d); // 0x00f473a0

struct cCreatureModeStrategy {
    u8   pad_00[0x200];                         // layout opaque in this slice
    u32 Init();                                                         // 0x00d47960
    u8  FUN_00d47ea0(void* a, void* b, f32 c, f32 d, void* e, void* f, void* g); // 0x00d47ea0
    void FUN_00d38f40();                                                // 0x00d38f40
    u64 FUN_00d3bfa0(void** out, u32 p2, u32 p3, void* p4);             // 0x00d3bfa0
};

// ===========================================================================
// @ 0x00d47960  (PARTIAL -- see partial.txt)
// ===========================================================================
u32 cCreatureModeStrategy::Init()
{
    // The original is dominated by inlined eastl template bodies
    // (sp_vector<AutoRefCount<cCreatureModeScenario>>::push_back plus its slow
    // path 0x00f14270, the 0x00d46610 fixed_hash_map constructor, AutoRefCount
    // add/release) and by six cCreatureModeScenario allocations.  Only the
    // outer operations are modelled here.
    cAppInterface* app = (cAppInterface*)((cAppObj*)SP_App())->V_50();
    app->Reg_20(0x2a7ecd6, (void*)&FUN_00d2a600);

    // message registration against EA::Messaging::GetServer()
    (void)GetMessagingServer();

    // six possible scenarios pushed into mPossibleScenarios (sizes and vtables)
    operator_new(0x38,   "Simulator", 0, 0, 0, 0);
    operator_new(8,      "Simulator", 0, 0, 0, 0);
    operator_new(0x65cc, "Simulator", 0, 0, 0, 0);
    operator_new(0x18,   "Simulator", 0, 0, 0, 0);
    operator_new(8,      "Simulator", 0, 0, 0, 0);
    operator_new(8,      "Simulator", 0, 0, 0, 0);

    // AppProperties (0x015fd918) slot 0x24 with property 0x64a44a8, followed by
    // cProperty::GetBool (0x0041e920) and GetPropertyAsKeyArray().
    // Finally the global 8-byte (key, value) filter list at 0x01583298 is seeded
    // with (0x887c91bb,0x32) (0x9d62e363,0x32) (0x91ca5e8c,0x32)
    // (0x228d8f36,0x32) (0xde8f240b,0x32) (0x7f466450,0x19) (0xa0325a4f,0x19).
    return 1;
}

// ===========================================================================
// @ 0x00d47ea0
// ===========================================================================
u8 cCreatureModeStrategy::FUN_00d47ea0(void* a, void* b, f32 c, f32 d, void* e, void* f, void* g)
{
    FUN_00d38f40();

    u8 flag = 0;
    cCollectableItems obj;
    obj.Ctor(&flag, &flag);
    cItemSource* source = (cItemSource*)a;
    source->Init(&obj, f, b);

    u8 result = 0;
    void* out = 0;
    u64 v;
    f64 rnd;

    rnd = ((cRandomGlobal*)0x1601760)->RandomDouble();
    if (c > (f32)rnd) {
        v = FUN_00d3bfa0(&out, 1, 1, f);
        if (v != (u64)-1) {
            result = source->Commit(g, (u32)v, (u32)(v >> 32), f);
            goto done;
        }
    }
    rnd = ((cRandomGlobal*)0x1601760)->RandomDouble();
    if (d > (f32)rnd) {
        v = FUN_00d3bfa0(&out, 0, (f == (void*)1) ? 2 : 1, f);
        if (v != (u64)-1) {
            result = source->Commit(g, (u32)v, (u32)(v >> 32), f);
            goto done;
        }
    }
    v = FUN_00d3bfa0(&out, 0, 2, f);
    if (v != (u64)-1) {
        result = source->Commit(g, (u32)v, (u32)(v >> 32), f);
        goto done;
    }
    v = FUN_00d3bfa0(&out, 0, 2, (void*)-1);
    if (v != (u64)-1)
        result = source->Commit(g, (u32)v, (u32)(v >> 32), f);

done:
    obj.Deinit(obj.mPool.mpTail, obj.mPool.mCount);
    u8* p = (u8*)obj.mPool.mpTail;
    obj.mPool.mField_0c = 0;
    if (obj.mPool.mCount > 1 && p != (u8*)obj.mPool.mpSentinel) {
        if (p >= obj.mPool.mpPoolLo && p < obj.mPool.mpPoolHi) {
            *(void**)p = obj.mPool.mpFreeHead;
            return result;
        }
        FUN_00f47380(p);
    }
    return result;
}