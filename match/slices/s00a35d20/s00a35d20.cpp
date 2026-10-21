// Slice s00a35d20 - SP::Audio::cAmbienceLayer (Update/Shutdown/ConnectPrimitive/
// ConfigurePrimitives/ReadTuningValues/Init), EA::Audio::PrimitiveAggregate aggregate
// machinery and the small EASTL-vector / fixed-allocator helpers in the same range.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    i8;
typedef short          i16;
typedef int            i32;

#define VFN(p, off) ((*(void***)(p))[(off) / 4])

// ---------------------------------------------------------------------------
// External callees (addresses from the analysis image; the annotation comments let
// tools/difftest/resolve.py bind each reference to the original target).
// ---------------------------------------------------------------------------
void   __fastcall fA35150(void* self);                                              // 0xa35150
void   __cdecl    f572020(void* p, int v);                                          // 0x572020
void*  __cdecl    GetSystemAT(void);                                                // 0xa206f0
void   __cdecl    AudioSetListener3(void* s, float x, float y, float z);            // 0x9fbc50
void   __cdecl    Start3dSoundByName(void* id, void* h, float x, float y, float z); // 0x571f80
void   __fastcall fA35840(void* self, u32 dummy, u32 id, float v);                  // 0xa35840
void   __fastcall fA358d0(void* self, u32 dummy, void** a, void** b);               // 0xa358d0
void*  __cdecl    GetServer(void);                                                  // 0x883860
void*  __fastcall f621f50(void* self, u32 dummy, void* first, void* last);          // 0x621f50
void*  __fastcall fA36d60(void* self, u32 dummy, void* arg);                        // 0xa36d60
void   __fastcall fA16a30(void* self, u32 dummy, void* arg);                        // 0xa16a30
void*  __cdecl    Alloc38c(int size);                                               // 0xa36f00
void*  __fastcall fA37160(void* self, u32 dummy, void* arg);                        // 0xa37160
void   __fastcall fA171c0(void* self, u32 dummy, void* a, int b);                   // 0xa171c0
void   __fastcall fA37080(void* self, u32 dummy, void* a);                          // 0xa37080
void   __fastcall DestroyAutoRefVec(void* self);                                    // 0x7c80c0
void   __cdecl    copyImpl(void* a, void* b, void* c);                              // 0x6782c0
void   __cdecl    fAC97A0(void* a, void* b, void* c);                               // 0xac97a0
void*  __cdecl    VecDoInsertValue(void* self, void* src, int nbytes);              // 0x11e0744
void*  __cdecl    EAAllocate(u32 size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void   __cdecl    opDelete(void* p);                                                // 0xf47380
namespace EA { namespace Allocator {
struct CoreBlock_s0092_6410;
struct FixedAllocatorBase_s0092_6410 { bool AddCore(CoreBlock_s0092_6410* p, u32 n); }; // 0x926650
} }
void*  __cdecl    f6abeb0(int size);                                                // 0x6abeb0
void   __fastcall EStrCtor(void* self, u32 dummy, void* src);                       // 0x57cb10
void   __fastcall EStrAppend(void* self, u32 dummy, const char* a, const char* b);  // 0x455d60
u32    __cdecl    FNV1_String8(const char* s, u32 seed, int flag);                  // 0x932e80
void   __fastcall EStrReplace(void* self, u32 dummy, int pos, int count, const char* s); // 0x91ba20
void   __fastcall EStrAssign(void* self, u32 dummy, const char* a, const char* b);  // 0x454cb0
void*  __cdecl    fA366e0(int size);                                                // 0xa366e0
void   __fastcall fA35EF0(void* self, u32 dummy, void** v);                         // 0xa35ef0

// data
extern char g_0166e290;         // 0x166e290 free-list head
extern char g_0166e280;         // 0x166e280 FixedAllocatorBase
extern char g_01453140;         // 0x1453140
extern char g_01453124;         // 0x1453124
extern char g_01453120;         // 0x1453120
extern char g_013ef094;         // 0x13ef094
extern char g_013eb938;         // 0x13eb938
extern char c_013ebb38[];       // 0x13ebb38 EASTL allocator.h path
extern char c_013f2150[];       // 0x13f2150 "EASTL"
extern char c_014530c8[];       // 0x14530c8
extern char c_014530ca[];       // 0x14530ca
extern char c_014530bc[];       // 0x14530bc "_density"
extern char c_014530c4[];       // 0x14530c4
extern char c_014335e8[];       // 0x14335e8
extern char c_014335e4[];       // 0x14335e4

struct EString { char* b; char* e; char* c; };

// ---------------------------------------------------------------------------
// SP::Audio::cAmbienceLayer
// ---------------------------------------------------------------------------
namespace SP { namespace Audio {

class cAmbienceLayer { public:
    char pad[0x400];

    void  Update();                 // 0xa35d20
    bool  Shutdown();               // 0xa35f70
    void  ConnectPrimitive(u32 key, void* primitive); // 0xa36070
    bool  ConfigurePrimitives();    // 0xa36250
    bool  ReadTuningValues();       // 0xa36490
    bool  Init();                   // 0xa36570
};

// @ 0x00a35d20
void cAmbienceLayer::Update()
{
    char* self = (char*)this;
    fA35150(self);

    bool bVar5;
    if (*(int*)(self + 0x24) == *(int*)(self + 0x28)) bVar5 = false;
    else if (*(u8*)(self + 0x88) == 0)               bVar5 = false;
    else                                             bVar5 = (*(u8*)(self + 0x89) == 0);

    bool bVar4 = (*(int*)(self + 0x5c) != 0) && bVar5;

    if (*(u8*)(self + 0x60) != 0 && !bVar4) {
        f572020(*(void**)(self + 0x64), 0);
        void* h = *(void**)(self + 0x64);
        void* sys = GetSystemAT();
        if (sys) ((void(__thiscall*)(void*, void*))VFN(sys, 0x2c))(sys, h);
        *(void**)(self + 0x64) = 0;
        *(u8*)(self + 0x60) = 0;
    }

    if (bVar5) {
        if (*(u8*)(self + 0x70) != 0) {
            *(u32*)(self + 0x48) = *(u32*)(self + 0x3c);
            *(u32*)(self + 0x4c) = *(u32*)(self + 0x40);
            *(u32*)(self + 0x50) = *(u32*)(self + 0x44);
        }
        float x = *(float*)(self + 0x48);
        float y = *(float*)(self + 0x4c);
        float z = *(float*)(self + 0x50);
        fA35840(self, 0, *(u32*)(self + 0x28c), *(float*)(self + 0x294));
        fA35840(self, 0, *(u32*)(self + 0x280), x);
        fA35840(self, 0, *(u32*)(self + 0x284), y);
        fA35840(self, 0, *(u32*)(self + 0x288), z);
        if (*(u8*)(self + 0x60) != 0) {
            AudioSetListener3(*(void**)(self + 0x64), x, y, z);
            return;
        }
        if (bVar4) {
            void* sys = GetSystemAT();
            void* h = sys ? ((void*(__thiscall*)(void*))VFN(sys, 0x24))(sys) : 0;
            *(void**)(self + 0x64) = h;
            Start3dSoundByName(*(void**)(self + 0x5c), h, x, y, z);
            *(u8*)(self + 0x60) = 1;
            return;
        }
    } else {
        fA35840(self, 0, *(u32*)(self + 0x28c), 0.0f);
    }
}

// @ 0x00a35f70
bool cAmbienceLayer::Shutdown()
{
    char* self = (char*)this;
    void* srv = GetServer();
    if (srv) ((void(__thiscall*)(void*, void*, int, int))VFN(srv, 0x2c))(srv, self, 0x3a127dc, -9999);
    *(u8*)(self + 0x27c) = 0;
    if (*(u8*)(self + 0x60) != 0) {
        fA35840(self, 0, *(u32*)(self + 0x28c), 0.0f);
        fA35840(self, 0, *(u32*)(self + 0x280), 0.0f);
        fA35840(self, 0, *(u32*)(self + 0x284), 0.0f);
        fA35840(self, 0, *(u32*)(self + 0x288), 0.0f);
        f572020(*(void**)(self + 0x64), 1);
        *(u8*)(self + 0x60) = 0;
    }
    char* vec = self + 0x74;
    int n = (*(int*)(self + 0x78) - *(int*)(self + 0x74)) >> 3;
    for (int i = 0; i < n; ++i) {
        void* e = *(void**)(*(int*)vec + i * 8 + 4);
        if (((void*(__thiscall*)(void*))VFN(e, 0x30))(e) == self)
            ((void(__thiscall*)(void*))VFN(e, 0x14))(e);
    }
    f621f50(vec, 0, *(void**)vec, *(void**)(vec + 4));
    return true;
}

struct AmbPair { u32 first; void* second; };

// @ 0x00a36070
void cAmbienceLayer::ConnectPrimitive(u32 key, void* primitive)
{
    char* self = (char*)this;
    char* vec = self + 0x74;
    int n = (*(int*)(self + 0x78) - *(int*)(self + 0x74)) >> 3;
    AmbPair* found = 0;
    for (int i = 0; i < n; ++i) {
        AmbPair* p = (AmbPair*)(*(int*)vec + i * 8);
        if (p->first == key) { found = p; break; }
    }
    if (!found) {
        if (primitive) ((void(__thiscall*)(void*))VFN(primitive, 0))(primitive);
        AmbPair p; p.first = key; p.second = primitive;
        if (primitive) ((void(__thiscall*)(void*))VFN(primitive, 0))(primitive);
        ((void(__fastcall*)(void*, u32, void**))fA35EF0)(vec, 0, (void**)&p);
        if (p.second) ((void(__thiscall*)(void*))VFN(p.second, 4))(p.second);
        if (primitive) ((void(__thiscall*)(void*))VFN(primitive, 4))(primitive);
        return;
    }

    void* obj = found->second;
    if (obj) {
        void* qi = ((void*(__thiscall*)(void*, int))VFN(obj, 0xc))(obj, 0x4e73a43a);
        if (qi && ((void*(__thiscall*)(void*))VFN(obj, 0x30))(obj) == self) {
            ((void(__thiscall*)(void*, void*))VFN(qi, 0x10))(qi, primitive);
            return;
        }
    }

    void* mem = fA366e0(0x6c);
    void* canvas = mem ? fA36d60(mem, 0, self) : 0;
    void* cv = 0;
    if (canvas) { ((void(__thiscall*)(void*))VFN(canvas, 0))(canvas); cv = canvas; }
    fA16a30(cv, 0, (void*)key);
    ((void(__thiscall*)(void*))VFN(cv, 0x10))(cv);
    void* sub = *(void**)((char*)cv + 4);
    ((void(__thiscall*)(void*, void*))VFN(sub, 0x10))(sub, obj);
    ((void(__thiscall*)(void*, void*))VFN(sub, 0x10))(sub, primitive);
    void* old = found->second;
    if (cv != old) {
        ((void(__thiscall*)(void*))VFN(cv, 0))(cv);
        found->second = cv;
        if (old) ((void(__thiscall*)(void*))VFN(old, 4))(old);
    }
    ((void(__thiscall*)(void*))VFN(cv, 4))(cv);
}

// @ 0x00a36250
bool cAmbienceLayer::ConfigurePrimitives()
{
    char* self = (char*)this;
    void* cfg = *(void**)(self + 0xc);
    u32 count = 0;
    void* array = 0;
    if (!((bool(__thiscall*)(void*, u32, u32*, void**))VFN(cfg, 0x48))(cfg, 0x3da0a727, &count, &array))
        return false;
    if (count == 0) return true;

    while (count >= 2) {
        u32* a = (u32*)array;
        u32 k1 = a[0];
        u32 k2 = a[1];
        a += 2;
        count -= 2;
        u32 k3 = 0;
        if (count != 0) {
            k3 = a[0]; ++a; --count;
            if (count != 0 && a[0] == 0) { ++a; --count; }
        }
        if (k1 == 0 || k2 == 0) return false;

        void* obj = 0;
        if (k3 != 0) {
            void* c2 = *(void**)(self + 0xc);
            void* pa = 0; void* pb = 0;
            if (((bool(__thiscall*)(void*, u32, void**, void**))VFN(c2, 0x44))(c2, k3, &pb, &pa)) {
                void* mem = Alloc38c(0x38c);
                void* o = mem ? fA37160(mem, 0, self) : 0;
                if (o) { ((void(__thiscall*)(void*))VFN(o, 0))(o); obj = o; }
                fA171c0(obj, 0, pb, ((int)pa) >> 1);
            }
        }
        void* sys = GetSystemAT();
        void* got = 0;
        if (((bool(__thiscall*)(void*, u32, void**))VFN(sys, 0x34))(sys, k2, &got)) {
            if (obj) {
                fA37080(obj, 0, got);
                ((void(__thiscall*)(void*))VFN(obj, 0x10))(obj);
                if (obj != got) {
                    ((void(__thiscall*)(void*))VFN(obj, 0))(obj);
                    got = obj;
                }
            }
            ConnectPrimitive(k1, got);
        }
        if (got) ((void(__thiscall*)(void*))VFN(got, 4))(got);
        if (obj) ((void(__thiscall*)(void*))VFN(obj, 4))(obj);
    }
    return true;
}

// @ 0x00a36490
bool cAmbienceLayer::ReadTuningValues()
{
    char* self = (char*)this;
    void* sys = GetSystemAT();
    char* cfg = self + 0xc;
    void* c = *(void**)(self + 0xc);
    if (c) { *(void**)(self + 0xc) = 0; ((void(__thiscall*)(void*))VFN(c, 4))(c); }
    if (!((bool(__thiscall*)(void*, u32, char*, int))VFN(sys, 0x14))(sys, *(u32*)(self + 0x20), cfg, 0x21407ee))
        return false;

    void* cc = *(void**)(self + 0xc);
    char* s = ((char*(__thiscall*)(void*, int))VFN(cc, 0x40))(cc, 0x2f8b3bf4);
    if (s) {
        char* e = s;
        while (*e) ++e;
        EStrAssign(self + 0x10, 0, s, e);
    }
    void* c2 = *(void**)(self + 0xc);
    ((void(__thiscall*)(void*, int, void*))VFN(c2, 0x30))(c2, 0xe0f9a433, self + 0x58);
    c2 = *(void**)(self + 0xc);
    ((void(__thiscall*)(void*, int, void*))VFN(c2, 0x30))(c2, 0x2bd62d35, self + 0x68);
    c2 = *(void**)(self + 0xc);
    ((void(__thiscall*)(void*, int, void*))VFN(c2, 0x30))(c2, 0x2e65b70f, self + 0x6c);
    c2 = *(void**)(self + 0xc);
    ((void(__thiscall*)(void*, int, void*))VFN(c2, 0x38))(c2, 0x701ed91e, self + 0x5c);
    c2 = *(void**)(self + 0xc);
    ((void(__thiscall*)(void*, int, void*))VFN(c2, 0x38))(c2, 0x1e16cfe8, self + 0x38);
    ConfigurePrimitives();
    return true;
}

// @ 0x00a36570
bool cAmbienceLayer::Init()
{
    char* self = (char*)this;
    if (!ReadTuningValues()) return false;
    char* name = self + 0x10;
    EString tmp;
    EStrCtor(&tmp, 0, name);
    EStrAppend(&tmp, 0, c_014530c8, c_014530ca);
    *(u32*)(self + 0x280) = FNV1_String8(tmp.b, 0x811c9dc5, 1);
    EStrReplace(&tmp, 0, (int)(tmp.e - tmp.b) - 1, 1, c_014335e8);
    *(u32*)(self + 0x284) = FNV1_String8(tmp.b, 0x811c9dc5, 1);
    EStrReplace(&tmp, 0, (int)(tmp.e - tmp.b) - 1, 1, c_014335e4);
    *(u32*)(self + 0x288) = FNV1_String8(tmp.b, 0x811c9dc5, 1);
    if (name != (char*)&tmp) EStrAssign(name, 0, tmp.b, tmp.e);
    EStrAppend(&tmp, 0, c_014530bc, c_014530c4);
    *(u32*)(self + 0x28c) = FNV1_String8(tmp.b, 0x811c9dc5, 1);
    void* srv = GetServer();
    if (srv) ((void(__thiscall*)(void*, void*, int))VFN(srv, 0x20))(srv, self, 0x3a127dc);
    if ((tmp.e - tmp.b) > 1 && tmp.b) opDelete(tmp.b);
    return true;
}

} } // namespace SP::Audio

using SP::Audio::cAmbienceLayer;

// ---------------------------------------------------------------------------
// EA::Audio::PrimitiveAggregate
// ---------------------------------------------------------------------------
namespace EA { namespace Audio {

class PrimitiveAggregate { public:
    char pad[0x100];

    float CalculateAggregate();     // 0xa367a0
    bool  ShouldUpdate(u32 b);      // 0xa36750
    void  SetParam(float value, int param_3); // 0xa36990
};

static float ElemValue(void* base, int i)
{
    void* e = *(void**)((char*)base + i * 4);
    return ((float(__thiscall*)(void*))VFN(e, 0x1c))(e);
}

// @ 0x00a367a0
float PrimitiveAggregate::CalculateAggregate()
{
    char* self = (char*)this;
    int n = (*(int*)(self + 0x14) - *(int*)(self + 0x10)) >> 2;
    if (n <= 0) return 0.0f;
    void* base = *(void**)(self + 0x10);
    if (n == 1) return ElemValue(base, 0);

    u32 mode = *(u32*)(self + 0x54);
    float acc = 0.0f;
    int i;

    if (mode == 0x467e1ea3) {                    // minimum
        acc = ElemValue(base, 0);
        for (i = 1; i < n; ++i) { float v = ElemValue(base, i); if (v < acc) acc = v; }
        return acc;
    }
    if (mode == 0x3e7e124d) {                    // maximum
        acc = ElemValue(base, 0);
        for (i = 1; i < n; ++i) { float v = ElemValue(base, i); if (acc < v) acc = v; }
        return acc;
    }
    if (mode == 0xd256aaba) {                    // product
        acc = ElemValue(base, 0);
        for (i = 1; i < n; ++i) acc *= ElemValue(base, i);
        return acc;
    }
    if (mode == 0xf524f3a6) {                    // average
        for (i = 0; i < n; ++i) acc += ElemValue(base, i);
        if (n > 1) acc = acc / (float)n;
        return acc;
    }
    if (mode == 0x1d3454e5) {                    // last
        return ElemValue(base, n - 1);
    }
    if (mode == 0x3b83da79) {                    // first
        return ElemValue(base, 0);
    }
    return acc;
}

// @ 0x00a36750
bool PrimitiveAggregate::ShouldUpdate(u32 b)
{
    char* self = (char*)this;
    if (*(bool*)(self + 0x50)) return true;
    if ((char)b != '\0') {
        void** begin = *(void***)(self + 0x10);
        void** end = *(void***)(self + 0x14);
        for (; begin != end; ++begin) {
            void* e = *begin;
            if (((bool(__thiscall*)(void*, u32))VFN(e, 0x20))(e, b)) return true;
        }
    }
    return *(bool*)(self + 0x50);
}

// @ 0x00a36990
void PrimitiveAggregate::SetParam(float value, int param_3)
{
    char* self = (char*)this;
    if (*(int*)(self + 0x58) == param_3) return;
    *(int*)(self + 0x58) = param_3;
    void** end = *(void***)(self + 0x14);
    void** begin = *(void***)(self + 0x10);
    u8 flag = *(u8*)(self + 0x50);
    for (; begin != end; ++begin) {
        void* e = *begin;
        ((void(__thiscall*)(void*, float, int))VFN(e, 0x28))(e, value, param_3);
        if (((bool(__thiscall*)(void*, int))VFN(e, 0x20))(e, 0)) flag = 1;
    }
    if (flag) {
        *(float*)(self + 0x60) = CalculateAggregate();
        --*(int*)(self + 0x58);
        *(u8*)(self + 0x50) = 1;
    }
}

} } // namespace EA::Audio

// ---------------------------------------------------------------------------
// Fixed-allocator helper and EASTL-vector helpers in the same range.
// ---------------------------------------------------------------------------
// @ 0x00a366e0
void* __cdecl fA366e0(int size)
{
    if (size == 0x6c) {
        char c;
        void* p;
        do {
            p = *(void**)&g_0166e290;
            if (p) { *(void**)&g_0166e290 = *(void**)p; return p; }
            c = ((EA::Allocator::FixedAllocatorBase_s0092_6410*)&g_0166e280)->AddCore(0, 0);
        } while (c);
        return 0;
    }
    return f6abeb0(size);
}

struct S106 {
    char pad[0x100];
    void pushPair(void** v);            // 0xa35ef0
    void dtor();                        // 0xa36a10
    void vecInsert(void** pos, void** value); // 0xa36ad0
    bool vecRemove(u32 key);            // 0xa36c80
};

// @ 0x00a35ef0
void S106::pushPair(void** v)
{
    char* self = (char*)this;
    void** end = *(void***)(self + 4);
    if (end < *(void***)(self + 8)) {
        *(void***)(self + 4) = end + 2;
        if (end) {
            end[0] = v[0];
            end[1] = v[1];
            if (end[1]) ((void(__thiscall*)(void*))VFN(end[1], 0))(end[1]);
        }
    } else {
        fA358d0(self, 0, end, v);
    }
}

// @ 0x00a36a10
void S106::dtor()
{
    char* self = (char*)this;
    *(void**)(self + 0) = &g_01453140;
    *(void**)(self + 4) = &g_01453124;
    *(void**)(self + 8) = &g_01453120;
    DestroyAutoRefVec(self + 0x10);
    *(void**)(self + 8) = &g_013ef094;
    *(void**)(self + 4) = &g_013eb938;
    *(void**)(self + 0) = &g_013eb938;
}

// @ 0x00a36ad0
void S106::vecInsert(void** pos, void** value)
{
    char* self = (char*)this;
    int* begin = *(int**)(self + 0);
    int* end = *(int**)(self + 4);
    int* cap = *(int**)(self + 8);
    if (end != cap) {
        int* src = (int*)value;
        if ((int*)pos <= src && src < end) src = src + 1;
        int* dest = end;
        if (dest) {
            int v = *(int*)(end - 1);
            *dest = v;
            if (v) ((void(__thiscall*)(void*))VFN((void*)v, 0))((void*)v);
        }
        fAC97A0(pos, end - 1, end);
        int* nv = *(int**)src;
        int* ov = *(int**)pos;
        if (nv != ov) {
            if (nv) ((void(__thiscall*)(void*))VFN((void*)nv, 0))((void*)nv);
            *(int**)pos = nv;
            if (ov) ((void(__thiscall*)(void*))VFN((void*)ov, 4))((void*)ov);
        }
        *(int**)(self + 4) = end + 1;
        return;
    }

    int count = (int)(end - begin);
    int newcap;
    if (count <= 0) newcap = 1;
    else newcap = count * 2;
    int* buf = 0;
    if (newcap != 0)
        buf = (int*)EAAllocate((u32)(newcap * 4), c_013f2150, 0, 0, c_013ebb38, 0xd1);
    int before = (int)((char*)pos - (char*)begin);
    void* r1 = VecDoInsertValue(buf, begin, before);
    int* mid = (int*)((char*)r1 + before);
    if (mid) {
        int v = *(int*)value;
        *mid = v;
        if (v) ((void(__thiscall*)(void*))VFN((void*)v, 0))((void*)v);
    }
    int after = (int)((char*)end - (char*)pos);
    void* r2 = VecDoInsertValue((char*)mid + 4, pos, after);
    int* newend = (int*)((char*)r2 + after);
    if (begin && begin != *(int**)(self + 0x10)) opDelete(begin);
    *(int**)(self + 4) = newend;
    *(int**)(self + 0) = buf;
    *(int**)(self + 8) = (int*)((char*)buf + newcap * 4);
}

// @ 0x00a36c80
bool S106::vecRemove(u32 key)
{
    char* self = (char*)this;
    u32* p = *(u32**)(self + 0xc);
    u32* end = *(u32**)(self + 0x10);
    while (p != end && *p != key) ++p;
    if (p == end) return false;
    if (p + 1 < end) copyImpl(p + 1, end, p);
    *(u32**)(self + 0x10) = end - 1;
    void* e = *(void**)(end - 1);
    if (e) ((void(__thiscall*)(void*))VFN(e, 4))(e);
    *(u8*)(self + 0x4c) = 1;
    return true;
}
