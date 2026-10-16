// src/game/Spui/SPUIHelpers.cpp -- migrated from slice(s) s00829bc0, s00809700, s008087f0, s00807840, s008068d0, s00805940, s00804920 by tools/migrate/rewrite.py
// Object file: Spui/SPUIHelpers.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/IWindow.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* SP_WindowManager();                 // 0x0067caa0
extern "C" void* FUN_009512b0(void*);
extern "C" void* GetDefaultAllocator();
extern "C" void  DeallocEAL(void*);
#include <intrin.h>
#include "cSPUILayout.h"
#include <math.h>
#include <new>

// ---- items of slice s00804920 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_WindowManager();                 // 0x0067caa0
extern "C" void* FUN_009512b0(void*);
extern "C" void* GetDefaultAllocator();
extern "C" void  DeallocEAL(void*);
static inline void* VSlot(void* p, unsigned byteOff) { return (void*)&((void**)*(void**)p)[byteOff / 4]; }
static inline void* VFn(void* p, unsigned byteOff) { return ((void**)*(void**)p)[byteOff / 4]; }
static inline void AddRefObj(void* p) { (*(void(__thiscall**)(void*))VSlot(p, 0))(p); }
struct Helper {
    void   H70(void*, void*);
    void   Hf0(float, float);
    void   Hc0(int);
    void   H40(void*, float, float, void*);
    void   Hb0();
    float  H70b();
};
struct IWnd {
    void H0();
    void H4();
    int  H30();
    void H5c(int);
    void H90();
};
struct WMgr {
    virtual void  s0();   // +0x00
    virtual void* s1();   // +0x04
    virtual void  s2();   // +0x08
    virtual void  s3();   // +0x0c
    virtual void  s4();   // +0x10
    virtual void  s5();   // +0x14
    virtual void  s6();   // +0x18
    virtual void  s7();   // +0x1c
    virtual void  s8();   // +0x20
    virtual void  s9();   // +0x24
    virtual void  s10();  // +0x28
    virtual void  s11();  // +0x2c
    virtual void  s12();  // +0x30
    virtual void  s13();  // +0x34
    virtual void  s14();  // +0x38
    virtual void  s15();  // +0x3c
    virtual void  s16();  // +0x40
    virtual void  s17();  // +0x44
    virtual void* s18(int); // +0x48
};
static inline void* WMStuff() {
    WMgr* wm = (WMgr*)SP_WindowManager();
    return wm->s1();
}
static inline Helper* WMObj() {
    void* r = WMStuff();
    return r ? (Helper*)((char*)r - 4) : 0;
}
struct VThunk8 { void CallVt8(int a, int b, int c, int d, int e); };
void* g_alloc;
// ---- items of slice s00804920 end

// ---- items of slice s00805940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_0067dd60();                         // texture/image manager
extern "C" void* FUN_009512c0();                         // GetUIAllocator
extern "C" void* FUN_009512d0(int, int, const char*, void*);
extern "C" void* FUN_008332a0();
extern "C" void* FUN_008332d0();
extern "C" void* SPKeyFromName(void*, int, int, int);    // 0x0068d840
extern "C" void* AllocEAL(unsigned size, const char* name, int, int, int, int);  // 0x00f473a0
extern float g_13ec4d0;   // default window size
extern unsigned char DAT_013f6b3c;
struct ImgHelper {
    void* UI_Image_Image(void*);                                            // 0x008333b0
    void* UI_Image_Image2(void*, int, int, float, float, float, float);     // 0x009579f0
};
struct WindowHelper {
    void* UI_Window_Window();                                               // 0x00962a10
    void* UI_WinText_WinText();                                             // 0x00989000
    void* UI_WinButton_WinButton();                                         // 0x00966f90
};
struct LayoutHelper {
    void* FindWindowByID(int, int);                                         // 0x008105b0
};
struct DrawHelper { void* FUN_00830cf0(int); };                             // 0x00830cf0
struct Vec4 { float x, y, z, w; };
#define S(n) virtual void* v##n();
struct W {
    S(00) S(04) S(08)
    virtual void* m0c(int);          // +0x0c  Cast(typeID)
    S(10)
    virtual void  m14(void*, void*); // +0x14
    S(18)
    virtual void  m1c(int);          // +0x1c
    virtual void* m20(int, int, int);// +0x20
    S(24) S(28) S(2c) S(30)
    S(34)                            // +0x34 GetArea -> Vec4*
    S(38)
    S(3c) S(40) S(44) S(48)
    virtual void  m4c(int, int);     // +0x4c
    virtual void  m50(int);          // +0x50
    virtual void  m54(int);          // +0x54
    S(58)
    virtual void  m5c(int);          // +0x5c
    virtual void  m60(void*);        // +0x60
    virtual void  m64(float, float); // +0x64
    virtual void  m68(float, float); // +0x68
    S(6c) S(70) S(74) S(78)
    virtual void  m7c(int, int);     // +0x7c
    S(80) S(84) S(88) S(8c)
    S(90)
    S(94) S(98) S(9c) S(a0) S(a4)
    S(a8)
    virtual void  mAc(int);          // +0xac
    virtual void  mB0(void*);        // +0xb0
    S(b4) S(b8) S(bc)
    virtual void* mC0(void*, int);   // +0xc0
    S(c4) S(c8) S(cc) S(d0) S(d4)
    virtual void  mD8(void*);        // +0xd8
    S(dc) S(e0) S(e4) S(e8) S(ec) S(f0) S(f4) S(f8) S(fc) S(100) S(104) S(108)
    virtual void* m10c(void*);       // +0x10c
};
struct DWin {
    S(00) S(04) S(08)
    virtual void* m0c(int);
    S(10)
    virtual void  m14(void*, void*);
    virtual void  m18(void*, int, int);
    virtual void  m1c(int);
    virtual void* m20(int, int);
    S(24) S(28) S(2c) S(30)
    S(34)
    S(38)
    S(3c) S(40) S(44) S(48)
    virtual void  m4c(int, int);
    virtual void  m50(int);
    virtual void  m54(int);
    S(58)
    virtual void  m5c(int);
    virtual void  m60(void*);
    virtual void  m64(float, float);
    virtual void  m68(float, float);
    S(6c) S(70) S(74) S(78)
    virtual void  m7c(int, int);
    S(80) S(84) S(88) S(8c)
    S(90)
    S(94) S(98) S(9c) S(a0) S(a4)
    S(a8)
    virtual void  mAc(int);
    virtual void  mB0(void*);
    S(b4) S(b8) S(bc)
    virtual void* mC0(void*, int);
    S(c4) S(c8) S(cc) S(d0) S(d4)
    virtual void  mD8(void*);
    S(dc) S(e0) S(e4) S(e8) S(ec) S(f0) S(f4) S(f8) S(fc) S(100) S(104) S(108)
    virtual void* m10c(void*);
};
struct W2 {
    S(00) S(04) S(08)
    virtual void* m0c(int);
    virtual void* m10(int);
    S(14) S(18)
    S(1c) S(20) S(24) S(28) S(2c) S(30) S(34) S(38) S(3c) S(40) S(44) S(48)
    S(4c) S(50) S(54) S(58) S(5c) S(60) S(64) S(68) S(6c) S(70) S(74) S(78)
    S(7c) S(80) S(84) S(88) S(8c) S(90) S(94) S(98) S(9c) S(a0) S(a4)
    S(a8)
};
struct WMgr_s0080_5940 { virtual void s0(); virtual void* s1(); };
// ---- items of slice s00805940 end


// callees this slice defines outside this object (rewrite.py held_callee_protos)
char CreateImageFromResource2(void* key, void** out, char flag, int a, int b);  // 0x00806230 (stays in the slice: not this object's)

// ---- items of slice s008068d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_008051b0(int);
extern "C" void* FUN_008055a0(void*);
extern "C" char  FUN_008055c0(void*, void*);
extern "C" char  FUN_0082aa20(void*, void*, int);
extern "C" void  FUN_0082a450();
extern "C" void  FUN_0082a500();
extern "C" void  FUN_008053e0();
extern "C" void  FUN_00805400();
extern "C" void  FUN_00830d10(void);
extern "C" void  FUN_008311f0(void);
extern "C" void* operator_new(unsigned size, const char* name, int, int, int, int);  // 0x00f473a0
extern "C" void  operator_delete(void*);                   // 0x00f47380
extern unsigned char DAT_01544384;
extern unsigned char DAT_01544388;
extern unsigned char DAT_0154438c;
extern unsigned char DAT_01544390;
extern float DAT_01471064;
extern void* PTR_FUN_01417958;
extern void* PTR_FUN_01403934;
struct ObjDtor { void dtor(); };
struct StdDraw {
    void  SetImageIcon(int, void*);     // 0x00831760
    void  SetImageIconColor(int, void*);// 0x00831380
    void  GetIconColor(void*, int);     // 0x00830d60
    int   FUN_00830d10(int);            // 0x00830d10
    void  FUN_008311f0(int, int);       // 0x008311f0
    void* Pick(int);                    // 0x00830cf0
};
struct StdDrawCtor { void* ctor(); };   // 0x00988420
struct ImgDrawCtor { void* ctor(); };   // 0x0097d8d0
struct ScrollCtor  { void* ctor(); };   // 0x0082a040
struct Layout { void Shutdown(int); };  // 0x00811ad0 (cSPUILayout::Shutdown, this=+8)
struct Tooltip { void SetText(void*, void*, void*); };  // 0x00835ed0
struct W_s0080_68d0 {
    S(00) S(04) S(08)
    virtual void* m0c(int);          // +0x0c
    virtual void* m10(int);          // +0x10
    virtual void  m14(int);          // +0x14
    S(18)
    S(1c) S(20) S(24) S(28) S(2c) S(30)
    S(34) S(38)
    S(3c) S(40) S(44) S(48) S(4c) S(50) S(54) S(58) S(5c) S(60)
    virtual void  m64(float, float); // +0x64
    S(68)
    virtual void  m6c(void*);        // +0x6c
    virtual void  m70(float, float); // +0x70
    S(74) S(78) S(7c) S(80) S(84) S(88)
    virtual void  m8c(int);          // +0x8c
    S(90) S(94) S(98) S(9c) S(a0) S(a4) S(a8) S(ac)
    virtual void  mB0(void*);        // +0xb0
    virtual void* mB4(int);          // +0xb4
    virtual void  mB8(int, void*);   // +0xb8
    S(bc)
    virtual void* mC0(void*, int, int);// +0xc0
    S(c4) S(c8) S(cc) S(d0) S(d4) S(d8) S(dc) S(e0) S(e4) S(e8) S(ec)
    S(f0) S(f4) S(f8) S(fc) S(100) S(104)
    virtual void  m108(void*);       // +0x108
    virtual void* m10c(void*);       // +0x10c
};
struct FixedAllocCtor {
    void* ctor(int, int, int, int, int, void*, void*, int);  // EA::Allocator::FixedAllocatorBase
};
// ---- items of slice s008068d0 end

// ---- items of slice s00807840 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char  CreateImageFromResource(void*, void**, char, int, int);  // 0x00806230
extern "C" void* SPUIShader_AcquireShaderProxy();            // 0x0082f630
extern "C" void  FUN_0095eb00(int);
extern "C" void  FUN_0095ec30(int);
extern "C" void  FUN_0095ed60(int);
extern "C" void  FUN_0095f5c0(void*, float);
extern "C" void  FUN_0095ea30(void*);
extern "C" void  FUN_0095e890(void*);
extern "C" void* SP_PropertyManager();                       // 0x00?????? // 0x0067de30
extern "C" char  SP_GetPropertyAsUint32Array(void*, int, int*, int*);   // 0x006a0840 (equiv t2)
extern "C" int   SP_OpenRecordAsStream(void*, void*);   // 0x00686490 (equiv t2)
extern float DAT_01485720;
extern void* SYM_13fa72c;
extern void* SYM_14179b8;
extern void* SYM_141799c;
extern void* SYM_1417a68;
extern void* SYM_1417a4c;
extern void* SYM_14178b0;
extern void* SYM_1417874;
extern void* SYM_141785c;
extern void* SYM_141788c;
extern int DAT_0164c4b8;
extern char DAT_0164c598;
#define ABS(x) ((x) < 0 ? -(x) : (x))
struct CbProc {
    char pad[0xc];
    int (*mpFn)(void*, void*, void*);
    void* mpCtx;
    char Invoke(void* a, void* b);
};
struct CbWinProc {
    void* vt0;    // +0x00
    void* vt1;    // +0x04
    int f8;       // +0x08
    void* fC;     // +0x0c
    void* f10;    // +0x10
    void* f14;    // +0x14
    int f18;      // +0x18
};
struct Xform {
    void* vt0;    // +0x00
    void* vt1;    // +0x04
    int f8;       // +0x08
    float fC;     // +0x0c
    float f10;    // +0x10
    float f14;    // +0x14
    float f18;    // +0x18
    float f1c;    // +0x1c
    float f20;    // +0x20
    float f24;    // +0x24
    float f28;    // +0x28
};
extern float DAT_01544384_s0080_7840;
extern float DAT_01544388_s0080_7840;
extern float DAT_0154438c_s0080_7840;
extern float DAT_01544390_s0080_7840;
struct W_s0080_7840 {
    S(00) S(04) S(08) S(0c) S(10) S(14) S(18) S(1c) S(20) S(24) S(28) S(2c) S(30)
    S(34) S(38) S(3c) S(40) S(44) S(48) S(4c) S(50) S(54) S(58) S(5c) S(60)
    S(64) S(68) S(6c) S(70) S(74) S(78) S(7c) S(80) S(84) S(88) S(8c) S(90)
    S(94) S(98) S(9c) S(a0) S(a4) S(a8) S(ac) S(b0) S(b4) S(b8) S(bc) S(c0)
    S(c4) S(c8)
    virtual void  mCc(void*);        // +0xcc
    virtual void* vD0();             // +0xd0
    S(d4) S(d8) S(dc) S(e0) S(e4) S(e8) S(ec) S(f0) S(f4) S(f8) S(fc) S(100)
    virtual void  m104(void*);       // +0x104
};
struct XAlign { void Update(void*, void*); };
int VisitWindowTreeDepthFirst(W_s0080_7840*, int (*)(W_s0080_7840*, void*), void*);
struct WinButtonCtor { void* ctor(); };
struct ButtonDrawableCtor { void* ctor(); };
// ---- items of slice s00807840 end

// ---- items of slice s008087f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  GetMainWindowArea(float* out);  // 0x00805ea0
extern float gRolloverMinScale;                    // 0x01485378 (reads 0.0)
struct IWin;
struct Mat;
extern "C" void  WindowAreaCB(IWin* w, void* user);
extern "C" void  AnchorWindowToScreen(float* rect, IWin* child, int flags, IWin* parent);  // 0x008070d0
extern "C" void  AnchorWindowToWindow(IWin* parent, IWin* child, int flags, int zero);  // 0x00807340
extern "C" IWin* FindWindowByID(void* layout, uint32_t id, int recurse);
struct Mat {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    void UseMaterial(int x);                       // FUN_0082f9a0 (thiscall)
};
struct MatContainer {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual Mat* FindMaterial(uint32_t id);        // vtable +0x0c
};
struct Pt { float x, y; };
struct IWinOwner;
struct cSPUILayout_s0080_87f0 { IWin* FindWindowByID(uint32_t id, int recurse); };   // 0x008105b0 (thiscall)
struct IUILayoutHolder {
    virtual void AddRef(); virtual void Release();
    int pad;
    cSPUILayout_s0080_87f0 layout;                            // +8
};
struct IWinOwner {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual IUILayoutHolder* GetLayoutHolder(uint32_t id);   // +0x0c
};
template <class T> struct Ref {
    T* p;
    Ref() : p(0) {}
    Ref(T* q) : p(q) { if (p) p->AddRef(); }
    ~Ref() { if (p) p->Release(); }
    Ref& operator=(T* q) {
        if (q != p) { T* old = p; if (q) q->AddRef(); p = q; if (old) old->Release(); }
        return *this;
    }
    T* operator->() const { return p; }
    operator T*() const { return p; }
};
struct IWin {
    virtual void AddRef(); virtual void Release(); virtual void s02(); virtual void s03();
    virtual void* GetArea();                       // +0x10 (index 4)
    virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual float* GetRect();                      // +0x38 (index 14)
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual MatContainer* GetSPMaterial();         // +0x4c (index 19)
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25();
    virtual void Fn68(float a, float b);           // +0x68 (index 26)
    virtual void s27();
    virtual void Fn70(float a, float b);           // +0x70 (index 28)
    virtual void s29(); virtual void s30();
    virtual void SetVisible(bool a, bool b);       // +0x7c (index 31)
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41();
    virtual void FnAc(bool a);                      // +0xac (index 43)
    virtual void s44(); virtual void s45();
    virtual IWinOwner* GetOwnerByID(uint32_t id);   // +0xb4 (index 45)
    virtual void FnB8(void* a, int b);              // +0xb8 (index 46)
    virtual void s47();
    virtual void FnC0(void* pt, Pt p);              // +0xc0 (index 48)
    virtual void FnC4(void* pt, float x, float y);  // +0xc4 (index 49)
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
    virtual void s58(); virtual void s59();
    virtual IWin* FnF0(int a, int b);               // +0xf0 (index 60)
    virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
    virtual IWin* Fn104(void* a);                   // +0x104 (index 65)
    virtual void Fn108(void* a);                    // +0x108 (index 66)
    virtual IWin* Fn10C(void* a);                   // +0x10c (index 67)
};
struct RolloverSlot { int idx; int flags; float fx, fy; };
static __forceinline void AnchorTo(IWin* parent, IWin* child, int f)
{
    AnchorWindowToWindow(parent, child, f, 0);
}
// ---- items of slice s008087f0 end


// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_008087f0(float* out, IWin* w, char useChildren);  // 0x008087f0 (stays in the slice: not this object's)

// ---- items of slice s00809700 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t g_894, g_895, g_896;  // 0x0164c894/5/6
extern uint32_t g_898, g_89c, g_8a0;// 0x0164c898/9c/a0
struct AppInner { char pad[0x118]; int flag; };
struct AppOuter { char pad[0x3c]; AppInner* inner; };
extern AppOuter* g_app;              // 0x015fd918
// ---- items of slice s00809700 end

// ---- items of slice s00829bc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Rect { float left, top, right, bottom; };
struct ObjT1 {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual ObjT1* m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual Rect* m14(); virtual void m15();
  virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19(); virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
  virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27(); virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31();
  virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35(); virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
  virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43(); virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
  virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51(); virtual void m52(); virtual void m53(); virtual void m54(ObjT1*); virtual void m55(ObjT1*);
  virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59(); virtual void m60(); virtual void m61(); virtual void m62(); virtual void m63();
  virtual void m64(); virtual void m65(); virtual void m66(); virtual void m67();
};
struct ObjT2 {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual ObjT1* m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual Rect* m14(); virtual void m15();
  virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19(); virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
  virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27(); virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31();
  virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35(); virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
  virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43(); virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
  virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51(); virtual void m52(); virtual void m53(); virtual void m54(ObjT1*); virtual void m55(ObjT1*);
  virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59(); virtual void m60(); virtual void m61(); virtual void m62(); virtual void m63();
  virtual void m64(); virtual void m65(); virtual void m66(); virtual void m67();
};
template<class T>
struct AutoRef {
  T* mpObject;
  AutoRef() : mpObject(0) {}
  T* operator->() const { return mpObject; }
  AutoRef(T* p) { mpObject = p; if (p) p->m0(); }
  AutoRef(const AutoRef<T>& o) { mpObject = o.mpObject; if (mpObject) mpObject->m0(); }
  ~AutoRef() { if (mpObject) mpObject->m1(); }
  AutoRef<T>& operator=(T* p) {
    T* pOld = mpObject;
    if (p != pOld) {
      if (p) p->m0();
      mpObject = p;
      if (pOld) pOld->m1();
    }
    return *this;
  }
};
struct SPUILayout : ObjT2 {
  bool Init(void* desc, int a, int b);
  ObjT1* FindWindowByID(unsigned id, int a);
  void SetParentWin(ObjT1* parent, int a, unsigned id);
  void Shutdown(int a);
};
typedef ObjT1 Win;
struct SFV {
  ObjT1* vtbl0;      // +0x00
  ObjT1* vtbl1;      // +0x04
  uint32_t m8;       // +0x08
  SPUILayout* mLayout;  // +0x0c
  AutoRef<ObjT1> m10;   // +0x10
  AutoRef<ObjT1> m14;   // +0x14
  AutoRef<ObjT1> m18;   // +0x18
  AutoRef<ObjT1> m1c;   // +0x1c
  AutoRef<ObjT1> m20;   // +0x20
  uint32_t m24;      // +0x24
  float m28;         // +0x28
  float m2c;         // +0x2c
  float m30;         // +0x30
  float m34;         // +0x34
  float m38;         // +0x38
  uint32_t m3c;      // +0x3c
  uint32_t m40;      // +0x40
  uint32_t m44;      // +0x44

  SFV();
  __declspec(noinline) bool Create(int a, unsigned b, unsigned c);
  void Destroy();
  float GetScrollOffset();
  bool CreateFromName(const unsigned short* name, unsigned a, unsigned b);
  void Shutdown();
  void Update();
  bool OnMessage(Win* pSender, void* pMsg);
};
// ---- items of slice s00829bc0 end

// @ 0x00804f80
void Help2(void* a, float f, float g, void* b)
{
    WMObj()->H40(a, f, g, b);
}









// @ 0x00804fc0
namespace SPUIHelpers {
void SetWindowAlpha(EA::UTFWin::IWindow * w, float a)
{
    if (w == 0) return;
    IWnd* p = (IWnd*)w;
    int c = (*(int(__thiscall**)(void*))VSlot(w, 0x30))(w);
    int v = (int)(a * 255.0f);
    if ((c & 0xff000000) != (v << 24)) {
        p->H5c((c & 0xffffff) | (v << 24));
        p->H90();
        (*(void(__thiscall**)(void*))VSlot(w, 0x90))(w);
    }
}
}  // namespace SPUIHelpers









// @ 0x00805040
float GetAlpha(int* p)
{
    if (p == 0) return 1.0f;
    unsigned v = (*(unsigned(__thiscall**)(void*))VSlot(p, 0x30))(p);
    return (float)(v >> 0x18) * 0.0039215689f;
}









// @ 0x00805080
namespace SPUIHelpers {
float GetElapsedSeconds()
{
    WMgr* wm = (WMgr*)SP_WindowManager();
    void* r = wm->s1();
    if (r != 0) {
        Helper* self = (Helper*)((char*)r - 4);
        return self->H70b();
    }
    return 0.0f;
}
}  // namespace SPUIHelpers









// @ 0x008050b0
int WalkAll(int* p)
{
    if (p != 0) {
        for (;;) {
            int r = (*(int(__thiscall**)(void*))VSlot(p, 0x28))(p);
            if ((r & 1) == 0) return 0;
            p = (int*)(*(void*(__thiscall**)(void*))VSlot(p, 0x10))(p);
            if (p == 0) return 1;
        }
    }
    return 0;
}









// @ 0x008050f0
int* WalkFind(int* p)
{
    if (p == 0) return 0;
    do {
        int* n = (int*)(*(void*(__thiscall**)(void*))VSlot(p, 0x10))(p);
        if (n != 0) {
            int r = (*(int(__thiscall**)(void*))VSlot(n, 0x1c))(n);
            if (r != 0) return (int*)r;
        }
        p = (int*)(*(void*(__thiscall**)(void*))VSlot(p, 0x10))(p);
    } while (p != 0);
    return 0;
}









// @ 0x00805150
bool Contains(int* a, int* b)
{
    if (a == 0) return false;
    while (b != 0) {
        if (a == b) return true;
        b = (int*)(*(void*(__thiscall**)(void*))VSlot(b, 0x10))(b);
    }
    return false;
}









// @ 0x008051b0
int* FindByKey(int* self, int key)
{
    int* n = (int*)((void*(__thiscall*)(void*, int))VFn(self, 0x10c))(self, 0);
    while (n != 0) {
        if (((int(__thiscall*)(void*, int))VFn(n, 0xc))(n, key) != 0) return n;
        n = (int*)((void*(__thiscall*)(void*, void*))VFn(self, 0x10c))(self, n);
    }
    return 0;
}









// @ 0x00805200
float AttrF14(int* p)
{
    if (p != 0) {
        int* q = FindByKey(p, 0x3ec2e62);
        if (q != 0) return *(float*)((char*)q + 0x14);
    }
    return 1.0f;
}









// @ 0x00805230
float AttrF18(int* p)
{
    if (p != 0) {
        int* q = FindByKey(p, 0x3ec2e62);
        if (q != 0) return *(float*)((char*)q + 0x18);
    }
    return 1.0f;
}









// @ 0x00805260
void* AttrP1c(int* p)
{
    if (p != 0) {
        int* q = FindByKey(p, 0x3ec2e62);
        if (q != 0) return (char*)q + 0x1c;
    }
    return (void*)0x1544384;
}









// @ 0x00805290
float AttrF0c(int* p)
{
    if (p != 0) {
        int* q = FindByKey(p, 0x3ec2e62);
        if (q != 0) return *(float*)((char*)q + 0xc);
    }
    return 0.0f;
}









// @ 0x008052c0
float AttrF10(int* p)
{
    if (p != 0) {
        int* q = FindByKey(p, 0x3ec2e62);
        if (q != 0) return *(float*)((char*)q + 0x10);
    }
    return 0.0f;
}









// @ 0x00805310
bool CreditsTabInit(int param1, int param2, void** out)
{
    char layout[0x18];
    extern void LayoutCtor(char*);
    extern bool LayoutInit(char*, int, int, int);
    extern void LayoutDtor(char*);
    extern void* LayoutFindById(char*, int, int);
    extern void LayoutShutdown(char*, int);
    LayoutCtor(layout);
    if (!LayoutInit(layout, param1, 0, 0x5b598fa)) {
        LayoutDtor(layout);
        return false;
    }
    void* w = LayoutFindById(layout, param2, 1);
    *out = w;
    bool ok;
    if (w == 0) ok = false;
    else {
        AddRefObj(w);
        void* o = (*(void*(__thiscall**)(void*))VSlot(w, 0x10))(w);
        if (o != 0) (*(void(__thiscall**)(void*, void*))VSlot(o, 0xdc))(o, w);
        ok = true;
    }
    LayoutShutdown(layout, 1);
    LayoutDtor(layout);
    return ok;
}









// @ 0x00805400
void FreeCoreBlock(void* p)
{ DeallocEAL(p); _ReadWriteBarrier(); }









// @ 0x00805490
void VThunk8::CallVt8(int a, int b, int c, int d, int e)
{
    (*(void(__thiscall**)(void*, int, int, int))VSlot(this, 8))(this, a, b, c);
}









// @ 0x008054b0
void FixedFree(int* self, void* p)
{
    int* base = (int*)((char*)p - 4);
    int idx = *base;
    if (idx < 0x9e) {
        char* block = *(char**)((char*)self + 4 + idx * 4);
        *base = *(int*)(block + 0x10);
        *(int**)(block + 0x10) = base;
        return;
    }
    (*(void(__thiscall**)(void*, int*, int))VSlot(*(void**)0x164c4b8, 0xc))(*(void**)0x164c4b8, base, 0);
}









// @ 0x008054f0
void InitAlloc()
{
    g_alloc = GetDefaultAllocator();
    *(void**)0x164c4b8 = g_alloc;
    FUN_009512b0(&g_alloc);
}








// @ 0x00805ea0
Vec4* SPUIHelpers_GetMainWindowArea(Vec4* out)
{
    WMgr_s0080_5940* wm = (WMgr_s0080_5940*)SP_WindowManager();
    char* p = (char*)wm->s1();
    p = p ? (char*)((char*)p - 4) : (char*)0;
    char* q = p + 4;
    Vec4* a = (Vec4*)((W*)q)->v34();
    out->x = a->x;
    out->y = a->y;
    out->z = a->z;
    out->w = a->w;
    return out;
}







// @ 0x00805ef0
Vec4* FUN_00805ef0(Vec4* out, W* w)
{
    Vec4* a = (Vec4*)w->v34();
    out->x = a->x; out->y = a->y; out->z = a->z; out->w = a->w;
    W* r = (W*)w->v10();
    if (r == 0) return out;
    Vec4* b = (Vec4*)r->v38();
    Vec4 tmp;
    tmp.x = b->x; tmp.y = b->y; tmp.z = b->z; tmp.w = b->w;
    W* it = (W*)w->m10c(0);
    if (it != 0) {
        do {
            W* v = (W*)it->m0c(0xcf3df10b);
            if (v != 0) {
                v->v00();
                v->m14(&tmp, out);
                v->v04();
            }
            it = (W*)w->m10c(it);
        } while (it != 0);
    }
    return out;
}







// @ 0x008060d0
void* GetImageFromTexture(int arg1, int arg2, int arg3, int arg4)
{
    W* mgr = (W*)FUN_0067dd60();
    W* i = (W*)mgr->m20(arg1, arg2, 0);
    if (i == 0) return 0;
    void* img = AllocEAL(0x14, (const char*)&DAT_013f6b3c, 0, 0, 0, 0);
    if (img == 0) return 0;
    img = ((ImgHelper*)img)->UI_Image_Image(i);
    if (img == 0) return 0;
    ((W*)img)->v00();
    int b = arg3;
    if (b < 0) b = (int)FUN_008332a0();
    int c = arg4;
    if (c < 0) c = (int)FUN_008332d0();
    void* img2 = AllocEAL(0x2c, (const char*)&DAT_013f6b3c, 0, 0, 0, 0);
    if (img2 == 0) {
        ((W*)img)->v04();
        return 0;
    }
    void* r = ((ImgHelper*)img2)->UI_Image_Image2(img, b, c, 0.0f, 0.0f, 1.0f, 1.0f);
    ((W*)img)->v04();
    return r;
}







// @ 0x008061c0
void* GetImageFromLayout(void* layout, int id)
{
    if (layout == 0) return 0;
    W* w = (W*)((LayoutHelper*)layout)->FindWindowByID(id, 1);
    if (w == 0) return 0;
    W2* d = (W2*)w->va8();
    if (d == 0) return 0;
    W2* a = (W2*)d->m0c(0xef3c47cf);
    if (a != 0) return a->v18();
    W2* b = (W2*)d->m0c(0x103c1908);
    if (b != 0) return b->m10(0);
    return 0;
}







// @ 0x00806320
void CreateImageFromResourceA(int a, int b, int c, int d, int e, int f, int g)
{
    int key[3] = {0, 0, 0};
    SPKeyFromName(&key, c, a, b);
    CreateImageFromResource2(&key, (void**)d, (char)e, f, g);
}







// @ 0x00806370
void* FUN_00806370(W* parent)
{
    void* alloc = FUN_009512c0();
    void* mem = FUN_009512d0(0x20c, 4, (const char*)"UI/Window", alloc);
    void* win = 0;
    if (mem != 0) {
        win = ((WindowHelper*)mem)->UI_Window_Window();
    }
    W* esi = win ? (W*)((char*)win + 4) : 0;
    if (esi == 0) return esi;
    esi->m54(0);
    esi->m50(0);
    Vec4 r;
    r.x = 0; r.y = 0;
    r.z = g_13ec4d0; r.w = g_13ec4d0;
    esi->m60(&r);
    esi->m5c(-1);
    esi->mAc(0xffffff);
    esi->m7c(1, 1);
    esi->m7c(0x10, 0);
    esi->m7c(2, 1);
    if (parent != 0) {
        Vec4* a = (Vec4*)parent->v34();
        r.x = 0; r.y = 0;
        r.z = a->z - a->x;
        r.w = a->w - a->y;
        esi->m60(&r);
        parent->mD8(esi);
    }
    esi->v90();
    return esi;
}







// @ 0x008064c0
void* FUN_008064c0(W* parent)
{
    void* alloc = FUN_009512c0();
    void* mem = FUN_009512d0(0x834, 4, (const char*)"UI/WinText", alloc);
    void* txt = 0;
    if (mem != 0) {
        txt = ((WindowHelper*)mem)->UI_WinText_WinText();
    }
    W* esi = txt ? (W*)((char*)txt + 0x20c) : 0;
    esi = (W*)esi->v10();
    if (esi == 0) return esi;
    esi->m54(0);
    esi->m50(0);
    Vec4 r;
    r.x = 0; r.y = 0;
    r.z = g_13ec4d0; r.w = g_13ec4d0;
    esi->m60(&r);
    esi->m5c(-1);
    esi->mAc(0xffffff);
    esi->m7c(1, 1);
    esi->m7c(0x10, 0);
    esi->m7c(2, 1);
    if (parent != 0) {
        Vec4* a = (Vec4*)parent->v34();
        r.x = 0; r.y = 0;
        r.z = a->z - a->x;
        r.w = a->w - a->y;
        esi->m60(&r);
        parent->mD8(esi);
    }
    esi->v90();
    return esi;
}







// @ 0x00806610
void FUN_00806610(DWin* win, int a, int b, Vec4* rc, W* obj)
{
    DWin* dw = (DWin*)win->v10();
    win->m1c(a);
    for (int i = 0; i < 8; i++) win->m4c(i, 0xff000000);
    dw->m54(0);
    dw->m50(b);
    dw->mAc(0);
    dw->m5c(-1);
    DWin* d = (DWin*)dw->va8();
    Vec4 area;
    d->m18(&area, 0, 0);
    dw->m64(rc->x, rc->y);
    dw->m68(area.x, area.y);
    if (obj != 0) obj->mD8(dw);
    dw->v90();
}







// @ 0x00806780
void* FUN_00806780(int a, int b, int c, int d, int e, int f)
{
    void* alloc = FUN_009512c0();
    void* mem = FUN_009512d0(0x888, 4, (const char*)"UI/WinButton", alloc);
    void* btn = 0;
    if (mem != 0) {
        btn = ((WindowHelper*)mem)->UI_WinButton_WinButton();
    }
    DWin* esi = btn ? (DWin*)((char*)btn + 0x20c) : 0;
    DWin* w = (DWin*)esi->v10();
    w->mB0((void*)a);
    FUN_00806610(esi, b, c, (Vec4*)&d, (W*)f);
    (void)e;
    return esi;
}







// @ 0x008067f0
void* FUN_008067f0(W2* w, int index)
{
    if (w == 0) return 0;
    W2* a = (W2*)w->va8();
    if (a != 0) a = (W2*)a->m0c(0x103c1908);
    else a = 0;
    W2* b = (W2*)w->va8();
    if (b != 0) b = (W2*)b->m0c(0xef3c47cf);
    else b = 0;
    if (a != 0) {
        if (index < 0 || index >= 8) index = 0;
        return a->m10(index);
    }
    if (b != 0) return b->v18();
    return 0;
}







// @ 0x00806880
void* FUN_00806880(W2* w, int index)
{
    if (w == 0) return 0;
    W2* d = (W2*)w->va8();
    if (d == 0) return 0;
    void* r = d->m0c(0x53eb526);
    if (r == 0) return 0;
    if (index < 0 || index >= 8) index = 0;
    return ((DrawHelper*)r)->FUN_00830cf0(index);
}






// @ 0x008068d0
char FUN_008068d0(W_s0080_68d0* w, int param2, int param3)
{
    W_s0080_68d0* a; W_s0080_68d0* b; void* alloc; void* mem; void* obj; W_s0080_68d0* sd; W_s0080_68d0* im; void* r;
    void* curp;
    if (w == 0) return 0;
    a = (W_s0080_68d0*)w->va8();
    if (a != 0) a = (W_s0080_68d0*)a->m0c(0x103c1908);
    else a = 0;
    b = (W_s0080_68d0*)w->va8();
    if (b != 0) b = (W_s0080_68d0*)b->m0c(0xef3c47cf);
    else b = 0;
    if (a != 0) goto do_assign;
    if (b != 0) goto lab2;
    alloc = FUN_009512c0();
    if ((unsigned)param3 < 8u) {
        mem = FUN_009512d0(0x7c, 4, "UI/StdDrawable", alloc);
        sd = 0;
        if (mem != 0) {
            obj = ((StdDrawCtor*)mem)->ctor();
            sd = obj ? (W_s0080_68d0*)((char*)obj + 0xc) : 0;
        }
        r = FUN_008055a0(sd);
        w->mB0(r);
        if (sd == 0) return 1;
        a = sd;
        goto do_assign;
    }
    mem = FUN_009512d0(0x50, 4, "UI/ImageDrawable", alloc);
    im = 0;
    if (mem != 0) {
        obj = ((ImgDrawCtor*)mem)->ctor();
        if (obj != 0) im = (W_s0080_68d0*)((char*)obj + 0xc);
    }
    if (im != 0) {
        r = im->m0c(0x6ec581fd);
        w->mB0(r);
        b = im;
    } else {
        w->mB0(0);
    }
    if (b == 0) return 1;
lab2:
    {
        curp = (void*)(*(void*(__thiscall**)(void*))VSlot(b, 0x18))(b);
        if (curp != (void*)param2) {
            (*(void(__thiscall**)(void*, int))VSlot(b, 0x14))(b, param2);
            w->v90();
        }
    }
    return 1;
do_assign:
    {
        if (param3 < 0 || param3 >= 8) param3 = 0;
        curp = (void*)(*(void*(__thiscall**)(void*, int))VSlot(a, 0x10))(a, param3);
        if (curp == (void*)w) return 1;
        (*(void(__thiscall**)(void*, int, void*))VSlot(a, 0x14))(a, param3, w);
        w->v90();
    }
    return 1;
}






// @ 0x00806a60
char FUN_00806a60(W_s0080_68d0* w, void* layout, int id, int param4)
{
    void* img = GetImageFromLayout(layout, id);
    if (img == 0) return 0;
    if (param4 == -1) param4 = 0;
    return FUN_008068d0(w, (int)img, param4);
}






// @ 0x00806aa0
char FUN_00806aa0(W_s0080_68d0* w, int idx)
{
    if (w == 0) return 0;
    W_s0080_68d0* d = (W_s0080_68d0*)w->va8();
    if (d == 0) return 0;
    StdDraw* sd = (StdDraw*)d->m0c(0x53eb526);
    if (sd == 0) return 0;
    if (idx < 0 || idx >= 8) idx = 0;
    void* cur = sd->Pick(idx);
    if (cur != (void*)w) {
        sd->SetImageIcon(idx, w);
        w->v90();
    }
    return 1;
}






// @ 0x00806b20
char FUN_00806b20(W_s0080_68d0* w, int param2, int param3)
{
    if (w == 0 || param3 == 0) return 0;
    W_s0080_68d0* d = (W_s0080_68d0*)w->va8();
    if (d == 0) return 0;
    StdDraw* sd = (StdDraw*)d->m0c(0x53eb526);
    if (sd == 0) return 0;
    int count = param3;
    int tmp = 8;
    int* arr;
    if (count > 8) arr = &tmp;
    else arr = &param2;
    param2 = *arr;
    int changed = 0;
    for (int i = 0, u = 0; i < 8; i++, u++) {
        int v = ((int*)w)[((count <= u) ? 0 : u)];
        int cur = sd->FUN_00830d10(i);
        if (cur != v) {
            changed = 1;
            sd->FUN_008311f0(i, v);
        }
    }
    if (changed) w->v90();
    return 1;
}






// @ 0x00806bf0
void SetWindowAreaToParent(W_s0080_68d0* w)
{
    if (w == 0) return;
    W_s0080_68d0* p = (W_s0080_68d0*)w->m10(0);
    if (p == 0) return;
    float* a = (float*)p->v38();
    float wd = a[2] - a[0];
    float hd = a[3] - a[1];
    float r[4];
    r[0] = 0; r[1] = 0; r[2] = wd; r[3] = hd;
    w->m6c(r);
}






// @ 0x00806c60
float* FUN_00806c60(float* out, void* wp)
{
    W_s0080_68d0* w = (W_s0080_68d0*)wp;
    out[0] = 0; out[1] = 0;
    if (w == 0) return out;
    float* a = (float*)w->v34();
    out[0] = a[0];
    float* b = (float*)w->v34();
    out[1] = b[1];
    return out;
}






// @ 0x00806ca0
void FUN_00806ca0(W_s0080_68d0* w, float x, float y)
{
    if (w == 0) return;
    float* a = (float*)w->v34();
    w->m64(x - (a[2] - a[0]) * DAT_01471064, y - (a[3] - a[1]) * DAT_01471064);
}






// @ 0x00806db0
unsigned char FUN_00806db0(W_s0080_68d0* w, void* p)
{
    w->m8c(*(int*)p);
    w->v90();
    return *(unsigned char*)((char*)p + 4);
}






// @ 0x00806de0
void SetTooltipText(W_s0080_68d0* w, void* text)
{
    if (w == 0) return;
    W_s0080_68d0* it = (W_s0080_68d0*)w->m10c(0);
    if (it == 0) return;
    for (;;) {
        Tooltip* t = (Tooltip*)(*(void*(__thiscall**)(void*, int))VSlot(it, 0xc))(it, 0x3796ce5);
        if (t != 0) { t->SetText(text, w, (void*)0); return; }
        it = (W_s0080_68d0*)w->m10c(it);
        if (it == 0) return;
    }
}






// @ 0x00806ee0
void FUN_00806ee0(W_s0080_68d0* w)
{
    if (w == 0) return;
    W_s0080_68d0* d = (W_s0080_68d0*)w->va8();
    if (d == 0) return;
    StdDraw* sd = (StdDraw*)d->m0c(0x53eb526);
    if (sd == 0) return;
    float pad[2];
    for (int i = 0; i < 8; i++) {
        sd->GetIconColor(pad, i);
        pad[0] = pad[0] + 0.0f;
        sd->SetImageIconColor(i, pad);
    }
}






// @ 0x00806f50
int __fastcall FUN_00806f50(void* s)
{
    float* f = (float*)s;
    if (f[3] == 0.0f && f[4] == 0.0f && f[5] == 1.0f && f[6] == 1.0f) {
        if (FUN_008055c0((char*)s + 0x1c, &DAT_01544384)) return 1;
    }
    return 0;
}






// @ 0x00806fc0
void FUN_00806fc0(W_s0080_68d0* w)
{
    if (w == 0) return;
    W_s0080_68d0* p = (W_s0080_68d0*)FUN_008051b0(0x3ec2e62);
    if (p == 0) return;
    float* d = (float*)p->m0c(0x3ec2e62);
    if (d != 0) {
        d[5] = 1.0f;   // +0x14
        d[6] = 1.0f;   // +0x18
        if ((char)FUN_00806f50(d)) w->m108(p);
    }
    w->v98();
    w->v90();
}






// @ 0x00807040
void FUN_00807040(W_s0080_68d0* w)
{
    if (w == 0) return;
    W_s0080_68d0* p = (W_s0080_68d0*)FUN_008051b0(0x3ec2e62);
    if (p == 0) return;
    unsigned* d = (unsigned*)p->m0c(0x3ec2e62);
    if (d != 0) {
        d[7] = *(unsigned*)&DAT_01544384;   // +0x1c
        d[8] = *(unsigned*)&DAT_01544388;   // +0x20
        d[9] = *(unsigned*)&DAT_0154438c;   // +0x24
        d[10] = *(unsigned*)&DAT_01544390;  // +0x28
        if ((char)FUN_00806f50(d)) w->m108(p);
    }
    w->v98();
    w->v90();
}






// @ 0x00807430
void FUN_00807430(W_s0080_68d0* w, float v)
{
    W_s0080_68d0* o;
    if (w == 0) o = 0;
    else o = (W_s0080_68d0*)w->m0c(0x10edf11);
    float x = v * 100.0f;
    if (x <= 0.0f) x = 0.0f;
    if (x >= 100.0f) x = 100.0f;
    (*(void(__thiscall**)(void*, float))VSlot(o, 4))(o, x);
}






// @ 0x008074a0
char DestroyRolloverFrame(W_s0080_68d0* w)
{
    if (w == 0) return 0;
    W_s0080_68d0* a = (W_s0080_68d0*)w->mB4(0x4a61af0);
    if (a != 0) a = (W_s0080_68d0*)a->m0c(0x4a61af0);
    else a = 0;
    if (a != 0) a->v00();
    w->mB8(0x4a61af0, 0);
    if (a != 0) ((Layout*)((char*)a + 8))->Shutdown(1);
    W_s0080_68d0* b = (W_s0080_68d0*)w->mB4(0x4a61af1);
    if (b != 0) b = (W_s0080_68d0*)b->m0c(0x4a61af0);
    else b = 0;
    W_s0080_68d0* keep = a;
    if (b != a) {
        if (b != 0) b->v00();
        keep = b;
        if (a != 0) a->v04();
    }
    w->mB8(0x4a61af1, 0);
    if (keep != 0) {
        ((Layout*)((char*)keep + 8))->Shutdown(1);
        keep->v04();
    }
    return 1;
}






// @ 0x00807590
void RemoveWindowCallback(W_s0080_68d0* w, int cb)
{
    if (w == 0 || cb == 0) return;
    W_s0080_68d0* it = (W_s0080_68d0*)w->m10c(0);
    if (it == 0) return;
    for (;;) {
        void* h = (void*)(*(void*(__thiscall**)(void*, int))VSlot(it, 0xc))(it, 0x4a61af2);
        if (h != 0 && *(int*)((char*)h + 0xc) == cb) break;
        it = (W_s0080_68d0*)w->m10c(it);
        if (it == 0) return;
    }
    w->m108(it);
}






// @ 0x00807600
void* FUN_00807600(void* p1, void* p2, void* p3)
{
    void* piVar5 = 0;
    void* mem = operator_new(0x48, "UI/ScrollFrameVertical", 0, 0, 0, 0);
    void* sf = 0;
    if (mem != 0) sf = ((ScrollCtor*)mem)->ctor();
    if (sf != 0) (*(void(__thiscall**)(void*))VSlot(sf, 0))(sf);
    char ok = FUN_0082aa20(p1, p3, 0);
    if (ok == 0) {
        if (sf != 0) {
            (*(void(__thiscall**)(void*))VSlot(sf, 4))(sf);
            return 0;
        }
    } else {
        piVar5 = *(void**)((char*)sf + 0x10);
        ((W_s0080_68d0*)piVar5)->mB8(0x4a61af1, sf);
        void* q = *(void**)((char*)sf + 0x18);
        *(void**)p2 = q;
        (*(void(__thiscall**)(void*))VSlot(q, 0))(q);
        (*(void(__thiscall**)(void*))VSlot(sf, 4))(sf);
    }
    return piVar5;
}






// @ 0x00807690
char FUN_00807690(W_s0080_68d0* w)
{
    W_s0080_68d0* a = (W_s0080_68d0*)w->mB4(0x4a61af1);
    if (a == 0) return 0;
    W_s0080_68d0* b = (W_s0080_68d0*)a->m0c(0x4a61af2);
    if (b == 0) return 0;
    b->v00();
    FUN_0082a500();
    b->v04();
    return 1;
}






// @ 0x008076f0
char FUN_008076f0(W_s0080_68d0* w)
{
    if (w == 0) return 0;
    W_s0080_68d0* a = (W_s0080_68d0*)w->mB4(0x4a61af0);
    if (a == 0) return 0;
    W_s0080_68d0* b = (W_s0080_68d0*)a->m0c(0x4a61af2);
    if (b == 0) return 0;
    b->v00();
    w->mB8(0x4a61af0, 0);
    FUN_0082a450();
    b->v04();
    return 1;
}






// @ 0x00807760
void* __fastcall FUN_00807760(void* p)
{
    *(void**)p = &PTR_FUN_01417958;
    int local8 = 5;
    int iVar4 = 0x10;
    void* cur = p;
    do {
        cur = (char*)cur + 4;
        int local4 = (iVar4 + 0x9c3) / iVar4;
        int* pi = &local8;
        if (local4 > 4) pi = &local4;
        void* mem = operator_new(0x20, "UI/FixedAllocationBin", 0, 0, 0, 0);
        void* obj = 0;
        if (mem != 0) {
            obj = ((FixedAllocCtor*)mem)->ctor(iVar4, 0, *pi, 0, -1, (void*)FUN_008053e0, (void*)FUN_00805400, 0);
        }
        *(void**)cur = obj;
        iVar4 += 0x10;
    } while (iVar4 < 0x9f0);
    return p;
}






// @ 0x008077f0
void __fastcall DoErase(void* p)
{
    *(void**)p = &PTR_FUN_01417958;
    void** cur = (void**)((char*)p + 4);
    int n = 0x9e;
    do {
        void* v = *cur;
        if (v != 0) {
            ((ObjDtor*)v)->dtor();
            operator_delete(v);
        }
        *cur = 0;
        cur++;
        n--;
    } while (n != 0);
    *(void**)p = &PTR_FUN_01403934;
}





// @ 0x00807840
void FUN_00807840(int a, int b, int c, int d, int e, int f, int g)
{
    int key[3];
    key[0] = c; key[1] = a; key[2] = b;
    CreateImageFromResource(&key, (void**)d, (char)e, f, g);
}





// @ 0x00807a50
int* FUN_00807a50(void* p1, int type, void* p3)
{
    float local[3];
    local[0] = ((float*)p1)[0];
    local[2] = ((float*)p1)[2];
    local[1] = 0.0f;
    int img = 0;
    CreateImageFromResource(local, (void**)&img, 0, 0xffffffff, 0xffffffff);
    if (img == 0) return 0;
    void* alloc = FUN_009512c0();
    void* d = 0;
    if (type == 3) {
        d = FUN_009512d0(0x18, 4, "UI/ButtonDrawableRadio", alloc);
        if (d != 0) {
            ((ButtonDrawableCtor*)d)->ctor();
            *(void**)d = &SYM_14178b0;
            *(void**)((char*)d + 4) = &SYM_1417874;
            *(void**)((char*)d + 0xc) = &SYM_141785c;
        }
    } else {
        d = FUN_009512d0(0x18, 4, "UI/ButtonDrawableStandard", alloc);
        if (d != 0) {
            ((ButtonDrawableCtor*)d)->ctor();
            *(void**)d = &SYM_141788c;
            *(void**)((char*)d + 4) = &SYM_1417874;
            *(void**)((char*)d + 0xc) = &SYM_141785c;
        }
    }
    int* piVar6 = 0;
    if (d != 0) {
        (*(void(__thiscall**)(void*, void*))VSlot((char*)d + 0xc, 0))((char*)d + 0xc, 0);
        (*(void(__thiscall**)(void*, int))VSlot(d, 0x14))(d, img);
        (*(void(__thiscall**)(void*, void*, int))VSlot(d, 0x14))(d, (void*)img, 0);
        void* wa = FUN_009512c0();
        void* wm = FUN_009512d0(0x888, 4, "UI/WinButton", wa);
        W_s0080_7840* btn = 0;
        if (wm != 0) {
            void* o = ((WinButtonCtor*)wm)->ctor();
            btn = o ? (W_s0080_7840*)((char*)o + 0x20c) : 0;
        }
        (*(void(__thiscall**)(void*, void*))VSlot(btn, 0x60))(btn, d);
        piVar6 = (int*)btn;
        (*(void(__thiscall**)(void*, int))VSlot(d, 4))(d, 0);
    }
    (void)p3;
    return piVar6;
}





// @ 0x00807dc0
void* SetWindowSPShader(W_s0080_7840* w, unsigned char flag, void* shader)
{
    void* local = 0;
    unsigned char lflag = flag;
    (void)lflag;
    if (shader != 0) {
        (*(void(__thiscall**)(void*))VSlot(shader, 0))(shader);
        local = shader;
    } else {
        void* p = SPUIShader_AcquireShaderProxy();
        void* old = local;
        if (p != old) {
            if (p != 0) (*(void(__thiscall**)(void*))VSlot(p, 0))(p);
            local = p;
            if (old != 0) (*(void(__thiscall**)(void*, int))VSlot(old, 4))(old, 0);
        }
    }
    VisitWindowTreeDepthFirst(w, (int (*)(W_s0080_7840*, void*))FUN_00806db0, &local);
    void* r = local;
    if (local != 0) (*(void(__thiscall**)(void*, int))VSlot(local, 4))(local, 0);
    return r;
}





// @ 0x00807e50
void* __fastcall WindowTransform_ctor(Xform* t)
{
    t->vt1 = &SYM_13fa72c;
    t->fC = 0.0f;
    t->f10 = 0.0f;
    float one = DAT_01485720;
    t->f8 = 0;
    t->vt0 = &SYM_14179b8;
    t->vt1 = &SYM_141799c;
    t->f14 = one;
    t->f18 = one;
    t->f1c = DAT_01544384_s0080_7840;
    t->f20 = DAT_01544388_s0080_7840;
    t->f24 = DAT_0154438c_s0080_7840;
    t->f28 = DAT_01544390_s0080_7840;
    return t;
}





// @ 0x00807ed0
char __stdcall FUN_00807ed0(W_s0080_7840* w)
{
    w->v98();
    w->v90();
    return 0;
}





// @ 0x00807f50
void __fastcall FUN_00807f50(int p)
{
    float* f = (float*)p;
    int count = 0;
    unsigned mode = 0;
    if (ABS(f[7]) > 1.1920929e-07f) { count = 1; }
    if (ABS(f[8]) > 1.1920929e-07f) { count++; mode = 1; }
    if (ABS(f[9]) > 1.1920929e-07f) { count++; mode = 2; }
    if (count > 1) mode = 3;
    if (count != 0) {
        switch (mode) {
        case 0: FUN_0095eb00(*(int*)(p + 0x28)); return;
        case 1: FUN_0095ec30(*(int*)(p + 0x28)); return;
        case 2: FUN_0095ed60(*(int*)(p + 0x28)); return;
        case 3: {
            float v[3];
            v[0] = f[7]; v[1] = f[8]; v[2] = f[9];
            FUN_0095f5c0(v, f[10] * 0.017453292f);
        }
        }
    }
}





// @ 0x00808050
void XAlign::Update(void* a, void* b)
{
    int p = (int)this;
    float* f = (float*)p;
    if (f[5] != 1.0f || f[6] != 1.0f) {
        float v[3];
        v[0] = f[5]; v[1] = f[6]; v[2] = 1.0f;
        FUN_0095ea30(v);
    }
    if (f[7] != DAT_01544384_s0080_7840 || f[8] != DAT_01544388_s0080_7840 || f[9] != DAT_0154438c_s0080_7840 || f[10] != DAT_01544390_s0080_7840) {
        FUN_00807f50((int)a);
    }
    if (f[3] != 0.0f || f[4] != 0.0f) {
        float v[3];
        v[0] = f[3]; v[1] = f[4]; v[2] = 1.0f;
        FUN_0095e890(v);
    }
    (void)b;
}





// @ 0x00808190
void FUN_00808190(W_s0080_7840* w, float a, float b)
{
    if (w == 0) return;
    Xform* t = (Xform*)FUN_008051b0(0x3ec2e62);
    if (t == 0) {
        void* alloc = FUN_009512c0();
        void* mem = FUN_009512d0(0x2c, 4, "UI/cWindowTransform", alloc);
        t = mem ? (Xform*)WindowTransform_ctor((Xform*)mem) : 0;
        w->m104(t);
    }
    t->f14 = a;
    t->f18 = b;
    w->v98();
}





// @ 0x00808210
void SetWindowScale(W_s0080_7840* w, float s)
{
    FUN_00808190(w, s, s);
}





// @ 0x00808230
void FUN_00808230(W_s0080_7840* w, float* v)
{
    if (w == 0) return;
    Xform* t = (Xform*)FUN_008051b0(0x3ec2e62);
    if (t == 0) {
        void* alloc = FUN_009512c0();
        void* mem = FUN_009512d0(0x2c, 4, "UI/cWindowTransform", alloc);
        t = mem ? (Xform*)WindowTransform_ctor((Xform*)mem) : 0;
        w->m104(t);
    }
    if (t->f1c != v[0] || t->f20 != v[1] || t->f24 != v[2] || t->f28 != v[3]) {
        t->f1c = v[0]; t->f20 = v[1]; t->f24 = v[2]; t->f28 = v[3];
        w->v98();
    }
}





// @ 0x008082f0
void FUN_008082f0(W_s0080_7840* w, float a, float b)
{
    if (w == 0) return;
    Xform* t = (Xform*)FUN_008051b0(0x3ec2e62);
    if (t == 0) {
        void* alloc = FUN_009512c0();
        void* mem = FUN_009512d0(0x2c, 4, "UI/cWindowTransform", alloc);
        t = mem ? (Xform*)WindowTransform_ctor((Xform*)mem) : 0;
        w->m104(t);
    }
    t->fC = a;
    t->f10 = b;
    w->v98();
}





// @ 0x00808590
char CbProc::Invoke(void* a, void* b)
{
    if (mpFn != 0) return (char)mpFn(a, b, mpCtx);
    return 0;
}





// @ 0x008085d0
void FUN_008085d0(W_s0080_7840* w, void* fn, void* ctx, void* a, void* b)
{
    if (w == 0 || fn == 0) return;
    void* alloc = FUN_009512c0();
    CbWinProc* p = (CbWinProc*)FUN_009512d0(0x1c, 4, "UI/cCallbackWinProc ", alloc);
    if (p == 0) p = 0;
    else {
        p->vt1 = &SYM_13fa72c;
        p->f8 = 0;
        p->vt0 = &SYM_1417a68;
        p->vt1 = &SYM_1417a4c;
        p->fC = 0;
        p->f10 = 0;
        p->f14 = 0;
        p->f18 = -1;
    }
    p->f14 = a;
    p->f10 = b;
    p->f18 = (int)ctx;
    p->fC = fn;
    w->m104(p);
}





// @ 0x00808660
int OpenRecordAsStream(void* key, int* rec, void* stream)
{
    int result = -1;
    if ((char)key != 0) {
        void* prop = SP_PropertyManager();
        void* list = 0;
        if (list != 0) (*(void(__thiscall**)(void*, int))VSlot(list, 4))(list, 0);
        char c = (*(char(__thiscall**)(void*, int, void**))VSlot(prop, 0x30))(prop, 0x5c770db7, &list);
        if (c != 0) {
            int count = 0, arr = 0;
            char ok = SP_GetPropertyAsUint32Array(list, rec[1], &count, &arr);
            if (ok != 0 && count > 0) {
                int i = 0;
                do {
                    if (result != -1) break;
                    int u = *(int*)(arr + i * 4);
                    int k[2];
                    k[0] = rec[0];
                    k[1] = rec[1];
                    (void)u;
                    result = SP_OpenRecordAsStream(k, stream);
                    i++;
                } while (i < count);
            }
        }
        if (list != 0) (*(void(__thiscall**)(void*, int))VSlot(list, 4))(list, 0);
        if (result != -1) return result;
    }
    return SP_OpenRecordAsStream(rec, stream);
}





// @ 0x00808780
void FUN_00808780()
{
    DoErase(&DAT_0164c598);
    DAT_0164c4b8 = 0;
}




// @ 0x008087f0
void FUN_008087f0(float* out, IWin* w, char useChildren)
{
    if (useChildren != 0) {
        float r[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        VisitWindowTreeDepthFirst((W_s0080_7840*)w, (int (*)(W_s0080_7840*, void*))&WindowAreaCB, r);
        out[0] = r[0];
        out[1] = r[1];
        out[2] = r[2];
        out[3] = r[3];
    } else {
        float* p = w->GetRect();
        float a[4];
        a[0] = p[0]; a[1] = p[1]; a[2] = p[2]; a[3] = p[3];
        Pt q0;
        w->FnC0(&q0, Pt());
        Pt in;
        in.x = a[2] - a[0];
        in.y = a[3] - a[1];
        Pt q1;
        w->FnC0(&q1, in);
        out[0] = q0.x;
        out[1] = q0.y;
        out[2] = q1.x;
        out[3] = q1.y;
    }
}



// @ 0x00808d40
bool SPUIHelpers_UpdateRolloverFrame(IWin* w, float p2, float p3, float p4, float p5, bool showAll, float scale)
{
    if (w == 0)
        return false;
    IWinOwner* owner = w->GetOwnerByID(0x4a61af0);
    IUILayoutHolder* h;
    if (owner == 0 || (h = owner->GetLayoutHolder(0x4a61af0)) == 0)
        return false;
    Ref<IUILayoutHolder> holder(h);
    cSPUILayout_s0080_87f0* lay = &h->layout;

    float rect[4];
    rect[0] = p2 - 0.5f;
    rect[2] = p2 + 0.5f;
    rect[1] = p3 - 0.5f;
    rect[3] = p3 + 0.5f;
    Ref<IWin> win1(lay->FindWindowByID(0x4aa0748, 0));
    win1->Fn68(1.0f, 1.0f);
    AnchorWindowToScreen(rect, win1, 0x300, 0);
    Ref<IWin> win2(lay->FindWindowByID(0x4a61af0, 1));
    Ref<IWin> win3(lay->FindWindowByID(0x4a612b0, 1));

    float A[4];
    float* r2 = win2->GetRect();
    A[0] = r2[0]; A[1] = r2[1]; A[2] = r2[2]; A[3] = r2[3];
    float* r3 = win3->GetRect();
    float b0 = r3[0], b1 = r3[1], b2 = r3[2], b3 = r3[3];
    float dw = 0.0f, dh = 0.0f;
    if (p4 > 0.0f) dw = p4 - (b2 - b0);
    if (p5 > 0.0f) dh = p5 - (b3 - b1);
    win2->Fn68((A[2] - A[0]) + dw, (A[3] - A[1]) + dh);

    float M[4];
    GetMainWindowArea(M);
    win2->FnF0(1, 1)->SetVisible(true, false);
    win2->FnF0(2, 1)->SetVisible(true, false);
    win2->FnF0(3, 1)->SetVisible(true, false);
    win2->FnF0(4, 1)->SetVisible(true, false);
    win2->FnF0(5, 1)->SetVisible(true, false);
    win2->FnF0(6, 1)->SetVisible(true, false);
    win2->FnF0(7, 1)->SetVisible(true, false);
    win2->FnF0(8, 1)->SetVisible(true, false);

    RolloverSlot tbl[8] = {
        { 7, 0x102, -1.0f, 0.0f },
        { 8, 0x22, -0.707107f, 0.707107f },
        { 6, 0x42, -0.707107f, -0.707107f },
        { 1, 0x220, 0.0f, 1.0f },
        { 5, 0x240, 0.0f, -1.0f },
        { 3, 0x104, 1.0f, 0.0f },
        { 2, 0x24, 0.707107f, 0.707107f },
        { 4, 0x44, 0.707107f, -0.707107f },
    };
    Ref<IWin> cur;
    for (int i = 0; i < 8; ++i) {
        cur = win2->FnF0(tbl[i].idx, 1);
        switch (tbl[i].idx) {
        case 3: case 7:
            AnchorTo(win2, cur, 0x900);
            break;
        case 1: case 5:
            AnchorTo(win2, cur, 0x600);
            break;
        default:
            break;
        }
        if (scale > gRolloverMinScale) {
            float x = p4 - scale * tbl[i].fy;
            float y = tbl[i].fx * scale + p5;
            rect[0] = x - 0.5f;
            rect[1] = y - 0.5f;
            rect[2] = x + 0.5f;
            rect[3] = y + 0.5f;
        }
        AnchorWindowToScreen(rect, cur, tbl[i].flags, win2);
        FUN_008087f0(A, win2, 0);
        float r0 = A[0] > M[0] ? M[0] : A[0];
        float r1 = A[1] > M[1] ? M[1] : A[1];
        float r2v = M[2] > A[2] ? M[2] : A[2];
        float r3v = M[3] > A[3] ? M[3] : A[3];
        if (r0 == M[0] && r1 == M[1] && r2v == M[2] && r3v == M[3])
            break;
    }
    if (showAll)
        cur->SetVisible(true, true);
    return true;
}


// @ 0x008098b0
void set894(uint8_t v)
{ if (g_app->inner->flag != 0) g_894 = v; }


// @ 0x008098d0
void set898(uint32_t v)
{ if (g_app->inner->flag != 0) g_898 = v; }


// @ 0x008098f0
void set895(uint8_t v)
{ if (g_app->inner->flag != 0) g_895 = v; }


// @ 0x00809910
void set89c(uint32_t v)
{ if (g_app->inner->flag != 0) g_89c = v; }


// @ 0x00809930
void set896(uint8_t v)
{ if (g_app->inner->flag != 0) g_896 = v; }


// @ 0x00809950
void set8a0(uint32_t v)
{ if (g_app->inner->flag != 0) g_8a0 = v; }

// @ 0x0082a450
void SFV::Shutdown()
{
  if (m10.mpObject) {
    ObjT1* pObj = m10.mpObject->m4();
    if (pObj) pObj->m55(m10.mpObject);
  }
  m10 = (ObjT1*)0;
  m14 = (ObjT1*)0;
  m18 = (ObjT1*)0;
  m1c = (ObjT1*)0;
  m20 = (ObjT1*)0;
  mLayout->Shutdown(1);
}

// @ 0x0082a4e0
float SFV::GetScrollOffset()
{
  Rect* r = m1c->m14();
  return (r->right - r->left) + m38;
}
