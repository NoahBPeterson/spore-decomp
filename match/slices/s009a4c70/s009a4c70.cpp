// Slice s009a4c70 (gold1 64): EA::RectT<float> planes rotations, checkerlib matrix->quaternion,
// nSPCreatureAnim::PlaySound and the event-data accessors.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// RotA/RotB/RotC are the three axis-plane rotations of a 4-float block (see the callers in
// s009a59e0, which call them on a quaternion with (0.0f, 1.0f)).  matrix_to_quaternion is the
// classic trace / largest-diagonal 3x3 -> quaternion conversion.
#include "types.h"
#include <math.h>

#define AT(T, p, off) (*(T*)((char*)(p) + (off)))

namespace EA {
template <typename T> class RectT { public:
    T mLeft, mTop, mRight, mBottom;
    RectT& operator=(const RectT& o);                 // 0x00572600
    void RotA(float c, float s);                      // 0x009a4c70 (thiscall, ret 8)
    void RotB(float c, float s);                      // 0x009a4d60
    void RotC(float c, float s);                      // 0x009a4e40
};
}

// @ 0x009a4c70
template <typename T>
void EA::RectT<T>::RotA(float c, float s)
{
    T x = mLeft, y = mTop, z = mRight, w = mBottom;
    T r0 = x * c + w * s - z * (T)0.0 + y * (T)0.0;
    T r1 = y * c + z * s + w * (T)0.0 - x * (T)0.0;
    T r2 = z * c - y * s + x * (T)0.0 + w * (T)0.0;
    T r3 = w * c - x * s - y * (T)0.0 - z * (T)0.0;
    mLeft = r0; mTop = r1; mRight = r2; mBottom = r3;
}
template void EA::RectT<float>::RotA(float, float);

// @ 0x009a4d60
template <typename T>
void EA::RectT<T>::RotB(float c, float s)
{
    T x = mLeft, y = mTop, z = mRight, w = mBottom;
    T r0 = x * c + w * (T)0.0 - z * s + y * (T)0.0;
    T r1 = y * c + w * s + z * (T)0.0 - x * (T)0.0;
    T r2 = z * c - y * (T)0.0 + x * s + w * (T)0.0;
    T r3 = w * c - x * (T)0.0 - y * s - z * (T)0.0;
    mLeft = r0; mTop = r1; mRight = r2; mBottom = r3;
}
template void EA::RectT<float>::RotB(float, float);

// @ 0x009a4e40
template <typename T>
void EA::RectT<T>::RotC(float c, float s)
{
    T x = mLeft, y = mTop, z = mRight, w = mBottom;
    T r0 = x * c + w * (T)0.0 - z * (T)0.0 + y * s;
    T r1 = y * c + z * (T)0.0 + w * (T)0.0 - x * s;
    T r2 = z * c - y * (T)0.0 + w * s + x * (T)0.0;
    T r3 = w * c - x * (T)0.0 - y * (T)0.0 - z * s;
    mLeft = r0; mTop = r1; mRight = r2; mBottom = r3;
}
template void EA::RectT<float>::RotC(float, float);

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

// ============================================================================================
// nSPCreatureAnim
// ============================================================================================
namespace nSPCreatureAnim {

// Audio event interface reached through EA::Audio::GetSystemAT().  Slot addresses decoded from
// the disassembly (+0x20, +0x24, +0x38, +0x3c, +0x40, +0x44, +0x58).  Unused slots are pads.
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

// SP::AudioSystem() returns a different object; its +0x40 takes one int.
struct AudioSystemObj {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void CommitId(int id);                // +0x40
};

// A small thiscall helper on creature+0x15b8 that returns a pointer pair (0x00a09f50).
struct RollList { int* End(); };

uint32_t GetEventDataAs32Bits(int a0, void* a1, int a2, int a3, void* creature, uint32_t index,
                              uint32_t defaultValue, int a7);                     // 0x009a5860

// classic bit interleave of the two masks (0x009a4660)
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

// thiscall key scan over a table of {key, ...} entries of 0x14 bytes (0x0099c470)
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

// @ 0x009a5860
uint32_t GetEventDataAs32Bits(int a0, void* a1, int a2, int a3, void* creature, uint32_t index,
                              uint32_t defaultValue, int a7)
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

// @ 0x009a59a0
float GetEventDataAsFloat(int p1, float* p2, int p3, void* p4, uint32_t p5, uint32_t p6, int p7)
{
    uint32_t bits = GetEventDataAs32Bits(p1, p2, p3, 0, p4, p5, p6, p7);
    return *(float*)&bits;
}

// declared callees
uint32_t EvaluateContextTargetQuery(void* p1, uint32_t p2, int p3, uint32_t* p4, int p5, char p6);
bool     CheckEventLocationType(uint32_t flags, int loc);

// @ 0x009a5650
uint32_t ComputeEventLocationData(uint32_t flags, uint32_t* param_2, uint32_t param_3,
                                  uint32_t* owner, uint32_t p5, int p6, int* outLoc,
                                  int* outLoc2, uint8_t* outByte)
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

AudioIface* GetSystemAT();                                  // ::EA::Audio::GetSystemAT 0xa206f0
AudioSystemObj* AudioSystem();                              // SP::AudioSystem 0x0067cb00

// @ 0x009a5090
uint32_t PlaySound(char* name, int* creature, uint32_t boneIdx, float* vec, char flag5,
                   char flag6, float f7)
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

} // namespace nSPCreatureAnim
