// Slice s00766fa0: UTFKernel "RenderAsset" editor serialization helpers
// (paint-model loader, ability-list loader, material-list loader and the
//  vector/insert helpers they use). /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>
#include <string.h>
#include <new>

extern char g_file[];

// ---------------------------------------------------------------------------
// out-of-slice callees (relocation targets)
// ---------------------------------------------------------------------------
extern "C" {
bool __cdecl ReadInt32(void* stream, void* dst, int count, int flags);      // 0x93a780
bool __cdecl ReadValue(void* stream, void* dst, int n);                     // 0x93a6c0
bool __cdecl WriteValue(void* stream, const void* src, int n);              // 0x93a890
bool __cdecl ReadTripletG(void* stream, void* dst, int n);                  // 0x692740
void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  __cdecl Dealloc(void* p);                                             // 0xf47380
void  __cdecl FUN_005965b0(void* out);
void  __cdecl FUN_00422fd0(void* p);
void  __cdecl FUN_0041f2d0(void* p);
void  __cdecl FUN_00764ff0(void* a, void* b, void* c, void* d);
void  __cdecl FUN_00757fb0(void* a, void* b, void* c);
void  __cdecl FUN_007664b0(void* a, void* b, void* c);
void* __cdecl FUN_00765230(void* a, void* b, void* c, void* d);
void* __cdecl FUN_00757ee0(void* a, void* b, void* c);
void* __cdecl FUN_00757f70(void* a, void* b, void* c);
void  __cdecl FUN_00763f50(void* a, void* b, void* c);
void* __cdecl Node8F4d0(void);                                              // 0x68f4d0
void  __cdecl FUN_0068f9b0(void* p);
void  __cdecl FUN_006909b0(void* p);
void  __cdecl FUN_00691380(void* p);
void* __cdecl FUN_009289f0(void* p, int, int, int, int, int);               // 0x9289f0
void  __cdecl FUN_0040d010(void* p);
void* __cdecl FUN_0067dd60(void);                                           // 0x67dd60
void* __cdecl MaterialManager(void);                                        // 0x67dd70
void  __cdecl RemoveRC(void* p);                                            // 0x714050
bool  __cdecl FUN_0071f8f0(void* stream, void* out);
int   __cdecl FUN_0071ddc0(void* obj, int a, int b, int c, int d);
void  __cdecl RefVecPush(void* vec, void* p);                               // 0x41ef20
void* __cdecl FUN_00764320(void* a, void* b, void* c);
void  __cdecl FUN_00765ac0(void* p);
void  __cdecl Reserve765a10(void* vec, uint32_t n);                         // 0x765a10
void  __cdecl VPtrPush(void* vec, const void* v);                           // 0x766910
void  __cdecl VBigInsert(void* vec, void* pos, uint32_t n, void* value);    // 0x7662d0
void  __cdecl FUN_00767700(void* a, void* b);
void  __cdecl GetImageResource(void* p);                                    // 0x576650
void* __cdecl Fake78050(int v);                                             // 0x778050 table lookup
void* __cdecl ResolveColorSlot(void* a, void* b);                           // 0x7633a0
}

// ===========================================================================
// @ 0x00766fa0  paint-model chunk loader
// ===========================================================================
struct PaintObj {
    uint32_t mVersion;        // +0
    uint32_t mA;              // +4
    uint32_t mB;              // +8
    uint32_t mC;              // +0xc
    uint32_t mFlags;          // +0x10
    uint32_t mD;              // +0x14
    unsigned char mByte18;    // +0x18
    uint32_t mCount;          // +0x1c
    char mVec0[0x58];         // +0x20
    char mVec1[0x24];         // +0x78
};
bool __stdcall ReadPaintStuff(PaintObj* obj, void* stream, void* p3) {
    (void)p3;
    if (!ReadInt32(stream, &obj->mVersion, 1, 1))
        return false;
    if (obj->mVersion > 1)
        return false;
    if (!ReadInt32(stream, &obj->mA, 1, 1))
        return false;
    if (!ReadInt32(stream, &obj->mB, 1, 1))
        return false;
    if (!ReadTripletG(stream, &obj->mC, 1))
        return false;
    if (!ReadTripletG(stream, &obj->mFlags, 1))
        return false;
    if (!ReadTripletG(stream, &obj->mD, 1))
        return false;
    if (obj->mVersion == 0) {
        obj->mByte18 = 0;
        obj->mCount = 1;
    } else {
        obj->mByte18 = (unsigned char)((obj->mFlags >> 0xc) & 1);
        obj->mCount = obj->mByte18 ? 6u : 1u;
    }
    if (!WriteValue(stream, &obj->mC, 4))
        return false;
    Reserve765a10(&obj->mVec0, obj->mC);
    Reserve765a10(obj->mVec1, obj->mCount * obj->mB);
    if (obj->mB != 0) {
        uint32_t i = 0;
        do {
            uint32_t n;
            if (!ReadInt32(stream, &n, 1, 1))
                return false;
            FUN_005965b0(&n);
            if (obj->mCount != 0) {
                uint32_t j = 0;
                do {
                    if (!WriteValue(stream, &n, 1))
                        return false;
                    void* p = Alloc6(n, "Graphics", 0, 0, 0, 0);
                    VPtrPush(&obj->mVec1, &p);
                } while (++j < obj->mCount);
            }
        } while (++i < obj->mB);
    }
    return true;
}

// ===========================================================================
// @ 0x00767170  read chunks into a stack temp and copy a triplet out
// ===========================================================================
void __cdecl FUN_00767170(char* stackObj, int a, int b, int c) {
    char tmp[0xd0];
    (void)tmp;
    if (ReadPaintStuff((PaintObj*)stackObj, (void*)a, (void*)b)) {
        if (FUN_00764320(stackObj, (void*)a, (void*)b)) {
            uint32_t* s = (uint32_t*)c;
            *(uint32_t*)(stackObj + 8) = s[0];
            *(uint32_t*)(stackObj + 0xc) = s[1];
            *(uint32_t*)(stackObj + 0x10) = s[2];
            FUN_00765ac0(stackObj);
            return;
        }
    }
    FUN_00765ac0(stackObj);
}

// ===========================================================================
// @ 0x00767270  forward a member chunk to the loader
// ===========================================================================
struct F67270 {
    char pad0[0xc];
    int mC;                   // +0xc
    char pad10[4];
    int m14;                  // +0x14
    char pad18[0x10];
    void* m28;                // +0x28
    char m2c[8];              // +0x2c
    void Method(int, int);
};
void F67270::Method(int, int unused) {
    (void)unused;
    ReadPaintStuff((PaintObj*)m2c, m28, (void*)m14);
}

// ===========================================================================
// @ 0x00767290  vector<stride 0xa0>::resize(n)
// ===========================================================================
struct VBig2 { char* b; char* e; char* c; void Resize(int, uint32_t n); };
void VBig2::Resize(int, uint32_t n) {
    uint32_t size = (uint32_t)((e - b) / 0xa0);
    if (size < n) {
        VBigInsert(this, e, n - size, 0);
        return;
    }
    char* dst = b + n * 0xa0;
    FUN_00763f50(e, e, dst);
    e = e + (uint32_t)((e - dst) / 0xa0) * 0xa0;
}

// ===========================================================================
// @ 0x00767350  vector<stride 0x7c>::insert(pos, n, value)
// ===========================================================================
struct V7c { char* b; char* e; char* c; void Insert(int, char*, uint32_t, char*); };
void V7c::Insert(int, char* pos, uint32_t n, char* value) {
    uint32_t size = (uint32_t)((e - b) / 0x7c);
    if (size < n) {
        uint32_t cap = size * 2;
        if (size == 0) cap = 1;
        uint32_t need = size + n;
        if (need < cap) need = cap;
        char* nb = need ? (char*)Alloc6(need * 0x7c, "Graphics", 0, 0, g_file, 0xd1) : 0;
        char* p = (char*)FUN_00757ee0(b, pos, nb);
        FUN_00757f70(b, pos, nb);
        FUN_00765230(p, (void*)(size_t)n, value, b);
        char* ne = (char*)FUN_00757ee0(pos, e, p + n * 0x7c);
        FUN_00757f70(pos, e, p + n * 0x7c);
        if (b && *(int*)(b - 4) != 0)
            Dealloc(b);
        e = ne;
        b = nb;
        c = nb + need * 0x7c;
    } else if (n) {
        char* end = e;
        uint32_t right = (uint32_t)((end - pos) / 0x7c);
        if (n < right) {
            char* edge = end - n * 0x7c;
            char tmp[0x7c];
            FUN_00764ff0(&tmp, edge, end, end);
            e = end + n * 0x7c;
            FUN_00757fb0(pos, edge, end);
            FUN_007664b0(pos, n * 0x7c + pos, tmp);
            FUN_0041f2d0(&tmp);
        } else {
            char tmp[0x7c];
            FUN_00765230(end, (void*)(size_t)(n - right), tmp, 0);
            e = end + (n - right) * 0x7c;
            FUN_00764ff0(&tmp, pos, end, e);
            e = e + right * 0x7c;
            FUN_007664b0(pos, end, tmp);
            FUN_0041f2d0(&tmp);
        }
    }
}

// ===========================================================================
// @ 0x00767590  build and enqueue a job object
// ===========================================================================
extern "C" void* __cdecl FUN_007640c0(void* p);      // 0x7640c0
bool __stdcall BuildJob(int* a, int* b, unsigned char c) {
    int* h = (int*)Alloc6(0x1c, "Graphics", 0, 0, 0, 0);
    if (h)
        h = (int*)FUN_007640c0(h);
    if (!h)
        return false;
    if (a != (int*)h[3]) {
        if (a) ((void(__thiscall**)(void*))*(void***)a)[0](a);
        h[3] = (int)a;
    }
    if (b != (int*)h[4]) {
        if (b) ((void(__thiscall**)(void*))*(void***)b)[1](b);
        h[4] = (int)b;
    }
    h[5] = 0x4755bcf;
    *(unsigned char*)(h + 6) = c;
    if (b) ((void(__thiscall**)(void*))*(void***)b)[8](b);
    void* node = Node8F4d0();
    int local = 0;
    ((void(__thiscall**)(void*, int*))*(void***)node)[4](node, &local);
    FUN_0068f9b0(h);
    FUN_006909b0((void*)local);
    if (h) ((void(__thiscall**)(void*))*(void***)h)[1](h);
    return true;
}

// ===========================================================================
// @ 0x007677c0  arm the decode of a 0x2f4e681c resource
// ===========================================================================
bool __fastcall ArmDecode(void* self, int, int unused) {
    (void)unused;
    char* s = (char*)self;
    if (*(int*)(s + 0x18) != 0x2f4e681c)
        return false;
    *(int*)(s + 0xfc) = 4;
    char* e = s + 0x64;
    *(char**)(s + 0x5c) = e;
    *(char**)(s + 0x50) = e;
    *(char**)(s + 0x4c) = e;
    *(char**)(s + 0x54) = s + 0xa4;
    char* f = s + 0xbc;
    *(char**)(s + 0xb4) = f;
    *(char**)(s + 0xa8) = f;
    *(char**)(s + 0xa4) = f;
    *(char**)(s + 0xac) = s + 0xfc;
    int* a = (int*)Node8F4d0();
    ((void(__thiscall**)(int*))*(void***)a)[8](a);
    int* b = (int*)Node8F4d0();
    if (b && !((bool(__thiscall**)(int*, int*))*(void***)b)[4](b, (int*)&b))
        return false;
    int* d = (int*)Node8F4d0();
    if (d && !((bool(__thiscall**)(int*, int*))*(void***)d)[4](d, (int*)&d))
        return false;
    FUN_0068f9b0(s);
    FUN_006909b0(s);
    if (a) ((void(__thiscall**)(int*))*(void***)a)[9](a);
    return true;
}

// ===========================================================================
// @ 0x007679f0  read a serialized ability list
// ===========================================================================
bool __stdcall ReadAbilityList(void* stream, char* obj, void* key) {
    (void)key;
    uint32_t count;
    if (!ReadValue(stream, &count, 4))
        return false;
    uint32_t alloc;
    if (!WriteValue(stream, &alloc, 4))
        return false;
    FUN_00767700(stream, &count);
    for (uint32_t i = 0; i < count; i++) {
        uint32_t kind;
        if (!ReadValue(stream, &kind, 4))
            return false;
        if (kind == 0x20d) {
            void* p = Alloc6(0x70, "Editor", 0, 0, 0, 0);
            if (p) FUN_0040d010(p);
            uint32_t n;
            if (!ReadValue(stream, &n, 4) || n > 6)
                return false;
            for (uint32_t j = 0; j < n; j++) {
                char item[0x10];
                if (!ReadValue(stream, item, 0x10))
                    return false;
                int c1 = 0, c2 = 0;
                if (!ReadValue(stream, &c1, 4) || !ReadValue(stream, &c2, 4))
                    return false;
                (void)ResolveColorSlot(&c1, &c2);
                void* mm = FUN_0067dd60();
                int img = ((int(__thiscall**)(void*, int, int, int))*(void***)mm)[8](mm, c1, c2, 4);
                GetImageResource(&img);
            }
        } else {
            void* p = FUN_009289f0((char*)0 + 0xc, 0, 0, 0, 0, 0);
            if (!p)
                p = 0;
            else {
                *(short*)((char*)p + 4) = (short)kind;
                *(void**)p = (void*)0;
                *(unsigned short*)((char*)p + 6) = (unsigned short)(size_t)Fake78050((int)kind);
                *(void**)((char*)p + 8) = (char*)p + 0xc;
            }
            if (!ReadValue(stream, *(void**)((char*)p + 8), (int)(size_t)Fake78050((int)kind)))
                return false;
        }
        (void)obj;
    }
    return true;
}

// ===========================================================================
// @ 0x00767c80  read a serialized material/ref list
// ===========================================================================
bool __stdcall ReadMaterialList(void* stream, char* obj, uint32_t* key3) {
    *(uint32_t*)(obj + 8) = key3[0];
    *(uint32_t*)(obj + 0xc) = key3[1];
    *(uint32_t*)(obj + 0x10) = key3[2];
    int one;
    if (!ReadInt32(stream, &one, 1, 0) || one != 1)
        return false;
    int count;
    if (!ReadInt32(stream, &count, 1, 0))
        return false;
    for (int i = 0; i < count; i++) {
        void* p = 0;
        if (!FUN_0071f8f0(stream, &p))
            return false;
        RefVecPush(obj + 0x18, &p);
        if (p) {
            volatile int* rc = (volatile int*)((char*)p + 4);
            if (_InterlockedExchangeAdd((volatile long*)rc, -1) - 1 == 0) {
                _InterlockedExchange((volatile long*)rc, 1);
                ((void(__thiscall**)(void*, int))*(void***)p)[0](p, 1);
            }
        }
    }
    for (int i = 0; i < count; i++) {
        int e = *(int*)(*(int*)(obj + 0x18) + i * 4);
        int idx = FUN_0071ddc0((void*)e, 0x15, 0, 6, 8);
        if (idx >= 0) {
            char* slot = (char*)(idx * 0x20 + 0x10 + *(int*)(e + 8));
            int* local = 0;
            void* mm = MaterialManager();
            int r = ((int(__thiscall**)(void*, void*, void*, int**, void*))*(void***)mm)[0x48 / 4](
                mm, *(void**)slot, *((void**)slot + 1), &local, key3);
            if (r < 0) {
                if (local) ((void(__thiscall**)(int*))*(void***)local)[1](local);
                return false;
            }
            if (local) {
                RemoveRC(*((void**)slot + 3));
                if (local != *((int**)slot + 3)) {
                    ((void(__thiscall**)(int*))*(void***)local)[0](local);
                    *((int**)slot + 3) = local;
                }
            }
            if (local) ((void(__thiscall**)(int*))*(void***)local)[1](local);
        }
    }
    return true;
}
