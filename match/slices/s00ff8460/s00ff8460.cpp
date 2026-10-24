// Slice s00ff8460 -- SP simulation region (10 functions, 0x00ff8460-0x00ff9100).
// Flags: /O2 /MD /Gy /EHsc /TP

// ---------------------------------------------------------------- eastl pool
// eastl::fixed_pool_base (one pointer: the head of the free list).
struct FixedPoolBase {
    void* mpHead;                                  // +0x00
    void* mpUnk04;                                 // +0x04  (never written here)
    // eastl::fixed_pool_base::init @ 0x00921260 (__thiscall ret 0x14)
    void init(void* pBegin, unsigned nodeSize, unsigned nodeCount,
              unsigned alignment, unsigned flags);
};

// A pooled object whose two node regions are carved from one embedded buffer:
// a sentinel list head (prev/next) followed by the first pool's bookkeeping and
// the node buffer itself.
struct PooledRegion {
    void*         mPrev;        // +0x00  list sentinel
    void*         mNext;        // +0x04  list sentinel
    FixedPoolBase mPool;        // +0x08  embedded fixed pool
    void*         mFirst10;     // +0x10
    void*         mLast14;      // +0x14
    unsigned      mCount18;     // +0x18
    char          mNodes[1];    // +0x1c  node buffer (node stride 0xf0)

    PooledRegion* FUN_00ff8460();
};

// @ 0x00ff8460
PooledRegion* PooledRegion::FUN_00ff8460()
{
    FixedPoolBase tmp;
    tmp.mpHead = 0;
    tmp.init(&mNodes[0], 0xf0, 0x18, 4, 0);
    void* head = tmp.mpHead;

    mPrev = 0;
    mNext = 0;
    mPool.mpHead = 0;
    mPool.init(head, 0xf0, 0x18, 4, 0);
    mFirst10 = head;
    mLast14  = (char*)head + 0xf0;
    mCount18 = 0x18;

    mPrev = this;
    mNext = this;
    return this;
}

// ------------------------------------------------------------------ qsort
// introsort driver: bit-count of the element count picks the depth limit
// (quick_sort_impl<int*,int> @ 0x00ff8260), then a final insertion pass over
// the whole range, or over the tail past the first 0x70 bytes when large.
extern void quick_sort_impl(int a, int b, int depth);   // 0x00ff8260
extern void FUN_00ff5ba0(int a, int b);                 // 0x00ff5ba0
extern void FUN_00ff5be0(int a, int b);                 // 0x00ff5be0

// @ 0x00ff84f0
void FUN_00ff84f0(int a, int b)
{
    if (a == b)
        return;
    int n = (b - a) >> 2;
    int t = n;
    int bits = 0;
    for (; t != 0; t >>= 1)
        bits++;
    quick_sort_impl(a, b, bits * 2 - 2);
    if (n > 0x1c) {
        FUN_00ff5ba0(a, a + 0x70);
        FUN_00ff5be0(a + 0x70, b);
    } else {
        FUN_00ff5ba0(a, b);
    }
}

// ------------------------------------------------------- game-data iterators
// SP::NounManager @ 0x00b3d300 (returns the live cGameNounManager* in eax).
extern void* SP_NounManager(void);
// SP::cGameNounManager::GetGameDataVector @ 0x00b21340 (__thiscall ret 0x14):
// returns a pointer to the requested game-data list (begin at +0x04, end at +0x08).
struct GameDataRange {
    void** mpBegin;     // +0x00
    void** mpEnd;       // +0x04
};
struct GameDataList {
    void*         mpUnk0;   // +0x00
    GameDataRange mRange;   // +0x04
};
struct cGameNounManager {
    GameDataList* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);
};

typedef void (__fastcall *GameDataSlotFn)(void* self);

// @ 0x00ff9070
void FUN_00ff9070(void)
{
    cGameNounManager* mgr = (cGameNounManager*)SP_NounManager();
    GameDataList* v = mgr->GetGameDataVector((void*)0x00b21080, (void*)0x00d3d420,
                                             (void*)0x00b236c0, (void*)0x00b1e500,
                                             (void*)0x018c816a);
    GameDataRange* r = &v->mRange;
    void** it = r->mpBegin;
    if (it != r->mpEnd) {
        do {
            void* obj = *it;
            GameDataSlotFn f = *(GameDataSlotFn*)((char*)*(void**)obj + 0x40);
            f(obj);
            ++it;
        } while (it != r->mpEnd);
    }

    mgr = (cGameNounManager*)SP_NounManager();
    v = mgr->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                               (void*)0x00ad48b0, (void*)0x00b1e500,
                               (void*)0x018ebadc);
    r = &v->mRange;
    it = r->mpBegin;
    if (it != r->mpEnd) {
        do {
            void* obj = *it;
            GameDataSlotFn f = *(GameDataSlotFn*)((char*)*(void**)obj + 0x40);
            f(obj);
            ++it;
        } while (it != r->mpEnd);
    }
}

// ------------------------------------------------- SP::cSPSimPlanetHighLOD
// Retail layout; only the members touched by this slice's functions are named.
// RCObject is an intrusive refcounted object whose release is a vtable slot
// (+4 or +8 depending on the owning pointer).
struct RCObject {
    virtual void v00();      // +0x00  AddRef
    virtual void v04();      // +0x04  Release
    virtual void v08();      // +0x08  Release (variant)
    virtual void* v0c(int);   // +0x0c
};
struct SimListNode { SimListNode* mpNext; SimListNode* mpPrev; RCObject* mpObj; };   // 0x0c B  (pool list node)
struct SimPool34   {
    SimListNode mHead;        // +0x34  intrusive list sentinel
    unsigned    mData[0x46];  // +0x40  pool storage
    void Init();                               // 0x00ff8460
    void Destroy();                            // 0x00ff80b0
    SimListNode* AllocNode(const void* pData); // 0x00ff8100
    void PopFront();                           // 0x00ff8210
};
struct SimTimer170 {                                                       // 0x2c B
    unsigned mData[0x0b];
    void Init();                               // 0x00b63890
    void Destroy();                            // 0x00b638b0
};
struct SimTree1c0 {                                                          // +0x1c0..+0x1cc
    void* mpRoot;      // +0x1c0
    void* mpNode;      // +0x1c4  self-linked sentinel head
    void* mpPrev;      // +0x1c8
    void Destroy(void* pNode);          // 0x00d0c930
};
struct SimSub1e4   {
    unsigned mData[0x01];
    void Init();                               // 0x007cf5d0
    void Destroy();                            // 0x007cfa90
};

struct cSPSimPlanetHighLOD {
    void*         mpVtbl0;      // +0x00  primary vtable
    void*         mpUnk04;      // +0x04
    void*         mpVtbl8;      // +0x08  secondary (base-subobject) vtable
    void*         mPad0c;       // +0x0c
    unsigned      mFlag10;      // +0x10
    unsigned char mByte14;      // +0x14
    unsigned char mPad15[3];    // +0x15
    RCObject*     mpFx18;       // +0x18  release vtable+4
    RCObject*     mpFx1c;       // +0x1c  release vtable+4
    RCObject*     mpFx20;       // +0x20  release vtable+8
    void*         mPad24;       // +0x24
    RCObject*     mpFx28;       // +0x28  release vtable+8 (reset to null first)
    RCObject*     mpFx2c;       // +0x2c  release vtable+4
    RCObject*     mpFx30;       // +0x30  release vtable+4
    SimPool34     mPool34;      // +0x34
    unsigned char mByte158;     // +0x158
    unsigned char mPad159[3];   // +0x159
    float         mF15c;        // +0x15c
    float         mF160;        // +0x160
    float         mF164;        // +0x164
    void*         mPad168[2];   // +0x168
    SimTimer170   mTimer170;    // +0x170
    unsigned*     mpArray19c;   // +0x19c  heap array (delete[] when the preceding slot is non-zero)
    void*         mpUnk1a0;     // +0x1a0
    void*         mpUnk1a4;     // +0x1a4
    void*         mPad1a8[2];   // +0x1a8
    RCObject*     mpFx1b0;      // +0x1b0  release vtable+8
    unsigned char mByte1b4;     // +0x1b4
    unsigned char mPad1b5[3];   // +0x1b5
    void*         mpUnk1b8;     // +0x1b8
    RCObject*     mpFx1bc;      // +0x1bc  release vtable+4
    SimTree1c0    mTree1c0;     // +0x1c0
    void*         mpNode1cc;    // +0x1cc
    unsigned      mCount1d0;    // +0x1d0  sentinel node count (cleared as a dword)
    void*         mpUnk1d4;     // +0x1d4
    void*         mPad1d8;      // +0x1d8
    RCObject*     mpFx1dc;      // +0x1dc  release vtable+4
    unsigned char mByte1e0;     // +0x1e0
    unsigned char mPad1e1[3];   // +0x1e1
    SimSub1e4     mSub1e4;      // +0x1e4

    ~cSPSimPlanetHighLOD();
    void AddToList(const unsigned* pSrc, RCObject* pObj);              // 0x00ff88c0
    void SpawnRallyChargeup(void* pTarget, float* pPos);               // 0x00ff8e00
};

extern void op_delete_array(void* p);   // operator_delete_array 0x00f47380

// @ 0x00ff8780
cSPSimPlanetHighLOD::~cSPSimPlanetHighLOD()
{
    mpVtbl0 = (void*)0x01495000;
    mpVtbl8 = (void*)0x01494fdc;

    if (mpFx28) {
        RCObject* p = mpFx28;
        mpFx28 = 0;
        p->v08();
    }
    mSub1e4.Destroy();
    if (mpFx1dc) mpFx1dc->v04();
    mTree1c0.Destroy(mpNode1cc);
    if (mpFx1bc) mpFx1bc->v04();
    if (mpFx1b0) mpFx1b0->v08();
    if (mpArray19c && mpArray19c[-1] != 0)
        op_delete_array(mpArray19c);
    mTimer170.Destroy();
    mPool34.Destroy();
    if (mpFx30) mpFx30->v04();
    if (mpFx2c) mpFx2c->v04();
    if (mpFx28) mpFx28->v08();
    if (mpFx1c) mpFx1c->v04();
    if (mpFx18) mpFx18->v04();

    mpVtbl0 = (void*)0x013ec458;
    mpVtbl8 = (void*)0x013eb938;
}

extern void __fastcall BaseGonzagoSim_ctor(void* self);   // 0x00b5b6c0
extern RCObject* __fastcall Simulator_alloc(void* mem);   // 0x00ff54e0
extern void* __cdecl operator_new(unsigned size, const char* desc,
                                  int a, int b, int c, int d);   // 0x00f473a0

// @ 0x00ff8970
cSPSimPlanetHighLOD* __fastcall cSPSimPlanetHighLOD_ctor(cSPSimPlanetHighLOD* self)
{
    BaseGonzagoSim_ctor(self);

    self->mpVtbl0 = (void*)0x01495000;
    self->mpVtbl8 = (void*)0x01494fdc;
    self->mFlag10 = 1;
    self->mByte14 = 0;
    self->mpFx18 = 0;
    self->mpFx1c = 0;
    self->mpFx20 = 0;
    self->mpFx28 = 0;
    self->mpFx2c = 0;
    self->mpFx30 = 0;
    self->mPool34.Init();
    self->mByte158 = 0;
    self->mF15c = 1.0f;                  // 0x015b60e0
    self->mF160 = 0.0f;                  // 0x015b60e4
    self->mF164 = 0.0f;                  // 0x015b60e8
    self->mTimer170.Init();
    self->mpArray19c = 0;
    self->mpUnk1a0 = 0;
    self->mpUnk1a4 = 0;
    self->mpFx1b0 = 0;
    self->mByte1b4 = 0;
    self->mpUnk1b8 = 0;
    self->mpFx1bc = 0;
    self->mTree1c0.mpNode = &self->mTree1c0.mpNode;
    self->mTree1c0.mpPrev = &self->mTree1c0.mpNode;
    self->mpNode1cc = 0;
    self->mCount1d0 = 0;
    self->mpUnk1d4 = 0;
    self->mpFx1dc = 0;
    self->mByte1e0 = 0;
    self->mSub1e4.Init();

    void* mem = operator_new(0x28, "Simulator", 0, 0, 0, 0);
    RCObject* pNew = mem ? Simulator_alloc(mem) : 0;
    RCObject* pOld = self->mpFx28;
    if (pNew != pOld) {
        if (pNew) pNew->v04();
        self->mpFx28 = pNew;
        if (pOld) pOld->v08();
    }
    return self;
}

// @ 0x00ff88c0
void cSPSimPlanetHighLOD::AddToList(const unsigned* pSrc, RCObject* pObj)
{
    SimListNode* head = &mPool34.mHead;
    SimListNode* cur  = head->mpNext;
    if (cur != head) {
        unsigned count = 0;
        do {
            cur = cur->mpNext;
            ++count;
        } while (cur != head);
        if (count >= 10) {
            SimListNode* first = head->mpNext;
            if (first->mpObj != 0)
                first->mpObj->v0c(0);
            mPool34.PopFront();
        }
    }

    RCObject* hold = 0;
    if (pObj != 0) {
        pObj->v00();
        hold = pObj;
    }

    struct NodeData { RCObject* mpObj; unsigned mD0, mD1, mD2; } data;
    data.mpObj = hold;
    data.mD0 = pSrc[0];
    data.mD1 = pSrc[1];
    data.mD2 = pSrc[2];

    SimListNode* n = mPool34.AllocNode(&data);
    n->mpNext = head;
    n->mpPrev = head->mpPrev;
    head->mpPrev->mpNext = n;
    head->mpPrev = n;

    if (hold != 0)
        hold->v04();
}

/* ============ remaining functions: behavioural sketches (bookkept as partial) ============ */
extern void* __cdecl FUN_01021260();                       // 0x01021260  active planet
extern void* __cdecl FUN_01021240();                       // 0x01021240  SimulatorUniverse::instance
extern void* __cdecl FUN_01021300();                       // 0x01021300
extern void* __cdecl FUN_010666a0();                       // 0x010666a0
extern void* __cdecl FUN_01067e60(void* a);                // 0x01067e60
extern void  __cdecl FUN_010421c0(void* a, void* b);       // 0x010421c0
extern void  __cdecl FUN_01009a40(void* a);                // 0x01009a40
extern int   __cdecl FUN_00b8e040(void* a, int b);         // 0x00b8e040
extern void  __cdecl FUN_00ac9200(void* a);                // 0x00ac9200
extern void  __cdecl FUN_00acb810(void* a, void* b);       // 0x00acb810
extern void  __cdecl FUN_00c74a30(void* a);                // 0x00c74a30
extern void  __cdecl FUN_00c74860(void* a);                // 0x00c74860
extern void  __cdecl FUN_00f924e0(void* a, float f);       // 0x00f924e0
extern void  __cdecl FUN_00aea5d0(void* a, void* b);       // 0x00aea5d0
extern void  __cdecl FUN_00dd85c0(void* a, void* b);       // 0x00dd85c0
extern void* __cdecl SP_PropertyManager();                 // 0x0067de30
extern void* __cdecl SP_NounManager();                     // 0x00b3d300
extern void  __cdecl SP_GetPropertyAsKeyInstance(void* a, unsigned k, void* out);  // 0x006a12a0
extern void* __cdecl SP_CreateNoun(void* self, unsigned key);    // 0x00b20c60
extern void* __cdecl SP_QuaternionFromDirections(void* q, void* d, void* up);      // 0x00698180
extern float* __cdecl SP_GetPropertyAsFloat();             // 0x0041ea70
extern void* __cdecl SP_StarManager(void* a);              // 0x00b3d2a0
extern void* __cdecl SP_GetEmpireByID(void* sm);           // 0x00ba9370
extern void* __cdecl SP_GetStarRecords(void* sm);          // 0x00bb1080
extern void* __cdecl SP_GetStars(void* emp);               // 0x00c308d0
extern void* __cdecl SP_GetUFOKey(void* emp);              // 0x00c326b0
extern void* __cdecl SP_CreateUFO(int a, void* b, void* c);     // 0x0102acb0
extern void* __cdecl SP_SpaceGameGet(void* ufo);           // 0x01002bd0
extern void* __cdecl SP_GetSpaceCombatTuning();            // 0x01029940
extern void* __cdecl SP_EffectsManager();                  // 0x0067ddd0
extern void* __cdecl SP_GetSystemAT();                     // 0x00a206f0
extern int   __cdecl SP_FNVHash(const char* s, unsigned seed, int a);   // 0x00932e80
extern void* __cdecl SP_GetUFOSimulator();                 // 0x00ffbe50
extern void* __cdecl SP_GetPlayerInventory(void* sim);     // 0x00a1ad60
extern void  __cdecl SP_Matrix3Assign(void* m, void* src); // 0x0041cb40
extern void* __cdecl SP_Matrix3FromFacingAndUp(void* out, void* a, void* b);  // 0x0069b440
extern void* __cdecl SP_GetSetting9();                     // 0x00401090
extern void* __cdecl SP_GetAvatarProfile(void* a);         // 0x004df420
extern void* __cdecl SP_GetGameDataVector(void* self, unsigned a, void* b,
                                          void* c, void* d, void* e);   // 0x00b21340
extern void* __cdecl FUN_00bd9d70(void* a, int b);         // 0x00bd9d70
extern void* __cdecl SP_GetPlayerCivilization(void* self); // 0x00b25fb0
extern void* __cdecl SP_GetPlayerEmpireOrMinus1();         // 0x00b1f9d0
extern void  __cdecl SP_SetPlayerEmpire(void* a, void* b, int c, unsigned d, int e);
extern void  __cdecl SP_ReduceCitiesOnPlanet(void* self, void* city);   // 0x00bf4370
extern void* __cdecl SP_GetCivilization(void* city);       // 0x00bd9bf0
extern void* __cdecl FUN_00be8680(void* a, int b, int c, int d, int e,
                                  int f, int g, int h, int i, int j);   // 0x00be8680
extern void* __cdecl operator_new(unsigned size, const char* desc,
                                  int a, int b, int c, int d);   // 0x00f473a0
extern void* __cdecl GetPlayerEmpireIDFn();                // 0x01021090
extern unsigned g_placeEmbassy;                            // 0x016db738

// @ 0x00ff8560
// (partial) SP::CreateToolObject — behavioural sketch. Keyed tool lookup (PropertyManager
// 0x30608f0b, GetPropertyAsKeyInstance 0x4e3eca1, CreateNoun 0x4e3fab5), the per-noun
// vtable dispatch, the x87-normalized direction handed to SP::QuaternionFromDirections,
// and the trailing planet/terrain/editor hooks follow the 531-byte listing; the embedded
// vector-push helpers (0x00ac9200/0x00acb810) and the exact 0x54 stack frame are sketched.
void FUN_00ff8560(int param_1, float* param_2, unsigned param_3)
{
    void* pUniverse = FUN_01021260();
    int   taken     = (int)FUN_00b8e040(pUniverse, param_1) & 0xff;
    if (taken == 0)
        FUN_00ac9200(param_2);

    void* pm   = SP_PropertyManager();
    SP_GetPropertyAsKeyInstance(pm, 0x30608f0bu, param_2);
    void* tool = SP_CreateNoun(SP_NounManager(), 0x4e3fab5u);
    void* prop = tool ? ((RCObject*)tool)->v0c(0x4e3faaf) : 0;
    if (prop) {
        FUN_00c74a30(prop);
        FUN_00c74860(prop);
        FUN_00f924e0(prop, 0.0f);
    }
    void* q = 0;
    SP_QuaternionFromDirections(&q, param_2, 0);
    if ((unsigned)param_1 == g_placeEmbassy)
        SP_StarManager(0);
    FUN_010421c0(FUN_01067e60(FUN_010666a0()), 0);
}

// @ 0x00ff8ad0
// (partial) SP::cSPSimulatorSpaceGame::UpdateInterceptorUFO — behavioural sketch: gather the
// avatar's empire, read the rally-range property (Key 0x55e7dad, default 10.0f = 0x41200000),
// collect neighbouring civilizations, create `count` interceptor UFOs (SP::CreateUFO,
// store 0x2f = 8) wiring each to a harvested city, then fire the audio cues and release the
// temporary SPVector. The SIMD/x87 distance filter and the vector reallocation details are
// sketched rather than reproduced.
void FUN_00ff8ad0(void)
{
    void* self   = FUN_01021240();
    void* avatar = SP_StarManager(self);
    void* empire = SP_GetEmpireByID(SP_StarManager(avatar));
    if (empire == 0)
        return;

    float range = 10.0f;
    if (SP_GetSpaceCombatTuning() != 0) {
        float* pf = SP_GetPropertyAsFloat();
        if (pf) range = *pf;
    }

    void* stars = SP_GetStars(empire);
    SP_GetStarRecords(SP_StarManager(0));
    SP_GetPropertyAsKeyInstance(stars, 0x1601760u, 0);

    int count = 3;
    if (SP_GetSpaceCombatTuning() != 0) {
        float* pf = SP_GetPropertyAsFloat();
        if (pf) count = (int)*pf;
    }

    void* ufoKey = SP_GetUFOKey(empire);
    for (int i = 0; i < count; ++i) {
        void* ufo = SP_CreateUFO(8, 0, ufoKey);
        SP_SpaceGameGet(ufo);
        FUN_01009a40(ufo);
    }

    RCObject* audio = (RCObject*)SP_GetSystemAT();
    if (audio != 0) {
        audio->v0c(0x3475365);
        audio->v0c(0x3475381);
        audio->v0c((int)GetPlayerEmpireIDFn());
    }
    (void)range;
}

// @ 0x00ff8e00
// (partial) spawns the "SG_ufo_raider_rally_chargeup" effect through the EffectsManager
// (FNV hash seeded 0x811c9dc5), builds an orientation matrix (Matrix3::Assign,
// Matrix3FromFacingAndUp) from the player inventory owner's facing and the incoming target
// position, feeds it to the +0x1c0 list (0x00dd85c0), then stores the effect handle into
// mpFx18. The 0x88 stack frame and the temp matrix rows are sketched.
void cSPSimPlanetHighLOD::SpawnRallyChargeup(void* pTarget, float* pPos)
{
    void* fx     = SP_EffectsManager();
    unsigned hash = (unsigned)SP_FNVHash("SG_ufo_raider_rally_chargeup", 0x811c9dc5u, 1);
    RCObject* effect = (RCObject*)((RCObject*)fx)->v0c((int)hash);

    if (effect != 0) {
        void* sim = SP_GetUFOSimulator();
        void* inv = SP_GetPlayerInventory(sim);
        float pos[3];
        pos[0] = pPos[0];
        pos[1] = pPos[1];
        pos[2] = pPos[2];
        float mat[9];
        SP_Matrix3Assign(mat, pos);
        SP_Matrix3FromFacingAndUp(mat, pos, (void*)pTarget);
        FUN_00dd85c0(&this->mTree1c0, mat);
        this->mpFx18 = effect;
    }
}

// @ 0x00ff9100
// (partial) player-civilization city-hoist handler (ret 8). Reads the setting (0x00401090),
// the avatar profile, builds a noun game-data query, resolves the incoming city, ensures the
// player civilization exists (CreateNoun 0x18c816a / vtable+0xc key 0x901f1362 /
// GetPlayerEmpireOrMinus1), reduces the city on the planet, then constructs the cCivData /
// cCityData companion object and posts the message-server events. Sketched.
void* FUN_00ff9100(int arg0, void* arg1)
{
    void* setting = SP_GetSetting9();
    if (setting == 0)
        return 0;

    void* profile = SP_GetAvatarProfile(setting);
    void* nounVec = SP_GetGameDataVector(SP_NounManager(),
                                         0x18c43e8u, 0, 0, 0, 0);
    (void)profile; (void)nounVec;

    RCObject* city = (RCObject*)FUN_00bd9d70(arg1, 0);
    if (city == 0)
        return 0;

    RCObject* player = (RCObject*)SP_GetPlayerCivilization(SP_NounManager());
    if (player == 0) {
        RCObject* created = (RCObject*)SP_CreateNoun(SP_NounManager(), 0x18c816au);
        if (created)
            player = (RCObject*)created->v0c(0x901f1362);
        SP_SetPlayerEmpire(player, SP_GetPlayerEmpireOrMinus1(), 1, 0x53dbcf2u, 0);
    }

    SP_ReduceCitiesOnPlanet(player, city);

    RCObject* civil = (RCObject*)SP_GetCivilization(city);
    if (civil == 0)
        return city;

    void* mem = operator_new(0x50, "Simulator/cCivData", 0, 0, 0, 0);
    if (mem)
        FUN_00be8680(mem, 0, 0, 0, 1, 0, 0, 0, 1, 0);

    (void)arg0;
    return city;
}