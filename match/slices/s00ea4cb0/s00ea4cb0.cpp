// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// SP::Audio::cCityMusicViewer::Follow (0x00ea4cb0).
//
// Detaches the window of every pulse the viewer currently owns, rebuilds the
// pulse list for the new music object (note count at +0x18, plus the two
// fixed pulses at index 0 and 1), then lets the note editor rebuild its note
// layout and refreshes the viewer.

typedef unsigned int uint;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct IWnd {
    virtual void AddRef();                        // 0x00
    virtual void Release();                       // 0x04
    PV                                            // 0x08
    virtual void* GetChild(uint id);              // 0x0c
    virtual IWnd* Slot10();                       // 0x10
    PV4 PV                                        // 0x14..0x24
    virtual void  Slot28(int a, int b);           // 0x28
    PV16 PV4                                      // 0x2c..0x78
    virtual void  Slot7c(int a, int b);           // 0x7c
    PV4 PV2                                       // 0x80..0x94
    virtual void  Slot98();                       // 0x98
    PV8 PV4                                       // 0x9c..0xc8
    virtual void  SlotCC(void** out);             // 0xcc
    virtual void  SlotD0(void** out);             // 0xd0
    PV4 PV                                        // 0xd4..0xe4
    virtual void  SlotE8(void* p);                // 0xe8
    PV                                            // 0xec
    virtual void* SlotF0(uint id, int a);         // 0xf0
    PV4                                           // 0xf4..0x100
    virtual void  Slot104(void* p);               // 0x104
    virtual void  Slot108(void* p);               // 0x108
};

// The first base of cWindowPulse (vtable at +0).
struct IRefCount {
    virtual void AddRef();                        // 0x00
    virtual void Release();                       // 0x04
};

// The second base of cWindowPulse (vtable at +4, member at +8).
struct PulseBase {
    virtual void Slot00();                        // 0x00
    virtual void Slot04();                        // 0x04
    virtual void Slot08();                        // 0x08
    virtual void Slot0c();                        // 0x0c
    void* mp08;                                   // +0x08
    PulseBase() : mp08(0) {}
};

struct cWindowPulse : IRefCount, PulseBase {
    IWnd* mpWindow;                               // +0x0c
    float mF10;                                   // +0x10
    cWindowPulse() : mpWindow(0), mF10(1.0f) {}
    static void* operator new(uint size, const char* name, int a, int b, int c, int d);
};

// Element of the pulse vector: a ref-counted pointer to a cWindowPulse.
struct PulseRef {
    cWindowPulse* mpPulse;                        // +0x00
    PulseRef& operator=(cWindowPulse* p)
    {
        cWindowPulse* old = mpPulse;
        if (p != old) {
            if (p)
                p->AddRef();
            mpPulse = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};

struct PulseVec {
    PulseRef* mpBegin;                            // +0x00
    PulseRef* mpEnd;                              // +0x04
    PulseRef* mpCap;                              // +0x08
    void insert(PulseRef* pos, uint n, PulseRef* value);   // 0x00ea1220 (ret 0xc)
    void erase(PulseRef* first, PulseRef* last);           // 0x00e25bd0
};

struct cCityMusicNoteEditor {
    void FUN_00ea3f10();                          // 0x00ea3f10
};

struct Viewer {
    char mPad00[0x18];
    int  mCount18;                                // +0x18
    char mPad1c[0xd8 - 0x1c];
    void* mpMusic;                                // +0xd8
    cCityMusicNoteEditor* mpNoteEditor;           // +0xdc
    PulseVec mPulses;                             // +0xe0
    void Refresh();                               // 0x00ea4610
    void Follow();
};

// @ 0x00ea4cb0
void Viewer::Follow()
{
    PulseVec& v = mPulses;
    uint n = (uint)(v.mpEnd - v.mpBegin);
    for (uint i = 0; i < n; ++i) {
        cWindowPulse* e = v.mpBegin[i].mpPulse;
        if (e->mpWindow) {
            e->mpWindow->Slot108(e);
            e->mpWindow->Slot98();
        }
        IWnd* w = e->mpWindow;
        if (w) {
            e->mpWindow = 0;
            w->Release();
        }
        if (e->mpWindow) {
            e->mpWindow->Slot104(e);
            e->mpWindow->Slot98();
            IWnd* r = e->mpWindow->Slot10();
            r->SlotE8(e->mpWindow);
        }
    }

    uint count = (uint)mCount18 + 2;
    if (count > (uint)(v.mpEnd - v.mpBegin)) {
        PulseRef empty;
        empty.mpPulse = 0;
        v.insert(v.mpEnd,
                       count - (uint)(v.mpEnd - v.mpBegin),
                       &empty);
    } else {
        v.erase(v.mpBegin + count, v.mpEnd);
    }

    for (uint i = 0; i < count; ++i) {
        cWindowPulse* pNew = new ("Audio", 0, 0, 0, 0) cWindowPulse;
        v.mpBegin[i] = pNew;
    }

    mpNoteEditor->FUN_00ea3f10();
    Refresh();
}
