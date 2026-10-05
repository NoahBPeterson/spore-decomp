// SP::cShowTexturesLayer::DrawLayer (caller-scored PDB name; retail layout inferred
// from the disassembly).  This is a 3966-byte /O2 /arch:SSE2 layer-draw routine.
// Not byte-matched: reconstructing the exact FP evaluation order of the four
// make-quad blocks by hand is out of budget.  The control flow, every call and
// every output slot are reproduced below.
#include <math.h>

struct Raster { char pad[0x14]; };

struct EmbeddedState {
    char pad[0x10];
    unsigned char m_hardStateDirty;   // +0x10
    void SetRaster(int index, Raster* r);
    void Dispatch();
};

struct cViewer {
    void Copy(int a, int b, int c);
    void SetView(int* rect, bool b);
    void SetRects(int x, int y, int w, int h);
    bool Check();
    void AddRect(char* p);
    void SetMode(int mode);
    void End();
};

struct DrawList {
    void Init();
    void Add(int index, float a, float b, float c, float d);
};

struct ITextureProvider {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual Raster* GetRaster(int a, int b);                                  // +0x18
    virtual void v7();
    virtual void v8();
    virtual void GetQuad(int a, int b, float* p0, float* p1,
                         float* p2, float* p3);                               // +0x24
};

struct IMaterialMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9();
    virtual void* GetMaterial(int id);                                        // +0x28
};

// callees (relocations; declared only)
int   FUN_0067dda0();
void  FUN_00761dc0();
void* MaterialManager();
void  FUN_0077d170();
void  FUN_0077ca20(DrawList* self, int index, float a, float b, float c, float d);
bool  FUN_006ddcc0(int a, int b, void** out, void* state);
void  FUN_006ddd10(int a, int b);
int   FUN_011f1120();
void  GlobalState_D3D9Sync();

extern int   g_renderState;      // 0x16fa38c
extern int   DAT_016f9218;
extern int   DAT_016f923c;
extern float DAT_016077c4;
extern float DAT_016077c8;
extern float DAT_01485720;       // 1.0f
extern unsigned g_negNaN;        // 0xffffffff

#define OUT(x) out[(x)]

struct cShowTexturesLayer {
    char pad00[0xc];
    unsigned m_materialId;        // +0xc
    int   m_texId0;               // +0x10
    int   m_texId1;               // +0x14
    Raster* m_srcRaster;          // +0x18
    int   m_destX;                // +0x1c
    int   m_destY;                // +0x20
    int   m_vecBegin;             // +0x24
    int   m_vecEnd;               // +0x28
    char  pad2c[0x38 - 0x2c];
    cViewer* m_viewer;            // +0x38
    float m_params[16];           // +0x3c
    char  pad7c[0x82 - 0x7c];
    bool  m_b82;                  // +0x82
    bool  m_b83;                  // +0x83
    unsigned short m_w84;         // +0x84
    unsigned short m_w88;         // +0x88
    unsigned short m_w8c;         // +0x8c
    unsigned short m_w90;         // +0x90
    int   m_quadrant;             // +0x94
    char  m_rect98[0x10];         // +0x98
    bool  m_ba8;                  // +0xa8
    float m_srcQuad[8];           // +0xac
    float m_inset;                // +0xcc
    float m_angle;                // +0xd0
    float m_tx;                   // +0xd4
    float m_ty;                   // +0xd8
    float m_sx;                   // +0xdc
    float m_sy;                   // +0xe0

    void DrawLayer(int a1, int a2, int* a3, int a4);
};

// @ 0x007b3a70
void cShowTexturesLayer::DrawLayer(int a1, int a2, int* a3, int a4)
{
    (void)a1; (void)a2;
    m_viewer->Copy(*a3, 1, 0);

    bool bSimple = (m_b83 == 0 && m_ba8 == 0);
    m_viewer->SetView(&m_destX, bSimple);

    ITextureProvider* p6 = (ITextureProvider*)FUN_0067dda0();

    if (m_b83)
        m_viewer->SetRects(m_w84, m_w88, m_w8c, m_w90);

    if (!m_viewer->Check())
        return;

    FUN_00761dc0();
    if (m_b82) {
        m_viewer->AddRect(m_rect98);
        m_viewer->SetMode(7);
    }

    IMaterialMgr* p7 = (IMaterialMgr*)MaterialManager();
    void* pMat = p7->GetMaterial((int)m_materialId);
    EmbeddedState* pES = *(EmbeddedState**)((char*)pMat + 4);

    Raster*  pRaster = 0;
    float    f144 = 0.0f, f140 = 0.0f, f13c = 0.0f, f138 = 0.0f;
    float    f14c = 0.0f, f148 = 0.0f, f154 = 0.0f;
    float    fVar9, fVar11, fVar12, fVar13;

    // ---- select the source raster and the base quad -------------------------
    {
        bool bCommon = false;
        if (m_srcRaster == 0) {
            pRaster = p6->GetRaster(m_texId0, m_texId1);
            p6->GetQuad(m_texId0, m_texId1, &f144, &f140, &f13c, &f138);
            if (pRaster != 0 && (pES->m_hardStateDirty & 1)) {
                pES->SetRaster(0, pRaster);
                float d0 = 0.0f, d1 = 0.0f;
                char  dummy[264];
                (void)d1; (void)dummy;
                p6->GetQuad(m_texId0, m_texId1, &d0, &f144, &f140, &f13c);
                fVar9  = f140;
                fVar13 = f144;
                bCommon = true;
            }
        } else if (pES->m_hardStateDirty & 1) {
            pES->SetRaster(0, m_srcRaster);
            fVar9  = (float)(unsigned)((unsigned short*)m_srcRaster)[7];
            fVar13 = (float)(unsigned)((unsigned short*)m_srcRaster)[6];
            bCommon = true;
        }
        if (bCommon) {
            f14c = (float)(int)fVar13;
            f148 = (float)(int)fVar9;
            DrawList dl;
            dl.Init();
            dl.Add(0, m_params[0], m_params[1], m_params[2], m_params[3]);
            dl.Add(1, m_params[4], m_params[5], m_params[6], m_params[7]);
            dl.Add(2, f14c, f148, 1.0f / f14c, 1.0f / f148);
            dl.Add(3, m_params[12], m_params[13], m_params[14], m_params[15]);
        }
    }

    // ---- additional rect ids -------------------------------------------------
    if (m_vecBegin != m_vecEnd) {
        int count = (int)((m_vecEnd - m_vecBegin) >> 3);
        if ((unsigned)(count - 1) < 4u) {
            unsigned short i = 0;
            if (count > 0) {
                do {
                    int* e = (int*)(m_vecBegin + i * 8);
                    Raster* r = p6->GetRaster(e[0], e[1]);
                    if (r != 0)
                        pES->SetRaster((int)i + 1, r);
                    i = (unsigned short)(i + 1);
                } while ((unsigned)i < (unsigned)count);
            }
        }
    }

    g_renderState |= 0x10080;
    int save18 = DAT_016f9218;
    int save3c = DAT_016f923c;
    DAT_016f9218 = 0;
    DAT_016f923c = 8;
    pES->Dispatch();
    GlobalState_D3D9Sync();

    int iR = FUN_011f1120();
    unsigned short uVar1 = *(unsigned short*)(*(int*)(iR + 0x40) + 0xc);
    iR = FUN_011f1120();
    unsigned short uVar2 = *(unsigned short*)(*(int*)(iR + 0x40) + 0xe);

    float* out = 0;
    char   st[264];
    if (!FUN_006ddcc0(2, 4, (void**)&out, st))
        goto restore;

    if (m_b83 == 0) {
        f13c = m_angle;
        if (m_angle == 0.0f && m_tx == 0.0f && m_ty == 0.0f &&
            m_sx == DAT_01485720 && m_sy == DAT_01485720) {
            fVar13 = DAT_016077c8 * 2.0f;
            fVar12 = (float)uVar1;
            fVar9  = m_srcQuad[1];
            OUT(0) = (m_srcQuad[0] - 1.0f) - (DAT_016077c4 * 2.0f) / fVar12;
            fVar11 = (float)uVar2;
            OUT(1) = 0.0f;
            OUT(2) = (fVar9 - 1.0f) - fVar13 / fVar11;
            fVar13 = DAT_016077c8;
            fVar9  = m_srcQuad[3];
            OUT(6) = (m_srcQuad[2] + 1.0f) - (DAT_016077c4 * 2.0f) / fVar12;
            OUT(7) = 0.0f;
            OUT(8) = (fVar9 - 1.0f) - (fVar13 * 2.0f) / fVar11;
            fVar9  = m_srcQuad[5];
            fVar13 = DAT_016077c8 * 2.0f;
            OUT(0xc) = ((m_srcQuad[4] + 1.0f) - m_inset) - (DAT_016077c4 * 2.0f) / fVar12;
            OUT(0xd) = 0.0f;
            OUT(0xe) = (fVar9 + 1.0f) - fVar13 / fVar11;
            fVar9    = ((m_srcQuad[6] + m_inset) - 1.0f) - (DAT_016077c4 * 2.0f) / fVar12;
            f154     = (m_srcQuad[7] + 1.0f) - (DAT_016077c8 * 2.0f) / fVar11;
        } else {
            float fsin_v = (float)sin(f13c);
            float a124 = m_srcQuad[2] + 1.0f;
            float a120 = m_srcQuad[3] - 1.0f;
            float a11c = (m_srcQuad[4] + 1.0f) - m_inset;
            float a118 = m_srcQuad[5] + 1.0f;
            f140 = (float)uVar1;
            f148 = 1.0f / f140;
            f14c = (float)uVar2;
            float a114 = (m_srcQuad[6] + m_inset) - 1.0f;
            f144 = 1.0f / f14c;
            fVar12 = m_srcQuad[1] - 1.0f;
            float a12c = m_srcQuad[0] - 1.0f;
            float a110 = m_srcQuad[7] + 1.0f;
            f138 = fsin_v;
            f13c = (float)cos(m_angle);

            fVar9  = m_ty;
            fVar13 = m_sy;
            fVar11 = DAT_016077c8 * 2.0f;
            OUT(0) = ((a12c * f13c - fVar12 * f138) + m_tx * f148) * m_sx
                     - (DAT_016077c4 * 2.0f) / f140;
            OUT(1) = 0.0f;
            OUT(2) = ((fVar12 * f13c + a12c * f138) + fVar9 * f144) * fVar13
                     - fVar11 / f14c;
            fVar9  = m_ty; fVar13 = m_sy; fVar12 = DAT_016077c8 * 2.0f;
            OUT(6) = ((f13c * a124 - f138 * a120) + m_tx * f148) * m_sx
                     - (DAT_016077c4 * 2.0f) / f140;
            OUT(7) = 0.0f;
            OUT(8) = ((f13c * a120 + f138 * a124) + fVar9 * f144) * fVar13
                     - fVar12 / f14c;
            fVar9  = m_ty; fVar13 = m_sy; fVar12 = DAT_016077c8 * 2.0f;
            OUT(0xc) = ((f13c * a11c - f138 * a118) + m_tx * f148) * m_sx
                       - (DAT_016077c4 * 2.0f) / f140;
            OUT(0xd) = 0.0f;
            OUT(0xe) = ((f13c * a118 + f138 * a11c) + fVar9 * f144) * fVar13
                       - fVar12 / f14c;
            fVar9 = ((f13c * a114 - f138 * a110) + m_tx * f148) * m_sx
                    - (DAT_016077c4 * 2.0f) / f140;
            f154  = ((f13c * a110 + f138 * a114) + m_ty * f144) * m_sy
                    - (DAT_016077c8 * 2.0f) / f14c;
        }
        OUT(0x12) = fVar9;
        OUT(0x13) = 0.0f;
        OUT(0x14) = f154;
    } else {
        int q = m_quadrant;
        if (q == 1) {
            fVar9 = DAT_016077c8 * 2.0f;
            OUT(0) = -0.97f - (DAT_016077c4 * 2.0f) / (float)uVar1;
            OUT(1) = 0.0f;
            OUT(2) = 0.0399f - fVar9 / (float)uVar2;
            fVar13 = -0.03f - (DAT_016077c4 * 2.0f) / (float)uVar1;
            f154 = (DAT_016077c8 * 2.0f) / (float)uVar2;
            fVar9 = -0.03f;
            goto lab_3e76;
        } else if (q == 2) {
            fVar12 = DAT_016077c8 * 2.0f;
            fVar9  = (float)uVar1;
            OUT(0) = -0.97f - (DAT_016077c4 * 2.0f) / fVar9;
            fVar13 = (float)uVar2;
            OUT(1) = 0.0f;
            OUT(2) = -0.9202f - fVar12 / fVar13;
            fVar12 = DAT_016077c8 * 2.0f;
            OUT(6) = -0.03f - (DAT_016077c4 * 2.0f) / fVar9;
            OUT(7) = 0.0f;
            OUT(8) = -0.9202f - fVar12 / fVar13;
            fVar9  = (DAT_016077c4 * 2.0f) / fVar9;
            fVar12 = 0.9202f;
            fVar13 = (DAT_016077c8 * 2.0f) / fVar13;
        } else if (q == 3) {
            fVar9 = DAT_016077c8 * 2.0f;
            OUT(0) = -0.97f - (DAT_016077c4 * 2.0f) / (float)uVar1;
            OUT(1) = 0.0f;
            OUT(2) = 0.0399f - fVar9 / (float)uVar2;
            fVar13 = 0.97f - (DAT_016077c4 * 2.0f) / (float)uVar1;
            f154 = (DAT_016077c8 * 2.0f) / (float)uVar2;
            fVar9 = 0.97f;
            goto lab_3e76;
        } else if (q == 4) {
            fVar12 = DAT_016077c8 * 2.0f;
            fVar9  = (float)uVar1;
            OUT(0) = -0.97f - (DAT_016077c4 * 2.0f) / fVar9;
            fVar13 = (float)uVar2;
            OUT(1) = 0.0f;
            OUT(2) = 0.0399f - fVar12 / fVar13;
            fVar12 = DAT_016077c8 * 2.0f;
            OUT(6) = -0.03f - (DAT_016077c4 * 2.0f) / fVar9;
            OUT(7) = 0.0f;
            OUT(8) = 0.0399f - fVar12 / fVar13;
            fVar9  = (DAT_016077c4 * 2.0f) / fVar9;
            fVar12 = 0.9601f;
            fVar13 = (DAT_016077c8 * 2.0f) / fVar13;
        } else {
            goto lab_4104;
        }
        OUT(0xc) = -0.03f - fVar9;
        OUT(0xd) = 0.0f;
        OUT(0xe) = fVar12 - fVar13;
        fVar9 = DAT_016077c8 * 2.0f;
        OUT(0x12) = -0.97f - (DAT_016077c4 * 2.0f) / (float)uVar1;
        OUT(0x13) = 0.0f;
        OUT(0x14) = fVar12 - fVar9 / (float)uVar2;
        goto lab_4104;
    lab_3e76:
        f154 = 0.0399f - f154;
        OUT(6) = fVar13;
        OUT(7) = 0.0f;
        OUT(8) = f154;
        fVar13 = DAT_016077c8;
        OUT(0xc) = fVar9 - (DAT_016077c4 * 2.0f) / (float)uVar1;
        OUT(0xd) = 0.0f;
        OUT(0xe) = 0.9601f - (fVar13 * 2.0f) / (float)uVar2;
        fVar9 = DAT_016077c8 * 2.0f;
        OUT(0x12) = -0.97f - (DAT_016077c4 * 2.0f) / (float)uVar1;
        OUT(0x13) = 0.0f;
        OUT(0x14) = 0.9601f - fVar9 / (float)uVar2;
    }

lab_4104:
    OUT(3)  = *(float*)&g_negNaN;
    OUT(4)  = 0.0f;
    OUT(5)  = 1.0f;
    OUT(9)  = *(float*)&g_negNaN;
    OUT(10) = 1.0f;
    OUT(11) = 1.0f;
    OUT(15) = *(float*)&g_negNaN;
    OUT(16) = 1.0f;
    OUT(17) = 0.0f;
    OUT(21) = *(float*)&g_negNaN;
    OUT(22) = 0.0f;
    OUT(23) = 0.0f;
    FUN_006ddd10(3, a4);

restore:
    g_renderState |= 0x10080;
    DAT_016f9218 = save18;
    DAT_016f923c = save3c;
    m_viewer->End();
}
