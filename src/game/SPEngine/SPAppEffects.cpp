// src/game/SPEngine/SPAppEffects.cpp -- migrated from slice(s) s007ce500, s007cd6d0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppEffects.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#ifndef SPORE_S007CA950_H
#endif  // SPORE_S007CA950_H

// ---- items of slice s007ce500 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" double __cdecl sqrt(double);
extern const float g_153d63c;   // 0x0153d63c
extern const float g_153d638;   // 0x0153d638
extern uint32_t    g_153d634;   // 0x0153d634
extern "C" float* FUN_007cdbe0(float* out, char* p);       // 0x007cdbe0
extern "C" float* FUN_00a816d0();                          // 0x00a816d0
extern "C" float* FUN_00a817c0(float* a, char* p, float f); // 0x00a817c0
extern "C" void   FUN_007cdee0(float* v);                  // 0x007cdee0
extern "C" void   FUN_007cda70(float* v);                  // 0x007cda70
extern "C" double FUN_007cdb90(float* v);                  // 0x007cdb90
#pragma intrinsic(_InterlockedExchangeAdd)
struct RandomLinearCongruential {          // thiscall receiver at 0x016778dc
    double RandomDoubleUniform();
};
extern RandomLinearCongruential sRandom;   // 0x016778dc
struct IFilter {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual bool Test(float* pos, float* a, float* b, int c, int d, int e); // slot 4
};
struct IVec3Provider {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void a4();
    virtual void a5();
    virtual bool Contains(float* v);       // slot 6 (0x18)
    virtual float Get(float* v);           // slot 7 (0x1c)
    virtual void Lambda(float* out, float* v); // slot 8 (0x20)
    virtual void Get2(float* out, float* v);   // slot 9 (0x24)
    virtual void Sub(float* out, float* v);    // slot 10 (0x28)
};
struct IPropertyManager {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual bool GetProperty(uint32_t key, uint32_t hash, void* out);  // 0x2c
};
struct GroundCoverConfig;
template <typename T> struct AutoRefT {
    T* mpObject;
    AutoRefT& operator=(T* p)
    {
        if (p != mpObject) {
            T* pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
struct GroundCoverConfig {
    virtual int AddRef();           // slot 0
    virtual int Release();          // slot 1 (0x4)
};
extern "C" IPropertyManager* PropertyManager();   // 0x0067de30
extern AutoRefT<GroundCoverConfig> sGroundCoverConfig;   // 0x01636e18
extern "C" void FUN_007d4460();
extern "C" void FUN_007d5ff0();
extern "C" void FUN_007e09a0();
extern "C" void FUN_007e12a0();
extern "C" void FUN_007ef270();
extern "C" void FUN_007efa10();
extern "C" void FUN_007edc10();
extern "C" void FUN_007ee450();
extern "C" void FUN_00a99150();
extern "C" void FUN_007d7f40();
extern "C" void FUN_007cdff0();
extern "C" void FUN_00aa7fa0(int, void (*)());
extern "C" void UpdateFromGroundCoverConfig();
// ---- items of slice s007ce500 end

// @ 0x007cdb90
void cConfigManagerUnnamedB90(void*)
{}

// @ 0x007cdcd0
void UpdateFromGroundCoverConfig(void*)
{}

// @ 0x007cdd80
void cConfigManagerUnnamedD80(void*)
{}

// @ 0x007cddc0
void cConfigManagerUnnamedDC0(void*)
{}

// @ 0x007cde30
void cConfigManagerUnnamedE30(void*)
{}

// @ 0x007cdee0
void TransformVectorByMatrix(void*, float*)
{}

// @ 0x007cdff0
void UpdateFloatAnim(void*, void*, float)
{}

// @ 0x007ce500
int GroundCoverCirclePhysics(char* self, float dt, char* p3, char* p4)
{
    float acc = dt + *(float*)(self + 8);
    *(float*)(self + 8) = acc;
    if (*(float*)(self + 0xc) <= acc)
        return 0;

    float m0 = *(float*)(p4 + 0xcc);
    float m1 = *(float*)(p4 + 0xd0);
    float m2 = *(float*)(p4 + 0xd4);
    float vx = m0, vy = m1, vz = m2;
    if (*(uint8_t*)(p4 + 0x100) & 2) {
        vx = *(float*)(p4 + 0x12c) * m2 + *(float*)(p4 + 0x120) * m1 + *(float*)(p4 + 0x114) * m0;
        vy = *(float*)(p4 + 0x118) * m0 + *(float*)(p4 + 0x130) * m2 + *(float*)(p4 + 0x124) * m1;
        vz = *(float*)(p4 + 0x11c) * m0 + *(float*)(p4 + 0x134) * m2 + *(float*)(p4 + 0x128) * m1;
    }
    float k = *(float*)(p4 + 0x110);
    float* pos = (float*)(self + 0x10);
    float cx = *(float*)(p4 + 0x104) + k * vx;
    float sx0 = *pos;
    float cy = *(float*)(p4 + 0x108) + k * vy;
    float sy0 = *(float*)(self + 0x14);
    float cz = *(float*)(p4 + 0x10c) + k * vz;
    float sz0 = *(float*)(self + 0x18);
    float rx = sx0, ry = sy0, rz = sz0;
    if (*(uint8_t*)(p4 + 0x100) & 2) {
        rx = *(float*)(p4 + 0x12c) * sz0 + *(float*)(p4 + 0x120) * sy0 + sx0 * *(float*)(p4 + 0x114);
        ry = *(float*)(p4 + 0x118) * sx0 + *(float*)(p4 + 0x130) * sz0 + *(float*)(p4 + 0x124) * sy0;
        rz = *(float*)(p4 + 0x11c) * sx0 + *(float*)(p4 + 0x134) * sz0 + *(float*)(p4 + 0x128) * sy0;
    }
    float k2 = *(float*)(p4 + 0x110);
    float px = *(float*)(p4 + 0x104) + rx * k2;
    float py = *(float*)(p4 + 0x108) + ry * k2;
    float pz = *(float*)(p4 + 0x10c) + rz * k2;

    float A = (cx * cx + cz * cz) + cy * cy;
    float B = (px * cx + pz * cz) + py * cy;
    float C = (px * px + pz * pz) + py * py;

    if (B * B < ((A / (g_153d63c * g_153d63c + A)) * C) * A) {
        double r = sRandom.RandomDoubleUniform();
        if ((float)r >= g_153d638) {
            float t = B / A;
            double r2 = sRandom.RandomDoubleUniform();
            double s = (1.0 - r2) * ((double)t / sqrt((double)C - (double)t * (double)B)) * (double)g_153d63c + r2;
            float f = (float)(s + s);
            px = (cx * t - px) * f + px;
            py = (cy * t - py) * f + py;
            pz = (cz * t - pz) * f + pz;
            *pos = px;
            *(float*)(self + 0x14) = py;
            *(float*)(self + 0x18) = pz;
        } else if (*(float*)(p3 + 100) < 0.0f) {
            float* v;
            if ((*(uint32_t*)(p3 + 8) >> 4 & 1) == 0)
                v = FUN_007cdbe0(&cx, p4 + 0x1c0);
            else
                v = FUN_00a816d0();
            *pos = v[0]; *(float*)(self + 0x14) = v[1]; *(float*)(self + 0x18) = v[2];
            FUN_007cdee0(pos);
        } else {
            float* v = FUN_00a817c0(&cx, p4 + 0x1c0, *(float*)(p3 + 100));
            *pos = v[0]; *(float*)(self + 0x14) = v[1]; *(float*)(self + 0x18) = v[2];
            FUN_007cdee0(pos);
        }
        *(uint32_t*)(self + 0x34) = 0x3f800000;
        if (*(char*)(p4 + 0x210) != 0) {
            uint32_t* it = *(uint32_t**)(p4 + 0x1e4);
            int base = *(int*)(p4 + 0x1fc);
            if (it != *(uint32_t**)(p4 + 0x1e8)) {
                do {
                    if ((float)(*(uint32_t*)it[1] & g_153d634) != 0.0f) {
                        int iv = (it[2] == 0) ? 0 : (int)it[3] + base;
                        IFilter* f = (IFilter*)it[0];
                        if (f->Test(pos, pos, &cx, 0, iv, 0)) {
                            float w = *(float*)((char*)it[1] + 0x20);
                            if (w != 0.0f) {
                                *pos = cx * w + *pos;
                                *(float*)(self + 0x14) += cy * w;
                                *(float*)(self + 0x18) += cz * w;
                            }
                            break;
                        }
                    }
                    it += 6;
                } while (it != *(uint32_t**)(p4 + 0x1e8));
            }
        }
        if (((*(uint32_t*)(p3 + 8) >> 5 & 1) != 0) && *(int*)(p4 + 0x1b4) != 0) {
            float a = *pos, b = *(float*)(self + 0x14), c = *(float*)(self + 0x18);
            if (*(char*)(p4 + 0x1bd) == 0) FUN_007cda70(&a); else FUN_007cdee0(&a);
            IVec3Provider* p = *(IVec3Provider**)(p4 + 0x1b4);
            if (p->Contains(&a)) {
                float d = p->Get(&a);
                c = d;
                float e = *(float*)(p4 + 0x1c8);
                float g = *(float*)(p4 + 0x1d4);
                c = (float)(FUN_007cdb90(&e) + (double)c);
                if (*(char*)(p4 + 0x1bd) == 0) FUN_007cdee0(&a); else FUN_007cda70(&a);
                *pos = a; *(float*)(self + 0x14) = b; *(float*)(self + 0x18) = c;
            }
        }
        if (*(int*)(p4 + 0x1b8) != 0) {
            float a = *pos, b = *(float*)(self + 0x14), c = *(float*)(self + 0x18);
            if (*(char*)(p4 + 0x1be) == 0) FUN_007cda70(&a); else FUN_007cdee0(&a);
            IVec3Provider* p = *(IVec3Provider**)(p4 + 0x1b8);
            if (p->Contains(&a)) {
                p->Sub(&a, &a);
                *(float*)(self + 0x38) = a;
                *(float*)(self + 0x3c) = b;
                *(float*)(self + 0x34) = c * *(float*)(self + 0x34);
                *(float*)(self + 0x40) = *(float*)(self + 0x18);
            }
        }
        if (*(int*)(p4 + 0x1b4) != 0) {
            float a = *pos, b = *(float*)(self + 0x14), c = *(float*)(self + 0x18);
            if (*(char*)(p4 + 0x1bd) == 0) FUN_007cda70(&a); else FUN_007cdee0(&a);
            float d = (*(IVec3Provider**)(p4 + 0x1b4))->Get(&a);
            if (d < 0.5f) *(uint32_t*)(self + 0x34) = 0;
        }
    }
    return 1;
}

// @ 0x007cec80
namespace SP {
void InitAppEffects()
{
    FUN_007d4460();
    FUN_007d5ff0();
    FUN_007e09a0();
    FUN_007e12a0();
    FUN_007ef270();
    FUN_007efa10();
    FUN_007edc10();
    FUN_007ee450();
    FUN_00a99150();
    FUN_007d7f40();
    FUN_00aa7fa0(3, FUN_007cdff0);
    FUN_00aa7fa0(4, FUN_007cdff0);
    IPropertyManager* pm = PropertyManager();
    sGroundCoverConfig = (GroundCoverConfig*)0;
    if (pm->GetProperty(0xc6db66f9, 0xea5118b1, &sGroundCoverConfig))
        UpdateFromGroundCoverConfig();
}
}  // namespace SP
