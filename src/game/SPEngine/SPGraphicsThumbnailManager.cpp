// src/game/SPEngine/SPGraphicsThumbnailManager.cpp -- migrated from slice(s) s007c13f0, s007ba350, s007b7530, s007c1c10, s007c0780, s007bfaa0, s007bedb0, s007bde20, s007bced0, s007bbf80, s007bb670, s007b97d0, s007b87f0, s007b7ac0, s007b6570, s007b55f0, s007b49f0, s007b3a70, s007b29a0, s007b19c0, s00572580 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsThumbnailManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include <new>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <intrin.h>
#include "SP/cThumbnailManager.h"
#include "SP/cRenderTargetRectID.h"
#include "SP/cPropertyManager.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cFrustumCull.h"
#include "SP/cViewer.h"
#include "EA/Variant.h"
#include "SP/cDirectPropertyList.h"
#include <float.h>
#include "SP/cPropertyList.h"
#include "SP/cCellBackgroundDrawLayer.h"
#include "SP/cTextureInstance.h"
#include "SP/cIThumbnailManager.h"
#include "EA/ArgScript/cIParser.h"
#include "SP/cIRTTManager.h"
#include "SP/cRenderer.h"
#include "SP/cTextureManager.h"

// ---- items of slice s00572580 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct UintArray {
    uint32_t mData[1];
    // @ 0x00572580
    uint32_t* At(int i);
    // @ 0x00572590
    UintArray* Self();
};
// ---- items of slice s00572580 end

// ---- items of slice s007b19c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_0067dcc0();                       // 0x0067DCC0 MessageServer()
struct IMsg {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void v5(void*,int,int);                 // +0x14
};
struct W27a0 {
    char pad[0x82];
    unsigned char m82;                              // +0x82
    char pad2[0x15];
    int m98, m9c, ma0, ma4;
    void f(int, int, int, int);
};
struct W27e0 {
    char pad[0x83];
    unsigned char m83;                              // +0x83
    int m84, m88, m8c, m90, m94;
    void f(int, int, int, int, int);
};
struct Pair { int x, y; };
struct W2820 {
    char pad[0xac];
    Pair a, b, c, d;                                // +0xac .. +0xc8
    float f;                                        // +0xcc
    void set(Pair*, Pair*, Pair*, Pair*, float);
};
struct IObj2 { virtual int AddRef(); virtual int Release(); };
struct B2890 { virtual int AddRef(); virtual int Release(); };
struct D2890 : B2890 {
    void* mObj;                                     // +0x10? (relative to +0x10 of full object)
    char pad[0xc];
    virtual int AddRef();
    virtual ~D2890();
};
extern void* g_vtblB2900;                           // 0x13ef094
struct B2900 { virtual int AddRef(); virtual int Release(); ~B2900() { *(void**)this = &g_vtblB2900; } };
struct D2900 : B2900 {
    char pad[0x20];
    void* mObj;                                     // +0x24
    virtual int AddRef();
    virtual ~D2900();
};
struct Node2900 { char pad[0xc]; unsigned char mFlag; };   // +0xc
struct P2970 { char pad[8]; Node2900* mNode; char pad2[4]; void* mArg; };
// ---- items of slice s007b19c0 end

// ---- items of slice s007b29a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PropHandle {
    char pad[0x10];
    unsigned char flags;                            // +0x10
    unsigned short type;                            // +0x12
    int* GetInt();                                  // 0x0041E990 __thiscall
};
struct PropList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual bool v9(int hash, PropHandle** out);    // +0x24
};
extern PropList* g_sAppProperties;                  // 0x015FD918
struct W3a30 {
    char pad[0x3c];
    void set(int idx, float* v);
};
struct W39d0 {
    char pad[0x70];
    int m70;                                        // +0x70
    int m74;                                        // +0x74
    unsigned char m78;                              // +0x78
    void f();
};
// ---- items of slice s007b29a0 end

// ---- items of slice s007b3a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   g_renderState;      // 0x16fa38c
extern int   DAT_016f9218;
extern int   DAT_016f923c;
extern float DAT_016077c4;
extern float DAT_016077c8;
extern float DAT_01485720;       // 1.0f
extern unsigned g_negNaN;        // 0xffffffff
struct Raster { char pad[0x14]; };
struct EmbeddedState {
    char pad[0x10];
    unsigned char m_hardStateDirty;   // +0x10
    void SetRaster(int index, Raster* r);
    void Dispatch();
};
struct cViewer {
    void Copy(int a, int b, int c);
    void SetView(int* rect, bool b);
    void SetRects(int x, int y, int w, int h);
    bool Check();
    void AddRect(char* p);
    void SetMode(int mode);
    void End();
};
struct DrawList {
    void Init();
    void Add(int index, float a, float b, float c, float d);
};
struct ITextureProvider {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual Raster* GetRaster(int a, int b);                                  // +0x18
    virtual void v7();
    virtual void v8();
    virtual void GetQuad(int a, int b, float* p0, float* p1,
                         float* p2, float* p3);                               // +0x24
};
struct IMaterialMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9();
    virtual void* GetMaterial(int id);                                        // +0x28
};
int   FUN_0067dda0();
void  FUN_00761dc0();
void* MaterialManager();
bool  FUN_006ddcc0(int a, int b, void** out, void* state);
void  FUN_006ddd10(int a, int b);
int   FUN_011f1120();
void  GlobalState_D3D9Sync();
#define OUT(x) out[(x)]
struct cShowTexturesLayer {
    char pad00[0xc];
    unsigned m_materialId;        // +0xc
    int   m_texId0;               // +0x10
    int   m_texId1;               // +0x14
    Raster* m_srcRaster;          // +0x18
    int   m_destX;                // +0x1c
    int   m_destY;                // +0x20
    int   m_vecBegin;             // +0x24
    int   m_vecEnd;               // +0x28
    char  pad2c[0x38 - 0x2c];
    cViewer* m_viewer;            // +0x38
    float m_params[16];           // +0x3c
    char  pad7c[0x82 - 0x7c];
    bool  m_b82;                  // +0x82
    bool  m_b83;                  // +0x83
    unsigned short m_w84;         // +0x84
    unsigned short m_w88;         // +0x88
    unsigned short m_w8c;         // +0x8c
    unsigned short m_w90;         // +0x90
    int   m_quadrant;             // +0x94
    char  m_rect98[0x10];         // +0x98
    bool  m_ba8;                  // +0xa8
    float m_srcQuad[8];           // +0xac
    float m_inset;                // +0xcc
    float m_angle;                // +0xd0
    float m_tx;                   // +0xd4
    float m_ty;                   // +0xd8
    float m_sx;                   // +0xdc
    float m_sy;                   // +0xe0

    void DrawLayer(int a1, int a2, int* a3, int a4);
};
// ---- items of slice s007b3a70 end

// ---- items of slice s007b49f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 { float x, y, z; };
struct Bounds6 {
    Vector3 mn;
    Vector3 mx;
    void Expand(const Vector3* p, int n, int stride);
};
struct IItem {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void* Get();
};
struct IOut {
    virtual void b0();
    virtual void b1();
    virtual void b2();
    virtual void Run(int a, int b, int c, int d);
};
struct ItemList {
    char pad0[0xc];
    IItem** begin;      // +0xc
    IItem** end;        // +0x10
    void Fn(int a, int b, int c, int d);
};
// ---- items of slice s007b49f0 end

// ---- items of slice s007b55f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_defaultPosX;   // 0x01635648
    extern float g_defaultPosY; // 0x0163564c
    extern float g_defaultPosZ; // 0x01635650
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
void* operator new(unsigned int, const char*, int, int, int, int);   // 0x00f473a0
struct TargetBase {
    struct Tex* tex;                    // +0
    uint32_t flags;                     // +4
};
static __forceinline long DecAndGet(volatile long* p)
{
    _InterlockedExchangeAdd(p, -1);
    return _InterlockedExchangeAdd(p, 0);
}
struct RcBase {
    volatile long rc;
    void AddRef() { _InterlockedExchangeAdd(&rc, 1); }
    void Release()
    {
        long v = DecAndGet(&rc);
        if (v < 1)
            _InterlockedExchangeAdd(&rc, 1);
        else
            _InterlockedExchangeAdd(&rc, 0);
    }
};
struct TargetObj : TargetBase, RcBase {
};
struct LockInfo {
    void* data;
    int a, b, c, d, e, f;
};
struct Tex {
    int Lock(int mode, int zero, LockInfo* out);    // 011ef750
    void Unlock(LockInfo* info);                    // 011ef880
};
struct AutoTarget {
    TargetObj* p;
    AutoTarget(TargetObj* o) : p(o) { if (o) static_cast<RcBase*>(o)->AddRef(); }
    ~AutoTarget() { static_cast<RcBase*>(p)->Release(); }
};
struct TargetFactory {              // FUN_0067dd60
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void Register(TargetObj* o);                                    // +0x34
    virtual void v14();
    virtual TargetObj* Create(int a, int b, int c, int d, int e, int f, int g, int h); // +0x3c
};
struct SizeSource {                 // FUN_0067ddb0
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void GetSize(int* wh);                                          // +0x18
};
struct Blitter {                    // FUN_0067dda0
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual void MeasureSomething(int w, int h, int* o0, int* o1, int* o2, int* o3); // +0x24
    virtual void v10();
    virtual void v11();
    virtual void Blit(int a, int b, int c);                                 // +0x30
};
TargetFactory* GetTargetFactory();  // 0067dd60
SizeSource* GetSizeSource();        // 0067ddb0
Blitter* GetBlitter();              // 0067dda0
struct RtParams {
    char pad0[0x0c];
    int f0c, f10;
    int pad14;
    int f18, f1c, f20, f24;
};
struct RtJobA {
    char pad0[0x30];
    RtParams* p;                    // +0x30
    void Run();
};
struct RtJobB {
    char pad0[0x18];
    RtParams* p;                    // +0x18
    void Run();
};
static __forceinline void UploadTargetA(TargetObj* obj)
{
    LockInfo info;
    Tex* t = obj->tex;
    if (t->Lock(2, 0, &info)) {
        int wh[2];
        wh[0] = -1;
        wh[1] = -1;
        GetSizeSource()->GetSize(wh);
        GetBlitter()->Blit(wh[0], wh[1], (int)info.data);
        if (!(obj->flags & 1))
            GetTargetFactory()->Register(obj);
        obj->tex->Unlock(&info);
    }
}
static __forceinline void UploadTargetB(TargetObj* obj)
{
    Tex* t = obj->tex;
    LockInfo info;
    if (t->Lock(2, 0, &info)) {
        int wh[2];
        wh[0] = -1;
        wh[1] = -1;
        GetSizeSource()->GetSize(wh);
        GetBlitter()->Blit(wh[0], wh[1], (int)info.data);
        t->Unlock(&info);
    }
}
struct RefHolder {
    char pad0[8];
    TargetObj* p;                   // +8
};
struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};
struct IJobBase {                   // primary base of JobInfo (vptr at +0)
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void v3();
    virtual int* Build(int zero, void* msg);                // +0x10 (slot 4)
};
struct CVSBase {                    // vptr at +4, refcount at +8
    virtual void cv0();
    int rc8;
    CVSBase() { rc8 = 0; }
};
struct JobInfo : IJobBase, CVSBase {    // 0x1c bytes, "Graphics" heap
    bool bound;                                             // +0xc
    IRefObj* owner;                                         // +0x10
    int arg14;                                              // +0x14
    int arg18;                                              // +0x18
    JobInfo() { bound = false; owner = 0; }
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void v3();
    virtual int* Build(int zero, void* msg);
    virtual void cv0();
};
struct MsgBase {
    virtual int mv0();
    virtual int AddRef();
    virtual int Release();
    volatile long rc;               // +4
    MsgBase() { _InterlockedExchange(&rc, 0); }
};
struct JobMsg : MsgBase {           // 0x18 bytes
    JobInfo* job;                   // +8
    int pad0c;
    int arg10;                      // +0x10
    int pad14;
    JobMsg() { arg10 = 0; }
    virtual int mv0();
    virtual int AddRef();
    virtual int Release();
};
struct MsgBuf {
    int a;
    int b;
    char flag;
    int d, e;
    int tag;
    JobMsg* msg;
    int g, h, i, j;
};
struct SinkObj {
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
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void Post(int id);                              // +0x78
};
SinkObj* GetSink();                 // 0067dd50
template <class T> struct SmartP {
    T* p;
    SmartP(T* x) : p(x) { if (p) p->AddRef(); }
    ~SmartP() { if (p) p->Release(); }
    T* operator->() const { return p; }
};
#define FLT_BIG 3.402823466e+38f
struct Vector3_s007b_55f0 {
    float x, y, z;
    Vector3_s007b_55f0() {}
    Vector3_s007b_55f0(float a, float b, float c) { x = a; y = b; z = c; }
};
struct Bounds6_s007b_55f0 {
    Vector3_s007b_55f0 mn;
    Vector3_s007b_55f0 mx;
    Bounds6_s007b_55f0() { mn = Vector3_s007b_55f0(FLT_BIG, FLT_BIG, FLT_BIG); mx = Vector3_s007b_55f0(-FLT_BIG, -FLT_BIG, -FLT_BIG); }
    void Expand(const Vector3_s007b_55f0* p, int n, int stride);       // 007b4c10 0x007b4c10
};
struct MeshGeom {
    int count;                      // +0x10
    const Vector3_s007b_55f0* verts;           // +0x14
};
struct MeshEntry {                  // 0x20 bytes
    char pad0[0x10];
    MeshGeom geom;
    char pad18[2];
    unsigned short stride;          // +0x1a
    char pad1c[4];
};
struct MeshObj {
    char pad0[8];
    MeshEntry* entries;             // +8
};
struct MeshVec {
    MeshObj** begin;
    MeshObj** end;
};
int __cdecl FindEntry(MeshObj* o, int a, int b, int c, int d);   // 0071ddc0
struct ViewParams {
    char pad0[0x3c];
    float offX;                     // +0x3c
    float offY;                     // +0x40
    float padX;                     // +0x44
    float padY;                     // +0x48
    float scale;                    // +0x4c
    float sx, sy;                   // +0x50, +0x54
    float z;                        // +0x58
};
struct ViewNode {
    char pad0[0x0c];
    ViewParams** params;            // +0xc
};
struct FrameScene {
    char pad0[8];
    int w8;                         // +8
    int hc;                         // +0xc
    ViewNode* node;                 // +0x10
    char pad14[0x0c];
    float fitSize;                  // +0x20
    float fitAspect;                // +0x24
};
struct FrameJob {
    char pad0[0x18];
    int a18, b1c;                   // +0x18, +0x1c
    char pad20[4];
    int h;                          // +0x24
    int w;                          // +0x28
    unsigned char* data;            // +0x2c  (RGBA, 4 bytes per pixel)
    FrameScene* sc;                 // +0x30
    void Fit();
    void FitAspect();
};
struct Matrix3 {
    Vector3_s007b_55f0 row0, row1, row2;
    Matrix3& Assign(const Matrix3& m);          // 0041cb40
};
struct XForm {                      // transform block: flags, change counter, position, scale, basis
    unsigned short flags;           // +0
    unsigned short rev;             // +2
    Vector3_s007b_55f0 pos;                    // +4
    float scale;                    // +0x10
    Matrix3 m;                      // +0x14
    void PreRotateY(float a);       // 006baa70
};
struct cFrustumCull {
    unsigned int data[0x3c];
    void Setup(const float* viewProj);                          // 006ffe00
    unsigned FrustumTestSphere(const float* a, const float* b, int c);   // 00700120
};
struct FitViewer {
    char pad0[0xc0];
    float viewProj[16];             // +0xc0
    void SetFov(float f);           // 007c4b50
    void SetXForm(XForm* x);        // 007c40f0
    void SetViewAngleY(float a);    // 007c53d0
    void SetNear(float n);          // 007c4ba0
    void ApplyXForm(XForm* x);      // 007c4d00
};
struct FitScene {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void Attach(int zero, FitViewer* v);            // +0x20
};
struct FitDevice {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12();
    virtual bool Select(int target);                        // +0x34
    virtual FitScene* GetScene();                           // +0x38
    virtual int GetCurrent();                               // +0x3c
};
struct FitApp {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual FitDevice* GetDevice();                         // +0x50
};
FitApp* GetApp();                   // 0067dd10 (SP::App)
extern const Matrix3 g_identityBasis;       // 01635788
struct Mat16 { float m[16]; };
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
// ---- items of slice s007b55f0 end

// ---- items of slice s007b6570 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_1485720;
extern int g_16f8b10[16];
extern int g_16f8c70[16];
extern float g_13ec4b4, g_13ec4b8, g_140ffc8, g_13eb960, g_140f7ac, g_1471064;
struct Tgt3; struct Tgt3Q; struct Tgt3P; struct cViewer_s007b_6570;
struct GfxA {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v1a();
    virtual void v1b();
    virtual void v1c();
    virtual void v1d();
    virtual void v1e();
    virtual void v1f();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v2a();
    virtual void v2b();
    virtual void v2c();
    virtual void v2d();
    virtual void v2e();
    virtual void v2f();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void f57(int* out);
};
struct GfxB {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void f6(int* out);
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void f22(int* a, int* b, int c, float d);
    virtual void v17();
    virtual void v18();
    virtual void f25(int a, int b, int c, int d, int e);
};
struct FitScene_s007b_6570 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void Attach(int zero, cViewer_s007b_6570* v);
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void s19();
};
struct FitDevice_s007b_6570 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual int f7();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual bool Select(int target);
    virtual FitScene_s007b_6570* GetScene();
    virtual int GetCurrent();
};
struct App {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual FitDevice_s007b_6570* f20();
};
struct MsgSrv {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void f5(int id, void* msg, int z);
    virtual void f6(int a, int b, int c, int d);
};
struct Mgr67dd50 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v1a();
    virtual void v1b();
    virtual void v1c();
    virtual void v1d();
    virtual void f30(void* self, int z, void* st);
};
struct Tgt3 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void f3(int a, int b, int c, int d);
};
struct SlotObj {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual Tgt3* f4();
};
struct Tgt3P {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void f3(int a, void* p, int c, int d);
};
struct Obj79 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v1a();
    virtual void v1b();
    virtual void v1c();
    virtual void v1d();
    virtual void v1e();
    virtual void v1f();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v2a();
    virtual void v2b();
    virtual void v2c();
    virtual void v2d();
    virtual void v2e();
    virtual void v2f();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v3a();
    virtual void v3b();
    virtual void v3c();
    virtual void v3d();
    virtual void v3e();
    virtual void v3f();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v4a();
    virtual void v4b();
    virtual void v4c();
    virtual void v4d();
    virtual void v4e();
    virtual Tgt3Q* f79();
};
struct Tgt3Q {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void f3(int a, int b, void* p, int d);
};
struct Obj0c {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void f3(int a, int b, void* p, int d);
};
struct ViewerRef { int viewer; int z0, z1, z2; };      // {viewer,0,0,0} context handed to job callbacks
struct cViewer_s007b_6570 {
    char pad0[0xc0];
    float viewProj[16];                    // +0xc0
    void Copy(int a, int b, int c);        // 0x7c50b0
    void F4b50(float v);                   // 0x7c4b50
    void SetRaster(const int* r, int a);   // 0x7c4be0
    void F3c20(const float* v);            // 0x7c3c20
    void F3c50(int a);                     // 0x7c3c50
    void F4a60(int* rect);                 // 0x7c4a60
    bool Update();                         // 0x7c4fd0
    void F3c10();                          // 0x7c3c10
    void SetViewAngleY(float a);           // 0x7c53d0
    void F40f0(void* xf);                  // 0x7c40f0
    void F4d00(void* xf);                  // 0x7c4d00
    float F40a0();                         // 0x7c40a0
    void F4ba0(float a);                   // 0x7c4ba0
};
GfxA*      __cdecl Gfx_67dd40();
GfxB*      __cdecl Gfx_67ddb0();
void*      __cdecl Gfx_67dda0();
App*       __cdecl SP_App();                 // 0x67dd10
MsgSrv*    __cdecl SP_MessageServer();       // 0x67dcc0
Mgr67dd50* __cdecl Mgr_67dd50();
void __cdecl shader(int id, const void* data, int on);   // 0x777ae0
struct AtomicInt32 {
    volatile long mn;
    void Set(long v) { _InterlockedExchange(&mn, v); }
};
struct MsgHdr {
    virtual void s0();
    virtual void AddRef();
    virtual void Release();
    AtomicInt32 mRefCount;     // +0x04
    int f8;
    int fc;
    int f10;
    int f14;
    MsgHdr() : f10(0) {}
};
struct MsgBase_s007b_6570 : MsgHdr {
    virtual void s0();
    virtual void AddRef();
    virtual void Release();
    MsgBase_s007b_6570() { mRefCount.Set(0); }
};
struct Msg : MsgBase_s007b_6570 {
    Msg() {}
    virtual void s0();
};
struct MsgRef {
    Msg* p;
    MsgRef(Msg* x) : p(x) { if (p) ((void(__thiscall*)(Msg*))(*(void***)p)[1])(p); }
    ~MsgRef() { p->Release(); }
};
struct Obj14 { char pad[0xc]; Obj0c* o; };
struct ThumbA {
    char pad[0x10];
    cViewer_s007b_6570* viewer;     // +0x10
    Obj14*   p14;        // +0x14
    void Fn35a0();       // 0x7b35a0
    void Run6570(int a1, int a2, int* a3, int a4);
};
struct ThumbB {
    char pad0[0xc];
    cViewer_s007b_6570* viewerA;     // +0x0c
    cViewer_s007b_6570* viewerB;     // +0x10
    int      m14[16];     // +0x14
    int      m54[16];     // +0x54
    int      r94[2];      // +0x94
    int      r9c[2];      // +0x9c
    char     pada4[4];
    Obj79*   oa8;         // +0xa8
    char     padac[0x14];
    GfxB*    oc0;         // +0xc0
    char     padc4[0x14];
    bool     bd8;         // +0xd8
    void Fn3820(cViewer_s007b_6570* v, int* r, int a);    // 0x7b3820
    void Run6730(int a1, int a2, int a3, int a4);
};
struct ThumbC {
    char pad0[0x108c];
    cViewer_s007b_6570* viewer;    // +0x108c
    char pad1[0x10f4 - 0x1090];
    int      raster[2]; // +0x10f4
    ThumbC*  next;      // +0x10fc
    void Fn49f0(int a, int b, ViewerRef* c, int d);   // 0x7b49f0
    void Run68f0(int flag, int a2, int a3, int a4, int a5);
};
struct JobStatus {
    int  one;
    int  zero;
    char flag;
    int  z[8];
};
struct ThumbD {
    char pad0[0xc];
    SlotObj** begin;   // +0x0c
    SlotObj** end;     // +0x10
    char pad1[0x10];
    int count;         // +0x24 ... (+0x14..+0x23 above)
    int index;         // +0x28
    int msgId;         // +0x2c
    int msgArg;        // +0x30
    void Fn49f0(int a, int b, int c, int d);   // 0x7b49f0
    void Run6980(int a, int b, int c, int d);
};
struct ItemList2 {
    char pad0[0x20];
    IItem** begin;      // +0x20
    IItem** end;        // +0x24
    void Other();
    void Fn(int a, int b, int c, int d);
};
void __cdecl operator_delete__(void* p) throw();     // 0xf47380
struct IRef2 { virtual void s0(); virtual void s1(); virtual void Release2(); };
struct VBase {
    IRef2** mBegin;
    IRef2** mEnd;
    ~VBase() {
        if (mBegin && ((int*)mBegin)[-1])
            operator_delete__(mBegin);
    }
};
struct RefVec : VBase {
    ~RefVec();
};
static inline void DestroyRange(IRef2** first, IRef2** last)
{
    for (; first < last; ++first)
        if (*first) (*first)->Release2();
}
struct IRef1 { virtual void s0(); virtual void Release1(); };
struct RefP1 {
    IRef1* p;
    ~RefP1() { if (p) p->Release1(); }
};
struct Str16 {
    unsigned short* mBegin;
    unsigned short* mEnd;
    unsigned short* mCap;
    ~Str16() {
        if ((((int)mCap - (int)mBegin) & ~1) > 2 && mBegin)
            operator_delete__(mBegin);
    }
};
struct Base0 {
    virtual ~Base0() {}
};
struct AbilityA : Base0 {
    char  pad[0x40 - 4];
    RefP1 m40;        // +0x40
    Str16 m44;        // +0x44
    char  pad50[4];
    RefP1 m54;        // +0x54
    ~AbilityA();
};
struct AtomicLong {
    volatile long mn;
};
static inline long AtomicAdd(volatile long* p, long v) { return _InterlockedExchangeAdd(p, v); }
struct RcObj { char pad[8]; AtomicLong rc; };
struct AtomicPtr {
    RcObj* p;
    ~AtomicPtr() {
        if (p) {
            AtomicLong* c = &p->rc;
            AtomicAdd(&c->mn, -1);
            long v = AtomicAdd(&c->mn, 0);
            if (v < 1) AtomicAdd(&c->mn, 1);
            else AtomicAdd(&c->mn, 0);
        }
    }
};
struct AbilityB : Base0 {
    char      pad[4];
    AtomicPtr m8;     // +0x08
    char      padc[4];
    RefP1     m10;    // +0x10
    char      pad14[4];
    char*     mBegin; // +0x18
    char*     mEnd;
    char*     mCap;   // +0x20
    ~AbilityB();
};
struct Vector3_s007b_6570 {
    float x, y, z;
    Vector3_s007b_6570() {}
    Vector3_s007b_6570(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3_s007b_6570 operator+(const Vector3_s007b_6570& b) const { return Vector3_s007b_6570(x + b.x, y + b.y, z + b.z); }
    Vector3_s007b_6570 operator-(const Vector3_s007b_6570& b) const { return Vector3_s007b_6570(x - b.x, y - b.y, z - b.z); }
    Vector3_s007b_6570 operator*(float s) const { return Vector3_s007b_6570(x * s, y * s, z * s); }
    Vector3_s007b_6570& operator+=(const Vector3_s007b_6570& b) { x += b.x; y += b.y; z += b.z; return *this; }
};
struct Matrix3_s007b_6570 {
    Vector3_s007b_6570 row0, row1, row2;
    Matrix3_s007b_6570& Assign(const Matrix3_s007b_6570& m);          // 0x41cb40
};
struct XForm_s007b_6570 {                      // flags, change counter, position, scale, basis
    unsigned short flags;           // +0
    unsigned short rev;             // +2
    Vector3_s007b_6570 pos;                    // +4
    float scale;                    // +0x10
    Matrix3_s007b_6570 m;                      // +0x14
    void PreRotateY(float a);       // 0x6baa70
};
struct cFrustumCull_s007b_6570 {
    char data[0xf0];
    void Setup(const float* viewProj);                                   // 0x6ffe00
    char FrustumTestSphere(const float* a, const float* b, int c);       // 0x700120
};
struct SphV {
    float x, y, z;
    SphV() {}
    SphV(const SphV& o) { x = o.x; y = o.y; z = o.z; }
};
struct Sphere6 { SphV c; SphV e; };
struct SphereVec { Sphere6* begin; Sphere6* end; };
extern const Matrix3_s007b_6570 g_identityBasis_s007b_6570;                          // 0x1635788
struct FitJob {
    char Fit6d50(SphereVec* v, cViewer_s007b_6570* vw, const float* c, const float* off, float* fov);
    void Run7270(SphereVec* v, cViewer_s007b_6570* vw, int target, const float* c, float k, float yaw);
};
// ---- items of slice s007b6570 end

// ---- items of slice s007b7ac0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_Pi;                          // 0x0153c158 (runtime float)
extern uint32_t g_shaderData223;            // 0x016f6e34
extern float g_OneOver180;                  // 0x0140ffcc (0.0055555557; cl /fp:fast folds a literal 1/180 with the 360)
#pragma intrinsic(_InterlockedExchange)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct Vector3_s007b_7ac0 {
    float x, y, z;
    Vector3_s007b_7ac0() {}
    Vector3_s007b_7ac0(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s007b_7ac0(const Vector3_s007b_7ac0& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s007b_7ac0 Cross(const Vector3_s007b_7ac0& b) const
    {
        return Vector3_s007b_7ac0(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
};
struct Vector4 { float x, y, z, w; };
struct Matrix3_s007b_7ac0 {
    Vector3_s007b_7ac0 row0, row1, row2;
};
struct XForm_s007b_7ac0 {                      // transform block: flags, change counter, position, scale, basis
    unsigned short flags;           // +0
    unsigned short rev;             // +2
    Vector3_s007b_7ac0 pos;                    // +4
    float scale;                    // +0x10
    Matrix3_s007b_7ac0 m;                      // +0x14
};
struct __declspec(align(16)) RwMatrix {
    Vector3_s007b_7ac0 right; uint32_t flags;
    Vector3_s007b_7ac0 up;    uint32_t pad1;
    Vector3_s007b_7ac0 at;    uint32_t pad2;
    Vector3_s007b_7ac0 pos;   uint32_t pad3;
};
extern const Matrix3_s007b_7ac0 g_identityBasis_s007b_7ac0;       // 0x01635788
extern const Vector3_s007b_7ac0 g_defaultPos;          // 0x01635648
inline float DegreesToRadians(float degrees) { return degrees * g_Pi * g_OneOver180; }
void SetShaderData(int index, uint32_t value, int flag);                 // 0x00777ae0
void SphericalFromCartesian(Vector3_s007b_7ac0 pos, float* theta, float* phi, float* radius);   // 0x007b2600
Vector3_s007b_7ac0 OrthogonalVector(const Vector3_s007b_7ac0& v);                              // 0x006985b0
struct cViewer_s007b_7ac0 {
    void SetRaster(int* handle, bool setViewport);                       // 0x007c4be0
    void SetClearColor(const Vector4* color);                            // 0x007c3c20
    void SetClearFlags(int flags);                                       // 0x007c3c50
    void SetNear(float n);                                               // 0x007c4ba0
    void SetFar(float f);                                                // 0x007c4bc0
    void SetXForm(XForm_s007b_7ac0* x);                                             // 0x007c40f0
    void ApplyXForm(XForm_s007b_7ac0* x);                                           // 0x007c4d00
    void SetCameraToWorldFromBasis(RwMatrix* m);                         // 0x007c4d20
    void SetViewportRectArgs(unsigned short x, unsigned short y,
                             unsigned short w, unsigned short h);        // 0x007c5310
};
struct RenderInfo {
    cViewer_s007b_7ac0* viewer;
    int a, b, c;
};
struct IRenderer {
    PV2 PV
    virtual void Render(int p1, int p2, RenderInfo* info, int p4);      // +0x0c
};
struct ThumbSettings {
    uint32_t pad00[4];
    IRenderer* mpRenderer;          // +0x10
    int mMode;                      // +0x14
};
struct IRasterSource {              // FUN_0067dd40
    PV8 PV8 PV8 PV8 PV8 PV8 PV
    virtual void GetCaptureRaster(int* handle);                          // +0xc4
    PV4 PV2 PV
    virtual void GetTargetRaster(int* handle);                           // +0xe4
};
struct ICapture {                   // FUN_0067ddb0
    PV4 PV2
    virtual void GetSize(int* wh);                                       // +0x18
    PV8 PV4 PV2
    virtual void CaptureTile(cViewer_s007b_7ac0* v, int* target, int* source, int p4, float alpha); // +0x54
    virtual void Capture(int* source, int* target, int p4, float alpha); // +0x58
};
struct IBlitter {                   // FUN_0067dda0
    PV8 PV
    virtual void MeasureSomething(int w, int h, int* o0, int* o1, int* o2, int* o3); // +0x24
};
IRasterSource* GetRasterSource();   // 0x0067dd40
ICapture* GetCapture();             // 0x0067ddb0
IBlitter* GetBlitter_s007b_7ac0();             // 0x0067dda0
struct BehaviorMessage {
    virtual int mv0();
    virtual int AddRef();           // +4
    virtual int Release();          // +8
    volatile long mRefCount;        // +4
    BehaviorMessage() { _InterlockedExchange(&mRefCount, 0); }
};
struct ThumbMessage : BehaviorMessage {     // 0x18 bytes
    cViewer_s007b_7ac0* mpViewer;              // +8
    int pad0c;
    int m10;                        // +0x10
    int pad14;
    ThumbMessage() { m10 = 0; }
    virtual int mv0();
    virtual int AddRef();
    virtual int Release();
};
struct IMessageServer {
    PV4 PV
    virtual void PostMessage(uint32_t id, ThumbMessage* msg, int zero);  // +0x14
};
IMessageServer* MessageServer();    // 0x0067dcc0
struct Property {
    uint32_t data[4];
    uint8_t flags;                  // +0x10
    uint8_t pad11;
    unsigned short type;            // +0x12
    float* AsVector();              // 0x006bb610 (default vector)
};
struct cDirectPropertyList {
    PV8 PV2
    virtual Property* GetProperty(uint32_t id);                          // +0x28
    int GetIntProperty(uint32_t id);                                     // 0x006a2660
    bool GetBoolProperty(uint32_t id);                                   // 0x006a25a0
    void SetBoolProperty(uint32_t id, bool value);                       // 0x006a17e0
};
extern cDirectPropertyList* sAppProperties;  // 0x015fd918
static __forceinline const float* GetVector3Value(Property* p)
{
    unsigned short type = p->type;
    if (type == 0x34 || type == 0x10) {
        if (p->flags & 0x30)
            return *(float**)p;
        return type ? (float*)p : 0;
    }
    return p->AsVector();
}
struct cThumbnailManager {
    uint32_t pad00[4];
    cViewer_s007b_7ac0* mpViewer;              // +0x10
    ThumbSettings* mpSettings;      // +0x14

    void FinishSingle();                                                 // 0x007b35a0
    void FinishTiled(int tileSize);                                      // 0x007b3630
    void Render(int p1, int p2, const RenderInfo* ri, int p4);
};
// ---- items of slice s007b7ac0 end

// ---- items of slice s007b87f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtbl_1410024[];
extern void* g_vtbl_1410014[];
extern void* g_vtbl_13ec458[];
extern void* g_vtbl_13eb938[];
#pragma float_control(precise, off, push)
#pragma float_control(pop)
void operator delete[](void*);   // 0x00f47380
struct Pair2 { int a, b; };
struct RawVec {
    Pair2* begin;
    Pair2* end;
    Pair2* cap;
    void push_back(Pair2* p);
    void DoInsertValue(Pair2* pos, Pair2* p);   // out-of-line vector grow (006ec390)
};
struct VecPair {
    char pad0[0x24];
    RawVec v;                           // +0x24
    void Push(Pair2* p);
};
void RawVec::push_back(Pair2* p)
{
    Pair2* e = end;
    if (e < cap) {
        end = e + 1;
        if (e)
            *e = *p;
    } else {
        DoInsertValue(e, p);
    }
}
struct ShutdownViewer {
    void Destroy1();                    // 007c3ba0
    void Destroy2();                    // 007c4000
};
struct PostFilterVec {
    void* b; void* e; void* c;
    void erase(void* first, void* last);   // 00d018d0
    void* begin() { return b; }
    void* end() { return e; }
    bool empty() const { return b == e; }
    void clear() { erase(begin(), end()); }
};
struct cJobPostFilter {
    virtual void v0();
    virtual void Release();             // vtbl+4
    char pad0[0x18 - 4];
    int* m_p18;                         // +0x18
    char pad1[0x24 - 0x1c];
    PostFilterVec m_vec;                // +0x24
    char pad2[0x38 - 0x30];
    ShutdownViewer* m_viewer;           // +0x38
    char pad3[0x80 - 0x3c];
    bool m_flag;                        // +0x80
    bool m_b81;                         // +0x81
    void Shutdown();
    void Init(bool b81);
    void Init(int a, const int* p, const int* q, bool b81);
};
typedef unsigned int uint;
#define VSLOT(obj, idx) ((*(void***)(obj))[idx])
void operator delete(void*, const char*, int, int, int, int);
struct RefVec_s007b_87f0 {  // 0041eb80 = ~RefVector
    void* b;
    void* e;
    void* c;
    void Destroy();
};
struct IRel { virtual void v0(); virtual void Release(); };
struct cFilterRes {
    void** vtbl0;                       // +0
    void** vtbl1;                       // +4
    int m08, m0c, m10;
    char pad14[0x94 - 0x14];
    int m94, m98, m9c, ma0;             // -1
    IRel* ma4;                          // +0xa4
    IRel* ma8;                          // +0xa8
    RefVec_s007b_87f0 mac;                         // +0xac..0xb7
    char padb8[0xc0 - 0xb8];
    int mc0;
    char mc4;
    char padc5[0xd8 - 0xc5];
    char md8;
    cFilterRes* Ctor();
    void Dtor();
};
struct cViewer_s007b_87f0 {
    char pad[0x174];
    cViewer_s007b_87f0();                          // 007c3f70
    void Init(int);                     // 007c4dd0 0x004b8c10
    void Fn3cc0(int);                   // 007c3cc0
};
static __forceinline cViewer_s007b_87f0* NewViewer()
{
    return new ("Graphics", 0, 0, 0, 0) cViewer_s007b_87f0();
}
struct IRC2 { virtual void AddRef(); virtual void Release(); };
struct ARC {
    IRC2* p;
    ARC(IRC2* q) : p(q) { if (p) p->AddRef(); }
    ~ARC() { if (p) p->Release(); }
};
struct FilterRef {
    cJobPostFilter* mpObject;
    void reset() { cJobPostFilter* p = mpObject; if (p) { mpObject = 0; p->Release(); } }
};
struct FilterVec {
    FilterRef* mpBegin;
    FilterRef* mpEnd;
    FilterRef* mpCap;
    FilterRef& operator[](uint i) { return mpBegin[i]; }
    void clear() { erase(mpBegin, mpEnd); }
    bool empty() const { return mpBegin == mpEnd; }
    uint size() const { return (uint)(mpEnd - mpBegin); }
    void push_back(const ARC& v);                                // 007a6ac0
    void erase(FilterRef* first, FilterRef* last);   // eastl::vector<AutoRefCount<..>>::erase
};
struct cFilterChainJob {
    char pad0[0xc];
    FilterVec mFilters;                 // +0xc
    char pad18[0x20 - 0x18];   // allocator
    bool mInitialized;                  // +0x20
    void Shutdown();
    int  AddFilter(IRel* p);
};
struct PtrFixedVec {
    void** begin;
    void** end;
    void** cap;
    void*  buf[14];
    PtrFixedVec() { begin = end = buf; cap = buf + 14; }
    ~PtrFixedVec() { if (begin && begin != buf) operator delete[](begin); }
};
struct BBox6 { float mn[3]; float mx[3]; };
struct CaptureCam {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    int pad[2];
    float radius;                       // +0xc
};
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct CapBox { Vec3 mn; Vec3 mx; };
struct CapBoxVec {
    CapBox* b; CapBox* e; CapBox* c;
    void DoInsertValue(CapBox* pos, const CapBox* v);                  // 00424010
    ~CapBoxVec() { if (b && ((int*)b)[-1]) operator delete[](b); }
};
unsigned int __cdecl FNV1_String8(const char* s, unsigned int h, int n);   // 00932e80
void* LightingManager();                                                  // 0067dd90
void* CaptureService();                                                   // 0067ddb0
struct cPlanetCapture {
    char pad0[0xc];
    bool mInit;                         // +0xc
    char pad1[3];
    cViewer_s007b_87f0* mViewer;                   // +0x10
    CaptureCam* mCam;                   // +0x14
    void Setup(CaptureCam* cam);
};
struct ResKey { unsigned int a, b, c; };
struct cCSAJobParams {
    char pad0[8];
    int m8, mc;                         // +8, +0xc
    char pad10[0x28 - 0x10];
    unsigned int mTileCount;            // +0x28
    unsigned int mId;                   // +0x2c
    int m30;                            // +0x30
    char pad34[0x40 - 0x34];
    struct cTileSink* mSink;            // +0x40
    const wchar_t* mName;               // +0x44
    char pad48[0x54 - 0x48];
    void* m54;                          // +0x54
};
struct cTileSink { char pad[0xc]; int** mpData; void Flush(int, int, void*, int);   /* 007b49f0 */ };
struct cTileViewer {
    void Copy(int, int, int);                       // 007c50b0
    void Fn3c20(void*);                             // 007c3c20
    void Fn40c0(float*, float*);                    // 007c40c0
    void Fn4b00(float, float);                      // 007c4b00
    void SetPos(float, float);                      // 007c4ad0
    void SetRaster(void*, int);                     // 007c4be0
    void Fn3c50(int);                               // 007c3c50
};
struct cImageObj {
    virtual void AddRef();
    virtual void Release();
    int m08, m0c, m10;
    char pad[0x38 - 0x14];
    cImageObj* Ctor(int w, int h, void* pixels, unsigned id, unsigned fmt);  // 007b4e10
};
struct WStr {
    wchar_t* b; wchar_t* e; wchar_t* c;
    WStr() { b = e = (wchar_t*)0x1667bac; c = (wchar_t*)0x1667bae; }
    ~WStr() { if ((((int)c - (int)b) & ~1) > 2 && b) operator delete[](b); }
};
void  WStr_Format(WStr*, const wchar_t*, ...);                // 0041e050
void* GetRTTManager();                                        // 0067dda0
void* GetRenderer();                                          // 0067dd50
void* GetSaveArea(int);                                       // 006b1f90
void* GetResourceMan();                                       // 0067dcd0
void  AsyncSave(cImageObj*, void*, int, ResKey*);             // 006b4b60
struct cCSAThumbnailJob {
    char pad0[0x10];
    void* mA;                           // +0x10
    void* mB;                           // +0x14
    cTileViewer* mViewer;               // +0x18
    char pad1c[4];
    cCSAJobParams* mP;                  // +0x20
    void RenderLargeTiledImage(int a0, int a1, int* a2, int a3);
};
// ---- items of slice s007b87f0 end

// ---- items of slice s007b97d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct TerrainFilter {
    virtual void slot0();
    virtual void Release();             // vtable +4
    void InnerTeardown();               // 007b9620
};
struct Viewer {
    void Destroy1();                    // 007c3ba0
    void Destroy2();                    // 007c4000
};
struct TerrainMgr {
    char pad0[0x10d1];
    bool m_terrainFilterInitialized;    // +0x10d1
    TerrainFilter* m_filter0;           // +0x10d4
    TerrainFilter* m_filter1;           // +0x10d8
    TerrainFilter* m_filter2;           // +0x10dc
    Viewer* m_viewer;                   // +0x10e0
    void Teardown();
};
// ---- items of slice s007b97d0 end

// ---- items of slice s007bb670 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RectID { int mPageID; int mAllocID; };
struct cFilterChainJob_s007b_b670 { void Shutdown(); };
struct ModelObj {
    virtual void v0();       // +0
    virtual void v1();       // +4
    char pad[0x38];
    int  m40;                // +0x40
};
struct Thumb {
    char pad[0xc];
    int  m0c;                // +0xc
    int  m10;                // +0x10
    char pad2[0x94];
    ModelObj* m_a8;          // +0xa8
    char pad3[0x18];
    unsigned char m_c4;      // +0xc4
};
struct BehaviorMessage_s007b_b670 {
    virtual void v0();       // +0
    virtual void v1();       // +4
    virtual void v2();       // +8
    int  mRefCount;          // +4
    int  m8;                 // +8
    int  mc;                 // +0xc
    int  m10;                // +0x10
    int  m14;
    int  m18;                // +0x18
    int  m1c;
    int  m20;                // +0x20
    int  m24;
    int  m28;                // +0x28
};
struct MessageServer_t {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void Send(int id, BehaviorMessage_s007b_b670* msg, int a);   // +0x14
};
extern "C" MessageServer_t* __cdecl SP_MessageServer_s007b_b670();
struct cThumbnailManager_s007b_b670 {
    char pad[0x10c8];
    ModelObj*     mModel;        // +0x10c8
    char pad2[0x10fc - 0x10cc];
    cFilterChainJob_s007b_b670* mFilterChain;   // +0x10fc
    Thumb* mThumbs[1024];        // +0x1100

    void HandleSomething(void* msg);  // 0x007bbde0 (cThumbnailManager::HandleSomething)
};
// ---- items of slice s007bb670 end

// ---- items of slice s007bbf80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gDefaultFloat;                                   // 0x15d1168
struct Key2 { uint32_t a, b; };
struct Vec4 {
    float x, y, z, w;
    Vec4(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
};
template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) { mpObject = p; if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void reset() { T* t = mpObject; if (t) { mpObject = 0; t->Release(); } }
};
struct Property_s007b_bf80 {
    uint32_t v;
    uint8_t  pad04[0xc];
    uint8_t  flags;          // +0x10
    uint8_t  pad11;
    uint16_t type;           // +0x12
};
static inline float PropGetFloat(Property_s007b_bf80* p) {
    float* r;
    uint16_t t = p->type;
    if (t == 0xd || t == 0x10) {
        if (p->flags & 0x30)
            r = *(float**)p;
        else
            r = (float*)(t != 0 ? p : 0);
    } else {
        r = &gDefaultFloat;
    }
    return *r;
}
struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual Property_s007b_bf80* GetProperty(uint32_t id);                // slot 10 (+0x28)
    bool GetDescription(uint32_t id);                          // 0x6a25a0
};
extern cPropertyList* sAppProperties_s007b_bf80;                          // 0x15fd918
struct IPropertyManager {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, AutoRefCount<cPropertyList>* out);  // slot 11 (+0x2c)
};
IPropertyManager* __cdecl PropertyManager();                   // 0x67de30
struct PostMsg;
struct cContentValidationSummarizer;
struct IMgr {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void Post(cContentValidationSummarizer* sender, int a, PostMsg* msg);       // slot 30 (+0x78)
};
IMgr* __cdecl GetMgr();                                        // 0x67dd50
struct IRtt {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42();
    virtual void GetRectAC(Key2* out);                         // slot 43 (+0xac)
    virtual void GetRectB0(Key2* out);                         // slot 44 (+0xb0)
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void GetRectC8(Key2* out);                         // slot 50 (+0xc8)
    virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
    virtual void GetRectE0(Key2* out, int index);              // slot 56 (+0xe0)
};
IRtt* __cdecl GetRtt();                                        // 0x67dd40
struct SumBaseA {
    virtual int AddRef();
    virtual int Release();
};
struct SumBaseB {
    virtual void b0();
    virtual void b1();
    int m8;
    SumBaseB() { m8 = 0; }
};
struct cContentValidationSummarizer : SumBaseA, SumBaseB {
    int mc, m10, m14, m18, m1c;
    uint8_t m20;
    int m24, m28, m2c, m30;
    cContentValidationSummarizer() {
        mc = 0; m10 = 0; m14 = 0;
        m20 = 0;
        m24 = 0; m28 = 0; m2c = 0; m30 = 0;
    }
    void AddJob(struct cFilterChainJob_s007b_bf80* job);                  // 0x7b9750
};
struct JobVec {
    Key2* mpBegin;
    Key2* mpEnd;
    Key2* mpCapacity;
    void DoInsertValue(Key2* pPosition, const Key2& val);       // 0x6ec390
    void push_back(const Key2& v) {
        Key2* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p) { p->a = v.a; p->b = v.b; }
        } else {
            DoInsertValue(p, v);
        }
    }
};
struct cFilterChainJob_s007b_bf80 {
    virtual int AddRef();
    virtual int Release();
    uint32_t f04, f08;
    uint32_t f0c, f10, f14, f18, f1c, f20;
    JobVec inputs;                    // +0x24
    uint32_t pad30[3];
    float f3c, f40, f44, f48, f4c, f50, f54, f58;
    uint32_t pad5c[4];
    float f6c, f70, f74, f78;
    uint8_t pad7c[6];
    uint8_t b82;
    uint8_t pad83;
    uint32_t pad84[5];
    Vec4 v98;                         // +0x98
    uint32_t pada8[15];
    cFilterChainJob_s007b_bf80();                                          // 0x7b8550
    void Connect(uint32_t id, Key2* a, Key2* b, int flag);      // 0x7b9510
    void Init(int flag);                                        // 0x7b9420
};
struct BehaviorMessageBase {
    virtual void d0();
    virtual int AddRef();
    virtual int Release();
    volatile long mRef;
    BehaviorMessageBase() { mRef = 0; }
};
struct BehaviorMessage_s007b_bf80 : BehaviorMessageBase {
    uint32_t f08;
    uint32_t pad0c;
    uint32_t f10;
    uint32_t pad14;
    uint32_t f18;
    uint32_t f1c;
    BehaviorMessage_s007b_bf80() { f18 = 0; }
};
struct PostMsg {
    int kind;
    int a;
    uint8_t b;
    int c, d;
    uint32_t id;
    BehaviorMessage_s007b_bf80* data;
    int e, f, g, h;
    PostMsg(BehaviorMessage_s007b_bf80* bm) {
        a = 0; b = 0; c = 0; d = 0;
        e = 0; f = 0; g = 0; h = 0;
        kind = 1;
        data = bm;
        id = 0x21d752f;
    }
    ~PostMsg() { if (data) data->Release(); }
};
struct DilateReq {
    uint32_t pad0[2];
    uint32_t f08;
    uint32_t pad0c;
    uint32_t f10;
    uint32_t pad14;
    uint32_t f18;
    uint32_t pad1c;
    uint32_t f20;
};
struct cThumbnailManager_s007b_bf80 {
    uint8_t pad0[0x10bc];
    bool    mFlag10bc;
    void DilateStart(DilateReq* req);  // 0x007bbf80 (cThumbnailManager::DilateStart)
};
// ---- items of slice s007bbf80 end

// ---- items of slice s007bced0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)
namespace EA {
namespace Thread {
        struct AtomicInt_s007b_ced0 {
            volatile long mValue;
            long GetValue() const { return _InterlockedExchangeAdd((long*)&mValue, 0); }
            long Increment() { return _InterlockedIncrement((long*)&mValue); }
            long Decrement() { return _InterlockedDecrement((long*)&mValue); }
        };
}
}
namespace EA {
    template <typename T> struct RefCountTemplate_s007b_ced0 {
        virtual ~RefCountTemplate_s007b_ced0() {}
        virtual int AddRef() { return mRefCount++ + 1; }
        virtual int Release() { int n = mRefCount - 1; mRefCount = n; if (n == 0) { mRefCount = 1; delete this; } return n; }
        T mRefCount;
    };
}
namespace EA {
    template <typename T> struct AutoRefCount_s007b_ced0 {
        T* mpObject;
        AutoRefCount_s007b_ced0(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
        ~AutoRefCount_s007b_ced0() { if (mpObject) mpObject->Release(); }
        T* operator->() const { return mpObject; }
        operator T*() const { return mpObject; }
        AutoRefCount_s007b_ced0& operator=(T* pObject) {
            if (pObject != mpObject) {
                T* const pTemp = mpObject;
                if (pObject) pObject->AddRef();
                mpObject = pObject;
                if (pTemp) pTemp->Release();
            }
            return *this;
        }
    };
}
void __cdecl EASTL_deallocate(void* p);           // 0x00f47380
struct cJobPostFilter_s007b_ced0;
struct DrawCtx;
struct Vec4_s007b_ced0 {
    float x, y, z, w;
    Vec4_s007b_ced0() {}
    Vec4_s007b_ced0(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};
struct cChainBaseA { virtual int AddRef(); virtual int Release(); };
struct cChainBaseB {
    virtual void b0();
    virtual void b1();
    int mRefCount;
    cChainBaseB() { mRefCount = 0; }
};
struct cFilterChainJob_s007b_ced0 : cChainBaseA, cChainBaseB {
    cJobPostFilter_s007b_ced0** mFilterBegin;                 // +0x0c  mFilters (eastl::vector<AutoRefCount<cJobPostFilter>>)
    cJobPostFilter_s007b_ced0** mFilterEnd;                   // +0x10
    cJobPostFilter_s007b_ced0** mFilterCapacity;              // +0x14
    int m18, m1c;
    unsigned char mInitialized;                    // +0x20
    int m24, m28, m2c, m30;
    cFilterChainJob_s007b_ced0() {
        mFilterBegin = 0; mFilterEnd = 0; mFilterCapacity = 0;
        mInitialized = 0;
        m24 = 0; m28 = 0; m2c = 0; m30 = 0;
    }
    void AddFilter(cJobPostFilter_s007b_ced0* pFilter);       // 0x007b9750
    void DrawLayer(int a0, int layer, DrawCtx* ctx, int a3);   // 0x007b49f0
    void Shutdown();                               // 0x007b96d0
};
struct cTextureInstance {                          // refcount at +8, non-virtual
    void* mRaster;                                 // +0x00
    unsigned char mFlags;                          // +0x04
    char pad[3];
    EA::Thread::AtomicInt_s007b_ced0 mRefCount;               // +0x08
    void AddRef() { mRefCount.Increment(); }
    void Release() {
        mRefCount.Decrement();
        if (mRefCount.GetValue() < 1)
            mRefCount.Increment();
        else
            mRefCount.GetValue();
    }
};
struct cViewer_s007b_ced0 {
    void FUN_007c3ba0();                           // 0x007c3ba0
    void FUN_007c4000();                           // 0x007c4000
    void Copy(const cViewer_s007b_ced0* src, int a, int b);   // 0x007c50b0 (SP::cViewer::Copy)
    void SetClearColor(const Vec4_s007b_ced0& c);            // 0x007c3c20
    void Flush(int mode);                          // 0x007c3c50
    void SetRaster(const RectID* r, int a);        // 0x007c4be0
    void FUN_007c40c0(float* a, float* b);         // 0x007c40c0 (reads two view extents)
    void FUN_007c4b00(float a, float b);           // 0x007c4b00 (writes the two view extents)
    void FUN_007c4ad0(float a, float b);           // 0x007c4ad0 (view offset)
    void SetViewportRect(int x, int y, int w, int h);   // 0x007c5310
};
struct DrawCtx {                                   // argument 3 of DrawLayer
    cViewer_s007b_ced0* viewer;
    int a, b, c;
};
struct ILayerDraw {                                // world->GetLayerDraw()
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void Draw(int a0, int layer, DrawCtx* ctx, int a3);   // +0xc
};
struct cPaletteJobInfo : EA::RefCountTemplate_s007b_ced0<int> {
    int mRectId0;                                  // +0x08
    int mRectId1;                                  // +0x0c
    EA::AutoRefCount_s007b_ced0<cFilterChainJob_s007b_ced0> mPostProcessLayer;   // +0x10
    unsigned mCameraId;                            // +0x14
    unsigned mWidth;                               // +0x18
    unsigned mHeight;                              // +0x1c
    unsigned mInstance;                            // +0x20
    unsigned mGroup;                               // +0x24
    bool mUseImageSpaceFraming;                    // +0x28
    void Shutdown();
};
struct cEditorJobInfo : EA::RefCountTemplate_s007b_ced0<int> {
    int mRectId0;                                  // +0x08
    int mRectId1;                                  // +0x0c
    EA::AutoRefCount_s007b_ced0<cFilterChainJob_s007b_ced0> mPostProcessLayer;   // +0x10
    unsigned mWidth;                               // +0x14
    unsigned mHeight;                              // +0x18
    EA::AutoRefCount_s007b_ced0<cTextureInstance> mThumbnailTex;      // +0x1c
    void Shutdown();
};
struct cCSAJobInfo : EA::RefCountTemplate_s007b_ced0<int> {
    RectID mLargeRectId;                           // +0x08
    RectID mSmallRectId;                           // +0x10
    RectID mAntiAliasRectId;                       // +0x18
    unsigned mResLarge;                            // +0x20
    unsigned mResSmall;                            // +0x24
    char pad28[0x40 - 0x28];
    EA::AutoRefCount_s007b_ced0<cFilterChainJob_s007b_ced0> mPostProcessLayer;   // +0x40
    char pad44[0x54 - 0x44];
    ILayerDraw* mExtraLayer;                       // +0x54
    void Shutdown();
};
struct cGameThumbJobInfo : EA::RefCountTemplate_s007b_ced0<int> {
    unsigned mRes;                                 // +0x08
    unsigned mGroup;                               // +0x0c
    unsigned mInstance;                            // +0x10
    int mRectId0;                                  // +0x14
    int mRectId1;                                  // +0x18
    unsigned mWidth;                               // +0x1c
    unsigned mHeight;                              // +0x20
    EA::AutoRefCount_s007b_ced0<cFilterChainJob_s007b_ced0> mPostProcessLayer;   // +0x24
    void Shutdown();
};
struct cPaletteThumbnailJob {
    char pad0[0xc];
    bool mInitialized;                             // +0x0c
    void* mModelWorld;                             // +0x10
    cViewer_s007b_ced0* mViewer;                              // +0x14
    int mBounds[2];                                // +0x18
    unsigned mTextureSize;                         // +0x20
    int mBoundsTextureWidth;                       // +0x24
    int mBoundsTextureHeight;                      // +0x28
    unsigned char* mTempPixelData;                 // +0x2c
    EA::AutoRefCount_s007b_ced0<cPaletteJobInfo> mInfo;       // +0x30
    void Shutdown();
};
struct cEditorThumbnailJob {
    char pad0[0xc];
    bool mInitialized;                             // +0x0c
    void* mModelWorld;                             // +0x10
    cViewer_s007b_ced0* mViewer;                              // +0x14
    int mBounds[2];                                // +0x18
    unsigned mTextureSize;                         // +0x20
    int mBoundsTextureWidth;                       // +0x24
    int mBoundsTextureHeight;                      // +0x28
    unsigned char* mTempPixelData;                 // +0x2c
    EA::AutoRefCount_s007b_ced0<cEditorJobInfo> mInfo;        // +0x30
    void Shutdown();
};
struct IModelWorld {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
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
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual void s63();
    virtual void s64();
    virtual void s65();
    virtual void s66();
    virtual void s67();
    virtual void s68();
    virtual void s69();
    virtual void s70();
    virtual void s71();
    virtual void s72();
    virtual void s73();
    virtual void s74();
    virtual void s75();
    virtual void s76();
    virtual void s77();
    virtual void s78();
    virtual ILayerDraw* GetLayerDraw();            // +0x13c
};
struct cCSAThumbnailJob_s007b_ced0 {
    char pad0[0xc];
    bool mInitialized;                             // +0x0c
    IModelWorld* mModelWorld;                      // +0x10
    IModelWorld* mBackgroundModelWorld;            // +0x14
    cViewer_s007b_ced0* mViewer;                              // +0x18
    cViewer_s007b_ced0* mFilterViewer;                        // +0x1c
    EA::AutoRefCount_s007b_ced0<cCSAJobInfo> mInfo;           // +0x20
    void Shutdown();  // 0x007bd6b0 (cCSAThumbnailJob::Shutdown)
    void DrawLayer(int a0, int layer, DrawCtx* ctx, int a3);          // 0x007bd750
    void FUN_007b3090();                                              // 0x007b3090
    void RenderLargeTiledImage(int a0, int layer, DrawCtx* ctx, int a3);   // 0x007b8cb0
};
struct cGameThumbnailJob {
    char pad0[0xc];
    bool mInitialized;                             // +0x0c
    void* mModelWorld;                             // +0x10
    cViewer_s007b_ced0* mViewer;                              // +0x14
    EA::AutoRefCount_s007b_ced0<cGameThumbJobInfo> mInfo;     // +0x18
    void Shutdown();
};
struct Obj90 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct MessageServer_s007b_ced0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void Send(int a, int b, int c, int d);            // +0x18
};
MessageServer_s007b_ced0* __cdecl SP_MessageServer_s007b_ced0();          // 0x0067dcc0
struct DilateMsg {
    char pad[8];
    int m8;                                        // +0x08
    int mc;                                        // +0x0c
    cFilterChainJob_s007b_ced0* mJob;                         // +0x10
};
struct cThumbnailManager_s007b_ced0 {
    char pad[0x10d0];
    bool mCurrentlyCapturingAO;                    // +0x10d0

    void DilateWithoutAODone(DilateMsg* msg);  // 0x007bd4c0 (cThumbnailManager::DilateWithoutAODone)
    void DilateWithoutAOStart(struct DilateReq_s007b_ced0* req);                // 0x007bced0
};
void operator delete(void* p);                                                         // 0x00f47380
struct cPropertyList_s007b_ced0 {
    bool GetDescription(unsigned id);                          // 0x006a25a0
};
extern cPropertyList_s007b_ced0* sAppProperties_s007b_ced0;                          // 0x015fd918
struct IMgr_s007b_ced0 {                                                  // 0x0067dd50
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual int* GetScreenSize();                              // +0x1c: {width, height}
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void DrawTarget(int a3, int w, int h, DrawCtx* c, int one, int zero);   // +0x40
    virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29();
    virtual void Post(void* sender, int a, void* msg);         // +0x78
};
IMgr_s007b_ced0* __cdecl GetMgr_s007b_ced0();                                        // 0x0067dd50
struct IRtt_s007b_ced0 {                                                  // 0x0067dd40
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42();
    virtual void GetRectAC(RectID* out);                       // +0xac
    virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48();
    virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55();
    virtual void GetRectE0(RectID* out, int index);            // +0xe0
};
IRtt_s007b_ced0* __cdecl GetRtt_s007b_ced0();                                        // 0x0067dd40
struct cJobPostFilter_s007b_ced0 {
    virtual int AddRef();                          // +0x00
    virtual int Release();                         // +0x04
    virtual void v2();
    virtual void Draw(int a0, int layer, DrawCtx* ctx, int a3);   // +0x0c
    unsigned mRefCountV[2];                        // +0x04 RefCountVTemplate
    unsigned mMaterialId;                          // +0x0c
    RectID mSrcRectID;                             // +0x10
    unsigned mSrcRaster;                           // +0x18
    RectID mDestRectID;                            // +0x1c
    struct RectVec {                               // eastl::vector<cRenderTargetRectID>, +0x24
        RectID* mpBegin;
        RectID* mpEnd;
        RectID* mpCapacity;
        void DoInsertValue(RectID* position, const RectID& value);   // 0x006ec390
        void push_back(const RectID& v) {
            RectID* p = mpEnd;
            if (p < mpCapacity) {
                mpEnd = p + 1;
                if (p) *p = v;
            } else {
                DoInsertValue(p, v);
            }
        }
        static RectID* copy(RectID* first, RectID* last, RectID* result) {
            for (; first != last; ++first, ++result)
                *result = *first;
            return result;
        }
        void erase(RectID* first, RectID* last) {
            if (first != last) {
                RectID* itEnd = copy(last, mpEnd, first);
                (void)itEnd;
                mpEnd -= (last - first);
            }
        }
        RectID* begin() { return mpBegin; }
        RectID* end() { return mpEnd; }
        void clear() { erase(begin(), end()); }
    } mAdditionalRectIDs;
    unsigned pad30[2];                             // +0x30
    cViewer_s007b_ced0* mViewer;                              // +0x38
    Vec4_s007b_ced0 mCustomParams[4];                         // +0x3c
    unsigned pad7c[1];
    bool mInitialized;                             // +0x80
    bool mDumpTexture;                             // +0x81
    bool mClearBeforeDraw;                         // +0x82
    bool mOverrideViewport;                        // +0x83
    int mView[4];                                  // +0x84
    int mQuadrant;                                 // +0x94
    Vec4_s007b_ced0 mClearColor;                              // +0x98
    bool mPreSetViewport;                          // +0xa8
    char padA9[0xe4 - 0xa9];

    cJobPostFilter_s007b_ced0();                              // 0x007b8550
    void Initialize(int flags);                    // 0x007b9420
    void InitBlur(int taps, const RectID& src, const RectID& dest, int flags);   // 0x007b9510
    void SetClearColor(Vec4_s007b_ced0 c) { mClearColor = c; mClearBeforeDraw = true; }     // 0x007b27a0
    void Shutdown()
    {
        if (mInitialized) {
            if (mViewer) {
                mViewer->FUN_007c3ba0();
                cViewer_s007b_ced0* v = mViewer;
                if (v) {
                    v->FUN_007c4000();
                    operator delete(v);
                }
                mViewer = 0;
            }
            if (mSrcRaster)
                mSrcRaster = 0;
            mAdditionalRectIDs.clear();
            mInitialized = false;
        }
    }
};
struct BehaviorMessage_s007b_ced0 : BehaviorMessageBase {
    unsigned f08;
    unsigned pad0c;
    unsigned f10;
    unsigned pad14;
    unsigned f18;
    unsigned f1c;
    BehaviorMessage_s007b_ced0() { f18 = 0; }
};
struct PostMsg_s007b_ced0 {
    int kind;
    int a;
    unsigned char b;
    int c, d;
    unsigned id;
    BehaviorMessage_s007b_ced0* data;
    int e, f, g, h;
    PostMsg_s007b_ced0(BehaviorMessage_s007b_ced0* bm) {
        a = 0; b = 0; c = 0; d = 0;
        e = 0; f = 0; g = 0; h = 0;
        kind = 1;
        data = bm;
        id = 0x21d752f;
    }
    ~PostMsg_s007b_ced0() { if (data) data->Release(); }
};
struct DilateReq_s007b_ced0 {
    unsigned pad0[2];
    unsigned f08;
    unsigned pad0c;
    unsigned f10;
    unsigned pad14;
    unsigned f18;
};
typedef EA::AutoRefCount_s007b_ced0<cJobPostFilter_s007b_ced0> FilterPtr;
__forceinline int RoundToInt(float f);  // 0x007bd750 (defined below; used by a stub's inline body)
void cCSAThumbnailJob_s007b_ced0::DrawLayer(int a0, int layer, DrawCtx* ctx, int a3)
{
    mViewer->Copy(ctx->viewer, 0, 0);
    Vec4_s007b_ced0 clear(0.0f, 0.0f, 0.0f, 0.0f);
    mViewer->SetClearColor(clear);
    if (!sAppProperties_s007b_ced0->GetDescription(0x5c8af84)) {
        mViewer->SetRaster(&mInfo.mpObject->mSmallRectId, 1);
        mViewer->Flush(7);
        DrawCtx c;
        c.viewer = mViewer;
        c.a = 0;
        c.b = 0;
        c.c = 0;
        mBackgroundModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
        mModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
        ILayerDraw* extra = mInfo.mpObject->mExtraLayer;
        if (extra)
            extra->Draw(a0, layer, &c, a3);
        GetMgr_s007b_ced0()->DrawTarget(a3, 0x12, 0x12, &c, 1, 0);
        if (mInfo.mpObject->mPostProcessLayer.mpObject) {
            cJobPostFilter_s007b_ced0* first = *mInfo.mpObject->mPostProcessLayer.mpObject->mFilterBegin;
            first->mDestRectID = mInfo.mpObject->mSmallRectId;
            mInfo.mpObject->mPostProcessLayer.mpObject->DrawLayer(a0, layer, &c, a3);
        }
    } else {
        mFilterViewer->Copy(mViewer, 0, 0);
        mFilterViewer->Flush(7);
        unsigned tileW = mInfo.mpObject->mResSmall;
        int* screen = GetMgr_s007b_ced0()->GetScreenSize();
        unsigned tileH = (unsigned)RoundToInt((float)screen[1] / (float)screen[0] * (float)mInfo.mpObject->mResSmall) >> 1;
        tileW >>= 1;
        float v1, v2;
        mViewer->FUN_007c40c0(&v1, &v2);
        v1 = v1 * 0.5f;
        v2 = v2 * 0.5f;
        mViewer->FUN_007c4b00(v1, v2);
        Vec4_s007b_ced0 p0(1.2f, 1.0f, 1.0f, 1.0f);
        Vec4_s007b_ced0 p1(0.0f, 1.0f, 1.0f, 0.0f);
        for (unsigned i = 0; i < 2; i++) {
            float rowF = 1.0f - (float)i * 2.0f;
            unsigned xo = i * tileW;
            for (unsigned j = 0; j < 2; j++) {
                mViewer->FUN_007c4ad0(rowF * v1, -(1.0f - (float)j * 2.0f) * v2);
                mViewer->SetRaster(&mInfo.mpObject->mAntiAliasRectId, 1);
                mViewer->Flush(7);
                DrawCtx c;
                c.viewer = mViewer;
                c.a = 0;
                c.b = 0;
                c.c = 0;
                mBackgroundModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
                mModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
                ILayerDraw* extra = mInfo.mpObject->mExtraLayer;
                if (extra)
                    extra->Draw(a0, layer, &c, a3);
                GetMgr_s007b_ced0()->DrawTarget(a3, 0x12, 0x12, &c, 1, 0);
                if (mInfo.mpObject->mPostProcessLayer.mpObject) {
                    cJobPostFilter_s007b_ced0* first = *mInfo.mpObject->mPostProcessLayer.mpObject->mFilterBegin;
                    first->mDestRectID = mInfo.mpObject->mAntiAliasRectId;
                    mInfo.mpObject->mPostProcessLayer.mpObject->DrawLayer(a0, layer, &c, a3);
                }
                mFilterViewer->SetRaster(&mInfo.mpObject->mSmallRectId, 1);
                mFilterViewer->SetViewportRect(xo, j * tileH, tileW, tileH);
                FilterPtr filter(new ("Graphics", 0, 0, 0, 0) cJobPostFilter_s007b_ced0());
                filter.mpObject->Initialize(0);
                filter.mpObject->mMaterialId = 0x88549f64;
                filter.mpObject->mSrcRectID = mInfo.mpObject->mAntiAliasRectId;
                filter.mpObject->mDestRectID = mInfo.mpObject->mSmallRectId;
                filter.mpObject->mCustomParams[0] = p0;
                filter.mpObject->mCustomParams[1] = p1;
                filter.mpObject->mCustomParams[3] = clear;
                filter.mpObject->mPreSetViewport = true;
                DrawCtx c2;
                c2.viewer = mFilterViewer;
                c2.a = 0;
                c2.b = 0;
                c2.c = 0;
                filter.mpObject->Draw(0, 0, &c2, a3);
                filter.mpObject->Shutdown();
            }
        }
    }
    FUN_007b3090();
    RenderLargeTiledImage(a0, layer, ctx, a3);
}
// ---- items of slice s007bced0 end

// ---- items of slice s007bde20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_fFltMax;      // [0x140fd1c]
extern float g_fNegFltMax;   // [0x13f51ac]
extern float g_fVecX;  // 0x01635640
    extern float g_fVecY; // 0x01635644
void* operator new(size_t size, const char* name, int a, int b, int c, int d);
struct Vec3_s007b_de20 { float x, y, z; Vec3_s007b_de20(const float& a, const float& b, const float& c) { x = a; y = b; z = c; } Vec3_s007b_de20() {} };
struct cRenderTargetRectID { int mPageID; int mAllocID; };
struct cViewer_s007b_de20
{
    uint32_t pad[0x5d];
    cViewer_s007b_de20();             // 0x7c3f70
    ~cViewer_s007b_de20();            // 0x7c4000
    void Shutdown();       // 0x7c3ba0
    void Init(int arg);    // 0x7c4dd0
};
struct IHandler { virtual void h0(); };
struct cMessageServer
{
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual void UnregisterHandler(IHandler* handler, unsigned msgID, int priority);  // slot 11
};
struct cModelManager
{
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5();
    virtual void UnregisterModelType(unsigned id);  // slot 6
};
struct cSporeManager1  // FUN_0067dd40's return value
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void Flush();  // slot 13 (0x34)
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
    virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); virtual void v55(); virtual void v56();
    virtual void GetHandle(int* out2);  // slot 57 (0xe4)
};
struct cMessageHandle { int a, b; };
struct cSporeManager2  // FUN_0067dd50's return value: slot 30 (0x78) takes the handle
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void Dispatch(void* handle);  // slot 30
};
cModelManager* GetModelManager();     // 0x67dd80
cMessageServer* GetMessageServer();   // 0x67dcc0
cSporeManager1* GetManager1();        // 0x67dd40
cSporeManager2* GetManager2();        // 0x67dd50
template <class T> struct RefPtrL  // an AutoRefCount-style local
{
    T* p;
    RefPtrL(T* q) : p(q) { if (p) p->AddRef(); }
    ~RefPtrL() { if (p) p->Release(); }
    T* operator->() const { return p; }
    operator T*() const { return p; }
};
struct cRCVirt { virtual void v0(); virtual void Release(); virtual void Release2(); };  // slots 1, 2
struct cFilterChainJob_s007b_de20;
struct cFilterChainJob_s007b_de20 : cRCVirt
{
    uint32_t pad[(0x60 - 4) / 4];           // up to +0x60
    cFilterChainJob_s007b_de20* mChain;                // +0x60 (non-null -> Shutdown)
    uint32_t pad2[(0x78 - 0x64) / 4];       // to +0x78
    bool mInitialized;                      // +0x78
    uint8_t pad3[3];
    uint32_t pad4[(0x90 - 0x7c) / 4];       // to +0x90
    cRCVirt* mEffect;                       // +0x90 (release via slot 2)
    void Shutdown();              // 0x7b96d0
};
struct cAmbOccJob : cRCVirt
{
    uint32_t pad0[2];                       // +4 .. +0xc
    int m0c, m10;
    uint32_t pad[(0xa8 - 0x14) / 4];        // up to +0xa8
    cRCVirt* mHandle;                       // +0xa8
    uint32_t pad2[(0xc4 - 0xac) / 4];
    bool mActive;                           // +0xc4
};
struct cTimelineJob : cRCVirt
{
    uint32_t pad[(0x34 - 4) / 4];           // up to +0x34
    cViewer_s007b_de20* mViewer;                       // +0x34
    uint32_t pad2[(0x40 - 0x38) / 4];
    bool mActive;                           // +0x40
};
struct cTextureInstance_s007b_de20 { uint32_t pad[2]; volatile long mnRefCount; };  // refcount at +8
static inline void ReleaseTexture(cTextureInstance_s007b_de20*& slot)
{
    if (slot != 0 && slot != 0)
    {
        volatile long* rc = &slot->mnRefCount;
        slot = 0;
        _InterlockedExchangeAdd(rc, -1);
        long n = _InterlockedExchangeAdd(rc, 0);
        if (n < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}
struct cIThumbnailManager { virtual void tm0(); };
struct cRTTManager
{
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4();
    virtual void ReleaseRect(cRenderTargetRectID id);  // slot 5
};
struct cThumbEffect;
struct cThumbTarget;
struct cCaptureCtx;
struct cPaletteRequest;
struct cPaletteImageRequest;
class cThumbnailManager_s007b_de20 : public cIThumbnailManager, public IHandler
{
public:
    int mnRefCount;                              // +0x08
    uint32_t pad0c[(0x64 - 0xc) / 4];            // +0x0c .. +0x64
    cTextureInstance_s007b_de20* mTimelineCellBg;           // +0x64
    cTextureInstance_s007b_de20* mTimelineCreatureBg;       // +0x68
    cTextureInstance_s007b_de20* mTimelineTribeBg;          // +0x6c
    cTextureInstance_s007b_de20* mTimelineCivBg;            // +0x70
    cTextureInstance_s007b_de20* mTimelineSpaceBg;          // +0x74
    cViewer_s007b_de20* mSplatterViewer;                    // +0x78
    cViewer_s007b_de20* mBakeInfoSplatterViewer;            // +0x7c
    cViewer_s007b_de20* mNMapSpecSplatterViewer;            // +0x80
    cViewer_s007b_de20* mDilateViewer;                      // +0x84
    cViewer_s007b_de20* mAmbOccShadowViewers[1024];         // +0x88
    cViewer_s007b_de20* mAmbOccSplatterViewer;              // +0x1088
    cViewer_s007b_de20* mAmbOccGatherViewer;                // +0x108c
    void* mLargeBufferTexture;                   // +0x1090
    cRenderTargetRectID mLargeBufferTextureRectID;  // +0x1094
    uint32_t pad109c[(0x10b4 - 0x109c) / 4];
    cRTTManager* mRTTMgr;                        // +0x10b4
    uint32_t pad10b8[(0x10e4 - 0x10b8) / 4];
    cFilterChainJob_s007b_de20* mPostFilter0;               // +0x10e4
    cFilterChainJob_s007b_de20* mPostFilter1;               // +0x10e8
    cFilterChainJob_s007b_de20* mPostFilter2;               // +0x10ec
    uint32_t pad10f0[(0x10fc - 0x10f0) / 4];
    cFilterChainJob_s007b_de20* mAOPostProcessLayer;        // +0x10fc
    cAmbOccJob* mAmbOccRenderJob[1024];          // +0x1100
    cTimelineJob* mTimelineJobs[3];              // +0x2100

    bool Shutdown();                                                       // 0x7bde20
    void SetupThumbnailRTTs(unsigned a, int b);                            // 0x7b26a0
    void InitPostProcessEffect(unsigned a, cThumbEffect* e, int one, bool noAA, Vec3_s007b_de20 v);  // 0x7ba350
    void CapturePaletteThumbnail(cCaptureCtx* ctx, cPaletteRequest* req);  // 0x7be430
    void CapturePaletteImageThumbnail(cCaptureCtx* ctx, cPaletteImageRequest* req);  // 0x7bea00
    void FUN_007b9e80();                                                   // 0x7b9e80
};
static inline void ReleaseJob(cFilterChainJob_s007b_de20*& slot)
{
    cFilterChainJob_s007b_de20* j = slot;
    if (j)
    {
        slot = 0;
        j->Release();
    }
}
static inline void ShutdownFilter(cFilterChainJob_s007b_de20*& slot)
{
    cFilterChainJob_s007b_de20* f = slot;
    if (f)
    {
        if (f->mInitialized)
        {
            if (f->mChain)
                f->mChain->Shutdown();
            cRCVirt* e = f->mEffect;
            if (e)
            {
                f->mEffect = 0;
                e->Release2();
            }
            f->mInitialized = false;
        }
        ReleaseJob(slot);
    }
}
bool cThumbnailManager_s007b_de20::Shutdown()
{
    GetModelManager()->UnregisterModelType(0x247d6adu);
    cMessageServer* ms = GetMessageServer();
    if (ms)
    {
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x1c913db, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x1c91270, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x212c1ee, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x21d7528, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x31e09b4, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x21d752f, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x50b834d, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x5221305, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x5fadac4, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x5fc2c38, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x7b240a0, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x238de9c, -10000);
    }
    GetManager1()->Flush();

    if (mSplatterViewer)
    {
        mSplatterViewer->Shutdown();
        delete mSplatterViewer;
        mSplatterViewer = 0;
    }
    if (mBakeInfoSplatterViewer)
    {
        mBakeInfoSplatterViewer->Shutdown();
        delete mBakeInfoSplatterViewer;
        mBakeInfoSplatterViewer = 0;
    }
    if (mNMapSpecSplatterViewer)
    {
        mNMapSpecSplatterViewer->Shutdown();
        delete mNMapSpecSplatterViewer;
        mNMapSpecSplatterViewer = 0;
    }
    if (mDilateViewer)
    {
        mDilateViewer->Shutdown();
        delete mDilateViewer;
        mDilateViewer = 0;
    }
    if (mAmbOccSplatterViewer)
    {
        mAmbOccSplatterViewer->Shutdown();
        delete mAmbOccSplatterViewer;
        mAmbOccSplatterViewer = 0;
    }
    if (mAmbOccGatherViewer)
    {
        mAmbOccGatherViewer->Shutdown();
        delete mAmbOccGatherViewer;
        mAmbOccGatherViewer = 0;
    }
    if (mLargeBufferTexture)
    {
        mRTTMgr->ReleaseRect(mLargeBufferTextureRectID);
        mLargeBufferTexture = 0;
    }

    for (int i = 0; i < 1024; i++)
    {
        if (mAmbOccShadowViewers[i])
        {
            mAmbOccShadowViewers[i]->Shutdown();
            delete mAmbOccShadowViewers[i];
            mAmbOccShadowViewers[i] = 0;
        }
        cAmbOccJob* job = mAmbOccRenderJob[i];
        if (job)
        {
            if (job->mActive)
            {
                cRCVirt* h = job->mHandle;
                if (h)
                {
                    job->mHandle = 0;
                    h->Release();
                }
                job->m0c = 0;
                job->m10 = 0;
                job->mActive = false;
            }
            cAmbOccJob* j2 = mAmbOccRenderJob[i];
            if (j2)
            {
                mAmbOccRenderJob[i] = 0;
                j2->Release();
            }
        }
    }

    if (mAOPostProcessLayer)
    {
        mAOPostProcessLayer->Shutdown();
        ReleaseJob(mAOPostProcessLayer);
    }

    ShutdownFilter(mPostFilter0);
    ShutdownFilter(mPostFilter1);
    ShutdownFilter(mPostFilter2);

    ReleaseTexture(mTimelineCellBg);
    ReleaseTexture(mTimelineCreatureBg);
    ReleaseTexture(mTimelineTribeBg);
    ReleaseTexture(mTimelineCivBg);
    ReleaseTexture(mTimelineSpaceBg);

    for (int i = 0; i < 3; i++)
    {
        cTimelineJob* tj = mTimelineJobs[i];
        if (tj)
        {
            if (tj->mActive)
            {
                if (tj->mViewer)
                {
                    tj->mViewer->Shutdown();
                    delete tj->mViewer;
                    tj->mViewer = 0;
                }
                tj->mActive = false;
            }
            cTimelineJob* t2 = mTimelineJobs[i];
            if (t2)
            {
                mTimelineJobs[i] = 0;
                t2->Release();
            }
        }
    }

    FUN_007b9e80();
    return true;
}
struct cThumbRef { virtual int AddRef(); virtual int Release(); };
struct cThumbBase2 { virtual void sb0(); int m08; cThumbBase2() : m08(0) {} };  // second base (vptr +4, field +8)
struct cThumbEffect : cThumbRef, cThumbBase2
{
    virtual void e2(); virtual void e3(); virtual void e4();
    virtual void CaptureBox(Vec3_s007b_de20* box, cViewer_s007b_de20* world, int p, float z, int q, float w);  // slot 5 (0x14)
    virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10();
    virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15();
    virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19();
    virtual void CaptureRect(void* src, cViewer_s007b_de20* world, int p, void* q, float r, float z);   // slot 20 (0x50)
    int m0c, m10, m14;   // +0xc..+0x14
    int pad18, pad1c;
    bool mFlag;          // +0x20
    int m24, m28, m2c, m30;
    cThumbEffect();
};
cThumbEffect::cThumbEffect() : m0c(0), m10(0), m14(0), mFlag(false), m24(0), m28(0), m2c(0), m30(0) {}
struct cThumbJobMsgEvent
{
    int a;        // +0
    int b;        // +4
    bool c;       // +8
    int d;        // +0xc
    int e;        // +0x10
    unsigned id;  // +0x14
    void* data;   // +0x18
    int f, g, h, i;
};
struct cThumbJobA : cThumbRef, cThumbBase2
{
    virtual void j2(); virtual void j3();
    virtual void* Queue(int zero, cThumbJobMsgEvent* ev);  // slot 4
    bool m0c;
    int m10;
    int pad14;
    int m18, m1c;
    uint32_t pad20[3];
    int m2c, m30;
    cThumbJobA();
    void Run(void* arg1, cViewer_s007b_de20* world, cThumbTarget* tgt);  // 0x7b2ab0
};
cThumbJobA::cThumbJobA() : m0c(false), m10(0), m18(-1), m1c(-1), m2c(0), m30(0) {}
struct cThumbJobB : cThumbRef, cThumbBase2
{
    virtual void j2(); virtual void j3();
    virtual void* Queue(int zero, cThumbJobMsgEvent* ev);  // slot 4
    bool m0c;
    int m10;
    int pad14;
    int m18, m1c;
    uint32_t pad20[3];
    int m2c, m30;
    cThumbJobB();
    void Run(void* arg1, cViewer_s007b_de20* world, cThumbTarget* tgt);  // 0x7b2ca0
};
cThumbJobB::cThumbJobB() : m0c(false), m10(0), m18(-1), m1c(-1), m2c(0), m30(0) {}
struct cImageResource { int v; void Set(int resKey); };  // 0x576650 (thiscall, 1 arg), object at target+0x1c
struct cThumbTarget
{
    virtual void dummy();
    virtual int AddRef();
    virtual int Release();
    int pad04;                      // +4
    int mHandleA, mHandleB;         // +8, +0xc
    cThumbEffect* mEffect;          // +0x10 (AutoRefCount, slot-1 release)
    int m14, m18, m1c, m20, m24;
    bool m28;
    int m2c;
    cThumbTarget();
};
cThumbTarget::cThumbTarget() : pad04(0), mHandleA(-1), mHandleB(-1), mEffect(0) {}
struct cThumbTargetB  // 0x34 bytes: image-resource variant
{
    virtual void dummy();
    virtual int AddRef();
    virtual int Release();
    int pad04;
    int mHandleA, mHandleB;
    cThumbEffect* mEffect;          // +0x10
    int m14, m18;
    cImageResource mImage;          // +0x1c (resource at ctor)
    float m20, m24;                 // +0x20, +0x24
    int m28, m2c, m30;
    cThumbTargetB();
};
cThumbTargetB::cThumbTargetB() : pad04(0), mHandleA(-1), mHandleB(-1), mEffect(0) {}
struct cThumbDoneMsg
{
    virtual void dummy();
    virtual int AddRef();
    virtual int Release();
    volatile long mRef;       // +4
    int m08, m0c, m10, m14;
    void* mJob;               // +0x18
    int m1c, m20, m24;
    cThumbDoneMsg();
};
cThumbDoneMsg::cThumbDoneMsg() : m20(0) { _InterlockedExchange(&mRef, 0); }
struct BBox3 { Vec3_s007b_de20 mn, mx; };
struct cPaletteRequest
{
    uint32_t pad00[2];
    unsigned m08;          // +8
    int m0c;               // +0xc
    unsigned m10;          // +0x10
    int m14;               // +0x14
    unsigned m18;          // +0x18
    unsigned m1c;          // +0x1c
    unsigned m20;
    float m24;             // +0x24 (second variant)
    float m28;             // +0x28
    BBox3* mBoxBegin;      // +0x2c
    BBox3* mBoxEnd;        // +0x30
    uint32_t pad34[2];
    unsigned m3c;          // +0x3c
    unsigned m40;          // +0x40
    int mMode;             // +0x44
    float m48;             // +0x48
    float m4c;             // +0x4c
    float m50;             // +0x50
};
struct cPropertyList_s007b_de20 { bool GetDescription(unsigned id); };  // 0x6a25a0
extern cPropertyList_s007b_de20* g_sAppProperties_s007b_de20;                       // [0x15fd918]
struct cPaletteImageRequest
{
    uint32_t pad00[2];
    unsigned m08;          // +8
    int m0c;               // +0xc
    unsigned m10;          // +0x10
    int m14;               // +0x14
    unsigned m18, m1c, m20;  // +0x18..+0x20
    float m24;             // +0x24
    uint32_t m28[4];       // +0x28 (address passed on)
    unsigned m38;
    unsigned m3c;          // +0x3c
    float m40, m44, m48;   // +0x40..+0x48
    float m4c, m50;        // +0x4c, +0x50
};
// ---- items of slice s007bde20 end

// ---- items of slice s007bedb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct DoneMsg {
    char pad0[8];
    int m8;                                                    // +0x08
    char pad1[4];
    int m10;                                                   // +0x10
    char pad2[4];
    void* mJob;                                                // +0x18
};
struct RectID_s007b_edb0 { int mPageID; int mAllocID; bool IsValid() const { return mAllocID != -1; } };
struct cPaletteThumbnailJob_s007b_edb0 { void Shutdown(); };
struct cEditorThumbnailJob_s007b_edb0  { void Shutdown(); };
struct cCSAThumbnailJob_s007b_edb0     { void Shutdown(); };
struct cGameThumbnailJob_s007b_edb0    { void Shutdown(); };
struct MessageServer_s007b_edb0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void Call14(int a, int b, int c);                 // +0x14
};
MessageServer_s007b_edb0* __cdecl SP_MessageServer_s007b_edb0();          // 0x0067dcc0
struct RTTFree {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void Free(int page, int alloc);                   // +0x14
};
void* __cdecl FUN_0067dda0_s007b_edb0();
struct DoneMsg_s007b_edb0 {
    char pad0[8];
    int m8;                                                    // +0x08
    char pad1[4];
    int m10;                                                   // +0x10
    char pad2[4];
    void* mJob;                                                // +0x18
};
struct cThumbnailManager_s007b_edb0 {
    char pad0[0x14];
    RectID_s007b_edb0 mThumbRectID;                                       // +0x14
    RectID_s007b_edb0 mBlurThumbRectID1;                                  // +0x1c
    RectID_s007b_edb0 mBlurThumbRectID2;                                  // +0x24
    RectID_s007b_edb0 mTempThumbnailBuffer;                               // +0x2c
    RectID_s007b_edb0 mCSALargeRectID;                                    // +0x34
    RectID_s007b_edb0 mCSASmallRectID;                                    // +0x3c
    RectID_s007b_edb0 mCSAAntiAliasRectID;                                // +0x44
    void ThumbnailDone(DoneMsg_s007b_edb0* msg);  // 0x007bf610 (cThumbnailManager::ThumbnailDone)
};
struct RefLike {
    virtual int AddRef();                                      // +0x00
    virtual void Release();                                    // +0x04
};
struct RefVector {
    char pad[0x14];
    void operator=(void* v);                                   // 0x0041ebe0
};
struct SetterBlock {
    char pad0[0xc];
    void* m0c;                                                 // +0x0c
    void* m10;                                                 // +0x10
    char pad1[0x80];                                           // +0x14..0x93
    Pair  m94;                                                 // +0x94
    Pair  m9c;                                                 // +0x9c
    char pad2[4];                                              // +0xa4
    RefLike* m_a8;                                             // +0xa8
    RefVector m_ac;                                            // +0xac
    int   m_c0;                                                // +0xc0
    unsigned char m_c4;                                        // +0xc4
    float m_c8, m_cc, m_d0, m_d4;                              // +0xc8
    unsigned char m_d8;                                        // +0xd8

    void Set(void* a1, int a2, int a3, int a4, Pair* a5, Pair* a6, int a7, char a8);
};
// ---- items of slice s007bedb0 end

// ---- items of slice s007bfaa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace AO {
struct Vector3_s007b_faa0 {
    float x, y, z;
    Vector3_s007b_faa0() {}
    Vector3_s007b_faa0(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3_s007b_faa0(const Vector3_s007b_faa0& v) : x(v.x), y(v.y), z(v.z) {}
};
}
namespace AO {
inline float InvLength(float x, float y, float z) { float l2 = x * x + y * y + z * z + 1e-8f; return 1.0f / sqrtf(l2); }
}
namespace AO {
struct Vector4_s007b_faa0 { float x, y, z, w; };
}
namespace AO {
__declspec(align(16)) struct CameraMatrix { Vector4_s007b_faa0 mUp, mRight, mBack, mPosition; };   // w left unset
}
namespace AO {
Vector3_s007b_faa0 OrthogonalVector(const Vector3_s007b_faa0& v);                     // 0x006985B0 (cdecl)
}
namespace AO {
extern const Vector3_s007b_faa0 kAODirections[];                           // 0x0155BBD8
}
namespace AO {
struct cViewer_s007b_faa0 {
    void SetClearColor(const Vector4_s007b_faa0* color);                   // 0x007C3C20
    void SetRenderMode(int mode, int flags);                    // 0x007C3CE0
    void SetNearPlane(float n);                                 // 0x007C4BA0
    void SetFarPlane(float f);                                  // 0x007C4BC0
    void SetCameraTransform(const CameraMatrix* m);             // 0x007C4D20
    void SetViewWindow(float w, float h);                       // 0x007C5440
};
}
namespace AO {
struct IRenderTargetManager {
    virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03(); virtual void r04();
    virtual void r05(); virtual void r06(); virtual void r07(); virtual void r08();
    virtual void SetFlag(int on);                               // +0x24
    virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14();
    virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19();
    virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23(); virtual void r24();
    virtual void r25(); virtual void r26(); virtual void r27(); virtual void r28(); virtual void r29();
    virtual void r30(); virtual void r31(); virtual void r32(); virtual void r33(); virtual void r34();
    virtual void r35(); virtual void r36(); virtual void r37(); virtual void r38(); virtual void r39();
    virtual void r40(); virtual void r41(); virtual void r42(); virtual void r43();
    virtual void AllocRect(RectID* rect);                       // +0xB0
    virtual void r45(); virtual void r46(); virtual void r47(); virtual void r48(); virtual void r49();
    virtual void r50(); virtual void r51();
    virtual void SelectRect(RectID* rect);                      // +0xD0
    virtual void r53(); virtual void r54(); virtual void r55();
    virtual void FreeRect(RectID* rect, bool b);                // +0xE0
    virtual void r57(); virtual void r58(); virtual void r59();
    virtual void SetTarget(int a);                              // +0xF0
};
}
namespace AO {
IRenderTargetManager* RenderTargetManager();                    // 0x0067DD40
}
namespace AO {
struct ILayerManager {
    virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03(); virtual void l04();
    virtual void l05(); virtual void l06(); virtual void l07(); virtual void l08(); virtual void l09();
    virtual void l10(); virtual void l11(); virtual void l12(); virtual void l13(); virtual void l14();
    virtual void l15(); virtual void l16(); virtual void l17(); virtual void l18(); virtual void l19();
    virtual void l20(); virtual void l21(); virtual void l22(); virtual void l23(); virtual void l24();
    virtual void l25(); virtual void l26(); virtual void l27(); virtual void l28(); virtual void l29();
    virtual void AddLayer(void* layer);                         // +0x78
};
}
namespace AO {
ILayerManager* LayerManager();                                  // 0x0067DD50
}
namespace AO {
struct Property_s007b_faa0 {
    float* GetValueFloat();                                     // 0x0041EA70
    int*   GetValueInt();                                       // 0x0041E990
};
}
namespace AO {
struct PropertyList {
    virtual void p00();
    virtual int Release();                                      // +0x04
    virtual void p02(); virtual void p03(); virtual void p04(); virtual void p05(); virtual void p06();
    virtual bool HasProperty(uint32_t id);                      // +0x1C
    virtual void p08(); virtual void p09();
    virtual Property_s007b_faa0* GetProperty(uint32_t id);                 // +0x28
};
}
namespace AO {
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyListPtr& operator=(PropertyList* p)
    {
        if (p != mpObject) {
            PropertyList* const old = mpObject;
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    PropertyList* operator->() const { return mpObject; }
};
}
namespace AO {
struct IPropManager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03(); virtual void m04();
    virtual void m05(); virtual void m06(); virtual void m07(); virtual void m08(); virtual void m09();
    virtual void m10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst);   // +0x2C
};
}
namespace AO {
IPropManager* PropertyManager_s007b_faa0();                                // 0x0067DE30
}
namespace AO {
void* AllocGraphics(size_t size, const char* name, int a, int b, int c, int d);   // 0x00F473A0 operator new
}
inline void* operator new(size_t size, const char* name, int a, int b, int c, int d)
{
    return AO::AllocGraphics(size, name, a, b, c, d);
}
namespace AO {
struct IModel;
}
namespace AO {
struct IModelWorld_s007b_faa0 {
    virtual void w00(); virtual void w01(); virtual void w02();
    virtual IModel* CreateModel(uint32_t instanceID, uint32_t groupID, int flags);   // +0x0C
};
}
namespace AO {
struct ModelPtr {
    IModel* mpObject;
    ModelPtr& operator=(IModel* p);                             // 0x00478DB0
};
}
namespace AO {
class cJobPostFilter_s007b_faa0 {
public:
    virtual int AddRef();                                       // +0x00
    virtual int Release();                                      // +0x04
    cJobPostFilter_s007b_faa0();                                           // 0x007B8550
    void Init(int materialID, RectID* src, RectID* dst, int raster);   // 0x007B9510
    char pad04[0x3c - 0x04];
    float mCustomParams[8];                                     // +0x3C
    char pad5c[0xe4 - 0x5c];
};
}
namespace AO {
struct FilterPtr_s007b_faa0 {
    cJobPostFilter_s007b_faa0* mpObject;
    FilterPtr_s007b_faa0(cJobPostFilter_s007b_faa0* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~FilterPtr_s007b_faa0() { if (mpObject) mpObject->Release(); }
    cJobPostFilter_s007b_faa0* operator->() const { return mpObject; }
};
}
namespace AO {
struct cFilterChainJob_s007b_faa0 {
    char pad0[0x20];
    bool mbActive;                                              // +0x20
    char pad21[7];
    int mFilterIndex;                                           // +0x28
    void AddFilter(cJobPostFilter_s007b_faa0* filter);                     // 0x007B9750
    void Start() { if (!mbActive) { mbActive = true; mFilterIndex = 0; } }
};
}
namespace AO {
struct cMessageBase {
    virtual ~cMessageBase();
    virtual int AddRef();                                       // +0x04
    virtual int Release();                                      // +0x08
    volatile long mnRefCount;                                   // +0x04
    cMessageBase() { _InterlockedExchange(&mnRefCount, 0); }
};
}
namespace AO {
struct cAOPassMessage : cMessageBase {
    int mPassIndex;  int pad0c;                                 // +0x08
    int mUserData;   int pad14;                                 // +0x10
    int mPassCount;  int pad1c;                                 // +0x18
    int mGatherAllocID; int pad24;                              // +0x20
    int mGatherPageID;  int pad2c;                              // +0x28
    int mPropListID; int pad34;                                 // +0x30
    int mField38;                                               // +0x38
    int pad3c;
    cAOPassMessage() : mField38(0) {}
    ~cAOPassMessage();
};
}
namespace AO {
struct MessagePtr {
    cMessageBase* mpObject;
    MessagePtr() : mpObject(0) {}
    ~MessagePtr() { if (mpObject) mpObject->Release(); }
    MessagePtr& operator=(cMessageBase* p) { if (p) p->AddRef(); mpObject = p; return *this; }
};
}
namespace AO {
struct LayerInfo {
    int mFlags;                                                 // +0x00
    int mField04;                                               // +0x04
    bool mbField08;                                             // +0x08
    int mField0C;                                               // +0x0C
    int mField10;                                               // +0x10
    uint32_t mDoneMessageID;                                    // +0x14
    MessagePtr mpDoneMessage;                                   // +0x18
    int mField1C, mField20, mField24, mField28;                 // +0x1C
};
}
namespace AO {
struct MeshVector {                                             // eastl::vector<AutoRefCount<cMeshData>>
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    int mAllocator;
    MeshVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~MeshVector() { DestroyRange(mpBegin, mpEnd); if (mpBegin) Free(mpBegin); }
    void DestroyRange(void** first, void** last);               // 0x004243E0
    static void Free(void* p);
};
}
namespace AO {
struct cAmbOccJob_s007b_faa0 {
    virtual void j00(); virtual void j01(); virtual void j02(); virtual void j03();
    virtual void* GetLayer(int a, LayerInfo* info);             // +0x10
    void Init(IModelWorld_s007b_faa0* world, const MeshVector& meshes, cViewer_s007b_faa0* shadowViewer, cViewer_s007b_faa0* splatterViewer,
              RectID* shadowRect, RectID* gatherRect, int passIndex, bool flag);   // 0x007BF9C0
};
}
namespace AO {
struct cThumbnailManagerAO {
    char pad0[0x88];
    cViewer_s007b_faa0* mAmbOccShadowViewers[1024];                        // +0x88
    cViewer_s007b_faa0* mAmbOccSplatterViewer;                             // +0x1088
    cViewer_s007b_faa0* mAmbOccGatherViewer;                               // +0x108C
    char pad1090[0x10bc - 0x1090];
    bool mMultiplyDiffuseWithAO;                                // +0x10BC
    char pad10bd[0x10c4 - 0x10bd];
    IModelWorld_s007b_faa0* mAOModelWorld;                                 // +0x10C4
    ModelPtr mSkinModel;                                        // +0x10C8
    int mSplatInProgress;                                       // +0x10CC
    bool mCurrentlyCapturingAO;                                 // +0x10D0
    char pad10d1[0x10f4 - 0x10d1];
    RectID mAOGatherRectID;                                     // +0x10F4
    cFilterChainJob_s007b_faa0* mAOPostProcessLayer;                       // +0x10FC
    cAmbOccJob_s007b_faa0* mAmbOccRenderJob[1024];                         // +0x1100

    void FUN_007b5c80(MeshVector* meshes, Vector3_s007b_faa0* outCenter, float* outRadius);        // 0x007B5C80, ret 0xc (this unused)
    void FUN_007b87f0(IModelWorld_s007b_faa0* world, Vector3_s007b_faa0* outCenter, float* outRadius);        // 0x007B87F0, ret 0xc (this unused)
    bool CaptureAmbientOcclusionB(RectID* shadowRect, IModelWorld_s007b_faa0* world, MeshVector* meshes, int userData,
                                  uint32_t propListID, bool useMeshes);                 // 0x007BFEE0
};
}
// ---- items of slice s007bfaa0 end

// ---- items of slice s007c0780 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct DoneMsg;
struct cThumbnailManagerBase { virtual void v0(); };
struct IHandlerRC {
    virtual bool HandleMessage(unsigned int msgId, void* arg);
};
struct cThumbnailManager_s007c_0780 : cThumbnailManagerBase, IHandlerRC {
    void ThumbnailDone(DoneMsg* msg);  // 0x007bf610 (cThumbnailManager::ThumbnailDone)
    void FUN_007bf720(void* arg);
    void FUN_007bbde0(void* arg);
    void DilateStart(void* arg);  // 0x007bbf80 (cThumbnailManager::DilateStart)
    void DilateWithoutAODone(void* arg);  // 0x007bd4c0 (cThumbnailManager::DilateWithoutAODone)
    void FUN_007bced0(void* arg);
    void PaletteJobInfo_Shutdown(void* arg);
    void FUN_007b29a0();
    void FUN_007b2970(void* arg);
    void FUN_007b77a0(void* arg);
};
namespace AO {
struct Vector3_s007c_0780 {
    float x, y, z;
    Vector3_s007c_0780() {}
    Vector3_s007c_0780(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3_s007c_0780(const Vector3_s007c_0780& v) : x(v.x), y(v.y), z(v.z) {}
};
}
namespace AO {
struct BoundingBox { Vector3_s007c_0780 mMin; Vector3_s007c_0780 mMax; };
}
namespace AO {
inline float Length(float x, float y, float z) { return sqrtf(x * x + y * y + z * z); }
}
namespace AO {
inline float InvLength_s007c_0780(float x, float y, float z) { return 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f); }
}
namespace AO {
struct Vector4_s007c_0780 { float x, y, z, w; };
}
namespace AO {
__declspec(align(16)) struct CameraMatrix_s007c_0780 { Vector4_s007c_0780 mUp, mRight, mBack, mPosition; };   // w left unset
}
namespace AO {
Vector3_s007c_0780 OrthogonalVector(const Vector3_s007c_0780& v);                     // 0x006985B0 (cdecl)
}
namespace AO {
extern const Vector3_s007c_0780 kAODirections_s007c_0780[];                           // 0x0155BBD8
}
namespace AO {
struct cViewer_s007c_0780 {
    void SetClearColor(const Vector4_s007c_0780* color);                   // 0x007C3C20
    void SetRenderMode(int mode, int flags);                    // 0x007C3CE0
    void SetNearPlane(float n);                                 // 0x007C4BA0
    void SetFarPlane(float f);                                  // 0x007C4BC0
    void SetCameraTransform(const CameraMatrix_s007c_0780* m);             // 0x007C4D20
    void SetViewWindow(float w, float h);                       // 0x007C5440
};
}
namespace AO {
struct Property_s007c_0780 {
    float* GetValueFloat();                                     // 0x0041EA70
    int*   GetValueInt();                                       // 0x0041E990
};
}
namespace AO {
struct PropertyList_s007c_0780 {
    virtual void p00();
    virtual int Release();                                      // +0x04
    virtual void p02(); virtual void p03(); virtual void p04(); virtual void p05(); virtual void p06();
    virtual bool HasProperty(uint32_t id);                      // +0x1C
    virtual void p08(); virtual void p09();
    virtual Property_s007c_0780* GetProperty(uint32_t id);                 // +0x28
};
}
namespace AO {
struct PropertyListPtr_s007c_0780 {
    PropertyList_s007c_0780* mpObject;
    PropertyListPtr_s007c_0780() : mpObject(0) {}
    ~PropertyListPtr_s007c_0780() { if (mpObject) mpObject->Release(); }
    PropertyListPtr_s007c_0780& operator=(PropertyList_s007c_0780* p)
    {
        if (p != mpObject) {
            PropertyList_s007c_0780* const old = mpObject;
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    PropertyList_s007c_0780* operator->() const { return mpObject; }
};
}
namespace AO {
struct IPropManager_s007c_0780 {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03(); virtual void m04();
    virtual void m05(); virtual void m06(); virtual void m07(); virtual void m08(); virtual void m09();
    virtual void m10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr_s007c_0780& dst);   // +0x2C
};
}
namespace AO {
IPropManager_s007c_0780* PropertyManager_s007c_0780();                                // 0x0067DE30
}
namespace AO {
inline void GetPropFloat(PropertyList_s007c_0780* pl, uint32_t id, float& dst)
{
    if (pl->HasProperty(id)) dst = *pl->GetProperty(id)->GetValueFloat();
}
}
namespace AO {
inline void GetPropInt(PropertyList_s007c_0780* pl, uint32_t id, int& dst)
{
    if (pl->HasProperty(id)) dst = *pl->GetProperty(id)->GetValueInt();
}
}
namespace AO {
struct IModelWorld_s007c_0780 {
    virtual void w00(); virtual void w01(); virtual void w02();
    virtual IModel* CreateModel(uint32_t instanceID, uint32_t groupID, int flags);   // +0x0C
};
}
namespace AO {
class cJobPostFilter_s007c_0780 {
public:
    virtual int AddRef();                                       // +0x00
    virtual int Release();                                      // +0x04
    cJobPostFilter_s007c_0780();                                           // 0x007B8550
    void Init(int materialID, RectID* src, RectID* dst, int raster);   // 0x007B9510
    char pad04[0x3c - 0x04];
    float mCustomParams[8];                                     // +0x3C
    char pad5c[0xe4 - 0x5c];
};
}
namespace AO {
struct FilterPtr_s007c_0780 {
    cJobPostFilter_s007c_0780* mpObject;
    FilterPtr_s007c_0780(cJobPostFilter_s007c_0780* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~FilterPtr_s007c_0780() { if (mpObject) mpObject->Release(); }
    cJobPostFilter_s007c_0780* operator->() const { return mpObject; }
};
}
namespace AO {
struct cFilterChainJob_s007c_0780 {
    char pad0[0x20];
    bool mbActive;                                              // +0x20
    int mFilterIndex;                                           // +0x28 (after padding)
    void AddFilter(cJobPostFilter_s007c_0780* filter);                     // 0x007B9750
    void Start() { if (!mbActive) { mbActive = true; mFilterIndex = 0; } }
};
}
namespace AO {
struct cAmbOccJob_s007c_0780 {
    virtual void j00(); virtual void j01(); virtual void j02(); virtual void j03();
    virtual void* GetLayer(int a, LayerInfo* info);             // +0x10
    void Init(IModelWorld_s007c_0780* world, const MeshVector& meshes, cViewer_s007c_0780* shadowViewer, cViewer_s007c_0780* splatterViewer,
              RectID* shadowRect, RectID* gatherRect, int passIndex, int flags);   // 0x007BF9C0
};
}
namespace AO {
struct cThumbnailManagerAO_s007c_0780 {
    char pad0[0x88];
    cViewer_s007c_0780* mAmbOccShadowViewers[1024];                        // +0x88
    cViewer_s007c_0780* mAmbOccSplatterViewer;                             // +0x1088
    cViewer_s007c_0780* mAmbOccGatherViewer;                               // +0x108C
    char pad1090[0x10bc - 0x1090];
    bool mMultiplyDiffuseWithAO;                                // +0x10BC
    char pad10bd[0x10c4 - 0x10bd];
    IModelWorld_s007c_0780* mAOModelWorld;                                 // +0x10C4
    ModelPtr mSkinModel;                                        // +0x10C8
    int mSplatInProgress;                                       // +0x10CC
    bool mCurrentlyCapturingAO;                                 // +0x10D0
    char pad10d1[0x10f4 - 0x10d1];
    RectID mAOGatherRectID;                                     // +0x10F4
    cFilterChainJob_s007c_0780* mAOPostProcessLayer;                       // +0x10FC
    cAmbOccJob_s007c_0780* mAmbOccRenderJob[1024];                         // +0x1100

    bool CaptureAmbientOcclusion(uint32_t instanceID, uint32_t groupID, const BoundingBox& bbox,
                                 int userData, uint32_t propListID, int target);
};
}
// ---- items of slice s007c0780 end

// ---- items of slice s007c1c10 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SPL {
struct RectID_s007c_1c10 { int mPageID; int mAllocID; };
}
namespace SPL {
struct Mat3 { float m[9]; void Assign(const void* src); };      // 0x0041CB40 (thiscall, ret 4)
}
namespace SPL {
extern const float kMat3Src[9];                                  // 0x01635788
}
namespace SPL {
extern const float kTransPos[3];                                 // 0x01635648
}
namespace SPL {
extern const float kOne;                                         // 0x01485720
}
namespace SPL {
struct Xform {
    unsigned short mFlags;
    unsigned short mCount;
    float mPos[3];
    float mScale;
    Mat3 mBasis;
    Xform()
    {
        mFlags = 0;
        mCount = 0;
        mPos[0] = kTransPos[0];
        mPos[1] = kTransPos[1];
        mPos[2] = kTransPos[2];
        mScale = kOne;
        mBasis.Assign(kMat3Src);
    }
};
}
namespace SPL {
struct cViewer_s007c_1c10 {
    void SetBasis(Xform* x);                                    // 0x007C4D00
    void SetRenderMode(int mode, int flags);                    // 0x007C3CE0
};
}
namespace SPL {
struct XformSource { void GetXform(Xform* out); };              // 0x007C40F0 (thiscall, ret 4)
}
namespace SPL {
struct IScene {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual XformSource* GetTransform();                        // +0x1C
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual void SetMode(int mode);                             // +0x2C
};
}
namespace SPL {
struct IApp {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual IScene* GetScene();                                 // +0x50
};
}
namespace SPL {
IApp* App();                                                    // 0x0067DD10
}
namespace SPL {
struct IRenderTargetManager_s007c_1c10 {
    virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03(); virtual void r04();
    virtual void r05(); virtual void r06(); virtual void r07(); virtual void r08();
    virtual void SetFlag(int on);                               // +0x24
    virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14();
    virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19();
    virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23(); virtual void r24();
    virtual void r25(); virtual void r26(); virtual void r27(); virtual void r28(); virtual void r29();
    virtual void r30(); virtual void r31(); virtual void r32(); virtual void r33(); virtual void r34();
    virtual void r35(); virtual void r36(); virtual void r37(); virtual void r38(); virtual void r39();
    virtual void r40(); virtual void r41(); virtual void r42(); virtual void r43(); virtual void r44();
    virtual void r45(); virtual void r46(); virtual void r47(); virtual void r48(); virtual void r49();
    virtual void r50(); virtual void r51(); virtual void r52(); virtual void r53(); virtual void r54();
    virtual void r55();
    virtual void FreeRect(RectID_s007c_1c10* rect, bool b);                // +0xE0
};
}
namespace SPL {
IRenderTargetManager_s007c_1c10* RenderTargetManager();                    // 0x0067DD40
}
namespace SPL {
struct LayerInfo_s007c_1c10 {
    int mFlags;                                                 // +0x00
    int mField04;                                               // +0x04
    bool mbField08;                                             // +0x08
    int mField0C;                                               // +0x0C
    int mField10;                                               // +0x10
    unsigned int mDoneMessageID;                                // +0x14
    void* mpDoneMessage;                                        // +0x18
    int mField1C, mField20, mField24, mField28;                 // +0x1C
    LayerInfo_s007c_1c10()
    {
        mFlags = 1;
        mField04 = 0;
        mbField08 = true;
        mField0C = 0;
        mField10 = 0;
        mDoneMessageID = 0;
        mpDoneMessage = 0;
        mField1C = 0;
        mField20 = 0;
        mField24 = 0;
        mField28 = 0;
    }
};
}
namespace SPL {
struct ILayerManager_s007c_1c10 {
    virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03(); virtual void l04();
    virtual void l05(); virtual void l06(); virtual void l07(); virtual void l08(); virtual void l09();
    virtual void l10(); virtual void l11(); virtual void l12(); virtual void l13(); virtual void l14();
    virtual void l15(); virtual void l16(); virtual void l17(); virtual void l18(); virtual void l19();
    virtual void l20(); virtual void l21(); virtual void l22(); virtual void l23(); virtual void l24();
    virtual void l25(); virtual void l26(); virtual void l27(); virtual void l28(); virtual void l29();
    virtual void AddLayer(void* layer);                         // +0x78
};
}
namespace SPL {
ILayerManager_s007c_1c10* LayerManager();                                  // 0x0067DD50
}
namespace SPL {
class cJobPostFilter_s007c_1c10 {
public:
    virtual int AddRef();                                       // +0x00
    virtual int Release();                                      // +0x04
    cJobPostFilter_s007c_1c10();                                           // 0x007B8550
    void Init(int materialID, const RectID_s007c_1c10* src, const RectID_s007c_1c10* dst, int raster);   // 0x007B9510
    char pad04[0xe4 - 0x04];
};
}
namespace SPL {
struct FilterPtr_s007c_1c10 {
    cJobPostFilter_s007c_1c10* mpObject;
    FilterPtr_s007c_1c10(cJobPostFilter_s007c_1c10* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~FilterPtr_s007c_1c10() { if (mpObject) mpObject->Release(); }
};
}
namespace SPL {
struct cILayer { virtual int AddRef(); virtual int Release(); virtual void l2(); };
}
namespace SPL {
struct RefCountVTemplateInt {
    virtual void rc0();
    int mnRefCount;                                             // +0x08
    RefCountVTemplateInt() : mnRefCount(0) {}
};
}
namespace SPL {
struct cFilterChainJob_s007c_1c10 : cILayer, RefCountVTemplateInt {
    void* mFilters[3];                                          // +0x0C
    int mAllocator;                                             // +0x18
    int pad1c;
    bool mbActive;                                              // +0x20
    int pad24;
    int mFilterIndex;                                           // +0x28
    int pad2c, pad30;
    cFilterChainJob_s007c_1c10()
    {
        mFilters[0] = 0;
        mFilters[1] = 0;
        mFilters[2] = 0;
        mbActive = false;
        pad24 = 0;
        mFilterIndex = 0;
        pad2c = 0;
        pad30 = 0;
    }
    void Start() { if (!mbActive) { mbActive = true; mFilterIndex = 0; } }
    void AddFilter(cJobPostFilter_s007c_1c10* filter);                     // 0x007B9750
};
}
namespace SPL {
struct ChainPtr {
    cFilterChainJob_s007c_1c10* mpObject;
    ChainPtr(cFilterChainJob_s007c_1c10* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~ChainPtr() { if (mpObject) mpObject->Release(); }
};
}
namespace SPL {
struct RefBaseA22 {
    virtual ~RefBaseA22();
    virtual int AddRef();                                       // +0x04
    virtual int Release();                                      // +0x08
    volatile long mnRefCount;                                   // +0x04
    RefBaseA22() { _InterlockedExchange(&mnRefCount, 0); }
};
}
namespace SPL {
struct DrvBA22 : RefBaseA22 {
    int mField08, pad0c;                                        // +0x08
    int mField10, pad14;                                        // +0x10
    int mField18, pad1c;                                        // +0x18
    int mField20, pad24;                                        // +0x20
    int mField28, pad2c;                                        // +0x28
    DrvBA22() : mField28(0) {}
    virtual ~DrvBA22();
};
}
namespace SPL {
struct DrvPtr {
    RefBaseA22* mpObject;
    DrvPtr& operator=(RefBaseA22* p)
    {
        if (p != mpObject) {
            RefBaseA22* const old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
}
namespace SPL {
struct cSplatJob {
    virtual void j00(); virtual void j01(); virtual void j02(); virtual void j03();
    virtual void* GetLayer(int a, LayerInfo_s007c_1c10* info);             // +0x10
    char pad04[0x90 - 0x04];
    DrvPtr mEffect;                                             // +0x90
    void Reset();                                               // 0x007B39D0
    void Init(int c1, int c2, int c3, int c4, int c5, const RectID_s007c_1c10* c6, cViewer_s007c_1c10* viewer, int c8,
              cFilterChainJob_s007c_1c10* chain);                          // 0x007C1B70 (ret 0x24)
};
}
namespace SPL {
struct cThumbnailManagerSplat {
    char pad0[0x78];
    cViewer_s007c_1c10* mSplatterViewer;                                   // +0x78
    cViewer_s007c_1c10* mBakeInfoSplatterViewer;                           // +0x7C
    cViewer_s007c_1c10* mNMapSpecSplatterViewer;                           // +0x80
    char pad84[0x10e4 - 0x84];
    cSplatJob* mJob0;                                           // +0x10E4
    cSplatJob* mJob1;                                           // +0x10E8
    cSplatJob* mJob2;                                           // +0x10EC

    void SetupSplat(int a1, const RectID_s007c_1c10* a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9,
                    const RectID_s007c_1c10* a10, const RectID_s007c_1c10* a11, int a12);
};
}
// ---- items of slice s007c1c10 end

// ---- items of slice s007ba350 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace graphics {
struct Raster_s007b_a350 {
    uint32_t pad0[3];
    unsigned short m_width;   // +0xc
    unsigned short m_height;  // +0xe
};
}
}
namespace EA {
template <typename T>
class AutoRefCount_s007b_a350 {
public:
    T* mpObject;
    AutoRefCount_s007b_a350(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s007b_a350() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
namespace SP {
struct cRenderTargetRectID_s007b_a350 {
    int mPageID;
    int mAllocID;
    cRenderTargetRectID_s007b_a350() : mPageID(-1), mAllocID(-1) {}
};
}
namespace SP {
struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float ax, float ay) : x(ax), y(ay) {}
};
}
namespace SP {
inline Vector2 operator*(const Vector2& v, float s) { return Vector2(v.x * s, v.y * s); }
}
namespace SP {
struct Vector4_s007b_a350 {
    float x, y, z, w;
    Vector4_s007b_a350() {}
    Vector4_s007b_a350(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};
}
namespace SP {
struct cSPColorRGBA {
    float r, g, b, a;
    cSPColorRGBA() {}
    cSPColorRGBA(float ar, float ag, float ab, float aa) : r(ar), g(ag), b(ab), a(aa) {}
    cSPColorRGBA(const cSPColorRGBA& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
};
}
namespace SP {
namespace eastl_ {
template <typename T>
struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    void DoInsertValue(T* position, const T& value);  // 0x006ec390
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
}
namespace SP {
class cILayer_s007b_a350 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
namespace SP {
class cTextureInstance_s007b_a350 {
public:
    rw::graphics::Raster_s007b_a350* GetRaster();  // 0x0046f260
};
}
namespace SP {
class cTextureManager_s007b_a350 {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual cTextureInstance_s007b_a350* GetTexture(uint32_t instance, uint32_t group, int flags);  // +0x20 0x007a93c0
};
}
namespace SP {
cTextureManager_s007b_a350* TextureManager();  // 0x0067dd60
}
namespace SP {
class cRenderer_s007b_a350 {
public:
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56)
    virtual void GetCurrentRenderTarget(cRenderTargetRectID_s007b_a350* pRect);  // +0xe4
};
}
namespace SP {
cRenderer_s007b_a350* Renderer();  // 0x0067dd40
}
namespace SP {
class cIRTTManager_s007b_a350 {
public:
    PV(0) PV(1) PV(2) PV(3)
    virtual cRenderTargetRectID_s007b_a350 AllocateRTT(int width, int height, int format, int a, int b, int c);  // +0x10
    PV(5) PV(6) PV(7) PV(8)
    virtual void GetRTTInfo(cRenderTargetRectID_s007b_a350 id, int* x, int* y, int* width, int* height);  // +0x24
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void SetRTTName(cRenderTargetRectID_s007b_a350 id, const char* name);  // +0x48
};
}
namespace SP {
class cThumbnailManager_s007b_a350 {
public:
    class cJobPostFilter;
    class cFilterChainJob;

    uint32_t pad0[4];
    rw::graphics::Raster_s007b_a350* mThumbRaster;           // +0x10
    cRenderTargetRectID_s007b_a350 mThumbRectID;             // +0x14
    cRenderTargetRectID_s007b_a350 mBlurThumbRectID1;        // +0x1c
    cRenderTargetRectID_s007b_a350 mBlurThumbRectID2;        // +0x24
    cRenderTargetRectID_s007b_a350 mTempThumbnailBuffer;     // +0x2c
    uint32_t pad1[(0x10b4 - 0x34) / 4];
    cIRTTManager_s007b_a350* mRTTMgr;                        // +0x10b4

    void InitPostProcessEffect(int type, cFilterChainJob* pChain, bool enable, bool alt,
                               Vector2 blurOffset, float blurStrength);
};
}
namespace SP {
class cThumbnailManager_s007b_a350::cJobPostFilter : public cILayer_s007b_a350 {
public:
    uint32_t mRefCountV[2];                       // +0x04 RefCountVTemplate
    unsigned int mMaterialId;                     // +0x0c
    cRenderTargetRectID_s007b_a350 mSrcRectID;               // +0x10
    rw::graphics::Raster_s007b_a350* mSrcRaster;             // +0x18
    cRenderTargetRectID_s007b_a350 mDestRectID;              // +0x1c
    eastl_::sp_vector<cRenderTargetRectID_s007b_a350> mAdditionalRectIDs;  // +0x24
    float mCustomParams[16];                      // +0x3c
    unsigned int mCallNumber;                     // +0x7c
    bool mInitialized;                            // +0x80
    bool mDumpTexture;                            // +0x81
    bool mClearBeforeDraw;                        // +0x82
    bool mOverrideViewport;                       // +0x83
    int mViewX, mViewY, mViewW, mViewH;           // +0x84
    int mQuadrant;                                // +0x94
    cSPColorRGBA mClearColor;                     // +0x98
    uint32_t mPreSetViewport;                     // +0xa8
    Vector2 mBlurA, mBlurB, mBlurC, mBlurD;       // +0xac
    float mBlurStrength;                          // +0xcc
    uint32_t pad2[(0xe4 - 0xd0) / 4];

    cJobPostFilter();                             // 0x007b8550
    virtual int AddRef();
    virtual int Release();
    void Initialize(int flags);                   // 0x007b9420
    void InitBlur(int taps, const cRenderTargetRectID_s007b_a350& src, const cRenderTargetRectID_s007b_a350& dest, int flags);  // 0x007b9510

    void SetCustomParams(int index, const Vector4_s007b_a350& v);  // 0x007b3a30

    void SetClearColor(cSPColorRGBA color)        // 0x007b27a0
    {
        mClearColor = color;
        mClearBeforeDraw = true;
    }
    void SetViewport(int x, int y, int w, int h, int quadrant)  // 0x007b27e0
    {
        mViewX = x;
        mViewY = y;
        mViewW = w;
        mViewH = h;
        mOverrideViewport = true;
        mQuadrant = quadrant;
    }
    void SetBlurParams(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, float strength)  // 0x007b2820
    {
        mBlurA = a;
        mBlurB = b;
        mBlurC = c;
        mBlurD = d;
        mBlurStrength = strength;
    }
    void AddAdditionalRect(const cRenderTargetRectID_s007b_a350& id)  // 0x007b9690
    {
        mAdditionalRectIDs.push_back(id);
    }
};
}
namespace SP {
void cThumbnailManager_s007b_a350::cJobPostFilter::SetCustomParams(int index, const Vector4_s007b_a350& v)
{
    mCustomParams[index * 4 + 0] = v.x;
    mCustomParams[index * 4 + 1] = v.y;
    mCustomParams[index * 4 + 2] = v.z;
    mCustomParams[index * 4 + 3] = v.w;
}
}
namespace SP {
class cThumbnailManager_s007b_a350::cFilterChainJob {
public:
    void AddFilter(cJobPostFilter* pFilter);      // 0x007b9750
};
}
namespace SP {
typedef EA::AutoRefCount_s007b_a350<cThumbnailManager_s007b_a350::cJobPostFilter> FilterPtr_s007b_a350;
}
// ---- items of slice s007ba350 end

// @ 0x00572590
UintArray* UintArray::Self()
{ return this; }

// @ 0x007b2600
void FUN_007b2600(void*)
{}

// @ 0x007b2680
void SP::cThumbnailManager::GetThumbRectID(SP::cRenderTargetRectID & out)
{
    out.mPageID = mThumbRectID.mPageID;
    out.mAllocID = mThumbRectID.mAllocID;
}

// @ 0x007b26a0
void FUN_007b26a0(void*)
{}

// @ 0x007b27a0
void W27a0::f(int a, int b, int c, int d)
{
    m98 = a; m9c = b; ma0 = c; m82 = 1; ma4 = d;
}

// @ 0x007b27e0
void W27e0::f(int a, int b, int c, int d, int e)
{
    m84 = a; m88 = b; m8c = c; m83 = 1; m90 = d; m94 = e;
}

// @ 0x007b2820
void W2820::set(Pair* pa, Pair* pb, Pair* pc, Pair* pd, float v)
{
    a.x = pa->x; a.y = pa->y;
    b.x = pb->x; b.y = pb->y;
    c.x = pc->x; c.y = pc->y;
    d.x = pd->x; d.y = pd->y;
    f = v;
}

// @ 0x007b2890
D2890::~D2890()
{ if (mObj) ((IObj2*)mObj)->Release(); }

// @ 0x007b2900
D2900::~D2900()
{ if (mObj) ((IObj2*)mObj)->Release(); }

// @ 0x007b2970
void __stdcall FUN_007b2970(P2970* p)
{
    Node2900* node = p->mNode;
    void* arg = p->mArg;
    IMsg* s = (IMsg*)FUN_0067dcc0();
    s->v5(arg, 0, 0);
    if (node->mFlag)
        node->mFlag = 0;
}

// @ 0x007b29a0
void FUN_007b29a0(void*)
{}

// @ 0x007b2ab0
void FUN_007b2ab0(void*)
{}

// @ 0x007b2ca0
void FUN_007b2ca0(void*)
{}

// @ 0x007b2e10
void FUN_007b2e10(void*)
{}

// @ 0x007b2eb0
void FUN_007b2eb0(void*)
{}

// @ 0x007b2f40
void FUN_007b2f40(void*)
{}

// @ 0x007b3090
void FUN_007b3090(void*)
{}

// @ 0x007b31f0
void FUN_007b31f0(void*)
{}

// @ 0x007b32e0
void FUN_007b32e0(void*)
{}

// @ 0x007b3340
void FUN_007b3340(void*)
{}

// @ 0x007b35a0
void FUN_007b35a0(void*)
{}

// @ 0x007b3630
void FUN_007b3630(void*)
{}

// @ 0x007b3760
void FUN_007b3760(void*)
{}

// @ 0x007b3820
void FUN_007b3820(void*)
{}

// @ 0x007b39d0
void W39d0::f()
{
    if (m78)
        return;
    m78 = 1;
    m74 = 0x10;
    PropList* p = g_sAppProperties;
    if (p) {
        PropHandle* h;
        if (p->v9(0x67c8be6, &h) && h->type == 9)
            m74 = *h->GetInt();
    }
    m70 = 0;
}

// @ 0x007b3a30
void W3a30::set(int idx, float* v)
{
    char* b = (char*)this;
    float* p = (float*)(b + 0x3c);
    int o = idx*4;
    p[o + 0] = v[0];
    *(float*)(b + (idx + 4) * 0x10) = v[1];
    p[o + 2] = v[2];
    p[o + 3] = v[3];
}

// @ 0x007b3a70
void cShowTexturesLayer::DrawLayer(int a1, int a2, int* a3, int a4)
{
    (void)a1; (void)a2;
    m_viewer->Copy(*a3, 1, 0);

    bool bSimple = (m_b83 == 0 && m_ba8 == 0);
    m_viewer->SetView(&m_destX, bSimple);

    ITextureProvider* p6 = (ITextureProvider*)FUN_0067dda0();

    if (m_b83)
        m_viewer->SetRects(m_w84, m_w88, m_w8c, m_w90);

    if (!m_viewer->Check())
        return;

    FUN_00761dc0();
    if (m_b82) {
        m_viewer->AddRect(m_rect98);
        m_viewer->SetMode(7);
    }

    IMaterialMgr* p7 = (IMaterialMgr*)MaterialManager();
    void* pMat = p7->GetMaterial((int)m_materialId);
    EmbeddedState* pES = *(EmbeddedState**)((char*)pMat + 4);

    Raster*  pRaster = 0;
    float    f144 = 0.0f, f140 = 0.0f, f13c = 0.0f, f138 = 0.0f;
    float    f14c = 0.0f, f148 = 0.0f, f154 = 0.0f;
    float    fVar9, fVar11, fVar12, fVar13;

    // ---- select the source raster and the base quad -------------------------
    {
        bool bCommon = false;
        if (m_srcRaster == 0) {
            pRaster = p6->GetRaster(m_texId0, m_texId1);
            p6->GetQuad(m_texId0, m_texId1, &f144, &f140, &f13c, &f138);
            if (pRaster != 0 && (pES->m_hardStateDirty & 1)) {
                pES->SetRaster(0, pRaster);
                float d0 = 0.0f, d1 = 0.0f;
                char  dummy[264];
                (void)d1; (void)dummy;
                p6->GetQuad(m_texId0, m_texId1, &d0, &f144, &f140, &f13c);
                fVar9  = f140;
                fVar13 = f144;
                bCommon = true;
            }
        } else if (pES->m_hardStateDirty & 1) {
            pES->SetRaster(0, m_srcRaster);
            fVar9  = (float)(unsigned)((unsigned short*)m_srcRaster)[7];
            fVar13 = (float)(unsigned)((unsigned short*)m_srcRaster)[6];
            bCommon = true;
        }
        if (bCommon) {
            f14c = (float)(int)fVar13;
            f148 = (float)(int)fVar9;
            DrawList dl;
            dl.Init();
            dl.Add(0, m_params[0], m_params[1], m_params[2], m_params[3]);
            dl.Add(1, m_params[4], m_params[5], m_params[6], m_params[7]);
            dl.Add(2, f14c, f148, 1.0f / f14c, 1.0f / f148);
            dl.Add(3, m_params[12], m_params[13], m_params[14], m_params[15]);
        }
    }

    // ---- additional rect ids -------------------------------------------------
    if (m_vecBegin != m_vecEnd) {
        int count = (int)((m_vecEnd - m_vecBegin) >> 3);
        if ((unsigned)(count - 1) < 4u) {
            unsigned short i = 0;
            if (count > 0) {
                do {
                    int* e = (int*)(m_vecBegin + i * 8);
                    Raster* r = p6->GetRaster(e[0], e[1]);
                    if (r != 0)
                        pES->SetRaster((int)i + 1, r);
                    i = (unsigned short)(i + 1);
                } while ((unsigned)i < (unsigned)count);
            }
        }
    }

    g_renderState |= 0x10080;
    int save18 = DAT_016f9218;
    int save3c = DAT_016f923c;
    DAT_016f9218 = 0;
    DAT_016f923c = 8;
    pES->Dispatch();
    GlobalState_D3D9Sync();

    int iR = FUN_011f1120();
    unsigned short uVar1 = *(unsigned short*)(*(int*)(iR + 0x40) + 0xc);
    iR = FUN_011f1120();
    unsigned short uVar2 = *(unsigned short*)(*(int*)(iR + 0x40) + 0xe);

    float* out = 0;
    char   st[264];
    if (!FUN_006ddcc0(2, 4, (void**)&out, st))
        goto restore;

    if (m_b83 == 0) {
        f13c = m_angle;
        if (m_angle == 0.0f && m_tx == 0.0f && m_ty == 0.0f &&
            m_sx == DAT_01485720 && m_sy == DAT_01485720) {
            fVar13 = DAT_016077c8 * 2.0f;
            fVar12 = (float)uVar1;
            fVar9  = m_srcQuad[1];
            OUT(0) = (m_srcQuad[0] - 1.0f) - (DAT_016077c4 * 2.0f) / fVar12;
            fVar11 = (float)uVar2;
            OUT(1) = 0.0f;
            OUT(2) = (fVar9 - 1.0f) - fVar13 / fVar11;
            fVar13 = DAT_016077c8;
            fVar9  = m_srcQuad[3];
            OUT(6) = (m_srcQuad[2] + 1.0f) - (DAT_016077c4 * 2.0f) / fVar12;
            OUT(7) = 0.0f;
            OUT(8) = (fVar9 - 1.0f) - (fVar13 * 2.0f) / fVar11;
            fVar9  = m_srcQuad[5];
            fVar13 = DAT_016077c8 * 2.0f;
            OUT(0xc) = ((m_srcQuad[4] + 1.0f) - m_inset) - (DAT_016077c4 * 2.0f) / fVar12;
            OUT(0xd) = 0.0f;
            OUT(0xe) = (fVar9 + 1.0f) - fVar13 / fVar11;
            fVar9    = ((m_srcQuad[6] + m_inset) - 1.0f) - (DAT_016077c4 * 2.0f) / fVar12;
            f154     = (m_srcQuad[7] + 1.0f) - (DAT_016077c8 * 2.0f) / fVar11;
        } else {
            float fsin_v = (float)sin(f13c);
            float a124 = m_srcQuad[2] + 1.0f;
            float a120 = m_srcQuad[3] - 1.0f;
            float a11c = (m_srcQuad[4] + 1.0f) - m_inset;
            float a118 = m_srcQuad[5] + 1.0f;
            f140 = (float)uVar1;
            f148 = 1.0f / f140;
            f14c = (float)uVar2;
            float a114 = (m_srcQuad[6] + m_inset) - 1.0f;
            f144 = 1.0f / f14c;
            fVar12 = m_srcQuad[1] - 1.0f;
            float a12c = m_srcQuad[0] - 1.0f;
            float a110 = m_srcQuad[7] + 1.0f;
            f138 = fsin_v;
            f13c = (float)cos(m_angle);

            fVar9  = m_ty;
            fVar13 = m_sy;
            fVar11 = DAT_016077c8 * 2.0f;
            OUT(0) = ((a12c * f13c - fVar12 * f138) + m_tx * f148) * m_sx
                     - (DAT_016077c4 * 2.0f) / f140;
            OUT(1) = 0.0f;
            OUT(2) = ((fVar12 * f13c + a12c * f138) + fVar9 * f144) * fVar13
                     - fVar11 / f14c;
            fVar9  = m_ty; fVar13 = m_sy; fVar12 = DAT_016077c8 * 2.0f;
            OUT(6) = ((f13c * a124 - f138 * a120) + m_tx * f148) * m_sx
                     - (DAT_016077c4 * 2.0f) / f140;
            OUT(7) = 0.0f;
            OUT(8) = ((f13c * a120 + f138 * a124) + fVar9 * f144) * fVar13
                     - fVar12 / f14c;
            fVar9  = m_ty; fVar13 = m_sy; fVar12 = DAT_016077c8 * 2.0f;
            OUT(0xc) = ((f13c * a11c - f138 * a118) + m_tx * f148) * m_sx
                       - (DAT_016077c4 * 2.0f) / f140;
            OUT(0xd) = 0.0f;
            OUT(0xe) = ((f13c * a118 + f138 * a11c) + fVar9 * f144) * fVar13
                       - fVar12 / f14c;
            fVar9 = ((f13c * a114 - f138 * a110) + m_tx * f148) * m_sx
                    - (DAT_016077c4 * 2.0f) / f140;
            f154  = ((f13c * a110 + f138 * a114) + m_ty * f144) * m_sy
                    - (DAT_016077c8 * 2.0f) / f14c;
        }
        OUT(0x12) = fVar9;
        OUT(0x13) = 0.0f;
        OUT(0x14) = f154;
    } else {
        int q = m_quadrant;
        if (q == 1) {
            fVar9 = DAT_016077c8 * 2.0f;
            OUT(0) = -0.97f - (DAT_016077c4 * 2.0f) / (float)uVar1;
            OUT(1) = 0.0f;
            OUT(2) = 0.0399f - fVar9 / (float)uVar2;
            fVar13 = -0.03f - (DAT_016077c4 * 2.0f) / (float)uVar1;
            f154 = (DAT_016077c8 * 2.0f) / (float)uVar2;
            fVar9 = -0.03f;
            goto lab_3e76;
        } else if (q == 2) {
            fVar12 = DAT_016077c8 * 2.0f;
            fVar9  = (float)uVar1;
            OUT(0) = -0.97f - (DAT_016077c4 * 2.0f) / fVar9;
            fVar13 = (float)uVar2;
            OUT(1) = 0.0f;
            OUT(2) = -0.9202f - fVar12 / fVar13;
            fVar12 = DAT_016077c8 * 2.0f;
            OUT(6) = -0.03f - (DAT_016077c4 * 2.0f) / fVar9;
            OUT(7) = 0.0f;
            OUT(8) = -0.9202f - fVar12 / fVar13;
            fVar9  = (DAT_016077c4 * 2.0f) / fVar9;
            fVar12 = 0.9202f;
            fVar13 = (DAT_016077c8 * 2.0f) / fVar13;
        } else if (q == 3) {
            fVar9 = DAT_016077c8 * 2.0f;
            OUT(0) = -0.97f - (DAT_016077c4 * 2.0f) / (float)uVar1;
            OUT(1) = 0.0f;
            OUT(2) = 0.0399f - fVar9 / (float)uVar2;
            fVar13 = 0.97f - (DAT_016077c4 * 2.0f) / (float)uVar1;
            f154 = (DAT_016077c8 * 2.0f) / (float)uVar2;
            fVar9 = 0.97f;
            goto lab_3e76;
        } else if (q == 4) {
            fVar12 = DAT_016077c8 * 2.0f;
            fVar9  = (float)uVar1;
            OUT(0) = -0.97f - (DAT_016077c4 * 2.0f) / fVar9;
            fVar13 = (float)uVar2;
            OUT(1) = 0.0f;
            OUT(2) = 0.0399f - fVar12 / fVar13;
            fVar12 = DAT_016077c8 * 2.0f;
            OUT(6) = -0.03f - (DAT_016077c4 * 2.0f) / fVar9;
            OUT(7) = 0.0f;
            OUT(8) = 0.0399f - fVar12 / fVar13;
            fVar9  = (DAT_016077c4 * 2.0f) / fVar9;
            fVar12 = 0.9601f;
            fVar13 = (DAT_016077c8 * 2.0f) / fVar13;
        } else {
            goto lab_4104;
        }
        OUT(0xc) = -0.03f - fVar9;
        OUT(0xd) = 0.0f;
        OUT(0xe) = fVar12 - fVar13;
        fVar9 = DAT_016077c8 * 2.0f;
        OUT(0x12) = -0.97f - (DAT_016077c4 * 2.0f) / (float)uVar1;
        OUT(0x13) = 0.0f;
        OUT(0x14) = fVar12 - fVar9 / (float)uVar2;
        goto lab_4104;
    lab_3e76:
        f154 = 0.0399f - f154;
        OUT(6) = fVar13;
        OUT(7) = 0.0f;
        OUT(8) = f154;
        fVar13 = DAT_016077c8;
        OUT(0xc) = fVar9 - (DAT_016077c4 * 2.0f) / (float)uVar1;
        OUT(0xd) = 0.0f;
        OUT(0xe) = 0.9601f - (fVar13 * 2.0f) / (float)uVar2;
        fVar9 = DAT_016077c8 * 2.0f;
        OUT(0x12) = -0.97f - (DAT_016077c4 * 2.0f) / (float)uVar1;
        OUT(0x13) = 0.0f;
        OUT(0x14) = 0.9601f - fVar9 / (float)uVar2;
    }

lab_4104:
    OUT(3)  = *(float*)&g_negNaN;
    OUT(4)  = 0.0f;
    OUT(5)  = 1.0f;
    OUT(9)  = *(float*)&g_negNaN;
    OUT(10) = 1.0f;
    OUT(11) = 1.0f;
    OUT(15) = *(float*)&g_negNaN;
    OUT(16) = 1.0f;
    OUT(17) = 0.0f;
    OUT(21) = *(float*)&g_negNaN;
    OUT(22) = 0.0f;
    OUT(23) = 0.0f;
    FUN_006ddd10(3, a4);

restore:
    g_renderState |= 0x10080;
    DAT_016f9218 = save18;
    DAT_016f923c = save3c;
    m_viewer->End();
}

// @ 0x007b49f0
void ItemList::Fn(int a, int b, int c, int d)
{
    int n = end - begin;
    for (unsigned i = 0; i < (unsigned)n; i++) {
        IItem* item = begin[i];
        IOut* out = (IOut*)item->Get();
        out->Run(a, b, c, d);
    }
}

// @ 0x007b4a50
void partial_007b4a50(void)
{}

// @ 0x007b4b10
void partial_007b4b10(void)
{}

// @ 0x007b4c10
void Bounds6::Expand(const Vector3* p, int n, int stride)
{
    n = n - 1;
    if (n >= 0) {
        do {
            if (mn.x > mx.x) {
                mn = *p;
                mx = *p;
            } else {
                if (mn.x > p->x) mn.x = p->x; else if (p->x > mx.x) mx.x = p->x;
                if (mn.y > p->y) mn.y = p->y; else if (p->y > mx.y) mx.y = p->y;
                if (mn.z > p->z) mn.z = p->z; else if (p->z > mx.z) mx.z = p->z;
            }
            p = (const Vector3*)((const char*)p + stride);
            n = n - 1;
        } while (n >= 0);
    }
}

// @ 0x007b4cd0
void partial_007b4cd0(void)
{}

// @ 0x007b4d70
void partial_007b4d70(void)
{}

// @ 0x007b4e10
void partial_007b4e10(void)
{}

// @ 0x007b4ee0
void partial_007b4ee0(void)
{}

// @ 0x007b5090
void partial_007b5090(void)
{}

// @ 0x007b5320
void partial_007b5320(void)
{}

// @ 0x007b55f0
void __stdcall FitViewerToBounds(const float* b, FitViewer* v, int target, float yaw)
{
    if (!v)
        return;
    FitDevice* dev = GetApp()->GetDevice();
    int prev = dev->GetCurrent();
    if (!dev->Select(target))
        return;
    v->SetFov(1.0f);
    dev->GetScene()->Attach(0, v);
    dev->Select(prev);
    XForm xf;
    xf.flags = 0;
    xf.rev = 0;
    xf.pos.x = g_defaultPosX;
    xf.pos.y = g_defaultPosY;
    xf.pos.z = g_defaultPosZ;
    xf.scale = 1.0f;
    xf.m.Assign(g_identityBasis);
    v->SetXForm(&xf);
    xf.PreRotateY(yaw);
    Vector3_s007b_55f0 np = xf.pos;
    Matrix3 m2;
    m2.Assign(xf.m);
    float len = sqrtf(m2.row1.z * m2.row1.z + m2.row1.y * m2.row1.y + m2.row1.x * m2.row1.x + 1e-8f);
    float inv = 1.0f / len;
    Vector3_s007b_55f0 dir(m2.row1.x * inv, m2.row1.y * inv, m2.row1.z * inv);
    v->SetFov(1.0f);
    v->SetViewAngleY(50.0f);
    v->SetNear(0.01f);
    float ex = b[3] - b[0];
    float ey = b[4] - b[1];
    float ez = b[5] - b[2];
    float r = sqrtf(ey * ey + (ez * ez + ex * ex)) * 0.5f;
    _ReadWriteBarrier();
    float cx = (b[3] + b[0]) * 0.5f;
    float cy = (b[4] + b[1]) * 0.5f;
    float cz = (b[5] + b[2]) * 0.5f;
    xf.flags |= 4;
    xf.rev++;
    np.x = cx - dir.x * r;
    np.y = cy - dir.y * r;
    np.z = cz - dir.z * r;
    xf.pos = np;
    v->ApplyXForm(&xf);
    for (unsigned k = 0; k < 5000; k++) {
        Mat16 vp = *(const Mat16*)v->viewProj;
        cFrustumCull cull;
        cull.Setup(vp.m);
        unsigned res = cull.FrustumTestSphere(b, b + 3, 0);
        if (res & 0xc0)
            return;
        bool nb0 = !(res & 1);
        bool nb1 = !((res >> 1) & 1);
        bool nb2 = !((res >> 2) & 1);
        bool nb3 = !((res >> 3) & 1);
        bool nb4 = !((res >> 4) & 1);
        bool nb5 = !((res >> 5) & 1);
        if ((nb0 && nb1) || (nb2 && nb3)) {
            r = r * 1.01f;
            np.x = cx - dir.x * r;
            np.y = cy - dir.y * r;
            np.z = cz - dir.z * r;
        } else {
            if (nb4 || nb5)
                continue;
            if (nb0)
                np.x = np.x - 0.1f;
            else if (nb1)
                np.x = np.x + 0.1f;
            if (nb2)
                np.y = np.y - 0.1f;
            else if (nb3)
                np.y = np.y + 0.1f;
            else if (!(nb0 || nb1))
                continue;
        }
        xf.flags |= 4;
        xf.rev++;
        xf.pos = np;
        v->ApplyXForm(&xf);
    }
}

// @ 0x007b5ad0
void __stdcall PostRenderJob(IRefObj* owner, int arg14, int arg18, int tagv, int arg10)
{
    SmartP<JobInfo> job(new ("Graphics", 0, 0, 0, 0) JobInfo);
    if (!job->bound) {
        job->arg14 = arg14;
        IRefObj* old = job->owner;
        if (owner != old) {
            if (owner)
                owner->AddRef();
            job->owner = owner;
            if (old)
                old->Release();
        }
        job->bound = true;
        job->arg18 = arg18;
    }
    MsgBuf mb;
    mb.a = 1;
    mb.b = 0;
    mb.flag = 1;
    mb.d = 0;
    mb.e = 0;
    mb.tag = 0;
    mb.msg = 0;
    mb.g = mb.h = mb.i = mb.j = 0;
    {
        SmartP<JobMsg> m(new ("Graphics", 0, 0, 0, 0) JobMsg);
        m->job = job.p;
        m->arg10 = arg10;
        mb.flag = 0;
        mb.b = tagv;
        mb.tag = 0x5fadac4;
        mb.msg = m.p;
        SinkObj* sink = GetSink();
        sink->Post((int)job->Build(0, &mb));
    }
}

// @ 0x007b5c80
void __stdcall MeshBoundingSphere(MeshVec* v, Vector3_s007b_55f0* outCenter, float* outRadius)
{
    Bounds6_s007b_55f0 b;
    int n = (int)(v->end - v->begin);
    for (int i = 0; i < n; i++) {
        int idx = FindEntry(v->begin[i], 1, -1, 3, 0xe);
        if (idx >= 0) {
            MeshEntry* base = v->begin[i]->entries;
            const MeshGeom& g = base[idx].geom;
            b.Expand(g.verts, g.count, base[idx].stride);
        }
    }
    if (b.mn.x > b.mx.x)
        return;
    float dx = b.mx.x - b.mn.x;
    float dy = b.mx.y - b.mn.y;
    float dz = b.mx.z - b.mn.z;
    *outCenter = Vector3_s007b_55f0((b.mx.x + b.mn.x) * 0.5f, (b.mx.y + b.mn.y) * 0.5f, (b.mx.z + b.mn.z) * 0.5f);
    *outRadius = sqrtf(dx * dx + dy * dy + dz * dz) * 0.5f + 1.0f;
}

// @ 0x007b5e20
void FrameJob::Fit()
{
    GetBlitter()->Blit(a18, b1c, (int)data);
    int minI = h;
    int maxI = 0;
    int minJ = w;
    int maxJ = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (data[(i * w + j) * 4 + 3]) {
                if (j < minI) minI = j;
                if (j > maxI) maxI = j;
                if (i < minJ) minJ = i;
                if (i > maxJ) maxJ = i;
            }
        }
    }
    int o0, o1, o2, o3;
    GetBlitter()->MeasureSomething(sc->w8, sc->hc, &o0, &o1, &o2, &o3);
    float fMinI = (float)minI;
    float dI = (float)fabs(maxI - fMinI);
    float fMinJ = (float)minJ;
    float dJ = (float)fabs(fMinJ - maxJ);
    float scale;
    if (dI > dJ)
        scale = (float)h / dI;
    else
        scale = (float)w / dJ;
    scale = scale * 0.8f;
    ViewParams* p = *sc->node->params;
    float inv = 1.0f / (float)h;
    p->padX = (((float)h - scale * dI) * 0.5f * inv) * 0.75f;
    p->padY = (((float)w - scale * dJ) * 0.5f * inv) * 0.75f;
    p->offX = fMinI * inv;
    p->offY = fMinJ * inv;
    p->sx = 1.2f;
    p->sy = 1.2f;
    p->scale = scale;
    p->z = 0.0f;
}

// @ 0x007b6010
void RtJobA::Run()
{
    TargetFactory* f = GetTargetFactory();
    TargetObj* obj = f->Create(p->f20, p->f24, p->f18, p->f1c, 1, 0x208, 0x15, 8);
    AutoTarget ref(obj);
    if (!(obj->flags & 1))
        GetTargetFactory()->Register(obj);
    UploadTargetA(obj);
}

// @ 0x007b6160
void FrameJob::FitAspect()
{
    GetBlitter()->Blit(a18, b1c, (int)data);
    int minI = h;
    int maxI = 0;
    int minJ = w;
    int maxJ = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (data[(i * w + j) * 4 + 3]) {
                if (j < minI) minI = j;
                if (j > maxI) maxI = j;
                if (i < minJ) minJ = i;
                if (i > maxJ) maxJ = i;
            }
        }
    }
    int o0, o1, o2, o3;
    GetBlitter()->MeasureSomething(sc->w8, sc->hc, &o0, &o1, &o2, &o3);
    FrameScene* s = sc;
    float fMinI = (float)minI;
    float dI = (float)fabs(maxI - fMinI);
    float fMinJ = (float)minJ;
    float dJ = (float)fabs(fMinJ - maxJ);
    float scale;
    if (dI > dJ)
        scale = (s->fitSize / dI) * (float)h;
    else
        scale = (s->fitSize / dJ) * (float)w;
    float hf = (float)h;
    float py = ((float)w - scale * dJ) * 0.5f;
    float inv = 1.0f / hf;
    float padY = (inv * py) * 0.75f;
    float padX = (((float)h - scale * dI) * 0.5f * inv) * 0.75f;
    if (dJ < dI)
        padY = (s->fitAspect * inv) * py + padY;
    ViewParams* p = *s->node->params;
    p->padX = padX;
    p->offX = fMinI * inv;
    p->offY = fMinJ * inv;
    p->padY = padY;
    p->sx = 1.2f;
    p->sy = 1.2f;
    p->scale = scale;
    p->z = 0.0f;
}

// @ 0x007b63b0
void RtJobB::Run()
{
    TargetFactory* f = GetTargetFactory();
    TargetObj* obj = f->Create(p->f10, p->f0c, p->f1c, p->f20, 1, 0x208, 0x15, 8);
    AutoTarget ref(obj);
    if (!(obj->flags & 1))
        GetTargetFactory()->Register(obj);
    UploadTargetB(obj);
}

// @ 0x007b64f0
void __fastcall RefHolder_Reset(RefHolder* h)
{
    if (h->p) {
        TargetObj* o = h->p;
        if (o) {
            h->p = 0;
            static_cast<RcBase*>(o)->Release();
        }
    }
}

// @ 0x007b6570
void ThumbA::Run6570(int a1, int a2, int* a3, int a4)
{
    viewer->Copy(*a3, 0, 0);
    viewer->F4b50(1.0f);
    MsgRef mr(new("Graphics", 0, 0, 0, 0) Msg());
    Msg* m = mr.p;
    int a[2] = { -1, -1 };
    Gfx_67dd40()->f57(a);
    int b[2] = { -1, -1 };
    Gfx_67ddb0()->f6(b);
    viewer->SetRaster(a, 1);
    float col[4] = { 0.0f, 0.0f, 0.0f, g_1485720 };
    viewer->F3c20(col);
    viewer->F3c50(7);
    m->f8 = SP_App()->f20()->f7();
    SP_MessageServer()->f5(0x12d74a2, m, 0);
    ViewerRef ctx = { (int)viewer, 0, 0, 0 };
    p14->o->f3(a1, a2, &ctx, a4);
    Gfx_67ddb0()->f22(a, b, a4, 1.0f);
    Fn35a0();
}

// @ 0x007b6730
void ThumbB::Run6730(int a1, int a2, int a3, int a4)
{
    {
        int rect[4] = { 0, 0, 0x200, 0x200 };
        viewerA->F4a60(rect);
    }
    if (viewerA->Update()) {
        memcpy(m14, g_16f8b10, sizeof(m14));
        memcpy(m54, g_16f8c70, sizeof(m54));
        shader(0x20a, m14, 1);
        shader(0x20b, m54, 1);
        viewerA->F3c10();
    }
    GfxB* g = Gfx_67ddb0();
    Gfx_67dda0();
    if (bd8) {
        Fn3820(viewerA, r94, a4);
    } else {
        viewerA->SetRaster(r94, 1);
        viewerA->F3c50(7);
        ViewerRef ctx = { (int)viewerA, 0, 0, 0 };
        oa8->f79()->f3(1, a2, &ctx, a4);
    }
    if (bd8) {
        Fn3820(viewerB, r9c, a4);
    } else {
        viewerB->SetRaster(r9c, 1);
        viewerB->F3c50(7);
        ViewerRef ctx = { (int)viewerB, 0, 0, 0 };
        oa8->f79()->f3(a1, a2, &ctx, a4);
    }
    shader(0x20a, 0, 0);
    shader(0x20b, 0, 0);
    g->f25((int)oc0, a1, a2, a3, a4);
}

// @ 0x007b68f0
void ThumbC::Run68f0(int flag, int a2, int a3, int a4, int a5)
{
    viewer->SetRaster(raster, 1);
    if (flag == 0)
        viewer->F3c50(7);
    ViewerRef ctx = { (int)viewer, 0, 0, 0 };
    next->Fn49f0(a2, a3, &ctx, a5);
}

// @ 0x007b6980
void ThumbD::Run6980(int a, int b, int c, int d)
{
    int lim = count;
    if (lim == 0) {
        Fn49f0(a, b, c, d);
        return;
    }
    int n = (int)(end - begin);
    int idx = index;
    lim += idx;
    if (lim > n) lim = n;
    for (int i = idx; i < lim; i++)
        begin[i]->f4()->f3(a, b, c, d);
    if (lim < n) {
        index = lim;
        Mgr67dd50* m = Mgr_67dd50();
        JobStatus st;
        st.zero = 0;
        for (int k = 0; k < 8; k++) st.z[k] = 0;
        st.one = 1;
        st.flag = 1;
        m->f30(this, 0, &st);
        return;
    }
    if (msgArg != 0)
        SP_MessageServer()->f6(msgId, msgArg, 0, 0);
}

// @ 0x007b6a90
void ItemList2::Fn(int a, int b, int c, int d)
{
    if (begin != end) {
        int n = end - begin;
        for (unsigned i = 0; i < (unsigned)n; i++) {
            IItem* item = begin[i];
            IOut* out = (IOut*)item->Get();
            out->Run(a, b, c, d);
        }
    }
    Other();
}

// @ 0x007b6b60
RefVec::~RefVec()
{
    DestroyRange(mBegin, mEnd);
}

// @ 0x007b6bd0
AbilityA::~AbilityA()
{}

// @ 0x007b6c70
AbilityB::~AbilityB()
{
    if (mCap - mBegin > 1 && mBegin)
        operator_delete__(mBegin);
}

// @ 0x007b6d50
char FitJob::Fit6d50(SphereVec* v, cViewer_s007b_6570* vw, const float* c, const float* off, float* fov)
{
    float fv = *fov;
    Sphere6 s;
    XForm_s007b_6570 xf;
    vw->SetViewAngleY(fv);
    cFrustumCull_s007b_6570 cull1;
    Mat16 vp1 = *(Mat16*)vw->viewProj;
    cull1.Setup(vp1.m);
    int n = (int)(v->end - v->begin);
    for (int i = 0; i < n; i++) {
        s = v->begin[i];
        if (cull1.FrustumTestSphere(&s.c.x, &s.e.x, 0) >= 0) {
            xf.flags = 0;
            xf.rev = 0;
            xf.pos.x = g_defaultPosX;
            xf.pos.y = g_defaultPosY;
            xf.pos.z = g_defaultPosZ;
            xf.scale = g_1485720;
            xf.m.row0 = Vector3_s007b_6570(g_identityBasis_s007b_6570.row0.x, g_identityBasis_s007b_6570.row0.y, g_identityBasis_s007b_6570.row0.z);
    xf.m.row1 = Vector3_s007b_6570(g_identityBasis_s007b_6570.row1.x, g_identityBasis_s007b_6570.row1.y, g_identityBasis_s007b_6570.row1.z);
    xf.m.row2 = Vector3_s007b_6570(g_identityBasis_s007b_6570.row2.x, g_identityBasis_s007b_6570.row2.y, g_identityBasis_s007b_6570.row2.z);
            vw->F40f0(&xf);
            xf.pos = xf.pos - *(const Vector3_s007b_6570*)off;
            xf.flags |= 4;
            xf.rev++;
            vw->F4d00(&xf);
            return 0;
        }
    }
    float scaled = fv * g_13ec4b4;
    vw->SetViewAngleY(scaled);
    cFrustumCull_s007b_6570 cull2;
    Mat16 vp2 = *(Mat16*)vw->viewProj;
    cull2.Setup(vp2.m);
    n = (int)(v->end - v->begin);
    bool all = true;
    for (int i = 0; i < n; i++) {
        s = v->begin[i];
        if (cull2.FrustumTestSphere(&s.c.x, &s.e.x, 0) >= 0)
            all = false;
    }
    if (!all)
        return 1;
    xf.flags = 0;
    xf.rev = 0;
    xf.pos.x = g_defaultPosX;
    xf.pos.y = g_defaultPosY;
    xf.pos.z = g_defaultPosZ;
    xf.scale = g_1485720;
    xf.m.row0 = Vector3_s007b_6570(g_identityBasis_s007b_6570.row0.x, g_identityBasis_s007b_6570.row0.y, g_identityBasis_s007b_6570.row0.z);
    xf.m.row1 = Vector3_s007b_6570(g_identityBasis_s007b_6570.row1.x, g_identityBasis_s007b_6570.row1.y, g_identityBasis_s007b_6570.row1.z);
    xf.m.row2 = Vector3_s007b_6570(g_identityBasis_s007b_6570.row2.x, g_identityBasis_s007b_6570.row2.y, g_identityBasis_s007b_6570.row2.z);
    vw->F40f0(&xf);
    xf.flags |= 4;
    xf.rev++;
    xf.pos += *(const Vector3_s007b_6570*)off * g_1471064;
    vw->F4d00(&xf);
    return 0;
}

// @ 0x007b7270
void FitJob::Run7270(SphereVec* v, cViewer_s007b_6570* vw, int target, const float* c, float k, float yaw)
{
    if (!vw)
        return;
    FitDevice_s007b_6570* dev = SP_App()->f20();
    {
        XForm_s007b_6570 xf;
        xf.flags = 0;
        xf.rev = 0;
        xf.pos.x = g_defaultPosX;
        xf.pos.y = g_defaultPosY;
        xf.pos.z = g_defaultPosZ;
        xf.scale = g_1485720;
        xf.m.Assign(g_identityBasis_s007b_6570);
        vw->F4d00(&xf);
    }
    if (target) {
        int prev = dev->GetCurrent();
        if (!dev->Select(target))
            return;
        vw->F4b50(1.0f);
        dev->GetScene()->Attach(0, vw);
        dev->Select(prev);
    } else {
        vw->F4b50(1.0f);
        dev->GetScene()->Attach(0, vw);
    }
    XForm_s007b_6570 xf2;
    xf2.flags = 0;
    xf2.rev = 0;
    xf2.pos.x = g_defaultPosX;
    xf2.pos.y = g_defaultPosY;
    xf2.pos.z = g_defaultPosZ;
    xf2.scale = g_1485720;
    xf2.m.Assign(g_identityBasis_s007b_6570);
    vw->F40f0(&xf2);
    xf2.PreRotateY(yaw);
    xf2.pos.x = c[0];
    xf2.pos.y = c[1];
    xf2.pos.z = c[2];
    xf2.flags |= 4;
    xf2.rev++;
    vw->F4d00(&xf2);
    Matrix3_s007b_6570 m2;
    m2.Assign(xf2.m);
    float inv = 1.0f / (float)sqrt((double)(m2.row1.x * m2.row1.x + m2.row1.y * m2.row1.y + m2.row1.z * m2.row1.z + g_13ec4b8));
    float s = k * g_140ffc8;
    float off[3];
    off[0] = m2.row1.x * inv * s;
    off[1] = m2.row1.y * inv * s;
    off[2] = m2.row1.z * inv * s;
    dev->GetScene()->s19();
    vw->F4b50(1.0f);
    float fov = vw->F40a0();
    vw->F4ba0(g_13eb960);
    int i = 0;
    do {
        if (Fit6d50(v, vw, c, off, &fov))
            break;
        i++;
    } while ((float)i < g_140f7ac);
    vw->SetViewAngleY(fov);
}

// @ 0x007b7530
void partial_007b7530(void)
{}

// @ 0x007b77a0
void partial_007b77a0(void)
{}

// @ 0x007b7830
void partial_007b7830(void)
{}

// @ 0x007b7920
void partial_007b7920(void)
{}

// @ 0x007b7a20
void partial_007b7a20(void)
{}

// @ 0x007b7ac0
void cThumbnailManager::Render(int p1, int p2, const RenderInfo* ri, int p4)
{
    uint32_t savedShaderData = g_shaderData223;
    SetShaderData(0x223, 0, 1);
    ThumbMessage* rawMsg = new ("Graphics", 0, 0, 0, 0) ThumbMessage;
    SmartP<ThumbMessage> msg(rawMsg);

    if (mpSettings->mMode == 0) {
        int target[2];
        target[0] = -1;
        target[1] = -1;
        GetRasterSource()->GetTargetRaster(target);
        int source[2];
        source[0] = -1;
        source[1] = -1;
        GetCapture()->GetSize(source);
        mpViewer->SetRaster(target, true);
        mpViewer->SetClearFlags(7);
        rawMsg->mpViewer = mpViewer;
        MessageServer()->PostMessage(0x12d74a2, rawMsg, 0);
        RenderInfo info;
        info.viewer = mpViewer;
        info.a = 0;
        info.b = 0;
        info.c = 0;
        mpSettings->mpRenderer->Render(p1, p2, &info, p4);
        GetCapture()->Capture(target, source, p4, 0.0f);
        FinishSingle();
    } else if (mpSettings->mMode == 1) {
        int tilesPerRow = sAppProperties->GetIntProperty(0x5893ee8);
        int tileSize = sAppProperties->GetIntProperty(0x5893ed4);
        unsigned int tileCount = tilesPerRow * tilesPerRow;
        const float* bg = GetVector3Value(sAppProperties->GetProperty(0x5d2c54b));
        Vector4 color;
        color.x = bg[0];
        color.y = bg[1];
        color.z = bg[2];
        color.w = 1.0f;
        int tileRaster[2];
        tileRaster[0] = -1;
        tileRaster[1] = -1;
        GetRasterSource()->GetTargetRaster(tileRaster);
        int captureRaster[2];
        captureRaster[0] = -1;
        captureRaster[1] = -1;
        GetRasterSource()->GetCaptureRaster(captureRaster);
        float step = DegreesToRadians(360.0f / (float)tileCount);

        for (unsigned int i = 0; i < tileCount; i++) {
            mpViewer->SetRaster(tileRaster, true);
            mpViewer->SetClearColor(&color);
            mpViewer->SetNear(10.0f);
            mpViewer->SetFar(10000.0f);
            mpViewer->SetClearFlags(7);

            bool b4f4edc94 = sAppProperties->GetBoolProperty(0x4f4edc94);
            bool bddca437d = sAppProperties->GetBoolProperty(0xddca437d);
            bool bab73e4f9 = sAppProperties->GetBoolProperty(0xab73e4f9);
            bool b5016cc22 = sAppProperties->GetBoolProperty(0x5016cc22);
            bool b5dee2437 = sAppProperties->GetBoolProperty(0x5dee2437);
            bool b05a3dc9e = sAppProperties->GetBoolProperty(0x5a3dc9e);
            sAppProperties->SetBoolProperty(0x4f4edc94, false);

            rawMsg->mpViewer = mpViewer;
            MessageServer()->PostMessage(0x12d74a2, rawMsg, 0);

            RenderInfo info;
            info.viewer = mpViewer;
            info.a = ri->a;
            info.b = ri->b;
            info.c = ri->c;
            sAppProperties->SetBoolProperty(0xddca437d, true);
            sAppProperties->SetBoolProperty(0xab73e4f9, false);
            sAppProperties->SetBoolProperty(0x5016cc22, false);
            sAppProperties->SetBoolProperty(0x5dee2437, false);
            sAppProperties->SetBoolProperty(0x5a3dc9e, false);
            mpSettings->mpRenderer->Render(p1, p2, &info, p4);
            sAppProperties->SetBoolProperty(0xddca437d, bddca437d);
            sAppProperties->SetBoolProperty(0xab73e4f9, bab73e4f9);
            sAppProperties->SetBoolProperty(0x5016cc22, b5016cc22);
            sAppProperties->SetBoolProperty(0x5dee2437, b5dee2437);
            sAppProperties->SetBoolProperty(0x5a3dc9e, b05a3dc9e);
            mpSettings->mpRenderer->Render(p1, p2, &info, p4);
            sAppProperties->SetBoolProperty(0x4f4edc94, b4f4edc94);

            mpViewer->SetRaster(captureRaster, true);
            int x, y, w, h;
            GetBlitter_s007b_7ac0()->MeasureSomething(captureRaster[0], captureRaster[1], &x, &y, &w, &h);
            x = (i % tilesPerRow) * tileSize;
            y = (i / tilesPerRow) * tileSize;
            w = tileSize;
            h = tileSize;
            mpViewer->SetViewportRectArgs((unsigned short)x, (unsigned short)y,
                                          (unsigned short)w, (unsigned short)h);
            mpViewer->SetClearColor(&color);
            mpViewer->SetClearFlags(7);
            GetCapture()->CaptureTile(mpViewer, tileRaster, captureRaster, p4, color.w);

            XForm_s007b_7ac0 xf;
            xf.flags = 0;
            xf.rev = 0;
            xf.pos = g_defaultPos;
            xf.scale = 1.0f;
            xf.m = g_identityBasis_s007b_7ac0;
            mpViewer->SetXForm(&xf);

            float theta, phi, radius;
            SphericalFromCartesian(xf.pos, &theta, &phi, &radius);
            xf.flags |= 4;
            phi = phi + step;
            xf.rev++;
            float sinTheta = sinf(theta);
            Vector3_s007b_7ac0 pos(sinTheta * cosf(phi) * radius, sinTheta * sinf(phi) * radius, cosf(theta) * radius);
            xf.pos = pos;
            mpViewer->ApplyXForm(&xf);

            float len = sqrtf(pos.z * pos.z + pos.y * pos.y + pos.x * pos.x + 1e-8f);
            float inv = 1.0f / len;
            Vector3_s007b_7ac0 dir(inv * pos.x, pos.y * inv, pos.z * inv);
            Vector3_s007b_7ac0 o = OrthogonalVector(dir);
            float olen = sqrtf(o.x * o.x + o.y * o.y + o.z * o.z + 1e-8f);
            float oinv = 1.0f / olen;
            Vector3_s007b_7ac0 right(o.x * oinv, o.y * oinv, o.z * oinv);
            Vector3_s007b_7ac0 up = right.Cross(dir);
            float ulen = sqrtf(up.x * up.x + up.y * up.y + up.z * up.z + 1e-8f);
            float uinv = 1.0f / ulen;

            RwMatrix m;
            m.right = right;
            m.up = Vector3_s007b_7ac0(uinv * up.x, uinv * up.y, uinv * up.z);
            m.at = Vector3_s007b_7ac0(-dir.x, -dir.y, -dir.z);
            m.pos = pos;
            mpViewer->SetCameraToWorldFromBasis(&m);
        }
        FinishTiled(tileSize);
    }
    SetShaderData(0x223, savedShaderData, 1);
}

// @ 0x007b8550
void partial_007b8550(void)
{}

// @ 0x007b8680
void partial_007b8680(void)
{}

// @ 0x007b8700
void partial_007b8700(void)
{}

// @ 0x007b8780
void partial_007b8780(void)
{}

// @ 0x007b87f0
void __stdcall ComputeBoundingSphere(void* obj, float* outCenter, float* outRadius)
{
    PtrFixedVec vec;
    BBox6 bb;
    bb.mn[0] = bb.mn[1] = bb.mn[2] = 0.0f;
    bb.mx[0] = bb.mx[1] = 0.0f;
    ((unsigned char*)&bb.mx[2])[0] = 0;
    ((unsigned char*)&bb.mx[2])[1] = 0;

    typedef bool (__thiscall* GetFn)(void*, PtrFixedVec*, BBox6*);
    if (!((GetFn)VSLOT(obj, 11))(obj, &vec, &bb))
        return;

    bb.mn[0] = bb.mn[1] = bb.mn[2] = FLT_MAX;
    bb.mx[0] = bb.mx[1] = bb.mx[2] = -FLT_MAX;

    uint n = (uint)(vec.end - vec.begin);
    for (uint i = 0; i < n; i++) {
        void* e = vec.begin[i];
        uint flags = *(uint*)((char*)e + 4);
        if (((flags >> 15) & 1) && (flags & 1)) {
            typedef const float* (__thiscall* BoundsFn)(void*, void*);
            const float* b = ((BoundsFn)VSLOT(obj, 24))(obj, e);
            const float* p = (const float*)((char*)e + 0xc);
            float lo0 = p[0] + b[0], lo1 = p[1] + b[1], lo2 = p[2] + b[2];
            float hi0 = p[0] + b[3], hi1 = p[1] + b[4], hi2 = p[2] + b[5];
            if (bb.mn[0] > bb.mx[0]) {
                bb.mn[0] = lo0; bb.mn[1] = lo1; bb.mn[2] = lo2;
                bb.mx[0] = hi0; bb.mx[1] = hi1; bb.mx[2] = hi2;
            } else {
                if (bb.mn[0] > lo0) bb.mn[0] = lo0;
                if (hi0 > bb.mx[0]) bb.mx[0] = hi0;
                if (bb.mn[1] > lo1) bb.mn[1] = lo1;
                if (hi1 > bb.mx[1]) bb.mx[1] = hi1;
                if (bb.mn[2] > lo2) bb.mn[2] = lo2;
                if (hi2 > bb.mx[2]) bb.mx[2] = hi2;
            }
        }
    }
    if (!(bb.mn[0] > bb.mx[0])) {
        float dx = bb.mx[0] - bb.mn[0];
        float dy = bb.mx[1] - bb.mn[1];
        float dz = bb.mx[2] - bb.mn[2];
        outCenter[0] = (bb.mx[0] + bb.mn[0]) * 0.5f;
        outCenter[1] = (bb.mx[1] + bb.mn[1]) * 0.5f;
        outCenter[2] = (bb.mx[2] + bb.mn[2]) * 0.5f;
        *outRadius = sqrtf((dz * dz + dy * dy) + dx * dx) * 0.5f + 1.0f;
    }
}

// @ 0x007b8b30
cFilterRes* cFilterRes::Ctor()
{
    vtbl1 = g_vtbl_13ec458;
    m08 = 0;
    vtbl0 = g_vtbl_1410024;
    vtbl1 = g_vtbl_1410014;
    m0c = 0;
    m10 = 0;
    m94 = m98 = m9c = ma0 = -1;
    ma4 = 0;
    ma8 = 0;
    mac.b = 0; mac.e = 0; mac.c = 0;    // RefVector at +0xac
    mc0 = 0;
    mc4 = 0;
    md8 = 0;
    return this;
}

// @ 0x007b8be0
void cFilterRes::Dtor()
{
    vtbl0 = g_vtbl_1410024;
    vtbl1 = g_vtbl_1410014;
    mac.Destroy();
    if (ma8) ma8->Release();
    if (ma4) ma4->Release();
    vtbl0 = g_vtbl_13eb938;
    vtbl1 = g_vtbl_13ec458;
}

// @ 0x007b8cb0
void cCSAThumbnailJob::RenderLargeTiledImage(int a0, int a1, int* a2, int a3)
{
    cCSAJobParams* P = mP;
    mViewer->Copy(*a2, 0, 0);
    int rect[4] = { 0, 0, 0, 0 };
    mViewer->Fn3c20(rect);

    unsigned int n = P->mTileCount;
    float s1, s2;
    mViewer->Fn40c0(&s1, &s2);
    float inv = 1.0f / (float)n;
    s1 = s1 * inv;
    s2 = s2 * inv;
    mViewer->Fn4b00(s1, s2);

    int dA, dB, tw, th;
    typedef void (__thiscall* QueryFn)(void*, int, int, int*, int*, int*, int*);
    void* rtt = GetRTTManager();
    ((QueryFn)VSLOT(rtt, 9))(rtt, P->m8, P->mc, &dB, &dA, &th, &tw);

    typedef unsigned char* (__thiscall* RasterFn)(void*, int, int);
    rtt = GetRTTManager();
    unsigned char* raster = ((RasterFn)VSLOT(rtt, 6))(rtt, P->m8, P->mc);
    int bpp = raster[0x10] >> 3;
    int tileBytes = bpp * th * tw;

    unsigned char* big  = (unsigned char*)operator new(tileBytes * n * n, "Graphics", 0, 0, 0, 0);
    unsigned char* tile = (unsigned char*)operator new(tileBytes, "Graphics", 0, 0, 0, 0);

    if (n != 0) {
        float nm1 = (float)(n - 1);
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = 0; j < n; j++) {
                float x = (nm1 - (float)i * 2.0f) * s1;
                float y = -(nm1 - (float)j * 2.0f) * s2;
                mViewer->SetPos(x, y);
                mViewer->SetRaster(&P->m8, 1);
                mViewer->Fn3c50(7);

                struct { cTileViewer* v; int z0, z1, z2; } q = { mViewer, 0, 0, 0 };
                typedef void* (__thiscall* GetLayerFn)(void*);
                typedef void  (__thiscall* DrawFn)(void*, int, int, void*, int);
                void* l = ((GetLayerFn)VSLOT(mB, 0x13c / 4))(mB);
                ((DrawFn)VSLOT(l, 3))(l, a0, a1, &q, a3);
                l = ((GetLayerFn)VSLOT(mA, 0x13c / 4))(mA);
                ((DrawFn)VSLOT(l, 3))(l, a0, a1, &q, a3);
                if (P->m54)
                    ((DrawFn)VSLOT(P->m54, 3))(P->m54, a0, a1, &q, a3);

                typedef void (__thiscall* RenderFn)(void*, int, int, int, void*, int, int);
                void* rd = GetRenderer();
                ((RenderFn)VSLOT(rd, 0x40 / 4))(rd, a3, 0x12, 0x12, &q, 1, 0);

                if (i == n - 1 && j == n - 1 && P->mSink) {
                    int* t = *P->mSink->mpData;
                    t[7] = P->m8;
                    t[8] = P->mc;
                    P->mSink->Flush(a0, a1, &q, a3);
                }

                typedef void (__thiscall* ReadFn)(void*, int, int, void*);
                rtt = GetRTTManager();
                ((ReadFn)VSLOT(rtt, 0xc))(rtt, P->m8, P->mc, tile);

                unsigned char* dst = big + ((((int)j * tw * (int)n) + (int)i) * bpp * th);
                unsigned char* src = tile;
                int rowBytes = bpp * th;
                int stride = rowBytes * (int)n;
                for (int k = 0; k < tw; k++) {
                    memcpy(dst, src, rowBytes);
                    src += rowBytes;
                    dst += stride;
                }
            }
        }
    }

    int totalW = tw * (int)n;
    int totalH = th * (int)n;
    cImageObj* img = 0;
    void* mem = operator new(0x38, "Graphics", 0, 0, 0, 0);
    if (mem)
        img = ((cImageObj*)mem)->Ctor(totalH, totalW, big, P->mId, 0x417b3a7);
    if (img) img->AddRef();

    ResKey key;
    key.a = P->mId;
    key.b = (unsigned)P->m30;
    key.c = 0x41602b00;
    img->m08 = key.a;
    img->m0c = key.b;
    img->m10 = key.c;

    void* area = GetSaveArea(0x11ac196);
    void* mgr = GetResourceMan();
    WStr path;
    WStr_Format(&path, L"CRE_%s-%08x_ful.png", P->mName, P->mId);
    typedef void (__thiscall* MakeKeyFn)(void*, ResKey*, const wchar_t*);
    ((MakeKeyFn)VSLOT(mgr, 0x80 / 4))(mgr, &key, path.b);
    AsyncSave(img, area, 0, &key);
    operator delete[](tile);
    operator delete[](big);
    img->Release();
}

// @ 0x007b91f0
#pragma float_control(precise, off, push)
void cPlanetCapture::Setup(CaptureCam* cam)
{
    if (mInit)
        return;
    CaptureCam* old = mCam;
    if (cam != old) {
        if (cam) cam->AddRef();
        mCam = cam;
        if (old) old->Release();
    }
    cViewer_s007b_87f0* v = NewViewer();
    mViewer = v;
    v->Init(0);
    mInit = true;

    CapBox bb;
    bb.mn = Vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    bb.mx = Vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    float r = mCam->radius;
    bb.mn.x -= r; bb.mn.y -= r; bb.mn.z -= r;
    bb.mx.x += r; bb.mx.y += r; bb.mx.z += r;

    CapBoxVec boxes;
    boxes.b = 0; boxes.e = 0; boxes.c = 0;
    boxes.DoInsertValue(0, &bb);

    unsigned int key = FNV1_String8("PlanetCapture", 0x811c9dc5u, 1);
    Vec3 sun;
    typedef void (__thiscall* GetDirFn)(void*, Vec3*);
    void* lm = LightingManager();
    ((GetDirFn)VSLOT(lm, 9))(lm, &sun);

    typedef void (__thiscall* CaptureFn)(void*, CapBoxVec*, cViewer_s007b_87f0*, unsigned int, Vec3*, float, float);
    void* svc = CaptureService();
    Vec3 origin(0.0f, 0.0f, 0.0f);
    ((CaptureFn)VSLOT(svc, 20))(svc, &boxes, mViewer, key, &origin, 30.0f, (float)atan2((double)sun.y, (double)sun.x));
}
#pragma float_control(pop)

// @ 0x007b9420
void cJobPostFilter::Init(bool b)
{
    if (m_flag)
        return;
    cViewer_s007b_87f0* v = NewViewer();
    m_viewer = (ShutdownViewer*)v;
    v->Init(0);
    ((cViewer_s007b_87f0*)m_viewer)->Fn3cc0(0);
    m_b81 = b;
    if (!m_vec.empty())
        m_vec.clear();
    int* z = (int*)((char*)this + 0x3c);
    for (int i = 0; i < 16; i++) z[i] = 0;
    m_flag = true;
}

// @ 0x007b9510
void cJobPostFilter::Init(int a, const int* p, const int* q, bool b)
{
    if (m_flag)
        return;
    cViewer_s007b_87f0* v = NewViewer();
    m_viewer = (ShutdownViewer*)v;
    v->Init(0);
    ((cViewer_s007b_87f0*)m_viewer)->Fn3cc0(0);
    int* me = (int*)this;
    me[3] = a;
    me[4] = p[0];
    me[5] = p[1];
    me[7] = q[0];
    me[8] = q[1];
    if (!m_vec.empty())
        m_vec.clear();
    int* z = (int*)((char*)this + 0x3c);
    for (int i = 0; i < 16; i++) z[i] = 0;
    m_b81 = b;
    m_flag = true;
}

// @ 0x007b9620
void cJobPostFilter::Shutdown()
{
    if (!m_flag)
        return;
    if (m_viewer) {
        m_viewer->Destroy1();
        ShutdownViewer* v = m_viewer;
        if (v) {
            v->Destroy2();
            operator delete[](v);
        }
        m_viewer = 0;
    }
    if (m_p18)
        m_p18 = 0;
    if (!m_vec.empty())
        m_vec.clear();
    m_flag = false;
}

// @ 0x007b9690
void VecPair::Push(Pair2* p)
{
    v.push_back(p);
}

// @ 0x007b96d0
void cFilterChainJob::Shutdown()
{
    if (!mInitialized)
        return;
    if (!mFilters.empty()) {
        uint n = mFilters.size();
        for (uint i = 0; i < n; i++) {
            mFilters[i].mpObject->Shutdown();
            mFilters[i].reset();
        }
        mFilters.clear();
    }
    mInitialized = false;
}

// @ 0x007b9750
int cFilterChainJob::AddFilter(IRel* p)
{
    {
        ARC tmp((IRC2*)p);
        mFilters.push_back(tmp);
    }
    return (int)mFilters.size() - 1;
}

// @ 0x007b97d0
void partial_007b97d0(void)
{}

// @ 0x007b9990
void partial_007b9990(void)
{}

// @ 0x007b9b00
void partial_007b9b00(void)
{}

// @ 0x007b9e80
void TerrainMgr::Teardown()
{
    if (!m_terrainFilterInitialized)
        return;
    m_viewer->Destroy1();
    Viewer* v = m_viewer;
    if (v) {
        v->Destroy2();
        operator delete[](v);
    }
    m_viewer = 0;
    m_filter0->InnerTeardown();
    TerrainFilter* p0 = m_filter0;
    if (p0) {
        m_filter0 = 0;
        p0->Release();
    }
    m_filter1->InnerTeardown();
    TerrainFilter* p1 = m_filter1;
    if (p1) {
        m_filter1 = 0;
        p1->Release();
    }
    m_filter2->InnerTeardown();
    TerrainFilter* p2 = m_filter2;
    if (p2) {
        m_filter2 = 0;
        p2->Release();
    }
    m_terrainFilterInitialized = false;
}

// @ 0x007b9f30
void partial_007b9f30(void)
{}

// @ 0x007ba0b0
void partial_007ba0b0(void)
{}

// @ 0x007ba350
namespace SP {
void cThumbnailManager_s007b_a350::InitPostProcessEffect(int type, cFilterChainJob* pChain, bool enable, bool alt, Vector2 blurOffset, float blurStrength)
{
    cRenderTargetRectID_s007b_a350 srcRect;

    if (type == 6 || type == 7 || type == 8 || type == 9) {
        if (!enable)
            return;
        Renderer()->GetCurrentRenderTarget(&srcRect);

        FilterPtr_s007b_a350 filter = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        filter->Initialize(0);
        if (alt) {
            filter->mMaterialId = 0x88549f64;
            filter->mSrcRectID = srcRect;
            filter->mDestRectID = (type == 7) ? mThumbRectID : mBlurThumbRectID1;
            filter->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            filter->mCustomParams[0] = 1.2f;
            filter->mCustomParams[1] = 1.0f;
            filter->mCustomParams[2] = 0.0f;
            filter->mCustomParams[3] = 1.0f;
            filter->mCustomParams[4] = 0.0f;
            filter->mCustomParams[5] = 1.0f;
            filter->mCustomParams[6] = 1.0f;
            filter->mCustomParams[7] = 0.0f;
        } else {
            filter->mMaterialId = 0x0fa800f3;
            filter->mSrcRectID = srcRect;
            filter->mDestRectID = (type == 7) ? mThumbRectID : mBlurThumbRectID1;
            filter->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            filter->mCustomParams[0] = 1.0f;
            filter->mCustomParams[1] = 1.0f;
            filter->mCustomParams[2] = 1.0f;
            filter->mCustomParams[3] = 1.0f;
            filter->mCustomParams[4] = 0.0f;
            filter->mCustomParams[5] = 1.2f;
            filter->mCustomParams[6] = 1.2f;
            filter->mCustomParams[7] = 0.0f;
        }
        filter->mCustomParams[15] = 0.0f;
        filter->mCustomParams[14] = 0.0f;
        filter->mCustomParams[13] = 0.0f;
        filter->mCustomParams[12] = 0.0f;
        pChain->AddFilter(filter);

        if (type == 6) {
            FilterPtr_s007b_a350 blurH = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
            FilterPtr_s007b_a350 blurV = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
            FilterPtr_s007b_a350 combine = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();

            blurH->InitBlur(100, mBlurThumbRectID1, mThumbRectID, 0);
            blurH->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            blurV->InitBlur(100, mThumbRectID, mBlurThumbRectID2, 0);
            blurV->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            blurH->mCustomParams[0] = 1.0f;
            blurH->mCustomParams[1] = -1.0f;
            blurH->mCustomParams[2] = -1.0f;
            blurH->mCustomParams[3] = 0.0f;
            blurV->mCustomParams[0] = 1.0f;
            blurV->mCustomParams[1] = -1.0f;
            blurV->mCustomParams[2] = 1.0f;
            blurV->mCustomParams[3] = 0.0f;

            combine->Initialize(0);
            combine->mMaterialId = 0xad3dd399;
            combine->mSrcRectID = mBlurThumbRectID1;
            combine->AddAdditionalRect(mBlurThumbRectID2);
            combine->mCustomParams[0] = 1.0f / (float)mThumbRaster->m_width;
            combine->mCustomParams[1] = 1.0f / (float)mThumbRaster->m_height;
            combine->mCustomParams[2] = 0.0f;
            combine->mCustomParams[3] = 0.0f;
            combine->mDestRectID = mThumbRectID;
            combine->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));

            pChain->AddFilter(blurH);
            pChain->AddFilter(blurV);
            pChain->AddFilter(combine);
        } else if (type == 8) {
            FilterPtr_s007b_a350 blur = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
            FilterPtr_s007b_a350 combine = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();

            blur->Initialize(0);
            blur->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            blur->mMaterialId = 0x2a4a174c;
            blur->mSrcRectID = mBlurThumbRectID1;
            blur->mCustomParams[0] = 1.0f / (float)mThumbRaster->m_width;
            blur->mCustomParams[1] = 1.0f / (float)mThumbRaster->m_height;
            blur->mCustomParams[2] = 0.0f;
            blur->mCustomParams[3] = 0.0f;
            blur->mDestRectID = mBlurThumbRectID2;
            Vector2 offset = blurOffset * -0.2f;
            blur->SetBlurParams(offset, offset, blurOffset, blurOffset, blurStrength);

            combine->Initialize(0);
            combine->mMaterialId = 0xda76c2bf;
            combine->mSrcRectID = mBlurThumbRectID1;
            combine->mDestRectID = mThumbRectID;
            combine->AddAdditionalRect(mBlurThumbRectID2);
            combine->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));

            pChain->AddFilter(blur);
            pChain->AddFilter(combine);
        }
    } else if (type == 1) {
        FilterPtr_s007b_a350 filter = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        cTextureInstance_s007b_a350* pTexture = TextureManager()->GetTexture(0x918c362c, 0x40607300, 0);
        if (pTexture) {
            rw::graphics::Raster_s007b_a350* pRaster = pTexture->GetRaster();
            filter->Initialize(0);
            filter->mMaterialId = 0xf515ba42;
            filter->mSrcRaster = pRaster;
            filter->mDestRectID = mThumbRectID;
            filter->SetCustomParams(0, Vector4_s007b_a350(6.0f, 6.0f, 5.0f, 5.0f));
            filter->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            pChain->AddFilter(filter);
        }
    } else if (type == 2) {
        FilterPtr_s007b_a350 filter = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        filter->Initialize(0);
        filter->mMaterialId = 0x46;
        filter->mSrcRectID = mThumbRectID;
        filter->mDestRectID = mThumbRectID;
        filter->SetCustomParams(0, Vector4_s007b_a350(0.8f, 0.5f, 0.3f, 1.0f));
        filter->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
        pChain->AddFilter(filter);
    } else if (type == 5) {
        int x, y, width, height;
        mRTTMgr->GetRTTInfo(mThumbRectID, &x, &y, &width, &height);
        int halfWidth = width / 2;
        int halfHeight = height / 2;

        cRenderTargetRectID_s007b_a350 id = mRTTMgr->AllocateRTT(halfWidth, halfHeight, 0x15, 0, -1, 0);
        mBlurThumbRectID1 = id;
        mRTTMgr->SetRTTName(id, "ThumbnailThresholdRTT1");
        id = mRTTMgr->AllocateRTT(halfWidth, halfHeight, 0x15, 0, -1, 0);
        mBlurThumbRectID2 = id;
        mRTTMgr->SetRTTName(id, "ThumbnailThresholdRTT2");
        id = mRTTMgr->AllocateRTT(width, height, 0x15, 0, -1, 0);
        mTempThumbnailBuffer = id;
        mRTTMgr->SetRTTName(id, "ThumbnailFullsizeTemp");

        FilterPtr_s007b_a350 threshold1 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        threshold1->Initialize(0);
        threshold1->mMaterialId = 0x5b6fc7d2;
        threshold1->mSrcRectID = mThumbRectID;
        threshold1->mDestRectID = mBlurThumbRectID1;
        threshold1->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));

        FilterPtr_s007b_a350 threshold2 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        threshold2->Initialize(0);
        threshold2->mMaterialId = 0x5b6fc7d1;
        threshold2->mSrcRectID = mThumbRectID;
        threshold2->mDestRectID = mBlurThumbRectID2;
        threshold2->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));

        FilterPtr_s007b_a350 quad1 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        FilterPtr_s007b_a350 quad2 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        FilterPtr_s007b_a350 quad3 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        FilterPtr_s007b_a350 quad4 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        FilterPtr_s007b_a350 copyBack = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();

        quad1->Initialize(0);
        quad1->mMaterialId = 0x050c0e26;
        quad1->AddAdditionalRect(mBlurThumbRectID1);
        quad1->AddAdditionalRect(mBlurThumbRectID2);
        quad1->mSrcRectID = mThumbRectID;
        quad1->mDestRectID = mTempThumbnailBuffer;
        quad1->SetViewport(0, 0, halfWidth, halfHeight, 1);
        quad1->SetCustomParams(0, Vector4_s007b_a350(0.9453125f, 0.76171875f, 0.30078125f, 0.0f));
        quad1->SetCustomParams(1, Vector4_s007b_a350(0.5234375f, 0.7109375f, 0.7265625f, 0.0f));
        quad1->SetCustomParams(3, Vector4_s007b_a350(0.9296875f, 0.83203125f, 0.8046875f, 0.0f));
        quad1->SetClearColor(cSPColorRGBA(1.0f, 1.0f, 1.0f, 1.0f));

        quad2->Initialize(0);
        quad2->mMaterialId = 0x050c0e26;
        quad2->AddAdditionalRect(mBlurThumbRectID1);
        quad2->AddAdditionalRect(mBlurThumbRectID2);
        quad2->mSrcRectID = mThumbRectID;
        quad2->mDestRectID = mTempThumbnailBuffer;
        quad2->SetViewport(halfWidth, 0, width, halfHeight, 2);
        quad2->SetCustomParams(0, Vector4_s007b_a350(0.671875f, 0.3984375f, 0.37109375f, 0.0f));
        quad2->SetCustomParams(1, Vector4_s007b_a350(0.77734375f, 0.640625f, 0.3828125f, 0.0f));
        quad2->SetCustomParams(3, Vector4_s007b_a350(0.88671875f, 0.4765625f, 0.59765625f, 0.0f));

        quad3->Initialize(0);
        quad3->mMaterialId = 0x050c0e26;
        quad3->AddAdditionalRect(mBlurThumbRectID1);
        quad3->AddAdditionalRect(mBlurThumbRectID2);
        quad3->mSrcRectID = mThumbRectID;
        quad3->mDestRectID = mTempThumbnailBuffer;
        quad3->SetViewport(0, halfHeight, halfWidth, height, 3);
        quad3->SetCustomParams(0, Vector4_s007b_a350(0.62109375f, 0.265625f, 0.24609375f, 0.0f));
        quad3->SetCustomParams(1, Vector4_s007b_a350(0.30078125f, 0.4296875f, 0.34765625f, 0.0f));
        quad3->SetCustomParams(3, Vector4_s007b_a350(0.54296875f, 0.63671875f, 0.38671875f, 0.0f));

        quad4->Initialize(0);
        quad4->mMaterialId = 0x050c0e26;
        quad4->AddAdditionalRect(mBlurThumbRectID1);
        quad4->AddAdditionalRect(mBlurThumbRectID2);
        quad4->mSrcRectID = mThumbRectID;
        quad4->mDestRectID = mTempThumbnailBuffer;
        quad4->SetViewport(halfWidth, halfHeight, width, height, 4);
        quad4->SetCustomParams(0, Vector4_s007b_a350(0.92578125f, 0.63671875f, 0.41015625f, 0.0f));
        quad4->SetCustomParams(1, Vector4_s007b_a350(0.9296875f, 0.8046875f, 0.84765625f, 0.0f));
        quad4->SetCustomParams(3, Vector4_s007b_a350(0.44140625f, 0.68359375f, 0.80078125f, 0.0f));

        copyBack->Initialize(0);
        copyBack->mMaterialId = 0x28;
        copyBack->mSrcRectID = mTempThumbnailBuffer;
        copyBack->mDestRectID = mThumbRectID;
        copyBack->SetCustomParams(0, Vector4_s007b_a350(1.0f, 1.0f, 1.0f, 1.0f));
        copyBack->SetCustomParams(1, Vector4_s007b_a350(0.0f, 1.0f, 1.0f, 0.0f));
        copyBack->SetCustomParams(3, Vector4_s007b_a350(0.0f, 0.0f, 0.0f, 0.0f));
        copyBack->SetClearColor(cSPColorRGBA(1.0f, 1.0f, 1.0f, 1.0f));

        pChain->AddFilter(threshold1);
        pChain->AddFilter(threshold2);
        pChain->AddFilter(quad1);
        pChain->AddFilter(quad2);
        pChain->AddFilter(quad3);
        pChain->AddFilter(quad4);
        pChain->AddFilter(copyBack);
    }
}
}  // namespace SP

// @ 0x007bb670
#pragma intrinsic(_InterlockedExchange)
namespace n670
{

struct RectID { int mPageID; int mAllocID; };
struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};

// RefBaseA22 -> callback object installed on the chain (0x20 bytes; vtable 0x1452a38)
struct RefBaseA22 {
    virtual ~RefBaseA22();
    virtual int AddRef();                            // +0x04
    virtual int Release();                           // +0x08
    volatile long mnRefCount;                        // +0x04
    RefBaseA22() { _InterlockedExchange(&mnRefCount, 0); }
};
struct cChainCallback : RefBaseA22 {
    int mField08, pad0c;                             // +0x08
    void* mChain;                                    // +0x10
    int pad14;
    int mField18, pad1c;                             // +0x18
    cChainCallback() : mField18(0) {}
    virtual ~cChainCallback();
};
struct DrvPtr {
    RefBaseA22* mpObject;
    DrvPtr& operator=(RefBaseA22* p)
    {
        if (p != mpObject) {
            RefBaseA22* const old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct CbPtr {
    RefBaseA22* mpObject;
    CbPtr(RefBaseA22* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~CbPtr() { if (mpObject) mpObject->Release(); }
};

struct cJobPostFilter;
struct cChainBaseA { virtual int AddRef(); virtual int Release(); };
struct cChainBaseB {
    virtual void b0();
    virtual void b1();
    int mRefCount;
    cChainBaseB() { mRefCount = 0; }
};
struct cFilterChainJob_s007b_b670 : cChainBaseA, cChainBaseB {
    cJobPostFilter** mFilterBegin;                   // +0x0c
    cJobPostFilter** mFilterEnd;                     // +0x10
    cJobPostFilter** mFilterCapacity;                // +0x14
    int m18, m1c;
    unsigned char mInitialized;                      // +0x20
    int m24, m28, m2c;
    DrvPtr mCallback;                                // +0x30
    cFilterChainJob_s007b_b670() {
        mFilterBegin = 0; mFilterEnd = 0; mFilterCapacity = 0;
        mInitialized = 0;
        m24 = 0; m28 = 0; m2c = 0; mCallback.mpObject = 0;
    }
    void AddFilter(cJobPostFilter* pFilter);         // 0x007b9750
};
struct ChainPtr {
    cFilterChainJob_s007b_b670* mpObject;
    ChainPtr(cFilterChainJob_s007b_b670* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~ChainPtr() { if (mpObject) mpObject->Release(); }
    cFilterChainJob_s007b_b670* operator->() const { return mpObject; }
};

struct cJobPostFilter {
    virtual int AddRef();                            // +0x00
    virtual int Release();                           // +0x04
    virtual void v2();
    virtual void Draw(int a0, int layer, void* ctx, int a3);   // +0x0c
    unsigned mRefCountV[2];                          // +0x04
    unsigned mMaterialId;                            // +0x0c
    RectID mSrcRectID;                               // +0x10
    unsigned mSrcRaster;                             // +0x18
    RectID mDestRectID;                              // +0x1c
    struct RectVec {                                 // eastl::vector<cRenderTargetRectID>, +0x24
        RectID* mpBegin;
        RectID* mpEnd;
        RectID* mpCapacity;
        void DoInsertValue(RectID* position, const RectID& value);   // 0x006ec390
        void push_back(const RectID& v) {
            RectID* p = mpEnd;
            if (p < mpCapacity) {
                mpEnd = p + 1;
                if (p) *p = v;
            } else {
                DoInsertValue(p, v);
            }
        }
    } mAdditionalRectIDs;
    unsigned pad30[2];
    void* mViewer;                                   // +0x38
    Vec4 mCustomParams[4];                           // +0x3c
    unsigned pad7c[1];
    bool mInitialized;                               // +0x80
    bool mDumpTexture;                               // +0x81
    bool mClearBeforeDraw;                           // +0x82
    bool mOverrideViewport;                          // +0x83
    int mView[4];                                    // +0x84
    int mQuadrant;                                   // +0x94
    Vec4 mClearColor;                                // +0x98
    bool mPreSetViewport;                            // +0xa8
    char padA9[0xe4 - 0xa9];

    cJobPostFilter();                                // 0x007b8550
    void Initialize(int flags);                      // 0x007b9420
    void InitBlur(int taps, const RectID& src, const RectID& dest, int flags);   // 0x007b9510
    void SetClearColor(Vec4 c) { mClearColor = c; mClearBeforeDraw = true; }     // 0x007b27a0
};
typedef struct FilterPtrT {
    cJobPostFilter* mpObject;
    FilterPtrT(cJobPostFilter* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~FilterPtrT() { if (mpObject) mpObject->Release(); }
    cJobPostFilter* operator->() const { return mpObject; }
} FilterPtr;

struct PostMsg {                                     // 0x2c bytes passed to IMgr::Post
    int kind;
    int a;
    unsigned char b;
    int c, d;
    unsigned id;
    void* data;
    int e, f, g, h;
    PostMsg() {
        a = 0; b = 1; c = 0; d = 0;
        e = 0; f = 0; g = 0; h = 0;
        kind = 1;
        data = 0;
        id = 0;
    }
};

struct IMgr {                                        // 0x0067dd50
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29();
    virtual void Post(void* sender, int a, void* msg);         // +0x78
};
IMgr* __cdecl GetMgr();                              // 0x0067dd50

struct IRtt {                                        // 0x0067dd40
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42();
    virtual void GetRectAC(RectID* out);             // +0xac
    virtual void s44(); virtual void s45(); virtual void s46();
    virtual void GetRectBC(RectID* out);             // +0xbc
    virtual void s48(); virtual void s49();
    virtual void GetRectC8(RectID* out);             // +0xc8
    virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55();
    virtual void GetRectE0(RectID* out, int index);  // +0xe0
};
IRtt* __cdecl GetRtt();                              // 0x0067dd40

struct cPropertyList {
    bool GetDescription(unsigned id);                // 0x006a25a0
};
extern cPropertyList* sAppProperties;                // 0x015fd918

struct cThumbnailManager_s007b_b670 {
    void __thiscall DilateSetup(int arg);            // 0x007bb670
};

void __thiscall cThumbnailManager_s007b_b670::DilateSetup(int arg)
{
    IMgr* mgr = GetMgr();
    IRtt* rtt = GetRtt();
    RectID sizeId;
    sizeId.mPageID = -1;
    sizeId.mAllocID = -1;
    RectID rectB;
    rectB.mPageID = -1;
    rectB.mAllocID = -1;
    rtt->GetRectAC(&sizeId);
    rtt->GetRectBC(&rectB);

    ChainPtr cs(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_b670());
    if (!cs->mInitialized) {
        cs->mInitialized = 1;
        cs->m28 = 0;
    }
    FilterPtr f0(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f1(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f2(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f3(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f4(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f5(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f6(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());

    RectID t;
    RectID pA, pB;
    pA.mPageID = -1; pA.mAllocID = -1;
    pB.mPageID = -1; pB.mAllocID = -1;
    GetRtt()->GetRectE0(&pA, 0);
    GetRtt()->GetRectE0(&pB, 1);
    f0->InitBlur(0xe7, sizeId, pA, 0);
    f0->mAdditionalRectIDs.push_back(sizeId);
    f0->mCustomParams[0].x = 1.0f;
    f0->mCustomParams[0].y = 1.0f;
    f0->mCustomParams[0].z = 1.0f;
    f0->mCustomParams[0].w = 1.0f;
    f0->mCustomParams[1].x = 1.0f;
    f0->mCustomParams[1].y = 1.0f;
    f0->mCustomParams[1].z = 1.0f;
    f0->mCustomParams[1].w = 0.0f;
    f1->InitBlur(0xd2, pA, pB, 0);
    f2->InitBlur(0xd2, pB, pA, 0);
    f3->InitBlur(0xd2, sizeId, pB, 0);
    f4->InitBlur(0xd2, pB, sizeId, 0);
    f5->InitBlur(0xcc, pA, rectB, 0);
    f5->SetClearColor(Vec4(0.0f, 0.0f, 0.0f, 0.0f));
    f5->mAdditionalRectIDs.push_back(sizeId);

    cPropertyList* props = sAppProperties;
    if (props->GetDescription(0x1a91189c)) {
        f6->Initialize(0);
        f6->mMaterialId = 0x28;
        f6->mSrcRectID = rectB;
        t.mPageID = -1;
        t.mAllocID = -1;
        GetRtt()->GetRectC8(&t);
        f6->mDestRectID = t;
        f6->mCustomParams[0].x = 1.0f;
        f6->mCustomParams[0].y = 1.0f;
        f6->mCustomParams[0].z = 1.0f;
        f6->mCustomParams[0].w = 1.0f;
        f6->mCustomParams[1].x = 0.0f;
        f6->mCustomParams[1].y = 1.0f;
        f6->mCustomParams[1].z = 1.0f;
        f6->mCustomParams[1].w = 0.0f;
        f6->mCustomParams[3].x = 0.0f;
        f6->mCustomParams[3].y = 0.0f;
        f6->mCustomParams[3].z = 0.0f;
        f6->mCustomParams[3].w = 0.0f;
    }
    cs->AddFilter(f0.mpObject);
    cs->AddFilter(f1.mpObject);
    cs->AddFilter(f2.mpObject);
    cs->AddFilter(f3.mpObject);
    cs->AddFilter(f4.mpObject);
    cs->AddFilter(f5.mpObject);
    if (props->GetDescription(0x1a91189c))
        cs->AddFilter(f6.mpObject);

    cs->m24 = 1;
    CbPtr cb(new ("Graphics", 0, 0, 0, 0) cChainCallback());
    ((cChainCallback*)cb.mpObject)->mField08 = arg;
    ((cChainCallback*)cb.mpObject)->mChain = cs.mpObject;
    cs->m2c = 0x5221305;
    cs->mCallback = cb.mpObject;
    if (cs->m24 == 0)
        cs->m24 = 0x14;
    cs->AddRef();
    PostMsg msg;
    mgr->Post(cs.mpObject, 0, &msg);
}

}

// @ 0x007bbde0
void cThumbnailManager_s007b_b670::HandleSomething(void* msg)
{
    int f8  = *(int*)((char*)msg + 8);
    int f10 = *(int*)((char*)msg + 0x10);
    int f18 = *(int*)((char*)msg + 0x18);
    int f20 = *(int*)((char*)msg + 0x20);
    int f28 = *(int*)((char*)msg + 0x28);
    int f30 = *(int*)((char*)msg + 0x30);

    if (f8 == f18 - 1) {
        if (f18 != 0) {
            Thumb** p = mThumbs;
            int n = f18;
            do {
                Thumb* t = *p;
                if (t->m_c4) {
                    ModelObj* o = t->m_a8;
                    if (o) { t->m_a8 = 0; o->v1(); }
                    t->m0c = 0;
                    t->m10 = 0;
                    t->m_c4 = 0;
                }
                ++p;
                --n;
            } while (n);
        }
        mFilterChain->Shutdown();
        ModelObj* m = mModel;
        if (m) {
            m->v0();                     // placeholder for vtable+0x16c call
            m = mModel;
            if (m) {
                mModel = 0;
                if (m->m40 <= 1)
                    m->v1();             // placeholder for vtable+0x170 call
                else
                    --m->m40;
            }
        }
        BehaviorMessage_s007b_b670* bm = new ("Graphics",0,0,0,0) BehaviorMessage_s007b_b670();
        if (bm) bm->v1();
        bm->m8  = f10;
        bm->m10 = f20;
        bm->m18 = f28;
        bm->m20 = f30;
        SP_MessageServer_s007b_b670()->Send(0x21d7528, bm, 0);
        if (bm) bm->v2();
    }
}

// @ 0x007bbf80
void cThumbnailManager_s007b_bf80::DilateStart(DilateReq* req)
{
    uint32_t a18 = req->f18;
    uint32_t b = req->f08;
    uint32_t a10 = req->f10;
    uint32_t d = req->f20;
    IMgr* mgr = GetMgr();
    IRtt* rtt = GetRtt();
    Key2 sizeId;
    sizeId.a = (uint32_t)-1;
    sizeId.b = (uint32_t)-1;
    rtt->GetRectB0(&sizeId);
    cPropertyList* appProps = sAppProperties_s007b_bf80;

    AutoRefCount<cContentValidationSummarizer> cs(new ("Graphics", 0, 0, 0, 0) cContentValidationSummarizer());
    if (!cs.mpObject->m20) {
        cs.mpObject->m20 = 1;
        cs.mpObject->m28 = 0;
    }
    AutoRefCount<cFilterChainJob_s007b_bf80> j1(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j2(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j3(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j4(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j5(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j6(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j7(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j8(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j9(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j10(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j11(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());
    AutoRefCount<cFilterChainJob_s007b_bf80> j12(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_bf80());

    Key2 pA, pB;
    pA.a = (uint32_t)-1; pA.b = (uint32_t)-1;
    pB.a = (uint32_t)-1; pB.b = (uint32_t)-1;
    GetRtt()->GetRectE0(&pA, 0);
    GetRtt()->GetRectE0(&pB, 1);
    j1.mpObject->Connect(0xe7, &pB, &pA, 0);
    j1.mpObject->v98 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
    j1.mpObject->b82 = 1;
    j1.mpObject->inputs.push_back(pB);
    j1.mpObject->f3c = 1.0f;
    j1.mpObject->f40 = 1.0f;
    j1.mpObject->f44 = 1.0f;
    j1.mpObject->f48 = 1.0f;
    j1.mpObject->f4c = 1.0f;
    j1.mpObject->f50 = 1.0f;
    j1.mpObject->f54 = 1.0f;
    float one = 1.0f;
    j1.mpObject->f58 = 0.0f;
    float zero = 0.0f;
    float half = 0.5f;

    AutoRefCount<cPropertyList> propList(0);
    IPropertyManager* pm = PropertyManager();
    propList.reset();
    if (pm->GetPropertyList(d, 0x40200100, &propList)) {
        one = PropGetFloat(propList.mpObject->GetProperty(0x26cabbf));
        zero = PropGetFloat(propList.mpObject->GetProperty(0x26dc91e));
        half = PropGetFloat(propList.mpObject->GetProperty(0x27c7387));
    }

    if (mFlag10bc) {
        j8.mpObject->Connect(0xdd, &pA, &pB, 0);
        j3.mpObject->Connect(0xd2, &pB, &pA, 0);
        j4.mpObject->Connect(0xd2, &pA, &pB, 0);
        j4.mpObject->v98 = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
        j4.mpObject->b82 = 1;
        j10.mpObject->Connect(0x65, &pB, &pA, 0);
        j10.mpObject->v98 = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
        j10.mpObject->b82 = 1;
        j10.mpObject->f3c = 1.0f;
        j10.mpObject->f40 = half;
        j10.mpObject->f44 = 0.0f;
        j10.mpObject->f48 = 0.0f;
        j11.mpObject->Connect(0x65, &pA, &sizeId, 0);
        j11.mpObject->v98 = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
        j11.mpObject->b82 = 1;
        {
            Key2 pC;
            pC.a = (uint32_t)-1; pC.b = (uint32_t)-1;
            rtt->GetRectAC(&pC);
            j11.mpObject->f3c = 1.0f;
            j11.mpObject->f40 = half;
            j11.mpObject->f44 = 0.0f;
            j11.mpObject->f48 = 0.0f;
            j2.mpObject->Connect(0xe7, &pC, &pA, 0);
            j2.mpObject->inputs.push_back(pC);
            j2.mpObject->f3c = 1.0f;
            j2.mpObject->f40 = 1.0f;
            j2.mpObject->f44 = 1.0f;
            j2.mpObject->f48 = 1.0f;
            j2.mpObject->f4c = 1.0f;
            j2.mpObject->f50 = 1.0f;
            j2.mpObject->f54 = 1.0f;
            j2.mpObject->f58 = 0.0f;
            j5.mpObject->Connect(0xd2, &pA, &pB, 0);
            j6.mpObject->Connect(0xd2, &pB, &pA, 0);
            j9.mpObject->Connect(0xcb, &sizeId, &pB, 0);
            j9.mpObject->b82 = 1;
            j9.mpObject->v98 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
            j9.mpObject->f3c = one;
            j9.mpObject->f40 = 1.0f;
            j9.mpObject->f44 = 1.0f;
            j9.mpObject->f48 = 1.0f;
            j9.mpObject->f6c = 0.0f;
            j9.mpObject->f70 = 0.0f;
            j9.mpObject->f74 = zero;
            j9.mpObject->f78 = 0.0f;
            j9.mpObject->inputs.push_back(pA);
            j7.mpObject->Connect(0x4f8e3f8e, &pB, (Key2*)&a18, 0);
            j7.mpObject->v98 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
            j7.mpObject->b82 = 1;
            j7.mpObject->inputs.push_back(pC);
        }
        if (appProps->GetDescription(0x1a91189c)) {
            Key2 pD;
            pD.a = (uint32_t)-1; pD.b = (uint32_t)-1;
            GetRtt()->GetRectC8(&pD);
            j12.mpObject->Init(0);
            j12.mpObject->f0c = 0x88549f64;
            j12.mpObject->f10 = a18;
            j12.mpObject->f14 = a10;
            j12.mpObject->f1c = pD.a;
            j12.mpObject->f20 = pD.b;
            j12.mpObject->f3c = 1.2f;
            j12.mpObject->f40 = 1.0f;
            j12.mpObject->f44 = 1.0f;
            j12.mpObject->f48 = 1.0f;
            j12.mpObject->f4c = 0.0f;
            j12.mpObject->f50 = 1.0f;
            j12.mpObject->f54 = 1.0f;
            j12.mpObject->f58 = 0.0f;
            j12.mpObject->f6c = 0.0f;
            j12.mpObject->f70 = 0.0f;
            j12.mpObject->f74 = 0.0f;
            j12.mpObject->f78 = 0.0f;
        }
    } else {
        j8.mpObject->Connect(0xdd, &pA, &pB, 0);
        j3.mpObject->Connect(0xd2, &pB, &pA, 0);
        j4.mpObject->Connect(0xd2, &pA, &pB, 0);
        j10.mpObject->Connect(0x65, &pB, &pA, 0);
        j11.mpObject->Connect(0x65, &pA, (Key2*)&a18, 0);
        j10.mpObject->v98 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
        j10.mpObject->b82 = 1;
        j10.mpObject->f3c = 1.0f;
        j10.mpObject->f40 = half;
        j10.mpObject->f44 = half;
        j10.mpObject->f48 = 0.0f;
    }

    cs.mpObject->AddJob(j1.mpObject);
    cs.mpObject->AddJob(j8.mpObject);
    if (mFlag10bc) {
        cs.mpObject->AddJob(j3.mpObject);
        cs.mpObject->AddJob(j4.mpObject);
        cs.mpObject->AddJob(j10.mpObject);
        cs.mpObject->AddJob(j11.mpObject);
        cs.mpObject->AddJob(j2.mpObject);
        cs.mpObject->AddJob(j5.mpObject);
        cs.mpObject->AddJob(j6.mpObject);
        cs.mpObject->AddJob(j9.mpObject);
        cs.mpObject->AddJob(j7.mpObject);
        if (appProps->GetDescription(0x1a91189c))
            cs.mpObject->AddJob(j12.mpObject);
    } else {
        cs.mpObject->AddJob(j3.mpObject);
        cs.mpObject->AddJob(j4.mpObject);
        cs.mpObject->AddJob(j10.mpObject);
        cs.mpObject->AddJob(j11.mpObject);
    }

    BehaviorMessage_s007b_bf80* bm = new ("Graphics", 0, 0, 0, 0) BehaviorMessage_s007b_bf80();
    if (bm)
        bm->AddRef();
    bm->f08 = b;
    bm->f10 = (uint32_t)cs.mpObject;
    PostMsg msg(bm);
    mgr->Post(cs.mpObject, 0, &msg);
}

// @ 0x007bced0
void cThumbnailManager_s007b_ced0::DilateWithoutAOStart(DilateReq_s007b_ced0* req)
{
    unsigned b = req->f08;
    RectID rect;
    rect.mAllocID = req->f10;
    rect.mPageID = req->f18;
    IMgr_s007b_ced0* mgr = GetMgr_s007b_ced0();
    RectID sizeId;
    sizeId.mPageID = -1;
    sizeId.mAllocID = -1;
    GetRtt_s007b_ced0()->GetRectAC(&sizeId);

    EA::AutoRefCount_s007b_ced0<cFilterChainJob_s007b_ced0> cs(new ("Graphics", 0, 0, 0, 0) cFilterChainJob_s007b_ced0());
    if (!cs.mpObject->mInitialized) {
        cs.mpObject->mInitialized = 1;
        cs.mpObject->m28 = 0;
    }
    FilterPtr f0(new ("Graphics", 0, 0, 0, 0) cJobPostFilter_s007b_ced0());
    FilterPtr f1(new ("Graphics", 0, 0, 0, 0) cJobPostFilter_s007b_ced0());
    FilterPtr f2(new ("Graphics", 0, 0, 0, 0) cJobPostFilter_s007b_ced0());
    FilterPtr f3(new ("Graphics", 0, 0, 0, 0) cJobPostFilter_s007b_ced0());
    FilterPtr f4(new ("Graphics", 0, 0, 0, 0) cJobPostFilter_s007b_ced0());
    FilterPtr f5(new ("Graphics", 0, 0, 0, 0) cJobPostFilter_s007b_ced0());

    RectID pA, pB;
    pA.mPageID = -1; pA.mAllocID = -1;
    pB.mPageID = -1; pB.mAllocID = -1;
    GetRtt_s007b_ced0()->GetRectE0(&pA, 0);
    GetRtt_s007b_ced0()->GetRectE0(&pB, 1);
    f0.mpObject->InitBlur(0xe7, sizeId, pA, 0);
    f0.mpObject->SetClearColor(Vec4_s007b_ced0(0.0f, 0.0f, 0.0f, 0.0f));
    f0.mpObject->mAdditionalRectIDs.push_back(sizeId);
    f0.mpObject->mCustomParams[0].x = 1.0f;
    f0.mpObject->mCustomParams[0].y = 1.0f;
    f0.mpObject->mCustomParams[0].z = 1.0f;
    f0.mpObject->mCustomParams[0].w = 1.0f;
    f0.mpObject->mCustomParams[1].x = 1.0f;
    f0.mpObject->mCustomParams[1].y = 1.0f;
    f0.mpObject->mCustomParams[1].z = 1.0f;
    f0.mpObject->mCustomParams[1].w = 0.0f;
    f1.mpObject->InitBlur(0xd2, pA, pB, 0);
    f2.mpObject->InitBlur(0xd2, pB, pA, 0);
    f3.mpObject->InitBlur(0xd2, pA, pB, 0);
    f4.mpObject->InitBlur(0xd2, pB, pA, 0);
    f5.mpObject->InitBlur(0xcc, pA, rect, 0);
    f5.mpObject->mAdditionalRectIDs.push_back(sizeId);
    cs.mpObject->AddFilter(f0.mpObject);
    cs.mpObject->AddFilter(f1.mpObject);
    cs.mpObject->AddFilter(f2.mpObject);
    cs.mpObject->AddFilter(f3.mpObject);
    cs.mpObject->AddFilter(f4.mpObject);
    cs.mpObject->AddFilter(f5.mpObject);

    BehaviorMessage_s007b_ced0* bm = new ("Graphics", 0, 0, 0, 0) BehaviorMessage_s007b_ced0();
    if (bm)
        bm->AddRef();
    bm->f08 = b;
    bm->f10 = (unsigned)cs.mpObject;
    PostMsg_s007b_ced0 msg(bm);
    mgr->Post(cs.mpObject, 0, &msg);
}

// @ 0x007bd4c0
void cThumbnailManager_s007b_ced0::DilateWithoutAODone(DilateMsg* msg)
{
    int u = msg->m8;
    msg->mJob->Shutdown();
    mCurrentlyCapturingAO = false;
    SP_MessageServer_s007b_ced0()->Send(u, 0, 0, 0);
}

// @ 0x007bd500
void __stdcall PaletteJobInfo_Shutdown(cPaletteJobInfo* pInfo)
{
    cFilterChainJob_s007b_ced0* pcVar1 = pInfo->mPostProcessLayer.mpObject;
    int uVar2 = pInfo->mRectId0;
    pcVar1->Shutdown();
    pcVar1->Release();
    SP_MessageServer_s007b_ced0()->Send(uVar2, 0, 0, 0);
}

// @ 0x007bd540
void cPaletteThumbnailJob::Shutdown()
{
    if (mInitialized) {
        if (mTempPixelData != 0 && mInfo.mpObject->mUseImageSpaceFraming) {
            EASTL_deallocate(mTempPixelData);
            mTempPixelData = 0;
        }
        cPaletteJobInfo* pcVar1 = mInfo.mpObject;
        if (pcVar1 != 0) {
            if (pcVar1->mPostProcessLayer.mpObject != 0) {
                pcVar1->mPostProcessLayer.mpObject->Shutdown();
                pcVar1->mPostProcessLayer = 0;
            }
            mInfo = 0;
        }
        if (mViewer != 0) {
            mViewer->FUN_007c3ba0();
            cViewer_s007b_ced0* pcVar3 = mViewer;
            if (pcVar3 != 0) {
                pcVar3->FUN_007c4000();
                EASTL_deallocate(pcVar3);
            }
            mViewer = 0;
        }
        mInitialized = false;
    }
}

// @ 0x007bd5d0
void cEditorJobInfo::Shutdown()
{
    if (mPostProcessLayer.mpObject != 0) {
        mPostProcessLayer.mpObject->Shutdown();
        mPostProcessLayer = 0;
    }
    if (mThumbnailTex.mpObject != 0) {
        mThumbnailTex = 0;
    }
}

// @ 0x007bd640
void cEditorThumbnailJob::Shutdown()
{
    if (mInitialized) {
        if (mTempPixelData != 0) {
            EASTL_deallocate(mTempPixelData);
            mTempPixelData = 0;
        }
        if (mInfo.mpObject != 0) {
            mInfo.mpObject->Shutdown();
            mInfo = 0;
        }
        if (mViewer != 0) {
            mViewer->FUN_007c3ba0();
            cViewer_s007b_ced0* pcVar2 = mViewer;
            if (pcVar2 != 0) {
                pcVar2->FUN_007c4000();
                EASTL_deallocate(pcVar2);
            }
            mViewer = 0;
        }
        mInitialized = false;
    }
}

// @ 0x007bd6b0
void cCSAThumbnailJob_s007b_ced0::Shutdown()
{
    if (mInitialized) {
        cCSAJobInfo* pcVar1 = mInfo.mpObject;
        if (pcVar1 != 0) {
            if (pcVar1->mPostProcessLayer.mpObject != 0) {
                pcVar1->mPostProcessLayer.mpObject->Shutdown();
                pcVar1->mPostProcessLayer = 0;
            }
            mInfo = 0;
        }
        if (mViewer != 0) {
            mViewer->FUN_007c3ba0();
            cViewer_s007b_ced0* pcVar3 = mViewer;
            if (pcVar3 != 0) {
                pcVar3->FUN_007c4000();
                EASTL_deallocate(pcVar3);
            }
            mViewer = 0;
        }
        if (mFilterViewer != 0) {
            mFilterViewer->FUN_007c3ba0();
            cViewer_s007b_ced0* pcVar3 = mFilterViewer;
            if (pcVar3 != 0) {
                pcVar3->FUN_007c4000();
                EASTL_deallocate(pcVar3);
            }
            mFilterViewer = 0;
        }
        mInitialized = false;
    }
}

// @ 0x007bd750
__forceinline int RoundToInt(float f)
{ __asm cvtss2si eax, f }

// @ 0x007bdd70
void cGameThumbnailJob::Shutdown()
{
    if (mInitialized) {
        cGameThumbJobInfo* pcVar1 = mInfo.mpObject;
        if (pcVar1 != 0) {
            if (pcVar1->mPostProcessLayer.mpObject != 0) {
                pcVar1->mPostProcessLayer.mpObject->Shutdown();
                pcVar1->mPostProcessLayer = 0;
            }
            mInfo = 0;
        }
        if (mViewer != 0) {
            mViewer->FUN_007c3ba0();
            cViewer_s007b_ced0* pcVar3 = mViewer;
            if (pcVar3 != 0) {
                pcVar3->FUN_007c4000();
                EASTL_deallocate(pcVar3);
            }
            mViewer = 0;
        }
        mInitialized = false;
    }
}

// @ 0x007bdde0
void __fastcall FUN_007bdde0(void* p)
{
    if (*(char*)((char*)p + 0x78) != 0) {
        if (*(void**)((char*)p + 0x60) != 0)
            (*(cFilterChainJob_s007b_ced0**)((char*)p + 0x60))->Shutdown();
        Obj90* q = *(Obj90**)((char*)p + 0x90);
        if (q != 0) {
            *(void**)((char*)p + 0x90) = 0;
            q->v2();
        }
        *(char*)((char*)p + 0x78) = 0;
    }
}

// @ 0x007be430
void cThumbnailManager_s007b_de20::CapturePaletteThumbnail(cCaptureCtx* ctx, cPaletteRequest* req)
{
    bool hasDesc = g_sAppProperties_s007b_de20->GetDescription(0x5cb6033);
    SetupThumbnailRTTs(req->m08, 1);

    RefPtrL<cThumbEffect> effect(new ("Graphics", 0, 0, 0, 0) cThumbEffect);
    if (!effect->mFlag)
    {
        effect->mFlag = true;
        effect->m28 = 0;
    }
    InitPostProcessEffect(req->m40, effect, 1, !hasDesc, Vec3_s007b_de20(g_fVecX, g_fVecY, 0.0f));

    RefPtrL<cThumbJobA> job(new ("Graphics", 0, 0, 0, 0) cThumbJobA);
    cThumbTarget* tgtRaw = new ("Graphics", 0, 0, 0, 0) cThumbTarget;
    RefPtrL<cThumbTarget> tgt(tgtRaw);

    cMessageHandle h = { -1, -1 };
    GetManager1()->GetHandle(&h.a);
    tgt->mHandleA = h.a;
    tgt->mHandleB = h.b;
    if (tgt->mEffect != effect.p)
    {
        effect->AddRef();
        cThumbEffect* old = tgt->mEffect;
        tgt->mEffect = effect.p;
        if (old)
            old->Release();
    }
    tgt->m14 = req->m0c;
    tgt->m20 = req->m18;
    tgt->m24 = req->m14;
    tgt->m18 = req->m08;
    tgt->m1c = req->m08;
    tgt->m28 = hasDesc;
    tgt->m2c = req->m40;

    cViewer_s007b_de20* world = new ("Graphics", 0, 0, 0, 0) cViewer_s007b_de20;
    world->Init(0);

    if (req->mMode == 1)
    {
        effect->CaptureRect(&req->mBoxBegin, world, req->m0c, &req->m1c, req->m28, 0.0f);
    }
    else if (req->mMode == 0)
    {
        BBox3 box;
        box.mn.x = box.mn.y = box.mn.z = g_fFltMax;
        box.mx.x = box.mx.y = box.mx.z = g_fNegFltMax;
        unsigned i = 0;
        const BBox3* src = req->mBoxBegin;
        for (; i < (unsigned)(req->mBoxEnd - req->mBoxBegin); i++, src++)
        {
            if (box.mn.x > box.mx.x)
            {
                box = *src;
            }
            else
            {
                if (src->mn.x < box.mn.x) box.mn.x = src->mn.x;
                if (src->mx.x > box.mx.x) box.mx.x = src->mx.x;
                if (src->mn.y < box.mn.y) box.mn.y = src->mn.y;
                if (src->mx.y > box.mx.y) box.mx.y = src->mx.y;
                if (src->mn.z < box.mn.z) box.mn.z = src->mn.z;
                if (src->mx.z > box.mx.z) box.mx.z = src->mx.z;
            }
        }
        effect->CaptureBox(&box.mn, world, req->m0c, req->m48, (int)req->m40, 1.0f);
    }

    job->Run(ctx, world, tgt);
    world->Shutdown();
    if (world)
        delete world;

    RefPtrL<cThumbDoneMsg> msg(new ("Graphics", 0, 0, 0, 0) cThumbDoneMsg);
    msg->m08 = req->m10;
    msg->m10 = 0;
    msg->mJob = job.p;

    cThumbJobMsgEvent ev;
    ev.a = 1;
    ev.b = 4;
    ev.c = false;
    ev.d = 0;
    ev.e = 0;
    ev.id = 0x1c913db;
    ev.data = msg.p;
    ev.f = ev.g = ev.h = ev.i = 0;
    void* handle = job->Queue(0, &ev);
    GetManager2()->Dispatch(handle);
}

// @ 0x007bea00
void cThumbnailManager_s007b_de20::CapturePaletteImageThumbnail(cCaptureCtx* ctx, cPaletteImageRequest* req)
{
    SetupThumbnailRTTs(req->m08, 1);

    RefPtrL<cThumbEffect> effect(new ("Graphics", 0, 0, 0, 0) cThumbEffect);
    if (!effect->mFlag)
    {
        effect->mFlag = true;
        effect->m28 = 0;
    }
    InitPostProcessEffect(req->m3c, effect, 1, false, Vec3_s007b_de20(req->m40, req->m44, req->m48));

    RefPtrL<cThumbJobB> job(new ("Graphics", 0, 0, 0, 0) cThumbJobB);
    RefPtrL<cThumbTargetB> tgt(new ("Graphics", 0, 0, 0, 0) cThumbTargetB);

    cMessageHandle h = { -1, -1 };
    GetManager1()->GetHandle(&h.a);
    tgt->mHandleA = h.a;
    tgt->mHandleB = h.b;
    if (tgt->mEffect != effect.p)
    {
        effect->AddRef();
        cThumbEffect* old = tgt->mEffect;
        tgt->mEffect = effect.p;
        if (old)
            old->Release();
    }
    tgt->m14 = req->m08;
    tgt->m18 = req->m08;
    tgt->mImage.Set(req->m14);
    tgt->m24 = req->m50;
    tgt->m20 = req->m4c;
    tgt->m28 = req->m18;
    tgt->m2c = req->m1c;
    tgt->m30 = req->m20;

    cViewer_s007b_de20* world = new ("Graphics", 0, 0, 0, 0) cViewer_s007b_de20;
    world->Init(0);
    effect->CaptureRect(&req->m28, world, req->m0c, &req->m18, req->m24, 0.0f);
    job->Run(ctx, world, (cThumbTarget*)tgt.p);
    world->Shutdown();
    if (world)
        delete world;

    RefPtrL<cThumbDoneMsg> msg(new ("Graphics", 0, 0, 0, 0) cThumbDoneMsg);
    msg->m08 = req->m10;
    msg->m10 = 1;
    msg->mJob = job.p;

    cThumbJobMsgEvent ev;
    ev.a = 1;
    ev.b = 4;
    ev.c = false;
    ev.d = 0;
    ev.e = 0;
    ev.id = 0x1c913db;
    ev.data = msg.p;
    ev.f = ev.g = ev.h = ev.i = 0;
    void* handle = job->Queue(0, &ev);
    GetManager2()->Dispatch(handle);
}

// @ 0x007bedb0
void FUN_007bedb0(void* a, void* b, void* c)
{ (void)a; (void)b; (void)c; }

// @ 0x007bf300
void FUN_007bf300(void* a)
{ (void)a; }

// @ 0x007bf610
void cThumbnailManager_s007b_edb0::ThumbnailDone(DoneMsg_s007b_edb0* msg)
{
    int u = msg->m8;
    switch (msg->m10) {
    case 2: ((cCSAThumbnailJob_s007b_edb0*)msg->mJob)->Shutdown(); break;
    case 1: ((cEditorThumbnailJob_s007b_edb0*)msg->mJob)->Shutdown(); break;
    case 0: ((cPaletteThumbnailJob_s007b_edb0*)msg->mJob)->Shutdown(); break;
    case 3: ((cGameThumbnailJob_s007b_edb0*)msg->mJob)->Shutdown();
    }
    SP_MessageServer_s007b_edb0()->Call14(u, 0, 0);
    RTTFree* r = (RTTFree*)FUN_0067dda0_s007b_edb0();
    if (mThumbRectID.IsValid())
        r->Free(mThumbRectID.mPageID, mThumbRectID.mAllocID);
    if (mBlurThumbRectID1.IsValid())
        r->Free(mBlurThumbRectID1.mPageID, mBlurThumbRectID1.mAllocID);
    if (mBlurThumbRectID2.IsValid())
        r->Free(mBlurThumbRectID2.mPageID, mBlurThumbRectID2.mAllocID);
    if (mTempThumbnailBuffer.IsValid())
        r->Free(mTempThumbnailBuffer.mPageID, mTempThumbnailBuffer.mAllocID);
    if (mCSALargeRectID.IsValid())
        r->Free(mCSALargeRectID.mPageID, mCSALargeRectID.mAllocID);
    if (mCSASmallRectID.IsValid())
        r->Free(mCSASmallRectID.mPageID, mCSASmallRectID.mAllocID);
    if (mCSAAntiAliasRectID.IsValid())
        r->Free(mCSAAntiAliasRectID.mPageID, mCSAAntiAliasRectID.mAllocID);
}

// @ 0x007bf9c0
void SetterBlock::Set(void* a1, int a2, int a3, int a4, Pair* a5, Pair* a6, int a7, char a8)
{
    if (m_c4 == 0) {
        m_c0 = 0;
        RefLike* old = m_a8;
        if (a1 != old) {
            if (a1) ((RefLike*)a1)->AddRef();
            m_a8 = (RefLike*)a1;
            if (old) old->Release();
        }
        m0c = (void*)a3;
        m10 = (void*)a4;
        m94.x = a5->x; m94.y = a5->y;
        m9c.x = a6->x; m9c.y = a6->y;
        m_c0 = a7;
        m_c4 = 1;
        m_c8 = 0.0f; m_cc = 0.0f; m_d0 = 0.0f; m_d4 = 0.0f;
        m_ac = (void*)a2;
        m_d8 = (unsigned char)a8;
    }
}

// @ 0x007bfeb0
void __stdcall FUN_007bfeb0(int a, int b, int c, int d, int e)
{ (void)a; (void)b; (void)c; (void)d; (void)e; }

// @ 0x007bfee0
namespace AO {
bool cThumbnailManagerAO::CaptureAmbientOcclusionB(RectID* shadowRect, IModelWorld_s007b_faa0* world, MeshVector* meshes, int userData, uint32_t propListID, bool useMeshes)
{
    if (mCurrentlyCapturingAO)
        return false;
    mCurrentlyCapturingAO = true;
    mMultiplyDiffuseWithAO = true;

    RenderTargetManager()->SetFlag(0);
    RenderTargetManager()->SetFlag(1);
    mAmbOccSplatterViewer->SetRenderMode(9, 0);
    ILayerManager* layerManager = LayerManager();

    RectID shadowMapRect;
    shadowMapRect.mPageID = -1;
    shadowMapRect.mAllocID = -1;
    RenderTargetManager()->SelectRect(&shadowMapRect);

    Vector3_s007b_faa0 center;
    float radius = 0.0f;
    if (useMeshes)
        FUN_007b5c80(meshes, &center, &radius);
    else
        FUN_007b87f0(world, &center, &radius);

    PropertyListPtr propList;
    int mode = 0;
    int flipCounter = 0;
    int flipPeriod = 4;
    int passCount = 0x40;

    IPropManager* propManager = PropertyManager_s007b_faa0();
    propList = 0;
    if (propManager->GetPropertyList(propListID, 0x40200100, propList)) {
        if (propList->HasProperty(0x4ee8a87)) propList->GetProperty(0x4ee8a87);
        if (propList->HasProperty(0x4efaf18)) mode = *propList->GetProperty(0x4efaf18)->GetValueInt();
        if (propList->HasProperty(0x4efbdc8)) propList->GetProperty(0x4efbdc8);
        if (propList->HasProperty(0x4efd359)) flipPeriod = *propList->GetProperty(0x4efd359)->GetValueInt();
        if (propList->HasProperty(0x5b99de4)) passCount = *propList->GetProperty(0x5b99de4)->GetValueInt();
    }

    mAmbOccGatherViewer->SetRenderMode(0, 0);
    FilterPtr_s007b_faa0 filter(new("Graphics", 0, 0, 0, 0) cJobPostFilter_s007b_faa0());
    RectID splatRect;
    splatRect.mPageID = -1;
    splatRect.mAllocID = -1;
    RenderTargetManager()->FreeRect(&splatRect, false);
    RenderTargetManager()->FreeRect(&mAOGatherRectID, true);

    filter->Init(0x2d, &splatRect, &mAOGatherRectID, 0);
    const float weight = 1.0f / (float)passCount;
    filter->mCustomParams[3] = 1.0f;
    filter->mCustomParams[2] = weight;
    filter->mCustomParams[0] = weight;
    filter->mCustomParams[1] = weight;
    filter->mCustomParams[4] = 0.0f;
    filter->mCustomParams[5] = 1.0f;
    filter->mCustomParams[6] = 1.0f;
    filter->mCustomParams[7] = 0.0f;
    mAOPostProcessLayer->Start();
    mAOPostProcessLayer->AddFilter(filter.mpObject);

    const float farPlane = radius * 5.0f;
    for (int i = 0; i < passCount; i++) {
        const Vector3_s007b_faa0 dir = kAODirections[i];
        float z = dir.z;
        if (mode == 1) {
            if (dir.z < 0.0f && ++flipCounter == flipPeriod) {
                z = fabsf(dir.z);
                flipCounter = 0;
            }
        } else if (mode == 2) {
            if (dir.z < 0.0f && ++flipCounter == flipPeriod) {
                z = -fabsf(dir.z);
                flipCounter = 0;
            }
        }

        cViewer_s007b_faa0* viewer = mAmbOccShadowViewers[i];
        const Vector3_s007b_faa0 view(dir.x, dir.y, z);
        viewer->SetViewWindow(radius, radius);
        viewer->SetNearPlane(0.1f);
        viewer->SetFarPlane(farPlane);

        const Vector3_s007b_faa0 ortho = OrthogonalVector(view);
        const float invUp = InvLength(ortho.x, ortho.y, ortho.z);
        const Vector3_s007b_faa0 up(ortho.x * invUp, invUp * ortho.y, invUp * ortho.z);
        const Vector3_s007b_faa0 side(view.z * up.y - view.y * up.z,
                           up.z * view.x - view.z * up.x,
                           view.y * up.x - up.y * view.x);
        const float invSide = InvLength(side.x, side.y, side.z);

        CameraMatrix camera;
        camera.mUp.x = up.x;
        camera.mUp.y = up.y;
        camera.mUp.z = up.z;
        camera.mRight.x = invSide * side.x;
        camera.mRight.y = invSide * side.y;
        camera.mRight.z = invSide * side.z;
        camera.mBack.x = -view.x;
        camera.mBack.y = -view.y;
        camera.mBack.z = -view.z;
        camera.mPosition.x = dir.x * radius + center.x;
        camera.mPosition.y = dir.y * radius + center.y;
        camera.mPosition.z = z * radius + center.z;
        viewer->SetCameraTransform(&camera);

        viewer->SetRenderMode(2, 0);
        Vector4_s007b_faa0 clearColor;
        clearColor.x = 1.0f;
        clearColor.y = 0.0f;
        clearColor.z = 0.0f;
        clearColor.w = 0.0f;
        viewer->SetClearColor(&clearColor);

        cAOPassMessage* msg = new("Graphics", 0, 0, 0, 0) cAOPassMessage();
        LayerInfo info;
        info.mpDoneMessage = msg;
        msg->mPassIndex = i;
        msg->mUserData = userData;
        msg->mPassCount = passCount;
        msg->mGatherAllocID = shadowRect->mAllocID;
        msg->mGatherPageID = shadowRect->mPageID;
        msg->mPropListID = propListID;
        info.mFlags = 1;
        info.mField04 = 0;
        info.mbField08 = false;
        info.mField0C = 0;
        info.mField10 = 0;
        info.mDoneMessageID = 0x212c1ee;
        info.mField1C = 0;
        info.mField20 = 0;
        info.mField24 = 0;
        info.mField28 = 0;

        mAmbOccRenderJob[i]->Init(world, *meshes, viewer, mAmbOccSplatterViewer,
                                  &shadowMapRect, &splatRect, i, useMeshes);
        layerManager->AddLayer(mAmbOccRenderJob[i]->GetLayer(0, &info));
    }
    return true;
}
}  // namespace AO

// @ 0x007c0780
namespace AO {
bool cThumbnailManagerAO_s007c_0780::CaptureAmbientOcclusion(uint32_t instanceID, uint32_t groupID, const BoundingBox& bbox, int userData, uint32_t propListID, int target)
{
    if (mCurrentlyCapturingAO)
        return false;
    mCurrentlyCapturingAO = true;

    RenderTargetManager()->SetTarget(target);
    mSkinModel = mAOModelWorld->CreateModel(instanceID, groupID, 0);
    mMultiplyDiffuseWithAO = false;

    RectID shadowRect;
    shadowRect.mPageID = -1;
    shadowRect.mAllocID = -1;
    RenderTargetManager()->AllocRect(&shadowRect);
    RenderTargetManager()->SetFlag(0);
    RenderTargetManager()->SetFlag(1);
    mAmbOccSplatterViewer->SetRenderMode(9, 1);
    ILayerManager* layerManager = LayerManager();

    const Vector3_s007c_0780 center((bbox.mMax.x + bbox.mMin.x) * 0.5f,
                         (bbox.mMax.y + bbox.mMin.y) * 0.5f,
                         (bbox.mMax.z + bbox.mMin.z) * 0.5f);
    const float dx = bbox.mMax.x - bbox.mMin.x;
    const float dy = bbox.mMax.y - bbox.mMin.y;
    const float dz = bbox.mMax.z - bbox.mMin.z;
    const float radius = Length(dx, dy, dz) * 0.5f + 1.0f;

    PropertyListPtr_s007c_0780 propList;
    float scale = 1.0f;
    int mode = 0;
    float heightOffset = 0.0f;
    int flipCounter = 0;
    int flipPeriod = 4;
    int passCount = 0x40;

    IPropManager_s007c_0780* propManager = PropertyManager_s007c_0780();
    propList = 0;
    if (propManager->GetPropertyList(propListID, 0x40200100, propList)) {
        GetPropFloat(propList.mpObject, 0x4ee8a87, scale);
        GetPropInt(propList.mpObject, 0x4efaf18, mode);
        GetPropFloat(propList.mpObject, 0x4efbdc8, heightOffset);
        GetPropInt(propList.mpObject, 0x4efd359, flipPeriod);
        GetPropInt(propList.mpObject, 0x5b99de4, passCount);
    }
    const float viewSize = scale * radius;

    mAmbOccGatherViewer->SetRenderMode(0, 0);
    RectID splatRect;
    splatRect.mPageID = -1;
    splatRect.mAllocID = -1;
    RenderTargetManager()->FreeRect(&splatRect, false);
    RenderTargetManager()->FreeRect(&mAOGatherRectID, true);

    FilterPtr_s007c_0780 filter(new("Graphics", 0, 0, 0, 0) cJobPostFilter_s007c_0780());
    filter->Init(0x2d, &splatRect, &mAOGatherRectID, 0);
    const float weight = 1.0f / (float)passCount;
    filter->mCustomParams[3] = 1.0f;
    filter->mCustomParams[2] = weight;
    filter->mCustomParams[0] = weight;
    filter->mCustomParams[1] = weight;
    filter->mCustomParams[4] = 0.0f;
    filter->mCustomParams[5] = 1.0f;
    filter->mCustomParams[6] = 1.0f;
    filter->mCustomParams[7] = 0.0f;
    mAOPostProcessLayer->Start();
    mAOPostProcessLayer->AddFilter(filter.mpObject);

    for (int i = 0; i < passCount; i++) {
        const Vector3_s007c_0780 dir = kAODirections_s007c_0780[i];
        float z = dir.z;
        if (mode == 1) {
            if (dir.z < 0.0f && ++flipCounter == flipPeriod) {
                z = fabsf(dir.z);
                flipCounter = 0;
            }
        } else if (mode == 2) {
            if (dir.z < 0.0f && ++flipCounter == flipPeriod) {
                z = -fabsf(dir.z);
                flipCounter = 0;
            }
        }

        cViewer_s007c_0780* viewer = mAmbOccShadowViewers[i];
        const Vector3_s007c_0780 view(dir.x, dir.y, z);
        viewer->SetViewWindow(viewSize, viewSize);
        viewer->SetNearPlane(0.1f);
        viewer->SetFarPlane(radius * 2.0f);

        const Vector3_s007c_0780 ortho = OrthogonalVector(view);
        const float invUp = InvLength_s007c_0780(ortho.x, ortho.y, ortho.z);
        const Vector3_s007c_0780 up(ortho.x * invUp, invUp * ortho.y, invUp * ortho.z);
        const Vector3_s007c_0780 side(view.z * up.y - view.y * up.z,
                           up.z * view.x - view.z * up.x,
                           view.y * up.x - up.y * view.x);
        const float invSide = InvLength_s007c_0780(side.x, side.y, side.z);

        CameraMatrix_s007c_0780 camera;
        camera.mUp.x = up.x;
        camera.mUp.y = up.y;
        camera.mUp.z = up.z;
        camera.mRight.x = invSide * side.x;
        camera.mRight.y = invSide * side.y;
        camera.mRight.z = invSide * side.z;
        camera.mBack.x = -view.x;
        camera.mBack.y = -view.y;
        camera.mBack.z = -view.z;
        camera.mPosition.x = dir.x * radius + center.x;
        camera.mPosition.y = dir.y * radius + center.y;
        camera.mPosition.z = z * radius + center.z + heightOffset;
        viewer->SetCameraTransform(&camera);

        RectID shadowMapRect;
        shadowMapRect.mPageID = -1;
        shadowMapRect.mAllocID = -1;
        RenderTargetManager()->SelectRect(&shadowMapRect);
        viewer->SetRenderMode(2, 0);
        Vector4_s007c_0780 clearColor;
        clearColor.x = 0.0f;
        clearColor.y = 0.0f;
        clearColor.z = 0.0f;
        clearColor.w = 0.0f;
        viewer->SetClearColor(&clearColor);

        cAOPassMessage* msg = new("Graphics", 0, 0, 0, 0) cAOPassMessage();
        LayerInfo info;
        info.mpDoneMessage = msg;
        msg->mPassIndex = i;
        msg->mUserData = userData;
        msg->mPassCount = passCount;
        msg->mGatherAllocID = shadowRect.mAllocID;
        msg->mGatherPageID = shadowRect.mPageID;
        msg->mPropListID = propListID;
        info.mFlags = 1;
        info.mField04 = 0;
        info.mbField08 = false;
        info.mField0C = 0;
        info.mField10 = 0;
        info.mDoneMessageID = 0x212c1ee;
        info.mField1C = 0;
        info.mField20 = 0;
        info.mField24 = 0;
        info.mField28 = 0;
        MeshVector meshes;

        mAmbOccRenderJob[i]->Init(mAOModelWorld, meshes, viewer, mAmbOccSplatterViewer,
                                  &shadowMapRect, &splatRect, i, 0);
        layerManager->AddLayer(mAmbOccRenderJob[i]->GetLayer(0, &info));
    }
    return true;
}
}  // namespace AO

// @ 0x007c1170
bool IHandlerRC::HandleMessage(unsigned int msgId, void* arg)
{
    switch (msgId) {
    case 0x1c913db: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->ThumbnailDone((DoneMsg*)arg); return true;
    case 0x1c91270: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->FUN_007bf720(arg); return true;
    case 0x212c1ee: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->FUN_007bbde0(arg); return true;
    case 0x21d7528: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->DilateStart(arg); return true;
    case 0x21d752f: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->DilateWithoutAODone(arg); return true;
    case 0x31e09b4: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->FUN_007bced0(arg); return true;
    case 0x5221305: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->PaletteJobInfo_Shutdown(arg); return true;
    case 0x50b834d: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->FUN_007b29a0(); return true;
    case 0x5fadac4: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->FUN_007b2970(arg); return true;
    case 0x5fc2c38: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->FUN_007b77a0(arg); return true;
    case 0x7b240a0: ((cThumbnailManager_s007c_0780*)((char*)this - 4))->FUN_007b77a0(arg); return true;
    }
    return false;
}

// @ 0x007c13f0
void FUN_007c13f0(void* a)
{ (void)a; }

// @ 0x007c1b70
void FUN_007c1b70(void* a)
{ (void)a; }

// @ 0x007c1c10
namespace SPL {
void cThumbnailManagerSplat::SetupSplat(int a1, const RectID_s007c_1c10* a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, const RectID_s007c_1c10* a10, const RectID_s007c_1c10* a11, int a12)
{
    const bool haveRect2 = a11->mAllocID != -1;
    const bool haveRect1 = a10->mAllocID != -1;
    RectID_s007c_1c10 tmp;

    RenderTargetManager()->SetFlag(0);
    RenderTargetManager()->SetFlag(1);
    IScene* scene = App()->GetScene();
    scene->SetMode(0);

    Xform xf;
    scene->GetTransform()->GetXform(&xf);
    mSplatterViewer->SetBasis(&xf);
    mSplatterViewer->SetRenderMode(3, 0);
    ILayerManager_s007c_1c10* layerManager = LayerManager();
    mJob0->Reset();
    mJob0->Init(a3, a8, a4, a5, a6, a2, mSplatterViewer, a12, 0);

    if (haveRect1) {
        mBakeInfoSplatterViewer->SetBasis(&xf);
        mBakeInfoSplatterViewer->SetRenderMode(3, 1);
        ChainPtr chain(new("Graphics", 0, 0, 0, 0) cFilterChainJob_s007c_1c10());
        chain.mpObject->Start();
        FilterPtr_s007c_1c10 f1(new("Graphics", 0, 0, 0, 0) cJobPostFilter_s007c_1c10());
        FilterPtr_s007c_1c10 f2(new("Graphics", 0, 0, 0, 0) cJobPostFilter_s007c_1c10());
        FilterPtr_s007c_1c10 f3(new("Graphics", 0, 0, 0, 0) cJobPostFilter_s007c_1c10());
        FilterPtr_s007c_1c10 f4(new("Graphics", 0, 0, 0, 0) cJobPostFilter_s007c_1c10());
        tmp.mPageID = -1;
        tmp.mAllocID = -1;
        RenderTargetManager()->FreeRect(&tmp, false);
        f1.mpObject->Init(0xd2, a10, &tmp, 0);
        f2.mpObject->Init(0xd2, &tmp, a10, 0);
        f3.mpObject->Init(0xd2, a10, &tmp, 0);
        f4.mpObject->Init(0xd2, &tmp, a10, 0);
        chain.mpObject->AddFilter(f1.mpObject);
        chain.mpObject->AddFilter(f2.mpObject);
        chain.mpObject->AddFilter(f3.mpObject);
        chain.mpObject->AddFilter(f4.mpObject);
        mJob1->Reset();
        mJob1->Init(a3, a8, a4, a5, a6, a10, mBakeInfoSplatterViewer, a12, chain.mpObject);
    }

    if (haveRect2) {
        ChainPtr chain(new("Graphics", 0, 0, 0, 0) cFilterChainJob_s007c_1c10());
        chain.mpObject->Start();
        mNMapSpecSplatterViewer->SetBasis(&xf);
        mNMapSpecSplatterViewer->SetRenderMode(3, 2);
        FilterPtr_s007c_1c10 f1(new("Graphics", 0, 0, 0, 0) cJobPostFilter_s007c_1c10());
        FilterPtr_s007c_1c10 f2(new("Graphics", 0, 0, 0, 0) cJobPostFilter_s007c_1c10());
        FilterPtr_s007c_1c10 f3(new("Graphics", 0, 0, 0, 0) cJobPostFilter_s007c_1c10());
        FilterPtr_s007c_1c10 f4(new("Graphics", 0, 0, 0, 0) cJobPostFilter_s007c_1c10());
        tmp.mPageID = -1;
        tmp.mAllocID = -1;
        RenderTargetManager()->FreeRect(&tmp, false);
        f1.mpObject->Init(0xd2, a11, &tmp, 0);
        f2.mpObject->Init(0xd2, &tmp, a11, 0);
        f3.mpObject->Init(0xd2, a11, &tmp, 0);
        f4.mpObject->Init(0xd3, &tmp, a11, 0);
        chain.mpObject->AddFilter(f1.mpObject);
        chain.mpObject->AddFilter(f2.mpObject);
        chain.mpObject->AddFilter(f3.mpObject);
        chain.mpObject->AddFilter(f4.mpObject);
        mJob2->Reset();
        mJob2->Init(a3, a8, a4, a5, a6, a11, mNMapSpecSplatterViewer, a12, chain.mpObject);
    }

    DrvBA22* drv = new("Graphics", 0, 0, 0, 0) DrvBA22();
    drv->mField08 = a7;
    drv->mField10 = 0;
    drv->mField18 = a9;
    drv->mField20 = 0;
    cSplatJob* job = mJob0;
    job->mEffect = drv;
    LayerInfo_s007c_1c10 info;
    layerManager->AddLayer(mJob0->GetLayer(0, &info));
}
}  // namespace SPL
