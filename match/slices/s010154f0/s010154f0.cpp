// Slice s010154f0 -- SP::cSimulatorUniverse::cSimulatorUniverse (0x010154f0, 2301 bytes).
// Constructs the universe simulator: base ctor, 9 inline event/action sub-objects registered in the
// event vector_map, three empty maps, then reads the tuning property list (0x3e9793b5/0x2ae0c7e).
// Field offsets are the retail ones from the disassembly (they differ from the 2008 PDB).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).  Property reads follow the cCityGameTuning::Init pattern (s00cef050).
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

// ---- property access ---------------------------------------------------------------------
struct Property {
    uint8_t pad[0x12];
    uint16_t mType;                                           // +0x12
    int* GetInt();                                            // 0x0041e990
    float* GetFloat();                                        // 0x0041ea70
};
struct cPropertyList {
    virtual void vf0();
    virtual int Release();                                    // +0x04
    virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5(); virtual void vf6();
    virtual void vf7(); virtual void vf8();
    virtual bool GetProperty(uint32_t id, Property** out);    // +0x24
};
struct PropListPtr {
    cPropertyList* mpObject;
    PropListPtr() : mpObject(0) {}
    cPropertyList** AsPPTypeParam()
    {
        if (mpObject) {
            cPropertyList* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};
struct IPropertyManager {
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3(); virtual void vf4();
    virtual void vf5(); virtual void vf6(); virtual void vf7(); virtual void vf8(); virtual void vf9();
    virtual void vf10();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** out);   // +0x2c
};
IPropertyManager* PropertyManager();                          // 0x0067de30

static inline void LoadInt(cPropertyList* l, uint32_t id, int& dst)
{
    Property* p;
    if (l && l->GetProperty(id, &p) && p->mType == 9)
        dst = *p->GetInt();
}
static inline void LoadFloat(cPropertyList* l, uint32_t id, float& dst)
{
    Property* p;
    if (l && l->GetProperty(id, &p) && p->mType == 13)
        dst = *p->GetFloat();
}
static inline float GetFloatDef(cPropertyList* l, uint32_t id, float def)
{
    Property* p;
    if (l && l->GetProperty(id, &p) && p->mType == 13)
        return *p->GetFloat();
    return def;
}

// EA float->int64 helper: fistp in the current (round-to-nearest) mode.
inline __int64 FloatToInt64(float f)
{
    __declspec(align(8)) __int64 result;
    __asm fld   f
    __asm fistp result
    return result;
}

// ---- EASTL pieces --------------------------------------------------------------------------
struct RBAnchor {
    void* right;
    void* left;
    void* parent;
    int color;
    RBAnchor() : left(0), parent(0), color(0) {}
};
struct RBMap {
    uint32_t mCompare;
    RBAnchor mAnchor;
    int mnSize;
    RBMap()
    {
        mAnchor.right = &mAnchor;
        mAnchor.left = &mAnchor;
        mAnchor.parent = 0;
        *(char*)&mAnchor.color = 0;
        mnSize = 0;
    }
};

struct UniverseAction;
struct UniverseEvent;
struct ActionVector {
    UniverseAction** mpBegin;
    UniverseAction** mpEnd;
    UniverseAction** mpCapacity;
    void DoInsertValue(UniverseAction** pos, UniverseAction* const& v);   // 0x00b96600
    void push_back(UniverseAction* const& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) UniverseAction*(v);
        else
            DoInsertValue(mpEnd, v);
    }
};
struct EventMap {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    EventMap() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ActionVector& operator[](UniverseEvent* const& key);       // 0x01015410
};

// ---- inline-constructed event / action sub-objects -----------------------------------------
struct V4  { virtual void f(); };                                         // vptr only
struct V8  { virtual void f(); int pad; };                                // vptr + unwritten word
struct E10 { virtual void f(); int pad; int a; int b; E10() : a(0), b(0) {} };
struct E08 { virtual void f(); int a; E08() : a(0) {} };
struct EF  { virtual void f(); float a; EF() : a(0.0f) {} };
struct EFI { virtual void f(); float a; int b; EFI() : a(0.0f), b(0) {} };
struct GrobWarAttackEvent {
    virtual void f();
    int a; float x, y, z; int b;
    GrobWarAttackEvent() : a(0), b(0) { x = 0.0f; y = 0.0f; z = 0.0f; }
    void Init();                                                          // 0x0100e150
};

struct GonzagoA { virtual void a0(); int padA; };
struct GonzagoB { virtual void b0(); int padB; };
struct cGonzagoSimulator : GonzagoA, GonzagoB {
    cGonzagoSimulator();                                                  // 0x00b5b6c0
    ~cGonzagoSimulator();
};
inline cGonzagoSimulator::~cGonzagoSimulator() {}

struct cSimulatorUniverse : cGonzagoSimulator {
    PropListPtr mTuning;           // +0x10
    int m14;                       // +0x14
    RBMap mTimeOfLastUpdate;       // +0x18 (anchor +0x1c)
    int pad30;
    V4 ev34;                       // +0x34
    V8 ac38;                       // +0x38
    E10 ev40;                      // +0x40
    V8 ac50;                       // +0x50
    E10 ev58;                      // +0x58
    V8 ac68;                       // +0x68
    E10 ev70;                      // +0x70
    V8 ac80;                       // +0x80
    E10 ev88;                      // +0x88
    V8 ac98;                       // +0x98
    E10 eva0;                      // +0xa0
    V4 acb0;                       // +0xb0
    GrobWarAttackEvent evb4;       // +0xb4
    V4 accc;                       // +0xcc
    E08 evd0;                      // +0xd0
    V4 acd8;                       // +0xd8
    EF evdc;                       // +0xdc
    V4 ace4;                       // +0xe4
    EFI eve8;                      // +0xe8
    V4 acf4;                       // +0xf4
    EventMap mEventList;           // +0xf8
    int pad104[3];
    int m110;                      // +0x110
    int m114;                      // +0x114
    int m118;                      // +0x118
    unsigned m11c;                 // +0x11c
    int m120;                      // +0x120
    unsigned m124;                 // +0x124
    int m128, m12c, m130;
    int m134, m138;
    float f13c, f140, f144, f148, f14c, f150, f154;
    int m158;
    unsigned m15c;
    float f160, f164, f168, f16c, f170, f174, f178;
    RBMap mAwarenessValue;         // +0x17c (anchor +0x180)
    int pad194[1];
    RBMap mThird;                  // +0x198 (anchor +0x19c)
    int pad1ac;

    cSimulatorUniverse();
    virtual void a0();
    virtual void b0();
};

extern cSimulatorUniverse* gUniverse;                                     // 0x016dc798

// @ 0x010154f0  SP::cSimulatorUniverse::cSimulatorUniverse
cSimulatorUniverse::cSimulatorUniverse()
    : m14(0), m110(-1), m114(0), m120(2), m124(0), m128(0), m12c(0), m130(0),
      f13c(0.0f), f140(0.0f), f144(0.0f), f148(0.0f), f150(0.0f), f154(0.0f), m158(0), m15c(0)
{
    gUniverse = this;
    IPropertyManager* mgr = PropertyManager();
    mgr->GetPropertyList(0x3e9793b5, 0x2ae0c7e, mTuning.AsPPTypeParam());
    {
        Property* p;
        cPropertyList* t = mTuning.mpObject;
        if (t && t->GetProperty(0x4a4b35f, &p) && p->mType == 9)
            m124 = *p->GetInt();
    }
    m124 = m124 * 1000;
    LoadInt(mTuning.mpObject, 0x4a5e5bb, m118);
    {
        float v = 0.0f;
        LoadFloat(mTuning.mpObject, 0x4a5e5bc, v);
        v *= 1000.0f;
        m11c = (unsigned)FloatToInt64(v);
    }
    LoadFloat(mTuning.mpObject, 0x4a5e5bd, f13c);
    LoadFloat(mTuning.mpObject, 0x4a5e5be, f140);
    LoadFloat(mTuning.mpObject, 0x4a5e5bf, f144);
    LoadFloat(mTuning.mpObject, 0x4a5e5c0, f148);
    LoadFloat(mTuning.mpObject, 0x4a5e5d0, f14c);
    LoadFloat(mTuning.mpObject, 0x4a5e5c1, f154);
    LoadFloat(mTuning.mpObject, 0x4a5e5d1, f150);
    {
        float v = 0.0f;
        LoadFloat(mTuning.mpObject, 0x4a5e5d2, v);
        v *= 1000.0f;
        m15c = (unsigned)FloatToInt64(v);
    }
    LoadFloat(mTuning.mpObject, 0x55b9da9, f160);
    LoadFloat(mTuning.mpObject, 0x55b9da7, f164);
    LoadFloat(mTuning.mpObject, 0x55b9da5, f168);
    LoadFloat(mTuning.mpObject, 0x55b9da4, f16c);
    LoadFloat(mTuning.mpObject, 0x55b9da2, f170);
    LoadFloat(mTuning.mpObject, 0x55b9d9f, f178);
    LoadFloat(mTuning.mpObject, 0x55b9d9c, f174);
    evb4.Init();
    {
        UniverseAction* a = (UniverseAction*)&ac38;
        UniverseEvent* e = (UniverseEvent*)&ev34;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&ac50;
        UniverseEvent* e = (UniverseEvent*)&ev40;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&ac68;
        UniverseEvent* e = (UniverseEvent*)&ev58;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&ac80;
        UniverseEvent* e = (UniverseEvent*)&ev70;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&ac98;
        UniverseEvent* e = (UniverseEvent*)&ev88;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&acb0;
        UniverseEvent* e = (UniverseEvent*)&eva0;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&accc;
        UniverseEvent* e = (UniverseEvent*)&evb4;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&ace4;
        UniverseEvent* e = (UniverseEvent*)&evdc;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&acf4;
        UniverseEvent* e = (UniverseEvent*)&eve8;
        mEventList[e].push_back(a);
    }
}

// =====================================================================
// s010154f0 cluster: SP::cSPSimulatorWalkAround and neighbours.
// Retail layout (the 2008 PDB offsets differ for cSimulatorUniverse, but
// these helpers use the retail cSPSimulatorWalkAround layout).
// =====================================================================

namespace SP {
struct cSPMissionManager {
    unsigned char pad00[8];
    unsigned* AsInterface(unsigned id);                                   // 0x01015e00
};
struct Ticker;
Ticker* SimTicker();                                                      // 0x00b3d330
} // namespace SP

// @ 0x01015e00  SP::cSPMissionManager::AsInterface
unsigned* SP::cSPMissionManager::AsInterface(unsigned id)
{
    switch (id) {
    case 0x11416b8u:
        return (unsigned*)((char*)this - 8);
    case 0x179c807u:
    case 0xee3f516eu: {
        cSPMissionManager* p = (cSPMissionManager*)((char*)this - 8);
        return (unsigned*)((size_t)this & -(size_t)(p != 0));
    }
    default:
        return 0;
    }
}

// Polymorphic helpers whose exact classes are unnamed in the image.
struct ITicker { virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
    virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07(); virtual void t08();
    virtual void t09(); virtual void t10(); virtual void t11(); virtual void t12(); virtual void t13();
    virtual void t14(); virtual void t15(); virtual void t16(); virtual void t17(); virtual void t18();
    virtual void t19(); virtual void t20(void* owner); };                 // slot 0x50

struct IRefCounted { virtual void r00(); virtual void r01(); };           // slots 0x00 / 0x04
struct IStrategyPart { virtual void s00(); virtual void s01(); virtual void s02(); };
struct IStrategyHolder { unsigned char pad00[0x3c]; IStrategyPart* mpPart; };
struct IRefBut34 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual char v11(); // slot 0x2c
    unsigned char pad04[0x34 - 4];
    unsigned      mField34;                                               // +0x34
};

struct cGonzagoTimer {
    unsigned char mData[0x14];                                            // +0x00
    int           mFlags;                                                 // +0x14 (object +0x34)
    unsigned char pad18[8];                                               // +0x18
    cGonzagoTimer();                                                      // 0x00b63890
    ~cGonzagoTimer();                                                     // 0x00b638b0
};
struct ObjVector {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    ObjVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~ObjVector();                                                         // 0x00ae6970
    void reserve8(int n);                                                 // 0x00d01790 (thiscall, ret 4)
};
void FUN_00d01790(int n);                                                 // 0x00d01790
extern void* gWalkAroundInstance;                                         // 0x016dcd54

struct AutoRefAvatar {
    void* mpObject;                                                       // +0x00
    AutoRefAvatar() : mpObject(0) {}
    ~AutoRefAvatar() { if (mpObject) ((IRefCounted*)mpObject)->r01(); }
};
struct AutoRefStrategy {
    void* mpObject;                                                       // +0x00
    AutoRefStrategy() : mpObject(0) {}
    // Release: call vtable slot 8 of the sub-object whose vptr sits at
    // object+0x3c (ecx = object+0x3c).
    ~AutoRefStrategy() {
        if (mpObject) {
            unsigned char* p = (unsigned char*)mpObject + 0x3c;
            (*(void (__thiscall**)(void*))(*(char**)p + 8))(p);
        }
    }
};

struct IStream { virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void* v06(); virtual void v07(); virtual void* v08();
    virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12(); };
struct cVarListSerializer {
    unsigned char mData[0xa14];
    cVarListSerializer(void* owner, const char* name, unsigned id);       // 0x00692f90
    void Serialize(void* stream);                                         // 0x00692900
};
void EA_IO_WriteUint32(void* stream, void* buf, int count, int flags);   // 0x0093aa70
extern const char g_sFieldName_015b6d4c[];                                // 0x015b6d4c

struct cSPSimulatorWalkAround : cGonzagoSimulator {
    unsigned char   mIsWalkingAround;                                     // +0x10
    unsigned char   pad11[3];
    AutoRefAvatar   mWalkAroundAvatar;                                    // +0x14
    AutoRefStrategy mWalkAroundStrategy;                                  // +0x18
    int             mBeamingState;                                        // +0x1c
    cGonzagoTimer   mBeamingTimer;                                        // +0x20
    float           mRescueDelay;                                         // +0x40
    int             m44;                                                  // +0x44
    ObjVector       mPlants;                                              // +0x48
    unsigned char   pad54[8];
    ObjVector       mPlantObstacles;                                      // +0x5c

    cSPSimulatorWalkAround();                                             // 0x010164d0
    void     SetRescueDelay(float v);                                     // 0x01015f30
    void     Write(IStream* s);                                           // 0x01015e30
    void     ResetState();                                                // 0x01015f50
    int      FindPlantValue(int key);                                     // 0x01015fa0
    unsigned char QueryBeamingFlag(IRefBut34* p);                         // 0x01016470
    void     GetOutOfUFO();                                               // 0x01016070
    ~cSPSimulatorWalkAround();                                            // 0x01015fe0
    virtual void a0();
    virtual void b0();
};

void cSPSimulatorWalkAround::a0() {}
void cSPSimulatorWalkAround::b0() {}

// @ 0x010164d0  SP::cSPSimulatorWalkAround::cSPSimulatorWalkAround
cSPSimulatorWalkAround::cSPSimulatorWalkAround()
    : mIsWalkingAround(0), mBeamingState(0), mRescueDelay(0.0f), m44(0)
{
    mPlants.reserve8(8);
    mPlantObstacles.reserve8(8);
    gWalkAroundInstance = this;
}

// @ 0x01015f30
void cSPSimulatorWalkAround::SetRescueDelay(float v)
{
    mRescueDelay = v;
    mBeamingState = 1;
}

// @ 0x01015e30  SP::cSPSimulatorWalkAround::Write
void cSPSimulatorWalkAround::Write(IStream* s)
{
    IStream* a = (IStream*)s->v08();
    unsigned v = 0x2f404e9u;
    void* b = a->v06();
    EA_IO_WriteUint32(b, &v, 1, 0);
    cVarListSerializer ser((void*)((char*)this - 8), g_sFieldName_015b6d4c, 0x1a80d26u);
    ser.Serialize(s);
}

// @ 0x01015f50
void cSPSimulatorWalkAround::ResetState()
{
    ((ITicker*)SP::SimTicker())->t20(this);
    mIsWalkingAround = 0;
    if (mWalkAroundAvatar.mpObject) {
        void* a = mWalkAroundAvatar.mpObject;
        mWalkAroundAvatar.mpObject = 0;
        (*(void (__thiscall**)(void*))(*(char**)a + 4))(a);
    }
    if (mWalkAroundStrategy.mpObject) {
        void* s = mWalkAroundStrategy.mpObject;
        unsigned char* p = (unsigned char*)s + 0x3c;
        mWalkAroundStrategy.mpObject = 0;
        (*(void (__thiscall**)(void*))(*(char**)p + 8))(p);
    }
    mBeamingState = 0;
    m44 = 0;
    mRescueDelay = 0.0f;
}

// @ 0x01015fa0
int cSPSimulatorWalkAround::FindPlantValue(int key)
{
    int n = (int)((char*)mPlantObstacles.mpEnd - (char*)mPlantObstacles.mpBegin) >> 2;
    if (n > 0) {
        int* p = (int*)mPlantObstacles.mpBegin;
        int i = 0;
        do {
            if (*p == key)
                return ((int*)mPlants.mpBegin)[i];
            ++i; ++p;
        } while (i < n);
    }
    return 0;
}

// @ 0x01016470
unsigned char cSPSimulatorWalkAround::QueryBeamingFlag(IRefBut34* p)
{
    int* e = (int*)mPlantObstacles.mpEnd;
    int* b = (int*)mPlantObstacles.mpBegin;
    if (b != e) {
        do { if (*b == (int)(size_t)p) break; ++b; } while (b != e);
        if (b != e)
            return (unsigned char)(p->v11() == 0);
    }
    return (unsigned char)((p->mField34 >> 1) & 1u);
}

// ---- externs/types for GetOutOfUFO (0x01016070) ---------------------------
struct IGameplayMgr20 { unsigned char pad[0x20]; int mField20; };        // 0x00b3d310 result
struct IInputMgr { virtual void i00(); virtual void i01(); virtual void i02(); virtual void i03();
    virtual void i04(void* a, int b, int c);      // slot 0x10
    virtual void i05(); virtual void i06(); virtual void i07();
    virtual void i08(void* a, int b, int c); };   // slot 0x20
struct ILocaleMap { virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03();
    virtual void l04(); virtual void* l05(void* w); };                    // slot 0x14
struct IInventory { virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11(); // 0x2c
    virtual void v12(); virtual void v13(); };                            // 0x30
struct IViewer { virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(); virtual void w05(); virtual void w06(); virtual IViewer* w07(); // slot 0x1c
    virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13(); virtual int w14(); };         // slot 0x38
struct IApp { virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual IViewer* p20(); };                                            // slot 0x50
struct IEffects { virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
    virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07(); virtual void e08();
    virtual void e09(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13();
    virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18();
    virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23();
    virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28();
    virtual void e29(); virtual void e30(); virtual void e31(); virtual void e32(); virtual void e33();
    virtual void e34(); virtual void e35(); virtual void e36(); virtual void e37(); virtual void e38(void* a, int b); // 0x98
};
struct IAudioSys { virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07(); virtual void* s08(); }; // 0x20

void*  FUN_00b3d310();                                                    // 0x00b3d310
IInputMgr* SP_GameInputManager();                                         // 0x00b3d250
void*  FUN_0067de40();                                                    // 0x0067de40
bool   FUN_006ab760(void* map);                                          // 0x006ab760
void*  operator_new_120(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
struct IStrategyCtor { IStrategyCtor* ctor(); };
IStrategyCtor* FUN_0107c0b0();                                            // 0x0107c0b0
void*  SP_NounManager0();                                                 // 0x00b3d300
bool   FUN_00685520(int flag);                                            // 0x00685520
void*  FUN_01021300();                                                    // 0x01021300
void*  FUN_00c30f90(void* empire);                                        // 0x00c30f90
void*  FUN_00401090(void* p);                                             // 0x00401090
void*  FUN_004df550(void* p);                                             // 0x004df550
void*  FUN_00c30c80(void* empire);                                        // 0x00c30c80
void*  SP_GetUFOSimulator();                                              // 0x00ffbe50
void*  FUN_00a1ad60(void* sim);                                           // 0x00a1ad60 (GetPlayerInventory)
void*  SP_PlanetModel(void* out, void* val);                             // 0x00b3d350
void*  FUN_00b815a0(void* pm, void* out, void* val);                      // 0x00b815a0
void*  FUN_00b3d300(void* out, void* key, int c, int d, int e, int f);   // 0x00b3d300
struct NounMgr {
    void* find(void* out, void* key);                                     // 0x00b23940
};
struct FoundObj {
    void set(int a);                                                      // 0x00c6ace0
};
void*  FUN_00b1fdb0(void* nm);                                            // 0x00b1fdb0 (GetAvatar)
void   FUN_00c042e0(void* avatar);                                        // 0x00c042e0
void*  SP_App();                                                          // 0x0067dd10
void*  FUN_00b3d230(int id);                                              // 0x00b3d230 (ret 4)
void   FUN_00b5cde0(void* p);                                             // 0x00b5cde0
void   FUN_00d26ed0(void* cam, void* a, void* b, float x, float y, float z); // 0x00d26ed0
void   FUN_00d25ca0(float f);                                             // 0x00d25ca0
void*  FUN_010666a0();                                                    // 0x010666a0
void   FUN_01065c30(int a);                                               // 0x01065c30
void*  SP_SpaceGameGet();                                                 // 0x01002bd0
void   FUN_01003480();                                                    // 0x01003480
void*  FUN_00b3d3c0(int a);                                               // 0x00b3d3c0
void   FUN_00b7c160(void* p);                                             // 0x00b7c160
IEffects* SP_EffectsManager();                                            // 0x0067ddd0
void*  FUN_01005180(int a);                                               // 0x01005180
void*  FUN_00f67d90(void* noun);                                          // 0x00f67d90
bool   FUN_00c772c0(void* a);                                             // 0x00c772c0
bool   FUN_00c77bf0(void* a);                                             // 0x00c77bf0
void   FUN_0106dcd0(void* a);                                             // 0x0106dcd0
void*  FUN_0067cac0(int a, int b);                                        // 0x0067cac0
void   FUN_0067c420(void* a, int b);                                      // 0x0067c420
IAudioSys* EA_Audio_GetSystemAT();                                       // 0x00a206f0
void   Start3dSoundByName(void* p, int a, float x, float y, float z);     // 0x00571f80
void*  FUN_010408b0();                                                    // 0x010408b0
void   FUN_010414c0(void* a);                                             // 0x010414c0
void   FUN_007c3d30(void* viewer, void* a, void* b, void* c, int d);     // 0x007c3d30
void*  FUN_0069b600(void* out, void* a, void* b);                         // 0x0069b600

// @ 0x01016070
void cSPSimulatorWalkAround::GetOutOfUFO()
{
    mIsWalkingAround = 1;
    mBeamingState = 3;
    ((IGameplayMgr20*)FUN_00b3d310())->mField20 = 1;
    if (mWalkAroundStrategy.mpObject == 0) {
        IInputMgr* im = SP_GameInputManager();
        im->i04((void*)0x14958dc, 0, 1);                     // "TriggerConfigWalkAround"
        const char* cfg = (const char*)0x1477770;            // "TriggerConfigWASD"
        ILocaleMap* lm = (ILocaleMap*)FUN_0067de40();
        void* h = lm->l05((void*)0x1403c98);                 // L"fr-fr"
        if (FUN_006ab760(h))
            cfg = (const char*)0x1477758;                    // "TriggerConfigWASD_fr-fr"
        im = SP_GameInputManager();
        im->i04((void*)cfg, 0, 0);
        void* mem = operator_new_120(0x120, (const char*)0x13f09b4, 0, 0, 0, 0); // "Simulator"
        void* newStrat = mem ? (void*)((IStrategyCtor*)mem)->ctor() : 0;
        void* oldStrat = mWalkAroundStrategy.mpObject;
        if (newStrat != oldStrat) {
            if (newStrat) {
                unsigned char* p = (unsigned char*)newStrat + 0x3c;
                (*(void (__thiscall**)(void*))(*(char**)p + 4))(p);
            }
            mWalkAroundStrategy.mpObject = newStrat;
            if (oldStrat) {
                unsigned char* p = (unsigned char*)oldStrat + 0x3c;
                (*(void (__thiscall**)(void*))(*(char**)p + 8))(p);
            }
        }
        void* st = mWalkAroundStrategy.mpObject;
        (*(void (__thiscall**)(void*))(*(char**)st + 4))(st);
        (*(void (__thiscall**)(void*))(*(char**)st + 8))(st);
        IInputMgr* im2 = SP_GameInputManager();
        im2->i08((unsigned char*)mWalkAroundStrategy.mpObject + 4, 0, 0);
    }
    SP_NounManager0();
    if (mWalkAroundAvatar.mpObject == 0) {
        void* key;
        if (FUN_00685520(2)) {
            void* empire = FUN_01021300();
            key = FUN_00c30f90(empire);
            void* t = FUN_00401090(key);
            key = FUN_004df550(t);
        } else {
            void* empire = FUN_01021300();
            key = FUN_00c30c80(empire);
        }
        void* inv = FUN_00a1ad60(SP_GetUFOSimulator());
        void* pos = (*(void* (__thiscall**)(void*))(*(char**)((unsigned char*)inv + 0x34) + 0x2c))((unsigned char*)inv + 0x34);
        unsigned char out[12];
        void* pm = SP_PlanetModel(out, pos);
        FUN_00b815a0(pm, out, pos);
        void* nm = FUN_00b3d300(out, key, 0, 1, 0, 0);
        void* found = ((NounMgr*)nm)->find(out, key);
        if (found) {
            ((FoundObj*)found)->set(1);
            void* av = FUN_00b1fdb0(SP_NounManager0());
            void* oldAv = mWalkAroundAvatar.mpObject;
            if (av != oldAv) {
                if (av)
                    (*(void (__thiscall**)(void*))(*(char**)av + 0))(av);
                mWalkAroundAvatar.mpObject = av;
                if (oldAv)
                    (*(void (__thiscall**)(void*))(*(char**)oldAv + 4))(oldAv);
            }
            if (mWalkAroundAvatar.mpObject != 0) {
                void* inv2 = FUN_00a1ad60(SP_GetUFOSimulator());
                void* avp = mWalkAroundAvatar.mpObject;
                void* slot = (void*)(*(void* (__thiscall**)(void*))(*(char**)((unsigned char*)inv2 + 0x34) + 0x30))((unsigned char*)inv2 + 0x34);
                (*(void (__thiscall**)(void*, void*))(*(char**)((unsigned char*)avp + 0xc0) + 0x3c))((unsigned char*)avp + 0xc0, slot);
                FUN_00c042e0(avp);
                *(unsigned*)((unsigned char*)avp + 0x2b0) = 0;
                void* inner = *(void**)((unsigned char*)avp + 0xb54);
                *(unsigned char*)((unsigned char*)(*(void**)((unsigned char*)inner + 0x17c)) + 0x270) = 0;
            }
        }
    }
    IApp* app = (IApp*)SP_App();
    IViewer* vw = app->p20()->w07();
    unsigned char v40[12], v1c[12], v28[12], v10[16];
    FUN_007c3d30(vw, v40, v1c, v28, 0);
    FUN_0069b600(v10, v1c, v28);
    void* qbond = FUN_00b3d230(0xb03af999);
    FUN_00b5cde0(qbond);
    IApp* app2 = (IApp*)SP_App();
    IViewer* vw2 = app2->p20();
    void* cam = 0;
    if (vw2->w14())
        cam = (*(void* (__thiscall**)(IViewer*, unsigned))(*(char**)vw2 + 0xc))(vw2, 0x2a7ecd2u);
    if (vw && cam) {
        FUN_00d26ed0(cam, v40, v10, 0.0f, 0.0f, 0.0f);
        FUN_00d25ca0(12.0f);
    }
    void* ui = FUN_010666a0();
    if (ui) {
        FUN_01065c30(0);
        SP_SpaceGameGet();
        FUN_01003480();
    }
    SP_SpaceGameGet();
    FUN_01005180(0xd);
    (void)FUN_00b3d3c0(7);
    FUN_00b7c160(0);
    IEffects* fx = SP_EffectsManager();
    fx->e38((void*)0x11, 1);
    fx = SP_EffectsManager();
    fx->e38((void*)0x14, 0);
    void* noun = SP_NounManager0();
    void* te = FUN_00f67d90(noun);
    if (FUN_00c772c0(te)) {
        void* noun2 = SP_NounManager0();
        void* te2 = FUN_00f67d90(noun2);
        FUN_00c77bf0(te2);
        FUN_0106dcd0(FUN_010666a0());
    }
    FUN_0067c420(FUN_0067cac0(0, 1), 1);
    IAudioSys* au = EA_Audio_GetSystemAT();
    void* ref = au ? au->s08() : 0;
    m44 = (int)(size_t)ref;
    Start3dSoundByName(ref, 0, 0.0f, 0.0f, 0.0f);
    FUN_010408b0();
    FUN_010414c0(0);
}

// @ 0x01015fe0
cSPSimulatorWalkAround::~cSPSimulatorWalkAround()
{
    gWalkAroundInstance = 0;
    // Member destructors (mPlantObstacles, mPlants, mBeamingTimer, then the
    // AutoRef avatar/strategy) and the cGonzagoSimulator base run after this body.
}
