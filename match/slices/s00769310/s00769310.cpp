// Slice s00769310: SP::cGraphicsResourceFactory game-model reader + dispatch
// helpers. /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>
#include <string.h>

extern "C" {
void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  __cdecl Dealloc(void* p);                                             // 0xf47380
void  __cdecl FUN_007006d0(void* p);                                        // 0x7006d0
char  __cdecl FUN_007638a0(void* a, void* b, void* c, void* d);             // 0x7638a0
char  __cdecl FUN_00767170(void* a, void* b, void* c);                      // 0x767170
char  __cdecl ReadMaterialList(void* a, void* b, void* c);                  // 0x767c80
char  __cdecl FUN_00764ce0(void* a, void* b, void* c);                      // 0x764ce0
char  __cdecl FUN_007637d0(void* a, void* b, int c, void* d);               // 0x7637d0
char  __cdecl ReadResourcePCAWeights(void* a, void* b, void* c);            // 0x763950
char  __cdecl FUN_00769cf0(void* a, void* b, void* c);                      // 0x769cf0
char  __cdecl FUN_00769310b(void* a, void* b, void* c, void* d);            // 0x769310
void* __cdecl FUN_0093b530(int a, int b, void* c);                          // 0x93b530
}

// ---- pieces of the 0x769310 game-model reader -----------------------------
extern "C" {
char  __cdecl FUN_0093a6c0(void* stream, void* dst, uint32_t n);             // 0x93a6c0
char  __cdecl FUN_0093a890(void* stream, uint32_t size, uint32_t count);     // 0x93a890
char  __cdecl FUN_0093a780(void* stream, void* dst, uint32_t n, uint32_t z); // 0x93a780
void  __fastcall FUN_007658f0(void* vec, int, uint32_t n);                   // 0x7658f0
void* __cdecl FUN_00762c60(void* desc, int a, uint32_t b, int c, void* vb, uint32_t p3); // 0x762c60
void* __fastcall FUN_011f4f20(void* vb, int, uint32_t mode, uint32_t* out);  // 0x11f4f20
void* __fastcall FUN_011f4fd0(void* vb, int, uint32_t* out);                 // 0x11f4fd0
void  __cdecl FUN_00762a30(void* vb);                                        // 0x762a30
void  __fastcall FUN_00700640(void* vec, int, void** elem);                  // 0x700640
void* __cdecl FUN_00761650(uint32_t n);                                      // 0x761650
void  __fastcall FUN_011f3220(void* vb, int);                                // 0x11f3220
void  __cdecl FUN_00761130(void* vb);                                        // 0x761130
void  __fastcall FUN_006ec4a0(void* vec, int, void** end, void** elem);      // 0x6ec4a0
void* __cdecl FUN_00762b70(void* vb, uint32_t size, int z, uint32_t p3);     // 0x762b70
void* __fastcall FUN_011f3620(void* vb, int, uint32_t flags, uint32_t a, uint32_t b); // 0x11f3620
void  __fastcall FUN_011f36a0(void* vb, int);                                // 0x11f36a0
void  __cdecl FUN_00762a00(void* vb);                                        // 0x762a00
void* __cdecl FUN_00761840(uint32_t n);                                      // 0x761840
void  __fastcall FUN_011f9670(void* m, int, uint32_t a, void* b);            // 0x11f9670
void  __fastcall FUN_011f96e0(void* m, int, void* a);                        // 0x11f96e0
void  __fastcall FUN_011f96b0(void* m, int, uint32_t a);                     // 0x11f96b0
void  __fastcall FUN_00768240(void* vec, int, uint32_t n);                   // 0x768240
void* __cdecl FUN_0067dd70();                                                // 0x67dd70
void  __fastcall FUN_00758ee0(void* vec, int, uint32_t n);                   // 0x758ee0
void  __fastcall FUN_00765980(void* vec, int, uint32_t n);                   // 0x765980
void  __fastcall FUN_00d018d0(void* vec, int, void* b, void* e);             // 0xd018d0
void  __fastcall FUN_005402c0(void* vec, int, void** pair);                  // 0x5402c0
char  __fastcall FUN_00768650(void* self, int, void* stream, void* obj, uint32_t p4); // 0x768650
void* __cdecl FUN_0067dcd0();                                                // 0x67dcd0
void  __cdecl FUN_006ac040(int a, void* b);                                  // 0x6ac040
void  __fastcall FUN_004535d0(void* slot, int, void* o);                     // 0x4535d0
void  __fastcall FUN_0041d8b0(void* slot, int, void* o);                     // 0x41d8b0
void  __fastcall FUN_0041ef20(void* vec, int, void** o);                     // 0x41ef20
void  __fastcall FUN_00472520(void* slot, int);                              // 0x472520
void* __fastcall FUN_0077d1d0(void* p, int);                                 // 0x77d1d0
char  __fastcall FUN_007679f0(void* self, int, void* stream, void* info, uint32_t p4); // 0x7679f0
extern unsigned char DAT_015d07a8[];                                         // 0x15d07a8
}

struct cGameModelReader {
    char ReadResourceGameModel(void* stream, void* obj, uint32_t a3, uint32_t a4);
};

// A vector with a 0x80-byte inline buffer (eastl::vector<T, sp_vector_allocator<T>> as used by the
// material-name list). Only the layout matters: the real helpers at 0x768240 / 0x767760 manage it.
struct MatNamesVec { uint32_t raw[0x98 / 4]; };

static void FreeMatNames(MatNamesVec& v) {
    uint32_t* begin = *(uint32_t**)&v;
    uint32_t* inl = *(uint32_t**)((char*)&v + 0x10);
    if (begin != 0 && begin != inl)
        Dealloc(begin);
}

static void ReleaseVt(void* p) {
    if (!p)
        return;
    void** vt = *(void***)p;
    ((void(__thiscall*)(void*))vt[1])(p);
}

static void ReleaseLocal(void* p) {
    if (!p)
        return;
    long* rc = (long*)((char*)p + 4);
    if (_InterlockedDecrement(rc) == 0) {
        _InterlockedExchange(rc, 1);
        (*(void(__thiscall**)(void*, int))*(void**)p)(p, 1);
    }
}

// ===========================================================================
// @ 0x00769310  cGameModelReader::ReadResourceGameModel
// ===========================================================================
char cGameModelReader::ReadResourceGameModel(void* stream, void* obj, uint32_t a3, uint32_t a4)
{
    char* o = (char*)obj;
    uint32_t f4 = 0;                                   // reused: mesh/material count
    if (!FUN_0093a6c0(stream, &f4, 4))
        return 0;
    if (!FUN_0093a6c0(stream, o + 0x11c, 0x18))
        return 0;
    if (!FUN_0093a6c0(stream, o + 0x134, 4))
        return 0;

    // ---- vertex buffers ---------------------------------------------------
    uint32_t d4 = 0;
    if (!FUN_0093a6c0(stream, &d4, 4))
        return 0;
    if (!FUN_0093a890(stream, d4, 1))
        return 0;
    FUN_007658f0(o + 0x40, 0, d4);
    for (uint32_t i = 0; i < d4; ++i) {
        uint32_t id = 0, count = 0, fmt = 0, bytes = 0;
        if (!FUN_0093a6c0(stream, &id, 4))
            return 0;
        if (!FUN_0093a6c0(stream, &count, 4))
            return 0;
        if (!FUN_0093a6c0(stream, &fmt, 4))
            return 0;
        if (!FUN_0093a6c0(stream, &bytes, 4))
            return 0;
        if ((fmt != 0x10 && fmt != 0x20) || bytes != (uint32_t)(fmt * count) >> 3)
            return 0;
        if (!FUN_0093a890(stream, bytes, 1))
            return 0;
        void* vb = FUN_00762c60(DAT_015d07a8 + ((fmt >> 4) * 8), 1, count, 8,
                                (void*)id, a3);
        uint32_t lock[3] = { 0, 0, 0 };
        if (!FUN_011f4f20(vb, 0, 2, lock))
            return 0;
        if (!FUN_0093a6c0(stream, (void*)lock[0], bytes)) {
            FUN_011f4fd0(vb, 0, lock);
            FUN_00762a30(vb);
            return 0;
        }
        FUN_011f4fd0(vb, 0, lock);
        FUN_00700640(o + 0x40, 0, &vb);
    }

    // ---- vertex descriptors ----------------------------------------------
    uint32_t dc = 0;
    if (!FUN_0093a6c0(stream, &dc, 4))
        return 0;
    if (!FUN_0093a890(stream, dc, 1))
        return 0;
    FUN_007658f0(o + 0x90, 0, dc);
    for (uint32_t i = 0; i < dc; ++i) {
        uint32_t n = 0;
        if (!FUN_0093a6c0(stream, &n, 4))
            return 0;
        void* vd = FUN_00761650(n);
        *(uint8_t*)((char*)vd + 0xe) |= 2;
        void* slot = vd;
        for (uint32_t j = 0; j < n; ++j) {
            if (!FUN_0093a6c0(stream, (char*)vd + 0x18 + j * 0xc, 0xc)) {
                FUN_011f3220(vd, 0);
                FUN_00761130(vd);
                return 0;
            }
        }
        FUN_011f3220(vd, 0);
        uint32_t* end = *(uint32_t**)(o + 0x94);
        if (end < *(uint32_t**)(o + 0x98)) {
            *(uint32_t**)(o + 0x94) = end + 1;
            if (end)
                *end = (uint32_t)vd;
        } else {
            FUN_006ec4a0(o + 0x90, 0, (void**)end, &slot);
        }
    }

    // ---- locked vertex ranges --------------------------------------------
    uint32_t d8 = 0;
    if (!FUN_0093a6c0(stream, &d8, 4))
        return 0;
    if (!FUN_0093a890(stream, d8, 1))
        return 0;
    FUN_007658f0(o + 0x68, 0, d8);
    for (uint32_t i = 0; i < d8; ++i) {
        uint32_t idx = 0, size = 0, off = 0;
        if (!FUN_0093a6c0(stream, &idx, 4))
            return 0;
        if (!FUN_0093a6c0(stream, &size, 4))
            return 0;
        if (!FUN_0093a6c0(stream, &off, 4))
            return 0;
        if ((uint32_t)(*(uint32_t**)(o + 0x94) - *(uint32_t**)(o + 0x90)) >> 2 <= idx)
            return 0;
        void* vb = (void*)*(uint32_t*)(*(uint32_t*)(o + 0x90) + idx * 4);
        vb = FUN_00762b70(vb, size, 0, a3);
        uint8_t stride = *(uint8_t*)((char*)*(void**)vb + 0xf);
        uint32_t base = *(uint32_t*)((char*)vb + 0xc);
        uint32_t num = *(uint32_t*)((char*)vb + 8);
        void* locked = FUN_011f3620(vb, 0, 2, stride * num, stride * base);
        if ((uint32_t)stride * size != off || !FUN_0093a6c0(stream, locked, off)) {
            FUN_011f36a0(vb, 0);
            FUN_00762a00(vb);
            return 0;
        }
        FUN_011f36a0(vb, 0);
        FUN_00700640(o + 0x68, 0, &vb);
    }

    // ---- mesh list --------------------------------------------------------
    if (!FUN_0093a890(stream, f4, 1))
        return 0;
    FUN_007658f0(o + 0x18, 0, f4);
    for (uint32_t i = 0; i < f4; ++i) {
        uint32_t mi = 0, vi = 0;
        if (!FUN_0093a6c0(stream, &mi, 4))
            return 0;
        if (!FUN_0093a6c0(stream, &vi, 4))
            return 0;
        if ((uint32_t)(*(uint32_t**)(o + 0x44) - *(uint32_t**)(o + 0x40)) >> 2 <= mi)
            return 0;
        if ((uint32_t)(*(uint32_t**)(o + 0x6c) - *(uint32_t**)(o + 0x68)) >> 2 <= vi)
            return 0;
        uint32_t vb = *(uint32_t*)(*(uint32_t*)(o + 0x68) + vi * 4);
        uint32_t mr = *(uint32_t*)(*(uint32_t*)(o + 0x40) + mi * 4);
        void* mesh = FUN_00761840(1);
        FUN_011f9670(mesh, 0, 0, (void*)vb);
        FUN_011f96e0(mesh, 0, (void*)mr);
        FUN_011f96b0(mesh, 0, *(uint32_t*)(mr + 8));
        FUN_00700640(o + 0x18, 0, &mesh);
    }

    // ---- material names ---------------------------------------------------
    MatNamesVec names;
    FUN_00768240(&names, 0, f4);
    uint32_t* nbegin = *(uint32_t**)&names;
    if (!FUN_0093a6c0(stream, nbegin, f4 * 4)) {
        FreeMatNames(names);
        return 0;
    }
    void* mgr = FUN_0067dd70();
    void** mvt = *(void***)mgr;
    int res = ((int(__thiscall*)(void*, void*, uint32_t, uint32_t*, int, uint32_t))mvt[0x48 / 4])
                  (mgr, stream, f4, nbegin, 0, a3);
    if (res < 0) {
        FreeMatNames(names);
        return 0;
    }
    FUN_00758ee0(o + 0xb8, 0, f4);
    mgr = FUN_0067dd70();
    mvt = *(void***)mgr;
    ((void(__thiscall*)(void*, uint32_t, uint32_t*, uint32_t))mvt[0x2c / 4])
        (mgr, f4, nbegin, *(uint32_t*)(o + 0xb8));

    // ---- material instances ----------------------------------------------
    uint32_t nMat = 0;
    if (!FUN_0093a6c0(stream, &nMat, 4)) {
        FreeMatNames(names);
        return 0;
    }
    for (uint32_t i = 0; i < nMat; ++i) {
        uint32_t flag = 1;
        if (a4 > 8 && !FUN_0093a780(stream, &flag, 1, 0)) {
            FreeMatNames(names);
            return 0;
        }
        void* info = 0;
        if (flag) {
            void* mem = Alloc6(0x1c, "RenderAsset/GameModel_MatInfo", 0, 0, 0, 0);
            void* ob = mem ? FUN_0077d1d0(mem, 0) : 0;
            FUN_0041d8b0(&info, 0, ob);
            if (!FUN_007679f0(this, 0, stream, info, a4)) {
                FUN_00472520(&info, 0);
                FreeMatNames(names);
                return 0;
            }
        }
        FUN_0041ef20(o + 0xf4, 0, &info);
        ReleaseLocal(info);
    }

    // ---- geometry batch table --------------------------------------------
    uint32_t nBatch = 0;
    if (!FUN_0093a6c0(stream, &nBatch, 4)) {
        FreeMatNames(names);
        return 0;
    }
    if (!FUN_0093a890(stream, 8, nBatch)) {
        FreeMatNames(names);
        return 0;
    }
    FUN_00d018d0(o + 0xe0, 0, *(void**)(o + 0xe0), *(void**)(o + 0xe4));
    FUN_00765980(o + 0xe0, 0, nBatch);
    for (uint32_t i = 0; i < nBatch; ++i) {
        uint32_t pair[2] = { 0, 0 };
        if (!FUN_0093a6c0(stream, &pair[0], 4) || !FUN_0093a6c0(stream, &pair[1], 4)) {
            FreeMatNames(names);
            return 0;
        }
        FUN_005402c0(o + 0xe0, 0, (void**)pair);
    }
    if (!FUN_00768650(this, 0, stream, obj, a4)) {
        FreeMatNames(names);
        return 0;
    }

    // ---- EA resource header ----------------------------------------------
    uint32_t hdr[3] = { 0, 0, 0 };
    if (!FUN_0093a6c0(stream, hdr, 0xc)) {
        FreeMatNames(names);
        return 0;
    }
    if ((int)hdr[1] != -1) {
        void* resObj = 0;
        void* rm = FUN_0067dcd0();
        void** rvt = *(void***)rm;
        ((void(__thiscall*)(void*, void*, void**, int, int, int, int))rvt[3])
            (rm, hdr, &resObj, 0, 0, 0, 0);
        void* hit = 0;
        if (resObj) {
            void** svt = *(void***)resObj;
            hit = (void*)((int(__thiscall*)(void*, uint32_t))svt[3])(resObj, 0x2f4e681b);
        }
        if (!resObj || !hit) {
            ReleaseVt(resObj);
            FreeMatNames(names);
            return 0;
        }
        FUN_006ac040(2, hit);
        FUN_004535d0(o + 0x13c, 0, hit);
        ReleaseVt(resObj);
    }
    void* tail = *(void**)(o + 0x138);
    if (tail) {
        *(void**)(o + 0x138) = 0;
        void** tvt = *(void***)tail;
        ((void(__thiscall*)(void*))tvt[1])(tail);
    }
    FreeMatNames(names);
    return 1;
}

// ===========================================================================
// @ 0x00769cb0  forward to the game-model reader
// ===========================================================================
struct M69310 { char Meth(int a, int b, int c); };
char __fastcall Func69cb0(void* self, int, int unused) {
    (void)unused;
    char* s = (char*)self;
    void* obj = *(void**)(s + 0x10);
    int uVar5 = *(int*)(s + 0x2c);
    int a14 = *(int*)(s + 0x14);
    int a28 = *(int*)(s + 0x28);
    int ebp = *(int*)(s + 0xc);
    int v = ((int(__thiscall**)(void*, int))*(void***)obj)[4](obj, uVar5);
    char c = ((M69310*)ebp)->Meth(a28, a14, v);
    if (c)
        *(char*)(s + 0x334) = 1;
    return c;
}

// ===========================================================================
// @ 0x00769cf0  stream vcall header check, then two-phase read
// ===========================================================================
char __fastcall Func69cf0(void* self, int, void* stream, void* a2, void* a3) {
    (void)self;
    int local;
    if (((int(__thiscall**)(void*, int*, int))*(void***)stream)[12](stream, &local, 4) != 4)
        return 0;
    if ((uint32_t)(local - 8) > 1)
        return 0;
    FUN_007006d0(a2);
    if (!FUN_007638a0(stream, a3, a2, (void*)local))
        return 0;
    return FUN_00769310b(stream, a3, a2, (void*)local);
}

// ===========================================================================
// @ 0x00769d80  SP::cGraphicsResourceFactory::ReadResourceFromStream
// ===========================================================================
// The reader is a cGraphicsResourceFactory member: the original takes `this` in ecx and four
// stack arguments (it ends with `ret 0x10`), and every dispatch target is a __thiscall on the
// same factory (ecx = the factory, three stack arguments).
struct cGraphicsResourceFactory {
    char ReadResourceFromStream(int* src, void* a2, int* obj, uint32_t kind);

    char ReadPCAWeights(void* holder, void* a2, void* obj);            // 0x763950
    char ReadVia69cf0(void* holder, void* a2, void* obj);              // 0x769cf0
    char ReadMaterialList_(void* holder, void* a2, void* obj);         // 0x767c80
    char ReadVia64ce0(void* holder, void* a2, void* obj);              // 0x764ce0
    char ReadVia637d0(void* holder, void* a2, int four, void* obj);    // 0x7637d0
    char ReadVia67170(void* holder, void* a2, void* obj);              // 0x767170
};

char cGraphicsResourceFactory::ReadResourceFromStream(int* src, void* a2, int* obj, uint32_t kind) {
    int* holder = 0;
    int* arg = src;
    if (src && ((int(__thiscall**)(int*))*(void***)src)[3](src) == 0x34722300) {
        void* p = Alloc6(0x34, "Graphics", 0, 0, 0, 0);
        if (p)
            p = FUN_0093b530(0x2000, 0, src);
        if (p) {
            ((void(__thiscall**)(void*))*(void***)p)[1](p);
            holder = (int*)p;
        }
        arg = holder;
    }
    uint32_t type = *(uint32_t*)((char*)obj + 4);
    char r = 0;
    bool handled = true;
    if (type <= 0x2cb4f2f) {
        if (type == 0x2cb4f2f)
            r = ReadPCAWeights(arg, a2, obj);
        else if (type == 0xe6bce5)
            r = ReadVia69cf0(arg, a2, obj);
        else if (type == 0x1c135da)
            r = ReadMaterialList_(arg, a2, obj);
        else
            handled = false;
    } else if (type == 0x2f4e681b) {
        r = ReadVia64ce0(arg, a2, obj);
    } else if (type == 0x2f4e681c && kind <= 0x2f7d0004) {
        if (kind == 0x2f7d0004)
            r = ReadVia637d0(arg, a2, 4, obj);
        else if (kind != 0x2f4e681b && kind == 0x2f4e681c)
            r = ReadVia67170(arg, a2, obj);
        else
            handled = false;
    } else {
        handled = false;
    }
    if (!handled) {
        if (holder)
            ((void(__thiscall**)(int*))*(void***)holder)[2](holder);
        return 0;
    }
    if (holder)
        ((void(__thiscall**)(int*))*(void***)holder)[2](holder);
    return r;
}
