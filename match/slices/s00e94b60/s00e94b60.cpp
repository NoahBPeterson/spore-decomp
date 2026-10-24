// Slice s00e94b60: SP::cVehicleView - constructor, destructor and the four
// payload methods (FUN_00e94d10 factory, FUN_00e94e50 tether-sample,
// UpdateTowedItem and ConnectBalloonString).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <new>
#include <math.h>

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) { x = a; y = b; z = c; }
};

#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))
#define VTBLADDR(x)   ((void*)(&(x)))

// ---------------------------------------------------------------------------------------------
// free / cdecl helpers
// ---------------------------------------------------------------------------------------------
extern "C" void* __cdecl FUN_00f473a0(int size, const char* file, int a, int b, int c, int d); // 0x00f473a0 operator_new
extern "C" void* __cdecl FUN_00b3d520(Vec3* pos, void* parent);        // 0x00b3d520 SP::GonzagoModelWorld
extern "C" void* __cdecl FUN_00b5b800(void);                            // 0x00b5b800 SP::GetCurrentGameMode
extern       void  __cdecl FUN_00572020(uint32_t handle, int flag);     // 0x00572020
extern       void  __cdecl FUN_00cc4160(float* dst, float* src);        // 0x00cc4160
extern       void* __cdecl FUN_00f47380(void* p);                       // 0x00f47380 operator_delete_array
extern       void  __cdecl FUN_0059c190(float* out, void* quat);        // 0x0059c190 Matrix3FromQuaternion
extern       const char aSimulatorCVehicleView[];                       // 0x01460cdc "Simulator/cVehicleView"

// ---------------------------------------------------------------------------------------------
// thiscall callees, declared as members of a host class so `this` travels in ecx
// ---------------------------------------------------------------------------------------------
class tHost {
public:
    void   __thiscall FUN_00b63890();                 // 0x00b63890 SP::cGonzagoTimer::cGonzagoTimer
    void   __thiscall FUN_00b638b0();                 // 0x00b638b0 SP::cGonzagoTimer::~cGonzagoTimer
    void*  __thiscall FUN_00c9f650(void* out);        // 0x00c9f650
    void   __thiscall FUN_0041cb40(void* src);        // 0x0041cb40 rw::math::Matrix3::Assign
    void   __thiscall FUN_005a2d90(float angle);      // 0x005a2d90 cXform::PreRotateX
};

// ---------------------------------------------------------------------------------------------
// data globals
// ---------------------------------------------------------------------------------------------
extern float  DAT_01485720;                    // 0x01485720 1.0f
extern float  DAT_01486114;                    // 0x01486114 2.5f
extern float  DAT_01486110;                    // 0x01486110 5.0f
extern float  DAT_014853e0;                    // 0x014853e0 tether angle bias
extern float  DAT_016c5ca0;                    // 0x016c5ca0 mAnimator default
extern float  DAT_016c5ca4;                    // 0x016c5ca4 towed position x default
extern float  DAT_016c5ca8;                    // 0x016c5ca8 towed position y default
extern float  DAT_013eba80;                    // 0x013eba80
extern float  DAT_016c62ac;                    // 0x016c62ac
extern float  DAT_016c62b0;                    // 0x016c62b0
extern float  DAT_016c62b4;                    // 0x016c62b4
extern float  DAT_016c6288[];                  // 0x016c6288 identity matrix source
extern uint32_t DAT_015a8a48;                  // 0x015a8a48
extern uint32_t DAT_015a8a4c;                  // 0x015a8a4c
extern uint32_t DAT_015a8a50;                  // 0x015a8a50
extern void*  DAT_01654c10;                    // 0x01654c10 space game-mode singleton
extern void*  DAT_0137e8e0;                    // 0x0137e8e0

// ---------------------------------------------------------------------------------------------
// cTransform - the xform blob passed to the towed-item update
// ---------------------------------------------------------------------------------------------
struct cTransform {
    uint16_t mFlags;              // +0x00
    uint16_t mModificationCount;  // +0x02
    float    mRotation[9];        // +0x04
    Vec3     mTranslation;        // +0x28
    float    mScale;              // +0x34
};

// ---------------------------------------------------------------------------------------------
// base class: only the offsets that matter (size 0x38)
// ---------------------------------------------------------------------------------------------
class cSpatialObjectView {
public:
    cSpatialObjectView();                       // 0x00e92af0
    virtual ~cSpatialObjectView();              // 0x00e92660
    uint8_t m004[0x14];                         // +0x04
    Vec3    mColor;                             // +0x18
    uint8_t m024[0x14];                         // +0x24 -> +0x38
};

// ---------------------------------------------------------------------------------------------
class cVehicleView : public cSpatialObjectView {
public:
    uint8_t  m038[0x20];                        // +0x038 cGonzagoTimer (effects)
    uint8_t  m058[0x20];                        // +0x058 cGonzagoTimer (path)
    uint8_t  m078[0x20];                        // +0x078 cGonzagoTimer (trail)
    uint32_t m98;                               // +0x098 elapsed-timer running handle
    uint32_t m9c;                               // +0x09c elapsed-timer callback
    uint32_t ma0;                              // +0x0a0 movement sound id
    float    ma4;                               // +0x0a4 elapsed-timer offset
    float    ma8;                               // +0x0a8 desired scale
    float    mac;                               // +0x0ac current scale
    uint8_t  mb0;                               // +0x0b0 zoom-out scale (byte)
    uint8_t  mPad_b1[3];                        // +0x0b1
    float    mb4;                               // +0x0b4 animator / towed x
    float    mb8;                               // +0x0b8 towed position y
    float    mbc;                               // +0x0bc towed position z
    float    mc0;                               // +0x0c0
    float    mc4;                               // +0x0c4 current tilt angle
    void*    mc8;                               // +0x0c8 selection effect
    void*    mcc;                               // +0x0cc length-of-tether-at-rest handle

    cVehicleView();
    ~cVehicleView();

    void* __thiscall FUN_00e94d10(void* param_1);
    void  __thiscall FUN_00e94e50(int param_2);
    void  __thiscall UpdateTowedItem(void* param_2, void* param_3, int param_4, char param_5);
    void  __thiscall ConnectBalloonString(int param_2, void* param_3);
};

// =============================================================================================
// 0x00e94b60
// =============================================================================================
// @ 0x00e94b60
cVehicleView::cVehicleView()
{
    ((tHost*)((char*)this + 0x38))->FUN_00b63890();
    ((tHost*)((char*)this + 0x58))->FUN_00b63890();
    ((tHost*)((char*)this + 0x78))->FUN_00b63890();

    mac = 2.5f;
    m98 = 0;
    m9c = 0;
    ma0 = 0;
    ma4 = 1.0f;
    ma8 = 1.0f;
    mb0 = 0;
    mb4 = DAT_016c5ca0;
    mb8 = DAT_016c5ca4;
    mbc = DAT_016c5ca8;
    mc0 = 0.0f;
    mc4 = 5.0f;
    mc8 = 0;
    mcc = 0;
    Vec3 one(1.0f, 1.0f, 1.0f);
    mColor = one;
}

// =============================================================================================
// 0x00e94c50
// =============================================================================================
// @ 0x00e94c50
cVehicleView::~cVehicleView()
{
    uint32_t handle = m98;
    if (handle != 0) {
        FUN_00572020(handle, 0);
    }

    if (mc8 != 0) {
        ((void(__thiscall*)(void*, int))VFN(mc8, 0xc))(mc8, 0);
        void* p = mc8;
        if (p != 0) {
            mc8 = 0;
            ((void(__thiscall*)(void*))VFN(p, 4))(p);
        }
    }

    if (mcc != 0) {
        ((void(__thiscall*)(void*, int))VFN(mcc, 0xc))(mcc, 0);
        void* p = mcc;
        if (p != 0) {
            mcc = 0;
            ((void(__thiscall*)(void*))VFN(p, 4))(p);
        }
    }

    if (mcc != 0) {
        ((void(__thiscall*)(void*))VFN(mcc, 4))(mcc);
    }
    if (mc8 != 0) {
        ((void(__thiscall*)(void*))VFN(mc8, 4))(mc8);
    }

    ((tHost*)((char*)this + 0x78))->FUN_00b638b0();
    ((tHost*)((char*)this + 0x58))->FUN_00b638b0();
    ((tHost*)((char*)this + 0x38))->FUN_00b638b0();
}

// =============================================================================================
// 0x00e94d10
// =============================================================================================
// @ 0x00e94d10
void* __thiscall cVehicleView::FUN_00e94d10(void* param_1)
{
    cVehicleView* pNew = (cVehicleView*)FUN_00f473a0(0xd0, aSimulatorCVehicleView, 0, 0, 0, 0);
    if (pNew != 0) {
        pNew = new (pNew) cVehicleView();       // cVehicleView::cVehicleView
    }

    if (param_1 != 0) {
        void* iVar4 = ((void*(__thiscall*)(void*, uint32_t))VFN(param_1, 0xc))(param_1, 0x137e8e0);
        if (iVar4 != 0) {
            void* pSub = (void*)((char*)iVar4 + 0x34);
            uint8_t cVar1 = ((uint8_t(__thiscall*)(void*))VFN(pSub, 0x90))(pSub);
            if (cVar1 == 0) {
                ((void(__thiscall*)(void*, void*))VFN(pNew, 0x24))(pNew, iVar4);
            } else {
                float* pf = (float*)((void*(__thiscall*)(void*))VFN(pSub, 0x98))(pSub);
                Vec3 pos;
                pos.x = pf[0];
                pos.y = pf[1];
                pos.z = pf[2];
                void* model = FUN_00b3d520(&pos, (void*)((char*)this + 0x18));
                ((void(__thiscall*)(void*, void*, void*))VFN(pNew, 0x28))(pNew, param_1, model);
                void* r = ((void*(__thiscall*)(void*))VFN(pNew, 0x2c))(pNew);
                if (r != 0) {
                    if (FUN_00b5b800() == DAT_01654c10) {
                        *(uint32_t*)((char*)r + 4) &= 0xfffffffb;
                        pNew->mColor.x = *(float*)&DAT_015a8a48;
                        pNew->mColor.y = *(float*)&DAT_015a8a4c;
                        pNew->mColor.z = *(float*)&DAT_015a8a50;
                    } else {
                        *(uint32_t*)((char*)r + 4) |= 4;
                        Vec3 tmp;
                        void* q = ((tHost*)param_1)->FUN_00c9f650(&tmp);
                        float* pq = (float*)q;
                        pNew->mColor.x = pq[0];
                        pNew->mColor.y = pq[1];
                        pNew->mColor.z = pq[2];
                    }
                    *(float*)((char*)r + 0x4c) = pNew->mColor.x;
                    *(float*)((char*)r + 0x50) = pNew->mColor.y;
                    *(float*)((char*)r + 0x54) = pNew->mColor.z;
                    return pNew;
                }
            }
        }
    }
    return pNew;
}

// =============================================================================================
// 0x00e94e50
// =============================================================================================
// @ 0x00e94e50
void __thiscall cVehicleView::FUN_00e94e50(int param_2)
{
    void* pSub = (void*)((char*)param_2 + 0x34);

    mc0 = 0.0f;

    float* pf = (float*)((void*(__thiscall*)(void*))VFN(pSub, 0x2c))(pSub);
    mb4 = pf[0];
    mb8 = pf[1];
    mbc = pf[2];

    float fAngle = ((float(__thiscall*)(void*))VFN(pSub, 0x70))(pSub);
    fAngle = -(fAngle + DAT_014853e0);

    float* pr = (float*)((void*(__thiscall*)(void*, void*))VFN(pSub, 0x5c))(pSub, (void*)0);
    mb4 = pr[0] * fAngle + mb4;
    mb8 = pr[1] * fAngle + mb8;
    mbc = pr[2] * fAngle + mbc;
}

// =============================================================================================
// 0x00e94f30
// =============================================================================================
// @ 0x00e94f30
void __thiscall cVehicleView::UpdateTowedItem(void* param_2, void* param_3, int param_4, char param_5)
{
    void* piVar8 = (void*)((char*)param_2 + 0x34);

    if (((uint8_t(__thiscall*)(void*))VFN(piVar8, 0x48))(piVar8) == 0) return;

    float fVar4 = (float)param_4;
    if (param_4 < 0) {
        fVar4 += 4.2949673e9f;
    }
    fVar4 *= 0.002f;

    float* pfVar6 = (float*)((void*(__thiscall*)(void*))VFN(piVar8, 0x2c))(piVar8);
    float fVar18 = pfVar6[0];
    float fVar1 = pfVar6[1];
    float fVar2 = pfVar6[2];

    float fVar15 = 1.0f / sqrtf((fVar2 * fVar2 + (fVar1 * fVar1 + fVar18 * fVar18)) + 1e-08f);
    float fVar11 = fVar15 * fVar18;
    float fVar13 = fVar1 * fVar15;
    fVar15 = fVar2 * fVar15;

    float stack_74 = fVar11;
    float stack_70 = fVar13;
    float stack_6c = fVar15;

    float fVar17;
    float fVar12, fVar14, fVar16;
    if (param_5 == 0) {
        float fVar10 = ((float(__thiscall*)(void*))VFN(piVar8, 0x70))(piVar8);
        fVar17 = -(fVar10 + 4.0f);
        float* pS = (float*)((void*(__thiscall*)(void*, void*))VFN(piVar8, 0x5c))(piVar8, (void*)0);
        fVar12 = pS[0];
        fVar14 = pS[1];
        fVar16 = pS[2];
    } else {
        int iVar7 = ((int(__thiscall*)(void*))VFN(piVar8, 0x68))(piVar8);
        fVar17 = *(float*)(iVar7 + 0x14) + mc4;
        fVar12 = fVar11;
        fVar14 = fVar13;
        fVar16 = fVar15;
    }

    float stack_78 = (fVar16 * fVar17 + fVar2) - mb8;
    float stack_7c = (fVar14 * fVar17 + fVar1) - mb4;
    float stack_80 = (fVar12 * fVar17 + fVar18) - mbc;

    float fOld4 = mb4;
    float fOldY = mb8;
    mb4 = mb4 + stack_80 * fVar4;
    mb8 = stack_7c * fVar4 + fOldY;
    mbc = stack_78 * fVar4 + fOld4;

    float* pfB = (float*)((void*(__thiscall*)(void*, void*))VFN(piVar8, 0x5c))(piVar8, (void*)0);

    float af[4];
    af[0] = fVar13 * pfB[1] - fVar11 * pfB[2];
    af[1] = fVar2 * pfB[2] - fVar13 * pfB[0];
    af[2] = fVar11 * pfB[0] - fVar2 * pfB[1];
    fVar18 = 1.0f / sqrtf(af[1] * af[1] + (af[2] * af[2] + af[0] * af[0]));
    af[0] = fVar18 * af[0];
    af[2] = af[2] * fVar18;
    af[1] = af[1] * fVar18;

    fVar18 = af[2] * fVar11 - af[1] * fVar13;
    float fStack_20 = af[1] * fVar2 - fVar11 * af[0];
    float fStack_24 = fVar13 * af[0] - af[2] * fVar2;
    af[3] = 1.0f / sqrtf(fVar18 * fVar18 + (fStack_24 * fStack_24 + fStack_20 * fStack_20));
    fStack_20 = fStack_20 * af[3];
    fStack_24 = fStack_24 * af[3];
    af[3] = af[3] * fVar18;

    cTransform xf;
    xf.mTranslation.x = DAT_016c62ac;
    xf.mTranslation.y = DAT_016c62b0;
    xf.mTranslation.z = DAT_016c62b4;
    xf.mFlags = 0;
    xf.mModificationCount = 0;
    xf.mScale = 1.0f;
    ((tHost*)&xf.mRotation)->FUN_0041cb40((void*)DAT_016c6288);

    float fPrevZ = mbc;
    for (int i = 0; i < 9; i++) {
        xf.mRotation[i] = af[i];
    }
    xf.mFlags = (uint16_t)(xf.mFlags | 2);
    xf.mModificationCount = (uint16_t)(xf.mModificationCount + 1);

    fVar18 = (sqrtf(stack_80 * stack_80 + (stack_7c * stack_7c + fVar4 * fVar4)) * 0.035f - fPrevZ) * fVar15 + fPrevZ;
    mbc = fVar18;
    ((tHost*)&xf)->FUN_005a2d90(fVar18);

    xf.mTranslation.z = mb8;
    xf.mTranslation.x = mb4;
    xf.mTranslation.y = mb8;
    xf.mFlags = (uint16_t)((uint16_t)(xf.mModificationCount + 1) << 16 | xf.mFlags | 4);

    ((void(__thiscall*)(void*, void*))VFN(param_2, 0x18))(param_2, &xf);
}

// =============================================================================================
// 0x00e953a0
// =============================================================================================
// @ 0x00e953a0
void __thiscall cVehicleView::ConnectBalloonString(int param_2, void* param_3)
{
    void* piVar6 = (void*)((char*)param_2 + 0x34);

    if (((uint8_t(__thiscall*)(void*))VFN(piVar6, 0x48))(piVar6) == 0) return;

    float* pfVar3 = (float*)((void*(__thiscall*)(void*))VFN(piVar6, 0x2c))(piVar6);
    float fStack_13c = pfVar3[0];
    float fStack_138 = pfVar3[1];
    float fStack_134 = pfVar3[2];

    int iVar4 = ((int(__thiscall*)(void*))VFN(piVar6, 0x68))(piVar6);
    float fStack_130 = *(float*)(iVar4 + 0x14) * 0.85f;

    void* uVar5 = ((void*(__thiscall*)(void*))VFN(piVar6, 0x30))(piVar6);
    float afM[6];
    FUN_0059c190(afM, uVar5);

    float fStack_128 = afM[1] * fStack_130 + fStack_138;
    float fStack_124 = afM[2] * fStack_130 + fStack_134;
    float fStack_12c = afM[0] * fStack_130 + fStack_13c;

    float fStack_110 = (mb4 - fStack_128) * 0.0625f;
    float fStack_114 = (mbc - fStack_12c) * 0.0625f;
    float fStack_10c = (mb8 - fStack_124) * 0.0625f;

    float fStack_118 = 1.0f / sqrtf((fStack_12c * fStack_12c + (fStack_124 * fStack_124 + fStack_128 * fStack_128)) + 1e-08f);
    float fStack_120 = fStack_118 * fStack_12c;
    float fStack_11c = fStack_128 * fStack_118;
    fStack_118 = fStack_118 * fStack_124;

    float pts[51];
    int n = 0;
    float fStack_130b = 0.0f;
    do {
        float fPrev = fStack_130b;
        fStack_130b = (float)((8.0f - (float)(int)fStack_130b) < 0 ? -((8.0f - (float)(int)fStack_130b)) : (8.0f - (float)(int)fStack_130b)) * 0.125f;
        float fVar7 = 1.0f - fStack_130b * fStack_130b;
        fStack_13c = fStack_12c - fStack_120 * fVar7;
        fStack_138 = fStack_128 - fStack_11c * fVar7;
        fStack_134 = fStack_124 - fStack_118 * fVar7;

        pts[n++] = fStack_13c;
        pts[n++] = fStack_138;
        pts[n++] = fStack_134;

        fStack_12c = fStack_12c + fStack_114;
        fStack_128 = fStack_128 + fStack_110;
        fStack_124 = fStack_124 + fStack_10c;
        fStack_130b = (float)((int)fPrev + 1);
    } while ((int)fStack_130b < 0x11);

    ((void(__thiscall*)(void*, int, void*, int))VFN(param_3, 0x44))(param_3, 0xd, pts, 0x33);

    if (fStack_114 != 0.0f) {
        FUN_00f47380((void*)0);
    }
}