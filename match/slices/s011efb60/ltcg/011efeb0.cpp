// Link-time stubs for Raster::Initialize 0x011efeb0 (tools/matching/ltcg.py): the RW4 core was built with /GL +
// link /LTCG, so the function's code depends on facts about its callees. This file gives them for the callee this
// slice does not define; D3D9Create (0x011efb60) is linked from s011efb60.cpp itself. Made with c2scope's
// ltcgstub.py from the original's code (kill set, calling convention, memory pattern): stubs, not decompilations.
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
}}
using namespace rw::graphics;

// Initialize and D3D9Create are called from outside the /GL set in the original (standard calling convention: the
// original passes `this` in ecx to D3D9Create): export them, or c2 gives them register arguments
#pragma comment(linker, "/EXPORT:?Initialize@Raster@graphics@rw@@SAPAV123@ABUMemoryResource@23@GGEHI@Z")
#pragma comment(linker, "/EXPORT:?D3D9Create@Raster@graphics@rw@@QAEHXZ")

// ---- ltcgstub for 011ef910: kill set eax,ecx; convention cdecl (ret 0) ----
// ---- calleesum stub for 011ef910: same read/write/escape pattern, not a decompilation ----
__declspec(noinline) unsigned char Raster::FormatGetDepth(unsigned int format)
{
#pragma comment(linker, "/EXPORT:" __FUNCDNAME__)   // standard convention: referenced from outside the /GL set
    volatile int ltcgstub_k[2];
    int cs = 0;
    cs += *(char*)format;                   // format: reads only
    return (unsigned char)((int)(cs) << ltcgstub_k[1]);   // kill set: the returned value goes through shl r, cl (ecx)
}
