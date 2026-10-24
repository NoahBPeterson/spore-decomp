// Slice s011efb60 -- RenderWare 4 core, rw::graphics::Raster (D3D9 textures/surfaces).
// Built with VC .NET 2003 like the rest of the RW4 core, with link-time code generation (/GL + /LTCG):
// the original keeps values in registers across calls whose callees it knows leave them alone
// (e.g. edx = 0 across FormatGetDepth), which a single-object compile cannot reproduce.
// Module flags: /vc71 /O2 /MD /Gy /TP
#include <string.h>

namespace rw { namespace graphics {

// Caller-provided storage for a Raster; only its pointer is read here.
struct MemoryResource
{
	void* ptr;
};

// What Raster::Lock fills in (D3DLOCKED_RECT / D3DLOCKED_BOX plus the locked extent).
struct RasterLockInfo
{
	unsigned char* bits;        // +0x00
	unsigned int   unk04;
	unsigned int   unk08;
	unsigned int   rowPitch;    // +0x0c
	unsigned int   slicePitch;  // +0x10
	unsigned int   unk14;
	unsigned int   depth;       // +0x18 volume slices
};

class Raster
{
public:
	typedef unsigned int Format;

	Format         m_format;        // +0x00
	union
	{
		int            m_type;      // +0x04 flags: 8 = mipmapped, 0x40 = no D3D object, 0x200 = single level
		struct
		{
			unsigned short m_typeLow;   // +0x04
			unsigned short m_typeHigh;  // +0x06 volume depth / mip-scaled height
		} m_typeParts;
	};
	void*          m_d3dTexture;    // +0x08
	unsigned short m_width;         // +0x0c
	unsigned short m_height;        // +0x0e
	unsigned char  m_depth;         // +0x10
	unsigned char  m_numMipLevels;  // +0x11
	unsigned char  m_face;          // +0x12
	unsigned char  m_pad;           // +0x13
	Raster*        m_nextParent;    // +0x14
	void*          m_swapChain;     // +0x18
	void*          m_window;        // +0x1c

	enum
	{
		FORMAT_DXT1 = 0x31545844,   // FOURCC 'DXT1'..'DXT5'
		FORMAT_DXT2 = 0x32545844,
		FORMAT_DXT3 = 0x33545844,
		FORMAT_DXT4 = 0x34545844,
		FORMAT_DXT5 = 0x35545844
	};
	static bool IsDXT(Format f)
	{
		return f == FORMAT_DXT1 || f == FORMAT_DXT2 || f == FORMAT_DXT3 || f == FORMAT_DXT4 || f == FORMAT_DXT5;
	}

	static unsigned char FormatGetDepth(Format format);   // 0x011ef910
	int D3D9Create();                                     // 0x011efb60
	void D3D9AddToUnmanagedList();                        // 0x011ef710
	void D3D9FlushTextureStages();                        // 0x011efb20
	void D3D9ReleaseResources();                          // 0x011eff60
	static void D3D9RestoreResources();                   // 0x011f00a0
	bool FillSpriteTexture(void* dst, unsigned int rowHint, unsigned int level);   // 0x011f0440
	int Lock(unsigned int flags, unsigned char level, RasterLockInfo* info);   // 0x011ef750
	void Unlock(RasterLockInfo* info);                                         // 0x011ef880
	int SetMipLevelData(const void* src, unsigned char level);

	unsigned int D3D9GetStreamedMipLevelPitch(unsigned char level);
	unsigned int D3D9GetMipLevelSize(unsigned char level);

	static Raster* Initialize(const MemoryResource& resource, unsigned short width, unsigned short height,
	                          unsigned char numMipLevels, int type, Format format);
};

// @ 0x011efeb0
Raster* Raster::Initialize(const MemoryResource& resource, unsigned short width, unsigned short height,
                           unsigned char numMipLevels, int type, Format format)
{
	Raster* r = (Raster*)resource.ptr;
	r->m_format = format;
	r->m_type = type;
	r->m_d3dTexture = 0;
	r->m_width = width;
	r->m_height = height;
	r->m_depth = FormatGetDepth(format);
	r->m_face = 0;
	r->m_pad = 0;
	r->m_nextParent = 0;
	r->m_swapChain = 0;
	r->m_window = 0;

	if ((type & 8) && !(type & 0x200))
	{
		if (numMipLevels == 0)
		{
			// Full chain: one level per halving of the larger side, down to 1.
			unsigned int size = (width > height) ? (unsigned int)width : (unsigned int)height;
			r->m_numMipLevels = 1;
			if (size != 1)
			{
				unsigned char levels = 1;
				do
				{
					size >>= 1;
					++levels;
				} while (size != 1);
				r->m_numMipLevels = levels;
			}
		}
		else
			r->m_numMipLevels = numMipLevels;
	}
	else
		r->m_numMipLevels = 1;

	if (!(type & 0x40) && !r->D3D9Create())
		return 0;
	return r;
}

// @ 0x011efe30
// Bytes per row of mip level `level`; DXT formats count rows of 4x4 blocks (8 bytes each for DXT1, 16 otherwise).
unsigned int Raster::D3D9GetStreamedMipLevelPitch(unsigned char level)
{
	unsigned int width = m_width >> level;
	if (width == 0)
		width = 1;
	Format f = m_format;
	if (!IsDXT(f))
		return (FormatGetDepth(f) >> 3) * width;
	unsigned int blocks = width >> 2;
	if (blocks == 0)
		blocks = 1;
	if (f == FORMAT_DXT1)
		return blocks * 8;
	return blocks << 4;
}

// @ 0x011f0000
// Bytes in mip level `level`. The dev PDB labels this address Raster::Fill; the code is the level size.
unsigned int Raster::D3D9GetMipLevelSize(unsigned char level)
{
	unsigned int height = m_height >> level;
	if (height == 0)
		height = 1;
	Format f = m_format;
	if (!IsDXT(f))
		return D3D9GetStreamedMipLevelPitch(level) * height;
	unsigned int width = m_width >> level;
	if (width == 0)
		width = 1;
	unsigned int shift = (f != FORMAT_DXT1) + 3;   // 8- or 16-byte blocks
	unsigned int bw = width >> 2;
	if (bw == 0)
		bw = 1;
	unsigned int bh = height >> 2;
	if (bh == 0)
		bh = 1;
	return (bh * bw) << shift;
}

// @ 0x011f0270
// Uploads one mip level: lock it, copy the caller's tightly packed data in (row by row when the locked
// pitch differs; slice by slice for volume textures, type flag 0x2000), unlock. The dev PDB labels this
// address Raster::D3D9GetStreamedMipLevelSize.
int Raster::SetMipLevelData(const void* src, unsigned char level)
{
	RasterLockInfo info;
	if (!Lock((m_type & 0x10) ? 0xa : 2, level, &info))
		return 0;
	if (IsDXT(m_format))
	{
		memcpy(info.bits, src, D3D9GetMipLevelSize(level));
	}
	else
	{
		unsigned int pitch = D3D9GetStreamedMipLevelPitch(level);
		if (m_type & 0x2000)
		{
			unsigned int height = m_height >> level;
			if (height == 0)
				height = 1;
			if (pitch == info.rowPitch && height * pitch == info.slicePitch)
				memcpy(info.bits, src, info.depth * info.slicePitch);
			else
			{
				const unsigned char* s = (const unsigned char*)src;
				unsigned char* slice = info.bits;
				unsigned int z = info.depth;
				do
				{
					unsigned char* d = slice;
					unsigned int y = height;
					do
					{
						memcpy(d, s, pitch);
						s += pitch;
						d += info.rowPitch;
					} while (--y);
					slice += info.slicePitch;
				} while (--z);
			}
		}
		else if (pitch == info.rowPitch)
		{
			memcpy(info.bits, src, D3D9GetMipLevelSize(level));
		}
		else
		{
			unsigned int height = m_height >> level;
			if (height == 0)
				height = 1;
			const unsigned char* s = (const unsigned char*)src;
			unsigned char* d = info.bits;
			for (unsigned int y = 0; y < height; ++y)
			{
				memcpy(d, s, pitch);
				d += info.rowPitch;
				s += pitch;
			}
		}
	}
	Unlock(&info);
	return 1;
}

// ===================================================================================
//  gold7 slice s011efb60 -- D3D9 render-target and texture plumbing.
//  The statics below carry their dev-address only for documentation; chk.py masks the
//  relocations, so only the instruction shapes have to line up.
// ===================================================================================

struct RECT
{
	long left;    // +0x00
	long top;     // +0x04
	long right;   // +0x08
	long bottom;  // +0x0c
};

struct D3DLockedRect
{
	int   Pitch;  // +0x00
	void* pBits;  // +0x04
};

struct D3DSurfaceDesc
{
	unsigned int Format;             // +0x00
	unsigned int Type;               // +0x04
	unsigned int Usage;              // +0x08
	unsigned int Pool;               // +0x0c
	unsigned int MultiSampleType;    // +0x10
	unsigned int MultiSampleQuality; // +0x14
	unsigned int Width;              // +0x18
	unsigned int Height;             // +0x1c
};

// D3DPRESENT_PARAMETERS, as handed to CreateAdditionalSwapChain.
struct PresentParameters
{
	unsigned int BackBufferWidth;             // +0x00
	unsigned int BackBufferHeight;            // +0x04
	unsigned int BackBufferFormat;            // +0x08
	unsigned int BackBufferCount;             // +0x0c
	unsigned int MultiSampleType;             // +0x10
	unsigned int MultiSampleQuality;          // +0x14
	unsigned int SwapEffect;                  // +0x18
	void*        hDeviceWindow;               // +0x1c
	int          Windowed;                    // +0x20
	int          EnableAutoDepthStencil;      // +0x24
	unsigned int AutoDepthStencilFormat;      // +0x28
	unsigned int Flags;                       // +0x2c
	unsigned int FullScreen_RefreshRateInHz;  // +0x30
	unsigned int PresentationInterval;        // +0x34
};

// D3DCAPS9 up to Caps2 -- the only field read here (D3DCAPS2_DYNAMICTEXTURES).
struct D3DCaps9
{
	unsigned int DeviceType;       // +0x00
	unsigned int AdapterOrdinal;   // +0x04
	unsigned int Caps;             // +0x08
	unsigned int Caps2;            // +0x0c
	unsigned int pad10[0x20];      // +0x10 ...
};

struct DevCapsManager
{
	static const D3DCaps9* GetD3DCAPS9();   // 0x011f8af0
};

// rw::core::arena::Arena::IdToObject -- resource id to pointer.
struct MemoryArena
{
	void* IdToObject(unsigned int id);      // 0x011e2300
};

// Whatever owns the resource arena (arena pointer lives at +0x78 of it).
struct GraphicsHolder
{
	unsigned char pad00[0x78];
	MemoryArena*  m_arena;                  // +0x78
};

// Texture-stage rebind helper (0x011f12e0), called as cdecl with (stage, raster).
extern void D3D9SetTextureStage(unsigned int stage, const Raster* raster);

extern void*             g_d3d9Device;            // 0x016f89d0 IDirect3DDevice9*
extern void*             g_d3d9;                  // 0x016f89c8 IDirect3D9*
extern void*             g_windowHandle;          // 0x016f658c HWND
extern Raster*           g_defaultZBufferRaster;  // 0x015d083c
extern Raster*           g_d3d9UnmanagedList;     // 0x016f5c0c
extern Raster*           g_rasterShadow[0x11];    // 0x016f5c58
extern PresentParameters g_presentParams;         // 0x016f8b9c
extern unsigned int      g_deviceParameters[15];  // 0x01712444
extern unsigned int      g_d3d9RtFormat;          // 0x016f8bc4
extern unsigned int      g_d3d9RtMultiSample;     // 0x016f8bac
extern unsigned int      g_d3d9RtQuality;         // 0x016f8bb0

extern "C" int __stdcall GetClientRect(void* hWnd, RECT* lpRect);   // IAT 0x013cc598


// @ 0x011efb60
// Creates the D3D9 object selected by the low nibble of m_type and registers the raster with
// the unmanaged list.  The dev PDB labels this address Raster::D3D9CreateSurface.
int Raster::D3D9Create()
{
	unsigned int t = (unsigned int)m_type;
	switch (t & 0xf)
	{
	case 1:
		return (int)this;

	case 2:
	{
		RECT rect;
		GetClientRect(g_windowHandle, &rect);
		Raster* def = g_defaultZBufferRaster;
		if ((rect.right != (long)m_width || rect.bottom != (long)m_height) && def->m_d3dTexture != 0)
		{
			{
				typedef long (__stdcall *Fn)(void*);
				(*(Fn*)(*(unsigned int*)g_d3d9Device + 0x14))(g_d3d9Device);   // EvictManagedResources
			}
			{
				typedef long (__stdcall *Fn)(void*, unsigned int, unsigned int, unsigned int,
				                             unsigned int, unsigned int, void*, void**, void*);
				(*(Fn*)(*(unsigned int*)g_d3d9Device + 0x74))(g_d3d9Device, m_width, m_height,
					g_d3d9RtFormat, g_d3d9RtMultiSample, g_d3d9RtQuality, 0, &m_d3dTexture, 0);
			}
			D3D9AddToUnmanagedList();
			return (int)this;
		}
		if (def == this)
			return (int)this;
		m_d3dTexture = def->m_d3dTexture;
		D3D9AddToUnmanagedList();
		return (int)this;
	}

	case 9:
		if (t & 0x1000)
		{
			typedef long (__stdcall *Fn)(void*, unsigned int, unsigned int, unsigned int,
			                             unsigned int, unsigned int, void**, void*);
			long hr = (*(Fn*)(*(unsigned int*)g_d3d9Device + 0x64))(g_d3d9Device, m_width, 1, 1,
			                                                       m_format, 0, &m_d3dTexture, 0);
			if (hr < 0)
				return 0;
			D3D9AddToUnmanagedList();
			return (int)this;
		}
		{
			typedef long (__stdcall *Fn)(void*, unsigned int, unsigned int, unsigned int,
			                             unsigned int, unsigned int, unsigned int, void**, void*);
			long hr = (*(Fn*)(*(unsigned int*)g_d3d9Device + 0x5c))(g_d3d9Device, m_width, m_height,
				1, 1, m_format, 0, &m_d3dTexture, 0);
			if (hr < 0)
				return 0;
		}
		D3D9AddToUnmanagedList();
		return (int)this;

	case 8:
	case 10:
	{
		typedef long (__stdcall *Fn)(void*, unsigned int, unsigned int, unsigned int,
		                             unsigned int, unsigned int, unsigned int, void**, void*);
		if ((*(Fn*)(*(unsigned int*)g_d3d9Device + 0x5c))(g_d3d9Device, m_width, m_height, 1, 2,
		                                                  m_format, 0, &m_d3dTexture, 0) < 0)
			return 0;
		D3D9AddToUnmanagedList();
		return (int)this;
	}

	case 7:
	{
		unsigned int rtype = (t & 0x1000) ? 5u : ((t & 0x2000) ? 4u : 3u);

		if (t & 0x200)
		{
			if (t & 0x10)
				return 0;
			if ((DevCapsManager::GetD3DCAPS9()->Caps2 & 0x40000000u) == 0)
				return 0;
			{
				typedef long (__stdcall *Fn)(void*, unsigned int, unsigned int, unsigned int,
				                             unsigned int, unsigned int, unsigned int);
				if ((*(Fn*)(*(unsigned int*)g_d3d9 + 0x28))(g_d3d9, g_deviceParameters[0],
				        g_deviceParameters[1], g_deviceParameters[5], 0x400, rtype, m_format) < 0)
					return 0;
			}
		}

		unsigned int usage = (t & 0x200) << 1;
		int pool = 1;
		if (t & 0x10)
		{
			pool = 0;
			usage |= 0x200;
		}

		if (rtype == 3)
		{
			typedef long (__stdcall *Fn)(void*, unsigned int, unsigned int, unsigned int, unsigned int,
			                             unsigned int, int, void**, void*);
			if ((*(Fn*)(*(unsigned int*)g_d3d9Device + 0x5c))(g_d3d9Device, m_width, m_height,
			        m_numMipLevels, usage, m_format, pool, &m_d3dTexture, 0) < 0)
				return 0;
		}
		else if (rtype == 4)
		{
			typedef long (__stdcall *Fn)(void*, unsigned int, unsigned int, unsigned int, unsigned int,
			                             unsigned int, unsigned int, int, void**, void*);
			if ((*(Fn*)(*(unsigned int*)g_d3d9Device + 0x60))(g_d3d9Device, m_width, m_width,
			        (unsigned int)m_typeParts.m_typeHigh, m_numMipLevels, usage, m_format, pool,
			        &m_d3dTexture, 0) < 0)
				return 0;
		}
		else if (rtype == 5)
		{
			typedef long (__stdcall *Fn)(void*, unsigned int, unsigned int, unsigned int, unsigned int,
			                             int, void**, void*);
			if ((*(Fn*)(*(unsigned int*)g_d3d9Device + 0x64))(g_d3d9Device, m_width, m_numMipLevels,
			        usage, m_format, pool, &m_d3dTexture, 0) < 0)
				return 0;
		}
		else
			return 0;

		if (pool == 0)
			D3D9AddToUnmanagedList();
		return (int)this;
	}

	default:
		return 0;
	}
}


// @ 0x011eff60
// Drops the D3D9 object (and swap chain) held by this raster and clears it from the sampler
// shadows.  Named after its dev-PDB role; the address itself is FUN_011eff60.
void Raster::D3D9ReleaseResources()
{
	if (m_d3dTexture == 0)
		return;

	D3D9FlushTextureStages();

	for (unsigned int i = 0; i < 0x11; ++i)
		if (g_rasterShadow[i] == this)
			D3D9SetTextureStage(i, 0);

	typedef unsigned long (__stdcall *ReleaseFn)(void*);
	unsigned int t = (unsigned int)m_type;

	if (t & 0x1000)
	{
		(*(ReleaseFn*)(*(unsigned int*)m_d3dTexture + 8))(m_d3dTexture);
		m_d3dTexture = 0;
		return;
	}
	if (t & 0x2000)
	{
		(*(ReleaseFn*)(*(unsigned int*)m_d3dTexture + 8))(m_d3dTexture);
		m_d3dTexture = 0;
		return;
	}
	switch (t & 0xf)
	{
	case 2:
		(*(ReleaseFn*)(*(unsigned int*)m_d3dTexture + 8))(m_d3dTexture);
		m_d3dTexture = 0;
		return;
	case 1:
		if (m_swapChain)
		{
			(*(ReleaseFn*)(*(unsigned int*)m_swapChain + 8))(m_swapChain);
			m_swapChain = 0;
		}
		(*(ReleaseFn*)(*(unsigned int*)m_d3dTexture + 8))(m_d3dTexture);
		m_d3dTexture = 0;
		return;
	case 9:
		(*(ReleaseFn*)(*(unsigned int*)m_d3dTexture + 8))(m_d3dTexture);
		m_d3dTexture = 0;
		return;
	default:
		(*(ReleaseFn*)(*(unsigned int*)m_d3dTexture + 8))(m_d3dTexture);
		m_d3dTexture = 0;
		return;
	}
}


// @ 0x011f00a0
// Walks the unmanaged list and re-creates the D3D9 object of every raster that lost it, then
// re-binds the sampler stages that point at those rasters.
void Raster::D3D9RestoreResources()
{
	typedef long (__stdcall *Fn0)(void*);
	typedef long (__stdcall *FnRT)(void*, unsigned int, unsigned int, unsigned int, unsigned int,
	                               unsigned int, void*, void**, void*);
	typedef long (__stdcall *FnSwap)(void*, PresentParameters*, void**);
	typedef long (__stdcall *FnBackBuf)(void*, unsigned int, unsigned int, void**);
	typedef long (__stdcall *FnSetTex)(void*, unsigned int, void*);

	for (Raster* it = g_d3d9UnmanagedList; it != 0; it = it->m_nextParent)
	{
		if (it->m_d3dTexture != 0)
			continue;

		unsigned int t = (unsigned int)it->m_type & 0xf;
		if (t == 2)
		{
			RECT rect;
			GetClientRect(g_windowHandle, &rect);
			if (rect.right == (long)it->m_width && rect.bottom == (long)it->m_height)
			{
				it->m_d3dTexture = g_defaultZBufferRaster->m_d3dTexture;
			}
			else
			{
				(*(Fn0*)(*(unsigned int*)g_d3d9Device + 0x14))(g_d3d9Device);
				(*(FnRT*)(*(unsigned int*)g_d3d9Device + 0x74))(g_d3d9Device, it->m_width,
					it->m_height, g_d3d9RtFormat, g_d3d9RtMultiSample, g_d3d9RtQuality, 0,
					&it->m_d3dTexture, 0);
			}
		}
		else if (t == 1)
		{
			PresentParameters pp = g_presentParams;
			pp.hDeviceWindow = it->m_window;
			RECT rect;
			GetClientRect(it->m_window, &rect);
			pp.BackBufferWidth = (rect.right == rect.left);
			pp.BackBufferHeight = (rect.bottom == rect.top);
			pp.EnableAutoDepthStencil = 0;

			void* sc = 0;
			if ((*(FnSwap*)(*(unsigned int*)g_d3d9Device + 0x34))(g_d3d9Device, &pp, &sc) >= 0)
			{
				it->m_swapChain = sc;
				void* bb = 0;
				(*(FnBackBuf*)(*(unsigned int*)sc + 0x14))(sc, 0, 0, &bb);
				if (bb)
					it->m_d3dTexture = bb;
			}
		}
		else
		{
			it->D3D9Create();
		}

		for (unsigned int i = 0; i < 0x11; ++i)
			if (g_rasterShadow[i] == it)
				(*(FnSetTex*)(*(unsigned int*)g_d3d9Device + 0x104))(g_d3d9Device, i,
					it->m_d3dTexture);
	}
}


// @ 0x011f0220
// Fills an eight-dword descriptor: 0x20, 4, then three (0, 1) pairs.
void FUN_011f0220(unsigned int* out)
{
	unsigned int tmp[8];
	tmp[3] = 1;
	tmp[5] = 1;
	tmp[7] = 1;
	tmp[2] = 0;
	tmp[4] = 0;
	tmp[6] = 0;
	tmp[0] = 0x20;
	tmp[1] = 4;
	memcpy(out, tmp, 32);
}


// @ 0x011f0440
// Copies one mip level of this raster into dst.  The streaming form (m_type bit 0) locks the
// level and copies it (or its rows one at a time when the locked pitch differs).  The
// surface/cube form reads the render target back through an offscreen system-memory surface.
bool Raster::FillSpriteTexture(void* dst, unsigned int rowHint, unsigned int level)
{
	(void)rowHint;

	unsigned int t = (unsigned int)m_type;

	if ((t & 1) == 0)
	{
		RasterLockInfo info;
		if (!Lock(1, (unsigned char)level, &info))
			return false;

		if (IsDXT(m_format))
		{
			memcpy(dst, info.bits, D3D9GetMipLevelSize((unsigned char)level));
		}
		else
		{
			unsigned int pitch = D3D9GetStreamedMipLevelPitch((unsigned char)level);
			if (pitch == info.rowPitch)
			{
				memcpy(dst, info.bits, D3D9GetMipLevelSize((unsigned char)level));
			}
			else
			{
				unsigned int height = m_height >> level;
				if (height == 0)
					height = 1;
				unsigned char* d = (unsigned char*)dst;
				unsigned char* s = info.bits;
				for (unsigned int y = height; y != 0; --y)
				{
					memcpy(d, s, pitch);
					d += info.rowPitch;
					s += pitch;
				}
			}
		}
		Unlock(&info);
		return true;
	}

	unsigned int flag = ((t & 9) == 9) ? 1u : 0u;
	void* surf = 0;
	// The original keeps its HRESULT in the first argument's home slot; without a surface to
	// fetch it simply carries that argument into the result test below.
	long hr = (long)dst;

	if (t & 0x1000)
	{
		typedef long (__stdcall *Fn)(void*, unsigned int, unsigned int, void**);
		hr = (*(Fn*)(*(unsigned int*)m_d3dTexture + 0x48))(m_d3dTexture, m_face, 0, &surf);
		if (hr < 0)
			goto done;
	}
	else
	{
		surf = m_d3dTexture;
		if (flag)
		{
			typedef long (__stdcall *Fn)(void*, unsigned int, void**);
			hr = (*(Fn*)(*(unsigned int*)m_d3dTexture + 0x48))(m_d3dTexture, 0, &surf);
			if (hr < 0)
				goto done;
		}
		else
		{
			goto haveSurface;
		}
	}

	if (surf == 0)
		goto done;
haveSurface:
	{
		typedef long (__stdcall *FnDesc)(void*, D3DSurfaceDesc*);
		typedef long (__stdcall *FnOff)(void*, unsigned int, unsigned int, unsigned int,
		                                unsigned int, void**, void*);
		typedef long (__stdcall *FnGetRT)(void*, void*, void*);
		typedef long (__stdcall *FnLock)(void*, D3DLockedRect*, void*, unsigned int);
		typedef long (__stdcall *FnUnlock)(void*);
		typedef unsigned long (__stdcall *FnRelease)(void*);

		D3DSurfaceDesc desc;
		(*(FnDesc*)(*(unsigned int*)surf + 0x30))(surf, &desc);

		void* offscreen = 0;
		if ((*(FnOff*)(*(unsigned int*)g_d3d9Device + 0x90))(g_d3d9Device, m_width, m_height,
		        desc.Format, 2, &offscreen, 0) >= 0)
		{
			if ((*(FnGetRT*)(*(unsigned int*)g_d3d9Device + 0x80))(g_d3d9Device, surf,
			        offscreen) >= 0)
			{
				D3DLockedRect lr;
				if ((*(FnLock*)(*(unsigned int*)offscreen + 0x34))(offscreen, &lr, 0, 0x10) >= 0)
				{
					memcpy(dst, lr.pBits, (unsigned int)m_height * (unsigned int)lr.Pitch);
					(*(FnUnlock*)(*(unsigned int*)offscreen + 0x38))(offscreen);
				}
			}
			(*(FnRelease*)(*(unsigned int*)offscreen + 8))(offscreen);
		}
	}

done:
	{
		typedef unsigned long (__stdcall *FnRelease)(void*);
		if (t & 0x1000)
		{
			if (surf != 0)
				(*(FnRelease*)(*(unsigned int*)surf + 8))(surf);
		}
		else if (flag)
		{
			if (surf != 0)
				(*(FnRelease*)(*(unsigned int*)surf + 8))(surf);
		}
	}
	return hr >= 0;
}


// @ 0x011f06c0
// Resolves the raster's arena id, creates its D3D9 object and uploads every mip of every cube
// face from the arena data.  Free function: both parameters arrive on the stack.
int RasterFixup(Raster* x, GraphicsHolder* holder)
{
	void* obj = holder->m_arena->IdToObject((unsigned int)x->m_window);
	x->m_window = obj;
	if (obj == 0)
		return 0;

	x->m_nextParent = 0;
	if (!x->D3D9Create())
		return 0;

	if ((unsigned int)x->m_type & 0x50)
		return 1;

	bool faces = false;
	unsigned int mask = 0;
	unsigned char* src = (unsigned char*)obj;

	if (x->m_type & 0x1000)
	{
		faces = true;
		mask = 0x3f;
	}

	while (true)
	{
		if (faces)
		{
			if (mask & 1)
			{
				x->m_face = 0;
				mask &= ~1u;
			}
			else if (mask & 2)
			{
				x->m_face = 1;
				mask &= ~2u;
			}
			else if (mask & 4)
			{
				x->m_face = 2;
				mask &= ~4u;
			}
			else if (mask & 8)
			{
				x->m_face = 3;
				mask &= ~8u;
			}
			else if (mask & 0x10)
			{
				x->m_face = 4;
				mask &= ~0x10u;
			}
			else if (mask & 0x20)
			{
				x->m_face = 5;
				mask = 0;
			}
			else
				return 1;
		}

		for (unsigned char mip = 0; mip < x->m_numMipLevels; ++mip)
		{
			if (!x->SetMipLevelData(src, mip))
				return 0;

			if (x->m_type & 0x2000)
			{
				unsigned int h = (unsigned int)x->m_typeParts.m_typeHigh >> mip;
				if (h == 0)
					h = 1;
				src += x->D3D9GetMipLevelSize(mip) * h;
			}
			else
			{
				src += x->D3D9GetMipLevelSize(mip);
			}
		}

		if (!faces)
			break;
		if (mask == 0)
			return 1;
	}
	return 1;
}

}}   // namespace rw::graphics
