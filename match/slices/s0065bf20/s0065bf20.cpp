// Slice s0065bf20: SP::cSPUIFeedEditAssetView / SP::cSPUIFeedEdit and helpers.
// Retail layouts are accessed by offset from `this`; function bodies follow the
// annotated disassembly.  Matching functions are the small/table-driven ones.
#include "types.h"
#include <intrin.h>

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" unsigned int __cdecl strlen(const char* p);
extern "C" int wcsncmp(const wchar_t*, const wchar_t*, unsigned int);
extern "C" wchar_t* wcsstr(const wchar_t*, const wchar_t*);

typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void(__thiscall* FnPi)(void*, int);
typedef void*(__thiscall* FnRetP)(void*);
typedef void*(__thiscall* FnRetPi)(void*, unsigned int);
typedef int(__thiscall* FnRetI)(void*);

// Load virtual slot `off` from object `o`: [o] is the vtable pointer.
static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }

struct cSPUILayout {
  void Shutdown(int a);
  void* FindWindowByID(uint32_t id, bool recursive);
};
struct cXHTMLFrameSet {
  void* GetFrame(uint32_t id);
  bool HandleLocationChange(void* win, const wchar_t* url, void* a, int b);
  bool HandleFormSubmit(void* win, void* form);
  void FUN_00997140();
};

// ---- external callees / globals ----
void* GetElapsedSeconds(); // 0x00805080
void SetWindowImage(void* w, uint32_t* key, int flags);
void* FUN_0067de40();
void* MessageServer();
void MessageServer_Unsub(void* h, uint32_t id, int y);
void MessageServer_Post(uint32_t id, void* p, int n);
void FUN_005ff180(void* p);
void FUN_0065b440(void* v);
void FUN_0054e460();
void FUN_0054e740();
void FUN_0054ed50();
void FUN_006108a0();
void FUN_005feea0();
void* FUN_005feff0();
void FUN_00809db0(int a, void* b);
void GetURL(int a, void* b); // 0x006214c0
void FormatI64(void* out, const wchar_t* fmt, int a, int b);
unsigned long long StrtoU64(const void* p, int a, int b);
void QualifyNameWithGroup();
void FUN_0067cb30();
void FUN_0067cb30b();
extern const wchar_t* g_sporecast;
extern const wchar_t* g_unsubscribe;
extern const wchar_t* g_asset;
extern const wchar_t* g_spore;
extern const wchar_t* g_sporeprofile;
extern const wchar_t* g_blank;
extern unsigned int g_nSporecast, g_nUnsub, g_nAsset, g_nSpore, g_nProfile;
extern int g_15fa6e4;
extern void* g_vt_13fff3c;
extern void* g_vt_13fff2c;
extern void* g_vt_13ec458;

namespace eastl {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
inline unsigned int CharStrlen(const char* p) { return strlen(p); }
struct allocator {};
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
  out[0] = 0;
  out[1] = 0x2f7d0004;
  out[2] = 0xca14de92;
  switch (id) {
    case 0x2090a11b: out[0] = 0x14585a1f; break;
    case 0x1f2a25b6: out[0] = 0x71981adc; break;
    case 0x1a4e0708: out[0] = 0x188ebff2; break;
    case 0x2a5147a9: out[0] = 0x62b8bc1; break;
    case 0x37148141: out[0] = 0xda273036; break;
    case 0x372e2c04: out[0] = 0x3f185edb; break;
    case 0x449c040f: out[0] = 0xe4d0e7f3; break;
    case 0x441cd3e6: out[0] = 0xe7792790; break;
    case 0x47c10953: out[0] = 0x62e861d9; break;
    case 0x4e3f7777: out[0] = 0x8c1f0aa3; break;
    case 0x4178b8e8: out[0] = 0x89b74761; break;
    case 0x65672ade: out[0] = 0x89b74761; break;
    case 0x72c49181: out[0] = 0xd1376095; break;
    case 0x7d433fad: out[0] = 0x6920384d; break;
    case 0x8f963dcb: out[0] = 0xc2d3ce6f; break;
    case 0x98e03c0d: out[0] = 0x7609745a; break;
    case 0x99e92f05: out[0] = 0xb390f699; break;
    case 0x9ad7d4aa: out[0] = 0xb6dc61a6; break;
    case 0x9ea3031a: out[0] = 0xe04dd8b1; break;
    case 0xb8669ec9: out[0] = 0x9fe7f178; break;
    case 0xbc1041e6: out[0] = 0xa0cc166e; break;
    case 0xbcd73e89: out[0] = 0x945e2516; break;
    case 0xbdd15f3d: out[0] = 0x8c1f0aa3; break;
    case 0xc0b74287: out[0] = 0x6920384d; break;
    case 0xc15695da: out[0] = 0xf6eb7174; break;
    case 0xccc35c46: out[0] = 0xdc1b3879; break;
    case 0xdfad9f51: out[0] = 0xb49e7fb2; break;
    case 0xf670aa43: out[0] = 0xf5f1b0d7; break;
  }
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

// @ 0x0065c790
struct CtorObj {
  void** vt; void** vt4; int m08; char pad0c[4]; void* m10; void* m14; void* m18; int m1c;
  void FUN_0065c790(void* a, void* b, void* c);
};
void CtorObj::FUN_0065c790(void* a, void* b, void* c) {
  vt4 = &g_vt_13ec458;
  m08 = 0;
  m10 = a;
  m14 = b;
  vt = &g_vt_13fff3c;
  vt4 = &g_vt_13fff2c;
  m18 = c;
  m1c = 0;
}

// @ 0x0065c840
void cSPUIFeedEditAssetView::SetMode(int mode) {
  char* p = (char*)this;
  if (mode == 2) {
    *(float*)(p + 0x48) = (float)(int)GetElapsedSeconds();
    (*(FnP2)Vslot(*(void**)(p + 0x1c), 0x7c))((void*)*(void**)(p + 0x1c), 1, 1);
    (*(FnP2)Vslot(*(void**)(p + 0x20), 0x7c))((void*)*(void**)(p + 0x20), 1, 1);
    (*(FnP2)Vslot(*(void**)(p + 0x24), 0x7c))((void*)*(void**)(p + 0x24), 1, 1);
    (*(FnP2)Vslot(*(void**)(p + 0x28), 0x7c))((void*)*(void**)(p + 0x28), 1, 0);
    (*(FnP2)Vslot(*(void**)(p + 0x18), 0x7c))((void*)*(void**)(p + 0x18), 1, 0);
    if (*(void**)(p + 0x14) && *(int*)(p + 0x44) == 0) {
      *(int*)(p + 0x44) = 2;
      (*(FnPv)Vslot(*(void**)(p + 0x14), 0x104))((void*)*(void**)(p + 0x14), this);
    }
  } else if (mode == 1 || mode == 3) {
    *(float*)(p + 0x48) = 0.0f;
    (*(FnP2)Vslot(*(void**)(p + 0x1c), 0x7c))((void*)*(void**)(p + 0x1c), 1, 1);
    (*(FnP2)Vslot(*(void**)(p + 0x20), 0x7c))((void*)*(void**)(p + 0x20), 1, 1);
    (*(FnP2)Vslot(*(void**)(p + 0x24), 0x7c))((void*)*(void**)(p + 0x24), 1, mode == 3 ? 0 : 1);
    (*(FnP2)Vslot(*(void**)(p + 0x28), 0x7c))((void*)*(void**)(p + 0x28), 1, mode == 3 ? 1 : 0);
    (*(FnP2)Vslot(*(void**)(p + 0x18), 0x7c))((void*)*(void**)(p + 0x18), 1, 0);
  } else {
    *(float*)(p + 0x48) = 0.0f;
    (*(FnP2)Vslot(*(void**)(p + 0x1c), 0x7c))((void*)*(void**)(p + 0x1c), 1, 0);
    (*(FnP2)Vslot(*(void**)(p + 0x20), 0x7c))((void*)*(void**)(p + 0x20), 1, 0);
    (*(FnP2)Vslot(*(void**)(p + 0x24), 0x7c))((void*)*(void**)(p + 0x24), 1, 0);
    (*(FnP2)Vslot(*(void**)(p + 0x28), 0x7c))((void*)*(void**)(p + 0x28), 1, 1);
    (*(FnP2)Vslot(*(void**)(p + 0x18), 0x7c))((void*)*(void**)(p + 0x18), 1, 0);
  }
  (*(FnP)Vslot(*(void**)(p + 0x14), 0x90))((void*)*(void**)(p + 0x14));
  *(int*)(p + 0x30) = mode;
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
  int id = *(int*)((char*)data + 8);
  if (id == 7) {
    struct S { int a, b, c, d, e; } s;
    s.c = *(int*)((char*)this + 0x40);
    s.e = *(int*)((char*)this + 0x14);
    s.a = 0x17;
    s.b = 0x590cb98;
    (*(FnPv)Vslot(msg, 0x114))(msg, &s);
    return 1;
  }
  if (id == 0xc)
    return FUN_0065c9a0(msg) ? 1 : 0;
  if (id == 0x11)
    ++g_15fa6e4;
  return 0;
}

// @ 0x0065cf30
void cSPUIFeedEditAssetView::FUN_0065cf30(int, int, int, int* asset) {
  char* p = (char*)this;
  if (!asset)
    return;
  void* q = (*(FnRetP)Vslot(*(void**)(p + 0x1c), 0xa8))((void*)*(void**)(p + 0x1c));
  if (!q)
    return;
  void* r = (*(FnRetPi)Vslot(q, 0x0c))(q, 0xef3c47cf);
  if (!r)
    return;
  (*(FnPv)Vslot(r, 0x14))(r, asset);
  (*(FnP)Vslot(*(void**)(p + 0x1c), 0x90))((void*)*(void**)(p + 0x1c));
  void* old = *(void**)(p + 0x2c);
  if (asset != old) {
    (*(FnP)Vslot(asset, 0))(asset);
    *(void**)(p + 0x2c) = asset;
    if (old)
      (*(FnP)Vslot(old, 4))(old);
  }
  uint32_t thumb[3];
  GetThumbnailBackdrop(thumb, *(unsigned int*)(p + 0x38));
  SetWindowImage(*(void**)(p + 0x20), thumb, 0xffffffff);
  *(float*)(p + 0x48) = 0.0f;
  (*(FnP2)Vslot(*(void**)(p + 0x1c), 0x7c))((void*)*(void**)(p + 0x1c), 1, 1);
  (*(FnP2)Vslot(*(void**)(p + 0x20), 0x7c))((void*)*(void**)(p + 0x20), 1, 1);
  (*(FnP2)Vslot(*(void**)(p + 0x24), 0x7c))((void*)*(void**)(p + 0x24), 1, 0);
  (*(FnP2)Vslot(*(void**)(p + 0x28), 0x7c))((void*)*(void**)(p + 0x28), 1, 0);
  (*(FnP2)Vslot(*(void**)(p + 0x18), 0x7c))((void*)*(void**)(p + 0x18), 1, 0);
  (*(FnP)Vslot(*(void**)(p + 0x14), 0x90))((void*)*(void**)(p + 0x14));
  *(int*)(p + 0x30) = 1;
}

// ===========================================================================
// cSPUIFeedEdit
// ===========================================================================
class cSPUIFeedEdit {
 public:
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
  char* p = (char*)this;
  int count = (*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4;
  int* q = *(int**)(p + 0xc4);
  for (int i = 0; i < count; ++i, q += 4) {
    if (q[0] == a && q[1] == b)
      return i;
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

// @ 0x0065cb90
void cSPUIFeedEdit::UpdateStrings() {
  char* p = (char*)this;
  void* o = *(void**)(p + 0x80);
  void* w1 = (*(FnRetPi)Vslot(o, 0xf0))(o, 0x58b5d48);
  if (w1) {
    // cString temporary; assign to control text
    (*(FnP)Vslot(w1, 0x80))(w1);
  }
  void* w2 = (*(FnRetPi)Vslot(o, 0xf0))(o, 0x58b5d50);
  if (w2) {
    (*(FnP)Vslot(w2, 0x80))(w2);
  }
}

// @ 0x0065bf20
bool cSPUIFeedEdit::FUN_0065bf20(void* msg, int* data) {
  char* p = (char*)this;
  (void)msg;
  if (data[0] == *(int*)(p + 0x9c)) {
    int kind = data[2];
    if (kind == 0x3326e8a) {
      wchar_t* s = *(wchar_t**)data[6];
      if (!s) return false;
      if (wcsncmp(s, g_sporecast, g_nSporecast) == 0) {
        if (wcsncmp(s + g_nSporecast, g_unsubscribe, g_nUnsub) == 0) {
          *(int*)(p + 0xa8) = 2;
          return false;
        }
        wchar_t* a = wcsstr(s + g_nSporecast, g_asset);
        if (a) {
          unsigned long long vv = StrtoU64(a + g_nAsset, 0, 10);
          FUN_005ff180(a + g_nAsset);
          FUN_0065b440((void*)vv);
          return false;
        }
      } else if (wcsncmp(s, g_spore, g_nSpore) == 0) {
        return false;
      } else if (wcsncmp(s, g_sporeprofile, g_nProfile) == 0) {
        unsigned long long vv = StrtoU64(s + g_nProfile, 0, 10);
        MessageServer_Post(0x6299932, &vv, 0);
        return false;
      } else {
        ((cXHTMLFrameSet*)(p + 0x20))->HandleLocationChange((void*)data[0], s, (void*)data[6], 0);
        return false;
      }
    } else if (kind == 0x3326e8b) {
      ((cXHTMLFrameSet*)(p + 0x20))->HandleFormSubmit((void*)data[0], (void*)data[6]);
      return false;
    } else if (kind == 0x43b0aee) {
      return true;
    }
  } else if (data[2] == 0x287259f6 && data[3] == 0x629c188) {
    MessageServer_Post(0x62d7860, 0, 0);
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
