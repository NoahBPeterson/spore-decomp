// Slice s00c299e0: SP orientation / superweapon-aim helpers.
//
//   00c299e0  ConstraintTable::remove     - hash-map remove-by-key on a keyed table
//   00c29ab0  cOrientation::CopyFrom      - copy four floats (+0xf0..+0xfc) from src
//   00c29b00  FUN_00c29b00                - thin wrapper: g_1572460.remove(&key)
//   00c29b10  FUN_00c29b10                - clamp / acos / slerp step, returns float
//   00c29d80  FUN_00c29d80                - like 00c29b10 but reads `this` from edi
//
// No VA carries a DB name (symbols/pdb_names.json, symbols/pdb_candidates.json); the names
// below are descriptive and the member offsets are the only recovered facts.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <math.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

struct Vec3 { float x, y, z; };

// ------------------------------------------------------------------ extern helpers
void   FUN_00af6250(void* src);                                     // 0x00af6250
void   FUN_00c293f0(void* out, void* a, int b);                     // 0x00c293f0
float* FUN_0059aed0(void* out, void* dat, void* in);                // 0x0059aed0
float  FUN_011e08c8();                                             // 0x011e08c8  acos
bool   FUN_00b3d550(void* q);                                       // 0x00b3d550
float* FUN_005b2500(void* out, void* a, void* b, float t);          // 0x005b2500  Slerp
void*  FUN_005b26f0(void* out, void* a, void* b, float t);          // 0x005b26f0  SlerpWrap
void*  operator_delete__(void*);                                    // 0x00f47380

// ------------------------------------------------------------------ extern data
extern float g_1485720;   // 1.0f                 0x01485720
extern float g_13eb1bc;   // -1.0f                0x013eb1bc
extern float g_1470f1c;   // 2.0f                 0x01470f1c
extern float g_1471064;   // 0.5f                 0x01471064
extern float g_1572420;   // PI                   0x01572420
extern float g_1572484;   // 1.5f                 0x01572484
extern char  g_1572480;   // global flag          0x01572480
extern char  g_168de1c;   //                      0x0168de1c
extern float g_168de28;   //                      0x0168de28

// ------------------------------------------------------------------ opaque game types
struct cPlanetModel;
struct cSimSingleton;

// A polymorphic helper object living at +0xc0 inside cOrientation.  Only the vtable is
// known; the slots used by this slice are +0x2c (float*), +0x30 (float*), +0x3c (void),
// +0x48 (bool).
struct cOrientSub {
    void* vtbl;   // +0x00
};

struct cOrientation {
    uchar      pad00[0xc0];
    cOrientSub m_sub;                  // +0x0c0
    uchar      pad_c4[0xf0 - 0xc4];
    float      m_f0, m_f4, m_f8, m_fc; // +0x0f0..+0x0fc
    uchar      pad_100[0x2ac - 0x100];
    float      m_2ac;                  // +0x2ac

    void*  CopyFrom(const cOrientation* src);                       // 0x00c29ab0
    void   CopyBase(const void* src);                              // 0x00af6250
    int    GetSubCount();                                          // 0x00c0c2f0
};

// ------------------------------------------------------------------ constraint table
struct cNodeSub {
    uchar m[0x100];
    void Destroy();            // 0x00c2e4e0  SetSerializer / destructor
};

struct ConstraintNode {
    uint  key;                 // +0x000
    uchar sub[0x800];          // +0x004 .. +0x804  (eight 0x100-byte sub-objects)
    void* ptrs[8];             // +0x804 .. +0x824
    ConstraintNode* next;      // +0x824
};

struct ConstraintTable {
    uchar pad00[4];
    ConstraintNode** buckets;  // +0x04
    uint  size;                // +0x08
    int   count;               // +0x0c

    int remove(uint* key);                                          // 0x00c299e0
};

extern ConstraintTable g_1572460;                                   // 0x01572460

// ================================================================== 00c299e0
// @ 0x00c299e0
int ConstraintTable::remove(uint* keyPtr)
{
    int  before = count;
    ConstraintNode** slot = &buckets[*keyPtr % size];

    if (*slot == 0)
        goto done;

    // walk to the first node whose key matches (or to the end of the chain)
    while (*keyPtr != (*slot)->key && (*slot)->next != 0)
        slot = &(*slot)->next;

    if (*slot == 0)
        goto done;

    // unlink every consecutive node that carries this key
    while (*slot != 0 && *keyPtr == (*slot)->key) {
        ConstraintNode* node = *slot;
        *slot = node->next;

        uchar* p = (uchar*)node + 0x824;
        for (int i = 7; i >= 0; --i) {
            void* o = *(void**)(p - 4);
            p -= 4;
            if (o != 0)
                (*(void (__thiscall**)(void*))(*(int*)o + 4))(o);
        }

        uchar* q = (uchar*)node + 0x804;
        for (int i = 7; i >= 0; --i) {
            q -= 0x100;
            ((cNodeSub*)q)->Destroy();
        }

        operator_delete__(node);
        count--;
    }

done:
    return before - count;
}

// ================================================================== 00c29ab0
// @ 0x00c29ab0
void* cOrientation::CopyFrom(const cOrientation* src)
{
    CopyBase(src);
    m_f0 = src->m_f0;
    m_f4 = src->m_f4;
    m_f8 = src->m_f8;
    m_fc = src->m_fc;
    return this;
}

// ================================================================== 00c29b00
// @ 0x00c29b00
int __cdecl FUN_00c29b00(uint key)
{
    return g_1572460.remove(&key);
}

// ================================================================== 00c29b10
// Clamp a target direction against a reference frame, take the enclosing angle, and (when
// the caller is allowed to move) advance the orientation toward it with a slerp.
// @ 0x00c29b10
float __cdecl FUN_00c29b10(cOrientation* obj, float* dir, int param3,
                           float param4, float param5, float param6, char param7)
{
    uchar* sub = obj ? (uchar*)obj + 0xc0 : 0;

    int local[4];                                   // 16-byte working object
    FUN_00c293f0(local, sub, param3);

    cOrientSub* s = (cOrientSub*)((uchar*)obj + 0xc0);
    void* vt = s->vtbl;

    bool b = ((bool (__thiscall*)(void*))(*(void**)((uchar*)vt + 0x48)))(s);
    if (!b && (uint)obj->GetSubCount() < 2) {
        ((void (__thiscall*)(void*, void*))(*(void**)((uchar*)vt + 0x3c)))(s, local);
        return param5;
    }

    float ref[4];
    float* pf = FUN_0059aed0(ref, &g_168de1c, local);

    float dot = (dir[2] * pf[2] + dir[1] * pf[1]) + dir[0] * pf[0];
    float d = dot;
    if (d > g_1485720) d = g_1485720;      // 1.0f
    if (d < g_13eb1bc) d = g_13eb1bc;      // -1.0f

    float zero = 0.0f;
    float* chosen = &zero;
    if (d > zero)
        chosen = &d;
    float rate = param5 * *chosen;

    float a = (float)acos(d);                        // arg passed in st0 (_CIacos)

    uint bits = *(uint*)&a;
    if ((bits & 0x7fffffff) != 0 && 0x7effffff < ((bits - 0x800000u) & 0x7f800000))
        return rate;

    if (zero < a) {
        float speed;
        if ((g_1572480 != 0 && param7 != 0) || a <= g_1471064) {
            speed = (param4 * param6) * g_1470f1c;
        } else {
            speed = (param4 * param6) / a;
        }
        if (speed > g_1485720)
            speed = g_1485720;

        void* q = ((void* (__thiscall*)(void*))(*(void**)((uchar*)vt + 0x30)))(s);
        float* r = FUN_005b2500(&ref, q, local, speed);
        float quat[4];
        quat[0] = r[0];
        quat[1] = r[1];
        quat[2] = r[2];
        quat[3] = r[3];

        if (FUN_00b3d550(quat))
            ((void (__thiscall*)(void*, void*))(*(void**)((uchar*)vt + 0x3c)))(s, quat);
    }
    return rate;
}

// ================================================================== 00c29d80
// Sibling of 00c29b10.  The original receives `this` in edi (no mov edi,ecx prologue) and
// a scratch pointer in ecx; modelled here as an ordinary __cdecl so it still compiles and
// behaves the same.
// @ 0x00c29d80
void __cdecl FUN_00c29d80(cOrientation* self, float* dir, float param2,
                          float param3, float param4)
{
    cOrientation* obj = self;
    uchar* sub = obj ? (uchar*)obj + 0xc0 : 0;

    float local[8];
    FUN_00c293f0(local, sub, (int)dir);

    cOrientSub* s = (cOrientSub*)((uchar*)obj + 0xc0);
    void* vt = s->vtbl;

    bool b = ((bool (__thiscall*)(void*))(*(void**)((uchar*)vt + 0x48)))(s);
    if (!b && (uint)obj->GetSubCount() < 2) {
        ((void (__thiscall*)(void*, void*))(*(void**)((uchar*)vt + 0x3c)))(s, local);
        return;
    }

    float ref[4];
    float* pf = FUN_0059aed0(ref, &g_168de1c, local);

    float f0 = pf[0];
    float f1 = pf[1];
    float f2 = pf[2];

    float dot = (dir[0] * f0 + dir[2] * f2) + dir[1] * f1;
    if (dot <= g_13eb1bc)
        dot = g_13eb1bc;
    if (g_1485720 <= dot)
        dot = g_1485720;

    uint dbits = *(uint*)&dot;
    if ((dbits & 0x7fffffff) != 0 && 0x7effffff < ((dbits - 0x800000u) & 0x7f800000))
        return;

    float a = (float)acos(dot);
    uint abits = *(uint*)&a;
    if ((abits & 0x7fffffff) != 0 && 0x7effffff < ((abits - 0x800000u) & 0x7f800000))
        return;

    float cx = dir[2] * f1 - dir[1] * f2;
    float cy = dir[0] * f2 - dir[2] * f0;
    float cz = dir[1] * f0 - dir[0] * f1;

    float* axis = ((float* (__thiscall*)(void*))(*(void**)((uchar*)vt + 0x2c)))(s);
    if ((axis[2] * cz + axis[1] * cy) + axis[0] * cx < 0.0f)
        a = -a;

    if (fabsf(a) < 1e-6f)
        return;

    float rate  = obj->m_2ac;
    float scale = g_1572484 * param4;                 // 1.5f * dt
    float extra = 0.0f;
    if (1e-6f < param4) {
        float sign = g_168de28;
        if (rate <= (g_1572420 - a) * scale) {
            if ((-a - g_1572420) * scale <= rate)
                goto step;
            sign = -g_168de28;
        }
        *(uint*)&local[0] ^= 0x80000000;
        *(uint*)&local[1] ^= 0x80000000;
        *(uint*)&local[2] ^= 0x80000000;
        *(uint*)&local[3] ^= 0x80000000;
        extra = sign;
    }
step:
    {
        float d = a - extra;
        if (1e-6f <= fabsf(d)) {
            void* fn = *(void**)((uchar*)vt + 0x30);
            float w = (d * scale + rate) * param2;
            float e = (float)exp(-(scale * param2));
            obj->m_2ac = (rate - w * scale) * e;

            float* q = ((float* (__thiscall*)(void*))fn)(s);
            float cur[4];
            cur[0] = q[0];
            cur[1] = q[1];
            cur[2] = q[2];
            cur[3] = q[3];

            float out[8];
            FUN_005b26f0(out, cur, local, (a - ((w + d) * e + extra)) / d);

            if (FUN_00b3d550(out))
                ((void (__thiscall*)(void*, void*))(*(void**)((uchar*)vt + 0x3c)))(s, out);
        }
    }
}
