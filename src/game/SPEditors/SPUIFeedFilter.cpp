// src/game/SPEditors/SPUIFeedFilter.cpp -- migrated from slice(s) s00661d10, s00660dd0, s0065f970, s0065ea00 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIFeedFilter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUIFeedEdit.h"
#include "SP/cSPUIFeedEditAssetView.h"
#include <intrin.h>
#include "cSPUILayout.h"
#include "SP/cSPUIFeedFilter.h"
#include "SP/cSPEditorVerbIconTray.h"
#include "EA/Messaging/IHandler.h"

// ---- items of slice s0065ea00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }
struct IWindow {
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
struct ModeViewGetter { char* Get(bool b); };
struct WindowSet4 {
    void* p0; void* p4; IWindow* pParent; IWindow* pC; IWindow* p10; IWindow* p14; IWindow* p18;
    void Set(IWindow* parent);
};
// ---- items of slice s0065ea00 end

// ---- items of slice s0065f970 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0
void  __cdecl EASTL_allocator_deallocate(void* p);                                                                                 // 0x00f47380
#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct IWindow_s0065_f970 {
    virtual void      s00();                       // +0x00
    virtual int       Release();                   // +0x04
    virtual void      s02();                       // +0x08
    virtual IWindow_s0065_f970*  FindWindow(uint32_t id);     // +0x0c
    virtual IWindow_s0065_f970*  GetSomething();              // +0x10
    virtual void      s05();                       // +0x14
    virtual void      s06();                       // +0x18
    virtual void      s07();                       // +0x1c
    virtual void      s08();                       // +0x20
    virtual void      s09();                       // +0x24
    virtual uint32_t  GetFlags();                  // +0x28
    virtual void      s11();                       // +0x2c
    virtual void      s12();                       // +0x30
    virtual void      s13();                       // +0x34
    virtual void      s14();                       // +0x38
    virtual void      s15();                       // +0x3c
    virtual void      s16();                       // +0x40
    virtual void      s17();                       // +0x44
    virtual void      s18();                       // +0x48
    virtual void      s19();                       // +0x4c
    virtual void      s20();                       // +0x50
    virtual void      s21();                       // +0x54
    virtual void      s22();                       // +0x58
    virtual void      s23();                       // +0x5c
    virtual void      s24();                       // +0x60
    virtual void      SetLocation(float, float);   // +0x64
    virtual void      s26();                       // +0x68
    virtual void      s27();                       // +0x6c
    virtual void      s28();                       // +0x70
    virtual void      s29();                       // +0x74
    virtual void      s30();                       // +0x78
    virtual void      SetFlag(int, bool);          // +0x7c
    virtual void      s32();                       // +0x80
    virtual void      s33();                       // +0x84
    virtual void      s34();                       // +0x88
    virtual void      s35();                       // +0x8c
    virtual void      s36();                       // +0x90
    virtual void      s37();                       // +0x94
    virtual void      s38();                       // +0x98
    virtual void      s39();                       // +0x9c
    virtual void      s40();                       // +0xa0
    virtual void      s41();                       // +0xa4
    virtual void      s42();                       // +0xa8
    virtual void      s43();                       // +0xac
    virtual void      s44();                       // +0xb0
    virtual void      s45();                       // +0xb4
    virtual void      s46();                       // +0xb8
    virtual void      s47();                       // +0xbc
    virtual void      s48();                       // +0xc0
    virtual void      s49();                       // +0xc4
    virtual void      s50();                       // +0xc8
    virtual void      s51();                       // +0xcc
    virtual void      s52();                       // +0xd0
    virtual void      s53();                       // +0xd4
    virtual void      s54();                       // +0xd8
    virtual void      s55();                       // +0xdc
    virtual void      s56(IWindow_s0065_f970* w);             // +0xe0
    virtual void      s57();                       // +0xe4
    virtual void      s58();                       // +0xe8
    virtual void      s59();                       // +0xec
    virtual IWindow_s0065_f970*  FindWindowByID(uint32_t id, bool recurse);  // +0xf0
    virtual void      s61();                       // +0xf4
    virtual void      s62();                       // +0xf8
    virtual void      s63();                       // +0xfc
    virtual void      s64();                       // +0x100
    virtual void      SetReloadCallback(void* p);  // +0x104
    virtual void      AttachProc(void* p);         // +0x108
};
struct IButton {
    virtual void      b00();
    virtual int       b01();
    virtual void      b02();
    virtual void      b03();
    virtual void      b04();
    virtual void      b05();
    virtual void      b06();
    virtual void      b07();
    virtual void      b08();
    virtual void      b09();
    virtual void      SetStateFlag(int flag, bool v);   // +0x28
};
struct cSPUILayout_s0065_f970 {
    virtual void s0();
    virtual void s1();
    virtual int  Release();                                       // +0x08
    void Shutdown(bool);                                          // 0x00811ad0
    IWindow_s0065_f970* FindWindowByID(uint32_t id, bool recurse);           // 0x008105b0
    char pad[0x18 - 4];
};
void __cdecl EA_RemoveHandler(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00571db0
IWindow_s0065_f970* __cdecl SPUIHelpers_SetWindowAreaToParent(IWindow_s0065_f970* w);                          // 0x00806bf0
struct FeedFilterA {
    int m0;              // +0x00
    int m4;              // +0x04
    IWindow_s0065_f970* m8;         // +0x08
    IWindow_s0065_f970* mWin[4];    // +0x0c
    void Update4();      // 0x0065f970
    ~FeedFilterA();      // 0x0065f9e0
};
struct FeedFilterB {
    char pad00[0x64];
    cSPUILayout_s0065_f970* mLayout;      // +0x64
    char pad68[4];
    IWindow_s0065_f970* mWin6c;           // +0x6c
    IWindow_s0065_f970* mWin70;           // +0x70
    IWindow_s0065_f970* mWin74;           // +0x74
    IWindow_s0065_f970* mWin78;           // +0x78
    void* mHandler;            // +0x7c
    uint32_t mA80;             // +0x80
    uint32_t mA84;             // +0x84
    uint32_t mA88;             // +0x88
    uint32_t mA8c;             // +0x8c
    void Shutdown();
};
struct RC {
    virtual int AddRef();      // +0x00
    virtual int Release();     // +0x04
};
struct RC4 {
    virtual void s0();
    virtual int  AddRef4();    // +0x04
};
struct Node14 {
    uint32_t a, b, c;
    RC4* d;
    uint32_t e;
};
struct AreaRec {
    uint32_t m0;                 // +0x00
    RC* mRef;                    // +0x04
    uint8_t m8;                  // +0x08
    uint8_t m9;                  // +0x09
    char pad0a[2];
    float f0c, f10, f14, f18;    // +0x0c
    uint32_t m1c;                // +0x1c
    uint32_t m20;                // +0x20
    AreaRec(const AreaRec& o);
    AreaRec* AssignChecked(const uint32_t* head, const void* inner);   // 0x006603d0
};
struct AreaInner {
    RC* ref;                 // +0x00
    uint8_t b4;              // +0x04
    uint8_t b5;              // +0x05
    char pad6[2];
    float f8, f0c, f10, f14;
    uint32_t m18, m1c;
};
struct Key {
    uint32_t mInstance;    // +0x00
    uint32_t mType;        // +0x04
    uint32_t mGroup;       // +0x08
};
Key*  __cdecl KeyLowerBound(Key* first, Key* last, const Key* key);   // 0x00660430
bool  __cdecl KeyContains(Key* first, Key* last, const Key* key);     // 0x00660650
struct KeyVec {
    Key* mBegin;    // +0x00
    Key* mEnd;      // +0x04
    Key* mCap;      // +0x08
    KeyVec& operator=(const KeyVec& o);
};
void  __cdecl CopyOverlap(Key* first, Key* last, Key* dest);   // 0x00b84c80
void  __cdecl UninitCopyPtr(void** out, void* first, void* last, void* dest, void* extra);  // 0x00512050
Key*  __cdecl KeyVecAlloc(uint32_t n, Key* first, Key* last);  // 0x006604b0
struct FeedEntry {
    uint32_t m0;             // +0x00
    bool     m4;             // +0x04
    char     pad05[3];
    KeyVec   v08;            // +0x08
    char     pad14[8];
    bool     m1c;            // +0x1c
    char     pad1d[3];
    KeyVec   v20;            // +0x20
    char     pad2c[8];
};
struct KeyProvider {
    virtual void     k00(); virtual void k01(); virtual void k02(); virtual void k03();
    virtual void     k04(); virtual void k05(); virtual void k06(); virtual void k07();
    virtual uint32_t k08();                       // +0x20
    virtual uint32_t k09();                       // +0x24
    virtual void     k10(); virtual void k11(); virtual void k12(); virtual void k13();
    virtual void     k14();
    virtual uint32_t k15();                       // +0x3c
    virtual uint32_t k16();                       // +0x40
};
struct FeedOwner {
    char pad00[0x1c];
    KeyVec mOther;    // +0x1c
    char pad28[8];
    KeyVec mMain;     // +0x30
    bool Matches(KeyProvider* p, char useOther);
};
struct FeedTreeNode {
    char pad00[0x14];
    IWindow_s0065_f970* mWin;     // +0x14
};
void* __cdecl RBTreeIncrement(void* n);   // 0x00921580
struct FeedFilterC {
    char pad[0xa0];
    FeedTreeNode* mEnd;    // +0xa0
    FeedTreeNode* mBegin;  // +0xa4
    void LockFilterUI(bool locked);
};
struct TreeStub { void dtorSubtree(FeedTreeNode* root); };
struct FeedFilterD {
    char pad[0xa0];
    FeedTreeNode* mEnd;    // +0xa0
    FeedTreeNode* mBegin;  // +0xa4
    FeedTreeNode* mRoot;   // +0xa8
    bool mAc;              // +0xac
    char padAd[3];
    uint32_t mB0;          // +0xb0
    void Clear();
};
// ---- items of slice s0065f970 end

// ---- items of slice s00660dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00d0c930(void* p);
extern "C" void  FUN_00646d70(void* first, void* last);
extern "C" void* SP_PropertyManager(); // 0x0067de30
extern "C" void  FUN_0066a5e0(void* self, int a, int b);
extern "C" void* FUN_00660720(void* a, void* b);
extern "C" void  EA_Messaging_RemoveHandler(void* a, void* b, void* c, void* d, void* e);
extern "C" void  DoCopyKeys(void* first, void* last, void* dest);
extern "C" void  Fun0066_0ad0(void* a, void* b, void* c, void* d, void* e);   // 0x00660ad0 (equiv t1)
extern "C" void* Fun0066_0b30(void* a, void* b, void* c);   // 0x00660b30 (equiv t1)
extern "C" void  Fun0066_0510(void* a, void* b, void* c);   // 0x00660510 (equiv t1)
extern "C" void* Fun0066_0d70(void* a, void* b, void* c);   // 0x00660d70 (equiv t1)
extern "C" void* Fun0066_0fc0(unsigned n, void* a, void* b);
extern "C" void* FUN_006603d0(void* key, void* out);
extern "C" char  FUN_006a12a0(void* obj, int k, void* out);
struct Blob14 { uint8_t x[0x14]; void Assign(Blob14* src); void FUN_006606a0(Blob14* src); };
struct E34 {
    uint32_t a;          // 0x00
    uint8_t  b;          // 0x04
    char     pad5[3];
    Blob14   c;          // 0x08
    uint8_t  d;          // 0x1c
    char     pad1d[3];
    Blob14   e;          // 0x20
};
struct Vec34 { E34* begin; E34* end; E34* cap; void FUN_00661670(); void FUN_00661700(); };
struct MapRoot34 { void* FUN_006612b0(void* key); };
struct SubD8 { void FUN_0065f9e0(); };
struct cSPUIFeedFilter {
    void* vt;                          // 0x00
    char  pad04[0xc];                  // 0x04
    char  mIsVisible;                  // 0x10
    char  pad11[3];
    void* mpLayout;                    // 0x14
    void* mpWinParent;                 // 0x18
    Vec34 mV0;                         // 0x1c
    char  pad28[8];                    // 0x28
    Vec34 mV1;                         // 0x30
    char  pad3c[8];                    // 0x3c
    char  m44[0x20];                   // 0x44
    void* mp64;                        // 0x64
    void* mp68;                        // 0x68
    void* mp6c;                        // 0x6c
    void* mp70;                        // 0x70
    void* mp74;                        // 0x74
    void* mp78;                        // 0x78
    void* mp7c;                        // 0x7c
    void* mp80;                        // 0x80
    void* mp84;                        // 0x84
    void* mp88;                        // 0x88
    void* mp8c;                        // 0x8c
    float mf90;                        // 0x90
    float mf94;                        // 0x94
    float mf98;                        // 0x98
    char  m9c[0x1c];                   // 0x9c..0xb7
    Vec34 mVb8;                        // 0xb8
    void* mC4;                         // 0xc4
    float mfC8;                        // 0xc8
    float mfCc;                        // 0xcc
    void* mD0;                         // 0xd0
    void* mD4;                         // 0xd4
    char  mD8[0x1c];                   // 0xd8..0xf3
    Vec34 mVf4;                        // 0xf4
    void* m100;                        // 0x100
    void* m104;                        // 0x104
    char  mb108;                       // 0x108
    char  pad109[3];
    char  mb10c;                       // 0x10c
    void* ctor();
    void dtor();
};
struct Key3 { uint32_t a, b, c; };
namespace __equiv_ann1 {
struct Blob14 {
    void Assign();   // 0x006606a0 (equiv t3)
};
}
// ---- items of slice s00660dd0 end

// ---- items of slice s00661d10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IWindow_s0066_1d10 {
    virtual void      s00(); virtual int Release();
    virtual void      s02(); virtual IWindow_s0066_1d10* FindWindow(uint32_t id);
    virtual IWindow_s0066_1d10*  GetSomething(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void      s08(); virtual void s09(); virtual uint32_t GetFlags(); virtual void s11();
    virtual void      s12(); virtual float* GetArea(); virtual void s14(); virtual void s15();
    virtual void      s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void      s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void      s24(); virtual void SetLocation(float, float); virtual void s26();
    virtual void      s27(); virtual void s28(); virtual void s29(); virtual void s30();
    virtual void      SetFlag(int, bool); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void      s35(); virtual void s36(); virtual void s37(); virtual void s38();
    virtual void      s39(); virtual void s40(); virtual void s41(); virtual void s42();
    virtual void      s43(); virtual void s44(); virtual void s45(); virtual void s46();
    virtual void      s47(); virtual void s48(); virtual void s49(); virtual void s50();
    virtual void      s51(); virtual void s52(); virtual void s53(); virtual void s54();
    virtual void      s55(); virtual void s56(IWindow_s0066_1d10*); virtual void s57(); virtual void s58();
    virtual void      s59(); virtual IWindow_s0066_1d10* FindWindowByID(uint32_t id, bool recurse);
    virtual void      s61(); virtual void s62(); virtual void s63(); virtual void s64();
    virtual void      SetReloadCallback(void*); virtual void AttachProc(void*);
};
struct cSPUILayout_s0066_1d10 {
    virtual void s0(); virtual void s1(); virtual int Release();
    void Shutdown(bool);                                   // 0x00811ad0
    IWindow_s0066_1d10* FindWindowByID(uint32_t, bool);               // 0x008105b0
    void Init(const uint32_t* area, int a, uint32_t key);  // 0x008120d0
    void SetParentWin(void* win, int a, uint32_t key);     // 0x008121b0
    void SetReloadCallback(void* fn, void* self);          // 0x00810090
    cSPUILayout_s0066_1d10* Construct();                              // 0x00810000
    char pad[0x18 - 4];
};
struct AudioAT {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void* Slot20();                                // +0x20
};
struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void PostMessage(uint32_t id, uint32_t a, uint32_t b);   // +0x14
};
IMessageServer* __cdecl SP_MessageServer();                                              // 0x0067dcc0
void* __cdecl SP_GetSystemAT();                                                          // 0x00a206f0
void  __cdecl SP_KillSetiEffects(uint32_t id, void* at);                                 // 0x00435ed0
struct ElemA { int Method(void* arg); };   // 0x00664640
struct Obj50 { virtual int AddRef(); virtual int Release(); void SetActive(bool); };  // 0x006673a0
struct Obj34 { char pad[0x20]; void* m20; };
struct FeedTreeNode_s0066_1d10 {
    char pad00[0x14];
    IWindow_s0066_1d10* mWin;     // +0x14
    bool b18;          // +0x18
    bool b19;          // +0x19
};
struct FeedList {
    char      pad00[0x10];
    bool      m10;                 // +0x10
    bool      m11;                 // +0x11
    char      pad12;
    bool      m13;                 // +0x13
    int       m14;                 // +0x14
    int       m18;                 // +0x18
    float     m1c;                 // +0x1c
    cSPUILayout_s0066_1d10* mLayout20;        // +0x20
    IWindow_s0066_1d10*  m24;                 // +0x24
    IWindow_s0066_1d10*  m28;                 // +0x28
    char      pad2c[8];
    Obj34*    m34;                 // +0x34
    ElemA**   m38;                 // +0x38 (vector begin)
    ElemA**   m3c;                 // +0x3c (vector end)
    char      pad40[0x10];
    Obj50*    m50;                 // +0x50
    void*     m54;                 // +0x54
    uint32_t  m58, m5c, m60;       // +0x58
    union { uint32_t m64; cSPUILayout_s0066_1d10* mLayout64; };  // +0x64
    IWindow_s0066_1d10*  m68;                 // +0x68
    IWindow_s0066_1d10*  m6c;                 // +0x6c
    IWindow_s0066_1d10*  m70;                 // +0x70
    IWindow_s0066_1d10*  m74;                 // +0x74
    IWindow_s0066_1d10*  m78;                 // +0x78
    char      pad7c[0x14];
    float     m90, m94, m98;       // +0x90
    char      pad9c[4];
    FeedTreeNode_s0066_1d10* mEnd;            // +0xa0
    FeedTreeNode_s0066_1d10* mBegin;          // +0xa4
    char      padA8[0x10];
    char      mHash[0x20];         // +0xb8 hashtable<Key, cSPUILayout*>
    int       md8, mdc;            // +0xd8 depth

    // defined in this slice
    void  FUN_006624d0(int param);
    void  FUN_00662540();
    void  FUN_006625f0(int* param2, void* param3);
    void  FUN_00662750(int param2, int param3, char param4);
    bool  FUN_006627d0(void* a, int* msg);
    void  FUN_006628d0();
    void  FUN_00662920(bool v);
    int   FUN_00662960(void* arg);
    int   FUN_006629a0(void* arg);
    void  FUN_006629e0();
    void* FUN_00662a20(uint32_t idx);
    void* FUN_00662a40(int id);
    void  FUN_00662a90(void* arg);
    void  FUN_00662ad0();
    void  FUN_00662b40(void* obj);
    void  FUN_00662c10(void* w);
    void  FUN_00662c70(void* obj);

    // external callees (ecx = this)
    void  CreateFilterButtons(int param, int a, int b, int* out);  // 0x00661d10
    void  DoMessage();                                             // 0x0065fd30
    void  GetSupportedFilterTypes(int param);                      // 0x006600c0
    bool  FUN_00661a10(int param);                                 // 0x00661a10
    bool  FUN_00661c00(int param, int b);                          // 0x00661c00
    bool  FUN_00661b10(int param);                                 // 0x00661b10
};
struct CFVec2 { float x, y; };
struct CFKey { uint32_t a, b, c; };
struct CFWin {                                   // UTFWin window (slots by index)
    virtual void v0(); virtual int Release();
    virtual void v2(); virtual void v3();
    virtual CFWin* GetInner();                   // 4  +0x10
    virtual void v5(); virtual void v6();
    virtual int GetTypeId();                     // 7  +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual float* GetArea();                    // 14 +0x38
    virtual void v15(); virtual void v16();
    virtual void SetCmd(uint32_t id);            // 17 +0x44
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void SetLocation(float x, float y);  // 28 +0x70
    virtual void SetSize(float w, float h);      // 29 +0x74
    virtual void v30(); virtual void v31();
    virtual void SetCaption(const wchar_t* t);   // 32 +0x80
    virtual void SetFlag2(uint32_t id);          // 33 +0x84
    virtual void v34(); virtual void v35();
    virtual void Finish();                       // 36 +0x90
    virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
    virtual uint32_t GetHandle();                // 42 +0xa8
    virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
    virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
    virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60();
    virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
    virtual void AddProc(void* p);               // 65 +0x104
};
struct CFLayout {
    virtual void s0(); virtual void s1(); virtual int Release();
    CFLayout* Construct();                               // 0x00810000
    void Init(const CFKey* k, int a, uint32_t key);      // 0x008120d0
    void SetParentWin(CFWin* w, int a, uint32_t key);    // 0x008121b0
    void SetVisibility(int v);                           // 0x00810590
    CFWin* FindWindowByID(uint32_t id, bool recurse);    // 0x008105b0
    char pad[0x14];
};
struct CFWinRef {
    CFWin* p;
    void Assign(CFWin* w);   // 0x00b5f950
};
struct CFLayoutRef {
    CFLayout* p;
    void Assign(const CFLayoutRef* r);   // 0x005766e0
    void Ctor(CFLayout* l);        // 0x00572620
};
struct CFTooltipRef {
    void* p;
    void Ctor(void* t);   // 0x00572660
};
struct CFString {
    char b[0x10];
    void Ctor();                   // 0x006b5060
    const wchar_t* GetText();      // 0x006b55c0
    void Dtor();                   // 0x006b5240
};
struct CFPlist { virtual void a0(); virtual void Release(); };
struct CFPropMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void GetPropertyList(int key, uint32_t id, CFPlist** out); };   // 11 +0x2c
struct CFValue {                                 // map value (tree node + 0x14)
    CFWinRef win; bool b4; bool b5; char pad6[2];
    float x, y; float rx, ry; uint32_t k18, k1c;
};
struct CFMap {
    void** find(void* out, const int* key);   // 0x00e5c780
    CFValue* Get(const int* key);             // 0x006612b0
};
struct CFHash {
    void** find(void* out, const CFKey* key);       // 0x00833840
    CFLayoutRef* Index(const CFKey* k);             // 0x00660c10
};
void*     __cdecl CF_AssetBrowser();                                                // 0x00401030
float     __cdecl CF_GetPropertyFloat(void* obj, uint32_t id, float def);           // 0x004e1c70
CFPropMgr* __cdecl CF_PropertyManager();                                            // 0x0067de30
bool      __cdecl CF_GetPropVec2(CFPlist* pl, uint32_t id, float* a, float* b);     // 0x006a0ae0
bool      __cdecl CF_GetPropArray(CFPlist* pl, uint32_t id, int* count, CFKey** arr);    // 0x006a0ae0
void      __cdecl CF_GetPropertyAsKey(CFPlist* pl, uint32_t id, CFKey* out);        // 0x006a1250
bool      __cdecl CF_GetPropertyAsText(CFPlist* pl, uint32_t id, CFString* out);    // 0x006a1360
void      __cdecl CF_GetPropertyAsKeyInstance(CFPlist* pl, uint32_t id, uint32_t* out);  // 0x006a12a0
CFWin*    __cdecl CF_ButtonFromHandle(uint32_t h, int t, int key, CFVec2 pos, CFWin* parent);   // 0x00806780
CFWin*    __cdecl CF_CreateButtonA(uint32_t a, int t, int key, CFVec2 pos, CFWin* parent);  // 0x00808930
CFWin*    __cdecl CF_CreateButtonB(CFKey* k, int t, int key, CFVec2 pos, CFWin* parent);    // 0x00807a50
CFWin*    __cdecl CF_InterfaceCast(CFWinRef* r);                                    // 0x005c2570
void*     __cdecl CF_AllocTooltipHeap();                                            // 0x009512c0
void*     __cdecl CF_AllocTooltip(int size, int align, const char* name, void* heap);  // 0x009512d0
struct CFTooltip {
    CFTooltip* Ctor(const wchar_t* name, uint32_t id, const wchar_t* text, float* off, int a, const void* b, int c);  // 0x00835e30
};
void* __cdecl CF_OperatorNew(uint32_t size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
// ---- items of slice s00661d10 end

// @ 0x0065f810
char* ModeViewGetter::Get(bool b)
{
    char* r = (char*)this + 0x30;
    if (!b) r = (char*)this + 0x1c;
    return r;
}




// @ 0x0065f820
void WindowSet4::Set(IWindow* parent)
{
    p0 = 0;
    p4 = 0;
    IWindow* old = pParent;
    if (parent != old) {
        if (parent) (*(FnP)Vslot(parent, 0))(parent);
        pParent = parent;
        if (old) (*(FnP)Vslot(old, 4))(old);
    }
    if (pParent) {
        IWindow* a = (IWindow*)pParent->SlotF0(0xda7f4890, 1);
        IWindow* o1 = pC;
        if (a != o1) { if (a) (*(FnP)Vslot(a, 0))(a); pC = a; if (o1) (*(FnP)Vslot(o1, 4))(o1); }
        IWindow* b = (IWindow*)pParent->SlotF0(0xda7f4891, 1);
        IWindow* o2 = p10;
        if (b != o2) { if (b) (*(FnP)Vslot(b, 0))(b); p10 = b; if (o2) (*(FnP)Vslot(o2, 4))(o2); }
        IWindow* c = (IWindow*)pParent->SlotF0(0xda7f4892, 1);
        IWindow* o3 = p14;
        if (c != o3) { if (c) (*(FnP)Vslot(c, 0))(c); p14 = c; if (o3) (*(FnP)Vslot(o3, 4))(o3); }
        IWindow* d = (IWindow*)pParent->SlotF0(0xda7f4893, 1);
        IWindow* o4 = p18;
        if (d != o4) { if (d) (*(FnP)Vslot(d, 0))(d); p18 = d; if (o4) (*(FnP)Vslot(o4, 4))(o4); }
        IWindow** w = (IWindow**)((char*)this + 0xc);
        int n = 4;
        do {
            IWindow* x = *w;
            if (x) (*(FnP2)Vslot(x, 0x7c))(x, 1, 0);
            ++w;
        } while (--n);
    }
}



// @ 0x0065f970
void FeedFilterA::Update4()
{
    int n = m0 - 1;
    for (int i = 0; i < 4; ++i) {
        IWindow_s0065_f970* w = mWin[i];
        if (w) {
            w->SetFlag(1, i <= n);
            IWindow_s0065_f970* q = mWin[i]->FindWindowByID(0x5d0dd57a, 0);
            if (q) q->SetFlag(1, i == m4);
        }
    }
}



// @ 0x0065f9e0
FeedFilterA::~FeedFilterA()
{
    IWindow_s0065_f970** p = mWin + 4;
    int i = 3;
    for (; i >= 0; --i) {
        IWindow_s0065_f970* q = *--p;
        if (q) q->Release();
    }
    IWindow_s0065_f970* z = m8;
    if (z) z->Release();
}



// @ 0x0065fa20
void FeedFilterB::Shutdown()
{
    if (mLayout) {
        mLayout->Shutdown(true);
        cSPUILayout_s0065_f970* p = mLayout;
        if (p) { mLayout = 0; p->Release(); }
    }
    if (mHandler) {
        void* h = mHandler;
        uint32_t a = mA80, b = mA84, c = mA88, d = mA8c;
        mHandler = 0;
        EA_RemoveHandler(h, a, b, c, d);
    }
}



// @ 0x0065faa0
void __cdecl cSPUIFeedFilter_ReloadCallback(FeedFilterB* self, void* a, char b)
{
    if (b == 0) {
        if (self->mWin6c) {
            self->mWin6c->AttachProc(self);
        }
        return;
    }
    IWindow_s0065_f970* w = self->mLayout->FindWindowByID(0xb435a20d, true);
    IWindow_s0065_f970* old = self->mWin6c;
    if (w != old) {
        if (w) w->s00();
        self->mWin6c = w;
        if (old) old->Release();
    }
    w = self->mLayout->FindWindowByID(0xb435a20c, true);
    old = self->mWin70;
    if (w != old) {
        if (w) w->s00();
        self->mWin70 = w;
        if (old) old->Release();
    }
    w = self->mLayout->FindWindowByID(0x12f66831, true);
    old = self->mWin74;
    if (w != old) {
        if (w) w->s00();
        self->mWin74 = w;
        if (old) old->Release();
    }
    w = self->mLayout->FindWindowByID(0x642a948, true);
    old = self->mWin78;
    if (w != old) {
        if (w) w->s00();
        self->mWin78 = w;
        if (old) old->Release();
    }
    if (self->mWin6c) {
        self->mWin6c->SetReloadCallback(self);
        SPUIHelpers_SetWindowAreaToParent(self->mWin6c);
    }
}



// @ 0x0065fbc0
Node14* __stdcall CloneNode14(const Node14* src)
{
    Node14* p = (Node14*)EASTL_allocator_allocate(0x14, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    if (p) {
        p->a = src->a;
        p->b = src->b;
        p->c = src->c;
        p->d = src->d;
        if (p->d) p->d->AddRef4();
    }
    p->e = 0;
    return p;
}



// @ 0x0065fcd0
AreaRec::AreaRec(const AreaRec& o)
{
    m0 = o.m0;
    mRef = o.mRef;
    if (mRef) mRef->AddRef();
    m8 = o.m8;
    m9 = o.m9;
    f0c = o.f0c;
    f10 = o.f10;
    f14 = o.f14;
    f18 = o.f18;
    m1c = o.m1c;
    m20 = o.m20;
}



// @ 0x00660360
void FeedFilterC::LockFilterUI(bool locked)
{
    for (FeedTreeNode* it = mBegin; it != (FeedTreeNode*)&mEnd; it = (FeedTreeNode*)RBTreeIncrement(it)) {
        IWindow_s0065_f970* w = it->mWin;
        if (w) {
            w->SetFlag(0x10, locked);
            w = it->mWin;
            if (w) {
                IWindow_s0065_f970* b = w->FindWindow(0x8ed27e7a);
                if (b) ((IButton*)b)->SetStateFlag(1, !locked);
            }
        }
    }
}



// @ 0x006603d0
AreaRec* AreaRec::AssignChecked(const uint32_t* head, const void* innerPtr)
{
    const AreaInner* o = (const AreaInner*)innerPtr;
    m0 = *head;
    mRef = o->ref;
    if (mRef) mRef->AddRef();
    m8 = o->b4;
    m9 = o->b5;
    f0c = o->f8;
    f10 = o->f0c;
    f14 = o->f10;
    f18 = o->f14;
    m1c = o->m18;
    m20 = o->m1c;
    return this;
}



// @ 0x00660430
Key* __cdecl KeyLowerBound(Key* first, Key* last, const Key* key)
{
    int n = (int)((char*)last - (char*)first) / 0xc;
    while (n > 0) {
        int half = n >> 1;
        Key* mid = (Key*)((char*)first + half * 0xc);
        bool less = mid->mInstance < key->mInstance;
        if (mid->mInstance == key->mInstance) {
            less = mid->mGroup < key->mGroup;
            if (mid->mGroup == key->mGroup)
                less = mid->mType < key->mType;
        }
        if (less) {
            first = (Key*)((char*)mid + 0xc);
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}



// @ 0x00660510
FeedEntry* __cdecl FeedDestroyRange(FeedEntry* first, FeedEntry* last, FeedEntry* out)
{
    while (first != last) {
        void* p = *(void**)((char*)first + 0x20);
        if (p && *(int*)((char*)p - 4) != 0)
            EASTL_allocator_deallocate(p);
        void* q = *(void**)((char*)first + 0x08);
        if (q && *(int*)((char*)q - 4) != 0)
            EASTL_allocator_deallocate(q);
        ++first;
        ++out;
    }
    return out;
}



// @ 0x00660650
bool __cdecl KeyContains(Key* first, Key* last, const Key* key)
{
    Key* it = KeyLowerBound(first, last, key);
    if (it == last) return false;
    bool less = key->mInstance < it->mInstance;
    if (key->mInstance == it->mInstance) {
        less = key->mGroup < it->mGroup;
        if (key->mGroup == it->mGroup)
            less = key->mType < it->mType;
    }
    return !less;
}



// @ 0x00660880
bool FeedOwner::Matches(KeyProvider* p, char useOther)
{
    KeyVec* vec = useOther ? &mOther : &mMain;
    if (p == 0) return true;
    uint32_t key = p->k09();
    int count = (int)(vec->mEnd - vec->mBegin) / 0x34;
    for (int i = 0; i < count; ++i) {
        FeedEntry* e = (FeedEntry*)((char*)vec->mBegin + i * 0x34);
        if (e->m0 != key) continue;
        bool bad = false;
        if (e->m4) {
            uint32_t first = *(uint32_t*)((char*)e + 0x08);
            uint32_t last  = *(uint32_t*)((char*)e + 0x0c);
            uint32_t k = p->k16();
            if (!KeyContains((Key*)first, (Key*)last, (Key*)k)) bad = true;
        }
        if (!e->m1c) {
            if (!bad) return false;
        } else if (!bad) {
            uint32_t first = *(uint32_t*)((char*)e + 0x20);
            uint32_t last  = *(uint32_t*)((char*)e + 0x24);
            uint32_t k = p->k16();
            if (KeyContains((Key*)first, (Key*)last, (Key*)k)) return false;
        }
    }
    return true;
}



// @ 0x006609a0
KeyVec& KeyVec::operator=(const KeyVec& o)
{
    if (&o == this) return *this;
    uint32_t n = (uint32_t)(o.mEnd - o.mBegin);
    if ((uint32_t)(mCap - mBegin) < n) {
        Key* p = KeyVecAlloc(n, o.mBegin, o.mEnd);
        if (mBegin) {
            if (*(int*)((char*)mBegin - 4) != 0)
                EASTL_allocator_deallocate(mBegin);
        }
        mCap = p + n;
        mBegin = p;
        mEnd = p + n;
        return *this;
    }
    uint32_t have = (uint32_t)(mEnd - mBegin);
    if (have < n) {
        CopyOverlap(o.mBegin, o.mEnd, mBegin);
        void* last = o.mEnd;
        UninitCopyPtr((void**)&last, o.mBegin + have, o.mEnd, mEnd, mEnd);
        mEnd = mBegin + n;
        return *this;
    }
    CopyOverlap(mBegin, o.mEnd, mBegin);
    mEnd = mBegin + n;
    return *this;
}



// @ 0x00660ad0
FeedEntry* __cdecl FeedRangeConstruct(FeedEntry** out, FeedEntry* first, FeedEntry* last, FeedEntry* p)
{
    *out = p;
    while (first != last) {
        if (*out) {
            (*out)->m0 = first->m0;
            (*out)->m4 = first->m4;
            (*out)->v08 = first->v08;
            (*out)->m1c = first->m1c;
            (*out)->v20 = first->v20;
        }
        ++first;
        ++*out;
    }
    return *out;
}



// @ 0x00660b30
FeedEntry* __cdecl FeedUninitCopy(FeedEntry* first, FeedEntry* last, FeedEntry* dest)
{
    while (first != last) {
        if (dest) {
            dest->m0 = first->m0;
            dest->m4 = first->m4;
            dest->v08 = first->v08;
            dest->m1c = first->m1c;
            dest->v20 = first->v20;
        }
        ++first;
        ++dest;
    }
    return dest;
}



// @ 0x00660b90
void FeedFilterD::Clear()
{
    for (FeedTreeNode* it = mBegin; it != (FeedTreeNode*)&mEnd; it = (FeedTreeNode*)RBTreeIncrement(it)) {
        IWindow_s0065_f970* w = it->mWin;
        if (w) {
            IWindow_s0065_f970* q = w->GetSomething();
            q->s56(w);
        }
    }
    ((TreeStub*)((char*)this + 0x9c))->dtorSubtree(mRoot);
    mBegin = mEnd;
    mRoot = 0;
    mAc = false;
    mB0 = 0;
    *(FeedTreeNode**)mEnd = mEnd;
}



// @ 0x00660d70
FeedEntry* __cdecl FeedRangeAssign(FeedEntry* first, FeedEntry* last, FeedEntry* dest)
{
    while (first != last) {
        dest->m0 = first->m0;
        dest->m4 = first->m4;
        dest->v08 = first->v08;
        dest->m1c = first->m1c;
        dest->v20 = first->v20;
        ++first;
        ++dest;
    }
    return dest;
}


// @ 0x00660dd0
E34* CopyBackward34(E34* first, E34* last, E34* dest)
{
    while (last != first) {
        --last; --dest;
        dest->a = last->a;
        dest->b = last->b;
        dest->c.Assign(&last->c);
        dest->d = last->d;
        dest->e.Assign(&last->e);
    }
    return dest;
}


// @ 0x00660e30
void cSPUIFeedFilter::dtor()
{
    char* p = (char*)this;
    *(void**)(p + 0) = (void*)0x14000e0;
    *(void**)(p + 4) = (void*)0x14000d0;
    *(void**)(p + 8) = (void*)0x14000c0;
    void* v = *(void**)(p + 0xf4);
    if (v) EASTL_allocator_deallocate(v);
    ((SubD8*)(p + 0xd8))->FUN_0065f9e0();
    FUN_00660720(*(void**)(p + 0xbc), *(void**)(p + 0xc0));
    *(void**)(p + 0xc4) = 0;
    if (*(uint32_t*)(p + 0xc0) > 1) EASTL_allocator_deallocate(*(void**)(p + 0xbc));
    FUN_00d0c930(*(void**)(p + 0xa8));
    void* h = *(void**)(p + 0x7c);
    if (h) { *(void**)(p + 0x7c) = 0; EA_Messaging_RemoveHandler(h, *(void**)(p + 0x80), *(void**)(p + 0x84), *(void**)(p + 0x88), *(void**)(p + 0x8c)); }
    void* a = *(void**)(p + 0x78); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x74); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x70); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x6c); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x68); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x64); if (a) (*(FnP)Vslot(a, 8))(a);
    { Vec34* w = (Vec34*)(p + 0x30);
      FUN_00646d70(w->begin, w->end);
      if (w->begin && *(int*)((char*)w->begin - 4) != 0) EASTL_allocator_deallocate(w->begin); }
    { Vec34* w = (Vec34*)(p + 0x1c);
      FUN_00646d70(w->begin, w->end);
      if (w->begin && *(int*)((char*)w->begin - 4) != 0) EASTL_allocator_deallocate(w->begin); }
    *(void**)(p + 8) = (void*)0x13ec458;
    *(void**)(p + 4) = (void*)0x13eb394;
    *(void**)(p + 0) = (void*)0x13eb938;
}


// @ 0x00661020
void* cSPUIFeedFilter::ctor()
{
    char* p = (char*)this;
    *(void**)(p + 4) = (void*)0x13eb384;
    *(void**)(p + 8) = (void*)0x13ec458;
    *(void**)(p + 0xc) = 0;
    *(void**)(p + 0) = (void*)0x14000e0;
    *(void**)(p + 4) = (void*)0x14000d0;
    *(void**)(p + 8) = (void*)0x14000c0;
    *(char*)(p + 0x10) = 0;
    *(void**)(p + 0x1c) = 0; *(void**)(p + 0x20) = 0; *(void**)(p + 0x24) = 0;
    *(void**)(p + 0x30) = 0; *(void**)(p + 0x34) = 0; *(void**)(p + 0x38) = 0;
    FUN_0066a5e0(p + 0x44, 1, *(int*)0x140042c);
    *(void**)(p + 0x64) = 0; *(void**)(p + 0x68) = 0; *(void**)(p + 0x6c) = 0;
    *(void**)(p + 0x70) = 0; *(void**)(p + 0x74) = 0; *(void**)(p + 0x78) = 0;
    *(void**)(p + 0x7c) = 0; *(void**)(p + 0x80) = 0; *(void**)(p + 0x84) = 0;
    *(void**)(p + 0x88) = 0; *(void**)(p + 0x8c) = 0;
    *(float*)(p + 0x90) = 0.0f; *(float*)(p + 0x94) = 0.0f; *(float*)(p + 0x98) = 0.0f;
    *(void**)(p + 0xa0 + 4) = 0; *(void**)(p + 0xa0 + 8) = 0; *(void**)(p + 0xa0 + 0xc) = 0;
    *(void**)(p + 0xa4) = p + 0xa0;
    *(void**)(p + 0xa8) = 0;
    *(char*)(p + 0xac) = 0;
    *(void**)(p + 0xb0) = 0;
    *(void**)(p + 0xa0) = p + 0xa0;
    *(float*)(p + 0xc8) = 1.0f;
    *(float*)(p + 0xcc) = *(float*)0x1470f1c;
    *(void**)(p + 0xc4) = 0;
    *(void**)(p + 0xd0) = 0;
    *(void**)(p + 0xc0) = (void*)1;
    *(void**)(p + 0xbc) = (void*)0x154df28;
    *(void**)(p + 0xe0) = 0; *(void**)(p + 0xe4) = 0; *(void**)(p + 0xe8) = 0;
    *(void**)(p + 0xec) = 0; *(void**)(p + 0xf0) = 0; *(void**)(p + 0xf4) = 0;
    *(void**)(p + 0xf8) = 0; *(void**)(p + 0xfc) = 0;
    *(char*)(p + 0x10c) = 0;
    return this;
}


// @ 0x00661180
char FUN_00661180(void* vec, void* key)
{
    DoCopyKeys(*(void**)((char*)vec + 0), *(void**)((char*)vec + 4), key);
    void* pm = SP_PropertyManager();
    void* local = 0;
    (*(void(__thiscall*)(void*, int, void**))Vslot(pm, 0x2c))(pm, 0xcc489c6f, &local);
    char r = 0;
    if (local) {
        Key3 k;
        r = FUN_006a12a0(local, 0x14593fac, &k);
        if (r) { r = 1; }
        if (r == 0 && local) (*(FnP)Vslot(local, 4))(local);
    }
    return r;
}


// @ 0x006612b0
void* MapRoot34::FUN_006612b0(void* key)
{
    char* p = (char*)this;
    uint32_t k = *(uint32_t*)key;
    E34* node = *(E34**)(p + 0xc);
    E34* found = (E34*)(p + 4);
    while (node) {
        if (node->a < k) node = *(E34**)node;
        else { found = node; node = *(E34**)((char*)node + 4); }
    }
    if (found == (E34*)(p + 4) || k < found->a) {
        E34* newn = (E34*)FUN_006603d0(key, 0);
        Fun0066_0b30(*(void**)p, found, newn);
        found = newn;
    }
    return found;
}


// @ 0x00661390
void* FUN_00661390(void* self, void* other)
{
    Vec34* v = (Vec34*)self;
    Vec34* o = (Vec34*)other;
    if (o != v) {
        unsigned n = (unsigned)(o->end - o->begin);
        unsigned cap = (unsigned)(v->cap - v->begin);
        if (cap < n) {
            E34* buf = (E34*)Fun0066_0fc0(n, o->begin, o->end);
            FUN_00646d70(v->begin, v->end);
            if (v->begin && *(int*)((char*)v->begin - 4) != 0) EASTL_allocator_deallocate(v->begin);
            v->end = buf + n; v->begin = buf; v->cap = buf + n;
            return self;
        }
        unsigned have = (unsigned)(v->end - v->begin);
        if (have < n) {
            E34* mid = v->begin + have;
            Fun0066_0d70(o->begin, o->begin + have, v->begin);
            Fun0066_0ad0(o->begin + have, o->end, mid, v->end, o->end);
            v->end = v->begin + n;
            return self;
        }
        Fun0066_0d70(o->begin, o->end, v->begin);
        FUN_00646d70(v->begin + n, v->end);
        v->end = v->begin + n;
    }
    return self;
}


// @ 0x006614d0
void* FUN_006614d0(void* self, void* pos, void* value)
{
    Vec34* v = (Vec34*)self;
    E34* end = v->end;
    if (end != v->cap) {
        E34* val = (E34*)value;
        if (pos <= val && val < end) val = (E34*)((char*)val + 0x34);
        if (end) {
            end->a = ((E34*)((char*)end - 0x34))->a;
            end->b = ((E34*)((char*)end - 0x34))->b;
            end->c.FUN_006606a0(&((E34*)((char*)end - 0x34))->c);
            end->d = ((E34*)((char*)end - 0x34))->d;
            end->e.FUN_006606a0(&((E34*)((char*)end - 0x34))->e);
        }
        CopyBackward34((E34*)pos, (E34*)((char*)v->end - 0x34), v->end);
        E34* p = (E34*)pos; E34* s = val;
        p->a = s->a; p->b = s->b; p->c.Assign(&s->c); p->d = s->d; p->e.Assign(&s->e);
        v->end = (E34*)((char*)v->end + 0x34);
        return pos;
    }
    unsigned n = (unsigned)(end - v->begin);
    unsigned nc = n ? n * 2 : 1;
    E34* buf = 0;
    if (nc) buf = (E34*)EASTL_allocator_allocate(nc * 0x34, "Editor", 0, 0,
                                                (const char*)0x13ebb38, 0xd1);
    if (buf) {
        E34* p = (E34*)Fun0066_0b30(v->begin, pos, buf);
        Fun0066_0510(v->begin, pos, buf);
        if (p) { E34* s = (E34*)value; p->a=s->a; p->b=s->b; p->c.Assign(&s->c); p->d=s->d; p->e.Assign(&s->e); }
        E34* p2 = (E34*)Fun0066_0b30(pos, v->end, (char*)p + 0x34);
        Fun0066_0510(pos, v->end, (char*)p + 0x34);
        if (v->begin && *(int*)((char*)v->begin - 4) != 0) EASTL_allocator_deallocate(v->begin);
        v->end = p2; v->begin = buf; v->cap = buf + nc;
    }
    return pos;
}


// @ 0x00661670
void Vec34::FUN_00661670()
{
    Vec34* v = this; void* self = this;
    E34* e = v->end;
    if (e < v->cap) {
        v->end = e + 1;
        if (e) {
            *(uint32_t*)(e->c.x + 0) = 0; *(uint32_t*)(e->c.x + 4) = 0; *(uint32_t*)(e->c.x + 8) = 0;
            *(uint32_t*)(e->e.x + 0) = 0; *(uint32_t*)(e->e.x + 4) = 0; *(uint32_t*)(e->e.x + 8) = 0;
        }
        return;
    }
    E34 tmp;
    *(uint32_t*)(tmp.c.x + 0) = 0; *(uint32_t*)(tmp.c.x + 4) = 0; *(uint32_t*)(tmp.c.x + 8) = 0;
    *(uint32_t*)(tmp.e.x + 0) = 0; *(uint32_t*)(tmp.e.x + 4) = 0; *(uint32_t*)(tmp.e.x + 8) = 0;
    FUN_006614d0(self, e, &tmp);
}


// @ 0x00661700
void Vec34::FUN_00661700()
{
    Vec34* v = this;
    E34* begin = v->begin;
    E34* end = v->end;
    Fun0066_0d70(end, end, begin);
    FUN_00646d70(begin, end);
    v->end = (E34*)((char*)v->end - 0x34);
}

// @ 0x00661d10
void FeedList::CreateFilterButtons(int key, int flag, int depth, int* counter)
{
    if (!FUN_00661a10(key)) return;
    if (!m70) return;
    CFVec2 pos;
    float c0 = (float)*counter;
    pos.x = c0 * m98 + m90;
    pos.y = m94;
    if ((char)flag == 0) {
        float add = 0.0f;
        if (CF_AssetBrowser() && *(void**)((char*)CF_AssetBrowser() + 0x18))
            add = CF_GetPropertyFloat(*(void**)((char*)CF_AssetBrowser() + 0x18), 0x5b9cdcf4, 0.0f);
        pos.x += add;
    }
    md8 = depth;
    CFPlist* props = 0;
    CFPropMgr* pm = CF_PropertyManager();
    if (props) { CFPlist* t = props; props = 0; t->Release(); }
    pm->GetPropertyList(key, 0xcc489c6f, &props);
    if (props) {
        CFValue* node;
        char fallback = 0;
        char found[4];
        CFMap* map = (CFMap*)((char*)this + 0x9c);
        void* endNode = (char*)this + 0xa0;
        if (*map->find(found, &key) == endNode) {
            node = map->Get(&key);
            float o2c = 0, o30 = 0;
            CFWin* btn;
            if (CF_GetPropVec2(props, 0x7435a2d1, &o30, &o2c)) {
                btn = CF_CreateButtonA(*(uint32_t*)&o2c, 3, key, pos, (CFWin*)m70);
            } else {
                CFKey k = {0, 0, 0};
                CF_GetPropertyAsKey(props, 0x86ad309, &k);
                uint32_t winId = k.b;
                k.b = 0x510a95b;
                if (winId == 0 || winId == (uint32_t)-1) winId = key;
                CFLayoutRef layout; layout.p = 0;
                CFWinRef w; w.p = 0;
                CFWinRef bw; bw.p = 0;
                if (k.a == 0 || k.a == (uint32_t)-1) {
                    w.Assign(((CFLayout*)mLayout64)->FindWindowByID(winId, true));
                    bw.Assign(CF_InterfaceCast(&w));
                } else {
                    if (k.c == 0 || k.c == (uint32_t)-1) k.c = 0x40464100;
                    char it[8];
                    CFHash* h = (CFHash*)mHash;
                    h->find(it, &k);
                    void** buckets = *(void***)(mHash + 4);
                    int nb = *(int*)(mHash + 8);
                    if (*(void**)(it) != buckets[nb]) {
                        layout.Assign((CFLayoutRef*)((char*)*(void**)it + 0xc));
                    } else {
                        CFLayout* nl = (CFLayout*)CF_OperatorNew(0x18, "Sporepedia", 0, 0, 0, 0);
                        if (nl) nl = nl->Construct();
                        layout.Ctor(nl);
                        layout.p->Init(&k, 1, 0x5b598fa);
                        layout.p->SetParentWin((CFWin*)m6c, 1, 0x5b598fa);
                        layout.p->SetVisibility(0);
                        h->Index(&k)->Assign(&layout);
                    }
                    w.Assign(layout.p->FindWindowByID(winId, true));
                    bw.Assign(CF_InterfaceCast(&w));
                }
                if (w.p && bw.p) {
                    btn = CF_ButtonFromHandle(w.p->GetHandle(), 3, key, pos, (CFWin*)m70);
                    if (w.p->GetInner()->GetTypeId() == 0x7e0c110) {
                        float* r = w.p->GetArea();
                        node->rx = r[0];
                        node->ry = r[1];
                        btn->GetInner()->SetSize(r[2] - r[0], r[3] - r[1]);
                        btn->GetInner()->SetLocation(node->rx + pos.x, node->ry + pos.y);
                    }
                } else {
                    CFKey k2 = {0xfa224478, 0x2f7d0004, 0x11c0bde};
                    btn = CF_CreateButtonB(&k2, 3, key, pos, (CFWin*)m70);
                    fallback = 1;
                }
                if (layout.p) layout.p->Release();
                if (w.p) w.p->Release();
                if (bw.p) bw.p->Release();
            }
            if (btn) {
                node->win.Assign(btn->GetInner());
                btn->SetCmd(0x3436f351);
                CFString str; str.Ctor();
                if (CF_GetPropertyAsText(props, 0x7435a2d0, &str)) {
                    if (fallback) {
                        CFWin* in = btn->GetInner();
                        in->SetCaption(str.GetText());
                        btn->GetInner()->SetFlag2(0xaf14b67e);
                        btn->GetInner()->Finish();
                    } else {
                        void* mem = CF_AllocTooltip(0x68, 4, "UI/Tooltip", CF_AllocTooltipHeap());
                        CFTooltip* tt = 0;
                        if (mem) {
                            float off[2]; off[0] = 0.0f; off[1] = *(float*)0x14000fc;
                            tt = ((CFTooltip*)mem)->Ctor(L"Tooltips", 0x3754e6c, str.GetText(), off, 0, (const void*)0x14000bc, 0);
                        }
                        CFTooltipRef tr; tr.Ctor(tt);
                        node->win.p->AddProc(tr.p);
                        if (tr.p) ((CFWin*)tr.p)->Release();
                    }
                }
                str.Dtor();
            }
            CF_GetPropertyAsKeyInstance(props, 0x7435a2d2, &node->k18);
            CF_GetPropertyAsKeyInstance(props, 0x14593fac, &node->k1c);
        } else {
            node = map->Get(&key);
        }
        node->b4 = true;
        node->x = pos.x;
        node->y = pos.y;
        bool sel = (key == m18);
        node->b5 = sel;
        if (sel) mdc = depth;
        ++*counter;
        if ((char)flag) {
            CFKey* arr = 0;
            int count = 0;
            if (CF_GetPropArray(props, 0x7435a2d3, &count, &arr)) {
                if (key == m18) {
                    for (int i = 0; i < count; ++i)
                        CreateFilterButtons(arr[i].a, 0, depth + 1, counter);
                } else if (FUN_00661c00(key, 0)) {
                    int idx = -1;
                    for (int i = 0; i < count; ++i) {
                        if (FUN_00661c00(arr[i].a, 0)) { idx = i; break; }
                    }
                    if (FUN_00661b10(arr[idx].a)) {
                        CreateFilterButtons(arr[idx].a, 1, depth + 1, counter);
                    } else {
                        for (int i = 0; i < count; ++i)
                            CreateFilterButtons(arr[i].a, 0, depth + 1, counter);
                    }
                }
            }
        }
        props->Release();
    }
}

// @ 0x006627d0
bool FeedList::FUN_006627d0(void* a, int* msg)
{
    (void)a;
    if (*(int*)((char*)msg + 8) != 0x287259f6) return false;
    void* at = SP_GetSystemAT();
    void* r = at ? ((AudioAT*)at)->Slot20() : 0;
    SP_KillSetiEffects(0x43ae5220, r);
    m18 = *(int*)((char*)msg + 0xc);
    FUN_00662540();
    SP_MessageServer()->PostMessage(0xd43aca3c, 0, 0);
    return true;
}
