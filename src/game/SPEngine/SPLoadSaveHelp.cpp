// src/game/SPEngine/SPLoadSaveHelp.cpp -- migrated from slice(s) s00695140, s00694210, s00693280, s006925c0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPLoadSaveHelp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cVarListSerializer.h"
#include "EA/Thread/Mutex.h"
#include "SP/cDataSerializationInfo.h"
#include "SP/cDataSerializerGeneric.h"
#include "SP/cJob.h"
#include "SP/cJobData.h"
#include "SP/cJobManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) long __cdecl atol(const char*);
extern "C" __declspec(dllimport) unsigned long __cdecl strtoul(const char*, char**, int);
extern "C" __declspec(dllimport) double __cdecl strtod(const char*, char**);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char*, const char*, ...);
extern void* g_RegVtbl;
#include <new>
#include <intrin.h>
#include "EA/Variant.h"
#include <wchar.h>

// ---- items of slice s006925c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) long __cdecl atol(const char*);
extern "C" __declspec(dllimport) unsigned long __cdecl strtoul(const char*, char**, int);
extern "C" __declspec(dllimport) double __cdecl strtod(const char*, char**);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char*, const char*, ...);
__declspec(noinline) long long FUN_0092d6f0(const char*, int, int);
__declspec(noinline) void* FUN_00920090();
struct cDataSerializationInfo {
    int mId;                    // +0x00
    int mDataSize;              // +0x04
    bool mbSerialized;          // +0x08
    char mPad09[3];
    void* mpBinderContext;      // +0x0c
    void* mpSerializer;         // +0x10
};
struct cDataSerializerGeneric {
    void* mpSerializer;         // +0x00
    int mId;                    // +0x04
    char mPad08[0x10];
    void* mpBinderContext;      // +0x18
    char mPad1c[8];
    void* mpWriteFunc;          // +0x24
    void* mpReadFunc;           // +0x28
    char mPad2c[0x10];
};
class cVarListSerializer {
public:
    char mPad00[0x10];
    cDataSerializationInfo mDataSerializationInfos[128]; // +0x10 (0x14 each)
    int mSerializableVarCount;  // +0xa00
    int mSerializedVarCount;    // +0xa04
    unsigned int mSignature;    // +0xa08
    void* mpObject;             // +0xa0c
    cDataSerializerGeneric* mpSerializerList; // +0xa10

    void Init(void* obj, cDataSerializerGeneric* list, unsigned int sig);
    bool Serialize(void* stream);
    void Unload();
    cVarListSerializer(void* obj, cDataSerializerGeneric* list, unsigned int sig);
};
bool EA_IO_WriteBytes(void*, const void*, int);
bool EA_IO_WriteUint16(void*, const void*, int, int);
bool EA_IO_WriteUint32(void*, const void*, int, int);
struct BlobRange { void* mpBegin; void* mpEnd; };
struct cRegNode { void* mpVtbl; cRegNode* mpNext; void* mpData; char mState; cRegNode* Construct(void* data); };
extern cRegNode* g_pRegList;   // 0x01600c58
extern void* g_RegVtbl;
// ---- items of slice s006925c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cRegNode* g_pRegList;   // 0x01600c58

// ---- items of slice s00693280 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" bool  EA_IO_ReadInt32(void* io, void* p, int n, int f);       // 93a780
extern "C" bool  EA_IO_ReadUint8(void* io, void* p, int n);              // 93a6c0
extern "C" void Str_DoInsertValue(char* dest, const char* src, int n);   // 11e0744
extern "C" void* __fastcall AutoRef_assign(void* dst, void* src);   // 0xb5f950
extern "C" void  FUN_00ac9480(void* a, void* b);                    // 0xac9480
extern "C" void* g_vtbl_1403970[];                                  // 0x1403970
struct Elem { unsigned int m0; unsigned int mId; unsigned int m2[13]; };
struct CString { char* begin; char* end; char* cap; void resize(int n, char c); };
struct Str16 { char* begin; char* end; char* cap; void* pad;
               void RangeInitialize(int n);
               void assign(const char* b, const char* e);
               Str16(const Str16& src); };
struct Hdr { unsigned int v[15]; };
struct Obj {
    Hdr h;
    unsigned int x;
    Str16 s1;
    Str16 s2;
    Obj(const Obj& src);
    Obj* copyAssign(const Obj& src);
};
Str16::Str16(const Str16& src)
{
    begin = 0; end = 0; cap = 0;
    int n = (int)(src.end - src.begin);
    RangeInitialize(n + 1);
    Str_DoInsertValue(begin, src.begin, n);
    end = begin + n;
    *end = 0;
}
typedef void  (__thiscall *VFn)(void*);
typedef bool  (__thiscall *VFnB)(void*);
#define VTABLE(o) (*(void***)(o))
static void vcall4(void* o)  { ((VFn)  VTABLE(o)[1])(o); }   // release (+4)
static bool vcall18(void* o) { return ((VFnB)VTABLE(o)[6])(o); }
static void vcall14(void* o) { ((VFn)  VTABLE(o)[5])(o); }
struct C3 {
    void* vtbl;   // +0
    void* p4;     // +4
    void* p8;     // +8
    int  bindA(void* obj, void* a, void* b, void* c);   // 0x6939b0
    int  bindB(void* obj, void* a, void* b, void* c);   // 0x693aa0
    C3*  ctorA(void* a, void* b, void* c, void* d);     // 0x693cd0
    C3*  ctorB(void* a, void* b, void* c, void* d);     // 0x693d60
};
// ---- items of slice s00693280 end

// ---- items of slice s00694210 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void operator_delete_arr(void* p);                    // 0xf47380
extern "C" void EA_sprintf(void* dst, const char* fmt, ...);     // 0x472fe0 basic_string::sprintf
extern "C" char gA[];   // 0x01667bac
extern "C" char gB[];   // 0x01667bae
typedef unsigned int u32;
struct CString_s0069_4210 {
    char* begin;
    char* end;
    char* cap;
    void assign(const char* b, const char* e);
};
extern "C" void  FUN_00693b90(Elem* first, Elem* last, int cmp); // 0x693b90
extern "C" void  FUN_00693c10(Elem* first, Elem* last, int cmp); // 0x693c10
extern "C" void  FUN_00693280(Elem* first, int top, int heapSize, int position, Elem value, int cmp); // 0x693280
extern "C" Elem* FUN_00694210(Elem* first, Elem* last, Elem value); // 0x694210
extern "C" void  FUN_00694270(Elem* first, Elem* mid, Elem* last, int cmp);   // 0x694270
extern "C" void  FUN_00694d00(Elem* first, Elem* last, int depth, int cmp);   // 0x694d00
extern "C" void  FUN_00692cb0(Elem* first, Elem* mid, int cmp);               // 0x692cb0
extern "C" void  FUN_00692d20(Elem* mid, Elem* last, int cmp);                // 0x692d20
struct Str16_s0069_4210 {
    char* begin;
    char* end;
    char* cap;
    void* pad;
    void assign(const char* b, const char* e);
};
struct Hdr15 { u32 v[15]; };
struct Obj60 { Hdr15 h; u32 x; Str16_s0069_4210 s1; Str16_s0069_4210 s2; };
struct StrBuf { char* begin; char* end; char* cap; void assign(const char* b, const char* e); void dtor(); };
extern "C" StrBuf* EA_ConvertToString8(StrBuf* out, void* v);
struct VStream {                       // IO stream: Read(buf, size) at vtable +0x30
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10();
    virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void s28(); virtual void s2c();
    virtual int Read(void* buf, int size);          // +0x30
};
struct Variant {
    char           pad0[4];            // +0 data (pointer / scalar), +4 element size, +8 element count
    int            mElemSize;          // +4
    int            mElemCount;         // +8
    int            padc;
    unsigned short mFlags;             // +0x10
    unsigned short mTypeId;            // +0x12
    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant() { if (mFlags & 4) Destruct(0); }
    Variant& operator=(const Variant& v);          // 0x00542b80
    void Destruct(int a);                          // 0x0093db80
};
extern "C" bool FUN_0093a700(VStream* io, void* p, int n, int endian);   // ReadUInt16
extern "C" bool FUN_0093a780(VStream* io, void* p, int n, int endian);   // ReadInt32
extern "C" bool FUN_0093ac80(VStream* io, void* v);                      // ReadBool
extern "C" bool R8a(VStream* io, void* v);                      // @ 0x00593840
extern "C" bool R8b(VStream* io, void* v);                      // @ 0x00593840
extern "C" bool R16a(VStream* io, void* v, int endian);         // @ 0x00692720
extern "C" bool R16b(VStream* io, void* v, int endian);         // @ 0x00692720
extern "C" bool R16c(VStream* io, void* v, int endian);         // @ 0x00692720
extern "C" bool R32a(VStream* io, void* v, int endian);         // @ 0x00692740
extern "C" bool R32b(VStream* io, void* v, int endian);         // @ 0x00692740
extern "C" bool R32c(VStream* io, void* v, int endian);         // @ 0x00692740
extern "C" bool R64a(VStream* io, void* v, int endian);         // @ 0x00692760
extern "C" bool R64b(VStream* io, void* v, int endian);         // @ 0x00692760
extern "C" bool R64c(VStream* io, void* v, int endian);         // @ 0x00692760
extern "C" bool FUN_00693c70_s0069_4210(VStream* io, void* v);                      // read narrow string
extern "C" bool FUN_00693890(VStream* io, void* v);                      // read wide string
void* operator new(unsigned int size, const char* name, int flags, unsigned int dflags,
                   const char* file, int line);                          // 0x00f473a0
struct Big2 {
    u32 f0;
    u32 f4, f8, fc, f10, f14, f18, f1c, f20, f24, f28;
    void* f2c; void* f30; void* f34; u32 f38;
    void* f3c; void* f40; void* f44; u32 f48;
    void* f4c; void* f50; void* f54; u32 f58;
    u32 f5c, f60, f64, f68, f6c, f70;
    void init(void* a);
};
// ---- items of slice s00694210 end

// ---- items of slice s00695140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_alloc6(unsigned sz, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern "C" void  FUN_00694320(char* first, char* last, char* dst);   // 0x694320
extern "C" char* FUN_00694e00(char* first, char* last, char* out);  // 0x694e00
extern char gEmptyString[];                     // @ 0x1667bac
extern "C" char g_bTextFlag;                        // 0x01600c5c
struct Sorter {
    void* run(char* first);
};
struct Vec60 {
    char* begin; char* end; char* cap;
    void reserve(unsigned int n);
};
namespace eastl {
inline size_t CharStrlen(const char* p)
{
    const char* pCurrent = p;
    while (*pCurrent++) {}
    return (size_t)(pCurrent - p - 1);
}
}
namespace eastl {
struct allocator_s0069_5140 {
    void deallocate(void* p, size_t) { delete[] (char*)p; }
};
}
namespace eastl {
struct basic_string_s0069_5140 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0069_5140 mAllocator;
    basic_string_s0069_5140() : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(); }
    ~basic_string_s0069_5140() { DeallocateSelf(); }
    void AllocateSelf() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void DoFree(char* p, size_t n) { if (p) mAllocator.deallocate(p, n); }
    basic_string_s0069_5140& assign(const char* pBegin, const char* pEnd);          // @ 0x454cb0
    basic_string_s0069_5140& assign(const char* p)
    {
        return assign(p, p + CharStrlen(p));
    }
};
}
namespace SP {
struct cDataSerializerGeneric_s0069_5140 {
    const char* mpStaticFieldName;      // +0x00
    unsigned int mId;                   // +0x04
    unsigned int mData[4];              // +0x08
    void* mpBinderContext;              // +0x18
    void* mpSetDefaultValueFunc;        // +0x1c
    void* (*mpDataBinderFunc)(cDataSerializerGeneric_s0069_5140*);   // +0x20
    void* mpReadFunc;                   // +0x24
    void* mpWriteFunc;                  // +0x28
    void* mpReadStringFunc;             // +0x2c
    void (*mpWriteStringFunc)(eastl::basic_string_s0069_5140*, void*);   // +0x30
    void (*mpWriteWideFunc)(void*, void*);   // +0x34
    void* mpPad38;                      // +0x38
};
}
namespace SP {
struct cDataSerializationInfo_s0069_5140 {
    unsigned int mId;                   // +0x0
    unsigned int mDataSize;             // +0x4
    bool mbSerialized;                  // +0x8
    void* mpBinderContext;              // +0xc
    cDataSerializerGeneric_s0069_5140* mpSerializer;   // +0x10
};
}
void* DefaultDataBinder(SP::cDataSerializerGeneric_s0069_5140*);   // 0x011874d0
struct FieldEntryBase : SP::cDataSerializerGeneric_s0069_5140 {
    FieldEntryBase()
    {
        mpStaticFieldName = "field_name";
        mId = 0xffffffff;
        mData[0] = 0;
        mpBinderContext = 0;
        mpSetDefaultValueFunc = 0;
        mpDataBinderFunc = (void* (*)(SP::cDataSerializerGeneric_s0069_5140*))DefaultDataBinder;
        mpReadFunc = 0; mpWriteFunc = 0; mpReadStringFunc = 0; mpWriteStringFunc = 0;
        mpWriteWideFunc = 0; mpPad38 = 0;
    }
};
struct FieldEntry : FieldEntryBase {
    void* mpObject;                     // +0x3c
    eastl::basic_string_s0069_5140 mName;          // +0x40
    eastl::basic_string_s0069_5140 mValue;         // +0x50
};
struct FieldVec {
    FieldEntry* mpBegin; FieldEntry* mpEnd; FieldEntry* mpCapacity;
    void reserve(unsigned n);                       // 0x00695490 (thiscall)
    void push_back(const FieldEntry& e);            // 0x006956f0 (thiscall, ret 4)
};
struct WStrTmp {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; eastl::allocator_s0069_5140 mAllocator;
    WStrTmp() {}
    ~WStrTmp()
    {
        if ((int)(((unsigned)((char*)mpCapacity - (char*)mpBegin)) & 0xfffffffeu) > 2 && mpBegin)
            mAllocator.deallocate(mpBegin, 0);
    }
};
struct CharString : eastl::basic_string_s0069_5140 {
    CharString& sprintf(const char* fmt, ...);      // 0x00472fe0 (cdecl, this pushed)
};
WStrTmp ConvertToString16(const eastl::basic_string_s0069_5140& s);       // 0x0093c6d0 (cdecl, sret first)
struct WStrTmpVec { void push_back(const WStrTmp& s); };          // 0x00553f10 (thiscall, ret 4)
struct SubA { void Reserve(int n); };                       // 0x006b58c0 (thiscall, ret 4)
struct SubB { void Reserve(int n); };                       // 0x006953b0 (thiscall, ret 4)
struct FieldReport {
    char pad0[4];
    SubA mFields;                       // +0x04
    char pad1[0x5c - 0x04 - 1];
    SubB mTexts;                        // +0x5c
};
namespace SP {
struct cVarListSerializer_s0069_5140 {
    cDataSerializationInfo_s0069_5140 mDataSerializationInfos[128];   // +0x0
    int mSerializableVarCount;                              // +0xa00
    int mSerializedVarCount;                                // +0xa04
    unsigned int mSignature;                                // +0xa08
    void* mpObject;                                         // +0xa0c
    cDataSerializerGeneric_s0069_5140* mpSerializerList;               // +0xa10
    int GetFields(FieldVec& out);  // 0x00695960 (SP::cVarListSerializer::GetFields)
    int Execute(FieldReport* report);
};
}
struct Obj60_s0069_5140 {
    char d[0x60];
    Obj60_s0069_5140(const Obj60_s0069_5140& o);                                          // 0x006940d0 (thiscall, ret 4)
    Obj60_s0069_5140& operator=(const Obj60_s0069_5140& o);                               // 0x006941c0 (thiscall, ret 4)
};
Obj60_s0069_5140* UninitCopy60(Obj60_s0069_5140* first, Obj60_s0069_5140* last, Obj60_s0069_5140* dst);         // 0x00694320 (cdecl)
Obj60_s0069_5140* UninitFill60(Obj60_s0069_5140* first, Obj60_s0069_5140* last, Obj60_s0069_5140* dst);         // 0x00694e00 (cdecl)
void   CopyBackward60(Obj60_s0069_5140* first, Obj60_s0069_5140* last, Obj60_s0069_5140* dstEnd);    // 0x006943b0 (cdecl)
struct Vec60b {
    Obj60_s0069_5140* mpBegin; Obj60_s0069_5140* mpEnd; Obj60_s0069_5140* mpCapacity;
    Obj60_s0069_5140* DoAllocate(unsigned n)
    {
        return n ? (Obj60_s0069_5140*)EASTL_alloc6(n * 0x60, "App", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    }
    void DoInsertValue(Obj60_s0069_5140* position, const Obj60_s0069_5140& value);
};
// ---- items of slice s00695140 end

// @ 0x00692880
void cVarListSerializer::Init(void* obj, cDataSerializerGeneric* list, unsigned int sig)
{
    mpObject = obj;
    mpSerializerList = list;
    mSerializableVarCount = 0;
    mSerializedVarCount = 0;
    mSignature = sig;
    cDataSerializerGeneric* p = list;
    while (p->mpWriteFunc != 0 && p->mpReadFunc != 0 && mSerializableVarCount < 0x80) {
        cDataSerializationInfo* info = &mDataSerializationInfos[mSerializableVarCount];
        ++mSerializableVarCount;
        info->mpSerializer = p;
        info->mbSerialized = false;
        info->mDataSize = 0;
        info->mId = p->mId;
        info->mpBinderContext = p->mpBinderContext;
        p = (cDataSerializerGeneric*)((char*)p + 0x3c);
    }
}

// @ 0x00692c50
void cVarListSerializer::Unload()
{
    for (int i = 0; i < mSerializableVarCount; ++i) {
        cDataSerializationInfo& info = mDataSerializationInfos[i];
        if (!info.mbSerialized) {
            cDataSerializerGeneric* p = (cDataSerializerGeneric*)info.mpSerializer;
            if (p != 0) {
                void* save = p->mpBinderContext;
                if (save == 0) p->mpBinderContext = mpObject;
                ((void(*)(void*))p->mpBinderContext)(save);
                p->mpBinderContext = info.mpBinderContext;
            }
        }
    }
}

// @ 0x00692ca0
int Info_AddOffset(void* p)
{
    return *(int*)((char*)p + 0x18) + *(int*)((char*)p + 8);
}

// @ 0x00692cb0
void SortRecords_A(void* first, void* last)
{
    char tmp[0x3c];
    for (char* i = (char*)first; i != last; i += 0x3c) {
        __movsb((unsigned char*)tmp, (unsigned char*)i, 0x3c);
        char* j = i;
        while (j != first && ((int*)tmp)[1] < *(int*)(j - 0x38)) {
            __movsb((unsigned char*)j, (unsigned char*)(j - 0x3c), 0x3c);
            j -= 0x3c;
        }
        __movsb((unsigned char*)j, (unsigned char*)tmp, 0x3c);
    }
}

// @ 0x00692e00
unsigned char WriteBlob32(void* writer, BlobRange* range)
{
    int size = (int)((char*)range->mpEnd - (char*)range->mpBegin);
    int tmp = size;
    if (!EA_IO_WriteUint32(writer, &tmp, 1, 0)) return 0;
    if (size != 0) return (unsigned char)EA_IO_WriteBytes(writer, range->mpBegin, size);
    return 1;
}

// @ 0x00692e50
unsigned char WriteBlob16(void* writer, BlobRange* range)
{
    int size = (int)((char*)range->mpEnd - (char*)range->mpBegin) >> 1;
    int tmp = size;
    if (!EA_IO_WriteUint32(writer, &tmp, 1, 0)) return 0;
    if (size != 0) return (unsigned char)EA_IO_WriteUint16(writer, range->mpBegin, size, 1);
    return 1;
}

// @ 0x00692ee0
void RegList_Resolve()
{
    for (cRegNode* p = g_pRegList; p != 0; p = p->mpNext) {
        if (!p->mState) {
            void* q = (void*)FUN_00920090();
            if (q) {
                void* r = (void*)FUN_00920090();
                bool v = ((bool(*)(cRegNode*, void*))(((void**)r)[1]))(p, p->mpData);
                p->mState = v;
            }
        }
    }
}

// @ 0x00692f20
void RegList_Release()
{
    for (cRegNode* p = g_pRegList; p != 0; p = p->mpNext) {
        if (p->mState) {
            void* q = (void*)FUN_00920090();
            if (q) {
                void* r = (void*)FUN_00920090();
                bool v = ((bool(*)(cRegNode*))(((void**)r)[2]))(p);
                p->mState = (v == 0);
            }
        }
    }
}

// @ 0x00692f60
cRegNode* cRegNode::Construct(void* data)
{
    mpVtbl = (void*)&g_RegVtbl;
    mpNext = 0;
    mpData = data;
    mState = 0;
    if (g_pRegList != 0) mpNext = g_pRegList;
    g_pRegList = this;
    return this;
}

// @ 0x00692f90
cVarListSerializer* cVarListSerializer_Construct(cVarListSerializer* self, void* obj, cDataSerializerGeneric* list, unsigned int sig)
{
    self->Init(obj, list, sig);
    return self;
}

// @ 0x00692fb0
void ClearBuffer(signed char** p)
{
    if (*p != (signed char*)p[1]) {
        **p = 0;
        p[1] = *p;
    }
}

// @ 0x00692fd0
void ParseInt64(const char** src, long long* out)
{
    const char* s = src[0];
    out[0] = FUN_0092d6f0(s, 0, 10);
}

// @ 0x00692ff0
void ParseLong(const char** src, long* out)
{ const char* s = src[0]; out[0] = atol(s); }

// @ 0x00693010
void ParseShort(const char** src, short* out)
{ const char* s = src[0]; out[0] = (short)atol(s); }

// @ 0x00693030
void ParseUShort(const char** src, unsigned short* out)
{ const char* s = src[0]; out[0] = (unsigned short)strtoul(s, 0, 10); }

// @ 0x00693050
void ParseChar(const char** src, signed char* out)
{ const char* s = src[0]; out[0] = (signed char)atol(s); }

// @ 0x00693070
void ParseUChar(const char** src, unsigned char* out)
{ const char* s = src[0]; out[0] = (unsigned char)strtoul(s, 0, 10); }

// @ 0x00693090
void ParseULong(const char** src, unsigned long* out)
{ const char* s = src[0]; out[0] = strtoul(s, 0, 10); }

// @ 0x006930b0
void ParseFloat(const char** src, float* out)
{
    char* end;
    double v = strtod(src[0], &end);
    out[0] = (float)v;
}

// @ 0x006930d0
void ParseVector2(const char** src, float* out)
{ sscanf(*src, "%f,%f", out, out + 1); }

// @ 0x006930f0
void ParseVector3(const char** src, float* out)
{ sscanf(*src, "%f,%f,%f", out, out + 1, out + 2); }

// @ 0x00693120
void ParseVector4(const char** src, float* out)
{ sscanf(*src, "%f,%f,%f", out, out + 1, out + 2, out + 3); }

// @ 0x00693150
void ParseColorRGB(const char** src, unsigned int* out)
{
    sscanf(*src, "0x%08x,0x%08x,0x%08x", out, out + 2, out + 1);
}

// @ 0x00693320
extern "C" void FUN_00693280(Elem* first, int topPosition, int heapSize, int position, Elem value, int cmp);
extern "C" __declspec(noinline) void FUN_00693320(Elem* first, Elem* last, int cmp)
{
    Elem value = *(last - 1);
    *(last - 1) = *first;
    int n = (int)((char*)last - (char*)first) / 60 - 1;
    FUN_00693280(first, 0, n, 0, value, cmp);
}

// @ 0x00693900
extern "C" void __fastcall FUN_00693900(C3* self)
{
    self->vtbl = g_vtbl_1403970;
    if (self->p8)
    {
        if (vcall18(self->p8))
            vcall14(self->p8);
    }
    if (self->p8)
    {
        void* t = self->p8;
        self->p8 = 0;
        vcall4(t);
    }
    if (self->p4)
    {
        void* t = self->p4;
        self->p4 = 0;
        vcall4(t);
    }
}

// @ 0x006939b0
int C3::bindA(void* obj, void* a, void* b, void* c)
{
    if (obj != 0)
    {
        int args[3];
        args[0] = (int)b;
        args[1] = (int)a;
        args[2] = (int)c;
        void* out = 0;
        bool ok = ((bool(__thiscall*)(void*, void*, void**))VTABLE(obj)[6])(obj, args, &out);
        if (ok)
        {
            if (!((bool(__thiscall*)(void*))VTABLE(out)[7])(out))
            {
                ((void(__thiscall*)(void*, void*))VTABLE(obj)[7])(obj, out);
            }
            else
            {
                AutoRef_assign(&p4, obj);
                FUN_00ac9480(&p8, &out);
            }
        }
        if (out)
            vcall4(out);
    }
    return (p4 != 0 && p8 != 0) ? 1 : 0;
}

// @ 0x00693aa0
int C3::bindB(void* obj, void* a, void* b, void* c)
{
    if (obj != 0)
    {
        int args[3];
        args[0] = (int)b;
        args[1] = (int)a;
        args[2] = (int)c;
        void* out = 0;
        bool ok = ((bool(__thiscall*)(void*, void*, void**, int))VTABLE(obj)[9])(obj, args, &out, 1);
        if (ok)
        {
            if (!((bool(__thiscall*)(void*))VTABLE(out)[7])(out))
            {
                ((void(__thiscall*)(void*, void*))VTABLE(obj)[10])(obj, out);
            }
            else
            {
                AutoRef_assign(&p4, obj);
                FUN_00ac9480(&p8, &out);
            }
        }
        if (out)
            vcall4(out);
    }
    return (p4 != 0 && p8 != 0) ? 1 : 0;
}

// @ 0x00693b90
extern "C" void FUN_00693b90(Elem* first, Elem* last, int cmp)
{
    int count = (int)((char*)last - (char*)first) / 60;
    if (count < 2)
        return;
    int parent = ((count - 2) >> 1) + 1;
    do
    {
        --parent;
        Elem value = first[parent];
        FUN_00693280(first, parent, count, parent, value, cmp);
    } while (parent != 0);
}

// @ 0x00693c10
extern "C" void FUN_00693c10(Elem* first, Elem* last, int cmp)
{
    int count = (int)((char*)last - (char*)first) / 60;
    while (count > 1)
    {
        FUN_00693320(first, last, cmp);
        last = (Elem*)((char*)last - 60);
        count = (int)((char*)last - (char*)first) / 60;
    }
}

// @ 0x00693c70
extern "C" bool FUN_00693c70(void* io, CString* str)
{
    if (str->begin != str->end)
    {
        *str->begin = 0;
        str->end = str->begin;
    }
    int n;
    if (!EA_IO_ReadInt32(io, &n, 1, 0))
        return false;
    if (n != 0)
    {
        str->resize(n, 0);
        char* begin = str->begin;
        return EA_IO_ReadUint8(io, begin, n);
    }
    return true;
}

// @ 0x00693cd0
C3* C3::ctorA(void* a, void* b, void* c, void* d)
{
    vtbl = g_vtbl_1403970;
    p4 = 0;
    p8 = 0;
    bindA(a, b, d, c);
    return this;
}

// @ 0x00693d60
C3* C3::ctorB(void* a, void* b, void* c, void* d)
{
    vtbl = g_vtbl_1403970;
    p4 = 0;
    p8 = 0;
    bindB(a, b, d, c);
    return this;
}

// @ 0x006940d0
Obj::Obj(const Obj& src)
: h(src.h), x(src.x), s1(src.s1), s2(src.s2)
{
}

// @ 0x00694210
Elem* FUN_00694210(Elem* first, Elem* last, Elem value)
{
    for (;;)
    {
        while (first->mId < value.mId)
            ++first;
        do { --last; } while (value.mId < last->mId);
        if (first >= last)
            break;
        Elem tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
    return first;
}

// @ 0x00694270
void FUN_00694270(Elem* first, Elem* mid, Elem* last, int cmp)
{
    FUN_00693b90(first, mid, cmp);
    for (Elem* i = mid; i < last; ++i)
    {
        if (i->mId < first->mId)
        {
            Elem value = *i;
            *i = *first;
            int n = (int)((char*)mid - (char*)first) / 60;
            FUN_00693280(first, 0, n, 0, value, cmp);
        }
    }
    FUN_00693c10(first, mid, cmp);
}

// @ 0x006943b0
extern "C" Obj60* FUN_006943b0(Obj60* first, Obj60* last, Obj60* out)
{
    while (last != first)
    {
        --last;
        --out;
        out->h = last->h;
        out->x = last->x;
        if (&last->s1 != &out->s1)
            out->s1.assign(last->s1.begin, last->s1.end);
        if (&last->s2 != &out->s2)
            out->s2.assign(last->s2.begin, last->s2.end);
    }
    return out;
}

// @ 0x00694440
bool FUN_00694440(VStream* io, Variant* v, int endian)
{
    if (v->mTypeId != 0) {
        Variant tmp;
        *v = tmp;
    }
    bool ok;
    bool bResult;
    if (FUN_0093a700(io, &v->mTypeId, 1, endian) && FUN_0093a700(io, &v->mFlags, 1, endian))
        ok = true;
    else
        ok = false;

    if ((v->mFlags & 0x30) == 0) {
        switch (v->mTypeId) {
        case 1:
            bResult = ok && FUN_0093ac80(io, v);
            break;
        case 2: case 6:
            bResult = ok && R8a(io, v);
            break;
        case 3: case 8:
            bResult = ok && R16a(io, v, endian);
            break;
        case 5:
            bResult = ok && R8b(io, v);
            break;
        case 7:
            bResult = ok && R16b(io, v, endian);
            break;
        case 9:
            bResult = ok && R32a(io, v, endian);
            break;
        case 10:
            bResult = ok && R32b(io, v, endian);
            break;
        case 11:
            bResult = ok && R64a(io, v, endian);
            break;
        case 12:
            bResult = ok && R64b(io, v, endian);
            break;
        case 13:
            bResult = ok && R32c(io, v, endian);
            break;
        case 14:
            bResult = ok && R64c(io, v, endian);
            break;
        case 18:
            ((void**)v)[0] = gA;
            ((void**)v)[1] = gA;
            ((void**)v)[2] = gA + 1;
            bResult = ok && FUN_00693c70_s0069_4210(io, v);
            break;
        case 19:
            ((void**)v)[0] = gA;
            ((void**)v)[1] = gA;
            ((void**)v)[2] = gB;
            bResult = ok && FUN_00693890(io, v);
            break;
        case 17:
            v->mFlags = 0;
            v->mTypeId = 0;
            bResult = false;
            break;
        default:
            if (ok && io->Read(v, 0x10) != 0)
                bResult = true;
            else
                bResult = false;
            v->mFlags &= 0xfff2;
            break;
        }
        return bResult;
    } else {
        if ((v->mFlags & 0x40) == 0) {
            if (ok && FUN_0093a780(io, &v->mElemCount, 1, endian) && FUN_0093a780(io, &v->mElemSize, 1, endian))
                bResult = true;
            else
                bResult = false;
            char* p = (char*)operator new(v->mElemSize * v->mElemCount, "App/PropertyList/Variant/PointerPtr", 0, 0, 0, 0);
            char* end = p + v->mElemCount * v->mElemSize;
            *(char**)v = p;
            if (p < end) {
                do {
                    switch (v->mTypeId) {
                    case 1:
                        if (!bResult || !FUN_0093ac80(io, p)) goto fail;
                        bResult = true;
                        break;
                    case 2: case 6:
                        if (!bResult || !R8a(io, p)) goto fail;
                        bResult = true;
                        break;
                    case 3:
                        if (!bResult || !R16a(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 5:
                        if (!bResult || !R8b(io, p)) goto fail;
                        bResult = true;
                        break;
                    case 7:
                        if (!bResult || !R16b(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 8:
                        if (!bResult || !R16c(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 9:
                        if (!bResult || !R32a(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 10:
                        if (!bResult || !R32b(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 11:
                        if (!bResult || !R64a(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 12:
                        if (!bResult || !R64b(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 13:
                        if (!bResult || !R32c(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 14:
                        if (!bResult || !R64c(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 18:
                        if (p) {
                            ((void**)p)[0] = gA;
                            ((void**)p)[1] = gA;
                            ((void**)p)[2] = gA + 1;
                        }
                        if (!bResult || !FUN_00693c70_s0069_4210(io, p)) goto fail;
                        bResult = true;
                        break;
                    case 19:
                        if (p) {
                            ((void**)p)[0] = gA;
                            ((void**)p)[1] = gA;
                            ((void**)p)[2] = gB;
                        }
                        if (!bResult || !FUN_00693890(io, p)) goto fail;
                        bResult = true;
                        break;
                    case 17:
                        v->mFlags = 0;
                        v->mTypeId = 0;
                        operator_delete_arr(*(void**)v);
                    fail:
                        bResult = false;
                        break;
                    case 16:
                        if (!bResult || io->Read(p, v->mElemSize) == 0) goto fail;
                        bResult = true;
                        break;
                    default:
                        if (bResult && io->Read(p, v->mElemSize) != 0)
                            bResult = true;
                        else
                            bResult = false;
                        v->mFlags &= 0xfffe;
                        break;
                    }
                    p += v->mElemSize;
                } while (p < end);
            }
            return bResult;
        }
        v->mFlags = 0;
        v->mTypeId = 0;
    }
    return false;
}

// @ 0x00694bf0
extern "C" void FUN_00694bf0(CString_s0069_4210* dst, CString_s0069_4210* src)
{
    if (src != dst)
        dst->assign(src->begin, src->end);
}

// @ 0x00694c10
extern "C" void FUN_00694c10(StrBuf* dst, void* v)
{
    StrBuf tmp;
    tmp.begin = 0;
    tmp.end = 0;
    tmp.cap = 0;
    StrBuf* r = EA_ConvertToString8(&tmp, v);
    if (r != dst)
        dst->assign(r->begin, r->end);
    tmp.dtor();
}

// @ 0x00694d00
void FUN_00694d00(Elem* first, Elem* last, int depth, int cmp)
{
    int len = (int)((char*)last - (char*)first) / 60;
    for (;;)
    {
        if (len < 0x1d || depth < 1)
        {
            if (depth == 0)
                FUN_00694270(first, last, last, cmp);
            return;
        }
        Elem* midp = first + len / 2;
        u32 a = first->mId;
        u32 b = midp->mId;
        u32 c = last[-1].mId;
        Elem* piv;
        if (a < b)
            piv = (b < c) ? midp : (a < c ? last - 1 : first);
        else
            piv = (a < c) ? first : (b < c ? last - 1 : midp);
        Elem* cut = FUN_00694210(first, last, *piv);
        --depth;
        FUN_00694d00(cut, last, depth, cmp);
        len = (int)((char*)cut - (char*)first) / 60;
        last = cut;
    }
}

// @ 0x00694e00
extern "C" char* FUN_00694e00(char* first, char* last, char* out)
{
    while (first != last)
    {
        char* p = *(char**)(first + 0x50);
        if ((*(char**)(first + 0x58) - p) > 1 && p != 0)
            operator_delete_arr(p);
        p = *(char**)(first + 0x40);
        if ((*(char**)(first + 0x48) - p) > 1 && p != 0)
            operator_delete_arr(p);
        first += 0x60;
        out += 0x60;
    }
    return out;
}

// @ 0x00694e60
void Big2::init(void* a)
{
    f0 = (u32)a;
    f4 = f8 = fc = 0;
    f18 = f1c = f20 = 0;
    f2c = gA;
    f30 = gA;
    f34 = gB;
    f3c = gA;
    f40 = gA;
    f44 = gB;
    f4c = gA;
    f50 = gA;
    f54 = gB;
    f5c = f60 = f64 = 0;
    f70 = 0;
}

// @ 0x00694ec0
extern "C" void FUN_00694ec0(void* dst, unsigned __int64* p)
{ EA_sprintf(dst, "%I64u", *p); }

// @ 0x00694ee0
extern "C" void FUN_00694ee0(void* dst, unsigned int* p)
{ EA_sprintf(dst, "%u", *p); }

// @ 0x00694f00
extern "C" void FUN_00694f00(void* dst, int* p)
{ EA_sprintf(dst, "%d", *p); }

// @ 0x00694f20
extern "C" void FUN_00694f20(void* dst, short* p)
{ EA_sprintf(dst, "%d", (int)*p); }

// @ 0x00694f40
extern "C" void FUN_00694f40(void* dst, unsigned short* p)
{ EA_sprintf(dst, "%d", (int)*p); }

// @ 0x00694f60
extern "C" void FUN_00694f60(void* dst, signed char* p)
{ EA_sprintf(dst, "%d", (int)*p); }

// @ 0x00694f80
extern "C" void FUN_00694f80(void* dst, unsigned char* p)
{ EA_sprintf(dst, "%d", (int)*p); }

// @ 0x00694fa0
extern "C" void FUN_00694fa0(void* dst, unsigned char* p)
{ EA_sprintf(dst, "%d", (int)*p); }

// @ 0x00694fc0
extern "C" void FUN_00694fc0(void* dst, float* p)
{ EA_sprintf(dst, "%f", (double)*p); }

// @ 0x00694fe0
extern "C" void FUN_00694fe0(void* dst, float* p)
{ EA_sprintf(dst, "%f,%f", (double)p[0], (double)p[1]); }

// @ 0x00695010
extern "C" void FUN_00695010(void* dst, float* p)
{ EA_sprintf(dst, "%f,%f,%f", (double)p[0], (double)p[1], (double)p[2]); }

// @ 0x00695040
extern "C" void FUN_00695040(void* dst, float* p)
{ EA_sprintf(dst, "%f,%f,%f,%f", (double)p[0], (double)p[1], (double)p[2], (double)p[3]); }

// @ 0x00695080
extern "C" void FUN_00695080(void* dst, unsigned int* p)
{ EA_sprintf(dst, "0x%08x,0x%08x,0x%08x", p[0], p[2], p[1]); }

// @ 0x006950b0
void FUN_006950b0(Elem* first, Elem* last, int cmp)
{
    if (first == last)
        return;
    int n = (int)((char*)last - (char*)first) / 60;
    int depth = 0;
    for (int t = n; t != 0; t >>= 1)
        ++depth;
    FUN_00694d00(first, last, depth * 2 - 2, cmp);
    if (n > 0x1c)
    {
        FUN_00692cb0(first, first + 0x1c, cmp);
        FUN_00692d20(first + 0x1c, last, cmp);
        return;
    }
    FUN_00692cb0(first, last, cmp);
}

// @ 0x00695450
void* Sorter::run(char* first)
{
    char* p = first;
    char* old;
    do
    {
        old = p;
        p += 0x3c;
        if (*(int*)(old + 0x24) == 0) break;
    } while (*(int*)(old + 0x28) != 0);
    bool flag = false;
    FUN_006950b0((Elem*)first, (Elem*)p, flag);
    return this;
}

// @ 0x00695490
void Vec60::reserve(unsigned int n)
{
    if ((unsigned)((end - begin) / 0x60) < n)
    {
        char* p;
        if (n == 0)
            p = 0;
        else
            p = (char*)EASTL_alloc6(n * 0x60, "App", 0, 0,
                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        char* oldbegin = begin;
        char* oldend = end;
        FUN_00694320(oldbegin, oldend, p);
        FUN_00694e00(oldbegin, oldend, p);
        if (oldbegin != 0 && *(int*)(oldbegin - 4) != 0)
            operator_delete_arr(oldbegin);
        begin = p;
        end = ((end - oldbegin) / 0x60) * 0x60 + p;
        cap = n * 0x60 + p;
    }
}

// @ 0x00695550
void Vec60b::DoInsertValue(Obj60_s0069_5140* position, const Obj60_s0069_5140& value)
{
    if (mpEnd != mpCapacity) {
        const Obj60_s0069_5140* pValue = &value;
        if ((&value >= position) && (&value < mpEnd))
            ++pValue;
        ::new(mpEnd) Obj60_s0069_5140(*(mpEnd - 1));
        CopyBackward60(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? 2 * nPrevSize : 1;
        Obj60_s0069_5140* const pNewData = DoAllocate(nNewSize);
        Obj60_s0069_5140* pNewPosition = UninitCopy60(mpBegin, position, pNewData);
        UninitFill60(mpBegin, position, pNewData);
        ::new(pNewPosition) Obj60_s0069_5140(value);
        Obj60_s0069_5140* pNewEnd = UninitCopy60(position, mpEnd, pNewPosition + 1);
        UninitFill60(position, mpEnd, pNewPosition + 1);
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete_arr(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNewData;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00695770
int SP::cVarListSerializer_s0069_5140::Execute(FieldReport* report)
{
    if (g_bTextFlag)
        report->mTexts.Reserve(mSerializableVarCount);
    report->mFields.Reserve(mSerializableVarCount);
    for (int i = 0; i < mSerializableVarCount; ++i) {
        cDataSerializationInfo_s0069_5140& info = mDataSerializationInfos[i];
        cDataSerializerGeneric_s0069_5140* ser = info.mpSerializer;
        if (ser->mpBinderContext == 0)
            ser->mpBinderContext = mpObject;
        if (ser->mpWriteWideFunc && ser->mpDataBinderFunc)
            ser->mpWriteWideFunc(report, ser->mpDataBinderFunc(ser));
        if (g_bTextFlag) {
            const char* name = ser->mpStaticFieldName;
            CharString value;
            if (ser->mpWriteStringFunc && ser->mpDataBinderFunc) {
                ser->mpWriteStringFunc(&value, ser->mpDataBinderFunc(ser));
                if (value.mpBegin != value.mpEnd) {
                    CharString tagged;
                    tagged.sprintf("<%s>%s</%s>", name, value.mpBegin, name);
                    ((WStrTmpVec*)&report->mTexts)->push_back(ConvertToString16(tagged));
                }
            }
        }
        ser->mpBinderContext = info.mpBinderContext;
    }
    return mSerializableVarCount;
}

// @ 0x00695960
int SP::cVarListSerializer_s0069_5140::GetFields(FieldVec& out)
{
    out.reserve(mSerializableVarCount);
    for (int i = 0; i < mSerializableVarCount; ++i) {
        cDataSerializationInfo_s0069_5140& info = mDataSerializationInfos[i];
        cDataSerializerGeneric_s0069_5140* ser = info.mpSerializer;
        if (ser->mpBinderContext == 0)
            ser->mpBinderContext = mpObject;
        FieldEntry entry;
        entry.mName.assign(ser->mpStaticFieldName);
        entry.mpObject = mpObject;
        *static_cast<cDataSerializerGeneric_s0069_5140*>(&entry) = *ser;
        if (ser->mpWriteStringFunc && ser->mpDataBinderFunc)
            ser->mpWriteStringFunc(&entry.mValue, ser->mpDataBinderFunc(ser));
        ser->mpBinderContext = info.mpBinderContext;
        out.push_back(entry);
    }
    return mSerializableVarCount;
}
