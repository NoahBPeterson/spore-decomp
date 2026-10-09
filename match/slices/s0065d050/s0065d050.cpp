// Slice s0065d050: SP::cSPUIFeedEdit / SP::cSPUIFeedEditAssetView browser+grid UI.
// Retail layouts are accessed by offset from `this`; bodies follow the annotated
// disassembly.  Class names/offsets cross-checked against the 2008 dev PDB.
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, int c,
                                          int d);
extern "C" void* operator_new_ea(unsigned int size, const char* tag, int, int, int, int);
extern "C" unsigned long __cdecl wcstoul(const wchar_t* s, wchar_t** end, int base);

typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPi)(void*, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void(__thiscall* FnPv2)(void*, void*, void*);
typedef void*(__thiscall* FnRetP)(void*);
typedef void*(__thiscall* FnRetPi)(void*, unsigned int);
typedef int(__thiscall* FnRetI)(void*);

// Load virtual slot `off` from object `o`: [o] is the vtable pointer.
static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }

struct ResourceKey { uint32_t a, b, c; };

struct cXHTMLFrameSet {
  void* GetFrame(uint32_t id);
  void HandleLocationChange(void* win, const wchar_t* url, int a, int b);
  void FUN_00997140();
};

// extern runtime callees
void* MessageServer();
unsigned int __cdecl FNVHash16(const wchar_t* s, unsigned int seed, int n);
float __cdecl GetElapsedSeconds();
void GetURL(unsigned int id, void* out);
void SetNumberString(int value, int a, wchar_t* buf, int n);
void StrtoU6416_ret(const wchar_t*, int, int);  // returns edx:eax
void* GetResourceProvider();
void* CopyImpl(void* first, void* last, void* dest);
void DoFreeNodes(void* a, void* b);
void DeallocateVector65cd30();
void DeallocateVectorAe6970();
void FrameSetDtor();
void FUN_005725a0();

extern const wchar_t* g_user;
extern uint32_t g_1526cb0;
extern wchar_t g_str_1667bac;
extern wchar_t g_str_1667bae;
extern void* g_vt_13ec458;
extern void* g_vt_13fff3c;
extern void* g_vt_13fff2c;

// ===========================================================================
// cSPUIFeedEditAssetView
// ===========================================================================
struct cSPUIFeedEditAssetView {
  void* vt;            // +0x00
  void* vt4;           // +0x04
  void* vt8;           // +0x08
  void* mpLayout;      // +0x0c
  void* mpParentWin;   // +0x10
  void* mpRootWin;     // +0x14
  void* mpButtonWin;   // +0x18
  void* mpAssetWin;    // +0x1c
  void* mpBackdropWin; // +0x20
  void* mpGlowWin;     // +0x24
  void* mpEmptyWin;    // +0x28
  void* mpImage;       // +0x2c
  int mnMode;          // +0x30
  int pad34;           // +0x34
  unsigned long long mnAssetID;  // +0x38
  unsigned int mnIndex;          // +0x40
  unsigned int mTickMask;        // +0x44
  float mfBlinkStart;            // +0x48

  void ClearAsset();                       // 0065d050
  bool Init(void* parent, unsigned int index);  // 0065d720
  void Shutdown();                         // 0065d810
  void SetMode(int mode);                  // 0065c840 (defined in slice s0065bf20)
};

struct cSPUILayout {
  bool Init(ResourceKey* key, int a, uint32_t b);
  void SetParentWin(void* parent, int a, uint32_t b);
  void SetReloadCallback(void* fn, void* self);
  void* FindWindowByID(uint32_t id, bool recursive);
  void Shutdown(int a);
  void* Create();
};

void ReloadCallback(cSPUIFeedEditAssetView* self, void* layout, bool b);

struct OutStr {
  void Assign(const wchar_t* b, const wchar_t* e);
};

struct IRefCounted {
  virtual void m0();
  virtual void Release();  // slot 1 (offset 4)
};

struct IWinLookup {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void* FindByKey(unsigned int key);  // slot 3 (offset 0xc)
};

// Stub window interface: slots 0..65 (offsets 0x0..0x104) in vtable order.
struct IWindow {
  virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
  virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
  virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
  virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
  virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
  virtual void m20(int);                        // 0x50
  virtual void m21(); virtual void m22(); virtual void m23();
  virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
  virtual void m28(); virtual void m29(); virtual void m30();
  virtual void m31(int, int);                   // 0x7c
  virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
  virtual void m36();                           // 0x90
  virtual void m37(); virtual void m38(); virtual void m39(); virtual void m40();
  virtual void m41();
  virtual IWinLookup* GetLookup();              // 0xa8
  virtual void m43(); virtual void m44(); virtual void m45(); virtual void m46();
  virtual void m47(); virtual void m48(); virtual void m49(); virtual void m50();
  virtual void m51(); virtual void m52(); virtual void m53(); virtual void m54();
  virtual void m55(); virtual void m56(); virtual void m57(); virtual void m58();
  virtual void m59(); virtual void m60(); virtual void m61(); virtual void m62();
  virtual void m63(); virtual void m64();
  virtual void m65(void*);                      // 0x104
};

// @ 0x0065d050
void cSPUIFeedEditAssetView::ClearAsset() {
  char* p = (char*)this;
  void* a = ((IWindow*)*(void**)(p + 0x1c))->GetLookup();
  if (!a)
    return;
  void* b = ((IWinLookup*)a)->FindByKey(0xef3c47cf);
  if (!b)
    return;
  (*(FnPi)Vslot(b, 0x14))(b, 0);
  void* img = *(void**)(p + 0x2c);
  if (img) {
    *(void**)(p + 0x2c) = 0;
    (*(FnP)Vslot(img, 4))(img);
  }
  *(int*)(p + 0x38) = -1;
  *(int*)(p + 0x3c) = -1;
  *(float*)(p + 0x48) = 0.0f;
  (*(FnP2)Vslot(*(void**)(p + 0x1c), 0x7c))(*(void**)(p + 0x1c), 1, 0);
  (*(FnP2)Vslot(*(void**)(p + 0x20), 0x7c))(*(void**)(p + 0x20), 1, 0);
  (*(FnP2)Vslot(*(void**)(p + 0x24), 0x7c))(*(void**)(p + 0x24), 1, 0);
  (*(FnP2)Vslot(*(void**)(p + 0x28), 0x7c))(*(void**)(p + 0x28), 1, 1);
  (*(FnP2)Vslot(*(void**)(p + 0x18), 0x7c))(*(void**)(p + 0x18), 1, 0);
  (*(FnP)Vslot(*(void**)(p + 0x14), 0x90))(*(void**)(p + 0x14));
  *(int*)(p + 0x30) = 0;
}

// @ 0x0065d110
void ReloadCallback(cSPUIFeedEditAssetView* self, void* layout, bool b) {
  (void)layout;
  if (!self)
    return;
  char* p = (char*)self;
  if (b) {
    void* w = ((cSPUILayout*)*(void**)(p + 0x0c))->FindWindowByID(0x590e400, 1);
    *(void**)(p + 0x14) = w;
    (*(FnPi)Vslot(w, 0x50))(w, *(int*)(p + 0x40));
    (*(FnPv)Vslot(*(void**)(p + 0x14), 0x104))(*(void**)(p + 0x14), self);
    w = ((cSPUILayout*)*(void**)(p + 0x0c))->FindWindowByID(0x590d548, 1);
    *(void**)(p + 0x1c) = w;
    (*(FnPv)Vslot(w, 0x104))(w, self);
    void* a = (*(FnRetP)Vslot(*(void**)(p + 0x1c), 0xa8))(*(void**)(p + 0x1c));
    if (a) {
      void* bb = ((IWinLookup*)a)->FindByKey(0xef3c47cf);
      if (bb)
        (*(FnPv)Vslot(bb, 0x14))(bb, *(void**)(p + 0x2c));
    }
    w = ((cSPUILayout*)*(void**)(p + 0x0c))->FindWindowByID(0x591c8d8, 1);
    *(void**)(p + 0x20) = w;
    (*(FnPv)Vslot(w, 0x104))(w, self);
    w = ((cSPUILayout*)*(void**)(p + 0x0c))->FindWindowByID(0x590c7f0, 1);
    *(void**)(p + 0x24) = w;
    (*(FnPv)Vslot(w, 0x104))(w, self);
    w = ((cSPUILayout*)*(void**)(p + 0x0c))->FindWindowByID(0x590c890, 1);
    *(void**)(p + 0x28) = w;
    (*(FnPv)Vslot(w, 0x104))(w, self);
    w = ((cSPUILayout*)*(void**)(p + 0x0c))->FindWindowByID(0x591c790, 1);
    *(void**)(p + 0x18) = w;
    if (w)
      (*(FnPi)Vslot(w, 0x50))(w, *(int*)(p + 0x40));
    ((cSPUIFeedEditAssetView*)self)->SetMode(*(int*)(p + 0x30));
  } else {
    if (*(void**)(p + 0x14) && *(int*)(p + 0x44)) {
      *(int*)(p + 0x44) = 0;
      (*(FnPv)Vslot(*(void**)(p + 0x14), 0x104))(*(void**)(p + 0x14), self);
    }
    *(void**)(p + 0x14) = 0;
    *(void**)(p + 0x1c) = 0;
    *(void**)(p + 0x20) = 0;
    *(void**)(p + 0x24) = 0;
    *(void**)(p + 0x28) = 0;
  }
}

// @ 0x0065d720
bool cSPUIFeedEditAssetView::Init(void* parent, unsigned int index) {
  char* p = (char*)this;
  *(void**)(p + 0x10) = parent;
  if (!parent)
    return false;
  void* obj = operator_new_ea(0x18, "Sporepedia", 0, 0, 0, 0);
  void* nw = obj ? ((cSPUILayout*)obj)->Create() : 0;
  void* old = *(void**)(p + 0x0c);
  if (nw != old) {
    if (nw)
      (*(FnP)Vslot(nw, 4))(nw);
    *(void**)(p + 0x0c) = nw;
    if (old)
      (*(FnP)Vslot(old, 8))(old);
  }
  void* lay = *(void**)(p + 0x0c);
  if (!lay)
    return false;
  ResourceKey key;
  key.a = 0xce45d388;
  key.b = 0x510a95b;
  key.c = g_1526cb0;
  if (!((cSPUILayout*)lay)->Init(&key, 1, 0x5b598fa))
    return false;
  ((cSPUILayout*)lay)->SetParentWin(*(void**)(p + 0x10), 1, 0x5b598fa);
  ((cSPUILayout*)lay)->SetReloadCallback((void*)&ReloadCallback, this);
  void* lay2 = *(void**)(p + 0x0c);
  *(unsigned int*)(p + 0x40) = index;
  ReloadCallback(this, lay2, true);
  return true;
}

// @ 0x0065d810
void cSPUIFeedEditAssetView::Shutdown() {
  char* p = (char*)this;
  if (this) {
    if (*(void**)(p + 0x14) && *(int*)(p + 0x44)) {
      *(int*)(p + 0x44) = 0;
      (*(FnPv)Vslot(*(void**)(p + 0x14), 0x104))(*(void**)(p + 0x14), this);
    }
    *(void**)(p + 0x14) = 0;
    *(void**)(p + 0x1c) = 0;
    *(void**)(p + 0x20) = 0;
    *(void**)(p + 0x24) = 0;
    *(void**)(p + 0x28) = 0;
  }
  void* lay = *(void**)(p + 0x0c);
  if (lay) {
    *(void**)(p + 0x0c) = 0;
    (*(FnP)Vslot(lay, 8))(lay);
  }
  *(void**)(p + 0x10) = 0;
}

// ===========================================================================
// cSPUIFeedEdit
// ===========================================================================
struct cSPUIFeedEdit {
  void* vt;  // +0x00
  char pad[0x50];

  void FUN_0065cc50();       // 0065cc50 (slice s0065bf20) page-button enable helper
  void UpdateStrings();      // 0065cb90 (slice s0065bf20)
  int GetAssetIndex(int a, int b);  // 0065ccd0 (slice s0065bf20)
  void FUN_0065cf30(int a, int b, int c, int* asset);  // slice s0065bf20

  void UpdateGrid();         // 0065d260
  void FUN_0065d490();       // 0065d490
  bool SetPage(unsigned int page);  // 0065d4e0
  void ShowAsset(int a, int b);     // 0065d570
  bool TranslateToken(const wchar_t* token, void* out);  // 0065dc60
  void SetActive(bool b);    // 0065d9f0
  bool FUN_0065dd30(unsigned int id);  // 0065dd30 wrapper
};

struct AssetInfo { int a, b, c, d; };  // 0x10 bytes
struct AutoRefAssetView { char pad[0x50]; };  // placeholder refcounted view

// @ 0x0065d260
void cSPUIFeedEdit::UpdateGrid() {
  char* p = (char*)this;
  unsigned int assetCount = (*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4;
  int per = (*(int*)(p + 0xb4) - *(int*)(p + 0xb0)) >> 2;
  unsigned int index = per * *(int*)(p + 0xa4);
  char** it = (char**)*(void**)(p + 0xb0);
  char** end = (char**)*(void**)(p + 0xb4);
  if (it == end)
    return;
  do {
    char* view = *it;
    if (index < assetCount) {
      int* e = (int*)(*(int*)(p + 0xc4) + (index << 4));
      if (*(unsigned long long*)(view + 0x38) != *(unsigned long long*)e)
        FUN_0065cf30(e[0], e[1], e[2], (int*)e[3]);
      if (index == *(unsigned int*)(p + 0xac)) {
        *(float*)(view + 0x48) = 0.0f;
        (*(FnP2)Vslot(*(void**)(view + 0x1c), 0x7c))(*(void**)(view + 0x1c), 1, 1);
        (*(FnP2)Vslot(*(void**)(view + 0x20), 0x7c))(*(void**)(view + 0x20), 1, 1);
        (*(FnP2)Vslot(*(void**)(view + 0x24), 0x7c))(*(void**)(view + 0x24), 1, 1);
        (*(FnP2)Vslot(*(void**)(view + 0x28), 0x7c))(*(void**)(view + 0x28), 1, 0);
        (*(FnP2)Vslot(*(void**)(view + 0x18), 0x7c))(*(void**)(view + 0x18), 1, 1);
        (*(FnP)Vslot(*(void**)(view + 0x14), 0x90))(*(void**)(view + 0x14));
        *(int*)(view + 0x30) = 3;
      } else if (*(int*)(view + 0x30) == 3) {
        *(float*)(view + 0x48) = 0.0f;
        (*(FnP2)Vslot(*(void**)(view + 0x1c), 0x7c))(*(void**)(view + 0x1c), 1, 1);
        (*(FnP2)Vslot(*(void**)(view + 0x20), 0x7c))(*(void**)(view + 0x20), 1, 1);
        (*(FnP2)Vslot(*(void**)(view + 0x24), 0x7c))(*(void**)(view + 0x24), 1, 0);
        (*(FnP2)Vslot(*(void**)(view + 0x28), 0x7c))(*(void**)(view + 0x28), 1, 0);
        (*(FnP2)Vslot(*(void**)(view + 0x18), 0x7c))(*(void**)(view + 0x18), 1, 0);
        (*(FnP)Vslot(*(void**)(view + 0x14), 0x90))(*(void**)(view + 0x14));
        *(int*)(view + 0x30) = 1;
      }
    } else {
      ((cSPUIFeedEditAssetView*)view)->ClearAsset();
    }
    ++it;
    ++index;
  } while (it != end);
}

// @ 0x0065d490
void cSPUIFeedEdit::FUN_0065d490() {
  char* p = (char*)this;
  unsigned int count = (*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4;
  unsigned int per = (*(int*)(p + 0xb4) - *(int*)(p + 0xb0)) >> 2;
  unsigned int np = count / per;
  *(unsigned int*)(p + 0xa8) = np;
  if (np * per != count)
    *(unsigned int*)(p + 0xa8) = np + 1;
  FUN_0065cc50();
}

// @ 0x0065d4e0
bool cSPUIFeedEdit::SetPage(unsigned int page) {
  char* p = (char*)this;
  if (page != *(unsigned int*)(p + 0xa4)) {
    unsigned int count = (*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4;
    unsigned int per = (*(int*)(p + 0xb4) - *(int*)(p + 0xb0)) >> 2;
    unsigned int np = count / per;
    *(unsigned int*)(p + 0xa8) = np;
    if (np * per != count)
      *(unsigned int*)(p + 0xa8) = np + 1;
    FUN_0065cc50();
    if (page < *(unsigned int*)(p + 0xa8)) {
      *(unsigned int*)(p + 0xa4) = page;
      *(int*)(p + 0xac) = -1;
      UpdateGrid();
      UpdateStrings();
      FUN_0065cc50();
      return true;
    }
  }
  return false;
}

// @ 0x0065d570
void cSPUIFeedEdit::ShowAsset(int a, int b) {
  char* p = (char*)this;
  int idx = GetAssetIndex(a, b);
  unsigned int count = (*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4;
  if ((unsigned int)idx >= count)
    return;
  *(int*)(p + 0xac) = -1;
  unsigned int per = (*(int*)(p + 0xb4) - *(int*)(p + 0xb0)) >> 2;
  SetPage((unsigned int)idx / per);
  UpdateGrid();
  char** it = (char**)*(void**)(p + 0xb0);
  char** end = (char**)*(void**)(p + 0xb4);
  if (it != end) {
    do {
      char* view = *it;
      if (*(int*)(view + 0x38) == a && *(int*)(view + 0x3c) == b)
        break;
      ++it;
    } while (it != end);
    if (it != end) {
      char* view = *it;
      *(float*)(view + 0x48) = GetElapsedSeconds();
      (*(FnP2)Vslot(*(void**)(view + 0x1c), 0x7c))(*(void**)(view + 0x1c), 1, 1);
      (*(FnP2)Vslot(*(void**)(view + 0x20), 0x7c))(*(void**)(view + 0x20), 1, 1);
      (*(FnP2)Vslot(*(void**)(view + 0x24), 0x7c))(*(void**)(view + 0x24), 1, 1);
      (*(FnP2)Vslot(*(void**)(view + 0x28), 0x7c))(*(void**)(view + 0x28), 1, 0);
      (*(FnP2)Vslot(*(void**)(view + 0x18), 0x7c))(*(void**)(view + 0x18), 1, 0);
      if (*(void**)(view + 0x14) && *(int*)(view + 0x44) == 0) {
        *(int*)(view + 0x44) = 2;
        (*(FnPv)Vslot(*(void**)(view + 0x14), 0x104))(*(void**)(view + 0x14), view);
      }
      (*(FnP)Vslot(*(void**)(view + 0x14), 0x90))(*(void**)(view + 0x14));
      *(int*)(view + 0x30) = 2;
    }
  }
}

// @ 0x0065d410
void AssetRequestCallBack(int* param) {
  int* ms = (int*)MessageServer();
  if (ms && param[4]) {
    int* r = (int*)(*(FnRetPi)Vslot((void*)param[4], 0x0c))((void*)param[4], 0x1be6ab3);
    if (r) {
      int* old = (int*)param[7];
      if (r != old) {
        (*(FnP)Vslot(r, 0))(r);
        param[7] = (int)r;
        if (old)
          (*(FnP)Vslot(old, 4))(old);
      }
      (*(void(__thiscall*)(void*, unsigned int, void*, int, int))Vslot(ms, 0x18))(ms, 0x3b27023,
                                                                                  (void*)param, 0, 0);
      (*(FnP)Vslot(param, 8))(param);
    }
  }
}

// @ 0x0065d6a0
struct HashtableU64 {
  int count;  // +0x0c
  int* erase(int* out, int* node, int* bucket);
};
int* HashtableU64::erase(int* out, int* node, int* bucket) {
  int iVar1 = node[2];
  out[1] = (int)bucket;
  out[0] = iVar1;
  while (iVar1 == 0) {
    out[1] = out[1] + 4;
    iVar1 = *(int*)out[1];
    out[0] = iVar1;
  }
  iVar1 = *bucket;
  if (iVar1 == (int)node) {
    *bucket = *(int*)(iVar1 + 8);
    EASTL_allocator_deallocate(node);
    count = count - 1;
    return out;
  }
  int iVar2 = *(int*)(iVar1 + 8);
  while (iVar2 != (int)node) {
    iVar1 = iVar2;
    iVar2 = *(int*)(iVar2 + 8);
  }
  *(int*)(iVar1 + 8) = *(int*)(iVar2 + 8);
  EASTL_allocator_deallocate(node);
  count = count - 1;
  return out;
}

// @ 0x0065d9f0
void cSPUIFeedEdit::SetActive(bool b) {
  char* p = (char*)this;
  if (b && *(void**)(p + 0x7c))
    (*(FnP2)Vslot(*(void**)(p + 0x7c), 0x7c))(*(void**)(p + 0x7c), 1, 1);
  if (*(void**)(p + 0x80)) {
    (*(FnP2)Vslot(*(void**)(p + 0x80), 0x7c))(*(void**)(p + 0x80), 1, b ? 1 : 0);
    if (b) {
      wchar_t* tmp[3];
      tmp[0] = &g_str_1667bac;
      tmp[1] = &g_str_1667bac;
      tmp[2] = &g_str_1667bae;
      *(int*)(p + 0x8c) = 0;
      GetURL(0x5908ef2, tmp);
      ((cXHTMLFrameSet*)(p + 0x18))->HandleLocationChange(*(void**)(p + 0x84), tmp[0], 0, 0);
    }
  }
}

// @ 0x0065dc60
bool cSPUIFeedEdit::TranslateToken(const wchar_t* token, void* out) {
  char* p = (char*)this;
  unsigned int h = FNVHash16(token, 0x811c9dc5, 1);
  unsigned int value;
  if (h == 0x508cf9e5) {
    value = *(unsigned int*)(p + 0xa8);
    if (!value)
      value = 1;
  } else if (h == 0x87b3e875) {
    value = (unsigned int)((*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4);
  } else if (h == 0xeca00430) {
    value = *(unsigned int*)(p + 0xa4) + 1;
  } else {
    return false;
  }
  wchar_t buf[64];
  SetNumberString(value, 0, buf, 0x40);
  wchar_t* e = buf;
  while (*e)
    ++e;
  ((OutStr*)out)->Assign(buf, e);
  return true;
}

// @ 0x0065dd30
void ResourceLoadHelper(cSPUIFeedEdit* self, unsigned int id) {
  (void)self;
  (void)id;
}

// @ 0x0065daa0
cSPUIFeedEdit* cSPUIFeedEdit_ctor(cSPUIFeedEdit* self) { return self; }

// @ 0x0065d860
cSPUIFeedEdit* cSPUIFeedEdit_dtor(cSPUIFeedEdit* self) { return self; }

// @ 0x0065ded0
struct UFOCollisionEffectInfo { int a, b, c; int ref; };
struct VecUFO {
  char pad[4];
  UFOCollisionEffectInfo* mpEnd;
  UFOCollisionEffectInfo* erase(UFOCollisionEffectInfo* first, UFOCollisionEffectInfo* last);
};
UFOCollisionEffectInfo* VecUFO::erase(UFOCollisionEffectInfo* first, UFOCollisionEffectInfo* last) {
  UFOCollisionEffectInfo* p =
      (UFOCollisionEffectInfo*)CopyImpl(last, mpEnd, first);
  if (p < mpEnd) {
    unsigned int d = (unsigned int)((char*)mpEnd - (char*)p);
    unsigned int n = ((d - 1) >> 4) + 1;
    char* q = (char*)p + 0xc;
    do {
      void* r = *(void**)q;
      if (r)
        ((IRefCounted*)r)->Release();
      q += 0x10;
    } while (--n);
  }
  mpEnd = (UFOCollisionEffectInfo*)((char*)mpEnd + (((char*)last - (char*)first) >> 4) * -0x10);
  return first;
}
