// Slice s00b9f9b0 -- Simulator star/planet setup helpers (0x00b9f9b0..0x00ba0770).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (float compares as ucomiss + lahf, no unwind frames)
#include "types.h"

// ---- engine / simulator imports (declared by address) ----------------------------------
void* __cdecl FUN_00b974c0(void* a, void* b, void* c);               // 0x00b974c0
void  __cdecl operator_delete(void* p);                               // 0x00f47380

// __thiscall callees modelled as member functions of an opaque struct.
struct Call2 { void f(void* a, void* b); };
struct Call1 { void f(void* a); };

// ---- element container: 0x18-byte elements, {begin,end,cap} at +0/+4/+8 ------------------
struct ElemVec18
{
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void push_back_uninitialised();
    void clear();
};

// Scratch record handed to the grow helper: only the three tail dwords are touched.
struct GrowTemp
{
    int    mPad0;
    void*  mpPtr;      // +0x04
    void*  mPad1;
    void*  mPad2;
    int    mPad3[2];
};

// @ 0x00ba0640
void ElemVec18::push_back_uninitialised()
{
    char* p = mpEnd;
    if ((unsigned)p < (unsigned)mpCap)
    {
        mpEnd = p + 0x18;
        if (p != 0)
        {
            ((int*)p)[1] = 0;
            ((int*)p)[2] = 0;
            ((int*)p)[3] = 0;
            return;
        }
    }
    else
    {
        GrowTemp tmp;
        tmp.mpPtr = 0;
        tmp.mPad1 = 0;
        tmp.mPad2 = 0;
        ((Call2*)this)->f(p, &tmp);
        if (tmp.mpPtr != 0 && *(int*)((char*)tmp.mpPtr - 4) != 0)
            operator_delete(tmp.mpPtr);
    }
}

// ---- element container: 0x34-byte elements, embedded tree head at +0x1c -----------------
struct Elem34
{
    int   mPad0;          // +0x00
    int   mPad4;
    int   mPad8;
    int   mPadC;
    int   mPad10;
    int   mPad14;
    int   mPad18;
    void* mpBegin;        // +0x1c  tree head, points at itself when empty
    void* mpEnd;          // +0x20
    void* mpCap;          // +0x24
    unsigned char mFlag;  // +0x28
    unsigned char mPad29;
    unsigned char mPad2A;
    unsigned char mPad2B;
    int   mVal;           // +0x2c
    int   mPad30;         // +0x30
    void InitTree()
    {
        void** h = &mpBegin;
        mpBegin = 0;
        mpEnd = 0;
        mpCap = 0;
        h[0] = h;
        h[1] = h;
        mFlag = 0;
        mVal = 0;
    }
};

struct ElemVec34
{
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void push_back_uninitialised();
};

// @ 0x00ba06f0
void ElemVec34::push_back_uninitialised()
{
    Elem34* p = (Elem34*)mpEnd;
    if ((unsigned)p < (unsigned)mpCap)
    {
        mpEnd = (char*)p + 0x34;
        if (p != 0)
        {
            p->InitTree();
            return;
        }
    }
    else
    {
        Elem34 tmp;
        tmp.InitTree();
        ((Call2*)this)->f(p, &tmp);
        ((Call1*)((char*)&tmp + 0x18))->f(tmp.mpCap);
    }
}

// @ 0x00ba06a0
void ElemVec18::clear()
{
    char* b = mpBegin;
    char* e = mpEnd;
    void* r = FUN_00b974c0(e, e, b);
    ((Call2*)this)->f(r, mpEnd);
    mpEnd -= (e - b) / 0x18 * 0x18;
}

// ---- fixed-size pool descriptor passed to the engine setup call -------------------------
extern float g_flt10000;                        // 0x013f0620
extern float g_flt2;                            // 0x01470f1c
void* __cdecl FUN_00921340(int id);             // 0x00921340

struct Call7 { void f(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7); };

struct FixedPool
{
    int    mHead;      // +0x00
    int    mPad4;      // +0x04
    char*  mpBegin;    // +0x08
    char*  mpEnd;      // +0x0c
    int    mElemSize;  // +0x10
    void*  mpOwner;    // +0x14
    void init(void* base, int bytes, int elemSize, int align, int flags);
};

// throw-away 0x18 byte scratch object reused for the size query (its own storage only)
struct PoolProbe
{
    int mPad0[6];
    unsigned grow(float f);
};

struct Vec2 { float x, y; };

// Simulator object owning the pool at +0x7c and a 2-float value at +0x10.
struct SimObj
{
    int      mPad0[2];   // +0x00
    unsigned mMax8;      // +0x08
    char*    mpEndC;     // +0x0c
    Vec2     mVec10;     // +0x10
    int      m18;        // +0x18
    int      mPad1C[6];  // +0x1c
    void*    mpCtx34;    // +0x34
    int      mPad38[17]; // +0x38
    int      mPool7C[0x120];
    SimObj*  setup(void* a2, void* a3);
};

// @ 0x00ba0570
SimObj* SimObj::setup(void* a2, void* a3)
{
    {
        FixedPool pool;
        pool.mHead = 0;
        pool.init((char*)this + 0x7c, 0x480, 0x48, 8, 0);
        pool.mpBegin = (char*)this + 0x7c;
        pool.mpEnd = (char*)this + 0x4fc;
        pool.mElemSize = 0x48;
        pool.mpOwner = (char*)this + 0x34;
        void* p = FUN_00921340(0x11);
        ((Call7*)this)->f(p, a2, &a3, &a3, a3, &a3, &pool);
    }
    Vec2 v;
    v.x = g_flt10000;
    v.y = g_flt2;
    mVec10 = v;
    int zero = 0;
    m18 = zero;
    unsigned n;
    {
        PoolProbe probe;
        n = probe.grow(*(float*)&mpEndC);
    }
    if (mMax8 < n)
        ((Call1*)this)->f((void*)n);
    return this;
}

// ---- star filtering (0x00b9ff80) ---------------------------------------------------------
struct Vector3
{
    float x, y, z;
    Vector3* Self();
};

// a star record: its child list sits at +0x3c as {begin,end}
struct ChildVec
{
    int* mpBegin;      // +0x00
    int* mpEnd;        // +0x04
    unsigned size() { return (unsigned)((char*)mpEnd - (char*)mpBegin) >> 2; }
};

// surface interface of a star (object reachable through star+0x34)
struct iSurfaceShape
{
    virtual void*  v00();
    virtual void*  v04();
    virtual void*  v08();
    virtual void*  v0c();
    virtual void*  v10();
    virtual void*  v14();
    virtual void*  v18();
    virtual void*  v1c();
    virtual void*  v20();
    virtual void*  v24();
    virtual void*  v28();
    virtual float* GetPosition();             // slot 0x2c
    virtual unsigned GetSurfaceID();          // slot 0x30
};

struct StarRec
{
    int            mPad0[13];   // +0x00
    iSurfaceShape* mpShape;     // +0x34
    int            mPad38[1];   // +0x38
    ChildVec       mChildren;   // +0x3c
    int            mPad44[49];  // +0x44
    int            mType;       // +0x108
    int            mPad10C;     // +0x10c
    int            mSubType;    // +0x110
};

struct StarVec
{
    StarRec** mpBegin;
    StarRec** mpEnd;
};

struct RandomLCG
{
    unsigned RandomUint32Uniform(unsigned a, unsigned b = 0);
};

struct StarWorld
{
    StarVec* getVec();      // 0x00c71000
    int      count();       // 0x00c710c0
    void     remove(int i); // 0x00c71150
};

extern Vector3 g_starPos;                       // 0x01688890
extern RandomLCG g_random;                      // 0x01601760
void __cdecl FUN_00bf55d0();                    // 0x00bf55d0
void __cdecl FUN_00b9fa40();                    // 0x00b9fa40
void __cdecl FUN_00b9a4d0(void* p);             // 0x00b9a4d0
void __cdecl FUN_00b96fa0(void* p);             // 0x00b96fa0
void __cdecl FUN_00b93750(unsigned a, void* p); // 0x00b93750

// @ 0x00b9ff80
void FUN_00b9ff80(StarWorld* p)
{
    FUN_00bf55d0();
    FUN_00b9fa40();
    FUN_00b9a4d0(p);
    StarVec* v = p->getVec();
    int i = 0;
    int n = p->count();
    while (i < n)
    {
        Vector3* pos = ((Vector3*)v->mpBegin[i]->mChildren.mpBegin[0])->Self();
        if (pos->x == g_starPos.x && pos->y == g_starPos.y && pos->z == g_starPos.z)
            p->remove(i);
        else
            i++;
        n = p->count();
    }
    StarVec* w = p->getVec();
    if (w->mpBegin != w->mpEnd)
    {
        unsigned cnt = (unsigned)p->count();
        unsigned r = g_random.RandomUint32Uniform(cnt, (unsigned)p);
        FUN_00b93750(r, p);
    }
    i = 0;
    n = p->count();
    while (i < n)
    {
        StarRec* e = v->mpBegin[i];
        if (e->mChildren.size() == 0)
            p->remove(i);
        else
            i++;
        n = p->count();
    }
    FUN_00b96fa0(p);
}

// ---- star-record registration -----------------------------------------------------------
struct Vector4 { float x, y, z, w; };

// interface implemented by the manager object at SimCtx+0x120 (slots 0x2c / 0x30 used)
struct VBase
{
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28();
    virtual void* v2c();
    virtual Vector4* v30(void* a);
};

// star record / surface placement shared by the two setup routines below
struct iStarShape;                          // object reachable through star+0x34
struct cEmpireRef                           // object reachable through SimCtx+0xd4
{
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28();
    virtual void* v2c();
    virtual void* v30();
    virtual void* v34();
    virtual void* v38();
    virtual void* v3c();
    virtual void* v40();
    virtual void* v44();
    virtual void* v48();
    virtual unsigned GetEmpireID();         // slot 0x4c
};

struct SimCtx
{
    int         mPad0[15];   // +0x00
    void*       mp3C;        // +0x3c
    int         mPad40[38];  // +0x40
    cEmpireRef  mEmpire;     // +0xd4
    int         mPadD8[25];  // +0xd8
    int         mPlanetId;   // +0x13c
    void* getMgr();
    void* GetCivData(int which);   // 0x00c71030
    int   GetCityEconomy();        // 0x00c70e00
};

struct SimSingleton
{
    SimSingleton* ctor();
    void reg(void* fn, void* a, void* b);
};

extern void* g_simSingleton;                   // 0x0167a60c
void* __cdecl EAAllocate(unsigned size, const char* file, int a, int b, int c, int d,
                         ...);                             // 0x00f473a0
void  __cdecl FUN_00b9c5b0();                  // 0x00b9c5b0 (callback)

// @ 0x00b9f9b0
void FUN_00b9f9b0(SimCtx* p)
{
    char* mgr = (char*)p->getMgr() + 0x120;
    VBase* vp = (VBase*)mgr;
    Vector4* pv = vp->v30(p);
    void* ctx = p->mp3C;
    SimSingleton* s = (SimSingleton*)g_simSingleton;
    if (s == 0)
    {
        void* mem = EAAllocate(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0, *pv);
        if (mem != 0)
            s = ((SimSingleton*)mem)->ctor();
        g_simSingleton = s;
    }
    void* a = vp->v2c();
    s->reg((void*)&FUN_00b9c5b0, ctx, a);
}

// ---- city placement driven by the planet arithmetic scripts ------------------------------
struct cArithmeticaProgram
{
    int   mStorage[0x24];
    void  ctor();                              // 0x007f1e60
    void  Destroy();                           // 0x007f1d90
    void  ArithReset();                        // 0x007f2500
    void  SetVar(const char* name, float v);   // 0x007f25c0
    float GetVar(const char* name);            // 0x007f2590
};

bool __cdecl LoadArithmeticaFile(unsigned a, unsigned b, cArithmeticaProgram* p); // 0x007f2240

struct cTerrainInfo                           // object reached through planet model +0x24
{
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual float* GetTerrain();              // slot 0x0c
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28();
    virtual void* v2c();
    virtual void* v30();
    virtual void* v34();
    virtual void* v38();
    virtual void* v3c();
    virtual void* v40();
    virtual void* v44();
    virtual void* v48();
    virtual void* v4c();
    virtual void* v50();
    virtual void  ApplySurfaceDetail(void* placement, void* prop);   // slot 0x54
};

struct cPlanetModel
{
    int          mPad0[9];     // +0x00
    cTerrainInfo* mpTerrain;   // +0x24
    int          mPad28[15];   // +0x28
    int          mEmpireIndex; // +0x64
    float water_fraction();                                        // 0x00b7ec50
    bool  FindClosestWater(float* pos, float radius, void* out);   // 0x00b8bb70
    void  BuildSurfaceOrientation2(float* rotation, float* quat, float* scale); // 0x00b7f250
};

cPlanetModel* __cdecl SP_PlanetModel();              // 0x00b3d350
void*         __cdecl SP_NounManager();              // 0x00b3d300
void*         __cdecl SP_TerraformingManager();      // 0x00b3d430
void*         __cdecl SP_StarManager(unsigned id);   // 0x00b3d2a0
void*         __cdecl SP_PropertyManager();          // 0x0067de30
void*         __cdecl SP_LivingUniverse_GetPlayerEmpire();   // 0x01021300
void          __cdecl FUN_00b992c0();                // 0x00b992c0

struct StarList                                // 12-byte eastl vector of StarRec*
{
    StarRec** mpBegin;
    StarRec** mpEnd;
    StarRec** mpCap;
    void build(int count, void* src);          // 0x00b93c60
    void destroy();                            // 0x00ae6970
};

struct GameData
{
    int       mPad0;
    StarRec** mpBegin;      // +0x04
    StarRec** mpEnd;        // +0x08
    int       mPadC;
    void*     mpExtra;      // +0x10
};

struct cGameNounManager
{
    GameData* GetGameDataVector(int a1, int a2, int a3, int a4, int a5);  // 0x00b21340
    void      RemoveNounsOfType(int type);                                // 0x00b22650
};

struct iRefCounted
{
    virtual void* v00();
    virtual void  Release();                   // slot 0x04
};

void __cdecl FUN_00829110(StarList* out, StarRec** begin, StarRec** end,
                          StarRec** all, int numCities);       // 0x00829110
void __cdecl FUN_00b96130(StarRec** a, StarRec** b, void* pos); // 0x00b96130
char __cdecl FUN_00b907a0(int region, int i, int j);            // 0x00b907a0
void __cdecl FUN_00b94090(float* pos, unsigned shape, unsigned a, unsigned b,
                          int c, float* dist, int flag);        // 0x00b94090
bool __cdecl FUN_00b9d640(int* slot, unsigned* tag, int* counter, int flag); // 0x00b9d640
void* __cdecl FUN_00921580(void* node);                         // 0x00921580 RBTreeIncrement

extern int   g_numTiles;         // 0x0156c084  tiles per surface edge
extern int*  g_citySlots;        // 0x01688 8ec  array of potential city slots
extern void* g_cityTreeRoot;     // 0x0156c048
extern void* g_cityTreeEnd;      // 0x0156c044
extern float g_starOrigin_y;     // 0x016888e8  reference surface position

// @ 0x00b9fa40
void FUN_00b9fa40()
{
    cPlanetModel* planet = SP_PlanetModel();
    if (planet == 0)
        return;

    cArithmeticaProgram arith;
    arith.ctor();
    LoadArithmeticaFile(0x18657795, 0x24a4f5a, &arith);
    arith.SetVar("water_fraction", planet->water_fraction());
    arith.ArithReset();

    int numCities     = (int)arith.GetVar("num_cities");
    int numNearWater  = (int)arith.GetVar("num_cities_near_water");
    int numDry        = numCities - numNearWater;

    int placedDry     = 0;
    int placedWater   = 0;
    int placed        = 0;

    FUN_00b992c0();

    bool wantWater = numNearWater > 0;
    bool wantDry   = numDry > 0;

    cGameNounManager* nouns =
        (cGameNounManager*)SP_NounManager();
    GameData* game = nouns->GetGameDataVector(0xcd7d10, 0xd3d420, 0xace070,
                                             0xb1e500, 0x36be27e);

    StarList stars;
    stars.build((int)(game->mpEnd - game->mpBegin), game->mpExtra);

    StarList waterStars;
    FUN_00829110(&waterStars, game->mpBegin, game->mpEnd, stars.mpBegin, numCities);
    FUN_00b96130(waterStars.mpBegin, waterStars.mpEnd, &g_starOrigin_y);

    for (StarRec** pp = stars.mpBegin; pp != stars.mpEnd; ++pp)
    {
        if (!wantWater && !wantDry)
            break;

        StarRec* star = *pp;
        if (star->mType != (int)0x91fe517b)
            continue;
        if (star->mSubType != (int)0xd8c67022 && star->mSubType != (int)0xaed08dd4)
            continue;

        float* pos = star->mpShape->GetPosition();
        unsigned shape = star->mpShape->GetSurfaceID();

        float x = pos[0];
        float y = pos[1];
        float z = pos[2];
        float ax = x < 0.0f ? -x : x;
        float ay = y < 0.0f ? -y : y;
        float az = z < 0.0f ? -z : z;
        float half = g_numTiles * 0.5f;

        int i;
        int j;
        int region;

        if (az < ax || az < ay)
        {
            if (ay < ax)
            {
                i = (int)((y / x + 1.0f) * half);
                j = (int)((z / ax + 1.0f) * half);
                region = x < 0.0f ? 3 : 2;
            }
            else
            {
                i = (int)((z / y + 1.0f) * half);
                j = (int)((x / ay + 1.0f) * half);
                region = y < 0.0f ? 5 : 4;
            }
        }
        else
        {
            i = (int)((x / z + 1.0f) * half);
            j = (int)((y / az + 1.0f) * half);
            region = z < 0.0f ? 1 : 0;
        }

        if (i == g_numTiles)
            i--;
        if (j == g_numTiles)
            j--;

        if ((FUN_00b907a0(region, i, j) & 0x77) != 0)
            continue;

        float dist = 0.0f;
        int   which = -1;                       // 0: near water, 1: dry
        if (planet->FindClosestWater(pos, 70.0f, &dist))
        {
            if (wantWater)
            {
                FUN_00b94090(pos, shape, 0x36be27e, 0xd18d25cd, 0, &dist, 1);
                which = 0;
            }
        }
        else if (wantDry)
        {
            FUN_00b94090(pos, shape, 0x36be27e, 0xd18d25cd, 0, &dist, 1);
            which = 1;
        }

        if (which >= 0 && dist != 0.0f)
        {
            if (which == 0)
                placedWater++;
            else
                placedDry++;
            placed++;
            wantWater = placedWater < numNearWater;
            wantDry   = placedDry < numDry;
        }
    }

    if (placedDry > 0 || placedWater > 0)
    {
        for (StarRec** pp = stars.mpBegin; pp < stars.mpEnd; ++pp)
            if (*pp != 0)
                ((iRefCounted*)*pp)->Release();
        if (stars.mpBegin != 0 && ((int*)stars.mpBegin)[-1] != 0)
            operator_delete(stars.mpBegin);
        arith.Destroy();
        return;
    }

    stars.destroy();

    // Fill the remaining city budget from the global list of candidate slots.
    unsigned tag[2];
    tag[0] = 0xf24e652e;
    tag[1] = 0xa3d74ba7;

    void* node = g_cityTreeRoot;
    while (node != g_cityTreeEnd && placed < numCities)
    {
        unsigned* entry = (unsigned*)node;
        if (*((char*)entry[4] + planet->mEmpireIndex) != 0)
        {
            int* slot = g_citySlots + entry[5] * 0x34;
            if (placedWater < numNearWater &&
                FUN_00b9d640(slot, tag, &placed, 0) != 0)
                placedWater++;
            else if (placedDry < numDry &&
                     FUN_00b9d640(slot, tag, &placed, 0) != 0)
                placedDry++;
        }
        node = FUN_00921580(node);
    }

    arith.Destroy();
}

// ---- initial city seeding for a planet (0x00ba0080) --------------------------------------
struct cEmpire
{
    int      GetHomePlanet();          // 0x00c31730
    bool     IsPlayerEmpire();         // 0x00c308b0
    unsigned GetColor(void* out);      // 0x00c32cd0
};

struct cStarManager
{
    cEmpire* GetEmpireByID(unsigned id);      // 0x00ba9370
};

struct cTerraformingManager
{
    int GetUnlockedCount(int flag);           // 0x00bbe470
};

struct cCity
{
    float* Self();                    // 0x00572590
    void   ctor();                    // 0x00ff1cb0
    void   SetID(unsigned id);        // 0x00ff0380
    void   SetSize(int size);         // 0x009879d0
    void   SetPosition(float* pos);   // 0x00ff0430
    void   SetStyle(unsigned style);  // 0x00bfc460
};

struct cCivData
{
    int      mPad0[15];        // +0x00
    cCity**  mpCitiesBegin;    // +0x3c
    cCity**  mpCitiesEnd;      // +0x40
    void     SetElementAlignment(unsigned style);      // 0x00fcc200
    cCity*   AddCity(cCity* city);                     // 0x00ff2c70
    void     EraseCity(int index);                     // 0x00ff1fb0
};

struct Matrix3
{
    float m[9];
    void Assign(const float* src);            // 0x0041cb40
};

struct cPropertyManager
{
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28();
    virtual bool  GetProperty(unsigned key, float def, void** out);   // slot 0x2c
};

void*    __cdecl FUN_00b6e3d0(unsigned color);          // 0x00b6e3d0
unsigned __cdecl FUN_00bef920(unsigned value);          // 0x00bef920
int      __cdecl FUN_00b93550(cCity* city, void* ctx);  // 0x00b93550
void     __cdecl FUN_0059c190(Matrix3* out, const float* quat);  // Matrix3FromQuaternion

extern float g_identityMatrix;   // 0x01688924  identity basis copied into the placement

// record describing where a city is dropped on the planet surface
struct SurfacePlacement
{
    unsigned short mFlags;        // +0x00
    unsigned short mStep;         // +0x02
    float          mPosition[3];  // +0x04
    float          mRadius;       // +0x10
    Matrix3        mRotation;     // +0x14
    float          mQuat[4];      // +0x38
    float          mScale[3];     // +0x48
};

// @ 0x00ba0080
void FUN_00ba0080(SimCtx* ctx)
{
    if (SP_NounManager() == 0)
        return;
    cPlanetModel* planet = SP_PlanetModel();
    if (planet == 0)
        return;

    cArithmeticaProgram arith;
    arith.ctor();
    LoadArithmeticaFile(0x9dd95c4, 0x24a4f5a, &arith);
    arith.ArithReset();

    unsigned empireID = ctx->mEmpire.GetEmpireID();
    cEmpire* empire = ((cStarManager*)SP_StarManager(empireID))->GetEmpireByID(empireID);
    if (empire == 0)
    {
        arith.Destroy();
        return;
    }

    bool isHomePlanet = empire->GetHomePlanet() == ctx->mPlanetId;

    cTerraformingManager* terra = (cTerraformingManager*)SP_TerraformingManager();
    cCivData* civ = (cCivData*)ctx->GetCivData(0);
    int numCities = (int)(civ->mpCitiesEnd - civ->mpCitiesBegin);
    int budget = numCities;
    if (!isHomePlanet)
    {
        int unlocked = terra->GetUnlockedCount(0);
        budget = unlocked < numCities ? unlocked : numCities;
    }

    unsigned style;
    if (empire == (cEmpire*)SP_LivingUniverse_GetPlayerEmpire() || !empire->IsPlayerEmpire())
    {
        unsigned rgb;
        style = (unsigned)FUN_00b6e3d0(empire->GetColor(&rgb));
    }
    else
        style = 0x53dbcf9;
    civ->SetElementAlignment(style);

    FUN_00b9fa40();

    cGameNounManager* nouns = (cGameNounManager*)SP_NounManager();
    GameData* game = nouns->GetGameDataVector(0xcd7d10, 0xd3d420, 0xace070,
                                             0xb1e500, 0x36be27e);
    StarRec** pp = game->mpBegin;
    int i = 0;
    while (pp != game->mpEnd)
    {
        if (i >= budget)
            break;
        StarRec* star = *pp;
        if (star->mType == (int)0xd18d25cd)
        {
            cCity* city = civ->mpCitiesBegin[i];
            i++;
            int size = FUN_00b93550(city, ctx);
            if (size != 0)
            {
                city->SetSize(size);
                city->SetPosition(star->mpShape->GetPosition());
                int economy = ctx->GetCityEconomy();
                unsigned s = (economy == 5) ? 0 : g_random.RandomUint32Uniform(3);
                city->SetStyle(FUN_00bef920(s));
            }
        }
        ++pp;
    }

    nouns->RemoveNounsOfType(0x36be27e);

    i = 0;
    while (i < (int)(civ->mpCitiesEnd - civ->mpCitiesBegin))
    {
        float* pos = civ->mpCitiesBegin[i]->Self();
        if (pos[0] == g_starPos.x && pos[1] == g_starPos.y && pos[2] == g_starPos.z)
            civ->EraseCity(i);
        else
            i++;
    }

    // No city survived on this planet: seed one at the surface directly below the star.
    if (civ->mpCitiesEnd == civ->mpCitiesBegin)
    {
        float* terrain = planet->mpTerrain->GetTerrain();
        float height = terrain[0x3c] * terrain[0x38] + terrain[0x34];

        SurfacePlacement place;
        place.mFlags = 0;
        place.mStep = 0;
        place.mPosition[0] = g_starPos.x;
        place.mPosition[1] = g_starPos.y;
        place.mPosition[2] = g_starPos.z;
        place.mRadius = 1.0f;
        place.mRotation.Assign(&g_identityMatrix);
        place.mFlags |= 4;
        place.mPosition[0] = 0.0f;
        place.mPosition[1] = height + 10.0f;
        place.mPosition[2] = 0.0f;

        float unit[3];
        unit[0] = unit[1] = unit[2] = 1.0f;
        place.mScale[0] = 0.0f;
        place.mScale[1] = 600.0f;
        place.mScale[2] = 0.0f;
        place.mStep++;
        planet->BuildSurfaceOrientation2(place.mRotation.m, place.mQuat, unit);

        Matrix3 basis;
        FUN_0059c190(&basis, place.mQuat);
        place.mRotation = basis;
        place.mFlags |= 2;
        place.mStep++;

        void* prop = 0;
        cPropertyManager* props = (cPropertyManager*)SP_PropertyManager();
        if (prop != 0)
        {
            void* dead = prop;
            prop = 0;
            ((iRefCounted*)dead)->Release();
        }
        if (props->GetProperty(0xbb1951ef, 4.0782470703125f, &prop))
            planet->mpTerrain->ApplySurfaceDetail(&place, prop);

        cCity* city = (cCity*)EAAllocate(0xc4, "Simulator/cCityData", 0, 0, 0, 0);
        if (city != 0)
            city->ctor();
        civ->AddCity(city);
        city->SetID(0xfd701f6f);
        city->SetSize(2);
        float pos[3];
        pos[0] = 0.0f;
        pos[1] = 600.0f;
        pos[2] = 0.0f;
        city->SetPosition(pos);
        city->SetStyle(FUN_00bef920(g_random.RandomUint32Uniform(3)));
        if (prop != 0)
            ((iRefCounted*)prop)->Release();
    }

    arith.Destroy();
}
