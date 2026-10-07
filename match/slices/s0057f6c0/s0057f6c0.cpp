// slice s0057f6c0 -- SP::cAppModeEditorBase::SaveModel (dev-PDB name, 3119 bytes).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: the smart pointers and
// strings below have dtors but the original has no EH frame).
// Retail cAppModeEditorBase layout differs from the 2008 PDB, so members are placed by the
// offsets the disassembly uses (names follow s005744b0 and ModAPI's Editor.h where they agree).
#include "types.h"
#include <intrin.h>
#pragma intrinsic(_InterlockedExchange)

void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);   // 0x00F473A0
void operator delete[](void* p);                                                                                       // 0x00F47380

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// ---- EA intrusive_ptr --------------------------------------------------------------------
template <class T> inline void intrusive_ptr_add_ref(T* p) { p->AddRef(); }
template <class T> inline void intrusive_ptr_release(T* p) { p->Release(); }

template <class T> class intrusive_ptr {
public:
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) intrusive_ptr_add_ref(mpObject); }
    ~intrusive_ptr() { if (mpObject) intrusive_ptr_release(mpObject); }
    intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                intrusive_ptr_add_ref(pObject);
            mpObject = pObject;
            if (pTemp)
                intrusive_ptr_release(pTemp);
        }
        return *this;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// ---- EASTL pieces ------------------------------------------------------------------------
extern wchar_t gEmptyString[];   // 0x01667bac

namespace eastl {
template <class T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    basic_string() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
    ~basic_string() { DeallocateSelf(); }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator delete[](mpBegin);
        }
    }
    const T* c_str() const { return mpBegin; }
    basic_string& sprintf(const T* pFormat, ...);   // 0x0041e050
};
typedef basic_string<wchar_t> wstring;

// SP vector: the allocator keeps a header word in front of each block.
template <class T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector()
    {
        if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};

template <unsigned int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
};
}

// ---- Resource manager --------------------------------------------------------------------
namespace Resource {
class IKeyFilter {
public:
    virtual ~IKeyFilter() {}
    virtual bool IsValid(const ResourceKey& name) = 0;
};

class StandardFileFilter : public IKeyFilter {
public:
    StandardFileFilter(uint32_t instance, uint32_t group, uint32_t type, uint32_t mask)
        : instanceID(instance), groupID(group), typeID(type), groupMask(mask) {}
    virtual ~StandardFileFilter() {}
    virtual bool IsValid(const ResourceKey& name);
    uint32_t instanceID;   // +0x04
    uint32_t groupID;      // +0x08
    uint32_t typeID;       // +0x0c
    uint32_t groupMask;    // +0x10
};

class Database {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual const wchar_t* GetLocation();               // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual bool DeleteRecord(const ResourceKey& name);  // +0x40
};

class IResourceManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual int GetRecordKeyList(eastl::sp_vector<ResourceKey>& dst, IKeyFilter* filter,
                                 eastl::sp_vector<Database*>* pDstDatabases);          // +0x38
    virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void FlushCache(void* pCache, IKeyFilter* pFilter);                        // +0x70
    virtual void v74(); virtual void v78(); virtual void v7c();
    virtual bool SetKeyName(const ResourceKey& key, const wchar_t* fileName);         // +0x80
};

IResourceManager* GetManager();   // 0x0067dcd0

// Points at DefaultCreateNameFromKey (0x008ddc80).
extern void (*CreateNameFromKey)(ResourceKey* key, eastl::wstring* dst, IResourceManager* pManager,
                                 Database* pDatabase, const wchar_t* name);   // [0x0154c468]
}

class cPropertyList;
bool GetFloatProperty(cPropertyList* pList, uint32_t propertyID, float& dst);   // 0x0040cf10

// ---- editor objects ----------------------------------------------------------------------
// Serialized model stream (0xac bytes).
class cEditorModelStream {
public:
    cEditorModelStream();   // 0x004b9c70
    virtual int AddRef();   // +0
    virtual int Release();  // +4
    uint32_t mData[(0xac - 4) / 4];
};

// EA DefaultRefCounted with an inline Release.
class DefaultRefCounted {
public:
    virtual ~DefaultRefCounted();
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        int n = mnRefCount - 1;
        mnRefCount = n;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return mnRefCount;
    }
    int mnRefCount;   // +0x08 of the model
};

class cISPEditorNameProvider {
public:
    virtual void SetName(const wchar_t* name);             // +0x0
    virtual const wchar_t* GetName();                      // +0x4
    virtual void SetDescription(const wchar_t* desc);      // +0x8
    virtual const wchar_t* GetDescription();               // +0xc
};

class cSPEditorModel : public cISPEditorNameProvider, public DefaultRefCounted {
public:
    cSPEditorModel();   // 0x004ab690 (0xe0 bytes)
    ResourceKey mKey;   // +0x0c
    uint32_t mData[(0xe0 - 0x18) / 4];
    void FUN_004ad330();                                                        // 0x004ad330
    bool LoadFromBinary(cEditorModelStream* pStream);                           // 0x004ae3b0
    bool SaveResource(cEditorModelStream* pStream);                             // 0x004af260
    bool FUN_004ae260(void* pModelWorld, int a, int b, bool c);                 // 0x004ae260
    void FUN_004ad6f0(eastl::sp_vector<uint32_t>& dst);                         // 0x004ad6f0
    void FUN_004ada40(eastl::sp_vector<uint32_t>& src);                         // 0x004ada40
    const wchar_t* GetFileName();                                               // 0x004ae000
};

class cSPEditorUI {
public:
    void UpdateUIBasedOnModelSaveability();           // 0x005dd7a0
    void ShowGeneralMessage(const wchar_t* message);  // 0x005dc460
};

struct cSkinMesh {
    uint32_t pad0[2];
    ResourceKey* mpBegin;   // +0x08
    ResourceKey* mpEnd;     // +0x0c
};
struct cSkinVertex { uint32_t mData[5]; };

class cSkinObject {
public:
    uint32_t pad0[0x34 / 4];
    cSkinMesh* mpMesh;           // +0x34
    uint32_t pad38[(0x7c - 0x38) / 4];
    cSkinVertex* mpVertsBegin;   // +0x7c
    cSkinVertex* mpVertsEnd;     // +0x80
    void BuildSkeleton();        // 0x004ca6e0
    void FUN_004cb340();         // 0x004cb340
    void FUN_004cb820();         // 0x004cb820
    __forceinline bool IsMeshValid() { return mpMesh && (mpMesh->mpEnd - mpMesh->mpBegin) == (mpVertsEnd - mpVertsBegin); }
};

struct cSkinUpdateFlags {
    bool mbA;
    bool mbB;
    cSkinUpdateFlags() : mbA(false), mbB(false) {}
};

class cSPEditorSkinManager {
public:
    cSkinObject* GetSkin(int index);                                  // 0x004c49e0
    bool IsSkinUpToDate();                                            // 0x004c4630
    void Update(int a, int b, cSkinUpdateFlags flags, int c);         // 0x004c38e0
    void ExportSkin(const wchar_t* pDir, const wchar_t* pName);       // 0x004c5980
};

class cEditorPainter {   // 0x88 bytes
public:
    cEditorPainter();                                                 // 0x004c2bc0
    virtual int AddRef();   // +0
    virtual int Release();  // +4
    void Shutdown();                                                  // 0x004c4eb0
    void Init(void* pEditor, cSPEditorModel* pModel, void* pModelWorld);   // 0x004c3070
    void SetRange(float a, float b);                                  // 0x004c5100
    void SetUpToDate(bool b);                                         // 0x004c4650
    uint32_t mData[(0x88 - 4) / 4];
};

class cSPEditorBlock {
public:
    virtual void v00();
    virtual int AddRef();    // +4
    virtual int Release();   // +8
    void FUN_0043a9a0(int a, int b);   // 0x0043a9a0
    uint32_t pad[(0xdc8 - 4) / 4];
    uint32_t mFlags;                   // +0xdc8
    bool IsLocked() const { return (mFlags >> 1) & 1; }
};

class cSPEditorHandle {
public:
    cSPEditorBlock* GetRigblock();     // 0x0047e6c0
};

namespace UI {
class BehaviorMessage {
public:
    BehaviorMessage() : mID(0) { _InterlockedExchange(&mnRefCount, 0); }
    virtual void v00();
    virtual int AddRef();    // +4
    virtual int Release();   // +8
    long mnRefCount;         // +0x04
    uint32_t pad08[10];
    uint32_t mID;            // +0x30
    uint32_t pad34;
};
}

class cEditorSavedMessage : public UI::BehaviorMessage {   // 0x40 bytes
public:
    cEditorSavedMessage() : m38(0) {}
    uint32_t m38;            // +0x38
    uint32_t pad3c;
};

void SetMessageString(UI::BehaviorMessage* pMsg, int index, const wchar_t* text);   // 0x0057cd40

class IMessageManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void PostMSG(uint32_t messageID, void* pMessage, void* pSource);   // +0x14
};

struct cEditorRequest {
    uint32_t mID;
    uint16_t mA;
    uint16_t mB;
};

class cEditorRequestHandler {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void Request(const ResourceKey& key, cEditorRequest* pRequest);   // +0x4c
};
cEditorRequestHandler* GetEditorRequestHandler();   // 0x00401010

namespace EA { namespace IO {
void SplitPath(const wchar_t* pPath, wchar_t* pDrive, wchar_t* pDirectory, wchar_t* pFileName,
               wchar_t* pExtension, int flags);   // 0x00930180
}}

namespace SP {
Resource::Database* GetSaveArea(uint32_t id);   // 0x006b1f90
bool IsSaveArea(Resource::Database* pDatabase);   // 0x006b1f60
IMessageManager* MessageServer();               // 0x0067dcc0
namespace EditorUtils {
void ExportToXMFAndBlocks(cSPEditorModel* pModel, cSkinObject* pSkin, const wchar_t* pDir);   // 0x004629e0
}
}
void FUN_004b7660(cSPEditorModel* pModel);                                       // 0x004b7660
void FUN_006ad030(const ResourceKey& key);                                       // 0x006ad030
void FUN_004647b0(cSPEditorModel* pModel, cSkinObject* pSkin, const wchar_t* pDir);   // 0x004647b0
void FUN_0046eae0(cSkinObject* pSkin, const wchar_t* pPath);                     // 0x0046eae0

extern const float kPainterRangeMin;   // 0x013ec478
extern const float kPainterRangeMax;   // 0x013f0318

namespace SP {

class cAppModeEditorBase {
public:
    uint32_t pad00[0x24 / 4];
    cPropertyList* mpConfigProperties;                       // +0x24
    uint32_t pad28[(0x48 - 0x28) / 4];
    eastl::bitset<128> mModelValidity;                       // +0x48
    eastl::bitset<128> mModelSaveValidity;                   // +0x58
    uint32_t pad68[(0x78 - 0x68) / 4];
    cSPEditorUI* mpUI;                                       // +0x78
    uint32_t pad7c[(0x88 - 0x7c) / 4];
    void* mpSaveModelWorld;                                  // +0x88
    uint32_t pad8c[(0x98 - 0x8c) / 4];
    cSPEditorModel* mpEditorSaveModel;                       // +0x98
    intrusive_ptr<cSPEditorModel> mpEditorModel;             // +0x9c
    uint32_t padA0[(0xd4 - 0xa0) / 4];
    intrusive_ptr<cSPEditorBlock> mpSelectedBlock;           // +0xd4
    uint32_t padD8[(0xe4 - 0xd8) / 4];
    cSPEditorHandle* mpRolloverHandle;                       // +0xe4
    bool mbE8;                                               // +0xe8
    bool mbTorsoInEffectsMask;                               // +0xe9
    uint16_t padEA;
    int mnEC;                                                // +0xec
    uint32_t padF0[(0x150 - 0xf0) / 4];
    cSPEditorSkinManager* mpSkinManager;                     // +0x150
    intrusive_ptr<cEditorPainter> mpPainter;                 // +0x154
    uint32_t pad158[(0x2ac - 0x158) / 4];
    uint32_t mSaveAreaID;                                    // +0x2ac
    uint32_t pad2b0[(0x2f0 - 0x2b0) / 4];
    bool mb2f0;
    bool mIsCreatureEditor;                                  // +0x2f1
    uint16_t pad2f2;
    uint32_t pad2f4[(0x31c - 0x2f4) / 4];
    int mEditorMode;                                         // +0x31c
    uint32_t pad320[(0x38c - 0x320) / 4];
    int mn38C;                                               // +0x38c
    uint32_t pad390[(0x4b0 - 0x390) / 4];
    bool mb4b0;
    bool mb4b1;
    bool mb4b2;                                              // +0x4b2
    bool mb4b3;                                              // +0x4b3
    bool mb4b4;                                              // +0x4b4

    eastl::bitset<128> BuildPartMask(cEditorModelStream* pStream, const wchar_t* pName, bool bSave);   // 0x0057ac00
    void RemoveTorsoFromEffectsMask();                                   // 0x005772b0
    void SetRolloverHandle(cSPEditorHandle* pHandle, bool b);            // 0x00573d70
    void FUN_00573c00(int a, int b);                                     // 0x00573c00

    __forceinline void RebuildSkin(cSkinObject* pSkin)
    {
        mpSkinManager->Update(0, 1, cSkinUpdateFlags(), 0);
        pSkin->BuildSkeleton();
        pSkin->FUN_004cb340();
        pSkin->FUN_004cb820();
    }
    __forceinline cSkinObject* GetSkin() { return mpSkinManager ? mpSkinManager->GetSkin(1) : 0; }

    void SaveModel(const ResourceKey& key, int saveMode);
};

// @ 0x0057f6c0  SP::cAppModeEditorBase::SaveModel
void cAppModeEditorBase::SaveModel(const ResourceKey& key, int saveMode)
{
    if (mpEditorModel) {
        mpEditorModel->FUN_004ad330();
        mpEditorModel = 0;
    }

    intrusive_ptr<cEditorModelStream> pStream = new ("Editor", 0, 0, 0, 0) cEditorModelStream();
    if (!mpEditorSaveModel->SaveResource(pStream))
        return;

    mb4b3 = false;
    mb4b4 = false;
    mb4b2 = true;
    mModelValidity = BuildPartMask(pStream, mpEditorSaveModel->GetName(), true);
    mpUI->UpdateUIBasedOnModelSaveability();
    mModelSaveValidity = BuildPartMask(pStream, mpEditorSaveModel->GetName(), false);

    mpEditorModel = new ("Editor", 0, 0, 0, 0) cSPEditorModel();
    mpEditorModel->LoadFromBinary(pStream);
    mpEditorModel->FUN_004ae260(mpSaveModelWorld, 0, 0, true);
    mpEditorModel->SetName(mpEditorSaveModel->GetName());
    mpEditorModel->SetDescription(mpEditorSaveModel->GetDescription());
    mpEditorModel->mKey = key;
    mpEditorSaveModel->mKey = key;

    eastl::sp_vector<uint32_t> blockData;
    mpEditorSaveModel->FUN_004ad6f0(blockData);
    mpEditorModel->FUN_004ada40(blockData);

    if (mIsCreatureEditor) {
        if (mpPainter) {
            mpPainter->Shutdown();
            mpPainter = 0;
        }
        mpPainter = new ("Editor", 0, 0, 0, 0) cEditorPainter();
        if (mpSkinManager) {
            bool bUpToDate = mpSkinManager->IsSkinUpToDate();
            mpPainter->Init(this, mpEditorModel, mpSaveModelWorld);
            float rangeMin = kPainterRangeMin;
            float rangeMax = kPainterRangeMax;
            GetFloatProperty(mpConfigProperties, 0x711306cd, rangeMin);
            GetFloatProperty(mpConfigProperties, 0x711306ce, rangeMax);
            mpPainter->SetRange(rangeMin, rangeMax);
            mpPainter->SetUpToDate(bUpToDate);
        }
    } else {
        FUN_004b7660(mpEditorModel);
    }

    const wchar_t* pName = mpEditorSaveModel->GetFileName();
    Resource::IResourceManager* pResourceManager = Resource::GetManager();
    Resource::Database* pSaveArea = SP::GetSaveArea(mSaveAreaID);
    const wchar_t* pDir = pSaveArea->GetLocation();

    if (saveMode == 0) {
        Resource::StandardFileFilter filter(key.instanceID, key.groupID, 0xffffffff, 0xdfff0000);
        pResourceManager->FlushCache(0, &filter);
        eastl::sp_vector<ResourceKey> keys;
        eastl::sp_vector<Resource::Database*> databases;
        pResourceManager->GetRecordKeyList(keys, &filter, &databases);
        int count = keys.size();
        for (int i = 0; i < count; ++i) {
            Resource::Database* pDatabase = databases[i];
            if (SP::IsSaveArea(pDatabase))
                pDatabase->DeleteRecord(keys[i]);
            FUN_006ad030(keys[i]);
        }
    }

    ResourceKey nameKey = key;
    const uint32_t groupID = key.groupID;
    eastl::wstring fileName;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.typeID = 0x1a99b06b;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.typeID = 0x0f43029a;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.typeID = 0x2f7d0004;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.typeID = 0x030bdee3;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.groupID = (groupID & 0xffffff01) | 1;
    nameKey.typeID = 0x2f7d0004;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.groupID = (groupID & 0xffffe5ff) | 0xe500;
    nameKey.typeID = 0x00b1b104;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());

    wchar_t name[256];
    switch (saveMode) {
    case 2:
        if (mpSkinManager && mpUI) {
            if (mEditorMode != 1) {
                mpUI->ShowGeneralMessage(L"You must switch to paint mode before exporting Z");
                break;
            }
            cSkinObject* pSkin = mpSkinManager->GetSkin(1);
            bool bMeshValid = pSkin->IsMeshValid();
            if (!mpSkinManager->IsSkinUpToDate() || !bMeshValid)
                RebuildSkin(pSkin);
            EA::IO::SplitPath(mpEditorModel->GetName(), 0, 0, name, 0, 4);
            {
                eastl::wstring path;
                path.sprintf(L"%ls/%ls.zpr", pDir, name);
                FUN_0046eae0(pSkin, path.c_str());
            }
        } else {
            cEditorRequestHandler* pHandler = GetEditorRequestHandler();
            if (!pHandler)
                break;
            cEditorRequest request;
            request.mB = 4;
            request.mA = 0x24;
            request.mID = 0x2ea8fb98;
            pHandler->Request(key, &request);
        }
        if (mpUI)
            mpUI->ShowGeneralMessage(L"Model exported");
        break;

    case 1: {
        EA::IO::SplitPath(mpEditorModel->GetFileName(), 0, 0, name, 0, 4);
        eastl::wstring path;
        path.sprintf(L"%ls/%ls.xsf", pDir, name);
        cSkinObject* pSkin = GetSkin();
        if (pSkin) {
            bool bMeshValid = pSkin->IsMeshValid();
            if (mpSkinManager->IsSkinUpToDate() && bMeshValid)
                mpSkinManager->ExportSkin(pDir, name);
            else
                RebuildSkin(pSkin);
            FUN_004647b0(mpEditorModel, GetSkin(), pDir);
            SP::EditorUtils::ExportToXMFAndBlocks(mpEditorModel, GetSkin(), pDir);
            if (mpUI) {
                eastl::wstring message;
                message.sprintf(L"Model saved to %ls", path);
                mpUI->ShowGeneralMessage(message.c_str());
            }
            cEditorSavedMessage* pMsg = new ("cAppModeEditorBase::Save", 0, 0, 0, 0) cEditorSavedMessage();
            if (pMsg)
                pMsg->AddRef();
            pMsg->mID = 0x5b053b5;
            SetMessageString(pMsg, 0, pDir);
            SetMessageString(pMsg, 1, name);
            SP::MessageServer()->PostMSG(pMsg->mID, pMsg, 0);
            pMsg->Release();
        } else {
            cEditorRequestHandler* pHandler = GetEditorRequestHandler();
            if (pHandler) {
                cEditorRequest request;
                request.mA = 0x28;
                request.mB = 4;
                request.mID = 0x2ea8fb98;
                pHandler->Request(key, &request);
            }
        }
        break;
    }

    case 0: {
        mnEC = 0;
        if (mbE8)
            mbE8 = false;
        if (mbTorsoInEffectsMask) {
            RemoveTorsoFromEffectsMask();
            mbTorsoInEffectsMask = false;
        }
        cSPEditorBlock* pBlock = mpSelectedBlock;
        if (pBlock) {
            if (!pBlock->IsLocked()) {
                if (mpRolloverHandle && mpRolloverHandle->GetRigblock() == pBlock)
                    SetRolloverHandle(0, true);
                mpSelectedBlock->FUN_0043a9a0(0, 1);
            }
            mpSelectedBlock = 0;
        }
        FUN_00573c00(0, -1);
        mn38C = 1;
        break;
    }
    }
}

}  // namespace SP
