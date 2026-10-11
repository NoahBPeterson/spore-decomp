// Slice s00f21850 (batch gold1) — SP drama-event / held-object helpers.
// Module "Spore" (VS2008 SP1). /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.

#include "types.h"

static inline void* VFN(void* obj, int off) { return *(void**)(*(unsigned int*)obj + off); }

extern "C" {
    unsigned int DAT_016c7aa4, DAT_016c8328, DAT_016c832c, DAT_016c8330;
    unsigned int DAT_016c8374, DAT_016c8398, DAT_016c839c, DAT_016c83a0;
    unsigned int DAT_016c83a4, DAT_016c83b8, DAT_016c83d0, DAT_016c83d4, DAT_016c83e0;
    unsigned int DAT_016c83b8_;

    unsigned int SP_PropertyManager();
    unsigned int SP_EffectsManager();
    unsigned int SP_GetPropertyAsFloat();
    unsigned int SP_GonzagoModelWorld();
    int   SPIDFromName(const char*);
    int   SPIDFromName2(const char*, unsigned int);
    unsigned int FUN_00ac8fa0(unsigned int, unsigned int, unsigned int);
    unsigned int FUN_00ac8fa0b(unsigned int, unsigned int);
    int   FUN_00f3e8a0(unsigned int);
    int   FUN_00f27670();
    unsigned int FUN_00eede20(void*, void*, void*, ...);
    unsigned int FUN_00f200c0(unsigned int, float);
    void  FUN_00eed0b0(unsigned int, void*, void*);
    void  FUN_00f20be0(void*, void*, unsigned int, unsigned int, unsigned int, unsigned int);
    void* FUN_00f20c60(void*, void*, unsigned int);
    unsigned int FUN_004a9b40(void*, unsigned int);
    unsigned int FUN_006c0200();
    void  FUN_00f202b0(unsigned int, int);
    unsigned int FUN_00f20260(void*, void*, unsigned int);
    void  FUN_00f25110();
    void  SP_Matrix3FromQuaternion_();     // placeholder
    unsigned int FUN_00b3d240();
    char  FUN_0069b910(void*, void*, unsigned int, void*);
    int   EA_RefCountRelease(const char*, unsigned int, int);
    float FUN_00e696a0(unsigned int, unsigned int, unsigned int, unsigned int);
}
namespace eastl {
    void vector_cSpatialObject_dtor(void*);
    void basic_string_DeallocateSelf();
}

// @ 0x00f21850
void FUN_00f21850(float* param_1, float* param_2, float* param_3, unsigned int param_4,
                  unsigned int param_5, float* param_6)
{
    *param_6 = 1.0f;
    *param_3 = 1.0f;
    *param_2 = 1.0f;
    void* local = 0;
    void* piVar4 = (void*)SP_PropertyManager();
    char cVar3 = ((char(__thiscall*)(void*, float, float, void**))VFN(piVar4, 0x2c))
                     (piVar4, param_1[0], param_1[2], (void**)&local);
    if (cVar3 == 0)
        return;
    *param_1 = *param_2;
    *param_2 = *param_3;
    (void)param_4; (void)param_5;
}

// @ 0x00f21a90
unsigned int FUN_00f21a90(int* param_1)
{
    int iVar1 = ((int(__thiscall*)(void*))VFN(param_1, 4))(param_1);
    int iVar2 = FUN_00f3e8a0(*(unsigned int*)(iVar1 + 0x1c));
    iVar1 = param_1[1];
    if (iVar1 == 0xe)
    {
        iVar1 = *(int*)(iVar2 + 0x48);
        if (-1 < iVar1)
        {
            if (iVar1 < 2)
                return 0;
            if (iVar1 == 2)
                return (unsigned int)EA_RefCountRelease("ep1_powerup_skinned_supporting", 0x811c9dc5u, 1);
        }
        return (unsigned int)EA_RefCountRelease("ep1_powerup", 0x811c9dc5u, 1);
    }
    iVar2 = *(int*)(iVar2 + 0x24);
    if (iVar2 == 0)
    {
        if (iVar1 == 0x10)
            return (unsigned int)EA_RefCountRelease("ep1_teleporter_exit", 0x811c9dc5u, 1);
    }
    else
    {
        if (iVar2 != 1)
        {
            if (iVar2 == 2)
            {
                if (iVar1 != 0x10)
                {
                    unsigned int k = SPIDFromName("ep1_powerup");
                    k = SPIDFromName2("physicsPropSkinned", k);
                    return FUN_00ac8fa0b(param_1[6], k);
                }
                return (unsigned int)SPIDFromName("ep1_powerup");
            }
            return (unsigned int)EA_RefCountRelease("ep1_powerup", 0x811c9dc5u, 1);
        }
        if (iVar1 == 0x10)
            return 0;
    }
    unsigned int uVar3 = (unsigned int)EA_RefCountRelease("ep1_powerup", 0x811c9dc5u, 1);
    unsigned int uVar4 = (unsigned int)EA_RefCountRelease("physicsProp", 0x811c9dc5u, 1);
    return FUN_00ac8fa0(param_1[6], uVar4, uVar3);
}

// @ 0x00f21bb0
unsigned int* FUN_00f21bb0(unsigned int param_1, unsigned int* param_2)
{
    void* local = 0;
    void* piVar2 = (void*)SP_PropertyManager();
    char cVar1 = ((char(__thiscall*)(void*, float, float, void**))VFN(piVar2, 0x2c))
                     (piVar2, *(float*)param_2, *(float*)(param_2 + 2), (void**)&local);
    if (cVar1 == 0)
    {
        param_2[0] = 0;
        param_2[1] = 0;
        param_2[2] = 0;
        return param_2;
    }
    unsigned int iVar3 = FUN_00ac8fa0b((unsigned int)local, DAT_016c83b8);
    unsigned int ebp = 0;
    void* pv = 0;
    if (iVar3 == 8)
    {
        unsigned char tmp[0x30];
        FUN_00f20be0(tmp, (void*)local, DAT_016c83d4, 0, 0, 0);
    }
    else if (iVar3 == 0xb)
    {
        unsigned char au[16];
        unsigned int* puVar4 = (unsigned int*)FUN_00f20c60(au, (void*)local, DAT_016c83d0);
        ebp = puVar4[0];
        pv = (void*)puVar4[2];
    }
    param_2[0] = ebp;
    param_2[1] = 0xb1b104u;
    param_2[2] = (unsigned int)pv;
    if (local != 0)
        ((void(__thiscall*)(void*))VFN(local, 4))(local);
    return param_2;
}

// @ 0x00f21cd0  eastl::multimap<unsigned int,EA::AutoRefCount<SP::cDramaEventInstanceData>,
//                              eastl::less<unsigned int>,eastl::allocator>::equal_range
namespace eastl {
struct DramaEventMultiMap
{
    void equal_range(void** out, const unsigned int* key);
};
}
void eastl::DramaEventMultiMap::equal_range(void** out, const unsigned int* key)
{
    void** root = *(void***)((char*)this + 0xc);
    void** lower = (void**)((char*)this + 4);
    void** upper = lower;
    void** node = root;
    if (node != 0)
    {
        do
        {
            void** next;
            if (*key < (unsigned int)node[4]) { next = (void**)node[1]; upper = node; }
            else next = (void**)*node;
            node = next;
        } while (node != 0);
    }
    node = root;
    if (node != 0)
    {
        do
        {
            void** next;
            if ((unsigned int)node[4] < *key) next = (void**)*node;
            else { next = (void**)node[1]; lower = node; }
            node = next;
        } while (node != 0);
    }
    out[1] = upper;
    out[0] = lower;
}

// @ 0x00f21d30
void FUN_00f21d30(float* pos, float* orient, float scale, unsigned int spid)
{
    (void)pos; (void)orient; (void)scale; (void)spid;
    void* local = 0;
    void* piVar3 = (void*)SP_EffectsManager();
    char cVar2 = ((char(__thiscall*)(void*, void**))VFN(piVar3, 0x2c))(piVar3, (void**)&local);
    if (cVar2 == 0)
        return;
    unsigned char s[0x40];
    *(unsigned int*)(s + 0x00) = 0;
    *(unsigned int*)(s + 0x04) = DAT_016c8398;
    *(unsigned int*)(s + 0x08) = DAT_016c839c;
    *(unsigned int*)(s + 0x0c) = DAT_016c83a0;
    *(unsigned int*)(s + 0x10) = 0x3f800000u;
    *(unsigned short*)(s + 0x00) = 0;
    *(unsigned short*)(s + 0x00) = *(unsigned short*)(s + 0x00) | 4;
    *(short*)(s + 0x02) = *(short*)(s + 0x02) + 1;
    (void)scale;
}

// @ 0x00f21e60
unsigned int FUN_00f21e60(int* param_1)
{
    int* piVar4 = (int*)((int(__thiscall*)(void*))VFN(param_1, 8))(param_1);
    unsigned int* puVar5 = (unsigned int*)((unsigned int(__thiscall*)(void*))VFN(piVar4, 0x2c))(piVar4);
    unsigned int uStack_28 = puVar5[0], uStack_24 = puVar5[1], uStack_20 = puVar5[2];
    piVar4 = (int*)((int(__thiscall*)(void*))VFN(param_1, 8))(param_1);
    puVar5 = (unsigned int*)((unsigned int(__thiscall*)(void*))VFN(piVar4, 0x30))(piVar4);
    unsigned int uStack_10 = puVar5[0], uStack_c = puVar5[1];
    void* piStack_8 = (void*)puVar5[2];
    unsigned int uStack_4 = puVar5[3];
    piVar4 = (int*)((int(__thiscall*)(void*))VFN(param_1, 8))(param_1);
    float fVar9 = ((float(__thiscall*)(void*))VFN(piVar4, 0x34))(piVar4);
    int iVar1 = param_1[0xb];
    int* puVar5b = (int*)FUN_00f3e8a0(iVar1);
    unsigned int uStack_1c = 0, uStack_18 = 0, uStack_14 = 0;
    char cVar3 = (char)FUN_00f27670();
    if (cVar3 == 0)
    {
        unsigned int uVar6 = FUN_00ac8fa0b(param_1[6], DAT_016c83a4);
        FUN_00f21d30((float*)&uStack_28, (float*)&uStack_10, fVar9, uVar6);
    }
    if (puVar5b == 0)
    {
        return FUN_00eede20(&uStack_1c, &uStack_28, &uStack_10, fVar9, 0, 0xffffffff, 0, 0,
                            *(unsigned int*)(*(int*)(DAT_016c7aa4 + 0x78) + 0xb8));
    }
    unsigned int uVar6;
    if (piStack_8 != 0)
    {
        int iVar8 = FUN_00ac8fa0b((unsigned int)piStack_8, DAT_016c83b8);
        if (iVar8 == 9)
        {
            unsigned char tmp[0x30];
            return FUN_00f20260(tmp, &uStack_1c, (unsigned int)puVar5b);
        }
    }
    ((void(__thiscall*)(void*, int, unsigned int))VFN(param_1, 4))(param_1, 0,
        *(unsigned int*)(*(int*)(DAT_016c7aa4 + 0x78) + 0xb8));
    uVar6 = FUN_006c0200();
    uVar6 = FUN_00eede20(puVar5b, 0, &uStack_1c, (unsigned int)puVar5b, 0, iVar1, uVar6, 0);
    FUN_00f202b0(uVar6, iVar1);
    if (piStack_8 != 0)
        ((void(__thiscall*)(void*))VFN(piStack_8, 4))(piStack_8);
    return uVar6;
}

// @ 0x00f22070  (SP::UpdateHeldObject)
unsigned int FUN_00f22070(int* param_1)
{
    unsigned int f0 = (unsigned int)param_1[0xb];
    f0 = (unsigned int)FUN_00f3e8a0(f0);
    ((void(__thiscall*)(void*))VFN(param_1, 4))(param_1);
    int iVar5 = FUN_006c0200();
    unsigned int held = 0;
    FUN_00f25110();
    if (((unsigned char*)&held)[3] != 0)
        return 0;

    int* piVar6 = (int*)SP_GonzagoModelWorld();
    int* obj = (int*)((int(__thiscall*)(void*))VFN(piVar6, 0xc))(piVar6);
    if (obj == 0)
        return 0;

    float cx = (float)obj[0x1c];
    float cy = (float)obj[0x1d];
    float cz = (float)obj[0x1e];
    float ex = (float)obj[0x1f];
    float ey = (float)obj[0x20];
    float ez = (float)obj[0x21];
    ((void(__thiscall*)(void*))VFN(obj, 0x16c))(obj);

    // orientation + position of the query volume (built from the held object's transform)
    unsigned char q[0x44];
    *(float*)(q + 0x00) = *(float*)&DAT_016c8328;
    *(float*)(q + 0x04) = *(float*)&DAT_016c832c;
    *(float*)(q + 0x08) = *(float*)&DAT_016c8330;
    *(float*)(q + 0x14) = 1.0f;
    *(float*)(q + 0x00) = *(float*)(iVar5 + 4);
    *(float*)(q + 0x04) = *(float*)(iVar5 + 8);
    *(float*)(q + 0x08) = *(float*)(iVar5 + 0xc);
    *(unsigned short*)(q + 0x10) = 0;
    *(unsigned short*)(q + 0x10) = *(unsigned short*)(q + 0x10) | 4;
    *(float*)(q + 0x14) = *(float*)(iVar5 + 0x20);

    float midz = (cz + cx) * 0.5f;
    float midx = (ex + cy) * 0.5f;
    float midy = (cy + ex) * 0.5f;
    (void)midz;

    int* world = (int*)FUN_00b3d240();
    float dx = ex - cx;
    float dy = ey - cy;
    float dz = ez - cz;
    float len;
    float len2 = dx * dx + dy * dy + dz * dz;
    __asm { fld len2 }
    __asm { fsqrt }
    __asm { fstp len }
    ((void(__thiscall*)(void*, void*, float, void*, int, int))VFN(world, 0x48))
        (world, q, len, 0, 0, 0);
    (void)midx; (void)midy; (void)f0;
    return 0;
}
