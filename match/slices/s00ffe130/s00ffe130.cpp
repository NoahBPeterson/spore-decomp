// s00ffe130 -- SP::cSPSimulatorPlayerUFO context / destination helpers
#include <math.h>
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int i32;
typedef float f32;
typedef double f64;

#define VT(p) (*(void***)(p))
#define REF_ADD(p) (((void(__thiscall*)(void*))VT(p)[1])(p))
#define REF_REL(p) (((void(__thiscall*)(void*))VT(p)[2])(p))
#define REF_ASSIGN(field, src) \
    do { \
        void* _n = (src); \
        void* _o = (field); \
        if (_n != _o) { \
            if (_n) REF_ADD(_n); \
            (field) = _n; \
            if (_o) REF_REL(_o); \
        } \
    } while (0)
#define REF_CLEAR(field) \
    do { \
        void* _p = (field); \
        if (_p) { \
            (field) = 0; \
            REF_REL(_p); \
        } \
    } while (0)
#define STOP_EFFECT(p) \
    do { \
        void* _e = (p); \
        if (_e) \
            ((void(__thiscall*)(void*, int))VT(_e)[0xc / 4])(_e, 0); \
    } while (0)
#define CLEAR_EFFECT(field) \
    do { \
        void* _e = (field); \
        if (_e) { \
            (field) = 0; \
            ((void(__thiscall*)(void*))VT(_e)[1])(_e); \
        } \
    } while (0)

struct Vector3 {
    f32 x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Quaternion { f32 x, y, z, w; };
struct Matrix3 { f32 m[9]; };
struct ResourceKey { u32 a, b, c; };

struct Transform {
    u16 mFlags;
    u16 mChangeCount;
    Vector3 mOffset;
    f32 mScale;
    Matrix3 mRotation;
    void ctor();  // 0x00434040
};

class cSpatialObject {
public:
    void* mVtbl;
    const Vector3* GetPosition()
    {
        return ((const Vector3*(__thiscall*)(cSpatialObject*))VT(this)[0x2c / 4])(this);
    }
    const Quaternion* GetOrientation()
    {
        return ((const Quaternion*(__thiscall*)(cSpatialObject*))VT(this)[0x30 / 4])(this);
    }
};

struct cInventoryView {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70();
    virtual bool IsToolSelected(const ResourceKey* key);  // +0x74
};

class cSPGameDataUFO {
public:
    u8 pad00[0x34];
    cSpatialObject mSpatial;            // +0x34
    u8 pad38[0x94 - 0x38];
    Vector3 mDirection;                 // +0x94
    u8 padA0[0x718 - 0xA0];
    Vector3 mSavedPos;                  // +0x718
    u8 pad724[0x790 - 0x724];
    void* m790;                         // +0x790
    void* m794;                         // +0x794
    void* m798;                         // +0x798
    void* m79c;                         // +0x79c
    void* m7a0;                         // +0x7a0

    void* GetToolFromToolID(const ResourceKey* key);  // 0x00ff3d40
};

class cSPSimulatorSpaceGame {
public:
    cSPGameDataUFO* GetPlayerInventory();  // 0x00a1ad60
};

struct cCivData {
    Vector3* GetCities();                  // 0x005c65e0
    u32 FUN_00801920(Vector3 pos);         // 0x00801920
};

struct CombatTuning {
    u8 pad00[8];
    void* mPropertyList;                   // +0x08
};

struct cSmoothCameraController {
    f32 CurrentDistance();                 // 0x00c373f0
};

namespace SP {

class cSPSimulatorPlayerUFO {
public:
    u8 pad00[0x40];
    cSPGameDataUFO* mpPlayerUFO;            // +0x40
    u8 pad44[0xb0 - 0x44];
    void* mEffectB0;                       // +0xb0
    void* mEffectB4;                       // +0xb4

    void OnContextChange(int context);                                     // 0x00ffe130
    void FUN_00ffe3a0(int context);                                        // 0x00ffe3a0
    void FUN_00ffe3d0(f32 value, bool flag);                               // 0x00ffe3d0
    void SetPlanetDestinationFromOffset(f32 xOffset, f32 yOffset,
                                        bool a, bool b, bool c,
                                        bool useOrientation, bool e);      // 0x00ffe570
    void SetPlanetDestination(Vector3* pos, bool a, bool b, bool c, bool d); // 0x00ffc350
    void FUN_00ffc030();                                                   // 0x00ffc030
    void FUN_00ffca20();                                                   // 0x00ffca20
    void FUN_00ffdde0(u32 cityID);                                         // 0x00ffdde0
};

}  // namespace SP

using namespace SP;

void* SpaceGameGet();                          // 0x01002bd0
void* GetSpaceCombatTuning();                  // 0x01029940
bool GetPropertyAsKeyArray(void* list, u32 id, int* count, ResourceKey** array); // 0x006a0ae0
cCivData* GetCurrentStar();                    // 0x01021240
void* EffectsManagerPtr();                     // 0x0067ddd0
void* App();                                   // 0x0067dd10
void* MessageServer();                         // 0x0067dcc0
cSmoothCameraController* FUN_00c37360();       // 0x00c37360
Vector3* FUN_0059aed0(Vector3* out, const Vector3* v, const Quaternion* q); // 0x0059aed0
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);          // 0x0059c190

extern u32 g16dba60;
extern u32 g16dba64;
extern u32 g16dba68;
extern Vector3 g15b626c;
extern f32 g14950d4;
extern f32 g1471064;

// @ 0x00ffe130
void cSPSimulatorPlayerUFO::OnContextChange(int context)
{
    cSPSimulatorPlayerUFO* self = this;
    cSPGameDataUFO* state = self->mpPlayerUFO;

    REF_CLEAR(state->m7a0);
    REF_ASSIGN(state->m79c, state->m7a0);
    REF_ASSIGN(state->m798, state->m79c);

    cSPGameDataUFO* inventory =
        ((cSPSimulatorSpaceGame*)SpaceGameGet())->GetPlayerInventory();

    ResourceKey* keys = 0;
    int count = 0;

    switch (context) {
    case 0: {
        CombatTuning* tuning = (CombatTuning*)GetSpaceCombatTuning();
        void** list = &tuning->mPropertyList;
        GetPropertyAsKeyArray(*list, 0x6170854, &count, &keys);
        break;
    }
    case 1: {
        CombatTuning* tuning = (CombatTuning*)GetSpaceCombatTuning();
        void** list = &tuning->mPropertyList;
        GetPropertyAsKeyArray(*list, 0x5877fb5, &count, &keys);
        self->FUN_00ffca20();
        break;
    }
    case 2: {
        CombatTuning* tuning = (CombatTuning*)GetSpaceCombatTuning();
        void** list = &tuning->mPropertyList;
        GetPropertyAsKeyArray(*list, 0x5877fc0, &count, &keys);
        cCivData* civ = GetCurrentStar();
        self->FUN_00ffdde0(civ->FUN_00801920(*civ->GetCities()));
        break;
    }
    }

    ResourceKey selected = { g16dba60, g16dba64, g16dba68 };
    for (int i = count - 1; i >= 0; --i) {
        if (((cInventoryView*)inventory)->IsToolSelected(&keys[i]))
            selected = keys[i];
    }

    if (selected.a != g16dba60 || selected.b != g16dba64 ||
        selected.c != g16dba68) {
        void* tool = inventory->GetToolFromToolID(&selected);
        REF_ASSIGN(state->m798, tool);
    }

    REF_ASSIGN(state->m790, state->m798);
}

// @ 0x00ffe3a0
void cSPSimulatorPlayerUFO::FUN_00ffe3a0(int context)
{
    void* server = MessageServer();
    ((void(__thiscall*)(void*, u32, int, int, int))VT(server)[0x18 / 4])(
        server, 0x490d429, 0, 0, 0);
    this->OnContextChange(context);
}

// @ 0x00ffe3d0
void cSPSimulatorPlayerUFO::FUN_00ffe3d0(f32 value, bool flag)
{
    void** field;

    if (flag) {
        STOP_EFFECT(this->mEffectB4);

        if (value <= 0.0f) {
            STOP_EFFECT(this->mEffectB0);
            return;
        }

        field = &this->mEffectB0;
        if (!*field) {
            void* mgr = EffectsManagerPtr();
            CLEAR_EFFECT(*field);
            ((void(__thiscall*)(void*, u32, int, void**))VT(mgr)[0x2c / 4])(
                mgr, 0x7a564da0, 0, field);
        }
    } else {
        STOP_EFFECT(this->mEffectB0);

        if (value <= 0.0f) {
            STOP_EFFECT(this->mEffectB4);
            return;
        }

        field = &this->mEffectB4;
        if (!*field) {
            void* mgr = EffectsManagerPtr();
            CLEAR_EFFECT(*field);
            ((void(__thiscall*)(void*, u32, int, void**))VT(mgr)[0x2c / 4])(
                mgr, 0x2796d2d5, 0, field);
        }
    }

    if (!*field)
        return;

    if (!((bool(__thiscall*)(void*))VT(*field)[0x10 / 4])(*field))
        ((void(__thiscall*)(void*, int))VT(*field)[8 / 4])(*field, 0);

    ((void(__thiscall*)(void*, int, const f32*, int))VT(*field)[0x44 / 4])(
        *field, 4, &value, 1);

    Matrix3 scratch;
    Transform msg;
    msg.ctor();

    cSPGameDataUFO* ufo = this->mpPlayerUFO;
    msg.mOffset = *ufo->mSpatial.GetPosition();
    msg.mFlags |= 4;
    msg.mChangeCount++;

    Matrix3* mat = Matrix3FromQuaternion(&scratch, ufo->mSpatial.GetOrientation());
    msg.mRotation = *mat;
    msg.mFlags |= 2;
    msg.mChangeCount++;

    ((void(__thiscall*)(void*, Transform*))VT(*field)[0x18 / 4])(*field, &msg);
}

// @ 0x00ffe570
void cSPSimulatorPlayerUFO::SetPlanetDestinationFromOffset(
    f32 xOffset, f32 yOffset, bool a, bool b, bool c, bool useOrientation,
    bool e)
{
    void* app = App();
    void* mode = ((void*(__thiscall*)(void*))VT(app)[0x50 / 4])(app);
    void* world = ((void*(__thiscall*)(void*))VT(mode)[0x38 / 4])(mode);
    if (!world)
        return;

    void* obj = ((void*(__thiscall*)(void*, u32))VT(world)[0xc / 4])(
        world, 0x303154cd);
    if (!obj)
        return;

    cSPGameDataUFO* data = (cSPGameDataUFO*)obj;
    Vector3 dir;

    if (useOrientation) {
        cSpatialObject* spatial = &this->mpPlayerUFO->mSpatial;
        FUN_0059aed0(&dir, &g15b626c, spatial->GetOrientation());
    } else {
        f32 inv = 1.0f / sqrtf(data->mDirection.x * data->mDirection.x +
                              data->mDirection.y * data->mDirection.y +
                              data->mDirection.z * data->mDirection.z);
        dir.x = data->mDirection.x * inv;
        dir.y = data->mDirection.y * inv;
        dir.z = data->mDirection.z * inv;
    }

    Vector3 base = dir;
    cSmoothCameraController* camera = FUN_00c37360();
    f32 angle = camera->CurrentDistance() * g14950d4;

    cSPGameDataUFO* ufo = this->mpPlayerUFO;
    Vector3 axis;
    axis.x = ufo->mSavedPos.y * dir.z - ufo->mSavedPos.z * dir.y;
    axis.y = ufo->mSavedPos.z * dir.x - ufo->mSavedPos.x * dir.z;
    axis.z = ufo->mSavedPos.x * dir.y - ufo->mSavedPos.y * dir.x;

    f32 invAxis = 1.0f / sqrtf(axis.x * axis.x + axis.y * axis.y +
                               axis.z * axis.z);
    f32 half1 = angle * yOffset * 0.5f;
    f32 sin1 = sinf(half1);
    f32 cos1 = cosf(half1);
    Quaternion q1;
    q1.x = axis.x * invAxis * sin1;
    q1.y = axis.y * invAxis * sin1;
    q1.z = axis.z * invAxis * sin1;
    q1.w = cos1;

    Vector3 rotated;
    FUN_0059aed0(&rotated, &ufo->mSavedPos, &q1);

    f32 half2 = angle * xOffset * 0.5f;
    f32 sin2 = sinf(half2);
    f32 cos2 = cosf(half2);
    Quaternion q2;
    q2.x = base.x * sin2;
    q2.y = base.y * sin2;
    q2.z = base.z * sin2;
    q2.w = cos2;

    Vector3 dest;
    FUN_0059aed0(&dest, &rotated, &q2);

    this->SetPlanetDestination(&dest, a, b, c, e);
    this->FUN_00ffc030();
}
