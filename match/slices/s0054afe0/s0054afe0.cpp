// Slice s0054afe0: SP::Pollen EASTL vector algorithms (uint32 assign, string
// uninitialized_copy, pair copy/copy_backward) and the cAssetMetadata factory.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

// ---------------------------------------------------------------- externals
void  WString_FreeBuffer(void* self);                              // 0x4237d0
void  WString_Assign(void* self, const void* b, const void* e);    // 0x423650
void  WString_AllocateSelf(void* self, const void* b, const void* e);// 0x423820
void  AString_Assign(void* self, const void* b, const void* e);    // 0x454cb0
void* EAAlloc(void* alloc, int size, int align, int flags);        // 0x42dee0
void* Sub_42e5b0(int n, void* first, void* last);                  // 0x42e5b0
void  Sub_511f70(void* first, void* last, void* result);           // 0x511f70
void* FUN_0054b510(void** out, char* first, char* last, char* result); // forward
void  operator_delete(void* p);
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

// cAssetMetadata allocation/construction (from slice 51).
struct cAssetMetadata;
void* cAssetMetadata_ctor(cAssetMetadata* p);                      // 0x550450
void* operator_new_meta(unsigned int n, const char* name, int a, unsigned b, const char* c, int d);

// stub vtable objects used by the factory (see disasm).
struct IObj10 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int* GetBounds();       // vtable slot 4
};
struct IHost {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual bool Make(void* a, void* b, int c, int d);  // vtable slot 9
};
struct IMeta {
    char pad0[8];
    uint32_t f2, f3, f4;
    virtual void s0();
    virtual void Delete();          // vtable slot 1
};

// 16-byte header shared by the vectors and string elements.
struct WStr {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    int       mAlloc;
};

struct VU32 {
    uint32_t* begin;
    uint32_t* end;
    uint32_t* cap;
    int       alloc;
    void* operator=(VU32* other);
};

struct VStr {
    WStr* begin;
    WStr* end;
    WStr* cap;
    int   alloc;
    void* FUN_0054b480(int n, void* first, void* last);
};

// @ 0x0054afe0
void* VU32::operator=(VU32* other)
{
    if (other != this) {
        unsigned n = (unsigned)(other->end - other->begin) >> 2;
        if ((unsigned)((cap - begin) >> 2) < n) {
            void* buf = Sub_42e5b0((int)n, other->begin, other->end);
            uint32_t* p = begin;
            while (p < end) { p = p + 1; }
            if (begin != 0) operator_delete(begin);
            begin = (uint32_t*)buf;
            cap = (uint32_t*)((char*)buf + n * 4);
        } else if ((unsigned)((end - begin) >> 2) < n) {
            unsigned cnt = (unsigned)((end - begin) >> 2);
            memcpy(begin, other->begin, cnt * 4);
            Sub_511f70((char*)other->begin + cnt * 4, other->end, end);
        } else {
            memcpy(begin, other->begin, (unsigned)((char*)other->end - (char*)other->begin));
            uint32_t* p = begin + ((unsigned)((char*)other->end - (char*)other->begin) >> 2);
            while (p < end) { p = p + 1; }
        }
        end = (uint32_t*)((char*)begin + n * 4);
    }
    return this;
}

// @ 0x0054b400
void* FUN_0054b400(char* first, char* last, char* result)
{
    char* dst = result;
    while (first != last) {
        if (dst != 0) {
            *(uint32_t*)(dst + 0) = 0;
            *(uint32_t*)(dst + 4) = 0;
            *(uint32_t*)(dst + 8) = 0;
            WString_AllocateSelf(dst, *(void**)(first + 0), *(void**)(first + 4));
        }
        first += 0x10;
        dst += 0x10;
    }
    return dst;
}

// @ 0x0054b480
void* VStr::FUN_0054b480(int n, void* first, void* last)
{
    void* buf = (n == 0) ? 0 : EAAlloc(&alloc, n << 4, 4, 0);
    void* out;
    FUN_0054b510(&out, (char*)first, (char*)last, (char*)buf);
    return buf;
}

// @ 0x0054b510
void* FUN_0054b510(void** out, char* first, char* last, char* result)
{
    char* dst = result;
    while (first != last) {
        if (dst != 0) {
            *(uint32_t*)(dst + 0) = 0;
            *(uint32_t*)(dst + 4) = 0;
            *(uint32_t*)(dst + 8) = 0;
            WString_AllocateSelf(dst, *(void**)(first + 0), *(void**)(first + 4));
        }
        first += 0x10;
        dst += 0x10;
    }
    *out = dst;
    return out;
}

// @ 0x0054b5b0
char* FUN_0054b5b0(char* first, char* last, char* result)
{
    char* dst = result;
    for (char* src = first; src != last; src = src + 0x14) {
        *(uint32_t*)dst = *(uint32_t*)src;
        if (src + 4 != dst + 4) {
            AString_Assign(dst + 4, *(void**)(src + 4), *(void**)(src + 8));
        }
        dst = dst + 0x14;
    }
    return dst;
}

// @ 0x0054b630
char* FUN_0054b630(char* first, char* last, char* result)
{
    char* dst = result;
    char* src = last;
    while (src != first) {
        src = src - 0x14;
        dst = dst - 0x14;
        *(uint32_t*)dst = *(uint32_t*)src;
        if (src + 4 != dst + 4) {
            AString_Assign(dst + 4, *(void**)(src + 4), *(void**)(src + 8));
        }
    }
    return dst;
}

// @ 0x0054b6f0
bool cAssetMetadataFactory_Create(IHost* self, IObj10* param2, IMeta** out, int param4, int param5)
{
    IMeta* meta = (IMeta*)operator_new_meta(0xd8, "Pollinator/cAssetMetadata", 0, 0, 0, 0);
    if (meta == 0) {
        meta = 0;
    } else {
        meta = (IMeta*)cAssetMetadata_ctor((cAssetMetadata*)meta);
    }
    meta->s0();
    int* p = param2->GetBounds();
    meta->f2 = p[0];
    meta->f3 = p[1];
    meta->f4 = p[2];
    bool ok = self->Make(param2, meta, param4, param5);
    if (!ok) {
        meta->Delete();
    } else {
        *out = meta;
    }
    return ok;
}
