// Slice s008b3040: T2K (Type 2000) PFR hint/edge decoders plus the two small readers
// that drive them, and the packed-coordinate reader they share.
//
// These are module-local helpers of the PFR glyph builder. In the original TU they were
// static, so MSVC (no /GL) gave them register arguments: the outline object arrives in
// eax (the object pointer also in edi for ProcessExtraEdges/Hints), the nibble reader in
// esi/ecx, and FUN_008b1c70 takes its object in eax and its key in edi. Those register
// conventions cannot be forced from a separate translation unit, so every callee here
// is declared with the registers passed explicitly and these functions are
// behaviour-complete reconstructions, not byte-exact. Bodies are literal ports of the
// Ghidra decompilation of this slice; layouts follow the neighbouring slice s008b3ae0.

#include "types.h"
typedef unsigned char uint8; typedef signed char int8; typedef unsigned short uint16;
typedef short int16; typedef unsigned int uint; typedef unsigned int uint32;
typedef int int32;

struct tsiMemObject;
struct InputStream;

extern "C" void* tsi_AllocMem(tsiMemObject* mem, uint32 size);                 // 0x008d1260
extern "C" void  tsi_DeAllocMem(tsiMemObject* mem, void* p);                   // 0x008d1440
extern "C" void* tsi_ReAllocMem(tsiMemObject* mem, void* p, uint32 size);      // 0x008d1330
extern "C" void  Seek_InputStream(InputStream* in, int pos);                   // 0x008cc580
extern "C" void  PeekInt16(InputStream* in, void* dst, int n);                 // 0x008cc220

// ---------------------------------------------------------------------------
// Outline accumulator: parallel int16 arrays with capacity/count pairs.
// ---------------------------------------------------------------------------
struct GlyphBuilder { char pad[0x38]; int16 contour; };

struct PFROutline {
    tsiMemObject* mem;           // 0x000
    char   pad4[0xfc - 4];
    GlyphBuilder* glyph;         // 0x0fc
    char   pad100[0x34e - 0x100];
    int16  cntEdges;             // 0x34e
    int16  capY;                 // 0x350
    int16  capX;                 // 0x352
    int16  cntXSet;              // 0x354
    char   pad356[2];
    int16* xAll;                 // 0x358
    int16* xPts;                 // 0x35c
    int16* xSetArr;              // 0x360
    int16* xExtra;               // 0x364
    int16* yAll;                 // 0x368
    int16* yPts;                 // 0x36c
    int16* ySetArr;              // 0x370
    int16* yExtra;               // 0x374
};

// ---------------------------------------------------------------------------
// Glyph builder + PFR font object (only the members these functions touch).
// ---------------------------------------------------------------------------
struct PFRClass {
    tsiMemObject* mem;           // 0x00
    InputStream*  stream;        // 0x04
    uint8  ver;                  // 0x08
    char   pad09[0x28 - 9];
    int    f28;                  // 0x28
    int    dataBase;             // 0x2c
    char   pad30[4];
    uint8  inContour;            // 0x34
    char   pad35[0xb4 - 0x35];
    int    fb4;                  // 0xb4
    char   padb8[0xe0 - 0xb8];
    int    m[6];                 // 0xe0 transform: m0 m1 m2 m3 tx ty
    char   pade8[0xfc - 0xf8];
    GlyphBuilder* glyph;         // 0xfc
};

// per-glyph coordinate sets decoded by FUN_008b0920
struct PFRPts {
    int16 nx;  int16 xs[64];     // 0x000
    int16 ny;  int16 ys[64];     // 0x082
    int16 curX, curY;            // 0x104
    int16 w108, w10a;            // 0x108 saved start of the last command
};

// command-stream cursor used by FUN_008b3680 (the "nibble reader" state)
struct cNibbleReader {
    uint8* cur;                  // 0x00
    int16  flag;                 // 0x04
};

// selectable bit-run record used by FUN_008b3440 (PFR_GetSbits)
struct PFRRec {
    char   pad00[0x40];
    int16  x;                    // 0x40
    int16  y;                    // 0x44
    int16  z;                    // 0x46
    int    f48;                  // 0x48
    int    f4c;                  // 0x4c
    int    f50;                  // 0x50
    int    f54;                  // 0x54
    int    f58;                  // 0x58
    int    f5c;                  // 0x5c
    int    f60;                  // 0x60
    int    f64;                  // 0x64
    int    f68;                  // 0x68
    char   pad6c[4];
    void*  buf70;                // 0x70
    uint16 size74;               // 0x74
    char   pad76[2];
    int    off78;                // 0x78
    void*  buf7c;                // 0x7c
};

// ---------------------------------------------------------------------------
// module-local callees (register conventions noted; all are out of slice)
// ---------------------------------------------------------------------------
extern "C" void ProcessExtraStrokes(PFROutline* o, uint8* data);               // 0x008b2da0 (eax = o)
extern "C" void ProcessExtraEdgesHints(PFROutline* o, uint8* data);            // 0x008b3040 (eax = o)
extern "C" void ProcessExtraHints(void* self, PFROutline* o, uint8** cursor);  // 0x008b3390 (eax = self)

extern "C" int   TransformPoint(int x, int* ox, int* oy);                      // 0x008b1e60 (x in eax)

extern "C" uint  NibbleReadA(PFRClass* pfr, int16* out);                       // 0x008b1040
extern "C" int16 NibbleReadB(PFRClass* pfr);                                   // 0x008b1070
extern "C" int16 ReadDelta(PFRClass* pfr, int first);                          // 0x008b10a0
extern "C" uint16 ReadPacked(cNibbleReader* st);                               // 0x008b2b30
extern "C" void  EmitVal(cNibbleReader* st, int16* dst, int a, int16 v);       // 0x008b2be0

extern "C" int   FindCharIndex(PFRClass* pfr, int16 key, int16* out);          // 0x008b1c70 (obj in eax, key in edi)
extern "C" int16 AddPointRange(PFRClass* pfr, int16 a, int16 b, int16 e, int16 f); // 0x008b20b0 (ecx = this)
extern "C" void  FUN_008b2250(PFRClass* pfr, int a, int b, int c);             // 0x008b2250

// ---------------------------------------------------------------------------
// @ 0x008b3040
// ProcessExtraEdges: decode a run of edge commands. The command byte gives a
// point count; the point loop runs twice over the same decoded stream, first
// filling the x pass arrays, then the y pass arrays.
// ---------------------------------------------------------------------------
extern "C" void ProcessExtraEdgesHints(PFROutline* o, uint8* data)
{
    int16* xAll = o->xAll;       // pass 0 "all"
    int16* xSet = o->xSetArr;    // pass 0 "current"
    int16* yAll = o->yAll;       // pass 0 secondary
    int16* ySet = o->ySetArr;    // pass 0 contour
    int16* xPts = o->xPts;       // pass 1 "current" (after realloc)
    int16* xExt = o->xExtra;
    int16* yPts = o->yPts;
    int16* yExt = o->yExtra;

    int   second = 0;
    int   count  = 0;
    uint8* cur   = data;

    int   base = o->cntEdges;    // word index of the first point this call writes

    // The "current point" array is xSetArr (pass 0) / xExtra (pass 1); the other
    // three arrays are reached through signed word deltas from it.
    int16* pt;
    int    dAll;                 // xAll (p0) / xPts (p1)
    int    dY;                   // yAll (p0) / yPts (p1)
    int    dYSet;                // ySetArr (p0) / yExtra (p1)

    if (!second) {
        pt    = xSet + base;
        dAll  = (int)(xAll - xSet);
        dY    = (int)(yAll - xSet);
        dYSet = (int)(ySet - xSet);
    } else {
        pt    = xExt + base;
        dAll  = (int)(xPts - xExt);
        dY    = (int)(yPts - xExt);
        dYSet = (int)(yExt - xExt);
    }

    int last = 0;

    for (;;) {
        count = *cur++;
        int tag = 0;

        if (second) {
            if (o->capX <= o->cntEdges + count) {
                int16 cap = (int16)(o->capX + 0x14);
                o->capX = cap;
                xPts = (int16*)tsi_ReAllocMem(o->mem, xPts, cap * 2);
                xExt = (int16*)tsi_ReAllocMem(o->mem, xExt, cap * 2);
                yPts = (int16*)tsi_ReAllocMem(o->mem, yPts, cap * 2);
                yExt = (int16*)tsi_ReAllocMem(o->mem, yExt, cap * 2);
                pt    = xExt + base;
                dAll  = (int)(xPts - xExt);
                dY    = (int)(yPts - xExt);
                dYSet = (int)(yExt - xExt);
            }
        } else {
            if (o->capY <= o->cntEdges + count) {
                int16 cap = (int16)(o->capY + 0x14);
                o->capY = cap;
                xAll = (int16*)tsi_ReAllocMem(o->mem, xAll, cap * 2);
                yAll = (int16*)tsi_ReAllocMem(o->mem, yAll, cap * 2);
                xSet = (int16*)tsi_ReAllocMem(o->mem, xSet, cap * 2);
                ySet = (int16*)tsi_ReAllocMem(o->mem, ySet, cap * 2);
                pt    = xSet + base;
                dAll  = (int)(xAll - xSet);
                dY    = (int)(yAll - xSet);
                dYSet = (int)(ySet - xSet);
            }
        }

        if (count > 0) {
            int16* p = pt;
            int n = count;
            do {
                uint8 b = *cur++;
                if ((int8_t)b < 0) {
                    tag = (b & 0x3f) - 1;
                    if (tag < 0) tag = *cur++;
                    if (b & 0x40)
                        *(int16*)((char*)p + dAll * 2) = 0x10;
                    else
                        *(int16*)((char*)p + dAll * 2) = *cur++;
                    int16 c = (int16)(int8_t)*cur++;
                    *p = c;
                    if (c == 0) {
                        c = (int16)((uint16)*cur * 0x100 + (uint16)cur[1]);
                        cur += 2;
                        *p = c;
                    }
                } else {
                    tag += b >> 4;
                    *(int16*)((char*)p + dAll * 2) = 0x10;
                    *p = (int16)((int8_t)(b << 4) >> 4);
                }

                int ox, oy;
                if (second) {
                    TransformPoint((int)*p << 16, &ox, &oy);
                    *p = (int16)(oy >> 16);
                } else {
                    TransformPoint(1, &ox, &oy);
                    *p = (int16)(ox >> 16);
                }
                last = tag;
                *(int16*)((char*)p + dY * 2) = (int16)tag;
                *(int16*)((char*)p + dYSet * 2) = o->glyph->contour;
                ++p;
            } while (--n != 0);
        }

        if (second) break;
        o->cntEdges = (int16)(o->cntEdges + (int16)count);
        base = o->cntEdges;
        second = 1;
        pt    = xExt + base;
        dAll  = (int)(xPts - xExt);
        dY    = (int)(yPts - xExt);
        dYSet = (int)(yExt - xExt);
    }
    (void)last;
    o->cntEdges = (int16)(o->cntEdges + (int16)count);
}

// ---------------------------------------------------------------------------
// @ 0x008b3390
// ProcessExtraHints: walk a list of hint records; each record's type byte picks
// the stroke or edge decoder. The cursor it advances is the caller's pointer.
// ---------------------------------------------------------------------------
extern "C" void ProcessExtraHints(void* self, PFROutline* o, uint8** cursor)
{
    (void)self;
    uint8* p = *cursor + 1;
    uint16 n = *(uint8*)*cursor;
    if (n != 0) {
        uint32 c = n;
        do {
            uint8 b = *p;
            uint8* q = p + 2;
            if (p[1] == 1)
                ProcessExtraStrokes(o, q);
            else if (p[1] == 2)
                ProcessExtraEdgesHints(o, q);
            p = q + (int16)(uint16)b;
        } while (--c != 0);
        *cursor = p;
        return;
    }
    *cursor = p;
}

// ---------------------------------------------------------------------------
// @ 0x008b3400
// Binary-search the character table for the key in edi; store the low byte of the
// result into obj->0x1ec and return the found index (or 0).
// ---------------------------------------------------------------------------
extern "C" uint FUN_008b3400(PFRClass* obj, int16 key)
{
    int16 local4 = 0;
    uint  r = (uint)FindCharIndex(obj, key, &local4);
    *(uint*)((char*)obj + 0x1ec) = (uint)(r & 0xff);
    return (uint)(uint16)local4;
}

// ---------------------------------------------------------------------------
// @ 0x008b3440
// PFR_GetSbits: resolve the selectable bit-run record for (key, flags), load it
// from the stream and copy its metrics into the target object.
// ---------------------------------------------------------------------------
extern "C" uint FUN_008b3440(PFRClass* obj, uint key, char noLoad, uint8 flags)
{
    uint result = 0;
    if (noLoad != 0)
        return 0;

    if (*(int*)((char*)obj + 0x1c) != 0) {
        char* q = *(char**)((char*)obj + 0x184);
        PFRRec* r = *(PFRRec**)(q + 0x28);
        int16 sx = r->x;
        int16 sy = r->y;
        int16 sz = r->z;

        if ((flags & 8) == 0)
            key = FUN_008b3400((PFRClass*)r, (int16)key);

        if ((( r->x != (int16)key || sy != r->y || sz != r->z ) &&
             (AddPointRange((PFRClass*)r, (int16)key, 0, sy, sz),
              r->x != (int16)key || sy != r->y || sz != r->z)))
            return 0;

        result = 1;
        void* buf = tsi_AllocMem(*(tsiMemObject**)r, r->size74);
        r->buf70 = buf;
        if (buf == 0)
            return 0;

        Seek_InputStream(*(InputStream**)((char*)r + 4), *(int*)((char*)r + 0x2c) + r->off78);
        PeekInt16(*(InputStream**)((char*)r + 4), r->buf70, r->size74);
        FUN_008b2250((PFRClass*)r, 0, 0, 0);
        tsi_DeAllocMem(*(tsiMemObject**)r, r->buf70);
        r->buf70 = 0;
        if (flags & 0x20) {
            tsi_DeAllocMem(*(tsiMemObject**)r, r->buf7c);
            r->buf7c = 0;
        }

        *(void**)((char*)obj + 0x118) = r->buf7c;
        r->buf7c = 0;
        *(int*)((char*)obj + 0xd0) = r->f58;
        *(int*)((char*)obj + 0xd4) = 0;
        *(int*)((char*)obj + 0x114) = r->f68;
        r->f68 = 0;
        *(int*)((char*)obj + 0x10c) = r->f48;
        *(int*)((char*)obj + 0x110) = r->f4c;
        *(int*)((char*)obj + 0xcc) = 1;
        *(int*)((char*)obj + 0xe4) = r->f50 >> 10;
        *(int*)((char*)obj + 0xe0) = r->f54 >> 10;
        int v = r->f58;
        *(int*)((char*)obj + 0xd0) = v;
        *(int*)((char*)obj + 0xd8) = v;
        v = r->f5c;
        *(int*)((char*)obj + 0xd4) = v;
        *(int*)((char*)obj + 0xdc) = v;
        *(int*)((char*)obj + 0xe8) = 1;
        *(int*)((char*)obj + 0x100) = r->f5c >> 10;
        *(int*)((char*)obj + 0xfc)  = r->f60 >> 10;
        v = r->f64;
        *(int*)((char*)obj + 0xf0) = v;
        *(int*)((char*)obj + 0xf8) = v;
        v = r->f58;
        *(int*)((char*)obj + 0xec) = v;
        *(int*)((char*)obj + 0xf4) = v;

        if (*(char*)((char*)r + 0x1c) != 0) {
            *(int*)((char*)obj + 0xcc) = 0;
            return 1;
        }
        *(int*)((char*)obj + 0xe8) = 0;
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x008b3680
// Decode one PFR command from the nibble reader and emit the resulting point
// (and, for the compound commands, the follow-up points) into `out`.
// ---------------------------------------------------------------------------
extern "C" void FUN_008b3680(PFRPts* pts, cNibbleReader* st, int16* out, int* type)
{
    out[0] = pts->w108;
    out[1] = pts->w10a;

    uint8 op;
    if (*type < 0) {
        op = 6;
    } else if (st->flag == 0) {
        st->flag = 1;
        op = (uint8)(*st->cur >> 4);
    } else {
        st->flag = 0;
        op = (uint8)(*st->cur & 0xf);
        st->cur += 1;
    }

    switch (op) {
    case 0:
        *type = 1;
        {
            uint8 b = (uint8)NibbleReadA((PFRClass*)pts, 0);
            if ((b & 8) == 0) {
                out[0] = ReadDelta((PFRClass*)pts, 0);
                goto save;
            }
            out[1] = ReadDelta((PFRClass*)pts, 1);
        }
        goto save;
    case 1:
        *type = 1;
        out[0] = (int16)((int8_t)NibbleReadB((PFRClass*)pts) + pts->w108);
        goto save;
    case 2:
        *type = 1;
        out[1] = (int16)((int8_t)NibbleReadB((PFRClass*)pts) + pts->w10a);
        goto save;
    case 3:
        *type = 1;
        out[0] = (int16)((int16)ReadPacked(st) + pts->w108);
        goto save;
    case 4:
        *type = 1;
        out[1] = (int16)((int16)ReadPacked(st) + pts->w10a);
        goto save;
    case 5:
        *type = 1;
        NibbleReadA((PFRClass*)pts, 0);
        EmitVal(st, out, 0, 0);
        return;
    case 6:
        *type = 0;
        NibbleReadA((PFRClass*)pts, 0);
        EmitVal(st, out, 0, 0);
        return;
    case 7:
        break;
    case 8:
        goto do_pair;
    case 9:
        NibbleReadA((PFRClass*)pts, 0);
        break;
    case 10:
        NibbleReadA((PFRClass*)pts, 0);
        goto do_pair;
    case 0xb:
        NibbleReadB((PFRClass*)pts);
        break;
    case 0xc:
        NibbleReadB((PFRClass*)pts);
        goto do_pair;
    case 0xd:
        NibbleReadA((PFRClass*)pts, 0);
        goto do_pair2;
    case 0xe:
        NibbleReadB((PFRClass*)pts);
        goto do_pair2;
    case 0xf:
        NibbleReadA((PFRClass*)pts, 0);
        NibbleReadB((PFRClass*)pts);
        goto do_pair2;
    default:
        return;
    }

    // cases 7 / 9 / 0xb fall here
    *type = 2;
    EmitVal(st, out, 0, 0);
    out[2] = out[0];
    {
        int16 v = ReadDelta((PFRClass*)pts, 0);
        out[3] = v;
        out[4] = out[3];
        EmitVal(st, out + 4, 0, 0);
    }
    return;

do_pair:
    *type = 2;
    EmitVal(st, out, 0, 0);
    out[2] = out[0];
    out[3] = ReadDelta((PFRClass*)pts, 1);
    EmitVal(st, out + 2, 0, 0);
    out[4] = out[2];
    out[5] = out[3];
    EmitVal(st, out + 4, 0, 0);
    return;

do_pair2:
    *type = 2;
    out[0] = (int16)(out[0] + (pts->w108 - pts->w10a));
    out[1] = (int16)(out[1] + (pts->w108 - pts->w10a));
    EmitVal(st, out, 0, 0);
    out[2] = out[0];
    out[3] = out[1];
    EmitVal(st, out + 2, 0, 0);
    out[4] = out[2];
    out[5] = out[3];
    EmitVal(st, out + 4, 0, 0);
    return;

save:
    pts->w108 = out[0];
    pts->w10a = out[1];
    pts->curX = out[0];
    pts->curY = out[1];
    return;
}
