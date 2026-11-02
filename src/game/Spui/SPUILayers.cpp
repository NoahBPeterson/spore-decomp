// src/game/Spui/SPUILayers.cpp -- migrated from slice(s) s0080f7c0, s0080e6b0, s0080d670, s0080c5d0 by tools/migrate/rewrite.py
// Object file: Spui/SPUILayers.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include "cSPUILayeredObject.h"
#include "cSPUIModelsAndEffectsRenderer.h"
#include <intrin.h>
#include "cSPUILayoutManager.h"
#include "cSPUILayoutObjectCollection.h"
#include "cSPUILayoutResourceFactory.h"
#include "cSPUIResourcesKeyFilter.h"
#include <math.h>
#include <xmmintrin.h>

// ---- items of slice s0080d670 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;
void  __cdecl  VisitTree(void*, void*, void*);    // 0x807d30 SPUIHelpers::VisitWindowTreeDepthFirst
void* __cdecl  BBoxAdd();                          // 0x67cad0 cSPBoundingBox::AddBoundingBox
void* __cdecl  ModelMgr();                         // 0x67dd80
void* __cdecl  EffectsMgr();                       // 0x67ddd0
void* __cdecl  GetRaster();                        // 0x67dd50
void* __cdecl  Fun82e4a0();                        // 0x82e4a0
void  __fastcall Fun7c4a60(void*, void*, void*);        // 0x7c4a60 cViewer::FUN_007c4a60
void  __fastcall Fun7c4b50(void*, void*, float);        // 0x7c4b50 cViewer::FUN_007c4b50
void  __fastcall Fun7c3c50(void*, void*, int);          // 0x7c3c50 cViewer::Clear
void  __fastcall BoundingBox_TransformBy(void*, void*, void*); // 0x409dd0 cSPBoundingBox::Transform
typedef void* (__thiscall *VF0)(void*);
typedef void  (__thiscall *VF0v)(void*);
typedef void* (__thiscall *VF1)(void*, void*);
typedef void  (__thiscall *VF1v)(void*, void*);
typedef void* (__thiscall *VF1a)(void*, void*, void*);
typedef void  (__thiscall *VF2v)(void*, void*, void*, int);
typedef void  (__thiscall *VF3v)(void*, void*, void*, void*, void*);
struct Vec2 {
    f32 x, y;
    Vec2() {}
    Vec2(f32 a, f32 b) : x(a), y(b) {}
    Vec2(const Vec2& o) : x(o.x), y(o.y) {}
};
struct Rect4 { f32 x0, y0, x1, y1; };
typedef void  (__thiscall *VFtf)(void*, void*, Vec2);
static inline void** VT(void* o) { return *(void***)o; }
static inline f32 SseSub(f32 a, f32 b) { return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b))); }
struct Layered {
    u8  pad0[8];
    void* renderer;  // +0x8
    void** vBegin;   // +0xc
    void** vEnd;     // +0x10
    void** v2Begin;  // +0x14
    void** v2End;    // +0x18
    u8  pad1c[0x10];          // +0x1c..+0x2b
    u8  modelTransform[0x10]; // +0x2c..+0x3b
    void* obj3c;     // +0x3c
    u8  pad40[4];
    u8  bits44[0x1c]; // +0x44..+0x5f
    u8  pad60[4];     // +0x60..+0x63
    f32 rectMinX;     // +0x64
    f32 rectMinY;     // +0x68
    f32 rectMaxX;     // +0x6c
    f32 rectMaxY;     // +0x70
    u8  flag74;       // +0x74
    u8  flag75;       // +0x75
    u8  flag76;       // +0x76
    u8  pad77;        // +0x77
    u8  flag78;       // +0x78
    u8  pad79[0x1cc - 0x79];
    u8  flag1cc;     // +0x1cc
    u8  pad1d4[0x1d4 - 0x1cd];
    i32 r1d4;        // +0x1d4
    i32 r1d8;        // +0x1d8
    i32 r1dc;        // +0x1dc
    i32 r1e0;        // +0x1e0
    u8  entries1e4[0x24c - 0x1e4];  // 6 * 0x14
    u8  flag24c;     // +0x24c
    u8  pad250[0x250 - 0x24d];
    void* p250;      // +0x250
    void* p254;      // +0x254
    void* p258;      // +0x258
    void* p25c;      // +0x25c
    void* p260;      // +0x260

    u8*  Method810(void* win);            // 0x80d810
    void MethodDA50(void* param, void*, void*, void*, void*); // 0x80da50
    void ReleaseAll();                    // 0x80dbb0
    void MethodDC50(int);                 // 0x80dc50
    void* MethodDC90();                   // 0x80dc90
    int  MethodDD50();                    // 0x80dd50
    void SetObj(void* p, u8 b);           // 0x80dda0
    void RenderEnd();                     // 0x80de20
    void* CameraLocZoom(void* outVec3, float* outZoom); // 0x80dfe0
    bool RenderBegin(int id);             // 0x80e270
};
struct Renderer {
    void __thiscall SetViewport(int x, int y, int w, int h); // 0x7c5310
    void __thiscall SetAspect(float aspect);                 // 0x7c4b50
    void __thiscall SetFov(float fov);                       // 0x7c53d0
    void __thiscall SetNearFar(float d);                     // 0x7c4ba0
    void __thiscall Snapshot(void* state);                   // 0x7c40f0
    void __thiscall Submit(void* state);                     // 0x7c4d00
};
struct CamState {
    u16 flags;      // +0x00
    u16 count;      // +0x02
    f32 x;          // +0x04
    f32 y;          // +0x08
    f32 z;          // +0x0c
    f32 w;          // +0x10
    f32 basis[9];   // +0x14..+0x37
};
u8   __cdecl  FUN_8050b0(void*);              // 0x8050b0
void __cdecl  FUN_805ea0(void* outRect);      // 0x805ea0
void __cdecl  CamStateInit(CamState* s);      // 0x409930
struct FlagSetter { int __thiscall Set790(char p2, char p3); };
struct DARecord {
    void* obj;   // +0
    void* a;     // +4
    void* b;     // +8
};
struct DDBounds {
    i32 flag;    // +0 (only the low byte is used)
    i32 lo;      // +4
    i32 hi;      // +8
};
struct Box6 {
    f32 minx, miny, minz;   // +0x00
    f32 maxx, maxy, maxz;   // +0x0c
};
struct ModelObj {
    u8  pad0[4];
    u32 flags;   // +0x04
    u8  pad8[4];
    f32 tx;      // +0x0c
    f32 ty;      // +0x10
    f32 tz;      // +0x14
};
// ---- items of slice s0080d670 end

// ---- items of slice s0080e6b0 begin (TODO(rewrite): local stubs, replace by canonical classes)

void* __cdecl  GameAlloc(size_t size, const char* name, int, int, int, int);
void  __cdecl  GameFree(void* p);
void  __fastcall Fun_7c3f70(void*);          // 0x7c3f70
void  __fastcall Fun_7c3ba0(void*);          // 0x7c3ba0
void  __fastcall Fun_7c4000(void*);          // 0x7c4000
void  __fastcall Fun_7c4dd0(void*, int);      // 0x7c4dd0 SP::cSPEditorPhysicsWorld::Init
void  __fastcall Fun_8e2b20(void*);           // 0x8e2b20
void  __fastcall SharedVecDtor(void*);        // 0x5c7f10
void* __cdecl  ModelManagerGet();             // 0x67dd80
void  __fastcall Fun_82e4b0(void*, void*);    // 0x82e4b0
void  __fastcall Fun_82e4c0(void*, void*);    // 0x82e4c0

struct cMWModel { u8 pad[0x40]; i32 mRefCount; u8 pad44[4]; };
struct cSPUILayeredObject_s0080_e6b0 {
    void**  vtbl;        // +0
    i32     mRefCount;   // +4 (base RefCount)
    void*   mpViewer;    // +8
    void*   mpWindow;    // +0xc
    void*   mpWinProc;   // +0x10
    cMWModel** mModelsBegin;  // +0x14
    cMWModel** mModelsEnd;    // +0x18
    cMWModel** mModelsCap;    // +0x1c
    u8      pad20[0x74 - 0x20];
    u8      flag74;      // +0x74
    u8      flag75;      // +0x75
    u8      flag76;      // +0x76
    u8      flag77;      // +0x77
    u8      flag78;      // +0x78

    cSPUILayeredObject_s0080_e6b0* __thiscall ctor();          // 0x80e850
    void __thiscall dtor();                         // 0x80ead0
    u32  __thiscall RemoveModel(cMWModel* m);       // 0x80e980
    void __thiscall RemoveAllModels();              // 0x80ea50
    void __thiscall MethodE6B0(void* a, void* b);   // 0x80e6b0
};
struct LayerInfoVec {                 // eastl::vector<cLayerInfo, fixed_vector_allocator<12,5,...>>
    void* begin;      // +0
    void* end;        // +4
    void* cap;        // +8
    void* x0c;        // +0xc
    void* inline_;    // +0x10
    void __thiscall dtor();   // 0x80ea80
};
class cSPUICustomRendererImpl { public:
    void** vtbl;         // +0   0x1417df8 / 0x1417e18
    void** vtbl2;        // +4   0x1417df4 / 0x1417e14
    u32    atomic8;      // +8
    LayerInfoVec mLayers;// +0xc
    u8     pad20[0x60 - 0x20];
    u8     sub60[0x1d4 - 0x60];
    u8     pad1d4[0x250 - 0x1d4];
    void*  p250;         // +0x250
    void*  p254;         // +0x254
    void*  p258;         // +0x258

    void* __thiscall ctor();              // 0x80ebc0
    void* __thiscall VectorDtor(u8 flags);// 0x80ec40 (dtor w/ flag)
    void  __thiscall ScalarDtor();        // 0x80eca0
    void __thiscall MethodF380(void*);    // 0x80f380
};
struct UI_LayerManager {
    void** vtbl;      // +0   0x1417de4
    void** vtbl2;     // +4   0x1417dd4
    u8     pad8[0xc - 8];
    void*  v1begin;   // +0xc
    void*  v1end;     // +0x10
    void*  v1cap;     // +0x14
    u8     pad18[0x20 - 0x18];
    void*  v2begin;   // +0x20
    void*  v2end;     // +0x24
    void*  v2cap;     // +0x28
    u8     pad2c[0x34 - 0x2c];
    u8     b34;       // +0x34
    u8     pad35[0x38 - 0x35];
    i32    i38;       // +0x38
    void*  p3c;       // +0x3c
    u8     pad40[0x94 - 0x40];
    u8     b94;       // +0x94

    UI_LayerManager* __thiscall ctor();  // 0x80edb0
    void* __thiscall VectorDtor(u8); // 0x80ee10
};
void __fastcall FUN_0080dbb0(void*);   // 0x80dbb0 (slice 24)
struct PtrVec {
    void** begin;  // +0
    void** end;    // +4
    void** cap;    // +8
    void*  x0c;    // +0xc
    void*  inline_;// +0x10
    void __thiscall Insert1(void** pos, void** val);   // 0x80efe0
    void __thiscall Insert12(void** pos, void** val);  // 0x80f140
};
void __fastcall FUN_0080f2e0(char* self, void** obj, void* a, void* b);
// ---- items of slice s0080e6b0 end

// ---- items of slice s0080f7c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* __cdecl EA_UTFWin_GetManager();      // 0x957f30
extern void* __cdecl SP_MessageServer();          // 0x67dcc0
extern void* __cdecl SP_ModelManager();           // 0x67dd80
extern void* __cdecl FUN_0067dd50();              // 0x67dd50
extern int   __cdecl FUN_0082e700(int);           // 0x82e700
extern void* __cdecl SPUIHelpers_VisitWindowTreeDepthFirst(void*, void*, void*); // 0x807d30
extern void* __cdecl cSP_getA(void*);             // 0x67cad0
extern void  __cdecl FUN_0080ee90(void*, void*);  // 0x80ee90
extern char FUN_0080e6b0_sym, FUN_0080ee90_sym, FUN_0080f380_sym, FUN_0080d6d0_sym,
            FUN_0080d770_sym, SerShutdown_sym, SerDtor_sym, ResetWinCache_sym,
            vtbl_cConnectionDialog, vtbl_014181d8, vtbl_014181c0, vtbl_SimSummarizer,
            vtbl_AddRef_014181e8, vtbl_EditorResource, DAT_013f6b3c,
            CountedPtr_sym, FUN_00998f60_sym, FUN_00998f80_sym, FUN_0080f7c0_sym,
            SerCtor_sym;
extern void* g_15fd918;
extern f32 g_rot[9];
extern f32 g_tx, g_ty, g_tz;
struct PtrVec_s0080_f7c0 {
    void* mBegin;   // +0
    void* mEnd;     // +4
    void* mCap;     // +8
    void* mAlloc;   // +0xc
    void __thiscall erase(void* first, void* last);
};
struct cMWModel_s0080_f7c0 {
    void** vtbl;      // +0
    u32    flags;     // +4
    u16    w8;        // +8
    u16    wa;        // +0xa
    f32    tx;        // +0xc
    f32    ty;        // +0x10
    f32    tz;        // +0x14
    f32    f18;       // +0x18
    f32    rot[9];    // +0x1c
    i32    ref40;     // +0x40
    u32    groups[8]; // +0x44
};
struct cSPUILayeredObject_s0080_f7c0 {
    void** vtbl;        // +0
    i32    mRefCount;   // +4
    void*  mpViewer;    // +8
    void*  mpWindow;    // +0xc
    void*  mpWinProc;   // +0x10
    PtrVec_s0080_f7c0 mModels;     // +0x14
    u8     pad24[0x6c - 0x24];
    f32    m6c;         // +0x6c
    u8     pad70[0x74 - 0x70];
    u8     b74;         // +0x74
    u8     pad75[2];
    u8     b77;         // +0x77

    u32  __thiscall MethodF9D0(void* a, void* key);
    void* __thiscall MethodFAC0(void* a, void* b, void* cb);
    void* __thiscall AddModel(cMWModel_s0080_f7c0* model);  // 0x0080fc50 (cSPUILayeredObject::AddModel)
};
class cSPUILayerManager { public:
    void** vtbl;        // +0
    void** vtbl2;       // +4
    u8     pad8[4];
    PtrVec_s0080_f7c0 mObjects;    // +0xc
    u8     pad1c[4];
    PtrVec_s0080_f7c0 mRemoved;    // +0x20
    u8     pad30[4];
    u8     b34;         // +0x34
    u8     pad35[3];
    i32    i38;         // +0x38
    void*  p3c;         // +0x3c
    PtrVec_s0080_f7c0 mLayerInfos; // +0x40
    u8     pad50[0x94 - 0x50];
    u8     b94;         // +0x94

    u32  __thiscall RemoveObject(cSPUILayeredObject_s0080_f7c0* p);
    void __thiscall RemoveAllObjects();
    void __thiscall DrawLayer(void* a, void* b, void* c, void* d);
    bool __thiscall Shutdown();
    void* __thiscall AddObject(void* a, void* b, void* cb);
};
struct ObjStub {
    void __thiscall go();                  // 0x80f380
    void __thiscall doE6B0(int, void*, void*); // 0x80e6b0
};
// ---- items of slice s0080f7c0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
u8 __cdecl FUN_0080d670(void* p, u8* p2);  // 0x0080d670 (stays in the slice: not this object's)
u16 __cdecl FUN_0080d6d0(void* p, u8* p2);  // 0x0080d6d0 (stays in the slice: not this object's)

// @ 0x0080d590
void __stdcall SetFlag8(char* p)
{ p[0x10] = 0; }

// @ 0x0080d770
void __cdecl FUN_0080d770(void* a, void* b, void* p3)
{
    ((VF2v)VT(p3)[0xc / 4])(p3, a, b, 4);
}

// @ 0x0080d790
int FlagSetter::Set790(char p2, char p3)
{
    char* self = (char*)this;
    self[0x75] = p2;
    int v = (p2 && !p3);
    self[0x76] = v;
    return v;
}

// @ 0x0080d7e0
i32 __cdecl FUN_0080d7e0(float* a, float* b)
{
    if (a[0] == b[0] && a[1] == b[1]) return 0;
    return 1;
}

// @ 0x0080d810
u8* Layered::Method810(void* win)
{
    u32 i = 0;
    u8* e = entries1e4;
    for (; i < 6; ++i, e += 0x14)
        if (*e == 0) break;
    if (i == 6) return 0;
    *e = 1;

    f32* r = (f32*)((VF0)VT(win)[0x38 / 4])(win);
    f32 w = SseSub(r[2], r[0]);
    f32 h = SseSub(r[3], r[1]);

    Vec2 p0, p1, p2, p3;
    VFtf tf = (VFtf)VT(win)[0xc0 / 4];
    tf(win, &p0, Vec2(0.0f, 0.0f));
    tf(win, &p1, Vec2(w, h));
    tf(win, &p2, Vec2(w, 0.0f));
    tf(win, &p3, Vec2(0.0f, h));

    const f32& maxY1 = p3.y > p2.y ? p3.y : p2.y;
    const f32& maxY2 = maxY1 > p1.y ? maxY1 : p1.y;
    const f32& maxY = maxY2 > p0.y ? maxY2 : p0.y;
    const f32& maxX1 = p3.x > p2.x ? p3.x : p2.x;
    const f32& maxX2 = maxX1 > p1.x ? maxX1 : p1.x;
    const f32& maxX = maxX2 > p0.x ? maxX2 : p0.x;
    const f32& minY1 = p2.y > p3.y ? p3.y : p2.y;
    const f32& minY2 = p1.y > minY1 ? minY1 : p1.y;
    const f32& minY = p0.y > minY2 ? minY2 : p0.y;
    const f32& minX1 = p2.x > p3.x ? p3.x : p2.x;
    const f32& minX2 = p1.x > minX1 ? minX1 : p1.x;
    const f32& minX = p0.x > minX2 ? minX2 : p0.x;

    u8* rect = (u8*)((char*)this + i * 0x14 + 0x1d4);
    ((i32*)rect)[0] = (i32)minX;
    ((i32*)rect)[1] = (i32)minY;
    ((i32*)rect)[2] = (i32)maxX;
    ((i32*)rect)[3] = (i32)maxY;
    return rect;
}

// @ 0x0080da50
void Layered::MethodDA50(void* param, void* a2, void* a3, void* a4, void* a5)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    void* bb = BBoxAdd();
    if (*(i32*)((char*)bb + 0x38) != 0) return;
    if (flag24c && param) {
        Fun7c4a60((char*)this + 0x60, 0, param);
        flag1cc = 0;
        u32 w = (u32)(*(i32*)((char*)param + 8) - *(i32*)param);
        u32 h = (u32)(*(i32*)((char*)param + 0xc) - *(i32*)((char*)param + 4));
        if (w != 0 && h != 0) {
            void* r = GetRaster();
            void* info = ((VF0)VT(r)[0x1c / 4])(r);
            f32 f = (f32)w * *(f32*)((char*)info + 0x1c) / (f32)h;
            Fun7c4b50((char*)this + 0x60, 0, f);
        }
    }
    Fun7c3c50((char*)this + 0x60, 0, 6);
    DARecord* begin = (DARecord*)vBegin;
    i32 n = (i32)((u8*)vEnd - (u8*)vBegin) / 0xc;
    if (n > 0) {
        struct Local { i32 a, b, c, pad0, pad1; } local;
        local.a = local.b = local.c = local.pad0 = local.pad1 = 0;
        DARecord* it = begin;
        for (i32 i = 0; i < n; ++i, ++it) {
            void* o = it->obj;
            void* result = Fun82e4a0();
            ((VF3v)VT(o)[0xc / 4])(o, it->b, it->a, &local, result);
        }
    }
}

// @ 0x0080db70
void* __fastcall FUN_0080db70(char* p)
{
    if (p) return *(void**)(p + 8);
    return *(void* volatile*)(p + 0x258);
}

// @ 0x0080db90
void* __fastcall FUN_0080db90(char* p)
{
    if (p) return *(void**)(p + 4);
    return *(void* volatile*)(p + 0x254);
}

// @ 0x0080dbb0
void Layered::ReleaseAll()
{
    if (!p258) return;
    if (p258) {
        void* o = p258;
        p258 = 0;
        ((VF0v)VT(o)[1])(o);
    }
    {
        void* m = ModelMgr();
        ((VF1v)VT(m)[0x18 / 4])(m, p25c);
    }
    p25c = 0;
    if (p254) {
        void* o = p254;
        p254 = 0;
        ((VF0v)VT(o)[1])(o);
    }
    {
        void* m = EffectsMgr();
        ((VF1v)VT(m)[0x50 / 4])(m, p260);
    }
    p260 = 0;
    ((VF0v)VT(p250)[0x7c / 4])(p250);
    if (p250) {
        void* o = p250;
        p250 = 0;
        ((VF0v)VT(o)[1])(o);
    }
}

// @ 0x0080dc50
void Layered::MethodDC50(int)
{
    if (!obj3c) return;
    void* r = ((VF1)VT(obj3c)[0x144 / 4])(obj3c, 0);
    if (!r) return;
    void* r2 = ((VF1)VT(obj3c)[0x144 / 4])(obj3c, 0);
    ((VF0v)VT(r2)[0x30 / 4])(r2);
}

// @ 0x0080dc90
void* Layered::MethodDC90()
{
    if (!obj3c) return 0;
    void* r = ((VF1)VT(obj3c)[0x144 / 4])(obj3c, 0);
    if (!r) return 0;
    void* r2 = ((VF1)VT(obj3c)[0x144 / 4])(obj3c, 0);
    return ((VF0)VT(r2)[0x34 / 4])(r2);
}

// @ 0x0080dcd0
void __stdcall FUN_0080dcd0(void* a, i32 b, u8 c)
{
    u8 local_c[8];
    *(i32*)(local_c + 4) = 10000;
    *(i32*)(local_c + 8) = 0xffffd8f0;
    local_c[0] = 1;
    VisitTree(a, (void*)FUN_0080d6d0, local_c);
    i32 d = b - *(i32*)(local_c + 4);
    u8 local14[8];
    local14[0] = c;
    *(i32*)(local14 + 4) = d;
    if (d != 0) VisitTree(a, (void*)FUN_0080d670, local14);
}

// @ 0x0080dd50
int Layered::MethodDD50()
{
    void* p = vBegin;
    if (!p) return 0;
    BBoxAdd();
    DDBounds local;
    local.flag = 0;
    local.lo = 10000;
    local.hi = -10000;
    VisitTree(p, (void*)FUN_0080d6d0, &local);
    return local.lo;
}

// @ 0x0080dda0
void Layered::SetObj(void* param, u8 b)
{
    void* old = vBegin;
    if (old == param) return;
    if (*(u8*)((char*)this + 0x74)) {
        ((VF1v)VT(old)[0x108 / 4])(old, *(void**)((char*)this + 0x10));
    }
    if (param != old) {
        if (param) ((VF0v)VT(param)[0])(param);
        vBegin = (void**)param;
        if (old) ((VF0v)VT(old)[1])(old);
    }
    u8 nv;
    if (vBegin == 0 || b == 0) nv = 0; else nv = 1;
    *(u8*)((char*)this + 0x74) = nv;
    if (nv) {
        void* cur = vBegin;
        ((VF1v)VT(cur)[0x104 / 4])(cur, *(void**)((char*)this + 0x10));
    }
}

// @ 0x0080de20
void Layered::RenderEnd()
{
    void** it = v2Begin;
    void** end = v2End;
    while (it != end) {
        void* o = *it++;
        void* m = ModelMgr();
        u32 idx = (u32)(size_t)((VF1)VT(m)[0x28 / 4])(m, (void*)0x32fab27);
        if (idx < 0x40) {
            u32* p = (u32*)((char*)o + 0x44 + (idx >> 5) * 4);
            *p &= ~(1u << (idx & 0x1f));
        }
    }
}

// @ 0x0080de80
void* __cdecl FUN_0080de80(void** first, void** last, void** dest)
{
    while (first != last) {
        if (dest) {
            void* o = *first;
            *dest = o;
            if (o) ((VF0v)VT(o)[0])(o);
        }
        ++first; ++dest;
    }
    return dest;
}

// @ 0x0080df00
void* __cdecl FUN_0080df00(void** first, void** last, void** dest)
{
    while (first != last) {
        if (dest) {
            void* o = *first;
            *dest = o;
            if (o) ((VF0v)VT(o)[0])(o);
            dest[1] = first[1];
            dest[2] = first[2];
        }
        first += 3; dest += 3;
    }
    return dest;
}

// @ 0x0080df50
int __fastcall FUN_0080df50(char* p)
{
    char* b = (p && p != (char*)0x250) ? p - 0x24c : 0;
    return _InterlockedIncrement((long*)(b + 4));
}

// @ 0x0080df80
int cSPUIModelsAndEffectsRenderer::Release()
{
    char* p = (char*)this;
    char* b = 0;
    if (p) { char* t = p - 0x250; if (t) b = t + 4; }
    long* rc = (long*)(b + 4);
    int n = _InterlockedExchangeAdd(rc, -1) - 1;
    if (n == 0) {
        _InterlockedExchange(rc, 1);
        if (b) ((VF1v)VT(b)[0])(b, (void*)1);
        return 0;
    }
    return n;
}

// @ 0x0080dfc0
void __fastcall FUN_0080dfc0(char* p)
{
    if (p) ((Layered*)(p - 0x250))->ReleaseAll();
    else   ((Layered*)0)->ReleaseAll();
}

// @ 0x0080dfe0
void* Layered::CameraLocZoom(void* outVec3, float* outZoom)
{
    Box6 box;
    box.minx = box.miny = box.minz = 3.402823466e+38F;
    box.maxx = box.maxy = box.maxz = -3.402823466e+38F;

    void* bbox = BBoxAdd();
    void* mgr = *(void**)((char*)bbox + 0x3c);
    ModelObj** begin = (ModelObj**)v2Begin;
    u32 n = (u32)((u8*)v2End - (u8*)v2Begin) >> 2;
    void* lastObj = bbox;

    for (u32 i = 0; i < n; ++i) {
        ModelObj* obj = begin[i];
        lastObj = obj;
        u32 flags = obj->flags;
        if (((flags >> 0xf) & 1) && (flags & 1)) {
            float* pf = (float*)((VF1)VT(mgr)[0x60 / 4])(mgr, obj);
            obj = begin[i];
            f32 tx = obj->tx, ty = obj->ty, tz = obj->tz;
            f32 cmnx = tx + pf[0];
            f32 cmny = ty + pf[1];
            f32 cmnz = tz + pf[2];
            f32 cmxx = tx + pf[3];
            f32 cmxy = ty + pf[4];
            f32 cmxz = tz + pf[5];
            if (box.minx <= box.maxx) {
                if (cmnx < box.minx) box.minx = cmnx;
                if (box.maxx < cmxx) box.maxx = cmxx;
                if (cmny < box.miny) box.miny = cmny;
                if (box.maxy < cmxy) box.maxy = cmxy;
                if (cmnz < box.minz) box.minz = cmnz;
                if (box.maxz < cmxz) box.maxz = cmxz;
            } else {
                box.minx = cmnx; box.miny = cmny; box.minz = cmnz;
                box.maxx = cmxx; box.maxy = cmxy; box.maxz = cmxz;
            }
        }
    }

    if (box.minx <= box.maxx) {
        BoundingBox_TransformBy(&box, 0, modelTransform);
        ((float*)outVec3)[0] = (box.maxx + box.minx) * 0.5f;
        ((float*)outVec3)[1] = (box.maxy + box.miny) * 0.5f;
        ((float*)outVec3)[2] = (box.maxz + box.minz) * 0.5f;
        double dx = (double)box.maxx - (double)box.minx;
        double dy = (double)box.maxy - (double)box.miny;
        double dz = (double)box.maxz - (double)box.minz;
        double sum = (dx * dx + dz * dz) + dy * dy;
        *outZoom = (f32)(sqrt(sum) * 1.8f);
        return outVec3;
    }
    return lastObj;
}

// @ 0x0080e270
bool Layered::RenderBegin(int id)
{
    if (!vBegin) return false;
    if (MethodDD50() != id) return false;
    void** it = v2Begin;
    void** end = v2End;
    if (it == end) return false;
    if (!FUN_8050b0(vBegin)) return false;

    f32 cb = 0.0f, cg = 0.0f, cr = 0.0f, ca = 0.0f;
    if (flag78) {
        u32 c = (u32)(size_t)((VF0)VT(vBegin)[0x30 / 4])(vBegin);
        const f32 k = 0.0039215689f;
        cb = (f32)((c >> 16) & 0xff) * k;
        cg = (f32)((c >> 8) & 0xff) * k;
        cr = (f32)(c & 0xff) * k;
        ca = (f32)(c >> 24) * k;
    }

    for (; it != end; ++it) {
        void* obj = *it;
        void* mgr = ModelMgr();
        u32 idx = (u32)(size_t)((VF1a)VT(mgr)[0x28 / 4])(mgr, (void*)0x32fab27, (void*)0);
        if (idx < 0x40) {
            u32* bits = (u32*)((char*)obj + 0x44 + (idx >> 5) * 4);
            *bits |= 1u << (idx & 0x1f);
        }
        if (flag78) {
            u32 flags = *(u32*)((char*)obj + 4);
            if (flags & 2) {
                *(f32*)((char*)obj + 0x4c) = cb;
                *(f32*)((char*)obj + 0x50) = cg;
                *(f32*)((char*)obj + 0x54) = cr;
                *(f32*)((char*)obj + 0x58) = ca;
            }
        }
    }

    if (!flag75 && !flag76) return true;

    f32* wr = (f32*)((VF0)VT(vBegin)[0x38 / 4])(vBegin);
    f32 rx0 = wr[0], ry0 = wr[1], rx1 = wr[2], ry1 = wr[3];

    Vec2 p0, p1;
    VFtf tf = (VFtf)VT(vBegin)[0xc0 / 4];
    tf(vBegin, &p0, Vec2(0.0f, 0.0f));
    tf(vBegin, &p1, Vec2(rx1 - rx0, ry1 - ry0));

    bool changed = FUN_0080d7e0((float*)&p0, &rectMinX) != 0
                || FUN_0080d7e0((float*)&p1, &rectMaxX) != 0;

    rectMinX = p0.x;
    rectMinY = p0.y;
    rectMaxX = p1.x;
    rectMaxY = p1.y;
    if (rectMinX >= rectMaxX) return false;
    if (rectMinY >= rectMaxY) return false;

    Rect4 vp;
    FUN_805ea0(&vp);
    if (0.0f > rectMaxX) return false;
    if (0.0f > rectMaxY) return false;
    if (rectMinX > vp.x1 - vp.x0) return false;
    if (rectMinY > vp.y1 - vp.y0) return false;

    if (!changed) return true;

    f32 w = rectMaxX - rectMinX;
    f32 h = rectMaxY - rectMinY;
    int iw = (int)w;
    int ih = (int)h;
    int ix = (int)rectMinX;
    int iy = (int)rectMinY;

    Renderer* dev = (Renderer*)renderer;
    dev->SetViewport(ix, iy, iw, ih);
    dev->SetAspect((f32)iw / (f32)ih);
    if (flag76) return true;

    dev->SetFov(50.0f);
    dev->SetNearFar(0.01f);

    f32 camPos[3];
    f32 zoom;
    CameraLocZoom(camPos, &zoom);

    CamState cs;
    CamStateInit(&cs);
    dev->Snapshot(&cs);
    cs.flags |= 4;
    ++cs.count;
    cs.x = camPos[0] - zoom * cs.basis[3];
    cs.y = camPos[1] - zoom * cs.basis[4];
    cs.z = camPos[2] - zoom * cs.basis[5];
    dev->Submit(&cs);
    return true;
}

// @ 0x0080e6b0
void __thiscall cSPUILayeredObject_s0080_e6b0::MethodE6B0(void* a, void* b)
{
    u8* self = (u8*)this;
    *(u32*)(self + 0x38) = (u32)(size_t)a;
    Fun_82e4b0(self, b);
    Fun_82e4c0(self, b);
    if (a) {
        void* x = ((VF0)VT(a)[4 / 4])(a);
        void* r = ((VF0)VT(x)[0x34 / 4])(x);
        f32 v[4];
        v[0] = ((f32*)r)[0]; v[1] = ((f32*)r)[1]; v[2] = ((f32*)r)[2]; v[3] = ((f32*)r)[3];
        (void)v;
    }
}

// @ 0x0080e850
cSPUILayeredObject_s0080_e6b0* __thiscall cSPUILayeredObject_s0080_e6b0::ctor()
{
    u8* self = (u8*)this;
    mRefCount = 0;
    vtbl = (void**)0x1417dc4;
    mpViewer = 0;
    mpWindow = 0;
    mpWinProc = 0;
    mModelsBegin = 0; mModelsEnd = 0; mModelsCap = 0;
    *(u32*)(self + 0x28) = 0;
    *(u16*)(self + 0x2e) = 0;
    *(u16*)(self + 0x2c) = 0;
    *(f32*)(self + 0x30) = 0.0f;
    *(f32*)(self + 0x34) = 0.0f;
    *(f32*)(self + 0x38) = 0.0f;
    *(f32*)(self + 0x3c) = 1.0f;
    *(f32*)(self + 0x64) = 0.0f;
    *(f32*)(self + 0x68) = 0.0f;
    *(f32*)(self + 0x6c) = 0.0f;
    *(f32*)(self + 0x70) = 0.0f;
    flag74 = 0; flag75 = 0; flag76 = 0; flag77 = 0; flag78 = 1;
    mpViewer = GameAlloc(0x174, "UI/cSPUILayeredObject/cViewer", 0, 0, 0, 0);
    if (mpViewer) Fun_7c3f70(mpViewer);
    Fun_7c4dd0(mpViewer, 0);
    void* wp = GameAlloc(0x10, "UI/cObjectWindowWinProc", 0, 0, 0, 0);
    if (wp) {
        *(void**)((u8*)wp + 0x0c) = this;
    }
    mpWinProc = wp;
    return this;
}

// @ 0x0080e980
u32 __thiscall cSPUILayeredObject_s0080_e6b0::RemoveModel(cMWModel* param)
{
    u32 n = (u32)(mModelsEnd - mModelsBegin);
    for (u32 i = 0; i < n; ++i) {
        cMWModel* m = mModelsBegin[i];
        if (m == param) {
            // detach from world
            void* world = *(void**)((u8*)param + 4);
            ((VF1v)VT(world)[0x16c / 4])(world, param);
            cMWModel* last = mModelsEnd[-1];
            cMWModel* old = mModelsBegin[i];
            if (last != old) {
                if (last) last->mRefCount += 1;
                mModelsBegin[i] = last;
                if (old) {
                    if (old->mRefCount > 1) old->mRefCount -= 1;
                    else { void* w = *(void**)((u8*)old + 4); ((VF1v)VT(w)[0x170 / 4])(w, old); }
                }
            }
            mModelsEnd -= 1;
            cMWModel* tail = mModelsEnd[0];
            if (tail) {
                if (tail->mRefCount > 1) tail->mRefCount -= 1;
                else { void* w = *(void**)((u8*)tail + 4); ((VF1v)VT(w)[0x170 / 4])(w, tail); }
            }
            *(f32*)((u8*)this + 0x6c) = 0.0f;
            return 1;
        }
    }
    return 0;
}

// @ 0x0080ea50
void cSPUILayeredObject::RemoveAllModels()
{
    while (mModels.mpBegin != mModels.mpEnd) RemoveModel(*mModels.mpBegin);
}

// @ 0x0080ea80
void __thiscall LayerInfoVec::dtor()
{
    void** e = (void**)end;
    for (void** p = (void**)begin; p < e; p = (void**)((u8*)p + 0xc)) {
        void* o = *p;
        if (o) ((VF0v)VT(o)[1])(o);
    }
    void* b = begin;
    if (b && b != inline_) GameFree(b);
}

// @ 0x0080ead0
void __thiscall cSPUILayeredObject_s0080_e6b0::dtor()
{
    u8* self = (u8*)this;
    vtbl = (void**)0x1417dc4;
    while (mModelsBegin != mModelsEnd) RemoveModel(*mModelsBegin);
    Fun_7c3ba0(mpViewer);
    if (mpViewer) { Fun_7c4000(mpViewer); GameFree(mpViewer); }
    mpViewer = 0;
    if (mpWindow) {
        if (flag74) { void* w = mpWindow; ((VF1v)VT(w)[0x108 / 4])(w, mpWinProc); }
        void* w = mpWindow;
        if (w) { mpWindow = 0; ((VF0v)VT(w)[1])(w); }
        flag74 = 0;
    }
    if (mpWinProc) { void* w = mpWinProc; mpWinProc = 0; ((VF0v)VT(w)[1])(w); }
    if (*(void**)(self + 0x28)) {
        void* o = *(void**)(self + 0x28);
        ((VF0v)VT(o)[1])(o);
    }
    // destroy model vector
    {
        u8* b = (u8*)mModelsBegin;
        u8* e = (u8*)mModelsEnd;
        for (; b < e; b += 4) { /* refcount release */ }
        void* p = mModelsBegin;
        if (p && ((u32*)p)[-1]) GameFree(p);
    }
    if (*(void**)(self + 0x10)) { void* o = *(void**)(self + 0x10); ((VF0v)VT(o)[1])(o); }
    if (*(void**)(self + 0xc)) { void* o = *(void**)(self + 0xc); ((VF0v)VT(o)[1])(o); }
    vtbl = (void**)0x13ec458;
}

// @ 0x0080ebc0
void* __thiscall cSPUICustomRendererImpl::ctor()
{
    u8* self = (u8*)this;
    vtbl = (void**)0x14426a0;
    vtbl2 = (void**)0x13ef094;
    atomic8 = 0;
    vtbl = (void**)0x1417df8;
    vtbl2 = (void**)0x1417df4;
    void* inl = self + 0x24;
    *(void**)(self + 0x1c) = inl;
    *(void**)(self + 0x10) = inl;
    *(void**)(self + 0xc) = inl;
    *(void**)(self + 0x14) = (u8*)inl + 0x3c;
    Fun_7c3f70(self + 0x60);
    *(u8*)(self + 0x24c) = 0;
    Fun_7c4dd0(self + 0x60, 0);
    return this;
}

// @ 0x0080ec40
void* __thiscall cSPUICustomRendererImpl::VectorDtor(u8 flags)
{
    u8* self = (u8*)this;
    vtbl = (void**)0x1417df8;
    vtbl2 = (void**)0x1417df4;
    Fun_7c3ba0(self + 0x60);
    Fun_7c4000(self + 0x60);
    mLayers.dtor();
    vtbl2 = (void**)0x13ef094;
    vtbl = (void**)0x13eb938;
    if (flags & 1) GameFree(this);
    return this;
}

// @ 0x0080eca0
void __thiscall cSPUICustomRendererImpl::ScalarDtor()
{
    u8* self = (u8*)this;
    vtbl = (void**)0x1417e18;
    vtbl2 = (void**)0x1417e14;
    if (p258) FUN_0080dbb0(this);
    if (p258) { void* o = p258; ((VF0v)VT(o)[1])(o); }
    if (p254) { void* o = p254; ((VF0v)VT(o)[1])(o); }
    if (p250) { void* o = p250; ((VF0v)VT(o)[1])(o); }
    vtbl = (void**)0x1417df8;
    vtbl2 = (void**)0x1417df4;
    Fun_7c3ba0(self + 0x60);
    Fun_7c4000(self + 0x60);
    mLayers.dtor();
    vtbl2 = (void**)0x13ef094;
    vtbl = (void**)0x13eb938;
}

// @ 0x0080ed50
void* __cdecl FUN_0080ed50()
{
    cSPUICustomRendererImpl* p = (cSPUICustomRendererImpl*)
        GameAlloc(0x264, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (!p) return 0;
    p->ctor();
    p->vtbl = (void**)0x1417e18;
    p->vtbl2 = (void**)0x1417e14;
    p->p250 = 0; p->p254 = 0; p->p258 = 0;
    return (u8*)p + 0x250;
}

// @ 0x0080edb0
UI_LayerManager* __thiscall UI_LayerManager::ctor()
{
    u8* self = (u8*)this;
    *(void**)(self + 4) = (void*)0x13ec458;
    *(u32*)(self + 8) = 0;
    vtbl = (void**)0x1417de4;
    *(void**)(self + 4) = (void*)0x1417dd4;
    *(u32*)(self + 0xc) = 0;
    *(u32*)(self + 0x10) = 0;
    *(u32*)(self + 0x14) = 0;
    *(u32*)(self + 0x20) = 0;
    *(u32*)(self + 0x24) = 0;
    *(u32*)(self + 0x28) = 0;
    *(u8*)(self + 0x34) = 0;
    *(u32*)(self + 0x38) = 0xffffffff;
    *(u32*)(self + 0x3c) = 0;
    void* inl = self + 0x58;
    *(void**)(self + 0x50) = inl;
    *(void**)(self + 0x44) = inl;
    *(void**)(self + 0x40) = inl;
    *(void**)(self + 0x48) = (u8*)inl + 0x3c;
    *(u8*)(self + 0x94) = 0;
    return this;
}

// @ 0x0080ee10
void* __thiscall UI_LayerManager::VectorDtor(u8 flags)
{
    u8* self = (u8*)this;
    vtbl = (void**)0x1417de4;
    *(void**)(self + 4) = (void*)0x1417dd4;
    Fun_8e2b20(self + 0x40);
    if (p3c) { void* o = p3c; ((VF0v)VT(o)[1])(o); }
    SharedVecDtor(self + 0x20);
    SharedVecDtor(self + 0xc);
    *(void**)(self + 4) = (void*)0x13ec458;
    vtbl = (void**)0x13eb938;
    if (flags & 1) GameFree(this);
    return this;
}

// @ 0x0080efe0
void __thiscall PtrVec::Insert1(void** pos, void** val)
{
    if (end != cap) {
        void** e = end;
        void** v = val;
        if (begin <= pos && pos < e) v = pos + 1;
        if (e) {
            void* o = e[-1];
            *e = o;
            if (o) ((VF0v)VT(o)[0])(o);
        }
        for (void** p = e - 1; p > pos; --p) p[0] = p[-1];
        void* nv = *v;
        void* ov = *pos;
        if (nv != ov) {
            if (nv) ((VF0v)VT(nv)[0])(nv);
            *pos = nv;
            if (ov) ((VF0v)VT(ov)[1])(ov);
        }
        end += 1;
        return;
    }
    u32 n = (u32)(end - begin);
    u32 nc = n ? n * 2 : 1;
    void** mem = nc ? (void**)GameAlloc(nc * 4, (const char*)0x13f6b3c, 0, 0, 0, 0) : 0;
    begin = mem; end = begin; cap = mem + nc;
}

// @ 0x0080f140
void __thiscall PtrVec::Insert12(void** pos, void** val)
{
    if (end != cap) {
        void** e = end;
        void** v = val;
        if (begin <= pos && pos < e) v = pos + 3;
        if (e) {
            void* o = e[-3];
            *e = o;
            if (o) ((VF0v)VT(o)[0])(o);
            e[1] = e[-2]; e[2] = e[-1];
        }
        (void)v;
        end += 3;
        return;
    }
    u32 n = (u32)(end - begin) / 3;
    u32 nc = n ? n * 2 : 1;
    void** mem = nc ? (void**)GameAlloc(nc * 0xc, (const char*)0x13f6b3c, 0, 0, 0, 0) : 0;
    (void)mem;
}

// @ 0x0080f2e0
void __fastcall FUN_0080f2e0(char* self, void** obj, void* a, void* b)
{
    void* o = obj ? *obj : 0;
    if (o) ((VF0v)VT(o)[0])(o);
    PtrVec* v = (PtrVec*)(self + 0xc);
    if (v->end < v->cap) {
        void** e = v->end;
        v->end = e + 3;
        if (e) {
            void* x = obj ? *obj : 0;
            *e = x;
            if (x) ((VF0v)VT(x)[0])(x);
            e[1] = a; e[2] = b;
        }
    } else {
        v->Insert12(v->end, obj);
    }
    void* x = obj ? *obj : 0;
    if (x) ((VF0v)VT(x)[1])(x);
}

// @ 0x0080f360
void __fastcall FUN_0080f360(char* p, void** obj, void* a, void* b)
{
    char* q = p ? p - 0xc : 0;
    FUN_0080f2e0(q, obj, a, b);
}

// @ 0x0080f380
void __thiscall cSPUICustomRendererImpl::MethodF380(void* param)
{
    p258 = param;
    void* m = ModelManagerGet();
    void* r = ((VF1)VT(m)[0x14 / 4])(m, param);
    if (r != p258) {
        void* old = p258;
        if (r) ((VF0v)VT(r)[0])(r);
        p258 = r;
        if (old) ((VF0v)VT(old)[1])(old);
    }
}

// @ 0x0080f530
void __fastcall FUN_0080f530(void* self, void* a)
{ (void)self; (void)a; }

// @ 0x0080f730
void __cdecl FUN_0080f730()
{}

// @ 0x0080f7c0
u32 __thiscall cSPUILayerManager::RemoveObject(cSPUILayeredObject_s0080_f7c0* p)
{
    u32 n = (u32)((u8*)mObjects.mEnd - (u8*)mObjects.mBegin) >> 2;
    for (u32 i = 0; i < n; ++i) {
        void** slot = &((void**)mObjects.mBegin)[i];
        if (*slot != p) continue;
        cSPUILayeredObject_s0080_f7c0* tmp = p;
        if (tmp) ((VF0v)VT(tmp)[1])(tmp);
        if (mRemoved.mEnd < mRemoved.mCap) {
            void** dst = (void**)mRemoved.mEnd;
            mRemoved.mEnd = (u8*)mRemoved.mEnd + 4;
            if (dst) {
                *dst = p;
                if (p) ((VF0v)VT(p)[1])(p);
            }
        } else {
            FUN_0080ee90(mRemoved.mEnd, &tmp);
            p = tmp;
        }
        if (tmp) ((VF0v)VT(tmp)[2])(tmp);
        if (p->mpWindow) {
            if (p->b74) ((VF1v)VT(p->mpWindow)[0x108 / 4])(p->mpWindow, p->mpWinProc);
            void* w = p->mpWindow;
            if (w) { p->mpWindow = 0; ((VF0v)VT(w)[1])(w); }
            p->b74 = 0;
        }
        u32 idx = (u32)((u8*)slot - (u8*)mObjects.mBegin) >> 2;
        void* last = ((void**)mObjects.mEnd)[-1];
        void* old = ((void**)mObjects.mBegin)[idx];
        if (last != old) {
            if (last) ((VF0v)VT(last)[1])(last);
            ((void**)mObjects.mBegin)[idx] = last;
            if (old) ((VF0v)VT(old)[2])(old);
        }
        mObjects.mEnd = (u8*)mObjects.mEnd - 4;
        void* tail = *(void**)mObjects.mEnd;
        if (tail) ((VF0v)VT(tail)[2])(tail);
        return 1;
    }
    return 0;
}

// @ 0x0080f8e0
void __thiscall cSPUILayerManager::RemoveAllObjects()
{
    while (mObjects.mBegin != mObjects.mEnd) {
        cSPUILayeredObject_s0080_f7c0* o = *(cSPUILayeredObject_s0080_f7c0**)mObjects.mBegin;
        RemoveObject(o);
    }
    mRemoved.erase(mRemoved.mBegin, mRemoved.mEnd);
}

// @ 0x0080f920
void __thiscall cSPUILayerManager::DrawLayer(void* a, void* b, void* c, void* d)
{
    void* mgr = EA_UTFWin_GetManager();
    if (!mgr) return;
    void* g = g_15fd918;
    if (g) {
        if (*(int*)(*(int*)((u8*)g + 0x3c) + 8) == 0) return;
    }
    if (b94 == 0) {
        b94 = 1;
    } else if (b94 == 1) {
        void* ms = SP_MessageServer();
        if (ms) {
            ms = SP_MessageServer();
            ((void(__thiscall*)(void*, u32, int, int))VT(ms)[0x14 / 4])(ms, 0x0366b9aa, 0, 0);
        }
        b94++;
    }
    mRemoved.erase(mRemoved.mBegin, mRemoved.mEnd);
    ((VF0v)VT(mgr)[0x28 / 4])(mgr);
    for (int i = 0; i < 0xf; ++i) {
        if (FUN_0082e700(i))
            ((ObjStub*)mgr)->doE6B0(i, c, d);
    }
    (void)a; (void)b;
}

// @ 0x0080f9d0
u32 __thiscall cSPUILayeredObject_s0080_f7c0::MethodF9D0(void* a, void* key)
{
    if (*(int*)((u8*)key + 8) == 0x12) {
        cSPUILayeredObject_s0080_f7c0* o = *(cSPUILayeredObject_s0080_f7c0**)((u8*)this + 0xc);
        if (o && *(int*)((u8*)o + 0xc) == (int)(size_t)a && o->b74) {
            void* bb = cSP_getA(o);
            ((u32(__thiscall*)(void*, void*))&FUN_0080f7c0_sym)(bb, this);
        }
    }
    return 0;
}

// @ 0x0080fa00
void __fastcall FUN_0080fa00(void* p)
{
    if (p) p = (u8*)((u32)p + 0xfffffdb0u);
    else   p = 0;
    ((ObjStub*)p)->go();
}

// @ 0x0080fa20
bool __thiscall cSPUILayerManager::Shutdown()
{
    if (b34) {
        void* o = FUN_0067dd50();
        ((void(__thiscall*)(void*, int))VT(o)[0x50 / 4])(o, 0x1e);
        RemoveAllObjects();
        void* base = mLayerInfos.mBegin;
        for (int i = 0; i < 0x3c; i += 4) {
            void* q = *(void**)((u8*)base + i);
            if (q) { *(void**)((u8*)base + i) = 0; ((VF0v)VT(q)[1])(q); }
        }
        mLayerInfos.erase(mLayerInfos.mBegin, mLayerInfos.mEnd);
        ((void(__thiscall*)(void*, int))VT(p3c)[0x134 / 4])(p3c, 0);
        void* q = p3c;
        if (q) { p3c = 0; ((VF0v)VT(q)[1])(q); }
        void* mm = SP_ModelManager();
        ((void(__thiscall*)(void*, unsigned int))VT(mm)[0x18 / 4])(mm, 0x032fab08);
        b34 = 0;
    }
    return true;
}

// @ 0x0080fac0
void* __thiscall cSPUILayeredObject_s0080_f7c0::MethodFAC0(void* a, void* b, void* cb)
{
    void* bb = cSP_getA(this);
    void* picked;
    if (mpWindow) {
        u32 local = 0x2710, local2 = 0xffffd8f0; u8 local3 = 0;
        (void)local2;
        cSP_getA(this);
        SPUIHelpers_VisitWindowTreeDepthFirst(mpWindow, &FUN_0080d6d0_sym, &local3);
        if (local < 0xf) picked = (void*)(*(int*)((u8*)bb + 0x40) + local * 4);
        else picked = 0;
    } else {
        picked = (void*)(*(int*)((u8*)bb + 0x40));
    }
    void* res;
    if (cb)
        res = ((void*(__cdecl*)(void*, void*, void*))cb)(a, b, *(void**)picked);
    else
        res = ((void*(__cdecl*)(void*, void*, void*))&FUN_0080d770_sym)(a, b, *(void**)picked);
    cMWModel_s0080_f7c0* m = (cMWModel_s0080_f7c0*)res;
    if (!m) return m;
    m->ref40++;
    // (remaining body: transform init + vector push) -- see partial.txt
    return m;
}

// @ 0x0080fc50
void* __thiscall cSPUILayeredObject_s0080_f7c0::AddModel(cMWModel_s0080_f7c0* m)
{
    if (!m) return m;
    m->f18 = 1.0f;
    for (int i = 0; i < 9; ++i) m->rot[i] = g_rot[i];
    m->tx = g_tx; m->ty = g_ty; m->tz = g_tz;
    m->w8 = 0; m->wa = 0;
    void* mm = SP_ModelManager();
    u32 grp = ((u32(__thiscall*)(void*, unsigned int, int))VT(mm)[0x28 / 4])(mm, 0x032fab27, 0);
    if (grp < 0x40)
        m->groups[grp >> 5] &= ~(1u << (grp & 0x1f));
    m->ref40++;
    if (mModels.mEnd < mModels.mCap) {
        void** dst = (void**)mModels.mEnd;
        mModels.mEnd = (u8*)mModels.mEnd + 4;
        if (dst) { *dst = m; m->ref40++; }
    } else {
        cMWModel_s0080_f7c0* tmp = m;
        ((void(__cdecl*)(void*, void*))&CountedPtr_sym)(mModels.mEnd, &tmp);
        m = tmp;
    }
    if (m) {
        if (m->ref40 > 1) m->ref40--;
        else ((void(__thiscall*)(void*, int))VT(m->vtbl)[0x170 / 4])(m, (int)((m->flags) >> 0x1f) & 1);
    }
    b77 = 1;
    m6c = 0.0f;
    return m;
}
