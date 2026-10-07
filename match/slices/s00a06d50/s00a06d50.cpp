// Slice s00a06d50: debug drawing of animated objects (bounding boxes, bone/locator axes,
// direction arrows) with optional camera-plane / view-sphere culling.
// Module flags: /O2 /arch:SSE /fp:fast (scalar SSE, x87 only for sqrt and float args).
#include "types.h"
#include <math.h>

template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Matrix3 { Matrix3() {} float m[9]; };
struct Color4f { float r, g, b, a; };
struct ColorARGB { uint8_t b, g, r, a; };

class Property {
public:
    Property(const uint32_t& value);            // 0x005bf350
    ~Property() { if (mnFlags & 4) Destruct(0); }
    void Destruct(int);                         // 0x0093db80 EA::Variant::Destruct
    int32_t* GetValueInt32();                   // 0x0041e990
    bool* GetValueBool();                       // 0x0041e920
    int32_t* GetValueInt32Alt();                // 0x0060d280 (type 9 or 0x10)
    bool* GetValueBoolAlt();                    // 0x004e42a0 (type 1 or 0x10)
    uint32_t mData[4];
    uint16_t mnFlags;                           // +0x10
    uint16_t mnType;                            // +0x12
};

class PropertyList {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual Property* GetProperty(uint32_t propertyID);   // +0x28
};

class cViewer {
public:
    bool Begin();                                // 0x007c4fd0
    void End();                                  // 0x007c3c10
    void GetCameraLocationInfo(Vector3* pos, int, int, int);  // 0x007c3d30
};

struct ViewerRef { cViewer* p; };

struct ModelResource {
    uint32_t pad0[0x324 / 4];
    float mColorR;          // +0x324
    float mColorG;          // +0x328
    float mColorB;          // +0x32c
    uint32_t pad330[(0x358 - 0x330) / 4];
    Vector3 mBoundsMin;     // +0x358
    Vector3 mBoundsSize;    // +0x364
};

struct Model {
    ModelResource* mpResource;      // +0x00
    uint32_t pad04[(0x18 - 0x04) / 4];
    Vector3 mPosition;              // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    Quaternion mOrientation;        // +0x3c
    uint32_t pad4c[(0x70 - 0x4c) / 4];
    float mScale;                   // +0x70
    uint32_t pad74[(0xe8 - 0x74) / 4];
    Vector3 mArrowBase;             // +0xe8
    Vector3 mArrowDir;              // +0xf4
    uint32_t pad100[(0x2c0 - 0x100) / 4];
    int mHasBody;                   // +0x2c0
};

struct ObjState { uint32_t pad0; uint32_t mFlags; };

struct DrawObject {
    uint32_t pad0[0x50 / 4];
    int mShapeAlt;          // +0x50
    int mShape;             // +0x54
    uint32_t pad58[(0x64 - 0x58) / 4];
    bool mbVisible;         // +0x64
    uint8_t pad65[3];
    uint32_t pad68[(0x74 - 0x68) / 4];
    float mColorR;          // +0x74
    float mColorG;          // +0x78
    float mColorB;          // +0x7c
    float mAlpha;           // +0x80
    uint32_t pad84;
    uint32_t mFlags;        // +0x88
    uint32_t pad8c[(0x17c - 0x8c) / 4];
    Model* mpModel;         // +0x17c
    ObjState* mpState;      // +0x180
};

struct DrawSettings {
    uint32_t pad0[0x50 / 4];
    PropertyList* mpProps;  // +0x50
    uint32_t pad54[(0x80 - 0x54) / 4];
    void* mpDrawContext;    // +0x80
};

typedef float (*RadiusCallback)(void* data, DrawObject* obj, int, int, int, int);

Matrix3 QuaternionToMatrix(const Quaternion& q);                       // 0x009a46a0
Matrix3 MatrixFromVectors(const Vector3& up, const Vector3& dir, int, int);  // 0x00a05890
Vector3 QuaternionVectorTransform(const Quaternion& q, const Vector3& v);    // 0x0099c1a0
float SmoothBlend(float a, float b, float t);                          // 0x009b01e0
float InvSqrt(float x);                                                // 0x009e5c00
void GetModelTransform(Model* m, Vector3* pos, Quaternion* q, int);    // 0x009cd580
void GetObjectColor(DrawObject* obj, Color4f* out);                    // 0x00a04590
void DrawBox(void* ctx, const Matrix3& rot, const Vector3& pos, float scale,
             const Vector3& lo, const Vector3& hi, ColorARGB color, int flags);   // 0x00a03e80
void DrawModelShape(void* ctx, Model* m, ColorARGB c0, ColorARGB c1, int flags);  // 0x00a03f50

extern bool g_cullByPlane;          // 0x01551a91
extern bool g_cullBySphere;         // 0x01551a90
extern const ColorARGB kMagenta;    // 0x01448ad4
extern const ColorARGB kGreen;      // 0x01448ad0
extern const float kMinusBoxHalf;   // 0x01448bc8 (-0.15)

static inline bool StateBit(uint32_t flags, int n) { return (flags >> n) & 1; }

class cAnimDebugDraw {
public:
    void Draw(uint8_t pass, int colorMode, ViewerRef& viewer, int flags);

    uint32_t pad0[0x1c / 4];
    DrawSettings* mpSettings;               // +0x1c
    uint32_t pad20;
    DrawObject** mObjectsBegin;             // +0x24
    DrawObject** mObjectsEnd;               // +0x28
    uint32_t pad2c[(0x38 - 0x2c) / 4];
    bool mbCullingEnabled;                  // +0x38
    uint8_t pad39[3];
    RadiusCallback mpRadiusCallback;        // +0x3c
    void* mpRadiusCallbackData;             // +0x40
    uint32_t pad44[(0x3038 - 0x44) / 4];
    bool mbUseDrawModeProperty;             // +0x3038
};

// @ 0x00a06d50
void cAnimDebugDraw::Draw(uint8_t pass, int colorMode, ViewerRef& viewer, int flags)
{
    if (viewer.p && viewer.p->Begin()) {
        if (mpSettings && mpSettings->mpDrawContext && mpSettings->mpProps) {
            bool useObjectColor = *mpSettings->mpProps->GetProperty(0xe0e98b25)->GetValueBoolAlt();
            int drawMode = *(mbUseDrawModeProperty
                                 ? mpSettings->mpProps->GetProperty(0xc2dafabb)
                                 : &Property(0u))->GetValueInt32Alt();
            int axesMode = *mpSettings->mpProps->GetProperty(0x567ad0f2)->GetValueInt32();
            int boxMode = *mpSettings->mpProps->GetProperty(0xcaea3820)->GetValueInt32();
            bool checkState = *mpSettings->mpProps->GetProperty(0x3d781d85)->GetValueBool();
            mpSettings->mpProps->GetProperty(0x32710aa4);
            void* ctx = mpSettings->mpDrawContext;

            bool cull = false;
            if (mbCullingEnabled && pass == 5) {
                if (*mpSettings->mpProps->GetProperty(0xe536de74)->GetValueBool())
                    cull = true;
            }
            bool needSetup = cull;
            Vector3 camDir;
            camDir.x = 0.0f;
            camDir.y = 0.0f;
            camDir.z = 0.0f;
            float planeDist;
            float radius;

            for (int i = (int)(mObjectsEnd - mObjectsBegin) - 1; i >= 0; --i) {
                DrawObject* obj = mObjectsBegin[i];
                if (!obj)
                    continue;
                Model* model = obj->mpModel;
                if (!model || !obj->mbVisible)
                    continue;

                switch (pass) {
                case 1:
                    if (obj->mAlpha < 1.0f)
                        continue;
                    break;
                case 2:
                    if (obj->mAlpha >= 1.0f)
                        continue;
                    break;
                }

                bool flagged = StateBit(obj->mFlags, 1);
                if (model->mHasBody != 0) {
                    if (checkState) {
                        ObjState* st = obj->mpState;
                        flagged |= !(st && StateBit(st->mFlags, 14) && !StateBit(st->mFlags, 18));
                    }
                } else
                    flagged = true;

                if (drawMode == 1 || (drawMode != -1 && flagged)) {
                    float fade = 1.0f;
                    if (needSetup) {
                        needSetup = false;
                        RadiusCallback cb = mpRadiusCallback;
                        if (cb) {
                            radius = cb(mpRadiusCallbackData, obj, 0, 0, 0, 1);
                            Vector3 camPos;
                            viewer.p->GetCameraLocationInfo(&camPos, 0, 0, 0);
                            float dist = sqrtf(camPos.x * camPos.x + camPos.y * camPos.y + camPos.z * camPos.z);
                            float inv = 1.0f / (dist + 1e-8f);
                            camDir.x = -camPos.x * inv;
                            camDir.y = -camPos.y * inv;
                            camDir.z = -camPos.z * inv;
                            float d2 = dist * dist - radius * radius;
                            if (d2 > 0.0f) {
                                planeDist = d2 * inv - dist;
                                goto cullTest;
                            }
                        }
                        cull = false;
                        goto colors;
                    }
                cullTest:
                    if (cull) {
                        if (g_cullByPlane) {
                            ModelResource* res = model->mpResource;
                            float s = model->mScale;
                            float hs = s * 0.5f;
                            Vector3 center;
                            center.x = res->mBoundsMin.x * s + res->mBoundsSize.x * hs;
                            center.y = res->mBoundsMin.y * s + res->mBoundsSize.y * hs;
                            center.z = res->mBoundsMin.z * s + res->mBoundsSize.z * hs;
                            Vector3 r = QuaternionVectorTransform(model->mOrientation, center);
                            float proj = (model->mPosition.x + r.x) * camDir.x
                                       + (model->mPosition.y + r.y) * camDir.y
                                       + (model->mPosition.z + r.z) * camDir.z;
                            if (proj > planeDist)
                                continue;
                            float nearDist = planeDist - 3.0f;
                            if (proj > nearDist)
                                fade = 1.0f - SmoothBlend(nearDist, planeDist, proj);
                        }
                        if (g_cullBySphere) {
                            Vector3 p = model->mPosition;
                            float lenSq = p.x * p.x + p.y * p.y + p.z * p.z;
                            float radiusSq = radius * radius;
                            if (lenSq > radiusSq) {
                                const Vector3& d = model->mArrowDir;
                                Vector3 a;
                                a.x = p.y * d.z - p.z * d.y;
                                a.y = p.z * d.x - p.x * d.z;
                                a.z = p.x * d.y - p.y * d.x;
                                Vector3 b;
                                b.x = a.y * d.z - a.z * d.y;
                                b.y = a.z * d.x - a.x * d.z;
                                b.z = a.x * d.y - a.y * d.x;
                                float bLenSq = b.x * b.x + b.y * b.y + b.z * b.z;
                                if (bLenSq < 1e-5f) {
                                    float rr = radius + 0.1f;
                                    if (lenSq > rr * rr)
                                        continue;
                                } else {
                                    float inv = InvSqrt(bLenSq);
                                    float t = (b.x * inv) * p.x + (b.y * inv) * p.y + (b.z * inv) * p.z;
                                    float disc = t * t - (lenSq - radiusSq);
                                    if (!(disc >= 0.0f))
                                        continue;
                                    float hs = model->mScale * 0.5f;
                                    ModelResource* res = model->mpResource;
                                    float ex = res->mBoundsSize.x * hs;
                                    float ey = res->mBoundsSize.y * hs;
                                    float hit = -t - sqrtf(disc);
                                    if (hit * hit > ex * ex + ey * ey)
                                        continue;
                                }
                            }
                        }
                    }
                colors:
                    ColorARGB color;
                    if (useObjectColor) {
                        Color4f c;
                        GetObjectColor(obj, &c);
                        color.b = (uint8_t)(int)(c.b * 255.0f);
                        color.g = (uint8_t)(int)(c.g * 255.0f);
                        color.r = (uint8_t)(int)(c.r * 255.0f);
                        color.a = (uint8_t)(int)(c.a * fade * 255.0f);
                    } else if (colorMode == 0x10) {
                        color.b = (uint8_t)(int)(obj->mColorB * 255.0f);
                        color.g = (uint8_t)(int)(obj->mColorG * 255.0f);
                        color.r = (uint8_t)(int)(obj->mColorR * 255.0f);
                        color.a = (uint8_t)(int)(obj->mAlpha * fade * 255.0f);
                    } else {
                        ModelResource* res = model->mpResource;
                        color.b = Max((uint8_t)0x20, (uint8_t)(int)(res->mColorB * 255.0f));
                        color.g = Max((uint8_t)0x20, (uint8_t)(int)(res->mColorG * 255.0f));
                        color.r = Max((uint8_t)0x20, (uint8_t)(int)(res->mColorR * 255.0f));
                        color.a = (uint8_t)(int)(obj->mAlpha * fade * 255.0f);
                    }

                    int shape = obj->mShape;
                    if (shape == 4)
                        shape = obj->mShapeAlt;
                    switch (shape) {
                    case 0: {
                        ModelResource* res = model->mpResource;
                        float s = model->mScale;
                        Vector3 lo;
                        lo.x = s * res->mBoundsMin.x;
                        lo.y = res->mBoundsMin.y * s;
                        lo.z = res->mBoundsMin.z * s;
                        Vector3 hi;
                        hi.x = res->mBoundsSize.x * s + lo.x;
                        hi.y = res->mBoundsSize.y * s + lo.y;
                        hi.z = res->mBoundsSize.z * s + lo.z;
                        DrawBox(ctx, QuaternionToMatrix(model->mOrientation), model->mPosition, 1.0f,
                                lo, hi, color, flags);
                        break;
                    }
                    case 1:
                    case 2:
                        DrawModelShape(ctx, model, color, color, flags);
                        break;
                    }
                }

                if (boxMode == 1 || (boxMode != -1 && (obj->mFlags & 4))) {
                    Vector3 pos;
                    pos.x = 0.0f;
                    pos.y = 0.0f;
                    pos.z = 0.0f;
                    Quaternion q;
                    q.x = 0.0f;
                    q.y = 0.0f;
                    q.z = 0.0f;
                    q.w = 1.0f;
                    GetModelTransform(model, &pos, &q, 0);
                    Vector3 hi;
                    hi.x = 0.15f;
                    hi.y = 0.15f;
                    hi.z = 0.15f;
                    Vector3 lo;
                    lo.x = kMinusBoxHalf;
                    lo.y = kMinusBoxHalf;
                    lo.z = kMinusBoxHalf;
                    DrawBox(ctx, QuaternionToMatrix(q), pos, 1.0f, lo, hi, kMagenta, flags);

                    Vector3 diff;
                    diff.x = pos.x - model->mPosition.x;
                    diff.y = pos.y - model->mPosition.y;
                    diff.z = pos.z - model->mPosition.z;
                    Vector3 lineHi;
                    lineHi.x = 0.025f;
                    lineHi.y = 0.025f;
                    lineHi.z = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
                    Vector3 up;
                    up.x = 0.0f;
                    up.y = 0.0f;
                    up.z = 1.0f;
                    Vector3 zero;
                    zero.x = 0.0f;
                    zero.y = 0.0f;
                    zero.z = 0.0f;
                    DrawBox(ctx, MatrixFromVectors(up, diff, 0, 0), model->mPosition, 1.0f,
                            zero, lineHi, kMagenta, flags);
                }

                if (axesMode == 1) {
                    Vector3 hi;
                    hi.x = 0.15f;
                    hi.y = 0.15f;
                    hi.z = 0.05f;
                    Vector3 up;
                    up.x = 0.0f;
                    up.y = 0.0f;
                    up.z = 1.0f;
                    Matrix3 rot = MatrixFromVectors(up, model->mArrowDir, 0, 0);
                    Vector3 lo;
                    lo.x = kMinusBoxHalf;
                    lo.y = kMinusBoxHalf;
                    lo.z = -0.05f;
                    Vector3 pos;
                    pos.x = model->mArrowDir.x * 0.05f + model->mArrowBase.x;
                    pos.y = model->mArrowBase.y + model->mArrowDir.y * 0.05f;
                    pos.z = model->mArrowBase.z + model->mArrowDir.z * 0.05f;
                    DrawBox(ctx, rot, pos, 1.0f, lo, hi, kGreen, flags);
                }
            }
        }
        viewer.p->End();
    }
}
