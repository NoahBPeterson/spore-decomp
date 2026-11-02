// src/game/UTFSpore_Win32/jdmarker.cpp -- migrated from slice(s) s0085ad60, s008544e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/jdmarker.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s008544e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cTerrainExport;
struct cJob {
    void** mVtbl;                    // +0x00
    int    m04;
    int    m08;
    int    m0C;
    int    m10;
    int    m14;                      // error code
    int    m18;                      // error arg0
    int    m1C;                      // error arg1
    int    m20;                      // error arg2
    void   Error() { ((void(__thiscall*)(cJob*))mVtbl[0])(this); }
};
struct cSlot {
    void* pfn0;                      // +0x00 = 0x00854b60
    void* pfn4;                      // +0x04 = 0x00854d10
    void* pfn8;                      // +0x08 = 0x00854d40
    int   m0C;                       // +0x0c
    int   m10;                       // +0x10
    int   m14;                       // +0x14  state
    int   m18;                       // +0x18  progress
    int   m1C;                       // +0x1c  total
    int   m20;                       // +0x20  extra counter
};
struct cLevel {
    int  m00;
    int  m04;
    int  m08;
    int  m0C;
    int  m10;
    int  m14;
    int  m18;
    int  m1C;
    int  m20;
    int  m24;
    int  m28;
    int  m2C;
    int  m30;
    int  m34;
    int  m38;
    int  m3C;
    int  m40;
    int  m44;
    int  m48;
};
struct cTerrainExport
{
    cJob*  mJob;                     // +0x000  (vtable-bearing error reporter)
    void** mAllocVtbl;               // +0x004  allocator vtable: slots called as Ty(this,...)
    void*  m008;                     // +0x008  optional progress sink
    int    m00C;                     // +0x00c
    int    m010;                     // +0x010
    int    m014;                     // +0x014
    int    m018;                     // +0x018
    int    m01C;                     // +0x01c
    int    m020;                     // +0x020
    int    m024;                     // +0x024
    int    m028;                     // +0x028
    int    m02C;                     // +0x02c
    int    m030;                     // +0x030
    int    m034;                     // +0x034  level count
    int    m038;                     // +0x038
    int    m03C;                     // +0x03c  base pointer for level stride
    int    m040;                     // +0x040
    int    m044[23];                 // +0x044 .. +0x09f
    int    m0A0;                     // +0x0a0  job count
    int*   m0A4;                     // +0x0a4  per-job descriptor array (0x24 bytes each)
    int    m0A8;                     // +0x0a8
    int    m0AC;                     // +0x0ac
    int    m0B0;                     // +0x0b0
    int    m0B4;                     // +0x0b4
    int    m0B8;                     // +0x0b8
    int    m0BC;                     // +0x0bc
    int    m0C0;                     // +0x0c0
    int    m0C4;                     // +0x0c4
    int    m0C8;                     // +0x0c8
    int    m0CC;                     // +0x0cc
    int    m0D0;                     // +0x0d0
    int    m0D4;                     // +0x0d4
    int    m0D8;                     // +0x0d8
    int    m0DC;                     // +0x0dc
    int    m0E0;                     // +0x0e0
    int    m0E4;                     // +0x0e4
    int    m0E8;                     // +0x0e8
    int    m0EC;                     // +0x0ec  level count in use
    cLevel* m0F0[4];                 // +0x0f0  per-level pointers (max 4)
    int    m100;                     // +0x100
    int    m104;                     // +0x104
    int    m108;                     // +0x108  running count
    void*  m10C[10];                 // +0x10c  filled level table (+0x10c..+0x133)
    int    m134;                     // +0x134
    int    m138;                     // +0x138
    int    m13C;                     // +0x13c
    int    m140;                     // +0x140
    cSlot* m144;                     // +0x144  slot block (vtbl-carrier)
    void*  m148;                     // +0x148
    int    m14C;                     // +0x14c
    int    m150;                     // +0x150
    void*  m154;                     // +0x154  fn-pointer table (slots at +8/+0xc)
    void*  m158;                     // +0x158
    void*  m15C;                     // +0x15c
    void*  m160;                     // +0x160
    void*  m164;                     // +0x164  fn-pointer table (slot at +8)

    // __thiscall vtable members of the export object
    void FUN_008544e0();
    void FUN_008548a0();
    void FUN_00854990();
};
__declspec(noinline) void* FUN_00854ed0(cTerrainExport* p);
// ---- items of slice s008544e0 end

// ---- items of slice s0085ad60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Reader;
typedef void (*WriteFn)(Reader*, void*, uint32_t*, uint32_t, uint32_t, uint32_t, uint32_t);
struct Ctx
{
    void    (*error)(Reader*);          // +0x00
    void    (*report)(Reader*, int32_t); // +0x04
    uint8_t   pad08[0x0c];
    int32_t   code;                     // +0x14
    int32_t   a18, a1c, a20, a24;       // +0x18
};
struct Stream
{
    uint8_t*  p;                        // +0x00
    int32_t   n;                        // +0x04
    uint8_t   pad08[4];
    int32_t (*refill)(Reader*);         // +0x0c
    void    (*skip)(Reader*, int32_t);  // +0x10
};
struct State                               // 0x50 bytes
{
    void*     step;                     // +0x00
    void*     work;                     // +0x04
    void*     buf[8];                   // +0x08
    uint8_t   pad28[8];
    int32_t   started;                  // +0x30
    uint32_t  pos;                      // +0x34
    void*     slot[2];                  // +0x38
    int32_t   index;                    // +0x40
    int32_t   phase;                    // +0x44
    uint32_t  limit;                    // +0x48
    int32_t   count;                    // +0x4c
};
struct Surf                                // 0x54-byte surface record
{
    uint32_t  id;                       // +0x00
    uint32_t  index;                    // +0x04
    uint32_t  x;                        // +0x08
    uint32_t  y;                        // +0x0c
    uint32_t  w;                        // +0x10
    uint32_t  h;                        // +0x14
    uint32_t  pad18[3];                 // +0x18
    int32_t   row;                      // +0x24
    uint32_t  span;                     // +0x28
    uint32_t  pad2c[2];                 // +0x2c
    uint32_t  level;                    // +0x34
};
struct Reader
{
    Ctx*      ctx;                      // +0x00
    struct Alloc* alloc;                // +0x04
    uint8_t   pad08[0x0c];
    Stream*   stream;                   // +0x14
    uint8_t   pad18[8];
    int32_t   count;                    // +0x20
    int32_t   counter;                  // +0x24
    uint8_t   pad28[0xac];
    uint8_t   pad_d4[4];                // +0xd4
    Surf*     surfs;                    // +0xd8
    uint8_t   padext[0x460];            // +0xdc
    int32_t   size;                     // +0x53c
    int32_t   limit;                    // +0x540
    uint8_t   pad544[0x5c];             // +0x544
    int32_t   stateCode;                // +0x5a0
    uint8_t   pad5a4[4];
    State*    state;                    // +0x5a8
    struct OpenIface* open;             // +0x5ac
    struct WriteIface* write;           // +0x5b0
    uint8_t   pad5b4[4];
    struct Header* header;              // +0x5b8
    uint8_t   pad5bc[8];
    struct PrePass* prepass;            // +0x5c4
};
struct Alloc
{
    void*   (*make)(Reader*, int32_t, uint32_t);              // +0x00
    void*   (*make1)(Reader*, int32_t, uint32_t);             // +0x04
    void*   (*alloc)(Reader*, int32_t, uint32_t, uint32_t);   // +0x08
};
struct OpenIface
{
    uint8_t   pad00[0x0c];
    int32_t (*open)(Reader*, void*);    // +0x0c
};
struct WriteIface
{
    uint8_t   pad00[4];
    WriteFn   write;                    // +0x04
};
struct PrePass
{
    uint8_t   pad00[8];
    int32_t   flag;                     // +0x08
};
struct Header
{
    uint8_t   pad00[0x50];
    int32_t   state;                    // +0x50
};
// ---- items of slice s0085ad60 end

// @ 0x00854ed0
__declspec(noinline) void* FUN_00854ed0(cTerrainExport* p)
{
    void** vt = (void**)p->mAllocVtbl;
    void* fn = vt[0];
    void* r = ((void*(__cdecl*)(cTerrainExport*, int, int))fn)(p, 0, 0x84);
    *(int*)((char*)r + 0x80) = 0;
    return r;
}

// @ 0x0085b0b0
uint32_t FUN_0085b0b0(Reader* o)
{
    o->ctx->code = 0x65;
    o->ctx->report(o, 1);
    if (o->header->state != 0)
    {
        o->ctx->code = 0x3c;
        o->ctx->error(o);
    }
    uint8_t* p = (uint8_t*)o + 0xf4;
    int32_t  k = 0x10;
    do
    {
        p[-0x10] = 0;
        p[0]     = 1;
        p[0x10]  = 5;
        ++p;
    } while (--k != 0);
    *(int32_t*)((uint8_t*)o + 0x114) = 0;
    *(int32_t*)((uint8_t*)o + 0x024) = 0;
    *(int32_t*)((uint8_t*)o + 0x12c) = 0;
    *(int32_t*)((uint8_t*)o + 0x118) = 0;
    *(uint8_t*)((uint8_t*)o + 0x11c) = 0;
    *(int32_t*)((uint8_t*)o + 0x124) = 0;
    *(uint8_t*)((uint8_t*)o + 0x128) = 0;
    *(uint16_t*)((uint8_t*)o + 0x11e) = 1;
    *(uint16_t*)((uint8_t*)o + 0x120) = 1;
    o->header->state = 1;
    return 1;
}

// @ 0x0085b150
int32_t FUN_0085b150(Reader* o, int32_t argEAX, int32_t argECX)
{
    Stream* st = o->stream;
    uint8_t* p = st->p;
    int32_t  n = st->n;

    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        p = st->p;
        n = st->n;
    }
    uint8_t b1 = *p++;
    --n;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        p = st->p;
        n = st->n;
    }
    uint8_t b2 = *p++;
    --n;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        p = st->p;
        n = st->n;
    }
    *(int32_t*)((uint8_t*)o + 0xd4) = (int32_t)*p++;
    --n;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        p = st->p;
        n = st->n;
    }
    *(int32_t*)((uint8_t*)o + 0x1c) = (int32_t)*p++ << 8;
    --n;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        p = st->p;
        n = st->n;
    }
    *(int32_t*)((uint8_t*)o + 0x1c) += (int32_t)*p++;
    --n;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        p = st->p;
        n = st->n;
    }
    *(int32_t*)((uint8_t*)o + 0x18) = (int32_t)*p++ << 8;
    --n;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        p = st->p;
        n = st->n;
    }
    *(int32_t*)((uint8_t*)o + 0x18) += (int32_t)*p++;
    --n;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        p = st->p;
        n = st->n;
    }
    int32_t cnt = (int32_t)*p++;
    --n;

    Ctx* c = o->ctx;
    *(int32_t*)((uint8_t*)o + 0x20)              = cnt;
    *(int32_t*)((uint8_t*)c + 0x18)              = *(int32_t*)((uint8_t*)o + 0x5a0);
    *(int32_t*)((uint8_t*)c + 0x1c)              = *(int32_t*)((uint8_t*)o + 0x18);
    *(int32_t*)((uint8_t*)c + 0x20)              = *(int32_t*)((uint8_t*)o + 0x1c);
    *(int32_t*)((uint8_t*)c + 0x24)              = *(int32_t*)((uint8_t*)o + 0x20);
    c->code = 99;
    c->report(o, 1);

    if (*(int32_t*)((uint8_t*)o->header + 0x54) != 0)
    {
        o->ctx->code = 0x39;
        o->ctx->error(o);
    }
    if (*(int32_t*)((uint8_t*)o + 0x1c) == 0 || *(int32_t*)((uint8_t*)o + 0x18) == 0 || cnt < 1)
    {
        o->ctx->code = 0x1f;
        o->ctx->error(o);
    }
    if ((uint32_t)b1 * 0x100 + (uint32_t)b2 - 8 != (uint32_t)cnt * 3)
    {
        o->ctx->code = 9;
        o->ctx->error(o);
    }
    if (o->surfs == 0)
        o->surfs = (Surf*)o->alloc->make(o, 1, (uint32_t)(cnt * 0x54));

    uint8_t* rec = (uint8_t*)o->surfs;
    for (int32_t i = 0; i < cnt; ++i)
    {
        *(int32_t*)(rec + 4) = i;
        if (n == 0)
        {
            if (st->refill(o) == 0)
                return 0;
            p = st->p;
            n = st->n;
        }
        *(int32_t*)rec = (int32_t)*p++;
        --n;
        if (n == 0)
        {
            if (st->refill(o) == 0)
                return 0;
            p = st->p;
            n = st->n;
        }
        uint8_t v = *p++;
        --n;
        *(int32_t*)(rec + 8)  = (int32_t)(v >> 4);
        *(int32_t*)(rec + 12) = (int32_t)(v & 0xf);
        if (n == 0)
        {
            if (st->refill(o) == 0)
                return 0;
            p = st->p;
            n = st->n;
        }
        *(int32_t*)(rec + 16) = (int32_t)*p++;
        --n;
        Ctx* cc = o->ctx;
        cc->a18 = *(int32_t*)rec;
        cc->a1c = *(int32_t*)(rec + 8);
        cc->a20 = *(int32_t*)(rec + 12);
        cc->a24 = *(int32_t*)(rec + 16);
        cc->code = 100;
        cc->report(o, 1);
        rec += 0x54;
    }
    *(int32_t*)((uint8_t*)o->header + 0x54) = 1;
    st->p = p;
    st->n = n;
    return 1;
}

// @ 0x0085b460
int32_t FUN_0085b460(Reader* o)
{
    Stream* st = o->stream;
    uint8_t* p = st->p;
    int32_t  n = st->n;

    if (*(int32_t*)((uint8_t*)o->header + 0x54) == 0)
    {
        o->ctx->code = 0x3d;
        o->ctx->error(o);
    }
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        n = st->n;
        p = st->p;
    }
    uint8_t u1 = *p++;
    --n;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        n = st->n;
        p = st->p;
    }
    uint8_t u2 = *p++;
    --n;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        n = st->n;
        p = st->p;
    }
    uint32_t cnt = (uint32_t)*p++;
    --n;
    if (((uint32_t)u1 << 8 | (uint32_t)u2) != cnt * 2 + 6 || cnt == 0 || cnt > 4)
    {
        o->ctx->code = 9;
        o->ctx->error(o);
    }
    o->ctx->code = 0x66;
    o->ctx->a18  = (int32_t)cnt;
    o->ctx->report(o, 1);
    *(int32_t*)((uint8_t*)o + 0x548) = (int32_t)cnt;

    uint8_t** slots = (uint8_t**)((uint8_t*)o + 0x54c);
    for (uint32_t i = 0; i < cnt; ++i)
    {
        if (n == 0)
        {
            if (st->refill(o) == 0)
                return 0;
            n = st->n;
            p = st->p;
        }
        uint32_t id = (uint32_t)*p++;
        --n;
        if (n == 0)
        {
            if (st->refill(o) == 0)
                return 0;
            n = st->n;
            p = st->p;
        }
        uint8_t v = *p++;
        --n;
        uint8_t* rec = (uint8_t*)o->surfs;
        int32_t  j   = 0;
        if (o->count > 0)
        {
            do
            {
                if (id == *(uint32_t*)rec)
                    goto found;
                ++j;
                rec += 0x54;
            } while (j < o->count);
        }
        o->ctx->code = 5;
        o->ctx->a18  = (int32_t)id;
        o->ctx->error(o);
    found:
        *slots = rec;
        *(uint32_t*)(rec + 0x14) = (uint32_t)(v >> 4);
        *(uint32_t*)(rec + 0x18) = (uint32_t)(v & 0xf);
        Ctx* c = o->ctx;
        c->a18 = (int32_t)id;
        c->a1c = *(uint32_t*)(rec + 0x14);
        c->a20 = *(uint32_t*)(rec + 0x18);
        c->code = 0x67;
        c->report(o, 1);
        ++slots;
    }

    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        n = st->n;
        p = st->p;
    }
    int32_t v1 = (int32_t)*p++;
    --n;
    *(int32_t*)((uint8_t*)o + 0x590) = v1;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        n = st->n;
        p = st->p;
    }
    int32_t v2 = (int32_t)*p++;
    --n;
    *(int32_t*)((uint8_t*)o + 0x594) = v2;
    if (n == 0)
    {
        if (st->refill(o) == 0)
            return 0;
        n = st->n;
        p = st->p;
    }
    uint8_t v3 = *p++;
    *(int32_t*)((uint8_t*)o + 0x598) = (int32_t)(v3 >> 4);
    *(int32_t*)((uint8_t*)o + 0x59c) = (int32_t)(v3 & 0xf);
    Ctx* c = o->ctx;
    c->a18 = *(int32_t*)((uint8_t*)o + 0x590);
    c->a1c = *(int32_t*)((uint8_t*)o + 0x594);
    c->a20 = *(int32_t*)((uint8_t*)o + 0x598);
    c->a24 = *(int32_t*)((uint8_t*)o + 0x59c);
    c->code = 0x68;
    c->report(o, 1);
    *(int32_t*)((uint8_t*)o->header + 0x58) = 0;
    ++*(int32_t*)((uint8_t*)o + 0x90);
    st->n = n - 1;
    st->p = p + 1;
    return 1;
}
