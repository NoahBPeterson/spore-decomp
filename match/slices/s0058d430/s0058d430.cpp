// slice s0058d430 -- anonymous-namespace cEditorCheat::Execute (4768 B): the "editor" console
// cheat (load / timing / zcorp / rename / save / savebinary / dumpPalettes / validate /
// dumpGeomInfo).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no float arithmetic here; no /EHsc:
// the string/vector locals get no EH frame).
#include "types.h"

void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags,
                     const char* file, int line);                // 0x00f473a0
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                  // 0x00f473a0 (same EA allocator entry)
void operator delete[](void* p);                                 // 0x00f47380
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char* a, const char* b);

struct ResourceKey {
    uint32_t instance, type, group;
};

// ---- EASTL pieces (inline, as in EASTL) ---------------------------------------------
extern char gEmptyString[];                                      // 0x01667bac

struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    string8() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
    __forceinline ~string8() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            delete[] mpBegin;
    }
    const char* c_str() const { return mpBegin; }
};

struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16() : mpBegin((wchar_t*)gEmptyString), mpEnd((wchar_t*)gEmptyString),
                 mpCapacity((wchar_t*)gEmptyString + 1) {}
    __forceinline ~string16() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            delete[] (char*)mpBegin;
    }
    const wchar_t* c_str() const { return mpBegin; }
};

struct sp_vector_allocator {
    uint32_t mFlags;
    sp_vector_allocator() {}
};

struct ResourceKeyVector {                                       // eastl::vector<ResourceKey, sp_vector_allocator>
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    sp_vector_allocator mAllocator;
    ResourceKeyVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~ResourceKeyVector() {
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            delete[] (char*)mpBegin;
    }
    bool empty() const { return mpBegin == mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
    ResourceKey& operator[](int i) { return mpBegin[i]; }
    void push_back(const ResourceKey& key);                      // 0x004e19a0
};

struct FloatVector {                                             // eastl::vector<float, sp_vector_allocator>
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    sp_vector_allocator mAllocator;
    __forceinline explicit FloatVector(int n) {
        mpBegin = n ? (float*)new("Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1) char[n * sizeof(float)] : 0;
        mpCapacity = mpBegin + n;
        for (float* p = mpBegin; p != mpCapacity; ++p)
            *(uint32_t*)p = 0;
        mpEnd = mpCapacity;
    }
    __forceinline ~FloatVector() {
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            delete[] (char*)mpBegin;
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    float& operator[](int i) { return mpBegin[i]; }
};

struct MeshVertex;
struct VertexVector {                                            // vector of geometry records
    MeshVertex* mpBegin;
    MeshVertex* mpEnd;
    MeshVertex* mpCapacity;
    sp_vector_allocator mAllocator;
    VertexVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~VertexVector() {
        DestroyValues(mpBegin, mpEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            delete[] (char*)mpBegin;
    }
    void DestroyValues(MeshVertex* first, MeshVertex* last);    // 0x004243e0
};

// ---- resources -----------------------------------------------------------------------
struct IResource {
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual void* Cast(uint32_t typeID);                         // +0x0c
};

template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    explicit AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    __forceinline T** AsPointer() {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator bool() const { return mpObject != 0; }
};

struct IResourceFilter {
    virtual ~IResourceFilter() {}
};

struct ResourceKeyFilter : IResourceFilter {                     // vtable 0x013eb898
    uint32_t mInstance;
    uint32_t mGroup;
    uint32_t mType;
    uint32_t mMask;
    ResourceKeyFilter() : mInstance(0xffffffff), mGroup(0xffffffff), mType(0xffffffff), mMask(0xffffffff) {}
    virtual bool IsValid(const ResourceKey& key);
};

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool GetResource(const ResourceKey* key, IResource** ppResource,
                             int a, int b, int c, int d);         // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual bool WriteResource(IResource* res, int a, void* saveArea, int b,
                               const ResourceKey* key);          // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual int GetResourceKeyList(ResourceKeyVector* keys, IResourceFilter* filter, int flags);   // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void v78();
    virtual bool GetFileName(const ResourceKey* key, string16* name);   // +0x7c
};

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    ResourceKey mResourceKey;                                    // +0x08
    cPropertyList();                                             // 0x006a1c40
};

struct IPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** ppList);   // +0x2c
};

struct cEditorModelResource {                                    // 0x3c609f8
    uint32_t pad0[2];
    ResourceKey mKey;                                            // +0x08
    uint32_t pad14;
    uint32_t mModelType;                                         // +0x18
};

struct cLocalizedName {                                          // 0x30bdee3
    const wchar_t* GetText();                                    // 0x00414e10
};

struct cSPEditorModelResource {                                  // 0xac bytes
    virtual int AddRef();
    virtual int Release();
    uint32_t mRefCount;                                          // +0x04
    ResourceKey mKey;                                            // +0x08
    uint32_t pad14[(0xac - 0x14) / 4];
    cSPEditorModelResource();                                    // 0x004b9c70
};

// Holder whose (out-of-line) constructor stores the pointer and AddRefs it; the cheat then
// works on the raw pointer and releases it itself (the holder is never read again).
struct ModelResourceRef {
    cSPEditorModelResource* mpObject;
    explicit ModelResourceRef(cSPEditorModelResource* p);        // 0x00572660
};

// ---- editor --------------------------------------------------------------------------
struct cSPEditorModel {
    virtual void SetName(const wchar_t* name);                   // +0x00
    uint32_t GetCreationID();                                    // 0x004ae000
    void SaveResource(cSPEditorModelResource* res);              // 0x004af260
};

struct IMessageListener {
    virtual void v00();
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);   // +0x04
};

struct ValidityBits {                                            // eastl::bitset<128>
    uint32_t mWord[4];
    bool test(uint32_t i) const {
        if (i < 128)
            return (mWord[i >> 5] & (1u << (i & 31))) != 0;
        return false;
    }
};

struct LoadParams { uint32_t v[4]; };

struct cAppModeEditorBase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c();
    virtual cSPEditorModel* GetModel();                          // +0x40
    virtual uint32_t GetEditorConfig();                          // +0x44
    uint32_t pad04[3];
    IMessageListener mMessageListener;                           // +0x10
    uint32_t pad14[(0x2a8 - 0x14) / 4];
    uint32_t mModelType;                                         // +0x2a8
    uint32_t mSaveAreaID;                                        // +0x2ac

    void LoadModel(const ResourceKey& key, LoadParams params, int flags);   // 0x0058cee0
    int ScoreCreatureForZCorp();                                 // 0x00574b40
    void SaveModel(const ResourceKey* key, int flags);           // 0x0057f6c0
};

struct MessageBasicRC5 {
    uint32_t mHeader[2];
    uint32_t mData[5];
    explicit MessageBasicRC5(int a);                             // 0x00421c80
    ~MessageBasicRC5();                                          // 0x00421cf0
};

struct cUIHint {
    uint32_t pad0[0x78 / 4];
    struct cString { const wchar_t* GetString(); } mText;        // +0x78, GetString 0x006b55c0
};

struct cUIHints {
    cUIHint* FindByID(uint32_t id);                              // 0x0067aee0
};

// ---- ArgScript -----------------------------------------------------------------------
namespace EA { namespace ArgScript {
struct cIParser;
struct cArguments {
    const char** MainArguments(int& count, int start, int max); // 0x00838020
};
void Output(cIParser* parser, const char* fmt, ...);             // 0x00841000
} }

// ---- free functions and globals ------------------------------------------------------
IResourceManager* GetManager();                                  // 0x0067dcd0
IPropertyManager* PropertyManager();                             // 0x0067de30
cUIHints* UIHints();                                             // 0x0067cac0
bool SPKeyFromName(ResourceKey* key, const char* name, uint32_t defType, uint32_t defGroup);   // 0x0068d5a0
void SPNameFromKey(const ResourceKey* key, string8* name, int flags);   // 0x0068d290
uint32_t EditorEntityToResourceType(uint32_t entity, int flags); // 0x004bbd20
uint32_t GetConfigFromModelType(uint32_t modelType);             // 0x00432f10
string16 ConvertToString16(const char* text, int length);        // 0x0093c5a0
uint32_t CreationIDFromModel(uint32_t id);                       // 0x00572c50
void* GetSaveArea(uint32_t id);                                  // 0x006b1f90
bool SavePropertyList(cPropertyList* props, void* saveArea, int flags);   // 0x006b1d50
void InitializeValidityData();                                   // 0x004ebe20
void DumpPalettes();                                             // 0x004eb980
void GetResourceDisplayName(const ResourceKey* key, string16* name, int flags);   // 0x00b1e4d0
ValidityBits CalculateValidity(cEditorModelResource* model, ValidityBits mask, int flags);   // 0x004f3de0
bool IsValid(ValidityBits result, ValidityBits mask);            // 0x004f3d60
uint32_t GetValidityHintID(uint32_t bit);                        // 0x004f3c40
bool GetPropertyAsKey(cPropertyList* props, uint32_t id, ResourceKey* key);   // 0x006a1250
void ReadGeometry(void* model, VertexVector* out);               // 0x0072fff0
float ComputeGeometryMetric(VertexVector* geom);                 // 0x00572b30
void SetPropertyKeys(cPropertyList* props, uint32_t id, int count, const ResourceKey* keys);   // 0x006a0ee0
void SetPropertyFloats(cPropertyList* props, uint32_t id, int count, const float* values);    // 0x006a0dc0

extern uint32_t kGroupCreature;                                  // 0x0150ce74
extern uint32_t kGroupBuilding;                                  // 0x0150ce78
extern uint32_t kGroupVehicle;                                   // 0x0150ce7c
extern uint32_t kGroupUFO;                                       // 0x0150ce80
extern uint32_t kGroupFlora;                                     // 0x0150ce84
extern uint32_t kGroupCell;                                      // 0x0150ce88
extern LoadParams kDefaultLoadParams;                            // 0x015dac10
extern bool sTimingEnabled;                                      // 0x015deff8
extern bool sValidityInitialized;                                // 0x015da6e4
extern ValidityBits kValidityAll;                                // 0x015da860
extern ValidityBits kValidityLoadable;                           // 0x015da9c8
extern ValidityBits kValidityEditable;                           // 0x015da784
extern ValidityBits kValidityPlayable;                           // 0x015da7c4
extern ValidityBits kValidityPollinatable;                       // 0x015dab94
extern ValidityBits kValidityWarning;                            // 0x015daa40

// Default package group of an editor model type (same TU, called out of line).
uint32_t GetModelGroup(uint32_t type);                           // 0x00572110
__declspec(noinline) uint32_t GetModelGroup(uint32_t type) {
    switch (type) {
    case 0x3d97a8e4: return kGroupCreature;
    case 0x2399be55: return kGroupVehicle;
    case 0x24682294: return kGroupUFO;
    case 0x438f6347: return kGroupCell;
    case 0x476a98c7: return kGroupFlora;
    default:         return kGroupBuilding;
    }
}

__forceinline void FixupModelKey(ResourceKey& key) {
    if (key.group == 0xffffffff) {
        switch (key.type) {
        case 0x3d97a8e4: key.group = kGroupCreature; break;
        case 0x2399be55: key.group = kGroupVehicle; break;
        case 0x24682294: key.group = kGroupUFO; break;
        case 0x2b978c46: key.group = kGroupBuilding; break;
        case 0x438f6347: key.group = kGroupCell; break;
        case 0x476a98c7: key.group = kGroupFlora; break;
        }
    }
    if (key.type == 0x1a99b06b && (key.group & 0xc0000000) == 0x40000000)
        key.type = EditorEntityToResourceType((key.group >> 16) & 0xff, 0);
}

namespace {

class cEditorCheat {
public:
    virtual void Execute(EA::ArgScript::cArguments* args);       // +0x00
    virtual const char* GetDescription(int mode);                // +0x04
    virtual void v08();
    virtual int AddRef();                                        // +0x0c
    virtual int Release();                                       // +0x10

    EA::ArgScript::cIParser* mParser;                            // +0x04
    int mRefCount;                                               // +0x08
    void* mState;                                                // +0x0c
    cAppModeEditorBase* mEditorApp;                              // +0x10

    __forceinline void ReportFailures(const ValidityBits& mask, const ValidityBits& result);
};

__forceinline void cEditorCheat::ReportFailures(const ValidityBits& mask, const ValidityBits& result) {
    for (uint32_t i = 0; i < 0x1c; ++i) {
        if (mask.test(i) && result.test(i)) {
            uint32_t hintID = GetValidityHintID(i);
            cUIHint* hint = UIHints()->FindByID(hintID);
            if (hint)
                EA::ArgScript::Output(mParser, "   * %ls\n", hint->mText.GetString());
        }
    }
}

// @ 0x0058d430
void cEditorCheat::Execute(EA::ArgScript::cArguments* args) {
    AutoRefCount<cEditorCheat> self(this);
    int count;
    const char** argv = args->MainArguments(count, 0, 0x7fffffff);

    if (count == 2 && !_stricmp(argv[0], "load")) {
        ResourceKey key;
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        if (!SPKeyFromName(&key, argv[1], mEditorApp->mModelType, 0xffffffff)) {
            EA::ArgScript::Output(mParser, "unable to get resource key from filename\n");
            return;
        }
        FixupModelKey(key);
        AutoRefCount<IResource> res;
        cEditorModelResource* model;
        if (!GetManager()->GetResource(&key, res.AsPointer(), 0, 0, 0, 0) || !res ||
            !(model = (cEditorModelResource*)res->Cast(0x3c609f8))) {
            EA::ArgScript::Output(mParser, "unable to load model resource\n");
        } else {
            uint32_t config = GetConfigFromModelType(model->mModelType);
            if (mEditorApp->GetEditorConfig() != config) {
                EA::ArgScript::Output(mParser, "switching editor config...\n");
                MessageBasicRC5 msg(0);
                msg.mData[0] = config;
                mEditorApp->mMessageListener.HandleMessage(0x22d308b, &msg);
            }
            string8 name;
            SPNameFromKey(&key, &name, 0);
            EA::ArgScript::Output(mParser, "loading model '%s'\n", name.c_str());
            mEditorApp->LoadModel(key, kDefaultLoadParams, 0);
        }
    } else if (count >= 1 && count <= 2 && !_stricmp(argv[0], "timing")) {
        if (count == 1)
            sTimingEnabled = !sTimingEnabled;
        else if (count == 2 && !_stricmp(argv[1], "on"))
            sTimingEnabled = true;
        else if (count == 2 && !_stricmp(argv[1], "off"))
            sTimingEnabled = false;
        EA::ArgScript::Output(mParser, sTimingEnabled ? "Timing: ON\n" : "Timing: OFF\n");
    } else if (count == 1 && !_stricmp(argv[0], "zcorp")) {
        EA::ArgScript::Output(mParser, "ZCorp Score: %d\n", mEditorApp->ScoreCreatureForZCorp());
    } else if (count == 2 && !_stricmp(argv[0], "rename")) {
        mEditorApp->GetModel()->SetName(ConvertToString16(argv[1], -1).c_str());
        EA::ArgScript::Output(mParser, "model renamed to '%s'\n", argv[1]);
    } else if (count >= 1 && count <= 2 && !_stricmp(argv[0], "save")) {
        ResourceKey key;
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        if (count > 1)
            SPKeyFromName(&key, argv[1], 0, 0);
        else
            key.instance = CreationIDFromModel(mEditorApp->GetModel()->GetCreationID());
        key.type = mEditorApp->mModelType;
        key.group = GetModelGroup(key.type);
        mEditorApp->SaveModel(&key, 0);
    } else if (count >= 1 && count <= 2 && !_stricmp(argv[0], "savebinary")) {
        ResourceKey key;
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        if (count > 1)
            SPKeyFromName(&key, argv[1], 0, 0);
        else
            key.instance = CreationIDFromModel(mEditorApp->GetModel()->GetCreationID());
        key.type = mEditorApp->mModelType;
        key.group = GetModelGroup(key.type);
        ModelResourceRef ref(new("Editor", 0, 0, 0, 0) cSPEditorModelResource());
        cSPEditorModelResource* res = ref.mpObject;
        mEditorApp->GetModel()->SaveResource(res);
        res->mKey = key;
        key.type = 0x1a99b06b;
        GetManager()->WriteResource((IResource*)res, 0, GetSaveArea(mEditorApp->mSaveAreaID), 0, &key);
        res->Release();
    } else if (count == 1 && !_stricmp(argv[0], "dumpPalettes")) {
        if (!sValidityInitialized)
            InitializeValidityData();
        DumpPalettes();
    } else if (count == 2 && !_stricmp(argv[0], "validate")) {
        ResourceKeyFilter filter;
        ResourceKeyVector keys;
        ResourceKey key;
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        SPKeyFromName(&key, argv[1], 0xffffffff, 0xffffffff);
        filter.mInstance = key.instance;
        filter.mGroup = key.group;
        filter.mType = key.type;
        GetManager()->GetResourceKeyList(&keys, &filter, 0);
        if (keys.empty())
            keys.push_back(key);
        int numKeys = keys.size();
        string16 fileName;
        for (int i = 0; i < numKeys; ++i) {
            ResourceKey& modelKey = keys[i];
            GetManager()->GetFileName(&modelKey, &fileName);
            GetResourceDisplayName(&modelKey, &fileName, 0);
            FixupModelKey(modelKey);
            AutoRefCount<IResource> res;
            cEditorModelResource* model;
            if (!GetManager()->GetResource(&modelKey, res.AsPointer(), 0, 0, 0, 0) || !res ||
                !(model = (cEditorModelResource*)res->Cast(0x3c609f8))) {
                EA::ArgScript::Output(mParser, "unable to load model resource\n");
                return;
            }
            ResourceKey nameKey = model->mKey;
            nameKey.type = 0x30bdee3;
            cLocalizedName* name = 0;
            AutoRefCount<IResource> nameRes;
            if (GetManager()->GetResource(&nameKey, nameRes.AsPointer(), 0, 0, 0, 0))
                name = nameRes ? (cLocalizedName*)nameRes->Cast(0x30bdee3) : 0;
            EA::ArgScript::Output(mParser, "Validating filename: '%ls', resource name: ", fileName.c_str());
            if (name)
                EA::ArgScript::Output(mParser, "'%ls'\n", name->GetText());
            else
                EA::ArgScript::Output(mParser, "<No Name>\n");

            ValidityBits result = CalculateValidity(model, kValidityAll, 0);
            if (!IsValid(result, kValidityLoadable)) {
                EA::ArgScript::Output(mParser, "  Model failed the Loadable test for the following reasons:\n");
                ReportFailures(kValidityLoadable, result);
            }
            if (!IsValid(result, kValidityEditable)) {
                EA::ArgScript::Output(mParser, "  Model failed the Editable test for the following reasons:\n");
                ReportFailures(kValidityEditable, result);
            }
            if (!IsValid(result, kValidityPlayable)) {
                EA::ArgScript::Output(mParser, "  Model failed the Playable test for the following reasons:\n");
                ReportFailures(kValidityPlayable, result);
            }
            if (!IsValid(result, kValidityPollinatable)) {
                EA::ArgScript::Output(mParser, "  Model failed the Pollinatable test for the following reasons:\n");
                ReportFailures(kValidityPollinatable, result);
            }
            if (!IsValid(result, kValidityWarning)) {
                EA::ArgScript::Output(mParser, "  Model failed the Warning test for the following reasons:\n");
                ReportFailures(kValidityWarning, result);
            }
            if (IsValid(result, kValidityAll))
                EA::ArgScript::Output(mParser, "  Model is valid.\n");
        }
    } else if (count == 1 && !_stricmp(argv[0], "dumpGeomInfo")) {
        for (int index = 0x61; index < 0x67; ++index) {
            AutoRefCount<cPropertyList> props(new("Editor", 0, 0, 0, 0) cPropertyList());
            uint32_t groupBits = (uint32_t)(uint8_t)index << 16;
            props->mResourceKey.instance = 0x6cc3c0c9;
            props->mResourceKey.type = 0xb1b104;
            props->mResourceKey.group = groupBits | 0x40000100;
            ResourceKeyFilter filter;
            filter.mGroup = groupBits | 0x40006000;
            filter.mType = 0xb1b104;
            ResourceKeyVector keys;
            GetManager()->GetResourceKeyList(&keys, &filter, 0);
            FloatVector values(keys.size());
            AutoRefCount<cPropertyList> geomProps;
            int numKeys = keys.size();
            for (int i = 0; i < numKeys; ++i) {
                if (!PropertyManager()->GetPropertyList(keys[i].instance, keys[i].group, geomProps.AsPointer()))
                    continue;
                ResourceKey modelKey;
                modelKey.instance = 0;
                modelKey.type = 0;
                modelKey.group = 0;
                if (!GetPropertyAsKey(geomProps.get(), 0xf9efbb, &modelKey))
                    continue;
                AutoRefCount<IResource> res;
                if (GetManager()->GetResource(&modelKey, res.AsPointer(), 0, 0, 0, 0)) {
                    VertexVector geometry;
                    ReadGeometry(res ? res->Cast(0x2f4e681b) : 0, &geometry);
                    values[i] = ComputeGeometryMetric(&geometry);
                }
            }
            SetPropertyKeys(props.get(), 0x66f235b, keys.size(), keys.mpBegin);
            SetPropertyFloats(props.get(), 0x66f235c, values.size(), values.mpBegin);
            SavePropertyList(props.get(), GetSaveArea(0x11ac19e), 0);
        }
        EA::ArgScript::Output(mParser, GetDescription(1));
    }
}

}  // namespace
