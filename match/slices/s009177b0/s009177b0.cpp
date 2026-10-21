// Slice s009177b0 -- EA colour gradient / HSL helpers and an embedded image-stream
// setup + scan.  Mixed object: EA::IO memory-stream helpers (0x918200..0x9186a0) and
// the Draw2D colour-gradient helpers (0x9176c0..0x918090).
#include "types.h"

// ---- runtime helpers ----
extern "C" void* MemCpyThunk(void* dst, const void* src, unsigned n);   // 0x011e0744
extern "C" void* AllocStream(unsigned n);                               // 0x006abeb0
extern "C" unsigned long long __allshl(unsigned lo, unsigned hi, int sh); // 0x011e06e0

// ---- EA I/O stream ----
struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual int  GetSize();                       // 0x1c
    virtual int  s8();                            // 0x20
    virtual int  GetPosition(int mode);           // 0x24
    virtual bool SetPosition(int pos, int mode);  // 0x28
    virtual int  s11();                           // 0x2c
    virtual int  Read(void* buf, int n);          // 0x30
};

struct MemoryStream : IStream {
    char  pad0[0x24 - 4];
    void* mpHolder;      // +0x24
    void* mpBuffer;      // +0x28
    unsigned mnSize;     // +0x2c
    bool SetData(void* pData, unsigned nSize, unsigned char copy, void* a, void* b); // 0x0093be30
    bool InitA(void* holder);   // 0x009182d0
    bool InitB(void* holder);   // 0x00918620
    bool ReadVarU64(unsigned long long* out);  // 0x00918200
    bool ReadVarS64(long long* out);           // 0x00918260
    bool ReadFixed(void* a1, void* a2, void* buf);  // 0x009186a0
    void* ScanExtra(const void* holder, void* out); // 0x00918350
};

// The holder objects (opaque, only the offsets the slice touches are named).
struct HolderA {
    char pad0[0x284];
    unsigned a284;
    unsigned a288;
    char pad28c[0x4];
    IStream stream4;     // placeholder; the real sub-object lives at +4
};
struct HolderB {
    char pad0[0x2d8];
    unsigned b2d8;
    unsigned char b2dc[0x2];
    unsigned char b2de;
    char pad2df[0x1];
    unsigned b2e0;
    char pad2e4[0x10];
};

// ---- colour helpers ----
struct Rgba5 { float v[5]; };

// round-to-nearest integer, the original's fldcw/fistp sequence
inline int RoundToInt(double d)
{
    int r;
    unsigned short cw;
    __asm {
        fnstcw word ptr cw
        movzx eax, word ptr cw
        or    eax, 0xc00
        push  eax
        fldcw word ptr [esp]
        fld qword ptr d
        fistp dword ptr r
        fldcw word ptr cw
        pop   eax
    }
    return r;
}

// 0x00917600: per-byte mix of two packed colours (a + (b-a)*t).
unsigned MixColor(unsigned a, unsigned b, float t);
// 0x009176c0: linear interpolation of a 5-float colour: dst = lerp(a,b,t), lane 2 mixes.
Rgba5* Lerp(Rgba5* dst, const Rgba5* a, const Rgba5* b, float t);
// 0x00917770: append one colour to the gradient table.
void PushColor(void* self, const Rgba5* c);

// ===== gradient table =====
struct Grad {
    Rgba5*  mpBegin;    // +0x00
    unsigned mnCount;   // +0x04
    unsigned mnCap;     // +0x08
    float   mf0c;       // +0x0c  horizontal low
    float   mf10;       // +0x10  vertical low
    float   mf14;       // +0x14  horizontal high
    float   mf18;       // +0x18  vertical high
    Rgba5   mCur1;      // +0x1c  horizontal current colour
    Rgba5   mCur2;      // +0x30  vertical current colour

    void AddX(const Rgba5* c);   // 0x009177b0
    void AddY(const Rgba5* c);   // 0x00917ac0
    int  SetColors(const Rgba5* colors, int n);  // 0x00917d70 -> returns mnCount
};
// 0x00917e10: free cdecl, 5 args (local's this = lea ecx,[esp+8])
int SetupGrad(const Rgba5* rect, const Rgba5* in, int nIn, Rgba5* out, int nOutMax);

// @ 0x00917600
unsigned MixColor(unsigned a, unsigned b, float t)
{
    unsigned a0 = a & 0xff;
    unsigned a1 = (a >> 8) & 0xff;
    unsigned a2 = (a >> 16) & 0xff;
    unsigned a3 = a >> 24;
    int d1 = (int)((b >> 8) & 0xff) - (int)a1;
    int d3 = (int)(b >> 24) - (int)a3;
    int d2 = (int)((b >> 16) & 0xff) - (int)a2;
    int d0 = (int)(b & 0xff) - (int)a0;
    unsigned r1 = (unsigned)(int)((float)d1 * t) + a1;
    unsigned r3 = (unsigned)(int)((float)d3 * t) + a3;
    unsigned r2 = (unsigned)(int)((float)d2 * t) + a2;
    unsigned r0 = (unsigned)(int)((float)d0 * t) + a0;
    return ((r1 & 0xff) << 8) | ((r3 & 0xff) << 24) | ((r2 & 0xff) << 16) | (r0 & 0xff);
}

// @ 0x009176c0
Rgba5* Lerp(Rgba5* dst, const Rgba5* a, const Rgba5* b, float t)
{
    float b0 = b->v[0], b1 = b->v[1], b3 = b->v[3], b4 = b->v[4];
    float a0 = a->v[0], a1 = a->v[1], a2 = a->v[2], a3 = a->v[3], a4 = a->v[4];
    dst->v[0] = (b0 - a0) * t + a0;
    dst->v[1] = (b1 - a1) * t + a1;
    dst->v[2] = (float)MixColor((unsigned)a2, (unsigned)b->v[2], t);
    dst->v[3] = (b3 - a3) * t + a3;
    dst->v[4] = (b4 - a4) * t + a4;
    return dst;
}

// @ 0x00917770
void PushColor(void* self, const Rgba5* c)
{
    Grad* g = (Grad*)self;
    if (g->mnCount < g->mnCap) {
        *g->mpBegin = *c;
        g->mpBegin = (Rgba5*)((char*)g->mpBegin + 0x14);
    }
    g->mnCount = g->mnCount + 1;
}

// @ 0x009177b0
void Grad::AddX(const Rgba5* c)
{
    float x = c->v[0];
    float lo = mf0c;
    float hi = mf14;
    Rgba5* cur = &mCur1;
    if (lo <= x) {
        float cx = cur->v[0];
        if (hi < x) {
            if (cx < lo) {
                Rgba5 tmp;
                Lerp(&tmp, cur, c, (cx - lo) / (cx - x));
                PushColor(this, &tmp);
            }
            cx = cur->v[0];
            if (cx <= hi) {
                Rgba5 tmp;
                Lerp(&tmp, cur, c, (cx - hi) / (cx - x));
                PushColor(this, &tmp);
            }
            goto tail;
        }
        if (lo <= cx) {
            if (hi < cx) {
                Rgba5 tmp;
                Lerp(&tmp, cur, c, (cx - hi) / (cx - x));
                PushColor(this, &tmp);
            }
        } else {
            Rgba5 tmp;
            Lerp(&tmp, cur, c, (cx - lo) / (cx - x));
            PushColor(this, &tmp);
        }
        if (mnCount < mnCap) {
            *mpBegin = *c;
            mpBegin = (Rgba5*)((char*)mpBegin + 0x14);
        }
    } else {
        float cx = cur->v[0];
        if (hi < cx) {
            float t = (cx - hi) / (cx - x);
            Rgba5 tmp;
            tmp.v[0] = (x - cur->v[0]) * t + cur->v[0];
            tmp.v[1] = (c->v[1] - cur->v[1]) * t + cur->v[1];
            tmp.v[2] = (float)MixColor((unsigned)cur->v[2], (unsigned)c->v[2], t);
            tmp.v[3] = (c->v[3] - cur->v[3]) * t + cur->v[3];
            tmp.v[4] = (c->v[4] - cur->v[4]) * t + cur->v[4];
            if (mnCount < mnCap) {
                *mpBegin = tmp;
                mpBegin = (Rgba5*)((char*)mpBegin + 0x14);
            }
            mnCount = mnCount + 1;
        }
        cx = cur->v[0];
        if (cx < lo)
            goto tail;
        {
            float t = (cx - lo) / (cx - x);
            Rgba5 tmp;
            tmp.v[0] = (x - cur->v[0]) * t + cur->v[0];
            tmp.v[1] = (c->v[1] - cur->v[1]) * t + cur->v[1];
            tmp.v[2] = (float)MixColor((unsigned)cur->v[2], (unsigned)c->v[2], t);
            tmp.v[3] = (c->v[3] - cur->v[3]) * t + cur->v[3];
            tmp.v[4] = (c->v[4] - cur->v[4]) * t + cur->v[4];
            if (mnCount < mnCap) {
                *mpBegin = tmp;
                mpBegin = (Rgba5*)((char*)mpBegin + 0x14);
            }
            mnCount = mnCount + 1;
        }
    }
tail:
    cur->v[0] = c->v[0];
    cur->v[1] = c->v[1];
    cur->v[2] = c->v[2];
    cur->v[3] = c->v[3];
    cur->v[4] = c->v[4];
}

// @ 0x00917ac0
void Grad::AddY(const Rgba5* c)
{
    float y = c->v[1];
    float lo = mf10;
    float hi = mf18;
    if (lo <= y) {
        float cy = mCur2.v[1];
        if (y <= hi) {
            if (lo <= cy) {
                if (cy <= hi)
                    goto tail;
                {
                    float t = (cy - hi) / (cy - y);
                    AddX(Lerp(&mCur2, &mCur2, c, t));
                }
            } else {
                float t = (cy - lo) / (cy - y);
                AddX(Lerp(&mCur2, &mCur2, c, t));
            }
            cy = mCur2.v[1];
            if (hi < cy)
                goto tail;
            {
                float t = (cy - hi) / (cy - y);
                AddX(Lerp(&mCur2, &mCur2, c, t));
            }
            goto tail;
        }
        if (cy < lo) {
            float t = (cy - lo) / (cy - y);
            AddX(Lerp(&mCur2, &mCur2, c, t));
        }
        cy = mCur2.v[1];
        if (hi < cy)
            goto tail;
        {
            float t = (cy - hi) / (cy - y);
            AddX(Lerp(&mCur2, &mCur2, c, t));
        }
        goto tail;
    }
    {
        float cy = mCur2.v[1];
        if (hi < cy) {
            float t = (cy - hi) / (cy - y);
            Rgba5 tmp;
            tmp.v[0] = (y - mCur2.v[1]) * t + mCur2.v[1];
            tmp.v[1] = (c->v[1] - mCur2.v[1]) * t + mCur2.v[1];
            tmp.v[2] = (float)MixColor((unsigned)mCur2.v[2], (unsigned)c->v[2], t);
            tmp.v[3] = (c->v[3] - mCur2.v[3]) * t + mCur2.v[3];
            tmp.v[4] = (c->v[4] - mCur2.v[4]) * t + mCur2.v[4];
            AddX(&tmp);
        }
        cy = mCur2.v[1];
        if (cy < lo)
            goto tail;
        {
            float t = (cy - lo) / (cy - y);
            Rgba5 tmp;
            tmp.v[0] = (y - mCur2.v[1]) * t + mCur2.v[1];
            tmp.v[1] = (c->v[1] - mCur2.v[1]) * t + mCur2.v[1];
            tmp.v[2] = (float)MixColor((unsigned)mCur2.v[2], (unsigned)c->v[2], t);
            tmp.v[3] = (c->v[3] - mCur2.v[3]) * t + mCur2.v[3];
            tmp.v[4] = (c->v[4] - mCur2.v[4]) * t + mCur2.v[4];
            AddX(&tmp);
        }
    }
tail:
    mCur2.v[0] = c->v[0];
    mCur2.v[1] = c->v[1];
    mCur2.v[2] = c->v[2];
    mCur2.v[3] = c->v[3];
    mCur2.v[4] = c->v[4];
}

// @ 0x00917d70
int Grad::SetColors(const Rgba5* colors, int n)
{
    const Rgba5* cur = colors + n - 1;
    mCur2 = *cur;
    mCur1 = *cur;
    for (int i = 0; i < n; ++i) {
        AddY(colors);
        colors = (const Rgba5*)((const char*)colors + 0x14);
    }
    float cy = mCur2.v[1];
    if (cy < mf10 || mf18 < cy)
        AddY(cur);
    return mnCount;
}

// @ 0x00917e10
int SetupGrad(const Rgba5* rect, const Rgba5* in, int nIn, Rgba5* out, int nOutMax)
{
    Grad local;
    local.mf0c = rect->v[0];
    local.mf10 = rect->v[1];
    local.mf14 = rect->v[2];
    local.mf18 = rect->v[3];
    Rgba5 tmp = *in;
    local.mpBegin = out;
    local.mnCap = nOutMax;
    local.mnCount = 0;
    return local.SetColors(in, nIn);
}
// @ 0x00917e70  hue -> channel byte (t in [0,6))
unsigned char HueToByte(double a, double b, double t)
{
    if (t <= 6.0) {
        if (t < 0.0)
            t = t + 6.0;
    } else {
        t = t - 6.0;
    }
    if (t < 1.0)
        return (unsigned char)RoundToInt((a + (b - a) * t) * 255.0);
    if (t < 3.0)
        return (unsigned char)RoundToInt(b * 255.0);
    if (4.0 <= t)
        return (unsigned char)RoundToInt(a * 255.0);
    return (unsigned char)RoundToInt((a + (b - a) * (4.0 - t)) * 255.0);
}

// @ 0x00917f80  HSL -> RGB byte triple
void HslToRgb(float h, float s, float l, unsigned char* r, unsigned char* g, unsigned char* b)
{
    if (l == 0.0f) {
        unsigned char v = (unsigned char)(int)RoundToInt((double)s * 255.0);
        *b = v;
        *g = v;
        *r = v;
        return;
    }
    float c;
    if (0.5f <= s)
        c = (s + l) - l * s;
    else
        c = (l + 1.0f) * s;
    float d = s * 2.0f - c;
    *r = HueToByte((double)d, (double)c, (double)(h + 2.0f));
    *g = HueToByte((double)d, (double)c, (double)h);
    *b = HueToByte((double)d, (double)c, (double)(h - 2.0f));
}

// @ 0x00918090  RGB -> HSL
void RgbToHsl(unsigned char r, unsigned char g, unsigned char b, float* h, float* s, float* l)
{
    unsigned char* pm = &g;
    if (g < r)
        pm = &r;
    if (*pm < b)
        pm = &b;
    unsigned char mx = *pm;
    unsigned char* pn = &g;
    if (r < g)
        pn = &r;
    if (b < *pn)
        pn = &b;
    unsigned char mn = *pn;

    float sum = (float)(int)((unsigned)mx + (unsigned)mn);
    float dif = (float)(int)((unsigned)mx - (unsigned)mn);
    *s = sum * 0.0019607844f;
    if (dif == 0.0f) {
        *l = 0.0f;
        *h = 0.0f;
        return;
    }
    float lum = sum * 0.0019607844f;
    if (lum < 0.5f)
        lum = dif / lum;
    else
        lum = dif / (510.0f - sum);
    *l = lum;
    if (r == mx)
        dif = (float)(int)((unsigned)g - (unsigned)b) / dif;
    else if (g == mx)
        dif = (float)(int)((unsigned)b - (unsigned)r) / dif + 2.0f;
    else if (b == mx)
        dif = (float)(int)((unsigned)r - (unsigned)g) / dif + 4.0f;
    else
        goto done;
    *h = dif;
done:
    if (*h < 0.0f)
        *h = *h + 6.0f;
}

// @ 0x009181e0
bool __fastcall ResetFlag(void* self)
{
    unsigned char* p = (unsigned char*)self + 0x280;
    if (*p != 0)
        *p = 0;
    return true;
}

// @ 0x00918200  read an unsigned varint (LEB128, 7 bits per byte)
bool MemoryStream::ReadVarU64(unsigned long long* out)
{
    *out = 0;
    int shift = 0;
    for (;;) {
        unsigned char b;
        if (Read(&b, 1) != 1)
            return false;
        *out |= (unsigned long long)(b & 0x7f) << shift;
        shift += 7;
        if (shift >= 0x3f)
            return false;
        if (b & 0x80)
            continue;
        return true;
    }
}

// @ 0x00918260  read a signed varint (0x40 = sign bit)
bool MemoryStream::ReadVarS64(long long* out)
{
    *out = 0;
    int shift = 0;
    for (;;) {
        unsigned char b;
        if (Read(&b, 1) != 1)
            return false;
        *out |= (unsigned long long)(b & 0x7f) << shift;
        shift += 7;
        if (shift >= 0x3f)
            return false;
        if (b & 0x80)
            continue;
        if (b & 0x40)
            *out |= (unsigned long long)(long long)(int)(-1 << shift);
        return true;
    }
}

// @ 0x009182d0
bool MemoryStream::InitA(void* holder)
{
    mpHolder = holder;
    int pos = (int)*(unsigned*)((char*)holder + 0x284);
    unsigned sz = *(unsigned*)((char*)holder + 0x288) - pos;
    mnSize = sz;
    mpBuffer = AllocStream(sz);
    IStream* s = (IStream*)((char*)holder + 4);
    if (s->SetPosition(pos, 0)) {
        if (s->Read(mpBuffer, (int)mnSize) == (int)mnSize) {
            SetData(mpBuffer, mnSize, 1, (void*)1, 0);
            return true;
        }
    }
    return false;
}

// @ 0x00918350
void* MemoryStream::ScanExtra(const void* holder, void* out)
{
    MemoryStream* scan = this;
    unsigned char flag = 0;
    unsigned v = 0;
    if (!scan->SetPosition(0, 0))
        return 0;
    unsigned char* end = (unsigned char*)holder + 4;
    for (;;) {
        const Rgba5* pos = (const Rgba5*)scan->GetPosition(0);
        if (!(pos < (const Rgba5*)holder + *(const unsigned*)((const char*)holder + 0x20))) {
            if (flag == 0)
                goto done;
            break;
        }
        unsigned u;
        unsigned short w;
        if (scan->Read(&u, 4) != 4)
            return 0;
        if (scan->Read(&w, 2) != 2)
            return 0;
        if (w != *(const unsigned short*)((const char*)holder + 4))
            return 0;
        if (scan->Read(&v, 4) != 4)
            return 0;
        unsigned char fmt;
        if (scan->Read(&fmt, 1) != 1)
            return 0;
        unsigned char sub;
        if (scan->Read(&sub, 1) != 1)
            return 0;
        unsigned n = (unsigned)fmt * 2;
        n = n - (0xc % n);
        if (!scan->SetPosition((int)n, 1))
            return 0;
        unsigned char* p = (unsigned char*)u + 0xc;
        while (p < end) {
            if (fmt == 4) {
                if (scan->Read(&u, 4) != 4)
                    return 0;
                if (scan->Read(&sub, 4) != 4)
                    return 0;
                u = 0;
                sub = 0;
            } else {
                if (fmt != 8)
                    return 0;
                if (scan->Read(&u, 8) != 8)
                    return 0;
                if (scan->Read(&sub, 8) != 8)
                    return 0;
            }
            if ((size_t)(p + n) < (size_t)end)
                p = p + n;
            else
                break;
        }
        (void)v;
        if (!scan->SetPosition((int)((char*)end - (char*)p), 1))
            return 0;
    }
    {
        char* base = *(char**)((char*)holder + 8);
        *(unsigned*)((char*)out + 8) = (unsigned)*(unsigned*)(base + 0x28c) + v;
        *(unsigned*)((char*)out + 0xc) = *(const unsigned*)((const char*)holder + 0x14) + 0;
    }
done:
    return (void*)(flag != 0);
}

// @ 0x00918620
bool MemoryStream::InitB(void* holder)
{
    mpHolder = holder;
    unsigned sz = *(unsigned*)((char*)holder + 0x2d8) + 4;
    int pos = (int)(*(unsigned*)((char*)holder + 0x2e0) + 0xb);
    mnSize = sz;
    mpBuffer = AllocStream(sz);
    IStream* s = (IStream*)((char*)holder + 4);
    if (s->SetPosition(pos, 0)) {
        if (s->Read(mpBuffer, (int)mnSize) == (int)mnSize) {
            SetData(mpBuffer, mnSize, 1, (void*)1, 0);
            return true;
        }
    }
    return false;
}

// @ 0x009186a0
bool MemoryStream::ReadFixed(void* a, void* b, void* buf)
{
    return Read(buf, (int)*(unsigned char*)((char*)mpHolder + 0x2de)) ==
           (int)*(unsigned char*)((char*)mpHolder + 0x2de);
}
