// src/game/SPCreatureAnim/animation_events.cpp -- migrated from slice(s) s009a59e0, s009a4c70, s009a3c80 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/animation_events.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/creature_instance_data.h"
#include <math.h>
#include "EA/RectT.h"

// ---- items of slice s009a4c70 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
namespace EA {
template <typename T> struct RectT_s009a_4c70 {
    T mLeft, mTop, mRight, mBottom;
    RectT_s009a_4c70& operator=(const RectT_s009a_4c70& o);                 // 0x00572600
    RectT_s009a_4c70& RotA(float c, float s);         // 0x009a4c70 (thiscall, ret 8)
    RectT_s009a_4c70& RotB(float c, float s);         // 0x009a4d60
    RectT_s009a_4c70& RotC(float c, float s);         // 0x009a4e40
};
}
template EA::RectT_s009a_4c70<float>& EA::RectT_s009a_4c70<float>::RotA(float, float);
template EA::RectT_s009a_4c70<float>& EA::RectT_s009a_4c70<float>::RotB(float, float);
template EA::RectT_s009a_4c70<float>& EA::RectT_s009a_4c70<float>::RotC(float, float);
namespace nSPCreatureAnim {
struct AudioIface {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual int  BeginA();                        // +0x20
    virtual int  BeginB();                        // +0x24
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void SetId(int id);                   // +0x38 (single id)
    virtual void SetFloat(int id, float v);       // +0x3c
    virtual void SetInt(int id, int v);           // +0x40
    virtual void SetStr(int id, const char* s, int b);   // +0x44
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void Commit();                        // +0x58
};
}
namespace nSPCreatureAnim {
struct AudioSystemObj {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void CommitId(int id);                // +0x40
};
}
namespace nSPCreatureAnim {
struct RollList { int* End(); };
}
namespace nSPCreatureAnim {
uint32_t GetEventDataAs32Bits(int a0, void* a1, int a2, int a3, void* creature, uint32_t index,
                              uint32_t defaultValue, int a7);                     // 0x009a5860
}
namespace nSPCreatureAnim {
uint32_t BitMatch(uint32_t a, uint32_t b)
{
    uint32_t acc = 0, bit = 1;
    while (a != 0 && b != 0) {
        uint32_t t = (a - 1) & a;
        a = t ^ a;
        acc |= ((a & b) != 0) ? bit : 0u;
        b = b & ~a;
        bit = bit * 2;
        a = t;
    }
    return acc;
}
}
namespace nSPCreatureAnim {
uint32_t TableFind(uint32_t* table, uint32_t key)
{
    uint32_t n = *table;
    uint32_t i = 0;
    if (n != 0) {
        uint32_t* p = table + 1;
        do {
            if (*p == key) return i;
            ++i;
            p += 5;
        } while (i < n);
    }
    return 0xffffffffu;
}
}
namespace nSPCreatureAnim {
uint32_t EvaluateContextTargetQuery(void* p1, uint32_t p2, int p3, uint32_t* p4, int p5, char p6);
}
namespace nSPCreatureAnim {
bool     CheckEventLocationType(uint32_t flags, int loc);
}
namespace nSPCreatureAnim {
AudioIface* GetSystemAT();                                  // ::EA::Audio::GetSystemAT 0xa206f0
}
namespace nSPCreatureAnim {
AudioSystemObj* AudioSystem();                              // SP::AudioSystem 0x0067cb00
}
// ---- items of slice s009a4c70 end

// ---- items of slice s009a59e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T> struct RectT_s009a_59e0 {
    T mLeft, mTop, mRight, mBottom;
    RectT_s009a_59e0& operator=(const RectT_s009a_59e0& o);                 // 0x00572600
    void RotA(float c, float s);                      // 0x009a4c70 (thiscall, ret 8)
    void RotB(float c, float s);                      // 0x009a4d60
    void RotC(float c, float s);                      // 0x009a4e40
};
}
namespace EA {
namespace Random {
class RandomMersenneTwister { public: double GenerateDouble(); };   // 0x009362d0
}
}
extern EA::Random::RandomMersenneTwister gRandom;     // 0x0166b4b8
struct EvCallback {                                   // *(owner + 0x1688)
    char enabled; char pad[3];
    float (*fn)(int data, int ownerField4, float* pos, float* dir, int flag, int zero);   // +4
    int data;                                         // +8
};
namespace checkerlib {
float* QuaternionVectorTransform(float* out, const float* q, const float* v);          // 0x0099c1a0
}
namespace checkerlib {
float* QuaternionProduct(float* out, const float* a, const float* b);                  // 0x0099c0b0
}
namespace checkerlib {
float* QuaternionVectorTransformInverse(float* out, const float* q, const float* v);   // 0x0099c310
}
namespace checkerlib {
float* matrix_to_quaternion(float* outQ, const float* m3x3);                           // 0x009a4f10
}
float* NormalizeVec3(float* out, const float* v, float* lenOut);   // 0x009a49d0
float  LengthSqVec3(const float* v);                               // 0x009a49b0
void   PerpPair(const float* dir, float* o1, float* o2);           // 0x009a4a70
namespace nSPCreatureAnim {
uint32_t GetEventDataAs32Bits(int a0, void* a1, int a2, int a3, void* creature, uint32_t index,
                              float defaultValue, int a7);         // 0x009a5860 (result is float bits)
}
namespace nSPCreatureAnim {
static inline void Unit(float* d) { d[0] = 0.0f; d[1] = 0.0f; d[2] = 1.0f; }
}
// ---- items of slice s009a59e0 end

// @ 0x009a47e0
namespace nSPCreatureAnim {
bool CheckEventLocationType(unsigned long param_1, creature_instance_data * param_2)
{
    int param_2_v = (int)param_2;
    if ((param_1 & 0xc00000) == 0x400000) {
        if ((param_2_v == 0) || (*(char*)(param_2_v + 0x2d6) == 0))
            return false;
    } else if (((param_1 & 0xc00000) == 0x800000) && (param_2_v != 0) && (*(char*)(param_2_v + 0x2d6) != 0)) {
        return false;
    }
    if ((param_1 & 0xc000000) == 0x4000000) {
        if ((param_2_v == 0) || (*(char*)(param_2_v + 0x2d4) == 0))
            return false;
    } else if (((param_1 & 0xc000000) == 0x8000000) && (param_2_v != 0) && (*(char*)(param_2_v + 0x2d4) != 0)) {
        return false;
    }
    if ((param_1 & 0x3000000) == 0x1000000) {
        if ((param_2_v == 0) || (*(char*)(param_2_v + 0x2d5) == 0))
            return false;
    } else if (((param_1 & 0x3000000) == 0x2000000) && (param_2_v != 0) && (*(char*)(param_2_v + 0x2d5) != 0)) {
        return false;
    }
    return true;
}
}  // namespace nSPCreatureAnim

// @ 0x009a4890
namespace nSPCreatureAnim {
bool ContextFilterEventLocationData(unsigned long param_1, unsigned long param_2, unsigned long * param_3, unsigned long param_4, unsigned long param_5)
{
    switch (param_1 & 0x70) {
    case 0x00:
        return true;
    case 0x10:
        return param_2 == 0;
    case 0x20:
        return param_2 != 0;
    case 0x30:
        return param_4 == -1 || param_3[param_2] == param_4;
    case 0x40:
        return param_4 == -1 || param_3[param_2] != param_4;
    case 0x50:
        return param_3[param_2] == param_5;
    case 0x60:
        return param_3[param_2] != param_5;
    default:
        return false;
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009a49b0
float LengthSqVec3(float* v)
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

// @ 0x009a49d0
void NormalizeVec3(float* out, float* in, float* lengthOut)
{
    float x = in[0];
    float z = in[2];
    float y = in[1];
    float len = sqrtf(y * y + z * z + x * x);
    if (lengthOut != 0) {
        *lengthOut = len;
    }
    if (len != 0.0f) {
        float inv = 1.0f / len;
        x = inv * x;
        y = inv * y;
        z = inv * z;
    }
    out[0] = x;
    out[1] = y;
    out[2] = z;
}

// @ 0x009a4a70
void PerpPair(float* n, float* out1, float* out2)
{
    float v[3] = { 1.0f, 1.0f, 1.0f };
    float best = 0.0f;
    float x = n[0];
    if (0.0f < fabsf(x))
        best = fabsf(x);
    float a1 = fabsf(n[1]);
    bool b = best < a1;
    if (b)
        best = a1;
    unsigned idx = (unsigned)b;
    if (best < fabsf(n[2]))
        idx = 2;
    float n2 = n[2];
    float n1 = n[1];
    v[idx] = 0.0f;

    float f4 = n2 * v[1] - n1 * v[2];
    float f5 = n1 * v[0] - x * v[1];
    float f3 = x * v[2] - n2 * v[0];
    float len = sqrtf(f4 * f4 + (f3 * f3 + f5 * f5));
    if (len != 0.0f) {
        len = 1.0f / len;
        f4 = len * f4;
        f3 = len * f3;
        f5 = len * f5;
    }
    out1[0] = f4;
    out1[1] = f3;
    out1[2] = f5;

    float g7 = n[1] * f5 - n[2] * f3;
    float g5 = n[2] * f4 - n[0] * f5;
    float g3 = n[0] * f3 - n[1] * f4;
    float len2 = sqrtf(g7 * g7 + (g3 * g3 + g5 * g5));
    if (len2 != 0.0f) {
        len2 = 1.0f / len2;
        g7 = len2 * g7;
        g5 = len2 * g5;
        g3 = len2 * g3;
    }
    out2[0] = g7;
    out2[1] = g5;
    out2[2] = g3;
}

// @ 0x009a4c70
template <typename T> EA::RectT_s009a_4c70<T>& EA::RectT_s009a_4c70<T>::RotA(float c, float s)
{
    T x = mLeft, y = mTop, z = mRight, w = mBottom;
    T r0 = x * c + w * s - z * (T)0.0 + y * (T)0.0;
    T r1 = y * c + z * s + w * (T)0.0 - x * (T)0.0;
    T r2 = z * c - y * s + x * (T)0.0 + w * (T)0.0;
    T r3 = w * c - x * s - y * (T)0.0 - z * (T)0.0;
    mLeft = r0; mTop = r1; mRight = r2; mBottom = r3;
    return *this;
}

// @ 0x009a4d60
template <typename T> EA::RectT_s009a_4c70<T>& EA::RectT_s009a_4c70<T>::RotB(float c, float s)
{
    T x = mLeft, y = mTop, z = mRight, w = mBottom;
    T r0 = x * c + w * (T)0.0 - z * s + y * (T)0.0;
    T r1 = y * c + w * s + z * (T)0.0 - x * (T)0.0;
    T r2 = z * c - y * (T)0.0 + x * s + w * (T)0.0;
    T r3 = w * c - x * (T)0.0 - y * s - z * (T)0.0;
    mLeft = r0; mTop = r1; mRight = r2; mBottom = r3;
    return *this;
}

// @ 0x009a4e40
template <typename T> EA::RectT_s009a_4c70<T>& EA::RectT_s009a_4c70<T>::RotC(float c, float s)
{
    T x = mLeft, y = mTop, z = mRight, w = mBottom;
    T r0 = x * c + w * (T)0.0 - z * (T)0.0 + y * s;
    T r1 = y * c + z * (T)0.0 + w * (T)0.0 - x * s;
    T r2 = z * c - y * (T)0.0 + w * s + x * (T)0.0;
    T r3 = w * c - x * (T)0.0 - y * (T)0.0 - z * s;
    mLeft = r0; mTop = r1; mRight = r2; mBottom = r3;
    return *this;
}

// @ 0x009a4f10
void checkerlib_matrix_to_quaternion(float* q, const float* m)
{
    float m00 = m[0], m11 = m[4], m22 = m[8];
    float trace = m00;
    trace += m11;
    trace += m22;
    q[0] = 0.0f; q[1] = 0.0f; q[2] = 0.0f; q[3] = 0.0f;
    if (trace > 0.0f) {
        float s = sqrtf(trace + 1.0f);
        float f = 0.5f / s;
        q[0] = (m[7] - m[5]) * f;
        q[1] = (m[2] - m[6]) * f;
        q[2] = (m[3] - m[1]) * f;
        q[3] = s * 0.5f;
    } else {
        int i = (m00 < m11) ? 1 : 0;
        if (m[i * 4] < m22) i = 2;
        int j = (i + 1) % 3;
        int k = (i + 2) % 3;
        float s = sqrtf((m[i * 4] - (m[j * 4] + m[k * 4])) + 1.0f);
        float f = 0.5f / s;
        q[i] = s * 0.5f;
        q[j] = (m[j * 3 + i] + m[i * 3 + j]) * f;
        q[k] = (m[k * 3 + i] + m[i * 3 + k]) * f;
        q[3] = (m[k * 3 + j] - m[j * 3 + k]) * f;
    }
}

// @ 0x009a5090
namespace nSPCreatureAnim {
uint32_t PlaySound(char* name, int* creature, uint32_t boneIdx, float* vec, char flag5, char flag6, float f7)
{
    uint32_t local_18 = 0;
    AudioIface* iface = GetSystemAT();
    if (iface == 0) return local_18;

    char* bone;
    if (creature == 0 ||
        (uint32_t)(((int)AT(int, creature, 0x2e8) - AT(int, creature, 0x2e4)) / 700) <= boneIdx)
        bone = 0;
    else
        bone = AT(char*, creature, 0x2e4) + boneIdx * 700;

    if (name[0] == 'v' || flag6 != 0) {
        if (creature != 0 && bone != 0 &&
            ((*(int*)(AT(char*, bone, 0) + 0x428) != 0 || AT(int, creature, 0x2d8) != 0) &&
             (AT(int, creature, 0x2d0) < 5 ||
              *(char*)(AT(char*, bone, 0) + 0x42c) != 0))) {
            local_18 = (flag5 != 0) ? iface->BeginB() : iface->BeginA();
            iface->SetId(0x3475365);
            iface->SetStr(0x347537e, name, 0);
            iface->SetInt(0x3475385, (int)local_18);
            iface->SetFloat(0x3475391, vec[0]);
            iface->SetFloat(0x3475395, vec[1]);
            iface->SetFloat(0x3475398, vec[2]);
            iface->SetInt(0x3475381, 0);
            iface->SetInt(0x39f9e01, *(int*)(AT(char*, bone, 0) + 0x428));
            iface->SetFloat(0x39f9e0f, AT(float, AT(char*, bone, 0), 0x37c) * 2.0f);
            iface->SetInt(0x39f9e08, AT(int, creature, 0x2d0));
            iface->SetInt(0x44d63a2, AT(char, creature, 0x2d4));
            iface->SetInt(0x48def6d, AT(uint8_t, creature, 0x2d5));
            if (AT(int, creature, 0x2d8) != 0 && AT(int, creature, 0x2dc) != 0) {
                iface->SetInt(0x39fb001, AT(int, creature, 0x2d8));
                iface->SetFloat(0x39fb000, (float)AT(int, creature, 0x2dc));
            }
            iface->Commit();
            if (flag6 != 0) {
                AudioSystemObj* as = AudioSystem();
                if (as != 0) as->CommitId((int)local_18);
            }
        }
    } else if (!(name[0] == 'f' && name[1] == 'o' && name[2] == 'o' && name[3] == 't')) {
        local_18 = (flag5 != 0) ? iface->BeginB() : iface->BeginA();
        iface->SetId(0x3475365);
        iface->SetStr(0x347537e, name, 0);
        iface->SetInt(0x3475385, (int)local_18);
        iface->SetFloat(0x3475391, vec[0]);
        iface->SetFloat(0x3475395, vec[1]);
        iface->SetFloat(0x3475398, vec[2]);
        iface->SetInt(0x3475381, 0);
        iface->Commit();
        return local_18;
    } else if (creature != 0 && bone != 0 && AT(char, creature, 0x2e0) != 0) {
        float t = (f7 < 0.0f) ? AT(float, creature, 0x15c0) : f7;
        AT(char, creature, 0x2e0) = 0;
        local_18 = (flag5 != 0) ? iface->BeginB() : iface->BeginA();
        iface->SetId(0x3475365);
        iface->SetStr(0x347537e, name, 0);
        iface->SetInt(0x3475385, (int)local_18);
        iface->SetFloat(0x3475391, vec[0]);
        iface->SetFloat(0x3475395, vec[1]);
        iface->SetFloat(0x3475398, vec[2]);
        iface->SetInt(0x3475381, 0);
        iface->SetInt(0x48def6d, AT(uint8_t, creature, 0x2d5));
        iface->SetFloat(0x39fa0cf, t);
        iface->SetFloat(0x39fa0ca,
            (AT(float, AT(char*, bone, 0), 0x434) * AT(float, creature, 0x70)) /
            (AT(float, AT(char*, creature, 0), 0x3e8) * AT(float, creature, 0x70)));
        iface->SetFloat(0x39fa0be,
            fabsf(AT(float, AT(char*, creature, 0), 0x370) * AT(float, creature, 0x70)));
        {
            float x = AT(float, AT(char*, bone, 0), 0x138) * AT(float, creature, 0x70);
            float y = AT(float, AT(char*, bone, 0), 0x13c) * AT(float, creature, 0x70);
            float z = AT(float, AT(char*, bone, 0), 0x140) * AT(float, creature, 0x70);
            float len = sqrtf(z * z + (y * y + x * x));
            iface->SetFloat(0x39fa0c4, len + len);
        }
        {
            RollList* rl = (RollList*)((char*)creature + 0x15b8);
            int* p = rl->End();
            iface->SetInt(0x39fa0b8, (p[1] - *p) / 0x108);
        }
        iface->SetInt(0x39fa0ab, AT(int, AT(char*, bone, 0), 0x424));
        iface->SetInt(0x39fa0b1,
            (AT(float, AT(char*, bone, 0), 0x10c) <= 0.0f &&
             AT(float, AT(char*, bone, 0), 0x10c) != 0.0f) ? 1 : 0);
        iface->SetInt(0x39fa376, 0);
        iface->SetFloat(0x25df0108, 1.0f);
        iface->SetFloat(0x71bc3009, 1.0f);
        iface->SetFloat(0xa26a765f, 0.0f);
        iface->Commit();
        return local_18;
    }
    return local_18;
}
}  // namespace nSPCreatureAnim

// @ 0x009a5650
namespace nSPCreatureAnim {
uint32_t ComputeEventLocationData(uint32_t flags, uint32_t* param_2, uint32_t param_3, uint32_t* owner, uint32_t p5, int p6, int* outLoc, int* outLoc2, uint8_t* outByte)
{
    uint32_t r;
    uint32_t vec[4];
    switch (flags & 0xf) {
    case 1:
        *outLoc = (int)owner;
        /* fall through */
    case 9:
        r = 1;
        break;
    case 2:
        *outLoc = (int)owner;
        *outLoc2 = p5;
        r = 1;
        break;
    case 3:
        *outLoc = (int)owner;
        r = (p6 != -1) ? 1u : 0u;
        *outLoc2 = p6;
        break;
    case 4:
        *outLoc = (int)owner;
        vec[0] = param_2[0];
        vec[1] = param_2[1];
        *outByte = 1;
        vec[2] = 0;
        vec[3] = 0;
        r = EvaluateContextTargetQuery(outLoc2, 0xff, *owner, vec, 0, 0);
        break;
    case 5:
    case 6:
    case 7:
        if (owner[0x9d] != 2) {
            r = ~(flags >> 0xe) & 1;
            break;
        }
        {
            int loc = owner[0xa5];
            *outLoc = loc;
            if (loc == 0) { r = 0; break; }
            if ((flags & 0xf) == 7) { r = 1; break; }
            vec[0] = owner[0xa6];
            vec[1] = owner[0xa7];
            vec[2] = owner[0xa8];
            vec[3] = owner[0xa9];
            if ((flags & 0xf) == 6) {
                vec[0] = param_2[0];
                vec[1] = param_2[1];
                vec[2] = 0;
                vec[3] = 0;
            }
            *outByte = 1;
            r = EvaluateContextTargetQuery(outLoc2, 0xff, *(uint32_t*)*outLoc, vec, 0, 0);
        }
        break;
    case 8:
        if (owner[0x9d] != 2) { r = 1; break; }
        {
            int loc = owner[0xa5];
            *outLoc = loc;
            if ((flags & 0x4000) == 0 && loc != 0) {
                *outByte = 1;
                r = EvaluateContextTargetQuery(outLoc2, 0xff, *(uint32_t*)*outLoc, owner + 0xa6, 0, 0);
                break;
            }
            r = 0;
        }
        break;
    default:
        r = 0;
        break;
    }
    return CheckEventLocationType(flags, *outLoc) ? r : 0;
}
}  // namespace nSPCreatureAnim

// @ 0x009a5860
namespace nSPCreatureAnim {
uint32_t GetEventDataAs32Bits(int a0, void* a1, int a2, int a3, void* creature, uint32_t index, uint32_t defaultValue, int a7)
{
    uint32_t table[2] = { 0x300, 0xc0000 };
    int kind = (int)BitMatch(table[a2], (uint32_t)a0);
    char* bone = 0;
    if (creature != 0 &&
        (uint32_t)(((int)AT(int, creature, 0x2e8) - AT(int, creature, 0x2e4)) / 700) > index)
        bone = AT(char*, creature, 0x2e4) + index * 700;

    if (kind == 1) {
        if (a3 == 0) {
            float f = (float)(*(int*)a1);
            return *(uint32_t*)&f;
        }
        return *(uint32_t*)a1;
    }
    if (kind == 2) {
        if (a3 != 1) return *(uint32_t*)a1;
        float f = *(float*)a1;
        return (uint32_t)(int)f;
    }
    if (kind == 3) {
        if (bone != 0 || (creature != 0 && (bone = AT(char*, creature, 8)) != 0)) {
            uint32_t* tbl = (uint32_t*)(bone + 0xa0);
            uint32_t idx = TableFind(tbl, *(uint32_t*)a1);
            if (idx < tbl[0]) {
                float v = AT(float, bone, 0xac + idx * 0x14) /
                          (AT(float, bone, 0xb4 + idx * 0x14) + 1e-08f);
                if (a3 == 0) return *(uint32_t*)&v;
                return (uint32_t)(int)v;
            }
        }
    }
    return *(uint32_t*)&defaultValue;
}
}  // namespace nSPCreatureAnim

// @ 0x009a59a0
namespace nSPCreatureAnim {
float GetEventDataAsFloat(int p1, float* p2, int p3, void* p4, uint32_t p5, uint32_t p6, int p7)
{
    uint32_t bits = GetEventDataAs32Bits(p1, p2, p3, 0, p4, p5, p6, p7);
    return *(float*)&bits;
}
}  // namespace nSPCreatureAnim

// @ 0x009a59e0
namespace nSPCreatureAnim {
bool ComputeEventLocationState(char randomize, int evData, uint32_t flags, int p4, char* owner, char* cr, uint32_t boneIdx, float* pos, float* pos2, EA::RectT_s009a_59e0<float>* outQuat, float* outScalar, float* outVec, float* dirIn, float* dirIn2, int p15)
{
    char* bone;
    if (cr == 0 || (uint32_t)(((int)(AT(char*, cr, 0x2e8) - AT(char*, cr, 0x2e4))) / 700) <= boneIdx)
        bone = 0;
    else
        bone = AT(char*, cr, 0x2e4) + boneIdx * 700;

    EvCallback* cb = AT(EvCallback*, owner, 0x1688);
    float dirA[3];      // local_94
    float dirB[3];      // local_c8
    float tmp[3];
    float tq[4];

    // ---- scalar output ------------------------------------------------------------------
    if (outScalar) {
        uint32_t k = flags & 0x8180;
        if (k > 0x100) {
            if (k == 0x180) {
                *outScalar = AT(float, owner, 0x70);
            } else if (k == 0x8000) {
                if (bone == 0) {
                    if (cr)
                        *outScalar = AT(float, AT(char*, cr, 0), 0x370) * AT(float, cr, 0x70);
                    else
                        *outScalar = 1.0f;
                } else {
                    char* m = AT(char*, bone, 0);
                    float s = AT(float, cr, 0x70);
                    float vx = s * AT(float, m, 0x138);
                    float vy = AT(float, m, 0x13c) * s;
                    float vz = AT(float, m, 0x140) * s;
                    float len = sqrtf(vx * vx + (vz * vz + vy * vy));
                    *outScalar = len + len;
                }
            } else {
                *outScalar = 1.0f;
            }
        } else if (k == 0x100) {
            uint32_t bits = GetEventDataAs32Bits(evData, &p4, 0, 0, cr, boneIdx, 1.0f, p15);
            *(uint32_t*)outScalar = bits;
        } else if (k == 0 || k != 0x80) {
            *outScalar = 1.0f;
        } else {
            if (cr) *outScalar = AT(float, cr, 0x70);
            else    *outScalar = 1.0f;
        }
    }

    // ---- position / second position / orientation ---------------------------------------
    if (cr != 0) {
        if ((flags & 0xf) - 1 > 7) return false;
        if (bone == 0) {
            if (pos) {
                pos[0] = AT(float, cr, 0x18);
                pos[1] = AT(float, cr, 0x1c);
                pos[2] = AT(float, cr, 0x20);
            }
            if (pos2) {
                pos2[0] = AT(float, cr, 0x74);
                pos2[1] = AT(float, cr, 0x78);
                pos2[2] = AT(float, cr, 0x7c);
            }
            if (outQuat) *outQuat = AT(EA::RectT_s009a_59e0<float>, cr, 0x3c);
        } else {
            if (pos) {
                float* r = checkerlib::QuaternionVectorTransform(tq, (float*)(cr + 0x3c), (float*)(bone + 0x10));
                float x = AT(float, cr, 0x18), y = AT(float, cr, 0x1c), z = AT(float, cr, 0x20);
                pos[0] = x + r[0];
                pos[1] = y + r[1];
                pos[2] = z + r[2];
            }
            if (pos2) {
                float* r = checkerlib::QuaternionVectorTransform(tq, (float*)(cr + 0x3c), (float*)(bone + 0x2c));
                float x = AT(float, cr, 0x74), y = AT(float, cr, 0x78), z = AT(float, cr, 0x7c);
                pos2[0] = x + r[0];
                pos2[1] = y + r[1];
                pos2[2] = z + r[2];
            }
            if (outQuat) {
                float* q = checkerlib::QuaternionProduct(tq, (float*)(cr + 0x3c), (float*)(bone + 0x1c));
                *outQuat = *(EA::RectT_s009a_59e0<float>*)q;
            }
        }
    } else {
        switch (flags & 0xf) {
        case 0:
        case 9:
            if (pos) { pos[0] = 0.0f; pos[1] = 0.0f; pos[2] = 0.0f; }
            if (pos2) { pos2[0] = 0.0f; pos2[1] = 0.0f; pos2[2] = 0.0f; }
            if (outQuat) {
                outQuat->mLeft = 0.0f; outQuat->mTop = 0.0f; outQuat->mRight = 0.0f; outQuat->mBottom = 1.0f;
            }
            break;
        default:
            return false;
        case 5: case 6: case 7: case 8:
            if (AT(int, owner, 0x274) == 0) {
                if (pos) {
                    float* r = checkerlib::QuaternionVectorTransform(tq, (float*)(owner + 0x3c), (float*)(owner + 0x278));
                    float y = AT(float, owner, 0x1c), z = AT(float, owner, 0x20);
                    pos[0] = r[0] + AT(float, owner, 0x18);
                    pos[1] = r[1] + y;
                    pos[2] = r[2] + z;
                }
                if (outQuat) {
                    float* q = checkerlib::QuaternionProduct(tq, (float*)(owner + 0x3c), (float*)(owner + 0x284));
                    *outQuat = *(EA::RectT_s009a_59e0<float>*)q;
                }
            } else {
                if (AT(int, owner, 0x274) != 1) return false;
                if (pos) {
                    pos[0] = AT(float, owner, 0x278);
                    pos[1] = AT(float, owner, 0x27c);
                    pos[2] = AT(float, owner, 0x280);
                }
                if (outQuat) *outQuat = AT(EA::RectT_s009a_59e0<float>, owner, 0x284);
            }
            if (pos2) { pos2[0] = 0.0f; pos2[1] = 0.0f; pos2[2] = 0.0f; }
        }
    }

    // ---- event offset applied to pos ------------------------------------------------------
    bool usedCb = false;
    if (pos) {
        uint32_t k = flags & 0x22000;
        if (k == 0x2000) {
            if (cr) {
                float s = AT(float, cr, 0x70);
                float* r;
                if (bone == 0) {
                    char* m = AT(char*, cr, 0);
                    float f1 = AT(float, m, 0x35c) * s;
                    float f2 = AT(float, m, 0x360) * s;
                    float f0 = s * AT(float, m, 0x358);
                    tmp[0] = ((AT(float, m, 0x364) * s + f0) + f0) * 0.5f;
                    tmp[1] = ((AT(float, m, 0x368) * s + f1) + f1) * 0.5f;
                    tmp[2] = ((AT(float, m, 0x36c) * s + f2) + f2) * 0.5f;
                    r = checkerlib::QuaternionVectorTransform(tq, (float*)(cr + 0x3c), tmp);
                } else {
                    char* m = AT(char*, bone, 0);
                    tmp[0] = s * AT(float, m, 0x144);
                    tmp[1] = AT(float, m, 0x148) * s;
                    tmp[2] = AT(float, m, 0x14c) * s;
                    float qb[4];
                    float* q = checkerlib::QuaternionProduct(qb, (float*)(cr + 0x3c), (float*)(bone + 0x1c));
                    r = checkerlib::QuaternionVectorTransform(tq, q, tmp);
                }
                pos[0] = r[0] + pos[0];
                pos[1] = r[1] + pos[1];
                pos[2] = r[2] + pos[2];
            }
        } else if (k == 0x20000) {
            if (outVec && cr) {
                float rnd[3];
                float* src = outVec;
                if (randomize) {
                    double a = gRandom.GenerateDouble();
                    double b = gRandom.GenerateDouble();
                    float c = (float)gRandom.GenerateDouble();
                    rnd[0] = c;
                    rnd[1] = (float)b;
                    rnd[2] = (float)a;
                    src = rnd;
                }
                float x = src[0], y = src[1], z = src[2];
                float* r;
                if (bone == 0) {
                    if (randomize) {
                        char* m = AT(char*, cr, 0);
                        float s = AT(float, cr, 0x70);
                        x = (s * AT(float, m, 0x364)) * x;
                        y = (AT(float, m, 0x368) * s) * y;
                        z = (AT(float, m, 0x36c) * s) * z;
                        outVec[0] = x; outVec[1] = y; outVec[2] = z;
                    }
                    float s = AT(float, cr, 0x70);
                    char* m = AT(char*, cr, 0);
                    tmp[0] = s * AT(float, m, 0x358) + x;
                    tmp[1] = AT(float, m, 0x35c) * s + y;
                    tmp[2] = AT(float, m, 0x360) * s + z;
                    r = checkerlib::QuaternionVectorTransform(tq, (float*)(cr + 0x3c), tmp);
                } else {
                    if (randomize) {
                        float s = AT(float, cr, 0x70);
                        char* m = AT(char*, bone, 0);
                        x = (x * 2.0f - 1.0f) * (AT(float, m, 0x138) * s);
                        y = (y * 2.0f - 1.0f) * (AT(float, m, 0x13c) * s);
                        z = (z * 2.0f - 1.0f) * (AT(float, m, 0x140) * s);
                        outVec[0] = x; outVec[1] = y; outVec[2] = z;
                    }
                    tmp[0] = x; tmp[1] = y; tmp[2] = z;
                    r = checkerlib::QuaternionVectorTransform(tq, (float*)(bone + 0x1c), tmp);
                }
                pos[0] = r[0] + pos[0];
                pos[1] = r[1] + pos[1];
                pos[2] = r[2] + pos[2];
            }
        } else if (k == 0x22000 && cr && bone) {
            char* m = AT(char*, bone, 0);
            float s = AT(float, cr, 0x70);
            tmp[0] = AT(float, m, 0x330) * s;
            tmp[1] = AT(float, m, 0x334) * s;
            tmp[2] = AT(float, m, 0x338) * s;
            float qb[4];
            float* q = checkerlib::QuaternionProduct(qb, (float*)(cr + 0x3c), (float*)(bone + 0x1c));
            float* r = checkerlib::QuaternionVectorTransform(tq, q, tmp);
            pos[0] = r[0] + pos[0];
            pos[1] = r[1] + pos[1];
            pos[2] = r[2] + pos[2];
        }

        // ---- absolute / relative / callback handling ----
        uint32_t k2 = flags & 0x11000;
        int flagByte = 0;
        bool doCb = false;
        if (k2 == 0x1000) {
            doCb = true;
        } else if (k2 == 0x10000) {
            flagByte = 1;
            doCb = true;
        } else if (k2 == 0x11000 && cr) {
            float ox = pos[0], oy = pos[1], oz = pos[2];
            tmp[0] = ox - AT(float, cr, 0x18);
            tmp[1] = oy - AT(float, cr, 0x1c);
            tmp[2] = oz - AT(float, cr, 0x20);
            float t[4];
            checkerlib::QuaternionVectorTransformInverse(t, (float*)(cr + 0x3c), tmp);
            float q1 = AT(float, cr, 0x40);
            float q0 = AT(float, cr, 0x3c);
            float q3 = AT(float, cr, 0x48);
            float q2 = AT(float, cr, 0x44);
            float s = AT(float, cr, 0x70);
            char* m = AT(char*, cr, 0);
            float d = (AT(float, m, 0x36c) * s + AT(float, m, 0x360) * s) - t[2];
            pos[0] = ((q0 * q2 + q1 * q3) * 2.0f) * d + ox;
            pos[1] = ((q2 * q1 - q0 * q3) * 2.0f) * d + oy;
            pos[2] = (1.0f - (q0 * q0 + q1 * q1) * 2.0f) * d + oz;
        }
        if (doCb) {
            if (cb == 0 || cb->fn == 0) {
                Unit(dirA);
                Unit(dirB);
                pos[2] = 0.0f;
            } else {
                usedCb = true;
                float r = cb->fn(cb->data, AT(int, owner, 4), pos, dirA, flagByte, 0);
                if (cb->enabled == 0) {
                    Unit(dirB);
                    pos[2] = r;
                } else {
                    float* n = NormalizeVec3(tq, (const float *)pos, 0);
                    dirB[0] = n[0]; dirB[1] = n[1]; dirB[2] = n[2];
                    pos[0] = n[0] * r;
                    pos[1] = n[1] * r;
                    pos[2] = n[2] * r;
                }
            }
        }
    }

    // ---- orientation output ---------------------------------------------------------------
    if (outQuat == 0) return true;
    {
        uint32_t k = flags & 0xe00;
        float m[9];
        float o1[3], o2[3];
        bool haveMat = false;
        if (k == 0x600) {
            if (!usedCb) {
                if (cb == 0 || cb->fn == 0 || cb->enabled == 0) {
                    Unit(dirB);
                } else {
                    float* n = NormalizeVec3(tq, (const float *)dirIn, 0);
                    dirB[0] = n[0]; dirB[1] = n[1]; dirB[2] = n[2];
                }
            }
            o1[0] = o1[1] = o1[2] = 0.0f;
            o2[0] = o2[1] = o2[2] = 0.0f;
            PerpPair(dirB, o1, o2);
            m[0] = o1[0]; m[1] = o2[0]; m[2] = dirB[0];
            m[3] = o1[1]; m[4] = o2[1]; m[5] = dirB[1];
            m[6] = o1[2]; m[7] = o2[2]; m[8] = dirB[2];
            haveMat = true;
        } else if (k == 0x200) {
            o1[0] = o1[1] = o1[2] = 0.0f;
            o2[0] = o2[1] = o2[2] = 0.0f;
            if (LengthSqVec3(dirIn2) >= 1e-06f) {
                float* n = NormalizeVec3(tq, (const float *)dirIn2, 0);
                dirB[0] = n[0]; dirB[1] = n[1]; dirB[2] = n[2];
            } else {
                float x = outQuat->mLeft, z = outQuat->mRight;
                dirB[2] = -((z * outQuat->mTop + x * outQuat->mBottom) * 2.0f);
                dirB[1] = -(1.0f - (x * x + z * z) * 2.0f);
                dirB[0] = -((x * outQuat->mTop - z * outQuat->mBottom) * 2.0f);
            }
            PerpPair(dirB, o1, o2);
            m[0] = o1[0]; m[1] = o2[0]; m[2] = dirB[0];
            m[3] = o1[1]; m[4] = o2[1]; m[5] = dirB[1];
            m[6] = o1[2]; m[7] = o2[2]; m[8] = dirB[2];
            haveMat = true;
        } else if (k == 0x400) {
            if (cr) {
                *outQuat = AT(EA::RectT_s009a_59e0<float>, cr, 0x3c);
            }
        } else if (k == 0x800) {
            if (!usedCb) {
                if (cb == 0 || cb->fn == 0) {
                    Unit(dirA);
                } else {
                    cb->fn(cb->data, AT(int, owner, 4), dirIn, dirA, (flags & 0x11000) == 0x10000, 0);
                }
            }
            o1[0] = o1[1] = o1[2] = 0.0f;
            o2[0] = o2[1] = o2[2] = 0.0f;
            PerpPair(dirA, o1, o2);
            m[0] = o1[0]; m[1] = o2[0]; m[2] = dirA[0];
            m[3] = o1[1]; m[4] = o2[1]; m[5] = dirA[1];
            m[6] = o1[2]; m[7] = o2[2]; m[8] = dirA[2];
            haveMat = true;
        } else if (k == 0xa00) {
            outQuat->mLeft = 0.0f; outQuat->mTop = 0.0f; outQuat->mRight = 0.0f; outQuat->mBottom = 1.0f;
        }
        if (haveMat) {
            float* q = checkerlib::matrix_to_quaternion(tq, m);
            *outQuat = *(EA::RectT_s009a_59e0<float>*)q;
        }
    }

    // ---- bone-driven rotation of the result -------------------------------------------------
    if (bone != 0 && 0.0f < AT(float, AT(char*, bone, 0), 0x10c)) {
        uint32_t k = flags & 0x70000000;
        if (k == 0x10000000)      outQuat->RotA(0.0f, 1.0f);
        else if (k == 0x20000000) outQuat->RotB(0.0f, 1.0f);
        else if (k == 0x30000000) outQuat->RotC(0.0f, 1.0f);
    }
    return true;
}
}  // namespace nSPCreatureAnim
