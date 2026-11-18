// Recovered from SporeApp.exe (retail).
//
// 0x00c75460: one step of the planet's asset/model setup.  The function asks
// the resource manager to load the asset stored at this+0x1280, applies the
// filter constraints to it, and, if the model manager does not have it yet,
// registers it with a zero/instance-4 resource key.  It always reports success.
//
// The objects returned by the two getters are only ever called through their
// vtables here, so the interface below names just the slots this function uses.

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

struct ResourceKey {
    uint32_t mType;      // +0
    uint16_t mGroup;     // +4
    uint16_t mInstance;  // +6
};

class IResourceManager {
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    // +0x0c
    virtual bool LoadAsset(const ResourceKey* key, int flag0, int flag1, int flag2,
                           int flag3, int flag4);
};

class IModelManager {
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0C();
    virtual void Slot10();
    virtual void Slot14();
    // +0x18
    virtual bool HasAsset(const ResourceKey* key);
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual void Slot44();
    virtual void Slot48();
    // +0x4c
    virtual void AddAsset(const ResourceKey* key, const ResourceKey* params);
};

// 0x0067dcd0 ::EA::ResourceMan::GetManager
IResourceManager* ResourceManager();
// 0x00401010
IModelManager* ModelManager();
// 0x0102c7f0
void ApplyFilterConstraints(const ResourceKey* key, char second);

class cPlanet {
public:
    bool LoadPlanetAsset();

    char mUnused[0x1280];       // +0x0000 .. +0x127f, not touched here
    ResourceKey mAsset;         // +0x1280
};

// @ 0x00c75460
bool cPlanet::LoadPlanetAsset()
{
    if (ResourceManager()->LoadAsset(&mAsset, 0, 0, 0, 0, 0))
        return true;

    ApplyFilterConstraints(&mAsset, 0);

    if (ModelManager()->HasAsset(&mAsset))
        return true;

    ResourceKey key;
    key.mType = 0;
    key.mGroup = 0;
    key.mInstance = 4;
    ModelManager()->AddAsset(&mAsset, &key);
    return true;
}
