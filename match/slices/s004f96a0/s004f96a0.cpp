// Slice s004f96a0: builds the force-field grid over the box between mV20 and mV2c.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /Oy (16-byte-aligned frame).
// The /Od slot layout of this ~100-local function is not reproduced, so this is not byte-exact;
// the behaviour (every call and path) is reconstructed from the annotated disassembly/Ghidra dump.
#include "types.h"

struct Vector3 { float x, y, z; };

struct SphereFields {
    float mX[4];
    float mY[4];
    float mZ[4];
    float mRadiusSq[4];
    float mInvRadiusSq[4];
    float mStrength[4];
    float mScaledStrength[4];
    uint32_t mId[4];
    void Clear(int index);                                    // 0x004f81a0
    void Copy(int index, const SphereFields* other, int otherIndex);  // 0x004f8370
};

// Passed to the overlap query (0x004fa5a0): three 4-wide component planes (grid spacing),
// the sample point and the source field array (base/count at +0x3c/+0x40).
struct FieldQuery {
    float mX[4];            // +0x00
    float mY[4];            // +0x10
    float mZ[4];            // +0x20
    Vector3 mPoint;         // +0x30
    const void* mpFields;   // +0x3c
    int mCount;             // +0x40
};

// vector math helpers (defined elsewhere)
Vector3* FUN_00453880(Vector3* out, const Vector3* v, const float* s);   // 0x00453880
Vector3* FUN_0041dca0(Vector3* out, const Vector3* v, const float* s);   // 0x0041dca0 (v * *s)
Vector3* FUN_0041db10(Vector3* out, const Vector3* a, const Vector3* b); // 0x0041db10
Vector3* FUN_0041dc10(Vector3* out, const Vector3* a, const Vector3* b); // 0x0041dc10
Vector3* FUN_0041de40(Vector3* out, const float* s, const Vector3* v);   // 0x0041de40 (*s * v)
void     FUN_0041ddb0(Vector3* a, const Vector3* b);                     // 0x0041ddb0 (a += b)
Vector3* FUN_004fa470(Vector3* out, const Vector3* v, Vector3* iout);    // 0x004fa470 (fract/floor)
Vector3* FUN_004fc510(Vector3* out, const Vector3* v, const Vector3* scale); // 0x004fc510
void*    FUN_004f8880(int size, int count);                              // 0x004f8880
uint32_t FUN_004fa5a0(const void* query, int* out, float thresh);        // 0x004fa5a0
void     FUN_004aa350(void* p, void* out);                               // 0x004aa350
void     FUN_004fc960(void* out, void* base, int* zero);                 // 0x004fc960
void     FUN_00425990(void* p);                                          // 0x00425990
extern "C" double ceil(double);

struct ForceGrid {
    char pad00[0x0c];
    float mField0c;         // +0x0c
    int mField10;           // +0x10
    int mField14;           // +0x14  source field count
    int mField18;           // +0x18
    int mField1c;           // +0x1c  source field array base
    Vector3 mV20;           // +0x20
    Vector3 mV2c;           // +0x2c
    Vector3 mV38;           // +0x38
    char pad44[0x08];
    Vector3* mField4c;      // +0x4c
    Vector3* mField50;      // +0x50
    void** mppTable54;      // +0x54
    void Reset();           // 0x004f89a0
    bool Build(float radius);
};

// @ 0x004f96a0
bool ForceGrid::Build(float radius)
{
    if (radius <= 0.0f)
        return false;
    if (mV2c.x <= mV20.x && mV20.x != mV2c.x)
        return false;

    Vector3 t20;
    Vector3* p24 = FUN_00453880(&t20, &mV20, &radius);
    Vector3 t30 = *p24;
    Vector3 t3c, t48;
    FUN_004fa470(&t48, &t30, &t3c);
    Vector3 t54;
    Vector3* p58 = FUN_0041dca0(&t54, &t3c, &radius);
    mV20 = *p58;
    Vector3 t6c = mV20;

    Vector3 t78;
    Vector3* p7c = FUN_0041db10(&t78, &mV2c, &mV20);
    Vector3 t88 = *p7c;
    Vector3 t94;
    Vector3* p98 = FUN_00453880(&t94, &t88, &radius);
    Vector3 ta4 = *p98;
    Vector3 tb0, tbc;
    Vector3* pbc = FUN_004fa470(&tbc, &ta4, &tb0);

    Vector3 ceils;
    ceils.x = (float)ceil(pbc->x);
    ceils.y = (float)ceil(pbc->y);
    ceils.z = (float)ceil(pbc->z);
    FUN_0041ddb0(&tb0, &ceils);

    if (tb0.x < 1.0f || 256.0f <= tb0.x ||
        tb0.y < 1.0f || 256.0f <= tb0.y ||
        tb0.z < 1.0f || 256.0f <= tb0.z)
        return false;

    Vector3 t104;
    Vector3* p108 = FUN_0041de40(&t104, &radius, &tb0);
    mV38 = *p108;
    Vector3 t118;
    Vector3* p11c = FUN_0041dc10(&t118, &t6c, &mV38);
    Vector3 t128 = *p11c;
    Vector3 t134;
    Vector3* p138 = FUN_0041db10(&t134, &t128, &t6c);
    Vector3 t144 = *p138;
    float c0001 = 0.0001f;
    Vector3 t154;
    Vector3* p158 = FUN_0041de40(&t154, &c0001, &t144);
    Vector3 t164 = *p158;
    Vector3 t170;
    Vector3* p174 = FUN_0041db10(&t170, &t6c, &t164);
    *mField50 = *p174;

    float c2 = 2.0f;
    Vector3 t188;
    Vector3* pu = FUN_0041de40(&t188, &c2, &t164);
    Vector3 t194;
    Vector3* p198 = FUN_0041dc10(&t194, &t144, pu);
    Vector3 t1a4 = *p198;

    mField4c->x = 8.0f / t1a4.x;
    mField4c->y = 8.0f / t1a4.y;
    mField4c->z = 8.0f / t1a4.z;
    *(int*)((char*)mField4c + 0x0c) = 0;

    if (mField14 == 0)
        return true;

    Reset();                                             // 0x004f89a0
    int base = mField14 + 4;
    char b1c1;
    FUN_004aa350((void*)base, &b1c1);
    int zero = 0;
    int* p1d8 = 0;
    FUN_004fc960(&p1d8, (void*)base, &zero);
    int end = (int)p1d8 + base * 4;

    float scale8v = 0.125f;
    Vector3 scale8;
    scale8.x = scale8v;
    scale8.y = scale8v;
    scale8.z = scale8v;
    Vector3 t1f8;
    Vector3* p1fc = FUN_004fc510(&t1f8, &t1a4, &scale8);
    Vector3 q = *p1fc;

    int n20c = mField14;
    int n234 = mField1c;
    void** table = mppTable54;
    float s270 = t1a4.x * 0.0625f + 0.0001f;
    float s260 = t1a4.y * 0.0625f + 0.0001f;
    float s250 = t1a4.z * 0.0625f + 0.0001f;
    uint32_t n230 = (uint32_t)(n20c + 3) & 0xfffffffcu;
    float f274 = mField0c;
    float half = 0.5f;

    FieldQuery query;
    for (int i = 0; i < 4; ++i) {
        query.mX[i] = s270;
        query.mY[i] = s260;
        query.mZ[i] = s250;
    }
    query.mpFields = (const void*)n234;
    query.mCount = (int)n230;

    Vector3 qhalf;
    Vector3* pqh = FUN_0041dca0(&qhalf, &q, &half);
    Vector3 qbase;
    Vector3* pqb = FUN_0041dc10(&qbase, pqh, &t6c);
    float bx = pqb->x;
    float by = pqb->y;
    float bz = pqb->z;

    int idx = 0;
    for (int a = 0; a < 8; ++a) {
        float px = (float)a * q.x + bx;
        for (int b = 0; b < 8; ++b) {
            float py = (float)b * q.y + by;
            for (float c = 0.0f; c < 8.0f; c += 1.0f) {
                float pz = q.z * c + bz;
                query.mPoint.x = px;
                query.mPoint.y = py;
                query.mPoint.z = pz;

                uint32_t cnt = FUN_004fa5a0(&query, p1d8, f274);
                if (cnt == 0) {
                    table[idx] = 0;
                } else {
                    int nelem = ((int)(cnt + 3)) >> 2;
                    SphereFields* arr = (SphereFields*)FUN_004f8880(nelem << 7, nelem);
                    table[idx] = arr;
                    uint32_t rem = cnt & 3;
                    if (rem == 1) {
                        arr[nelem - 1].Clear(1);
                        arr[nelem - 1].Clear(2);
                        arr[nelem - 1].Clear(3);
                    } else if (rem == 2) {
                        arr[nelem - 1].Clear(2);
                        arr[nelem - 1].Clear(3);
                    } else if (rem == 3) {
                        arr[nelem - 1].Clear(3);
                    }
                    do {
                        --cnt;
                        uint32_t w = ((uint32_t*)p1d8)[cnt];
                        const SphereFields* src =
                            (const SphereFields*)((const char*)mField1c + (int)(w >> 2) * 0x80);
                        arr[cnt >> 2].Copy((int)(cnt & 3), src, (int)(w & 3));
                    } while (cnt != 0);
                }
                ++idx;
            }
        }
    }

    for (int p = (int)p1d8; p < end; p += 4) {
    }
    FUN_00425990(&p1d8);
    return true;
}
