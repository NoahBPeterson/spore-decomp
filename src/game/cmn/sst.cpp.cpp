// src/game/cmn/sst.cpp.cpp -- migrated from slice(s) s01131b70 by tools/migrate/rewrite.py
// Object file: cmn/sst.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "sse_helpers.h"
#include "rw/audio/core/System.h"

// ---- items of slice s01131b70 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
static inline int RwFloat2Int(float f)
{
    return SseRoundToInt(f);
}
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Stream {
    void* GetChunk();                 // 0x011e6b50
    int   FUN_011e6bf0();             // 0x011e6bf0
    int   FUN_011e6c40();             // 0x011e6c40
    int   FUN_011e6cc0();             // 0x011e6cc0
    void  ReleaseChunk(void* chunk);  // 0x011e7c70
    void  FUN_011e7b70();             // 0x011e7b70
    void  FUN_011e7cf0();             // 0x011e7cf0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class System_s0113_1b70 { public:
    void* Alloc(unsigned size, const char* name, int align, int flags);  // 0x0112c820
    void  Free(void* p, int flags);                                       // 0x0112c850
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern System_s0113_1b70* g_pSystem;    // 0x016e61a8
}
}
}
namespace rw {
namespace audio {
namespace core {
void*  FUN_0113f250(int handle, void* a, void* b, void* c);   // 0x0113f250
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_01141150(int h);                                   // 0x01141150
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_0113fec0(int a);                                   // 0x0113fec0
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_011406e0(int a);                                   // 0x011406e0
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_011405e0(int a, void* b);                          // 0x011405e0
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_01141270(unsigned a);                              // 0x01141270
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_01141230(void* a, int b);                          // 0x01141230
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_011411a0(void* a, int b);                          // 0x011411a0
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_011412b0(int a0, int a1, int a2, int a3, int a4, int a5); // 0x011412b0 SNDI_patchtohdr
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_01141200(void* a);                                 // 0x01141200
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_0113f9b0(int handle);                              // 0x0113f9b0
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_0113f750(int handle);                              // 0x0113f750
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_0113f720(int handle);                              // 0x0113f720
}
}
}
namespace rw {
namespace audio {
namespace core {
int    FUN_0113f6c0(int handle);                              // 0x0113f6c0
}
}
}
namespace rw {
namespace audio {
namespace core {
void   FUN_01133450();                                        // 0x01133450
}
}
}
namespace rw {
namespace audio {
namespace core {
void   FUN_01133460();                                        // 0x01133460
}
}
}
namespace rw {
namespace audio {
namespace core {
void   FUN_0113ec90(void* p, int size);                       // 0x0113ec90 SNDMEMI_alloc
}
}
}
namespace rw {
namespace audio {
namespace core {
void   FUN_011416b0(void* proc);                              // 0x011416b0
}
}
}
namespace rw {
namespace audio {
namespace core {
int    SNDPKTPLAY_submit(int handle, void* packet);           // 0x0113f5c0
}
}
}
namespace rw {
namespace audio {
namespace core {
extern uint8_t  g_016e7bfe;     // 0x016e7bfe  stream-state count
}
}
}
namespace rw {
namespace audio {
namespace core {
struct SndStreamState;
}
}
}
namespace rw {
namespace audio {
namespace core {
extern SndStreamState* g_016e61e0[];   // 0x016e61e0  stream-state table
}
}
}
namespace rw {
namespace audio {
namespace core {
extern int      g_016e7c78;     // 0x016e7c78
}
}
}
namespace rw {
namespace audio {
namespace core {
extern uint8_t  g_015ba5fe[];   // 0x015ba5fe
}
}
}
namespace rw {
namespace audio {
namespace core {
extern int      g_015bfe38;     // 0x015bfe38
}
}
}
namespace rw {
namespace audio {
namespace core {
extern uint8_t  g_014cafd2[];   // 0x014cafd2
}
}
}
namespace rw {
namespace audio {
namespace core {
extern uint8_t  g_016e7c22;     // 0x016e7c22  callback count
}
}
}
namespace rw {
namespace audio {
namespace core {
extern void*    g_016e7c58[];   // 0x016e7c58  callback table
}
}
}
namespace rw {
namespace audio {
namespace core {
extern uint8_t  g_016e7c1c;     // 0x016e7c1c  initialised flag
}
}
}
namespace rw {
namespace audio {
namespace core {
extern int      g_016e6268;     // 0x016e6268  shutdown list head
}
}
}
namespace rw {
namespace audio {
namespace core {
extern int      g_016e7c74;     // 0x016e7c74
}
}
}
namespace rw {
namespace audio {
namespace core {
struct SndStreamState { char m[0x224]; };  // stream-state table 0x016e61e0
}
}
}
namespace rw {
namespace audio {
namespace core {
extern SndStreamState* g_016e61e0[];
}
}
}
namespace rw {
namespace audio {
namespace core {
static inline int&     fi(SndStreamState* s, int off) { return *(int*)(s->m + off); }
}
}
}
namespace rw {
namespace audio {
namespace core {
static inline void*&   fp(SndStreamState* s, int off) { return *(void**)(s->m + off); }
}
}
}
namespace rw {
namespace audio {
namespace core {
static inline uint8_t& fb(SndStreamState* s, int off) { return *(uint8_t*)(s->m + off); }
}
}
}
namespace rw {
namespace audio {
namespace core {
static inline float&   ff(SndStreamState* s, int off) { return *(float*)(s->m + off); }
}
}
}
namespace rw {
namespace audio {
namespace core {
static inline uint16_t& fw(SndStreamState* s, int off) { return *(uint16_t*)(s->m + off); }
}
}
}
namespace rw {
namespace audio {
namespace core {
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
}
}
}
namespace rw {
namespace audio {
namespace core {
struct SndPacket {
    int      field0;
    uint32_t size;
    int      field8;
    void*    channel[8];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
void SndStream_startStream(SndStreamState* self);
}
}
}
namespace rw {
namespace audio {
namespace core {
void SndStream_parseData(unsigned int a, int b);
}
}
}
namespace rw {
namespace audio {
namespace core {
void SndStream_parseChunk();
}
}
}
namespace rw {
namespace audio {
namespace core {
int  SndStream_purge(int index);
}
}
}
namespace rw {
namespace audio {
namespace core {
int  SndStream_destroy(int index);
}
}
}
namespace rw {
namespace audio {
namespace core {
int  SndStream_isHeld(SndStreamState* self);
}
}
}
namespace rw {
namespace audio {
namespace core {
void SndStream_releaseCallback(int p);
}
}
}
namespace rw {
namespace audio {
namespace core {
void SndStream_removeLine(unsigned a);
}
}
}
namespace rw {
namespace audio {
namespace core {
void SndStream_releaseLine(int unused, unsigned b, SndStreamState* self);
}
}
}
namespace rw {
namespace audio {
namespace core {
int  SndStream_getState(int index);
}
}
}
// ---- items of slice s01131b70 end

// @ 0x01131f00
namespace rw { namespace audio { namespace core {
void SndStream_unlinkAll(SndStreamState* self)
{
    SndStream_unlink(self, 0x13c, 0x150);
    SndStream_unlink(self, 0x160, 0x174);
    SndStream_unlink(self, 0x184, 0x198);
    SndStream_unlink(self, 0x1a8, 0x1bc);
    SndStream_unlink(self, 0x1cc, 0x1e0);
    SndStream_unlink(self, 0x1f0, 0x204);
}
}}}  // namespace rw::audio::core

// @ 0x01132090
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x01132280
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x01132300
namespace rw { namespace audio { namespace core {
int SndStream_getState(int index)
{
    if (index < (int)(unsigned)g_016e7bfe && index >= 0)
        return (int)g_016e61e0[index];
    return 0;
}
}}}  // namespace rw::audio::core

// @ 0x01132320
namespace rw { namespace audio { namespace core {
void SndStream_removeLine(unsigned a)
{
    SndStreamState* s = g_016e61e0[a & 0xff];
    int v = FUN_01141270(a);
    if (fi(s, 0x12c) != v)
    {
        FUN_01141230(s->m + 0x114, v);
        FUN_011411a0(s->m + 0x120, v);
        fi(s, 0x12c) = v;
    }
}
}}}  // namespace rw::audio::core

// @ 0x01132370
namespace rw { namespace audio { namespace core {
void SndStream_releaseCallback(int p)
{
    unsigned d = *(unsigned*)(p - 4);
    SndStreamState* s = (SndStreamState*)g_016e61e0[d & 0xff];
    Stream* stream = *(Stream**)&fi(s, 0x04);
    stream->ReleaseChunk(*(void**)(p - 8));
}
}}}  // namespace rw::audio::core

// @ 0x011323a0
namespace rw { namespace audio { namespace core {
void SndStream_releaseLine(int unused, unsigned b, SndStreamState* self)
{
    (void)unused;
    int* node = (int*)(fi(self, 0x114));
    int iter = 1;
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
        node = (int*)(fi(self, 0x114));
        ++iter;
        if (iter > 200) {
            SndStream_removeLine((unsigned)node[3]);
            return;
        }
    }
}
}}}  // namespace rw::audio::core

// @ 0x01132450
namespace rw { namespace audio { namespace core {
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
        int local30[5];
        local30[0] = 3;
        local30[1] = *p;
        local30[2] = p[4];
        local30[4] = *(int*)(hdr + 0xc);
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
    *(int*)(hdr + 0x10) = SndStream_bitrateToFrames((unsigned short*)(s->m + 0x1c));
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
}}}  // namespace rw::audio::core

// @ 0x011325d0
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x01132660
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x01132770
namespace rw { namespace audio { namespace core {
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

    unsigned char nch = fb(s, 0x1a);
    int base = v7 + 0xc;
    int end = base + (int)nch * 4;
    SndPacket pkt;
    for (int i = 0; i < (int)nch; ++i) {
        unsigned vv = *(unsigned*)(base + i * 4);
        if (swapped)
            vv = (vv >> 24) | ((vv >> 8) & 0xff00) | ((vv << 8) & 0xff0000) | (vv << 24);
        pkt.channel[i] = (void*)(end + vv);
    }
    if ((acc & 0x7fffffff) != 0) {
        *(int*)((char*)pkt.channel[0] - 8) = b;
        *(int*)((char*)pkt.channel[0] - 4) = fi((SndStreamState*)hdr, 0xc);
        *(int*)(hdr + 0x1c) += (int)(acc & 0x7fffffff);
        pkt.size = ((unsigned)fb((SndStreamState*)hdr, 0x24) << 31) | (acc & 0x7fffffff);
        SNDPKTPLAY_submit(fi(s, 0x0c), &pkt);
        fb((SndStreamState*)hdr, 0x24) = 1;
        return;
    }
    ((Stream*)fp(s, 0x04))->ReleaseChunk((void*)b);
}
}}}  // namespace rw::audio::core

// @ 0x011328c0
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x01132a10
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core
