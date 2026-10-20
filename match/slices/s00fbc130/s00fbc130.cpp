// Slice s00fbc130 — SP::cTerrainStateMgr definition / lighting helpers (retail layout).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

#pragma warning(disable: 4035)
// EA math helper: (int)floorf, hand-written SSE in the original.
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}
#pragma warning(default: 4035)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

struct Key { uint32_t instance, type, group; };

// ---- callees ---------------------------------------------------------------
struct cPropertyList;
bool __cdecl GetPropertyAsKey(cPropertyList* list, uint32_t id, Key* out);   // 0x6a1250
void __cdecl TextureManager(Key* out, Key key);                              // 0xfba2f0
void __cdecl RGBToHSL(Vector3 rgb, float* p0, float* p1, float* p2);         // 0x67ff30
void __cdecl HSLToRGB(Vector3 hsl, Vector3* out);                            // 0x67fe30

struct IGameMode;
struct IApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual IGameMode* GetActiveMode();          // +0x38
};
namespace SP { IApp* __cdecl App(); }            // 0x67dd10
extern char g_GameModeEditor;                    // 0x1654c10

void __cdecl operator_delete(void* p);           // 0xf47380
struct Sub13c { void Cleanup(); };               // 0xfb9f40 (__thiscall, self = +0x13c)

// Objects reached through +0x204/+0x208/+0x20c/+0x210/+0x1ec are intrusive
// reference-counted: slot 1 (+4) releases.
struct IRefObject {
    virtual void v00();
    virtual void Release();
    virtual void v08();
    virtual void v0c();
};

struct IEffect {
    virtual void v00();                                          // +0x00
    virtual void Release();                                      // +0x04
    virtual bool Activate(unsigned int key, int arg, IEffect** out); // +0x08
    virtual void SetActive(int on);                              // +0x0c
};
struct IEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual IEffect* GetEffect(uint32_t id);   // +0x54
};
namespace SP { IEffectsManager* __cdecl EffectsManager(); }   // 0x67ddd0

int __cdecl GetTerraformPlanetType(float t);     // 0xfc1fd0

// The object returned by *(this + 0x20c): an image with dimensions and a pixel buffer.
struct CloudImage {
    uint32_t pad00[7];
    int mnWidth;                  // +0x1c
    int mnHeight;                 // +0x20
    uint32_t pad24;
    uint8_t* mpData;              // +0x28
};

extern int gLightCountA;          // 0x15b15c8
extern float gLightBlend;         // 0x15b15c4
extern int gLightCountB;          // 0x15b15cc

// ---- cTerrainStateMgr (retail offsets) -------------------------------------
struct cTerrainStateMgr {
    void* mpTerrainSphere;        // +0x000
    char pad004[0x2c - 4];
    float m02c;                   // +0x02c
    float m030;                   // +0x030
    char pad034[0x80 - 0x34];
    uint32_t m080;                // +0x080
    char pad084[0x120 - 0x84];
    void* m120;                   // +0x120 (eastl vector buffer)
    char pad124[0x13c - 0x124];
    char m13c[8];                 // +0x13c (sub-object with an out-of-line cleanup)
    char pad144[0x1ec - 0x144];
    void* m1ec;                   // +0x1ec (float bit pattern / vector buffer)
    float m1f0;                   // +0x1f0
    char pad1f4[0x200 - 0x1f4];
    float m200;                   // +0x200
    void* m204;                   // +0x204
    void* m208;                   // +0x208
    CloudImage* mpImageMain;      // +0x20c
    CloudImage* mpImageA;         // +0x210
    CloudImage* mpImageB;         // +0x214
    CloudImage* mpImageC;         // +0x218
    float m21c[18];               // +0x21c .. +0x263 (twelve float tables, +4 stride apart)
    bool m264;                    // +0x264
    char pad265[0x28c - 0x265];
    float m28c;                   // +0x28c
    float m290;                   // +0x290
    float m294;                   // +0x294
    char pad298[0x2a4 - 0x298];
    void* m2a4;                   // +0x2a4 (eastl vector buffer)
    char pad2a8[0x300 - 0x2a8];
    char mKeys[0x34];             // +0x300 (four Key values at 0x300 / 0x304 / 0x31c / 0x320)
    char pad334[0x348 - 0x334];
    void* m348;                   // +0x348
    char pad34c[0x3cc - 0x34c];
    float mLightColor[3][4];      // +0x3cc
    float mLightScale[3][4];      // +0x3fc
    char pad42c[0x4f8 - 0x42c];
    float m4f8;                   // +0x4f8
    char pad4fc[0x5fc - 0x4fc];
    IEffect* m5fc;                // +0x5fc
    char pad600[0x620 - 0x600];
    float m620;                   // +0x620

    void UpdateFromDefinition(cPropertyList* def);
    void ComputeLightColors(float* out, bool flag);
    void UpdateLightColors(float t, bool flag);
    void SetTemperature(float temp);
    void DestroySubObjects();
};

// @ 0x00fbc130
void cTerrainStateMgr::UpdateFromDefinition(cPropertyList* def)
{
    if (!def)
        return;

    Key key = { 0, 0, 0 };
    if (GetPropertyAsKey(def, 0x3b4f7c6, &key))
        TextureManager((Key*)(mKeys + 0x20), key);
    if (GetPropertyAsKey(def, 0x3b4f7c9, &key))
        TextureManager((Key*)(mKeys + 0x00), key);
    if (GetPropertyAsKey(def, 0x3b4f7cb, &key))
        TextureManager((Key*)(mKeys + 0x04), key);
    if (GetPropertyAsKey(def, 0x3b4f7cc, &key))
        TextureManager((Key*)(mKeys + 0x1c), key);

    Key key2 = { 0, 0, 0 };
    if (GetPropertyAsKey(def, 0x3b5ec4a, &key2))
        m080 = key2.instance;
}

// @ 0x00fbc290
void cTerrainStateMgr::ComputeLightColors(float* out, bool flag)
{
    float v = (float)((double)(gLightCountA - 1) * (double)gLightBlend);
    int blend = (int)v;
    float frac = v - (float)(unsigned)blend;
    CloudImage* img = mpImageMain;

    int w = img->mnWidth;
    int h1 = img->mnHeight - 1;
    float fh1 = (float)h1;
    if (h1 < 0)
        fh1 = fh1 + 4294967296.0f;
    int col = FloorToInt((1.0f - gLightBlend) * fh1);

    int w1 = w - 1;
    float fw1 = (float)w1;
    if (w1 < 0)
        fw1 = fw1 + 4294967296.0f;
    int row = FloorToInt(fw1 * m030);

    if (!m264) {
        if (SP::App()->GetActiveMode() != (IGameMode*)&g_GameModeEditor || flag) {
            uint8_t* data = img->mpData + (col * w + row) * 4;
            out[2] = (float)data[0] * 0.003921569f;
            out[1] = (float)data[1] * 0.003921569f;
            out[0] = (float)data[2] * 0.003921569f;
            goto done;
        }
    }
    {
        float R = m28c;
        float G = m290;
        float B = m294;
        float invA = 1.0f - gLightBlend;
        float h, s, l;
        RGBToHSL(Vector3(R, G, B), &h, &s, &l);
        Vector3 rgb;
        HSLToRGB(Vector3(h, s * 0.5f, l), &rgb);
        out[0] = (rgb.x - R) * invA + R;
        out[1] = (rgb.y - G) * invA + G;
        out[2] = (rgb.z - B) * invA + B;
    }
done:
    out[3] = 1.0f;

    uint8_t* dataA = mpImageA->mpData;
    int idx = (col * w + row) * 4;
    out[6] = (float)dataA[idx + 0] * 0.003921569f;
    out[5] = (float)dataA[idx + 1] * 0.003921569f;
    out[4] = (float)dataA[idx + 2] * 0.003921569f;
    out[7] = 1.0f;

    uint8_t* dataB = mpImageB->mpData;
    out[10] = (float)dataB[idx + 0] * 0.003921569f;
    out[9] = (float)dataB[idx + 1] * 0.003921569f;
    out[11] = 1.0f;
    out[8] = (float)dataB[idx + 2] * 0.003921569f;

    uint8_t* dataC = mpImageC->mpData;
    int idxC = ((int)(fh1 * gLightBlend) * w + (int)(fw1 * m02c)) * 4;
    float scale = (float)dataC[idxC + 0] * 0.003921569f;

    int i = blend;
    float s0 = (m200 * scale) * ((m21c[i + 4] - m21c[i + 3]) * frac + m21c[i + 3]);
    out[0] = out[0] * s0;
    out[1] = s0 * out[1];
    out[3] = (m21c[i + 1] - m21c[i + 0]) * frac + m21c[i + 0];
    out[2] = s0 * out[2];

    float s1 = (*(float*)&m204 * scale) * ((m21c[i + 10] - m21c[i + 9]) * frac + m21c[i + 9]);
    out[4] = out[4] * s1;
    out[5] = out[5] * s1;
    out[6] = out[6] * s1;
    out[7] = (m21c[i + 7] - m21c[i + 6]) * frac + m21c[i + 6];

    float s2 = (*(float*)&m208 * scale) * ((m21c[i + 16] - m21c[i + 15]) * frac + m21c[i + 15]);
    out[8] = out[8] * s2;
    out[9] = out[9] * s2;
    out[10] = out[10] * s2;
    out[11] = (m21c[i + 13] - m21c[i + 12]) * frac + m21c[i + 12];
}

// @ 0x00fbc770
void cTerrainStateMgr::UpdateLightColors(float t, bool flag)
{
    float v = (float)((double)(gLightCountB - 1) * (double)t);
    int blend = (int)v;
    float frac = v - (float)(unsigned)blend;
    CloudImage* img = mpImageMain;

    int w = img->mnWidth;
    int h1 = img->mnHeight - 1;
    float fh1 = (float)h1;
    if (h1 < 0)
        fh1 = fh1 + 4294967296.0f;
    float invT = 1.0f - t;
    int col = FloorToInt(invT * fh1);

    int w1 = w - 1;
    float fw1 = (float)w1;
    if (w1 < 0)
        fw1 = fw1 + 4294967296.0f;
    int row = FloorToInt(fw1 * m030);

    float rgb0;
    if (!m264) {
        if (SP::App()->GetActiveMode() != (IGameMode*)&g_GameModeEditor || flag) {
            uint8_t* data = img->mpData + (col * w + row) * 4;
            mLightColor[0][2] = (float)data[0] * 0.003921569f;
            mLightColor[0][1] = (float)data[1] * 0.003921569f;
            rgb0 = (float)data[2] * 0.003921569f;
            goto done;
        }
    }
    {
        float R = m28c;
        float G = m290;
        float B = m294;
        float h, s, l;
        RGBToHSL(Vector3(R, G, B), &h, &s, &l);
        Vector3 rgb;
        HSLToRGB(Vector3(h, s * 0.5f, l), &rgb);
        mLightColor[0][1] = (rgb.y - G) * invT + G;
        mLightColor[0][2] = (rgb.z - B) * invT + B;
        rgb0 = (rgb.x - R) * invT + R;
    }
done:
    mLightColor[0][0] = rgb0;
    mLightColor[0][3] = 1.0f;

    uint8_t* dataA = mpImageA->mpData;
    int idx = (col * w + row) * 4;
    mLightColor[1][2] = (float)dataA[idx + 0] * 0.003921569f;
    mLightColor[1][1] = (float)dataA[idx + 1] * 0.003921569f;
    mLightColor[1][0] = (float)dataA[idx + 2] * 0.003921569f;
    mLightColor[1][3] = 1.0f;

    uint8_t* dataB = mpImageB->mpData;
    mLightColor[2][2] = (float)dataB[idx + 0] * 0.003921569f;
    mLightColor[2][1] = (float)dataB[idx + 1] * 0.003921569f;
    mLightColor[2][0] = (float)dataB[idx + 2] * 0.003921569f;
    mLightColor[2][3] = 1.0f;

    uint8_t* dataC = mpImageC->mpData;
    int idxC = ((int)(fh1 * t) * w + (int)(fw1 * m02c)) * 4;
    float scale = (float)dataC[idxC + 0] * 0.003921569f;

    int i = blend;
    mLightScale[0][0] = (m21c[i + 1] - m21c[i + 0]) * frac + m21c[i + 0];
    mLightScale[1][0] = (m21c[i + 7] - m21c[i + 6]) * frac + m21c[i + 6];
    mLightScale[2][0] = (m21c[i + 13] - m21c[i + 12]) * frac + m21c[i + 12];
    mLightScale[0][2] = (m21c[i + 4] - m21c[i + 3]) * frac + m21c[i + 3];
    mLightScale[1][2] = (m21c[i + 10] - m21c[i + 9]) * frac + m21c[i + 9];
    mLightScale[2][2] = (m21c[i + 16] - m21c[i + 15]) * frac + m21c[i + 15];
    mLightScale[0][1] = m200 * scale;
    mLightScale[1][1] = *(float*)&m204 * scale;
    mLightScale[2][1] = *(float*)&m208 * scale;
    mLightScale[0][3] = 1.0f - m02c;
    m4f8 = scale;
}

// @ 0x00fbcc20
void cTerrainStateMgr::SetTemperature(float temp)
{
    float v = m620 + temp;
    float old = m030;
    if (fabsf(old - v) < 0.001f)
        return;

    int oldType = GetTerraformPlanetType(old);
    m030 = v;
    if (v > 0.75f)
        *(float*)((char*)m348 + 0x1c) = m1f0;
    else
        *(float*)((char*)m348 + 0x1c) = *(float*)&m1ec;

    int newType = GetTerraformPlanetType(v);
    int arg = 0;
    if (newType == oldType)
        goto tail;

    {
        unsigned int key;
        if ((newType & 2) && (oldType & 2)) {
            key = 0x9c1ed904u;
            if (!(newType & 1))
                key = 0xf3439d25u;
        } else if ((newType & 4) && (oldType & 4)) {
            key = 0xfaa5e99du;
            if (!(newType & 1))
                key = 0x71909b82u;
        } else {
            goto tail;
        }

        if (m5fc) {
            m5fc->SetActive(0);
            if (m5fc) {
                IEffect* p = m5fc;
                m5fc = 0;
                p->Release();
            }
        }
        IEffect* e = SP::EffectsManager()->GetEffect(0x3fbae24);
        if (m5fc) {
            IEffect* p = m5fc;
            m5fc = 0;
            p->Release();
        }
        if (e->Activate(key, arg, &m5fc))
            ((void(__thiscall*)(IEffect*, int))((void**)*(void**)m5fc)[2])(m5fc, 0);
    }
tail:
    ((void(__thiscall*)(void*, int))(*(void***)mpTerrainSphere)[0x48 / 4])(mpTerrainSphere, 2);
}

// @ 0x00fbcd80
void cTerrainStateMgr::DestroySubObjects()
{
    if (m2a4 && ((int*)m2a4)[-1])
        operator_delete(m2a4);
    void* p290 = *(void**)&m290;
    if (p290 && ((int*)p290)[-1])
        operator_delete(p290);
    {
        IRefObject* p = (IRefObject*)mpImageA;
        if (p) p->Release();
    }
    {
        IRefObject* p = (IRefObject*)mpImageMain;
        if (p) p->Release();
    }
    {
        IRefObject* p = (IRefObject*)m208;
        if (p) p->Release();
    }
    {
        IRefObject* p = (IRefObject*)m204;
        if (p) p->Release();
    }
    {
        IRefObject* p = (IRefObject*)m1ec;
        if (p) p->Release();
    }
    ((Sub13c*)m13c)->Cleanup();
    if (m120 && ((int*)m120)[-1])
        operator_delete(m120);
}
