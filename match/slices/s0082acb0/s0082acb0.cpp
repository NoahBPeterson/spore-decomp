// Slice s0082acb0 (batch w2g7, slice 27).
// UTFWin UI serialization helpers: cSPUISerializeHelper / cSPUIDeserializeHelper,
// the temporary StackAllocator and small serialization/allocator helpers.
#include "types.h"
#include <new>
#include <math.h>
#include <string.h>

// The binary expands wcscmp inline (two wide characters per pass, sbb-based result).
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
#pragma intrinsic(wcscmp)
// Inline UTF-16 length scan (the binary expands it to the same two-byte loop).
extern "C" unsigned int __cdecl wcslen(const wchar_t* s);
#pragma intrinsic(wcslen)

// Generic object with a serialization virtual at slot 14 (byte offset +0x38).
struct SerObj {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14(unsigned* p, int n);
};

// A pointer-slot wrapper: this + 0x00 is the object pointer.
struct RefSlot {
  SerObj* mp;                        // +0x00
  void Write8(unsigned a);
  void Write16(unsigned a);
  void Write32(unsigned a);
  void Write64(unsigned a, unsigned b);
};

// @ 0x0082B880
void RefSlot::Write8(unsigned a)  { mp->m14(&a, 1); }
// @ 0x0082B8A0
void RefSlot::Write16(unsigned a) { mp->m14(&a, 2); }
// @ 0x0082B8C0
void RefSlot::Write32(unsigned a) { mp->m14(&a, 4); }
// @ 0x0082B8E0
void RefSlot::Write64(unsigned a, unsigned b) { mp->m14(&a, 8); (void)b; }

// ---- temporary StackAllocator (EA::Allocator::StackAllocator) ----
struct TempAlloc {
  char pad0[8];
  uint32_t mLimit;    // +0x08
  uint32_t mCur;      // +0x0c
  uint32_t mCur2;     // +0x10
  char pad14[0xc];
  void* mpTop;        // +0x20
  bool Grow(uint32_t n);                              // calls 0x928ba0
  void* MallocAligned(uint32_t a, uint32_t b, int c, int d);  // calls 0x928d40
};

// ---- EA::Allocator::StackAllocator::AllocateNewBlock (0x82b0d0) ----
// A 0x10-byte block header linked onto the owned-block list at +0x20:
// +0x00 previous list head, +0x04 current position, +0x08 high-water position.
struct Bookmark {
  Bookmark* mpPrev;   // +0x00
  uint32_t  mCur;     // +0x04
  uint32_t  mHigh;    // +0x08
  uint32_t  mPad0c;   // +0x0c (never initialised)
};
struct StackAlloc {
  char pad0[8];
  uint32_t mLimit;   // +0x08
  uint32_t mCur;     // +0x0c
  uint32_t mCur2;    // +0x10
  char pad14[0xc];
  void* mpTop;       // +0x20
  bool Grow(uint32_t n);
  void AllocateNewBlock(Bookmark* b);
};

struct Pair16 { uint32_t a, b, c, d; };
struct Tri12 { uint32_t a, b, c; };

struct Pool16 {
  char pad0[0x10];
  TempAlloc mAlloc;   // +0x10
  Pair16* NewPair();
};
struct Pool12 {
  char pad0[0x10];
  TempAlloc mAlloc;   // +0x10
  Tri12* NewTri();
};

// @ 0x0082B920
Pair16* Pool16::NewPair() {
  if ((int)(mAlloc.mLimit - mAlloc.mCur) - 0x10 < 0) {
    if (!mAlloc.Grow(0x10)) {
      Pair16* p = 0;
      p->a = 0; p->b = 0; p->c = 0; p->d = 0;
      return 0;
    }
  }
  Pair16* p = (Pair16*)mAlloc.mCur;
  uint32_t nxt = (uint32_t)p + 0x10;
  mAlloc.mCur = nxt;
  mAlloc.mCur2 = nxt;
  p->a = 0; p->b = 0; p->c = 0; p->d = 0;
  return p;
}

// @ 0x0082B970
Tri12* Pool12::NewTri() {
  if ((int)(mAlloc.mLimit - mAlloc.mCur) - 0x10 < 0) {
    if (!mAlloc.Grow(0x10)) {
      Tri12* p = 0;
      p->a = 0; p->b = 0; p->c = 0;
      return 0;
    }
  }
  Tri12* p = (Tri12*)mAlloc.mCur;
  uint32_t nxt = (uint32_t)p + 0x10;
  mAlloc.mCur = nxt;
  mAlloc.mCur2 = nxt;
  p->a = 0; p->b = 0; p->c = 0;
  return p;
}

// ---- cSPUISerializeHelper / cSPUIDeserializeHelper (large members) ----
// Byte stream the (de)serializer pulls from: vtable slot 10 (+0x28) skips n
// bytes, slot 12 (+0x30) reads n bytes and returns the count actually read.
struct SerStream {
  virtual void s00();  virtual void s01();  virtual void s02();  virtual void s03();
  virtual void s04();  virtual void s05();  virtual void s06();  virtual void s07();
  virtual void s08();  virtual void s09();
  virtual uint8_t Skip(int n, int flag);         // +0x28 (slot 10) -> nonzero on success
  virtual void s11();                            // +0x2c (slot 11)
  virtual int  Read(void* buf, int n);           // +0x30 (slot 12)
};

// A named child entry of a parsed value node: { name, payload }.
struct SerProp {
  const wchar_t* mpName;    // +0x00
  void*          mpValue;   // +0x04
};

// 0x20-byte parsed value node (allocated by NewArrayValue).
struct Value20 {
  Value20*       mpChild;   // +0x00 first child
  int            mKind;     // +0x04 1 = object map, 4 = anonymous value
  const wchar_t* mpName;    // +0x08
  void*          mpData0c;  // +0x0c
  void*          mpData10;  // +0x10
  SerProp*       mpProps;   // +0x14
  int            mPropCount;// +0x18
  uint32_t       mPad1c;    // +0x1c
};

// Output of ParseValue: the payload lands in the slot selected by the node's
// "type" property.
struct ParsedProp {
  void* mOther;    // +0x00 default / flattened "value" payload
  void* mString;   // +0x04 "string"
  void* mImage;    // +0x08 "image"
  void* mTexture;  // +0x0c "texture"
  void* mHitmask;  // +0x10 "hitmask"
  void* mObject;   // +0x14 "object"
  void* mStruct;   // +0x18 "struct"
  void* mUnknown;  // +0x1c non-empty "object" with no value child
};

// ---- property table used by ReadProperty -------------------------------
// Node whose child properties are searched (the 12-byte cursor that
// ReadProperty itself receives and hands down to nested elements).
struct PropEntry;
struct PropCursor {
  void* mpNode;     // +0x00 node/view searched by Find
  void* mpData;     // +0x04 destination buffer
  int   mIndex;     // +0x08 element index inside the current run
  PropEntry* Find(PropCursor* pIter, unsigned key, void* ctx);          // 0x95dd00
};

// One named child of a property node (0x18 bytes).
struct PropEntry {
  uint32_t mPad00;      // +0x00
  void*    mpOwner;     // +0x04 object that owns the child list
  uint32_t mKey;        // +0x08
  uint16_t mType;       // +0x0c low 12 bits: type; bit 15: count comes from the stream
  uint16_t mPad0e;
  uint32_t mPad10;      // +0x10
  uint32_t mRunCount;   // +0x14 elements in this run
  bool Prepare(PropCursor* pSlot, PropCursor* pIter, int count, void* ctx, int flags);  // 0x95dbd0
  bool Commit(PropCursor* pIter, PropCursor* pSlot, void* ctx);                         // 0x95dda0
};

// Element descriptor selected by the entry's type (global table 0x154eea0).
struct PropDesc {
  uint16_t mType;       // +0x00 low 12 bits: serialized type
  uint16_t mPad02;
  uint32_t mPad04;
  uint32_t mStride;     // +0x08 bytes per element
  void*    mpChildren;  // +0x0c
  uint32_t mChildCount; // +0x10
};

// Temporary-block reference released when a property has been read (0x82aac0).
struct TempAllocRef {
  StackAlloc* mp;      // +0x00
  void Release();
};

// Localized-text holder (SP::cString at +0x228). Only the two helpers used
// here are modelled.
struct LocString {
  uint32_t mData[5];   // +0x00 (vtable at +0x08)
  bool Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);  // 0x6b54b0
  const wchar_t* GetText();                                                   // 0x6b55c0
};

// True for the type pairs that share a payload representation:
// (3,7), (4,8), (5,9), (6,10) — 0x82ab00.
bool CompatibleTypes(int a, int b);

// Rounds `bytes` up to 8 and carves it out of a stack allocator. Retail expands
// this at both string sites, so keep it inline.
static __forceinline void* AllocTempString(StackAlloc* alloc, uint32_t bytes) {
  uint32_t size = (bytes + 7) & 0xfffffff8u;
  if ((int)(alloc->mLimit - size) - (int)alloc->mCur < 0) {
    if (!alloc->Grow(size)) return 0;
  }
  uint32_t p = alloc->mCur;
  alloc->mCur = p + size;
  alloc->mCur2 = p + size;
  return (void*)p;
}

struct SerializeHelper {
  SerStream* mpStream;   // +0x00
  char pad04[4];         // +0x04
  void** mpObjects;      // +0x08 object table indexed by the 16-bit handles
  char pad0c[4];         // +0x0c
  TempAlloc mTemp;       // +0x10
  char pad34[0x224 - 0x34];
  int  mVersion;         // +0x224
  LocString mText;       // +0x228 localized-string scratch
  void* mPropContext;    // +0x23c context handed to the property table
  StackAlloc mPropAlloc; // +0x240 scratch allocator for the decoded payloads
  Value20* NewArrayValue(int count);
  void* FindProp(Value20* node, const wchar_t* name);   // 0x82ab40
  void* UnwrapValueNode(Value20* node);                 // 0x82abd0
  void* ParseObjectValue(Value20* node);                // 0x82d910
  void* ParseStructValue(Value20* node);                // 0x82d7b0
  bool ParseValue(ParsedProp* out, const wchar_t* defaultType, Value20* node);
  bool SkipProperty(unsigned short type, unsigned short value);
  bool ReadProperty(PropCursor* cur);
};

// @ 0x0082ACB0
bool SerializeHelper::ParseValue(ParsedProp* out, const wchar_t* defaultType, Value20* node) {
  if (node->mKind != 1)
    return false;

  const wchar_t* typeName = (const wchar_t*)FindProp(node, L"type");
  if (!typeName)
    typeName = defaultType;

  void* key = FindProp(node, L"key");
  if (key) {
    if (wcscmp(typeName, L"image") == 0)   { out->mImage   = key; return true; }
    if (wcscmp(typeName, L"texture") == 0) { out->mTexture = key; return true; }
    if (wcscmp(typeName, L"hitmask") == 0) { out->mHitmask = key; return true; }
    if (wcscmp(typeName, L"string") == 0)  { out->mString  = key; return true; }
    return false;
  }

  void* value = FindProp(node, L"value");
  if (value) {
    if (wcscmp(typeName, L"object") == 0) { out->mObject = value; return true; }
    out->mOther = value;
    return true;
  }

  // No "key"/"value" property: resolve through the node's first child.
  Value20* child = node->mpChild;
  bool childIsValue = child && child->mKind == 4 && wcscmp(node->mpName, L"value") == 0;

  if (wcscmp(typeName, L"object") == 0) {
    if (childIsValue) {
      out->mObject = UnwrapValueNode(child);
      return true;
    }
    void* r = ParseObjectValue(child);
    if (!r)
      return false;
    out->mUnknown = r;
    return true;
  }
  if (wcscmp(typeName, L"struct") == 0) {
    if (child->mKind != 1)
      return false;
    if (wcscmp(child->mpName, L"struct") != 0)
      return false;
    out->mStruct = ParseStructValue(child);
    return true;
  }
  if (childIsValue)
    out->mOther = UnwrapValueNode(child);
  return true;
}

// @ 0x0082B160
bool SerializeHelper::SkipProperty(unsigned short type, unsigned short value) {
  if (mVersion < 2) {
    // Legacy format: the stored byte count itself precedes the payload.
    unsigned n;
    if (mpStream->Read(&n, 4) != 4)
      return false;
    return mpStream->Skip(n, 1);
  }
  switch (type) {
  case 2: case 3: case 7:
    return mpStream->Skip(value, 1);
  case 4: case 8: case 19:
    return mpStream->Skip(value * 2, 1);
  case 5: case 9: case 11:
    return mpStream->Skip(value * 4, 1);
  case 6: case 10: case 12: case 15: case 17:
    return mpStream->Skip(value * 8, 1);
  case 14: case 16:
    return mpStream->Skip(value * 16, 1);
  case 18: {
    // Array of counted payloads: 0xffff marks an 8-byte entry, otherwise
    // the count is in UTF-16 code units.
    int n = value;
    for (int i = 0; i < n; i++) {
      unsigned short len;
      if (mpStream->Read(&len, 2) != 2)
        return false;
      unsigned size = (len == 0xffff) ? 8 : (unsigned)len * 2;
      if (!mpStream->Skip(size, 1))
        return false;
    }
    return true;
  }
  case 20: {
    // Stored length is a full dword in this variant.
    unsigned n;
    if (mpStream->Read(&n, 4) != 4)
      return false;
    return mpStream->Skip(n, 1);
  }
  case 13:
  default:
    return false;
  }
}

// @ 0x0082B310 : cSPUIDeserializeHelper::ReadProperty
//
// Reads one property (key, type, element count, payload) from the stream and
// decodes the elements into the buffer described by the cursor. Element type
// 19 stores object handles, 20 a run of nested property lists, 18 strings
// (inline or as a localized reference) and the remaining types a blittable
// payload. 0xffff in a 16-bit length field marks the extended encodings.
bool SerializeHelper::ReadProperty(PropCursor* cur) {
  // Scratch allocator owning the payloads decoded below; released on exit.
  void* ctx = &mPropContext;                       // +0x23c
  TempAllocRef allocRef;                           // L(0x0c)
  allocRef.mp = ctx ? &mPropAlloc : 0;             // +0x240
  StackAlloc* alloc = allocRef.mp;
  alloc->AllocateNewBlock(0);

  unsigned key;
  unsigned short type;
  unsigned short count;
  PropCursor iter;
  PropCursor slot;
  PropEntry* entry;
  PropDesc* desc;
  unsigned short expected;
  bool ok;

  if (mpStream->Read(&key, 4) != 4) goto unwind;
  if (mpStream->Read(&type, 2) != 2) goto unwind;
  if (mpStream->Read(&count, 2) != 2) goto unwind;
  if ((unsigned short)(type - 2) > 0x12) goto fail;

  entry = cur->Find(&iter, key, &mPropContext);
  if (!entry || (!(entry->mType & 0x8000) && count != entry->mRunCount)) {
    // Unknown property, or a run length that disagrees with the table:
    // skip the payload without touching the destination.
    ok = SkipProperty(type, count);
    goto release;
  }
  if (!entry->Prepare(&slot, &iter, count, &mPropContext, 0)) goto fail;

  desc = (PropDesc*)slot.mpNode;
  expected = (unsigned short)(desc->mType & 0xfff);
  if (type != expected && !CompatibleTypes(type, expected)) {
    // The stored type is not the one the destination expects.
    ok = SkipProperty(type, count);
    goto release;
  }

  if (expected == 19) {
    // 32-bit object handles; 0xffff leaves the destination slot untouched.
    unsigned* out = (unsigned*)slot.mpData;
    unsigned* end = out + count;
    while (out != end) {
      unsigned short idx;
      if (mpStream->Read(&idx, 2) != 2) goto fail;
      if (idx != 0xffff)
        *out = (unsigned)mpObjects[idx];
      ++out;
    }
  } else if (expected == 20) {
    // Array of sub-objects: each element carries its own property run.
    unsigned header;
    mpStream->Read(&header, 4);        // leading dword, value unused
    (void)header;
    PropCursor sub;
    sub.mpNode = slot.mpNode;
    sub.mpData = slot.mpData;
    sub.mIndex = 1;
    for (int i = 0; i < (int)count; i++) {
      unsigned short subCount;
      if (mpStream->Read(&subCount, 2) != 2) goto fail;
      if (subCount > 0xc8) goto fail;
      for (int j = 0; j < (int)subCount; j++) {
        if (!ReadProperty(&sub)) goto fail;
      }
      sub.mpData = (char*)sub.mpData + desc->mStride;
    }
  } else if (expected == 18) {
    // Strings: a localized reference (0xffff + table/instance ids) or an
    // inline UTF-16 run whose length is the 16-bit field.
    const wchar_t** out = (const wchar_t**)slot.mpData;
    const wchar_t** end = out + count;
    while (out != end) {
      unsigned short len;
      if (mpStream->Read(&len, 2) != 2) goto fail;
      if (len == 0xffff) {
        unsigned tableID;
        unsigned instanceID;
        if (mpStream->Read(&tableID, 4) != 4) goto fail;
        if (mpStream->Read(&instanceID, 4) != 4) goto fail;
        mText.Load(tableID, instanceID, 0);
        const wchar_t* text = mText.GetText();
        unsigned bytes = (unsigned)wcslen(text) * 2 + 2;
        wchar_t* buf = (wchar_t*)AllocTempString(alloc, bytes);
        memcpy(buf, text, bytes);
        *out = buf;
      } else {
        unsigned bytes = (unsigned)len * 2 + 2;
        wchar_t* buf = (wchar_t*)AllocTempString(alloc, bytes);
        if (len) {
          unsigned n = (unsigned)len * 2;
          if (mpStream->Read(buf, n) != (int)n) goto fail;
        }
        buf[len] = 0;
        *out = buf;
      }
      ++out;
    }
  } else {
    // Blittable payload: `count` elements of the descriptor's stride.
    if ((unsigned short)(expected - 2) > 0xf) goto fail;
    unsigned size = (unsigned)count * desc->mStride;
    if (mpStream->Read(slot.mpData, size) != (int)size) goto fail;
  }

  ok = entry->Commit(&iter, &slot, &mPropContext);
release:
  allocRef.Release();
  return ok;
fail:
  allocRef.Release();
  return false;
unwind:
  allocRef.Release();
  return false;
}

// @ 0x0082B060
Value20* SerializeHelper::NewArrayValue(int count) {
  if (count == 0) return 0;
  uint32_t size = count * 0x20;
  uint32_t aligned = (size + 7) & 0xfffffff8u;
  if ((int)(mTemp.mLimit - mTemp.mCur) - (int)aligned < 0) {
    if (!mTemp.Grow(aligned)) {
      memset((void*)0, 0, size);
      return 0;
    }
  }
  Value20* p = (Value20*)mTemp.mCur;
  uint32_t nxt = (uint32_t)p + aligned;
  mTemp.mCur = nxt;
  mTemp.mCur2 = nxt;
  memset(p, 0, size);
  return p;
}

// @ 0x0082B7F0 : cSPUISerializationAllocator::Allocate (8-byte object fast path)
struct SerAlloc {
  char pad0[4];
  TempAlloc mAlloc;   // +0x04
  void* Allocate(uint32_t align, uint32_t size);
};
void* SerAlloc::Allocate(uint32_t align, uint32_t size) {
  if (size > 8) {
    return mAlloc.MallocAligned(align, size, 0, 1);
  }
  uint32_t aligned = (align + 7) & 0xfffffff8u;
  if ((int)(mAlloc.mLimit - mAlloc.mCur) - (int)aligned < 0) {
    if (!mAlloc.Grow(aligned)) return 0;
  }
  uint32_t p = mAlloc.mCur;
  uint32_t nxt = p + aligned;
  mAlloc.mCur = nxt;
  mAlloc.mCur2 = nxt;
  return (void*)p;
}

// @ 0x0082B0D0
void StackAlloc::AllocateNewBlock(Bookmark* b) {
  uint32_t curPos, highPos;
  if (b) {
    highPos = (uint32_t)b;
    curPos = (uint32_t)b;
  } else {
    curPos = mCur;
    highPos = mCur2;
  }
  if (mCur != mCur2) {
    uint32_t t = (mCur2 + 7) & 0xfffffff8u;
    mCur2 = t;
    if (t > mLimit) mCur2 = mLimit;
    mCur = mCur2;
  }
  Bookmark* p;
  Bookmark* prev;
  if ((int)(mLimit - mCur) - 0x10 < 0 && !Grow(0x10)) {
    // Retail still runs the list-link stores, through a null block pointer.
    prev = (Bookmark*)mpTop;
    p = 0;
  } else {
    p = (Bookmark*)mCur;
    prev = (Bookmark*)mpTop;
    uint32_t nxt = mCur + 0x10;
    mCur = nxt;
    mCur2 = nxt;
  }
  p->mCur = curPos;
  p->mHigh = highPos;
  p->mpPrev = prev;
  mpTop = p;
}

// binary search of a static wide-string table, returns a 16-bit code (0x0082AFE0).
extern const unsigned char g_strTable[];   // 0x141a1c0 pairs {char16* name; ushort code;}
static int CmpW(const unsigned short* a, const unsigned short* b) {
  while (*a == *b) { if (!*a) return 0; ++a; ++b; }
  return *a < *b ? -1 : 1;
}
// @ 0x0082AFE0
int __stdcall LookupCode(const unsigned short* key) {
  int lo = 0, hi = 0x16;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    const unsigned short* name = *(const unsigned short**)(g_strTable + mid * 8);
    if (CmpW(key, name) == 0) return *(const unsigned short*)(g_strTable + mid * 8 + 4);
    if (CmpW(key, name) < 0) hi = mid; else lo = mid + 1;
  }
  return 0;
}
