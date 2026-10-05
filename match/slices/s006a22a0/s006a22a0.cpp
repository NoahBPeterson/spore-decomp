// Slice s006a22a0: SP::cPropertyList / SP::cDirectPropertyList property accessors,
// map/vector helpers and the eastl::vector<pair<unsigned int,EA::Variant> >
// instantiations. /O2 /MD /Gy /EHsc /TP /GS-.
#include "s006a22a0.h"
#include <new>

extern EA::Variant g_sNullVariant;  // 0x016027d0
void* PropertyManager();            // 0x0067de30
void* Property_GetBool(void* prop);
void* Property_GetInt(void* prop);
void* Property_GetFloat(void* prop);
bool WriteVariant(EA::IO::IStream* stream, EA::Variant* value, int flags);

namespace EA {
namespace IO {
bool ReadInt32(IStream* stream, void* pData, unsigned int count, int flags);
}
}

// ---------------------------------------------------------------------------
// Small local helpers
// ---------------------------------------------------------------------------
static VariantPair* PairsAllocate(unsigned int n) {
  if (n == 0) return 0;
  return new ("App/cDirectPropertyList", 0, 0, 0, 0) VariantPair[n];
}
static void PairsDestroy(VariantPair* first, VariantPair* last) {
  for (; first != last; ++first) first->~VariantPair();
}
static void PairsCopy(VariantPair* dst, VariantPair* first, VariantPair* last) {
  for (; first != last; ++first, ++dst) *dst = *first;
}
static void PairsMoveBack(VariantPair* dstEnd, VariantPair* first, VariantPair* last) {
  for (; last != first;) *--dstEnd = *--last;
}

// ---------------------------------------------------------------------------
// SP::cPropertyList / cDirectPropertyList accessors
// ---------------------------------------------------------------------------
// @ 0x006A2470
bool SP::cPropertyList::HasProperty(unsigned int key) const {
  VariantPair* end = mPropertyMap.mpEnd;
  VariantPair* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, mPropertyMap.mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it != end) return true;
  if (mParent) return mParent->HasProperty(key);
  return false;
}

// @ 0x006A24D0
EA::Variant* SP::cPropertyList::GetPropertyValue(unsigned int key) const {
  VariantPair* end = mPropertyMap.mpEnd;
  VariantPair* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, mPropertyMap.mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it != end) return &it->second;
  if (mParent) return mParent->GetPropertyValue(key);
  return &g_sNullVariant;
}

// @ 0x006A2530
bool SP::cPropertyList::GetProperty(unsigned int key, EA::Variant** out) const {
  VariantPair* end = mPropertyMap.mpEnd;
  VariantPair* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, mPropertyMap.mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it != end) {
    *out = &it->second;
    return true;
  }
  if (mParent) return mParent->GetProperty(key, out);
  return false;
}

// @ 0x006A28C0
bool SP::cDirectPropertyList::GetProperty(unsigned int key, EA::Variant** out) const {
  if (key < mNumDirectProps) {
    *out = GetPropertyValue(key);
    return true;
  }
  return cPropertyList::GetProperty(key, out);
}

// @ 0x006A27D0
bool SP::cDirectPropertyList::HasProperty(unsigned int key) const {
  if (key < mNumDirectProps) return mDirectProps[key] != 0;
  return cPropertyList::HasProperty(key);
}

// @ 0x006A2800
EA::Variant* SP::cDirectPropertyList::GetPropertyValue(unsigned int key) const {
  if (key < mNumDirectProps) return (EA::Variant*)(mDirectProps + key);
  return cPropertyList::GetPropertyValue(key);
}

// @ 0x006A25A0
bool SP::cDirectPropertyList::GetDescription(unsigned int key) const {
  if (key < mNumDirectProps) return mDirectProps[key] != 0;
  VariantPair* end = mPropertyMap.mpEnd;
  VariantPair* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, mPropertyMap.mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it == end) return false;
  EA::Variant* v = &it->second;
  return v->mTypeId != 0;
}

// @ 0x006A2660
int SP::cDirectPropertyList::GetIntProperty(unsigned int index) const {
  if (index < mNumDirectProps) return mDirectProps[index];
  EA::Variant* v = GetPropertyValue(index);
  return v->mData[0];
}

// @ 0x006A2710
float SP::cDirectPropertyList::GetFloatProperty(unsigned int index) const {
  if (index < mNumDirectProps) return ((float*)mDirectProps)[index];
  EA::Variant* v = GetPropertyValue(index);
  return *(float*)&v->mData[0];
}

// ---------------------------------------------------------------------------
// Map helpers
// ---------------------------------------------------------------------------
VariantPair* SP::VariantMap::insert_pos(VariantPair* position, const VariantPair& value) {
  if (position == mpEnd && mpEnd != mpCapacity) {
    *mpEnd = value;
    mpEnd = mpEnd + 1;
    return position;
  }
  // full reallocation
  unsigned int n = (unsigned int)(position - mpBegin);
  unsigned int cur = (unsigned int)(mpEnd - mpBegin);
  unsigned int newCap = cur ? cur * 2 : 1;
  VariantPair* p = PairsAllocate(newCap);
  PairsCopy(p, mpBegin, position);
  p[n] = value;
  PairsCopy(p + n + 1, position, mpEnd);
  PairsDestroy(mpBegin, mpEnd);
  if (mpBegin) EA::Allocator::ZoneObject::operator delete(mpBegin);
  mpBegin = p;
  mpEnd = p + cur + 1;
  mpCapacity = p + newCap;
  return p + n;
}

// @ 0x006A2C50
VariantPair* SP::VariantMap::insert(VariantPair* out, const VariantPair& value) {
  VariantPair* end = mpEnd;
  VariantPair* it = eastl::lower_bound(mpBegin, end, &value.first, mCompare);
  if (it == end || value.first < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it != end) {
    out[0] = *it;
    ((unsigned char*)out)[4] = 0;
    return out;
  }
  *out = *insert_pos(it, value);
  ((unsigned char*)out)[4] = 1;
  return out;
}

// @ 0x006A2CB0
unsigned int SP::VariantMap::erase(const unsigned int& key) {
  VariantPair* end = mpEnd;
  VariantPair* it = eastl::lower_bound(mpBegin, end, &key, mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it == end) return 0;
  if (it + 1 < end) PairsCopy(it, it + 1, end);
  mpEnd = mpEnd - 1;
  mpEnd->~VariantPair();
  return 1;
}

// @ 0x006A2D30
VariantPair* SP::VariantMap::InsertOrGet(const unsigned int& key, const EA::Variant& value) {
  VariantPair* end = mpEnd;
  VariantPair* it = eastl::lower_bound(mpBegin, end, &key, mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it != end) return it;
  VariantPair v;
  v.first = key;
  v.second = value;
  return insert_pos(it, v);
}

// @ 0x006A2A80
void SP::cPropertyList::Clear() {
  PairsDestroy(mPropertyMap.mpBegin, mPropertyMap.mpEnd);
  mPropertyMap.mpEnd = mPropertyMap.mpBegin;
  mModificationCount++;
}

// @ 0x006A28F0
void SP::cPropertyList::ClearMapOnly() {
  PairsDestroy(mPropertyMap.mpBegin, mPropertyMap.mpEnd);
  mPropertyMap.mpEnd = mPropertyMap.mpBegin;
}

// @ 0x006A2A40
void SP::cPropertyList::Copy(cPropertyList* src) {
  if (this == src) return;
  mPropertyMap.mpBegin = src->mPropertyMap.mpBegin;
  mPropertyMap.mpEnd = src->mPropertyMap.mpEnd;
  mPropertyMap.mpCapacity = src->mPropertyMap.mpCapacity;
  mPropertyMap.mCompare = src->mPropertyMap.mCompare;
  SetParent(src->mParent);
}

// @ 0x006A2AD0
void SP::cDirectPropertyList::Copy(cPropertyList* src) {
  if (this == src) return;
  ClearMapOnly();
  VariantPair* it = src->mPropertyMap.mpBegin;
  VariantPair* end = src->mPropertyMap.mpEnd;
  for (; it != end; ++it) SetProperty(it->first, &it->second);
  SetParent(src->mParent);
}

// @ 0x006A2B20
void SP::cDirectPropertyList::Clear() {
  Memset32(mDirectProps, 0, mNumDirectProps);
  PairsDestroy(mPropertyMap.mpBegin, mPropertyMap.mpEnd);
  mPropertyMap.mpEnd = mPropertyMap.mpBegin;
}

// ---------------------------------------------------------------------------
// pvector (eastl::vector<pair<unsigned int,EA::Variant> >)
// ---------------------------------------------------------------------------
// @ 0x006A22A0
void eastl::pvector::DoInsertValue(VariantPair* position, const VariantPair& value) {
  if (mpEnd != mpCapacity) {
    PairsMoveBack(mpEnd + 1, position, mpEnd);
    *position = value;
    mpEnd = mpEnd + 1;
    return;
  }
  unsigned int n = (unsigned int)(position - mpBegin);
  unsigned int cur = (unsigned int)(mpEnd - mpBegin);
  unsigned int newCap = cur ? cur * 2 : 1;
  VariantPair* p = PairsAllocate(newCap);
  PairsCopy(p, mpBegin, position);
  p[n] = value;
  PairsCopy(p + n + 1, position, mpEnd);
  PairsDestroy(mpBegin, mpEnd);
  if (mpBegin) EA::Allocator::ZoneObject::operator delete(mpBegin);
  mpBegin = p;
  mpEnd = p + cur + 1;
  mpCapacity = p + newCap;
}

// @ 0x006A2940
VariantPair* eastl::pvector::insert(VariantPair* position, const VariantPair& value) {
  VariantPair* beg = mpBegin;
  DoInsertValue(position, value);
  return beg + (position - beg);
}

VariantPair* eastl::pvector::erase(VariantPair* first, VariantPair* last) {
  unsigned int n = (unsigned int)(last - first);
  PairsCopy(first, last, mpEnd);
  PairsDestroy(mpEnd - n, mpEnd);
  mpEnd = mpEnd - n;
  return first;
}

void eastl::pvector::DoInsertValues(VariantPair* position, unsigned int n,
                                    const VariantPair& value) {
  if (n == 0) return;
  unsigned int idx = (unsigned int)(position - mpBegin);
  unsigned int cur = size();
  VariantPair* p = PairsAllocate(cur + n);
  PairsCopy(p, mpBegin, position);
  for (unsigned int i = 0; i < n; ++i) p[idx + i] = value;
  PairsCopy(p + idx + n, position, mpEnd);
  PairsDestroy(mpBegin, mpEnd);
  if (mpBegin) EA::Allocator::ZoneObject::operator delete(mpBegin);
  mpBegin = p;
  mpEnd = p + cur + n;
  mpCapacity = p + cur + n;
}

// @ 0x006A2B80
void eastl::pvector::resize(unsigned int n) {
  if (size() < n) {
    VariantPair v;
    DoInsertValues(mpEnd, n - size(), v);
  } else {
    erase(mpBegin + n, mpEnd);
  }
}

// ---------------------------------------------------------------------------
// Property list mutators
// ---------------------------------------------------------------------------
// @ 0x006A2E20
void SP::cPropertyList::SetProperty(unsigned int key, EA::Variant* value) {
  VariantPair* end = mPropertyMap.mpEnd;
  VariantPair* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, mPropertyMap.mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it == mPropertyMap.mpEnd) {
    VariantPair v;
    v.first = key;
    v.second = *value;
    mPropertyMap.insert_pos(it, v);
  } else {
    it->second = *value;
  }
  mModificationCount++;
}

// @ 0x006A2EF0
void SP::cPropertyList::RemoveProperty(unsigned int key) {
  mPropertyMap.erase(key);
  mModificationCount++;
}

// @ 0x006A2F10
void SP::cPropertyList::v12(cPropertyList* src) {
  if (this == src) return;
  VariantPair* it = src->mPropertyMap.mpBegin;
  VariantPair* end = src->mPropertyMap.mpEnd;
  for (; it != end; ++it) {
    VariantPair* d = mPropertyMap.InsertOrGet(it->first, it->second);
    d->second = it->second;
  }
  mModificationCount++;
}

// @ 0x006A3070
unsigned int SP::cPropertyList::GetPropertyIDs(unsigned int* ids) {
  unsigned int n = (unsigned int)(mPropertyMap.mpEnd - mPropertyMap.mpBegin);
  unsigned int i = 0;
  for (VariantPair* it = mPropertyMap.mpBegin; it != mPropertyMap.mpEnd; ++it)
    ids[i++] = it->first;
  return n;
}

// @ 0x006A30C0
void SP::cDirectPropertyList::SetProperty(unsigned int index, EA::Variant* value) {
  if (index < mNumDirectProps) {
    void* mgr = PropertyManager();
    void* entry = (*(void*(**)(void*, unsigned int))(*(int*)mgr + 0x50))(mgr, index);
    short type = *(short*)((char*)entry + 0x12);
    if (type == 1) {
      SetBoolProperty(index, *(bool*)Property_GetBool(value));
      return;
    }
    if (type == 9) {
      SetIntProperty(index, *(int*)Property_GetInt(value));
      return;
    }
    if (type == 0xd) {
      SetFloatProperty(index, *(float*)Property_GetFloat(value));
      return;
    }
  }
  cPropertyList::SetProperty(index, value);
}

// @ 0x006A3180
unsigned int SP::cDirectPropertyList::GetPropertyIDs(unsigned int* ids) {
  unsigned int out = 0;
  unsigned int i = 1;
  while (i < mNumDirectProps) {
    void* mgr = PropertyManager();
    void* entry = (*(void*(**)(void*, unsigned int))(*(int*)mgr + 0x50))(mgr, i);
    if (*(short*)((char*)entry + 0x12) != 0) ids[out++] = i;
    i++;
  }
  for (VariantPair* it = mPropertyMap.mpBegin; it != mPropertyMap.mpEnd; ++it)
    ids[out++] = it->first;
  return out;
}

// ---------------------------------------------------------------------------
// Read
// ---------------------------------------------------------------------------
// @ 0x006A2F60
bool SP::cPropertyList::Read(EA::IO::IStream* stream) {
  int nCount = 0;
  bool bResult = EA::IO::ReadInt32(stream, &nCount, 1, 0);
  if (bResult && nCount < 0) {
    int key[3] = {0, 0, 0};
    bResult = EA::IO::ReadInt32(stream, key, 3, 0);
    void* mgr = PropertyManager();
    if (mParent) {
      cPropertyList* old = mParent;
      mParent = 0;
      old->Release();
    }
    (*(void(**)(void*, int, int, void**))(*(int*)mgr + 0x2c))(mgr, key[0], key[2],
                                                             (void**)&mParent);
  }
  unsigned int want = (unsigned int)nCount & 0x7fffffff;
  while ((unsigned int)(mPropertyMap.mpEnd - mPropertyMap.mpBegin) < want) {
    VariantPair v;
    mPropertyMap.insert_pos(mPropertyMap.mpEnd, v);
  }
  for (VariantPair* it = mPropertyMap.mpBegin; it != mPropertyMap.mpEnd; ++it) {
    if (!bResult) break;
    bResult = EA::IO::ReadInt32(stream, &it->first, 1, 0);
    if (bResult) bResult = WriteVariant(stream, &it->second, 0) != 0;
  }
  return bResult;
}
