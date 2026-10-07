// Slice s007b7ac0 - cThumbnailManager summarizer/job helpers.
//
// 0x007b7ac0 renders a thumbnail through the manager's cViewer: mode 0 renders one frame into the
// capture raster; mode 1 renders a "tiled" summary image, an n x n grid of views of the model, each
// tile taken from a camera orbiting the model (spherical coordinates, azimuth stepped by 360/n^2
// degrees per tile), rendering every tile twice (once with a fixed set of app bool properties, once
// with the user's values restored) and blitting it into its cell of the target raster.
// Module flags: /O2 /arch:SSE, EH (intrusive message pointer), no /GS cookie.
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

void* operator new(unsigned int, const char*, int, int, int, int);

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
};

struct Vector4 { float x, y, z, w; };

struct Matrix3 {
    Vector3 row0, row1, row2;
};

struct XForm {                      // transform block: flags, change counter, position, scale, basis
    unsigned short flags;           // +0
    unsigned short rev;             // +2
    Vector3 pos;                    // +4
    float scale;                    // +0x10
    Matrix3 m;                      // +0x14
};

// RenderWare RwMatrix (16-byte aligned): right, up, at, pos with padding words
struct __declspec(align(16)) RwMatrix {
    Vector3 right; uint32_t flags;
    Vector3 up;    uint32_t pad1;
    Vector3 at;    uint32_t pad2;
    Vector3 pos;   uint32_t pad3;
};

extern const Matrix3 g_identityBasis;       // 0x01635788
extern const Vector3 g_defaultPos;          // 0x01635648
extern float g_Pi;                          // 0x0153c158 (runtime float)
extern uint32_t g_shaderData223;            // 0x016f6e34
extern float g_OneOver180;                  // 0x0140ffcc (0.0055555557; cl /fp:fast folds a literal 1/180 with the 360)
inline float DegreesToRadians(float degrees) { return degrees * g_Pi * g_OneOver180; }

void SetShaderData(int index, uint32_t value, int flag);                 // 0x00777ae0
void SphericalFromCartesian(Vector3 pos, float* theta, float* phi, float* radius);   // 0x007b2600
Vector3 OrthogonalVector(const Vector3& v);                              // 0x006985b0

struct cViewer {
    void SetRaster(int* handle, bool setViewport);                       // 0x007c4be0
    void SetClearColor(const Vector4* color);                            // 0x007c3c20
    void SetClearFlags(int flags);                                       // 0x007c3c50
    void SetNear(float n);                                               // 0x007c4ba0
    void SetFar(float f);                                                // 0x007c4bc0
    void SetXForm(XForm* x);                                             // 0x007c40f0
    void ApplyXForm(XForm* x);                                           // 0x007c4d00
    void SetCameraToWorldFromBasis(RwMatrix* m);                         // 0x007c4d20
    void SetViewportRectArgs(unsigned short x, unsigned short y,
                             unsigned short w, unsigned short h);        // 0x007c5310
};

struct RenderInfo {
    cViewer* viewer;
    int a, b, c;
};

struct IRenderer {
    PV2 PV
    virtual void Render(int p1, int p2, RenderInfo* info, int p4);      // +0x0c
};

struct ThumbSettings {
    uint32_t pad00[4];
    IRenderer* mpRenderer;          // +0x10
    int mMode;                      // +0x14
};

struct IRasterSource {              // FUN_0067dd40
    PV8 PV8 PV8 PV8 PV8 PV8 PV
    virtual void GetCaptureRaster(int* handle);                          // +0xc4
    PV4 PV2 PV
    virtual void GetTargetRaster(int* handle);                           // +0xe4
};
struct ICapture {                   // FUN_0067ddb0
    PV4 PV2
    virtual void GetSize(int* wh);                                       // +0x18
    PV8 PV4 PV2
    virtual void CaptureTile(cViewer* v, int* target, int* source, int p4, float alpha); // +0x54
    virtual void Capture(int* source, int* target, int p4, float alpha); // +0x58
};
struct IBlitter {                   // FUN_0067dda0
    PV8 PV
    virtual void MeasureSomething(int w, int h, int* o0, int* o1, int* o2, int* o3); // +0x24
};
IRasterSource* GetRasterSource();   // 0x0067dd40
ICapture* GetCapture();             // 0x0067ddb0
IBlitter* GetBlitter();             // 0x0067dda0

struct BehaviorMessage {
    virtual int mv0();
    virtual int AddRef();           // +4
    virtual int Release();          // +8
    volatile long mRefCount;        // +4
    BehaviorMessage() { _InterlockedExchange(&mRefCount, 0); }
};

struct ThumbMessage : BehaviorMessage {     // 0x18 bytes
    cViewer* mpViewer;              // +8
    int pad0c;
    int m10;                        // +0x10
    int pad14;
    ThumbMessage() { m10 = 0; }
    virtual int mv0();
    virtual int AddRef();
    virtual int Release();
};

template <class T> struct SmartP {
    T* p;
    SmartP(T* x) : p(x) { if (p) p->AddRef(); }
    ~SmartP() { if (p) p->Release(); }
    T* operator->() const { return p; }
};

struct IMessageServer {
    PV4 PV
    virtual void PostMessage(uint32_t id, ThumbMessage* msg, int zero);  // +0x14
};
IMessageServer* MessageServer();    // 0x0067dcc0

struct Property {
    uint32_t data[4];
    uint8_t flags;                  // +0x10
    uint8_t pad11;
    unsigned short type;            // +0x12
    float* AsVector();              // 0x006bb610 (default vector)
};

struct cDirectPropertyList {
    PV8 PV2
    virtual Property* GetProperty(uint32_t id);                          // +0x28
    int GetIntProperty(uint32_t id);                                     // 0x006a2660
    bool GetBoolProperty(uint32_t id);                                   // 0x006a25a0
    void SetBoolProperty(uint32_t id, bool value);                       // 0x006a17e0
};
extern cDirectPropertyList* sAppProperties;  // 0x015fd918

static __forceinline const float* GetVector3Value(Property* p)
{
    unsigned short type = p->type;
    if (type == 0x34 || type == 0x10) {
        if (p->flags & 0x30)
            return *(float**)p;
        return type ? (float*)p : 0;
    }
    return p->AsVector();
}

struct cThumbnailManager {
    uint32_t pad00[4];
    cViewer* mpViewer;              // +0x10
    ThumbSettings* mpSettings;      // +0x14

    void FinishSingle();                                                 // 0x007b35a0
    void FinishTiled(int tileSize);                                      // 0x007b3630
    void Render(int p1, int p2, const RenderInfo* ri, int p4);
};

// @ 0x007b7ac0
void cThumbnailManager::Render(int p1, int p2, const RenderInfo* ri, int p4)
{
    uint32_t savedShaderData = g_shaderData223;
    SetShaderData(0x223, 0, 1);
    ThumbMessage* rawMsg = new ("Graphics", 0, 0, 0, 0) ThumbMessage;
    SmartP<ThumbMessage> msg(rawMsg);

    if (mpSettings->mMode == 0) {
        int target[2];
        target[0] = -1;
        target[1] = -1;
        GetRasterSource()->GetTargetRaster(target);
        int source[2];
        source[0] = -1;
        source[1] = -1;
        GetCapture()->GetSize(source);
        mpViewer->SetRaster(target, true);
        mpViewer->SetClearFlags(7);
        rawMsg->mpViewer = mpViewer;
        MessageServer()->PostMessage(0x12d74a2, rawMsg, 0);
        RenderInfo info;
        info.viewer = mpViewer;
        info.a = 0;
        info.b = 0;
        info.c = 0;
        mpSettings->mpRenderer->Render(p1, p2, &info, p4);
        GetCapture()->Capture(target, source, p4, 0.0f);
        FinishSingle();
    } else if (mpSettings->mMode == 1) {
        int tilesPerRow = sAppProperties->GetIntProperty(0x5893ee8);
        int tileSize = sAppProperties->GetIntProperty(0x5893ed4);
        unsigned int tileCount = tilesPerRow * tilesPerRow;
        const float* bg = GetVector3Value(sAppProperties->GetProperty(0x5d2c54b));
        Vector4 color;
        color.x = bg[0];
        color.y = bg[1];
        color.z = bg[2];
        color.w = 1.0f;
        int tileRaster[2];
        tileRaster[0] = -1;
        tileRaster[1] = -1;
        GetRasterSource()->GetTargetRaster(tileRaster);
        int captureRaster[2];
        captureRaster[0] = -1;
        captureRaster[1] = -1;
        GetRasterSource()->GetCaptureRaster(captureRaster);
        float step = DegreesToRadians(360.0f / (float)tileCount);

        for (unsigned int i = 0; i < tileCount; i++) {
            mpViewer->SetRaster(tileRaster, true);
            mpViewer->SetClearColor(&color);
            mpViewer->SetNear(10.0f);
            mpViewer->SetFar(10000.0f);
            mpViewer->SetClearFlags(7);

            bool b4f4edc94 = sAppProperties->GetBoolProperty(0x4f4edc94);
            bool bddca437d = sAppProperties->GetBoolProperty(0xddca437d);
            bool bab73e4f9 = sAppProperties->GetBoolProperty(0xab73e4f9);
            bool b5016cc22 = sAppProperties->GetBoolProperty(0x5016cc22);
            bool b5dee2437 = sAppProperties->GetBoolProperty(0x5dee2437);
            bool b05a3dc9e = sAppProperties->GetBoolProperty(0x5a3dc9e);
            sAppProperties->SetBoolProperty(0x4f4edc94, false);

            rawMsg->mpViewer = mpViewer;
            MessageServer()->PostMessage(0x12d74a2, rawMsg, 0);

            RenderInfo info;
            info.viewer = mpViewer;
            info.a = ri->a;
            info.b = ri->b;
            info.c = ri->c;
            sAppProperties->SetBoolProperty(0xddca437d, true);
            sAppProperties->SetBoolProperty(0xab73e4f9, false);
            sAppProperties->SetBoolProperty(0x5016cc22, false);
            sAppProperties->SetBoolProperty(0x5dee2437, false);
            sAppProperties->SetBoolProperty(0x5a3dc9e, false);
            mpSettings->mpRenderer->Render(p1, p2, &info, p4);
            sAppProperties->SetBoolProperty(0xddca437d, bddca437d);
            sAppProperties->SetBoolProperty(0xab73e4f9, bab73e4f9);
            sAppProperties->SetBoolProperty(0x5016cc22, b5016cc22);
            sAppProperties->SetBoolProperty(0x5dee2437, b5dee2437);
            sAppProperties->SetBoolProperty(0x5a3dc9e, b05a3dc9e);
            mpSettings->mpRenderer->Render(p1, p2, &info, p4);
            sAppProperties->SetBoolProperty(0x4f4edc94, b4f4edc94);

            mpViewer->SetRaster(captureRaster, true);
            int x, y, w, h;
            GetBlitter()->MeasureSomething(captureRaster[0], captureRaster[1], &x, &y, &w, &h);
            x = (i % tilesPerRow) * tileSize;
            y = (i / tilesPerRow) * tileSize;
            w = tileSize;
            h = tileSize;
            mpViewer->SetViewportRectArgs((unsigned short)x, (unsigned short)y,
                                          (unsigned short)w, (unsigned short)h);
            mpViewer->SetClearColor(&color);
            mpViewer->SetClearFlags(7);
            GetCapture()->CaptureTile(mpViewer, tileRaster, captureRaster, p4, color.w);

            XForm xf;
            xf.flags = 0;
            xf.rev = 0;
            xf.pos = g_defaultPos;
            xf.scale = 1.0f;
            xf.m = g_identityBasis;
            mpViewer->SetXForm(&xf);

            float theta, phi, radius;
            SphericalFromCartesian(xf.pos, &theta, &phi, &radius);
            xf.flags |= 4;
            phi = phi + step;
            xf.rev++;
            float sinTheta = sinf(theta);
            Vector3 pos(sinTheta * cosf(phi) * radius, sinTheta * sinf(phi) * radius, cosf(theta) * radius);
            xf.pos = pos;
            mpViewer->ApplyXForm(&xf);

            float len = sqrtf(pos.z * pos.z + pos.y * pos.y + pos.x * pos.x + 1e-8f);
            float inv = 1.0f / len;
            Vector3 dir(inv * pos.x, pos.y * inv, pos.z * inv);
            Vector3 o = OrthogonalVector(dir);
            float olen = sqrtf(o.x * o.x + o.y * o.y + o.z * o.z + 1e-8f);
            float oinv = 1.0f / olen;
            Vector3 right(o.x * oinv, o.y * oinv, o.z * oinv);
            Vector3 up = right.Cross(dir);
            float ulen = sqrtf(up.x * up.x + up.y * up.y + up.z * up.z + 1e-8f);
            float uinv = 1.0f / ulen;

            RwMatrix m;
            m.right = right;
            m.up = Vector3(uinv * up.x, uinv * up.y, uinv * up.z);
            m.at = Vector3(-dir.x, -dir.y, -dir.z);
            m.pos = pos;
            mpViewer->SetCameraToWorldFromBasis(&m);
        }
        FinishTiled(tileSize);
    }
    SetShaderData(0x223, savedShaderData, 1);
}

// @ 0x007b8550  (partial)
void partial_007b8550(void) {}
// @ 0x007b8680  (partial)
void partial_007b8680(void) {}
// @ 0x007b8700  (partial)
void partial_007b8700(void) {}
// @ 0x007b8780  (partial)
void partial_007b8780(void) {}
