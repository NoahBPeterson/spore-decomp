// src/game/SPGonzago/SPUIMinimapWin.cpp -- migrated from slice(s) s00e10e30, s00e100e0, s00e0d100, s00e0f050, s00e0df70, s00e0c2a0, s00e0b350, s00e0a4c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIMinimapWin.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include <wchar.h>
#include <string.h>
#include <math.h>
#include <intrin.h>
#include "EA/UTFWin/Image.h"
#include "EA/UTFWin/Window.h"
#include "SP/cITerrainSphere.h"
#include "SP/cPlanetModel.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWin/Draw2D.h"
#include "EA/UTFWin/IWindow.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void*  __cdecl memcpy(void*, const void*, unsigned int);
extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl atan2(double, double);
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma warning(disable : 4100)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)

// ---- items of slice s00e0a4c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
struct Float3 { float x, y, z; };
struct cPaletteGrid;
float g_15a4bfc;
float g_15a4c00;
float g_16a2024;
float g_16a203c;
float g_15a4cb8;
u32   g_16a2028;
u32   g_16a202c;
u8    g_16a1fa0;
u32   g_16a2040;
u32   g_16a2044;
u32   g_16a2048;
u32   g_16a1f9c;
u32   g_16a1f98;
struct IWin;
struct ISlot {
    virtual void v00();
    virtual void v04();
    virtual void v08();
};
struct IWin {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void* v0C(u32 name);
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void* v1C();
    virtual void  v20();
    virtual void  v24();
    virtual void  v28();
    virtual void  v2C();
    virtual void  v30();
    virtual void  v34();
    virtual void* v38();
    virtual void  v3C();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual IWin* v4C();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58();
    virtual void  v5C();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6C(void* child);
    virtual void  v70(float x, float y);
    virtual void  v74();
    virtual void  v78();
    virtual void  v7C(int a, int b);
    virtual void  v80();
    virtual void  v84();
    virtual bool  v88(void* a, void* b);
    virtual void  v8C();
    virtual void  v90();
    virtual void  v94(void* p);
    virtual void  v98();
    virtual void  v9C();
    virtual void  vA0();
    virtual void  vA4();
    virtual void  vA8();
    virtual void  vAC();
    virtual void  vB0();
    virtual void  vB4();
    virtual void  vB8();
    virtual void  vBC();
    virtual void  vC0();
    virtual void  vC4();
    virtual void  vC8();
    virtual void  vCC();
    virtual void  vD0();
    virtual void  vD4();
    virtual void  vD8(void* child);
};
struct cHelper {
    void Set(float v, int index);                          // 0x0082e340
};
struct cObj95 {
    void Set(float v);                                     // 0x0095ed60
};
struct cRefVector {
    u32*  mBegin;
    u32*  mEnd;
    u32*  mCap;
    void  Reserve(u32 n);                                  // 0x00d01790
    void* erase(u32* first, u32* last);                    // 0x005c2170
    void  DoInsert(u32* pos, void** val);                  // 0x005c8480
};
struct cU32Vector {
    u32* mBegin;
    u32* mEnd;
    u32* mCap;
    void erase(u32* first, u32* last) {
        u32* e = mEnd;
        memcpy(first, last, (u32)((char*)e - (char*)last));
        mEnd -= (last - first);
    }
    void DoInsertValueI(u32* pos, const u32& val);          // 0x004558a0
    void DoAssign(const int* first, const int* last, u32 n);// 0x004d04f0
};
struct cPaletteGrid {
    u8 pad00[4];
    void* mWin4;            // +0x04
    void* mWin8;            // +0x08
    u32 mKey0C;             // +0x0c
    u32 mKey10;             // +0x10
    u32 mKey14;             // +0x14
    cRefVector mPages;      // +0x18
    u8 pad24[0x0c];
    cU32Vector mSel;        // +0x30
    u8 pad3C[0x20];
    u32 mHandler;           // +0x5c
    u32 mHandlerA0;         // +0x60
    u32 mHandlerA1;         // +0x64
    u32 mHandlerA2;         // +0x68
    u32 mHandlerA3;         // +0x6c
    u8 pad70[0x19c];
    IWin* mTarget;          // +0x20c
    u8 pad210[8];
    float m218;             // +0x218
    float m21C;             // +0x21c
    float m220;             // +0x220
    u8 pad224[0x15];
    u8 m239;                // +0x239
    u8 pad23A[2];
    int m23C;               // +0x23c
    u8 pad240[0x40];
    u8 mPal[0x81];          // +0x280
    u8 pad301[0x53];
    float m354;             // +0x354
    u8 pad358[4];
    u32 m35C;               // +0x35c
    u8 pad360[0x630];
    float m990;             // +0x990
    float m994;             // +0x994
    float m998;             // +0x998
    float m99C;             // +0x99c
    float m9A0;             // +0x9a0

    void FUN_00e09d10();    // 0x00e09d10
    bool LayoutCells();     // 0x00e0a270 (declared bool: callers return its eax)
    bool AddPages(u32 count); // 0x00e0a680
};
struct cPaletteGrid2 {
    u8 pad00[4];
    IWin mWin;              // +0x04
    u8 pad08[0x204];
    IWin* mTarget;          // +0x20c
};
__int64 __fastcall FUN_0093a3a0(void* ecx_this);
void*  __cdecl FUN_0067dd50();
float* __cdecl SPUIHelpers_GetBoundingScreenRect(float* out, IWin* win, char flag);
static float FUN_00e0af90_clamp(float v)
{
    if (v < -1.0f)
        v = -1.0f;
    if (v > 1.0f)
        v = 1.0f;
    return v;
}
// ---- items of slice s00e0a4c0 end

// ---- items of slice s00e0b350 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_00806370(void* p);                       // 0x00806370
void  __cdecl FUN_00806a60(void* a, void* b, int c, int d); // 0x00806a60
float* __cdecl FUN_00e0b350(float* out, void* a2, float* a3, float* a4, float f5, float* a6);
float* __cdecl FUN_00e0b580(float* out, void* a2, float* a3, float* a4, float* a5, float f6, void* a7);
float* __cdecl FUN_00e0b580b(void* out, void* in);          // 0x00e0b580 (2-arg view)
static inline float Call_E0AA80(void* p, float a, float b) {
    return ((float (__thiscall*)(void*, float, float))0x00e0aa80)(p, a, b);
}
void* __cdecl FUN_00b5b800();                              // 0x00b5b800
void* __cdecl FUN_00b3d350();                              // 0x00b3d350
void* __cdecl FUN_0067dd10();                              // 0x0067dd10  SP::App
static inline void RefAddRef(void* p) {
    ((void (__thiscall*)(void*))*((void***)*(void**)p + 0))(p);
}
static inline void RefRelease(void* p) {
    ((void (__thiscall*)(void*))*((void***)*(void**)p + 1))(p);
}
static inline void VT_90(void* p) {
    ((void (__thiscall*)(void*))*((void***)*(void**)p + 0x90 / 4))(p);
}
static inline void* VT_38(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0x38 / 4))(p);
}
static inline void VT_7C(void* p, int a, int b) {
    ((void (__thiscall*)(void*, int, int))*((void***)*(void**)p + 0x7c / 4))(p, a, b);
}
static inline void* VT_A8(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0xa8 / 4))(p);
}
static inline void VT_18(void* p, void* out, int a, int b) {
    ((void (__thiscall*)(void*, void*, int, int))*((void***)*(void**)p + 0x18 / 4))(p, out, a, b);
}
static inline void VT_74(void* p, float a, float b) {
    ((void (__thiscall*)(void*, float, float))*((void***)*(void**)p + 0x74 / 4))(p, a, b);
}
static inline void VT_EC(void* p, void* a) {
    ((void (__thiscall*)(void*, void*))*((void***)*(void**)p + 0xec / 4))(p, a);
}
static inline int VT_0C_0(void* p) {
    return ((int (__thiscall*)(void*))*((void***)*(void**)p + 0xc / 4))(p);
}
static inline void VT_8C(void* p) {
    ((void (__thiscall*)(void*))*((void***)*(void**)p + 0x8c / 4))(p);
}
struct ObjB {                     // 0x24 bytes, ref-counted pointer at 0x14
    u32   m0;
    float m4;
    float m8;
    float mC;
    u32   m10;
    void* mRef;
    float m18;
    u32   m1C;
    u32   m20;

    ObjB* FUN_00e0bd70(const ObjB& o);                 // 0x00e0bd70
};
struct ObjC {                     // 0x24 bytes, ref-counted pointer at 0x14
    u32   m0;
    u32   m4;
    u32   m8;
    u32   mC;
    u32   m10;
    void* mRef;
    float m18;
    u32   m1C;
    u32   m20;

    ObjC* FUN_00e0bdc0(const ObjC& o);                 // 0x00e0bdc0
};
struct cSPUIMinimapWin {
    void* mp000;                                       // 0x000
    void* mpObj4;                                      // 0x004  object (vtable at +4)
    char  pad008[0x1f8 - 0x08];
    float mF1F8;                                       // 0x1f8
    float mF1FC;                                       // 0x1fc
    char  pad200[0x218 - 0x200];
    float mF218;                                       // 0x218
    float mF21C;                                       // 0x21c
    float mF220;                                       // 0x220
    char  pad224[0x23c - 0x224];
    int   mI23C;                                       // 0x23c
    int   mI240;                                       // 0x240
    char  pad244[0x254 - 0x244];
    void* mpField254;                                  // 0x254
    void* mpField258;                                  // 0x258
    char  pad25C[0x280 - 0x25c];
    u8    mBytes280[0x84];                             // 0x280
    float mVec304[3];                                  // 0x304
    char  pad310[0x338 - 0x310];
    float mVec338[3];                                  // 0x338  icon position
    float mVec344[3];                                  // 0x344
    float mF350;                                       // 0x350
    char  pad354[0x35c - 0x354];
    u32   mFlags35C;                                   // 0x35c
    char  pad360[0x98c - 0x360];
    void* mpField98C;                                  // 0x98c  ref-counted

    void  FUN_00e0b970();                              // 0x00e0b970
    char  FUN_00e0bcb0(void* p2, float* out, void* p4); // 0x00e0bcb0
    void  FUN_00e0be50();                              // 0x00e0be50
    u32   FUN_00e0b990(float* p2, int p3, void* p4, char p5); // 0x00e0b990
    void  FUN_00e0c1f0(float* v);                      // 0x00e0c1f0
    void  ComputeIconPositionFromMinimapCoords(float* p2, void* p3, char p4); // 0x00e0bf40
};
// ---- items of slice s00e0b350 end

// ---- items of slice s00e0c2a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef float f32;
struct cRec14 {
    u32  mField00;                      // 0x00
    u32  mField04;                      // 0x04
    u8   mField08;                      // 0x08
    u8   mPad09[3];
    void* mpField0c;                    // 0x0c
    void* mpField10;                    // 0x10
};
struct cRec28 {
    u32  mField00;                      // 0x00
    u32  mField04;                      // 0x04
    u32  mField08;                      // 0x08
    u32  mField0c;                      // 0x0c
    u32  mField10;                      // 0x10
    u32  mField14;                      // 0x14
    void* mpField18;                    // 0x18
    u32  mField1c;                      // 0x1c
    u32  mField20;                      // 0x20
    u32  mField24;                      // 0x24
};
void  __fastcall FUN_00962740(void* p);                                    // 0x00962740
void  __cdecl FUN_00951330(void* p);                                       // 0x00951330
static inline void VT_00_0(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[0])(p);
}
static inline void VT_04_0(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[1])(p);
}
struct cRec28Copy {
    void* Copy(const u32* src, const u32* args);   // 0x00e0c610
};
struct cRec14Copy {
    void* Copy(const cRec14* src);      // 0x00e0c670
};
struct cRec28CopyB {
    void* Copy(const cRec28* src);      // 0x00e0c6b0
};
struct cTerrainRenderer {
    u8    mPad0000[0x20c];
    void* mpField20c;                   // 0x20c
    void* mpField210;                   // 0x210

    void* Destroy(u8 flags);            // 0x00e0c7d0
};
// ---- items of slice s00e0c2a0 end

// ---- items of slice s00e0df70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_1485720, g_13ec4b8, g_13f1160, g_141021c, g_13f2100;
extern unsigned char g_16a40b8;
extern int g_16a40bc;
extern unsigned g_16a40c0;
extern unsigned char g_16a40c8[];
extern unsigned g_16a38b8[];
extern const char g_147d84e[];                       // "...itorButtonBounceDuration"
extern const wchar_t g_147fb74[];                    // L"MinimapIcons"
extern const wchar_t g_147fb4c[];                    // L"ui_material_minimap"
extern const unsigned g_147f678[];                   // message id table
extern const char g_147fad0[], g_147fabc[], g_147fb90[], g_147fb38[], g_13f6b3c[];
struct Vector3 { float x, y, z; };
static inline void Release(void* p) {
    if (p) ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
}
static inline void AddRef(void* p) {
    if (p) ((void(__thiscall*)(void*))(*(void***)p)[0 / 4])(p);
}
struct DataInfo {
    u32   mKey;                  // +0x00
    char  pad_04[0x10];
};
struct RefHolder {
    void* mp0;                   // +0x00
    u8    b4;                    // +0x04
    char  pad_05[3];
    void* mp8;                   // +0x08
    void* mpc;                   // +0x0c
    RefHolder* Assign(const RefHolder& o);   // copy-assign (likely operator=; named so the checker can find it)
};
struct IRef0 {
    virtual void AddRef();
    virtual void Release();
};
struct IRef1 {
    virtual void v00();
    virtual void AddRef();
    virtual void Release();
};
struct Obj19 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void* f3(int id);
};
struct IWin_s00e0_df70 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual IWin_s00e0_df70* GetParent();
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
    virtual Obj19* f19();
    virtual void f20(int a);
    virtual void v15();
    virtual void v16();
    virtual void f23(int a);
    virtual void SetArea(const float* r);
    virtual void v19();
    virtual void v1a();
    virtual void v1b();
    virtual void v1c();
    virtual void v1d();
    virtual void v1e();
    virtual void f31(int a, int b);
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void f36();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v2a();
    virtual void f43(int a);
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
    virtual void AddChild(IWin_s00e0_df70* w);
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v3a();
    virtual void v3b();
    virtual IWin_s00e0_df70* GetChild(unsigned id, int flag);
};
struct ResMgr {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual bool Get(const unsigned* key, IRef0** out, int a, int b, int c, int d);
};
struct TexFactory {
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
    virtual void Register(void* tex);
    virtual void v0e();
    virtual void v0f();
    virtual struct TexObj* Create(int w, int h, int a, int b, int c, int d);
};
struct DistGrid {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual struct GridSub* f3();
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
    virtual const float* f51();
    virtual const float* f52();
};
struct MsgServer {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void Register(void* handler, int id);
};
struct IXfObj {
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
    virtual const Vector3* GetPos();
    virtual const void* GetRot();
};
struct MinimapVt {
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
    virtual void Refresh();
};
struct Matrix3 {
    Vector3 row0, row1, row2;
    Matrix3& Assign(const Matrix3& m);          // 0x41cb40
};
struct XForm {                      // PartTransform: flags, change counter, position, scale, basis
    unsigned short flags;           // +0
    unsigned short rev;             // +2
    Vector3 pos;                    // +4
    float scale;                    // +0x10
    Matrix3 m;                      // +0x14
    void Invert();                  // 0x40efa0 PartTransform::Invert
    void SetPos(const Vector3& p) {
        const int* src = (const int*)&p;
        int y = src[1];
        int x = src[0];
        int z = src[2];
        flags |= 4;
        rev++;
        ((int*)&pos)[1] = y;
        ((int*)&pos)[0] = x;
        ((int*)&pos)[2] = z;
    }
    void SetBasis(const Matrix3& b) { m = b; flags |= 2; rev++; }
};
struct LockInfo { void* data; int a, b, c, d, e, f; };
struct Tex {
    int Lock(int mode, int zero, LockInfo* out);    // 0x11ef750
    void Unlock(LockInfo* info);                    // 0x11ef880
};
struct TexObj { Tex* tex; unsigned flags; };
struct ResObj;
struct Image {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual ResObj* Find(const char* name);          // +0xc
    int f4;                                          // +4
    char pad8[0xc];
    void* GetAllocator();                            // 0x7f54d0
    Image(TexObj* t);                                // 0x8333b0 UI::Image::Image
};
struct TexImage : IRef0 {
    char pad4[0x28];
    TexImage(Image* img, int w, int h, float a, float b, float c, float d, int e);   // 0x9579f0
};
struct AllocObj { int pad; unsigned flags; int Fn46f260(); };
struct ResObj {
    AllocObj* GetAllocator();                        // 0x7f54d0 Resource::DatabasePackedFile::GetAllocator
};
struct Obj3Ret { void Fn82eb80(int a, void* alloc); };           // 0x82eb80
struct RefSlot {
    IRef0* p;
    void Assign(IRef0* v);                           // 0xb5f950 AutoRefCount::operator=
};
struct Layout : IRef1 {
    char pad4[0x14];
    Layout();                                        // 0x810000
    bool Init(const wchar_t* name, int a, int b, int c);   // 0x812160
    void SetVisibility(int v);                       // 0x810590
};
struct IconTree {
    char hdr[4];
    char sentinel[4];                                // +4 = end()
    void Find(void** out, const unsigned* key);      // 0xe5c780 eastl::rbtree::find
};
struct GridData : IRef0 { char pad4[0x18]; int count; char pad20[8]; int* table; };
struct GridSub { char pad[0x3c]; float f3c; };
struct PlanetModelObj { char pad[0x24]; int f24; };
struct Planet { char pad[0x13c]; struct PlanetSub* sub; };
struct PlanetSub { char pad[0xb4]; float f; };
extern const Matrix3 g_16a2070;                      // 0x16a2070
ResMgr*     __cdecl EA_GetManager();                 // 0x67dcd0
TexFactory* __cdecl GetTexFactory();                 // 0x67dd60
MsgServer*  __cdecl SP_MessageServer();              // 0x67dcc0
void        __cdecl FUN_00b3d460();
int         __cdecl GetUniverseContext();            // 0x1021080
Planet*     __cdecl GetActivePlanet();               // 0x1021260
PlanetModelObj* __cdecl PlanetModel();               // 0xb3d350
DistGrid*   __cdecl DebugDrawGrid();                 // 0xf48aa0
int         __cdecl GetCurrentGameMode();            // 0xb5b800
const void* __cdecl Matrix3FromQuaternion(void* out, const void* q);   // 0x59c190
Vector3*    __cdecl normalized_safe(Vector3* out, const Vector3* in);   // 0x449c20
void        __cdecl FUN_00957c20(Image* img, int a);
void        __cdecl UpdatePallete(unsigned* pal, int a, unsigned c1, unsigned c2, int v, int mode);   // 0xe0ad10
void        __cdecl FUN_00e0cba0(const float* a, const void* b, int c, int d, const float* e);
void        __cdecl FUN_00e0c820(const float* a, const void* b, int c, int d, const float* e, float f, bool g);
const float* __cdecl FUN_00e0b580(void* out, int a, const Vector3* v, const float* b, const float* c, float f, int g);
IRef0*      __cdecl GetImageFromLayout(Layout* l, unsigned id);   // 0x8061c0
void        __cdecl SetWindowSPMaterial(IWin_s00e0_df70* w, const wchar_t* name, int a);   // 0x808ad0
void*       __cdecl FUN_009512c0();
void        __cdecl AnchorWindowToWindow(IWin_s00e0_df70* a, IWin_s00e0_df70* b, int flags, int c);    // 0x807340
void*       __cdecl memset(void* p, int v, unsigned n);
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);
struct PerfCount { unsigned lo, hi; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(PerfCount* c);
struct CursorAttachment : IRef0 {
    char pad4[0xac];
    CursorAttachment();                              // 0xe2b8e0
};
struct CamBase1 { virtual void AddRef(); virtual void Release(); };
struct WinBase : CamBase1, IWin_s00e0_df70 {
    WinBase();                                       // 0x962a10 EA::UTFWin::Window::Window
    char pad_win[0x20c - 8];
};
struct MinimapWin;
struct MinimapCamera : WinBase {
    int f20c;                                        // +0x20c
    int f210;                                        // +0x210
    virtual void AddRef();
    virtual void Release();
    virtual IWin_s00e0_df70* GetParent();
    MinimapCamera() : f20c(0), f210(0) { ((void(__thiscall*)(void*))(*(void***)this)[0])(this); }
    void SetOwner(MinimapWin* w);                    // 0xe0b230
};
void* __cdecl operator new(unsigned int, int, const char*, void*);
typedef void (__thiscall *VSlot)(void*);
static __forceinline void CallSlot(void* p, int i) { ((VSlot)(*(void***)p)[i])(p); }
struct MinimapWin : MinimapVt, IWin_s00e0_df70 {
    char pad_008[0x214 - 8];
    char handler[0x10];             // +0x214  EA::Messaging::AutoHandler
    void* msgServer;                // +0x224
    void* handlerPtr;               // +0x228
    const unsigned* msgTable;       // +0x22c
    int msgCount;                   // +0x230
    int m234;                       // +0x234
    char pad_238;
    unsigned char squareRaster;     // +0x239
    char pad_23a[2];
    int width;                      // +0x23c
    int height;                     // +0x240
    IRef0* mRoadIcon;               // +0x244
    IRef0* mMapImage;               // +0x248
    RefSlot mTexture;               // +0x24c
    IRef0* mIconImage;              // +0x250
    IRef0* mCamera;                 // +0x254
    Layout* mLayout;                // +0x258
    char pad_25c[4];
    unsigned swLo;                  // +0x260
    unsigned swHi;                  // +0x264
    int m268;                       // +0x268
    int m26c;                       // +0x26c
    int swMode;                     // +0x270
    char pad_274[8];
    Image* mImage;                  // +0x27c
    unsigned char edge[0x81];       // +0x280
    char pad_301[0x31c - 0x301];
    IconTree tree;                  // +0x31c
    char pad_324[0x338 - 0x324];
    float m338[3];                  // +0x338
    float m344[3];                  // +0x344
    float m350;                     // +0x350
    char pad_354[4];
    int m358;                       // +0x358
    unsigned m35c;                  // +0x35c
    int m360;                       // +0x360
    unsigned char b364;             // +0x364
    char pad_365[0x984 - 0x365];
    GridData* mGrid;                // +0x984
    IRef0* mCursor;                 // +0x988

    bool FindIcon(unsigned id, const float* dir, bool flag);          // 0xe0df70
    void Update();                                                    // 0xe1a0
    void build_edge_offsets();                                        // 0xe840
    bool Init();                                                      // 0xeab0
    bool Initialize();                                                // 0xb1fbf0 UTFWin::Window::Initialize
    void FUN_e0bcb0(const float* a, const float* b, float* c);        // 0xe0bcb0
    void ComputeIconPositionFromMinimapCoords(const float* c, IWin_s00e0_df70* w, bool f);   // 0xe0bf40
    void FUN_e0d100(IWin_s00e0_df70* w, float f, const float* p, const float* q);            // 0xe0d100
};
struct ImgInfo { virtual void v0(); virtual void GetInfo(int* w, int* h, unsigned char** d); };
struct IconNode { char pad[0x18]; float vec[3]; };
static inline int FtoI(float f) { return (int)f; }
// ---- items of slice s00e0df70 end

// ---- items of slice s00e0f050 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cRefCounted {
public:
    virtual void r00();                                  // +0x00
    virtual void Release();                              // +0x04
};
struct cIconNode {
    uint8_t         pad000[0x10];                        // +0x00 .. +0x0f
    uint32_t        mIconId;                             // +0x10
    uint8_t         pad014[0x14];                        // +0x14 .. +0x27
    cRefCounted*    mpValue;                             // +0x28
};
struct cRBTreeHeader {
    uint8_t pad000[0x10];                                // +0x00 .. +0x0f
};
void* __cdecl RBTreeIncrement(cIconNode* pNode);         // 0x00921580
void  __cdecl RBTreeErase(cIconNode* pNode, cRBTreeHeader* pTree); // 0x00921880
void  __cdecl operator_delete_array(void* p);            // 0x00f47380
class cIconTree {
public:
    uint8_t         pad000[4];                           // +0x00
    cRBTreeHeader   mTree;                               // +0x04
    int32_t         mCount;                              // +0x14

    void FUN_00e0f1a0(cIconNode** ppOut, cIconNode* pNode);
};
class cSPUIMinimapWin_s00e0_f050 {
public:
    void FUN_00e0f050();
    void FUN_00e0f100(float a1, float a2, float a3, float a4);
    void FUN_00e0f1a0();
    void draw_civilization_borders();  // 0x00e0f2c0 (cSPUIMinimapWin::draw_civilization_borders)
    ~cSPUIMinimapWin_s00e0_f050();
    bool RemoveIcon(uint32_t iconId, int first, int flags);  // 0x00e0f9c0 (cSPUIMinimapWin::RemoveIcon)
    bool RemoveAllIcons();  // 0x00e0fb50 (cSPUIMinimapWin::RemoveAllIcons)
    void FUN_00e0fb90(uint32_t mask);
    void CRG_Minimap();
    void FUN_00e0ff80();

    uint8_t         pad000[0x324];                       // +0x000 .. +0x323
    cIconNode*      mpFirstIcon;                         // +0x324
    uint8_t         pad328[8];                           // +0x328 .. +0x32f
    uint32_t        mIconCount;                          // +0x330
};
// ---- items of slice s00e0f050 end

// ---- items of slice s00e0d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float GetElapsedSeconds();                                    // 0x00805080
extern "C" void PlayEvent(void* pHandle, float a, float b, int tag);     // 0x00b69aa0
extern float    g_fxThreshold;                                           // 0x015a4cb8
extern float    g_fxScale;                                               // 0x016a203c
extern float    g_lastDirX, g_lastDirY, g_lastDirZ;                      // 0x016a1fa4 / a8 / ac
struct Vec3 { float x, y, z; };
struct Vec2 { float x, y; };
struct Image_s00e0_d100 { char pad[0x1c]; int mW; int mH; };
struct Vertex2D {                       // 0x14 bytes
    float x, y;
    unsigned int color;
    float u, v;
};
struct Target2D {                       // returned by RenderContext::Begin2D
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
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
    virtual void DrawQuads(Vertex2D* v, int count, Image_s00e0_d100* img);          // +0x54, ret 0xc
};
struct RenderContext {
    Target2D* Begin2D(int);             // 0x95bc10
    void End2D();                       // 0x95bb20
};
struct MapSet;
struct ITerrain {
    virtual int AddRef();
    virtual int Release();
    virtual void* GetPropertyList();
    virtual MapSet* GetTerrainMapSet();                                  // +0xc
};
struct PlanetModel_s00e0_d100 {
    char pad[0x24]; ITerrain* mpTerrain;
    Vec3* DirectionToSurfacePosition(const Vec3* pDir, Vec3* pOut);     // 0xb815a0 (thiscall ret 8)
};
PlanetModel_s00e0_d100* GetPlanetModel();                                           // 0xb3d350 (SP::PlanetModel)
extern "C" unsigned int GetCurrentGameMode_s00e0_d100();                            // 0xb5b800 (SP::GetCurrentGameMode)
extern "C" Vec2* ProjectToUV(Vec2* out, MapSet* ms, const Vec3* pos, const Vec3* a, const Vec3* b, float scale, int flag); // 0x00e0b580
struct MinimapWin_s00e0_d100 {
    char pad0[0x23c];
    int mW;                             // +0x23c
    int mH;                             // +0x240
    char pad1[0x250 - 0x244];
    Image_s00e0_d100* mpImage;                     // +0x250
    char pad2[0x304 - 0x254];
    Vec3 mCenter;                       // +0x304
    Vec3 mUp;                           // +0x310
    char pad3[0x338 - 0x31c];
    Vec3 mAxisA;                        // +0x338
    Vec3 mAxisB;                        // +0x344
    float mScale;                       // +0x350

    bool ProjectCenter(const Vec3* pos, Vec2* out, int flag);           // 0xe0bcb0 (thiscall ret 0xc)
    float RemapX(float x, float y);                                      // 0xe0aa80 (thiscall ret 8, float in ST0)
    bool DrawCameraArrow(RenderContext* ctx, int unused);  // 0x00e0d2e0 (MinimapWin::DrawCameraArrow)
};
static __forceinline float WrapNearest(float x, float ref) {
    float c = x - 1.0f;
    if (fabs(x - ref) <= fabs(c - ref)) {
        c = x;
        if (fabs((x + 1.0f) - ref) < fabs(x - ref)) c = x + 1.0f;
    }
    return c;
}
struct IMinimapIcon;                     // icon / window object drawn on the minimap
struct IMinimapIcon {                    // vtable slots used by this slice
    virtual void s00();                  // +0x00
    virtual void s04();                  // +0x04
    virtual void s08();                  // +0x08
    virtual void s0c();                  // +0x0c
    virtual IMinimapIcon* s10();         // +0x10 parent
    virtual void s14();                  // +0x14
    virtual void s18();                  // +0x18
    virtual void s1c();                  // +0x1c
    virtual void s20();                  // +0x20
    virtual void s24();                  // +0x24
    virtual bool s28();                  // +0x28 is-visible
    virtual void s2c();                  // +0x2c
    virtual void s30();                  // +0x30
    virtual void s34();                  // +0x34
    virtual const float* s38();          // +0x38 quad (4 floats)
    virtual void s3c();                  // +0x3c
    virtual void s40();                  // +0x40
    virtual void s44();                  // +0x44
    virtual void s48();                  // +0x48
    virtual void s4c();                  // +0x4c
    virtual void s50();                  // +0x50
    virtual void s54();                  // +0x54
    virtual void s58();                  // +0x58
    virtual void s5c();                  // +0x5c
    virtual void s60();                  // +0x60
    virtual void s64();                  // +0x64
    virtual void s68();                  // +0x68
    virtual void s6c(float* pQuad);      // +0x6c set quad
    virtual void s70();                  // +0x70
    virtual void s74();                  // +0x74
    virtual void s78();                  // +0x78
    virtual void s7c(int a, int b);      // +0x7c set visible
    virtual void s80();                  // +0x80
    virtual void s84();                  // +0x84
    virtual void s88();                  // +0x88
    virtual void s8c();                  // +0x8c
    virtual void s90();                  // +0x90
    virtual void s94();                  // +0x94
    virtual void s98();                  // +0x98
    virtual void s9c();                  // +0x9c
    virtual void sa0();                  // +0xa0
    virtual void sa4();                  // +0xa4
    virtual void sa8();                  // +0xa8
    virtual void sac();                  // +0xac
    virtual void sb0();                  // +0xb0
    virtual void sb4();                  // +0xb4
    virtual void sb8();                  // +0xb8
    virtual void sbc();                  // +0xbc
    virtual void sc0(Vec2 size, float* pOut);   // +0xc0
    virtual void sc4();                  // +0xc4
    virtual void sc8();                  // +0xc8
    virtual void scc();                  // +0xcc
    virtual void sd0();                  // +0xd0
    virtual void sd4();                  // +0xd4
    virtual void sd8();                  // +0xd8
    virtual void sdc();                  // +0xdc
    virtual void se0(IMinimapIcon* pIcon);      // +0xe0 detach parent
    virtual void se4();                  // +0xe4
    virtual void se8();                  // +0xe8
    virtual void sec(IMinimapIcon* pIcon);      // +0xec attach
    virtual IMinimapIcon* sf0(uint32_t id, int flag);   // +0xf0 lookup icon by id
};
struct IDirectionProvider {              // subobject holding the surface direction
    virtual void d00();                  // +0x00
    virtual void d04();                  // +0x04
    virtual void d08();                  // +0x08
    virtual void d0c();                  // +0x0c
    virtual void d10();                  // +0x10
    virtual void d14();                  // +0x14
    virtual void d18();                  // +0x18
    virtual void d1c();                  // +0x1c
    virtual void d20();                  // +0x20
    virtual void d24();                  // +0x24
    virtual void d28();                  // +0x28
    virtual const Vec3* GetDirection();  // +0x2c
};
struct IMinimapTargetA {                 // feedback target, direction subobject at +0x34
    virtual void a00();                  // +0x00
    virtual void a04();                  // +0x04
    virtual void a08();                  // +0x08
    virtual void* Find(uint32_t id);     // +0x0c
    char pad_010[0x24];                  // +0x10
    IDirectionProvider mDirection;       // +0x34
};
struct IMinimapTargetB {                 // feedback target, direction subobject at +0xc0
    virtual void b00();                  // +0x00
    virtual void b04();                  // +0x04
    virtual void b08();                  // +0x08
    virtual void* Find(uint32_t id);     // +0x0c
    char pad_010[0xb0];                  // +0x10
    IDirectionProvider mDirection;       // +0xc0
};
struct IMinimapTargetC {                 // feedback target exposing its event mode
    virtual void c00();                  // +0x00
    virtual void c04();                  // +0x04
    virtual void c08();                  // +0x08
    virtual void* Find(uint32_t id);     // +0x0c
    virtual void c10();                  // +0x10
    virtual void c14();                  // +0x14
    virtual void c18();                  // +0x18
    virtual void c1c();                  // +0x1c
    virtual void* GetMode();             // +0x20
};
struct IMinimapView {                    // current minimap view
    virtual void v00();                  // +0x00
    virtual void v04();                  // +0x04
    virtual void v08();                  // +0x08
    virtual void v0c();                  // +0x0c
    virtual void v10();                  // +0x10
    virtual void v14();                  // +0x14
    virtual void v18();                  // +0x18
    virtual float GetAngle();            // +0x1c
    virtual void* GetMode();             // +0x20
};
struct IWindowManager {                  // SP::WindowManager()
    virtual void w00();                  // +0x00
    virtual void w04();                  // +0x04
    virtual void w08();                  // +0x08
    virtual void w0c();                  // +0x0c
    virtual void w10();                  // +0x10
    virtual void w14();                  // +0x14
    virtual void w18();                  // +0x18
    virtual void w1c();                  // +0x1c
    virtual void w20();                  // +0x20
    virtual void w24();                  // +0x24
    virtual void w28();                  // +0x28
    virtual void w2c();                  // +0x2c
    virtual void w30();                  // +0x30
    virtual void w34();                  // +0x34
    virtual void w38();                  // +0x38
    virtual void w3c();                  // +0x3c
    virtual void w40();                  // +0x40
    virtual void w44();                  // +0x44
    virtual IMinimapView* GetView(int which);   // +0x48
};
struct IMapSetProjection {               // ITerrain slot +0x0c is variadic (0 or 4 args)
    virtual void p00();                  // +0x00
    virtual void p04();                  // +0x04
    virtual void p08();                  // +0x08
    virtual Vec2* Project(Vec2* pUV, const Vec3* pA, const Vec3* pB, float scale);  // +0x0c
};
struct MinimapEventNode;                 // eastl rbtree node (event id + feedback event)
struct MinimapEventTree {                // eastl::rbtree keyed by the event id
    uint32_t          mSize;             // +0x00 (not touched here)
    MinimapEventNode* mpRoot;            // +0x04 anchor: parent (end iterator)
    MinimapEventNode* mpBegin;           // +0x08 anchor: leftmost node
    MinimapEventNode* mpEnd;             // +0x0c anchor: rightmost node
    uint32_t          mColor;            // +0x10 anchor: colour
    MinimapEventNode* find(MinimapEventNode** pFound, const void* pKey);  // 0x00e5c780
};
struct cFeedbackEvent;                   // feedback event payload (only referenced here)
struct AutoRefCountEvent {               // EA::AutoRefCount<cFeedbackEvent> (4 bytes)
    cFeedbackEvent* mpEvent;             // +0x00
};
struct MinimapEventNode {
    MinimapEventNode* mpParent;          // +0x00
    MinimapEventNode* mpLeft;            // +0x04
    MinimapEventNode* mpRight;           // +0x08
    uint32_t          mColor;            // +0x0c
    uint32_t          mKey;              // +0x10
    AutoRefCountEvent mEvent;            // +0x14
    Vec3              mPos;              // +0x18 direction of the event on the surface
    uint32_t          mFlags;            // +0x24
    IMinimapTargetA*  mpTarget;          // +0x28
    float             mTime;             // +0x2c
    uint32_t          mState;            // +0x30
};
struct cMinimapOverlay {                 // cSPUIMinimapWin (retail layout)
    char             pad_000[4];         // +0x000
    IMinimapIcon     mWindow;            // +0x004 polymorphic window subobject
    char             pad_008[0x230];     // +0x008
    uint8_t          mIconsHidden;       // +0x238
    char             pad_239[3];         // +0x239
    int32_t          mW;                 // +0x23c
    int32_t          mH;                 // +0x240
    char             pad_244[0xc];       // +0x244
    Image_s00e0_d100*           mpImage;            // +0x250
    char             pad_254[0xc8];      // +0x254
    MinimapEventTree mEvents;            // +0x31c
    char             pad_330[8];         // +0x330
    Vec3             mAxisA;             // +0x338
    Vec3             mAxisB;             // +0x344
    float            mScale;             // +0x350
    char             pad_354[0x638];     // +0x354
    IMinimapIcon*    mpIcon;             // +0x98c

    void DrawIcon(void* pWindow, float angle, void* pOwner);                  // 0x00e0d100
    bool ProjectEvent(const Vec2* pMapPos, Vec3* pOut);                       // 0x00e0de40
    AutoRefCountEvent* FindEvent(uint32_t key);                               // 0x00e0df30
    uint32_t OnTick();                                                        // 0x00e0d940

    float AngleFromPoint(float x, float y);                                   // 0x00e0a9e0
    void ComputeIconPositionFromMinimapCoords(const void* pPos, IMinimapIcon* pIcon, int flag);  // 0xe0bf40
    bool ProjectCenter(const Vec3* pPos, Vec2* pOut, int flag);               // 0xe0bcb0
    void RefreshEffects(const void* pData, uint32_t a, uint32_t b, int c);    // 0xe0b990
};
extern "C" Vec3* ExpandCoord(Vec3* pOut, const Vec2* pUV);               // 0x00e0cea0 (returns pOut)
extern "C" MinimapEventNode* RBTreeIncrement_s00e0_d100(MinimapEventNode* pNode);   // 0x00921580
extern "C" IWindowManager* WindowManager();                              // 0x0067caa0
extern "C" void* EventAction(IMinimapTargetC* pTarget, const void* pEventId);   // 0x00ac80d0
struct Stopwatch { __int64 GetElapsed(); };                              // 0x0093a3a0
extern Stopwatch g_minimapStopwatch;                                     // 0x016a2028
extern uint32_t g_swLo, g_swHi;                                          // 0x016a2028 / 0x016a202c
extern uint8_t  g_fxEnabled;                                             // 0x016a1fa0
extern uint32_t g_fxA, g_fxB;                                            // 0x016a1f9c / 0x016a1f98
extern uint8_t  g_fxData[];                                              // 0x016a2040
// ---- items of slice s00e0d100 end

// ---- items of slice s00e100e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtWinButton0[];          // 0x0147f868
extern void* g_vtWinButton1[];          // 0x0147f748
extern void* g_vtWinButton2[];          // 0x0147f6d8
extern void* g_vtDrawable0[];           // 0x0141788c
extern void* g_vtDrawable1[];           // 0x01417874
extern void* g_vtDrawable2[];           // 0x0141785c
extern const char g_cityIconName[];     // "UI/CivMinimap/CityIcon"
extern const char g_cityIconDrawableName[];
extern const float g_epsilon;           // 0x013ec4b8
extern const float g_half;              // 0x01471064 = 0.5
inline void* operator new(unsigned int, void* p) { return p; }
namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle() {}
    __forceinline Rectangle(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
};
}
class IQueried {                        // returned by RefObject slot +0x0c
public:
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
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual bool IsMinimapObject();     // +0x58
};
class IQueryable {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual IQueried* Query(uint32_t typeID);    // +0x0c
};
struct cIconInfo {                      // size 0x24
    uint32_t mType;                     // +0x00
    float mX, mY, mZ;                   // +0x04 direction
    uint32_t mFlags;                    // +0x10
    IQueryable* mpObject;               // +0x14 (ref counted)
    float mTimeout;                     // +0x18
    uint32_t mAnimState;                // +0x1c
    uint32_t mImageID;                  // +0x20
    __forceinline cIconInfo(const cIconInfo& o)
        : mType(o.mType), mX(o.mX), mY(o.mY), mZ(o.mZ), mFlags(o.mFlags), mpObject(o.mpObject),
          mTimeout(o.mTimeout), mAnimState(o.mAnimState), mImageID(o.mImageID)
    {
        if (mpObject)
            mpObject->AddRef();
    }
    __forceinline ~cIconInfo()
    {
        if (mpObject)
            mpObject->Release();
    }
    cIconInfo& operator=(const cIconInfo& o);        // 0x00e0bdc0
};
class Image_s00e1_00e0 {
public:
    virtual int AddRef();
    virtual int Release();  // 0x00957550 (Image::Release)
    uint32_t pad[7];
    int mWidth;                         // +0x20
};
class IWin_s00e1_00e0 {
public:
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
    virtual const float* GetArea();                         // +0x38
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual void v4c();
    virtual void SetID(uint32_t id);                        // +0x50
virtual void v54();
virtual void v58();
    virtual void SetColor(uint32_t color);                  // +0x5c
    virtual void SetArea(const Math::Rectangle* r);         // +0x60
    virtual void v64();
    virtual void SetSize(float w, float h);                 // +0x68
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
    virtual void SetFlag(int flag, int enable);             // +0x7c
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
    virtual void SetVisible(int v);                         // +0xac
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
    virtual bool AddChild(IWin_s00e1_00e0* child);                     // +0xd8
virtual void vdc();
virtual void ve0();
virtual void ve4();
    virtual void PlaceAfter(IWin_s00e1_00e0* child);                   // +0xe8
    virtual void PlaceBefore(IWin_s00e1_00e0* child);                  // +0xec
    virtual IWin_s00e1_00e0* GetChild(int id, int recurse);            // +0xf0
};
class IButtonControl {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual IWin_s00e1_00e0* GetWindow();                              // +0x10
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
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
    virtual void SetDrawable(void* drawable);               // +0x60
};
class IDrawableSize {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void SetSize(const float* size, int a, int b);  // +0x18
};
class IDrawable {                       // drawable's third interface (object offset +0x0c)
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual IDrawableSize* GetSizeIface();                  // +0x10
    virtual void SetImage(Image_s00e1_00e0* image, int a);             // +0x14
};
struct WinButtonObj {
    void** vt0;
    void** vt1;
    uint32_t pad[0x204 / 4 - 1];
    void** vt2;                         // +0x20c
    WinButtonObj();                     // 0x00966f90 UI::WinButton::WinButton
};
struct DrawableObj {
    void** vt0;
    void** vt1;
    void** vt2;                         // +0x08 (interface at +0x0c in retail)
    DrawableObj();                      // 0x00966dc0 ButtonDrawableRadio::ButtonDrawableRadio
};
class cApp {
public:
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
    virtual uint32_t GetGameMode();                         // +0x38
};
cApp* __cdecl App();                                        // 0x0067dd10
Image_s00e1_00e0* __cdecl GetImageFromLayout(void* layout, uint32_t id);   // 0x008061c0
void* __cdecl GetAllocator();                               // 0x009512c0
void* __cdecl TooltipAlloc(unsigned size, unsigned align, const char* name, void* alloc);   // 0x009512d0
void __cdecl FitWindowToArea(IWin_s00e1_00e0* w, const Math::Rectangle* r);    // 0x00806d10
struct IconTree_s00e1_00e0 {
    cIconInfo& At(const uint32_t& key);                     // 0x00e0ff80 (map::operator[])
};
class MinimapVt_s00e1_00e0 {
public:
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
};
class cSPUIMinimapWin_s00e1_00e0 : public MinimapVt_s00e1_00e0, public IWin_s00e1_00e0 {
public:
    uint32_t pad_008[(0x258 - 8) / 4];
    void* mpLayout;                     // +0x258
    uint32_t pad_25c[(0x31c - 0x25c) / 4];
    IconTree_s00e1_00e0 mIconInfos;                // +0x31c
    uint32_t pad_320[(0x364 - 0x320) / 4 - 1];
    bool mbTradeRoutesDirty;            // +0x364 (byte at +0x364)

    void FUN_e0bcb0(const float* pos, const float* out, float* extra);     // 0x00e0bcb0
    void ComputeIconPositionFromMinimapCoords(const float* c, IWin_s00e1_00e0* w, bool f);   // 0x00e0bf40
    void FUN_e0d100(IWin_s00e1_00e0* w, float f, const float* p);                     // 0x00e0d100
    IWin_s00e1_00e0* SubWin() { return (IWin_s00e1_00e0*)((char*)this + 4); }
    bool AddIcon(uint32_t id, const cIconInfo* info, int parentID, bool flag);  // 0x00e10580 (cSPUIMinimapWin::AddIcon)
};
static __forceinline uint32_t PickImageID(uint32_t f, uint32_t mode, uint32_t infoImage)
{
    uint32_t id = infoImage;
    if (f & 1) {
        id = (f & 8) ? 0x5e51b64 : 0x5e51b58;
    } else if (f & 2) {
        if (f & 8)
            id = 0x5e51b4c;
        else
            id = ((f & 0x100000) ? 10 : 0) + 0x5e51b25;
    } else if (f & 0x1000) {
        id = 0x5e51b2f;
    } else if (f & 0x10) {
        id = ((f & 8) ? 0xb : 0) + 0x5e51aef;
    } else if (f & 0x40000) {
        id = 0x5e51b03;
    } else if (f & 0x20) {
        if (f & 8) {
            if (mode != 0x1654c10)
                id = 0x5e51bd7;
        } else if (f & 0x80000) {
            id = 0xccd1f01e;
        } else if (f & 0x100000) {
            id = 0x71abd9ca;
        } else {
            id = ((f & 0x200000) ? 0xadb5da70 : 0) + 0x5e51bce;
        }
    } else if (f & 0x40) {
        if (f & 8)
            id = 0x5e51b19;
        else
            id = ((mode != 0x1654c10) ? 0xfe415759 : 0) + 0x7a3c3c0;
    } else if (f & 0x80) {
        if (mode != 0x1654c10)
            id = 0x5e51b25;
    } else if (f & 0x100) {
        id = 0x5e51aef;
    } else if (f & 0x2000) {
        id = 0x5e51b19;
    } else if (f & 0x4000) {
        id = 0x5e51ad8;
    } else if (f & 0x10000) {
        id = 0x5e51bb6;
    } else if (f & 0x8000) {
        id = 0x5e51bc1;
    } else {
        id = ((f & 0x20000) ? 0x122 : 0) + 0x5e51ad8;
    }
    return id;
}
// ---- items of slice s00e100e0 end

// ---- items of slice s00e10e30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector2 {
    float x, y;
};
struct Vector3_s00e1_0e30 {
    float x, y, z;
    Vector3_s00e1_0e30() {}
    Vector3_s00e1_0e30(float a, float b, float c) : x(a), y(b), z(c) {}
};
namespace Math {
struct Rectangle_s00e1_0e30 {
    float x1, y1, x2, y2;
    Rectangle_s00e1_0e30() {}
    Rectangle_s00e1_0e30(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
};
}
struct Vector3Vector {
    Vector3_s00e1_0e30* mpBegin;
    Vector3_s00e1_0e30* mpEnd;
    Vector3_s00e1_0e30* mpCapacity;
    uint32_t mAllocator[2];

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    Vector3_s00e1_0e30* begin() { return mpBegin; }
    Vector3_s00e1_0e30* end() { return mpEnd; }
    Vector3_s00e1_0e30& operator[](uint32_t i) { return mpBegin[i]; }
    Vector3_s00e1_0e30* erase(Vector3_s00e1_0e30* first, Vector3_s00e1_0e30* last);          // 0x0050f740
    void DoInsertValue(Vector3_s00e1_0e30* position, const Vector3_s00e1_0e30& value);   // 0x004b5ad0
    void push_back(const Vector3_s00e1_0e30& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) Vector3_s00e1_0e30(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void clear() { erase(mpBegin, mpEnd); }
};
namespace EA {
namespace UTFWin {
class Image_s00e1_0e30;
}
}
namespace EA {
namespace UTFWin {
class Draw2D_s00e1_0e30 {
public:
    virtual void v00();
    virtual void SetColor(uint32_t color);                                      // +0x04
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
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual void DrawImage(const Math::Rectangle_s00e1_0e30& area, Image_s00e1_0e30* image,
                           const Math::Rectangle_s00e1_0e30& uv);                         // +0x58
};
}
}
namespace EA {
namespace UTFWin {
class RenderContext_s00e1_0e30 {
public:
    Draw2D_s00e1_0e30* Begin2D(int unk);                                   // 0x0095bc10
    void End2D();                                               // 0x0095bb20
    void AddRenderable(void* p);                                // 0x0095bbc0
};
}
}
struct cTradeRoutePoint {
    Vector3_s00e1_0e30 mPosition;
    float mSize;            // +0x0c
    uint32_t pad10[5];
};
struct cTradeRoute {
    uint32_t pad0;
    cTradeRoutePoint* mpPointsBegin;    // +0x04
    cTradeRoutePoint* mpPointsEnd;      // +0x08
    uint32_t NumPoints() const { return (uint32_t)(mpPointsEnd - mpPointsBegin); }
};
class cPlanet_s00e1_0e30 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void* GetHorizonSource();                       // +0x0c
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
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
    virtual void vc0();
    virtual cTradeRoute* GetTradeRoute(int index);          // +0xc4
    virtual int GetTradeRouteCount();                       // +0xc8
};
struct cPlanetModel_s00e1_0e30 {
    uint32_t pad0[9];
    cPlanet_s00e1_0e30* mpPlanet;      // +0x24
};
struct cRouteObject {
    uint32_t pad0[0x49];
    int mRouteKind;                     // +0x124 (1 = second dot style)
    Vector3_s00e1_0e30* mpPointsBegin;             // +0x128
    Vector3_s00e1_0e30* mpPointsEnd;               // +0x12c
    uint32_t NumPoints() const { return (uint32_t)(mpPointsEnd - mpPointsBegin); }
};
struct cRouteObjectVector {
    cRouteObject** mpBegin;
    cRouteObject** mpEnd;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cRouteObject* operator[](uint32_t i) { return mpBegin[i]; }
};
struct cGameDataVector {
    uint32_t pad0;
    cRouteObjectVector mData;           // +0x04
};
typedef void (*GameDataFn)();
void GameDataFn_cd7d10();
void GameDataFn_d3d420();
void GameDataFn_e10060();
void GameDataFn_b1e500();
namespace SP {
uint32_t GetCurrentGameMode();          // 0x00b5b800
}
namespace SP {
cPlanetModel_s00e1_0e30* PlanetModel_s00e1_0e30();            // 0x00b3d350
}
namespace SP {
class cGameNounManager_s00e1_0e30 { public:
    cGameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d,
                                       uint32_t nounID);   // 0x00b21340
};
}
namespace SP {
cGameNounManager_s00e1_0e30* NounManager();        // 0x00b3d300
}
Vector3_s00e1_0e30 GetHorizonPoint(void* source, const Vector2& range, const Vector3_s00e1_0e30& cameraPos,
                        const Vector3_s00e1_0e30& cameraDir, float cameraParam);
struct cDotStyle {
    float mHalfWidth;
    float mHalfHeight;
    uint32_t mColor;
    float mSpacing;
};
class IWindow_s00e1_0e30 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
};
class cHashable {
public:
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
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual uint32_t GetID();                                   // +0x4c
};
class cSPUIMinimapWin_s00e1_0e30 {
public:
    uint32_t mVtable;                       // +0x000
    IWindow_s00e1_0e30 mWindow;                        // +0x004
    uint32_t pad008[0x8d];                  // +0x008 .. +0x23b
    int mStopwatchField0;                   // +0x23c
    int mStopwatchField1;                   // +0x240
    uint32_t pad244;                        // +0x244
    EA::UTFWin::Image_s00e1_0e30* mpRoadIconImage;     // +0x248
    EA::UTFWin::Image_s00e1_0e30* mpTexture;           // +0x24c
    uint32_t pad250[0x3a];                  // +0x250 .. +0x337
    Vector3_s00e1_0e30 mWorldCameraPos;                // +0x338
    Vector3_s00e1_0e30 mWorldCameraDir;                // +0x344
    float mCameraParam;                     // +0x350
    uint32_t pad354[4];                     // +0x354 .. +0x363
    bool mbTradeRoutesDirty;                // +0x364
    Vector3Vector mTradeRouteDots;          // +0x368 .. +0x37b
    uint32_t pad37c[0x181];                 // +0x37c .. +0x97f
    cHashable* mpBorderRenderable;          // +0x980

    bool WorldXYZToMinimapXY(const Vector3_s00e1_0e30& pos, Vector2& out, bool clamp);   // 0x00e0bcb0
    void draw_trade_routes(EA::UTFWin::Draw2D_s00e1_0e30& draw);  // 0x00e10e30 (cSPUIMinimapWin::draw_trade_routes)
    bool OnRebuild(EA::UTFWin::RenderContext_s00e1_0e30* ctx);                        // 0x00e119c0
};
struct IRefCounted {
    virtual void AddRef();                                      // vtable +0x00
    virtual void Release();                                     // vtable +0x04
};
struct cRefPtr {
    IRefCounted* mpObject;                                      // +0x00
    cRefPtr() : mpObject(0) {}
    cRefPtr(const cRefPtr& other) : mpObject(other.mpObject) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~cRefPtr() { if (mpObject) mpObject->Release(); }
};
struct cDataValue {
    uint32_t mId;                                               // +0x00
    bool mbDirty;                                               // +0x04
    unsigned char mPad05[3];                                    // +0x05
    cRefPtr mPtr0;                                              // +0x08
    cRefPtr mPtr1;                                              // +0x0c
    cDataValue() : mId(0), mbDirty(true), mPtr0(), mPtr1() {}
    void draw_civilization_borders(EA::UTFWin::RenderContext_s00e1_0e30* ctx,
                                   cSPUIMinimapWin_s00e1_0e30* win);        // 0x00e0f2c0
};
struct cDataInfo {
    uint32_t mKey;                                              // +0x00
    cDataValue mValue;                                          // +0x04
    cDataInfo(uint32_t key) : mKey(key), mValue() {}
};
struct cInsertResult {
    cDataInfo* mpNode;                                          // +0x00
    bool mbInserted;                                            // +0x04
    cInsertResult(cDataInfo* node, bool inserted)
        : mpNode(node), mbInserted(inserted) {}
};
struct cDataArray {
    cDataInfo* mpBegin;                                         // +0x00
    cDataInfo* mpEnd;                                           // +0x04
    cDataInfo* mpCapacity;                                      // +0x08
    uint32_t mPad0c[2];                                         // +0x0c
    unsigned char mCompare;                                     // +0x14

    cInsertResult insert(const cDataInfo& value);               // 0x00e118b0
    cDataValue& FindOrInsert(uint32_t key);                     // 0x00e11910
    cDataInfo* insert_at(cDataInfo* pos, const cDataInfo& value);  // 0x00e10c10
};
cDataInfo* lower_bound_DataInfo(cDataInfo* first, cDataInfo* last,
                                const uint32_t& value, unsigned char cmp);  // 0x00e0e9f0
void RebuildBaseWindow(IWindow_s00e1_0e30* window);                        // 0x00e0af90
extern cDataArray gDataMap;                                     // 0x016a204c
static __forceinline cDataInfo* find_DataInfo(cDataArray& map, const uint32_t& key)
{
    cDataInfo* end = map.mpEnd;
    cDataInfo* it = lower_bound_DataInfo(map.mpBegin, end, key, map.mCompare);
    if (it == end || key < it->mKey || it == it + 1)
        it = end;
    return it;
}
// ---- items of slice s00e10e30 end

// ---- items of slice s00e100e0_g7 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_allocator;              // 0x013ebb38
extern void* g_feedbackBegin;           // 0x016a204c
extern void* g_feedbackEnd;             // 0x016a2050
extern const float g_halfConst;         // 0x01471064 (=0.5f)
struct cRecSub {
    void* mp00;                         // +0x00
    u8    mb04;                         // +0x04
    u8    mPad05[3];                    // +0x05
    void* mp08;                         // +0x08  (refcounted interface)
    void* mp0c;                         // +0x0c  (refcounted interface)

    cRecSub* Assign(const cRecSub* o);  // 0x00e0ea40 (thiscall, this = dst)
};
struct cRec14_s00e1_00e0__g7 {
    u32     mField00;                   // +0x00
    cRecSub mSub;                       // +0x04

    cRec14_s00e1_00e0__g7* Copy(const cRec14_s00e1_00e0__g7* src);    // 0x00e0c670 (thiscall, this = dst)
};
void*   __cdecl CopyRecRange(void* first, void* last, void* dst);        // 0x00e0c710
void*   __cdecl DestroyRecRange(void* first, void* last, void* dst);     // 0x00e0c780
void*   __cdecl MoveBack(const void* src, void* first, void* last);      // 0x00e0f050
void* __cdecl operator_new_rec(u32 size, const char* file, int line,
                               int a, void* alloc, int c);      // 0x00f473a0
void  __cdecl operator_delete_rec(void* p);                     // 0x00f47380
struct VecRec14 {
    cRec14_s00e1_00e0__g7* mpBegin;                    // +0x00
    cRec14_s00e1_00e0__g7* mpEnd;                      // +0x04
    cRec14_s00e1_00e0__g7* mpCap;                      // +0x08

    void    DoInsertValue(cRec14_s00e1_00e0__g7* pos, const cRec14_s00e1_00e0__g7* value);    // 0x00e100e0
    cRec14_s00e1_00e0__g7* insert(cRec14_s00e1_00e0__g7* pos, const cRec14_s00e1_00e0__g7* value);           // 0x00e10c10
};
class IRefcount {
public:
    virtual int  AddRef();                          // +0x00
    virtual int  Release();                         // +0x04
    virtual int  v08();                             // +0x08
};
class IUnknownInt {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void* Query(unsigned id);                // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void* v1c();                             // +0x1c
};
struct cFeedbackEvent_s00e1_00e0__g7 {
    IUnknownInt* mpObject;              // +0x00
    u32          mField04;              // +0x04
    u32          mMessageId;            // +0x08
    u32          mField0c;              // +0x0c
    u32          mField10;              // +0x10
    u32          mField14;              // +0x14
    u32          mFlags18;              // +0x18
    u32          mField1c;              // +0x1c
    u32          mField20;              // +0x20
    u32          mField24;              // +0x24
    void*        mpCity;                // +0x28
};
struct cIconInfo;
void* __cdecl SP_PlanetModel();                                 // 0x00b3d350
void* __cdecl SP_GetCurrentGameMode();                          // 0x00b5b800
void* __cdecl SP_NounManager(void*);                            // 0x00b3d300
float* __cdecl SP_PlanetModel_DirectionToSurfacePosition(void* model, float* out, float* dir);  // 0x00b815a0
void* __cdecl cSPUIPropertyLayout_GetRootWindow(void* layout);  // 0x00828100
void* __cdecl FUN_0067cab0(int a);                              // 0x0067cab0
bool  __cdecl FUN_008017f0(void* p);                            // 0x008017f0
void* __cdecl FUN_00b1fc00(unsigned id);                        // 0x00b1fc00
void* __cdecl FUN_00c6aa30(void* p);                            // 0x00c6aa30
void* __cdecl FUN_010666a0(void* a, void* b);                   // 0x010666a0
void  __cdecl FUN_01067e70(void* a, void* b);                   // 0x01067e70
void  __cdecl FUN_00e2e8d0(void* a, int b, int c, void* d);     // 0x00e2e8d0
bool  __cdecl FUN_00950bb0(void* event);                        // 0x00950bb0
void  __cdecl FUN_00e0b990(void* self, void* pos, u32 flags, int a, int b);   // 0x00e0b990
void* __cdecl FUN_00e0ff80(void* tree, const unsigned* key, void* out);       // 0x00e0ff80
void  __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e);      // 0x00571db0
void* __cdecl FUN_00bdde70(void* self, void* city);             // 0x00bdde70
void* __cdecl FUN_00bd9bf0(void* city);                         // 0x00bd9bf0
void  __cdecl FUN_00b25f40(void* p);                            // 0x00b25f40
void  __cdecl FUN_00e0f160(void* node);                         // 0x00e0f160
void* __cdecl FUN_00e0f010(void* a, void* b, void* c);          // 0x00e0f010
void* __cdecl FUN_00e0e9a0(void* a, void* b);                   // 0x00e0e9a0
void* __cdecl eastl_rbtree_find(void* out, void* tree, const void* key);   // 0x00e5c780
struct CBaseWindow {
    void Shutdown();                    // 0x00961e80
};
struct CVec3Store {
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void* erase(void* a, void* b);      // 0x0050f740
};
void* __cdecl FUN_00b5f950(void* self, void* p);                // 0x00b5f950
extern u32 g_modeCityHall;              // 0x01654c04
extern u32 g_modeTribe;                 // 0x01654c05
struct CMinimapWin {
    unsigned char mPad000[4];
    void*        mpWinIface;            // +0x004
    unsigned char mPad008[0x224 - 8];
    IRefcount*   mpHandlerTarget;       // +0x224
    void*        mHandlerArg228;        // +0x228
    void*        mHandlerArg22c;        // +0x22c
    void*        mHandlerArg230;        // +0x230
    void*        mHandlerArg234;        // +0x234
    unsigned char mPad238[0x244 - 0x238];
    IRefcount*   mpRef244;              // +0x244
    IRefcount*   mpRef248;              // +0x248
    IRefcount*   mpRef24c;              // +0x24c
    IRefcount*   mpRef250;              // +0x250
    IRefcount*   mpRef254;              // +0x254
    IRefcount*   mpRef258;              // +0x258
    unsigned char mPad25c[0x27c - 0x25c];
    u32          mField27c;             // +0x27c
    unsigned char mPad280[0x320 - 0x280];
    void*        mpTreeAnchor;          // +0x320
    void*        mpTreeEnd;             // +0x324
    void*        mpTreeRoot;            // +0x328
    u8           mbTreeFlag;            // +0x32c
    unsigned char mPad32d[3];
    u32          mTreeCount;            // +0x330
    unsigned char mPad334[0x368 - 0x334];
    void*        mVecBegin;             // +0x368
    void*        mVecEnd;               // +0x36c
    unsigned char mPad370[0x980 - 0x370];
    IRefcount*   mpRef980;              // +0x980
    IRefcount*   mpRef984;              // +0x984
    IRefcount*   mpRef988;              // +0x988

    bool HandleNotification(cFeedbackEvent_s00e1_00e0__g7* event);     // 0x00e10220
    void Shutdown();                    // 0x00e10c80
};
// ---- items of slice s00e100e0_g7 end

// @ 0x00e0a950
bool __cdecl FUN_00e0a950()
{
    if ((g_16a2028 | g_16a202c) != 0) {
        __int64 t = FUN_0093a3a0(&g_16a2028);
        double d = (double)t;
        return d * g_16a203c < g_15a4cb8;
    }
    return false;
}

// @ 0x00e0a9a0
void __cdecl FUN_00e0a9a0(const Float3* p, u32 a, u32 b)
{
    const u32* q = (const u32*)p;
    g_16a1fa0 = 1;
    g_16a2040 = q[0];
    g_16a2044 = q[1];
    g_16a2048 = q[2];
    g_16a1f9c = a;
    g_16a1f98 = b;
}

// @ 0x00e0a9e0
double __fastcall FUN_00e0a9e0(cPaletteGrid* ecx_this, void* edx, float a, float b)
{
    float s = ecx_this->m218 * b;
    int i = (int)s;
    if (s < (float)i)
        i--;
    if (i < 0)
        i = 0;
    else if (i > 0x80)
        i = 0x80;
    int range = (int)((0u - (u32)(ecx_this->m239 != 0)) & 0xffffff80u) + 0x100;
    double p = (double)(u32)ecx_this->mPal[i];
    double r = (double)range;
    return (((double)ecx_this->m21C * (double)a - p) * r) / (r - (p + p)) * (double)ecx_this->m220;
}

// @ 0x00e0aa80
double __fastcall FUN_00e0aa80(cPaletteGrid* ecx_this, void* edx, float a, float b)
{
    float s = ecx_this->m218 * b;
    int i = (int)s;
    if (s < (float)i)
        i--;
    if (i < 0)
        i = 0;
    else if (i > 0x80)
        i = 0x80;
    int range = (int)((0u - (u32)(ecx_this->m239 != 0)) & 0xffffff80u) + 0x100;
    double p = (double)(u32)ecx_this->mPal[i];
    double r = (double)range;
    return (p + ((r - (p + p)) * (double)ecx_this->m21C * (double)a) / r) * (double)ecx_this->m220;
}

// @ 0x00e0ab30
bool __fastcall FUN_00e0ab30(cPaletteGrid* ecx_this, void* edx, float a, float b, u8* out)
{
    if (FUN_00e0aa80(ecx_this, edx, 0.0, b) <= (double)a) {
        if ((double)a < FUN_00e0aa80(ecx_this, edx, (float)ecx_this->m23C, b)) {
            *out = 1;
            return false;
        }
    }
    *out = 0;
    return false;
}

// @ 0x00e0aba0
void __fastcall FUN_00e0aba0(cPaletteGrid* ecx_this, void* edx, void* obj)
{
    ((cObj95*)obj)->Set(ecx_this->m354);
}

// @ 0x00e0abc0
bool __fastcall FUN_00e0abc0(cPaletteGrid* ecx_this, void* edx, u32 a, u32 b, u32 c, void* d)
{
    ((IWin*)ecx_this)->v94(d);
    return true;
}

// @ 0x00e0abe0
void __fastcall FUN_00e0abe0(cPaletteGrid* ecx_this, void* edx, float a, float b, float c, char d)
{
    double ang = (double)g_15a4bfc - atan2((double)b, (double)a);
    float fa = (float)ang;
    double sph = atan2((double)c, sqrt((double)a * (double)a + (double)b * (double)b));
    float fv = (float)sph;

    if (d != 0 || fv < ecx_this->m998) {
        ecx_this->m998 = fv;
        if (d != 0)
            goto set_angles;
    }
    if (fv > ecx_this->m99C) {
        ecx_this->m99C = fv;
        if (d != 0) {
        set_angles:
            ecx_this->m990 = fa;
            ecx_this->m9A0 = fa;
            ecx_this->m994 = fa;
            return;
        }
    }
    if (fabs(ang - (double)ecx_this->m9A0) > (double)g_15a4c00) {
        if (ecx_this->m9A0 > fa)
            fa = g_16a2024 + fa;
        else
            fa = fa - g_16a2024;
    }
    if (fa < ecx_this->m990)
        ecx_this->m990 = fa;
    else if (fa > ecx_this->m994)
        ecx_this->m994 = fa;
}

// @ 0x00e0ad00
void __fastcall FUN_00e0ad00(cPaletteGrid* ecx_this, void* edx, u32 flags)
{
    ecx_this->m35C |= flags;
}

// @ 0x00e0ad10
namespace  {
void UpdatePallete(unsigned int * buf, int count, unsigned int colA, unsigned int colB, unsigned int colC, unsigned int divisor)
{
    u32 uVar8 = colC >> 16;
    u32 uVar1 = colC & 0xff;
    u32 uVar9 = colC >> 8;
    u32 uVar2 = colA & 0xff;
    int iVar3 = (int)(colB & 0xff) - (int)uVar2;
    u32 uVar12 = (colA >> 16) & 0xff;
    u32 uVar10 = (colA >> 8) & 0xff;
    int iVar13 = (int)((colB >> 8) & 0xff) - (int)uVar10;
    int iVar17 = (int)((colB >> 16) & 0xff) - (int)uVar12;
    u32 uVar4 = (u32)(count << 4) / divisor;
    int i = 0;
    int iVar15 = 0xff - count;
    int iVar5 = -count;
    int local34 = -(iVar3 * count);
    int iVar14 = -(iVar13 * count);
    int accB = 0;
    int accG = 0;
    int accR = 0;
    int iVar18 = -(iVar17 * count);

    do {
        if (count < i || count == 0) {
            if (iVar5 < 5) {
                buf[i] = 0xffbe9f50;
                buf[0x100 + i] = 0xffae8f40;
            } else {
                u32 rr = (u32)(iVar18 / iVar15 + (int)uVar12) & 0xff;
                u32 gg = (u32)(iVar14 / iVar15 + (int)uVar10) & 0xff;
                u32 bb = (u32)(local34 / iVar15 + (int)uVar2) & 0xff;
                u32 v = (rr << 16) | (gg << 8) | bb;
                buf[i] = v | 0xff000000;
                u32 p = (((rr * divisor) & 0xfffffff0) << 12) | (((gg << 8) & 0xff0) * divisor);
                p &= 0xffffff00;
                buf[0x100 + i] = p | ((bb * divisor) >> 4) | 0xff000000;
            }
        } else {
            buf[i] = (((accR / count) | 0xff00) << 8 | (accG / count)) << 8 | (accB / count);
            buf[0x100 + i] = (((accR / (int)uVar4) | 0xff00) << 8 | (accG / (int)uVar4)) << 8 |
                             (accB / (int)uVar4);
        }
        accR += (int)uVar8;
        accB += (int)uVar1;
        local34 += iVar3;
        iVar18 += iVar17;
        iVar14 += iVar13;
        accG += (int)uVar9;
        i++;
        iVar5++;
    } while (i < 0x100);
}
}  // namespace 

// @ 0x00e0af90
void __cdecl FUN_00e0af90(IWin* win)
{
    float* src = (float*)((IWin*)FUN_0067dd50())->v1C();
    float m[8];
    float* d = m;
    int n = 8;
    do {
        *d++ = *src++;
    } while (--n);

    float rect[4];
    SPUIHelpers_GetBoundingScreenRect(rect, win, 0);

    float x0 = FUN_00e0af90_clamp(((1.0f / (float)(int)m[3]) * rect[3] - 0.5f) * 2.0f);
    float y0 = FUN_00e0af90_clamp(((1.0f / (float)(int)m[1]) * rect[1] - 0.5f) * 2.0f);
    float x1 = FUN_00e0af90_clamp(((1.0f / (float)(int)m[3]) * rect[2] - 0.5f) * 2.0f);
    float y1 = FUN_00e0af90_clamp(((1.0f / (float)(int)m[1]) * rect[3] - 0.5f) * 2.0f);

    float ny0 = -y0;
    float ny1 = -y1;

    IWin* parent = win->v4C();
    cHelper* h = 0;
    if (parent != 0)
        h = (cHelper*)parent->v0C(0x5234b49);

    const float& xmin = (x0 > x1) ? x1 : x0;
    h->Set(xmin, 0);
    const float& ymin = (ny0 > ny1) ? ny1 : ny0;
    h->Set(ymin, 1);
    const float& xmax = (x1 > x0) ? x1 : x0;
    h->Set(xmax, 2);
    const float& ymax = (ny1 > ny0) ? ny1 : ny0;
    h->Set(ymax, 3);
    h->Set((float)fabs(1.0 / (double)(x1 - x0)), 4);
    h->Set((float)fabs(1.0 / (double)(ny1 - ny0)), 5);
}

// @ 0x00e0b230
void __fastcall FUN_00e0b230(cPaletteGrid2* ecx_this, void* edx, ISlot* arg)
{
    ISlot* old = (ISlot*)ecx_this->mTarget;
    if (arg != old) {
        if (arg != 0)
            arg->v00();
        ecx_this->mTarget = (IWin*)arg;
        if (old != 0)
            old->v04();
    }
    IWin* w = &ecx_this->mWin;
    w->v7C(0x10, 1);
    w->v7C(0x40, 1);
}

// @ 0x00e0b290
bool __fastcall FUN_00e0b290(cPaletteGrid2* ecx_this, void* edx, void* arg)
{
    IWin* t = ecx_this->mTarget;
    if (t != 0)
        return t->v88(arg, &ecx_this->mWin);
    return true;
}

// @ 0x00e0b2c0
void __cdecl FUN_00e0b2c0(float* out, u32 unused, float* a, float* b, float w)
{
    double f2 = atan2((double)b[2], sqrt((double)b[1] * (double)b[1] + (double)b[0] * (double)b[0]));
    double f4 = (f2 - 0.5 * (double)w) + (1.0 - (double)a[1]) * (double)w;
    double cc = cos(f4);
    double f3 = atan2((double)b[1], (double)b[0]);
    double f5 = (double)(1.0f - a[0]) * (double)w;
    f3 = (f5 + f5) + (((double)g_15a4bfc - f3) - (double)w);
    out[0] = (float)(sin(f3) * cc);
    out[1] = (float)(cos(f3) * cc);
    out[2] = (float)sin(f4);
}

// @ 0x00e0b350
float* FUN_00e0b350(float* out, void* a2, float* a3, float* a4, float f5, float* a6)
{
    (void)a2;
    float ay = a4[1];
    float ax = a4[0];
    float az = a4[2];
    out[0] = 0.0f;
    out[1] = 0.0f;
    float lim    = *(float*)0x15a4c00;
    float halfpi = *(float*)0x15a4bfc;
    float pi     = *(float*)0x16a2024;
    float pitchA = (float)atan2((double)az, (double)sqrtf(ay * ay + ax * ax));
    float half   = 0.5f;
    float yawA   = (float)atan2((double)ay, (double)ax);
    float dA     = (halfpi - yawA) - f5;
    float b      = dA;
    float by = a3[1];
    float bx = a3[0];
    float yawB = halfpi - (float)atan2((double)by, (double)bx);
    float d    = yawB;
    float pitchB = (float)atan2((double)a3[2], (double)sqrtf(bx * bx + by * by));
    if (dA <= 0.0f) {
        if (0.0f < d) {
            d = yawB - pi;
            if (lim < fabsf((yawB - pi) - dA))
                b = b - pi;
        }
    } else {
        if (d < 0.0f) {
            d = pi + d;
            yawB = d;
        }
        if (lim < fabsf(yawB - dA))
            b = pi + b;
    }
    float v1 = 1.0f - (d - b) / (f5 * 2.0f);
    float v0 = 1.0f - (pitchB - (pitchA - f5 * half)) / f5;
    out[1] = v0;
    out[0] = v1;
    if (lim <= f5)
        return out;
    if (a6 && (1.0f < v1 || 1.0f < v0 || v1 < 0.0f || v0 < 0.0f))
        *a6 = (float)atan2((double)v0 - (double)half, (double)v1 - (double)half);
    float c0 = 0.0f;
    if (0.0f <= v0)
        c0 = v0;
    if (1.0f <= c0)
        c0 = 1.0f;
    out[1] = c0;
    float c1 = 0.0f;
    if (0.0f <= v1)
        c1 = v1;
    if (1.0f <= c1)
        c1 = 1.0f;
    out[0] = c1;
    return out;
}

// @ 0x00e0b580
float* FUN_00e0b580(float* out, void* a2, float* a3, float* a4, float* a5, float f6, void* a7)
{
    (void)a2;
    void* gm = FUN_00b5b800();
    if (gm != (void*)0x1654c05 && gm != (void*)0x1654c04)
        return FUN_00e0b350(out, a2, a3, a4, f6, (float*)a7);

    float v6 = a3[0];
    float v7 = a3[1];
    float v11 = a3[2];
    float n2 = 1.0f / sqrtf(v11 * v11 + (v7 * v7 + v6 * v6) + 1e-08f);
    float u14 = a5[1];
    float u13 = a5[2];
    float u1  = a5[0];
    float w8  = u13 * a4[1] - u14 * a4[2];
    float w9  = u1 * a4[2] - a4[0] * u13;
    float w12 = a4[0] * u14 - u1 * a4[1];
    float n3 = 1.0f / sqrtf(w9 * w9 + (w12 * w12 + w8 * w8) + 1e-08f);
    float dot = (u14 * (v7 * n2) + u13 * (v11 * n2)) + u1 * (v6 * n2);
    v11 = v11 * n2 - u13 * dot;
    u13 = v6 * n2 - u1 * dot;
    u14 = v7 * n2 - u14 * dot;
    float n4 = 1.0f / sqrtf(u14 * u14 + (v11 * v11 + u13 * u13) + 1e-08f);
    float ang1 = (float)acos((double)((float)((n4 * u13) * (n3 * w8)) +
                                       (float)((v11 * n4) * (w12 * n3)) +
                                       (float)((u14 * n4) * (w9 * n3))));
    if ((n4 * u13) * (n3 * w8) + (v11 * n4) * (w12 * n3) + (u14 * n4) * (w9 * n3) < 0.0f)
        ang1 = *(float*)0x16a2024 - ang1;
    float a1 = ang1 / (f6 * 2.0f);
    float a0 = (float)((double)acos(0.0) / (double)f6);
    if (f6 < *(float*)0x15a4c00) {
        float c0 = 0.0f;
        if (0.0f <= a0)
            c0 = a0;
        if (1.0f <= c0)
            c0 = 1.0f;
        a0 = c0;
        float c1 = 0.0f;
        if (0.0f <= a1)
            c1 = a1;
        if (1.0f <= c1)
            c1 = 1.0f;
        a1 = c1;
        out[0] = a0;
        out[1] = a1;
        return out;
    }
    out[0] = a1;
    out[1] = a0;
    return out;
}

// @ 0x00e0b970
void cSPUIMinimapWin::FUN_00e0b970()
{
    void* p = mpField254;
    if (p)
        return VT_90((char*)p + 4);
}

// @ 0x00e0bcb0
char cSPUIMinimapWin::FUN_00e0bcb0(void* p2, float* out, void* p4)
{
    void* g = FUN_00b3d350();
    void* o = g ? *(void**)((char*)g + 0x24) : 0;
    if (!o)
        return 0;
    if (VT_0C_0(o) == 0)
        return 0;
    void* r = ((void* (__thiscall*)(void*, void*, float*, float*, float, void*))
               ((void***)*(void**)o)[0xc / 4])(o, p2, mVec338, mVec344, mF350, p4);
    float buf[2];
    float* tmp = FUN_00e0b580b(buf, r);
    out[0] = tmp[0];
    out[1] = tmp[1];
    out[1] = (float)mI240 * out[1];
    float y = out[1];
    float x = (float)mI23C * out[0];
    out[0] = Call_E0AA80(this, x, y);
    return 1;
}

// @ 0x00e0bd70
ObjB* ObjB::FUN_00e0bd70(const ObjB& o)
{
    m0  = o.m0;
    m4  = o.m4;
    m8  = o.m8;
    mC  = o.mC;
    m10 = o.m10;
    mRef = o.mRef;
    if (mRef)
        RefAddRef(mRef);
    m18 = o.m18;
    m1C = o.m1C;
    m20 = o.m20;
    return this;
}

// @ 0x00e0bdc0
ObjC* ObjC::FUN_00e0bdc0(const ObjC& o)
{
    m0  = o.m0;
    m4  = o.m4;
    m8  = o.m8;
    mC  = o.mC;
    m10 = o.m10;
    void* nv = o.mRef;
    if (nv != mRef) {
        void* old = mRef;
        if (nv)
            RefAddRef(nv);
        mRef = nv;
        if (old)
            RefRelease(old);
    }
    m18 = o.m18;
    m1C = o.m1C;
    m20 = o.m20;
    return this;
}

// @ 0x00e0be50
void cSPUIMinimapWin::FUN_00e0be50()
{
    void* base = this ? (char*)this + 4 : 0;
    void* nv = FUN_00806370(base);
    void* old = mpField98C;
    if (nv != old) {
        if (nv)
            RefAddRef(nv);
        mpField98C = nv;
        if (old)
            RefRelease(old);
    }
    VT_7C(mpField98C, 0x10, 1);
    VT_7C(mpField98C, 1, 0);
    FUN_00806a60(mpField98C, mpField258, 0x24a451fc, -1);
    void* r = VT_A8(mpField98C);
    if (r) {
        float pos[2];
        VT_18(r, pos, 0, 0);
        VT_74(mpField98C, pos[0], pos[1]);
    }
    VT_EC((char*)this + 4, mpField98C);
}

// @ 0x00e0bf40
void cSPUIMinimapWin::ComputeIconPositionFromMinimapCoords(float* p2, void* p3, char p4)
{
    float* r1 = (float*)VT_38(p3);
    float lo0 = r1[0];
    float lo1 = r1[1];
    float lo2 = r1[2];
    float lo3 = r1[3];
    float x = p2[0];
    float y = p2[1];
    float edge = (float)mBytes280[(int)(mF218 * y) + 0x30] * mF220;
    void* iw = mpObj4;
    int flag = 1;
    float* r2 = (float*)VT_38(iw);
    float inner0 = r2[0];
    float inner2 = r2[2];
    void* app = FUN_0067dd10();
    void* gm = VT_38(app);
    float big = (lo2 - lo0) * 2.0f;
    if ((gm == (void*)0x1654c02 || (gm == (void*)0x1654c10 && p4 == 0)) &&
        (x < big + edge || ((inner2 - inner0) - edge) - big < x))
        flag = 0;
    float halfH = (lo3 - lo1) * 0.5f;
    if ((gm != (void*)0x1654c02 && (gm != (void*)0x1654c10 || p4 != 0)) ||
        (halfH <= y && y <= ((float*)VT_38(iw))[3] - ((float*)VT_38(iw))[1] - halfH)) {
        float* r3 = (float*)VT_38(iw);
        if (halfH <= y && (r3[3] - r3[1]) - halfH < y)
            VT_38(iw);
    } else {
        flag = 0;
    }
    void* o = (void*)((void* (__thiscall*)(void*, int, int))
                      ((void***)*(void**)p3)[0x7c / 4])(p3, 1, flag);
    float w = lo3 - lo1;
    ((void (__thiscall*)(void*, float, float))
     ((void***)*(void**)o)[0x64 / 4])(o, w, y);
}

// @ 0x00e0c1f0
void cSPUIMinimapWin::FUN_00e0c1f0(float* v)
{
    float x = v[0];
    float y = v[1];
    float z = v[2];
    float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
    mVec338[0] = x * inv;
    mVec338[1] = y * inv;
    mVec338[2] = z * inv;
    VT_90((char*)this + 4);
    VT_8C(this);
    mFlags35C |= 3;
}

// @ 0x00e0c610
void* cRec28Copy::Copy(const u32* src, const u32* args)
{
    char* dst = (char*)this;
    *(u32*)(dst + 0x00) = *src;
    *(u32*)(dst + 0x04) = args[0];
    *(f32*)(dst + 0x08) = *(f32*)&args[1];
    *(f32*)(dst + 0x0c) = *(f32*)&args[2];
    *(f32*)(dst + 0x10) = *(f32*)&args[3];
    *(u32*)(dst + 0x14) = args[4];
    void* p18 = (void*)args[5];
    *(void**)(dst + 0x18) = p18;
    if (p18 != 0)
        VT_00_0(p18);
    *(f32*)(dst + 0x1c) = *(f32*)&args[6];
    *(u32*)(dst + 0x20) = args[7];
    *(u32*)(dst + 0x24) = args[8];
    return dst;
}

// @ 0x00e0c670
void* cRec14Copy::Copy(const cRec14* src)
{
    char* dst = (char*)this;
    *(u32*)(dst + 0x00) = *(u32*)((char*)src + 0x00);
    *(u32*)(dst + 0x04) = *(u32*)((char*)src + 0x04);
    *(u8*)(dst + 0x08) = *(u8*)((char*)src + 0x08);
    void* p0c = *(void**)((char*)src + 0x0c);
    *(void**)(dst + 0x0c) = p0c;
    if (p0c != 0)
        VT_00_0(p0c);
    void* p10 = *(void**)((char*)src + 0x10);
    *(void**)(dst + 0x10) = p10;
    if (p10 != 0)
        VT_00_0(p10);
    return dst;
}

// @ 0x00e0c6b0
void* cRec28CopyB::Copy(const cRec28* src)
{
    char* dst = (char*)this;
    *(u32*)(dst + 0x00) = src->mField00;
    void* ptr04 = (void*)src->mField04;
    *(u32*)(dst + 0x04) = (u32)ptr04;
    *(f32*)(dst + 0x08) = *(f32*)&src->mField08;
    *(f32*)(dst + 0x0c) = *(f32*)&src->mField0c;
    *(f32*)(dst + 0x10) = *(f32*)&src->mField10;
    u32 v14 = src->mField14;
    *(u32*)(dst + 0x14) = v14;
    void* ptr18 = src->mpField18;
    *(void**)(dst + 0x18) = ptr18;
    if (ptr18 != 0)
        VT_00_0(ptr18);
    *(f32*)(dst + 0x1c) = *(f32*)&src->mField1c;
    *(u32*)(dst + 0x20) = src->mField20;
    *(u32*)(dst + 0x24) = src->mField24;
    return dst;
}

// @ 0x00e0c710
void* __cdecl CopyRecRange(void* first, void* last, void* dst)
{
    if (first != last) {
        char* q = (char*)first + 0x0c;
        char* e = (char*)dst + 0x0c;
        do {
            if (dst != 0) {
                *(u32*)((char*)dst + 0x00) = *(u32*)((char*)first + 0x00);
                *(u32*)((char*)dst + 0x04) = *(u32*)((char*)first + 0x04);
                *(u8*)((char*)dst + 0x08) = *(u8*)((char*)first + 0x08);
                *(u32*)(e) = *(u32*)(q);
                if (*(void**)(e) != 0)
                    VT_00_0(*(void**)(e));
                *(u32*)(e + 0x04) = *(u32*)(q + 0x04);
                if (*(void**)(e + 0x04) != 0)
                    VT_00_0(*(void**)(e + 0x04));
            }
            first = (char*)first + 0x14;
            dst = (char*)dst + 0x14;
            q += 0x14;
            e += 0x14;
        } while (first != last);
    }
    return dst;
}

// @ 0x00e0c780
void* __cdecl DestroyRecRange(void* first, void* last, void* dst)
{
    if (first != last) {
        char* q = (char*)first + 0x0c;
        do {
            if (*(void**)(q + 0x04) != 0)
                VT_04_0(*(void**)(q + 0x04));
            if (*(void**)(q) != 0)
                VT_04_0(*(void**)(q));
            first = (char*)first + 0x14;
            q += 0x14;
            dst = (char*)dst + 0x14;
        } while (first != last);
    }
    return dst;
}

// @ 0x00e0c7d0
void* cTerrainRenderer::Destroy(u8 flags)
{
    if (mpField210 != 0)
        VT_04_0(mpField210);
    if (mpField20c != 0)
        VT_04_0(mpField20c);
    FUN_00962740(this);
    if ((flags & 1) != 0)
        FUN_00951330(this);
    return this;
}

// @ 0x00e0d2e0
bool MinimapWin_s00e0_d100::DrawCameraArrow(RenderContext* ctx, int unused)
{
    const Vec3* pc = &mCenter;
    if ((pc->x * pc->x + pc->y * pc->y) + pc->z * pc->z <= 0.1f) return true;
    if ((mUp.x * mUp.x + mUp.y * mUp.y) + mUp.z * mUp.z <= 0.9f) return true;

    Target2D* tgt = ctx->Begin2D(0);
    Vertex2D v[4];
    v[0].x = 0.0f; v[0].y = 0.0f; v[0].color = 0xffffffff; v[0].u = 0.0f; v[0].v = 0.0f;
    v[1].color = 0xffffffff; v[1].u = 1.0f; v[1].v = 0.0f;
    v[2].color = 0xffffffff; v[2].u = 1.0f; v[2].v = 1.0f;
    v[3].color = 0xffffffff; v[3].u = 0.0f; v[3].v = 1.0f;

    Vec2 p;
    ProjectCenter(pc, &p, 0);

    float dx, dy;                       // (uninitialised in the original when there is no terrain)
    PlanetModel_s00e0_d100* pm = GetPlanetModel();
    ITerrain* ter = pm ? pm->mpTerrain : 0;
    if (ter) {
        Vec2 t0, t1, t2;
        Vec2 tmp;
        t0 = *ProjectToUV(&tmp, ter->GetTerrainMapSet(), pc, &mAxisA, &mAxisB, mScale, 0);
        Vec3 q;
        q.x = mUp.x * 0.3f + pc->x;
        q.y = pc->y + mUp.y * 0.3f;
        q.z = pc->z + mUp.z * 0.3f;
        t1 = *ProjectToUV(&tmp, ter->GetTerrainMapSet(), &q, &mAxisA, &mAxisB, mScale, 0);
        Vec3 r;
        r.x = pc->x - mUp.x * 0.3f;
        r.y = pc->y - mUp.y * 0.3f;
        r.z = pc->z - mUp.z * 0.3f;
        t2 = *ProjectToUV(&tmp, ter->GetTerrainMapSet(), &r, &mAxisA, &mAxisB, mScale, 0);

        float rx, ry;
        unsigned int mode = GetCurrentGameMode_s00e0_d100();
        bool plain = true;
        if (mode == 0x1654c05 || mode == 0x1654c04) {
            t1.x = WrapNearest(t1.x, t0.x);
            t2.x = WrapNearest(t2.x, t0.x);
            float d1 = sqrt((t1.x - t0.x) * (t1.x - t0.x) + (t1.y - t0.y) * (t1.y - t0.y));
            float d2 = sqrt((t0.x - t2.x) * (t0.x - t2.x) + (t0.y - t2.y) * (t0.y - t2.y));
            if (!(d1 < d2)) {
                float mx = t0.x * 2.0f;
                float my = t0.y * 2.0f - t2.y;
                float cy = my;
                if (cy <= 0.0f) cy = 0.0f;
                if (0.999f <= cy) cy = 0.999f;
                float yy = (float)mH * cy;
                ry = my * (float)mH;
                rx = RemapX((float)mW * (mx - t2.x), yy);
                plain = false;
            }
        }
        if (plain) {
            ry = (float)mH * t1.y;
            rx = RemapX((float)mW * t1.x, ry);
        }
        dy = ry - p.y;
        dx = rx - p.x;
    }
    Image_s00e0_d100* img = mpImage;
    float nx = -dx;
    float s1 = ((float)img->mH / sqrt(dx * dx + dy * dy)) * 0.4f;
    float A = dx * s1, B = dy * s1;
    float s2 = ((float)img->mW / sqrt(nx * nx + dy * dy)) * 0.4f;
    float P = dy * s2, Q = nx * s2;
    v[0].x = (p.x + A) - P;  v[0].y = (B + p.y) - Q;
    v[1].x = (P + p.x) + A;  v[1].y = (Q + B) + p.y;
    v[2].x = ((p.x - A) + P); v[2].y = Q + (p.y - B);
    v[3].x = ((p.x - A) - P); v[3].y = (p.y - B) - Q;
    tgt->DrawQuads(v, 1, img);
    ctx->End2D();
    return true;
}

// @ 0x00e0d940
uint32_t cMinimapOverlay::OnTick()
{
    if ((mWindow.s28() & 1) == 0)
        return 1;

    float now = GetElapsedSeconds();
    MinimapEventNode* pEnd = (MinimapEventNode*)&mEvents.mpRoot;
    for (MinimapEventNode* p = mEvents.mpBegin; p != pEnd; p = RBTreeIncrement_s00e0_d100(p)) {
        IMinimapIcon* pIcon = 0;
        uint32_t key = p->mKey;
        if (p->mFlags & 0x40103) {
            IMinimapIcon* pGroup = mWindow.sf0(key, 1);
            if (pGroup) {
                pIcon = pGroup->s10()->sf0(key + 1, 1);
                if (pIcon && !mIconsHidden) {
                    if (now > p->mTime) {
                        pIcon->s7c(1, 0);
                        if (now > p->mTime + 1.0f) {
                            pIcon->s10()->se0(pIcon);
                            pIcon = 0;
                            p->mState = 0;
                        }
                    } else if ((pIcon->s28() & 1) == 0) {
                        pIcon->s7c(1, 1);
                    }
                }
            }
        }

        if ((p->mFlags & 0x100) && p->mpTarget) {
            IMinimapTargetA* pTargetA = (IMinimapTargetA*)p->mpTarget->Find(0x137e8e0);
            if (pTargetA) {
                const Vec3* pDir = pTargetA->mDirection.GetDirection();
                float len2 = pDir->x * pDir->x + pDir->y * pDir->y + pDir->z * pDir->z + 1e-8f;
                float inv = 1.0f / sqrt((double)len2);
                p->mPos.x = pDir->x * inv;
                p->mPos.y = pDir->y * inv;
                p->mPos.z = pDir->z * inv;
                if (p->mPos.x != g_lastDirX || p->mPos.y != g_lastDirY || p->mPos.z != g_lastDirZ) {
                    Vec2 uv;
                    ProjectCenter(&p->mPos, &uv, 0);
                    IMinimapIcon* pFound = mWindow.sf0(key, 1);
                    if (pFound)
                        ComputeIconPositionFromMinimapCoords(&uv, pFound, 0);
                }
            }
        }

        if ((p->mFlags & 0x2000) && p->mpTarget) {
            IMinimapTargetB* pTargetB = (IMinimapTargetB*)p->mpTarget->Find(0x4f176642);
            if (pTargetB) {
                const Vec3* pDir = pTargetB->mDirection.GetDirection();
                float len2 = pDir->x * pDir->x + pDir->y * pDir->y + pDir->z * pDir->z + 1e-8f;
                float inv = 1.0f / sqrt((double)len2);
                p->mPos.x = pDir->x * inv;
                p->mPos.y = pDir->y * inv;
                p->mPos.z = pDir->z * inv;
                Vec2 uv;
                ProjectCenter(&p->mPos, &uv, 0);
                if (pIcon)
                    ComputeIconPositionFromMinimapCoords(&uv, pIcon, 0);
                IMinimapIcon* pFound = mWindow.sf0(key, 1);
                if (pFound)
                    ComputeIconPositionFromMinimapCoords(&uv, pFound, 0);
            }
        }
    }

    if (g_fxEnabled != 0) {
        if ((g_swLo == 0 && g_swHi == 0) ||
            (g_fxThreshold <= (float)(__int64)g_minimapStopwatch.GetElapsed() * g_fxScale))
            RefreshEffects(g_fxData, g_fxA, g_fxB, 1);
    }

    unsigned int mode = GetCurrentGameMode_s00e0_d100();
    if (mode != 0x1654c01 && mode != 0x1654c05 && mode != 0x1654c02)
        return 1;

    IMinimapView* pView = WindowManager()->GetView(1);
    if (!pView)
        return 1;

    float viewAngle = pView->GetAngle();
    MinimapEventNode* pFound;
    mEvents.find(&pFound, &viewAngle);
    if (pFound == pEnd)
        return 1;
    if (!pFound->mpTarget)
        return 1;

    IMinimapIcon* pFocus = mWindow.sf0(pFound->mKey, 1);
    if (!pFocus)
        return 1;

    const float* pQuad = pFocus->s38();
    float halfW = (pQuad[2] - pQuad[0]) * 0.5f;
    float halfH = (pQuad[3] - pQuad[1]) * 0.5f;
    Vec2 half;
    half.x = halfW;
    half.y = halfH;
    float size[2];
    pFocus->sc0(half, size);

    if (!pFound->mpTarget)
        return 1;
    IMinimapTargetC* pTargetC = (IMinimapTargetC*)pFound->mpTarget->Find(0x17f243b);
    if (!pTargetC)
        return 1;

    void* pEventMode = pTargetC->GetMode();
    void* pHandle;
    int tag;
    if ((uint32_t)pEventMode == 0x18c43e8) {
        pHandle = EventAction(pTargetC, (const void*)0x18c43e8);
        tag = 0;
    } else if ((uint32_t)pEventMode == 0x18c6d19) {
        pHandle = EventAction(pTargetC, (const void*)0x18c6d19);
        tag = 0x05b598f6;
    } else if ((uint32_t)pEventMode == 0x52aa6122) {
        if (mode != 0x1654c01)
            return 1;
        pHandle = EventAction(pTargetC, (const void*)0x52aa6122);
        tag = 0;
    } else {
        return 1;
    }
    PlayEvent(pHandle, size[0], size[1], tag);
    return 1;
}

// @ 0x00e0de40
bool cMinimapOverlay::ProjectEvent(const Vec2* pMapPos, Vec3* pOut)
{
    PlanetModel_s00e0_d100* pm = GetPlanetModel();
    ITerrain* ter;
    if (pm) ter = pm->mpTerrain;
    else    ter = 0;
    if (!ter || !ter->GetTerrainMapSet()) return false;

    float angle = AngleFromPoint(pMapPos->x, pMapPos->y);
    Vec2 uv;
    uv.x = angle / mW;
    uv.y = pMapPos->y / (float)mH;

    Vec2* pUV = ((IMapSetProjection*)ter)->Project(&uv, &mAxisA, &mAxisB, mScale);
    Vec3 local;
    Vec3* pLocal = ExpandCoord(&local, pUV);
    *pOut = *pLocal;

    Vec3* pSurface = pm->DirectionToSurfacePosition(&local, pOut);
    *pOut = *pSurface;
    return true;
}

// @ 0x00e0df30
AutoRefCountEvent* cMinimapOverlay::FindEvent(uint32_t key)
{
    MinimapEventNode* pFound;
    mEvents.find(&pFound, &key);
    if (pFound != (MinimapEventNode*)&mEvents.mpRoot)
        return &pFound->mEvent;
    return 0;
}

// @ 0x00e0df70
bool MinimapWin::FindIcon(unsigned id, const float* dir, bool flag)
{
    IconNode* it;
    tree.Find((void**)&it, &id);
    if ((char*)it != tree.sentinel) {
        IWin_s00e0_df70* sub = (IWin_s00e0_df70*)((char*)this + 4);   // IWindow subobject (no null test)
        IWin_s00e0_df70* win = sub->GetChild(id, 1);
        float x = dir[0];
        float y = dir[1];
        float z = dir[2];
        float inv = 1.0f / (float)sqrt((double)(x * x + y * y + z * z + g_13ec4b8));
        Vector3 n;
        n.x = x * inv;
        n.y = y * inv;
        n.z = z * inv;
        *(Vector3*)it->vec = n;
        float f = 0.0f;
        FUN_e0bcb0(it->vec, &n.x, flag ? &f : 0);
        ComputeIconPositionFromMinimapCoords(&n.x, win, flag);
        if (flag)
            FUN_e0d100(win, f, &n.x, &n.x);
        sub->f36();
        IWin_s00e0_df70* parent = win->GetParent();
        IWin_s00e0_df70* next = parent->GetChild(id + 1, 0);
        if (next)
            AnchorWindowToWindow(win, next, 0x300, 0);
        return true;
    }
    return false;
}

// @ 0x00e0e0e0
void __cdecl GetInverseOffset(float* out, IXfObj* o)
{
    XForm xf;
    xf.flags = 0;
    xf.rev = 0;
    xf.scale = g_1485720;
    xf.m.Assign(g_16a2070);
    xf.SetPos(*o->GetPos());
    char tmp[0x24];
    const Matrix3* m = (const Matrix3*)Matrix3FromQuaternion(tmp, o->GetRot());
    xf.SetBasis(*m);
    xf.Invert();
    out[0] = xf.pos.x;
    out[1] = xf.pos.y;
    out[2] = xf.pos.z;
}

// @ 0x00e0e1a0
void MinimapWin::Update()
{
    FUN_00b3d460();
    if (GetUniverseContext() != 0)
        return;
    if (mGrid == 0)
        return;
    int n = squareRaster ? 0x80 : 0x100;
    if (mTexture.p == 0) {
        TexObj* tex = GetTexFactory()->Create(n, 0x80, 1, 0x18, 0x15, 0);
        Image* img = new("UI/MiniMapCivTexture", 0, 0, 0, 0) Image(tex);
        mImage = img;
        FUN_00957c20(img, 1);
        if (!(tex->flags & 1))
            GetTexFactory()->Register(tex);
        IWin_s00e0_df70* sub = (IWin_s00e0_df70*)((char*)this + 4);   // IWindow subobject (no null test)
        Obj19* o = sub->f19();
        Obj3Ret* r3 = 0;
        if (o)
            r3 = (Obj3Ret*)o->f3(0x5234b49);
        r3->Fn82eb80(1, mImage->GetAllocator());
        LockInfo info;
        Tex* t = tex->tex;
        if (t->Lock(2, 0, &info)) {
            memset(info.data, 0, n << 9);
            t->Unlock(&info);
        }
        TexImage* im2 = new("UI/cUIMinimapWin", 0, 0, 0, 0) TexImage(mImage, n, 0x80, 0.0f, 0.0f, 1.0f, 1.0f, 8);
        mTexture.Assign(im2);
    }
    Image* res = mImage;
    int sp10 = 0;
    if (res) {
        sp10 = res->f4;
        if (sp10 == 0) {
            ResObj* r = res->Find(g_147d84e);
            if (r) {
                if (r->GetAllocator()->flags & 1)
                    sp10 = r->GetAllocator()->Fn46f260();
            }
        }
    }
    if (mTexture.p == 0)
        return;
    if (sp10 == 0)
        return;
    if (PlanetModel() == 0)
        return;
    if (PlanetModel()->f24 == 0)
        return;
    GridSub* gs = DebugDrawGrid()->f3();
    unsigned flags = m35c;
    if (flags & 4) {
        if (gs != 0) {
            int mode = GetCurrentGameMode();
            if (mode == 0x1654c01 || GetCurrentGameMode() == 0x1654c02 || GetCurrentGameMode() == 0x1654c10) {
                m358 = 0x10;
                FUN_00e0c820((const float*)gs, g_16a40c8, 0, 0x80, m338, m350, (m35c & 3) != 0);
            } else {
                m358 = 10;
                FUN_00e0cba0((const float*)gs, g_16a40c8, 0, 0x80, m338);
            }
            b364 = 1;
            m35c = 0;
            g_16a40c0 = 0;
            g_16a40bc = 0;
            g_16a40b8 = 1;
            goto L_refresh;
        }
        if (g_16a40b8 != 0)
            goto L_refresh;
        if (g_16a40bc != 0)
            goto L_scroll;
    } else {
        if (g_16a40b8 != 0)
            goto L_refresh;
        if (g_16a40bc != 0)
            goto L_scroll;
        g_16a40c0 = flags;
        m35c = 0;
    }
    if ((g_16a40c0 & 2) == 0)
        goto L_refresh;
L_scroll:
    FUN_00e0cba0((const float*)gs, g_16a40c8 + n * g_16a40bc, g_16a40bc, 8, m338);
    g_16a40c0 &= ~2u;
    g_16a40bc = (g_16a40bc + 8) & 0x7f;
    if (g_16a40bc != 0)
        return;
    g_16a40b8 = 1;
    return;
L_refresh:
    {
        Vector3 v3;
        GetInverseOffset(&v3.x, (IXfObj*)GetActivePlanet());
        Vector3 tmp;
        const Vector3* nv = normalized_safe(&tmp, &v3);
        v3 = *nv;
        char outb[8];
        const float* rr = FUN_00e0b580(outb, 0, &v3, m338, m344, m350, 0);
        int rot = FtoI(rr[0] * g_13f1160) - 0x40;
        if ((rot != m360 && GetCurrentGameMode() != 0x1654c02) || g_16a40b8 != 0 || (g_16a40c0 & 1) != 0) {
            m360 = rot;
            float f12 = gs->f3c;
            int pv = FtoI((f12 + g_1485720) * g_141021c);
            Planet* pl = GetActivePlanet();
            int idx = FtoI((float)(mGrid->count - 1) * pl->sub->f);
            int pcol = mGrid->table[idx];
            const float* fp = DebugDrawGrid()->f51();
            int r = FtoI(fp[0] * g_13f2100);
            int g = FtoI(fp[1] * g_13f2100);
            int b = FtoI(fp[2] * g_13f2100);
            unsigned col1 = (((unsigned)r << 8) | g) << 8 | b;
            unsigned col2;
            if (GetCurrentGameMode() == 0x1654c10) {
                col2 = 0xffffff;
            } else {
                const float* fp2 = DebugDrawGrid()->f52();
                int r2 = FtoI(fp2[0] * g_13f2100);
                int g2 = FtoI(fp2[1] * g_13f2100);
                int b2 = FtoI(fp2[2] * g_13f2100);
                col2 = (((unsigned)r2 << 8) | g2) << 8 | b2;
            }
            UpdatePallete(g_16a38b8, pv, col1, col2, pcol, m358);
            LockInfo info;
            Tex* t = (Tex*)sp10;
            if (t->Lock(10, 0, &info)) {
                unsigned* dst = (unsigned*)info.data;
                const unsigned char* src = g_16a40c8;
                for (unsigned j = 0; j < 0x80; j++) {
                    int e = edge[j];
                    unsigned* p = dst;
                    if (e > 0) {
                        for (int k = 0; k < e; k++) *p++ = 0;
                    }
                    int cnt = n - e * 2;
                    for (int k = 0; k < cnt; k++) {
                        int idx2 = (k << 8) / cnt;
                        *p++ = g_16a38b8[(((idx2 - rot) * 2) & 0x100) + src[idx2]];
                    }
                    if (e > 0) {
                        for (int k = 0; k < e; k++) *p++ = 0;
                    }
                    src += n;
                    dst += n;
                }
                t->Unlock(&info);
            }
            g_16a40c0 &= ~1u;
            g_16a40b8 = 0;
            IWin_s00e0_df70* sub = (IWin_s00e0_df70*)((char*)this + 4);   // IWindow subobject (no null test)
            sub->f36();
            Refresh();
        }
    }
}

// @ 0x00e0e840
void MinimapWin::build_edge_offsets()
{
    int n = squareRaster ? 0x80 : 0x100;
    memset(edge, 0, 0x81);
    unsigned key[3];
    key[0] = 0x361f52ed;
    key[1] = 0x03e421ed;
    key[2] = 0;
    IRef0* ptr = 0;
    ResMgr* mgr = EA_GetManager();
    {
        IRef0* t = ptr;
        if (t) { ptr = 0; t->Release(); }
    }
    if (mgr->Get(key, &ptr, 0, 0, 0, 0)) {
        int w, h;
        unsigned char* data;
        // ptr's secondary interface (+0x18) reports width, height and the pixel data
        ImgInfo* ii = (ImgInfo*)((char*)ptr + 0x18);
        ii->GetInfo(&w, &h, &data);
        int stride = w * 4;
        if (w * 2 > n)
            w = (unsigned)n >> 1;
        if (h * 2 > 0x80)
            h = 0x40;
        if (h > 0) {
            unsigned char* d0 = edge;
            unsigned char* d1 = &edge[0x7f];
            unsigned char* row = data;
            int rows = h;
            do {
                int j = 0;
                if (w > 0) {
                    const unsigned char* px = row + 3;
                    do {
                        if (*px != 0)
                            break;
                        (*d0)++;
                        (*d1)++;
                        j++;
                        px += 4;
                    } while (j < w);
                }
                row += stride;
                d0++;
                d1--;
                rows--;
            } while (rows != 0);
        }
        edge[0x80] = edge[0x7f];
    }
    {
        IRef0* t = ptr;
        if (t) { ptr = 0; t->Release(); }
        if (ptr) ptr->Release();
    }
}

// @ 0x00e0e9a0
void __stdcall e0e9a0(u32 begin, u32 end)
{
    if (begin < end) {
        u32 n = ((end - begin) - 1) / 0x14 + 1;
        char* e = (char*)begin + 0xc;
        do {
            void* p1 = *(void**)(e + 4);
            if (p1) Release(p1);
            void* p0 = *(void**)(e + 0);
            if (p0) Release(p0);
            e += 0x14;
            --n;
        } while (n != 0);
    }
}

// @ 0x00e0e9f0
DataInfo* __cdecl lower_bound_DataInfo(DataInfo* first, DataInfo* last, u32* value)
{
    int n = (int)(last - first);
    while (n > 0) {
        int half = n >> 1;
        DataInfo* mid = first + half;
        if (mid->mKey < *value) {
            first = mid + 1;
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}

// @ 0x00e0ea40
RefHolder* RefHolder::Assign(const RefHolder& o)
{
    mp0 = o.mp0;
    b4 = o.b4;
    if (o.mp8 != mp8) {
        AddRef(o.mp8);
        void* old = mp8;
        mp8 = o.mp8;
        Release(old);
    }
    if (o.mpc != mpc) {
        AddRef(o.mpc);
        void* old = mpc;
        mpc = o.mpc;
        Release(old);
    }
    return this;
}

// @ 0x00e0eab0
bool MinimapWin::Init()
{
    CursorAttachment* ca = new(g_13f6b3c, 0, 0, 0, 0) CursorAttachment();
    {
        IRef0* old = mCursor;
        if ((IRef0*)ca != old) {
            if (ca) ((IRef0*)ca)->AddRef();
            mCursor = (IRef0*)ca;
            if (old) old->Release();
        }
    }
    IRef0* ptr = 0;
    unsigned key[3];
    key[0] = 0x26976266;
    key[1] = 0x03e421ed;
    key[2] = 0;
    ResMgr* mgr = EA_GetManager();
    if (ptr) { IRef0* t = ptr; ptr = 0; t->Release(); }
    mgr->Get(key, &ptr, 0, 0, 0, 0);
    {
        // mGrid is an AutoRefCount<> slot taking the loaded object
        IRef0* nw = ptr;
        GridData* old = mGrid;
        if (nw != (IRef0*)old) {
            if (nw) nw->AddRef();
            mGrid = (GridData*)nw;
            if (old) old->Release();
        }
    }
    if (swMode == 1) {
        unsigned long long t = __rdtsc();
        swLo = (unsigned)t;
        swHi = (unsigned)(t >> 32);
    } else {
        PerfCount t;
        QueryPerformanceCounter(&t);
        swLo = t.lo;
        swHi = t.hi;
    }
    m268 = 0;
    m26c = 0;
    bool ok = Initialize();
    IWin_s00e0_df70* sub = (IWin_s00e0_df70*)((char*)this + 4);   // IWindow subobject (no null test)
    {
        float r[4];
        r[0] = 0.0f;
        r[1] = 0.0f;
        r[2] = (float)width;
        r[3] = (float)height;
        sub->SetArea(r);
    }
    build_edge_offsets();
    m35c |= 4;
    sub->f43(0);
    sub->f23(-1);
    m360 = 0xf000;
    {
        Layout* lay = new(g_147fb90, 0, 0, 0, 0) Layout();
        Layout* old = mLayout;
        if (lay != old) {
            if (lay) lay->AddRef();
            mLayout = lay;
            if (old) old->Release();
        }
    }
    if (mLayout->Init(g_147fb74, 0x40464100, 1, 0x5b598fa))
        mLayout->SetVisibility(0);
    {
        IRef0* nw = GetImageFromLayout(mLayout, 0x5e51b82);
        IRef0* old = mIconImage;
        if (nw != old) {
            if (nw) CallSlot(nw, 0);
            mIconImage = nw;
            if (old) CallSlot(old, 1);
        }
    }
    {
        IRef0* nw = GetImageFromLayout(mLayout, 0x67b4af8);
        IRef0* old = mRoadIcon;
        if (nw != old) {
            if (nw) CallSlot(nw, 0);
            mRoadIcon = nw;
            if (old) CallSlot(old, 1);
        }
    }
    {
        IRef0* nw = GetImageFromLayout(mLayout, 0x67b4ad8);
        IRef0* old = mMapImage;
        if (nw != old) {
            if (nw) CallSlot(nw, 0);
            mMapImage = nw;
            if (old) CallSlot(old, 1);
        }
    }
    {
        MsgServer* srv = SP_MessageServer();
        void* h = handler;
        msgServer = srv;
        handlerPtr = h;
        msgTable = g_147f678;
        msgCount = 0x12;
        m234 = 0;
        if (srv && h) {
            for (unsigned i = 0; i < 0x48; i += 4)
                srv->Register(handler, *(const unsigned*)((const char*)g_147f678 + i));
        }
    }
    SetWindowSPMaterial(sub, g_147fb4c, 0);
    sub->f31(0x400, 1);
    MinimapCamera* cam = new(4, g_147fb38, FUN_009512c0()) MinimapCamera();
    cam->SetOwner(this);
    IWin_s00e0_df70* csub = (IWin_s00e0_df70*)((char*)cam + 4);
    {
        float r[4];
        r[0] = 0.0f;
        r[1] = 0.0f;
        r[2] = (float)width;
        r[3] = (float)height;
        csub->SetArea(r);
    }
    csub->f20(0x6c53765);
    sub->AddChild(csub);
    {
        IRef0* old = mCamera;
        IRef0* nw = (IRef0*)cam;
        if (nw != old) {
            nw->AddRef();
            mCamera = nw;
            if (old) old->Release();
        }
    }
    ((IRef0*)cam)->Release();
    if (ptr) ptr->Release();
    return ok;
}

// @ 0x00e0f050
void __thiscall cSPUIMinimapWin_s00e0_f050::FUN_00e0f050()
{
}

// @ 0x00e0f100
void __thiscall cSPUIMinimapWin_s00e0_f050::FUN_00e0f100(float a1, float a2, float a3, float a4)
{
    (void)a1; (void)a2; (void)a3; (void)a4;
}

// @ 0x00e0f1a0
void __thiscall cIconTree::FUN_00e0f1a0(cIconNode** ppOut, cIconNode* pNode)
{
    --mCount;
    cIconNode* pNext = (cIconNode*)RBTreeIncrement(pNode);
    RBTreeErase(pNode, &mTree);
    cRefCounted* pValue = pNode->mpValue;
    if (pValue)
        pValue->Release();
    operator_delete_array(pNode);
    *ppOut = pNext;
}

// @ 0x00e0f2c0
void __thiscall cSPUIMinimapWin_s00e0_f050::draw_civilization_borders()
{
}

// @ 0x00e0f810
cSPUIMinimapWin_s00e0_f050::~cSPUIMinimapWin_s00e0_f050()
{
}

// @ 0x00e0f9c0
bool __thiscall cSPUIMinimapWin_s00e0_f050::RemoveIcon(uint32_t iconId, int first, int flags)
{
    (void)iconId;
    (void)first;
    (void)flags;
    return true;
}

// @ 0x00e0fb50
bool __thiscall cSPUIMinimapWin_s00e0_f050::RemoveAllIcons()
{
    bool ok = true;
    while (mIconCount > 0) {
        if (ok)
            ok = RemoveIcon(mpFirstIcon->mIconId, 1, 0);
        else
            ok = false;
    }
    return ok;
}

// @ 0x00e0fb90
void __thiscall cSPUIMinimapWin_s00e0_f050::FUN_00e0fb90(uint32_t mask)
{
    (void)mask;
}

// @ 0x00e0fc90
void __thiscall cSPUIMinimapWin_s00e0_f050::CRG_Minimap()
{
}

// @ 0x00e0ff80
void __thiscall cSPUIMinimapWin_s00e0_f050::FUN_00e0ff80()
{
}

// @ 0x00e100e0
void VecRec14::DoInsertValue(cRec14_s00e1_00e0__g7* pos, const cRec14_s00e1_00e0__g7* value)
{
    if (mpEnd != mpCap) {
        if (pos <= value && value < mpEnd)
            value = value + 1;
        if (mpEnd != 0)
            mpEnd->Copy(mpEnd - 1);
        MoveBack(pos, mpEnd - 1, mpEnd);
        pos->mField00 = value->mField00;
        pos->mSub.Assign(&value->mSub);
        mpEnd = mpEnd + 1;
        return;
    }

    int count = (int)((char*)mpEnd - (char*)mpBegin) / 0x14;
    int newCap;
    cRec14_s00e1_00e0__g7* newBuf;
    if (count == 0) {
        newCap = 1;
    } else {
        newCap = count * 2;
        if (newCap == 0) {
            newBuf = 0;
            goto build;
        }
    }
    newBuf = (cRec14_s00e1_00e0__g7*)operator_new_rec(newCap * 0x14, "Simulator", 0, 0,
                                       g_allocator, 0xd1);
build:
    {
        cRec14_s00e1_00e0__g7* oldBegin = mpBegin;
        cRec14_s00e1_00e0__g7* mid = (cRec14_s00e1_00e0__g7*)CopyRecRange(oldBegin, pos, newBuf);
        DestroyRecRange(oldBegin, pos, newBuf);
        if (mid != 0)
            mid->Copy(value);
        cRec14_s00e1_00e0__g7* after = (cRec14_s00e1_00e0__g7*)CopyRecRange(pos, mpEnd, mid + 1);
        DestroyRecRange(pos, mpEnd, mid + 1);
        if (mpBegin != 0)
            operator_delete_rec(mpBegin);
        mpEnd = after;
        mpBegin = newBuf;
        mpCap = newBuf + newCap;
    }
}

// @ 0x00e10220
bool CMinimapWin::HandleNotification(cFeedbackEvent_s00e1_00e0__g7* event)
{
    float pos[3];
    void* self = this;
    if (event->mMessageId == 0x287259f6) {
        if (SP_PlanetModel()) {
            void* obj = event->mpObject;
            void* dir = (*(void* (__thiscall**)(void*))(*(u32*)obj + 0x1c))(obj);
            void* v = &dir;
            cIconInfo* info = (cIconInfo*)FUN_00e0ff80((char*)self + 0x31c, (const unsigned*)v, v);
            void* p = (char*)info + 4;
            SP_PlanetModel_DirectionToSurfacePosition(SP_PlanetModel(), pos, (float*)p);
            u32 flags = (~(event->mFlags18 >> 2) & 2) | 0x3e8;
            FUN_00e0b990(self, pos, flags, 0, 0);
        }
        return true;
    }

    if (event->mMessageId != 0x13 || event->mpObject == 0)
        goto l_ret;

    {
        void* obj = event->mpObject;
        void* found = (*(void* (__thiscall**)(void*, unsigned))(*(u32*)obj + 0xc))(obj, 0x8ed27e7a);
        if (!found)
            goto l_ret;

        void* obj2 = event->mpObject;
        u32 v = (u32)(*(void* (__thiscall**)(void*))(*(u32*)obj2 + 0x1c))(obj2);

        u32 f0c = event->mField0c;
        u32 f10 = event->mField10;
        if (((f0c >> 3) & 1) == 0) {
            if (((f10 >> 3) & 1) != 0) {
                void* layout = *(void**)((char*)self + 0x988);
                if (*(char*)((char*)layout + 0x44) != 0) {
                    void* root = cSPUIPropertyLayout_GetRootWindow(layout);
                    (*(void (__thiscall**)(void*, int, int))(*(u32*)root + 0x7c))(root, 1, 0);
                    layout = *(void**)((char*)self + 0x988);
                    (*(void (__thiscall**)(void*))(*(u32*)layout + 0x24))(layout);
                }
                FUN_0067cab0(0);
                FUN_008017f0(0);
                void* h = *(void**)((char*)self + 0x980);
                if (h != 0) {
                    *(void**)((char*)self + 0x980) = 0;
                    (*(void (__thiscall**)(void*))(*(u32*)h + 4))(h);
                    return FUN_00950bb0(event);
                }
            }
            goto l_ret;
        }

        if (((f10 >> 3) & 1) != 0)
            goto l_ret;

        void* it;
        eastl_rbtree_find(&it, (char*)self + 0x31c, &v);
        if (it == (char*)self + 0x320)
            goto l_ret;

        {
            void* city = *(void**)((char*)it + 0x28);
            u32 key10 = *(u32*)((char*)it + 0x10);
            if (city == 0)
                goto l_ret;
            u32 fl = *(u32*)((char*)it + 0x24);
            if (fl & 1) {
                if (SP_GetCurrentGameMode() == &g_modeCityHall) {
                    void* layout = *(void**)((char*)self + 0x988);
                    (*(void (__thiscall**)(void*, unsigned))(*(u32*)layout + 0x28))(layout, 0x5b598f6);
                    FUN_00bdde70(layout, city);
                    void* root = cSPUIPropertyLayout_GetRootWindow(layout);
                    void* btn = (*(void* (__thiscall**)(void*, int))(*(u32*)found + 0x10))(found, 0);
                    void* bwin = (*(void* (__thiscall**)(void*))(*(u32*)btn + 0x10))(btn);
                    float* area = (*(float* (__thiscall**)(void*))(*(u32*)bwin + 0x34))(bwin);
                    (*(void (__thiscall**)(void*, float*, float, int))(*(u32*)btn + 0xc0))(btn, pos, (area[2] - area[0]) * g_halfConst, 0);
                    (*(void (__thiscall**)(void*, void*, void*, void*))(*(u32*)root + 0x34))(root, &pos[0], &pos[1], &pos[2]);
                    FUN_00e2e8d0(btn, 0, 0x41600000, 0);
                    (*(void (__thiscall**)(void*, void*, void*))(*(u32*)root + 0x64))(root, 0, 0);
                    (*(void (__thiscall**)(void*, int, int))(*(u32*)root + 0x7c))(root, 1, 1);
                }
                FUN_00b5f950((char*)self + 0x980, FUN_00bd9bf0(city));
            } else if (fl & 0x100) {
                void* p = (*(void* (__thiscall**)(void*))(*(u32*)city + 0x10))(city);
                FUN_00b25f40(SP_NounManager(p));
                FUN_00b5f950((char*)self + 0x980, FUN_00bd9bf0(city));
            } else if (fl & 0x4000) {
                void* r = (*(void* (__thiscall**)(void*))(*(u32*)city + 0x4c))(city);
                if (r != (void*)-1) {
                    r = (*(void* (__thiscall**)(void*))(*(u32*)city + 0x4c))(city);
                    FUN_00b25f40(SP_NounManager(r));
                    FUN_00b5f950((char*)self + 0x980, FUN_00bd9bf0(city));
                }
            } else if (fl & 0x20) {
                SP_GetCurrentGameMode();
                if (SP_GetCurrentGameMode() == &g_modeTribe) {
                    void* win = (*(void* (__thiscall**)(void*, u32, int))(*(u32*)((char*)self + 4) + 0xf0))((char*)self + 4, key10, 1);
                    if (win) {
                        void* city2 = FUN_00b1fc00(*(u32*)((char*)it + 0x28));
                        if (city2) {
                            void* q = FUN_00c6aa30(city2);
                            if (q) {
                                void* arg = (char*)q + 0x504;
                                void* r = FUN_010666a0(win, arg);
                                FUN_01067e70(r, arg);
                            }
                        }
                    }
                }
            }
        }
    }

l_ret:
    return FUN_00950bb0(event);
}

// @ 0x00e10580
bool cSPUIMinimapWin_s00e1_00e0::AddIcon(uint32_t id, const cIconInfo* info, int parentID, bool flag)
{
    cIconInfo local(*info);
    IWin_s00e1_00e0* parent = 0;
    if (parentID) {
        parent = SubWin()->GetChild(parentID, 0);
        if (!parent)
            return false;
    }
    uint32_t mode = App()->GetGameMode();
    if (!(local.mFlags & 8) && local.mpObject) {
        IQueried* q = local.mpObject->Query(0x1186577);
        if (q && q->IsMinimapObject())
            local.mFlags |= 8;
    }
    uint32_t imageID = PickImageID(local.mFlags, mode, local.mImageID);

    Image_s00e1_00e0* image = GetImageFromLayout(mpLayout, imageID);
    if (image)
        image->AddRef();

    WinButtonObj* wb = (WinButtonObj*)TooltipAlloc(0x888, 4, g_cityIconName, GetAllocator());
    IButtonControl* button = 0;
    if (wb) {
        new (wb) WinButtonObj();
        wb->vt0 = g_vtWinButton0;
        wb->vt1 = g_vtWinButton1;
        wb->vt2 = g_vtWinButton2;
        button = (IButtonControl*)&wb->vt2;
    }
    IWin_s00e1_00e0* win = button->GetWindow();

    DrawableObj* dr = (DrawableObj*)TooltipAlloc(0x18, 4, g_cityIconDrawableName, GetAllocator());
    IDrawable* drawable = 0;
    if (dr) {
        new (dr) DrawableObj();
        dr->vt0 = g_vtDrawable0;
        dr->vt1 = g_vtDrawable1;
        dr->vt2 = g_vtDrawable2;
        drawable = (IDrawable*)((char*)dr + 0xc);
    }
    drawable->SetImage(image, 0);
    float size[2];
    size[0] = size[1] = (float)image->mWidth;
    drawable->GetSizeIface()->SetSize(size, 0, 0);
    button->SetDrawable(drawable);
    win->SetID(id);
    win->SetVisible(0);
    win->SetColor(local.mType ? local.mType : (uint32_t)-1);
    Math::Rectangle area(0.0f, 0.0f, size[0], size[1]);
    win->SetArea(&area);

    bool result;
    if (local.mFlags & 2) {
        if (mode == 0x1654c02) {
            mbTradeRoutesDirty = true;
        } else {
            win->SetSize(size[0] * g_half, size[1] * g_half);
        }
    }
    float inv = 1.0f / (float)sqrt((double)(local.mZ * local.mZ + local.mY * local.mY + local.mX * local.mX + g_epsilon));
    Vector3 n;
    n.x = inv * local.mX;
    n.y = local.mY * inv;
    n.z = local.mZ * inv;
    local.mX = n.x;
    local.mY = n.y;
    local.mZ = n.z;
    float f = 0.0f;
    FUN_e0bcb0(&local.mX, &n.x, flag ? &f : 0);
    ComputeIconPositionFromMinimapCoords(&n.x, win, false);
    if (!parent) {
        mIconInfos.At(id) = local;
        IWin_s00e1_00e0* self = SubWin();
        result = self->AddChild(win);
        if (mode == 0x1654c10) {
            if (local.mFlags & 0x80)
                self->PlaceAfter(win);
            else
                self->PlaceBefore(win);
        } else if (!(local.mFlags & 0x18021)) {
            self->PlaceAfter(win);
        } else {
            self->PlaceBefore(win);
        }
    } else {
        const float* a = parent->GetArea();
        float x1 = a[0], y1 = a[1];
        Math::Rectangle r(-x1 + x1, -y1 + y1, a[2] + -x1, a[3] + -y1);
        FitWindowToArea(win, &r);
        win->SetFlag(1, 1);
        win->SetFlag(0x10, 1);
        mIconInfos.At(id) = local;
        result = parent->AddChild(win);
        parent->PlaceAfter(win);
    }
    if (flag)
        FUN_e0d100(win, f, &n.x);
    image->Release();
    return result;
}

// @ 0x00e10c10
cRec14_s00e1_00e0__g7* VecRec14::insert(cRec14_s00e1_00e0__g7* pos, const cRec14_s00e1_00e0__g7* value)
{
    int idx = (int)((char*)pos - (char*)mpBegin) / 0x14;
    cRec14_s00e1_00e0__g7* end = mpEnd;
    if (pos == end && end != mpCap) {
        mpEnd = end + 1;
        if (end != 0)
            end->Copy(value);
    } else {
        DoInsertValue(pos, value);
    }
    return mpBegin + idx;
}

// @ 0x00e10c80
void CMinimapWin::Shutdown()
{
    if (mpHandlerTarget != 0) {
        IRefcount* h = mpHandlerTarget;
        mpHandlerTarget = 0;
        FUN_00571db0(h, mHandlerArg228, mHandlerArg22c, mHandlerArg230, mHandlerArg234);
    }
    if (mpRef24c != 0) { IRefcount* p = mpRef24c; mpRef24c = 0; p->Release(); }
    if (mpRef250 != 0) { IRefcount* p = mpRef250; mpRef250 = 0; p->Release(); }
    if (mpRef258 != 0) { IRefcount* p = mpRef258; mpRef258 = 0; p->v08(); }
    if (mpRef244 != 0) { IRefcount* p = mpRef244; mpRef244 = 0; p->Release(); }
    if (mpRef248 != 0) { IRefcount* p = mpRef248; mpRef248 = 0; p->Release(); }
    mField27c = 0;
    if (mpRef254 != 0) { IRefcount* p = mpRef254; mpRef254 = 0; p->Release(); }

    FUN_00e0f160(mpTreeRoot);
    mpTreeAnchor = (char*)this + 0x320;
    mpTreeEnd = (char*)this + 0x320;
    mpTreeRoot = 0;
    mbTreeFlag = 0;
    mTreeCount = 0;

    if (mpRef988 != 0) { IRefcount* p = mpRef988; mpRef988 = 0; p->Release(); }

    ((CVec3Store*)&mVecBegin)->erase(mVecEnd, mVecBegin);

    {
        void* begin = g_feedbackBegin;
        void* end = g_feedbackEnd;
        void* r = FUN_00e0f010(end, end, begin);
        FUN_00e0e9a0(r, g_feedbackEnd);
        int n = (int)((char*)begin - (char*)end) / 0x14;
        g_feedbackEnd = (char*)end + n * 0x14;
    }

    if (mpRef980 != 0) { IRefcount* p = mpRef980; mpRef980 = 0; p->Release(); }
    if (mpRef984 != 0) { IRefcount* p = mpRef984; mpRef984 = 0; p->Release(); }
    ((CBaseWindow*)this)->Shutdown();
}

// @ 0x00e10e30
void cSPUIMinimapWin_s00e1_0e30::draw_trade_routes(EA::UTFWin::Draw2D_s00e1_0e30& draw)
{
    Math::Rectangle_s00e1_0e30 uv(0.0f, 0.0f, 1.0f, 1.0f);
    uint32_t mode = SP::GetCurrentGameMode();
    if (mode != 0x1654c01 && mode != 0x1654c02) {
        cDotStyle styles[2] = {
            { 0.5f, 0.5f, 0xffbfbfff, 20.0f },
            { 1.0f, 1.0f, 0xffffffbf, 6.0f },
        };
        cRouteObjectVector& routes = SP::NounManager()->GetGameDataVector(
            (GameDataFn)GameDataFn_cd7d10, (GameDataFn)GameDataFn_d3d420,
            (GameDataFn)GameDataFn_e10060, (GameDataFn)GameDataFn_b1e500, 0x2b8a4e7)->mData;
        for (uint32_t i = 0; i < routes.size(); ++i) {
            cRouteObject* route = routes[i];
            cDotStyle* style = &styles[0];
            if (route->mRouteKind == 1)
                style = &styles[1];
            if (route->NumPoints() > 1) {
                float halfWidth = style->mHalfWidth;
                float halfHeight = style->mHalfHeight;
                float minDistSq = (halfWidth + halfHeight) * style->mSpacing;
                Vector3_s00e1_0e30 prev = route->mpPointsBegin[0];
                Vector2 lastXY;
                WorldXYZToMinimapXY(prev, lastXY, false);
                draw.SetColor(style->mColor);
                draw.DrawImage(Math::Rectangle_s00e1_0e30(lastXY.x - halfWidth, lastXY.y - halfHeight,
                                               lastXY.x + halfWidth, lastXY.y + halfHeight),
                               mpRoadIconImage, uv);
                for (uint32_t j = 1; j < route->NumPoints(); ++j) {
                    Vector3_s00e1_0e30 cur = route->mpPointsBegin[j];
                    float dx = cur.x - prev.x;
                    float dy = cur.y - prev.y;
                    float dz = cur.z - prev.z;
                    float step = 2.0f / sqrtf(dx * dx + dy * dy + dz * dz);
                    float t = 0.0f;
                    do {
                        t = step + t;
                        float s = 1.0f - t;
                        Vector3_s00e1_0e30 p(prev.x * s + cur.x * t, prev.y * s + cur.y * t, prev.z * s + cur.z * t);
                        Vector2 xy;
                        WorldXYZToMinimapXY(p, xy, false);
                        float ex = xy.x - lastXY.x;
                        float ey = xy.y - lastXY.y;
                        if (ex * ex + ey * ey > minDistSq) {
                            lastXY = xy;
                            draw.DrawImage(Math::Rectangle_s00e1_0e30(xy.x - halfWidth, xy.y - halfHeight,
                                                           xy.x + halfWidth, xy.y + halfHeight),
                                           mpRoadIconImage, uv);
                        }
                    } while (t < 1.0f);
                    prev = cur;
                }
            }
        }
        return;
    }

    draw.SetColor(0xffbfbfff);
    cPlanetModel_s00e1_0e30* model = SP::PlanetModel_s00e1_0e30();
    cPlanet_s00e1_0e30* planet = model ? model->mpPlanet : 0;
    if (mbTradeRoutesDirty && planet) {
        mbTradeRoutesDirty = false;
        mTradeRouteDots.clear();

        // Points farther from the camera than the horizon are on the far side.
        Vector2 range = { 0.0f, 1.0f };
        Vector3_s00e1_0e30 horizon = GetHorizonPoint(planet->GetHorizonSource(), range, mWorldCameraPos,
                                          mWorldCameraDir, mCameraParam);
        float inv = 1.0f / sqrtf(horizon.y * horizon.y + horizon.z * horizon.z +
                                 horizon.x * horizon.x + 1e-8f);
        float hx = mWorldCameraPos.x - horizon.x * inv;
        float hy = mWorldCameraPos.y - horizon.y * inv;
        float hz = mWorldCameraPos.z - horizon.z * inv;
        float horizonDistSq = hx * hx + hy * hy + hz * hz;

        int count = planet->GetTradeRouteCount();
        for (int i = 0; i < count; ++i) {
            cTradeRoute* route = planet->GetTradeRoute(i);
            if (route && route->NumPoints() > 1) {
                Vector3_s00e1_0e30 prev = route->mpPointsBegin[0].mPosition;
                Vector2 lastXY;
                WorldXYZToMinimapXY(prev, lastXY, false);
                inv = 1.0f / sqrtf(prev.x * prev.x + prev.y * prev.y + prev.z * prev.z + 1e-8f);
                hx = mWorldCameraPos.x - prev.x * inv;
                hy = mWorldCameraPos.y - prev.y * inv;
                hz = mWorldCameraPos.z - prev.z * inv;
                if (hx * hx + hy * hy + hz * hz < horizonDistSq)
                    mTradeRouteDots.push_back(Vector3_s00e1_0e30(lastXY.x, lastXY.y, route->mpPointsBegin[0].mSize));

                for (uint32_t j = 1; j < route->NumPoints(); ++j) {
                    float size = route->mpPointsBegin[j].mSize;
                    Vector3_s00e1_0e30 cur = route->mpPointsBegin[j].mPosition;
                    inv = 1.0f / sqrtf(cur.y * cur.y + cur.z * cur.z + cur.x * cur.x + 1e-8f);
                    hx = mWorldCameraPos.x - cur.x * inv;
                    hy = mWorldCameraPos.y - cur.y * inv;
                    hz = mWorldCameraPos.z - cur.z * inv;
                    if (hx * hx + hy * hy + hz * hz < horizonDistSq) {
                        float dx = cur.x - prev.x;
                        float dy = cur.y - prev.y;
                        float dz = cur.z - prev.z;
                        float step = 2.0f / sqrtf(dx * dx + dy * dy + dz * dz);
                        float t = 0.0f;
                        do {
                            t = step + t;
                            float s = 1.0f - t;
                            Vector3_s00e1_0e30 p(prev.x * s + cur.x * t, prev.y * s + cur.y * t,
                                      prev.z * s + cur.z * t);
                            Vector2 xy;
                            WorldXYZToMinimapXY(p, xy, false);
                            float ex = xy.x - lastXY.x;
                            float ey = xy.y - lastXY.y;
                            if (ex * ex + ey * ey > 12.0f) {
                                lastXY = xy;
                                mTradeRouteDots.push_back(Vector3_s00e1_0e30(xy.x, xy.y, size));
                            }
                        } while (t < 1.0f);
                    }
                    prev = cur;
                }
            }
        }
    }

    uint32_t n = mTradeRouteDots.size();
    for (uint32_t k = 0; k < n; ++k) {
        Vector3_s00e1_0e30& dot = mTradeRouteDots[k];
        float r = dot.z * 1.5f;
        draw.DrawImage(Math::Rectangle_s00e1_0e30(dot.x - r, dot.y - r, dot.x + r, dot.y + r),
                       mpRoadIconImage, uv);
    }
}

// @ 0x00e118b0
cInsertResult cDataArray::insert(const cDataInfo& value)
{
    cDataInfo* end = mpEnd;
    cDataInfo* it = lower_bound_DataInfo(mpBegin, end, value.mKey, mCompare);
    if (it != end && !(value.mKey < it->mKey))
        return cInsertResult(it, false);
    return cInsertResult(insert_at(it, value), true);
}

// @ 0x00e11910
cDataValue& cDataArray::FindOrInsert(uint32_t key)
{
    cDataInfo* end = mpEnd;
    cDataInfo* it = find_DataInfo(*this, key);
    if (it == end) {
        it = insert(cDataInfo(key)).mpNode;
        it->mValue.mId = key;
        it->mValue.mbDirty = true;
    }
    return it->mValue;
}

// @ 0x00e119c0
bool cSPUIMinimapWin_s00e1_0e30::OnRebuild(EA::UTFWin::RenderContext_s00e1_0e30* ctx)
{
    RebuildBaseWindow(this ? &mWindow : 0);
    EA::UTFWin::Draw2D_s00e1_0e30* draw = ctx->Begin2D(0);
    if (mpTexture) {
        draw->DrawImage(Math::Rectangle_s00e1_0e30(0.0f, 0.0f,
                                        (float)mStopwatchField0, (float)mStopwatchField1),
                        mpTexture,
                        Math::Rectangle_s00e1_0e30(0.0f, 0.0f, 1.0f, 1.0f));
    }
    draw_trade_routes(*draw);
    ctx->End2D();
    cHashable* border = mpBorderRenderable;
    if (border) {
        cDataValue& value = gDataMap.FindOrInsert(border->GetID());
        if (value.mbDirty) {
            value.draw_civilization_borders(ctx, this);
            value.mbDirty = false;
        }
        ctx->AddRenderable(value.mPtr0.mpObject);
    }
    return true;
}
