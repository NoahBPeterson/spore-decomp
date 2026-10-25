// slice s007776f0: shader-profile helpers and D3D shader-state setters.
// Small helpers are byte-exact; the EH-framed serializers and the shader-data
// walker are complete reconstructions and are recorded in nonmatching.txt.
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

// ---------------------------------------------------------------------------
// @ 0x007776f0  SP::PSProfileFromVersion
extern char g_psProfile[];   // 0x01539ec0 ("ps_x_x")
char* PSProfileFromVersion(unsigned int version) {
    int lo = (int)(version & 0xff);
    g_psProfile[3] = (char)(version >> 8) + '0';
    char c = (char)lo;
    if (lo < 10)
        c = c + '0';
    g_psProfile[5] = c;
    return g_psProfile;
}

// ---------------------------------------------------------------------------
// @ 0x007779e0  copy a 0x40-byte matrix (four movaps)
struct __declspec(align(16)) Mat44 {
    __m128 r[4];
    void assignTo(Mat44* dst) const;  // @ 0x007779e0
};
void Mat44::assignTo(Mat44* dst) const {
    dst->r[0] = r[0];
    dst->r[1] = r[1];
    dst->r[2] = r[2];
    dst->r[3] = r[3];
}

// ---------------------------------------------------------------------------
// D3D shader-state setters over an object with a 0x18 header and 0x10-byte slots
// ---------------------------------------------------------------------------
struct ShaderState {
    char pad[0x18];
    void setSlotU0(int idx, char v);  // @ 0x00777a60
    void setSlotU1(int idx, char v);  // @ 0x00777a80
    void setSlotV0(int idx, char v);  // @ 0x00777aa0
    void setSlotV1(int idx, char v);  // @ 0x00777ac0
};

void ShaderState::setSlotU0(int idx, char v) {
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 1;
    p[0x19] = v;
}
void ShaderState::setSlotU1(int idx, char v) {
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 2;
    p[0x1a] = v;
}
void ShaderState::setSlotV0(int idx, char v) {
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 4;
    p[0x1b] = v;
}
void ShaderState::setSlotV1(int idx, char v) {
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 8;
    p[0x1c] = v;
}

// ---------------------------------------------------------------------------
// Shader-data stack (array of 8-byte {short key; short pad; int value})
// ---------------------------------------------------------------------------
struct ShaderStackEntry {
    short key;
    short pad;
    int value;
};
extern ShaderStackEntry g_shaderStack[];  // 0x016312f0
extern int g_shaderStackTop;              // 0x01632bf0

// @ 0x00777bf0
void pushShaderDataNull() {
    int top = g_shaderStackTop;
    g_shaderStack[top].key = 0;
    g_shaderStack[top].value = 0;
    g_shaderStackTop = top + 1;
}

// @ 0x00777c90
extern char g_shaderStackRaw[];  // 0x016312e8 (= g_shaderStack - 8)
int shaderDataStackNotEmpty() {
    if (g_shaderStackTop > 0 && *(short*)(g_shaderStackRaw + g_shaderStackTop * 8) != 0)
        return 1;
    return 0;
}

// @ 0x00778050
extern int g_table1631ef0[];  // 0x01631ef0
int tableLookup(unsigned short idx) {
    return g_table1631ef0[idx];
}

// ---------------------------------------------------------------------------
// D3D device, shader-state and draw-state globals.
// ---------------------------------------------------------------------------
struct D3DDevice;

struct D3DVtbl {
    void* m_pad0[0x178 / 4];
    void (__stdcall *m_call178)(D3DDevice*, int, int, int);
    void* m_pad1[(0x1b4 - 0x17c) / 4];
    void (__stdcall *m_call1b4)(D3DDevice*, int, int, int);
};
struct D3DDevice {
    D3DVtbl* m_vtbl;
};

struct VertexDescElement {
    unsigned int m_id;              // +0x00
    union {
        unsigned int m_flags;       // +0x04 (dword view)
        unsigned char m_count;      // +0x04 (byte view)
    };
    unsigned char m_pad[3];         // +0x05
};
struct VertexDescriptor {
    VertexDescElement m_elements[16];
    unsigned int FindElement(unsigned int index);
};

struct DrawBatch {
    unsigned char m_a;
    unsigned char m_b;
    unsigned char m_c;
};
struct DrawState {
    int m_base;
    int m_count;
    int m_batchCount;
    unsigned char* m_batches;
    int m_vertexBase;
};

struct Arena {
    void* ObjectToId(void* object);
    void* IdToObject(void* id);
};
struct ArenaHandle {
    char m_pad[0x78];
    Arena* m_arena;
};
struct ArenaCtx {
    char m_pad[0x1c];
    ArenaHandle* m_handle;
};
struct ArenaObject {
    void* m_unused;
    void* m_value;
};

struct ShaderDataHeader {
    unsigned int m_pad[2];
    unsigned int m_flags;
};
struct ShaderDataRecord {
    unsigned short m_key;
    unsigned short m_offset;
    unsigned short m_size;
    unsigned short m_pad;
};

extern D3DDevice* g_d3dDevice;                  // 0x016f89d0
extern int* g_maxVertexCount;                   // 0x016f65b4
extern VertexDescriptor* g_vertexDescriptor;    // 0x016f65a0
extern void* g_shaderData[];                    // 0x016f65a8
extern unsigned int g_shaderDirty[];            // 0x016f89f8
extern int g_softStateUpdated;                  // 0x016f9110
extern DrawState* g_drawState;                  // 0x016f65b8
extern int* g_pData6dec;                        // 0x016f6dec
extern void* g_pData6df0;                       // 0x016f6df0
extern void* g_pData6e28;                       // 0x016f6e28
extern float* g_pFloat6ec8;                     // 0x016f6ec8
extern char g_emptyString16[];                  // 0x01667bac
extern void* g_graphicsAllocator;               // 0x013ebb38

struct EAIOStream;
namespace EA { namespace IO {
int WriteUint32(void* stream, const void* data, int count, int flags);
int ReadInt32(void* stream, void* data, int count, int flags);
} }
int gfxRead(void* stream, void* data, int count);                        // 0x0093a6c0
extern "C" void* memset(void* dst, int value, unsigned int count);
void* gfxAlloc(unsigned int size, const char* name, int a, int b, void* alloc, int line);  // 0x00f473a0
void gfxFree(void* p);                                                   // 0x00f47380

extern void* BuildStateLookupShader(void* key);                          // 0x011fa000
extern void RemoveShader(void* key);                                     // 0x011fa050

// ---------------------------------------------------------------------------
// Shader-object wrappers (three-argument stdcall virtual calls).
// ---------------------------------------------------------------------------
struct ShaderVtbl {
    void* m_pad[0x10 / 4];
    void (__stdcall *m_call)(void* self, int a, int* b);
};
struct ShaderObject {
    ShaderVtbl* m_vtbl;
};

// @ 0x00777720
void FUN_00777720(ShaderObject* self, int b, int c) {
    self->m_vtbl->m_call(self, c, &b);
}

// @ 0x00777740
int FUN_00777740(int self) {
    ((ShaderObject*)self)->m_vtbl->m_call((void*)self, 0, &self);
    return self;
}

// ---------------------------------------------------------------------------
// SP::cShaderBase serialization.
// ---------------------------------------------------------------------------
struct cShaderBase;

extern void* ShaderConstruct(cShaderBase* self, void* key, unsigned int flags,
                             unsigned int geom, unsigned int elem,
                             unsigned int vs1, unsigned int vs2,
                             unsigned int ps1, unsigned int ps2);          // 0x011f4440

struct cShaderBase {
    unsigned int m_flags;             // +0x00
    unsigned int m_geomType;          // +0x04
    unsigned int m_elementTypes;      // +0x08
    unsigned char m_pad0c[2];         // +0x0c
    unsigned short m_maxVSVersion;    // +0x0e
    unsigned char m_pad10[2];         // +0x10
    unsigned short m_maxPSVersion;    // +0x12
    unsigned char m_pad14[0x28];      // +0x14
    int m_refCount;                   // +0x3c
    unsigned char m_pad40[4];         // +0x40
    unsigned int m_nameFlags;         // +0x44

    bool Write(EAIOStream* io);
    bool Read(EAIOStream* io, void* key, unsigned int reserved);
};

// @ 0x00777760
bool cShaderBase::Write(EAIOStream* io) {
    unsigned int geom = m_geomType;
    unsigned int flags = m_flags;
    unsigned int elem = m_elementTypes;
    unsigned int vs = m_maxVSVersion ? (m_maxVSVersion | 0xfffe0000u) : 0;
    unsigned int ps = m_maxPSVersion ? (m_maxPSVersion | 0xffff0000u) : 0;
    EA::IO::WriteUint32(io, &geom, 1, 0);
    EA::IO::WriteUint32(io, &flags, 1, 0);
    EA::IO::WriteUint32(io, &elem, 1, 0);
    EA::IO::WriteUint32(io, &vs, 1, 0);
    EA::IO::WriteUint32(io, &ps, 1, 0);
    unsigned int name = m_nameFlags;
    EA::IO::WriteUint32(io, &name, 1, 0);
    return 1;
}

// @ 0x00777840
bool cShaderBase::Read(EAIOStream* io, void* key, unsigned int reserved) {
    (void)reserved;
    unsigned int geom;
    unsigned int flags;
    unsigned int elem;
    unsigned int vs;
    unsigned int ps;
    EA::IO::ReadInt32(io, &geom, 1, 0);
    EA::IO::ReadInt32(io, &flags, 1, 0);
    EA::IO::ReadInt32(io, &elem, 1, 0);
    EA::IO::ReadInt32(io, &vs, 1, 0);
    EA::IO::ReadInt32(io, &ps, 1, 0);
    EA::IO::ReadInt32(io, &m_nameFlags, 1, 0);

    cShaderBase* found = (cShaderBase*)BuildStateLookupShader(key);
    if (found) {
        if (found != this)
            found->m_refCount++;
        RemoveShader(key);
    }
    int savedRefCount = m_refCount;
    bool ok = ShaderConstruct(this, key, flags, geom, elem, vs, vs, ps, ps) != 0;
    if (savedRefCount > 0)
        m_refCount += savedRefCount;
    if ((m_nameFlags & 0x10) != 0) {
        int len;
        EA::IO::ReadInt32(io, &len, 1, 0);
        unsigned int cap = (unsigned int)len + 1;
        char* buf;
        if (cap <= 1)
            buf = g_emptyString16;
        else
            buf = (char*)gfxAlloc(cap, "Graphics", 0, 0, g_graphicsAllocator, 0xd1);
        memset(buf, 0x20, (unsigned int)len);
        buf[len] = 0;
        gfxRead(io, buf, len);
        if (cap > 1 && buf)
            gfxFree(buf);
    }
    return ok;
}

// ---------------------------------------------------------------------------
// Vertex-format size queries.
// ---------------------------------------------------------------------------
// @ 0x00777a10
int FUN_00777a10() {
    int maxCount = *g_maxVertexCount;
    VertexDescriptor* vd = g_vertexDescriptor;
    if ((vd->m_elements[1].m_flags & 0x8000) == 0)
        return 1;
    unsigned int idx = vd->FindElement(0xf);
    VertexDescElement* e = &vd->m_elements[idx + 2];
    int count = (int)e->m_count + 1;
    if (count < 0 || maxCount <= count)
        count = maxCount;
    return count;
}

// ---------------------------------------------------------------------------
// Shader-data dirty tracking.
// ---------------------------------------------------------------------------
// @ 0x00777ae0
void FUN_00777ae0(unsigned short index, void* value, char force) {
    void* old = g_shaderData[index];
    if (old == value && force == 0)
        return;
    int top = g_shaderStackTop;
    if (top > 0) {
        g_shaderStack[top].key = index;
        g_shaderStack[top].value = (int)old;
        g_shaderStackTop = top + 1;
    }
    g_shaderData[index] = value;
    g_shaderDirty[index >> 5] |= 1u << (index & 0x1f);
    g_softStateUpdated |= 8;
}

// @ 0x00777b50
void FUN_00777b50(ShaderDataHeader* header) {
    if (g_shaderStackTop <= 0)
        return;
    unsigned int flags = header->m_flags;
    if ((flags & 8) == 0)
        return;
    unsigned char* next = (unsigned char*)(((unsigned int)header + 0x2b) & 0xfffffff0u);
    if (flags & 1)
        next += 0x40;
    if (flags & 0x100000)
        next += (*(unsigned short*)(next + 0xc) + 2) * 12;
    ShaderDataRecord* rec = (ShaderDataRecord*)next;
    unsigned short key = rec->m_key;
    while (key != 0) {
        unsigned char* following = (unsigned char*)(rec + 1);
        if (rec->m_size != 0)
            following += rec->m_offset + rec->m_size;
        else
            following += 4;
        g_shaderStack[g_shaderStackTop].key = key;
        g_shaderStack[g_shaderStackTop].value = (int)g_shaderData[key];
        g_shaderStackTop++;
        rec = (ShaderDataRecord*)following;
        key = rec->m_key;
    }
}

// @ 0x00777c10
void FUN_00777c10() {
    int top = g_shaderStackTop - 1;
    unsigned short key = g_shaderStack[top].key;
    g_shaderStackTop = top;
    if (key == 0)
        return;
    int soft = g_softStateUpdated;
    do {
        g_shaderData[key] = (void*)g_shaderStack[top].value;
        g_shaderDirty[key >> 5] |= 1u << (key & 0x1f);
        --top;
        key = g_shaderStack[top].key;
        soft |= 8;
    } while (key != 0);
    g_softStateUpdated = soft;
    g_shaderStackTop = top;
}

// ---------------------------------------------------------------------------
// Draw-call wrappers.
// ---------------------------------------------------------------------------
// @ 0x00777cb0
void FUN_00777cb0(int params) {
    DrawState* st = g_drawState;
    if (!st)
        return;
    if (st->m_batchCount == 0) {
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice,
            params + st->m_base * 3,
            st->m_base * 0x30 + st->m_vertexBase,
            st->m_count * 3);
        return;
    }
    for (int i = 0; i < st->m_batchCount; i += 3) {
        DrawBatch* batch = (DrawBatch*)(st->m_batches + i);
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice,
            params + batch->m_b * 3,
            batch->m_c * 0x30 + st->m_vertexBase,
            batch->m_a * 3);
    }
}

// @ 0x00777d60
void FUN_00777d60(int a, int b, int hard) {
    (void)b;
    int count = *g_maxVertexCount;
    VertexDescriptor* vd = g_vertexDescriptor;
    if ((vd->m_elements[1].m_flags & 0x8000) == 0) {
        count = 1;
    } else {
        unsigned int idx = vd->FindElement(0xf);
        VertexDescElement* e = &vd->m_elements[idx + 2];
        int n = (int)e->m_count + 1;
        if (n >= 0 && count > n)
            count = n;
    }
    float data[4];
    data[0] = (float)count;
    data[1] = 0.0f;
    data[2] = 1.0f;
    data[3] = 0.0f;
    if (hard)
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)data, 1);
    else
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)data, 1);
}

// @ 0x00777e10
void FUN_00777e10(ArenaObject* object, ArenaCtx* ctx) {
    Arena* arena = ctx->m_handle->m_arena;
    object->m_value = arena->ObjectToId(object->m_value);
}

// @ 0x00777e30
void FUN_00777e30(ArenaObject* object, ArenaHandle* handle) {
    Arena* arena = handle->m_arena;
    object->m_value = arena->IdToObject(object->m_value);
}

// @ 0x00777e50
void FUN_00777e50(int a, int b, int hard) {
    (void)b;
    int* base = g_pData6dec;
    if (hard)
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)(base + 1), 1);
    else
        g_d3dDevice->m_vtbl->m_call1b4(g_d3dDevice, a, (int)(base + 1), 1);
}

// @ 0x00777e90
void FUN_00777e90(int a, int b, int hard) {
    (void)b;
    void* data = g_pData6df0;
    if (!data)
        return;
    if (hard)
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)data, 2);
    else
        g_d3dDevice->m_vtbl->m_call1b4(g_d3dDevice, a, (int)data, 2);
}

// @ 0x00777ed0
void FUN_00777ed0(int a, int b, int hard) {
    (void)b;
    void* data = g_pData6e28;
    if (hard)
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)data, 1);
    else
        g_d3dDevice->m_vtbl->m_call1b4(g_d3dDevice, a, (int)data, 1);
}

// @ 0x00777f80
void FUN_00777f80(int a, int b, int hard) {
    (void)b;
    float* p = g_pFloat6ec8;
    if (!p)
        return;
    float t = *p;
    float s = sinf(t);
    __declspec(align(16)) float data[8];
    data[0] = t;
    data[1] = s;
    data[2] = 0.25f * s + 0.5f;
    data[3] = (s + 1.0f) * 0.5f;
    data[4] = t * 0.0035f;
    data[5] = t * 0.0045f;
    data[6] = t * 0.0065f;
    data[7] = t * 0.0055f;
    if (hard)
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)data, 2);
    else
        g_d3dDevice->m_vtbl->m_call1b4(g_d3dDevice, a, (int)data, 2);
}
