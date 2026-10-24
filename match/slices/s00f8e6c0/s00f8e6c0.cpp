// Slice s00f8e6c0 -- Simulator eastl vector constructors and vector<T>::insert(pos,n,value)
// specialisations for 4-, 2- and 1-byte elements, plus the 4-byte grow helper.
// Reconstructed from the retail object.

#include <string.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" void* operator_new(int size, int align, int a3, const char* a4,
                              int a5, int a6, const char* file, int line); // 0xf473d0
extern "C" void  operator_delete__(void* p);                                  // 0xf47380
extern "C" void* eastl_fill(void* dst, const void* src, int nbytes);          // 0x11e0744 (memcpy)
extern "C" void  eastl_set(void* dst, int value, int nbytes);                 // 0x11e073e (memset)

#define ALLOC_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---------------------------------------------------------------------------
// Simulator compact-vector constructors (vtbl + six zeroed words)
// ---------------------------------------------------------------------------
struct SimVecHead {
    void* m00;      // +0x00  vftable
    int   m04;      // +0x04
    int   m08;      // +0x08
    int   m0c;      // +0x0c
    int   m10;      // +0x10
    int   m14;      // +0x14
    int   m18;      // +0x18
};

// @ 0x00f8ee70
extern "C" void* __fastcall FUN_00f8ee70(SimVecHead* self)
{
    self->m04 = 0;
    self->m08 = 0;
    self->m0c = 0;
    self->m00 = (void*)0x1490020;
    self->m10 = 0;
    self->m14 = 0;
    self->m18 = 0;
    return self;
}

// @ 0x00f8ee90
extern "C" void* __fastcall FUN_00f8ee90(SimVecHead* self)
{
    self->m04 = 0;
    self->m08 = 0;
    self->m0c = 0;
    self->m00 = (void*)0x1490028;
    self->m10 = 0;
    self->m14 = 0;
    self->m18 = 0;
    return self;
}

// @ 0x00f8eeb0
extern "C" void* __fastcall FUN_00f8eeb0(SimVecHead* self)
{
    self->m04 = 0;
    self->m08 = 0;
    self->m0c = 0;
    self->m00 = (void*)0x1490030;
    self->m10 = 0;
    self->m14 = 0;
    self->m18 = 0;
    return self;
}

// @ 0x00f8eed0
extern "C" void* __fastcall FUN_00f8eed0(SimVecHead* self)
{
    self->m04 = 0;
    self->m08 = 0;
    self->m0c = 0;
    self->m00 = (void*)0x1490038;
    self->m10 = 0;
    self->m14 = 0;
    self->m18 = 0;
    return self;
}

// ---------------------------------------------------------------------------
// 4-byte grow helper: allocate n*4 bytes and copy [first,last)
// ---------------------------------------------------------------------------
// @ 0x00f8eef0
extern "C" void* __fastcall FUN_00f8eef0(void* self, void*, int n,
                                          const void* first, const void* last)
{
    void* p;
    if (n) {
        p = operator_new(n * 4, 0x80, 0, "Simulator", 0, 0, ALLOC_FILE, 0xe5);
    } else {
        p = 0;
    }
    eastl_fill(p, first, (int)((const char*)last - (const char*)first));
    return p;
}

// ---------------------------------------------------------------------------
// eastl::vector<u32>::insert(pos, n, value)
// ---------------------------------------------------------------------------
struct Vec4 {
    u32* mpBegin;   // +0x00
    u32* mpEnd;     // +0x04
    u32* mpCap;     // +0x08
};

// @ 0x00f8ef50
extern "C" void __fastcall FUN_00f8ef50(Vec4* self, void*, u32* pos,
                                         unsigned int n, const u32* pvalue)
{
    if (n > (unsigned int)(self->mpCap - self->mpEnd)) {
        int size = (int)(self->mpEnd - self->mpBegin);
        unsigned int newCap = (unsigned int)(size * 2);
        if (size == 0)
            newCap = 1;
        unsigned int need = (unsigned int)size + n;
        if (newCap <= need)
            newCap = need;
        u32* pNew;
        if (newCap != 0)
            pNew = (u32*)operator_new((int)(newCap * 4), 0x80, 0, "Simulator", 0, 0,
                                      ALLOC_FILE, 0xe5);
        else
            pNew = 0;
        unsigned int off = (unsigned int)((char*)pos - (char*)self->mpBegin);
        char* base = (char*)eastl_fill(pNew, self->mpBegin, (int)off);
        u32* dst = (u32*)(base + off);
        u32 v = *pvalue;
        for (unsigned int i = 0; i < n; ++i)
            dst[i] = v;
        unsigned int tail = (unsigned int)((char*)self->mpEnd - (char*)pos);
        char* newEnd = (char*)eastl_fill(dst + n, pos, (int)tail);
        if (self->mpBegin != 0)
            operator_delete__(self->mpBegin);
        self->mpBegin = pNew;
        self->mpEnd = (u32*)(newEnd + tail);
        self->mpCap = (u32*)((char*)pNew + (int)(newCap * 4));
    } else if (n != 0) {
        u32 v = *pvalue;
        unsigned int tailCount = (unsigned int)(self->mpEnd - pos);
        if (n < tailCount) {
            u32* src = self->mpEnd - n;
            eastl_fill(self->mpEnd, src, (int)(n * 4));
            self->mpEnd = (u32*)((char*)self->mpEnd + n * 4);
            memmove(pos + n, pos, (int)((char*)src - (char*)pos));
            for (u32* q = pos; q != pos + n; ++q)
                *q = v;
        } else {
            u32* oldEnd = self->mpEnd;
            unsigned int fill = n - tailCount;
            for (unsigned int i = 0; i < fill; ++i)
                self->mpEnd[i] = v;
            self->mpEnd = (u32*)((char*)self->mpEnd + fill * 4);
            eastl_fill(self->mpEnd, pos, (int)((char*)oldEnd - (char*)pos));
            self->mpEnd = (u32*)((char*)self->mpEnd + tailCount * 4);
            for (u32* q = pos; q != oldEnd; ++q)
                *q = v;
        }
    }
}

// ---------------------------------------------------------------------------
// eastl::vector<u16>::insert(pos, n, value)
// ---------------------------------------------------------------------------
struct Vec2 {
    u16* mpBegin;   // +0x00
    u16* mpEnd;     // +0x04
    u16* mpCap;     // +0x08
};

// @ 0x00f8f130
extern "C" void __fastcall FUN_00f8f130(Vec2* self, void*, u16* pos,
                                         unsigned int n, const u16* pvalue)
{
    if (n > (unsigned int)(self->mpCap - self->mpEnd)) {
        int size = (int)(self->mpEnd - self->mpBegin);
        unsigned int newCap = (unsigned int)(size * 2);
        if (size == 0)
            newCap = 1;
        unsigned int need = (unsigned int)size + n;
        if (newCap <= need)
            newCap = need;
        u16* pNew;
        if (newCap != 0)
            pNew = (u16*)operator_new((int)(newCap * 2), 0x80, 0, "Simulator", 0, 0,
                                      ALLOC_FILE, 0xe5);
        else
            pNew = 0;
        unsigned int off = (unsigned int)((char*)pos - (char*)self->mpBegin);
        char* base = (char*)eastl_fill(pNew, self->mpBegin, (int)off);
        u16* dst = (u16*)(base + off);
        u16 v = *pvalue;
        for (unsigned int i = 0; i < n; ++i)
            dst[i] = v;
        unsigned int tail = (unsigned int)((char*)self->mpEnd - (char*)pos);
        char* newEnd = (char*)eastl_fill(dst + n, pos, (int)tail);
        if (self->mpBegin != 0)
            operator_delete__(self->mpBegin);
        self->mpBegin = pNew;
        self->mpEnd = (u16*)(newEnd + tail);
        self->mpCap = (u16*)((char*)pNew + (int)(newCap * 2));
    } else if (n != 0) {
        u16 v = *pvalue;
        unsigned int tailCount = (unsigned int)(self->mpEnd - pos);
        if (n < tailCount) {
            u16* src = self->mpEnd - n;
            eastl_fill(self->mpEnd, src, (int)(n * 2));
            self->mpEnd = (u16*)((char*)self->mpEnd + n * 2);
            memmove(pos + n, pos, (int)((char*)src - (char*)pos));
            for (u16* q = pos; q != pos + n; ++q)
                *q = v;
        } else {
            u16* oldEnd = self->mpEnd;
            unsigned int fill = n - tailCount;
            for (unsigned int i = 0; i < fill; ++i)
                self->mpEnd[i] = v;
            self->mpEnd = (u16*)((char*)self->mpEnd + fill * 2);
            eastl_fill(self->mpEnd, pos, (int)((char*)oldEnd - (char*)pos));
            self->mpEnd = (u16*)((char*)self->mpEnd + tailCount * 2);
            for (u16* q = pos; q != oldEnd; ++q)
                *q = v;
        }
    }
}

// ---------------------------------------------------------------------------
// eastl::vector<u8>::insert(pos, n, value)
// ---------------------------------------------------------------------------
struct Vec1 {
    u8* mpBegin;    // +0x00
    u8* mpEnd;      // +0x04
    u8* mpCap;      // +0x08
};

// @ 0x00f8f330
extern "C" void __fastcall FUN_00f8f330(Vec1* self, void*, u8* pos,
                                         unsigned int n, const u8* pvalue)
{
    if (n > (unsigned int)(self->mpCap - self->mpEnd)) {
        int size = (int)(self->mpEnd - self->mpBegin);
        unsigned int newCap = (unsigned int)(size * 2);
        if (size == 0)
            newCap = 1;
        unsigned int need = (unsigned int)size + n;
        if (newCap <= need)
            newCap = need;
        u8* pNew;
        if (newCap != 0)
            pNew = (u8*)operator_new((int)newCap, 0x80, 0, "Simulator", 0, 0,
                                     ALLOC_FILE, 0xe5);
        else
            pNew = 0;
        unsigned int off = (unsigned int)(pos - self->mpBegin);
        char* base = (char*)eastl_fill(pNew, self->mpBegin, (int)off);
        u8* dst = (u8*)(base + off);
        u8 v = *pvalue;
        for (unsigned int i = 0; i < n; ++i)
            dst[i] = v;
        unsigned int tail = (unsigned int)(self->mpEnd - pos);
        char* newEnd = (char*)eastl_fill(dst + n, pos, (int)tail);
        if (self->mpBegin != 0)
            operator_delete__(self->mpBegin);
        self->mpBegin = pNew;
        self->mpEnd = (u8*)(newEnd + tail);
        self->mpCap = (u8*)((char*)pNew + (int)newCap);
    } else if (n != 0) {
        u8 v = *pvalue;
        unsigned int tailCount = (unsigned int)(self->mpEnd - pos);
        if (n < tailCount) {
            u8* src = self->mpEnd - n;
            eastl_fill(self->mpEnd, src, (int)n);
            self->mpEnd = (u8*)((char*)self->mpEnd + n);
            memmove(pos + n, pos, (int)((char*)src - (char*)pos));
            for (u8* q = pos; q != pos + n; ++q)
                *q = v;
        } else {
            u8* oldEnd = self->mpEnd;
            unsigned int fill = n - tailCount;
            for (unsigned int i = 0; i < fill; ++i)
                self->mpEnd[i] = v;
            self->mpEnd = (u8*)((char*)self->mpEnd + fill);
            eastl_fill(self->mpEnd, pos, (int)((char*)oldEnd - (char*)pos));
            self->mpEnd = (u8*)((char*)self->mpEnd + tailCount);
            for (u8* q = pos; q != oldEnd; ++q)
                *q = v;
        }
    }
}
