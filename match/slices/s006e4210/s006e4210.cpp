// Slice s006e4210: SP::CaptureCubeMap (0x006e4210, 3988 bytes, __cdecl, 8 args, 16-byte-aligned
// frame, /O2 /arch:SSE2 /EHsc).
//
// Renders the scene into the six faces of a cube map.  For each face i (+X,-X,+Z,-Z,+Y,-Y) it
// builds the face direction F, derives an orthonormal basis (W = right, V = up; special-cased for
// the world-axis directions that are parallel to the reference axis), optionally flips V, writes a
// 4x4 view matrix M (rows -W, V, -F, position), composes the passed position/quaternion rotation
// through cViewer::UpdateTransforms + Matrix44::Multiply, sets that matrix/viewport/clear colour on
// the face's render target pOut[i], then builds a capture command (two refcounted "Graphics"
// messages, an effects collection filled from the render queue's entries, and the capture
// object) and queues it on the render queue.
//
// Names below for the engine singletons/interfaces are guesses from usage; vtable slot indices come
// straight from the machine code (slot = offset / 4).  Float expression order follows the asm.
#include "types.h"
#include <math.h>
#include <string.h>
#include <intrin.h>

void* operator new(unsigned size, const char* tag, int a, int b, int c, int d);

// ---- engine interfaces ---------------------------------------------------------------------
struct TargetHandle { unsigned a, b; };               // render-target id pair (two dwords)
struct TargetInfo { char pad[0xc]; unsigned short width, height; };   // +0xc / +0xe

struct IGraphicsDevice {                              // FUN_0067dda0
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual TargetHandle* CreateTarget(TargetHandle* out, unsigned w, unsigned h, int format,
                                       int a, int b, int c);        // +0x10 (slot 4)
    virtual void s5();
    virtual TargetInfo* GetTargetInfo(unsigned a, unsigned b);      // +0x18 (slot 6)
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void SetTargetName(unsigned a, unsigned b, const char* name);   // +0x48 (slot 18)
};

struct RenderQueueEntry { unsigned a; unsigned kind; unsigned c; };

// Refcounted objects: either AddRef/Release at vt+0/+4 (collection, capture) or the
// UI::BehaviorMessage layout (vt+4/+8).
struct MsgBase {                                      // vtbl_UI::BehaviorMessage (0x013eb90c)
    virtual void s0();
    virtual int AddRef();                             // +4
    virtual int Release();                            // +8
    long mRefCount;
    MsgBase() { _InterlockedExchange(&mRefCount, 0); }
};
struct CaptureMsgA : MsgBase {                        // 0x18 bytes
    unsigned mTarget;                                 // +8
    unsigned pad_c;
    unsigned mZero;                                   // +0x10
    unsigned pad_14;
    CaptureMsgA() { mZero = 0; }
};
struct CaptureCommand;                                // 0x24 bytes (0x0076b660 / 0x0076b720)
struct CaptureMsgB : MsgBase {                        // 0x30 bytes
    unsigned mFace;                                   // +8
    unsigned pad_c;
    unsigned mHandleB;                                // +0x10
    unsigned pad_14;
    unsigned mHandleA;                                // +0x18
    unsigned pad_1c;
    CaptureCommand* mCommand;                         // +0x20
    unsigned pad_24;
    unsigned mZero;                                   // +0x28
    unsigned pad_2c;
    CaptureMsgB() { mZero = 0; }
};

struct EffectsCollection {                            // 0x20 bytes (ctor 0x00760c00)
    EffectsCollection();
    virtual int AddRef();                             // +0
    virtual int Release();                            // +4
    void AddEffect(unsigned a, unsigned kind, unsigned c);   // 0x00760fd0
};
struct CaptureCommand {                               // ctor 0x0076b660 (D660)
    CaptureCommand();
    virtual int AddRef();                             // +0
    virtual int Release();                            // +4
    void Init(unsigned face, unsigned target, TargetHandle* handle, EffectsCollection* fx,
              int arg8);                              // 0x0076b720 (Ctor76b720)
};

struct QueueItem {                                    // command record (0x2c bytes)
    unsigned mKind;                                   // +0 = 1
    unsigned mZero4;                                  // +4
    unsigned char mFlag;                              // +8
    unsigned mTypeId;                                 // +0xc
    CaptureMsgA* mMsgA;                               // +0x10
    unsigned mId2;                                    // +0x14
    CaptureMsgB* mMsgB;                               // +0x18
    unsigned mTarget;                                 // +0x1c
    unsigned mZero20, mZero24, mZero28;
};

struct IRenderQueue {                                 // FUN_0067dd50
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
    virtual int GetEntryCount();                      // +0x68 (slot 26)
    virtual void s27();
    virtual RenderQueueEntry* GetEntry(int i);        // +0x70 (slot 28)
    virtual void s29();
    virtual void Submit(CaptureCommand* cmd, int zero, QueueItem* item);   // +0x78 (slot 30)
};

struct IEffectsManager {                              // SP::EffectsManager()
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void SetTime(float a, float b);           // +0x40 (slot 16)
};

struct IRenderTarget {                                // pOut[i]
    void SetViewMatrix(const float* m);               // 0x007c4d20
    void SetViewportRect(int x, int y, int w, int h); // 0x007c5310 (cViewer_SetViewportRect)
    void Clear(const float* rgba);                    // 0x007c3c20
};

struct Matrix44 { float m[16]; };
struct cViewer {                                      // stack object; only the transform is used
    float m[16];
    float* UpdateTransforms(const float* p);          // 0x006e3000 (returns this)
};
float* Matrix44Multiply(float* out, const float* lhs, const float* rhs);   // 0x006e3f70 (cdecl, returns out)

IRenderQueue*    GetRenderQueue();                    // 0x0067dd50
IGraphicsDevice* GetGraphicsDevice();                 // 0x0067dda0
IEffectsManager* EffectsManager();                    // 0x0067ddd0 (SP::EffectsManager)

template <class T> struct Ref {                       // intrusive smart pointer (AddRef on construct)
    T* p;
    explicit Ref(T* q) : p(q) { if (p) p->AddRef(); }
    ~Ref() { if (p) p->Release(); }
    T* operator->() const { return p; }
};

namespace SP {

void CaptureCubeMap(int* pOut, float* pPosition, float* pRotation,
                    unsigned short size, int arg5, int arg6, bool flip, int arg8);

}  // namespace SP

// @ 0x006e4210
void SP::CaptureCubeMap(int* pOut, float* pPosition, float* pRotation,
                        unsigned short size, int arg5, int arg6, bool flip, int arg8)
{
    IRenderQueue* pQueue = GetRenderQueue();
    IGraphicsDevice* pDevice = GetGraphicsDevice();

    unsigned hB = (unsigned)-1;
    unsigned hA = (unsigned)-1;
    TargetHandle tmpHandle;
    TargetHandle* ph = pDevice->CreateTarget(&tmpHandle, size, size, 0x16, 1, -1, 0);
    hA = ph->a;
    hB = ph->b;
    pDevice->SetTargetName(ph->a, ph->b, "CubemapCapture");
    TargetInfo* pInfo = pDevice->GetTargetInfo(hA, hB);
    TargetHandle handle;
    handle.a = hA;
    handle.b = hB;

    for (int face = 0; face < 6; face++) {
        float a, b, c;                                // face direction
        switch (face) {
        case 0: a = 1.0f;  b = 0.0f;  c = 0.0f;  break;
        case 1: a = -1.0f; b = 0.0f;  c = 0.0f;  break;
        case 2: a = 0.0f;  b = 0.0f;  c = 1.0f;  break;
        case 3: a = 0.0f;  b = 0.0f;  c = -1.0f; break;
        case 4: a = 0.0f;  b = 1.0f;  c = 0.0f;  break;
        case 5: a = 0.0f;  b = -1.0f; c = 0.0f;  break;
        }

        // normalized face direction F
        float s = 1.0f / sqrtf(((c * c + b * b) + a * a) + 1e-08f);
        float Fx = s * a;
        float Fy = s * b;
        float Fz = s * c;

        // U = normalize(dir x ref)
        float ux, uy, uz;
        if (a == 0.0f && ((b == 0.0f && c == 1.0f) || (b == 0.0f && c == -1.0f))) {
            float t0 = b * 0.0f - c * 0.0f;
            float t1 = c - a * 0.0f;
            float t2 = a * 0.0f - b;
            float k = 1.0f / sqrtf(((t0 * t0 + t1 * t1) + t2 * t2) + 1e-08f);
            ux = k * t0; uy = k * t1; uz = k * t2;
        } else {
            float t0 = b * 0.0f - c;
            float t1 = c * 0.0f - a * 0.0f;
            float t2 = a - b * 0.0f;
            float k = 1.0f / sqrtf(((t0 * t0 + t1 * t1) + t2 * t2) + 1e-08f);
            ux = k * t0; uy = k * t1; uz = k * t2;
        }
        if (sqrtf((uy * uy + uz * uz) + ux * ux) < 1e-06f) {
            if (a == 0.0f && b == 1.0f && c == 0.0f) {
                ux = 0.0f; uy = 0.0f; uz = -1.0f;
            } else {
                ux = 0.0f; uy = 0.0f; uz = 1.0f;
            }
        }

        // W = normalize(U x F) (negated for the Y-axis-parallel faces)
        float wx, wy, wz;
        {
            float t0 = Fz * uy - Fy * uz;
            float t1 = Fx * uz - ux * Fz;
            float t2 = ux * Fy - Fx * uy;
            float k = 1.0f / sqrtf(((t0 * t0 + t1 * t1) + t2 * t2) + 1e-08f);
            wx = k * t0; wy = k * t1; wz = k * t2;
            if ((a == 0.0f && b == -1.0f && c == 0.0f) || (a == 1.0f && b == 0.0f && c == 0.0f)) {
                wx = -wx; wy = -wy; wz = -wz;
            }
        }

        // V = normalize(W x F), up = -V (or +V when flipping)
        float upx, upy, upz;
        {
            float t0 = Fz * wy - Fy * wz;
            float t1 = Fx * wz - wx * Fz;
            float t2 = wx * Fy - Fx * wy;
            float k = 1.0f / sqrtf(((t0 * t0 + t1 * t1) + t2 * t2) + 1e-08f);
            upx = -(k * t0); upy = -(k * t1); upz = -(k * t2);
            if (flip) {
                upx = -upx; upy = -upy; upz = -upz;
            }
        }

        float M[16];                                  // view matrix; the w column is left unset
        M[0] = -wx;  M[1] = -wy;  M[2] = -wz;
        M[4] = upx;  M[5] = upy;  M[6] = upz;
        M[8] = -Fx;  M[9] = -Fy;  M[10] = -Fz;
        M[12] = pPosition[0];
        M[13] = pPosition[1];
        M[14] = pPosition[2];

        // rotation matrix from the quaternion (x, y, z, w)
        float qx = pRotation[0], qy = pRotation[1], qz = pRotation[2], qw = pRotation[3];
        float yy = qy * qy, zz = qz * qz, xy = qy * qx, xz = qz * qx, zy = qz * qy;
        float wx_ = qw * qx, wy_ = qw * qy, wz_ = qw * qz, xx = qx * qx;
        float R[16];
        R[0] = 1.0f - (yy + zz) * 2.0f;
        R[1] = (xy + wz_) * 2.0f;
        R[2] = (xz - wy_) * 2.0f;
        R[3] = (xy - wz_) * 2.0f;
        R[4] = 1.0f - (xx + zz) * 2.0f;
        R[5] = (zy + wx_) * 2.0f;
        R[6] = (xz + wy_) * 2.0f;
        R[7] = (zy - wx_) * 2.0f;
        R[8] = 1.0f - (xx + yy) * 2.0f;
        R[9] = 0.0f; R[10] = 0.0f; R[11] = 0.0f;

        cViewer viewer;
        float* pX = viewer.UpdateTransforms(R);
        float* pM = Matrix44Multiply(R, M, pX);
        memcpy(M, pM, 64);

        IRenderTarget* pTarget = (IRenderTarget*)pOut[face];
        pTarget->SetViewMatrix(M);
        pTarget->SetViewportRect(0, 0, pInfo->width, pInfo->height);
        float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        pTarget->Clear(clear);

        Ref<CaptureMsgA> msgA(new("Graphics", 0, 0, 0, 0) CaptureMsgA);
        msgA->mTarget = (unsigned)pOut[face];

        Ref<CaptureMsgB> msgB(new("Graphics", 0, 0, 0, 0) CaptureMsgB);
        msgB->mFace = face;
        msgB->mHandleB = hB;
        msgB->mHandleA = hA;

        Ref<EffectsCollection> fx(new("Graphics", 0, 0, 0, 0) EffectsCollection);
        EffectsManager()->SetTime(0.0f, 0.0f);

        int n = pQueue->GetEntryCount();
        for (int k = 0; k < n; k++) {
            RenderQueueEntry* e = pQueue->GetEntry(k);
            unsigned kind = e->kind;
            if (kind != 0x11 && kind != 0x22 && kind != 0x1a &&
                kind != 0x1f && kind != 0x23 && kind != 0x1e) {
                fx.p->AddEffect(e->a, kind, e->c);
            }
        }

        Ref<CaptureCommand> cmd(new("Graphics", 0, 0, 0, 0) CaptureCommand);
        cmd.p->Init(face, pOut[face], &handle, fx.p, arg8);
        msgB->mCommand = cmd.p;

        QueueItem item;
        item.mZero4 = 0;
        item.mZero20 = 0; item.mZero24 = 0; item.mZero28 = 0;
        item.mFlag = 0;
        item.mTarget = (unsigned)pOut[face];
        item.mKind = 1;
        item.mTypeId = 0x12d74a2;
        item.mMsgA = msgA.p;
        item.mId2 = 0x1c91276;
        item.mMsgB = msgB.p;
        pQueue->Submit(cmd.p, 0, &item);
    }
}
