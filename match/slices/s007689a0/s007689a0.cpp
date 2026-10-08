// Slice s007689a0: SP::cGraphicsResourceFactory game-model / dispatch writers.
// /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>
#include <string.h>
#include <new>

typedef unsigned int uint;

struct Key { uint a, b, c; };       // 12-byte resource key (read from owner+8)

struct Stream {                     // EA::IO::IStream; Write is slot 0x38
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34();
    virtual bool Write(const void* p, uint n);                  // +0x38
};

struct IMaterialMgr {               // SP::cMaterialManager vtable (offsets recovered from calls)
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30();
    virtual uint GetMaterialID(void* mat);                      // +0x34 (ret 4)
    virtual void FlagMaterials(uint n, void* mats, uint* out);  // +0x38 (ret 0xc)
    virtual void s3c(); virtual void s40();
    virtual void WriteMaterials(uint n, uint* flags, Stream* s, void* ctx); // +0x44 (ret 0x10)
    virtual void s48();
    virtual void CollectKeys(uint n, uint* ids, void* keyVec, int flag);    // +0x4c (ret 0x10)
};

struct LockedRegion { void* data; uint a, b; };

struct VDesc {                      // rw::graphics::VertexDescriptor
    char p0[0xc];
    uint16_t numElements;           // +0xc
    uint8_t lockFlags;              // +0xe
    uint8_t stride;                 // +0xf
    char p1[8];
    char elements[1];               // +0x18, 12 bytes each
    uint8_t GetStride() const { return stride; }
    void Finish();                  // 0x011f3220
};

struct VBuf {                       // rw::graphics::VertexBuffer
    VDesc* desc;
    uint p4, base, numVertices;
    uint Bytes(uint n) const { return desc->GetStride() * n; }
    void* Lock(uint flags, uint off, uint size);               // 0x011f3620 (ret 0xc)
    void Unlock();                                             // 0x011f36a0
};

struct IBuf {                       // rw::graphics::IndexBuffer
    uint p0, p4, numIndices, pc, p10, primType;
    uint GetDepth();                                           // 0x011f4fb0
    IBuf* Lock(uint flags, LockedRegion* r);                   // 0x011f4f20 (ret 8)
    void Unlock(LockedRegion* r);                              // 0x011f4fd0 (ret 4)
};

struct MeshEntry {                  // element of Model+0x18
    char p0[8];
    IBuf* ib;                       // +0x08
    char p1[0x18];
    VBuf* vb;                       // +0x24
};

struct KeyOwner { char p0[8]; Key key; };   // Key at +8

struct SubObj { char p0[0x74]; KeyOwner* owner; char p1[0x7c - 0x78]; };   // 0x7c bytes
struct Pair8 { uint a, b; };

struct sp_alloc { uint d[2]; };
template<class T> struct PVec {
    T* b; T* e; T* cap; sp_alloc a;      // 0x14 bytes
    T& operator[](uint i) { return b[i]; }
    uint size() const { return (uint)(e - b); }
};

struct Model {
    char p0[8];
    char ctx[0x10];                 // +0x08 (passed to the material manager)
    PVec<MeshEntry*> meshes;        // +0x18
    char q0[0x40 - 0x2c];
    PVec<IBuf*> ibs;                // +0x40
    char q1[0x68 - 0x54];
    PVec<VBuf*> vbs;                // +0x68
    char q2[0x90 - 0x7c];
    PVec<VDesc*> descs;             // +0x90
    char q3[0xb8 - 0xa4];
    PVec<void*> mats;               // +0xb8
    char q4[0xe0 - 0xcc];
    PVec<Pair8> pairs;              // +0xe0 (8-byte elements)
    PVec<void*> bvhs;               // +0xf4
    PVec<SubObj> subs;              // +0x108 (0x7c-byte elements)
    char block18[0x18];             // +0x11c
    char pad134[4];                 // +0x134
    char pad138[4];
    KeyOwner* extra;                // +0x13c
};

void* __cdecl Memmove(void* d, const void* s, uint n);          // 0x011e0744

// Fixed-capacity eastl::vector<Key, sp_vector_allocator> with a 32-element local buffer.
struct KeyVec {
    Key* b; Key* e; Key* cap;
    sp_alloc a;
    uint hdr;                       // 0 header before the local buffer: never freed
    Key buf[32];
    KeyVec() { hdr = 0; b = buf; e = b; cap = buf + 32; }
    ~KeyVec() { if (b && ((uint*)b)[-1] != 0) Dealloc(b); }
    void GrowAndAppend(Key* pos, const Key& v);                 // 0x004e3e10
    void push_back(const Key& v) {
        if (e < cap) { Key* p = e++; if (p) *p = v; }
        else GrowAndAppend(e, v);
    }
    static void Dealloc(void* p);                               // 0x00f47380
};

// eastl::vector<bool-as-dword, fixed_vector_allocator<..>> with a 32-word local buffer.
struct BitVec {
    struct FixedAlloc {
        uint pad6c; uint* pool; uint pad74;
        FixedAlloc(uint* p) : pool(p) {}
    };
    uint* b; uint* e; uint* cap;
    FixedAlloc a;
    uint buf[32];
    BitVec() : a(buf) { e = a.pool; b = e; cap = buf + 32; }
    ~BitVec() { if (b && b != a.pool) KeyVec::Dealloc(b); }
    void Insert(uint* pos, uint n, const uint& val);            // 0x00766950
    void Erase(uint* first, uint* last) {
        Memmove(first, last, (uint)(e - last) * 4);
        e -= (last - first);
    }
    void ResizeFalse(uint n) {
        uint sz = (uint)(e - b);
        if (n > sz) {
            uint v = 0;
            Insert(e, n - sz, v);
        } else {
            Erase(b + n, e);
        }
    }
};

IMaterialMgr* __cdecl MaterialManager();                        // 0x0067dd70
bool __cdecl WriteUint32(Stream* s, const uint* p, uint n, int endian);   // 0x0093aa70

extern const uint kModelHeader;                                 // 0x0140dfd8 (4 bytes)

static inline void PutU32(Stream* s, uint v) { s->Write(&v, 4); }

template<class T> static inline int IndexOf(T* b, T* e, T v) {
    T* p = b;
    while (p != e && *p != v) ++p;
    return p == e ? -1 : (int)(p - b);
}

namespace SP {
struct cGraphicsResourceFactory {
    bool WriteResourceGameModel(Model* m, Stream* s);           // 0x007689a0 (ret 8)
    bool WriteResourceGameMeshes(void* obj, Stream* s);         // 0x00764f60
    bool WriteResourceRaster(void* obj, Stream* s);             // 0x00767ee0
    bool WriteResourceRasterArena(void* obj, Stream* s);        // 0x00763a80
    bool BuildJob(void* obj, void* a, uint flag);               // 0x00767590
    void WriteMaterialRef(Stream* s, void* p);                  // 0x007656c0 (ret 8)
    void WriteTail(Stream* s, Model* m);                        // 0x00764430 (ret 8)
    bool WriteResource(void* obj, void* src, void* u3, void* u4);   // 0x00769200 (ret 0x10)
};
}
typedef SP::cGraphicsResourceFactory Factory;

// ===========================================================================
// @ 0x007689a0  SP::cGraphicsResourceFactory::WriteResourceGameModel
// ===========================================================================
bool Factory::WriteResourceGameModel(Model* m, Stream* s) {
    s->Write(&kModelHeader, 4);
    {
        // Collect the resource keys referenced by the sub-objects and the extra object.
        KeyVec keys;
        uint nsub = (uint)(m->subs.e - m->subs.b);
        for (uint i = 0; i < nsub; ++i) {
            SubObj* so = &m->subs[i];
            KeyOwner* o = so->owner;
            if (o) keys.push_back(o->key);
        }
        if (m->extra) keys.push_back(m->extra->key);

        // The material manager adds each material's dependencies.
        uint nm = (uint)(m->mats.e - m->mats.b);
        for (uint i = 0; i < nm; ++i) {
            uint id = MaterialManager()->GetMaterialID(m->mats[i]);
            MaterialManager()->CollectKeys(1, &id, &keys, 0);
        }

        uint nk = (uint)(keys.e - keys.b);
        WriteUint32(s, &nk, 1, 0);
        uint cnt = (uint)(keys.e - keys.b);
        Key* k = keys.b;
        for (uint i = 0; i < cnt; ++i) {
            uint v = k[i].a;
            if (WriteUint32(s, &v, 1, 0)) {
                v = k[i].c;
                if (WriteUint32(s, &v, 1, 0)) {
                    v = k[i].b;
                    WriteUint32(s, &v, 1, 0);
                }
            }
            k = keys.b;
        }
    }

    uint nmesh = (uint)(m->meshes.e - m->meshes.b);
    s->Write(&nmesh, 4);
    s->Write(m->block18, 0x18);
    s->Write(m->pad134, 4);

    // Index buffers.
    uint nib = (uint)(m->ibs.e - m->ibs.b);
    s->Write(&nib, 4);
    for (uint i = 0; i < nib; ++i) {
        IBuf* ib = m->ibs.b[i];
        uint prim = ib->primType;
        s->Write(&prim, 4);
        uint num = ib->numIndices;
        s->Write(&num, 4);
        uint depth = ib->GetDepth();
        s->Write(&depth, 4);
        LockedRegion r;
        ib->Lock(1, &r);
        void* data = r.data;
        uint size = (depth * num) >> 3;
        s->Write(&size, 4);
        s->Write(data, size);
        ib->Unlock(&r);
    }

    // Vertex descriptors.
    uint ndesc = (uint)(m->descs.e - m->descs.b);
    s->Write(&ndesc, 4);
    for (uint i = 0; i < ndesc; ++i) {
        VDesc* d = m->descs.b[i];
        d->lockFlags |= 1;
        uint ne = d->numElements;
        s->Write(&ne, 4);
        for (uint j = 0; j < ne; ++j)
            s->Write(d->elements + j * 12, 0xc);
        d->Finish();
    }

    // Vertex buffers.
    uint nvb = (uint)(m->vbs.e - m->vbs.b);
    s->Write(&nvb, 4);
    for (uint i = 0; i < nvb; ++i) {
        VBuf* vb = m->vbs.b[i];
        VDesc* want = vb->desc;
        int idx = IndexOf(m->descs.b, m->descs.e, want);
        PutU32(s, idx);
        uint nv = vb->numVertices;
        s->Write(&nv, 4);
        void* data;
        VBuf* lvb;
        void* p = vb->Lock(1, vb->Bytes(vb->base), vb->Bytes(vb->numVertices));
        if (p) { data = p; lvb = vb; }
        uint size = lvb->desc->stride * nv;
        s->Write(&size, 4);
        s->Write(data, size);
        vb->Unlock();
    }

    // Mesh entries: which index/vertex buffer each uses.
    for (uint i = 0; i < nmesh; ++i) {
        MeshEntry* e = m->meshes.b[i];
        VBuf* evb = e->vb;
        IBuf* eib = e->ib;
        int ii = IndexOf(m->ibs.b, m->ibs.e, eib);
        PutU32(s, ii);
        int vi = IndexOf(m->vbs.b, m->vbs.e, evb);
        PutU32(s, vi);
    }

    BitVec flags;
    flags.ResizeFalse(nmesh);
    MaterialManager()->FlagMaterials(nmesh, m->mats.b, flags.b);
    s->Write(flags.b, nmesh * 4);
    MaterialManager()->WriteMaterials(nmesh, flags.b, s, m->ctx);

    uint nbvh = (uint)(m->bvhs.e - m->bvhs.b);
    if (nbvh > nmesh) nbvh = nmesh;
    s->Write(&nbvh, 4);
    for (uint i = 0; i < nbvh; ++i) {
        void* p = m->bvhs.b[i];
        uint present = p != 0;
        WriteUint32(s, &present, 1, 0);
        if (p) WriteMaterialRef(s, p);
    }

    uint npair = (uint)(m->pairs.e - m->pairs.b);
    if (npair > nmesh) npair = nmesh;
    s->Write(&npair, 4);
    for (uint i = 0; i < npair; ++i) {
        Pair8* pr = m->pairs.b + i;
        s->Write(&pr->a, 4);
        s->Write(&pr->b, 4);
    }

    WriteTail(s, m);

    KeyOwner* ex = m->extra;
    Key last;
    last.a = 0; last.c = 0; last.b = 0xffffffff;
    if (ex) { last.a = ex->key.a; last.b = ex->key.b; last.c = ex->key.c; }
    s->Write(&last, 0xc);
    return true;
}

// ===========================================================================
// @ 0x00769200  SP::cGraphicsResourceFactory::WriteResource (dispatch)
// ===========================================================================
struct IFactorySrc {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
    virtual void f4(); virtual void f5(); virtual Stream* GetStream();   // +0x18
};
struct IRefObj {                                   // slots +4 AddRef, +8 Release
    virtual void v0(); virtual void AddRef(); virtual void Release();
};
struct StreamRef {                                 // EA::AutoRefCount<Stream>
    Stream* p;
    StreamRef(Stream* x) : p(x) { if (p) ((IRefObj*)p)->AddRef(); }
    ~StreamRef() { if (p) ((IRefObj*)p)->Release(); }
};
bool Factory::WriteResource(void* obj, void* src, void* u3, void* u4) {
    (void)u3; (void)u4;
    StreamRef st(((IFactorySrc*)src)->GetStream());
    bool r;
    if (st.p) {
        uint32_t type = *(uint32_t*)((char*)obj + 0xc);
        switch (type) {
        case 0x46194d0:
            r = BuildJob(obj, src, 1);
            break;
        case 0x1c135da:
            r = WriteResourceGameMeshes(obj, st.p);
            break;
        case 0xe6bce5:
            r = WriteResourceGameModel((Model*)obj, st.p);
            break;
        case 0x65ea4ec:
            r = BuildJob(obj, src, 0);
            break;
        case 0x2f4e681b:
            r = WriteResourceRasterArena(obj, st.p);
            break;
        case 0x2f4e681c:
            r = WriteResourceRaster(obj, st.p);
            break;
        default:
            return false;
        }
        return r;
    }
    return false;
}
