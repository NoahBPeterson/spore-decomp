// s01000740 — SP::cSPSimulatorPlayerUFO (ctor / dtor / Shutdown / UpdateUFO /
// BuildStarRecords + FUN_01000dc0).  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <stddef.h>
#include <string.h>
#include <math.h>

#pragma warning(disable: 4100 4244 4312 4996)

// ===========================================================================
// low-level dispatch helpers
// ===========================================================================
#define VT(p) (*(void***)(p))

// ===========================================================================
// container / value stubs
// ===========================================================================
struct Vec {                 // eastl::vector, 0x14 bytes
    void*    mpBegin;        // 0x00
    void*    mpEnd;          // 0x04
    void*    mpCapacity;     // 0x08
    uint32_t mAlloc0;        // 0x0c
    uint32_t mAlloc1;        // 0x10

    void  Reserve(uint32_t n);                        // 0x4e0880
    void  DoDestroyValues(void* first, void* last);   // 0x5f3680
};

struct ListHead {            // eastl::list node base, 0x10 bytes (only 8 used)
    void*    mpNext;         // 0x00
    void*    mpPrev;         // 0x04
    uint32_t mSize;          // 0x08
    uint32_t mPad0;          // 0x0c
};

// model-world instance (SP::cMWModel)
class cMWModel {
public:
    uint32_t mpVftable;       // 0x00
    int32_t  field_04;        // 0x04
    uint16_t field_08;        // 0x08  flags (bit 4 set once a civ is bound)
    uint16_t field_0a;        // 0x0a  count
    int32_t  field_0c;        // 0x0c
    int32_t  field_10;        // 0x10
    int32_t  field_14;        // 0x14
    float    field_18;        // 0x18
    uint32_t mData_1c[9];     // 0x1c  (9 dwords copied from DAT_016dc0a4)
    int32_t  mRefCount;       // 0x40
    uint32_t pad_44[8];       // 0x44
    void*    mpOwner_64;      // 0x64  (bound cCivData*)
};

struct cGonzagoTimer {
    uint32_t mpVftable;       // 0x00
    uint32_t pad_04[7];       // 0x04..0x1f

    void ctor();              // 0xb63890
    void dtor();              // 0xb638b0
    void Start();             // 0xbc30f0
};

// UFO noun (SP::cSPGameDataUFO) — embedded transform at 0x34, tool at 0x508
class cGameDataUFO {
public:
    uint32_t pad_00[0x34 / 4];      // 0x00..0x33
    uint32_t mTransform_34;         // 0x34  (embedded transform: its vftable ptr)
    uint8_t  pad_38[0x508 - 0x38];  // 0x38..0x507
    uint32_t mTool_508;             // 0x508 (embedded tool: its vftable ptr)
    uint8_t  pad_50c[0x714 - 0x50c];// 0x50c..0x713
    int32_t  mNounType_714;         // 0x714
    float    mPosition_718[3];      // 0x718
    uint8_t  pad_724[0x76c - 0x724];// 0x724..0x76b
    int32_t  mState_76c;            // 0x76c
};

// civ record (SP::cCivData)
struct cCivData {
    float mPosition_00[3];    // 0x00..0x0b  (world position; passed to FUN_01000660)
    void* GetCities();        // 0x5c65e0  (returns this + 0x3c)
};

// property value node (SP::cProperty)
struct cProperty {
    uint32_t mValue;          // 0x00
    uint32_t pad_04[3];       // 0x04..0x0f
    uint8_t  mFlags;          // 0x10  (bit 0x30 => indirect)
    uint8_t  pad_11;          // 0x11
    uint16_t mType;           // 0x12
};

// ===========================================================================
// interface stubs (vtable shapes only; never instantiated)
// ===========================================================================
struct cSPSimulatorSpaceGame {
    void* GetPlayerInventory();          // 0xa1ad60
};

struct cSPPlayerInventory {
    void* GetToolFromToolID(const void* key);  // 0xff3d40
};

struct cStarManager {
    void* GetEmpireByID(int id);                          // 0xba9370
    void  GetStarRecords(cCivData* civ, void* filter, void* outVec); // 0xbb1080
};

struct cGameNounManager {
    void** GetGameDataVectorPtr();       // 0xad49b0
    void   RemoveNoun(void* noun);       // 0xb225d0
};

struct cEmpire {
    bool IsHostileToPlayer();            // 0xc309e0
};

struct cHomePlanet {
    cCivData* GetCivData();              // 0xb8de30
};

// IPropertyManager: slot 0x2c == GetProperty
struct IPropertyManager {
    virtual void  pad00(); virtual void  pad04(); virtual void  pad08();
    virtual void  pad0c(); virtual void  pad10(); virtual void  pad14();
    virtual void  pad18(); virtual void  pad1c(); virtual void  pad20();
    virtual void  pad24(); virtual void  pad28();
    virtual void  GetProperty(uint32_t key, uint32_t name, void** out);  // 0x2c
};

// IPropertyHolder (property list): slot 0x24 == GetValue
struct IPropertyHolder {
    virtual void  pad00(); virtual void  pad04(); virtual void  pad08();
    virtual void  pad0c(); virtual void  pad10(); virtual void  pad14();
    virtual void  pad18(); virtual void  pad1c(); virtual void  pad20();
    virtual bool  GetValue(uint32_t key, void** out);            // 0x24
};

struct cSPToolManager {
    void PlayerUseToolStart();           // 0x1050bb0
};

// ===========================================================================
// free-function callees (name + annotation so the resolver maps them)
// ===========================================================================
void*  SP_SpaceGameGet(const void* key);      // 0x1002bd0
void*  SP_GetPlayerHomePlanet();              // 0x1021370
int    SP_GetPlayerEmpireID();                // 0x1021090
void*  SP_GetUniverseContext();               // 0x1021080
bool   SP_PlayerHasAnyAutoblaster();          // 0x10299c0
void*  SP_GetPropertyAsVector3(void* plist, uint32_t id, void* out); // 0x6a1110
void   SP_RemoveHandler(void* handler, void* a, void* b, void* c, void* d); // 0x571db0

void*  SP_ModelManager();                     // 0x67dd80
void*  SP_PropertyManager();                  // 0x67de30
void*  SP_NounManager();                      // 0xb3d300
void*  SP_StarManager();                      // 0xb3d2a0
void*  SP_SimTicker();                        // 0xb3d330

void*  SP_NormalizedSafe(void* out, const void* src, int flags); // 0x449c20
void*  FUN_00b3d390(void* a, void* b);        // 0xb3d390
void   FUN_01000660(void* begin, void* end, float x, float y, float z); // 0x1000660

void*  VecDoCopy(void* first, void* last, void* dest);           // 0x5f4e10
void   CountedPtrVecDoInsert(void* end, void* value);           // 0x423c40
void   EAllocDelete(void* p);                 // 0xf47380
void*  EAllocNew(uint32_t size, const char* name, uint32_t a, uint32_t b,
                 const char* file, uint32_t line);               // 0xf473a0

// function-pointer immediates passed to GetGameDataVector
#define FUN_00cd7d10 ((void*)0xcd7d10)
#define FUN_00d3d420 ((void*)0xd3d420)
#define FUN_00ad48b0 ((void*)0xad48b0)
#define FUN_00b1e500 ((void*)0xb1e500)

// ===========================================================================
// global data
// ===========================================================================
class cSPSimulatorPlayerUFO;                       // fwd

extern uint32_t g_016dc004;                        // 0x016dc004
extern uint32_t g_016dc0a4[9];                     // 0x016dc0a4
extern int32_t  g_016dba18;                        // 0x016dba18
extern int32_t  g_016dba1c;                        // 0x016dba1c
extern int32_t  g_016dba20;                        // 0x016dba20
extern float    g_013ef548;                        // 0x013ef548
extern float    g_014950e0;                        // 0x014950e0

extern cSPSimulatorPlayerUFO* g_016dba14;          // 0x016dba14

// ===========================================================================
// the player-UFO simulator (layout ASSERT_SIZE 0xE0)
// ===========================================================================
class cSPSimulatorPlayerUFO {
public:
    // ---- behaviour implementing this slice ----
    cSPSimulatorPlayerUFO();                 // 0x1000740
    ~cSPSimulatorPlayerUFO();                // 0x1000bb0
    void Shutdown();                         // 0x1001110
    void UpdateUFO();                        // 0x1000eb0
    void BuildStarRecords(cCivData* civ);    // 0x1001360

    // ---- declared elsewhere in the original binary ----
    void OnContextChange(uint32_t ctx);      // 0xffe130
    void SetTarget(int a, void* b);          // 0xffd710

    // ---- data ----
    uint32_t mpVftable0;       // 0x00
    uint32_t field_04;         // 0x04
    uint32_t mpVftable1;       // 0x08
    uint32_t field_0C;         // 0x0c
    uint32_t mpVftable2;       // 0x10
    uint8_t  mUIButton_ZoomIn; // 0x14
    uint8_t  mUIButton_ZoomOut;// 0x15
    uint8_t  mUIButton_Left;   // 0x16
    uint8_t  mUIButton_Right;  // 0x17
    uint8_t  field_18;         // 0x18
    uint8_t  pad_19[3];        // 0x19
    uint32_t field_1C;         // 0x1c
    uint8_t  field_20;         // 0x20
    uint8_t  pad_21[3];        // 0x21
    uint32_t field_24;         // 0x24
    uint8_t  field_28;         // 0x28
    uint8_t  pad_29[3];        // 0x29
    void*    mAutoHandler_2C;  // 0x2c
    void*    mAutoHandler_30;  // 0x30
    void*    mAutoHandler_34;  // 0x34
    void*    mAutoHandler_38;  // 0x38
    void*    mAutoHandler_3C;  // 0x3c
    void*    mpPlayerUFO;      // 0x40  (cGameDataUFO*)
    void*    field_44;         // 0x44
    float    mMaxDistance;     // 0x48
    float    mMaxScanDistance; // 0x4c
    float    field_50;         // 0x50
    uint8_t  field_54;         // 0x54
    uint8_t  field_55;         // 0x55
    uint8_t  field_56;         // 0x56
    uint8_t  pad_57;           // 0x57
    Vec      mHitSpheres;      // 0x58
    void*    mpModelWorld_6C;  // 0x6c  (cMWModel*)
    ListHead mPosseUFOList;    // 0x70
    cGonzagoTimer mIdleTimer;  // 0x80
    int32_t  field_A0;         // 0xa0
    void*    field_A4;         // 0xa4
    void*    field_A8;         // 0xa8
    void*    field_AC;         // 0xac
    void*    field_B0;         // 0xb0
    void*    field_B4;         // 0xb4
    float    field_B8;         // 0xb8
    float    field_BC;         // 0xbc
    float    field_C0;         // 0xc0
    float    field_C4;         // 0xc4
    float    field_C8;         // 0xc8
    uint32_t field_CC;         // 0xcc
    void*    field_D0;         // 0xd0
    void*    field_D4;         // 0xd4
    void*    field_D8;         // 0xd8
    void*    field_DC;         // 0xdc
};

// ===========================================================================
// shared small helpers (inlined in the original)
// ===========================================================================
static void RefAssign(void** field, void* src)
{
    void* old = *field;
    if (src == old) return;
    if (src) ((void(__thiscall*)(void*))VT(src)[0])(src);
    *field = src;
    if (old) ((void(__thiscall*)(void*))VT(old)[1])(old);
}

static void ReleaseClear1(void** field)
{
    void* p = *field;
    if (p) {
        *field = 0;
        ((void(__thiscall*)(void*))VT(p)[1])(p);
    }
}

static void ReleaseClear64(void** field)
{
    void* p = *field;
    if (p) {
        *field = 0;
        ((void(__thiscall*)(void*))VT(p)[0x64 / 4])(p);
    }
}

static void Release1(void** field)
{
    void* p = *field;
    if (p) ((void(__thiscall*)(void*))VT(p)[1])(p);
}

static void Release64(void** field)
{
    void* p = *field;
    if (p) ((void(__thiscall*)(void*))VT(p)[0x64 / 4])(p);
}

static void ReleaseChecked(void** field)
{
    void* p = *field;
    if (p && ((bool(__thiscall*)(void*))VT(p)[0x10 / 4])(p))
        ((void(__thiscall*)(void*, int))VT(p)[0x0c / 4])(p, 1);
    ReleaseClear1(field);
}

static void VecClear(Vec* v)
{
    void* b = v->mpBegin;
    void* e = v->mpEnd;
    void* r = VecDoCopy(e, e, b);
    v->DoDestroyValues(r, v->mpEnd);
    int n = (int)((char*)e - (char*)b) >> 2;   // element count (sar 2)
    n = -n;                                    // neg
    n += n; n += n;                            // *4 (two adds)
    v->mpEnd = (char*)v->mpEnd + n;
}

// A created-model instance is a two-level object: [inst] is the primary subobject that owns
// the vtable, while `inst` itself is passed as the first explicit argument.
static void ModelSlot16c(void* m, int flag)
{
    ((void(__thiscall*)(void*, void*, int))(*(void***)(*(void***)m))[0x16c / 4])(*(void**)m, m, flag);
}

static void ModelReleaseTmp(cMWModel* m)
{
    if (m->mRefCount <= 1) {
        int flag = (int)((uint32_t)m->field_04 >> 31);
        ((void(__thiscall*)(void*, void*, int))(*(void***)(*(void***)m))[0x170 / 4])(*(void**)m, m, flag);
    } else {
        m->mRefCount -= 1;
    }
}

// free a hit-sphere entry's owner reference and re-flag the model
static void DestroyHitSphereOwner(cMWModel* m)
{
    void* owner = m->mpOwner_64;
    if (owner) {
        m->mpOwner_64 = 0;
        ((void(__thiscall*)(void*))VT(owner)[1])(owner);
    }
}

// ===========================================================================
// FUN_01000dc0 — "tool selected on the UFO noun"
// ===========================================================================
// @ 0x01000dc0
void FUN_01000dc0(void)
{
    void* sg = SP_SpaceGameGet((void*)0x16dbf04);
    void* inv = ((cSPSimulatorSpaceGame*)sg)->GetPlayerInventory();
    void* tool = ((cSPPlayerInventory*)inv)->GetToolFromToolID((void*)0x16dbf04);
    if (tool == 0) return;
    if (((bool(__thiscall*)(void*))0x104ff10)(tool)) return;

    int empireID = SP_GetPlayerEmpireID();

    void* nm = SP_NounManager();
    char* vec = (char*)((void*(__thiscall*)(void*, void*, void*, void*, void*, void*))0xb21340)
                    (nm, FUN_00cd7d10, FUN_00d3d420, FUN_00ad48b0, FUN_00b1e500, (void*)0x18ebadc);
    void** begin = *(void***)(vec + 4);
    int count = (int)((*(char**)(vec + 8) - (char*)begin) >> 2);

    for (int i = 0; i < count; ++i) {
        cGameDataUFO* noun = (cGameDataUFO*)begin[i];
        if (noun == 0) continue;
        if (noun->mNounType_714 != 3) continue;
        if (((int(__thiscall*)(void*))VT(noun)[0x4c / 4])(noun) != empireID) continue;

        void* toolp = &noun->mTool_508;
        float buf[3];
        void* t = SP_NormalizedSafe(buf, noun->mPosition_718, 0);
        ((void(__thiscall*)(void*, float, int, int, void*, int))VT(toolp)[0x18 / 4])
            (toolp, g_013ef548, -1, 0, t, 0);
        return;
    }
}

// ===========================================================================
// ctor @ 0x01000740
// ===========================================================================
cSPSimulatorPlayerUFO::cSPSimulatorPlayerUFO()
{
    ((void(__thiscall*)(void*))0xb5b6c0)(this);        // cGonzagoSimulator::cGonzagoSimulator

    mpVftable2 = 0x13eb394;
    mpVftable0 = 0x14951c4;
    mpVftable1 = 0x14951a0;
    mpVftable2 = 0x1495198;

    mUIButton_ZoomIn  = 0;
    mUIButton_ZoomOut = 0;
    mUIButton_Left    = 0;
    mUIButton_Right   = 0;
    field_18 = 0;
    field_1C = 0;
    field_20 = 0;
    field_24 = 0;
    field_28 = 0;
    mAutoHandler_2C = 0;
    mAutoHandler_30 = 0;
    mAutoHandler_34 = 0;
    mAutoHandler_38 = 0;
    mAutoHandler_3C = 0;
    mpPlayerUFO = 0;
    field_44 = 0;
    field_50 = 0.0f;
    field_54 = 0;
    field_55 = 0;
    field_56 = 1;
    mHitSpheres.mpBegin = 0;
    mHitSpheres.mpEnd = 0;
    mHitSpheres.mpCapacity = 0;
    mpModelWorld_6C = 0;
    mPosseUFOList.mpNext = &mPosseUFOList.mpNext;
    mPosseUFOList.mpPrev = &mPosseUFOList.mpNext;
    mIdleTimer.ctor();
    field_A0 = 0;
    field_A4 = 0;
    field_A8 = 0;
    field_AC = 0;
    field_B0 = 0;
    field_B4 = 0;
    field_B8 = 1.0f;
    field_BC = 0.75f;
    field_C0 = 50.0f;
    field_C4 = 50.0f;
    field_C8 = 50.0f;
    field_CC = 0;
    field_D0 = 0;
    field_D4 = 0;
    field_D8 = 0;
    field_DC = 0;

    g_016dba14 = this;

    // --- build the "StarPickingSpheres" model world ---
    void* mm = SP_ModelManager();
    cMWModel* world = ((cMWModel*(__thiscall*)(void*, uint32_t, const char*, uint32_t))VT(mm)[0x14 / 4])
                          (mm, 0x56723400, "StarPickingSpheres", 0);
    RefAssign(&mpModelWorld_6C, world);

    VecClear(&mHitSpheres);
    mHitSpheres.Reserve(1000);

    for (int remaining = 1000; remaining != 0; --remaining) {
        cMWModel* m = ((cMWModel*(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))
                           VT(mpModelWorld_6C)[0x0c / 4])(mpModelWorld_6C, 0x2e81370, g_016dc004, 0x10);
        for (int k = 0; k < 9; ++k) m->mData_1c[k] = g_016dc0a4[k];
        m->field_18 = 1.0f;
        m->field_0c = g_016dba18;
        m->field_10 = g_016dba1c;
        m->field_08 = 0;
        m->field_14 = g_016dba20;
        m->field_0a = 0;

        ModelSlot16c(m, 0);
        m->mRefCount += 1;

        if ((char*)mHitSpheres.mpEnd < (char*)mHitSpheres.mpCapacity) {
            *(cMWModel**)mHitSpheres.mpEnd = m;
            mHitSpheres.mpEnd = (char*)mHitSpheres.mpEnd + 4;
            m->mRefCount += 1;
        } else {
            cMWModel* tmp = m;
            CountedPtrVecDoInsert(mHitSpheres.mpEnd, &tmp);
            m = tmp;
        }
        if (m) ModelReleaseTmp(m);
    }

    mIdleTimer.Start();

    // --- read tunable properties ---
    void* holder1 = 0;
    void* holder2 = 0;
    cProperty* prop = 0;

    void* pm = SP_PropertyManager();
    ((IPropertyManager*)pm)->GetProperty(0xc63dfdba, 0x522de06, &holder1);
    if (holder1 != 0) {
        if (((IPropertyHolder*)holder1)->GetValue(0x5a71ab3, (void**)&prop) && prop->mType == 9) {
            cProperty* p = prop;
            if (p->mFlags & 0x30) p = (cProperty*)p->mValue;
            field_A0 = (int32_t)p->mValue;
        }
    }
    field_A0 = field_A0 * 1000;

    pm = SP_PropertyManager();
    if (field_A4 != 0) {
        void* c = field_A4;
        field_A4 = 0;
        ((void(__thiscall*)(void*))VT(c)[1])(c);
    }
    ((IPropertyManager*)pm)->GetProperty(0x521d0174, 0x2ae0c7e, &field_A4);

    pm = SP_PropertyManager();
    if (holder2 != 0) {
        void* c = holder2;
        holder2 = 0;
        ((void(__thiscall*)(void*))VT(c)[1])(c);
    }
    ((IPropertyManager*)pm)->GetProperty(0x272ddeda, 0x2ae0c7e, &holder2);

    if (holder2 != 0) {
        if (((IPropertyHolder*)holder2)->GetValue(0x5dffaa8, (void**)&prop) && prop->mType == 0xd) {
            cProperty* p = prop;
            if (p->mFlags & 0x30) p = (cProperty*)p->mValue;
            field_B8 = *(float*)&p->mValue;
        }
        if (((IPropertyHolder*)holder2)->GetValue(0x5dffabe, (void**)&prop) && prop->mType == 0xd) {
            cProperty* p = prop;
            if (p->mFlags & 0x30) p = (cProperty*)p->mValue;
            field_BC = *(float*)&p->mValue;
        }
    }
    SP_GetPropertyAsVector3(holder2, 0x5dffb15, &field_C0);

    if (prop != 0) {
        void* c = prop;
        ((void(__thiscall*)(void*))VT(c)[1])(c);
    }
    if (holder1 != 0) {
        void* c = holder1;
        ((void(__thiscall*)(void*))VT(c)[1])(c);
    }
}

// ===========================================================================
// dtor @ 0x01000bb0
// ===========================================================================
cSPSimulatorPlayerUFO::~cSPSimulatorPlayerUFO()
{
    mpVftable0 = 0x14951c4;
    mpVftable1 = 0x14951a0;
    mpVftable2 = 0x1495198;
    g_016dba14 = 0;

    int n = (int)((char*)mHitSpheres.mpEnd - (char*)mHitSpheres.mpBegin) >> 2;
    for (int i = 0; i < n; ++i) {
        cMWModel* m = ((cMWModel**)mHitSpheres.mpBegin)[i];
        ModelSlot16c(m, 0);
        DestroyHitSphereOwner(m);
    }
    VecClear(&mHitSpheres);

    void* mm = SP_ModelManager();
    ((void(__thiscall*)(void*, uint32_t))VT(mm)[0x18 / 4])(mm, 0x56723400);

    ReleaseClear1(&mpModelWorld_6C);
    Release1(&field_DC);
    Release64(&field_D8);
    Release64(&field_D4);
    Release64(&field_D0);
    Release1(&field_B4);
    Release1(&field_B0);
    Release1(&field_AC);
    Release1(&field_A8);
    Release1(&field_A4);

    mIdleTimer.dtor();

    void* head = &mPosseUFOList.mpNext;
    void* node = mPosseUFOList.mpNext;
    while (node != head) {
        void* nxt = *(void**)node;
        EAllocDelete(node);
        node = nxt;
    }

    Release1(&mpModelWorld_6C);

    mHitSpheres.DoDestroyValues(mHitSpheres.mpBegin, mHitSpheres.mpEnd);
    if (mHitSpheres.mpBegin && ((int*)mHitSpheres.mpBegin)[-1] != 0)
        EAllocDelete(mHitSpheres.mpBegin);

    Release1(&field_44);
    Release1(&mpPlayerUFO);

    if (mAutoHandler_2C) {
        void* h = mAutoHandler_2C;
        mAutoHandler_2C = 0;
        SP_RemoveHandler(h, mAutoHandler_30, mAutoHandler_34, mAutoHandler_38, mAutoHandler_3C);
    }

    mpVftable2 = 0x13eb394;
    mpVftable1 = 0x13eb938;
    mpVftable0 = 0x13ec458;
}

// ===========================================================================
// Shutdown @ 0x01001110
// ===========================================================================
void cSPSimulatorPlayerUFO::Shutdown()
{
    if (mAutoHandler_2C) {
        void* h = mAutoHandler_2C;
        mAutoHandler_2C = 0;
        SP_RemoveHandler(h, mAutoHandler_30, mAutoHandler_34, mAutoHandler_38, mAutoHandler_3C);
    }

    void* ticker = SP_SimTicker();
    ((void(__thiscall*)(void*, void*))VT(ticker)[0x54 / 4])(ticker, this);

    ReleaseClear64(&field_D0);
    ReleaseClear64(&field_D4);
    ReleaseClear64(&field_D8);
    ReleaseClear1(&field_DC);

    if (mpPlayerUFO) {
        void* nm = SP_NounManager();
        ((void(__thiscall*)(void*, void*))0xb225d0)(nm, mpPlayerUFO);
        ReleaseClear1(&mpPlayerUFO);
    }

    int n = (int)((char*)mHitSpheres.mpEnd - (char*)mHitSpheres.mpBegin) >> 2;
    for (int i = 0; i < n; ++i) {
        cMWModel* m = ((cMWModel**)mHitSpheres.mpBegin)[i];
        ModelSlot16c(m, 0);
        DestroyHitSphereOwner(m);
    }
    VecClear(&mHitSpheres);

    void* mm = SP_ModelManager();
    ((void(__thiscall*)(void*, uint32_t))VT(mm)[0x18 / 4])(mm, 0x56723400);

    ReleaseClear1(&mpModelWorld_6C);

    ReleaseChecked(&field_A8);
    ReleaseChecked(&field_AC);
    ReleaseChecked(&field_B0);
    ReleaseChecked(&field_B4);
}

// ===========================================================================
// UpdateUFO @ 0x01000eb0
// ===========================================================================
void cSPSimulatorPlayerUFO::UpdateUFO()
{
    cGameDataUFO* noun = (cGameDataUFO*)g_016dba14->mpPlayerUFO;
    if (noun->mState_76c == 3) return;
    if (!SP_PlayerHasAnyAutoblaster()) return;

    void* tool = &noun->mTool_508;
    void* active = ((void*(__thiscall*)(void*))VT(tool)[0x14 / 4])(tool);
    if (active == 0) {
        uint32_t ctx = (uint32_t)SP_GetUniverseContext();
        g_016dba14->OnContextChange(ctx);
    }
    active = ((void*(__thiscall*)(void*))VT(tool)[0x14 / 4])(tool);
    if (active == 0) return;

    void* d4 = g_016dba14->field_D4;
    void* bestNoun = 0;

    // self noun world position (computed once)
    float* posSelf = ((float*(__thiscall*)(void*))VT(&noun->mTransform_34)[0x2c / 4])(&noun->mTransform_34);

    if (SP_GetUniverseContext() != 0) {
        if (d4 != 0) {
            float maxScan = ((float(__thiscall*)(void*))0x104be30)(active);
            void* inner = ((void*(__thiscall*)(void*))VT(d4)[8 / 4])(d4);
            float* posA = ((float*(__thiscall*)(void*))VT(inner)[0x2c / 4])(inner);
            float a = posSelf[0] - posA[0];
            float b = posSelf[1] - posA[1];
            float c = posSelf[2] - posA[2];
            float dist = (float)sqrt((double)(a * a + b * b + c * c));
            if (dist <= maxScan) goto use_tool;
            g_016dba14->SetTarget(0, 0);
            d4 = 0;
        }
        {
            void* nm = SP_NounManager();
            char* vec = (char*)((void*(__thiscall*)(void*))0xad49b0)(nm);
            void** it = (void**)*(void**)vec;
            void** end = (void**)*((void**)vec + 1);
            float best = g_014950e0;
            for (; it != end; ++it) {
                cGameDataUFO* cand = (cGameDataUFO*)*it;
                if (cand->mNounType_714 != 8) continue;
                if (cand->mState_76c == 3) continue;
                float* posC = ((float*(__thiscall*)(void*))VT(&cand->mTransform_34)[0x2c / 4])
                                  (&cand->mTransform_34);
                float a = posSelf[0] - posC[0];
                float b = posSelf[1] - posC[1];
                float c = posSelf[2] - posC[2];
                float d2 = a * a + b * b + c * c;
                if (!(best > d2)) continue;
                int empID = ((int(__thiscall*)(void*))VT(cand)[0x4c / 4])(cand);
                void* sm = SP_StarManager();
                void* emp = ((void*(__thiscall*)(void*, int))0xba9370)(sm, empID);
                if (emp == 0 || ((bool(__thiscall*)(void*))0xc309e0)(emp)) {
                    best = d2;
                    bestNoun = cand;
                }
            }
        }
        if (bestNoun != 0) {
            g_016dba14->SetTarget((int)(intptr_t)active, &((cGameDataUFO*)bestNoun)->mTool_508);
            d4 = g_016dba14->field_D4;
        }
    }

    if (d4 == 0) return;

use_tool:
    {
        void* inner = ((void*(__thiscall*)(void*))VT(d4)[8 / 4])(d4);
        void* ptr = ((void*(__thiscall*)(void*, int))VT(inner)[0x2c / 4])(inner, 0);
        void* it = FUN_00b3d390(active, ptr);
        ((cSPToolManager*)it)->PlayerUseToolStart();
    }
}

// ===========================================================================
// BuildStarRecords @ 0x01001360
// ===========================================================================
void cSPSimulatorPlayerUFO::BuildStarRecords(cCivData* civ)
{
    int used = 0;
    void* sm = SP_StarManager();
    char* civBegin = *(char**)((char*)sm + 0xf0);
    int civCount = (int)((*(char**)((char*)sm + 0xf4) - civBegin) >> 2);

    for (int i = 0; i < civCount; ++i) {
        cCivData* c = *(cCivData**)(civBegin + i * 4);
        void* home = SP_GetPlayerHomePlanet();
        cCivData* homeCiv = ((cHomePlanet*)home)->GetCivData();
        if (c == homeCiv) continue;

        cMWModel* m = ((cMWModel**)mHitSpheres.mpBegin)[used];
        uint32_t* cities = (uint32_t*)((cCivData*)c)->GetCities();
        m->field_0c = (int32_t)cities[0];
        m->field_10 = (int32_t)cities[1];
        m->field_14 = (int32_t)cities[2];
        m->field_08 |= 4;
        m->field_0a += 1;
        m->field_0a += 1;
        m->field_18 = 0.2f;

        RefAssign(&m->mpOwner_64, c);

        used += 1;
        ModelSlot16c(m, 1);
    }

    // temporary star-record vector, backed by a 1000-entry (4000-byte) block
    Vec v;
    v.mpBegin = 0;
    v.mpEnd = 0;
    v.mpCapacity = 0;
    void* buf = EAllocNew(4000, "Simulator", 0, 0, (const char*)0x13ebb38, 0xd1);
    memcpy(buf, v.mpBegin, (char*)v.mpEnd - (char*)v.mpBegin);
    if (v.mpBegin && ((int*)v.mpBegin)[-1] != 0)
        EAllocDelete(v.mpBegin);
    v.mpEnd = (void**)((char*)buf + ((char*)v.mpEnd - (char*)v.mpBegin));
    v.mpBegin = (void**)buf;
    v.mpCapacity = (void**)buf + 1000;

    uint32_t filter[7];
    filter[0] = 0x1fff;
    filter[1] = 0x3f;
    filter[2] = 0;
    filter[3] = 0xbf800000u;                       // -1.0f
    filter[4] = *(uint32_t*)&mMaxScanDistance;
    filter[5] = 0xbf800000u;                       // -1.0f
    filter[6] = 0;

    ((cStarManager*)sm)->GetStarRecords(civ, filter, &v);

    int count = (int)((char*)v.mpEnd - (char*)v.mpBegin) >> 2;

    if (used + count > 1000)
        FUN_01000660(v.mpBegin, v.mpEnd,
                     civ->mPosition_00[0], civ->mPosition_00[1], civ->mPosition_00[2]);

    int n = 1000 - used;
    if (n > count) n = count;

    for (int i = 0; i < n; ++i) {
        cCivData* c = ((cCivData**)v.mpBegin)[i];
        cMWModel* m = ((cMWModel**)mHitSpheres.mpBegin)[used];
        uint32_t* cities = (uint32_t*)((cCivData*)c)->GetCities();
        m->field_0c = (int32_t)cities[0];
        m->field_10 = (int32_t)cities[1];
        m->field_14 = (int32_t)cities[2];
        m->field_08 |= 4;
        m->field_0a += 1;
        m->field_0a += 1;
        m->field_18 = 0.2f;
        RefAssign(&m->mpOwner_64, c);
        used += 1;
        ModelSlot16c(m, 1);
    }

    for (int i = used * 4; i < 4000; i += 4)
        ModelSlot16c(((cMWModel**)mHitSpheres.mpBegin)[i / 4], 0);

    // release the temporary star-record elements, then the backing block
    for (void** p = (void**)v.mpBegin; p < (void**)v.mpEnd; ++p) {
        void* e = *p;
        if (e) ((void(__thiscall*)(void*))VT(e)[1])(e);
    }
    if (v.mpBegin && ((int*)v.mpBegin)[-1] != 0)
        EAllocDelete(v.mpBegin);
}