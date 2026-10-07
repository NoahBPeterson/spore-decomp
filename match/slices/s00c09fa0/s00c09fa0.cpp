// Slice s00c09fa0 -- 0x00c09fa0 (3307 bytes, __cdecl, 5 args): spawn the animals of a herd
// (Simulator creature module; name guessed: SpawnHerdAnimals).
//
//   pos      planet position to spawn around
//   species  cSpeciesProfile of the new animals
//   count    number of animals to create
//   babyFrac fraction of the herd's target size spawned as babies
//   herd     cHerd that receives them (mHerd vector at +0x40)
//
// Preloads the species' object templates, builds the spawn frame (surface orientation at pos),
// counts how many adults/babies the herd still needs (archetype property 0xe6f2fce8 = adult
// fraction, minus existing members), then for each new animal: creates it through the
// creature factory, attaches it to the herd, places it (placement service vfunc 0x10, then
// teleport to the planet-projected position/orientation), resets AI/behavior state, rates its
// strength against the avatar species and randomises its scale and speed.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>
#pragma intrinsic(sin, cos)

#pragma warning(disable: 4100)

inline void* operator new(unsigned int, void* p) throw() { return p; }
inline void operator delete(void*, void*) throw() {}

// float -> int rounding up (the module's asm helper; cvtss2si + cmovb)
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}

// float -> int, current rounding mode (the module's asm helper)
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    static const Vector3 ZERO;     // 0x0168d844
};
struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o)
    {
        m[0] = o.m[0]; m[1] = o.m[1]; m[2] = o.m[2];
        m[3] = o.m[3]; m[4] = o.m[4]; m[5] = o.m[5];
        m[6] = o.m[6]; m[7] = o.m[7]; m[8] = o.m[8];
    }
    static const Matrix3 IDENTITY; // 0x0168d8d4
};

inline Matrix3 QuaternionToMatrix(const Quaternion& q)
{
    Matrix3 r;
    float x = q.x, y = q.y, z = q.z, w = q.w;
    float yy = y * y;
    float zx = z * x;
    float xy = y * x;
    float wx = w * x;
    float zz = z * z;
    float xx = x * x;
    float zy = z * y;
    float wz = w * z;
    float wy = w * y;
    r.m[0] = 1.0f - (zz + yy) * 2.0f;
    r.m[1] = (wz + xy) * 2.0f;
    r.m[2] = (zx - wy) * 2.0f;
    r.m[3] = (xy - wz) * 2.0f;
    r.m[4] = 1.0f - (zz + xx) * 2.0f;
    r.m[5] = (wx + zy) * 2.0f;
    r.m[6] = (wy + zx) * 2.0f;
    r.m[7] = (zy - wx) * 2.0f;
    r.m[8] = 1.0f - (xx + yy) * 2.0f;
    return r;
}

struct cSPTransform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3 mOffset;
    float   mfScale;
    Matrix3 mRotation;
    __forceinline cSPTransform() : mnFlags(0), mnTransformCount(0), mOffset(Vector3::ZERO), mfScale(1.0f)
    {
        mRotation = Matrix3(Matrix3::IDENTITY);
    }
    cSPTransform& SetOffset(const Vector3& v) { mOffset = v; mnFlags |= 4; mnTransformCount++; return *this; }
    cSPTransform& SetRotation(const Matrix3& r) { mRotation = r; mnFlags |= 2; mnTransformCount++; return *this; }
    cSPTransform& operator=(const cSPTransform& o);   // 0x00537dc0
};

// ---- engine types (only what this function touches) ----
struct Property {
    uint32_t pad00[4];
    uint16_t pad10;
    uint16_t mnType;                                  // +0x12 (0xd = float)
    const float* GetValueFloat();                     // 0x0041ea70
};
struct PropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
struct cSpeciesArchetype {
    uint32_t pad000[0x330 / 4];
    int      mStrengthRating;                         // +0x330
    uint32_t pad334[(0x43c - 0x334) / 4];
    PropertyList* mpPropList;                         // +0x43c
};
struct cSpeciesProfile {
    uint32_t pad000[0x504 / 4];
    uint32_t mTemplateKey[(0x53c - 0x504) / 4];       // +0x504 (passed to ObjectTemplateDB)
    uint32_t mSeq;                                    // +0x53c
    uint32_t pad540[(0x56c - 0x540) / 4];
    float    mStat56c;                                // +0x56c
    uint32_t pad570[(0x5b0 - 0x570) / 4];
    float    mStat5b0;                                // +0x5b0
};
struct cSPEditorSpeciesManager {
    cSpeciesArchetype* GetSpeciesArchetype(uint32_t archetype, int generation);  // 0x004e0050
    cSpeciesArchetype* GetAvatarArchetype();                                       // 0x004e01b0
    cSpeciesProfile*   GetAvatarProfile();                                         // 0x004df420
};
cSPEditorSpeciesManager* SpeciesManager();             // 0x00401090

struct IObjectTemplateDB {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual void Preload(void* key, int flag);        // +0x58
};
namespace SP { IObjectTemplateDB* ObjectTemplateDB(); }   // 0x0067cb40

struct cPlanetModel {
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3* pos, const Vector3* dir);  // 0x00b7f250
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3* pos);                      // 0x00b7f190
    Vector3*    ProjectToSurface(Vector3* out, const Vector3* pos, int flag);                      // 0x00b82970
};
namespace SP { cPlanetModel* PlanetModel(); }          // 0x00b3d350

struct IPlacement {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void Place(cSPTransform* out, const cSPTransform* in, cSPTransform* io);   // +0x10
};
struct cSimManager {
    IPlacement* GetPlacement(int which);              // 0x00ac84d0
    struct cCreatureObject* CreateAnimal(cSpeciesProfile* species, int age);   // 0x00ad20e0
};
cSimManager* SimManager();                             // 0x00b3d480

struct cHerd;

struct ILocomotive {                                   // cCreatureBase + 0xc0
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void SetSpeed(float v);                   // +0x40
    virtual void Teleport(const Vector3* pos, const Quaternion* q);   // +0x44
};
struct ICombatant {                                    // cCreatureBase + 0x5a8
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void Reset(int flag);                     // +0x2c
    void SetScale(float s);                           // 0x00f924e0
};
struct cSub34 {
    void Init(int a, int b, float maxDist, float minDist, int c);   // 0x00cee2c0
};
struct cGonzagoTimer {
    void Start();                                     // 0x00bc30f0
};
struct IBehaviorManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void AddAgent(void* agent);               // +0x38
};
namespace SP { IBehaviorManager* BehaviorManager(); }  // 0x00b3d260
namespace SP { uint32_t GetCurrentGameMode(); }        // 0x00b5b800

struct cCreatureObject {
    virtual int  AddRef();                            // +0x00
    virtual int  Release();                           // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c();
    virtual uint32_t GetNounID();                     // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40();
    virtual void ResetProfile();                      // +0x44
    virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void ResetAnimation();                    // +0x54
    virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual float GetDefaultSpeed(int run);           // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8();
    virtual void SetVisible(int on);                  // +0xac
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8();
    virtual void SetSelected(int on);                 // +0xcc
    virtual void OnHerdReset();                       // +0xd0
};

struct cCreatureAnimal : cCreatureObject {
    uint32_t pad004[(0x2a8 - 4) / 4];
    float    f2a8;                                    // +0x2a8
    uint32_t pad2ac;
    int      f2b0;                                    // +0x2b0
    uint32_t pad2b4[(0x5e0 - 0x2b4) / 4];
    float    mScaleBase;                              // +0x5e0
    uint32_t pad5e4[(0xb20 - 0x5e4) / 4];
    cSpeciesProfile* mpSpeciesProfile;                // +0xb20
    uint32_t mProfileSeq;                             // +0xb24
    uint32_t padb28[3];
    int      mAge;                                    // +0xb34
    uint32_t padb38[(0xb58 - 0xb38) / 4];
    uint32_t mGeneralFlags;                           // +0xb58
    uint8_t  padb5c[2];
    uint8_t  mbDead;                                  // +0xb5e
    uint8_t  padb5f;
    uint32_t padb60[(0xb88 - 0xb60) / 4];
    int      mStrengthRating;                         // +0xb88
    uint32_t padb8c[(0x1674 - 0xb8c) / 4];
    cHerd*   mHerd;                                   // +0x1674

    bool  IsBaby();                                   // 0x00c0b770
    bool  HasFlag388();                               // 0x00c0c0e0
    void  SetArchetype(cSpeciesArchetype* a);         // 0x00c0c180
    void  SetSpecies(cSpeciesProfile* s);             // 0x00c222f0
    void  ResetState();                               // 0x00c21090
    void  ResetHealth();                              // 0x00c0d9b0
    void  ResetHunger();                              // 0x00c0bbe0
    void  ResetGoals();                               // 0x00c042e0
    float GetSpeedScale();                            // 0x00c0b9c0
    void  SetSpeedScale(float s);                     // 0x00c0b9d0

    ILocomotive*  Locomotive()  { return (ILocomotive*)((char*)this + 0xc0); }
    ICombatant*   Combatant()   { return (ICombatant*)((char*)this + 0x5a8); }
    cSub34*       Sub34()       { return (cSub34*)((char*)this + 0x34); }
    cGonzagoTimer* Timer1628()  { return (cGonzagoTimer*)((char*)this + 0x1628); }
    void*         BehaviorAgent() { return (char*)this + 0x58; }
};

struct cCreatureAnimalPtr {
    cCreatureAnimal* mpObject;
    cCreatureAnimalPtr(cCreatureAnimal* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    cCreatureAnimalPtr(const cCreatureAnimalPtr& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~cCreatureAnimalPtr() { if (mpObject) mpObject->Release(); }
};

struct AnimalVector {
    cCreatureAnimalPtr* mpBegin;
    cCreatureAnimalPtr* mpEnd;
    cCreatureAnimalPtr* mpCapacity;
    uint32_t mAllocator;
    void DoInsertValue(cCreatureAnimalPtr* position, const cCreatureAnimalPtr& value);   // 0x00aea5d0
    void push_back(const cCreatureAnimalPtr& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) cCreatureAnimalPtr(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct cHerd {
    virtual int AddRef();                             // +0x00
    virtual int Release();                            // +0x04
    uint32_t pad004[(0x40 - 4) / 4];
    AnimalVector mHerd;                               // +0x40
    uint32_t pad050[(0x84 - 0x50) / 4];
    uint8_t  mOwnedByAvatar;                          // +0x84
    uint8_t  pad85[3];
    uint32_t mArchetype;                              // +0x88
    uint32_t pad8c[(0xf0 - 0x8c) / 4];
    int      mGeneration;                             // +0xf0
    int      mTargetHerdSize;                         // +0xf4
    uint32_t padf8[(0x15c - 0xf8) / 4];
    int      mCreaturePersonality;                    // +0x15c

    void OnAnimalRemoved(cCreatureAnimal* a);         // 0x00c6b440
};

struct RandomLCG {
    double RandomDoubleUniform();                     // 0x009360d0
};
extern RandomLCG g_mathRandom;                         // 0x01601760

Quaternion* __cdecl QuaternionFromMatrix33(Quaternion* out, const Matrix3* m, float eps);    // 0x00472b80
Vector3*    __cdecl RotateVector(Vector3* out, const Vector3* v, const Quaternion* q);       // 0x0059aed0
float       __cdecl PlayAvatarSpawn(uint32_t id);                                            // 0x00c0b440
void        __cdecl InitAnimalTuning(cCreatureAnimal* a);                                    // 0x00c035f0

extern float    g_spawnAngle;          // 0x01571278 (pi/2)
extern Vector3  g_spawnAxisA;          // 0x0157127c (1,0,0)
extern Vector3  g_spawnAxisB;          // 0x01571288 (0,1,0)
extern float    g_defaultAdultFrac;    // 0x01582f54
extern uint32_t g_avatarSpawnId;       // 0x0169e370
extern float    g_babyStat2a8;         // 0x015d96b8
extern float    g_scaleRandMin;        // 0x01687a54
extern float    g_scaleRandMax;        // 0x01687a58
extern float    g_speedRandMin;        // 0x01687a4c
extern float    g_speedRandMax;        // 0x01687a50

inline double RandomRange(double lo, double hi)
{
    double v = g_mathRandom.RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi)
        v = hi;
    else if (lo > v)
        v = lo;
    return v;
}

// @ 0x00c09fa0
void __cdecl SpawnHerdAnimals(const Vector3* pos, cSpeciesProfile* species, int count, float babyFrac,
                              cHerd* herd)
{
    SP::ObjectTemplateDB()->Preload(species->mTemplateKey, 1);
    IPlacement* placement = SimManager()->GetPlacement(1);

    // spawn frame: two quarter-turn half-angle rotations combined
    float half = g_spawnAngle * 0.5f;
    Quaternion q1;
    double s1 = sin(half);
    q1.x = (float)(g_spawnAxisA.x * s1);
    q1.y = (float)(g_spawnAxisA.y * s1);
    q1.z = (float)(s1 * g_spawnAxisA.z);
    q1.w = (float)cos(half);
    Quaternion q2;
    float s2 = (float)sin(half);
    q2.x = s2 * g_spawnAxisB.x;
    q2.y = s2 * g_spawnAxisB.y;
    q2.z = s2 * g_spawnAxisB.z;
    q2.w = (float)cos(half);
    Quaternion q;
    q.x = (q1.w * q2.x + q2.w * q1.x) + (q2.z * q1.y - q2.y * q1.z);
    q.y = (q2.y * q1.w + q2.w * q1.y) + (q1.z * q2.x - q2.z * q1.x);
    q.z = (q2.z * q1.w + q2.w * q1.z) + (q2.y * q1.x - q1.y * q2.x);
    q.w = q2.w * q1.w - ((q2.y * q1.y + q2.z * q1.z) + q2.x * q1.x);
    Vector3 tmpV;
    Vector3 dir(*RotateVector(&tmpV, pos, &q));
    cPlanetModel* planet = SP::PlanetModel();
    Quaternion surf;
    planet->BuildSurfaceOrientation(&surf, pos, &dir);

    SpeciesManager();   // result unused (kept: the original makes this call)
    cSimManager* sim = SimManager();
    cSpeciesArchetype* archetype = SpeciesManager()->GetSpeciesArchetype(herd->mArchetype, herd->mGeneration);

    float defaultFrac = g_defaultAdultFrac;
    float adultFrac = defaultFrac;
    if (archetype != 0 && archetype->mpPropList != 0) {
        Property* prop;
        if (archetype->mpPropList->GetProperty(0xe6f2fce8, prop) && prop->mnType == 0xd) {
            adultFrac = *prop->GetValueFloat();
            if (adultFrac < 0.0f)
                adultFrac = g_defaultAdultFrac;
        } else {
            adultFrac = defaultFrac;
        }
    }

    int numBabies = CeilToInt((float)herd->mTargetHerdSize * babyFrac);
    int numAdults;
    if (herd->mTargetHerdSize > 0 && herd->mOwnedByAvatar == 0)
        numAdults = CeilToInt((float)herd->mTargetHerdSize * adultFrac);
    else
        numAdults = 0;

    if (numAdults > 0 || numBabies > 0) {
        int existingAdults = 0;
        for (cCreatureAnimalPtr* it = herd->mHerd.mpBegin, *end = herd->mHerd.mpEnd; it != end; ++it) {
            cCreatureAnimal* a = it->mpObject;
            if (a != 0) {
                if (a->mGeneralFlags & 1)
                    existingAdults++;
                if (!a->IsBaby())
                    numBabies--;
                a->OnHerdReset();
            }
        }
        numAdults -= existingAdults;
    }

    cSpeciesArchetype* avatarArchetype = SpeciesManager()->GetAvatarArchetype();

    cSPTransform xf;
    cSPTransform placed;
    int groupCount = 1;
    xf.SetRotation(QuaternionToMatrix(*planet->BuildSurfaceOrientation(&surf, pos)));
    xf.SetOffset(*pos);
    placed = xf;

    cSpeciesProfile* avatar = SpeciesManager()->GetAvatarProfile();

    int groupSize = 6;
    for (int i = 0; i < count; ++i) {
        bool isAdult = false;
        if (herd->mCreaturePersonality != 1)
            isAdult = i < numAdults;
        int age = 1;
        if (!isAdult && i > 0 && numBabies > 0) {
            age = 0;
            numBabies -= 1;
        }
        if (species == avatar)
            PlayAvatarSpawn(g_avatarSpawnId);
        if (groupCount >= groupSize) {
            groupSize += 6;
            groupCount = 0;
        }
        groupCount += 1;

        cCreatureObject* obj = sim->CreateAnimal(species, age);
        if (obj == 0)
            return;
        cCreatureAnimal* animal = (obj->GetNounID() == 0x18eb45e) ? (cCreatureAnimal*)obj : 0;

        if (animal->mpSpeciesProfile != 0 &&
            (animal->mpSpeciesProfile != species || animal->mProfileSeq != species->mSeq))
            animal->ResetProfile();

        if (animal->mHerd != 0)
            animal->mHerd->OnAnimalRemoved(animal);
        cHerd* old = animal->mHerd;
        if (herd != old) {
            herd->AddRef();
            animal->mHerd = herd;
            if (old != 0)
                old->Release();
        }

        animal->SetArchetype(species == avatar ? avatarArchetype : archetype);
        herd->mHerd.push_back(cCreatureAnimalPtr(animal));

        placement->Place(&xf, &placed, &xf);
        animal->mAge = age;
        Quaternion tq;
        Quaternion orient(*QuaternionFromMatrix33(&tq, &placed.mRotation, 0.0f));
        Vector3 tp;
        animal->Locomotive()->Teleport(planet->ProjectToSurface(&tp, &placed.mOffset, 0), &orient);
        animal->mbDead = 0;
        animal->SetSpecies(species);
        animal->ResetState();
        animal->Sub34()->Init(0, 1, 3.402823466e+38F, 0.0f, 1);
        animal->mGeneralFlags &= 0xfffeff7f;
        animal->Locomotive()->SetSpeed(animal->GetDefaultSpeed(0));
        animal->SetVisible(1);
        animal->SetSelected(0);
        if (!animal->IsBaby() && ((animal->mGeneralFlags >> 9) & 1) == 0 &&
            (SP::GetCurrentGameMode() == 0x1654c01 || SP::GetCurrentGameMode() == 0x1654c02))
            animal->Timer1628()->Start();
        if (animal->HasFlag388())
            animal->f2a8 = g_babyStat2a8;
        animal->ResetHealth();
        animal->ResetHunger();
        animal->ResetGoals();
        animal->f2b0 = 0;
        animal->ResetAnimation();
        SP::BehaviorManager()->AddAgent(animal->BehaviorAgent());

        if (archetype != 0) {
            animal->mStrengthRating = archetype->mStrengthRating;
        } else {
            cSpeciesProfile* prof = animal->mpSpeciesProfile;
            if (prof != 0) {
                float mine = (prof->mStat5b0 + prof->mStat56c) * 0.1f;
                float rating = mine * 0.1f;
                cSpeciesProfile* av = SpeciesManager()->GetAvatarProfile();
                if (av != 0)
                    rating = (mine - (av->mStat5b0 + av->mStat56c) * 0.1f) * 0.1f + 5.0f;
                int r = RoundToInt(rating);
                if (r < 0)
                    r = 0;
                else if (r > 10)
                    r = 10;
                animal->mStrengthRating = r;
            }
        }
        animal->mGeneralFlags |= (isAdult ? 1 : 0);
        InitAnimalTuning(animal);
        animal->Combatant()->Reset(1);
        float scaleBase = animal->mScaleBase;
        animal->Combatant()->SetScale((float)(RandomRange(g_scaleRandMin, g_scaleRandMax) * scaleBase));
        double speedMul = RandomRange(g_speedRandMin, g_speedRandMax);
        animal->SetSpeedScale((float)(animal->GetSpeedScale() * speedMul));
    }
}
