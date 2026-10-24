// Slice s00ea28f0 - city-music UI: the load/save dialog driver and the note editor.
//   00ea28f0  cCityMusicLoadSave message hook (this = object + 0x10)
//   00ea29b0  cCityMusicLoadSave teardown (vtable restore + member release)
//   00ea2a30  load one resource key and clear the pending flag (this = object + 8)
//   00ea2a60  thumbnail save dialog driver
//   00ea2d50  cCityMusicNoteEditor::SetMusic
//   00ea2da0  note-duration redraw helper (FastRoundToInt23)
//   00ea2f40  cCityMusicNoteEditor::SetTempo
//   00ea3040  sound volume / mute-button property
//   00ea30b0  RedrawNoteDuration
//   00ea3120  cCityMusicNoteEditor::LoopMelody
//   00ea3390  cCityMusicNoteEditor::SetActiveNoteId
//   00ea3420  cCityMusicNoteEditor::RedrawMelody
#include "types.h"
#include <stddef.h>

#define CHK(cls, name, off) typedef char chk_##cls##_##name[(offsetof(cls, name) == (off)) ? 1 : -1]

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;

// ---------------------------------------------------------------------------
// shared call helpers
// ---------------------------------------------------------------------------
static inline void** VTP(void* p) { return *(void***)p; }

void* __cdecl operator new(unsigned int size);

// UI / window-manager entry points
void* __cdecl FUN_0067dda0();            // UI manager
void* __cdecl FUN_0067dd50();            // window manager
void* __cdecl cSPUITooltipPanel_ctor(void* mem, u32 a, void* layout, u32 b, u32 c, u32 d); // 0x00e36150
extern void** vtbl_UI_BehaviorMessage;   // 0x013eb90c
extern void** vtbl_Behavior;             // 0x01452a38

// ===========================================================================
// load/save dialog object
// ===========================================================================
struct cSPUILayout;

struct LoadSaveKey {                     // 12-byte resource key
    u32 mType_00;
    u32 mGroup_04;
    u32 mName_08;
};
CHK(LoadSaveKey, mType_00, 0x00);
CHK(LoadSaveKey, mGroup_04, 0x04);
CHK(LoadSaveKey, mName_08, 0x08);

struct KeyVec {
    LoadSaveKey* mpBegin_00;
    LoadSaveKey* mpEnd_04;
    LoadSaveKey* mpCap_08;
};

struct LoadSaveMsg {
    KeyVec* mpKeys_00;                   // +0x00 key list (for the load-key message)
    u32     mPad_04;
    void*   mpSender_08;                 // +0x08 window that sent the message
};
CHK(LoadSaveMsg, mpKeys_00, 0x00);
CHK(LoadSaveMsg, mpSender_08, 0x08);

struct cSPUILayout {
    void** mpVtbl_00;
    void SetVisibility(bool visible);                              // 0x00810590
    cSPUILayout* FindWindowByID(u32 id, s32 flag);                 // 0x008105b0
    bool SetParentWin(cSPUILayout* parent, bool flag, u32 name);   // 0x008121b0
};

struct cCityMusicViewer {
    u8   mPad_00[0x04];
    void Redraw();                                                 // 0x00ea4610
};

extern void* vtbl_LoadSave_00[];         // 0x01487280
extern void* vtbl_LoadSave_08[];         // 0x0148727c
extern void* vtbl_LoadSave_0c[];         // 0x01487260
extern void* vtbl_LoadSave_10[];         // 0x01487258
extern void* vtbl_PaintSystem[];         // 0x013eb394
extern void* vtbl_ITracerBase[];         // 0x013eb938
extern void* vtbl_ContentValidation[];   // 0x013ec458

struct cCityMusicLoadSave {
    void** mpVtbl_00;                    // +0x00
    u32    mField_04;                    // +0x04
    void** mpVtbl_08;                    // +0x08
    void** mpVtbl_0c;                    // +0x0c
    void** mpVtbl_10;                    // +0x10
    void*  mpField_14;                   // +0x14  IRefCounted (release at vtable+4)
    void*  mpViewer_18;                  // +0x18  viewer (IRefCounted subobject at +4)
    cSPUILayout* mpLayout_1c;            // +0x1c  thumbnail layout
    cSPUILayout* mpLayout_20;            // +0x20  save-dialog layout
    u8     mFlag_24;                     // +0x24
    u8     mFlag_25;                     // +0x25  waiting for save dialog
    u8     mFlag_26;                     // +0x26  waiting for thumbnail
    u8     mPad_27;
    void*  mpWindow_28;                  // +0x28
    u32    mField_2c;                    // +0x2c
    u32    mField_30;                    // +0x30
    u8     mPad_34[0x0c];

    void Shutdown();                                    // 0x00ea26f0
    bool LoadKey(LoadSaveKey key);                      // 0x00ea2790
    void SaveThumbnail();                               // 0x00ea23e0
    void StartDialog(cSPUILayout* dlg);                 // 0x00ea20d0
    void Destroy();                                     // 0x00ea29b0
    void SaveDialog();                                  // 0x00ea2a60
};
CHK(cCityMusicLoadSave, mpVtbl_00, 0x00);
CHK(cCityMusicLoadSave, mpVtbl_08, 0x08);
CHK(cCityMusicLoadSave, mpVtbl_0c, 0x0c);
CHK(cCityMusicLoadSave, mpVtbl_10, 0x10);
CHK(cCityMusicLoadSave, mpField_14, 0x14);
CHK(cCityMusicLoadSave, mpViewer_18, 0x18);
CHK(cCityMusicLoadSave, mpLayout_1c, 0x1c);
CHK(cCityMusicLoadSave, mpLayout_20, 0x20);
CHK(cCityMusicLoadSave, mFlag_24, 0x24);
CHK(cCityMusicLoadSave, mFlag_25, 0x25);
CHK(cCityMusicLoadSave, mFlag_26, 0x26);
CHK(cCityMusicLoadSave, mpWindow_28, 0x28);
CHK(cCityMusicLoadSave, mField_2c, 0x2c);
CHK(cCityMusicLoadSave, mField_30, 0x30);

// the message hook lives in the interface subobject at object+0x10
struct LoadSaveMsgProc {
    u8           mPad_00[0x0c];
    cSPUILayout* mpLayout_0c;            // object+0x1c
    u8           mPad_10[6];
    u8           mFlag_16;               // object+0x26
    u8           mPad_17[0x05];
    void*        mpA_1c;                 // object+0x2c
    void*        mpB_20;                 // object+0x30
    bool HandleMessage(u32 type, LoadSaveMsg* msg);   // 0x00ea28f0
};
CHK(LoadSaveMsgProc, mpLayout_0c, 0x0c);
CHK(LoadSaveMsgProc, mFlag_16, 0x16);
CHK(LoadSaveMsgProc, mpA_1c, 0x1c);
CHK(LoadSaveMsgProc, mpB_20, 0x20);

// the key-loader hook lives in the interface subobject at object+8
struct LoadSaveIface8 {
    u8  mPad_00[0x1c];
    u8  mFlag_1c;                        // object+0x24
    void LoadKeyAndClear(LoadSaveKey* key);           // 0x00ea2a30
};
CHK(LoadSaveIface8, mFlag_1c, 0x1c);

// ---------------------------------------------------------------------------
// @ 0x00ea28f0
// ---------------------------------------------------------------------------
bool LoadSaveMsgProc::HandleMessage(u32 type, LoadSaveMsg* msg)
{
    if (type == 0x50b4709) {
        if (msg->mpSender_08 == (cCityMusicLoadSave*)((char*)this - 0x10)) {
            if (mFlag_16) {
                mFlag_16 = 0;
                mpLayout_0c->SetVisibility(false);
                ((cCityMusicLoadSave*)((char*)this - 0x10))->SaveThumbnail();
                return true;
            }
            void* pm = FUN_0067dda0();
            ((void (__thiscall*)(void*, void*, void*))VTP(pm)[0x14 / 4])(pm, mpA_1c, mpB_20);
        }
    } else if (type == 0x5132389) {
        LoadSaveKey* it = msg->mpKeys_00->mpBegin_00;
        LoadSaveKey* end = msg->mpKeys_00->mpEnd_04;
        while (it != end) {
            if (((cCityMusicLoadSave*)((char*)this - 0x10))->LoadKey(*it))
                return true;
            ++it;
        }
        return true;
    } else {
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00ea29b0
// ---------------------------------------------------------------------------
void cCityMusicLoadSave::Destroy()
{
    mpVtbl_00 = vtbl_LoadSave_00;
    mpVtbl_08 = vtbl_LoadSave_08;
    mpVtbl_0c = vtbl_LoadSave_0c;
    mpVtbl_10 = vtbl_LoadSave_10;
    Shutdown();

    void* p20 = mpLayout_20;
    if (p20)
        ((void (__thiscall*)(void*))VTP(p20)[2])(p20);
    void* p1c = mpLayout_1c;
    if (p1c)
        ((void (__thiscall*)(void*))VTP(p1c)[2])(p1c);
    void* p18 = mpViewer_18;
    if (p18) {
        void* sub = (char*)p18 + 4;
        ((void (__thiscall*)(void*))VTP(sub)[2])(sub);
    }
    void* p14 = mpField_14;
    if (p14)
        ((void (__thiscall*)(void*))VTP(p14)[1])(p14);

    mpVtbl_10 = vtbl_PaintSystem;
    mpVtbl_0c = vtbl_ITracerBase;
    mpVtbl_00 = vtbl_ContentValidation;
}

// ---------------------------------------------------------------------------
// @ 0x00ea2a30
// ---------------------------------------------------------------------------
void LoadSaveIface8::LoadKeyAndClear(LoadSaveKey* key)
{
    cCityMusicLoadSave* self = (cCityMusicLoadSave*)((char*)this - 8);
    self->LoadKey(*key);
    mFlag_1c = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00ea2a60  (drives the thumbnail save dialog; only the observable
// sequence is modelled - the retail body inlines the message/window setup)
// ---------------------------------------------------------------------------
void cCityMusicLoadSave::SaveDialog()
{
    if (mFlag_25 || mFlag_26)
        return;

    mpLayout_1c->SetParentWin(0, true, 0x5b598fa);
    mpLayout_1c->SetVisibility(true);
    ((cCityMusicViewer*)mpViewer_18)->Redraw();
    mpLayout_1c->SetParentWin(0, false, 0x5b598fa);

    // ask the window manager for the thumbnail-sized rect of the music viewer
    void* pm = FUN_0067dda0();
    u32 rect[2];
    ((void (__thiscall*)(void*, u32*, u32, s32, s32, s32, u32, u32))VTP(pm)[0x10 / 4])(
        pm, rect, 0x80, 0x80, 1, -1, 0, 0);
    mField_2c = rect[0];
    mField_30 = rect[1];

    // create the "CityMusicThumbnail" property on the music object
    void* pw = FUN_0067dda0();
    ((void (__thiscall*)(void*, u32, u32, const char*))VTP(pw)[0x48 / 4])(
        pw, mField_2c, mField_30, "CityMusicThumbnail");

    // tooltip panel over the thumbnail
    void* mem = operator new(0x30);
    void* tooltip = 0;
    if (mem)
        tooltip = cSPUITooltipPanel_ctor(mem, 0x43000000, mpLayout_1c, mField_2c, mField_30, 0);
    if (tooltip)
        ((void (__thiscall*)(void*))VTP(tooltip)[0])(tooltip);

    // a small behaviour object that forwards the thumbnail click
    void* mem2 = operator new(0x18);
    void* behavior = 0;
    if (mem2) {
        *(u32*)((char*)mem2 + 0x10) = 0;
        *(void**)mem2 = vtbl_UI_BehaviorMessage;
        *(u32*)((char*)mem2 + 4) = 0;
        *(void**)mem2 = vtbl_Behavior;
        behavior = mem2;
        ((void (__thiscall*)(void*))VTP(behavior)[1])(behavior);
    }
    *(void**)((char*)behavior + 8) = this;

    struct DialogMsg {
        u32 mPad_00[4];
        u32 mType_10;
        void* mpObj_14;
        u32 mPad_18[4];
    } msg;
    msg.mPad_00[0] = 0;
    msg.mPad_00[1] = 0;
    msg.mPad_00[2] = 1;
    msg.mPad_00[3] = 0;
    msg.mType_10 = 0x50b4709;
    msg.mpObj_14 = behavior;
    msg.mPad_18[0] = 0;
    msg.mPad_18[1] = 0;
    msg.mPad_18[2] = 0;
    msg.mPad_18[3] = 0;

    void* pmgr = FUN_0067dd50();
    mField_2c = (u32)((void* (__thiscall*)(void*, void*, void*, void*))VTP(pmgr)[0x78 / 4])(
        pmgr, tooltip, 0, &msg);
    mFlag_26 = 1;

    cSPUILayout* dlg = mpLayout_20->FindWindowByID(0x50232c0, 1);
    void* btn = ((void* (__thiscall*)(cSPUILayout*, u32, s32))VTP(dlg)[0xf0 / 4])(dlg, 0x50229a8, 0);

    void* label = ((void* (__thiscall*)(cSPUILayout*, u32, s32))VTP(dlg)[0xf0 / 4])(dlg, 0x5023398, 0);
    ((void (__thiscall*)(void*, u32))VTP(label)[0x80 / 4])(label, mField_30);

    StartDialog(dlg);
    ((void (__thiscall*)(void*))VTP(behavior)[2])(behavior);
    if (btn)
        ((void (__thiscall*)(void*))VTP(btn)[1])(btn);
}

// ===========================================================================
// note editor
// ===========================================================================
struct cPlayerCityMusicConfig {
    u8    mPad_00[0x10];
    u32   mMinNotes_10;                  // +0x10
    u32   mMaxNotes_14;                  // +0x14
    u8    mPad_18[0x04];
    float mBeatStep_1c;                  // +0x1c
    float mBeatMax_20;                   // +0x20
    u8    mPad_24[0x3c];
    u32   mRangeMax_60;                  // +0x60
};
CHK(cPlayerCityMusicConfig, mMinNotes_10, 0x10);
CHK(cPlayerCityMusicConfig, mMaxNotes_14, 0x14);
CHK(cPlayerCityMusicConfig, mBeatMax_20, 0x20);

union NoteCell {
    u32   mBits;
    float mValue;
};

struct NoteCellVec {
    NoteCell* mpBegin_00;
    NoteCell* mpEnd_04;
    s32 size() const { return (s32)(mpEnd_04 - mpBegin_00); }
};
CHK(NoteCellVec, mpBegin_00, 0x00);
CHK(NoteCellVec, mpEnd_04, 0x04);

struct cPlayerCityMusic {
    void**    mpVtbl_00;                 // +0x00
    u8        mPad_04[0x154];
    u32       mActiveNoteId_158;         // +0x158
    u32       mTempoBits_15c;            // +0x15c
    u8        mPad_160[0x6c];
    NoteCellVec mCells_1cc;              // +0x1cc / +0x1d0
    u8        mPad_1d4[0x0c];
    float*    mpNotePitches_1e0;         // +0x1e0

    void AddRef() { ((void (__thiscall*)(cPlayerCityMusic*))mpVtbl_00[0])(this); }
    void Release() { ((void (__thiscall*)(cPlayerCityMusic*))mpVtbl_00[1])(this); }
    void FUN_00eacf70(bool on);
};
CHK(cPlayerCityMusic, mCells_1cc, 0x1cc);
CHK(cPlayerCityMusic, mpNotePitches_1e0, 0x1e0);

struct RefElem {
    struct cUILayout* mpObject;
};

struct cNoteVec {
    RefElem* mpBegin_00;
    RefElem* mpEnd_04;
    RefElem* mpCap_08;
    u32      mAlloc_0c;
    u32      mAlloc2_10;
};
CHK(cNoteVec, mpBegin_00, 0x00);
CHK(cNoteVec, mpEnd_04, 0x04);
CHK(cNoteVec, mpCap_08, 0x08);

struct cUILayout {
    void** mpVtbl_00;

    cUILayout* FindChildWindow(u32 id)
        { return ((cUILayout* (__thiscall*)(cUILayout*, u32))mpVtbl_00[3])(this, id); }        // +0x0c
    void* GetChild(void* prev)
        { return ((void* (__thiscall*)(cUILayout*, void*))mpVtbl_00[0x10c / 4])(this, prev); } // +0x10c
    cUILayout* NextChild(cUILayout* prev)
        { return ((cUILayout* (__thiscall*)(cUILayout*, cUILayout*))mpVtbl_00[0x10c / 4])(this, prev); } // +0x10c
    void SetValue(s32 a, bool b)
        { ((void (__thiscall*)(cUILayout*, s32, bool))mpVtbl_00[0x28 / 4])(this, a, b); }      // +0x28
    float* GetRect()
        { return ((float* (__thiscall*)(cUILayout*))mpVtbl_00[0x38 / 4])(this); }               // +0x38
    void SetRect4(float* r)
        { ((void (__thiscall*)(cUILayout*, float*))mpVtbl_00[0x60 / 4])(this, r); }             // +0x60
    void SetFloat(float v)
        { ((void (__thiscall*)(cUILayout*, float))mpVtbl_00[0x18 / 4])(this, v); }              // +0x18
    void SetFlag(s32 a, bool b)
        { ((void (__thiscall*)(cUILayout*, s32, bool))mpVtbl_00[0x7c / 4])(this, a, b); }       // +0x7c
    void SetIndex(s32 a)
        { ((void (__thiscall*)(cUILayout*, s32))mpVtbl_00[0x5c / 4])(this, a); }                // +0x5c
    void SetRect2(float* r)
        { ((void (__thiscall*)(cUILayout*, float*))mpVtbl_00[0x6c / 4])(this, r); }             // +0x6c

    cUILayout* FindWindowByID(u32 id, s32 flag);                 // 0x008105b0
    void SetVisibility(bool visible);                            // 0x00810590
};
CHK(cUILayout, mpVtbl_00, 0x00);

struct cCityMusicNoteEditor {
    void**  mpVtbl_00;                   // 0x00
    void**  mpVtblRefCount_04;           // 0x04
    u32     mRefCount_08;                // 0x08
    cPlayerCityMusicConfig* mConfig_0c;  // 0x0c
    cPlayerCityMusic* mpMusic_10;        // 0x10
    cUILayout*      mpLayout_14;         // 0x14
    cNoteVec mNoteLayouts_18[3];         // 0x18
    u8      mEditMode_54;                // 0x54
    u8      mField_55;                   // 0x55
    u8      mPad_56[2];
    u32     mActiveNoteId_58;            // 0x58
    u32     mTempo_5c;                   // 0x5c
    s32     mField_60;                   // 0x60
    float   mOutline_64[4];              // 0x64
    float   mfNoteWidth_74;              // 0x74
    float   mfNoteHeight_78;             // 0x78
    float   mfGridLeft_7c;               // 0x7c
    float   mfSpacingX_80;               // 0x80
    float   mfSpacingY_84;               // 0x84
    float   mfRowHeight_88;              // 0x88
    u8      mPad_8c[0x2c];

    void SetMusic(cPlayerCityMusic* p);                  // 0x00ea2d50
    void FastRoundToInt23(u32 note, float value);        // 0x00ea2da0
    void SetTempo(u32 tempo);                            // 0x00ea2f40
    void SetSoundProperty(bool up);                      // 0x00ea3040
    void SetActiveNoteId(u32 id);                        // 0x00ea3390
    void RedrawMelody(s32 flag);                         // 0x00ea3420
    void LoopMelody();                                   // 0x00ea3120
};
CHK(cCityMusicNoteEditor, mConfig_0c, 0x0c);
CHK(cCityMusicNoteEditor, mpMusic_10, 0x10);
CHK(cCityMusicNoteEditor, mpLayout_14, 0x14);
CHK(cCityMusicNoteEditor, mNoteLayouts_18, 0x18);
CHK(cCityMusicNoteEditor, mEditMode_54, 0x54);
CHK(cCityMusicNoteEditor, mField_55, 0x55);
CHK(cCityMusicNoteEditor, mActiveNoteId_58, 0x58);
CHK(cCityMusicNoteEditor, mTempo_5c, 0x5c);
CHK(cCityMusicNoteEditor, mField_60, 0x60);
CHK(cCityMusicNoteEditor, mOutline_64, 0x64);
CHK(cCityMusicNoteEditor, mfNoteWidth_74, 0x74);
CHK(cCityMusicNoteEditor, mfNoteHeight_78, 0x78);
CHK(cCityMusicNoteEditor, mfGridLeft_7c, 0x7c);
CHK(cCityMusicNoteEditor, mfSpacingX_80, 0x80);
CHK(cCityMusicNoteEditor, mfSpacingY_84, 0x84);
CHK(cCityMusicNoteEditor, mfRowHeight_88, 0x88);

void __cdecl RecursiveButtonSelect(void* window, s32 select);   // 0x00ea03e0

// the note-layout rows live in a global table; a row is a small record whose
// first dword is the offset of the next row
struct NoteLayoutRow {
    s32  mNext_00;
    u8   mPad_04[0x0c];
};
extern char* gNoteLayoutTable;                                  // 0x01440aec

// ---------------------------------------------------------------------------
// @ 0x00ea30b0
// ---------------------------------------------------------------------------
void __cdecl RedrawNoteDuration(cUILayout* p, s32 value)
{
    s32 first;
    s32 last;
    ((void (__thiscall*)(cUILayout*, s32*))p->mpVtbl_00[0xcc / 4])(p, &first);
    ((void (__thiscall*)(cUILayout*, s32*))p->mpVtbl_00[0xd0 / 4])(p, &last);
    while (first != last) {
        NoteLayoutRow* row = (NoteLayoutRow*)(gNoteLayoutTable + first);
        RedrawNoteDuration((cUILayout*)row, value);
        first = row->mNext_00;
    }
    ((void (__thiscall*)(cUILayout*, s32, s32))p->mpVtbl_00[0x7c / 4])(p, 2, value);
}

// ---------------------------------------------------------------------------
// @ 0x00ea2d50
// ---------------------------------------------------------------------------
void cCityMusicNoteEditor::SetMusic(cPlayerCityMusic* p)
{
    cPlayerCityMusic* old = mpMusic_10;
    if (p != old) {
        if (p)
            p->AddRef();
        mpMusic_10 = p;
        if (old)
            old->Release();
    }
    if (mpMusic_10)
        mpMusic_10->FUN_00eacf70(mField_60 > 0);
}

// ---------------------------------------------------------------------------
// @ 0x00ea2da0
// ---------------------------------------------------------------------------
void cCityMusicNoteEditor::FastRoundToInt23(u32 note, float value)
{
    cUILayout* w0 = mNoteLayouts_18[1].mpBegin_00[note].mpObject->FindWindowByID(0x4506b98, 1);
    cUILayout* w1 = mNoteLayouts_18[0].mpBegin_00[note].mpObject->FindWindowByID(0x4515be8, 1);
    cUILayout* w2 = mNoteLayouts_18[1].mpBegin_00[note].mpObject->FindWindowByID(0x4515bb0, 1);

    float* rect = w2->GetRect();
    float x0 = rect[0];
    float x2 = rect[2];

    float scale = (1.0f / mConfig_0c->mBeatMax_20) * value;
    float out[4];
    out[0] = mOutline_64[0] * scale;
    out[1] = mOutline_64[1] * scale;
    out[2] = mOutline_64[2] * scale;
    out[3] = mOutline_64[3] * scale;

    w0->SetRect4(out);
    w1->SetRect4(out);

    float ratio = (x0 - out[2]) / ((out[0] - x0) + (x0 - out[2]));

    for (void* it = w1->GetChild(0); it; it = w1->GetChild(it)) {
        void* a = ((void* (__thiscall*)(void*, u32))VTP(it)[3])(it, 0x8f2b630b);
        if (a)
            ((void (__thiscall*)(void*, float))VTP(a)[0x18 / 4])(a, x2);
        void* b = ((void* (__thiscall*)(void*, u32))VTP(it)[3])(it, 0xaf3dad29);
        if (b)
            ((void (__thiscall*)(void*, float))VTP(b)[0x18 / 4])(b, x0);
    }
    (void)ratio;
}

// ---------------------------------------------------------------------------
// @ 0x00ea2f40
// ---------------------------------------------------------------------------
void cCityMusicNoteEditor::SetTempo(u32 tempo)
{
    if (tempo == mTempo_5c)
        return;

    float spb;
    if (mTempo_5c > 0)
        spb = 60.0f / (float)mTempo_5c;
    else
        spb = 0.0f;

    u32 count = (u32)mpMusic_10->mCells_1cc.size();
    for (u32 i = 0; i < count; ++i) {
        float v = mpMusic_10->mpNotePitches_1e0[i] * spb;
        cUILayout* w = mNoteLayouts_18[0].mpBegin_00[i].mpObject->FindWindowByID(0x4515be8, 1);
        for (cUILayout* it = w->NextChild(0); it; it = w->NextChild(it)) {
            cUILayout* prop = it->FindChildWindow(0x8f2b630b);
            if (prop)
                prop->SetFloat(v);
        }
    }
    mTempo_5c = tempo;
}

// ---------------------------------------------------------------------------
// @ 0x00ea3040
// ---------------------------------------------------------------------------
void cCityMusicNoteEditor::SetSoundProperty(bool up)
{
    mField_60 += up ? 1 : -1;
    if (mpMusic_10)
        mpMusic_10->FUN_00eacf70(mField_60 > 0);

    cUILayout* w = mpLayout_14->FindWindowByID(0x4efc540, 1);
    if (w) {
        cUILayout* h = w->FindChildWindow(0x8ed27e7a);
        if (h)
            h->SetValue(4, mField_60 > 0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ea3390
// ---------------------------------------------------------------------------
void cCityMusicNoteEditor::SetActiveNoteId(u32 id)
{
    u32 old = mActiveNoteId_58;
    if (id == old)
        return;
    if (old) {
        for (int i = 0; i < 3; ++i) {
            RecursiveButtonSelect(mNoteLayouts_18[i].mpBegin_00[mActiveNoteId_58 - 1].mpObject
                                      ->FindWindowByID(0x4515bb0, 1), 0);
        }
    }
    if (id) {
        for (int i = 0; i < 3; ++i) {
            RecursiveButtonSelect(mNoteLayouts_18[i].mpBegin_00[id - 1].mpObject
                                      ->FindWindowByID(0x4515bb0, 1), 1);
        }
    }
    mActiveNoteId_58 = id;
}

// ---------------------------------------------------------------------------
// @ 0x00ea3420
// ---------------------------------------------------------------------------
void cCityMusicNoteEditor::RedrawMelody(s32 flag)
{
    mField_55 = (u8)flag;
    RedrawNoteDuration(mpLayout_14->FindWindowByID(0x4595798, 1), flag);

    u32 count = (u32)mpMusic_10->mCells_1cc.size();

    cUILayout* a = mpLayout_14->FindWindowByID(0x4ecfe40, 1);
    cUILayout* b = mpLayout_14->FindWindowByID(0x4ecfe08, 1);
    if (a && b) {
        a->SetFlag(2, mField_55 && count < mConfig_0c->mMaxNotes_14);
        if (mField_55 && count > mConfig_0c->mMinNotes_10)
            b->SetFlag(2, true);
        else
            b->SetFlag(2, false);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ea3120
// ---------------------------------------------------------------------------
void cCityMusicNoteEditor::LoopMelody()
{
    if (!mpMusic_10)
        return;

    mTempo_5c = (mpMusic_10->mTempoBits_15c < 1) ? 1 : mpMusic_10->mTempoBits_15c;

    u32 count = (u32)mpMusic_10->mCells_1cc.size();

    cUILayout* a = mpLayout_14->FindWindowByID(0x4ecfe40, 1);
    cUILayout* b = mpLayout_14->FindWindowByID(0x4ecfe08, 1);
    if (a && b) {
        a->SetValue(2, mField_55 && (s32)count < mConfig_0c->mMaxNotes_14);
        b->SetValue(2, mField_55 && (s32)count > mConfig_0c->mMinNotes_10);
    }

    cUILayout* c = mpLayout_14->FindWindowByID(0x4efc540, 1);
    if (c) {
        cUILayout* h = c->FindChildWindow(0x8ed27e7a);
        if (h)
            h->SetValue(4, mField_60 > 0);
    }

    mfGridLeft_7c = (float)(mConfig_0c->mMaxNotes_14 - (s32)count) * mfSpacingX_80 * 0.5f
                    + mfNoteWidth_74;

    u32 n = count;
    for (u32 i = 0; i < n; ++i) {
        float y = (float)(s32)i * mfSpacingX_80 + mfGridLeft_7c;
        float x = (float)(s32)(mConfig_0c->mRangeMax_60 - mpMusic_10->mCells_1cc.mpBegin_00[i].mBits)
                  * mfRowHeight_88 + mfNoteHeight_78;

        FastRoundToInt23(i, mpMusic_10->mpNotePitches_1e0[i]);

        for (int row = 0; row < 3; ++row) {
            cUILayout* w = mNoteLayouts_18[row].mpBegin_00[i].mpObject->FindWindowByID(0x4515bb0, 1);
            float r[2];
            r[0] = x;
            r[1] = y;
            w->SetRect2(r);
            if (row != 1) {
                u32 icon = mConfig_0c->mRangeMax_60;
                w->SetIndex(icon);
            }
            w->SetVisibility(true);
        }
    }

    for (u32 i = n; i < (u32)mConfig_0c->mMaxNotes_14; ++i) {
        for (int row = 0; row < 3; ++row)
            mNoteLayouts_18[row].mpBegin_00[i].mpObject->SetVisibility(false);
    }
}
