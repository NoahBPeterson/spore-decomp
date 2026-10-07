// slice s0057d710 — SP::cAppModeEditorBase helpers and FUN_0057d710 (drop a block/assembly at a screen position). Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

struct cVector4 {
    float x, y, z, w;
    cVector4() {}
    cVector4(const cVector4& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
};
extern cVector4 gTorsoColor;   // 0x0150ce40 (x,y,z,w)
extern char gVtbl0;
extern char gVtbl1;
void* FUN_00401060();
void  FUN_0043cfc0(int, int);
void  operator delete[](void*);


#include <math.h>
inline void* operator new(unsigned int, void* p) { return p; }

#define PV(n) virtual void pv##n();

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    float Dot(const Vector3& o) const { return x * o.x + y * o.y + z * o.z; }
    Vector3 operator/(float f) const { float inv = 1.0f / f; return Vector3(x * inv, y * inv, z * inv); }
    Vector3& operator+=(const Vector3& o) { x += o.x; y += o.y; z += o.z; return *this; }
    Vector3 Normalized() const { return *this / Length(); }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    Vector3 operator+(const Vector3& o) const { return Vector3(x + o.x, y + o.y, z + o.z); }
};
extern const Vector3 kVector3Zero;     // 0x015e4f18
extern const Vector3 kPlaneAxis;       // 0x015e504c
extern const Vector3 kUpAxis;          // 0x015e50a4

// rw::math::fpu::Matrix33Template<float,0>: its copy ctor is out of line (0x0041cb40).
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);
};
struct Matrix3Data { float m[9]; };

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

struct cMWModel {
    char pad0[4];
    uint32_t mFlags;                    // +0x04
};

struct cSPEditorBlock {
    virtual void Dtor();
    virtual int AddRef();
    virtual int Release();
    char pad4[0x10 - 4];
    cMWModel* mModel;                   // +0x10
    char pad14[0x48 - 0x14];
    float mPositionZ;                   // +0x48
    char pad4c[0xa8 - 0x4c];
    Matrix3Data mBaseOrientation;       // +0xa8
    char padcc[0xdc8 - 0xcc];
    uint32_t mFlagsDC8;                 // +0xdc8
    uint32_t mFlagsDCC;                 // +0xdcc
    char padDD0[0xe08 - 0xdd0];

    cSPEditorBlock();                                             // 0x004346b0
    void SetSymmetrySign(int side);                               // 0x0044e980
    void BuildBlock(uint32_t instance, uint32_t group, void* modelWorld, void* physicsWorld,
                    float scale, bool a, bool b, bool c);         // 0x00441440
    void SetBooleanAttribute(int attr, bool value);               // 0x00435a10
    Matrix3 GetOrientation();                                     // 0x0044b590
    void SetOrientation(Matrix3 m);                               // 0x0043ffa0
    float GetDefaultScale(bool b);                                // 0x0044b5c0
    void SetScaleA(float s);                                      // 0x00440020
    void SetScaleB(float s);                                      // 0x00440090
    void Rebuild(void* modelWorld, void* physicsWorld, float scale, bool a, bool b);  // 0x00450f70
    int GetSymmetryIndex();                                       // 0x0044f220
    void FUN_0043e2b0();                                          // 0x0043e2b0
    bool TestFlagDC8(int bit) const { return ((mFlagsDC8 >> bit) & 1) != 0; }
    bool TestFlagDCC(int bit) const { return ((mFlagsDCC >> bit) & 1) != 0; }
};
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);                   // 0x00f473a0

struct cEditorPhysics {
    void* World();                                                // 0x004b91c0
};

struct cRefCountBase {
    virtual ~cRefCountBase();
    int mnRefCount;
    void AddRef() { ++mnRefCount; }
    void Release() {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
    }
};
struct cEditorModelBase { virtual void v0(); };

struct cEditorModel : cEditorModelBase, cRefCountBase {
    void FUN_004ad110();       // 0x004ad110
    float GetScale();                                             // 0x004adaa0
    cEditorPhysics* GetPhysics();                                 // 0x004ad450
    void AddBlock(cSPEditorBlock* block, bool b);                 // 0x004abaf0
    int GetBlockCount();                                          // 0x004accf0
    cSPEditorBlock* GetBlock(int i);                              // 0x004accb0
    void RemoveBlock(cSPEditorBlock* block, int a, int b);        // 0x004ac8b0
    void FUN_004ad330();                                          // 0x004ad330
};

struct cPaintTheme {
    void ApplyToAsset(cSPEditorBlock* block, int flags);          // 0x004b3190
};

struct Property {
    char pad0[0x12];
    int16_t mnType;                     // +0x12
    bool* GetBool();                    // 0x0041e920
};
struct cPropertyList {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t id, Property*& prop);       // slot 9 (+0x24)
};
struct cPropManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual cPropertyList* GetPropertyList(uint32_t instance, uint32_t group);  // slot 22 (+0x58)
};
cPropManager* PropManager();                                      // 0x00401010
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, ResourceKey& out);  // 0x006a1250

struct cViewer {
    void GetCameraLocationInfo(Vector3* pos, Vector3* dir, void* a, void* b);   // 0x007c3d30
    void GetWorldRayFromScreenCoords(float x, float y, Vector3& origin, Vector3& dir);  // 0x007c4730
};
struct cAppSystem {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual cViewer* GetViewer();                                 // slot 22 (+0x58)
};
cAppSystem* App();                                                // 0x0067dd10

bool LoadEditorModel(const ResourceKey& key, AutoRefCount<cEditorModel>& out, int flags);  // 0x004badd0
cSPEditorBlock* FindRootBlock(cSPEditorBlock* block);              // 0x004a5db0
bool IsSymmetryAllowed(int symmetryIndex, int side, int flags);   // 0x004a7ea0
void SnapBlockPosition(cSPEditorBlock* block, float z, int a, int b);  // 0x0049d1f0
void FUN_004a0bf0(cSPEditorBlock* block);                          // 0x004a0bf0
Matrix3 MirrorMatrix(const Matrix3& m, int axis);                  // 0x004a8e10
void RepinBlockToTorso(cSPEditorBlock* block, Vector3 pos, Matrix3Data orientation, bool b);  // 0x0049fbd0

// EASTL allocator / vector pieces used by the assembly path.
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);                 // 0x00f473a0
#define EASTL_ALLOCATOR_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct false_type { false_type() {} };
// 0x004b2320: the linker kept an /Od copy of this EASTL helper; ours is out of line too.
template <typename T>
__declspec(noinline) void uninitialized_fill_n_impl(T* first, unsigned int n, const T& value, false_type)
{
    T* pCurrent = first;
    for (; n > 0; --n, ++pCurrent)
        ::new((void*)pCurrent) T(value);
}

template <typename T>
struct BlockVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    __forceinline explicit BlockVector(int n) {
        mpBegin = n ? (T*)new("Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1) char[n * sizeof(T)] : 0;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + n;
        uninitialized_fill_n_impl(mpBegin, (unsigned int)n, T(), false_type());
        mpEnd = mpBegin + n;
    }
    ~BlockVector() {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            operator delete[](mpBegin);
    }
    T& operator[](int i) { return mpBegin[i]; }
};

struct cSkinManager {
    void* GetSkin(bool create);          // 0x004c49e0
    void* GetSceneObject(int flags);     // 0x004c45d0
    void  FUN_005d1600(int a, int b);    // 0x005d1600
};

struct cAnimCreatureManager {
    void* GetCreature(void* viewer);     // 0x0059ca70
};

struct cTrayRow { bool* mpStates; char pad0[0x10]; };   // 0x14 bytes

struct cSphereListItem {
    char pad0[0x28];
    char* mpBegin;      // +0x28
    char* mpEnd;        // +0x2c
};

struct cAppModeEditorBase {
    char pad0[0x70];
    float m70;                          // +0x70
    char pad74[0x84 - 0x74];
    void* mSaveModelWorld;              // +0x84
    char pad88[0x90 - 0x88];
    cEditorPhysics* mPhysics;           // +0x90
    char pad94[0x98 - 0x94];
    cEditorModel* mEditorSaveModel;     // +0x98
    char pad9c[0xd4 - 0x9c];
    void* mD4;                          // +0xd4
    char padD8[0xe9 - 0xd8];
    bool mTorsoSelected;                // +0xe9
    char padEA[0x14c - 0xea];
    cSkinManager* mSaveSkinManager;     // +0x14c
    cSkinManager* mSaveLoadFactory;     // +0x150
    char pad154[0x1cc - 0x154];
    void* mLaunchData;                  // +0x1cc
    char pad1d0[0x2a0 - 0x1d0];
    cPaintTheme* mPaintTheme;           // +0x2a0
    char pad2a4[0x360 - 0x2a4];
    cAnimCreatureManager* mAnimCreatureManager;  // +0x360
    void* mShadowViewer;                // +0x364
    char pad368[0x385 - 0x368];
    bool mAnimatingCreatureActive;      // +0x385
    char pad386[0x472 - 0x386];
    bool m472;
    char pad473[1];
    float m474;
    char pad478[0x480 - 0x478];
    float m480;
    float m484;
    char pad488[0x48c - 0x488];
    int m48c;
    int m490;
    char pad494[0x4d4 - 0x494];
    bool m4d4;
    char pad4d5[3];
    void* m4d8;                         // +0x4d8
    char pad4dc[0x508 - 0x4dc];
    cTrayRow mTrayRows[6];              // +0x508

    void RemoveTorsoFromEffectsMask();                    // 0x005772b0
    void AddTorsoToEffectsMask(cVector4 v);              // 0x0057a610
    void SetTorsoIsSelected(bool);
    void FUN_00573970();                                  // 0x00573970
    int  GetCurrentTrayRow();                             // 0x00576140
    void UpdateAnimatedCreature();                        // 0x0057ae10
    void FUN_0057e220(float, float, void*, int);
    void FUN_0057e340(bool);
    bool FUN_0057d710(const ResourceKey& key, cSPEditorBlock** ppBlock, float screenX, float screenY,
                      bool bAssembly);
};

// @ 0x0057e160  SP::cAppModeEditorBase::SetTorsoIsSelected
void cAppModeEditorBase::SetTorsoIsSelected(bool selected)
{
    if (selected == mTorsoSelected)
        return;
    if (selected)
        AddTorsoToEffectsMask(gTorsoColor);
    else
        RemoveTorsoFromEffectsMask();
    mTorsoSelected = selected;
}

// ---------------------------------------------------------------------------------------------
// 0x0057e1d0 — scalar deleting destructor of a resourced object (ret 4).
struct cResourcedObject {
    void* mpVtbl0;      // +0
    void* mpVtbl1;      // +4
    char  pad8[4];
    char* mpBegin;      // +0xc
    char* mpEnd;        // +0x10
    char* mpCapacity;   // +0x14
    cResourcedObject* Delete(unsigned flags);
};

// @ 0x0057e1d0
cResourcedObject* cResourcedObject::Delete(unsigned flags)
{
    char* begin = mpBegin;
    if (((mpCapacity - begin) & ~1) > 2 && begin)
        operator delete[](begin);
    mpVtbl1 = (void*)&gVtbl1;
    mpVtbl0 = (void*)&gVtbl0;
    if (flags & 1)
        operator delete[](this);
    return this;
}

// @ 0x0057e220
void cAppModeEditorBase::FUN_0057e220(float a, float b, void* block, int extra)
{
    if (m4d4) {
        m4d4 = false;
        if (!mAnimCreatureManager || !mSaveLoadFactory || mSaveLoadFactory->GetSkin(true) == 0) {
            mEditorSaveModel->FUN_004ad110();
            mAnimatingCreatureActive = false;
        }
        FUN_00573970();
    }
    if (mSaveSkinManager && block) {
        uint32_t creatureFlags = *(uint32_t*)((char*)block + 0xdc8);
        bool bActive = (creatureFlags >> 7) & 1;
        if (bActive)
            mSaveSkinManager->FUN_005d1600(1, 1);
    }
    m480 = a;
    m484 = b;
    m474 = 0.0f;
    m48c = (int)block;
    m490 = extra;
    m472 = true;
    void* p = FUN_00401060();
    if (p) {
        typedef void (__thiscall *Fn)(void*, int, float, float, int);
        Fn fn = *(Fn*)(*(char**)p + 0x1c);
        fn(p, 0x1012, 1.0f, 0.2f, 1);
    }
    *(uint8_t*)((char*)m4d8 + 2) = 1;
    int row = GetCurrentTrayRow();
    if (row < 6 && mLaunchData && *(char*)((char*)mLaunchData + 0x6e))
        mTrayRows[row].mpStates[2] = 1;
}

// @ 0x0057e340
void cAppModeEditorBase::FUN_0057e340(bool active)
{
    mAnimatingCreatureActive = active;
    if (mAnimCreatureManager) {
        void* creature = mAnimCreatureManager->GetCreature(mShadowViewer);
        if (creature && *(char**)((char*)creature + 0x17c)) {
            cSphereListItem* list = *(cSphereListItem**)(*(char**)((char*)creature + 0x17c) + 0x2c0);
            if (list) {
                int n = (int)((list->mpEnd - list->mpBegin) / 0x14);
                if (n > 0) {
                    int off = 0;
                    do {
                        char* item = *(char**)&list->mpBegin[off + 0xc];
                        if (item) {
                            char* iface = *(char**)item;
                            if (iface) {
                                typedef void (__cdecl *Fn)(void*, int, int, int);
                                Fn fn = *(Fn*)(*(char**)iface + 0xc4);
                                fn(item, active, active, 0);
                            }
                        }
                        off += 0x14;
                        --n;
                    } while (n != 0);
                }
            }
        }
    }
    if (!active) {
        m70 = 0.0f;
    } else if (mD4) {
        FUN_0043cfc0(0, 1);
    }
    cEditorModel* model = mEditorSaveModel;
    int* modelBegin = *(int**)((char*)model + 0x18);
    int  count = (int)((*(int**)((char*)model + 0x1c) - modelBegin));
    int  n = count >> 2;
    if (n > 0) {
        int i = 0;
        do {
            char* item = (char*)modelBegin[i];
            if (item) {
                typedef void (__thiscall *Fn0)(void*);
                (*(Fn0*)(*(char**)item + 4))(item);
                void* a = *(void**)(item + 0x10);
                char* b = *(char**)(item + 0x18);
                if (a && b) {
                    typedef void (__cdecl *Fn3)(void*, int, int, int);
                    Fn3 fn = *(Fn3*)(*(char**)b + 0xc4);
                    fn(a, !active, !active, 0);
                }
                (*(Fn0*)(*(char**)item + 8))(item);
            }
            ++i;
        } while (i < n);
    }
    UpdateAnimatedCreature();
}


// @ 0x0057d710  (2631 bytes)
// Creates the block (or, with bAssembly, the blocks of an assembly loaded from `key`) that the
// user drops at screen position (screenX, screenY): the side of the drop point (sign of the
// hit's x on a camera-facing plane) picks the left/center/right variant, the block is built into
// the editor model and repinned to the torso. On success *ppBlock gets a referenced block.
bool cAppModeEditorBase::FUN_0057d710(const ResourceKey& key, cSPEditorBlock** ppBlock,
                                      float screenX, float screenY, bool bAssembly)
{
    cPropertyList* propList = PropManager()->GetPropertyList(key.instanceID, key.groupID);
    bool bUsePlaneAxis = false;
    if (propList) {
        Property* prop;
        if (propList->GetProperty(0x5c5e51ec, prop) && prop->mnType == 1)
            bUsePlaneAxis = *prop->GetBool();
    }

    Vector3 camPos;
    Vector3 camDir;
    App()->GetViewer()->GetCameraLocationInfo(&camPos, &camDir, 0, 0);
    Vector3 planePoint = camPos;
    mEditorSaveModel->GetScale();
    planePoint += camDir.Normalized() * camPos.Length() * 0.9f;
    Vector3 planeNormal = -camDir;
    Vector3 horizDir = Vector3(camDir.x, camDir.y, 0.0f).Normalized();
    float upDot = fabsf(horizDir.Dot(kUpAxis));
    if (bUsePlaneAxis && upDot < 0.8f) {
        planeNormal = kPlaneAxis;
        planePoint = kVector3Zero;
    }
    float planeD = -planeNormal.Dot(planePoint);

    Vector3 rayOrigin;
    Vector3 rayDir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(screenX, screenY, rayOrigin, rayDir);
    Vector3 hit = kVector3Zero;
    float denom = rayDir.Dot(planeNormal);
    if (denom != 0.0f) {
        float t = -(rayOrigin.Dot(planeNormal) + planeD) / denom;
        if (t >= 0.0f)
            hit = rayOrigin + rayDir * t;
    }
    float sign = 0.0f;
    if (hit.x < 0.0f)
        sign = -1.0f;
    else if (hit.x > 0.0f)
        sign = 1.0f;
    int side = (int)sign;
    bool bCenter = side == 0;

    AutoRefCount<cSPEditorBlock> block;
    if (!bAssembly) {
        ResourceKey blockKey = key;
        ResourceKey rightKey = key;
        ResourceKey centerKey = key;
        ResourceKey leftKey = key;
        GetPropertyAsKey(propList, 0x3a3b9d21, centerKey);
        GetPropertyAsKey(propList, 0x0f48eb09, rightKey);
        GetPropertyAsKey(propList, 0x18c1dbe0, leftKey);
        switch (side) {
        case -1:
            blockKey = leftKey;
            break;
        case 0:
            blockKey = centerKey;
            break;
        case 1:
            blockKey = rightKey;
            break;
        }

        block = new("Editor", 0, 0, 0, 0) cSPEditorBlock();
        block->SetSymmetrySign(side);
        cEditorModel* model = mEditorSaveModel;
        void* modelWorld = mSaveModelWorld;
        block->BuildBlock(blockKey.instanceID, blockKey.groupID, modelWorld,
                          model->GetPhysics()->World(), model->GetScale(), true, true, true);
        if (block->TestFlagDCC(27))
            block->SetBooleanAttribute(0x39, true);
        Matrix3 orientation = block->GetOrientation();
        if (side != 1)
            orientation = MirrorMatrix(orientation, 0);
        block->SetOrientation(orientation);
        mEditorSaveModel->AddBlock(block, true);
        if (block->mModel && mPaintTheme) {
            block->mModel->mFlags &= ~2u;
            mPaintTheme->ApplyToAsset(block, 0);
        }
        block->SetScaleA(block->GetDefaultScale(false));
        block->SetScaleB(block->GetDefaultScale(false));
    } else {
        AutoRefCount<cEditorModel> assembly;
        if (LoadEditorModel(key, assembly, 0)) {
            if (!assembly)
                return false;
            if (mSaveModelWorld) {
                int count = assembly->GetBlockCount();
                for (int i = 0; i < count; i++) {
                    cEditorPhysics* physics = mPhysics;
                    void* modelWorld = mSaveModelWorld;
                    assembly->GetBlock(i)->Rebuild(modelWorld, physics->World(),
                                                   assembly->GetScale(), true, true);
                    assembly->GetBlock(i)->SetOrientation(assembly->GetBlock(i)->GetOrientation());
                }
                block = FindRootBlock(assembly->GetBlock(0));
                if (IsSymmetryAllowed(block->GetSymmetryIndex(), side, 0))
                    SnapBlockPosition(block, block->mPositionZ, 0, 1);
                {
                    BlockVector<AutoRefCount<cSPEditorBlock> > blocks(count);
                    for (int i = 0; i < count; i++) {
                        blocks[i] = assembly->GetBlock(i);
                        mEditorSaveModel->AddBlock(blocks[i], true);
                    }
                    for (int i = 0; i < count; i++)
                        assembly->RemoveBlock(blocks[i], 0, 0);
                    assembly->FUN_004ad330();
                    assembly = 0;
                }
            }
        }
    }

    if (!block)
        return false;
    if (block->TestFlagDC8(5))
        FUN_004a0bf0(block);
    block->SetBooleanAttribute(9, true);
    block->SetBooleanAttribute(3, true);
    block->SetBooleanAttribute(1, true);
    block->SetBooleanAttribute(0xf, bCenter);
    block->FUN_0043e2b0();
    RepinBlockToTorso(block, hit, block->mBaseOrientation, false);
    block->AddRef();
    *ppBlock = block;
    return true;
}
