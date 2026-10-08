// Slice s0046c000: SP::EditorUtils::GetTranslationOffset (0x46c000).
//
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /Oi /GS- (no /EHsc).
// Computes the translation that recentres an editor creature: the volume-weighted center of the
// bounding boxes of the parts that qualify (per-part property flags in the part's property list),
// combined with the lowest box z, selected axis by axis through the mode mask in the model's
// translation-mode property.  The parts come from either an editor model (stride 0x1d8, `model`)
// or, when `model` is null, a runtime creature (stride 0x8c).
#include "types.h"

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { return (float)fabs(x); }

struct Vec3Data {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Vector3 : Vec3Data {
    Vector3() {}
    Vector3(const Vec3Data& o) { x = o.x; y = o.y; z = o.z; }
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};
// rw::math::fpu::Vector3Template<float,0>: its copy constructor is emitted out of line
struct Vector3Copyable : Vec3Data {
    Vector3Copyable() {}
    Vector3Copyable(const Vector3Copyable& o);   // 0x004098a0
    Vector3Copyable(const Vec3Data& o) { x = o.x; y = o.y; z = o.z; }
};

Vec3Data& operator+=(Vec3Data& a, const Vec3Data& b);                // 0x0041ddb0
Vector3 operator-(const Vec3Data& v);                                // 0x00422020
Vector3 operator/(const Vec3Data& v, const float& s);                // 0x00453880
Vector3 operator*(const Vec3Data& a, const float& s);                // 0x0041dca0

extern const Vector3Copyable kZeroPos;                               // 0x015d4034
extern const float kFltMax;                                          // 0x013eec70
extern const float kZero;                                            // 0x01485378
extern const float kOne;                                             // 0x01485720
extern const uint32_t kPropGroup;                                    // 0x015d3eb4

struct BoundingBox {
    Vector3Copyable min;
    Vector3Copyable max;
    BoundingBox(const BoundingBox& o) : min(o.min), max(o.max) {}
    Vector3& GetCenter(Vector3& out) const;                          // 0x00409b90
};

// ---- property system -------------------------------------------------------------------------
struct Property {
    bool* GetBool();                                                 // 0x0041e920
    uint32_t* GetUInt();                                             // 0x0041ea00
    char pad[0x12];
    uint16_t type;                                                   // +0x12
};
struct PropertyList {
    virtual int AddRef();                                            // +0x00
    virtual int Release();                                           // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);                           // +0x1c
    virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);           // +0x24
};
template <class T>
struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    ~AutoRefCount() { if (mp) mp->Release(); }
    T** AsPPVoidParam();                                             // 0x0041d870
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};
struct PropertyManager_ {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** out);  // +0x2c
};
PropertyManager_* PropertyManager();                                 // 0x0067de30
bool GetBoolProperty(PropertyList* list, uint32_t id, bool* out);    // 0x00407190
uint32_t RemapTypeId(uint32_t id);                                   // 0x00432f10

inline void GetUIntProp(PropertyList* l, uint32_t id, uint32_t& out) {
    Property* p;
    if (l && l->GetProperty(id, &p) && p->type == 10) out = *p->GetUInt();
}
inline void GetBoolProp(PropertyList* l, uint32_t id, bool& out) {
    Property* p;
    if (l && l->GetProperty(id, &p) && p->type == 1) out = *p->GetBool();
}

struct ResKey { uint32_t instanceID, typeID, groupID; };

// ---- part sources ----------------------------------------------------------------------------
struct ModelPart {                    // 0x1d8 bytes
    uint32_t groupID;                 // +0
    uint32_t instanceID;              // +4
    char pad8[0xc];
    Vector3Copyable pos;              // +0x14
    char pad20[0x1d8 - 0x20];
};
struct CreaturePart {                 // 0x8c bytes
    char pad0[0x54];
    Vector3Copyable pos;              // +0x54
    char pad60[0x84 - 0x60];
    uint32_t groupID;                 // +0x84
    uint32_t instanceID;              // +0x88
};
template <class T>
struct PartVec {
    T* mpBegin;
    T* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct EditorModel {
    char pad0[0x18];
    uint32_t typeID;                  // +0x18
    char pad1c[0x98 - 0x1c];
    PartVec<ModelPart> parts;         // +0x98
};
struct Creature {
    char pad0[0x18];
    uint32_t typeID;                  // +0x18
    char pad1c[0x98 - 0x1c];
    PartVec<CreaturePart> parts;      // +0x98
};
struct BoxVec {
    BoundingBox* mpBegin;
};

// @ 0x0046c000
Vector3Copyable GetTranslationOffset(BoxVec* boxes, EditorModel* model, Creature* creature)
{
    float volumeSum = kZero;
    Vector3Copyable weighted(kZeroPos);
    float minHistY = kFltMax;
    float minZ = kFltMax;
    bool anyFlag = false;
    float minZFlag = minZ;
    uint32_t typeId = model ? model->typeID : creature->typeID;
    uint32_t remapped = RemapTypeId(typeId);
    if (remapped == 0xffffffff)
        return kZeroPos;

    AutoRefCount<PropertyList> modeList;
    PropertyManager()->GetPropertyList(remapped, kPropGroup, modeList.AsPPVoidParam());
    uint32_t flags = 0;
    GetUIntProp(modeList, 0x51ce36a, flags);

    int count = model ? model->parts.size() : creature->parts.size();

    for (int i = 0; i < count; i++) {
        Vector3Copyable offset(kZeroPos);
        ResKey key;
        if (model) {
            key.instanceID = model->parts.mpBegin[i].instanceID;
            key.groupID = model->parts.mpBegin[i].groupID;
            offset = model->parts.mpBegin[i].pos;
        } else {
            key.instanceID = creature->parts.mpBegin[i].instanceID;
            key.groupID = creature->parts.mpBegin[i].groupID;
            offset = creature->parts.mpBegin[i].pos;
        }
        BoundingBox box(boxes->mpBegin[i]);

        AutoRefCount<PropertyList> partList;
        PropertyManager()->GetPropertyList(key.instanceID, key.groupID, partList.AsPPVoidParam());
        const uint32_t kPropHasFlag = 0xafff3a14;
        const uint32_t kPropBoolA = 0xd8800eb;
        const uint32_t kPropBoolB = 0x8e31d974;
        const uint32_t kPropBoolC = 0x4a33896;
        bool hasFlag = partList->HasProperty(kPropHasFlag);
        bool boolA = false;
        GetBoolProp(partList, kPropBoolA, boolA);
        bool boolB = false;
        GetBoolProperty(partList, kPropBoolB, &boolB);
        bool boolC = false;
        GetBoolProperty(partList, kPropBoolC, &boolC);
        anyFlag = (anyFlag || boolC) ? true : false;

        bool accumulate = false;
        if (flags & 0x10) {
            if (hasFlag) {
                float yHist = offset[1];
                if (minHistY > yHist) {
                    minHistY = yHist;
                    weighted = offset;
                    volumeSum = kOne;
                }
            }
        } else if (flags & 0x20) {
            if (hasFlag || boolA || boolB)
                accumulate = true;
        } else {
            accumulate = true;
        }
        if (accumulate) {
            float sx = Abs(box.max[0] - box.min[0]);
            float sy = Abs(box.max[1] - box.min[1]);
            float sz = Abs(box.max[2] - box.min[2]);
            float vol = sx * sy * sz;
            volumeSum += vol;
            Vector3 center;
            weighted += box.GetCenter(center) * vol;
        }
        if (minZ > box.min[2])
            minZ = box.min[2];
        if (boolC) {
            if (minZFlag > box.min[2])
                minZFlag = box.min[2];
        }
    }

    Vector3 result(kZeroPos);
    if (volumeSum > kZero) {
        Vector3 c = weighted / volumeSum;
        Vector3 neg = -c;
        float zoff = -(anyFlag ? minZFlag : minZ);
        if ((flags & 1) && kZero >= zoff)
            result[2] += zoff;
        if (flags & 2)
            result[0] += neg[0];
        if (flags & 4)
            result[1] += neg[1];
        if (flags & 8)
            result[2] += neg[2];
        if (flags & 0x10) {
            result.x = neg.x;
            result.y = neg.y;
            result.z = neg.z;
        }
    }
    return result;
}
