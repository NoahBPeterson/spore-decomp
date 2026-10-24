// slice s00eff790 -- scenario checklist construction / surface and noun lookup helpers.
// All five targets are complete and recorded in nonmatching.txt (partial.txt is empty).
// 0x00f001b0 walks the 0x238-stride surface array for the nearest node with a given key;
// 0x00f00380 is the surface query that aims the selected target; 0x00f004f0 the object query.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>


typedef int  (__thiscall *FN0_i)(void*);
typedef void (__thiscall *FN1_i)(void*, int);
typedef void (__thiscall *FN2_ii)(void*, int, int);

void* __fastcall FUN_00ff3f00(void*);
void* __cdecl FUN_00b3d300();
void* __cdecl FUN_00c680d0(void*, int);
void* __cdecl FUN_00c654e0(void*, float);
void* __cdecl FUN_00c65510(void*, float);
void* __cdecl FUN_00c654b0(void*, float);
void* __cdecl FUN_00c686d0(void*, int, void*, void*);
void* __cdecl FUN_00c662b0(void*, float);
void* __cdecl FUN_00c66310(void*, float);
void* __cdecl FUN_00c643a0(void*, int);
void* __cdecl FUN_00f46410(void*, void*, void*);
void* __cdecl FUN_00fd9450(void*, int);

// ---------------------------------------------------------------------------------------------
// ScenarioTutorials_BuildChecklist (0x00eff790): (re)builds the tutorial checklist's 3D helpers.
// Releases the previous objects, then creates four simple rotation rings, a rotation ball,
// a target morph handle and five arrow morph handles through the game noun manager and stores
// them (ref-counted) in the checklist state at *g_016c7b88.
// ---------------------------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

inline Vector3 operator*(Vector3 v, float s)
{
    v.x *= s; v.y *= s; v.z *= s;
    return v;
}

namespace Simulator {

class cGameData {                       // ref-counted noun base (vtable: AddRef, Release, ?, Cast)
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual void* Cast(uint32_t typeID);
};

template <class T>
struct AutoRefCount {
    T* mpObject;

    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// Model attached at +0x118 of the rings / the ball.
struct cHandleModel {
    void SetUserData(int data);                                         // 0x00fd9450
    void SetDirections(int count, const Vector3* dirs, const void* p);  // 0x00c686d0
};

class cSimpleRotationRing : public cGameData {                        // kSimpleRotationRing
public:
    static const uint32_t NOUN_ID = 0x7a81829;
    static const uint32_t TYPE = 0x7a81824;
    uint32_t pad04[(0x118 - 4) / 4];
    cHandleModel mModel;                                                // +0x118
    void SetAxis(int axis);                                             // 0x00c680d0
    void SetRadius(float r);                                            // 0x00c654e0
    void SetSegments(float n);                                          // 0x00c65510
    void SetOffset(float d);                                            // 0x00c654b0
};

class cSimpleRotationBall : public cGameData {                        // kSimpleRotationBall
public:
    static const uint32_t NOUN_ID = 0x7abdd91;
    static const uint32_t TYPE = 0x7abdd8d;
    uint32_t pad04[(0x118 - 4) / 4];
    cHandleModel mModel;                                                // +0x118
    void SetRadius(float r);                                            // 0x00c662b0
    void SetScale(float s);                                             // 0x00c66310
    void SetEnabled(int b);                                             // 0x00c643a0
};

class cTargetMorphHandle : public cGameData {                         // kTargetMorphHandle
public:
    static const uint32_t NOUN_ID = 0x76f6e64;
    static const uint32_t TYPE = 0x76c67df;
    void SetModel(uint32_t id);                                         // 0x00c68b40
    void SetScale(float s);                                             // 0x00c68bd0
};

class cHandleWindow {                                                   // base at +0x34
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void SetScale(float s);                                     // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90();
    virtual void SetColor(const void* color);                           // 0x94
};

class cArrowMorphHandle : public cGameData {                          // kArrowMorphHandle
public:
    static const uint32_t NOUN_ID = 0x771ad6f;
    static const uint32_t TYPE = 0x771ad6a;
    uint32_t pad04[(0x34 - 4) / 4];
    cHandleWindow mWindow;                                              // +0x34
    void SetRange(float lo, float hi);                                  // 0x00c666f0
    void SetFacing(const Vector3& dir);                                 // 0x00c65940
    void SetOrigin(const Vector3& pos);                                 // 0x00c658e0
    cHandleWindow* operator->() { return &mWindow; }
};

class cGameNounManager {
public:
    cGameData* CreateNoun(uint32_t nounID);                             // 0x00b20c60
};
cGameNounManager* NounManager();                                        // 0x00b3d300

template <class T>
inline T* CreateNoun()
{
    cGameNounManager* pManager = NounManager();
    cGameData* p = pManager->CreateNoun(T::NOUN_ID);
    return p ? (T*)p->Cast(T::TYPE) : 0;
}

struct cHandleSet { void Reset(); };                                    // 0x00c63b20

class cResourceHandleManager {
public:
    void Release(int kind, uint32_t handle, int flags);                 // 0x00f46410
};
struct cSimulatorState {
    uint32_t pad[0x74 / 4];
    cResourceHandleManager* mpHandleManager;                            // +0x74
};

struct cHandleProps { uint8_t pad[0xa6]; bool mbPickable; };
cHandleProps* GetHandleProps(cArrowMorphHandle* handle);                // 0x00b18e00 (cdecl)

}  // namespace Simulator

using namespace Simulator;

struct cTutorialChecklistState {
    uint32_t mHandle;                                   // +0x00
    AutoRefCount<cGameData> mObjects[4];                // +0x04..+0x10
    AutoRefCount<cSimpleRotationRing> mRing3;           // +0x14
    AutoRefCount<cSimpleRotationRing> mRing0;           // +0x18
    AutoRefCount<cSimpleRotationRing> mRing1;           // +0x1c
    AutoRefCount<cSimpleRotationRing> mRing2;           // +0x20
    AutoRefCount<cSimpleRotationBall> mBall;            // +0x24
    AutoRefCount<cTargetMorphHandle> mTarget;           // +0x28
    AutoRefCount<cArrowMorphHandle> mArrow0;            // +0x2c
    cHandleSet mHandleSet;                              // +0x30
    uint32_t pad34[(0x54 - 0x34) / 4];
    AutoRefCount<cArrowMorphHandle> mArrow1;            // +0x54
    AutoRefCount<cArrowMorphHandle> mArrow2;            // +0x58
    AutoRefCount<cArrowMorphHandle> mArrow3;            // +0x5c
    AutoRefCount<cArrowMorphHandle> mArrow4;            // +0x60
    bool mbDirty;                                       // +0x64
    int mCount;                                         // +0x68
};

extern cTutorialChecklistState* g_016c7b88;             // 0x016c7b88
extern cSimulatorState* gSimulator;                     // 0x016c7aa4
extern Vector3 g_016c7b98;                              // 0x016c7b98 arrow origin
extern Vector3 g_016c7c1c;                              // 0x016c7c1c arrow facing
extern const uint8_t g_0148b6ec[];                      // 0x0148b6ec
extern const uint8_t g_015ad304[];                      // 0x015ad304 colour
extern const uint8_t g_015ad310[];                      // 0x015ad310 colour
extern const uint8_t g_015ad31c[];                      // 0x015ad31c colour
extern float g_015ad34c, g_015ad350, g_015ad354, g_015ad358;

struct cTutorialCallbacks {
    void SetAddObjectCallback(void (*fn)());            // 0x00b33ce0
    void SetRemoveObjectCallback(void (*fn)());         // 0x00b33cf0
};
cTutorialCallbacks* TutorialCallbacks();                // 0x00b3d240
void AddObjectGated();                                  // 0x00eff760
void FUN_00efca60();                                    // 0x00efca60
void ScenarioTutorials_PlacePlanetCamera();             // 0x00efdee0

// @ 0x00eff790
void ScenarioTutorials_BuildChecklist()
{
    g_016c7b88->mbDirty = true;
    g_016c7b88->mCount = 0;
    g_016c7b88->mObjects[1] = 0;
    g_016c7b88->mObjects[0] = 0;
    g_016c7b88->mObjects[3] = 0;
    g_016c7b88->mObjects[2] = 0;
    uint32_t handle = g_016c7b88->mHandle;
    g_016c7b88->mHandle = 0;
    if (handle)
        gSimulator->mpHandleManager->Release(1, handle, 0);

    static Vector3 kDirections[6] = {
        Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f),
        Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)
    };

    g_016c7b88->mRing0 = CreateNoun<cSimpleRotationRing>();
    g_016c7b88->mRing0->SetAxis(0);
    g_016c7b88->mRing0->SetRadius(5.0f);
    g_016c7b88->mRing0->SetSegments(16.0f);
    g_016c7b88->mRing0->SetOffset(0.0f);
    g_016c7b88->mRing0->mModel.SetUserData(0x546);
    g_016c7b88->mRing0->mModel.SetDirections(6, kDirections, g_0148b6ec);

    g_016c7b88->mRing1 = CreateNoun<cSimpleRotationRing>();
    g_016c7b88->mRing1->SetAxis(1);
    g_016c7b88->mRing1->SetRadius(2.0f);
    g_016c7b88->mRing1->SetSegments(16.0f);
    g_016c7b88->mRing1->SetOffset(0.0f);
    g_016c7b88->mRing1->mModel.SetUserData(0x546);
    g_016c7b88->mRing1->mModel.SetDirections(6, kDirections, g_0148b6ec);

    g_016c7b88->mRing2 = CreateNoun<cSimpleRotationRing>();
    g_016c7b88->mRing2->SetAxis(2);
    g_016c7b88->mRing2->SetRadius(5.0f);
    g_016c7b88->mRing2->SetSegments(16.0f);
    g_016c7b88->mRing2->SetOffset(2.0f);
    g_016c7b88->mRing2->mModel.SetUserData(0x546);
    g_016c7b88->mRing2->mModel.SetDirections(6, kDirections, g_0148b6ec);

    g_016c7b88->mRing3 = CreateNoun<cSimpleRotationRing>();
    g_016c7b88->mRing3->SetAxis(2);
    g_016c7b88->mRing3->SetRadius(5.0f);
    g_016c7b88->mRing3->SetSegments(16.0f);
    g_016c7b88->mRing3->SetOffset(2.0f);
    g_016c7b88->mRing3->mModel.SetUserData(0x546);
    g_016c7b88->mRing3->mModel.SetDirections(6, kDirections, g_0148b6ec);

    g_016c7b88->mBall = CreateNoun<cSimpleRotationBall>();
    g_016c7b88->mBall->SetRadius(1.0f);
    g_016c7b88->mBall->SetScale(1.2f);
    g_016c7b88->mBall->SetEnabled(1);
    g_016c7b88->mBall->mModel.SetUserData(0x546);
    g_016c7b88->mBall->mModel.SetDirections(6, kDirections, g_0148b6ec);

    g_016c7b88->mTarget = CreateNoun<cTargetMorphHandle>();
    g_016c7b88->mTarget->SetModel(0x2fc096bc);
    g_016c7b88->mTarget->SetScale(2.0f);
    g_016c7b88->mHandleSet.Reset();

    AutoRefCount<cArrowMorphHandle> arrow;
    arrow = CreateNoun<cArrowMorphHandle>();
    arrow->SetRange(0.0f, 250.0f);
    arrow->mWindow.SetColor(g_015ad304);
    g_016c7b88->mArrow0 = arrow;

    arrow = CreateNoun<cArrowMorphHandle>();
    arrow->SetFacing(g_016c7c1c);
    arrow->SetOrigin(g_016c7c1c * 7.0f);
    arrow->mWindow.SetColor(g_015ad304);
    g_016c7b88->mArrow1 = arrow;

    arrow = CreateNoun<cArrowMorphHandle>();
    arrow->SetOrigin(g_016c7b98);
    arrow->mWindow.SetColor(g_015ad304);
    g_016c7b88->mArrow2 = arrow;

    arrow = CreateNoun<cArrowMorphHandle>();
    arrow->mWindow.SetColor(g_015ad31c);
    arrow->SetRange(g_015ad358, g_015ad354 + g_015ad358);
    arrow->SetOrigin(g_016c7b98);
    arrow->mWindow.SetScale(3.0f);
    GetHandleProps(arrow.mpObject)->mbPickable = false;
    g_016c7b88->mArrow3 = arrow;

    arrow = CreateNoun<cArrowMorphHandle>();
    arrow->mWindow.SetColor(g_015ad310);
    arrow->SetRange(g_015ad350, g_015ad34c + g_015ad350);
    arrow->SetFacing(g_016c7c1c);
    arrow->SetOrigin(g_016c7b98);
    arrow->mWindow.SetScale(3.0f);
    GetHandleProps(arrow.mpObject)->mbPickable = false;
    g_016c7b88->mArrow4 = arrow;

    TutorialCallbacks()->SetAddObjectCallback(AddObjectGated);
    TutorialCallbacks()->SetRemoveObjectCallback(FUN_00efca60);
    ScenarioTutorials_PlacePlanetCamera();
}

// =============================================================================================
// Surface / noun query helpers: 0x00f001b0 (nearest surface point), 0x00f00380 (surface query)
// and 0x00f004f0 (object query).
// =============================================================================================

extern uint8_t g_016065f8;                                  // 0x016065f8 tutorial queries enabled
extern void*   g_015ad298;                                  // 0x015ad298
extern uint8_t g_015ad35c;                                  // 0x015ad35c
extern float   g_015ad2ac;                                  // 0x015ad2ac
extern float   g_01471064;                                  // 0x01471064
extern float   g_01485720;                                  // 0x01485720 _HK_REAL_ONE
extern float   g_0148b6e0;                                  // 0x0148b6e0 FLT_MAX
extern char    g_015ad328;                                  // 0x015ad328 tutorial window set (passed in ecx)

// Out-of-slice callees.  The originals behind FUN_00b10200/FUN_00b0f210/FUN_00b10340/
// FUN_00b16270/FUN_00efe930/FUN_00f45970/FUN_00f445c0/FUN_00f3c0b0/FUN_00f3e2b0/
// FUN_00f3ec90/FUN_00f42a00/FUN_00f414b0/FUN_00f45a80/FUN_00efeae0 are thiscall members
// (ecx = self, callee pops its stack args); the __fastcall self slot reproduces that.  The three
// helpers whose original reads a register at entry (a same-TU MSVC register convention with no C
// signature) are reached from inline asm only: FUN_00efccd0 takes its argument in eax,
// FUN_00efcb40 in esi and returns a float in xmm0, FUN_00efc930 writes three floats through esi.
void* __cdecl FUN_00eec0d0(void* p);                                    // 0x00eec0d0
void* __cdecl FUN_00eec0b0(void* p);                                    // 0x00eec0b0
void* __cdecl FUN_0067dd10();                                           // 0x0067dd10 SP::App
void* __cdecl FUN_0067dcc0();                                           // 0x0067dcc0 MessageServer
float* __fastcall FUN_00b10200(void* self, int dummy);                  // 0x00b10200
void __fastcall FUN_00b0f210(void* self, int dummy, float* a, float* b, float* c);  // 0x00b0f210
void __fastcall FUN_00b10340(void* self, int dummy, float a, float b, float c);     // 0x00b10340
void __fastcall FUN_00b16270(void* self, int dummy);                    // 0x00b16270
void __fastcall FUN_00efe930(void* self, int dummy, void* p);           // 0x00efe930
void __fastcall FUN_00f45970(void* self, int dummy);                    // 0x00f45970
void* __fastcall FUN_00f445c0(void* self, int dummy, void* p);          // 0x00f445c0
void __fastcall FUN_00f3c0b0(void* self, int dummy);                    // 0x00f3c0b0 KillThing
void __fastcall FUN_00f3e2b0(void* self, int dummy, void* a, void* b, void* c);     // 0x00f3e2b0
bool __fastcall FUN_00f3ec90(void* self, int dummy, int p);             // 0x00f3ec90
void __fastcall FUN_00f42a00(void* self, int dummy, void* p);           // 0x00f42a00
void __fastcall FUN_00f414b0(void* self, int dummy);                    // 0x00f414b0
void __fastcall FUN_00f45a80(void* self, int dummy);                    // 0x00f45a80
bool __fastcall FUN_00efeae0(void* self, int dummy, void* p);           // 0x00efeae0
float __cdecl FUN_00efcb40();                                           // 0x00efcb40 argument in esi
void  __cdecl FUN_00efccd0();                                           // 0x00efccd0 argument in eax
bool  __cdecl FUN_00efc930();                                           // 0x00efc930 out pointer in esi

// slot of an interface pointer's vtable, by byte offset
inline void* VSlot(void* p, int byteOffset)
{
    return ((void**)*(void***)p)[byteOffset / 4];
}

// A surface node of the 0x238-stride array 0x00f001b0 walks.  mFlags bit 0x40000000 marks the end
// of a run; a negative next key ends it too.  mKey is the selector the caller passes.
struct cSurfacePoint {
    uint32_t mFlags;                                    // +0x00
    uint32_t mKey;                                      // +0x04
    float    mX;                                        // +0x08 unit normal / direction
    float    mY;                                        // +0x0c
    float    mZ;                                        // +0x10
    uint8_t  mRest[0x238 - 0x14];
};

// @ 0x00f001b0
void* __cdecl FUN_00f001b0(int a, void* b)
{
    // The original keeps its element pointer in ecx and restores ecx from the 4-byte scratch slot
    // it reserves at entry (push ecx / pop ecx; LTCG callers may keep a live value there and the
    // gate requires it untouched: docs/codegen.md 11.3.2).  Save and restore ours the same way,
    // before anything (notably the manager load) can take ecx.
    __asm { push ecx }
    char* mgr = (char*)*(void**)((char*)gSimulator + 0x74);
    if (a == -2) {
        __asm { add esp, 4 }
        return FUN_00ff3f00(mgr);
    }
    char* base = *(char**)(mgr + 0x10);
    const float* pos = (const float*)b;
    float best = g_0148b6e0;
    void* result = 0;
    cSurfacePoint* e;
    if (*(uint32_t*)(base + 0x2c24) < 0x3fffffff)
        e = (cSurfacePoint*)(*(uint32_t*)(base + 0x2c24) * 0x238 + *(int*)(base + 0x2c10));
    else
        e = *(cSurfacePoint**)(base + 0x2c14);
    cSurfacePoint* end = *(cSurfacePoint**)(base + 0x2c14);
    if (end != e) {
        do {
            if (e->mKey == (uint32_t)a) {
                // 80-bit x87: the whole chain stays in extended precision, one rounding on store
                float inv = (float)(1.0 / sqrt((double)e->mX * e->mX +
                                               (double)e->mY * e->mY +
                                               (double)e->mZ * e->mZ));
                float dx = e->mX * inv - pos[0];
                float dy = e->mY * inv - pos[1];
                float dz = e->mZ * inv - pos[2];
                float d = (dz * dz + dy * dy) + dx * dx;
                if (d < best) {
                    best = d;
                    result = &e->mKey;
                }
            }
            uint32_t v;
            do {
                v = e->mFlags;
                ++e;
                if ((v >> 0x1e) & 1)
                    break;
            } while ((int)e->mFlags < 0);
        } while (end != e);
    }
    __asm { pop ecx }
    return result;
}

// @ 0x00f002d0
uint32_t* __cdecl FUN_00f002d0(uint32_t* p)
{
    char* mgr = (char*)*(void**)((char*)gSimulator + 0x74);
    uint32_t* r = (uint32_t*)FUN_00ff3f00(mgr);
    if (r == p)
        return p;
    char* base = *(char**)(mgr + 0x10);
    bool b = false;
    uint32_t* first = 0;
    uint32_t* e;
    if (*(uint32_t*)(base + 0x2c24) < 0x3fffffff)
        e = (uint32_t*)(*(uint32_t*)(base + 0x2c24) * 0x238 + *(int*)(base + 0x2c10));
    else
        e = *(uint32_t**)(base + 0x2c14);
    uint32_t* end = *(uint32_t**)(base + 0x2c14);
    if (end != e) {
        do {
            uint32_t* q = e + 1;
            if (e[1] == *p) {
                if (q == p) {
                    b = true;
                } else {
                    if (b)
                        return q;
                    if (first == 0)
                        first = q;
                }
            }
            uint32_t v;
            do {
                v = *e;
                e += 0x8e;
                if ((v >> 0x1e) & 1)
                    break;
            } while ((int)*e < 0);
        } while (end != e);
        if (first != 0)
            return first;
    }
    return p;
}

// @ 0x00f00380  surface query: (re)select and aim the tutorial target for `key`
void __stdcall FUN_00f00380(int key)
{
    if (g_016065f8 == 0)
        return;
    void* p = g_015ad298;
    if (((bool (__thiscall*)(void*))VSlot(p, 0x38))(p))
        return;
    void* app = FUN_0067dd10();
    void* a = ((void* (__thiscall*)(void*))VSlot(app, 0x50))(app);
    void* b = ((void* (__thiscall*)(void*))VSlot(a, 0x38))(a);
    if (b == 0)
        return;
    void* cam = ((void* (__thiscall*)(void*, int))VSlot(b, 0xc))(b, 0x11966ed);
    if (cam == 0)
        return;

    float* pos = FUN_00b10200(cam, 0);
    uint32_t* node = (uint32_t*)FUN_00f001b0(key, pos);
    if (node == 0)
        return;

    float dx = *(float*)((char*)node + 4) - pos[0];
    float dy = *(float*)((char*)node + 8) - pos[1];
    float dz = *(float*)((char*)node + 0xc) - pos[2];
    float d = (dz * dz + dy * dy) + dx * dx;
    if (d < g_01485720)
        node = FUN_00f002d0(node);

    void* sel = FUN_00eec0d0(node);
    FUN_00efe930(&g_015ad328, 0, sel);
    void* props = (void*)GetHandleProps((cArrowMorphHandle*)sel);
    __asm {
        mov     eax, props
        call    FUN_00efccd0
    }

    float pitch, yaw, roll;
    FUN_00b0f210(cam, 0, &pitch, &yaw, &roll);
    if (g_015ad35c != 0)
        yaw = g_015ad2ac * g_01471064;
    float f = 0.0f;
    __asm {
        push    esi
        mov     esi, node
        call    FUN_00efcb40
        movss   dword ptr [f], xmm0
        pop     esi
    }
    FUN_00b10340(cam, 0, pitch, yaw, f);
    FUN_00b16270(cam, 0);
}

// receiver of 0x00f004f0: ecx = this
struct cTutorialQuery {
    uint32_t mPad0;                                     // +0x00
    uint32_t mPad4;                                     // +0x04
    void*    mpWorld;                                   // +0x08 used as `this` for the world helpers
    void*    mpSelected;                                // +0x0c pointer whose first dword is the selected id
    void Query();                                       // 0x00f004f0
};

// @ 0x00f004f0  object query: refresh the selected tutorial object
void cTutorialQuery::Query()
{
    cTutorialQuery* const self = this;
    int id = *(int*)self->mpSelected;
    if (id == -1)
        return;
    void* world = self->mpWorld;
    if (!FUN_00f3ec90(world, 0, id)) {
        void* ms = FUN_0067dcc0();
        ((void (__thiscall*)(void*, int, int, int))VSlot(ms, 0x14))(ms, 0x78c406b, 0, 0);
        return;
    }

    float buf[3];
    bool ok;
    __asm {
        push    esi
        lea     esi, buf
        call    FUN_00efc930
        mov     ok, al
        pop     esi
    }
    if (!ok)
        return;

    FUN_00f45970(world, 0);
    uint32_t* node = (uint32_t*)FUN_00f445c0(world, 0, self->mpSelected);
    if (node == 0) {
        FUN_00f3c0b0(world, 0);
        return;
    }

    void* sel = FUN_00eec0d0(node);
    *(float*)((char*)node + 4) = buf[0];
    *(float*)((char*)node + 8) = buf[1];
    *(float*)((char*)node + 0xc) = buf[2];
    FUN_00f3e2b0(world, 0, node, 0, 0);
    if (FUN_00efeae0(self, 0, sel)) {
        FUN_00f42a00(world, 0, node);
        FUN_00f414b0(world, 0);
        FUN_00f3c0b0(world, 0);
        return;
    }
    ((void (__thiscall*)(void*, void*))VSlot(self, 0x20))(self, sel);
    FUN_00f45a80(world, 0);
    void* props = FUN_00eec0b0(sel);
    if (props != 0) {
        *(uint8_t*)((char*)props + 0x12b) = 1;
        *(uint8_t*)((char*)props + 0x128) = 0;
        void* vp = (char*)props + 0x34;
        ((void (__thiscall*)(void*, void*))VSlot(vp, 0x3c))(vp, (char*)props + 0x44);
    }
}
