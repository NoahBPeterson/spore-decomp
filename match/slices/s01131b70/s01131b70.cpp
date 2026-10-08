// SNDSTRM streaming layer (rw audio core, VC .NET 2003, /GL+/LTCG): SNDSTRMI_* / SNDSTRM_*
// routines over the global stream-state table at 0x016e61e0 (count 0x016e7bfe).
// Only call-free functions can be byte-exact (manifest.txt); the rest are complete,
// behaviour-equivalent source (nonmatching.txt).  32-bit only.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

namespace rw { namespace audio { namespace core {

static inline int RwFloat2Int(float f)
{
    int r;
    __asm { cvtss2si eax, f }
    __asm { mov r, eax }
    return r;
}

// ---------------------------------------------------------------- filesys Stream
struct Stream {
    void* GetChunk();                 // 0x011e6b50
    int   FUN_011e6bf0();             // 0x011e6bf0
    int   FUN_011e6c40();             // 0x011e6c40
    int   FUN_011e6cc0();             // 0x011e6cc0
    void  ReleaseChunk(void* chunk);  // 0x011e7c70
    void  FUN_011e7b70();             // 0x011e7b70
    void  FUN_011e7cf0();             // 0x011e7cf0
};

struct System {
    void* Alloc(unsigned size, const char* name, int align, int flags);  // 0x0112c820
    void  Free(void* p, int flags);                                       // 0x0112c850
};
extern System* g_pSystem;    // 0x016e61a8

// slice s01130c50 header parser / sync scanner
int      Mp3Player_parseHeader(unsigned char* data, void* self);   // 0x01130c50
unsigned Mp3Player_findSync(unsigned char* data, int len);         // 0x01130d90

// ---------------------------------------------------------------- callees
void*  FUN_0113f250(int handle, void* a, void* b, void* c);   // 0x0113f250
int    FUN_01141150(int h);                                   // 0x01141150
int    FUN_0113fec0(int a);                                   // 0x0113fec0
int    FUN_011406e0(int a);                                   // 0x011406e0
int    FUN_011405e0(int a, void* b);                          // 0x011405e0
int    FUN_01141270(unsigned a);                              // 0x01141270
int    FUN_01141230(void* a, int b);                          // 0x01141230
int    FUN_011411a0(void* a, int b);                          // 0x011411a0
int    FUN_011412b0(int a0, int a1, int a2, int a3, int a4, int a5); // 0x011412b0 SNDI_patchtohdr
int    FUN_01141200(void* a);                                 // 0x01141200
int    FUN_0113f9b0(int handle);                              // 0x0113f9b0
int    FUN_0113f750(int handle);                              // 0x0113f750
int    FUN_0113f720(int handle);                              // 0x0113f720
int    FUN_0113f6c0(int handle);                              // 0x0113f6c0
void   FUN_01133450();                                        // 0x01133450
void   FUN_01133460();                                        // 0x01133460
void   FUN_0113ec90(void* p, int size);                       // 0x0113ec90 SNDMEMI_alloc
void   FUN_011416b0(void* proc);                              // 0x011416b0
int    SNDPKTPLAY_submit(int handle, void* packet);           // 0x0113f5c0

extern uint8_t  g_016e7bfe;     // 0x016e7bfe  stream-state count
extern void*    g_016e61e0[];   // 0x016e61e0  stream-state table
extern int      g_016e7c78;     // 0x016e7c78
extern uint8_t  g_015ba5fe[];   // 0x015ba5fe
extern int      g_015bfe38;     // 0x015bfe38
extern uint8_t  g_014cafd2[];   // 0x014cafd2
extern uint8_t  g_016e7c22;     // 0x016e7c22  callback count
extern void*    g_016e7c58[];   // 0x016e7c58  callback table
extern uint8_t  g_016e7c1c;     // 0x016e7c1c  initialised flag
extern int      g_016e6268;     // 0x016e6268  shutdown list head
extern int      g_016e7c74;     // 0x016e7c74

// ---------------------------------------------------------------- stream state
// Full 0x220-byte layout, addressed by explicit byte offsets (the original overlaps words/bytes).
struct SndStreamState { char m[0x224]; };

static inline int&     fi(SndStreamState* s, int off) { return *(int*)(s->m + off); }
static inline void*&   fp(SndStreamState* s, int off) { return *(void**)(s->m + off); }
static inline uint8_t& fb(SndStreamState* s, int off) { return *(uint8_t*)(s->m + off); }
static inline float&   ff(SndStreamState* s, int off) { return *(float*)(s->m + off); }
static inline uint16_t& fw(SndStreamState* s, int off) { return *(uint16_t*)(s->m + off); }

__forceinline void SndStream_unlink(SndStreamState* self, int nodeOff, int activeOff)
{
    if (ff(self, activeOff) != 0.0f) {
        int* node = (int*)(self->m + nodeOff);
        if ((int)node == g_016e6268)
            g_016e6268 = *node;
        if (*(int*)(self->m + nodeOff + 4) != 0)
            *(int*)(*(int*)(self->m + nodeOff + 4)) = *node;
        if (*node != 0)
            *(int*)(*node + 4) = *(int*)(self->m + nodeOff + 4);
    }
}

struct SndPacket {
    int      field0;
    uint32_t size;
    int      field8;
    void*    channel[8];
};

int  SndStream_parseHeader(unsigned char* data, unsigned len, int a2, SndStreamState* self, unsigned* out);
void SndStream_startStream(SndStreamState* self);
void SndStream_parseData(unsigned int a, int b);
void SndStream_parseChunk();
int  SndStream_purge(int index);
int  SndStream_destroy(int index);
int  SndStream_isHeld(SndStreamState* self);
void SndStream_releaseCallback(int p);
void SndStream_removeLine(unsigned a);
void SndStream_releaseLine(unsigned p);
int  SndStream_getState(int index);

// @ 0x01131b70
// Interpret the current chunk's tag: submit frame length, skip ID3, scan RIFF, etc.
int SndStream_parseHeader(unsigned char* data, unsigned len, int a2, SndStreamState* self, unsigned* out)
{
    if (len < 4) {
        *out = 0;
        return 0;
    }
    int r = Mp3Player_parseHeader(data, self);
    if (r > 0 && r <= (int)len) {
        int v = fi(self, 0xa0) - r;
        fi(self, 0xa0) = v;
        *out = r;
        if (v > 0)
            return 1;
        if (v < 0) {
            *out = 0;
            fi(self, 0xa0) = 0;
        }
        return 2;
    }
    if (r == -2) {
        unsigned v = ((((data[6] & 0x7f) << 7 | (data[7] & 0x7f)) << 7 | (data[8] & 0x7f)) << 7 |
                      (data[9] & 0x7f)) + 10;
        if (v < len) {
            fi(self, 0xa0) -= v;
            *out = v;
            return 1;
        }
    } else if (r == -3) {
        if (len < 0x14)
            return 0;
        if ((((unsigned)data[8] << 24) | ((unsigned)data[9] << 16) | ((unsigned)data[10] << 8) |
             (unsigned)data[11]) != 0x57415645) {
            *out = 0;
            fi(self, 0xa0) = 0;
            return 2;
        }
        unsigned char* p = data + 0xc;
        unsigned char* end = data + len;
        while (p < end) {
            unsigned tag = ((unsigned)p[0] << 24) | ((unsigned)p[1] << 16) |
                           ((unsigned)p[2] << 8) | (unsigned)p[3];
            unsigned sz = ((unsigned)p[4] << 24) | ((unsigned)p[5] << 16) |
                          ((unsigned)p[6] << 8) | (unsigned)p[7];
            if (tag == 0x666d7420) {
                if (sz < 0x10)
                    goto checkp;
                if ((((unsigned)p[8] << 8) | (unsigned)p[9]) != 0x55) {
                    *out = 0;
                    fi(self, 0xa0) = 0;
                    return 2;
                }
            } else if (tag == 0x64617461) {
                p += 8;
                goto checkp;
            }
            p = p + sz + 8;
        }
checkp:
        if (p < end) {
            *out = (unsigned)(p - data);
            return 1;
        }
    } else if (r == -1) {
        fi(self, 0xa0) = 0;
        *out = 0;
        return 2;
    } else if (r == 0) {
        unsigned char* q = (unsigned char*)Mp3Player_findSync(data, (int)len);
        if (q == 0) {
            fi(self, 0xa0) += 3;
            *out = 0;
            return 0;
        }
        unsigned d = (unsigned)(q - data);
        if (d < len) {
            fi(self, 0xa0) -= d;
            fi(self, 0xe4) = 0;
            *out = d;
            return 1;
        }
    }
    *out = 0;
    return 0;
}

// @ 0x01131e00
SndStreamState* SndStream_init(int a0, int a1, int a2, int a3, int a4, SndStreamState* self, int a6, int* out)
{
    fi(self, 0x9c) = a6;
    fi(self, 0x20) = a0;
    fi(self, 0xac) = a2;
    fi(self, 0xa8) = a3;
    fi(self, 0xe0) = a4;
    fi(self, 0x00) = 0;
    fi(self, 0xe8) = 0;
    fi(self, 0xec) = 0;
    fi(self, 0xf0) = 0;
    fi(self, 0x04) = 0;
    fi(self, 0x08) = 0;
    fi(self, 0xe4) = 0;
    fi(self, 0xb8) = 0; fi(self, 0xbc) = 0; fi(self, 0xc0) = 0; fi(self, 0xc4) = 0;
    fi(self, 0xc8) = 0; fi(self, 0xcc) = 0; fi(self, 0xd0) = 0; fi(self, 0xd4) = 0;
    fi(self, 0xd8) = 0; fi(self, 0xdc) = 0;
    fi(self, 0x0c) = -1;
    if (fi(self, 0x9c) == -1)
        fi(self, 0x9c) = ((Stream*)a2)->FUN_011e6cc0();
    fi(self, 0xa0) = fi(self, 0x9c);
    fi(self, 0xa4) = fi(self, 0x00);
    fi(self, 0xa0) = fi(self, 0x9c) - fi(self, 0x00);
    fi(self, 0xb4) = -1;
    *out = fi(self, 0x00);
    SndStream_parseHeader((unsigned char*)a1, (unsigned)a2, 0, self, (unsigned*)out);
    return self;
}

// @ 0x01131f00
// Unlink the six per-stream equalizer nodes that are still active.
void SndStream_unlinkAll(SndStreamState* self)
{
    SndStream_unlink(self, 0x13c, 0x150);
    SndStream_unlink(self, 0x160, 0x174);
    SndStream_unlink(self, 0x184, 0x198);
    SndStream_unlink(self, 0x1a8, 0x1bc);
    SndStream_unlink(self, 0x1cc, 0x1e0);
    SndStream_unlink(self, 0x1f0, 0x204);
}

// @ 0x01132090
void SndStream_startStream(SndStreamState* self)
{
    void* h = FUN_0113f250(fi(self, 0x0c), self->m + 0x18, self->m + 0x20, self->m + 0xe8);
    fi(self, 0x08) = (int)h;
    int n = FUN_01141150((int)h);
    int i = 0;
    if (fb(self, 0x1a) != 0) {
        int off = n * 0x84 + 4;
        do {
            short s = *(short*)(g_016e7c78 + off);
            int node = s * 0x84 + g_016e7c78;
            char c = g_015ba5fe[(unsigned)fb(self, 0x1a) * 6 + i];
            int j = 0;
            if (g_015bfe38 > 0) {
                do {
                    *(int*)(*(int*)(node + 100) + j * 4) = ((int*)fp(self, 0xf8))[j];
                    ++j;
                } while (j < g_015bfe38);
            }
            int v = fi(self, 0x130 + c * 0x24 + 8);
            *(int*)(node + 0x38) = v;
            *(int*)(node + 0x48) = v;
            FUN_0113fec0(s);
            ++i;
            off += 2;
        } while (i < (unsigned)fb(self, 0x1a));
    }
    if (fb(self, 0x16) == 0) {
        unsigned n2 = fb(self, 0x1a);
        unsigned k = 0;
        if (n2 != 0) {
            int off = n * 0x84 + 4;
            do {
                short s = *(short*)(g_016e7c78 + off);
                int node = s * 0x84 + g_016e7c78;
                char c = g_015ba5fe[(unsigned)fb(self, 0x1a) * 6 + k];
                float f = ff(self, 0x130 + c * 0x24);
                if (f == -1.0e6f) {
                    *(uint16_t*)(node + 0x1c) = (uint16_t)((uint16_t)g_014cafd2[k + n2 * 6] << 8);
                } else {
                    *(uint16_t*)(node + 0x1c) = (int16_t)RwFloat2Int(f * 182.04445f);
                    if (fb(self, 0x130 + c * 0x24 + 4) == 0)
                        *(uint16_t*)(node + 0x1c) =
                            (uint16_t)(((uint16_t)g_014cafd2[k + n2 * 6] * 0x100) +
                                       *(uint16_t*)(node + 0x1c));
                }
                FUN_011406e0(s);
                off += 2;
                ++k;
            } while (k < fb(self, 0x1a));
        }
    }
    if (fi(self, 0x10c) != 0)
        FUN_011405e0(fi(self, 0x08), self->m + 0xfc);
    fb(self, 0x14) = 1;
}

// @ 0x01132280
int SndStream_bitrateToFrames(unsigned short* p)
{
    char c = *(char*)((char*)p + 3);
    int v = (int)*p * (int)*(unsigned char*)((char*)p + 2);
    int k = 0;
    if (c == 0xa) k = 0x88;
    else if (c == 4) k = 0x33;
    else if (c == 0x16) k = 0x66;
    else if (c == 8) k = 0x200;
    else if (c == 0x10 || c == 0x17)
        return (int)*(unsigned char*)((char*)p + 2) * 8;
    return (v * k) >> 8;
}

// @ 0x01132300
int SndStream_getState(int index)
{
    if (index < (int)(unsigned)g_016e7bfe && index >= 0)
        return (int)g_016e61e0[index];
    return 0;
}

// @ 0x01132320
void SndStream_removeLine(unsigned a)
{
    SndStreamState* s = (SndStreamState*)g_016e61e0[a & 0xff];
    int v = FUN_01141270(a);
    FUN_01141230(s->m + 0x114, v);
    FUN_011411a0(s->m + 0x120, v);
    if (fi(s, 0x12c) == v)
        fi(s, 0x12c) = 0;
}

// @ 0x01132370
// Release the filesys chunk whose address sits just before this callback record.
void SndStream_releaseCallback(int p)
{
    unsigned d = *(unsigned*)(p - 4);
    SndStreamState* s = (SndStreamState*)g_016e61e0[d & 0xff];
    Stream* stream = *(Stream**)&fi(s, 0x04);
    stream->ReleaseChunk(*(void**)(p - 8));
}

// @ 0x011323a0
void SndStream_releaseLine(unsigned a, unsigned b)
{
    int* node = (int*)(fi((SndStreamState*)a, 0x114));
    int iter = 1;
    (void)b;
    int s = 0;
    for (;;) {
        unsigned v3 = b;
        unsigned v5 = 0;
        if ((unsigned)node[7] < b) {
            v5 = b - node[7];
            v3 = b - v5;
        }
        b = v5;
        node[5] += v3;
        node[7] -= v3;
        if ((unsigned)node[6] <= (unsigned)node[5]) {
            SndStreamState* st = (SndStreamState*)g_016e61e0[node[3] & 0xff];
            int v = FUN_01141270(node[3]);
            FUN_01141230(st->m + 0x114, v);
            FUN_011411a0(st->m + 0x120, v);
            if (fi(st, 0x12c) == v)
                fi(st, 0x12c) = 0;
        }
        if (b == 0)
            return;
        node = (int*)(fi((SndStreamState*)b, 0x114));
        ++iter;
        if (iter > 200) {
            SndStream_removeLine((unsigned)node[3]);
            return;
        }
    }
}

// @ 0x01132450
int SndStream_parseHeaderAndStart(int index, int chunk)
{
    SndStreamState* s = (SndStreamState*)g_016e61e0[index];
    if (fp(s, 0x12c) == 0)
        fp(s, 0x12c) = (void*)fi(s, 0x114);
    else
        fp(s, 0x12c) = *(void**)(int)fp(s, 0x12c);
    int hdr = fi(s, 0x12c);
    int local[7];
    FUN_011412b0(0, *(int*)(chunk + 8) + 8, (int)(s->m + 0x1c), (int)(s->m + 0x84), (int)local, hdr + 0x25);
    *(int*)(hdr + 0x18) = local[0];
    *(unsigned char*)(hdr + 0x24) = 0;
    int* p = (int*)(s->m + 0xc8);
    int cur = *p;
    while (cur != 0) {
        int local30[4];
        local30[0] = 3;
        local30[1] = *p;
        local30[2] = p[4];
        local30[3] = fi(s, 0xc);
        cur = 0;
        *p = 0;
        p[4] = 0;
        ++p;
        if ((char)g_016e7c22 > 0) {
            int k = 0;
            do {
                ((void (*)(void*))g_016e7c58[k])(local30);
                ++k;
            } while (k < (int)(char)g_016e7c22);
        }
        cur = *p;
    }
    Stream* stream = *(Stream**)&fi(s, 0x04);
    stream->ReleaseChunk((void*)chunk);
    fi(s, 0x10) = SndStream_bitrateToFrames((unsigned short*)(s->m + 0x1c));
    if (fi(s, 0x18) == fi(s, 0x1c)) {
        int* a = (int*)(s->m + 0x20);
        int* q = (int*)(s->m + 0x84);
        int same = 1;
        for (int k = 0; k < 25; ++k) {
            if (a[k] != q[k]) { same = 0; break; }
        }
        if (same && fi(s, 0x98) == 0)
            goto lab_a7;
    }
lab73:
    if (fw(s, 0x18) != 0) {
        fb(s, 0x14) = 2;
        return 0;
    }
    {
        int v = fi(s, 0x1c);
        int* dst = (int*)(s->m + 0x20);
        int* src = (int*)(s->m + 0x84);
        for (int k = 0x19; k != 0; --k)
            *dst++ = *src++;
        fi(s, 0x18) = v;
        fi(s, 0x98) = 0;
    }
lab_a7:
    if (fb(s, 0x14) != 1) {
        SndStream_startStream(s);
        fb(s, 0x14) = 1;
    }
    return 0;
}

// @ 0x011325d0
int SndStream_isHeld(SndStreamState* self)
{
    int p = fi(self, 0x12c);
    if (p != 0 && *(int*)(p + 0x10) != 0) {
        if (*(int*)(p + 0x20) < 0)
            return 1;
        if (*(int*)(p + 0x20) != 0) {
            unsigned u = (unsigned)((Stream*)fp(self, 0x04))->FUN_011e6bf0();
            if (u > 4000000u)
                u = 4000000u;
            if ((u * 1000) / *(unsigned*)(p + 0x10) < *(unsigned*)(p + 0x20) &&
                ((Stream*)fp(self, 0x04))->FUN_011e6c40() != 2) {
                if (fi(self, 0x128) > 0)
                    return 1;
                if (((Stream*)fp(self, 0x04))->FUN_011e6c40() != 0)
                    return 1;
                *(int*)(p + 0x20) = 0;
                return 0;
            }
            *(int*)(p + 0x20) = 0;
        }
    }
    return 0;
}

// @ 0x01132660
int SndStream_purge(int index)
{
    if (g_016e7c1c == 0)
        return 0xfffffff6;
    FUN_01133450();
    if (index < (int)(unsigned)g_016e7bfe && index >= 0 &&
        (g_016e61e0[index] != 0)) {
        SndStreamState* s = (SndStreamState*)g_016e61e0[index];
        if (fi(s, 0x08) >= 0)
            FUN_0113f9b0(fi(s, 0x0c));
        fi(s, 0x08) = -1;
        if (fb(s, 0x15) == 0)
            ((Stream*)fp(s, 0x04))->FUN_011e7b70();
        if (fi(s, 0x98) != 0 && fb(s, 0x1e) != 0) {
            int i = 0;
            unsigned char n = fb(s, 0x1e);
            do {
                g_pSystem->Free(fp(s, 0x98 + i * 4), 0);
                ++i;
            } while (i < (int)n);
        }
        for (;;) {
            int v = FUN_01141200(s->m + 0x114);
            if (v == 0)
                break;
            FUN_011411a0(s->m + 0x120, v);
        }
        fi(s, 0x12c) = 0;
        fb(s, 0x14) = 0;
        FUN_0113ec90(s->m + 0x18, 4);
        FUN_0113ec90(s->m + 0x1c, 4);
        FUN_0113ec90(s->m + 0x20, 100);
        FUN_0113ec90(s->m + 0x84, 100);
        FUN_01133460();
        return 0;
    }
    FUN_01133460();
    return 0xfffffff8;
}

// @ 0x01132770
// De-interleave one CSDl chunk into the channel destination pointers and submit it.
void SndStream_parseData(unsigned int a, int b)
{
    SndStreamState* s = (SndStreamState*)a;
    int hdr = fi(s, 0x12c);
    int v7 = *(int*)(b + 8);
    unsigned acc = fi(s, 0x14);
    int swapped = fb((SndStreamState*)hdr, 0x25) != 0;
    unsigned val;
    {
        unsigned v = *(unsigned*)(v7 + 8);
        if (swapped)
            val = (v >> 24) | ((v >> 8) & 0xff00) | ((v << 8) & 0xff0000) | (v << 24);
        else
            val = v;
    }
    acc = acc ^ ((acc ^ val) & 0x7fffffff);
    fi(s, 0x14) = acc;

    unsigned char nch = fb(s, 0x1a);
    int base = v7 + 0xc;
    int end = base + (int)nch * 4;
    int* dest = (int*)(s->m + 0x24);
    for (int i = 0; i < (int)nch; ++i) {
        unsigned vv = *(unsigned*)(base + i * 4);
        if (swapped)
            vv = (vv >> 24) | ((vv >> 8) & 0xff00) | ((vv << 8) & 0xff0000) | (vv << 24);
        dest[i] = end + vv;
    }
    if ((acc & 0x7fffffff) != 0) {
        *(int*)(dest[0] - 8) = b;
        *(int*)(dest[0] - 4) = fi(s, 0x0c);
        fi(s, 0x1c) += (int)(acc & 0x7fffffff);
        unsigned sz = ((unsigned)fb((SndStreamState*)hdr, 0x24) << 31) | (acc & 0x7fffffff);
        SndPacket pkt;
        pkt.field0 = (int)dest[0];
        pkt.size = (uint32_t)(dest[1] - dest[0]);
        pkt.field8 = (int)dest[2];
        pkt.channel[0] = (void*)dest[3];
        (void)sz;
        SNDPKTPLAY_submit(fi(s, 0x0c), &pkt);
        fb((SndStreamState*)hdr, 0x24) = 1;
        return;
    }
    ((Stream*)fp(s, 0x04))->ReleaseChunk((void*)b);
}

// @ 0x011328c0
void SndStream_parseChunk()
{
    FUN_01133450();
    if (g_016e7bfe != 0) {
        int idx = 0;
        int* p = (int*)g_016e61e0;
        do {
            int s = *p;
            if (s != 0 && *(int*)(s + 0x11c) != 0) {
                if (*(char*)(s + 0x14) == 2) {
                    if (!(FUN_0113f720(*(int*)(s + 0xc)) <= 0)) {
                        // skip
                    } else {
                        int v = *(int*)(s + 0xc);
                        int t = *(int*)(s + 0x1c);
                        int* dst = (int*)(s + 0x20);
                        int* src = (int*)(s + 0x84);
                        for (int k = 0x19; k != 0; --k)
                            *dst++ = *src++;
                        *(int*)(s + 0x18) = t;
                        *(int*)(s + 0x98) = 0;
                        FUN_0113f9b0(v);
                        SndStream_startStream((SndStreamState*)s);
                    }
                }
                if (SndStream_isHeld((SndStreamState*)s) == 0) {
                    int n;
                    if (*(char*)(s + 0x14) == 1) {
                        if (FUN_0113f6c0(*(int*)(s + 0xc)) < 1)
                            goto next;
                        n = FUN_0113f6c0(*(int*)(s + 0xc));
                    } else {
                        n = 8;
                    }
                    int got = 0;
                    do {
                        --n;
                        int c = (int)((Stream*)*(int*)(s + 4))->GetChunk();
                        if (c == 0) {
                            if (!got)
                                break;
                        } else if (*(int*)(*(int*)(c + 8)) == 0x6c444353) {
                            SndStream_parseData((unsigned int)*p, c);
                            got = 1;
                        } else if (*(int*)(*(int*)(c + 8)) == 0x6c484353) {
                            int ci = idx;
                            (void)ci;
                            SndStream_parseHeaderAndStart(idx, c);
                            break;
                        } else {
                            ((Stream*)*(int*)(s + 4))->ReleaseChunk((void*)c);
                            got = 1;
                        }
                    } while (n > 0);
                }
            }
next:
            ++idx;
            ++p;
        } while (idx < (int)(unsigned)g_016e7bfe);
    }
    FUN_01133460();
}

// @ 0x01132a10
int SndStream_destroy(int index)
{
    if (g_016e7c1c == 0)
        return 0xfffffff6;
    FUN_01133450();
    if (index < (int)(unsigned)g_016e7bfe && index >= 0 &&
        (g_016e61e0[index] != 0)) {
        SndStreamState* s = (SndStreamState*)g_016e61e0[index];
        SndStream_purge(index);
        SndStream_unlinkAll(s);
        int live = 0;
        for (int i = 0; i < (int)(unsigned)g_016e7bfe; ++i)
            if (g_016e61e0[i] != 0)
                ++live;
        if (live == 1) {
            FUN_011416b0((void*)&SndStream_parseChunk);
            g_016e7c74 = 0;
        }
        FUN_0113f750(fi(s, 0x0c));
        g_016e61e0[index] = 0;
        FUN_01133460();
        if (fb(s, 0x15) == 0)
            ((Stream*)fp(s, 0x04))->FUN_011e7cf0();
        return 0;
    }
    FUN_01133460();
    return 0xfffffff8;
}

} } } // namespace rw::audio::core
