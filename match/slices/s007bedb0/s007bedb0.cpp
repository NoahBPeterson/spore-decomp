// Slice s007bedb0 — SP::cThumbnailManager capture/dispatch routines.
// /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"
#include <intrin.h>

struct RectID { int mPageID; int mAllocID; bool IsValid() const { return mAllocID != -1; } };

// ---------------------------------------------------------------------------
// jobs (only Shutdown is needed by ThumbnailDone)
// ---------------------------------------------------------------------------
struct cPaletteThumbnailJob { void Shutdown(); };
struct cEditorThumbnailJob  { void Shutdown(); };
struct cCSAThumbnailJob     { void Shutdown(); };
struct cGameThumbnailJob    { void Shutdown(); };

// ---------------------------------------------------------------------------
// @ 0x007bf610  SP::cThumbnailManager::ThumbnailDone(this, msg)   (ret 4)
// ---------------------------------------------------------------------------
struct MessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void Call14(int a, int b, int c);                 // +0x14
};
MessageServer* __cdecl SP_MessageServer();          // 0x0067dcc0

struct RTTFree {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void Free(int page, int alloc);                   // +0x14
};
void* __cdecl FUN_0067dda0();

struct DoneMsg {
    char pad0[8];
    int m8;                                                    // +0x08
    char pad1[4];
    int m10;                                                   // +0x10
    char pad2[4];
    void* mJob;                                                // +0x18
};

struct cThumbnailManager {
    char pad0[0x14];
    RectID mThumbRectID;                                       // +0x14
    RectID mBlurThumbRectID1;                                  // +0x1c
    RectID mBlurThumbRectID2;                                  // +0x24
    RectID mTempThumbnailBuffer;                               // +0x2c
    RectID mCSALargeRectID;                                    // +0x34
    RectID mCSASmallRectID;                                    // +0x3c
    RectID mCSAAntiAliasRectID;                                // +0x44
    void ThumbnailDone(DoneMsg* msg);
};

void cThumbnailManager::ThumbnailDone(DoneMsg* msg)
{
    int u = msg->m8;
    switch (msg->m10) {
    case 2: ((cCSAThumbnailJob*)msg->mJob)->Shutdown(); break;
    case 1: ((cEditorThumbnailJob*)msg->mJob)->Shutdown(); break;
    case 0: ((cPaletteThumbnailJob*)msg->mJob)->Shutdown(); break;
    case 3: ((cGameThumbnailJob*)msg->mJob)->Shutdown();
    }
    SP_MessageServer()->Call14(u, 0, 0);
    RTTFree* r = (RTTFree*)FUN_0067dda0();
    if (mThumbRectID.IsValid())
        r->Free(mThumbRectID.mPageID, mThumbRectID.mAllocID);
    if (mBlurThumbRectID1.IsValid())
        r->Free(mBlurThumbRectID1.mPageID, mBlurThumbRectID1.mAllocID);
    if (mBlurThumbRectID2.IsValid())
        r->Free(mBlurThumbRectID2.mPageID, mBlurThumbRectID2.mAllocID);
    if (mTempThumbnailBuffer.IsValid())
        r->Free(mTempThumbnailBuffer.mPageID, mTempThumbnailBuffer.mAllocID);
    if (mCSALargeRectID.IsValid())
        r->Free(mCSALargeRectID.mPageID, mCSALargeRectID.mAllocID);
    if (mCSASmallRectID.IsValid())
        r->Free(mCSASmallRectID.mPageID, mCSASmallRectID.mAllocID);
    if (mCSAAntiAliasRectID.IsValid())
        r->Free(mCSAAntiAliasRectID.mPageID, mCSAAntiAliasRectID.mAllocID);
}

// ---------------------------------------------------------------------------
// @ 0x007bf9c0  setter block (this + 8 stack args, ret 0x20)
// ---------------------------------------------------------------------------
struct RefLike {
    virtual int AddRef();                                      // +0x00
    virtual void Release();                                    // +0x04
};
struct RefVector {
    char pad[0x14];
    void operator=(void* v);                                   // 0x0041ebe0
};
struct Pair { int x, y; };

struct SetterBlock {
    char pad0[0xc];
    void* m0c;                                                 // +0x0c
    void* m10;                                                 // +0x10
    char pad1[0x80];                                           // +0x14..0x93
    Pair  m94;                                                 // +0x94
    Pair  m9c;                                                 // +0x9c
    char pad2[4];                                              // +0xa4
    RefLike* m_a8;                                             // +0xa8
    RefVector m_ac;                                            // +0xac
    int   m_c0;                                                // +0xc0
    unsigned char m_c4;                                        // +0xc4
    float m_c8, m_cc, m_d0, m_d4;                              // +0xc8
    unsigned char m_d8;                                        // +0xd8

    void Set(void* a1, int a2, int a3, int a4, Pair* a5, Pair* a6, int a7, char a8);
};

void SetterBlock::Set(void* a1, int a2, int a3, int a4, Pair* a5, Pair* a6, int a7, char a8)
{
    if (m_c4 == 0) {
        m_c0 = 0;
        RefLike* old = m_a8;
        if (a1 != old) {
            if (a1) ((RefLike*)a1)->AddRef();
            m_a8 = (RefLike*)a1;
            if (old) old->Release();
        }
        m0c = (void*)a3;
        m10 = (void*)a4;
        m94.x = a5->x; m94.y = a5->y;
        m9c.x = a6->x; m9c.y = a6->y;
        m_c0 = a7;
        m_c4 = 1;
        m_c8 = 0.0f; m_cc = 0.0f; m_d0 = 0.0f; m_d4 = 0.0f;
        m_ac = (void*)a2;
        m_d8 = (unsigned char)a8;
    }
}

// ---------------------------------------------------------------------------
// large routines (skeletons)
// ---------------------------------------------------------------------------
void FUN_007bedb0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }   // CaptureCSAPhotos
void FUN_007bf300(void* a) { (void)a; }
void FUN_007bf720(void* a) { (void)a; }
