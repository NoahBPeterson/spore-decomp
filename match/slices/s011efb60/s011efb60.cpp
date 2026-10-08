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
	int            m_type;          // +0x04 flags: 8 = mipmapped, 0x40 = no D3D object, 0x200 = single level
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

}}   // namespace rw::graphics
