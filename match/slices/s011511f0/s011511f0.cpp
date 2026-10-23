// Slice s011511f0 — 6 functions of the RenderWare4-core particle ribbon emitter at object base
// 0x115xxxx (011511f0 01151570 01151720 01151a40 01151c30 01151e10).  This region was built with
// /GL + /LTCG (see symbols/renderware4_core.txt), so callers cannot reproduce the original
// cross-call register allocation from a per-file compile; policy here is equivalence-only.
// Field offsets and class/field names are Claude-coined from the disassembly.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /vc71
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

namespace EA { namespace Swarm {

struct cVertexBuffer {
    u32    mField00;   // +0x00
    float* mpData;     // +0x04
    u32    mField08;   // +0x08
    u32    mField0c;   // +0x0c
    u16    mStride;    // +0x0e  (in floats)
};

struct cAngleRow { float x, y, z, w; };

// A 0x14-byte per-segment record starting at object+0xd4.
struct cRibbonSegment {
    float mPrev;   // +0x00 (object +0xd4)
    float mCur;    // +0x04 (object +0xd8)
    float mPad;    // +0x08 (object +0xdc)
    float mDir0;   // +0x0c (object +0xe0)
    float mDir1;   // +0x10 (object +0xe4)
};

// RenderWare-core emit helpers defined in other translation units.
void __stdcall Emit34260(float* pSrc, float* pDst, float fVal, u32 n);
void __stdcall Emit342c0(float* pSrc, float* pDst, float fVal, u32 n);
void __stdcall Emit60300(float* pSrc, float* pDst, float fA, float fB, u32 n);
void __stdcall Emit600e0(float* pSrc, float* pDst, float fA, float fB, u32 n);

class cRibbonEmitter {
public:
    // -- helpers implemented elsewhere (RenderWare core) --
    void SegmentBase(int i);
    void SegmentBaseXY();

    void AddSegmentOffset(int nIndex);
    void BuildSegments();
    void BuildVertexBuffers(cVertexBuffer* pSrc, cVertexBuffer* pDst, float* pSaved, float fScale);
    void EmitSegments(cVertexBuffer* pSrc, cVertexBuffer* pDst);
    int  Update(char* pStream, u8 bRebuild);
    void ComputeCurve();

    // ---- layout (offsets read off the disassembly) ------------------------------------------
    u8     pad000[0x20];
    u8     mField20;      // +0x20
    u8     mField21;      // +0x21
    u8     pad022[0x28 - 0x22];
    float  mField28;      // +0x28
    u8     pad02c[0x30 - 0x2c];
    float  mField30;      // +0x30
    u8     pad034[0x38 - 0x34];
    float  mField38;      // +0x38
    u8     pad03c[0x40 - 0x3c];
    float  mField40;      // +0x40
    u8     pad044[0x48 - 0x44];
    float  mField48;      // +0x48
    u8     pad04c[0x50 - 0x4c];
    float  mField50;      // +0x50
    u8     pad054[0x58 - 0x54];
    float  mField58;      // +0x58
    u8     pad05c[0x60 - 0x5c];
    float  mField60;      // +0x60
    float  mField64;      // +0x64
    float  mField68;      // +0x68
    float  mField6c;      // +0x6c
    float  mField70;      // +0x70
    float  mField74;      // +0x74
    float  mField78;      // +0x78
    float  mField7c;      // +0x7c
    float  mField80;      // +0x80
    float  mField84;      // +0x84
    float  mField88;      // +0x88
    float  mField8c;      // +0x8c
    float  mField90;      // +0x90
    float  mField94;      // +0x94
    float  mField98;      // +0x98
    float  mField9c;      // +0x9c
    float  mFielda0;      // +0xa0
    float  mFielda4;      // +0xa4
    float  mFielda8;      // +0xa8
    float  mFieldac;      // +0xac
    float  mFieldb0;      // +0xb0
    float  mFieldb4;      // +0xb4
    float  mFieldb8;      // +0xb8
    float  mFieldbc;      // +0xbc
    float  mFieldc0;      // +0xc0
    float  mFieldc4;      // +0xc4
    float  mFieldc8;      // +0xc8
    int    mCount1;       // +0xcc  (ComputeCurve stores a float into it; loops read it as int)
    int    mCount0;       // +0xd0
    u8     pad0d4[0x138 - 0xd4];
    float  mField138;     // +0x138
    u8     pad13c[0x164 - 0x13c];
    cAngleRow mAngleTable[8];   // +0x164, stride 0x10
};

// ---- per-frame ribbon growth (887 bytes) ----------------------------------------------------
// @ 0x11511f0
void cRibbonEmitter::AddSegmentOffset(int nIndex)
{
    float fBase = mField7c;
    float fTab  = mAngleTable[nIndex].w;
    float fDiv  = mAngleTable[nIndex].z;

    float  fScaled = (fTab + fBase) * 0.15915494f;
    double dFloor  = floor(fScaled);
    double dAng    = (fScaled - dFloor) * 6.2831855f - fBase;
    float  fAng    = (float)dAng;
    float  fSin    = (float)sin(dAng);
    float  fCos    = (float)cos(dAng);

    if (fAng < fBase) {
        float a = mField90 * fCos + mField8c * fSin;
        float b = mField98 * fCos + mField94 * fSin;
        float c = 0.0f;
        if (mCount0 == 5) {
            c = (a < b) ? a : b;
            c = mField48 * c;
            a = a - c;
            b = b - c;
            c = mField88 * c;
        }
        float* pfA = (float*)this + (nIndex * 5 + 0x37);
        float  sc  = fDiv / sqrt(a * a + (b * b + c * c));
        *pfA = sc * a + *pfA;
        char* p = (char*)this + nIndex * 0x14;
        *(float*)(p + 0xd4) = b * sc + *(float*)(p + 0xd4);
        *(float*)(p + 0xd8) = sc * c + *(float*)(p + 0xd8);
        return;
    }
    if (mField80 <= fAng) {
        if (6.2831855f - mField80 <= fAng) {
            float a = mFielda0 * fCos + mField9c * fSin;
            float b = mFielda8 * fCos + mFielda4 * fSin;
            float* pfA = (float*)((char*)this + 0xe4 + nIndex * 0x14);
            float  sc  = fDiv / sqrt(a * a + b * b);
            *pfA = a * sc + *pfA;
            pfA = (float*)this + (nIndex * 5 + 0x37);
            *pfA = b * sc + *pfA;
            return;
        }
        float a = mFieldb0 * fCos + mFieldac * fSin;
        float b = mFieldb8 * fCos + mFieldb4 * fSin;
        char* p  = (char*)this + nIndex * 0x14;
        float sc = fDiv / sqrt(a * a + b * b);
        *(float*)(p + 0xe0) = a * sc + *(float*)(p + 0xe0);
        *(float*)(p + 0xe4) = b * sc + *(float*)(p + 0xe4);
        return;
    }
    float a = mFieldc0 * fCos + mFieldbc * fSin;
    float b = mFieldc8 * fCos + mFieldc4 * fSin;
    char* p  = (char*)this + nIndex * 0x14;
    float sc = fDiv / sqrt(a * a + b * b);
    *(float*)(p + 0xd4) = a * sc + *(float*)(p + 0xd4);
    *(float*)(p + 0xe0) = b * sc + *(float*)(p + 0xe0);
}

// ---- recompute segment normals (430 bytes) --------------------------------------------------
// @ 0x1151570
void cRibbonEmitter::BuildSegments()
{
    float fSpacing = mField50;
    mField138 = mField58;
    if (mCount0 == 2) {
        for (int i = 0; i < mCount1; i++) {
            float* pfW = (float*)((char*)this + 0x168 + i * 0x10);
            float* pfP = (float*)((char*)this + 0xd8 + i * 0x14);
            float t = (*pfW + 1.0f) * 0.5f;
            float u = 1.0f - t;
            pfP[0]  = u;
            pfP[-1] = t;
            float f2 = ((1.0f / sqrt(t * t + u * u)) * mField84) * fSpacing;
            pfP[-1]  = f2 * t;
            pfP[0]   = u * f2;
        }
        return;
    }
    for (int i = 0; i < mCount1; i++) {
        float* pfP = (float*)((char*)this + 0xd8 + i * 0x14);
        SegmentBase(i);
        AddSegmentOffset(i);
        float f3 = pfP[3];
        float f2 = pfP[2];
        float f1 = pfP[1];
        float f0 = pfP[-1];
        float fz = pfP[0];
        float sc = ((1.0f / sqrt(fz * fz + (f0 * f0 + (f1 * f1 + (f2 * f2 + f3 * f3)))))
                    * mField84) * fSpacing;
        pfP[-1] = f0 * sc;
        pfP[0]  = fz * sc;
        pfP[1]  = f1 * sc;
        pfP[2]  = f2 * sc;
        pfP[3]  = f3 * sc;
    }
}

// ---- build vertex buffers (798 bytes) -------------------------------------------------------
// @ 0x1151720
void cRibbonEmitter::BuildVertexBuffers(cVertexBuffer* pSrc, cVertexBuffer* pDst,
                                        float* pSaved, float fScale)
{
    float afDelta[40];
    int   nSeg = mCount1;
    if (nSeg > 0) {
        float* pfOut = afDelta;
        float* pfSeg = (float*)((char*)this + 0xd4);
        float* pfIn  = pSaved;
        for (int k = 0; k < nSeg; k++) {
            pfOut[0] = (pfSeg[0] - pfIn[0]) * 0.015625f;
            pfOut[1] = (pfSeg[1] - pfIn[1]) * 0.015625f;
            pfOut[2] = (pfSeg[2] - pfIn[2]) * 0.015625f;
            pfOut[3] = (pfSeg[3] - pfIn[3]) * 0.015625f;
            pfOut[4] = (pfSeg[4] - pfIn[4]) * 0.015625f;
            pfOut += 5; pfSeg += 5; pfIn += 5;
        }
    }
    float fAlpha = (mField138 - fScale) * 0.015625f;
    int   idx[5];
    idx[0] = 0;
    if (mCount0 == 4) {
        idx[1] = 2; idx[2] = 3; idx[3] = 4;
    } else {
        idx[1] = 1; idx[2] = 2; idx[3] = 3; idx[4] = 4;
    }
    u32 n0 = (u32)mCount0;
    for (u32 i = 0; i < n0; i++) {
        Emit60300(pSrc->mpData + pSrc->mStride * i, pDst->mpData,
                  pSaved[idx[i]], afDelta[idx[i]], 0x100);
    }
    for (int s = 1; s < mCount1; s++) {
        for (u32 i = 0; i < n0; i++) {
            Emit600e0(pSrc->mpData + pSrc->mStride * i,
                      pDst->mpData + pDst->mStride * s,
                      pSaved[idx[i] + s * 5], afDelta[idx[i] + s * 5], 0x100);
        }
    }
    if (mField21 == 6) {
        if (mField20 == 6) {
            Emit60300(pSrc->mpData + pSrc->mStride * 5,
                      pDst->mpData + pDst->mStride * 5, fScale, fAlpha, 0x100);
            return;
        }
        float* pfRow = pSrc->mpData + pSrc->mStride * 5;
        Emit60300(pfRow, pDst->mpData, fScale, fAlpha, 0x100);
        for (int s = 1; s < mCount1; s++) {
            Emit600e0(pfRow, pDst->mpData + pDst->mStride * s, fScale, fAlpha, 0x100);
        }
    }
}

// ---- capacity-dependent multi-lane emit (489 bytes) -----------------------------------------
// @ 0x1151a40
void cRibbonEmitter::EmitSegments(cVertexBuffer* pSrc, cVertexBuffer* pDst)
{
    int idx[5];
    idx[0] = 0;
    if (mCount0 == 4) {
        idx[1] = 2; idx[2] = 3; idx[3] = 4;
    } else {
        idx[1] = 1; idx[2] = 2; idx[3] = 3; idx[4] = 4;
    }
    float* pDstBase = pDst->mpData;
    u32 n0 = (u32)mCount0;
    for (u32 i = 0; i < n0; i++) {
        float fVal = *((float*)this + idx[i] + 0x35);
        Emit34260(pSrc->mpData + pSrc->mStride * i, pDstBase, fVal, 0x100);
    }
    for (int s = 1; s < mCount1; s++) {
        float* pfDstRow = pDstBase + pDst->mStride * s;
        for (u32 i = 0; i < n0; i++) {
            float fVal = *((float*)this + (idx[i] + s * 5) + 0x35);
            Emit342c0(pSrc->mpData + pSrc->mStride * i, pfDstRow, fVal, 0x100);
        }
    }
    if (mField21 == 6) {
        if (mField20 == 6) {
            Emit34260(pSrc->mpData + pSrc->mStride * 5,
                      pDstBase + pDst->mStride * 5, mField138, 0x100);
            return;
        }
        float* pfSrcRow = pSrc->mpData + pSrc->mStride * 5;
        Emit34260(pfSrcRow, pDstBase, mField138, 0x100);
        for (int s = 1; s < mCount1; s++) {
            Emit342c0(pfSrcRow, pDstBase + pDst->mStride * s, mField138, 0x100);
        }
    }
}

// ---- top-level per-frame update (468 bytes) -------------------------------------------------
// @ 0x1151c30
int cRibbonEmitter::Update(char* pStream, u8 bRebuild)
{
    float f0 = mField28, f1 = mField30, f2 = mField38, f3 = mField40;
    float f4 = mField48, f5 = mField50, f6 = mField58;
    u32   uA = *(u32*)(pStream + 0x3000c);
    u32   uB = *(u32*)(pStream + 0x30010);

    bool bSame = (f0 == mField60) && (f1 == mField64) && (f2 == mField68)
              && (f3 == mField6c) && (f4 == mField70) && (f5 == mField74)
              && (f6 == mField78);
    if (!bSame) {
        float fAlpha = mField138;
        float afSave[40];
        if (mCount1 > 0) {
            float* pSrcS = (float*)((char*)this + 0xd4);
            float* pDstS = afSave;
            for (int i = mCount1; i != 0; i--) {
                pDstS[0] = pSrcS[0];
                pDstS[1] = pSrcS[1];
                pDstS[2] = pSrcS[2];
                pDstS[3] = pSrcS[3];
                pDstS[4] = pSrcS[4];
                pSrcS += 5; pDstS += 5;
            }
        }
        SegmentBaseXY();
        BuildSegments();
        mField60 = f0; mField64 = f1; mField68 = f2; mField6c = f3;
        mField70 = f4; mField74 = f5; mField78 = f6;
        if (bRebuild == 0) {
            BuildVertexBuffers((cVertexBuffer*)uB, (cVertexBuffer*)uA, afSave, fAlpha);
            goto done;
        }
    } else {
        if (bRebuild) {
            SegmentBaseXY();
            BuildSegments();
        }
    }
    EmitSegments((cVertexBuffer*)uB, (cVertexBuffer*)uA);
done:
    {
        u32 t = *(u32*)(pStream + 0x3000c);
        *(u32*)(pStream + 0x3000c)  = *(u32*)(pStream + 0x30010);
        *(u32*)(pStream + 0x30010) = t;
    }
    return 1;
}

// ---- per-frame inverse-path constants (173 bytes) -------------------------------------------
// @ 0x1151e10
void cRibbonEmitter::ComputeCurve()
{
    float fT = 0.0f;
    if (mField21 == 6) {
        fT = mField38;
    }
    float fU   = 1.0f / mField78;
    float fV   = (1.0f - fT) / mField74;
    float fInv = 1.0f / sqrt(fT * fT + (fV * fV * 2.0f + fU * fU * 2.0f));
    *(float*)((char*)this + 0xcc) = fInv * fT;
    mFieldbc  = fInv * fV;
    mFieldc0  = fInv * fV;
    mFieldc4  = fInv * fU;
    mFieldc8  = fInv * fU;
}

}} // namespace EA::Swarm
