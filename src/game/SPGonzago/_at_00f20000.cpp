// src/game/SPGonzago/_at_00f20000.cpp -- migrated from slice(s) s00f25a40, s00f24b30, s00f23cd0, s00f22d50, s00f22630, s00f20a60, s00f1faa0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00f20000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Stopwatch.h"

// unnamed retail callees and globals (address in the comment)
extern "C" float sqrtf(float);
extern char g_16c8328;                          // 0x016c8328
extern float kCtlEps;                           // 0x013ec4b8 (FLT_EPSILON)
extern float kCtlHalf;                          // 0x01471064 (0.5f)
extern const float kCtlOne;                     // 0x01485720 (1.0f)
#include <intrin.h>
#include <math.h>
#include "SP/cVarListSerializer.h"

// ---- items of slice s00f1faa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float sqrtf(float);
struct cUICard { void SetVisible(int);          // 0x00e13360
};
struct PanelMgr {
    char pad0[0x148];
    cUICard* card;
    void FUN_00f0e4a0(int);                      // 0x00f0e4a0
};
struct UIRoot { char pad[0x6c]; PanelMgr* panels; };
extern UIRoot* g_UIRoot;                         // 0x016c7aa4
struct BoundingBox { float mnX, mnY, mnZ; float mxX, mxY, mxZ; };  // +0x00 min, +0x0c max
struct IVObj {
    virtual void   AddRef();                                            // +0x00
    virtual void   Release();                                           // +0x04
    virtual void   v008();                                              // +0x08
    virtual void*  GetInterface(uint32_t id);                           // +0x0c
    virtual void   v010();
    virtual void   v014();
    virtual void   PostAt(float value, int a, int b, void* data, void* obj); // +0x18
    virtual void   v01c();
    virtual void   v020();
    virtual void   v024();
    virtual void   v028();
    virtual bool   IsActive();                                          // +0x2c
    virtual void   v030();
    virtual void   v034();
    virtual void   v038();
    virtual void   v03c();
    virtual void   v040();
    virtual void   v044();
    virtual void   SetOnView(int on);                                   // +0x48
    virtual void   v04c();
    virtual void   v050();
    virtual void   v054();
    virtual void   v058();
    virtual void*  FindChild(uint32_t id);                              // +0x5c
    virtual void   v060();
    virtual void   v064();
    virtual void   v068();
    virtual BoundingBox* GetBounds(void* out);                          // +0x6c
    virtual void   v070();
    virtual void   v074();
    virtual void   v078();
    virtual void   v07c();
    virtual void   v080();
    virtual void   v084();
    virtual void   v088();
    virtual void   v08c();
    virtual bool   HasModel();                                          // +0x90
    virtual void   v094();
    virtual void   v098();
    virtual void   v09c();
    virtual void   v0a0();
    virtual void   v0a4();
    virtual void   v0a8();
    virtual void   v0ac();
    virtual void   v0b0();
    virtual void   v0b4();
    virtual IVObj* Cast(uint32_t type);                                 // +0xb8
};
struct SpatialObj {
    virtual void   AddRef();                                            // +0x00
    virtual void   Release();                                           // +0x04
    virtual void   v008();                                              // +0x08
    virtual void*  GetInterface(uint32_t id);                           // +0x0c
    virtual void   v010();
    virtual void   v014();
    virtual void   PostAt(float value, int a, int b, void* data, void* obj); // +0x18
    virtual void   v01c();
    virtual void   v020();
    virtual void   v024();
    virtual void   v028();
    virtual float* GetPosition();                                       // +0x2c
    virtual void   v030();
    virtual void   v034();
    virtual void   v038();
    virtual void   v03c();
    virtual void   v040();
    virtual void   v044();
    virtual void   v048();
    virtual void   v04c();
    virtual void   v050();
    virtual void   v054();
    virtual void   v058();
    virtual void*  FindChild(uint32_t id);                              // +0x5c
    virtual void   v060();
    virtual void   v064();
    virtual void   v068();
    virtual BoundingBox* GetBounds(void* out);                          // +0x6c
    virtual void   v070();
    virtual void   v074();
    virtual void   v078();
    virtual void   v07c();
    virtual void   v080();
    virtual void   v084();
    virtual void   v088();
    virtual void   v08c();
    virtual bool   HasModel();                                          // +0x90
    virtual void   v094();
    virtual void   v098();
    virtual void   v09c();
    virtual void   v0a0();
    virtual void   v0a4();
    virtual void   v0a8();
    virtual void   v0ac();
    virtual void   v0b0();
    virtual void   v0b4();
    virtual void*  Cast(uint32_t type);                                 // +0xb8
};
struct PostTarget : IVObj {
    char  pad004[0x38 - 0x04];
    float f38;                                                          // +0x38
};
struct CtlBase {
    virtual void   AddRef();                                            // +0x00
    virtual IVObj* GetTarget();                                         // +0x04
    virtual void   v008();                                              // +0x08
    virtual void*  GetInterface(uint32_t id);                           // +0x0c
    virtual void   v010();
    virtual void   v014();
    virtual void   PostAt(float value, int a, int b, void* data, void* obj); // +0x18
    virtual void   v01c();
    virtual void   v020();
    virtual void   v024();
    virtual void   v028();
    virtual bool   IsActive();                                          // +0x2c
};
struct Ctl2 : CtlBase {
    char   pad004[0x30 - 0x04];
    char   mActive;                                                     // +0x30
    char   pad031[3];
    float  mTimer;                                                      // +0x34
    IVObj* mObj;                                                        // +0x38
};
struct Comp {
    char pad000[0xb10];
    char flagB10;                                                       // +0xb10
    char padb11[0xb18 - 0xb11];
    char flagB18;                                                       // +0xb18
    void SetFlags(int a, int b);                                        // 0x00c0d0c0
    bool Flag388();                                                     // 0x00c0c0e0
};
struct Tele { void Apply(void* target, void* dir, int z); };             // 0x00b452f0
Tele* __cdecl FUN_00b3d310();
struct ChildCfg {
    char pad000[0x77];
    char f77;                                                           // +0x77
    char pad078[0xa4 - 0x78];
    char fA4;                                                           // +0xa4
    char padA5[0x1f0 - 0xa5];
    int  f1F0;                                                          // +0x1f0
};
struct Ticker { void Tick(); };
struct UIEntry {                        // entry in the global win-proc list
    uint32_t key;                       // +0x00
    IVObj*   obj;                       // +0x04
    float    interval;                  // +0x08
    float    elapsed;                   // +0x0c
    void   (*callback)(UIEntry*);       // +0x10
};
struct WinProcMgr {
    int      FindFirst();                       // 0x00b72160
    UIEntry* GetEntry(int handle);              // 0x00b72210
    UIEntry* NextEntry(uint32_t* key);          // 0x00b72230
    void     RemoveByKey(uint32_t key);         // 0x00b72260
    void     ClearAll();                        // 0x00b72110
    int      GetPriority();                     // 0x00e31100
};
extern WinProcMgr* g_WinProcMgr;                // 0x016c831c
struct ScenarioSub {
    char pad000[0xb8];
    int  fB8;                                   // +0xb8
    int  ByIndex(void* arg);                    // 0x00f19840
    void Attach(void* ctl);                     // 0x00f1a7f0
};
struct UIRoot2 { char pad000[0x78]; ScenarioSub* sub; };
extern char g_16c8328;                          // 0x016c8328
extern float kCtlEps;                           // 0x013ec4b8 (FLT_EPSILON)
extern float kCtlHalf;                          // 0x01471064 (0.5f)
extern const float kCtlOne;                     // 0x01485720 (1.0f)
void __cdecl FUN_00eede20(void* out, int a, int b, float c, int d, int e,
                          int f, int g, int h);                  // 0x00eede20
void __cdecl FUN_00f196f0(void* obj);                            // 0x00f196f0
// ---- items of slice s00f1faa0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern UIRoot* g_UIRoot;                         // 0x016c7aa4
extern WinProcMgr* g_WinProcMgr;                // 0x016c831c

// ---- items of slice s00f20a60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*       g_pSimCtor;       // 0x016c831c
extern int         g_evtPropKey_16c83cc; // 0x016c83cc (global property key)
struct TreeHeader {
    char        pad0[4];
    TreeHeader* mpAnchor;            // +0x04 (anchor self-reference)
    TreeHeader* mpRoot;              // +0x08
    void  find(void** out, int* key); // 0x00e5c780 thiscall
};
struct TreeNode {
    char  pad0[0x10];
    int   key;                       // +0x10
    void* value;                     // +0x14
};
extern TreeHeader* g_pEventLog;      // 0x016c8318
void* __cdecl   sub_ac8fa0(void* p, int key, int def);
void  __cdecl   sub_c6f770(int a, int b, int c);
void  __cdecl   sub_f20620(int* a, int* b, void* c, float d);
void  __cdecl   sub_f20350(void* p);
struct RefreshState;
void  __cdecl   sub_f211f0(RefreshState* self); // 0x00f211f0
void* __cdecl   sub_rbtinc(void* n);
void  __cdecl   sub_c889c0(int e, int b);
void* __cdecl   sub_6bb640();
void* __cdecl   sub_new(int, const char*, int, int, int, int);
void* __cdecl   sub_b3d300_id(int v);      // NounManager(nounId)
void* __cdecl   sub_b3d300_0();            // NounManager()
void* __cdecl   sub_planetmodel(void* v);
float* __cdecl  sub_59aed0(float* out, void* vec, void* mat);
float __cdecl   sub_getprop_f(void* prop, int key, float def);
struct Ctx {
    int   getNode();                 // 0x00b18530 reads [ecx+0x1c]
    void* getWorld();                // 0x006c0200 reads [ecx+0x18]
};
struct Mgr {
    void  RemoveNoun();              // 0x00b225d0
    void* GetAvatar();               // 0x00b1fdb0
};
struct SimCtx {
    void  b720e0();                  // 0x00b720e0
    void  c2e4e0();                  // 0x00c2e4e0
    void  ctor743b50();              // 0x00743b50
    void  b72080(int, int);          // 0x00b72080
};
struct V4   { virtual void p0(); virtual void* q(); };                    // +4
struct V4F  { virtual void p0(); virtual void* q(float, void*); };        // +4 (float,void*)->void*
struct V8   { virtual void p0(); virtual void p1(); virtual void* q(); }; // +8
struct V0c  { virtual void p0(); virtual void p1(); virtual void p2();
              virtual void* q(int); };                                    // +0xc
struct V24  { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
              virtual void p8(); virtual char q(int, void**); };                 // +0x24
struct V2cC { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
              virtual void p8(); virtual void p9(); virtual void p10(); virtual char q(); }; // +0x2c
struct V2cP { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
              virtual void p8(); virtual void p9(); virtual void p10(); virtual void* q(); }; // +0x2c
struct V34F { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
              virtual void p12(); virtual float q(); };                   // +0x34
struct VacP { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
virtual void p20();
virtual void p21();
virtual void p22();
virtual void p23();
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
virtual void p28();
virtual void p29();
virtual void p30();
virtual void p31();
virtual void p32();
virtual void p33();
virtual void p34();
virtual void p35();
virtual void p36();
virtual void p37();
virtual void p38();
virtual void p39();
              virtual void p40(); virtual void p41(); virtual void* q(); };  // +0xac
struct Vb8P { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
virtual void p20();
virtual void p21();
virtual void p22();
virtual void p23();
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
virtual void p28();
virtual void p29();
virtual void p30();
virtual void p31();
virtual void p32();
virtual void p33();
virtual void p34();
virtual void p35();
virtual void p36();
virtual void p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual void p41();
virtual void p42();
virtual void p43();
              virtual void p44(); virtual void p45(); virtual void* q(int); };  // +0xb8
struct Model { float GetRadiusAt(); };        // 0x00b7ef70 ecx-receiver
struct PropData {
    char    pad0[0xe60];
    uint8_t flag0;                   // +0xe60
    uint8_t flag1;                   // +0xe61
};
struct RefreshState {
    void* mpVtable;
    uint32_t mState;
};
struct Noun {
    uint32_t pad0[0x130 / 4];
    RefreshState mRefreshState;       // +0x130
};
struct Property {
    void*   pData;                   // +0x00
    char    pad4[0x10 - 4];
    uint8_t flags;                   // +0x10
    char    pad11[0x12 - 0x11];
    short   type;                    // +0x12
};
struct IdObj { char pad0[4]; int m4(); };
struct World {
    char  pad0[0x1e8];
    float x1e8, y1ec, z1f0;
    float q1f4[4];                       // +0x1f4 orientation used by sub_59aed0
    float k204;                          // +0x204 scale
};
struct Node48 { char pad[0x48]; int v48; };
void* __cdecl FUN_00f20de0(float* out, V4* self) {
    Ctx*    c  = (Ctx*)self->q();
    World*  w  = (World*)c->getWorld();
    Ctx*    c2 = (Ctx*)self->q();
    Node48* n  = (Node48*)c2->getNode();
    if (n->v48 == 0) {
        VacP* av = (VacP*)self->q();          // placeholder; real site uses v8
        (void)av;
        float au[3];
        float* r = sub_59aed0(au, (void*)0x015ada7c, (char*)w + 0x1f4);
        float s = w->k204;
        out[0] = w->x1e8 + s * (r[0] * 1.0f);
        out[1] = w->y1ec + s * (r[1] * 1.0f);
        out[2] = w->z1f0 + s * (r[2] * 1.0f);
    } else {
        out[0] = w->x1e8;
        out[1] = w->y1ec;
        out[2] = w->z1f0;
    }
    return out;
}
struct RadiusInfo {                      // object returned by the +0xac getter
    char  pad0[0x84];
    float radius;                        // +0x84
};
struct ModelVtbl {
    void*  slot[0x2b];                                    // +0x00 .. +0xa8
    RadiusInfo* (__thiscall *GetRadiusInfo)(void*);       // +0xac
};
struct RadiusSource { ModelVtbl* mpVtbl; };               // +0x00
struct MarkerCtx {
    virtual void          p0();                           // +0x00
    virtual Ctx*          WorldSource();                  // +0x04 (receiver of 0x006c0200 / 0x00b18530)
    virtual RadiusSource* RadiusSourceObj();              // +0x08
};
struct MarkerRec {
    char pad0[0x48];
    int  v48;                            // +0x48 marker kind
};
struct XformTarget {                     // noun+0x70 sub-object vtable
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
    virtual void SetPos(void*);          // +0x3c
    virtual void SetRot(void*);          // +0x40
    virtual void SetScale(float);        // +0x44
};
struct EvtEntity { char pad0[0x18]; void* mpProp; };   // +0x18 property pointer
struct CombatList {
    int   GetCount();                // 0x00c0f4f0 thiscall
    void* GetAt(unsigned i);         // 0x00c0f8a0 thiscall
};
// ---- items of slice s00f20a60 end

// ---- items of slice s00f22630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gDefault;
extern float gScale;
extern const char gKeyName[];
struct Vec3 { float x, y, z; };
extern Vec3 gOrigin;
struct Key { Key(const char*); uint32_t pad[9]; };
struct Msg {
  uint16_t id;
  uint16_t count;
  float x, y, z;
  float value;
  Key key;
  Msg() : id(0), count(0), x(gOrigin.x), y(gOrigin.y), z(gOrigin.z), value(gDefault), key(gKeyName) {}
};
struct Target {
  virtual void v0();
  virtual void v1();
  virtual void Begin(int);
  virtual void Reset(int);
  virtual void v4();
  virtual void v5();
  virtual void Send(Msg*);
  virtual void v7();
  virtual void Init(Msg*);
};
struct Sub {
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
  virtual float GetValue();
};
struct Owner {
  Target* Find(uint32_t);
  Target* Create(uint32_t);
  char pad[0xc0];
  Sub sub;
};
// ---- items of slice s00f22630 end

// ---- items of slice s00f22d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int DAT_016c7aa4;      // 0x016c7aa4  Simulator singleton
extern "C" unsigned int DAT_016c8318;      // 0x016c8318  drama-event multimap
extern "C" unsigned int DAT_016c8328;      // 0x016c8328  component key (data)
extern "C" unsigned int DAT_016c83a4;      // key
extern "C" unsigned int DAT_016c83b0;      // key
extern "C" unsigned int DAT_016c83b4;      // key
extern "C" unsigned int DAT_016c83d0;      // key
extern "C" unsigned int DAT_018c88e4;      // noun type id
extern "C" char         DAT_0148c398[];    // "EP1_powerup_spawnerReincarnate"
typedef unsigned int uint;
void* FUN_00ac8fa0(void* owner, unsigned int key, int d);               // 0x00ac8fa0
void  FUN_00f21d30(void* pos, void* orient, float scale, unsigned int spid); // 0x00f21d30
void  FUN_00f22630(void* noun, void* spid);                             // 0x00f22630
void* SP_NounManager(void);                                             // 0x00b3d300
void* FUN_00b3d240(void);                                               // 0x00b3d240
void  FUN_00f21080(void* a, void* b, float c, float d, float e);        // 0x00f21080
void  FUN_00f20a60(void* out, void* in);                                // 0x00f20a60
void  FUN_00f20be0(void* out, void* a, unsigned int b, unsigned int c,
                   unsigned int d, unsigned int e);                     // 0x00f20be0
void  FUN_00f20cb0(void* a, void* b);                                   // 0x00f20cb0
int*  FUN_00f213f0(void* a, void* b, int c);                            // 0x00f213f0
unsigned int FNV1_String8(const char* s, unsigned int basis, int flags); // 0x00932e80
void* SP_PropertyManager(void);                                         // 0x0067de30
struct Fns {
    void   c0d0c0(unsigned a, int b);            // 0x00c0d0c0  CCB::d0c0
    void   c41d60(void* key);                    // 0x00c41d60
    void   c12310(unsigned id, int a, int b);    // 0x00c12310  InterruptAnimation
    void   c446d0(void* v, int n);               // 0x00c446d0  ApplyImpulse
    void   c6f770(int a, int b);                 // 0x00c6f770
    void   c15d50(void* info, int a, int b);     // 0x00c15d50
    float* d20610();                             // 0x00d20610  GetVelocity
    int*   f3f950(void* noun);                   // 0x00f3f950
    int*   b18530();                             // 0x00b18530  cGameData accessor
    int**  b1f9c0();                             // 0x00b1f9c0  item list begin/end
    void   b225d0(void* n);                      // 0x00b225d0  RemoveNoun
    void*  b20c60(void* type);                   // 0x00b20c60  CreateNoun
    void   f1be10(void* a, void* b);             // 0x00f1be10  AddObj
    void   f1b260(void* a, void* b, void* c);    // 0x00f1b260  q3
    void   f1c4b0();                             // 0x00f1c4b0  End
    void   d00f80(void** out, void* key);        // 0x00d00f80  tree find
    void   d25e00();                             // 0x00d25e00
};
struct Evt {
    virtual void  v00();
    virtual int*  v04();
    virtual int*  v08();
    virtual void* v0c(unsigned int id);
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void  v1c();
    virtual void  v20();
    virtual char  v24(unsigned int key, void** out);
    virtual void  v28(void* out, int tag);
    virtual float* v2c();
    virtual float* v30();
    virtual float v34();
    virtual void  v38(void* v);
    virtual void  v3c(void* v);
    virtual void  v40(float f);
    virtual void  v44(void* a, void* b);
    virtual void  v48(void* a, float f, void* b, int x, int y, int z);
    virtual void  v4c();
    virtual void* v50();
    virtual void  v54(int v);
    virtual void  v58();
    virtual void  v5c(unsigned int id);
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual float* v6c(void* out);
    virtual void  v70();
    virtual void  v74();
    virtual void  v78();
    virtual void  v7c();
    virtual void  v80();
    virtual void  v84();
    virtual void  v88();
    virtual void  v8c();
    virtual void  v90();
    virtual void  v94();
    virtual void  v98();
    virtual void  v9c();
    virtual void  va0();
    virtual void  va4();
    virtual void  va8();
    virtual void  vac();
    virtual void  vb0();
    virtual void  vb4();
    virtual void  vb8();
    virtual void  vbc();
    virtual void  vc0();
    virtual void  vc4();
    virtual void  vc8();
    virtual void  vcc();
    virtual void  vd0();
    virtual void  vd4();
    virtual void  vd8();
    virtual void  vdc(void* v);
    virtual void  ve0();
    virtual void  ve4();
    virtual void  ve8();
    virtual void  vec();
};
struct PropMgr : Evt {
    void* v2c(unsigned int a, unsigned int b, void** out);
};
struct VecObj {
    void* a;
    void* b;
    void* c;
    void* pad0;
    void* pad1;
    ~VecObj();                           // 0x00ad92d0
};
void FUN_00f232a0(void* ev, unsigned int spid);
void FUN_00f23300(int* ev, int* noun, void* pos, void* orient, char flag);
void FUN_00f239f0(int* ev);
// ---- items of slice s00f22d50 end

// ---- items of slice s00f23cd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float        DAT_01485378;                  // 0x01485378  float constant
extern "C" float        DAT_01486110;                  // 0x01486110  float constant
extern "C" unsigned int SP_GameData();                 // 0x00b18530  SP::cGameData
extern "C" int*         SP_NounManager(int* noun);             // 0x00b3d300
extern "C" void         RemoveNoun(int* mgr, int* noun);       // 0x00b225d0
extern "C" int          GetFileCount(int* p);                  // 0x008e7f80
extern "C" void*        FUN_00f3e900(int a);                   // 0x00f3e900
extern "C" int*         FUN_00f21e60(int* a);                  // 0x00f21e60
extern "C" char         FUN_00f22070(int* a);                  // 0x00f22070
extern "C" char         FUN_00f20350(void* a);                 // 0x00f20350
extern "C" void*        operator_delete(void* p);              // 0x00f47380
extern "C" void         RBTreeIncrement(void* node);           // 0x00921580
extern "C" void         RBTreeInsert(void* node, void* a, void* b, int side);  // 0x009216a0
extern "C" void         RBTreeErase(void* a, void* b);         // 0x00921880
extern "C" void         WordCtor_16c8318();
extern "C" void         WordFind_16c8318(void* a, void* b);
struct RBTreeCtorFn { void* Ctor(void* key); };     // 0x00cea030 ecx = tree
static inline void* RBTreeIncrementPtr(void* node)
{
    RBTreeIncrement(node);
    return 0;
}
static inline int FieldAt(int iVar2)
{
    int iVar5 = *(int*)(*(int*)(DAT_016c7aa4 + 0x78) + 0xb8);
    int iVar3 = (int)FUN_00f3e900(0);
    return *(char*)(iVar5 * 0x4e0 + 2 + *(int*)(iVar3 + 0x70)) != 0;
}
struct DramaEventMultiMap {
    void equal_range(void** out, const unsigned int* key);   // 0x00f21cd0
};
struct cDramaEventInstance {
    virtual int  AddRef();                  // +0x00  (slot 0)
    virtual int* GetNoun();                 // +0x04  (slot 1)
    virtual int* GetOwner();                // +0x08  (slot 2)
    virtual int* GetComponent(uint id);     // +0x0c  (slot 3)
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual char IsDead();                  // +0x2c  (slot 11)
    virtual void v30();
    virtual float GetScale();               // +0x34  (slot 13)
};
struct EventTree {
    void Destroy(int* node);                                                          // 0x00f240d0
    unsigned int* Insert(unsigned int* out, unsigned int* key, unsigned int tag);      // 0x00f24120
};
struct AutoRef { void* p; };
// ---- items of slice s00f23cd0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00f248b0(int* ev, int* target);  // 0x00f248b0 (stays in the slice: not this object's)

// ---- items of slice s00f24b30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   sub_eece20(void*);          // noun/type id of an object
extern "C" int   sub_eecf10(void*);          // noun/type id of an object (variant)
extern "C" int   sub_eeca60(void*, void*);   // writes a key struct at arg0
extern "C" void* sub_f21bb0(void*, void*);   // fills a Vector3 at arg0, returns it
extern "C" int   sub_005f7930(void);
extern "C" void* sub_manager_0067cb30(void);
extern "C" int   sub_00552300(void*);
extern float g_1485720;   // 0x01485720  1.0f
extern float g_148c3b8;   // 0x0148c3b8  0.111110926f
extern float g_1471064;   // 0x01471064  0.5f
extern float g_1488874;   // 0x01488874  0.1f
#pragma intrinsic(sqrt)
#ifndef PV
#endif
typedef unsigned int uint_s00f2_4b30;
struct Vec3i { int x, y, z; };
struct Obj;
enum : uint_s00f2_4b30 {
  kType24682294 = 0x24682294,
  kType2B978C46 = 0x2b978c46,
  kType476A98C7 = 0x476a98c7,
  kType2399BE55 = 0x2399be55,
  kType90C48D09 = 0x90c48d09,
  kType3144B430 = 0x3144b430,
  kTypeB1B104   = 0xb1b104,
  kType2F7D0004 = 0x2f7d0004,
  kType65928944 = 0x65928944,
  kTypeCF56099A = 0xcf56099a,
  kTypeB10E526F = 0xb10e526f,
  kTypeD37C1045 = 0xd37c1045,
  kTypeE34E8A60 = 0xe34e8a60,
  kType5B3D1D0D = 0x5b3d1d0d,
  kType6031C03A = 0x6031c03a,
  kType7998CE71 = 0x7998ce71,
  kTypeE137FF08 = 0xe137ff08,
};
struct Obj {
  uint_s00f2_4b30 f00, f04, f08, f0c, f10, f14, f18;
  unsigned char b1c; unsigned char _p1[3];
  unsigned char b20; unsigned char _p2[3];
  uint_s00f2_4b30 f24, f28, f2c, f30, f34;
  uint_s00f2_4b30 _g38[4];
  uint_s00f2_4b30 f48, f4c, f50, f54, f58;
  char _g5c[0x4a8 - 0x5c];
  uint_s00f2_4b30 f4a8, f4ac, f4b0, f4b4, f4b8, f4bc, f4c0, f4c4;

  int  fn25080(Obj* o);
  void fn25110(Vec3i* out, bool* flag);
  void fn25160(Vec3i* o);
  void fn25190(Vec3i* out, bool* flag);
  Vec3i* fn251f0(Vec3i* o);
  Vec3i* fn25240(Vec3i* o, bool* flag);

  int  fn252c0();
  int  fn252f0();
  bool fn25330();
  bool fn25360();
  bool fn25370();
  char fn253e0();
  char fn253f0();
  char fn25420();
  bool fn25430();
  bool fn25470();
  bool fn25490();
  bool fn254d0();
  int  fn25530();
  bool fn25560();
  bool fn25580();
  bool fn255d0();
  bool fn25600();
  bool fn25640();
  bool fn25670();
  int  fn25680();
  bool fn256a0();
  bool fn256e0();
  bool fn25720();
  bool fn25730();
  int  fn25750();
  Obj* fn257b0();

  // complex
  char fn257f0(void* serializer);
};
struct VarListSerializer {
  unsigned mData[0xa14 / 4];                    // +0x0000
  VarListSerializer(Obj*, const char*, int);    // 0x00692f90
  char Serialize(void*);                        // 0x00693e10
};
struct VarReader {
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
virtual void v14();
  virtual int  GetVersion();
};
struct LayoutTree {          // 0x1c-byte Simulator event-tree header
  void*  mpUnused00;         // +0x00
  void*  mpNext;             // +0x04  self-referential list head
  void*  mpPrev;             // +0x08
  void*  mpRoot;             // +0x0c  tree root (nuked / destroyed)
  unsigned char mColor;      // +0x10
  unsigned char mPad11[3];   // +0x11
  void*  mpSize;             // +0x14
  unsigned mPad18;           // +0x18
  void DoNukeSubtree(void* pNode);   // 0x009a9600
  void Destroy(void* pNode);         // 0x00f240d0
};
struct LayoutGlobal {        // 0x38-byte Simulator layout singleton
  LayoutTree worlds;         // +0x00
  LayoutTree collections;    // +0x1c
};
#define gLayoutManager (*(LayoutGlobal**)0x016c8318)   /* 0x016c8318 */
void* FUN_00f473a0(unsigned size, const char* name, int a, int b,
                   const char* file, int line);      // 0x00f473a0
void  FUN_00f47380(void* p);                         // 0x00f47380
struct AssetDir {                                       // SP::Pollen::cAssetDirectory
  bool GetLocalKey(void* a1, void* a2, void* pKey);     // 0x0054e460
  bool IsPending(void* a1, void* a2);                   // 0x0054e740
};
struct UintArray {                                      // 3-dword key array
  unsigned m00;                                         // +0x00
  int      m04;                                         // +0x04
  int      m08;                                         // +0x08
  UintArray* Self();                                    // 0x00572590
};
struct AssetManager {
  unsigned  mPad00[0x16];                               // +0x00
  AssetDir* mpDirectory;                                // +0x58
};
struct AssetThing {                                     // object returned by 0x005f7930
  unsigned mPad00[0x11];                                // +0x00
  void*    mpValue;                                     // +0x44
  bool GetKey(void* p, UintArray* pKey);                // 0x005f8a10
};
#define PV(n) virtual void pv##n();
struct InnerCheck {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual char Check();                        // +0x2c
};
struct PosProvider {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual float* GetPos();                     // +0x2c
};
struct EffectComp {
  PV(0)                                        // +0x00
  virtual InnerCheck*    GetInner();           // +0x04
  virtual PosProvider*   GetPosProvider();     // +0x08
  unsigned mKind;                              // +0x04  dispatch kind (6/0xa/0xd/0xf)
};
struct EffectRoot {
  PV(0) PV(1) PV(2)
  virtual EffectComp* GetComponent(unsigned id);   // +0x0c
};
struct EffectOwner {                           // result of FUN_00ae6740
  PV(0) PV(1)
  virtual PosProvider* GetPosProvider();       // +0x08
  PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  unsigned mPad04[9];                          // +0x04
  void* mpSlot28;                              // +0x28
};
void* FUN_00ae6740(void* p);                              // 0x00ae6740
void* FUN_00f20240(void* pSlot);                          // 0x00f20240
void  FUN_00f24ae0(int* a1, int a2, float a3);            // 0x00f24ae0
// ---- items of slice s00f24b30 end

// ---- items of slice s00f25a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   sub_0067dea0(void);
extern "C" void* __stdcall sub_PropertyManager(void*);
extern "C" size_t __cdecl wcslen(const wchar_t*);
struct DataObj {
  char _pad[4];
  uint f04;            // +0x04  type id
  char _pad8[0x18 - 8];
  uint f18;            // +0x18  sub type id
  char _pad1c[0x70 - 0x1c];
  void* f70;           // +0x70

  char fn25ed0();
  bool fn25ee0();
  bool fn25f20();
  bool fn25f60();
};
struct PtrVec { bool Contains(void* p); };
struct CString { int GetText(); };
struct Mgr6a3dd0 { void Do(); };
struct Mgrf37690 { void Do(void* p); };
struct Mgr71 { int* Find(void* a); };
unsigned g016c8474;
unsigned g016c8470;
unsigned g016c847c;
unsigned g016c8478;
void* g016c7aa4;
struct Tray262e0 {
  char _pad[0x2c54];
  int* begin;   // +0x2c54
  int* end;     // +0x2c58
  bool fn262e0();
};
struct Tray26330 {
  char _pad[0x18];
  char body[4];
  void fn26330();
};
struct Tray26360 {
  char _pad[0x14];
  int f14;
  int f18;
  char _pad1c[0x24 - 0x1c];
  int f24;
  int f28;
  int fn26360();
  int fn26380();
};
// ---- items of slice s00f25a40 end

// @ 0x00f200c0
float __cdecl FUN_00f200c0(uint32_t obj, int index)
{
    if (obj > 0x3a2511e) {
        if (obj == 0x2399be55) {
            switch (index) {
            case 1: case 2: case 3: case 4: case 5: case 0xf: return 0.2f;
            case 6: case 10: case 0xc: case 0xd: return 0.125f;
            case 7: case 8: case 0x10: return 0.3f;
            }
        } else if (obj == 0x24682294 || obj == 0x476a98c7) {
            switch (index) {
            case 1: case 2: case 3: case 4: case 5: case 0xf: return 0.75f;
            case 6: return 0.2f;
            case 7: case 8: case 0x10: return 0.5f;
            case 10: case 0xc: case 0xd: return 0.125f;
            }
        }
    } else if (obj == 0x3a2511e) {
        switch (index) {
        case 1: case 2: case 3: case 4: case 5: case 0xf: return 2.5f;
        case 6: return 1.5f;
        case 7: case 8: case 0x10: return 5.0f;
        case 0xb: case 0xe: return 10.0f;
        }
    } else if (obj != 0 && (obj == 0x18c88e4 || obj == 0x2a8fb3f)) {
        switch (index) {
        case 1: case 2: case 3: case 4: case 5: case 0xf: return 1.25f;
        case 6: return 0.75f;
        case 7: case 8: case 0x10: return 2.5f;
        case 10: case 0xc: case 0xd: return 0.5f;
        case 0xb: case 0xe: return 5.0f;
        }
    }
    return 1.0f;
}

// @ 0x00f20260
void __cdecl FUN_00f20260(int a, int b, float c)
{
    ScenarioSub* s = ((UIRoot2*)g_UIRoot)->sub;
    int b8 = s->fB8;
    int pt[3];
    pt[0] = 0; pt[1] = 0; pt[2] = 0;
    FUN_00eede20(pt, a, b, c, 0, -1, 0, 0, b8);
}

// @ 0x00f202b0
void __cdecl FUN_00f202b0(IVObj* ctl, void* arg)
{
    ScenarioSub* s = ((UIRoot2*)g_UIRoot)->sub;
    int v = s->ByIndex(arg);
    _ReadWriteBarrier();
    ctl->SetOnView(v);
    s->Attach(ctl);

    void* q = ctl->GetInterface(0x70704db);
    if (q)
        ((IVObj*)q)->HasModel();

    void* r = ctl->GetInterface(0x137e8e0);
    if (r)
        ((Ticker*)r)->Tick();         // 0x00ca6db0
    void* t = ctl->GetInterface(0xd0036e08);
    if (t)
        ((Ticker*)t)->Tick();         // 0x00c06f70
    void* u = ctl->GetInterface(0x13f94d4);
    if (u)
        FUN_00f196f0(u);
}

// @ 0x00f20350
bool __cdecl FUN_00f20350(IVObj* obj, float interval, void (*cb)(UIEntry*))
{
    int h = g_WinProcMgr->FindFirst();
    if (!h)
        return false;
    UIEntry* e = g_WinProcMgr->GetEntry(h);
    IVObj* old = e->obj;
    if (obj != old) {
        if (obj)
            obj->AddRef();
        e->obj = obj;
        if (old)
            old->Release();
    }
    e->interval = interval;
    e->callback = cb;
    e->elapsed = 0.0f;
    return true;
}

// @ 0x00f203c0
bool __cdecl FUN_00f203c0(IVObj* obj, float interval, void (*cb)(UIEntry*))
{
    uint32_t prio = (uint32_t)g_WinProcMgr->GetPriority();
    UIEntry* e = g_WinProcMgr->NextEntry(&prio);
    while (e) {
        if (e->obj == obj && e->callback == cb) {
            e->interval = interval;
            e->elapsed = 0.0f;
            return true;
        }
        e = g_WinProcMgr->NextEntry(&prio);
    }
    return FUN_00f20350(obj, interval, cb);
}

// @ 0x00f20440
void __cdecl FUN_00f20440()
{
    uint32_t prio = (uint32_t)g_WinProcMgr->GetPriority();
    UIEntry* e = g_WinProcMgr->NextEntry(&prio);
    while (e) {
        e->callback(e);
        IVObj* o = e->obj;
        if (o) {
            e->obj = 0;
            o->Release();
        }
        g_WinProcMgr->RemoveByKey(e->key);
        e = g_WinProcMgr->NextEntry(&prio);
    }
    g_WinProcMgr->ClearAll();
}

// @ 0x00f204c0
void __cdecl FUN_00f204c0(float dt)
{
    uint32_t prio = (uint32_t)g_WinProcMgr->GetPriority();
    UIEntry* e = g_WinProcMgr->NextEntry(&prio);
    while (e) {
        float t = e->elapsed + dt;
        e->elapsed = t;
        if (t > e->interval) {
            e->callback(e);
            IVObj* o = e->obj;
            if (o) {
                e->obj = 0;
                o->Release();
            }
            g_WinProcMgr->RemoveByKey(e->key);
        }
        e = g_WinProcMgr->NextEntry(&prio);
    }
}

// @ 0x00f20550
void __cdecl FUN_00f20550(UIEntry* e)
{
    if (e->obj->IsActive() == 1)
        return;
    IVObj* o = e->obj;
    Comp* q;
    if (o)
        q = (Comp*)o->GetInterface(0xce9f6639);
    else
        q = (Comp*)0;
    q->flagB18 = 0;
}

// @ 0x00f20590
void __cdecl FUN_00f20590(UIEntry* e)
{
    if (e->obj->IsActive() == 1)
        return;
    IVObj* o = e->obj;
    Comp* q;
    if (o)
        q = (Comp*)o->GetInterface(0xce9f6639);
    else
        q = (Comp*)0;
    q->flagB10 = 0;
}

// @ 0x00f205d0
void __cdecl FUN_00f205d0(UIEntry* e)
{
    if (e->obj->IsActive() == 1)
        return;
    IVObj* o = e->obj;
    Comp* q;
    if (o)
        q = (Comp*)o->GetInterface(0xce9f6639);
    else
        q = (Comp*)0;
    q->SetFlags(7, 0);
}

// @ 0x00f20620
void __cdecl FUN_00f20620(SpatialObj* parent, SpatialObj* target, float param3, float param4)
{
    float dir[3];

    if (target) {
        float* p = target->GetPosition();
        float inv = 1.0f / sqrtf(p[0] * p[0] + p[1] * p[1] + p[2] * p[2] + kCtlEps);
        dir[0] = p[0] * inv;
        dir[1] = p[1] * inv;
        dir[2] = p[2] * inv;
    }

    char flag;
    if (parent) {
        SpatialObj* q = (SpatialObj*)parent->GetInterface(0x1186577);
        if (!q)
            goto lab_207ef;
        if (!target)
            goto lab_20811;
        {
            BoundingBox b1, b2;
            BoundingBox* pb1 = q->GetBounds(&b1);
            float c1x = (pb1->mnX + pb1->mxX) * kCtlHalf;
            float c1y = (pb1->mnY + pb1->mxY) * kCtlHalf;
            float c1z = (pb1->mnZ + pb1->mxZ) * kCtlHalf;
            BoundingBox* pb2 = target->GetBounds(&b2);
            float dx = (pb2->mnX + pb2->mxX) * kCtlHalf - c1x;
            float dy = (pb2->mnY + pb2->mxY) * kCtlHalf - c1y;
            float dz = (pb2->mnZ + pb2->mxZ) * kCtlHalf - c1z;
            float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + kCtlEps);
            dir[0] = dx * inv;
            dir[1] = dy * inv;
            dir[2] = dz * inv;
        }
    }

lab_207ef:
    if (target) {
        Comp* c = (Comp*)target->Cast(0xce9f6639);
        if (c) {
            flag = c->Flag388() ? 1 : 0;
            goto lab_20813;
        }
    }
lab_20811:
    flag = 0;

lab_20813:
    if (target) {
        if (!flag) {
            float s = sqrtf(param3);
            float v[3];
            v[0] = dir[0] * s * param4;
            v[1] = dir[1] * s * param4;
            v[2] = dir[2] * s * param4;
            FUN_00b3d310()->Apply(target, v, 0);
        }
        PostTarget* pt = (PostTarget*)target->Cast(0x13f94d4);
        if (pt) {
            void* src = parent ? parent->GetInterface(0x13f94d4) : 0;
            pt->PostAt(param3, 0, 0, dir, src);
            ChildCfg* child = (ChildCfg*)target->FindChild(0x116dd1b);
            if (child) {
                child->f77 = 0;
                child->f1F0 = 3;
                child->fA4 = 1;
            }
        }
    }
}

// @ 0x00f20900
void __cdecl FUN_00f20900(CtlBase* ctl, void* obj)
{
    IVObj* p = ctl->GetTarget();
    PostTarget* q = p ? (PostTarget*)p->GetInterface(0x13f94d4) : (PostTarget*)0;
    q->PostAt(q->f38, 0, 0x13, &g_16c8328, obj);
}

// @ 0x00f20990
void __cdecl FUN_00f20990(Ctl2* ctl, IVObj* obj)
{
    IVObj* p = ctl->GetTarget();
    if (p->IsActive())
        return;
    if (!ctl->mActive)
        return;
    if (ctl->mObj == obj && ctl->mTimer < kCtlOne)
        return;
    IVObj* q0 = ctl->GetTarget();
    PostTarget* q = q0 ? (PostTarget*)q0->GetInterface(0x13f94d4) : (PostTarget*)0;
    PostTarget* r = obj ? (PostTarget*)obj->GetInterface(0x13f94d4) : (PostTarget*)0;
    q->PostAt(q->f38, 0, 0x13, &g_16c8328, r);
}

// @ 0x00f20a20
void __cdecl FUN_00f20a20(Ctl2* ctl, IVObj* obj)
{
    IVObj* nv = obj;
    *(volatile char*)&ctl->mActive = 1;
    IVObj* old = *(IVObj* volatile*)&ctl->mObj;
    if (nv != old) {
        if (nv)
            nv->AddRef();
        ctl->mObj = nv;
        if (old)
            old->Release();
    }
    ctl->mTimer = 0.0f;
}

// @ 0x00f20a60
void __cdecl FUN_00f20a60(float* out, float* in)
{
    Model* pm = (Model*)sub_planetmodel(in);
    float radius = pm->GetRadiusAt();
    float f1 = *in;
    float s  = in[1] * in[1] + in[2] * in[2] + f1 * f1;
    if (sqrtf(s) < radius) {
        float f3 = 1.0f / sqrtf(s + 1e-08f);
        out[0] = (f1 * f3) * radius;
        out[1] = (f3 * in[1]) * radius;
        out[2] = (f3 * in[2]) * radius;
    } else {
        out[0] = f1;
        out[1] = in[1];
        out[2] = in[2];
    }
}

// @ 0x00f20b20
void __cdecl FUN_00f20b20(int* self)
{
    V2cC* p = (V2cC*)self[1];
    if (p->q() != 1) {
        V0c* q = (V0c*)self[1];
        if (q) {
            PropData* d = (PropData*)q->q(0xce9f6639);
            d->flag1 = 0;
        } else {
            ((PropData*)0)->flag1 = 0;
        }
    }
}

// @ 0x00f20b60
void __cdecl FUN_00f20b60(int* self)
{
    V2cC* p = (V2cC*)self[1];
    if (p->q() != 1) {
        V0c* q = (V0c*)self[1];
        if (q) {
            PropData* d = (PropData*)q->q(0xce9f6639);
            d->flag0 = 0;
        } else {
            ((PropData*)0)->flag0 = 0;
        }
    }
}

// @ 0x00f20be0
void* __cdecl FUN_00f20be0(void* out, V24* prop, int key, void* d4, void* d5, void* d6)
{
    if (prop) {
        Property* found = (Property*)prop;
        if (prop->q(key, (void**)&found)) {
            void** p;
            if (found->type == 0x20 || found->type == 0x10) {
                if ((found->flags & 0x30) == 0)
                    p = (void**)(-(uint32_t)(found->type != 0) & (uint32_t)found);
                else
                    p = *(void***)found->pData;
            } else {
                p = (void**)sub_6bb640();
            }
            ((void**)out)[0] = p[0];
            ((void**)out)[1] = p[1];
            ((void**)out)[2] = p[2];
            return out;
        }
    }
    ((void**)out)[0] = d4;
    ((void**)out)[1] = d5;
    ((void**)out)[2] = d6;
    return out;
}

// @ 0x00f20c60
void* __cdecl FUN_00f20c60(void* out, int* self, int key)
{
    FUN_00f20be0(out, (V24*)self, key, 0, 0, 0);
    return out;
}

// @ 0x00f20cb0
void __cdecl FUN_00f20cb0(int key, void* p)
{
    TreeHeader* g = g_pEventLog;
    TreeNode* node = (TreeNode*)g->mpRoot;
    TreeHeader* end = (TreeHeader*)((char*)g + 4);
    if ((void*)node == (void*)end) return;
    do {
        if (node->key == key) {
            void* old = node->value;
            if (p != old) {
                if (p) ((void(__cdecl*)(void*))(*(void***)p)[0])(p);
                node->value = p;
                if (old) ((void(__cdecl*)(void*))(*(void***)old)[1])(old);
            }
        }
        node = (TreeNode*)sub_rbtinc(node);
        g = g_pEventLog;
        end = (TreeHeader*)((char*)g + 4);
    } while ((void*)node != (void*)end);
}

// @ 0x00f20d20
void* __cdecl FUN_00f20d20(void* p)
{
    void* keep = p;
    void* found;
    if (p) ((void(__cdecl*)(void*))(*(void***)p)[0])(p);
    g_pEventLog->find(&found, (int*)&keep);
    if (p) ((void(__cdecl*)(void*))(*(void***)p)[1])(p);
    TreeHeader* g = g_pEventLog;
    if (found == (void*)((char*)g + 4)) return 0;
    return *(void**)((char*)found + 0x14);
}

// @ 0x00f20d80
void __cdecl FUN_00f20d80(IdObj* self)
{
    TreeHeader* g = g_pEventLog;
    TreeNode* node = (TreeNode*)g->mpRoot;
    TreeHeader* end = (TreeHeader*)((char*)g + 4);
    if ((void*)node == (void*)end) return;
    do {
        int id = *(int*)((char*)node + 0x10);
        if (self->m4() == id) {
            int v = (int)node->value;
            ((Mgr*)sub_b3d300_id(v))->RemoveNoun();
        }
        node = (TreeNode*)sub_rbtinc(node);
        g = g_pEventLog;
        end = (TreeHeader*)((char*)g + 4);
    } while ((void*)node != (void*)end);
}

// @ 0x00f20de0
void __cdecl FUN_00f20de0(float* out, MarkerCtx* ctx)
{
    Ctx* src = ctx->WorldSource();
    World* w = (World*)src->getWorld();
    Node48* node = (Node48*)src->getNode();
    if (node->v48 == 0) {
        RadiusSource* rs = ctx->RadiusSourceObj();
        RadiusInfo* pm = rs->mpVtbl->GetRadiusInfo(rs);
        float radius = pm->radius;
        float buf[4];
        float* qv = sub_59aed0(buf, (void*)0x015ada7c, w->q1f4);
        out[0] = w->x1e8 + w->k204 * (qv[0] * radius);
        out[1] = w->y1ec + w->k204 * (qv[1] * radius);
        out[2] = w->z1f0 + w->k204 * (qv[2] * radius);
    } else {
        out[0] = w->x1e8;
        out[1] = w->y1ec;
        out[2] = w->z1f0;
    }
}

// @ 0x00f20ef0
void __cdecl FUN_00f20ef0(V4* self)
{
    Ctx*    c  = (Ctx*)self->q();
    Node48* n  = (Node48*)c->getNode();
    if (n->v48 != 0) return;
    int  prop = *(int*)((char*)self + 0x18);
    float f   = sub_getprop_f((void*)prop, 0x016c8404, 0.0f);
    int   e   = (int)sub_ac8fa0((void*)prop, 0x016c8408, 0);
    V8*   sv  = (V8*)self->q();
    void* mgr = sub_b3d300_0();
    void* av  = ((Mgr*)mgr)->GetAvatar();
    (void)sv;
    (void)av;
    (void)e;
    (void)f;
    sub_c889c0(e, 0);
}

// @ 0x00f20fe0
void __cdecl FUN_00f20fe0(void)
{
    void* p = sub_new(0x1c, "Simulator", 0, 0, 0, 0);
    if (p) {
        ((SimCtx*)p)->ctor743b50();
        g_pSimCtor = p;
        ((SimCtx*)p)->b72080(0x14, 0x80);
    } else {
        g_pSimCtor = 0;
        ((SimCtx*)0)->b72080(0x14, 0x80);
    }
}

// @ 0x00f21080
void __cdecl FUN_00f21080(V0c* self, void** vec, void* arg3, float r, float scale)
{
    void* v = 0;
    if (self) v = self->q(0x01186577);
    int n = (int)(*(void***)((char*)vec + 4) - *(void***)vec);
    int i = 0;
    if (n <= 0) return;
    do {
        int e = ((int*)*vec)[i];
        float t = 0.0f;
        if (v) {
            float* a = (float*)((V2cP*)v)->q();
            float* b = (float*)((V2cP*)e)->q();
            float d = sqrtf((b[2]-a[2])*(b[2]-a[2]) + (b[1]-a[1])*(b[1]-a[1]) + (b[0]-a[0])*(b[0]-a[0])) / r;
            if (d <= 0.0f) d = 0.0f;
            if (1.0f <= d) d = 1.0f;
            d = (d - 1.0f) * -1.0f;
            t = (1.0f - (((3.0f - d * 2.0f) * d) * d) * 1.0f) * scale;
        }
        sub_f20620((int*)self, (int*)e, arg3, t);
        i++;
    } while (i < n);
}

// @ 0x00f211f0
void __cdecl FUN_00f211f0(int* self)
{
    V2cC* r = (V2cC*)((V4*)self)->q();
    if (r->q() != 0) return;
    Ctx*   c = (Ctx*)((V4*)self)->q();
    Node48* n = (Node48*)c->getNode();
    if (n->v48 == 0) {
        int tmp[3];
        FUN_00f20be0(tmp, (V24*)self[6], 0x016c83c8, 0, 0, 0);
        self[2] = tmp[0];
        self[3] = tmp[1];
        self[4] = tmp[2];
    }
    V8* sv = (V8*)((V4*)self)->q();
    (void)sv;
    float f = sub_getprop_f((void*)self[6], 0x016c83c0, 0.0f);
    void* res = ((V4F*)self)->q(f, (void*)0x00f20940);
    sub_f20350(res);
}

// @ 0x00f212c0
int __cdecl FUN_00f212c0(float* a, float r, float* b)
{
    if ((r + 1.0f) * 3.0f <
        sqrtf((a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) + (a[2]-b[2])*(a[2]-b[2])))
        return 1;
    return 0;
}

// @ 0x00f21310
char __cdecl FUN_00f21310(int* self, float* out, float* info)
{
    float tmp[3];
    float* p = (float*)FUN_00f20de0(tmp, (V4*)self);
    out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
    void* a = ((V8*)self)->q();
    void* b = ((V8*)self)->q();
    float f = ((V34F*)a)->q();
    float* q = (float*)((V2cP*)b)->q();
    if (sqrtf((q[1]-out[1])*(q[1]-out[1]) + (q[2]-out[2])*(q[2]-out[2]) + (q[0]-out[0])*(q[0]-out[0]))
        <= (f + 1.0f) * 3.0f)
        return 0;
    Ctx* c = (Ctx*)((V4*)self)->q();
    World* w = (World*)c->getWorld();
    info[0] = w->x1e8;
    info[1] = w->y1ec;
    info[2] = w->z1f0;
    info[3] = w->k204;
    return 1;
}

// @ 0x00f213f0
void __cdecl FUN_00f213f0(void* arg1, int* arg2)
{
    void* sim = *(void**)0x016c7aa4;                       // Simulator
    MarkerRec* rec = (MarkerRec*)((void* (__thiscall*)(void*, int))0x00f3e8a0)(
        *(void**)((char*)sim + 0x74), *arg2);
    int style = (int)sub_ac8fa0(arg1, *(int*)0x016c83b8, 0);
    void* noun;
    if (style == 0xa || style == 0xd || style == 0xc) {
        noun = ((void* (__thiscall*)(void*))0x00b20c60)(sub_b3d300_id(0x3a2511e));
        (*(void (__thiscall**)(void*))(*(void***)noun + 0x5c))(noun);   // +0x5c init
        *(int*)((char*)noun + 0x110) = 8;
        if (*(int*)((char*)rec + 0x24) == 1 && *(int*)((char*)sim + 0xcc) == 2)
            (*(void (__thiscall**)(void*, int))(*(void***)noun + 0x60))(noun, 0);
        return;
    }
    noun = ((void* (__thiscall*)(void*))0x00b20c60)(sub_b3d300_id(0x018c88e4));
    sub_c6f770((int)noun, 1, 0);
    if (style == 8 && rec->v48 != 1) {
        void* inner = ((void* (__thiscall*)(void*))0x00b20c60)(sub_b3d300_id(0x018c88e4));
        sub_c6f770((int)inner, 1, 0);
        int pos[3];
        FUN_00f20c60(pos, arg2, *(int*)0x016c83d4);
        int scale = rec->v48;
        (void)scale;
        XformTarget* xf = (XformTarget*)((char*)inner + 0x70);
        xf->SetPos((char*)arg2 + 0x1e8);
        xf->SetRot((char*)arg2 + 0x1f4);
        xf->SetScale(*(float*)((char*)arg2 + 0x204));
    }
}

// @ 0x00f21760
void __cdecl FUN_00f21760(V0c* self)
{
    if (self) {
        Noun* n = (Noun*)self->q(0x3a25119);
        if (n) {
            RefreshState* p = &n->mRefreshState;
            if (p) {
                uint32_t state = p->mState;
                if (state) {
                    state -= 0xa;
                    if (state == 0)
                        // The zero offset keeps the decrement live in the retail tail-call form.
                        sub_f211f0(p + state);
                }
            }
        }
    }
}

// @ 0x00f217a0
void __cdecl FUN_00f217a0(EvtEntity* self)
{
    void* prop = self->mpProp;
    sub_ac8fa0(prop, g_evtPropKey_16c83cc, 0);
}

// @ 0x00f217c0
int __cdecl FUN_00f217c0(int* self)
{
    if (self) {
        CombatList* h = (CombatList*)((V0c*)self)->q(0xce9f6639);
        if (h) {
            int n = h->GetCount();
            for (int i = 0; i < n; i++) {
                int* o = (int*)h->GetAt(i);
                if (o) {
                    int r = (int)((Vb8P*)o)->q(0x3a25119);
                    if (r && *(int*)((char*)r + 0x134) == 0xc) {
                        int* q = (int*)sub_ac8fa0(*(void**)((char*)r + 0x148), g_evtPropKey_16c83cc, 0);
                        if (q == self) return r;
                    }
                }
            }
        }
    }
    return 0;
}

// @ 0x00f22630
void FUN_00f22630(Owner* owner, uint32_t id)
{
  Target* t = owner->Find(id);
  if (!t) t = owner->Create(id);
  t->Reset(0);
  t->Begin(0);
  Msg m;
  t->Init(&m);
  m.value = owner->sub.GetValue() * gScale;
  m.count++;
  t->Send(&m);
}

// @ 0x00f23220
void FUN_00f23220(int* a, void* b, float c, float d, float e)
{
    VecObj vec;
    vec.a = 0;
    vec.b = 0;
    vec.c = 0;
    void* w = FUN_00b3d240();
    ((Evt*)w)->v48(b, d, &vec, 0, 0, 0);
    FUN_00f21080(a, &vec, c, d, e);
}

// @ 0x00f232a0
void FUN_00f232a0(void* ev, unsigned int spid)
{
    float local[3];
    ((Evt*)((char*)ev + 0x5a8))->v28(local, -1);
    Evt* c = (Evt*)((char*)ev + 0xc0);
    FUN_00f21d30(local, c->v30(), c->v34(), spid);
}

// @ 0x00f23300
void FUN_00f23300(int* ev, int* noun, void* pos, void* orient, char flag)
{
    struct V3 { float x, y, z; } local;
    FUN_00f20a60(&local, pos);
    Evt* c = (Evt*)((char*)noun + 0xc0);
    c->v44(&local, orient);
    *(char*)((char*)noun + 0x137) = 0;
    ((Fns*)c)->c41d60(&DAT_016c8328);
    c->vec();
    int* gd = ((Fns*)((Evt*)ev)->v04())->b18530();
    if (*(int*)((char*)gd + 0x48) == 0) {
        void* o = (void*)ev[6];
        if (flag) FUN_00f232a0(noun, (uint)FUN_00ac8fa0(o, DAT_016c83b0, 0));
        else      FUN_00f232a0(noun, (uint)FUN_00ac8fa0(o, DAT_016c83b4, 0));
    }
}

// @ 0x00f238e0
void* FUN_00f238e0(int* arg)
{
    void* local = 0;
    unsigned int h = FNV1_String8(DAT_0148c398, 0x811c9dc5u, 1);
    void* pm = SP_PropertyManager();
    if (local) {
        void* t = local;
        local = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)t + 4))(t);
    }
    ((PropMgr*)pm)->v2c(h, 0xd87454e6u, &local);
    int* res = FUN_00f213f0(local, arg, *arg);

    if (*(int*)((char*)DAT_016c7aa4 + 0xcc) != 1) {
        void* x = res ? (void*)((Evt*)res)->v0c(0x175cdc9) : 0;
        (*(void(__thiscall**)(void*, int))((char*)*(void**)x + 0x54))(x, 0);
        *(int*)((char*)x + 0x3c) = 0;
        *(int*)((char*)x + 0x40) = 0;
        *(char*)((char*)x + 0xe5) = 0;
        *(int*)((char*)x + 0x44) = 0;
    }
    void* y = res ? (void*)((Evt*)res)->v0c(0x1186577) : 0;
    (*(void(__thiscall**)(void*, void*))((char*)*(void**)y + 0x38))(y, (char*)arg + 4);
    (*(void(__thiscall**)(void*, void*))((char*)*(void**)y + 0x3c))(y, (char*)arg + 0x10);
    (*(void(__thiscall**)(void*, float))((char*)*(void**)y + 0x40))(y, *(float*)((char*)arg + 0x20));
    if (local)
        (*(void(__thiscall**)(void*))((char*)*(void**)local + 4))(local);
    return res;
}

// @ 0x00f239f0
void FUN_00f239f0(int* ev)
{
    int* n = ((Evt*)ev)->v04();
    int p1c = *(int*)((char*)n + 0x1c);
    int p18 = *(int*)((char*)((Evt*)ev)->v04() + 0x18);
    int* gd = ((Fns*)((Evt*)ev)->v04())->b18530();

    float pos[3];
    float* sp = ((Evt*)((Evt*)ev)->v08())->v2c();
    pos[0] = sp[0];
    pos[1] = sp[1];
    pos[2] = sp[2];

    float scale = ((Evt*)((Evt*)ev)->v08())->v34();

    float orient[4];
    float* so = ((Evt*)((Evt*)ev)->v08())->v30();
    orient[0] = so[0];
    orient[1] = so[1];
    orient[2] = so[2];
    orient[3] = so[3];

    int u1c[3];
    FUN_00f20be0(u1c, (void*)ev[6], DAT_016c83d0, 0, 0, 0);
    unsigned int spid = (unsigned int)FUN_00ac8fa0((void*)ev[6], DAT_016c83a4, 0);
    ((Fns*)SP_NounManager())->b225d0(((Evt*)ev)->v04());
    FUN_00f21d30(pos, orient, scale, spid);

    if (*(int*)((char*)gd + 0x48) != 1) {
        void* nn = ((Fns*)SP_NounManager())->b20c60(&DAT_018c88e4);
        ((Fns*)nn)->c6f770(1, 0);
        if (*(int*)((char*)gd + 0x48) == 2) {
            *(int*)((char*)nn + 0x3c) = *(int*)((char*)gd + 0x50);
            *(int*)((char*)nn + 0x40) = *(int*)((char*)gd + 0x54);
            *(int*)((char*)nn + 0x44) = *(int*)((char*)gd + 0x58);
        } else {
            *(int*)((char*)nn + 0x3c) = u1c[0];
            *(int*)((char*)nn + 0x40) = u1c[1];
            *(int*)((char*)nn + 0x44) = u1c[2];
        }
        Evt* e70 = (Evt*)((char*)nn + 0x70);
        e70->v38(pos);
        e70->v3c(orient);
        e70->v40(scale);
        *(int*)((char*)nn + 0x18) = p18;
        *(int*)((char*)nn + 0x38) = 0xe;
        *(int*)((char*)nn + 0x1c) = p1c;
        FUN_00f20cb0(nn, (void*)((Evt*)ev)->v04());
    }
}

// @ 0x00f23be0
void FUN_00f23be0(void* a, int* b, int* c)
{
    FUN_00f239f0(c);
    void* o = (void*)b[6];
    FUN_00f22630(a, (void*)FUN_00ac8fa0(o, DAT_016c83b0, 0));

    void* mgr = *(void**)((char*)DAT_016c7aa4 + 0x78);
    ((Fns*)mgr)->f1b260(((Evt*)c)->v04(), ((Evt*)b)->v04(), a);
    ((Fns*)a)->c15d50(((Evt*)b)->v08(), 1, 0);
    ((Fns*)SP_NounManager())->b225d0(((Evt*)b)->v04());
    ((Fns*)(*(void**)((char*)DAT_016c7aa4 + 0x78)))->f1c4b0();
}

// @ 0x00f23c80
int FUN_00f23c80(int a, int b)
{
    unsigned int key[2];
    key[0] = (unsigned int)a;
    key[1] = (unsigned int)b;
    void* m = (void*)DAT_016c8318;
    void* out;
    ((Fns*)((char*)m + 0x1c))->d00f80(&out, key);
    if (out != (void*)((char*)m + 0x20))
        return *(int*)((char*)out + 0x18);
    return -1;
}

// @ 0x00f24060
int FUN_00f24060(int* ev)
{
    int* piVar1 = (int*)((int(__thiscall*)(void*))*(void**)(*ev + 4))(ev);
    unsigned int key = (uint)piVar1;
    if (piVar1 != 0)
        ((void(__thiscall*)(void*))*(void**)*piVar1)(piVar1);

    void* lower;
    void* upper;
    ((DramaEventMultiMap*)DAT_016c8318)->equal_range(&lower, &key);

    int iVar2 = 0;
    while (lower != upper) {
        lower = RBTreeIncrementPtr(lower);
        iVar2 = iVar2 + 1;
    }
    if (piVar1 != 0)
        ((void(__thiscall*)(void*))*(void**)(*piVar1 + 4))(piVar1);
    return iVar2;
}

// @ 0x00f240d0
void EventTree::Destroy(int* node)
{
    while (node != 0) {
        Destroy((int*)node[0]);
        int* next = (int*)node[1];
        if (node[5] != 0)
            ((void(__thiscall*)(void*))*(void**)(*(int*)node[5] + 4))((void*)node[5]);
        if (node[4] != 0)
            ((void(__thiscall*)(void*))*(void**)(*(int*)node[4] + 4))((void*)node[4]);
        operator_delete(node);
        node = next;
    }
}

// @ 0x00f24120
unsigned int* EventTree::Insert(unsigned int* out, unsigned int* key, unsigned int tag)
{
    int* eleft = (int*)((char*)this + 4);
    int* place = eleft;
    int* root = *(int**)((char*)this + 0xc);
    if (root != 0) {
        do {
            place = root;
            if (*key < (uint)root[4]) root = (int*)root[1];
            else                      root = (int*)root[0];
        } while (root != 0);
    }
    int side;
    int* leftend = (int*)((char*)this + 4);
    if (place == leftend || *key < (uint)place[4])
        side = 0;
    else
        side = 1;
    (void)tag;
    unsigned int uVar2 = (uint)((RBTreeCtorFn*)this)->Ctor(key);
    RBTreeInsert((void*)uVar2, place, leftend, side);
    unsigned int* pOut = out;
    *(int*)((char*)this + 0x14) = *(int*)((char*)this + 0x14) + 1;
    *pOut = uVar2;
    return pOut;
}

// @ 0x00f24190
void FUN_00f24190(int* a, int* b)
{
    AutoRef ra; ra.p = a;
    if (a != 0)
        ((void(__thiscall*)(void*))*(void**)*a)(a);
    AutoRef rb; rb.p = b;
    if (b != 0)
        ((void(__thiscall*)(void*))*(void**)*b)(b);

    unsigned int tag = 0;
    ((EventTree*)DAT_016c8318)->Insert((unsigned int*)&ra, (unsigned int*)&rb, tag);

    if (b != 0)
        ((void(__thiscall*)(void*))*(void**)(*b + 4))(b);
    if (a != 0)
        ((void(__thiscall*)(void*))*(void**)(*a + 4))(a);
}

// @ 0x00f24200
void FUN_00f24200(void)
{
    int iVar4 = *(int*)(DAT_016c8318 + 8);
    if (iVar4 == DAT_016c8318 + 4)
        return;

    int iVar5 = 0;
    do {
        iVar5 = 0;
        int uStack_4, iVar2, iVar3;

        if (*(int**)(iVar4 + 0x10) == 0)
            uStack_4 = 0;
        else
            uStack_4 = (int)((cDramaEventInstance*)*(int**)(iVar4 + 0x10))->GetComponent(0x175cdc9);

        if (*(int**)(iVar4 + 0x14) == 0) {
            iVar2 = 0; iVar3 = 0;
        } else {
            iVar2 = (int)((cDramaEventInstance*)*(int**)(iVar4 + 0x14))->GetComponent(0xce9f6639);
            iVar3 = (int)((cDramaEventInstance*)*(int**)(iVar4 + 0x14))->GetComponent(0x137e8e0);
        }
        if (*(int**)(iVar4 + 0x14) != 0)
            iVar5 = (int)((cDramaEventInstance*)*(int**)(iVar4 + 0x14))->GetComponent(0x70704db);

        char cVar1 = ((cDramaEventInstance*)*(int**)(iVar4 + 0x10))->IsDead();
        bool keep =
            (cVar1 == 0
             && ((cDramaEventInstance*)*(int**)(iVar4 + 0x14))->IsDead() == 0
             && (iVar5 == 0 || GetFileCount((int*)(iVar5 + 0x120)) != 2)
             && (iVar3 == 0 || GetFileCount((int*)(iVar3 + 0x508)) != 2)
             && (iVar2 == 0
                 || (GetFileCount((int*)(iVar2 + 0x5a8)) != 2
                     || FieldAt(iVar2))));

        if (keep) {
            iVar5 = (int)RBTreeIncrementPtr((void*)iVar4);
        } else {
            int* iVarNext = (int*)RBTreeIncrementPtr((void*)iVar4);
            if (iVar3 != 0)
                *(uint8_t*)(iVar3 + 0xe78) = 1;
            int iVar2b = DAT_016c8318;
            *(int*)(DAT_016c8318 + 0x14) = *(int*)(DAT_016c8318 + 0x14) - 1;
            RBTreeIncrement((void*)iVar4);
            RBTreeErase((void*)iVar4, (void*)(iVar2b + 4));
            if (*(int**)(iVar4 + 0x14) != 0)
                ((void(__thiscall*)(void*))*(void**)(**(int**)(iVar4 + 0x14) + 4))(*(void**)&*(int**)(iVar4 + 0x14));
            if (*(int**)(iVar4 + 0x10) != 0)
                ((void(__thiscall*)(void*))*(void**)(**(int**)(iVar4 + 0x10) + 4))(*(void**)&*(int**)(iVar4 + 0x10));
            operator_delete((void*)iVar4);
            iVar5 = (int)iVarNext;
        }
        iVar4 = iVar5;
    } while (iVar5 != DAT_016c8318 + 4);
}

// @ 0x00f24390
void FUN_00f24390(void)
{
    EventTree* tree = (EventTree*)DAT_016c8318;
    int* puVar1 = (int*)(DAT_016c8318 + 0xc);
    int iVar3 = (int)tree;
    tree->Destroy(*(int**)((char*)tree + 0xc));
    int iVar2 = iVar3 + 4;
    *(int*)(iVar3 + 8) = iVar2;
    *(int*)iVar2 = iVar2;
    *puVar1 = 0;
    *(uint8_t*)(iVar3 + 0x10) = 0;
    *(int*)(iVar3 + 0x14) = 0;
}

// @ 0x00f243c0
void FUN_00f243c0(int* ev, float dt)
{
    int* piVar7 = ev;
    if (*(float*)((char*)ev + 0x28) > DAT_01485378)
        *(float*)((char*)ev + 0x28) = *(float*)((char*)ev + 0x28) - dt;

    int local_10 = FUN_00f24060(ev);
    int iVar4;
    int iVar5;
    int* piVar3;
    int* piStack_c;
    int* piStack_8;
    int* piStack_4;
    int localFlag1 = 0;      // [esp+0x24] byte flag
    int localFlag2 = 0;      // [esp+0x0f] byte flag
    int dec1 = 0;            // [esp+0x28] byte flag (uStack_14._3_1_)

    piVar3 = (int*)((int(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
    {
        unsigned int key = (uint)piVar3;
        if (piVar3 != 0)
            ((void(__thiscall*)(void*))*(void**)*piVar3)(piVar3);
        WordCtor_16c8318();
        {
            void** out = (void**)&piStack_8;
            void* thisp = (void*)DAT_016c8318;
            ((void(__thiscall*)(void*, void**, unsigned int*))*(void**)(0))(thisp, out, &key);
        }
        if (piVar3 != 0)
            ((void(__thiscall*)(void*))*(void**)(*piVar3 + 4))(piVar3);
    }

    piStack_c = piStack_8;
    if (piStack_8 != piStack_4) {
        do {
            piVar3 = (int*)piStack_c[5];
            if (piVar3 != 0) {
                iVar4 = (int)((cDramaEventInstance*)piVar3)->GetComponent(0x70704db);
                if (iVar4 != 0 && GetFileCount((int*)(iVar4 + 0x120)) == 2
                    && *(char*)(*(int*)(*(int*)(DAT_016c7aa4 + 0x78) + 0xb8) * 0x4e0 + 2
                                + *(int*)((char*)SP_GameData() + 0x70)) == 0) {
                    dec1 = 1;
                }
                iVar4 = (int)((cDramaEventInstance*)piVar3)->GetComponent(0x175cdc9);
                if (iVar4 != 0 && *(int*)(iVar4 + 0x38) == 0xe) {
                    local_10 = local_10 - 1;
                    localFlag2 = 1;
                }
            }
            piStack_c = (int*)RBTreeIncrementPtr(piStack_c);
        } while (piStack_c != piStack_4);
    }

    if (local_10 >= 1)
        return;

    iVar4 = (int)((int(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
    {
        unsigned int gd = (uint)SP_GameData();
        float fVar1 = *(float*)((char*)piVar7 + 0x24);
        iVar5 = *(int*)(*(int*)(*(int*)(DAT_016c7aa4 + 0x78) + 0xb8) * 0x4e0 + 0x4a4
                        + *(int*)(gd + 0x70));
        *(float*)((char*)piVar7 + 0x24) = fVar1 - dt;
        (void)iVar4;
        if (fVar1 - dt > 0.0f || *(float*)((char*)piVar7 + 0x28) > 0.0f)
            return;

        char cVar2 = FUN_00f22070(piVar7);
        if (cVar2 != 0) {
            *(float*)((char*)piVar7 + 0x24) = 0.25f;
            return;
        }
        *(float*)((char*)piVar7 + 0x24) = (float)iVar5 + *(float*)((char*)piVar7 + 0x24);
        *(float*)((char*)piVar7 + 0x28) = DAT_01486110;
        unsigned int uVar6 = (uint)FUN_00f21e60(piVar7);
        uVar6 = (uint)((int(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
        FUN_00f24190((int*)uVar6, (int*)0);

        if (localFlag1 != 0) {
            piVar3 = (int*)((int(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
            {
                unsigned int key = (uint)piVar3;
                if (piVar3 != 0)
                    ((void(__thiscall*)(void*))*(void**)*piVar3)(piVar3);
                WordFind_16c8318((void*)0, &key);
                if (piVar3 != 0)
                    ((void(__thiscall*)(void*))*(void**)(*piVar3 + 4))(piVar3);
            }
            piVar3 = piStack_c;
            if (piStack_c != (int*)(DAT_016c8318 + 4)) {
                do {
                    int* piVar9 = (int*)piVar3[5];
                    if (piVar9 != 0) {
                        iVar4 = (int)((cDramaEventInstance*)piVar9)->GetComponent(0x70704db);
                        if (iVar4 != 0 && GetFileCount((int*)(iVar4 + 0x120)) == 2) {
                            RemoveNoun(SP_NounManager(piVar9), piVar9);
                            break;
                        }
                    }
                    piVar3 = (int*)RBTreeIncrementPtr(piVar3);
                } while (piVar3 != (int*)(DAT_016c8318 + 4));
            }
        }

        if (dec1) {
            piVar7 = (int*)((int(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
            {
                unsigned int key = (uint)piVar7;
                if (piVar7 != 0)
                    ((void(__thiscall*)(void*))*(void**)*piVar7)(piVar7);
                WordFind_16c8318((void*)0, &key);
                if (piVar7 != 0)
                    ((void(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
            }
            piVar7 = piStack_c;
            if (piStack_c != (int*)(DAT_016c8318 + 4)) {
                while (1) {
                    int* p3 = (int*)piVar7[5];
                    if (p3 == 0)
                        break;
                    int v = (int)((cDramaEventInstance*)p3)->GetComponent(0x175cdc9);
                    if (v == 0 || *(int*)(v + 0x38) != 0xe)
                        break;
                    RemoveNoun(SP_NounManager(p3), p3);
                    break;
                }
            }
        }
    }
}

// @ 0x00f24ae0
void FUN_00f24ae0(int* ev, int target, float dt)
{
    if (dt != 0.0f) {
        char cVar1 = FUN_00f20350((IVObj*)((void* (__thiscall*)(void*))*(void**)(*ev + 4))(ev), dt, (void (*)(UIEntry*))0x00f24a90);
        if (cVar1 != 0)
            return;
    }
    FUN_00f248b0(ev, (int*)target);
}

// @ 0x00f24b30
void fn24b30(EffectRoot* root, unsigned mode)
{
  if (!root) return;
  EffectComp* comp = root->GetComponent(0x8367427);
  if (!comp || comp->mKind == 0) return;
  if (comp->GetInner()->Check()) return;
  switch (comp->mKind) {
    case 6: case 10: case 13: case 15: {
      EffectOwner* o = (EffectOwner*)FUN_00ae6740(root);
      void* selected;
      if (mode == 0x13) selected = o->mpSlot28;
      else              selected = 0;
      void* rec = FUN_00f20240(&o->mpSlot28);
      float scale = 0.0f;
      if (rec) {
        unsigned t = *(unsigned*)((char*)rec + 4);
        if (t == 0xf || t == 6 || t == 0xa || t == 0xd) {
          Vec3 p1 = *(Vec3*)comp->GetPosProvider()->GetPos();
          Vec3* p2 = (Vec3*)o->GetPosProvider()->GetPos();
          Vec3 delta;
          delta.z = p2->z - p1.z;
          delta.x = p2->x - p1.x;
          delta.y = p2->y - p1.y;
          double d = sqrt((double)delta.z * delta.z + (double)delta.x * delta.x
                          + (double)delta.y * delta.y);
          d = (d - g_1485720) * g_148c3b8;
          float v = (float)d;
          if (v < 0.0f) v = 0.0f;
          if (v > g_1485720) v = g_1485720;
          scale = (float)((double)v * g_1471064 + g_1488874);
        }
      }
      FUN_00f24ae0((int*)comp, (int)selected, scale);
      break;
    }
    default:
      break;
  }
}

// @ 0x00f24d30
void fn24d30()
{
  LayoutGlobal* g = (LayoutGlobal*)FUN_00f473a0(0x38, "Simulator", 0, 0, 0, 0);
  if (g) {
    // default-construct the two embedded event-tree headers
    g->worlds.mpNext = (void*)&g->worlds.mpNext;
    g->worlds.mpPrev = (void*)&g->worlds.mpNext;
    g->worlds.mpRoot = 0;
    g->worlds.mColor = 0;
    g->worlds.mpSize = 0;
    g->collections.mpNext = (void*)&g->collections.mpNext;
    g->collections.mpPrev = (void*)&g->collections.mpNext;
    g->collections.mpRoot = 0;
    g->collections.mColor = 0;
    g->collections.mpSize = 0;
  }
  gLayoutManager = g;
}

// @ 0x00f24d90
void fn24d90()
{
  LayoutGlobal* g = gLayoutManager;
  if (g) {
    LayoutTree& c = g->collections;
    c.DoNukeSubtree(c.mpRoot);                             // free the world tree
    LayoutTree& w = g->worlds;
    w.Destroy(w.mpRoot);                                   // destroy the collection tree
    FUN_00f47380(g);
  }
}

// @ 0x00f25050
int __stdcall fn25050(void* buf, uint_s00f2_4b30 n)
{
  if (buf) {
    if (n < 3) return 0;
    *(uint_s00f2_4b30*)buf = 0x366a930d;
    ((uint_s00f2_4b30*)buf)[1] = 0x191c3c61;
    ((uint_s00f2_4b30*)buf)[2] = 0xe22261b7;
  }
  return 3;
}

// @ 0x00f25080
int Obj::fn25080(Obj* o)
{
  if (f4a8 == o->f4a8 && f4ac == o->f4ac && f4b0 == o->f4b0 &&
      f4b4 == o->f4b4 && f4b8 == o->f4b8 && f4bc == o->f4bc &&
      f4c0 == o->f4c0 && f4c4 == o->f4c4)
    return 0;
  return 1;
}

// @ 0x00f25110
void Obj::fn25110(Vec3i* out, bool* flag)
{
  *flag = (f24 == 1);
  out->x = 0; out->y = 0; out->z = 0;
  if (f24 == 2) {
    out->x = (int)f28; out->y = (int)f2c; out->z = (int)f30;
  } else {
    out->x = (int)f00; out->y = (int)f04; out->z = (int)f08;
  }
}

// @ 0x00f25160
void Obj::fn25160(Vec3i* o)
{
  o->x = (int)f00; o->y = (int)f04; o->z = (int)f08;
  if ((uint_s00f2_4b30)o->y == kTypeB1B104) o->z = (int)kType65928944;
  o->y = (int)kType2F7D0004;
}

// @ 0x00f25190
void Obj::fn25190(Vec3i* out, bool* flag)
{
  *flag = (f24 == 1);
  out->x = 0; out->y = 0; out->z = 0;
  if (f24 == 2) {
    out->x = (int)f28; out->y = (int)f2c; out->z = (int)f30;
  } else {
    out->x = (int)f00; out->y = (int)f04; out->z = (int)f08;
  }
  if ((uint_s00f2_4b30)out->y == kTypeB1B104) out->z = (int)kType65928944;
  out->y = (int)kType2F7D0004;
}

// @ 0x00f251f0
Vec3i* Obj::fn251f0(Vec3i* o)
{
  o->x = 0; o->y = 0; o->z = 0;
  Vec3i tmp;
  Vec3i* r = (Vec3i*)sub_f21bb0(&tmp, this);
  *o = *r;
  if ((uint_s00f2_4b30)o->y == kTypeB1B104) o->z = (int)kType65928944;
  o->y = (int)kType2F7D0004;
  return o;
}

// @ 0x00f25240
Vec3i* Obj::fn25240(Vec3i* o, bool* flag)
{
  *flag = (f48 == 1);
  o->x = 0; o->y = 0; o->z = 0;
  if (f48 == 2) {
    o->x = (int)f50; o->y = (int)f54; o->z = (int)f58;
  } else {
    Vec3i tmp;
    Vec3i* r = (Vec3i*)sub_f21bb0(&tmp, this);
    *o = *r;
  }
  if ((uint_s00f2_4b30)o->y == kTypeB1B104) o->z = (int)kType65928944;
  o->y = (int)kType2F7D0004;
  return o;
}

// @ 0x00f252c0
int Obj::fn252c0()
{
  if (sub_eece20(this) == (int)kTypeCF56099A)
    return (f00 != kType3144B430) * 2 + 1;
  return 0;
}

// @ 0x00f252f0
int Obj::fn252f0()
{
  uint_s00f2_4b30 t = f00;
  if (t == kType90C48D09) return 1;
  if (t == 0x4117bf2c || t == 0x7d14bb49 || t == 0x8e83d305 ||
      t == 0x34fb4ab0 || t == 0x21329a37) return 3;
  return 0;
}

// @ 0x00f25330
bool Obj::fn25330()
{
  bool r = false;
  switch (f04) {
    case 0x2b978c46: case 0x2399be55: case 0x24682294: case 0x476a98c7:
      r = true; break;
  }
  return r;
}

// @ 0x00f25360
bool Obj::fn25360()
{
  bool r = false;
  if (f04 == kType2B978C46) r = true;
  return r;
}

// @ 0x00f25370
bool Obj::fn25370()
{
  bool r = false;
  switch (f04) {
    case 0x2b978c46: case 0x2399be55: case 0x24682294: case 0x476a98c7:
      r = true; break;
  }
  if (!r) {
    switch (f00) {
      case 0xa0ebd95a: case 0x48b8e425: case 0x812057c5: case 0x93512140:
      case 0xc7c9cc8d: case 0xd41f216b: case 0xf70ab170:
        r = true; break;
    }
  }
  return r;
}

// @ 0x00f253e0
char Obj::fn253e0()
{
  return (char)(f00 == kType90C48D09);
}

// @ 0x00f253f0
char Obj::fn253f0()
{
  if (f04 != kTypeB1B104) return 0;
  uint_s00f2_4b30 local[3];
  sub_eeca60(local, this);
  return local[1] == 0xf0000001;
}

// @ 0x00f25420
char Obj::fn25420()
{
  return (char)(f00 == kType3144B430);
}

// @ 0x00f25430
bool Obj::fn25430()
{
  uint_s00f2_4b30 t = f00;
  if (t == 0xc7c9cc8d || t == 0x48b8e425 || t == 0xd41f216b ||
      t == 0xa0ebd95a || t == 0x812057c5 || t == 0xf70ab170)
    return true;
  return false;
}

// @ 0x00f25470
bool Obj::fn25470()
{
  bool r = false;
  uint_s00f2_4b30 t = f04;
  if (t == kType24682294 || t == kType2B978C46 || t == kType476A98C7)
    r = true;
  return r;
}

// @ 0x00f25490
bool Obj::fn25490()
{
  bool r = false;
  switch (sub_eece20(this)) {
    case (int)0xe34e8a60: case (int)0xb10e526f: case (int)0xcf56099a:
    case (int)0xd37c1045: case (int)0x5b3d1d0d: case (int)0x6031c03a:
      r = true; break;
  }
  return r;
}

// @ 0x00f254d0
bool Obj::fn254d0()
{
  if (sub_eecf10(this) == 0x0b7e477a) return true;
  uint_s00f2_4b30 t = f00;
  if (t == 0xc7c9cc8d || t == 0x48b8e425 || t == 0xd41f216b ||
      t == 0x812057c5 || t == 0xff562b48 || t == 0x35e79d51 ||
      t == 0x293fc645 || t == 0x979592bc || t == 0xfd7178fb)
    return true;
  return false;
}

// @ 0x00f25530
int Obj::fn25530()
{
  uint_s00f2_4b30 t = f04;
  if (t == kType24682294 || t == kType2B978C46 || t == kType476A98C7) goto R;
  if (fn254d0()) goto R;
  return 0;
R:
  return 1;
}

// @ 0x00f25560
bool Obj::fn25560()
{
  int t = sub_eece20(this);
  if (t == (int)kTypeE137FF08 || t == (int)kType7998CE71) return false;
  return true;
}

// @ 0x00f25580
bool Obj::fn25580()
{
  int v = sub_eece20(this);
  if (v > (int)0x6031c03a) {
    if (v == (int)0x7998ce71) return true;
    return false;
  }
  if (v == (int)0x6031c03a) return sub_eecf10(this) == 0x167b1f54;
  if (v == (int)0xb10e526f) return true;
  if (v == (int)0xcf56099a) return fn254d0() == false;
  return false;
}

// @ 0x00f255d0
bool Obj::fn255d0()
{
  int t = sub_eece20(this);
  switch (t) {
    case (int)kTypeE34E8A60:
    case (int)kTypeD37C1045:
    case (int)kTypeE137FF08:
    case (int)kType5B3D1D0D:
      return false;
  }
  return true;
}

// @ 0x00f25600
bool Obj::fn25600()
{
  if (f00 == kType90C48D09) return false;
  if (f04 == kTypeB1B104) {
    int t = sub_eecf10(this);
    return t != (int)0x8b8556d8 && t != (int)0x8adff558;
  }
  return true;
}

// @ 0x00f25640
bool Obj::fn25640()
{
  if (f04 == kTypeB1B104) {
    int t = sub_eecf10(this);
    return t != (int)0x8b8556d8 && t != (int)0x8adff558;
  }
  return true;
}

// @ 0x00f25670
bool Obj::fn25670()
{
  return f04 == kType2B978C46;
}

// @ 0x00f25680
int Obj::fn25680()
{
  uint_s00f2_4b30 t = f04;
  if (t == kType24682294 || t == kType476A98C7) return 1;
  return 0;
}

// @ 0x00f256a0
bool Obj::fn256a0()
{
  uint_s00f2_4b30 t = f04;
  if (t == 0x24682294 || t == 0x476a98c7) {
    uint_s00f2_4b30 u = f18;
    if (u <= 0xbc1041e6) {
      if (u == 0xbc1041e6 || u == 0x7d433fad || u == 0x9ad7d4aa) return true;
    } else {
      if (u == 0xc0b74287 || u == 0xf670aa43) return true;
    }
  }
  return false;
}

// @ 0x00f256e0
bool Obj::fn256e0()
{
  uint_s00f2_4b30 t = f04;
  if (t == 0x24682294 || t == 0x476a98c7) {
    uint_s00f2_4b30 u = f18;
    if (u <= 0x441cd3e6) {
      if (u == 0x441cd3e6 || u == 0x1a4e0708 || u == 0x2090a11b) return true;
    } else {
      if (u == 0x449c040f || u == 0x98e03c0d) return true;
    }
  }
  return false;
}

// @ 0x00f25720
bool Obj::fn25720()
{
  return f04 == kType2399BE55;
}

// @ 0x00f25730
bool Obj::fn25730()
{
  return sub_eece20(this) == (int)kTypeCF56099A;
}

// @ 0x00f25750
int Obj::fn25750()
{
  switch (sub_eece20(this)) {
    case (int)kTypeE34E8A60: return 5;
    case (int)kTypeB10E526F: return 7;
    case (int)kTypeCF56099A: return 10;
    case (int)kTypeD37C1045: return 6;
    case (int)kType5B3D1D0D: return 6;
    case (int)kType6031C03A: return 8;
  }
  return -1;
}

// @ 0x00f257b0
Obj* Obj::fn257b0()
{
  f00 = 0; f04 = 0; f08 = 0; f0c = 0;
  f10 = 0xffffffffu; f14 = 0xffffffffu; f18 = 0xffffffffu;
  b1c = 0; b20 = 0;
  f24 = 0; f28 = 0; f2c = 0;
  f30 = 0xffffffffu; f34 = 0xffffffffu;
  return this;
}

// @ 0x00f257f0
char Obj::fn257f0(void* serializer)
{
  // Constructs a cVarListSerializer over this and serializes through it, then
  // (if the serializer version is < 15) collapses the pending key fields.
  VarListSerializer ser(this, (const char*)0x15aed38, 0x1a80d26);
  char r = ser.Serialize(serializer);
  if ((uint_s00f2_4b30)((VarReader*)serializer)->GetVersion() < 0xf) {
    f00 = f24; f04 = f28; f08 = f2c; f10 = f30; f14 = f34;
    f24 = 0; f28 = 0; f2c = 0; f30 = 0xffffffffu; f34 = 0xffffffffu;
  }
  return r;
}

// @ 0x00f25930
bool fn25930(void* a1, void* a2, Vec3i* out)
{
  int key[3];
  key[0] = 0; key[1] = 0; key[2] = 0;
  AssetManager* mgr = (AssetManager*)sub_manager_0067cb30();
  AssetDir* dir = mgr->mpDirectory;
  if (dir->GetLocalKey(a1, a2, key)) {
    if (!dir->IsPending(a1, a2)) {
      if (out) { out->x = key[0]; out->y = key[1]; out->z = key[2]; }
      return true;
    }
  }
  return false;
}

// @ 0x00f259b0
bool fn259b0(int* p, void** out)
{
  AssetThing* mgr = (AssetThing*)sub_005f7930();
  if (mgr && *p != 0) {
    UintArray key;
    key.Self();
    if (mgr->GetKey(p, &key)) {
      p[2] = key.m04;
      *p = key.m08;
      *out = (void*)key.m00;
      return true;
    }
    switch (sub_00552300(p)) {
      case 0:
        *out = 0;
        break;
      case 1:
        *out = mgr->mpValue;
        return true;
    }
    return true;
  }
  return false;
}

// @ 0x00f25a40
int fn25a40(void* a, int* out)
{ (void)a; if (out) *out = 0; return 1; }

// @ 0x00f25af0
char fn25af0(void* self)
{ (void)self; return 0; }

// @ 0x00f25d80
int fn25d80(void* a, void* b)
{ (void)a; (void)b; return 1; }

// @ 0x00f25ed0
char DataObj::fn25ed0()
{
  return (char)(*(int*)((char*)f70 + 0x4a4) != -1);
}

// @ 0x00f25ee0
bool DataObj::fn25ee0()
{
  uint t = f04;
  if (t == 0x24682294 || t == 0x476a98c7) {
    uint u = f18;
    if (u > 0x8f963dcb) {
      if (u == 0xc15695da) return false;
    } else {
      if (u == 0x8f963dcb || u == 0x1f2a25b6 || u == 0x2a5147a9) return false;
    }
  }
  return true;
}

// @ 0x00f25f20
bool DataObj::fn25f20()
{
  uint t = f04;
  if (t == 0x24682294 || t == 0x476a98c7) {
    uint u = f18;
    if (u > 0xbc1041e6) {
      if (u == 0xc0b74287 || u == 0xf670aa43) return false;
    } else {
      if (u == 0xbc1041e6 || u == 0x7d433fad || u == 0x9ad7d4aa) return false;
    }
  }
  return true;
}

// @ 0x00f25f60
bool DataObj::fn25f60()
{
  uint t = f04;
  if (t == 0x24682294 || t == 0x476a98c7 || t == 0x2b978c46) return false;
  return true;
}

// @ 0x00f25f80
int fn25f80()
{ return 0; }

// @ 0x00f26230
void fn26230(void* self)
{ (void)self; }

// @ 0x00f262e0
bool Tray262e0::fn262e0()
{
  PtrVec* v = (PtrVec*)sub_0067dea0();
  int* p = begin;
  int* e = end;
  while (p != e) {
    if (!v->Contains((void*)*p)) return false;
    ++p;
  }
  return true;
}

// @ 0x00f26330
void Tray26330::fn26330()
{
  void* b = *(void**)((char*)g016c7aa4 + 0x18);
  if (b) {
    void* p = body;
    void* r = sub_PropertyManager(p);
    ((Mgr6a3dd0*)r)->Do();
    ((Mgrf37690*)b)->Do(p);
  }
}

// @ 0x00f26360
int Tray26360::fn26360()
{
  if (f28 != 0 && f24 != 0) return ((CString*)this)->GetText();
  return f14;
}

// @ 0x00f26380
int Tray26360::fn26380()
{
  if (f28 != 0 && f24 != 0) {
    return (int)wcslen((const wchar_t*)((CString*)this)->GetText());
  }
  return (f18 - f14) >> 1;
}

// @ 0x00f263b0
char fn263b0(void* self, void* other)
{ (void)self; (void)other; return 0; }

// @ 0x00f26440
char fn26440(void* self, void* other)
{ (void)self; (void)other; return 0; }

// @ 0x00f264b0
float fn264b0(void* a)
{
  Mgr71* m = *(Mgr71**)((char*)g016c7aa4 + 0x74);
  int i = (int)m->Find(a);
  if (i) return *(float*)(i + 0x484);
  return 0.0f;
}

// @ 0x00f264d0
void* fn264d0(void* a, int b, int c)
{ (void)a; (void)b; (void)c; return 0; }

// @ 0x00f26ac0
void fn26ac0(void* param)
{
  int* p = ((int*(*)(void*))*(void**)((char*)param + 0x20))(param);
  if ((g016c8474 & 1) == 0) {
    g016c8474 |= 1;
    g016c8470 = *p = 0;
    return;
  }
  *p = (int)g016c8470;
}

// @ 0x00f26b00
void fn26b00(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x00f26c60
void fn26c60(void* param)
{
  int* p = ((int*(*)(void*))*(void**)((char*)param + 0x20))(param);
  if ((g016c847c & 1) == 0) {
    g016c847c |= 1;
    g016c8478 = *p = 0;
    return;
  }
  *p = (int)g016c8478;
}

// @ 0x00f26ca0
void fn26ca0(void* a, void* b)
{ (void)a; (void)b; }
