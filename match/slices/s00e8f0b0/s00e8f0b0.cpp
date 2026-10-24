// Slice s00e8f0b0 -- 17 Simulator view helpers in the cSpatialObjectView subclass family:
// the cMineralView / cTotemPoleView / cAnimalTrapView / cTribeFoodMatView / cOrnamentView /
// cHitSphereView / cSolarHitSphereView / cInteractableObjectView factories ("MakeView") plus
// their per-step update methods and the ornament-model key dispatcher.  0x00e8f0b0..0x00e8ff7c.
//
// Retail layout (from the disassembly, all offsets named below):
//   view+0x00   vftable
//   view+0x0c   void* mpObject           (the underlying cSpatialObject, EA::AutoRefCount)
//   view+0x18   Vec3  mModelPos          (model-world input of GonzagoModelWorld)
//   view+0x24   Vec3  mModelRot          (model-world input of GonzagoModelWorld)
//   view+0x34   int   mAnimId            (cMineralView: -1 sentinel; other views: ref target)
//   view+0x38..+0x3a  three bools        (cMineralView loading/animation/LOD flags)
//   view+0x108  void** mpSubBegin        (sub-object vector begin; reached through QI(0x...) )
//   view+0x10c  void** mpSubEnd          (sub-object vector end)
//   obj+0x228   int   mModelKey
//   obj+0x22c   int   mSubModelKey
//   obj+0x2c0   float mModelScale
//
// The QI-style cast in the original is vtable slot 0xb8, called with the class key as its
// only argument; it returns the sub-object of the requested class or null.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

// ---------------------------------------------------------------------------
// Raw virtual-call / field helpers.
// ---------------------------------------------------------------------------
#define VS(o, off)              (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)          ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)  ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))

// ---------------------------------------------------------------------------
// Callees / external globals.
// ---------------------------------------------------------------------------
void* operator_new(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
bool  FUN_00e8eb90(void* obj, void* out);                                         // 0x00e8eb90
typedef void (__thiscall *Fn00e8ef10)(void* self, int flag);                      // 0x00e8ef10
typedef void* (__thiscall *Fn00c90460)(void* self);                               // 0x00c90460
extern "C" void FUN_00e8ef10();
extern "C" void FUN_00c90460();

void* FUN_00ac8730(void* handle);                                                 // 0x00ac8730
void* FUN_00b3d240();                                                             // 0x00b3d240
void* FUN_00d08d70();                                                             // 0x00d08d70
void* SP_GonzagoModelWorld(void* a, void* b);                                     // 0x00b3d520

// The patchwork of static model names (the "Simulator/..." literals live at these VAs).
// Vftables stored by the constructors.
extern char kVtblMineralView[];               // 0x0148687c
extern char kVtblAnimalTrapView[];            // 0x01486814
extern char kVtblTribeFoodMatView[];          // 0x01486848
extern char kVtblOrnamentView[];              // 0x0146063c
extern char kVtblHitSphereView[];             // 0x01460670
extern char kVtblSolarHitSphereView[];        // 0x01460920
extern char kVtblInteractableObjectView[];    // 0x014867ac

// Class keys used with the vtable-slot-0xb8 query-interface cast.
const u32 kKeyMineralView      = 0x0403df5f;
const u32 kKeyAnimalTrapView   = 0x061494bd;
const u32 kKeyTribeFoodMatView = 0x0629baec;
const u32 kKeyOrnamentView     = 0x0175cdc9;
const u32 kKeyHitSphereView    = 0x02e71a5a;
const u32 kKeySolarHitSphere   = 0x032f9777;
const u32 kKeyInteractable     = 0x03a25119;
const u32 kKeyInteractable2    = 0x02a8fe3c;
const u32 kKeyTotemPoleView    = 0x055cf8e3;

// ---------------------------------------------------------------------------
// Layouts.
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };

// A "model key" triple (three dwords written by GetOrnamentModelKey / the tribe-food helper).
struct ModelKey {
    u32 mName;   // +0x00
    u32 mSub;    // +0x04
    u32 mKind;   // +0x08
};

// The QI result of the sub-object queries: a cSpatialObject subclass exposing the fields the
// view families in this slice touch.  Offsets are the retail member offsets.
struct cSpatialObjectSub {
    char  pad_00[0x18];
    Vec3  mModelPos18;      // +0x18: model-world position passed to the view Init
    char  pad_24[0x34 - 0x24];
    void* mpCallback1;      // +0x34: object used by the vt[0x94]/[0xa4]/[0x98] callbacks
    char  pad_38[0x38];
    void* mpSub70;          // +0x70: the hit-sphere/interaction sub-object
    char  pad_74[0x94];
    void** mpVectorBegin;   // +0x108: pointer vector begin
    void** mpVectorEnd;     // +0x10c: pointer vector end
    char  pad_110[0x118];
    int   mKey;             // +0x228: ornament model-key selector (== cSpatialObject::mKey)
    int   mSubKey;          // +0x22c
};

// The inner "interaction" sub-object at +0x70 of the QI result.  Slots: +0x24 IsActive,
// +0x48 HasModel, +0x8c SetFoo(int), +0x94 SetKey(ModelKey*), +0xa4 ClearKey, +0xa8 SetWorld,
// +0xac GetWorld.  Its +0x08 is the model handle read back after SetWorld.
struct cInteractionSub {
    char  pad_00[8];
    void* mpModel;          // +0x08
};

// The model-world object returned by the world-factory (slots +0xc Create, +0x170 Release).
// Only the fields the hit-sphere factories touch are named.
struct cHitSphereWorld {
    u32   mFlags;           // +0x04
    char  pad_08[0x1c];
    char* mpModelPtr;       // +0x24: pointer whose +0x08 is the model handle passed to SetKey
    char  pad_28[0x18];
    int   mRefCount;        // +0x40
};

// One element of the +0x108 sub-object vector.  Its +0x00 is the object used as the receiver
// (its own vftable lives at that object's +0x00); +0x04 is a state bitset.
struct cSubVectorElem {
    void* mpThis;           // +0x00: object whose vftable holds the slot being called
    u32   mFlags;           // +0x04: bit 0 = visible, bit 15 = in-world
};

// The per-object visible-flag byte at +0x108 of a cSpatialObject subclass.
struct cSpatialObjectFlag {
    char pad_00[0x108];
    u8   mbFlag;            // +0x108
};

// SP::cSpatialObject: the simulation object reached through view->mpObject (and passed as the
// int* "obj" to GetOrnamentModelKey).  Only the fields this slice reads are named.
struct cSpatialObject {
    char pad00[0x228];
    int  mKey;           // +0x228: the ornament model key selector
    int  mSubKey;        // +0x22c: sub-key / model override, when non-zero
    char pad230[0x38 - 0x2c];
    int  mField38;       // +0x38
    int  mField3c;       // +0x3c
    int  mField40;       // +0x40
    int  mField44;       // +0x44
    char pad48[0x2c0 - 0x48];
    float mModelScale;   // +0x2c0
};

// cSpatialObjectView (retail size 0x34, ctor 0x00e92af0).  Virtual slot helpers used below:
//   +0x00 SetIsInWorld (0x00e92620), +0x04 GetIsInWorld (0x00e92c60),
//   +0x08 SetIsVisible (0x00e889f0), +0x0c GetIsVisible (0x00e92c80),
//   +0x10 SetFoo(bool) / +0x14 GetFoo() (the per-class visible-state byte),
//   +0x1c MakeView-ish no-arg accessor, +0x24 Init(gameData), +0x28 Init(a, world),
//   +0x2c GetModel/GetTransform, +0x30 GetSubModel.
// The QI cast is slot 0xb8.
class cSpatialObjectView {
public:
    virtual void  SetIsInWorld(bool b);           // +0x00  0x00e92620
    virtual u8    GetIsInWorld();                 // +0x04  0x00e92c60
    virtual void  SetIsVisible(bool b);           // +0x08  0x00e889f0
    virtual u8    GetIsVisible();                 // +0x0c  0x00e92c80
    virtual void  SetClassFlag(u8 b);             // +0x10
    virtual u8    GetClassFlag();                 // +0x14
    virtual void  v18();
    virtual void* v1c();
    virtual void  v20();
    virtual void  Init(void* g);                  // +0x24
    virtual void  Init(void* a, void* w);         // +0x28
    virtual void* GetModel();                     // +0x2c
    virtual void* GetTransform();                 // +0x30

    void  HandleSimulationUpdate(int a, int b);   // non-virtual, 0x00e92ca0

    // 0x00e8eb90 (thiscall; ecx = the creating view, arg1 = the QI result, arg2 = the key buffer)
    bool BuildSubKey(void* sub, ModelKey* out);

    cSpatialObjectView();                         // 0x00e92af0

    u32   mField04;                               // +0x04
    u32   mField08;                               // +0x08
    void* mpObject;                               // +0x0c
    void* mpObjectCombatant;                      // +0x10
    u8    mField14;                               // +0x14
    char  pad_15[3];
    Vec3  mModelPos;                              // +0x18
    Vec3  mModelRot;                              // +0x24
    u8    mField30;                               // +0x30
    u8    mField31;                               // +0x31
    u8    mField32;                               // +0x32
    char  pad_33[1];
};

// SP::cMineralView (retail size 0x48, vftable 0x0148687c): adds an animation id and three
// loading flags after the 0x34-byte base.
class cMineralView : public cSpatialObjectView {
public:
    int   mAnimId;              // +0x34
    u8    mbLoadingModel;       // +0x38
    u8    mbAnimationsStarted;  // +0x39
    u8    mbEffectsInLOD;       // +0x3a
    char  pad_3b[1];
    u32   mField3c;             // +0x3c
    u32   mField40;             // +0x40
    u32   mField44;             // +0x44

    cMineralView* MakeView(void* gameData);       // 0x00e8f0b0
    void Update(void* a, void* b);                // 0x00e8f490
};

// SP::cTotemPoleView (retail size 0x38, vftable 0x014867e0): base 0x34 plus a bool.
class cTotemPoleView : public cSpatialObjectView {
public:
    u8 mField34;                // +0x34

    void SetIsInWorld(bool b);                    // 0x00e8f1f0
    u8   GetIsInWorld();                          // 0x00e8f260
    void SetIsVisible(bool b);                    // 0x00e8f2d0
    u8   GetIsVisible();                          // 0x00e8f330
};

// The plain 0x34-byte spatial views built by the remaining factories.
class cAnimalTrapView : public cSpatialObjectView {
public:
    cAnimalTrapView* MakeView(void* gameData);    // 0x00e8f3c0
    void Update(void* a, void* b);                // 0x00e8f490 is on cMineralView, see below
};

class cTribeFoodMatView : public cSpatialObjectView {
public:
    cTribeFoodMatView* MakeView(void* gameData);  // 0x00e8f5e0
    bool BuildKey(cTribeFoodMatView* self, ModelKey* out);   // 0x00e8f550
    void Update(void* a, void* b);                // 0x00e8f6b0
};

class cOrnamentView : public cSpatialObjectView {
public:
    cOrnamentView* MakeView(void* gameData);      // 0x00e8fa00
    void Update(void* a, void* b);                // 0x00e8fae0
};

class cHitSphereView : public cSpatialObjectView {
public:
    cHitSphereView* MakeView(void* gameData);     // 0x00e8fc20
};

class cSolarHitSphereView : public cSpatialObjectView {
public:
    cSolarHitSphereView* MakeView(void* gameData);   // 0x00e8fd60
};

class cInteractableObjectView : public cSpatialObjectView {
public:
    cInteractableObjectView* MakeView(void* gameData);   // 0x00e8fe80
    void Update(void* a, void* b);                // 0x00e8ff10
};

// Global round-robin counter used by GetOrnamentModelKey's case 0x2ae5ba7.
extern u32 gOrnamentKeyCounter;     // 0x016c53a0
// Global resource handle used by the hit-sphere factories.
extern u32 gHitSphereResource;      // 0x016c53b8
// Global properties object consulted for two tuning floats.
extern void* gPropertyManager;      // 0x0158128c

// SP::GetPropertyT<float>(mgr, key, def) -- 0x004e1c70.
float GetPropertyFloat(void* mgr, u32 key, float def);

// EA::ResourceMan::operator!=(key, handle) -- 0x005f78f0.
bool ResourceMan_NotEqual(void* key, void* handle);

// Two .rdata float constants read directly by the original.
extern const float kOrnamentMinScale;   // 0x01473c70
extern const float kOrnamentMaxScale;   // 0x013eecd8

// ---------------------------------------------------------------------------
// 0x00e8f0b0  SP::cMineralView::MakeView
// ---------------------------------------------------------------------------
// @ 0x00e8f0b0
cMineralView* cMineralView::MakeView(void* gameData)
{
    cMineralView* p = (cMineralView*)operator_new(0x48, "Simulator/cMineralView", 0, 0, 0, 0);
    if (p == 0)
        return 0;
    p->cSpatialObjectView::cSpatialObjectView();
    void* g = gameData;
    *(void**)p = (void*)kVtblMineralView;
    p->mAnimId = 0;
    p->mbLoadingModel = 0;
    p->mbAnimationsStarted = 0;
    p->mbEffectsInLOD = 0;
    p->mField3c = 0;
    p->mField40 = 0;
    p->mField44 = 0;
    void** vt = *(void***)p;
    p->mAnimId = -1;
    ((void (__thiscall*)(void*, void*))vt[0x24 / 4])(p, g);
    return p;
}

// ---------------------------------------------------------------------------
// 0x00e8f1f0  SP::cTotemPoleView::SetIsInWorld
// ---------------------------------------------------------------------------
// @ 0x00e8f1f0
void cTotemPoleView::SetIsInWorld(bool b)
{
    cSpatialObjectView::SetIsInWorld(b);
    void* obj = mpObject;
    if (obj == 0)
        return;
    void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyTotemPoleView);
    if (sub == 0)
        return;
    cSpatialObjectSub* vec = (cSpatialObjectSub*)sub;
    cSubVectorElem** begin = (cSubVectorElem**)vec->mpVectorBegin;
    cSubVectorElem** end   = (cSubVectorElem**)vec->mpVectorEnd;
    for (; begin != end; ++begin) {
        cSubVectorElem* o = *begin;
        if (o != 0) {
            void* self = o->mpThis;
            void** vtbl = *(void***)self;
            ((void (__thiscall*)(void*, cSubVectorElem*, bool))vtbl[0x16c / 4])(self, o, b);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00e8f260  SP::cTotemPoleView::GetIsInWorld
// ---------------------------------------------------------------------------
// @ 0x00e8f260
u8 cTotemPoleView::GetIsInWorld()
{
    u8 r = cSpatialObjectView::GetIsInWorld();
    if (r == 0) {
        void* obj = mpObject;
        if (obj != 0) {
            void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyTotemPoleView);
            if (sub != 0) {
                cSpatialObjectSub* vec = (cSpatialObjectSub*)sub;
                cSubVectorElem** begin = (cSubVectorElem**)vec->mpVectorBegin;
                cSubVectorElem** end   = (cSubVectorElem**)vec->mpVectorEnd;
                for (; begin != end; ++begin) {
                    cSubVectorElem* o = *begin;
                    if (o != 0) {
                        u8 bit = (u8)(o->mFlags >> 0xf);
                        if ((bit & 1) != 0)
                            return 1;
                    }
                }
            }
        }
    }
    return r;
}

// ---------------------------------------------------------------------------
// 0x00e8f2d0  SP::cTotemPoleView::SetIsVisible
// ---------------------------------------------------------------------------
// @ 0x00e8f2d0
void cTotemPoleView::SetIsVisible(bool b)
{
    cSpatialObjectView::SetIsVisible(b);
    void* obj = mpObject;
    if (obj == 0)
        return;
    void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyTotemPoleView);
    if (sub == 0)
        return;
    cSpatialObjectSub* vec = (cSpatialObjectSub*)sub;
    cSubVectorElem** begin = (cSubVectorElem**)vec->mpVectorBegin;
    cSubVectorElem** end   = (cSubVectorElem**)vec->mpVectorEnd;
    if (begin == end)
        return;
    for (; begin != end; ++begin) {
        cSubVectorElem* o = *begin;
        if (o != 0) {
            if (b)
                o->mFlags |= 1;
            else
                o->mFlags &= 0xfffffffe;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00e8f330  SP::cTotemPoleView::GetIsVisible
// ---------------------------------------------------------------------------
// @ 0x00e8f330
u8 cTotemPoleView::GetIsVisible()
{
    u8 r = cSpatialObjectView::GetIsVisible();
    if (r == 0) {
        void* obj = mpObject;
        if (obj != 0) {
            void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyTotemPoleView);
            if (sub != 0) {
                cSpatialObjectSub* vec = (cSpatialObjectSub*)sub;
                cSubVectorElem** begin = (cSubVectorElem**)vec->mpVectorBegin;
                cSubVectorElem** end   = (cSubVectorElem**)vec->mpVectorEnd;
                if (begin != end) {
                    for (; begin != end; ++begin) {
                        cSubVectorElem* o = *begin;
                        if (o != 0 && (o->mFlags & 1) != 0)
                            return 1;
                    }
                }
            }
        }
    }
    return r;
}

// ---------------------------------------------------------------------------
// 0x00e8f3c0  SP::cAnimalTrapView::MakeView
// ---------------------------------------------------------------------------
// @ 0x00e8f3c0
cAnimalTrapView* cAnimalTrapView::MakeView(void* gameData)
{
    ModelKey key = { 0, 0, 0 };
    void* sub;
    if (gameData != 0
        && (sub = (void*)VC1(void*, gameData, 0xc, u32, kKeyAnimalTrapView)) != 0
        && FUN_00e8eb90(sub, &key)) {
        cAnimalTrapView* p = (cAnimalTrapView*)operator_new(0x34, "Simulator/cAnimalTrapView", 0, 0, 0, 0);
        if (p != 0) {
            p->cSpatialObjectView::cSpatialObjectView();
            *(void**)p = (void*)kVtblAnimalTrapView;
        } else {
            p = 0;
        }
        void** vt = *(void***)p;
        void* world = key.mName != 0
            ? SP_GonzagoModelWorld(&key, &mModelPos)
            : SP_GonzagoModelWorld(&mModelRot, &mModelPos);
        ((void (__thiscall*)(void*, void*, void*))vt[0x28 / 4])(p, gameData, world);
        return p;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00e8f490  SP::cMineralView::Update
// ---------------------------------------------------------------------------
// @ 0x00e8f490
void cMineralView::Update(void* a, void* b)
{
    HandleSimulationUpdate((int)a, (int)b);
    void* obj = mpObject;
    if (obj == 0)
        return;
    void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyAnimalTrapView);
    if (sub == 0)
        return;
    ModelKey key = { 0, 0, 0 };
    if (!((cSpatialObjectView*)this)->BuildSubKey(sub, &key))
        return;
    void* inner = &((cSpatialObjectSub*)sub)->mpCallback1;
    if (key.mName != 0)
        VC1(void, inner, 0x94, void*, &key);
    else
        VC0(void, inner, 0xa4);
}

// ---------------------------------------------------------------------------
// 0x00e8f550  SP::cTribeFoodMatView::BuildKey (thiscall; ecx = the creating view,
// arg1 = the cTribeFoodMat QI result whose mpObject is inspected)
// ---------------------------------------------------------------------------
// @ 0x00e8f550
bool cTribeFoodMatView::BuildKey(cTribeFoodMatView* self, ModelKey* out)
{
    cSpatialObjectSub* obj = (cSpatialObjectSub*)self;
    out->mKind = 0xc279c707;
    out->mName = 0xb5efedbb;
    void* vecEnd = obj->mpVectorEnd;
    if (!((Fn00c90460)&FUN_00c90460)(vecEnd))
        return true;
    out->mKind = 0xf37c24e6;
    void* r = ((Fn00c90460)&FUN_00c90460)(vecEnd);
    cInteractionSub* inner = (cInteractionSub*)&((cSpatialObjectSub*)r)->mpCallback1;
    u32* v = (u32*)VC0(void*, inner, 0x98);
    if (*v == 0x93256b8) {
        out->mName = 0x512dfc22;
    } else if (*v == 0x93256b9) {
        out->mName = 0x512dfc23;
    } else if (*v == 0x93256ba) {
        out->mName = 0x512dfc20;
    } else {
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00e8f5e0  SP::cTribeFoodMatView::MakeView
// ---------------------------------------------------------------------------
// @ 0x00e8f5e0
cTribeFoodMatView* cTribeFoodMatView::MakeView(void* gameData)
{
    ModelKey key = { 0, 0, 0 };
    void* sub;
    if (gameData != 0
        && (sub = (void*)VC1(void*, gameData, 0xc, u32, kKeyTribeFoodMatView)) != 0
        && ((cTribeFoodMatView*)this)->BuildKey((cTribeFoodMatView*)sub, &key)) {
        cTribeFoodMatView* p = (cTribeFoodMatView*)operator_new(0x34, "Simulator/cTribeFoodMatView", 0, 0, 0, 0);
        if (p != 0) {
            p->cSpatialObjectView::cSpatialObjectView();
            *(void**)p = (void*)kVtblTribeFoodMatView;
        } else {
            p = 0;
        }
        void** vt = *(void***)p;
        void* world = key.mName != 0
            ? SP_GonzagoModelWorld(&key, &mModelPos)
            : SP_GonzagoModelWorld(&mModelRot, &mModelPos);
        ((void (__thiscall*)(void*, void*, void*))vt[0x28 / 4])(p, gameData, world);
        return p;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00e8f6b0  SP::cTribeFoodMatView::Update
// ---------------------------------------------------------------------------
// @ 0x00e8f6b0
void cTribeFoodMatView::Update(void* a, void* b)
{
    HandleSimulationUpdate((int)a, (int)b);
    void* obj = mpObject;
    void* sub;
    if (obj != 0)
        sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyTribeFoodMatView);
    else
        sub = 0;
    cSpatialObjectFlag* flagObj = (cSpatialObjectFlag*)sub;
    u8 flag = flagObj->mbFlag;
    if (GetClassFlag() != flag)
        SetClassFlag(flagObj->mbFlag);
    if (GetClassFlag()) {
        ModelKey key = { 0, 0, 0 };
        if (((cTribeFoodMatView*)this)->BuildKey((cTribeFoodMatView*)sub, &key)) {
            void* inner = &((cSpatialObjectSub*)sub)->mpCallback1;
            VC1(void, inner, 0x94, void*, &key);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00e8f760  `anonymous namespace'::GetOrnamentModelKey (664 bytes)
// ---------------------------------------------------------------------------
// @ 0x00e8f760
bool GetOrnamentModelKey(cSpatialObject* obj, ModelKey* out)
{
    int key = obj->mKey;
    switch (key) {
    case 0x611a05e:
        out->mName = 0xba6596d3;
        out->mKind = 0x41842000;
        return true;
    case 0x611a05f:
        out->mName = 0x9597ce64;
        out->mKind = 0x41842000;
        return true;
    case 0x65658d2:
        out->mName = obj->mSubKey;
        out->mKind = 0x40828100;
        return true;
    case 0x750f022:
        out->mName = 0xcf571b4e;
        out->mKind = 0xd94352ed;
        return true;
    case 0x5d97f762:
        out->mName = 0x975f9185;
        out->mKind = 0xf37c24e6;
        return true;
    case 0x345bd5d:
        if (obj->mSubKey != 0) {
            out->mName = obj->mSubKey;
            out->mKind = 0;
            return true;
        }
        return true;
    case 0x356eb8a:
        return false;
    case 0x5b9a06e:
    {
        out->mName = 0xc5c2d389;
        out->mKind = 0xf37c24e6;
        void* h = (void*)VC0(void*, obj, 0x30);
        void* r = (void*)FUN_00ac8730(h);
        if (r == 0)
            return true;
        float lo = GetPropertyFloat(gPropertyManager, 0xd2078a9b, kOrnamentMinScale);
        float hi = GetPropertyFloat(gPropertyManager, 0xad06ca38, kOrnamentMaxScale);
        float s = ((cSpatialObject*)r)->mModelScale;
        if (hi <= s) {
            out->mName = 0x7d3993a4;
            return true;
        }
        if (lo < s) {
            out->mName = 0xda6fd23b;
            return true;
        }
        return true;
    }
    case 1:
        if (obj->mField38 == 9) {
            out->mName = 0;
            out->mSub  = 0;
            out->mKind = 0;
            return false;
        }
        out->mName = obj->mField3c;
        out->mSub  = obj->mField40;
        out->mKind = obj->mField44;
        return true;
    case 0x2ae5ba7:
        if (obj->mSubKey != 0) {
            out->mName = obj->mSubKey;
            out->mKind = 0x9430add7;
            return true;
        } else {
            u32 c = gOrnamentKeyCounter;
            u32 rem = c % 5;
            gOrnamentKeyCounter = c + 1;
            switch (rem) {
            case 0:  out->mName = 0x7afab880; break;
            case 1:  out->mName = 0x14b55883; break;
            case 2:  out->mName = 0x4b44c8c9; break;
            case 3:  out->mName = 0x7c6c1c1b; break;
            case 4:  out->mName = 0x7afab880; break;
            default: return true;
            }
            out->mSub  = 0;
            out->mKind = 0x9430add7;
            return true;
        }
    default:
        return false;
    }
}

// ---------------------------------------------------------------------------
// 0x00e8fa00  SP::cOrnamentView::MakeView
// ---------------------------------------------------------------------------
// @ 0x00e8fa00
cOrnamentView* cOrnamentView::MakeView(void* gameData)
{
    ModelKey key = { 0, 0, 0 };
    void* sub;
    if (gameData != 0
        && (sub = (void*)VC1(void*, gameData, 0xc, u32, kKeyOrnamentView)) != 0
        && GetOrnamentModelKey((cSpatialObject*)sub, &key)) {
        cOrnamentView* p = (cOrnamentView*)operator_new(0x34, "Simulator/cOrnamentView", 0, 0, 0, 0);
        if (p != 0) {
            p->cSpatialObjectView::cSpatialObjectView();
            *(void**)p = (void*)kVtblOrnamentView;
        } else {
            p = 0;
        }
        void** vt = *(void***)p;
        void* world = key.mName != 0
            ? SP_GonzagoModelWorld(&key, &mModelPos)
            : SP_GonzagoModelWorld(&mModelRot, &mModelPos);
        ((void (__thiscall*)(void*, void*, void*))vt[0x28 / 4])(p, gameData, world);
        u32* r = (u32*)VC0(void*, p, 0x2c);
        if (r != 0)
            r[1] &= 0xfffffffd;
        return p;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00e8fae0  SP::cOrnamentView::Update
// ---------------------------------------------------------------------------
// @ 0x00e8fae0
void cOrnamentView::Update(void* a, void* b)
{
    HandleSimulationUpdate((int)a, (int)b);
    void* obj = mpObject;
    if (obj == 0)
        return;
    cSpatialObjectSub* sub = (cSpatialObjectSub*)VC1(void*, obj, 0xb8, u32, kKeyOrnamentView);
    if (sub == 0)
        return;
    u8 v = (u8)VC0(u8, sub, 0x58);
    if (GetClassFlag() != v)
        SetClassFlag((u8)VC0(u8, sub, 0x58));
    cInteractionSub* inner = (cInteractionSub*)&sub->mpSub70;
    if (sub->mKey == 0x2ae5ba7) {
        u32* r = (u32*)VC0(void*, this, 0x2c);
        if (r != 0) {
            void* d = FUN_00d08d70();
            if (d != 0 && (u8)VC0(u8, inner, 0x24)) {
                r[1] |= 8;
                ((cSpatialObjectFlag*)r)->mbFlag = 2;
                return;
            }
            r[1] &= 0xfffffff7;
        }
    } else if (sub->mKey == 0x5b9a06e) {
        if ((u8)VC0(u8, inner, 0x48)) {
            ModelKey* h = (ModelKey*)VC0(void*, inner, 0x98);
            ModelKey key;
            key.mName = h->mName;
            key.mSub  = h->mSub;
            key.mKind = h->mKind;
            GetOrnamentModelKey((cSpatialObject*)sub, &key);
            if (ResourceMan_NotEqual(&key, h))
                VC1(void, inner, 0x94, void*, &key);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00e8fc20  SP::cHitSphereView::MakeView
// ---------------------------------------------------------------------------
// @ 0x00e8fc20
cHitSphereView* cHitSphereView::MakeView(void* gameData)
{
    cHitSphereView* p = (cHitSphereView*)operator_new(0x34, "Simulator/cHitSphereView", 0, 0, 0, 0);
    if (p != 0) {
        p->cSpatialObjectView::cSpatialObjectView();
        *(void**)p = (void*)kVtblHitSphereView;
    } else {
        p = 0;
    }
    if (gameData == 0)
        return p;
    void* sub = (void*)VC1(void*, gameData, 0xc, u32, kKeyHitSphereView);
    if (sub == 0)
        return p;
    cInteractionSub* inner = (cInteractionSub*)((cSpatialObjectSub*)sub)->mpSub70;
    if (VC0(void*, inner, 0xac) != 0) {
        VC1(void, p, 0x24, void*, gameData);
        return p;
    }
    cHitSphereWorld* world = (cHitSphereWorld*)SP_GonzagoModelWorld(0, 0);
    cHitSphereWorld* r = (cHitSphereWorld*)VC3(void*, world, 0xc, u32, 0x2e81370, u32, gHitSphereResource, u32, 0x10);
    if (r != 0)
        r->mRefCount++;
    VC2(void, inner, 0xa8, void*, r, void*, world);
    VC1(void, inner, 0x94, void*, r->mpModelPtr + 8);
    VC1(void, inner, 0x8c, int, 0);
    ((void (__thiscall*)(void*, void*, void*, void*, void*))VS(p, 0x28))
        (p, gameData, world, r->mpModelPtr + 8, &((cSpatialObjectSub*)sub)->mModelPos18);
    if (r->mRefCount > 1) {
        r->mRefCount--;
        return p;
    }
    VC1(void, r, 0x170, u32, r->mFlags >> 0x1f);
    return p;
}

// ---------------------------------------------------------------------------
// 0x00e8fd60  SP::cSolarHitSphereView::MakeView
// ---------------------------------------------------------------------------
// @ 0x00e8fd60
cSolarHitSphereView* cSolarHitSphereView::MakeView(void* gameData)
{
    cSolarHitSphereView* p = (cSolarHitSphereView*)operator_new(0x34, "Simulator/cSolarHitSphereView", 0, 0, 0, 0);
    if (p != 0) {
        p->cSpatialObjectView::cSpatialObjectView();
        *(void**)p = (void*)kVtblSolarHitSphereView;
    } else {
        p = 0;
    }
    if (gameData == 0)
        return p;
    void* sub = (void*)VC1(void*, gameData, 0xc, u32, kKeySolarHitSphere);
    if (sub == 0)
        return p;
    void* h = FUN_00b3d240();
    void* world = (void*)VC0(void*, h, 0x70);
    cHitSphereWorld* r = (cHitSphereWorld*)VC3(void*, world, 0xc, u32, 0x2e81370, u32, gHitSphereResource, u32, 0x10);
    if (r != 0)
        r->mRefCount++;
    cInteractionSub* inner = (cInteractionSub*)((cSpatialObjectSub*)sub)->mpSub70;
    VC2(void, inner, 0xa8, void*, r, void*, world);
    VC1(void, inner, 0x94, void*, r->mpModelPtr + 8);
    VC1(void, inner, 0x8c, int, 0);
    ((void (__thiscall*)(void*, void*, void*, void*, void*))VS(p, 0x28))
        (p, gameData, world, r->mpModelPtr + 8, &p->mModelPos);
    if (r->mRefCount > 1) {
        r->mRefCount--;
        return p;
    }
    VC1(void, r, 0x170, u32, r->mFlags >> 0x1f);
    return p;
}

// ---------------------------------------------------------------------------
// 0x00e8fe80  SP::cInteractableObjectView::MakeView
// ---------------------------------------------------------------------------
// @ 0x00e8fe80
cInteractableObjectView* cInteractableObjectView::MakeView(void* gameData)
{
    cInteractableObjectView* p =
        (cInteractableObjectView*)operator_new(0x34, "Simulator/cInteractableObjectView", 0, 0, 0, 0);
    if (p != 0) {
        p->cSpatialObjectView::cSpatialObjectView();
        *(void**)p = (void*)kVtblInteractableObjectView;
    } else {
        p = 0;
    }
    void* a;
    void* b;
    if (gameData != 0) {
        a = (void*)VC1(void*, gameData, 0xc, u32, kKeyInteractable);
        b = (void*)VC1(void*, gameData, 0xc, u32, kKeyInteractable2);
    } else {
        a = 0;
        b = 0;
    }
    if (p != 0 && (b != 0 || a != 0)) {
        VC1(void, p, 0x24, void*, gameData);
        ((Fn00e8ef10)&FUN_00e8ef10)(p, 1);
    }
    return p;
}

// ---------------------------------------------------------------------------
// 0x00e8ff10  SP::cInteractableObjectView::Update
// ---------------------------------------------------------------------------
// @ 0x00e8ff10
void cInteractableObjectView::Update(void* a, void* b)
{
    HandleSimulationUpdate((int)a, (int)b);
    ((Fn00e8ef10)&FUN_00e8ef10)(this, 0);
    void* obj = mpObject;
    if (obj == 0)
        return;
    void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyInteractable);
    if (sub == 0)
        return;
    u8 v = (u8)VC0(u8, sub, 0x64);
    if (GetClassFlag() != v)
        SetClassFlag((u8)VC0(u8, sub, 0x64));
}

// ---------------------------------------------------------------------------
// Restored by the check-in: byte-exact 00e8f120 from commit 8dd062dbc, dropped when this
// slice was rewritten for its new functions.
// Slice s00e8f0b0 (batch hk2, slice 3). Region 0x00e8f120-0x00e8f1bd.
// SP::cMineralView::UpdateLoyaltyBar (159 bytes).
#include "types.h"

void* operator_new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0 EA 6-arg new

struct cSPUIMeter_e8f0 {
  void* Init(unsigned a, unsigned b, unsigned c, const wchar_t* name, unsigned d);  // 0x00e06a10 thiscall, ret 0x14, returns this
  void  Shutdown(int flag);       // 0x00e06940 SP::cSPUIMeter::Shutdown, thiscall
  void  Func_e06ca0(unsigned v);  // 0x00e06ca0 thiscall, ret 4
  void  Func_e06cf0(void* obj);   // 0x00e06cf0 thiscall, ret 4
};

struct cMineralView_e8f0 {
  uint32_t pad[3];                // base cSpatialObjectView header up to +0xc
  void*    mpObject;              // +0x0c  EA::AutoRefCount<cSpatialObject> (raw pointer)

  cSPUIMeter_e8f0* UpdateLoyaltyBar(cSPUIMeter_e8f0* p, char bShow, unsigned hdr);  // 0x00e8f120
};

// @ 0x00e8f120
cSPUIMeter_e8f0* cMineralView_e8f0::UpdateLoyaltyBar(cSPUIMeter_e8f0* p, char bShow, unsigned hdr) {
  if (bShow != 0) {
    unsigned v;
    if (mpObject) {
      void* obj = mpObject;
      v = ((unsigned (__thiscall*)(void*, unsigned))((*(void***)obj)[46]))(obj, 0x403df5f);
    } else {
      v = 0;
    }
    if (p == 0) {
      cSPUIMeter_e8f0* np;
      void* mem = operator_new(0x50, (const char*)0x013f6b3c, 0, 0, 0, 0);
      if (mem) {
        np = (cSPUIMeter_e8f0*)((cSPUIMeter_e8f0*)mem)->Init(hdr, 0x3ffb28c, 0x4d428c1, L"CivConversionBar", 0xe9f70df9);
      } else {
        np = 0;
      }
      np->Func_e06ca0(v);
      np->Func_e06cf0(mpObject);
      return np;
    }
    return p;
  }
  if (p) { p->Shutdown(1); p = 0; }
  return p;
}
