// Slice s004d34f0: species tuning statics + small accessors on the tuning/profile
// object (vector at +0x48, pair pointers +0x70/+0x74, min/max floats +0x134/+0x138).
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#pragma pack(push, 4)

// 0x004D2450, one argument here (InitStatics pushes a single 0).
void LoadSpeciesTuning(uint32_t which);

// @ 0x004D34F0  SP::`anonymous namespace'::InitStatics
void InitStatics()
{
    LoadSpeciesTuning(0);
}

// ---------------------------------------------------------------------------
// Tuning/profile object stub.
// ---------------------------------------------------------------------------
struct TuningObj {
    char pad0[0x48];
    int   mBegin;      // +0x48
    int   mEnd;        // +0x4c
    char pad50[0x20];  // up to +0x70
    int   m70;         // +0x70
    int   m74;         // +0x74
    char pad78[0x134 - 0x78];
    float mMin;        // +0x134
    float mMax;        // +0x138

    uint32_t GetAt(uint32_t index);
    int      GetActive();
    float    GetBound(bool which);
    void     SetBounds(float lo, float hi);
};

// @ 0x004D3CD0
uint32_t TuningObj::GetAt(uint32_t index)
{
    int* vec = (int*)((char*)this + 0x48);
    int count = (vec[1] - vec[0]) >> 2;
    if (count == 0 || index >= (uint32_t)count)
        return 0x04330667;
    return *(uint32_t*)(*(int*)((char*)this + 0x48) + index * 4);
}

// @ 0x004D3D40
int TuningObj::GetActive()
{
    if (m74 != 0)
        return m74;
    else
        return m70;
}

// @ 0x004D3D70
float TuningObj::GetBound(bool which)
{
    if (which)
        return mMax;
    else
        return mMin;
}

// @ 0x004D3DA0
void TuningObj::SetBounds(float lo, float hi)
{
    mMin = lo;
    mMax = hi;
}

// @ 0x004D3500  (7-arg cdecl float blend)
float Blend(float, float, float a, float, float b, float c, float d)
{
    float k1 = 40.0f;
    float kr = 20.0f;
    float k2 = 20.0f;
    float k3 = (b * k1 + a) + c * kr + d * k2;
    return k3;
}

// ---------------------------------------------------------------------------
// Species hash-map accessors (0x4D3570..0x4D36A0): find() then read a field.
// ---------------------------------------------------------------------------
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct MapNode { uint32_t key; uint32_t v[5]; MapNode* next; };
struct MapIter {
    MapNode* mpNode; MapNode** mpBucket;
    MapIter(MapNode** p) { MapNode* t = *p; mpNode = t; mpBucket = p; }
    bool operator!=(const MapIter& o) const { return mpNode != o.mpNode; }
};
struct SpeciesMap {
    char pad0[4];
    MapNode** mpBuckets; // +4
    uint32_t mCount;  // +8
    MapIter find(const uint32_t& k);
    MapIter end() { ScratchSlots<12>(); return MapIter(mpBuckets + mCount); }
};
// @ 0x004D3570
uint32_t MapGetFieldC(SpeciesMap* m, uint32_t key) {
    MapIter it = m->find(key);
    MapIter e = m->end();
    if (it != e) return it.mpNode->v[2];
    return 0;
}
// @ 0x004D35D0
uint32_t MapGetClamped(SpeciesMap* m, uint32_t key) {
    MapIter it = m->find(key);
    MapIter e = m->end();
    if (it != e) { if (it.mpNode->v[2] > 5) return 5; else return it.mpNode->v[2]; }
    return 0;
}
// @ 0x004D3640
uint32_t MapGetField4(SpeciesMap* m, uint32_t key) {
    MapIter it = m->find(key);
    MapIter e = m->end();
    if (it != e) return it.mpNode->v[0];
    return 0;
}
extern const float kOne;
struct MapDefault { uint32_t a,b,c; float d,e; MapDefault(){ a=0; b=0; c=0; d=kOne; e=kOne; } };
// @ 0x004D36A0
void* MapGetPtr(SpeciesMap* m, uint32_t key) {
    MapIter it = m->find(key);
    MapIter e = m->end();
    if (it != e) return &it.mpNode->v[0];
    static MapDefault def;
    return &def;
}

// ---------------------------------------------------------------------------
// cCreatureAbility ctor/dtor (0x4D3760 / 0x4D3B80): complete, byte-exact.
// ---------------------------------------------------------------------------
template<class T> struct AbVec {
    T* b; T* e; T* c; uint32_t alloc[2];
    AbVec() { b = 0; e = 0; c = 0; }
    void Free();
    ~AbVec() { ScratchSlots<3>(); for (T* p = b; p < e; ++p) {} Free(); }
};
struct AbStr { char pad[0x14]; AbStr(); ~AbStr(); };
struct AbIObj { virtual void AddRef(); virtual void Release(); };
struct AbSmartPtr { AbIObj* p; AbSmartPtr() { p = 0; if (p) p->AddRef(); } ~AbSmartPtr() { if (p) p->Release(); } };
struct AbKey { uint32_t instanceID, typeID, groupID; AbKey() { ScratchSlots<2>(); instanceID = 0; typeID = 0; groupID = 0; } };
struct CreatureAbilityBase { int field04; CreatureAbilityBase() { field04 = 0; } virtual ~CreatureAbilityBase() {} virtual void a(); virtual void b(); };
struct CreatureAbility : CreatureAbilityBase {
    int mType, mCategory, mSocialCategory;
    AbStr nName;                       // 0x14
    uint32_t mVerbIconImageID;       // 0x28
    AbKey mVerbIconGameLayout;         // 0x2c
    uint32_t mVerbIconTriggerKey;    // 0x38
    float mDamage, mRangedDamage, mRazeDamage; // 0x3c
    AbVec<uint32_t> mAnimationIDs;     // 0x48
    AbVec<uint32_t> mFollowerAnimationIDs; // 0x5c
    uint32_t mVerbIconRepresentativeAnimation, mBabyGameAnimationID, mBuildingSpecificAnimationID, mEffectKind; // 0x70
    float mEffectDuration, mEffectDamage;   // 0x80
    uint32_t mMuzzleEffectID, mTrailEffectID, mImpactEffectID; // 0x88
    float mConeDist, mConeRadius, mRefresh, mDuration, mRecharge, mRange, mEnergyCost, mSpeed; // 0x94
    int mSpeedGear;                  // 0xb4
    AbVec<uint32_t> mCombatEffectTypes; // 0xb8
    AbVec<float> mCombatEffectPercentages; // 0xcc
    AbVec<uint32_t> mCombatEffectEffectIds; // 0xe0
    float mRushingRange; uint32_t mRushingAnimationID; float mRushingSpeed; // 0xf4
    bool mbRushingTargetedCharge, mbRushingDoDamage; // 0x100
    float mAdventurerEnergyCost; int mSprintBuff; float mDNAPoints, mLevelMultiplier; // 0x104
    bool mbIsSpecial, mbUseForBabyGame; // 0x114
    uint32_t mHintName; float mAreaOfEffect; // 0x118
    uint32_t mReactionAnimation, mReactionDeathAnimation, mReactionLiveAnimation; // 0x120
    float mReactionDuration;         // 0x12c
    AbSmartPtr mpPropList;             // 0x130
    float mRangeMin, mAvatarRangeMin; // 0x134
    CreatureAbility();
    ~CreatureAbility();
    virtual void a(); virtual void b();
};
// @ 0x004D3760
CreatureAbility::CreatureAbility()
  : mType(0), mCategory(1), mSocialCategory(0),
    nName(),
    mVerbIconImageID(0),
    mVerbIconGameLayout(),
    mVerbIconTriggerKey(0),
    mDamage(0.0f), mRangedDamage(0.0f), mRazeDamage(0.0f),
    mAnimationIDs(), mFollowerAnimationIDs(),
    mVerbIconRepresentativeAnimation(0), mBabyGameAnimationID(0), mBuildingSpecificAnimationID(0), mEffectKind(0),
    mEffectDuration(0.0f), mEffectDamage(0.0f),
    mMuzzleEffectID(0), mTrailEffectID(0), mImpactEffectID(0),
    mConeDist(0.0f), mConeRadius(0.0f), mRefresh(5.0f), mDuration(0.0f), mRecharge(0.0f),
    mRange(10.0f), mEnergyCost(0.0f), mSpeed(5.0f),
    mSpeedGear(0),
    mCombatEffectTypes(), mCombatEffectPercentages(), mCombatEffectEffectIds(),
    mRushingRange(0.0f), mRushingAnimationID(0xffffffff), mRushingSpeed(20.0f),
    mbRushingTargetedCharge(true), mbRushingDoDamage(false),
    mAdventurerEnergyCost(0.0f), mSprintBuff(2), mDNAPoints(0.0f), mLevelMultiplier(1.0f),
    mbIsSpecial(false), mbUseForBabyGame(false),
    mHintName(0), mAreaOfEffect(0.0f),
    mReactionAnimation(0xffffffff), mReactionDeathAnimation(0xffffffff), mReactionLiveAnimation(0xffffffff),
    mReactionDuration(0.0f),
    mpPropList(),
    mRangeMin(0.0f), mAvatarRangeMin(0.0f)
{
}
// @ 0x004D3B80
CreatureAbility::~CreatureAbility() {}

// ---------------------------------------------------------------------------
// cSpeciesProfile ctor (0x4D3DD0): complete; field names are offsets (retail layout differs
// from the 2008 PDB past +0x53c).
// ---------------------------------------------------------------------------
struct CapsTag1 { bool c; CapsTag1() { c = false; } };
struct CapsTag2 { CapsTag2() {} };
struct CapsMap { char data[0x4e0]; CapsMap(const CapsTag1&, const CapsTag2&); };
struct ColorRGB { float r, g, b; ColorRGB() { ScratchSlots<7>(); } };
struct ResKey { uint32_t instanceID, typeID; int groupID; ResKey() { instanceID = 0; typeID = 0; groupID = 0; } };
extern wchar_t gEmptyWStr[2];
struct ProfWStr { wchar_t* b; wchar_t* e; wchar_t* c; uint32_t alloc;
    ProfWStr() { b = 0; e = 0; c = 0; b = gEmptyWStr; e = b; c = b + 1; } };
struct ProfVec3 { uint32_t* b; uint32_t* e; uint32_t* c; ProfVec3() { b = 0; e = 0; c = 0; } };
struct ObjA { uint32_t d[0x1a]; ObjA(); };
struct SubTag { SubTag() {} };
struct ObjAB {
    uint32_t d[0x1a];
    void SubInit(const SubTag&);
    void Init();
    ObjAB() { SubTag t; SubInit(t); Init(); }
};
void BadModelKey(ResKey* k, int n);
inline bool IsEditorGroup(uint32_t g) { return ((g >> 30) & 3) == 1; }
struct cSpeciesProfile {
    CapsMap capsInfos;               // 0x0
    ColorRGB mSkinColors[3];            // 0x4e0
    ResKey animatedCreatureKey;         // 0x504
    ResKey animatedBabyKey;             // 0x510
    ProfWStr animatedCreatureName;       // 0x51c
    ProfWStr animatedCreatureDesc;       // 0x52c
    uint32_t m53c;
    uint32_t m540;
    uint32_t m544;
    float m548;
    float m54c;
    float m550;
    char pad554[0x18];
    float m56c;
    float m570;
    float m574;
    bool m578;
    char pad579[0x3];
    uint32_t m57c;
    char pad580[0x8];
    uint32_t m588;
    float m58c;
    float m590;
    float m594;
    float m598;
    float m59c;
    float m5a0;
    float m5a4;
    float m5a8;
    float m5ac;
    float m5b0;
    float m5b4;
    float m5b8;
    float m5bc;
    float m5c0;
    float m5c4;
    uint32_t m5c8;
    float m5cc;
    uint32_t m5d0;
    uint32_t m5d4;
    uint32_t m5d8;
    uint32_t m5dc;
    uint32_t m5e0;
    uint32_t m5e4;
    uint32_t m5e8;
    uint32_t m5ec;
    uint32_t m5f0;
    char pad5f4[0x4];
    uint32_t m5f8;
    uint32_t m5fc;
    uint32_t m600;
    uint32_t m604;
    uint32_t m608;
    uint32_t m60c;
    uint32_t m610;
    uint32_t m614;
    char pad618[0x4];
    uint32_t m61c;
    char pad620[0x20];
    float m640;
    char pad644[0x4];
    uint32_t m648;
    uint32_t m64c;
    uint32_t m650;
    uint32_t m654;
    uint32_t m658;
    uint32_t m65c;
    uint32_t m660;
    uint32_t m664;
    uint32_t m668;
    float m66c;
    uint32_t m670;
    uint32_t m674;
    uint32_t m678;
    uint32_t m67c;
    uint32_t m680;
    uint32_t m684;
    uint32_t m688;
    uint32_t m68c;
    uint32_t m690;
    uint32_t m694;
    uint32_t m698;
    uint32_t m69c;
    uint32_t m6a0;
    uint32_t m6a4;
    uint32_t m6a8;
    uint32_t m6ac;
    float m6b0;
    uint32_t m6b4;
    ProfVec3 m6b8;                      // 0x6b8
    char pad6c4[8];
    bool m6cc;
    uint32_t m6d0;
    ObjAB m6d4;
    ObjAB m73c;
    ObjA m7a4;
    bool m80c, m80d;
    ObjA m810, m878, m8e0, m948, m9b0;
    cSpeciesProfile(const ResKey& key, bool flag);
};
// @ 0x004D3DD0
cSpeciesProfile::cSpeciesProfile(const ResKey& key, bool flag)
  : capsInfos(CapsTag1(), CapsTag2()),
    mSkinColors(),
    animatedCreatureKey(), animatedBabyKey(), animatedCreatureName(), animatedCreatureDesc(),
    m53c(0),
    m540(0),
    m544(0),
    m548(0.0f),
    m54c(0.0f),
    m550(0.0f),
    m56c(100.0f),
    m570(200.0f),
    m574(0.0f),
    m578(false),
    m57c(0),
    m588(1),
    m58c(0.0f),
    m590(0.0f),
    m594(0.0f),
    m598(0.0f),
    m59c(0.0f),
    m5a0(0.0f),
    m5a4(0.0f),
    m5a8(0.0f),
    m5ac(0.0f),
    m5b0(0.0f),
    m5b4(0.0f),
    m5b8(0.0f),
    m5bc(0.0f),
    m5c0(0.0f),
    m5c4(0.0f),
    m5c8(5000),
    m5cc(1.0f),
    m5d0(2),
    m5d4(0),
    m5d8(0),
    m5dc(0),
    m5e0(0),
    m5e4(0),
    m5e8(0),
    m5ec(0),
    m5f0(0),
    m5f8(0),
    m5fc(0),
    m600(0),
    m604(0),
    m608(0),
    m60c(0),
    m610(0),
    m614(0),
    m61c(0),
    m640(0.0f),
    m648(0),
    m64c(0),
    m650(0),
    m654(0),
    m658(0),
    m65c(0),
    m660(0),
    m664(0),
    m668(0),
    m66c(0.0f),
    m670(0),
    m674(0),
    m678(0),
    m67c(0),
    m680(0),
    m684(0),
    m688(0),
    m68c(0),
    m690(0),
    m694(0),
    m698(0),
    m69c(0),
    m6a0(0),
    m6a4(0),
    m6a8(0),
    m6ac(0),
    m6b0(0.0f),
    m6b4(0),
    m6b8(), m6cc(flag), m6d0(0), m6d4(), m73c(), m7a4(), m80c(false), m80d(false),
    m810(), m878(), m8e0(), m948(), m9b0()
{
    animatedCreatureKey = key;
    animatedBabyKey = key;
    if (key.instanceID != 0 && IsEditorGroup(animatedBabyKey.groupID))
        BadModelKey(&animatedBabyKey, 1);
}
