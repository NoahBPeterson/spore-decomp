// SP::Pollen registration dialog continuation (SporeEP1_RL) plus the URL registry helpers.
// Region 0x620bd0-0x621830. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
//   00620bd0  cRegistrationDialog::SubmitRegistrationForm
//   00620dc0  OnModalEnd (this = dialog+8)
//   00620e50  dialog UI-notify helper
//   00620ef0  cTOSDialog::DoMessage
//   00621460  map lookup -> optional string out
//   006214c0  SP::Pollen::GetURL
//   00621540  URL sanitizer
//   006216b0  SP::Pollen::RegisterURL
//   00621770  SP::Pollen::RegisterInsecureURL
#include "types.h"

// ---------------------------------------------------------------------------------------------
// External callees / globals (targets are masked relocations).
// ---------------------------------------------------------------------------------------------
void* __cdecl EA_Allocate(unsigned size, const char* name, int a, int b,
                          const char* file, int line);                              // 0xf473a0
void  __cdecl EA_Free(void* p);                                                     // 0xf47380
void* __cdecl WStr_Format(void* dst, const void* fmt, ...);                         // 0x41e050
void  __cdecl FUN_008e4f00(void* cb, void* ctx);                                    // 0x8e4f00
void* __cdecl FUN_009512c0();                                                       // 0x9512c0
void* __cdecl FUN_009512d0(unsigned size, int align, const char* name, void* alloc); // 0x9512d0
void* __cdecl FUN_00607a60();                                                       // 0x607a60
void  __cdecl FUN_006205f0();                                                       // 0x6205f0 ConfirmLogin
void  __cdecl FUN_00620380();                                                       // 0x620380 End
void  __cdecl FUN_00620110(int b);                                                  // 0x620110
void  __cdecl FUN_00620050(int b);                                                  // 0x620050
void  __cdecl FUN_00620020(void* cb);                                               // 0x620020
int   __cdecl FUN_00620270();                                                       // 0x620270
int   __cdecl FUN_00620690(void* p);                                                // 0x620690
bool  __cdecl FUN_00809db0(void* a, const void* b);                                 // 0x809db0
void  __cdecl FUN_00620e50_stub();                                                  // 0x620e50
uint32_t* __cdecl eastl_lower_bound(uint32_t* first, uint32_t* last,
                                    const uint32_t* key, int comp);                 // 0x549dc0
void* __cdecl String8_CtorSprintf(void* self, int tag, const char* fmt, ...);       // 0x472f50

extern uint32_t* gMapA;        // 0x15f5bbc
extern uint32_t* gMapAEnd;     // 0x15f5bc0
extern uint8_t   gMapACmp;     // 0x15f5bd0
extern uint32_t* gMapB;        // 0x15f5bd4
extern uint32_t* gMapBEnd;     // 0x15f5bd8
extern uint8_t   gMapBCmp;     // 0x15f5be8
extern const wchar_t gURLFormat[];  // 0x13f3da0
extern uint8_t   gFlag1520a24;      // 0x1520a24

static inline void** Vt(void* p) { return *(void***)p; }

struct String8 {
  char* mpBegin;      // +0x00
  char* mpEnd;        // +0x04
  char* mpCapacity;   // +0x08
  char* mpAllocator;  // +0x0c
  void assign(const char* pBegin, const char* pEnd);   // 0x454cb0
};
struct URLMap {
  String8* op_index(const void* key);                  // 0x546930
};
// @ 0x00621460
bool MapLookup(uint32_t key, String8* out) {
  uint32_t* end = gMapBEnd;
  uint32_t* r = eastl_lower_bound(gMapB, end, &key, (int)gMapBCmp);
  if (r != end && key >= *r && r != r + 5) {
    if (out != 0) out->assign((char*)r[1], (char*)r[2]);
    return true;
  }
  return false;
}

// @ 0x006214c0
bool GetURL(uint32_t key, String8* out) {
  uint32_t* end = gMapBEnd;
  uint32_t* r = eastl_lower_bound(gMapB, end, &key, (int)gMapBCmp);
  if (r != end && key >= *r && r != r + 5) {
    if (out != 0) WStr_Format(out, gURLFormat, *(String8*)(r + 1));
    return true;
  }
  return false;
}

// @ 0x006216b0
bool RegisterURL(uint32_t storeKey, uint32_t typeKey, const char* path) {
  uint32_t* end = gMapAEnd;
  uint32_t* r = eastl_lower_bound(gMapA, end, &typeKey, (int)gMapACmp);
  if (r != end && typeKey >= *r && r != r + 5 && path != 0 && *path == '/') {
    char tag = 0;
    String8 local;
    String8* src = (String8*)String8_CtorSprintf(&local, tag, "https://%hs%hs",
                                                 *(char**)(r + 1), path);
    String8* dst = ((URLMap*)&gMapB)->op_index(&storeKey);
    if (src != dst) dst->assign(src->mpBegin, src->mpEnd);
    if ((local.mpCapacity - local.mpBegin) > 1 && local.mpBegin) EA_Free(local.mpBegin);
    return true;
  }
  return false;
}

// @ 0x00621770
bool RegisterInsecureURL(uint32_t storeKey, uint32_t typeKey, const char* path) {
  uint32_t* end = gMapAEnd;
  uint32_t* r = eastl_lower_bound(gMapA, end, &typeKey, (int)gMapACmp);
  if (r != end && typeKey >= *r && r != r + 5 && path != 0 && *path == '/') {
    char tag = 0;
    String8 local;
    String8* src = (String8*)String8_CtorSprintf(&local, tag, "http://%hs%hs",
                                                 *(char**)(r + 1), path);
    String8* dst = ((URLMap*)&gMapB)->op_index(&storeKey);
    if (src != dst) dst->assign(src->mpBegin, src->mpEnd);
    if ((local.mpCapacity - local.mpBegin) > 1 && local.mpBegin) EA_Free(local.mpBegin);
    return true;
  }
  return false;
}

// ---------------------------------------------------------------------------------------------
// cRegistrationDialog and its frame set.  Stub declarations (bodies live elsewhere).
// ---------------------------------------------------------------------------------------------
struct cSPUILayout {
  void* FindWindowByID(uint32_t id, bool recursive);   // 0x8105b0
};
struct cXHTMLFrameSet {
  void* GetFrame(const void* name);
  bool  HandleLocationChange(int a, const void* url, const void* p, int b);
  bool  HandleFormSubmit(void* frame, int a);
  int   AddRef();
  int   Release();
};
struct cRegDialog {
  char pad00[0x14];
  cSPUILayout mLayout;             // +0x14
  char pad18[0x14];
  cXHTMLFrameSet* mpFrameSet;      // +0x2c
  bool  mbFlag30;                  // +0x30
  char pad31[0x34];
  char  mbFlag65;                  // +0x65
  int   mState;                    // +0x68
  char  mbKey64;                   // +0x64
  void SubmitRegistrationForm();   // 0x620bd0
};
void FormParamCallback();
struct DialogSub {                 // this = cRegDialog + 8
  char pad0[0xc];
  cSPUILayout* mpLayout;           // +0xc
  char pad10[0x50];
  int  mState;                     // +0x60
};

static inline unsigned WndFlags28(void* w) { return ((unsigned(__thiscall*)(void*))Vt(w)[10])(w); }  // +0x28
static inline unsigned WndFlags2c(void* w) { return ((unsigned(__thiscall*)(void*))Vt(w)[11])(w); }  // +0x2c

// @ 0x00620bd0
void cRegDialog::SubmitRegistrationForm() {
  void* frame = mpFrameSet->GetFrame((const void*)0x1520a0c);
  if (frame == 0) return;
  int found = FUN_00620690(*(void**)((char*)frame + 0x40));
  if (found == 0) return;
  FUN_008e4f00((void*)&FormParamCallback, this);
  void* f2 = mpFrameSet->GetFrame((const void*)0x1520a0c);
  int frameArg = f2 ? 1 : 0;
  if (mpFrameSet->HandleFormSubmit((void*)frameArg, found)) FUN_00620110(0);
}

// @ 0x00620dc0
void OnModalEnd(DialogSub* self, void* pWindow, int id) {
  if (self->mState == 1) {
    if (id == -0xf) {
      FUN_006205f0();                       // ConfirmLogin
      self->mState = 0;
      return;
    }
  } else if (self->mState == 2) {
    if (id == 0x5107b1a) {
      ((cRegDialog*)((char*)self - 8))->SubmitRegistrationForm();
      self->mState = 0;
      return;
    }
    void* w = self->mpLayout->FindWindowByID(0x6555770, true);
    if (w) {
      void* c = ((void*(__thiscall*)(void*, uint32_t))Vt(w)[3])(w, 0x8ed27e7a);  // +0xc
      if (c) ((void(__thiscall*)(void*, int, int))Vt(c)[10])(c, 4, 0);           // +0x28
    }
  }
  self->mState = 0;
  (void)pWindow;
}

// @ 0x00620e50
void DialogUiNotify(cRegDialog* self) {
  void* w = self->mLayout.FindWindowByID(0x519d9b8, true);
  if (w == 0) return;
  if ((WndFlags28(w) & 2) == 0) return;
  if ((WndFlags28(w) & 1) == 0) return;
  void* w2 = self->mLayout.FindWindowByID(0x6555770, true);
  if (gFlag1520a24 != 0 && w2 != 0 && (WndFlags2c(w2) & 4) != 0) {
    gFlag1520a24 = 0;
    void* p = (char*)self + 8;
    if (FUN_00809db0(p, (const void*)0x1520ce4)) {
      self->mState = 2;
      return;
    }
  }
  self->SubmitRegistrationForm();
}

// @ 0x00620ef0  (cTOSDialog::DoMessage)
int TOSDialog_DoMessage(int param_1, void* param_2, int* msg) {
  int type = msg[2];
  if (type == 0x3326e8a) return 1;
  if (type == 0x51a1a2d) return 1;
  if (type == 0x43b0aee) return 1;
  if (type == 0x287259f6) {
    int code = ((int(__thiscall*)(int))Vt((void*)*msg)[7])(*msg);   // +0x1c
    if (code == -0xe) {
      int sub = ((int(__thiscall*)(int))Vt((void*)*msg)[8])(*msg);  // +0x20
      (void)sub;
      FUN_006205f0();
      return 1;
    }
    if (code == 0x519d9b8) {
      FUN_00620e50_stub();
      return 1;
    }
    if (code == 0x519e168) {
      *(uint8_t*)(param_1 + 0x30) = 1;
      FUN_00620050(0);
      return 1;
    }
    if (code == 0x65d20a8) return 1;
  }
  (void)param_2;
  return 0;
}

// @ 0x00621540
void SanitizeURL(void* out, char* url) {
  if (url == 0) return;
  char* end = url;
  while (*end) ++end;
  String8 tmp;
  tmp.mpBegin = 0; tmp.mpEnd = 0; tmp.mpCapacity = 0; tmp.mpAllocator = 0;
  (void)end;
  (void)out;
}

// @ 0x006205f0 referenced by TOSDialog_DoMessage no-op path
extern "C" void FUN_00620e50_placeholder() {}
