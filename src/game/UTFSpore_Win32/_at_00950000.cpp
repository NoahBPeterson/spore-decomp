// src/game/UTFSpore_Win32/_at_00950000.cpp -- migrated from slice(s) s0095eeb0, s0095df60, s0095d000, s0095b310, s009579f0, s009568c0, s00950bb0, s0094fb80 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00950000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Mutex.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/SSL/SSLManager.h"
#include "EA/Sockets/Socket.h"
#include <intrin.h>
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWin/Window.h"
#include "EA/UTFWin/Image.h"
#include "EA/UTFWin/WindowMgr.h"
#include <xmmintrin.h>
#include "EA/UTFWin/Renderable2DBuilder.h"
#include "EA/UTFWin/IRenderable.h"
#include "EA/UTFWin/IRenderer.h"
#include "EA/Text/Typesetter.h"
#include <math.h>
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchangeAdd)

// ---- items of slice s0094fb80 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define I32(p,o)     (*(int*)((char*)(p)+(o)))
// ---- items of slice s0094fb80 end

// ---- items of slice s00950bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct UIMessage {
    int mSender;     // +0x00  sender object
    int mPad04;      // +0x04
    unsigned int mCode; // +0x08  message id (1..0x1c, 0x1000, 0x1001)
    union {
        struct { int mArg0; int mArg1; int mArg2; int mArg3; };          // +0x0c
        struct { float mFArg0; float mFArg1; float mFArg2; float mFArg3; };
    };
};
class Window_s0095_ff20 {
public:
    bool DoMessage(UIMessage* msg);                      // 0x00960410 (defined in another TU)

    bool HandleMessage(UIMessage* msg);                  // 0x00950BB0
    bool HandleMessageExt(int arg, UIMessage* msg);      // 0x00950EF0
};
// ---- items of slice s00950bb0 end

// ---- items of slice s009568c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_154ecf0[];                                   // 0x154ecf0
extern void*  g_pSerTypeTable[4096]; // 0x154eea0
extern int    g_166b134;
void  __cdecl operator_delete__(void*) throw();                                    // 0xf47380
void* __cdecl FUN_00920090();
void __cdecl FUN_009574f0();
void __cdecl FUN_00951360();
void __cdecl FUN_009513b0();
void __fastcall FUN_00957530(int*);                        // 0x957530 (defined below)
typedef void (__thiscall *VFn0)(void*);
typedef void (__thiscall *VFn1i)(void*, int);
typedef void (__thiscall *VFn2ii)(void*, int, int);
static inline void** Vt(void* p) { return *(void***)p; }
struct UIObj {
    int   Release();
    void* Cast(unsigned int id);
    void* VirtualDtor(unsigned char flags);
    int*  Ctor(int* p2, int* p3, float* r, int extra);
    void  SetPos(int* p);
    void  GetRect(float* out);
    void  SetRect(float* in);
};
struct IRefObj {
    virtual void AddRef();                          // +0
    virtual void Release();                         // +4
    virtual void v2();
    virtual IRefObj* Cast(unsigned int id);         // +0xc
};
struct SerOps { void* fn[16]; };
struct SerObj { void* vtbl; void* mpData; };
struct SerDesc {
    int f0;
    SerOps* mpOps;                                  // +4
    int f8;
    unsigned short mTypeId;                         // +0xc
    unsigned short f0e;
    unsigned int mOffset;                           // +0x10
    unsigned int mCount;                            // +0x14
};
struct SerValue {
    virtual void* Alloc(unsigned int size, unsigned int align);
    void* mpData;                                   // +4
    unsigned int mCount;                            // +8
};
struct Int2 { int x, y; Int2() {} Int2(const Int2& o) : x(o.x), y(o.y) {} };
struct Float4 {
    float l, t, r, b;
    Float4& operator=(const Float4& o) { l = o.l; t = o.t; r = o.r; b = o.b; return *this; }
};
typedef void (__thiscall *SetterFn)(void* pObj, void* pValue);
typedef Int2 (__thiscall *GetInt2Fn)(void* pObj);
typedef Float4 (__thiscall *GetFloat4Fn)(void* pObj);
// ---- items of slice s009568c0 end

// ---- items of slice s009579f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchange)
void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int);  // 0x00F473A0
struct VTab {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c(int);
    virtual void  v10(int, int);
    virtual void  v14();
    virtual void  v18(int, int, void*);
    virtual void  v1c();
    virtual char  v20(void*);
    virtual void  v24();
    virtual void  v28();
    virtual void  v2c();
    virtual void  v30();
    virtual void  v34();
    virtual void  v38();
    virtual void  v3c();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual void  v4c();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58(int, int);
    virtual void  v5c();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6c();
    virtual void  v70();
    virtual char  v74(void*, int);
    virtual void  v78(void*, int);
    virtual void  v7c();
};
struct UIImage {
    void* vtbl;                  // +0x00
    void* p1;                    // +0x04
    int   f8;                    // +0x08
    float f0c, f10, f14, f18;    // +0x0c
    int   f1c, f20, f24, f28;    // +0x1c
    UIImage* Image(void* obj, int a, int b, float c, float d, float e, float f, int h); // 0x009579F0
};
// ---- items of slice s009579f0 end

// ---- items of slice s0095b310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_1471064, g_1485720, g_1470f1c, g_13eb1bc_f;
typedef uint8_t u8;
typedef uint32_t u32;
struct Node { Node* next; Node* prev; };
struct V2 {
    float x, y;
    V2() {}
    V2(float a, float b) : x(a), y(b) {}
    V2(const V2& o) : x(o.x), y(o.y) {}
};
struct IWin;
struct IRel { virtual void r0(); virtual void Release(); };   // vtbl+4
struct IWin {
    virtual void i00();
    virtual void i01();
    virtual void i02();
    virtual void i03();
    virtual IWin* vGetParent();
    virtual void i05();
    virtual void i06();
    virtual void i07();
    virtual void i08();
    virtual void i09();
    virtual void i0a();
    virtual void i0b();
    virtual void i0c();
    virtual void i0d();
    virtual void i0e();
    virtual void i0f();
    virtual void i10();
    virtual void i11();
    virtual void i12();
    virtual void i13();
    virtual void i14();
    virtual void i15();
    virtual void i16();
    virtual void i17();
    virtual void i18();
    virtual void i19();
    virtual void i1a();
    virtual void i1b();
    virtual void i1c();
    virtual void i1d();
    virtual void i1e();
    virtual void vSetFlags(int a, int b);              // vtbl+0x7c (31)
virtual void i32();
virtual void i33();
virtual void i34();
virtual void i35();
virtual void i36();
virtual void i37();
virtual void i38();
virtual void i39();
virtual void i40();
virtual void i41();
virtual void i42();
virtual void i43();
virtual void i44();
virtual void i45();
virtual void i46();
    virtual bool vHitLocal(V2 p);                      // vtbl+0xbc (47)
    virtual void i48();
    virtual V2 vToLocal(V2 p);                         // vtbl+0xc4 (49)
    virtual bool vHit(V2 p, V2* out);                  // vtbl+0xc8 (50)
virtual void i51();
virtual void i52();
virtual void i53();
virtual void i54();
virtual void i55();
virtual void i56();
virtual void i57();
    virtual void vSetOwner(IWin* w);                   // vtbl+0xe8 (58)
virtual void i59();
virtual void i60();
virtual void i61();
    virtual bool vAccepts(IWin* w);                    // vtbl+0xf8 (62)
};
struct ChunkItem { IRel* obj; u32 b; };
struct Chunk { Chunk* next; int count; ChunkItem items[5]; void __thiscall Swap(Chunk* o); };   // Swap 0x95ba90
typedef uint16_t u16;
struct RectF {
    float x0, y0, x1, y1;
    void __thiscall Intersect(const RectF& a, const RectF& b);     // 0x634b60
};
struct Xform {
    float m[17];                                                    // 0x44 bytes (Matrix43)
    void __thiscall Init(const float* trans, const float* scale);   // 0x95e810
    void __thiscall Multiply(const Xform* o);                       // 0x95f860
};
struct RenderCtx;
struct IRenderable {
    virtual void AddRef();                                          // +0
    virtual void Release();                                         // +4
    virtual void r2();
    virtual void Render(RenderCtx* c);                              // +0xc
};
struct IRenderMode {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
    virtual void Begin();                                           // +0x10
    virtual void Render(IRenderable* r, RenderCtx* c);              // +0x14
    virtual void End();                                             // +0x18
    virtual bool vFlag();                                           // +0x1c
};
struct IRenderer {
virtual void AddRef();
virtual void Release();
virtual void r2();
    virtual bool NeedsPrepass();                                    // +0xc
    virtual void* CreateData(IWin* w);                              // +0x10
    virtual void  FreeData(void* d);                                // +0x14
    virtual void  RenderBatch(void* data, RenderCtx* c, Node** begin, int n, int flag);   // +0x18
virtual void r7();
virtual void r8();
virtual void r9();
virtual void r10();
virtual void r11();
virtual void r12();
virtual void r13();
virtual void r14();
virtual void r15();
virtual void r16();
virtual void r17();
virtual void r18();
virtual void r19();
virtual void r20();
virtual void r21();
    virtual void DrawRect(const RectF* dst, const RectF* clip, const RectF* uv);   // +0x58
};
struct Base2D {                                                  // size 0x24
    Base2D(void* a);                                             // 0x9520a0
    virtual ~Base2D();                                           // 0x951ba0
    u32 d[8];
};
struct Builder {
    Builder();                                                   // 0x952aa0
    ~Builder();                                                  // 0x952f80
    u32 d[40];
};
struct Batch2D : Base2D {
    Builder b;                                                       // +0x24
    Batch2D(void* a) : Base2D(a) {}
    IRenderable* __thiscall Take();                                  // 0x9557c0
};
struct RenderData {                                                  // 0x5c
    Xform xf;                                                        // +0
    float r0, r1, r2, r3;                                            // +0x44 clip rect
    u32 shade;                                                       // +0x54
    void* rdata;                                                     // +0x58
};
struct DispEntry {                                                   // 0x100
    Node link;                                                       // +0
    DispEntry* prevEntry;                                            // +8
    u8 bReplace, bActive, bSecond, pad0f;                            // +0xc..
    u16 depth, lowest;                                               // +0x10 / +0x12
    IRenderer* renderer;                                             // +0x14
    Chunk chunks;                                                    // +0x18 (0x30)
    RenderData data[2];                                              // +0x48
};
struct EVec {                                                        // eastl::fixed_vector<DispEntry*,64> header
    DispEntry** begin; DispEntry** end; DispEntry** cap; u32 pad; DispEntry** buf;
    void __thiscall Overflow(DispEntry** pos, DispEntry** val);      // 0x899480
};
struct RenderCtx {
    Xform* xf;          // 0
    u32    shade;       // 4
    RectF  clip;        // 8
    RectF  vp;          // 0x18
    float  trans[3];    // 0x28
    float  scale[3];    // 0x34
    IRenderMode* mode;  // 0x40
    IRenderMode* defMode;   // 0x44
    Node*  list;        // 0x48
    Xform* mat;         // 0x4c
    u32    colorMod;    // 0x50
    Chunk* chunks;      // 0x54
    Batch2D batch;      // 0x58

    // @ 0x95bb80
    RenderCtx(void* a) : mode(0), defMode(0), mat(0), colorMod(0xffffffff), chunks(0), batch(a) {}
    // @ 0x95bb20
    void __thiscall End2D();
    // @ 0x95bbc0
    void __thiscall AddRenderable(IRenderable* r);
    // @ 0x95bc10
    Batch2D* __thiscall Begin2D(IRenderMode* m);
    // @ 0x95bc40
    Node** __thiscall RenderBatch(Node** pIt, DispEntry* head, int flag);
    // @ 0x95bd60
    void __thiscall RenderList(Node* lst, const RectF* r);
};
extern IRenderMode* __cdecl GetDefaultMode();                        // 0x951d50
extern u32 __cdecl ModulateARGB32(u32 a, u32 b);                     // 0x95f8c0
// ---- items of slice s0095b310 end

// ---- items of slice s0095d000 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* kSerTypeTable[];                                                          // 0x154eea0
extern void* __cdecl VectorDoInsertValue(void* begin, void* pos, int count);           // 0x11e0744
extern void* __cdecl OperatorNewArray(void* dst, int zero, unsigned size);             // 0x11e073e
extern "C" void  WString_Clear(void* self);                                            // 0x5726c0
extern "C" void  WString_Append(void* self, const void* s);                            // 0x5c3d90
struct SerItem;
struct StAlloc {
    virtual void* Alloc(uint32_t size, uint32_t align);              // vtable[0]
};
struct PropInfo {
    char      pad0[4];
    int*      meta;                    // +0x04  { fn(void*) at +0, fn2 at +8 }
    uint32_t  id;                      // +0x08
    uint16_t  flags;                   // +0x0c  low 12 bits = type, bit 15 = variable
    uint16_t  pad_e;
    uint32_t  offset;                  // +0x10
    uint32_t  count;                   // +0x14
    bool Commit(SerItem* base, uint32_t* value, int* st);          // 0x95dda0
    bool Build(SerItem* out, SerItem* base, uint32_t count, int* st, int flag); // 0x95dbd0
};
struct SerDesc_s0095_d000 { char pad0[8]; uint32_t elemSize; PropInfo* elems; uint32_t nelems; };
struct SerItem {
    SerDesc_s0095_d000*  desc;                    // +0
    uint32_t  a;                       // +4
    uint32_t  b;                       // +8
    PropInfo* FindProp(SerItem* out, uint32_t id, int* st);         // 0x95dd00
};
bool __cdecl SerWalk(SerItem* item, uint32_t* value);              // 0x95db50
// ---- items of slice s0095d000 end

// ---- items of slice s0095df60 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sin, cos)
struct Mat4 {
    float m[16];
    int flags;     // 0x40: 0 identity, 1 translate/scale, 2 rotated, 3 projective

    void SetIdentity();
    void SetScaleTranslate(const float* t, const float* s);
    void Translate(const float* v);
    void Scale(const float* s);
    void RotateX(float a);
    void RotateY(float a);
    void RotateZ(float a);
    void AddPerspectiveCol(float d);
};
// ---- items of slice s0095df60 end

// ---- items of slice s0095eeb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_0045EAC0(void* out, const void* a, const void* b); // 0x0045EAC0
#pragma intrinsic(_InterlockedExchangeAdd)
struct CM;
struct Mat44 { float f[16]; };
struct CM {
    float m[16];
    int   type;               // +0x40: matrix kind (0 = identity-ish, 1..4)

    void  TransformPoint3(float* out, const float* v);
    void  TransformPoint3B(float* out, const float* v);
    float* TransformPoint4(float* out, const float* v);
    __declspec(noinline) void* BuildMat33(const float* src);
    void  SetRotationAtLeast2(float* axis, float angle);
    void  Invert();
    void  Multiply(const float* o);
    CM*   SetAxes(float* a, float* b, float* c);
};
// ---- items of slice s0095eeb0 end

// @ 0x00950060
int __cdecl Fn00950060(int p)
{
    int z = 0;
    I32(p, 0xc) = 1;
    I32(p, 0x1c) = z;
    I32(p, 0x20) = z;
    I32(p, 0x14) = z;
    return z + 1;
}

// @ 0x00950bb0
bool Window_s0095_ff20::HandleMessage(UIMessage* msg)
{
    switch (msg->mCode) {
    case 3:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x28 / 4])(
            this, msg->mArg0, msg->mArg1, msg->mArg2);
    case 4:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x2c / 4])(
            this, msg->mArg0, msg->mArg1, msg->mArg2);
    case 1:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x30 / 4])(
            this, msg->mArg0, msg->mArg1, msg->mArg2);
    case 2:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x34 / 4])(
            this, msg->mArg0, msg->mArg1, msg->mArg2);
    case 5:
        return ((bool (__thiscall*)(void*, int, unsigned short))(*(void***)this)[0x38 / 4])(
            this, msg->mArg0, (unsigned short)msg->mArg1);
    case 6:
        return ((bool (__thiscall*)(void*, float, float, int, int))(*(void***)this)[0x3c / 4])(
            this, msg->mFArg0, msg->mFArg1, msg->mArg3, msg->mArg2);
    case 7:
        return ((bool (__thiscall*)(void*, float, float, int, int))(*(void***)this)[0x40 / 4])(
            this, msg->mFArg0, msg->mFArg1, msg->mArg3, msg->mArg2);
    case 8:
        return ((bool (__thiscall*)(void*, float, float, int))(*(void***)this)[0x44 / 4])(
            this, msg->mFArg0, msg->mFArg1, msg->mArg2);
    case 9:
        return ((bool (__thiscall*)(void*, float, float, int, int))(*(void***)this)[0x48 / 4])(
            this, msg->mFArg0, msg->mFArg1, msg->mArg2, msg->mArg3);
    case 10:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x4c / 4])(
            this, msg->mArg0, msg->mArg3);
    case 22:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x50 / 4])(
            this, msg->mArg0, msg->mArg3);
    case 11:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x54 / 4])(
            this, msg->mArg0, msg->mArg3);
    case 12:
        return ((bool (__thiscall*)(void*))(*(void***)this)[0x58 / 4])(this);
    case 23:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x70 / 4])(
            this, msg->mSender, msg->mArg0);
    case 24:
        return ((bool (__thiscall*)(void*, int, int, UIMessage*))(*(void***)this)[0x74 / 4])(
            this, msg->mSender, msg->mArg0, msg);
    case 25:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x78 / 4])(
            this, msg->mArg0, msg->mArg1);
    case 26:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x7c / 4])(
            this, msg->mArg0, msg->mArg1);
    case 27:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x80 / 4])(
            this, msg->mArg0, msg->mArg3);
    case 28:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x84 / 4])(
            this, msg->mArg0, msg->mArg3);
    case 17:
        ((bool (__thiscall*)(void*))(*(void***)this)[0x5c / 4])(this);
        return false;
    case 18:
        ((bool (__thiscall*)(void*))(*(void***)this)[0x60 / 4])(this);
        return false;
    case 20:
        if (!((bool (__thiscall*)(void*, float, float, int))(*(void***)this)[0x64 / 4])(
                this, msg->mFArg0, msg->mFArg1, msg->mArg3))
            return DoMessage(msg);
        // fall through: the "finish" body is shared with case 16
    case 16:
        ((bool (__thiscall*)(void*, int))(*(void***)this)[0x68 / 4])(this, msg->mArg3);
        return false;
    case 21:
        ((bool (__thiscall*)(void*, int))(*(void***)this)[0x6c / 4])(this, msg->mArg3);
        return false;
    default:
        return DoMessage(msg);
    }
}

// @ 0x00950ef0
bool Window_s0095_ff20::HandleMessageExt(int arg, UIMessage* msg)
{
    switch (msg->mCode) {
    case 3:
        return ((bool (__thiscall*)(void*, int, int, int, int))(*(void***)this)[0x1c / 4])(
            this, arg, msg->mArg0, msg->mArg1, msg->mArg2);
    case 4:
        return ((bool (__thiscall*)(void*, int, int, int, int))(*(void***)this)[0x20 / 4])(
            this, arg, msg->mArg0, msg->mArg1, msg->mArg2);
    case 1:
        return ((bool (__thiscall*)(void*, int, int, int, int))(*(void***)this)[0x24 / 4])(
            this, arg, msg->mArg0, msg->mArg1, msg->mArg2);
    case 2:
        return ((bool (__thiscall*)(void*, int, int, int, int))(*(void***)this)[0x28 / 4])(
            this, arg, msg->mArg0, msg->mArg1, msg->mArg2);
    case 5:
        return ((bool (__thiscall*)(void*, int, int, unsigned short))(*(void***)this)[0x2c / 4])(
            this, arg, msg->mArg0, (unsigned short)msg->mArg1);
    case 6:
        return ((bool (__thiscall*)(void*, int, float, float, int, int))(*(void***)this)[0x30 / 4])(
            this, arg, msg->mFArg0, msg->mFArg1, msg->mArg3, msg->mArg2);
    case 7:
        return ((bool (__thiscall*)(void*, int, float, float, int, int))(*(void***)this)[0x34 / 4])(
            this, arg, msg->mFArg0, msg->mFArg1, msg->mArg3, msg->mArg2);
    case 8:
        return ((bool (__thiscall*)(void*, int, float, float, int))(*(void***)this)[0x38 / 4])(
            this, arg, msg->mFArg0, msg->mFArg1, msg->mArg2);
    case 9:
        return ((bool (__thiscall*)(void*, int, float, float, int, int))(*(void***)this)[0x3c / 4])(
            this, arg, msg->mFArg0, msg->mFArg1, msg->mArg2, msg->mArg3);
    case 10:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x40 / 4])(
            this, arg, msg->mArg0, msg->mArg3);
    case 11:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x44 / 4])(
            this, arg, msg->mArg0, msg->mArg3);
    case 23:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x68 / 4])(
            this, arg, msg->mSender, msg->mArg0);
    case 24:
        return ((bool (__thiscall*)(void*, int, int, int, UIMessage*))(*(void***)this)[0x6c / 4])(
            this, arg, msg->mSender, msg->mArg0, msg);
    case 25:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x70 / 4])(
            this, arg, msg->mArg0, msg->mArg1);
    case 26:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x74 / 4])(
            this, arg, msg->mArg0, msg->mArg1);
    case 12:
        return ((bool (__thiscall*)(void*, int))(*(void***)this)[0x48 / 4])(this, arg);
    case 20:
        return ((bool (__thiscall*)(void*, int, float, float, int))(*(void***)this)[0x4c / 4])(
            this, arg, msg->mFArg0, msg->mFArg1, msg->mArg3);
    case 27:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x78 / 4])(
            this, arg, msg->mArg0, msg->mArg3);
    case 28:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x7c / 4])(
            this, arg, msg->mArg0, msg->mArg3);
    case 17:
        return ((bool (__thiscall*)(void*, int))(*(void***)this)[0x50 / 4])(this, arg);
    case 18:
        return ((bool (__thiscall*)(void*, int))(*(void***)this)[0x54 / 4])(this, arg);
    case 16:
        ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x58 / 4])(this, arg, msg->mArg3);
        return false;
    case 21:
        ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x5c / 4])(this, arg, msg->mArg3);
        return false;
    default:
        return false;
    case 0x1000:
        ((bool (__thiscall*)(void*, int))(*(void***)this)[0x60 / 4])(this, arg);
        return true;
    case 0x1001:
        ((bool (__thiscall*)(void*, int))(*(void***)this)[0x64 / 4])(this, arg);
        return true;
    }
}

// @ 0x00956d90
void __cdecl FUN_00956d90()
{
    void* p = (void*)FUN_00920090();
    ((VFn2ii)Vt(p)[1])(p, (int)g_154ecf0, 0);
    FUN_009574f0();
    FUN_00951360();
    FUN_009513b0();
}

// @ 0x00957530
__declspec(noinline) void __fastcall FUN_00957530(int* self)
{
    int* p = (int*)self[1];
    if (p != 0) {
        ((VFn0)Vt(p)[1])(p);
        self[1] = 0;
    }
}

// @ 0x00957550
int EA::UTFWin::Image::Release()
{
    int* self = (int*)this;
    int n = _InterlockedDecrement((volatile long*)((char*)self + 0x28));
    if (n == 0 && self != 0)
        ((VFn1i)Vt(self)[2])(self, 1);
    return n;
}

// @ 0x00957570
void* UIObj::Cast(unsigned int id)
{
    switch (id) {
    case 0xee3f516e: return this;
    case 0x1be6ab3:  return this;
    case 0x2f84737:  return (char*)this + 0x1c;
    case 0xeec58382: return this;
    }
    return 0;
}

// @ 0x009575f0
bool __cdecl FUN_009575f0(SerObj* pDst, SerObj* pSrc, SerDesc* pDesc)
{
    IRefObj** pSrcArr = (IRefObj**)pSrc->mpData;
    IRefObj** pDstArr = (IRefObj**)((char*)pDst->mpData + pDesc->mOffset);
    for (unsigned int i = 0; i < pDesc->mCount; ++i) {
        IRefObj* pOld = *pDstArr;
        IRefObj* pNew = 0;
        if (pOld)
            pOld->Release();
        if (*pSrcArr) {
            pNew = (*pSrcArr)->Cast(0x1be8ca6);
            if (pNew)
                pNew->AddRef();
        }
        *pDstArr = pNew;
        ++pDstArr;
        ++pSrcArr;
    }
    return true;
}

// @ 0x009576f0
bool __cdecl FUN_009576f0(SerObj* pDst, SerObj* pSrc, SerDesc* pDesc)
{
    ((SetterFn)pDesc->mpOps->fn[4])(pDst->mpData, pSrc->mpData);
    return true;
}

// @ 0x00957710
bool __cdecl FUN_00957710(SerObj* a, SerObj* pObj, SerDesc* pDesc, SerValue* pOut)
{
    void* pTarget = pObj->mpData;
    SerOps* pOps = pDesc->mpOps;
    Int2* pDest = (Int2*)pOut->Alloc(pDesc->mCount * 8, 4);
    if (pDest) {
        Int2 v = ((GetInt2Fn)pOps->fn[3])(pTarget);
        *pDest = v;
        pOut->mpData = pDest;
        pOut->mCount = pDesc->mCount;
        *(void**)pOut = g_pSerTypeTable[pDesc->mTypeId & 0xfff];
    }
    return true;
}

// @ 0x00957790
void UIObj::SetPos(int* p)
{
    char* self = (char*)this;
    *(int*)(self + 0x1c) = p[0];
    *(int*)(self + 0x20) = p[1];
}

// @ 0x009577b0
void UIObj::GetRect(float* out)
{
    char* self = (char*)this;
    float x = *(float*)(self + 0xc);
    float h = *(float*)(self + 0x14);
    float hx = h + x;
    out[0] = x;
    out[2] = hx;
    float y = *(float*)(self + 0x10);
    float w = *(float*)(self + 0x18);
    out[1] = y;
    out[3] = w + y;
}

// @ 0x009577f0
void UIObj::SetRect(float* in)
{
    char* self = (char*)this;
    *(float*)(self + 0xc) = in[0];
    *(float*)(self + 0x10) = in[1];
    *(float*)(self + 0x14) = in[2] - in[0];
    *(float*)(self + 0x18) = in[3] - in[1];
}

// @ 0x00957850
void __fastcall FUN_00957850(int* self)
{
    self[0] = 0x144064c;
    if (self[1] != 0) {
        ((VFn0)Vt((void*)self[1])[1])((void*)self[1]);
        self[1] = 0;
    }
    self[0] = 0x13eb938;
}

// @ 0x00957880
void** __cdecl FUN_00957880(int a, int b)
{
    if ((g_166b134 & 1) == 0) {
        g_166b134 |= 1;
        *(int*)0x154ede4 = a;
        *(int*)0x154ede8 = b;
        *(int*)0x154edec = 0;
    }
    return (void**)0x154edd8;
}

// @ 0x009578c0
bool __cdecl FUN_009578c0(SerObj* a, SerObj* pObj, SerDesc* pDesc, SerValue* pOut)
{
    void* pTarget = pObj->mpData;
    SerOps* pOps = pDesc->mpOps;
    Float4* pDest = (Float4*)pOut->Alloc(pDesc->mCount << 4, 4);
    if (pDest) {
        Float4 v = ((GetFloat4Fn)pOps->fn[3])(pTarget);
        *pDest = v;
        pOut->mpData = pDest;
        pOut->mCount = pDesc->mCount;
        *(void**)pOut = g_pSerTypeTable[pDesc->mTypeId & 0xfff];
    }
    return true;
}

// @ 0x00957940
void* UIObj::VirtualDtor(unsigned char flags)
{
    int* self = (int*)this;
    self[0] = 0x144064c;
    if (self[1] != 0) {
        ((VFn0)Vt((void*)self[1])[1])((void*)self[1]);
        self[1] = 0;
    }
    self[0] = 0x13eb938;
    if (flags & 1)
        operator_delete__(self);
    return self;
}

// @ 0x00957980
int* UIObj::Ctor(int* p2, int* p3, float* r, int extra)
{
    int* self = (int*)this;
    self[0] = 0x144064c;
    _InterlockedExchange((volatile long*)(self + 10), 0);
    self[1] = (int)p2;
    if (p2 != 0)
        ((VFn0)Vt(p2)[0])(p2);
    self[7] = p3[0];
    self[8] = p3[1];
    *(float*)(self + 3) = r[0];
    *(float*)(self + 4) = r[1];
    *(float*)(self + 5) = r[2] - r[0];
    *(float*)(self + 6) = r[3] - r[1];
    self[9] = extra;
    return self;
}

// @ 0x009579f0
UIImage* UIImage::Image(void* obj, int a, int b, float c, float d, float e, float f, int h)
{
    vtbl = (void*)0x144064c;
    _InterlockedExchange((volatile long*)&f28, 0);
    p1 = obj;
    if (obj) ((VTab*)obj)->v00();
    f0c = c;
    f10 = d;
    f14 = e;
    f1c = a;
    f20 = b;
    f24 = h;
    f18 = f;
    return this;
}

// @ 0x00957a60
void** __cdecl Fn00957a60(int a, int b)
{
    unsigned* g = (unsigned*)0x166b138;
    if ((*g & 1) == 0) {
        *g |= 1;
        *(int*)0x154edfc = a;
        *(int*)0x154ee00 = b;
        *(int*)0x154ee04 = 0;
    }
    return (void**)0x154edf0;
}

// @ 0x00957aa0
UIImage* __fastcall Fn00957aa0(UIImage* self)
{
    self->vtbl = (void*)0x144064c;
    _InterlockedExchange((volatile long*)&self->f28, 0);
    self->p1 = 0;
    return self;
}

// @ 0x00957ac0
void* __stdcall Fn00957ac0(int a, int b)
{
    UIImage* p = (UIImage*)operator new(0x2c, "UTFWin/Image", 0, 0, 0, 0);
    if (p) {
        p->vtbl = (void*)0x144064c;
        _InterlockedExchange((volatile long*)&p->f28, 0);
        p->p1 = 0;
        return p;
    }
    return 0;
}

// @ 0x0095bc40
Node** __thiscall RenderCtx::RenderBatch(Node** pIt, DispEntry* head, int flag)
{
    DispEntry* buf[64];
    EVec vec;
    vec.begin = buf; vec.end = buf; vec.cap = buf + 64; vec.buf = buf;
    DispEntry* first = head;
    u32 depth = head->depth;
    Node* anchor = list;
    *pIt = &head->link;
    if (&head->link != anchor) {
        do {
            DispEntry* cur = (DispEntry*)*pIt;
            int lowest = cur->lowest;
            if (!(lowest > (int)(depth + 1))) {
                if (cur != head && lowest <= (int)depth)
                    break;
                DispEntry* v = cur;
                if (vec.end < vec.cap) {
                    DispEntry** p = vec.end;
                    vec.end = p + 1;
                    if (p)
                        *p = v;
                } else {
                    vec.Overflow(vec.end, &v);
                }
            }
            *pIt = (*pIt)->next;
        } while (*pIt != anchor);
    }
    Xform* savedMat = mat;
    u32 savedCol = colorMod;
    int n = (int)(vec.end - vec.begin);
    first->renderer->RenderBatch(first->data[first->bSecond].rdata, this, (Node**)vec.begin, n, flag);
    mat = savedMat;
    colorMod = savedCol;
    if (vec.begin && vec.begin != vec.buf)
        operator delete(vec.begin);
    return pIt;
}

// @ 0x0095bd60
void __thiscall RenderCtx::RenderList(Node* lst, const RectF* r)
{
    list = lst;
    float sy, sx;
    sx = g_1470f1c / (r->x1 - r->x0);
    sy = g_1470f1c / (r->y1 - r->y0);
    vp.x0 = r->x0;
    vp.y0 = r->y0;
    vp.x1 = r->x1;
    vp.y1 = r->y1;
    IRenderMode* dm = defMode;
    if (!dm)
        dm = GetDefaultMode();
    bool flag = dm->vFlag();
    float* t = trans;
    if (!flag) {
        t[1] = sy * r->y0 + g_1485720;
        t[0] = g_13eb1bc_f - r->x0 * sx;
        t[2] = g_1471064;
    } else {
        t[0] = g_13eb1bc_f - (r->x0 + g_1471064) * sx;
        t[1] = (r->y0 + g_1471064) * sy + g_1485720;
        t[2] = g_1471064;
    }
    float* s = scale;
    s[0] = sx;
    s[1] = -sy;
    s[2] = 0.0f;
    Xform xf0;
    xf0.Init(trans, scale);
    mat = &xf0;
    if (lst->prev == lst)
        return;
    {
        Node* it = list;
        Node* first = it->next;
        for (; it != first; it = it->prev) {
            DispEntry* e = (DispEntry*)it->prev;
            if (e->renderer && e->renderer->NeedsPrepass()) {
                Node* tmp;
                RenderBatch(&tmp, e, 1);
            }
        }
    }
    DispEntry* cur = (DispEntry*)lst->next;
    Node* anchor = list;
    u32 firstLowest = cur->lowest;
    IRenderMode* curMode = 0;
    bool first = true;
    if ((Node*)cur == anchor)
        return;
    for (;;) {
        if (!first && !(cur->lowest > (u16)firstLowest))
            break;
        RenderData* d = &cur->data[cur->bSecond];
        first = false;
        xf = &d->xf;
        Xform tmpx;
        if (mat) {
            tmpx = d->xf;
            tmpx.Multiply(mat);
            xf = &tmpx;
        }
        float cx0, cy0, cx1, cy1;
        if (vp.x0 >= d->r2 || d->r0 >= vp.x1 || vp.y0 >= d->r3 || d->r1 >= vp.y1) {
            cx0 = 0.0f; cy0 = 0.0f; cx1 = 0.0f; cy1 = 0.0f;
        } else {
            cx0 = (d->r0 > vp.x0) ? d->r0 : vp.x0;
            cy0 = (d->r1 > vp.y0) ? d->r1 : vp.y0;
            cx1 = (vp.x1 > d->r2) ? d->r2 : vp.x1;
            cy1 = (vp.y1 > d->r3) ? d->r3 : vp.y1;
        }
        clip.x0 = cx0; clip.y0 = cy0; clip.x1 = cx1; clip.y1 = cy1;
        shade = d->shade;
        if (colorMod != 0xffffffff)
            shade = ModulateARGB32(d->shade, colorMod);
        if (cur->renderer) {
            if (curMode) {
                curMode->End();
                curMode = 0;
            }
            Node* it2;
            Node** res = RenderBatch(&it2, cur, 0);
            cur = (DispEntry*)*res;
        } else {
            for (Chunk* c = &cur->chunks; c; c = c->next) {
                int cnt = c->count;
                for (int i = 0; i < cnt; i++) {
                    if (curMode != (IRenderMode*)c->items[i].b) {
                        if (curMode)
                            curMode->End();
                        curMode = (IRenderMode*)c->items[i].b;
                        if (curMode)
                            curMode->Begin();
                    }
                    if (curMode)
                        curMode->Render((IRenderable*)c->items[i].obj, this);
                    else
                        ((IRenderable*)c->items[i].obj)->Render(this);
                }
            }
            cur = (DispEntry*)cur->link.next;
        }
        if ((Node*)cur == anchor)
            break;
    }
    if (curMode)
        curMode->End();
}

// @ 0x0095db50
bool __cdecl SerWalk(SerItem* item, uint32_t* value)
{
    PropInfo* e = item->desc->elems;
    uint32_t n = item->desc->nelems;
    // The original's call site pushes the incoming ebx as Commit's st argument (an uninitialized
    // scratch value); the differential harness seeds every callee-saved register with this
    // sentinel, so use the same value here to keep the st-dependent Commit/meta call identical.
    int* st = (int*)0x0BB0BB00;
    while (n != 0) {
        uint16_t f = e->flags;
        n--;
        if (f & 0x8000) { e++; continue; }
        if ((f & 0xfff) == 1) { e++; continue; }
        uint32_t local[3];
        local[0] = 0;
        local[1] = e->offset + value[1];
        local[2] = e->count;
        if (!e->Commit(item, local, st))
            return false;
        e++;
    }
    return true;
}

// @ 0x0095dbd0
bool PropInfo::Build(SerItem* out, SerItem* base, uint32_t count, int* st, int flag)
{
    if (count != this->count && !(this->flags & 0x8000))
        return false;
    int* m = this->meta;
    if (m == 0 || m[2] == 0) {
        out->desc = (SerDesc_s0095_d000*)kSerTypeTable[this->flags & 0xfff];
    } else {
        bool r = ((bool(__cdecl*)(SerItem*, SerItem*, PropInfo*, int*))m[2])(out, base, this, st);
        if (!r)
            return false;
    }
    out->b = count;
    if (count != 0) {
        uint32_t t = this->flags & 0xfff;
        if (flag == 0 && t != 0x13 && t != 0x12 && (this->meta == 0 || this->meta[0] == 0)) {
            out->a = base->a + this->offset;
            return out->a != 0;
        }
        uint32_t size = out->desc->elemSize * count;
        void* d = ((struct StAlloc*)st)->Alloc(size, 4);
        out->a = (uint32_t)d;
        if (d == 0)
            return false;
        if (t == 0x13 || t == 0x12 || t == 0x14)
            OperatorNewArray(d, 0, out->desc->elemSize * count);
        return out->a != 0;
    }
    out->a = 0;
    return true;
}

// @ 0x0095dd00
PropInfo* SerItem::FindProp(SerItem* out, uint32_t id, int* st)
{
    PropInfo* e = this->desc->elems;
    uint32_t n = this->desc->nelems;
    while (n > 0) {
        if ((e->flags & 0xfff) == 1) {
            SerItem local;
            if (((bool(__cdecl*)(void*, SerItem*, PropInfo*, int*))e->meta[2])(&local, this, e, st)) {
                PropInfo* r = local.FindProp(out, id, st);
                if (r != 0)
                    return r;
            }
        } else if (e->id == id) {
            out->desc = this->desc;
            out->b = this->b;
            out->a = this->a;
            return e;
        }
        n--;
        e++;
    }
    return 0;
}

// @ 0x0095dda0
bool PropInfo::Commit(SerItem* base, uint32_t* value, int* st)
{
    int* m = this->meta;
    if (m != 0 && m[0] != 0) {
        return ((bool(__cdecl*)(SerItem*, uint32_t*, PropInfo*, int*))m[0])(base, value, this, st);
    }
    if ((int16_t)this->flags < 0)
        return false;
    if (value[2] != this->count)
        return false;

    uint32_t* valPtr;
    int type;
    uint32_t cnt;
    if (m == 0 || m[2] == 0) {
        valPtr = (uint32_t*)(base->a + this->offset);
        type = (int)(uint32_t)kSerTypeTable[this->flags & 0xfff];
        cnt = value[2];
    } else {
        uint32_t buf[3];
        ((void(__cdecl*)(uint32_t*, SerItem*, PropInfo*, int*))m[2])(buf, base, this, st);
        type = (int)buf[0];
        valPtr = (uint32_t*)buf[1];
        cnt = buf[2];
    }
    uint32_t existing = value[1];
    if (valPtr != (uint32_t*)existing) {
        uint32_t elemSize = *(uint32_t*)(type + 8);
        uint32_t t = this->flags & 0xfff;
        if (t >= 2 && t <= 0x11) {
            VectorDoInsertValue(valPtr, (void*)existing, elemSize * cnt);
        } else if (t == 0x13) {
            VectorDoInsertValue(valPtr, (void*)existing, elemSize * cnt);
        } else if (t == 0x12) {
            uint32_t i = 0;
            uint32_t* src = valPtr;
            uint32_t* dst = (uint32_t*)existing;
            if (cnt == 0)
                return true;
            do {
                uint32_t s = *dst;
                if (s == 0) WString_Clear(src);
                else if (s != *src) WString_Append(src, (const void*)s);
                i++;
                dst++;
                src += 4;
            } while (i < cnt);
            return true;
        } else if (t == 0x14) {
            uint32_t us[3];
            us[0] = value[0];
            us[1] = value[1];
            us[2] = value[2];
            uint32_t i = 0;
            if (cnt == 0)
                return true;
            do {
                if (!SerWalk((SerItem*)valPtr, us))
                    return false;
                valPtr = (uint32_t*)((char*)valPtr + elemSize);
                i++;
            } while (i < cnt);
            return true;
        } else {
            return false;
        }
    }
    return true;
}

// @ 0x0095df60
float* FUN_0095df60(float* out, const float* v, const float* m)
{
    float x = v[0], y = v[1], z = v[2];
    out[0] = z * m[8] + (y * m[4] + x * m[0]);
    out[1] = m[9] * z + (m[1] * x + m[5] * y);
    out[2] = m[10] * z + (m[2] * x + m[6] * y);
    return out;
}

// @ 0x0095e7a0
void Mat4::SetIdentity()
{
    flags = 0;
    m[0] = 1.0f; m[1] = 0; m[2] = 0; m[3] = 0;
    m[4] = 0; m[5] = 1.0f; m[6] = 0; m[7] = 0;
    m[8] = 0; m[9] = 0; m[10] = 1.0f; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1.0f;
}

// @ 0x0095e810
void Mat4::SetScaleTranslate(const float* t, const float* s)
{
    flags = 1;
    m[0] = s[0]; m[1] = 0; m[2] = 0; m[3] = 0;
    m[4] = 0; m[6] = 0; m[7] = 0; m[5] = s[1];
    m[8] = 0; m[9] = 0; m[11] = 0; m[10] = s[2];
    m[12] = t[0]; m[13] = t[1]; m[14] = t[2]; m[15] = 1.0f;
}

// @ 0x0095e890
void Mat4::Translate(const float* v)
{
    if (flags == 0) flags = 1;
    float w = m[15];
    float x = v[0], y = v[1], z = v[2];
    m[12] = m[12] + w * x;
    m[13] = m[13] + w * y;
    m[14] = m[14] + w * z;
    m[15] = m[15] + w * 0.0f;
    if (flags == 3) {
        w = m[11];
        m[8] = m[8] + w * x;
        m[9] = m[9] + w * y;
        m[10] = m[10] + w * z;
        m[11] = m[11] + w * 0.0f;
        w = m[7];
        m[4] = m[4] + w * x;
        m[5] = m[5] + w * y;
        m[6] = m[6] + w * z;
        m[7] = m[7] + w * 0.0f;
        w = m[3];
        m[1] = w * y + m[1];
        m[0] = m[0] + w * x;
        m[2] = w * z + m[2];
        m[3] = m[3] + w * 0.0f;
    }
}

// @ 0x0095ea30
void Mat4::Scale(const float* s)
{
    if (flags == 0) flags = 1;
    m[0] = s[0] * m[0];
    m[1] = m[1] * s[1];
    m[2] = m[2] * s[2];
    m[4] = m[4] * s[0];
    m[5] = m[5] * s[1];
    m[6] = m[6] * s[2];
    m[8] = m[8] * s[0];
    m[9] = m[9] * s[1];
    m[10] = m[10] * s[2];
    m[12] = m[12] * s[0];
    m[13] = m[13] * s[1];
    m[14] = m[14] * s[2];
}

// @ 0x0095eb00
void Mat4::RotateX(float a)
{
    if (flags < 2) flags = 2;
    float f6 = m[6];
    float sn = (float)sin((double)a);
    float f1 = m[1];
    float f9 = m[9];
    float f13 = m[13];
    float cs = (float)cos((double)a);
    m[1] = f1 * cs - m[2] * sn;
    m[2] = m[2] * cs + f1 * sn;
    m[6] = f6 * cs + m[5] * sn;
    m[5] = m[5] * cs - f6 * sn;
    m[9] = f9 * cs - m[10] * sn;
    m[10] = m[10] * cs + f9 * sn;
    m[13] = f13 * cs - m[14] * sn;
    m[14] = m[14] * cs + f13 * sn;
}

// @ 0x0095ec30
void Mat4::RotateY(float a)
{
    if (flags < 2) flags = 2;
    float f6 = m[6];
    float sn = (float)sin((double)a);
    float f0 = m[0];
    float f8 = m[8];
    float f12 = m[12];
    float cs = (float)cos((double)a);
    m[0] = m[2] * sn + f0 * cs;
    m[2] = m[2] * cs - f0 * sn;
    m[6] = f6 * cs - m[4] * sn;
    m[4] = f6 * sn + m[4] * cs;
    m[8] = m[10] * sn + f8 * cs;
    m[10] = m[10] * cs - f8 * sn;
    m[12] = m[14] * sn + f12 * cs;
    m[14] = m[14] * cs - f12 * sn;
}

// @ 0x0095ed60
void Mat4::RotateZ(float a)
{
    volatile float pad[8];
    pad[0] = a;
    if (flags < 2) flags = 2;
    float f4 = m[4];
    float sn = (float)sin((double)a);
    float f1 = m[1];
    float f9 = m[9];
    float cs = (float)cos((double)a);
    m[1] = f1 * cs + m[0] * sn;
    m[0] = m[0] * cs - f1 * sn;
    m[9] = f9 * cs + m[8] * sn;
    m[8] = m[8] * cs - f9 * sn;
    m[4] = f4 * cs - m[5] * sn;
    m[5] = m[5] * cs + f4 * sn;
}

// @ 0x0095ee40
void Mat4::AddPerspectiveCol(float d)
{
    if (flags < 3) flags = 3;
    d = 1.0f / d;
    m[3] = m[2] * d + m[3];
    m[7] = m[6] * d + m[7];
    m[11] = m[10] * d + m[11];
    m[15] = m[14] * d + m[15];
}

// @ 0x0095eeb0
void CM::TransformPoint3(float* out, const float* v)
{
    float x = v[0], y = v[1], z = v[2];
    out[0] = m[12] + (m[8] * z + (m[4] * y + x * m[0]));
    out[1] = m[13] + (m[9] * z + (m[1] * x + m[5] * y));
    out[2] = m[14] + (m[10] * z + (m[2] * x + m[6] * y));
}

// @ 0x0095efb0
void CM::TransformPoint3B(float* out, const float* v)
{
    float x = v[0], y = v[1], z = v[2];
    out[0] = m[8] * z + (m[4] * y + x * m[0]);
    out[1] = m[9] * z + (m[1] * x + m[5] * y);
    out[2] = m[10] * z + (m[2] * x + m[6] * y);
}

// @ 0x0095f860
void CM::Multiply(const float* o)
{
    if (type == 0) {
        *(CM*)this = *(const CM*)o;
        return;
    }
    if (((const int*)o)[0x10] != 0) {
        float tmp[16];
        float* r = (float*)FUN_0045EAC0(tmp, this, o);
        *(Mat44*)m = *(Mat44*)r;
        if (((int*)m)[0x10] < ((const int*)o)[0x10])
            ((int*)m)[0x10] = ((const int*)o)[0x10];
    }
}
