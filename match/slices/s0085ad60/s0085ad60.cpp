// slice s0085ad60 -- chunked surface reader: the state machine that opens a
// surface, streams its pixels and the palette / colour-table records.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// Recovered model
// ---------------
//  * Reader (the big object): +0x00 error context (fn at +0, report fn at +4,
//    code at +0x14, message words at +0x18..+0x24), +0x04 an interface whose
//    +0x08 slot allocates, +0x14 the byte stream, +0x20 surface count,
//    +0x24 a counter, +0xd8 an array of 0x54-byte surface records,
//    +0x53c the file size, +0x540 a surface limit, +0x5a8 the streaming state,
//    +0x5ac the open interface (+0x0c), +0x5b0 the write interface (+0x04),
//    +0x5b8 a header object, +0x5c4 a pre-pass object (+0x08).
//  * State (0x50 bytes): +0x00 step fn, +0x04 work fn, +0x08 buffer pointers,
//    +0x30 started, +0x34 position, +0x38 two surface slots, +0x40 slot index,
//    +0x44 phase, +0x48 limit, +0x4c surface counter.
//  * Stream (0x14 bytes): +0x00 cursor, +0x04 remaining, +0x0c refill fn,
//    +0x10 skip fn.
#include "types.h"

struct Reader;

typedef int  (*OpenFn)(Reader*, void*);
typedef void (*WriteFn)(Reader*, void*, uint32_t*, uint32_t, uint32_t, uint32_t, uint32_t);
typedef void (*RefillFn)(Reader*);
typedef void (*SkipFn)(Reader*, int32_t);

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

void FUN_0085aaa0(Reader* o);           // 0x0085aaa0
void FUN_0085acc0(Reader* o);           // 0x0085acc0
void FUN_0085abe0(Reader* o);           // 0x0085abe0
void FUN_0085a9f0();                    // 0x0085a9f0

// surface field pair helpers: records are addressed by raw offsets in places
static inline uint8_t* Rec(Reader* o, int32_t i)
{
    return (uint8_t*)o->surfs + i * 0x54;
}

// ---------------------------------------------------------------------------
// 0x0085ad60 -- stream one surface chunk
// ---------------------------------------------------------------------------
// @ 0x0085ad60
void FUN_0085ad60(Reader* o, uint32_t a2, uint32_t a3, uint32_t a4)
{
    State* s = o->state;
    if (s->started == 0)
    {
        if (o->open->open(o, (uint8_t*)s + 8) == 0)
            return;
        s->started = 1;
    }
    uint32_t n = (uint32_t)o->size;
    o->write->write(o, (uint8_t*)s + 8, &s->pos, n, a2, (uint32_t)a3, a4);
    if (s->pos >= n)
    {
        s->started = 0;
        s->pos     = 0;
    }
}

// ---------------------------------------------------------------------------
// 0x0085ade0 -- two-slot surface streamer with a three-phase state machine
// ---------------------------------------------------------------------------
// @ 0x0085ade0
void FUN_0085ade0(Reader* o, uint32_t a2, uint32_t* a3, uint32_t a4)
{
    State* s = o->state;
    if (s->started == 0)
    {
        OpenFn open = o->open->open;
        if (open(o, s->slot[s->index]) == 0)
            return;
        ++s->count;
        s->started = 1;
    }
    switch (s->phase)
    {
    case 0:
        break;
    case 1:
        goto send;
    case 2:
    {
        o->write->write(o, s->slot[s->index], &s->pos, s->limit, a2, (uint32_t)a3, a4);
        if (s->pos < s->limit)
            return;
        s->phase = 0;
        if (*a3 >= a4)
            return;
        break;
    }
    default:
        return;
    }

    s->pos   = 0;
    s->limit = (uint32_t)(o->size - 1);
    if (s->count == o->limit)
        FUN_0085acc0(o);
    s->phase = 1;

send:
    o->write->write(o, s->slot[s->index], &s->pos, s->limit, a2, (uint32_t)a3, a4);
    if (s->pos < s->limit)
        return;
    if (s->count == 1)
        FUN_0085abe0(o);
    s->index   ^= 1;
    s->started = 0;
    s->pos     = (uint32_t)(o->size + 1);
    s->limit   = (uint32_t)(o->size + 2);
    s->phase   = 2;
}

// ---------------------------------------------------------------------------
// 0x0085af20 -- flush an empty chunk through the writer
// ---------------------------------------------------------------------------
// @ 0x0085af20
void FUN_0085af20(Reader* o, uint32_t a2, uint32_t a3, uint32_t a4)
{
    WriteFn w = o->write->write;
    w(o, 0, 0, 0, a2, (uint32_t)a3, a4);
}

// ---------------------------------------------------------------------------
// 0x0085af50 -- pick the chunking strategy for the requested mode
// ---------------------------------------------------------------------------
// @ 0x0085af50
void FUN_0085af50(Reader* o, int32_t mode)
{
    State* s = o->state;
    switch (mode)
    {
    case 0:
        if (o->prepass->flag != 0)
        {
            s->work = (void*)FUN_0085ade0;
            FUN_0085aaa0(o);
            s->index   = 0;
            s->phase   = 0;
            s->count   = 0;
            s->pos     = 0;
            s->started = 0;
            return;
        }
        s->pos     = 0;
        s->started = 0;
        s->work    = (void*)FUN_0085ad60;
        return;
    case 2:
        s->work = (void*)FUN_0085af20;
        return;
    default:
        o->ctx->code = 4;
        o->ctx->error(o);
        return;
    }
}

// ---------------------------------------------------------------------------
// 0x0085afd0 -- allocate the state block and one buffer per surface
// ---------------------------------------------------------------------------
// @ 0x0085afd0
void FUN_0085afd0(Reader* o, int32_t a2)
{
    State* s = (State*)o->alloc->make(o, 1, 0x50);
    o->state = s;
    s->step  = (void*)FUN_0085af50;
    if (a2 != 0)
    {
        o->ctx->code = 4;
        o->ctx->error(o);
    }
    int32_t extra;
    if (o->prepass->flag == 0)
        extra = o->size;
    else
    {
        if (o->size < 2)
        {
            o->ctx->code = 0x2e;
            o->ctx->error(o);
        }
        FUN_0085a9f0();
        extra = o->size + 2;
    }
    if (o->count > 0)
    {
        int32_t*  r = (int32_t*)((uint8_t*)o->surfs + 0x24);
        uint8_t** b = (uint8_t**)((uint8_t*)s + 8);
        for (int32_t i = 0; i < o->count; ++i)
        {
            *b = (uint8_t*)o->alloc->alloc(o, 1,
                                           (uint32_t)(r[-2] * r[0]),
                                           (uint32_t)((r[-6] * r[0]) / o->size * extra));
            ++b;
            r += 0x15;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x0085b0b0 -- reset the decoder tables (header accepted)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x0085b150 -- read the palette header and its colour entries
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x0085b460 -- read the colour table and resolve each entry against it
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x0085b9e0 -- Adobe (Photoshop) resource signature block
// ---------------------------------------------------------------------------
// @ 0x0085b9e0
int32_t FUN_0085b9e0(Reader* o)
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
    int32_t len = (int32_t)((uint32_t)b1 << 8 | (uint32_t)b2) - 2;

    if (len < 0xc)
    {
        o->ctx->code = 0x4d;
        o->ctx->a18  = len;
        o->ctx->report(o, 1);
    }
    else
    {
        uint8_t sig[12];
        for (int32_t i = 0; i < 12; ++i)
        {
            if (n == 0)
            {
                if (st->refill(o) == 0)
                    return 0;
                p = st->p;
                n = st->n;
            }
            sig[i] = *p++;
            --n;
        }
        int32_t rest = len - 0xc;
        if (sig[0] == 'A' && sig[1] == 'd' && sig[2] == 'o' && sig[3] == 'b' && sig[4] == 'e')
        {
            Ctx* c = o->ctx;
            c->a18 = (int32_t)((uint32_t)sig[5] << 8 | (uint32_t)sig[6]);
            c->a1c = (int32_t)((uint32_t)sig[7] << 8 | (uint32_t)sig[8]);
            c->a20 = (int32_t)((uint32_t)sig[9] << 8 | (uint32_t)sig[10]);
            c->a24 = (int32_t)sig[11];
            c->code = 0x4b;
            c->report(o, 1);
            *(int32_t*)((uint8_t*)o + 0x124) = 1;
            *(uint8_t*)((uint8_t*)o + 0x128) = sig[11];
        }
        else
        {
            o->ctx->code = 0x4d;
            o->ctx->a18  = len;
            o->ctx->report(o, 1);
        }
        len = rest;
    }
    st->p = p;
    st->n = n;
    if (len > 0)
        st->skip(o, len);
    return 1;
}
