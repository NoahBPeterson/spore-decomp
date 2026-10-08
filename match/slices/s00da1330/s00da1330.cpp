// Slice s00da1330: 0x00da1330, start-up of a tribe-mode "community approach" helper object (retail class
// unnamed). Binds the community / two game objects, computes the approach direction from the leader to
// the target, lays out a 5-point marker fan (0x00f4 vertex array: leader-side points at -15/-22 along the
// direction, two points rotated by +-angle about the direction), starts the effect at +0x178, sends
// message 0x41638ca, derives the relationship mode (+0xec) from the relationship manager, and queues
// tribe-mode command ids 7 / 5 / 6 into the vector at +0x1e4.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"
#include <math.h>

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
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
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
