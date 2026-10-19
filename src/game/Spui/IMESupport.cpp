// src/game/Spui/IMESupport.cpp -- migrated from slice(s) s007f5300, s007f42e0, s007f3380, s007f2340 by tools/migrate/rewrite.py
// Object file: Spui/IMESupport.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* SPGetMessageServer();
extern void* UTFWinGetManager();
#include <new>
#include <intrin.h>

// ---- items of slice s007f2340 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
extern void* SPGetMessageServer();
extern void* UTFWinGetManager();
struct IMEProxy {
  char pad0[8];
  bool mbInitialized;      // +0x08
  char pad1[7];
  void* mpMessageServer;   // +0x10
  char pad2[0xc];
  void* mpIMEServer;       // +0x20
  void* mpWinMgr;          // +0x24
  bool Init(void* server, int);
  void Shutdown();
  void SetupDefaultFonts();
};
// ---- items of slice s007f2340 end

// ---- items of slice s007f3380 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* UTFWinGetMgr();
struct IMEComp {
  bool HandleMessage(int msg, void* arg);
};
struct IMECand {
  bool HandleMessage(int msg, void* arg);
};
struct SubObj {
  void* Get();
};
struct IMEComp3 {
  char pad[0x20c];
  SubObj mSub;  // +0x20c
  void Helper(int param);
};
struct IMEProxy2 {
  char pad0[8];
  bool mbInitialized;          // +0x08
  char pad1[7];
  void* mpMessageServer;       // +0x10
  char pad2[0xc];
  void* mpIMEServer;           // +0x20
  void* mpWinMgr;              // +0x24
  char pad3[8];
  void* mpWinComposition;      // +0x30
  char pad4[8];
  void* mpWinCandidateList;    // +0x3c
  void ShutdownCandidateList();
  void ShutdownCandidateListImpl();
  void ShutdownComposition();
  bool Shutdown();
};
struct TS {
  void LayoutLine(int text, int style, float a, float b, int len);
  void* GetLineLayout();
};
struct IMECompColors {
  char pad0[4];
  char mAt4[4];        // +0x04 (subobject with a vtable)
  char pad1[0x20c - 8];
  char mAt20c[4];      // +0x20c (subobject with a vtable)
  char pad2[0x6a8 - 0x210];
  int c6a8;            // +0x6a8
  int c6ac;            // +0x6ac
  int c6b0;            // +0x6b0
  int c6b4;            // +0x6b4
  void SetWindowColors();
};
struct IMEC {
  char pad[0x68c];
  void* p68c;   // +0x68c
  bool OnChar(int, unsigned short ch);
};
// ---- items of slice s007f3380 end

// ---- items of slice s007f42e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vt_1414fd0;
extern void* g_vt_1414eb0;
extern void* g_vt_1414db8;
extern void* g_vt_1414dac;
extern void* g_vt_13eb394;
extern void* g_vt_1414d84;
extern void* g_vt_1414ba4;
extern void* g_vt_13eb90c;
extern const wchar_t g_ja_jp[] = L"ja-jp";
extern const char g_name_IMEServer[] = "UI/IME/IMEServer";
extern const char g_name_IMEProxy[] = "UI/IME/IMEProxy";
extern const char g_name_IMECandidateList[] = "UI/IME/IMECandidateList";
extern const char g_name_mpWinComposition[] = "UI/IME/mpWinComposition";
extern const float g_compDx;
extern const float g_compDy;
#pragma intrinsic(_InterlockedExchange)
typedef unsigned short wchar16;
#define VTOBJ(p) (*(void***)(p))
typedef void*  (__thiscall *FPR0)(void*);
typedef void   (__thiscall *FV0)(void*);
typedef void   (__thiscall *FVI)(void*, int);
typedef void   (__thiscall *FVP)(void*, void*);
typedef void*  (__thiscall *FPRI)(void*, int);
typedef char   (__thiscall *FPC0)(void*);
typedef char   (__thiscall *FPCI)(void*, int);
void* __cdecl FUN_009512c0();
void* __cdecl FUN_009512d0(int size, int align, const char* name, void* caller);
void* __cdecl op_new(int size, const char* name, int a, int b, int c, int d);
void* __cdecl FUN_0067de40();
void* __cdecl SP_Canvas();
void* __cdecl FUN_0067dce0();
void* __cdecl EA_Messaging_GetServer();
void* __cdecl EA_UTFWin_GetManager();
void* __cdecl interface_cast(void* window);
bool  __cdecl DoFindNode(void* table, const wchar_t* key);
void  __cdecl deallocate(void* p);
struct WinTextEditCtor { void Ctor(); };
struct IMEServerWin32Ctor {
    void* Ctor();
    void SetCanvas(void*);
    void SetSomething(void*);
};
struct IMECandidateListCtor_s007f_42e0 { void* Ctor(); };
struct IMECandidateListInit { void Init(void* msg); };
struct IMECompositionInit_s007f_42e0 { void Init(void* msg); };
struct IMECompositionCtorStub { IMECompositionCtorStub* Construct(); };
struct IMEProxyInit { bool Init(void* server, void* svc); };
struct IMEProxyMisc { void M1(); void M2(); };
struct AutoRefAssign { void* Assign(void* p); };
struct IMEProxyShutdown { void Shutdown(); };
struct WideFixedBuf {
    wchar16* mBegin;      // +0x00
    wchar16* mEnd;        // +0x04
    wchar16* mCapacity;   // +0x08
    int      mPad;        // +0x0c
    wchar16* mFixed;      // +0x10
    wchar16  mFixedBuf[0x100]; // +0x14
    WideFixedBuf(const wchar16* s);
    WideFixedBuf& append(const wchar16* first, const wchar16* last);
};
static inline uint32_t WLen(const wchar16* s)
{
    const wchar16* p = s;
    while (*p)
        ++p;
    return (uint32_t)(p - s);
}
struct IMEProxyS {
    char     pad0[8];
    bool     mbInitialized;               // +0x08
    uint32_t mnTickCount;                 // +0x0c
    void*    mpMessageServer;             // +0x10
    int32_t  mPtX;                        // +0x14
    int32_t  mPtY;                        // +0x18
    bool     mbNonTextEditCompositionEnabled; // +0x1c
    void*    mpIMEServer;                 // +0x20
    void*    mpWinMgr;                    // +0x24
    void*    mpWinLastFocus;              // +0x28
    bool     mbWinCompositionEnabled;     // +0x2c
    void*    mpWinComposition;            // +0x30
    void*    mpWinCompositionTextStyle;   // +0x34
    bool     mbWinCandidateListEnabled;   // +0x38
    void*    mpWinCandidateList;          // +0x3c
    void*    mpWinCandidateListTextStyle; // +0x40

    bool Update();
    void StartCandidateList();
    void StartComposition();
    bool HandleMessage(uint32_t msgId, void* param);
    void SetupDefaultFonts();             // external 0x7F31E0
};
struct WinTextEditDtorStub { void Dtor(); };
struct IMECompositionS {
    char pad0[0x700];
    IMECompositionS* Construct();
    void Dtor();
    void SetFlag(int x);   // @ 0x7F4630
};
struct IMEServiceS {
    void* vftable;       // +0x00
    void* mpIMEServer;   // +0x04
    void* mpIMEProxy;    // +0x08
    bool Init();
};
extern void* g_pIMEProxy;   // 0x01542214
extern void* g_pIMEServer;  // 0x01542210
// ---- items of slice s007f42e0 end


// ---- items of slice s007f5300 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_0095fba0();
void  __cdecl IMEComp_CalculateTextSize(void* out, void* a, int b, void* c, void* d);
struct Callee {
    void  f();   // 0x0095bb20 (equiv t3)
    void  f(int);
    void  f(void*);
    void  f(void*, int);
    void  f(int, int);
    void  f(void*, int, int);
    void  f(void*, void*, int, int);
    void  f(float);
    void  f(float, float);
    void  f(float, float, float);
    void  f6(float, float, float, float, float, float);   // 0x007fd650 (equiv t3)
    void  resize(int);
    void* ctor();   // 0x00804e20 (equiv t3)
    void* ctor2(int, int);   // 0x0093a560 (equiv t3)
    void* ctorff(float, float);
    void* ctorf(float);   // 0x007fd610 (equiv t3)
    bool  b();
    bool  b(void*);
    void* p();
    void* p(int);   // 0x0095bc10 (equiv t3)
    int64_t i64();   // 0x0093a3a0 (equiv t3)
};
struct VecCallee { void resize(int); };
struct Obj {
    void  M5300(void* p);
    int   M53C0(void* p);
    bool  M53D0();
    void* M5410(int type);
    bool  M5460(int v);
    int   M5490();
    void  M54B0(int v);
    bool  M54E0();
    void  M55B0();
    bool  M55F0(void* ev);
    bool  M5660(void* p);
    void  M5690();
    void  M56C0();
    float M56E0();
    bool  M5710(float v);
    void  M58E0();
    bool  M5990();
    bool  M59E0(void* obj, int a2, int a3, int a4);
    bool  M5A60(void* ctx);
    bool  M5BD0(void* out, int, int);
    Obj*  M5C20();
    void  M5D00();
    void* M5FF0(char flags);
};
namespace __equiv_ann1 {
struct VecCallee {
    void resize();   // 0x004c0410 (equiv t2)
};
}
// ---- items of slice s007f5300 end

// @ 0x007f30e0
bool IMEProxy::Init(void* server, int)
{
  if (mbInitialized) return true;
  mbInitialized = true;
  mpMessageServer = SPGetMessageServer();
  mpIMEServer = server;
  mpWinMgr = UTFWinGetManager();
  ((void(__thiscall*)(void*, void*, int))VSLOT(mpMessageServer, 0x20))(mpMessageServer, this, 0x2ac44c0e);
  ((void(__thiscall*)(void*, void*, int))VSLOT(mpMessageServer, 0x20))(mpMessageServer, this, 0x2ac44c11);
  ((void(__thiscall*)(void*, void*, int))VSLOT(mpMessageServer, 0x20))(mpMessageServer, this, 0x2ac44ed1);
  ((void(__thiscall*)(void*, void*, int))VSLOT(mpMessageServer, 0x20))(mpMessageServer, this, 0x2ac44ed4);
  return true;
}





// @ 0x007f31e0
void IMEProxy::SetupDefaultFonts()
{}





// @ 0x007f3320
void IMEProxy::Shutdown()
{
  void* p = mpIMEServer;
  if (p) {
    void* a = ((void*(__thiscall*)(void*))VSLOT(*(void**)((char*)p + 0x20c), 0x10))(*(void**)((char*)p + 0x20c));
    void* b = ((void*(__thiscall*)(void*))VSLOT(mpWinMgr, 4))(mpWinMgr);
    ((void(__thiscall*)(void*))VSLOT(p, 0x1c))(p);
    ((void(__thiscall*)(void*, void*))VSLOT(b, 0xdc))(b, a);
    mpIMEServer = 0;
    ((void(__thiscall*)(void*, int))VSLOT(p, 4))(p, 1);
  }
}




// @ 0x007f3380
void IMEProxy2::ShutdownCandidateListImpl()
{
  if (mpWinCandidateList != 0) {
    void* cand4 = (char*)mpWinCandidateList + 4;
    void* r = ((void*(__thiscall*)(void*))VSLOT(mpWinMgr, 4))(mpWinMgr);
    ((void(__thiscall*)(void*))VSLOT(mpWinCandidateList, 0x1c))(mpWinCandidateList);
    ((void(__thiscall*)(void*, void*))VSLOT(r, 0xdc))(r, cand4);
    void* p = mpWinCandidateList;
    if (p != 0) {
      mpWinCandidateList = 0;
      ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
    }
  }
}




// @ 0x007f33d0
void IMECompositionInit(void* self, int a, int b)
{
  (void)self;
  (void)a;
  (void)b;
}




// @ 0x007f35d0
void IMECompositionShutdown(void* self)
{
  (void)self;
}




// @ 0x007f36e0
bool IMEComp::HandleMessage(int msg, void* arg)
{
  switch (msg) {
    case 0x2ac44c14: {
      void* s = (char*)this - 0x658;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x94))(s, *(int*)((char*)arg + 8));
      break;
    }
    case 0x2ac44c1a: {
      void* s = (char*)this - 0x658;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x98))(s, *(int*)((char*)arg + 8));
      break;
    }
    case 0x2ac44c1b: {
      void* s = (char*)this - 0x658;
      ((void(__thiscall*)(void*))VSLOT(s, 0x8c))(s);
      break;
    }
    default:
      break;
  }
  return true;
}




// @ 0x007f3750
void IMECompositionBig(void* self, int a, int b)
{
  (void)self;
  (void)a;
  (void)b;
}




// @ 0x007f3a90
void IMECompColors::SetWindowColors()
{
  char* p = mAt20c;
  c6ac = (int)0xff000000;
  c6b0 = (int)0xff000000;
  c6a8 = 0xffffffff;
  c6b4 = 0xff0000f0;
  ((void(__thiscall*)(void*, int, int))VSLOT(p, 0x20))(p, 0, (int)0xff000000);
  ((void(__thiscall*)(void*, int, int))VSLOT(p, 0x20))(p, 1, (int)0xffefefef);
  ((void(__thiscall*)(void*, int))VSLOT(mAt4, 0xac))(mAt4, -1);
}




// @ 0x007f3b00
void* CalculateTextSize(void* out, int text, int style, int len, void* typesetter)
{
  if (text != 0 && len != 0) {
    TS* ts = (TS*)typesetter;
    ts->LayoutLine(text, style, 0.0f, 0.0f, len);
    char* ll = (char*)ts->GetLineLayout();
    *(float*)out = *(float*)(ll + 0x98);
    *(float*)((char*)out + 4) = *(float*)(ll + 0xa0) - *(float*)(ll + 0xa4);
    return out;
  }
  *(float*)out = 0.0f;
  *(float*)((char*)out + 4) = 0.0f;
  return out;
}




// @ 0x007f3b70
bool IMEC::OnChar(int, unsigned short ch)
{
  if (p68c) {
    struct L {
      int a;
      int b;
      int ch;
      int c;
    } l;
    l.a = 5;
    l.b = 0;
    l.ch = ch;
    l.c = 0;
    void* mgr = UTFWinGetMgr();
    ((void(__thiscall*)(void*, int, void*, void*, int))VSLOT(mgr, 0x10))(
        mgr, 0, (char*)p68c + 4, &l, 0);
    ((void(__thiscall*)(void*))VSLOT(this, 0x8c))(this);
  }
  return true;
}




// @ 0x007f3be0
void IMEComp3::Helper(int param)
{
  if (param) {
    SubObj* p = &mSub;
    void* r = p->Get();
    ((void(__thiscall*)(void*, void*, int))VSLOT(p, 0x8c))(p, r, 1);
  }
}




// @ 0x007f3c10
void IMECandidateListCtor(void* self)
{
  (void)self;
}




// @ 0x007f3cc0
void IMECandidateListDtor(void* self)
{
  (void)self;
}




// @ 0x007f3d20
void IMECandidateListPaint(void* self, int a, int b)
{
  (void)self;
  (void)a;
  (void)b;
}




// @ 0x007f4090
void IMECandidateListShutdown(void* self)
{
  (void)self;
}




// @ 0x007f4170
bool IMECand::HandleMessage(int msg, void* arg)
{
  switch (msg) {
    case 0x2ac44ed8: {
      void* s = (char*)this - 0x20c;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x88))(s, *(int*)((char*)arg + 8));
      break;
    }
    case 0x2ac44ef0: {
      void* s = (char*)this - 0x20c;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x8c))(s, *(int*)((char*)arg + 8));
      break;
    }
    default:
      break;
  }
  return true;
}




// @ 0x007f4200
void IMECandidateListScalarDtor(void* self, unsigned flags)
{
  (void)self;
  (void)flags;
}




// @ 0x007f4250
bool IMEProxy2::Shutdown()
{
  if (!mbInitialized) return true;
  bool hasCand = mpWinCandidateList != 0;
  mbInitialized = false;
  if (hasCand) ShutdownCandidateList();
  if (mpWinComposition) ShutdownComposition();
  ((void(__thiscall*)(void*, int))VSLOT(mpIMEServer, 0x14))(mpIMEServer, 0);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44c0e, 0xffffd8f1);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44c11, 0xffffd8f1);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44ed1, 0xffffd8f1);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44ed4, 0xffffd8f1);
  return true;
}



// @ 0x007f42e0
bool IMEProxyS::Update()
{
    if ((++mnTickCount & 3) != 0)
        return true;
    if (mpWinMgr == 0)
        return true;
    if (mpIMEServer == 0)
        return true;

    void* focus = ((FPR0)VTOBJ(mpWinMgr)[0x48 / 4])(mpWinMgr);
    bool bVar10 = false;
    if (mpWinLastFocus != focus) {
        char c = ((FPC0)VTOBJ(mpIMEServer)[0x1c / 4])(mpIMEServer);
        if (c != 0) {
            bool show = false;
            void* comp = mpWinComposition;
            if (comp) {
                void* q = (char*)comp + 0x20c;
                void* r = ((FPR0)VTOBJ(q)[0x10 / 4])(q);
                if (r != focus)
                    show = true;
            }
            void* cand = mpWinCandidateList;
            if (cand && (char*)cand + 4 != focus)
                show = true;
            if (show)
                ((FVI)VTOBJ(mpIMEServer)[0x20 / 4])(mpIMEServer, 0);
        }
        uint8_t localFlag = 0;
        void* mgr = FUN_0067de40();
        void* key = ((FPR0)VTOBJ(mgr)[0x14 / 4])(mgr);
        if (DoFindNode(key, g_ja_jp)) {
            interface_cast(focus);
        }
        if (((FPC0)VTOBJ(mpIMEServer)[0x1c / 4])(mpIMEServer) == 0) {
            int r = (int)((FPRI)VTOBJ(focus)[0xc / 4])(focus, (int)0xcf428691);
            if (r != 0) {
                ((FVI)VTOBJ(mpIMEServer)[0x20 / 4])(mpIMEServer, 1);
                bVar10 = true;
            }
        }
        mpWinLastFocus = focus;
        if (bVar10 || mbNonTextEditCompositionEnabled)
            bVar10 = true;
        bool bNonText = mbNonTextEditCompositionEnabled;
        mPtX = 0x7fffffff;
        mPtY = 0x7fffffff;
        if (!bNonText && focus != 0) {
            int r1 = (int)((FPRI)VTOBJ(focus)[0xc / 4])(focus, (int)0xcf428691);
            int r2 = 0, r3 = 0;
            if (r1 == 0) {
                r2 = (int)((FPRI)VTOBJ(mpWinLastFocus)[0xc / 4])(mpWinLastFocus, (int)0x1382be3e);
                if (r2 == 0)
                    r3 = (int)((FPRI)VTOBJ(mpWinLastFocus)[0xc / 4])(mpWinLastFocus, (int)0x9fedbcdb);
            }
            if (r1 != 0 || r2 != 0 || r3 != 0)
                bVar10 = true;
        }
        if (!bVar10) {
            struct Msg {
                uint32_t f0;
                uint32_t f4;
                uint32_t f8;
                uint32_t fc;
                uint32_t f10;
                void*    vt;      // +0x14
                uint32_t rc;      // +0x18
                uint32_t f1c;
                uint32_t f20;
                uint32_t a;       // +0x24
                uint32_t f28;
                uint32_t b;       // +0x2c
                uint32_t f30;
                void*    arg;     // +0x34
            } msg;
            msg.vt = &g_vt_13eb90c;
            msg.rc = 0;
            msg.a = 2;
            msg.b = 2;
            msg.arg = (void*)0xbe10a20;
            ((void(__thiscall*)(void*, int, Msg*, int))VTOBJ(mpMessageServer)[0x14 / 4])(
                mpMessageServer, (int)0xbe10a20, &msg, 0);
            if (*(uint32_t*)((char*)&msg + 0x18) != 0) {
                bool eq = (localFlag == 0);
                mPtX = *(int*)((char*)&msg + 0x24);
                mPtY = *(int*)((char*)&msg + 0x2c);
                if (!eq)
                    goto after;
            }
            if (((FPC0)VTOBJ(mpIMEServer)[0x1c / 4])(mpIMEServer)) {
                ((FVI)VTOBJ(mpIMEServer)[0x20 / 4])(mpIMEServer, 0);
            }
        after:
            ;
        }
    }
    return true;
}

// @ 0x007f4500
void IMEProxyS::StartCandidateList()
{
    if (!mbWinCandidateListEnabled)
        return;
    void* pCand = (char*)this + 0x3c;
    if (mpWinCandidateList != 0)
        return;
    void* window = ((FPR0)VTOBJ(mpWinMgr)[4 / 4])(mpWinMgr);
    void* caller = FUN_009512c0();
    void* mem = FUN_009512d0(0x244, 4, g_name_IMECandidateList, caller);
    void* obj;
    if (mem) {
        obj = ((IMECandidateListCtor_s007f_42e0*)mem)->Ctor();
    } else {
        obj = 0;
    }
    ((AutoRefAssign*)pCand)->Assign(obj);
    if (*(void**)pCand == 0)
        return;
    SetupDefaultFonts();
    void* win = (char*)*(void**)pCand + 4;
    ((FVP)VTOBJ(window)[0xd8 / 4])(window, win);
    ((FVP)VTOBJ(window)[0xe8 / 4])(window, win);
    ((void(__thiscall*)(void*, int, int))VTOBJ(win)[0x7c / 4])(win, 4, 0);
    ((IMECandidateListInit*)mpWinCandidateList)->Init(mpMessageServer);
}

// @ 0x007f45b0
void IMECompositionS::Dtor()
{
    *(void**)((char*)this + 0x0) = &g_vt_1414fd0;
    *(void**)((char*)this + 0x4) = &g_vt_1414eb0;
    *(void**)((char*)this + 0x20c) = &g_vt_1414db8;
    *(void**)((char*)this + 0x658) = &g_vt_1414dac;
    void* p1 = *(void**)((char*)this + 0x694);
    if (p1 && *(int*)((char*)p1 - 4) != 0)
        deallocate(p1);
    void* p2 = *(void**)((char*)this + 0x68c);
    if (p2)
        ((FV0)VTOBJ(p2)[4 / 4])(p2);
    void* p3 = *(void**)((char*)this + 0x688);
    if (p3)
        ((FV0)VTOBJ(p3)[4 / 4])(p3);
    *(void**)((char*)this + 0x658) = &g_vt_13eb394;
    ((WinTextEditDtorStub*)this)->Dtor();
}

// @ 0x007f4630
void IMECompositionS::SetFlag(int x)
{
    void* sub = (char*)this + 0x208;
    ((void(__thiscall*)(void*, int, int))VTOBJ(sub)[0x60 / 4])(sub, x, 1);
}

// @ 0x007f4710
bool IMEServiceS::Init()
{
    void* server = EA_Messaging_GetServer();
    void* mem = op_new(0xd8, g_name_IMEServer, 0, 0, 0, 0);
    void* srv;
    if (mem) {
        srv = ((IMEServerWin32Ctor*)mem)->Ctor();
    } else {
        srv = 0;
    }
    mpIMEServer = srv;
    ((IMEServerWin32Ctor*)srv)->SetCanvas(SP_Canvas());
    ((IMEServerWin32Ctor*)srv)->SetSomething(FUN_0067dce0());
    ((void(__thiscall*)(void*, void*))VTOBJ(srv)[0x18 / 4])(srv, server);
    ((FV0)VTOBJ(srv)[4 / 4])(srv);

    void* pmem = op_new(0x44, g_name_IMEProxy, 0, 0, 0, 0);
    void* proxy;
    if (pmem) {
        *(void**)pmem = &g_vt_1414d84;
        _InterlockedExchange((long*)((char*)pmem + 4), 0);
        *(void**)pmem = &g_vt_1414ba4;
        *(uint8_t*)((char*)pmem + 8) = 0;
        *(uint32_t*)((char*)pmem + 0xc) = 0;
        *(uint32_t*)((char*)pmem + 0x10) = 0;
        *(uint32_t*)((char*)pmem + 0x14) = 0x7fffffff;
        *(uint32_t*)((char*)pmem + 0x18) = 0x7fffffff;
        *(uint8_t*)((char*)pmem + 0x1c) = 0;
        *(uint32_t*)((char*)pmem + 0x20) = 0;
        *(uint32_t*)((char*)pmem + 0x24) = 0;
        *(uint32_t*)((char*)pmem + 0x28) = 0;
        *(uint8_t*)((char*)pmem + 0x2c) = 1;
        *(uint32_t*)((char*)pmem + 0x30) = 0;
        *(uint32_t*)((char*)pmem + 0x34) = 0;
        *(uint8_t*)((char*)pmem + 0x38) = 1;
        *(uint32_t*)((char*)pmem + 0x3c) = 0;
        *(uint32_t*)((char*)pmem + 0x40) = 0;
        proxy = pmem;
    } else {
        proxy = 0;
    }
    void* old = mpIMEProxy;
    if (proxy != old) {
        if (proxy)
            ((FV0)VTOBJ(proxy)[8 / 4])(proxy);
        mpIMEProxy = proxy;
        if (old)
            ((FV0)VTOBJ(old)[0xc / 4])(old);
    }
    void* cur = mpIMEProxy;
    if (cur == 0)
        return false;
    return ((IMEProxyInit*)cur)->Init(mpIMEServer, this);
}

// @ 0x007f4860
namespace Sims3 {
namespace UI {
void IMEServiceShutdown()
{
    if (g_pIMEProxy) {
        ((IMEProxyShutdown*)g_pIMEProxy)->Shutdown();
        void* p = g_pIMEProxy;
        if (p) {
            g_pIMEProxy = 0;
            ((FV0)VTOBJ(p)[0xc / 4])(p);
        }
    }
    if (g_pIMEServer) {
        void* p = g_pIMEServer;
        ((FV0)VTOBJ(p)[8 / 4])(p);
        if (g_pIMEServer) {
            ((void(__thiscall*)(void*, int))VTOBJ(g_pIMEServer)[0 / 4])(g_pIMEServer, 1);
        }
        g_pIMEServer = 0;
    }
}
}
}  // namespace Sims3::UI

// @ 0x007f48d0
WideFixedBuf::WideFixedBuf(const wchar16* s)
{
    wchar16* pFixed = mFixedBuf;
    mFixed = pFixed;
    mCapacity = pFixed + 0x100;
    mEnd = pFixed;
    mBegin = pFixed;
    *mBegin = 0;
    append(s, s + WLen(s));
}

// @ 0x007f4920
IMECompositionS* IMECompositionS::Construct()
{
    ((WinTextEditCtor*)this)->Ctor();
    *(void**)((char*)this + 0x658) = &g_vt_13eb394;
    *(uint8_t*)((char*)this + 0x660) = 0;
    *(uint32_t*)((char*)this + 0x664) = 0;
    *(void**)((char*)this + 0x0) = &g_vt_1414fd0;
    *(void**)((char*)this + 0x4) = &g_vt_1414eb0;
    *(void**)((char*)this + 0x20c) = &g_vt_1414db8;
    *(void**)((char*)this + 0x658) = &g_vt_1414dac;
    *(uint32_t*)((char*)this + 0x688) = 0;
    *(uint32_t*)((char*)this + 0x68c) = 0;
    *(uint32_t*)((char*)this + 0x694) = 0;
    *(uint32_t*)((char*)this + 0x69c) = 0;
    *(uint32_t*)((char*)this + 0x698) = 0;
    *(uint32_t*)((char*)this + 0x6b8) = 0;
    *(uint32_t*)((char*)this + 0x6a8) = 0xffffffff;
    *(uint32_t*)((char*)this + 0x6ac) = 0xffffffff;
    *(uint32_t*)((char*)this + 0x6b0) = 0xffffffff;
    *(uint32_t*)((char*)this + 0x6b4) = 0xffffffff;
    return this;
}

// @ 0x007f49b0
void IMECandidateListS_SetupWindow(void* self)
{
    (void)self;
}

// @ 0x007f50f0
void IMEProxyS::StartComposition()
{
    if (!mbWinCompositionEnabled)
        return;
    if (mpWinComposition != 0)
        return;
    void* window = ((FPR0)VTOBJ(mpWinMgr)[4 / 4])(mpWinMgr);
    void* caller = FUN_009512c0();
    void* mem = FUN_009512d0(0x6c0, 8, g_name_mpWinComposition, caller);
    void* obj;
    if (mem) {
        obj = ((IMECompositionCtorStub*)mem)->Construct();
    } else {
        obj = 0;
    }
    ((AutoRefAssign*)((char*)this + 0x30))->Assign(obj);
    void* comp = mpWinComposition;
    ((FVI)VTOBJ((char*)comp + 4)[0x50 / 4])((char*)comp + 4, (int)0x7a7c0bb);
    if (mpWinComposition == 0)
        return;
    SetupDefaultFonts();
    void* win = (char*)mpWinComposition + 4;
    ((FVP)VTOBJ(window)[0xd8 / 4])(window, win);
    ((FVP)VTOBJ(window)[0xe8 / 4])(window, win);
    if (mPtX != 0x7fffffff) {
        struct Rect { float l, t, r, b; } rc;
        rc.l = (float)mPtX;
        rc.t = (float)mPtY;
        rc.r = (float)mPtX + g_compDx;
        rc.b = (float)mPtY + g_compDy;
        ((void(__thiscall*)(void*, void*))VTOBJ((char*)mpWinComposition + 4)[0x6c / 4])(
            (char*)mpWinComposition + 4, &rc);
    }
    ((void(__thiscall*)(void*, int, int))VTOBJ((char*)mpWinComposition + 4)[0x7c / 4])(
        (char*)mpWinComposition + 4, 4, 0);
    ((IMECompositionInit_s007f_42e0*)mpWinComposition)->Init(mpMessageServer);
}

// @ 0x007f5220
bool IMEProxyS::HandleMessage(uint32_t msgId, void* param)
{
    switch (msgId) {
    case 0x2ac44ed1: {
        void* comp = mpWinComposition;
        if (comp) {
            char c = ((FPCI)VTOBJ((char*)comp + 0x20c)[0x48 / 4])((char*)comp + 0x20c, 0x80);
            if (c)
                return true;
        }
        StartCandidateList();
        return true;
    }
    case 0x2ac44c0e: {
        void* mgr = EA_UTFWin_GetManager();
        void* w = ((FPRI)VTOBJ(mgr)[0x48 / 4])(mgr, 0);
        if (w) {
            void* t = ((FPRI)VTOBJ(w)[0xc / 4])(w, (int)0xcf428691);
            if (t) {
                char c = ((FPCI)VTOBJ(t)[0x48 / 4])(t, 0x80);
                if (c) {
                    int* p = *(int**)((char*)param + 0x10);
                    *p = 2;
                    StartComposition();
                    return true;
                }
                int* p = *(int**)((char*)param + 0x10);
                *p = 1;
            }
        }
        StartComposition();
        return true;
    }
    case 0x2ac44c11:
        ((IMEProxyMisc*)this)->M1();
        return true;
    case 0x2ac44ed4:
        ((IMEProxyMisc*)this)->M2();
        return true;
    }
    return true;
}

// @ 0x007f5300
void Obj::M5300(void* p)
{
    if (p == 0)
        return;
    if (*(int*)p != 0) {
        void* t = FUN_0095fba0();
        int out[2];
        IMEComp_CalculateTextSize(out, *(void**)p, *(int*)((char*)p + 8),
                                  *(void**)((char*)this + 0x6b8), t);
        void* sub = (char*)this + 4;
        ((Callee*)sub)->f(*(void**)p);
    }
    if (*(int*)((char*)p + 4) != 0) {
        void* vec = (char*)this + 0x694;
        ((VecCallee*)vec)->resize(*(int*)((char*)p + 8));
        uint32_t n = (uint32_t)*(int*)((char*)p + 8);
        for (uint32_t i = 0; i < n; ++i) {
            uint8_t* src = (uint8_t*)*(void**)((char*)p + 4);
            uint8_t* dst = (uint8_t*)*(void**)((char*)this + 0x694);
            dst[i] = src[i];
            if (dst[i] >= 4)
                dst[i] = 0;
        }
    }
    ((Callee*)this)->f();
    ((Callee*)this)->f(p);
    void* sub = (char*)this + 4;
    ((Callee*)sub)->f();
}
