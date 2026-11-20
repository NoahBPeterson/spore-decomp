// Slice s006dd250: D3D9 buffer-draw module (cBufferDrawImpl channel management,
// vertex/index lock helpers, draw issue and the ActiveState descriptor shims).
#include "game/types.h"
#include "../s006ccf50/s006ccf50.h"
#include "rw/graphics/VertexBuffer.h"
#include "rw/graphics/VertexDescriptor.h"

// ---- globals ----------------------------------------------------------------
extern void* g_d3d9Device;            // _m_d3d9Device_ActiveState...
extern void* g_shader;               // _m_shader_ActiveState...
extern int   g_softStateUpdated;     // _m_softStateUpdated...
extern int   g_rasterDelta;          // _m_rasterDelta...
extern int   g_renderStateDirty;     // _m_renderStateDirty...
extern int   g_activeVertexDesc;     // _m_vertexDescriptor_ActiveState...
extern int   DAT_016f9138, DAT_016f913c, DAT_016f9140, DAT_016f8afc;
extern int   DAT_016f9144[];         // table up to 0x016f9168
extern void* DAT_016079a0;
extern void* DAT_016079a4;
extern int   DAT_016079a8;
extern int*  DAT_01607728;           // cBufferDrawImpl singleton
extern int   DAT_0160772c, DAT_01607730, DAT_016077c4, DAT_016077c8;
extern int*  _sAppProperties;

// ---- helpers ----------------------------------------------------------------
int  __cdecl FUN_011f3620(int a, int b, int c);
struct VBi {
    uint32_t FUN_011f3620(uint32_t a, uint32_t b, uint32_t c);  // 0x011F3620
};
struct VertexBuffer {
    int* Lock(int a, int* b, int c, int d, int e);  // 0x006DD250
    int* Unlock();                                  // 0x011F36A0
};
int  __cdecl FUN_007c3af0(const char* name);
int  __cdecl FUN_00762b70(int a, int b, int c, int d);
void* __cdecl FUN_00762c60(void* desc, int a, int b, int c, int d, int e);
void __cdecl FUN_00762a30(void* p);
void __cdecl FUN_00762a00(void* p);
void __cdecl FUN_011f2bc0();
int  __cdecl FUN_011f4f20(int a, void* out);
void __cdecl FUN_011f4fd0(void* p);
int  __cdecl FUN_011f1120();
void __cdecl FUN_011f53a0();   // placeholder (unused)

int  __cdecl VertexDescriptor_AreEqual(void* a, void* b);
void __cdecl ActiveState_SetTexture(void* a, void* b);
void __cdecl VertexBuffer_Unlock(void* vb);
uint32_t __cdecl VertexBuffer_UnlockR(void* vb);
void __fastcall CompiledState_Dispatch(void* cs);
void __cdecl GlobalState_D3D9Sync();
void __cdecl VecBool_DoInsertValue(void* a, void* b, uint32_t n);   // eastl::vector<bool> helper

void* __cdecl operator_new(uint32_t size, const char* tag, int a, int b, const char* file, int line);
void  __cdecl operator_delete__(void* p);
void  __cdecl operator_new__(void* p, int a, int b);

// slice-52 helpers (forward declarations)
void __cdecl FUN_006de2a0();
void __cdecl FUN_006de350();
void __fastcall FUN_006dd8b0(void* self);
int* __cdecl FUN_006dd250(void* self, int a, int* b, int c, int d, int e);
void __fastcall FUN_006dd4d0(void* self);

#define D3D9DEV ((void***)g_d3d9Device)

// The dev header only declares VertexDescriptor::D3D9GetStride(); retail inlines it at
// both uses of the stride, leaving the byte in AL and widening it again for the second
// multiply.  Providing the (inline) body here reproduces that shape without touching the
// shared generated header.
inline unsigned char const rw::graphics::VertexDescriptor::D3D9GetStride() const
{
    return m_stride;
}

// ---------------------------------------------------------------------------
// 0x006dd250: lock a channel's vertex/index buffer range.
// @ 0x006dd250
rw::graphics::VertexBuffer* rw::graphics::VertexBuffer::Lock(
    unsigned int flags, BatchIterator& batch, unsigned int& base,
    unsigned int start, unsigned int count)
{
    if (count == 0)
        count = m_numVertices;
    void* data = D3D9Lock(flags, (m_base + start) * m_desc->D3D9GetStride(),
                          m_desc->D3D9GetStride() * count);
    if (data == 0)
        return 0;
    batch.m_lockedBuffer = data;
    batch.m_vb = this;
    return this;
}
