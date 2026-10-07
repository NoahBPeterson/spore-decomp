// slice s00eff790 -- scenario checklist construction / surface and noun lookup helpers.
// 0x00eff790 and 0x00f002d0 are complete (nonmatching.txt); the rest are partial (partial.txt).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"


typedef int  (__thiscall *FN0_i)(void*);
typedef void (__thiscall *FN1_i)(void*, int);
typedef void (__thiscall *FN2_ii)(void*, int, int);

void* __cdecl FUN_00ff3f00(void*);
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

// @ 0x00f001b0
void* __cdecl FUN_00f001b0(int a, void* b)
{
    void* mgr = *(void**)((char*)gSimulator + 0x74);
    if (a == -2)
        return FUN_00ff3f00(mgr);
    return (void*)FUN_00ff3f00(mgr);
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

// @ 0x00f00380
int __cdecl FUN_00f00380()
{
    return 0;
}

// @ 0x00f004f0
int __cdecl FUN_00f004f0()
{
    return 0;
}
