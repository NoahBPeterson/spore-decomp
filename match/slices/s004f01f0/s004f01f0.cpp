// slice s004f01f0 -- SP::cSPEditorModelValidity::TestSize
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (editor /Od region, no /EHsc).
//
// Validity test "too small": reads the per-model-type minimum size (x, y, z) and minimum
// absolute height from the editor config property list, accumulates the world bounding
// box of every rigblock (each block's model bbox transformed by its offset, orientation
// and scale) and flags kValidityTooSmall{X,Y,Z} / kValidityTooSmallAbsoluteZ /
// kValidityTooSmall (9) in the result bitset. Sibling of TestBounds/TestLimbs (s004ee9b0).

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

// eastl::bitset<128>: set() as the inline EASTL body (the range check survives /Od).
struct ValidityBits {
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline ValidityBits& set(uint32_t i, bool value) {
        if (i < 128) {
            if (value)
                DoGetWord(i) |= (1u << (i % 32));
            else
                DoGetWord(i) &= ~(1u << (i % 32));
        }
        return *this;
    }
};

enum {
    kValidityTooSmall = 9,
    kValidityTooSmallX = 22,
    kValidityTooSmallY = 23,
    kValidityTooSmallZ = 24,
    kValidityTooSmallAbsoluteZ = 25
};

struct RefCounted {
    virtual int AddRef();
    virtual int Release();
};

template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T** GetAddress();               // @ 0x0041d870 (releases, returns &mpObject)
    T** AsPPointer() { return GetAddress(); }
};

struct Property {
    char pad[0x12];
    uint16_t mType;                 // +0x12 (0xd = float)
    float* GetFloat();              // @ 0x0041ea70
};

struct cPropertyList : RefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};

struct cPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, cPropertyList** ppOut);   // +0x2c
};
cPropertyManager* PropertyManager();                 // @ 0x0067de30
uint32_t GetConfigFromModelType(uint32_t modelType); // @ 0x00432f10
extern uint32_t kEditorConfigGroup;                  // 0x015daa00
extern const float kMinSizeDefault;                  // 0x013f106c (FLT_MIN)

// Math types (arrays, so constant indices compile to `mov r,i; shl r,2`).
struct Vector3 {
    float v[3];
    Vector3() {}
    Vector3(float x, float y, float z) { v[0] = x; v[1] = y; v[2] = z; }
    float& operator[](int i) { return v[i]; }
};

struct Matrix3Base {
    float m[9];
    Matrix3Base();                  // @ 0x00402ab0 (out of line, empty)
};
struct Matrix3 : Matrix3Base {
    Matrix3() {}
    Matrix3(const Matrix3Base& o) { *(Matrix3Base*)this = o; }
};
Matrix3Base MultiplyMatrix(const Matrix3Base& a, const Matrix3Base& b);   // @ 0x0041de20

struct Transform {
    uint16_t mnFlags;               // +0x00
    uint16_t mnTransformCount;      // +0x02
    Vector3 mOffset;                // +0x04
    float mfScale;                  // +0x10
    Matrix3Base mRotation;          // +0x14
    Transform();                    // @ 0x00409930
    Transform& SetOffset(const Vector3& value) {
        mOffset = value;
        mnFlags |= 4;
        mnTransformCount++;
        return *this;
    }
    Transform& SetRotation(const Matrix3& value) {
        mRotation = value;
        mnFlags |= 2;
        mnTransformCount++;
        return *this;
    }
    Transform& SetScale(float value) {
        mfScale = value;
        mnTransformCount++;
        return *this;
    }
};

struct BoundingBox {
    Vector3 mMin;
    Vector3 mMax;
    BoundingBox();                                  // @ 0x00409c00 (min=+FLT_MAX, max=-FLT_MAX)
    void ApplyTransform(const Transform& t);        // @ 0x00409dd0
    void Add(const BoundingBox& b);                 // @ 0x0043f050
};

// One rigblock record of the editor model (0x1d8 bytes; copy ctor out of line).
struct cEditorModelBlock {
    uint32_t mGroupID;              // +0x00
    uint32_t mInstanceID;           // +0x04
    uint32_t pad08[2];
    float mScale;                   // +0x10
    Vector3 mPosition;              // +0x14
    uint32_t pad20[6];
    Matrix3Base mOrientation;       // +0x38
    Matrix3Base mBaseOrientation;   // +0x5c
    uint32_t pad80[4];
    uint32_t mModelFlags;           // +0x90
    uint32_t mBoundsInfo[8];        // +0x94
    uint32_t padb4[(0x1d8 - 0xb4) / 4];
    cEditorModelBlock(const cEditorModelBlock& o);  // @ 0x004721e0
};

struct BlockVec {
    cEditorModelBlock* mpBegin;
    cEditorModelBlock* mpEnd;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cEditorModelBlock& operator[](int i) { return mpBegin[i]; }
};

struct cEditorModel {
    uint32_t pad0[6];
    uint32_t mModelType;            // +0x18
    uint32_t pad1[(0x98 - 0x1c) / 4];
    BlockVec mBlocks;               // +0x98
};

// Resource manager: +0x54 = GetModelBoundingBox(instance, group, info, flags, &min, &max),
// +0x58 = GetPropertyList(instance, group).
struct cModelManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual bool GetBoundingBox(uint32_t instance, uint32_t group, uint32_t* info, uint32_t flags,
                                Vector3* pMin, Vector3* pMax);                  // +0x54
    virtual cPropertyList* GetPropertyList(uint32_t instance, uint32_t group);   // +0x58
};
cModelManager* ModelManager();      // @ 0x00401010

inline void GetPropertyFloat(cPropertyList* pList, uint32_t id, float& dst) {
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == 0xd)
        dst = *prop->GetFloat();
}

// <math.h> (VS2008) C++ overload
inline float fabsf(float _X) { return (float)fabs((double)_X); }

// @ 0x004f01f0
bool TestSize(cEditorModel* model, ValidityBits* validity)
{
    BlockVec* blocks = &model->mBlocks;
    Vector3 minSize = Vector3(kMinSizeDefault, kMinSizeDefault, kMinSizeDefault);
    float minHeight = kMinSizeDefault;

    if (validity) {
        validity->set(kValidityTooSmallX, false);
        validity->set(kValidityTooSmallY, false);
        validity->set(kValidityTooSmallZ, false);
        validity->set(kValidityTooSmall, false);
        validity->set(kValidityTooSmallAbsoluteZ, false);
    }

    uint32_t modelType = model->mModelType;
    AutoRefCount<cPropertyList> config;
    PropertyManager()->GetPropertyList(GetConfigFromModelType(modelType), kEditorConfigGroup,
                                       config.AsPPointer());
    if (!config) {
        if (validity)
            validity->set(kValidityTooSmall, true);
        return false;
    }

    if (config) {
        GetPropertyFloat(config, 0x538b032, minSize[0]);
        GetPropertyFloat(config, 0x538b033, minSize[1]);
        GetPropertyFloat(config, 0x538b031, minSize[2]);
        GetPropertyFloat(config, 0x538b034, minHeight);
    }

    if (blocks->size() == 0) {
        if (validity) {
            validity->set(kValidityTooSmallX, true);
            validity->set(kValidityTooSmallY, true);
            validity->set(kValidityTooSmallZ, true);
            validity->set(kValidityTooSmall, true);
            validity->set(kValidityTooSmallAbsoluteZ, true);
        }
        return true;
    }

    BoundingBox bbox;
    bool valid = blocks->size() > 0;
    for (int i = 0, n = (int)blocks->size(); i < n; i++) {
        cEditorModelBlock block((*blocks)[i]);
        AutoRefCount<cPropertyList> blockProps =
            ModelManager()->GetPropertyList(block.mInstanceID, block.mGroupID);
        if (!blockProps) {
            if (validity)
                validity->set(kValidityTooSmall, true);
            return false;
        }
        if (blockProps) {
            BoundingBox blockBox;
            bool hasBox = ModelManager()->GetBoundingBox(block.mInstanceID, block.mGroupID,
                block.mBoundsInfo, block.mModelFlags, &blockBox.mMin, &blockBox.mMax);
            if (hasBox) {
                Transform t;
                t.SetOffset(block.mPosition);
                t.SetRotation(MultiplyMatrix(block.mBaseOrientation, block.mOrientation));
                t.SetScale(block.mScale);
                blockBox.ApplyTransform(t);
                bbox.Add(blockBox);
            } else {
                valid = false;
            }
        }
    }

    if (!valid)
        return true;

    if (minHeight > bbox.mMax[2]) {
        if (validity) {
            validity->set(kValidityTooSmallAbsoluteZ, true);
            validity->set(kValidityTooSmall, true);
        }
        return false;
    }

    for (int axis = 0; axis < 3; axis++) {
        if (minSize[axis] > fabsf(bbox.mMax[axis] - bbox.mMin[axis])) {
            if (validity) {
                switch (axis) {
                case 0: validity->set(kValidityTooSmallX, true); break;
                case 1: validity->set(kValidityTooSmallY, true); break;
                case 2: validity->set(kValidityTooSmallZ, true); break;
                }
                validity->set(kValidityTooSmall, true);
            }
            return false;
        }
    }
    return true;
}
