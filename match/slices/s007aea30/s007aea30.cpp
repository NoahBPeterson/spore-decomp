// Slice s007aea30 — DXT endpoint refinement and the 0x20-byte "endpoint" array
// copy helpers (0x7aea30..0x7af720).
// Optimized region: /O2 /MD /Gy /EHsc /TP. findendpoints (0x7aeab0) is complete, not byte-exact.
#include "types.h"

// 0x20-byte endpoint record.
struct Endpoint {
    int      v[7];   // +0x00
    uint8_t  c;      // +0x1c
};

// ---------------------------------------------------------------------------
// @ 0x007af5d0
void FUN_007af5d0(Endpoint* first, Endpoint* last, Endpoint* dest)
{
    for (; first != last; ++first) {
        if (dest != 0) {
            dest->v[0] = first->v[0];
            dest->v[1] = first->v[1];
            dest->v[2] = first->v[2];
            dest->v[3] = first->v[3];
            dest->v[4] = first->v[4];
            dest->v[5] = first->v[5];
            dest->v[6] = first->v[6];
            dest->c    = first->c;
        }
        ++dest;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007af620
void FUN_007af620(Endpoint* first, Endpoint* last, const Endpoint* src)
{
    for (; first != last; ++first) {
        first->v[0] = src->v[0];
        first->v[1] = src->v[1];
        first->v[2] = src->v[2];
        first->v[3] = src->v[3];
        first->v[4] = src->v[4];
        first->v[5] = src->v[5];
        first->v[6] = src->v[6];
        first->c    = src->c;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007af670
void FUN_007af670(Endpoint* dest, uint32_t n, const Endpoint* src)
{
    Endpoint* d = dest;
    while (n > 0) {
        if (d != 0) {
            d->v[0] = src->v[0];
            d->v[1] = src->v[1];
            d->v[2] = src->v[2];
            d->v[3] = src->v[3];
            d->v[4] = src->v[4];
            d->v[5] = src->v[5];
            d->v[6] = src->v[6];
            d->c    = src->c;
        }
        --n;
        d = (Endpoint*)((char*)d + 0x20);
    }
}

// ---------------------------------------------------------------------------
// @ 0x007af6d0
void FUN_007af6d0(Endpoint* first, Endpoint* last, Endpoint* dest)
{
    while (last != first) {
        last = (Endpoint*)((char*)last - 0x20);
        dest = (Endpoint*)((char*)dest - 0x20);
        dest->v[0] = last->v[0];
        dest->v[1] = last->v[1];
        dest->v[2] = last->v[2];
        dest->v[3] = last->v[3];
        dest->v[4] = last->v[4];
        dest->v[5] = last->v[5];
        dest->v[6] = last->v[6];
        dest->c    = last->c;
    }
}

// ---------------------------------------------------------------------------
// DXT surface destructor (compiler-generated): releases three held references and resets the base
// vtables. Same shape as DxtSurface (slice s007ada40, 0x007ae980) with a third member at +0x24.
class DxtBase1 { public: virtual void v1(); virtual ~DxtBase1() {} };
class DxtBase2 { public: virtual void v2(); virtual ~DxtBase2() {} };
class DxtRefCount { public: long mCount; };
struct IRel1 { virtual void v0(); virtual void Release(); };                      // Release at slot 1 (+4)
struct IRel2 { virtual void v0(); virtual void v1(); virtual void Release(); };   // Release at slot 2 (+8)
template<class T> struct RelPtr {
    T* mp;
    ~RelPtr() { if (mp) mp->Release(); }
};
class DxtSurfaceEx : public DxtBase1, public DxtBase2, public DxtRefCount {
public:
    RelPtr<IRel1> mC;    // +0x0c
    RelPtr<IRel1> m10;   // +0x10
    int m14[4];          // +0x14
    RelPtr<IRel2> m24;   // +0x24
    DxtSurfaceEx();
};
DxtSurfaceEx::DxtSurfaceEx() { mC.mp = 0; m10.mp = 0; m24.mp = 0; }   // forces the vtable / dtor emission

// @ 0x007aea30 (compiler-generated ~DxtSurfaceEx)
#pragma auto_inline(off)
void DestroyDxtSurfaceEx(DxtSurfaceEx* p)
{
    p->~DxtSurfaceEx();
}
#pragma auto_inline(on)

// @ 0x007aeab0  findendpoints
//
// Searches 565 endpoint pairs for a 4x4 DXT block.  `colors` holds the block's
// two extreme 888 colours (0xAARRGGBB); the search widens with `quality`:
//   >=  5  try the extremes,  < 10 also try them swapped,
//   >= 10  try every ordered pixel pair,
//   >  10  refine around the extrapolated min/max box: e0 alone (>=20), e1
//          alone (>=25), then red/blue pre-screened pairs (>=30).
// Stops early once the error is <= the quality threshold.  Returns the best error.
//
// In the original the helpers in this TU use compiler-chosen register
// conventions (findendpoints: colors in ecx; trymapblock: c0 in ecx, c1 in eax).
// Here they are plain cdecl with the same argument values.
extern "C" uint32_t trymapblock(uint32_t c0, uint32_t c1, uint32_t* map,
                                const uint32_t* pixels, uint32_t best);       // 0x7ad810
uint32_t rtrymapblock(const uint32_t* src, uint32_t raw0, uint32_t raw1);  // 0x7ade70
uint32_t rbtrymapblock(const uint32_t* src, uint32_t raw0, uint32_t raw1); // 0x7ae0b0

union DxtColor {
    uint32_t u;
    struct { uint8_t b, g, r, a; } c;
};

// 565 colour as separate channel bytes (b, g, r).
struct Rgb565 {
    uint8_t b, g, r, pad;
};

#define RGB888TO565(x) (((((x) >> 3) & 0x1f0000 | (x) & 0xfc00) >> 2 | (x) & 0xf8) >> 3)
#define CLAMP0(x)      ((x) < 0 ? 0 : (x))
#define MIN(a, b)      ((a) < (b) ? (a) : (b))
#define MAX(a, b)      ((a) > (b) ? (a) : (b))

struct EndpointColors {
    uint32_t v[2];
    uint32_t findendpoints(const uint32_t* pixels, uint32_t* out0, uint32_t* out1, int alpha, int quality);
};

uint32_t EndpointColors::findendpoints(const uint32_t* pixels, uint32_t* out0, uint32_t* out1,
                                       int alpha, int quality)
{
    const uint32_t* colors = v;
    DxtColor c0, c1;
    uint32_t map[257];
    c0.u = colors[0];
    c1.u = colors[1];
    map[0] = 0;

    uint32_t thresh = 4;
    if (quality >= 40) thresh = 3;
    if (quality >= 60) thresh = 1;
    if (quality >= 70) thresh = 0;

    uint32_t e0 = RGB888TO565(c1.u);
    uint32_t e1 = RGB888TO565(c0.u);
    uint32_t best = 0x7fffffff;

    if (quality >= 5)
    {
        best = trymapblock(e0, e1, map, pixels, best);
        if (best > thresh)
        {
            if (quality < 10)
            {
                uint32_t err = trymapblock(e1, e0, map, pixels, best);
                if (err < best)
                {
                    uint32_t t = e0;
                    best = err;
                    e0 = e1;
                    e1 = t;
                }
            }
            else
            {
                for (int i = 0; i < 16; ++i)
                {
                    uint32_t a = RGB888TO565(pixels[i]);
                    for (int j = 0; j < 16; ++j)
                    {
                        uint32_t b = RGB888TO565(pixels[j]);
                        if (a > b)
                        {
                            uint32_t err = trymapblock(a, b, map, pixels, best);
                            if (err < best)
                            {
                                best = err;
                                e0 = a;
                                e1 = b;
                                if (err <= thresh)
                                    goto done;
                            }
                        }
                    }
                }
            }
        }
    }

    for (int pass = 0; pass < 1; ++pass)
    {
        if (quality > 10)
        {
            // Extrapolated 888 box: lo = 2*c0 - c1, hi = 2*c1 - c0.
            uint8_t lo8r = (uint8_t)CLAMP0((int)c0.c.r * 2 - (int)c1.c.r);
            uint8_t lo8g = (uint8_t)CLAMP0((int)c0.c.g * 2 - (int)c1.c.g);
            uint8_t lo8b = (uint8_t)CLAMP0((int)c0.c.b * 2 - (int)c1.c.b);
            int x;
            uint8_t hi8r, hi8g, hi8b;
            x = (int)c1.c.r * 2 - (int)c0.c.r;  hi8r = x > 0xff ? 0xff : (uint8_t)x;
            x = (int)c1.c.g * 2 - (int)c0.c.g;  hi8g = x > 0xff ? 0xff : (uint8_t)x;
            x = (int)c1.c.b * 2 - (int)c0.c.b;  hi8b = x > 0xff ? 0xff : (uint8_t)x;

            Rgb565 lo, hi;
            lo.r = (uint8_t)CLAMP0((int)(lo8r >> 3) - 1);
            lo.g = (uint8_t)CLAMP0((int)(lo8g >> 2) - 1);
            lo.b = (uint8_t)CLAMP0((int)(lo8b >> 3) - 1);
            x = (hi8r >> 3) + 2;  hi.r = x > 0x1f ? 0x1f : (uint8_t)x;
            x = (hi8g >> 2) + 2;  hi.g = x > 0x3f ? 0x3f : (uint8_t)x;
            x = (hi8b >> 3) + 2;  hi.b = x > 0x1f ? 0x1f : (uint8_t)x;

            // Search boxes around e0 (lo0..hi0) and e1 (lo1..hi1).
            Rgb565 lo0, hi0, lo1, hi1;
            if (quality >= 100)
            {
                lo0 = lo;
                lo1 = lo;
                hi0 = hi;
                hi1 = hi;
            }
            else
            {
                uint32_t dn = quality / 50;
                uint32_t up = quality / 40 + 1;
                uint32_t r, g, b;

                r = (e0 >> 11) & 0x1f;  g = (e0 >> 5) & 0x3f;  b = e0 & 0x1f;
                lo0.r = (uint8_t)MAX((uint32_t)lo.r, r - dn);
                lo0.g = (uint8_t)MAX((uint32_t)lo.g, g - dn);
                lo0.b = (uint8_t)MAX((uint32_t)lo.b, b - dn);
                hi0.r = (uint8_t)MIN(MIN((uint32_t)hi.r, r + up), 0x1fu);
                hi0.g = (uint8_t)MIN(MIN((uint32_t)hi.g, g + up), 0x3fu);
                hi0.b = (uint8_t)MIN(MIN((uint32_t)hi.b, b + up), 0x1fu);

                r = (e1 >> 11) & 0x1f;  g = (e1 >> 5) & 0x3f;  b = e1 & 0x1f;
                lo1.r = (uint8_t)MAX((uint32_t)lo.r, r - dn);
                lo1.g = (uint8_t)MAX((uint32_t)lo.g, g - dn);
                lo1.b = (uint8_t)MAX((uint32_t)lo.b, b - dn);
                hi1.r = (uint8_t)MIN(MIN((uint32_t)hi.r, r + up), 0x1fu);
                hi1.g = (uint8_t)MIN(MIN((uint32_t)hi.g, g + up), 0x3fu);
                hi1.b = (uint8_t)MIN(MIN((uint32_t)hi.b, b + up), 0x1fu);
            }

            // Vary e0 with e1 fixed.
            if (quality >= 20)
            {
                for (uint32_t r = lo0.r; r <= hi0.r; ++r)
                    for (uint32_t b = lo0.b; b <= hi0.b; ++b)
                        for (uint32_t g = lo0.g; g <= hi0.g; ++g)
                        {
                            uint32_t c = ((r << 6 | g) << 5) | b;
                            if (c > e1)
                            {
                                uint32_t err = trymapblock(c, e1, map, pixels, best);
                                if (err < best)
                                {
                                    best = err;
                                    e0 = c;
                                    if (err <= thresh)
                                        goto done;
                                }
                            }
                        }
            }

            // Vary e1 with e0 fixed.
            if (quality >= 25)
            {
                for (uint32_t r = lo1.r; r <= hi1.r; ++r)
                    for (uint32_t b = lo1.b; b <= hi1.b; ++b)
                        for (uint32_t g = lo1.g; g <= hi1.g; ++g)
                        {
                            uint32_t c = ((r << 6 | g) << 5) | b;
                            if (e0 > c)
                            {
                                uint32_t err = trymapblock(e0, c, map, pixels, best);
                                if (err < best)
                                {
                                    best = err;
                                    e1 = c;
                                    if (err <= thresh)
                                        goto done;
                                }
                            }
                        }
            }

            // Vary both: red pairs, then red/blue pairs, pre-screened by the
            // partial-channel error bounds.
            if (quality >= 30)
            {
                for (uint32_t r0 = lo0.r; r0 <= hi0.r; ++r0)
                    for (uint32_t r1 = lo1.r; r1 <= hi1.r; ++r1)
                    {
                        if (!(r0 > r1 || quality >= 50))
                            continue;
                        if (rtrymapblock(pixels, r0, r1) >= best)
                            continue;
                        for (uint32_t b0 = lo0.b; b0 <= hi0.b; ++b0)
                            for (uint32_t b1 = lo1.b; b1 <= hi1.b; ++b1)
                            {
                                uint32_t err = rbtrymapblock(pixels, b0 | r0 << 11, r1 << 11 | b1);
                                if (err < best)
                                {
                                    for (uint32_t g0 = lo0.g; g0 <= hi0.g; ++g0)
                                    {
                                        uint32_t ca = ((r0 << 6 | g0) << 5) | b0;
                                        for (uint32_t g1 = lo1.g; g1 <= hi1.g; ++g1)
                                        {
                                            uint32_t cb = ((r1 << 6 | g1) << 5) | b1;
                                            if (ca > cb || quality >= 60)
                                            {
                                                uint32_t e = trymapblock(ca, cb, map, pixels, best);
                                                if (e < best)
                                                {
                                                    best = e;
                                                    e0 = ca;
                                                    e1 = cb;
                                                    if (e <= thresh)
                                                        goto done;
                                                }
                                                else if (e - best > 16)
                                                {
                                                    ++g1;
                                                }
                                            }
                                        }
                                    }
                                }
                                else if (err - best > 0x1000)
                                {
                                    ++b1;
                                }
                            }
                    }
            }

            if (quality == 100)
                break;
        }
    }

done:
    if (!alpha && c0.c.a < 0x80 && e0 > e1)
    {
        uint32_t t = e0;
        e0 = e1;
        e1 = t;
    }
    *out0 = e0;
    *out1 = e1;
    return best;
}

// ---------------------------------------------------------------------------
// Callees that the original reaches through compiler-chosen register conventions (see the
// nonmatching notes); declared here with the same argument values.
struct __m64_t { uint32_t lo, hi; };
void FUN_007ae840(const uint8_t* src, int stride, void* copy, uint32_t* out);        // 0x007ae840 (MMX min/max)
void FUN_007ae5b0(const uint8_t* src, uint8_t* dst, int stride);                     // 0x007ae5b0
void InterpolatedAlphaBlock(int hi, int lo, const uint8_t* src, uint8_t* dst);       // 0x007ae660
uint32_t RefineMinMaxColors(const uint32_t* px, uint32_t* out);                      // 0x007ae2a0
void FUN_007adcf0(const uint32_t* src, uint8_t* dst, uint32_t cB, uint32_t cA);      // 0x007adcf0
void mapblock(const uint32_t* src, uint8_t* dst, uint32_t c0, uint32_t c1, int mode); // 0x007ada40

// @ 0x007af490
// eadxt: compress `nblocks` 4x4 blocks of 32-bit pixels (rows `stride` bytes apart) into DXT blocks.
// flags: 0x100 = DXT3 explicit alpha, 0x200 = DXT5 interpolated alpha, nonzero = punch-through/alpha
// mapping; quality < 10 uses the fast endpoint mapper, otherwise the endpoint search.
void eadxt(uint8_t* dst, const uint8_t* src, int stride, int nblocks, uint32_t flags, int quality)
{
    for (int i = 0; i < nblocks; ++i) {
        uint32_t block[16];
        EndpointColors mm;
        FUN_007ae840(src, stride, block, mm.v);
        if (flags & 0x100) {
            FUN_007ae5b0((const uint8_t*)block, dst, 0x10);
            dst += 8;
        } else if (flags & 0x200) {
            InterpolatedAlphaBlock((int)(mm.v[1] >> 24), (int)(mm.v[0] >> 24), (const uint8_t*)block, dst);
            dst += 8;
        }
        if (quality < 10 && flags != 0) {
            if (quality >= 5 && ((mm.v[1] - mm.v[0]) & 0xf8f8f8) != 0)
                RefineMinMaxColors(block, mm.v);
            FUN_007adcf0(block, dst, mm.v[0], mm.v[1]);
        } else {
            uint32_t e0, e1;
            mm.findendpoints(block, &e0, &e1, (int)flags, quality);
            mapblock(block, dst, e0, e1, (int)flags);
        }
        src += 0x10;
        dst += 8;
    }
}

// ---------------------------------------------------------------------------
// Write the surface to a stream: opens the stream named by the key at +0x24, writes a 0x18-byte
// header {1, width, height, mip count, 8, format}, then for each mip level its byte size followed by
// its data. Returns false when the stream cannot be opened.
struct IDxtWriter {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7();
    virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13();
    virtual void Write(const void* data, int size);   // slot 14 (+0x38)
};
struct IDxtStream {
    virtual void s0(); virtual void s1();
    virtual void Release();                           // slot 2 (+8)
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual IDxtWriter* GetWriter();                  // slot 6 (+0x18)
    virtual void s7(); virtual void s8();
    virtual void Close();                             // slot 9 (+0x24)
};
struct DxtKey { uint32_t instance, type, group; };
struct IDxtStreamMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11();
    virtual void m12();
    virtual bool Open(const DxtKey* key, IDxtStream** out, int a, int b, int c, int d);   // slot 13 (+0x34)
};
struct DxtMip {
    char pad00[0x1c];
    int mWidth;      // +0x1c
    int mHeight;     // +0x20
    int pad24;
    void* mpData;    // +0x28
};
template <class T> struct StreamRef {
    T* mp;
    StreamRef() : mp(0) {}
    ~StreamRef() { if (mp) mp->Release(); }
};
class DxtImage {
public:
    char pad00[0xc];
    DxtMip** mpMipBegin;       // +0x0c
    DxtMip** mpMipEnd;         // +0x10
    char pad14[0xc];
    IDxtStreamMgr* mpMgr;      // +0x20
    DxtKey mKey;               // +0x24
    uint32_t mFormat;          // +0x30
    int mBlockBytes;           // +0x34
    int mPixelBytes;           // +0x38
    bool WriteStream(int unused);
};

// @ 0x007af720
bool DxtImage::WriteStream(int unused)
{
    (void)unused;
    StreamRef<IDxtStream> stream;
    if (mpMgr->Open(&mKey, &stream.mp, 2, 2, 1, 0)) {
        IDxtWriter* w = stream.mp->GetWriter();
        int n = (int)(mpMipEnd - mpMipBegin);
        uint32_t hdr[6];
        hdr[0] = 1;
        hdr[1] = (uint32_t)mpMipBegin[0]->mWidth;
        hdr[2] = (uint32_t)mpMipBegin[0]->mHeight;
        hdr[3] = (uint32_t)n;
        hdr[4] = 8;
        hdr[5] = mFormat;
        w->Write(hdr, 0x18);
        for (int i = 0; i < n; ++i) {
            DxtMip* mip = mpMipBegin[i];
            int size;
            if (mBlockBytes != 0)
                size = ((mip->mHeight + 3) / 4) * ((mip->mWidth + 3) / 4) * mBlockBytes;
            else
                size = mip->mHeight * mip->mWidth * mPixelBytes;
            w->Write(&size, 4);
            w->Write(mip->mpData, size);
        }
        stream.mp->Close();
        return true;
    }
    return false;
}
