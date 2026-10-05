// Slice s005fa8d0 - SP::Thumbnail::cImportExport
// Flags: /O2 /MD /Gy /TP
#include "s005fa8d0.h"

namespace EA { namespace IO { namespace File {
bool Remove(const wchar_t* path);   // 0x00931fd0
} } }

// The hashtable members that live in this slice.  operator== / operator delete / assign
// are declared (not defined) on purpose: the original calls them out of line (masked reloc).
template class eastl::hashtable<eastl::NameKeyPair, eastl::string16, eastl::hash, eastl::equal_to>;
template class eastl::hashtable<eastl::KeyNamePair, Key, EA::ResourceMan::KeyHash, eastl::equal_to>;

// @ 0x005fa8d0
bool SP::Thumbnail::cImportExport::CreateExportThumb(void* pImage, const Key& key, void* pInfo)
{
  if (!pInfo) return false;
  // Reconstructed (behavioural) form; the exact inner sprite/file pipeline is not reproduced.
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
  eastl::KeyNameMap::iterator it = mKeyToNameMap.equal_range(key).first;
  if (it != mKeyToNameMap.end()) {
    eastl::string16 name = it.mpNode->mValue.second;
    EA::IO::File::Remove(name.c_str());
    mNameToKeyMap.erase(name);
    mKeyToNameMap.erase(it);
    Save();
  }
  return true;
}

// @ 0x005fafb0
bool SP::Thumbnail::cImportExport::ImportFromFolder(const Key& key, void* pArg)
{
  // Reconstructed (behavioural) form of the folder scanning loop.
  (void)key;
  (void)pArg;
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
