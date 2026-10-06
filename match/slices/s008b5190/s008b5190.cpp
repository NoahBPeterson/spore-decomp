// T2K (Type 2000) PFR font loader: tsi_NewPFRClass.
// Several callees use custom register conventions in the original (pfr in esi/eax/edi); they are
// declared here as ordinary functions with the pfr/stream passed explicitly, so this source is a
// behavior-complete (not byte-exact) reconstruction.
#include "types.h"
#include <string.h>
typedef uint8_t uint8; typedef int8_t int8; typedef uint16_t uint16; typedef int16_t int16;
typedef uint32_t uint32; typedef int32_t int32;

struct tsiMemObject;
struct PFRKern;

struct InputStream {
    uint8*  ram;        // 0x000 in-memory data (NULL => read through func)
    int   (*readFunc)(void* ctx, void* dst, int pos, int n);   // 0x004
    void*   ctx;        // 0x008
    uint8   buf[0x208]; // 0x00c scratch (first byte is the read-through result)
    uint32  cacheSize;  // 0x214
    int     cacheStart; // 0x218
    int     pos;        // 0x21c
    int     pad220[3];
    tsiMemObject* mem;  // 0x22c
};

extern "C" void*  tsi_AllocMem(tsiMemObject* mem, uint32 size);               // 0x008d1260
extern "C" void   tsi_DeAllocMem(tsiMemObject* mem, void* p);                 // 0x008d1440
extern "C" void   tsi_Error(tsiMemObject* mem, int code);
extern "C" void   Seek_InputStream(InputStream* in, int pos);                 // 0x008cc580
extern "C" int    Tell_InputStream(InputStream* in);                          // 0x008cc5b0
extern "C" void   PeekInt16(InputStream* in, void* dst, int n);               // 0x008cc220
extern "C" uint16 ReadInt16(InputStream* in);                                 // 0x008cc190
extern "C" void   PrimeT2KInputStream(InputStream* in);
extern "C" int    util_FixMul(int a, int b);                                  // 0x008d1590
extern "C" int    util_FixDiv(int a, int b);                                  // 0x008d16d0
extern "C" void*  memcpy(void*, const void*, size_t);                         // thunk 0x011e0744

struct PFRClass;
// custom-register callees in the original (esi/eax/edi = pfr)
void  FUN_008b1160(InputStream* in);                                          // 0x008b1160 (esi = stream)
void  SetupTCB(PFRClass* pfr);                                                // 0x008b1cd0 (esi = pfr)
void  TransformPoint(PFRClass* pfr, int x, int y, int* outA, int* outB);      // 0x008b1e60 (esi = pfr, eax = x)
void  FUN_008b15b0(PFRClass* pfr, uint8** cursor, uint32 flags, uint32 n);    // 0x008b15b0 (edi = pfr)
uint8 FUN_008b1c70(PFRClass* pfr, uint16 in, int* out);                       // 0x008b1c70 (eax = pfr, di = in)
void  FUN_008b4f00(PFRClass* pfr);                                            // 0x008b4f00 (esi = pfr)
extern "C" void FUN_008cfac0(void* p, uint32 count);                          // 0x008cfac0
PFRKern* New_pfrkernClass(tsiMemObject* mem, uint8* data, uint32 size);       // 0x008b14b0

struct KernEntry { uint16 w0, w1; int rest; };           // 8 bytes
struct KernTable { char pad0[4]; uint16 count; char pad6[6]; KernEntry* entries; /* +0xc */ char pad10[4]; };
struct KernInner { char pad[0x10]; KernTable* table; };
struct PFRKern   { char pad[0xc]; KernInner** inner; };

struct PFRSub  { uint16 z0; uint16 w1; uint16 w2; uint16 pad6; int w3; };   // 12 bytes
struct PFRItem { uint16 a; uint16 b; int count; PFRSub* subs; };            // 12 bytes

struct PFRClass {
    tsiMemObject* mem;      // 0x00
    InputStream*  in;       // 0x04
    uint8  ver;             // 0x08
    char   pad09[7];
    uint32 f10;             // 0x10
    int16  f14;             // 0x14
    uint16 f16;
    uint16 f18;
    uint16 f1a;
    uint8  f1c;             // 0x1c
    char   pad1d[3];
    uint8* f20;             // 0x20
    uint32 f24;             // 0x24
    int    f28;             // 0x28
    int    f2c;             // 0x2c
    int    f30;             // 0x30
    uint8  pad34, f35, f36, pad37;
    uint16 itemCount;       // 0x38
    char   pad3a[2];
    PFRItem* items;         // 0x3c
    char   pad40[0x98 - 0x40];
    uint16 f98, f9a, f9c, f9e, fa0, fa2, fa4, fa6;
    char   pada8[4];
    uint8  fac, fad;        // 0xac, 0xad
    char   padae[2];
    int    fb0[4];          // 0xb0..0xbf
    int    fc0, fc4;
    int    fc8, fcc, fd0, fd4, fd8, fdc;
    int    fe0, fe4, fe8, fec, ff0, ff4;
    char*  ff8;             // 0xf8 (string)
    char   padfc[0x108 - 0xfc];
    uint16 f108;
    char   pad10a[2];
    int    f10c;
    char   pad110[0x120 - 0x110];
    int    f120;
    char   pad124[4];
    PFRKern* kern;          // 0x128
    int    f12c[14];        // 0x12c
    int    f164;            // 0x164
    int    f168, f16c, f170, f174, f178;
    int    f17c, f180;
    int    f184[12];        // 0x184
    int    f1b4[14];        // 0x1b4
    int    f1ec;            // 0x1ec
};

// T2K ReadUnsignedByteMacro
static inline uint8 ReadByte(InputStream* s)
{
    if (s->ram == 0) {
        int p = s->pos++;
        if (s->readFunc(s->ctx, s->buf, p, 1) < 0) {
            tsi_Error(s->mem, 0x2728);
            return 0;
        }
        return s->buf[0];
    }
    if (s->readFunc == 0) {
        uint8 b = s->ram[s->pos];
        s->pos++;
        return b;
    }
    if (s->cacheSize < (uint32)(s->pos - s->cacheStart) + 1)
        PrimeT2KInputStream(s);
    uint8 b = s->ram[s->pos - s->cacheStart];
    s->pos++;
    return b;
}

static inline uint32 be16(const uint8* p) { return (uint16)(p[0] * 0x100 + p[1]); }
static inline uint32 be24(const uint8* p) { return (p[0] << 16) | (p[1] << 8) | p[2]; }

// Transform a value by the TCB matrix (the discarded FixMul calls mirror the original)
static inline int XformX(PFRClass* c, int v)       // v already <<16
{
    util_FixMul(v, c->fe8);
    util_FixMul(1, c->fe0);
    int a = util_FixMul(v, c->fec);
    int b = util_FixMul(1, c->fe4);
    return (c->ff4 + a + b) >> 16;
}
static inline int XformY(PFRClass* c, int v)
{
    int a = util_FixMul(v, c->fe0);
    int b = util_FixMul(1, c->fe8);
    util_FixMul(v, c->fe4);
    util_FixMul(1, c->fec);
    return (c->ff0 + a + b) >> 16;
}

// @ 0x008b5190
PFRClass* tsi_NewPFRClass(tsiMemObject* mem, InputStream* in, int fontIndex)
{
    uint8   hdr[10];
    uint8   hdr2[0x2b];
    uint8   tmp3[3];
    uint8*  data = 0;
    uint32  flags = 0;
    uint32  extra = 0;      // local_78
    int     i;

    PFRClass* pfr = (PFRClass*)tsi_AllocMem(mem, 0x1f0);
    pfr->mem = mem;
    pfr->f14 = (int16)fontIndex;
    pfr->fad = 0;
    pfr->fac = 0;
    pfr->ff8 = 0;
    pfr->in = in;
    pfr->f30 = 0;
    pfr->f120 = 0;

    Seek_InputStream(in, 0);
    PeekInt16(in, hdr, 10);
    if (hdr[0] == 'P' && hdr[1] == 'F' && hdr[2] == 'R') {
        pfr->fa2 = (uint16)(hdr[8] * 0x100 + hdr[9]);
        pfr->fa4 = (uint16)(hdr[4] * 0x100 + hdr[5]);
        pfr->ver = (uint8)(hdr[3] - '0');

        Seek_InputStream(in, 0);
        PeekInt16(in, hdr2, 0x2b);
        pfr->f36 = hdr2[0x2a];
        int dataSize = (int)(((uint32)hdr2[0x29] << 16) | (uint16)(hdr2[0x16] * 0x100 + hdr2[0x17]));
        pfr->f2c = (int)be24(hdr2 + 0x23);
        pfr->f30 = (int)be24(hdr2 + 0x20);

        Seek_InputStream(in, (uint16)(hdr2[0x0c] * 0x100 + hdr2[0x0d]));
        uint16 cnt = ReadInt16(in);
        int p0 = Tell_InputStream(in);
        Seek_InputStream(in, p0 + fontIndex * 5);
        p0 = Tell_InputStream(in);
        Seek_InputStream(in, p0 + 2);
        PeekInt16(in, tmp3, 3);
        int blockPos = (int)be24(tmp3);
        pfr->f10 = cnt;
        Seek_InputStream(in, blockPos);

        // four signed 24-bit values << 8
        PeekInt16(in, tmp3, 3);
        pfr->fb0[0] = ((int)(int8)tmp3[0] * 0x100 + tmp3[1]) * 0x100 + tmp3[2];
        pfr->fb0[0] <<= 8;
        PeekInt16(in, tmp3, 3);
        pfr->fb0[1] = (((int)(int8)tmp3[0] * 0x100 + tmp3[1]) * 0x100 + tmp3[2]) << 8;
        PeekInt16(in, tmp3, 3);
        pfr->fb0[2] = (((int)(int8)tmp3[0] * 0x100 + tmp3[1]) * 0x100 + tmp3[2]) << 8;
        PeekInt16(in, tmp3, 3);
        pfr->fb0[3] = (((int)(int8)tmp3[0] * 0x100 + tmp3[1]) * 0x100 + tmp3[2]) << 8;
        if (pfr->fb0[3] < 0)
            pfr->fb0[3] = -pfr->fb0[3];

        // normalise by the smaller of the two largest-magnitude pairs
        pfr->fc0 = 0;
        pfr->fc4 = 0;
        int m0 = pfr->fb0[0];
        int a0 = m0 < 0 ? -m0 : m0;
        int m1 = pfr->fb0[1];
        int a1 = m1 < 0 ? -m1 : m1;
        int big0;
        if (a1 < a0) big0 = m0 < 0 ? -m0 : m0;
        else         big0 = m1 < 0 ? -m1 : m1;
        int m2 = pfr->fb0[2];
        int a2 = m2 < 0 ? -m2 : m2;
        int m3 = pfr->fb0[3];
        int a3 = m3 < 0 ? -m3 : m3;
        int big1;
        if (a3 < a2) big1 = m2 < 0 ? -m2 : m2;
        else         big1 = m3 < 0 ? -m3 : m3;
        int div = big0;
        if (big1 <= big0) div = big1;
        pfr->fb0[0] = util_FixDiv(pfr->fb0[0], div);
        pfr->fb0[1] = util_FixDiv(pfr->fb0[1], div);
        pfr->fb0[2] = util_FixDiv(pfr->fb0[2], div);
        pfr->fb0[3] = util_FixDiv(pfr->fb0[3], div);

        Seek_InputStream(in, blockPos + 0xc);
        flags = ReadByte(in);

        uint32 v;
        if (flags & 4) {
            if (!(flags & 8)) v = ReadByte(in);
            else              v = ReadInt16(in);
            pfr->fa0 = (uint16)v;
            v = 0;
        } else {
            if (!(flags & 0x10)) v = 0;
            else if (!(flags & 0x20)) v = ReadByte(in);
            else                      v = ReadInt16(in);
        }
        pfr->fa6 = (uint16)v;
        pfr->fac = 0;
        pfr->fad = 0;
        if (flags & 0x40)
            FUN_008b1160(in);

        uint32 size = ReadInt16(in) & 0xffff;
        uint32 dataLen = size;
        PeekInt16(in, tmp3, 3);
        int dataPos = (int)be24(tmp3);
        if (dataSize > 0xffff) {
            size += (uint32)ReadByte(in) * 0x10000;
            dataLen = size;
        }
        data = (uint8*)tsi_AllocMem(mem, size);
        if (data == 0)
            return 0;
        Seek_InputStream(in, dataPos);
        PeekInt16(in, data, dataLen);

        pfr->f16 = (uint16)be16(data);
        pfr->f18 = (uint16)be16(data + 2);
        pfr->f1a = (uint16)be16(data + 4);
        pfr->f35 = (pfr->ver < 2 || pfr->f18 > 0xff) ? 0 : 1;
        int r = util_FixDiv((uint32)pfr->f1a << 16, (uint32)pfr->f18 << 16);
        pfr->f28 = r;
        pfr->fc8 = r;
        pfr->fcc = 0;
        pfr->fd0 = 0;
        pfr->fd4 = r;
        pfr->fd8 = 0;
        pfr->fdc = 0;
        SetupTCB(pfr);
        pfr->f10c = pfr->f1a;
        pfr->f98 = (uint16)be16(data + 6);
        pfr->f9a = (uint16)be16(data + 8);
        pfr->f9c = (uint16)be16(data + 10);
        pfr->f9e = (uint16)be16(data + 12);

        uint8 flags2 = data[14];
        uint8* cur = data + 15;
        flags = flags2;
        pfr->f1c = flags2 & 1;
        if (!(flags2 & 4)) {
            extra = be16(cur);
            cur += 2;
        }
        pfr->kern = 0;
        pfr->itemCount = 0;

        if ((int8)flags2 < 0) {
            int nItems = *cur++;
            int itemsDone = 0;      // local_5c
            if (nItems != 0) {
                for (int it = 0; it < nItems; it++) {
                    uint32 itemSize = cur[0];
                    uint8  type = cur[1];
                    uint8* body = cur + 2;
                    if (type == 2) {
                        uint8* e = body;
                        uint8 c;
                        do { c = *e++; } while (c != 0);
                        uint8* name = (uint8*)tsi_AllocMem(mem, (uint32)(e + 1 - (cur + 3)));
                        pfr->ff8 = (char*)name;
                        cur = body;
                        if (name != 0) {
                            do {
                                c = *cur;
                                *name = c;
                                name++;
                                cur++;
                            } while (c != 0);
                        }
                    } else if (type == 3) {
                        uint8 b = *body;
                        uint8* q = cur + 3;
                        int nx = b >> 4;
                        pfr->f17c = nx;
                        pfr->f180 = b & 0xf;
                        int ox, oy;
                        if (nx != 0) {
                            int k = 0, idx = 0;
                            do {
                                pfr->f1b4[idx] = (int)be16(q);
                                q += 2;
                                TransformPoint(pfr, pfr->f1b4[idx] << 16, 1, &ox, &oy);
                                pfr->f1b4[idx] = ox >> 16;
                                k++;
                                idx = (int16)k;
                            } while (idx < pfr->f17c);
                        }
                        if (pfr->f180 > 0) {
                            int k = 0, idx = 0;
                            do {
                                pfr->f184[idx] = (int)be16(q);
                                q += 2;
                                TransformPoint(pfr, 1, pfr->f184[idx] << 16, &ox, &oy);
                                pfr->f184[idx] = oy >> 16;
                                k++;
                                idx = (int16)k;
                            } while (idx < pfr->f180);
                        }
                    } else if (type == 4) {
                        if (pfr->kern == 0)
                            pfr->kern = New_pfrkernClass(mem, body, itemSize);
                    } else if (type == 1) {
                        uint8 kflags = cur[5];
                        int base = dataPos + (int)size;
                        int nk = (int16)(uint16)cur[6];
                        cur += 7;
                        pfr->items = (PFRItem*)tsi_AllocMem(mem, nk * 12);
                        if (pfr->items != 0 && nk > 0) {
                            uint8 f2 = kflags & 2, f4 = kflags & 4, f8 = kflags & 8, f10 = kflags & 0x10;
                            int rec = itemsDone * 12;
                            uint8 f1 = kflags & 1;
                            for (int k = 0; k < nk; k++) {
                                uint16 va;
                                uint8* t;
                                if (f1 == 0) { va = *cur; t = cur + 1; }
                                else         { t = cur + 2; va = (uint16)be16(cur); }
                                uint32 vb;
                                if (f2 == 0) { vb = *t; cur = t + 1; }
                                else         { cur = t + 2; vb = be16(t); }
                                uint8 sflags = *cur;
                                uint32 vlen;
                                if (f4 == 0) { t = cur + 3; vlen = be16(cur + 1); }
                                else         { t = cur + 4; vlen = be24(cur + 1); }
                                uint32 voff;
                                uint8* t2;
                                if (f8 == 0) { t2 = t + 2; voff = be16(t); }
                                else         { t2 = t + 3; voff = be24(t); }
                                int vcount;
                                if (f10 == 0) { vcount = *t2; cur = t2 + 1; }
                                else          { cur = t2 + 2; vcount = (int)be16(t2); }

                                PFRItem* item = (PFRItem*)((char*)pfr->items + rec);
                                item->a = va;
                                item->b = (uint16)vb;
                                item->count = vcount;
                                item->subs = (PFRSub*)tsi_AllocMem(mem, vcount * 12);
                                uint8* sbuf = (uint8*)tsi_AllocMem(mem, vlen);
                                if (sbuf == 0)
                                    return 0;
                                Seek_InputStream(in, voff + base);
                                PeekInt16(in, sbuf, vlen);
                                if (vcount > 0) {
                                    uint8 g2 = sflags & 2, g4 = sflags & 4;
                                    uint8 g1 = sflags & 1;
                                    int off = 0;
                                    int n = vcount;
                                    uint8* s = sbuf;
                                    do {
                                        uint16 sa;
                                        uint8* s1;
                                        if (g1 == 0) { sa = *s; s1 = s + 1; }
                                        else         { s1 = s + 2; sa = (uint16)be16(s); }
                                        uint16 sb;
                                        uint8* s2;
                                        if (g2 == 0) { sb = *s1; s2 = s1 + 1; }
                                        else         { s2 = s1 + 2; sb = (uint16)be16(s1); }
                                        uint32 sc;
                                        if (g4 == 0) { sc = be16(s2); s = s2 + 2; }
                                        else         { sc = be24(s2); s = s2 + 3; }
                                        PFRSub* sub = (PFRSub*)((char*)item->subs + off);
                                        sub->z0 = 0;
                                        sub->w1 = sa;
                                        sub->w2 = sb;
                                        sub->w3 = (int)sc;
                                        off += 12;
                                        n--;
                                    } while (n != 0);
                                }
                                tsi_DeAllocMem(mem, sbuf);
                                itemsDone++;
                                rec += 12;
                            }
                        }
                        pfr->itemCount = (uint16)itemsDone;
                    }
                    cur = body + (int16)itemSize;
                }
            }
        }

        // glyph data block
        uint8* blk = cur + 3;
        uint32 blkLen = be24(cur);
        pfr->f24 = blkLen;
        if (blkLen == 0) {
            pfr->f20 = 0;
        } else {
            pfr->f20 = (uint8*)tsi_AllocMem(mem, blkLen);
            memcpy(pfr->f20, blk, pfr->f24);
        }
        int nc = (int16)(uint16)blk[pfr->f24];
        blk += pfr->f24 + 1;
        pfr->f164 = nc;
        if (nc != 0) {
            int* dst = pfr->f12c;
            int left = nc;
            do {
                int v16 = (int)be16(blk);
                blk += 2;
                *dst = v16;
                *dst = XformX(pfr, v16 << 16);
                dst++;
                left--;
            } while (left != 0);
        }
        pfr->f168 = blk[0];
        pfr->f168 = XformX(pfr, (int)blk[0] << 16);
        pfr->f16c = blk[1];
        {
            int xv = XformX(pfr, (int)blk[1] << 16);
            pfr->f170 = (int)(((uint32)pfr->f18 * 0x1cb + 0x8000)) >> 16;
            pfr->f16c = xv;
        }
        pfr->f174 = (int)be16(blk + 2);
        pfr->f174 = XformY(pfr, pfr->f174 << 16);
        pfr->f178 = (int)be16(blk + 4);
        {
            int xv = XformX(pfr, pfr->f178 << 16);
            uint8* rest = blk + 8;
            pfr->f178 = xv;
            pfr->f108 = (uint16)be16(blk + 6);
            uint8* c2 = rest;
            FUN_008b15b0(pfr, &c2, flags, extra);
        }

        for (int k = 0; k < (int)pfr->itemCount; k++) {
            PFRItem* item = &pfr->items[k];
            for (int j = 0; j < item->count; j++) {
                int out = 0;
                uint8 r2 = FUN_008b1c70(pfr, item->subs[j].w1, &out);
                pfr->f1ec = r2;
                item->subs[j].z0 = (uint16)out;
            }
        }
        if (pfr->kern != 0) {
            KernTable* t = (*pfr->kern->inner)->table;
            for (i = 0; i < t->count; i++) {
                KernEntry* e = &t->entries[i];
                uint16 w0 = e->w0;
                int outHi = 0;
                pfr->f1ec = FUN_008b1c70(pfr, e->w1, &outHi);
                int outLo = 0;
                pfr->f1ec = FUN_008b1c70(pfr, w0, &outLo);
                *(uint32*)e = ((uint32)(uint16)outHi << 16) | (uint16)outLo;
            }
            FUN_008cfac0(t->entries, t->count);
        }
        FUN_008b4f00(pfr);
        tsi_DeAllocMem(mem, pfr->f20);
        tsi_DeAllocMem(mem, data);
    }
    pfr->fad = 1;
    return pfr;
}
