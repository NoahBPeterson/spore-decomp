// nSPSkinner mesh loading + skin-weight accumulation (/Od /Ob1 /MD /Gy /TP /arch:SSE).
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

inline void* operator new(unsigned int, void* p) { return p; }
extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);

// helpers (external instantiations)
void  DoInsertPairs(void* end, uint32_t n, const void* value);     // 0x004cef00
void* ErasePairs(void* first, void* last);                         // vector<pair<int,float>>::erase
void  ClustersAndEdges(void* mesh, int flags);                     // 0x00733ed0 / CreateClustersAndEdges
int   MeshOp1(void* mesh);                                         // 0x00733ed0
int   MeshOp2(void* mesh, int, int, int, int);                     // 0x0071ddc0
int   MeshOp3(void* mesh, int, int*, int*, int, int*, int);           // 0x0071ded0
void  MeshOp4(void* mesh);                                         // 0x00736b00
int   MeshOp5(void* mesh);                                         // 0x0071e230
void* CreateRaster(int w, int h, int a, int b, int c);             // SP::CreateRaster
int   RasterFill(void* r, int);                                    // rw::graphics::Raster::Fill
void  RasterMip(void* r, void* data, int);                         // D3D9GetStreamedMipLevelSize
void* TextureManager();                                            // 0x0067dd60
void  FUN_00402420(...);                                           // 0x00402420
void  ReleaseRaster(void*);                                        // 0x00402420
void  FUN_00473810(int);
void  FUN_00473dc0(int);
void  FUN_0050d3c0(int);
void* FUN_0044e460(void* out, void* a, void* b);
void* V3NormalizeSafe(void* out, void* in);                        // SP::normalized_safe
int   FUN_00467980(int);
void  FUN_004cd3c0(int);
void  FUN_00533680(void*, void*, char);
void  FUN_0052b060Impl(void*, void*, float);
void  FUN_0052b170Impl(void*, float);
void  FUN_0052b220Impl(void*, void*);
void  FUN_0052ae30(uint32_t, const void*);
bool  SP_GetResourceTypeFromModelType();               // 0x00526430

extern uint8_t DAT_013f18d0[3];
extern uint8_t DAT_013f18d8[3];
extern float   _DAT_0150cb00;
extern uint8_t DAT_013f1f10[64];

struct TexMgr {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual void* v19(int, int, void*, int);      // +0x4c
};

// @ 0x0052a400  nSPSkinner::CreatePlaceholderTextures
int CreatePlaceholderTextures(int a, int b, int c, int* out1, int* out2, float* color)
{
    float f = color[0];
    if (f < 0.0f) f = 0.0f;
    f = f * 255.0f;
    if (f > 255.0f) f = 255.0f;
    uint8_t local_36 = (uint8_t)(int)(f + 0.5f);
    f = color[1];
    if (f < 0.0f) f = 0.0f;
    f = f * 255.0f;
    if (f > 255.0f) f = 255.0f;
    uint8_t local_37 = (uint8_t)(int)(f + 0.5f);
    f = color[2];
    if (f < 0.0f) f = 0.0f;
    f = f * 255.0f;
    if (f > 255.0f) f = 255.0f;
    uint8_t local_38 = (uint8_t)(int)(f + 0.5f);
    uint8_t local_35 = 0xff, local_31 = 0xff, local_2d = 0xff, local_29 = 0xff;
    int local_3c = 0, local_40 = 0;
    uint8_t local_34 = local_38, local_33 = local_37, local_32 = local_36;
    uint8_t local_30 = local_38, local_2f = local_37, local_2e = local_36;
    uint8_t local_2c = local_38, local_2b = local_37, local_2a = local_36;
    uint8_t local_25 = local_38, local_1d = local_37, local_15 = local_36;
    uint8_t buf[16];
    buf[0] = local_38; buf[1] = local_37; buf[2] = local_36; buf[3] = 0xff;
    buf[4] = local_34; buf[5] = local_33; buf[6] = local_32; buf[7] = local_35;
    buf[8] = local_30; buf[9] = local_2f; buf[10] = local_2e; buf[11] = local_31;
    buf[12] = local_2c; buf[13] = local_2b; buf[14] = local_2a; buf[15] = local_29;
    (void)local_25; (void)local_1d; (void)local_15;

    int iVar2;
    void* pR = CreateRaster(2, 2, 0, 8, 0x15);
    if (pR && (iVar2 = RasterFill(pR, 0)) == 0x10) {
        RasterMip(pR, buf, 0);
        TexMgr* tm = (TexMgr*)TextureManager();
        iVar2 = (int)tm->v19(a, b, pR, 0);
        if (iVar2 != 0) {
            local_3c = iVar2;
            *(int*)(iVar2 + 8) = *(int*)(iVar2 + 8) + 1;
        }
    }
    int iVar1 = local_3c;
    pR = CreateRaster(2, 2, 0, 8, 0x15);
    if (pR && (iVar2 = RasterFill(pR, 0)) == 0x10) {
        RasterMip(pR, DAT_013f1f10, 0);
        TexMgr* tm = (TexMgr*)TextureManager();
        iVar2 = (int)tm->v19(a, c, pR, 0);
        if (iVar2 != 0) {
            local_40 = iVar2;
            *(int*)(iVar2 + 8) = *(int*)(iVar2 + 8) + 1;
        }
    }
    int iVar4 = local_40;
    if (out1) *out1 = iVar1;
    if (out2) *out2 = iVar4;
    if (local_40) ReleaseRaster((void*)local_40);
    if (local_3c) ReleaseRaster((void*)local_3c);
    return 1;
}

// @ 0x0052a700  LoadSkinnerMesh
int LoadSkinnerMesh(int mesh, int md)
{
    MeshOp1((void*)mesh);
    ClustersAndEdges((void*)mesh, 1);
    uint32_t i = 0;
    uint32_t nBlocks = (uint32_t)((*(int*)(mesh + 0x20) - *(int*)(mesh + 0x1c)) / 0x8c);
    while (i < nBlocks) {
        if (SP_GetResourceTypeFromModelType())
            break;
        i++;
    }
    if (i < nBlocks)
        return 0;

    int r = MeshOp2((void*)mesh, 3, -1, 3, 0xe);
    if (r < 0)
        MeshOp4((void*)mesh);
    int local_48[4] = { 1, 2, 3, 8 };
    int local_38[4] = { 3, 3, 3, 2 };
    int local_24[4] = { -1, -1, -1, -1 };
    uint32_t uVar4 = (uint32_t)MeshOp3((void*)mesh, 4, local_24, local_48, 0, local_38, 0);
    if ((uVar4 & 0xff) == 0)
        return uVar4 & 0xffffff00u;

    uint32_t* local_10 = (uint32_t*)(*(int*)(mesh + 8) + 0x10 + local_24[0] * 0x20);
    uint32_t* local_54 = (uint32_t*)(*(int*)(mesh + 8) + 0x10 + local_24[1] * 0x20);
    int local_8 = *(int*)(mesh + 8) + 0x10 + local_24[2] * 0x20;
    uint32_t* local_28 = (uint32_t*)(*(int*)(mesh + 8) + 0x10 + local_24[3] * 0x20);
    int local_c = (*(int*)(md + 0xc) - *(int*)(md + 8)) / 0xc;
    int local_4c = (*(int*)(md + 0x20) - *(int*)(md + 0x1c)) / 0xc;
    int local_14 = (*(int*)(md + 0x48) - *(int*)(md + 0x44)) / 0x18;
    int local_50 = (*(int*)(md + 0x34) - *(int*)(md + 0x30)) >> 3;
    FUN_00473810(local_c + *local_10);
    for (uint32_t k = 0; k < *local_10; k++) {
        uint32_t* src = (uint32_t*)(*(uint16_t*)((char*)local_10 + 10) * k + local_10[1]);
        uint32_t* dst = (uint32_t*)(*(int*)(md + 8) + (local_c + k) * 0xc);
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
    }
    FUN_00473810(local_4c + *local_54);
    for (uint32_t k = 0; k < *local_54; k++) {
        uint32_t* dst = (uint32_t*)((local_4c + k) * 0xc + *(int*)(md + 0x1c));
        char tmp[12];
        uint32_t* src = (uint32_t*)V3NormalizeSafe(tmp, (void*)(*(uint16_t*)((char*)local_54 + 10) * k + local_54[1]));
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
    }
    FUN_00473dc0(local_50 + *local_28);
    FUN_0050d3c0(*(int*)(md + 0x34) - *(int*)(md + 0x30) >> 3);
    for (uint32_t k = 0; k < *local_28; k++) {
        uint32_t* src = (uint32_t*)(*(uint16_t*)(local_8 + 10) * k + *(int*)(local_8 + 4));
        uint32_t* dst = (uint32_t*)(*(int*)(md + 0x44) + (local_14 + k) * 0x18);
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
        int row = (local_14 + k) * 0x18 + *(int*)(md + 0x44);
        char tmp[12];
        uint32_t* t = (uint32_t*)FUN_0044e460(tmp, (void*)(*(uint16_t*)((char*)local_54 + 10) * k + local_54[1]),
                                              (void*)(*(uint16_t*)(local_8 + 10) * k + *(int*)(local_8 + 4)));
        *(uint32_t*)(row + 0xc) = t[0];
        *(uint32_t*)(row + 0x10) = t[1];
        *(uint32_t*)(row + 0x14) = t[2];
        uint32_t* s2 = (uint32_t*)(*(uint16_t*)((char*)local_28 + 10) * k + local_28[1]);
        int base = *(int*)(md + 0x30);
        *(uint32_t*)(base + (local_50 + k) * 8) = s2[0];
        *(uint32_t*)(base + 4 + (local_50 + k) * 8) = s2[1];
    }
    int pairv[2] = { 0, -1 };
    FUN_0052ae30((uint32_t)(*(int*)(md + 0x34) - *(int*)(md + 0x30)) >> 3, pairv);
    (void)pairv;
    for (uint32_t b = 0; b < (uint32_t)((*(int*)(mesh + 0x20) - *(int*)(mesh + 0x1c)) / 0x8c); b++) {
        uint32_t* blk = (uint32_t*)(b * 0x8c + *(int*)(mesh + 0x1c));
        char ok = (char)MeshOp5(blk + 5);
        if (ok) {
            uint32_t cnt = *blk;
            int local_8c = (*(int*)(md + 0x5c) - *(int*)(md + 0x58)) >> 2;
            FUN_004cd3c0(local_8c + cnt);
            FUN_004cd3c0(local_8c + cnt);
            FUN_004cd3c0(local_8c + cnt);
            for (uint32_t m = 0; m < cnt; m++) {
                int idx = FUN_00467980(m);
                *(int*)(*(int*)(md + 0x58) + (local_8c + m) * 4) = local_c + idx;
                *(int*)(*(int*)(md + 0x6c) + (local_8c + m) * 4) = local_4c + idx;
                *(int*)(*(int*)(md + 0x80) + (local_8c + m) * 4) = local_50 + idx;
                if (*(int*)(*(int*)(md + 0x124) + 4 + (local_50 + idx) * 8) == -1)
                    *(int*)(*(int*)(md + 0x124) + 4 + (local_50 + idx) * 8) = local_8c + m;
            }
        }
    }
    return 1;
}

// @ 0x0052ae30  vector<pair<int,float>>::resize(n, value)
struct PairVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mFlags[2];
    void resize(uint32_t n, const void* value);   // 0x0052ae30
};
void PairVec::resize(uint32_t n, const void* value)
{
    uint32_t cur = (uint32_t)((uint32_t*)mpEnd - (uint32_t*)mpBegin) >> 1;
    if (cur < n)
        DoInsertPairs(mpEnd, n - cur, value);
    else
        ErasePairs((char*)mpBegin + n * 8, mpEnd);
}

// ---------------------------------------------------------------- skinning
// @ 0x0052aeb0
void SkinBoneWeights(int out1, int out2, int param_3, int param_4, float param_5)
{
    int iVar1 = *(int*)(param_4 + 0xc);
    int iVar2 = *(int*)(param_4 + 8);
    for (int b = 0; b < (iVar1 - iVar2) / 0xc; b++) {
        *(uint32_t*)(param_3 + 0x14) = 0;
        uint32_t uVar3 = *(uint32_t*)(*(int*)(param_4 + 0xa8) + b * 4);
        uint32_t local_10 = uVar3;
        uint32_t uVar5;
        do {
            uVar5 = (int)(char)(&DAT_013f18d8)[local_10 % 3] + local_10;
            int iVar4 = *(int*)(*(int*)(param_4 + 0x58) + ((int)(char)(&DAT_013f18d0)[local_10 % 3] + local_10) * 4);
            float* pfVar7 = (float*)(b * 0xc + *(int*)(param_4 + 0x1c));
            float* pfVar6 = (float*)(iVar4 * 0xc + *(int*)(param_4 + 0x1c));
            float dp = pfVar6[0] * pfVar7[0] + pfVar6[1] * pfVar7[1] + pfVar6[2] * pfVar7[2];
            if (_DAT_0150cb00 < dp)
                FUN_0052b060Impl((void*)(iVar4 * 0x14 + out1), (void*)iVar4, dp * dp);
            local_10 = *(uint32_t*)(*(int*)(param_4 + 0x94) + uVar5 * 4);
        } while (local_10 != uVar5 && local_10 != uVar3);
        FUN_0052b170Impl((void*)(b * 0x14 + out1), param_5);
        FUN_0052b060Impl((void*)(b * 0x14 + out1), (void*)b, 1.0f - param_5);
        FUN_0052b220Impl((void*)(b * 0x14 + out2), (void*)b);
    }
}

// @ 0x0052b060
void AccumBoneWeight(int* this_, int param_2, float param_3)
{
    for (int i = 0; i < 4 && 0.0f < *(float*)(param_2 + 4 + i * 4); i++) {
        int j = 0;
        while (j < this_[5] && *(char*)(*this_ + j * 8) != *(char*)(param_2 + i))
            j++;
        if (j < this_[5]) {
            float* pf = (float*)(*this_ + 4 + j * 8);
            *pf = *(float*)(param_2 + 4 + i * 4) * param_3 + *pf;
        } else {
            *(uint8_t*)(*this_ + this_[5] * 8) = *(uint8_t*)(param_2 + i);
            *(float*)(*this_ + 4 + this_[5] * 8) = *(float*)(param_2 + 4 + i * 4) * param_3;
            this_[5] = this_[5] + 1;
        }
    }
}

// @ 0x0052b170
void NormalizeBoneWeights(int* this_, float param_2)
{
    float total = 0.0f;
    for (int i = 0; i < this_[5]; i++)
        total = total + *(float*)(*this_ + 4 + i * 8);
    if (0.0f < total) {
        for (int i = 0; i < this_[5]; i++) {
            float* pf = (float*)(*this_ + 4 + i * 8);
            *pf = (param_2 / total) * *pf;
        }
    }
}

// @ 0x0052b220
void CopyTopBoneWeights(int* this_, int param_2)
{
    char tmp;
    FUN_00533680((void*)*this_, (void*)this_[1], tmp);
    float total = 0.0f;
    for (int i = 0; i < 4; i++) {
        if (i < this_[5]) {
            *(uint8_t*)(param_2 + i) = *(uint8_t*)(*this_ + i * 8);
            float f = *(float*)(*this_ + 4 + i * 8);
            *(float*)(param_2 + 4 + i * 4) = f;
            total = total + f;
        } else {
            *(uint32_t*)(param_2 + 4 + i * 4) = 0;
        }
    }
    if (0.0f < total) {
        for (int i = 0; i < 4; i++) {
            float* pf = (float*)(param_2 + 4 + i * 4);
            *pf = *pf / total;
        }
    }
}
