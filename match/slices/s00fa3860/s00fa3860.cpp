// Slice s00fa3860 -- SP::cTerrainSphere::ApplyModelFootprint (0x00fa3c10, 1740 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module as s00fa2a20.
//
// Applies the "footprint" terrain decals described by a model's property list to the planet:
//   - 0x3b28c1d / 0x3b28c1e / 0x442151e: a footprint decal (size vector, offset vector, image key)
//     rendered through cTerrainSphere::FUN_00f9d5c0,
//   - 0x3b28c1b / 0x3b28c1c: a second decal resource drawn through FUN_00fa01e0,
//   - 0x3abc381..0x3abc386: an optional colored decal (created with FUN_00fa2920) whose per-face
//     bounding boxes are returned in the caller's array, then tinted by the properties.
#include "types.h"
#include <intrin.h>

typedef unsigned char uint8;

struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };
struct ResKey { uint32_t instance, type, group; };

struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    float mOffset[3];
    float mfScale;
    float mRotation[9];

    Transform(const Transform& src);   // 0x0040ce80
    void RotateY(float angle);         // 0x004099b0
    __forceinline void ScaleBy(float s)
    {
        mfScale = mfScale * s;
        mnFlags |= 1;
        mnTransformCount += 1;
    }
};

struct Property {
    char pad0[0x12];
    uint16_t mnType;                   // +0x12
    const bool* GetBool();             // 0x0041e920
    const float* GetFloat();           // 0x0041ea70
};

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // +0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // +0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
};

bool GetPropertyAsKey(cPropertyList* list, uint32_t id, ResKey* value);           // 0x006a1250
bool GetPropertyAsVector2(cPropertyList* list, uint32_t id, Vector2* value);      // 0x006a10c0
bool GetPropertyAsVector3(cPropertyList* list, uint32_t id, Vector3* value);      // 0x006a1110
bool GetPropertyAsColorRGB(cPropertyList* list, uint32_t id, float* rgb);         // 0x006a11b0
bool GetFloatProperty(cPropertyList* list, uint32_t id, float* value);            // 0x0040cf10

extern const float kPi;                // 0x015b1190
extern const float kLerpBase[3];       // 0x015b11ac..0x015b11b4

// Atomic intrusive refcount at +8 (decrement, re-read, restore on underflow), as inlined by the original.
static __forceinline void ReleaseRef(void* o)
{
    volatile long* c = (volatile long*)((char*)o + 8);
    _InterlockedExchangeAdd(c, -1);
    long n = _InterlockedExchangeAdd(c, 0);
    if (n < 1) _InterlockedExchangeAdd(c, 1);
    else _InterlockedExchangeAdd(c, 0);
}
static __forceinline void AddRef(void* o)
{
    _InterlockedExchangeAdd((volatile long*)((char*)o + 8), 1);
}

struct cImage;
struct cImgRes {
    cImage* mpImage;
    void GetImageResource(void* resource);   // 0x00576650
};
struct ImageRef {
    cImgRes r;
    ImageRef() { r.mpImage = 0; }
    ~ImageRef() { if (r.mpImage) ReleaseRef(r.mpImage); }
};

struct IApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void* GetCurrentMode();   // +0x38
};
IApp* App();                          // 0x0067dd10

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18();
    virtual void* GetResource(ResKey key, int type);   // +0x1c
};
IResourceManager* GetResourceManager();   // 0x0067dd60

extern char gSpecialMode;                 // 0x01654c10

struct cTerrainSphereDecal {
    char pad0[0x40];
    float r, g, b, a;                     // +0x40 color / alpha
    bool GetBBoxForFace(int face, float* box);   // 0x00fad140
};

struct LightInfo {
    char pad[0x59c];
    float color[3];                       // +0x59c
};

struct cTerrainSphere {
    char pad0[0x20c];
    LightInfo* mpLight;                   // +0x20c
    void ApplyModelFootprint(const Transform* modelXform, cPropertyList* props, void* a3, float* faceBoxes, bool bDecal);
    void DrawFootprint(Transform* xform, float z, cImage* img, const Vector2* off, bool flag, float* faceBoxes, void* a3);   // 0x00f9d5c0
    void DrawResource(Transform* xform, float z, void* res, void* a3);                                                // 0x00fa01e0
    cTerrainSphereDecal* CreateDecal(void* res, Transform* xform, float z, int layer);                                // 0x00fa2920
};

// @ 0x00fa3c10
void cTerrainSphere::ApplyModelFootprint(const Transform* modelXform, cPropertyList* props, void* a3, float* faceBoxes, bool bDecal)
{
    ResKey key = { 0, 0, 0 };
    bool bFootprintDone = false;
    bool bSpecial = (App()->GetCurrentMode() == (void*)&gSpecialMode);

    Vector3 fp = { 10.0f, 0.0f, 0.1f };
    if (!bSpecial && GetPropertyAsVector3(props, 0x3b28c1d, &fp)) {
        float width = fp.x;
        float angle = fp.y * kPi * 2.0f;
        float z = fp.z;
        Transform xform(*modelXform);
        bool flag = bSpecial;
        if (props) {
            Property* p;
            if (props->GetProperty(0x589e78c, p) && p->mnType == 1)
                flag = *p->GetBool();
        }
        Vector2 off = { 0.0f, 0.0f };
        GetPropertyAsVector2(props, 0x3b28c1e, &off);
        xform.RotateY(angle);
        xform.ScaleBy(width);
        cImgRes img;
        img.mpImage = 0;
        cImage* image = 0;
        if (GetPropertyAsKey(props, 0x442151e, &key)) {
            void* res = GetResourceManager()->GetResource(key, 2);
            img.GetImageResource(res);
            image = img.mpImage;
        }
        DrawFootprint(&xform, z, image, &off, flag, faceBoxes, a3);
        bFootprintDone = true;
        if (image) ReleaseRef(image);
    }

    Vector3 fp2 = { 10.0f, 0.0f, 0.1f };
    if (!bSpecial && GetPropertyAsKey(props, 0x3b28c1b, &key)) {
        GetPropertyAsVector3(props, 0x3b28c1c, &fp2);
        void* res = GetResourceManager()->GetResource(key, 2);
        if (res) {
            AddRef(res);
            float angle = fp2.y * kPi * 2.0f;
            float z = fp2.z;
            Transform xform(*modelXform);
            xform.RotateY(angle);
            xform.ScaleBy(fp2.x);
            DrawResource(&xform, z, res, a3);
            ReleaseRef(res);
        }
    }

    if (bDecal && GetPropertyAsKey(props, 0x3abc381, &key)) {
        Vector3 dv = { 10.0f, 0.0f, 1.0f };
        GetPropertyAsVector3(props, 0x3abc382, &dv);
        void* res = GetResourceManager()->GetResource(key, 2);
        if (res) {
            Transform xform(*modelXform);
            xform.ScaleBy(dv.x);   // scale first, as in the original
            float angle = dv.y * kPi * 2.0f;
            xform.RotateY(angle);
            cTerrainSphereDecal* decal = CreateDecal(res, &xform, 0.0f, 0);

            if (faceBoxes && !bFootprintDone) {
                for (int face = 0; face < 6; face++) {
                    float box[4];
                    if (decal->GetBBoxForFace(face, box)) {
                        faceBoxes[face * 4 + 0] = box[0];
                        faceBoxes[face * 4 + 1] = box[1];
                        faceBoxes[face * 4 + 2] = box[2];
                        faceBoxes[face * 4 + 3] = box[3];
                    }
                    else {
                        faceBoxes[face * 4 + 0] = 0.0f;
                        faceBoxes[face * 4 + 1] = 0.0f;
                        faceBoxes[face * 4 + 2] = 0.0f;
                        faceBoxes[face * 4 + 3] = 0.0f;
                    }
                }
            }

            float col[3] = { 1.0f, 1.0f, 1.0f };
            if (GetPropertyAsColorRGB(props, 0x3abc383, col)) {
                decal->r = col[0];
                decal->g = col[1];
                decal->b = col[2];
            }
            if (props) {
                Property* p;
                if (props->GetProperty(0x3abc384, p) && p->mnType == 0xd)
                    decal->a = *p->GetFloat();
                if (props->GetProperty(0x3abc385, p) && p->mnType == 1 && *p->GetBool() && mpLight) {
                    float t = 1.0f;
                    GetFloatProperty(props, 0x3abc386, &t);
                    LightInfo* li = mpLight;
                    decal->r = ((li->color[0] - kLerpBase[0]) * t + kLerpBase[0]) * decal->r;
                    decal->g = decal->g * ((li->color[1] - kLerpBase[1]) * t + kLerpBase[1]);
                    decal->b = decal->b * ((li->color[2] - kLerpBase[2]) * t + kLerpBase[2]);
                }
            }
        }
    }
}
