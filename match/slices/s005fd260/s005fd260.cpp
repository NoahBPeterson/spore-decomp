// Slice s005fd260 - cImportExport import helpers + UI::AchievementNotifier + cSPUILayout helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "../s005fa8d0/s005fa8d0.h"

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

extern "C" __declspec(dllimport) int __cdecl tolower(int);

// ---------------------------------------------------------------------------------------------
// Masked address globals (retail .rdata/.data relocations; masked by chk on both sides).
// ---------------------------------------------------------------------------------------------
extern char vt_13eb384;   // 0x013eb384  cListenerBase base vtable
extern char vt_14426a0;   // 0x014426a0  second base vtable
extern char vt_13fa158;   // 0x013fa158  UI::AchievementNotifier vtable
extern char vt_13fa148;   // 0x013fa148  UI::AchievementNotifier vtable (+8)
extern char vt_13fa12c;   // 0x013fa12c  UI::AchievementNotifier vtable (+0xc)
extern char vt_13eb938;   // 0x013eb938  base-dtor vtable (+0xc)
extern char vt_13eb394;   // 0x013eb394  base-dtor vtable (+8)
extern char vt_13ec458;   // 0x013ec458  base-dtor vtable (+0)
extern char vt_13fa168;   // 0x013fa168  message-handler vtable
extern char g_66e6b90;    // 0x0066e6b90  window id
extern char g_66e6b98;    // 0x0066e6b98  window id
extern void* g_15fd918;   // 0x015fd918  _sAppProperties
extern char kEditorAllocName_13eb430[];  // 0x013eb430  ?kEditorAllocName@@3QBDB
extern char kAllocFile_13ebb38[];        // 0x013ebb38  allocator.h
extern char gStr_13f6b3c[];              // 0x013f6b3c
extern char gStr_13f3da0[];              // 0x013f3da0
extern wchar_t gStr_13fa16c[];           // 0x013fa16c  L"Achievement"
extern char gStr_13fa168[];              // 0x013fa168

// ---------------------------------------------------------------------------------------------
// Atomic intrusive refcount release at +8, exactly as inlined by the original.
// ---------------------------------------------------------------------------------------------
static __forceinline void ReleaseRef(volatile long* c)
{
  _InterlockedExchangeAdd(c, -1);
  long n = _InterlockedExchangeAdd(c, 0);
  if (n < 1) _InterlockedExchangeAdd(c, 1);
  else       _InterlockedExchangeAdd(c, 0);
}

// ---------------------------------------------------------------------------------------------
// thiscall-through-fastcall helpers (edx carries an unused dummy so `this` lands in ecx and the
// callee's `ret N` stays balanced).
// ---------------------------------------------------------------------------------------------
typedef void     (__fastcall *FnV0)(void*, void*);
typedef void     (__fastcall *FnV1)(void*, void*, void*);
typedef void     (__fastcall *FnV2)(void*, void*, void*, uint32_t);
typedef void     (__fastcall *FnV3i)(void*, void*, uint32_t, uint32_t, void*);
typedef void     (__fastcall *FnVFF)(void*, void*, float, float);
typedef void     (__fastcall *FnVW)(void*, void*, const wchar_t*);
typedef uint32_t (__fastcall *FnR0)(void*, void*);
typedef void*    (__fastcall *FnP0)(void*, void*);
typedef void*    (__fastcall *FnPv)(void*, void*, void*, uint32_t, void*);
typedef uint32_t (__fastcall *FnR6)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef void     (__fastcall *FnV3s)(void*, void*, uint32_t, void*, uint32_t);
typedef void*    (__fastcall *FnP1)(void*, void*, void*, uint32_t);

#define VTSLOT(obj, off) (*(void**)(*(char**)(obj) + (off)))

// ---------------------------------------------------------------------------------------------
// Retail callees (masked relocations).
// ---------------------------------------------------------------------------------------------
void*  MessageServer_67dcc0();                                  // 0x0067dcc0
void*  PropertyManager_67de30();                                // 0x0067de30
void*  ResourceManager_67dcd0();                                // 0x0067dcd0
void*  SP_App_67dd10();                                         // 0x0067dd10
void*  GetSystemAT_a206f0();                                    // 0x00a206f0
void*  FUN_0067dd60();                                          // 0x0067dd60
void   KillSetiEffects_435ed0(uint32_t id, void* at);           // 0x00435ed0
void   RemoveHandler_571db0(void*, void*, void*, void*, void*); // 0x00571db0
void     __fastcall GetImageResource_576650(void* refOut, void* dummy, void* res); // 0x00576650
void*  GetImageFromTexture_8060d0(int a, int b, int c, int d, int e); // 0x008060d0
void   FUN_008068d0(void* dst, void* img, int x);                // 0x008068d0
bool   GetPropertyAsKey_6a1250(void* list, uint32_t id, void* out);   // 0x006a1250 (cdecl)
void   GetPropertyAsText_6a1360(void* list, uint32_t id, void* out);  // 0x006a1360 (cdecl)
void     __fastcall cString_ctor_6b5060(void* self, void* dummy);      // 0x006b5060
void     __fastcall cString_dtor_6b5240(void* self, void* dummy);      // 0x006b5240
const wchar_t* __fastcall cString_GetText_6b55c0(void* self, void* dummy); // 0x006b55c0

uint32_t __fastcall FUN_008d3ac0(void* a, void* dummy);                  // 0x008d3ac0 (thiscall)
void*    __fastcall FUN_00688ed0(void* a, void* dummy, uint32_t i);      // 0x00688ed0 (thiscall)
void*    __fastcall FindWindowByID_8105b0(void* layout, void* dummy, uint32_t id, int recurse); // 0x008105b0
void     __fastcall SetVisibility_810590(void* layout, void* dummy, int on);                    // 0x00810590
bool     __fastcall LayoutInit_812160(void* layout, void* dummy, const wchar_t* name,
                                      uint32_t flags, int b, uint32_t c);                       // 0x00812160
void*    __fastcall ConnectionDialog_ctor_810000(void* p, void* dummy);                         // 0x00810000
bool     __fastcall ImportNewAsset_5fc330(void* self, void* dummy, const wchar_t* name, void* key); // 0x005fc330
void     __fastcall Key_DoInsertKey_4e3e10(void* vec, void* dummy, void* pos, const void* val);  // 0x004e3e10
void     __fastcall FillVec_push_back_4e19a0(void* vec, void* dummy, const void* val);           // 0x004e19a0
void     __fastcall FlagsVec_DoInsertValue_426730(void* vecEnd, void* dummy, void* pos, void* val); // 0x00426730
void     __fastcall FUN_00414e10(void* res, void* dummy, uint32_t typeID, void* outStr);        // 0x00414e10

// eastl/FileStream helpers used by the import deserializer.
struct FileStream {
  char pad[0x100];
  FileStream(const wchar_t* path);   // 0x00931e10
  ~FileStream();                     // 0x00931e70
  int  AddRef();                     // 0x009317b0
  bool Open(int a, int b, int c, int d);  // 0x009318f0
  void Close();                      // 0x00931a70
};
void RangeCoder_Serialize_68e1a0(void* rc, void* stream);             // 0x0068e1a0
void FUN_005f8ad0(void* self);                                        // 0x005f8ad0
void* FUN_005f95a0(void* a, void* b, uint32_t c);                     // 0x005f95a0
void FUN_005f8910(void* p);                                           // 0x005f8910
void SetupExportFolderPath_5f9310(void* self, uint32_t id, void* dst, uint32_t arg); // 0x005f9310
void RestoreImportTable_5fa290(void* self);                           // 0x005fa290
bool ScanForImports_5fd0a0(void* self);                               // 0x005fd0a0

// 0x006b family (system info / string / IO)
void CBig_ctor_6b8460(void* self);                                   // 0x006b8460
void SP_GetSystemInfo_6b8680(void* out);                             // 0x006b8680
uint32_t FNVHash_932e80(uint32_t v, uint32_t h, uint32_t dummy);     // 0x00932e80
uint32_t FNV1_String16_932f30(const wchar_t* s, uint32_t h, uint32_t dummy); // 0x00932f30
int GetDriveSerialNumber_932220(const wchar_t* drive, wchar_t* out); // 0x00932220
void StrCtor_473020(void* out, int zero, const void* lit, const void* src); // 0x00473020

float GetElapsedSeconds();   // 0x00805080
// Forward declaration so Update() can dispatch into SP::cSPPaletteItemUIHutStyle::Init.
namespace SP { struct cSPPaletteItemUIHutStyle { char mPad[0x188]; void Init(uint32_t id); }; }

// ---------------------------------------------------------------------------------------------
// Small helper structs.
// ---------------------------------------------------------------------------------------------
// 0x14-byte local as the original: begin/end/cap plus 8 bytes of untouched stack.
struct VecHandle { void* mpBegin; void* mpEnd; void* mpCap; uint32_t mPadA; uint32_t mPadB; };

struct ByteVec { uint8_t* mpBegin; uint8_t* mpEnd; uint8_t* mpCap; };

struct WStr16 { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; };

struct IterWK { void* mpNode; void* mpBucket; };

// The eastl NameKey map embedded at this+4 (its buckets at +8, count at +0xc).
struct MapWKStub {
  void* mpUnk0;            // +0x00
  void* mpBucketArray;     // +0x04
  uint32_t mnBucketCount;  // +0x08
  IterWK find(const WStr16& name);   // 0x005f8fe0
};

static __forceinline void OutPushKey(VecHandle* v, const Key& k)
{
  Key* e = (Key*)v->mpEnd;
  if (e < (Key*)v->mpCap) {
    v->mpEnd = e + 1;
    if (e) *e = k;
  } else {
    Key_DoInsertKey_4e3e10(v, 0, v->mpEnd, &k);
  }
}

static __forceinline void FlagsPush(ByteVec* v, uint8_t x)
{
  if (v->mpEnd < v->mpCap) {
    *v->mpEnd++ = x;
  } else {
    FlagsVec_DoInsertValue_426730(&v->mpEnd, 0, v->mpEnd, &x);
  }
}

// ---------------------------------------------------------------------------------------------
// UI::AchievementNotifier (layout: vptrs at +0/+8/+0xc, data from +0x10).
// ---------------------------------------------------------------------------------------------
namespace UI {

class AchievementNotifier {
 public:
  char mPad[0x188];

  AchievementNotifier();      // 0x005fdeb0
  ~AchievementNotifier();     // 0x005fdbb0
  bool     TextureReady();    // 0x005fde30
  void ToggleWindow(int on);  // 0x005fdaa0
  void SetupLayout();         // 0x005fe050
  void Update();              // 0x005fdf40
};

// @ 0x005fdeb0
AchievementNotifier::AchievementNotifier()
{
  char* t = (char*)this;
  float z = 0.0f;
  *(uint32_t*)(t + 0x04) = 0;
  *(void**)(t + 0x08) = &vt_13eb384;
  *(void**)(t + 0x0c) = &vt_14426a0;
  *(void**)(t + 0x00) = &vt_13fa158;
  *(void**)(t + 0x08) = &vt_13fa148;
  *(void**)(t + 0x0c) = &vt_13fa12c;
  *(uint32_t*)(t + 0x10) = 0;
  *(uint32_t*)(t + 0x14) = 0;
  *(uint32_t*)(t + 0x18) = 0;
  *(uint32_t*)(t + 0x1c) = 0;
  *(uint32_t*)(t + 0x20) = 0;
  *(uint32_t*)(t + 0x30) = 0;
  *(uint32_t*)(t + 0x34) = 0;
  *(uint32_t*)(t + 0x38) = 0;
  *(uint32_t*)(t + 0x48) = 0;
  *(uint32_t*)(t + 0x4c) = 0;
  *(uint32_t*)(t + 0x50) = 0;
  *(uint32_t*)(t + 0x54) = 0;
  *(uint32_t*)(t + 0x58) = 0;
  *(uint32_t*)(t + 0x5c) = 0;
  *(uint32_t*)(t + 0x60) = 0;
  *(uint32_t*)(t + 0x44) = 0;
  *(float*)(t + 0x2c) = z;
  *(uint32_t*)(t + 0x24) = 0;
  *(float*)(t + 0x28) = z;
}

// @ 0x005fdbb0
AchievementNotifier::~AchievementNotifier()
{
  char* t = (char*)this;
  *(void**)(t + 0x00) = &vt_13fa158;
  *(void**)(t + 0x08) = &vt_13fa148;
  *(void**)(t + 0x0c) = &vt_13fa12c;

  void* p = *(void**)(t + 0x60);
  if (p) ((FnV0)VTSLOT(p, 0x04))(p, 0);
  p = *(void**)(t + 0x5c);
  if (p) ((FnV0)VTSLOT(p, 0x04))(p, 0);
  p = *(void**)(t + 0x58);
  if (p) ((FnV0)VTSLOT(p, 0x04))(p, 0);

  void* img = *(void**)(t + 0x48);
  if (img) ReleaseRef((volatile long*)((char*)img + 8));

  void* bp = *(void**)(t + 0x30);
  if (bp && *(int*)((char*)bp - 4) != 0) operator delete(bp);

  void* h = *(void**)(t + 0x10);
  if (h) {
    RemoveHandler_571db0(h, *(void**)(t + 0x14), *(void**)(t + 0x18),
                         *(void**)(t + 0x1c), *(void**)(t + 0x20));
    *(void**)(t + 0x10) = 0;
  }

  *(void**)(t + 0x0c) = &vt_13eb938;
  *(void**)(t + 0x08) = &vt_13eb394;
  *(void**)(t + 0x00) = &vt_13ec458;
}

// @ 0x005fde30
bool AchievementNotifier::TextureReady()
{
  char* t = (char*)this;
  void* img = *(void**)(t + 0x48);
  if (img != 0) {
    if ((*(uint8_t*)((char*)img + 4) & 1) != 0) {
      void* w = *(void**)(t + 0x58);
      void* tex = GetImageFromTexture_8060d0(*(int*)(t + 0x4c), *(int*)(t + 0x54),
                                             -1, -1, -1);
      FUN_008068d0(w, tex, -1);
      void* q = *(void**)(t + 0x48);
      if (q != 0) {
        *(void**)(t + 0x48) = 0;
        ReleaseRef((volatile long*)((char*)q + 8));
      }
    } else {
      return false;
    }
  }
  return true;
}

// @ 0x005fdaa0
void AchievementNotifier::ToggleWindow(int on)
{
  char* t = (char*)this;
  void* w = FindWindowByID_8105b0(*(void**)(t + 0x44), 0, 0x6244c50u, 1);
  if (w == 0) return;

  if (on) {
    void* app = SP_App_67dd10();
    uint32_t r = ((FnR0)VTSLOT(app, 0x38))(app, 0);
    void* id;
    if (r == 0xdbdba1u)       id = &g_66e6b98;
    else if (r == 0x2ccd1d2u) id = &g_66e6b98;
    else                      id = &g_66e6b90;

    void* w2 = FindWindowByID_8105b0(*(void**)(t + 0x44), 0, (uint32_t)id, 1);
    if (id != 0) {
      float* v = (float*)((FnP0)VTSLOT(w2, 0x38))(w2, 0);
      ((FnVFF)VTSLOT(w, 0x70))(w, 0, v[0], v[1]);
    }
    void* sub = ((FnP0)VTSLOT(w, 0x10))(w, 0);
    if (sub != 0) {
      void* d = ((FnP0)VTSLOT(sub, 0x10))(sub, 0);
      ((FnV1)VTSLOT(d, 0xe8))(d, 0, w);
    }
    void* at = GetSystemAT_a206f0();
    void* a = at ? ((FnP0)VTSLOT(at, 0x20))(at, 0) : 0;
    KillSetiEffects_435ed0(0x12e11b1b, a);
  }
  ((FnV2)VTSLOT(w, 0x7c))(w, 0, (void*)1, (uint32_t)on);
}

// Assign `nw` into a refcounted window slot (AddRef new / Release old), as the original does.
static __forceinline void AssignWindow(void** slot, void* nw)
{
  void* old = *slot;
  if (nw == old) return;
  if (nw)  ((FnV0)VTSLOT(nw, 0x00))(nw, 0);
  *slot = nw;
  if (old) ((FnV0)VTSLOT(old, 0x04))(old, 0);
}

// @ 0x005fe050
void AchievementNotifier::SetupLayout()
{
  char* t = (char*)this;

  // vector<bool> at +0x30 (ByteVector): drop all elements.
  char* begin = *(char**)(t + 0x30);
  char* end   = *(char**)(t + 0x34);
  memcpy(begin, end, 0);
  int n = (int)(end - begin);
  *(char**)(t + 0x34) = end - ((n >> 2) << 2);
  *(uint32_t*)(t + 0x24) = 0;

  void* layout = operator new[](0x18, gStr_13f6b3c, 0, 0, 0, 0);
  if (layout) ConnectionDialog_ctor_810000(layout, 0);
  *(void**)(t + 0x44) = layout;

  LayoutInit_812160(layout, 0, gStr_13fa16c, 0x40464100u, 1, 0x5b598f7u);

  void* win = FindWindowByID_8105b0(layout, 0, 0xffffffffu, 1);
  if (win) ((FnV1)VTSLOT(win, 0x104))(win, 0, t + 0xc);
  SetVisibility_810590(layout, 0, 0);

  void* sv = MessageServer_67dcc0();
  *(void**)(t + 0x10) = sv;
  *(void**)(t + 0x14) = t + 8;
  *(void**)(t + 0x18) = &gStr_13fa168;
  *(uint32_t*)(t + 0x1c) = 1;
  *(uint32_t*)(t + 0x20) = 0;
  if (sv && (t + 8)) ((FnV2)VTSLOT(sv, 0x24))(sv, 0, (void*)(t + 8), 0x5c6930eu);

  AssignWindow((void**)(t + 0x58), FindWindowByID_8105b0(layout, 0, 0x5244c08u, 1));
  AssignWindow((void**)(t + 0x5c), FindWindowByID_8105b0(layout, 0, 0x52432e0u, 1));
  AssignWindow((void**)(t + 0x60), FindWindowByID_8105b0(layout, 0, 0x5244c68u, 1));
}

// @ 0x005fdf40
void AchievementNotifier::Update()
{
  char* t = (char*)this;
  float elapsed = GetElapsedSeconds();
  float dt = elapsed - *(float*)(t + 0x2c);
  *(float*)(t + 0x2c) = elapsed;
  int state = *(int*)(t + 0x24);
  if (state == 0) {
    void* a = *(void**)(t + 0x30);
    void* b = *(void**)(t + 0x34);
    if (a != b) {
      void* elem = *(void**)((char*)b - 4);
      if (elem != 0) ((SP::cSPPaletteItemUIHutStyle*)elem)->Init(0);
      *(void**)(t + 0x34) = (char*)b - 4;
      *(int*)(t + 0x24) = 1;
      return;
    }
  } else if (state == 1) {
    if (TextureReady()) {
      SetVisibility_810590(*(void**)(t + 0x44), 0, 1);
      ToggleWindow(1);
      *(float*)(t + 0x28) = 0.0f;
      *(int*)(t + 0x24) = 2;
      return;
    }
  } else if (state == 2) {
    float timer = *(float*)(t + 0x28) + dt;
    *(float*)(t + 0x28) = timer;
    if (5.0f < timer) {
      void* w = FindWindowByID_8105b0(*(void**)(t + 0x44), 0, 0x6244c50u, 1);
      if (w) ((FnV2)VTSLOT(w, 0x7c))(w, 0, (void*)1, 0);
      *(float*)(t + 0x28) = 0.0f;
      *(int*)(t + 0x24) = 3;
      return;
    }
  } else if (state == 3) {
    float timer = *(float*)(t + 0x28) + dt;
    *(float*)(t + 0x28) = timer;
    if (3.0f < timer) {
      SetVisibility_810590(*(void**)(t + 0x44), 0, 0);
      *(int*)(t + 0x24) = 0;
    }
  }
}

}  // namespace UI

// ---------------------------------------------------------------------------------------------
// SP::cSPPaletteItemUIHutStyle
// ---------------------------------------------------------------------------------------------
namespace SP {
struct cString {
  char mPlaceholderId[0x14];
  cString();                       // 0x006b5060
  ~cString();                      // 0x006b5240
  const wchar_t* GetText();        // 0x006b55c0
};
}  // namespace SP

// @ 0x005fdca0
void SP::cSPPaletteItemUIHutStyle::Init(uint32_t id)
{
  char* t = (char*)this;

  void* list = 0;                         // the property-list returned by the vcall
  uint32_t key[3] = { 0, 0, 0 };

  char cA[0x14];                          // cString for 0x5ee1fac (window at +0x5c)
  char cB[0x14];                          // cString for 0x5ee1fba (window at +0x60)

  cString_ctor_6b5060(cA, 0);
  cString_ctor_6b5060(cB, 0);

  void* pm = PropertyManager_67de30();
  if (list) { void* old = list; list = 0; ((FnV0)VTSLOT(old, 0x04))(old, 0); }

  ((FnV3i)VTSLOT(pm, 0x2c))(pm, 0, id, 0x5befd27u, &list);

  GetPropertyAsText_6a1360(list, 0x5ee1facu, cA);
  GetPropertyAsText_6a1360(list, 0x5ee1fbau, cB);

  void* wA = *(void**)(t + 0x5c);
  if (wA) ((FnVW)VTSLOT(wA, 0x80))(wA, 0, cString_GetText_6b55c0(cA, 0));
  void* wB = *(void**)(t + 0x60);
  if (wB) ((FnVW)VTSLOT(wB, 0x80))(wB, 0, cString_GetText_6b55c0(cB, 0));

  if (GetPropertyAsKey_6a1250(list, 0x5ee1fbbu, key)) {
    key[1] = 0x2f7d0004u;
    void* mgr = FUN_0067dd60();
    void* res = ((FnP1)VTSLOT(mgr, 0x1c))(mgr, 0, key, 0);
    GetImageResource_576650(t + 0x48, 0, res);
    *(uint32_t*)(t + 0x4c) = key[0];
    *(uint32_t*)(t + 0x50) = key[1];
    *(uint32_t*)(t + 0x54) = key[2];
  } else {
    void* img = *(void**)(t + 0x48);
    if (img != 0) {
      *(void**)(t + 0x48) = 0;
      ReleaseRef((volatile long*)((char*)img + 8));
    }
  }

  cString_dtor_6b5240(cB, 0);
  cString_dtor_6b5240(cA, 0);
  if (list) ((FnV0)VTSLOT(list, 0x04))(list, 0);
}

// ---------------------------------------------------------------------------------------------
// The message-handler object (HandlerStub::Handler) + the importer + the cImportExport::Init.
// ---------------------------------------------------------------------------------------------
struct HandlerStub {
  char mPad[0x188];
  bool Handler(uint32_t id, void* p);     // 0x005fda40
  bool Init(uint8_t useFirst);            // 0x005fd880
  void ImportAssets(void* a, void* b);    // 0x005fd260
};

// @ 0x005fda40
bool HandlerStub::Handler(uint32_t id, void* p)
{
  if (id == 0x24ce123 && p) {
    VecHandle v;
    v.mpBegin = 0; v.mpEnd = 0; v.mpCap = 0;
    ImportAssets(p, &v);
    if (v.mpBegin && ((int*)v.mpBegin)[-1]) operator delete(v.mpBegin);
  }
  return true;
}

// @ 0x005fd880
bool HandlerStub::Init(uint8_t useFirst)
{
  char* t = (char*)this;

  char sysInfo[0xd8];
  CBig_ctor_6b8460(sysInfo);
  SP_GetSystemInfo_6b8680(sysInfo);

  uint32_t h = FNVHash_932e80(*(uint32_t*)(sysInfo + 0x04), 0x811c9dc5u, 0);
  *(uint32_t*)(t + 0x44) = h;
  h = FNVHash_932e80(*(uint32_t*)(sysInfo + 0x60), h, 0);
  *(uint32_t*)(t + 0x44) = h;

  WStr16 driveStr;
  driveStr.mpBegin = 0; driveStr.mpEnd = 0; driveStr.mpCapacity = 0;
  StrCtor_473020(&driveStr, 0, gStr_13f3da0, 0);
  wchar_t sn[0x20];
  int r = GetDriveSerialNumber_932220(driveStr.mpBegin, sn);
  if (r == 10) {
    h = FNV1_String16_932f30(sn, h, 0);
    *(uint32_t*)(t + 0x44) = h;
  }

  *(uint8_t*)(t + 0x184) = useFirst;

  SetupExportFolderPath_5f9310(t, 0x54a8fe1u, t + 0x114, 0xffffffffu);
  if (*(int*)(*(int*)((char*)g_15fd918 + 0x3c) + 0x118) == 0) {
    SetupExportFolderPath_5f9310(t, 0x54a8fe0u, t + 0x104, 0xffffffffu);
    SetupExportFolderPath_5f9310(t, 0x54a8fe2u, t + 0x124, 0xffffffffu);
    SetupExportFolderPath_5f9310(t, 0x54a8fe3u, t + 0x134, 0xffffffffu);
    SetupExportFolderPath_5f9310(t, 0x54a8fe4u, t + 0x144, 0xffffffffu);
    SetupExportFolderPath_5f9310(t, 0x54a8fe5u, t + 0x154, 0xffffffffu);
    SetupExportFolderPath_5f9310(t, 0x55d09dau, t + 0x164, 0xffffffffu);
    SetupExportFolderPath_5f9310(t, 0x8d780fdeu, t + 0x174, 0xbf170c98u);
  }

  RestoreImportTable_5fa290(t);
  if (ScanForImports_5fd0a0(t))
    FUN_005f8ad0(t);

  void* sv = MessageServer_67dcc0();
  ((FnV2)VTSLOT(sv, 0x24))(sv, 0, t, 0x24ce123u);

  FUN_005f8910(sysInfo);
  return true;
}

// @ 0x005fd260
void HandlerStub::ImportAssets(void* a, void* b)
{
  char* t = (char*)this;
  VecHandle* out = (VecHandle*)b;

  uint32_t count = FUN_008d3ac0(a, 0);

  ByteVec flags;
  flags.mpBegin = 0; flags.mpEnd = 0; flags.mpCap = 0;

  for (uint32_t i = 0; i < count; ++i) {
    const wchar_t* src = (const wchar_t*)FUN_00688ed0(a, 0, i);

    // Build the lowercased, '/'-normalised name.
    WStr16 name;
    uint32_t len = 0;
    while (src[len]) ++len;
    uint32_t n = len + 1;
    if (n < 2) {
      name.mpBegin = eastl::gEmptyString16;
      name.mpCapacity = eastl::gEmptyString16 + 1;
    } else {
      name.mpBegin = (wchar_t*)operator new[](n * 2, kEditorAllocName_13eb430, 0, 0,
                                              kAllocFile_13ebb38, 0xd1);
      name.mpCapacity = name.mpBegin + n;
    }
    memcpy(name.mpBegin, src, len * 2);
    name.mpEnd = name.mpBegin + len;
    *name.mpEnd = 0;
    for (wchar_t* q = name.mpBegin; q < name.mpEnd; ++q) {
      uint32_t c = (uint32_t)*q;
      if (c < 0x100) *q = (wchar_t)tolower((int)(c & 0xff));
    }
    for (uint32_t j = 0; j < len; ++j)
      if (name.mpBegin[j] == 0x5c) name.mpBegin[j] = 0x2f;

    Key key;
    key.instanceID = 0; key.typeID = 0; key.groupID = 0;

    MapWKStub* map = (MapWKStub*)(t + 4);
    IterWK it = map->find(name);
    void* node = it.mpNode;
    void* endNode = ((void**)map->mpBucketArray)[map->mnBucketCount];

    if (node != endNode) {
      Key* found = (Key*)((char*)node + 0x10);
      OutPushKey(out, *found);
      FlagsPush(&flags, 0);
    } else if (!ImportNewAsset_5fc330(t, 0, src, &key)) {
      if (key.instanceID != 0xffffffffu || key.typeID != 0xffffffffu ||
          key.groupID != 0xffffffffu) {
        OutPushKey(out, key);
        FlagsPush(&flags, 0);
      }
    } else {
      // Reload the freshly-imported asset through the resource manager and reserialize.
      uint32_t kk[4];
      kk[0] = key.instanceID;
      kk[1] = 0x30bdee3u;
      kk[2] = key.groupID;
      kk[3] = 0;

      void* res = 0;
      void* mgr = ResourceManager_67dcd0();
      if (res) { void* old = res; res = 0; ((FnV0)VTSLOT(old, 0x04))(old, 0); }
      uint32_t ok = ((FnR6)VTSLOT(mgr, 0x0c))(mgr, 0, kk, &res, 0, 0, 0, 0);
      if (ok) {
        if (res) ((FnV2)VTSLOT(res, 0x0c))(res, 0, 0, 0x30bdee3u);

        WStr16 s;
        s.mpBegin = eastl::gEmptyString16;
        s.mpEnd = eastl::gEmptyString16;
        s.mpCapacity = eastl::gEmptyString16 + 1;
        FUN_00414e10(res, 0, key.typeID, &s);
        if (FUN_005f97c0(res, (void*)(uintptr_t)key.typeID, &s, 0, 0)) {
          FileStream fs(name.mpBegin);
          fs.AddRef();
          if (fs.Open(3, 1, 1, 0)) {
            RangeCoder_Serialize_68e1a0(t + 0x88, &fs);
            fs.Close();
            FUN_005f7970(&s);

            void* pk = FUN_005f9080(0);
            FUN_005f8320(pk);
            FUN_005f9470(&s, kk, 0);
            FUN_005f90c0(pk, 0, 0, 0);
            FUN_005f8390(pk);
            FUN_005f95a0(&s, kk, 0);
            FUN_005f8ad0(t);
            FillVec_push_back_4e19a0(out, 0, &key);
            FlagsPush(&flags, 1);
          }
          if ((((int)s.mpCapacity - (int)s.mpBegin) & ~1) > 2 && s.mpBegin &&
              s.mpBegin != eastl::gEmptyString16)
            operator delete[](s.mpBegin);
        }
      }
      if (res) ((FnV0)VTSLOT(res, 0x04))(res, 0);
    }

    if (name.mpBegin != eastl::gEmptyString16 &&
        (((int)name.mpCapacity - (int)name.mpBegin) & ~1) > 2)
      operator delete[](name.mpBegin);
  }

  void* sv = MessageServer_67dcc0();
  if (out->mpBegin == out->mpEnd) {
    ((FnV3s)VTSLOT(sv, 0x14))(sv, 0, 0x60b3d03u, 0, 0);
  } else {
    struct Payload { void* out; void* flags; uint32_t zero; } pl;
    pl.out = out; pl.flags = &flags; pl.zero = 0;
    ((FnV3s)VTSLOT(sv, 0x14))(sv, 0, 0x5132389u, &pl, 0);
  }

  if (flags.mpBegin && ((int*)flags.mpBegin)[-1]) operator delete(flags.mpBegin);
}