// slice s011fe2c0 -- RenderWare 4 rwoldanimation: the interpolator controller's reverse frame
// advance, key emission, keyframe fixup and the packed quaternion/float blend helpers.
//
// The controller object (0x38 bytes plus the key tables) is the one modelled in slice s011fd3a0;
// here it is the `rw::oldanimation::Interpolator` specialisation whose vtable is
// _sm_vTable_Interpolator (0x015d0968).  RenderWare 4 core was built with VC .NET 2003 (/vc71)
// and /GL, so only the leaf routines are byte-exact; the two 1 KB SSE blend kernels are complete
// behavioural reconstructions (the original works on __m128 lanes, this source on scalars).
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
#include <stddef.h>
#include "types.h"

typedef unsigned int  u32;
typedef signed   int  i32;
typedef unsigned char u8;
typedef unsigned short u16;

// ---- image globals ---------------------------------------------------------
extern float g_blendDotLimit;      // 0x014f84e0 dot product above which the blend lerps
extern float g_nlerpCosLimit;      // 0x0171e220 cos(angle) below which nlerp replaces slerp
extern char  s_vtableInterpolator[]; // 0x015d0968 _sm_vTable_Interpolator

// ---- callees outside this slice --------------------------------------------
extern "C" float _CIacos(float);   // 0x011e08c8 single-precision acos (CRT block)
extern "C" float sinf(float);      // CRT sinf, inlined as fsin in the original
extern "C" float sqrtf(float);     // CRT sqrtf (the original uses rsqrtps + two Newton steps)
void* FUN_011ffa40(void* handle);  // 0x011ffa40 resolve a frame-table handle
void __cdecl ControllerFixup(void* self, void* arena, i32 delta, u32 n); // 0x011fdb30

namespace rw { namespace core { namespace arena {
class Arena
{ public:
    void* IdToObject(u32 id);      // 0x011e2300
};
}}}

namespace rw { namespace oldanimation {

// A packed stream shape: the low byte counts 4-float quaternions, the second the plain floats
// trailing them.  Passed by value in one 4-byte stack slot, exactly like the original.
struct BlendCounts
{
    u8  m_quats;    // +0x00
    u8  m_floats;   // +0x01
    u16 m_pad;      // +0x02
};

// The frame table header a keyframe block was loaded with.
class FrameTable
{
public:
    u32 m_pad00[0x1e];  // +0x00
    void* m_arena;      // +0x78 rw::core::arena::Arena the block lives in
    u32   m_base;       // +0x7c address the block was built at
};

// The controller description the interpolator points at.
class Controller
{
public:
    u32   m_pad00;      // +0x00
    u32   m_pad04;      // +0x04
    u32   m_pad08;      // +0x08
    u32   m_id;         // +0x0c frame-table id handed to the key emitters
    u32   m_pad10;      // +0x10
    u32   m_pad14;      // +0x14
    u32   m_pad18;      // +0x18
    u8    m_flags;      // +0x1c bit 0: keys use the 12-byte layout
    u8    m_pad1d[3];   // +0x1d
    float m_duration;   // +0x20 loop length in frames
    u32   m_stride;     // +0x24 key stride (used by KeyOf)
    u32   m_pad28;      // +0x28
    void* m_base;       // +0x2c key block base (used by KeyOf)
    void* KeyOf(u32 index);     // 0x011fd860 key object for one track
};

// The per-track remap table (NULL or empty when the tracks are emitted in order).
class KeyMap
{
public:
    u32  m_pad00;       // +0x00
    u32  m_count;       // +0x04
    u32* m_keys;        // +0x08 track -> keyframe index
};

// One emulated track: the two key pointers written for the current frame.
struct KeySlot
{
    u32 m_pos;          // +0x00
    u32 m_end;          // +0x04
};

typedef void (__cdecl *KeyEmitter)(void* dest, const void* keys, u32 offset, float frame,
                                   u32 id, const void* key);

class Interpolator
{
public:
    static u32* GetResourceDescriptor(u32* out, u32 size, u32 desc, int hasData); // 0x011fe550
    static int  Fixup(Interpolator* self, FrameTable* table);                     // 0x011fe680

    int   AdvanceBack(float delta);     // 0x011fe2c0 rewind by delta frames
    void  EmitCurrent();                // 0x011fe3f0 emit every track for the current frame
    float GetInvDuration();             // 0x011fe510 frames -> normalised time
    void  SetPlaybackRate(float rate);  // 0x011fe520
    int   Seek(float frame);            // 0x011fe600
    u32   GetResourceSize();            // 0x011fe650
    int   Advance2(float dt);           // 0x011fe180 forward advance (slice s011fd3a0)

    KeyMap*     m_map;      // +0x00
    void*       m_vtable;   // +0x04
    void*       m_dest;     // +0x08 destination buffer
    u32         m_format;   // +0x0c track format
    u32         m_stride;   // +0x10 destination stride
    u32         m_tracks;   // +0x14 track count
    u32         m_done;     // +0x18 keys already emitted for this frame
    Controller* m_ctrl;     // +0x1c
    float       m_cur;      // +0x20 current frame
    float       m_rate;     // +0x24 playback rate
    u32*        m_keys;     // +0x28 per-track key pointers
    void*       m_emit;     // +0x2c key emitter
    void*       m_emitFmt;  // +0x30 format emitter
    u32         m_handle;   // +0x34 frame-table handle
};

// A 4-float lane of the blend kernels.
struct Quad
{
    float m_x, m_y, m_z, m_w;
};

// Interpolate one quad: shortest-path slerp while the dot product is below the limit, plain lerp
// above it.  `b` may already be negated by the caller (the flags!=0 stream shape does that).
static Quad BlendQuad(const Quad& a, const Quad& b, float t)
{
    float dot = a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z + a.m_w * b.m_w;
    float wa = 1.0f - t;
    float wb = t;
    if (dot < g_blendDotLimit)
    {
        float angle = _CIacos(dot);
        float inv = 1.0f / sinf(angle);
        wa = sinf(wa * angle) * inv;
        wb = sinf(t * angle) * inv;
    }
    Quad r;
    r.m_x = a.m_x * wa + b.m_x * wb;
    r.m_y = a.m_y * wa + b.m_y * wb;
    r.m_z = a.m_z * wa + b.m_z * wb;
    r.m_w = a.m_w * wa + b.m_w * wb;
    return r;
}

// ============================================================ interpolator
// 011fe2c0 -- rewind by `delta` frames; wraps below 0 and hands the positive remainder to the
// forward advance, then re-positions every track's key pointers (searched downwards).
// @ 0x011fe2c0
int Interpolator::AdvanceBack(float delta)
{
    float step = m_rate * delta;
    if (step > 0.0f)
    {
        float cur = m_cur;
        Controller* c = m_ctrl;
        float len = c->m_duration;
        u32 n = m_tracks;
        float f = cur - step;
        m_done = 0;
        if (f < 0.0f)
        {
            do
                f += len;
            while (f < 0.0f);
            float over = f - cur;
            if (over > 0.0f)
                return Advance2(over);
        }
        m_cur = f;
        KeySlot* slot = (KeySlot*)m_keys;
        if ((c->m_flags & 1) != 0)
        {
            while (n != 0)
            {
                --n;
                u8* k = (u8*)c->KeyOf(n);
                u32 stride = *(u32*)(k + 4);
                u8* e = (u8*)(slot->m_pos + stride - 0xc);
                while (m_cur < *(float*)e)
                    e += *(u32*)(e + 8);
                slot->m_pos = (u32)e - stride + 0xc;
                slot->m_end = (u32)e + (*(u32*)(e + 4) - stride) + 0xc;
                ++slot;
            }
        }
        else if (n != 0)
        {
            do
            {
                --n;
                u8* k = (u8*)c->KeyOf(n);
                u32 stride = *(u32*)(k + 4);
                u8* e = (u8*)(slot->m_pos + stride - 4);
                while (m_cur < *(float*)e)
                    e -= stride;
                slot->m_pos = (u32)e - stride + 4;
                slot->m_end = slot->m_pos + stride;
                ++slot;
            } while (n != 0);
        }
    }
    return 1;
}

// 011fe3f0 -- emit every track for the current frame (once per frame).
// @ 0x011fe3f0
void Interpolator::EmitCurrent()
{
    if (m_done != 0)
    {
        m_done = 1;
        return;
    }
    u32 tracks = m_tracks;
    u32 flags = ((m_ctrl->m_flags & 1) << 3) | 4;
    u8* dest = (u8*)m_dest;
    u32 i = 0;
    if (m_map != NULL && m_map->m_count != 0)
    {
        while (i < tracks)
        {
            u32 key = m_map->m_keys[i];
            u8* k = (u8*)m_ctrl->KeyOf(key);
            ((KeyEmitter)m_emit)(dest, m_keys + key * 2, *(u32*)(k + 4) - flags, m_cur,
                                 m_ctrl->m_id, k);
            dest += m_stride;
            ++i;
        }
        m_done = 1;
        return;
    }
    KeySlot* slot = (KeySlot*)m_keys;
    while (i < tracks)
    {
        u8* k = (u8*)m_ctrl->KeyOf(i);
        ((KeyEmitter)m_emit)(dest, slot, *(u32*)(k + 4) - flags, m_cur, m_ctrl->m_id, k);
        dest += m_stride;
        ++slot;
        ++i;
    }
    m_done = 1;
}

// 011fe510 -- the reciprocal of the loop length: frames -> normalised time.
// @ 0x011fe510
float Interpolator::GetInvDuration()
{
    return 1.0f / m_ctrl->m_duration;
}

// 011fe520 -- scale the playback rate so `rate` is in loop times per second.
// @ 0x011fe520
void Interpolator::SetPlaybackRate(float rate)
{
    m_rate = rate / (1.0f / m_ctrl->m_duration);
}

// 011fe550 -- the resource descriptor of a keyframe block: {size, alignment} pairs.
// @ 0x011fe550
u32* Interpolator::GetResourceDescriptor(u32* out, u32 size, u32 desc, int hasData)
{
    u32 align = ((desc & 0xff) != 0) ? 0x10 : 4;
    u32 stride = (((desc >> 16 & 0xff) + (desc & 0xff) * 4 + (desc >> 8 & 0xff)) * 4 + 4
                  + (align - 1)) & ~(align - 1);

    u32 extra = 0;
    if (hasData != 0)
        extra = size * 4 + 0xc;

    u32 total = extra + size * 8 + 0x38;
    if (align > 1)
        total = (total + (align - 1)) & ~(align - 1);
    total += stride * size;

    out[1] = 1;
    out[3] = 1;
    out[0] = 0;
    out[2] = 0;
    out[5] = 1;
    out[4] = 0;
    out[7] = 1;
    out[6] = 0;
    out[1] = align;
    out[0] = total;
    return out;
}

// 011fe600 -- seek to an absolute frame, rewinding through the reverse advance.
// @ 0x011fe600
int Interpolator::Seek(float frame)
{
    float d = frame - m_cur;
    if (d < 0.0f)
        AdvanceBack(0.0f - d);
    else
        Advance2(d);
    return 1;
}

// 011fe650 -- the byte size this interpolator's keyframe block needs.
// @ 0x011fe650
u32 Interpolator::GetResourceSize()
{
    u32 desc[8];
    int hasData = (m_map != NULL);
    u32* out = GetResourceDescriptor(desc, m_tracks, m_format, hasData);
    return *out;
}

// 011fe680 -- relocate the interpolator after its frame table moved and rebind the emitters.
// @ 0x011fe680
int Interpolator::Fixup(Interpolator* self, FrameTable* table)
{
    i32 delta = (i32)self - (i32)table->m_base;
    ControllerFixup(self, table->m_arena, delta, 1);
    self->m_keys = (u32*)((u8*)self->m_keys + delta);

    rw::core::arena::Arena* arena = (rw::core::arena::Arena*)table->m_arena;
    void* id = (void*)self->m_ctrl;
    self->m_ctrl = (Controller*)arena->IdToObject((u32)id);

    u32 handle = self->m_handle;
    self->m_vtable = s_vtableInterpolator;
    u32* bind = (u32*)FUN_011ffa40((void*)handle);
    if (bind != NULL)
    {
        self->m_handle = handle;
        u32 emitter = bind[1];
        self->m_emit = (void*)emitter;
        u32 fmt = bind[2];
        self->m_emitFmt = (void*)fmt;
    }

    u32 n = self->m_tracks;
    Controller* c = self->m_ctrl;
    KeySlot* slot = (KeySlot*)self->m_keys;
    while (n != 0)
    {
        slot->m_pos += (u32)c;
        slot->m_end += (u32)c;
        ++slot;
        --n;
    }
    return 1;
}

// ============================================================ blends
// 011fe730 -- blend two packed streams (quaternion prefix plus trailing floats) into `out`.
// Per-quat: slerp/lerp `a` with `b` (negated when the per-quat flag is set), then copy the
// quaternion surplus of the longer stream and lerp/copy the trailing floats.
// @ 0x011fe730
void __cdecl BlendStream(float* out, BlendCounts outCounts, const float* a, BlendCounts aCounts,
                         const float* b, BlendCounts bCounts, float t, const int* flags)
{
    u32 na = aCounts.m_quats;
    u32 nb = bCounts.m_quats;
    u32 n = outCounts.m_quats;
    i32 diff = (i32)nb - (i32)na;       // quaternions the b stream has beyond a
    u32 blend = n < na ? n : na;

    for (u32 i = 0; i < blend; ++i)
    {
        Quad av = *(const Quad*)a;
        Quad bv = *(const Quad*)b;
        if (flags[i] != 0)
        {
            bv.m_x = -bv.m_x;
            bv.m_y = -bv.m_y;
            bv.m_z = -bv.m_z;
            bv.m_w = -bv.m_w;
        }
        *(Quad*)out = BlendQuad(av, bv, t);
        a += 4;
        b += 4;
        out += 4;
    }

    if (na < nb)
    {
        for (i32 i = 0; i < diff; ++i)
            ((Quad*)out)[i] = *(const Quad*)&b[i * 4];
        b += (u32)diff * 4;
    }
    else
    {
        for (i32 i = 0; i < diff; ++i)
            ((Quad*)out)[i] = *(const Quad*)&a[i * 4];
        a += (u32)diff * 4;
    }
    out += (n - blend) * 4;

    u32 af = aCounts.m_floats;
    u32 bf = bCounts.m_floats;
    u32 of = outCounts.m_floats;
    i32 fdiff = (i32)af - (i32)bf;
    u32 nf = of < bf ? of : bf;
    float* dst = out;
    for (u32 i = 0; i < nf; ++i)
        dst[i] = (b[i] - a[i]) * t + a[i];
    a += nf;
    b += nf;
    const float* src = (bf < af) ? b : a;
    for (i32 i = 0; i < fdiff; ++i)
        dst[i] = src[i];
}

// 011fed20 -- per-quat slerp (below cos(limit)) or normalised lerp, then a plain float lerp.
// @ 0x011fed20
void __cdecl BlendSlerpLerp(float* out, const float* a, const float* b, BlendCounts counts,
                            float t)
{
    u32 n = counts.m_quats;
    for (u32 i = 0; i < n; ++i)
    {
        Quad av = *(const Quad*)a;
        Quad bv = *(const Quad*)b;
        float dot = av.m_x * bv.m_x + av.m_y * bv.m_y + av.m_z * bv.m_z + av.m_w * bv.m_w;
        if (dot < 0.0f)
        {
            av.m_x = -av.m_x;
            av.m_y = -av.m_y;
            av.m_z = -av.m_z;
            av.m_w = -av.m_w;
            dot = 0.0f - dot;
        }
        Quad r;
        if (dot <= g_nlerpCosLimit)
        {
            float angle = _CIacos(dot);
            float inv = 1.0f / sinf(angle);
            float wa = sinf((1.0f - t) * angle) * inv;
            float wb = sinf(t * angle) * inv;
            r.m_x = av.m_x * wa + bv.m_x * wb;
            r.m_y = av.m_y * wa + bv.m_y * wb;
            r.m_z = av.m_z * wa + bv.m_z * wb;
            r.m_w = av.m_w * wa + bv.m_w * wb;
        }
        else
        {
            // a + (b - a) * t, or a - (a + b) * t when the pair points the other way, normalised
            float k = (dot > 0.0f) ? t : 0.0f - t;
            r.m_x = av.m_x + (bv.m_x - av.m_x) * k;
            r.m_y = av.m_y + (bv.m_y - av.m_y) * k;
            r.m_z = av.m_z + (bv.m_z - av.m_z) * k;
            r.m_w = av.m_w + (bv.m_w - av.m_w) * k;
            float len2 = r.m_x * r.m_x + r.m_y * r.m_y + r.m_z * r.m_z + r.m_w * r.m_w;
            float inv = 1.0f / sqrtf(len2);
            r.m_x *= inv;
            r.m_y *= inv;
            r.m_z *= inv;
            r.m_w *= inv;
        }
        *(Quad*)out = r;
        out += 4;
        a += 4;
        b += 4;
    }

    u32 nf = counts.m_floats;
    while (nf != 0)
    {
        *out = (*b - *a) * t + *a;
        ++out;
        ++a;
        ++b;
        --nf;
    }
}

}} // namespace rw::oldanimation
