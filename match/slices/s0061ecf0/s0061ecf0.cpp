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
void  __cdecl String8_Dtor(void* self);                                             // 0x530670
void* __cdecl String8_CtorSprintf(void* self, int tag, const char* fmt, ...);       // 0x472f50
void  __cdecl EmitLine(void* pOut, const void* str);                                // 0x61dea0
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
struct EVariant {
  void*    mpValue;       // +0x00
  uint32_t mPad04;
  uint32_t mCount;        // +0x08
  uint32_t mPad0c;
  uint8_t  mFlags;        // +0x10
  uint8_t  mPad11;
  uint16_t mArrayCount;   // +0x12
  uint16_t mPad14;
  uint16_t mPad16;
  uint16_t mType;         // +0x16
};

struct cEventDisplay {
  uint32_t mPad00[3];
  int      mVerb;         // +0x0c
  uint32_t mAsset0;       // +0x10
  uint32_t mAsset1;       // +0x14
  DateTime mDate;         // +0x18 (8 bytes)
  EVariant mVariant;      // +0x20

  bool Show(void* pOut);  // 0x0061ecf0
};

// Helper used by every switch arm: format one value into a temporary eastl::string and emit it.
static void EmitFormatted(void* pOut, const char* fmt, ...) {
  char strbuf[16];
  void* s = String8_CtorSprintf(strbuf, 0, fmt, 0);
  EmitLine(pOut, *(void**)s);
  String8_Dtor(strbuf);
}

// @ 0x0061ecf0
bool cEventDisplay::Show(void* pOut) {
  char buf[0x100];
  int  n;
  if (mAsset0 == 0 && mAsset1 == 0) {
    int p10 = mDate.GetParameter(10);
    int p9  = mDate.GetParameter(9);
    int p8  = mDate.GetParameter(8);
    int p6  = mDate.GetParameter(6);
    int p2  = mDate.GetParameter(2);
    int p1  = mDate.GetParameter(1);
    Sprintf8(buf, "<event verb (0x%08x), timestamp: %04u-%02u-%02u %02u:%02u:%02u>",
             mVerb, p1, p2, p6, p8, p9, p10);
    n = 0x3e;
  } else {
    int p10 = mDate.GetParameter(10);
    int p9  = mDate.GetParameter(9);
    int p8  = mDate.GetParameter(8);
    int p6  = mDate.GetParameter(6);
    int p2  = mDate.GetParameter(2);
    int p1  = mDate.GetParameter(1);
    Sprintf8(buf, "<event verb (0x%08x), assetid (0x%08x:%08x) %04u-%02u-%02u %02u:%02u:%02u>",
             mVerb, mAsset0, mAsset1, p1, p2, p6, p8, p9, p10);
    n = 0x5b;
  }
  if (!((FBool_VPV)Vt(pOut)[14])(pOut, buf, n)) return false;

  uint32_t count;
  uint32_t data;
  if ((mVariant.mFlags & 0x30) == 0) {
    if (mVariant.mArrayCount == 0) goto done;
    count = 1;
    data  = (uint32_t)&mVariant;
  } else {
    count = mVariant.mCount;
    if (count == 0) goto done;
    data  = (uint32_t)mVariant.mpValue;
  }
  for (uint32_t i = 0; i < count; ++i) {
    uint32_t base = data;
    switch (mVariant.mType) {
      case 1:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<bool>", 0)) goto fail;
        EmitLine(pOut, mVariant.mpValue);
        break;
      case 5:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<arg>", 0)) goto fail;
        EmitFormatted(pOut, "%I8d", (int)*(char*)(base + i));
        break;
      case 6:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<arg>", 0)) goto fail;
        EmitFormatted(pOut, "%I8u", (unsigned)*(uint8_t*)(base + i));
        break;
      case 7:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<arg>", 0)) goto fail;
        EmitFormatted(pOut, "%I16d", (int)*(int16_t*)(base + i * 2));
        break;
      case 8:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<arg>", 0)) goto fail;
        EmitFormatted(pOut, "%I16u", (unsigned)*(uint16_t*)(base + i * 2));
        break;
      case 9:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<arg>", 0)) goto fail;
        EmitFormatted(pOut, "%I32d", *(int*)(base + i * 4));
        break;
      case 10:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<arg>", 0)) goto fail;
        EmitFormatted(pOut, "%I32u", *(unsigned*)(base + i * 4));
        break;
      case 11:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<arg>", 0)) goto fail;
        EmitFormatted(pOut, "%I64d", *(int*)(base + i * 8));
        break;
      case 12:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<arg>", 0)) goto fail;
        EmitFormatted(pOut, "%I64u", *(unsigned*)(base + i * 8));
        break;
      case 13:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<arg>", 0)) goto fail;
        EmitFormatted(pOut, "%f", (double)*(float*)(base + i * 4));
        break;
      case 14:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<arg>", 0)) goto fail;
        EmitFormatted(pOut, "%f", *(double*)(base + i * 8));
        break;
      case 0x12:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<string>", 0)) goto fail;
        EmitLine(pOut, mVariant.mpValue);
        break;
      case 0x13:
        if (!((FBool_VPV)Vt(pOut)[14])(pOut, "<string>", 0)) goto fail;
        EmitFormatted(pOut, "%ls", mVariant.mpValue);
        break;
      default:
        break;
    }
    if (!((FBool_V)Vt(pOut)[14])(pOut)) goto fail;
    continue;
  fail:
    return false;
  }
done:
  return ((FBool_VPV)Vt(pOut)[14])(pOut, "<event>", 0);
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
      if (((cEventDisplay*)data)->Show(mpOut)) {
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
