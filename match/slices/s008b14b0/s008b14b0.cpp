// flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2 /fp:fast
// Slice s008b14b0 - Bitstream PFR/T2K font engine (pfrread.obj), Spore.
//
// Several of these routines use *custom register conventions* in the original (this in
// esi/edi/eax, other arguments in eax/ecx/dx/di).  Those are written here as ordinary
// functions that take the object/arguments explicitly, so the slice is behavior-complete
// for them but not byte-identical.  The plain cdecl / thiscall ones are written to match.

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef signed char    int8;
typedef short          int16;
typedef int            int32;

// ---------------------------------------------------------------------------
// external helpers (defined elsewhere in the binary)
// ---------------------------------------------------------------------------
struct tsiMemObject;
extern "C" void* tsi_AllocMem(tsiMemObject* mem, uint32 size);      // 0x008d1260
extern "C" void  tsi_DeAllocMem(tsiMemObject* mem, void* p);        // 0x008d1440
extern "C" int   util_FixMul(int a, int b);                         // 0x008d1590
extern "C" void* New_pfrkernSubTable0Data(tsiMemObject* mem, int a, int b); // 0x008b12e0
extern "C" void* New_hmtxEmptyClass(tsiMemObject* mem, int a, int b);       // 0x008cda00
extern "C" void* memset(void* dst, int c, uint32 n);                // 0x011e073e

extern const uint8 g_bitMaskHi[8];   // 0x01432784
extern const uint8 g_bitMaskLo[8];   // 0x01432790

// ---------------------------------------------------------------------------
// PFRClass - the big PFR font object (0x1ec+ bytes)
// ---------------------------------------------------------------------------
struct PFRClass {
    tsiMemObject* mem;          // 0x000
    void*         stream;       // 0x004
    uint8         ver;          // 0x008
    char          pad09[3];     // 0x009
    void*         f0c;          // 0x00c  cmap entry table
    char          pad10[0x28 - 0x10];
    int           f28;          // 0x028
    uint8         f2c;          // 0x02c
    char          pad2d[0x34 - 0x2d];
    uint8         inContour;    // 0x034
    char          pad35[0x36 - 0x35];
    uint16        f36;          // 0x036
    uint16        f38;          // 0x038
    char          pad3a[0x3c - 0x3a];
    void*         f3c;          // 0x03c  kerning item table
    void*         f40;          // 0x040
    void*         f44;          // 0x044
    void*         f48;          // 0x048
    void*         f4c;          // 0x04c
    char          pad50[0xb0 - 0x50];
    int           fb0;          // 0x0b0
    int           fb4;          // 0x0b4
    int           fb8;          // 0x0b8
    int           fbc;          // 0x0bc
    int           fc0;          // 0x0c0
    int           fc4;          // 0x0c4
    int           fc8;          // 0x0c8
    int           fcc;          // 0x0cc
    int           fd0;          // 0x0d0
    int           fd4;          // 0x0d4
    char          padd8[0xe0 - 0xd8];
    int           m[6];         // 0x0e0  transform matrix
    char*         name;         // 0x0f8
    void*         glyph;        // 0x0fc
    void*         f100;         // 0x100  hmtx object
    void*         f104;         // 0x104  hmtx object
    uint16        f108;         // 0x108  glyph count
    char          pad10a[0x120 - 0x10a];
    int           f120;         // 0x120
    char          pad124[0x1e8 - 0x124];
    uint16        f1e8;         // 0x1e8
    uint16        f1ea;         // 0x1ea
};

// hmtx object header: [obj+0x10] is the uint16 metrics array
struct Hmtx { char pad0[0x10]; uint16* data; };

// cmap entry (8 bytes), table at PFRClass::f0c
struct CMapEntry { uint16 w0; uint16 w1; int rest; };

// kerning item (12 bytes), table at PFRClass::f3c
struct KernItem { uint16 w0; uint16 w1; int count; void* data; };
// kerning sub entry (12 bytes), table at KernItem::data
struct KernSub  { uint16 w0; uint16 w1; uint16 w2; uint16 w3; int rest; };

// ---------------------------------------------------------------------------
// run-length / nibble decoder states
// ---------------------------------------------------------------------------
struct BitReader {          // 008b1f50
    uint8  mask;            // 0x00
    uint8  xorflag;         // 0x01
    char   pad02[2];
    uint8* cur;             // 0x04
    int    remaining;       // 0x08
    int    count0;          // 0x0c
    int    count1;          // 0x10
};

struct NibReader {          // 008b1ff0 / 008b2050
    char   pad0[4];
    uint8* cur;             // 0x04
    int    remaining;       // 0x08
    int    f0c;             // 0x0c
    int    f10;             // 0x10
};

struct DecState {           // 008b1ed0
    char   pad0[0xc];
    int    f0c;             // 0x0c
    int    f10;             // 0x10
    void (*cb)(DecState*);  // 0x14
    uint16 f18;             // 0x18
    uint16 f1a;             // 0x1a
    uint16 f1c;             // 0x1c
    uint16 f1e;             // 0x1e
    uint16 f20;             // 0x20
    uint16 f22;             // 0x22
};

// ---------------------------------------------------------------------------
// PFRKern class built by New_pfrkernClass
// ---------------------------------------------------------------------------
struct PFRKernSub {
    tsiMemObject* mem;      // 0x00
    uint16 f04;             // 0x04
    uint16 pad06;
    int    f08;             // 0x08
    uint16 f0c;             // 0x0c
    uint16 pad0e;
    void*  f10;             // 0x10
};

struct PFRKern {
    tsiMemObject* mem;      // 0x00
    uint16 f04;             // 0x04
    uint16 pad06;
    int    f08;             // 0x08
    PFRKernSub** sub;       // 0x0c
};

// output record filled by the kerning-pair lookup (008b20b0)
struct KernOut {
    uint16 w0;              // 0x00
    uint8  b2;              // 0x02
    char   pad3;
    uint16 w4;              // 0x04
    uint16 w6;              // 0x06
    char   pad8[0x30 - 0x08];
    int    f30;             // 0x30
    uint16 f34;             // 0x34
    char   pad36[0x38 - 0x36];
    int    f38;             // 0x38
};

// ===========================================================================
// functions
// ===========================================================================

// @ 0x008b14b0
// original: mem in ebx; args (data, size) on the stack.
PFRKern* New_pfrkernClass(tsiMemObject* mem, int data, int size)
{
    PFRKern* k = (PFRKern*)tsi_AllocMem(mem, 0x10);
    k->mem = mem;
    k->f04 = 0;
    k->f08 = 1;
    k->sub = (PFRKernSub**)tsi_AllocMem(mem, 4);

    PFRKernSub* s = (PFRKernSub*)tsi_AllocMem(mem, 0x14);
    s->mem = mem;
    s->f04 = 0;
    s->f08 = 0x14;
    s->f0c = 1;
    s->f10 = 0;
    s->f10 = New_pfrkernSubTable0Data(mem, data, size);
    *k->sub = s;
    return k;
}

// @ 0x008b1520
void tsi_DeletePFRClass(PFRClass* p)
{
    if (p == 0)
        return;
    tsi_DeAllocMem(p->mem, p->f0c);

    int cnt = (int)(uint16)p->f38;
    if (cnt > 0) {
        int off = cnt * 0xc;
        do {
            tsi_DeAllocMem(p->mem, *(void**)(((char*)p->f3c - 4) + off));
            cnt--;
            off -= 0xc;
        } while (cnt > 0);
    }
    if (p->f38 != 0 && p->f3c != 0)
        tsi_DeAllocMem(p->mem, p->f3c);
    tsi_DeAllocMem(p->mem, p->name);
    tsi_DeAllocMem(p->mem, p);
}

// @ 0x008b15b0
// original: this in edi.
void BuildPFRCMAP(PFRClass* p, uint8** cursor, uint8 flags, uint16 base)
{
    uint8* s = *cursor;
    int cnt = (int)(int16)p->f108;
    CMapEntry* map = (CMapEntry*)tsi_AllocMem(p->mem, (uint32)cnt * 8);
    p->f0c = map;
    for (int i = 0; i < cnt; i++) {
        map[i].w0 = 0xffff;
        map[i].w1 = 0;
        map[i].rest = 0;
    }
    p->f1ea = 0;
    p->f1e8 = 0xffff;

    Hmtx* hmtx = (Hmtx*)New_hmtxEmptyClass(p->mem, cnt, cnt);
    p->f100 = hmtx;
    p->f104 = hmtx;
    uint16* hdata = hmtx->data;

    uint32 accum = 0;       // running first code point
    int    lastRest = 0;    // running "rest" accumulator
    uint16 fonv = 0;        // running advance

    for (int i = 0; i < cnt; i++) {
        if (p->ver != 0) {
            uint32 b = *s++;
            switch (b & 3) {
            case 0:
                map[i].w0 = (uint16)accum;
                break;
            case 1:
                map[i].w0 = (uint16)(*s++ + accum);
                break;
            case 2: {
                uint16 v = (uint16)((s[0] << 8) + s[1]);
                s += 2;
                map[i].w0 = (uint16)(v + accum);
                break;
            }
            default:            // case 3: no store, w0 unchanged
                break;
            }
            accum = (uint32)(uint16)(map[i].w0 + 1);

            switch ((b >> 2) & 3) {
            case 0:
                break;
            case 1:
                fonv = (uint16)(fonv + *s++);
                break;
            case 2:
                fonv = (uint16)(fonv - *s++);
                break;
            default:
                fonv = (uint16)((s[0] << 8) + s[1]);
                s += 2;
                break;
            }
            hdata[i] = fonv;

            switch ((b >> 4) & 3) {
            case 0:
                map[i].w1 = (uint16)(*s++);
                break;
            case 1:
                map[i].w1 = (uint16)(*s++ + 0x100);
                break;
            case 2:
                map[i].w1 = (uint16)(*s++ + 0x200);
                break;
            default:
                map[i].w1 = (uint16)((s[0] << 8) + s[1]);
                s += 2;
                break;
            }

            switch (b >> 6) {
            case 0:
                break;
            case 1:
                lastRest = (int)(uint32)(*s++ + lastRest);
                break;
            case 2: {
                uint32 v = *s;
                s += 2;
                lastRest = (int)((v << 8) + s[-1]);
                break;
            }
            default: {
                uint32 v = ((uint32)s[0] << 16) | ((uint32)s[1] << 8) | s[2];
                s += 3;
                lastRest = (int)v;
                break;
            }
            }
            map[i].rest = lastRest;
            lastRest = (int)((uint32)map[i].w1 + (uint32)map[i].rest);
        } else {
            if (flags & 2) {
                map[i].w0 = (uint16)((s[0] << 8) + s[1]);
                s += 2;
            } else {
                map[i].w0 = (uint16)(*s++);
            }

            if (flags & 4) {
                fonv = (uint16)((s[0] << 8) + s[1]);
                s += 2;
            } else {
                fonv = base;
            }
            hdata[i] = fonv;

            if (flags & 8)
                s++;

            if (flags & 0x10) {
                map[i].w1 = (uint16)((s[0] << 8) + s[1]);
                s += 2;
            } else {
                map[i].w1 = (uint16)(*s++);
            }

            if (flags & 0x20) {
                map[i].rest = (int)(uint32)(((uint32)s[0] << 16) | ((uint32)s[1] << 8) | s[2]);
                s += 3;
            } else {
                map[i].rest = (int)(uint32)(uint16)((s[0] << 8) + s[1]);
                s += 2;
            }
        }

        int adv = (int)(int16)fonv;
        if (p->f120 < adv)
            p->f120 = adv;
        uint16 w0 = map[i].w0;
        if (w0 < p->f1e8)
            p->f1e8 = w0;
        if (w0 > p->f1ea)
            p->f1ea = w0;
    }
    *cursor = s;
}

// @ 0x008b1980
char* GetPFRNameProperty(PFRClass* p)
{
    char* name = p->name;
    if (name == 0)
        return 0;
    char* q = name;
    char* q1 = name + 1;
    char c;
    do { c = *q++; } while (c);
    int len = (int)(q - q1);
    char* out = (char*)tsi_AllocMem(p->mem, len + 1);
    char* src = name;
    int delta = (int)(out - name);
    do { c = *src; src[delta] = c; src++; } while (c);
    out[len] = 0;
    return out;
}

// @ 0x008b19e0
// original: cdecl (does not pop); cursor in ecx, three outputs on the stack, two more in
// eax and edi, key at [esp+8], count at [esp+4].  The register inputs are read with asm.
int ReadKerningEntry(int count, int16 key, int16* o1, int16* o2, int16* o3)
{
    const uint8* p;
    int16* oeax;       // the output pointer that lives in eax
    int*   oedi;       // the output pointer that lives in edi
    __asm {
        mov dword ptr [p], ecx
        mov dword ptr [oeax], eax
        mov dword ptr [oedi], edi
    }
    int found = 1;
    if (count <= 0)
        return found;
    for (;;) {
        uint16 len = (uint16)((p[0] << 8) + p[1]);
        if (len == 0)
            return found;
        uint16 kind = (uint16)((p[2] << 8) + p[3]);
        int eq = (kind == (uint16)key);
        if (kind == 2) {
            if (eq) {
                *o1 = (int16)((p[0xe] << 8) + p[0xf]);
                *o2 = (int16)((p[0x10] << 8) + p[0x11]);
                *oeax = (int16)((p[0x16] << 8) + p[0x17]);
                *o3 = (int16)((p[0x1a] << 8) + p[0x1b]);
                *oedi = (~(int)(int8)p[0x20]) & 1;
                found = 0;
                return found;
            }
        } else if (kind == 7) {
            if (eq) {
                *o1 = (int16)((p[4] << 8) + p[5]);
                *o2 = (int16)((p[0xc] << 8) + p[0xd]);
                *oeax = (int16)((p[0xe] << 8) + p[0xf]);
                *o3 = (int16)((p[6] << 8) + p[7]);
                *oedi = p[0x15];
                found = 0;
                return found;
            }
        }
        if (eq)
            break;
        p += len;
    }
    return found;
}

// @ 0x008b1b80
void FUN_008b1b80(PFRClass* p)
{
    uint16* A  = (uint16*)p->f44;
    uint16* B  = (uint16*)p->f48;
    uint8*  C  = (uint8*)p->f4c;

    for (int16 i = 0; i < (int16)p->f36; i++) {
        int16 a = (int16)((uint16*)p->f3c)[i];
        int16 b = (int16)((uint16*)p->f40)[i];
        int n = (b - a) / 2;
        if (n > 0) {
            int lo = a + 1;
            int hi = b;
            do {
                uint16 sa = A[lo], sb = B[lo];
                uint8  sc = C[lo];
                A[lo] = A[hi];
                B[lo] = B[hi];
                C[lo] = C[hi];
                A[hi] = sa;
                B[hi] = sb;
                C[hi] = sc;
                hi--;
                lo++;
                n--;
            } while (n != 0);
        }
    }
}

// @ 0x008b1c70
// original: this in eax, key in di.
int CmapLookup(PFRClass* p, uint16 key, int* out)
{
    int lo = 0;
    int hi = (int)(int16)p->f108 - 1;
    if (hi < 0)
        return 0;
    CMapEntry* map = (CMapEntry*)p->f0c;
    for (;;) {
        int mid = (hi + lo) / 2;
        uint16 v = map[mid].w0;
        if (key == v) {
            *out = mid;
            return 1;
        }
        if (key < v)
            hi = mid - 1;
        else
            lo = mid + 1;
        if (lo > hi)
            return 0;
    }
}

// @ 0x008b1cd0
// original: this in esi.
void SetupTCB(PFRClass* p)
{
    int a = util_FixMul(p->fd0, p->fb4);
    int b = util_FixMul(p->fc8, p->fb0);
    p->m[0] = a + b;
    a = util_FixMul(p->fd4, p->fb4);
    b = util_FixMul(p->fcc, p->fb0);
    p->m[1] = a + b;
    a = util_FixMul(p->fd0, p->fbc);
    b = util_FixMul(p->fc8, p->fb8);
    p->m[2] = a + b;
    a = util_FixMul(p->fd4, p->fbc);
    b = util_FixMul(p->fcc, p->fb8);
    p->m[3] = a + b;
    p->m[4] = 0;
    p->m[5] = 0;
}

// @ 0x008b1db0
// original: this in esi, arg1 in eax, arg2 in ecx, arg3/arg4 on the stack.
void SetupTrans(PFRClass* p, int a, int b, int c, int d)
{
    int t = util_FixMul(p->m[2], a) + util_FixMul(p->m[0], b);
    p->m[4] += t;
    t = util_FixMul(p->m[1], b) + util_FixMul(p->m[3], a);
    p->m[5] += t;
    p->m[0] = util_FixMul(p->m[0], c);
    p->m[2] = util_FixMul(p->m[2], d);
    p->m[1] = util_FixMul(p->m[1], c);
    p->m[3] = util_FixMul(p->m[3], d);
}

// @ 0x008b1e60
// original: this in esi, x in eax, y / outx / outy on the stack.
void TransformPoint(PFRClass* p, int x, int y, int* ox, int* oy)
{
    int a = util_FixMul(p->m[0], x) + util_FixMul(p->m[2], y);
    int b = util_FixMul(p->m[1], x) + util_FixMul(p->m[3], y);
    *ox = p->m[4] + a;
    *oy = p->m[5] + b;
}

// @ 0x008b1ed0
// original: this in esi.
int FUN_008b1ed0(DecState* p)
{
    if (p->f10 == 0)
        p->cb(p);

    int acc = (int)(int16)p->f1e + p->f0c;
    int step = (int)(int16)p->f18;
    p->f0c = 0;
    if (acc >= step) {
        uint32 sum = p->f20;
        uint32 inc = p->f22;
        do {
            acc -= step;
            sum += inc;
        } while (acc >= step);
        p->f20 = (uint16)sum;
    }
    int avail = p->f10;
    p->f1c = (uint16)acc;
    if (avail + acc >= step) {
        p->f1e = p->f18;
        p->f10 = avail - step + acc;
        return 1;
    }
    if (avail > 0) {
        p->f1e = (uint16)(avail + acc);
        p->f10 = 0;
        return 1;
    }
    return 0;
}

// @ 0x008b1f50
void FUN_008b1f50(BitReader* p)
{
    uint8 mask = p->mask;
    uint8 inv  = p->xorflag;
    int remaining = p->remaining;
    int count1 = 0;
    int count0 = 0;
    if (remaining > 0) {
        uint8 v = *p->cur ^ inv;
        while ((mask & v) != 0) {
            count0++;
            remaining--;
            if (remaining < 1)
                goto done;
            mask >>= 1;
            if (mask == 0) {
                p->cur++;
                mask = 0x80;
                v = *p->cur ^ inv;
            }
        }
        v = *p->cur ^ (uint8)~inv;
        while ((mask & v) != 0) {
            remaining--;
            count1++;
            if (remaining < 1)
                break;
            mask >>= 1;
            if (mask == 0) {
                p->cur++;
                mask = 0x80;
                v = *p->cur ^ (uint8)~inv;
            }
        }
    }
done:
    p->remaining = remaining;
    p->count1 = count1;
    p->count0 = count0;
    p->mask = mask;
}

// @ 0x008b1ff0
void FUN_008b1ff0(NibReader* p)
{
    p->f0c = 0;
    p->f10 = 0;
    if (p->remaining <= 0)
        return;
    uint8 lo;
    do {
        uint8 v = *p->cur;
        uint8 hi = v >> 4;
        lo = v & 0xf;
        p->f10 += lo;
        p->f0c += hi;
        p->cur = p->cur + 1;
        p->remaining -= (int)hi + (int)lo;
    } while (p->remaining > 0 && (lo == 0 || *p->cur == 0));
}

// @ 0x008b2050
void FUN_008b2050(NibReader* p)
{
    p->f0c = 0;
    p->f10 = 0;
    while (p->remaining > 0) {
        uint8* cur = p->cur;
        uint8 v0 = *cur;
        cur++;
        p->f0c += v0;
        p->cur = cur;
        uint8 v1 = *cur;
        uint8* next = cur + 1;
        p->f10 += v1;
        p->remaining -= (int)v0 + (int)v1;
        p->cur = next;
        if (v1 != 0 && next[0] != 0)
            break;
    }
}

// @ 0x008b20b0
// original: cdecl with the output record passed in ecx (never popped); PFRClass / key /
// flag / a / b on the stack.  The register argument is read with a single asm load.
int KernMatch(PFRClass* p, int16 key, char flag, int16 a, int16 b)
{
    KernOut* out;
    __asm { mov dword ptr [out], ecx }
    int found = 0;
    if (flag != 0)
        return 0;

    KernItem* match = 0;
    int idx = 0;
    int i = 0;
    int ok;
    do {
        if (i >= (int)(uint16)p->f38) {
            if (!found)
                return 0;
            break;
        }
        KernItem* e = (KernItem*)p->f3c + idx;
        ok = 0;
        if (e->w0 == (uint16)a && e->w1 == (uint16)b) {
            ok = 1;
            match = e;
        }
        i++;
        idx++;
    } while (!ok);

    KernSub* sub = (KernSub*)match->data;
    for (int j = 0;; j++) {
        if (j >= match->count)
            return found;
        if (sub[j].w0 == (uint16)key) {
            out->w4 = a;
            out->w0 = key;
            out->b2 = 0;
            out->w6 = b;
            out->f34 = sub[j].w2;
            out->f38 = sub[j].rest;
            out->f30 = 0;
            found = 1;
            break;
        }
    }
    return found;
}

// @ 0x008b21a0
// original: x0 in ax, x1 in cx, y in dx, this in esi.
void FUN_008b21a0(PFRClass* p, int16 x0, int16 x1, int16 y)
{
    if (x0 >= x1)
        return;
    int i = (int)x0 >> 3;
    int j = (int)x1 >> 3;
    int row;
    if (p->f2c == 0)
        row = (int)p->f0c - (int)y - 1;
    else
        row = (int)y;
    uint8* dst = (uint8*)p->f44 + row * p->f28 + i;

    uint32 m0 = (uint32)(x0 & 7);
    uint32 m1 = (uint32)(x1 & 7);
    if (i == j) {
        uint8 m = g_bitMaskHi[m1] & g_bitMaskLo[m0];
        dst[0] = (uint8)((~m & dst[0]) + m);
    } else {
        uint8 m = g_bitMaskLo[m0];
        dst[0] = (uint8)((~m & dst[0]) + m);
        dst++;
        if (i + 1 < j) {
            uint32 n = (uint32)(j - (i + 1));
            memset(dst, 0xff, n);
            dst += n;
        }
        m = g_bitMaskHi[m1];
        dst[0] = (uint8)((~m & dst[0]) + m);
    }
}
