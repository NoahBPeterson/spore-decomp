// src/game/Spui/SPUISerialization.cpp -- migrated from slice(s) s0082cd30, s0082b9c0, s0082acb0, s00829bc0 by tools/migrate/rewrite.py
// Object file: Spui/SPUISerialization.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include <math.h>
#include <string.h>
#include "EA/Allocator/StackAllocator.h"

// ---- items of slice s00829bc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct TableEntry { const unsigned short* mpName; uint32_t mValue; };
struct Table {
  char pad0[4];
  int m4;              // +4
  char pad8[0xc];
  TableEntry* mEntries;  // +0x14
  int mCount;            // +0x18
};
static int CmpStr16(const unsigned short* a, const unsigned short* b) {
  while (*a == *b) { if (!*a) return 0; ++a; ++b; }
  return *a < *b ? -1 : 1;
}
// ---- items of slice s00829bc0 end

// ---- items of slice s0082acb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const unsigned char g_strTable[];   // 0x141a1c0 pairs {char16* name; ushort code;}
struct SerObj {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14(unsigned* p, int n);
};
struct RefSlot {
  SerObj* mp;                        // +0x00
  void Write8(unsigned a);
  void Write16(unsigned a);
  void Write32(unsigned a);
  void Write64(unsigned a, unsigned b);
};
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
struct Value20 { uint8_t raw[0x20]; };
struct SerializeHelper {
  char pad0[0x10];
  TempAlloc mTemp;    // +0x10
  Value20* NewArrayValue(int count);
  void ParseValue();
  void SkipProperty();
  void ReadProperty();
};
struct SerAlloc {
  char pad0[4];
  TempAlloc mAlloc;   // +0x04
  void* Allocate(uint32_t align, uint32_t size);
};
struct Bookmark { void* mpNext; void* mpA; void* mpB; };
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
static int CmpW(const unsigned short* a, const unsigned short* b) {
  while (*a == *b) { if (!*a) return 0; ++a; ++b; }
  return *a < *b ? -1 : 1;
}
// ---- items of slice s0082acb0 end

// ---- items of slice s0082b9c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct U16Vec {
  unsigned short* mpBegin;    // +0x00
  unsigned short* mpEnd;      // +0x04
  unsigned short* mpEndCap;   // +0x08
  __declspec(noinline) U16Vec* Setup(unsigned n, const void* alloc);
  U16Vec* Init(unsigned n, const void* alloc);
  void AddZero();
  void InsertAt(void* pos, const void* value);  // @ 0x82c970 (thiscall)
};
struct RBTree {
  char pad0[0x14];
  int mCount;   // +0x14
  void Insert(void* node, void* parent, void* where, int flag);
};
struct RLEHitMask {
  char pad0[0x14];
  int m14;            // +0x14
  int m18;            // +0x18
  int m1c;            // +0x1c
  RLEHitMask();
};
// ---- items of slice s0082b9c0 end

// ---- items of slice s0082cd30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
#pragma intrinsic(wcscmp)
void __cdecl operator_delete_array(void* p);     // @ 0xf47380 (operator delete[])
struct SerObject;
struct Token {
    Token* mpNext;              // +0x00
    int mType;                  // +0x04 (1 = element)
    const wchar_t* mpName;      // +0x08
    int mReserved;              // +0x0c
    int mDepth;                 // +0x10
};
struct Prop;
struct SerObject {              // Pool12 record
    const wchar_t* mpClassId;   // +0x00 "clsid"
    const wchar_t* mpAttr2;     // +0x04
    Prop* mpProps;              // +0x08
};
struct Value {                  // 0x20 bytes, allocated as an array by NewValues
    char mData[0x18];
    Prop* mpStruct;             // +0x18 (nested "struct": property list)
    SerObject* mpObject;        // +0x1c (nested "object")
};
struct Prop {                   // Pool16 record
    uint32_t mId;               // +0x00 "propid"
    uint16_t mType;             // +0x04
    uint16_t mCount;            // +0x06
    Value* mpValues;            // +0x08
    Prop* mpNext;               // +0x0c
};
extern Prop g_CommentProp;      // @ 0x164E8A8 (returned for <prop propid="Comment">)
extern Prop g_EmptyProps;       // @ 0x164E8B8 (returned for an empty <struct>)
template<class T> struct PtrVector {
    T* mpBegin;                 // +0x00
    T* mpEnd;                   // +0x04
    T* mpCapacity;              // +0x08
    uint32_t mAllocator;        // +0x0c
    void DoInsertValue(T* position, const T& value);        // @ 0x820BB0
    void push_back(T value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
struct PropStackVector {
    Prop** mpBegin;
    Prop** mpEnd;
    Prop** mpCapacity;
    uint32_t mOverflowAllocator;        // fixed_vector_allocator: overflow allocator state
    Prop** mpPoolBegin;                 // fixed_vector_allocator: start of the in-object buffer
    uint32_t mPoolUsed;
    Prop* mBuffer[64];
    void DoInsertValue(Prop** position, Prop* const& value);   // @ 0x82F170
    PropStackVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 64), mpPoolBegin(mBuffer) {}
    ~PropStackVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator_delete_array(mpBegin);
    }
    void push_back(Prop* const& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) Prop*(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
struct SerializeHelper_s0082_cd30 {
    char mHead[0x50];                       // +0x00 stream, token list, temp allocator, top-level set
    PtrVector<SerObject*> mAllObjects;      // +0x50
    char mGap[4];
    PtrVector<Value*> mAllValues;           // +0x64
    char mTail[0xfc - 0x74];

    const wchar_t* GetAttribute(Token* tok, const wchar_t* name);         // @ 0x82AB40
    bool ParseValue(Value* value, const wchar_t* type, Token* tok);        // @ 0x82ACB0
    uint16_t ParseTypeName(const wchar_t* type);                           // @ 0x82AFE0
    Value* NewValues(unsigned count);                                      // @ 0x82B060
    Prop* NewProp();                                                       // @ 0x82B920
    SerObject* NewObject();                                                // @ 0x82B970

    SerObject* ParseObject(Token* tok);                                    // 0x0082D910
    Prop* ParseProp(Token* tok);                                           // 0x0082D480
    Prop* ParseProps(Token* tok);                                          // 0x0082D7B0
};
struct IStream {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
    virtual void s20();
    virtual int GetPosition(int whence);                 // +0x24
    virtual int SetPosition(int pos, int whence);        // +0x28
    virtual int s2C();
    virtual int Read(void* dst, int size);               // +0x30
};
struct SerTypeInfo {                                     // per-type serialization record
    char mPad[0x1c];
    void (*mpFinish)(void* instance);                    // +0x1c
};
struct SerDesc {                                         // filled by ISerializable::GetDescriptor
    const SerTypeInfo* mpType;
    void* mpInstance;
    int mReserved[4];
};
struct ISerializable;
struct IUnknown32 {
    virtual void AddRef();
    virtual void Release();
    virtual void* s08();
    virtual ISerializable* QueryInterface(uint32_t iid);    // +0x0c
};
struct ISerializable : IUnknown32 {
    virtual void GetDescriptor(SerDesc* out);               // +0x10
};
template<class T> struct AutoRefCount {
    T* mp;
    AutoRefCount(T* p);                                     // @ 0x572660
    ~AutoRefCount() { if (mp) mp->Release(); }
    void Set(T* p);                                         // @ 0x68F5B0 (ClsF5B0::Set)
};
struct ObjectList {
    AutoRefCount<IUnknown32>* mpBegin;      // +0x00
    AutoRefCount<IUnknown32>* mpEnd;        // +0x04
    void Reserve(unsigned n);                               // @ 0x82C650
    void push_back(const AutoRefCount<IUnknown32>& v);      // @ 0x82CCF0
    void push_back_null();                                  // @ 0x82CCB0
};
ISerializable* interface_cast_ISerializable(AutoRefCount<IUnknown32>* slot);   // @ 0x82B900
struct ResourceManager {
    virtual void m00(); virtual void m04(); virtual void m08();
    virtual int GetResource(void* key, IUnknown32** out, int a, int b, int c, void* desc);   // +0x0c
};
ResourceManager* GetResourceManager();                       // @ 0x67DCD0
struct ObjectFactory {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0C();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1C(); virtual void m20();
    virtual IUnknown32* CreateById(uint32_t id, int a, int b);    // +0x24
};
ObjectFactory* GetObjectFactory();                           // @ 0x920090
struct Bookmark_s0082_cd30 {
    Bookmark_s0082_cd30* mpPrev;       // +0x00
    char* mpAddress;        // +0x04
    char* mpObjectEnd;      // +0x08
};
struct StackAllocator {
    char mPad0[4];
    char* mpCurrentBlock;       // +0x04
    char* mpCurrentBlockEnd;    // +0x08
    char* mpObjectBegin;        // +0x0c
    char* mpObjectCursor;       // +0x10
    char mPad14[0x0c];
    Bookmark_s0082_cd30* mpTopBookmark;    // +0x20
    void AllocateNewBlock(int flags);                       // @ 0x82B0D0
    void FreeToBlock(char* address);                        // @ 0x928C40
    // Pop the top bookmark (the inlined tail used when parsing ends without a fatal error).
    bool PopBookmark()
    {
        Bookmark_s0082_cd30* bm = mpTopBookmark;
        if (bm == 0)
            return false;
        char* address = bm->mpAddress;
        char* objectEnd = bm->mpObjectEnd;
        mpTopBookmark = bm->mpPrev;
        if (mpCurrentBlock < address && address < mpCurrentBlockEnd) {
            mpObjectBegin = address;
            mpObjectCursor = address;
            mpObjectCursor = objectEnd;
            return true;
        }
        FreeToBlock(address);
        mpObjectCursor = objectEnd;
        return true;
    }
};
struct AllocScope {
    char mPad[4];
    StackAllocator* mpAlloc;
    void Release();                                         // @ 0x82AAC0
};
struct AllocVBase { virtual void a0(); };
struct TempAllocator : AllocVBase, StackAllocator {};
struct ImageBinder {                                        // cSPUIImageToTextureBinder (embedded at +0x264)
    virtual void b00(); virtual void b04(); virtual void b08(); virtual void b0C();
    virtual void Bind(void* desc, int kind, void* key);    // +0x10
    virtual void End();                                    // +0x14
};
struct BindDesc {
    const void* mpName;         // 0x141A134
    int* mpOut;
    int mCount;
};
struct RLEHitMask_s0082_cd30 : IUnknown32 {
    char mPad[0x24];
    RLEHitMask_s0082_cd30();                                           // @ 0x82C190
    void BuildAssign(const int* size, void* data);          // @ 0x9574C0
};
void* operator new(size_t size, const char* name, int a, int b, int c, int d);   // @ 0xf473a0
struct U16Buffer {
    uint16_t* mpData;
    char mPad[0x14];
    U16Buffer() {}
    void Resize(unsigned count, const void* fill);          // @ 0x82CC60
    ~U16Buffer();                                           // @ 0x7A41A0
};
struct SerCollection {
    void NotifyBound(IUnknown32* obj);                      // @ 0x998FC0
};
struct DeserializeHelper {
    IStream* mpStream;                      // +0x000
    SerCollection* mpOutput;                // +0x004
    ObjectList mObjects;                    // +0x008 (fixed_vector<AutoRefCount<IUnknown32>,128>)
    char mObjectsStorage[0x224 - 0x10];     // +0x010 fixed storage, error message, ...
    int mFormatVersion;                     // +0x224
    char mLocalizer[0x23c - 0x228];         // +0x228
    TempAllocator mTempAlloc;               // +0x23C (StackAllocator subobject at +0x240)
    ImageBinder mImageBinder;               // +0x264
    char mTail[0x270 - 0x268];                // retail size is 0x270

    DeserializeHelper(IStream* stream, void* output);       // @ 0x82C770 (second argument is not the output collection pointer)
    ~DeserializeHelper();                                   // @ 0x82C550
    bool ProcessStream();                                   // @ 0x82CD30
    bool ProcessProperty(SerDesc* desc);                    // @ 0x82B310
};
// ---- items of slice s0082cd30 end

// @ 0x0082ab00
int RangeCheck(int a, int b)
{
  while (a > b) { int t = a; a = b; b = t; }
  if ((unsigned)(a - 3) <= 3 && b - a == 4) return 1;
  return 0;
}




// @ 0x0082ab40
uint32_t __stdcall TableLookup(Table* t, const unsigned short* key)
{
  if (t->m4 != 1) return 0;
  for (int i = 0; i < t->mCount; ++i) {
    if (CmpStr16(t->mEntries[i].mpName, key) == 0) return t->mEntries[i].mValue;
  }
  return 0;
}



// @ 0x0082acb0
void SerializeHelper::ParseValue()
{
  // Full recursive-descent serializer not reconstructed.
}



// @ 0x0082afe0
int __stdcall LookupCode(const unsigned short* key)
{
  int lo = 0, hi = 0x16;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    const unsigned short* name = *(const unsigned short**)(g_strTable + mid * 8);
    if (CmpW(key, name) == 0) return *(const unsigned short*)(g_strTable + mid * 8 + 4);
    if (CmpW(key, name) < 0) hi = mid; else lo = mid + 1;
  }
  return 0;
}



// @ 0x0082b060
Value20* SerializeHelper::NewArrayValue(int count)
{
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



// @ 0x0082b0d0
void StackAlloc::AllocateNewBlock(Bookmark* b)
{
  uint32_t a, c;
  if (b) {
    a = (uint32_t)b;
    c = (uint32_t)b;
  } else {
    c = mCur;
    a = mCur2;
  }
  if (mCur != mCur2) {
    uint32_t t = (mCur2 + 7) & 0xfffffff8u;
    mCur2 = t;
    if (t > mLimit) mCur2 = mLimit;
    mCur = mCur2;
  }
  if ((int)(mLimit - mCur) - 0x10 < 0) {
    if (!Grow(0x10)) return;
  }
  uint32_t p = mCur;
  uint32_t nxt = p + 0x10;
  mCur = nxt;
  mCur2 = nxt;
  void** q = (void**)p;
  q[0] = mpTop;
  q[1] = (void*)a;
  q[2] = (void*)c;
  mpTop = (void*)p;
}



// @ 0x0082b160
void SerializeHelper::SkipProperty()
{
}



// @ 0x0082b310
void SerializeHelper::ReadProperty()
{
}



// @ 0x0082b7f0
void* SerAlloc::Allocate(uint32_t align, uint32_t size)
{
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



// @ 0x0082b880
void RefSlot::Write8(unsigned a)
{ mp->m14(&a, 1); }



// @ 0x0082b8a0
void RefSlot::Write16(unsigned a)
{ mp->m14(&a, 2); }



// @ 0x0082b8c0
void RefSlot::Write32(unsigned a)
{ mp->m14(&a, 4); }



// @ 0x0082b8e0
void RefSlot::Write64(unsigned a, unsigned b)
{ mp->m14(&a, 8); (void)b; }



// @ 0x0082b920
Pair16* Pool16::NewPair()
{
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



// @ 0x0082b970
Tri12* Pool12::NewTri()
{
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


// @ 0x0082b9c0
void SerializeHelperProcessTokens2()
{
}


// @ 0x0082bfa0
U16Vec* U16Vec::Setup(unsigned n, const void* alloc)
{
  if (n != 0) {
    unsigned short* p = (unsigned short*)::operator new((size_t)(n * 2), (const char*)0x13f6b3c, 0, 0, 0x13ebb38, 0xd1);
    mpBegin = p;
    mpEnd = p;
    mpEndCap = p + n;
  } else {
    mpBegin = 0;
    mpEnd = 0;
    mpEndCap = 0;
  }
  return this;
}


// @ 0x0082c000
void RBTree::Insert(void* node, void* parent, void* where, int flag)
{
  (void)node; (void)parent; (void)where; (void)flag;
}


// @ 0x0082c190
RLEHitMask::RLEHitMask()
: m14(0), m18(0), m1c(0) {
}


// @ 0x0082c1d0
void RLEHitMaskDestroy(RLEHitMask* p)
{ (void)p; }


// @ 0x0082c210
void WriteHitmaskInline()
{
}


// @ 0x0082c420
void SerializeHelperWrite2()
{
}


// @ 0x0082c550
void SerializeHelperNuke()
{
}


// @ 0x0082c5a0
void SerializeHelperNuke2()
{
}


// @ 0x0082c770
void SerializeHelperWrite3()
{
}


// @ 0x0082c810
void SerializeHelperWrite4()
{
}


// @ 0x0082cc60
U16Vec* U16Vec::Init(unsigned n, const void* alloc)
{
  Setup(n, alloc);
  if (n != 0) {
    unsigned short* p = mpBegin;
    unsigned short* e = p + n;
    while (p < e) *p++ = 0;
  }
  mpEnd = mpBegin + n;
  return this;
}


// @ 0x0082ccb0
void U16Vec::AddZero()
{
  unsigned short* e = mpEnd;
  if (e < mpEndCap) {
    mpEnd = (unsigned short*)((char*)e + 4);
    if (e != 0)
      *(unsigned int*)e = 0;
  } else {
    unsigned int v = 0;
    InsertAt(e, &v);
  }
}

// @ 0x0082cd30
bool DeserializeHelper::ProcessStream()
{
    StackAllocator* const pAlloc = &mTempAlloc;
    AllocScope scope;
    scope.mpAlloc = pAlloc;
    pAlloc->AllocateNewBlock(0);
    ResourceManager* const mgr = GetResourceManager();
    ObjectFactory* const factory = GetObjectFactory();

    if (mgr == 0)
        goto endOfStream;

    uint32_t magic;
    uint32_t version;
    uint16_t countBindA, countBindB, countHit, countObjects;
    uint32_t total;
    if (factory == 0 || mpStream->Read(&magic, 4) != 4)
        goto fail;
    version = 0;
    if (mpStream->Read(&version, 2) != 2)
        goto fail;
    if (mpStream->Read(&countBindA, 2) != 2)
        goto fail;
    if (mpStream->Read(&countBindB, 2) != 2)
        goto fail;
    if (mpStream->Read(&countHit, 2) != 2)
        goto fail;
    if (mpStream->Read(&countObjects, 2) != 2)
        goto fail;
    if (magic != 0xE3FE3FB8 || (uint16_t)(version - 1) > 2)
        goto fail;

    mFormatVersion = (uint16_t)version;
    total = (uint32_t)countObjects + countHit + countBindB + countBindA;
    if (total > 0x1770)
        goto fail;
    {
        ObjectList* const objects = &mObjects;
        objects->Reserve(total);

        // first group: images (binder kind 0x3FD)
        for (int i = 0; i < (int)countBindA; ++i) {
            uint32_t key[3] = { 0, 0, 0 };
            if (mpStream->Read(key, 12) != 12)
                goto fail;
            int out = 0;
            BindDesc desc;
            desc.mpOut = &out;
            desc.mpName = (const void*)0x141A134;
            desc.mCount = 1;
            mImageBinder.Bind(&desc, 0x3FD, key);
            {
                AutoRefCount<IUnknown32> ref((IUnknown32*)out);
                objects->push_back(ref);
            }
            mImageBinder.End();
        }
        // second group: textures (binder kind 0x3FE)
        for (int i = 0; i < (int)countBindB; ++i) {
            uint32_t key[3] = { 0, 0, 0 };
            if (mpStream->Read(key, 12) != 12)
                goto fail;
            int out = 0;
            BindDesc desc;
            desc.mpOut = &out;
            desc.mpName = (const void*)0x141A134;
            desc.mCount = 1;
            mImageBinder.Bind(&desc, 0x3FE, key);
            {
                AutoRefCount<IUnknown32> ref((IUnknown32*)out);
                objects->push_back(ref);
            }
            mImageBinder.End();
        }
        // third group: hit masks
        for (int i = 0; i < (int)countHit; ++i) {
            uint8_t kind = 0;
            if (mFormatVersion >= 3) {
                if (mpStream->Read(&kind, 1) != 1)
                    goto fail;
                if (kind == 1) {
                    int size[2];
                    int rleCount;
                    if (mpStream->Read(&size[0], 4) != 4 || mpStream->Read(&size[1], 4) != 4 ||
                        mpStream->Read(&rleCount, 4) != 4)
                        goto fail;
                    U16Buffer data;
                    data.Resize(rleCount, &kind);
                    if (mpStream->Read(data.mpData, rleCount * 2) != rleCount * 2)
                        goto fail;
                    RLEHitMask_s0082_cd30* mask = new("UTFWin/RLEHitMask", 0, 0, 0, 0) RLEHitMask_s0082_cd30;
                    int dims[2] = { size[0], size[1] };
                    mask->BuildAssign(dims, &data);
                    AutoRefCount<IUnknown32> ref(mask);
                    objects->push_back(ref);
                    continue;
                }
                if (kind != 0)
                    continue;
            }
            // legacy / external hit mask: a resource key
            uint32_t key[3] = { 0, 0, 0 };
            if (mpStream->Read(key, 12) != 12)
                goto fail;
            IUnknown32* resource = 0;
            struct { uint32_t a; int pad; uint32_t c; } keyDesc;
            keyDesc.a = key[0];
            keyDesc.pad = 0x19AEF76;
            keyDesc.c = key[2];
            mgr->GetResource(key, &resource, 0, 0, 0, &keyDesc);
            objects->push_back_null();
            (objects->mpEnd - 1)->Set(resource);
        }
        // fourth group: objects created through the factory by id
        for (int i = 0; i < (int)countObjects; ++i) {
            uint32_t id;
            if (mpStream->Read(&id, 4) != 4)
                goto fail;
            IUnknown32* obj = factory->CreateById(id, 0, 0);
            if (obj)
                obj->AddRef();
            objects->push_back(*(AutoRefCount<IUnknown32>*)&obj);
            if (obj)
                obj->Release();
            if (objects->mpEnd[-1].mp == 0)
                goto fail;
        }

        // property blocks: <0x5FF5 marker><u16 object index><u16 flags><count x property>
        uint16_t marker;
        uint16_t index;
        int got = mpStream->Read(&marker, 2);
        while (got == 2 && mpStream->Read(&index, 2) == 2) {
            if (marker != 0x5FF5)
                goto fail;
            if (index == 0xFFFF) {
                uint32_t trailer;
                if (mpStream->Read(&trailer, 4) != 4 || trailer != 0x1C01C047)
                    goto fail;
                int n = (int)(objects->mpEnd - objects->mpBegin);
                for (int k = 0; k < n; ++k) {
                    IUnknown32* o = objects->mpBegin[k].mp;
                    if (o) {
                        ISerializable* ser = o->QueryInterface(0xEEC58382);
                        if (ser) {
                            SerDesc desc;
                            ser->GetDescriptor(&desc);
                            if (desc.mpType->mpFinish)
                                desc.mpType->mpFinish(desc.mpInstance);
                        }
                    }
                }
                scope.Release();
                return true;
            }
            if (index >= total)
                goto fail;
            uint16_t flags;
            if (mpStream->Read(&flags, 2) != 2)
                goto fail;
            if (flags & 0x8000)
                mpOutput->NotifyBound(objects->mpBegin[index].mp);
            int propCount = flags & 0x7FFF;
            if (propCount > 200)
                goto fail;
            if (propCount > 0) {
                ISerializable* ser = interface_cast_ISerializable(&objects->mpBegin[index]);
                if (ser == 0)
                    goto fail;
                SerDesc desc;
                ser->GetDescriptor(&desc);
                for (int k = 0; k < propCount; ++k) {
                    if (!ProcessProperty(&desc))
                        goto fail;
                }
            }
            got = mpStream->Read(&marker, 2);
        }
    }

endOfStream:
    pAlloc->PopBookmark();
    return false;

fail:
    scope.Release();
    return false;
}

// @ 0x0082d480
Prop* SerializeHelper_s0082_cd30::ParseProp(Token* tok)
{
    if (tok->mType == 1 && wcscmp(tok->mpName, L"prop") == 0) {
    const wchar_t* propId = GetAttribute(tok, L"propid");
    const wchar_t* type = GetAttribute(tok, L"type");
    const wchar_t* count = GetAttribute(tok, L"count");
    if (propId == 0 || type == 0)
        return 0;
    if (_wcsicmp(propId, L"Comment") == 0)
        return &g_CommentProp;

    Prop* prop = NewProp();
    prop->mId = wcstoul(propId, 0, 0);
    prop->mType = ParseTypeName(type);
    unsigned n = count ? wcstoul(count, 0, 0) : 1;
    prop->mCount = (uint16_t)n;
    prop->mpValues = NewValues((uint16_t)n);

    Token* child = tok->mpNext;
    int depth = tok->mDepth;
    if (child == 0 || child->mDepth <= depth) {
        // no child elements: the value is inline (at most one)
        if (prop->mCount > 1)
            return 0;
        if (prop->mCount != 0 && !ParseValue(prop->mpValues, type, tok))
            return 0;
    } else {
        int found = 0;
        int offset = 0;
        for (; child; child = child->mpNext) {
            if (child->mDepth <= depth)
                break;
            if (child->mDepth != depth + 1 || child->mType != 1)
                continue;
            if (found >= (int)prop->mCount)
                return 0;
            const wchar_t* name = child->mpName;
            bool failed;
            if (wcscmp(name, L"value") == 0) {
                failed = !ParseValue((Value*)((char*)prop->mpValues + offset), type, child);
            } else if (wcscmp(name, L"object") == 0) {
                ((Value*)((char*)prop->mpValues + offset))->mpObject = ParseObject(child);
                failed = ((Value*)((char*)prop->mpValues + offset))->mpObject == 0;
            } else if (wcscmp(name, L"struct") == 0) {
                ((Value*)((char*)prop->mpValues + offset))->mpStruct = ParseProps(child);
                failed = ((Value*)((char*)prop->mpValues + offset))->mpStruct == 0;
            } else {
                return 0;
            }
            if (failed)
                return 0;
            ++found;
            offset += 0x20;
        }
        if (found != (int)prop->mCount)
            return 0;
    }

    // register every value of the property
    for (int i = 0, n2 = prop->mCount; i < n2; ++i) {
        Value* v = (Value*)((char*)prop->mpValues + i * 0x20);
        mAllValues.push_back(v);
    }
    return prop;
    }
    return 0;
}

// @ 0x0082d7b0
Prop* SerializeHelper_s0082_cd30::ParseProps(Token* tok)
{
    PropStackVector props;
    Token* child = tok->mpNext;
    int depth = tok->mDepth;
    while (child) {
        if (child->mDepth <= depth) {
            if (props.mpBegin == props.mpEnd)
                return &g_EmptyProps;
            int n = (int)(props.mpEnd - props.mpBegin);
            for (int i = 1; i < n; ++i)
                props.mpBegin[i - 1]->mpNext = props.mpBegin[i];
            return props.mpBegin[0];
        }
        if (child->mDepth == depth + 1 && child->mType == 1) {
            Prop* prop = ParseProp(child);
            if (prop == 0)
                return 0;
            if (prop->mType != 0)
                props.push_back(prop);
        }
        child = child->mpNext;
    }
    return 0;
}

// @ 0x0082d910
SerObject* SerializeHelper_s0082_cd30::ParseObject(Token* tok)
{
    if (tok->mType == 1 && wcscmp(tok->mpName, L"object") == 0) {
        SerObject* obj = NewObject();
        obj->mpClassId = GetAttribute(tok, L"clsid");
        obj->mpAttr2 = GetAttribute(tok, L"id");
        if (obj->mpClassId == 0)
            return 0;
        obj->mpProps = ParseProps(tok);
        mAllObjects.push_back(obj);
        return obj;
    }
    return 0;
}
