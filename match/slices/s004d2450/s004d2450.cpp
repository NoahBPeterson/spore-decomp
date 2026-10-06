// Slice s004d2450: SP::`anonymous namespace'::LoadSpeciesTuning (4243 bytes, /Od).
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
//
// Loads the global species-editor tuning property list (instance 0x236f18f2,
// fetched through the property manager's vtable slot 12) once, or again when
// forced, and copies ~45 typed properties into file-scope tuning globals:
// uint32 values (three of them are seconds converted to milliseconds), floats,
// one bool, four Vector2s, a float array (resized into a global float vector)
// and three Vector3 arrays (resized into global Vector3 vectors).
//
// The property IDs are FNV hashes whose names are not known, so the globals
// are named by address.
//
// /Od frame: the function-scope pair (propManager, propList) and the eight
// array locals of the inner scope are laid out by the hash of their names, so
// those names were chosen to reproduce the original slot order (byte-exact).
// AsPPTypeParam is EA::AutoRefCount's inline wrapper around the out-of-line
// AsPPVoidParam (its returned pointer gets the original's temp slot), and
// get() gives each array read its pointer temp.
#include "types.h"
#pragma pack(push, 4)

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };

// ---- properties -----------------------------------------------------------

enum PropertyType {
    kPropBool = 1,
    kPropUInt32 = 10,
    kPropFloat = 13
};

struct Property {
    uint32_t pad0[4];
    uint16_t mFlags;            // +0x10
    uint16_t mType;             // +0x12
    bool* GetBool();            // 0x0041E920
    uint32_t* GetUInt();        // 0x0041EA00
    float* GetFloat();          // 0x0041EA70
};

struct PropertyList {
    virtual int AddRef();                                           // slot 0
    virtual int Release();                                          // slot 1
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& pOut);         // slot 9  (+0x24)
};

// eastl::intrusive_ptr<PropertyList>
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() { mpObject = 0; }
    ~PropertyListPtr();                                             // 0x004A9B10
    PropertyList* get() const { return mpObject; }
    void** AsPPVoidParam();                                         // 0x0041D870: release, return &mpObject
    PropertyList** AsPPTypeParam() { return (PropertyList**)AsPPVoidParam(); }
};

struct IPropManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual bool GetGlobalPropertyList(uint32_t instanceID, PropertyList** ppOut);  // slot 12 (+0x30)
};

// Typed property reads (inlined: no list/prop temps shared between reads).
inline void ReadPropertyUInt32(PropertyList* pList, uint32_t id, uint32_t& dst)
{
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropUInt32)
        dst = *prop->GetUInt();
}

inline void ReadPropertyFloat(PropertyList* pList, uint32_t id, float& dst)
{
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropFloat)
        dst = *prop->GetFloat();
}

inline void ReadPropertyBool(PropertyList* pList, uint32_t id, bool& dst)
{
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropBool)
        dst = *prop->GetBool();
}

namespace SP {
IPropManager* PropertyManager();                                                        // 0x0067DE30
bool GetPropertyAsFloat(PropertyList* p, uint32_t id, float* pOut);                     // 0x0040CF10
bool GetPropertyAsUint32(PropertyList* p, uint32_t id, uint32_t* pOut);                 // 0x004AF210
bool GetPropertyAsVector2(PropertyList* p, uint32_t id, Vector2* pOut);                 // 0x006A10C0
bool GetPropertyAsFloatArray(PropertyList* p, uint32_t id, int* pCount, float** ppData);      // 0x006A08B0
bool GetPropertyAsVector3Array(PropertyList* p, uint32_t id, int* pCount, Vector3** ppData);  // 0x006A0AE0
}

// ---- containers -----------------------------------------------------------

struct FloatVector {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32_t mAllocator;
    void resize(uint32_t n);                                        // 0x004AFC80
};

struct Vector3Vector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;
    void resize(uint32_t n);                                        // 0x004548D0
};

// ---- tuning globals -------------------------------------------------------

extern bool sSpeciesTuningLoaded;           // 0x015D9C48

extern uint32_t sTuning_15d9674;            // 0x1368995d
extern uint32_t sTuning_15d9670;            // 0xd8f99173
extern uint32_t sTuning_150c884;            // 0x7717409a (seconds -> ms)
extern float sTuning_150c888;               // 0x11074696
extern float sTuning_150c88c;               // 0x61ecd45c
extern float sTuning_15d9650;               // 0x518ea467
extern float sTuning_15d9654;               // 0x518ea466
extern float sTuning_15d9658;               // 0x518ea465
extern float sTuning_15d965c;               // 0x518ea464
extern float sTuning_15d9660;               // 0x518ea463
extern float sTuning_15d9664;               // 0x518ea462
extern float sTuning_150c900;               // 0xd899bec5
extern float sTuning_15d96b8;               // 0x4745de1b
extern float sTuning_150c890;               // 0x57634c7c
extern float sTuning_150c894;               // 0x57634c7d
extern float sTuning_150c898;               // 0x57634c7e
extern float sTuning_150c89c;               // 0x57634c7f
extern float sTuning_150c8a0;               // 0x57634c78
extern float sTuning_150c8a4;               // 0x57634c79
extern float sTuning_150c8a8;               // 0x57634c7a
extern float sTuning_150c8ac;               // 0xb6ec210b
extern float sTuning_150c8b0;               // 0x71c653b2
extern float sTuning_150c8b4;               // 0xffb2d688
extern float sTuning_150c8b8;               // 0x49c7436e
extern float sTuning_150c8bc;               // 0x0a97c583
extern float sTuning_150c8c0;               // 0x6b559718
extern uint32_t sTuning_150c8c4;            // 0x24cb8070
extern Vector2 sTuning_15d9834;             // 0xb237e271
extern Vector2 sTuning_15d9764;             // 0xf237e2d7
extern Vector2 sTuning_15d9a68;             // 0x5237e2d8
extern float sTuning_15d9668;               // 0xd237f426
extern bool sTuning_15d966c;                // 0x32380e2c
extern uint32_t sTuning_150c8c8;            // 0x523a8f4c
extern float sTuning_150c8cc;               // 0x036ad4db
extern Vector2 sTuning_15d992c;             // 0x036ad587
extern float sTuning_150c8d4;               // 0xbf623956
extern float sTuning_150c8e4;               // 0xa597b8c1
extern float sTuning_150c8e8;               // 0xa597b8c0
extern float sTuning_150c8ec;               // 0xa597b8c3
extern float sTuning_150c8f0;               // 0xa597b8c2
extern float sTuning_150c8f4;               // 0xa597b8c5
extern float sTuning_150c8f8;               // 0xa597b8c4
extern float sTuning_150c8fc;               // 0xa597b8c7
extern float sTuning_150c8d0;               // 0x81275d0a
extern uint32_t sTuning_150c8d8;            // 0x32ca0de1 (seconds -> ms)
extern float sTuning_150c8dc;               // 0x3e7cf53b
extern FloatVector sTuning_15d976c;         // 0x0610d73b
extern uint32_t sTuning_150c8e0;            // 0x0435d996 (seconds -> ms)
extern float sTuning_150c904;               // 0x5c74d18b
extern Vector3Vector sTuning_15d96fc;       // 0x53d75041
extern Vector3Vector sTuning_15d99fc;       // 0xf3d75063
extern Vector3Vector sTuning_15d97fc;       // 0x33f6c3c4

namespace SP {
namespace {

// @ 0x004D2450  SP::`anonymous namespace'::LoadSpeciesTuning
void LoadSpeciesTuning(bool force)
{
    if (force || !sSpeciesTuningLoaded) {
        sSpeciesTuningLoaded = true;

        IPropManager* propManager = PropertyManager();
        PropertyListPtr propList;
        if (propManager->GetGlobalPropertyList(0x236f18f2, propList.AsPPTypeParam())) {
            ReadPropertyUInt32(propList.mpObject, 0x1368995d, sTuning_15d9674);
            ReadPropertyUInt32(propList.mpObject, 0xd8f99173, sTuning_15d9670);
            ReadPropertyUInt32(propList.mpObject, 0x7717409a, sTuning_150c884);
            sTuning_150c884 *= 1000;
            ReadPropertyFloat(propList.mpObject, 0x11074696, sTuning_150c888);
            ReadPropertyFloat(propList.mpObject, 0x61ecd45c, sTuning_150c88c);
            ReadPropertyFloat(propList.mpObject, 0x518ea467, sTuning_15d9650);
            ReadPropertyFloat(propList.mpObject, 0x518ea466, sTuning_15d9654);
            ReadPropertyFloat(propList.mpObject, 0x518ea465, sTuning_15d9658);
            ReadPropertyFloat(propList.mpObject, 0x518ea464, sTuning_15d965c);
            ReadPropertyFloat(propList.mpObject, 0x518ea463, sTuning_15d9660);
            ReadPropertyFloat(propList.mpObject, 0x518ea462, sTuning_15d9664);
            ReadPropertyFloat(propList.mpObject, 0xd899bec5, sTuning_150c900);
            ReadPropertyFloat(propList.mpObject, 0x4745de1b, sTuning_15d96b8);
            ReadPropertyFloat(propList.mpObject, 0x57634c7c, sTuning_150c890);
            ReadPropertyFloat(propList.mpObject, 0x57634c7d, sTuning_150c894);
            ReadPropertyFloat(propList.mpObject, 0x57634c7e, sTuning_150c898);
            ReadPropertyFloat(propList.mpObject, 0x57634c7f, sTuning_150c89c);
            ReadPropertyFloat(propList.mpObject, 0x57634c78, sTuning_150c8a0);
            ReadPropertyFloat(propList.mpObject, 0x57634c79, sTuning_150c8a4);
            ReadPropertyFloat(propList.mpObject, 0x57634c7a, sTuning_150c8a8);
            ReadPropertyFloat(propList.mpObject, 0xb6ec210b, sTuning_150c8ac);
            ReadPropertyFloat(propList.mpObject, 0x71c653b2, sTuning_150c8b0);
            ReadPropertyFloat(propList.mpObject, 0xffb2d688, sTuning_150c8b4);
            ReadPropertyFloat(propList.mpObject, 0x49c7436e, sTuning_150c8b8);
            ReadPropertyFloat(propList.mpObject, 0x0a97c583, sTuning_150c8bc);
            ReadPropertyFloat(propList.mpObject, 0x6b559718, sTuning_150c8c0);
            ReadPropertyUInt32(propList.mpObject, 0x24cb8070, sTuning_150c8c4);
            GetPropertyAsVector2(propList.mpObject, 0xb237e271, &sTuning_15d9834);
            GetPropertyAsVector2(propList.mpObject, 0xf237e2d7, &sTuning_15d9764);
            GetPropertyAsVector2(propList.mpObject, 0x5237e2d8, &sTuning_15d9a68);
            ReadPropertyFloat(propList.mpObject, 0xd237f426, sTuning_15d9668);
            ReadPropertyBool(propList.mpObject, 0x32380e2c, sTuning_15d966c);
            ReadPropertyUInt32(propList.mpObject, 0x523a8f4c, sTuning_150c8c8);
            ReadPropertyFloat(propList.mpObject, 0x036ad4db, sTuning_150c8cc);
            GetPropertyAsVector2(propList.mpObject, 0x036ad587, &sTuning_15d992c);
            ReadPropertyFloat(propList.mpObject, 0xbf623956, sTuning_150c8d4);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c1, sTuning_150c8e4);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c0, sTuning_150c8e8);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c3, sTuning_150c8ec);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c2, sTuning_150c8f0);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c5, sTuning_150c8f4);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c4, sTuning_150c8f8);
            GetPropertyAsFloat(propList.mpObject, 0xa597b8c7, &sTuning_150c8fc);
            GetPropertyAsFloat(propList.mpObject, 0x81275d0a, &sTuning_150c8d0);
            GetPropertyAsUint32(propList.mpObject, 0x32ca0de1, &sTuning_150c8d8);
            sTuning_150c8d8 *= 1000;
            GetPropertyAsFloat(propList.mpObject, 0x3e7cf53b, &sTuning_150c8dc);

            int numItems = 0;
            float* vectors = 0;
            if (GetPropertyAsFloatArray(propList.get(), 0x0610d73b, &numItems, &vectors)) {
                sTuning_15d976c.resize(numItems);
                for (int i = 0; i < numItems; i++)
                    sTuning_15d976c.mpBegin[i] = vectors[i];
            }

            GetPropertyAsUint32(propList.mpObject, 0x0435d996, &sTuning_150c8e0);
            sTuning_150c8e0 *= 1000;
            GetPropertyAsFloat(propList.mpObject, 0x5c74d18b, &sTuning_150c904);

            int numVectors;
            Vector3* source;
            if (GetPropertyAsVector3Array(propList.get(), 0x53d75041, &numVectors, &source)) {
                sTuning_15d96fc.resize(numVectors);
                for (int i = 0; i < numVectors; i++)
                    sTuning_15d96fc.mpBegin[i] = source[i];
            }
            int arraySize;
            Vector3* vectorData;
            if (GetPropertyAsVector3Array(propList.get(), 0xf3d75063, &arraySize, &vectorData)) {
                sTuning_15d99fc.resize(arraySize);
                for (int i = 0; i < arraySize; i++)
                    sTuning_15d99fc.mpBegin[i] = vectorData[i];
            }
            int size;
            Vector3* src;
            if (GetPropertyAsVector3Array(propList.get(), 0x33f6c3c4, &size, &src)) {
                sTuning_15d97fc.resize(size);
                for (int i = 0; i < size; i++)
                    sTuning_15d97fc.mpBegin[i] = src[i];
            }
        }
    }
}

}  // namespace
}  // namespace SP

// Out-of-namespace caller so the anonymous-namespace function is emitted.
void LoadSpeciesTuning_Emit(bool force) { SP::LoadSpeciesTuning(force); }
