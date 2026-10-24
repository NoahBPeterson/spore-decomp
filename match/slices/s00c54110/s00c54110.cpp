// Slice s00c54110 - SP::cSPMissionFetch::HandleMessage (message handler of the fetch mission).
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// `this` is the IHandler subobject of the mission (mission = this - 0x34); fields are addressed from `this`.
#include "types.h"

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Key  { uint32_t a, b, c; };

extern Vec3 gDefaultPos;   // 0x016907c8
extern Key  gNullKey;      // 0x016907d4
extern wchar_t gEmptyWString[]; // 0x01667bac

// eastl::wstring, 16 bytes with the 4-byte allocator
struct WStr {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAlloc;
    WStr() { mpBegin = gEmptyWString; mpEnd = gEmptyWString; mpCapacity = gEmptyWString + 1; }
    void DeallocateSelf();            // 0x00933960
    ~WStr() { DeallocateSelf(); }
};

struct Msg { uint32_t f0; uint32_t f4; uint8_t* src; uint32_t fc; void* f10; uint32_t f14; uint32_t f18; };

struct PosProv {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual Vec3* GetPos();           // slot 0x2c
};

struct Mission {
    void  TriggerUIUpdate();                 // 0x00c47d80
    void* GetTargetPlanet();                 // 0x00970b30
    void* GetModel();                        // 0x00c45ce0
    void* GetOwnerEmpire();                  // 0x00c451e0
    void  GetText(uint32_t key, WStr* out);  // 0x00c487d0
    void  PostEvent(void* ev);               // 0x00c48e50
    void  FUN_00c5ed90(int a);               // 0x00c5ed90
    void  FUN_00c47180(void* planet);        // 0x00c47180
    void  Complete();                        // 0x00c52ea0
};
struct Avatar {
    void* SpawnArtifact(void* params);       // 0x00ff5d20
};
struct GameNounMgr {
    Avatar* GetAvatar();                     // 0x00b1fdb0
};
struct SpecimenMgr {
    void* Lookup(Msg* m);                    // 0x00b2b1e0
};
struct ArtItem {
    Key* GetKey(Key* out);                   // 0x00ad2620
};
struct PlantItem {
    Key* GetKey(Key* out);                   // 0x00c3e1e0
};
struct AnimItem {
    Key* GetKey();                           // 0x00c0bc00
};
struct VecP { uint8_t** b; uint8_t** e; };
struct NounMgr {
    VecP* GetAll();                          // 0x00ace2c0
};
struct EventLog {
    void* PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);  // 0x00dd8640
    void  ModifyEventText(void* ev, wchar_t* text);                               // 0x00dd6df0
};
struct CommMgr {
    void AddEntry(int empire, int ctx, int text, uint32_t key, void* obj, int a, int b); // 0x00aeb160
};
struct StarRec {
    int GetCommContext();                    // 0x00ce6950
};
struct Vec3Vec {
    void push_back(const Vec3* v);           // 0x004739d0
};

void*  __cdecl GetActivePlanet();                  // 0x01021260
GameNounMgr* __cdecl SpaceGameGet();               // 0x01002bd0
NounMgr* __cdecl GetNounManager();                 // 0x00b3d300
SpecimenMgr* __cdecl GetSpecimenMgr();             // 0x00b3d3b0
EventLog* __cdecl GetEventLog();                   // 0x00b3d3e0
CommMgr* __cdecl GetCommManager();                 // 0x00b3d4a0
bool   __cdecl KeyEq(const Key* a, const Key* b);  // 0x004eb930
bool   __cdecl KeyNe(const Key* a, const Key* b);  // 0x005f78f0
Vec3*  __cdecl FindVec3(Vec3* first, Vec3* last, const Vec3* v);  // 0x00c52d30
ArtItem*   __cdecl CastArt(void* p);               // 0x00c52220
PlantItem* __cdecl CastPlant(void* p);             // 0x00c52240
AnimItem*  __cdecl CastAnimal(void* p);            // 0x00c52260
AnimItem*  __cdecl CastAnimal2(void* p);           // 0x00c4bbe0
bool   __cdecl IsItemARare(Key* k);                // 0x0103a3c0

struct SpawnParams {
    uint32_t a; Key pos; uint16_t w; uint8_t b12; uint8_t pad; float f; uint32_t g[4]; uint8_t t28;
};

struct FetchHandler {
    void HandleMessage(uint32_t msg, Msg* m);
    void BaseHandleMessage(uint32_t msg, Msg* m);   // 0x00c4a6b0 cSPMission::HandleMessage

    template<class T> T& F(int off) { return *(T*)((char*)this + off); }
    Mission* Mis() { return (Mission*)((char*)this - 0x34); }
};

static inline int SlotId(Mission* mi) {
    return ((int(__thiscall*)(Mission*))(*(void***)mi)[0xa4 / 4])(mi);
}

// ---------------------------------------------------------------------------
// cSPMissionFetch: the mission object itself (no vfptr at 0; base cSPMission).
// ---------------------------------------------------------------------------
struct PropTable;
struct TerraMgr;
struct cSPMissionFetch;

// a quest property table (0x00ba7bd0 ctor / 0x00ba8220 dtor)
struct PickParams {
    uint32_t mType;              // +0x00
    uint32_t mEa;                // +0x04
    uint32_t mEb;                // +0x08
    uint8_t  mB0c;               // +0x0c
    uint8_t  mB0d;               // +0x0d
    uint8_t  mB0e;               // +0x0e
    uint8_t  mB0f;               // +0x0f
    uint32_t mCost;              // +0x10
    uint32_t mCost2;             // +0x14
    uint32_t mFlags;             // +0x18
    uint32_t mFlags2;            // +0x1c
    uint32_t mF20;               // +0x20
    uint32_t mF24;               // +0x24
    uint32_t mF28;               // +0x28
    uint32_t mF2c;               // +0x2c
    uint32_t mF30;               // +0x30
    uint32_t mPlanet;            // +0x34
    uint32_t mF38;               // +0x38
    uint32_t mF3c;               // +0x3c
    void Ctor();                 // 0x00ba7bd0
    void Dtor();                 // 0x00ba8220
};
struct SpeciesEntry {            // 0x10-byte vector element of +0x234
    uint8_t  mIsEditor;          // +0x00
    uint8_t  mPad01[3];
    Key      mKey;               // +0x04
    uint8_t  mPad10[0x10 - 0x04 - sizeof(Key)];
};

struct FetchMission {
    // ... [0x000, 0x078) omitted
    uint8_t  mPad000[0x78];
    uint32_t mSubtype;                       // +0x078
    uint8_t  mPad07c[0x180 - 0x7c];
    void*    mpPropTable;                    // +0x180
    uint8_t  mPad184[0x1bc - 0x184];
    int      mStateA;                        // +0x1bc
    uint32_t mSpeciesType;                   // +0x1c0
    uint32_t mFetchType;                     // +0x1c4
    uint8_t  mPad1c8[0x1f0 - 0x1c8];
    int      mValidateState;                 // +0x1f0
    uint32_t mType;                          // +0x1f4
    uint8_t  mPad1f8[0x210 - 0x1f8];
    Key      mKeyA;                          // +0x210
    Key      mKeyB;                          // +0x21c
    uint8_t  mPad228[0x234 - 0x228];
    SpeciesEntry* mpSpeciesBegin;            // +0x234
    SpeciesEntry* mpSpeciesEnd;              // +0x238

    void ValidateSpecies(Key* pKey);         // 0x00c54110
    bool Init();                             // 0x00c54380
    // cSPMission base helpers
    void SetState(int s);                    // 0x00c47cc0
    void FUN_00c48470(Key* pKey);            // 0x00c48470
    void FUN_00c53a90();                     // 0x00c53a90
    bool FUN_00c53bc0();                     // 0x00c53bc0
    bool InitBase();                         // 0x00c4ad50 cSPMission::Init
    void ReadDropOffFields();                // 0x00c52580
    uint32_t ReadTargetPlanetType();         // 0x00c45b40
    void* GetPlanetRecordFromTargetType(uint32_t t); // 0x00c474b0
    void FUN_00c47180(void* planet);         // 0x00c47180
    void* GetTargetPlanet();                 // 0x00970b30
    uint32_t ReadTargetAnimalSpeciesType(Key* out); // 0x00c45b60
    void GetAnimalSpeciesFromType(uint32_t t, Key* out); // 0x00c47610
    void* PickPlanet(PickParams* p);         // 0x00c47e20
    bool HasPickedFetchItem();               // 0x00c52930
    void FUN_00c45250(void* p);              // 0x00c45250
    void FUN_00c4a0c0();                     // 0x00c4a0c0
};

bool  __cdecl KeyEq3(const Key* a, const Key* b);      // 0x004eb930
void* __cdecl FUN_00401090();                          // 0x00401090 species mgr
void* __cdecl FUN_00b3d420();                          // 0x00b3d420 plant species mgr
struct SpeciesMgr { void* GetByKey(const Key* k); };   // 0x004df550 (editor) / 0x00b90410 (plant)
void  __cdecl FUN_00bc1b10(TerraMgr* mgr, void* planet, void* x, void* y); // 0x00bc1b10
void* __cdecl FUN_00b3d3d0(void* p);                   // 0x00b3d3d0
void  FUN_0103aa00(void* p);                           // 0x0103aa00 (thiscall)
void* __cdecl FUN_00c6acc0(void* noun);                // 0x00c6acc0 cNearNoun::GetPosition
void* __cdecl FUN_00c71e30(void* planet);              // 0x00c71e30
bool __cdecl GetPropertyAsKey(void* table, uint32_t id, int* out); // 0x006a1250
struct NounManager {
    void* GetDataVector(void* a, void* b, void* c, void* d, uint32_t e); // 0x00b21340
};
struct NearNoun {
    Vec3* GetPosition();                     // 0x00c6acc0
};
struct UFOPlayer {
    void* GetPlayerInventory();              // 0x00a1ad60
};
NounManager* __cdecl GetNounManager_();                // 0x00b3d300
UFOPlayer* __cdecl GetUFOSim();                        // 0x00ffbe50

// @ 0x00c54e50
bool FindNearestNoun(void* out, Key* pKey)
{
    void* v = GetNounManager_()->GetDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                           (void*)0x00accc30, (void*)0x00b1e500, 0x1be418e);
    float best = *(float*)0x0146e760;                // FLT_MAX
    int count = (*(int*)((char*)v + 8) - *(int*)((char*)v + 4)) >> 2;
    void* inv = GetUFOSim()->GetPlayerInventory();
    const float* invPos = (const float*)((char*)inv + 0x718);
    for (int i = 0; i < count; ++i) {
        NearNoun* noun = *(NearNoun**)(*(int*)((char*)v + 4) + i * 4);
        Key* k = (Key*)(*(int*)((char*)noun + 0xa4) + 0x504);
        if (k->a != pKey->a || k->b != pKey->b || k->c != pKey->c)
            continue;
        float* p = (float*)noun->GetPosition();
        float dy = p[1] - invPos[1];
        float dx = p[0] - invPos[0];
        float dz = p[2] - invPos[2];
        float d2 = dz * dz + dy * dy + dx * dx;
        if (best > d2) {
            best = d2;
            NearNoun* noun2 = *(NearNoun**)(*(int*)((char*)v + 4) + i * 4);
            float* p2 = (float*)noun2->GetPosition();
            *(Vec3*)out = *(Vec3*)p2;
        }
    }
    return best != *(float*)0x0146e760;
}

// @ 0x00c54110
void FetchMission::ValidateSpecies(Key* pKey)
{
    int i = 0;
    if (mValidateState != 0 && mValidateState != 1)
        goto done;

    switch ((int)mType) {
    case 0x2dc69129:
    case 0xfb3b1635:
    case 0x6d5c48c:
    case 0x3e994b2b:
    case 0x69412983:
    case 0x736c417f:
        goto alt;
    case (int)0x23da98ff: {
        int n = (int)((mpSpeciesEnd - mpSpeciesBegin));   // 0x238 - 0x234 >> 4
        int off = 0;
        for (i = 0; i < n; ++i) {
            char* e = (char*)mpSpeciesBegin + off;
            Key* k = (Key*)(e + 4);
            void* profile;
            if (*e != 0) {
                profile = ((SpeciesMgr*)FUN_00401090())->GetByKey(k);
            } else {
                profile = ((SpeciesMgr*)FUN_00b3d420())->GetByKey(k);
            }
            if (!profile)
                goto found;
            if (pKey != 0 && KeyEq3(pKey, k))
                goto found;
            off += 0x10;
        }
        FUN_00c48470(pKey);
        return;
    found:
        if (FUN_00c53bc0()) {
            mValidateState = 0;
            FUN_00c48470(pKey);
            return;
        }
        FUN_00c53a90();
        SetState(1);
        goto done;
    }
    default:
        goto done;
    }

alt:
    if (*(uint32_t*)&mKeyA != *(uint32_t*)0x016907d4 ||
        *(uint32_t*)((char*)&mKeyA + 4) != *(uint32_t*)0x016907d8 ||
        *(uint32_t*)((char*)&mKeyA + 8) != *(uint32_t*)0x016907dc) {
        if (((SpeciesMgr*)FUN_00b3d420())->GetByKey(&mKeyA) &&
            (pKey == 0 || !KeyEq3(pKey, &mKeyA))) {
            if (FUN_00c53bc0())
                mValidateState = 0;
            else {
                mKeyA = *(Key*)0x016907d4;
                SetState(1);
            }
        }
    }

    if (*(uint32_t*)&mKeyB != *(uint32_t*)0x016907d4 ||
        *(uint32_t*)((char*)&mKeyB + 4) != *(uint32_t*)0x016907d8 ||
        *(uint32_t*)((char*)&mKeyB + 8) != *(uint32_t*)0x016907dc) {
        if (((SpeciesMgr*)FUN_00401090())->GetByKey(&mKeyB) &&
            (pKey == 0 || !KeyEq3(pKey, &mKeyB)) &&
            FUN_00c53bc0()) {
            mValidateState = 0;
            FUN_00c48470(pKey);
            return;
        }
        mKeyB = *(Key*)0x016907d4;
        SetState(1);
    }

done:
    FUN_00c48470(pKey);
}

// @ 0x00c54380
typedef void (__thiscall *VFn0)(void* pThis);
typedef bool (__thiscall *VFnB)(void* pThis);
bool FetchMission::Init()
{
    int i = 0;
    if (!InitBase())
        return false;

    ((VFn0)(*(void***)this)[0x16c / 4])(this);

    int prop[3] = { 0, 0, 0 };
    if (GetPropertyAsKey(mpPropTable, 0xac10e58a, prop))
        mType = prop[0];

    ReadDropOffFields();
    uint32_t t = ReadTargetPlanetType();
    char one = 1;
    if (t == 0x2ca33bdb) {
        if (mSubtype != 0x809ab04a)
            goto after_pick;
        PickParams pp;
        pp.Ctor();
        pp.mType = 0x38;
        pp.mCost = 2;
        void* pl = PickPlanet(&pp);
        if (pl) {
            void* q = FUN_00b3d3d0(pl);
            FUN_0103aa00(q);
        }
        pp.Dtor();
    } else {
        void* rec = GetPlanetRecordFromTargetType(t);
        if (rec)
            FUN_00c47180(rec);
        if (mSubtype == 0xbb448992) {
            uint32_t sp = ReadTargetAnimalSpeciesType(&mKeyB);
            GetAnimalSpeciesFromType(sp, &mKeyB);
        }
        if (GetTargetPlanet() != 0)
            goto after_pick;

        PickParams pp;
        pp.Ctor();
        pp.mType = 0x38;
        uint32_t ft = mType;
        if ((int)ft > 0x2dc69129) {
            if ((int)ft > 0x736c417f) {
                if (ft == 0x7ecbe6f5)
                    pp.mType = 0x3c;
            } else {
                switch (ft) {
                case 0x736c417f: pp.mB0e = one; pp.mB0d = one; break;
                case 0x3e994b2b: pp.mCost = 0x10; pp.mCost2 = 0x10; break;
                case 0x69412983: pp.mCost = 0x20; pp.mCost2 = 0x20; break;
                default: break;
                }
            }
        } else if (ft == 0x2dc69129) {
            pp.mB0e = one;
        } else if ((int)ft > 0x6d5c48c) {
            if (ft == 0x19ec2c8b)
                pp.mType = 0x3c;
            else if (ft == 0x23da98ff) {
                pp.mB0e = one; pp.mB0d = one;
            }
        } else if (ft == 0x6d5c48c) {
            pp.mB0e = one; pp.mB0d = one;
        } else if (ft == 0xbfb44ccc) {
            pp.mCost = 0x20; pp.mCost2 = 0x20;
        } else if (ft == 0xfb3b1635) {
            pp.mCost = 4; pp.mCost2 = 4;
        }

        void* pl = PickPlanet(&pp);
        if (!pl) {
            pp.Dtor();
            return false;
        }
        FUN_00c47180(pl);
        void* tp = GetTargetPlanet();
        FUN_00bc1b10((TerraMgr*)FUN_00b3d3d0(tp), tp, 0, 0);
        pp.Dtor();
    }

after_pick:
    if (!HasPickedFetchItem() && !FUN_00c53bc0())
        return false;
    ((VFn0)(*(void***)this)[0x188 / 4])(this);
    if (!((VFnB)(*(void***)this)[0x128 / 4])(this))
        return false;
    if (mType == 0x69412983) {
        void* tp = GetTargetPlanet();
        FUN_00c45250(FUN_00c71e30(tp));
    }
    FUN_00c4a0c0();
    ((VFn0)(*(void***)this)[0x170 / 4])(this);
    return true;
}

// @ 0x00c545f0
void FetchHandler::HandleMessage(uint32_t msg, Msg* m)
{
    Key f12plant, f11art2, f11plant, f11art1, f11rare, f12art1, f12art2;
    switch (msg) {
    case 0x2489766: case 0x248976a:
        if (F<int>(0x1bc) != 0) break;
    ui_update:
        if (F<uint32_t>(0x44) == 0x809ab04a)
            Mis()->TriggerUIUpdate();
        break;
    case 0x248975f:
        if (F<uint32_t>(0x1c0) == 0x19ec2c8b) {
            if (F<int>(0x1bc) == 0) {
                Mission* mi = Mis();
                void* target = m->f10;
                if (mi->GetTargetPlanet() == target) {
                    Avatar* av = SpaceGameGet()->GetAvatar();
                    if (av) {
                        SpawnParams sp;
                        sp.a = F<uint32_t>(0x1c4);
                        sp.pos.a = F<uint32_t>(0x1d0);
                        sp.pos.b = F<uint32_t>(0x1d4);
                        sp.pos.c = F<uint32_t>(0x1d8);
                        sp.w = 1;
                        sp.g[1] = 0; sp.g[2] = 0; sp.g[3] = 0;
                        sp.t28 = 0x28;
                        sp.b12 = 5; sp.f = 0.0f;
                        sp.g[0] = 0;
                        void* obj = av->SpawnArtifact(&sp);
                        if (obj) {
                            F<Vec3>(0x1d0) = *((PosProv*)((char*)obj + 0x34))->GetPos();
                        } else {
                            F<Vec3>(0x1d0) = gDefaultPos;
                        }
                    }
                }
            }
            break;
        }
        goto ui_update;
    case 0x2e9977e:
        if (F<uint32_t>(0x1c0) == 0x6d5c48c) {
            uint8_t* src = m->src;
            if (src && m->f18 && m->f18 != 0x2ebcd6a6) {
                void* sp = GetSpecimenMgr()->Lookup(m);
                if (sp && KeyEq((Key*)sp, &F<Key>(0x1dc))) {
                    Vec3 pos = *(Vec3*)(src + 4);
                    Vec3* b = F<Vec3*>(0x21c);
                    Vec3* e = F<Vec3*>(0x220);
                    if (FindVec3(b, e, &pos) == e)
                        ((Vec3Vec*)&F<Vec3*>(0x21c))->push_back(&pos);
                }
            }
        }
        break;
    case 0x3029f12: {
        Mission* mi = Mis();
        void* model = mi->GetModel();
        if (GetActivePlanet() != model) break;
        if (!F<uint8_t>(0x214)) break;
        bool hasTarget = m->f10 != 0;
        uint8_t* src = m->src;
        if (!src) break;
        PosProv* pp;
        switch ((int)F<uint32_t>(0x1c0)) {
        case 0x3e994b2b: case 0x69412983: case (int)0xfb3b1635: {
            AnimItem* a = CastAnimal2(src);
            if (!a) goto done;
            if (!KeyEq(a->GetKey(), &F<Key>(0x1e8))) goto done;
            pp = (PosProv*)((char*)a + 0xc0);
            break;
        }
        case (int)0xbfb44ccc: {
            ArtItem* a = CastArt(src);
            if (!a) goto done;
            if (*(int*)((char*)a + 0x658) != 4) goto done;
            if (!KeyEq(a->GetKey(&f12art1), &F<Key>(0x1f4))) goto done;
            pp = (PosProv*)((char*)a + 0x34);
            break;
        }
        case 0x19ec2c8b: {
            ArtItem* a = CastArt(src);
            if (!a) goto done;
            if (!KeyEq(a->GetKey(&f12art2), &F<Key>(0x1c4))) goto done;
            pp = (PosProv*)((char*)a + 0x34);
            F<Vec3>(0x1d0) = *pp->GetPos();
            break;
        }
        case 0x2dc69129: case 0x6d5c48c: case 0x736c417f: {
            Key* kp = &F<Key>(0x1dc);
            if (KeyNe(kp, &gNullKey)) {
                PlantItem* a = CastPlant(src);
                if (!a) goto done;
                if (!KeyEq(a->GetKey(&f12plant), kp)) goto done;
                pp = (PosProv*)((char*)a + 0x34);
            } else {
                kp = &F<Key>(0x1e8);
                if (!KeyNe(kp, &gNullKey)) goto done;
                AnimItem* a = CastAnimal(src);
                if (!a) goto done;
                if (!KeyEq(a->GetKey(), kp)) goto done;
                pp = (PosProv*)((char*)a + 0xc0);
            }
            break;
        }
        default:
            goto done;
        }
        Vec3 pos = *pp->GetPos();
        if (!hasTarget) break;
        {
            float r = F<float>(0x218);
            float r2 = r * r;
            VecP* list = GetNounManager()->GetAll();
            for (uint8_t** it = list->b; it != list->e; ++it) {
                PosProv* o = (PosProv*)(*it + 0x120);
                Vec3* p = o->GetPos();
                float dz = p->z - pos.z, dy = p->y - pos.y, dx = p->x - pos.x;
                if (r2 > dz * dz + dy * dy + dx * dx) {
                    mi->Complete();
                    goto done;
                }
            }
        }
        {
            WStr text;
            mi->GetText(0x959d4317, &text);
            void* ev = GetEventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
            GetEventLog()->ModifyEventText(ev, text.mpBegin);
            mi->PostEvent(ev);
        }
        break;
    }
    case 0x3029f11: {
        Mission* mi = Mis();
        void* tp = mi->GetTargetPlanet();
        bool ok;
        if (tp == 0) {
            if (F<uint32_t>(0x1c0) != 0x7ecbe6f5) goto done;
            ArtItem* a = CastArt(m->src);
            if (!a) goto done;
            ok = IsItemARare(a->GetKey(&f11rare));
        } else {
            void* tp2 = mi->GetTargetPlanet();
            if (GetActivePlanet() != tp2) goto done;
            uint8_t* src = m->src;
            if (!src) goto done;
            switch ((int)F<uint32_t>(0x1c0)) {
            case 0x3e994b2b: case 0x69412983: case (int)0xfb3b1635: {
                AnimItem* a = CastAnimal2(src);
                if (!a) goto done;
                ok = KeyEq(a->GetKey(), &F<Key>(0x1e8));
                break;
            }
            case (int)0xbfb44ccc: {
                ArtItem* a = CastArt(src);
                if (!a) goto done;
                if (*(int*)((char*)a + 0x658) != 4) goto done;
                ok = KeyEq(a->GetKey(&f11art1), &F<Key>(0x1f4));
                break;
            }
            case 0x19ec2c8b: {
                ArtItem* a = CastArt(src);
                if (!a) goto done;
                if (!KeyEq(a->GetKey(&f11art2), &F<Key>(0x1c4))) goto done;
                F<Vec3>(0x1d0) = gDefaultPos;
                goto finish;
            }
            case 0x2dc69129: case 0x6d5c48c: case 0x736c417f: {
                if (KeyNe(&F<Key>(0x1dc), &gNullKey)) {
                    PlantItem* a = CastPlant(src);
                    if (!a) goto done;
                    ok = KeyEq(a->GetKey(&f11plant), &F<Key>(0x1dc));
                } else {
                    if (!KeyNe(&F<Key>(0x1e8), &gNullKey)) goto done;
                    AnimItem* a = CastAnimal(src);
                    if (!a) goto done;
                    ok = KeyEq(a->GetKey(), &F<Key>(0x1e8));
                }
                break;
            }
            default:
                goto done;
            }
        }
        if (!ok) break;
    finish:
        if (F<uint8_t>(0x214)) {
            if (F<uint32_t>(0x44) != 0xbb448992) break;
            if (F<int>(0x1bc) != 0) break;
            mi->FUN_00c5ed90(1);
            void* obj = F<void*>(0x148);
            if (!obj) obj = mi;
            int owner = *(int*)((char*)mi->GetModel() + 0x13c);
            int empire = *(int*)((char*)mi->GetOwnerEmpire() + 0x84);
            int text = SlotId(mi);
            int ctx = ((StarRec*)owner)->GetCommContext();
            GetCommManager()->AddEntry(empire, ctx, text, 0x932a66fe, obj, 0, 0);
        } else {
            void* pl = GetActivePlanet();
            if (pl) mi->FUN_00c47180(*(void**)((char*)pl + 0x13c));
            mi->Complete();
        }
        break;
    }
    }
done:
    BaseHandleMessage(msg, m);
}
