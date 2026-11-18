// Slice s00ea4330 -- SP::Audio::cCityMusicViewer (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {
namespace Audio {

struct IEventModifier {
    void*          mpVtable0;                                // +0x00
    volatile void* mpVtable4;                                // +0x04
    uint32_t       mPad08;                                   // +0x08
    IEventModifier();
};

// ---- cCityMusicViewer members around 0x00ea4330 ----

struct cUILayout {
    void* mpVtable;                                     // +0x00
    void SetVisibility(bool visible);                   // 0x00810590
};

struct cCityMusicNoteEditor {
    void SetSoundProperty(bool value);                  // 0x00ea3040
};

// The audio system, only the virtual slots this function uses.
struct IAudioSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void Begin(uint32_t eventId);               // +0x38
    virtual void v3c();
    virtual void SetParam(uint32_t id, uint32_t value); // +0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void Commit();                              // +0x58
};

IAudioSystem* GetSystemAT();                            // 0x00a206f0
void SetGlobalProperty(uint32_t id, float value);       // 0x005ca880
void PlayEditorSound(uint32_t handle, uint32_t param, float value, int flag); // 0x00435f40

extern uint32_t gNoteSoundHandles[6];                   // 0x014872dc

// Starts one note-preview sound with its two note parameters.
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

struct cCityMusicViewer {
    unsigned char mPad00[0xd8];                          // +0x000
    cUILayout* mpLayout;                                 // +0x0d8
    cCityMusicNoteEditor* mpNoteEditor;                  // +0x0dc
    unsigned char mPadE0[0x0f4 - 0xe0];                  // +0x0e0
    unsigned char mNoteSoundsOn;                         // +0x0f4

    void SetNoteSounds(bool on);
};

// @ 0x00ea4330
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

// @ 0x00ea4fd0
IEventModifier::IEventModifier()
{
    mpVtable4 = (void*)0x013ef094;
    mPad08 = 0;
    mpVtable0 = (void*)0x0148734c;
    mpVtable4 = (void*)0x01487348;
}

} // namespace Audio
} // namespace SP
