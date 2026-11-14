// src/game/UTFSpore_Win32/Render.cpp

#include "game/types.h"

typedef uint8_t u8;
typedef uint32_t u32;
struct Node { Node* next; Node* prev; };

struct IRel { virtual void r0(); virtual void Release(); };   // vtbl+4
// A Chunk holds at most kChunkCapacity items before another one is allocated.
const int kChunkCapacity = 5;
struct ChunkItem { IRel* obj; u32 b; };
struct Chunk { Chunk* next; int count; ChunkItem items[kChunkCapacity]; };
struct RectF { float x0, y0, x1, y1; };
struct Xform { float m[17]; };                                  // 0x44 bytes (Matrix43)
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

    // @ 0x95bb20
    void __thiscall End2D();
    // @ 0x95bbc0
    void __thiscall AddRenderable(IRenderable* r);
    // @ 0x95bc10
    Batch2D* __thiscall Begin2D(IRenderMode* m);
};
extern Chunk* __cdecl AllocRenderableListChunk();                    // 0x956ed0

// @ 0x0095bb20
void __thiscall RenderCtx::End2D()
{
    IRenderable* r = batch.Take();
    if (r) {
        Chunk* c = chunks;
        while (c->next)
            c = c->next;
        if (c->count == kChunkCapacity) {
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
    if (c->count == kChunkCapacity) {
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
