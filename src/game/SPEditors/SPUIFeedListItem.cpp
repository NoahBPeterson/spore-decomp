// src/game/SPEditors/SPUIFeedListItem.cpp -- migrated from slice(s) s00669f50, s00669430, s00668be0, s00666cb0, s00665d30 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIFeedListItem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUIFeedListItem.h"
#include "cSPUILayout.h"
#include <intrin.h>
#include "cSPColorRGBA.h"
#include "SP/cString.h"
#include <string.h>

// ---- items of slice s00665d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Obj184 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  char padA[5];
  bool b9;
  bool bA;
  void SomeMethod();
  void SetKey(const float* v, int a);
  void GetKey(float* out);
};
struct cSPUILayout_s0066_5d30 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  void Shutdown(int);  // 0x00811ad0 (cSPUILayout::Shutdown)
  void Init(const void* p, int a, uint32_t id);  // 0x008120d0 (cSPUILayout::Init)
  void SetParentWin(void* w, int a, uint32_t id);  // 0x008121b0 (cSPUILayout::SetParentWin)
};
struct Obj90 {
  bool Method(int);
};
struct CFeed {
  char pad00[0x14];
  bool m14;              // +0x14
  char pad15[0x4b];      // 0x15..0x60
  void* m60;             // +0x60
  void* m64;             // +0x64  cSPUILayout*
  float m68, m6c, m70, m74;  // +0x68..+0x78
  char pad78[0xc];       // 0x78..0x84
  bool  m84;             // +0x84
  char pad85[7];         // 0x85..0x8c
  float m8c;             // +0x8c
  void* m90;             // +0x90
  void* m94;             // +0x94
  char pad98[0xc];       // 0x98..0xa4
  void* ma4;             // +0xa4
  void* ma8;             // +0xa8
  char padAC[8];         // 0xac..0xb4
  void* mb4;             // +0xb4
  char padB8[0x5c];      // 0xb8..0x114
  void* m114;            // +0x114
  int m118, m11c, m120, m124;  // +0x118
  char pad128[0x14];     // 0x128..0x13c
  int m13c;              // +0x13c
  char pad140[0x38];     // 0x140..0x178
  int m178;              // +0x178
  int m17c;              // +0x17c
  void* m180;            // +0x180
  Obj184* m184;          // +0x184

  bool IsKnownID() const;
  bool IsKnownState() const;
  void SetDefault(int unused);
  void Teardown();
  void SetIconKey(const float* v);
  float* GetIconKey(float* out);
  void Reserve(int a, int b);
  bool CheckFlag(bool b);
  bool Action(int* p);
};
void RemoveHandler(int a, int b, int c, int d, int e);
void vec_reserve(int a, uint32_t id, int b, int c);
struct VObj { void** vt; };
typedef void* (__thiscall *FnV0)(void*);
typedef void  (__thiscall *FnV1p)(void*, void*);
typedef void  (__thiscall *FnV1i)(void*, int);
typedef void  (__thiscall *FnV2b)(void*, int, bool);
typedef void* (__thiscall *FnV0i)(void*, int);
typedef bool  (__thiscall *FnVb1i)(void*, int, void**);
struct Asset { char pad[0x18]; void* m18; };
Asset* AssetBrowser();
struct Prop {
  void** vt;
  float* AsVec();          // FUN_006bb610
};
void* GetFloatProp2(void* obj, uint32_t key, float* out);
int wcscmp(const wchar_t*, const wchar_t*);
struct CItem {
  char pad[0xa4];
  float mActualHeight;   // +0xa4
  void* mBg;             // +0xa8
  void Refresh(unsigned short* s);
};
// ---- items of slice s00665d30 end

// ---- items of slice s00666cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int gVt6f0_0, gVt6f0_1, gVt6f0_2, gVt6f0_3;
extern int gVT_base0, gVT_base1, gVT_base2;
typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void  (__thiscall *FnVoidII)(void*, int, int);
typedef void* (__thiscall *FnPtrV)(void*);
typedef void  (__thiscall *FnVoidIP)(void*, int, void*);
#define VT(p) (*(void***)(p))
void  __cdecl EASTL_allocator_deallocate(void* p);            // 0x00f47380
void  __cdecl FUN_00571db0(void* h, void* a, void* b, void* c, void* d); // RemoveHandler
void* __cdecl EA_Audio_GetSystemAT();                         // 0x00a206f0
void* __cdecl SP_MessageServer();                             // 0x0067dcc0
void  __stdcall WString_Assign(void* a, void* b);             // 0x00423650
struct P184Obj { void FUN_00829160(int v); };      // 0x00829160
struct FeedItem {
    void       FUN_00666cb0();
    void       FUN_006673a0(bool sel);
    FeedItem*  FUN_006676b0(unsigned flags);
    FeedItem*  FUN_006676f0();
    void       FUN_006678f0();
    void       FUN_00667ac0();
    void       FUN_00667ae0();
    void       FUN_00667b00();
};
struct MsgBuffer { uint32_t a, b, c, d; void* e; uint8_t f, g; };
// ---- items of slice s00666cb0 end

// ---- items of slice s00668be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gFmt13f5c04[];   // 0x013f5c04
extern int gVt14002a8;          // 0x014002a8
int __cdecl WStr_Format(wchar_t* dst, const wchar_t* fmt, ...);   // 0x0041e050
void* __cdecl FUN_007eb100(void* a);                              // 0x007eb100
void* __cdecl EA_GetManager();                                    // 0x0067dcd0
void* __cdecl DoInsertValue0066(void* dst, void* src, int nbytes); // 0x011e0744
void  __cdecl FUN_00642c70(void* self, int n);                    // 0x00642c70
void  __cdecl FUN_006431b0(void* self, void* item, void* end);    // 0x006431b0
struct Vec { void* begin; void* end; void* cap; };
struct AssetListSource { void GetAssetList(Vec* out); };  // 0x00668d90
void __fastcall FUN_00669410(void* self);  // 0x00669410 (defined below; used by a stub's inline body)
struct FeedItem_s0066_8be0 {
    bool FUN_00668be0(wchar_t* dst);
    void FUN_00668c80(void* a1, void* c);
    void FUN_00668d90(Vec* out);
    int  FUN_006693c0();
    void FUN_00669410();
};
struct Item { int a; int b; int c; void* d; };
struct Vec4 { void* begin; void* end; void* cap; };
struct Obj9360 {
    void* vt;        // +0x00
    Vec4  v;         // +0x04
    char  pad10[8];  // +0x10
    void* m18;       // +0x18
    Obj9360* init(int p2, Vec* p3);
    void reserve(int count, void* p);   // 0x004aa350
};
// ---- items of slice s00668be0 end

// ---- items of slice s00669430 begin (TODO(rewrite): local stubs, replace by canonical classes)
bool  __cdecl FUN_00664550(int v);
struct IWin {
    virtual void AddRef();                          // +0x00
    virtual void Release();                         // +0x04
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v0a(); virtual void v0b(); virtual void v0c(); virtual void v0d();
    virtual const float* GetArea();                 // +0x38
    virtual void v0f(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17();
    virtual void SetArea(const float* rect);        // +0x60
    virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void SetSize(float a, float b);         // +0x70
    virtual void v1d(); virtual void v1e();
    virtual void SetFlag(int flag, int on);         // +0x7c
    virtual void SetCaption(const void* text);      // +0x80
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v2a(); virtual void v2b(); virtual void v2c();
    virtual void v2d(); virtual void v2e(); virtual void v2f(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v3a(); virtual void v3b(); virtual void v3c();
    virtual void v3d(); virtual void v3e(); virtual void v3f(); virtual void v40();
    virtual void AddWinProc(void* proc);            // +0x104
    virtual void RemoveWinProc(void* proc);         // +0x108
};
struct RefObj {                                      // vtable-refcounted helper at +0x184
    virtual void v0();
    virtual void AddRef();                          // +0x04
    virtual void Release();                         // +0x08
    void Cancel();                                  // 0x00829d30
};
struct cSPUILayout_s0066_9430 {
    IWin* FindWindowByID(unsigned id, int flag);    // 0x008105b0
};
struct cSPColorRGBA_s0066_9430 {
    float r, g, b, a;
    cSPColorRGBA_s0066_9430() {}
    cSPColorRGBA_s0066_9430(const cSPColorRGBA_s0066_9430& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
};
struct cAssetBrowser { char pad[0x18]; void* mpProps; };
cAssetBrowser* __cdecl AssetBrowser_s0066_9430();               // 0x00401030
cSPColorRGBA_s0066_9430* __cdecl GetColorProperty(cSPColorRGBA_s0066_9430* out, void* props, unsigned id, cSPColorRGBA_s0066_9430 def);  // 0x00666b20
void __cdecl GetFloatProperty(void* props, unsigned id, float* out);                                    // 0x0040cf10
void __cdecl SetWindowAlpha(IWin* w, float a);                                                          // 0x00804fc0
void __cdecl SetWindowImage(IWin* w, const void* key, int index);                                       // 0x00807bb0
extern const cSPColorRGBA_s0066_9430 kColorDefaultA;            // 0x01527678
extern const cSPColorRGBA_s0066_9430 kColorDefaultB;            // 0x015275e8
struct cString {
    char pad[0x14];
    cString();                                                      // 0x006b5060
    ~cString();                                                     // 0x006b5240
    void Load(uint32_t tableId, uint32_t stringId, const wchar_t* def);   // 0x006b54b0
    const wchar_t* GetText();                                       // 0x006b55c0
};
struct NumberHolder { char pad[0x38]; int mCount; };
extern NumberHolder* gNumberHolder;                  // 0x015ee298
inline void* operator new(unsigned, void* p) { return p; }
struct AutoWin {                                     // EA::AutoRefCount<IWindow>
    IWin* mp;
    AutoWin() : mp(0) {}
    AutoWin(const AutoWin& x) : mp(x.mp) { if (mp) mp->AddRef(); }
};
struct WinVec {                                      // eastl::vector<AutoRefCount<IWindow>>
    AutoWin* mpBegin;
    AutoWin* mpEnd;
    AutoWin* mpCapacity;
    ~WinVec();                                                      // 0x004b5440
    void DoInsertValue(AutoWin* pos, const AutoWin& value);        // 0x004b6000
    void push_back(const AutoWin& value) {
        if (mpEnd < mpCapacity) {
            AutoWin* p = mpEnd++;
            if (p) ::new(p) AutoWin(value);
        } else
            DoInsertValue(mpEnd, value);
    }
};
struct FeedHelper {                                  // object created at +0x184
    FeedHelper* Init();                                             // 0x00829770 (ctor)
    void Rebuild(IWin* win, WinVec* wins, uint32_t arg, void* item);    // 0x00829bc0
};
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
struct FeedItem_s0066_9430 {
    char    pad00[8];
    char    mSub08[0x10];               // +0x08 (address passed on)
    const wchar_t* mpFeedName;          // +0x18
    char    pad1c[0xc];
    const wchar_t* mpFeedAuthor;        // +0x28
    char    pad2c[0x34];
    int     mCount60;                   // +0x60
    int     mCount64;                   // +0x64
    float   mArea[4];                   // +0x68 (x0, y0, x1, y1)
    uint32_t mIconKey[3];               // +0x78
    char    pad84[2];
    uint8_t mChanged;                   // +0x86
    char    pad87[0xd];
    cSPUILayout_s0066_9430* mLayout;               // +0x94
    char    pad98[4];
    uint32_t mField9C;                  // +0x9c
    IWin*   mWinRoot;                   // +0xa0
    IWin*   mWinA4;                     // +0xa4
    IWin*   mWinA8;                     // +0xa8
    IWin*   mWinAC;                     // +0xac
    IWin*   mWinB0;                     // +0xb0
    IWin*   mWinB4;                     // +0xb4
    IWin*   mWinB8;                     // +0xb8
    IWin*   mWinBC;                     // +0xbc
    char    padc0[8];
    float   mHeightC8;                  // +0xc8
    float   mHeightCC;                  // +0xcc
    char    padd0[4];
    cSPColorRGBA_s0066_9430 mColorD4;              // +0xd4
    cSPColorRGBA_s0066_9430 mColorE4;              // +0xe4
    cSPColorRGBA_s0066_9430 mColorF4;              // +0xf4
    cSPColorRGBA_s0066_9430 mColor104;             // +0x104
    char    pad114[0x1c];
    int     mCount;                     // +0x130
    char    pad134[8];
    int     mType;                      // +0x13c
    char    pad140[0x44];
    RefObj* mpHelper;                   // +0x184
    int     CountItems();                                           // 0x006693c0
};
__forceinline void AssignWin(IWin** field, IWin* nw)
{
    IWin* old = *field;
    if (nw != old) {
        if (nw) nw->AddRef();
        *field = nw;
        if (old) old->Release();
    }
}
// ---- items of slice s00669430 end

// ---- items of slice s00669f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t g_EmptyW[2];                 // 0x01667bac (eastl shared empty string)
extern unsigned g_1527824;                  // 0x01527824
extern unsigned g_140041c;                  // 0x0140041c
extern unsigned g_Keys24[24];               // 0x01400480
extern unsigned g_MsgIds[2];                // 0x014003a0
void __cdecl operator_delete_array(void* p);  // 0x00f47380
void* __cdecl operator_new_tag(unsigned size, const char* tag, int a, int b, int c, int d);  // 0x00f473a0
struct FStr {                               // eastl::basic_string<wchar_t> (16 bytes)
  wchar_t* mb;
  wchar_t* me;
  wchar_t* mc;
  int mAlloc;
  FStr() { mb = g_EmptyW; me = g_EmptyW; mc = g_EmptyW + 1; }
  FStr(const FStr& o);                      // 0x0056e2d0
  ~FStr() { Dealloc(); }
  void Append(const wchar_t* p);            // 0x005c3d90
  void AppendStr(const FStr* o);            // 0x00667c40
  int FindA(const wchar_t* p, int pos);     // 0x00630630
  int FindB(const wchar_t* p, int pos);     // 0x00608340
  FStr* Substr(FStr* out, int pos, int n);  // 0x00453d20 (ret 0xc)
  void MakeLower();                         // 0x005e8e80
  void Dealloc();                           // 0x00933960
};
struct CStr {                               // SP::cString (0x14 bytes)
  char d[0x14];
  CStr();                                   // 0x006b5060
  ~CStr();                                  // 0x006b5240
  wchar_t* GetText();                       // 0x006b55c0
};
struct Prop_s0066_9f50 {
  char pad[0x12];
  unsigned short type;
  bool* GetBool();                          // 0x0041e920
  unsigned* GetUInt();                      // 0x0041ea00
};
struct NarrowStr {
  void Assign(const void* o);               // 0x00579c60 basic_string<char>::operator=
};
struct Obj5467 {
  int F5467e0();                            // 0x005467e0
};
bool __cdecl GetPropertyAsText(void* pl, unsigned key, CStr* out);        // 0x006a1360
void __cdecl GetPropertyAsKeyInstance(void* pl, unsigned key, unsigned* out);  // 0x006a12a0
void __cdecl GetPropertyAsKey(void* pl, unsigned key, unsigned* out);     // 0x006a1250
void __cdecl GetPropertyAsUint32(void* pl, unsigned key, unsigned* out);  // 0x004af210
void __cdecl GetBoolProp(void* pl, unsigned key, bool* out);              // 0x00407190
void* PropertyManager();                    // 0x0067de30
void* ConfigManager();                      // 0x0067dd30
void* MessageServer();                      // 0x0067dcc0
void* AuthManager();                        // 0x00607a60
struct LayoutObj {
  LayoutObj* Ctor();                        // 0x00810000 (cConnectionDialog ctor)
  void Init(unsigned* key, int a, unsigned b);        // 0x008120d0
  void SetParentWin(int win, int a, unsigned b);      // 0x008121b0
  void SetReloadCallback(void* cb, void* self);       // 0x00810090
};
void __cdecl ReloadCallback(void* self, void* layout, int flag);   // 0x00669430
#define VTS(o, off) ((*(void***)(o))[(off) / 4])
struct FeedItemInit {
  char pad0[4];
  char sub4[0x10];
  bool b14;                 // +0x14
  char pad15;
  bool b16;                 // +0x16
  char pad17;
  FStr s18;                 // +0x18
  FStr s28;                 // +0x28
  unsigned u38, u3c;        // +0x38
  FStr s40;                 // +0x40
  NarrowStr s50;            // +0x50
  char pad54[0x60 - 0x54];
  int count60;              // +0x60
  char pad64[0x78 - 0x64];
  unsigned key78;           // +0x78
  char pad7c[0x90 - 0x7c];
  void* ref90;              // +0x90
  void* layout94;           // +0x94
  void* ref98;              // +0x98
  void* ref9c;              // +0x9c
  char pada0[0xc0 - 0xa0];
  bool bc0;                 // +0xc0
  char padc1[0x114 - 0xc1];
  void* ahServer;           // +0x114
  void* ahHandler;          // +0x118
  void* ahIds;              // +0x11c
  int ahCount;              // +0x120
  int ahPrio;               // +0x124
  unsigned u128, u12c;      // +0x128
  int i130;                 // +0x130
  int i134;                 // +0x134
  unsigned u138;            // +0x138
  int i13c;                 // +0x13c
  bool b140;                // +0x140
  bool b141;                // +0x141
  char pad142[2];
  unsigned u144, u148, u14c, u150, u154;   // +0x144
  bool flags158[24];        // +0x158
  unsigned u170;            // +0x170
  char pad174[4];
  unsigned typeKey;         // +0x178
  unsigned propId;          // +0x17c
  void* propList;           // +0x180
  char pad184[4];
  unsigned u188;            // +0x188
  void* GetAssetList(void* vec);            // 0x00668d90 (ret 4)
  bool Init(void* a1, void* a2, unsigned a3, void* a4, int a5);
};
struct AssetVec { char* b; char* e; char* c; };
// ---- items of slice s00669f50 end

// @ 0x00666420
bool CFeed::IsKnownID() const
{
  uint32_t v = (uint32_t)m178;
  return v == 0x11f44f6b || v == 0xe8104769 || v == 0x48a6f111;
}

// @ 0x00666450
bool CFeed::IsKnownState() const
{
  uint32_t v = (uint32_t)m13c;
  return v == 1 || v == 2 || v == 3 || v == 0xb;
}

// @ 0x00666490
void CFeed::SetDefault(int unused)
{
  (void)unused;
  m84 = true;
  m8c = 2.0f;
}

// @ 0x006664f0
void CFeed::Teardown()
{
  if (m184) {
    m184->SomeMethod();
    Obj184* p = m184;
    if (p) { m184 = 0; p->v2(); }
  }
  if (m94) {
    ((cSPUILayout_s0066_5d30*)m94)->Shutdown(1);
    cSPUILayout_s0066_5d30* p = (cSPUILayout_s0066_5d30*)m94;
    if (p) { m94 = 0; p->v2(); }
  }
  if (m114) {
    int p = (int)m114;
    m114 = 0;
    RemoveHandler(p, m118, m11c, m120, m124);
  }
}

// @ 0x00666590
void CFeed::SetIconKey(const float* v)
{
  if (m184 && (m184->b9 || m184->bA)) {
    m184->SetKey(v, 1);
    return;
  }
  m68 = v[0];
  m6c = v[1];
  m70 = v[2];
  m74 = v[3];
}

// @ 0x006665e0
float* CFeed::GetIconKey(float* out)
{
  if (m184 && (m184->b9 || m184->bA)) {
    m184->GetKey(out);
    return out;
  }
  out[0] = m68;
  out[1] = m6c;
  out[2] = m70;
  out[3] = m74;
  return out;
}

// @ 0x00666630
void CFeed::Reserve(int a, int b)
{
  void* v = m180;
  vec_reserve((int)v, 0x662081e, a, b);
}

// @ 0x00666680
bool CFeed::CheckFlag(bool b)
{
  if (b) {
    return m14 && m90 && ((Obj90*)m90)->Method(1);
  }
  return m14;
}

// @ 0x006666c0
void CItem::Refresh(unsigned short* s)
{
  if (!mBg) return;
  VObj* o = (VObj*)mBg;
  unsigned short* p = (unsigned short*)((FnV0)o->vt[15])(o);
  if (wcscmp((const wchar_t*)p, (const wchar_t*)s) == 0) return;
  ((FnV1p)o->vt[32])(o, s);
  ((FnV2b)o->vt[31])(o, 1, s[0] != 0);
  float* a = (float*)((FnV0)o->vt[14])(o);
  float r0x = a[0], r0y = a[1], r0z = a[2], r0w = a[3];
  if (mBg) {
    void* x = ((FnV0i)o->vt[3])(o, 0xf15f4bd);
    if (x) ((FnV1i)((VObj*)x)->vt[5])(x, 0);
  }
  float* b = (float*)((FnV0)o->vt[14])(o);
  float rect[4];
  rect[0] = (r0z - b[2]) + b[0];
  rect[1] = r0y;
  rect[2] = r0z;
  rect[3] = b[3];
  ((FnV1p)o->vt[27])(o, rect);
  if (mActualHeight != 0.0f) {
    float h = 2.0f;
    if (AssetBrowser() && AssetBrowser()->m18)
      GetFloatProp2(AssetBrowser()->m18, 0xe5b5d7a8, &h);
    float* c = (float*)((FnV0)o->vt[14])(o);
    float rect2[4];
    rect2[0] = c[0]; rect2[1] = c[1]; rect2[2] = c[2]; rect2[3] = c[3];
    rect2[2] = (s[0] == 0 ? rect[2] : rect[0]) - h;
    ((FnV1p)o->vt[27])(o, rect2);
  }
}

// @ 0x00666b20
float* GetVec4(float* out, Prop* p, int key, float a, float b, float c, float d)
{
  if (p) {
    Prop* q = p;
    bool ok = ((FnVb1i)p->vt[9])(p, key, (void**)&q);
    if (ok) {
      short type = *(short*)((char*)q + 0x12);
      float* src;
      if (type == 0x34 || type == 0x10) {
        if ((*(unsigned char*)((char*)q + 0x10) & 0x30) != 0)
          src = (float*)(*(void**)q);
        else
          src = (float*)q;
      } else {
        src = q->AsVec();
      }
      out[0] = src[0];
      out[1] = src[1];
      out[2] = src[2];
      out[3] = src[3];
      return out;
    }
  }
  out[0] = a;
  out[1] = b;
  out[2] = c;
  out[3] = d;
  return out;
}

// @ 0x006678f0
void FeedItem::FUN_006678f0()
{
    void* self = this;
    *(void**)self = &gVt6f0_0;
    *(void**)((char*)self + 4)  = &gVt6f0_1;
    *(void**)((char*)self + 8)  = &gVt6f0_2;
    *(void**)((char*)self + 0xc) = &gVt6f0_3;
    _ReadWriteBarrier();

    void* p;
    p = *(void**)((char*)self + 0x184);
    if (p) ((FnVoid)VT(p)[2])(p);
    p = *(void**)((char*)self + 0x180);
    if (p) ((FnVoid)VT(p)[1])(p);
    void* h = *(void**)((char*)self + 0x114);
    if (h) {
        void* a = *(void**)((char*)self + 0x118);
        void* b = *(void**)((char*)self + 0x11c);
        void* c = *(void**)((char*)self + 0x120);
        void* d = *(void**)((char*)self + 0x124);
        *(uint32_t*)((char*)self + 0x114) = 0;
        FUN_00571db0(h, a, b, c, d);
    }
    p = *(void**)((char*)self + 0xbc);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xb8);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xb4);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xb0);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xac);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xa8);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xa4);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0xa0);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0x9c);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0x98);
    if (p) ((FnVoid)VT(p)[1])(p);
    p = *(void**)((char*)self + 0x94);
    if (p) ((FnVoid)VT(p)[2])(p);
    p = *(void**)((char*)self + 0x90);
    if (p) ((FnVoid)VT(p)[3])(p);

    {
        uint8_t* a = *(uint8_t**)((char*)self + 0x50);
        uint8_t* c = *(uint8_t**)((char*)self + 0x58);
        if ((int)(c - a) > 1 && a) EASTL_allocator_deallocate(a);
    }
    {
        uint8_t* a = *(uint8_t**)((char*)self + 0x40);
        uint8_t* c = *(uint8_t**)((char*)self + 0x48);
        if ((int)((c - a) & 0xfffffffe) > 2 && a) EASTL_allocator_deallocate(a);
    }
    {
        uint8_t* a = *(uint8_t**)((char*)self + 0x28);
        uint8_t* c = *(uint8_t**)((char*)self + 0x30);
        if ((int)((c - a) & 0xfffffffe) > 2 && a) EASTL_allocator_deallocate(a);
    }
    {
        uint8_t* a = *(uint8_t**)((char*)self + 0x18);
        uint8_t* c = *(uint8_t**)((char*)self + 0x20);
        if ((int)((c - a) & 0xfffffffe) > 2 && a) EASTL_allocator_deallocate(a);
    }

    *(void**)((char*)self + 0xc) = &gVT_base2;
    *(void**)((char*)self + 4)  = &gVT_base1;
    *(void**)self = &gVT_base0;
}

// @ 0x00667ac0
void FeedItem::FUN_00667ac0()
{
    FUN_00666cb0();
    void* p = *(void**)((char*)this + 0x184);
    if (p) ((P184Obj*)p)->FUN_00829160(1);
}

// @ 0x00667ae0
void FeedItem::FUN_00667ae0()
{
    FUN_00666cb0();
    void* p = *(void**)((char*)this + 0x184);
    if (p) ((P184Obj*)p)->FUN_00829160(0);
}

// @ 0x00667b00
void SP::cSPUIFeedListItem::OnLeftMouseDown()
{
    void* self = this;
    void* at = EA_Audio_GetSystemAT();
    void* r = at ? ((FnPtrV)VT(at)[8])(at) : 0;

    void* at2 = EA_Audio_GetSystemAT();
    if (at2) {
        ((FnVoidI)VT(at2)[14])(at2, 0x03475365);
        ((FnVoidII)VT(at2)[16])(at2, 0x03475381, 0x0f05a8af);
        ((FnVoidII)VT(at2)[16])(at2, 0x03475385, (int)r);
        ((FnVoid)VT(at2)[22])(at2);
    }

    void* ms = SP_MessageServer();
    MsgBuffer buf;
    buf.a = 0x0140029c;
    buf.b = 0x01400298;
    buf.c = 0;
    buf.d = 0;
    buf.e = self;
    if (self) ((FnVoid)VT(self)[0])(self);
    buf.f = 0;
    buf.g = 0;
    ((FnVoidIP)VT(ms)[5])(ms, 0xb3d53f95, &buf);

    *(uint8_t*)((char*)self + 0x142) = 0;
    void* p = *(void**)((char*)self + 0x14c);
    if (p) {
        MsgBuffer buf2;
        buf2.a = 0x013eb90c;
        buf2.b = 0x013eb844;
        buf2.d = 0;
        buf2.e = 0;
        (void)buf2;
    }

    void* q = *(void**)((char*)self + 0x184);
    if (q) ((P184Obj*)q)->FUN_00829160(1);
}

// @ 0x00667c40
void __stdcall FUN_00667c40(void** p)
{
    void* b = p[1];
    void* a = p[0];
    WString_Assign(a, b);
}

// @ 0x00668be0
bool FeedItem_s0066_8be0::FUN_00668be0(wchar_t* dst)
{
    const wchar_t* name = *(wchar_t**)((char*)this + 0x18);
    if (name) {
        const wchar_t* author = *(wchar_t**)((char*)this + 0x28);
        if (author) {
            switch (*(int*)((char*)this + 0x13c)) {
            case 1:
                WStr_Format(dst, L"Sporecast \"%s\" by %s", name, author);
                return true;
            case 2:
                WStr_Format(dst, L"Creations by %s", author);
                return true;
            case 3:
                WStr_Format(dst, L"Content tagged \"%s\"", name);
                return true;
            default:
                WStr_Format(dst, gFmt13f5c04, name);
                return true;
            }
        }
    }
    return false;
}

// @ 0x00668c80
void FeedItem_s0066_8be0::FUN_00668c80(void* a1, void* c)
{
    (void)a1;
    void* list = FUN_007eb100(c);
    if (!list) return;
    int count = 0;
    void** node = (void**)*(void**)list;
    void** head = (void**)list;
    while (node != head) { ++count; node = (void**)*node; }
    FUN_00642c70(this, count);

    int idx = 1;
    node = (void**)*head;
    while (node != head) {
        void* e = node[5];
        int loc1c = *(int*)((char*)e + 8);
        int loc14 = *(int*)((char*)e + 0xc);
        int loc18 = *(int*)((char*)e + 4);
        void** puVar7 = node + 2;
        int next = idx;
        if (loc1c == 0) {
        use:
            {
                int m28 = *(int*)((char*)(node[5]) + 0x28);
                Item tmp;
                tmp.a = idx;
                tmp.b = m28;
                tmp.c = 0;
                tmp.d = puVar7;
                void* end = *(void**)((char*)this + 4);
                next = idx + 1;
                if (end < *(void**)((char*)this + 8)) {
                    *(void**)((char*)this + 4) = (char*)end + 0x10;
                    if (end) {
                        *(int*)((char*)end + 0) = idx;
                        *(int*)((char*)end + 4) = m28;
                        *(int*)((char*)end + 8) = 0;
                        *(void**)((char*)end + 0xc) = puVar7;
                    }
                } else {
                    FUN_006431b0(this, &tmp, end);
                }
            }
        } else {
            void* mgr = EA_GetManager();
            char ok = ((char(__thiscall*)(void*, void*, int, int, int, int, int))VT(mgr)[3])
                          (mgr, &loc1c, 0, 0, 0, 0, 0);
            next = idx;
            if (ok) goto use;
        }
        idx = next;
        node = (void**)*node;
    }
}

// @ 0x00668d90
__declspec(noinline) void FeedItem_s0066_8be0::FUN_00668d90(Vec* out)
{
    out->begin = 0;
    out->end = 0;
    out->cap = 0;
    // Skeleton: the real body walks the managed-asset database, filters by the
    // item's feed type/id and pushes 16-byte entries into the output vector.
    (void)this;
}

// @ 0x00669360
Obj9360* Obj9360::init(int p2, Vec* p3)
{
    vt = &gVt14002a8;
    int count = (int)((char*)p3->end - (char*)p3->begin) >> 2;
    reserve(count, (char*)p3 + 0xc);
    int nbytes = (int)((char*)p3->end - (char*)p3->begin);
    void* r = DoInsertValue0066(v.begin, p3->begin, nbytes);
    v.end = (char*)r + (nbytes >> 2) * 4;
    m18 = (void*)p2;
    return this;
}

// @ 0x006693c0
__declspec(noinline) int FeedItem_s0066_8be0::FUN_006693c0()
{
    Vec v;
    v.begin = 0;
    v.end = 0;
    v.cap = 0;
    ((AssetListSource*)this)->GetAssetList(&v);
    int n = (int)((char*)v.end - (char*)v.begin);
    if (v.begin && *(int*)((char*)v.begin - 4) != 0)
        EASTL_allocator_deallocate(v.begin);
    return n >> 4;
}

// @ 0x00669410
void __fastcall FUN_00669410(void* self)
{
    int n = ((FeedItem_s0066_8be0*)self)->FUN_006693c0();
    *(int*)((char*)self + 0x60) = n;
    if (n != *(int*)((char*)self + 0x64))
        *(uint8_t*)((char*)self + 0x86) = 1;
}

// @ 0x00669430
void __cdecl ReloadCallback(FeedItem_s0066_9430* self, int a2, bool reload)
{
    (void)a2;
    if (!reload) {
        if (self->mWinRoot) self->mWinRoot->RemoveWinProc(self);
        if (self->mpHelper) {
            self->mpHelper->Cancel();
            RefObj* p = self->mpHelper;
            if (p) {
                self->mpHelper = 0;
                p->Release();
            }
        }
        return;
    }

    AssignWin(&self->mWinRoot, self->mLayout->FindWindowByID(0xf3c6dc19, 1));

    if (AssetBrowser_s0066_9430() && AssetBrowser_s0066_9430()->mpProps) {
        cSPColorRGBA_s0066_9430 buf;
        unsigned id2;
        if (self->mType == 0xb) {
            self->mColorD4 = *GetColorProperty(&buf, AssetBrowser_s0066_9430()->mpProps, 0x139ac029, kColorDefaultA);
            id2 = 0xe025f710;
        } else {
            self->mColorD4 = *GetColorProperty(&buf, AssetBrowser_s0066_9430()->mpProps, 0x6b9f30ed, kColorDefaultA);
            id2 = 0x2695d23c;
        }
        self->mColorF4 = *GetColorProperty(&buf, AssetBrowser_s0066_9430()->mpProps, id2, kColorDefaultB);
        self->mColorE4 = self->mColorD4;
        self->mColor104 = self->mColorF4;
    }

    AssignWin(&self->mWinAC, self->mLayout->FindWindowByID(0xf435d021, 1));
    AssignWin(&self->mWinB0, self->mLayout->FindWindowByID(0xd4232d3b, 1));
    if (self->mWinB0)
        SetWindowAlpha(self->mWinB0, 0.0f);

    AssignWin(&self->mWinA4, self->mLayout->FindWindowByID(0xb3c6efca, 1));
    if (self->mWinA4)
        self->mWinA4->SetCaption(self->mpFeedName);

    AssignWin(&self->mWinB4, self->mLayout->FindWindowByID(0x548f3bf6, 1));
    if (self->mWinB4 && self->mIconKey[0]) {
        SetWindowImage(self->mWinB4, self->mIconKey, 0);
        self->mWinB4->SetFlag(1, 1);
    }

    if (self->mWinA4 && self->mWinB4) {
        float h = self->mWinA4->GetArea()[1];
        float w = self->mWinB4->GetArea()[2];
        float pad;
        float x;
        if (self->mIconKey[0]) {
            pad = 2.0f;
            if (AssetBrowser_s0066_9430() && AssetBrowser_s0066_9430()->mpProps)
                GetFloatProperty(AssetBrowser_s0066_9430()->mpProps, 0x02beb75e, &pad);
            x = w + pad;
        } else {
            pad = 6.0f;
            if (AssetBrowser_s0066_9430() && AssetBrowser_s0066_9430()->mpProps)
                GetFloatProperty(AssetBrowser_s0066_9430()->mpProps, 0xa05a01c6, &pad);
            x = pad;
        }
        self->mWinA4->SetSize(x, h);
    }

    if (self->mType == 0xb) {
        AssignWin(&self->mWinBC, self->mLayout->FindWindowByID(0x07d5f060, 1));
    } else {
        AssignWin(&self->mWinBC, self->mLayout->FindWindowByID(0x14c87a13, 1));
        if (self->mWinBC)
            self->mWinBC->SetCaption(self->mpFeedAuthor);
    }

    AssignWin(&self->mWinB8, self->mLayout->FindWindowByID(0x14c87a12, 1));
    if (self->mWinB8) {
        gNumberHolder->mCount = self->mCount;
        cString s;
        s.Load(0x21671745, 0xf4c87cf6 + (self->mCount != 1), L"*Num Subscribers*");
        self->mWinB8->SetCaption(s.GetText());
    }

    AssignWin(&self->mWinA8, self->mLayout->FindWindowByID(0xb48e225b, 1));
    if (self->mWinA8)
        self->mWinA8->SetFlag(1, 0);

    if (self->mWinRoot) {
        const float* r = self->mWinRoot->GetArea();
        float a[4] = { r[0], r[1], r[2], r[3] };
        float rect[4] = { 0.0f, 0.0f, a[2] - a[0], a[3] - a[1] };
        self->mWinRoot->SetArea(rect);
        self->mArea[0] = rect[0];
        self->mArea[1] = rect[1];
        self->mArea[2] = rect[2];
        self->mArea[3] = rect[3];
        float h = rect[3] - rect[1];
        self->mHeightC8 = h;
        self->mHeightCC = h;
    }
    if (self->mWinRoot)
        self->mWinRoot->AddWinProc(self);

    WinVec wins = { 0, 0, 0 };
    wins.push_back(*(AutoWin*)&self->mWinA4);
    wins.push_back(*(AutoWin*)&self->mWinB8);
    wins.push_back(*(AutoWin*)&self->mWinBC);

    FeedHelper* helper = 0;
    {
        void* mem = ::operator new(0x34, "UI", 0, 0, 0, 0);
        if (mem)
            helper = ((FeedHelper*)mem)->Init();
    }
    RefObj* nh = (RefObj*)helper;
    RefObj* old = self->mpHelper;
    if (nh != old) {
        if (nh) nh->AddRef();
        self->mpHelper = nh;
        if (old) old->Release();
    }
    ((FeedHelper*)self->mpHelper)->Rebuild(self->mWinRoot, &wins, self->mField9C, self->mSub08);

    self->mCount60 = self->CountItems();
    if (self->mCount60 != self->mCount64)
        self->mChanged = 1;
}

// @ 0x00669c90
bool __fastcall FUN_00669c90(void* self, int a1, unsigned* a2)
{
    void* item = (char*)self - 4;
    if (!*(uint8_t*)((char*)self + 0x10)) return false;
    if (!*(void**)((char*)item + 0x90)) return false;
    if (!FUN_00664550(1)) return false;
    if (*(int*)((char*)self + 0x174) != 0x11f44f6b) return false;
    if (a1 != 0x064e5bda && a1 != (int)0x9421c619) return false;
    (void)a2;
    // Skeleton: the real body dispatches on the feed-type/query hashes, builds
    // SP::FunctionalMatch::Constraint objects and probes SP::ObjectTemplateDB.
    return false;
}

// @ 0x00669f50
bool FeedItemInit::Init(void* a1, void* a2, unsigned a3, void* a4, int a5)
{
  (void)a5;
  Prop_s0066_9f50* prop;
  {   // AutoRefCount assignments
    void* old = ref98;
    if (a1 != old) {
      if (a1) ((void(__thiscall*)(void*))VTS(a1, 0))(a1);
      ref98 = a1;
      if (old) ((void(__thiscall*)(void*))VTS(old, 4))(old);
    }
  }
  {
    void* old = ref9c;
    if (a2 != old) {
      if (a2) ((void(__thiscall*)(void*))VTS(a2, 0))(a2);
      ref9c = a2;
      if (old) ((void(__thiscall*)(void*))VTS(old, 4))(old);
    }
  }
  propId = a3;
  {
    void* old = ref90;
    if (a4 != old) {
      if (a4) ((void(__thiscall*)(void*))VTS(a4, 8))(a4);
      ref90 = a4;
      if (old) ((void(__thiscall*)(void*))VTS(old, 0xc))(old);
    }
  }
  b14 = true;
  void* pm = PropertyManager();
  if (propList != 0) {
    void* old = propList;
    propList = 0;
    ((void(__thiscall*)(void*))VTS(old, 4))(old);
  }
  ((void(__thiscall*)(void*, unsigned, unsigned, void**))VTS(pm, 0x2c))(pm, propId, 0x4e5892eb, &propList);
  if (propList != 0) {
    void* cm = ConfigManager();
    int cfg = ((int(__thiscall*)(void*, unsigned))VTS(cm, 0x30))(cm, 0x5de7b4a);
    if (cfg == 1 && propList != 0 &&
        ((bool(__thiscall*)(void*, unsigned, Prop_s0066_9f50**))VTS(propList, 0x24))(propList, 0x6397993, &prop) &&
        prop->type == 1 && *prop->GetBool() == false)
      return false;
    if (propList != 0 &&
        ((bool(__thiscall*)(void*, unsigned, Prop_s0066_9f50**))VTS(propList, 0x24))(propList, 0x6678df3, &prop) &&
        prop->type == 10)
      u188 = *prop->GetUInt();
    GetPropertyAsKeyInstance(propList, 0x744717c3, &typeKey);
    if (typeKey != 0xffffffff) {
      CStr text1;
      if (GetPropertyAsText(propList, 0x744717c5, &text1))
        s18.Append(text1.GetText());
      CStr text2;
      if (GetPropertyAsText(propList, 0x5af1baf, &text2))
        s40.Append(text2.GetText());
      GetBoolProp(propList, 0x74b839b7, &b16);
      GetBoolProp(propList, 0x744717c8, &bc0);
      GetPropertyAsKey(propList, 0xf4906970, &key78);
      GetBoolProp(propList, 0xb5135387, &b141);
      GetPropertyAsKeyInstance(propList, 0x5e90865, &u150);
      GetPropertyAsKeyInstance(propList, 0x5e9086c, &u154);
      unsigned k = typeKey;
      if (k == 0x11f44f6b || k == 0xe8104769 || k == 0x48a6f111) {
        int i = 0;
        do {
          if (propList != 0 &&
              ((bool(__thiscall*)(void*, unsigned, Prop_s0066_9f50**))VTS(propList, 0x24))(propList, g_Keys24[i], &prop) &&
              prop->type == 1)
            flags158[i] = *prop->GetBool();
          i++;
        } while (i < 0x18);
        GetPropertyAsKeyInstance(propList, g_140041c, &u170);
      }
      switch (typeKey) {
      case 0xe8104769:
        GetPropertyAsKeyInstance(propList, 0x56b8d5e, &u144);
        break;
      case 0xaabe8769:
        GetPropertyAsKeyInstance(propList, 0x144d7575, &u14c);
        break;
      case 0x984b7145:
        GetPropertyAsKeyInstance(propList, 0x58b92cd, &u12c);
        break;
      case 0x11f44f6b: {
        GetPropertyAsKeyInstance(propList, 0x744717c6, &u138);
        int* b = (int*)a2;
        if (b != 0) {
          int v = b[0x10];
          i130 = v & ((v < 0) - 1);
          s28.Append((const wchar_t*)b[0]);
          u38 = b[4];
          u3c = b[5];
          i13c = b[0x1a];
          i134 = ((Obj5467*)b)->F5467e0();
          s50.Assign(b + 0x15);
          void* am = AuthManager();
          long long id = ((long long(__thiscall*)(void*))VTS(am, 0x40))(am);
          unsigned lo = (unsigned)id, hi = (unsigned)(id >> 32);
          if ((unsigned)b[4] == lo && (unsigned)b[5] == hi)
            b140 = 1;
          else
            b140 = 0;
          int kind = b[0x1a];
          if (kind == 2) {
            s18.Append((const wchar_t*)b[0]);
            {
              FStr tmp(s18);
              tmp.MakeLower();
              if (tmp.FindB(L"maxis", 0) != -1)
                key78 = 0xf29655f5;
            }
          } else if (kind == 3) {
            FStr tmp;
            tmp.Append((const wchar_t*)b[6]);
            if (tmp.FindA(L"Assets tagged", 0) != -1) {
              FStr sub;
              s18.AppendStr(tmp.Substr(&sub, 0xf, (int)(tmp.me - tmp.mb) - 0x10));
            }
          } else {
            s18.Append((const wchar_t*)b[6]);
          }
        }
        break;
      }
      case 0x793a246b:
        GetPropertyAsKeyInstance(propList, 0x744717c4, &u128);
        break;
      case 0x48a6f111:
        GetPropertyAsUint32(propList, 0x71d9ed4, &u148);
        break;
      default:
        break;
      }
    }
  }
  AssetVec av;
  av.b = 0; av.e = 0; av.c = 0;
  GetAssetList(&av);
  int cnt = (int)(av.e - av.b) >> 4;
  if (av.b != 0 && *(int*)(av.b - 4) != 0)
    operator_delete_array(av.b);
  count60 = cnt;
  LayoutObj* lay;
  void* mem = operator_new_tag(0x18, "Sporepedia", 0, 0, 0, 0);
  if (mem != 0)
    lay = ((LayoutObj*)mem)->Ctor();
  else
    lay = 0;
  {
    void* old = layout94;
    if ((void*)lay != old) {
      if (lay) ((void(__thiscall*)(void*))VTS(lay, 4))(lay);
      layout94 = lay;
      if (old) ((void(__thiscall*)(void*))VTS(old, 8))(old);
    }
  }
  struct Key3 { unsigned a, b, c; } key3;
  key3.c = g_1527824;
  key3.a = 0xc1966e00;
  key3.b = 0x510a95b;
  ((LayoutObj*)layout94)->Init((unsigned*)&key3, 1, 0x5b598fa);
  ((LayoutObj*)layout94)->SetParentWin((int)ref98, 1, 0x5b598fa);
  ((LayoutObj*)layout94)->SetReloadCallback((void*)(void (__cdecl*)(FeedItem_s0066_9430*, int, bool))ReloadCallback, this);
  ReloadCallback(this, layout94, 1);
  void* handler = sub4;
  void* srv = MessageServer();
  ahServer = srv;
  ahHandler = handler;
  ahIds = g_MsgIds;
  ahCount = 2;
  ahPrio = 0;
  if (srv != 0 && handler != 0) {
    for (unsigned u = 0; u < 8; u += 4)
      ((void(__thiscall*)(void*, void*, unsigned))VTS(srv, 0x24))(srv, handler, *(unsigned*)((char*)g_MsgIds + u));
  }
  return true;
}
