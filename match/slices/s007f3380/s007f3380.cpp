// Slice s007f3380: Sims3::UI IME composition / candidate-list / proxy methods.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <new>

#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]

// ---------------------------------------------------------------------------
// Sims3::UI::IMEComposition::HandleMessage: ecx is a secondary subobject whose
// primary object lives at this-0x658.
// ---------------------------------------------------------------------------
struct IMEComp {
  bool HandleMessage(int msg, void* arg);
};

// @ 0x007F36E0
bool IMEComp::HandleMessage(int msg, void* arg) {
  switch (msg) {
    case 0x2ac44c14: {
      void* s = (char*)this - 0x658;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x94))(s, *(int*)((char*)arg + 8));
      break;
    }
    case 0x2ac44c1a: {
      void* s = (char*)this - 0x658;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x98))(s, *(int*)((char*)arg + 8));
      break;
    }
    case 0x2ac44c1b: {
      void* s = (char*)this - 0x658;
      ((void(__thiscall*)(void*))VSLOT(s, 0x8c))(s);
      break;
    }
    default:
      break;
  }
  return true;
}

// ---------------------------------------------------------------------------
// Sims3::UI::IMECandidateList::HandleMessage: primary object at this-0x20c.
// ---------------------------------------------------------------------------
struct IMECand {
  bool HandleMessage(int msg, void* arg);
};

// @ 0x007F4170
bool IMECand::HandleMessage(int msg, void* arg) {
  switch (msg) {
    case 0x2ac44ed8: {
      void* s = (char*)this - 0x20c;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x88))(s, *(int*)((char*)arg + 8));
      break;
    }
    case 0x2ac44ef0: {
      void* s = (char*)this - 0x20c;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x8c))(s, *(int*)((char*)arg + 8));
      break;
    }
    default:
      break;
  }
  return true;
}

// ---------------------------------------------------------------------------
// 0x007F3BE0: push a subobject value through its vtable.
// ---------------------------------------------------------------------------
struct SubObj {
  void* Get();
};

struct IMEComp3 {
  char pad[0x20c];
  SubObj mSub;  // +0x20c
  void Helper(int param);
};

// @ 0x007F3BE0
void IMEComp3::Helper(int param) {
  if (param) {
    SubObj* p = &mSub;
    void* r = p->Get();
    ((void(__thiscall*)(void*, void*, int))VSLOT(p, 0x8c))(p, r, 1);
  }
}

// ---------------------------------------------------------------------------
// Sims3::UI::IMEProxy::Shutdown.
// ---------------------------------------------------------------------------
struct IMEProxy2 {
  char pad0[8];
  bool mbInitialized;          // +0x08
  char pad1[7];
  void* mpMessageServer;       // +0x10
  char pad2[0xc];
  void* mpIMEServer;           // +0x20
  void* mpWinMgr;              // +0x24
  char pad3[8];
  void* mpWinComposition;      // +0x30
  char pad4[8];
  void* mpWinCandidateList;    // +0x3c
  void ShutdownCandidateList();
  void ShutdownCandidateListImpl();
  void ShutdownComposition();
  bool Shutdown();
};

// @ 0x007F4250
bool IMEProxy2::Shutdown() {
  if (!mbInitialized) return true;
  bool hasCand = mpWinCandidateList != 0;
  mbInitialized = false;
  if (hasCand) ShutdownCandidateList();
  if (mpWinComposition) ShutdownComposition();
  ((void(__thiscall*)(void*, int))VSLOT(mpIMEServer, 0x14))(mpIMEServer, 0);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44c0e, 0xffffd8f1);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44c11, 0xffffd8f1);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44ed1, 0xffffd8f1);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44ed4, 0xffffd8f1);
  return true;
}

// ---------------------------------------------------------------------------
// 0x007F3B00 - static text-size helper.
// ---------------------------------------------------------------------------
struct TS {
  void LayoutLine(int text, int style, float a, float b, int len);
  void* GetLineLayout();
};

// @ 0x007F3B00
void* CalculateTextSize(void* out, int text, int style, int len, void* typesetter) {
  if (text != 0 && len != 0) {
    TS* ts = (TS*)typesetter;
    ts->LayoutLine(text, style, 0.0f, 0.0f, len);
    char* ll = (char*)ts->GetLineLayout();
    *(float*)out = *(float*)(ll + 0x98);
    *(float*)((char*)out + 4) = *(float*)(ll + 0xa0) - *(float*)(ll + 0xa4);
    return out;
  }
  *(float*)out = 0.0f;
  *(float*)((char*)out + 4) = 0.0f;
  return out;
}

// ---------------------------------------------------------------------------
// 0x007F3A90 - IMEComposition::SetWindowColors.
// ---------------------------------------------------------------------------
struct IMECompColors {
  char pad0[4];
  char mAt4[4];        // +0x04 (subobject with a vtable)
  char pad1[0x20c - 8];
  char mAt20c[4];      // +0x20c (subobject with a vtable)
  char pad2[0x6a8 - 0x210];
  int c6a8;            // +0x6a8
  int c6ac;            // +0x6ac
  int c6b0;            // +0x6b0
  int c6b4;            // +0x6b4
  void SetWindowColors();
};

// @ 0x007F3A90
void IMECompColors::SetWindowColors() {
  char* p = mAt20c;
  c6ac = (int)0xff000000;
  c6b0 = (int)0xff000000;
  c6a8 = 0xffffffff;
  c6b4 = 0xff0000f0;
  ((void(__thiscall*)(void*, int, int))VSLOT(p, 0x20))(p, 0, (int)0xff000000);
  ((void(__thiscall*)(void*, int, int))VSLOT(p, 0x20))(p, 1, (int)0xffefefef);
  ((void(__thiscall*)(void*, int))VSLOT(mAt4, 0xac))(mAt4, -1);
}

// ---------------------------------------------------------------------------
// 0x007F3B70 - IMEComposition::OnChar.
// ---------------------------------------------------------------------------
extern void* UTFWinGetMgr();

struct IMEC {
  char pad[0x68c];
  void* p68c;   // +0x68c
  bool OnChar(int, unsigned short ch);
};

// @ 0x007F3B70
bool IMEC::OnChar(int, unsigned short ch) {
  if (p68c) {
    struct L {
      int a;
      int b;
      int ch;
      int c;
    } l;
    l.a = 5;
    l.b = 0;
    l.ch = ch;
    l.c = 0;
    void* mgr = UTFWinGetMgr();
    ((void(__thiscall*)(void*, int, void*, void*, int))VSLOT(mgr, 0x10))(
        mgr, 0, (char*)p68c + 4, &l, 0);
    ((void(__thiscall*)(void*))VSLOT(this, 0x8c))(this);
  }
  return true;
}

// @ 0x007F3380
void IMEProxy2::ShutdownCandidateListImpl() {
  if (mpWinCandidateList != 0) {
    void* cand4 = (char*)mpWinCandidateList + 4;
    void* r = ((void*(__thiscall*)(void*))VSLOT(mpWinMgr, 4))(mpWinMgr);
    ((void(__thiscall*)(void*))VSLOT(mpWinCandidateList, 0x1c))(mpWinCandidateList);
    ((void(__thiscall*)(void*, void*))VSLOT(r, 0xdc))(r, cand4);
    void* p = mpWinCandidateList;
    if (p != 0) {
      mpWinCandidateList = 0;
      ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
    }
  }
}

// ===========================================================================
// Remaining slice functions: skeletons (partial.txt).
// ===========================================================================

// @ 0x007F33D0  Sims3::UI::IMEComposition::Init (506 bytes)
void IMECompositionInit(void* self, int a, int b) {
  (void)self;
  (void)a;
  (void)b;
}

// @ 0x007F35D0  Sims3::UI::IMEComposition::Shutdown (271 bytes)
void IMECompositionShutdown(void* self) {
  (void)self;
}

// @ 0x007F3750  IMEComposition message/font handler (832 bytes)
void IMECompositionBig(void* self, int a, int b) {
  (void)self;
  (void)a;
  (void)b;
}

// @ 0x007F3C10  Sims3::UI::IMECandidateList::IMECandidateList
void IMECandidateListCtor(void* self) {
  (void)self;
}

// @ 0x007F3CC0  Sims3::UI::IMECandidateList::~IMECandidateList
void IMECandidateListDtor(void* self) {
  (void)self;
}

// @ 0x007F3D20  IMECandidateList paint/layout (880 bytes)
void IMECandidateListPaint(void* self, int a, int b) {
  (void)self;
  (void)a;
  (void)b;
}

// @ 0x007F4090  Sims3::UI::IMECandidateList::Shutdown (211 bytes)
void IMECandidateListShutdown(void* self) {
  (void)self;
}

// @ 0x007F4200  IMECandidateList-like scalar deleting destructor
void IMECandidateListScalarDtor(void* self, unsigned flags) {
  (void)self;
  (void)flags;
}
