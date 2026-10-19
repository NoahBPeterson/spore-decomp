// src/game/UTFSpore_Win32/XmlDeserializer.cpp -- migrated from slice(s) s0099afe0, s0099a050, s0082cd30 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/XmlDeserializer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/StackAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#include <new>
#include <wchar.h>
#include "EA/UTFWinTools/IDataBinder.h"
#include "EA/UTFWinTools/SerCollection.h"
#pragma intrinsic(wcscmp)

// ---- items of slice s0082cd30 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct Bookmark {
    Bookmark* mpPrev;       // +0x00
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
    Bookmark* mpTopBookmark;    // +0x20
    void AllocateNewBlock(int flags);                       // @ 0x82B0D0
    void FreeToBlock(char* address);                        // @ 0x928C40
    // Pop the top bookmark (the inlined tail used when parsing ends without a fatal error).
    bool PopBookmark()
    {
        Bookmark* bm = mpTopBookmark;
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
struct AllocVBase { virtual void a0(); };
struct TempAllocator : AllocVBase, StackAllocator {};
struct ImageBinder {                                        // cSPUIImageToTextureBinder (embedded at +0x264)
    virtual void b00(); virtual void b04(); virtual void b08(); virtual void b0C();
    virtual void Bind(void* desc, int kind, void* key);    // +0x10
    virtual void End();                                    // +0x14
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
struct XmlDeserializer {
    virtual uint32_t Read(IStream* stream, int a1, void* output, int a3, int a4, int a5);   // @ 0x99BE60
};
struct cSPUIDeserializer : XmlDeserializer {
    virtual uint32_t Read(IStream* stream, int a1, void* output, int a3, int a4, int a5);
};
// ---- items of slice s0082cd30 end

// ---- items of slice s0099a050 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWinTools {
namespace UTFWinToolsInternal {
struct StackAllocator_s0099_a050 {
    void* MallocAligned(void* a, void* b, int zero, int one);  // 0x928d40
    bool  AllocateNewBlock(int size);                          // 0x928ba0
};
}
}
}
namespace EA {
namespace UTFWinTools {
namespace UTFWinToolsInternal {
struct XmlObj094 {
    virtual void pv00(); virtual void pv01(); virtual void pv02(); virtual void pv03();
    virtual void* v10(void* a);          // +0x10
    virtual void* v14(void* a);          // +0x14
    void* FUN_0113ae10(void* r);         // 0x113ae10
};
}
}
}
namespace EA {
namespace UTFWinTools {
namespace UTFWinToolsInternal {
struct XmlReaderState {
    // 0x99a920
    void Allocate(void* param_2, void* param_3);
    // 0x99a940
    void* StrDup(const wchar_t* s);
    // 0x99a470
    void  ReportResult(void* param_2);
    // 0x99a9d0
    void  Splice(void* param_2);
    // large entry points (partial)
    unsigned ReadObjectArray(int param_2);                                  // 0x99a4c0
    unsigned ReadStructArray(int* param_2, unsigned param_3);               // 0x99a7c0
    unsigned ParsePropertyValue(double* param_2, unsigned param_3, wchar_t* param_4);  // 0x99aa20
    unsigned ReadPropertyValueArray(void* param_2);                         // 0x99ac80
};
}
}
}
// ---- items of slice s0099a050 end

// ---- items of slice s0099afe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
extern void FUN_f47380(void*);     // operator delete(void*)
extern "C" void* __cdecl MemSetThunk(void* p, int v, unsigned n);   // 0x011e073e
extern "C" void* __cdecl FormatPos(const void* p);       // 0x0113ae10
extern "C" int  __cdecl ParseTypeName(const wchar_t* s);             // 0x0099a380
struct RefObj {
  virtual void r0();
  virtual void Release();
};
struct S962100b { int* op(void*); };        // eastl hash_map<unsigned,AutoRefCount<...>>::operator[]
struct S693230 { void f(void*, unsigned); }; // hashtable bucket dealloc/copy helper
struct S620230b { void f(); };               // intrusive_list_base::~intrusive_list_base
struct S928dc0 { void f(); };                // allocator reset
struct S928cd0 {
  void init(int, int, int, int, int);   // 0x00928cd0 StackAllocator::StackAllocator
};
struct S928b00 {
  void init(int, int, int, int, int);   // 0x00928b00 StackAllocator::Init
};
struct S99b5a0 { void f(int, int); };
struct S99b5e0 { void f(); };
struct S99b660 { S99b660* f(int, int, int, int, int); };
struct XmlReaderState_s0099_afe0;
struct SerItem;
struct PropInfo {                                        // SerPropertyInfo
  char pad[0xc];
  uint16_t flags;                                        // +0xc: low 12 bits = type bits, bit 15 = variable count
  uint16_t pad2;
  uint32_t count;                                        // +0x14 fixed element count
  bool Commit(SerItem* base, SerItem* value, XmlReaderState_s0099_afe0* st);                                  // 0x0095dda0
  bool Build(SerItem* out, SerItem* base, uint32_t count, XmlReaderState_s0099_afe0* st, int flag);           // 0x0095dbd0
};
struct SerItem {
  uint32_t w[3];
  PropInfo* FindProp(SerItem* out, uint32_t id, XmlReaderState_s0099_afe0* st);                               // 0x0095dd00
};
struct ResKey { uint32_t a, b, c; };
struct HandlerItem : SerItem { uint32_t extra; };
struct INode { INode* next; INode* prev; };              // eastl::intrusive_list_node
struct IList {
  INode anchor;
  IList() { anchor.next = &anchor; anchor.prev = &anchor; }
  ~IList() {
    INode* n = anchor.next;
    while (n != &anchor) { INode* nx = n->next; n->prev = 0; n->next = 0; n = nx; }
  }
};
struct LazyReference {
  INode node;                // +0
  INode children;            // +8
  SerItem base;              // +0x10
  SerItem value;             // +0x1c
  PropInfo* prop;            // +0x28
  uint32_t* ids;             // +0x2c
  uint32_t count;            // +0x30
  char pad[4];
};
struct StackAlloc {          // EA::Allocator::StackAllocator (tail of the object)
  char pad[4];
  char* blk;                 // +4
  char* blkEnd;              // +8
  char* objBegin;            // +0xc
  char* objEnd;              // +0x10
  bool AllocateNewBlock(unsigned n);   // 0x00928ba0
  void Free(void* p);                  // 0x00928c40
  void Reset();                        // 0x00928dc0
};
struct IUnknown32_s0099_afe0 {
  virtual void AddRef();
  virtual void Release();
  virtual void v2();
  virtual IUnknown32_s0099_afe0* QueryInterface(uint32_t iid);      // +0xc
  virtual void GetInfo(void* out);                       // +0x10
};
struct ClassInfo { char pad[0x1c]; void (__cdecl* onLoaded)(void*); };
struct InfoOut { ClassInfo* info; void* ctx; uint32_t x2; uint32_t x3; };
struct IDataBinder {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual bool BindKey(SerItem* out, int typeCode, ResKey* key);   // +0x10
  virtual void Done();                                             // +0x14
  virtual bool GetHandler(uint32_t handler, SerItem* out);         // +0x18
};
struct BinderVec { IDataBinder** begin; IDataBinder** end; };
struct IReader {
  virtual void v0(); virtual void v1();
  virtual bool Open(void* stream, void* arg);            // +8
  virtual bool Next();                                   // +0xc
  virtual const void* GetPos(void* ctx);                 // +0x10
  virtual void* GetLine(const void* pos);                // +0x14 (ctx -> pos)
  const wchar_t* GetAttribute(const wchar_t* name);      // 0x00900720
  int            GetNodeType();                          // 0x00900660  (1 = element, 2 = end element)
  const wchar_t* GetName();                              // 0x00900690
  void           EndElement();                           // 0x009007b0
  uint32_t       GetErrorCode();                         // 0x00fcc210
};
extern "C" bool __cdecl ReadResKey(const wchar_t* s, ResKey* key);   // 0x008de0c0
struct HNode { uint32_t key; void* value; HNode* next; };
struct HFind {
  void find(HNode** out, const uint32_t* key);   // 0x00645ed0 (hashtable<uint,pair<uint,int>>::find)
};
struct HMap { char pad[4]; HNode** buckets; uint32_t nbuckets; uint32_t count; };   // +4 buckets, +8 bucket count, +0xc count
struct SerCollection_s0099_afe0 {
  char pad[0x1c];
  HMap idMap;                                            // +0x1c
  char pad2[0x3c - 0x1c - sizeof(HMap)];
  void RemoveAll();                                      // 0x00999000
  bool Check(int n);                                     // 0x00998fb0
  void Add(IUnknown32_s0099_afe0* obj);                             // 0x00998fc0
};
struct FactoryMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual IUnknown32_s0099_afe0* Create(uint32_t clsid, uint32_t iid, int a, int b); };            // +0x20
FactoryMgr* GetFactoryMgr();                                                            // 0x00920090
struct HMapOps {
  IUnknown32_s0099_afe0** op(const uint32_t* key);   // 0x00975d40 operator[]
};
struct CollMapAssign {
  void f(uint32_t key, IUnknown32_s0099_afe0* obj);   // 0x0099b5a0
};
struct XmlReaderState_s0099_afe0 {
  const void* vptr;                                      // +0
  char allocA[0x24];                                     // +4   StackAllocator mAllocator
  char allocB[0x24];                                     // +0x28 StackAllocator mTempAllocator
  void (__cdecl* mErrorCallback)(uint32_t, void*);       // +0x4c
  void* mpCallbackContext;                               // +0x50
  uint32_t mNextTempID;                                  // +0x54
  uint32_t mResult;                                      // +0x58
  IList mLazyReferences;                                 // +0x5c
  HMap mObjectMap;                                       // +0x64 (+0x68 buckets, +0x6c bucket count, +0x70 count)
  char pad2[0x84 - 0x64 - sizeof(HMap)];
  SerCollection_s0099_afe0* mCollection;                            // +0x84
  BinderVec* mBinders;                                   // +0x88
  void* mImports;                                        // +0x8c
  void* mExports;                                        // +0x90
  IReader* mReader;                                      // +0x94

  StackAlloc* Temp() { return (StackAlloc*)((char*)this + 0x28); }
  StackAlloc* Pool() { return (StackAlloc*)((char*)this + 4); }

  void Report(uint32_t code);                                       // 0x0099a470
  bool CheckType(int typeCode, unsigned propBits);                  // 0x0099a3f0
  bool ReadObjectArray(LazyReference* ref);                         // 0x0099a4c0
  bool ReadStructArray(SerItem* val, IList* out);                   // 0x0099a7c0
  bool ReadPropertyValueArray(SerItem* val);                        // 0x0099ac80
  bool ParsePropertyValue(uint32_t v, int typeCode, const wchar_t* s); // 0x0099aa20
  void MoveChildren(IList* from, INode* to);                        // 0x0099a9d0 (thiscall on the list)

  bool Fixup(IList* list);                                          // 0x0099afe0
  LazyReference* CreateLazyReference(SerItem* base, PropInfo* prop, SerItem* value, int count); // 0x0099b110
  bool ReadProperty(SerItem* base, LazyReference** outRef);         // 0x0099b1f0
  bool ReadPropertyList(SerItem* base, IList* list);                // 0x0099b730
  IUnknown32_s0099_afe0* ReadObject(uint32_t* outId);                          // 0x0099b8a0
  bool ReadBindings();                                              // 0x0099b9e0
  bool ReadGraph();                                                 // 0x0099bac0
  uint32_t Read();                                                  // 0x0099bc00
};
bool XmlReaderState_s0099_afe0::ReadProperty(SerItem* base, LazyReference** outRef)
{
  const wchar_t* propid = mReader->GetAttribute(L"propid");
  const wchar_t* typeStr = mReader->GetAttribute(L"type");
  const wchar_t* valueStr = mReader->GetAttribute(L"value");
  const wchar_t* countStr = mReader->GetAttribute(L"count");
  const wchar_t* keyStr = mReader->GetAttribute(L"key");
  if (propid == 0) { Report(0x2fc50003); return false; }
  int typeCode = 0;
  if (typeStr == 0 || (typeCode = ParseTypeName(typeStr)) == 0) { Report(0x2fc50004); return false; }
  SerItem prop;
  PropInfo* info = base->FindProp(&prop, wcstoul(propid, 0, 0), this);
  if (info) {
    if (!CheckType(typeCode, info->flags & 0xfff)) {
      Report(0x2fc50005);
    } else {
      uint32_t count = countStr ? wcstoul(countStr, 0, 0) : 1;
      if (!((info->flags >> 15) & 1) && count != info->count) {
        Report(0x2fc50007);
      } else {
        SerItem val;
        if (!info->Build(&val, &prop, count, this, 0)) {
          Report(3);
          return false;
        }
        if (typeCode == 0x13) {
          LazyReference* lr = CreateLazyReference(&prop, info, &val, count);
          *outRef = lr;
          if (!ReadObjectArray(lr))
            return false;
          goto done;
        }
        if (typeCode == 0x14) {
          IList list;
          if (!ReadStructArray(&val, &list))
            return false;
          if (list.anchor.prev == &list.anchor) {
            if (!info->Commit(&prop, &val, this)) {
              Report(0x2fc5000a);
              mReader->EndElement();
              return true;
            }
          } else {
            LazyReference* lr = CreateLazyReference(base, info, &val, 0);
            *outRef = lr;
            MoveChildren(&list, &lr->children);
          }
          mReader->EndElement();
          return true;
        }
        if (countStr != 0) {
          if (!ReadPropertyValueArray(&val))
            return false;
        } else if (keyStr != 0) {
          ResKey key = { 0, 0, 0 };
          if (ReadResKey(keyStr, &key)) {
            IDataBinder** it = mBinders->begin;
            for (; it != mBinders->end; ++it) {
              if ((*it)->BindKey(&val, typeCode, &key))
                goto commit;
            }
            Report(0x2fc50009);
          }
        } else if (valueStr != 0) {
          if (!ParsePropertyValue(val.w[1], typeCode, valueStr))
            return false;
        }
      commit:
        if (!info->Commit(&prop, &val, this))
          Report(0x2fc5000a);
      }
    }
  }
done:
  mReader->EndElement();
  return true;
}
struct IStreamX {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
  virtual int  GetPosition(int mode);              // +0x24
  virtual bool SetPosition(int pos, int mode);     // +0x28
  virtual void v11();
  virtual int  Read(void* buf, int n);             // +0x30
};
struct XmlTextReader  : IReader { char body[0x88 - 4]; XmlTextReader(int);  ~XmlTextReader(); };   // 0x00900b30 / 0x00900b70
struct XmlTokenReader : IReader { char body[0xa4 - 4]; XmlTokenReader(int); ~XmlTokenReader(); };  // 0x009031a0 / 0x009031d0
struct XmlReaderStateObj : XmlReaderState_s0099_afe0 {
  XmlReaderStateObj(IReader* r, SerCollection_s0099_afe0* c, BinderVec* b, void* cb, void* ctx);   // 0x0099b660
  ~XmlReaderStateObj();                                                                  // 0x0099b5e0
};
// ---- items of slice s0099afe0 end

// @ 0x0082d9f0
uint32_t cSPUIDeserializer::Read(IStream* stream, int a1, void* output, int a3, int a4, int a5)
{
    int pos = stream->GetPosition(0);
    uint32_t magic = 0;
    if (stream->Read(&magic, 4) == 4 && magic == 0xE3FE3FB8) {
        stream->SetPosition(pos, 0);
        DeserializeHelper helper(stream, output);       // 0x274 bytes on the stack
        if (!helper.ProcessStream())
            return 0x2FC50006;
        return 0;
    }
    stream->SetPosition(pos, 0);
    return XmlDeserializer::Read(stream, a1, output, a3, a4, a5);
}

// @ 0x0099a3f0
namespace EA { namespace UTFWinTools { namespace UTFWinToolsInternal {
bool __fastcall FUN_0099a3f0(unsigned param_1, unsigned param_2)
{
    switch (param_1) {
    case 3:
    case 7:
        return param_2 == 3 || param_2 == 7;
    case 4:
    case 8:
        return param_2 == 4 || param_2 == 8;
    case 5:
    case 9:
        return param_2 == 5 || param_2 == 9;
    case 0x3fd:
    case 0x3fe:
    case 0x3ff:
        return param_2 == 0x13;
    default:
        return param_1 == param_2;
    }
}
}}}  // namespace EA::UTFWinTools::UTFWinToolsInternal

// @ 0x0099a470
namespace EA { namespace UTFWinTools { namespace UTFWinToolsInternal {
void XmlReaderState::ReportResult(void* param_2)
{
    *(void**)((char*)this + 0x58) = param_2;
    if (*(void**)((char*)this + 0x4c) != 0) {
        XmlObj094* p = *(XmlObj094**)((char*)this + 0x94);
        void* r = p->v14(*(void**)((char*)this + 0x50));
        r = p->v10(r);
        r = (*(XmlObj094**)((char*)this + 0x94))->FUN_0113ae10(r);
        void* f = *(void**)((char*)this + 0x4c);
        ((void(__cdecl*)(void*, void*))f)(*(void**)((char*)this + 0x58), r);
    }
}
}}}  // namespace EA::UTFWinTools::UTFWinToolsInternal

// @ 0x0099a4c0
namespace EA { namespace UTFWinTools { namespace UTFWinToolsInternal {
unsigned XmlReaderState::ReadObjectArray(int)
{
    return 0;
}
}}}  // namespace EA::UTFWinTools::UTFWinToolsInternal

// @ 0x0099a7c0
namespace EA { namespace UTFWinTools { namespace UTFWinToolsInternal {
unsigned XmlReaderState::ReadStructArray(int*, unsigned)
{
    return 0;
}
}}}  // namespace EA::UTFWinTools::UTFWinToolsInternal

// @ 0x0099a920
namespace EA { namespace UTFWinTools { namespace UTFWinToolsInternal {
void XmlReaderState::Allocate(void* param_2, void* param_3)
{
    ((StackAllocator_s0099_a050*)((char*)this + 0x28))->MallocAligned(param_2, param_3, 0, 1);
}
}}}  // namespace EA::UTFWinTools::UTFWinToolsInternal

// @ 0x0099a940
namespace EA { namespace UTFWinTools { namespace UTFWinToolsInternal {
void* XmlReaderState::StrDup(const wchar_t* s)
{
    const wchar_t* p = s;
    const wchar_t* q = s + 1;
    while (*p++) {
    }
    int n = (int)(p - q);
    unsigned size = ((unsigned)(n * 2 + 9)) & 0xfffffff8u;

    char* base = (char*)this + 4;
    if ((int)(*(int*)((char*)this + 0x0c) - (int)size - *(int*)(base + 0x0c)) < 0) {
        if (!((StackAllocator_s0099_a050*)base)->AllocateNewBlock((int)size))
            return 0;
    }
    char* dst = *(char**)(base + 0x0c);
    char* newEnd = dst + size;
    *(char**)(base + 0x0c) = newEnd;
    *(char**)(base + 0x10) = newEnd;

    const wchar_t* r = s;
    wchar_t* out = (wchar_t*)dst;
    wchar_t c;
    do {
        c = *r++;
        *out++ = c;
    } while (c != 0);
    return dst;
}
}}}  // namespace EA::UTFWinTools::UTFWinToolsInternal

// @ 0x0099a9d0
namespace EA { namespace UTFWinTools { namespace UTFWinToolsInternal {
void XmlReaderState::Splice(void* param_2)
{
    void** a = (void**)this;
    void** b = (void**)param_2;
    void* iVar1 = a[0];
    void* iVar2 = a[1];
    a[0] = b[0];
    a[1] = b[1];
    b[1] = iVar2;
    b[0] = iVar1;
    if (a[0] == (void*)b) {
        a[1] = (void*)a;
        a[0] = (void*)a;
    } else {
        *(void**)a[1] = (void*)a;
        *(void**)((char*)a[0] + 4) = (void*)a;
    }
    if (b[0] == (void*)a) {
        b[1] = (void*)b;
        b[0] = (void*)b;
        return;
    }
    *(void**)b[1] = (void*)b;
    *(void**)((char*)b[0] + 4) = (void*)b;
}
}}}  // namespace EA::UTFWinTools::UTFWinToolsInternal

// @ 0x0099aa20
namespace EA { namespace UTFWinTools { namespace UTFWinToolsInternal {
unsigned XmlReaderState::ParsePropertyValue(double*, unsigned, wchar_t*)
{
    return 0;
}
}}}  // namespace EA::UTFWinTools::UTFWinToolsInternal

// @ 0x0099ac80
namespace EA { namespace UTFWinTools { namespace UTFWinToolsInternal {
unsigned XmlReaderState::ReadPropertyValueArray(void*)
{
    return 0;
}
}}}  // namespace EA::UTFWinTools::UTFWinToolsInternal

// @ 0x0099afe0
bool XmlReaderState_s0099_afe0::Fixup(IList* list)
{
  INode* anchor = &list->anchor;
  for (INode* n = anchor->next; n != anchor; n = n->next) {
    LazyReference* lr = (LazyReference*)n;
    if (lr->children.prev != &lr->children)
      Fixup((IList*)&lr->children);
    if (lr->prop != 0) {
      uint32_t count = lr->count;
      if (count != 0) {
        uint32_t* out = (uint32_t*)lr->value.w[1];
        uint32_t i = 0;
        do {
          uint32_t key = lr->ids[i];
          void* v = 0;
          if (key != 0) {
            HNode* it;
            ((HFind*)&mObjectMap)->find(&it, &key);
            if (it == mObjectMap.buckets[mObjectMap.nbuckets]) {
              HMap* m = &mCollection->idMap;
              HNode* it2;
              ((HFind*)m)->find(&it2, &key);
              if (it2 == m->buckets[m->nbuckets])
                v = 0;
              else
                v = it2->value;
            } else {
              v = it->value;
            }
          }
          *out = (uint32_t)v;
          out++;
          i++;
        } while (i < count);
      }
      lr->prop->Commit(&lr->base, &lr->value, this);
    }
  }
  return true;
}

// @ 0x0099b110
LazyReference* XmlReaderState_s0099_afe0::CreateLazyReference(SerItem* base, PropInfo* prop, SerItem* value, int count)
{
  StackAlloc* pool = Pool();
  LazyReference* obj;
  if ((int)(pool->blkEnd - pool->objBegin - 0x38) < 0) {
    if (pool->AllocateNewBlock(0x38))
      goto alloc_ok;
  } else {
  alloc_ok:
    char* mem = pool->objBegin;
    pool->objBegin = mem + 0x38;
    pool->objEnd = mem + 0x38;
    obj = (LazyReference*)mem;
    if (obj) {
      obj->node.prev = 0;
      obj->node.next = 0;
      obj->children.prev = &obj->children;
      obj->children.next = &obj->children;
      goto have_obj;
    }
  }
  obj = 0;
have_obj:
  obj->base = *base;
  obj->prop = prop;
  obj->value = *value;
  obj->count = count;
  if (count != 0) {
    unsigned bytes = count * 4;
    unsigned rounded = (bytes + 7) & ~7u;
    if ((int)(pool->blkEnd - pool->objBegin - rounded) < 0) {
      if (!pool->AllocateNewBlock(rounded)) {
        obj->ids = 0;
        return obj;
      }
    }
    char* mem = pool->objBegin;
    pool->objBegin = mem + rounded;
    pool->objEnd = mem + rounded;
    if (mem)
      MemSetThunk(mem, 0, bytes);
    obj->ids = (uint32_t*)mem;
  }
  return obj;
}

// @ 0x0099b1f0
static inline void ReleaseTemp(StackAlloc* a, char* p)
{
  if (p > a->blk && p < a->blkEnd) { a->objBegin = p; a->objEnd = p; }
  else a->Free(p);
}

// @ 0x0099b5a0
void S99b5a0::f(int key, int obj)
{
  int* slot = ((S962100b*)this)->op(&key);
  int old = *slot;
  if (obj != old) {
    if (obj) ((RefObj*)(size_t)obj)->r0();
    *slot = obj;
    if (old) ((RefObj*)(size_t)old)->Release();
  }
}

// @ 0x0099b5e0
void S99b5e0::f()
{
  char* self = (char*)this;
  char* ht = self + 0x64;
  *(int*)self = (int)0x1446c44;
  ((S693230*)ht)->f(*(void**)(ht + 4), *(unsigned*)(ht + 8));
  *(int*)(ht + 0xc) = 0;
  if (*(unsigned*)(ht + 8) > 1) FUN_f47380(*(void**)(ht + 4));
  ((S620230b*)(self + 0x5c))->f();
  ((S928dc0*)(self + 0x28))->f();
  ((S928dc0*)(self + 4))->f();
  *(int*)self = (int)0x14613b8;
}

// @ 0x0099b660
S99b660* S99b660::f(int a, int b, int c, int d, int e)
{
  char* self = (char*)this;
  *(int*)self = (int)0x1446c44;
  ((S928cd0*)(self + 4))->init(0, -1, 0, 0, 0);
  ((S928cd0*)(self + 0x28))->init(0, -1, 0, 0, 0);
  *(int*)(self + 0x4c) = d;
  *(int*)(self + 0x50) = e;
  *(int*)(self + 0x54) = (int)0xef54054c;
  *(int*)(self + 0x58) = 0;
  *(int*)(self + 0x60) = (int)(self + 0x5c);
  *(int*)(self + 0x5c) = (int)(self + 0x5c);
  *(int*)(self + 0x74) = 0x3f800000;
  *(int*)(self + 0x78) = 0x40000000;
  *(int*)(self + 0x6c) = 1;
  *(int*)(self + 0x68) = (int)0x154df28;
  *(int*)(self + 0x70) = 0;
  *(int*)(self + 0x7c) = 0;
  *(int*)(self + 0x94) = a;
  *(int*)(self + 0x84) = b;
  *(int*)(self + 0x88) = c;
  *(int*)(self + 0x8c) = 0;
  *(int*)(self + 0x90) = 0;
  ((S928b00*)(self + 0x28))->init(0, 0, 0, 0, 0);
  ((S928b00*)(self + 4))->init(0, 0, 0, 0, 0);
  return this;
}

// @ 0x0099b730
bool XmlReaderState_s0099_afe0::ReadPropertyList(SerItem* base, IList* list)
{
  INode* head = &list->anchor;
  if (!mReader->Next()) {
    Report(mReader->GetErrorCode());
    return false;
  }
  for (;;) {
    int t = mReader->GetNodeType();
    if (t == 1) {
      if (wcscmp(mReader->GetName(), L"prop") != 0) {
        Report(0x2fc50001);
        return false;
      }
      char* mark = Temp()->objBegin;
      LazyReference* ref = 0;
      if (!ReadProperty(base, &ref)) {
        ReleaseTemp(Temp(), mark);
        return false;
      }
      if (ref) {
        ref->node.prev = head->prev;
        ref->node.next = head;
        head->prev = &ref->node;
        ref->node.prev->next = &ref->node;
      } else {
        ReleaseTemp(Temp(), mark);
      }
    } else {
      if (mReader->GetNodeType() == 2)
        return true;
      if (!mReader->Next()) {
        Report(mReader->GetErrorCode());
        return false;
      }
    }
  }
}

// @ 0x0099b8a0
IUnknown32_s0099_afe0* XmlReaderState_s0099_afe0::ReadObject(uint32_t* outId)
{
  const wchar_t* idStr = mReader->GetAttribute(L"id");
  const wchar_t* clsidStr = mReader->GetAttribute(L"clsid");
  if (clsidStr == 0) {
    Report(0x2fc50002);
    return 0;
  }
  uint32_t clsid = wcstoul(clsidStr, 0, 0);
  IUnknown32_s0099_afe0* obj = GetFactoryMgr()->Create(clsid, 0xee3f516e, 0, 0);
  if (obj == 0) {
    Report(0x2fc50002);
    return 0;
  }
  if (idStr != 0) {
    *outId = wcstoul(idStr, 0, 0);
    if (*outId != 0) {
      if (*outId + 0x10000 > 0x7fff && mCollection->Check(2))
        ((CollMapAssign*)((char*)mCollection + 0x3c))->f(*outId, obj);
      goto map_it;
    }
  } else {
    *outId = mNextTempID;
    mNextTempID++;
  map_it:
    if (*outId != 0)
      *((HMapOps*)((char*)this + 0x64))->op(outId) = obj;
  }
  obj->AddRef();
  {
    IUnknown32_s0099_afe0* iface = obj->QueryInterface(0xeec58382);
    if (iface) {
      InfoOut io;
      iface->GetInfo(&io);
      if (!ReadPropertyList((SerItem*)&io, &mLazyReferences)) {
        Report(0x2fc50002);
        return 0;
      }
    }
  }
  return obj;
}

// @ 0x0099b9e0
bool XmlReaderState_s0099_afe0::ReadBindings()
{
  const wchar_t* handlerStr = mReader->GetAttribute(L"handler");
  if (handlerStr == 0) {
    Report(0x2fc50008);
    return false;
  }
  uint32_t handler = wcstoul(handlerStr, 0, 0);
  HandlerItem item;
  for (IDataBinder** it = mBinders->begin; it != mBinders->end; ++it) {
    if ((*it)->GetHandler(handler, &item))
      return ReadPropertyList(&item, &mLazyReferences);
  }
  mResult = 0x2fc50008;
  if (mErrorCallback) {
    IReader* r = mReader;
    void* line = r->GetLine(mpCallbackContext);
    const void* pos = r->GetPos(line);
    mErrorCallback(mResult, FormatPos(pos));
  }
  return false;
}

// @ 0x0099bac0
bool XmlReaderState_s0099_afe0::ReadGraph()
{
  while (mReader->Next()) {
    if (mReader->GetNodeType() == 1) {
      if (wcscmp(mReader->GetName(), L"object") == 0) {
        uint32_t id = 0;
        IUnknown32_s0099_afe0* obj = ReadObject(&id);
        if (!obj)
          return false;
        mCollection->Add(obj);
      } else {
        if (wcscmp(mReader->GetName(), L"prologue") != 0) {
          Report(0x2fc50001);
          return false;
        }
        if (!ReadBindings())
          return false;
      }
    } else {
      if (mReader->GetNodeType() == 2)
        return true;
    }
  }
  Report(mReader->GetErrorCode());
  return false;
}

// @ 0x0099be60
uint32_t __stdcall XmlDeserializerRead(IStreamX* stream, void* arg2, SerCollection_s0099_afe0* coll, BinderVec* binders, void* cb, void* ctx)
{
  XmlTextReader text(0);
  XmlTokenReader token(0);
  IReader* reader = &text;
  int pos = stream->GetPosition(0);
  uint32_t magic = 0xffff;
  if (stream->Read(&magic, 2) == -1)
    return 0;
  if ((uint16_t)magic == 0)
    reader = &token;
  stream->SetPosition(pos, 0);
  uint32_t result = 0;
  if (reader->Open(stream, arg2)) {
    XmlReaderStateObj st(reader, coll, binders, cb, ctx);
    result = st.Read();
  }
  return result;
}
