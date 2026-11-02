// src/game/SPEngine/SPGraphicsBufferDraw.cpp -- migrated from slice(s) s006de020, s006dd250 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsBufferDraw.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/graphics/VertexBuffer.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_d3d9Device;            // _m_d3d9Device_ActiveState...
extern void* g_shader;               // _m_shader_ActiveState...
extern int   g_softStateUpdated;     // _m_softStateUpdated...
extern int   g_activeVertexDesc;     // _m_vertexDescriptor_ActiveState...
extern int   DAT_016f9138, DAT_016f913c, DAT_016f9140, DAT_016f8afc;
extern int   DAT_016f9144[];         // table up to 0x016f9168
extern void* DAT_016079a0;
extern void* DAT_016079a4;
#include <xmmintrin.h>

// ---- items of slice s006dd250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_d3d9Device;            // _m_d3d9Device_ActiveState...
extern void* g_shader;               // _m_shader_ActiveState...
extern int   g_softStateUpdated;     // _m_softStateUpdated...
extern int   g_activeVertexDesc;     // _m_vertexDescriptor_ActiveState...
extern int   DAT_016f9138, DAT_016f913c, DAT_016f9140, DAT_016f8afc;
extern int   DAT_016f9144[];         // table up to 0x016f9168
extern void* DAT_016079a0;
extern void* DAT_016079a4;
int  __cdecl FUN_011f3620(int a, int b, int c);
struct VBi {
    uint32_t FUN_011f3620(uint32_t a, uint32_t b, uint32_t c);  // 0x011F3620
};
struct VertexBuffer {
    int* Lock(int a, int* b, int c, int d, int e);  // 0x006DD250
    int* Unlock();                                  // 0x011F36A0
};
int  __cdecl FUN_011f4f20(int a, void* out);
void __cdecl FUN_011f4fd0(void* p);
int  __cdecl VertexDescriptor_AreEqual(void* a, void* b);
void __cdecl VertexBuffer_Unlock(void* vb);
void __cdecl VecBool_DoInsertValue(void* a, void* b, uint32_t n);   // eastl::vector<bool> helper
void __fastcall FUN_006dd8b0(void* self);
struct VertexDesc { void Refresh(); };   // out-of-line 0x011f2bc0
struct CBufferDraw { void IssueDraw(int param_2); int Lock(int count, void* out, uint32_t* stride, int flag); bool FUN_006ddb40(int param_2, void* param_3, uint32_t* param_4, int param_5, int* param_6, int param_7); };
// ---- items of slice s006dd250 end

// ---- items of slice s006de020 begin (TODO(rewrite): local stubs, replace by canonical classes)
int* g_bufferDraw = 0;          // 0x01607728 cBufferDrawImpl singleton
int* _sAppProperties = 0;
int __cdecl FUN_011f1120();
void __cdecl FUN_006dd8b0();
void __cdecl FUN_006dd540(int a);
void __cdecl FUN_006ddd80(int a, int b, int c, int d);
int __cdecl FUN_006dd9b0(void* self, int count, void* out, uint32_t* stride, int flag);
void __cdecl CompiledState_Dispatch(void* cs);
void __cdecl GlobalState_D3D9Sync();
int DAT_016f9200 = 0;
struct Rec13
{
    int a, b;               // +0, +4
    float c;                // +8
    int d;                  // +c
    float e, f, g, h, i, j, k;   // +10..+28
    int l;                  // +2c
    float m;                // +30
    Rec13& operator=(const Rec13& src);   // 0x006de7f0
};
Rec13& Rec13::operator=(const Rec13& src)   // @ 0x006de7f0
{
    a = src.a;
    b = src.b;
    c = src.c;
    d = src.d;
    e = src.e;
    f = src.f;
    g = src.g;
    h = src.h;
    i = src.i;
    j = src.j;
    k = src.k;
    l = src.l;
    m = src.m;
    return *this;
}
// ---- items of slice s006de020 end

// @ 0x006dd2a0
void FUN_006dd2a0(void* param_1) // @ 0x006dd2a0
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

// @ 0x006dd540
void CBufferDraw::IssueDraw(int param_2)
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

// @ 0x006dd8b0
void __fastcall FUN_006dd8b0(void* self)
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

// @ 0x006dd9b0
int CBufferDraw::Lock(int param_2, void* param_3, uint32_t* param_4, int param_5)
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
    iVar3 = ((VBi*)piVar1)->FUN_011f3620((iVar3 != 0) * 4 + 4 | 2,
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

// @ 0x006ddb40
bool CBufferDraw::FUN_006ddb40(int param_2, void* param_3, uint32_t* param_4, int param_5, int* param_6, int param_7)
{
    void* self = this;
    char* p = (char*)this;
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
        void* vb = *(void**)(p + *(int*)(p + 0x1a0) * 4);
        int* r = ((VertexBuffer*)vb)->Lock((iVar4 != 0) * 4 + 4 | 2, local_8, (int)&param_2, iVar4, iVar2);
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
                return true;
            }
            ((VertexBuffer*)vb)->Unlock();
        }
        return false;
    }
    return false;
}

// @ 0x006de020
void FUN_006de020(int param_1, int param_2, int param_3)
{
    int uVar1 = DAT_016f9200;
    DAT_016f9200 = 3;
    float local_18 = 0.0f;
    float local_14 = 0.0f;
    if (*(int*)(*(int*)((char*)_sAppProperties + 0x3c) + 0x110) != 0)
    {
        int iVar2 = FUN_011f1120();
        local_18 = -1.0f / (float)*(uint16_t*)(*(int*)(iVar2 + 0x40) + 0xc);
        iVar2 = FUN_011f1120();
        local_14 = 1.0f / (float)*(uint16_t*)(*(int*)(iVar2 + 0x40) + 0xe);
    }
    *(int*)((char*)g_bufferDraw + 0x1a0) = 1;
    float* local_10 = 0;
    uint32_t local_c = 0;
    int iVar2 = FUN_006dd9b0(g_bufferDraw, 4, &local_10, &local_c, 0);
    if (iVar2 != 4)
    {
        FUN_006dd8b0();
        DAT_016f9200 = uVar1;
        return;
    }
    local_10[0] = local_18 - 1.0f;
    local_10[1] = local_14 - 1.0f;
    local_10[2] = 0.0f;
    local_10[3] = 0.0f;
    local_10[4] = 1.0f;
    local_10[5] = local_18 + 1.0f;
    local_10[6] = local_14 - 1.0f;
    local_10[7] = 0.0f;
    local_10[8] = 1.0f;
    local_10[9] = 1.0f;
    local_10[10] = local_18 + 1.0f;
    local_10[0xb] = local_14 + 1.0f;
    local_10[0xc] = 0.0f;
    local_10[0xd] = 1.0f;
    local_10[0xf] = local_18 - 1.0f;
    local_10[0xe] = 0.0f;
    local_10[0x10] = local_14 + 1.0f;
    local_10[0x11] = 0.0f;
    local_10[0x12] = 0.0f;
    local_10[0x13] = 0.0f;
    if (param_2 != 0)
    {
        FUN_006ddd80(5, param_1, param_2, param_3);
        DAT_016f9200 = uVar1;
        return;
    }
    FUN_006dd8b0();
    CompiledState_Dispatch(*(void**)(param_1 + 4));
    GlobalState_D3D9Sync();
    *(int*)((char*)g_bufferDraw + 0x1a4) = 5;
    FUN_006dd540(param_3);
    DAT_016f9200 = uVar1;
}
