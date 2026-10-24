// Slice s0065bf20: SP::cSPUIFeedEditAssetView / SP::cSPUIFeedEdit and helpers.
// Retail layouts are accessed by offset from `this`; function bodies follow the
// annotated disassembly.  Matching functions are the small/table-driven ones.
#include "types.h"
#include <intrin.h>

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" __declspec(dllimport) unsigned int __cdecl strlen(const char* p);
extern "C" __declspec(dllimport) int wcsncmp(const wchar_t*, const wchar_t*, unsigned int);
extern "C" __declspec(dllimport) wchar_t* wcsstr(const wchar_t*, const wchar_t*);

typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void(__thiscall* FnPi)(void*, int);
typedef void*(__thiscall* FnRetP)(void*);
typedef void*(__thiscall* FnRetPi)(void*, unsigned int);
typedef int(__thiscall* FnRetI)(void*);
typedef int(__thiscall* FnRetI2)(void*, void*);

// extra calling-convention shapes used by the 0x0065bf20 message handler
typedef void(__thiscall* FnTh1)(void*, void*);
typedef void(__thiscall* FnTh2)(void*, int, int);
typedef void(__thiscall* FnTh2p)(void*, void*, int);
typedef void(__thiscall* FnTh3v)(void*, int, void*, int);
typedef void(__thiscall* FnTh3)(void*, int, void*, int);
typedef bool(__thiscall* FnThKeyOut)(void*, unsigned long long, void*);
typedef bool(__thiscall* FnThKey)(void*, unsigned long long);
typedef bool(__thiscall* FnThKeyIB)(void*, unsigned long long, int);
typedef bool(__thiscall* FnThMgr)(void*, void*, int, int, int, int, int);
typedef unsigned int(__thiscall* FnThRfind)(void*, const char*, unsigned int, unsigned int);
typedef void(__thiscall* FnThErase)(void*, unsigned int);
typedef void(__thiscall* FnThDtor)(void*);
typedef void*(__cdecl* FnRetP0)();
typedef bool(__cdecl* FnCallout)(void*, void*);
typedef char(__cdecl* FnExtract)(const wchar_t*, void*);
typedef int(__cdecl* FnSprintf)(void*, const char*, const wchar_t*);
typedef unsigned long long(__cdecl* FnStrto)(const wchar_t*, int, int);

// 12-byte scratch records passed to the extracted helpers.
struct WStr3 { void* a; void* b; void* c; };
struct Key12 { int a; int b; int c; };

// Load virtual slot `off` from object `o`: [o] is the vtable pointer.
static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }

class cSPUILayout { public:
  void Shutdown(int a);
  void* FindWindowByID(uint32_t id, bool recursive);
};
struct cXHTMLFrameSet {
  void* GetFrame(uint32_t id);
  bool HandleLocationChange(void* win, const wchar_t* url, void* a, int b);   // 0x00997730
  bool HandleFormSubmit(void* win, void* form);                              // 0x009978b0
  void FUN_00997140();
};

// ---- external callees / globals ----
float GetElapsedSeconds(); // 0x00805080
void SetWindowImage(void* w, uint32_t* key, int flags);
void* FUN_0067de40();                                  // 0x0067de40
void* MessageServer();                                 // 0x0067dcc0
void MessageServer_Unsub(void* h, uint32_t id, int y); // 0x0067dcc0 (equiv t2)
void MessageServer_Post(uint32_t id, void* p, int n);
void* FUN_0067cb30();                                  // 0x0067cb30
void* GetManager();                                    // 0x0067dcd0
void GetURL(int a, void* b);                           // 0x006214c0
void FormatI64(void* out, const wchar_t* fmt, int a, int b);
char FUN_0065be20(const wchar_t* path, void* out);     // 0x0065be20
int FUN_00472fe0(void* str, const char* fmt, const wchar_t* w); // 0x00472fe0
bool UI_CalloutMessageBox(void* owner, void* text);    // 0x00809db0
unsigned long long StrtoU64(const void* p, int a, int b); // 0x0092d710

// thiscall externals modelled as members so the ABI matches exactly.
struct WString {                                       // 12-byte eastl wstring
  void* a; void* b; void* c;
  void DeallocateSelf();                               // 0x00933960
};
struct eastl_cstring_h {                               // eastl::basic_string<char>
  unsigned int rfind(const char* s, unsigned int pos, unsigned int n); // 0x0065bcb0
  void erase(unsigned int pos);                        // 0x0061e200
};
struct FeedDir {                                       // SP::Pollen::cAssetDirectory
  bool GetLocalKey(unsigned long long key, void* out); // 0x0054e460
  bool IsPending(unsigned long long key);              // 0x0054e740
  bool FUN_0054ed50(int lo, int hi, char one);         // 0x0054ed50
};
struct FeedResMgr {                                    // EA::ResourceMan manager
  bool FUN_0067dcd0out(void* out, int, int, int, int, int); // 0x0067dcd0 vtbl slot
};
struct FeedBrowser {                                   // SP::cSPUIAssetWebBrowser
  void FUN_005ff180(void* p);                          // 0x005ff180
  void FUN_0065b440(int lo, int hi);                   // 0x0065b440
};
struct FeedDir3 {                                      // Dir
  void FUN_006108a0(int lo, int hi);                   // 0x006108a0
};
extern const wchar_t* g_sporecast;            // 0x01526580
extern const wchar_t* g_unsubscribe;          // 0x01526584
extern const wchar_t* g_asset;                // 0x01526588
extern const wchar_t* g_spore;                // 0x01526594
extern const wchar_t* g_sporeprofile;         // 0x01526590
extern const wchar_t* g_blank;
extern unsigned int g_nSporecast;             // 0x015fa2b8
extern unsigned int g_nUnsub;                 // 0x015fa22c
extern unsigned int g_nAsset;                 // 0x015fa2a0
extern unsigned int g_nSpore;                 // 0x015fa2b4
extern unsigned int g_nProfile;               // 0x015fa3f4
extern int g_15fa6e4;
extern void* g_vt_13fff3c;
extern void* g_vt_13fff2c;
extern void* g_vt_13ec458;

// Same entry point as FUN_0065c9a0, declared with the raw integer result so the
// caller returns eax unchanged instead of zero-extending a bool.  __fastcall puts
// self in ecx (the callee's `this`) and the window on the stack, matching __thiscall;
// edx is an unused dummy.
int __fastcall FUN_0065c9a0_int(void* self, void* dummy, void* win); // 0x0065c9a0

// --- globals referenced by 0x0065bf20 (address = symbol) ---
extern wchar_t g_01667bac;                 // empty wstring begin        @ 0x01667bac
extern wchar_t g_01667bae;                 // empty wstring capacity     @ 0x01667bae
extern char g_015268fc;                    // CalloutMessageBox text     @ 0x015268fc
extern char g_01526908;                    // CalloutMessageBox text     @ 0x01526908
extern char g_01526914;                    // CalloutMessageBox text     @ 0x01526914
extern char g_01526920;                    // CalloutMessageBox text     @ 0x01526920
extern char g_0152692c;                    // CalloutMessageBox text     @ 0x0152692c
extern char g_01526938;                    // CalloutMessageBox text     @ 0x01526938

// inline wcslen equivalent used by the handler (original inlines the loop)
static inline unsigned int wcslen_(const wchar_t* s) {
  const wchar_t* e = s;
  while (*e) ++e;
  return (unsigned int)(e - s);
}
// clear an eastl::cstring (begin/end/capacity triple) in place
static inline void clear_str(void* cstr) {
  char** f = (char**)cstr;
  if (f[0] != f[1]) {
    *f[0] = 0;
    f[1] = f[0];
  }
}

namespace eastl {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
inline unsigned int CharStrlen(const char* p) { return strlen(p); }
class allocator { public:};
class cstring {
 public:
  char* mpBegin; char* mpEnd; char* mpCapacity; allocator mAllocator;
};
}

// ===========================================================================
// cSPUIFeedEditAssetView
// ===========================================================================
class cSPUIFeedEditAssetView {
 public:
  uint32_t mPad00[5];          // +0x00..+0x13
  void* mpWindow_14;           // +0x14
  void* mpWindow_18;           // +0x18
  void* mpWindow_1c;           // +0x1c
  void* mpWindow_20;           // +0x20
  void* mpWindow_24;           // +0x24
  void* mpWindow_28;           // +0x28
  void* mpAsset_2c;            // +0x2c
  int mnMode_30;               // +0x30
  uint32_t mPad34;             // +0x34
  int mnAssetA_38;             // +0x38
  int mnAssetB_3c;             // +0x3c
  int mnMsgField_40;           // +0x40
  int mnState_44;              // +0x44
  float mfModeTime_48;         // +0x48

  cSPUIFeedEditAssetView* FUN_0065c480(int v);
  uint32_t GetEventMask() const;
  void GetThumbnailBackdrop(uint32_t* out, unsigned int id) const;
  void SetMode(int mode);
  bool FUN_0065c9a0(void* win);
  int FUN_0065cec0(void* msg, void* data);
  void FUN_0065cf30(int a, int b, int c, int* asset);
};

// @ 0x0065c480
cSPUIFeedEditAssetView* cSPUIFeedEditAssetView::FUN_0065c480(int v) {
  *(int*)((char*)this + 8) = v;
  return this;
}

// @ 0x0065c6f0
uint32_t cSPUIFeedEditAssetView::GetEventMask() const {
  return (uint32_t)(*(int*)((char*)this + 0x44)) | 0xfffffffd;
}

// @ 0x0065c490
void cSPUIFeedEditAssetView::GetThumbnailBackdrop(uint32_t* out, unsigned int id) const {
  uint32_t* dst = out;
  unsigned int key = id;
  dst[0] = 0;
  dst[1] = 0x2f7d0004;
  dst[2] = 0xca14de92;
  switch (key) {
    case 0x2090a11b: dst[0] = 0x14585a1f; break;
    case 0x1f2a25b6: dst[0] = 0x71981adc; break;
    case 0x1a4e0708: dst[0] = 0x188ebff2; break;
    case 0x2a5147a9: dst[0] = 0x62b8bc1; break;
    case 0x37148141: dst[0] = 0xda273036; break;
    case 0x372e2c04: dst[0] = 0x3f185edb; break;
    case 0x449c040f: dst[0] = 0xe4d0e7f3; break;
    case 0x441cd3e6: dst[0] = 0xe7792790; break;
    case 0x47c10953: dst[0] = 0x62e861d9; break;
    case 0x4e3f7777: dst[0] = 0x8c1f0aa3; break;
    case 0x4178b8e8: dst[0] = 0x89b74761; break;
    case 0x65672ade: dst[0] = 0x89b74761; break;
    case 0x72c49181: dst[0] = 0xd1376095; break;
    case 0x7d433fad: dst[0] = 0x6920384d; break;
    case 0x8f963dcb: dst[0] = 0xc2d3ce6f; break;
    case 0x98e03c0d: dst[0] = 0x7609745a; break;
    case 0x99e92f05: dst[0] = 0xb390f699; break;
    case 0x9ad7d4aa: dst[0] = 0xb6dc61a6; break;
    case 0x9ea3031a: dst[0] = 0xe04dd8b1; break;
    case 0xb8669ec9: dst[0] = 0x9fe7f178; break;
    case 0xbc1041e6: dst[0] = 0xa0cc166e; break;
    case 0xbcd73e89: dst[0] = 0x945e2516; break;
    case 0xbdd15f3d: dst[0] = 0x8c1f0aa3; break;
    case 0xc0b74287: dst[0] = 0x6920384d; break;
    case 0xc15695da: dst[0] = 0xf6eb7174; break;
    case 0xccc35c46: dst[0] = 0xdc1b3879; break;
    case 0xdfad9f51: dst[0] = 0xb49e7fb2; break;
    case 0xf670aa43: dst[0] = 0xf5f1b0d7; break;
  }
  __asm { mov eax, dst }
}

// @ 0x0065c730
__declspec(noinline) void FindChar(const wchar_t* p1, const wchar_t* p2, const wchar_t* c) {
  if (p1 != p2) {
    do {
      if (*p1 == *c)
        return;
      ++p1;
    } while (p1 != p2);
  }
}

struct CtorObj {
  void** vt; void** vt4; int m08; char pad0c[4]; void* m10; void* m14; void* m18; int m1c;
  void FUN_0065c790(void* a, void* b, void* c);
};
// @ 0x0065c790
void CtorObj::FUN_0065c790(void* a, void* b, void* c) {
  CtorObj* self = this;
  self->vt4 = &g_vt_13ec458;
  self->m08 = 0;
  self->m10 = a;
  self->m14 = b;
  self->vt = &g_vt_13fff3c;
  self->vt4 = &g_vt_13fff2c;
  self->m18 = c;
  self->m1c = 0;
  __asm { mov eax, ecx }
}

// @ 0x0065c840
void cSPUIFeedEditAssetView::SetMode(int mode) {
  if (mode == 1) {
    mfModeTime_48 = 0.0f;
    (*(FnP2)Vslot(mpWindow_1c, 0x7c))(mpWindow_1c, 1, 1);
    (*(FnP2)Vslot(mpWindow_20, 0x7c))(mpWindow_20, 1, 1);
    (*(FnP2)Vslot(mpWindow_24, 0x7c))(mpWindow_24, 1, 0);
    (*(FnP2)Vslot(mpWindow_28, 0x7c))(mpWindow_28, 1, 0);
    (*(FnP2)Vslot(mpWindow_18, 0x7c))(mpWindow_18, 1, 0);
  } else if (mode == 2) {
    mfModeTime_48 = GetElapsedSeconds();
    (*(FnP2)Vslot(mpWindow_1c, 0x7c))(mpWindow_1c, 1, 1);
    (*(FnP2)Vslot(mpWindow_20, 0x7c))(mpWindow_20, 1, 1);
    (*(FnP2)Vslot(mpWindow_24, 0x7c))(mpWindow_24, 1, 1);
    (*(FnP2)Vslot(mpWindow_28, 0x7c))(mpWindow_28, 1, 0);
    (*(FnP2)Vslot(mpWindow_18, 0x7c))(mpWindow_18, 1, 0);
    if (mpWindow_14 && mnState_44 == 0) {
      mnState_44 = 2;
      (*(FnPv)Vslot(mpWindow_14, 0x104))(mpWindow_14, this);
    }
  } else if (mode == 3) {
    mfModeTime_48 = 0.0f;
    (*(FnP2)Vslot(mpWindow_1c, 0x7c))(mpWindow_1c, 1, 1);
    (*(FnP2)Vslot(mpWindow_20, 0x7c))(mpWindow_20, 1, 1);
    (*(FnP2)Vslot(mpWindow_24, 0x7c))(mpWindow_24, 1, 1);
    (*(FnP2)Vslot(mpWindow_28, 0x7c))(mpWindow_28, 1, 0);
    (*(FnP2)Vslot(mpWindow_18, 0x7c))(mpWindow_18, 1, 1);
  } else {
    mfModeTime_48 = 0.0f;
    (*(FnP2)Vslot(mpWindow_1c, 0x7c))(mpWindow_1c, 1, 0);
    (*(FnP2)Vslot(mpWindow_20, 0x7c))(mpWindow_20, 1, 0);
    (*(FnP2)Vslot(mpWindow_24, 0x7c))(mpWindow_24, 1, 0);
    (*(FnP2)Vslot(mpWindow_28, 0x7c))(mpWindow_28, 1, 1);
    (*(FnP2)Vslot(mpWindow_18, 0x7c))(mpWindow_18, 1, 0);
  }
  (*(FnP)Vslot(mpWindow_14, 0x90))(mpWindow_14);
  mnMode_30 = mode;
}

// @ 0x0065c9a0
bool cSPUIFeedEditAssetView::FUN_0065c9a0(void* win) {
  char* p = (char*)this;
  if (win == *(void**)(p + 0x14) && *(int*)(p + 0x30) == 2 && 0.0f < *(float*)(p + 0x48)) {
    float now = (float)(int)GetElapsedSeconds();
    if (0.35f < now - *(float*)(p + 0x48)) {
      SetMode(1);
      if (*(void**)(p + 0x14) && *(int*)(p + 0x44)) {
        *(int*)(p + 0x44) = 0;
        (*(FnPv)Vslot(*(void**)(p + 0x14), 0x104))((void*)*(void**)(p + 0x14), this);
      }
    }
  }
  return false;
}

// @ 0x0065cec0
int cSPUIFeedEditAssetView::FUN_0065cec0(void* msg, void* data) {
  struct MsgData { uint32_t pad00[2]; int id; };
  int id = ((MsgData*)data)->id;
  if (id == 7) {
    struct S { uint32_t pad00[2]; int a; int b; int c; uint32_t pad14; void* e; } s;
    s.c = mnMsgField_40;
    s.e = mpWindow_14;
    s.a = 0x17;
    s.b = 0x590cb98;
    int r = (*(FnRetI2)Vslot(msg, 0x114))(msg, &s);
    return (r & 0xffffff00) | 1;
  }
  if (id == 0xc)
    return FUN_0065c9a0_int(this, 0, msg);
  if (id == 0x11)
    ++g_15fa6e4;
  return id & 0xffffff00;
}

// @ 0x0065cf30
void cSPUIFeedEditAssetView::FUN_0065cf30(int a, int b, int c, int* asset) {
  if (!asset) {
    __asm { xor al, al }
    return;
  }
  void* q = (*(FnRetP)Vslot(mpWindow_1c, 0xa8))(mpWindow_1c);
  if (!q) {
    __asm { xor al, al }
    return;
  }
  void* r = (*(FnRetPi)Vslot(q, 0x0c))(q, 0xef3c47cf);
  if (!r) {
    __asm { xor al, al }
    return;
  }
  (*(FnPv)Vslot(r, 0x14))(r, asset);
  (*(FnP)Vslot(mpWindow_1c, 0x90))(mpWindow_1c);
  void* old = mpAsset_2c;
  if (asset != old) {
    (*(FnP)Vslot(asset, 0))(asset);
    mpAsset_2c = asset;
    if (old)
      (*(FnP)Vslot(old, 4))(old);
  }
  mnAssetA_38 = a;
  mnAssetB_3c = b;
  uint32_t thumb[3];
  GetThumbnailBackdrop(thumb, (unsigned int)c);
  SetWindowImage(mpWindow_20, thumb, 0xffffffff);
  mfModeTime_48 = 0.0f;
  (*(FnP2)Vslot(mpWindow_1c, 0x7c))(mpWindow_1c, 1, 1);
  (*(FnP2)Vslot(mpWindow_20, 0x7c))(mpWindow_20, 1, 1);
  (*(FnP2)Vslot(mpWindow_24, 0x7c))(mpWindow_24, 1, 0);
  (*(FnP2)Vslot(mpWindow_28, 0x7c))(mpWindow_28, 1, 0);
  (*(FnP2)Vslot(mpWindow_18, 0x7c))(mpWindow_18, 1, 0);
  (*(FnP)Vslot(mpWindow_14, 0x90))(mpWindow_14);
  mnMode_30 = 1;
  __asm { mov al, 1 }
}

// ===========================================================================
// cSPUIFeedEdit
// ===========================================================================
class cSPUIFeedEdit {
 public:
  uint32_t mPad00[0x31];       // +0x00..+0xc3
  char* mpAssetsBegin;         // +0xc4
  char* mpAssetsEnd;           // +0xc8

  void Shutdown();
  void FUN_0065cae0();
  void UpdateStrings();
  void FUN_0065cc50();
  int GetAssetIndex(int a, int b);
  bool FUN_0065bf20(void* msg, int* data);
  bool FUN_0065c3c0(int a, int b);
};

// @ 0x0065ca10
void cSPUIFeedEdit::Shutdown() {
  char* p = (char*)this;
  if (!*(char*)(p + 0x91))
    return;
  ((cXHTMLFrameSet*)(p + 0x18))->FUN_00997140();
  cSPUILayout* lay = *(cSPUILayout**)(p + 0x14);
  lay->Shutdown(1);
  if (lay) {
    *(void**)(p + 0x14) = 0;
    (*(FnP)Vslot(lay, 8))(lay);
  }
  *(char*)(p + 0x91) = 0;
  void* h = *(void**)(p + 0x10);
  MessageServer_Unsub(h, 0x3cdd5f9, -1);
  MessageServer_Unsub(h, 0x49a3777, -1);
  MessageServer_Unsub(h, 0x1dd7bda9, -1);
  MessageServer_Unsub(h, 0x3b27023, -1);
  void* q = FUN_0067de40();
  q = (*(FnRetP)Vslot(q, 0x20))(q);
  (*(FnPv)Vslot(q, 0x20))(q, this);
}

// @ 0x0065cc50
void cSPUIFeedEdit::FUN_0065cc50() {
  char* p = (char*)this;
  unsigned int idx = *(unsigned int*)(p + 0xa4);
  unsigned int n = *(unsigned int*)(p + 0xa8);
  cSPUILayout* lay = *(cSPUILayout**)(p + 0x14);
  void* w1 = lay->FindWindowByID(0x58b5d84, true);
  if (w1)
    (*(FnP2)Vslot(w1, 0x7c))(w1, 1, idx + 1 < n);
  void* w2 = lay->FindWindowByID(0x58b5d7e, true);
  if (w2)
    (*(FnP2)Vslot(w2, 0x7c))(w2, 1, idx != 0);
}

// @ 0x0065ccd0
int cSPUIFeedEdit::GetAssetIndex(int a, int b) {
  int count = (int)((mpAssetsEnd - mpAssetsBegin) >> 4);
  int* q = (int*)mpAssetsBegin;
  int i = 0;
  if (count != 0) {
    do {
      if (q[0] == a && q[1] == b)
        return i;
      ++i;
      q += 4;
    } while (i != count);
  }
  return -1;
}

struct IRef {
  virtual void AddRef();   // slot 0 (offset 0)
  virtual void Release();  // slot 1 (offset 4)
};
struct AssetInfo {
  void* a; void* b; void* c; void* d;
  AssetInfo& operator=(const AssetInfo& other);
};
// @ 0x0065cd70
AssetInfo& AssetInfo::operator=(const AssetInfo& other) {
  a = other.a;
  b = other.b;
  c = other.c;
  _ReadWriteBarrier();
  void* nw = other.d;
  void* old = d;
  if (nw != old) {
    if (nw) ((IRef*)nw)->AddRef();
    d = nw;
    if (old) ((IRef*)old)->Release();
  }
  return *this;
}
// @ 0x0065cdc0
__declspec(noinline) AssetInfo* FUN_0065cdc0(AssetInfo* first, AssetInfo* last, AssetInfo* out) {
  if (first != last) {
    do {
      if (out) {
        out->a = first->a; out->b = first->b; out->c = first->c;
        void* q = first->d; out->d = q;
        if (q) ((IRef*)q)->AddRef();
      }
      ++first;
      ++out;
    } while (first != last);
  }
  return out;
}
// @ 0x0065ce10
__declspec(noinline) AssetInfo* FUN_0065ce10(AssetInfo* first, AssetInfo* last, AssetInfo* out) {
  while (last != first) {
    --last;
    --out;
    *out = *last;
  }
  return out;
}

// @ 0x0065cae0
void cSPUIFeedEdit::FUN_0065cae0() {
  char* p = (char*)this;
  bool v = false;
  int s = *(int*)(p + 0x8c);
  if (s == 0) {
    if (*(char*)(p + 0x149) != 0 && *(int*)(p + 0x104) != 0)
      v = true;
  } else if (s == 1) {
    if (*(char*)(p + 0x14a) != 0 || *(int*)(p + 0x104) != 0)
      v = true;
    if (*(unsigned int*)(p + 0x124) != 0)
      v = *(unsigned int*)(p + 0x124) <
          (unsigned int)(*(int*)(p + 0x104) + *(int*)(p + 0xe4));
  }
  void* w = (*(FnRetPi)Vslot(*(void**)(p + 0x80), 0xf0))((void*)*(void**)(p + 0x80), 0x5937900);
  if (w)
    (*(FnP2)Vslot(w, 0x7c))(w, 2, v);
}

struct FeedStr {                      // SP::cString, 0x14 bytes
  uint32_t raw[5];
  FeedStr(uint32_t table, uint32_t id, const wchar_t* dflt);   // 0x006b5770
  const wchar_t* GetText();                                    // 0x006b55c0
  ~FeedStr();                                                  // 0x006b5240
};
struct FeedWin {
  virtual void fa0(); virtual void fa1(); virtual void fa2(); virtual void fa3(); virtual void fa4(); virtual void fa5(); virtual void fa6(); virtual void fa7(); virtual void fa8(); virtual void fa9(); virtual void fa10(); virtual void fa11(); virtual void fa12(); virtual void fa13(); virtual void fa14(); virtual void fa15(); virtual void fa16(); virtual void fa17(); virtual void fa18(); virtual void fa19(); virtual void fa20(); virtual void fa21(); virtual void fa22(); virtual void fa23(); virtual void fa24(); virtual void fa25(); virtual void fa26(); virtual void fa27(); virtual void fa28(); virtual void fa29(); virtual void fa30(); virtual void fa31();
  virtual void SetText(const wchar_t* s);                      // 0x80
  virtual void fb0(); virtual void fb1(); virtual void fb2(); virtual void fb3(); virtual void fb4(); virtual void fb5(); virtual void fb6(); virtual void fb7(); virtual void fb8(); virtual void fb9(); virtual void fb10(); virtual void fb11(); virtual void fb12(); virtual void fb13(); virtual void fb14(); virtual void fb15(); virtual void fb16(); virtual void fb17(); virtual void fb18(); virtual void fb19(); virtual void fb20(); virtual void fb21(); virtual void fb22(); virtual void fb23(); virtual void fb24(); virtual void fb25(); virtual void fb26();
  virtual FeedWin* FindWin(uint32_t id, int recursive);        // 0xf0
};

// @ 0x0065cb90
void cSPUIFeedEdit::UpdateStrings() {
  char* p = (char*)this;
  FeedWin* w1 = (*(FeedWin**)(p + 0x80))->FindWin(0x58b5d48, 1);
  if (w1) {
    FeedStr s(0xa153f7a1, 0x58b5d48, L"Items Added (~feededitnumitems~):");
    w1->SetText(s.GetText());
  }
  FeedWin* w2 = (*(FeedWin**)(p + 0x80))->FindWin(0x58b5d50, 1);
  if (w2) {
    FeedStr s(0xa153f7a1, 0x58b5d50, L"(~feededitcurpage~/~feededitnumpages~)");
    w2->SetText(s.GetText());
  }
}

// @ 0x0065bf20
bool cSPUIFeedEdit::FUN_0065bf20(void* msg, int* data) {
  char* p = (char*)this;
  (void)msg;
  if (data[0] == *(int*)(p + 0x9c)) {
    int kind = data[2];
    if (kind == 0x3326e8a) {
      int* arg = (int*)data[6];
      wchar_t* s = (wchar_t*)*arg;
      if (!s) return false;
      if (wcsncmp(s, g_sporecast, g_nSporecast) == 0) {
        if (wcslen_(s) > g_nSporecast) {
          if (wcsncmp(s + g_nSporecast, g_unsubscribe, g_nUnsub) == 0) {
            wchar_t* dst = s + (g_nUnsub + g_nSporecast);
            clear_str(p + 0x84);
            FUN_00472fe0(p + 0x84, "%ls", dst);
            WString tmp;
            tmp.a = &g_01667bac; tmp.b = &g_01667bac; tmp.c = &g_01667bae;
            *(int*)(p + 0xa8) = 2;
            if (!FUN_0065be20(dst, &tmp)) {
              bool r = UI_CalloutMessageBox(p + 4, &g_01526914);
              tmp.DeallocateSelf();
              return r;
            }
            unsigned int pos = ((eastl_cstring_h*)(p + 0x84))->rfind("/", 0xffffffff, 0xffffffff);
            ((eastl_cstring_h*)(p + 0x84))->erase(pos);
            void* q = FUN_0067de40();
            q = (*(FnRetP)Vslot(q, 0x20))(q);
            (*(FnTh2p)Vslot(q, 0x34))(q, &tmp, 0);
            UI_CalloutMessageBox(p + 4, &g_0152692c);
            tmp.DeallocateSelf();
            return false;
          }
          wchar_t* a = wcsstr(s + g_nSporecast, g_asset);
          if (a) {
            if (wcslen_(a) > g_nAsset) {
              unsigned long long v = StrtoU64(a + g_nAsset, 0, 10);
              ((FeedBrowser*)*(void**)(p + 0xa0))->FUN_005ff180((void*)(a + g_nAsset));
              ((FeedBrowser*)this)->FUN_0065b440((int)v, (int)(v >> 32));
            }
            return false;
          }
          wchar_t* rest = s + g_nSporecast;
          clear_str(p + 0x84);
          FUN_00472fe0(p + 0x84, "%ls", rest);
          WString tmp;
          tmp.a = &g_01667bac; tmp.b = &g_01667bac; tmp.c = &g_01667bae;
          *(int*)(p + 0xa8) = 1;
          if (!FUN_0065be20(rest, &tmp)) {
            bool r = UI_CalloutMessageBox(p + 4, &g_01526908);
            tmp.DeallocateSelf();
            return r;
          }
          unsigned int pos = ((eastl_cstring_h*)(p + 0x84))->rfind("/", 0xffffffff, 0xffffffff);
          ((eastl_cstring_h*)(p + 0x84))->erase(pos);
          void* q = FUN_0067de40();
          q = (*(FnRetP)Vslot(q, 0x20))(q);
          (*(FnTh2p)Vslot(q, 0x34))(q, &tmp, 0);
          bool r = UI_CalloutMessageBox(p + 4, &g_01526920);
          tmp.DeallocateSelf();
          return r;
        }
      } else if (wcsncmp(s, g_spore, g_nSpore) == 0) {
        wchar_t* q = s + g_nSpore;
        if (q) {
          unsigned long long v = ((FnStrto)0x0092d710)(q, 0, 10);
          Key12 key; key.a = 0; key.b = 0; key.c = 0;
          FeedDir* dir = (FeedDir*)((char*)FUN_0067cb30() + 0x58);
          if (!dir->GetLocalKey(v, &key)) {
            void* ms = MessageServer();
            (*(FnTh3v)Vslot(ms, 0x14))(ms, 0x66fcce4, 0, 0);
            ((FeedDir3*)FUN_0067cb30())->FUN_006108a0((int)v, (int)(v >> 32));
            return false;
          }
          FeedDir* dir2 = (FeedDir*)((char*)FUN_0067cb30() + 0x58);
          if (!dir2->IsPending(v)) {
            void* mgr = GetManager();
            if (!(*(FnThMgr)Vslot(mgr, 0xc))(mgr, &key, 0, 0, 0, 0, 0)) {
              FeedDir* d3 = (FeedDir*)((char*)FUN_0067cb30() + 0x58);
              d3->FUN_0054ed50((int)v, (int)(v >> 32), 1);
              void* ms = MessageServer();
              (*(FnTh3v)Vslot(ms, 0x14))(ms, 0x66fcce4, 0, 0);
              ((FeedDir3*)FUN_0067cb30())->FUN_006108a0((int)v, (int)(v >> 32));
              return false;
            }
          }
          UI_CalloutMessageBox(0, &g_01526938);
          return false;
        }
      } else if (wcsncmp(s, g_sporeprofile, g_nProfile) == 0) {
        wchar_t* q = s + g_nProfile;
        if (q) {
          unsigned long long v = StrtoU64(q, 0, 10);
          void* ms = MessageServer();
          (*(FnTh3v)Vslot(ms, 0x14))(ms, 0x6299932, &v, 0);
          return false;
        }
      } else {
        return ((cXHTMLFrameSet*)(p + 0x20))->HandleLocationChange(
            (void*)data[0], s, (void*)arg[1], 0);
      }
    } else if (kind == 0x3326e8b) {
      return ((cXHTMLFrameSet*)(p + 0x20))->HandleFormSubmit((void*)data[0], (void*)data[6]);
    } else if (kind == 0x43b0aee) {
      UI_CalloutMessageBox(0, &g_015268fc);
      return true;
    }
  } else if (data[2] == 0x287259f6 && data[3] == 0x629c188) {
    void* ms = MessageServer();
    (*(FnTh3v)Vslot(ms, 0x14))(ms, 0x62d7860, 0, 0);
    return true;
  }
  return false;
}

// @ 0x0065c3c0
bool cSPUIFeedEdit::FUN_0065c3c0(int a, int b) {
  char* p = (char*)this;
  void* win = *(void**)(p + 0x9c);
  if (!win) return false;
  cXHTMLFrameSet* fs = (cXHTMLFrameSet*)(p + 0x20);
  fs->HandleLocationChange(win, g_blank, 0, 0);
  uint32_t tmp[3];
  tmp[0] = 0x1667bac; tmp[1] = 0x1667bac; tmp[2] = 0x1667bae;
  GetURL(0x62ec46a, tmp); // 0x006214c0
  FormatI64(tmp, L"%lld", a, b);
  return fs->HandleLocationChange(win, (const wchar_t*)tmp[0], 0, 0);
}
// --- equivalence checker address annotations
    void GetElapsedSeconds(...); // 0x00805080
    void GetURL(...); // 0x006214c0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct cXHTMLFrameSet {
    void HandleLocationChange(void*, wchar_t*, void*, int); // 0x00997730
};
}
