// src/game/SPGonzago/SPUIMinimapWin.cpp -- migrated from slice(s) s00e0f050, s00e0df70, s00e0c2a0, s00e0b350, s00e0a4c0 by tools/migrate/rewrite.py
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
u8    g_16a1fa0;
u32   g_16a2040;
u32   g_16a2044;
u32   g_16a2048;
u32   g_16a1f9c;
u32   g_16a1f98;
extern "C" void*  __cdecl memcpy(void*, const void*, unsigned int);
extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl atan2(double, double);
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
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
