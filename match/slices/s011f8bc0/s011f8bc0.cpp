// Slice s011f8bc0 -- RenderWare D3D9 graphics device caps + global vertex/index state.
// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

typedef unsigned int uint;
typedef unsigned int size_t;

// ---------------------------------------------------------------- globals
extern uint8_t  g_14f7d94[];      // 0x014f7d94  D3D9 vertex-declaration format table (6 dwords)
extern uint8_t  g_15d0840[];      // 0x015d0840  D3D9 sampler/state table (59 dwords)
extern void    (*g_15d092c_fn)(void*);  // 0x015d092c  same global, as a function pointer
extern void*    g_15d0930;        // 0x015d0930  deviceInfoPtr (points at the device-info block)
extern uint32_t g_15d0934;        // 0x015d0934  number of D3D9 streams in use
extern void*    g_16f89d0;        // 0x016f89d0  _m_d3d9Device
extern uint32_t g_16f8afc;        // 0x016f8afc  cached stream source pointer
extern uint8_t  g_16f9138[];      // 0x016f9138  per-stream cache (16 * 3 dwords)
extern void*    g_16f6568;        // 0x016f6568  compile-shader function table (vtable ptr)
extern void*    g_1718648;        // 0x01718648  global vertex-shader declaration
extern uint32_t g_1718670;        // 0x01718670  atexit-registered flag
extern uint32_t g_1718614;        // 0x01718614  cached vertex-shader handle
extern uint32_t g_1718618;        // 0x01718618  cached FVF
extern uint32_t g_1718610;        // 0x01718610  cached primitive count
extern uint32_t g_171861c;        // 0x0171861c
extern uint32_t g_1718620;        // 0x01718620
extern uint32_t g_1719b14;        // _m_softStateUpdated
extern uint32_t g_1719b18;        // _m_primitiveType
extern uint32_t g_16f89d4;        // _m_shader
extern uint32_t g_1718630;        // _m_d3d9Device_ActiveState (graphics rw)
extern void*    g_devInfoPtr;     // (unused)

extern "C" void  __cdecl FUN_011e07ef(void*);        // 0x011e07ef atexit
extern "C" void* __cdecl FUN_011f8b00(void);         // 0x011f8b00 GetNonD3DDeviceInfo
void* __cdecl FUN_011f9250(int*, char*);                // 0x011f9250
extern "C" int   __cdecl sprintf_(char*, const char*, ...); // 0x013cc4a0
__declspec(noinline) uint32_t Arena_IdToObject_imp(void* arena, uint32_t id); // 0x011e2300 (ecx=arena)
#define Arena_IdToObject(arena, id) Arena_IdToObject_imp(arena, id)

extern "C" void* __cdecl memset(void*, int, size_t);  // 0x013cc??? MSVCRT memset

// deviceInfoPtr is the base of the 0x6xxx-byte device-info block at 0x015d0930.
#define DEVINFO ((int*)g_15d0930)

// ---------------------------------------------------------------- 0x011f8bc0
// Fills the per-format vertex-declaration cache (0x428..0x40c in the device-info block)
// by querying the D3D9 device for each vertex-declaration element.
// @ 0x011f8bc0
void f011f8bc0(int* param_1, uint param_2)
{
    extern uint8_t g_14f7d94[];
    uint offset = 0;
    uint count = 0;
    uint* dst;
    uint elem[6];
    int n, i, j;
    uint used, lo, hi;
    uint* scan;
    uint* e;
    uint fmt;
    *(uint*)(param_2 + 0x40c) = 0;
    do {
        fmt = *(uint*)(g_14f7d94 + offset);
        n = (*(int(__thiscall**)(int*, uint, uint))(*param_1 + 0x18))(param_1, *(uint*)(param_2 + 0x148), fmt);
        i = 0;
        dst = (uint*)(count * 0x5c + 0x428 + param_2);
        if (0 < n) {
            do {
                int matched = 0;
                (*(void(__thiscall**)(int*, uint, uint, int, uint*))(*param_1 + 0x1c))
                    (param_1, *(uint*)(param_2 + 0x148), fmt, i, elem);
                if (0xff < count) break;
                j = 0;
                if (0 < (int)count) {
                    scan = (uint*)(param_2 + 0x414);
                    do {
                        if ((((scan[-1] == 1) && (*scan == elem[0])) && (scan[1] == elem[1])) &&
                            (scan[4] == elem[5])) {
                            e = (uint*)(j * 0x5c + 0x410 + param_2);
                            used = e[6];
                            if (used == 0) {
                                e[3] = elem[3];
                                e[4] = elem[3];
                                e[7] = elem[3];
                                e[6] = e[6] + 1;
                            } else if (used < 0x10) {
                                lo = e[3]; hi = e[4];
                                if (lo <= elem[3]) lo = elem[3];
                                e[3] = lo;
                                if (elem[3] <= hi) hi = elem[3];
                                e[4] = hi;
                                e[7 + used] = elem[3];
                                e[6] = e[6] + 1;
                            }
                            matched = 1;
                            break;
                        }
                        j++;
                        scan += 0x17;
                    } while (j < (int)count);
                }
                if (!matched) {
                    uint rec;
                    dst[-6] = 1;
                    dst[-5] = elem[0];
                    dst[-4] = elem[1];
                    dst[-1] = elem[5];
                    rec = *dst;
                    if (rec == 0) {
                        dst[-3] = elem[3];
                        dst[-2] = elem[3];
                        dst[rec + 1] = elem[3];
                        *dst = *dst + 1;
                    } else if (rec < 0x10) {
                        lo = dst[-3]; hi = dst[-2];
                        if (lo <= elem[3]) lo = elem[3];
                        dst[-3] = lo;
                        if (elem[3] <= hi) hi = elem[3];
                        dst[-2] = hi;
                        dst[rec + 1] = elem[3];
                        *dst = *dst + 1;
                    }
                    count++;
                    dst += 0x17;
                }
                i++;
            } while (i < n);
        }
        offset += 4;
        if (0x17 < offset) {
            *(uint*)(param_2 + 0x40c) = count;
            return;
        }
    } while (true);
}

// ---------------------------------------------------------------- 0x011f8d60
// Binds the per-stage sampler state objects, skipping any the device refuses.
// @ 0x011f8d60
void f011f8d60(int* param_1, int param_2)
{
    int* slot = (int*)(param_2 + 0x6010);
    uint i = 0;
    do {
        *slot = 0;
        int obj = *(int*)(g_15d0840 + i);
        if (obj != 0) {
            int* self = param_1;
            int rc = (*(int(__thiscall**)(int*, int, int, int, int, int, int))(*(int*)self + 0x28))
                         (self, *(int*)(param_2 + 0x148), 1, *(int*)(param_2 + 0x408), 0, 3, obj);
            if (rc == 0) *slot = obj;
        }
        i += 4;
        slot++;
    } while (i < 0xec);
}

// ---------------------------------------------------------------- 0x011f8dc0
// Vendor/device-id driven capability overrides for the D3D9 device the game shipped against.
// @ 0x011f8dc0
int f011f8dc0(int param_1)
{
    uint id = *(uint*)(param_1 + 0x134);
    *(uint*)(param_1 + 0x15c) =
        (((*(uint8_t*)(param_1 + 0x2c) & 0x10) == 0) || ((*(uint8_t*)(param_1 + 0x30) & 2) == 0)) ? 1 : 0;
    if (((id & 0xffff0000) == 0x10de0000) && (0xff < (id & 0xffff)))
        *(uint*)(param_1 + 0x164) = 1;

    // Every exit of the original keeps eax = param_1 (the function is declared void but
    // its first eax value is the argument, so equivalence treats eax as a return value).
#define RET   return (int)param_1
#define CLR24  (*(uint*)(param_1 + 0x24) &= 0xffeffeff)
#define CLR25  (*(uint*)(param_1 + 0x24) &= 0xffefffff)
    if (id < 0x10de0021) {
        if (id == 0x10de0020) goto case_10de0028;
        if (0x10025144 < id) {
            if (id < 0x10390331) {
                if (id == 0x10390330) goto case_10024c57;
                if (id < 0x1033002b) {
                    if (id == 0x1033002a) goto case_1033002a;
                    if (id == 0x10025157) { *(uint*)(param_1 + 0xcc) = 0xffff0000; CLR24; RET; }
                    if ((0x102b051f < id) && (id < 0x102b0522)) RET;
                } else if (id == 0x10330046) goto case_1033002a;
            } else {
                if (id == 0x10396326) RET;
                if (id == 0x104a0010) goto case_10024c57;
                if (id == 0x104c3d07) goto case_011f8ff9;
            }
            goto case_10024c45;
        }
        if (id == 0x10025144) { CLR24; RET; }
        if (0x10024c42 < id) {
            switch (id) {
            case 0x10024c44: case 0x10024c47: case 0x10024c49: goto case_10024c44;
            case 0x10024c57: goto case_10024c57;
            default: goto case_10024c45;
            }
        }
        if (id == 0x10024c42) goto case_10024c44;
        if (id < 0x10024745) {
            if (id == 0x10024744) goto case_10024c44;
            if (id == 0x3d00d1) goto case_011f8f97;
            if (id == 0x10024742) goto case_10024c44;
        } else if (id == 0x10024749) {
            goto case_10024c44;
        }
        goto case_10024c45;
    } else {
        if (id < 0x3d3d000a) {
            if (id == 0x3d3d0009) goto case_011f8ff9;
            if (id < 0x121a0002) {
                if (id == 0x121a0001) { *(uint*)(param_1 + 0x98) = 1; *(uint*)(param_1 + 0x14c) = 1; RET; }
                if (id < 0x10de0172) {
                    if (id == 0x10de0171) goto case_10024c57;
                    switch (id) {
                    case 0x10de0028: case 0x10de0029: case 0x10de002a: case 0x10de002b:
                    case 0x10de002c: case 0x10de002d: case 0x10de002e: case 0x10de002f:
                        goto case_10de0028;
                    case 0x10de0100: case 0x10de0101: case 0x10de0102: case 0x10de0103:
                        RET;
                    }
                } else if (id == 0x110b0004) goto case_011f8f97;
            } else if (id < 0x121a0006) {
                if (0x121a0003 < id) RET;
                if (id == 0x121a0002) goto case_10de0028;
                if (id == 0x121a0003) RET;
            } else if ((0x12d20017 < id) && (id < 0x12d2001a)) {
                *(uint*)(param_1 + 0x15c) = 1;
                goto case_011f8ff9;
            }
        } else {
            if (0x53338a21 < id) {
                if (id != 0x53338a22) {
                    if (id != 0x53339102) {
                        if (id == 0x80867800) goto case_011f8f97;
                        goto case_10024c45;
                    }
                    *(uint*)(param_1 + 0x74) = 0;
                    *(uint*)(param_1 + 0x7c) = 0;
                    *(uint*)(param_1 + 0x78) = 0;
                    *(uint*)(param_1 + 0x80) = 0;
                    *(uint*)(param_1 + 0xcc) = 0xffff0000;
                }
                *(uint*)(param_1 + 0x150) = 1;
            case_10de0028:
                *(uint*)(param_1 + 0x14c) = 1;
                RET;
            }
            if (0x53338a1f < id) {
                *(uint*)(param_1 + 0x150) = 1;
                *(uint*)(param_1 + 0x14c) = 1;
                *(uint*)(param_1 + 0x154) = 0;
                RET;
            }
            if (id < 0x5333883e) {
                if (id == 0x5333883d) { case_011f8f97: *(uint*)(param_1 + 0x98) = 1; RET; }
                if (id == 0x3d3d000a) goto case_10de0028;
                if (id == 0x53335631) { *(uint*)(param_1 + 0x98) = 1; RET; }
            } else if (id == 0x53338a01) { *(uint*)(param_1 + 0x98) = 1; RET; }
        }
    case_10024c45:
        if (((0x10025041 <= id) && (id <= 0x100250fe)) ||
            ((0x10025241 <= id) && (id <= 0x100252fe)) ||
            ((0x10025341 <= id) && (id <= 0x100253fe))) goto lab_011f90ef;
        if ((0x1002474d <= id) && (id <= 0x10024751)) {
            *(uint*)(param_1 + 0x98) = 1;
            goto lab_011f90ef;
        }
        if ((0x10024c49 <= id) && (id <= 0x10024c53)) goto case_10024c44;
        RET;
    case_10024c44:
        *(uint*)(param_1 + 0x98) = 1;
    lab_011f90ef:
        CLR25;
        RET;
    }
case_1033002a:
    *(uint*)(param_1 + 0x98) = 1;
    *(uint*)(param_1 + 0x15c) = 1;
    RET;
case_10024c57:
    *(uint*)(param_1 + 0xcc) = 0xffff0000;
    RET;
case_011f8ff9:
    *(uint*)(param_1 + 0x98) = 1;
    *(uint*)(param_1 + 0x160) = 1;
    CLR25;
    RET;
#undef RET
#undef CLR24
#undef CLR25
}

// ---------------------------------------------------------------- 0x011f9250
// PDB: rw::graphics::DevCapsManager::GetD3DDeviceCaps
// @ 0x011f9250 FUN_011f9250
__declspec(noinline) void* __cdecl FUN_011f9250(int* param_1, char* param_2)
{
    struct D3DCAPS9 { uint32_t pad[0x100]; };
    struct AdapterId {
        uint32_t pad0[0xd];
        char desc[0x200];
        uint32_t pad1;
        uint32_t VendorId;
        uint32_t DeviceId;
        uint32_t Revision;
        uint32_t SubSysId;
        uint32_t pad2;
    };
    struct CreationParams {
        uint32_t pad0[0x10];
        void* hFocusWindow;
        uint32_t BehaviorFlags;
        uint32_t pad1[0x27];
    };
    int* info = (int*)g_15d0930;
    for (int i = 0x183f; i != 0; i--) *info++ = 0;
    *(uint32_t*)((uint8_t*)g_15d0930 + 0x130) = 0;
    *(uint32_t*)((uint8_t*)g_15d0930 + 0x148) = 0;
    if (param_1 == 0) {        if (param_2 != 0) sprintf_(param_2, "pDevice is NULL\n");
        return 0;
    }
    void* d3d = 0;
    int hr = (*(int(__thiscall**)(int*, void**))(*param_1 + 0x18))(param_1, &d3d);
    if (hr != 0) {
        if (param_2 != 0) sprintf_(param_2, "IDirect3DDevice9_GetDirect3D failed: err = 0x%x\n", hr);
        return 0;
    }
    (*(void(__thiscall**)(void*))(*(uint32_t*)d3d + 8))(d3d);
    CreationParams cp;
    hr = (*(int(__thiscall**)(int*, CreationParams*))(*param_1 + 0x24))(param_1, &cp);
    if (hr != 0) {
        if (param_2 != 0) sprintf_(param_2, "IDirect3DDevice9_GetCreationParameters failed: err = 0x%x\n", hr);
        return 0;
    }
    uint8_t* base = (uint8_t*)g_15d0930;
    *(void**)(base + 0x148) = d3d;
    AdapterId ai;
    hr = (*(int(__thiscall**)(void*, void*, int, AdapterId*))(*(uint32_t*)d3d + 0x14))
             (d3d, *(void**)(base + 0x148), 0, &ai);
    if (hr != 0) {
        if (param_2 != 0) sprintf_(param_2, "IDirect3D9_GetAdapterIdentifier failed: err = 0x%x\n", hr);
        return 0;
    }
    *(uint32_t*)(base + 0x138) = ai.DeviceId;
    *(uint32_t*)(base + 0x13c) = ai.Revision;
    *(uint32_t*)(base + 0x134) = (ai.Revision & 0xffff) | (ai.DeviceId << 0x10);
    *(uint32_t*)(base + 0x140) = ai.SubSysId;
    *(uint32_t*)(base + 0x144) = ai.pad2;
    char* src = ai.desc;
    char* dst = (char*)(base + 0x1fc);
    char c;
    do { c = *src++; *dst++ = c; } while (c != 0);
    f011f8bc0((int*)d3d, (uint)base);
    (*(void(__thiscall**)(int*, int, uint8_t*))(*param_1 + 0x20))((int*)param_1, 0, base + 0x3fc);
    f011f8d60((int*)param_1, (int)base);
    hr = (*(int(__thiscall**)(int*, uint8_t*))(*param_1 + 0x1c))(param_1, base);
    if (hr == 0) {
        *(uint32_t*)(base + 0x130) = 1;
        return base;
    }
    if (param_2 != 0) sprintf_(param_2, "IDirect3DDevice9_GetDeviceCaps failed: err = 0x%x\n", hr);
    return 0;
}

// ---------------------------------------------------------------- 0x011f94a0
// PDB: rw::graphics::DevCapsManager::GenerateDevCaps
// @ 0x011f94a0
uint32_t f011f94a0(uint32_t param_1)
{
    int rc = (int)FUN_011f9250((int*)g_16f89d0, (char*)param_1);
    if (rc == 0) {
        uint8_t* p = (uint8_t*)g_15d0930;
        for (int i = 0x183f; i != 0; i--) *(uint32_t*)p = 0, p += 4;
        return 0;
    }
    FUN_011f8b00();
    if (g_15d092c_fn != 0) {
        g_15d092c_fn(g_15d0930);
    }
    return 1;
}

// ---------------------------------------------------------------- 0x011f94f0
// Resolves arena ids back to objects for a device-info block.
// @ 0x011f94f0
uint32_t f011f94f0(uint32_t param_1, uint32_t param_2)
{
    uint32_t* arena = *(uint32_t**)(param_2 + 0x78);
    *(uint32_t*)(param_1 + 8) = Arena_IdToObject(arena, *(uint32_t*)(param_1 + 8));
    uint32_t i = 0;
    uint32_t count = *(uint32_t*)(param_1 + 0x10);
    if (0 < (int)count) {
        uint32_t* p = (uint32_t*)(param_1 + 0x24);
        do {
            *p = Arena_IdToObject(arena, *p);
            count = *(uint32_t*)(param_1 + 0x10);
            i++;
            p++;
        } while (i < count);
    }
    return 1;
}

// ---------------------------------------------------------------- 0x011f9560
// Resets every cached D3D9 stream source.
// @ 0x011f9560
typedef int (__thiscall *PFN_D3D9STATE)(void*, int, int, int, int);
void f011f9560(void)
{
    g_16f8afc = 0;
    void* dev = g_16f89d0;
    (*(void(__thiscall**)(void*, int))(*(uint32_t*)dev + 0x1a0))(dev, 0);
    int n = 0;
    for (uint i = 0; i < 0x30; i += 0xc) {
        dev = g_16f89d0;
        *(uint32_t*)(g_16f9138 + i) = 0;
        *(uint32_t*)(g_16f9138 + i + 4) = 0;
        *(uint32_t*)(g_16f9138 + i + 8) = 0;
        (*(PFN_D3D9STATE*)(*(uint32_t*)dev + 0x190))(dev, n, 0, 0, 0);
        n++;
    }
}

// ---------------------------------------------------------------- 0x011f95c0
// Primitive count -> vertex count for the current primitive type.
// (Modelled as a member function of a dummy class so MSVC emits __thiscall.)
struct SASDesc {
    int method(int prim);
    uint32_t f9670(int a, int b);
    void f96b0(int a);
    void f96e0(int a);
    void f9ae0(int* out, int a);
};
// @ 0x011f95c0
int SASDesc::method(int param_2)
{
    int param_1 = (int)this;
    int iVar1 = *(int*)(param_1 + 8);
    if (iVar1 == 0) {
        if (param_2 != -1) {
            uint32_t u = *(uint32_t*)(*(int*)(param_1 + 0x24) + 0xc);
            switch (param_2) {
            case 1: return u;
            case 2: return u >> 1;
            case 3: return u - 1;
            case 4: { uint32_t q = (uint32_t)(((uint64_t)u * 0xaaaaaaab) >> 32); return q >> 1; }
            case 5: case 6: return u - 2;
            default: return 0;
            }
        }
    } else if ((param_2 != -1) || ((param_2 = *(int*)(iVar1 + 0x14)) != -1)) {
        uint32_t u = *(uint32_t*)(param_1 + 0x18);
        if (u == 0) u = *(uint32_t*)(iVar1 + 8);
        switch (param_2) {
        case 1: case 2: return u >> 1;
        case 3: return u - 1;
        case 4: { uint32_t q = (uint32_t)(((uint64_t)u * 0xaaaaaaab) >> 32); return q >> 1; }
        case 5: case 6: return u - 2;
        default: return 0;
        }
    }
    return 0;
}

// ---------------------------------------------------------------- 0x011f9ae0
// @ 0x011f9ae0
void SASDesc::f9ae0(int* param_2, int param_3)
{
    int param_1 = (int)this;
    int* pp = *(int**)(param_1 + 4);
    int iVar1 = *pp;
    param_2[1] = *(uint8_t*)(iVar1 + 0xf);
    int iVar2 = *(int*)param_1;
    *param_2 = iVar2;
    *param_2 = *(uint16_t*)(iVar1 + 0x1a + param_3 * 0xc) + iVar2;
}

// ---------------------------------------------------------------- 0x011f9710
// Pushes the cached stream/FVF state to the D3D9 device.
// @ 0x011f9710
void f011f9710(int param_1)
{
    f011f9560();
    int rc = (*(int(__cdecl**)(int))(*(uint32_t*)g_16f6568 + 0x14))(param_1);
    if (rc == 0) return;
    g_1719b14 = 0;
    if (*(int*)(param_1 + 0x10) == 1) {
        g_1718614 = *(uint32_t*)(*(int*)(param_1 + 0x24) + 8);
        g_1718618 = g_1718614;
    }
    uint32_t stream = 0;
    if (*(int*)(param_1 + 0x10) != 0) {
        int* p = (int*)(param_1 + 0x24);
        uint8_t* cache = (uint8_t*)(g_16f9138 + 4);
        do {
            int* src = (int*)*p;
            int span = 0;      // iStack_c
            uint32_t stride = 0; // uVar7
            int spanBytes = 0;   // iVar3
            if (src != 0) {
                int caps;
                span = src[1];
                stride = *(uint8_t*)(*src + 0xf);
                caps = (*(int(__thiscall**)(int))(*(uint32_t*)g_16f6568 + 0x18))((int)param_1);
                if ((*(uint8_t*)(caps + 0xd4) & 1) == 0) {
                    spanBytes = 0;
                } else {
                    spanBytes = src[2] * (int)stride;
                    g_1718614 = 0;
                    g_1718618 = 0;
                }
            }
            if (((*(uint32_t*)(cache - 4) != (uint32_t)span) ||
                 (*(uint32_t*)(cache) != (uint32_t)spanBytes)) ||
                (*(uint32_t*)(cache + 4) != stride)) {
                int hr = (*(int(__thiscall**)(void*, uint32_t, int, int, uint32_t))(*(uint32_t*)g_16f89d0 + 0x190))
                             (g_16f89d0, stream, span, spanBytes, stride);
                if (hr < 0) return;
                *(uint32_t*)(cache - 4) = (uint32_t)span;
                *(uint32_t*)(cache) = (uint32_t)spanBytes;
                *(uint32_t*)(cache + 4) = stride;
            }
            stream++;
            p++;
            cache += 0xc;
        } while (stream < *(uint32_t*)(param_1 + 0x10));
    }
    if (stream < g_15d0934) {
        uint8_t* p = (uint8_t*)(g_16f9138 + 4 + stream * 0xc);
        uint32_t n = g_15d0934;
        do {
            int hr = (*(int(__thiscall**)(void*, uint32_t, int, int, int))(*(uint32_t*)g_16f89d0 + 0x190))
                         (g_16f89d0, stream, 0, 0, 0);
            n = g_15d0934;
            if (hr < 0) return;
            *(uint32_t*)(p - 4) = 0;
            *(uint32_t*)(p) = 0;
            *(uint32_t*)(p + 4) = 0;
            stream++;
            p += 0xc;
        } while (stream < n);
        g_15d0934 = *(uint32_t*)(param_1 + 0x10);
    }
    uint32_t prim = g_1719b18;
    if (*(int*)(param_1 + 4) == g_1719b18) {
        g_1718610 = *(uint32_t*)(param_1 + 0xc);
    } else {
        g_1718610 = (*(int(__cdecl**)(uint32_t))(*(uint32_t*)g_16f6568))(g_1719b18);
    }
    int* tbl = *(int**)(param_1 + 8);
    if (tbl == 0) {
        (*(void(__thiscall**)(void*, uint32_t, uint32_t, uint32_t))(*(uint32_t*)g_16f89d0 + 0x144))
            (g_16f89d0, prim, g_1718618, g_1718610);
    } else {
        int id = *tbl;
        uint32_t cached = g_16f8afc;
        if (id == g_16f8afc) {
        use_cached:
            g_16f8afc = cached;
            (*(int(__thiscall**)(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))
                 (*(uint32_t*)g_16f89d0 + 0x148))
                (g_16f89d0, prim, g_1718614, *(uint32_t*)(param_1 + 0x1c),
                 *(uint32_t*)(param_1 + 0x20), tbl[1] + *(int*)(param_1 + 0x14), g_1718610);
            return;
        }
        int hr = (*(int(__thiscall**)(void*, int))(*(uint32_t*)g_16f89d0 + 0x1a0))(g_16f89d0, id);
        cached = id;
        if (-1 < hr) goto use_cached;
    }
}

// ---------------------------------------------------------------- 0x011f9920
// Records the vertex-shader declaration / stream layout for the current draw.
// @ 0x011f9920
int f011f9920(int param_1, uint32_t param_2, uint32_t param_3, int param_4)
{
    if ((g_1718670 & 1) == 0) {
        g_1718670 |= 1;
        FUN_011e07ef((void*)0x013cb960);
    }
    int rc = (*(int(__cdecl**)(void*))(*(uint32_t*)g_16f6568 + 0x14))(&g_1718648);
    if (rc == 0) return -0x7fffbffb;
    g_1719b14 = 0;
    if ((*(uint32_t*)(g_16f9138) != (uint32_t)param_1) ||
        (*(uint32_t*)(g_16f9138 + 4) != 0) ||
        (*(uint32_t*)(g_16f9138 + 8) != (uint32_t)param_4)) {
        int hr = (*(int(__thiscall**)(void*, int, int, int, int))(*(uint32_t*)g_16f89d0 + 0x190))
                     (g_16f89d0, 0, param_1, 0, param_4);
        if (hr < 0) return hr;
        *(uint32_t*)(g_16f9138) = param_1;
        *(uint32_t*)(g_16f9138 + 4) = 0;
        *(uint32_t*)(g_16f9138 + 8) = param_4;
    }
    uint32_t i = 1;
    uint32_t n = g_15d0934;
    if (1 < g_15d0934) {
        uint8_t* p = (uint8_t*)(g_16f9138 + 0xc);
        do {
            int hr = (*(int(__thiscall**)(void*, uint32_t, int, int, int))(*(uint32_t*)g_16f89d0 + 0x190))
                         (g_16f89d0, i, 0, 0, 0);
            n = g_15d0934;
            if (hr < 0) return hr;
            *(uint32_t*)(p) = 0;
            *(uint32_t*)(p + 4) = 0;
            *(uint32_t*)(p + 8) = 0;
            i++;
            p += 0xc;
        } while (i < n);
        g_15d0934 = 1;
    }
    switch (g_1719b18) {
    case 1: break;
    case 2: param_3 >>= 1; break;
    case 3: param_3 -= 1; break;
    case 4: param_3 = param_3 / 3; break;
    case 5: case 6: param_3 -= 2; break;
    default: return -0x7fffbffb;
    }
    g_1718618 = param_2;
    g_1718610 = param_3;
    return (*(int(__thiscall**)(void*, uint32_t, uint32_t, uint32_t))(*(uint32_t*)g_16f89d0 + 0x144))
               (g_16f89d0, g_1719b18, param_2, param_3);
}

// ---------------------------------------------------------------- 0x011f9670
// @ 0x011f9670
uint32_t SASDesc::f9670(int param_2, int param_3)
{
    int param_1 = (int)this;
    *(int*)(param_1 + 0x24 + param_2 * 4) = param_3;
    *(uint32_t*)(param_1 + 0xc) = method(*(int*)(param_1 + 4));
    uint32_t u = *(uint32_t*)(param_3 + 0xc);
    uint32_t cur = *(uint32_t*)(param_1 + 0x20);
    if ((cur == 0) || (cur > u)) {
        *(uint32_t*)(param_1 + 0x20) = u;
    }
    return 1;
}

// ---------------------------------------------------------------- 0x011f96b0
// @ 0x011f96b0
void SASDesc::f96b0(int param_2)
{
    int param_1 = (int)this;
    *(int*)(param_1 + 0x18) = param_2;
    if (*(int*)(param_1 + 8) != 0) {
        *(uint32_t*)(param_1 + 4) = *(uint32_t*)(*(int*)(param_1 + 8) + 0x14);
    }
    *(uint32_t*)(param_1 + 0xc) = method(*(int*)(param_1 + 4));
}

// ---------------------------------------------------------------- 0x011f96e0
// @ 0x011f96e0
void SASDesc::f96e0(int param_2)
{
    int param_1 = (int)this;
    *(int*)(param_1 + 8) = param_2;
    if (param_2 != 0) {
        *(uint32_t*)(param_1 + 4) = *(uint32_t*)(param_2 + 0x14);
    }
    *(uint32_t*)(param_1 + 0xc) = method(*(int*)(param_1 + 4));
}

// ---------------------------------------------------------------- 0x011f9a90
// Allocates/initialises a vertex-declaration descriptor (unrolled by the original
// compiler; left as a faithful loop -> non-exact).
// @ 0x011f9a90
int* f011f9a90(uint32_t* param_1, int param_2)
{
    int* p = (int*)*param_1;
    *p = param_2 * 4 + 0x24;
    p[2] = 0;
    p[1] = -1;
    p[3] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0;
    p[4] = param_2;
    for (int i = 0; i < param_2; i++) p[9 + i] = 0;
    return p;
}

