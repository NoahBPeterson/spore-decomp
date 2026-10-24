// Slice s006a22a0: SP::cPropertyList / SP::cDirectPropertyList property accessors,
// map/vector helpers and the eastl::vector<pair<unsigned int,EA::Variant> >
// instantiations. /O2 /MD /Gy /EHsc /TP /GS-.
#include "s006a22a0.h"
#include <new>

extern EA::Variant g_sNullVariant;  // 0x016027d0
void* PropertyManager();            // 0x0067de30
// PropertyManager vtable slot +0x50 (PropertyManager::GetPropertyByID): `this` in ecx, the
// key on the stack, one stack dword -- a thiscall member, declared as a __fastcall shim.
typedef void* (__fastcall* PropertyLookup)(void* mgr, int unused, unsigned int key);
void* Property_GetBool(void* prop); // 0x0041e920
void* Property_GetInt(void* prop);
void* Property_GetFloat(void* prop);
bool WriteVariant(EA::IO::IStream* stream, EA::Variant* value, int flags);  // 0x00694440

namespace EA {
namespace IO {
bool ReadInt32(IStream* stream, void* pData, unsigned int count, int flags);  // 0x0093a780
}
}

// Variant-shaped scratch used by the inlined property getters.
struct VariantBytes {
  unsigned int mData[4];   // +0x00
  unsigned short mFlags;   // +0x10
  unsigned short mTypeId;  // +0x12
};
struct VariantOps {
  void* ToStr(const void* src);    // 0x006a19b0
  void* ToInt(const void* src);    // 0x0060d990
  void* ToFloat(const void* src);  // 0x006a1a10
};

static const void* VariantData(const VariantBytes* v, unsigned short tA,
                               unsigned short tB, unsigned int emptyAddr) {
  unsigned short t = v->mTypeId;
  if (t == tA || t == tB) {
    if ((v->mFlags & 0x30) == 0)
      return (const void*)(-(unsigned)(t != 0) & (unsigned)(size_t)v);
    return *(const void**)(const void*)v;
  }
  return (const void*)(size_t)emptyAddr;
}

// ---------------------------------------------------------------------------
// Small local helpers
// ---------------------------------------------------------------------------
static VariantPair* PairsAllocate(unsigned int n) {
  if (n == 0) return 0;
  return new ("App/cDirectPropertyList", 0, 0, 0, 0) VariantPair[n];
}
void PairsCopyRange(VariantPair* first, VariantPair* last, VariantPair* dst);  // 0x00612b20
void __stdcall PairsDestroyRange(VariantPair* first, VariantPair* last);      // 0x00685a30
void PairsCopyBytes(void* dst, const void* src, unsigned int size);           // 0x011e0744
static void PairsDestroy(VariantPair* first, VariantPair* last) {
  PairsDestroyRange(first, last);
}
static void PairsCopy(VariantPair* dst, VariantPair* first, VariantPair* last) {
  PairsCopyRange(first, last, dst);
}
static void PairsMoveBack(VariantPair* dstEnd, VariantPair* first, VariantPair* last) {
  for (; last != first;) *--dstEnd = *--last;
}

// eastl::vector<unsigned int> stub used by GetPropertyIDs (the retail argument is a vector).
struct UIntVector {
  unsigned int* mpBegin;     // +0x00
  unsigned int* mpEnd;       // +0x04
  unsigned int* mpCapacity;  // +0x08
  void resize(unsigned int n);                                            // 0x004cd3c0
  void DoInsertValue(unsigned int* position, const unsigned int& value);  // 0x004558a0
  void DoInsertValues(unsigned int* position, unsigned int n, const unsigned int& value);  // 0x004cea40
};

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
  if (key != 0 && key < mNumDirectProps) return true;
  // The original keeps the inherited lookup as a real call (never a tail call) and returns a
  // full-width 0/1 (`mov eax,1` / `xor eax,eax`), not just a normalized `al`; widening the
  // callee's bool through a volatile int reproduces that.
  volatile int bInherited = cPropertyList::HasProperty(key);
  return bInherited != 0;
}

// @ 0x006A2800
EA::Variant const& SP::cDirectPropertyList::GetProperty(unsigned int key) const {
  if (key < mNumDirectProps) {
    EA::Variant* out = const_cast<EA::Variant*>(&mTempDirectVariant);
    void* mgr = PropertyManager();
    void* entry = (*(PropertyLookup*)(*(int*)mgr + 0x50))(mgr, 0, key);
    VariantCopyAssign(out, 0, (EA::Variant*)entry);
    if (!(out->mFlags & 0x10)) {
      if (out->mTypeId == 1)
        *out = (bool)(mDirectProps[key] != 0);
      else if (out->mTypeId == 9)
        *out = mDirectProps[key];
      else if (out->mTypeId == 0xd)
        *out = ((float*)mDirectProps)[key];
    }
    return mTempDirectVariant;
  }
  return *cPropertyList::GetPropertyValue(key);
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
  VariantBytes v;
  const VariantBytes* rv = (const VariantBytes*)((VariantOps*)&v)->ToStr(&it->second);
  const void* p = VariantData(rv, 1, 0x10, 0x15d115d);
  bool res = *(const bool*)p;
  if (v.mFlags & 4) ((EA::Variant*)&v)->Destruct(0);
  return res;
}

// @ 0x006A2660
int SP::cDirectPropertyList::GetIntProperty(unsigned int index) const {
  if (index < mNumDirectProps) return mDirectProps[index];
  VariantPair* end = mPropertyMap.mpEnd;
  VariantPair* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &index, mPropertyMap.mCompare);
  if (it == end || index < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it == end) return 0;
  VariantBytes v;
  const VariantBytes* rv = (const VariantBytes*)((VariantOps*)&v)->ToInt(&it->second);
  const void* p = VariantData(rv, 9, 0x10, 0x15d1160);
  int r = *(const int*)p;
  if (v.mFlags & 4) ((EA::Variant*)&v)->Destruct(0);
  return r;
}

// @ 0x006A2710
float SP::cDirectPropertyList::GetFloatProperty(unsigned int index) const {
  if (index < mNumDirectProps) return ((float*)mDirectProps)[index];
  VariantPair* end = mPropertyMap.mpEnd;
  VariantPair* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &index, mPropertyMap.mCompare);
  if (it == end || index < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it == end) return 0.0f;
  VariantBytes v;
  const VariantBytes* rv = (const VariantBytes*)((VariantOps*)&v)->ToFloat(&it->second);
  const void* p = VariantData(rv, 0xd, 0x10, 0x15d1168);
  float r = *(const float*)p;
  if (v.mFlags & 4) ((EA::Variant*)&v)->Destruct(0);
  return r;
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

// The original shrinks by the signed byte distance rounded to whole 0x18 elements
// (truncating division), which only equals `mpEnd = mpBegin` for a consistent range.
static VariantPair* ShrinkEnd(VariantPair* begin, VariantPair* end) {
  int diff = (int)((char*)end - (char*)begin);
  return (VariantPair*)((char*)end - diff / 0x18 * 0x18);
}

// @ 0x006A2A80
void SP::cPropertyList::Clear() {
  VariantMap* map = &mPropertyMap;
  PairsCopy(map->mpBegin, map->mpEnd, map->mpEnd);
  PairsDestroy(map->mpBegin, map->mpEnd);
  map->mpEnd = ShrinkEnd(map->mpBegin, map->mpEnd);
  mModificationCount++;
}

// @ 0x006A28F0
void SP::VariantMap::ClearMapOnly() {
  PairsCopy(mpBegin, mpEnd, mpEnd);
  PairsDestroy(mpBegin, mpEnd);
  mpEnd = ShrinkEnd(mpBegin, mpEnd);
}

// @ 0x006A2A40
void SP::cPropertyList::Copy(cPropertyList* src) {
  if (this == src) return;
  VariantMap* s = &src->mPropertyMap;
  VariantMap* d = &mPropertyMap;
  cPropertyList* me = this;
  *(eastl::pvector*)d = *(const eastl::pvector*)s;
  d->mCompare = s->mCompare;
  me->SetParent(me->mParent);
}

// @ 0x006A2AD0
void SP::cDirectPropertyList::Copy(cPropertyList* src) {
  if (this == src) return;
  mPropertyMap.ClearMapOnly();
  VariantPair* it = src->mPropertyMap.mpBegin;
  VariantPair* end = src->mPropertyMap.mpEnd;
  for (; it != end; ++it) SetProperty(it->first, &it->second);
  SetParent(mParent);
}

// @ 0x006A2B20
void SP::cDirectPropertyList::Clear() {
  Memset32(mDirectProps, 0, mNumDirectProps); // 0x0092cb00
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
  unsigned int idx = (unsigned int)(position - beg);
  if (position == mpEnd && mpEnd != mpCapacity) {
    VariantPair* e = mpEnd;
    mpEnd = e + 1;
    if (e) {
      e->first = value.first;
      e->second = value.second;
    }
  } else {
    DoInsertValue(position, value);
  }
  return mpBegin + idx;
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
  UIntVector* v = (UIntVector*)ids;
  unsigned int n = (unsigned int)(mPropertyMap.mpEnd - mPropertyMap.mpBegin);
  v->resize(n);
  unsigned int i = 0;
  for (VariantPair* it = mPropertyMap.mpBegin; it != mPropertyMap.mpEnd; ++it) {
    v->mpBegin[i] = it->first;
    i++;
  }
  return (unsigned int)(size_t)mPropertyMap.mpEnd;
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

// The original trims an unsigned-int vector end by the signed byte distance rounded down
// (arithmetic shift) to whole 4-byte elements.
static unsigned int* ShrinkUIntEnd(unsigned int* base, unsigned int* end) {
  int diff = (int)((char*)end - (char*)base);
  return (unsigned int*)((char*)end - (diff >> 2) * 4);
}

// @ 0x006A3180
unsigned int SP::cDirectPropertyList::GetPropertyIDs(unsigned int* ids) {
  UIntVector* v = (UIntVector*)ids;
  PairsCopyBytes(v->mpBegin, v->mpEnd, 0);
  v->mpEnd = ShrinkUIntEnd(v->mpBegin, v->mpEnd);
  void* mgr = PropertyManager();
  for (unsigned int i = 1; i < mNumDirectProps; i++) {
    void* entry = (*(PropertyLookup*)(*(int*)mgr + 0x50))(mgr, 0, i);
    if (*(short*)((char*)entry + 0x12) != 0) {
      unsigned int* e = v->mpEnd;
      if (e < v->mpCapacity) {
        v->mpEnd = e + 1;
        if (e) *e = i;
      } else {
        v->DoInsertValue(e, i);
      }
    }
  }
  unsigned int mapN = (unsigned int)(mPropertyMap.mpEnd - mPropertyMap.mpBegin);
  unsigned int oldN = (unsigned int)(v->mpEnd - v->mpBegin);
  unsigned int total = oldN + mapN;
  if (total > oldN) {
    unsigned int zero = 0;
    v->DoInsertValues(v->mpEnd, total - oldN, zero);
  } else {
    unsigned int* dst = v->mpBegin + total;
    PairsCopyBytes(dst, v->mpEnd, 0);
    v->mpEnd = ShrinkUIntEnd(dst, v->mpEnd);
  }
  unsigned int k = oldN;
  for (VariantPair* it = mPropertyMap.mpBegin; it != mPropertyMap.mpEnd; ++it) {
    v->mpBegin[k] = it->first;
    k++;
  }
  return (unsigned int)(size_t)mPropertyMap.mpEnd;
}

// ---------------------------------------------------------------------------
// Read
// ---------------------------------------------------------------------------
// @ 0x006A2F60
bool SP::cPropertyList::Read(EA::IO::IStream* stream) {
  int nCount;
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
  ((eastl::pvector*)&mPropertyMap)->resize(want);
  for (VariantPair* it = mPropertyMap.mpBegin; it != mPropertyMap.mpEnd; ++it) {
    if (!bResult) break;
    bResult = EA::IO::ReadInt32(stream, &it->first, 1, 0);
    if (bResult) bResult = WriteVariant(stream, &it->second, 0) != 0;
  }
  return bResult;
}
// --- equivalence checker address annotations
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
    void Memset32(...); // 0x0092cb00
    void Property_GetBool(...); // 0x0041e920

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct eastl {
    void lower_bound(void*, void*, unsigned int*, unsigned char); // 0x00555a20
};
struct EA {
    void operator=(int&); // 0x00542b80
};
struct SP {
    void SetBoolProperty(unsigned int, bool); // 0x006a17e0
};
}
