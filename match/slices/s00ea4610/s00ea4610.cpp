// Slice s00ea4610: SP::Audio::cCityMusicEditor::UpdatePulseWindows.
// SP::Audio::cCityMusicEditor::UpdatePulseWindows
// Rebind the six cWindowPulse windows of the city-music editor to the layout's
// rhythm / instrument / group windows: drop every old window, publish the two
// "row" windows (each with the icon of the selected entry taken from one of the
// three ImageEntry tables), let the note editor relayout itself, then show one
// group window per populated group id and hide the rest.
// Layout of the editor taken from the retail offsets: +0xc0/+0xc4/+0xc8 the
// three ImageEntry arrays, +0xd4 cPlayerCityMusic, +0xd8 cSPUILayout,
// +0xdc cCityMusicNoteEditor, +0xe0..+0xe8 the cWindowPulse vector.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int u32;
typedef int s32;

struct ImageEntry { int m0, m4, m8; };

// ---------------------------------------------------------------- window interfaces
// Slots are named by their retail vtable byte offset.
struct IObject {
    virtual void  o00(); virtual void  o04(); virtual void  o08();
    virtual void* o0c(u32 id);
    virtual void  o10();
    virtual void  o14(int a, void* b);
};

struct IWinNode {
    virtual void  v00(); virtual void  v04(); virtual void  v08();
    virtual void  v0c(int b);
    virtual void* v10();
    virtual void  v14(int a, void* b);
    virtual void  v18();
    virtual int   v1c();
    virtual void  v20(); virtual void  v24(); virtual void  v28(); virtual void  v2c();
    virtual void  v30(); virtual void  v34(); virtual void  v38(); virtual void  v3c();
    virtual void  v40(); virtual void  v44(); virtual void  v48(); virtual void  v4c();
    virtual void  v50(); virtual void  v54(); virtual void  v58(); virtual void  v5c();
    virtual void  v60(); virtual void  v64(); virtual void  v68(); virtual void  v6c();
    virtual void  v70(); virtual void  v74(); virtual void  v78();
    virtual void  v7c(int a, bool b);
    virtual void  v80(); virtual void  v84(); virtual void  v88(); virtual void  v8c();
    virtual void  v90(); virtual void  v94(); virtual void  v98(); virtual void  v9c();
    virtual void  va0(); virtual void  va4();
    virtual void* va8();
    virtual void  vac(); virtual void  vb0(); virtual void  vb4(); virtual void  vb8();
    virtual void  vbc(); virtual void  vc0(); virtual void  vc4(); virtual void  vc8();
    virtual void  vcc(void** a); virtual void  vd0(void** a); virtual void  vd4();
    virtual void  vd8(); virtual void  vdc(); virtual void  ve0(); virtual void  ve4();
    virtual void  ve8(void* p); virtual void  vec();
    virtual IWinNode* vf0(int id, int b);
};

// Refcounted interface whose Release lives at vtable+4.
struct IRef4 {
    virtual void q00();
    virtual void Release();
};

// ---------------------------------------------------------------- collaborators
struct cSPUILayout {
    IWinNode* FindWindowByID(u32 id, int b);                        // 0x008105b0 (ret 8)
};

struct cWindowPulse : IRef4 {
    void SetWindow(IWinNode* pWindow);                              // 0x00e9fe90
};

struct cCityMusicNoteEditor {
    void LoopMelody();                                              // 0x00ea3120
};

// EASTL 3-pointer vector of 4-byte elements: the per-group note counts.
struct GroupVec {
    u32* mpBegin;   // +0x00
    u32* mpEnd;     // +0x04
    u32* mpCap;     // +0x08
    s32 size() const { return (s32)((char*)mpEnd - (char*)mpBegin) >> 2; }
};

// The city-music score: the per-group note counts and the two entry counters.
struct cPlayerCityMusic {
    char  mPad00[0x114];
    GroupVec mGroupCounts;      // +0x114
    char  mPad11c[0xa4];        // +0x120..+0xc4
    u32   mRhythmCount;         // +0x1c4
    u32   mInstrumentCount;     // +0x1c8
};

typedef void* ImageHandle;

void  CreateImageFromResource2(const ImageEntry* entry, void** out, int a, int b, int c); // 0x00806230
void  SetPulseBase(IWinNode* w, int flag);                        // 0x00ea03e0

// EASTL 3-pointer vector of 4-byte elements.
struct PulseVec {
    void* mpBegin;   // +0x00
    void* mpEnd;     // +0x04
    void* mpCap;     // +0x08
};

struct cCityMusicEditor {
    char  mPad00[0xc0];
    ImageEntry* mpGroupImages;        // +0xc0
    ImageEntry* mpRhythmImages;       // +0xc4
    ImageEntry* mpInstrumentImages;   // +0xc8
    char  mPadCc[8];                  // +0xcc..+0xd4
    cPlayerCityMusic* mpPlayer;       // +0xd4
    cSPUILayout* mpLayout;            // +0xd8
    cCityMusicNoteEditor* mpNoteEditor; // +0xdc
    PulseVec mPulses;                 // +0xe0

    cWindowPulse* PulseAt(int i) { return ((cWindowPulse**)mPulses.mpBegin)[i]; }

    void UpdatePulseWindows();
};

// @ 0x00ea4610
void cCityMusicEditor::UpdatePulseWindows()
{
    if (!mpPlayer)
        return;
    if (!mpLayout)
        return;

    s32 pulseCount = (s32)((char*)mPulses.mpEnd - (char*)mPulses.mpBegin) >> 2;
    for (s32 i = 0; i != pulseCount; ++i)
        PulseAt(i)->SetWindow(0);

    SetPulseBase(mpLayout->FindWindowByID(0x5b9c400, 1), 0);

    IWinNode* wRhythm = mpLayout->FindWindowByID(0x514e688, 1);
    u32 rhythmCount = mpPlayer->mRhythmCount;
    bool rhythmVisible = rhythmCount > 0;
    wRhythm->v7c(1, rhythmVisible);
    if (rhythmCount > 0) {
        wRhythm->v7c(1, 1);
        PulseAt(0)->SetWindow(wRhythm);
        if (mpRhythmImages) {
            ImageEntry entry = mpRhythmImages[rhythmCount - 1];
            ImageHandle image = 0;
            CreateImageFromResource2(&entry, &image, 0, -1, -1);
            IObject* obj = (IObject*)wRhythm->vf0(0x5bfe9d0, 0)->va8();
            if (obj)
                obj = (IObject*)obj->o0c(0x103c1908);
            else
                obj = 0;
            obj->o14(0, image);
            if (image)
                ((IRef4*)image)->Release();
        }
    } else {
        wRhythm->v7c(1, 0);
    }

    IWinNode* wInstruments = mpLayout->FindWindowByID(0x5187ce0, 1);
    u32 instrCount = mpPlayer->mInstrumentCount;
    bool instrumentsVisible = instrCount > 0;
    wInstruments->v7c(1, instrumentsVisible);
    if (instrCount > 0) {
        PulseAt(1)->SetWindow(wInstruments);
        if (mpInstrumentImages) {
            ImageEntry entry = mpInstrumentImages[instrCount - 1];
            ImageHandle image = 0;
            CreateImageFromResource2(&entry, &image, 0, -1, -1);
            IObject* obj = (IObject*)wInstruments->vf0(0x5bfe9d0, 0)->va8();
            if (obj)
                obj = (IObject*)obj->o0c(0x103c1908);
            else
                obj = 0;
            obj->o14(0, image);
            if (image)
                ((IRef4*)image)->Release();
        }
    }

    IWinNode* wThird = mpLayout->FindWindowByID(0x5187ce8, 1);
    wThird->v7c(2, instrCount > 0);

    mpNoteEditor->LoopMelody();

    u32 id = 0x514e691;
    s32 groupCount = mpPlayer->mGroupCounts.size();
    for (u32 i = 0; i < groupCount; ++i) {
        u32 value = mpPlayer->mGroupCounts.mpBegin[i];
        if (value > 0u) {
            IWinNode* wGroup = mpLayout->FindWindowByID(id, 1);
            ++id;
            wGroup->v7c(1, 1);
            PulseAt((int)i + 2)->SetWindow(wGroup);
            if (mpGroupImages) {
                ImageEntry entry = mpGroupImages[value - 1];
                ImageHandle image = 0;
                CreateImageFromResource2(&entry, &image, 0, -1, -1);
                IObject* obj = (IObject*)wGroup->vf0(0x5bfe9d0, 0)->va8();
                if (obj)
                    obj = (IObject*)obj->o0c(0x103c1908);
                else
                    obj = 0;
                obj->o14(0, image);
                if (image)
                    ((IRef4*)image)->Release();
            }
        }
    }
    if (id > 0x514e694)
        return;

    while (id <= 0x514e694) {
        IWinNode* wGroup = mpLayout->FindWindowByID(id, 1);
        ++id;
        wGroup->v7c(1, 0);
    }
}
