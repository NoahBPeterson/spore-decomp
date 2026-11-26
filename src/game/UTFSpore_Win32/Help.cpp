// src/game/UTFSpore_Win32/Help.cpp -- migrated from slice(s) s00840250 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Help.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int   __cdecl _stricmp(const char* a, const char* b);
extern "C" __declspec(dllimport) int   __cdecl tolower(int);
extern "C" int   __cdecl Vsnprintf8(char* buf, unsigned n, const char* fmt, void* args);   // 0x00938400
extern "C" unsigned int __cdecl strlen(const char*);
extern char gEmptyString[];
extern char gSprintfBuf[];      // 0x0164f780
extern char gSprintfAppendBuf[];  // 0x0164fb80
#include "eastl/allocator.h"

// ---- items of slice s00840250 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  uint8;
extern "C" __declspec(dllimport) int   __cdecl _stricmp(const char* a, const char* b);
extern "C" __declspec(dllimport) int   __cdecl tolower(int);
extern "C" int   __cdecl Vsnprintf8(char* buf, unsigned n, const char* fmt, void* args);   // 0x00938400
extern char gEmptyString[];
struct cError {
    char mData[0x10];
    cError(const char* fmt, ...);
    cError(const cError&);
};
namespace eastl {
struct allocator_s0084_0250 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0084_0250 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator_s0084_0250 mAllocator;
    string8_s0084_0250() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void assign(const char* first, const char* last);
    void append(const char* first, const char* last);
    void resize(unsigned n, char c);
    void append_sprintf_va_list(const char* fmt, void* args);
    ~string8_s0084_0250();
};
}
extern char gSprintfBuf[];      // 0x0164f780
extern char gSprintfAppendBuf[];  // 0x0164fb80
// ---- items of slice s00840250 end
// @ 0x008409b0
void __cdecl MakeCaseInsensitive(eastl::string8_s0084_0250* s)
{
    for (unsigned i = 0; i < (unsigned)(s->mpEnd - s->mpBegin); ++i)
        s->mpBegin[i] = (char)tolower(s->mpBegin[i]);
}

// @ 0x008409f0
int __cdecl StringConvert(int* out, int* in, char* name)
{
    (void)out; (void)in; (void)name; return 0;
}

// @ 0x00840bb0
int __cdecl ParseEnum(const char* name, int* table)
{
    while (*table) {
        if (_stricmp(name, (const char*)*table) == 0)
            return table[1];
        table += 2;
    }
    throw cError("Unknown enum '%s'", name);
}

// @ 0x00840c20
void __cdecl Sprintf(eastl::string8_s0084_0250* out, const char* fmt, ...)
{    char* args = (char*)&fmt + 4;
    Vsnprintf8(gSprintfBuf, 0x400, fmt, args);
    out->assign(gSprintfBuf, gSprintfBuf + strlen(gSprintfBuf));
}

// @ 0x00840c70
void __cdecl SprintfAppend(eastl::string8_s0084_0250* out, const char* fmt, ...)
{    char* args = (char*)&fmt + 4;
    Vsnprintf8(gSprintfAppendBuf, 0x400, fmt, args);
    out->append(gSprintfAppendBuf, gSprintfAppendBuf + strlen(gSprintfAppendBuf));
}

// @ 0x00840cc0
void __cdecl MakeCaseInsensitiveChars(char* p, int* s)
{ (void)p; (void)s; }

// @ 0x00840d50
struct FArgs_s00840d50 {
    virtual void f00();
    virtual void f04();
    virtual void f08();
    virtual void f0c();
    virtual void f10();
    virtual void f14();
    virtual void f18();
    virtual void f1c();
    virtual void f20();
    virtual void f24();
    virtual void f28();
    virtual void f2c();
    virtual void f30();
    virtual void f34();
    virtual void f38();
    virtual void f3c();
    virtual void f40();
    virtual void f44();
    virtual void f48();
    virtual void f4c();
    virtual void f50();
    virtual void f54();
    virtual void f58();
    virtual void f5c();
    virtual void f60();
    virtual void f64();
    virtual void f68();
    virtual void f6c();
    virtual void f70();
    virtual void f74();
    virtual void f78();
    virtual void f7c();
    virtual void f80();
    virtual void f84();
    virtual void f88();
    virtual void f8c();
    virtual void f90();
    virtual void f94();
    virtual float GetFloat(int index);   // +0x98
};
float __cdecl ParseRangedFloat(FArgs_s00840d50* args, int index, float lo, float hi)
{
    float v = args->GetFloat(index);
    if (lo > v || v > hi)
        throw cError("argument out of range: expecting [%g..%g], got %g", (double)lo, (double)hi, (double)v);
    return v;
}

// @ 0x00840dc0
struct Args_s00840dc0 {
    virtual void f00();
    virtual void f04();
    virtual void f08();
    virtual void f0c();
    virtual void f10();
    virtual void f14();
    virtual void f18();
    virtual void f1c();
    virtual void f20();
    virtual void f24();
    virtual void f28();
    virtual void f2c();
    virtual void f30();
    virtual void f34();
    virtual void f38();
    virtual void f3c();
    virtual void f40();
    virtual void f44();
    virtual void f48();
    virtual void f4c();
    virtual void f50();
    virtual void f54();
    virtual void f58();
    virtual void f5c();
    virtual void f60();
    virtual void f64();
    virtual void f68();
    virtual void f6c();
    virtual void f70();
    virtual void f74();
    virtual void f78();
    virtual void f7c();
    virtual void f80();
    virtual void f84();
    virtual void f88();
    virtual void f8c();
    virtual void f90();
    virtual void f94();
    virtual void f98();
    virtual int GetInt(int index);       // +0x9c
};
int __cdecl ParseRangedInt(Args_s00840dc0* args, int index, int lo, int hi)
{
    int v = args->GetInt(index);
    if (v >= lo && v <= hi)
        return v;
    throw cError("argument out of range: expecting [%d..%d], got %d", lo, hi, v);
}

// @ 0x00840e10
float* __cdecl ParseRangedVector3(float* out, int* expr, int arg, float lo, float hi)
{
    ((void(__thiscall*)(int*, float*, int))(*(void***)expr)[0xa8 / 4])(expr, out, arg);
    float x = out[0];
    if (x < lo || x > hi || out[1] < lo || out[1] > hi || out[2] < lo || out[2] > hi)
        throw cError("argument out of range: expecting components (%g..%g), got (%g, %g, %g)",
                     (double)lo, (double)hi, (double)x, (double)out[1], (double)out[2]);
    return out;
}

// @ 0x00840ec0
bool __cdecl StripCommentsAndWhiteSpace(uint8* s, int* out, int* depth)
{
    (void)s; (void)out; (void)depth; return false;
}

// @ 0x00841000
void __cdecl Output(int* expr, const char* fmt, ...)
{ (void)expr; (void)fmt; }
