// Slice s00da1330: 0x00da1330, start-up of a tribe-mode "community approach" helper object (retail class
// unnamed). Binds the community / two game objects, computes the approach direction from the leader to
// the target, lays out a 5-point marker fan (0x00f4 vertex array: leader-side points at -15/-22 along the
// direction, two points rotated by +-angle about the direction), starts the effect at +0x178, sends
// message 0x41638ca, derives the relationship mode (+0xec) from the relationship manager, and queues
// tribe-mode command ids 7 / 5 / 6 into the vector at +0x1e4.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"
#include <math.h>
#include <string.h>

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

Vec3* __cdecl RotateByQuat(Vec3* out, const Vec3* v, const Quat* q);    // 0x0059aed0

struct IRef { virtual void AddRef(); virtual void Release(); };

// position-carrying sub-object embedded at +0xc0 of the game objects
struct PosSub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual Vec3* GetPos();                       // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
    virtual float* GetRange();                    // +0x68: floats at +8 and +0x14
};

struct KeyedRef : IRef {
    virtual void v2(); virtual void SetParam(uint32_t id); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18();
    virtual uint32_t GetKey();                    // +0x4c
};

struct Entity : KeyedRef {
    char pad04[0xc0 - 4];
    PosSub sub;                                   // +0xc0
    char padC4[0xb20 - 0xc4];
    uint32_t levelId;                             // +0xb20
};

struct Community : KeyedRef {
    Entity* GetLeader();                          // 0x00c00650 (thiscall)
};

struct Object2 : KeyedRef {                       // object bound at +0xc; its +0x2cc float is cleared at the end
    char pad04[0x2cc - 4];
    float f2cc;
};

struct Strategy;
struct StrategyObj { char pad[0x50]; IRef* held; };     // field at +0x50
struct Strategy {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26();
    virtual StrategyObj* GetObj();                // +0x6c
    bool Has(int id);                             // 0x00cd6ef0 (thiscall, ret 4)
    static Strategy* __cdecl Instance();          // 0x00cd40b0
};

struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void Post(void* sender, uint32_t msg);   // +0x24
};
IMessageServer* __cdecl MessageServer();             // 0x0067dcc0

struct RelationshipManager {
    float Score(uint32_t a, uint32_t b, int c);      // 0x00d00a10 (thiscall, ret 0xc)
    int Classify(float score);                       // 0x00d00780 (thiscall, ret 4)
};
RelationshipManager* __cdecl GetRelationshipManager();   // 0x00b3d2c0

struct LevelTable {
    float Value(uint32_t id);                        // 0x00ce6a40 (thiscall, ret 4)
};
extern LevelTable g_levelTable;                      // global instance, address 0x01581208

struct Effect {                                      // object embedded at +0x178
    void Init(const Vec3* pos, float f, const Vec3* dir, float g);   // 0x00af9cf0 (thiscall, ret 0x10)
    void SetMode(int mode, float v);                                 // 0x00afef10 (thiscall, ret 8)
};
void __cdecl EffectStart(Effect* e);                 // 0x00d9aa20 (cdecl)

struct MarkerRef : IRef {
    void Reset();                                    // 0x00e31550 (thiscall)
    void SetMode(int mode);                          // 0x00e311b0 (thiscall, ret 4)
};

struct IntVec {                                      // eastl::vector<int> at +0x1e4
    int* mpBegin; int* mpEnd; int* mpCapacity;
    void DoInsertValue(int* pos, const int& v);      // 0x00cd0550 (thiscall, ret 8)
    void push_back(const int& v)
    {
        if (mpEnd < mpCapacity) {
            int* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

extern float g_markerAngle;      // 0x01593470
extern uint32_t g_vtxInit[3];    // 0x0169f32c

template <class T> static inline void AssignRef(T*& slot, T* v)
{
    T* old = slot;
    if (v != old) {
        if (v)
            v->AddRef();
        slot = v;
        if (old)
            old->Release();
    }
}

struct CommunityApproach {
    char pad00[8];
    Community* mCommunity;       // +0x08
    Object2* mObj2;              // +0x0c
    Vec3 mTarget;                // +0x10
    Vec3 mDir;                   // +0x1c
    Vec3 mAim;                   // +0x28
    char pad34[0x5c - 0x34];
    float mSavedF;               // +0x5c
    char pad60[0xe4 - 0x60];
    Entity* mEntity;             // +0xe4
    MarkerRef* mMarker;          // +0xe8
    int mMode;                   // +0xec
    char padF0[0xf4 - 0xf0];
    Vec3* mVerts;                // +0xf4
    char padF8[0x150 - 0xf8];
    uint32_t* mZeroes;           // +0x150
    char pad154[0x178 - 0x154];
    Effect mEffect;              // +0x178
    char padE[0x1e4 - 0x178 - 4];
    IntVec mCommands;            // +0x1e4

    void Start(Community* comm, Object2* o2, Entity* ent, Entity* other);   // 0x00da1330
};

// @ 0x00da1330
void CommunityApproach::Start(Community* comm, Object2* o2, Entity* ent, Entity* other)
{
    AssignRef<Community>(mCommunity, comm);
    AssignRef<Object2>(mObj2, o2);
    AssignRef<Entity>(mEntity, ent);

    Vec3* ep = ent->sub.GetPos();
    mTarget = *ep;

    Entity* leader = comm->GetLeader();
    Vec3* lp = leader->sub.GetPos();
    Vec3 d;
    d.x = mTarget.x - lp->x;
    d.z = mTarget.z - lp->z;
    d.y = mTarget.y - lp->y;
    float inv = 1.0f / sqrtf(d.y * d.y + (d.z * d.z + d.x * d.x) + 1e-8f);
    Vec3* dir = &mDir;
    dir->x = inv * d.x;
    dir->y = d.y * inv;
    dir->z = d.z * inv;

    float a = g_levelTable.Value(other->levelId);
    float b = g_levelTable.Value(ent->levelId);
    float r = (a > b) ? a : b;

    Vec3* v = mVerts;
    ((uint32_t*)v)[0] = g_vtxInit[0];
    ((uint32_t*)v)[1] = g_vtxInit[1];
    ((uint32_t*)v)[2] = g_vtxInit[2];

    float len1 = r * 2.0f + 15.0f;
    float len2 = r * 2.0f + 22.0f;
    v = mVerts;
    v[1].y = mTarget.y - mDir.y * len1;
    v[1].x = mTarget.x - mDir.x * len1;
    v[1].z = mTarget.z - mDir.z * len1;
    v = mVerts;
    v[4].x = mTarget.x - mDir.x * len2;
    v[4].z = mTarget.z - mDir.z * len2;
    v[4].y = mTarget.y - mDir.y * len2;

    Vec3 rot;
    Quat q;
    float s, c;
    {
        float qi = 1.0f / sqrtf(mTarget.x * mTarget.x + mTarget.y * mTarget.y + mTarget.z * mTarget.z + 1e-8f);
        s = sinf(g_markerAngle * 0.5f);
        q.x = mTarget.x * qi * s;
        q.y = mTarget.y * qi * s;
        q.z = mTarget.z * qi * s;
        c = cosf(g_markerAngle * 0.5f);
        q.w = c;
        Vec3* rv = RotateByQuat(&rot, &mDir, &q);
        float rx = rv->x, ry = rv->y, rz = rv->z;
        v = mVerts;
        v[2].y = mTarget.y - ry * len1;
        v[2].z = mTarget.z - rz * len1;
        v[2].x = mTarget.x - rx * len1;
    }
    {
        float qi = 1.0f / sqrtf(mTarget.x * mTarget.x + mTarget.y * mTarget.y + mTarget.z * mTarget.z + 1e-8f);
        s = sinf(-g_markerAngle * 0.5f);
        c = cosf(-g_markerAngle * 0.5f);
        q.x = mTarget.x * qi * s;
        q.y = mTarget.y * qi * s;
        q.z = mTarget.z * qi * s;
        q.w = c;
        Vec3* rv = RotateByQuat(&rot, &mDir, &q);
        float rx = rv->x, ry = rv->y, rz = rv->z;
        v = mVerts;
        v[3].x = mTarget.x - rx * len1;
        v[3].y = mTarget.y - ry * len1;
        v[3].z = mTarget.z - rz * len1;
    }

    v = mVerts;
    v[5] = mTarget;

    mZeroes[0] = 0;
    mZeroes[1] = 0;
    mZeroes[2] = 0;
    mZeroes[3] = 0;
    mZeroes[4] = 0;

    Vec3 mid;
    mid.x = mTarget.x - (mDir.x * len1) * 0.5f;
    mid.y = mTarget.y - (mDir.y * len1) * 0.5f;
    mid.z = mTarget.z - (mDir.z * len1) * 0.5f;
    mEffect.Init(&mid, 45.0f, &mDir, 0.0f);
    mEffect.SetMode(0, r * 1.5f);
    EffectStart(&mEffect);

    MessageServer()->Post(this, 0x41638ca);

    RelationshipManager* rm = GetRelationshipManager();
    uint32_t k1 = comm->GetKey();
    uint32_t k2 = o2->GetKey();
    float score = rm->Score(k2, k1, 0);
    int rel = rm->Classify(score);
    if (rel == 2)
        mMode = 1;
    else if (rel == 3)
        mMode = 2;
    else
        mMode = 0;

    if (mMode != 0) {
        StrategyObj* so = Strategy::Instance()->GetObj();
        MarkerRef* nm = (MarkerRef*)so->held;
        MarkerRef* om = mMarker;
        if (nm != om) {
            if (nm)
                nm->AddRef();
            mMarker = nm;
            if (om)
                om->Release();
        }
        mMarker->Reset();
        float* range = ent->sub.GetRange();
        float dd = range[5] - range[2];
        float qi = 1.0f / sqrtf(mTarget.x * mTarget.x + mTarget.y * mTarget.y + mTarget.z * mTarget.z + 1e-8f);
        mAim.x = (qi * mTarget.x) * dd + mTarget.x;
        mAim.y = mTarget.y + (qi * mTarget.y) * dd;
        mAim.z = mTarget.z + (qi * mTarget.z) * dd;
        mMarker->SetMode(rel);
    }

    if (Strategy::Instance()->Has(6)) {
        const int val = 7;
        mCommands.push_back(val);
    }
    if (Strategy::Instance()->Has(4)) {
        const int val = 5;
        mCommands.push_back(val);
    }
    if (Strategy::Instance()->Has(5)) {
        const int val = 6;
        mCommands.push_back(val);
    }

    mSavedF = mObj2->f2cc;
    mObj2->f2cc = 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00da1b00 .. 0x00da1fc0: tribe "social band" reaction object (retail class unnamed).
// The band keeps two reference-counted creature lists (+0x64, +0x78), one ref list at
// +0x8c, a command-id vector at +0x1e4 and the reaction state in +0x04/+0x44..+0x60.

struct Creature;
struct OrderNode;

struct AutoRefCount {                                  // 4-byte ref-counted handle (AutoRefCount)
    Entity* mpObj;
    AutoRefCount(Entity* o) : mpObj(o) { if (o) o->AddRef(); }
    AutoRefCount(const AutoRefCount& o) : mpObj(o.mpObj) { if (mpObj) mpObj->AddRef(); }
    ~AutoRefCount() { if (mpObj) mpObj->Release(); }
};

struct RefVec {                                        // SPVector<AutoRefCount>
    AutoRefCount* mpBegin;                             // +0x00
    AutoRefCount* mpEnd;                               // +0x04
    AutoRefCount* mpCapacity;                          // +0x08
    void DoInsertPtr(AutoRefCount* pos, const AutoRefCount& v);   // 0x00aea5d0 (thiscall, ret 8)

    void push_back(const AutoRefCount& v)
    {
        AutoRefCount* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p) {
                Entity* o = v.mpObj;
                p->mpObj = o;
                if (o)
                    o->AddRef();
            }
        } else {
            DoInsertPtr(p, v);
        }
    }
};

// Appends a creature to a reference list; the temporary ref dies right after the insert.
__forceinline void PushCreature(RefVec& list, Entity* e)
{
    AutoRefCount ref(e);
    list.push_back(ref);
}

struct RefToSkin {                                     // EA::AutoRefCount<...>, out-of-line ctor
    Entity* mpObj;
    RefToSkin(Entity* o);                              // 0x00572660 (thiscall, ret 4)
    ~RefToSkin() { if (mpObj) mpObj->Release(); }
};

struct SkinVec {                                       // vector at +0x8c
    void* mpBegin; void* mpEnd; void* mpCapacity;
    void Insert(const RefToSkin& v);                   // 0x00e26c40 (thiscall, ret 4)
};

struct TribeSlot {                                     // 0xac-byte slot of the +0xb4c holder
    char pad00[4];
    int mState;                                        // +0x04
    char pad08[4];
    IRef* mObj;                                        // +0x0c
    uint8_t mFlag10;                                   // +0x10
};

struct Anim {                                          // sub-object at +8 of the +0xb4c holder
    void* Play(int a, uint32_t flags);                 // 0x00bc96a0 (thiscall, ret 8)
    void PlayWait(int a, uint32_t flags, float f, int b);   // 0x00bc97f0 (thiscall, ret 0x10)
};

struct TribeHolder {                                   // creature +0xb4c
    char pad00[8];
    Anim anim;                                         // +0x08
    char pad0c[0x1d0 - 0x0c];
    TribeSlot mSlots[1];                               // +0x1d0 (slot i lives at &mSlots[0] + i*0xac - 0x70)
    int mIndex;                                        // +0x1dc
    void Close();                                      // 0x00b45410 (thiscall)
    void FUN_00bcb480(OrderNode* n, Creature* c, void* r, void* fn);   // 0x00bcb480 (ret 0x10)
};

__forceinline TribeSlot* TribeSlotAt(TribeHolder* h, int i)
{
    return (TribeSlot*)((char*)&h->mSlots[0] + i * 0xac - 0x70);
}

struct Creature : Entity {
    char padB24[0xb4c - 0xb24];
    TribeHolder* mTribe;                               // +0xb4c
    char padB50[0xb58 - 0xb50];
    uint32_t mFlags;                                   // +0xb58
    uint32_t GetTribe();                               // 0x00c22f50 (thiscall)
    void UpdateLocomotion(int on);                     // 0x00c14750 (thiscall, ret 4)
    int FUN_00c22dc0();                                // 0x00c22dc0 (thiscall)
    void FUN_00c0b2f0(int anim, void* obj, int* out);  // 0x00c0b2f0 (thiscall, ret 0xc)
    int InterruptAnimation(int anim, int a, int b);    // 0x00c12310 (thiscall, ret 0xc)
    void FUN_00c1d460(uint32_t a, uint32_t b);         // 0x00c1d460 (thiscall, ret 8)
};
Creature* __cdecl FUN_00c0c380(Entity* e);             // 0x00c0c380

TribeHolder* __stdcall FUN_00b3d310(PosSub* sub);      // 0x00b3d310 (stdcall, 1 arg)
void* __cdecl Fun_00b45410(TribeHolder* h);            // 0x00b45410

struct Owner {                                         // object at band +0x0c
    char pad00[0x550];
    void* mBandInfo;                                   // +0x550
};

struct Msg {                                           // audio EAPD message
    uint32_t GetType();                                // 0x00fcc210 (thiscall)
    bool GetNextFloat(float* out);                     // 0x00a34e30 (thiscall, ret 4)
};

struct MsgSink { void Close(); };                      // 0x0067c830 (thiscall)
MsgSink* __cdecl FUN_0067cac0(uint32_t id);            // 0x0067cac0

struct Random {
    uint32_t RandomUint32Uniform(uint32_t n);          // 0x00a68fb0 (thiscall, ret 4)
};
extern Random g_random;                                // 0x01601760

struct SocialBand;                                     // band object returned by the pool
struct SocialBandPool {
    void* GetObject(uint32_t id);                      // 0x00d9eb70 (thiscall, ret 4)
};
extern SocialBandPool g_socialBandPool;                // 0x015935a8

struct BandKey { uint32_t mTribe1, mTribe2; Vec3 mPos; };
struct OrderNode { char pad00[0x1a8]; uint32_t mBandId; };
struct OrderManager {
    OrderNode* FindNode(uint32_t id, void* fn, void* ctx);          // 0x00bca620 (thiscall, ret 0xc)
};
OrderManager* __cdecl FUN_00bc9b00(uint32_t id, void* fn, void* ctx);   // 0x00bc9b00
void* __cdecl SP_FindSocialBandGroup(BandKey* key);                     // 0x00d9f0a0 (address used only)
void* __cdecl WatchMemoryBlock(void* block);                            // 0x00d999d0
Creature* __cdecl FUN_00d994c0(void* block);                            // 0x00d994c0

struct ReactResult {
    uint32_t f0, f1, f2, f3;
};
struct ReactRunner {
    void FUN_00d9d100(Creature* c, void* band);        // 0x00d9d100 (thiscall, ret 8)
};

extern const float kFloatMax;                          // 0x0147c190
extern const float kSmallEpsilon;                      // 0x0147c194
extern const float g_reactionTimer;                    // 0x0158132c

float __cdecl RandomInRange(const float* range);       // 0x004df2d0
void __cdecl FUN_00d9b480();                           // 0x00d9b480 (address used only)
void* __cdecl FUN_00c8ea70(void* info);                // 0x00c8ea70
void __cdecl FUN_00e26de0(void* begin, void* end, void* fn);   // 0x00e26de0

struct SocialBand {
    char pad00[4];
    int mState04;                                      // +0x04 (6 = done)
    char pad08[4];
    Owner* mOwner;                                     // +0x0c
    char pad10[0x44 - 0x10];
    uint32_t mCount;                                   // +0x44
    uint32_t mLimit;                                   // +0x48
    float mDelay;                                      // +0x4c
    char pad50[1];
    uint8_t mFlag51;                                   // +0x51
    char pad52[2];
    float mTimer;                                      // +0x54
    uint8_t mFlag58;                                   // +0x58
    char pad59[0x60 - 0x59];
    uint32_t mHandle;                                  // +0x60
    RefVec mListA;                                     // +0x64
    char pad70[0x78 - 0x70];
    RefVec mListB;                                     // +0x78
    char pad84[0x8c - 0x84];
    SkinVec mSkins;                                    // +0x8c
    char pad98[0x1dc - 0x98];
    int mMode;                                         // +0x1dc
    uint32_t mChosen;                                  // +0x1e0
    IntVec mCommands;                                  // +0x1e4

    void AddCreature(Creature* e);                     // 0x00da1b00
    void AddOther(Creature* e);                        // 0x00da1b90
    bool OnMessage(uint32_t msg, Msg* m);              // 0x00da1fc0
};

// @ 0x00da1b00
void SocialBand::AddCreature(Creature* e)
{
    if (e)
        e->SetParam(0x4f176642);
    PushCreature(mListA, e);
    e->mFlags |= 0x20;
    FUN_00b3d310(&e->sub)->Close();
}

// @ 0x00da1b90
void SocialBand::AddOther(Creature* e)
{
    PushCreature(mListB, e);
    e->mFlags |= 0x20;
    FUN_00b3d310(&e->sub)->Close();
}

// @ 0x00da1c10
bool FUN_00da1c10(Creature* c, int, int, int, ReactResult* res)
{
    if (res) {
        res->f1 = 5;
        res->f2 = 0;
        res->f3 = 0;
    }
    void* block = c->mTribe->anim.Play(0, 0x200000);
    if (!block)
        return false;
    Creature* other = FUN_00d994c0(WatchMemoryBlock(block));
    if (!other)
        return false;
    BandKey key;
    key.mTribe1 = other->GetTribe();
    key.mTribe2 = c->GetTribe();
    key.mPos = *c->sub.GetPos();
    BandKey* kp = &key;
    void* fn = (void*)&SP_FindSocialBandGroup;
    OrderManager* mgr = FUN_00bc9b00(0xf445d1cc, fn, kp);
    OrderNode* node = mgr->FindNode(0xf445d1cc, fn, kp);
    if (!node)
        return false;
    c->mTribe->FUN_00bcb480(node, c, res, fn);
    SocialBand* band = (SocialBand*)g_socialBandPool.GetObject(node->mBandId);
    band->AddOther(c);
    c->mTribe->anim.PlayWait(0, 0x2000000, kFloatMax, 0);
    ((ReactRunner*)res)->FUN_00d9d100(c, band);
    c->UpdateLocomotion(1);
    res->f0 = 0;
    return true;
}

// ---------------------------------------------------------------------------
// Vector helpers (element sizes 0x20 and 4).

struct Elem32 { uint32_t mWords[8]; };                 // 32-byte value element

struct BigVec {                                        // eastl::vector<32-byte element>
    void* mpBegin; void* mpEnd; void* mpCapacity;
    __forceinline uint32_t size() const { return (uint32_t)((int)((char*)mpEnd - (char*)mpBegin) >> 5); }
    void DoInsert(void* pos, uint32_t n, const Elem32& value);     // 0x00d9fb20 (thiscall, ret 0xc)
    void Erase(void* first, void* last);                           // 0x00899420 (thiscall, ret 8)
    void resize(uint32_t n);                           // 0x00da1db0
};

// @ 0x00da1db0
void BigVec::resize(uint32_t n)
{
    if (n > size()) {
        Elem32 value;
        DoInsert(mpEnd, n - size(), value);
    } else {
        Erase((char*)mpBegin + n * 0x20, mpEnd);
    }
}

struct IntV {                                          // eastl::vector<int>
    int* mpBegin; int* mpEnd; int* mpCapacity;
    void assign(const int* first, const int* last, int tag);       // 0x00da1e70
};

// @ 0x00da1e70
void IntV::assign(const int* first, const int* last, int)
{
    int bytes = (int)((const char*)last - (const char*)first);
    int n = bytes >> 2;
    if ((uint32_t)n > (uint32_t)((int)((char*)mpCapacity - (char*)mpBegin) >> 2)) {
        memcpy(0, first, bytes);
        mpBegin = 0;
        mpCapacity = (int*)(n * 4);
        mpEnd = (int*)(n * 4);
        return;
    }
    int size = (int)((char*)mpEnd - (char*)mpBegin) >> 2;
    if ((uint32_t)n > (uint32_t)size) {
        const char* mid = (const char*)first + size * 4;
        memcpy(mpBegin, first, mid - (const char*)first);
        mpEnd = (int*)memcpy(mpEnd, mid, (const char*)last - mid)
              + (((const char*)last - mid) >> 2);
        return;
    }
    mpEnd = (int*)memcpy(mpBegin, first, bytes) + n;
}

// ---------------------------------------------------------------------------
// 0x00da1fc0: message handler of the reaction object (0x41638ca = "community approach").

// @ 0x00da1fc0
bool SocialBand::OnMessage(uint32_t msg, Msg* m)
{
    if (msg != 0x41638ca)
        return false;
    switch (m->GetType()) {
    case 0xaceb7ea7: {
        if (mCount >= mLimit)
            return false;
        if (mState04 == 6)
            return false;
        mCount++;
        if (!mFlag58)
            mTimer = g_reactionTimer;
        AutoRefCount* it = mListA.mpBegin;
        AutoRefCount* end = mListA.mpEnd;
        while (it != end) {
            Creature* e = (Creature*)it->mpObj;
            Creature* c = FUN_00c0c380(e);
            if (c) {
                TribeSlot* slot = TribeSlotAt(c->mTribe, c->mTribe->mIndex);
                int kind = c->FUN_00c22dc0();
                if (slot->mFlag10 == 0) {
                    int base = mCount <= 5 ? (int)mCount : 5;
                    int anim = 0;
                    switch (kind) {
                    case 6: anim = base + 0x5508f8cd; break;
                    case 5: anim = base - 0x0af70712; break;
                    case 4: anim = base - 0x4af70817; break;
                    }
                    if (anim != 0) {
                        int out;
                        e->FUN_00c0b2f0(anim, slot->mObj, &out);
                        slot->mState = e->InterruptAnimation(out, -1, 0);
                    }
                }
                if (mFlag58)
                    slot->mFlag10 = 0;
            }
            ++it;
        }
        return false;
    }
    case 0x79836ba6: {
        float f = 0.0f;
        m->GetNextFloat(&f);
        if (f > kSmallEpsilon)
            mDelay = f;
        return false;
    }
    case 0xf69ff317: {
        float f = 0.0f;
        m->GetNextFloat(&f);
        if (f > kSmallEpsilon)
            mLimit = (uint32_t)(int)f;
        return false;
    }
    case 0xff77507f: {
        if (mCount >= mLimit)
            return false;
        if (mState04 == 6)
            return false;
        mFlag58 = 0;
        void* info = mOwner->mBandInfo;
        if (!info)
            return false;
        char* band = (char*)FUN_00c8ea70(info);
        int n = (int)(mCommands.mpEnd - mCommands.mpBegin);
        if (n <= 0) {
            mChosen = 0;
            mMode = -1;
            return false;
        }
        if (mHandle > 1) {
            FUN_0067cac0(0xe807e90c)->Close();
            mHandle = 0;
        }
        mFlag51 = 1;
        mChosen = (uint32_t)(int)RandomInRange((const float*)(band + 0x98));
        uint32_t idx = g_random.RandomUint32Uniform(
            (uint32_t)(mCommands.mpEnd - mCommands.mpBegin));
        int cmd = mCommands.mpBegin[idx];
        uint32_t key = 0x9de794a4;
        if (cmd == 5) {
            mMode = 2;
            key = 0xc3933f3f;
        } else if (cmd == 6) {
            mMode = 0;
            key = 0x4ea19703;
        } else if (cmd == 7) {
            mMode = 1;
        }
        FUN_00e26de0(mListB.mpBegin, mListB.mpEnd, (void*)&FUN_00d9b480);
        int cnt = (int)(mListB.mpEnd - mListB.mpBegin);
        if (mChosen > (uint32_t)cnt)
            mChosen = (uint32_t)cnt;
        for (uint32_t i = 0; i < mChosen; ++i) {
            Creature* c = (Creature*)mListB.mpBegin[i].mpObj;
            TribeSlot* slot = TribeSlotAt(c->mTribe, c->mTribe->mIndex);
            if (slot->mState == 5 || slot->mState == 4)
                continue;
            slot->mState = 4;
            c->InterruptAnimation(0x61e0675, -1, 0);
            c->FUN_00c1d460(key, 0x950a2438);
            RefToSkin ref(c);
            mSkins.Insert(ref);
        }
        return false;
    }
    }
    return false;
}
