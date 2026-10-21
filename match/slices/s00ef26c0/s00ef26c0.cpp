// Slice s00ef26c0: the "ScenarioPlanet" play-mode flow of Spore's scenario/planet
// editor. A singleton flow object (0x15acc30) drives a small state machine that
// rebuilds the scene's cMWModel set from the planet model store and refreshes the
// scenario node, while a sibling play-mode object ticks the effects, creatures,
// movies and tutorial UI every frame. Also here: the global AutoRefCount<cMWModel>
// vector destructor, a noun sweep used to retire dead play-mode props, and the
// per-frame creature/posse tick.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint;

struct cModelWorld;
struct cMWModel;
struct cScenarioNode;
struct cGameNounManager;
struct PlanetFlow;
struct PlayMode;

// =============================================================== refcounting
// cMWModel carries a model-world pointer and an intrusive refcount at +0x40; the
// low bit of mFlags is a "release pending" marker cleared on AddRef.
struct cMWModel {
    cModelWorld* mpWorld;   // +0x00
    uint32_t     mFlags;    // +0x04
    uint8_t      pad08[0x3c];
    int32_t      mRefCount; // +0x40
    inline void AddRef() { mFlags &= 0xfffffffeu; mRefCount++; }
    inline void Release();
};

inline void cMWModel::Release()
{
    if (mRefCount > 1) {
        mRefCount--;
    } else {
        typedef void (__thiscall* DF)(void*, cMWModel*, int);
        DF f = (DF)*(void**)(*(char**)mpWorld + 0x170);
        f(mpWorld, this, (int)((mFlags >> 31) & 1));
    }
}

// AutoRefCount<cMWModel> is a 4-byte intrusive handle.
struct AutoRefCount { cMWModel* mpObject; };

// ---- eastl vector<AutoRefCount<cMWModel>> -----------------------------------
struct MWVec {
    AutoRefCount* mpBegin;      // +0x00
    AutoRefCount* mpEnd;        // +0x04
    AutoRefCount* mpCapacity;   // +0x08
    void reserve(uint32_t n);                                   // 0x4e0880
    void DoInsertValue(AutoRefCount* pos, AutoRefCount* value); // 0x423c40
};

// ---- eastl vector<uint8_t> (the pending-checklist bytes) --------------------
struct ByteVec {
    uint8_t* mpBegin;      // +0x00
    uint8_t* mpEnd;        // +0x04
    uint8_t* mpCapacity;   // +0x08
    void insertFill(uint8_t* pos, uint32_t count, const uint8_t* value); // 0x5151b0
};

// ---- local eastl vector<void*> used by the noun sweep -----------------------
struct PtrVec {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCapacity;   // +0x08
    void ctor(uint32_t n, const void* src);      // 0xb93c60
    void DoInsertValue(void** pos, void** value);// 0xedafd0
};

// =============================================================== node / store
struct cModelStore {
    uint8_t  pad0000[0x2c10];
    void*    mpBegin;      // +0x2c10
    void*    mpEnd;        // +0x2c14
    uint8_t  pad218[0x2c24 - 0x2c18];
    uint32_t mIndex;       // +0x2c24
    uint8_t  pad228[0x2c50 - 0x2c28];
    int32_t  mField2c50;   // +0x2c50
};

struct cScenarioNode {
    uint8_t       pad00[0x10];
    cModelStore*  mpStore;    // +0x10
    uint8_t       mField14;   // +0x14
    uint8_t       pad15[0x84 - 0x15];
    uint8_t       mField84;   // +0x84
    void    F3C2C0();                 // 0xf3c2c0
    uint8_t F40370();                 // 0xf40370
    void    F427C0();                 // 0xf427c0
    void    F3E3B0(int);              // 0xf3e3b0
    void    F3E6B0(int);              // 0xf3e6b0
    void    F45FD0(int, int, int);    // 0xf45fd0
    uint8_t FED5330(uint32_t);        // 0xed5330
    void    FED5400(uint32_t);        // 0xed5400
    void    FED6540(int);             // 0xed6540
};

// The singleton flow object at 0x15acc30.
struct PlanetFlow {
    uint8_t       mFlag;      // +0x00
    uint8_t       mFlag1;     // +0x01
    uint8_t       pad02[2];
    int32_t       mStage;     // +0x04
    uint8_t       pad08[8];
    uint32_t      mCounter;   // +0x10
    cScenarioNode* mpNode;    // +0x14
    ByteVec       mPending;   // +0x18
    uint8_t       pad24[0x74 - 0x24];
    MWVec         mModels;    // +0x74

    void RebuildModels();     // 0xef26c0
    void FillPending();       // 0xef2940
    void AdvanceStage();      // 0xef2a10
    void FEF0220();           // 0xef0220
    uint8_t FEF02A0();        // 0xef02a0
    void FEF1C40();           // 0xef1c40
};
#define GFLOW (*(PlanetFlow*)0x15acc30)

// ---- play-mode object (ticked every frame) ----------------------------------
struct PlayMode {
    uint8_t       pad00[0x14];
    void*         mpField14;    // +0x14
    void*         mpField18;    // +0x18
    uint8_t       pad1c[0x6c - 0x1c];
    void*         mpMovie6c;    // +0x6c
    void*         mpEffects;    // +0x70
    void*         mpScenario74; // +0x74
    void*         mpField78;    // +0x78
    uint8_t       pad7c[0xc8 - 0x7c];
    uint8_t       mVelBlob;     // +0xc8
    uint8_t       padc9[0xcc - 0xc9];
    int32_t       mMode;        // +0xcc
    void*         mpTutorials;  // +0xd4
    void*         mpMovieD8;    // +0xd8
    uint8_t       mFieldDC;     // +0xdc

    void TickBase(int ms);          // 0xef2f70
    void TickFull(int ms);          // 0xef2f90
    void Tick(float a, float b);    // 0xef2fe0
    void FEF0DE0(int);              // 0xef0de0
    void FEF0A70(int);              // 0xef0a70
    void FEF0EE0();                 // 0xef0ee0
};

// =============================================================== callees
typedef void   (__thiscall* PFN_v)(void*);
typedef void   (__thiscall* PFN_i)(void*, int);
typedef void*  (__thiscall* PFN_p)(void*);

void*   __cdecl SP_NounManager();                       // 0xb3d300
void*   __cdecl FUN_00b3d320();                         // 0xb3d320
void*   __cdecl FUN_00b3d230();                         // 0xb3d230
void*   __cdecl FUN_00b3d310();                         // 0xb3d310
void*   __cdecl FUN_00b3d4d0();                         // 0xb3d4d0
void*   __cdecl FUN_00b3d410();                         // 0xb3d410
void*   __cdecl FUN_00b3d4c0();                         // 0xb3d4c0
void*   __cdecl SP_GameTimeManager();                   // 0xb3d380
void*   __cdecl SP_PlanetModel();                       // 0xb3d350
void*   __cdecl FUN_0067dd50();                         // 0x67dd50
void*   __cdecl FUN_0067cab0();                         // 0x67cab0
void*   __cdecl FUN_00401010();                         // 0x401010
void*   __cdecl FUN_0067dd10();                         // 0x67dd10
void*   __cdecl FUN_0067dcc0();                         // 0x67dcc0 MessageServer
void*   __cdecl FUN_00eeca30(void* p);                  // 0xeeca30
uint32_t __cdecl FUN_00ef1990(void* first, void* last, void* self); // 0xef1990
void    __cdecl FUN_00ef0b80();                         // 0xef0b80
void    __cdecl FUN_00ef0570();                         // 0xef0570
void    __cdecl FUN_00ef8590();                         // 0xef8590
void    __cdecl FUN_00f3c1b0();                         // 0xf3c1b0
void    __cdecl FUN_00efe240(float);                    // 0xefe240
void    __cdecl FUN_00f0a440(float);                    // 0xf0a440
void    __cdecl FUN_00f0ac40(float);                    // 0xf0ac40
void    __cdecl FUN_00f204c0(float);                    // 0xf204c0
void    __cdecl FUN_00f24dc0(float);                    // 0xf24dc0
void    __cdecl FUN_00ecb690(float);                    // 0xecb690
void    __cdecl FUN_00f0c310(float);                    // 0xf0c310
void    __cdecl FUN_00f1faa0(int);                      // 0xf1faa0
void    __cdecl FUN_00829110(void* a0, void* a1, void* a2, void* a3, void* a4); // 0x829110
void    __cdecl FUN_00ef2b20(float);                    // 0xef2b20
void    __cdecl FUN_011e0744(void* pos, void* last, int n); // 0x11e0744
int     __cdecl FUN_008e7f80(void* self);               // 0x8e7f80
int     __cdecl FUN_00bcc800(void* self);               // 0xbcc800
void*   __cdecl FUN_00d539d0();                         // 0xd539d0
char*   __cdecl FUN_0041e920(void* p);                  // 0x41e920 Property::GetBool
void*   __cdecl FUN_005f4e10(void* first, void* last, void* out); // 0x5f4e10
void    __cdecl FUN_005f3680(void* first, void* last);  // 0x5f3680
void*   __cdecl FUN_00f47380(void* p);                  // 0xf47380 operator delete
void*   __cdecl FUN_00b60a50(void* a);                  // 0xb60a50
void*   __cdecl FUN_00b5cc20(void* a);                  // 0xb5cc20
uint32_t __cdecl FUN_00932e80(const char* s, uint32_t hash, int len); // 0x932e80
void*   __cdecl FUN_00805070();                         // 0x805070 GetLayoutManager

// game-noun vector returned by cGameNounManager::GetGameDataVector.
struct NounVec {
    uint32_t mUnk0;      // +0x00
    void**   mpBegin;    // +0x04
    void**   mpEnd;      // +0x08
    uint32_t mUnk0c;     // +0x0c
    void*    mField10;   // +0x10
};
struct cGameNounManager {
    void ProcessPending();                                          // 0xb22960
    NounVec* GetGameDataVector(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e); // 0xb21340
    void RemoveNoun(void* noun);                                    // 0xb225d0
};

// ---- property query object (0x15fd918) --------------------------------------
struct PropObj {
    virtual void q00(); virtual void q01(); virtual void q02(); virtual void q03();
    virtual void q04(); virtual void q05(); virtual void q06(); virtual void q07();
    virtual void q08();
    virtual uint8_t Query(uint32_t key, void** out);   // +0x24
};

// ---- misc leaf objects ------------------------------------------------------
struct Field18 { void F32440(int); };                    // 0xf32440
struct Bag     { void FBA3350(); };                      // 0xba3350
struct C801360 { void Show(); void Hide(); };            // 0x801360 / 0x801380
struct Movie6c { void F118E0(int); };                    // 0xf118e0
struct TutUI   { void Update(); };                       // 0xefbf00
struct MovieD8 { void Update(int); };                    // 0xf067b0
struct Scenario74 {
    void F3D7E0(int);     // 0xf3d7e0
    void F3D8A0();        // 0xf3d8a0
    void F45B50();        // 0xf45b50
};
struct VelBlob { void Set(float* v); };                  // 0xb2f870
struct PosseSim { void RemovePosseMember(void*, void*, void*); };  // 0xd53490
struct SimObj  { void Tick(); };                          // 0xc06f70
struct Combat  { void F924E0(float); };                   // 0xf924e0
struct Effects { void Tick(float dt); };                  // 0xebe3e0
struct PlanetModel { void ComputeContinents(); };         // 0xb87dc0
struct D3D410  { uint8_t F00E36FA0(); void F00E3E350(int, void*, int); };
struct LayoutMgr { uint8_t IsWorldVisible(uint32_t id); void F00810660(uint32_t, int); };
struct Hash30  { void Method30(uint32_t id); };           // 0x167ea54 vtable+0x30
struct TerrainCam { float* F00B10200(); };                // 0xb10200
struct Loco    { float* GetVelocity(); };                 // 0xd20610
struct ILoc    { void* GetLocation(); };                  // 0xa42730
struct GTM     { void DecPauseGate(uint32_t); };          // 0xb32250
struct B3D230  { void M2C(int); void M30(int); };
struct WorldVisHost { void UpdateWorldVisibility(int); };

// Scenario / planet editor helpers reached through the space manager.
struct SpaceMgr {
    uint8_t       pad00[0x14];
    cScenarioNode* mpNode;   // +0x14
    uint8_t       pad18[0x74 - 0x18];
    void*         mpStore74;  // +0x74
    uint8_t       pad78[0xcc - 0x78];
    int32_t       mMode;     // +0xcc
};
#define GMGR (*(SpaceMgr**)0x16c7aa4)

// message sent when a creature crosses the planet threshold
struct RCMsg {
    void*    mpVtbl;    // +0x00
    int      mRefCount; // +0x04
    float    mData[10]; // +0x08
    uint32_t mId;       // +0x30
    uint32_t pad34;     // +0x34
    uint32_t mRCFlags;  // +0x38
    void Destruct();                                       // 0x421cf0
};
struct IMsgServer {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04();
    virtual void Send(uint32_t id, void* msg, void* extra); // +0x14
};

// =============================================================== functions

// @ 0x00ef26c0
void PlanetFlow::RebuildModels()
{
    ((cGameNounManager*)SP_NounManager())->ProcessPending();

    uint8_t flag = 0;
    {
        PropObj* props = *(PropObj**)0x15fd918;
        if (props != 0) {
            void* out = 0;
            if (props->Query(0x50caab1u, &out) != 0 &&
                *(uint16_t*)((uint8_t*)out + 0x12) == 1) {
                flag = (uint8_t)*FUN_0041e920(out);
            }
        }
    }

    if (GMGR->mMode == 2 && flag != 0) {
        MWVec* v = &this->mModels;
        AutoRefCount* begin = v->mpBegin;
        AutoRefCount* end = v->mpEnd;
        void* p = FUN_005f4e10(end, end, begin);
        FUN_005f3680(p, end);
        int n = (int)((char*)end - (char*)begin);
        v->mpEnd = (AutoRefCount*)((char*)v->mpEnd + (-(n >> 2)) * 4);

        cModelStore* store = (cModelStore*)(*(void**)((uint8_t*)GMGR->mpStore74 + 0x10));
        void* start;
        if (store->mIndex < 0x3fffffffu)
            start = (uint8_t*)store->mpBegin + (uint32_t)store->mIndex * 0x238;
        else
            start = store->mpEnd;
        uint32_t cnt = FUN_00ef1990(start, store->mpEnd, this);
        v->reserve(cnt);

        void* it = start;
        void* vend = store->mpEnd;
        if (it != vend) {
            for (;;) {
                void* obj = FUN_00eeca30((uint8_t*)it + 4);
                if (obj != 0) {
                    void* model = ((PFN_p)*(void**)(*(char**)obj + 0xac))(obj);
                    if (model != 0) {
                        cMWModel* mod = (cMWModel*)model;
                        mod->AddRef();
                        AutoRefCount tmp; tmp.mpObject = mod;
                        if (v->mpEnd < v->mpCapacity) {
                            AutoRefCount* slot = v->mpEnd++;
                            if (slot != 0) { slot->mpObject = mod; mod->AddRef(); }
                        } else {
                            v->DoInsertValue(v->mpEnd, &tmp);
                        }
                        if (tmp.mpObject != 0)
                            tmp.mpObject->Release();
                    }
                }
                uint32_t f;
                do {
                    f = *(uint32_t*)it;
                    it = (uint8_t*)it + 0x238;
                } while (!(f & 0x40000000u) && *(int32_t*)it < 0);
                if (it == vend) break;
            }
        }

        this->mpNode->F45FD0(2, 0, 0);
    }

    ((PlanetModel*)SP_PlanetModel())->ComputeContinents();
    this->mpNode->F3C2C0();
    if (this->mpNode->mField14 != 0) {
        uint8_t r = this->mpNode->F40370();
        if (GMGR->mMode == 1) {
            this->mpNode->F427C0();
        } else if (GMGR->mMode == 2 && r == 0) {
            this->mpNode->F45FD0(2, 0, 0);
        }
    } else if (GMGR->mMode == 1) {
        this->mpNode->F427C0();
    }

    if (*(uint8_t*)0x15acb40 != 0) {
        cScenarioNode* node = this->mpNode;
        int32_t c = node->mpStore->mField2c50;
        if (c < 1) {
            if (c == 0) node->F3E3B0(1);
            node->mpStore->mField2c50 = 1;
            node->mField84 = 1;
        }
    }
    this->mpNode->F3E6B0(0);
}

// @ 0x00ef2940
void PlanetFlow::FillPending()
{
    ByteVec* v = &this->mPending;
    uint8_t* begin = v->mpBegin;
    uint8_t* end = v->mpEnd;
    if ((uint32_t)(end - begin) < 0x1c) {
        uint8_t value = 0;
        v->insertFill(end, 0x1c - (uint32_t)(end - begin), &value);
    } else {
        uint8_t* pos = begin + 0x1c;
        FUN_011e0744(pos, end, 0);
        v->mpEnd = end + (pos - end);
    }
    for (int i = 0; i <= 0x1b; ++i) {
        void* o = FUN_0067dd50();
        uint8_t r = ((uint8_t (__thiscall*)(void*, int, int))*(void**)(*(char**)o + 0x60))(o, i, 1);
        begin[i] = (uint8_t)(r & 1);
    }
    this->mFlag1 = 1;
}

// @ 0x00ef29c0
void GlobalMwVector_Clear()
{
    MWVec* v = (MWVec*)0x15acca4;
    AutoRefCount* begin = v->mpBegin;
    AutoRefCount* end = v->mpEnd;
    void* p = FUN_005f4e10(end, end, begin);
    FUN_005f3680(p, v->mpEnd);
    int n = -(int)(end - begin);
    v->mpEnd = (AutoRefCount*)((char*)v->mpEnd + n * 4);
}

// @ 0x00ef2a10
void PlanetFlow::AdvanceStage()
{
    switch (this->mStage) {
    case 0:
        if (this->mCounter == 0) {
            cScenarioNode* node = GMGR->mpNode;
            if (node != 0)
                this->mFlag = (node->FED5330(0x7eaf739u) == 0);
            else
                this->mFlag = 1;
            ((C801360*)FUN_0067cab0())->Show();
            this->mCounter = 1;
        }
        if ((this->mFlag != 0 && this->mCounter >= *(uint32_t*)0x15acd1c) ||
            this->mCounter > 0x1e) {
            this->FillPending();
            this->FEF0220();
            this->mStage++;
        }
        break;
    case 1: {
        void* o = FUN_00401010();
        int r = ((int (__thiscall*)(void*))*(void**)(*(char**)o + 0x28))(o);
        if (r == 0)
            this->mStage++;
        break;
    }
    case 2:
        if (this->FEF02A0() != 0) {
            this->FEF1C40();
            this->mStage++;
        }
        break;
    case 3: {
        this->RebuildModels();
        cScenarioNode* node = GMGR->mpNode;
        if (node != 0) {
            FUN_00ef0b80();
            node->FED5400(0x7eaf739u);
            ((C801360*)FUN_0067cab0())->Hide();
            this->mStage++;
        } else {
            this->mFlag = 1;
            ((C801360*)FUN_0067cab0())->Hide();
            this->mStage++;
        }
        break;
    }
    default:
        break;
    }
}

// @ 0x00ef2b20
void FUN_00ef2b20(float)
{
    cGameNounManager* m = (cGameNounManager*)SP_NounManager();
    NounVec* src = m->GetGameDataVector(0xcd7d10, 0xd3d420, 0xef2640, 0xb1e500, 0x70703b3);

    void*  local[8];
    void** begin = local;
    void** end = local;
    void** cap = local + 8;

    int n = (int)(src->mpEnd - src->mpBegin);
    for (int i = 0; i < n; ++i) {
        void* noun = src->mpBegin[i];
        if (noun == 0) continue;
        if (((uint8_t (__thiscall*)(void*))*(void**)(*(char**)noun + 0x2c))(noun) != 0) continue;
        if (FUN_00bcc800(noun) <= *(int32_t*)0x15acb44) continue;
        ((void (__thiscall*)(void*))*(void**)(*(char**)noun + 0))(noun);
        void* item = noun;
        if (end < cap) {
            void** slot = end++;
            if (slot != 0) {
                *slot = noun;
                ((void (__thiscall*)(void*))*(void**)(*(char**)noun + 0))(noun);
            }
        } else {
            ((void (__thiscall*)(void*, void**, void**))0xedafd0)(&begin, end, &item);
        }
        if (item != 0)
            ((void (__thiscall*)(void*))*(void**)(*(char**)item + 4))(item);
    }

    int cnt = (int)(end - begin);
    for (int i = 0; i < cnt; ++i)
        ((cGameNounManager*)SP_NounManager())->RemoveNoun(begin[i]);

    for (void** p = begin; p < end; ++p) {
        if (*p != 0)
            ((void (__thiscall*)(void*))*(void**)(*(char**)*p + 4))(*p);
    }
    if (begin != 0 && begin != local)
        FUN_00f47380(begin);
}

// @ 0x00ef2c70
void FUN_00ef2c70(int ms)
{
    if (((uint8_t*)SP_GameTimeManager())[0x48] & 1) return;
    float dt = (float)ms * 0.001f;

    cGameNounManager* m = (cGameNounManager*)SP_NounManager();
    NounVec* v = m->GetGameDataVector(0xcd7d10, 0xd3d420, 0xace0f0, 0xb1e500, 0x18eb45e);
    int n = (int)(v->mpEnd - v->mpBegin);
    for (int i = 0; i < n; ++i) {
        uint8_t* noun = (uint8_t*)v->mpBegin[i];
        uint8_t* combat = noun + 0x5a8;
        if (FUN_008e7f80(combat) != 2) {
            float* e58 = (float*)(noun + 0xe58);
            float* e5c = (float*)(noun + 0xe5c);
            float vel = *(float*)(*(uint8_t**)(noun + 0xb20) + 0x640) * dt + *e58;
            *e58 = vel;
            if (vel > *e5c) vel = *e5c;
            *e58 = vel;

            float local50 = *(float*)(*(uint8_t**)(noun + 0xb20) + 0x66c) * dt +
                            *(float*)(noun + 0x5e0);
            float f48 = ((float (__thiscall*)(void*))*(void**)(*(char**)combat + 0x58))(combat);
            if (local50 > f48) local50 = f48;

            void* loc = ((ILoc*)FUN_00b3d320())->GetLocation();
            if (loc == (void*)0x1654c10) {
                float d = local50 - *(float*)(noun + 0x5e0);
                if (d > 0.0f) {
                    RCMsg msg;
                    msg.mpVtbl = (void*)0x13eb844;
                    msg.mRefCount = 0;
                    msg.mRCFlags = 0;
                    msg.mId = 0x7c789f8;
                    msg.mData[0] = d;
                    ((IMsgServer*)FUN_0067dcc0())->Send(msg.mId, &msg, 0);
                    msg.Destruct();
                }
            }
            if (local50 != *(float*)(noun + 0x5e0))
                ((Combat*)combat)->F924E0(local50);
        }
        if (*(uint8_t*)(noun + 0xe68) != 0) {
            uint32_t t = *(uint32_t*)(noun + 0xe6c);
            if (t > (uint32_t)ms) {
                *(uint32_t*)(noun + 0xe6c) = t - (uint32_t)ms;
            } else {
                *(uint32_t*)(noun + 0xe6c) = 0;
                ((PosseSim*)FUN_00d539d0())->RemovePosseMember(0, 0, noun);
                *(uint8_t*)(noun + 0xe68) = 0;
                ((SimObj*)noun)->Tick();
            }
        }
    }
}

// @ 0xef2e90
void FUN_00ef2e90(int ms)
{
    if (((uint8_t*)SP_GameTimeManager())[0x48] & 1) return;
    cGameNounManager* m = (cGameNounManager*)SP_NounManager();
    NounVec* v = m->GetGameDataVector(0xcd7d10, 0xd3d420, 0xace0f0, 0xb1e500, 0x18eb45e);
    int n = (int)(v->mpEnd - v->mpBegin);

    PtrVec local;
    local.ctor((uint32_t)n, &v->mField10);
    FUN_00829110(&local, v->mpBegin, v->mpEnd, local.mpEnd, local.mpBegin);

    int cnt = (int)(local.mpEnd - local.mpBegin);
    for (int i = 0; i < cnt; ++i) {
        void* p = local.mpBegin[i];
        if (p != 0 && *((uint8_t*)p + 0x135) != 0)
            ((void (__thiscall*)(void*, int))*(void**)(*(char**)p + 0x60))(p, ms);
    }
    for (void** p = local.mpBegin; p < local.mpEnd; ++p) {
        if (*p != 0)
            ((void (__thiscall*)(void*))*(void**)(*(char**)*p + 4))(*p);
    }
    if (local.mpBegin != 0 && *((int*)local.mpBegin - 1) != 0)
        FUN_00f47380(local.mpBegin);
}

// @ 0xef2f70
void PlayMode::TickBase(int ms)
{
    FUN_00ef2e90(ms);
    ((Field18*)this->mpField18)->F32440(0);
}

// @ 0xef2f90
void PlayMode::TickFull(int ms)
{
    FUN_00ef2c70(ms);
    FUN_00ef2e90(ms);
    ((Bag*)FUN_00b3d4c0())->FBA3350();
    ((Field18*)this->mpField18)->F32440(0);
}

// @ 0xef2fe0
void PlayMode::Tick(float a, float b)
{
    (void)a;
    if (((uint8_t*)FUN_00b3d320())[0x28] != 0) return;

    if (*(int32_t*)0x15acc34 != 4) {
        if (*(int32_t*)0x15acc40 != 0)
            (*(int32_t*)0x15acc40)++;
        GFLOW.AdvanceStage();
        return;
    }

    if (this->mFieldDC != 0) {
        this->mFieldDC = 0;
        ((GTM*)SP_GameTimeManager())->DecPauseGate(0x4bf38a7u);
        if (((D3D410*)FUN_00b3d410())->F00E36FA0() != 0)
            ((D3D410*)FUN_00b3d410())->F00E3E350(0, (void*)0x1654c10, 1);
        LayoutMgr* lm = (LayoutMgr*)FUN_00805070();
        if (lm->IsWorldVisible(0x614de4cu) == 1)
            lm->F00810660(0x614de4cu, 0);
        if (this->mMode == 2)
            this->FEF0EE0();
        else
            this->FEF0A70(0);
        uint32_t hash = FUN_00932e80("ScenarioPlanet", 0x811c9dc5u, 1);
        ((Hash30*)*(void**)0x167ea54)->Method30(hash);
        return;
    }

    FUN_00ef0570();
    int ms = (int)(b * 1000.0f);
    ((B3D230*)FUN_00b3d230())->M2C(ms);

    if (this->mMode == 1) {
        *(uint8_t*)((uint8_t*)FUN_00b3d310() + 0x24) = 0;
        if (*(int32_t*)((uint8_t*)this->mpScenario74 + 0x18) == 0) {
            if (((uint8_t*)FUN_00b3d4d0())[0x2a] == 0) {
                void* app = FUN_0067dd10();
                void* x = ((PFN_p)*(void**)(*(char**)app + 0x50))(app);
                void* y = ((PFN_p)*(void**)(*(char**)x + 0x38))(x);
                void* d1 = FUN_00b5cc20(y);
                float* vel = ((TerrainCam*)d1)->F00B10200();
                ((VelBlob*)((uint8_t*)this + 0xc8))->Set(vel);
            }
            FUN_00efe240(b);
            ((Scenario74*)this->mpScenario74)->F3D7E0(this->mMode);
            if (this->mpField14 != 0)
                ((Scenario74*)this->mpField14)->F3D7E0(ms);
            ((Effects*)this->mpEffects)->Tick(b);
            this->TickBase(ms);
            FUN_00ecb690(b);
            FUN_00f0c310(b);
            FUN_00f3c1b0();
            if (this->mpTutorials != 0)
                ((TutUI*)this->mpTutorials)->Update();
            FUN_00ef8590();
            if (this->mpMovieD8 != 0)
                ((MovieD8*)this->mpMovieD8)->Update(ms);
            ((Scenario74*)this->mpScenario74)->F3D8A0();
        } else {
            ((Scenario74*)this->mpScenario74)->F45B50();
        }
    } else if (this->mMode == 2) {
        int e = *(int32_t*)((uint8_t*)this->mpField78 + 0x90);
        uint8_t bl = (e == 0 || e == 1) ? 0 : 1;
        *(uint8_t*)((uint8_t*)FUN_00b3d310() + 0x24) = bl;
        FUN_00f1faa0((int)(b * 1000.0f));
        this->FEF0DE0(ms);
        if (((uint8_t*)FUN_00b3d4d0())[0x2a] == 0) {
            void* app = FUN_0067dd10();
            void* x = ((PFN_p)*(void**)(*(char**)app + 0x50))(app);
            void* y = ((PFN_p)*(void**)(*(char**)x + 0x38))(x);
            void* lo = FUN_00b60a50(y);
            float* vel = ((Loco*)lo)->GetVelocity();
            ((VelBlob*)((uint8_t*)this + 0xc8))->Set(vel);
        }
        if (this->mpMovie6c != 0)
            ((Movie6c*)this->mpMovie6c)->F118E0(ms);
        this->TickFull(ms);
        ((Scenario74*)this->mpScenario74)->F3D7E0(this->mMode);
        FUN_00efe240(b);
        FUN_00f0a440(b);
        FUN_00f0ac40(b);
        FUN_00f204c0(b);
        FUN_00f24dc0(b);
        FUN_00ef2b20(b);
        if (this->mpTutorials != 0)
            ((TutUI*)this->mpTutorials)->Update();
        if (this->mpMovieD8 != 0)
            ((MovieD8*)this->mpMovieD8)->Update(ms);
    }

    ((B3D230*)FUN_00b3d230())->M30(ms);
    ((WorldVisHost*)FUN_00b3d230())->UpdateWorldVisibility(ms);
}
