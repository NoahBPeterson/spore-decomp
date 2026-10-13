// src/game/SPEditors/SPUIFeedEdit.cpp -- migrated from slice(s) s0065ea00, s0065df30, s0065d050, s0065bf20 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIFeedEdit.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUIFeedEditAssetView.h"
#include "SP/cSPUIFeedEdit.h"

// unnamed retail callees and globals (address in the comment)
extern int g_15fa6e4;
extern void* g_vt_13fff3c;
extern void* g_vt_13fff2c;
extern void* g_vt_13ec458;
#include <intrin.h>
#include <string.h>
#include "EA/UTFWin/IWinProc.h"

// ---- items of slice s0065bf20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void*(__thiscall* FnRetP)(void*);
typedef void*(__thiscall* FnRetPi)(void*, unsigned int);
static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }
struct cSPUILayout_s0065_bf20 {
  void Shutdown(int a);  // 0x00811ad0 (cSPUILayout::Shutdown)
  void* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
};
struct cXHTMLFrameSet {
  void* GetFrame(uint32_t id);
  bool HandleLocationChange(void* win, const wchar_t* url, void* a, int b);
  bool HandleFormSubmit(void* win, void* form);
  void FUN_00997140();
};
void* GetElapsedSeconds(); // 0x00805080
void SetWindowImage(void* w, uint32_t* key, int flags);
void* FUN_0067de40();
void MessageServer_Unsub(void* h, uint32_t id, int y);   // 0x0067dcc0 (equiv t2)
extern int g_15fa6e4;
extern void* g_vt_13fff3c;
extern void* g_vt_13fff2c;
extern void* g_vt_13ec458;
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
struct CtorObj {
  void** vt; void** vt4; int m08; char pad0c[4]; void* m10; void* m14; void* m18; int m1c;
  void FUN_0065c790(void* a, void* b, void* c);
};
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
struct IRef {
  virtual void AddRef();   // slot 0 (offset 0)
  virtual void Release();  // slot 1 (offset 4)
};
struct AssetInfo {
  void* a; void* b; void* c; void* d;
  AssetInfo& operator=(const AssetInfo& other);
};
    void GetElapsedSeconds(...); // 0x00805080
// ---- items of slice s0065bf20 end

// ---- items of slice s0065d050 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* operator_new_ea(unsigned int size, const char* tag, int, int, int, int);
extern uint32_t g_1526cb0;
extern wchar_t g_str_1667bac;
extern wchar_t g_str_1667bae;
typedef void(__thiscall* FnPi)(void*, int);
struct ResourceKey { uint32_t a, b, c; };
struct cXHTMLFrameSet_s0065_d050 {
  void* GetFrame(uint32_t id);  // 0x00996d40 (cXHTMLFrameSet::GetFrame)
  void HandleLocationChange(void* win, const wchar_t* url, int a, int b);  // 0x00997730 (cXHTMLFrameSet::HandleLocationChange)
  void FUN_00997140();
};
void* MessageServer();
unsigned int __cdecl FNVHash16(const wchar_t* s, unsigned int seed, int n);
void GetURL(unsigned int id, void* out);
void SetNumberString(int value, int a, wchar_t* buf, int n);
void* CopyImpl(void* first, void* last, void* dest);
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
  void ShowAsset(int a, int b);     // 0065d570 0x0065d570
  bool TranslateToken(const wchar_t* token, void* out);  // 0065dc60 0x0065dc60
  void SetActive(bool b);    // 0065d9f0 0x0065d9f0
  bool FUN_0065dd30(unsigned int id);  // 0065dd30 wrapper
};
struct HashtableU64 {
  int count;  // +0x0c
  int* erase(int* out, int* node, int* bucket);
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
struct HashSet_s0065_df30 {
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
    HashSet_s0065_df30 mNewAssets;                // 0xd8
    HashSet_s0065_df30 mDeleteAssets;             // 0xf8
    HashSet_s0065_df30 mExistingAssets;           // 0x118
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
extern "C" void  FUN_00809db0(void* a, void* b);
extern "C" void  FUN_00996280(void* self, int a, int b, int c, int d);  // thiscall via struct
extern "C" void  FUN_0065d490();
extern "C" void* HashFind64(uint64_t* out, uint64_t* key);       // 0x553510
extern "C" void  HashDoInsert(uint64_t* a, uint64_t* b, int c);  // 0x553750
struct AssetInfo_s0065_ea00 { uint64_t mnAssetID; uint32_t mnType; void* mpImage; };
struct AssetVec_s0065_ea00 {
    AssetInfo_s0065_ea00* begin; AssetInfo_s0065_ea00* end; AssetInfo_s0065_ea00* cap;
    AssetInfo_s0065_ea00* DoInsertValue(AssetInfo_s0065_ea00* pos, AssetInfo_s0065_ea00* value);
    AssetInfo_s0065_ea00* erase(AssetInfo_s0065_ea00* first, AssetInfo_s0065_ea00* last);
    void push_back();  // 0x0065e6d0 (AssetVec::push_back)
};
struct HashSet { char pad[0xc]; int count; void DoFreeNodes(void*, void*); };
struct cSPUILayout_s0065_ea00 {
    void* FindWindowByID(uint32_t id, int recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void* Init(const void* key, int a, int id);  // 0x008120d0 (cSPUILayout::Init)
    void  SetParentWin(void* parent, int a, int id);  // 0x008121b0 (cSPUILayout::SetParentWin)
    void  SetReloadCallback(void* fn, void* self);  // 0x00810090 (cSPUILayout::SetReloadCallback)
};
struct TextSlot { void Assign(void* p); };
struct LayoutCtor { void* Create(); };
struct ComObj {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
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
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
    virtual void m28(); virtual void m29(); virtual void m30();
    virtual void Slot7c(int, int);          // 0x7c (index 31)
    virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
    virtual void Slot90();                  // 0x90 (index 36)
    virtual void m37(); virtual void m38(); virtual void m39(); virtual void m40();
    virtual void m41(); virtual void m42(); virtual void m43(); virtual void m44();
    virtual void m45(); virtual void m46(); virtual void m47(); virtual void m48();
    virtual void m49(); virtual void m50(); virtual void m51(); virtual void m52();
    virtual void m53(); virtual void m54(); virtual void m55(); virtual void m56();
    virtual void m57(); virtual void m58(); virtual void m59();
    virtual void* SlotF0(uint32_t id, int b);  // 0xf0 (index 60)
    virtual void m61(); virtual void m62(); virtual void m63(); virtual void m64();
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
    HashSet mNewAssets;                // 0xd8
    HashSet mDeleteAssets;             // 0xf8
    HashSet mExistingAssets;           // 0x118
    char  pad138[0x11];                // 0x138..0x148
    char  mbTransactionActive;         // 0x149
    char  mbNameSet;                   // 0x14a

    void DoMessage(int msg, void* data);  // 0x0065ea00 (cSPUIFeedEdit::DoMessage)
    void UnloadLayout();
    bool Populate();
    bool RemoveAsset(int a, int b);
    void ResetPanel();
    void LoadLayout();  // 0x0065e8d0 (cSPUIFeedEdit::LoadLayout)
    void Init(void* parent);  // 0x0065f700 (cSPUIFeedEdit::Init)
    void InitLayout();
    void LoadFilter(int param, bool b);
    char AddAsset(int a, int b, int c, void* img);
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
extern "C" void* SP_MessageServer();
// ---- items of slice s0065ea00 end

// @ 0x0065c490
void cSPUIFeedEditAssetView::GetThumbnailBackdrop(uint32_t* out, unsigned int id) const
{
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








// @ 0x0065c6f0
unsigned int SP::cSPUIFeedEditAssetView::GetEventMask() const
{
  return (uint32_t)(*(int*)((char*)this + 0x44)) | 0xfffffffd;
}








// @ 0x0065c790
void CtorObj::FUN_0065c790(void* a, void* b, void* c)
{
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
void SP::cSPUIFeedEditAssetView::SetMode(SP::cSPUIFeedEditAssetView::Mode mode)
{
  char* p = (char*)this;
  if (mode == 2) {
    *(float*)(p + 0x48) = (float)(int)((void* (__cdecl *)(void))GetElapsedSeconds)();
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
bool SP::cSPUIFeedEditAssetView::OnTick(EA::UTFWin::IWindow * win)
{
  char* p = (char*)this;
  if (win == *(void**)(p + 0x14) && *(int*)(p + 0x30) == 2 && 0.0f < *(float*)(p + 0x48)) {
    float now = (float)(int)((void* (__cdecl *)(void))GetElapsedSeconds)();
    if (0.35f < now - *(float*)(p + 0x48)) {
      SetMode((SP::cSPUIFeedEditAssetView::Mode)1);
      if (*(void**)(p + 0x14) && *(int*)(p + 0x44)) {
        *(int*)(p + 0x44) = 0;
        (*(FnPv)Vslot(*(void**)(p + 0x14), 0x104))((void*)*(void**)(p + 0x14), this);
      }
    }
  }
  return false;
}








// @ 0x0065ca10
void SP::cSPUIFeedEdit::Shutdown()
{
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
  char* p = (char*)this;
  int count = (*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4;
  int* q = *(int**)(p + 0xc4);
  for (int i = 0; i < count; ++i, q += 4) {
    if (q[0] == a && q[1] == b)
      return i;
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
void cSPUIFeedEditAssetView::FUN_0065cf30(int, int, int, int* asset)
{
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
void cSPUIFeedEdit_s0065_d050::ShowAsset(int a, int b)
{
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
      tmp[0] = &g_str_1667bac;
      tmp[1] = &g_str_1667bac;
      tmp[2] = &g_str_1667bae;
      *(int*)(p + 0x8c) = 0;
      GetURL(0x5908ef2, tmp);
      ((cXHTMLFrameSet_s0065_d050*)(p + 0x18))->HandleLocationChange(*(void**)(p + 0x84), tmp[0], 0, 0);
    }
  }
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
            *p = *value;
            if (p->mpImage) (*(FnP)Vslot(p->mpImage, 0))(p->mpImage);
        }
        AssetInfo_s0065_df30* p2 = UninitCopy(position, end, p + 1);
        AssignRange(position, end, p + 1);
        if (begin && (begin[-1].mnAssetID != 0)) EASTL_allocator_deallocate(begin);
        begin = buf;
        end = p2;
        cap = buf + nc;
    }
    return position;
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
        view->mnIndex = 0xffffffff; view->mTickMask = 0xffffffff; view->mfBlinkStart = 0.0f;
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
            if (v) { v->mpImage = 0; v->mnAssetID = (uint64_t)-1; v->mnIndex = 0xffffffff; v->mTickMask = 0xffffffff; v->mfBlinkStart = 0.0f; }
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
    ((cSPUIFeedEdit_s0065_ea00*)s)->InitLayout();
    *(char*)(s + 0x91) = 1;
    void* handler = s + 0x10;
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x3b27023);
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x1dd7bda9);
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x3cdd5f9);
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x49a3777);
}
