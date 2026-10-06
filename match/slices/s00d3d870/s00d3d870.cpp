// Slice s00d3d870: SP::LoadCreatureGameplayTuning (0x00d3d870).
// /O2 /arch:SSE module (movss float copies).
//
// Loads the creature-game tuning property list (from the terrain manager in the
// editor case 0xad56080c, otherwise from the property manager) and copies ~130
// tuning values into globals through the inline App::Property-style getters
// (pl && pl->GetProperty(id, p) && p->mnType == T  ->  *p->GetValueT()).  cl inlines
// Property::GetValueFloat etc. in the middle of the chain and calls the
// out-of-line copies (0x41e920/0x41e990/0x41ea00/0x41ea70) at the ends, as the
// original does.  The list is then stored in the creature-mode strategy (+0xb4),
// a second list (0xb2bd78ca) is loaded into +0xb8, and modifier tuning reloaded.
#include "types.h"

// ---------------------------------------------------------------- properties
extern const bool     kDefaultBoolValue;
extern const int      kDefaultInt32Value;
extern const uint32_t kDefaultUInt32Value;
extern const float    kDefaultFloatValue;   // 0x015d1168

struct Property {
    void*    mpData;      // +0x00 (array data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10 (0x30 = array / external data)
    uint16_t mnType;      // +0x12

    uint16_t GetType() const { return mnType; }
    void* GetValuePtr()                                         // 0x00446ff0
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    bool* GetValueBool()                                        // 0x0041e920
    {
        if (mnType == 1 || mnType == 0x10)
            return (bool*)GetValuePtr();
        return (bool*)&kDefaultBoolValue;
    }
    int* GetValueInt32()                                        // 0x0041e990
    {
        if (mnType == 9 || mnType == 0x10)
            return (int*)GetValuePtr();
        return (int*)&kDefaultInt32Value;
    }
    uint32_t* GetValueUInt32()                                  // 0x0041ea00
    {
        if (mnType == 10 || mnType == 0x10)
            return (uint32_t*)GetValuePtr();
        return (uint32_t*)&kDefaultUInt32Value;
    }
    float* GetValueFloat()                                      // 0x0041ea70
    {
        if (mnType == 13 || mnType == 0x10)
            return (float*)GetValuePtr();
        return (float*)&kDefaultFloatValue;
    }
};

class cPropertyList {
public:
    virtual int  AddRef();                                       // 0x00
    virtual int  Release();                                      // 0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& result);    // 0x24
};

// eastl::intrusive_ptr<cPropertyList> (just what is used here)
struct PropertyListPtr {
    cPropertyList* mpObject;

    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    cPropertyList* get() const { return mpObject; }
    operator cPropertyList*() const { return mpObject; }
    void reset()
    {
        if (mpObject) {
            cPropertyList* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    PropertyListPtr& operator=(cPropertyList* pObject)
    {
        if (pObject != mpObject) {
            cPropertyList* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    PropertyListPtr& operator=(const PropertyListPtr& x) { return operator=(x.mpObject); }
};

class cPropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyListRaw(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst); // 0x2c

    bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst)
    {
        dst.reset();
        return GetPropertyListRaw(instanceID, groupID, dst);
    }
};

// App::Property static getters (inline in this module)
inline bool GetBool(cPropertyList* pl, uint32_t id, bool& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 1) { v = *p->GetValueBool(); return true; }
    return false;
}
inline bool GetInt(cPropertyList* pl, uint32_t id, int& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 9) { v = *p->GetValueInt32(); return true; }
    return false;
}
inline bool GetUInt(cPropertyList* pl, uint32_t id, uint32_t& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 10) { v = *p->GetValueUInt32(); return true; }
    return false;
}
inline bool GetFloat(cPropertyList* pl, uint32_t id, float& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 13) { v = *p->GetValueFloat(); return true; }
    return false;
}

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };

bool TryGetUIntProperty(cPropertyList* pl, uint32_t id, int& value);        // 0x00410370
bool GetFloatProperty(cPropertyList* pl, uint32_t id, float& value);        // 0x0040cf10
bool GetPropertyAsVector2(cPropertyList* pl, uint32_t id, Vector2& value);  // 0x006a10c0
bool GetPropertyAsVector3(cPropertyList* pl, uint32_t id, Vector3& value);  // 0x006a1110
bool GetPropertyAsFloatArray(cPropertyList* pl, uint32_t id, int& count, float*& values); // 0x006a08b0

// ---------------------------------------------------------------- other types
template <typename T> inline const T& min_(const T& a, const T& b) { return (b < a) ? b : a; }

struct FloatVector {                  // eastl::vector<float>
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    void resize(uint32_t n);          // 0x004afc80
    float& operator[](int i) { return mpBegin[i]; }
};

class cTerrainEditor { public: void* GetCurrentTerrainSphere(); };   // 0x00f67d90
cTerrainEditor* NounManager();                                         // 0x00b3d300 (SP::NounManager)
class TerrainMgr { public: cPropertyList* Fn1(const char* key, bool sphere); }; // 0x00b1daf0
TerrainMgr* GetTerrainMgr();                                           // 0x00b3d320
extern const char kTerrainTuningKeys[];                                // 0x01654c00
cPropertyManager* PropertyManager();                                   // 0x0067de30

struct cCreatureModeStrategy {
    uint32_t pad00[0xb4 / 4];
    PropertyListPtr mpTuning;         // +0xb4
    PropertyListPtr mpTuning2;        // +0xb8
};
extern cCreatureModeStrategy* spInstance_cCreatureModeStrategy;       // 0x0169e294

void LoadCreatureModeExtraTuning(cPropertyList* pl);                   // 0x00d3ca90
namespace cCreatureModeTuning { void LoadPrivateTuningVariables(cPropertyList* pl); } // 0x00d39a10
void ReloadModifierTuning();                                           // 0x00d8b320

// ---------------------------------------------------------------- tuning globals
extern int64_t g_01582df8;
extern int g_01582e5c;
extern Vector2 g_01583330;
extern Vector3 g_01583338;
extern FloatVector g_0169e35c;
extern int g_01582ec4, g_01582ec8;
extern float g_01582ecc, g_01582ed0;
extern float g_01550aa8;
extern float g_01550aac;
extern float g_01582df0;
extern bool g_01582df4;
extern bool g_01582df5;
extern bool g_01582df6;
extern float g_01582e00;
extern float g_01582e04;
extern float g_01582e08;
extern float g_01582e0c;
extern float g_01582e10;
extern float g_01582e14;
extern float g_01582e18;
extern float g_01582e1c;
extern uint32_t g_01582e20;
extern uint32_t g_01582e24;
extern float g_01582e28;
extern float g_01582e2c;
extern float g_01582e30;
extern float g_01582e34;
extern float g_01582e38;
extern float g_01582e3c;
extern float g_01582e40;
extern float g_01582e44;
extern float g_01582e48;
extern float g_01582e4c;
extern float g_01582e50;
extern float g_01582e54;
extern int g_01582e58;
extern float g_01582e60;
extern float g_01582e64;
extern float g_01582e68;
extern float g_01582e6c;
extern float g_01582e70;
extern float g_01582e74;
extern float g_01582e78;
extern float g_01582e7c;
extern float g_01582e80;
extern float g_01582e84;
extern float g_01582e88;
extern float g_01582e8c;
extern float g_01582eb0;
extern uint32_t g_01582eb4;
extern uint32_t g_01582eb8;
extern float g_01582ebc;
extern float g_01582ec0;
extern float g_01582ed4;
extern float g_01582ed8;
extern float g_01582edc;
extern float g_01582ee0;
extern float g_01582ee4;
extern uint32_t g_01582ee8;
extern float g_01582eec;
extern float g_01582ef0;
extern float g_01582ef4;
extern float g_01582ef8;
extern float g_01582efc;
extern uint32_t g_01582f00;
extern uint32_t g_01582f04;
extern float g_01582f08;
extern float g_01582f0c;
extern uint32_t g_01582f10;
extern uint32_t g_01582f14;
extern float g_01582f18;
extern float g_01582f1c;
extern float g_01582f20;
extern float g_01582f24;
extern float g_01582f28;
extern float g_01582f2c;
extern float g_01582f30;
extern int g_01582f34;
extern float g_01582f38;
extern float g_01582f3c;
extern float g_01582f40;
extern float g_01582f44;
extern float g_01582f48;
extern uint32_t g_01582f4c;
extern float g_01582f50;
extern float g_01582f54;
extern float g_01582f58;
extern float g_01582f5c;
extern float g_01582f60;
extern float g_01582f64;
extern float g_01582f68;
extern float g_01582f6c;
extern float g_01582f70;
extern float g_01582f74;
extern float g_01582f78;
extern float g_01582f7c;
extern float g_01582f80;
extern float g_01582f84;
extern float g_01582f88;
extern float g_01582f8c;
extern float g_01582f90;
extern uint32_t g_01582f94;
extern uint32_t g_01582f98;
extern float g_01582f9c;
extern float g_01582fa0;
extern float g_01582fa4;
extern float g_01582fa8;
extern int g_01582fac;
extern int g_01582fb0;
extern int g_01582fb4;
extern float g_01582fb8;
extern float g_01582fbc;
extern float g_01582fc0;
extern int g_01582fc4;
extern int g_01582fc8;
extern int g_01582fcc;
extern int g_01582fd0;
extern int g_01582fd4;
extern float g_01582fd8;
extern float g_01582fdc;
extern float g_01582fe0;
extern float g_01582fe4;
extern float g_01582fe8;
extern float g_01582fec;
extern float g_01582ff0;
extern float g_01582ff4;
extern float g_01582ff8;
extern float g_0169e278;
extern float g_0169e27c;
extern float g_0169e280;
extern float g_0169e284;
extern float g_0169e288;
extern float g_0169e28c;
extern bool g_0169e290;
extern bool g_0169e291;

namespace SP {

// @ 0x00d3d870
void LoadCreatureGameplayTuning(uint32_t groupID, uint32_t instanceID)
{
    PropertyListPtr pl;

    if (groupID == 0xad56080c) {
        pl = GetTerrainMgr()->Fn1(kTerrainTuningKeys + 1, NounManager()->GetCurrentTerrainSphere() != 0);
    } else {
        PropertyManager()->GetPropertyList(instanceID, groupID, pl);
    }

    if (pl) {
        int seconds = 0;
        GetInt(pl, 0x9226de4cu, seconds);
        g_01582df8 = seconds * 1000;
        GetFloat(pl, 0xbaf251a1u, g_01582df0);
        GetBool(pl, 0x9040f372u, g_01582df4);
        GetFloat(pl, 0x724289feu, g_01582e00);
        GetFloat(pl, 0xad0d6a72u, g_01582e04);
        GetFloat(pl, 0xd02942aau, g_01582e08);
        GetFloat(pl, 0x2beb6558u, g_01582e0c);
        GetFloat(pl, 0x2acbad8u, g_01582e10);
        GetFloat(pl, 0x9a4955ddu, g_01582e14);
        GetFloat(pl, 0xffca7ffu, g_01582e18);
        GetFloat(pl, 0x511b50d8u, g_01582e1c);
        GetUInt(pl, 0x31d51f1du, g_01582e20);
        GetUInt(pl, 0x723bbffcu, g_01582e24);
        GetFloat(pl, 0xd3d10a58u, g_01582e28);
        GetFloat(pl, 0xd6e7812fu, g_01582e2c);
        GetFloat(pl, 0x31b148ccu, g_01582e30);
        GetFloat(pl, 0x11b148cdu, g_01582e34);
        GetFloat(pl, 0x31d515aeu, g_0169e278);

        int count = 0;
        float* values = 0;
        if (GetPropertyAsFloatArray(pl, 0xe39b27bfu, count, values)) {
            g_0169e35c.resize(count);
            for (int i = 0; i < count; i++)
                g_0169e35c[i] = values[i];
        }

        GetFloat(pl, 0xb67c4f9au, g_01582f88);
        GetFloat(pl, 0xf5c2bf12u, g_01582f8c);
        GetFloat(pl, 0x3964a33du, g_01582f90);
        GetFloat(pl, 0x11074694u, g_01582e38);
        GetFloat(pl, 0x2c73027u, g_01582e3c);
        GetFloat(pl, 0x2c73028u, g_01582e40);
        GetFloat(pl, 0x2c73029u, g_01582e44);
        GetFloat(pl, 0x12292735u, g_0169e27c);
        GetFloat(pl, 0x32292736u, g_01582e48);
        GetFloat(pl, 0x92292737u, g_01582e4c);
        GetFloat(pl, 0x12292738u, g_01582e50);
        GetFloat(pl, 0x8c248961u, g_01582e54);
        GetInt(pl, 0xf15cd7e4u, g_01582e58);
        GetInt(pl, 0x51cbead0u, g_01582e5c);
        g_01582e58 *= 1000;
        g_01582e5c *= 1000;

        GetFloat(pl, 0x7163782eu, g_01582e74);
        GetFloat(pl, 0x48a66eau, g_01582e60);
        GetFloat(pl, 0x48a66eeu, g_01582e64);
        GetFloat(pl, 0x6284c0cu, g_01582e68);
        GetFloat(pl, 0x1269b5b5u, g_0169e280);
        GetFloat(pl, 0x7af7926u, g_01582e6c);
        GetFloat(pl, 0x75bb1b3cu, g_0169e284);
        GetFloat(pl, 0x284e6c1u, g_01582e70);
        GetFloat(pl, 0x523a480eu, g_01582e88);
        GetFloat(pl, 0x1ad0639u, g_01582e78);
        GetFloat(pl, 0x1c2301bu, g_01582e84);
        GetFloat(pl, 0x25476fcu, g_01582e7c);
        GetFloat(pl, 0x95f7ee0cu, g_01582e80);
        GetFloat(pl, 0x967f9546u, g_01582ed4);
        GetFloat(pl, 0x4bc7f666u, g_0169e288);
        GetFloat(pl, 0xad530307u, g_01582ed8);
        GetFloat(pl, 0xb5531079u, g_01582edc);
        GetFloat(pl, 0xeeaa8367u, g_01582ee0);
        GetFloat(pl, 0x8b1fd1f1u, g_01582ee4);
        GetFloat(pl, 0x13138bd2u, g_01582ebc);
        GetFloat(pl, 0xb070eba6u, g_01582ec0);
        GetUInt(pl, 0xff7d4a77u, g_01582ee8);
        GetFloat(pl, 0x3da92194u, g_01582eec);
        GetFloat(pl, 0x687fbcecu, g_01582ef0);
        GetFloat(pl, 0xdf6747c9u, g_01582ef4);
        GetFloat(pl, 0x516e7b63u, g_01582ef8);
        GetBool(pl, 0xa5e247f0u, g_01582df5);
        GetFloat(pl, 0x18ce7bc3u, g_01582efc);
        GetUInt(pl, 0x3194b523u, g_01582f00);
        GetUInt(pl, 0x2f343a3cu, g_01582f04);
        GetFloat(pl, 0xa5b8d733u, g_01582f08);
        GetFloat(pl, 0xe1532d2du, g_01582f0c);
        GetUInt(pl, 0x5c68a779u, g_01582f10);
        GetUInt(pl, 0xfb2020b9u, g_01582f14);
        GetFloat(pl, 0x95e575c6u, g_01582f18);
        GetFloat(pl, 0x770f1ac5u, g_01582f1c);
        GetFloat(pl, 0xa1247843u, g_01582f20);
        GetFloat(pl, 0x93110e94u, g_01582f24);
        GetFloat(pl, 0x3215f0afu, g_01582f28);
        GetFloat(pl, 0x25e6ad1cu, g_01582f2c);
        GetPropertyAsVector2(pl, 0xd0fc1cacu, g_01583330);
        GetFloat(pl, 0xe11cb6ccu, g_01582f30);
        GetInt(pl, 0xdb370fb5u, g_01582f34);
        GetFloat(pl, 0xbf5e5d72u, g_01582f38);
        g_01582f38 = g_01582f38 * g_01582f38;
        GetFloat(pl, 0x65525b4eu, g_01582f3c);
        GetFloat(pl, 0x6459830bu, g_01582f40);
        GetFloat(pl, 0xfd87b588u, g_01582f44);
        g_01582f44 = g_01582f44 * g_01582f44;
        GetFloat(pl, 0xbcf97143u, g_01582f48);
        GetFloat(pl, 0xcff3e974u, g_01550aa8);
        GetFloat(pl, 0x3fbd28e4u, g_01550aac);
        GetPropertyAsVector3(pl, 0x99646e30u, g_01583338);
        GetUInt(pl, 0x37ae622u, g_01582f4c);
        g_01582f4c = min_(g_01582f4c, (uint32_t)2);
        GetFloat(pl, 0x3da2a2d2u, g_01582f50);
        GetFloat(pl, 0xe6f2fce8u, g_01582f54);
        GetFloat(pl, 0xceb65676u, g_01582f58);
        GetFloat(pl, 0xce78e0d8u, g_01582f5c);
        GetFloat(pl, 0x274fc6e0u, g_01582f60);
        GetBool(pl, 0xf7e9bdeeu, g_01582df6);
        GetFloat(pl, 0x5e352b93u, g_01582f64);
        GetFloat(pl, 0xa6a4f0bu, g_0169e28c);
        GetFloat(pl, 0x41752dd5u, g_01582f68);
        GetFloat(pl, 0xda14d908u, g_01582f6c);
        GetFloat(pl, 0x90c1b65cu, g_01582f70);
        GetFloat(pl, 0xa3e580f3u, g_01582f74);
        GetFloat(pl, 0x4e229d3eu, g_01582f78);
        GetFloat(pl, 0x832f6d3du, g_01582f7c);
        GetFloat(pl, 0x553c6e30u, g_01582f80);
        GetFloat(pl, 0x4d5f54b6u, g_01582f84);
        GetFloat(pl, 0x5933f8f4u, g_01582fa4);
        GetFloat(pl, 0x397b295au, g_01582fa8);
        GetBool(pl, 0x42b6c4b6u, g_0169e291);
        GetInt(pl, 0x22e5d26bu, g_01582fac);
        GetInt(pl, 0x22e5d268u, g_01582fb0);
        GetInt(pl, 0x22e5d269u, g_01582fb4);
        GetFloat(pl, 0x94a76e85u, g_01582fb8);
        GetFloat(pl, 0x196c4280u, g_01582fbc);
        GetFloat(pl, 0xdcbc7c1eu, g_01582fc0);
        GetInt(pl, 0xbcfd2a42u, g_01582fc4);
        GetInt(pl, 0xbcfd2a41u, g_01582fc8);
        GetInt(pl, 0xbcfd2a40u, g_01582fcc);
        GetInt(pl, 0xbcfd2a47u, g_01582fd0);
        GetInt(pl, 0xbcfd2a46u, g_01582fd4);
        GetFloat(pl, 0x9efa4612u, g_01582fd8);
        GetFloat(pl, 0x7195edf1u, g_01582eb0);
        GetUInt(pl, 0xac640ba9u, g_01582eb4);
        GetUInt(pl, 0x1d7441c9u, g_01582eb8);
        GetUInt(pl, 0x1810c6e0u, g_01582f94);
        GetUInt(pl, 0x6a86c027u, g_01582f98);
        GetFloat(pl, 0x954f8dccu, g_01582f9c);
        GetFloat(pl, 0xdcd5e42eu, g_01582fa0);
        GetBool(pl, 0xc3fff105u, g_0169e290);
        GetFloat(pl, 0x600e59cdu, g_01582fdc);
        GetFloat(pl, 0xa2433d86u, g_01582fe0);
        GetFloat(pl, 0xdb821babu, g_01582fe4);
        GetFloat(pl, 0x3d73d3b0u, g_01582fe8);
        GetFloat(pl, 0x39697de6u, g_01582fec);
        GetFloat(pl, 0x89e27397u, g_01582e8c);
        GetFloat(pl, 0xdec48a8fu, g_01582ff0);
        GetFloat(pl, 0xdcc9694fu, g_01582ff4);
        GetFloat(pl, 0x7dc0a48au, g_01582ff8);

        LoadCreatureModeExtraTuning(pl);
        cCreatureModeTuning::LoadPrivateTuningVariables(pl);
    }

    spInstance_cCreatureModeStrategy->mpTuning = pl;

    if (PropertyManager()->GetPropertyList(0xb2bd78ca, groupID, pl)) {
        TryGetUIntProperty(pl, 0xb136a2d1u, g_01582ec4);
        TryGetUIntProperty(pl, 0xb136a2d2u, g_01582ec8);
        GetFloatProperty(pl, 0xe8ad4f2du, g_01582ecc);
        GetFloatProperty(pl, 0x4453df5du, g_01582ed0);
    }

    spInstance_cCreatureModeStrategy->mpTuning2 = pl;
    ReloadModifierTuning();
}

} // namespace SP
