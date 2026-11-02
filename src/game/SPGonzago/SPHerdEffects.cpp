// src/game/SPGonzago/SPHerdEffects.cpp -- migrated from slice(s) s00ea28f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPHerdEffects.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include <stddef.h>

// ---- items of slice s00ea28f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            s32;
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
union NoteCell {
    u32   mBits;
    float mValue;
};
struct NoteCellVec {
    NoteCell* mpBegin_00;
    NoteCell* mpEnd_04;
    s32 size() const { return (s32)(mpEnd_04 - mpBegin_00); }
};
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
// ---- items of slice s00ea28f0 end

// @ 0x00ea3040
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
