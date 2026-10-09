// Bakes four-direction impostor sprites for a model resource into two 256x256 sprite sheets
// and publishes the results as properties on the owning object.
// Behavioural reconstruction of a huge /Od /Ob1 /arch:SSE function; NOT byte-exact.
#include "types.h"

// Call virtual slot at byte offset `off` of `obj` (__thiscall).
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
typedef void* (__thiscall *Fn0)(void*);
typedef void* (__thiscall *Fn1)(void*, void*);
typedef void* (__thiscall *Fn3)(void*, void*, void*, void*);
typedef void* (__thiscall *Fn4)(void*, void*, void*, void*, void*);
typedef void* (__thiscall *Fn7)(void*, void*, void*, void*, void*, void*, void*, void*);
#define VC0(o, off) ((Fn0)VSLOT(o, off))(o)
#define VC1(o, off, a) ((Fn1)VSLOT(o, off))(o, (void*)(a))
#define VC3(o, off, a, b, c) ((Fn3)VSLOT(o, off))(o, (void*)(a), (void*)(b), (void*)(c))
#define VC4(o, off, a, b, c, d) ((Fn4)VSLOT(o, off))(o, (void*)(a), (void*)(b), (void*)(c), (void*)(d))
#define VC7(o, off, a, b, c, d, e, f, g) ((Fn7)VSLOT(o, off))(o, (void*)(a), (void*)(b), (void*)(c), (void*)(d), (void*)(e), (void*)(f), (void*)(g))

struct ResourceKey { uint32_t instance, type, group; };

// Counted resource: refcount at +0x40, model bounds at +0x70 (min) / +0x7c (max).
struct ModelResource {
    void** vtbl;
    char pad0[0x3c];
    int refCount;
    char pad1[0x2c];
    float boundsMin[3];
    float boundsMax[3];
};

extern "C++" {
void ReleaseRef(void* obj);                                     // Counted::Release @ 0x40f360
bool GetProperty(void* props, uint32_t id, ResourceKey* out);   // 0x6a1250
void* GetRenderDevice();                                        // 0x67dda0
void* GetRenderFormat();                                        // 0x67dd60
void* GetGraphicsManager();                                     // 0x67dd50
void* GetCompositor();                                          // 0x67ddb0
void* GetPropertyService();                                     // 0x67dcd0
void* GetMessageService();                                      // 0x67dcc0
float Vector3_MaxComponent(float* v);                           // 0x41bf30
void* EASTL_allocator_allocate(uint32_t sz, const char* name, int a, int b, int c, int d); // 0x00f473a0
void* NewSpriteTexture(int w, int h);                           // 0x4328d0
void* NewBakeSprites();                                         // Graphics::BakeSprites::BakeSprites
void SetSpriteParam(void* tex, float v, int z);                 // 0x11f0440
void FinishBake(void* tex, float a, float b, void* sprites);    // 0x430ca0
void BuildBasis(float* out, float a, float b, float c, float d, float e, float f, float g, float h, float i);  // 0x432c50
void CameraCtor(void* cam);          // 0x7c3f70
void CameraSetMode(void* cam, int m);// 0x7c4dd0
void BeginRender();                  // 0x7618e0
void CameraSetTarget(void* cam, void* t);  // 0x7c3cb0
void DefaultsCtor(void* p);          // 0x432830
void ClearState();                   // 0x409930
void SetRenderTarget(void* t, int z);// 0x7c3ce0
void ApplyCamera(void* flagsBlock);  // 0x7c4d00
void SetOrtho(float a, float b);     // 0x7c5440
void SetNear(uint32_t bits);         // 0x7c4ba0
void SetFar(float f);                // 0x7c4bc0
void SetViewport(int x, int y, int w, int h);  // 0x7c5310
bool NeedsFlush();                   // 0x7c4fd0
void Flush(int n);                   // 0x7c3c50
void FlushEnd();                     // 0x7c3c10
void EndRender();                    // 0x7c3ba0
void EndCamera();                    // 0x7c4000
void* GetVariantKey(uint32_t id, int a, int b = 0);   // 0x6b1f90
void RegisterSprite(void* sheet, void* key, void* variantKey);  // 0x7b10d0
void PackKeys(void* dst);            // 0x422f40
void PackFloat(void* dst);           // 0x428060
void FreeVariant(int x);             // 0x93db80
}

static void AssignRef(void** slot, void* neu) {
    void* old = *slot;
    if (neu != old) {
        if (neu) VC0(neu, 0);
        *slot = neu;
        if (old) VC0(old, 4);
    }
}

// @ 0x00430e70
void BakeImpostorSprites(void* props, void* resMgr, void* notifyTarget)
{
    ModelResource* model = 0;
    ResourceKey key = {0, 0, 0};
    if (GetProperty(props, 0xf9efbb, &key)) {
        ModelResource* m = (ModelResource*)VC3(resMgr, 0xc, key.instance, key.group, 0);
        if (m != model) {
            if (m) m->refCount++;
            ModelResource* old = model;
            model = m;
            if (old) ReleaseRef(old);
        }
    }
    if (model == 0)
        return;

    VC1(resMgr, 0x58, model);

    const int kLargeSize = 0x200, kSheetSize = 0x100;
    void* dev = GetRenderDevice();
    uint32_t desc0[2], desc1[2];
    VC7(dev, 0x10, desc0, kLargeSize, kLargeSize, 0x15, 0, 0x46c01b8f, 0);
    void* largeTarget = VC3(dev, 0x18, desc0[0], desc0[1], 0);
    VC7(dev, 0x10, desc1, kSheetSize, kSheetSize, 0x15, 0, 0xa1043d28, 0);
    void* sheetTarget = VC3(dev, 0x18, desc1[0], desc1[1], 0);

    float ext[3];
    float nx = -model->boundsMin[0];
    ext[0] = model->boundsMax[0] > nx ? model->boundsMax[0] : nx;
    float ny = -model->boundsMin[1];
    ext[1] = model->boundsMax[1] > ny ? model->boundsMax[1] : ny;
    ext[2] = model->boundsMax[2] * 0.5f;
    float radius = Vector3_MaxComponent(ext);
    float orthoSize = radius * 2.0f;

    char camera[0x178];
    CameraCtor(camera);
    CameraSetMode(camera, 0);
    BeginRender();
    CameraSetTarget(camera, largeTarget);
    char defaults[0x2c];
    DefaultsCtor(defaults);

    void* gfx = GetGraphicsManager();
    VC0(gfx, 0x88);

    void* textures[2] = {0, 0};
    void* sprites[2] = {0, 0};
    void* textures2[2] = {0, 0};
    void* sprites2[2] = {0, 0};
    uint32_t keysA[6] = {0}, keysB[6] = {0};

    for (int i = 0; i < 2; ++i) {
        ClearState();
        SetRenderTarget(0, 0);
        float basis[9];
        uint16_t flags = 0;
        BuildBasis(basis, 1.0f, 0, 0, 0, 0, -1.0f, 0, 1.0f, 0);
        flags |= 6;
        ApplyCamera(&flags);
        SetOrtho(radius, radius);
        SetNear(0x38d1b717);
        SetFar(orthoSize + 1.0f);
        SetViewport(0, 0, kLargeSize, kLargeSize);
        if (NeedsFlush()) { Flush(7); FlushEnd(); }
        VC4(resMgr, 0x13c, 0, 0, 0, 0);
        void* comp = GetCompositor();
        VC4(comp, 0x58, &desc0, &desc1, 0, 0);

        textures[i] = NewSpriteTexture(kSheetSize, kSheetSize);
        SetSpriteParam(textures[i], 0, 0);
        sprites[i] = NewBakeSprites();
        keysA[i * 3] = key.instance;
        keysA[i * 3 + 1] = 0x2f4e681c;
        keysA[i * 3 + 2] = (key.group & 0xffff0000) | ((i & 0xff) << 8);
        FinishBake(textures[i], 0, 0, sprites[i]);
        if (NeedsFlush()) { Flush(7); FlushEnd(); }

        // Four orientation passes into the quadrants of the sheet.
        static const float rot[4][9] = {
            {1,0,0, 0,1,0, 0,0,1}, {-1,0,0, 0,-1,0, 0,0,1},
            {0,-1,0, 1,0,0, 0,0,1}, {0,1,0, -1,0,0, 0,0,1}};
        static const int vp[4][2] = {{0,0},{0x100,0},{0,0x100},{0x100,0x100}};
        for (int q = 0; q < 4; ++q) {
            BuildBasis(basis, rot[q][0], rot[q][1], rot[q][2], rot[q][3], rot[q][4], rot[q][5], rot[q][6], rot[q][7], rot[q][8]);
            flags |= 6;
            ApplyCamera(&flags);
            SetViewport(vp[q][0], vp[q][1], kSheetSize, kSheetSize);
            VC4(resMgr, 0x13c, 0, 0, 0, 0);
        }

        textures2[i] = NewSpriteTexture(kSheetSize, kSheetSize);
        SetSpriteParam(textures2[i], 0, 0);
        sprites2[i] = NewBakeSprites();
        keysB[i * 3] = key.instance;
        keysB[i * 3 + 1] = 0x2f4e681c;
        keysB[i * 3 + 2] = (key.group & 0xffff0000) | ((i & 0xff) << 8) | 1;
        FinishBake(textures2[i], 0, 0, sprites2[i]);
    }

    VC1(*(void**)model, 0x16c, 0);  // finish with the model
    ReleaseRef(model);
    EndRender();
    VC0(GetGraphicsManager(), 0x8c);

    for (int i = 0; i < 2; ++i) {
        void* sA = sprites[i] ? (char*)sprites[i] + 0xc : 0;
        RegisterSprite(sA, &keysA[i * 3], GetVariantKey(0x11ac1ac, 1));
        void* sB = sprites2[i] ? (char*)sprites2[i] + 0xc : 0;
        RegisterSprite(sB, &keysB[i * 3], GetVariantKey(0x11ac1ac, 1));
    }

    uint16_t variant[16];
    PackKeys(keysA);
    VC3(props, 0x14, 0xd124fce7, variant, 0);
    if (variant[8] & 4) FreeVariant(0);
    PackKeys(keysB);
    VC3(props, 0x14, 0xd124fce4, variant, 0);
    if (variant[8] & 4) FreeVariant(0);
    PackFloat(&radius);
    VC3(props, 0x14, 0x4057881, variant, 0);
    if (variant[8] & 4) FreeVariant(0);

    void* propSvc = GetPropertyService();
    VC3(propSvc, 0x20, props, 0, GetVariantKey(0x11ac1ac, 0));
    if (notifyTarget) {
        void* msg = GetMessageService();
        VC4(msg, 0x18, notifyTarget, 0, 0, 0);
    }
    for (int i = 1; i >= 0; --i) { if (sprites2[i]) VC0(sprites2[i], 4); }
    for (int i = 1; i >= 0; --i) { if (textures2[i]) VC0(textures2[i], 4); }
    for (int i = 1; i >= 0; --i) { if (sprites[i]) VC0(sprites[i], 4); }
    for (int i = 1; i >= 0; --i) { if (textures[i]) VC0(textures[i], 4); }
    EndCamera();
}
