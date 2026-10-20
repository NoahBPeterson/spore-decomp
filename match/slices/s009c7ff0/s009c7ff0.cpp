// s009c7ff0 -- nSPCreatureAnim creature mesh instance: mesh bind/clear/resize, the body
// clearance queries, the 0x28-byte record copy/fill primitives and the creature_effect
// release helpers.  All layouts and offsets are read from the disassembly; the 2008 PDB
// predates the AutoRefCount revision, so eastl vectors are 0x14 bytes here (begin/end/cap
// + an 8-byte allocator slot) and mesh_data::posed_xforms sits at +0x08.
//
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>
#pragma intrinsic(fabs)
inline float Abs(float v) { return (float)fabs((double)v); }

typedef unsigned int  uint;
typedef unsigned long ulong;

// =====================================================================
// reference-counted objects: refcount at +0x40, Release virtual at +0x170
// =====================================================================
#define VPAD(n) virtual void vpad##n()

struct IRefObj {
    VPAD(0);  VPAD(1);  VPAD(2);  VPAD(3);  VPAD(4);  VPAD(5);  VPAD(6);  VPAD(7);
    VPAD(8);  VPAD(9);  VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15);
    VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20); VPAD(21); VPAD(22); VPAD(23);
    VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29); VPAD(30); VPAD(31);
    VPAD(32); VPAD(33); VPAD(34); VPAD(35); VPAD(36); VPAD(37); VPAD(38); VPAD(39);
    VPAD(40); VPAD(41); VPAD(42); VPAD(43); VPAD(44); VPAD(45); VPAD(46); VPAD(47);
    VPAD(48); VPAD(49); VPAD(50); VPAD(51); VPAD(52); VPAD(53); VPAD(54); VPAD(55);
    VPAD(56); VPAD(57); VPAD(58); VPAD(59); VPAD(60); VPAD(61); VPAD(62); VPAD(63);
    VPAD(64); VPAD(65); VPAD(66); VPAD(67); VPAD(68); VPAD(69); VPAD(70); VPAD(71);
    VPAD(72); VPAD(73); VPAD(74); VPAD(75); VPAD(76); VPAD(77); VPAD(78); VPAD(79);
    VPAD(80); VPAD(81); VPAD(82); VPAD(83); VPAD(84); VPAD(85); VPAD(86); VPAD(87);
    VPAD(88); VPAD(89); VPAD(90);
    virtual void Release(int complete);          // +0x170
};

struct RefObject : IRefObj {
    unsigned char pad_004[0x3c];
    int RefCount;                                // +0x40
};

// SP::cMWModel: the two members the slice touches (the full retail type is bigger).
struct cMWModel : RefObject {
    unsigned char pad_044[0x68 - 0x44];
    unsigned short mModificationCount;           // +0x68
    unsigned char pad_06a[0x90 - 0x6a];
};

// SP::cIModelWorld: the slice needs the manager vtable slots at +0x0c, +0x4c and +0xa4.
// The vtable starts at slot 0 here (IRefObj's pads are not part of this interface view),
// so slot N lives at vtable+N*4.
struct cIModelWorld {
    virtual void v000(); virtual void v004(); virtual void v008();      // 0x00..0x08
    virtual void* CreateModelGroup(void* a, void* b, int idx);          // +0x0c (ret 0xc)
    virtual void v010(); virtual void v014(); virtual void v018();      // 0x10..0x18
    virtual void v01c(); virtual void v020(); virtual void v024();      // 0x1c..0x24
    virtual void v028(); virtual void v02c(); virtual void v030();      // 0x28..0x30
    virtual void v034(); virtual void v038(); virtual void v03c();      // 0x34..0x3c
    virtual void v040(); virtual void v044(); virtual void v048();      // 0x40..0x48
    virtual bool AssignKeyModel(void* key, void* desc);                 // +0x4c (ret 8)
    virtual void v050(); virtual void v054(); virtual void v058();      // 0x50..0x58
    virtual void v05c(); virtual void v060(); virtual void v064();      // 0x5c..0x64
    virtual void v068(); virtual void v06c(); virtual void v070();      // 0x68..0x70
    virtual void v074(); virtual void v078(); virtual void v07c();      // 0x74..0x7c
    virtual void v080(); virtual void v084(); virtual void v088();      // 0x80..0x88
    virtual void v08c(); virtual void v090(); virtual void v094();      // 0x8c..0x94
    virtual void v098(); virtual void v09c(); virtual void v0a0();      // 0x98..0xa0
    virtual void AssignModel(void* model, void* group, int idx);        // +0xa4 (ret 0xc)
};

// SP::cModelInstance: only its virtual vtable is used here (Release at +0x170).
struct cModelInstance : RefObject {};

// =====================================================================
// the record primitives' element (0x28 bytes)
// =====================================================================
struct Elem28 {
    uint  key;                                   // +0x00
    uint  idx;                                   // +0x04
    float f[8];                                  // +0x08
};

// =====================================================================
// eastl::vector<T, sp_vector_allocator> -- retail layout 0x14
// =====================================================================
template <class T>
struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned char mAllocatorSlot[8];

    ulong size()  const { return (ulong)(mpEnd - mpBegin); }
    bool  empty() const { return mpBegin == mpEnd; }
    T*    begin()       { return mpBegin; }
    T*    end()         { return mpEnd; }
    T&    operator[](ulong i) { return mpBegin[i]; }

    void SetBodyCount(ulong n);                  // 0x009c8170 (ret 4)
    void erase(T* first, T* last);               // 0x009c6d20
    void resize(T* end, ulong n, const T* v);    // 0x009c6d70
};

// =====================================================================
// creature body / static data (retail; body stride 0x468)
// =====================================================================
struct body_static_data {
    unsigned char pad_000[0x10c];
    float rx;                                    // +0x10c
    float ry;                                    // +0x110
    float rz;                                    // +0x114
    unsigned char pad_118[0x130 - 0x118];
    float c130;                                  // +0x130
    float c134;                                  // +0x134
    float c138;                                  // +0x138
    float c13c;                                  // +0x13c
    float c140;                                  // +0x140
    float rest_center[3];                        // +0x144
    ulong flags_150;                             // +0x150
    unsigned char pad_154[0x1f8 - 0x154];
    ulong f1f8;                                  // +0x1f8
    ulong f1fc;                                  // +0x1fc
    ulong f200;                                  // +0x200
    unsigned char pad_204[0x208 - 0x204];
    ulong f208;                                  // +0x208
    unsigned char pad_20c[0x21c - 0x20c];
    ulong bone_idx;                              // +0x21c
    unsigned char pad_220[0x324 - 0x220];
    float loc[3];                                // +0x324
};

struct creature_static_data {
    unsigned char pad_000[0x37c];
    ulong num_bones_with_mesh_parts;             // +0x37c
    bool  block_default_deforms_hack;            // +0x380
    unsigned char pad_381[3];
    body_static_data* BodiesBegin;               // +0x384
    body_static_data* BodiesEnd;                 // +0x388
};

struct creature_instance_data {
    creature_static_data* sd;                    // +0x00
    unsigned char pad_004[0x18 - 0x04];
    float pos[3];                                // +0x18
    unsigned char pad_024[0x34 - 0x24];
    unsigned char flags_34;                      // +0x34
    unsigned char pad_035[0x3c - 0x35];
    float quat[4];                               // +0x3c
    unsigned char pad_04c[0x70 - 0x4c];
    float scale;                                 // +0x70
    unsigned char pad_074[0x2e4 - 0x74];
    unsigned char* mpAnimsBegin;                 // +0x2e4 (0x2bc-byte records)
    unsigned char* mpAnimsEnd;                   // +0x2e8
};

struct model_instance_vector {                   // retail vector header at +0x98 (stride 0x8c)
    unsigned char* begin;                        // +0x00
    unsigned char* end;                          // +0x04
};

struct bone { float m[12]; };                    // 0x30

struct body_mesh_data {                          // 0x14
    float     local_origin[3];                   // +0x00
    cMWModel* model;                             // +0x0c
    ulong     modcount;                          // +0x10
};

// =====================================================================
// the object itself (retail size 0x3c)
// =====================================================================
struct ResKey { ulong a, b, c; };

struct creature_mesh_instance_data {
    struct mesh_data {
        cMWModel*       model;                   // +0x00
        ulong           modcount;                // +0x04
        sp_vector<bone> posed_xforms;            // +0x08 (0x14 -> +0x1c)
        void Clear();                            // 0x009c6c30
        void Assign(cMWModel* m);                // 0x00478db0 (thiscall ret 4)
    };

    creature_instance_data* creature;            // +0x00
    cIModelWorld*           world;               // +0x04
    mesh_data               mesh_lo;             // +0x08
    bool  force_not_in_world;                    // +0x24
    bool  enable_auto_eye_lookat;                // +0x25
    unsigned short pad_26;                       // +0x26
    sp_vector<body_mesh_data> BodyMeshes;        // +0x28

    creature_mesh_instance_data* ctor();         // 0x009c8200
    __declspec(noinline) void Clear();            // 0x009c7ff0
    bool Bind(creature_instance_data* c, cIModelWorld* w, void* unused,
              ResKey* key, bool eye_lookat);     // 0x009c8050 (ret 0x14)
    void SetWorldState();                        // 0x009c8890
    bool Init(creature_instance_data* c, cIModelWorld* w, void* data); // 0x009c8230 (ret 0x10)
    void Dispose();                              // 0x009c8460
    void RefreshWorldState();                    // 0x009c8900

    static void MinClearance(float* minOut, creature_static_data* sd);        // 0x009c8630
    static void MinClearanceIdx(float* minOut, uint* idxOut, creature_static_data* sd); // 0x009c86e0
    static void BodyToWorld(float* out, uint* outIdx, body_static_data* b);     // 0x009c87e0
};

// =====================================================================
// helpers, all VA-resolved
// =====================================================================
uint  ModelIdToGroup(void* key, cIModelWorld* world, void* out);    // 0x009c66a0
void  ModelGroupAssign(cMWModel* m, cMWModel* v);                   // 0x00478db0 (thiscall ret 4, via mesh_lo)
void* ElemInitCopyB(void* first, void* last, void* dst);            // 0x009c6860
void  ElemDestroy(uint* first, uint* last);                         // 0x009c67e0

struct body_mesh_data;
void  BodyMeshErase(body_mesh_data* first, body_mesh_data* last);                // 0x009c6d20
void  BodyMeshResize(body_mesh_data* end, ulong n, const body_mesh_data* v);     // 0x009c6d70
struct Vec3 { float x, y, z; };
Vec3 QuaternionVectorTransform(const float* q, const float* v);       // 0x0099c1a0 (3-float sret, ret 8)
extern "C" void AudioSetFlag(void* sound, char flag);               // 0x009fbd10
extern "C" void AudioSetListener2(void* param, char flag);          // 0x009fbd70
extern "C" int  AudioQueryB(void* param);                           // 0x009fbe00
void* InvalidEditorModelKey(ResKey* key, uint flags);               // 0x0068c700
void* EngineGetManager();                                           // 0x00401010

// =====================================================================
// @ 0x009c7ff0
void creature_mesh_instance_data::Clear()
{
    force_not_in_world = false;
    creature = 0;
    mesh_lo.Clear();
    body_mesh_data* b = BodyMeshes.mpBegin;
    body_mesh_data* e = BodyMeshes.mpEnd;
    void* first = ElemInitCopyB(e, e, b);
    ElemDestroy((uint*)first, (uint*)e);
    BodyMeshes.mpEnd += BodyMeshes.mpBegin - BodyMeshes.mpEnd;
}

// @ 0x009c8050
bool creature_mesh_instance_data::Bind(creature_instance_data* c, cIModelWorld* w,
                                       void* unused, ResKey* key, bool eye_lookat)
{
    Clear();
    creature = c;
    if (world != w) {
        if (w)
            w->v000();
        cIModelWorld* old = world;
        world = w;
        if (old)
            old->v004();
    }
    ResKey local = *key;
    if ((local.c & 0xff0000) == 0x620000)
        InvalidEditorModelKey(&local, 0);
    cIModelWorld* mgr = (cIModelWorld*)EngineGetManager();
    struct ResDesc { ulong a; unsigned short b, c; } desc;
    desc.b = 0;
    desc.c = 4;
    desc.a = 0x609b763;
    if (!mgr->AssignKeyModel(&local, &desc))
        return false;
    cMWModel* m = (cMWModel*)world->CreateModelGroup((void*)key->a, (void*)key->c, 0);
    mesh_lo.Assign(m);
    if (mesh_lo.model) {
        mesh_lo.modcount = mesh_lo.model->mModificationCount - 1;
        mesh_lo.model->Release(0);
        if ((key->c & 0xff0000) == 0x610000)
            *(uint*)((char*)mesh_lo.model + 4) |= 0x1000;
    }
    enable_auto_eye_lookat = eye_lookat;
    return mesh_lo.model != 0;
}

// @ 0x009c8170
void sp_vector<body_mesh_data>::SetBodyCount(ulong n)
{
    ulong have = size();
    if (n > have) {
        body_mesh_data tmp;
        tmp.local_origin[0] = 0.0f;
        tmp.local_origin[1] = 0.0f;
        tmp.local_origin[2] = 0.0f;
        tmp.model = 0;
        resize(mpEnd, n - have, &tmp);
        return;
    }
    erase(mpBegin + n, mpEnd);
}

// @ 0x009c8200
creature_mesh_instance_data* creature_mesh_instance_data::ctor()
{
    world = 0;
    mesh_lo.model = 0;
    mesh_lo.posed_xforms.mpBegin = 0;
    mesh_lo.posed_xforms.mpEnd = 0;
    mesh_lo.posed_xforms.mpCapacity = 0;
    BodyMeshes.mpBegin = 0;
    BodyMeshes.mpEnd = 0;
    BodyMeshes.mpCapacity = 0;
    Clear();
    return this;
}

// @ 0x009c8230
bool creature_mesh_instance_data::Init(creature_instance_data* c, cIModelWorld* w, void* data)
{
    Clear();
    creature = c;
    if (world != w) {
        if (w)
            w->v000();
        cIModelWorld* old = world;
        world = w;
        if (old)
            old->v004();
    }
    uint mdl = ModelIdToGroup((void*)data, world, mesh_lo.posed_xforms.mpBegin);
    mesh_lo.Assign((cMWModel*)mdl);
    if (*(char*)((char*)data + 0x34))
        mesh_lo.model->pad_044[0] |= 0x1000;
    else
        mesh_lo.model->pad_044[0] &= 0xffffefff;
    world->AssignModel(mesh_lo.model, *(void**)((char*)data + 8), -1);

    ulong nparts = (ulong)(*(unsigned char**)(*(char**)data + 0x9c) -
                           *(unsigned char**)(*(char**)data + 0x98)) / 0x8c;
    ulong nbodies = (ulong)(creature->mpAnimsEnd - creature->mpAnimsBegin) / 0x2bc;
    BodyMeshes.SetBodyCount(nparts);
    if (nbodies != 0) {
        int off = 0;
        ulong left = nbodies;
        do {
            body_static_data* sb = (body_static_data*)((char*)creature->sd->BodiesBegin + off);
            uint bi = (uint)sb->bone_idx;
            if (bi < nparts && *(cMWModel**)(*(char**)((char*)data + 0xc) + bi * 4) != 0) {
                body_mesh_data* bmd = (body_mesh_data*)((char*)BodyMeshes.mpBegin + bi * 0x14);
                bmd->local_origin[0] = sb->loc[0] + sb->rest_center[0];
                bmd->local_origin[1] = sb->loc[1] + sb->rest_center[1];
                bmd->local_origin[2] = sb->loc[2] + sb->rest_center[2];
                void* mi = (void*)ModelIdToGroup(
                    *(void**)(*(char**)((char*)data + 0xc) + bi * 4), world,
                    &bmd->model);
                cMWModel* old = (cMWModel*)bmd->model;
                if ((void*)old != mi) {
                    if (mi)
                        ++*(int*)((char*)mi + 0x40);
                    bmd->model = (cMWModel*)mi;
                    if (old) {
                        if (old->RefCount > 1)
                            --old->RefCount;
                        else
                            old->Release((old->pad_004[0] & 0x80) != 0);
                    }
                }
                if (*(char*)((char*)data + 0x34))
                    bmd->model->pad_044[0] |= 0x1000;
                else
                    bmd->model->pad_044[0] &= 0xffffefff;
                if (*(void**)((char*)data + 0x20) != *(void**)((char*)data + 0x24))
                    world->AssignModel(bmd->model,
                                       *(void**)(*(char**)((char*)data + 8) + bi * 4), -1);
            }
            off += 0x468;
            --left;
        } while (left);
    }
    enable_auto_eye_lookat = (bool)*(char*)((char*)data + 0x34);
    return true;
}

// @ 0x009c8460
void creature_mesh_instance_data::Dispose()
{
    void* sfx = (void*)*(void**)((char*)this + 0x94);
    if (sfx) {
        if (!*(char*)((char*)this + 0x30) ||
            (*(ulong*)((char*)this + 0x34) & 0x800020) != 0x800000) {
            char flag = 1;
            if (*(char*)((char*)this + 0x30) &&
                (*(unsigned char*)((char*)this + 0x34) & 0x10))
                flag = 0;
            AudioSetListener2(sfx, flag);
        }
        AudioQueryB(sfx);
        *(void**)((char*)this + 0x94) = 0;
    }
}

// @ 0x009c8890
void creature_mesh_instance_data::SetWorldState()
{
    void* sound = (void*)*(void**)((char*)this + 0x8c);
    if (!(*(char*)((char*)this + 0x30) &&
          (*(ulong*)((char*)this + 0x34) & 0x800020) == 0x800000)) {
        if (sound) {
            char flag = 1;
            if (*(char*)((char*)this + 0x30) &&
                (*(unsigned char*)((char*)this + 0x34) & 0x10))
                flag = 0;
            AudioSetFlag(sound, flag);
        }
    }
    void* obj = (void*)*(void**)((char*)this + 0x8c);
    if (obj) {
        *(void**)((char*)this + 0x8c) = 0;
        ((IRefObj*)obj)->vpad1();
    }
}

// @ 0x009c8900
void creature_mesh_instance_data::RefreshWorldState()
{
    void* sfx = (void*)*(void**)((char*)this + 0x94);
    if (sfx) {
        char flag = 1;
        if (*(char*)((char*)this + 0x30) &&
            (*(unsigned char*)((char*)this + 0x34) & 0x10))
            flag = 0;
        AudioSetListener2(sfx, flag);
    }
    sfx = (void*)*(void**)((char*)this + 0x8c);
    if (sfx) {
        char flag = 1;
        if (*(char*)((char*)this + 0x30) &&
            (*(unsigned char*)((char*)this + 0x34) & 0x10))
            flag = 0;
        AudioSetFlag(sfx, flag);
    }
}

// @ 0x009c8630
void creature_mesh_instance_data::MinClearance(float* minOut, creature_static_data* sd)
{
    int n = (int)((char*)sd->BodiesEnd - (char*)sd->BodiesBegin);
    n = n / 0x468;
    if (n > 0) {
        body_static_data* b = sd->BodiesBegin;
        do {
            if (b->flags_150 & 8) {
                float a0 = Abs(b->c130);
                float a1 = Abs(b->c134);
                float a2 = Abs(b->c138);
                float h = b->rz - ((b->c13c * a1 + b->c140 * a2) + b->c138 * a0);
                if (h < *minOut)
                    *minOut = h;
            }
            b = (body_static_data*)((char*)b + 0x468);
            --n;
        } while (n);
    }
}

// @ 0x009c86e0
void creature_mesh_instance_data::MinClearanceIdx(float* minOut, uint* idxOut,
                                                  creature_static_data* sd)
{
    int n = (int)((char*)sd->BodiesEnd - (char*)sd->BodiesBegin);
    n = n / 0x468;
    int i = 0;
    if (n > 0) {
        body_static_data* base = sd->BodiesBegin;
        do {
            body_static_data* b = (body_static_data*)((char*)base + i * 0x468);
            if (b->f208 == 0 && (b->flags_150 & 2) && !(b->flags_150 & 4)) {
                float h = b->rz - ((b->c13c * Abs(b->c134)
                                  + b->c140 * Abs(b->c138))
                                 + Abs(b->c130) * b->c138);
                if (h < *minOut) {
                    *minOut = h;
                    *idxOut = (uint)i;
                }
            }
            ++i;
        } while (i < n);
    }
}

// @ 0x009c87e0
void creature_mesh_instance_data::BodyToWorld(float* out, uint* outIdx, body_static_data* b)
{
    if ((b->flags_150 & 0x60) == 0) {
        *outIdx = (uint)b->f1f8;
        Vec3 v = QuaternionVectorTransform((const float*)((const char*)b + 0x118),
                                           b->rest_center);
        out[0] = b->rx - v.x;
        out[1] = b->ry - v.y;
        out[2] = b->rz - v.z;
        return;
    }
    *outIdx = (uint)b->f1fc;
    out[0] = b->rx;
    out[1] = b->ry;
    out[2] = b->rz;
}

// =====================================================================
// 0x28-byte record primitives (upward copy, backward copy, copy-construct n)
// =====================================================================

// @ 0x009c8510
void Elem28CopyFwd(Elem28* first, Elem28* last, Elem28* dst)
{
    if (first != last) {
        float* d = (float*)((char*)dst + 0x14);
        float* s = (float*)((char*)first + 0x14);
        do {
            if (dst) {
                dst->key = first->key;
                dst->idx = first->idx;
                d[-3] = s[-3]; d[-2] = s[-2]; d[-1] = s[-1];
                d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
            }
            first = (Elem28*)((char*)first + 0x28); s += 10;
            dst   = (Elem28*)((char*)dst + 0x28);   d += 10;
        } while (first != last);
    }
}

// @ 0x009c85c0
void Elem28CopyBack(Elem28* first, Elem28* last, Elem28* dstEnd)
{
    if (last != first) {
        float* d = (float*)((char*)dstEnd + 0x14);
        float* s = (float*)((char*)last + 0x14);
        do {
            last   = (Elem28*)((char*)last   - 0x28); s -= 10;
            dstEnd = (Elem28*)((char*)dstEnd - 0x28); d -= 10;
            dstEnd->key = last->key;
            dstEnd->idx = last->idx;
            d[-3] = s[-3]; d[-2] = s[-2]; d[-1] = s[-1];
            d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        } while (last != first);
    }
}

// @ 0x009c8970
void Elem28ConstructRange(Elem28* first, Elem28* last, const Elem28* src)
{
    while (first != last) {
        first->key = src->key;
        first->idx = src->idx;
        const float* s = (const float*)((const char*)src + 0x8);
        float* d = (float*)((char*)first + 0x14);
        d[-3] = s[0]; d[-2] = s[1]; d[-1] = s[2];
        d[0] = s[3]; d[1] = s[4]; d[2] = s[5]; d[3] = s[6]; d[4] = s[7];
        ++first;
    }
}

// @ 0x009c89d0
void Elem28FillN(Elem28* dst, ulong n, const Elem28* src)
{
    if (!n)
        return;
    float* d = (float*)((char*)dst + 0x14);
    do {
        if (dst) {
            dst->key = src->key;
            dst->idx = src->idx;
            const float* s = (const float*)((const char*)src + 0x8);
            d[-3] = s[0]; d[-2] = s[1]; d[-1] = s[2];
            d[0] = s[3]; d[1] = s[4]; d[2] = s[5]; d[3] = s[6]; d[4] = s[7];
        }
        --n;
        dst = (Elem28*)((char*)dst + 0x28);
        d += 10;
    } while (n);
}
