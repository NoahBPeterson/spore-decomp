// Slice s00e6b370 -- SPGonzago/SPCellGame.obj (cell stage): the cell's eye-lookat target
// update, the "wants player effect" query, a helper that finds the point on a cell's
// collision model closest to a position, and the electric-ribbon / charging effect updaters.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
#include "types.h"

#pragma intrinsic(sqrt)
extern "C" double __cdecl sqrt(double);

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

// ---------------------------------------------------------------- math
struct Vector3 { float x, y, z; };

// ---------------------------------------------------------------- raw offset accessors
#define I(p,o) (*(int*)((char*)(p) + (o)))
#define U(p,o) (*(uint32*)((char*)(p) + (o)))
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define B(p,o) (*(uint8*)((char*)(p) + (o)))
#define P(p,o) (*(void**)((char*)(p) + (o)))

// ---------------------------------------------------------------- globals
extern char* gspCellGame;             // 0x016b3c04

struct Registry {                     // cSPObjectPool at gspCellGame + 0x1c (thiscall)
    void* GetSafe(int id);            // 0x00b721d0
    void* Get(int id);               // 0x00b72210
};

struct cCellGameFields {              // typed view used so the compiler forms &mCells as an lvalue
    char pad0[0x1c];
    Registry mCells;                  // +0x1c
    char pad1[0x411c - 0x1c - 1];
    int mAvatarCellIndex;             // +0x411c
    char pad2[0x5190 - 0x4120];
    char* mpSerializableData;         // +0x5190
    char pad3[0x51d4 - 0x5198];
    int field_51d4;                   // +0x51d4
};

struct RandomLCG {                    // EA::Random::RandomLinearCongruential at 0x01601760
    uint32 RandomUint32Uniform(uint32 range);   // 0x00a68fb0
};
extern RandomLCG gRandomLCG;          // 0x01601760
extern float gT_016b3c28[3];          // 0x016b3c28 (identity transform translation)
extern float gT_016b3c54[3];          // 0x016b3c54
extern float gR_016b3c60[9];          // 0x016b3c60 (identity 3x3 rotation)
extern float gMatrix_016b3dac;        // 0x016b3dac (matrix source)
extern float gOne;                    // 0x01485720 = 1.0f
extern float gMinPos;                 // 0x014851ec = 1.5258789e-05f
extern float gTwo;                    // 0x01470f1c = 2.0f
extern float gEpsilon;                // 0x013ec4b8 = 1e-08f
extern float gFrac05;                 // 0x013ec478 = 0.05f
extern float gFar;                    // 0x013f0620 = 10000.0f

// ---------------------------------------------------------------- helpers
struct ResourceKey { uint32 instanceID, typeID, groupID; };
int* GetCellResource(ResourceKey key);                       // 0x00e679e0
int  GetScaleDifferenceWithPlayer(void* cell);               // 0x00e57340
int  FUN_00e573e0(void* cell, void* other);                  // 0x00e573e0
float* FUN_00e5fc90(void* out, void* cell, int a, int b);    // 0x00e5fc90
void* FUN_00e4cc40(void* value, void* handle);               // 0x00e823a0 (thunk)

// 0x00e6b180
void* sChooseRandomLookatTarget(void* cell, int a2, int a3, int* out);

// 0x00e68000: resolve the ribbon endpoint from the cell + a transform
void FUN_00e68000(void* cell, int a, void* out);
// 0x00e84150
void FUN_00e84150(void* a, int index, void* transform);
// 0x0041cb40: Matrix33Template<float,0>::Matrix33Template<float,0>(const float*)
void Matrix33_ctor(void* self, const void* src);

// 0x00628450
bool CreateEffectSafe(void* world, uint32 id, int flags, int** ppEffect);

// RAII handle used by FUN_00e6b500 (the temporary at local_4)
struct Handle { int mValue; void ctor(); void dtor(); };

// ---------------------------------------------------------------- effect interface
struct cIVisualEffect {
    virtual int  AddRef();                 // +0x00
    virtual int  Release();                // +0x04
    virtual bool Start(int flags);         // +0x08
    virtual bool Stop(int flags);          // +0x0c
    virtual bool v10();                    // +0x10
    virtual void v14();                    // +0x14
    virtual void SetTransform(const void*); // +0x18
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44(int a, const void* data, int count);   // +0x44
};

struct cSPTransform {
    uint16 mFlags;
    uint16 mModCount;
    float  mTranslation[3];
    float  mScale;
    float  mRotation[9];
};

struct IntVec {
    void* begin;
    void* end;
    void* cap;
    void DoInsertValue(void* where, void** value);   // 0x004558a0
};

// @ 0x00e6b370  SP::sUpdateEyeLookatTarget
void FUN_00e6b370(void* cell)
{
    char* game = gspCellGame;
    if (I(game, 0x51d4) == I(cell, 0)) {
        cCellGameFields* g = (cCellGameFields*)game;
        int avatar = g->mAvatarCellIndex;
        void* target = ((Registry*)(gspCellGame + 0x1c))->GetSafe(avatar);
        if (target != 0) {
            *(Vector3*)((char*)cell + 0x12c) = *(Vector3*)((char*)target + 0x4c);
            return;
        }
        game = gspCellGame;
    }
    if (I(cell, 0x248) != 0 && I(cell, 0xfc) != 0) {
        int iVar2;
        if (I(cell, 0) == I(game, 0x411c))
            iVar2 = 0;
        else
            iVar2 = (GetScaleDifferenceWithPlayer(cell) == 4) ? 2 : 1;

        int iVar4 = I(cell, 0x18c);
        switch (iVar4) {
        case 0:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x30:
            break;
        default:
            iVar4 = -1;
        }

        if (iVar4 != I(cell, 0x118) || iVar2 != I(cell, 0x11c) ||
            I(cell, 0x128) <= I(I(game, 0x5190), 0x74)) {
            I(cell, 0x118) = iVar4;
            I(cell, 0x11c) = iVar2;
            I(cell, 0x120) = (int)sChooseRandomLookatTarget(cell, iVar2, iVar4, (int*)((char*)cell + 0x124));
            int t = I(I(gspCellGame, 0x5190), 0x74);
            uint32 r = gRandomLCG.RandomUint32Uniform(1000);
            I(cell, 0x128) = (int)(r + 500 + t);
        }

        int local[3];
        float* p = FUN_00e5fc90(local, cell, I(cell, 0x120), I(cell, 0x124));
        I(cell, 0x12c) = I(p, 0);
        I(cell, 0x130) = I(p, 4);
        I(cell, 0x134) = I(p, 8);
    }
}

// @ 0x00e6b500  SP::CellWantsPlayerEffect
bool FUN_00e6b500(void* cell)
{
    int avatar = I(gspCellGame, 0x411c);
    if (avatar != 0 && I(cell, 0) != avatar) {
        Registry* reg = (Registry*)(gspCellGame + 0x1c);
        void* c = reg->Get(avatar);
        int* res = GetCellResource(*(ResourceKey*)((char*)c + 0xfc));
        int r = FUN_00e573e0(c, cell);
        if (r == 1 || r == 0) {
            Handle h;
            h.ctor();
            void* a = FUN_00e4cc40((void*)I(cell, 0x108), &h);
            int b4 = I(a, 0xb4);
            if (B(res, 0x1251) != 0 && b4 == 3) {
                h.dtor();
                return true;
            }
            if (B(res, 0x1250) != 0 && b4 == 2) {
                h.dtor();
                return true;
            }
            h.dtor();
        }
    }
    return false;
}

// @ 0x00e6b5d0  closest point on a cell's collision model to a world position
void FUN_00e6b5d0(float* out, const float* pos, void* cell)
{
    float l30 = pos[0] - F(cell, 0x4c);
    float l2c = pos[1] - F(cell, 0x50);
    float l28 = pos[2] - F(cell, 0x54);
    float inv = (float)(1.0 / sqrt((double)(l30 * l30 + (l2c * l2c + l28 * l28)) + (double)gEpsilon));
    float l18 = inv * l30;
    float l34 = F(cell, 0x58);
    float l14 = l2c * inv;
    float l10 = l28 * inv;

    if (I(cell, 0x248) == 0) {
        out[0] = F(cell, 0x4c) + l18 * l34;
        out[1] = F(cell, 0x50) + l14 * l34;
        out[2] = F(cell, 0x54) + l10 * l34;
        return;
    }
    if (I(cell, 0xfc) == 0) {
        out[0] = l18 * l34 + F(cell, 0x4c);
        out[1] = F(cell, 0x50) + l14 * l34;
        out[2] = F(cell, 0x54) + l10 * l34;
        return;
    }

    int* set = GetCellResource(*(ResourceKey*)((char*)cell + 0xfc));
    int* end = set + 5;
    float best = gFar;
    int bestIdx = -1;
    if (set[0] > 0) {
        int idx = 0;
        float* e = (float*)end;
        do {
            if (I(set, 8 + idx * 0x48) == 0xc) {
                float a = F(set, 0x0c + idx * 0x48);
                float b = F(set, 0x10 + idx * 0x48);
                float c = F(set, 0x14 + idx * 0x48);
                float ra = F(set, 0x3c + idx * 0x48);
                if ((B(cell, 0x48) & 2) != 0) {
                    float na = F(cell, 0x74) * c + F(cell, 0x68) * b + F(cell, 0x5c) * a;
                    float nb = F(cell, 0x60) * a + F(cell, 0x78) * c + F(cell, 0x6c) * b;
                    float nc = F(cell, 0x64) * a + F(cell, 0x7c) * c + F(cell, 0x70) * b;
                    a = na; b = nb; c = nc;
                }
                float scale = F(cell, 0x58);
                ra = F(set, 0x3c + idx * 0x48) * scale;
                a = F(cell, 0x4c) + a * scale;
                b = F(cell, 0x50) + b * scale;
                c = F(cell, 0x54) + c * scale;

                float dx = pos[0] - a;
                float dy = pos[1] - b;
                float dz = pos[2] - c;
                float dist = (float)sqrt((double)(dx * dx + (dy * dy + dz * dz)));
                float d = 0.0f;
                float* sel = (float*)&d;
                if (dist - ra > 0.0f)
                    sel = (float*)&pos;      // choose the position itself
                float score = *sel;
                if (score < best) {
                    float invd = (float)(1.0 / sqrt((double)(dx * dx + (dy * dy + dz * dz)) + (double)gEpsilon));
                    bestIdx = idx;
                    best = score;
                    out[0] = invd * dx * ra + a;
                    out[1] = invd * dy * ra + b;
                    out[2] = invd * dz * ra + c;
                }
            }
            idx++;
            e += 0x12;
        } while (idx < set[0]);
        if (bestIdx != -1)
            return;
    }

    out[0] = l18 * l34 + F(cell, 0x4c);
    out[1] = F(cell, 0x50) + l14 * l34;
    out[2] = F(cell, 0x54) + l10 * l34;
}

// @ 0x00e6b9b0  SP::sUpdateElectricRibbonEffect
void sUpdateElectricRibbonEffect(void* world, cIVisualEffect** ppEffect, void* cell, int id, int a5)
{
    cIVisualEffect* fx = (cIVisualEffect*)((Registry*)(gspCellGame + 0x1c))->GetSafe(id);
    if (fx == 0 || B(fx, 0x112) != 0) {
        if (*ppEffect != 0) {
            (*ppEffect)->Stop(1);
            (*ppEffect)->Release();
            *ppEffect = 0;
        }
        return;
    }

    if (*ppEffect == 0) {
        uint32 effID = 0xa1fb7133;
        void* subject = ((Registry*)(gspCellGame + 0x1c))->Get(id);
        if (I(subject, 0xfc) != 0) {
            int* set = GetCellResource(*(ResourceKey*)((char*)subject + 0xfc));
            int n = set[0];
            int i = 0;
            if (n > 0) {
                int* e = set + 2;
                do {
                    if (*e == 6) { effID = 0x7d84966f; break; }
                    i++;
                    e += 0x12;
                } while (i < n);
            }
        }
        CreateEffectSafe(world, effID, 0, (int**)ppEffect);
        if (!(*ppEffect)->v10())
            (*ppEffect)->Start(0);
    }

    (*ppEffect)->SetTransform((char*)cell + 0x48);

    cSPTransform xf;
    xf.mFlags = 0;
    xf.mModCount = 0;
    xf.mTranslation[0] = gT_016b3c28[0];
    xf.mTranslation[1] = gT_016b3c28[1];
    xf.mTranslation[2] = gT_016b3c28[2];
    xf.mScale = gOne;
    Matrix33_ctor(xf.mRotation, &gMatrix_016b3dac);
    FUN_00e68000(fx, a5, &xf);

    float x0 = xf.mTranslation[0], y0 = xf.mTranslation[1], z0 = xf.mTranslation[2];
    float out[3];
    float pos[3];
    pos[0] = x0; pos[1] = y0; pos[2] = z0;
    FUN_00e6b5d0(out, pos, cell);

    float x1 = out[0], y1 = out[1], z1 = out[2];
    float pts[0x15 * 3];
    for (int i = 0; i < 0x15; i++) {
        float t = (float)i * gFrac05;
        pts[i * 3 + 0] = (x1 - x0) * t + x0;
        pts[i * 3 + 1] = (y1 - y0) * t + y0;
        pts[i * 3 + 2] = (z1 - z0) * t + z0;
    }
    (*ppEffect)->v44(0xd, pts, 0x3f);
}

// @ 0x00e6bc10  SP::sUpdateChargingEffect
void sUpdateChargingEffect(void* world, IntVec* vec, uint32* key, void* a4, void* a5, uint8 b, float f)
{
    int alive = 0;
    if (b != 0) {
        int* set = GetCellResource(*(ResourceKey*)key);
        if (set[0] > 0) {
            int i = 0;
            int* e = set + 2;
            do {
                if (*e == 6) {
                    cIVisualEffect* fx = 0;
                    int count = (int)(((char*)vec->end - (char*)vec->begin) >> 2);
                    if (alive < count) {
                        fx = (cIVisualEffect*)((void**)vec->begin)[alive];
                        if (fx != 0)
                            fx->AddRef();
                    } else {
                        uint32 effID = (I(set, 0x121c) > 2) ? 0x5ca636dc : 0x17aab61f;
                        CreateEffectSafe(world, effID, 0, (int**)&fx);
                        fx->Start(1);
                        bool added = false;
                        void** slot = (void**)vec->end;
                        if (slot < (void**)vec->cap) {
                            vec->end = (char*)slot + 4;
                            if (slot != 0) {
                                *slot = fx;
                                fx->AddRef();
                                added = true;
                            }
                        } else {
                            vec->DoInsertValue(vec->end, (void**)&fx);
                        }
                        if (!added)
                            fx->AddRef();
                    }

                    cSPTransform xf;
                    xf.mFlags = 0;
                    xf.mModCount = 0;
                    xf.mTranslation[0] = gT_016b3c54[0];
                    xf.mTranslation[1] = gT_016b3c54[1];
                    xf.mTranslation[2] = gT_016b3c54[2];
                    xf.mScale = gOne;
                    for (int k = 0; k < 9; k++)
                        xf.mRotation[k] = gR_016b3c60[k];
                    FUN_00e84150(a4, i, &xf);
                    float s = f * gTwo;
                    xf.mScale = (s < gMinPos) ? gMinPos : s;
                    xf.mModCount = (uint16)(xf.mModCount + 1);
                    fx->SetTransform(&xf);
                    if (fx != 0)
                        fx->Release();
                    alive++;
                }
                e += 0x12;
                i++;
            } while (i < set[0]);
        }
    }

    int n = (int)(((char*)vec->end - (char*)vec->begin) >> 2);
    while (n - 1 >= alive) {
        n--;
        cIVisualEffect* p = (cIVisualEffect*)((void**)vec->begin)[n];
        p->Stop(1);
        p->Release();
        ((void**)vec->begin)[n] = 0;
        vec->end = (char*)vec->end - 4;
    }
}
