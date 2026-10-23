// Slice s00ccece0 (tribe-mode input strategy + selection cursor).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (tribe-mode module; no /EHsc).
//
// 0x00ccef10  SP::cTribeInputStrategy::RestorePlanner  (thiscall, ret 4)
// 0x00ccece0  ShowSelection                            (cdecl, the cursor/selection message builder)
#include "types.h"

typedef unsigned int u32;

// ---- allocator / message plumbing (shared with the tribe-mode module) --------------------
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);   // 0xf473a0
extern char g_allocTag[];                 // 0x013ebc58  "App"

extern "C" float __cdecl sqrtf(float);
extern "C" double __cdecl sqrt(double);

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

#define VSLOT(n) virtual void vslot##n()

// The 0x40-byte message object: RefBase primary base (vptr +0, refcount +4), the data
// block as a secondary base at +8, flags at +0x38.  Base vtable 0x013eb90c, final
// vtable 0x013eb844.
struct cMessageData {
    u32 mData08;                                                          // +0x08
    u32 mData0c;                                                          // +0x0c
    u32 mData10;                                                          // +0x10
    u32 mData14;                                                          // +0x14
    u32 mData18;                                                          // +0x18
    u32 mData1c;                                                          // +0x1c
    u32 mData20;                                                          // +0x20
    u32 mData24;                                                          // +0x24
    u32 mData28;                                                          // +0x28
    u32 mData2c;                                                          // +0x2c
    u32 mMessageID;                                                       // +0x30
    cMessageData(u32 id) : mMessageID(id) {}
};

struct RefBase {                              // vtable 0x013eb90c
    virtual void v0();
    virtual int AddRef();                                                 // +0x04
    virtual int Release();                                                // +0x08
    long rc;                                                              // +0x04
    RefBase() { _InterlockedExchange(&rc, 0); }
};

struct cMessage : cMessageData, RefBase {     // vtable 0x013eb844
    u32 mData34;                                                          // +0x34
    u32 mFlags;                                                           // +0x38
    u32 mData3c;                                                          // +0x3c
    cMessage(u32 id) : cMessageData(id), mFlags(0) {}
};

struct cMessagePtr {
    cMessage* mpMessage;
    cMessagePtr(cMessage* p) : mpMessage(p) { if (p) p->AddRef(); }
    ~cMessagePtr() { mpMessage->Release(); }
    cMessage* operator->() const { return mpMessage; }
};

struct cMessageServer {
    VSLOT(0); VSLOT(1); VSLOT(2); VSLOT(3); VSLOT(4);
    virtual void SendMSG(u32 id, void* data, void* target);               // +0x14
    virtual void PostMSG(u32 id, cMessage* msg, void* a, void* b);        // +0x18
};
cMessageServer* MessageServer();              // 0x0067dcc0

struct cTribeModeController { bool IsPlacing(); };   // 0x00d09660

namespace SP {

struct cTribeInputStrategy {
    char pad[0x5c];
    cTribeModeController* mpModeController;    // +0x5c

    void RestorePlanner(int param_2);
};

// @ 0x00ccef10
void cTribeInputStrategy::RestorePlanner(int param_2)
{
    cTribeModeController* c = mpModeController;
    if (!c)
        return;
    if (c->IsPlacing())
        return;
    if (param_2 == -1)
        return;
    cMessagePtr msg(new (g_allocTag, 0, 0, 0, 0) cMessage(0));
    msg->mMessageID = 0xb2699146;
    msg->mData08 = param_2;
    MessageServer()->PostMSG(msg->mMessageID, msg.mpMessage, 0, 0);
}

}  // namespace SP

// ===========================================================================
// 0x00ccece0  ShowSelection  (cdecl; 5 stack args)
//
//   callers (e.g. 0x00cd0910 / 0x00cd0e69 / 0x00cd106c / 0x00cd11fd) push
//   (arg5=flag, arg4=float, arg3=0, arg2=id, arg1=cursor) and clean 0x14.
// ===========================================================================
struct Vec3 { float x, y, z; };

struct Mat33 {
    float m[9];
    void Ctor(const void* src);                                   // 0x0041cb40
};

struct SelRecord {
    unsigned short flags;                                         // +0x00
    unsigned short count;                                         // +0x02
    float x, y, z;                                                // +0x04
    float scale;                                                  // +0x10
    Mat33 mat;                                                    // +0x14
};

struct SelCursor {
    virtual void v0();
    virtual void Release();                                       // +0x04
    virtual void v2(int);                                         // +0x08
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void Submit(SelRecord* rec);                          // +0x18
};

struct IEffectsManager {
    VSLOT(0); VSLOT(1); VSLOT(2); VSLOT(3); VSLOT(4); VSLOT(5);
    VSLOT(6); VSLOT(7); VSLOT(8); VSLOT(9); VSLOT(10);
    virtual char CreateCursor(u32 id, int z, SelCursor** out);    // +0x2c
};
IEffectsManager* EffectsManager();                                // 0x0067ddd0

struct IPlanetModel {
    void  F_00b81630(Vec3* out, void* a);                         // 0x00b81630
    Vec3* F_00b7e3b0(Vec3* out, const Vec3* in);                  // 0x00b7e3b0
};
IPlanetModel* PlanetModel();                                      // 0x00b3d350

void F_006985b0(Vec3* up, const Vec3* facing);                    // 0x006985b0
void F_0069b440(float* mat, const Vec3* up, const Vec3* facing);  // 0x0069b440

extern float g_169b264, g_169b268, g_169b26c;                     // 0x0169b264..
extern char  g_169b240[];                                         // 0x0169b240

// @ 0x00ccece0
void ShowSelection(void* pArg1, u32 id, int arg3, float f, char flag)
{
    SelCursor* L = 0;
    IEffectsManager* em = EffectsManager();
    if (L)
    {
        SelCursor* old = L;
        L = 0;
        old->Release();
    }
    if (em->CreateCursor(id, arg3, &L))
    {
        Vec3 vec;
        PlanetModel()->F_00b81630(&vec, pArg1);

        SelRecord rec;
        rec.count = 0;
        rec.scale = 1.0f;
        rec.flags = 0;
        rec.x = g_169b264;
        rec.y = g_169b268;
        rec.z = g_169b26c;
        rec.mat.Ctor(g_169b240);
        rec.flags |= 4;
        rec.count++;
        rec.x = vec.x;
        rec.y = vec.y;
        rec.z = vec.z;

        Vec3 facing;
        if (flag == 0)
        {
            double sum = (double)vec.x * vec.x + (double)vec.y * vec.y + (double)vec.z * vec.z + 1e-8f;
            float s = (float)(1.0 / sqrt(sum));
            facing.x = vec.x * s;
            facing.y = vec.y * s;
            facing.z = vec.z * s;
        }
        else
        {
            Vec3 tmp;
            Vec3* r = PlanetModel()->F_00b7e3b0(&tmp, &vec);
            facing.x = r->x;
            facing.y = r->y;
            facing.z = r->z;
        }

        Vec3 up;
        Mat33 m;
        F_006985b0(&up, &facing);
        F_0069b440(m.m, &up, &facing);
        rec.mat = m;
        rec.flags |= 2;
        rec.count++;
        if (f != 1.0f)
        {
            rec.count++;
            rec.scale = f;
        }
        L->Submit(&rec);
        L->v2(0);
    }
    if (L)
        L->Release();
}
