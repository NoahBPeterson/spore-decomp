// Slice s007cd6d0: cConfigManager startup/configure + eastl pair copy helpers + draw/animation.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-

#include "../s007ca950/s007ca950.h"

namespace EA { namespace ArgScript {
struct cArguments { void** MainArguments(int n); void** OptionArguments(const char* pName, int n); };
}}
namespace EA { namespace CommandLine {
struct cCommandLine { int FindSwitch(const wchar_t* pName, int a, int b, int c); };
}}

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

typedef eastl::pair<uint64, EA::AutoRefCount<SP::cPropertyList> > PropPair;

// ---------------------------------------------------------------- eastl pair helpers
namespace eastl {
// @ 0x007cd9d0
template <>
PropPair* uninitialized_copy_ptr<PropPair>(const PropPair* first, const PropPair* last, PropPair* result) {
    PropPair* d = result;
    for (; first != last; ++first, ++d)
        ::new ((void*)d) PropPair(*first);
    return d;
}
// @ 0x007cde80
template <> template <>
PropPair* copy_backward_impl<0, std::random_access_iterator_tag>::do_copy<PropPair*, PropPair*>(PropPair* first, PropPair* last, PropPair* result) {
    while (last != first) {
        --last;
        --result;
        ((uint32*)result)[0] = ((const uint32*)last)[0];
        ((uint32*)result)[1] = ((const uint32*)last)[1];
        SP::cPropertyList* pNew = last->second.mpObject;
        _ReadWriteBarrier();
        SP::cPropertyList* pOld = result->second.mpObject;
        if (pNew != pOld) {
            if (pNew) pNew->AddRef();
            result->second.mpObject = pNew;
            if (pOld) pOld->Release();
        }
    }
    return result;
}
}  // namespace eastl

// ---------------------------------------------------------------- externals
extern "C" void* _sAppProperties;                                    // 0x15fd918
void __cdecl    FUN_008476b0(void*, void*);                          // 0x008476b0
void __cdecl    FUN_006bb1c0(const char*, unsigned, unsigned, const char*); // 0x006bb1c0
void* __cdecl   CheatManager();                                      // 0x0067de20
namespace EA { namespace Messaging { void* __cdecl GetServer(); } }  // 0x00883860

// External __thiscall methods, modelled as members of placeholder classes.
struct ExtConfig {
    void Reset();                          // 0x007ccc30
    void LoadOptionSetup();                // 0x007cd340
    void AddResolutionOption();            // 0x007cccc0
    void LoadResolutionOptions();          // 0x007cce50
    void ApplyAllOptions();                // 0x007c9680
    void GatherInformation();              // 0x007cb590
    int  GetIntProperty(unsigned);         // 0x006a2660
    void SetIntProperty(unsigned, int);    // 0x006a1880
};
struct ExtCommandBase { void Ctor(); };                              // 0x0083c800
struct ExtCheatManager { void Register(const char*, void*, int); };  // vtable slot 0x18
struct ExtRandom { double RandomDoubleUniform(); };                  // 0x009360d0

// The "option" cheat object built by SetupParser: allocated with the EA
// allocator, base-constructed, then the derived vtable/owner are stored.
struct cCommandBase {
    int mPad[4];
    cCommandBase();
};
struct cOptionCheat : cCommandBase {
    int mParser;
    cOptionCheat(void* parser);
    static void* operator new(unsigned size, const char* name, int flags, unsigned debugFlags, const char* file, int line) {
        return ::operator new(size, name, flags, debugFlags, file, line);
    }
};
cOptionCheat::cOptionCheat(void* parser) : cCommandBase() {
    *(void**)this = (void*)0x14114c4;
    mParser = (int)parser;
}

struct cConfigManagerS {
    void Initialize();
    bool SetupParser(void* cmd, bool p3);
    void TryConfigure();
    bool Configure();
    void Unnamed960();
    void Unnamed990();
    bool Unnamed9C0();
    void UnnamedA70(float* v);
};

#define VTOBJ(p)      (*(void***)(p))
#define VTCALL0(p, s) ((void(__thiscall*)(void*))VTOBJ(p)[(s) / 4])

// ---------------------------------------------------------------- bespoke config startup
// @ 0x007cd6d0
void cConfigManagerS::Initialize()
{
    int* self = (int*)this;
    ((ExtConfig*)((char*)self + 0x20))->Reset();
    if (self[3] != 0) {                                              // +0x0c mFileParser
        ((ExtConfig*)self)->AddResolutionOption();
        ((ExtConfig*)self)->LoadResolutionOptions();
        VTCALL0((void*)self[3], 0x20)((void*)self[3]);
    } else {
        ((ExtConfig*)self)->LoadOptionSetup();
        ((ExtConfig*)self)->AddResolutionOption();
        ((ExtConfig*)self)->LoadResolutionOptions();
        FUN_008476b0((void*)self[4], (char*)self + 0x14);
    }
    char* pc = (char*)((void*(__thiscall*)(void*))VTOBJ((void*)self[4])[0x58 / 4])((void*)self[4]);
    if (((char*)self)[0x61] == 0 && *pc != 0)
        FUN_006bb1c0((const char*)0x1411ad8, 0x7d0, 1, 0);
    if (self[0xa8 / 4] >= 0) {
        int v = ((ExtConfig*)self[0xb0 / 4])->GetIntProperty(0x1a34e253u);
        int cur = self[0xa8 / 4];
        if (v > cur) ((ExtConfig*)self[0xb0 / 4])->SetIntProperty(0x1a34e253u, cur);
    }
    ((ExtConfig*)self)->ApplyAllOptions();
    if (!((char*)self)[0xac]) VTCALL0(self, 0x3c)(self);
    else                      VTCALL0(self, 0x40)(self);
}

// @ 0x007cd7a0
bool cConfigManagerS::SetupParser(void* cmd, bool param3)
{
    int* self = (int*)this;
    void* newProps = _sAppProperties;
    void* oldProps = (void*)self[0xb0 / 4];
    if (newProps != oldProps) {
        if (newProps) VTCALL0(newProps, 0x00)(newProps);
        self[0xb0 / 4] = (int)newProps;
        if (oldProps) VTCALL0(oldProps, 0x04)(oldProps);
    }
    if (((EA::CommandLine::cCommandLine*)cmd)->FindSwitch( L"safe", 0, 0, 0) != -1)
        ((char*)self)[0xac] = 1;
    if (((EA::CommandLine::cCommandLine*)cmd)->FindSwitch( L"showConfigAlerts", 0, 0, 0) != -1)
        ((char*)self)[0xad] = 1;
    ((char*)self)[0x60] = (char)param3;
    cOptionCheat* p = new ("App", 0, 0u, (const char*)0, 0) cOptionCheat(self);
    void* cm = CheatManager();
    ((ExtCheatManager*)cm)->Register("option", p, 0);
    ((ExtConfig*)self)->AddResolutionOption();
    ((ExtConfig*)self)->LoadResolutionOptions();
    return true;
}

// @ 0x007cd8b0
void cConfigManagerS::TryConfigure()
{
    int* self = (int*)this;
    void* fp = (void*)self[3];
    if (fp != 0) {
        if (((bool(__thiscall*)(void*))VTOBJ(fp)[0x28 / 4])(fp))
            Initialize();
    }
}

// @ 0x007cd8d0
bool cConfigManagerS::Configure()
{
    int* self = (int*)this;
    void* pl = (void*)self[4];
    if (pl != 0) {
        const char* v1 = ((char*)self)[0xac] ? "1" : "0";
        ((void(__thiscall*)(void*, const char*, const char*))VTOBJ(pl)[0x74 / 4])(pl, "safeMode", v1);
        const char* v2 = ((char*)self)[0xad] ? "1" : "0";
        pl = (void*)self[4];
        ((void(__thiscall*)(void*, const char*, const char*))VTOBJ(pl)[0x74 / 4])(pl, "showConfigAlerts", v2);
        ((ExtConfig*)((char*)self + 0x20))->GatherInformation();
        Initialize();
        return ((char*)self)[0x61] == 0;
    }
    ((ExtConfig*)self)->LoadOptionSetup();
    ((ExtConfig*)self)->AddResolutionOption();
    ((ExtConfig*)self)->LoadResolutionOptions();
    return true;
}

// @ 0x007cd960
void cConfigManagerS::Unnamed960()
{
    char* self = (char*)this;
    if (self[4] == 0) {
        void* s = EA::Messaging::GetServer();
        ((void(__thiscall*)(void*, char*, int))VTOBJ(s)[0x24 / 4])(s, self, *(int*)(self + 0x1c));
        self[4] = 1;
    }
}

// @ 0x007cd990
void cConfigManagerS::Unnamed990()
{
    char* self = (char*)this;
    if (self[4] != 0) {
        void* s = EA::Messaging::GetServer();
        ((void(__thiscall*)(void*, char*, int, int))VTOBJ(s)[0x2c / 4])(s, self, *(int*)(self + 0x1c), 0xffffd8f1);
        *(int*)(self + 0x1c) = 0;
        self[4] = 0;
    }
}

// @ 0x007cd9c0
bool cConfigManagerS::Unnamed9C0()
{
    int* p = *(int**)this;
    return *p == 0;
}

// @ 0x007cda70
void cConfigManagerS::UnnamedA70(float* v)
{
    unsigned char* self = (unsigned char*)this;
    float x = v[0] - *(float*)(self + 4);
    float y = v[1] - *(float*)(self + 8);
    float z = v[2] - *(float*)(self + 0xc);
    v[0] = x; v[1] = y; v[2] = z;
    float s = *(float*)(self + 0x10);
    if (s != 1.0f) {
        float inv = 1.0f / s;
        v[0] = x * inv; v[1] = y * inv; v[2] = z * inv;
    }
    if (self[0] & 2) {
        float a = v[0], b = v[1], c = v[2];
        v[0] = *(float*)(self + 0x1c) * c + *(float*)(self + 0x18) * b + *(float*)(self + 0x14) * a;
        v[1] = *(float*)(self + 0x28) * c + *(float*)(self + 0x24) * b + *(float*)(self + 0x20) * a;
        v[2] = *(float*)(self + 0x34) * c + *(float*)(self + 0x30) * b + *(float*)(self + 0x2c) * a;
    }
}

// @ 0x007cdb90
float __cdecl cConfigManagerUnnamedB90(float* param_1)
{
    double lo = param_1[0];
    double hi = param_1[1];
    double v = ((ExtRandom*)0x16778dc)->RandomDoubleUniform() * (hi - lo) + lo;
    return (float)v;
}
// @ 0x007cdbe0
void cConfigManagerUnnamedBE0(void*) {}
// @ 0x007cdcd0
void UpdateFromGroundCoverConfig(void*) {}
// @ 0x007cdd80
void cConfigManagerUnnamedD80(void*) {}
// @ 0x007cddc0
void cConfigManagerUnnamedDC0(void*) {}
// @ 0x007cde30
void cConfigManagerUnnamedE30(void*) {}
// @ 0x007cdee0
void TransformVectorByMatrix(void*, float*) {}
// @ 0x007cdff0
void UpdateFloatAnim(void*, void*, float) {}
