// Slice s005810d0: EASTL vector insert for 4-byte scalars, and the GIF export
// texture setup on the graphics system.
// Flags: /O2 /Ob1 /MD /Gy /TP /GS- /fp:fast.
#include "types.h"
#include <string.h>

// ---------------------------------------------------------------------------
// Allocator plumbing shared with the other EASTL slices.
// ---------------------------------------------------------------------------
struct Alloc { int unused; };                                            // generic_allocator

void* __cdecl AllocatorAllocate(Alloc* a, unsigned size, unsigned align, unsigned off);  // 0x00f473a0
void  __cdecl AllocatorDeallocate(void* p);                              // 0x00f47380
extern const char kEditorAllocName[];                                    // 0x013eb430

// ---------------------------------------------------------------------------
// VecU9: vector<unsigned> with the EASTL fixed allocator baked into the object.
// ---------------------------------------------------------------------------
struct VecU9 {
    unsigned* mpBegin;                                   // +0x00
    unsigned* mpEnd;                                     // +0x04
    unsigned* mpCapacity;                                // +0x08
    Alloc     mAllocator;                                // +0x0c

    inline unsigned* DoAllocate(uint32_t n) {
        return n ? (unsigned*)AllocatorAllocate(&mAllocator, n * 4, 4, 0) : 0;
    }
    inline void deallocate(void* p, uint32_t n) {
        if (((uint32_t*)p)[-1]) { void* q = p; AllocatorDeallocate(q); }
    }
    inline void DoFree(unsigned* p, uint32_t n) { if (p) deallocate(p, n * 4); }

    void DoInsertN(unsigned* position, uint32_t n, const unsigned* value);   // 0x005810d0
};

// @ 0x005810d0  VecU9::DoInsertN -- insert `n` copies of *value at `position`.
void VecU9::DoInsertN(unsigned* position, uint32_t n, const unsigned* value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const unsigned tempValue = *value;
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            unsigned* const pEnd = mpEnd;
            if (n < nExtra) {
                const uint32_t n4 = n * 4;
                memcpy(pEnd, pEnd - n, n4);
                mpEnd = pEnd + n;
                memmove(pEnd - nExtra, position, nExtra * 4);
                unsigned* p = position;
                do { *p = tempValue; ++p; } while (p != position + n);
            } else {
                unsigned* p = mpEnd;
                uint32_t nFill = n - nExtra;
                if (nFill != 0) {
                    unsigned* d = p;
                    for (uint32_t i = 0; i < nFill; ++i) *d++ = tempValue;
                }
                mpEnd += n - nExtra;
                memcpy(mpEnd, position, (uint32_t)(pEnd - position) * 4);
                mpEnd += nExtra;
                unsigned* q = position;
                if (q != pEnd) {
                    do { *q++ = tempValue; } while (q != pEnd);
                }
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        unsigned* const pNewData = DoAllocate(nNewSize);
        memcpy(pNewData, mpBegin, (uint32_t)(position - mpBegin) * 4);
        unsigned* pNewEnd = pNewData + (position - mpBegin);
        unsigned* p = pNewEnd;
        for (uint32_t i = 0; i < n; ++i)
            *p++ = *value;
        pNewEnd += n;
        memcpy(pNewEnd, position, (uint32_t)(mpEnd - position) * 4);
        pNewEnd += (uint32_t)(mpEnd - position);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// GIF export texture setup.
// ---------------------------------------------------------------------------
extern void* gAppProperties9;                            // 0x015fd918 (SP::cDirectPropertyList)

struct PropertyList9 {
    int  GetIntProperty(uint32_t key) const;             // 0x006a2660
    bool GetDescription(uint32_t key) const;             // 0x006a25a0
};

void* FUN_006bb610();                                    // 0x006bb610
void* FUN_0067dd40();                                    // 0x0067dd40
void* FUN_0067dda0();                                    // 0x0067dda0
void* FUN_0067ddb0();                                    // 0x0067ddb0

struct ColorRGBA9 { float r, g, b, a; };

struct Ctx2D9 {                                          // object at gs+0x3d8
    void SetRaster(int* p, bool flag);                   // 0x007c4be0
    void SetClearColor(const ColorRGBA9& c);             // 0x007c3c20
    void Clear(unsigned flags);                          // 0x007c3c50
    void SetViewportRectArgs(int x, int y);              // 0x007c5310
};

struct GraphicsSystem9 {
    uint8_t  pad00[0x84];
    void*    m84;                                        // +0x84
    uint8_t  pad88[0x360 - 0x88];
    void*    m360;                                       // +0x360
    uint8_t  pad364[0x3d8 - 0x364];
    Ctx2D9*  m3d8;                                       // +0x3d8
    uint8_t  m3e0;                                       // +0x3e0
    uint8_t  m3e1;                                       // +0x3e1
    uint8_t  pad3e2[0x3e4 - 0x3e2];
    uint32_t m3e4;                                       // +0x3e4

    void CaptureGIF(void* name);                         // 0x005809a0
};

// DO NOT REORDER: field names of these argument blocks are referenced by name.
// Raster target bound to the renderer in the GIF-export path.
struct BitmapSrc9 {
    Ctx2D9*  pTarget;                                    // +0x00
    uint32_t v04;                                        // +0x04
    uint32_t v08;                                        // +0x08
    uint32_t v0c;                                        // +0x0c
};

void __cdecl WriteAnimatedCSAGIF(BitmapSrc9* src, uint32_t frames, const char* name,
                                 const uint32_t* p, uint32_t u, float f, bool b1, bool b2); // 0x007c3410

// Empty string used as a placeholder path when capturing the GIF.
extern char gEmptyString16[];                            // 0x01667bac

// @ 0x005812b0  SP::cGraphicsSystem::InitGIFExportTexture
void __fastcall FUN_005812b0(GraphicsSystem9* self, uint32_t f1, BitmapSrc9* src,
                             uint32_t f3, uint32_t f4)
{
    PropertyList9* props = (PropertyList9*)gAppProperties9;
    const int dim   = props->GetIntProperty(0x05893ee8);
    const int scale = props->GetIntProperty(0x05893ed4);
    const int area  = dim * dim;                         // squares the first property

    self->m3e1 = 1;

    void* prop = (*(void* (__thiscall**)(void*, uint32_t))(*(uint32_t*)props + 0x28))(props, 0x05d2c54b);
    // Property tag: 0x34/0x10 select the direct payload, anything else falls
    // back to the neutral value.
    uint16_t tag = *(uint16_t*)((char*)prop + 0x12);
    if (tag == 0x34 || tag == 0x10) {
        if ((*(uint8_t*)((char*)prop + 0x10) & 0x30) != 0)
            prop = *(void**)prop;
        else
            prop = (tag != 0) ? prop : 0;
    } else {
        prop = FUN_006bb610();
    }

    ColorRGBA9 color;                                    // +0x3c .. +0x48
    color.r = ((float*)prop)[0];
    color.g = ((float*)prop)[1];
    color.b = ((float*)prop)[2];
    color.a = ((float*)prop)[3];

    (void)area;
    BitmapSrc9 bmp;                                      // scratch descriptor for the GIF blit

    if (props->GetDescription(0x05d2c51b)) {
        // Description present: render at the full animation size.
        BitmapSrc9 raster;                               // +0x34 .. +0x40
        raster.v04 = 0xffffffff;
        raster.v08 = 0xffffffff;
        {
            void* viewer = FUN_0067dd40();
            (*(void (__thiscall**)(void*, uint32_t*))(*(uint32_t*)viewer + 0xe4))(
                viewer, &raster.v04);
        }
        self->m3d8->SetRaster((int*)&raster.v04, true);
        self->m3d8->SetClearColor(color);
        self->m3d8->Clear(7);

        bmp.pTarget = self->m3d8;
        bmp.v04     = src->v04;
        bmp.v08     = src->v08;
        bmp.v0c     = src->v0c;

        void* rast = self->m84;
        void* sink = (*(void* (__thiscall**)(void*))(*(uint32_t*)rast + 0x13c))(rast);
        (*(void (__thiscall**)(void*, BitmapSrc9*, uint32_t, uint32_t, uint32_t))(
            *(uint32_t*)sink + 0xc))(sink, &bmp, 5, f3, f4);

        if (self->m360 != 0) {
            void* sub = *(void**)((char*)self->m360 + 0x38);
            if (sub != 0)
                (*(void (__thiscall**)(void*, uint32_t, uint32_t, uint32_t, uint32_t))(
                    *(uint32_t*)sub + 0xc))(sub, f3, f4, (uint32_t)&bmp, f1);
        }
    } else {
        // No description: tile the export across the atlas grid.
        int rect[2];                                     // +0x24 .. +0x2c
        rect[0] = -1;
        rect[1] = -1;
        {
            void* viewer = FUN_0067dd40();
            (*(void (__thiscall**)(void*, int*))(*(uint32_t*)viewer + 0xc0))(viewer, rect);
        }
        self->m3d8->SetRaster(rect, true);

        bmp.pTarget = self->m3d8;
        bmp.v04     = src->v04;
        bmp.v08     = src->v08;
        bmp.v0c     = src->v0c;

        void* atlas = FUN_0067dda0();
        (*(void (__thiscall**)(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(
            *(uint32_t*)atlas + 0x24))(atlas, f3, f4, (uint32_t)&bmp, (uint32_t)&bmp, 0xffffffff, f1);

        const int vx = (int)((self->m3e4 / (uint32_t)dim) * (uint32_t)scale);
        const int vy = (int)((self->m3e4 % (uint32_t)dim) * (uint32_t)scale);
        self->m3d8->SetViewportRectArgs(vx, vy);
        self->m3d8->SetClearColor(color);
        self->m3d8->Clear(7);

        void* rast = self->m84;
        void* sink = (*(void* (__thiscall**)(void*))(*(uint32_t*)rast + 0x13c))(rast);
        bmp.v04 = src->v04;
        bmp.v08 = src->v08;
        bmp.v0c = src->v0c;
        (*(void (__thiscall**)(void*, BitmapSrc9*, uint32_t, uint32_t, uint32_t))(
            *(uint32_t*)sink + 0xc))(sink, &bmp, 5, f3, f4);

        void* v3 = FUN_0067ddb0();
        (*(void (__thiscall**)(void*, Ctx2D9*, BitmapSrc9*, ColorRGBA9*, int))(
            *(uint32_t*)v3 + 0x54))(v3, self->m3d8, &bmp, &color, 0);
    }

    // Once the accumulated frame index matches the caller's target, capture the
    // atlas into an animated GIF and reset the export state.
    if (self->m3e4 == f1) {
        int capRect[2];
        capRect[0] = -1;
        capRect[1] = -1;
        {
            void* viewer = FUN_0067dd40();
            (*(void (__thiscall**)(void*, int*))(*(uint32_t*)viewer + 0xc0))(viewer, capRect);
        }
        char* namePair[2];
        namePair[0] = gEmptyString16;
        namePair[1] = gEmptyString16 + 1;
        self->CaptureGIF(namePair);
        void* atlas = FUN_0067dda0();
        bmp.v0c = f3;
        BitmapSrc9* captured = (BitmapSrc9*)(*(void* (__thiscall**)(void*, uint32_t, uint32_t,
            uint32_t, uint32_t, BitmapSrc9*, uint32_t, uint32_t, uint32_t))(
            *(uint32_t*)atlas + 0x18))(atlas, (uint32_t)&bmp, f4, (uint32_t)&bmp, 0,
                                       &bmp, 0, 0, 1);
        WriteAnimatedCSAGIF(captured, (uint32_t)&bmp, gEmptyString16, (uint32_t*)&bmp,
                            0, 0.0f, false, false);

        self->m3e4 = 0;
        self->m3e0 = 0;
        self->m3e1 = 0;

        // The capture path hands back an owned character buffer; release it when
        // it is a real allocation rather than the shared empty string.
        void* bufBegin = gEmptyString16;
        void* bufEnd   = gEmptyString16 + 1;
        if ((char*)bufEnd - (char*)bufBegin > 1 && bufBegin != 0)
            AllocatorDeallocate(bufBegin);
    }
}
