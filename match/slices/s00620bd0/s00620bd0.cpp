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
#include <ctype.h>
#include <string.h>

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
void  __cdecl FUN_00620380();                                                       // 0x620380 End
void  __cdecl FUN_00620110(int b);                                                  // 0x620110
void  __cdecl FUN_00620050(int b);                                                  // 0x620050
void  __cdecl FUN_00620020(void* cb);                                               // 0x620020
int   __cdecl FUN_00620270();                                                       // 0x620270
void* __cdecl FUN_00620690(void* p);                                                // 0x620690
bool  __cdecl FUN_00809db0(void* a, const void* b);                                 // 0x809db0
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
// Eastl's shared empty-string dummy; both the narrow and the wide triad point at it.
extern char gEmptyString16[];                 // 0x01667bac
// Registration-form globals (frame/attribute/registry names).
extern const wchar_t* gMainFrameName;         // 0x01520a0c
extern const wchar_t* gRegistrationCodeName;  // 0x01520a1c
extern const wchar_t* gRegKeyDefault;         // 0x01520a04
extern const wchar_t* gRegKeyModal;           // 0x01520a08
extern const wchar_t* gTypeAttr;              // 0x013f36bc L"type"
extern const wchar_t* gNameAttr;              // 0x013f3868 L"name"
extern const wchar_t* gLineBreakSeq;          // 0x013faf54
extern const wchar_t* gSpaceSeq;              // 0x013ec468
// Modal-page state read by the registration code path.
struct cPropertySubList {
  uint32_t mPad00[0x46];        // +0x00..0x117
  uint32_t mModalActive;        // +0x118
};
struct cDirectPropertyList {
  uint32_t mPad00[0xf];         // +0x00..0x3b
  cPropertySubList* mpModalSub; // +0x3c
};
extern cDirectPropertyList* sAppProperties;   // 0x015fd918
// Wide string triad used for the registration code.
struct WString {
  wchar_t* mpBegin;      // +0x00
  wchar_t* mpEnd;        // +0x04
  wchar_t* mpCapacity;   // +0x08
};
void* __cdecl WinXHTML_GetDocument(void* pFrame);                            // 0xcd8000
bool  __cdecl RegistryReadString(const wchar_t* pKey, WString* pOut);        // 0x6aba80
uint32_t __cdecl WString_Find(WString* pStr, const wchar_t* pFind, uint32_t pos);  // 0x608340
void __cdecl WString_Replace(WString* pStr, uint32_t pos, uint32_t n, const wchar_t* pText);  // 0x5f8f80
void __cdecl WString_MakeUpper(WString* pStr);                               // 0x606e60
void* __cdecl cXHTMLRegistrationHandler_Ctor(void* pSelf, void* pDoc, int kind,
                                             const wchar_t* pName);          // 0x6206f0
void  __cdecl FUN_008e45d0(const wchar_t* pAttr, const wchar_t* pValue, int add);  // 0x8e45d0
void  __cdecl FUN_008e4350(void* pControl);                                  // 0x8e4350
void* __cdecl Window_Construct(void* pObject);                               // 0x962a10
void  __cdecl FormControl_SetControl(void* pControl, void* pWindow);         // 0x8e4b60
void  __cdecl FUN_006201a0(bool enabled);                                    // 0x6201a0
extern const char gSchemeSeparators[];        // 0x013fce5c ":/\"
char* __cdecl eastl_find_first_not_of(const char* first, const char* last,
                                      const char* pBegin, const char* pEnd);  // 0x61df60
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
void String8_Erase(String8* self, int position, int n);   // 0x61e200
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
class cSPUILayout { public:
  void* FindWindowByID(uint32_t id, bool recursive);   // 0x8105b0
};
struct cXHTMLFrameSet {
  void* GetFrame(const void* name);
  bool  HandleLocationChange(int a, const void* url, const void* p, int b);
  bool  HandleFormSubmit(void* frame, void* pForm);
  int   AddRef();
  int   Release();
};
struct cRegDialog {
  char pad00[0x14];
  cSPUILayout mLayout;             // +0x14
  char pad18[0x14];
  cXHTMLFrameSet* mpFrameSet;      // +0x2c
  bool  mbFlag30;                  // +0x30
  char pad31[3];                   // +0x31..
  const char* mpGroupName;         // +0x34
  char pad38[0x18];                // +0x38..0x4f
  char pad50[4];                   // +0x50
  WString mCode;                   // +0x54 (begin/end/capacity)
  char pad60[4];                   // +0x60..0x63
  char  mbKey64;                   // +0x64
  char  mbFlag65;                  // +0x65
  char pad66[2];                   // +0x66..0x67
  int   mState;                    // +0x68
  void SubmitRegistrationForm();   // 0x620bd0
  void ConfirmLogin();             // 0x6205f0
  void DialogUiNotify();           // 0x620e50
};
void FormParamCallback();
struct DialogSub {                 // this = cRegDialog + 8
  char pad0[0xc];
  cSPUILayout mLayout;             // +0xc (embedded; FindWindowByID gets this = &mLayout)
  char pad10[0x53];
  int  mState;                     // +0x60
  void OnModalEnd(void* pWindow, int id);  // 0x620dc0
};

static inline unsigned WndFlags28(void* w) { return ((unsigned(__thiscall*)(void*))Vt(w)[10])(w); }  // +0x28
static inline unsigned WndFlags2c(void* w) { return ((unsigned(__thiscall*)(void*))Vt(w)[11])(w); }  // +0x2c

// @ 0x00620bd0
void cRegDialog::SubmitRegistrationForm() {
  void* pFrame = mpFrameSet->GetFrame(gMainFrameName);
  if (pFrame == 0) return;
  void* pDoc = WinXHTML_GetDocument(pFrame);
  if (pDoc == 0) return;
  void* pTagged = FUN_00620690(*(void**)((char*)pDoc + 0x40));
  if (pTagged == 0) return;

  WString code;
  code.mpBegin = (wchar_t*)gEmptyString16;
  code.mpEnd = code.mpBegin;
  code.mpCapacity = code.mpBegin + 1;

  const wchar_t* pKey = sAppProperties->mpModalSub->mModalActive ? gRegKeyModal : gRegKeyDefault;
  if (RegistryReadString(pKey, &code)) {
    uint32_t pos = WString_Find(&code, gLineBreakSeq, 0);
    while (pos != 0xffffffffu) {
      WString_Replace(&code, pos, 1, gSpaceSeq);
      pos = WString_Find(&code, gLineBreakSeq, 0);
    }
    WString_MakeUpper(&code);
    void* pHandler = EA_Allocate(0x50, "Pollinator/Registration/FormControl", 0, 0, 0, 0);
    void* pControl = pHandler ? cXHTMLRegistrationHandler_Ctor(pHandler, pDoc, 0x17,
                                                              gRegistrationCodeName) : 0;
    FUN_008e45d0(gTypeAttr, L"hidden", 1);
    FUN_008e45d0(gNameAttr, gRegistrationCodeName, 1);
    void* pWindow = FUN_009512d0(0x20c, 4, "UI/Registration/Window", FUN_009512c0());
    void* pIface = 0;
    if (pWindow) {
      void* pObj = Window_Construct(pWindow);
      if (pObj) pIface = (char*)pObj + 4;
    }
    ((void(__thiscall*)(void*, int, int))Vt(pIface)[0x7c / 4])(pIface, 1, 0);
    ((void(__thiscall*)(void*, const wchar_t*))Vt(pIface)[0x80 / 4])(pIface, code.mpBegin);
    FormControl_SetControl(pControl, pIface);
    FUN_008e4350(pControl);
  }

  FUN_008e4f00((void*)&FormParamCallback, this);
  void* pFrame2 = mpFrameSet->GetFrame(gMainFrameName);
  void* pFrameBody = pFrame2 ? (char*)pFrame2 + 4 : 0;
  if (mpFrameSet->HandleFormSubmit(pFrameBody, pTagged)) FUN_006201a0(false);
  if ((((char*)code.mpCapacity - (char*)code.mpBegin) & ~1) > 2 && code.mpBegin)
    operator delete[](code.mpBegin);
}

// @ 0x00620dc0
void DialogSub::OnModalEnd(void* pWindow, int id) {
  DialogSub* self = this;
  if (self->mState == 1) {
    if (id == -0xf) {
      ((cRegDialog*)((char*)self - 8))->ConfirmLogin();
    }
    self->mState = 0;
    return;
  }
  if (self->mState == 2) {
    if (id == 0x5107b1a) {
      ((cRegDialog*)((char*)self - 8))->SubmitRegistrationForm();
    } else {
      void* w = self->mLayout.FindWindowByID(0x6555770, true);
      if (w) {
        void* c = ((void*(__thiscall*)(void*, uint32_t))Vt(w)[3])(w, 0x8ed27e7a);  // +0xc
        if (c) ((void(__thiscall*)(void*, int, int))Vt(c)[10])(c, 4, 0);           // +0x28
      }
    }
    self->mState = 0;
  }
  (void)pWindow;
}

// @ 0x00620e50
void cRegDialog::DialogUiNotify() {
  cRegDialog* self = this;
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

// Terms-of-service dialog plumbing.
#define PV(n) virtual void _pv##n();
extern const char* gAuthFormat;                                        // 0x013ef064
struct ConfigManagerStub {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void SetSetting(uint32_t id, uint32_t value);   // +0x2c
};
ConfigManagerStub* ConfigManager();                                    // 0x67dd30
struct MessageServerStub {
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void Post(uint32_t id, uint32_t a, uint32_t b);  // +0x14
};
MessageServerStub* MessageServer();                                    // 0x67dcc0
bool  __cdecl FrameSet_HandleLocationChange(void* pFrameSet, int* pWindow, void* pDoc,
                                            const wchar_t* pName, int flag);  // 0x997730
void  __cdecl AnchorWindowToWindow(void* pTarget, void* pAnchor, int flags, int e);  // 0x807340
void* __cdecl cCancelConfirmationDialog_Ctor(void* pSelf);             // 0x6204b0
bool  __cdecl cCancelConfirmationDialog_Init(void* pSelf);             // 0x620270
void* __cdecl AutoRefCount_Ctor(void* pObject);                        // 0x572660
void  __cdecl WString_DeallocateSelf(WString* pStr);                   // 0x933960
void  operator delete[](void* p);                                      // 0xf47380
// Terms-of-service dialog object (same layout as cRegDialog).
struct cTOSDialog {
  int DoMessage(void* param_2, int* pMsg);   // 0x00620ef0
};

// Window slots used by the terms-of-service message handler.
static inline int WindowID(void* w) { return ((int(__thiscall*)(void*))Vt(w)[0x1c / 4])(w); }   // +0x1c
static inline int WindowSubID(void* w) { return ((int(__thiscall*)(void*))Vt(w)[0x20 / 4])(w); } // +0x20
static inline void WndSetState(void* w, int value) {                                    // +0x54
  ((void(__thiscall*)(void*, int))Vt(w)[0x54 / 4])(w, value);
}
static inline unsigned WndSubFlags(void* w) {                                           // +0x2c
  return ((unsigned(__thiscall*)(void*))Vt(w)[0x2c / 4])(w);
}
static inline void WndSetName(void* w, const char* pText) {                             // +0x18
  ((void(__thiscall*)(void*, const char*))Vt(w)[0x18 / 4])(w, pText);
}
static inline void WndSlot28(void* w, int value) {                                      // +0x28
  ((void(__thiscall*)(void*, int))Vt(w)[0x28 / 4])(w, value);
}
static inline void WndSlot48(void* w, int value) {                                      // +0x48
  ((void(__thiscall*)(void*, int))Vt(w)[0x48 / 4])(w, value);
}
static inline void WndSlot4c(void* w) {                                                 // +0x4c
  ((void(__thiscall*)(void*))Vt(w)[0x4c / 4])(w);
}
static inline void WndSetVisible(void* w, int part, int on) {                           // +0x7c
  ((void(__thiscall*)(void*, int, int))Vt(w)[0x7c / 4])(w, part, on);
}
static inline int MsgRelease(void* pMsg) {                                              // +0x04
  return ((int(__thiscall*)(void*))Vt(pMsg)[1])(pMsg);
}

// @ 0x00620ef0  (SP::Pollen::cTOSDialog::DoMessage)
int cTOSDialog::DoMessage(void* param_2, int* pMsg) {
  cRegDialog* self = (cRegDialog*)this;
  cSPUILayout* pLayout = &self->mLayout;
  int id = pMsg[2];

  if (id == 0x3326e8a) {
    return FrameSet_HandleLocationChange(self->mpFrameSet, (int*)pMsg[0], (void*)pMsg[6], 0, 0);
  }

  if (id == 0x51a1a2d) {
    void* pFrame = self->mpFrameSet->GetFrame(gMainFrameName);
    if (pFrame != 0 && (int*)((char*)pFrame + 4) != 0) WndSetVisible((char*)pFrame + 4, 1, 1);
    void* w = pLayout->FindWindowByID(0x451d381, true);
    if (w) WndSetVisible(w, 1, 0);
    void* pTagged = FUN_00620690(*(void**)(pMsg[6] + 0x40));
    if (pTagged == 0) {
      FUN_00620110(0);
      w = pLayout->FindWindowByID(0xfffffff2, true);
      if (w) WndSetVisible(w, 1, 0);
      w = pLayout->FindWindowByID(0x519d9b8, true);
      if (w) {
        WndSetState(w, 1);
        WndSetVisible(w, 2, 1);
      }
      w = pLayout->FindWindowByID(0x6555770, true);
      if (w && (WndSubFlags(w) & 4) != 0) {
        ConfigManager()->SetSetting(0x5de7b4a, 1);
        MessageServer()->Post(0x5de7b4a, 0, 0);
      }
      void* pAuth = FUN_00607a60();
      if (pAuth) {
        String8 name;
        String8 group;
        String8_CtorSprintf(&name, 0, gAuthFormat, self->mCode.mpBegin);
        String8_CtorSprintf(&group, 0, gAuthFormat, self->mpGroupName, name.mpBegin);
        WndSetName(pAuth, group.mpBegin);
        if ((group.mpCapacity - group.mpBegin) > 1 && group.mpBegin) operator delete[](group.mpBegin);
        if ((name.mpCapacity - name.mpBegin) > 1 && name.mpBegin) operator delete[](name.mpBegin);
        if (self->mCode.mpBegin != self->mCode.mpEnd) {
          *self->mCode.mpBegin = 0;
          self->mCode.mpEnd = self->mCode.mpBegin;
        }
        WndSlot28(pAuth, 1);
        WndSlot4c(pAuth);
        self->mbFlag30 = 0;
        return 1;
      }
    } else {
      w = pLayout->FindWindowByID(0x519d9b8, true);
      if (w) {
        WndSetVisible(w, 1, 1);
        WndSetState(w, 0);
      }
      w = pLayout->FindWindowByID(0x65d20a8, true);
      if (w) WndSetVisible(w, 1, 0);
      w = pLayout->FindWindowByID(0xfffffff2, true);
      if (w) WndSetState(w, (self->mbFlag65 != 0 ? 1 : 0) + 2);
      FUN_00620110(1);
      FUN_006201a0(true);
    }
    return 1;
  }

  if (id == 0x43b0aee) {
    void* w = pLayout->FindWindowByID(0x451d381, true);
    if (w) {
      void* pFrame = self->mpFrameSet->GetFrame(gMainFrameName);
      void* pFrameBody = pFrame ? (char*)pFrame + 4 : 0;
      AnchorWindowToWindow(pFrameBody, w, 0x300, 0);
      WndSetVisible(w, 1, 1);
      WndSetVisible((char*)pFrame + 4, 1, 0);
    }
    FUN_00620110(0);
    FUN_006201a0(true);
    w = pLayout->FindWindowByID(0x519d9b8, true);
    if (w) WndSetVisible(w, 1, 0);
    w = pLayout->FindWindowByID(0x65d20a8, true);
    if (w) WndSetVisible(w, 1, 1);
    w = pLayout->FindWindowByID(0xfffffff2, true);
    if (w) WndSetState(w, 2);
    return 1;
  }

  if (id == 0x287259f6) {
    void* pTarget = (void*)pMsg[0];
    int code = WindowID(pTarget);
    if (code == -0xe) {
      if (WindowSubID(pTarget) == 3) {
        void* pDialog = FUN_009512d0(0x24, 4, "UI/cCancelConfirmationDialog", FUN_009512c0());
        if (pDialog) pDialog = cCancelConfirmationDialog_Ctor(pDialog);
        AutoRefCount_Ctor(pDialog);
        if (cCancelConfirmationDialog_Init(pDialog)) {
          FUN_00620020((char*)self + 8);
          self->mState = 1;
          MsgRelease(pMsg);
          return 1;
        }
        MsgRelease(pMsg);
      }
      self->ConfirmLogin();
      return 1;
    }
    if (code == 0x519d9b8) {
      int sub = WindowSubID(pTarget);
      if (sub == 0) {
        self->DialogUiNotify();
      } else if (sub == 1) {
        FUN_00620380();
      }
      return 1;
    }
    if (code == 0x519e168) {
      self->mbFlag30 = 1;
      FUN_00620050(0);
      WndSlot48(FUN_00607a60(), 0);
      return 1;
    }
    if (code == 0x65d20a8) {
      WString url;
      url.mpBegin = (wchar_t*)gEmptyString16;
      url.mpEnd = url.mpBegin;
      url.mpCapacity = url.mpBegin + 1;
      GetURL(0x538766b, (String8*)&url);
      if (FrameSet_HandleLocationChange(self->mpFrameSet, 0, url.mpBegin, gMainFrameName, 1))
        FUN_006201a0(false);
      WString_DeallocateSelf(&url);
      return 1;
    }
    return 0;
  }

  if (id == 1) {
    if (pMsg[4] == 0xd && self->mbKey64 == 0) {
      self->mbKey64 = 1;
      self->DialogUiNotify();
      return 1;
    }
    if (pMsg[4] == 0x42) return 1;
  } else if (id == 2 && pMsg[4] == 0xd) {
    self->mbKey64 = 0;
    return 1;
  }
  return 0;
}

// @ 0x00621540
void SanitizeURL(uint32_t key, char* url) {
  if (url == 0) return;
  size_t len = strlen(url);
  String8 text;
  if (len + 1 <= 1) {
    text.mpBegin = gEmptyString16;
    text.mpCapacity = gEmptyString16 + 1;
  } else {
    text.mpBegin = (char*)EA_Allocate((unsigned)(len + 1), "Editor", 0, 0,
                                      "EASTL/allocator.h", 0xd1);
    text.mpCapacity = text.mpBegin + len + 1;
  }
  text.mpEnd = text.mpBegin;
  text.mpAllocator = 0;
  memcpy(text.mpBegin, url, len);
  text.mpEnd = text.mpBegin + len;
  *text.mpEnd = 0;
  char* first = eastl_find_first_not_of(text.mpBegin, text.mpEnd, gSchemeSeparators,
                                        gSchemeSeparators + 3);
  String8_Erase(&text, 0, first == text.mpEnd ? -1 : (int)(first - text.mpBegin));
  while (text.mpBegin != text.mpEnd) {
    if (isalnum((unsigned char)*(text.mpEnd - 1))) break;
    String8_Erase(&text, (int)(text.mpEnd - text.mpBegin) - 1, 1);
  }
  if (text.mpBegin != text.mpEnd) {
    String8* slot = ((URLMap*)&gMapB)->op_index(&key);
    if (slot != &text) slot->assign(text.mpBegin, text.mpEnd);
  }
  if ((text.mpCapacity - text.mpBegin) > 1 && text.mpBegin) EA_Free(text.mpBegin);
}

// @ 0x006205f0 referenced by TOSDialog_DoMessage no-op path
extern "C" void FUN_00620e50_placeholder() {}
