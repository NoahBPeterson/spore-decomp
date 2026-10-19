// src/game/SPEngine/SPGraphicsBufferDraw.cpp -- migrated from slice(s) s006dd250 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsBufferDraw.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_d3d9Device;            // _m_d3d9Device_ActiveState...
extern void* g_shader;               // _m_shader_ActiveState...
extern int   g_softStateUpdated;     // _m_softStateUpdated...
extern int   g_activeVertexDesc;     // _m_vertexDescriptor_ActiveState...
extern int   DAT_016f9138, DAT_016f913c, DAT_016f9140, DAT_016f8afc;
extern int   DAT_016f9144[];         // table up to 0x016f9168
extern void* DAT_016079a0;
extern void* DAT_016079a4;

// ---- items of slice s006dd250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_d3d9Device;            // _m_d3d9Device_ActiveState...
extern void* g_shader;               // _m_shader_ActiveState...
extern int   g_softStateUpdated;     // _m_softStateUpdated...
extern int   g_activeVertexDesc;     // _m_vertexDescriptor_ActiveState...
extern int   DAT_016f9138, DAT_016f913c, DAT_016f9140, DAT_016f8afc;
extern int   DAT_016f9144[];         // table up to 0x016f9168
extern void* DAT_016079a0;
extern void* DAT_016079a4;
int  __cdecl VertexDescriptor_AreEqual(void* a, void* b);
struct VertexDesc { void Refresh(); };   // out-of-line 0x011f2bc0
struct CBufferDraw { void IssueDraw(int param_2); int Lock(int count, void* out, uint32_t* stride, int flag); uint32_t FUN_006ddb40(int param_2, void* param_3, uint32_t* param_4, int param_5, int* param_6, int param_7); };
// ---- items of slice s006dd250 end

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
