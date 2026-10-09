// Swarm skin-paint particle description serialization + the EASTL vectors that
// back the eval list (stride 0x10 and 0x14), and ArgScript::PaintCompat ctors.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* operator new[](size_t); void operator delete[](void*); void operator delete[](void*, size_t);
extern "C" void* __cdecl memcpy(void*, const void*, size_t);

namespace EA { namespace IO { struct IStream {}; } }
bool ReadInt32(EA::IO::IStream*, int32_t*, size_t, int);           // @ 0x93a780
bool ReadUInt8(EA::IO::IStream*, uint8_t*, size_t);                // @ 0x93a6c0
bool WriteUInt32(EA::IO::IStream*, const uint32_t*, size_t, int);  // @ 0x93aa70
void WriteUInt8(EA::IO::IStream*, const uint8_t*, size_t); // 0x0093a9a0
void ReadEvalList(EA::IO::IStream*, char*);                        // @ 0x53a6d0 (slice 31)
void WriteEvalList(EA::IO::IStream*, char*);                       // @ 0x53a930 (slice 31)
void ReadDescBase(EA::IO::IStream*, char*);                        // @ 0x53bc90
void WriteDescBase(EA::IO::IStream*, char*);                       // @ 0x53bd00

// The IStream vtable slots used here: +0x30 ReadBytes, +0x38 WriteBytes.
struct IStreamV {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual bool ReadBytes(void* p, unsigned n);                   // +0x30
    virtual void v13();
    virtual bool WriteBytes(const void* p, unsigned n);            // +0x38
};

// Basic eastl-style vector over a compile-time stride.
struct BlobVec { char* mpBegin; char* mpEnd; char* mpCapacity; char* mpAlloc; };

template <int Stride>
void BlobResize(BlobVec* v, unsigned n)
{
    unsigned have = (unsigned)((v->mpEnd - v->mpBegin) / Stride);
    if (have < n) {
        char* nb = (char*)operator new[]((size_t)n * Stride + 4);
        *(uint32_t*)nb = 0;
        nb += 4;
        if (have)
            memcpy(nb, v->mpBegin, (size_t)have * Stride);
        for (unsigned i = have; i < n; ++i)
            for (int b = 0; b < Stride; ++b)
                nb[i * Stride + b] = 0;
        if (v->mpBegin) {
            char* ob = v->mpBegin - 4;
            if (*(uint32_t*)ob != 0)
                operator delete[](ob);
        }
        v->mpBegin = nb;
        v->mpEnd = nb + (size_t)n * Stride;
        v->mpCapacity = v->mpEnd;
    } else {
        v->mpEnd = v->mpBegin + (size_t)n * Stride;
    }
}

template <int Stride>
BlobVec* BlobAssign(BlobVec* v, const BlobVec* o)
{
    if (o == v)
        return v;
    unsigned n = (unsigned)((o->mpEnd - o->mpBegin) / Stride);
    if (n > (unsigned)((v->mpEnd - v->mpBegin) / Stride)) {
        BlobResize<Stride>(v, n);
        memcpy(v->mpBegin, o->mpBegin, (size_t)n * Stride);
    } else {
        memcpy(v->mpBegin, o->mpBegin, (size_t)n * Stride);
        v->mpEnd = v->mpBegin + (size_t)n * Stride;
    }
    return v;
}

namespace EA { namespace ArgScript {
struct cIParser {
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
    PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34)
#undef PV
};
struct cICommand { virtual void AddRef(); virtual void Release(); virtual void Cast(); };
struct cCommandBase : cICommand { cIParser* mParser; int mRefCount; };
} }

// ================================================================ functions

// @ 0x0053acc0
void ReadParticleDescription(EA::IO::IStream* s, char* d)
{
    ReadDescBase(s, d + 0xc);
    ReadInt32(s, (int32_t*)(d + 0x20), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x24), 1, 0);
    ((IStreamV*)s)->ReadBytes(d + 0x28, 0xc);
    ReadUInt8(s, (uint8_t*)(d + 0x34), 1);
    ReadUInt8(s, (uint8_t*)(d + 0x35), 1);
    ReadUInt8(s, (uint8_t*)(d + 0x36), 1);
    ReadUInt8(s, (uint8_t*)(d + 0x37), 1);
    ((IStreamV*)s)->ReadBytes(d + 0x38, 0xc);
    ((IStreamV*)s)->ReadBytes(d + 0x44, 0xc);
    ((IStreamV*)s)->ReadBytes(d + 0x50, 0xc);
    ReadInt32(s, (int32_t*)(d + 0x5c), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x60), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x64), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x68), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x6c), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x70), 1, 0);
    ReadEvalList(s, d + 0x74);
    ReadUInt8(s, (uint8_t*)(d + 0xb0), 1);
    ReadUInt8(s, (uint8_t*)(d + 0xb1), 1);
    ReadUInt8(s, (uint8_t*)(d + 0xb2), 1);
}

// @ 0x0053aea0
void WriteParticleDescription(EA::IO::IStream* s, char* d)
{
    WriteDescBase(s, d + 0xc);
    uint32_t v;
    v = *(uint32_t*)(d + 0x20); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x24); WriteUInt32(s, &v, 1, 0);
    ((IStreamV*)s)->WriteBytes(d + 0x28, 0xc);
    WriteUInt8(s, (uint8_t*)(d + 0x34), 1);
    WriteUInt8(s, (uint8_t*)(d + 0x35), 1);
    WriteUInt8(s, (uint8_t*)(d + 0x36), 1);
    WriteUInt8(s, (uint8_t*)(d + 0x37), 1);
    ((IStreamV*)s)->WriteBytes(d + 0x38, 0xc);
    ((IStreamV*)s)->WriteBytes(d + 0x44, 0xc);
    ((IStreamV*)s)->WriteBytes(d + 0x50, 0xc);
    v = *(uint32_t*)(d + 0x5c); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x60); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x64); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x68); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x6c); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x70); WriteUInt32(s, &v, 1, 0);
    WriteEvalList(s, d + 0x74);
    WriteUInt8(s, (uint8_t*)(d + 0xb0), 1);
    WriteUInt8(s, (uint8_t*)(d + 0xb1), 1);
    WriteUInt8(s, (uint8_t*)(d + 0xb2), 1);
}

// @ 0x0053b160  AutoRefCount<T>::operator=(T*)
void** AutoRefCountAssign(void** slot, void* p)
{
    if (p != *slot) {
        void* old = *slot;
        if (p)
            ((void(__thiscall*)(char*))(*(void***)((char*)p + 8))[0])((char*)p + 8);
        *slot = p;
        if (old)
            ((void(__thiscall*)(char*))(*(void***)((char*)old + 8))[1])((char*)old + 8);
    }
    return slot;
}

// @ 0x0053b1c0
EA::ArgScript::cCommandBase* FUN_0053b1c0(EA::ArgScript::cCommandBase* p)
{
    *(void**)p = (void*)0x13f4b30;
    *(void**)p = (void*)0x13f4b30;
    return p;
}

// @ 0x0053b1f0
EA::ArgScript::cCommandBase* FUN_0053b1f0(EA::ArgScript::cCommandBase* p)
{
    *(void**)p = (void*)0x13f4b30;
    return p;
}

// @ 0x0053b210  eastl::vector<Entry16>::operator=
BlobVec* Vector16Assign(BlobVec* v, const BlobVec* o)
{
    return BlobAssign<0x10>(v, o);
}

// @ 0x0053b520  eastl::vector<Entry16>::resize
void Vector16Resize(BlobVec* v, unsigned n)
{
    BlobResize<0x10>(v, n);
}

// @ 0x0053b5a0  eastl::vector<Entry20>::operator=
BlobVec* Vector20Assign(BlobVec* v, const BlobVec* o)
{
    return BlobAssign<0x14>(v, o);
}

// @ 0x0053b8a0  eastl::vector<Entry20>::resize
void Vector20Resize(BlobVec* v, unsigned n)
{
    BlobResize<0x14>(v, n);
}
// --- equivalence checker address annotations
    void WriteUInt8(...); // 0x0093a9a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
