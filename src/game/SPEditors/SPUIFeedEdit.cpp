// src/game/SPEditors/SPUIFeedEdit.cpp -- migrated from slice(s) s00ed6720, s00ed57e0, s00ed4730, s00ed37c0, s00ed2600, s00ed1880, s00ed74f0, s0065ea00, s0065df30, s0065d050, s0065bf20 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIFeedEdit.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUIFeedEditAssetView.h"
#include "SP/cSPUIFeedEdit.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern int g_15fa6e4;
extern void* g_vt_13fff3c;
extern void* g_vt_13fff2c;
extern void* g_vt_13ec458;

// Same entry point as FUN_0065c9a0, declared with the raw integer result so the
// caller returns eax unchanged instead of zero-extending a bool.  __fastcall puts
// self in ecx (the callee's `this`) and the window on the stack, matching __thiscall;
// edx is an unused dummy.
int __fastcall FUN_0065c9a0_int(void* self, void* dummy, void* win); // 0x0065c9a0
#include <intrin.h>
#include <string.h>
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"
#include "SP/cStringTokenTranslator.h"
#include "SP/cString.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "EA/Messaging/IHandlerRC.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteUI.h"
#include <math.h>

// ---- items of slice s0065bf20 begin (TODO(rewrite): local stubs, replace by canonical classes)
    void GetElapsedSeconds(...); // 0x00805080
typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void*(__thiscall* FnRetP)(void*);
typedef void*(__thiscall* FnRetPi)(void*, unsigned int);
typedef int(__thiscall* FnRetI2)(void*, void*);
static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }
struct cSPUILayout_s0065_bf20 {
  void Shutdown(int a);  // 0x00811ad0 (cSPUILayout::Shutdown)
  void* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
};
struct cXHTMLFrameSet {
  void* GetFrame(uint32_t id);
  bool HandleLocationChange(void* win, const wchar_t* url, void* a, int b);   // 0x00997730
  bool HandleFormSubmit(void* win, void* form);                              // 0x009978b0
  void FUN_00997140();
};
float GetElapsedSeconds_f(); // 0x00805080 (SetMode uses the float ABI; older stubs keep their void* cast)
void SetWindowImage(void* w, uint32_t* key, int flags);
void* FUN_0067de40();                                  // 0x0067de40
void MessageServer_Unsub(void* h, uint32_t id, int y); // 0x0067dcc0 (equiv t2)
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
struct CtorObj {
  void** vt; void** vt4; int m08; char pad0c[4]; void* m10; void* m14; void* m18; int m1c;
  void FUN_0065c790(void* a, void* b, void* c);
};
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
struct IRef {
  virtual void AddRef();   // slot 0 (offset 0)
  virtual void Release();  // slot 1 (offset 4)
};
struct AssetInfo {
  void* a; void* b; void* c; void* d;
  AssetInfo& operator=(const AssetInfo& other);
};
struct FeedStr {                      // SP::cString, 0x14 bytes
  uint32_t raw[5];
  FeedStr(uint32_t table, uint32_t id, const wchar_t* dflt);   // 0x006b5770
  const wchar_t* GetText();                                    // 0x006b55c0
  ~FeedStr();                                                  // 0x006b5240
};
struct FeedWin {
virtual void fa0();
virtual void fa1();
virtual void fa2();
virtual void fa3();
virtual void fa4();
virtual void fa5();
virtual void fa6();
virtual void fa7();
virtual void fa8();
virtual void fa9();
virtual void fa10();
virtual void fa11();
virtual void fa12();
virtual void fa13();
virtual void fa14();
virtual void fa15();
virtual void fa16();
virtual void fa17();
virtual void fa18();
virtual void fa19();
virtual void fa20();
virtual void fa21();
virtual void fa22();
virtual void fa23();
virtual void fa24();
virtual void fa25();
virtual void fa26();
virtual void fa27();
virtual void fa28();
virtual void fa29();
virtual void fa30();
virtual void fa31();
  virtual void SetText(const wchar_t* s);                      // 0x80
virtual void fb0();
virtual void fb1();
virtual void fb2();
virtual void fb3();
virtual void fb4();
virtual void fb5();
virtual void fb6();
virtual void fb7();
virtual void fb8();
virtual void fb9();
virtual void fb10();
virtual void fb11();
virtual void fb12();
virtual void fb13();
virtual void fb14();
virtual void fb15();
virtual void fb16();
virtual void fb17();
virtual void fb18();
virtual void fb19();
virtual void fb20();
virtual void fb21();
virtual void fb22();
virtual void fb23();
virtual void fb24();
virtual void fb25();
virtual void fb26();
  virtual FeedWin* FindWin(uint32_t id, int recursive);        // 0xf0
};
// ---- items of slice s0065bf20 end

// ---- items of slice s0065d050 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* operator_new_ea(unsigned int size, const char* tag, int, int, int, int);
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t* s, wchar_t** end, int base);
extern uint32_t g_1526cb0;
extern wchar_t g_01667bac;
extern wchar_t g_01667bae;
extern void* g_0154df28;
extern "C" void FUN_00623f40();  // 0x00623f40 (LAB_00623f40 callback)
extern const wchar_t* g_0152694c;
unsigned long long __cdecl StrtoU6416(const wchar_t* s, wchar_t** end, int base);  // 0x0092d710
typedef void(__thiscall* FnPi)(void*, int);
struct ResourceKey { uint32_t a, b, c; };
struct cXHTMLFrameSet_s0065_d050 {
  void* GetFrame(uint32_t id);  // 0x00996d40 (cXHTMLFrameSet::GetFrame)
  void HandleLocationChange(void* win, const wchar_t* url, int a, int b);  // 0x00997730 (cXHTMLFrameSet::HandleLocationChange)
  void FUN_00997140();
};
void* MessageServer();
unsigned int __cdecl FNVHash16(const wchar_t* s, unsigned int seed, int n);
void GetURL(unsigned int id, void* out);  // 0x006214c0
void SetNumberString(int value, int a, wchar_t* buf, int n);
void* GetResourceProvider();  // 0x008fe480
void* CopyImpl(void* first, void* last, void* dest);
void DoFreeNodes(void* a, void* b);
struct cSPUIFeedEditAssetView_s0065_d050 {
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

  void ClearAsset();                       // 0065d050 0x0065d050
  bool Init(void* parent, unsigned int index);  // 0065d720 0x0065d720
  void Shutdown();                         // 0065d810 0x0065d810
  void SetMode(int mode);                  // 0065c840 (defined in slice s0065bf20) 0x0065c840
};
struct cSPUILayout_s0065_d050 {
  bool Init(ResourceKey* key, int a, uint32_t b);  // 0x008120d0 (cSPUILayout::Init)
  void SetParentWin(void* parent, int a, uint32_t b);  // 0x008121b0 (cSPUILayout::SetParentWin)
  void SetReloadCallback(void* fn, void* self);  // 0x00810090 (cSPUILayout::SetReloadCallback)
  void* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  void Shutdown(int a);  // 0x00811ad0 (cSPUILayout::Shutdown)
  void* Create();
};
void ReloadCallback(cSPUIFeedEditAssetView_s0065_d050* self, void* layout, bool b);
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
struct IWindow {
virtual void m00();
virtual void m01();
virtual void m02();
virtual void m03();
virtual void m04();
virtual void m05();
virtual void m06();
virtual void m07();
virtual void m08();
virtual void m09();
virtual void m10();
virtual void m11();
virtual void m12();
virtual void m13();
virtual void m14();
virtual void m15();
virtual void m16();
virtual void m17();
virtual void m18();
virtual void m19();
  virtual void m20(int);                        // 0x50
virtual void m21();
virtual void m22();
virtual void m23();
virtual void m24();
virtual void m25();
virtual void m26();
virtual void m27();
virtual void m28();
virtual void m29();
virtual void m30();
  virtual void m31(int, int);                   // 0x7c
virtual void m32();
virtual void m33();
virtual void m34();
virtual void m35();
  virtual void m36();                           // 0x90
virtual void m37();
virtual void m38();
virtual void m39();
virtual void m40();
  virtual void m41();
  virtual IWinLookup* GetLookup();              // 0xa8
virtual void m43();
virtual void m44();
virtual void m45();
virtual void m46();
virtual void m47();
virtual void m48();
virtual void m49();
virtual void m50();
virtual void m51();
virtual void m52();
virtual void m53();
virtual void m54();
virtual void m55();
virtual void m56();
virtual void m57();
virtual void m58();
virtual void m59();
virtual void m60();
virtual void m61();
virtual void m62();
virtual void m63();
virtual void m64();
  virtual void m65(void*);                      // 0x104
};
void __stdcall FUN_0065dd30(const wchar_t* s);  // 0x0065dd30 (defined below; used by a stub's inline body)
struct cSPUIFeedEdit_s0065_d050 {
  void* vt;  // +0x00
  char pad[0x50];

  void FUN_0065cc50();       // 0065cc50 (slice s0065bf20) page-button enable helper 0x0065cc50
  void UpdateStrings();      // 0065cb90 (slice s0065bf20) 0x0065cb90
  int GetAssetIndex(int a, int b);  // 0065ccd0 (slice s0065bf20) 0x0065ccd0
  void FUN_0065cf30(int a, int b, int c, int* asset);  // slice s0065bf20

  void UpdateGrid();         // 0065d260 0x0065d260
  void FUN_0065d490();       // 0065d490 0x0065d490
  bool SetPage(unsigned int page);  // 0065d4e0 0x0065d4e0
  bool ShowAsset(int a, int b);     // 0065d570 0x0065d570
  bool TranslateToken(const wchar_t* token, void* out);  // 0065dc60 0x0065dc60
  void SetActive(bool b);    // 0065d9f0 0x0065d9f0
  bool FUN_0065dd30(unsigned int id);  // 0065dd30 wrapper
};
struct HashtableU64 {
  char pad[0xc];
  int count;  // +0x0c
  int* erase(int* out, int* node, int* bucket);
};
struct WStr3 {  // eastl::basic_string<wchar_t> head: begin, end, capacity
  wchar_t* b;
  wchar_t* e;
  wchar_t* c;
  unsigned int mAlloc;
  void Append(const wchar_t* first, const wchar_t* last);  // 0x00429580
};
struct FEPolicy {  // eastl::prime_rehash_policy
  float mfMaxLoadFactor, mfGrowthFactor;
  unsigned int mnNextResize;
};
struct FEHashTab {  // eastl::hashtable<uint64> after the allocator word
  void* mpAlloc;
  void* mpBucketArray;
  unsigned int mnBucketCount;
  unsigned int mnElementCount;
  FEPolicy mRehashPolicy;
  unsigned int mpad;
  void DoFreeNodes(void* a, unsigned int n);  // 0x005687d0
  FEHashTab() {
    mRehashPolicy.mfMaxLoadFactor = 1.0f;
    mRehashPolicy.mfGrowthFactor = 2.0f;
    mnElementCount = 0;
    mRehashPolicy.mnNextResize = 0;
    mnBucketCount = 1;
    mpBucketArray = &g_0154df28;
  }
  ~FEHashTab() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
      EASTL_allocator_deallocate(mpBucketArray);
  }
};
struct FEI { virtual void a0(); virtual void Release(); };
struct FELay { virtual void a0(); virtual void a1(); virtual void Release(); };
struct FERef {
  FEI* p;
  FERef() : p(0) {}
  ~FERef() {
    if (p)
      p->Release();
  }
};
struct FELayRef {
  FELay* p;
  FELayRef() : p(0) {}
  ~FELayRef() {
    if (p)
      p->Release();
  }
};
struct FEVecA {
  void* b; void* e; void* c; void* n;
  FEVecA() : b(0), e(0), c(0) {}
  ~FEVecA();  // 0x0065cd30
};
struct FEVecB {
  void* b; void* e; void* c; void* n;
  FEVecB() : b(0), e(0), c(0) {}
  ~FEVecB();  // 0x00ae6970
};
struct FEStr {
  wchar_t* b; wchar_t* e; wchar_t* c; unsigned int pad;
  FEStr() {
    b = &g_01667bac;
    e = &g_01667bac;
    c = (wchar_t*)((char*)&g_01667bac + 1);
  }
  ~FEStr() {
    if (((char*)c - (char*)b) > 1 && b)
      EASTL_allocator_deallocate(b);
  }
};
struct FEFrameSet {
  unsigned int d[25];
  FEFrameSet(void* fn);  // 0x00996cc0
  ~FEFrameSet();         // 0x009968a0
};
struct FETok {                     // cStringTokenTranslator: vptr +0, refcount +4
  FETok();                         // 0x006b5870
  ~FETok();                        // 0x005725a0
  virtual void t0();
  int mRefCount;
};
struct FEWinProc { FEWinProc() {} ~FEWinProc() {} virtual void w0(); };          // +8 (IWinProc)
struct __declspec(novtable) FEModalCB { virtual void m0() = 0; };  // +0xc (no vptr store in base ctor)
struct FEHandler { FEHandler() {} ~FEHandler() {} virtual void h0(); };          // +0x10 (IHandlerRC)
struct FeedEditObj : FETok, FEWinProc, FEModalCB, FEHandler {
  FELayRef mpLayout;        // +0x14
  FEFrameSet mFrameSet;     // +0x18 .. 0x7b (cXHTMLFrameSet)
  FERef mpRef7c;
  FERef mpRef80;
  FERef mpRef84;
  FERef mpRef88;
  int m8c;
  bool mb90;
  bool mb91;
  float mf94;
  float mf98;
  unsigned int m9c, ma0, ma4, ma8;
  int mac;
  FEVecB mViewList;         // +0xb0
  unsigned int mc0;
  FEVecA mAssetList;        // +0xc4
  unsigned int md4;
  FEHashTab mExisting;      // +0xd8
  FEHashTab mNew;           // +0xf8
  FEHashTab mDelete;        // +0x118
  FEStr mStr;               // +0x138
  bool mb148, mb149, mb14a;
  FeedEditObj();   // 0x0065daa0
  ~FeedEditObj();  // 0x0065d860
  virtual void t0();
  virtual void w0();
  virtual void m0();
  virtual void h0();
};
struct ResProvider {
  void Request(void* out, const wchar_t* url, void* cb, void* obj, int a, int b);  // vslot 1 (+4)
};
struct __declspec(novtable) ReqI { virtual void q0(); virtual void AddRef(); };
struct ReqRC {
  virtual void r0();
  int mRefCount;
  ReqRC() : mRefCount(0) {}
};
struct ReqObj : ReqI, ReqRC {
  unsigned long long mId;  // +0x10
  unsigned long mNum;      // +0x18
  void* mpData;            // +0x1c
  ReqObj(unsigned long long id, unsigned long num) : mId(id), mNum(num), mpData(0) {}
  virtual void q0();
  virtual void AddRef();
  virtual void r0();
  static void* operator new(unsigned int n, const char* name, int a, int b, int c, int d) {
    return operator_new_ea(n, name, a, b, c, d);
  }
};
struct UFOCollisionEffectInfo { int a, b, c; int ref; };
struct VecUFO {
  char pad[4];
  UFOCollisionEffectInfo* mpEnd;
  UFOCollisionEffectInfo* erase(UFOCollisionEffectInfo* first, UFOCollisionEffectInfo* last);
};
// ---- items of slice s0065d050 end

// ---- items of slice s0065df30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  SPUIHelpers_SetWindowAreaToParent(void* win);
extern "C" char  FUN_009979f0(void* win, uint32_t id);
extern const wchar_t* g_kFrameName;  // 0x1526954
extern void* g_vt_13fff58;
extern void* g_vt_13fff48;
extern "C" void* HashFind64(uint64_t* out, uint64_t* key);      // 0x553510
extern "C" void  HashEraseR(uint64_t* a, uint64_t* key, int f);  // 0x553750
struct AssetInfo_s0065_df30 { uint64_t mnAssetID; uint32_t mnType; void* mpImage; };
struct AssetVec {
    AssetInfo_s0065_df30* begin;
    AssetInfo_s0065_df30* end;
    AssetInfo_s0065_df30* cap;
    AssetInfo_s0065_df30* DoInsertValue(AssetInfo_s0065_df30* pos, AssetInfo_s0065_df30* value);      // 0065df30
    AssetInfo_s0065_df30* erase(AssetInfo_s0065_df30* first, AssetInfo_s0065_df30* last);
    void push_back();                                                // 0065e6d0
};
extern "C" AssetInfo_s0065_df30* UninitCopy(AssetInfo_s0065_df30* first, AssetInfo_s0065_df30* last, AssetInfo_s0065_df30* dest); // 0x65cdc0
extern "C" AssetInfo_s0065_df30* UninitMove(AssetInfo_s0065_df30* first, AssetInfo_s0065_df30* last, AssetInfo_s0065_df30* dest); // 0x65ce10
extern "C" void  AssignRange(AssetInfo_s0065_df30* first, AssetInfo_s0065_df30* last, AssetInfo_s0065_df30* dest);     // 0x65c750
extern "C" void  DestroyRange(AssetInfo_s0065_df30* p);                                          // 0x65cd70
struct cSPUILayout_s0065_df30 { void* FindWindowByID(uint32_t id, int recursive); };
struct cXHTMLFrameSet_s0065_df30 {
    void* GetFrame(const wchar_t* name);  // 0x00996d40 (cXHTMLFrameSet::GetFrame)
    bool  FUN_009979f0(void* win, uint32_t id);
    void  FUN_00997140();
};
struct TextSlot { void Assign(void* p); };
struct IWindow_s0065_df30 {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
    virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31();
    virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
    virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
    virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43();
    virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
    virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51();
    virtual void m52(); virtual void m53(); virtual void m54(); virtual void m55();
    virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59();
    virtual void m60(); virtual void m61(); virtual void m62(); virtual void m63();
    virtual void m64();
    virtual void Slot104(void*);   // 0x104
};
struct VecPtr {
    void* begin; void* end; void* cap;
    void* erase(void* first, void* last);
};
struct HashSet {
    char pad[0xc];
    int  count;
    void DoFreeNodes(void* a, void* b);
};
struct cSPUIFeedEditAssetView_s0065_df30 {
    void* vt; void* vt4; void* vt8;      // 0x00
    void* mpLayout;                        // 0x0c
    void* mpParentWin;                     // 0x10
    void* mpRootWin;                       // 0x14
    void* mpButtonWin;                     // 0x18
    void* mpAssetWin;                      // 0x1c
    void* mpBackdropWin;                   // 0x20
    void* mpGlowWin;                       // 0x24
    void* mpEmptyWin;                      // 0x28
    void* mpImage;                         // 0x2c
    int   mnMode;                          // 0x30
    int   pad34;                           // 0x34
    uint64_t mnAssetID;                    // 0x38
    uint32_t mnIndex;                      // 0x40
    uint32_t mTickMask;                    // 0x44
    float mfBlinkStart;                    // 0x48
    void ClearAsset();                     // 0065d050 0x0065d050
};
struct cSPUIFeedEdit_s0065_df30 {
    void* vt;                          // 0x00
    char  pad04[0x10];                 // 0x04
    cSPUILayout_s0065_df30* mpLayout;             // 0x14
    char  mFrameSet[0x48];             // 0x18
    char  pad60[0x1c];                 // 0x60
    void* mpWin7c;                     // 0x7c
    void* mpWin80;                     // 0x80
    void* mpWin84;                     // 0x84
    void* mpWin88;                     // 0x88
    int   m8c;                         // 0x8c
    char  mbIsLoaded;                  // 0x90
    char  pad91[3];
    float mfAssetViewWidth;            // 0x94
    float mfAssetViewHeight;           // 0x98
    uint32_t mnAssetColCount;          // 0x9c
    uint32_t mnAssetRowCount;          // 0xa0
    uint32_t mnCurPage;                // 0xa4
    uint32_t mnNumPages;               // 0xa8
    int32_t  mnSelectedIndex;          // 0xac
    void* mViewBegin;                  // 0xb0
    void* mViewEnd;                    // 0xb4
    void* mViewCap;                    // 0xb8
    char  padbc[8];                    // 0xbc
    AssetVec mAssetList;               // 0xc4
    char  padcc[8];                    // 0xcc
    HashSet mNewAssets;                // 0xd8
    HashSet mDeleteAssets;             // 0xf8
    HashSet mExistingAssets;           // 0x118
    char  pad138[0x11];                // 0x138..0x148
    char  mbTransactionActive;         // 0x149
    char  mbNameSet;                   // 0x14a

    void UnloadLayout();               // 0065e0a0
    bool Populate();                   // 0065e110
    bool RemoveAsset(int a, int b);    // 0065e570
    void ResetPanel();                 // 0065e720
    void LoadLayout();                 // 0065e8d0 0x0065e8d0
    void UpdateStrings();              // 0065cb90 0x0065cb90
    void UpdateEnabledState();         // 0065cae0
    void UpdateGrid();                 // 0065d260 0x0065d260
    void UpdateButtons();              // 0065cc50
    bool SetPage(unsigned int page);  // 0x0065d4e0 (cSPUIFeedEdit::SetPage)
    int  GetAssetIndex(int a, int b);  // 0065ccd0 0x0065ccd0
};
// ---- items of slice s0065df30 end

// ---- items of slice s0065ea00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_MessageServer();
extern "C" void  FUN_00809db0(void* a, void* b);
extern "C" void  FUN_00996280(void* self, int a, int b, int c, int d);  // thiscall via struct
extern "C" void  FUN_0065d490();
extern "C" void  HashDoInsert(uint64_t* a, uint64_t* b, int c);  // 0x553750
struct AssetInfo_s0065_ea00 { uint64_t mnAssetID; uint32_t mnType; void* mpImage; };
struct AssetVec_s0065_ea00 {
    AssetInfo_s0065_ea00* begin; AssetInfo_s0065_ea00* end; AssetInfo_s0065_ea00* cap;
    AssetInfo_s0065_ea00* DoInsertValue(AssetInfo_s0065_ea00* pos, AssetInfo_s0065_ea00* value);   // 0x0065df30
    AssetInfo_s0065_ea00* erase(AssetInfo_s0065_ea00* first, AssetInfo_s0065_ea00* last);   // 0x0065ded0
    void push_back();  // 0x0065e6d0 (AssetVec::push_back)
};
struct TrueTag {};
struct HashSet_s0065_ea00 {
    char pad[0xc];
    int count;
    uint32_t tail[4];
    void DoFreeNodes(void*, void*);                              // 0x005687d0
    void Insert(void* outIt, uint64_t* key, TrueTag tag);        // 0x00553750
};
struct cSPUILayout_s0065_ea00 {
    void* FindWindowByID(uint32_t id, int recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void* Init(const void* key, int a, int id);  // 0x008120d0 (cSPUILayout::Init)
    void  SetParentWin(void* parent, int a, int id);  // 0x008121b0 (cSPUILayout::SetParentWin)
    void  SetReloadCallback(void* fn, void* self);  // 0x00810090 (cSPUILayout::SetReloadCallback)
};
struct LayoutCtor { void* Create(); };
struct ComObj {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
    virtual void Slot1c(void*);   // 0x1c
    virtual ComObj* Slot20();     // 0x20
};
struct cXHTMLFrameSet_s0065_ea00 {
    void  FUN_00996280(int a, int b, int c, int d);
    void  FUN_00997140();
};
struct cSPUIFeedEditAssetView_s0065_ea00;
struct cSPUIFeedEdit_s0065_ea00;
struct IWindow_s0065_ea00 {
virtual void m00();
virtual void m01();
virtual void m02();
virtual void m03();
virtual void m04();
virtual void m05();
virtual void m06();
virtual void m07();
virtual void m08();
virtual void m09();
virtual void m10();
virtual void m11();
virtual void m12();
virtual void m13();
virtual void m14();
virtual void m15();
virtual void m16();
virtual void m17();
virtual void m18();
virtual void m19();
virtual void m20();
virtual void m21();
virtual void m22();
virtual void m23();
virtual void m24();
virtual void m25();
virtual void m26();
virtual void m27();
virtual void m28();
virtual void m29();
virtual void m30();
    virtual void Slot7c(int, int);          // 0x7c (index 31)
virtual void m32();
virtual void m33();
virtual void m34();
virtual void m35();
    virtual void Slot90();                  // 0x90 (index 36)
virtual void m37();
virtual void m38();
virtual void m39();
virtual void m40();
virtual void m41();
virtual void m42();
virtual void m43();
virtual void m44();
virtual void m45();
virtual void m46();
virtual void m47();
virtual void m48();
virtual void m49();
virtual void m50();
virtual void m51();
virtual void m52();
virtual void m53();
virtual void m54();
virtual void m55();
virtual void m56();
virtual void m57();
virtual void m58();
virtual void m59();
    virtual void* SlotF0(uint32_t id, int b);  // 0xf0 (index 60)
virtual void m61();
virtual void m62();
virtual void m63();
virtual void m64();
    virtual void Slot104(void*);               // 0x104 (index 65)
};
struct cSPUIFeedEdit_s0065_ea00 {
    void* vt;                          // 0x00
    char  pad04[0x10];                 // 0x04
    cSPUILayout_s0065_ea00* mpLayout;             // 0x14
    char  mFrameSet[0x48];             // 0x18
    char  pad60[0x1c];                 // 0x60
    IWindow_s0065_ea00* mpWin7c;                  // 0x7c
    void* mpWin80;                     // 0x80
    void* mpWin84;                     // 0x84
    void* mpWin88;                     // 0x88
    int   m8c;                         // 0x8c
    char  mbIsLoaded;                  // 0x90
    char  mbInited;                    // 0x91
    char  pad92[2];
    float mfAssetViewWidth;            // 0x94
    float mfAssetViewHeight;           // 0x98
    uint32_t mnAssetColCount;          // 0x9c
    uint32_t mnAssetRowCount;          // 0xa0
    uint32_t mnCurPage;                // 0xa4
    uint32_t mnNumPages;               // 0xa8
    int32_t  mnSelectedIndex;          // 0xac
    void* mViewBegin;                  // 0xb0
    void* mViewEnd;                    // 0xb4
    void* mViewCap;                    // 0xb8
    char  padbc[8];                    // 0xbc
    AssetVec_s0065_ea00 mAssetList;               // 0xc4
    char  padcc[8];                    // 0xcc
    HashSet_s0065_ea00 mNewAssets;                // 0xd8
    HashSet_s0065_ea00 mDeleteAssets;             // 0xf8
    HashSet_s0065_ea00 mExistingAssets;           // 0x118
    char  pad138[0x11];                // 0x138..0x148
    char  mbTransactionActive;         // 0x149
    char  mbNameSet;                   // 0x14a

    void DoMessage(int msg, void* data);  // 0x0065ea00 (cSPUIFeedEdit::DoMessage)
    void UnloadLayout();  // 0x0065e0a0 (cSPUIFeedEdit::UnloadLayout)
    bool Populate();  // 0x0065e110 (cSPUIFeedEdit::Populate)
    bool RemoveAsset(int a, int b);  // 0x0065e570 (cSPUIFeedEdit::RemoveAsset)
    void ResetPanel();  // 0x0065e720 (cSPUIFeedEdit::ResetPanel)
    void LoadLayout();  // 0x0065e8d0 (cSPUIFeedEdit::LoadLayout)
    void Init(void* parent);  // 0x0065f700 (cSPUIFeedEdit::Init)
    void InitLayout();  // 0x0065f4d0 (cSPUIFeedEdit::InitLayout)
    bool LoadFilter(int param, bool b);
    void Sub65cae0();   // 0x0065cae0
    void Sub65cc50();   // 0x0065cc50
    char AddAsset(int a, int b, int c, void* img);  // 0x0065f390 (cSPUIFeedEdit::AddAsset)
    char HandleMessage(int msg, int* data);
    void UpdateStrings();  // 0x0065cb90 (cSPUIFeedEdit::UpdateStrings)
    void UpdateEnabledState();
    void UpdateGrid();  // 0x0065d260 (cSPUIFeedEdit::UpdateGrid)
    void UpdateButtons();
    bool SetPage(unsigned int page);  // 0x0065d4e0 (cSPUIFeedEdit::SetPage)
    int  GetAssetIndex2(int a, int b);
    void ShowAsset(int a, int b);  // 0x0065d570 (cSPUIFeedEdit::ShowAsset)
};
struct cSPUIFeedEditAssetView_s0065_ea00 {
    void* vt; void* vt4; void* vt8;      // 0x00
    void* mpLayout;                        // 0x0c
    void* mpParentWin;                     // 0x10
    void* mpRootWin;                       // 0x14
    void* mpButtonWin;                     // 0x18
    void* mpAssetWin;                      // 0x1c
    void* mpBackdropWin;                   // 0x20
    void* mpGlowWin;                       // 0x24
    void* mpEmptyWin;                      // 0x28
    void* mpImage;                         // 0x2c
    int   mnMode;                          // 0x30
    int   pad34;                           // 0x34
    uint64_t mnAssetID;                    // 0x38
    uint32_t mnIndex;                      // 0x40
    uint32_t mTickMask;                    // 0x44
    float mfBlinkStart;                    // 0x48
    void ClearAsset();  // 0x0065d050 (cSPUIFeedEditAssetView::ClearAsset)
    void SetMode(int m);  // 0x0065c840 (cSPUIFeedEditAssetView::SetMode)
};
struct CallbackObj {
    char pad[0x74];
    IWindow_s0065_ea00* win;
    void Handler(int a, int b);
};
struct FEStr_s0065_ea00 {
    char* mpBegin; char* mpEnd; char* mpCap; int mAlloc;
    void assign(const char* b, const char* e);   // 0x00454cb0
    FEStr_s0065_ea00& operator=(const FEStr_s0065_ea00& x) { if (&x != this) assign(x.mpBegin, x.mpEnd); return *this; }
};
struct FilterRec {                 // 0x70 bytes
    char pad00[0x18];
    int f18, f1c;
    char pad20[8];
    int f28;
    char pad2c[0x54 - 0x2c];
    FEStr_s0065_ea00 name;                    // +0x54
    int id;                        // +0x64
    char pad68[8];
};
struct IAssetDir {
    bool GetServerId(const void* key, uint64_t* out, bool flag) const;   // 0x0054e530
};
struct FilterDB {
    char pad00[0x58];
    IAssetDir* mpDir;              // +0x58
    char pad5c[0xb4 - 0x5c];
    FilterRec* mpFilterBegin;      // +0xb4
    FilterRec* mpFilterEnd;        // +0xb8
};
FilterDB* __cdecl GetFilterDB();   // 0x0067cb30
void* __cdecl GetImageFromTexture(int a, int b, int c, int d);   // 0x008060d0
struct Cons {                      // SP::FunctionalMatch::Constraint, 0x24 bytes
    uint32_t mParameter, mType;
    int mMin, mMax;
    Cons* cb; Cons* ce; Cons* cc;
    uint32_t p1c, p20;
    Cons(int dummy);                               // 0x00558830
    Cons(uint32_t id, int kind, int value);        // 0x00558960
    void DestroyChild();                           // 0x006066f0
    ~Cons() {
        Cons* e = ce;
        for (Cons* c = cb; c < e; ++c) c->DestroyChild();
        if (cb && ((int*)cb)[-1] != 0) EASTL_allocator_deallocate(cb);
    }
};
struct FKey { int a, b, c; };
struct FKeyVec {
    FKey* b; FKey* e; FKey* c;
    FKeyVec() : b(0), e(0), c(0) {}
    ~FKeyVec() { if (b && ((int*)b)[-1] != 0) EASTL_allocator_deallocate(b); }
};
struct TplDB {
virtual void tp0();
virtual void tp1();
virtual void tp2();
virtual void tp3();
virtual void tp4();
virtual void tp5();
virtual void tp6();
virtual void tp7();
virtual void tp8();
virtual void tp9();
virtual void tp10();
virtual void tp11();
virtual void tp12();
    virtual void __cdecl Query(FKeyVec* out, Cons filter, Cons extra);   // 0x34
virtual void tq0();
virtual void tq1();
virtual void tq2();
virtual void tq3();
virtual void tq4();
virtual void tq5();
virtual void tq6();
virtual void tq7();
virtual void tq8();
virtual void tq9();
virtual void tq10();
virtual void tq11();
virtual void tq12();
virtual void tq13();
virtual void tq14();
virtual void tq15();
virtual void tq16();
virtual void tq17();
    virtual bool Lookup(const FKey* key, uint32_t* outType);             // 0x80
};
TplDB* __cdecl GetTplDB();         // 0x0067cb40
struct ImgRef {
    void* p;
    ImgRef() : p(0) {}
    ~ImgRef() { if (p) ((FnP)Vslot(p, 4))(p); }
};
struct AssetInfoT {
    uint64_t mnAssetID; uint32_t mnType; ImgRef mpImage;
};
struct FWin {
virtual void wa0();
virtual void wa1();
virtual void wa2();
    virtual void* QueryProc(uint32_t id);                                // 0xc
};
struct FProc {
virtual void pa0();
virtual void pa1();
virtual void pa2();
virtual void pa3();
    virtual void* GetParent();                                           // 0x10
virtual void pb0();
virtual void pb1();
virtual void pb2();
virtual void pb3();
virtual void pb4();
virtual void pb5();
virtual void pb6();
virtual void pb7();
virtual void pb8();
virtual void pb9();
virtual void pb10();
virtual void pb11();
virtual void pb12();
virtual void pb13();
virtual void pb14();
virtual void pb15();
virtual void pb16();
virtual void pb17();
virtual void pb18();
    virtual void SetValue(int v, int w);                                 // 0x60
};
struct FParent {
virtual void qa0();
virtual void qa1();
virtual void qa2();
virtual void qa3();
virtual void qa4();
virtual void qa5();
virtual void qa6();
virtual void qa7();
virtual void qa8();
virtual void qa9();
virtual void qa10();
virtual void qa11();
virtual void qa12();
virtual void qa13();
virtual void qa14();
virtual void qa15();
virtual void qa16();
virtual void qa17();
virtual void qa18();
virtual void qa19();
virtual void qa20();
virtual void qa21();
virtual void qa22();
virtual void qa23();
virtual void qa24();
virtual void qa25();
virtual void qa26();
virtual void qa27();
virtual void qa28();
virtual void qa29();
virtual void qa30();
    virtual void SetTab(int a, int b);                                   // 0x7c
};
// ---- items of slice s0065ea00 end

// ---- items of slice s00ed74f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char     g_16065f8;           // 0x016065f8: UI enabled flag
extern const wchar_t g_13ec468[];    // L"" 0x013ec468
struct Key12 {                       // resource key: instance/type/group
    uint32_t a, b, c;
};
extern Key12    g_15ac190;   // 0x015ac190
extern Key12    g_15ac19c;   // 0x015ac19c
extern Key12    g_15ac1cc;   // 0x015ac1cc
extern Key12    g_15ac1f0;   // 0x015ac1f0
extern Key12    g_15ac1fc;   // 0x015ac1fc
extern Key12    g_15ac208;   // 0x015ac208
extern Key12    g_15ac220;   // 0x015ac220
extern Key12    g_15ac22c;   // 0x015ac22c
extern Key12    g_15ac238;   // 0x015ac238
extern Key12    g_15ac250;   // 0x015ac250
extern Key12    g_15ac25c;   // 0x015ac25c
extern Key12    g_15ac268;   // 0x015ac268
struct IWindow_s00ed_74f0 {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
    virtual uint32_t GetControlID();                 // +0x1c
};
struct Message {
    IWindow_s00ed_74f0* source;                                 // +0
    uint32_t pad4;
    uint32_t type;                                   // +8
};
struct cMessageServer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void Post(uint32_t id, int a, int b);    // +0x14
};
struct cAudioSystem {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual int  GetState();                         // +0x20
};
struct cUIGate {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual bool IsBlocked();                        // +0x38
};
extern cUIGate* g_15ad298;                           // 0x015ad298
struct cNotifyTarget {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual void v12();
    virtual void SetText(const wchar_t* text, int flags);   // +0x34
};
struct cNotifyHost {                                 // 0x0067de40 singleton
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual cNotifyTarget* GetTarget();              // +0x20
};
struct cText { const wchar_t* GetText(); };          // 0x006b55c0
struct cUIHint {
    char pad[0x78];
    cText mText;                                     // +0x78
};
class cUIHints { public:
    cUIHint* FindByID(uint32_t id);                  // 0x0067aee0
    void     ShowHint(uint32_t id);                  // 0x0067c830
};
struct cNode;
struct cSim {                                        // *(g + 0x74)
    bool   Classify(int* out);                       // 0x00f41270
    bool   f3b920();                                 // 0x00f3b920
    bool   f3b950();                                 // 0x00f3b950
    cNode* ff3f00();                                 // 0x00ff3f00
    bool   f41420(cNode* n, int a, int b, int c);    // 0x00f41420
    void   f45970();                                 // 0x00f45970
    int    f3bf60();                                 // 0x00f3bf60
    void   f3bcc0(int n);                            // 0x00f3bcc0
    void   f45a80();                                 // 0x00f45a80
    void   f427c0();                                 // 0x00f427c0
};
struct cTutorials {
    void MarkDirty();                                // 0x00ef72c0
    void f8860();                                    // 0x00ef8860
};
struct cHintPanel { void f69a0(int a); };            // *(g + 0xd8); 0x00f069a0
struct cOwned {                                      // *(this + 0x3c)
    void e02e80();                                   // 0x00e02e80
    void e018c0(int a);                              // 0x00e018c0
};
struct cGlobals {
    char        pad0[0x74];
    cSim*       sim;                                 // +0x74
    char        pad1[0xd4 - 0x78];
    cTutorials* tutorials;                           // +0xd4
    cHintPanel* hints;                               // +0xd8
};
extern cGlobals* g_16c7aa4;                          // 0x016c7aa4
struct cSporeGuide { void FUN_00ed4930(); };         // thiscall on a global object (ignores ecx)
extern cSporeGuide g_16c7680;                       // 0x016c7680
cMessageServer* __cdecl MessageServer_s00ed_74f0();             // 0x0067dcc0
cUIHints*       __cdecl UIHints();                   // 0x0067cac0
cNotifyHost*    __cdecl NotifyHost();                // 0x0067de40
cAudioSystem*   __cdecl GetSystemAT();               // 0x00a206f0
int             __cdecl GetRecorderState();          // 0x00435e90
void            __cdecl PlayUISound(uint32_t id, int state);   // 0x00435ed0
int             __cdecl GetCurrentGameMode();        // 0x00b5b800
void            __cdecl ShowSettingsWindow(int mode);          // 0x006035d0
void            __cdecl ShowContextSensitiveSporeGuide();      // 0x00e02200
void            __cdecl CalloutMessageBox(void* where, const Key12* key);   // 0x00809db0
int             __stdcall HintForState(int state);   // 0x00f3b2c0 ($E366)
struct cVerbIconTray {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void SetSelected(int on);                // +0x1c
};
struct PanelCallout {
    char pad00[0x20];
    cVerbIconTray* mpVerbTray;                       // +0x20  == Panel+0x2c
    char pad24[0x3c - 0x24];
    int  mParam;                                     // +0x3c  == Panel+0x48
    int  mType;                                      // +0x40  == Panel+0x4c
    int  mExtra;                                     // +0x44  == Panel+0x50
    int  mKey;                                       // +0x48  == Panel+0x54
    int  mMode;                                      // +0x4c  == Panel+0x58
    void Dispatch(unsigned unused, unsigned selected);   // 0x00ed74f0
};
struct Panel {                                       // primary object; the handler is its base at +8
    char pad0[0xc];
    PanelCallout mCallout;                           // +0x0c
    void ShowCallout();                              // 0x00ed5910
    void SelectionChanged(int index);                // 0x00ed7490
    void FUN_00ed5640();                             // 0x00ed5640
    void FUN_00ed6720(int i);                        // 0x00ed6720
    void FUN_00ed76e0(int i);                        // 0x00ed76e0
    bool FUN_00ed8130(int msg, int type, int extra); // 0x00ed8130
};
struct PanelHandler {                                // sub-object at Panel+8
    virtual void h0();
    virtual bool DoMessage(IWindow_s00ed_74f0* w, const Message* msg);
    Panel* panel() { return (Panel*)((char*)this - 8); }
    char   pad4[0x14 - 4];
    int    mActiveSet;                               // +0x14
    char   pad18[0x3c - 0x18];
    cOwned* mOwned;                                  // +0x3c
};
// ---- items of slice s00ed74f0 end

// ---- items of slice s00ed1880 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* (__thiscall* FV_i)(void*, int);
typedef void* (__thiscall* FV_fff)(void*, void*, void*);
void* __cdecl FUN_00ed1180(void*, void*);                          // 0x00ed1180
void* __cdecl FUN_0067dcc0(void*, void*, int);                     // 0x0067dcc0 SP::MessageServer
struct Container;
void* __cdecl FUN_0092a7a0(void*, int);                            // 0x0092a7a0 Schedule
void* __cdecl FUN_00929c60(void*);                                 // 0x00929c60 Cancel
void* __cdecl FUN_00571db0(void*, void*, void*, void*, void*);     // 0x00571db0 RemoveHandler
void* __cdecl FUN_005cb180(void*, char);                           // 0x005cb180 SetVisible
struct Entry {
    void* a;         // +0x00
    void* b;         // +0x04
    int   cat;       // +0x08
    int   page;      // +0x0c
    int   sub;       // +0x10
};
struct Container {
    char   pad00[8];
    int    f08;                 // +0x08
    int    pad0c;
    void*  hA;                  // +0x10  handle
    void*  hB;                  // +0x14  handle
    void*  hItemUI;             // +0x18  handle
    char   pad1c[4];
    char   conn[0x38 - 0x20];
    void*  hAvatarUI;           // +0x38
    int    pad3c;
    void*  hPaletteCatUI;       // +0x40  QueryInterface 0x52deed23
    int    pad44;
    char   f48;                 // +0x48  visible flag
    char   pad49[3];
    int    notifier;            // +0x4c
    char   pad50[8];
    int    callback;            // +0x58
    Entry* vec0;                // +0x5c
    Entry* vec0End;             // +0x60
    char   pad64[0x0c];
    Entry* vec1;                // +0x70
    Entry* vec1End;             // +0x74
};
// ---- items of slice s00ed1880 end

// ---- items of slice s00ed2600 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl operator_delete(void*);                                           // 0xf47380
void* __cdecl eastl_RBTreeDecrement(void*);              // 0x009215c0
void  __cdecl RemoveHandler(void*, int, int, int, int);  // 0x00571db0
void  __fastcall ShutdownPaletteUI(void*, int);          // 0x005cba90
void  __fastcall ShutdownPalette(void*, int);            // 0x005c5c20
struct CallbackObj_s00ed_2600 { void Cancel(); };                   // 0x00929c60 (thiscall, 0 args)
struct Singleton;
struct RBNode {
    RBNode*  mpLeft;   // +0x00
    RBNode*  mpRight;  // +0x04
    RBNode*  mpParent; // +0x08
    unsigned mColor;   // +0x0c
    void*    mpValue;  // +0x10
};
struct MapInsertResult {
    RBNode* mpNode;    // +0x00
    char    mbNew;     // +0x04
    char    mPad05[3];
};
struct RefMap {
    unsigned mPad00;   // +0x00
    RBNode*  mAnchor;  // +0x04  (tree sentinel; &mAnchor is the anchor node)
    RBNode*  mBegin;   // +0x08
    RBNode*  mRoot;    // +0x0c
    char     mColor;   // +0x10
    char     mPad11[3];
    int      mSize;    // +0x14
    void Nuke(RBNode* node);                                              // 0x00ed2a10
    void Insert(MapInsertResult* result, void** key, int flag);           // 0x00ed2b30
    void InsertUnique(void** result, RBNode* pos, void** key, char flag);  // 0x00ed2a50
    void Erase(void** result, RBNode* node);                              // 0x00ed2ae0
};
struct RefVtbl {
    void (__thiscall* mSlot00)(void*, int); // +0x00
    void (__thiscall* mSlot04)(void*);      // +0x04
    void (__thiscall* mSlot08)(void*);      // +0x08
    void (__thiscall* mSlot0c)(void*);      // +0x0c
};
struct RefObj { RefVtbl* mpVtbl; };
struct HandlerVtbl {
    void  (__thiscall* mDestroy)(void*, int);      // +0x00
    void  (__thiscall* mRelease)(void*);           // +0x04
    void  (__thiscall* mReleaseAlt)(void*);        // +0x08
    void* (__thiscall* mLookup)(void*, unsigned);  // +0x0c
    void  (__thiscall* mSlot10)(void*);            // +0x10
    void  (__thiscall* mSlot14)(void*);            // +0x14
    void  (__thiscall* mSlot18)(void*);            // +0x18
    void  (__thiscall* mSlot1c)(void*);            // +0x1c
    void  (__thiscall* mSlot20)(void*);            // +0x20
    void  (__thiscall* mSlot24)(void*);            // +0x24
    int   (__thiscall* mSlot28)(void*);            // +0x28
};
struct Handler {
    HandlerVtbl* mpVtbl;
    void Cleanup();   // 0x00ed0b70 (thiscall, 0 args)
};
struct Obj3C {
    HandlerVtbl* mpVtbl;  // +0x00
    void*        mPad04;  // +0x04
    Handler*     mpInner08; // +0x08
};
struct Obj44 {
    unsigned mHash;      // +0x00
    int      mGameMode;  // +0x04
    unsigned mPad08;     // +0x08
    void*    mpLookup0c; // +0x0c
    char     mFlag10;    // +0x10
    char     mFlag11;    // +0x11
    char     mPad12[2];
    char     mFlag14;    // +0x14
    char     mPad15[3];
    unsigned mRec0;      // +0x18
    unsigned mRec1;      // +0x1c
    unsigned mRec2;      // +0x20
    char     mFlag24;    // +0x24
    char     mPad25[0x0b];
    void*    mpAddr30;   // +0x30
    int      mIndex34;   // +0x34
    unsigned mPad38;     // +0x38
    void*    mpInner3c;  // +0x3c
    unsigned mPad40;     // +0x40
    void*    mpRef44;    // +0x44
    void Cleanup();      // 0x00644b60
};
struct SingletonVtbl {
    void* mSlot00;                                   // +0x00
    void (__thiscall* mSlot04)(void*, void*, int);   // +0x04
    void (__thiscall* mSlot08)(void*, void*);        // +0x08
};
struct Singleton { SingletonVtbl* mpVtbl; };
Singleton* __cdecl FUN_00920090();                   // 0x00920090
struct PaletteUI {
    void UpdateCategories(void* arg);  // 0x005ca980
    int  GetCurrentCategoryIndex();    // 0x005ca9c0
    void* GetSubCategory(int index);   // 0x005cae30
};
struct PageUI {
    char  mPad00[0x34];
    int*  mpItemsBegin; // +0x34
    int*  mpItemsEnd;   // +0x38
};
struct CategoryUI {
    char  mPad00[0x88];
    char* mpEntriesBegin; // +0x88
    char* mpEntriesEnd;   // +0x8c
    char  mPad90[0x10];
    int   mCurrentPage;   // +0xa0
    PageUI* GetPageUI(int index);        // 0x005c2e50
    void    SetPageVisible(int, int);    // 0x005c29a0
    int     SetPageIndex(int);           // 0x005c3bd0
    void    Update(unsigned);            // 0x005c28b0
};
void __stdcall FUN_00ed2970(int* a, int* b);                              // 0x00ed2970
void* FUN_00ed2390(void* first, void* last, void* dst);                    // 0x00ed2390
struct SimPalette {
    void*    mpVtbl00;    // +0x00
    int      mPad04;      // +0x04
    void*    mpVtbl08;    // +0x08
    void*    mpVtbl0c;    // +0x0c
    Handler* mpHandler10; // +0x10
    int      mH14;        // +0x14
    int      mH18;        // +0x18
    int      mH1c;        // +0x1c
    int      mH20;        // +0x20
    Handler* mpHandler24; // +0x24
    int      mH28;        // +0x28
    int      mH2c;        // +0x2c
    int      mH30;        // +0x30
    int      mH34;        // +0x34
    Handler* mp38;        // +0x38
    Obj3C*   mp3c;        // +0x3c
    Handler* mp40;        // +0x40
    Obj44*   mp44;        // +0x44
    char     mFlag48;     // +0x48
    char     mPad49[3];
    Handler* mp4c;        // +0x4c
    Handler* mp50;        // +0x50
    int      mPad54;      // +0x54
    Handler* mp58;        // +0x58
    int*     mpVec5cBegin; // +0x5c
    int*     mpVec5cEnd;   // +0x60
    int*     mpVec5cCap;   // +0x64
    int      mPad68;       // +0x68
    int      mPad6c;       // +0x6c
    int*     mpVec70Begin; // +0x70
    int*     mpVec70End;   // +0x74
    int*     mpVec70Cap;   // +0x78
    int      mPad7c;       // +0x7c
    int      mPad80;       // +0x80
    RefMap   mMap;         // +0x84

    SimPalette* Construct();                                // 0x00ed2e40
    void        Destroy();                                  // 0x00ed2bc0
    void        Shutdown();                                 // 0x00ed2f30
    void        Launch(void* resource, char flag);          // 0x00ed2600
    int         GetOption(int type);                        // 0x00ed20c0
    int         LoadPageState(CategoryUI* cat);             // 0x00ed1e10
    int         CountPageItems(int data, int index);        // 0x00ed1e70
    void        UpdateMap(CategoryUI* cat, int index, int dir); // 0x00ed2410
    void        UpdateCategory(CategoryUI* cat, char flag); // 0x00ed3120
    void        RemoveCategory(int unused, void* arg);      // 0x00ed33f0
};
void RefMap::Nuke(RBNode* node)
{
    while (node) {
        Nuke(node->mpLeft);
        RBNode* next = node->mpRight;
        void* value = node->mpValue;
        if (value)
            ((RefObj*)value)->mpVtbl->mSlot0c(value);
        operator_delete(node);
        node = next;
    }
}
void RefMap::Insert(MapInsertResult* result, void** key, int flag)
{
    (void)flag;
    RBNode* parent = (RBNode*)&mAnchor;
    RBNode* current = mRoot;
    char less = 1;
    while (current) {
        parent = current;
        less = *key < current->mpValue;
        current = less ? current->mpRight : current->mpLeft;
    }
    RBNode* pos = parent;
    if (less) {
        if (parent == mBegin)
            goto do_insert;
        pos = (RBNode*)eastl_RBTreeDecrement(parent);
    }
    if (*key <= pos->mpValue) {
        result->mpNode = pos;
        result->mbNew = 0;
        return;
    }
do_insert:
    void* node = 0;
    InsertUnique(&node, parent, key, 0);
    result->mpNode = (RBNode*)node;
    result->mbNew = 1;
}
// ---- items of slice s00ed2600 end

// ---- items of slice s00ed37c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const unsigned kMsgIds[];   // 0x01489bb4 (message id table)
template <int N> inline void VCall(void* p)
{
    ((void(__thiscall*)(void*))(*(void***)p)[N])(p);
}
template <int N, class R> inline R VCall1(void* p, unsigned a)
{
    return ((R(__thiscall*)(void*, unsigned))(*(void***)p)[N])(p, a);
}
template <int A, int R, class T> inline void AssignRef(T*& dst, T* v)
{
    T* old = dst;
    if (v != old) {
        if (v) VCall<A>(v);
        dst = v;
        if (old) VCall<R>(old);
    }
}
inline void* operator new(size_t, void* p) { return p; }
inline const int& MaxRef(const int& a, const int& b) { return b < a ? a : b; }
struct Any { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); };
struct PalEntry {
    Any* item;   // +0  (AddRef slot 1, Release slot 2)
    Any* pal;    // +4  (AddRef slot 2, Release slot 3)
    int  cat;    // +8
    int  row;    // +0xc
    int  idx;    // +0x10
    PalEntry() : item(0), pal(0) {}
    ~PalEntry()
    {
        if (pal)  VCall<3>(pal);
        if (item) VCall<2>(item);
    }
};
struct PalVec {
    PalEntry* mpBegin;
    PalEntry* mpEnd;
    PalEntry* mpCapacity;
    int       alloc;
    int       pad;
    void DoInsertValue(PalEntry* pos, const PalEntry& v);   // 0x00ed2d00 (thiscall, ret 8)
    __forceinline void push_back()
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) PalEntry();
        } else {
            DoInsertValue(mpEnd, PalEntry());
        }
    }
};
void* __cdecl operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0
struct Layout { Any* GetWorldMainWindow(unsigned id); };               // 0x00810620
Layout* __cdecl GetLayoutManager();                                    // 0x00805070
struct Row {                         // element of Category::rows (+0x34/+0x38 = item pointers)
    char  pad[0x34];
    void** itemsBegin;
    void** itemsEnd;
    void* GetItem(int i);            // 0x005cae30
};
struct RowCell { Row* row; int pad; };
struct Category : Any {              // cSPPalette
    char    pad4[0x84];
    RowCell* rowsBegin;              // +0x88
    RowCell* rowsEnd;                // +0x8c
    bool Init(const void* key, int a, int b, int c, int d, int e, int f);   // 0x005c6340 (ret 0x1c)
    void AddRowLike(int src);        // 0x005c50b0
    Row* GetRow(int i);              // 0x005c2e50
};
struct PaletteUI_s00ed_37c0 : Any {             // cSPPaletteUI (0x6c)
    PaletteUI_s00ed_37c0();                     // 0x005cb3b0
    char  pad4[0x30];
    Category** catBegin;             // +0x34
    Category** catEnd;               // +0x38
    void Init(Category* pal, Any* mainWin, int a, Any* b);   // 0x005cb5a0 (ret 0x10)
    void SetVisible(int v);          // 0x005ca900 (ret 4)
    int  FindCategoryIndex();        // 0x005ca9c0
    Category* GetCategory(int i);    // 0x005cae30
    uint32_t tail[12];
};
struct CastPanel : Any { uint32_t pad[15]; CastPanel(); };                    // 0x005c5e30 (0x40)
struct ToolObj : Any { uint32_t pad[51]; ToolObj(); };                        // 0x00eccaf0 (0xd0)
struct Obj34 : Any {                                        // 0x005c64e0 (0x34)
    uint32_t pad[12];
    Obj34();
};
struct Obj34Fields {
    void* vt;
    int   rc;
    Any*  doc;       // +8 (refcounted, rc at +4, deleting dtor slot 0)
    int   pad0c;
    Any*  f10;       // +0x10 (release slot 1)
    Any*  f14;       // +0x14 (AddRef 0 / Release 1)
    unsigned short w18;
    char  pad1a[0x17];
    char  b31;
};
struct DocRC { void* vt; int rc; };
struct ItemUI : Any { uint32_t pad[8]; ItemUI(Any* item); };                 // 0x00ece870 (0x24)
struct AvatarUI : Any {
    uint32_t pad[14];
    AvatarUI();            // 0x00ed0ab0
    void Setup(int a);     // 0x00ed1880
};
struct MsgServer { void Register(void* listener, unsigned id); };   // vtable slot 9
MsgServer* __cdecl MessageServer_s00ed_37c0();                          // 0x0067dcc0
struct CallbackBase {                                        // EA::CallbackSystem::Callback
    char pad[0x20];
    CallbackBase(int a, int b, int c, int d, int e, int f, int g);   // 0x00929e70 (ret 0x1c)
    void Set(void* fn, void* obj, int flag);                 // 0x00929da0 (ret 0xc)
    virtual ~CallbackBase();
};
class Scn;
struct ScnCallback : CallbackBase {
    Scn*  owner;     // +0x24
    void* fn;        // +0x28
    int   extra;     // +0x2c
    ScnCallback(Scn* o) : CallbackBase(0, 0, 0x16, 0, 2, 0, 0)
    {
        fn = (void*)0x00ed33f0;
        extra = 0;
        owner = o;
        Set((void*)0x00ed1cf0, this, 0);
    }
    virtual ~ScnCallback() {}
};
struct Globals { char pad[0x74]; struct Sub* sub; };
struct Sub { char pad[0x10]; char* db; char pad2[0xbc]; Any* doc; };
extern Globals* g_16c7aa4_s00ed_37c0;                                   // 0x016c7aa4
struct ResKey { unsigned instance, type, group; };
class Scn {
public:
    char       pad0[8];
    char       listener[0x1c];        // +8 .. message listener sub-object
    MsgServer* server;                // +0x24
    void*      lstn;                  // +0x28
    const void* lstnName;             // +0x2c
    int        lstnFlag;              // +0x30
    int        lstnZero;              // +0x34
    Any*       mainWin;               // +0x38
    CastPanel* castPanel;             // +0x3c
    PaletteUI_s00ed_37c0* paletteUI;             // +0x40
    int        pad44[2];
    AvatarUI*  avatarUI;              // +0x4c
    Any*       tool;                  // +0x50
    int        pad54;
    ScnCallback* callback;            // +0x58
    PalVec     vecA;                  // +0x5c
    PalVec     vecB;                  // +0x70

    void Finish();                    // 0x00ed3a00
    void SelectCategory(Category* cat, int one);   // 0x00ed3120 (ret 8)
    bool Setup();                     // 0x00ed3c00
};
struct ScnRecBody {                 // helper view (ecx == ProcessMessage this - 8)
    char   pad5c[0x5c];
    PalVec palVecA;                 // +0x5c (== ProcessMessage +0x54)
    PalVec palVecB;                 // +0x70 (== ProcessMessage +0x68)
    void Finish();                  // 0x00ed3a00
    void RemoveIcon(int key);       // 0x00ed38a0
    void ClearTwo(int key);         // 0x00ed3920
    void DeselectTwo(int key);      // 0x00ed39a0
    void ChooseSubCategory(void* sub, int key);  // 0x00ed3b20
};
void Scn::Finish()
{
    ((ScnRecBody*)(void*)this)->Finish();
}
// ---- items of slice s00ed37c0 end

// ---- items of slice s00ed4730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   g_15da7c4;   // 0x015da7c4
extern int   g_15da7c8;   // 0x015da7c8
extern int   g_15da7cc;   // 0x015da7cc
extern int   g_15da7d0;   // 0x015da7d0
extern char* g_16c7aa4_s00ed_4730;   // 0x016c7aa4
struct S_ef72c0 { void f(); };
struct S_f45970 { void* f(); };
struct S_f45a80 { void f(); };
struct S_644b10 {
    void f();   // 0x00644b10
};
struct S_644b60 {
    void f();   // 0x00644b60
};
struct S_ef00b0 { void f(); };
struct S_f46630 { char f(void*); };
struct S_b3d3c0 { void* f(); };
struct S_8105b0 { void* f(int, int); };
struct S_e281a0 { void f(int); };
struct S_e22700 { void f(int); };
struct S_f3bfa0 {
    void* f(unsigned);   // 0x00f3bfa0
};
struct S_f3bf60 { int  f(); };
struct S_f3bf70 {
    unsigned f();   // 0x00f3bf70
};
struct S_f3bde0 { char f(int); };
struct S_f3bd90 { void f(void*, unsigned char); };
struct S_e02e80 { void f(); };
struct S_e226c0 { char f(); };
struct S_ed4c70 { void f(int); };
struct S_5508a0 {
    unsigned long long f();   // 0x005508a0
};
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
void  __cdecl SP_ShowContextSensitiveSporepedia(void*);        // 0xe02040
void* __cdecl SP_CheatManager(void);                           // 0x67de20
void* __cdecl FUN_00b3d3c0(void);
void* __cdecl FUN_00b3d310(void);
void  __cdecl FUN_00efc8c0(int);
void* __cdecl FUN_00957f30(void);   // UTFWin::GetManager
void* __cdecl FUN_009512c0(void);
void* __cdecl FUN_009512d0(int, int, const char*, void*);
void  __cdecl FUN_008085d0(void*, void*, int, int, int);
void  __cdecl FUN_00804f50(int);
void* __cdecl SP_EffectsManager(void);                          // 0x67ddd0
char  __cdecl FUN_00e00ac0(void);                               // 0xe00ac0
void* __cdecl SP_WindowManager(void);                           // 0x67caa0
void* __cdecl FUN_00d539d0(void);                               // 0xd539d0
struct S_e277b0 {
    int f(int w);   // 0x00e277b0  cSPUIPosseItem::init (char in al; declared int to keep the full eax)
};
void  __cdecl FUN_00571db0(int, int, int, int, int);            // EA::Messaging::RemoveHandler
void  __cdecl FUN_006447c0(char flag, void** out);              // 0x006447c0
void  __cdecl FUN_0064a990(void* launch);                       // 0x0064a990
int   __cdecl FUN_00b5b800(void);                               // 0x00b5b800
void* __cdecl FUN_008de1a0(void);                               // 0x008de1a0
void* __cdecl FUN_00607a60(void);                               // 0x00607a60
typedef void  (__thiscall *FV_v)(void*);
typedef void* (__thiscall *FV_p)(void*);
typedef void  (__thiscall *FV_i_s00ed_4730)(void*, int);
typedef void* (__thiscall *FV_ip)(void*, int);
typedef void  (__thiscall *FV_ii)(void*, int, int);
typedef void  (__thiscall *FV_iip)(void*, int, int, void*);
typedef void* (__thiscall *FV_iir)(void*, int, int);
typedef int   (__thiscall *FV_ipr)(void*, int);
typedef unsigned long long (__thiscall *FV_q)(void*);
typedef void  (__thiscall *FV_ff)(void*, float, float);
typedef char  (__thiscall *FV_ppiiii)(void*, void*, void*, int, int, int, int);
struct Obj49a0 { void f(); };
struct Obj4b70 { void f(); };
struct Obj4c70 { void f(int flag); };
struct Obj4e30 { char pad[0x84]; int f(); };
struct Obj4f90 { int f(int a, int b); };
struct AssetBrowserLaunch {
    void* m_pVtbl;        // +0x00
    int   m_gameMode;     // +0x04
    int   m_pad08;        // +0x08
    void* m_pEntry;       // +0x0c
    char  m_pad10;        // +0x10
    char  m_flag11;       // +0x11
    char  m_pad12[6];     // +0x12
    int   m_v18;          // +0x18
    int   m_v1c;          // +0x1c
    int   m_v20;          // +0x20
    char  m_flag24;       // +0x24
    char  m_pad25[0xb];   // +0x25
    void* m_pFn30;        // +0x30
    int   m_pad34;        // +0x34
    void* m_pOwner38;     // +0x38
    int   m_pad3c;        // +0x3c
    void* m_p40;          // +0x40
    void* m_pData44;      // +0x44
};
struct EditorLaunchData {
    void* m_pad00[9];     // +0x00
    void* m_pRole0;       // +0x24
    void* m_pRole1;       // +0x28
    void* m_pRole2;       // +0x2c
    void* m_pRole3;       // +0x30
    char  m_flag34;       // +0x34
};
struct PosseEntry {
    void* m_pVtbl;        // +0x00
    void* m_p04;          // +0x04
    int   m_index;        // +0x08
};
struct Obj5020 {
    char  m_pad000[0x50]; // +0x000
    void* m_pPosse;       // +0x050
    char  m_pad054[0xe8]; // +0x054
    void* m_pOwner;       // +0x13c
    char  m_pad140[0xc];  // +0x140
    void* m_pLaunchArg;   // +0x14c
    char  f(void*, void*, void*, void*, void*);
};
struct Obj5190 { int f(int w); };
struct Obj5220 { void* f(); };
struct Obj5330 { int f(int a); };
struct Obj5400 { void f(int a); };
struct Obj54b0 { void f(int a); };
struct PanelMatchDesc {
    int m_field0;         // +0x00
    int m_typeId;         // +0x04
};
struct Obj5640 { void f(); };
// ---- items of slice s00ed4730 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
char __cdecl FUN_00ed48a0(void* a, int* c);  // 0x00ed48a0 (stays in the slice: not this object's)

// ---- items of slice s00ed57e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* __cdecl FUN_0067cae0();                     // 0x0067cae0
extern void* __cdecl FUN_0059c190(void*, void*);         // 0x0059c190  Matrix3FromQuaternion
extern void* __cdecl PlanetModel();                      // 0x00b3d350  SP::PlanetModel
extern const char kUITagAlloc[];                 // 0x013f6b3c  "UI"
extern const char kComplexityWorldName[];        // 0x01489f7c  "UI/cScenarioComplexityMeter/World"
extern const char kComplexityTerraName[];        // 0x01489f58  "UI/cScenarioComplexityMeter/Terra"
extern const char kChecklistUIName[];            // 0x01489f34  "UI/cScenarioTutorialsChecklistUI"
extern const char kScriptUIName[];               // 0x01489f14  "UI/cScenarioEditModeScriptUI"
extern const char kGlobalOptionsName[];          // 0x01489ef4  "Simulator/cSPUIGlobalOptions"
extern const char kPosseAllocName[];             // 0x01476ab8  "UI/Posse"
extern char       kPosseDatum[];                 // 0x015ac28c
extern char       kMessageHandlerStub[];         // 0x01489d38
extern float      kPosseMaxRange;                // 0x01486ebc
#pragma intrinsic(_InterlockedExchange)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
#define G16C7AA4       (*(void**)0x016c7aa4)          // app / scenario global
#define G16065F8       (*(const u8*)0x016065f8)
#define G16065D8       (*(const u32*)0x016065d8)
#define G16065DC       (*(const u32*)0x016065dc)
#define G16065EC       (*(const u32*)0x016065ec)
#define F1485720       (*(const float*)0x01485720)     // _HK_REAL_ONE
#define MAT_DEFAULT    ((void*)0x016c76d8)
#define VTBL_13EB90C   ((void*)0x013eb90c)
#define VTBL_13EB844   ((void*)0x013eb844)
typedef void  (__thiscall* FnV0)(void*);
typedef void  (__thiscall* FnV1)(void*, void*);
typedef void  (__thiscall* FnPost)(void*, u32, void*, int);
typedef void* (__thiscall* FnP0)(void*);
typedef void* (__thiscall* FnP1)(void*, u32);
typedef float (__thiscall* FnF0)(void*);
typedef u32   (__thiscall* FnU0)(void*);
typedef void  (__thiscall* FnVis)(void*, int, int);
void __fastcall FUN_00ed5890(void* self_, int dummy, u32 param_2);  // 0x00ed5890 (defined below; used by a stub's inline body)
void __fastcall FUN_00ed59e0(void* self_, int dummy, u32 mode);  // 0x00ed59e0 (defined below; used by a stub's inline body)
struct ObjV                            // generic view: thiscall callees as members
{
    // panel / page plumbing
    void  FUN_00ed5330(u32);             // 0x00ed5330  Panel::SetMode
    void  FUN_00ed4c70(int);             // 0x00ed4c70  Panel::Select
    void  FUN_00ed5890(u32);             // 0x00ed5890  page (set page id)
    void  FUN_00ed59e0(u32);             // 0x00ed59e0
    void  FUN_00ed2f30();                // 0x00ed2f30
    void  FUN_00edb6c0();                // 0x00edb6c0
    void  FUN_00ed0660();                // 0x00ed0660  cEditorPage::Shutdown
    void  FUN_00ed0030(u32);             // 0x00ed0030  cEditorPage::Update
    void  FUN_00e02e10();                // 0x00e02e10
    void  FUN_00ee12c0();                // 0x00ee12c0
    void  FUN_00ee3f20(u32);             // 0x00ee3f20
    void  FUN_00ef79d0();                // 0x00ef79d0
    void  FUN_00ef72b0();                // 0x00ef72b0  ScenarioTutorials_ClearPending
    void  FUN_00f190a0();                // 0x00f190a0  cScenarioPlayProgressBar::Reset
    void  FUN_00f44dd0();                // 0x00f44dd0
    // scenario / tutorial glue
    char  FUN_00ec5a60(void*, int, int); // 0x00ec5a60
    char  FUN_00ec4320();                // 0x00ec4320
    int   FUN_00a42730();                // 0x00a42730  GetCurrentGameMode
    void* FUN_00f3d780(void*);           // 0x00f3d780
    float FUN_00f3e910();                // 0x00f3e910
    float FUN_00f325b0();                // 0x00f325b0
    char  FUN_00f41270(int*);            // 0x00f41270  sim (mode out)
    char  FUN_00f3b920();                // 0x00f3b920
    void  FUN_005a7410(float);           // 0x005a7410
    void* FUN_008105b0(u32, int);        // 0x008105b0  cSPUILayout::FindWindowByID
    void  FUN_00811ad0(int);             // 0x00811ad0  cSPUILayout::Shutdown
    void  FUN_005fdf40();                // 0x005fdf40  UI::AchievementNotifier::Update
    // geometry
    void* FUN_00b81630(void*, void*);            // 0x00b81630
    void* FUN_00b7f1f0(void*, void*, void*);     // 0x00b7f1f0  BuildSurfaceOrientation_2
    void  FUN_0041cb40(void*);                   // 0x0041cb40  Matrix3::Assign
};
struct SlotMsg
{
    void*         mVtbl;        // +0x00
    volatile long mRefCount;    // +0x04
    u32           mD0;          // +0x08  Data[0].lo
    u32           mD0h;         // +0x0c
    u32           mD1;          // +0x10  Data[1].lo
    u32           mD1h;         // +0x14
    u32           mD2;          // +0x18  Data[2].lo
    u32           mD2h;         // +0x1c
    u32           mD3;          // +0x20  Data[3].lo
    u32           mD3h;         // +0x24
    u32           mD4;          // +0x28  Data[4].lo
    u32           mD4h;         // +0x2c
    u32           mId;          // +0x30
    u32           mField34;     // +0x34
    u32           mRCFlags;     // +0x38
    u32           mField3c;     // +0x3c

    SlotMsg(u32 id) : mId(id)
    {
        mVtbl = VTBL_13EB90C;
        _InterlockedExchange(&mRefCount, 0);
        mVtbl = VTBL_13EB844;
        mRCFlags = 0;
    }
    void FUN_00421cf0();        // 0x00421cf0  SlotMessage::Destruct
};
struct XV3 { float x, y, z; };
struct XV4 { float x, y, z, w; };
struct XMat33 { float m00, m01, m02, m10, m11, m12, m20, m21, m22; };
struct XLocal                          // block handed to the vtbl+0x18 update call
{
    u16    mFlags;                     // +0x00
    u16    mCount;                     // +0x02
    float  mPosX;                      // +0x04
    float  mPosY;                      // +0x08
    float  mPosZ;                      // +0x0c
    float  mW;                         // +0x10
    XMat33 mRot;                       // +0x14
};
void* operator new(unsigned int, const char*, int, int, int, int);   // 0x00f473a0
void* __cdecl GetAllocContext();                                            // 0x009512c0
void* __cdecl AllocNamed(u32 size, int align, const char* name, void* ctx); // 0x009512d0
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PV1 virtual void CAT(_pv, __COUNTER__)();
#define PV5 PV1 PV1 PV1 PV1 PV1
#define PV20 PV5 PV5 PV5 PV5
struct SyncKey { u32 mA, mB, mC; };               // 12-byte resource key
struct IWinS;
class SyncLayout {                                // cSPUILayout
public:
    virtual void pv0();                           // +0x00
    virtual int  AddRef();                        // +0x04
    virtual int  Release();                       // +0x08
    SyncLayout();                                                     // 0x00810000
    bool  Init(const SyncKey* key, bool visible, u32 id);             // 0x008120d0
    void  Shutdown(u32 flags);                                        // 0x00811ad0
    void  SetVisibility(int visible);                                 // 0x00810590
    IWinS* FindWindowByID(u32 id, int recursive);                     // 0x008105b0
    u32 mPad[5];                                  // retail size 0x18
};
struct IWinS {
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    PV20 PV20 PV20 PV1 PV1 PV1                    // slots 2..64
    virtual void SetWinProc(void* proc);          // +0x104
};
struct WinProcS { void* mpVtbl; void* mpOwner; }; // 8-byte window proc object at Panel+0x08
struct SyncPage {                                 // cEditorPage
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    SyncPage();                                                       // 0x00ed02c0
    void Init(IWinS* win, void* param);                               // 0x00ed0400
    u32 mPad[0x54 / 4];                           // retail size 0x58
};
struct SyncChecklist {                            // cScenarioTutorialsChecklistUI
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    SyncChecklist();                                                  // 0x00ef7900
    void SelectCategory(IWinS* win, int which);                       // 0x00efb9c0
    u32 mPad[0x34 / 4];                           // retail size 0x38
};
struct SyncScenarioObj {                          // 0xa0 object built by 0x00ed2e40
    virtual void pv0();                           // +0x00
    virtual int  AddRef();                        // +0x04
    virtual int  Release();                       // +0x08
    SyncScenarioObj();                                                // 0x00ed2e40
    bool Setup();                                                     // 0x00ed3c00
    u32 mPad[0x9c / 4];                           // retail size 0xa0
};
struct SyncC40 {                                  // 0x40 object built by 0x00ee9180
    virtual void pv0();                           // +0x00
    virtual int  AddRef();                        // +0x04
    virtual int  Release();                       // +0x08
    virtual void pv3();                           // +0x0c
    virtual bool Init(int arg);                   // +0x10
    SyncC40();                                                        // 0x00ee9180
    u32 mPad[0x3c / 4];                           // retail size 0x40
};
struct SyncScriptUI {                             // cScenarioEditModeScriptUI
    virtual void pv0();                           // +0x00
    virtual int  AddRef();                        // +0x04
    virtual int  Release();                       // +0x08
    SyncScriptUI();                                                   // 0x00edd580
    bool Init();                                                      // 0x00ee3940
    u32 mPad[0x108 / 4];                          // retail size 0x10c
};
struct SyncMeter {                                // 0xe0 object built by 0x00edaf10
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    SyncMeter();                                                      // 0x00edaf10
    void SetWindow(IWinS* win);                                       // 0x00edb4c0
    u32 mPad[0xdc / 4];                           // retail size 0xe0
};
struct SyncOptions {                              // cSPUIGlobalOptions
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    SyncOptions();                                                    // 0x00e00ec0
    u32 mPad[0x54 / 4];                           // retail size 0x58
};
struct SyncPosse {                                // 0x20c object built by 0x00e25710
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    PV20 PV5 PV5 PV1                              // slots 2..32
    virtual bool SetDatum(const void* datum);     // +0x84
    PV1 PV1
    virtual void SetRange(float lo, float hi, int a, int b);          // +0x90
    PV5 PV1 PV1 PV1 PV1                           // slots 37..45
    virtual void SetCaption(const wchar_t* text); // +0xb8
    PV1
    virtual void SetFlag(int on);                 // +0xc0
    void SetField1e5(int on);                                         // 0x00e21950
    SyncPosse();                                                      // 0x00e25710
    u32 mPad[0x208 / 4];                          // retail size 0x20c
};
struct SyncWinMgr2 {
    PV20 PV20 PV20                                // slots 0..59
    virtual IWinS* FindWindow(u32 id, int recursive);                 // +0x0f0
};
struct SyncWinMgr {
    virtual void pv0();                           // +0x00
    virtual SyncWinMgr2* GetWindows();            // +0x04
};
SyncWinMgr* __cdecl WindowManager();                                 // 0x0067caa0
struct IMsgServerSync {
    PV5 PV1 PV1 PV1 PV1                           // slots 0..8
    virtual void AddListener(void* object, u32 id);                   // +0x24
};
struct SyncHandlerReg {                           // inline registration block at Panel+0x70
    void* mpServer;                               // +0x70
    void* mpObject;                               // +0x74
    void* mpFunc;                                 // +0x78
    u32   mFlags;                                 // +0x7c
    void* mExtra;                                 // +0x80
};
template <class T> struct SyncRef12 {             // AddRef slot1 / Release slot2
    T* mpObject;
    SyncRef12& operator=(T* q) {
        if (q != mpObject) {
            T* pOld = mpObject;
            if (q) q->AddRef();
            mpObject = q;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
};
template <class T> struct SyncRef01 {             // AddRef slot0 / Release slot1
    T* mpObject;
    SyncRef01& operator=(T* q) {
        if (q != mpObject) {
            T* pOld = mpObject;
            if (q) q->AddRef();
            mpObject = q;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
};
namespace SP {
class cString_s00ed_57e0 {
public:
    cString_s00ed_57e0(u32 a, u32 b, const wchar_t* def);                        // 0x006b5770
    ~cString_s00ed_57e0();                                                       // 0x006b5240
    const wchar_t* GetText();                                         // 0x006b55c0
    u32 mPad[5];                                  // retail size 0x14
};
}
struct SyncSim { char mPad[0xd0]; void* mpData; };                    // +0xd0
struct SyncApp { char mPad[0x74]; SyncSim* mpSim; };                  // +0x74
#define SYNC_APP (*(SyncApp**)0x016c7aa4)
struct Panel_s00ed_57e0 {
    char        mPad00[8];                        // +0x00
    WinProcS    mWinProc;                         // +0x08
    void*       mpMsgObject;                      // +0x10
    SyncRef12<SyncScenarioObj> mScn;              // +0x14
    SyncRef12<SyncScriptUI>    mScriptUI;         // +0x18
    u32         mPage;                            // +0x1c
    u32         mField20;                         // +0x20
    SyncRef12<SyncLayout>      mLayout;           // +0x24
    SyncRef12<SyncC40>         mC40;              // +0x28
    SyncRef01<SyncMeter>       mMeter;            // +0x2c
    SyncRef01<SyncPage>        mPageWorld;        // +0x30
    SyncRef01<SyncPage>        mPageTerra;        // +0x34
    SyncRef01<SyncChecklist>   mCheck1;           // +0x38
    SyncRef01<SyncChecklist>   mCheck2;           // +0x3c
    SyncRef01<SyncPosse>       mPosse;            // +0x40
    SyncRef01<SyncOptions>     mOptions;          // +0x44
    char        mPad48[0x28];                     // +0x48
    SyncHandlerReg mHandler;                      // +0x70
    char        mPad84[0x10];                     // +0x84
    u8          mField94;                         // +0x94

    void SetPage(u32 page);                       // 0x00ed5890
    bool SyncState();                             // 0x00ed5d70
};
// ---- items of slice s00ed57e0 end

// ---- items of slice s00ed6720 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern Key12 g_15ac184;              // 0x015ac184: last badge callout key
struct IWindow_s00ed_6720 {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
    virtual uint32_t GetControlID();                 // +0x1c
virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
virtual void w30();
    virtual void SetVisible(bool visible, bool b);   // +0x7c
};
struct cMessageServer_s00ed_6720 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void AddHandler(void* target, void* handler);   // +0x14
};
cMessageServer_s00ed_6720* __cdecl MessageServer_s00ed_6720();             // 0x0067dcc0
struct cSim_s00ed_6720 {
    void   f45970();                                 // 0x00f45970
    void   f45a80();                                 // 0x00f45a80
    void   f427c0();                                 // 0x00f427c0
    void   f3bce0(int id, const void* key);          // 0x00f3bce0
    void   f40ae0(const void* key);                  // 0x00f40ae0 ScenarioNode_AppendToWorld
    void   f3e810(int id);                           // 0x00f3e810
    int    f3bf60();                                 // 0x00f3bf60
    void   f3bcc0(int n);                            // 0x00f3bcc0
    bool   f327f0();                                 // 0x00f327f0
    bool   f41270(int a);                            // 0x00f41270
    char   pad10[0x10];
    void*  f10;                                      // +0x10
};
void __fastcall sim_f3d8c0(cSim_s00ed_6720* self);              // 0x00f3d8c0
struct cGlobals_s00ed_6720 {
    char  pad0[0x18];
    void* f18;                                       // +0x18
    char  pad1[0x74 - 0x1c];
    cSim_s00ed_6720* sim;                                       // +0x74
    char  pad2[0xd4 - 0x78];
    void* d4;                                        // +0xd4
};
extern cGlobals_s00ed_6720* g_16c7aa4_s00ed_6720;                          // 0x016c7aa4
struct cGlobalOptions {
    void  CreateDialog();                            // 0x00e02430
    void* GetAccessFlags();                          // 0x00ff0420
    void  Enable(int a);                             // 0x00e018c0
};
struct cInventory { void ToggleExpanded(); };        // 0x005cb380
struct cMenu {
    cInventory* GetExpandedItem();                   // item at [+0x20]
    void        OnClick2();                          // 0x00e02e80
};
struct cPage {
    void         AsInterface(int a);                 // 0x00ed0260
    void         SetActive(int a);                   // 0x00ed1fe0
    void         SetActiveB(int a);                  // 0x00ee3e40
    void         Vis(int a);                         // 0x00ef8550
    void         Hook(int a);                        // 0x00ed5890
    cInventory*  GetPlayerInventory();               // 0x00a1ad60
};
struct cSPUILayout_s00ed_6720 {
    bool     SetVisibility(bool visible);            // 0x00810590
    bool     IsVisible();                            // 0x00810070
    IWindow_s00ed_6720* FindWindowByID(uint32_t id, bool b);    // 0x008105b0
};
void __cdecl UI_CalloutMessageBox(void* where, const Key12* key);   // 0x00809db0
void* __cdecl GetUITextManager();                    // 0x00957f30
void __cdecl HelpersRemoveWindowCallback(void* p);   // 0x00807590
bool __cdecl FUN_00e00ac0_s00ed_6720();                         // 0x00e00ac0
void __cdecl FUN_00e02e10();                         // 0x00e02e10
void __cdecl FUN_00e21960();                         // 0x00e21960
void __cdecl FUN_00e09600();                         // 0x00e09600
void __cdecl FUN_00e097c0();                         // 0x00e097c0
int  __cdecl FUN_00ed4970();                         // 0x00ed4970 (window callback)
void* __cdecl SetupTimers(void* p, int a);           // 0x008085d0
void* __cdecl FUN_00ef13b0(int a);                   // 0x00ef13b0
void __cdecl cUIBanningContent_Init();               // 0x00dd12f0
void __cdecl cUIBanningContent_Shutdown();           // 0x00dd14b0
void __cdecl EA_Messaging_RemoveHandler(void* a, void* b, void* c, int d, int e); // 0x00571db0
struct cAchievements { void AutoTest(uint32_t id, int count); };   // 0x00676e90
cAchievements* __stdcall AchievementsController(uint32_t id, int count);  // 0x00675250
struct Panel_s00ed_6720;
struct PanelBase {                                   // sub-object at Panel+0x10
    virtual void b0();                               // +0x00
    virtual bool DoBadgeMessage(int key, void* data, int unused);   // +0x04
    Panel_s00ed_6720* panel() { return (Panel_s00ed_6720*)((char*)this - 0x10); }
};
struct Panel_s00ed_6720 {                                       // primary object (cSPUIBadges)
    void*        vtable;                             // +0x00
    void*        mGame;                              // +0x04
    char         pad8[0xc - 8];
    int          mMode0c;                            // +0x0c
    void*        mGap10;                             // +0x10
    cPage*       mPage14;                            // +0x14
    cPage*       mPage18;                            // +0x18
    cSPUILayout_s00ed_6720* mSet1c;                             // +0x1c (layout; also used as an
                                                     //       int selection sentinel)
                                                     //       and as the DoBadgeMessage
                                                     //       message-mode int
    int          mSel20;                             // +0x20
    cSPUILayout_s00ed_6720* mLayout;                            // +0x24
    cMenu*       mMenu;                              // +0x28
    void*        mGap2c;                             // +0x2c
    cPage*       mPage30;                            // +0x30
    cPage*       mPage34;                            // +0x34
    cPage*       mPage38;                            // +0x38
    cPage*       mPage3c;                            // +0x3c
    void*        mList40;                            // +0x40
    cGlobalOptions* mOptions44;                      // +0x44
    int          mState48;                           // +0x48
    Key12        mKey4c;                             // +0x4c
    int          mMode;                              // +0x58
    void*        mMsgServer;                         // +0x5c
    void*        mMsgTarget;                         // +0x60
    void*        mMsgHandler;                        // +0x64
    int          mMode68;                            // +0x68 (DoBadgeMessage msg mode)
    int          mMsgFlags;                          // +0x6c
    void*        mGap70;                             // +0x70
    char         pad74[0x84 - 0x74];
    void*        mOwned84;                           // +0x84
    char         pad88[0x94 - 0x88];
    char         mReady94;                           // +0x94

    void Rebuild(int which);                         // 0x00ed6720
    void Activate2();                                // 0x00ed6a10
    void Deactivate2();                              // 0x00ed6b00
    void BadgeAutoTest();                            // 0x00ed7060
    void SelectionChanged(int a);                    // 0x00ed7490
    void Refresh();                                  // 0x00ed5640
    void ShowCallout();                              // 0x00ed5910
    void SetMode(int key);                           // 0x00ed5330
    void Select(int a);                              // 0x00ed4c70
    void UpdateModes();                              // 0x00ed63a0
    void SyncState();                                // 0x00ed5d70
    void DropSelection();                            // 0x00ed4b70
    int  GetKey();                                   // 0x00ed4e30
};
int  __cdecl Panel_Find(void* p);                    // 0x00ed4f50
int  __cdecl Panel_Match(uint32_t a, uint32_t b, uint32_t c);   // 0x00ed5580
int* __cdecl FUN_00ed29b0(void* begin, void* end, void* key, char c);   // 0x00ed29b0
int  __cdecl FUN_00552300(void* p);                  // 0x00552300
bool __cdecl AssetDataList(uint32_t id, int flags);  // 0x004bbe20 SetAssetData
// ---- items of slice s00ed6720 end

// @ 0x0065c490
void cSPUIFeedEditAssetView::GetThumbnailBackdrop(uint32_t* out, unsigned int id) const
{
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

// @ 0x0065c6f0
unsigned int SP::cSPUIFeedEditAssetView::GetEventMask() const
{
  return (uint32_t)(*(int*)((char*)this + 0x44)) | 0xfffffffd;
}

// @ 0x0065c730
__declspec(noinline) void FindChar(const wchar_t* p1, const wchar_t* p2, const wchar_t* c)
{
  if (p1 != p2) {
    do {
      if (*p1 == *c)
        return;
      ++p1;
    } while (p1 != p2);
  }
}

// @ 0x0065c790
void CtorObj::FUN_0065c790(void* a, void* b, void* c)
{
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
void SP::cSPUIFeedEditAssetView::SetMode(SP::cSPUIFeedEditAssetView::Mode mode)
{
  if (mode == kModeNormal) {
    mfBlinkStart = 0.0f;
    (*(FnP2)Vslot(mpAssetWin, 0x7c))(mpAssetWin, 1, 1);
    (*(FnP2)Vslot(mpBackdropWin, 0x7c))(mpBackdropWin, 1, 1);
    (*(FnP2)Vslot(mpGlowWin, 0x7c))(mpGlowWin, 1, 0);
    (*(FnP2)Vslot(mpEmptyWin, 0x7c))(mpEmptyWin, 1, 0);
    (*(FnP2)Vslot(mpButtonWin, 0x7c))(mpButtonWin, 1, 0);
  } else if (mode == kModeFlash) {
    mfBlinkStart = GetElapsedSeconds_f();
    (*(FnP2)Vslot(mpAssetWin, 0x7c))(mpAssetWin, 1, 1);
    (*(FnP2)Vslot(mpBackdropWin, 0x7c))(mpBackdropWin, 1, 1);
    (*(FnP2)Vslot(mpGlowWin, 0x7c))(mpGlowWin, 1, 1);
    (*(FnP2)Vslot(mpEmptyWin, 0x7c))(mpEmptyWin, 1, 0);
    (*(FnP2)Vslot(mpButtonWin, 0x7c))(mpButtonWin, 1, 0);
    if (mpRootWin && mTickMask == 0) {
      mTickMask = 2;
      (*(FnPv)Vslot(mpRootWin, 0x104))(mpRootWin, this);
    }
  } else if (mode == kModeSelected) {
    mfBlinkStart = 0.0f;
    (*(FnP2)Vslot(mpAssetWin, 0x7c))(mpAssetWin, 1, 1);
    (*(FnP2)Vslot(mpBackdropWin, 0x7c))(mpBackdropWin, 1, 1);
    (*(FnP2)Vslot(mpGlowWin, 0x7c))(mpGlowWin, 1, 1);
    (*(FnP2)Vslot(mpEmptyWin, 0x7c))(mpEmptyWin, 1, 0);
    (*(FnP2)Vslot(mpButtonWin, 0x7c))(mpButtonWin, 1, 1);
  } else {
    mfBlinkStart = 0.0f;
    (*(FnP2)Vslot(mpAssetWin, 0x7c))(mpAssetWin, 1, 0);
    (*(FnP2)Vslot(mpBackdropWin, 0x7c))(mpBackdropWin, 1, 0);
    (*(FnP2)Vslot(mpGlowWin, 0x7c))(mpGlowWin, 1, 0);
    (*(FnP2)Vslot(mpEmptyWin, 0x7c))(mpEmptyWin, 1, 1);
    (*(FnP2)Vslot(mpButtonWin, 0x7c))(mpButtonWin, 1, 0);
  }
  (*(FnP)Vslot(mpRootWin, 0x90))(mpRootWin);
  mnMode = mode;
}

// @ 0x0065c9a0
bool cSPUIFeedEditAssetView::FUN_0065c9a0(void* win)
{
  char* p = (char*)this;
  if (win == *(void**)(p + 0x14) && *(int*)(p + 0x30) == 2 && 0.0f < *(float*)(p + 0x48)) {
    float now = (float)(int)((void* (__cdecl *)(void))GetElapsedSeconds)();
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

// @ 0x0065ca10
void cSPUIFeedEdit::Shutdown()
{
  char* p = (char*)this;
  if (!*(char*)(p + 0x91))
    return;
  ((cXHTMLFrameSet*)(p + 0x18))->FUN_00997140();
  cSPUILayout_s0065_bf20* lay = *(cSPUILayout_s0065_bf20**)(p + 0x14);
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

// @ 0x0065cae0
void cSPUIFeedEdit::FUN_0065cae0()
{
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
void cSPUIFeedEdit::UpdateStrings()
{
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

// @ 0x0065cc50
void cSPUIFeedEdit::FUN_0065cc50()
{
  char* p = (char*)this;
  unsigned int idx = *(unsigned int*)(p + 0xa4);
  unsigned int n = *(unsigned int*)(p + 0xa8);
  cSPUILayout_s0065_bf20* lay = *(cSPUILayout_s0065_bf20**)(p + 0x14);
  void* w1 = lay->FindWindowByID(0x58b5d84, true);
  if (w1)
    (*(FnP2)Vslot(w1, 0x7c))(w1, 1, idx + 1 < n);
  void* w2 = lay->FindWindowByID(0x58b5d7e, true);
  if (w2)
    (*(FnP2)Vslot(w2, 0x7c))(w2, 1, idx != 0);
}

// @ 0x0065ccd0
int cSPUIFeedEdit::GetAssetIndex(int a, int b)
{
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

// @ 0x0065cd70
AssetInfo& AssetInfo::operator=(const AssetInfo& other)
{
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
__declspec(noinline) AssetInfo* FUN_0065cdc0(AssetInfo* first, AssetInfo* last, AssetInfo* out)
{
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
__declspec(noinline) AssetInfo* FUN_0065ce10(AssetInfo* first, AssetInfo* last, AssetInfo* out)
{
  while (last != first) {
    --last;
    --out;
    *out = *last;
  }
  return out;
}

// @ 0x0065cec0
int cSPUIFeedEditAssetView::FUN_0065cec0(void* msg, void* data)
{
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
void cSPUIFeedEditAssetView::FUN_0065cf30(int a, int b, int c, int* asset)
{
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

// @ 0x0065d050
void SP::cSPUIFeedEditAssetView::ClearAsset()
{
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
void ReloadCallback(cSPUIFeedEditAssetView_s0065_d050* self, void* layout, bool b)
{
  (void)layout;
  if (!self)
    return;
  char* p = (char*)self;
  if (b) {
    void* w = ((cSPUILayout_s0065_d050*)*(void**)(p + 0x0c))->FindWindowByID(0x590e400, 1);
    *(void**)(p + 0x14) = w;
    (*(FnPi)Vslot(w, 0x50))(w, *(int*)(p + 0x40));
    (*(FnPv)Vslot(*(void**)(p + 0x14), 0x104))(*(void**)(p + 0x14), self);
    w = ((cSPUILayout_s0065_d050*)*(void**)(p + 0x0c))->FindWindowByID(0x590d548, 1);
    *(void**)(p + 0x1c) = w;
    (*(FnPv)Vslot(w, 0x104))(w, self);
    void* a = (*(FnRetP)Vslot(*(void**)(p + 0x1c), 0xa8))(*(void**)(p + 0x1c));
    if (a) {
      void* bb = ((IWinLookup*)a)->FindByKey(0xef3c47cf);
      if (bb)
        (*(FnPv)Vslot(bb, 0x14))(bb, *(void**)(p + 0x2c));
    }
    w = ((cSPUILayout_s0065_d050*)*(void**)(p + 0x0c))->FindWindowByID(0x591c8d8, 1);
    *(void**)(p + 0x20) = w;
    (*(FnPv)Vslot(w, 0x104))(w, self);
    w = ((cSPUILayout_s0065_d050*)*(void**)(p + 0x0c))->FindWindowByID(0x590c7f0, 1);
    *(void**)(p + 0x24) = w;
    (*(FnPv)Vslot(w, 0x104))(w, self);
    w = ((cSPUILayout_s0065_d050*)*(void**)(p + 0x0c))->FindWindowByID(0x590c890, 1);
    *(void**)(p + 0x28) = w;
    (*(FnPv)Vslot(w, 0x104))(w, self);
    w = ((cSPUILayout_s0065_d050*)*(void**)(p + 0x0c))->FindWindowByID(0x591c790, 1);
    *(void**)(p + 0x18) = w;
    if (w)
      (*(FnPi)Vslot(w, 0x50))(w, *(int*)(p + 0x40));
    ((cSPUIFeedEditAssetView_s0065_d050*)self)->SetMode(*(int*)(p + 0x30));
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

// @ 0x0065d260
void cSPUIFeedEdit_s0065_d050::UpdateGrid()
{
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
      ((cSPUIFeedEditAssetView_s0065_d050*)view)->ClearAsset();
    }
    ++it;
    ++index;
  } while (it != end);
}

// @ 0x0065d410
void AssetRequestCallBack(int* param)
{
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

// @ 0x0065d490
void cSPUIFeedEdit_s0065_d050::FUN_0065d490()
{
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
bool cSPUIFeedEdit_s0065_d050::SetPage(unsigned int page)
{
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
bool cSPUIFeedEdit_s0065_d050::ShowAsset(int a, int b)
{
  char* p = (char*)this;
  int idx = GetAssetIndex(a, b);
  unsigned int count = (*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4;
  if ((unsigned int)idx >= count)
    return false;
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
      *(float*)(view + 0x48) = (float)(int)((void* (__cdecl *)(void))GetElapsedSeconds)();
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
  return true;
}

// @ 0x0065d6a0
int* HashtableU64::erase(int* out, int* node, int* bucket)
{
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

// @ 0x0065d720
bool cSPUIFeedEditAssetView_s0065_d050::Init(void* parent, unsigned int index)
{
  char* p = (char*)this;
  *(void**)(p + 0x10) = parent;
  if (!parent)
    return false;
  void* obj = operator_new_ea(0x18, "Sporepedia", 0, 0, 0, 0);
  void* nw = obj ? ((cSPUILayout_s0065_d050*)obj)->Create() : 0;
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
  if (!((cSPUILayout_s0065_d050*)lay)->Init(&key, 1, 0x5b598fa))
    return false;
  ((cSPUILayout_s0065_d050*)lay)->SetParentWin(*(void**)(p + 0x10), 1, 0x5b598fa);
  ((cSPUILayout_s0065_d050*)lay)->SetReloadCallback((void*)&ReloadCallback, this);
  void* lay2 = *(void**)(p + 0x0c);
  *(unsigned int*)(p + 0x40) = index;
  ReloadCallback(this, lay2, true);
  return true;
}

// @ 0x0065d810
void SP::cSPUIFeedEditAssetView::Shutdown()
{
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

// @ 0x0065d860
FeedEditObj::~FeedEditObj()
{}

// @ 0x0065d9f0
void cSPUIFeedEdit_s0065_d050::SetActive(bool b)
{
  char* p = (char*)this;
  if (b && *(void**)(p + 0x7c))
    (*(FnP2)Vslot(*(void**)(p + 0x7c), 0x7c))(*(void**)(p + 0x7c), 1, 1);
  if (*(void**)(p + 0x80)) {
    (*(FnP2)Vslot(*(void**)(p + 0x80), 0x7c))(*(void**)(p + 0x80), 1, b ? 1 : 0);
    if (b) {
      wchar_t* tmp[3];
      tmp[0] = &g_01667bac;
      tmp[1] = &g_01667bac;
      tmp[2] = &g_01667bae;
      *(int*)(p + 0x8c) = 0;
      GetURL(0x5908ef2, tmp);
      ((cXHTMLFrameSet_s0065_d050*)(p + 0x18))->HandleLocationChange(*(void**)(p + 0x84), tmp[0], 0, 0);
    }
  }
}

// @ 0x0065daa0
FeedEditObj::FeedEditObj()
: mFrameSet((void*)&FUN_00623f40), m8c(0), mb90(false), mb91(false), mf94(0.0f), mf98(0.0f),
      m9c(0), ma0(0), ma4(0), ma8(0), mac(-1), mb148(false), mb149(false), mb14a(false) {
  (*(FnP)Vslot(&mFrameSet, 0))(&mFrameSet);
}

// @ 0x0065dc60
bool cSPUIFeedEdit_s0065_d050::TranslateToken(const wchar_t* token, void* out)
{
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
void __stdcall FUN_0065dd30(const wchar_t* s)
{
  WStr3 url;
  url.b = &g_01667bac;
  url.e = &g_01667bac;
  url.c = &g_01667bae;
  GetURL(0x55192fa, &url);
  const wchar_t* t = s;
  const wchar_t* t1 = s + 1;
  while (*t++) {
  }
  const wchar_t* end = s + (t - t1);
  const wchar_t* dot = s;
  while (dot != end && *dot != L'.')
    ++dot;
  unsigned int n = (unsigned int)(dot - s);
  unsigned int i = 0;
  const wchar_t* q = s;
  unsigned int rem = n;
  while (rem > 3) {
    url.Append(q, q + 3);
    const wchar_t* sep = L"/";
    const wchar_t* se = sep;
    while (*++se) {
    }
    url.Append(sep, sep + (se - sep));
    i += 3;
    q += 3;
    rem = n - i;
  }
  url.Append(s, s + n);
  const wchar_t* g = g_0152694c;
  const wchar_t* ge = g;
  while (*ge)
    ++ge;
  url.Append(g, g + (ge - g));
  unsigned long long id = StrtoU6416(s, 0, 10);
  unsigned long num = wcstoul(s + n + 1, 0, 10);
  ReqObj* obj = new ("Sporepedia", 0, 0, 0, 0) ReqObj(id, num);
  (*(FnP)Vslot(obj, 4))(obj);
  ResProvider* rp = (ResProvider*)GetResourceProvider();
  char res[4];
  (*(void(__thiscall*)(void*, void*, const wchar_t*, void*, void*, int, int))Vslot(rp, 4))(
      rp, res, url.b, (void*)&AssetRequestCallBack, obj, 0, 0);
  if (((int)((char*)url.c - (char*)url.b) & ~1) > 2 && url.b)
    EASTL_allocator_deallocate(url.b);
}

// @ 0x0065ded0
UFOCollisionEffectInfo* VecUFO::erase(UFOCollisionEffectInfo* first, UFOCollisionEffectInfo* last)
{
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

// @ 0x0065df30
__declspec(noinline) AssetInfo_s0065_df30* AssetVec::DoInsertValue(AssetInfo_s0065_df30* position, AssetInfo_s0065_df30* value)
{
    if (end != cap) {
        if (position <= value && value < end) value = value + 1;
        if (end != 0) {
            end->mnAssetID = end[-1].mnAssetID;
            end->mnType = end[-1].mnType;
            end->mpImage = end[-1].mpImage;
            if (end->mpImage) (*(FnP)Vslot(end->mpImage, 0))(end->mpImage);
        }
        UninitMove(position, end - 1, end);
        DestroyRange(position);
        end = end + 1;
        return position;
    }
    int n = (int)(end - begin);
    int nc = (n == 0) ? 1 : n * 2;
    AssetInfo_s0065_df30* buf = 0;
    if (nc != 0)
        buf = (AssetInfo_s0065_df30*)EASTL_allocator_allocate((unsigned)(nc << 4), "Editor", 0, 0,
                                                   (const char*)0x13ebb38, 0xd1);
    if (buf) {
        AssetInfo_s0065_df30* p = UninitCopy(begin, position, buf);
        AssignRange(begin, position, buf);
        if (p) {
            // Field-wise copy (four dword moves at 0x0065e016-0x0065e02d): `*p = *value` makes cl emit
            // a movq pair through xmm0, a register the original never writes.
            p->mnAssetID = value->mnAssetID;
            p->mnType = value->mnType;
            p->mpImage = value->mpImage;
            if (p->mpImage) (*(FnP)Vslot(p->mpImage, 0))(p->mpImage);
        }
        AssetInfo_s0065_df30* p2 = UninitCopy(position, end, p + 1);
        AssignRange(position, end, p + 1);
        if (begin && (begin[-1].mnAssetID != 0)) EASTL_allocator_deallocate(begin);
        begin = buf;
        end = p2;
        cap = buf + nc;
    }
    // The retail tail (0x0065e06f) forms buf + nNewCapacity once and leaves it in eax while storing
    // begin/end/cap, so this grow path returns the capacity pointer, not the stale position.
    return cap;
}

// @ 0x0065e0a0
void SP::cSPUIFeedEdit::UnloadLayout()
{
    char* p = (char*)this;
    if (!*(char*)(p + 0x90)) return;
    void* a = *(void**)(p + 0x80);
    if (a) { *(void**)(p + 0x80) = 0; (*(FnP)Vslot(a, 4))(a); }
    void* b = *(void**)(p + 0x88);
    if (b) { *(void**)(p + 0x88) = 0; (*(FnP)Vslot(b, 4))(b); }
    ((VecPtr*)(p + 0xb0))->erase(*(void**)(p + 0xb0), *(void**)(p + 0xb4));
    ((cXHTMLFrameSet_s0065_df30*)(p + 0x18))->FUN_00997140();
    *(char*)(p + 0x90) = 0;
}

// @ 0x0065e110
bool cSPUIFeedEdit_s0065_df30::Populate()
{
    char* p = (char*)this;
    ((VecPtr*)(p + 0xb0))->erase(*(void**)(p + 0xb0), *(void**)(p + 0xb4));

    cSPUIFeedEditAssetView_s0065_df30* view =
        (cSPUIFeedEditAssetView_s0065_df30*)EASTL_allocator_allocate(0x50, "Sporepedia", 0, 0, 0, 0);
    if (view) {
        view->vt4 = &g_vt_13ec458; view->vt8 = 0;
        view->vt = &g_vt_13fff58;  view->vt4 = &g_vt_13fff48;
        view->mpLayout = 0; view->mpParentWin = 0; view->mpRootWin = 0;
        view->mpButtonWin = 0; view->mpAssetWin = 0; view->mpBackdropWin = 0;
        view->mpGlowWin = 0; view->mpEmptyWin = 0; view->mpImage = 0;
        view->mnMode = 0; view->mnAssetID = (uint64_t)-1;
        view->mnIndex = 0xffffffff; view->mTickMask = 0; view->mfBlinkStart = 0.0f;
    }
    if (!view) return false;

    (*(FnP)Vslot(view, 0))(view);
    int nViews = (*(int*)(p + 0xb4) - *(int*)(p + 0xb0)) >> 2;
    char c = (*(char(__thiscall*)(void*, uint32_t, int))Vslot(view, 0x1c))(view, *(uint32_t*)(p + 0x88), nViews);
    if (!c) { (*(FnP)Vslot(view, 4))(view); return false; }

    void* root = view->mpRootWin;
    if (root == 0) { (*(FnP)Vslot(view, 4))(view); return false; }
    float* r = (*(float*(__thiscall*)(void*))Vslot(root, 0x38))(root);
    *(float*)(p + 0x94) = r[2] - r[0];
    float* r2 = (*(float*(__thiscall*)(void*))Vslot(root, 0x38))(root);
    *(float*)(p + 0x98) = r2[3] - r2[1];
    float* pr = (*(float*(__thiscall*)(void*))Vslot(*(void**)(p + 0x88), 0x38))(*(void**)(p + 0x88));
    float w = pr[2] - pr[0];
    float* pr2 = (*(float*(__thiscall*)(void*))Vslot(*(void**)(p + 0x88), 0x38))(*(void**)(p + 0x88));
    float h = pr2[3] - pr2[1];
    int cols = (int)(w / *(float*)(p + 0x94));
    *(int*)(p + 0x9c) = cols;
    int rows = (int)(h / *(float*)(p + 0x98));
    *(int*)(p + 0xa0) = rows;
    float fx = (w - (float)cols * *(float*)(p + 0x94)) * 0.5f;
    float fy = (h - (float)rows * *(float*)(p + 0x98)) * 0.5f;
    (*(void(__thiscall*)(void*, float, float))Vslot(root, 0x64))(root, fx, fy);

    int idx = 0;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            cSPUIFeedEditAssetView_s0065_df30* v =
                (cSPUIFeedEditAssetView_s0065_df30*)EASTL_allocator_allocate(0x50, "Sporepedia", 0, 0, 0, 0);
            if (v) { v->mpImage = 0; v->mnAssetID = (uint64_t)-1; v->mnIndex = 0xffffffff; v->mTickMask = 0; v->mfBlinkStart = 0.0f; }
            if (idx != 0 && v == 0) {
                ((VecPtr*)(p + 0xb0))->erase(*(void**)(p + 0xb0), *(void**)(p + 0xb4));
                return false;
            }
            float px = (float)col * *(float*)(p + 0x94) + fx;
            float py = (float)row * *(float*)(p + 0x98) + fy;
            if (v->mpRootWin)
                (*(void(__thiscall*)(void*, float, float))Vslot(v->mpRootWin, 0x64))(v->mpRootWin, px, py);
            VecPtr* list = (VecPtr*)(p + 0xb0);
            if (list->end < list->cap) {
                void** slot = (void**)list->end;
                list->end = (char*)list->end + 4;
                if (slot) { *slot = v; (*(FnP)Vslot(v, 0))(v); }
            }
            ++idx;
        }
    }
    void** it = (void**)*(void**)(p + 0xb0);
    void** end = (void**)*(void**)(p + 0xb4);
    for (; it != end; ++it)
        (*(void(__thiscall*)(void*, uint32_t))Vslot(*(void**)(p + 0x88), 0xe8))(*(void**)(p + 0x88), ((cSPUIFeedEditAssetView_s0065_df30*)*it)->mnIndex);
    return true;
}

// @ 0x0065e570
bool cSPUIFeedEdit_s0065_df30::RemoveAsset(int a, int b)
{
    char* p = (char*)this;
    uint32_t idx = GetAssetIndex(a, b);
    uint32_t count = (uint32_t)((*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4);
    if (idx >= count) return false;

    int bucket = *(int*)(*(int*)(p + 0xdc) + *(int*)(p + 0xe0) * 4);
    uint64_t key = (uint64_t)(uint32_t)a | ((uint64_t)(uint32_t)b << 32);
    uint64_t local = 0;
    void* r = HashFind64(&local, &key);
    if (*(int*)r != bucket) {
        local &= 0xffffff00ULL;
        HashEraseR(&local, &key, 0);
    }
    AssetInfo_s0065_df30* first = (AssetInfo_s0065_df30*)(*(int*)(p + 0xc4) + (idx << 4));
    AssetInfo_s0065_df30* e = (AssetInfo_s0065_df30*)*(void**)(p + 0xc8);
    if (first + 1 < e) CopyImpl(first + 1, e, first);
    *(int*)(p + 0xc8) -= 0x10;
    AssetInfo_s0065_df30* lastp = (AssetInfo_s0065_df30*)*(void**)(p + 0xc8);
    if (lastp->mpImage) (*(FnP)Vslot(lastp->mpImage, 4))(lastp->mpImage);
    UpdateEnabledState();
    uint32_t n = (uint32_t)((*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4);
    uint32_t per = (uint32_t)((*(int*)(p + 0xb4) - *(int*)(p + 0xb0)) >> 2);
    uint32_t pages = n / per;
    *(uint32_t*)(p + 0xa8) = pages;
    if (pages * per != n) *(uint32_t*)(p + 0xa8) = pages + 1;
    UpdateButtons();
    UpdateGrid();
    UpdateStrings();
    return true;
}

// @ 0x0065e6d0
void AssetVec::push_back()
{
    AssetInfo_s0065_df30* e = end;
    if (e < cap) {
        end = e + 1;
        if (e) e->mpImage = 0;
        return;
    }
    AssetInfo_s0065_df30 tmp;
    tmp.mpImage = 0;
    DoInsertValue(e, &tmp);
    void* x = *(void* volatile*)&tmp.mpImage;
    if (x) (*(FnP)Vslot(x, 4))(x);
}

// @ 0x0065e720
void cSPUIFeedEdit_s0065_df30::ResetPanel()
{
    char* p = (char*)this;
    mAssetList.erase(mAssetList.begin, mAssetList.end);
    mNewAssets.DoFreeNodes(*(void**)(p + 0xdc), *(void**)(p + 0xe0)); mNewAssets.count = 0;
    mDeleteAssets.DoFreeNodes(*(void**)(p + 0xfc), *(void**)(p + 0x100)); mDeleteAssets.count = 0;
    mExistingAssets.DoFreeNodes(*(void**)(p + 0x11c), *(void**)(p + 0x120)); mExistingAssets.count = 0;

    void** it = (void**)*(void**)(p + 0xb0);
    void** end = (void**)*(void**)(p + 0xb4);
    for (; it != end; ++it) ((cSPUIFeedEditAssetView_s0065_df30*)*it)->ClearAsset();

    *(int*)(p + 0xac) = -1;
    SetPage(0);
    *(int*)(p + 0xa4) = 0;

    void* w = *(void**)(p + 0x80);
    void* r = (*(void*(__thiscall*)(void*, uint32_t, int))Vslot(w, 0xf0))(w, 0x58b5d5b, 1);
    if (r) {
        void* q = (*(void*(__thiscall*)(void*, uint32_t))Vslot(r, 0xc))(r, 0xcf428691);
        if (q) {
            (*(void(__thiscall*)(void*, void*, int))Vslot(q, 0x60))(q, (void*)0x13ec468, 0);
            void* q2 = (*(void*(__thiscall*)(void*))Vslot(q, 0x10))(q);
            (*(void(__thiscall*)(void*, int, int))Vslot(q2, 0x7c))(q2, 2, 1);
        }
    }
    w = *(void**)(p + 0x80);
    r = (*(void*(__thiscall*)(void*, uint32_t, int))Vslot(w, 0xf0))(w, 0x58b5d76, 1);
    if (r) {
        void* q = (*(void*(__thiscall*)(void*, uint32_t))Vslot(r, 0xc))(r, 0xcf428691);
        if (q) (*(void(__thiscall*)(void*, void*, int))Vslot(q, 0x60))(q, (void*)0x13ec468, 0);
    }
    *(uint32_t*)(p + 0x8c) = 0;
    *(char*)(p + 0x149) = 0;
    *(char*)(p + 0x14a) = 0;

    uint32_t n = (uint32_t)((*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4);
    uint32_t per = (uint32_t)((*(int*)(p + 0xb4) - *(int*)(p + 0xb0)) >> 2);
    uint32_t pages = n / per;
    *(uint32_t*)(p + 0xa8) = pages;
    if (pages * per != n) *(uint32_t*)(p + 0xa8) = pages + 1;
    UpdateButtons();
    UpdateStrings();
    UpdateEnabledState();
}

// @ 0x0065e8d0
void cSPUIFeedEdit_s0065_df30::LoadLayout()
{
    char* p = (char*)this;
    if (*(char*)(p + 0x90)) return;

    {
        void* nw = mpLayout->FindWindowByID(0x58cdf30, 1);
        void* old = *(void**)(p + 0x80);
        if (nw != old) {
            if (nw) (*(FnP)Vslot(nw, 0))(nw);
            *(void**)(p + 0x80) = nw;
            if (old) (*(FnP)Vslot(old, 4))(old);
        }
    }
    void* win = *(void**)(p + 0x80);
    if (win) {
        ((IWindow_s0065_df30*)win)->Slot104(p + 8);
        SPUIHelpers_SetWindowAreaToParent(*(void**)(p + 0x80));

        void* nw = mpLayout->FindWindowByID(0x58b6a40, 1);
        void* old = *(void**)(p + 0x88);
        if (nw != old) {
            if (nw) (*(FnP)Vslot(nw, 0))(nw);
            *(void**)(p + 0x88) = nw;
            if (old) (*(FnP)Vslot(old, 4))(old);
        }

        Populate();
        UpdateStrings();
        UpdateEnabledState();

        if (((cXHTMLFrameSet_s0065_df30*)(p + 0x18))->FUN_009979f0(*(void**)(p + 0x80), 0x58b69d0)) {
            void* fr = ((cXHTMLFrameSet_s0065_df30*)(p + 0x18))->GetFrame(g_kFrameName);
            fr = fr ? (char*)fr + 4 : 0;
            ((TextSlot*)(p + 0x84))->Assign(fr);
        }
        *(char*)(p + 0x90) = 1;
    }
}

// @ 0x0065ea00
void cSPUIFeedEdit_s0065_ea00::DoMessage(int msg, void* data)
{
    (void)msg;
    int* p = (int*)data;
    char* s = (char*)this;
    if (p && p[2] == 0x17) {
        if (p[3] == 0x590cb98 && (uint32_t)p[4] < ((*(int*)(s + 0xc8) - *(int*)(s + 0xc4)) >> 2)) {
            cSPUIFeedEditAssetView_s0065_ea00* v = *(cSPUIFeedEditAssetView_s0065_ea00**)(*(int*)(s + 0xc4) + p[4] * 4);
            if (v->mnMode > 0) {
                if (v->mnMode < 3) {
                    v->mfBlinkStart = 0.0f;
                    (*(FnP2)Vslot(v->mpAssetWin, 0x7c))(v->mpAssetWin, 1, 1);
                    (*(FnP2)Vslot(v->mpBackdropWin, 0x7c))(v->mpBackdropWin, 1, 1);
                    (*(FnP2)Vslot(v->mpGlowWin, 0x7c))(v->mpGlowWin, 1, 1);
                    (*(FnP2)Vslot(v->mpEmptyWin, 0x7c))(v->mpEmptyWin, 1, 0);
                    (*(FnP2)Vslot(v->mpButtonWin, 0x7c))(v->mpButtonWin, 1, 1);
                    (*(FnP)Vslot(v->mpRootWin, 0x90))(v->mpRootWin);
                    uint32_t hi = (uint32_t)(v->mnAssetID >> 32);
                    v->mnMode = 3;
                    *(int*)(s + 0xac) = GetAssetIndex2((int)v->mnAssetID, (int)hi);
                    UpdateGrid();
                    return;
                }
                if (v->mnMode == 3) {
                    v->SetMode(1);
                    *(int*)(s + 0xac) = -1;
                    UpdateGrid();
                    return;
                }
            }
        }
    }
    else if (p && p[2] == 0x18) {
        if (p[4] == 0x58b5d5b) { *(bool*)(s + 0x139) = (p[5] != 0); UpdateEnabledState(); return; }
        if (p[4] == 0x58b5d76) { *(char*)(s + 0x13a) = 1; UpdateEnabledState(); return; }
    }
    else if (p && p[2] == 0x287259f6) {
        int* o = (int*)*p;
        uint32_t uVar7 = (*(uint32_t(__thiscall*)(void*))Vslot(o, 0x1c))(o);
        int k = (*(int(__thiscall*)(void*))Vslot(o, 0x20))(o);
        if (k == 0x590cb98) {
            if (uVar7 < ((*(int*)(s + 0xc8) - *(int*)(s + 0xc4)) >> 2)) {
                cSPUIFeedEditAssetView_s0065_ea00* v = *(cSPUIFeedEditAssetView_s0065_ea00**)(*(int*)(s + 0xc4) + uVar7 * 4);
                RemoveAsset((int)v->mnAssetID, (int)(v->mnAssetID >> 32));
                return;
            }
        }
        else {
            if (uVar7 == 0x58b5d7e) { SetPage(*(uint32_t*)(s + 0xac)); return; }
            if (uVar7 == 0x58b5d84) { SetPage(*(uint32_t*)(s + 0xa8)); return; }
            if (uVar7 == 0x5937900) {
                void* a = (*(void*(__thiscall*)(void*, uint32_t, int))Vslot(mpLayout, 0xf0))(mpLayout, 0x58b5d5b, 1);
                void* b = (*(void*(__thiscall*)(void*, uint32_t, int))Vslot(mpLayout, 0xf0))(mpLayout, 0x58b5d76, 1);
                (void)a; (void)b;
                if (mnAssetRowCount == 0) { *(char*)(s + 0x139) = 0; }
                else if (mnAssetRowCount == 1) { *(char*)(s + 0x139) = 1; }
                *(char*)(s + 0x139) = 1;
                return;
            }
        }
    }
    else if (p && p[2] == 0x3326e8a) {
        *(char*)(s + 0x139) = 1;
        return;
    }
    else if (p && p[2] == 0x3326e8b) {
        *(char*)(s + 0x13a) = 1;
        return;
    }
    else if (p && p[2] == 0x43b0aee) {
        FUN_00809db0(0, (void*)0x1526ce4);
        return;
    }
}

// @ 0x0065ef10
void CallbackObj::Handler(int a, int b)
{
    (void)a; (void)b;
    ((cSPUIFeedEdit_s0065_ea00*)((char*)this - 0xc))->ResetPanel();
    (*(FnP)Vslot(win, 0x90))(win);
}

// @ 0x0065ef30
bool cSPUIFeedEdit_s0065_ea00::LoadFilter(int param, bool b)
{
    char* s = (char*)this;
    mNewAssets.DoFreeNodes(*(void**)(s + 0xdc), *(void**)(s + 0xe0)); mNewAssets.count = 0;
    mDeleteAssets.DoFreeNodes(*(void**)(s + 0xfc), *(void**)(s + 0x100)); mDeleteAssets.count = 0;
    mExistingAssets.DoFreeNodes(*(void**)(s + 0x11c), *(void**)(s + 0x120)); mExistingAssets.count = 0;
    mAssetList.erase(mAssetList.begin, mAssetList.end);

    FilterDB* db = GetFilterDB();
    FilterRec* it = db->mpFilterBegin;
    FilterRec* itEnd = db->mpFilterEnd;
    for (; it != itEnd; it = (FilterRec*)((char*)it + 0x70)) {
        if (it->id == param)
            break;
    }
    if (it == itEnd)
        return false;
    *(FEStr_s0065_ea00*)(s + 0x138) = it->name;

    FKeyVec keys;
    GetTplDB()->Query(&keys, Cons(0x3cc89b1, 0, param), Cons(0));
    if (!b) {
        FKey* kEnd = keys.e;
        for (FKey* k = keys.b; k != kEnd; ++k) {
            uint64_t id;
            if (GetFilterDB()->mpDir->GetServerId(k, &id, false)) {
                void* img = GetImageFromTexture(k->a, k->c, -1, -1);
                if (img) {
                    AssetInfo_s0065_ea00* pEnd = mAssetList.end;
                    if (pEnd < mAssetList.cap) {
                        mAssetList.end = pEnd + 1;
                        if (pEnd)
                            *(void**)((char*)pEnd + 0xc) = 0;
                    } else {
                        AssetInfoT tmp;
                        mAssetList.DoInsertValue(pEnd, (AssetInfo_s0065_ea00*)&tmp);
                    }
                    AssetInfo_s0065_ea00* e = mAssetList.end - 1;
                    uint32_t type;
                    if (!GetTplDB()->Lookup(k, &type))
                        type = k->b;
                    e->mnAssetID = id;
                    e->mnType = type;
                    void* old = e->mpImage;
                    if (img != old) {
                        ((FnP)Vslot(img, 0))(img);
                        e->mpImage = img;
                        if (old)
                            ((FnP)Vslot(old, 4))(old);
                    }
                    uint32_t itOut[2];
                    mNewAssets.Insert(itOut, &id, TrueTag());
                }
            }
        }
    }
    m8c = 1;
    Sub65cae0();
    uint32_t nAssets = ((char*)mAssetList.end - (char*)mAssetList.begin) >> 4;
    uint32_t nPerPage = ((char*)mViewEnd - (char*)mViewBegin) >> 2;
    mnNumPages = nAssets / nPerPage;
    if (mnNumPages * nPerPage != nAssets)
        mnNumPages++;
    Sub65cc50();
    UpdateStrings();
    FWin* w1 = (FWin*)((IWindow_s0065_ea00*)mpWin80)->SlotF0(0x58b5d5b, 1);
    if (w1) {
        FProc* pr = (FProc*)w1->QueryProc(0xcf428691);
        if (pr) {
            pr->SetValue(it->f18, 0);
            mbTransactionActive = (it->f18 != it->f1c);
            ((FParent*)pr->GetParent())->SetTab(2, 0);
        }
    }
    FWin* w2 = (FWin*)((IWindow_s0065_ea00*)mpWin80)->SlotF0(0x58b5d76, 1);
    if (w2) {
        FProc* pr2 = (FProc*)w2->QueryProc(0xcf428691);
        if (pr2)
            pr2->SetValue(it->f28, 0);
    }
    mbNameSet = 0;
    Sub65cae0();
    if (mAssetList.begin != mAssetList.end) {
        AssetInfo_s0065_ea00* last = mAssetList.end;
        ShowAsset(((int*)last)[-4], ((int*)last)[-3]);
    }
    return true;
}

// @ 0x0065f390
char cSPUIFeedEdit_s0065_ea00::AddAsset(int a, int b, int c, void* img)
{
    char* s = (char*)this;
    if (c == 0) return 0;
    int bucket = *(int*)(*(int*)(s + 0xdc) + *(int*)(s + 0xe0) * 4);
    uint64_t key = (uint64_t)(uint32_t)a | ((uint64_t)(uint32_t)b << 32);
    uint64_t local = 0;
    void* r = HashFind64(&local, &key);
    if (*(int*)r != bucket) { return 0; }
    int b2 = *(int*)(*(int*)(s + 0xfc) + *(int*)(s + 0x100) * 4);
    void* r2 = HashFind64(&local, &key);
    if (*(int*)r2 != b2) { return 0; }

    mAssetList.push_back();
    AssetInfo_s0065_ea00* e = (AssetInfo_s0065_ea00*)(*(int*)(s + 0xc8) - 0x10);
    e->mnAssetID = (uint64_t)(uint32_t)a | ((uint64_t)(uint32_t)b << 32);
    e->mnType = c;
    ((TextSlot*)&e->mpImage)->Assign(img);
    HashFind64(&local, &key);
    {
        int delBucket = *(int*)(*(int*)(s + 0x11c) + *(int*)(s + 0x120) * 4);
        if (*(int*)(*(int*)(s + 0x11c) + *(int*)(s + 0x120) * 4) == delBucket) {
            /* insert into mExistingAssets */
            HashDoInsert(&local, &key, 0);
        }
    }
    UpdateEnabledState();
    FUN_0065d490();
    char result = 1;
    ShowAsset(a, b);
    UpdateStrings();
    return result;
}

// @ 0x0065f4d0
void cSPUIFeedEdit_s0065_ea00::InitLayout()
{
    char* s = (char*)this;
    void* obj = EASTL_allocator_allocate(0x18, "Sporepedia", 0, 0, 0, 0);
    void* nw = obj ? ((LayoutCtor*)obj)->Create() : 0;
    cSPUILayout_s0065_ea00* old = mpLayout;
    if (nw != old) {
        if (nw) (*(FnP)Vslot(nw, 4))(nw);
        mpLayout = (cSPUILayout_s0065_ea00*)nw;
        if (old) (*(FnP)Vslot(old, 8))(old);
    }
    uint32_t keyv = *(uint32_t*)0x1526cb0;
    uint32_t key[3];
    key[0] = 0xa153f7a1; key[1] = 0x510a95b; key[2] = keyv;
    mpLayout->Init(key, 1, 0x5b598fa);
    mpLayout->SetParentWin(*(void**)(s + 0x7c), 1, 0x5b598fa);
    mpLayout->SetReloadCallback((void*)0x65e9e0, this);
    LoadLayout();
}

// @ 0x0065f580
char cSPUIFeedEdit_s0065_ea00::HandleMessage(int msg, int* data)
{
    char* s = (char*)this;
    if (msg == 0x3b27023) {
        if (data) {
            AddAsset(data[4], data[5], data[6], (void*)data[7]);
            UpdateGrid();
        }
        return 1;
    }
    if (*(char*)(s + 0x138)) {
        if (msg == 0x3cdd5f9) {
            IWindow_s0065_ea00* ms = (IWindow_s0065_ea00*)SP_MessageServer();
            (*(void(__thiscall*)(void*, int, int, int))Vslot(ms, 0x14))(ms, 0x53dd093, 0, 0);
            if (s) FUN_00809db0((void*)0x1526cb4, *(void**)(s + 0xfffffff4 + 0x14 + 0x14));
            return 1;
        }
        if (msg == 0x49a3777) { return 1; }
        if (msg == 0x1dd7bda9 && data && data[1] && data[0] != 1) {
            if (*(int*)(s + 0x7c) == 0) return 1;
            if (*(int*)(s + 0x7c) == 1) return 1;
        }
        *(char*)(s + 0x138) = 0;
    }
    return 0;
}

// @ 0x0065f700
void SP::cSPUIFeedEdit::Init(EA::UTFWin::IWindow * parent)
{
    char* s = (char*)this;
    if (*(char*)(s + 0x91)) return;
    ((cXHTMLFrameSet_s0065_ea00*)(s + 0x18))->FUN_00996280(0x1002, 0x1006, 0x1003, 0x1024);
    IWindow_s0065_ea00* ms = (IWindow_s0065_ea00*)SP_MessageServer();
    if (!ms) return;

    void* old = *(void**)(s + 0x7c);
    if (parent != old) {
        if (parent) (*(FnP)Vslot(parent, 0))(parent);
        *(void**)(s + 0x7c) = parent;
        if (old) (*(FnP)Vslot(old, 4))(old);
    }
    ComObj* m = (ComObj*)FUN_0067de40();
    ComObj* q = m->Slot20();
    q->Slot1c(s);
    ((cSPUIFeedEdit*)s)->InitLayout();
    *(char*)(s + 0x91) = 1;
    void* handler = s + 0x10;
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x3b27023);
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x1dd7bda9);
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x3cdd5f9);
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x49a3777);
}

// @ 0x00ed1fe0
void __fastcall FUN_00ed1fe0(Container* self, int* unused, char show)
{
    int i;

    if (show == self->f48)
        return;

    if (self->hPaletteCatUI != 0)
        FUN_005cb180(
            ((FV_i)(*(void***)self->hPaletteCatUI)[0xc / 4])(self->hPaletteCatUI, 0x52deed23),
            show);
    else
        FUN_005cb180(0, show);

    if (show != 0) {
        char* base = (char*)self + 8;
        self->f08 = (int)FUN_0067dcc0(base, (void*)0x1489bd0, 0x0c);
        self->pad0c; // unused
        for (i = 0; i < 0x30; i += 4) {
            void* h = *(void**)(0x1489bd0 + i);
            if (self->f08 != 0 && base != 0)
                ((FV_fff)(*(void***)self->f08)[0x24 / 4])((void*)self->f08, base, h);
        }
        FUN_0092a7a0((void*)self->callback, 0);
        ((void(__thiscall*)(void*, int))FUN_00ed1180)((void*)self->notifier, (int)show);
        self->f48 = show;
    } else {
        if (self->pad0c == 0)
            ;
        if (self->f08 != 0) {
            int id = self->f08;
            self->f08 = 0;
            FUN_00571db0((void*)id, (void*)0, (void*)0x1489bd0, (void*)0x0c, 0);
        }
        FUN_00929c60((void*)self->callback);
        ((void(__thiscall*)(void*, int))FUN_00ed1180)((void*)self->notifier, (int)show);
        self->f48 = 0;
    }
}

// @ 0x00ed29b0
int* __cdecl FUN_00ed29b0(int* a, int* b, int* key)
{
    int n = (int)((char*)b - (char*)a) / 0x27e8;
    while (n > 0) {
        int half = n >> 1;
        int* mid = (int*)((char*)a + half * 0x27e8);
        if (*mid < *key) {
            a = (int*)((char*)mid + 0x27e8);
            n = n - 1 - half;
        } else {
            n = half;
        }
    }
    return a;
}

// @ 0x00ed2e40
SimPalette* SimPalette::Construct()
{
    mPad04 = 0;
    *(void* volatile*)&mpVtbl08 = (void*)0x013eb394;
    *(void* volatile*)&mpVtbl0c = (void*)0x0140b5a0;

    mpVtbl00 = (void*)0x01489cc8;
    mpVtbl08 = (void*)0x01489cc0;
    mpVtbl0c = (void*)0x01489cbc;

    mpHandler10 = 0;
    mH14 = 0; mH18 = 0; mH1c = 0; mH20 = 0;
    mpHandler24 = 0;
    mH28 = 0; mH2c = 0; mH30 = 0; mH34 = 0;
    mp38 = 0;
    mp3c = 0;
    mp40 = 0;
    mp44 = 0;
    mFlag48 = 0;
    mp4c = 0;
    mp50 = 0;
    mp58 = 0;
    mpVec5cBegin = 0;
    mpVec5cEnd = 0;
    mpVec5cCap = 0;
    mpVec70Begin = 0;
    mpVec70End = 0;
    mpVec70Cap = 0;

    RBNode* anchor = (RBNode*)&mMap.mAnchor;
    anchor->mpRight = 0;
    anchor->mpParent = 0;
    anchor->mColor = 0;
    anchor->mpLeft  = anchor;
    mMap.mBegin = anchor;
    mMap.mRoot = 0;
    mMap.mColor = 0;
    mMap.mSize = 0;

    Singleton* s = FUN_00920090();
    s->mpVtbl->mSlot04(s, (void*)0x015ac078, 0);
    s = FUN_00920090();
    s->mpVtbl->mSlot04(s, (void*)0x015ac074, 0);

    return this;
}

// @ 0x00ed2f30
void SimPalette::Shutdown()
{
    if (mpHandler24) {
        Handler* h = mpHandler24;
        mpHandler24 = 0;
        RemoveHandler(h, mH28, mH2c, mH30, mH34);
    }

    if (mp58) {
        ((CallbackObj_s00ed_2600*)mp58)->Cancel();
        Handler* h = mp58;
        if (h)
            h->mpVtbl->mDestroy(h, 1);
        mp58 = 0;
    }

    if (mp4c) {
        mp4c->Cleanup();
        Handler* h = mp4c;
        if (h) {
            mp4c = 0;
            h->mpVtbl->mReleaseAlt(h);
        }
    }
    if (mp50) {
        mp50->mpVtbl->mSlot24(mp50);
        Handler* h = mp50;
        if (h) {
            mp50 = 0;
            h->mpVtbl->mRelease(h);
        }
    }

    {
        int* begin = mpVec5cBegin;
        int* end = mpVec5cEnd;
        void* newEnd = FUN_00ed2390(end, end, begin);
        FUN_00ed2970((int*)newEnd, end);
        mpVec5cEnd = mpVec5cBegin;
    }
    {
        int* begin = mpVec70Begin;
        int* end = mpVec70End;
        void* newEnd = FUN_00ed2390(end, end, begin);
        FUN_00ed2970((int*)newEnd, end);
        mpVec70End = mpVec70Begin;
    }

    if (mp40) {
        PaletteUI* ui = (PaletteUI*)mp40->mpVtbl->mLookup(mp40, 0x52deed23);
        ShutdownPaletteUI(ui, 0);
    }

    if (mp3c) {
        if (mp3c->mpInner08) {
            void* inner = mp3c->mpInner08->mpVtbl->mLookup(mp3c->mpInner08, 0x12dca0ea);
            ShutdownPalette(inner, 0);
        }
        mp3c->mpVtbl->mReleaseAlt(mp3c);
        mp3c = 0;
    }

    if (mp40) {
        mp40->mpVtbl->mRelease(mp40);
        mp40 = 0;
    }

    if (mp44) {
        mp44->Cleanup();
        operator_delete(mp44);
        mp44 = 0;
    }

    if (mp38) {
        Handler* h = mp38;
        mp38 = 0;
        h->mpVtbl->mRelease(h);
    }
}

// @ 0x00ed3c00
bool Scn::Setup()
{
    AssignRef<0, 1>(mainWin, GetLayoutManager()->GetWorldMainWindow(0x08d0f4fb));

    castPanel = new ("Simulator/Scenario/CastPanel", 0, 0, 0, 0) CastPanel();
    VCall<1>(castPanel);
    paletteUI = new ("Simulator/Scenario/CastPanelUI", 0, 0, 0, 0) PaletteUI_s00ed_37c0();
    VCall<0>(paletteUI);

    Category* pal;
    {
        Any* sub = castPanel ? (Any*)((char*)castPanel + 8) : 0;
        pal = sub ? VCall1<3, Category*>(sub, 0x12dca0ea) : 0;
    }
    ResKey key;
    key.type     = 0x00b1b104;
    key.group    = 0x406b6a00;
    key.instance = 0xb4;
    if (pal->Init(&key, -1, 0, 0, 0, 0, 0)) {
        ToolObj* t = new ("Editor", 0, 0, 0, 0) ToolObj();
        AssignRef<0, 1>(tool, (Any*)t);
        VCall<7>(tool);

        PaletteUI_s00ed_37c0* ui = paletteUI ? VCall1<3, PaletteUI_s00ed_37c0*>(paletteUI, 0x52deed23) : 0;

        Obj34Fields* o = (Obj34Fields*)new ("Editor", 0, 0, 0, 0) Obj34();
        if (o) VCall<1>(o);

        DocRC* doc = (DocRC*)g_16c7aa4_s00ed_37c0->sub->doc;
        DocRC* old = (DocRC*)o->doc;
        if (doc != old) {
            if (doc) doc->rc = doc->rc + 1;
            o->doc = (Any*)doc;
            if (old) {
                int n = old->rc - 1;
                old->rc = n;
                if (n == 0) {
                    old->rc = 1;
                    ((void(__thiscall*)(void*, int))(*(void***)old)[0])(old, 1);
                }
            }
        }
        if (o->f10) {
            Any* p = o->f10;
            o->f10 = 0;
            VCall<1>(p);
        }
        o->w18 = 0x268a;
        o->b31 = 1;
        AssignRef<0, 1>(o->f14, tool);
        ui->Init(pal, mainWin, 0, (Any*)o);
        ui->SetVisible(1);
        VCall<2>(o);
    }

    PaletteUI_s00ed_37c0* ui2 = paletteUI ? VCall1<3, PaletteUI_s00ed_37c0*>(paletteUI, 0x52deed23) : 0;
    for (int i = 0; i < (ui2->catEnd - ui2->catBegin); ++i) {
        Category* cat = ui2->GetCategory(i);
        PalVec* vec;
        int limit;
        if (i < 7) {
            limit = 6;
            vec = &vecA;
        } else if (i == 7) {
            limit = 0x30;
            vec = &vecB;
        } else {
            continue;
        }
        if ((cat->rowsEnd - cat->rowsBegin) < limit) {
            int last = 0;
            for (int k = 0; ; ++k) {
                int cur = (int)(cat->rowsEnd - cat->rowsBegin);
                if (k >= MaxRef(limit, cur)) break;
                if (k < (int)(cat->rowsEnd - cat->rowsBegin)) {
                    last = k;
                } else {
                    cat->AddRowLike(last);
                }
            }
        }
        for (int r = 0; r < (cat->rowsEnd - cat->rowsBegin); ++r) {
            Row* row = cat->GetRow(r);
            for (int j = 0; j < (row->itemsEnd - row->itemsBegin); ++j) {
                void* it = row->GetItem(j);
                Any* data = it ? VCall1<3, Any*>((char*)it + 0xc, 0x0722de52) : 0;
                ItemUI* iu = new ("UI/cSPScenarioPaletteItemUIBase", 0, 0, 0, 0) ItemUI(data);
                ((void(__thiscall*)(void*, int))(*(void***)iu)[9])(iu, i);

                vec->push_back();
                PalEntry& e = vec->mpEnd[-1];
                AssignRef<1, 2>(e.item, (Any*)iu);
                AssignRef<2, 3>(e.pal, (Any*)cat);
                e.cat = i;
                e.idx = j;
                e.row = r;
            }
        }
    }

    SelectCategory(ui2->GetCategory(ui2->FindCategoryIndex()), 1);

    callback = new ("Simulator/Scenario/CastPanel", 0, 0, 0, 0) ScnCallback(this);

    AvatarUI* av = new ("Simulator/Scenario/AvatarUI", 0, 0, 0, 0) AvatarUI();
    AssignRef<1, 2>(avatarUI, av);
    avatarUI->Setup(0);
    Finish();

    void* l = listener;
    server = MessageServer_s00ed_37c0();
    lstn = l;
    lstnName = kMsgIds;
    lstnFlag = 1;
    lstnZero = 0;
    if (server && l)
        ((void(__thiscall*)(void*, void*, unsigned))(*(void***)server)[9])(server, l, 0x030c11c7);
    return true;
}

// @ 0x00ed4930
void FUN_00ed4930(void)
{
    uint32_t buf[0x12];
    char* g = g_16c7aa4_s00ed_4730;
    ((S_ef72c0*)*(int*)(g + 0xd4))->f();
    ((S_644b10*)buf)->f();
    SP_ShowContextSensitiveSporepedia(buf);
    ((S_644b60*)buf)->f();
}

// @ 0x00ed49a0
void Obj49a0::f()
{
    char* s = (char*)this;
    *(int**)s = (int*)0x1489e8c;
    *(int**)(s + 8) = (int*)0x1489e70;
    *(int**)(s + 0xc) = (int*)0x1489e64;
    *(int**)(s + 0x10) = (int*)0x1489e54;
    if (SP_MessageServer() != 0) {
        int* sv = (int*)SP_MessageServer();
        ((FV_iip)(*(void***)sv)[0x2c / 4])(sv, 0xffffd8f1, 0x65ff54a, s + 0x10);
    }
    if (*(int**)(s + 0x8c)) ((FV_v)(*(void***)*(int**)(s + 0x8c))[4 / 4])(*(int**)(s + 0x8c));
    if (*(int**)(s + 0x88)) ((FV_v)(*(void***)*(int**)(s + 0x88))[4 / 4])(*(int**)(s + 0x88));
    if (*(int**)(s + 0x84)) ((FV_v)(*(void***)*(int**)(s + 0x84))[4 / 4])(*(int**)(s + 0x84));
    if (*(int*)(s + 0x70)) {
        int h = *(int*)(s + 0x70);
        *(int*)(s + 0x70) = 0;
        FUN_00571db0(h, *(int*)(s + 0x74), *(int*)(s + 0x78), *(int*)(s + 0x7c), *(int*)(s + 0x80));
    }
    if (*(int*)(s + 0x5c)) {
        int h = *(int*)(s + 0x5c);
        *(int*)(s + 0x5c) = 0;
        FUN_00571db0(h, *(int*)(s + 0x60), *(int*)(s + 0x64), *(int*)(s + 0x68), *(int*)(s + 0x6c));
    }
    if (*(int**)(s + 0x44)) ((FV_v)(*(void***)*(int**)(s + 0x44))[4 / 4])(*(int**)(s + 0x44));
    if (*(int**)(s + 0x40)) ((FV_v)(*(void***)*(int**)(s + 0x40))[4 / 4])(*(int**)(s + 0x40));
    for (int i = 0; i < 2; i++) {
        int* p = *(int**)(s + 0x3c - i * 4);
        if (p) ((FV_v)(*(void***)p)[4 / 4])(p);
    }
    if (*(int**)(s + 0x34)) ((FV_v)(*(void***)*(int**)(s + 0x34))[4 / 4])(*(int**)(s + 0x34));
    if (*(int**)(s + 0x30)) ((FV_v)(*(void***)*(int**)(s + 0x30))[4 / 4])(*(int**)(s + 0x30));
    if (*(int**)(s + 0x2c)) ((FV_v)(*(void***)*(int**)(s + 0x2c))[4 / 4])(*(int**)(s + 0x2c));
    if (*(int**)(s + 0x28)) ((FV_v)(*(void***)*(int**)(s + 0x28))[8 / 4])(*(int**)(s + 0x28));
    if (*(int**)(s + 0x24)) ((FV_v)(*(void***)*(int**)(s + 0x24))[8 / 4])(*(int**)(s + 0x24));
    if (*(int**)(s + 0x18)) ((FV_v)(*(void***)*(int**)(s + 0x18))[8 / 4])(*(int**)(s + 0x18));
    if (*(int**)(s + 0x14)) ((FV_v)(*(void***)*(int**)(s + 0x14))[8 / 4])(*(int**)(s + 0x14));
    *(int**)(s + 0x10) = (int*)0x13eb394;
    *(int**)(s + 8) = (int*)0x13eb938;
    *(int**)s = (int*)0x13ec458;
}

// @ 0x00ed4b70
void Obj4b70::f()
{
    char* s = (char*)this;
    switch (*(int*)(s + 0x58)) {
    case 1: case 3: case 6:
        ((S_ef00b0*)s)->f();
        *(int*)(s + 0x58) = 0;
        return;
    case 4: {
        ((S_b3d3c0*)FUN_00b3d3c0())->f();
        ((S_b3d3c0*)FUN_00b3d310())->f();
        ((S_b3d3c0*)FUN_00b3d310())->f();
        ((S_b3d3c0*)FUN_00b3d3c0())->f();
        FUN_00efc8c0(0);
        ((S_ef00b0*)(*(int*)(g_16c7aa4_s00ed_4730 + 0x78)))->f();
        char c = ((S_f46630*)(*(int*)(g_16c7aa4_s00ed_4730 + 0x74)))->f(s + 0x48);
        if (c) {
            int* sv = (int*)SP_MessageServer();
            ((FV_ii)(*(void***)sv)[0x14 / 4])(sv, 0x86a4609d, 0);
        }
        *(int*)(s + 0x48) = 0;
        *(int*)(s + 0x4c) = 0;
        *(int*)(s + 0x50) = 0;
        *(int*)(s + 0x58) = 0;
        break;
    }
    case 7: {
        int* cm = (int*)SP_CheatManager();
        ((FV_i_s00ed_4730)(*(void***)cm)[0x20 / 4])(cm, (int)"quit");
        *(int*)(s + 0x58) = 0;
        return;
    }
    }
    *(int*)(s + 0x58) = 0;
}

// @ 0x00ed4c70
void Obj4c70::f(int flag)
{
    int* mgr = (int*)FUN_00957f30();
    int* m = (int*)((FV_p)(*(void***)mgr)[4 / 4])(mgr);
    if (m == 0) return;
    int* win = (int*)((FV_iir)(*(void***)m)[0xf0 / 4])(m, 0x2ccda9c, 0);
    char created = 0;
    if (win == 0) {
        if (flag) return;
        void* u = FUN_009512c0();
        int esi = (int)FUN_009512d0(0x20c, 4, "InputCaptureWin", u);
        if (esi != 0) {
            ((S_644b10*)esi)->f();
            *(int*)esi = 0x1414b10;
            *(int*)(esi + 4) = 0x14431f8;
            win = (int*)(esi + 4);
        } else {
            win = 0;
        }
        ((FV_ip)(*(void***)win)[0x50 / 4])(win, 0x2ccda9c);
        ((FV_ip)(*(void***)win)[0x78 / 4])(win, 0x1003);
        void* arg = ((FV_p)(*(void***)m)[0x38 / 4])(m);
        ((FV_i_s00ed_4730)(*(void***)win)[0x6c / 4])(win, (int)arg);
        ((FV_ff)(*(void***)win)[0x70 / 4])(win, 0.0f, 0.0f);
        ((FV_ii)(*(void***)win)[0x7c / 4])(win, 0x40, 1);
        ((FV_ip)(*(void***)m)[0xd8 / 4])(m, (int)win);
        ((FV_ip)(*(void***)m)[0xe8 / 4])(m, (int)win);
        created = 1;
    } else if (flag) {
        int* mgr2 = (int*)FUN_00957f30();
        int* w2 = (int*)((FV_ip)(*(void***)mgr2)[0x54 / 4])(mgr2, 1);
        if (w2 == win) {
            int* mgr3 = (int*)FUN_00957f30();
            ((FV_ii)(*(void***)mgr3)[0x5c / 4])(mgr3, 1, (int)win);
        }
        int* mgr4 = (int*)FUN_00957f30();
        int* w3 = (int*)((FV_ip)(*(void***)mgr4)[0x54 / 4])(mgr4, 0);
        if (w3 == win) {
            int* mgr5 = (int*)FUN_00957f30();
            ((FV_ii)(*(void***)mgr5)[0x5c / 4])(mgr5, 0, (int)win);
        }
        ((FV_ip)(*(void***)m)[0xe0 / 4])(m, (int)win);
        FUN_00804f50(1);
        return;
    }
    {
        int* g1 = (int*)FUN_00957f30();
        ((FV_ii)(*(void***)g1)[0x4c / 4])(g1, 1, (int)win);
        int* g2 = (int*)FUN_00957f30();
        ((FV_ii)(*(void***)g2)[0x4c / 4])(g2, 0, (int)win);
        int* g3 = (int*)FUN_00957f30();
        ((FV_ii)(*(void***)g3)[0x58 / 4])(g3, 1, (int)win);
        int* g4 = (int*)FUN_00957f30();
        ((FV_ii)(*(void***)g4)[0x58 / 4])(g4, 0, (int)win);
    }
    if (created)
        FUN_008085d0(win, (void*)&FUN_00ed48a0, -1, 0, 0);
}

// @ 0x00ed4e30
int Obj4e30::f()
{
    char* s = (char*)this;
    int* p = *(int**)(s + 0x84);
    if (p != 0) {
        if (((FV_q)(*(void***)p)[0x60 / 4])(p) == 0x6ca35b3bull) {
            int* q = (int*)((FV_iir)(*(void***)p)[0x58 / 4])(p, 6, 0);
            int v = *q;
            if (v > 0x7eaf737 && v <= 0x7eaf739)
                return v;
        }
    }
    return 0;
}

// @ 0x00ed4f90
int Obj4f90::f(int a, int b)
{
    (void)a;
    char* s = (char*)this;
    int* msg = (int*)b;
    if (msg[2] == 0x287259f6 && msg[3] == 0x7c4b4a0) {
        ((S_f45970*)(*(int*)(g_16c7aa4_s00ed_4730 + 0x74)))->f();
        int* q = *(int**)(s + 0x50);
        int* r = q ? (int*)((FV_ip)(*(void***)q)[0xc / 4])(q, 0x774c96f) : 0;
        int v = *(int*)((char*)r + 8);
        char c = ((S_e226c0*)s)->f();
        ((S_f3bd90*)(*(int*)(g_16c7aa4_s00ed_4730 + 0x74)))->f((void*)v, (unsigned char)c);
        ((S_f45a80*)(*(int*)(g_16c7aa4_s00ed_4730 + 0x74)))->f();
        return 1;
    }
    return 0;
}

// @ 0x00ed5020
char Obj5020::f(void* a1, void* a2, void* a3, void* a4, void* a5)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    if (m_pOwner != a1) return 0;

    int v0 = 0, v1 = 0, v2 = 0;
    void* q = m_pPosse;
    void* r = q ? (void*)((FV_ip)(*(void***)q)[0xc / 4])(q, 0x774c96f) : 0;
    unsigned idx = (unsigned)((PosseEntry*)r)->m_index;
    unsigned n = ((S_f3bf70*)(*(int*)(g_16c7aa4_s00ed_4730 + 0x74)))->f();
    if (idx < n) {
        int* v = (int*)((S_f3bfa0*)(*(int*)(g_16c7aa4_s00ed_4730 + 0x74)))->f(idx);
        v0 = v[0]; v1 = v[1]; v2 = v[2];
    }

    void* launch = 0;
    FUN_006447c0(0, &launch);
    ((EditorLaunchData*)launch)->m_pRole0 = (void*)g_15da7c4;
    ((EditorLaunchData*)launch)->m_pRole1 = (void*)g_15da7c8;
    ((EditorLaunchData*)launch)->m_pRole2 = (void*)g_15da7cc;
    ((EditorLaunchData*)launch)->m_pRole3 = (void*)g_15da7d0;
    ((EditorLaunchData*)launch)->m_flag34 = 0;

    AssetBrowserLaunch b;
    ((S_644b10*)&b)->f();
    b.m_pVtbl = (void*)0xf25aef31;
    b.m_gameMode = FUN_00b5b800();
    b.m_flag11 = 1;
    b.m_pEntry = r;
    b.m_v18 = v0;
    b.m_v1c = v1;
    b.m_v20 = v2;
    b.m_flag24 = 0;
    b.m_pFn30 = (void*)0xad0e52;
    b.m_pOwner38 = (void*)&m_pLaunchArg;
    if (b.m_pData44 != launch) {
        if (launch != 0) ((FV_v)(*(void***)launch)[4 / 4])(launch);
        void* old = b.m_pData44;
        b.m_pData44 = launch;
        if (old != 0) ((FV_v)(*(void***)old)[8 / 4])(old);
    }

    FUN_0064a990(&b);
    ((S_644b60*)&b)->f();
    if (launch != 0) ((FV_v)(*(void***)launch)[8 / 4])(launch);
    return 1;
}

// @ 0x00ed5190
int Obj5190::f(int w)
{
    char* s = (char*)this;
    int r0 = ((S_e277b0*)s)->f(w);
    if ((unsigned char)r0 == 0) return (int)(r0 & 0xffffff00u);
    int* win = (int*)((S_8105b0*)(w + 0x1bc))->f(0x3dae412, 1);
    ((FV_ii)(*(void***)win)[0x7c / 4])(win, 0x10, 1);
    int* q = *(int**)(s + 0x50);
    int* r = q ? (int*)((FV_ip)(*(void***)q)[0xc / 4])(q, 0x774c96f) : 0;
    int b = (*(int*)((char*)r + 8) != -1) ? 1 : 0;
    int* lay = *(int**)(s + 0x13c);
    int* win2 = lay ? (int*)((FV_iir)(*(void***)lay)[0xf0 / 4])(lay, 0x7c4b4a0, 1) : 0;
    if (win2 != 0)
        ((FV_ii)(*(void***)win2)[0x7c / 4])(win2, 1, b);
    return 1;
}

// @ 0x00ed5220
void* Obj5220::f()
{
    char* s = (char*)this;
    *(int*)(s + 4) = 0;
    *(int*)(s + 8) = 0x14426a0;
    *(int*)(s + 0x10) = 0x13eb384;
    *(int*)s = 0x1489e8c;
    *(int*)(s + 8) = 0x1489e70;
    *(int*)(s + 0xc) = 0x1489e64;
    *(int*)(s + 0x10) = 0x1489e54;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = -1;
    *(int*)(s + 0x20) = -1;
    for (int off = 0x24; off <= 0x8c; off += 4) *(int*)(s + off) = 0;
    if (SP_MessageServer() != 0) {
        int* sv = (int*)SP_MessageServer();
        ((FV_ii)(*(void***)sv)[0x20 / 4])(sv, 0x65ff54a, (int)(s + 0x10));
    }
    for (int i = 0; i < 2; i++) {
        int off = 0x38 + i * 4;
        int* p = *(int**)(s + off);
        if (p) { *(int**)(s + off) = 0; ((FV_v)(*(void***)p)[4 / 4])(p); }
    }
    return s;
}

// @ 0x00ed5330
int Obj5330::f(int a)
{
    (void)a;
    char* s = (char*)this;
    char* f84 = s + 0x84;
    int* p = *(int**)(s + 0x84);
    if (p != 0 && ((FV_q)(*(void***)p)[0x60 / 4])(p) != 0x6ca35b3bull) {
        ((FV_i_s00ed_4730)(*(void***)*(int**)f84)[0xc / 4])(*(int**)f84, 0);
        int* q = *(int**)f84;
        if (q != 0) { *(int**)f84 = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
    }
    if (*(int**)f84 == 0) {
        int* em = (int*)SP_EffectsManager();
        int* q = *(int**)f84;
        if (q != 0) { *(int**)f84 = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
        char c = (char)((FV_ipr)(*(void***)em)[0x2c / 4])(em, 0x6ca35b3b);
        if (c) {
            if (FUN_00e00ac0()) ((S_e02e80*)(*(int*)(s + 0x44)))->f();
            ((S_ed4c70*)s)->f(0);
            int* z = *(int**)f84;
            ((FV_ii)(*(void***)z)[0x48 / 4])(z, 6, 1);
            ((FV_i_s00ed_4730)(*(void***)z)[8 / 4])(z, 0);
            return 1;
        }
    }
    return 0;
}

// @ 0x00ed5400
void Obj5400::f(int a)
{
    (void)a;
    char* s = (char*)this;
    char* f84 = s + 0x84;
    int* p = *(int**)(s + 0x84);
    if (p != 0 && ((FV_q)(*(void***)p)[0x60 / 4])(p) != 0xf08ce134ull) {
        ((FV_i_s00ed_4730)(*(void***)*(int**)f84)[0xc / 4])(*(int**)f84, 0);
        int* q = *(int**)f84;
        if (q != 0) { *(int**)f84 = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
    }
    if (*(int**)f84 == 0) {
        int* em = (int*)SP_EffectsManager();
        int* q = *(int**)f84;
        if (q != 0) { *(int**)f84 = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
        char c = (char)((FV_ipr)(*(void***)em)[0x2c / 4])(em, 0xf08ce134);
        if (c) {
            int* z = *(int**)f84;
            ((FV_ii)(*(void***)z)[0x48 / 4])(z, 6, 1);
            ((FV_ii)(*(void***)z)[0x64 / 4])(z, 0x7ec5866, 0);
            ((FV_i_s00ed_4730)(*(void***)z)[8 / 4])(z, 0);
        }
    }
}

// @ 0x00ed54b0
void Obj54b0::f(int a)
{
    char* s = (char*)this;
    if (*(int**)(s + 0x88) == 0) {
        int* em = (int*)SP_EffectsManager();
        int* q = *(int**)(s + 0x88);
        if (q != 0) { *(int**)(s + 0x88) = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
        char c = (char)((FV_ipr)(*(void***)em)[0x2c / 4])(em, 0x54248876);
        if (c) {
            int* z = *(int**)(s + 0x88);
            ((FV_i_s00ed_4730)(*(void***)z)[8 / 4])(z, 0);
        }
    }
    if (*(int**)(s + 0x8c) == 0) {
        int* em = (int*)SP_EffectsManager();
        int* q = *(int**)(s + 0x8c);
        if (q != 0) { *(int**)(s + 0x8c) = 0; ((FV_v)(*(void***)q)[4 / 4])(q); }
        char c = (char)((FV_ipr)(*(void***)em)[0x2c / 4])(em, 0x14785c1);
        if (c) {
            int* z = *(int**)(s + 0x8c);
            ((FV_i_s00ed_4730)(*(void***)z)[8 / 4])(z, 0);
        }
    }
    *(int*)(s + 0x90) = a;
}

// @ 0x00ed5580
bool __stdcall Panel_Match(int a1, int a2, int a3)
{
    (void)a3;
    PanelMatchDesc* desc = (PanelMatchDesc*)&a1;
    desc->m_typeId = 0x30bdee3;

    void* local = 0;
    if (local != 0) {
        void* t = local; local = 0;
        ((FV_v)(*(void***)t)[4 / 4])(t);
    }
    void* factory = FUN_008de1a0();

    char ok = ((FV_ppiiii)(*(void***)factory)[0xc / 4])(factory, (void*)desc, (void*)&local, 0, 0, 0, 0);
    if (!ok) {
        if (local != 0) {
            void* t = local; local = 0;
            ((FV_v)(*(void***)t)[4 / 4])(t);
        }
        return false;
    }
    if (local == 0) return false;

    void* meta = (void*)((FV_ip)(*(void***)local)[0xc / 4])(local, 0x30bdee3);
    if (meta == 0) {
        if (local != 0) {
            void* t = local; local = 0;
            ((FV_v)(*(void***)t)[4 / 4])(t);
        }
        return false;
    }

    void* auth = FUN_00607a60();
    unsigned long long a = ((FV_q)(*(void***)auth)[0x40 / 4])(auth);
    unsigned long long c = ((S_5508a0*)meta)->f();
    bool r = (a == c);

    if (local != 0) {
        void* t = local; local = 0;
        ((FV_v)(*(void***)t)[4 / 4])(t);
    }
    return r;
}

// @ 0x00ed5640
void Obj5640::f()
{
    char* s = (char*)this;
    int* mgr = *(int**)(g_16c7aa4_s00ed_4730 + 0x74);
    int count = ((S_f3bf60*)mgr)->f();
    unsigned count2 = ((S_f3bf70*)mgr)->f();
    int* wm = (int*)SP_WindowManager();
    int* wm2 = (int*)((FV_p)(*(void***)wm)[4 / 4])(wm);
    int* win = (int*)((FV_iir)(*(void***)wm2)[0xf0 / 4])(wm2, 0x774b060, 1);
    if (win != 0)
        ((FV_ii)(*(void***)win)[0x7c / 4])(win, 2, count < 3);
    ((S_e281a0*)(*(int*)(s + 0x40)))->f(1);
    int* x = (int*)FUN_00d539d0();
    if (x != 0) *(int*)((char*)x + 0x18) = count;
    for (int i = 0; i < count; i++) {
        int pos = ((unsigned)i < count2) ? i : -1;
        int* pi = (int*)operator_new(0xc, "Simulator/tPosseIndex", 0, 0, 0, 0);
        if (pi != 0) {
            pi[1] = 0;
            pi[0] = 0x1489eac;
            pi[2] = pos;
        }
        void* u = FUN_009512c0();
        int* item = (int*)FUN_009512d0(0x150, 4, "UI/cScenarioEditPosseItem", u);
        if (item != 0) {
            ((S_e226c0*)item)->f();
            item[0x14c / 4] = 0x140b5a0;
            item[0] = 0x1489d70;
            item[1] = 0x1489d58;
            item[3] = 0x1489d48;
            item[0x14c / 4] = 0x1489d44;
        }
        ((S_e281a0*)(*(int*)(s + 0x40)))->f((int)item);
        if ((unsigned)i < count2) {
            int* v = (int*)((S_f3bfa0*)mgr)->f(i);
            int v0 = v[0], v1 = v[1], v2 = v[2];
            char c = ((S_f3bde0*)mgr)->f(i);
            ((FV_ii)(*(void***)item)[0x90 / 4])(item, (int)&v0, 0);
            ((S_e22700*)item)->f(c);
        }
    }
}

// @ 0x00ed57e0
void __fastcall FUN_00ed57e0(void* self_, int dummy, u32* param_2)
{
    char* self = (char*)self_;

    if (*param_2 != 0)
    {
        void* holder = *(void**)(self - 0xfc);
        void* src = holder
                  ? (void*)((FnP1)(*(void***)holder)[0xc / 4])(holder, 0x774c96f)
                  : 0;
        u32 d0 = *(u32*)((char*)src + 8);

        SlotMsg msg(0);
        msg.mD0 = d0;
        msg.mD1 = param_2[1];
        msg.mD2 = param_2[2];
        msg.mD3 = param_2[0];

        void* srv = MessageServer();
        ((FnPost)(*(void***)srv)[0x14 / 4])(srv, 0x774e2dc, &msg, 0);

        msg.FUN_00421cf0();
    }

    ((ObjV*)*(void**)((char*)G16C7AA4 + 0xd4))->FUN_00ef72b0();
}

// @ 0x00ed5890
void __fastcall FUN_00ed5890(void* self_, int dummy, u32 param_2)
{
    char* self = (char*)self_;

    if (param_2 == *(u32*)(self + 0x1c))
        return;

    SlotMsg msg(0x74baf67);
    msg.mD0 = param_2;
    msg.mD1 = *(u32*)(self + 0x1c);

    void* srv = MessageServer();
    ((FnPost)(*(void***)srv)[0x14 / 4])(srv, msg.mId, &msg, 0);

    *(u32*)(self + 0x1c) = param_2;

    msg.FUN_00421cf0();
}

// @ 0x00ed5910
void __fastcall FUN_00ed5910(void* self_)
{
    char* self = (char*)self_;

    switch (*(u32*)(self + 0x58))
    {
    case 2:
        *(u32*)(self + 0x58) = 0;
        return;

    case 5:
        FUN_00efc8c0(0);
        ((ObjV*)*(void**)((char*)G16C7AA4 + 0x78))->FUN_00f190a0();
        ((ObjV*)*(void**)((char*)G16C7AA4 + 0x74))->FUN_00f44dd0();
        *(u32*)(self + 0x58) = 0;
        return;

    case 1:
    case 3:
    case 6:
    case 7:
        ((ObjV*)self)->FUN_00ed5330(0x7eaf738);
        return;

    case 4:
        break;

    default:
        *(u32*)(self + 0x58) = 0;
        return;
    }

    void* owner = *(void**)((char*)G16C7AA4 + 0x1c);
    if (owner != 0 && ((ObjV*)owner)->FUN_00ec5a60(self + 0x48, 1, 0) != 0)
    {
        if (((ObjV*)owner)->FUN_00ec4320() != 0)
            return;
        if (((ObjV*)owner)->FUN_00a42730() == 2)
        {
            ((ObjV*)self)->FUN_00ed5330(0x7eaf738);
            return;
        }
    }

    *(u32*)(self + 0x58) = 0;
}

// @ 0x00ed59e0
void __fastcall FUN_00ed59e0(void* self_, int dummy, u32 mode)
{
    char* self = (char*)self_;
    (void)mode;

    if (*(void**)(self + 0x88) == 0)
        return;

    void* obj = ((ObjV*)*(void**)((char*)G16C7AA4 + 0x74))->FUN_00f3d780(*(void**)(self + 0x90));

    char* src;
    if (obj == 0)
        src = 0;
    else
        src = (char*)((FnP1)(*(void***)obj)[0xc / 4])(obj, 0x1186577);

    float fHeight = ((FnF0)(*(void***)src)[0x74 / 4])(src);

    if (*(void**)(self + 0x88) != 0)
    {
        XLocal local;
        XV3    pos;
        XV4    orient;
        XV4    dirOut;

        XV3* v = (XV3*)((FnP0)(*(void***)src)[0x2c / 4])(src);
        pos.x = v->x; pos.y = v->y; pos.z = v->z;

        XV4* q = (XV4*)((FnP0)(*(void***)src)[0x30 / 4])(src);
        orient = *q;

        void* r = ((ObjV*)PlanetModel())->FUN_00b81630(&dirOut, &pos);
        pos = *(XV3*)r;

        local.mPosX = pos.x;
        local.mPosY = pos.y;
        local.mPosZ = pos.z;
        local.mW = F1485720;
        ((ObjV*)&local.mRot)->FUN_0041cb40(MAT_DEFAULT);
        local.mRot = *(const XMat33*)MAT_DEFAULT;
        local.mFlags = 4;
        local.mCount = 1;

        void* qo = ((ObjV*)PlanetModel())->FUN_00b7f1f0(&dirOut, &pos, &orient);

        XMat33 mat;
        FUN_0059c190(&mat, qo);
        local.mRot = mat;

        local.mFlags = (u16)(local.mFlags | 2);
        local.mCount = (u16)(local.mCount + 2);
        local.mW = fHeight;

        void* target = *(void**)(self + 0x88);
        ((FnV1)(*(void***)target)[0x18 / 4])(target, &local);
    }

    if (*(void**)(self + 0x8c) != 0)
    {
        XLocal local;
        XV3    pos;
        XV4    orient;
        XV4    dirOut;

        XV3* v = (XV3*)((FnP0)(*(void***)src)[0x2c / 4])(src);
        pos.x = v->x; pos.y = v->y; pos.z = v->z;

        XV4* q = (XV4*)((FnP0)(*(void***)src)[0x30 / 4])(src);
        orient = *q;

        void* r = ((ObjV*)PlanetModel())->FUN_00b81630(&dirOut, &pos);
        pos = *(XV3*)r;

        local.mPosX = pos.x;
        local.mPosY = pos.y;
        local.mPosZ = pos.z;
        local.mW = F1485720;
        ((ObjV*)&local.mRot)->FUN_0041cb40(MAT_DEFAULT);
        local.mRot = *(const XMat33*)MAT_DEFAULT;
        local.mFlags = 4;
        local.mCount = 1;

        void* qo = ((ObjV*)PlanetModel())->FUN_00b7f1f0(&dirOut, &pos, &orient);

        XMat33 mat;
        FUN_0059c190(&mat, qo);
        local.mRot = mat;

        local.mFlags = (u16)(local.mFlags | 2);
        local.mCount = (u16)(local.mCount + 2);
        local.mW = fHeight;

        void* target = *(void**)(self + 0x8c);
        ((FnV1)(*(void***)target)[0x18 / 4])(target, &local);
    }
}

// @ 0x00ed5d70
bool Panel_s00ed_57e0::SyncState()
{
    SyncKey key = { 0x396f69f5, 0x510a95b, 0x40464100 };

    mLayout = new (kUITagAlloc, 0, 0, 0, 0) SyncLayout();
    if (!mLayout->Init(&key, true, 0x2edd95ca)) {
        mLayout->Shutdown(1);
        mLayout = 0;
        return false;
    }

    IWinS* win = mLayout->FindWindowByID(0xffffffff, 1);
    if (win)
        win->SetWinProc(&mWinProc);

    IWinS* w = mLayout->FindWindowByID(0x73bd748, 1);
    if (w) {
        mPageWorld = new (kComplexityWorldName, 0, 0, 0, 0) SyncPage();
        mPageWorld->Init(w, SYNC_APP->mpSim->mpData);
    }

    w = mLayout->FindWindowByID(0x74b85c8, 1);
    if (w) {
        mPageTerra = new (kComplexityTerraName, 0, 0, 0, 0) SyncPage();
        mPageTerra->Init(w, SYNC_APP->mpSim->mpData);
    }

    w = mLayout->FindWindowByID(0x771f0a0, 1);
    if (w) {
        mCheck1 = new (kChecklistUIName, 0, 0, 0, 0) SyncChecklist();
        mCheck1->SelectCategory(w, 0);
    }

    w = mLayout->FindWindowByID(0x7736c78, 1);
    if (w) {
        mCheck2 = new (kChecklistUIName, 0, 0, 0, 0) SyncChecklist();
        mCheck2->SelectCategory(w, 1);
    }

    mScn = new (kUITagAlloc, 0, 0, 0, 0) SyncScenarioObj();
    if (!mScn->Setup())
        mScn = 0;

    mC40 = new (kUITagAlloc, 0, 0, 0, 0) SyncC40();
    if (!mC40->Init(0))
        mC40 = 0;

    w = mLayout->FindWindowByID(0x7108388, 1);
    if (w) {
        mScriptUI = new (kScriptUIName, 0, 0, 0, 0) SyncScriptUI();
        if (!mScriptUI->Init())
            mScriptUI = 0;
    }

    w = mLayout->FindWindowByID(0x272eb68e, 1);
    if (w) {
        mMeter = new (kUITagAlloc, 0, 0, 0, 0) SyncMeter();
        mMeter->SetWindow(w);
    }

    if (mOptions.mpObject == 0)
        mOptions = new (kGlobalOptionsName, 0, 0, 0, 0) SyncOptions();

    mPosse = new (AllocNamed(0x20c, 4, kPosseAllocName, GetAllocContext())) SyncPosse();
    if (!mPosse->SetDatum(kPosseDatum)) {
        mPosse = 0;
    } else {
        SP::cString_s00ed_57e0 str(0xefdb68ec, 0x760b242, 0);
        mPosse->SetCaption(str.GetText());
        mPosse->SetRange(0.0f, kPosseMaxRange, 0, 0);
        mPosse->SetFlag(0);
        mPosse->SetField1e5(1);
    }

    IWinS* pw = WindowManager()->GetWindows()->FindWindow(0x774b060, 1);
    if (pw)
        pw->SetWinProc(&mWinProc);

    mHandler.mpServer = MessageServer();
    mHandler.mpObject = &mpMsgObject;
    mHandler.mpFunc = kMessageHandlerStub;
    mHandler.mFlags = 1;
    mHandler.mExtra = 0;
    if (mHandler.mpServer != 0 && mHandler.mpObject != 0)
        ((IMsgServerSync*)mHandler.mpServer)->AddListener(mHandler.mpObject, 0x30c11c7);

    if (mLayout.mpObject != 0)
        mLayout->SetVisibility(0);
    mField94 = 0;
    SetPage(0xffffffff);
    mField20 = 0xffffffff;
    return true;
}

// @ 0x00ed63a0
void __fastcall FUN_00ed63a0(void* self_)
{
    char* self = (char*)self_;

    if (*(void**)(self + 0x84) != 0)
        ((FnV1)(*(void***)*(void**)(self + 0x84))[0xc / 4])(*(void**)(self + 0x84), 0);

    ((ObjV*)self)->FUN_00ed4c70(1);

    void* h = *(void**)(self + 0x70);
    if (h != 0)
    {
        *(u32*)(self + 0x70) = 0;
        FUN_00571db0(h, *(void**)(self + 0x74), *(void**)(self + 0x78),
                     *(void**)(self + 0x7c), *(void**)(self + 0x80));
    }

    if (*(void**)(self + 0x44) != 0)
    {
        ((ObjV*)*(void**)(self + 0x44))->FUN_00e02e10();
        void* p = *(void**)(self + 0x44);
        if (p != 0)
        {
            *(u32*)(self + 0x44) = 0;
            ((FnV0)(*(void***)p)[4 / 4])(p);
        }
    }

    if (*(void**)(self + 0x14) != 0)
    {
        ((ObjV*)*(void**)(self + 0x14))->FUN_00ed2f30();
        void* p = *(void**)(self + 0x14);
        if (p != 0)
        {
            *(u32*)(self + 0x14) = 0;
            ((FnV0)(*(void***)p)[8 / 4])(p);
        }
    }

    if (*(void**)(self + 0x28) != 0)
    {
        ((FnV0)(*(void***)*(void**)(self + 0x28))[0x14 / 4])(*(void**)(self + 0x28));
        void* p = *(void**)(self + 0x28);
        if (p != 0)
        {
            *(u32*)(self + 0x28) = 0;
            ((FnV0)(*(void***)p)[8 / 4])(p);
        }
    }

    if (*(void**)(self + 0x18) != 0)
    {
        ((ObjV*)*(void**)(self + 0x18))->FUN_00ee12c0();
        void* p = *(void**)(self + 0x18);
        if (p != 0)
        {
            *(u32*)(self + 0x18) = 0;
            ((FnV0)(*(void***)p)[8 / 4])(p);
        }
    }

    if (*(void**)(self + 0x2c) != 0)
    {
        ((ObjV*)*(void**)(self + 0x2c))->FUN_00edb6c0();
        void* p = *(void**)(self + 0x2c);
        if (p != 0)
        {
            *(u32*)(self + 0x2c) = 0;
            ((FnV0)(*(void***)p)[4 / 4])(p);
        }
    }

    if (*(void**)(self + 0x30) != 0)
    {
        ((ObjV*)*(void**)(self + 0x30))->FUN_00ed0660();
        void* p = *(void**)(self + 0x30);
        if (p != 0)
        {
            *(u32*)(self + 0x30) = 0;
            ((FnV0)(*(void***)p)[4 / 4])(p);
        }
    }

    if (*(void**)(self + 0x34) != 0)
    {
        ((ObjV*)*(void**)(self + 0x34))->FUN_00ed0660();
        void* p = *(void**)(self + 0x34);
        if (p != 0)
        {
            *(u32*)(self + 0x34) = 0;
            ((FnV0)(*(void***)p)[4 / 4])(p);
        }
    }

    {
        char* slot = self + 0x38;
        for (int i = 0; i < 2; ++i, slot += 4)
        {
            if (*(void**)slot != 0)
            {
                ((ObjV*)*(void**)slot)->FUN_00ef79d0();
                void* p = *(void**)slot;
                if (p != 0)
                {
                    *(u32*)slot = 0;
                    ((FnV0)(*(void***)p)[4 / 4])(p);
                }
            }
        }
    }

    if (*(void**)(self + 0x40) != 0)
    {
        ((FnV0)(*(void***)*(void**)(self + 0x40))[0x88 / 4])(*(void**)(self + 0x40));
        void* p = *(void**)(self + 0x40);
        if (p != 0)
        {
            *(u32*)(self + 0x40) = 0;
            ((FnV0)(*(void***)p)[4 / 4])(p);
        }
    }

    if (*(void**)(self + 0x24) != 0)
    {
        ((ObjV*)*(void**)(self + 0x24))->FUN_00811ad0(1);
        void* p = *(void**)(self + 0x24);
        if (p != 0)
        {
            *(u32*)(self + 0x24) = 0;
            ((FnV0)(*(void***)p)[8 / 4])(p);
        }
    }

    ((ObjV*)self)->FUN_00ed5890(0xffffffff);
    *(u32*)(self + 0x20) = 0xffffffff;
}

// @ 0x00ed6540
void __fastcall FUN_00ed6540(void* self_, int dummy, int param_2)
{
    char* self = (char*)self_;
    void* sim = *(void**)((char*)G16C7AA4 + 0x74);

    if (*(void**)(self + 0x28) != 0)
        ((FnV1)(*(void***)*(void**)(self + 0x28))[0x1c / 4])(*(void**)(self + 0x28), (void*)param_2);

    if (*(void**)(self + 0x18) != 0)
        ((ObjV*)*(void**)(self + 0x18))->FUN_00ee3f20((u32)param_2);

    if (*(void**)(self + 0x30) != 0)
    {
        float f = ((ObjV*)sim)->FUN_00f3e910();
        ((ObjV*)*(void**)(self + 0x30))->FUN_005a7410(f);
        ((ObjV*)*(void**)(self + 0x30))->FUN_00ed0030((u32)param_2);
    }

    if (*(void**)(self + 0x34) != 0)
    {
        float f = ((ObjV*)*(void**)((char*)G16C7AA4 + 0x18))->FUN_00f325b0();
        ((ObjV*)*(void**)(self + 0x34))->FUN_005a7410(f);
        ((ObjV*)*(void**)(self + 0x34))->FUN_00ed0030((u32)param_2);
    }

    ((ObjV*)self)->FUN_00ed59e0((u32)param_2);

    int mode = 0;
    char haveSim = ((ObjV*)sim)->FUN_00f41270(&mode);
    char simOk = ((ObjV*)sim)->FUN_00f3b920();

    bool visA = ((haveSim != 0) || mode == 4 || mode == 2 || mode == 3) && (simOk != 0);

    void* wnd = ((ObjV*)*(void**)(self + 0x24))->FUN_008105b0(0x6fcb638, 1);
    u32 stateA = ((FnU0)(*(void***)wnd)[0x28 / 4])(wnd);
    if ((u32)((stateA >> 1) & 1) != (u32)visA)
        ((FnVis)(*(void***)wnd)[0x7c / 4])(wnd, 2, visA);

    bool visB = (haveSim != 0) || mode == 4 || mode == 2 || mode == 3 || mode == 5;

    void* wnd2 = ((ObjV*)*(void**)(self + 0x24))->FUN_008105b0(0xbbbb1001, 1);
    u32 stateB = ((FnU0)(*(void***)wnd2)[0x28 / 4])(wnd2);
    if ((u32)((stateB >> 1) & 1) != (u32)visB)
        ((FnVis)(*(void***)wnd2)[0x7c / 4])(wnd2, 2, visB);

    int showA = (G16065F8 != 0 && G16065EC != 0) ? 1 : 0;
    void* wnd3 = ((ObjV*)*(void**)(self + 0x24))->FUN_008105b0(0xb006ef6e, 1);
    if (wnd3 != 0)
        ((FnVis)(*(void***)wnd3)[0x7c / 4])(wnd3, 2, showA);

    int showB = (G16065F8 != 0 && (u32)((G16065DC - G16065D8) >> 2) > G16065EC) ? 1 : 0;
    void* wnd4 = ((ObjV*)*(void**)(self + 0x24))->FUN_008105b0(0xf006efa5, 1);
    if (wnd4 != 0)
        ((FnVis)(*(void***)wnd4)[0x7c / 4])(wnd4, 2, showB);

    ((ObjV*)FUN_0067cae0())->FUN_005fdf40();
}

// @ 0x00ed6720
void Panel_s00ed_6720::Rebuild(int which)
{
    IWindow_s00ed_6720* w = mLayout->FindWindowByID(0x7105378, true);
    if (w)
        w->SetVisible(true, false);

    mPage30->AsInterface(0);
    mPage34->AsInterface(0);
    mPage3c->Vis(0);
    mPage38->Vis(0);
    (*(void(__thiscall**)(void*, int))(*(uint32_t**)mList40)[0x30])(mList40, 0);
    mPage14->SetActive(0);
    mPage18->SetActiveB(0);
    (*(void(__thiscall**)(void*, int))(*(uint32_t**)mMenu)[6])(mMenu, 0);

    IWindow_s00ed_6720* piVar1 = 0;
    IWindow_s00ed_6720* piVar2 = 0;
    IWindow_s00ed_6720* piVar3 = 0;
    int uVar4 = 0;

    if (which != -1) {
        cAudioSystem* at = GetSystemAT();
        if (at != 0)
            at->GetState();
        PlayUISound(0x8c35f293, 0);
    }

    if (which == 0) {
        mPage14->SetActive(1);
        mPage18->SetActiveB(1);
        (*(void(__thiscall**)(void*, int))(*(uint32_t**)mList40)[0x30])(mList40, 1);
        mPage30->AsInterface(1);
        mPage3c->Vis(1);
        mPage3c->Hook(0);

        piVar1 = mLayout->FindWindowByID(0x7104132, true);
        if (piVar1 == 0)
            piVar2 = 0;
        else {
            (*(void(__thiscall**)(void*))(*(uint32_t**)piVar1)[0])(piVar1);
            piVar2 = (IWindow_s00ed_6720*)(*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t**)piVar1)[3])(piVar1, 0x8ed27e7a);
        }
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 4, 0);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 0x20, 0);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 1, 1);

        piVar2 = mLayout->FindWindowByID(0x7104130, true);
        if (piVar2 == 0)
            piVar3 = 0;
        else {
            (*(void(__thiscall**)(void*))(*(uint32_t**)piVar2)[0])(piVar2);
            piVar3 = (IWindow_s00ed_6720*)(*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t**)piVar2)[3])(piVar2, 0x8ed27e7a);
        }
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar3)[10])(piVar3, 4, 1);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar3)[10])(piVar3, 0x20, 1);
        uVar4 = 0;
    }
    else if (which == 1) {
        FUN_00ef13b0(1);
        mSel20 = (int)mSet1c;
        mPage3c->Hook(1);
        return;
    }
    else if (which == 2) {
        piVar1 = mLayout->FindWindowByID(0x7105378, true);
        if (piVar1 != 0)
            (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar1)[0x1f])(piVar1, 1, 1);
        (*(void(__thiscall**)(void*, int))(*(uint32_t**)mMenu)[6])(mMenu, 1);
        mPage30->AsInterface(1);
        mPage3c->Vis(1);
        mPage3c->Hook(2);

        piVar1 = mLayout->FindWindowByID(0x7104132, true);
        if (piVar1 == 0)
            piVar2 = 0;
        else {
            (*(void(__thiscall**)(void*))(*(uint32_t**)piVar1)[0])(piVar1);
            piVar2 = (IWindow_s00ed_6720*)(*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t**)piVar1)[3])(piVar1, 0x8ed27e7a);
        }
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 4, 1);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 0x20, 1);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 1, 0);

        piVar2 = mLayout->FindWindowByID(0x7104130, true);
        if (piVar2 == 0)
            piVar3 = 0;
        else {
            (*(void(__thiscall**)(void*))(*(uint32_t**)piVar2)[0])(piVar2);
            piVar3 = (IWindow_s00ed_6720*)(*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t**)piVar2)[3])(piVar2, 0x8ed27e7a);
        }
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar3)[10])(piVar3, 4, 0);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar3)[10])(piVar3, 0x20, 0);
        uVar4 = 1;
    }
    else {
        return;
    }

    (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar3)[10])(piVar3, 1, uVar4);
    if (piVar2 != 0)
        (*(void(__thiscall**)(void*))(*(uint32_t**)piVar2)[1])(piVar2);
    if (piVar1 != 0)
        (*(void(__thiscall**)(void*))(*(uint32_t**)piVar1)[1])(piVar1);
}

// @ 0x00ed6a10
void Panel_s00ed_6720::Activate2()
{
    cUIBanningContent_Init();
    FUN_00e09600();

    if (mLayout)
        mLayout->SetVisibility(true);

    int sel = mSel20;
    mReady94 = 1;
    if (sel == -1)
        sel = (int)mSet1c;
    else {
        mSel20 = -1;
        sel = mSel20;      // dead store, kept for shape
    }

    Rebuild(sel);

    mOptions44->CreateDialog();
    void* parent = mOptions44->GetAccessFlags();
    (*(void(__thiscall**)(void*, void*))(*(uint32_t**)parent)[0x41])(parent, (char*)this + 8);

    Refresh();

    void* target = (char*)this + 0x10;
    cMessageServer_s00ed_6720* server = MessageServer_s00ed_6720();
    mMsgServer  = server;
    mMsgTarget  = target;
    mMsgHandler = (void*)0x01489fa0;
    mMode68     = 10;
    mMsgFlags   = 0;

    if (server && target) {
        for (int i = 0; i < 0x28; i += 4) {
            void* h = *(void**)((char*)0x01489fa0 + i);
            (*(void(__thiscall**)(void*, void*, void*))(*(uint32_t**)server)[9])(server, target, h);
        }
    }

    void* mgr = GetUITextManager();
    void* h = (*(void*(__thiscall**)(void*, void*, int, int, int))(*(uint32_t**)mgr)[1])(
                  mgr, &FUN_00ed4970, 0x40, 0, 0);
    SetupTimers(h, 0);
}

// @ 0x00ed6b00
void Panel_s00ed_6720::Deactivate2()
{
    void* mgr = GetUITextManager();
    void* h = (*(void*(__thiscall**)(void*, int(*)(), int, int, int))(*(uint32_t**)mgr)[1])(
                  mgr, FUN_00ed4970, 0, 0, 0);
    HelpersRemoveWindowCallback(h);

    if (mMsgServer) {
        void* srv = mMsgServer;
        mMsgServer = 0;
        EA_Messaging_RemoveHandler(srv, mMsgTarget, mMsgHandler, mMode68, mMsgFlags);
    }

    if (mLayout)
        mLayout->SetVisibility(false);

    mReady94 = 0;
    FUN_00e02e10();

    IWindow_s00ed_6720* w = mLayout->FindWindowByID(0x7105378, true);
    if (w)
        w->SetVisible(true, false);

    mPage30->AsInterface(0);
    mPage34->AsInterface(0);
    mPage3c->Vis(0);
    mPage38->Vis(0);
    (*(void(__thiscall**)(void*, int))(*(uint32_t**)mList40)[0x30])(mList40, 0);
    mPage14->SetActive(0);
    mPage18->SetActiveB(0);
    (*(void(__thiscall**)(void*, int))(*(uint32_t**)mMenu)[6])(mMenu, 0);
    FUN_00e21960();
    cUIBanningContent_Shutdown();
    FUN_00e097c0();
}

// @ 0x00ed6bf0
bool PanelBase::DoBadgeMessage(int key, void* data, int unused)
{
    Panel_s00ed_6720* p = panel();
    (void)unused;
    char* pb = (char*)data;

    if (key == 0x30c11c7) {
        int* r = (int*)Panel_Find(pb + 0x10);
        if (r == 0 || pb[0x44] != 0)
            return false;
        int id = r[2];
        void* args = pb + 0x18;
        g_16c7aa4_s00ed_6720->sim->f45970();
        if (id == -1)
            g_16c7aa4_s00ed_6720->sim->f40ae0(args);
        else
            g_16c7aa4_s00ed_6720->sim->f3bce0(id, args);
        g_16c7aa4_s00ed_6720->sim->f45a80();
        p->Refresh();
        g_16c7aa4_s00ed_6720->sim->f427c0();
        return false;
    }

    if (key == 0x462c656) {
        if (p->GetKey() != 0x7eaf739) {
            switch (p->mMode68) {
            case 1: case 3: case 4: case 6: case 7:
                p->DropSelection();
                break;
            default:
                break;
            }
        }
        return false;
    }

    if (key == 0x6202731 || key == 0x5d1536c) {
        if (FUN_00e00ac0_s00ed_6720())
            p->mOptions44->Enable(1);
        return false;
    }

    if (key == 0x65ff54a) {
        if (*(uint32_t*)(pb + 0x10) != 0x40464100)
            return false;
        uint32_t v = *(uint32_t*)(pb + 0x18);
        if (v != 0x396f69f5 && v != 0x709cbc09)
            return false;
        bool vis = false;
        if (p->mLayout != 0 && p->mLayout->IsVisible()) {
            vis = true;
            p->Deactivate2();
        }
        p->UpdateModes();
        p->SyncState();
        if (vis)
            p->Activate2();
        return false;
    }

    if (key == 0x72bdb11) {
        p->Refresh();
        return false;
    }

    if (key == 0x774e2dc) {
        int id  = *(int*)(pb + 8);
        uint32_t w0 = *(uint32_t*)(pb + 0x10);
        uint32_t w1 = *(uint32_t*)(pb + 0x18);
        uint32_t w2 = *(uint32_t*)(pb + 0x20);
        uint32_t args[3];
        g_16c7aa4_s00ed_6720->sim->f45970();
        args[0] = w0; args[1] = w1; args[2] = w2;
        if (id == -1)
            g_16c7aa4_s00ed_6720->sim->f40ae0(args);
        else
            g_16c7aa4_s00ed_6720->sim->f3bce0(id, args);
        g_16c7aa4_s00ed_6720->sim->f45a80();
        p->Refresh();
        g_16c7aa4_s00ed_6720->sim->f427c0();
        return false;
    }

    if (key == 0x7d8af04) {
        int v = (int)p->mSet1c;
        if (v == 0) {
            p->mPage14->GetPlayerInventory()->ToggleExpanded();
            return false;
        }
        if (v - 2 == 0) {
            p->mMenu->GetExpandedItem()->ToggleExpanded();
            return false;
        }
        return false;
    }

    if (key == 0x7ec5866) {
        if (*(int*)(pb + 8) != 0)
            return false;
        p->Select(1);
        if (FUN_00e00ac0_s00ed_6720())
            p->mMenu->OnClick2();
        if (p->mOwned84 != 0) {
            void* o = p->mOwned84;
            p->mOwned84 = 0;
            (*(void(__thiscall**)(void*))(*(uint32_t**)o)[1])(o);
        }
        return false;
    }

    if (key == 0x14051500) {
        int* r = (int*)*(void**)(pb + 8);
        g_16c7aa4_s00ed_6720->sim->f45970();
        if (r[2] == -1) {
            int n = g_16c7aa4_s00ed_6720->sim->f3bf60();
            g_16c7aa4_s00ed_6720->sim->f3bcc0(n - 1);
        }
        else {
            g_16c7aa4_s00ed_6720->sim->f3e810(r[2]);
        }
        g_16c7aa4_s00ed_6720->sim->f45a80();
        p->Refresh();
        g_16c7aa4_s00ed_6720->sim->f427c0();
        cAudioSystem* at = GetSystemAT();
        int state = at ? at->GetState() : 0;
        PlayUISound(0xf89e056, state);
        return false;
    }

    if (key == 0xcc0bf723) {
        if (p->mMode == 4 && data != 0) {
            int v = *(int*)data;
            if (v == 1 || v == 3) {
                p->mMode = 0;
            }
            else if (v == 2) {
                p->SetMode(0x7eaf738);
            }
        }
        return false;
    }

    if (key == 0xfd7a08d0) {
        p->Select(1);
        if (p->mMode == 3) {
            p->ShowCallout();
            return false;
        }
        void* where = (p != 0) ? (char*)p + 4 : 0;
        UI_CalloutMessageBox(where, &g_15ac184);
        p->mKey4c.a = g_15ac184.a;
        return false;
    }

    return false;
}

// @ 0x00ed7060
void Panel_s00ed_6720::BadgeAutoTest()
{
    cAchievements* c;
    c = AchievementsController(0x48cdfa34, 1); c->AutoTest(0x48cdfa34, 1);
    c = AchievementsController(0xabc8af1a, 1); c->AutoTest(0xabc8af1a, 1);
    c = AchievementsController(0xec310ad9, 1); c->AutoTest(0xec310ad9, 1);

    uint32_t* pi = *(uint32_t**)((char*)g_16c7aa4_s00ed_6720->sim + 0x10);
    if (pi != 0)
        (*(void(__thiscall**)(uint32_t*))(*(uint32_t**)pi)[0])(pi);

    int local_24 = 0;    // count of 0x2b978c46
    int local_c  = 0;    // count of 0x9ea3031a
    int local_1c = 0;    // count of 0x372e2c04
    int local_14 = 0;    // count of 0xccc35c46
    int local_10 = 0;    // count of 0x65672ade
    int local_28 = 0;    // count of 0x24682294
    int local_20 = 0;    // count of 0x2399be55
    bool bVar5 = true;
    bool bVar6 = true;
    bool bVar7 = true;

    uint32_t* puVar10;
    if (pi[0x2c24 / 4] < 0x3fffffff)
        puVar10 = (uint32_t*)(pi[0x2c24 / 4] * 0x238 + pi[0x2c10 / 4]);
    else
        puVar10 = (uint32_t*)pi[0x2c14 / 4];
    uint32_t* puVar2 = (uint32_t*)pi[0x2c14 / 4];

    if (puVar2 != puVar10) {
        int* iVar13  = (int*)pi[0x2bf4 / 4];
        int* piVar14 = (int*)pi[0x2bf8 / 4];
        do {
            int* piVar11 = (int*)FUN_00ed29b0(iVar13, piVar14, puVar10 + 1,
                                              (char)pi[0x2c08 / 4]);
            if (piVar11 != piVar14 && *piVar11 <= (int)puVar10[1] &&
                piVar11 != piVar11 + 0x9fa) {
                int iVar12 = piVar11[8];
                int iVar3  = piVar11[3];
                if (iVar3 == 0x2399be55) {
                    local_20++;
                }
                else if (iVar3 == 0x24682294) {
                    local_28++;
                }
                else if (iVar3 == 0x2b978c46) {
                    local_24++;
                    if (iVar12 == (int)0x9ea3031a)
                        local_c++;
                    else if (iVar12 == 0x372e2c04)
                        local_1c++;
                    else if (iVar12 == (int)0xccc35c46)
                        local_14++;
                    else if (iVar12 == 0x65672ade)
                        local_10++;
                }
            }
            do {
                uint32_t uVar4 = *puVar10;
                puVar10 += 0x8e;
                if ((uVar4 >> 0x1e & 1) != 0) break;
            } while ((int)*puVar10 < 0);
        } while (puVar2 != puVar10);
    }

    {
        int iVar13 = pi[0x2bf4 / 4];
        if (iVar13 != (int)pi[0x2bf8 / 4]) {
            int* piVar14 = (int*)(iVar13 + 0xc);
            do {
                if (AssetDataList(*piVar14, 0)) {
                    if (bVar5 && FUN_00552300(piVar14 - 1) != 0)
                        bVar5 = false;
                    if (bVar6 && Panel_Match(piVar14[-1], *piVar14, piVar14[1]) == 0)
                        bVar6 = false;
                }
                {
                    int iVar12 = piVar14[0x1b];
                    if (iVar12 != piVar14[0x1c]) {
                        do {
                            if ((*piVar14 == 0x2b978c46 || *piVar14 == 0x24682294) &&
                                (!bVar7 || *(int*)(iVar12 + 0x4ac) != 1))
                                bVar7 = false;
                            iVar12 += 0x4e0;
                        } while (iVar12 != piVar14[0x1c]);
                    }
                }
                iVar13 += 0x27e8;
                piVar14 += 0x9fa;
            } while (iVar13 != (int)pi[0x2bf8 / 4]);
        }
    }

    if (local_24 == 0) {
        c = AchievementsController(0xe55af32f, 1); c->AutoTest(0xe55af32f, 1);
    }
    if (0 < local_c)  { c = AchievementsController(0x62d8b529, local_c);  c->AutoTest(0x62d8b529, local_c); }
    if (0 < local_1c) { c = AchievementsController(0xeec38869, local_1c); c->AutoTest(0xeec38869, local_1c); }
    if (0 < local_14) { c = AchievementsController(0xaeda120e, local_14); c->AutoTest(0xaeda120e, local_14); }
    if (0 < local_10) { c = AchievementsController(0x5191a2e3, local_10); c->AutoTest(0x5191a2e3, local_10); }
    if (0 < local_1c && 0 < local_14 && 0 < local_10) {
        c = AchievementsController(0xa9d241a5, 1); c->AutoTest(0xa9d241a5, 1);
    }
    if (0 < local_28) { c = AchievementsController(0x60aec253, local_28); c->AutoTest(0x60aec253, local_28); }
    if (0 < local_20) { c = AchievementsController(0x836a79ce, local_20); c->AutoTest(0x836a79ce, local_20); }
    if (bVar5 && (0 < local_20 || 0 < local_28 || 0 < local_24)) {
        c = AchievementsController(0x280d4a31, 1); c->AutoTest(0x280d4a31, 1);
    }
    if (bVar6 && (0 < local_20 || 0 < local_28 || 0 < local_24)) {
        c = AchievementsController(0x5c324dc2, 1); c->AutoTest(0x5c324dc2, 1);
    }
    if (99 < local_20 + local_28 + local_24) {
        c = AchievementsController(0x88b15773, 1); c->AutoTest(0x88b15773, 1);
    }
    if (bVar7 && (0 < local_28 || 0 < local_24)) {
        c = AchievementsController(0x3b23cfa9, 1); c->AutoTest(0x3b23cfa9, 1);
    }
    if (g_16c7aa4_s00ed_6720->sim->f327f0()) {
        c = AchievementsController(0xe5e6d992, 1); c->AutoTest(0xe5e6d992, 1);
    }

    if (pi != 0)
        (*(void(__thiscall**)(uint32_t*))(*(uint32_t**)pi)[1])(pi);
}

// @ 0x00ed7490
void Panel_s00ed_6720::SelectionChanged(int a)
{
    (void)a;
    if (g_16c7aa4_s00ed_6720->sim->f41270(0)) {
        if (*(int*)((char*)g_16c7aa4_s00ed_6720->sim->f10 + 8) == 0)
            BadgeAutoTest();
        Select(0);
        sim_f3d8c0(g_16c7aa4_s00ed_6720->sim);
    }
    else {
        mMode = 0;
    }
}

// @ 0x00ed74f0
void PanelCallout::Dispatch(unsigned unused, unsigned selected)
{
    (void)unused;
    unsigned key = mKey;
    mKey = 0;
    if (key == 0x3cc9f2f3) {
        ((Panel*)((char*)this - 0xc))->ShowCallout();
        return;
    }

    bool is17, is1a, is1b, is19;
    is17 = false;
    is1b = false;
    is1a = false;
    switch (key)
    {
    case 0x48ee60f0: case 0x53830374: case 0x7c1ea6a4: case 0xb016b570:
        is17 = (selected == 0x5107b17);
        is19 = (selected == 0x5107b19);
        is1a = (selected == 0x5107b1a);
        break;

    case 0x811778da:
        is19 = (selected == 0x5107b17);
        is1b = (selected == 0x5107b19);
        is1a = (selected == 0x5107b1a);
        break;

    case 0x12b8ba66: case 0x9d533cda: case 0x8bf4d3f2: case 0xbe186a9a:
        is17 = (selected == 0x5107b17);
        is19 = (selected == 0x5107b18);
        is1b = (selected == 0x5107b19);
        is1a = (selected == 0x5107b1a);
        break;

    case 0x3a5ea067: case 0x5cd172a9: case 0xc6bdfccc: case 0xe6c74f99: case 0xf46fbea9:
        is19 = (selected == 0x5107b17);
        is17 = (selected == 0x5107b1a);
        break;

    case 0xc2b30789: case 0xeb3bc709: case 0xcf4c3d25: case 0xebdc80d5:
        is17 = (selected == 0x5107b17);
        is19 = (selected == 0x5107b19);
        is1b = (selected == 0x5107b1a);
        break;

    default:
        return;
    }

    cAudioSystem* at = GetSystemAT();
    int state = at ? at->GetState() : 0;
    PlayUISound(0xe76c9b4f, state);

    if (is19) { mMode = 0; return; }
    if (is17) { ((Panel*)((char*)this - 0xc))->ShowCallout(); return; }
    if (is1a) { ((Panel*)((char*)this - 0xc))->SelectionChanged(0); return; }
    if (is1b) { ((Panel*)((char*)this - 0xc))->SelectionChanged(1); }
}

// @ 0x00ed76e0
void Panel::FUN_00ed76e0(int mode)
{
    if (mode == 0)
        return;
    cSim* sim = g_16c7aa4->sim;
    if (sim == 0)
        return;
    mCallout.mMode = mode;
    int sel = mode;

    if (mode == 1) {
        if (sim->f3b920()) {
            CalloutMessageBox(&mCallout, &g_15ac19c);
            mCallout.mKey = g_15ac19c.a;
            return;
        }
        ShowCallout();
        return;
    }

    Key12 key;

    if (sim->Classify(&mode)) {
        bool high = sim->f3b950();
        int idx = sel - 2;
        key.a = 0; key.b = 0; key.c = 0;
        if (high) {
            switch (idx) {
            case 0: key = g_15ac190; break;
            case 1: key = g_15ac1cc; break;
            case 2: key = g_15ac208; break;
            case 3: key = g_15ac238; break;
            case 4: case 5: key = g_15ac268; break;
            }
        } else {
            switch (idx) {
            case 0: case 1: SelectionChanged(0); return;
            case 2: key = g_15ac1f0; break;
            case 3: key = g_15ac220; break;
            case 4: case 5: key = g_15ac250; break;
            }
        }
        CalloutMessageBox(&mCallout, &key);
        mCallout.mKey = key.a;
        return;
    }

    key.a = 0; key.b = 0; key.c = 0;
    int hint = HintForState(mode);
    switch (sel)
    {
    case 3:
        if (mode == 5) { ShowCallout(); return; }
        /* fall through */
    case 2:
        if (mode == 4 && mCallout.mpVerbTray != 0)
            mCallout.mpVerbTray->SetSelected(1);
        if (hint != 0)
            UIHints()->ShowHint(hint);
        mCallout.mMode = 0;
        return;

    case 4:
        key = g_15ac1fc;
        if (!sim->f3b920()) { ShowCallout(); return; }
        break;

    case 5:
        key = g_15ac22c;
        if (!sim->f3b920()) { ShowCallout(); return; }
        break;

    case 6: case 7:
        key = g_15ac25c;
        if (!sim->f3b920()) { ShowCallout(); return; }
        break;
    }

    if (key.a != 0) {
        cUIHint* h = UIHints()->FindByID(hint);
        cNotifyTarget* t = NotifyHost()->GetTarget();
        if (h == 0) t->SetText(g_13ec468, 0);
        else        t->SetText(h->mText.GetText(), 0);
        CalloutMessageBox(&mCallout, &key);
        mCallout.mKey = key.a;
    }
}

// @ 0x00ed7a10
bool PanelHandler::DoMessage(IWindow_s00ed_74f0* w, const Message* msg)
{
    (void)w;
    if (!g_16065f8 || g_15ad298->IsBlocked())
        return false;
    if (msg->type != 0x287259f6)
        return false;

    switch (msg->source->GetControlID())
    {
    case 0x10f366e:
        mOwned->e02e80();
        ((cMessageServer*)MessageServer_s00ed_74f0())->Post(0x101, 0, 0);
        g_16c7aa4->tutorials->f8860();
        return false;

    case 0x10f366d: {
        Panel* p = panel();
        cSim* sim = g_16c7aa4->sim;
        if (sim == 0) return false;
        p->mCallout.mMode = 7;
        int* out = (int*)&msg;           // the original reuses the dead message-pointer slot
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac268;
            else               key = g_15ac250;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac25c;
            if (!sim->f3b920()) { p->ShowCallout(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(&p->mCallout, &key);
        p->mCallout.mKey = key.a;
        return false;
    }

    case 0x2268ba4: {
        Panel* p = panel();
        cSim* sim = g_16c7aa4->sim;
        if (sim == 0) return false;
        p->mCallout.mMode = 6;
        int* out = (int*)&msg;
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac268;
            else               key = g_15ac250;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac25c;
            if (!sim->f3b920()) { p->ShowCallout(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(&p->mCallout, &key);
        p->mCallout.mKey = key.a;
        return false;
    }

    case 0x4766ff0: {
        PlayUISound(0xe76c9b4f, GetRecorderState());
        cSim* sim = g_16c7aa4->sim;
        Panel* p = panel();
        if (sim == 0) return false;
        p->mCallout.mMode = 5;
        int* out = (int*)&msg;
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac238;
            else               key = g_15ac220;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac22c;
            if (!sim->f3b920()) { p->ShowCallout(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(&p->mCallout, &key);
        p->mCallout.mKey = key.a;
        return false;
    }

    case 0x43b72d0:
        ShowSettingsWindow(GetCurrentGameMode());
        return false;

    case 0x447060a:
        ShowContextSensitiveSporeGuide();
        g_16c7aa4->tutorials->MarkDirty();
        return false;

    case 0x44ea79e:
        ((cMessageServer*)MessageServer_s00ed_74f0())->Post(0x44eaa93, 0, 0);
        mOwned->e018c0(0);
        return true;

    case 0x62025f9:
        ((cMessageServer*)MessageServer_s00ed_74f0())->Post(0x620222b, 0, 0);
        mOwned->e018c0(0);
        return true;

    case 0x6fcb630:
        g_16c7680.FUN_00ed4930();
        return false;

    case 0x6fcb638: {
        cAudioSystem* at = GetSystemAT();
        int state = at ? at->GetState() : 0;
        PlayUISound(0xcc089e57, state);
        ((cMessageServer*)MessageServer_s00ed_74f0())->Post(0x101, 0, 0);
        return false;
    }

    case 0x7104130:
        if (mActiveSet == 0) return false;
        panel()->FUN_00ed6720(0);
        return false;

    case 0x7104131: {
        if (mActiveSet == 1) return false;
        cSim* sim = g_16c7aa4->sim;
        cNode* node = sim->ff3f00();
        if (node && sim->f41420(node, 0, 0, 0)) {
            panel()->FUN_00ed6720(1);
            return false;
        }
        UIHints()->ShowHint(0xb192f625);
        return false;
    }

    case 0x7104132:
        if (mActiveSet == 2) return false;
        panel()->FUN_00ed6720(2);
        return false;

    case 0x774b060: {
        g_16c7aa4->sim->f45970();
        cSim* sim = g_16c7aa4->sim;
        sim->f3bcc0(sim->f3bf60() + 1);
        g_16c7aa4->sim->f45a80();
        PlayUISound(0xcec93ef5, GetRecorderState());
        panel()->FUN_00ed5640();
        g_16c7aa4->sim->f427c0();
        return false;
    }

    case 0x78d57d8:
        g_16c7aa4->hints->f69a0(0);
        return false;

    case 0x90439d7c:
        PlayUISound(0xe76c9b4f, GetRecorderState());
        panel()->FUN_00ed76e0(1);
        return false;

    case 0xbbbb1001:
        PlayUISound(0xe76c9b4f, GetRecorderState());
        panel()->FUN_00ed76e0(3);
        return false;

    case 0xb006ef6e:
        ((cMessageServer*)MessageServer_s00ed_74f0())->Post(0xc9d86390, 0, 0);
        return false;

    case 0xf006efa5:
        ((cMessageServer*)MessageServer_s00ed_74f0())->Post(0xc9d86391, 0, 0);
        return false;
    }
    return false;
}
