// src/game/Spui/_at_00800000.cpp -- migrated from slice(s) s0080c5d0, s0080b6b0, s0080a700, s00809700, s008019f0, s007ffc70 by tools/migrate/rewrite.py
// Object file: Spui/_at_00800000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float g_1471064;
extern char dv_a[], dv_b[];
#include <new>
#include <intrin.h>
#include "EA/IO/FileStream.h"
#include "cSPUIMessageBox.h"

// ---- items of slice s007ffc70 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __stdcall f_9512c0();
void* __cdecl f_9512d0(unsigned size, int align, const char* name, void* alloc);
void  __cdecl f_951330(void* p);              // MultiHeapObject::operator delete
void  __fastcall f_800060_base(void* p);
struct IFactoryObj {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void* v3(uint32_t id);
};
struct RCBase { virtual void rc0(); virtual void Release(); };
class cSPUIBehaviorWinEventBase { public: cSPUIBehaviorWinEventBase(int, int, int); };
class cSPUIBehaviorWinBoolStateEvent { public: cSPUIBehaviorWinBoolStateEvent(int, int, int, int); };
class cSPUIBehaviorTimeFunctionSmoothRamp { public: cSPUIBehaviorTimeFunctionSmoothRamp(float, float); };
class cSPUIBehaviorTimeFunctionDampedPeriodic { public: cSPUIBehaviorTimeFunctionDampedPeriodic(int); };
extern float g_1471064;
extern char dv_a[], dv_b[];
struct C_800060 { void* ScalarDtor(uint8_t flags); };
// ---- items of slice s007ffc70 end

// ---- items of slice s008019f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RCObj { virtual void r0(); virtual void Release(); };
struct CursorLayout {
  void Shutdown(bool recursive);
  void* FindWindowByID(uint32_t id, int recursive);
};
struct C_802890 { void* f(void* want); };
// ---- items of slice s008019f0 end

// ---- items of slice s00809700 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void efree(void* p); // 0x00a222c0
extern int g_15446cc, g_15446d0, g_15446d4;
extern char g_obj_15446c8;
extern "C" void* dbgnew(unsigned size, const void* data, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void*  GetUTFManager();                         // 0x00957f30
extern "C" void*  GetUIAllocator();                        // 0x009512c0
extern "C" void*  op_new(unsigned size, int align, const char* name, void* alloc); // 0x009512d0
extern float       g_half_1471064;   // 0x01471064
extern float       g_zero_13eb1bc;   // 0x013eb1bc
struct WM {
    virtual void w0();                              // +0x00
    virtual void* w1();                             // +0x04
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
    virtual void w18();
    virtual void w19(void* a, void* b);             // +0x4c
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
virtual void w30();
virtual void w31();
    virtual void w32();
    virtual int Fn84();                             // +0x84 (index 33)
};
struct ComObj {
    virtual void q0();
    virtual void Release();       // +4
};
struct Holder {
    void* a;                      // +0
    void* b;                      // +4
    ComObj* m8;                   // +8
    ComObj* mC;                   // +0xc
    Holder* DeleteThis(unsigned char flags);
};
struct G {
    char pad[8];
    void FUN_0080a4f0(int a, int b);
};
struct IWin;
#define VSLOT(o, off) (*(void***)(o))[(off) / 4]
static inline void  vcall0(void* o, int off) { ((void (__thiscall*)(void*))VSLOT(o, off))(o); }
static inline void* vp0(void* o, int off) { return ((void* (__thiscall*)(void*))VSLOT(o, off))(o); }
static inline void  vcall1(void* o, int off, void* a) { ((void (__thiscall*)(void*, void*))VSLOT(o, off))(o, a); }
static inline void  vcall4(void* o, int off, void* a, void* b, void* c, void* d) { ((void (__thiscall*)(void*, void*, void*, void*, void*))VSLOT(o, off))(o, a, b, c, d); }
struct AutoRefIWin {
    IWin* p;
    AutoRefIWin& operator=(IWin* q);   // 0x00b5f950
};
struct MsgBox {
    MsgBox* ctor(void* where);                                  // 0x00816cb0
    bool Init(const void* key, bool b);                         // 0x00817040
    void Show(const char* a, const char* b, float f0, float f1);// 0x00816a20
};
struct IObj0 {
    virtual void f0();                      // +0
};
struct IObj4 {
    virtual void f0();                      // +0
    virtual void f4();                      // +4
};
struct IWinObj {
    virtual void Fn0(IWin* w);              // +0
    virtual void Fn4(IWin* w, void* arg);   // +4
};
struct HelperObj {
    void** vt;          // +0
    IWinObj* m4;        // +4
    AutoRefIWin m8;     // +8
    AutoRefIWin mC;     // +0xc
    void Fn(IWin* w, void* arg);
};
struct ScaleArgs {
    int kind;
    float x;
    float y;
    int a;
    int b;
};
__declspec(noinline) void __cdecl FUN_00809ff0(void* self);
struct ModalBind {
    void** vt;          // +0
    IWinObj* m4;        // +4
    AutoRefIWin m8;     // +8
    AutoRefIWin mC;     // +0xc
    void Fn(IWin* w);
};
// ---- items of slice s00809700 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __fastcall FUN_00809e40(HelperObj* self);  // 0x00809e40 (stays in the slice: not this object's)

// ---- items of slice s0080a700 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_const_13ef548;
struct Ref {
    virtual void AddRef();     // +0
    virtual void Release();    // +4
};
struct Sub {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual Sub* Fn10();                        // +0x10 (index 4)
virtual void v5();
virtual void v6();
    virtual void Fn1c(int x);                   // +0x1c (index 7)
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual float* Fn38();                      // +0x38 (index 14)
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
    virtual void Fn74(float a, float b);        // +0x74 (index 29)
};
struct Win2 {
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
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
    virtual void Fn88(int x);                   // +0x88 (index 34)
};
struct AutoRef2 {
    Ref* p;
    AutoRef2& operator=(Ref* x) {
        Ref* old = p;
        if (x != old) {
            if (x) x->AddRef();
            p = x;
            if (old) old->Release();
        }
        return *this;
    }
};
struct W40 { int x[10]; };
struct RecC {
    void* vtbl;          // +0
    W40 w;               // +4..+0x2b
    AutoRef2 r;          // +0x2c
    int tail;            // +0x30
    RecC& operator=(const RecC& src);
};
RecC& RecC::operator=(const RecC& src)
{
    w = src.w;
    r = src.r.p;
    tail = src.tail;
    return *this;
}
struct AtlasOwner {
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
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
    virtual const unsigned short* Title();     // +0x3c (index 15)
};
struct AtlasEntry {
    void* mpVtable;                 // +0x00
    char pad04[0x28];
    AtlasOwner* mpOwner;            // +0x2c
    unsigned int mFlags;            // +0x30
};
struct AtlasState {
    char pad00[0x1c4];
    AtlasEntry* mpBegin;            // +0x1c4
    AtlasEntry* mpEnd;              // +0x1c8
    char pad1cc[0x41c - 0x1cc];
    unsigned char mReady;           // +0x41c

    bool Validate();
};
struct ActorFind {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual void* Find(int id);                 // +0x0c (index 3)
};
unsigned int FUN_0080ab00_dispatch(void* sub, float a, float b, float c);   // 0x0080ab00
unsigned int FUN_0080acb0_dispatch(void* sub, float a, float b, float c);   // 0x0080acb0
// ---- items of slice s0080a700 end

// ---- items of slice s0080b6b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char ObjB_vtable[];
struct Layout {
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
    void* FindWindowByID(int id, int recurse);       // 0x008105b0
};
struct Win {
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
virtual void w10();
virtual void w14();
virtual void w18();
virtual void w1c();
virtual void w20();
virtual void w24();
virtual void w28();
virtual void w2c();
virtual void w30();
virtual void w34();
    virtual float* rect();                       // +0x38
    virtual const unsigned short* label();       // +0x3c
virtual void w40();
virtual void w44();
virtual void w48();
virtual void w4c();
virtual void w50();
virtual void w54();
virtual void w58();
virtual void w5c();
virtual void w60();
virtual void w64();
virtual void w68();
    virtual void w6c(float* box);                // +0x6c
    virtual void w70(float x, float y);          // +0x70
    virtual void w74(float x, float y);          // +0x74
    virtual void w78();                          // +0x78
    virtual void w7c(int a, int b);              // +0x7c
};
struct VecRec {
    virtual void Destroy(int flag);      // +0x00 (vtable 0x1417cac)
    int f04;                             // +0x04
    int f08;                             // +0x08
    int f0c;                             // +0x0c
    int f10;                             // +0x10
    int f14;                             // +0x14
    float f18;                           // +0x18
    float f1c;                           // +0x1c
    int f20;                             // +0x20
    int f24;                             // +0x24
    int f28;                             // +0x28
    Win* ref;                            // +0x2c
    unsigned int flags;                  // +0x30
    void __thiscall CopyFrom(const VecRec* src);    // 0x80af90
    void __thiscall CopyAssign(const VecRec* src);  // 0x80b240
};
VecRec* __cdecl UninitCopy(const VecRec* first, const VecRec* last, VecRec* dst);   // 0x80b290
VecRec* __cdecl DestroyRange(const VecRec* first, const VecRec* last, VecRec* dst); // 0x80aea0
VecRec* __cdecl CopyBackward(const VecRec* first, const VecRec* last, VecRec* dstEnd); // 0x80b2d0
VecRec* __cdecl CopyForward(const VecRec* first, const VecRec* last, VecRec* dst);  // 0x80b340
void* __cdecl UninitCopyOut(void* out, const VecRec* first, const VecRec* last,
                            VecRec* dst);                                           // 0x80b970
void __cdecl FUN_0080b170(Win* w, char animate, float a, float b, float c);         // 0x80b170
void* __cdecl GameAlloc(unsigned int size, const char* name, int a, int b,
                        const char* file, int line);                                // 0xf473a0
struct RecVec {
    VecRec* begin;      // +0x00
    VecRec* end;        // +0x04
    VecRec* cap;        // +0x08
    void*   pad0c;      // +0x0c
    VecRec* inlineBuf;  // +0x10
    void*   pad14;      // +0x14
    VecRec  buf[11];    // +0x18 .. 0x254
    int  Count() const { return (int)(end - begin); }
    void Insert(VecRec* pos, const VecRec* value);                         // 0x80baa0
    void Assign(const VecRec* first, VecRec* last, const void* owner);     // 0x80bbe0
    VecRec* AllocCopyRange(int count, const VecRec* first, const VecRec* last); // 0x80ba40
    void __thiscall DestroyRange2(VecRec* first, VecRec* last);            // 0x80ae70
};
struct PtrVec {
    void** begin;       // +0x00
    void** end;         // +0x04
    void** cap;         // +0x08
    void*  pad0c;       // +0x0c
    void** inlineBuf;   // +0x10
    void*  pad14;       // +0x14
    void*  buf[11];     // +0x18 .. 0x44
    void Init() { inlineBuf = (void**)buf; cap = (void**)buf + 11; end = (void**)buf; begin = (void**)buf; }
    void __thiscall InsertAt(void** pos, void* const* value);              // 0x82f170
    int Count() const { return (int)(end - begin); }
};
struct Big3 {
    void*  vtbl;          // +0x000
    char   pad04[0x1c0];  // +0x004
    RecVec records;       // +0x1c4 .. 0x418
    Layout* layout;       // +0x418
    char   flag;          // +0x41c
    char   pad41d[3];     // +0x41d
    int    state;         // +0x420
    float  f424;          // +0x424
    float  f428;          // +0x428
    void* method(int a);
    void FUN_0080b4d0(int a);
    void FUN_0080b6b0();
    void FUN_0080b000();
    void FUN_0080bd50(float offset);
    bool FUN_0080bfb0(float width);
    Win* FUN_0080c520(float a, float b, int c);
    void* DeletingDtor(char flags);
};
struct E34 { virtual void Fn(int v); char pad[0x30]; };
struct E42C { virtual void Fn(int v); char pad[0x428]; };
struct ObjB {
    void* vtbl;
    int f1, f2, f3, f4, f5, f6, f7;
};
struct RecC_s0080_b6b0 {
    virtual void Fn(int v);
    int w[10];
    void* r;
    int tail;
};
RecC_s0080_b6b0* copyFwd(RecC_s0080_b6b0* begin, RecC_s0080_b6b0* end, RecC_s0080_b6b0* dst);
struct Vec {
    RecC_s0080_b6b0* begin;     // +0
    RecC_s0080_b6b0* end;       // +4
    RecC_s0080_b6b0* cap;       // +8
    int pad;         // +0xc
    RecC_s0080_b6b0* inlineBuf; // +0x10
    RecC_s0080_b6b0* erase(RecC_s0080_b6b0* first, RecC_s0080_b6b0* last);
};
static int NameLen(const unsigned short* s)
{
    const unsigned short* p = s;
    while (*p != 0)
        ++p;
    return (int)(p - s);
}
// ---- items of slice s0080b6b0 end

// ---- items of slice s0080c5d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;
void* __cdecl  GameAlloc(size_t size, const char* name, int, int, const char* file, int line);
void  __cdecl  GameFree(void* p);
void  __stdcall ArrayCopy(void* dst, const void* src, unsigned elemSize, int count, void* copyfn);
void  __fastcall ElemCopy28(void* dst, const void* src);
void* __fastcall LayoutCtor(void* self);              // 0x810000
void  __fastcall VecDtorInline(void* self);           // 0x80b8f0
void  __fastcall VecDtorVec(void* self);              // 0x80b930
u8    __fastcall IsActive(void* self);                // 0x80b400
void  __fastcall Setup1(void* self, void* ctx);       // 0x80b4d0
void  __fastcall Setup2(void* self);                  // 0x80b6b0
void  __fastcall Setup3(void* self);                  // 0x80b000
void* __fastcall FindElem(void* self, float, float, void*); // 0x80c520
void* __cdecl  VecEraseMove(void* last, void* end, void* first);   // 0x80cab0
void  __cdecl  VecDestroy(void* first, void* last, void* dst);      // 0x80aee0
void* __cdecl  VecCopyCtor(void* first, void* last, void* dst);     // 0x80cbd0
void  __cdecl  VecMoveBack(void* first, void* last, void* dst);     // 0x80caf0
typedef void* (__thiscall *VF0)(void*);
typedef void  (__thiscall *VF0v)(void*);
typedef void  (__thiscall *VF1v)(void*, void*);
typedef void  (__thiscall *VFFv)(void*, float, float);
static inline void** VT(void* o) { return *(void***)o; }
struct cSPUIInfoLine;
struct LineHead {
    void* f4;
    void* f8;
    u8    v1[0x1b8];
};
class cSPUILayout_s0080_c5d0 { public:
    virtual void v00();
    virtual void AddRef();
    virtual void Release();
    void* __thiscall FindWindowByID(u32 id, int flag);   // 0x8105b0
    u8    __thiscall Init(const u32* key, int a, u32 b); // 0x8120d0
    void  __thiscall Shutdown(int a);                    // 0x811ad0
};
struct WinRef {
    virtual void v00();
    virtual void Release();                              // vtable +4
};
struct WinRec {
    void**  vtbl;        // +0x00 (0x1417cac)
    u8      body[0x28];  // +0x04 .. +0x2c
    WinRef* win;         // +0x2c
    u32     f30;         // +0x30
    WinRec* __thiscall Make(const void* src, void* win);  // 0x80af20
    WinRec* __thiscall CopyFrom(const WinRec* src);       // 0x80af90
};
struct SubVec {
    WinRec* begin;      // +0x00
    WinRec* end;        // +0x04
    WinRec* cap;        // +0x08
    void*   pad0c;      // +0x0c
    void*   alloc;      // +0x10 (points into buf)
    void*   pad14;      // +0x14
    u8      buf[0x23c]; // +0x18
    void __thiscall InitInline();
    void __thiscall CopyRange(void* first, void* last, const void* owner); // 0x80bbe0
    void __thiscall EraseRange(void* first, void* last);                   // 0x80bcf0
    void __thiscall PushBack(WinRec* rec);                                 // 0x80baa0
};
struct cSPUIInfoLine {
    void**        vtbl;        // +0x000
    void*         f4;          // +0x004
    void*         f8;          // +0x008
    u8            v1[0x1b8];   // +0x00c .. +0x1c4 (0xb * 0x28)
    SubVec        v2;          // +0x1c4 .. +0x418
    cSPUILayout_s0080_c5d0*  layout;      // +0x418
    u8            flag41c;     // +0x41c
    u8            pad41d[3];   // +0x41d
    u32           f420;        // +0x420
    f32           f424;        // +0x424
    f32           f428;        // +0x428

    cSPUIInfoLine* __thiscall ctor(const void* src);              // 0x80c840
    cSPUIInfoLine* __thiscall assign(const cSPUIInfoLine* o);     // 0x80c9f0
    cSPUIInfoLine* __thiscall ctor2(const cSPUIInfoLine* o);      // 0x80cb30
};
struct InfoVec {
    cSPUIInfoLine* begin;   // +0x00
    cSPUIInfoLine* end;     // +0x04
    cSPUIInfoLine* cap;     // +0x08
    void*          pad0c;   // +0x0c
    void*          alloc;   // +0x10 (inline buffer pointer)

    i32 Count() const { return (i32)((u8*)end - (u8*)begin) / 0x42c; }
    cSPUIInfoLine* __thiscall Erase(cSPUIInfoLine* first, cSPUIInfoLine* last); // 0x80cc10
    void __thiscall Insert(cSPUIInfoLine* pos, const cSPUIInfoLine* val);       // 0x80cc80
};
struct cSPUIInfoLineTray {
    void**          vtbl;     // +0x00
    cSPUIInfoLine*  mCurrent; // +0x04
    cSPUILayout_s0080_c5d0*    mLayout;  // +0x08
    InfoVec         mVec;     // +0x0c

    void  __thiscall Method(void* p, float fA, float fB, void* ctx);      // 0x80c5d0
    void  __thiscall dtor();                                               // 0x80cdd0
    void  __thiscall Add(const void* src);                                 // 0x80ce20
    void* __thiscall ScalarDeletingDtor(u8 flags);                         // 0x80ceb0
};
void __thiscall SubVec::InitInline()
{
    u8* inl = buf;
    alloc = inl;
    end = (WinRec*)inl;
    begin = (WinRec*)inl;
    cap = (WinRec*)(inl + 0x23c);
}
static inline f32 MaxF(f32 a, f32 b) { return a < b ? b : a; }
static inline f32 MinF(f32 a, f32 b) { return a < b ? a : b; }
struct Rect4 { float x1, y1, x2, y2; };
struct IWin_s0080_c5d0;
struct WinAux {                       // object returned by IWin slot 0x2a
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual IWin_s0080_c5d0* Query(u32 id);      // 0x0c
};
struct IWin_s0080_c5d0 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
    virtual IWin_s0080_c5d0* GetParent();                          // 0x10
    virtual void s5();
    virtual void s6();
    virtual u32 GetControlID();                         // 0x1c
virtual void s8();
virtual void s9();
virtual void s10();
    virtual u32 GetFlagsValue();                        // 0x2c
virtual void s12();
virtual void s13();
    virtual Rect4* GetArea();                           // 0x38
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
    virtual void SetShadeColor(u32 c);                  // 0x5c
    virtual void SetArea(Rect4* r);                     // 0x60
    virtual void SetLocation(float x, float y);         // 0x64
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
    virtual void SetFlag(int flag, int on);             // 0x7c
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
    virtual void s37();
    virtual void Invalidate();                          // 0x98
virtual void s39();
virtual void s40();
virtual void s41();
    virtual WinAux* GetAux();                           // 0xa8
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
    virtual int** ChildBegin(int** out);                // 0xcc
    virtual int** ChildEnd(int** out);                  // 0xd0
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
    virtual IWin_s0080_c5d0* FindWindowByID(u32 id, int flag);     // 0xf0
};
struct Xform { char pad[0x40]; int dirty; char pad2[0x10]; void __thiscall Scale(const float* v); };  // 0x95ea30
struct WinMsg {
    IWin_s0080_c5d0* source;     // +0
    u32   pad4;
    u32   type;       // +8
    u32   flagsNew;   // +0xc
    u32   flagsOld;   // +0x10
    u32   pad14;
    Xform* xform;     // +0x18
};
class cSPUILaunchScreenWinProc { public:
    void** vtbl;   // +0
    void** vtbl2;  // +4
    u32    f8;     // +8
    u32    fC;     // +0xc
    i32    f10;    // +0x10

    cSPUILaunchScreenWinProc* __thiscall ctor();             // 0x80cf00
    u8   __thiscall DoMessage(IWin_s0080_c5d0* window, WinMsg* msg);    // 0x80cf80
};
// ---- items of slice s0080c5d0 end

// @ 0x00800060
void* C_800060::ScalarDtor(uint8_t flags)
{
  *(void**)this = (void*)dv_a;
  *(void**)((char*)this + 4) = (void*)dv_b;
  _ReadWriteBarrier();
  RCBase* p = *(RCBase**)((char*)this + 0x1c);
  if (p) {
    *(void**)((char*)this + 0x1c) = 0;
    p->Release();
  }
  p = *(RCBase**)((char*)this + 0x1c);
  if (p)
    p->Release();
  f_800060_base(this);
  if (flags & 1)
    f_951330(this);
  return this;
}

// @ 0x00800ea0
void* __stdcall f_800ea0(int unused, void* alloc)
{
  if (!alloc)
    alloc = f_9512c0();
  cSPUIBehaviorWinEventBase* p =
      (cSPUIBehaviorWinEventBase*)f_9512d0(0x8c, 4, "UTFWin/cSPUIBehaviorWinEventBase", alloc);
  if (p) {
    p = new (p) cSPUIBehaviorWinEventBase(10, 0x7fffffff, 0);
    if (p)
      return ((IFactoryObj*)p)->v3(0x2f009dd0);
  }
  return 0;
}

// @ 0x00800ef0
void* __stdcall f_800ef0(int unused, void* alloc)
{
  if (!alloc)
    alloc = f_9512c0();
  cSPUIBehaviorWinBoolStateEvent* p =
      (cSPUIBehaviorWinBoolStateEvent*)f_9512d0(0x90, 4, "UTFWin/cSPUIBehaviorWinBoolStateEvent", alloc);
  if (p) {
    p = new (p) cSPUIBehaviorWinBoolStateEvent(1, 10, 0x7fffffff, 0);
    if (p)
      return ((IFactoryObj*)p)->v3(0x2f009dd0);
  }
  return 0;
}

// @ 0x008010a0
void* __stdcall f_8010a0(int unused, void* alloc)
{
  if (!alloc)
    alloc = f_9512c0();
  cSPUIBehaviorTimeFunctionSmoothRamp* p =
      (cSPUIBehaviorTimeFunctionSmoothRamp*)f_9512d0(0x48, 4, "UTFWin/cSPUIBehaviorTimeFunctionSmoothRamp", alloc);
  if (p) {
    p = new (p) cSPUIBehaviorTimeFunctionSmoothRamp(g_1471064, g_1471064);
    if (p)
      return ((IFactoryObj*)p)->v3(0xee3f516e);
  }
  return 0;
}

// @ 0x00801100
void* __stdcall f_801100(int unused, void* alloc)
{
  if (!alloc)
    alloc = f_9512c0();
  cSPUIBehaviorTimeFunctionDampedPeriodic* p =
      (cSPUIBehaviorTimeFunctionDampedPeriodic*)f_9512d0(0x50, 4, "UTFWin/cSPUIBehaviorTimeFunctionDampedPeriodic", alloc);
  if (p) {
    p = new (p) cSPUIBehaviorTimeFunctionDampedPeriodic(1);
    if (p)
      return ((IFactoryObj*)p)->v3(0xee3f516e);
  }
  return 0;
}

// @ 0x00802890
void* C_802890::f(void* want)
{
  void* w = ((CursorLayout*)((char*)this + 0x10))->FindWindowByID(0x14a4606, 1);
  if (!w)
    return 0;
  if (((void* (__thiscall*)(void*))((*(void***)w)[0x1c / 4]))(w) == want)
    return w;
  return ((void* (__thiscall*)(void*, void*, int))((*(void***)w)[0xf0 / 4]))(w, want, 1);
}

// @ 0x008028e0
bool __fastcall Sub_8028e0(void* self)
{
  if (*(void**)((char*)self + 0x28)) {
    ((CursorLayout*)((char*)self + 0x10))->Shutdown(true);
    RCObj* p = *(RCObj**)((char*)self + 0x28);
    if (p) {
      *(void**)((char*)self + 0x28) = 0;
      p->Release();
    }
  }
  return true;
}

// @ 0x00809db0
char __cdecl FUN_00809db0(void* where, const void* key)
{
    MsgBox* mem = (MsgBox*)dbgnew(0x78, "UI/cSPUIMessageBox", 0, 0, 0, 0);
    MsgBox* box;
    if (mem)
        box = mem->ctor(where);
    else
        box = 0;
    if (box) vcall0(box, 0);
    char ok = box->Init(key, true);
    if (ok) box->Show((const char*)0x15112d6, (const char*)0x15112d2, g_zero_13eb1bc, g_zero_13eb1bc);
    if (box) vcall0(box, 4);
    return ok;
}

// @ 0x00809f40
void HelperObj::Fn(IWin* w, void* arg)
{
    if (m4) m4->Fn4(w, arg);
    vcall1(w, 0x108, mC.p);
    if (mC.p) {
        IWin* old = mC.p;
        mC.p = 0;
        vcall0(old, 4);
    }
    FUN_00809e40(this);
    vcall1(this, 8, (void*)1);
}

// @ 0x00809fa0
Holder* Holder::DeleteThis(unsigned char flags)
{
    ComObj* p = mC;
    if (p) p->Release();
    ComObj* q = m8;
    if (q) q->Release();
    if (flags & 1)
        efree(this);
    return this;
}

// @ 0x00809ff0
void __cdecl FUN_00809ff0(void* self)
{
    float* r = (float*)vp0(vp0(self, 0x10), 0x38);
    float a = -r[0];
    float b = -r[1];
    float t0 = a + r[0];
    float t1 = b + r[1];
    ScaleArgs args;
    args.x = (r[2] + a) + t0;
    args.y = (b + r[3]) + t1;
    args.x *= g_half_1471064;
    args.y *= g_half_1471064;
    args.kind = 6;
    args.a = 8;
    args.b = 0x3e8;
    void* mgr = GetUTFManager();
    vcall4(mgr, 0x10, 0, (IWin*)vp0(self, 0x10), &args, 0);
    args.kind = 7;
    args.a = 0;
    mgr = GetUTFManager();
    vcall4(mgr, 0x10, 0, (IWin*)vp0(self, 0x10), &args, 0);
}

// @ 0x0080a390
void ModalBind::Fn(IWin* w)
{
    if (m4) m4->Fn0(w);
    WM* mgr = (WM*)GetUTFManager();
    if (mgr->w1())
        mgr->w19(0, mgr->w1());
    mgr->w19(0, w);
    void* alloc = GetUIAllocator();
    int* raw = (int*)op_new(0xc, 4, "cDoModalWinProc", alloc);
    int* obj;
    if (raw) {
        raw[1] = 0x13fa72c;
        raw[2] = 0;
        raw[0] = 0x1417bc0;
        raw[1] = 0x13fa750;
        obj = raw;
    } else {
        obj = 0;
    }
    IWin* old = mC.p;
    if ((IWin*)obj != old) {
        if (obj) ((IObj0*)obj)->f0();
        mC.p = (IWin*)obj;
        if (old) ((IObj4*)old)->f4();
    }
    vcall1(w, 0x104, mC.p);
}

// @ 0x0080a5f0
void FUN_0080a5f0()
{
    ((G*)&g_obj_15446c8)->FUN_0080a4f0(g_15446cc, g_15446d0);
    g_15446d4 = 0;
}

// @ 0x0080aa20
bool FUN_0080aa20(void* p)
{
    Sub* s = (Sub*)((char*)p + 0x20c);
    Sub* w = s->Fn10();
    float* r = w->Fn38();
    w->Fn74(g_const_13ef548, r[3] - r[1]);
    s->Fn1c(0);
    s->Fn1c(1);
    return true;
}

// @ 0x0080aa90
bool FUN_0080aa90(void* p)
{
    Sub* s = (Sub*)((char*)p + 0x20c);
    Sub* w = s->Fn10();
    float* r = w->Fn38();
    w->Fn74(g_const_13ef548, r[3] - r[1]);
    Win2* o = (Win2*)p;
    o->Fn88(0);
    o->Fn88(1);
    return true;
}

// @ 0x0080ab00
void FUN_0080ab00()
{ /* not reconstructed */ }

// @ 0x0080acb0
void FUN_0080acb0()
{ /* not reconstructed */ }

// @ 0x0080b000
void FUN_0080b000()
{ /* not reconstructed */ }

// @ 0x0080b170
unsigned int __stdcall FUN_0080b170(void* actor, char mode, float a, float b, float c)
{
    char* sub1 = 0;
    if (actor != 0) {
        char* w = (char*)((ActorFind*)actor)->Find(0xf15f4bd);
        if (w != 0)
            sub1 = w - 0x20c;           // subobject header sits 0x20c before the window
    }
    char* sub2 = 0;
    if (actor != 0) {
        char* w = (char*)((ActorFind*)actor)->Find(0x8ed27e7a);
        if (w != 0)
            sub2 = w - 0x20c;
    }
    if (mode == 0) {
        if (sub1 != 0)
            return FUN_0080aa20(sub1);
        if (sub2 != 0)
            return FUN_0080aa90(sub2);
    } else {
        if (sub1 != 0)
            return FUN_0080ab00_dispatch(sub1, a, b, c);
        if (sub2 != 0)
            return FUN_0080acb0_dispatch(sub2, a, b, c);
    }
    return 1;
}

// @ 0x0080b2d0
RecC* copyBack(void* unused, RecC* begin, RecC* end, RecC* dst)
{
    (void)unused;
    if (end == begin)
        return dst;
    do {
        --end;
        --dst;
        *dst = *end;
    } while (end != begin);
    return dst;
}

// @ 0x0080b340
RecC* copyFwd(void* unused, RecC* begin, RecC* end, RecC* dst)
{
    (void)unused;
    if (begin == end)
        return dst;
    do {
        *dst = *begin;
        ++begin;
        ++dst;
    } while (begin != end);
    return dst;
}

// @ 0x0080b3b0
void FUN_0080b3b0()
{ /* deleting destructor of a 0x34 record; not reconstructed */ }

// @ 0x0080b400
bool AtlasState::Validate()
{
    if (mReady == 0)
        return false;
    for (unsigned int i = 0; i < (unsigned int)(((char*)mpEnd - (char*)mpBegin) / 0x34); i++) {
        AtlasEntry* e = mpBegin + i;
        bool checkFlags = false;
        if (e->mpOwner != 0) {
            if (((e->mFlags >> 10) & 1) != 0) {
                const unsigned short* s = e->mpOwner->Title();
                if (s != 0) {
                    const unsigned short* q = s;
                    while (*q != 0)
                        ++q;
                    if ((int)(q - s) >= 1)
                        checkFlags = true;
                }
            } else {
                checkFlags = true;
            }
        }
        if (checkFlags && ((e->mFlags >> 8) & 1) == 0)
            return true;
    }
    return false;
}

// @ 0x0080b4d0
void FUN_0080b4d0()
{ /* not reconstructed */ }

// @ 0x0080b6b0
void Big3::FUN_0080b6b0()
{
    float span = 0.0f;
    float height = 0.0f;
    for (int i = 0; i < records.Count(); ++i) {
        VecRec* r = &records.begin[i];
        Win* w = r->ref;
        if (w == 0) {
            w->w7c(1, 0);
            continue;
        }
        if (((r->flags >> 10) & 1) != 0) {
            const unsigned short* nm = w->label();
            if (nm == 0 || nm[0] == 0) {
                w->w7c(1, 0);
                continue;
            }
        }
        if (((r->flags >> 8) & 1) != 0) {
            w->w7c(1, 0);
            continue;
        }
        w->w7c(1, 1);
        w->w70(span, 0.0f);
        if (((r->flags >> 10) & 1) != 0)
            FUN_0080b170(w, 0, 1.0f, 0.0f, 1000000.0f);
        float* rc = w->rect();
        span += rc[2] - rc[0];
        float h = rc[3] - rc[1];
        if (height < h)
            height = h;
    }
    Win* win = (Win*)layout->FindWindowByID(0x79830aa, 0);
    win->w74(span, height);
    f424 = span;
    f428 = height;
    state = 1;
}

// @ 0x0080b8a0
void* Big3::method(int a)
{
    if (layout != 0 && flag != 0) {
        void* w = layout->FindWindowByID(0x79830aa, 0);
        FUN_0080b4d0(a);
        FUN_0080b6b0();
        FUN_0080b000();
        return w;
    }
    return 0;
}

// @ 0x0080b8f0
void __fastcall Vec34Dtor(int* v)
{
    E34* p = (E34*)v[0];
    E34* e = (E34*)v[1];
    for (; p < e; ++p)
        p->Fn(0);
    int d = v[0];
    if (d != 0 && d != v[4])
        efree((void*)d);
}

// @ 0x0080b930
void __fastcall Vec42CDtor(int* v)
{
    E42C* p = (E42C*)v[0];
    E42C* e = (E42C*)v[1];
    for (; p < e; ++p)
        p->Fn(0);
    int d = v[0];
    if (d != 0 && d != v[4])
        efree((void*)d);
}

// @ 0x0080b9b0
void* Big3::DeletingDtor(char flags)
{
    vtbl = (void*)0x1417cb0;
    Layout* l = layout;
    if (l != 0) {
        layout = 0;
        l->v2();
    }
    if (layout != 0)
        layout->v2();
    Vec34Dtor((int*)&records.begin);
    if (flags & 1)
        efree(this);
    return this;
}

// @ 0x0080ba10
ObjB* __fastcall ObjBCtor(ObjB* o)
{
    o->vtbl = (void*)ObjB_vtable;
    o->f1 = 0;
    o->f2 = 0;
    void* p = (char*)o + 0x24;
    o->f7 = (int)p;
    o->f4 = (int)p;
    o->f3 = (int)p;
    p = (char*)p + 0x5370;
    o->f5 = (int)p;
    return o;
}

// @ 0x0080baa0
void RecVec::Insert(VecRec* pos, const VecRec* value)
{
    if (end != cap) {
        const VecRec* v = value;
        if (v >= pos && v < end)
            ++v;
        if (end != 0)
            end->CopyFrom(end - 1);
        CopyBackward(pos, end - 1, end);
        pos->CopyAssign(v);
        ++end;
        return;
    }
    int n = (int)(end - begin);
    unsigned int newCap = n != 0 ? (unsigned int)n * 2 : 1;
    VecRec* mem = 0;
    if (newCap != 0)
        mem = (VecRec*)GameAlloc(newCap * 0x34, (const char*)0x13f6b3c, 0, 0,
                                 (const char*)0x13ebb38, 0xd1);
    VecRec* mid = UninitCopy(begin, pos, mem);
    DestroyRange(begin, pos, mem);
    if (mid != 0)
        mid->CopyFrom(value);
    VecRec* e = end;
    VecRec* p2 = UninitCopy(pos, e, mid + 1);
    DestroyRange(pos, e, mid + 1);
    if (begin != 0 && begin != inlineBuf)
        efree(begin);
    begin = mem;
    end = p2;
    cap = mem + newCap;
}

// @ 0x0080bbe0
void RecVec::Assign(const VecRec* first, VecRec* last, const void* owner)
{
    int count = (int)(last - first);
    if (count > (int)(cap - begin)) {
        VecRec* mem = AllocCopyRange(count, first, last);
        for (VecRec* p = begin; p < end; ++p)
            p->Destroy(0);
        if (begin != 0 && begin != inlineBuf)
            efree(begin);
        begin = mem;
        end = mem + count;
        cap = end;
        return;
    }
    int cur = (int)(end - begin);
    if (count > cur) {
        CopyForward(first, first + cur, begin);
        UninitCopyOut(&last, first + cur, last, end);
        end = last;
        return;
    }
    VecRec* newEnd = CopyForward(first, last, begin);
    DestroyRange2(newEnd, end);
    end = newEnd;
}

// @ 0x0080bcf0
RecC_s0080_b6b0* Vec::erase(RecC_s0080_b6b0* first, RecC_s0080_b6b0* last)
{
    RecC_s0080_b6b0* newEnd = copyFwd(last, end, first);
    RecC_s0080_b6b0* e = end;
    for (RecC_s0080_b6b0* p = newEnd; p < e; ++p)
        p->Fn(0);
    end = end - (last - first);
    return first;
}

// @ 0x0080bd50
void Big3::FUN_0080bd50(float offset)
{
    PtrVec list;
    list.Init();
    for (int i = 0; i < records.Count(); ++i) {
        VecRec* r = &records.begin[i];
        Win* w = r->ref;
        if (w == 0)
            continue;
        if (((r->flags >> 10) & 1) != 0) {
            const unsigned short* nm = w->label();
            if (nm == 0 || nm[0] == 0)
                continue;
        }
        if (((r->flags >> 8) & 1) != 0)
            continue;
        VecRec* rec = r;
        if (list.end < list.cap) {
            VecRec** slot = (VecRec**)list.end;
            list.end = (void**)(slot + 1);
            if (slot != 0)
                *slot = rec;
        } else {
            list.InsertAt(list.end, (void* const*)&rec);
        }
    }
    Win* win = (Win*)layout->FindWindowByID(0x79830aa, 1);
    f428 = offset;
    win->w74(offset, f424);
    int n = list.Count();
    int limit = n;
    for (int i = 0; i < n; ++i) {
        VecRec* r = (VecRec*)list.begin[i];
        if (((r->flags >> 3) & 1) != 0) {
            limit = i;
            break;
        }
    }
    float acc = offset;
    for (int i = 0; i < limit; ++i) {
        VecRec* r = (VecRec*)list.begin[i];
        float* rc = r->ref->rect();
        r->ref->w70(acc, rc[1]);
        acc += rc[2] - rc[0];
    }
    acc = f428;
    for (int i = n - 1; i >= limit; --i) {
        VecRec* r = (VecRec*)list.begin[i];
        float* rc = r->ref->rect();
        acc -= rc[2] - rc[0];
        r->ref->w70(acc, rc[1]);
    }
    if (list.begin != 0 && list.begin != list.inlineBuf)
        efree(list.begin);
}

// @ 0x0080bfb0
bool Big3::FUN_0080bfb0(float width)
{
    PtrVec vis;
    vis.Init();
    for (int i = 0; i < records.Count(); ++i) {
        VecRec* r = &records.begin[i];
        Win* w = r->ref;
        if (w == 0)
            continue;
        if (((r->flags >> 10) & 1) != 0) {
            const unsigned short* nm = w->label();
            if (nm == 0 || nm[0] == 0)
                continue;
        }
        if (((r->flags >> 8) & 1) != 0)
            continue;
        VecRec* rec = r;
        if (vis.end < vis.cap) {
            VecRec** slot = (VecRec**)vis.end;
            vis.end = (void**)(slot + 1);
            if (slot != 0)
                *slot = rec;
        } else {
            vis.InsertAt(vis.end, (void* const*)&rec);
        }
    }

    PtrVec group;
    group.Init();
    float sum = 0.0f;
    int visCount = vis.Count();
    for (int i = 0; i < visCount; ++i) {
        VecRec* r = (VecRec*)vis.begin[i];
        unsigned int u = r->flags;
        if (((u >> 6) & 1) == 0 && (((u >> 10) & 1) == 0 || ((u >> 5) & 1) == 0)) {
            float* rc = r->ref->rect();
            sum += rc[2] - rc[0];
        } else {
            VecRec* rec = r;
            if (group.end < group.cap) {
                VecRec** slot = (VecRec**)group.end;
                group.end = (void**)(slot + 1);
                if (slot != 0)
                    *slot = rec;
            } else {
                group.InsertAt(group.end, (void* const*)&rec);
            }
        }
    }

    float gap = width - sum;
    int nGroup = group.Count();
    int shrunk = 0;
    bool all = false;
    if (gap > 0.0f && nGroup != 0) {
        float avg = sum / (float)(visCount - nGroup);
        for (int i = 0; i < nGroup; ++i) {
            VecRec* r = (VecRec*)group.begin[i];
            if (((r->flags >> 10) & 1) == 0) {
                float box[4];
                float* rc = r->ref->rect();
                box[0] = rc[0];
                box[1] = rc[1];
                box[2] = rc[2];
                box[3] = rc[3];
                if ((box[2] - box[0]) - avg > 0.0f) {
                    group.begin[i] = 0;
                    gap -= box[2] - box[0];
                    r->ref->w6c(box);
                    ++shrunk;
                }
            }
        }
        if (gap > 1.0f && shrunk < group.Count()) {
            float total = 0.0f;
            for (int i = 0; i < nGroup; ++i) {
                VecRec* r = (VecRec*)group.begin[i];
                if (r != 0)
                    total += (float)NameLen(r->ref->label());
            }
            for (int i = 0; i < nGroup; ++i) {
                VecRec* r = (VecRec*)group.begin[i];
                if (r != 0) {
                    float len = (float)NameLen(r->ref->label());
                    float f = (len / total) * gap;
                    FUN_0080b170(r->ref, 1, 1.5f, f, f);
                    float* rc = r->ref->rect();
                    gap -= rc[2] - rc[0];
                    total -= len;
                    group.begin[i] = 0;
                    float h = rc[3] - rc[1];
                    if (f424 < h)
                        f424 = h;
                    ++shrunk;
                }
            }
        }
        f428 = 0.0f;
        FUN_0080bd50(width);
        Win* win = (Win*)layout->FindWindowByID(0x79830aa, 1);
        win->w74(f428, f424);
        FUN_0080b000();
        all = shrunk == group.Count();
    }
    if (group.begin != 0 && group.begin != group.inlineBuf)
        efree(group.begin);
    if (vis.begin != 0 && vis.begin != vis.inlineBuf)
        efree(vis.begin);
    return all;
}

// @ 0x0080c520
Win* Big3::FUN_0080c520(float a, float b, int c)
{
    Win* win = (Win*)layout->FindWindowByID(0x79830aa, 0);
    if (state == 0)
        win = (Win*)method(c);
    if (win == 0)
        return 0;
    if (state != 1 && state != 2)
        return 0;
    state = 2;
    float* rc = win->rect();
    float w = rc[2] - rc[0];
    if (w < a) {
        FUN_0080bd50(a);
        return win;
    }
    if (w > b) {
        if (!FUN_0080bfb0(b))
            return 0;
    }
    return win;
}

// @ 0x0080c5d0
void __thiscall cSPUIInfoLineTray::Method(void* p, float fA, float fB, void* ctx)
{
    cSPUIInfoLine* old = mCurrent;
    if (p != old) {
        if (p) ((VF0v)VT(p)[0])(p);          // AddRef
        mCurrent = (cSPUIInfoLine*)p;
        if (old) ((VF0v)VT(old)[1])(old);    // Release
    }
    f32 acc = 0.0f;
    for (u32 i = 0, off = 0; i < (u32)mVec.Count(); ++i, off += 0x42c) {
        cSPUIInfoLine* e = (cSPUIInfoLine*)((u8*)mVec.begin + off);
        if (IsActive(e) && e->layout && e->flag41c) {
            void* win = e->layout->FindWindowByID(0x79830aa, 0);
            Setup1(e, ctx);
            Setup2(e);
            Setup3(e);
            if (win) {
                float* r = (float*)((VF0)VT(win)[0x38 / 4])(win);
                f32 d = r[2] - r[0];
                acc = MaxF(acc, d);
            }
        }
    }
    acc = MinF(MaxF(acc, fA), fB);
    f32 pos = 0.0f;
    for (u32 i = 0, off = 0; i < (u32)mVec.Count(); ++i, off += 0x42c) {
        cSPUIInfoLine* e = (cSPUIInfoLine*)((u8*)mVec.begin + off);
        if (!IsActive(e)) continue;
        cSPUIInfoLine* x = (cSPUIInfoLine*)FindElem(e, acc, acc, ctx);
        if (!x) continue;
        ((VF0v)VT(x)[0])(x);                       // AddRef
        void* s = ((VF0)VT(x)[0x10 / 4])(x);
        if (s) {
            void* s2 = ((VF0)VT(x)[0x10 / 4])(x);
            ((VF1v)VT(s2)[0xdc / 4])(s2, x);
        }
        ((VF1v)VT(p)[0xd8 / 4])(p, x);
        ((VFFv)VT(x)[0x70 / 4])(x, 0.0f, pos);
        float* r = (float*)((VF0)VT(x)[0x38 / 4])(x);
        pos += r[3] - r[1];
        ((VF0v)VT(x)[1])(x);                       // Release
    }
    ((VFFv)VT(p)[0x74 / 4])(p, acc, pos);
}

// @ 0x0080c840
cSPUIInfoLine* __thiscall cSPUIInfoLine::ctor(const void* src)
{
    vtbl = (void**)0x1417cb0;
    f4 = *(void* const*)src;
    f8 = *((void* const*)src + 1);
    ArrayCopy(v1, (const u8*)src + 8, 0x28, 0xb, (void*)ElemCopy28);
    v2.InitInline();
    layout = 0;
    flag41c = 1;
    void* w = f4 ? f4 : (void*)0x40464100;
    cSPUILayout_s0080_c5d0* lay = (cSPUILayout_s0080_c5d0*)GameAlloc(0x18, "UI/cSPUIInfoLine", 0, 0, 0, 0);
    if (lay) lay = (cSPUILayout_s0080_c5d0*)LayoutCtor(lay);
    if (lay != layout) {
        if (lay) lay->AddRef();
        cSPUILayout_s0080_c5d0* prev = layout;
        layout = lay;
        if (prev) prev->Release();
    }
    u32 key[3];
    key[0] = (u32)f8;
    key[1] = 0x510a95b;
    key[2] = (u32)w;
    if (!layout->Init(key, 0, 0x5b598fa)) {
        layout->Shutdown(1);
        if (layout) { cSPUILayout_s0080_c5d0* l2 = layout; layout = 0; l2->Release(); }
        flag41c = 0;
    }
    if (layout) {
        for (i32 i = 0; i < 0xb; ++i) {
            u32 id = *(u32*)(v1 + i * 0x28);
            if (id == 0) break;
            void* win = layout->FindWindowByID(id, 1);
            WinRec tmp;
            WinRec* r = tmp.Make(v1 + i * 0x28, win);
            if (v2.end < v2.cap) {
                WinRec* slot = v2.end;
                v2.end = (WinRec*)((u8*)v2.end + 0x34);
                if (slot) slot->CopyFrom(r);
            } else {
                v2.PushBack(r);
            }
            tmp.vtbl = (void**)0x1417cac;
            if (tmp.win) { WinRef* wr = tmp.win; tmp.win = 0; wr->Release(); }
            if (tmp.win) tmp.win->Release();
        }
    }
    return this;
}

// @ 0x0080c9f0
cSPUIInfoLine* __thiscall cSPUIInfoLine::assign(const cSPUIInfoLine* o)
{
    *(LineHead*)&f4 = *(const LineHead*)&o->f4;
    if (&v2 != &o->v2) {
        SubVec& sv = v2;
        sv.EraseRange(sv.begin, sv.end);
        const SubVec& ov = o->v2;
        sv.CopyRange(ov.begin, ov.end, o);
    }
    cSPUILayout_s0080_c5d0* nl = o->layout;
    cSPUILayout_s0080_c5d0* prev = layout;
    if (nl != prev) {
        if (nl) nl->AddRef();
        layout = nl;
        if (prev) prev->Release();
    }
    flag41c = o->flag41c;
    f420 = o->f420;
    f424 = o->f424;
    f428 = o->f428;
    return this;
}

// @ 0x0080cb30
cSPUIInfoLine* __thiscall cSPUIInfoLine::ctor2(const cSPUIInfoLine* o)
{
    vtbl = (void**)0x1417cb0;
    f4 = o->f4;
    f8 = o->f8;
    ArrayCopy(v1, o->v1, 0x28, 0xb, (void*)ElemCopy28);
    v2.InitInline();
    const SubVec& ov = o->v2;
    v2.CopyRange(ov.begin, ov.end, o);
    layout = o->layout;
    if (layout) layout->AddRef();
    flag41c = o->flag41c;
    f420 = 0;
    return this;
}

// @ 0x0080cc10
cSPUIInfoLine* __thiscall InfoVec::Erase(cSPUIInfoLine* first, cSPUIInfoLine* last)
{
    cSPUIInfoLine* p = (cSPUIInfoLine*)VecEraseMove(last, end, first);
    cSPUIInfoLine* e = end;
    while (p < e) {
        ((VF1v)VT(p)[0])(p, 0);
        p = (cSPUIInfoLine*)((u8*)p + 0x42c);
    }
    end -= last - first;
    return first;
}

// @ 0x0080cc80
void __thiscall InfoVec::Insert(cSPUIInfoLine* pos, const cSPUIInfoLine* val)
{
    if (end != cap) {
        cSPUIInfoLine* v = (cSPUIInfoLine*)val;
        if (v >= pos && v < end) v = (cSPUIInfoLine*)((u8*)v + 0x42c);
        if (end) ((cSPUIInfoLine*)end)->ctor2((cSPUIInfoLine*)((u8*)end - 0x42c));
        VecMoveBack(pos, (cSPUIInfoLine*)((u8*)end - 0x42c), end);
        pos->assign(v);
        end = (cSPUIInfoLine*)((u8*)end + 0x42c);
        return;
    }
    i32 n = (i32)((u8*)end - (u8*)begin) / 0x42c;
    u32 newCap = n ? (u32)n * 2 : 1;
    u8* mem;
    if (newCap) mem = (u8*)GameAlloc(newCap * 0x42c, (const char*)0x13f6b3c, 0, 0, (const char*)0x13ebb38, 0xd1);
    else        mem = 0;
    u8* p = (u8*)VecCopyCtor(begin, pos, mem);
    VecDestroy(begin, pos, mem);
    if (p) ((cSPUIInfoLine*)p)->ctor2(val);
    cSPUIInfoLine* e = end;
    u8* p2 = (u8*)VecCopyCtor(pos, e, p + 0x42c);
    VecDestroy(pos, e, p + 0x42c);
    if (begin && begin != (cSPUIInfoLine*)alloc) GameFree(begin);
    begin = (cSPUIInfoLine*)mem;
    end = (cSPUIInfoLine*)p2;
    cap = (cSPUIInfoLine*)(mem + newCap * 0x42c);
}

// @ 0x0080cdd0
void __thiscall cSPUIInfoLineTray::dtor()
{
    if (mLayout) mLayout->Shutdown(1);
    if (mLayout) {
        cSPUILayout_s0080_c5d0* l = mLayout;
        mLayout = 0;
        ((VF0v)VT(l)[2])(l);
    }
    if (mCurrent) {
        cSPUIInfoLine* c = mCurrent;
        mCurrent = 0;
        ((VF0v)VT(c)[1])(c);
    }
    mVec.Erase(mVec.begin, mVec.end);
}

// @ 0x0080ce20
void __thiscall cSPUIInfoLineTray::Add(const void* src)
{
    cSPUIInfoLine tmp;
    cSPUIInfoLine* e = tmp.ctor(src);
    InfoVec* v = &mVec;
    if (v->end < v->cap) {
        cSPUIInfoLine* slot = v->end;
        v->end = (cSPUIInfoLine*)((u8*)slot + 0x42c);
        if (slot) slot->ctor2(e);
    } else {
        v->Insert(v->end, e);
    }
    cSPUILayout_s0080_c5d0* l = tmp.layout;
    tmp.vtbl = (void**)0x1417cb0;
    if (l) { tmp.layout = 0; l->Release(); }
    if (tmp.layout) tmp.layout->Release();
    VecDtorInline(&tmp.v2);
}

// @ 0x0080ceb0
void* __thiscall cSPUIInfoLineTray::ScalarDeletingDtor(u8 flags)
{
    vtbl = (void**)0x1417cb4;
    dtor();
    VecDtorVec(&mVec);
    if (mLayout) ((VF0v)VT(mLayout)[2])(mLayout);
    if (mCurrent) ((VF0v)VT(mCurrent)[1])(mCurrent);
    if (flags & 1) GameFree(this);
    return this;
}

// @ 0x0080cf00
cSPUILaunchScreenWinProc* __thiscall cSPUILaunchScreenWinProc::ctor()
{
    vtbl2 = (void**)0x13ec458;
    f8 = 0;
    vtbl = (void**)0x1417d14;
    vtbl2 = (void**)0x1417d04;
    fC = 3;
    f10 = -1;
    return this;
}
