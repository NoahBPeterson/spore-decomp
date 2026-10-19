// Slice s005fa8d0 - SP::Thumbnail::cImportExport
// Flags: /O2 /MD /Gy /TP
#include "s005fa8d0.h"
#include <ctype.h>

namespace EA { namespace IO { namespace File {
bool Remove(const wchar_t* path);                          // 0x00931fd0
bool Move(const wchar_t* pFrom, const wchar_t* pTo, bool bOverwrite);   // 0x00931ff0
} } }

// External helpers the slice bodies dispatch to (relocations masked in the original image).
int  CompareI16(const wchar_t* a, const wchar_t* b, unsigned int n);   // 0x00572930
void FUN_005f8690(void* a, void* b);                                   // 0x005f8690
void FUN_0068e1a0(void* a, void* b);                                   // 0x0068e1a0
void* FUN_00414e10(void* a, void* b, void* c, int d);                  // 0x00414e10
// EA::ResourceMan manager + the opaque vtable dispatches the original performs.
void* ResMan_GetManager();                                             // EA::ResourceMan::GetManager()
bool  ResMan_LoadImage(void* pMgr, void* pData, void** ppRes, int a, int b);   // mgr vtbl +0x0c
void* ResMan_GetAsset(void* pRes, uint32_t nId);                       // pRes vtbl +0x0c
void  ResMan_Release(void* pRes);                                      // pRes vtbl +0x04
bool  WriteAssetDataToImage(void* pAsset, void* a, void* b);
bool  SaveDb_AddRecord(void* pDb, void* pFields, void** ppRec, int a, int b, int c, int d); // db vtbl +0x34
void* Record_GetStream(void* pRec, int a);                             // pRec vtbl +0x18
void  Record_Release(void* pRec);                                      // pRec vtbl +0x24
void  Record_ReleaseTop(void* pRec);                                   // pRec vtbl +0x08
// EA::IO::FileStream dispatches.
void  FileStream_Ctor(void* p, const wchar_t* pName);
void  FileStream_AddRef(void* p);
bool  FileStream_Open(void* p, int a, int b, int c, int d);
void  FileStream_Close(void* p);
void  FileStream_Dtor(void* p);

// The hashtable members that live in this slice.  operator== / operator delete / assign
// are declared (not defined) on purpose: the original calls them out of line (masked reloc).
template class eastl::hashtable<eastl::NameKeyPair, eastl::string16, eastl::hash, eastl::equal_to>;
template class eastl::hashtable<eastl::KeyNamePair, Key, EA::ResourceMan::KeyHash, eastl::equal_to>;

// @ 0x005fa8d0
// Retail ABI is five stack args (ret 0x14): (void* pResource, void* pImage, void* pSaveDb, int, int).
// The original walks an opaque sprite/texture/file pipeline; the body below reproduces the observed
// dispatch order (behavioural reconstruction; not byte-exact).
bool SP::Thumbnail::cImportExport::CreateExportThumb(void* pResource, void* pImage, void* pSaveDb,
                                                     int arg4, int arg5)
{
  (void)arg4;
  (void)arg5;
  if (!pImage) return false;

  const uint32_t nType = *(uint32_t*)pImage;
  const uint32_t nWidth = *(uint16_t*)((char*)pImage + 0xc);
  const uint32_t nHeight = *(uint16_t*)((char*)pImage + 0xe);
  const uint32_t nDepth = *(uint8_t*)((char*)pImage + 0x10);
  const bool bStandard = (nType == 0x15);

  void* pSprite = FUN_0068e8f0(nWidth, nHeight, nDepth);
  const int nBits = (int)(nWidth * nHeight * nDepth);
  if (!FillSpriteTexture(pSprite, (nBits + ((nBits >> 31) & 7)) >> 3)) return false;

  const uint32_t k0 = *(uint32_t*)((char*)pResource + 8);
  const uint32_t k1 = *(uint32_t*)((char*)pResource + 0xc);
  const uint32_t k2 = *(uint32_t*)((char*)pResource + 0x10);
  uint32_t* pKey = (uint32_t*)((char*)this + 0xf8);
  pKey[0] = k0;
  pKey[1] = k1;
  pKey[2] = k2;

  // Thumbnail image resource id is 0x30bdee3; the data blob is described by {k0,k1,k2,k0,k2}.
  uint32_t aFields[5];
  aFields[0] = 0x30bdee3;
  aFields[1] = k0;
  aFields[2] = k1;
  aFields[3] = k2;
  aFields[4] = k0;
  uint32_t aFields2[5] = {k0, k1, k2, k0, k2};

  void* pLoaded = 0;
  void* pMgr = ResMan_GetManager();
  if (!ResMan_LoadImage(pMgr, aFields, &pLoaded, 0, 0)) {
    if (pLoaded) ResMan_Release(pLoaded);
    return false;
  }
  void* pAsset = pLoaded ? ResMan_GetAsset(pLoaded, 0x30bdee3) : 0;
  if (pLoaded) pLoaded = 0;   // ownership transferred to the asset handle

  if (!WriteAssetDataToImage(pAsset, pSprite, pSaveDb)) {
    if (pLoaded) ResMan_Release(pLoaded);
    return false;
  }

  aFields2[0] = 0x2f7d0004;
  void* pRecord = 0;
  if (!SaveDb_AddRecord(pSaveDb, aFields2, &pRecord, 2, 6, 1, 0)) {
    if (pLoaded) ResMan_Release(pLoaded);
    return false;
  }
  if (pRecord) {
    void* pStream = Record_GetStream(pRecord, 0);
    FUN_0068e1a0(pStream, 0);
    Record_Release(pRecord);
  }

  // Build the on-disk name for the image and write the (empty) export stream header.
  wchar_t aNameBuf[0x30];
  void* pNameSrc = FUN_00414e10((void*)(uintptr_t)0, aNameBuf, 0, 0);
  if (FUN_005f97c0(pNameSrc, (void*)(uintptr_t)0, aNameBuf, 0, 0)) {
    char aStream[0x40];
    FileStream_Ctor(aStream, L"");
    FileStream_AddRef(aStream);
    if (FileStream_Open(aStream, 3, 2, 1, 0)) {
      FUN_0068e1a0(aStream, 0);
      FileStream_Close(aStream);

      // Sprite/texture qualification + map updates.
      uint32_t aSprite[8];
      uint32_t aSprite2[8];
      uint8_t aTmpA[12];
      uint8_t aTmpB[12];
      void* pInfo = FUN_005f9080(aSprite);
      FUN_005f8320(pInfo);
      FUN_005fa0a0(aSprite2, aSprite);
      QualifyNameWithGroup();
      QualifyNameWithGroup();
      void* pTex = FUN_005f90c0(aSprite, pSprite, (void*)(uintptr_t)k1, (void*)(uintptr_t)k2);
      FUN_005f8390(pTex);
      FUN_005fa0d0(aSprite2, aSprite);
      FUN_005f8d80();
      FUN_005f8d80();
      void* pEntryA = FUN_005f7940(aSprite2, aTmpA);
      FUN_005f8ed0(aTmpB, pEntryA);
      void* pEntryB = FUN_005f7940(aTmpA, aSprite2);
      FUN_005f8f00(aTmpB, pEntryB);
      Save();
      QualifyNameWithGroup();
      FileStream_Dtor(aStream);
      QualifyNameWithGroup();
      if (pRecord) Record_ReleaseTop(pRecord);
      if (pLoaded) ResMan_Release(pLoaded);
      return true;
    }
    FileStream_Dtor(aStream);
  }
  if (pRecord) Record_ReleaseTop(pRecord);
  if (pLoaded) ResMan_Release(pLoaded);
  return false;
}

// @ 0x005fae40
bool SP::Thumbnail::cImportExport::Shutdown()
{
  GetMessageServer()->vt2c(this, 0x24ce123, 0xffffd8f1);
  mNameToKeyMap.clear();
  mKeyToNameMap.clear();
  mGuidToKeyMap.clear();
  mKeyToGuidMap.clear();
  return true;
}

// @ 0x005faec0
bool SP::Thumbnail::cImportExport::RemoveExportThumb(const Key& key)
{
  eastl::pair<eastl::KeyNameMap::iterator, eastl::KeyNameMap::iterator> range;
  mKeyToNameMap.equal_range(&range, key);
  if (range.first != range.second) {
    eastl::string16 name = range.first.mpNode->mValue.second;
    EA::IO::File::Remove(name.c_str());
    mNameToKeyMap.erase(range.first.mpNode->mValue.second);
    mKeyToNameMap.erase(range.first);
    KeyGuidMap::iterator itGuid = mKeyToGuidMap.find(key);
    if (itGuid != mKeyToGuidMap.end()) {
      mGuidToKeyMap.erase(itGuid.mpNode->mValue.second);
      mKeyToGuidMap.erase(itGuid);
    }
    Save();
  }
  return true;
}

// @ 0x005fafb0
// Walks every stored name for `key`, rebuilds each name via FUN_005f97c0, normalises it
// (lower-case + '\\' -> '/'), and when it differs from the stored name and the rebuild
// succeeded, moves the file and re-keys both hash maps.  Last argument is the scan context.
bool SP::Thumbnail::cImportExport::ImportFromFolder(const Key& key, void* pArg)
{
  eastl::pair<eastl::KeyNameMap::iterator, eastl::KeyNameMap::iterator> range;
  mKeyToNameMap.equal_range(&range, key);

  bool bChanged = false;
  if (range.first != range.second) {
    for (eastl::KeyNameMap::iterator it = range.first; it != range.second; ++it) {
      eastl::string16& entryName = it.mpNode->mValue.second;

      eastl::string16 scanName;   // default-constructed empty string
      const bool bScan = FUN_005f97c0(*(void**)pArg, (void*)(uintptr_t)key.typeID, &scanName, 0,
                                      entryName.mpBegin);

      // Normalised copy of the rebuilt name.
      eastl::string16 lower(scanName);
      for (wchar_t* p = lower.mpBegin; p != lower.mpEnd; ++p)
        if ((uint32_t)*p < 0x100) *p = (wchar_t)tolower((int)((uint8_t)*p));
      for (wchar_t* p = lower.mpBegin; p != lower.mpEnd; ++p)
        if (*p == L'\\') *p = L'/';

      const int nScan = (int)(scanName.mpEnd - scanName.mpBegin);
      const int nEntry = (int)(entryName.mpEnd - entryName.mpBegin);
      const int nMin = (nScan < nEntry) ? nScan : nEntry;
      if ((CompareI16(scanName.mpBegin, entryName.mpBegin, (unsigned int)nMin) != 0 ||
           nScan != nEntry) &&
          bScan) {
        if (EA::IO::File::Move(entryName.mpBegin, scanName.mpBegin, true)) {
          mNameToKeyMap.erase(entryName);
          entryName = lower;

          eastl::string16 newNode(entryName);
          Key newKey = key;
          FUN_005f8690(&newNode, &newKey);

          uint8_t aRec[0x28];
          uint8_t aGuidKey[8];
          uint8_t aGuid[12];
          FUN_005f8320(aRec);
          FUN_005f9470(aGuid, aGuidKey, 0);
          bChanged = true;
        }
      }
    }
    if (bChanged) Save();
  }
  return false;
}

// @ 0x005fb350
cImportInfo& cImportInfo::operator=(const cImportInfo& o)
{
  mKey0 = o.mKey0;
  mKey4 = o.mKey4;
  mKey8 = o.mKey8;
  m10 = o.m10; m14 = o.m14; m18 = o.m18; m1c = o.m1c; m20 = o.m20; m24 = o.m24;
  mName = o.mName;
  m38 = o.m38; m3c = o.m3c;
  mDisplayName = o.mDisplayName;
  mDescription = o.mDescription;
  mPath = o.mPath;
  mIDs = o.mIDs;
  m84 = o.m84; m88 = o.m88; m8c = o.m8c;
  return *this;
}
