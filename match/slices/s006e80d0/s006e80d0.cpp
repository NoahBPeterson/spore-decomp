// Slice s006e80d0 -- deterministic decompilation of SporeApp.exe region.
// Class identity: SP::cSPCreatureBase (debug render / body-part material helpers).
// All member offsets are raw where the real class layout is uncertain.
#include <algorithm>
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned long long u64;

// ---- external thiscall surface (callees; targets are relocation-masked) ----
struct Ext {
    void* r6f2050(int, int);
    char  r6f4170();
    void* r6f41e0(int);
    void* r6f3fe0();
    void  r6f3ee0(int);
    void* r6f3f20(int);
    float r6f3ff0(int);
    float r6f4010(int);
    float r6f4000(int);
    void  r6f4190(void*);
    void* r6f3fb0(int);
    void  r7c4010(void*);
    void  r7c50b0(int, int, int);
    void  r7c4ad0(float, float);
    void  r7c4ba0(float);
    void  r7c4bc0(float);
    void  r7c4be0(void*, int);
    void  r7c3c50(int);
    void  r7c3cb0(void*);
    void  r7a4420(int, int, int, int);
    int   r7a47c0(int, int, int);
    char  r7a4910(int, int, int, int, int);
    void  r7a4650();
    void* r776420(float, float);
    void  r776440();
    void  r7764a0();
    void  r7764c0(int, int, float, float);
    void  r776520(int, int, float, float);
    void  r776a60(int, void*, void*);
    char  r7773c0(unsigned int, int, int, int);
    char  r7775a0(unsigned int, int, int, int);
};

extern void*  F_67dd50();
extern void*  F_67dd70();   // SP::MaterialManager
extern void*  F_67dd40();
extern void*  F_67ddb0();
extern void*  f6f4170();
extern void   F_777ae0(int, void*, int);
extern void   f76d5c0();
extern void   f76d6e0();

extern void*  g15ddc84;    // _spInstance_..StaticBufferDraw
extern void*  g15d0838;    // default camera raster
extern void*  g1618d10;

#define VFN(p, off)  (*(void***)(p))[((off) >> 2)]

struct CCreature {
    char m_unk[0x9c0];
    // 0x006e80d0
    void m80d0(int idx, int a, int b);
    // 0x006e8160
    void m8160(float a, float b);
    // 0x006e8200
    char m8200(char* p, int a);
    // 0x006e82b0
    void m82b0(int a, int b, float c, float d);
    // 0x006e8360
    void m8360(int a);
    // 0x006e83e0
    void m83e0(int a, int* out1, int* out2);
    // 0x006e8420
    void m8420(int a, void* b);
    // 0x006e8480
    void m8480(void* b);
    // 0x006e8810
    void m8810(uint* flags, void** p3, uint* p4);
    // 0x006e8d70 / 0x006e8dd0 forwarders
    void m8d70(int, int, void*, int, int, int, int, int, int);
    void m8dd0(int, int, int, int, void*, int, int, int, int, int, int, int);
    // 0x006e8e40
    void m8e40(int a, int b);
    // 0x006e8ee0
    int  m8ee0(int a, int b, int c);
    // 0x006e8f20
    char m8f20(int a, int b, int c, int d, int e);
    // 0x006e8f60
    u64  m8f60(int a);
};

// 0x006e8f50 is a free (cdecl) function.
int f8f50();

// ---------------------------------------------------------------------------
// @ 0x006e80d0
void CCreature::m80d0(int idx, int a, int b)
{
    char* self = (char*)this;
    int off = idx * 0x68;
    void* e = *(void**)(self + 0x1b8);
    void* p = *(void**)((char*)e + off + 0x60);
    if (p) {
        ((void(__thiscall*)(void*, int, int, int))VFN(p, 0x20))(p, idx, a, b);
        return;
    }
    void* r = ((Ext*)(*(void**)(self + 0x40)))->r6f2050(a, b);
    if (r) {
        *(uint*)((char*)*(void**)(self + 0x1b8) + off + 0x54) = *(uint*)r;
        *(uint*)((char*)*(void**)(self + 0x1b8) + off + 0x58) = *(uint*)((char*)r + 4);
        return;
    }
    void* mm = F_67dd70();
    void* base = (char*)*(void**)(self + 0x1b8) + off;
    int v = ((int(__thiscall*)(void*, int))VFN(mm, 0x28))(mm, a);
    *(uint*)((char*)base + 0x54) = (uint)v;
}

// ---------------------------------------------------------------------------
// @ 0x006e8160
void CCreature::m8160(float a, float b)
{
    if (*(void**)((char*)this + 0x20) == 0)
        return;
    int rect[4];
    ((Ext*)(*(void**)((char*)this + 0x20)))->r7c4010(rect);
    float x = a / (float)(rect[2] - rect[0]);
    float y = b / (float)(rect[3] - rect[1]);
    ((Ext*)(*(void**)((char*)this + 0x20)))->r7c4ad0(x, y);
    if (*(void**)((char*)this + 0x360))
        ((Ext*)(*(void**)((char*)this + 0x360)))->r776420(-x, -y);
}

// ---------------------------------------------------------------------------
// @ 0x006e8200
char CCreature::m8200(char* p, int a)
{
    char* self = (char*)this;
    if (*(char*)(self + 0x368)) {
        void* m = F_67dd50();
        ((void(__thiscall*)(void*, int, int))VFN(m, 0x60))(m, 0x16, 2);
        *(char*)(self + 0x368) = 0;
    }
    if (*p == '\n') {
        void* q = *(void**)(self + 0x35c);
        if (q)
            return (char)((int(__thiscall*)(void*, void*, int, ushort))VFN(q, 0x18))(
                q, *(void**)(p + 0x10), a, *(ushort*)(p + 2));
        return 0;
    }
    void* h = *(void**)(self + 0x360);
    if (h && ((Ext*)h)->r7773c0((unsigned char)*p, *(int*)(p + 8), *(int*)(p + 0xc), a))
        return 1;
    void* h2 = *(void**)(self + 0x364);
    if (h2 && ((Ext*)h2)->r7775a0((unsigned char)*p, *(int*)(p + 8), *(int*)(p + 0xc), a))
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006e82b0
void CCreature::m82b0(int a, int b, float c, float d)
{
    if (a >= 0xc) {
        if (*(void**)((char*)this + 0x35c) == 0)
            return;
        ((void(__thiscall*)(void*, int, int, float, float))VFN(
            *(void**)((char*)this + 0x35c), 0x1c))(
            *(void**)((char*)this + 0x35c), a, b, c, d);
        return;
    }
    if (a < 1)
        return;
    {
        void* h = *(void**)((char*)this + 0x360);
        int t = a - 1;
        if (h && (t == 5 || t == 4)) {
            ((Ext*)h)->r7764c0(a, b, c, d);
            return;
        }
    }
    {
        void* h2 = *(void**)((char*)this + 0x364);
        if (h2)
            ((Ext*)h2)->r776520(a, b, c, d);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e8360
void CCreature::m8360(int a)
{
    char* self = (char*)this;
    void* r = *(void**)(self + 0x35c);
    if (r && a >= 0xc) {
        ((void(__thiscall*)(void*, int))VFN(r, 0x20))(r, a);
        ((Ext*)(*(void**)(self + 0x20)))->r7c3cb0(g15d0838);
        goto done;
    }
    if (a < 1)
        goto done;
    {
        void* h = *(void**)(self + 0x360);
        int t = a - 1;
        if (h && (t == 5 || t == 4)) {
            ((Ext*)h)->r776440();
        } else {
            void* h2 = *(void**)(self + 0x364);
            if (h2)
                ((Ext*)h2)->r7764a0();
        }
    }
done:
    {
        void* m = F_67dd50();
        ((void(__thiscall*)(void*, int, int))VFN(m, 0x60))(m, 0x16, 2);
        *(char*)(self + 0x368) = 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e83e0
void CCreature::m83e0(int a, int* out1, int* out2)
{
    *(int*)((char*)this + 0x15c) = std::min(a, 0x9c4);
    int v = (int)g1618d10 + 0x10;
    *out1 = v;
    *out2 = 0x50;
}

// ---------------------------------------------------------------------------
// @ 0x006e8420
void CCreature::m8420(int a, void* b)
{
    char* self = (char*)this;
    void* old = *(void**)(self + 0x28);
    if (b != old) {
        if (b)
            ((void(__thiscall*)(void*))VFN(b, 0x8))(b);
        *(void**)(self + 0x28) = b;
        if (old)
            ((void(__thiscall*)(void*))VFN(old, 0xc))(old);
    }
    if (a != 0) {
        *(void**)(self + 0x20) = (void*)a;
    } else {
        void* q = *(void**)(self + 0x28);
        *(void**)(self + 0x20) = (void*)((int(__thiscall*)(void*))VFN(q, 0x1c))(q);
    }
    if (*(void**)(self + 0x35c))
        ((Ext*)(*(void**)(self + 0x35c)))->r6f3ee0(a);
}

// ---------------------------------------------------------------------------
// @ 0x006e8480
void CCreature::m8480(void* b)
{
    char* self = (char*)this;
    if (*(void**)(self + 0x1e0) == b)
        return;
    if (*(void**)(self + 0x1e0) != 0) {
        int n = (*(int*)(self + 0x4c) - *(int*)(self + 0x48)) / 0x70;
        if (n > 0) {
            char* p = *(char**)(self + 0x48);
            for (int i = 0; i < n; i++, p += 0x70) {
                void* v = *(void**)(p + 0x68);
                if (v) {
                    void* q = *(void**)(self + 0x1e0);
                    ((void(__thiscall*)(void*, void*))VFN(q, 0x20))(q, v);
                    *(void**)(p + 0x68) = 0;
                }
            }
        }
        n = (*(int*)(self + 0x178) - *(int*)(self + 0x174)) / 0x70;
        if (n > 0) {
            char* p = *(char**)(self + 0x174);
            for (int i = 0; i < n; i++, p += 0x70) {
                void* v = *(void**)(p + 0x64);
                if (v) {
                    void* q = *(void**)(self + 0x1e0);
                    ((void(__thiscall*)(void*, void*))VFN(q, 0x20))(q, v);
                    *(void**)(p + 0x64) = 0;
                }
            }
        }
        n = (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68;
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                char* base = *(char**)(self + 0x1b8);
                void* v = *(void**)(base + i * 0x68 + 0x5c);
                if (v) {
                    void* q = *(void**)(self + 0x1e0);
                    ((void(__thiscall*)(void*, void*))VFN(q, 0x20))(q, v);
                    base = *(char**)(self + 0x1b8);
                    *(void**)(base + i * 0x68 + 0x5c) = 0;
                }
            }
        }
    }
    {
        void* old = *(void**)(self + 0x1e0);
        if (b != old) {
            if (b)
                ((void(__thiscall*)(void*))VFN(b, 0x0))(b);
            *(void**)(self + 0x1e0) = b;
            if (old)
                ((void(__thiscall*)(void*))VFN(old, 0x4))(old);
        }
    }
    if (*(void**)(self + 0x1e0) != 0) {
        int n = (*(int*)(self + 0x60) - *(int*)(self + 0x5c)) >> 1;
        for (int i = 0; i < n; i++) {
            int idx = *(ushort*)(*(int*)(self + 0x5c) + i * 2);
            char* e = *(char**)(self + 0x48) + idx * 0x70;
            if (*(char*)(e + 0x48)) {
                float c[3];
                c[0] = (*(float*)(e + 0x30) + *(float*)(e + 0x3c)) * 0.5f;
                c[1] = (*(float*)(e + 0x40) + *(float*)(e + 0x34)) * 0.5f;
                c[2] = (*(float*)(e + 0x44) + *(float*)(e + 0x38)) * 0.5f;
                void* q = *(void**)(self + 0x1e0);
                *(int*)(e + 0x68) =
                    ((int(__thiscall*)(void*, float, float*))VFN(q, 0x18))(q, 1.0f, c);
            }
        }
        n = (*(int*)(self + 0x18c) - *(int*)(self + 0x188)) >> 1;
        for (int i = 0; i < n; i++) {
            int idx = *(ushort*)(*(int*)(self + 0x188) + i * 2);
            char* e = *(char**)(self + 0x174) + idx * 0x70;
            if (*(char*)(e + 0x48)) {
                float c[3];
                c[0] = (*(float*)(e + 0x2c) + *(float*)(e + 0x38)) * 0.5f;
                c[1] = (*(float*)(e + 0x3c) + *(float*)(e + 0x30)) * 0.5f;
                c[2] = (*(float*)(e + 0x40) + *(float*)(e + 0x34)) * 0.5f;
                void* q = *(void**)(self + 0x1e0);
                *(int*)(e + 0x64) =
                    ((int(__thiscall*)(void*, float, float*))VFN(q, 0x18))(q, 1.0f, c);
            }
        }
        n = (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68;
        for (int i = 0; i < n; i++) {
            char* base = *(char**)(self + 0x1b8);
            char* e = base + i * 0x68;
            if (*(char*)(e + 0x50) && *(void**)e != 0) {
                void* v = *(void**)e;
                float c[3];
                c[0] = (*(float*)((char*)v + 0x5c) + *(float*)((char*)v + 0x50)) * 0.5f;
                c[1] = (*(float*)((char*)v + 0x60) + *(float*)((char*)v + 0x54)) * 0.5f;
                c[2] = (*(float*)((char*)v + 0x64) + *(float*)((char*)v + 0x58)) * 0.5f;
                void* q = *(void**)(self + 0x1e0);
                *(int*)(e + 0x5c) =
                    ((int(__thiscall*)(void*, float, float*))VFN(q, 0x18))(q, 1.0f, c);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e8810
// Large body-part material/debug-render helper: resolve the part handle, run
// the property-list-driven viewer setup, then emit the Format draws.
// ---------------------------------------------------------------------------
extern void*  g_15fd918;          // 0x15fd918  SP::sAppProperties<cDirectPropertyList>

// property-list accessors on g_15fd918 (thiscall; 32-bit property key)
struct PropList {
    float F_6a2710(int key);      // 0x6a2710 GetFloatProperty
    int   F_6a2660(int key);      // 0x6a2660 GetIntProperty
    uchar F_6a25a0(int key);      // 0x6a25a0 GetDescription (byte)
};

void CCreature::m8810(uint* flags, void** p3, uint* p4)
{
    char* self = (char*)this;
    uint  fv = (uint)(intptr_t)flags;   // the flag word is the argument value itself
    void* m = F_67dd50();
    int   ddb0 = (int)(intptr_t)F_67ddb0();
    (void)ddb0;
#define MGR_0040(...)  ((void(__thiscall*)(void*, void*, int, int, void*, int, uint))VFN(m, 0x40))(m, __VA_ARGS__)
    if (*(void**)(self + 0x35c) == 0 ||
        ((Ext*)(*(void**)(self + 0x35c)))->r6f4170() != 0 ||
        (fv & 0x20) == 0) {
        if (*(void**)(self + 0x360) == 0)
            return;
        if ((fv & 8) == 0)
            return;
        ((Ext*)(*(void**)(self + 0x360)))->r776a60((int)fv, p3, p4);
        return;
    }

    void* handle = ((Ext*)(*(void**)(self + 0x35c)))->r6f41e0((int)(intptr_t)p3[0]);
    if (!handle)
        return;
    uint v40    = (uint)(int)handle;
    uint a3_1   = (uint)(intptr_t)p3[1];
    uint a3_2   = (uint)(intptr_t)p3[2];
    uint a3_3   = (uint)(intptr_t)p3[3];
    void* viewer = *(void**)(self + 0x254);

    if (*(void**)(self + 0x360) != 0 && (fv & 8) != 0) {
        void* q = *(void**)(self + 0x25c);
        if (!((char(__thiscall*)(void*))VFN(q, 0x104))(q))
            ((Ext*)(*(void**)(self + 0x360)))->r776a60((int)fv, (void*)&v40, p4);
    }

    if (((Ext*)(*(void**)(self + 0x35c)))->r6f3fe0()) {
        MGR_0040(p4, 4, 0x15, &v40, 1, 0);
        F_777ae0(0x223, 0, 1);
        uint  h3    = (uint)(int)((Ext*)(*(void**)(self + 0x35c)))->r6f3f20((int)(intptr_t)p3[0]);
        float f3ff0 = ((Ext*)(*(void**)(self + 0x35c)))->r6f3ff0((int)(intptr_t)p3[0]);
        float f4010 = ((Ext*)(*(void**)(self + 0x35c)))->r6f4010((int)(intptr_t)p3[0]);
        float f4000 = ((Ext*)(*(void**)(self + 0x35c)))->r6f4000((int)(intptr_t)p3[0]);
        (void)f4010; (void)f4000;
        F_777ae0(0x231, &f3ff0, 0);
        MGR_0040(p4, 8, 8, &h3, 1, 0x1000000);
        MGR_0040(p4, 0xa, 0xa, &h3, 1, 0x1000000);
        MGR_0040(p4, 0xc, 0xf, &h3, 1, 0x1000000);
        MGR_0040(p4, 0x12, 0x12, &h3, 1, 0x1000000);
        F_777ae0(0x231, 0, 0);
        F_777ae0(0x223, &h3, 1);
        goto done;
    }

    if (!((char(__thiscall*)(void*))VFN(*(void**)(self + 0x25c), 0x104))(*(void**)(self + 0x25c))) {
        MGR_0040(p4, 4, 0x15, &v40, 1, 0);
    } else {
        void* c = *(void**)(self + 0x25c);
        int  iVar5 = (int)((int(__thiscall*)(void*))VFN(c, 0x10c))(c);
        PropList* pl = (PropList*)g_15fd918;
        float  fVar17 = pl->F_6a2710(0x637fee8);
        int    iVar6  = pl->F_6a2660(0x628708c);
        uint   bVar2  = pl->F_6a25a0(0x6395f06);
        uint   bVar3  = pl->F_6a25a0(0x6395efa);
        uint   uVar15 = (bVar3 << 0x18) | (bVar2 << 0x10);
        if (*(void**)(self + 0x360) != 0 && (fv & 8) != 0)
            uVar15 = (uVar15 & 0xffff0000) | 0x100;
        else
            uVar15 = uVar15 & 0xffff0000;

        int slot0[2] = { -1, -1 };   // uStack_d4 / uStack_d0
        if (iVar6 == 3) {
            void* o = F_67dd40();
            ((void(__thiscall*)(void*, int, void*, int))VFN(o, 0xa8))(o, 0, slot0, 0);
        } else if (iVar6 == 2) {
            void* o = F_67dd40();
            ((void(__thiscall*)(void*, int, void*, int))VFN(o, 0xa8))(o, 3, slot0, 0);
        }

        int slot1[2] = { -1, -1 };   // ppuStack_c4 / uStack_c0
        ((Ext*)(*(void**)(self + 0x35c)))->r6f4190(slot1);
        ((Ext*)viewer)->r7c50b0((int)(intptr_t)p3[0], 0, 0);
        ((Ext*)viewer)->r7c4be0(slot0, 1);
        ((Ext*)viewer)->r7c3c50(7);
        uint vvec[4];
        vvec[0] = (uint)(intptr_t)p3[1];
        vvec[1] = (uint)(intptr_t)viewer;
        vvec[2] = (uint)(intptr_t)p3[2];
        vvec[3] = (uint)(intptr_t)p3[3];
        float* pfVar8 = (float*)((Ext*)(*(void**)(self + 0x35c)))->r6f3fb0((int)(intptr_t)p3[0]);
        uint pvec[4];
        pvec[0] = (uint)(intptr_t)p3[1];
        pvec[1] = (uint)(intptr_t)p3[2];
        pvec[2] = (uint)(intptr_t)p3[3];
        pvec[3] = (uint)(intptr_t)pfVar8;
        ((Ext*)viewer)->r7c4be0(slot0, 1);
        float fCur = ((float(__thiscall*)(void*))VFN(c, 0xf8))(c);
        ((Ext*)viewer)->r7c4ba0(fCur - fVar17);

        if (((uVar15 >> 0x10) & 0xff) != 0) {
            if (((uVar15 >> 8) & 0xff) != 0)
                ((Ext*)(*(void**)(self + 0x360)))->r776a60((int)fv, (void*)&vvec[1], p4);
            MGR_0040(p4, 4, 7, (void*)&pvec[0], 1, 0);
            if (iVar5 == 0) {
                MGR_0040(p4, 8, 8, (void*)&pvec[0], 1, 0x4000000);
                MGR_0040(p4, 0xa, 0xa, (void*)&slot1[1], 1, 0x4000000);
                MGR_0040(p4, 0xc, 0x15, (void*)&slot0[1], 1, 0x4000000);
            }
            if (iVar6 > 0)
                ((void(__thiscall*)(void*, int*, int*, int))VFN(slot0, 0x5c))(
                    slot0, slot0, slot1, 0);
        }
        if (((uVar15 >> 0x18) & 0xff) == 0 || iVar5 != 0) {
            if (iVar5 != 1)
                goto done;
            MGR_0040(p4, 8, 0x15, (void*)&vvec[0], 1, 0);
            goto done;
        }
        float fCur2 = ((float(__thiscall*)(void*))VFN(c, 0xf8))(c);
        ((Ext*)viewer)->r7c4bc0(fCur2 + fVar17);
        ((Ext*)viewer)->r7c3c50(6);
        MGR_0040(p4, 8, 0x15, (void*)&pvec[0], 1, 0x2000000);
    }
done:
    if (*(char*)(self + 0x368))
        ((void(__thiscall*)(void*, int, int))VFN(m, 0x5c))(m, 0x16, 2);
}

// ---------------------------------------------------------------------------
// @ 0x006e8d70
// Forwarder to vector<0x28>::push_back (0x76d5c0): the Vector3* argument is
// passed by value (three floats), so cl copies it into a caller temp.
struct Vec3 { float x, y, z; };
struct Vec28Sink {
    void push76d5c0(int a2, int a3, Vec3 v, int a5, int a6, int a7, int a8, int a9, int a10);
};

void CCreature::m8d70(int a2, int a3, void* a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
    Vec28Sink* o = (Vec28Sink*)*(void**)((char*)this + 0x24);
    if (o) {
        Vec3 v = *(Vec3*)a4;
        o->push76d5c0(a2, a3, v, a5, a6, a7, a8, a9, a10);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e8dd0
// Forwarder to the three-call helper at 0x76d6e0, also Vector3-by-value.
struct Vec3Sink {
    void push76d6e0(int a2, int a3, int a4, int a5, Vec3 v, int a7, int a8, int a9, int a10,
                    int a11, int a12, int a13);
};

void CCreature::m8dd0(int a2, int a3, int a4, int a5, void* a6, int a7, int a8, int a9,
                      int a10, int a11, int a12, int a13)
{
    Vec3Sink* o = (Vec3Sink*)*(void**)((char*)this + 0x24);
    if (o) {
        Vec3 v = *(Vec3*)a6;
        o->push76d6e0(a2, a3, a4, a5, v, a7, a8, a9, a10, a11, a12, a13);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e8e40
void CCreature::m8e40(int a, int b)
{
    char* self = (char*)this;
    void* inst = g15ddc84;
    switch (b) {
    case 0:
        ((Ext*)inst)->r7a4420(a, 3, 2, 0);
        *(int*)(self + 4) = 4;
        return;
    case 2:
        ((Ext*)inst)->r7a4420(a, 3, 6, 0);
        *(int*)(self + 4) = 4;
        return;
    case 3:
        ((Ext*)inst)->r7a4420(a, 3, 7, 0);
        *(int*)(self + 4) = 4;
        return;
    case 4:
        ((Ext*)inst)->r7a4420(a, 3, 8, 0);
        *(int*)(self + 4) = 4;
        return;
    default:
        *(int*)(self + 4) = 0;
        return;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e8ee0
int CCreature::m8ee0(int a, int b, int c)
{
    char* self = (char*)this;
    if (*(int*)(self + 4)) {
        void* sb = *(void**)g15ddc84;
        int r = ((Ext*)sb)->r7a47c0(*(int*)(self + 4) * a, b, c);
        return r / *(int*)(self + 4);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006e8f20
char CCreature::m8f20(int a, int b, int c, int d, int e)
{
    char* self = (char*)this;
    if (*(int*)(self + 4))
        return ((Ext*)*(void**)g15ddc84)->r7a4910(*(int*)(self + 4) * a, b, c, d, e);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006e8f50
int f8f50()
{
    void* sb = *(void**)g15ddc84;
    ((Ext*)sb)->r7a4650();
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006e8f60
u64 CCreature::m8f60(int a)
{
    void* p = *(void**)((char*)this + 0xc);
    if (p)
        return (u64)((uint(__thiscall*)(void*, int))VFN(p, 0x44))(p, a);
    return 0xffffffffffffffffULL;
}
