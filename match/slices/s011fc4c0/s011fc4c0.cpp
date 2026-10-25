// Slice s011fc4c0 -- 0x11fxxxx region (attribute-mask helpers with per-letter
// dispatch tables).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP
// /arch:SSE /fp:fast (default /GS on).

typedef unsigned int  uint;
typedef unsigned char byte;

#include <math.h>
#include <string.h>
#include <xmmintrin.h>
#pragma intrinsic(sqrt)
#pragma intrinsic(sqrtf)

// @ 0x011fcde0 -- FUN_011fcde0
// Walks the NUL-terminated letter list at param_1+0x11 and invokes the
// per-letter handler at &DAT_01719d08 when the letter's mask at &DAT_0171a108
// intersects param_2, passing the parallel dword at param_1+0x34.
void __cdecl FUN_011fcde0(void* param_1, uint param_2) {
    byte* pbVar3 = (byte*)((char*)param_1 + 0x11);
    int* puVar4 = (int*)((char*)param_1 + 0x34);
    do {
        byte bVar1 = *pbVar3;
        uint uVar2 = (uint)bVar1;
        if ((*(uint*)(0x171a108 + uVar2 * 4) & param_2) != 0) {
            (*(void(__cdecl**)(uint, uint, int))(0x1719d08 + uVar2 * 4))(uVar2, param_2, *puVar4);
        }
        puVar4 = puVar4 + 1;
        pbVar3 = pbVar3 + 1;
    } while (*pbVar3 != 0);
}

// @ 0x011fcee0 -- FUN_011fcee0
// Same walk as FUN_011fcde0, but against the &DAT_0171b538 mask table and the
// &DAT_0171b938 handlers, reading the parallel dword at param_1+0x20.
void __cdecl FUN_011fcee0(byte* param_1, uint param_2) {
    int* pbVar3 = (int*)(param_1 + 0x20);
    byte bVar1 = *param_1;
    do {
        uint uVar2 = (uint)bVar1;
        if ((*(uint*)(0x171b538 + uVar2 * 4) & param_2) != 0) {
            (*(void(__cdecl**)(uint, uint, int))(0x171b938 + uVar2 * 4))(uVar2, param_2, *pbVar3);
        }
        bVar1 = param_1[1];
        pbVar3 = pbVar3 + 1;
        param_1 = param_1 + 1;
    } while (bVar1 != 0);
}

// @ 0x011fcd10 -- FUN_011fcd10
// Letter-list/mask intersection, sibling of FUN_011fce20: walks the letter list at
// param_1+0x11 against the candidate list at param_2+0x11, accumulating the matched
// masks in param_1+0xb4 and returning the mask of letters whose parallel dword at
// param_1+0x34 differs from the candidate's dword at param_2+0x34+index*4.
uint __cdecl FUN_011fcd10(byte* param_1, byte* param_2) {
    byte* pbVar3 = param_2 + 0x11;
    byte bVar4 = param_1[0x11];
    uint uVar8 = 0;
    byte* pbVar7 = param_1 + 0x12;
    if (param_2[0x11] != 0) {
        int* pl = (int*)(param_1 + 0x34);
        uint local_4 = 0;
        do {
            uint uVar5 = *(uint*)(0x171a108 + (uint)bVar4 * 4);
            if (uVar5 != 0) {
                uVar8 = uVar8 | uVar5;
                int iVar6 = 0;
                byte bVar2 = *pbVar3;
                while (bVar4 != bVar2 && bVar2 != 0) {
                    int iVar1 = iVar6 + 1;
                    iVar6 = iVar6 + 1;
                    bVar2 = pbVar3[iVar1];
                }
                if (pbVar3[iVar6] == 0 ||
                    *pl != *(int*)(param_2 + iVar6 * 4 + 0x34)) {
                    local_4 = local_4 | uVar5;
                }
            }
            bVar4 = *pbVar7;
            pl = pl + 1;
            pbVar7 = pbVar7 + 1;
        } while (bVar4 != 0);
        *(uint*)(param_1 + 0xb4) = uVar8;
        return local_4;
    }
    do {
        uint uVar5 = (uint)bVar4;
        bVar4 = *pbVar7;
        uVar8 = uVar8 | *(uint*)(0x171a108 + uVar5 * 4);
        pbVar7 = pbVar7 + 1;
    } while (bVar4 != 0);
    *(uint*)(param_1 + 0xb4) = uVar8;
    return uVar8;
}

// @ 0x011fce20 -- FUN_011fce20
// Intersects the letter list at param_1 with the candidate string param_2,
// accumulating the matched masks in param_1+0xa0 and returning the mask of the
// letters that matched a different payload.
uint __cdecl FUN_011fce20(byte* param_1, byte* param_2) {
    byte* pbVar3 = param_2;
    byte bVar4 = *param_1;
    uint uVar8 = 0;
    byte* pbVar7 = param_1 + 1;
    if (*param_2 != 0) {
        byte* param_2b = param_1 + 0x20;
        uint local_4 = 0;
        do {
            uint uVar5 = *(uint*)(0x171b538 + (uint)bVar4 * 4);
            if (uVar5 != 0) {
                uVar8 = uVar8 | uVar5;
                int iVar6 = 0;
                byte bVar2 = *pbVar3;
                while (bVar4 != bVar2 && bVar2 != 0) {
                    int iVar1 = iVar6 + 1;
                    iVar6 = iVar6 + 1;
                    bVar2 = pbVar3[iVar1];
                }
                if (pbVar3[iVar6] == 0 || *(int*)param_2b != *(int*)(pbVar3 + iVar6 * 4 + 0x20)) {
                    local_4 = local_4 | uVar5;
                }
            }
            bVar4 = *pbVar7;
            param_2b = param_2b + 4;
            pbVar7 = pbVar7 + 1;
        } while (bVar4 != 0);
        *(uint*)(param_1 + 0xa0) = uVar8;
        return local_4;
    }
    do {
        uint uVar5 = (uint)bVar4;
        bVar4 = *pbVar7;
        uVar8 = uVar8 | *(uint*)(0x171b538 + uVar5 * 4);
        pbVar7 = pbVar7 + 1;
    } while (bVar4 != 0);
    *(uint*)(param_1 + 0xa0) = uVar8;
    return uVar8;
}

void __cdecl FUN_011fca60(float* out, const float* in);

// @ 0x011fcbc0 -- FUN_011fcbc0
// Picks the first active light (scanning &DAT_016f6570 for the first non-null
// entry, stopping after 8), transforms its 4-float colour through FUN_011fca60
// (or zeroes it) and pushes it to the D3D9 device constant slot.
void __cdecl FUN_011fcbc0(void* param_1, void* param_2, int param_3) {
    float local_30[4];
    float local_20[4];
    unsigned uVar2 = 0;
    int* lightArray = (int*)0x16f6570;
    if (lightArray[0] == 0) {
        do {
            int* piVar1 = lightArray + uVar2;
            uVar2 = uVar2 + 1;
            if (*piVar1 != 0) break;
        } while (true);
        if (uVar2 < 8) goto LAB_011fcbe6;
    } else {
LAB_011fcbe6:
        int* piVar1 = (int*)lightArray[uVar2];
        if (piVar1 != 0 && *piVar1 != 1 && *piVar1 != 3) {
            local_20[0] = ((float*)piVar1)[8];
            local_20[1] = ((float*)piVar1)[9];
            local_20[2] = ((float*)piVar1)[10];
            local_20[3] = ((float*)piVar1)[0xb];
            FUN_011fca60(local_30, local_20);
            goto LAB_011fcc3c;
        }
    }
    local_30[0] = 0.0f;
    local_30[1] = 0.0f;
    local_30[2] = 0.0f;
    local_30[3] = 0.0f;
LAB_011fcc3c:
    if (param_3 != 0) {
        (*(void(__cdecl**)(void*, void*, void*, int))(*(int*)0x16f89d0 + 0x178))(
            *(void**)0x16f89d0, param_1, local_30, 1);
        return;
    }
    (*(void(__cdecl**)(void*, void*, void*, int))(*(int*)0x16f89d0 + 0x1b4))(
        *(void**)0x16f89d0, param_1, local_30, 1);
}

// @ 0x011fcc70 -- FUN_011fcc70
// Copies the 4x4 matrix at &DAT_016fa5b8 to the stack, transforms its third row
// through FUN_011fca60, forces w = 1 and pushes the result to the device.
void __cdecl FUN_011fcc70(void* param_1, void* param_2, int param_3) {
    float m[16];
    float out70[4];
    float arg[4];
    for (int i = 0; i < 16; i++) {
        m[i] = ((float*)0x16fa5b8)[i];
    }
    FUN_011fca60(out70, m + 8);
    arg[0] = out70[0];
    arg[1] = out70[1];
    arg[2] = out70[2];
    arg[3] = 1.0f;
    if (param_3 != 0) {
        (*(void(__cdecl**)(void*, void*, void*, int))(*(int*)0x16f89d0 + 0x178))(
            *(void**)0x16f89d0, param_1, arg, 1);
        return;
    }
    (*(void(__cdecl**)(void*, void*, void*, int))(*(int*)0x16f89d0 + 0x1b4))(
        *(void**)0x16f89d0, param_1, arg, 1);
}

// ===================== D3D9 soft-state cache: bitmap-gated flush walks =====================
// These three are the sibling of s011fd3a0's StateCacheApplyPixel (0x011fd3a0): they walk the
// same record lists of the soft-state cache, but each record is gated by a bitmap of live
// shader/state ids at g_stateLive (0x016f89f8) instead of being applied unconditionally.
//
// One 4-byte record is {u16 id; u8 value; u8 sub}; the groups are separated by one skipped
// record.  A custom render command is {fn; u16 cmd; u8 a; u8 b}.

extern void* g_device;             // 0x016f89d0 IDirect3DDevice9*
extern unsigned g_stateLive[];     // 0x016f89f8 bitmap of live state ids (id>>5, 1<<(id&31))
extern void* g_stateTable[];       // 0x016f65a8 state objects indexed by 16-bit id
extern unsigned g_stateCommandMask; // 0x016f9110 mask forcing the custom-command path
extern unsigned g_constantPool[];  // 0x016fa5ec constant payloads, 0x20 bytes per id

struct StateRecord
{
    unsigned short id;             // +0x00
    byte value;                    // +0x02
    byte sub;                      // +0x03
};

typedef void (__stdcall* PFN_StateIndexed)(void* dev, byte value, void* obj, byte sub);
typedef void (__cdecl* PFN_StateCmd3)(byte a, byte b, int c);
typedef void (__cdecl* PFN_StateCmdArg)(void* arg);

// IDirect3DDevice9 vtable, viewed as the flat array of indexed-state setters this cache
// walks.  Only the six slots below are ever called.
enum DeviceSlot
{
    kSetVertexState0 = 0x178 / 4,  // +0x178
    kSetVertexState1 = 0x180 / 4,  // +0x180
    kSetVertexState2 = 0x188 / 4,  // +0x188
    kSetPixelState0  = 0x1b4 / 4,  // +0x1b4
    kSetPixelState1  = 0x1bc / 4,  // +0x1bc
    kSetPixelState2  = 0x1c4 / 4,  // +0x1c4
    kDeviceSlotCount = 0x1c8 / 4
};

struct DeviceVTable
{
    PFN_StateIndexed slot[kDeviceSlotCount];   // +0x000, indexed by DeviceSlot
};

struct DeviceState
{
    DeviceVTable* vtbl;            // +0x00
};

struct StateCommand
{
    PFN_StateCmd3 fn;              // +0x00
    unsigned short cmd;            // +0x04
    byte a;                        // +0x06
    byte b;                        // +0x07
};

// One custom-command argument block: two bytes, the pooled payload and a flag byte.
struct StateCommandArg
{
    byte a;                        // +0x00
    byte b;                        // +0x01
    unsigned payload;              // +0x04
    byte flag;                     // +0x08
};

// Header of a soft-state list: the cache flags at +0x4 are OR-ed with the forced bit 4 and
// tested against g_stateCommandMask.  The record groups follow the header.
struct StateList
{
    void*    owner;                // +0x00
    unsigned cacheFlags;           // +0x04
};

// Vertex lists keep one more header dword, so their records start at +0x0c.
struct VertexStateList
{
    StateList   header;            // +0x00 .. +0x07
    unsigned    unused08;          // +0x08
    StateRecord records[1];        // +0x0c
};

// Pixel lists start their records right after the header, at +0x08.
struct PixelStateList
{
    StateList   header;            // +0x00 .. +0x07
    StateRecord records[1];        // +0x08
};

static bool StateIdIsLive(unsigned short id)
{
    return (g_stateLive[id >> 5] & (1u << (id & 0x1f))) != 0;
}

// Applies one record through the named device vtable slot; the caller passes the slot
// constant so cl emits the retail's three hard-coded call sites.
static __forceinline void StateApplyRecord(StateRecord* record, unsigned short id, DeviceSlot slot)
{
    DeviceState* dev = (DeviceState*)g_device;
    dev->vtbl->slot[slot](dev, record->value, g_stateTable[id], record->sub);
}

// @ 0x011fcf20 -- FUN_011fcf20
// Flushes the vertex-shader state list: three bitmap-gated indexed-state groups (device slots
// 0x178/0x180/0x188) followed by the custom render commands, which use the plain three-argument
// form unless the command id is in [0x400,0x800) and the cache mask forces the pooled form.
void __fastcall FUN_011fcf20(VertexStateList* self)
{
    StateRecord* record = self->records;

    for (;;) { unsigned short id = record->id; if (id == 0) break; if (StateIdIsLive(id)) StateApplyRecord(record, id, kSetVertexState0); ++record; }
    ++record;
    for (;;) { unsigned short id = record->id; if (id == 0) break; if (StateIdIsLive(id)) StateApplyRecord(record, id, kSetVertexState1); ++record; }
    ++record;
    for (;;) { unsigned short id = record->id; if (id == 0) break; if (StateIdIsLive(id)) StateApplyRecord(record, id, kSetVertexState2); ++record; }
    ++record;

    StateCommand* command = (StateCommand*)record;
    for (;;)
    {
        unsigned short cmd = command->cmd;
        if (cmd == 0)
            break;
        if (((self->header.cacheFlags | 4) & g_stateCommandMask) != 0)
        {
            if (cmd < 0x400 || cmd >= 0x800)
            {
                command->fn(command->a, command->b, 1);
            }
            else
            {
                StateCommandArg arg;
                arg.a = command->a;
                arg.b = command->b;
                arg.payload = g_constantPool[cmd * 8];
                arg.flag = 1;
                ((PFN_StateCmdArg)command->fn)(&arg);
            }
        }
        ++command;
    }
}

// @ 0x011fd0c0 -- FUN_011fd0c0
// Same walk as FUN_011fcf20 with the bitmap gate dropped: every record is applied (slots
// 0x178/0x180/0x188), then the custom commands use the plain/pooled split on the command id
// alone (no cache mask).
void __fastcall FUN_011fd0c0(VertexStateList* self)
{
    StateRecord* record = self->records;

    for (;;) { unsigned short id = record->id; if (id == 0) break; StateApplyRecord(record, id, kSetVertexState0); ++record; }
    ++record;
    for (;;) { unsigned short id = record->id; if (id == 0) break; StateApplyRecord(record, id, kSetVertexState1); ++record; }
    ++record;
    for (;;) { unsigned short id = record->id; if (id == 0) break; StateApplyRecord(record, id, kSetVertexState2); ++record; }
    ++record;

    StateCommand* command = (StateCommand*)record;
    for (;;)
    {
        unsigned short cmd = command->cmd;
        if (cmd == 0)
            break;
        if (cmd < 0x400 || cmd >= 0x800)
        {
            command->fn(command->a, command->b, 1);
        }
        else
        {
            StateCommandArg arg;
            arg.a = command->a;
            arg.b = command->b;
            arg.payload = g_constantPool[cmd * 8];
            arg.flag = 1;
            ((PFN_StateCmdArg)command->fn)(&arg);
        }
        ++command;
    }
}

// @ 0x011fd1f0 -- FUN_011fd1f0
// Pixel-shader counterpart: the groups start at self+8 and use device slots 0x1b4/0x1bc/0x1c4.
// The custom commands are again gated, with the pooled argument block flagged 0 instead of 1.
void __fastcall FUN_011fd1f0(PixelStateList* self)
{
    StateRecord* record = self->records;

    for (;;) { unsigned short id = record->id; if (id == 0) break; if (StateIdIsLive(id)) StateApplyRecord(record, id, kSetPixelState0); ++record; }
    ++record;
    for (;;) { unsigned short id = record->id; if (id == 0) break; if (StateIdIsLive(id)) StateApplyRecord(record, id, kSetPixelState1); ++record; }
    ++record;
    for (;;) { unsigned short id = record->id; if (id == 0) break; if (StateIdIsLive(id)) StateApplyRecord(record, id, kSetPixelState2); ++record; }
    ++record;

    unsigned commandMaskSet = ((self->header.cacheFlags | 4) & g_stateCommandMask) != 0;
    StateCommand* command = (StateCommand*)record;
    for (;;)
    {
        unsigned short cmd = command->cmd;
        if (cmd == 0)
            break;
        if (commandMaskSet || StateIdIsLive(cmd))
        {
            if (cmd < 0x400 || cmd >= 0x800)
            {
                command->fn(command->a, command->b, 0);
            }
            else
            {
                StateCommandArg arg;
                arg.a = command->a;
                arg.b = command->b;
                arg.payload = g_constantPool[cmd * 8];
                arg.flag = 0;
                ((PFN_StateCmdArg)command->fn)(&arg);
            }
        }
        ++command;
    }
}

// ===================== 0x011fc4c0 / 0x011fca60: normal-matrix cache =====================
// The D3D9 driver keeps one lazily-built matrix for D3DXVec3TransformNormal (the transform
// that lights push to the device).  FUN_011fc4c0 rebuilds the rotation part of an affine
// matrix as a right-handed orthonormal basis; FUN_011fca60 chooses and caches which matrix
// to use.

// 16-byte aligned row, so whole-row copies are single movaps loads/stores.
struct __declspec(align(16)) Vec4
{
    float x;                        // +0x00
    float y;                        // +0x04
    float z;                        // +0x08
    float w;                        // +0x0c
};

struct Matrix4
{
    Vec4 row[4];                    // +0x00 .. +0x3c
};

// Lazily cached transform state.
extern const Matrix4* g_cachedTransform; // 0x016f9114 matrix handed to D3DXVec3TransformNormal
extern const Matrix4* g_matrixOverride;  // 0x016f8cf4 explicit 3x3 override
extern const Matrix4* g_cachedBasis;     // 0x016f9120 cached orthonormal basis
extern const Matrix4* g_sourceMatrix;    // 0x016f85ac the world matrix being reduced
extern int            g_matrixType;      // 0x016f8b50 3 = 33 matrix, 4 = identity

// Matrix scratch buffers owned by this module (16-byte aligned, like the rows they hold).
// The mixed cases exercise the +0x50/+0x60/+0x70 scratch, so those need the same initial
// contents in the original and in the reconstruction; the symbol names are the g_<hex> form
// that the equivalence harness resolves unqualified references by.
extern __declspec(align(16)) Matrix4 g_1718a60;   // 0x01718a60
extern __declspec(align(16)) Matrix4 g_1718a20;   // 0x01718a20
extern __declspec(align(16)) Matrix4 g_1718aa0;   // 0x01718aa0 (identity)

extern "C" void     __cdecl Matrix33Mul(Matrix4* dst, const Matrix4* src);       // 0x011fb750
extern "C" Matrix4* __cdecl Matrix44Invert(Matrix4* dst, const Matrix4* src);    // 0x011fb310
extern "C" void     __cdecl D3DXVec3TransformNormal(float* out, const float* in,
                                                   const Matrix4* m);            // 0x0120bb62

// Row helpers.  The retail code keeps each row in an xmm register and does its dot
// products / cross products with packed SSE, so these are written with __m128 too.
static __forceinline __m128 SplatX(__m128 v) { return _mm_shuffle_ps(v, v, 0x00); }

// Broadcast dot(a.xyz, b.xyz): s = a.x*b.x + (a.y*b.y + a.z*b.z), the same association
// (and the same shuffle order) as the retail kernel.
static __forceinline __m128 Dot3(__m128 a, __m128 b)
{
    __m128 p = _mm_mul_ps(a, b);
    __m128 s = _mm_add_ps(_mm_shuffle_ps(p, p, 0x01), _mm_shuffle_ps(p, p, 0x02));
    return SplatX(_mm_add_ps(p, s));
}

// 1 / sqrt(d) exactly as the retail kernel refines it: rsqrtps, then twice
// r += (1 - d*r*r) * (0.5*r).
static __forceinline __m128 RecipSqrt2(__m128 d)
{
    const __m128 one  = _mm_set1_ps(1.0f);
    const __m128 half = _mm_set1_ps(0.5f);
    __m128 r = _mm_rsqrt_ps(d);
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(d, _mm_mul_ps(r, r))),
                                 _mm_mul_ps(half, r)));
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(d, _mm_mul_ps(r, r))),
                                 _mm_mul_ps(half, r)));
    return r;
}

// Scales all four lanes by the reciprocal length of the xyz part.  Also returns that
// length, which the retail code derives as d*r (and masks to zero for a zero-length row).
static __forceinline __m128 Normalize3(__m128 v, __m128* length)
{
    __m128 d = Dot3(v, v);
    __m128 r = RecipSqrt2(d);
    __m128 zero = _mm_setzero_ps();
    *length = _mm_andnot_ps(_mm_cmpeq_ps(d, zero), _mm_mul_ps(d, r));
    return _mm_mul_ps(v, r);
}

// a x b, identical shuffle/pairing to the retail sequence (a1b2-a2b1, a2b0-a0b2, a0b1-a1b0).
static __forceinline __m128 Cross3(__m128 a, __m128 b)
{
    __m128 minuend = _mm_mul_ps(_mm_shuffle_ps(a, a, 0x09), _mm_shuffle_ps(b, b, 0x12));
    __m128 subtrahend = _mm_mul_ps(_mm_shuffle_ps(a, a, 0x12), _mm_shuffle_ps(b, b, 0x09));
    return _mm_sub_ps(minuend, subtrahend);
}

// @ 0x011fc4c0 -- FUN_011fc4c0
// Rebuilds the rotation part of `in` as a right-handed orthonormal basis and returns `out`.
// Row 3 (the translation) is copied through unchanged.  Two of the three normalized rows are
// replaced by normalized cross products; which two depends on the row lengths (a zero row
// makes that row the one to keep) and, when all three are valid, on the pairwise |dot| values.
//
// The retail code keeps three row pointers (eax = the row read as-is, ecx = the row that the
// second cross product overwrites, edx = the row that the first cross product overwrites) and
// picks one of three permutations:
//   eax/ecx/edx = n1/n2/n0, n2/n0/n1 or n0/n1/n2.
void* __cdecl FUN_011fc4c0(Matrix4* out, const Matrix4* in)
{
    __m128 l0, l1, l2, unused;
    __m128 n0 = Normalize3(_mm_load_ps(reinterpret_cast<const float*>(&in->row[0])), &l0);
    __m128 n1 = Normalize3(_mm_load_ps(reinterpret_cast<const float*>(&in->row[1])), &l1);
    __m128 n2 = Normalize3(_mm_load_ps(reinterpret_cast<const float*>(&in->row[2])), &l2);

    float len0 = _mm_cvtss_f32(l0);
    float len1 = _mm_cvtss_f32(l1);
    float len2 = _mm_cvtss_f32(l2);

    __m128* pKeep;    // eax: the row the cross products are built from
    __m128* pSecond;  // ecx: receives cross(c, keep)
    __m128* pCross;   // edx: receives cross(keep, second)

    // The retail code tests each length with comiss/jbe, so a zero (or unordered) length
    // takes the branch; only three positive lengths reach the |dot| selection.
    if (!(len0 > 0.0f))
    {
        pKeep = &n1; pSecond = &n2; pCross = &n0;
    }
    else if (!(len1 > 0.0f))
    {
        pKeep = &n2; pSecond = &n0; pCross = &n1;
    }
    else if (!(len2 > 0.0f))
    {
        pKeep = &n0; pSecond = &n1; pCross = &n2;
    }
    else
    {
        // the retail kernel uses max(kHitMiss * d, d) with kHitMiss == -1.0f, i.e. |d|
        __m128 kHitMiss = _mm_set1_ps(-1.0f);
        __m128 d01 = Dot3(n0, n1);
        __m128 d20 = Dot3(n2, n0);
        __m128 d12 = Dot3(n1, n2);
        float f01 = _mm_cvtss_f32(_mm_max_ps(_mm_mul_ps(kHitMiss, d01), d01));
        float f20 = _mm_cvtss_f32(_mm_max_ps(_mm_mul_ps(kHitMiss, d20), d20));
        float f12 = _mm_cvtss_f32(_mm_max_ps(_mm_mul_ps(kHitMiss, d12), d12));

        if (f20 > f12)
        {
            if (f01 > f12) { pKeep = &n1; pSecond = &n2; pCross = &n0; }
            else           { pKeep = &n0; pSecond = &n1; pCross = &n2; }
        }
        else
        {
            if (f01 > f20) { pKeep = &n2; pSecond = &n0; pCross = &n1; }
            else           { pKeep = &n0; pSecond = &n1; pCross = &n2; }
        }
    }

    __m128 c = Normalize3(Cross3(*pKeep, *pSecond), &unused);
    *pCross = c;
    *pSecond = Normalize3(Cross3(c, *pKeep), &unused);

    _mm_store_ps(reinterpret_cast<float*>(&out->row[0]), n0);
    _mm_store_ps(reinterpret_cast<float*>(&out->row[1]), n1);
    _mm_store_ps(reinterpret_cast<float*>(&out->row[2]), n2);
    _mm_store_ps(reinterpret_cast<float*>(&out->row[3]),
                 _mm_load_ps(reinterpret_cast<const float*>(&in->row[3])));
    return out;
}

// Four-row (64-byte) copy, the way retail does it: one movaps per row.
static __forceinline void CopyMatrix(Matrix4* dst, const Matrix4* src)
{
    _mm_store_ps(reinterpret_cast<float*>(&dst->row[0]),
                 _mm_load_ps(reinterpret_cast<const float*>(&src->row[0])));
    _mm_store_ps(reinterpret_cast<float*>(&dst->row[1]),
                 _mm_load_ps(reinterpret_cast<const float*>(&src->row[1])));
    _mm_store_ps(reinterpret_cast<float*>(&dst->row[2]),
                 _mm_load_ps(reinterpret_cast<const float*>(&src->row[2])));
    _mm_store_ps(reinterpret_cast<float*>(&dst->row[3]),
                 _mm_load_ps(reinterpret_cast<const float*>(&src->row[3])));
}

// @ 0x011fca60 -- FUN_011fca60
// Chooses the cached normal-transform matrix (building it on first use) and transforms `in`
// into `out`.  type 3 uses the 3x3 product (or an explicit override), type 4 means the
// cached transform is the identity so only the xyz lanes are copied, anything else inverts
// the source matrix and orthonormalizes it.
void __cdecl FUN_011fca60(float* out, const float* in)
{
    const Matrix4* m = g_cachedTransform;
    __declspec(align(16)) Matrix4 scratch;

    if (m == 0)
    {
        int type = g_matrixType;
        if (type == 3)
        {
            if (g_matrixOverride != 0)
            {
                D3DXVec3TransformNormal(out, in, g_matrixOverride);
                return;
            }
            m = g_cachedBasis;
            if (m == 0)
            {
                Matrix33Mul(&g_1718a60, g_sourceMatrix);
                m = &g_1718a60;
                g_cachedBasis = m;
            }
        }
        else if (type == 4)
        {
            m = &g_1718aa0;
            g_cachedBasis = m;
        }
        else
        {
            m = g_cachedBasis;
            if (m == 0)
            {
                const Matrix4* pInverse = Matrix44Invert(&scratch, g_sourceMatrix);
                CopyMatrix(&g_1718a60, pInverse);
                m = &g_1718a60;
                g_cachedBasis = m;
            }
            const Matrix4* pBasis = (const Matrix4*)FUN_011fc4c0(&scratch, m);
            CopyMatrix(&g_1718a20, pBasis);
            m = &g_1718a20;
        }
        g_cachedTransform = m;
    }

    if (m == &g_1718aa0)
    {
        // identity transform: copy the three normal lanes, leave w untouched
        Vec4* o = (Vec4*)out;
        const Vec4* i = (const Vec4*)in;
        o->x = i->x;
        o->y = i->y;
        o->z = i->z;
        return;
    }

    D3DXVec3TransformNormal(out, in, m);
}
