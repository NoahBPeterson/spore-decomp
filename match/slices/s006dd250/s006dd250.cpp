// Slice s006dd250: D3D9 buffer-draw module (cBufferDrawImpl channel management,
// vertex/index lock helpers, draw issue and the ActiveState descriptor shims).
#include "../s006ccf50/s006ccf50.h"

// ---- globals ----------------------------------------------------------------
extern void* g_d3d9Device;            // _m_d3d9Device_ActiveState...
extern void* g_shader;               // _m_shader_ActiveState...
extern int   g_softStateUpdated;     // _m_softStateUpdated...
extern int   g_rasterDelta;          // _m_rasterDelta...
extern int   g_renderStateDirty;     // _m_renderStateDirty...
extern int   g_activeVertexDesc;     // _m_vertexDescriptor_ActiveState...
extern int   DAT_016f9138, DAT_016f913c, DAT_016f9140, DAT_016f8afc;
extern int   DAT_016f9144[];         // table up to 0x016f9168
extern void* DAT_016079a0;
extern void* DAT_016079a4;
extern int   DAT_016079a8;
extern int*  DAT_01607728;           // cBufferDrawImpl singleton
extern int   DAT_0160772c, DAT_01607730, DAT_016077c4, DAT_016077c8;
extern int*  _sAppProperties;

// ---- helpers ----------------------------------------------------------------
int  __cdecl FUN_011f3620(int a, int b, int c);
int  __cdecl FUN_007c3af0(const char* name);
int  __cdecl FUN_00762b70(int a, int b, int c, int d);
void* __cdecl FUN_00762c60(void* desc, int a, int b, int c, int d, int e);
void __cdecl FUN_00762a30(void* p);
void __cdecl FUN_00762a00(void* p);
void __cdecl FUN_011f2bc0();
int  __cdecl FUN_011f4f20(int a, void* out);
void __cdecl FUN_011f4fd0(void* p);
int  __cdecl FUN_011f1120();
void __cdecl FUN_011f53a0();   // placeholder (unused)

int  __cdecl VertexDescriptor_AreEqual(void* a, void* b);
void __cdecl ActiveState_SetTexture(void* a, void* b);
void __cdecl VertexBuffer_Unlock(void* vb);
uint32_t __cdecl VertexBuffer_UnlockR(void* vb);
void __fastcall CompiledState_Dispatch(void* cs);
void __cdecl GlobalState_D3D9Sync();
void __cdecl VecBool_DoInsertValue(void* a, void* b, uint32_t n);   // eastl::vector<bool> helper

void* __cdecl operator_new(uint32_t size, const char* tag, int a, int b, const char* file, int line);
void  __cdecl operator_delete__(void* p);
void  __cdecl operator_new__(void* p, int a, int b);

// slice-52 helpers (forward declarations)
void __cdecl FUN_006de2a0();
void __cdecl FUN_006de350();
void __fastcall FUN_006dd8b0(void* self);
int* __cdecl FUN_006dd250(void* self, int a, int* b, int c, int d, int e);
void __fastcall FUN_006dd4d0(void* self);

#define D3D9DEV ((void***)g_d3d9Device)

// ---------------------------------------------------------------------------
// 0x006dd250: lock a channel's vertex/index buffer range.
int* FUN_006dd250(void* self, int param_2, int* param_3, int param_4, int param_5, int param_6)   // @ 0x006dd250
{
    int* p = (int*)self;
    if (param_6 == 0)
        param_6 = p[3];
    int iVar1 = FUN_011f3620(param_2, (p[2] + param_5) * (uint32_t)*(uint8_t*)(*p + 0xf),
                             (uint32_t)*(uint8_t*)(*p + 0xf) * param_6);
    if (iVar1 == 0)
        return 0;
    *param_3 = iVar1;
    param_3[1] = (int)p;
    return p;
}

// 0x006dd2a0: rw::graphics::ActiveState::VertexDescriptorChange
struct VertexDesc { void Refresh(); };   // out-of-line 0x011f2bc0
void FUN_006dd2a0(void* param_1)   // @ 0x006dd2a0
{
    if (g_activeVertexDesc != 0)
    {
        if (VertexDescriptor_AreEqual((void*)g_activeVertexDesc, param_1) != 0)
            goto done;
    }
    g_softStateUpdated = g_softStateUpdated | 0x100000;
done:
    g_activeVertexDesc = (int)param_1;
    ((VertexDesc*)param_1)->Refresh();
}

// 0x006dd2e0: ActiveState::SetTexture + raster delta
void FUN_006dd2e0(void* param_1, void* param_2)   // @ 0x006dd2e0
{
    ActiveState_SetTexture(param_1, param_2);
    g_rasterDelta = g_rasterDelta | (1 << (uint32_t)param_1);
}

// 0x006dd310: cBufferDrawImpl constructor body
int __fastcall FUN_006dd310(void* self)   // @ 0x006dd310
{
    char* p = (char*)self;
    *(uint32_t*)(p + 0x30) = 0;
    *(uint32_t*)(p + 100) = 0;
    *(uint32_t*)(p + 0x68) = 0;
    *(uint32_t*)(p + 0x6c) = 0;
    *(uint8_t*)(p + 400) = 0;
    *(uint32_t*)(p + 0x194) = 0;
    *(uint32_t*)(p + 0x198) = 0;
    *(uint8_t*)(p + 0x19c) = 0;
    *(uint32_t*)(p + 0x1a0) = 0xc;
    *(uint32_t*)(p + 0x1a4) = 6;
    *(uint32_t*)(p + 0x1a8) = 0;
    *(uint32_t*)(p + 0x1ac) = 0;
    *(uint8_t*)(p + 0x1b0) = 0;
    operator_new__(p + 0x70, 0, 0x30);
    operator_new__(p + 0xa0, 0, 0x30);
    return (int)self;
}

// 0x006dd390: create all vertex declarations and channel buffers
void __fastcall FUN_006dd390(void* self)   // @ 0x006dd390
{
    char* p = (char*)self;
    FUN_006de2a0();
    int* piVar4 = (int*)(p + 0x34);
    piVar4[0] = FUN_007c3af0("V3FC4B");
    piVar4[1] = FUN_007c3af0("V3FT2F");
    piVar4[2] = FUN_007c3af0("V3FC4BT2F");
    piVar4[3] = FUN_007c3af0("V3FC4BT3F");
    piVar4[4] = FUN_007c3af0("V3FN3FC4BT2F");
    piVar4[5] = FUN_007c3af0("V3FC4BP1F");
    piVar4[6] = FUN_007c3af0("V4FN4FC4BT2F");
    piVar4[7] = FUN_007c3af0("V4FN4FC4BC4B");
    piVar4[8] = FUN_007c3af0("V4FN4FG3FC4BC4B");
    piVar4[9] = FUN_007c3af0("V4FN3FC4BT4FT4FT4FT4FT4F");
    piVar4[10] = FUN_007c3af0("V3FC4BT2FT2FT2F");
    piVar4[11] = FUN_007c3af0("V4FN4FC4BC4BT4B");
    int iVar1 = 0xc;
    do
    {
        if (*piVar4 == 0)
            piVar4[-0xd] = 0;
        else
            piVar4[-0xd] = FUN_00762b70(*piVar4, 0x1ff8, 1, 0);
        piVar4[0xf] = 0;
        piVar4[0x1b] = 0;
        piVar4[0x27] = 0;
        piVar4[0x33] = (int)operator_new(*(uint8_t*)(*piVar4 + 0xf), "Graphics", 0, 0, 0, 0);
        piVar4[0x3f] = 0;
        piVar4[0x4b] = 0;
        piVar4 = piVar4 + 1;
        iVar1 = iVar1 - 1;
    } while (iVar1 != 0);
    uint32_t uVar2 = (uint32_t)FUN_00762c60((void*)0, 0x3ff0, 0xbfd0, 8, 4, 0);
    *(uint32_t*)(p + 0x194) = 0;
    *(uint32_t*)(p + 0x30) = uVar2;
}

// 0x006dd4d0: destroy all channel buffers
void __fastcall FUN_006dd4d0(void* self)   // @ 0x006dd4d0
{
    char* p = (char*)self;
    if (*(int*)(p + 0x30) != 0)
    {
        FUN_00762a30(*(void**)(p + 0x30));
        *(uint32_t*)(p + 0x30) = 0;
    }
    uint32_t* puVar1 = (uint32_t*)(p + 0x100);
    int iVar2 = 0xc;
    do
    {
        puVar1[-0x33] = 0;
        FUN_00762a00((void*)puVar1[-0x40]);
        puVar1[-0x40] = 0;
        operator_delete__((void*)*puVar1);
        *puVar1 = 0;
        puVar1 = puVar1 + 1;
        iVar2 = iVar2 - 1;
    } while (iVar2 != 0);
    FUN_006de350();
}

// 0x006dd540: SP::cBufferDrawImpl::IssueDraw
// 0x006dd540: SP::cBufferDrawImpl::IssueDraw
struct CBufferDraw { void IssueDraw(int param_2); int Lock(int count, void* out, uint32_t* stride, int flag); };
void CBufferDraw::IssueDraw(int param_2)   // @ 0x006dd540
{
    char* p = (char*)this;
    int* dev = (int*)g_d3d9Device;
    int iVar3 = *(int*)(p + 0x1a0);
    if (iVar3 == 0xc)
        return;
    if (*(int*)(p + 0x1a4) == 6)
        return;
    int iVar5 = *(int*)(p + 0x194) - *(int*)(p + 0x198);
    int iVar8 = *(int*)(p + 0x70 + iVar3 * 4) - *(int*)(p + 0xa0 + iVar3 * 4);
    if (iVar8 == 0)
        return;
    FUN_006dd2a0(*(void**)(p + 0x34 + iVar3 * 4));
    // shader->vtable[5](DAT_016079a0)
    iVar3 = ((int(__thiscall*)(void*, void*))((void**)g_shader)[0x14/4])(g_shader, DAT_016079a0);
    if (iVar3 == 0)
        return;
    g_softStateUpdated = 0;
    int* piVar9 = *(int**)(p + *(int*)(p + 0x1a0) * 4);
    iVar3 = piVar9[1];
    uint32_t uVar4 = (uint32_t)*(uint8_t*)(*piVar9 + 0xf);
    if (DAT_016f9138 != iVar3 || DAT_016f913c != 0 || DAT_016f9140 != (int)uVar4)
    {
        ((void(__thiscall*)(void*, int, int, int, int))((void**)dev)[400/4])(dev, 0, iVar3, 0, uVar4);
        DAT_016f913c = 0;
        DAT_016f9138 = iVar3;
        DAT_016f9140 = uVar4;
    }
    int iStack_c = 1;
    piVar9 = DAT_016f9144;
    do
    {
        if (*piVar9 != 0)
        {
            ((void(__thiscall*)(void*, int, int, int, int))((void**)dev)[400/4])(dev, iStack_c, 0, 0, 0);
            *piVar9 = 0;
            piVar9[1] = 0;
            piVar9[2] = 0;
        }
        iStack_c = iStack_c + 1;
        piVar9 = piVar9 + 3;
    } while ((int)piVar9 < 0x16f9168);

    iStack_c = 0;
    if (*(int*)(p + 0x1a4) == 3)
        iStack_c = *(int*)DAT_016079a4;
    else if (0 < iVar5)
        iStack_c = **(int**)(p + 0x30);
    if (DAT_016f8afc != iStack_c)
    {
        ((void(__thiscall*)(void*, int))((void**)dev)[0x1a0/4])(dev, iStack_c);
        DAT_016f8afc = iStack_c;
    }

    uint32_t uVar10 = 0, uVar11 = 0;
    void (*pcVar7)(void*, int, int, int) = 0;
    switch (*(int*)(p + 0x1a4))
    {
    case 0:
        ((void(__thiscall*)(void*, int, int, int))((void**)dev)[0x144/4])
            (dev, 1, *(int*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4), iVar8);
        goto deflt;
    case 1:
        uVar11 = *(uint32_t*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4);
        uVar10 = 2;
        pcVar7 = *(void(**)(void*, int, int, int))((void**)dev + 0x144/4);
        break;
    case 2:
        if (iStack_c != 0)
        {
            ((void(__thiscall*)(void*, int, int, int, int, int, int))((void**)dev)[0x148/4])
                (dev, 4, *(int*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4), 0, iVar8,
                 *(int*)(*(int*)(p + 0x30) + 4) + *(int*)(p + 0x198), iVar5 / 3);
            goto deflt;
        }
        uVar11 = *(uint32_t*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4);
        uVar10 = 4;
        pcVar7 = *(void(**)(void*, int, int, int))((void**)dev + 0x144/4);
        break;
    case 3:
        ((void(__thiscall*)(void*, int, int, int, int, int, int))((void**)dev)[0x148/4])
            (dev, 4, *(int*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4), 0, iVar8,
             *(int*)((char*)DAT_016079a4 + 4), iVar8 / 2);
        *(int*)(param_2 + 0x24) += (iVar8 * 3) / 2;
        goto deflt;
    case 4:
        if (iStack_c != 0)
        {
            ((void(__thiscall*)(void*, int, int, int, int, int, int))((void**)dev)[0x148/4])
                (dev, 5, *(int*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4), 0, iVar8,
                 *(int*)(*(int*)(p + 0x30) + 4) + *(int*)(p + 0x198), iVar5 + -2);
            goto deflt;
        }
        uVar11 = *(uint32_t*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4);
        uVar10 = 5;
        pcVar7 = *(void(**)(void*, int, int, int))((void**)dev + 0x144/4);
        break;
    case 5:
        if (iStack_c != 0)
        {
            ((void(__thiscall*)(void*, int, int, int, int, int, int))((void**)dev)[0x148/4])
                (dev, 6, *(int*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4), 0, iVar8,
                 *(int*)(*(int*)(p + 0x30) + 4) + *(int*)(p + 0x198), iVar5 + -2);
            goto deflt;
        }
        uVar11 = *(uint32_t*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4);
        uVar10 = 6;
        pcVar7 = *(void(**)(void*, int, int, int))((void**)dev + 0x144/4);
        break;
    default:
        goto deflt;
    }
    pcVar7(dev, uVar10, uVar11, iVar3);
deflt:
    *(int*)(param_2 + 0x20) += iVar8;
    *(int*)(param_2 + 0x24) += iVar5;
    *(int*)(param_2 + 0x28) += 1;
    *(int*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4) = *(int*)(p + 0x70 + *(int*)(p + 0x1a0) * 4);
    *(int*)(p + 0x198) = *(int*)(p + 0x194);
}

// 0x006dd8b0: flush/unlock the current channel if it is open
void __fastcall FUN_006dd8b0(void* self)   // @ 0x006dd8b0
{
    char* p = (char*)self;
    if (*(char*)(p + 400) != '\0')
    {
        int iVar1 = *(int*)(p + 0x1a0);
        if (*(int*)(p + 0x160 + iVar1 * 4) == 0)
        {
            *(uint32_t*)(p + 0xd0 + iVar1 * 4) = 0;
        }
        else
        {
            uint32_t size = (uint32_t)*(uint8_t*)(*(int*)(p + 0x34 + iVar1 * 4) + 0xf);
            if (*(int*)(p + 0x130 + iVar1 * 4) != 0)
            {
                VecBool_DoInsertValue(*(void**)(p + 0x130 + iVar1 * 4),
                                      *(void**)(p + 0xd0 + iVar1 * 4), size);
                iVar1 = *(int*)(p + 0x130 + *(int*)(p + 0x1a0) * 4);
                VecBool_DoInsertValue((void*)(iVar1 + size), (void*)(iVar1 + size * 2), size);
                *(uint32_t*)(p + 0x130 + *(int*)(p + 0x1a0) * 4) = 0;
            }
            *(uint32_t*)(p + 0xd0 + *(int*)(p + 0x1a0) * 4) =
                *(uint32_t*)(p + 0x100 + *(int*)(p + 0x1a0) * 4);
            VecBool_DoInsertValue(*(void**)(p + 0xd0 + *(int*)(p + 0x1a0) * 4),
                                  *(void**)(p + 0x160 + *(int*)(p + 0x1a0) * 4), size);
            *(uint32_t*)(p + 0x160 + *(int*)(p + 0x1a0) * 4) = 0;
        }
        VertexBuffer_Unlock(*(void**)(p + *(int*)(p + 0x1a0) * 4));
        *(uint8_t*)(p + 400) = 0;
    }
    if (*(char*)(p + 0x19c) != '\0')
    {
        FUN_011f4fd0(p + 100);
        *(uint8_t*)(p + 0x19c) = 0;
    }
}

// 0x006dd9b0: lock the current channel's buffer for writing
int CBufferDraw::Lock(int param_2, void* param_3, uint32_t* param_4, int param_5)   // @ 0x006dd9b0
{
    char* p = (char*)this;
    bool bVar2;
    if (*(char*)(p + 0x1b0) == '\0' || *(int*)(p + 0x1a4) != 4)
        bVar2 = false;
    else
        bVar2 = true;
    int iVar3 = 0;
    int local_4 = 0;
    int iVar5 = param_2;
    if (bVar2 && *(int*)(p + 0xd0 + *(int*)(p + 0x1a0) * 4) != 0)
    {
        iVar3 = 2;
        local_4 = 2;
        iVar5 = param_2 + 2;
    }
    if (0x1ff8 < *(int*)(p + 0x70 + *(int*)(p + 0x1a0) * 4) + iVar5)
    {
        if (*(char*)(p + 0x1b0) != '\0')
            this->IssueDraw(param_5);
        *(uint32_t*)(p + 0x70 + *(int*)(p + 0x1a0) * 4) = 0;
        *(uint32_t*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4) = 0;
        iVar5 = iVar5 - iVar3;
        local_4 = 0;
        *(uint32_t*)(p + 0xd0 + *(int*)(p + 0x1a0) * 4) = 0;
        if (0x1ff8 < iVar5)
            iVar5 = 0x1ff8;
    }
    iVar3 = *(int*)(p + 0x70 + *(int*)(p + 0x1a0) * 4);
    int* piVar1 = *(int**)(p + *(int*)(p + 0x1a0) * 4);
    int n = iVar5;
    if (iVar5 == 0)
        n = piVar1[3];
    iVar3 = FUN_011f3620((iVar3 != 0) * 4 + 4 | 2,
                         (piVar1[2] + iVar3) * (uint32_t)*(uint8_t*)(*piVar1 + 0xf),
                         (uint32_t)*(uint8_t*)(*piVar1 + 0xf) * n);
    if (iVar3 == 0)
        return 0;
    uint32_t uVar4 = (uint32_t)*(uint8_t*)(**(int**)(p + *(int*)(p + 0x1a0) * 4) + 0xf);
    int* piVar1b = (int*)(p + 0x70 + *(int*)(p + 0x1a0) * 4);
    *piVar1b = *piVar1b + iVar5;
    *(uint8_t*)(p + 400) = 1;
    if (bVar2)
    {
        *(uint32_t*)(p + 0x160 + *(int*)(p + 0x1a0) * 4) = (iVar5 + -1) * uVar4 + iVar3;
        if (*(int*)(p + 0xd0 + *(int*)(p + 0x1a0) * 4) != 0)
            *(uint32_t*)(p + 0x130 + *(int*)(p + 0x1a0) * 4) = iVar3;
        iVar3 = uVar4 * local_4 + iVar3;
        iVar5 = iVar5 - local_4;
    }
    *(int*)param_3 = iVar3;
    *param_4 = uVar4;
    return iVar5;
}

// 0x006ddb40: lock a rectangle of the index/vertex buffer
uint32_t FUN_006ddb40(void* self, int param_2, void* param_3, uint32_t* param_4, int param_5, int* param_6, int param_7)   // @ 0x006ddb40
{
    char* p = (char*)self;
    int iVar3 = param_5;
    int iVar2 = param_2;
    if (param_2 < 0x1ff9 && param_5 < 0xbfd1)
    {
        if (0x1ff8 < *(int*)(p + 0x70 + *(int*)(p + 0x1a0) * 4) + param_2 ||
            0xbfd0 < *(int*)(p + 0x194) + param_5)
        {
            if (*(char*)(p + 0x1b0) != '\0')
                ((CBufferDraw*)self)->IssueDraw(param_7);
            *(uint32_t*)(p + 0x70 + *(int*)(p + 0x1a0) * 4) = 0;
            *(uint32_t*)(p + 0xa0 + *(int*)(p + 0x1a0) * 4) = 0;
            *(uint32_t*)(p + 0x194) = 0;
            *(uint32_t*)(p + 0x198) = 0;
        }
        int iVar4 = *(int*)(p + 0x70 + *(int*)(p + 0x1a0) * 4);
        int local_8[2];
        int* r = FUN_006dd250(self, (iVar4 != 0) * 4 + 4 | 2, local_8, (int)&param_2, iVar4, iVar2);
        uint32_t uVar5 = 0;
        if (r != 0)
        {
            if (FUN_011f4f20(2, p + 100) != 0)
            {
                *(int*)param_3 = local_8[0];
                *param_4 = (uint32_t)*(uint8_t*)(**(int**)(p + *(int*)(p + 0x1a0) * 4) + 0xf);
                int iv = *(int*)(p + 100);
                iv = iv + *(int*)(p + 0x194) * 2;
                *param_6 = iv;
                *(int*)(p + 0x194) += iVar3;
                int* piVar1 = (int*)(p + 0x70 + *(int*)(p + 0x1a0) * 4);
                *(uint8_t*)(p + 0x19c) = 1;
                *piVar1 = *piVar1 + iVar2;
                *(uint8_t*)(p + 400) = 1;
                return 1;
            }
            uVar5 = VertexBuffer_UnlockR(*(void**)(p + *(int*)(p + 0x1a0) * 4));
        }
        return uVar5 & 0xffffff00;
    }
    return 0;
}

// 0x006ddc90: destroy the singleton
void FUN_006ddc90(void)   // @ 0x006ddc90
{
    if (DAT_01607728 != 0)
    {
        FUN_006dd4d0(DAT_01607728);
        operator_delete__(DAT_01607728);
        DAT_01607728 = 0;
    }
}

// 0x006ddcc0
bool FUN_006ddcc0(int param_1, int param_2, int param_3, int param_4)   // @ 0x006ddcc0
{
    *(uint32_t*)((char*)DAT_01607728 + 0x1a0) = param_1;
    int iVar1 = ((CBufferDraw*)DAT_01607728)->Lock(param_2, (void*)param_3, (uint32_t*)param_4, 0);
    if (param_2 == iVar1)
        return true;
    FUN_006dd8b0(DAT_01607728);
    return false;
}

// 0x006ddd10
void FUN_006ddd10(int param_1, int param_2)   // @ 0x006ddd10
{
    FUN_006dd8b0(DAT_01607728);
    *(uint32_t*)((char*)DAT_01607728 + 0x1a4) = param_1;
    GlobalState_D3D9Sync();
    ((CBufferDraw*)DAT_01607728)->IssueDraw(param_2);
}

// 0x006ddd40
void FUN_006ddd40(int param_1, int param_2, int param_3)   // @ 0x006ddd40
{
    FUN_006dd8b0(DAT_01607728);
    CompiledState_Dispatch(*(void**)(param_2 + 4));
    GlobalState_D3D9Sync();
    *(uint32_t*)((char*)DAT_01607728 + 0x1a4) = param_1;
    ((CBufferDraw*)DAT_01607728)->IssueDraw(param_3);
}

// 0x006ddd80
void FUN_006ddd80(int param_1, int param_2, int* param_3, int param_4)   // @ 0x006ddd80
{
    FUN_006dd8b0(DAT_01607728);
    CompiledState_Dispatch(*(void**)(param_2 + 4));
    ActiveState_SetTexture(0, (void*)*param_3);
    g_rasterDelta = g_rasterDelta | 1;
    GlobalState_D3D9Sync();
    *(uint32_t*)((char*)DAT_01607728 + 0x1a4) = param_1;
    ((CBufferDraw*)DAT_01607728)->IssueDraw(param_4);
}

// 0x006ddde0
void FUN_006ddde0(int param_1, int param_2)   // @ 0x006ddde0
{
    *(uint32_t*)((char*)DAT_01607728 + 0x1a4) = param_1;
    *(uint32_t*)((char*)DAT_01607728 + 0x1a0) = param_2;
    *(uint32_t*)((char*)DAT_01607728 + 0x1a8) = 0;
    *(uint32_t*)((char*)DAT_01607728 + 0x1ac) = 0;
    GlobalState_D3D9Sync();
    *(uint8_t*)((char*)DAT_01607728 + 0x1b0) = 1;
}

// 0x006dde30
void FUN_006dde30(int param_1, int param_2, int param_3)   // @ 0x006dde30
{
    *(uint32_t*)((char*)DAT_01607728 + 0x1a4) = param_1;
    *(uint32_t*)((char*)DAT_01607728 + 0x1a0) = param_2;
    *(uint32_t*)((char*)DAT_01607728 + 0x1a8) = param_3;
    *(uint32_t*)((char*)DAT_01607728 + 0x1ac) = 0;
    CompiledState_Dispatch(*(void**)(param_3 + 4));
    GlobalState_D3D9Sync();
    *(uint8_t*)((char*)DAT_01607728 + 0x1b0) = 1;
}

// 0x006dde90
void FUN_006dde90(int param_1, int param_2, int param_3, int param_4)   // @ 0x006dde90
{
    ((CBufferDraw*)DAT_01607728)->Lock(param_1, (void*)param_2, (uint32_t*)param_3, param_4);
}

// 0x006ddef0
void FUN_006ddef0(int param_1)   // @ 0x006ddef0
{
    if (*(char*)((char*)DAT_01607728 + 400) != '\0' || *(char*)((char*)DAT_01607728 + 0x19c) != '\0')
        FUN_006dd8b0(DAT_01607728);
    ((CBufferDraw*)DAT_01607728)->IssueDraw(param_1);
    *(uint32_t*)((char*)DAT_01607728 + 0x1a0) = 0xc;
    *(uint32_t*)((char*)DAT_01607728 + 0x1a4) = 6;
    *(uint32_t*)((char*)DAT_01607728 + 0x1a8) = 0;
    *(uint32_t*)((char*)DAT_01607728 + 0x1ac) = 0;
    *(uint8_t*)((char*)DAT_01607728 + 0x1b0) = 0;
}

// 0x006ddf80: install the singleton and vertex declarations
void FUN_006ddf80(void)   // @ 0x006ddf80
{
    int iVar1 = (int)operator_new(0x1b4, "Graphics/BufferDraw", 0, 0, 0, 0);
    if (iVar1 == 0)
        DAT_01607728 = 0;
    else
        DAT_01607728 = (int*)FUN_006dd310((void*)iVar1);
    FUN_006dd390(DAT_01607728);
    if (*(int*)(*(int*)((char*)_sAppProperties + 0x3c) + 0x110) != 0)
    {
        DAT_016077c4 = 0x3f000000;
        DAT_016077c8 = 0xbf000000;
        return;
    }
    DAT_016077c4 = DAT_0160772c;
    DAT_016077c8 = DAT_01607730;
}
