// src/game/UTFSpore_Win32/Render.cpp -- migrated from slice(s) s0095b310 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Render.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWin/Renderable2DBuilder.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/UTFWin/IRenderable.h"
#include "EA/UTFWin/IRenderer.h"
#include "EA/Thread/Mutex.h"
#include "EA/Text/Typesetter.h"
#include "EA/UTFWin/Transform.h"

// ---- items of slice s0095b310 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
extern Chunk* __cdecl AllocRenderableListChunk();                    // 0x956ed0
// ---- items of slice s0095b310 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Chunk* __cdecl AllocRenderableListChunk();                    // 0x956ed0

// @ 0x0095bb20
void __thiscall RenderCtx::End2D()
{
    IRenderable* r = batch.Take();
    if (r) {
        Chunk* c = chunks;
        while (c->next)
            c = c->next;
        if (c->count == 5) {
            Chunk* n = AllocRenderableListChunk();
            c->next = n;
            c = n;
        }
        int i = c->count;
        c->count = i + 1;
        r->AddRef();
        c->items[i].obj = (IRel*)r;
        c->items[i].b = (u32)mode;
    }
}

// @ 0x0095bbc0
void __thiscall RenderCtx::AddRenderable(IRenderable* r)
{
    End2D();
    Chunk* c = chunks;
    while (c->next)
        c = c->next;
    if (c->count == 5) {
        Chunk* n = AllocRenderableListChunk();
        c->next = n;
        c = n;
    }
    int i = c->count;
    c->count = i + 1;
    r->AddRef();
    c->items[i].obj = (IRel*)r;
    c->items[i].b = 0;
}

// @ 0x0095bc10
Batch2D* __thiscall RenderCtx::Begin2D(IRenderMode* m)
{
    if (!m)
        m = defMode;
    if (m != mode) {
        End2D();
        mode = m;
    }
    return &batch;
}
