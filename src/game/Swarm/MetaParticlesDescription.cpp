// src/game/Swarm/MetaParticlesDescription.cpp -- migrated from slice(s) s00addb50 by tools/migrate/rewrite.py
// Object file: Swarm/MetaParticlesDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cConfigManager.h"
#include "EA/ArgScript/cArguments.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned int __cdecl FNV1_String8(const char* s, unsigned int seed, int flag);  // 0x932e80
extern void* g_vtbl_145b38c;    // 0x145b38c
extern void* g_vtbl_145b380;    // 0x145b380
extern void* g_vtbl_13eb844;    // 0x13eb844
extern void* g_vtbl_13eb90c;    // 0x13eb90c
extern const float g_1471064;             // 0x1471064
extern const float g_140f7ac;             // 0x140f7ac
extern const float g_1485720;             // 0x1485720

// ---- items of slice s00addb50 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void  (__thiscall *TC_v0)(void*);
typedef float (__thiscall *TC_fs)(void*, const char*);
typedef void* (__thiscall *TC_vps)(void*, void* out, const char* s);
#define VFN(obj, off, T) ((T)(*(void***)(obj))[((off) >> 2)])
void* operator new(unsigned int size, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
extern unsigned int __cdecl FNV1_String8(const char* s, unsigned int seed, int flag);  // 0x932e80
struct cArguments {
    const char** MainArguments(int n);                             // 0x838320
    const char** OptionArguments(const char* name, int n);         // 0x838330
    const char** OptionArguments(const char* name, int* count, int min, int max);  // 0x838130
    bool HasFlag(const char* name);                                // 0x8380b0
};
struct cAppState {
    void AddMessage(cArguments* args, void* refobj, char flag);    // 0x7e4190
};
struct SpVec3 {
    void* begin;                                    // +0
    void* end;                                      // +4
    void* cap;                                      // +8
    void* erase(void* begin, void* end);            // 0x50f740
    void  DoInsertValue(void* pos, const void* value);  // 0x4b5ad0
};
extern void* g_vtbl_145b38c;    // 0x145b38c
extern void* g_vtbl_145b380;    // 0x145b380
extern void* g_vtbl_13eb844;    // 0x13eb844
extern void* g_vtbl_13eb90c;    // 0x13eb90c
extern const float g_1471064;             // 0x1471064
extern const float g_140f7ac;             // 0x140f7ac
extern const float g_1485720;             // 0x1485720
// ---- items of slice s00addb50 end

// @ 0x00ade1d0
void __fastcall FUN_00ade1d0(void* self, int /*edx*/, cArguments* args)
{
    char* s = (char*)self;
    args->MainArguments(0);

    unsigned int* o = (unsigned int*)operator new(0x8c, "Simulator", 0, 0, 0, 0);
    if (o != 0) {
        o[1] = 0;
        unsigned int* sub = o + 2;                 // +8 sub-object
        *sub = (unsigned int)&g_vtbl_145b38c;      // dead store
        *o = (unsigned int)&g_vtbl_145b38c;
        *sub = (unsigned int)&g_vtbl_145b380;
        o[0x1b] = 0;
        o[0x1c] = 0;
        o[0x1d] = 0;
        VFN(sub, 0, TC_v0)(sub);
    } else {
        o = 0;
    }

    float zero = 0.0f;
    float k1471064 = g_1471064;
    *(float*)((char*)o + 0x80) = zero;
    *(float*)((char*)o + 0x84) = zero;
    *(float*)((char*)o + 0x88) = zero;
    *(float*)((char*)o + 0x14) = zero;
    *(float*)((char*)o + 0x18) = zero;
    *(float*)((char*)o + 0x60) = k1471064;
    *(float*)((char*)o + 0x1c) = zero;
    *(float*)((char*)o + 0x20) = zero;
    *(float*)((char*)o + 0x64) = g_140f7ac;
    *(float*)((char*)o + 0x24) = zero;
    *(float*)((char*)o + 0x28) = zero;
    o[0x10] = 3;
    *(char*)((char*)o + 0x3c) = 1;
    *(char*)((char*)o + 0x3e) = 0;
    o[4] = 0;
    *(char*)((char*)o + 0x44) = 0;
    *(float*)((char*)o + 0x54) = zero;
    *(float*)((char*)o + 0x58) = g_1485720;
    *(char*)((char*)o + 0x2c) = 0;
    *(char*)((char*)o + 0x3d) = 0;
    *(float*)((char*)o + 0x0c) = zero;
    *(char*)((char*)o + 0x5d) = 0;

    unsigned int* m = (unsigned int*)operator new(0x40, "Simulator", 0, 0, 0, 0);
    if (m != 0) {
        m[0xc] = 0;
        *m = (unsigned int)&g_vtbl_13eb90c;     // dead store
        m[1] = 0;
        m[0xe] = 0;
        *m = (unsigned int)&g_vtbl_13eb844;
        VFN(m, 4, TC_v0)(m);
    } else {
        m = 0;
    }

    unsigned int* r = o + 2;
    if ((m[0xe] & 1) != 0 && (unsigned int*)m[2] != 0)
        VFN((unsigned int*)m[2], 4, TC_v0)((unsigned int*)m[2]);
    m[2] = (unsigned int)r;
    if (r != 0)
        VFN(r, 0, TC_v0)(r);
    m[0xe] = m[0xe] | 1;
    m[0xc] = 0x04448b81;

    if (args->HasFlag("noWait"))
        *(char*)((char*)o + 0x3c) = 0;
    if (args->HasFlag("ease"))
        *(char*)((char*)o + 0x3e) = 1;

    const char** a;
    a = args->OptionArguments("target", 1);
    if (a != 0)
        o[4] = FNV1_String8(*a, 0x811c9dc5, 1);

    a = args->OptionArguments("pos", 1);
    if (a != 0) {
        unsigned int v[3];
        VFN(*(void**)(s + 4), 0xa8, TC_vps)(*(void**)(s + 4), v, *a);
        *(float*)((char*)o + 0x80) = *(float*)&v[0];
        *(float*)((char*)o + 0x84) = *(float*)&v[1];
        *(float*)((char*)o + 0x88) = *(float*)&v[2];
    }

    a = args->OptionArguments("targetOffset", 1);
    if (a != 0) {
        unsigned int v[3];
        VFN(*(void**)(s + 4), 0xa8, TC_vps)(*(void**)(s + 4), v, *a);
        *(float*)((char*)o + 0x14) = *(float*)&v[0];
        *(float*)((char*)o + 0x18) = *(float*)&v[1];
        *(float*)((char*)o + 0x1c) = *(float*)&v[2];
    }

    ((SpVec3*)((char*)o + 0x6c))->erase(*(void**)((char*)o + 0x6c), *(void**)((char*)o + 0x70));

    int count = 0;
    const char** e;
    e = args->OptionArguments("path", &count, 1, 1000);
    if (e != 0) {
        for (int i = 0; i < count; ++i) {
            unsigned int v[3];
            VFN(*(void**)(s + 4), 0xa8, TC_vps)(*(void**)(s + 4), v, e[i]);
            float x = *(float*)&v[0], y = *(float*)&v[1], z = *(float*)&v[2];
            float* dst = *(float**)((char*)o + 0x70);
            if ((char*)dst < *(char**)((char*)o + 0x74)) {
                *(float**)((char*)o + 0x70) = dst + 3;
                if (dst != 0) { dst[0] = x; dst[1] = y; dst[2] = z; }
            } else {
                ((SpVec3*)((char*)o + 0x6c))->DoInsertValue(dst, &x);
            }
        }
    } else {
        e = args->OptionArguments("pathEndStart", &count, 1, 1000);
        if (e != 0) {
            for (int i = 0; i < count; ++i) {
                unsigned int v[3];
                VFN(*(void**)(s + 4), 0xa8, TC_vps)(*(void**)(s + 4), v, e[i]);
                float x = *(float*)&v[0], y = *(float*)&v[1], z = *(float*)&v[2];
                float* dst = *(float**)((char*)o + 0x70);
                if ((char*)dst < *(char**)((char*)o + 0x74)) {
                    *(float**)((char*)o + 0x70) = dst + 3;
                    if (dst != 0) { dst[0] = x; dst[1] = y; dst[2] = z; }
                } else {
                    ((SpVec3*)((char*)o + 0x6c))->DoInsertValue(dst, &x);
                }
            }
            *(char*)((char*)o + 0x44) = 1;
        }
    }

    a = args->OptionArguments("fov", 1);
    if (a != 0)
        *(float*)((char*)o + 0x54) = VFN(*(void**)(s + 4), 0x98, TC_fs)(*(void**)(s + 4), (const char*)*a);
    a = args->OptionArguments("nearClip", 1);
    if (a != 0)
        *(float*)((char*)o + 0x60) = VFN(*(void**)(s + 4), 0x98, TC_fs)(*(void**)(s + 4), (const char*)*a);
    a = args->OptionArguments("farClip", 1);
    if (a != 0)
        *(float*)((char*)o + 0x64) = VFN(*(void**)(s + 4), 0x98, TC_fs)(*(void**)(s + 4), (const char*)*a);
    a = args->OptionArguments("duration", 1);
    if (a != 0)
        *(float*)((char*)o + 0x58) = VFN(*(void**)(s + 4), 0x98, TC_fs)(*(void**)(s + 4), (const char*)*a);

    ((cAppState*)*(void**)(s + 0xc))->AddMessage(args, m, 0);
    VFN(m, 8, TC_v0)(m);
    VFN(r, 4, TC_v0)(r);
}
