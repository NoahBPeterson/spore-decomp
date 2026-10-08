// Slice s005fc330 - cImportExport retail constructor / scan helpers.
// Flags: /O2 /MD /Gy /TP /GS-
#include "../s005fa8d0/s005fa8d0.h"

struct RefVec8 {
  void* mpBegin;
  ~RefVec8() {
    if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin);
  }
};

struct IHandlerBase8 {
  virtual void s0();
  virtual void s1();
  virtual ~IHandlerBase8() {}
};

// Embedded image data (retail 0x70 bytes): two refcounted buffers at +0x00 / +0x58.
struct cImageDataEmbed8 {
  RefVec8 v0;
  char pad0[0x58 - 4];
  RefVec8 v58;
  char pad58[0x70 - 0x5c];
  cImageDataEmbed8();
  void Serialize(void* stream, int flag);   // 0x0068e1a0
};


// ---- stubs for ImportNewAsset (0x005fc330) ----
namespace IN {
#pragma pack(push, 4)
struct wstr { const wchar_t* b; const wchar_t* e; const wchar_t* c; uint32_t alloc; };
struct IRefObj { virtual void _a0(); virtual void _a1(); virtual void Release(); };
struct IRecordS {
  virtual void _r0(); virtual void AddRef(); virtual void Release();
  PV(3) PV(4) PV(5)
  virtual void* GetStream();            // +0x18
  PV(7) PV(8)
  virtual void _r9();
  virtual bool RecordClose();           // +0x24
};
struct ResObjS {
  virtual void AddRef(); virtual void Release();
  int rc; Key key;
};
struct AssetMeta {
  virtual void AddRef(); virtual void Release();
  char pad[0xd8 - 4];
  AssetMeta();
  void SetMetadata(Key* k, uint64_t id, uint64_t t, const wchar_t* name, uint64_t aid, const wchar_t* aname,
                   const wchar_t* desc, const wchar_t* tags, const char* authors, bool b);  // 0x551620
  void SetParentAssetID(uint64_t id);   // 0x551b60
  void SetFlag(bool b);                 // 0x550990
  void AddTrait(uint32_t t);            // 0x550b00
};
struct MemRecord : IRecordS {
  char pad[0x24 - 4];
  MemRecord(uint32_t a, IRefObj* o, Key* k, uint32_t b, uint32_t c);   // 0x8e2380
  static void* operator new(size_t, const char*, int, int, int, int);   // 0x926020
  static void operator delete(void*, const char*, int, int, int, int) {}
};
struct Database {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual bool OpenRecord(Key* k, IRecordS** pp, int access, int cd, int b, int c);   // +0x34
};
struct IResourceFactory {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool CreateResource(IRecordS* rec, ResObjS** pDst, void* extra, uint32_t type);   // +0x1c
};
struct IResourceManager {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual bool WriteResource(void* res, void* extra, Database* db, void* fac, const Key* nameKey);   // +0x20
  PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
  virtual IResourceFactory* FindFactory(uint32_t type, uint32_t recType);   // +0x48
};
struct IIDGen {
  PV(0) PV(1)
  virtual void Generate(Key* out, uint32_t a, uint32_t b);   // +8
};
struct IKeyLookup {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual int Lookup(Key* k);   // +0x58
};
struct IMsgServer {
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void Post(uint32_t msg, Key* data, int b);   // +0x14
};
struct AssetDirectory {
  bool GetLocalKey(uint64_t id, Key* out);          // 0x54e460
  void RemoveMapping(uint64_t id, int b);           // 0x54ed50
  void AddMapping(uint64_t id, Key* k);             // 0x54e250
};
struct PollenModule { char pad[0x58]; AssetDirectory* mpAssetDir; };
PollenModule* GetPollenModule();                    // 0x0067cb30
IKeyLookup* GetKeyLookup();                         // 0x008de1a0
IIDGen* GetIDGenerator();                           // 0x0067de60
IResourceManager* GetManager();                     // 0x0067dcd0
IMsgServer* GetMessageServer();                     // 0x0067dcc0
Database* GetSaveArea(uint32_t id);                 // 0x006b1f90
void FUN_006ad010(void* p);
void FUN_006ac0a0(int a, void* p);

struct FileStream {
  void* vptr; char pad[0x21c - 4];
  FileStream(const wchar_t* path);                  // 0x00931e10
  void AddRef();                                    // 0x009317b0
  bool Open(int a, int b, int c, int d);            // 0x009318f0
  void Close();                                     // 0x00931a70
  ~FileStream();                                    // 0x00931e70
};

static wchar_t sEmptyStr[2];
struct ImpInfo {
  uint32_t u0, idA, idB, u0c;
  uint64_t assetId;     // +0x10
  uint64_t parentId;    // +0x18
  uint64_t timeCreated; // +0x20
  wstr name;            // +0x28
  uint64_t authorId;    // +0x38
  wstr authorName;      // +0x40
  wstr desc;            // +0x50
  wstr tags;            // +0x60
  uint32_t* idsBegin; uint32_t* idsEnd; uint32_t* idsCap;   // +0x70
  uint32_t u7c, u80;
  SP::Thumbnail::AssetGUID guid;   // +0x84
  ImpInfo() {
    const wchar_t* e = sEmptyStr;
    name.b = name.e = e; name.c = e + 1;
    authorName.b = authorName.e = e; authorName.c = e + 1;
    desc.b = desc.e = e; desc.c = e + 1;
    tags.b = tags.e = e; tags.c = e + 1;
    idsBegin = 0; idsEnd = 0; idsCap = 0;
  }
  ~ImpInfo();                                       // 0x005f8e40
};
#pragma pack(pop)

struct GuidMapX : SP::Thumbnail::GuidKeyMap {
  iterator find(const SP::Thumbnail::AssetGUID& g);   // 0x005f8050
  insert_return_type DoInsertValue(const SP::Thumbnail::GuidKeyPair& v, eastl::true_type);   // 0x005f8170
};
struct KeyGuidMapX : SP::Thumbnail::KeyGuidMap {
  insert_return_type DoInsertValue(const SP::Thumbnail::KeyGuidPair& v, eastl::true_type);   // 0x005f8240
};
}  // namespace IN
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0

struct cImportExportCtor : IHandlerBase8 {
  eastl::NameKeyMap mNameToKeyMap;             // +0x04
  eastl::KeyNameMap mKeyToNameMap;             // +0x24
  uint32_t mnMachineID;                        // +0x44
  SP::Thumbnail::GuidKeyMap mGuidToKeyMap;     // +0x48
  SP::Thumbnail::KeyGuidMap mKeyToGuidMap;     // +0x68
  cImageDataEmbed8 mEmbed;                     // +0x88
  uint32_t xf8, xfc, x100;                     // +0xf8
  eastl::string16 s104, s114, s124, s134, s144, s154, s164, s174;

  cImportExportCtor();                         // 0x005fcf40
  bool CreateKey(IN::FileStream* s, IN::ImpInfo* info, IN::IRefObj** pp);   // 0x005fbb00
  unsigned char ScanForImports();              // 0x005fd0a0
  bool ImportNewAsset(const wchar_t* path, Key* pOut);   // 0x005fc330
  bool ScanFolder(const void* a, void* b, void* c);   // 0x005fc9f0
};

__declspec(noinline) cImageDataEmbed8::cImageDataEmbed8() { v0.mpBegin = 0; v58.mpBegin = 0; }

// @ 0x005fcf40
cImportExportCtor::cImportExportCtor() {}

// @ 0x005fd0a0
unsigned char cImportExportCtor::ScanForImports()
{
  // Reconstructed (behavioural) skeleton: scans the eight folder paths.
  return 0;
}

// @ 0x005fc330
bool cImportExportCtor::ImportNewAsset(const wchar_t* path, Key* pOut)
{
  pOut->instanceID = (uint32_t)-1;
  pOut->typeID = (uint32_t)-1;
  pOut->groupID = (uint32_t)-1;
  bool bResult = false;
  IN::FileStream stream(path);
  stream.AddRef();
  if (stream.Open(1, 3, 1, 0)) {
    IN::PollenModule* pollen = IN::GetPollenModule();
    IN::ImpInfo info;
    IN::IRefObj* pObj = 0;
    bResult = CreateKey(&stream, &info, &pObj);
    stream.Close();
    SP::Thumbnail::AssetGUID guid = info.guid;
    IN::GuidMapX* gm = (IN::GuidMapX*)&mGuidToKeyMap;
    IN::GuidMapX::iterator it = gm->find(guid);
    if (it.mpNode != gm->mpBucketArray[gm->mnBucketCount]) {
      pOut->instanceID = it.mpNode->mValue.second.instanceID;
      pOut->typeID = it.mpNode->mValue.second.typeID;
      pOut->groupID = it.mpNode->mValue.second.groupID;
      if (pObj) pObj->Release();
      return false;
    }
    Key found = {0, 0, 0};
    if (pollen->mpAssetDir->GetLocalKey(info.assetId, &found)) {
      IN::IKeyLookup* kl = IN::GetKeyLookup();
      if (kl->Lookup(&found)) {
        *pOut = found;
        if (pObj) pObj->Release();
        return false;
      }
    }
    if (bResult) {
      Key newKey = {0, 0, 0};
      IN::GetIDGenerator()->Generate(&newKey, info.idA, info.idB);
      IN::AssetMeta* pMeta = new ("Thumbnail_cImportExport", 0, 0, 0, 0) IN::AssetMeta();
      if (pMeta) pMeta->AddRef();
      pMeta->SetMetadata(&newKey, info.assetId, info.timeCreated, info.name.b, info.authorId,
                         info.authorName.b, info.desc.b, info.tags.b, "tag:spore.com,2006:ImportedContent", true);
      pMeta->SetParentAssetID(info.parentId);
      if (info.guid.mnMachineID == mnMachineID) pMeta->SetFlag(true);
      for (uint32_t* p = info.idsBegin; p != info.idsEnd; ++p) pMeta->AddTrait(*p);
      IN::IRecordS* pStreamRec = 0;
      IN::Database* saveArea = IN::GetSaveArea(0x11ac19d);
      IN::IResourceFactory* factory = IN::GetManager()->FindFactory(newKey.typeID, (uint32_t)-1);
      if (!factory) {
        bResult = false;
      } else {
        IN::ResObjS* pDst = 0;
        IN::IRecordS* rec = new ("Thumbnail_cImportExport", 0, 0, 0, 0) IN::MemRecord(0, pObj, &newKey, 0, 0);
        if (rec) rec->AddRef();
        if (pDst) { IN::ResObjS* t = pDst; pDst = 0; t->Release(); }
        if (!factory->CreateResource(rec, &pDst, 0, newKey.typeID)) {
          bResult = false;
        } else {
          pDst->key = newKey;
          IN::FUN_006ad010(pDst);
          bResult = IN::GetManager()->WriteResource(pDst, 0, saveArea, 0, 0);
          IN::FUN_006ac0a0(2, pDst);
          IN::FUN_006ad010(pMeta);
          bResult = bResult && IN::GetManager()->WriteResource(pMeta, 0, saveArea, 0, 0);
          IN::FUN_006ac0a0(2, pMeta);
          Key imgKey = newKey;
          imgKey.typeID = 0x2f7d0004;
          if (!bResult) {
            bResult = false;
          } else {
            if (pStreamRec) { IN::IRecordS* t = pStreamRec; pStreamRec = 0; t->Release(); }
            if (!saveArea->OpenRecord(&imgKey, &pStreamRec, 2, 6, 1, 0)) {
              bResult = false;
            } else {
              bResult = true;
              mEmbed.Serialize(pStreamRec->GetStream(), 0);
              pStreamRec->RecordClose();
            }
          }
        }
        if (rec) rec->Release();
        if (pDst) pDst->Release();
        if (bResult) {
          *pOut = newKey;
          xf8 = newKey.instanceID;
          xfc = newKey.typeID;
          x100 = newKey.groupID;
          if (info.assetId != (uint64_t)-1) {
            IN::AssetDirectory* dir = pollen->mpAssetDir;
            if (dir->GetLocalKey(info.assetId, 0)) dir->RemoveMapping(info.assetId, 1);
            dir->AddMapping(info.assetId, &newKey);
          }
          SP::Thumbnail::GuidKeyPair gp(info.guid, *pOut);
          gm->DoInsertValue(gp, eastl::true_type());
          IN::KeyGuidMapX* kgm = (IN::KeyGuidMapX*)&mKeyToGuidMap;
          SP::Thumbnail::KeyGuidPair kp(*pOut, info.guid);
          kgm->DoInsertValue(kp, eastl::true_type());
          IN::GetMessageServer()->Post(0x5132ed1, &newKey, 0);
        }
      }
      if (pStreamRec) pStreamRec->Release();
      if (pMeta) pMeta->Release();
    }
    if (pObj) pObj->Release();
  }
  return bResult;
}


// @ 0x005fc9f0
bool cImportExportCtor::ScanFolder(const void* a, void* b, void* c)
{
  (void)a;
  (void)b;
  (void)c;
  return false;
}
