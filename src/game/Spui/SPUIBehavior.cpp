// src/game/Spui/SPUIBehavior.cpp -- migrated from slice(s) s012f64e0, s007fc880, s007fb7b0, s007fa520, s007f9550, s007f8540 by tools/migrate/rewrite.py
// Object file: Spui/SPUIBehavior.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUIBehaviorEventBase.h"
#include "cSPUIBehaviorValueInterpolator.h"
#include <cstddef>
#include <math.h>
#include "EA/Messaging/Server.h"

// ---- items of slice s007f8540_od begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AnimMgr {
    char  pad0[0x3a];   // +0x00
    bool  b3a;          // +0x3a
    char  pad3b;        // +0x3b
    float f3c;          // +0x3c

    void  Reset();
    void  AddTime(float dt);
    bool  Set(int key, float value);
    bool  Get(int key, float* out);
    bool  Has(int key);
    void  Clear();

    void* Find(int key) {
        return ((void*(__thiscall*)(void*, int))(*(void**)((char*)*(void**)this + 0x5c)))(this, key);
    }
    void Shutdown() {
        ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)this + 0x60)))(this);
    }
};
// ---- items of slice s007f8540_od end

// ---- items of slice s007f9550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EA_Messaging_GetServer();
extern "C" void __cdecl FUN_00e4a9c0(void*);
struct Ev {
    void* AsA(int id);      // @ 0x007f97a0
    void* AsB(int id);      // @ 0x007f9800
    void* Sub10();          // @ 0x007f9860
    void* AsC(int id);      // @ 0x007f9890
    bool  Set14(int value); // @ 0x007f99c0
    void* AsD(int id);      // @ 0x007f99e0
    void* Sub0C();          // @ 0x007f9b50
    bool  Test1();          // @ 0x007f9b90
    void* AsE(int id);      // @ 0x007f9bb0
    bool  False();          // @ 0x007fa120
    void  Call93a0();       // @ 0x007fa130
    uint32_t Flags();       // @ 0x007fa150
    void* AsInterface(int id); // @ 0x007fa180
    Ev*   SetGlobal();      // @ 0x007fa350
    void  ClearGlobal();    // @ 0x007fa370
    bool  Eval();           // @ 0x007f9550
    int** SlotB(int i);     // FUN_007f93b0
    int** SlotC(int i);     // FUN_007f93c0
    int** SlotD(int i);     // FUN_007f93d0
};
struct EvSub { void M(); uint32_t ExtFlags(); };
struct Cont;
struct Cont {                  // cSPUIBehaviorEventBase
    int** SlotB(int i);        // FUN_007f93b0
    int** SlotC(int i);        // FUN_007f93c0
    int** SlotD(int i);        // FUN_007f93d0
    void  Refresh();           // @ 0x007f9a40
    bool  SetValue(int v);     // @ 0x007f9ae0
    bool  AddB(void* obj);     // @ 0x007f9c10
    bool  RemoveB(void* obj);  // @ 0x007f9c90
    bool  RemoveAllB();        // @ 0x007f9d00
};
inline void* VCallR(void* o, int off) {
    return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline void VCall1(void* o, int off, void* a) {
    ((void(__thiscall*)(void*, void*))(*(void**)((char*)*(void**)o + off)))(o, a);
}
void* g_evGlobal = 0;
struct B0 { virtual void b0(); uint32_t pad[5]; };
struct IfB;
struct PredO { virtual void AddRef(); virtual void Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void* GetOwner(); virtual void SetOwner(IfB*); };
struct ActO { virtual void AddRef(); virtual void Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual bool IsStarted();
virtual void SetStarted(bool);
  virtual void v8(); virtual void* GetOwner(); virtual void SetOwner(IfB*); };
struct IfB { virtual bool AddPredicate(PredO*) = 0; virtual bool AddAction(ActO*) = 0; };
struct CB : B0, IfB {
    PredO** SlotC(int i);
    ActO** SlotD(int i);
    bool AddPredicate(PredO* pred);
    bool AddAction(ActO* act);
    void SerUpdate();
    char fill[0x5c - 0x1c];
    bool mActive;
    int mLast;
};
// ---- items of slice s007f9550 end

// ---- items of slice s007fa520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_tag_7fa780[];
extern char g_serconst_7fa840[];
extern char g_serconst_7fa8e0[];
extern char g_sc_7faa30[];
extern char g_sc_7fb250[];
extern char g_sc_7fb2e0[];
extern char g_sc_7fb440[];
extern char g_7faa70_a[], g_7faa70_b[], g_7faa70_c[];
extern char g_7fb000_a[], g_7fb000_b[], g_7fb000_c[];
extern char g_7fb290_a[], g_7fb290_b[], g_7fb290_c[];
extern char g_7fb320_a[], g_7fb320_b[], g_7fb320_c[], g_7fb320_d[];
extern char g_7fb110_a[], g_7fb110_b[], g_7fb110_c[], g_7fb110_d[], g_7fb110_c2[];
extern char g_serconst_7fb040[];
extern char g_serconst_7fb1a0[];
#pragma pack(push,1)
#pragma pack(pop)
struct RCObj {
  virtual void AddRef();   // +0
  virtual void Release();  // +4
};
struct Pred {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5();
  virtual bool v6();               // +0x18
  virtual void v7();
  virtual int v8();                // +0x20
  virtual void v9();
  virtual unsigned char v10();     // +0x28
};
struct C53 { char pad0[4]; unsigned off; int M(int b); };
struct C_7fa690 {
  char pad0[8];
  struct E { RCObj* p; void* q; } elems[4];   // +0x08, stride 8
  char pad1[0x18];                            // +0x28 .. +0x40
  char flags[4];                              // +0x40
  RCObj* GetAt(int i);
  bool SetAt(int i, RCObj* p);
};
struct Creator {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual RCObj* Create(int tag);   // +0x0c
};
struct P2 { char pad0[4]; RCObj** c; };                     // +0x04
struct P3 { char pad0[0x10]; int off; unsigned count; };    // +0x14 = count
struct IAlloc { virtual void* alloc(int n, int align); };
struct Y { char pad0[0x14]; unsigned count; };
struct VC22 {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
  virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21();
};
struct SerItem { void* type; void* base; unsigned count; void* extra; };
struct VSer {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void* vf();   // +0x14
};
struct C_7faa30 : VSer { void f(SerItem* p); };
struct C_7fb250 : VSer { void f(SerItem* p); };
struct C_7fb2e0 : VSer { void f(SerItem* p); };
struct C_7fb440 : VSer { void f(SerItem* p); };
struct C_7faa70 { char pad[4]; void Base(); void Dtor(); };
struct C_7fb000 { char pad[4]; void Base(); void Dtor(); };
struct C_7fb290 { char pad[4]; void Base(); void Dtor(); };
struct SubC_7fb320 { void Dtor(); };
struct C_7fb320 { char pad[4]; void Mid(); void Base(); void Dtor(); };
struct IWindow { virtual void a0(); virtual void Release(); };
struct Sub10_7fb110 { void Dtor(); };
struct Sub4_7fb110 { void Dtor(); };
struct C_7fb110 {
  char pad[4];
  void Base();
  void Dtor();
};
struct VT_TF {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
  virtual float v6();                     // +0x18
  virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
  virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
  virtual void v19(); virtual void v20(); virtual void v21();
  virtual float v22(float f);             // +0x58
  virtual void v23();
  virtual void v24();                     // +0x60
};
struct C_TF : VT_TF {
  char pad0[8];
  float duration;      // +0x0c
  char pad1[8];        // +0x10 .. +0x18
  float easein;        // +0x18
  float easeout;       // +0x1c
  char pad2[0x19];     // +0x20 .. +0x39
  unsigned char negated; // +0x39  (raw byte: SetNegated stores the argument unchanged)
  bool dirty;          // +0x3a
  char pad3[1];
  float mtime;         // +0x3c
  float workfrom;      // +0x40
  void Update();
  float Evaluate(float f);
  float f20();
  float f40();
  float f60();
  bool IsValid();
  bool IsValid2();
  void* GetMember(int i);
  float Ease(float f);
  void SetNegated(unsigned char b);
};
struct VT16 {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual unsigned char v6();   // +0x18
  virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14();
  virtual bool v15(int a, int b);                  // +0x3c
};
struct C_7fb3b0 : VT16 { bool f(unsigned char b); };
struct Alloc_7fb6a0 { void Free(void* p, unsigned n); };
struct C_7fb6a0 {
  char* begin;
  char* end;
  char* cap;
  Alloc_7fb6a0 alloc;
  void Clear();
};
template<int N> inline void ScratchSlots(){ unsigned int s[N]; }
struct EvtAction {
  virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
  virtual void a4(); virtual void a5(); virtual unsigned char a6();   // +0x18
  virtual void a7(unsigned char);                                     // +0x1c
};
struct EvtBase {
  void* f_7f93d0(int i);                       // 0x007f93d0  (thiscall)
};
void* f_7fa750(void* p);                       // 0x007fa750  (cdecl)
struct Temp12 {
  char pad[0xc];
  void* f_65c480(int n, int z);                // 0x0065c480  (thiscall, stack temp)
};
struct Sub7fb480 { bool f_7fb480(unsigned char b); };
// ---- items of slice s007fa520 end

// ---- items of slice s007fb7b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned char g_164b1f0;
extern void* g_164b410;
extern int   g_164b1f4;
extern char tf_a[], tf_b[], tf_c[], tf_d[];
extern char vi_a[], vi_b[], vi_c[], vi_d[];
extern char v2_a[], v2_b[], v2_c[], v2_d[];
extern char ba_a[], ba_b[], ba_c[], ba_d[], ba_e[], ba_f[], ba_g[], ba_h[];
extern char bce0_vt[];
extern char pb_a[], pb_b[], pb_c[], pb_d[], pb_e[], pb_f[], pb_g[];
extern char ed_a[], ed_b[], ed_c[], ed_d[], ed_e[];
extern char bm_a[], bm_b[], bm_c[];
void* f_7fa4f0(void* a, void* b, void* c);
int   f_571e00(void* p);
void* f_7fa4c0(void* a, int b);
void  wstring_assign(void* s, void* a, void* b);
void  wstring_freebuffer(void* p);
void* string_ctor_copy(void* s, void* other);
void** GetActSlot(void* self, int i);
void  f_7fc330(void* p);
void  f_7fc2a0_ctor(void* p);
void  f_7fbce0_dtor(void* p);
struct Ev7f93 {
  void ClearGlobal();                 // 0x007fa370
  ~Ev7f93() { ClearGlobal(); }
};
Ev7f93* GetEv7f93();                  // 0x007f93e0
struct IMsgServer {
  virtual ~IMsgServer();              // slot 0
  virtual void s1();
  virtual void Shutdown();            // slot 2 (+8)
};
IMsgServer* GetMsgServer();           // 0x00883860
void SetMsgServer(IMsgServer* s);     // 0x00883870
struct IModelWorld7fb {
virtual void s0();
virtual void s1();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s0a();
virtual void s0b();
virtual void s0c();
virtual void s0d();
virtual void s0e();
virtual void s0f();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s1a();
virtual void s1b();
virtual void s1c();
virtual void s1d();
virtual void s1e();
virtual void s1f();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s2a();
virtual void s2b();
virtual void s2c();
virtual void s2d();
virtual void s2e();
virtual void s2f();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s3a();
virtual void s3b();
virtual void s3c();
virtual void s3d();
virtual void s3e();
virtual void s3f();
virtual void s40();
virtual void s41();
  virtual void SetCurrent(void* p);   // +0x108
};
struct IWorldHost {
  virtual void s0();
  virtual IModelWorld7fb* GetWorld();  // +4
};
void f_7fb7b0(IWorldHost* param);
struct C_7fb880 { char pad[4]; void BaseCtor(); void* Ctor(); };
struct C_7fba00 { char pad[4]; void BaseCtor(); void* Ctor(); };
struct C_7fbb20 { char pad[4]; void BaseCtor(); void* Ctor(); };
struct Base4 { void Ctor(); };
struct C_7fba80 { char pad[4]; void BaseCtor0(); void* Ctor(); };
struct C_7fbce0 {
  char pad0[8];
  struct E { RCObj* p; void* q; } elems[4];
  char pad1[0x18];
  char flags[4];
  void BaseDtor();
  void Dtor();
};
void C_7fbce0::Dtor() {
  *(void**)this = (void*)bce0_vt;
  ScratchSlots<1>();
  for (int i = 0; i < 4; i++) {
    if (flags[i] && elems[i].p) elems[i].p->Release();
  }
  BaseDtor();
}
struct C_7fbe70 { int GetClassId(); };
struct C_7fc860 { void g(int a, int b); void f(int a, int b); };
void C_7fc860::f(int a, int b) { g(a, b); }
struct C_7fbbc0 { char pad[4]; void BaseCtor(); void** GetSlot(int i); void* Ctor(); };
struct Alloc7fbd50 {
  Alloc7fbd50(const char* name);                 // 0x00e5cac0 (ret 4, returns this; the copy ctor is the same body)
  Alloc7fbd50(const Alloc7fbd50& o);             // 0x00e5cac0
  void set_name(const char* name);               // 0x010829f0 (ret 4)
};
void* operator new(size_t n, void* p);           // 0x008ac360 (cdecl placement new)
struct VecMap7fbd50 {
  void* mBegin; void* mEnd; void* mCap; Alloc7fbd50 mAlloc;
  VecMap7fbd50(const Alloc7fbd50& a = Alloc7fbd50("UI/vector"))
    : mBegin(0), mEnd(0), mCap(0), mAlloc(a) { mAlloc.set_name("UI/vector_map"); }
};
struct Holder7fbd50 {
  VecMap7fbd50 v;
  Holder7fbd50();
};
struct Pair8 { unsigned first; unsigned second; };
struct Sub18 { void Ctor(); void RemoveAllPredicates(); void RemoveAllActions(); void BaseDtor(); };
struct Sub68 { void FreeBuffer(); };
struct WinProcInit { void Dtor(); };
struct C_7fc200 { char pad[4]; void Dtor(); };
struct C_7fc2a0 { char pad[4]; void BaseCtor(); void* Ctor(); };
struct IRefHost {
  virtual void AddRef();                   // 0x00
  virtual void Release();                  // 0x04
virtual void s2();
virtual void s3();
virtual void s4();
  virtual IWorldHost* GetHost();           // 0x14
};
IRefHost* f_11b7240_ref(void* arg);        // 0x011b7240 (cdecl)
template <class T>
struct RefPtr7fc4b0 {
  T* mpObject;
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
  RefPtr7fc4b0& operator=(T* p) {
    if (p != mpObject) {
      T* pOld = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (pOld) pOld->Release();
    }
    return *this;
  }
};
struct Handler7fc4b0 {
  char pad[4];
  RefPtr7fc4b0<IRefHost> mpHost;           // +4
  bool OnMessage(int msg, void* arg);
};
struct Obj7fc600 { bool f_7fc600(int a, int b); };
// ---- items of slice s007fb7b0 end

// ---- items of slice s007fc880 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct BehaviorMessage { char pad[0x48]; BehaviorMessage(); };
void* operator new(size_t, const char*, int, int, int, int);
struct DispIface;
struct DispReceiver {
    virtual void v0();
    virtual void OnMessage(int msg, void* arg);                // +0x04
};
struct DispSlot {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual bool IsActive();                                   // +0x18
    virtual void v1c();
    virtual int GetFlags();                                    // +0x20
    virtual void v24();
    virtual void Detach(DispIface* iface);                     // +0x28
    virtual DispReceiver* GetReceiver();                       // +0x2c
    virtual void Attach(DispIface* iface);                     // +0x30
};
struct DispIface {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
    virtual void SetActive(int v);                             // +0x3c
};
struct DispCont {
    char pad0[0x10];
    DispSlot** SlotC(int i);        // 0x007f93c0
    DispSlot** SlotD(int i);        // 0x007f93d0
};
struct DispHandleObj {
    virtual int AddRef();                                      // +0x00
    virtual int Release();                                     // +0x04
};
template <class T>
struct DispARC {
    T* mpObject;
    DispARC& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
#define DISP_CONT() ((DispCont*)((char*)this - 0x10))
#define DISP_IFACE() (DISP_CONT() ? (DispIface*)((char*)DISP_CONT() + 0x18) : (DispIface*)0)
struct EvD {
    char pad0[8];
    char pad1[0x44];                // +0x8 .. +0x4b
    bool mbActive;                  // +0x4c
    char pad2[0x1b];                // +0x4d .. +0x67
    DispARC<DispHandleObj> mHandle; // +0x68
    unsigned BaseHandle(int msg, void* arg);   // @ 0x007fc4b0
    bool Dispatch(int msg, void* arg);         // @ 0x007fc880
};
// ---- items of slice s007fc880 end

// @ 0x007f93f0
void AnimMgr::Reset()
{
    f3c = 0.0f;
}

// @ 0x007f9430
void AnimMgr::AddTime(float dt)
{
    f3c = f3c + dt;
}

// @ 0x007f9460
bool AnimMgr::Set(int key, float value)
{
    void* p = Find(key);
    if (p != 0) {
        *(float*)p = value;
        b3a = true;
    }
    return p != 0;
}

// @ 0x007f94b0
bool AnimMgr::Get(int key, float* out)
{
    void* p = Find(key);
    if (p != 0 && out != 0) {
        *out = *(float*)p;
    }
    return p != 0;
}

// @ 0x007f9500
bool AnimMgr::Has(int key)
{
    return Find(key) != 0;
}

// @ 0x007f9530
void AnimMgr::Clear()
{
    Shutdown();
}

// @ 0x007f9550
bool Ev::Eval()
{
    *(char*)((char*)this + 0x3a) = 0;
    VCallR(this, 0x24);
    float* p8 = (float*)((char*)this + 0x20);
    float* p9 = (float*)((char*)this + 0x24);
    if (*p8 <= 0.0f && *p8 != 0.0f) *p8 = 0.0f;
    if (*p9 <= 0.0f && *p9 != 0.0f) *p9 = 0.0f;
    if (0.0f <= *p8 || 0.0f <= *p9) {
        if (1.0f < *p8) *p8 = 1.0f;
        if (1.0f < *p8 + *p8) *p9 = 1.0f - *p8;
    } else {
        *p9 = 0.0f;
        *p8 = 0.0f;
    }
    float* p6 = (float*)((char*)this + 0x18);
    float* p7 = (float*)((char*)this + 0x1c);
    if (*p6 <= 0.0f && *p6 != 0.0f) *p6 = 0.0f;
    if (*p7 <= 0.0f && *p7 != 0.0f) *p7 = 0.0f;
    if (0.0f <= *p6 || 0.0f <= *p7) {
        if (1.0f < *p6) *p6 = 1.0f;
        if (1.0f < *p6 + *p6) *p7 = 1.0f - *p6;
    } else {
        *p7 = 0.0f;
        *p6 = 0.0f;
    }
    float* p3 = (float*)((char*)this + 0x0c);
    if (*p3 <= 0.0f && *p3 != 0.0f) *p3 = 1.0e9f;
    *(float*)((char*)this + 0x40) = *p3 * *p8;
    *(float*)((char*)this + 0x44) = (1.0f - *p9) * *p3;
    float* p4 = (float*)((char*)this + 0x10);
    if (*p4 <= 0.0f && *p4 != 0.0f) *p4 = 0.0f;
    return true;
}

// @ 0x007f97a0
void* Ev::AsA(int id)
{
    int v = id;
    if (v == (int)0xeec58382) return this;
    if (v == (int)0xae9cb0fa) return this;
    if (v == (int)0xee3f516e) return this;
    if (v == (int)0x0243a853) return this;
    return 0;
}

// @ 0x007f9800
void* Ev::AsB(int id)
{
    if (id == (int)0xeec58382) return this;
    if (id == (int)0xae9cb0fa) return this;
    if (id == (int)0xee3f516e) return this;
    if (id == (int)0x0243c076) return this;
    return 0;
}

// @ 0x007f9860
void* Ev::Sub10()
{
    return this ? (void*)((char*)this + 0x10) : 0;
}

// @ 0x007f9890
void* Ev::AsC(int id)
{
    if (id == (int)0xeec58382) return this ? (void*)((char*)this + 4) : 0;
    if (id == (int)0xae9cb0fa) return this ? (void*)((char*)this + 4) : 0;
    if (id == (int)0xee3f516e) return this ? (void*)((char*)this + 4) : 0;
    if (id == (int)0x2f009dd0) return this;
    return 0;
}

// @ 0x007f99c0
bool Ev::Set14(int value)
{
    *(int*)((char*)this + 0x14) = value;
    return true;
}

// @ 0x007f99e0
void* Ev::AsD(int id)
{
    if (id == (int)0xeec58382) return this;
    if (id == (int)0xae9cb0fa) return this;
    if (id == (int)0xee3f516e) return this;
    if (id == (int)0x024b5c98) return this;
    return 0;
}

// @ 0x007f9a40
void Cont::Refresh()
{
    for (int i = 0; i < 4; ++i) {
        int** slot = SlotB(i);
        if (*slot != 0) {
            int r = (int)VCallR(*slot, 0x2c);
            if (r != *(int*)((char*)this + 0x38)) {
                VCall1(*slot, 0x30, (void*)(*(int*)((char*)this + 0x38)));
            }
        }
    }
    *(int*)((char*)this + 0x34) = -1;
}

// @ 0x007f9ae0
bool Cont::SetValue(int v)
{
    *(int*)((char*)this + 0x38) = v;
    for (int i = 0; i < 4; ++i) {
        int** slot = SlotB(i);
        if (*slot != 0) {
            VCall1(*slot, 0x30, (void*)v);
        }
    }
    return true;
}

// @ 0x007f9b90
bool Ev::Test1()
{
    return (*(uint32_t*)((char*)this + 0x10) & 1) != 0;
}

// @ 0x007f9bb0
void* Ev::AsE(int id)
{
    if (id == (int)0xeec58382) return this;
    if (id == (int)0xae9cb0fa) return this;
    if (id == (int)0xee3f516e) return this;
    if (id == (int)0x02439c2f) return this;
    return 0;
}

// @ 0x007f9c10
bool Cont::AddB(void* obj)
{
    for (int i = 0; i < 4; ++i) {
        int** slot = SlotB(i);
        if (*slot == 0) {
            *slot = (int*)obj;
            VCallR(obj, 0);
            VCall1(obj, 0x30, (void*)(*(int*)((char*)this + 0x38)));
            return true;
        }
    }
    return false;
}

// @ 0x007f9c90
bool Cont::RemoveB(void* obj)
{
    for (int i = 0; i < 4; ++i) {
        int** slot = SlotB(i);
        if (*slot == (int*)obj) {
            VCall1(obj, 0x30, 0);
            VCallR(obj, 4);
            *slot = 0;
            return true;
        }
    }
    return false;
}

// @ 0x007f9d00
bool Cont::RemoveAllB()
{
    for (int i = 0; i < 4; ++i) {
        if (*SlotB(i) != 0) {
            VCall1((void*)*SlotB(i), 0x30, 0);
            VCallR((void*)*SlotB(i), 4);
            *SlotB(i) = 0;
        }
    }
    return true;
}

// @ 0x007f9d90
bool CB::AddPredicate(PredO* pred)
{
    for (int i = 0; i < 4; ++i) {
        PredO** slot = SlotC(i);
        if (*slot == 0) {
            *slot = pred;
            (*slot)->AddRef();
            (*slot)->SetOwner(this);
            return true;
        }
    }
    return false;
}

// @ 0x007f9e20
bool CB::AddAction(ActO* act)
{
    for (int i = 0; i < 4; ++i) {
        ActO** slot = SlotD(i);
        if (*slot == 0) {
            *slot = act;
            act->AddRef();
            act->SetOwner(this);
            if (mActive) {
                if (!act->IsStarted()) act->SetStarted(true);
            }
            return true;
        }
    }
    return false;
}

// @ 0x007f9ee0
bool cSPUIBehaviorEventBase::RemovePredicate(cISPUIBehaviorPredicate * pred)
{
    for (int i = 0; pred != 0 && i < 4; ++i) {
        int** slot = ((Cont*)((char*)this))->SlotC(i);
        if (*slot == (int*)pred) {
            VCall1(pred, 0x30, 0);
            VCallR(pred, 4);
            *slot = 0;
            return true;
        }
    }
    return false;
}

// @ 0x007f9f60
bool cSPUIBehaviorEventBase::RemoveAction(cISPUIBehaviorAction * act)
{
    for (int i = 0; act != 0 && i < 4; ++i) {
        int** slot = ((Cont*)((char*)this))->SlotD(i);
        if (*slot == (int*)act) {
            VCall1(act, 0x28, 0);
            VCallR(act, 4);
            *slot = 0;
            return true;
        }
    }
    return false;
}

// @ 0x007f9fe0
bool cSPUIBehaviorEventBase::RemoveAllPredicates()
{
    for (int i = 0; i < 4; ++i) {
        int** slot = ((Cont*)((char*)this))->SlotC(i);
        if (*slot != 0) {
            VCall1((void*)*slot, 0x30, 0);
            VCallR((void*)*slot, 4);
            *slot = 0;
        }
    }
    return true;
}

// @ 0x007fa060
bool cSPUIBehaviorEventBase::RemoveAllActions()
{
    for (int i = 0; i < 4; ++i) {
        int** slot = ((Cont*)((char*)this))->SlotD(i);
        if (*slot != 0) {
            VCall1((void*)*slot, 0x28, 0);
            VCallR((void*)*slot, 4);
            *slot = 0;
        }
    }
    return true;
}

// @ 0x007fa120
bool Ev::False()
{
    return false;
}

// @ 0x007fa130
void Ev::Call93a0()
{
    ((EvSub*)this)->M();
}

// @ 0x007fa150
uint32_t Ev::Flags()
{
    bool c = *(bool*)((char*)this + 0x5c);
    uint32_t part = -(uint32_t)(c != 0) & 2u;
    return (((EvSub*)this)->ExtFlags() & 0xfffffffd) | part;
}

// @ 0x007fa180
void* Ev::AsInterface(int id)
{
    void* r;
    if (id == (int)0x2f009dd0) {
        r = this ? (void*)((char*)this + 0x18) : 0;
    } else {
        r = AsC(id);
    }
    return r;
}

// @ 0x007fa1d0
void CB::SerUpdate()
{
    for (int i = 0; i < 4; ++i) {
        PredO** slot = SlotC(i);
        if (*slot != 0) {
            if ((*slot)->GetOwner() != (IfB*)this) {
                (*slot)->SetOwner(this);
            }
        }
    }
    for (int j = 0; j < 4; ++j) {
        ActO** slot = SlotD(j);
        if (*slot != 0) {
            if ((*slot)->GetOwner() != (IfB*)this) {
                (*slot)->SetOwner(this);
                if (mActive) {
                    if (!(*slot)->IsStarted()) (*slot)->SetStarted(true);
                }
            }
        }
    }
    mLast = -1;
}

// @ 0x007fa350
Ev* Ev::SetGlobal()
{
    g_evGlobal = this;
    return this;
}

// @ 0x007fa370
void Ev::ClearGlobal()
{
    g_evGlobal = 0;
}

// @ 0x007fa390
int __cdecl FUN_007fa390(uint32_t msg, void* data, char flag)
{
    if (msg < 0x1d) {
        void* srv = EA_Messaging_GetServer();
        if (flag == '\0') VCall1(srv, 0x18, 0);
        else VCall1(srv, 0x14, 0);
    }
    bool special = (msg == 0x25a5f95);
    if (msg >= 0x25a5f96) {
        special = (msg == 0x25a5f9a || msg == 0x25a61c5 || msg == 0x25c8cb3);
    } else if (msg < 0x25a5f85) {
        special = (msg == 0x25a5f84 || msg == 0x249f699 || msg == 0x25a5f5a);
    } else {
        special = (msg == 0x25a5f8e);
    }
    if (!special) return 1;
    FUN_00e4a9c0(data);
    void* srv = EA_Messaging_GetServer();
    if (flag == '\0') VCall1(srv, 0x18, 0);
    else VCall1(srv, 0x14, 0);
    return 1;
}

// @ 0x007fa4c0
int* FUN_007fa4c0(int* p, int v)
{
    p[0xc] = v;
    p[2] = 0;
    ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)p + 4)))(p);
    return p;
}

// @ 0x007fa4f0
void FUN_007fa4f0(int p, int a2, int p3)
{
    *(int*)((char*)p + 0x10) = a2;
    *(int*)((char*)p + 0x18) = p3;
    FUN_007fa4c0((int*)p, *(int*)((char*)p3 + 8));
}

// @ 0x007fa520
bool f_7fa520(Pred*** arr, int n, int* counter)
{
  if (*counter == 0) { return true; } else { *counter = 0; }
  bool result = true;
  int combine = -1;
  for (int i = 0; i < n; i++) {
    Pred** e = arr[i];
    if (*e) {
      (*counter)++;
      int mode = (*e)->v8();
      bool val = (*e)->v6();
      if ((*e)->v10()) val = (val == 0);
      if (combine == -1) {
        int m = mode; if (m == -1 || m == 1) m = 2; combine = m; result = val;
        continue;
      }
      if (mode != 1) combine = mode;
      switch (combine) {
        case 2: result = result && val; break;
        case 3: result = result || val; break;
      }
    }
  }
  return result;
}

// @ 0x007fa690
RCObj* C_7fa690::GetAt(int i)
{
  if (i >= 0 && i < 4 && flags[i]) return elems[i].p;
  return 0;
}

// @ 0x007fa6d0
bool C_7fa690::SetAt(int i, RCObj* p)
{
  if (i >= 0 && i < 4) {
    if (flags[i] && elems[i].p) elems[i].p->Release();
    elems[i].p = p;
    if (p) p->AddRef();
    flags[i] = 1;
    return true;
  }
  return false;
}

// @ 0x007fa780
bool f_7fa780(C53* self, P2* p2, P3* p3)
{
  RCObj** c = p2->c;
  RCObj** it = (RCObj**)self->M((int)p3);
  for (unsigned i = 0; i < p3->count; i++, it++, c++) {
    RCObj* created = 0;
    RCObj* old = *it;
    if (old) old->Release();
    Creator* src = (Creator*)*c;
    if (src) {
      created = src->Create((int)g_tag_7fa780);
      if (created) created->AddRef();
    }
    *it = created;
  }
  return true;
}

// @ 0x007fa840
bool f_7fa840(void** p, C53* a, Y* b, IAlloc* c)
{
  int* src = (int*)a->M((int)b);
  int* dst = (int*)c->alloc((int)(b->count * 4), 4);
  if (dst) {
    p[1] = dst;
    p[2] = (void*)b->count;
    p[0] = (void*)g_serconst_7fa840;
    for (unsigned i = 0; i < b->count; i++, src++, dst++) {
      *dst = *src;
    }
    return true;
  }
  return false;
}

// @ 0x007fa8e0
bool f_7fa8e0(void** p, C53* a, Y* b)
{
  p[0] = (void*)g_serconst_7fa8e0;
  p[1] = (void*)a->M((int)b);
  p[2] = (void*)b->count;
  return true;
}

// @ 0x007fa950
void f_7fa950(VC22* p)
{ p->v21(); }

// @ 0x007fa9b0
void f_7fa9b0(VC22* p)
{ p->v15(); }

// @ 0x007faa10
void f_7faa10(VC22* p)
{ p->v18(); }

// @ 0x007faa30
void C_7faa30::f(SerItem* p)
{
  p->type = (void*)g_sc_7faa30;
  p->base = this;
  p->count = 1;
  p->extra = vf();
}

// @ 0x007faa70
void C_7faa70::Dtor()
{
  *(void**)this = (void*)g_7faa70_a;
  *(void**)((char*)this + 4) = (void*)g_7faa70_b;
  *(void**)((char*)this + 4) = (void*)g_7faa70_c;
  Base();
}

// @ 0x007faad0
float C_TF::Evaluate(float f)
{
  if (dirty) Update();
  float r = v22(f);
  if (negated) return 1.0f - r;
  return r;
}

// @ 0x007fab20
float C_TF::f20()
{ return Evaluate(mtime); }

// @ 0x007fab40
float C_TF::f40()
{ return Evaluate(duration); }

// @ 0x007fab60
float C_TF::f60()
{ return Evaluate(0.0f); }

// @ 0x007fab80
void C_TF::SetNegated(unsigned char b)
{
  if (dirty) v24();
  if (b == negated) return;
  int n = 0x14d;
  float step = duration / (float)(n - 0x21);
  float t = workfrom;
  float eps = 0.001f;
  float target = v6();
  negated = b;
  float cur = Evaluate(t);
  unsigned char rising = cur > target;
  while (fabsf(target - cur) >= eps && --n != 0) {
    t += step;
    cur = Evaluate(t);
    if (rising != (cur > target)) {
      rising = !rising;
      step *= -0.47f;
    }
  }
  mtime = t;
}

// @ 0x007facf0
bool C_TF::IsValid()
{
  if (dirty) Update();
  return 1e9f > duration;
}

// @ 0x007fad40
bool C_TF::IsValid2()
{
  if (dirty) Update();
  return mtime > duration;
}

// @ 0x007fad90
void* C_TF::GetMember(int i)
{
  if (dirty) Update();
  void* p = 0;
  switch (i) {
    case 0: p = (char*)this + 0xc; break;
    case 1: p = (char*)this + 0x10; break;
    case 2: p = (char*)this + 0x18; break;
    case 3: p = (char*)this + 0x1c; break;
    case 4: p = (char*)this + 0x14; break;
    case 5: p = (char*)this + 0x20; break;
    case 6: p = (char*)this + 0x24; break;
    case 10: p = (char*)this + 0x28; break;
    case 11: p = (char*)this + 0x2c; break;
    case 12: p = (char*)this + 0x30; break;
    case 13: p = (char*)this + 0x34; break;
  }
  return p;
}

// @ 0x007fae90
float C_TF::Ease(float f)
{
  if (dirty) Update();
  if (f != 0.0f && f != 1.0f && (easein + easeout) != 0.0f) {
    float k = 1.0f / ((2.0f - easein) - easeout);
    if (easein > f) f = ((k / easein) * f) * f;
    else {
      if (1.0f - easeout > f) f = (2.0f * f - easein) * k;
      else f = 1.0f - ((k / easeout) * (1.0f - f)) * (1.0f - f);
    }
  }
  return f;
}

// @ 0x007fb000
void C_7fb000::Dtor()
{
  *(void**)this = (void*)g_7fb000_a;
  *(void**)((char*)this + 4) = (void*)g_7fb000_b;
  *(void**)((char*)this + 4) = (void*)g_7fb000_c;
  Base();
}

// @ 0x007fb040
void f_7fb040(void** p, void* a)
{
  p[0] = (void*)g_serconst_7fb040;
  p[1] = a;
  p[2] = (void*)1;
}

// @ 0x007fb0b0
void f_7fb0b0(VC22* p)
{ p->v09(); }

// @ 0x007fb110
void C_7fb110::Dtor()
{
  *(void**)this = (void*)g_7fb110_a;
  *(void**)((char*)this + 4) = (void*)g_7fb110_b;
  *(void**)((char*)this + 8) = (void*)g_7fb110_c;
  *(void**)((char*)this + 0x10) = (void*)g_7fb110_d;
  void** pv = (void**)((char*)this + 0x14);
  if (*(IWindow**)pv) ((IWindow*)*(IWindow**)pv)->Release();
  ((Sub10_7fb110*)((char*)this + 0x10))->Dtor();
  *(void**)((char*)this + 8) = (void*)g_7fb110_c2;
  ((Sub4_7fb110*)((char*)this + 4))->Dtor();
  Base();
}

// @ 0x007fb1a0
void f_7fb1a0(void** p, void* a)
{
  p[0] = (void*)g_serconst_7fb1a0;
  p[1] = a;
  p[2] = (void*)1;
}

// @ 0x007fb250
void C_7fb250::f(SerItem* p)
{
  p->type = (void*)g_sc_7fb250;
  p->base = this;
  p->count = 1;
  p->extra = vf();
}

// @ 0x007fb290
void C_7fb290::Dtor()
{
  *(void**)this = (void*)g_7fb290_a;
  *(void**)((char*)this + 4) = (void*)g_7fb290_b;
  *(void**)((char*)this + 4) = (void*)g_7fb290_c;
  Base();
}

// @ 0x007fb2e0
void C_7fb2e0::f(SerItem* p)
{
  p->type = (void*)g_sc_7fb2e0;
  p->base = this;
  p->count = 1;
  p->extra = vf();
}

// @ 0x007fb320
void C_7fb320::Dtor()
{
  *(void**)this = (void*)g_7fb320_a;
  *(void**)((char*)this + 4) = (void*)g_7fb320_b;
  *(void**)((char*)this + 0xc) = (void*)g_7fb320_c;
  Mid();
  ((SubC_7fb320*)((char*)this + 0xc))->Dtor();
  *(void**)((char*)this + 4) = (void*)g_7fb320_d;
  Base();
}

// @ 0x007fb3b0
bool C_7fb3b0::f(unsigned char b)
{
  unsigned char a = v6();
  bool r = f_7fa520((Pred***)((char*)this + 0x14), 4, (int*)((char*)this + 0x34));
  if (r) v15(1, b); else if (b == 0) v15(1, 0);
  return b == v6();
}

// @ 0x007fb440
void C_7fb440::f(SerItem* p)
{
  p->type = (void*)0x01415598;   // .rdata serialization class descriptor
  p->base = (char*)this - 4;
  p->count = 1;
  p->extra = vf();
}

// @ 0x007fb480
bool Sub7fb480::f_7fb480(unsigned char b)
{
  char* self = (char*)this;
  char* base = self - 0x18;
  char prev = self[0x44];
  bool active;
  if (b != 0 && f_7fa520((Pred***)(self + 4), 4, (int*)(self + 0x48))) active = true;
  else active = false;
  self[0x44] = active ? 1 : 0;
  for (int i = 0; i < 4; i++) {
    EvtAction* a = *(EvtAction**)((EvtBase*)base)->f_7f93d0(i);
    if (a && a->a6() == 0 && self[0x44] != 0)
      a->a7(self[0x44]);
  }
  if (self[0x44] == 0 && *(void**)(self + 0x60) != 0) {
    void* p = *(void**)(self + 0x60);
    *(void**)(self + 0x60) = 0;
    if (p) ((void (__thiscall*)(void*))(*(void***)p)[1])(p);
  }
  if (*(void**)(self - 4) != 0 && prev != self[0x44]) {
    void* srcp = *(void**)(self - 4);
    void** vt = *(void***)srcp;
    void* a0 = f_7fa750((void*)(self - 0x18));
    ((void (__thiscall*)(void*, void*))vt[0x104 / 4])(srcp, a0);
    void* child = ((void* (__thiscall*)(void*))vt[0x14 / 4])(srcp);
    if (child != 0) {
      Temp12 tmp;
      void* d = tmp.f_65c480(0xc, 0);
      void** cvt = *(void***)child;
      ((void (__thiscall*)(void*, int, void*, void*, int))cvt[0x10 / 4])(child, 0, *(void**)(self - 4), d, 0);
    }
  }
  return true;
}

// @ 0x007fb6a0
void C_7fb6a0::Clear()
{
  ScratchSlots<1>();
  char* p = begin;
  for (; p < end; p += 8) {}
  if (begin)
    alloc.Free(begin, (unsigned)(((int)(cap - begin) >> 3) << 3));
}

// @ 0x007fb7b0
void f_7fb7b0(IWorldHost* param)
{
  delete GetEv7f93();
  if (g_164b1f0) {
    IModelWorld7fb* ptr = param->GetWorld();
    ptr->SetCurrent(g_164b410);
    IMsgServer* w = GetMsgServer();
    SetMsgServer(0);
    w->Shutdown();
    delete w;
  }
}

// @ 0x007fb880
void* C_7fb880::Ctor()
{
  BaseCtor();
  *(void**)this = (void*)tf_a;
  void** rc = (void**)((char*)this + 4);
  rc[0] = (void*)tf_b;
  rc[1] = 0;
  *(void**)this = (void*)tf_c;
  *(void**)((char*)this + 4) = (void*)tf_d;
  *(float*)((char*)this + 0xc) = 1.0f;
  *(float*)((char*)this + 0x10) = 1.0f;
  *(float*)((char*)this + 0x14) = 0.0f;
  *(float*)((char*)this + 0x18) = 0.0f;
  *(float*)((char*)this + 0x1c) = 0.0f;
  *(float*)((char*)this + 0x20) = 0.0f;
  *(float*)((char*)this + 0x24) = 0.0f;
  *(float*)((char*)this + 0x28) = 0.0f;
  *(float*)((char*)this + 0x2c) = 0.0f;
  *(float*)((char*)this + 0x30) = 0.0f;
  *(float*)((char*)this + 0x34) = 0.0f;
  *(char*)((char*)this + 0x38) = 0;
  *(char*)((char*)this + 0x39) = 0;
  *(char*)((char*)this + 0x3a) = 1;
  *(float*)((char*)this + 0x3c) = 0.0f;
  *(float*)((char*)this + 0x40) = 0.0f;
  *(float*)((char*)this + 0x44) = 0.0f;
  return this;
}

// @ 0x007fba00
void* C_7fba00::Ctor()
{
  BaseCtor();
  *(void**)this = (void*)vi_a;
  void** p = (void**)((char*)this + 4);
  p[0] = (void*)vi_b;
  p[1] = 0;
  *(void**)this = (void*)vi_c;
  *(void**)((char*)this + 4) = (void*)vi_d;
  return this;
}

// @ 0x007fba80
void* C_7fba80::Ctor()
{
  BaseCtor0();
  *(void**)this = (void*)ba_a;
  ((Base4*)((char*)this + 4))->Ctor();
  void** a = (void**)((char*)this + 8);
  a[0] = (void*)ba_b;
  a[1] = 0;
  void** b = (void**)((char*)this + 0x10);
  b[0] = (void*)ba_c;
  b[0] = (void*)ba_d;
  *(void**)this = (void*)ba_e;
  *(void**)((char*)this + 4) = (void*)ba_f;
  *(void**)((char*)this + 8) = (void*)ba_g;
  *(void**)((char*)this + 0x10) = (void*)ba_h;
  void** c = (void**)((char*)this + 0x14);
  c[0] = 0;
  return this;
}
#pragma pack(push,1)

// @ 0x007fbb20
void* C_7fbb20::Ctor()
{
  BaseCtor();
  *(void**)this = (void*)v2_a;
  void** p = (void**)((char*)this + 4);
  p[0] = (void*)v2_b;
  p[1] = 0;
  *(void**)this = (void*)v2_c;
  *(void**)((char*)this + 4) = (void*)v2_d;
  *(void**)((char*)this + 0xc) = (void*)1;
  *(char*)((char*)this + 0x10) = 0;
  *(void**)((char*)this + 0x14) = 0;
  return this;
}

// @ 0x007fbbc0
void* C_7fbbc0::Ctor()
{
  BaseCtor();
  *(void**)this = (void*)pb_a;
  void** x = (void**)((char*)this + 4);
  x[0] = (void*)pb_b;
  x[1] = 0;
  void** y = (void**)((char*)this + 0xc);
  y[0] = (void*)pb_c;
  y[0] = (void*)pb_d;
  *(void**)this = (void*)pb_e;
  *(void**)((char*)this + 4) = (void*)pb_f;
  *(void**)((char*)this + 0xc) = (void*)pb_g;
  *(void**)((char*)this + 0x10) = 0;
  *(void**)((char*)this + 0x34) = (void*)0xffffffff;
  *(void**)((char*)this + 0x38) = 0;
  *(void**)((char*)this + 0x14) = (void*)((char*)this + 0x24);
  *(void**)((char*)this + 0x18) = (void*)((char*)this + 0x28);
  *(void**)((char*)this + 0x1c) = (void*)((char*)this + 0x2c);
  *(void**)((char*)this + 0x20) = (void*)((char*)this + 0x30);
  for (int m = 0; m < 4; m++) *(void**)GetSlot(m) = 0;
  return this;
}

// @ 0x007fbce0
void C_7fc200::Dtor()
{
  *(void**)this = (void*)ed_a;
  *(void**)((char*)this + 4) = (void*)ed_b;
  *(void**)((char*)this + 8) = (void*)ed_c;
  *(void**)((char*)this + 0x10) = (void*)ed_d;
  *(void**)((char*)this + 0x18) = (void*)ed_e;
  ((Sub18*)((char*)this + 0x18))->RemoveAllPredicates();
  ((Sub18*)((char*)this + 0x18))->RemoveAllActions();
  RCObj** pv = (RCObj**)((char*)this + 0x78);
  if (*pv) (*pv)->Release();
  ((Sub68*)((char*)this + 0x68))->FreeBuffer();
  ((Sub18*)((char*)this + 0x18))->BaseDtor();
  ((WinProcInit*)this)->Dtor();
}

// @ 0x007fbd50
Holder7fbd50::Holder7fbd50()
{}

// @ 0x007fbdb0
Pair8* f_7fbdb0(Pair8* first, Pair8* last, Pair8* dest)
{
  Pair8* result;
  {
    bool bSuccess = false;
    Pair8* d = dest;
    for (Pair8* it = first; it != last; ++it, ++d) {
      new (d) Pair8(*it);
    }
    result = d;
  }
  {
    bool b2 = false;
    Pair8* d2 = dest;
    for (Pair8* it2 = first; it2 != last; ++it2, ++d2) {
    }
  }
  return result;
}

// @ 0x007fbe70
int C_7fbe70::GetClassId()
{ return 0x24b899e; }

// @ 0x007fc2a0
void* C_7fc2a0::Ctor()
{
  void* p = (char*)this + 8;
  *(void**)((char*)p + 0x28) = 0;
  BaseCtor();
  *(void**)this = (void*)bm_a;
  *(void**)this = (void*)bm_b;
  *(void**)((char*)this + 0x38) = 0;
  *(void**)this = (void*)bm_c;
  *(void**)((char*)this + 0x40) = 0;
  return this;
}

// @ 0x007fc4b0
bool Handler7fc4b0::OnMessage(int msg, void* arg)
{
  switch (msg) {
    case 0x11:
      mpHost = f_11b7240_ref(arg);
      if (g_164b1f4++ == 0)
        f_7fc330(mpHost->GetHost());
      break;
    case 0x12:
      if (--g_164b1f4 == 0 && mpHost)
        f_7fb7b0(mpHost->GetHost());
      mpHost = 0;
      break;
  }
  return false;
}

struct Msg7fc600 {
  char pad30[0x30];
  void* mArg;                                     // +0x30 (message argument read after the fill call)
  char pad34[0x18];
};
struct ISub7fc600 {
  virtual void s0();
  virtual void Notify(void* a, void* b);          // +0x04
};
// @ 0x007fc600
bool Obj7fc600::f_7fc600(int a, int b)
{
  Msg7fc600 msg;
  ((C_7fc2a0*)&msg)->Ctor();
  void* r = f_7fa4f0(&msg, (void*)a, (void*)b);
  ((ISub7fc600*)((char*)this + 0x10))->Notify(msg.mArg, r);
  bool ok = false;
  ((C_7fbce0*)&msg)->Dtor();
  return ok;
}

// @ 0x007fc690
int f_7fc690(void* self, void* param)
{
  char s[0x10];
  string_ctor_copy(s, (char*)self + 0x50);
  void* end = (char*)param + f_571e00(param) * 2;
  wstring_assign((char*)self + 0x50, param, end);
  char msg[0x48];
  f_7fc2a0_ctor(msg);
  void* u = (void*)f_7fa4c0(msg, 0x24f6efb);
  for (int i = 0; i < 4; i++) {
    void** slot = (void**)GetActSlot((char*)self - 0x18, i);
    if (*slot) {
      void* obj = (void*)((void* (__thiscall*)(void*))(*(void***)(*slot))[0x2c / 4])(*slot);
      ((void (__thiscall*)(void*, void*, void*))(*(void***)obj)[1])(obj, u, 0);
    }
  }
  f_7fbce0_dtor(msg);
  wstring_freebuffer(s);
  return 1;
}

// @ 0x007fc790
int f_7fc790(void* self, void* param)
{
  void* old = *(void**)((char*)self + 0x4c);
  *(void**)((char*)self + 0x4c) = param;
  (void)old;
  char msg[0x48];
  f_7fc2a0_ctor(msg);
  void* u = (void*)f_7fa4c0(msg, 0x24f6efa);
  for (int i = 0; i < 4; i++) {
    void** slot = (void**)GetActSlot((char*)self - 0x18, i);
    if (*slot) {
      void* obj = (void*)((void* (__thiscall*)(void*))(*(void***)(*slot))[0x2c / 4])(*slot);
      ((void (__thiscall*)(void*, void*, void*))(*(void***)obj)[1])(obj, u, 0);
    }
  }
  f_7fbce0_dtor(msg);
  return 1;
}

// @ 0x007fc880
bool EvD::Dispatch(int msg, void* arg)
{
    BaseHandle(msg, arg);
    switch (msg) {
    case 0x11:
        for (int i = 0; i < 4; ++i) {
            if (*DISP_CONT()->SlotC(i) != 0)
                (*DISP_CONT()->SlotC(i))->Attach(DISP_IFACE());
        }
        for (int i = 0; i < 4; ++i) {
            if (*DISP_CONT()->SlotD(i) != 0)
                (*DISP_CONT()->SlotD(i))->Detach(DISP_IFACE());
        }
        break;
    case 0x12:
        for (int i = 0; i < 4; ++i) {
            if (*DISP_CONT()->SlotC(i) != 0)
                (*DISP_CONT()->SlotC(i))->Attach(0);
        }
        for (int i = 0; i < 4; ++i) {
            if (*DISP_CONT()->SlotD(i) != 0)
                (*DISP_CONT()->SlotD(i))->Detach(0);
        }
        mHandle = 0;
        break;
    case 0xc:
        if (mbActive) {
            int cnt = 0;
            for (int i = 0; i < 4; ++i) {
                DispSlot** slot = DISP_CONT()->SlotD(i);
                if (*slot != 0 && (*slot)->IsActive()) {
                    ++cnt;
                    if ((*slot)->IsActive() && ((*slot)->GetFlags() & 0x80)) {
                        DispReceiver* o = (*slot)->GetReceiver();
                        if (o != 0)
                            o->OnMessage(msg, arg);
                    }
                }
            }
            if (cnt == 0)
                ((DispIface*)((char*)this + 8))->SetActive(0);
        }
        break;
    case 0x15:
        if (mbActive) {
            for (int i = 0; i < 4; ++i) {
                DispSlot** slot = DISP_CONT()->SlotD(i);
                if (*slot != 0 && ((*slot)->GetFlags() & 0x100)) {
                    DispReceiver* o = (*slot)->GetReceiver();
                    if (o != 0)
                        o->OnMessage(msg, arg);
                }
            }
        }
        break;
    }
    return false;
}

// @ 0x007fcc40
void Factory(BehaviorMessage** out, int arg)
{
    *out = new ("UI/BehaviorMessage", 0, 0, 0, 0) BehaviorMessage();
    f_7fa4c0(*out, arg);
}

// @ 0x012f6e50
void init_154279c()
{
    *(int*)0x154279c = 1;
    *(int*)0x15427a0 = 0;
    *(void**)0x15427a4 = (void*)0x1415464; *(int*)0x15427a8 = 0x3335c13; *(short*)0x15427ac = 0x13; *(int*)0x15427b0 = 0x30; *(int*)0x15427b4 = 1; *(int*)0x15427b8 = 0;
    *(void**)0x15427bc = (void*)0x1415464; *(int*)0x15427c0 = 0x3335c14; *(short*)0x15427c4 = 0x13; *(int*)0x15427c8 = 0x34; *(int*)0x15427cc = 1; *(int*)0x15427d0 = 0;
    *(void**)0x15427d4 = (void*)0x1415464; *(int*)0x15427d8 = 0x3335c15; *(short*)0x15427dc = 0x13; *(int*)0x15427e0 = 0x38; *(int*)0x15427e4 = 1; *(int*)0x15427e8 = 0;
    *(void**)0x15427ec = (void*)0x1415b08; *(int*)0x15427f0 = 0x3335c41; *(short*)0x15427f4 = 0x13; *(int*)0x15427f8 = 0x4c; *(int*)0x15427fc = 1; *(int*)0x1542800 = 0;
    *(void**)0x1542804 = (void*)0x1415b08; *(int*)0x1542808 = 0x3335c42; *(short*)0x154280c = 0x13; *(int*)0x1542810 = 0x50; *(int*)0x1542814 = 1; *(int*)0x1542818 = 0;
    *(void**)0x154281c = (void*)0x1415b08; *(int*)0x1542820 = 0x3335c43; *(short*)0x1542824 = 0x13; *(int*)0x1542828 = 0x54; *(int*)0x154282c = 1; *(int*)0x1542830 = 0;
    *(void**)0x1542834 = (void*)0x1415b08; *(int*)0x1542838 = 0x3335c44; *(short*)0x154283c = 0x13; *(int*)0x1542840 = 0x58; *(int*)0x1542844 = 1;
}
