// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// SP::Audio::cCityMusicViewer::SetMusic
//
// Retail at 0x00ea4f00.  The viewer keeps its current music object at +0xd8,
// the player/note editor at +0xdc and the message-listener bookkeeping at
// +0xf8..+0x108.  Selecting a music object hands it to the editor; when the
// editor accepts it the viewer subscribes to the two message ids in the
// static table at 0x0148730c, follows the new track and refreshes its
// active state from the music object.

struct IRefCounted {
    virtual void v00();                 // +0x00
    virtual void AddRef();              // +0x04
    virtual void Release();             // +0x08
    bool IsActive();                    // 0x00810070 (plain member: retail calls it directly)
};

struct NoteEditor {
    char mPad00[0x14];
    IRefCounted* mpMusic;               // +0x14
    char mPad18[0x54 - 0x18];
    bool mbFlag;                        // +0x54
    bool SetMusic(IRefCounted* pMusic, bool bFlag);   // 0x00ea4250
};

struct MessageServer {
    virtual void v00();                 // +0x00
    virtual void v04();                 // +0x04
    virtual void v08();                 // +0x08
    virtual void v0c();                 // +0x0c
    virtual void v10();                 // +0x10
    virtual void v14();                 // +0x14
    virtual void v18();                 // +0x18
    virtual void v1c();                 // +0x1c
    virtual void v20();                 // +0x20
    virtual void AddListener(void* pHandler, unsigned nMessage); // +0x24
};

void* MessageServerInstance();          // 0x0067dcc0

struct Viewer {
    char mPad00[0xd8];
    IRefCounted* mpMusic;               // +0xd8
    NoteEditor*  mpNoteEditor;          // +0xdc
    char mPadE0[0xf8 - 0xe0];
    void*        mpListenerServer;      // +0xf8
    void*        mpListenerOwner;       // +0xfc
    unsigned     mnListenerIds;         // +0x100
    unsigned     mnListenerCount;       // +0x104
    unsigned     mnListenerIndex;       // +0x108
    void Follow();                      // 0x00ea4cb0
    void SetActive(bool bActive);       // 0x00ea4330
    bool SetMusic(IRefCounted* pMusic);
};

// @ 0x00ea4f00
bool Viewer::SetMusic(IRefCounted* pMusic)
{
    bool bResult = false;
    IRefCounted* pOld = mpMusic;
    if (pMusic != pOld) {
        if (pMusic)
            pMusic->AddRef();
        mpMusic = pMusic;
        if (pOld)
            pOld->Release();
    }
    if (mpNoteEditor->SetMusic(pMusic, false)) {
        MessageServer* pServer = (MessageServer*)MessageServerInstance();
        mpListenerServer = pServer;
        mpListenerOwner = this;
        mnListenerIds = 0x0148730c;
        mnListenerCount = 2;
        mnListenerIndex = 0;
        if (pServer) {
            for (unsigned i = 0; i < 8; i += 4)
                pServer->AddListener(this, *(const unsigned*)(0x0148730c + i));
        }
        Follow();
        SetActive(mpMusic->IsActive());
        bResult = true;
    }
    return bResult;
}
