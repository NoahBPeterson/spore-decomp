// Slice s007c2ab0 — DXT/GIF conversion routines plus a 64-byte aligned struct copy.
// /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"
#include <xmmintrin.h>
#include <string.h>

// ---------------------------------------------------------------------------
// @ 0x007c3b70  64-byte (4x __m128) aligned copy, this=dst, arg=src, ret 4
// ---------------------------------------------------------------------------
struct Mat4 {
    __m128 a, b, c, d;                 // 4 x 16 bytes
    void CopyMat4(const Mat4* src);
};

void Mat4::CopyMat4(const Mat4* src)
{
    a = src->a;
    b = src->b;
    c = src->c;
    d = src->d;
}


// ---- hashtable helpers (0x007c3910, 0x007c3af0) ----
struct HNode { unsigned key; int value; HNode* next; };
struct HIter { HNode* node; HNode** bucket; };
struct HMap {
    HNode** mpBucketArray; unsigned mnBucketCount; unsigned mnElementCount;
    void DoFreeNodes(HNode** b, unsigned n);
    HIter find(const unsigned& k) const;
    int& operator[](const unsigned& k);
};
struct HMapHolder { int pad; HMap m; };
extern HMapHolder gTable;
void FUN_00761130(int);
int FUN_007625d0(const char*);
unsigned FNV1_String8(const char*, unsigned, int);

// @ 0x007c3910
void FUN_007c3910()
{
    HNode* n = *gTable.m.mpBucketArray;
    HNode** p = gTable.m.mpBucketArray;
    if (!n) {
        ++p;
        while (!*p) ++p;
        n = *p;
    }
    HNode* end = gTable.m.mpBucketArray[gTable.m.mnBucketCount];
    while (n != end) {
        FUN_00761130(n->value);
        n = n->next;
        if (!n) { do { n = *++p; } while (!n); }
    }
    gTable.m.DoFreeNodes(gTable.m.mpBucketArray, gTable.m.mnBucketCount);
    gTable.m.mnElementCount = 0;
}

// @ 0x007c3af0
int FUN_007c3af0(const char* name)
{
    unsigned h = FNV1_String8(name, 0x811c9dc5, 2);
    HIter it = gTable.m.find(h);
    int v;
    if (it.node == gTable.m.mpBucketArray[gTable.m.mnBucketCount] || (v = it.node->value) == 0) {
        v = FUN_007625d0(name);
        if (v) gTable.m[h] = v;
    }
    return v;
}

// ---- DXT block decoders ----

// Builds the two DXT colour endpoints (RGB565 -> 8888) and the two interpolated colours.
static inline unsigned DXT_Expand565(unsigned c)
{
    unsigned t = (c & 0xf800) * 0x20 + (c & 0x1f);
    return (((c & 0x7e0) * 0x20 + ((c & 0x7e0) >> 1)) & 0xff00) + (((t >> 2) + t * 8) & 0xff00ff);
}

// @ 0x007c2ab0
void ConvertDXT3ToARGB8888(uint8_t* dst, int dstStride, const uint8_t* src, int srcStride, int width, int height)
{
    int bw = (width + 3) >> 2;
    int bh = (height + 3) >> 2;
    if (bw == 0 || bh == 0) return;
    do {
        uint8_t* d0 = dst;
        uint8_t* d1 = dst + dstStride;
        uint8_t* d2 = dst + dstStride * 2;
        uint8_t* d3 = dst + dstStride * 3;
        const uint8_t* s = src;
        int n = bw;
        do {
            uint32_t col[4];
            col[0] = DXT_Expand565(*(const uint16_t*)(s + 8));
            col[1] = DXT_Expand565(*(const uint16_t*)(s + 10));
            uint32_t a1 = (col[1] >> 8) & 0xff00ff;
            uint32_t a0 = (col[0] >> 8) & 0xff00ff;
            int t = a0 * 0xab + a1 * 0x55;
            uint32_t idx = *(const uint32_t*)(s + 12);
            col[2] = ((((col[0] & 0xff00ff) * 0xab + 0x800080 + (col[1] & 0xff00ff) * 0x55) >> 8 ^ (t - 0x7fff80u)) & 0xff00ff) ^ (t + 0x800080u);
            t = a1 * 0xab + a0 * 0x55;
            col[3] = ((((col[1] & 0xff00ff) * 0xab + 0x800080 + (col[0] & 0xff00ff) * 0x55) >> 8 ^ (t - 0x7fff80u)) & 0xff00ff) ^ (t + 0x800080u);

            uint32_t lo = *(const uint32_t*)(s + 0) & 0x0f0f0f0f;
            uint32_t hi = *(const uint32_t*)(s + 0) & 0xf0f0f0f0;
            uint32_t lo2 = *(const uint32_t*)(s + 4) & 0x0f0f0f0f;
            uint32_t hi2 = *(const uint32_t*)(s + 4) & 0xf0f0f0f0;
            uint32_t A = lo * 0x11;
            uint32_t B = hi + (hi >> 4);
            uint32_t C = lo2 * 0x11;
            uint32_t D = hi2 + (hi2 >> 4);
            ((uint32_t*)d0)[0] = A * 0x1000000 + col[idx & 3];
            ((uint32_t*)d0)[1] = B * 0x1000000 + col[(idx >> 2) & 3];
            ((uint32_t*)d0)[2] = (A & 0xffffff00) * 0x10000 + col[(idx >> 4) & 3];
            ((uint32_t*)d0)[3] = (B & 0xffffff00) * 0x10000 + col[(idx >> 6) & 3];
            ((uint32_t*)d1)[0] = (A & 0xffff0000) * 0x100 + col[(idx >> 8) & 3];
            ((uint32_t*)d1)[1] = (B & 0xffff0000) * 0x100 + col[(idx >> 10) & 3];
            ((uint32_t*)d1)[2] = (A & 0xff000000) + col[(idx >> 12) & 3];
            ((uint32_t*)d1)[3] = (B & 0xff000000) + col[(idx >> 14) & 3];
            ((uint32_t*)d2)[0] = C * 0x1000000 + col[(idx >> 16) & 3];
            ((uint32_t*)d2)[1] = D * 0x1000000 + col[(idx >> 18) & 3];
            ((uint32_t*)d2)[2] = (C & 0xffffff00) * 0x10000 + col[(idx >> 20) & 3];
            ((uint32_t*)d2)[3] = (D & 0xffffff00) * 0x10000 + col[(idx >> 22) & 3];
            ((uint32_t*)d3)[0] = (C & 0xffff0000) * 0x100 + col[(idx >> 24) & 3];
            ((uint32_t*)d3)[1] = (D & 0xffff0000) * 0x100 + col[(idx >> 26) & 3];
            ((uint32_t*)d3)[2] = (C & 0xff000000) + col[(idx >> 28) & 3];
            ((uint32_t*)d3)[3] = (D & 0xff000000) + col[idx >> 30];
            d0 += 16; d1 += 16; d2 += 16; d3 += 16; s += 16;
        } while (--n);
        src += srcStride;
        dst += dstStride * 4;
    } while (--bh);
}

// @ 0x007c2ee0  DXT5 variant (interpolated alpha)
void ConvertDXT5ToARGB8888(uint8_t* dst, int dstStride, const uint8_t* src, int srcStride, int width, int height)
{
    int bw = (width + 3) >> 2;
    int bh = (height + 3) >> 2;
    if (bw == 0 || bh == 0) return;
    do {
        uint8_t* d0 = dst;
        uint8_t* d1 = dst + dstStride;
        uint8_t* d2 = dst + dstStride * 2;
        uint8_t* d3 = dst + dstStride * 3;
        const uint8_t* s = src;
        int n = bw;
        do {
            uint32_t col[4];
            uint32_t al[8];
            col[0] = DXT_Expand565(*(const uint16_t*)(s + 8));
            col[1] = DXT_Expand565(*(const uint16_t*)(s + 10));
            uint32_t a1 = (col[1] >> 8) & 0xff00ff;
            uint32_t a0 = (col[0] >> 8) & 0xff00ff;
            int t = a0 * 0xab + a1 * 0x55;
            uint32_t idx = *(const uint32_t*)(s + 12);
            col[2] = ((((col[0] & 0xff00ff) * 0xab + 0x800080 + (col[1] & 0xff00ff) * 0x55) >> 8 ^ (t - 0x7fff80u)) & 0xff00ff) ^ (t + 0x800080u);
            t = a1 * 0xab + a0 * 0x55;
            col[3] = ((((col[1] & 0xff00ff) * 0xab + 0x800080 + (col[0] & 0xff00ff) * 0x55) >> 8 ^ (t - 0x7fff80u)) & 0xff00ff) ^ (t + 0x800080u);

            uint16_t w0 = *(const uint16_t*)(s + 2);
            uint16_t w1 = *(const uint16_t*)(s + 4);
            uint16_t w2 = *(const uint16_t*)(s + 6);
            uint32_t d32 = *(const uint32_t*)(s + 2);
            uint32_t e0 = s[0] * 0x1000000u + 0x800000;
            uint32_t e1 = s[1] * 0x1000000u + 0x800000;
            al[0] = s[0] * 0x1000000u;
            al[1] = s[1] * 0x1000000u;
            if (e1 < e0) {
                uint32_t step = (e0 - e1) / 7;
                uint32_t v = e0 - step;
                al[2] = v & 0xff000000;
                v -= step; al[3] = v & 0xff000000;
                v -= step; al[4] = v & 0xff000000;
                v -= step; al[5] = v & 0xff000000;
                v -= step; al[6] = v & 0xff000000;
                v -= step; al[7] = v & 0xff000000;
            } else {
                uint32_t step = (e1 - e0) / 5;
                uint32_t v = e0 + step;
                al[2] = v & 0xff000000;
                v += step; al[3] = v & 0xff000000;
                v += step; al[4] = v & 0xff000000;
                v += step; al[5] = v & 0xff000000;
                al[6] = 0;
                al[7] = 0xff000000;
            }
            ((uint32_t*)d0)[0] = al[w0 & 7] + col[idx & 3];
            ((uint32_t*)d0)[1] = al[(w0 & 0x38) >> 3] + col[(idx >> 2) & 3];
            ((uint32_t*)d0)[2] = al[(w0 & 0x1c0) >> 6] + col[(idx >> 4) & 3];
            ((uint32_t*)d0)[3] = al[(w0 & 0xe00) >> 9] + col[(idx >> 6) & 3];
            ((uint32_t*)d1)[0] = al[(w0 & 0x7000) >> 12] + col[(idx >> 8) & 3];
            ((uint32_t*)d1)[1] = al[(d32 >> 15) & 7] + col[(idx >> 10) & 3];
            ((uint32_t*)d1)[2] = al[(w1 & 0x1c) >> 2] + col[(idx >> 12) & 3];
            ((uint32_t*)d1)[3] = al[(w1 & 0xe0) >> 5] + col[(idx >> 14) & 3];
            ((uint32_t*)d2)[0] = al[(w1 & 0x700) >> 8] + col[(idx >> 16) & 3];
            ((uint32_t*)d2)[1] = al[(w1 & 0x3800) >> 11] + col[(idx >> 18) & 3];
            ((uint32_t*)d2)[2] = al[((w1 >> 14) + w2 * -4) & 7] + col[(idx >> 20) & 3];
            ((uint32_t*)d2)[3] = al[(w2 >> 1) & 7] + col[(idx >> 22) & 3];
            ((uint32_t*)d3)[0] = al[(w2 >> 4) & 7] + col[(idx >> 24) & 3];
            ((uint32_t*)d3)[1] = al[(w2 >> 7) & 7] + col[(idx >> 26) & 3];
            ((uint32_t*)d3)[2] = al[(w2 >> 10) & 7] + col[(idx >> 28) & 3];
            ((uint32_t*)d3)[3] = al[w2 >> 13] + col[idx >> 30];
            d0 += 16; d1 += 16; d2 += 16; d3 += 16; s += 16;
        } while (--n);
        src += srcStride;
        dst += dstStride * 4;
    } while (--bh);
}

// ---- animated GIF writer ----
#include <string.h>

void* __cdecl operator new(size_t size, const char* tag, int, int, int, int);   // 0x00f473a0
inline void* operator new(size_t, void* p) { return p; }
void __cdecl operator_delete_array(void* p);                                    // 0x00f47380

// ---- external helpers --------------------------------------------------------------------------
struct IStream_ {                         // EA::IO::FileStream
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void Close();                 // +0x18
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18();
    virtual void SetAccessFlags(int a, int b, int c, int d);   // +0x4c
};
struct FileStream_ : IStream_ { FileStream_(const char* path); char pad[0x22c - 4]; };  // 0x00931da0

struct GifInfo {                          // 0x2a70 bytes
    char pad0[0xc];
    unsigned frameIndex;                  // +0x0c
    unsigned width;                       // +0x10 (scaled)
    int height;                           // +0x14
    int bits1;                            // +0x18
    int bits2;                            // +0x1c
    char pad1[4];
    int numColors;                        // +0x24
    char pad2[0x438 - 0x28];
    int flag;                             // +0x438
    char pad3[0x2a60 - 0x43c];
    float delay;                          // +0x2a60
    char pad4[0x2a70 - 0x2a64];
};
struct GifWriter {                        // local object at +0x44
    char pad[0x40];
    GifWriter();                          // 0x0087cf40
    void SetStream(FileStream_* s);       // 0x0087cf60
    char Begin(int a, unsigned nFrames);  // 0x0087d2a0
    void WriteFrame(GifInfo* i, void* data, unsigned w);   // 0x0087d030
    void Finish();                        // 0x0087cff0
    ~GifWriter();                         // 0x0087d260
};
struct BitmapSrc {
    char pad[0xc];
    unsigned short width;                 // +0xc
    unsigned short height;                // +0xe
    unsigned char bpp;                    // +0x10
    void FillSpriteTexture(void* buf, unsigned size, int flag);   // 0x011f0440
};
void __cdecl ColorReduce(void* src, void* dst, GifInfo* info, unsigned w, unsigned h, int bits);   // 0x007c2790

struct SaveArea { virtual void v0(); virtual void v1(); virtual void v2();
    virtual int GetType();                // +0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual const wchar_t* GetPath(); };  // +0x28
SaveArea* __cdecl GetSaveArea(unsigned id);          // 0x006b1f90 (id is a key value, not a pointer)
extern const wchar_t kDefaultSavePath[];             // 0x013ec468
static const unsigned kSaveAreaId = 0x011ac198;      // save-area key (an id value; points into .text, not data)

struct StrBuf {                           // eastl::basic_string<char> in place
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void sprintf(const char* fmt, ...);   // 0x00472fe0
    ~StrBuf() { if (mpCapacity - mpBegin > 1 && mpBegin) operator_delete_array(mpBegin); }
};
extern char gEmptyStr[];                  // 0x01667bac

struct Prop { int data; char pad[0xc]; unsigned char flags; char pad2; short type; };
struct IPropList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual Prop* GetProperty(unsigned id);                    // +0x28
};
extern IPropList* sAppProperties;                              // 0x015fd918
extern float gDefaultDelay;                                    // 0x015d1168

struct MsgRC {
    void* vftable; volatile int refCount; char pad[0x28]; unsigned mId; char pad2[4]; unsigned mRCFlags;
    void Destruct();                                           // SlotMessage::Destruct 0x00421cf0
};
extern void* vtbl_BehaviorMessage;                             // 0x013eb90c
extern void* vtbl_MessageRC;                                   // 0x013eb844
void __cdecl SetMessageString8(MsgRC* m, int idx, const char* s);   // 0x00618bd0
struct IMessageServer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void PostMessage(unsigned id, MsgRC* m, int flag); };   // +0x14
IMessageServer* __cdecl MessageServer();                       // 0x0067dcc0

// @ 0x007c3410
bool WriteAnimatedCSAGIF(BitmapSrc* bmp, unsigned scale, const char* name, const unsigned* order,
                         unsigned nFrames, float delay, bool padEnd, bool sendMsg)
{
    const wchar_t* dir = kDefaultSavePath;
    SaveArea* sa = GetSaveArea(kSaveAreaId);
    if (sa && sa->GetType() == 0x34728492)
        dir = sa->GetPath();

    StrBuf path;
    path.mpBegin = gEmptyStr; path.mpEnd = gEmptyStr; path.mpCapacity = gEmptyStr + 1;
    path.sprintf("%ls%s.gif", dir, name);

    if (bmp) {
        unsigned s = bmp->width / scale;
        unsigned s2 = s * s;
        FileStream_* fs = (FileStream_*)operator new(0x22c, "Graphics/GIFUtils", 0, 0, 0, 0);
        FileStream_* stream = fs ? new (fs) FileStream_(path.mpBegin) : 0;

        GifWriter gif;
        GifInfo info;
        memset(&info, 0, sizeof(info));
        info.width = bmp->width / s;
        info.numColors = 0x100;
        info.flag = 1;
        info.height = bmp->height / s;
        info.bits1 = 8;
        info.bits2 = 8;
        if (delay == 0.0f) {
            Prop* p = sAppProperties->GetProperty(0x5893f01);
            float* pf;
            if (p->type == 0xd || p->type == 0x10) {
                if (p->flags & 0x30) pf = (float*)p->data;
                else pf = (float*)(-(unsigned)(p->type != 0) & (unsigned)p);
            } else {
                pf = &gDefaultDelay;
            }
            delay = *pf;
        }
        info.delay = delay;
        stream->SetAccessFlags(3, 2, 1, 0);
        gif.SetStream(stream);
        if (gif.Begin(7, padEnd ? nFrames + 10 : nFrames)) {
            int bits = bmp->bpp * bmp->height * bmp->width;
            unsigned size = (bits + ((bits >> 31) & 7)) >> 3;
            void* full = operator new(size, "Graphics/GIFTemp", 0, 0, 0, 0);
            memset(full, 0, size);
            bmp->FillSpriteTexture(full, size, 0);
            size >>= 2;
            void* reduced = operator new(size, "Graphics/GIFTemp", 0, 0, 0, 0);
            memset(reduced, 0, size);
            ColorReduce(full, reduced, &info, bmp->width, bmp->height, info.bits1);
            size /= s2;
            void* frameBuf = operator new(size, "Graphics/GIFTemp", 0, 0, 0, 0);
            memset(frameBuf, 0, size);

            for (unsigned i = 0; i < nFrames; ++i) {
                unsigned j = i;
                if (order) {
                    for (unsigned k = 0; k < nFrames; ++k) {
                        if (order[k] == i) { j = k; break; }
                    }
                }
                unsigned stride = info.width * s2 / s;
                char* src = (char*)reduced + ((j / s * info.height * s) + j % s) * info.width;
                char* dst = (char*)frameBuf;
                for (int r = 0; r < info.height; ++r) {
                    memcpy(dst, src, info.width);
                    src += stride;
                    dst += info.width;
                }
                info.frameIndex = j;
                gif.WriteFrame(&info, frameBuf, info.width);
            }
            if (padEnd) {
                for (int n = 10; n != 0; --n)
                    gif.WriteFrame(&info, frameBuf, info.width);
            }
            operator_delete_array(full);
            operator_delete_array(reduced);
            operator_delete_array(frameBuf);
            gif.Finish();
            stream->Close();
            if (sendMsg) {
                MsgRC msg;
                msg.mId = 0;
                msg.vftable = vtbl_BehaviorMessage;
                msg.refCount = 0;
                msg.vftable = vtbl_MessageRC;
                msg.mRCFlags = 0;
                msg.mId = 0x58b8059;
                SetMessageString8(&msg, 0, path.mpBegin);
                MessageServer()->PostMessage(msg.mId, &msg, 0);
                msg.Destruct();
            }
        }
    }
    return false;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
