// SP::cSPPlayModePhotoBrowser helpers / EASTL instantiations. Region 0x630750-0x631b90.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>

typedef void (__thiscall *TF0)(void*);
typedef void (__thiscall *TF1)(void*, int);

extern "C" void* __cdecl EA_Allocate(unsigned size, const char* name, int a, int b, const char* file, int line);
extern "C" void  __cdecl FUN_00f47380(void*);   // 0x00f47380 operator delete[]
#define EA_Free FUN_00f47380
extern void* gVt13fe518;    // 0x13fe518
extern void* gVt13fe528;    // 0x13fe528
extern void* gVt13ec458;    // 0x13ec458

struct RefObj { virtual void s0(); virtual void s1(); virtual void s2(); };

// @ 0x00630750  basic_string<wchar_t> ctor from [first,last)
struct WStr {
  short* begin; short* end; short* cap;
  void AllocateSelf(int n);
  void Append(const short* first, const short* last);
};
void* __fastcall FUN_00630750(void* self, short* /*unused edx arg*/, short* first, short* last, int /*unused*/) {
  // Retail ignores the edx argument and reads its [first,last) pair from the
  // two stack parameters ([esp+4] and [esp+8]), popping three stack dwords.
  WStr* s = (WStr*)self;
  s->begin = 0; s->end = 0; s->cap = 0;
  int n = ((char*)last - (char*)first) >> 1;
  s->AllocateSelf(n + 1);
  short* dst = s->begin;
  memcpy(dst, first, n * 2);
  short* e = dst + n;
  s->end = e;
  *e = 0;
  return self;
}

// @ 0x006307a0
extern "C" void __cdecl RBTreeInsert(void* node, void* pos, void* root, char b);
void __fastcall FUN_006307a0(void* self, int* out, int* pos, unsigned* val, char flag) {
  char* s = (char*)self;
  char b;
  if (flag == 0 && pos != (int*)(s + 4) && *val >= *(unsigned*)((char*)pos + 0x10))
    b = 1;
  else
    b = 0;
  char* node = (char*)EA_Allocate(0x24, "Editor", 0, 0,
                                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  if (node + 0x10 != 0) {
    *(unsigned*)(node + 0x10) = val[0];
    *(unsigned*)(node + 0x14) = val[1];
    *(unsigned*)(node + 0x18) = val[2];
    *(unsigned*)(node + 0x1c) = val[3];
    *(unsigned*)(node + 0x20) = val[4];
  }
  RBTreeInsert(node, pos, s + 4, b);
  ++*(int*)(s + 0x14);
  *out = (int)node;
}

// @ 0x006308d0
struct Job { void GetStatus(); };
void* __fastcall FUN_006308d0(void* self, char flag) {
  char* s = (char*)self;
  *(void**)s = (void*)&gVt13fe518;
  {
    void* p = *(void**)(s + 0x34);
    if (p != 0) ((Job*)p)->GetStatus();
  }
  {
    void* p = *(void**)(s + 0x30);
    if (p != 0) ((Job*)p)->GetStatus();
  }
  {
    void* p = *(void**)(s + 0x20);
    unsigned n = (*(unsigned*)(s + 0x28) - (unsigned)p) & 0xfffffffe;
    if (n > 2 && p != 0) EA_Free(p);
  }
  *(void**)s = (void*)&gVt13ec458;
  if (flag & 1) EA_Free(s);
  return self;
}

// @ 0x006309e0
void* __cdecl FUN_006309e0(void* out, const short* lhs, const WStr* rhs) {
  const short* p = lhs;
  while (*p) ++p;
  int n = (int)(p - lhs);
  int len = (int)(rhs->end - rhs->begin) >> 1;
  WStr* o = (WStr*)out;
  o->begin = 0; o->end = 0; o->cap = 0;
  int total = len + n;
  o->AllocateSelf(total + 1);
  *o->end = 0;
  o->Append(lhs, lhs + n);
  o->Append(rhs->begin, rhs->end);
  return out;
}

// @ 0x00630a50
struct Ent24 { int f0, f4, f8, fc, f10, f14, f18, f1c, f20; };
void __fastcall FUN_00630a50(void* self) {
  // Build the reusable sub-object pointer first and recover the base from it;
  // this keeps the object base in eax, so the void return still leaves eax =
  // self like the retail function does.
  char* p = (char*)self;
  p += 0x6c;
  char* a = p - 0x6c;
  *(void**)a = (void*)&gVt13fe528;
  *(int*)(a + 4) = 0;
  *(int*)(a + 8) = 0;
  *(int*)(a + 0xc) = 0;
  *(int*)(a + 0x18) = 0;
  *(unsigned char*)(a + 0x20) = 0;
  *(int*)(a + 0x28) = 0;
  *(int*)(a + 0x2c) = 0;
  *(int*)(a + 0x30) = 0;
  *(int*)(a + 0x50) = 0;
  *(int*)(a + 0x54) = 0;
  *(int*)(p + 4) = 0;
  *(int*)(p + 8) = 0;
  *(int*)(p + 0xc) = 0;
  *(void**)p = (void*)p;
  *(int*)(a + 0x70) = (int)p;
  *(int*)(a + 0x74) = 0;
  *(unsigned char*)(a + 0x78) = 0;
  *(int*)(a + 0x7c) = 0;
  p = a + 0x84;
  for (int i = 0x62; i >= 0; --i) {
    *(int*)(p + 0x00) = 0;
    *(int*)(p + 0x04) = 0;
    *(int*)(p + 0x08) = 0;
    *(int*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    *(int*)(p + 0x1c) = 0;
    *(int*)(p + 0x20) = 0;
    p += 0x24;
  }
  *(int*)(a + 0xe70) = 0;
  *(int*)(a + 0xe74) = 4;
  *(int*)(a + 0xe78) = 0;
  *(int*)(a + 0xe7c) = 0;
  *(int*)(a + 0xe80) = 0;
  *(int*)(a + 0xe8c) = 0;
  *(int*)(a + 0xe90) = 0;
  *(int*)(a + 0xe94) = 0;
  *(int*)(a + 0xe98) = 0;
  *(int*)(a + 0xe9c) = 0;
  *(int*)(a + 0xea0) = 0;
  *(int*)(a + 0xea8) = 0;
}

// @ 0x00630b30
void __fastcall FUN_00630b30(void* self, int* pos, int* val) {
  int* v = (int*)self;
  int* end = (int*)v[1];
  if (end != (int*)v[2]) {
    int* src = val;
    if (val >= pos && val < end) src = val + 1;
    if (end != 0) *end = end[-1];
    unsigned n = (unsigned)((char*)(v[1] - 1) - (char*)pos);
    memmove((char*)v[1] - ((int)n >> 2) * 4, pos, n);
    *pos = *src;
    v[1] += 1;
    return;
  }
  int cap = (int)((char*)end - (char*)v[0]) >> 2;
  if (cap == 0) cap = 1; else cap *= 2;
  int* dst;
  if (cap == 0) dst = 0;
  else dst = (int*)EA_Allocate(cap * 4, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  unsigned n1 = (unsigned)((char*)pos - (char*)v[0]);
  int* p = (int*)((char*)dst + ((int)n1 >> 2) * 4);
  if (p != 0) *p = *val;
  int* oldEnd = (int*)v[1];
  memmove(p + 1, pos, (char*)oldEnd - (char*)pos);
  if (v[0] != 0 && *(int*)((char*)v[0] - 4) != 0) EA_Free((void*)v[0]);
  v[0] = (int)dst;
  v[1] = (int)((char*)p + 4 + (((char*)oldEnd - (char*)pos) >> 2) * 4);
  v[2] = (int)((char*)dst + cap * 4);
}



// ---------------------------------------------------------------------------
// Target functions: browser teardown, photo-count refresh, send-email window
// and the file-name parser.  Layout offsets are the retail object's.
// ---------------------------------------------------------------------------
extern short gEmpty16[];          // 0x01667bac eastl::gEmptyString16 (1 wchar + sentinel)
extern void* gVt13eb394;          // 0x013eb394 base-vtable after teardown
extern void* g_015f7cf4;          // 0x015f7cf4 photo-browser UI stats singleton
extern int   g_01523310;          // 0x01523310 raster group id

static inline void** VTw(void* p) { return *(void***)p; }
static inline void FreeArray(void* p) { if (p && *(int*)((char*)p - 4)) EA_Free(p); }
static inline void ReleaseObj(void* p) { if (p) ((RefObj*)p)->s1(); }

// 16-byte eastl wide string with the retail inline empty-string init
struct WStrI {
  short* begin; short* end; short* cap; void* alloc;
  void initEmpty() { begin = gEmpty16; end = gEmpty16; cap = gEmpty16 + 1; }
  void destroy() {
    if ((((int)((char*)cap - (char*)begin)) & ~1) > 2 && begin) EA_Free(begin);
  }
  WStrI* Substr(WStrI* out, unsigned pos, unsigned n);              // 0x00453d20
  WStrI* Assign(const short* first, const short* last);             // 0x00423650
  int    Compare(unsigned pos, unsigned n, const short* p) const;   // 0x00630690
  unsigned FindFirstOf(const short* set, unsigned pos) const;       // 0x00630630
  void   Erase(unsigned pos, unsigned n);                           // 0x004228e0
  void   RangeInit(const short* p);                                 // 0x00579a90
};

// SP::cString (EASTL wide string owner used by the localized-label helpers)
struct CString16 {
  short* begin; short* end; short* cap; void* alloc;
  void ctor();                                                   // 0x006b5060
  void ctor(uint32_t a, uint32_t b, const short* text);          // 0x006b5770
  char Load(uint32_t a, uint32_t b, const short* text);          // 0x006b54b0
  short* GetText();                                              // 0x006b55c0
  void dtor();                                                   // 0x006b5240
};

struct PlayModeUI {                                              // owner at this+0x24
  void* FindEditorUIWindow(unsigned id);                         // 0x00634e40
  void* FindPlayModeUIWindow(unsigned id);                       // 0x00634dc0
  void  SetSendEmailDialogVisibility(char b);                    // 0x00635400
  void  SetEditorUIGroupVisible(unsigned id, char b);            // 0x00635790
  void  SetEditorUIEnabled(unsigned id, char b);                 // 0x00634f20
  void  SetEditorText(unsigned id, const short** text);          // 0x00635010
};

struct UIHints {
  char pad[0x4c];
  int  f4c;                                                      // +0x4c
  void UpdateHints(char a, char b);                              // 0x0067c350
  int  SetFlag(int a, int b);                                    // 0x0067c420
};
UIHints* __cdecl FUN_0067cac0();                                 // 0x0067cac0
void*    __cdecl FUN_0067dd60();                                 // 0x0067dd60
char     __cdecl FUN_008068d0(void* w, int obj, int flag);       // 0x008068d0
void*    __fastcall GetImageFromRaster(void* self, void* edx, void* raster); // 0x006300d0
void     __cdecl FUN_006b8f00(const void* s, void* out);         // 0x006b8f00
void*    __cdecl FUN_00607a60();                                 // 0x00607a60 SP::Pollen::AuthManager
void     __cdecl SPUIHelpers_BeginModal(void* w, int a, int b);  // 0x008099a0
void*    __cdecl MessageServer();                                // 0x0067dcc0
void     __cdecl WStrFormat(WStrI* out, const short* fmt, ...);  // 0x0041e050
const short* __cdecl FindLastOf(const short* pEnd, const short* pBegin,
                                const short* setBegin, const short* setEnd);  // 0x005728f0
struct AutoRefIV { void* mpObject; };                            // 0x00b5f950 Assign (thiscall)
void* __fastcall FUN_00b5f950(void* self, void* edx, void* p);   // 0x00b5f950
void  __fastcall FUN_009a9600(void* self, void* edx, void* n);   // 0x009a9600 rbtree DoNukeSubtree
void  __fastcall FUN_005c7f10(void* self);                       // 0x005c7f10 vector dtor

// @ 0x00630930  cSPPlayModePhotoBrowser::~cSPPlayModePhotoBrowser
void __fastcall FUN_00630930(void* self) {
  char* a = (char*)self;
  *(void**)a = (void*)&gVt13fe528;
  char* p = a + 0xea4;
  for (int i = 4; i >= 0; --i) {
    void* o = *(void**)(p - 4);
    p -= 4;
    ReleaseObj(o);
  }
  FreeArray(*(void**)(a + 0xe78));
  char* q = a + 0xe70;
  for (int i = 0x62; i >= 0; --i) {
    void* o = *(void**)(q - 0x24);
    q -= 0x24;
    FreeArray(o);
  }
  FUN_009a9600(a + 0x68, 0, *(void**)(a + 0x74));
  FreeArray(*(void**)(a + 0x28));
  FUN_005c7f10(a + 4);
  *(void**)a = (void*)&gVt13eb394;
}

// @ 0x00630d10  cSPPlayModePhotoBrowser::UpdatePhotoCountText
static inline int PhotoCount(char* a) {
  return (int)(*(int**)(a + 8) - *(int**)(a + 4));
}
static inline void SetTextW(void* w, const short* s) {
  ((void (__thiscall*)(void*, const short*))VTw(w)[0x80 / 4])(w, s);
}

void __fastcall FUN_00630d10(void* self) {
  char* const esi = (char*)self;
  CString16 label;
  label.ctor();
  void* w = ((PlayModeUI*)*(void**)(esi + 0x24))->FindEditorUIWindow(0x3f6c990);
  if (w != 0) {
    label.Load(0x7518573e, 0x4587552, (const short*)0x13fe548);
    ((int*)g_015f7cf4)[4] = *(int*)(esi + 0x1c) + 1;
    ((int*)g_015f7cf4)[5] = PhotoCount(esi);
    SetTextW(w, label.GetText());
  }

  w = ((PlayModeUI*)*(void**)(esi + 0x24))->FindEditorUIWindow(0x4474410);
  if (w != 0) {
    WStrI text;
    text.initEmpty();
    WStrFormat(&text, (const short*)0x13f01bc, PhotoCount(esi));
    SetTextW(w, text.begin);
    text.destroy();
  }

  w = ((PlayModeUI*)*(void**)(esi + 0x24))->FindPlayModeUIWindow(0x4463820);
  if (w != 0) {
    WStrI text;
    text.initEmpty();
    WStrFormat(&text, (const short*)0x13f01bc, PhotoCount(esi));
    SetTextW(w, text.begin);
    text.destroy();
  }

  w = ((PlayModeUI*)*(void**)(esi + 0x24))->FindPlayModeUIWindow(0x447ca18);
  if (w != 0) {
    label.Load(0x7518573e, 0x456f912, (const short*)0x13fe530);
    int const count = PhotoCount(esi);
    if ((unsigned)count == 0) {
      ((int*)g_015f7cf4)[2] = 1;
      ((int*)g_015f7cf4)[3] = 1;
    } else {
      ((int*)g_015f7cf4)[2] = (int)((unsigned)*(int*)(esi + 0x18) / 5) + 1;
      ((int*)g_015f7cf4)[3] = (int)((unsigned)(count - 1) / 5) + 1;
    }
    SetTextW(w, label.GetText());
  }
  label.dtor();
}

// @ 0x00630f20  cSPPlayModePhotoBrowser::ShowSendEmailWindow
void __fastcall FUN_00630f20(void* self) {
  char* const a = (char*)self;
  PlayModeUI* const ui = *(PlayModeUI**)(a + 0x24);

  if (FUN_0067cac0()->f4c != 0)
    FUN_0067cac0()->UpdateHints(0, 1);

  void* w = ui->FindEditorUIWindow(0x3ffb8cc);
  if (w != 0) {
    AutoRefIV view;
    view.mpObject = 0;
    unsigned const index = *(unsigned*)(a + 0x1c);
    int const count = (int)(*(int**)(a + 8) - *(int**)(a + 4));
    void* photo = 0;
    if (index < (unsigned)count)
      photo = *(void**)(*(int*)(a + 4) + index * 4);
    if (photo != 0) {
      void* const mgr = FUN_0067dd60();
      void* const image = ((void* (__thiscall*)(void*, int, int, int))VTw(mgr)[0x20 / 4])
                            (mgr, *(int*)((char*)photo + 0xc), g_01523310, 0);
      if (image == 0)
        return;
      void* const mgr2 = FUN_0067dd60();
      ((void (__thiscall*)(void*, void*))VTw(mgr2)[0x68 / 4])(mgr2, image);
      FUN_00b5f950(&view, 0, GetImageFromRaster(a, 0, image));
      FUN_008068d0(w, (int)view.mpObject, -1);
      ReleaseObj(view.mpObject);
    } else {
      FUN_008068d0(w, 0, -1);
    }
  }

  w = ui->FindEditorUIWindow(0x3f67620);
  if (w != 0) {
    ((void (__thiscall*)(void*, int, int))VTw(w)[0x7c / 4])(w, 1, 1);
    ui->SetSendEmailDialogVisibility(1);
    SPUIHelpers_BeginModal(w, 0, 0);
    FUN_0067cac0()->SetFlag(0, 1);
  }

  void* const auth = FUN_00607a60();
  WStrI addr;
  addr.initEmpty();
  FUN_006b8f00(*(void**)((void* (__thiscall*)(void*))VTw(auth)[0x30 / 4])(auth), &addr);
  w = ui->FindEditorUIWindow(0x4581d50);
  ((void (__thiscall*)(void*, const short*))VTw(w)[0x80 / 4])(w, addr.begin);

  CString16 emailLabel;
  emailLabel.ctor();
  w = ui->FindEditorUIWindow(0x45adfc8);
  if (w != 0) {
    emailLabel.Load(0x7518573e, 0x45ad5b9, (const short*)L"*Email a Friend*");
    ((void (__thiscall*)(void*, const short*))VTw(w)[0x80 / 4])(w, emailLabel.GetText());
  }
  w = ui->FindEditorUIWindow(0x45ae078);
  if (w != 0) {
    emailLabel.Load(0x7518573e, 0x45ad62f, (const short*)L"*Your Email*");
    ((void (__thiscall*)(void*, const short*))VTw(w)[0x80 / 4])(w, emailLabel.GetText());
  }
  w = ui->FindEditorUIWindow(0x45ae090);
  if (w != 0) {
    emailLabel.Load(0x7518573e, 0x45ad634, (const short*)L"*Recipient's Email*");
    ((void (__thiscall*)(void*, const short*))VTw(w)[0x80 / 4])(w, emailLabel.GetText());
  }
  w = ui->FindEditorUIWindow(0x45ae0c0);
  if (w != 0) {
    emailLabel.Load(0x7518573e, 0x45ad63a, (const short*)L"*Your Message*");
    ((void (__thiscall*)(void*, const short*))VTw(w)[0x80 / 4])(w, emailLabel.GetText());
  }

  FUN_00630d10(a);

  ui->SetEditorUIGroupVisible(0x447c4e8, 1);
  ui->SetEditorUIGroupVisible(0x447c040, 1);
  ui->SetEditorUIGroupVisible(0x447b968, 1);
  ui->SetEditorUIGroupVisible(0x447b980, 1);
  ui->SetEditorUIGroupVisible(0x3f6c990, 1);
  ui->SetEditorUIGroupVisible(0x56be960, 0);
  ui->SetEditorUIEnabled(0x56be960, 0);
  ui->SetEditorUIGroupVisible(0x3f67720, 1);
  if (*(int*)(a + 8) - *(int*)(a + 4) != 0)
    ui->SetEditorUIEnabled(0x3f67720, 1);

  CString16 subjectLabel;
  subjectLabel.ctor(0x7518573e, 0x56bce10, 0);
  {
    WStrI text;
    text.begin = 0; text.end = 0; text.cap = 0;
    text.RangeInit(subjectLabel.GetText());
    ui->SetEditorText(0x4581d90, (const short**)&text);
    text.destroy();
  }
  {
    void* const ms = MessageServer();
    ((void (__thiscall*)(void*, int, int, int))VTw(ms)[0x14 / 4])(ms, 0x52f180, 0x20, 0);
  }
  subjectLabel.dtor();
  emailLabel.dtor();
  addr.destroy();
}

// @ 0x006312f0  parse "prefix-<hex>.ext" style photo file names

// @ 0x006312f0  parse "<name>-<hex>.<ext>" and return 1 when the name is "CRE"
// msvcr90!swscanf through its IAT slot (hex-named global so difftest resolves it)
extern "C" int (__cdecl* const g_013cc4e0)(const wchar_t* s, const wchar_t* fmt, ...);

char __stdcall FUN_006312f0(short* sBegin, short* sEnd, short* sCap, void* sAlloc,
                            unsigned* outHex, int* outCode, WStrI* outPath) {
  WStrI& mid = *(WStrI*)&sBegin;     // the 4 string dwords arrive by value on the stack
  (void)sAlloc;
  WStrI ext;
  WStrI num;
  ext.initEmpty();
  num.initEmpty();
  char ok = 1;
  unsigned const len = (unsigned)(sEnd - sBegin);

  // extension: 3 chars after the last '.', then drop ".ext" from the working copy
  if (len == 0) {
    ok = 0;
  } else {
    const short* p = FindLastOf(sEnd, sBegin, (const short*)0x13f5ca8, (const short*)0x13f5caa);
    if (p == sBegin) {
      ok = 0;
    } else {
      int const i = (int)(p - sBegin) - 1;
      if (i == -1) {
        ok = 0;
      } else {
        WStrI tmp;
        tmp.initEmpty();
        WStrI* const r = mid.Substr(&tmp, (unsigned)(i + 1), 3);
        ext.Assign(r->begin, r->end);
        tmp.destroy();
        mid.Erase((unsigned)i, 0xffffffff);
      }
    }
  }

  // "ful"/"sml" after the last '_'
  int uscore = -1;
  if (len != 0) {
    const short* p = FindLastOf(sEnd, sBegin, (const short*)0x13fe614, (const short*)0x13fe616);
    if (p != sBegin)
      uscore = (int)(p - sBegin) - 1;
  }
  if (ok && uscore != -1) {
    if (mid.Compare((unsigned)(uscore + 1), 3, (const short*)0x13fe60c) == 0)
      *outCode = 0x417b3a7;
    else if (mid.Compare((unsigned)(uscore + 1), 3, (const short*)0x13fe604) == 0)
      *outCode = 0x417b3bc;
    else
      ok = 0;
    if (ok) {
      mid.Erase((unsigned)uscore, 0xffffffff);
      const short* const expect = (*outCode == 0x417b3a7) ? (const short*)0x13f8ef4
                                                         : (const short*)0x13f8f14;
      if (mid.Compare(0, 3, expect) != 0)
        ok = 0;
    }
  } else {
    ok = 0;
  }

  // hex tail after the last '-'
  int dash = -1;
  if (len != 0) {
    const short* p = FindLastOf(sEnd, sBegin, (const short*)0x13faf54, (const short*)0x13faf56);
    if (p != sBegin)
      dash = (int)(p - sBegin) - 1;
  }
  if (ok && dash != -1) {
    WStrI tail;
    tail.initEmpty();
    WStrI* const r = mid.Substr(&tail, (unsigned)(dash + 1), 8);
    num.Assign(r->begin, r->end);
    tail.destroy();
    WStrI tmp;
    tmp.initEmpty();
    FUN_006309e0(&tmp, (const short*)0x13fe5fc, (const WStr*)&num);
    num.Assign(tmp.begin, tmp.end);
    tmp.destroy();
    g_013cc4e0((const wchar_t*)num.begin, (const wchar_t*)0x13fe5f4, outHex);
    mid.Erase((unsigned)dash, 0xffffffff);
  } else {
    ok = 0;
  }

  // remainder after the first '_' goes to outPath
  int const first = (int)mid.FindFirstOf((const short*)0x13fe614, 0);
  if (ok && first != -1) {
    unsigned n = 0;
    while (sBegin[n] != 0)
      ++n;
    WStrI rest;
    rest.initEmpty();
    WStrI* const r = mid.Substr(&rest, (unsigned)(first + 1), n - (unsigned)first);
    WStrI tmp;
    tmp.initEmpty();
    tmp.Assign(r->begin, r->end);
    r->destroy();
    WStrFormat(outPath, (const short*)0x13f5c04, tmp);
    tmp.destroy();
    mid.Erase((unsigned)first, 0xffffffff);
    ok = ((int)len == 3) && (mid.Compare(0, 3, (const short*)0x13fe5ec) == 0);
  } else {
    ok = 0;
  }

  ext.destroy();
  num.destroy();
  if ((((int)((char*)sCap - (char*)sBegin)) & ~1) > 2 && sBegin)
    EA_Free(sBegin);
  return ok;
}
