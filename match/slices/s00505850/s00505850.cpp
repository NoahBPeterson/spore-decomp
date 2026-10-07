// w1g1 slice s00505850 -- nSPSkinner / Simulator::cCreatureAbility helpers.
//
// Flags for this region: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE).
//
// 0x505850 is the 2.7 KB /Od point-to-triangle squared distance (Eberly); it is
// byte-exact with /Oi added (intrinsic fabs: fabs; fstp tmp; fld tmp).
// The remaining four functions are small ctors/dtors around
// nSPSkinner::cRTTBuffer and Simulator::cCreatureAbility; complete behavioural
// ports are given, but they are not byte-exact (class/vtable scheduling).

typedef unsigned int uint32_t;

inline void* operator new(unsigned int, void* p) { return p; }

void* ea_new(uint32_t size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  ea_free(void* p);                                                    // 0x00f47380
void  ea_delete(void* p);                                                  // operator_delete__

// ---------------------------------------------------------------------------
// @ 0x00505850  SqrDistancePointTriangle
// Squared distance from a point to the triangle (v0, v1, v2) (Eberly / Magic Software
// "MgcSqrDistance(point, triangle)"): writes the barycentric parameters s (along v1-v0) and
// t (along v2-v0) of the closest point and returns |squared distance|.
// ---------------------------------------------------------------------------
#include <math.h>
#pragma intrinsic(fabs)

struct Vector3 {
    float x, y, z;
};

float __cdecl SqrDistancePointTriangle(const Vector3* rkPoint, const Vector3* rkV0,
                                       const Vector3* rkV1, const Vector3* rkV2,
                                       float* pfSParam, float* pfTParam)
{
    Vector3 kDiff;
    kDiff.x = rkV0->x - rkPoint->x;
    kDiff.y = rkV0->y - rkPoint->y;
    kDiff.z = rkV0->z - rkPoint->z;
    Vector3 kDir;
    kDir.x = rkV1->x - rkV0->x;
    kDir.y = rkV1->y - rkV0->y;
    kDir.z = rkV1->z - rkV0->z;
    Vector3 kEdge1;
    kEdge1.x = rkV2->x - rkV0->x;
    kEdge1.y = rkV2->y - rkV0->y;
    kEdge1.z = rkV2->z - rkV0->z;
    float fA00 = kDir.x * kDir.x + kDir.y * kDir.y + kDir.z * kDir.z;
    float fA01 = kDir.x * kEdge1.x + kDir.y * kEdge1.y + kDir.z * kEdge1.z;
    float fA11 = kEdge1.x * kEdge1.x + kEdge1.y * kEdge1.y + kEdge1.z * kEdge1.z;
    float fB0 = kDiff.x * kDir.x + kDiff.y * kDir.y + kDiff.z * kDir.z;
    float fB1 = kDiff.x * kEdge1.x + kDiff.y * kEdge1.y + kDiff.z * kEdge1.z;
    float fC = kDiff.x * kDiff.x + kDiff.y * kDiff.y + kDiff.z * kDiff.z;
    float fDet = fabs(fA00 * fA11 - fA01 * fA01);
    float fS = fA01 * fB1 - fA11 * fB0;
    float fT = fA01 * fB0 - fA00 * fB1;
    float fSqrDist;

    if (fS + fT <= fDet) {
        if (fS < 0.0f) {
            if (fT < 0.0f) {  // region 4
                if (fB0 < 0.0f) {
                    fT = 0.0f;
                    if (-fB0 >= fA00) {
                        fS = 1.0f;
                        fSqrDist = fA00 + 2.0f * fB0 + fC;
                    } else {
                        fS = -fB0 / fA00;
                        fSqrDist = fB0 * fS + fC;
                    }
                } else {
                    fS = 0.0f;
                    if (fB1 >= 0.0f) {
                        fT = 0.0f;
                        fSqrDist = fC;
                    } else if (-fB1 >= fA11) {
                        fT = 1.0f;
                        fSqrDist = fA11 + 2.0f * fB1 + fC;
                    } else {
                        fT = -fB1 / fA11;
                        fSqrDist = fB1 * fT + fC;
                    }
                }
            } else {  // region 3
                fS = 0.0f;
                if (fB1 >= 0.0f) {
                    fT = 0.0f;
                    fSqrDist = fC;
                } else if (-fB1 >= fA11) {
                    fT = 1.0f;
                    fSqrDist = fA11 + 2.0f * fB1 + fC;
                } else {
                    fT = -fB1 / fA11;
                    fSqrDist = fB1 * fT + fC;
                }
            }
        } else if (fT < 0.0f) {  // region 5
            fT = 0.0f;
            if (fB0 >= 0.0f) {
                fS = 0.0f;
                fSqrDist = fC;
            } else if (-fB0 >= fA00) {
                fS = 1.0f;
                fSqrDist = fA00 + 2.0f * fB0 + fC;
            } else {
                fS = -fB0 / fA00;
                fSqrDist = fB0 * fS + fC;
            }
        } else {  // region 0
            // minimum at interior point
            float fInvDet = 1.0f / fDet;
            fS *= fInvDet;
            fT *= fInvDet;
            fSqrDist = fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) +
                       fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
        }
    } else {
        float fTmp0, fTmp1, fNumer, fDenom;

        if (fS < 0.0f) {  // region 2
            fTmp0 = fA01 + fB0;
            fTmp1 = fA11 + fB1;
            if (fTmp1 > fTmp0) {
                fNumer = fTmp1 - fTmp0;
                fDenom = fA00 - 2.0f * fA01 + fA11;
                if (fNumer >= fDenom) {
                    fS = 1.0f;
                    fT = 0.0f;
                    fSqrDist = fA00 + 2.0f * fB0 + fC;
                } else {
                    fS = fNumer / fDenom;
                    fT = 1.0f - fS;
                    fSqrDist = fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) +
                               fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
                }
            } else {
                fS = 0.0f;
                if (fTmp1 <= 0.0f) {
                    fT = 1.0f;
                    fSqrDist = fA11 + 2.0f * fB1 + fC;
                } else if (fB1 >= 0.0f) {
                    fT = 0.0f;
                    fSqrDist = fC;
                } else {
                    fT = -fB1 / fA11;
                    fSqrDist = fB1 * fT + fC;
                }
            }
        } else if (fT < 0.0f) {  // region 6
            fTmp0 = fA01 + fB1;
            fTmp1 = fA00 + fB0;
            if (fTmp1 > fTmp0) {
                fNumer = fTmp1 - fTmp0;
                fDenom = fA00 - 2.0f * fA01 + fA11;
                if (fNumer >= fDenom) {
                    fT = 1.0f;
                    fS = 0.0f;
                    fSqrDist = fA11 + 2.0f * fB1 + fC;
                } else {
                    fT = fNumer / fDenom;
                    fS = 1.0f - fT;
                    fSqrDist = fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) +
                               fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
                }
            } else {
                fT = 0.0f;
                if (fTmp1 <= 0.0f) {
                    fS = 1.0f;
                    fSqrDist = fA00 + 2.0f * fB0 + fC;
                } else if (fB0 >= 0.0f) {
                    fS = 0.0f;
                    fSqrDist = fC;
                } else {
                    fS = -fB0 / fA00;
                    fSqrDist = fB0 * fS + fC;
                }
            }
        } else {  // region 1
            fNumer = fA11 + fB1 - fA01 - fB0;
            if (fNumer <= 0.0f) {
                fS = 0.0f;
                fT = 1.0f;
                fSqrDist = fA11 + 2.0f * fB1 + fC;
            } else {
                fDenom = fA00 - 2.0f * fA01 + fA11;
                if (fNumer >= fDenom) {
                    fS = 1.0f;
                    fT = 0.0f;
                    fSqrDist = fA00 + 2.0f * fB0 + fC;
                } else {
                    fS = fNumer / fDenom;
                    fT = 1.0f - fS;
                    fSqrDist = fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) +
                               fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
                }
            }
        }
    }

    *pfSParam = fS;
    *pfTParam = fT;
    return fabs(fSqrDist);
}

// ---------------------------------------------------------------------------
struct cRTTBuffer { cRTTBuffer(int w, int h); };            // 100-byte object

struct cCreatureAbility {
    virtual void v0();      // vtbl_Simulator::cCreatureAbility[0]
    int*  mField4;          // +0x04
    void* mObj;             // +0x08
    void* mObj2;            // +0x0c
    void* mSlots[3];        // +0x10
    int   mParam;           // +0x1c
    float mF20, mF24, mF28, mF2c, mF30;
    uint32_t mKey;          // +0x34
    void* mHandle;          // +0x38
};

void* CreateRTT(int param)
{
    cRTTBuffer* p = (cRTTBuffer*)ea_new(100, "Skinner", 0, 0, 0, 0);
    if (p) return new ((void*)p) cRTTBuffer(param, param);
    return 0;
}

// @ 0x005062f0  (constructor)
cCreatureAbility* __fastcall cCreatureAbility_ctor(cCreatureAbility* self)
{
    self->mField4 = 0;
    self->mObj = ea_new(0x54, "Skinner", 0, 0, 0, 0);
    self->mObj2 = ea_new(0x54, "Skinner", 0, 0, 0, 0);
    self->mSlots[0] = 0;
    self->mSlots[1] = 0;
    self->mSlots[2] = 0;
    self->mF20 = 0.5f;
    self->mF24 = 1.0f;
    self->mF28 = 20.0f;
    self->mF2c = 1.0f;
    self->mF30 = 1.0f;
    self->mKey = 0;
    self->mHandle = 0;
    return self;
}

void CleanupResource(void* p);         // 0x00762a00
uint32_t HashName(const char* s);      // 0x007c3af0
void* Lookup(uint32_t k, int a, int b, int c);  // 0x00762b70

// @ 0x005064a0  (destructor)
void __fastcall cCreatureAbility_dtor(cCreatureAbility* self)
{
    CleanupResource(self->mHandle);
    self->mHandle = 0;
    self->mKey = 0;
    if (self->mObj) {
        ea_delete(self->mObj);
        self->mObj = 0;
    }
    if (self->mObj2) {
        ea_delete(self->mObj2);
        self->mObj2 = 0;
    }
}

// @ 0x00506590  (Setup)
void __fastcall cCreatureAbility_Setup(cCreatureAbility* self, int param)
{
    self->mSlots[0] = CreateRTT(param);
    self->mSlots[1] = CreateRTT(param);
    self->mSlots[2] = CreateRTT(param);
    self->mParam = param;
    self->mF20 = 0.5f;
    self->mF24 = 1.0f;
    self->mF28 = 20.0f;
    self->mF2c = 1.0f;
    self->mF30 = 1.0f;
}

struct Disposable { void Destroy(); };   // 0x00528e20

// @ 0x005066d0  (Cleanup)
void __fastcall cCreatureAbility_Cleanup(cCreatureAbility* self)
{
    for (int i = 0; i < 3; ++i) {
        if (self->mSlots[i] != 0) {
            ((Disposable*)self->mSlots[i])->Destroy();
            ea_free(self->mSlots[i]);
            self->mSlots[i] = 0;
        }
    }
}
