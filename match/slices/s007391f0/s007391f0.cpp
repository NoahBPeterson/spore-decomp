// Slice s007391f0 — single large /O2 routine in the model/mesh region of SporeApp.exe.
//
// 3870-byte function with an SEH prologue (`sub esp,0x144`) and __cdecl calling
// convention (plain `ret`), taking a pointer to a mesh/part container.  It walks
// the container's 0x20-byte element vector, builds an index/sort structure and a
// set of temporary vertex buffers, dispatches to several geometry helpers
// (0x00733400, 0x00732410, 0x007322...), and then normalises vertex data.

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef short int16_t;

// @ 0x007391F0 — large mesh build/sort/normalise pass.
// (Behavioral skeleton: the outer loops and helper dispatch are summarised; the
// full per-element body is not reproduced.)
void MeshBuildSort(void* self)
{
    (void)self;
    // 1) count total elements across the container's inner vectors
    // 2) build the sort/index structure (0x00733400)
    // 3) for each element: reset fields, dispatch 0x00732410 for ids 0xc,0xd,0xe,
    //    then normalise each vertex batch (x87 sqrt + SSE multiply)
    return;
}
