// src/game/SPEditors/SPUIFeedListCategory.cpp -- migrated from slice(s) s00665d30, s00664c90, s00663be0, s00662d70 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIFeedListCategory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
#include <intrin.h>
#include "SP/cSPUIFeedListCategory.h"
#include "cSPUILayout.h"
#include "EA/UTFWin/IWinProc.h"

// ---- items of slice s00662d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
// ---- items of slice s00662d70 end

// ---- items of slice s00663be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_fp1;   // 0x01486110
struct IWindow;
struct FeedItem {
    virtual int  AddRef();       // +0x00
    virtual int  Release();      // +0x04
    char     pad08[8];
    void*    m0c;                // +0x0c
    int      m10;                // +0x10
    bool     m14;                // +0x14
    char     pad15[3];
    wchar_t* mName;              // +0x18
    char     pad1c[0xc4 - 0x1c];
    int      mGroup;             // +0xc4
    char     padc8[0x134 - 0xc8];
    int      m134;               // +0x134
    char     pad138[0x17c - 0x138];
    int      m17c;               // +0x17c
    char     pad180[0x188 - 0x180];
    int      m188;               // +0x188
    void FUN_00667690(int v);    // 0x00667690
    void FUN_00668550(int v);    // 0x00668550
    void FUN_00666590(float* r); // 0x00666590
    void FUN_00666680(int v);    // 0x00666680
};
struct AutoRefCountT {
    FeedItem* mpObject;
    AutoRefCountT() : mpObject(0) {}
    AutoRefCountT(const AutoRefCountT& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCountT() { if (mpObject) mpObject->Release(); }
    AutoRefCountT& operator=(const AutoRefCountT& o) {
        if (o.mpObject != mpObject) {
            if (o.mpObject) o.mpObject->AddRef();
            FeedItem* old = mpObject;
            mpObject = o.mpObject;
            if (old) old->Release();
        }
        return *this;
    }
    FeedItem* operator->() const { return mpObject; }
    operator FeedItem*() const { return mpObject; }
};
struct IWindow {
    virtual void      v00();                          // 0x00
    virtual int       Release();                      // 0x04
    virtual void      v02();                          // 0x08
    virtual IWindow*  FindWindow(uint32_t id);        // 0x0c
    virtual IWindow*  v04();                          // 0x10
    virtual void      v05();                          // 0x14
    virtual void      v06();                          // 0x18
    virtual void      v07();                          // 0x1c
    virtual void      v08();                          // 0x20
    virtual void      v09();                          // 0x24
    virtual void      SetStateFlag(int, bool);        // 0x28
    virtual void      v11();                          // 0x2c
    virtual void      v12();                          // 0x30
    virtual float*    GetArea();                      // 0x34
    virtual float*    GetRect();                      // 0x38
    virtual void      v15();                          // 0x3c
    virtual void      v16();                          // 0x40
    virtual void      v17();                          // 0x44
    virtual void*     v18(int);                       // 0x48
    virtual void      v19();                          // 0x4c
    virtual void      v20();                          // 0x50
    virtual void      v21();                          // 0x54
    virtual void      v22();                          // 0x58
    virtual void      v23();                          // 0x5c
    virtual void      SetArea(float*);                // 0x60
    virtual void      v25();                          // 0x64
    virtual void      v26();                          // 0x68
    virtual void      v27(void*);                     // 0x6c
    virtual void      v28();                          // 0x70
    virtual void      v29();                          // 0x74
    virtual void      v30();                          // 0x78
    virtual void      SetFlag(int, bool);             // 0x7c
    virtual void      v32();                          // 0x80
    virtual void      v33();                          // 0x84
    virtual void      v34();                          // 0x88
    virtual void      v35();                          // 0x8c
    virtual void      v36();                          // 0x90
    virtual void      v37();                          // 0x94
    virtual void      v38();                          // 0x98
    virtual void      v39();                          // 0x9c
    virtual void      v40();                          // 0xa0
    virtual void      v41();                          // 0xa4
    virtual void      v42();                          // 0xa8
    virtual void      v43();                          // 0xac
    virtual void      v44();                          // 0xb0
    virtual void      v45();                          // 0xb4
    virtual void      v46();                          // 0xb8
    virtual void      v47();                          // 0xbc
    virtual void      v48();                          // 0xc0
    virtual void      v49();                          // 0xc4
    virtual void      v50();                          // 0xc8
    virtual void      v51();                          // 0xcc
    virtual void      v52();                          // 0xd0
    virtual void      v53();                          // 0xd4
    virtual void      v54();                          // 0xd8
    virtual void      v55();                          // 0xdc
    virtual void      v56();                          // 0xe0
    virtual void      v57();                          // 0xe4
    virtual void      v58();                          // 0xe8
    virtual void      v59();                          // 0xec
    virtual void      v60();                          // 0xf0
    virtual void      v61();                          // 0xf4
    virtual void      v62();                          // 0xf8
    virtual void      v63();                          // 0xfc
    virtual void      v64();                          // 0x100
    virtual void      v65();                          // 0x104
    virtual void      AttachProc(void*);              // 0x108
};
struct AudioAT {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void* Slot20();                           // 0x20
};
struct cSPUILayout_s0066_3be0 {
    virtual void s0();
    virtual void s1();
    virtual int  Release();                           // 0x08
    void Shutdown(bool);                              // 0x00811ad0
    char pad[0x18 - 4];
};
struct WindowManager {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(int a, void* b, void* c, int d); // 0x10
    virtual void w05(); virtual void w06(); virtual void w07(); virtual void w08();
    virtual void w09(); virtual void w10(); virtual void w11(); virtual void w12();
    virtual void w13(); virtual void w14(); virtual void w15(); virtual void w16();
    virtual void w17();
    virtual void* w18(int v);                         // 0x48
};
void  __cdecl EA_RemoveHandler(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00571db0
struct D4Obj { void FUN_00829d30(); };
void  __stdcall FUN_008294c0(void* p, int v);                 // 0x008294c0
bool  __cdecl FUN_00805150(void* a, void* b);                 // 0x00805150
bool  __cdecl StartBanMode(uint32_t id);                      // 0x008d2fb0
struct PredObj { bool FUN_00a98020(); };
void* __cdecl SP_WindowManager();                             // 0x0067caa0
void* __cdecl SP_GetSystemAT();                               // 0x00a206f0
void  __cdecl SP_KillSetiEffects(uint32_t id, void* at);      // 0x00435ed0
void* __cdecl FUN_005c2570(void* p);                          // 0x005c2570 interface_cast
void  __cdecl FUN_00662b00(void* p);                          // 0x00662b00
struct cSPUIFeedListCategory {
    char      pad00[0x10];
    bool      m10;            // +0x10
    char      pad11[3];
    bool      m14;            // +0x14
    bool      m15;            // +0x15
    char      pad16[0x12];
    float     m28, m2c, m30, m34;   // +0x28 Rect
    float     m38, m3c, m40, m44;   // +0x38 Rect
    char      pad48[0x10];
    float     m58;            // +0x58
    float     m5c;            // +0x5c
    void*     m60;            // +0x60
    cSPUILayout_s0066_3be0* m64;         // +0x64
    char      pad68[4];
    void*     m6c;            // +0x6c
    IWindow*  m70;            // +0x70
    IWindow*  m74;            // +0x74
    IWindow*  m78;            // +0x78
    IWindow*  m7c;            // +0x7c
    IWindow*  m80;            // +0x80
    IWindow*  m84;            // +0x84
    FeedItem** m88;           // +0x88 vector begin
    FeedItem** m8c;           // +0x8c vector end
    char      pad90[8];
    bool      m98;            // +0x98
    char      pad99[3];
    bool      m9c;            // +0x9c
    char      pad9d[0x1f];
    void*     mbc;            // +0xbc
    uint32_t  mc0, mc4, mc8, mcc;   // +0xc0..0xcc
    char      padD0[4];
    void*     md4;            // +0xd4

    bool FUN_00663be0(void* msg);
    void FUN_00663e50();
    void FUN_00663ef0(int param);
    void FUN_00664390(float a, float b, float c, float d);
    void FUN_00664440();
    void FUN_00664480(bool expanded);
    void FUN_006644e0(bool b);
    bool FUN_00664550(bool b);
    void FUN_00664580(bool b);
    FeedItem* FUN_00664610(uint32_t idx);
    FeedItem* FUN_00664640(int id);
    FeedItem* FUN_00664680(int id);
    FeedItem* FUN_006646c0(int id);
    bool FUN_00664a60(uint32_t id, void* msg);
};
static void AssignRef(AutoRefCountT& slot, FeedItem* p) {
    if (p != slot.mpObject) {
        if (p) p->AddRef();
        FeedItem* old = slot.mpObject;
        slot.mpObject = p;
        if (old) old->Release();
    }
}
// ---- items of slice s00663be0 end

// ---- items of slice s00664c90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void  EA_Messaging_RemoveHandler(void* a, void* b, void* c, void* d, void* e);
extern "C" void* SP_PropertyManager();
extern "C" void __stdcall FUN_00601b40(void* pos, void* val);
extern "C" void  FUN_00b2af00(int* a, int* b);
extern "C" void  FUN_00ac97a0(void* a, void* b, void* c);
extern "C" void  FUN_006664f0(void* p);
extern "C" void  FUN_006657f0(void* a, void* b, void* c);
extern "C" void  FUN_00669410(void* p);
extern int gVtA, gVtB, gVtC, gVtD, gVtE, gVtF, gVtG, gVtH;
extern "C" void  FUN_00665000(void*, void*, void*);
extern "C" void  FUN_00665050(void*, void*, void*);
extern "C" void  FUN_00664ad0(void*, int, int, int);
extern "C" void  FUN_006b5060(void* self);
extern "C" void  FUN_006b5240(void* self);
extern "C" void  FUN_006b55c0(void* self);
extern "C" char  FUN_006a1360(void* obj, int k, void* out);
extern "C" char  FUN_006a0ae0(void* obj, int k, int* count, void** ptr);
typedef void(__thiscall* FnP)(void*);
static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }
struct Vec8 {
    void* begin; void* end; void* cap;
    void push_back(void* val);
};
struct VecAutoRef4 {
    void* begin; void* end; void* cap;
    void erase(void* first, void* last);
    void FUN_006650c0(void* pos, void* value);
};
struct cSPUIFeedListCategory_s0066_4c90 {
    char  vt[0xc];                     // 0x00
    char  b0c[8];                      // 0x0c..0x13
    char  m14;                         // 0x14
    char  m15;                         // 0x15
    char  pad16[2];
    void* p18; void* p1c; void* p20;   // cString
    char  pad24[0x34];                 // 0x24..0x57
    float f58; float f5c;              // 0x58,0x5c
    void* p60; void* p64; void* p68; void* p6c;
    void* p70; void* p74; void* p78; void* p7c;
    void* p80; void* p84;
    void* childBegin;                  // 0x88
    void* childEnd;                    // 0x8c
    void* childCap;                    // 0x90
    void* p94; void* p98;
    char  m9c;                         // 0x9c
    char  pad9d[3];
    void* pA0; void* pA4; void* pA8;   // vector<pair8>
    void* padAc;
    void* pB4;
    void* pB8; void* pBc; void* pC0;
    void* pC4; void* pC8; void* pCc;
    char  mD0;                         // 0xd0
    char  padD1[3];
    void* pD4;

    void* Ctor();
    void  Dtor();
    __declspec(noinline) void  ShutdownChildren();
    __declspec(noinline) void  Populate();  // 0x00665c50 (cSPUIFeedListCategory::Populate)
    __declspec(noinline) void* Refresh(int param, int* count);
};
struct CatChild { void FUN_006664f0(); };
// ---- items of slice s00664c90 end

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
void FUN_00829d30();
struct VObj { void** vt; };
typedef void* (__thiscall *FnV0)(void*);
typedef void  (__thiscall *FnV1)(void*);
typedef void  (__thiscall *FnV1p)(void*, void*);
typedef void  (__thiscall *FnV1i)(void*, int);
typedef void  (__thiscall *FnV2i)(void*, int, int);
typedef void* (__thiscall *FnV0i)(void*, int);
typedef bool  (__thiscall *FnVb1i)(void*, int, void**);
typedef bool  (__thiscall *FnVb2i)(void*, int, int, void**);
struct IRef2 { virtual void AddRef(); virtual void Release(); };
struct CFull;
void ReloadCallback(CFull*, void*, char);
void SetRefSlot(void** slot, void* p) {
  if (p != *slot) {
    if (p) ((IRef2*)p)->AddRef();
    void* old = *slot;
    *slot = p;
    if (old) ((IRef2*)old)->Release();
  }
}
void* PropertyManager();
struct Dlg { int a, b, c, d, e, f; Dlg(); };
void* operator new(size_t, const char*, int, int, int, int);
void* ConfigManager();
void* MessageServer();
char* GetPropertyAsKeyArray();
void SetReloadCB(void* layout, void* cb, void* self);
void InitLayout(void* layout, void* arr, int a, uint32_t id);
void SetParentWinF(void* layout, void* w, int a, uint32_t id);
void SetRefSlot(void** slot, void* p);
struct CCat {
  char pad00[0x10];
  bool m10; bool m14; bool m15;
  char pad16[0x4a];      // to 0x60
  void* m60;             // +0x60
  void* m64;             // +0x64
  void* m68;             // +0x68
  void* m6c;             // +0x6c
  char pad70[0x44];      // to 0xb4
  void* mb4;             // +0xb4
  void* mb8;             // +0xb8
  char padBC[0x10];      // to 0xcc
  int mbc, mc0, mc4, mc8, mcc;
  bool Init(void* a, void* b, int c);
};
void Populate(CFull* self);
void FUN_00805ef0(void* out, void* in);
void FUN_00829c50(void* a, void* b, void* c, void* d);
void vec_erase(void* vec, void* begin, void* end);
void* FindWindowByIDF(void* layout, uint32_t id, bool rec);
struct CFull {
  char pad00[0x18];
  int m18;
  char pad1c[0xc];
  float m28, m2c, m30, m34;
  float m38, m3c, m40, m44;
  float m48, m4c, m50, m54;
  float m58;
  char pad5c[4];
  void* m60;
  void* m64;
  void* m68;
  void* m6c;
  void* m70;
  void* m74;
  void* m78;
  void* m7c;
  void* m80;
  void* m84;
  void* m88;
  void* m8c;
  char pad90[0x44];
  void* md4;
};
// ---- items of slice s00665d30 end

// @ 0x00663b80
char FUN_00663b80(int a, int b)
{
    if (!a || !b) return 0;
    int x = *(int*)(a + 0xc4);
    int y = *(int*)(b + 0xc4);
    if (x != y) return (char)(x < y);
    const wchar_t* sa = *(const wchar_t**)(a + 0x18);
    const wchar_t* sb = *(const wchar_t**)(b + 0x18);
    if (sa && sb) {
        if (_wcsicmp(sa, sb) < 0) return 1;
    }
    return 0;
}




// @ 0x00663be0
bool cSPUIFeedListCategory::FUN_00663be0(void* msg)
{
    int type = *(int*)((char*)msg + 8);
    if (type > 0x1c) goto case287259f6;
    if (type == 0x1c) goto case1c;
    if (type == 9) goto case9;
    if (type != 0x1b) goto def;
    {
        if (*(int*)((char*)msg + 0xc) != 1) goto def;
        if (mcc) goto def;
        void* q = *(void**)((char*)msg + 0x18);
        if (!FUN_00805150(m70, q)) goto def;
        bool b1 = StartBanMode(0x3e8);
        bool b2 = StartBanMode(0x3ea);
        bool b3 = StartBanMode(0x3e9);
        if (b1 || b2 || b3) goto def;
        mcc = 1;
        return false;
    }
case9:
    {
        uint32_t v = *(uint32_t*)((char*)msg + 4);
        if (v != (uint32_t)m78 && v != (uint32_t)m7c && v != (uint32_t)m80) goto def;
        WindowManager* wm = (WindowManager*)SP_WindowManager();
        wm->w04((int)m6c, m64, msg, 0);
        return false;
    }
case1c:
    {
        if (*(int*)((char*)msg + 0xc) != 1) goto def;
        if (!mcc) goto def;
        WindowManager* wm = (WindowManager*)SP_WindowManager();
        void* r = wm->w18(1);
        void* q = *(void**)((char*)msg + 0x18);
        if (!FUN_00805150(m70, q)) goto def;
        if (FUN_00805150(m70, r)) goto def;
        mcc = 0;
        return false;
    }
case287259f6:
    if (type != 0x287259f6) goto def;
    {
        int sub = *(int*)((char*)msg + 0xc);
        if (sub == (int)0xb3c6efc2) goto sub_b3;
        if (sub == (int)0xb48e2560) goto sub_b4;
        goto def;
    }
sub_b3:
    {
        bool nv = (m98 == 0);
        m98 = nv;
        void* at = SP_GetSystemAT();
        void* r = at ? ((AudioAT*)at)->Slot20() : 0;
        uint32_t id = nv ? 0xea0588f8u : 0x2dd00402u + 0xea0588f8u;
        SP_KillSetiEffects(id, r);
        if (m7c) {
            IWindow* b = (IWindow*)FUN_005c2570(&m7c);
            b->SetStateFlag(4, nv);
        }
        goto tail;
    }
sub_b4:
    {
        bool nv = (m98 == 0);
        m98 = nv;
        void* at = SP_GetSystemAT();
        void* r = at ? ((AudioAT*)at)->Slot20() : 0;
        uint32_t id = nv ? 0xea0588f8u : 0x2dd00402u + 0xea0588f8u;
        SP_KillSetiEffects(id, r);
        if (m7c) {
            IWindow* b = (IWindow*)FUN_005c2570(&m7c);
            b->SetStateFlag(4, nv);
        }
        goto tail;
    }
tail:
    if (m5c) FUN_00662b00((char*)this - 4);
    return true;
def:
    return false;
}



// @ 0x00663e50
void cSPUIFeedListCategory::FUN_00663e50()
{
    if (md4) {
        ((D4Obj*)md4)->FUN_00829d30();
        void* p = md4;
        if (p) { md4 = 0; ((cSPUILayout_s0066_3be0*)p)->Release(); }
    }
    if (m70) {
        void* self = (char*)this + 4;
        m70->AttachProc(self);
    }
    if (m64) {
        m64->Shutdown(true);
        cSPUILayout_s0066_3be0* p = m64;
        if (p) { m64 = 0; p->Release(); }
    }
    if (mbc) {
        void* h = mbc;
        uint32_t a = mc0, b = mc4, c = mc8, d = mcc;
        mbc = 0;
        EA_RemoveHandler(h, a, b, c, d);
    }
}



// @ 0x00663ef0
void cSPUIFeedListCategory::FUN_00663ef0(int param)
{
    if (!m7c) return;
    float* p = m7c->GetRect();
    float span = p[2] - p[0];
    float total = m58 + *(float*)&g_fp1;
    int n = (int)((m8c - m88));
    for (int i = 0; i < n; ++i) {
        FeedItem* it = m88[i];
        it->FUN_00668550(param);
        float h = 0.0f;
        (void)h;
        float r[4];
        (void)span;
        it->FUN_00666590(r);
    }
    m5c = total + *(float*)&g_fp1;
    m7c->SetFlag(1, m9c);
    (void)span;
}



// @ 0x00664390
void cSPUIFeedListCategory::FUN_00664390(float a, float b, float c, float d)
{
    struct D4 { char pad0[9]; bool f9; bool fa; };
    D4* d4 = (D4*)md4;
    if (d4 && (d4->f9 || d4->fa)) {
        FUN_008294c0((char*)this + 0x48, 1);
    } else if (m74) {
        float r[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        m74->SetArea(r);
        float* p = m74->GetRect();
        m38 = p[0];
        m3c = p[1];
        m40 = p[2];
        m44 = p[3];
    }
    m28 = a;
    m2c = b;
    m30 = c;
    m34 = d;
}



// @ 0x00664440
void cSPUIFeedListCategory::FUN_00664440()
{
    int n = (int)((m8c - m88));
    for (int i = 0; i < n; ++i)
        m88[i]->FUN_00667690(1);
}



// @ 0x00664480
void cSPUIFeedListCategory::FUN_00664480(bool expanded)
{
    if (expanded == m9c) return;
    m9c = expanded;
    IWindow* btn = m80 ? m80->FindWindow(0x8ed27e7a) : 0;
    ((IWindow*)btn)->SetStateFlag(4, m9c);
    if (m60) FUN_00662b00(this);
}



// @ 0x006644e0
void cSPUIFeedListCategory::FUN_006644e0(bool b)
{
    if (m78) m78->SetFlag(1, b);
    if (m80) {
        m80->SetFlag(1, b);
        float v;
        if (b) {
            float* p = m80->GetArea();
            v = p[3] - p[1];
        } else {
            v = 0.0f;
        }
        m58 = v;
    }
    if (m84) m84->SetFlag(1, b);
}



// @ 0x00664550
bool cSPUIFeedListCategory::FUN_00664550(bool b)
{
    if (!b) return m14;
    if (m14 && m60 && ((PredObj*)m60)->FUN_00a98020()) return true;
    return false;
}



// @ 0x00664580
void cSPUIFeedListCategory::FUN_00664580(bool b)
{
    m15 = b;
    if (m70) m70->SetFlag(2, m15);
    if (m78) m78->SetFlag(2, m15);
    if (m7c) m7c->SetFlag(2, m15);
    if (m80) m80->SetFlag(2, m15);
    if (m84) m84->SetFlag(2, m15);
}



// @ 0x00664610
FeedItem* cSPUIFeedListCategory::FUN_00664610(uint32_t idx)
{
    FeedItem* result = 0;
    if (idx < (uint32_t)((m8c - m88)))
        result = m88[idx];
    return result;
}



// @ 0x00664640
FeedItem* cSPUIFeedListCategory::FUN_00664640(int id)
{
    int n = (int)(m8c - m88);
    int i = 0;
    FeedItem** p = m88;
    if (n > 0) {
        do {
        FeedItem* e = *p;
        if (e && e->m17c == id) return e;
            ++i; ++p;
        } while (i < n);
    }
    return 0;
}



// @ 0x00664680
FeedItem* cSPUIFeedListCategory::FUN_00664680(int id)
{
    int n = (int)(m8c - m88);
    int i = 0;
    FeedItem** p = m88;
    if (n > 0) {
        do {
        FeedItem* e = *p;
        if (e && e->m134 == id) return e;
            ++i; ++p;
        } while (i < n);
    }
    return 0;
}



// @ 0x006646c0
FeedItem* cSPUIFeedListCategory::FUN_006646c0(int id)
{
    int n = (int)(m8c - m88);
    int i = 0;
    FeedItem** p = m88;
    if (n > 0) {
        do {
        FeedItem* e = *p;
        if (e && e->m188 == id) return e;
            ++i; ++p;
        } while (i < n);
    }
    return 0;
}



// @ 0x00664700
void __cdecl FUN_00664700(AutoRefCountT* first, AutoRefCountT* last)
{
    if (first == last) return;
    AutoRefCountT* i = first + 1;
    if (i == last) return;
    do {
        FeedItem* value = i->mpObject;
        if (value) value->AddRef();
        AutoRefCountT* j = i;
        while (j != first) {
            FeedItem* prev = (j - 1)->mpObject;
            if (!value || !prev) break;
            if (value->mGroup == prev->mGroup) {
                if (!value->mName || !prev->mName) break;
                if (_wcsicmp(value->mName, prev->mName) >= 0) break;
            } else if (!(prev->mGroup < value->mGroup)) {
                break;
            }
            AssignRef(*j, prev);
            --j;
        }
        AssignRef(*j, value);
        if (value) value->Release();
        ++i;
    } while (i != last);
}



// @ 0x00664800
void __cdecl FUN_00664800(AutoRefCountT* first, AutoRefCountT* last)
{
    if (first == last) return;
    AutoRefCountT* i = first;
    do {
        FeedItem* value = i->mpObject;
        if (value) value->AddRef();
        AutoRefCountT* j = i;
        while (j != first) {
            FeedItem* prev = (j - 1)->mpObject;
            if (!value || !prev) break;
            if (value->mGroup == prev->mGroup) {
                if (!value->mName || !prev->mName) break;
                if (_wcsicmp(value->mName, prev->mName) >= 0) break;
            } else if (!(prev->mGroup < value->mGroup)) {
                break;
            }
            AssignRef(*j, prev);
            --j;
        }
        AssignRef(*j, value);
        if (value) value->Release();
        ++i;
    } while (i != last);
}



// @ 0x00664960
template <typename T, typename Compare> __declspec(noinline) void promote_heap(T* first, int topPosition, int position, const T& value)
{
    Compare compare;
    for (int parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}



// @ 0x00664a60
bool cSPUIFeedListCategory::FUN_00664a60(uint32_t id, void* msg)
{
    if (id != 0xb3d53f95) return false;
    if (!msg) return false;
    FeedItem* target = *(FeedItem**)((char*)msg + 0x10);
    if (!target) {
        if (*(unsigned char*)((char*)msg + 0x14) != 0)
            target = FUN_00664680(*(int*)((char*)msg + 0xc));
        else
            target = FUN_00664640(*(int*)((char*)msg + 0xc));
        if (!target) return false;
    }
    FeedItem** it = m88;
    FeedItem** end = m8c;
    for (; it != end; ++it)
        if (*it == target) break;
    if (it != end) FUN_00664480(true);
    return false;
}


// @ 0x00664c90
void* cSPUIFeedListCategory_s0066_4c90::Ctor()
{
    char* p = (char*)this;
    *(void* volatile*)&p[4] = &gVtA;
    *(void* volatile*)&p[8] = &gVtB;
    *(void**)(p + 0xc) = &gVtC;
    *(int*)(p + 0x10) = 0;
    *(void**)(p + 0) = &gVtD;
    *(void**)(p + 4) = &gVtE;
    *(void**)(p + 8) = &gVtF;
    *(void**)(p + 0xc) = &gVtG;
    *(char*)(p + 0x14) = 0;
    *(char*)(p + 0x15) = 0;
    *(void**)(p + 0x20) = (void*)0x1667bae;
    *(void**)(p + 0x18) = (void*)0x1667bac;
    *(void**)(p + 0x1c) = (void*)0x1667bac;
    *(float*)(p + 0x58) = 0.0f;
    *(float*)(p + 0x5c) = 0.0f;
    *(void**)(p + 0x60) = 0; *(void**)(p + 0x64) = 0; *(void**)(p + 0x68) = 0;
    *(void**)(p + 0x6c) = 0; *(void**)(p + 0x70) = 0; *(void**)(p + 0x74) = 0;
    *(void**)(p + 0x78) = 0; *(void**)(p + 0x7c) = 0; *(void**)(p + 0x80) = 0;
    *(void**)(p + 0x84) = 0; *(void**)(p + 0x88) = 0; *(void**)(p + 0x8c) = 0;
    *(void**)(p + 0x90) = 0;
    *(char*)(p + 0x9c) = 1;
    *(void**)(p + 0xa0) = 0; *(void**)(p + 0xa4) = 0; *(void**)(p + 0xa8) = 0;
    *(void**)(p + 0xb4) = 0; *(void**)(p + 0xb8) = 0; *(void**)(p + 0xbc) = 0;
    *(void**)(p + 0xc0) = 0; *(void**)(p + 0xc4) = 0; *(void**)(p + 0xc8) = 0;
    *(void**)(p + 0xcc) = 0;
    *(char*)(p + 0xd0) = 0;
    *(void**)(p + 0xd4) = 0;
    return p;
}


// @ 0x00664dc0
void cSPUIFeedListCategory_s0066_4c90::Dtor()
{
    char* p = (char*)this;
    *(void**)(p + 0) = &gVtD;
    *(void**)(p + 4) = &gVtE;
    *(void**)(p + 8) = &gVtF;
    *(void**)(p + 0xc) = &gVtG;
    void* a = *(void**)(p + 0xd4);
    if (a) (*(FnP)Vslot(a, 8))(a);
    void* h = *(void**)(p + 0xbc);
    if (h) { *(void**)(p + 0xbc) = 0; EA_Messaging_RemoveHandler(h, *(void**)(p + 0xc0), *(void**)(p + 0xc4), *(void**)(p + 0xc8), *(void**)(p + 0xcc)); }
    a = *(void**)(p + 0xb8); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0xa0); if (a && *(int*)((char*)a - 4) != 0) EASTL_allocator_deallocate(a);
    { void* v = p + 0x88; (*(void(__thiscall*)(void*))0xae6970)(v); }
    a = *(void**)(p + 0x84); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x80); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x7c); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x78); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x74); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x70); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x6c); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x68); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x64); if (a) (*(FnP)Vslot(a, 8))(a);
    a = *(void**)(p + 0x60); if (a) (*(FnP)Vslot(a, 4))(a);
    { char* b = *(char**)(p + 0x18); int d = *(int*)(p + 0x20) - (int)b; d &= ~1; if (d > 2 && b) EASTL_allocator_deallocate(b); }
    *(void**)(p + 0xc) = &gVtC;
    *(void**)(p + 4) = &gVtH;
    *(void**)(p + 0) = &gVtB;
}


// @ 0x00664f30
int* PartitionByFeed(int* first, int* last, int* key)
{
    int* lo = first;
    do {
        while (lo < last) {
            int* v = (int*)*lo;
            if (!v || !key) break;
            int* kv = (int*)0;
            (void)kv;
            if (v[0x31] != *(int*)((char*)key + 0xc4)) { break; }
            const wchar_t* sa = (const wchar_t*)v[6];
            const wchar_t* sb = (const wchar_t*)key[6];
            if (!sa || !sb) break;
            if (_wcsicmp(sa, sb) < 0) { ++lo; break; }
            break;
        }
        while (last > lo) {
            int* v = (int*)*(last - 1);
            if (!key || !v) break;
            if (key[0x31] != *(int*)((char*)v + 0xc4)) { break; }
            const wchar_t* sa = (const wchar_t*)key[6];
            const wchar_t* sb = (const wchar_t*)v[6];
            if (!sa || !sb) break;
            if (_wcsicmp(sa, sb) < 0) { --last; continue; }
            break;
        }
        if (lo >= last) break;
        FUN_00b2af00(lo, last - 1);
        ++lo;
    } while (true);
    if (key) (*(FnP)Vslot(key, 4))(key);
    return lo;
}


// @ 0x006650c0
void VecAutoRef4::FUN_006650c0(void* pos, void* value)
{
    char* p = (char*)this;
    char* end = *(char**)(p + 4);
    if (end != *(char**)(p + 8)) {
        char* val = (char*)value;
        if (pos <= val && val < end) val += 4;
        if (end) {
            void* last = *(void**)(end - 4);
            *(void**)end = last;
            if (last) (*(FnP)Vslot(last, 0))(last);
        }
        FUN_00ac97a0(pos, end - 4, end);
        void* v = *(void**)value;
        void* old = *(void**)pos;
        if (v != old) {
            if (v) (*(FnP)Vslot(v, 0))(v);
            *(void**)pos = v;
            if (old) (*(FnP)Vslot(old, 4))(old);
        }
        *(char**)(p + 4) = end + 4;
        return;
    }
    int n = (int)(end - *(char**)p) >> 2;
    int nc = n ? n * 2 : 1;
    void* buf = 0;
    if (nc) buf = EASTL_allocator_allocate(nc * 4, "Editor", 0, 0, (const char*)0x13ebb38, 0xd1);
    if (buf) {
        char* begin = *(char**)p;
        char* posc = (char*)pos;
        char* e = *(char**)(p + 4);
        char* d = (char*)buf;
        for (char* s = begin; s < posc; s += 4, d += 4) *(void**)d = *(void**)s;
        { void* v = *(void**)value; *(void**)d = v; if (v) (*(FnP)Vslot(v, 0))(v); d += 4; }
        for (char* s = posc; s < e; s += 4, d += 4) *(void**)d = *(void**)s;
        if (begin && *(int*)(begin - 4) != 0) EASTL_allocator_deallocate(begin);
        *(char**)(p + 4) = (char*)buf + (int)(end - begin);
        *(void**)p = buf;
        *(char**)(p + 8) = (char*)buf + nc * 4;
    }
}


// @ 0x00665210
void FUN_00665210(void* first, void* mid, void* last, void* cmp)
{
    FUN_00665000(first, mid, cmp);
    while (mid < last) {
        void* v = *(void**)mid;
        void* f = *(void**)first;
        bool less = false;
        if (v && f) {
            int a = *(int*)((char*)v + 0xc4), b = *(int*)((char*)f + 0xc4);
            if (a != b) less = a < b;
            else {
                const wchar_t* sa = *(const wchar_t**)((char*)v + 0x18);
                const wchar_t* sb = *(const wchar_t**)((char*)f + 0x18);
                if (sa && sb && _wcsicmp(sa, sb) < 0) less = true;
            }
        }
        if (less) {
            FUN_00664ad0(first, 0, ((char*)mid - (char*)first) >> 2, 0);
        }
        mid = (char*)mid + 4;
    }
    FUN_00665050(first, mid, cmp);
}


// @ 0x00665330
void Vec8::push_back(void* val)
{
    char* e = (char*)end;
    if (e < (char*)cap) {
        end = e + 8;
        if (e) { *(uint32_t*)e = *(uint32_t*)val; *((uint32_t*)e + 1) = ((uint32_t*)val)[1]; }
        return;
    }
    FUN_00601b40(e, val);
}


// @ 0x00665410
void* cSPUIFeedListCategory_s0066_4c90::Refresh(int param, int* count)
{
    char* p = (char*)this;
    (void)count;
    int n = (int)((*(char**)(p + 0x8c) - *(char**)(p + 0x88)) >> 2);
    (void)n;
    if (param == -1) param = (*(int*)(p + 0x8c) - *(int*)(p + 0x88)) >> 2;
    void* pm = SP_PropertyManager();
    void* local = 0;
    (*(char(__thiscall*)(void*, int, void**))Vslot(pm, 0x2c))(pm, 0x4e5892eb, &local);
    return 0;
}


// @ 0x006657a0
void cSPUIFeedListCategory_s0066_4c90::ShutdownChildren()
{
    char* v = (char*)this + 0x88;
    int n = (int)((*(char**)(v + 4) - *(char**)v) >> 2);
    for (int i = 0; i < n; ++i)
        ((CatChild*)(*(void**)(*(int*)v + i * 4)))->FUN_006664f0();
    ((VecAutoRef4*)v)->erase(*(void**)v, *(void**)(v + 4));
}


// @ 0x00665870
void FUN_00665870(char* p)
{
    for (int i = 0; i < (int)((*(char**)(p + 0x8c) - *(char**)(p + 0x88)) >> 2); ++i)
        FUN_00669410(p);
}


// @ 0x00665c50
void cSPUIFeedListCategory_s0066_4c90::Populate()
{
    char* p = (char*)this;
    if (!*(void**)(p + 0x7c) || !*(void**)(p + 0xb8)) return;
    char str[0x14];
    FUN_006b5060(str);
    if (*(void**)(p + 0x78)) {
        if (FUN_006a1360(*(void**)(p + 0xb8), 0x744717c2, str))
            FUN_006b55c0(str);
    }
    int a = 0;
    void* b = 0;
    if (FUN_006a0ae0(*(void**)(p + 0xb8), 0x744717c1, &a, &b)) {
        for (int i = 0; i < a; ++i)
            Refresh(*(int*)((char*)b + i * 0xc), 0);
    }
    FUN_006657f0(*(void**)(p + 0x8c), *(void**)(p + 0x88), b);
    FUN_006b5240(str);
}

// @ 0x00665d30
void ReloadCallback(CFull* self, void* layout, char reload)
{
  if (!reload) {
    int n = (int)(((int)self->m8c - (int)self->m88) >> 2);
    for (int i = 0; i < n; i++)
      ((CFeed*)((void**)self->m88)[i])->Teardown();
    vec_erase(&self->m88, self->m88, self->m8c);
    if (self->m7c) ((FnV1p)((VObj*)self->m7c)->vt[66])(self->m7c, (char*)self + 4);
    if (self->m74) ((FnV1p)((VObj*)self->m74)->vt[66])(self->m74, (char*)self + 4);
    if (self->m80) ((FnV1p)((VObj*)self->m80)->vt[66])(self->m80, (char*)self + 4);
    if (self->m84) ((FnV1p)((VObj*)self->m80)->vt[66])(self->m80, (char*)self + 4);
    if (self->md4) {
      FUN_00829d30();
      void** p = &self->md4;
      if (*p) { *p = 0; ((FnV1)((VObj*)*p)->vt[2])(*p); }
    }
    if (self->m70) { void* p = self->m70; self->m70 = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    if (self->m74) { void* p = self->m74; self->m74 = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    if (self->m78) { void* p = self->m78; self->m78 = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    if (self->m7c) { void* p = self->m7c; self->m7c = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    if (self->m80) { void* p = self->m80; self->m80 = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    if (self->m84) { void* p = self->m84; self->m84 = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    return;
  }
  SetRefSlot(&self->m70, FindWindowByIDF(layout, 0xf3c6dc19, true));
  SetRefSlot(&self->m74, FindWindowByIDF(layout, 0x684be28, true));
  SetRefSlot(&self->m78, FindWindowByIDF(layout, 0xb3c6efca, true));
  SetRefSlot(&self->m7c, FindWindowByIDF(layout, 0xf3c839e5, true));
  SetRefSlot(&self->m80, FindWindowByIDF(layout, 0xb3c6efc2, true));
  SetRefSlot(&self->m84, FindWindowByIDF(layout, 0xb48e2560, true));
  if (self->m78)
    ((FnV1i)((VObj*)self->m78)->vt[32])(self->m78, self->m18);
  if (self->m70) {
    float* a = (float*)((FnV0)((VObj*)self->m68)->vt[14])(self->m68);
    float rect[4];
    rect[0] = a[2] - a[0];
    rect[1] = a[3] - a[1];
    float* b = (float*)((FnV0)((VObj*)self->m70)->vt[14])(self->m70);
    rect[3] = b[3] - b[1];
    rect[2] = 0.0f;
    ((FnV1p)((VObj*)self->m70)->vt[24])(self->m70, rect);
    self->m28 = rect[0]; self->m2c = rect[1];
    self->m30 = rect[2]; self->m34 = rect[3];
  }
  if (self->m74) {
    float out[4];
    FUN_00805ef0(out, self->m74);
    self->m38 = out[0]; self->m3c = out[1];
    self->m40 = out[2]; self->m44 = out[3];
    self->m48 = self->m38; self->m4c = self->m3c;
    self->m50 = self->m40; self->m54 = self->m44;
    ((FnV1p)((VObj*)self->m74)->vt[65])(self->m74, (char*)self + 4);
  }
  if (self->m7c)
    ((FnV1p)((VObj*)self->m7c)->vt[65])(self->m7c, (char*)self + 4);
  if (self->m80) {
    float* a = (float*)((FnV0)((VObj*)self->m80)->vt[13])(self->m80);
    self->m58 = a[3] - a[1];
    ((FnV1p)((VObj*)self->m80)->vt[65])(self->m80, (char*)self + 4);
  }
  if (self->m84)
    ((FnV1p)((VObj*)self->m84)->vt[65])(self->m84, (char*)self + 4);
  Dlg* d = new("Sporepedia", 0, 0, 0, 0) Dlg();
  SetRefSlot(&self->md4, d);
  ((FnV1p)((VObj*)self->md4)->vt[66])(self->md4, self->m74);
  FUN_00829c50(self->md4, self->m74, self->m78, self->m6c);
  Populate(self);
}

// @ 0x006661d0
bool CCat::Init(void* a, void* b, int c)
{
  SetRefSlot(&m68, a);
  SetRefSlot(&m6c, b);
  void* pm = PropertyManager();
  if (mb8) {
    ((IRef2*)mb8)->Release();
    mb8 = 0;
  }
  ((FnVb2i)((VObj*)pm)->vt[11])(pm, c, 0x6b38241, &mb8);
  mb4 = (void*)c;
  SetRefSlot(&m60, a);
  m14 = true;
  m15 = true;
  int r = (int)((FnV0i)((VObj*)ConfigManager())->vt[12])(ConfigManager(), 0x5de7b4a);
  if (r == 1 && mb8) {
    void* tmp = 0;
    bool chk = ((FnVb1i)((VObj*)mb8)->vt[9])(mb8, 0x6397993, &tmp);
    if (chk && *(short*)((char*)tmp + 0x12) == 1) {
      if (*GetPropertyAsKeyArray() == 0) return false;
    }
  }
  Dlg* d = new("Sporepedia", 0, 0, 0, 0) Dlg();
  SetRefSlot(&m64, d);
  int arr[3];
  arr[0] = 0x5a71fb79; arr[1] = 0x510a95b; arr[2] = (int)0x1527554;
  InitLayout(m64, arr, 1, 0x5b598fa);
  SetParentWinF(m64, m68, 1, 0x5b598fa);
  SetReloadCB(m64, (void*)&ReloadCallback, this);
  ReloadCallback((CFull*)this, m64, 1);
  void* ms = MessageServer();
  mbc = (int)ms;
  mc0 = (int)this;
  mc4 = 0x1400244;
  mc8 = 1;
  mcc = 0;
  if (ms) ((FnV2i)((VObj*)ms)->vt[9])(ms, (int)this, 0xb3d53f95);
  return true;
}
