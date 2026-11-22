#include "game/types.h"
#include "EA/Variant.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include <string.h>

// Local Variant stand-in for the non-canonical header EA/Variant.h (module SPEngine/SPPropertyList.obj).
struct Variant {
    enum { kfInvariant = 2, kfDestruct = 4 };
    enum { kTypeInt32 = 10 };
    uint32_t data[4];
    uint16_t flags;    // 2 = invariant/typed, 4 = needs destruct
    uint16_t type;

    void __thiscall Clear(int full);                                                    // 0x93DB80
    void __thiscall Set(int type, int flags, const void* src, int elemSize, int count); // 0x93DD80

    Variant() : flags(0), type(0) {}
    void __thiscall SetBool(const bool* v);         // 0x422E20
    Variant* __thiscall SetInt(const int* v);       // 0x427FD0
    Variant* __thiscall SetFloat(const float* v);   // 0x428060
};

// ---- items of slice s00542980 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
extern wchar_t gEmptyString16[];
extern "C" __declspec(dllimport) int swscanf(const wchar_t* s, const wchar_t* fmt, ...);
#pragma intrinsic(wcscmp)
typedef unsigned int size_type;
typedef int off_type;
struct XML_ParserStruct_s0054_2980;
typedef XML_ParserStruct_s0054_2980* XML_Parser;
void* operator new(unsigned int size);
inline void* operator new(unsigned int, void* p) { return p; }
inline size_type CharStrlen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p) ++p;
    return (size_type)(p - s);
}
namespace eastl {
class allocator_s0054_2980 { public:
    allocator_s0054_2980() {}
    void deallocate(void* p, size_type) { delete[] (char*)p; }
};
}
namespace eastl {
template <typename T, typename A = allocator_s0054_2980>
struct basic_string_s0054_2980 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    basic_string_s0054_2980(const A& allocator_s0054_2980 = A()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator_s0054_2980) {
        mpBegin = (T*)gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    ~basic_string_s0054_2980() { DeallocateSelf(); }
    // 0x004237d0 (wchar_t): inline, but /Ob1 leaves it out of line; its inlined helpers'
    // locals still reserve frame slots in callers that try to inline it.
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void DoFree(T* p, size_type n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
    basic_string_s0054_2980& assign(const T* pBegin, const T* pEnd);   // 0x00423650
    basic_string_s0054_2980& operator=(const T* p) { return assign(p, p + CharStrlen(p)); }
    basic_string_s0054_2980& operator=(const basic_string_s0054_2980& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    const T* c_str() const { return mpBegin; }
    enum { npos = (size_type)-1 };
    void resize(size_type n);                                                    // 0x00429520
    basic_string_s0054_2980& erase(size_type position = 0, size_type n = npos);            // 0x004228e0
    size_type find_first_not_of(const T* p, size_type position, size_type n) const;  // 0x00547900
    size_type find_first_not_of(const T* p, size_type position = 0) const {
        return find_first_not_of(p, position, CharStrlen(p));
    }
    size_type find_last_not_of(const T* p, size_type position, size_type n) const;   // 0x00547970
    size_type find_last_not_of(const T* p, size_type position = npos) const {
        return find_last_not_of(p, position, CharStrlen(p));
    }
    basic_string_s0054_2980& sprintf(const T* pFormat, ...);           // 0x00472fe0 (char)
};
}
typedef eastl::basic_string_s0054_2980<wchar_t> string16;
typedef eastl::basic_string_s0054_2980<char> string8;
namespace EA {
template <typename T> class RefCountTemplate_s0054_2980 { public:
    RefCountTemplate_s0054_2980() : mRefCount(0) {}
    virtual ~RefCountTemplate_s0054_2980() {}
    T mRefCount;
    int AddRef() { return mRefCount++ + 1; }
    // 0x00453540: declared inline but too big for /Ob1, so it stays out of line (its
    // locals still reserve frame slots in every caller that tries to inline it).
    int Release() {
        int count = mRefCount - 1;
        mRefCount = mRefCount - 1;
        if (count)
            return count;
        mRefCount = 1;
        delete this;
        return 0;
    }
};
}
namespace EA {
template <typename T> class AutoRefCount_s0054_2980 { public:
    T* mpObject;
    AutoRefCount_s0054_2980(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0054_2980() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0054_2980& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    // 0x004e4350: stays out of line (the nested inline operator= is expanded inside it), but
    // callers still reserve frame slots for it.
    AutoRefCount_s0054_2980& operator=(const AutoRefCount_s0054_2980& x) { return operator=(x.mpObject); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T> class RefCountVTemplate_s0054_2980 {
public:
    RefCountVTemplate_s0054_2980() : mRefCount(0) {}
    virtual ~RefCountVTemplate_s0054_2980() {}
    virtual int AddRef();
    virtual int Release();
    T mRefCount;
};
}
namespace EA {
namespace IO {
enum PositionType_s0054_2980 { kPositionTypeBegin_s0054_2980, kPositionTypeCurrent_s0054_2980, kPositionTypeEnd_s0054_2980 };
}
}
namespace EA {
namespace IO {
class IStream_s0054_2980 {
public:
    virtual ~IStream_s0054_2980() {}
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual unsigned int GetType() const = 0;
    virtual int GetAccessFlags() const = 0;
    virtual int GetState() const = 0;
    virtual bool Close() = 0;
    virtual size_type GetSize() const = 0;
    virtual bool SetSize(size_type size) = 0;
    virtual off_type GetPosition(PositionType_s0054_2980 positionType = kPositionTypeBegin_s0054_2980) const = 0;
    virtual bool SetPosition(off_type position, PositionType_s0054_2980 positionType = kPositionTypeBegin_s0054_2980) = 0;
    virtual size_type GetAvailable() const = 0;
    virtual size_type Read(void* pData, size_type nSize) = 0;
    virtual bool Flush() = 0;
    virtual bool Write(const void* pData, size_type nSize) = 0;
};
}
}
namespace EA {
struct Variant_s0054_2980 {
    struct Generic { unsigned int mData[4]; };
    struct Pointer { const void* mpData; unsigned int mnSize; unsigned int mnCount; };
    enum { kFlagUnsized = 2, kFlagAllocated = 4, kFlagNoCopy = 8, kFlagPointer = 0x30 };
    union {
        Generic mGeneric;
        Pointer mPointer;
        int mInt32;
        float mFloat;
    };
    unsigned short mFlags;          // +0x10
    unsigned short mTypeId;         // +0x12

    Variant_s0054_2980() : mFlags(0), mTypeId(0) {}
    ~Variant_s0054_2980() {
        if (mFlags & kFlagAllocated)
            Destruct(false);  // 0x0093db80 (EA::Variant::Destruct)
    }
    Variant_s0054_2980& operator=(const Variant_s0054_2980& x);                          // 0x00542b80
    template <typename T> Variant_s0054_2980& operator=(const T& x);        // 0x00422eb0 <int>, 0x00428060 <float>
    void Destruct(bool bReconstruct);                              // 0x0093db80
    void Construct(const Variant_s0054_2980& x, unsigned short flags);  // 0x0093dd80 (EA::Variant::Construct)
    void Construct(unsigned short typeId, unsigned short flags, const void* pData, unsigned int nSize,
                   unsigned int nCount);                           // 0x0093dd80
};
}
namespace EA {
struct VariantCopyAssign {
    Variant_s0054_2980& Assign(const Variant_s0054_2980& x);                              // 0x00542b80
};
}
namespace SP {
namespace Feed {
struct Person_s0054_2980 : EA::RefCountTemplate_s0054_2980<int> {
    string16 mName;                 // +0x08
    unsigned __int64 mnID;          // +0x18
};
}
}
namespace SP {
namespace Feed {
struct Link {
    string16 mName;                 // +0x00
    string16 mType;                 // +0x10
    EA::Variant_s0054_2980 mValue;             // +0x20
};
}
}
namespace SP {
namespace Feed {
template <typename T> struct EntryVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned int mAllocator;
    // push_back() is inline but too big for /Ob1, so it stays out of line
    // (0x00546b70 / 0x00546800); its value_type temporary still reserves caller frame space.
    T& push_back() {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());
        return *(mpEnd - 1);
    }
    void DoInsertValue(T* position, const T& value);
    T* erase(T* position);          // 0x00546880 (Link)
    T& back() { return *(mpEnd - 1); }
};
}
}
namespace SP {
namespace Feed {
struct AtomEntry_s0054_2980 {                  // retail: 0x118 bytes
    AtomEntry_s0054_2980();
    ~AtomEntry_s0054_2980();
    string8 mID;                    // +0x00
    unsigned __int64 mnAssetID;     // +0x10
    string16 mTitle;                // +0x18
    __int64 mUpdated;               // +0x28
    __int64 mPublished;             // +0x30
    __int64 mTime38;                // +0x38
    __int64 mParentAuthorID;        // +0x40
    string16 mParentScreenName;     // +0x48
    __int64 mTime58;                // +0x58
    __int64 mOriginalAuthorID;      // +0x60
    string16 mOriginalScreenName;   // +0x68
    EntryVector<Link> mLinkList;    // +0x78
    unsigned int pad88[7];
    EA::AutoRefCount_s0054_2980<Person_s0054_2980> mpAuthor;  // +0xa4
    unsigned int padA8[9];
    unsigned int mnFlagsCC;         // +0xcc
    string16 mSummary;              // +0xd0
    unsigned int padE0[12];
    bool mbFlag110;                 // +0x110
};
}
}
namespace SP {
namespace Feed {
struct AtomDocument_s0054_2980 : EA::RefCountTemplate_s0054_2980<int> {
    string8 mID;                            // +0x08
    unsigned int mIDHash;                   // +0x18
    string16 mTitle;                        // +0x1c
    string16 mSubtitle;                     // +0x2c
    unsigned int pad3C;
    __int64 mUpdated;                       // +0x40
    unsigned int mnSubcount;                // +0x48
    EA::AutoRefCount_s0054_2980<Person_s0054_2980> mpAuthor;      // +0x4c
    unsigned int pad50[4];
    EntryVector<AtomEntry_s0054_2980> mEntryList;      // +0x60
    unsigned int pad70;
    bool mbFlag74;                          // +0x74
    string16 mText78;                       // +0x78
};
}
}
namespace SP {
namespace Feed {
class AtomParser_s0054_2980 : public EA::RefCountVTemplate_s0054_2980<int>, public EA::IO::IStream_s0054_2980 {
public:
    AtomParser_s0054_2980();
    virtual ~AtomParser_s0054_2980();
    virtual int AddRef();
    virtual int Release();
    virtual unsigned int GetType() const;
    virtual int GetAccessFlags() const;
    virtual int GetState() const;
    virtual bool Close();
    virtual size_type GetSize() const;
    virtual bool SetSize(size_type size);
    virtual off_type GetPosition(EA::IO::PositionType_s0054_2980 positionType) const;
    virtual bool SetPosition(off_type position, EA::IO::PositionType_s0054_2980 positionType);
    virtual size_type GetAvailable() const;
    virtual size_type Read(void* pData, size_type nSize);
    virtual bool Flush();
    virtual bool Write(const void* pData, size_type nSize);

    void EndLink();
    void StartParentAuthor(const wchar_t** attrs);
    void EndTime38();
    void StartOriginalAuthor(const wchar_t** attrs);
    void EndTime58();
    void EndTitle();
    void EndSubtitle();
    void EndSubcount();
    void EndFlagsCC();
    void EndName();
    void EndUserID();
    void EndId();
    void EndSummary();
    void EndUpdated();
    void EndPublished();
    void EndFlag110();
    void EndText78();
    static void SetupDict();                                                  // 0x00543f00
    static void StartElementHandler(void* ud, const wchar_t* name, const wchar_t** attrs);  // 0x00545220
    static void EndElementHandler(void* ud, const wchar_t* name);             // 0x005452b0
    static void CharacterDataHandler(void* ud, const wchar_t* s, int len);    // 0x00546600
    static bool sbDictSetup;

    XML_Parser mpXMLParser;                     // +0x0c
    string16 mCharacterData;                    // +0x10
    EA::AutoRefCount_s0054_2980<AtomDocument_s0054_2980> mpDocument;  // +0x20
    bool mbInDoc;                               // +0x24
    AtomEntry_s0054_2980* mpCurEntry;                      // +0x28
    EA::AutoRefCount_s0054_2980<Person_s0054_2980> mpCurAuthor;       // +0x2c
    Link* mpCurLink;                            // +0x30
    bool mbOpen;                                // +0x34
    int mParseStatus;                           // +0x38
    long mBitesRead;                            // +0x3c
};
}
}
// ---- items of slice s00542980 end

// ---- items of slice s00b1c8d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern int gNextStateIndex;         // 0x0167be94
#pragma intrinsic(memcpy, strlen)
void* operator new[](unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file,
                     int line);  // 0x00f473a0
#define EASTL_ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
namespace eastl {
extern char gEmptyString[];  // 0x01667bac
}
namespace eastl {
struct true_type {};
}
namespace eastl {
class allocator_s00b1_c8d0 {
public:
  allocator_s00b1_c8d0(const char* = 0) {}
  allocator_s00b1_c8d0(const allocator_s00b1_c8d0&) {}
  void* allocate(unsigned int n, int flags = 0) {
    return ::new ("Simulator", flags, 0, EASTL_ALLOC_FILE, 0xd1) char[n];
  }
  void deallocate(void* p, unsigned int) { delete[] (char*)p; }
};
}
namespace eastl {
class string {
public:
  typedef unsigned int size_type;

  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  allocator_s00b1_c8d0 mAllocator;

  string() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
  string(const char* p, const allocator_s00b1_c8d0& a = allocator_s00b1_c8d0("EASTL basic_string")) : mAllocator(a) { RangeInitialize(p); }
  ~string() { DeallocateSelf(); }

  const char* c_str() const { return mpBegin; }

  string& assign(const char* pBegin, const char* pEnd);  // 0x00454cb0
  string& assign(const char* p) { return assign(p, p + strlen(p)); }

  string& operator=(const string& x) {
    if (this != &x) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }

  void RangeInitialize(const char* pBegin, const char* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  void RangeInitialize(const char* p) { RangeInitialize(p, p + strlen(p)); }

  void AllocateSelf() {
    mpBegin = gEmptyString;
    mpEnd = gEmptyString;
    mpCapacity = gEmptyString + 1;
  }
  void AllocateSelf(size_type n) {
    if (n > 1) {
      mpBegin = DoAllocate(n);
      mpEnd = mpBegin;
      mpCapacity = mpBegin + n;
    } else
      AllocateSelf();
  }
  char* DoAllocate(size_type n) { return (char*)mAllocator.allocate(n); }
  void DoFree(char* p, size_type n) {
    if (p) mAllocator.deallocate(p, n);
  }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
  }

  static char* CharStringUninitializedCopy(const char* pSource, const char* pSourceEnd, char* pDestination) {
    memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource));
    return pDestination + (pSourceEnd - pSource);
  }
};
}
namespace eastl {
bool operator==(const string& a, const char* p);  // 0x00555020
}
namespace EA {
namespace ArgScript {
class cArguments_s00b1_c8d0 {
public:
  int NumArguments();                                                 // 0x00837f30
  const char* operator[](int i);                                      // 0x00837f20
  bool HasArgument(const char* p);                                    // 0x00837ee0
  char** OptionArguments(const char* label, int* count, int min, int max);  // 0x00838130
  char** OptionArguments(const char* label, int n);                   // 0x00838330
};
}
}
namespace EA {
namespace ArgScript {
class FormatParser {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
  virtual int ParseInt(const char* pString) const;  // +0x9c
};
}
}
using EA::ArgScript::cArguments_s00b1_c8d0;
struct RBNodeBase {
  RBNodeBase* mpNodeRight;
  RBNodeBase* mpNodeLeft;
  RBNodeBase* mpNodeParent;
  char mColor;
};
struct StringIntPair {  // eastl::pair<const eastl::string, int>
  const eastl::string first;
  int second;
  StringIntPair(const eastl::string& a, const int& b);  // 0x006a3f40
};
struct StringIntNode : RBNodeBase {
  StringIntPair mValue;  // +0x10
};
struct StringIntMap {
  struct iterator {
    StringIntNode* mpNode;
    StringIntPair* operator->() const { return &mpNode->mValue; }
    bool operator==(const iterator& x) const { return mpNode == x.mpNode; }
  };
  struct insert_return_type {
    iterator first;
    bool second;
  };

  int mDummy;
  RBNodeBase mAnchor;  // +4
  unsigned int mnSize;

  iterator end() {
    iterator it;
    it.mpNode = (StringIntNode*)&mAnchor;
    return it;
  }
  iterator find(const eastl::string& key);                                                // 0x00b20930
  insert_return_type DoInsertValue(const StringIntPair& value, eastl::true_type);           // 0x00b1aba0
  insert_return_type insert(const StringIntPair& value) { return DoInsertValue(value, eastl::true_type()); }
  int& operator[](const eastl::string& key);                                              // 0x00b1c220
};
extern StringIntMap gMessageNames;  // 0x015682ec
extern StringIntMap gMenuNames;     // 0x015680cc
extern EA::ArgScript::FormatParser* gScriptParser;  // 0x0167be98
struct StateTable {  // state-name container searched by FindState
  uint32_t mData[4];
};
int __cdecl FindState(StateTable* states, const char* name);  // 0x00b19b10
int __cdecl GetEventType(const eastl::string& s);             // 0x00b19a90
int __cdecl GetEventMessage(const eastl::string& s);          // 0x00b1a250
int __cdecl GetEventKey(const eastl::string& s);              // 0x00b19ef0
int __cdecl GetKeyModifier(const eastl::string& s);           // 0x00b19a50
int __cdecl GetObjectType(const eastl::string& s);            // 0x00b1a290
int __cdecl GetObjectFlag(const eastl::string& s);            // 0x00b19ad0
struct Transition {          // 0x38 bytes
  eastl::string mComment;    // +0x00
  int mToState;              // +0x10
  int mObjectFlags;          // +0x14
  int mMessageParam;         // +0x18
  int mEventValue;           // +0x1c
  int mObject;               // +0x20
  char mStackOp;             // +0x24
  char mPad25[3];            // +0x25
  int mEventType;            // +0x28
  int mKeyMod;               // +0x2c
  int mObjectFlagsCopy;      // +0x30 (the original stores the object flags twice)
  int mLongMouseMove;        // +0x34

  Transition() {}
  Transition(const Transition& x);  // 0x00b1a0f0
};
struct TransitionVector {  // eastl::vector<Transition> (12 bytes)
  Transition* mpBegin;     // +0x00
  Transition* mpEnd;       // +0x04
  Transition* mpCapacity;  // +0x08

  void push_back(const Transition& v) {
    if (mpEnd < mpCapacity) {
      Transition* p = mpEnd;
      mpEnd = p + 1;
      if (p) new (p) Transition(v);
    } else
      Insert(mpEnd, &v);  // 0x00b1a900
  }
  TransitionVector& operator=(const TransitionVector& x);  // 0x00b1a7b0
  void Insert(Transition* pPos, const Transition* pValue);  // 0x00b1a900
};
struct TransitionMapNode : RBNodeBase {
  int mKey;                          // +0x10
  TransitionVector mTransitions;     // +0x14
};
struct TransitionMap {
  int mDummy;            // +0x00
  RBNodeBase mAnchor;    // +0x04
  unsigned int mnSize;   // +0x14
  int mPad18;            // +0x18

  TransitionMapNode* Begin() { return (TransitionMapNode*)mAnchor.mpNodeRight; }
  TransitionMapNode* End() { return (TransitionMapNode*)&mAnchor; }

  void Find(void** pOut, const int* pKey);                  // 0x00e5c780
  TransitionMapNode* FindNode(const int& key) {
    void* pNode;
    Find(&pNode, &key);
    return (TransitionMapNode*)pNode;
  }
  TransitionVector& operator[](const int& key);             // 0x00b1c150
};
struct StateMapA {       // 0x1c bytes
  int mDummy;            // +0x00
  RBNodeBase mAnchor;    // +0x04
  unsigned int mnSize;   // +0x14
  int mPad18;            // +0x18

  StateMapA() {
    mAnchor = RBNodeBase();
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  StateMapA& operator=(const StateMapA& x);  // 0x00b1c0c0
  void FreeTree(void* pNode);                // 0x00b1b830
  ~StateMapA() { FreeTree(mAnchor.mpNodeParent); }
};
struct StateMapB {       // 0x1c bytes
  int mDummy;            // +0x00
  RBNodeBase mAnchor;    // +0x04
  unsigned int mnSize;   // +0x14
  int mPad18;            // +0x18

  StateMapB() {
    mAnchor = RBNodeBase();
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  StateMapB& operator=(const StateMapB& x);  // 0x00b1b630
  void FreeTree(void* pNode);                // 0x00e4b990
  ~StateMapB() { FreeTree(mAnchor.mpNodeParent); }
};
struct Transitions {     // 0x38 bytes
  StateMapA mPrimary;    // +0x00
  StateMapB mSecondary;  // +0x1c
};
class cStateMachineHost;
struct cStateMachineInfo {
  TransitionMap mTransitions;  // +0x00
  uint32_t mPad18;             // +0x18
  StateTable mStates;          // +0x1c
};
class cStateMachineHost {
public:
  void ParseLine(cArguments_s00b1_c8d0& args);
  void LoadStateMachine(const char* name);           // 0x00b1b410
  void DeclareState(int index, const char* name);    // 0x00b1c080
  void AddTransition(int fromState, int eventType, int keyMod, int eventValue, int object, int objectFlags,
                     int messageId, int messageParam, int toState, int longMouseMove,
                     const eastl::string& comment, int stackOp);  // 0x00b1c8d0
  void ResetAndLoad(const char* name);               // 0x00b1caa0
  void SetTransitions(const Transitions* pTransitions, int a, int b);  // 0x00b1cc00

  uint32_t pad[4];              // +0x00
  cStateMachineInfo* mpInfo;    // +0x10
  uint32_t pad14[5];            // +0x14
  Transitions mTransitions;     // +0x28
  int m60;                      // +0x60
  int m64;                      // +0x64
  uint32_t pad68[0x1d];         // +0x68
  eastl::string mName;          // +0xdc
  uint32_t padEc[4];            // +0xec
  uint32_t* mPendingBegin;      // +0xfc
  uint32_t* mPendingEnd;        // +0x100
};
// ---- items of slice s00b1c8d0 end

// @ 0x00427fd0
Variant* __thiscall Variant::SetInt(const int* v)
{
    if (flags & kfDestruct)
        Clear(1);
    if (true && (!(flags & kfInvariant) || type == kTypeInt32)) {
        *(int*)this = *v;
        type = kTypeInt32;
        flags = flags & kfInvariant;
    } else {
        Set(kTypeInt32, 0, v, 4, 1);
    }
    return this;
}

// @ 0x00542980
namespace SP { namespace Feed {
void AtomParser_s0054_2980::EndLink()
{
    if (mpCurLink) {
        ((EA::VariantCopyAssign*)&mpCurLink->mValue)->Assign(EA::Variant_s0054_2980());
        if (wcscmp(mpCurLink->mType.c_str(), L"int") == 0) {
            int value;
            if (swscanf(mCharacterData.c_str(), L"%d", &value) == 1)
                mpCurLink->mValue = value;
        } else if (wcscmp(mpCurLink->mType.c_str(), L"float") == 0) {
            float value;
            if (swscanf(mCharacterData.c_str(), L"%f", &value) == 1)
                mpCurLink->mValue = value;
        }
        if (mpCurLink->mValue.mTypeId == 0)
            mpCurEntry->mLinkList.erase(mpCurLink);
        mpCurLink = 0;
    }
}
}}  // namespace SP::Feed

// @ 0x00542b80
EA::Variant & EA::Variant::operator=(EA::Variant const & x)
{
    if (mFlags & kfDestruct)
        Destruct(true);
    if (!(x.mFlags & kfConstruct) && (!(mFlags & kfInvariant) || mTypeId == x.mTypeId)) {
        mGeneric = x.mGeneric;
        mTypeId = x.mTypeId;
        mFlags = (x.mFlags & ~kfInvariant) | (mFlags & kfInvariant);
    } else
        Construct(x, 0);
    return *this;
}

// @ 0x00542c30
namespace EA {
void Variant_s0054_2980::Construct(const Variant_s0054_2980& x, unsigned short flags)
{
    if (x.mFlags & kFlagPointer)
        Construct(x.mTypeId, x.mFlags | flags, x.mPointer.mpData, x.mPointer.mnSize, x.mPointer.mnCount);
    else
        Construct(x.mTypeId, x.mFlags | flags, &x, 0x10, 1);
}
}  // namespace EA

// @ 0x00b1cca0
void cStateMachineHost::ParseLine(cArguments_s00b1_c8d0& args)
{
  int numArgs = args.NumArguments();
  if (numArgs <= 0) return;

  eastl::string command(args[0]);

  if ((command == "IncludeMachine") && (numArgs > 1)) LoadStateMachine(args[1]);

  if (command == "DeclareState") {
    if (numArgs > 1) {
      eastl::string name(args[1]);
      DeclareState(gNextStateIndex, name.c_str());
      ++gNextStateIndex;
    }
  } else if (command == "DeclareMessage") {
    if (numArgs > 2) {
      int id = gScriptParser->ParseInt(args[2]);
      eastl::string name(args[1]);
      gMessageNames.insert(StringIntPair(name, id));
    }
  } else if (command == "DeclareMenu") {
    if (numArgs > 2) {
      int id = gScriptParser->ParseInt(args[2]);
      gMenuNames[args[1]] = id;
    }
  }

  if (command == "AddTransition") {
    int count;
    char** p;

    int fromState = -1;
    p = args.OptionArguments("FromState", 1);
    if (p) fromState = FindState(&mpInfo->mStates, p[0]);

    eastl::string comment;
    p = args.OptionArguments("Comment", 1);
    if (p) comment.assign(p[0]);

    int toState = -2;
    p = args.OptionArguments("ToState", 1);
    if (p) toState = FindState(&mpInfo->mStates, p[0]);

    int eventType = 12;
    int eventValue = -1;
    p = args.OptionArguments("Event", &count, 1, 2);
    int eventMessage = 0;
    if (p) {
      eastl::string eventName(p[0]);
      eventType = GetEventType(eventName);
      if (count > 1) {
        eastl::string valueName(p[1]);
        if (eventType == 9)
          eventValue = eventMessage = GetEventMessage(valueName);
        else
          eventValue = GetEventKey(valueName);
      }
    }

    int keyMod = 0;
    p = args.OptionArguments("KeyMod", &count, 1, 4);
    if (p) {
      do {
        --count;
        eastl::string modName(p[count]);
        keyMod |= GetKeyModifier(modName);
      } while (count > 0);
    }

    int object = -1;
    p = args.OptionArguments("Object", 1);
    if (p) {
      eastl::string objectName(p[0]);
      object = GetObjectType(objectName);
    }

    int objectFlags = 0;
    p = args.OptionArguments("ObjectFlags", &count, 1, 4);
    if (p) {
      for (int i = 0; i < count; ++i) {
        eastl::string flagName(p[i]);
        objectFlags |= GetObjectFlag(flagName);
      }
    }

    int longMouseMove = 0;
    p = args.OptionArguments("LongMouseMove", &count, 1, 0x7fffffff);
    if (p) longMouseMove = gScriptParser->ParseInt(p[0]);

    int messageId = 0;
    int messageParam = 666;
    p = args.OptionArguments("Message", &count, 1, 2);
    if (p) {
      eastl::string messageName(p[0]);
      StringIntMap::iterator it = gMessageNames.find(messageName);
      if (it == gMessageNames.end()) goto done;  // unknown message: no transition
      messageId = it->second;
      if (count > 1)
        messageParam = gScriptParser->ParseInt(p[1]);
      else if (eventType == 9)
        messageParam = eventMessage;
    }

    if (args.HasArgument("Push")) {
      args.OptionArguments("Push", 0);
      AddTransition(fromState, eventType, keyMod, eventValue, object, objectFlags, messageId, messageParam, toState,
                    longMouseMove, comment, 1);
    } else if (args.HasArgument("Pop")) {
      args.OptionArguments("Pop", 0);
      AddTransition(fromState, eventType, keyMod, eventValue, object, objectFlags, messageId, messageParam, -3,
                    longMouseMove, comment, 0);
    } else {
      AddTransition(fromState, eventType, keyMod, eventValue, object, objectFlags, messageId, messageParam, toState,
                    longMouseMove, comment, 0);
    }
  done:;
  }
}
