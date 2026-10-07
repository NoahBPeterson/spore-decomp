// Slice s004ba150: Editor resource constructors / AsInterface thunks plus two large editor
// paint/validity bodies. Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"

extern void* g_vtbl;

extern "C" {
    void  FUN_004f3de0(void* a, void* b, int c, int d, int e, int f, char g);
    void* SP_cResourceBase_AsInterface(void* self, int type);
    void  FUN_0046a7c0(void* a);
    void  FUN_004b00a0(void* a);
    void  FUN_0041eb80(void);
    void  FUN_0041e640(void);
    void  FUN_004e8a30(void* a);
    void* ResourceMgr();
}
extern int DAT_015da860, DAT_015da864, DAT_015da868, DAT_015da86c;

struct cResourceBase {
    cResourceBase* AsInterface(int type);
};

class cEditorResource {
public:
    void* mpVtbl0;   // +0
    int   mRefCount; // +4
    char  pad[0x100];
    cEditorResource(int* src);
    void* AsInterface(int type) { return SP_cResourceBase_AsInterface(this, type); }
};

class cRuntimeCreatureResource {
public:
    cResourceBase* AsInterface(int type);   // 0x4bac80
    void zero();                             // 0x4bacc0
};

// @ 0x4bab30
cEditorResource::cEditorResource(int* src)
{
    mpVtbl0 = &g_vtbl;
    mpVtbl0 = &g_vtbl;
    mpVtbl0 = &g_vtbl;
    mRefCount = 0;
    *(int*)((char*)this + 8) = *(int*)((char*)src + 8);
    *(int*)((char*)this + 0xc) = *(int*)((char*)src + 0xc);
    *(int*)((char*)this + 0x10) = *(int*)((char*)src + 0x10);
    mpVtbl0 = &g_vtbl;
    *(int*)((char*)this + 0x14) = *(int*)((char*)src + 0x14);
    mpVtbl0 = &g_vtbl;
    FUN_0046a7c0((char*)src + 0x18);
    FUN_004b00a0((char*)src + 0x98);
}

extern void* g_vtbl;

extern void* g_vtbl;

// @ 0x4babe0
void* __fastcall FUN_004babe0(void* self, void* b, char c)
{
    FUN_004f3de0(b, self, DAT_015da860, DAT_015da864, DAT_015da868, DAT_015da86c, c);
    return b;
}

// @ 0x4bac30
void* __fastcall FUN_004bac30(void* self, void* b, void* c, void* d, void* e, void* f, char g)
{
    FUN_004f3de0(b, self, (int)c, (int)d, (int)e, (int)f, g);
    return b;
}

// @ 0x4bac80
cResourceBase* cRuntimeCreatureResource::AsInterface(int type)
{
    return type == 0x3e1c247
               ? (cResourceBase*)this
               : ((cResourceBase*)this)->AsInterface(type);
}

// @ 0x4bacc0
void cRuntimeCreatureResource::zero()
{
    int* p = (int*)this;
    p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
    p[8] = 0; p[9] = 0; p[10] = 0;
}

// @ 0x4bad50
void __fastcall FUN_004bad50(int* p)
{
    FUN_0041eb80();
    FUN_0041e640();
    if (p[2] != 0) {
        extern void ThreadedObject_Release(void*);
        ThreadedObject_Release((void*)p[2]);
    }
    if (p[1] != 0) {
        extern void AutoRefCount_assign(void);
    }
    if (*p != 0)
        (*(void(__thiscall**)(int))(*p + 4))(*p);
}

// @ 0x4badd0  SP::cSPEditorPaintTheme::Apply (large)
int FUN_004badd0(void* self, int* a, void* b)
{
    (void)self; (void)a; (void)b;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x004ba150  (thiscall on a cEditorResource, ret 4)
// PDB caller-scored candidate: SP::EditorValidity::AddCellUpgradeForBlockPropList.
// For a cell-stage resource (model type 0xdfad9f51) it makes a copy, retypes it
// (0x9ea3031a), drops every block onto z = 0 using the part bounding boxes, re-orients
// the blocks whose part properties ask for it, remaps block keys, and returns the copy.
// ---------------------------------------------------------------------------
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* pFile, int line);                                      // 0xf473a0

namespace SP {

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    float& operator[](int i) { return (&x)[i]; }
};

struct Matrix3 {
    Vector3 m[3];
    Vector3& operator[](int i) { return m[i]; }
};
Matrix3 operator*(const Matrix3& a, const Matrix3& b);                               // 0x0041de20
extern Matrix3 kMatrix3Identity;                                                       // 0x015d8364

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { return (float)fabs(x); }

struct ColorRGB { float r, g, b; };

struct cSPTransform {
    uint16_t mnFlags;            // +0x00
    int16_t  mnTransformCount;   // +0x02
    Vector3  mOffset;            // +0x04
    float    mfScale;            // +0x10
    Matrix3  mRotation;          // +0x14
    cSPTransform();                                                                    // 0x00409930
    void SetOffset(const Vector3& v) { mOffset = v; mnFlags |= 4; mnTransformCount++; }
    void SetRotation(Matrix3 m) { mRotation = m; mnFlags |= 2; mnTransformCount++; }
    void SetScale(float s) { mfScale = s; mnTransformCount++; }
};

struct cSPBoundingBox {
    Vector3 mMin;
    Vector3 mMax;
    cSPBoundingBox();                                                                  // 0x00409c00
    void Transform(const cSPTransform& t);                                             // 0x00409dd0
};

struct ResourceKey {
    uint32_t mInstanceID, mTypeID, mGroupID;
    ResourceKey() : mInstanceID(0), mTypeID(0), mGroupID(0) {}
};

// Part group id built from bitfields (0x40616000 for the cell-mouth part group).
struct PartGroupID {
    union {
        uint32_t mValue;
        struct {
            uint32_t mLow   : 8;
            uint32_t mMinor : 8;
            uint32_t mMajor : 8;
            uint32_t mPad   : 6;
            uint32_t mKind  : 2;
        };
    };
    PartGroupID(int major, int minor) { mValue = 0; mKind = 1; mMajor = major; mMinor = minor; }
};

struct Property {
    uint32_t pad[4];
    uint16_t mnFlags;                                                                  // +0x10
    uint16_t mnType;                                                                   // +0x12
    bool* GetValueBool();                                                              // 0x0041e920
};

struct cPropertyList {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20();
    virtual bool GetProperty(uint32_t id, Property*& out);                             // +0x24
};
bool GetPropertyAsKey(cPropertyList* pl, uint32_t id, ResourceKey& out);               // 0x006a1250

inline bool GetPropertyBool(cPropertyList* pl, uint32_t id, bool& value)
{
    Property* prop;
    if (pl && pl->GetProperty(id, prop) && prop->mnType == 1) {
        value = *prop->GetValueBool();
        return true;
    }
    return false;
}

struct IEditorPartData {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24(); virtual void f28(); virtual void f2c();
    virtual void f30(); virtual void f34(); virtual void f38(); virtual void f3c();
    virtual void f40(); virtual void f44(); virtual void f48(); virtual void f4c();
    virtual void f50();
    virtual bool GetBoundingBox(uint32_t instanceID, uint32_t groupID, float* handleWeights,
                                int handleCount, Vector3* pMin, Vector3* pMax);        // +0x54
    virtual cPropertyList* GetPropertyList(uint32_t instanceID, uint32_t groupID);     // +0x58
};
IEditorPartData* EditorPartData();                                                     // 0x00401010

struct cEditorResourceBlock {                                                          // 0x1d8
    uint32_t groupID;            // +0x00
    uint32_t instanceID;         // +0x04
    int      parentIndex;        // +0x08
    int      symmetricIndex;     // +0x0c
    float    scale;              // +0x10
    Vector3  position;           // +0x14
    Vector3  triangleDirection;  // +0x20
    Vector3  trianglePickOrigin; // +0x2c
    Matrix3  orientation;        // +0x38
    Matrix3  userOrientation;    // +0x5c
    uint32_t pad80[4];           // +0x80
    int      handlesCount;       // +0x90
    float    handleWeights[8];   // +0x94
    uint32_t padB4[73];          // +0xb4
};

template <typename T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
};

struct cEditorResourceProperties {
    uint32_t mModelType;         // +0x00
    uint32_t pad04[7];
    ColorRGB mSkinColor1;        // +0x20
    ColorRGB mSkinColor2;        // +0x2c
    ColorRGB mSkinColor3;        // +0x38
    uint32_t pad44[15];
};

class cEditorResource {
public:
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04[5];
    cEditorResourceProperties mProperties;     // +0x18
    vector<cEditorResourceBlock> mBlocks;      // +0x98

    cEditorResource(const cEditorResource& other);                                     // 0x004bab30
    const ColorRGB& GetSkinColor1() const { return mProperties.mSkinColor1; }
    bool CreateCellUpgradeCopy(cEditorResource** ppOut);
};

template <typename T>
struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T* detach() { T* const temp = mpObject; mpObject = 0; return temp; }
};

bool cEditorResource::CreateCellUpgradeCopy(cEditorResource** ppOut)
{
    bool result = false;
    if (mProperties.mModelType == 0xdfad9f51) {
        intrusive_ptr<cEditorResource> res = new("Editor/cEditorResource", 0, 0, 0, 0) cEditorResource(*this);
        res->mProperties.mModelType = 0x9ea3031a;
        res->mProperties.mSkinColor2 = res->GetSkinColor1();

        float minZ = 0.0f;
        cSPBoundingBox bbox;
        cSPTransform transform;

        for (uint32_t i = 0, n = res->mBlocks.size(); i < n; i++) {
            cEditorResourceBlock& block = res->mBlocks[i];
            bool ok = true;
            if (block.instanceID == 0xc15cfa84 && block.groupID == PartGroupID(0x61, 0x60).mValue) {
                bbox.mMin.x = -0.19f;
                bbox.mMin.y = -0.07f;
                bbox.mMin.z = -0.35f;
                bbox.mMax.x = 0.19f;
                bbox.mMax.y = 0.07f;
                bbox.mMax.z = 0.03f;
            } else {
                ok = EditorPartData()->GetBoundingBox(block.instanceID, block.groupID, block.handleWeights,
                                                      block.handlesCount, &bbox.mMin, &bbox.mMax);
            }
            if (ok) {
                transform.SetOffset(block.position);
                transform.SetRotation(block.userOrientation * block.orientation);
                transform.SetScale(block.scale);
                bbox.Transform(transform);
                float z = bbox.mMin[2];
                if (minZ > z)
                    minZ = z;
            }
        }

        for (uint32_t i = 0, n = res->mBlocks.size(); i < n; i++) {
            cEditorResourceBlock& block = res->mBlocks[i];
            block.position[2] -= minZ;
        }

        ResourceKey key;
        for (uint32_t i = 0, n = res->mBlocks.size(); i < n; i++) {
            cEditorResourceBlock& block = res->mBlocks[i];
            cPropertyList* props = EditorPartData()->GetPropertyList(block.instanceID, block.groupID);
            if (props) {
                bool resetUserOrientation = false;
                if (GetPropertyBool(props, 0x655296a, resetUserOrientation) && resetUserOrientation)
                    block.userOrientation = kMatrix3Identity;

                bool alignToAxis = false;
                if (GetPropertyBool(props, 0x6554604, alignToAxis) && Abs(block.position[0]) < 0.001f) {
                    if (block.orientation[1][1] > 0.0f) {
                        static const Vector3 kRight(1.0f, 0.0f, 0.0f);
                        static const Vector3 kDown(0.0f, 0.0f, -1.0f);
                        static const Vector3 kForward(0.0f, 1.0f, 0.0f);
                        block.orientation[0] = kDown;
                        block.orientation[1] = kForward;
                        block.orientation[2] = kRight;
                        block.userOrientation = kMatrix3Identity;
                    } else {
                        static const Vector3 kRight(1.0f, 0.0f, 0.0f);
                        static const Vector3 kUp(0.0f, 0.0f, 1.0f);
                        static const Vector3 kBack(0.0f, -1.0f, 0.0f);
                        block.orientation[0] = kUp;
                        block.orientation[1] = kBack;
                        block.orientation[2] = kRight;
                        block.userOrientation = kMatrix3Identity;
                    }
                }

                if (GetPropertyAsKey(props, 0xf45f59d7, key)) {
                    block.instanceID = key.mInstanceID;
                    block.groupID = key.mGroupID;
                }
            }
        }

        *ppOut = res.detach();
        result = true;
    }
    return result;
}

} // namespace SP
