// src/game/SPEditors/SPUIFeedEdit.cpp -- migrated from slice(s) s00ed74f0, s0065ea00, s0065df30, s0065d050, s0065bf20 by tools/migrate/rewrite.py
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
extern Key12    g_15ac220;   // 0x015ac220
extern Key12    g_15ac22c;   // 0x015ac22c
extern Key12    g_15ac238;   // 0x015ac238
extern Key12    g_15ac250;   // 0x015ac250
extern Key12    g_15ac25c;   // 0x015ac25c
extern Key12    g_15ac268;   // 0x015ac268
struct IWindow_s00ed_74f0 {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6();
    virtual uint32_t GetControlID();                 // +0x1c
};
struct Message {
    IWindow_s00ed_74f0* source;                                 // +0
    uint32_t pad4;
    uint32_t type;                                   // +8
};
struct cMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post(uint32_t id, int a, int b);    // +0x14
};
struct cAudioSystem {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual int  GetState();                         // +0x20
};
struct cUIGate {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual bool IsBlocked();                        // +0x38
};
extern cUIGate* g_15ad298;                           // 0x015ad298
struct cNotifyTarget {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void SetText(const wchar_t* text, int flags);   // +0x34
};
struct cNotifyHost {                                 // 0x0067de40 singleton
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
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
struct Panel {                                       // primary object; the handler is its base at +8
    char pad0[0xc];
    char mCallout[0x48];                             // +0x0c
    int  mCalloutKey;                                // +0x54
    int  mMode;                                      // +0x58
    void FUN_00ed5910();                             // 0x00ed5910
    void FUN_00ed5640();                             // 0x00ed5640
    void FUN_00ed6720(int i);                        // 0x00ed6720
    void FUN_00ed76e0(int i);                        // 0x00ed76e0
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
        ((cMessageServer*)MessageServer())->Post(0x101, 0, 0);
        g_16c7aa4->tutorials->f8860();
        return false;

    case 0x10f366d: {
        Panel* p = panel();
        cSim* sim = g_16c7aa4->sim;
        if (sim == 0) return false;
        p->mMode = 7;
        int* out = (int*)&msg;           // the original reuses the dead message-pointer slot
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac268;
            else               key = g_15ac250;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac25c;
            if (!sim->f3b920()) { p->FUN_00ed5910(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(p->mCallout, &key);
        p->mCalloutKey = key.a;
        return false;
    }

    case 0x2268ba4: {
        Panel* p = panel();
        cSim* sim = g_16c7aa4->sim;
        if (sim == 0) return false;
        p->mMode = 6;
        int* out = (int*)&msg;
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac268;
            else               key = g_15ac250;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac25c;
            if (!sim->f3b920()) { p->FUN_00ed5910(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(p->mCallout, &key);
        p->mCalloutKey = key.a;
        return false;
    }

    case 0x4766ff0: {
        PlayUISound(0xe76c9b4f, GetRecorderState());
        cSim* sim = g_16c7aa4->sim;
        Panel* p = panel();
        if (sim == 0) return false;
        p->mMode = 5;
        int* out = (int*)&msg;
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac238;
            else               key = g_15ac220;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac22c;
            if (!sim->f3b920()) { p->FUN_00ed5910(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(p->mCallout, &key);
        p->mCalloutKey = key.a;
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
        ((cMessageServer*)MessageServer())->Post(0x44eaa93, 0, 0);
        mOwned->e018c0(0);
        return true;

    case 0x62025f9:
        ((cMessageServer*)MessageServer())->Post(0x620222b, 0, 0);
        mOwned->e018c0(0);
        return true;

    case 0x6fcb630:
        g_16c7680.FUN_00ed4930();
        return false;

    case 0x6fcb638: {
        cAudioSystem* at = GetSystemAT();
        int state = at ? at->GetState() : 0;
        PlayUISound(0xcc089e57, state);
        ((cMessageServer*)MessageServer())->Post(0x101, 0, 0);
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
        ((cMessageServer*)MessageServer())->Post(0xc9d86390, 0, 0);
        return false;

    case 0xf006efa5:
        ((cMessageServer*)MessageServer())->Post(0xc9d86391, 0, 0);
        return false;
    }
    return false;
}
