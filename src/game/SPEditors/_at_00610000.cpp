// src/game/SPEditors/_at_00610000.cpp -- migrated from slice(s) s0061fbd0, s0061ecf0, s0061e250, s0061d240 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00610000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include "SP/cPollinator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"
#include "EA/DateTime/DateTime.h"
#include "SP/cJob.h"
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(strlen)
#pragma intrinsic(memmove)

// ---- items of slice s0061d240 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Pollen {
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void*);
}
}
namespace SP {
namespace Pollen {
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void*);
}
}
namespace SP {
namespace Pollen {
struct GuardedFlag {
  char pad0[0x48];
  uint32_t mCriticalSection[6];  // +0x48 (CRITICAL_SECTION, 0x18 bytes)
  char pad1[0x68 - 0x60];
  bool mbFlag;  // +0x68
  bool Get() const;
};
}
}
namespace SP {
namespace Pollen {
void PollenNotifyHelper(void* self);
}
}
namespace SP {
namespace Pollen {
void* PollenHelper311(void* self, void* a, void* b);
}
}
namespace SP {
namespace Pollen {
void* PollenCtor78(void* self, void* a, void* b);
}
}
// ---- items of slice s0061d240 end

// ---- items of slice s0061e250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" unsigned int __cdecl wcslen(const wchar_t*);
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void*);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void*);
extern "C" __declspec(dllimport) void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" char V_13ef094[];
extern "C" char V_13fcab8[];
extern "C" char V_13fcabc[];
extern "C" char V_13fcac4[];
extern "C" char V_13eb394[];
extern "C" char V_13eb938[];
extern wchar_t gEmptyStringW[];  // 0x01667bac
extern "C" void F_93c440(void* dst, const wchar_t* first, int last);  // cdecl, 3 args
#pragma intrinsic(strlen, wcslen, wcscmp)
#define PV(n) virtual void pv##n();
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
struct ICoreAllocator;
void* operator new(unsigned int size, int alignment, const char* name, ICoreAllocator* pAllocator);
namespace eastl {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
}
namespace EA {
namespace Messaging {
class IHandler_s0061_e250 {
 public:
  virtual ~IHandler_s0061_e250() {}
  virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};  // namespace Messaging
}
}
namespace EA {
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* p1, void* p2);  // +0x14
  PV(6) PV(7)
  virtual void RegisterHandler(Messaging::IHandler_s0061_e250* pHandler, uint32_t messageID);  // +0x20
  virtual void AddListener(Messaging::IHandler_s0061_e250* pHandler, uint32_t messageID);  // +0x24
  PV(10)
  virtual void RemoveListener(Messaging::IHandler_s0061_e250* pHandler, uint32_t messageID, int priority);  // +0x2c
};
}
namespace SP {
EA::IMessageServer* MessageServer();          // 0x0067dcc0
}
namespace SP {
namespace Pollen {
struct String8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  void* mAllocator;
  String8* TrimLeft();
  void TrimRight();
  unsigned int find_last_not_of(const char* p, unsigned int position, unsigned int n) const;
  unsigned int find_last_not_of(const char* p, unsigned int position) const;
};
}
}
namespace SP {
namespace Pollen {
const char* FindFirstNotOf(const char* first1, const char* last1, const char* first2,
                           const char* last2);
}
}
namespace SP {
namespace Pollen {
const char* FindLastNotOf(const char* last1, const char* first1, const char* first2,
                          const char* last2);
}
}
namespace SP {
namespace Pollen {
struct BaseA {
  virtual void a0();
  virtual void a1();
};
}
}
namespace SP {
namespace Pollen {
struct BaseB {
  virtual void b0();
  virtual void b1();
};
}
}
namespace SP {
namespace Pollen {
struct RCInit {
  volatile long mRefCount;  // +0x08
  RCInit() { _InterlockedExchange(&mRefCount, 0); }
};
}
}
namespace SP {
namespace Pollen {
struct D18 {
  char pad[8];
  D18(int v);
};
}
}
namespace SP {
namespace Pollen {
struct D20 {
  char pad0[0x10];
  unsigned short mType;
  unsigned short mType2;
  void SetValue(const void* src);
  void Destroy(int);
  D20(const void* b) : mType(0), mType2(0) { SetValue(b); }
};
}
}
namespace SP {
namespace Pollen {
struct O96 : BaseA, BaseB, RCInit {
  void* m0c;  // +0x0c
  int m10;    // +0x10
  int m14;    // +0x14
  D18 m18;    // +0x18
  D20 m20;    // +0x20
  O96(void* a, const void* b);
  O96(void* a, int b, int c, const void* d);
  O96* DeletingDtor(unsigned int flags);
  virtual void a0();
};
}
}
namespace SP {
namespace Pollen {
struct String8Tmp {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  void* mAllocator;
};
}
}
extern "C" bool __cdecl CreateTempFileW(wchar_t* path, const wchar_t* dir, const wchar_t* prefix,
                                        const wchar_t* suffix);  // 0x00932580
extern "C" bool __cdecl FileRemoveW(const wchar_t* path);        // 0x00931fd0
namespace SP {
namespace Pollen {
extern "C" wchar_t* PTR_DAT_01520730;                            // temp-file prefix
}
}
namespace SP {
namespace Pollen {
extern "C" wchar_t* PTR_u__evt_01520734;                         // temp-file suffix
}
}
namespace SP {
namespace Pollen {
extern "C" char* PTR_s_events_01520728;                          // "<events>"
}
}
namespace SP {
namespace Pollen {
extern "C" char* PTR_s_events_0152072c;                          // "<_events>"
}
}
namespace SP {
namespace Pollen {
extern "C" unsigned short DAT_015f5880;
}
}
namespace SP {
namespace Pollen {
extern "C" unsigned short DAT_015f5888;
}
}
namespace SP {
namespace Pollen {
struct IPollenObject {
  virtual void v00();
  virtual void AddRef();                                       // +0x04
  virtual void Release();                                      // +0x08
  virtual void v0c();
  virtual void v10();
  virtual void v14();
  virtual void v18();                                          // +0x18
  virtual void v1c();
  virtual void v20();
  virtual void v24();
  virtual bool v28(int a, int b);                              // +0x28
  virtual void v2c();
  virtual void v30();
  virtual void v34();
  virtual bool v38(const char* p, unsigned short id);          // +0x38
  virtual bool v3c(const char* path);                          // +0x3c
  virtual void v40();
  virtual unsigned int v44(wchar_t* buf, unsigned int count);  // +0x44
  virtual void v48();
  virtual bool v4c(int a, int b, int c, int d);                // +0x4c
  IPollenObject* InitStream(const wchar_t* path);              // 0x00931e10
  IPollenObject* InitPollen(IPollenObject* stream);            // 0x00609790
  IPollenObject* InitEvent(IPollenObject* a, IPollenObject* b);  // 0x0061e1a0
};
}
}
namespace SP {
namespace Pollen {
struct AutoPollenRef {
  IPollenObject* mpObject;
  AutoPollenRef() {}
  AutoPollenRef(IPollenObject* p);          // 0x0061df40
  void SetFromField(IPollenObject*& p);     // 0x005725d0
  ~AutoPollenRef() {
    if (mpObject) mpObject->Release();
  }
  IPollenObject* operator->() const { return mpObject; }
  operator IPollenObject*() const { return mpObject; }
};
}
}
namespace SP {
namespace Pollen {
struct IMessagePoster {
  virtual void m00();
  virtual void m04();
  virtual void m08();
  virtual void m0c();
  virtual void m10();
  virtual void m14();
  virtual void PostEvent(uint32_t id, void* p1, void* p2, void* p3);  // +0x18
};
}
}
namespace SP {
namespace Pollen {
struct PBase0 {
  void Ctor7(int a, int b, int c, int d, int e, int f, int g);
  ~PBase0();
};
}
}
namespace SP {
namespace Pollen {
struct PBase38 {
  void Ctor3(void* a, void* b, int c);
};
}
}
namespace SP {
namespace Pollen {
struct IBuf {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
  virtual void s16();
  virtual unsigned int GetText(wchar_t* buf, unsigned int count);  // vtbl +0x44
};
}
}
namespace SP {
namespace Pollen {
struct IArg8 {
virtual void a0();
virtual void a1();
virtual void a2();
  virtual void* Lookup(unsigned int id);  // vtbl +0x0c
};
}
}
namespace SP {
namespace Pollen {
struct FileArg {
  void* m0;
  void* m4;
  IArg8* m8;
};
}
}
namespace SP {
namespace Pollen {
extern "C" void F_931fd0(void* p);
}
}
namespace SP {
namespace Pollen {
struct PaintSystem {
  void* mVt;                    // +0x00
  char pad04[0x20];             // +0x04..0x23
  int m24, m28, m2c, m30, m34;  // +0x24
  void* mVt2;                   // +0x38
  IPollenObject* m3c;           // +0x3c
  IPollenObject* m40;           // +0x40
  char pad44[4];                // +0x44
  uint32_t mCS[6];              // +0x48 (CRITICAL_SECTION)
  char pad60[8];                // +0x60
  bool m68, m69;                // +0x68
  char pad6a[2];
  int m6c;                      // +0x6c
  wchar_t* m70a;                // +0x70
  wchar_t* m70b;                // +0x74
  wchar_t* m70c;                // +0x78
  void* m70d;                   // +0x7c
  PaintSystem* Ctor();
  void Dtor();
  bool ProcessFile(FileArg* arg);   // 0x0061eac0
  bool F_61e040(void* out, int flag);  // 0x0061e040
  bool Helper886(FileArg* arg);     // 0x0061e740
};
}
}
namespace SP {
namespace Pollen {
struct HeaderHandler_s0061_e250 {
  char pad00[0x3c];
  IPollenObject* m3c;  // +0x3c header file stream
  IPollenObject* m40;  // +0x40 header parser
  char pad44[0x2c];
  wchar_t* m70;        // +0x70 directory for the temporary file
  bool Invoke();
};
}
}
// ---- items of slice s0061e250 end

// ---- items of slice s0061ecf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
extern void* kVtbl13f1ab0[];   // 0x013f1ab0
extern void* kVtbl13ef094[];   // 0x013ef094
extern void* kVtbl13fca84[];   // 0x013fca84
extern void* kVtbl14188c0[];   // 0x014188c0
extern const char* g_pEventFmt;       // 0x1520704
extern const char* g_pEventAssetFmt;  // 0x1520708
extern const char* g_pEventClose;     // 0x152070c
extern const char* g_pArgOpen;        // 0x1520710
extern const char* g_pArgClose;       // 0x1520714
extern const char* g_pBoolOpen;       // 0x1520718
extern const char* g_pBoolClose;      // 0x152071c
extern const char* g_pStringOpen;     // 0x1520720
extern const char* g_pStringClose;    // 0x1520724
extern uint16_t g_nEventClose;        // 0x15f588c
extern uint16_t g_nArgOpen;           // 0x15f5884
extern uint16_t g_nArgClose;          // 0x15f589c
extern uint16_t g_nBoolOpen;          // 0x15f5894
extern uint16_t g_nBoolClose;         // 0x15f5890
extern uint16_t g_nStringOpen;        // 0x15f5898
extern uint16_t g_nStringClose;       // 0x15f58c4
int  __cdecl Sprintf8(char* dst, const char* fmt, ...);                             // 0x938470
void* __cdecl EA_Allocate(unsigned size, const char* name, int a, int b,
                          const char* file, int line);                              // 0xf473a0
void  __cdecl EA_Free(void* p);                                                     // 0xf47380
bool  __cdecl FUN_0061e040(void* dst, int a);                                       // 0x61e040
void  __cdecl FUN_0061e430(void* out, void* in);                                    // 0x61e430
void  __cdecl FUN_0061eba0(void);                                                   // 0x61eba0
void  __cdecl FUN_0061ec30(void);                                                   // 0x61ec30
void* __cdecl FileStream_ctor(void* self, void* path);                              // 0x931e10
void* __cdecl EncryptedStream_ctor(void* self, void* stream);                       // 0x609790
void  __cdecl File_Remove(void* path);                                              // 0x931fd0
void* __cdecl JobManager();                                                         // 0x68f4d0
void  __cdecl Job_Queue(void* item);                                                // 0x6b47a0
void* __cdecl Pollinator();                                                         // 0x67cb30
struct PollinatorRequest {
  void*    mpVtbl0;     // +0x00
  void*    mpVtbl1;     // +0x04
  uint32_t mRefCount;   // +0x08
  char     mPayload[0x214 - 0x0c];  // +0x0c
};
void* __cdecl MessageServer_s0061_ecf0();                                                      // 0x67dcc0
static inline void** Vt(void* p) { return *(void***)p; }
typedef bool (__thiscall *FBool_V)(void*);
typedef bool (__thiscall *FBool_VI)(void*, int);
typedef bool (__thiscall *FBool_VII)(void*, int, int);
typedef bool (__thiscall *FBool_VIIII)(void*, int, int, int, int);
typedef bool (__thiscall *FBool_VPV)(void*, const void*, int);
typedef bool (__thiscall *FBool_VP)(void*, void*);
typedef int  (__thiscall *FInt_V)(void*);
typedef int  (__thiscall *FInt_VPV)(void*, void*, int);
typedef unsigned (__thiscall *FUInt_VPV)(void*, void*, unsigned);
typedef int (__thiscall *FRef_V)(void*);
static inline void RefRelease(void* p) { if (p) ((FRef_V)Vt(p)[2])(p); }
typedef void (__thiscall *FListener)(void*, void*, uint32_t, int);
static inline void MsgListener(void* ms, void* handler, uint32_t msg, int prio) {
  ((FListener)Vt(ms)[11])(ms, handler, msg, prio);
}
struct DateTime_s0061_ecf0 {
  uint32_t mData[2];
  int GetParameter(int id);   // 0x92df80 (thiscall)
};
struct IEventSink {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
  virtual bool Write(const char* p, unsigned n);
};
struct EmptyAlloc {};
struct String8_s0061_ecf0 {            // eastl::basic_string<char>, 16 bytes
  char* mpBegin;
  char* mpEnd;
  char* mpCap;
  char* mpAlloc;
  ~String8_s0061_ecf0();               // 0x530670
};
String8_s0061_ecf0* __cdecl String8_Format(String8_s0061_ecf0* self, EmptyAlloc a, const char* fmt, ...);  // 0x472f50
void __cdecl EmitLine(IEventSink* pOut, const char* str);                             // 0x61dea0
struct EVariant {
  void*    mpValue;       // +0x00
  uint32_t mPad04;
  uint32_t mCount;        // +0x08
  uint32_t mPad0c;
  uint8_t  mFlags;        // +0x10
  uint8_t  mPad11;
  uint16_t mType;         // +0x12 (also the "is non-empty" word of an inline value)

  uint32_t Count() {
    if (mFlags & 0x30) return mCount;
    return mType != 0 ? 1 : 0;
  }
  char* Data() {
    if (mFlags & 0x30) return (char*)mpValue;
    return mType != 0 ? (char*)this : 0;
  }
};
struct cEventDisplay {
  uint32_t mPad00[3];
  int      mVerb;         // +0x0c
  uint32_t mAsset0;       // +0x10
  uint32_t mAsset1;       // +0x14
  DateTime_s0061_ecf0 mDate;         // +0x18 (8 bytes)
  EVariant mVariant;      // +0x20

  bool Show(IEventSink* pOut);  // 0x0061ecf0
};
#define EMIT_STR(str) EmitLine(pOut, (str))
#define EMIT_FMT(fmt, ...) { String8_s0061_ecf0 s_; EmitLine(pOut, String8_Format(&s_, EmptyAlloc(), fmt, __VA_ARGS__)->mpBegin); }
struct Base0 {
  virtual void b0();
  char pad[0x34];
};
namespace EA {
namespace Messaging {
class IHandler_s0061_ecf0 { public:
  virtual ~IHandler_s0061_ecf0();
  virtual bool HandleMessage(uint32_t messageID, void* pMessage);
};  // namespace EA::Messaging
}
}
struct cFeedManager : Base0, EA::Messaging::IHandler_s0061_ecf0 {
  void*    mpStream;      // +0x3c
  void*    mpOut;         // +0x40
  uint32_t mPad44;        // +0x44
  uint32_t mCS[6];        // +0x48 CRITICAL_SECTION
  uint32_t mPad60[2];     // +0x60
  uint8_t  mBusy;         // +0x68
  uint8_t  mFlag69;       // +0x69
  uint8_t  mPad6a[2];     // +0x6a
  uint32_t mLimit;        // +0x6c
  void*    mPad70[3];     // +0x70

  void OnPoll(void* pFeed);                 // 0061f3a0
  bool Pump(void* pA);                      // 0061f530
  bool Load(void* arg);                     // 0061f670
  bool StartJob();                          // 0061f9f0
  void Init();                              // 0061faf0
  virtual bool HandleMessage(uint32_t, void*);  // 0061fb50
  bool Dispatch2(uint32_t, void*);          // 0061fbc0
  void HeaderHandler();                     // 0x61e5b0
  bool CheckA();                            // 0xa9adf0
  void DoB();                               // 0x929c60
  void SetState(int a);                     // 0x92a7a0
};
struct Job {
  void*    mpCallback;    // +0x00
  void*    mpData;        // +0x04
  uint32_t mPad08[4];
  uint32_t mAffinity;     // +0x18
  void AddRequest(void* req);   // 0x68f9b0
  void Submit();                // 0x6909b0
  void GetStatus();             // 0x690120
};
void FUN_0061ecb0();        // job callback used by StartJob
void FUN_0061eca0();        // job callback used by OnPoll
typedef void (__thiscall *FReq_V)(void*);
// ---- items of slice s0061ecf0 end

// ---- items of slice s0061fbd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class AutoRefCount_s0061_fbd0 {
 public:
  T* mpObject;
  AutoRefCount_s0061_fbd0() : mpObject(0) {}
  AutoRefCount_s0061_fbd0(T* pObject) : mpObject(pObject) {
    if (mpObject) mpObject->AddRef();
  }
  AutoRefCount_s0061_fbd0& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  ~AutoRefCount_s0061_fbd0() {
    if (mpObject) mpObject->Release();
  }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
using EA::AutoRefCount_s0061_fbd0;
namespace SP {
namespace Pollen {
using namespace EA;
}
}
namespace SP {
namespace Pollen {
struct WorkItem {
  void* mpFunc;     // +0
  void* mpContext;  // +4
  uint32_t pad[4];
  int mPriority;  // +0x18
  void SetCallback(void* fn, void* ctx) {
    mpFunc = fn;
    mpContext = ctx;
  }
  void Release();  // 0x00690120
  void Submit();   // 0x006909b0
};
}
}
namespace SP {
namespace Pollen {
struct IWorkScheduler {
  PV(0) PV(1) PV(2) PV(3)
  virtual bool CreateItem(WorkItem** ppItem);  // +0x10
};
}
}
namespace SP {
namespace Pollen {
IWorkScheduler* GetWorkScheduler();  // 0x0068f4d0
}
}
namespace SP {
namespace Pollen {
void SubmitWorkItem(WorkItem* p);    // 0x006b47a0
}
}
namespace SP {
namespace Pollen {
struct WorkItemRef {
  WorkItem* mp;
  WorkItemRef() : mp(0) {}
  ~WorkItemRef() {
    if (mp) mp->Release();
  }
  WorkItem*& AsOutParam() {
    if (mp) {
      WorkItem* p = mp;
      mp = 0;
      p->Release();
    }
    return mp;
  }
};
}
}
namespace SP {
namespace Pollen {
void WorkFn_61fae0();
}
}
namespace SP {
namespace Pollen {
struct PollEvent {
  uint32_t pad[4];
  uint8_t mFlags;  // +0x10 (bit 0x20: handled)
  uint8_t pad11;
  uint16_t mType;  // +0x12
};
}
}
namespace SP {
namespace Pollen {
struct RequestObj {  // 0x38 bytes
  uint32_t pad[(0x38 - 4) / 4];
  RequestObj(void* a1, PollEvent* ev);                            // 0x0061e250
  RequestObj(void* a1, void* a2, void* a3, PollEvent* ev);        // 0x0061e2c0
  virtual int AddRef();
  virtual int Release();
};
}
}
namespace SP {
namespace Pollen {
void __stdcall RegisterRequestObj(RequestObj* p);  // 0x0068f9b0
}
}
namespace SP {
namespace Pollen {
class cPollinatorJobHost {
 public:
  bool QueueEvent(void* a1, PollEvent* ev);                                // 0x0061fdb0
  bool QueueEvent4(void* a1, void* a2, void* a3, PollEvent* ev);           // 0x0061fee0
};
}
}
// ---- items of slice s0061fbd0 end

// @ 0x0061df60
namespace SP { namespace Pollen {
const char* FindFirstNotOf(const char* first1, const char* last1, const char* first2, const char* last2)
{
  for (; first1 != last1; ++first1) {
    const char* it = first2;
    for (; it != last2; ++it) {
      if (*first1 == *it) break;
    }
    if (it == last2) return first1;
  }
  return last1;
}
}}  // namespace SP::Pollen

// @ 0x0061dfa0
namespace SP { namespace Pollen {
const char* FindLastNotOf(const char* last1, const char* first1, const char* first2, const char* last2)
{
  while (last1 != first1) {
    --last1;
    const char* it = first2;
    for (; it != last2; ++it) {
      if (*last1 == *it) break;
    }
    if (it == last2) return last1;
  }
  return first1;
}
}}  // namespace SP::Pollen

// @ 0x0061dfe0
namespace SP { namespace Pollen {
void PollenNotifyHelper(void* self)
{
  (void)self;
}
}}  // namespace SP::Pollen

// @ 0x0061e040
namespace SP { namespace Pollen {
void* PollenHelper311(void* self, void* a, void* b)
{
  (void)a;
  (void)b;
  return self;
}
}}  // namespace SP::Pollen

// @ 0x0061e180
namespace SP { namespace Pollen {
bool GuardedFlag::Get() const
{
  EnterCriticalSection((void*)mCriticalSection);
  bool b = mbFlag;
  LeaveCriticalSection((void*)mCriticalSection);
  return b;
}
}}  // namespace SP::Pollen

// @ 0x0061e1a0
namespace SP { namespace Pollen {
void* PollenCtor78(void* self, void* a, void* b)
{
  (void)a;
  (void)b;
  return self;
}
}}  // namespace SP::Pollen

// @ 0x0061e250
namespace SP { namespace Pollen {
O96::O96(void* a, const void* b)
: m0c(a), m10(0), m14(0), m18(1), m20(b) {}
}}  // namespace SP::Pollen

// @ 0x0061e2c0
namespace SP { namespace Pollen {
O96::O96(void* a, int b, int c, const void* d)
: m0c(a), m10(b), m14(c), m18(1), m20(d) {}
}}  // namespace SP::Pollen

// @ 0x0061e330
namespace SP { namespace Pollen {
O96* O96::DeletingDtor(unsigned int flags)
{
  D20& v20 = m20;
  if (v20.mType & 4) v20.Destroy(0);
  *(void**)((char*)this + 4) = V_13ef094;
  *(void**)this = V_13eb938;
  if (flags & 1) EASTL_allocator_deallocate(this);
  return this;
}
}}  // namespace SP::Pollen

// @ 0x0061e3c0
namespace SP { namespace Pollen {
unsigned int String8::find_last_not_of(const char* p, unsigned int position) const
{
  const unsigned int n = (unsigned int)strlen(p);
  char* const begin = mpBegin;
  const unsigned int len = (unsigned int)(mpEnd - begin);
  if (len == 0) return 0xffffffffu;
  const unsigned int lenMinus1 = len - 1;
  const unsigned int& pos = position < lenMinus1 ? position : lenMinus1;
  const char* const r = FindLastNotOf(begin + pos + 1, begin, p, p + n);
  if (r == begin) return 0xffffffffu;
  return (unsigned int)(r - begin) - 1;
}
}}  // namespace SP::Pollen

// @ 0x0061e430
namespace SP { namespace Pollen {
void ConvertToString8(void* out, const wchar_t* wide)
{
  const unsigned int n = (unsigned int)wcslen(wide);
  String8Tmp tmp;
  F_93c440(&tmp, wide + n - 0x10, -1);
  memcpy(out, tmp.mpBegin, (unsigned int)(tmp.mpEnd - tmp.mpBegin));
  if ((tmp.mpCapacity - tmp.mpBegin) > 1) {
    if (tmp.mpBegin) EASTL_allocator_deallocate(tmp.mpBegin);
  }
}
}}  // namespace SP::Pollen

// @ 0x0061e4a0
namespace SP { namespace Pollen {
PaintSystem* PaintSystem::Ctor()
{
  ((PBase0*)this)->Ctor7(0, 0, 0x12c, 0x3e8, 2, 0, 0);
  m28 = 0;
  m2c = 0;
  m30 = 0;
  mVt = V_13fcab8;
  m34 = -1;
  m24 = 0;
  ((PBase38*)this)->Ctor3((void*)0xed1cf0, this, 0);
  mVt2 = V_13eb394;
  mVt = V_13fcac4;
  mVt2 = V_13fcabc;
  m3c = 0;
  m40 = 0;
  InitializeCriticalSection(&mCS);
  m68 = 0;
  m69 = 0;
  m6c = 0x8000;
  m70a = gEmptyStringW;
  m70b = m70a;
  m70c = m70a + 1;
  return this;
}
}}  // namespace SP::Pollen

// @ 0x0061e540
namespace SP { namespace Pollen {
void PaintSystem::Dtor()
{
  volatile void** const vt = (volatile void**)this;
  vt[0] = V_13fcac4;
  ((volatile void**)this)[0x0e] = V_13fcabc;
  if ((m70c - m70a) > 1) {
    if (m70a) EASTL_allocator_deallocate(m70a);
  }
  DeleteCriticalSection(&mCS);
  if (m40) m40->Release();
  if (m3c) m3c->Release();
  vt[0x0e] = V_13eb394;
  ((PBase0*)this)->~PBase0();
}
}}  // namespace SP::Pollen

// @ 0x0061e5b0
namespace SP { namespace Pollen {
bool HeaderHandler_s0061_e250::Invoke()
{
  wchar_t path[0x104];
  if (!CreateTempFileW(path, m70, PTR_DAT_01520730, PTR_u__evt_01520734)) return false;
  void* const memStream = operator new(0x22c, "Pollinator", 0, 0, 0, 0);
  IPollenObject* stream = memStream ? ((IPollenObject*)memStream)->InitStream(path) : 0;
  IPollenObject* const oldStream = m3c;
  if (stream != oldStream) {
    if (stream) stream->AddRef();
    m3c = stream;
    if (oldStream) oldStream->Release();
  }
  void* const memParser = operator new(0xb0, "Pollinator", 0, 0, 0, 0);
  IPollenObject* parser = memParser ? ((IPollenObject*)memParser)->InitPollen(m3c) : 0;
  IPollenObject* const oldParser = m40;
  if (parser != oldParser) {
    if (parser) parser->AddRef();
    m40 = parser;
    if (oldParser) oldParser->Release();
  }
  String8Tmp tmp;
  ConvertToString8(&tmp, path);
  if (m40->v3c((const char*)&tmp)) {
    if (m3c->v4c(2, 3, 1, 0)) {
      if (m40->v38(PTR_s_events_01520728, DAT_015f5880)) return true;
      m3c->v18();
    }
  }
  if (m3c) {
    IPollenObject* const p = m3c;
    m3c = 0;
    p->Release();
  }
  if (m40) {
    IPollenObject* const p = m40;
    m40 = 0;
    p->Release();
  }
  FileRemoveW(path);
  return false;
}
}}  // namespace SP::Pollen

// @ 0x0061e740
namespace SP { namespace Pollen {
bool PaintSystem::Helper886(FileArg* arg)
{
  (void)arg;
  if (m3c) {
    wchar_t next[0x104];
    wchar_t cur[0x104];
    if (F_61e040(cur, 1)) {
      const unsigned int n = m3c->v44(next, 0x104u);
      if (n > 0) {
        if (wcscmp(next, cur) == 0) {
          if (m3c->v4c(3, 3, 1, 0) && m3c->v28(0, 2) &&
              m40->v38(PTR_s_events_0152072c, DAT_015f5888)) {
            AutoPollenRef parser;
            parser.SetFromField(m40);
            AutoPollenRef stream;
            stream.SetFromField(m3c);
            if (m3c) {
              IPollenObject* const p = m3c;
              m3c = 0;
              p->Release();
            }
            if (m40) {
              IPollenObject* const p = m40;
              m40 = 0;
              p->Release();
            }
            if (parser->v28(0, 0)) {
              void* const mem = operator new(0x14, "Pollinator", 0, 0, 0, 0);
              IPollenObject* ev = mem ? ((IPollenObject*)mem)->InitEvent(parser, stream) : 0;
              AutoPollenRef ref((IPollenObject*)ev);
              ((IMessagePoster*)SP::MessageServer())
                  ->PostEvent(0x5fff3ffu, (IPollenObject*)ref, 0, 0);
              return true;
            }
          }
        } else if (!m69) {
          void* const memStream = operator new(0x22c, "Pollinator", 0, 0, 0, 0);
          IPollenObject* stream = memStream ? ((IPollenObject*)memStream)->InitStream(cur) : 0;
          AutoPollenRef refStream((IPollenObject*)stream);
          void* const memParser = operator new(0xb0, "Pollinator", 0, 0, 0, 0);
          IPollenObject* parser =
              memParser ? ((IPollenObject*)memParser)->InitPollen((IPollenObject*)refStream) : 0;
          AutoPollenRef refParser((IPollenObject*)parser);
          String8Tmp tmp;
          ConvertToString8(&tmp, cur);
          if (parser->v3c((const char*)&tmp) && stream->v4c(1, 3, 1, 0)) {
            void* const mem = operator new(0x14, "Pollinator", 0, 0, 0, 0);
            IPollenObject* ev = mem ? ((IPollenObject*)mem)->InitEvent((IPollenObject*)refParser,
                                                                      (IPollenObject*)refStream)
                                    : 0;
            AutoPollenRef ref((IPollenObject*)ev);
            ((IMessagePoster*)SP::MessageServer())
                ->PostEvent(0x5fff3ffu, (IPollenObject*)ref, 0, 0);
            return true;
          }
        }
      }
    }
  }
  void* const cs = mCS;
  EnterCriticalSection(cs);
  m68 = 0;
  LeaveCriticalSection(cs);
  return true;
}
}}  // namespace SP::Pollen

// @ 0x0061eac0
namespace SP { namespace Pollen {
bool PaintSystem::ProcessFile(FileArg* arg)
{
  if (arg->m8) {
    void* p = arg->m8->Lookup(0x60419efu);
    if (p) F_931fd0((char*)p + 0xc);
  }
  if (!m69) {
    wchar_t cur[0x104];
    if (F_61e040(cur, 1)) {
      wchar_t next[0x104];
      const unsigned int n = ((IBuf*)m3c)->GetText(next, 0x104u);
      if (n > 0) {
        const wchar_t* a = next;
        const wchar_t* b = cur;
        while (*a && *a == *b) {
          ++a;
          ++b;
        }
        if (*a != *b) {
          return Helper886(arg);
        }
      }
    }
  }
  void* const cs = mCS;
  EnterCriticalSection(cs);
  m68 = 0;
  LeaveCriticalSection(cs);
  return true;
}
}}  // namespace SP::Pollen

// @ 0x0061eba0
namespace SP { namespace Pollen {
String8* String8::TrimLeft()
{
  char ws[3];
  ws[0] = ' ';
  ws[1] = '\t';
  ws[2] = 0;
  const char* wsEnd = ws;
  while (*wsEnd) ++wsEnd;
  const char* const p = FindFirstNotOf(mpBegin, mpEnd, ws, wsEnd);
  const unsigned int n = (p == mpEnd) ? 0xffffffffu : (unsigned int)(p - mpBegin);
  char* pDst = mpBegin;
  char* pSrc = pDst + n;
  if (pDst != pSrc) {
    memmove(pDst, pSrc, (mpEnd - pSrc) + 1);
    mpEnd = (char*)mpEnd + (pDst - pSrc);
  }
  return this;
}
}}  // namespace SP::Pollen

// @ 0x0061ec30
namespace SP { namespace Pollen {
void String8::TrimRight()
{
  char ws[4];
  ws[0] = ' ';
  ws[1] = '\t';
  ws[2] = 0;
  const unsigned int npos = 0xffffffffu;
  const unsigned int pos = find_last_not_of(ws, npos) + 1;
  unsigned int count = npos;
  count = eastl::min_alt(count, (unsigned int)(mpEnd - mpBegin) - pos);
  char* const pSrc = mpBegin + count + pos;
  char* const pDst = mpBegin + pos;
  if (pDst != pSrc) {
    memmove(pDst, pSrc, (unsigned int)(mpEnd - pSrc) + 1);
    mpEnd = (char*)mpEnd + (pDst - pSrc);
  }
}
}}  // namespace SP::Pollen

// @ 0x0061ecf0
bool cEventDisplay::Show(IEventSink* pOut)
{
  char buf[0x80];
  unsigned n;
  if (mAsset0 == 0 && mAsset1 == 0) {
    Sprintf8(buf, g_pEventFmt, mVerb, mDate.GetParameter(1), mDate.GetParameter(2),
             mDate.GetParameter(6), mDate.GetParameter(8), mDate.GetParameter(9),
             mDate.GetParameter(10));
    n = 0x3e;
  } else {
    Sprintf8(buf, g_pEventAssetFmt, mVerb, mAsset0, mAsset1, mDate.GetParameter(1),
             mDate.GetParameter(2), mDate.GetParameter(6), mDate.GetParameter(8),
             mDate.GetParameter(9), mDate.GetParameter(10));
    n = 0x5b;
  }
  if (!pOut->Write(buf, n)) return false;

  uint32_t count;
  if (mVariant.mFlags & 0x30) {
    count = mVariant.mCount;
    if (count == 0) goto done;
  } else {
    if (mVariant.mType == 0) goto done;
    count = 1;
  }
  {
    char* data = mVariant.Data();
    String8_s0061_ecf0* strs = (String8_s0061_ecf0*)data;
    for (uint32_t i = 0; i < count; ++i) {
      switch (mVariant.mType) {
        case 1:
          if (!pOut->Write(g_pBoolOpen, g_nBoolOpen)) return false;
          EMIT_STR(data[i] != 0 ? "true" : "false");
          if (!pOut->Write(g_pBoolClose, g_nBoolClose)) return false;
          break;
        case 0x12:
          if (!pOut->Write(g_pStringOpen, g_nStringOpen)) return false;
          EMIT_STR(strs[i].mpBegin);
          if (!pOut->Write(g_pStringClose, g_nStringClose)) return false;
          break;
        case 0x13:
          if (!pOut->Write(g_pStringOpen, g_nStringOpen)) return false;
          EMIT_FMT("%ls", strs[i].mpBegin);
          if (!pOut->Write(g_pStringClose, g_nStringClose)) return false;
          break;
        case 5:
          if (!pOut->Write(g_pArgOpen, g_nArgOpen)) return false;
          EMIT_FMT("%I8d", (int)((char*)data)[i]);
          if (!pOut->Write(g_pArgClose, g_nArgClose)) return false;
          break;
        case 6:
          if (!pOut->Write(g_pArgOpen, g_nArgOpen)) return false;
          EMIT_FMT("%I8u", (unsigned)((uint8_t*)data)[i]);
          if (!pOut->Write(g_pArgClose, g_nArgClose)) return false;
          break;
        case 7:
          if (!pOut->Write(g_pArgOpen, g_nArgOpen)) return false;
          EMIT_FMT("%I16d", (int)((int16_t*)data)[i]);
          if (!pOut->Write(g_pArgClose, g_nArgClose)) return false;
          break;
        case 8:
          if (!pOut->Write(g_pArgOpen, g_nArgOpen)) return false;
          EMIT_FMT("%I16u", (unsigned)((uint16_t*)data)[i]);
          if (!pOut->Write(g_pArgClose, g_nArgClose)) return false;
          break;
        case 9:
          if (!pOut->Write(g_pArgOpen, g_nArgOpen)) return false;
          EMIT_FMT("%I32d", ((int*)data)[i]);
          if (!pOut->Write(g_pArgClose, g_nArgClose)) return false;
          break;
        case 10:
          if (!pOut->Write(g_pArgOpen, g_nArgOpen)) return false;
          EMIT_FMT("%I32u", ((unsigned*)data)[i]);
          if (!pOut->Write(g_pArgClose, g_nArgClose)) return false;
          break;
        case 11:
          if (!pOut->Write(g_pArgOpen, g_nArgOpen)) return false;
          EMIT_FMT("%I64d", ((int64_t*)data)[i]);
          if (!pOut->Write(g_pArgClose, g_nArgClose)) return false;
          break;
        case 12:
          if (!pOut->Write(g_pArgOpen, g_nArgOpen)) return false;
          EMIT_FMT("%I64u", ((uint64_t*)data)[i]);
          if (!pOut->Write(g_pArgClose, g_nArgClose)) return false;
          break;
        case 13:
          if (!pOut->Write(g_pArgOpen, g_nArgOpen)) return false;
          EMIT_FMT("%f", (double)((float*)data)[i]);
          if (!pOut->Write(g_pArgClose, g_nArgClose)) return false;
          break;
        case 14:
          if (!pOut->Write(g_pArgOpen, g_nArgOpen)) return false;
          EMIT_FMT("%f", ((double*)data)[i]);
          if (!pOut->Write(g_pArgClose, g_nArgClose)) return false;
          break;
        default:
          break;
      }
    }
  }
done:
  return pOut->Write(g_pEventClose, g_nEventClose);
}

// @ 0x0061f3a0
void cFeedManager::OnPoll(void* pFeed)
{
  if (pFeed != 0) {
    ((FBool_V)Vt(pFeed)[6])(pFeed);         // +0x18
    PollinatorRequest* reqObj = (PollinatorRequest*)EA_Allocate(0x214, "Pollinator", 0, 0, 0, 0);
    void* req = reqObj;
    if (req == 0) {
      req = 0;
    } else {
      // The inlined base and derived constructors install their vftables and
      // zero the refcount before the virtual slot-0 call.
      reqObj->mpVtbl0 = kVtbl13f1ab0;
      reqObj->mpVtbl1 = kVtbl13ef094;
      reqObj->mRefCount = 0;
      reqObj->mpVtbl0 = kVtbl13fca84;
      reqObj->mpVtbl1 = kVtbl14188c0;
      ((void(__thiscall*)(void*))Vt(req)[0])(req);
      Job* job = 0;
      void* mgr = JobManager();
      if (job) { Job* old = job; job = 0; old->GetStatus(); }
      bool ok = ((FBool_VP)Vt(mgr)[4])(mgr, &job);   // +0x10
      if (ok) {
        job->AddRequest(req);
        int n = ((FInt_VPV)Vt(pFeed)[17])(pFeed, reqObj->mPayload, 0x104);  // +0x44
        if ((unsigned)n > 0) {
          job->mpCallback = (void*)FUN_0061eca0;
          job->mpData = this;
          job->mAffinity = 4;
          Job_Queue(job);
          job->Submit();
          if (job) job->GetStatus();
          ((FReq_V)Vt(req)[1])(req);
          return;
        }
      }
      if (job) job->GetStatus();
    }
    char buf[0x104];
    int r = ((FInt_VPV)Vt(pFeed)[18])(pFeed, buf, 0x104);  // +0x48
    if (r == 0) {
      *(uint32_t*)buf = 0x4c554e3c;        // "<NUL"
      *(uint16_t*)(buf + 4) = 0x3e4c;      // "L>"
      buf[6] = 0;
    }
    if (req) ((FReq_V)Vt(req)[1])(req);
  }
  EnterCriticalSection((char*)this + 0x48);
  mBusy = 0;
  LeaveCriticalSection((char*)this + 0x48);
}

// @ 0x0061f530
bool cFeedManager::Pump(void* pA)
{
  void* sub = *(void**)((char*)pA + 8);
  if (sub == 0) return false;
  void* data = ((void*(__thiscall*)(void*, uint32_t))Vt(sub)[3])(sub, 0x5f8fd2c);
  if (data == 0) return false;

  if (mpStream == 0) {
    HeaderHandler();
  } else {
    if (((FBool_VIIII)Vt(mpStream)[19])(mpStream, 2, 3, 1, 0)) {
      bool b = ((FBool_VII)Vt(mpStream)[10])(mpStream, 0, 2);
      void* stream = mpStream;
      if (!b) {
        if (stream) { mpStream = 0; RefRelease(stream); }
        if (mpOut)   { void* p = mpOut; mpOut = 0; RefRelease(p); }
      } else {
        uint32_t extra = (*(uint8_t*)((char*)data + 0x30) & 0x30)
                             ? *(uint32_t*)((char*)data + 0x24) : 0x10u;
        int size = ((FInt_V)Vt(stream)[7])(stream);   // +0x1c
        if ((uint32_t)(size + extra + 0x60) > mLimit) {
          ((FBool_VPV)Vt(mpOut)[14])(mpOut, "<events>", 0);  // +0x38
          ((FInt_V)Vt(mpStream)[6])(mpStream);               // +0x18
          HeaderHandler();
        }
      }
    }
  }
  if (mpStream != 0 && mpOut != 0) {
    if (((FInt_V)Vt(mpOut)[5])(mpOut) == 0) {   // +0x14
      if (((cEventDisplay*)data)->Show((IEventSink*)mpOut)) {
        ((FInt_V)Vt(mpStream)[6])(mpStream);    // +0x18
        return true;
      }
      { void* p = mpStream; if (p) { mpStream = 0; RefRelease(p); } }
      { void* p = mpOut;    if (p) { mpOut = 0;    RefRelease(p); } }
    }
  }
  return false;
}

// @ 0x0061f670
bool cFeedManager::Load(void* arg)
{
  char path[0x214];   // wide-path scratch (local_608 + guards)
  if (!FUN_0061e040(path, 0)) return true;

  void* fs = EA_Allocate(0x22c, "Pollinator", 0, 0, 0, 0);
  if (fs) fs = FileStream_ctor(fs, path);
  void* old = mpStream;
  if (fs != old) {
    if (fs) ((FRef_V)Vt(fs)[1])(fs);
    mpStream = fs;
    if (old) RefRelease(old);
  }

  void* es = EA_Allocate(0xb0, "Pollinator", 0, 0, 0, 0);
  if (es) es = EncryptedStream_ctor(es, mpStream);
  old = mpOut;
  if (es != old) {
    if (es) ((FRef_V)Vt(es)[1])(es);
    mpOut = es;
    if (old) RefRelease(old);
  }

  // Decoded stream name: wide-path -> char buffer.
  char name[0x1c];
  FUN_0061e430(name, path);
  bool ok = (*(bool(__thiscall*)(void*, void*))Vt(mpOut)[15])(mpOut, name);  // +0x3c
  if (!ok) goto fail;
  ok = ((FBool_VIIII)Vt(mpStream)[19])(mpStream, 3, 3, 1, 0);                // +0x4c
  if (!ok) goto fail;

  {
    // Build the "</event>" marker string as an eastl string (global, else heap).
    const char* pat = g_pEventClose;   // "<event>" pattern (masked global 0x152070c)
    uint32_t patLen = 0;
    { const char* p = pat; while (*p) ++p; patLen = (uint32_t)(p - pat); }

    char* strBeg = (char*)0x1667bac;   // eastl::gEmptyString16 (masked)
    char* strCap;
    uint32_t allocLen = patLen + 1;
    if (allocLen > 1) {
      strBeg = (char*)EA_Allocate(allocLen, "Editor", 0, 0,
                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                  0xd1);
      strCap = strBeg + allocLen;
    } else {
      strCap = strBeg + 1;
    }
    for (uint32_t i = 0; i < patLen; ++i) strBeg[i] = pat[i];
    strBeg[patLen] = 0;
    FUN_0061eba0();     // TrimLeft on the marker
    FUN_0061ec30();     // TrimRight on the marker

    // Scan the stream for the marker.  `match` is the running match offset into
    // the marker; `lastMatch` records the byte offset one past the match.
    char readbuf[0x400];
    int found = 0;
    uint32_t match = 0;
    int consumed = 0;
    uint32_t got = ((FUInt_VPV)Vt(mpOut)[12])(mpOut, readbuf, 0x400);   // +0x30
    if (got != 0) {
      do {
        uint32_t i = 0;
        do {
          uint16_t m = (uint16_t)match;
          ++match;
          if (strBeg[m] == readbuf[i]) {
            if ((uint16_t)match == (uint16_t)(-(int)strBeg)) {  // == patLen
              found = (int)(i + 1) + consumed;
              match = 0;
            }
          } else {
            match = 0;
          }
          ++i;
        } while (i < got);
        consumed += got;
        got = ((FUInt_VPV)Vt(mpOut)[12])(mpOut, readbuf, 0x400);
      } while (got != 0);

      if (found != 0) {
        ok = ((FBool_VI)Vt(mpStream)[8])(mpStream, found);     // +0x20
        if (ok) {
          ok = ((FBool_VII)Vt(mpOut)[10])(mpOut, 0, 0);         // +0x28
          if (ok) {
            for (;;) {
              if (((FUInt_VPV)Vt(mpOut)[12])(mpOut, readbuf, 0x400) == 0) break;
            }
            ((FInt_V)Vt(mpStream)[6])(mpStream);                // +0x18
            EA_Free(strBeg);                                    // (eastl string dtor)
            return true;
          }
        }
        ((FInt_V)Vt(mpOut)[6])(mpOut);                          // +0x18
        File_Remove(name);
        if (strCap - strBeg > 1 && strBeg != 0) EA_Free(strBeg);
        goto fail;
      }
    }
    ((FInt_V)Vt(mpOut)[6])(mpOut);                              // +0x18
    File_Remove(name);
    if (mpStream) { void* p = mpStream; mpStream = 0; RefRelease(p); }
    if (mpOut)    { void* p = mpOut;    mpOut = 0;    RefRelease(p); }
    if (strCap - strBeg > 1 && strBeg != 0) EA_Free(strBeg);
    return true;
  }
fail:
  if (mpStream) { void* p = mpStream; mpStream = 0; RefRelease(p); }
  if (mpOut)    { void* p = mpOut;    mpOut = 0;    RefRelease(p); }
  return false;
}

// @ 0x0061f9f0
bool cFeedManager::StartJob()
{
  EnterCriticalSection((char*)this + 0x48);
  if (mBusy != 0) {
    LeaveCriticalSection((char*)this + 0x48);
    return false;
  }
  mBusy = 1;
  void* poll = Pollinator();
  if (poll != 0 && *(uint8_t*)((char*)poll + 0xf1) != 0) {
    Job* job = 0;
    void* mgr = JobManager();
    if (job) { Job* old = job; job = 0; old->GetStatus(); }
    bool ok = ((FBool_VP)Vt(mgr)[4])(mgr, &job);   // +0x10
    if (ok) {
      mBusy = 1;
      job->mpCallback = (void*)FUN_0061ecb0;
      job->mpData = this;
      job->mAffinity = 4;
      Job_Queue(job);
      job->Submit();
      if (job) job->GetStatus();
      LeaveCriticalSection((char*)this + 0x48);
      return true;
    }
    if (job) job->GetStatus();
  }
  mBusy = 0;
  LeaveCriticalSection((char*)this + 0x48);
  return false;
}

// @ 0x0061faf0
void cFeedManager::Init()
{
  mFlag69 = 1;
  EA::Messaging::IHandler_s0061_ecf0* h = this;
  MsgListener(MessageServer_s0061_ecf0(), h, 0x44db12e, -9999);
  MsgListener(MessageServer_s0061_ecf0(), h, 0x685f4af, -9999);
  if (CheckA()) DoB();
  StartJob();
}

// @ 0x0061fb50
bool cFeedManager::HandleMessage(uint32_t messageID, void* pMessage)
{
  if (messageID == 0x60ba744) {
    OnPoll(pMessage);
    return true;
  }
  if (messageID == 0x44db12e) {
    if (pMessage == 0) {
      if (CheckA()) {
        DoB();
        return true;
      }
    } else {
      SetState(0);
      StartJob();
    }
    return true;
  }
  if (messageID == 0x685f4af) {
    StartJob();
  }
  return false;
}

// @ 0x0061fbc0
bool cFeedManager::Dispatch2(uint32_t, void*)
{
  return StartJob();
}

// @ 0x0061fdb0
namespace SP { namespace Pollen {
bool cPollinatorJobHost::QueueEvent(void* a1, PollEvent* ev)
{
  if (!(ev->mFlags & 0x20)) {
    switch (ev->mType) {
      case 0: case 2: case 3: case 4: case 0xf: case 0x10: case 0x11: case 0x14:
        break;
      default: {
        AutoRefCount_s0061_fbd0<RequestObj> obj(new ("Pollinator", 0, 0, 0, 0) RequestObj(a1, ev));
        if (obj.mpObject) {
          WorkItemRef item;
          if (GetWorkScheduler()->CreateItem(&item.AsOutParam())) {
            RegisterRequestObj(obj.mpObject);
            item.mp->mpFunc = (void*)WorkFn_61fae0;
            item.mp->mpContext = this;
            item.mp->mPriority = 4;
            SubmitWorkItem(item.mp);
            item.mp->Submit();
            return true;
          }
        }
      }
    }
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x0061fee0
namespace SP { namespace Pollen {
bool cPollinatorJobHost::QueueEvent4(void* a1, void* a2, void* a3, PollEvent* ev)
{
  if (!(ev->mFlags & 0x20)) {
    switch (ev->mType) {
      case 0: case 2: case 3: case 4: case 0xf: case 0x10: case 0x11: case 0x14:
        break;
      default: {
        AutoRefCount_s0061_fbd0<RequestObj> obj(new ("Pollinator", 0, 0, 0, 0) RequestObj(a1, a2, a3, ev));
        if (obj.mpObject) {
          WorkItemRef item;
          if (GetWorkScheduler()->CreateItem(&item.AsOutParam())) {
            RegisterRequestObj(obj.mpObject);
            item.mp->mpFunc = (void*)WorkFn_61fae0;
            item.mp->mpContext = this;
            item.mp->mPriority = 4;
            SubmitWorkItem(item.mp);
            item.mp->Submit();
            return true;
          }
        }
      }
    }
  }
  return false;
}
}}  // namespace SP::Pollen
