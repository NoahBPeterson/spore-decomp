// src/game/SPCreatureAnim/animation_events.cpp -- migrated from slice(s) s009a4c70, s009a3c80 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/animation_events.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/creature_instance_data.h"
#include <math.h>

// ---- items of slice s009a4c70 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
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

// @ 0x009a59a0
namespace nSPCreatureAnim {
float GetEventDataAsFloat(int p1, float* p2, int p3, void* p4, uint32_t p5, uint32_t p6, int p7)
{
    uint32_t bits = GetEventDataAs32Bits(p1, p2, p3, 0, p4, p5, p6, p7);
    return *(float*)&bits;
}
}  // namespace nSPCreatureAnim
