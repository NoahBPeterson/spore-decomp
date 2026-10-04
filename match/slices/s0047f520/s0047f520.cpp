// Slice s0047f520: SP::cSPEditorHandle subclasses (BallConnector, Deform) -- /Od code.
// Retail layouts differ from the 2008 PDB for the Deform class (retail mSetPickData is at +0x118),
// so members are accessed through typed offsets where the PDB layout does not apply.
#include "types.h"

typedef uint32_t u32;

struct Vec3 { float x, y, z; };
struct Mat3 { float m[9]; };
struct cMWModel { char pad[0x44]; u32 mGroups[2]; };

struct ModelManagerIface {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual u32 GetGroupID(u32 name, int flag);   // slot 0x28
};

struct cSPEditorHandle;

extern ModelManagerIface* ModelManager();
extern void* EditorTuning();                       // tuning struct, Vec3 members at +0x6c.. +0x90
extern void  cSPEditorHandle_Shutdown(cSPEditorHandle*);   // SP::cSPEditorHandle::Shutdown
extern void  cSPEditorHandle_BaseDtor(cSPEditorHandle*);   // FUN_0047d870
extern void  cSPEditorHandle_BaseCtor(cSPEditorHandle*);   // FUN_0047d6a0
extern void  cSPEditorHandle_BaseInit(cSPEditorHandle*, void* a, int b, int c, int d); // FUN_0047db30
extern void  Transform_Ctor(void* t);              // 0x409930
extern void  TrianglePinningInfo_Ctor(void* p);    // FUN_004e8f70
extern void  TrianglePinningInfo_Dtor(void* p);    // FUN_004ae250
extern void  Matrix3_Assign(Mat3* dst, void* src); // Matrix3::Assign 0x41cb40
extern void  cSPTransform_Assign(void* dst, void* src);
extern void  operator_delete_array(void* p, ...);  // EASTL_allocator_deallocate (0xf47380)

extern const float kDeformVec0, kDeformVec1, kDeformVec2;  // 0x15d4fd8..0x15d4fe0
extern const float kDefaultHandleOffset[3];                // 0x15d4aa8
extern const float kPreviewDelta;                          // 0x1471064 (0.5f)
extern char gEmptyString[];                                // 0x1667bac

#define AT(T, p, off) (*(T*)((char*)(p) + (off)))

struct cSPEditorBlock;

// Common handle layout (retail, 0x50 bytes)
struct cSPEditorHandle {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void GetPosition(Vec3* out);   // slot 0x24
    void* mRefCountVft;                    // +4
    char pad8[8];
    cSPEditorBlock* mBlock;                // +0x10
    cMWModel* mModel;                      // +0x14
    cMWModel* mOverdrawModel;              // +0x18
    char pad1c[0x34];
};

// @ 0x47f520
void __fastcall BallConnector_Dtor(cSPEditorHandle* self)
{
    *(void**)self = (void*)0x13ef1c0;
    self->mRefCountVft = (void*)0x13ef1ac;
    cSPEditorHandle_Shutdown(self);
    cSPEditorHandle_BaseDtor(self);
}

// @ 0x47f550  (QueryInterface-style: returns this for 3 known interface IDs)
void* __stdcall BallConnector_QueryInterface(void* self, u32 id)
{
    switch (id) {
    case 0xee3f516e: return self;
    case 0x050a1fe5: return self;
    case 0x050e8e23: return self;
    }
    return 0;
}

static void SetGroupBit(cMWModel* m, u32 bit)
{
    if (bit < 0x40)
        m->mGroups[bit >> 5] |= 1u << (bit % 32);
}

// @ 0x47f5a0  push position + orientation to both models' transform components
void __fastcall cSPEditorHandle_UpdateModelTransforms(cSPEditorHandle* self)
{
    Vec3 pos;
    Mat3 rot;
    self->GetPosition(&pos);
    Matrix3_Assign(&rot, (char*)AT(void*, self, 0x10) + 0x60);
    cMWModel* models[2] = { self->mModel, self->mOverdrawModel };
    for (int i = 0; i < 2; i++) {
        char* m = (char*)models[i];
        if (m) {
            Vec3* p = (Vec3*)(m + 0xc);
            *p = pos;
            AT(uint16_t, m, 8) |= 4;
            AT(uint16_t, m, 10) += 1;
            Mat3* r = (Mat3*)(m + 0x1c);
            *r = rot;
            AT(uint16_t, m, 8) |= 2;
            AT(uint16_t, m, 10) += 1;
        }
    }
}

// @ 0x47f720
void __fastcall BallConnector_Init(cSPEditorHandle* self, int /*edx*/, void* param)
{
    cSPEditorHandle_BaseInit(self, param, 1, 0, 0);
    if (self->mBlock) {
        if (self->mModel)
            SetGroupBit(self->mModel, ModelManager()->GetGroupID(0x900c6cdd, 0));
        if (self->mOverdrawModel) {
            SetGroupBit(self->mOverdrawModel, ModelManager()->GetGroupID(0x22fff11, 0));
            SetGroupBit(self->mOverdrawModel, ModelManager()->GetGroupID(0x900c6cdd, 0));
        }
    }
}

// @ 0x47f960  handle position: block's vec at +0x48, or a default constant
Vec3* __fastcall cSPEditorHandle_GetBlockOffset(cSPEditorHandle* self, int /*edx*/, Vec3* out)
{
    if (self->mBlock) {
        *out = AT(Vec3, self->mBlock, 0x48);
    } else {
        out->x = kDefaultHandleOffset[0];
        out->y = kDefaultHandleOffset[1];
        out->z = kDefaultHandleOffset[2];
    }
    return out;
}

// @ 0x47f9e0
Vec3* __fastcall cSPEditorHandle_GetTuningVec90(void* self, int /*edx*/, Vec3* out)
{
    *out = AT(Vec3, EditorTuning(), 0x90);
    return out;
}

// @ 0x47fa30  SP::cSPEditorHandleDeform::cSPEditorHandleDeform
void* __fastcall cSPEditorHandleDeform_Ctor(cSPEditorHandle* self)
{
    cSPEditorHandle_BaseCtor(self);
    *(void**)self = (void*)0x13ef270;
    self->mRefCountVft = (void*)0x13ef25c;
    Transform_Ctor((char*)self + 0x50);
    AT(u32, self, 0xac) = 0x95f07f3d;      // mPinningType
    AT(u32, self, 0xb0) = 0;               // mAxisToIgnore
    AT(void*, self, 0xb4) = 0;             // mSymmetricHandle
    AT(char, self, 0x118) = 0;             // mSetPickData
    // empty eastl string at +0x11c
    AT(char*, self, 0x11c) = 0;
    AT(char*, self, 0x120) = 0;
    AT(char*, self, 0x124) = 0;
    AT(char*, self, 0x11c) = gEmptyString;
    AT(char*, self, 0x120) = AT(char*, self, 0x11c);
    AT(char*, self, 0x124) = AT(char*, self, 0x11c) + 1;
    for (int off = 0x12c; off <= 0x144; off += 0xc) {
        AT(float, self, off)     = kDeformVec0;
        AT(float, self, off + 4) = kDeformVec1;
        AT(float, self, off + 8) = kDeformVec2;
    }
    AT(float, self, 0x184) = kPreviewDelta;
    TrianglePinningInfo_Ctor((char*)self + 0x188);
    AT(char, self, 0x1d5) = 0;
    return self;
}

// @ 0x47fc10  Deform destructor
void __fastcall cSPEditorHandleDeform_Dtor(cSPEditorHandle* self)
{
    *(void**)self = (void*)0x13ef270;
    self->mRefCountVft = (void*)0x13ef25c;
    extern void __fastcall cSPEditorHandleDeform_Shutdown(cSPEditorHandle*);
    cSPEditorHandleDeform_Shutdown(self);
    void** held = &AT(void*, self, 0x18c);
    if (*held) {
        // release: vtable slot 1
        (*(void (__fastcall**)(void*, int))(*(char**)*held + 4))(*held, 0);
    }
    char** str = (char**)((char*)self + 0x11c);
    if (str[2] - str[0] > 1) {
        if (str[0])
            operator_delete_array(str[0], self, str, str[2] - str[0]);
    }
    cSPEditorHandle_BaseDtor(self);
}

// @ 0x47fcb0  Deform shutdown
void __fastcall cSPEditorHandleDeform_Shutdown(cSPEditorHandle* self)
{
    cSPEditorHandle_Shutdown(self);
    AT(u32, self, 0xb4) = 0;
    TrianglePinningInfo_Dtor((char*)self + 0x188);
}

// @ 0x47fce0
void* __stdcall Deform_QueryInterface(void* self, u32 id)
{
    switch (id) {
    case 0xee3f516e: return self;
    case 0x050a1fe5: return self;
    case 0x050a993c: return self;
    }
    return 0;
}

extern void __fastcall DeformHandleData_Assign(void* dst, void* src); // FUN_0047fda0
extern void* TransformFromBlock(void* out, void* blockXform);         // FUN_004362a0
extern void  Vec3_Apply(Vec3* v, void* arg);                          // FUN_0044d4f0 (thiscall)
extern void  Deform_UpdateHandle(void* self, char flag);              // FUN_0047fe20

// @ 0x47fd30
void __fastcall Deform_SetData(char* self, int /*edx*/, void* data, char flag)
{
    DeformHandleData_Assign(self + 0x50, data);
    if (AT(void*, self, 0x10)) {
        char tmp[0x38];
        TransformFromBlock(tmp, AT(char*, self, 0x10));
        Vec3_Apply((Vec3*)tmp, self + 0x90);
        Vec3_Apply((Vec3*)tmp, self + 0x9c);
    }
    Deform_UpdateHandle(self, flag);
}

// @ 0x47fda0  copy cModelDeformationHandle (0x58 bytes: dword, transform, 8 dwords)
u32* __fastcall DeformHandleData_Copy(u32* dst, int /*edx*/, u32* src)
{
    dst[0] = src[0];
    cSPTransform_Assign(dst + 1, src + 1);
    for (int i = 0xf; i <= 0x16; i++)
        dst[i] = src[i];
    return dst;
}

extern void  Deform_SetFade(char* self, float f);                         // FUN_004809a0
extern Vec3* Vec3_Sub(Vec3* out, void* a, void* b);                       // FUN_0041db10
extern Mat3* Mat3_FromXform(void* out, void* xf);                         // FUN_0041ded0
extern Vec3* Mat3_TransformDir(Vec3* out, Mat3* m, Vec3* v);              // FUN_0047ff90
extern Vec3* Vec3_Normalize(Vec3* out, Vec3* v);                          // FUN_00436ce0
extern float Vec3_Dot(Vec3* a, void* b);                                  // FUN_00455cc0

// @ 0x47fe20
void __fastcall Deform_UpdateDirection(cSPEditorHandle* self, int /*edx*/, char flag)
{
    char* p = (char*)self;
    if (flag == 0) {
        float d = AT(float, p, 0xa8);
        if (d < 0.0f || 1.0f < d)
            Deform_SetFade(p, 0.0f);
        else
            Deform_SetFade(p, d);
    }
    Vec3 dir;
    Vec3 tmp = *Vec3_Sub(&dir, p + 0x9c, p + 0x90);
    char xf[0x24];
    Mat3 m = *Mat3_FromXform(xf, (char*)AT(char*, self->mBlock, 0x10) + 0x1c);
    tmp = *Mat3_TransformDir(&dir, &m, &tmp);
    Vec3 nrm;
    Vec3* n = Vec3_Normalize(&nrm, &tmp);
    AT(Vec3, p, 0x12c) = *n;
    // virtual slot 5 (+0x14)
    (*(void (__fastcall**)(void*, int))(*(char**)p + 0x14))(p, 0);
}

// @ 0x47ff90  three dot products of a vector against rows of a 3x3 matrix
Vec3* Mat3_TransformDir_(Vec3* out, char* mat, void* v)
{
    float a = Vec3_Dot((Vec3*)v, mat);
    float b = Vec3_Dot((Vec3*)v, mat + 0xc);
    float c = Vec3_Dot((Vec3*)v, mat + 0x18);
    out->x = a; out->y = b; out->z = c;
    return out;
}

struct Iface28 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual u32 GetGroupID(u32 name, int flag); };

// @ 0x480030  SP::cSPEditorHandleDeform::Init
void __fastcall cSPEditorHandleDeform_Init(cSPEditorHandle* self, int /*edx*/, Iface28* mgr, void* a3, void* data, char a5)
{
    DeformHandleData_Assign((char*)self + 0x50, data);
    cSPEditorHandle_BaseInit(self, a3, a5, 0, 0);
    if (self->mModel)
        SetGroupBit(self->mModel, mgr->GetGroupID(0x1ba53ea, 0));
    if (self->mOverdrawModel) {
        SetGroupBit(self->mOverdrawModel, mgr->GetGroupID(0x1ba53eb, 0));
        SetGroupBit(self->mOverdrawModel, mgr->GetGroupID(0x22fff11, 0));
    }
    AT(char, self, 0x1d4) = 0;
    Deform_SetData((char*)self, 0, data, 0);
}

// @ 0x480280  handle colour/vec chosen by pinning type (+0x8c) from EditorTuning
Vec3* __fastcall Deform_GetTuningVec(char* self, int /*edx*/, Vec3* out)
{
    char* t = (char*)EditorTuning();
    u32 k = AT(u32, self, 0x8c);
    if (k == 0x503283aa)      *out = AT(Vec3, t, 0x78);
    else if (k == 0xe20e2032) *out = AT(Vec3, t, 0x84);
    else                      *out = AT(Vec3, t, 0x6c);
    return out;
}
