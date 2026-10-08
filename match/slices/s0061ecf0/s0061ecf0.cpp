// SP::Pollen feed/event manager (Spore EP1 "SporeEP1_RL") and its property-list event
// printer. Region 0x61e000-0x61fbc0. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Contents (VAs):
//   0061ecf0  cEventDisplay::Show        (property-list event formatter, big switch)
//   0061f3a0  cFeedManager::OnPoll       (build a Pollinator work item, enqueue it)
//   0061f530  cFeedManager::Pump         (open/advance the encrypted event stream)
//   0061f670  cFeedManager::Load         (open the feed file, scan for marker)
//   0061f9f0  cFeedManager::StartJob
//   0061faf0  cFeedManager::Init
//   0061fb50  cFeedManager::HandleMessage (IHandler override)
//   0061fbc0  cFeedManager::Dispatch2
#include "types.h"

// ---------------------------------------------------------------------------------------------
// External callees (bodies live elsewhere; targets are masked relocations).
// ---------------------------------------------------------------------------------------------
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void* cs);

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
void  __cdecl Job_Add(void* item);                                                  // 0x68f9b0
void  __cdecl Job_Submit();                                                         // 0x6909b0
void  __cdecl Job_Queue(void* item);                                                // 0x6b47a0
void  __cdecl Job_Release(void* job);                                               // 0x690120 (SP::cJob::GetStatus)
void* __cdecl Pollinator();                                                         // 0x67cb30

void* __cdecl MessageServer();                                                      // 0x67dcc0

// vtable-slot call helpers (thiscall through an explicit function pointer).
static inline void** Vt(void* p) { return *(void***)p; }
typedef bool (__thiscall *FBool_V)(void*);
typedef bool (__thiscall *FBool_VI)(void*, int);
typedef bool (__thiscall *FBool_VII)(void*, int, int);
typedef bool (__thiscall *FBool_VIII)(void*, int, int, int);
typedef bool (__thiscall *FBool_VIIII)(void*, int, int, int, int);
typedef bool (__thiscall *FBool_VPV)(void*, const void*, int);
typedef bool (__thiscall *FBool_VP)(void*, void*);
typedef int  (__thiscall *FInt_V)(void*);
typedef int  (__thiscall *FInt_VPV)(void*, void*, int);
typedef unsigned (__thiscall *FUInt_VPV)(void*, void*, unsigned);

// Generic ref-counted object: +0x4 AddRef, +0x8 Release.
typedef int (__thiscall *FRef_V)(void*);
static inline void RefAdd(void* p) { if (p) ((FRef_V)Vt(p)[1])(p); }
static inline void RefRelease(void* p) { if (p) ((FRef_V)Vt(p)[2])(p); }

// Message server: +0x2c AddListener/RemoveListener (handler, msg, prio).
typedef void (__thiscall *FListener)(void*, void*, uint32_t, int);
static inline void MsgListener(void* ms, void* handler, uint32_t msg, int prio) {
  ((FListener)Vt(ms)[11])(ms, handler, msg, prio);
}

// ---------------------------------------------------------------------------------------------
// EA::DateTime
// ---------------------------------------------------------------------------------------------
struct DateTime {
  uint32_t mData[2];
  int GetParameter(int id);   // 0x92df80 (thiscall)
};

// ---------------------------------------------------------------------------------------------
// cEventDisplay : the object printed by the feed event list.  Layout:
//   +0x0c verb-hash, +0x10/+0x14 asset id, +0x18 DateTime, +0x20 Variant
// ---------------------------------------------------------------------------------------------
// Static XML fragments: pointer table in .data, lengths filled at startup.
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

// Output sink: slot 14 writes a (ptr, length) fragment and returns success.
struct IEventSink {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13();
  virtual bool Write(const char* p, unsigned n);
};

struct EmptyAlloc {};
struct String8 {            // eastl::basic_string<char>, 16 bytes
  char* mpBegin;
  char* mpEnd;
  char* mpCap;
  char* mpAlloc;
  ~String8();               // 0x530670
};
String8* __cdecl String8_Format(String8* self, EmptyAlloc a, const char* fmt, ...);  // 0x472f50
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
  DateTime mDate;         // +0x18 (8 bytes)
  EVariant mVariant;      // +0x20

  bool Show(IEventSink* pOut);  // 0x0061ecf0
};

#define EMIT_STR(str) EmitLine(pOut, (str))
#define EMIT_FMT(fmt, ...) { String8 s_; EmitLine(pOut, String8_Format(&s_, EmptyAlloc(), fmt, __VA_ARGS__)->mpBegin); }

// @ 0x0061ecf0
bool cEventDisplay::Show(IEventSink* pOut) {
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
    String8* strs = (String8*)data;
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

// ---------------------------------------------------------------------------------------------
// cFeedManager.  Primary base occupies 0x00..0x37, the Messaging::IHandler subobject sits at
// +0x38 (see the -0x38 adjustments in HandleMessage).  Own fields start at +0x3c.
// ---------------------------------------------------------------------------------------------
struct Base0 {
  virtual void b0();
  char pad[0x34];
};

namespace EA { namespace Messaging {
struct IHandler {
  virtual ~IHandler();
  virtual bool HandleMessage(uint32_t messageID, void* pMessage);
};
}}  // namespace EA::Messaging

struct cFeedManager : Base0, EA::Messaging::IHandler {
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

// A work-item / job object handed around by the Pollinator subsystem.
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

// @ 0x0061f3a0
void cFeedManager::OnPoll(void* pFeed) {
  if (pFeed != 0) {
    ((FBool_V)Vt(pFeed)[6])(pFeed);         // +0x18
    void* req = EA_Allocate(0x214, "Pollinator", 0, 0, 0, 0);
    if (req == 0) {
      req = 0;
    } else {
      // construct the Pollinator request (its ctor is vtable slot 0)
      ((void(__thiscall*)(void*))Vt(req)[0])(req);
      Job* job = 0;
      void* mgr = JobManager();
      if (job) { Job* old = job; job = 0; old->GetStatus(); }
      bool ok = ((FBool_VP)Vt(mgr)[4])(mgr, &job);   // +0x10
      if (ok) {
        job->AddRequest(req);
        int n = ((FInt_VPV)Vt(pFeed)[17])(pFeed, (char*)req + 0xc, 0x104);  // +0x44
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
    int r = ((FInt_VPV)Vt(pFeed)[18])(pFeed, (char*)this + 0x70, 0x104);  // +0x48
    if (r == 0) {
      *(uint32_t*)((char*)this + 0x70) = 0x4c554e3c;  // "<NUL"
      *(uint16_t*)((char*)this + 0x74) = 0x3e4c;      // "L>"
      *((uint8_t*)this + 0x76) = 0;
    }
    if (req) ((FReq_V)Vt(req)[1])(req);
  }
  EnterCriticalSection((char*)this + 0x48);
  mBusy = 0;
  LeaveCriticalSection((char*)this + 0x48);
}

// @ 0x0061f530
bool cFeedManager::Pump(void* pA) {
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
bool cFeedManager::Load(void* arg) {
  char path[0x220];
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
  char marker[0x18];
  marker[0] = 0;
  FUN_0061e430(marker, path);
  if (!(*(bool(__thiscall*)(void*, void*))Vt(mpOut)[15])(mpOut, marker)) goto fail;  // +0x3c
  if (!((FBool_VIIII)Vt(mpStream)[19])(mpStream, 3, 3, 1, 0)) goto fail;             // +0x4c

  {
    const char* pat = "<event>";
    uint32_t patLen = 0;
    { const char* p = pat; while (*p++) ++patLen; }
    char*   strBeg = (char*)0x1667bac;   // empty-string global (masked)
    char*   strEnd;
    if (patLen + 1 > 1) {
      strBeg = (char*)EA_Allocate(patLen + 1, "Editor", 0, 0,
                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                  0xd1);
      strEnd = strBeg + patLen + 1;
    } else {
      strEnd = strBeg + 1;
    }
    for (uint32_t i = 0; i < patLen; ++i) strBeg[i] = pat[i];
    strBeg[patLen] = 0;
    // (the original builds this through eastl::vector<bool,...>::DoInsertValue; masked target)
    FUN_0061eba0();
    FUN_0061ec30();

    char readbuf[0x400];
    uint32_t total = 0;
    uint32_t got = ((FUInt_VPV)Vt(mpOut)[12])(mpOut, readbuf, 0x400);  // +0x30
    int found = 0;
    while (got > 0) {
      for (uint32_t i = 0; i < got; ++i) {
        if (strBeg[total + i - total] == readbuf[i]) {
          ++total;
          if (total == patLen) { found = (int)(i + 1); break; }
        } else {
          total = 0;
        }
      }
      got = ((FUInt_VPV)Vt(mpOut)[12])(mpOut, readbuf, 0x400);
    }
    if (found == 0) goto fail;
    if (!((FBool_VI)Vt(mpStream)[8])(mpStream, found)) goto fail;      // +0x20
    if (!((FBool_VII)Vt(mpOut)[10])(mpOut, 0, 0)) goto fail;           // +0x28
    for (;;) { if (((FUInt_VPV)Vt(mpOut)[12])(mpOut, readbuf, 0x400) == 0) break; }
    ((FInt_V)Vt(mpStream)[6])(mpStream);                              // +0x18
    EA_Free(strBeg);
    return true;
  }
fail:
  if (mpOut) ((FInt_V)Vt(mpOut)[6])(mpOut);
  File_Remove(path);
  if (mpStream) { void* p = mpStream; mpStream = 0; RefRelease(p); }
  if (mpOut)    { void* p = mpOut;    mpOut = 0;    RefRelease(p); }
  return false;
}

// @ 0x0061f9f0
bool cFeedManager::StartJob() {
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
void cFeedManager::Init() {
  mFlag69 = 1;
  EA::Messaging::IHandler* h = this;
  MsgListener(MessageServer(), h, 0x44db12e, -9999);
  MsgListener(MessageServer(), h, 0x685f4af, -9999);
  if (CheckA()) DoB();
  StartJob();
}

// @ 0x0061fb50
bool cFeedManager::HandleMessage(uint32_t messageID, void* pMessage) {
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
bool cFeedManager::Dispatch2(uint32_t, void*) {
  return StartJob();
}
