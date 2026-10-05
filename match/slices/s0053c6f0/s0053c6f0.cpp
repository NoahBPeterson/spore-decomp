// Swarm skin-paint paint-variable commands (copy/add-variable), the
// PaintVarModifier ctor and the 0x14-stride vector insert helpers.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern "C" void* __cdecl memmove(void*, const void*, size_t);
void* operator new[](size_t); void operator delete[](void*);

struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {} };

namespace EA { namespace ArgScript {
struct cIParser {
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void V35(); PV(36) virtual float GetFloat(const char*); PV(39) PV(40) PV(41)
    virtual cSPVector3 GetVector(const char*);
#undef PV
};
struct cArguments {
    const char** MainArguments(size_t* pCount, int min, int max);
    const char** MainArguments(int count);
    const char** OptionArguments(const char* name, int count);
    bool HasFlag(const char* flag);
    const char* operator[](int i);
};
struct cICommand { virtual void AddRef(); virtual void Release(); virtual void Cast(); };
struct cCommandBase : cICommand { cIParser* mParser; int mRefCount; };
} }

void FUN_005370b0(int n, void* p);                                    // 0x5370b0
void FUN_004547f0(float* p);                                          // 0x4547f0
void FUN_00537130(float* p);                                          // 0x537130
void FUN_004227f0(void* p);                                           // 0x4227f0
void* FUN_0042dee0(void* alloc, unsigned n, unsigned align, unsigned off); // 0x42dee0
void* FUN_0047b3d0(const void* first, const void* last, void* dst);   // 0x47b3d0
void FUN_0053d230(void* dst, int n, void* src);                       // 0x53d230
extern float kDefaultColor[3];                                        // 0x15e24bc

static EA::ArgScript::cIParser* Parser(void* self) { return *(EA::ArgScript::cIParser**)((char*)self + 4); }
static cSPVector3 mParserGetVector(void* self, const char* s) { return Parser(self)->GetVector(s); }
static float mParserGetFloat(void* self, const char* s) { return Parser(self)->GetFloat(s); }
static void mParserV35(void* self) { Parser(self)->V35(); }

// @ 0x0053c6f0
void PaintCopyVar_Execute(void* self, EA::ArgScript::cArguments& args)
{
    const char** argv = args.MainArguments(2);
    cSPVector3 a = mParserGetVector(self, argv[0]);
    cSPVector3 b = mParserGetVector(self, argv[1]);
    int* vec = *(int**)(*(int*)((char*)self + 0xc) + 0x50);
    unsigned n = (unsigned)(vec[1] - *vec) >> 4;
    if (!((n != 0 && *(uint8_t*)(*vec + 0xc) > 0xfc) &&
          (n >= 2 && *(uint8_t*)(*vec + 0x1c) > 0xfd)))
        return;
    if (n < 2) {
        float def[3] = { kDefaultColor[0], kDefaultColor[1], kDefaultColor[2] };
        FUN_005370b0(2, def);
    }
    int* p = (int*)*vec;
    *(float*)(p + 4) = a.x;
    *(float*)(p + 5) = a.y;
    *(float*)(p + 6) = a.z;
    *(int*)(p + 7) = (int)(((vec[0xb] - vec[10]) >> 2) << 16) | 0x3fe;
    FUN_004547f0(&b.x);
    FUN_004547f0(&b.y);
    FUN_004547f0(&b.z);
}

// @ 0x0053c930
void PaintAddVary_Execute(void* self, EA::ArgScript::cArguments& args, const char** argv, int count)
{
    int* vec = *(int**)(*(int*)((char*)self + 0xc) + 0x50);
    unsigned n = (unsigned)(vec[1] - *vec) >> 4;
    if (!((n != 0 && *(uint8_t*)(*vec + 0xc) > 0xfc) &&
          (n >= 2 && *(uint8_t*)(*vec + 0x1c) > 0xfd)))
        return;
    if (n < 2) {
        float def[3] = { kDefaultColor[0], kDefaultColor[1], kDefaultColor[2] };
        FUN_005370b0(2, def);
    }
    float v[7];
    v[0] = kDefaultColor[0]; v[1] = kDefaultColor[1]; v[2] = kDefaultColor[2];
    *(uint8_t*)&v[3] = 0xff;
    *(uint8_t*)((char*)v + 0xd) = (uint8_t)count;
    *(uint16_t*)((char*)v + 0xe) = (uint16_t)((vec[0xb] - vec[10]) >> 2);
    for (int i = 0; i < count; ++i) {
        float f = mParserGetFloat(self, argv[i]);
        FUN_004547f0(&f);
    }
    const char** o = args.OptionArguments("vary", 1);
    if (o) v[0] = mParserGetFloat(self, o[0]);
    o = args.OptionArguments("offset", 1);
    if (o) v[1] = mParserGetFloat(self, o[0]);
    FUN_00537130(v);
    (void)args; (void)self;
}

// @ 0x0053cca0
void* PaintVarModifierCtor(void* p)
{
    *(void**)p = (void*)0x13f3f10;
    return p;
}

// @ 0x0053cd80
void Vector20Insert(void* vec, const void* value, unsigned count, const void* src)
{
    char* b = *(char**)vec;
    char* e = *(char**)((char*)vec + 4);
    char* cap = *(char**)((char*)vec + 8);
    unsigned size = (unsigned)((e - b) / 0x14);
    if ((unsigned)((cap - b) / 0x14) >= count) {
        if (count) {
            // shift tail right and fill with copies of src
            unsigned pos = (unsigned)(((char*)value - b) / 0x14);
            memmove(e + count * 0x14, value, (size - pos) * 0x14);
            for (unsigned i = 0; i < count; ++i)
                FUN_0053d230(b + (pos + i) * 0x14, 1, (void*)src);
            *(char**)((char*)vec + 4) = e + count * 0x14;
        }
    } else {
        unsigned newcap = size ? size * 2 : 1;
        if (size + count > newcap) newcap = size + count;
        char* nb = (char*)FUN_0042dee0((char*)vec + 0xc, newcap * 0x14, 4, 0);
        char* mid = (char*)FUN_0047b3d0(b, value, nb);
        FUN_0053d230(mid, count, (void*)src);
        char* end = (char*)FUN_0047b3d0(value, e, mid + count * 0x14);
        if (b) operator delete[](b);
        *(char**)vec = nb;
        *(char**)((char*)vec + 4) = end;
        *(char**)((char*)vec + 8) = nb + newcap * 0x14;
    }
}

// @ 0x0053d1a0
void** UninitCopy20(void** out, void** first, void** last, void** dst)
{
    void** d = dst;
    for (; first != last; first += 5) {
        if (d) {
            d[0] = first[0]; d[1] = first[1]; d[2] = first[2]; d[3] = first[3]; d[4] = first[4];
        }
        d += 5;
    }
    *out = d;
    return out;
}

// @ 0x0053d230
void UninitFill20(void* dst, int n, void* src)
{
    int* d = (int*)dst;
    for (; n != 0; --n) {
        if (d) {
            d[0] = ((int*)src)[0]; d[1] = ((int*)src)[1]; d[2] = ((int*)src)[2];
            d[3] = ((int*)src)[3]; d[4] = ((int*)src)[4];
        }
        d += 5;
    }
}
