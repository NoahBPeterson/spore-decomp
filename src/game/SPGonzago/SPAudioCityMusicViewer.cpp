// src/game/SPGonzago/SPAudioCityMusicViewer.cpp -- migrated from slice(s) s00ea4f00, s00ea4e60, s00ea4cb0, s00ea4bd0, s00ea4b40, s00ea4af0, s00ea4a10, s00ea4610, s00ea4330 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioCityMusicViewer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include <new>

// ---- items of slice s00ea4330 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Audio {
struct cUILayout {
    void* mpVtable;                                     // +0x00
    void SetVisibility(bool visible);                   // 0x00810590
};
}
}
namespace SP {
namespace Audio {
struct cCityMusicNoteEditor {
    void SetSoundProperty(bool value);                  // 0x00ea3040
};
}
}
namespace SP {
namespace Audio {
struct IAudioSystem {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual void Begin(uint32_t eventId);               // +0x38
    virtual void v3c();
    virtual void SetParam(uint32_t id, uint32_t value); // +0x40
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual void Commit();                              // +0x58
};
}
}
namespace SP {
namespace Audio {
IAudioSystem* GetSystemAT();                            // 0x00a206f0
}
}
namespace SP {
namespace Audio {
void SetGlobalProperty(uint32_t id, float value);       // 0x005ca880
}
}
namespace SP {
namespace Audio {
void PlayEditorSound(uint32_t handle, uint32_t param, float value, int flag); // 0x00435f40
}
}
namespace SP {
namespace Audio {
extern uint32_t gNoteSoundHandles[6];                   // 0x014872dc
}
}
namespace SP {
namespace Audio {
static __forceinline void SetNoteSound(uint32_t handle, uint32_t eventId, uint32_t noteParam)
{
    IAudioSystem* audio = GetSystemAT();
    if (audio) {
        audio->Begin(eventId);
        audio->SetParam(0x3475385, handle);
        audio->SetParam(0x34753a7, noteParam);
        audio->Commit();
    }
}
}
}
namespace SP {
namespace Audio {
struct cCityMusicViewer {
    unsigned char mPad00[0xd8];                          // +0x000
    cUILayout* mpLayout;                                 // +0x0d8
    cCityMusicNoteEditor* mpNoteEditor;                  // +0x0dc
    unsigned char mPadE0[0x0f4 - 0xe0];                  // +0x0e0
    unsigned char mNoteSoundsOn;                         // +0x0f4

    void SetNoteSounds(bool on);
};
}
}
// ---- items of slice s00ea4330 end

// ---- items of slice s00ea4610 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef int s32;
struct ImageEntry { int m0, m4, m8; };
struct IObject {
virtual void  o00();
virtual void  o04();
virtual void  o08();
    virtual void* o0c(u32 id);
    virtual void  o10();
    virtual void  o14(int a, void* b);
};
struct IWinNode {
virtual void  v00();
virtual void  v04();
virtual void  v08();
    virtual void  v0c(int b);
    virtual void* v10();
    virtual void  v14(int a, void* b);
    virtual void  v18();
    virtual int   v1c();
virtual void  v20();
virtual void  v24();
virtual void  v28();
virtual void  v2c();
virtual void  v30();
virtual void  v34();
virtual void  v38();
virtual void  v3c();
virtual void  v40();
virtual void  v44();
virtual void  v48();
virtual void  v4c();
virtual void  v50();
virtual void  v54();
virtual void  v58();
virtual void  v5c();
virtual void  v60();
virtual void  v64();
virtual void  v68();
virtual void  v6c();
virtual void  v70();
virtual void  v74();
virtual void  v78();
    virtual void  v7c(int a, bool b);
virtual void  v80();
virtual void  v84();
virtual void  v88();
virtual void  v8c();
virtual void  v90();
virtual void  v94();
virtual void  v98();
virtual void  v9c();
virtual void  va0();
virtual void  va4();
    virtual void* va8();
virtual void  vac();
virtual void  vb0();
virtual void  vb4();
virtual void  vb8();
virtual void  vbc();
virtual void  vc0();
virtual void  vc4();
virtual void  vc8();
virtual void  vcc(void** a);
virtual void  vd0(void** a);
virtual void  vd4();
virtual void  vd8();
virtual void  vdc();
virtual void  ve0();
virtual void  ve4();
virtual void  ve8(void* p);
virtual void  vec();
    virtual IWinNode* vf0(int id, int b);
};
struct IRef4 {
    virtual void q00();
    virtual void Release();
};
struct cSPUILayout_s00ea_4610 {
    IWinNode* FindWindowByID(u32 id, int b);                        // 0x008105b0 (ret 8)
};
struct cWindowPulse : IRef4 {
    void SetWindow(IWinNode* pWindow);                              // 0x00e9fe90
};
struct cCityMusicNoteEditor_s00ea_4610 {
    void LoopMelody();                                              // 0x00ea3120
};
struct GroupVec {
    u32* mpBegin;   // +0x00
    u32* mpEnd;     // +0x04
    u32* mpCap;     // +0x08
    s32 size() const { return (s32)((char*)mpEnd - (char*)mpBegin) >> 2; }
};
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
    cSPUILayout_s00ea_4610* mpLayout;            // +0xd8
    cCityMusicNoteEditor_s00ea_4610* mpNoteEditor; // +0xdc
    PulseVec mPulses;                 // +0xe0

    cWindowPulse* PulseAt(int i) { return ((cWindowPulse**)mPulses.mpBegin)[i]; }

    void UpdatePulseWindows();
};
// ---- items of slice s00ea4610 end

// ---- items of slice s00ea4af0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IFace {
    virtual void AddRef();
    virtual void Release();
};
struct Player {
    void Set(IFace* p); // 0x00ea2d50
};
struct Viewer {
    char mPad[0xd4];
    IFace* mpMusic;     // +0xd4
    char mPadD8[0xdc - 0xd8];
    Player* mpPlayer;   // +0xdc
    void Refresh();     // 0x00ea4610
    void SetMusic(IFace* p);
};
// ---- items of slice s00ea4af0 end

// ---- items of slice s00ea4b40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct Player_s00ea_4b40 {
    void Clear(); // 0x00ea3ed0
};
struct Pair {
    void* mpA; // +0x00
    void* mpB; // +0x04
    void Both(void* a, void* b); // 0x00e25bd0
};
struct Obj {
    char mPad[0xd8];
    V3* mpD8;          // +0xd8
    Player_s00ea_4b40* mpPlayer;  // +0xdc
    Pair mPair;        // +0xe0
    char mPadE8[0xf8 - 0xe8];
    void* mpF8;
    void* mpFc;
    void* mp100;
    void* mp104;
    void* mp108;
    void Helper(int n); // 0x00ea4330
    void FUN_00ea4b40();
};
void Free5(void* a, void* b, void* c, void* d, void* e); // 0x00571db0
// ---- items of slice s00ea4b40 end

// ---- items of slice s00ea4bd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefObj_s00ea_4bd0 {
    virtual int AddRef();
    virtual int Release();
};
struct RefPtr_s00ea_4bd0 {
    IRefObj_s00ea_4bd0* mp;

    ~RefPtr_s00ea_4bd0() { if (mp) mp->Release(); }
};
struct IUnknownLike_s00ea_4bd0 {
    virtual int QueryInterface();
    virtual int AddRef();
    virtual int Release();  // slot 0x08
};
struct ComPtr_s00ea_4bd0 {
    IUnknownLike_s00ea_4bd0* mp;

    ~ComPtr_s00ea_4bd0() { if (mp) mp->Release(); }
};
struct Vector_s00ea_4bd0 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    int mAllocator;

    ~Vector_s00ea_4bd0()
    {
        if (mpBegin)
            operator delete(mpBegin);
    }
};
void FreeBlock_s00ea_4bd0(void* p, int a, int b, int c, int d);  // 0x00571db0
struct Block_s00ea_4bd0 {
    void* mpData;
    int mA, mB, mC, mD;

    ~Block_s00ea_4bd0()
    {
        if (mpData) {
            void* p = mpData;
            mpData = 0;
            FreeBlock_s00ea_4bd0(p, mA, mB, mC, mD);
        }
    }
};
struct Membere0_s00ea_4bd0 {
    char pad00[0xf8 - 0xe0];
    ~Membere0_s00ea_4bd0();  // 0x00ea0e60
};
struct BaseA_s00ea_4bd0 {
    virtual ~BaseA_s00ea_4bd0() {}
};
struct BaseB_s00ea_4bd0 {
    virtual ~BaseB_s00ea_4bd0() {}
};
struct Object_s00ea_4bd0 : BaseA_s00ea_4bd0, BaseB_s00ea_4bd0 {
    char pad08[0x3c - 8];
    Vector_s00ea_4bd0 mVec3c;          // +0x3c
    char pad4c[4];
    Vector_s00ea_4bd0 mVec50;          // +0x50
    char pad60[0xcc - 0x60];
    RefPtr_s00ea_4bd0 mpRefcc;         // +0xcc
    RefPtr_s00ea_4bd0 mpRefd0;         // +0xd0
    RefPtr_s00ea_4bd0 mpRefd4;         // +0xd4
    ComPtr_s00ea_4bd0 mpComd8;         // +0xd8
    RefPtr_s00ea_4bd0 mpRefdc;         // +0xdc
    Membere0_s00ea_4bd0 me0;           // +0xe0
    Block_s00ea_4bd0 mBlock;           // +0xf8

    void Shutdown();  // 0x00ea4b40
    virtual ~Object_s00ea_4bd0();
};
// ---- items of slice s00ea4bd0 end


// @ 0x00ea4330
namespace SP { namespace Audio {
void cCityMusicViewer::SetNoteSounds(bool on)
{
    if (mNoteSoundsOn == on)
        return;
    mNoteSoundsOn = on;
    mpNoteEditor->SetSoundProperty(on);
    SetGlobalProperty(0xd1922eb3, (float)on);
    unsigned i = 0;
    if (on) {
        for (; i < 6; ++i) {
            PlayEditorSound(gNoteSoundHandles[i], 0xdb83a083, 1.0f, 0);
            SetNoteSound(gNoteSoundHandles[i], 0x407ab38, 0xad57725a);
            SetNoteSound(gNoteSoundHandles[i], 0x407ab38, 0xdf08e251);
        }
    } else {
        for (; i < 6; ++i) {
            PlayEditorSound(gNoteSoundHandles[i], 0xdb83a083, 0.0f, 0);
            SetNoteSound(gNoteSoundHandles[i], 0x407ab40, 0xad57725a);
            SetNoteSound(gNoteSoundHandles[i], 0x407ab40, 0xdf08e251);
        }
    }
    mpLayout->SetVisibility(on);
}
}}  // namespace SP::Audio

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

// @ 0x00ea4af0
void Viewer::SetMusic(IFace* p)
{
    IFace* old = mpMusic;
    if (p != old) {
        if (p)
            p->AddRef();
        mpMusic = p;
        if (old)
            old->Release();
    }
    mpPlayer->Set(p);
    Refresh();
}

// @ 0x00ea4b40
void Obj::FUN_00ea4b40()
{
    Helper(0);
    if (mpF8) {
        void* a = mpF8;
        void* b = mpFc;
        void* c = mp100;
        void* d = mp104;
        void* e = mp108;
        mpF8 = 0;
        Free5(a, b, c, d, e);
    }
    mPair.Both(mPair.mpA, mPair.mpB);
    mpPlayer->Clear();
    V3* v = mpD8;
    if (v) {
        mpD8 = 0;
        v->v2();
    }
}

// @ 0x00ea4bd0
Object_s00ea_4bd0::~Object_s00ea_4bd0()
{
    Shutdown();
}

