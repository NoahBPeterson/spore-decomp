// Slice s00c89d60: SP::cSpatialObject view/effect helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct cSPVector3 { float x, y, z; };
struct cSPBoundingBox { cSPVector3 mMin; cSPVector3 mMax; };
struct Matrix33 { float m[9]; };

// Transform record shared with the engine's effect interface: a dirty-flag word,
// a change counter, a five-float payload and a 3x3 matrix.
struct SpatialXform {
    u16      mFlags;        // +0x00  bit 1 = ... , bit 2 = ... , bit 4 = payload valid
    u16      mVersion;      // +0x02  bumped on every payload write
    float    mPos[5];       // +0x04  position / direction payload
    Matrix33 mMatrix;       // +0x18
};

// The effect interface stored at EffectElem::p38.
struct EffectInterface {
    virtual void VS00(); virtual void VS04(); virtual void VS08(); virtual void VS0c();
    virtual void VS10(); virtual void VS14();
    virtual void SetTransform(const SpatialXform* xf);   // +0x18
    virtual void VS1c();
    virtual void BuildTransform(SpatialXform* xf);       // +0x20
};

// Effect element stored in the +0xc0 vector (stride 0x3c).
struct EffectElem {
    int   id;              // +0x00
    char  pad04[0x08 - 0x04];
    char  b08;             // +0x08  participates in the world-transform pass
    char  pad09[0x10 - 0x09];
    char  b10;             // +0x10  scale this->mf60 into the blend factor
    char  pad11[0x14 - 0x11];
    float f14;             // +0x14  blend factor
    float f18;             // +0x18  direction scale
    float f1c;             // +0x1c  local position x
    float f20;             // +0x20  local position y
    float f24;             // +0x24  local position z
    char  pad28[0x38 - 0x28];
    EffectInterface* p38;  // +0x38  effect interface
};

// The +0xc0 eastl::vector<tEffectInfo> header; the erase/insert helpers take
// this sub-object directly in ecx.
struct EffectVector {
    EffectElem* vecBegin;  // +0x00
    EffectElem* vecEnd;    // +0x04
    EffectElem* vecCap;    // +0x08
};

static inline void* vfn(void* obj, unsigned off);

struct Spatial {
    void** vt;                       // +0x00
    char   pad04[0x50 - 0x4];
    u32    mFlags50;                 // +0x50  attachment state bits
    char   pad54[0x5c - 0x54];
    float  mf5c;                     // +0x5c  cached scaled distance
    float  mf60;                     // +0x60  blend scale
    float  mf64;                     // +0x64  model scale
    char   pad68[0x90 - 0x68];
    void*  mNameData_90;             // +0x90  model-name string
    u32    mNameSize_94;             // +0x94
    u32    mNameCap_98;              // +0x98
    int*   p9c;                      // +0x9c  refcounted model holder
    int*   pa0;                      // +0xa0  model instance
    char   padA4[0xc0 - 0xa4];
    EffectElem* vecBegin;            // +0xc0
    EffectElem* vecEnd;              // +0xc4
    EffectElem* vecCap;              // +0xc8
    int    padCc;

    float* GetExtents() { return ((float* (__thiscall*)(Spatial*))vfn(this, 0x68))(this); }
};

// vtable-slot fetcher (all engine objects are reached through their vtable).
static inline void* vfn(void* obj, unsigned off) { return ((void**)*(void***)obj)[off / 4]; }


// Column-major 3x3 * vector.
static inline cSPVector3 Rotate(const Matrix33* m, const cSPVector3& v) {
    cSPVector3 r;
    r.x = m->m[0] * v.x + m->m[3] * v.y + m->m[6] * v.z;
    r.y = m->m[1] * v.x + m->m[4] * v.y + m->m[7] * v.z;
    r.z = m->m[2] * v.x + m->m[5] * v.y + m->m[8] * v.z;
    return r;
}

// Engine vector/matrix constants.
extern float DAT_016952a0, DAT_016952a4, DAT_016952a8;   // direction basis
extern float DAT_016952f4, DAT_016952f8, DAT_016952fc;   // secondary basis
extern float DAT_01485720;                               // 1.0f

void  __fastcall FUN_0041cb40(Matrix33* self, int, const void* src);  // 0x41cb40 matrix ctor
void  __fastcall FUN_00478db0(void* self, int, void* src);            // 0x478db0 ref assign
void* __cdecl    FUN_00b3d240();                                      // 0xb3d240 simulator
char  __fastcall FUN_00b33e10(void* self, int, u32 key);              // 0xb33e10
void* __cdecl    FUN_00401010();                                      // 0x401010 noun manager
void* __cdecl    FUN_0059c190(void* dst, void* src);                  // 0x59c190 matrix copy
void  __fastcall FUN_00b5f950(void* self, int, void* model);           // 0xb5f950 model attach
void* __cdecl    FUN_00f473a0(u32 size, void* f, int line, void* a, void* b, void* c);
void  __cdecl    FUN_00f47380(void* p);

// Destructor helpers the original reaches through `this` in ecx.
struct SpatialBaseDtor {
    void Destroy();  // 0x00c898f0
};
struct EffectVecDtor {
    void Destroy();  // 0x00c895f0
};
void __fastcall FUN_00c88ba0(void* self, int, void* p);   // 0xc88ba0 element destroy
void __fastcall FUN_00c88c30(void* self, int, void* src); // 0xc88c30 element copy-ctor
void __cdecl    FUN_00c88570(void* base, void* pos, void* value);
void* __cdecl   FUN_00c88cd0(void* base, void* pos, void* buf);
void* __cdecl   FUN_00c88d10(void* first, void* last, void* dest);
void* __cdecl   FUN_00c88d50(void* dest, void* first, void* last);
void __cdecl    LocalToWorldTransform(Spatial* s, void* m);
void __cdecl    cSPBoundingBox_Transform(cSPBoundingBox* b, void* m);
void __cdecl    Opaque();

// The +0xc0..+0xc8 vector element operations declared cdecl to force call relocations.
void* __cdecl eastl_erase_effect(int a, int b, int c);           // 0xc8a890 support
void  __cdecl FUN_00c88d90(void* p);

// Extents-query basis (0x1695248/4c/50) and per-call helper entries.
extern float DAT_01695248, DAT_0169524c, DAT_01695250;
void __fastcall FUN_00c897e0(void* self, int, void* xf);   // 0xc897e0 local->world
void __fastcall FUN_00409dd0(void* self, int, void* xf);   // 0x409dd0 box transform

// ===========================================================================
// @ 0x00c89d60
// ===========================================================================
// World-transform pass over the +0xc0 effect list.  A parent transform is
// supplied by the caller; each live element's local direction (offset by the
// 0x16952a0/a4/a8 basis scaled by f18*this->mf78) is rotated into the parent
// frame, translated, and handed to the effect interface.
void __fastcall F89d60(Spatial* s, int, const SpatialXform* parent)
{
    if (s->vecBegin == s->vecEnd) return;

    float scale = ((float (__thiscall*)(Spatial*))vfn(s, 0x78))(s);

    SpatialXform xf;
    xf.mFlags = 0;
    xf.mVersion = 0;
    xf.mPos[0] = DAT_016952f4;
    xf.mPos[1] = DAT_016952f8;
    xf.mPos[2] = DAT_016952fc;
    xf.mPos[3] = DAT_01485720;
    xf.mPos[4] = DAT_01485720;
    FUN_0041cb40(&xf.mMatrix, 0, (const void*)0x016952d0);
    xf.mMatrix = parent->mMatrix;
    xf.mFlags |= 2;
    xf.mVersion += 1;

    for (EffectElem* p = s->vecBegin; p != s->vecEnd; ++p) {
        EffectInterface* fx = p->p38;
        if (fx == 0) continue;
        if (p->b08 == 0) continue;

        float t = p->f18 * scale;
        cSPVector3 v;
        v.x = p->f1c + DAT_016952a0 * t;
        v.y = p->f20 + DAT_016952a4 * t;
        v.z = p->f24 + DAT_016952a8 * t;
        cSPVector3 r = Rotate(&parent->mMatrix, v);
        r.x += parent->mPos[0];
        r.y += parent->mPos[1];
        r.z += parent->mPos[2];

        float blend = p->f14;
        if (p->b10 != 0) blend *= s->mf60;
        if (blend != 0.0f) {
            fx->BuildTransform(&xf);
            blend = xf.mPos[4];
            xf.mVersion += 1;
        }

        xf.mFlags |= 4;
        xf.mPos[0] = r.x;
        xf.mPos[1] = r.y;
        xf.mPos[2] = r.z;
        xf.mPos[4] = blend;
        fx->SetTransform(&xf);
    }
}

// Linear search of the +0xc0 effect vector by id.
static EffectElem* FindEffect(Spatial* s, int id)
{
    for (EffectElem* p = s->vecBegin; p != s->vecEnd; ++p)
        if (p->id == id) return p;
    return 0;
}

// Build the default SpatialXform payload the effect interface expects.
static void InitXform(SpatialXform* xf)
{
    xf->mFlags = 0;
    xf->mVersion = 0;
    xf->mPos[0] = DAT_016952f4;
    xf->mPos[1] = DAT_016952f8;
    xf->mPos[2] = DAT_016952fc;
    xf->mPos[3] = DAT_01485720;
    xf->mPos[4] = DAT_01485720;
    FUN_0041cb40(&xf->mMatrix, 0, (const void*)0x016952d0);
}

// ===========================================================================
// @ 0x00c8a020  find effect by id, set +0x14
// ===========================================================================
void __fastcall F8a020(Spatial* s, int, int id, float val)
{
    EffectElem* p = FindEffect(s, id);
    if (p == 0) return;
    p->f14 = val;
    EffectInterface* fx = p->p38;
    if (fx == 0) return;

    float blend = (p->b10 != 0) ? s->mf60 : DAT_01485720;
    blend *= val;

    SpatialXform xf;
    InitXform(&xf);
    fx->BuildTransform(&xf);
    xf.mPos[4] = blend;
    xf.mVersion += 1;
    fx->SetTransform(&xf);
}

// ===========================================================================
// @ 0x00c8a110  find effect by id, set byte +0x10
// ===========================================================================
void __fastcall F8a110(Spatial* s, int, int id, char val)
{
    EffectElem* p = FindEffect(s, id);
    if (p == 0) return;
    p->b10 = val;
    EffectInterface* fx = p->p38;
    if (fx == 0) return;

    float blend = (val != 0) ? s->mf60 : DAT_01485720;
    blend *= p->f14;

    SpatialXform xf;
    InitXform(&xf);
    fx->BuildTransform(&xf);
    xf.mPos[4] = blend;
    xf.mVersion += 1;
    fx->SetTransform(&xf);
}

// ===========================================================================
// @ 0x00c8a200
// ===========================================================================
void __fastcall F8a200(Spatial* s, int, int id, float val)
{
    EffectElem* p = FindEffect(s, id);
    if (p == 0) return;
    p->f18 = val;
    EffectInterface* fx = p->p38;
    if (fx == 0) return;

    float scale = ((float (__thiscall*)(Spatial*))vfn(s, 0x78))(s) * p->f18;
    cSPVector3 v;
    v.x = p->f1c + DAT_016952a0 * scale;
    v.y = p->f20 + DAT_016952a4 * scale;
    v.z = p->f24 + DAT_016952a8 * scale;

    SpatialXform xf;
    InitXform(&xf);
    fx->BuildTransform(&xf);

    cSPVector3 r = Rotate(&xf.mMatrix, v);
    float* pos = ((float* (__thiscall*)(Spatial*))vfn(s, 0x2c))(s);
    xf.mPos[0] = r.x + pos[0];
    xf.mPos[1] = r.y + pos[1];
    xf.mPos[2] = r.z + pos[2];
    xf.mFlags |= 4;
    xf.mVersion += 1;
    fx->SetTransform(&xf);
}

// ===========================================================================
// @ 0x00c8a420  destructor: reset vtable, release +0xa0, release +0x9c
// ===========================================================================
// Refcounted holder behind +0x9c: +0x00 the shared object, +0x04 flags, +0x40 refcount.
struct RefHolder {
    void**   mpObject;    // +0x00
    uint32_t mFlags;      // +0x04
    char     pad08[0x40 - 0x08];
    int32_t  mRefCount;   // +0x40
};
// slot 0x170 takes the holder and the "delete" flag on the stack, this = the shared object
typedef void (__thiscall* RefReleaseFn)(void* self, void* holder, unsigned char del);
void __fastcall F8a420(Spatial* s)
{
    s->vt = (void**)0x1473758;
    ((SpatialBaseDtor*)s)->Destroy();
    ((EffectVecDtor*)((char*)s + 0xc0))->Destroy();
    if (s->pa0 != 0) {
        void** vt = *(void***)s->pa0;
        ((void(__thiscall*)(int*))vt[4 / 4])(s->pa0);
    }
    RefHolder* p = (RefHolder*)s->p9c;
    if (p != 0) {
        if (p->mRefCount > 1) { p->mRefCount -= 1; return; }
        void** vt = *(void***)p->mpObject;
        ((RefReleaseFn)vt[0x170 / 4])(p->mpObject, p, (unsigned char)((p->mFlags >> 31) & 1));
    }
}

// ===========================================================================
// @ 0x00c8a480
// ===========================================================================
extern char g_empty13ec47c;   // 0x13ec47c  empty-string sentinel
struct StrAssigner {
    void Assign(const void* first, const void* last);   // 0x454cb0
};
void __stdcall F8a480(StrAssigner* self)
{
    self->Assign(&g_empty13ec47c, &g_empty13ec47c);
}

// ===========================================================================
// @ 0x00c8a4a0  SP::cSpatialObject::GetWorldExtents
// ===========================================================================
cSPBoundingBox* __fastcall GetWorldExtents(Spatial* s, int, cSPBoundingBox* box)
{
    float* f = s->GetExtents();
    box->mMin.x = f[0];
    box->mMin.y = f[1];
    box->mMin.z = f[2];
    box->mMax.x = f[3];
    box->mMax.y = f[4];
    box->mMax.z = f[5];

    SpatialXform xf;
    xf.mFlags = 0;
    xf.mVersion = 0;
    xf.mPos[0] = DAT_01695248;
    xf.mPos[1] = DAT_0169524c;
    xf.mPos[2] = DAT_01695250;
    xf.mPos[3] = DAT_01485720;
    xf.mPos[4] = DAT_01485720;
    FUN_0041cb40(&xf.mMatrix, 0, (const void*)0x016952ac);

    FUN_00c897e0(s, 0, &xf);       // local -> world
    FUN_00409dd0(box, 0, &xf);     // transform the box
    return box;
}

// ===========================================================================
// @ 0x00c8a550  SP::cSpatialObject::LoadModel
// ===========================================================================
// Attaches `model` to the spatial: builds the model reference (either from the
// cached key or through the noun manager), publishes it on +0x9c/+0xa0, then
// copies the current pose (position, matrix, scale) into the new model and
// bumps its dirty words.
struct ModelDesc {                    // stack descriptor handed to the noun manager
    u32  mTag;                        // +0x00  0x2ea8fb98
    u16  mKind;                       // +0x04  4 = plain, 2 = ...
    u16  mPad06;
};
// Refcounted element wrapper copied at Spatial+0x9c (same shape used by the
// destructor at 0x00c8a420); it is the 8-byte base of every +0x9c value.
struct EffectElementRef {
    void**  mpObject;    // +0x00 finished object (size >= 0x170)
    u32     mFlags;      // +0x04 bit 31 = owned
};

struct SimFlags {
    char pad[0x10c];
    u8   mFlag10c;                    // 0x10c
    u8   mFlag10d;                    // 0x10d
};
struct ModelHolder {                  // refcounted model instance
    void** vt;                        // +0x00
    u32    mFlags04;                  // +0x04
    u16    mFlags08;                  // +0x08  dirty bits
    u16    mVersion0a;                // +0x0a  write counter
    float  mPos0c[3];                 // +0x0c
    float  mf18;                      // +0x18
    Matrix33 mMatrix1c;               // +0x1c
    int32_t mRefCount40;              // +0x40
    float  mf6c;                      // +0x6c
    float  mf70;                      // +0x70
};

bool __fastcall LoadModel(Spatial* s, void*, void* model)
{
    bool loaded = false;
    if (model == 0) goto finish;
    if (!((char (__thiscall*)(Spatial*))vfn(s, 0x90))(s)) goto finish;

    {
        EffectElementRef holder;
        holder.mpObject = 0;
        u32 key = s->mNameSize_94;
        if (key == 0x24682294 || key == 0x2399be55 || key == 0x476a98c7) {
            // Known key: describe the spatial and ask the noun manager.
            ModelDesc desc;
            desc.mTag = 0x2ea8fb98;
            desc.mKind = 4;
            desc.mPad06 = 0;
            if (((char (__thiscall*)(Spatial*))vfn(s, 0x58))(s)) desc.mKind = 2;

            SimFlags* sim = (SimFlags*)FUN_00b3d240();
            bool wantFlag = false;
            if (sim->mFlag10c != 0 &&
                FUN_00b33e10(sim, 0, s->mNameSize_94) != 0) {
                desc.mKind |= 0x100;
                wantFlag = true;
            }
            void* nouns = FUN_00401010();
            ((void (__thiscall*)(void*, void*, ModelDesc*))vfn(nouns, 0x4c))(
                nouns, (void*)&s->mNameData_90, &desc);
            holder.mpObject = (void**)((void* (__thiscall*)(void*, u32, u32, void*))vfn(model, 0x0c))(
                model, wantFlag ? 0x20u : 0u, s->mNameCap_98, s->mNameData_90);
            FUN_00478db0(&holder, 0, holder.mpObject);
            if (holder.mpObject != 0 && wantFlag &&
                ((SimFlags*)FUN_00b3d240())->mFlag10d != 0)
                holder.mFlags |= 0x2000;
        } else {
            // Unknown key: let the model build its own reference.
            holder.mpObject = (void**)((void* (__thiscall*)(void*, u32, u32, void*))vfn(model, 0x0c))(
                model, 0u, s->mNameCap_98, s->mNameData_90);
            FUN_00478db0(&holder, 0, holder.mpObject);
        }
        if (holder.mpObject != 0) {
        ModelHolder* h = (ModelHolder*)holder.mpObject;

        ((void (__thiscall*)(Spatial*))vfn(s, 0xa4))(s);
        FUN_00b5f950(&s->pa0, 0, model);
        FUN_00478db0(&s->p9c, 0, h);

        if (s->mFlags50 & 8) {
            ((void (__thiscall*)(void*, ModelHolder*))vfn(model, 0x58))(model, h);
            float f = ((float (__thiscall*)(Spatial*))vfn(s, 0x34))(s);
            ((void (__thiscall*)(Spatial*, ModelHolder*, float))vfn(s, 0x64))(s, h, f);
        } else if (h->mFlags04 & 0x4000) {
            ((void (__thiscall*)(void*, ModelHolder*))vfn(model, 0x58))(model, h);
            float f = ((float (__thiscall*)(Spatial*))vfn(s, 0x34))(s);
            ((void (__thiscall*)(Spatial*, ModelHolder*, float))vfn(s, 0x64))(s, h, f);
        } else {
            s->mFlags50 |= 0x10;
            if (h->mFlags04 & 0x20000) {
                s->mFlags50 |= 0x40;
                float f = ((float (__thiscall*)(Spatial*))vfn(s, 0x34))(s) * h->mf6c;
                s->mf5c = f;
                s->mf60 = f;
            }
            if (((u8*)&h->mFlags04)[2] & 1) {
                float f = ((float (__thiscall*)(Spatial*))vfn(s, 0x34))(s);
                ((void (__thiscall*)(Spatial*, ModelHolder*, float))vfn(s, 0x64))(s, h, f);
            }
        }

        // Copy the live pose into the model.
        float* p = ((float* (__thiscall*)(Spatial*))vfn(s, 0x2c))(s);
        h->mPos0c[0] = p[0];
        h->mPos0c[1] = p[1];
        h->mPos0c[2] = p[2];
        h->mFlags08 |= 4;
        h->mVersion0a += 1;

        void* src = ((void* (__thiscall*)(Spatial*))vfn(s, 0x30))(s);
        Matrix33 tmp;
        FUN_0059c190(&tmp, src);
        h->mMatrix1c = tmp;
        h->mFlags08 |= 2;
        h->mVersion0a += 1;

        h->mf18 = s->mf64;
        h->mVersion0a += 1;
        loaded = true;
        }

        if (holder.mpObject != 0) {
            holder.mFlags |= 0x40000000;
            if (holder.mpObject != 0) {
                void** vt = *(void***)holder.mpObject;
                ((void (__thiscall*)(void*, EffectElementRef*, u32))vt[0x170 / 4])(
                    holder.mpObject, &holder, (holder.mFlags >> 31) & 1);
            }
        }
    }

finish:
    ((void (__thiscall*)(Spatial*, int))vfn(s, 0x8c))(s, 0);
    return loaded;
}

// ===========================================================================
// @ 0x00c8a890  eastl::vector<tEffectInfo>::erase
// ===========================================================================
// `this` is the vector member itself (belongs at Spatial+0xc0), not the Spatial.
// Shifts [last, vecEnd) down to `first`, destroys the vacated tail through the
// element's vtable slot 1, and moves vecEnd by (last - first).
EffectElem* __fastcall EraseEffect(EffectVector* v, int, EffectElem* first, EffectElem* last)
{
    u8* newEnd = (u8*)FUN_00c88d10(last, v->vecEnd, first);
    if ((u32)newEnd < (u32)v->vecEnd) {
        int count = (int)(((u8*)v->vecEnd - newEnd - 1) / sizeof(EffectElem)) + 1;
        for (EffectElem* p = (EffectElem*)newEnd; count > 0; --count, ++p) {
            if (p->p38 != 0) {
                void** vt = *(void***)p->p38;
                ((void (__thiscall*)(void*))vt[1])(p->p38);
            }
        }
    }
    v->vecEnd = (EffectElem*)((u8*)v->vecEnd +
        ((long)((u8*)first - (u8*)last) / (long)sizeof(EffectElem)) * (long)sizeof(EffectElem));
    return first;
}

// ===========================================================================
// @ 0x00c8a910  eastl::vector<tEffectInfo>::insert
// ===========================================================================
void __fastcall F8a910(EffectVector* v, int, EffectElem* pos, EffectElem* value)
{
    if (v->vecEnd != v->vecCap) {
        EffectElem* ins = pos;
        if (value >= pos && value < v->vecEnd) ins = value + 1;
        if (v->vecEnd != 0)
            FUN_00c88ba0(v->vecEnd, 0, v->vecEnd - 1);
        FUN_00c88d50(pos, v->vecEnd - 1, v->vecEnd);
        FUN_00c88c30(pos, 0, ins);
        v->vecEnd += 1;
        return;
    }

    // Grow: new capacity is twice the current size (minimum 1), then rebase.
    long count = (long)(v->vecEnd - v->vecBegin);
    long cap = count != 0 ? count * 2 : 1;
    u8* buf = (u8*)FUN_00f473a0((u32)(cap * sizeof(EffectElem)),
                                (void*)0x013ebb38, 0xd1, 0, (void*)0x013f09b4, 0);
    EffectElem* newPos = (EffectElem*)FUN_00c88cd0(v->vecBegin, pos, buf);
    FUN_00c88570(v->vecBegin, pos, value);
    if (newPos != 0) FUN_00c88ba0(newPos, 0, value);
    EffectElem* newEnd = (EffectElem*)FUN_00c88cd0(v->vecBegin, v->vecEnd, buf);
    FUN_00c88570(v->vecBegin, v->vecEnd, buf);

    if (v->vecBegin != 0) {
        if (*((int*)v->vecBegin - 1) != 0)
            FUN_00f47380(v->vecBegin);
    }
    v->vecEnd = newEnd;
    v->vecBegin = (EffectElem*)buf;
    v->vecCap = (EffectElem*)(buf + cap * sizeof(EffectElem));
}
