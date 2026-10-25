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

// ---------------------------------------------------------------------------------------------
// Containers and IO types used by ScanFolder (0x005fc9f0) and ScanForImports (0x005fd0a0).
// ---------------------------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __cdecl tolower(int);

namespace eastl {
struct false_type {};
}

namespace EA {
namespace IO {
// FilePath (PDB: wchar_t mPath[520], size 0x410). The original reaches these helpers through
// renamed stubs, so they are called by address name.
struct FilePath {
  wchar_t mPath[520];                          // +0x000
  void FUN_0092fcc0();                         // 0x0092fcc0  constructor: mPath[0] = 0
  bool FUN_00930da0(const wchar_t* path);      // 0x00930da0  assign the directory component
  void FUN_00931100(const wchar_t* name, bool flag);  // 0x00931100  replace the name component
  wchar_t* FUN_00572590();                     // 0x00572590  UintArray::Self
};
}  // namespace IO
}  // namespace EA

namespace IN {

// eastl::basic_string<wchar_t> value as stored in a map/set node (0x10 bytes including the
// empty allocator's padding).
struct WText16 {
  wchar_t* mpBegin;                            // +0x00
  wchar_t* mpEnd;                              // +0x04
  wchar_t* mpCapacity;                         // +0x08
  uint32_t mAllocator;                         // +0x0c
  void FUN_00429760(size_t n);                 // 0x00429760  AllocateSelf
};

// pair<wstring, Key> and pair<Key, wstring>.
struct WKPair {
  WText16 first;
  Key second;
  WKPair() {}
  WKPair(const WText16& name, const Key& key) : first(name), second(key) {}
};
struct KWPair {
  Key first;
  WText16 second;
  KWPair() {}
  KWPair(const Key& key, const WText16& name) : first(key), second(name) {}
};
struct WKNode {
  WKPair mValue;                               // +0x00
  WKNode* mpNext;                              // +0x1c
};
struct KWNode {
  KWPair mValue;                               // +0x00
  KWNode* mpNext;                              // +0x1c
};

struct WKIter {
  WKNode* mpNode;                              // +0x00
  WKNode** mpBucket;                           // +0x04
};
struct WKInsert {
  WKIter first;
  bool second;
};
struct KWIter {
  KWNode* mpNode;
  KWNode** mpBucket;
};
struct KWInsert {
  KWIter first;
  bool second;
};

// hashtable<pair<wstring, Key>> : normalised path -> Key (mNameToKeyMap at +0x04).
struct MapWK {
  uint32_t mHash;                              // +0x00  empty hash object
  WKNode** mpBucketArray;                      // +0x04
  uint32_t mnBucketCount;                      // +0x08
  uint32_t mnElementCount;                     // +0x0c
  float mfMaxLoadFactor;                       // +0x10
  float mfGrowthFactor;                        // +0x14
  uint32_t mnNextResize;                       // +0x18
  uint32_t mAllocator;                         // +0x1c  empty allocator object
  WKIter find(const WText16& name);                                // 0x005f8fe0
  WKInsert DoInsertValue(const WKPair& value, eastl::true_type);   // 0x005f9470
};

// hashtable<pair<Key, wstring>> : Key -> normalised path (mKeyToNameMap at +0x24).
struct MapKW {
  uint32_t mHash;                              // +0x00
  KWNode** mpBucketArray;                      // +0x04
  uint32_t mnBucketCount;                      // +0x08
  uint32_t mnElementCount;                     // +0x0c
  float mfMaxLoadFactor;                       // +0x10
  float mfGrowthFactor;                        // +0x14
  uint32_t mnNextResize;                       // +0x18
  uint32_t mAllocator;                         // +0x1c
  KWInsert DoInsertValue(const KWPair& value, eastl::false_type);  // 0x005f95a0
};

// hashtable<wstring> : the scratch set of already imported names handed to ScanFolder.
struct SetWStr {
  struct Node {
    WText16 mKey;                              // +0x00
    Node* mpNext;                              // +0x10
  };
  struct Iter {
    Node* mpNode;
    Node** mpBucket;
  };
  struct Insert {
    Iter first;
    bool second;
  };

  uint32_t mHash;                              // +0x00
  Node** mpBucketArray;                        // +0x04
  uint32_t mnBucketCount;                      // +0x08
  uint32_t mnElementCount;                     // +0x0c
  float mfMaxLoadFactor;                       // +0x10
  float mfGrowthFactor;                        // +0x14
  uint32_t mnNextResize;                       // +0x18
  uint32_t mAllocator;                         // +0x1c

  SetWStr() {
    mHash = 0;
    mpBucketArray = (Node**)&eastl::gEmptyBucketArray;
    mnBucketCount = 1;
    mnElementCount = 0;
    mfMaxLoadFactor = 1.0f;
    mfGrowthFactor = 2.0f;
    mnNextResize = 0;
    mAllocator = 0;
  }
  Insert DoInsertValue(const WText16& value, eastl::true_type);    // 0x005f9100
};

struct StrTable : SetWStr {
  uint32_t erase(const WText16* key);                              // 0x005fa100
};
void FUN_005f9760(SetWStr::Node** buckets, uint32_t count);        // 0x005f9760

// EA::IO::DirectoryIterator::Entry (0x30 bytes) and the deque<Entry> DirectoryIterator::Read
// fills in (0x30 bytes, four entries per subarray).
struct DirEntry {
  uint32_t mType;                              // +0x00
  WText16 mName;                               // +0x04
  uint32_t mPad;                               // +0x14
  uint32_t mTimes[6];                          // +0x18
};
struct DirIter {
  DirEntry* mpCurrent;                         // +0x00
  DirEntry* mpBegin;                           // +0x04
  DirEntry* mpEnd;                             // +0x08
  DirEntry** mpCurrentArrayPtr;                // +0x0c
};
struct DirDeque {
  DirEntry** mpPtrArray;                       // +0x00
  uint32_t mnPtrArraySize;                     // +0x04
  DirIter mItBegin;                            // +0x08
  DirIter mItEnd;                              // +0x18
  void* mpAllocator;                           // +0x28
  uint32_t mnAllocatorFlags;                   // +0x2c
  DirDeque();
  void FUN_005f8840(size_t n);                 // 0x005f8840  DequeBase::DoInit
  void FUN_005f96c0();                         // 0x005f96c0  DequeBase destructor
};

void* FUN_00925cb0();                          // 0x00925cb0  GetDefaultAllocator
unsigned __stdcall FUN_0092ef40(const wchar_t* dir, DirDeque* list, const wchar_t* pattern,
                                unsigned char flags, uint32_t maxCount, int wantTimes); // 0x0092ef40

inline DirDeque::DirDeque()
    : mpPtrArray(0), mnPtrArraySize(0), mpAllocator(0), mnAllocatorFlags(0) {
  mItBegin.mpCurrent = 0;
  mItBegin.mpBegin = 0;
  mItBegin.mpEnd = 0;
  mItBegin.mpCurrentArrayPtr = 0;
  mItEnd.mpCurrent = 0;
  mItEnd.mpBegin = 0;
  mItEnd.mpEnd = 0;
  mItEnd.mpCurrentArrayPtr = 0;
  mpAllocator = FUN_00925cb0();
  FUN_005f8840(0);
}

// Allocate `len + 1` wchar_t and copy [src, src + len), NUL terminated (retail keeps the empty
// string in the shared eastl buffer).
static void TextAlloc(WText16* s, const wchar_t* src, uint32_t len) {
  s->mpBegin = 0;
  s->mpEnd = 0;
  s->mpCapacity = 0;
  s->mAllocator = 0;
  s->FUN_00429760((size_t)len + 1);
  memcpy(s->mpBegin, src, (size_t)len * 2);
  s->mpEnd = s->mpBegin + len;
  *s->mpEnd = 0;
}

static void TextFree(WText16* s) {
  if (s->mpCapacity - s->mpBegin > 1 && s->mpBegin) operator delete(s->mpBegin);
}

}  // namespace IN

void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0

struct cImportExportCtor : IHandlerBase8 {
  IN::MapWK mNameToKeyMap;                     // +0x04
  IN::MapKW mKeyToNameMap;                     // +0x24
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
  uint32_t count = 0;

  // Snapshot every name already present in the name -> key cache into a scratch set; ScanFolder
  // removes the entries it finds on disk again (leaving the names whose files have disappeared).
  IN::StrTable seen;
  for (uint32_t i = 0; i < mNameToKeyMap.mnBucketCount; ++i) {
    for (IN::WKNode* node = mNameToKeyMap.mpBucketArray[i]; node; node = node->mpNext)
      seen.DoInsertValue(node->mValue.first, eastl::true_type());
  }

  unsigned char found = (unsigned char)ScanFolder(&s104, &seen, &count);
  found |= (unsigned char)ScanFolder(&s114, &seen, &count);
  found |= (unsigned char)ScanFolder(&s124, &seen, &count);
  found |= (unsigned char)ScanFolder(&s134, &seen, &count);
  found |= (unsigned char)ScanFolder(&s144, &seen, &count);
  found |= (unsigned char)ScanFolder(&s154, &seen, &count);
  found |= (unsigned char)ScanFolder(&s164, &seen, &count);
  found |= (unsigned char)ScanFolder(&s174, &seen, &count);

  IN::FUN_005f9760(seen.mpBucketArray, seen.mnBucketCount);
  seen.mnElementCount = 0;
  if (seen.mnBucketCount > 1) operator delete(seen.mpBucketArray);
  return found;
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
bool cImportExportCtor::ScanFolder(const void* folderArg, void* tableArg, void* countArg)
{
  const eastl::string16* folder = (const eastl::string16*)folderArg;
  IN::StrTable* known = (IN::StrTable*)tableArg;
  uint32_t* count = (uint32_t*)countArg;
  unsigned char found = 0;

  IN::DirDeque entries;
  IN::FUN_0092ef40(folder->mpBegin, &entries, L"*.png", 2, 0x100000, 0);

  IN::DirEntry* cur = entries.mItBegin.mpCurrent;
  IN::DirEntry* subEnd = entries.mItBegin.mpEnd;
  IN::DirEntry** block = entries.mItBegin.mpCurrentArrayPtr;
  IN::DirEntry* end = entries.mItEnd.mpCurrent;

  while (cur != end) {
    EA::IO::FilePath path;
    path.FUN_0092fcc0();
    path.FUN_00930da0(folder->mpBegin);
    path.FUN_00931100(cur->mName.mpBegin, false);
    const wchar_t* full = path.FUN_00572590();

    // Lowercase the full path and use '/' separators for the cache key.
    uint32_t len = 0;
    while (full[len]) ++len;
    IN::WText16 norm;
    IN::TextAlloc(&norm, full, len);
    for (wchar_t* p = norm.mpBegin; p < norm.mpEnd; ++p) {
      uint32_t ch = (uint32_t)*p;
      if (ch < 0x100) *p = (wchar_t)tolower((int)(ch & 0xff));
    }
    for (uint32_t i = 0; i < len; ++i)
      if (norm.mpBegin[i] == L'\\') norm.mpBegin[i] = L'/';

    IN::WKIter it = mNameToKeyMap.find(norm);
    if (it.mpNode != mNameToKeyMap.mpBucketArray[mNameToKeyMap.mnBucketCount] || *count >= 500) {
      // Already imported (or the per-call cap is reached): drop the name from the scratch set.
      known->erase(&cur->mName);
    } else {
      Key key;
      key.instanceID = 0;
      key.typeID = 0;
      key.groupID = 0;
      bool imported = ImportNewAsset(full, &key);

      // A valid key is either the freshly generated one or a cache hit reported by CreateKey.
      if (imported || key.instanceID != 0xffffffffu || key.typeID != 0xffffffffu ||
          key.groupID != 0xffffffffu) {
        IN::WText16 nameCopy;
        IN::TextAlloc(&nameCopy, norm.mpBegin, len);
        IN::KWPair kp(key, nameCopy);
        mKeyToNameMap.DoInsertValue(kp, eastl::false_type());
        IN::TextFree(&nameCopy);
        ++*count;
        found = 1;
      }

      // Cache the attempt under the normalised path (failed imports keep the all-ones key).
      IN::WText16 nameCopy;
      IN::TextAlloc(&nameCopy, norm.mpBegin, len);
      IN::WKPair wp(nameCopy, key);
      mNameToKeyMap.DoInsertValue(wp, eastl::true_type());
      IN::TextFree(&nameCopy);
    }

    IN::TextFree(&norm);

    ++cur;
    if (cur == subEnd) {
      ++block;
      cur = *block;
      subEnd = cur + 4;
    }
  }

  entries.FUN_005f96c0();
  return found != 0;
}
