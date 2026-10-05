// slice s0063d9e0: cSPPlayModeSubModePhoto activation/shutdown + movie/photo helpers.
#include "../s00636320/s00636320.h"

struct cAutoHandler { uint32_t a, b, c, d, e; };
void RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);   // 0x00571DB0
struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void PostMessage(uint32_t id, void* data, int flags);   // +0x14
};
IMessageServer* GetMessageServer();                                               // 0x0067DCC0

struct IHandlerServer {
    virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); virtual void h4();
    virtual void h5(); virtual void h6(); virtual void h7(); virtual void h8();
    virtual void AddHandler(void* handler, uint32_t id);   // +0x24
};
struct IPhotoBrowser { void HandleMessage(); void Deactivate(); };   // 0x006340C0 / 0x00632FE0
struct IAnimObj {
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual float v3(uint32_t a, uint32_t b, int c, int d, int e);   // +0x0C
};

struct cSPPlayModeSubModePhoto {
    void* mVptr;                   // +0x00
    void* mObj4;                   // +0x04
    IAnimObj* mAnim;               // +0x08
    char pad0c[0x14 - 0x0c];
    char mHandlerSub[0x50 - 0x14]; // +0x14 (IHandler subobject)
    IPhotoBrowser mBrowser;        // +0x50
    char padF30[0xf30 - 0x51];
    bool mbF30;                    // +0xF30
    bool mbF31;                    // +0xF31
    char padF32[0xf58 - 0xf32];
    bool mbF58;                    // +0xF58
    char padF59[0xf78 - 0xf59];
    bool mbF78;                    // +0xF78
    char padF79[0xf9c - 0xf79];
    bool mbF9C;                    // +0xF9C
    bool mbF9D;                    // +0xF9D
    char padF9E[0xfa0 - 0xf9e];
    cAutoHandler mAutoMsgHandler;  // +0xFA0

    bool Activate();               // 0x0063E770
    void Shutdown();               // 0x0063E810
    void FUN_0063d9e0();
    void FUN_0063dc40();
    void FUN_0063de20();
    void FUN_0063e100();
};

// @ 0x0063E770
bool cSPPlayModeSubModePhoto::Activate()
{
    mBrowser.HandleMessage();
    mbF30 = false;
    mbF31 = false;
    mbF58 = false;
    mbF78 = false;
    mbF9C = false;
    mbF9D = false;

    IHandlerServer* ms = (IHandlerServer*)GetMessageServer();
    if (ms) {
        void* handler = (void*)((char*)this + 0x14);
        mAutoMsgHandler.a = (uint32_t)ms;
        mAutoMsgHandler.b = (uint32_t)handler;
        mAutoMsgHandler.c = 0x13ff4d4;
        mAutoMsgHandler.d = 0xd;
        mAutoMsgHandler.e = 0;
        if (handler) {
            for (uint32_t i = 0; i < 0x34; i += 4)
                ms->AddHandler(handler, *(uint32_t*)(0x13ff4d4 + i));
        }
    }
    return true;
}

// @ 0x0063E810
void cSPPlayModeSubModePhoto::Shutdown()
{
    if (mAutoMsgHandler.a) {
        uint32_t a = mAutoMsgHandler.a, b = mAutoMsgHandler.b, c = mAutoMsgHandler.c;
        uint32_t d = mAutoMsgHandler.d, e = mAutoMsgHandler.e;
        mAutoMsgHandler.a = 0;
        RemoveHandler(a, b, c, d, e);
    }
    mBrowser.Deactivate();
    mAnim->v3(*(uint32_t*)((char*)mObj4 + 0x364), 0x4330667, 1, 1, 0);
}

// @ 0x0063D9E0  PARTIAL
void cSPPlayModeSubModePhoto::FUN_0063d9e0() {}
// @ 0x0063DC40  PARTIAL
void cSPPlayModeSubModePhoto::FUN_0063dc40() {}
// @ 0x0063DE20  PARTIAL
void cSPPlayModeSubModePhoto::FUN_0063de20() {}
// @ 0x0063E100  PARTIAL
void cSPPlayModeSubModePhoto::FUN_0063e100() {}
