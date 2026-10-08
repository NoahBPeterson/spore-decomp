// Slice s011efb60 -- RenderWare 4 core, rw::graphics::Raster (D3D9 textures/surfaces).
// Built with VC .NET 2003 like the rest of the RW4 core, with link-time code generation (/GL + /LTCG):
// the original keeps values in registers across calls whose callees it knows leave them alone
// (e.g. edx = 0 across FormatGetDepth), which a single-object compile cannot reproduce.
// Module flags: /vc71 /O2 /MD /Gy /TP

namespace rw { namespace graphics {

// Caller-provided storage for a Raster; only its pointer is read here.
struct MemoryResource
{
	void* ptr;
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

	static unsigned char FormatGetDepth(Format format);   // 0x011ef910
	int D3D9Create();                                     // 0x011efb60

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

}}   // namespace rw::graphics
