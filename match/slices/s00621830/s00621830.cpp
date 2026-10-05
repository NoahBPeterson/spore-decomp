// SP::Pollen::InitURLs (big URL-registration table) and the SP::cXHTMLControlAppearance
// class (drawable appearance + the vector<ControlDrawable> helpers it uses).
// Region 0x621830-0x622128. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
//   00621830  SP::Pollen::InitURLs
//   00621bf0  SP::cXHTMLControlAppearance::Apply
//   00621c80  SetGlobalAppearance (AutoRefCount assignment)
//   00621cc0  uninitialized_copy<ControlDrawable>
//   00621d50  uninitialized_copy_backward<ControlDrawable>
//   00621db0  SP::cXHTMLControlAppearance::CreateHitMaskFromResource
//   00621ee0  SP::cXHTMLControlAppearance::cXHTMLControlAppearance
//   00621f00  SP::cXHTMLControlAppearance::~cXHTMLControlAppearance
//   00621f50  vector<ControlDrawable>::erase
//   00621fc0  vector<ControlDrawable>::DoInsertValue / insert
#include "types.h"

// ---- external callees -------------------------------------------------------------------
void __cdecl FUN_00621540(uint32_t key, const char* url);                    // 0x621540 SanitizeURL
bool __cdecl RegisterURL(uint32_t storeKey, uint32_t typeKey, const char* path);          // 0x6216b0
bool __cdecl RegisterInsecureURL(uint32_t storeKey, uint32_t typeKey, const char* path);  // 0x621770
uint32_t __cdecl FUN_00a35070(void* a, void* b, void* c);                    // 0xa35070
void* __cdecl FUN_00621d10(void* a, void* b, void* c);                       // 0x621d10
void* __cdecl FUN_008de1a0();                                                // 0x8de1a0 (resource manager)
uint32_t __cdecl Hash_FNV1_String16(const void* s, uint32_t basis, int a);    // 0x932f30
void* __cdecl EA_Allocate(unsigned size, const char* name, int a, int b,
                          const char* file, int line);                       // 0xf473a0
void  __cdecl EA_Free(void* p);                                              // 0xf47380

extern const char* gURL1520cf4;   // 0x1520cf4
extern const char* gURL1520cf8;   // 0x1520cf8
extern const char* gURL1520cfc;   // 0x1520cfc
extern const char* gURL1520d00;   // 0x1520d00
extern void* gAppearance1520f9c;  // 0x15f5f9c

static inline void** Vt(void* p) { return *(void***)p; }

// @ 0x00621830
void SP_Pollen_InitURLs() {
  FUN_00621540(0x5384c3f, gURL1520cf4);
  FUN_00621540(0x53dd8c2, gURL1520cf8);
  FUN_00621540(0x55bdfd6, gURL1520cfc);
  FUN_00621540(0x55e9027, gURL1520d00);
  RegisterURL(0x539f4e1, 0x5384c3f, "/pollinator/handshake");
  RegisterURL(0x539f864, 0x5384c3f, "/pollinator/public-interface/login");
  RegisterURL(0x5387572, 0x5384c3f, "/pollinator/public-interface/AssetUploadServlet");
  RegisterURL(0x68cb17d, 0x5384c3f, "/pollinator/upload/status/");
  RegisterURL(0x539e135, 0x5384c3f, "/pollinator/atom/randomAsset");
  RegisterURL(0x539e146, 0x5384c3f, "/pollinator/atom/subscribe");
  RegisterURL(0x539e14b, 0x5384c3f, "/pollinator/atom/userAssets");
  RegisterURL(0x539e150, 0x5384c3f, "/pollinator/atom/static/");
  RegisterURL(0x539f3e1, 0x5384c3f, "/pollinator/atom/creatureMatch");
  RegisterURL(0x539f69d, 0x5384c3f, "/pollinator/atom/delete");
  RegisterURL(0x539f705, 0x5384c3f, "/pollinator/atom/unsubscribe");
  RegisterURL(0x539f953, 0x5384c3f, "/pollinator/telemetry");
  RegisterURL(0x539f86b, 0x5384c3f, "/pollinator/atom/subscribe");
  RegisterURL(0x541aed9, 0x5384c3f, "/pollinator/atom/asset/");
  RegisterURL(0xe10f3837, 0x5384c3f, "/pollinator/atom/asset");
  RegisterURL(0x5efa12b, 0x53dd8c2, "/community/assetBrowser/deleteAsset/");
  RegisterURL(0x5ffeebf, 0x5384c3f, "/pollinator/event/upload");
  RegisterURL(0x538766b, 0x53dd8c2, "/community/auth/registerNew");
  RegisterURL(0x53f0df9, 0x53dd8c2, "/community/assetBrowser/comment/");
  RegisterURL(0xf4a5bd1e, 0x53dd8c2, "/community/assetBrowser/requiredPacks");
  RegisterInsecureURL(0x55192fa, 0x53dd8c2, "/static/thumb/");
  RegisterInsecureURL(0x56bbbd1, 0x53dd8c2, "/community/auth/help");
  RegisterURL(0x5908ef2, 0x53dd8c2, "/community/assetBrowser/createSporecast");
  RegisterURL(0x539e13b, 0x53dd8c2, "/community/assetBrowser/createSporecast");
  RegisterURL(0x539e141, 0x53dd8c2, "/community/assetBrowser/editSporecast");
  RegisterURL(0x53dd7c4, 0x53dd8c2, "/community/assetBrowser/home");
  RegisterURL(0x5436cc92, 0x53dd8c2, "/community/assetBrowser/findBuddy");
  RegisterURL(0x5436cc93, 0x53dd8c2, "/community/assetBrowser/findSporecast");
  RegisterURL(0x5436cc94, 0x53dd8c2, "/community/assetBrowser/createSporecast");
  RegisterURL(0x5436cc95, 0x53dd8c2, "/community/assetBrowser/store");
  RegisterURL(0x34c040d5, 0x53dd8c2, "/community/assetBrowser/achievements");
  RegisterURL(0x615ae67, 0x53dd8c2, "/community/assetBrowser/singleDownload");
  RegisterURL(0x62ec46a, 0x53dd8c2, "/community/assetBrowser/profile/");
  RegisterURL(0x53c3e41, 0x53dd8c2, "/community/public-interface/SnapshotUploadServlet");
  RegisterURL(0x56518ed, 0x53dd8c2, "/community-csa/csa/CSABrowser.html");
  RegisterURL(0x55bd0c8, 0x55bdfd6, "/youtube/accounts/ClientLogin");
  RegisterInsecureURL(0x55e8f9c, 0x55e9027, "/feeds/users");
  RegisterURL(0x56cded4, 0x53dd8c2, "/community/public-interface/VideoPathUploadServlet");
  RegisterURL(0x811c9dc5, 0x53dd8c2, "/community/assetBrowser/leaderBoardDlg/");
  RegisterURL(0x811c9dc7, 0x53dd8c2, "/community/assetBrowser/largeCard/gamesUsed/");
  RegisterURL(0x811c9dc8, 0x53dd8c2, "/community/assetBrowser/largeCard/comments/");
  RegisterURL(0x811c9dc9, 0x53dd8c2, "/community/assetBrowser/largeCard/leaderboard/");
  RegisterURL(0xf8671bdb, 0x53dd8c2, "/community/assetBrowser/rate");
}

// ---------------------------------------------------------------------------------------------
// Element / container types.
// ---------------------------------------------------------------------------------------------
struct Drawable {
  virtual void dtor();     // +0x00 (slot 0)
  virtual void AddRef();   // +0x04 (slot 1)
  virtual void Release();  // +0x08 (slot 2)
};
struct ControlDrawable {
  uint32_t  mId;          // +0x00
  Drawable* mpDrawable;   // +0x04
  void AddRefIfAny() { if (mpDrawable) ((void(__thiscall*)(Drawable*))Vt(mpDrawable)[0])(mpDrawable); }
};
struct WinXHTML {
  void SetFormControlDrawable(uint32_t id, Drawable* p);
  void SetScrollbarDrawable(int which, void* p);
};

struct cXHTMLControlAppearance {
  virtual void v0();          // +0x00
  uint32_t mPad4;             // +0x04
  ControlDrawable* mpBegin;   // +0x08
  ControlDrawable* mpEnd;     // +0x0c
  ControlDrawable* mpCap;     // +0x10
  uint32_t mPad14;            // +0x14
  uint32_t mPad18;            // +0x18
  Drawable* mpScroll1;        // +0x1c
  Drawable* mpScroll2;        // +0x20

  cXHTMLControlAppearance();                       // 0x621ee0
  ~cXHTMLControlAppearance();                      // 0x621f00
  void Apply(WinXHTML* w);                         // 0x621bf0
  bool CreateHitMaskFromResource(int* p1, int* p2, void** out);  // 0x621db0
};

// @ 0x00621bf0
void cXHTMLControlAppearance::Apply(WinXHTML* w) {
  if (w == 0) return;
  ControlDrawable* e = mpEnd;
  for (ControlDrawable* p = mpBegin; p != e; ++p)
    w->SetFormControlDrawable(p->mId, p->mpDrawable);
  w->SetScrollbarDrawable(0, mpScroll2 ? (char*)mpScroll2 + 0xc : 0);
  if (mpScroll1) w->SetScrollbarDrawable(1, (char*)mpScroll1 + 0xc);
  else w->SetScrollbarDrawable(1, 0);
}

// @ 0x00621c80
void SetGlobalAppearance(Drawable* p) {
  Drawable* old = (Drawable*)gAppearance1520f9c;
  if (p != old) {
    if (p) ((void(__thiscall*)(Drawable*))Vt(p)[1])(p);   // AddRef
    gAppearance1520f9c = p;
    if (old) ((void(__thiscall*)(Drawable*))Vt(old)[2])(old);  // Release
  }
}

// @ 0x00621cc0
ControlDrawable* UninitCopy(ControlDrawable* first, ControlDrawable* last, ControlDrawable* dest) {
  while (first != last) {
    if (dest != 0) {
      dest->mId = first->mId;
      dest->mpDrawable = first->mpDrawable;
      if (dest->mpDrawable)
        ((void(__thiscall*)(Drawable*))Vt(dest->mpDrawable)[0])(dest->mpDrawable);
    }
    ++first;
    ++dest;
  }
  return dest;
}

// @ 0x00621d50
ControlDrawable* UninitCopyBackward(ControlDrawable* first, ControlDrawable* last,
                                    ControlDrawable* destEnd) {
  while (last != first) {
    --last;
    --destEnd;
    destEnd->mId = last->mId;
    Drawable* p = last->mpDrawable;
    Drawable* old = destEnd->mpDrawable;
    if (p != old) {
      if (p) ((void(__thiscall*)(Drawable*))Vt(p)[0])(p);
      destEnd->mpDrawable = p;
      if (old) ((void(__thiscall*)(Drawable*))Vt(old)[1])(old);
    }
  }
  return destEnd;
}

// @ 0x00621db0
bool cXHTMLControlAppearance::CreateHitMaskFromResource(int* p1, int* p2, void** out) {
  uint32_t hash = Hash_FNV1_String16(p2, 0x811c9dc5, 0);
  void* local18 = (void*)0x2f7d0004;
  (void)local18;
  uint32_t localc = hash;
  (void)localc;
  *out = 0;
  void* req = 0;
  void* mgr = FUN_008de1a0();
  if (req) { void* o = req; req = 0; ((void(__thiscall*)(void*))Vt(o)[1])(o); }
  bool ok = ((bool(__thiscall*)(void*, void*, void**, int, int, int, void*))Vt(mgr)[3])
               (mgr, &localc, &req, 0, 0, 0, &local18);
  if (ok) {
    if (p1 == 0) return false;
    void* r = ((void*(__thiscall*)(void*, uint32_t))Vt(p1)[3])(p1, 0xf074e1c8);
    if (r) {
      *out = r;
      ((void(__thiscall*)(void*))Vt(r)[0])(r);
      if (p1) ((void(__thiscall*)(void*))Vt(p1)[1])(p1);
      return true;
    }
  }
  if (p1) ((void(__thiscall*)(void*))Vt(p1)[1])(p1);
  return false;
}

// @ 0x00621ee0
cXHTMLControlAppearance::cXHTMLControlAppearance()
    : mPad4(0), mpBegin(0), mpEnd(0), mpCap(0), mpScroll1(0), mpScroll2(0) {}

// @ 0x00621f00
cXHTMLControlAppearance::~cXHTMLControlAppearance() {
  if (mpScroll2) ((void(__thiscall*)(Drawable*))Vt(mpScroll2)[1])(mpScroll2);
  if (mpScroll1) ((void(__thiscall*)(Drawable*))Vt(mpScroll1)[1])(mpScroll1);
  if (mpBegin) EA_Free(mpBegin);
}

// @ 0x00621f50  vector<ControlDrawable>::erase(first,last) -- this = &vector
ControlDrawable* VectorErase(void* self, ControlDrawable* first, ControlDrawable* last) {
  ControlDrawable** pEnd = (ControlDrawable**)((char*)self + 4);
  uint32_t r = FUN_00a35070(last, *pEnd, first);
  if (r < (uint32_t)*pEnd) {
    int n = (int)((((uint32_t)*pEnd - r) - 1) >> 3) + 1;
    uint32_t* p = (uint32_t*)(r + 4);
    do {
      if (*p) ((void(__thiscall*)(void*))Vt((void*)*p)[1])((void*)*p);
      p += 2;
      --n;
    } while (n != 0);
  }
  *pEnd = (ControlDrawable*)((char*)*pEnd + (((char*)last - (char*)first) >> 3) * -8);
  return first;
}

// @ 0x00621fc0  vector<ControlDrawable>::DoInsertValue(position, value) -- this = &vector
void VectorInsert(void* self, ControlDrawable* position, const ControlDrawable& value) {
  ControlDrawable** pBegin = (ControlDrawable**)self;
  ControlDrawable** pEnd = (ControlDrawable**)((char*)self + 4);
  ControlDrawable** pCap = (ControlDrawable**)((char*)self + 8);
  ControlDrawable* end = *pEnd;
  if (end != *pCap) {
    if (position <= end && end < (ControlDrawable*)pEnd) position += 1;
    if (end) {
      end->mId = end[-1].mId;
      end->mpDrawable = end[-1].mpDrawable;
      if (end->mpDrawable)
        ((void(__thiscall*)(Drawable*))Vt(end->mpDrawable)[0])(end->mpDrawable);
    }
    UninitCopyBackward(position, end - 1, end);
    position->mId = value.mId;
    Drawable* p = value.mpDrawable;
    Drawable* old = position->mpDrawable;
    if (p != old) {
      if (p) ((void(__thiscall*)(Drawable*))Vt(p)[0])(p);
      position->mpDrawable = p;
      if (old) ((void(__thiscall*)(Drawable*))Vt(old)[1])(old);
    }
    *pEnd = end + 1;
    return;
  }
  int n = (int)(end - *pBegin);
  int cap;
  if (n == 0) cap = 1;
  else cap = n * 2;
  ControlDrawable* newBuf = 0;
  if (cap != 0)
    newBuf = (ControlDrawable*)EA_Allocate(cap * 8, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  ControlDrawable* mid = UninitCopy(*pBegin, position, newBuf);
  UninitCopyBackward(*pBegin, position, newBuf);
  if (mid) {
    mid->mId = value.mId;
    mid->mpDrawable = value.mpDrawable;
    if (mid->mpDrawable)
      ((void(__thiscall*)(Drawable*))Vt(mid->mpDrawable)[0])(mid->mpDrawable);
  }
  ControlDrawable* tail = UninitCopy(position, end, mid + 1);
  if (*pBegin && *(int*)((char*)*pBegin - 4) != 0) EA_Free(*pBegin);
  *pBegin = newBuf;
  *pEnd = tail;
  *pCap = newBuf + cap;
}
