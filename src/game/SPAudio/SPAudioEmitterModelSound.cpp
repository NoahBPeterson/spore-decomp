// src/game/SPAudio/SPAudioEmitterModelSound.cpp -- migrated from slice(s) s00a36d60 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioEmitterModelSound.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Sound.h"
#include "SP/Audio/cEAPDVoiceManager.h"

// ---- items of slice s00a36d60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cEmitterModelSound {
    float ComputeGainAttenuation(void* a, void* b, void* c, void* d);
};
// ---- items of slice s00a36d60 end

// @ 0x00a37b70
float cEmitterModelSound::ComputeGainAttenuation(void*, void*, void*, void*)
{
    return 1.0f;
}
