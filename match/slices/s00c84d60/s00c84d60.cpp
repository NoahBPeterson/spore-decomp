// Slice s00c84d60: SP::cSolarSystem planetary simulation (0x00c84d60 - 0x00c85a30).
//   UpdatePlanet      advances one planet's orbital state for a frame
//   InitBinarySystem  composes the display name of one star of a binary system
//   UpdatePlanets     ticks every planet, then pushes the active component transform into the
//                     celestial-body list
//   GetBinarySuffix   creates / refreshes the two binary-star celestial bodies
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <wctype.h>

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PAD1 virtual void CAT(pad, __COUNTER__)();
#define PAD4 PAD1 PAD1 PAD1 PAD1
#define PAD8 PAD4 PAD4
#define PAD16 PAD8 PAD8

struct Vector3 {
    float x, y, z;
};
struct Raw3 {
    float x, y, z;
};

// ------------------------------------------------------------------ eastl helpers
struct WString {                            // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;                       // +0x00
    wchar_t* mpEnd;                         // +0x04
    wchar_t* mpCap;                         // +0x08
    void*    mpPad0c;                       // +0x0c
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};

struct cString {                            // SP::cString
    uint8_t mData[0x14];
    cString(uint32_t a, uint32_t b, const wchar_t* text);     // 0x006b5770
    const wchar_t* GetText();                                 // 0x006b55c0
    ~cString();                                               // 0x006b5240
};

extern WString* __cdecl PathJoin(WString* out, WString* name, const wchar_t* text);  // 0x0057cba0
extern void __cdecl FreeRawBlock(void* block);                                        // 0x00f47380
extern void* __cdecl FUN_00f473a0(uint32_t size, const char* name, int, int, int, int); // 0x00f473a0
extern void* __cdecl FUN_00bd6410(void* memory, int kind);                            // 0x00bd6410
extern int __cdecl FUN_00c6ff90(void* component);                                     // 0x00c6ff90
extern void __cdecl FUN_00aea5d0(void* dst, void* src);                               // 0x00aea5d0
extern float __cdecl GetStarRotationRate(void* star);                                 // 0x00c842a0
extern float __cdecl GetStarRadius(void* star);                                       // 0x00c84120
extern float __cdecl GetStarMass(void* star);
extern float __cdecl RandomDoubleUniform();                                           // 0x00e1a5a0

struct WString;

struct cGameData {                          // star-system description shared by the solar system
    uint8_t  pad00[0x34];                   // +0x00 .. +0x33
    void*    mpStarA;                       // +0x34
    void*    mpStarB;                       // +0x38
    bool  IsBinary();                       // 0x00c8b7e0
    WString* GetName();                     // 0x00c8b540
};

struct cAvatar {
    uint8_t pad00[0xc0];                    // +0x00 .. +0xbf
    Vector3 mPosC0;                         // +0xc0
};

struct cProperty {
    uint8_t  pad00[0x12];                   // +0x00 .. +0x11
    uint16_t mType12;                       // +0x12
};

// ------------------------------------------------------------------ celestial bodies
struct cCelestialBody;

struct IBodyComponent {                     // component found by type key on a body
    PAD8 PAD1 PAD1 PAD1
    virtual const Vector3& GetPosition();                 // vtable +0x2c
    int GetState();                                       // 0x00c6ff90
};

struct IBodyData {                          // payload object held at cCelestialBody::mpData64
    PAD1 PAD1 PAD1
    virtual void* QueryComponent(const void* typeKey);    // vtable +0x0c
};

struct IBodyInterface {                     // interface held at cCelestialBody::mpIface0
    virtual void AddRef();                                  // vtable +0x00
    virtual void Release();                                 // vtable +0x04
    PAD16 PAD16 PAD16 PAD16 PAD16 PAD8 PAD1
    virtual void SetVisible(cCelestialBody* body, int on);   // vtable +0x16c
};

struct cCelestialBody {
    IBodyInterface* mpIface0;               // +0x00
    uint32_t  mBits4;                       // +0x04   bit 15 marks the secondary star
    uint16_t  mFlags8;                      // +0x08
    uint16_t  mCounterA;                    // +0x0a
    Vector3   mPosition;                    // +0x0c
    uint8_t   pad18[0x20];                  // +0x18 .. +0x37
    uint8_t   mKind38;                      // +0x38
    Vector3   mAxis3c;                      // +0x3c
    float     mSwing48;                     // +0x48
    Vector3   mOffset4c;                    // +0x4c
    float     mInclination58;               // +0x58
    uint8_t   pad5c[0x08];                  // +0x5c .. +0x63
    IBodyData* mpData64;                    // +0x64
    uint8_t   pad68[0x38];                  // +0x68 .. +0x9f
    Vector3   mVelocityA0;                  // +0xa0
    float     mRotationAc;                  // +0xac
    WString   mName;                        // +0xb0
    uint8_t   padc0[0x08];                  // +0xc0 .. +0xc7
    float     mRadiusC8;                    // +0xc8
};

// ------------------------------------------------------------------ planet
struct cPlanet {
    PAD8 PAD1 PAD1 PAD1                                         // slots 0..10
    virtual const Vector3& GetPosition();                       // vtable +0x2c
    PAD1 PAD1                                                   // slots 12..13
    virtual void SetPosition(const Vector3& p);                 // vtable +0x38
    uint8_t  pad04[0x20];                                       // +0x04 .. +0x23
    void*    mpObj24;                                           // +0x24
    uint8_t  pad28[0x08];                                       // +0x28 .. +0x2f
    Vector3  mPosition30;                                       // +0x30
    uint8_t  pad3c[0x6c];                                       // +0x3c .. +0xa7
    void GetPtolemaicPosition(Vector3& out);                    // 0x00c83a10
};

namespace SP {

class cSPLivingUniverse {
public:
    static cPlanet* GetActivePlanet();                          // 0x01021260
    static int GetUniverseContext();                            // 0x01021080
};

class cSolarSystem {
public:
    void UpdatePlanet(cPlanet* planet, float dt);               // 0x00c84d60
    void UpdatePlanets(float dt);                               // 0x00c85380
    void InitBinarySystem(WString* name);                       // 0x00c85200
    void GetBinarySuffix();                                     // 0x00c85540

    uint8_t  pad00[0x0c];                                       // +0x00
    cGameData* mpGameData;                                      // +0x0c
    cPlanet** mpPlanetsBegin;                                   // +0x10
    cPlanet** mpPlanetsEnd;                                     // +0x14
    uint8_t  pad18[0x0c];                                       // +0x18
    void**   mpBodies0Begin;                                    // +0x24
    void**   mpBodies0End;                                      // +0x28
    void**   mpBodies0Cap;                                      // +0x2c
    uint8_t  pad30[0x08];                                       // +0x30
    cCelestialBody* mpPrimary;                                  // +0x38
    cCelestialBody* mpSecondary;                                // +0x3c
    cCelestialBody** mpBodiesBegin;                             // +0x40
    cCelestialBody** mpBodiesEnd;                               // +0x44
};

}

// ------------------------------------------------------------------ misc externs
extern int   __cdecl FUN_00b5b800();                            // 0x00b5b800
extern void* __cdecl FUN_00b3d300();                            // 0x00b3d300
extern void* __cdecl FUN_00b1fdb0(void* mgr);                    // 0x00b1fdb0
extern void* __cdecl FUN_00b20030(void* mgr);                    // 0x00b20030
extern void* __cdecl FUN_00409930();                            // 0x00409930
extern void* __cdecl FUN_0045f1c0();                            // 0x0045f1c0 (App)
extern int   __cdecl FUN_00c70880(cPlanet* planet);             // 0x00c70880 (GetPlanetType)
extern float __cdecl FUN_00c708a0(float f);                     // 0x00c708a0
extern void  __cdecl FUN_00c72770(float f);                     // 0x00c72770
extern void  __cdecl FUN_00c719d0(int mode);                    // 0x00c719d0
extern void* __cdecl FUN_00c71530();                            // 0x00c71530
extern void  __cdecl FUN_00c84950(cPlanet* planet);             // 0x00c84950
extern bool  __cdecl FUN_00c83e40(cPlanet* planet);             // 0x00c83e40
extern void  __cdecl FUN_00bc30b0(void* v);                     // 0x00bc30b0
extern float __cdecl FUN_00bc2b60(void* v);                     // 0x00bc2b60
extern void  __cdecl FUN_00bc28c0(float f);                     // 0x00bc28c0
extern void  __cdecl FUN_007c40f0(void* v);                     // 0x007c40f0
extern void* __cdecl FUN_00fe8780(void* out, void* in);         // 0x00fe8780
extern void  __cdecl FUN_01021740();                            // 0x01021740
extern void* __cdecl FUN_0041ea70(void* prop);                  // 0x0041ea70 (Property::GetFloat)
extern void* __cdecl FUN_00fe8450();                            // 0x00fe8450

extern int*  g_p01694c68;                                       // 0x01694c68
extern int   g_mode_01654c01;                                   // 0x01654c01
extern float g_f01694c10;                                       // 0x01694c10
extern float g_f01694c14;                                       // 0x01694c14
extern float g_f01694c18;                                       // 0x01694c18
extern float g_f01579ea4;                                       // 0x01579ea4
extern float g_f01579d58;                                       // 0x01579d58
extern float g_f01579d5c;                                       // 0x01579d5c
extern float g_f01579d60;                                       // 0x01579d60

struct IConfig {                            // settings object behind 0x01694c68
    PAD8 PAD1
    virtual bool GetProperty(const void* key, void** out);   // vtable +0x24
};

// @ 0x00c85380
// Advances every planet of the system by one frame, then refreshes the transform of each
// celestial body from the positional component it publishes.
void SP::cSolarSystem::UpdatePlanets(float dt)
{
    cCelestialBody** it;
    int count = (int)(mpPlanetsEnd - mpPlanetsBegin);
    for (int i = 0; i < count; i++)
        UpdatePlanet(mpPlanetsBegin[i], dt);

    if (cSPLivingUniverse::GetUniverseContext() != 0)
        return;

    for (it = mpBodiesBegin; it != mpBodiesEnd; it++) {
        cCelestialBody* body = *it;
        IBodyData* data = body->mpData64;
        if (!data)
            continue;
        IBodyComponent* comp = (IBodyComponent*)data->QueryComponent((const void*)0x3275872);
        if (!comp)
            continue;

        int state = comp->GetState();
        unsigned shifted = body->mBits4 >> 15;
        if (state == 2) {
            if (!(shifted & 1))
                body->mpIface0->SetVisible(body, 1);
            body->mPosition = comp->GetPosition();
            body->mFlags8 = body->mFlags8 | 4;
            body->mCounterA = body->mCounterA + 1;
        } else if (shifted & 1) {
            body->mpIface0->SetVisible(body, 0);
        }
    }
}

// @ 0x00c85200
// Composes the name of one member of a binary system: either copies the base name straight in
// (simulation running) or appends the "a"/"b" suffix picked from the last character.
void SP::cSolarSystem::InitBinarySystem(WString* name)
{
    if (mpGameData->IsBinary()) {
        wchar_t* pLast = name->mpEnd;
        bool alpha = iswctype(*--pLast, 4) != 0;

        if (mpPrimary) {
            const wchar_t* suffix;
            {
                cString text(0x2db6dad3, (alpha ? 1 : 0) * 2 + 0x5d66e7c, 0);
                suffix = text.GetText();
            }
            WString tmp;
            cCelestialBody* primary = mpPrimary;
            WString* joined = PathJoin(&tmp, name, suffix);
            if (joined != &primary->mName)
                primary->mName.assign(joined->mpBegin, joined->mpEnd);
            if ((int)(((uint32_t)((uint8_t*)tmp.mpCap - (uint8_t*)tmp.mpBegin)) & 0xfffffffeu) > 2 &&
                tmp.mpBegin)
                FreeRawBlock(tmp.mpBegin);
        }

        if (mpSecondary) {
            const wchar_t* suffix;
            {
                cString text(0x2db6dad3, (alpha ? 3 : 0) + 0x5d66e7d, 0);
                suffix = text.GetText();
            }
            WString tmp;
            cCelestialBody* secondary = mpSecondary;
            WString* joined = PathJoin(&tmp, name, suffix);
            if (joined != &secondary->mName)
                secondary->mName.assign(joined->mpBegin, joined->mpEnd);
            if ((int)(((uint32_t)((uint8_t*)tmp.mpCap - (uint8_t*)tmp.mpBegin)) & 0xfffffffeu) > 2 &&
                tmp.mpBegin)
                FreeRawBlock(tmp.mpBegin);
        }
    } else {
        if (mpPrimary && name != &mpPrimary->mName)
            mpPrimary->mName.assign(name->mpBegin, name->mpEnd);
    }
}

// @ 0x00c85540
// Makes sure both binary-star bodies exist and refreshes their orbital parameters.
void SP::cSolarSystem::GetBinarySuffix()
{
    int alpha = iswctype((wint_t)mpGameData->GetName()->mpEnd[-1], 4);

    if (!mpPrimary) {
        cCelestialBody* body =
            (cCelestialBody*)FUN_00f473a0(0xcc, "Simulator/cCelestialBody", 0, 0, 0, 0);
        if (body)
            body = (cCelestialBody*)FUN_00bd6410(body, 0);
        cCelestialBody* old = mpPrimary;
        if (body != old) {
            if (body)
                body->mpIface0->AddRef();
            mpPrimary = body;
            if (old)
                old->mpIface0->Release();
        }
        if (mpBodies0End < mpBodies0Cap) {
            void** slot = mpBodies0End++;
            if (slot) {
                *slot = mpPrimary;
                if (mpPrimary)
                    mpPrimary->mpIface0->AddRef();
            }
        } else {
            FUN_00aea5d0(mpBodies0End, &mpPrimary);
        }
    }

    cCelestialBody* primary = mpPrimary;
    primary->mRotationAc = GetStarRotationRate(mpGameData->mpStarA);
    primary->mRadiusC8 = GetStarRadius(mpGameData->mpStarA);

    if (!mpSecondary) {
        cCelestialBody* body =
            (cCelestialBody*)FUN_00f473a0(0xcc, "Simulator/cCelestialBody", 0, 0, 0, 0);
        if (body)
            body = (cCelestialBody*)FUN_00bd6410(body, 0);
        cCelestialBody* old = mpSecondary;
        if (body != old) {
            if (body)
                body->mpIface0->AddRef();
            mpSecondary = body;
            if (old)
                old->mpIface0->Release();
        }
        if (mpBodies0End < mpBodies0Cap) {
            void** slot = mpBodies0End++;
            if (slot) {
                *slot = mpSecondary;
                if (mpSecondary)
                    mpSecondary->mpIface0->AddRef();
            }
        } else {
            FUN_00aea5d0(mpBodies0End, &mpSecondary);
        }
    }

    cCelestialBody* secondary = mpSecondary;
    secondary->mRotationAc = GetStarRotationRate(mpGameData->mpStarB);
    secondary->mRadiusC8 = GetStarRadius(mpGameData->mpStarB);

    float massA = GetStarMass(mpGameData->mpStarA);
    float massB = GetStarMass(mpGameData->mpStarB);
    float radiusA = GetStarRadius(mpGameData->mpStarA);
    float radiusB = GetStarRadius(mpGameData->mpStarB);
    float distance = ((radiusA + radiusB) * 1.5f) / ((massB / massA) + 1.0f);
    float jitter = (float)RandomDoubleUniform() * ((distance + 10.0f) - distance) + distance;
    float orbit = jitter * (massB / massA);

    float binaryOffset;
    if (mpGameData->mpStarA == mpGameData->mpStarB) {
        float r = (float)RandomDoubleUniform() * 0.2f;
        binaryOffset = r < 0.0f ? 0.0f : (r > 0.2f ? 0.2f : r);
    } else {
        binaryOffset = 0.0f;
    }

    float tilt = (float)RandomDoubleUniform() * 60.0f + 30.0f;
    if (tilt > 90.0f)
        tilt = 90.0f;

    primary->mKind38 = 0;
    primary->mAxis3c.x = g_f01579d58;
    primary->mAxis3c.y = g_f01579d5c;
    primary->mAxis3c.z = g_f01579d60;
    primary->mSwing48 = binaryOffset;
    primary->mVelocityA0.x = orbit;
    primary->mVelocityA0.y = 0.0f;
    primary->mVelocityA0.z = 0.0f;
    primary->mInclination58 = tilt;
    primary->mOffset4c.x = orbit;
    primary->mOffset4c.y = 0.0f;
    primary->mOffset4c.z = 0.0f;
    FUN_00fe8450();

    secondary->mKind38 = 0;
    secondary->mAxis3c.x = g_f01579d58;
    secondary->mAxis3c.y = g_f01579d5c;
    secondary->mAxis3c.z = g_f01579d60;
    secondary->mSwing48 = binaryOffset;
    secondary->mVelocityA0.x = -orbit;
    secondary->mVelocityA0.y = 0.0f;
    secondary->mVelocityA0.z = 0.0f;
    secondary->mInclination58 = tilt;
    secondary->mOffset4c.x = -orbit;
    secondary->mOffset4c.y = 0.0f;
    secondary->mOffset4c.z = 0.0f;
    FUN_00fe8450();
}

// @ 0x00c84d60
// Advances a single planet: rescales the frame time for the simulation context, keeps the
// active planet's orbit phase in sync with the day clock, moves the planet transform and
// finally updates the camera-relative visibility state.
void SP::cSolarSystem::UpdatePlanet(cPlanet* planet, float dt)
{
    cPlanet* active = cSPLivingUniverse::GetActivePlanet();
    int ctx = cSPLivingUniverse::GetUniverseContext();
    bool isActive = (ctx == 0 && planet == active);

    float step = dt;
    if (ctx == 1) {
        float scale = 10.0f;
        if (g_p01694c68) {
            void* prop = 0;
            if (((IConfig*)g_p01694c68)->GetProperty((const void*)0x54fc890, &prop) &&
                ((cProperty*)prop)->mType12 == 0xd)
                scale = *(float*)FUN_0041ea70(prop);
        }
        step = scale * dt;
    }

    if (FUN_00c70880(planet) == 0)
        return;

    Vector3 target;
    if (FUN_00b5b800() == (int)&g_mode_01654c01) {
        void* mgr = FUN_00b3d300();
        void* avatar = mgr ? FUN_00b1fdb0(mgr) : 0;
        if (avatar) {
            const Vector3& p = ((cAvatar*)avatar)->mPosC0;
            target = p;
        } else {
            target = planet->mPosition30;
        }
    } else {
        target = planet->mPosition30;
    }

    if (isActive) {
        FUN_00bc30b0(&target);
        float phase = FUN_00bc2b60(&target);
        FUN_00bc28c0(phase);
    }

    float orbit = step;
    if (FUN_00c70880(planet) == 1)
        orbit = dt;
    FUN_00c72770(orbit);

    Vector3 delta;
    delta.x = target.x - planet->mPosition30.x;
    delta.y = target.y - planet->mPosition30.y;
    delta.z = target.z - planet->mPosition30.z;

    Vector3 pos;
    pos.x = planet->GetPosition().x + delta.x;
    pos.y = planet->GetPosition().y + delta.y;
    pos.z = planet->GetPosition().z + delta.z;
    planet->SetPosition(pos);

    (void)FUN_00c71530();

    if (!isActive) {
        FUN_00c84950(planet);
        if (ctx == 0) {
            Vector3 ptol;
            planet->GetPtolemaicPosition(ptol);
            float near = delta.x * pos.x + delta.y * pos.y + ptol.x * orbit;
            int mode = (near <= g_f01579ea4) ? 3 : 2;
            if (mode == 2 && FUN_00c83e40(planet))
                mode = 3;
            FUN_00c719d0(mode);
        }
        return;
    }

    FUN_01021740();
}
