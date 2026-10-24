// Slice s00e0c2a0 - SporeApp 0x00e0c2a0..0x00e0cea0
// Planet / terrain-render helpers: small copy loops, functor objects and grid
// sampling routines.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS- /fp:fast
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;
typedef unsigned short u16;

typedef float f32;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
struct Vec3f {
    f32 x;                              // 0x00
    f32 y;                              // 0x04
    f32 z;                              // 0x08
};

// 20-byte record copied by the container copy loops.
struct cRec14 {
    u32  mField00;                      // 0x00
    u32  mField04;                      // 0x04
    u8   mField08;                      // 0x08
    u8   mPad09[3];
    void* mpField0c;                    // 0x0c
    void* mpField10;                    // 0x10
};

// 0x28-byte record with one pointer field at 0x18.
struct cRec28 {
    u32  mField00;                      // 0x00
    u32  mField04;                      // 0x04
    u32  mField08;                      // 0x08
    u32  mField0c;                      // 0x0c
    u32  mField10;                      // 0x10
    u32  mField14;                      // 0x14
    void* mpField18;                    // 0x18
    u32  mField1c;                      // 0x1c
    u32  mField20;                      // 0x20
    u32  mField24;                      // 0x24
};

// 0x10-byte parameter record of the record constructors.
struct cCtorArgs {
    u32  mField00;                      // 0x00
    void* mpField04;                    // 0x04
    f32  mField08;                      // 0x08
    f32  mField0c;                      // 0x0c
    f32  mField10;                      // 0x10
    u32  mField14;                      // 0x14
    void* mpField18;                    // 0x18
    f32  mField1c;                      // 0x1c
    u32  mField20;                      // 0x20
    u32  mField24;                      // 0x24
};

// object whose first virtual slot is a reference-count release.
struct cRefObj {
    virtual void Release();             // slot 0 (offset 0x00)
};

// ---------------------------------------------------------------------------------------------
// External helpers / globals implemented in other slices.
// ---------------------------------------------------------------------------------------------
void  __fastcall FUN_00962740(void* p);                                    // 0x00962740
void  __cdecl FUN_00951330(void* p);                                       // 0x00951330
void  __fastcall FUN_00e0c1f0(const Vec3f* p);                             // 0x00e0c1f0
void  __cdecl FUN_00e0b2c0(float* out, void* a, const Vec3f* b,
                           const Vec3f* c, f32 d);                         // 0x00e0b2c0
void* __cdecl FUN_00453b20(void* out, const Vec3f* v, f32 s);              // 0x00453b20
void  __fastcall FUN_0041cb40(void* p, const void* src);                   // 0x0041cb40
void* __cdecl SP_GetActiveTerrainSphere();                                 // 0x00f48aa0
void* __cdecl SP_GetCurrentGameMode();                                     // 0x00b5b800
void* __fastcall SP_DebugDrawGrid();                                       // 0x???

// vtable dispatch helper for slot 0 (offset 0x00).
static inline void VT_00_0(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[0])(p);
}
// vtable dispatch helper for slot 1 (offset 0x04).
static inline void VT_04_0(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[1])(p);
}
// vtable dispatch helper for slot 3 (offset 0x0c).
static inline void* VT_0C_0(void* p)
{
    return ((void* (__thiscall*)(void*))(*(void***)p)[3])(p);
}

// ---------------------------------------------------------------------------------------------
// Definitions
// ---------------------------------------------------------------------------------------------
// @ 0x00e0c610
// Copies a 4-vector and a 9-dword record into a new object.
struct cRec28Copy {
    void* Copy(const u32* src, const u32* args);   // 0x00e0c610
};

void* cRec28Copy::Copy(const u32* src, const u32* args)
{
    char* dst = (char*)this;
    *(u32*)(dst + 0x00) = *src;
    *(u32*)(dst + 0x04) = args[0];
    *(f32*)(dst + 0x08) = *(f32*)&args[1];
    *(f32*)(dst + 0x0c) = *(f32*)&args[2];
    *(f32*)(dst + 0x10) = *(f32*)&args[3];
    *(u32*)(dst + 0x14) = args[4];
    void* p18 = (void*)args[5];
    *(void**)(dst + 0x18) = p18;
    if (p18 != 0)
        VT_00_0(p18);
    *(f32*)(dst + 0x1c) = *(f32*)&args[6];
    *(u32*)(dst + 0x20) = args[7];
    *(u32*)(dst + 0x24) = args[8];
    return dst;
}

// @ 0x00e0c670
// Copies a 20-byte record, retaining both interface pointers.
struct cRec14Copy {
    void* Copy(const cRec14* src);      // 0x00e0c670
};

void* cRec14Copy::Copy(const cRec14* src)
{
    char* dst = (char*)this;
    *(u32*)(dst + 0x00) = *(u32*)((char*)src + 0x00);
    *(u32*)(dst + 0x04) = *(u32*)((char*)src + 0x04);
    *(u8*)(dst + 0x08) = *(u8*)((char*)src + 0x08);
    void* p0c = *(void**)((char*)src + 0x0c);
    *(void**)(dst + 0x0c) = p0c;
    if (p0c != 0)
        VT_00_0(p0c);
    void* p10 = *(void**)((char*)src + 0x10);
    *(void**)(dst + 0x10) = p10;
    if (p10 != 0)
        VT_00_0(p10);
    return dst;
}

// @ 0x00e0c6b0
// Copies a 0x28-byte record, retaining its interface pointer.
struct cRec28CopyB {
    void* Copy(const cRec28* src);      // 0x00e0c6b0
};

void* cRec28CopyB::Copy(const cRec28* src)
{
    char* dst = (char*)this;
    *(u32*)(dst + 0x00) = src->mField00;
    void* ptr04 = (void*)src->mField04;
    *(u32*)(dst + 0x04) = (u32)ptr04;
    *(f32*)(dst + 0x08) = *(f32*)&src->mField08;
    *(f32*)(dst + 0x0c) = *(f32*)&src->mField0c;
    *(f32*)(dst + 0x10) = *(f32*)&src->mField10;
    u32 v14 = src->mField14;
    *(u32*)(dst + 0x14) = v14;
    void* ptr18 = src->mpField18;
    *(void**)(dst + 0x18) = ptr18;
    if (ptr18 != 0)
        VT_00_0(ptr18);
    *(f32*)(dst + 0x1c) = *(f32*)&src->mField1c;
    *(u32*)(dst + 0x20) = src->mField20;
    *(u32*)(dst + 0x24) = src->mField24;
    return dst;
}

// @ 0x00e0c710
// Copies a range of 20-byte records (retaining pointers) to the destination.
void* __cdecl CopyRecRange(void* first, void* last, void* dst)
{
    if (first != last) {
        char* q = (char*)first + 0x0c;
        char* e = (char*)dst + 0x0c;
        do {
            if (dst != 0) {
                *(u32*)((char*)dst + 0x00) = *(u32*)((char*)first + 0x00);
                *(u32*)((char*)dst + 0x04) = *(u32*)((char*)first + 0x04);
                *(u8*)((char*)dst + 0x08) = *(u8*)((char*)first + 0x08);
                *(u32*)(e) = *(u32*)(q);
                if (*(void**)(e) != 0)
                    VT_00_0(*(void**)(e));
                *(u32*)(e + 0x04) = *(u32*)(q + 0x04);
                if (*(void**)(e + 0x04) != 0)
                    VT_00_0(*(void**)(e + 0x04));
            }
            first = (char*)first + 0x14;
            dst = (char*)dst + 0x14;
            q += 0x14;
            e += 0x14;
        } while (first != last);
    }
    return dst;
}


// @ 0x00e0c780
// Releases both interface pointers of every record in the range.
void* __cdecl DestroyRecRange(void* first, void* last, void* dst)
{
    if (first != last) {
        char* q = (char*)first + 0x0c;
        do {
            if (*(void**)(q + 0x04) != 0)
                VT_04_0(*(void**)(q + 0x04));
            if (*(void**)(q) != 0)
                VT_04_0(*(void**)(q));
            first = (char*)first + 0x14;
            q += 0x14;
            dst = (char*)dst + 0x14;
        } while (first != last);
    }
    return dst;
}

// @ 0x00e0c7d0
// Destructor of the terrain-render object.
struct cTerrainRenderer {
    u8    mPad0000[0x20c];
    void* mpField20c;                   // 0x20c
    void* mpField210;                   // 0x210

    void* Destroy(u8 flags);            // 0x00e0c7d0
};

void* cTerrainRenderer::Destroy(u8 flags)
{
    if (mpField210 != 0)
        VT_04_0(mpField210);
    if (mpField20c != 0)
        VT_04_0(mpField20c);
    FUN_00962740(this);
    if ((flags & 1) != 0)
        FUN_00951330(this);
    return this;
}
