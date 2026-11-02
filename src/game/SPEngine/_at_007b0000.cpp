// src/game/SPEngine/_at_007b0000.cpp -- migrated from slice(s) s007b19c0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_007b0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTexturePreload.h"
#include "SP/cIRTTManager.h"
#include "SP/cRenderTargetRectID.h"
#include <intrin.h>
#include <math.h>
#include <string.h>
#include <new>
#pragma pack(push,1)
#pragma pack(pop)

// ---- items of slice s007b19c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl eastl_alloc(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00F473A0
static inline void* shallow_new_layout(unsigned size) { return eastl_alloc(size, "Graphics", 0, 0, 0, 0); }
void  __cdecl eastl_dealloc(void* p);                                                    // 0x00F47380
void  __cdecl operator_delete__(void* p);                                                // 0x00F47380
void* __cdecl operator_new__(void* dst, int val, int count);                             // 0x011E073E
void __cdecl ConvertDXT1ToARGB8888(unsigned int*, int, unsigned short*, int, int, int);  // 0x007C2880
void __cdecl ConvertDXT3ToARGB8888(unsigned char*, int, unsigned char*, int, int, int);  // 0x007C2AB0
void __cdecl ConvertDXT5ToARGB8888(unsigned char*, int, unsigned char*, int, int, int);  // 0x007C2EE0
struct Raster      // rw::graphics::Raster (0x0c=width u16, 0x0e=height u16)
{
    unsigned D3D9GetMipLevelSize(int level);                     // 0x011F0000
    void     FillSpriteTexture(void* data, unsigned size, int a); // 0x011F0440
};
struct RasterHdr {
    unsigned int   m_format;        // +0x00 (FOURCC)
    unsigned int   m_type;          // +0x04
    void*          m_d3dTexture;    // +0x08
    unsigned short m_width;         // +0x0c
    unsigned short m_height;        // +0x0e
    unsigned char  m_depth;         // +0x10
    unsigned char  pad11;           // +0x11
    unsigned char  m_face;          // +0x12
    unsigned char  pad13;           // +0x13
};
#define FORMAT_DXT1 0x31545844
#define FORMAT_DXT3 0x33545844
#define FORMAT_DXT5 0x35545844
void __cdecl InitViewportDesc(void* out, void* data, int width, int height, int depth, int fmt);  // 0x007C5A40
int  __cdecl WriteImageFile(const char* path, void* desc);                               // 0x007C5F00
struct D3DSurf;
struct D3DTex;
struct D3DTex {                          // IDirect3DTexture9-ish
virtual void t00();
virtual void t01();
virtual void t02();
virtual void t03();
virtual void t04();
virtual void t05();
virtual void t06();
virtual void t07();
virtual void t08();
virtual void t09();
virtual void t10();
virtual void t11();
virtual void t12();
virtual void t13();
    virtual void Unlock();                                            // +0x38
virtual void t15();
virtual void t16();
virtual void t17();
    virtual void GetSurfaceLevel(int face, int level, D3DSurf** out); // +0x48
};
struct D3DSurf {                         // IDirect3DSurface9-ish
virtual void s00();
virtual void s01();
    virtual void Release();                                           // +0x08
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual void s11();
    virtual void GetDesc(void* out);                                  // +0x30
    virtual void Lock(void* out, int a, int size);                    // +0x34
};
struct D3DDevice {                       // IDirect3DDevice9-ish
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24();
virtual void d25();
virtual void d26();
virtual void d27();
virtual void d28();
virtual void d29();
virtual void d30();
virtual void d31();
    virtual void SetSamplerState(int a, void* b);                     // +0x80
virtual void d33();
virtual void d34();
virtual void d35();
    virtual void CreateTexture(int w, int h, void* a, int b, void* c, int d);  // +0x90
};
extern D3DDevice* g_d3d9Device;                    // 0x016f89d0
void __cdecl DoInsertValue(void* dst, void* src, unsigned size);   // 0x011e0744 (memcpy-like)
struct RasterFace {
    unsigned char  m_format[4];     // +0x00
    unsigned int   m_flags;         // +0x04
    unsigned int   m_unk08;         // +0x08
    unsigned short m_width;         // +0x0c
    unsigned short m_height;        // +0x0e
    unsigned char  m_depth;         // +0x10
    unsigned char  pad11[1];        // +0x11
    unsigned char  m_face;          // +0x12
    unsigned char  pad13[1];
};
struct FaceOffset { int x, y; };
extern const FaceOffset g_faceOffsets[6];    // 0x0140fcb8
// ---- items of slice s007b19c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern D3DDevice* g_d3d9Device;                    // 0x016f89d0
extern const FaceOffset g_faceOffsets[6];    // 0x0140fcb8

// @ 0x007b1f40
void* FUN_007b1f40(RasterHdr* r)
{
    unsigned width  = r->m_width;
    unsigned height = r->m_height;
    unsigned fourcc = r->m_format;

    if (fourcc == FORMAT_DXT1) {
        void* p = shallow_new_layout(height * width * 4);
        void* q = shallow_new_layout(((Raster*)r)->D3D9GetMipLevelSize(0));
        ((Raster*)r)->FillSpriteTexture(q,
            ((Raster*)r)->D3D9GetMipLevelSize(0), 0);
        ConvertDXT1ToARGB8888((unsigned int*)p, (int)(width * 4),
            (unsigned short*)q, (int)(((width + 3) >> 2) * 8),
            (int)width, (int)height);
        eastl_dealloc(q);
        return p;
    }
    if (fourcc == FORMAT_DXT3) {
        void* p = shallow_new_layout(height * width * 4);
        void* q = shallow_new_layout(((Raster*)r)->D3D9GetMipLevelSize(0));
        ((Raster*)r)->FillSpriteTexture(q,
            ((Raster*)r)->D3D9GetMipLevelSize(0), 0);
        ConvertDXT3ToARGB8888((unsigned char*)p, (int)(width * 4),
            (unsigned char*)q, (int)(((width + 3) >> 2) << 4),
            (int)width, (int)height);
        eastl_dealloc(q);
        return p;
    }
    if (fourcc == FORMAT_DXT5) {
        void* p = shallow_new_layout(height * width * 4);
        void* q = shallow_new_layout(((Raster*)r)->D3D9GetMipLevelSize(0));
        ((Raster*)r)->FillSpriteTexture(q,
            ((Raster*)r)->D3D9GetMipLevelSize(0), 0);
        ConvertDXT5ToARGB8888((unsigned char*)p, (int)(width * 4),
            (unsigned char*)q, (int)(((width + 3) >> 2) << 4),
            (int)width, (int)height);
        eastl_dealloc(q);
        return p;
    }

    unsigned depth = r->m_depth;
    if (((Raster*)r)->D3D9GetMipLevelSize(0) != (depth * height * width >> 3))
        return 0;

    unsigned size = (depth * height * width) >> 3;
    if (depth < 0x20)
        size = ((((depth * width) >> 3) + 3) >> 2) * depth * height;

    unsigned char* p = (unsigned char*)shallow_new_layout(size);
    if ((r->m_type & 0x1009) == 0x1009) {
        D3DTex*  tex  = (D3DTex*)r->m_d3dTexture;
        D3DSurf* surf = 0;
        unsigned char desc[0x14];
        unsigned char surfDesc[0x14];
        unsigned int  pitch = 0;

        tex->GetSurfaceLevel(r->m_face, 0, &surf);
        surf->GetDesc(surfDesc);
        g_d3d9Device->CreateTexture((int)width, (int)height, surf, 2, desc, 0);
        g_d3d9Device->SetSamplerState((int)surf, surfDesc);

        unsigned int n = height * pitch;
        surf->Lock(desc, 0, 0x10);
        DoInsertValue(p, desc, n);
        tex->Unlock();
        surf->Release();
        ((D3DSurf*)surf)->Release();
        return p;
    }

    ((Raster*)r)->FillSpriteTexture(p, size, 0);
    return p;
}

// @ 0x007b2270
void FUN_007b2270(unsigned char* dst, int x, int y, int dstPitch, int /*unused*/, const unsigned char* src, int w, int h)
{
    if (h <= 0)
        return;
    unsigned char* d = dst + y * dstPitch * 4;
    const unsigned char* s = src;
    for (int j = 0; j < h; ++j) {
        for (int i = x; i < x + w; ++i)
            memcpy(d + i * 4, s + i * 4, 4);
        s += w * 4;
        d += dstPitch * 4;
    }
}

// @ 0x007b2320
void FUN_007b2320(unsigned char* dst, int x, int y, int dstPitch, int /*unused*/, const unsigned char* src, int w, int h)
{
    if (h <= 0)
        return;
    unsigned char* d = dst + y * dstPitch;
    const unsigned char* s = src;
    for (int j = 0; j < h; ++j) {
        if (x < x + w) {
            d += x;
            s += x;
            for (int i = 0; i < w; ++i)
                d[i] = s[i];
            d -= x;
            s -= x;
        }
        s += w;
        d += dstPitch;
    }
}

// @ 0x007b2380
bool FUN_007b2380(void* mgr, RasterFace* r)
{
    if (r->m_unk08 == 0)
        return false;

    unsigned fourcc = *(unsigned*)r->m_format;
    unsigned width  = r->m_width;
    unsigned height = r->m_height;
    unsigned depth  = r->m_depth;

    if (fourcc == FORMAT_DXT1 || fourcc == FORMAT_DXT3 || fourcc == FORMAT_DXT5)
        depth = 0x20;

    if (r->m_flags & 0x1000) {
        unsigned pitch = width * 4;
        unsigned rows  = height * 3;
        void* dst = 0;

        if (depth == 0x20) {
            dst = eastl_alloc(rows * pitch * 4, "Graphics", 0, 0, 0, 0);
            if (rows != 0) {
                unsigned char* p = (unsigned char*)dst + 2;
                unsigned char* rowStart = p;
                unsigned nrows = rows;
                do {
                    unsigned npix = width;
                    while (npix != 0) {
                        p[-2] = 0x7f; p[-1] = 0x7f; p[0] = 0x7f; p[1] = 0xff;
                        p += 4;
                        npix--;
                    }
                    p = rowStart + width * 0x10;
                    rowStart = p;
                } while (--nrows != 0);
            }
            for (int i = 0; i < 6; ++i) {
                r->m_face = (unsigned char)i;
                void* src = FUN_007b1f40((RasterHdr*)r);
                FUN_007b2270((unsigned char*)dst,
                             g_faceOffsets[i].x * width, g_faceOffsets[i].y * height,
                             (int)pitch, (int)rows, (const unsigned char*)src,
                             (int)width, (int)height);
                operator_delete__(src);
            }
        } else if (depth == 8) {
            dst = eastl_alloc(rows * pitch, "Graphics", 0, 0, 0, 0);
            unsigned char* p = (unsigned char*)dst;
            if (rows != 0) {
                unsigned nrows = rows;
                do {
                    if (width != 0)
                        operator_new__(p, 0x7f, (int)pitch);
                    p += pitch;
                } while (--nrows != 0);
            }
            for (int i = 0; i < 6; ++i) {
                r->m_face = (unsigned char)i;
                void* src = FUN_007b1f40((RasterHdr*)r);
                FUN_007b2320((unsigned char*)dst,
                             g_faceOffsets[i].x * width, g_faceOffsets[i].y * height,
                             (int)pitch, (int)rows, (const unsigned char*)src,
                             (int)width, (int)height);
                operator_delete__(src);
            }
        }

        unsigned char desc[0x14];
        InitViewportDesc(desc, dst, (int)pitch, (int)rows, (int)depth, 0);
        desc[2] = (unsigned char)((depth == 8) + 2);
        int rc = WriteImageFile((const char*)mgr, desc);
        operator_delete__(dst);
        return rc == 0;
    }

    void* src = FUN_007b1f40((RasterHdr*)r);
    unsigned char desc[0x14];
    InitViewportDesc(desc, src, (int)width, (int)height, (int)depth, 0);
    desc[2] = (unsigned char)((depth == 8) + 2);
    int rc = WriteImageFile((const char*)mgr, desc);
    operator_delete__(src);
    return rc == 0;
}
