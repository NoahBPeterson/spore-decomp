// src/game/SPAudio/SPAudioObjectMixer.cpp -- migrated from slice(s) s00a3cbb0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioObjectMixer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"

// unnamed retail callees and globals (address in the comment)
extern char  DAT_01453a40[];                // "mixer" name literal
extern int s_mixer, DAT_0166ee94, DAT_0166ee98, DAT_0166ee9c, spMixerClass;

// ---- items of slice s00a3cbb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char  DAT_01453a40[];                // "mixer" name literal
extern int s_mixer, DAT_0166ee94, DAT_0166ee98, DAT_0166ee9c, spMixerClass;
namespace EA {
namespace Audio {
namespace Eapd {
void* gensym(void* out, const void* name);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   class_new(void* name, void* a, void* alloc, void* dtor, int size, int a2, int a3, int a4);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  class_addmethod(int cls, void* fn, int a, int b, int c, int d);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  class_addanything(int cls, void* fn);
}
}
}
// ---- items of slice s00a3cbb0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00a3ced0(int self, int a, int b);  // 0x00a3ced0 (stays in the slice: not this object's)
void FUN_00a3d120(int a1, int a2, int a3, int a4, int a5);  // 0x00a3d120 (stays in the slice: not this object's)
int FUN_00a3d2a0(int a, int b, int c, int d);  // 0x00a3d2a0 (stays in the slice: not this object's)
void FUN_00a3d360(int self);  // 0x00a3d360 (stays in the slice: not this object's)

// @ 0x00a3d380
int SP_Audio_Mixer_Register(void)
{
    uint8_t buf[8];
    int* p = (int*)EA::Audio::Eapd::gensym(buf, "mixer");
    s_mixer = p[0];
    DAT_0166ee94 = p[1];
    p = (int*)EA::Audio::Eapd::gensym(buf, DAT_01453a40);
    DAT_0166ee98 = p[0];
    DAT_0166ee9c = p[1];
    spMixerClass = EA::Audio::Eapd::class_new((void*)s_mixer, (void*)DAT_0166ee94,
                                              (void*)FUN_00a3d2a0, (void*)FUN_00a3d360,
                                              0x30, 0, 9, 0);
    EA::Audio::Eapd::class_addmethod(spMixerClass, (void*)FUN_00a3ced0, DAT_0166ee98, DAT_0166ee9c, 2, 0);
    EA::Audio::Eapd::class_addanything(spMixerClass, (void*)FUN_00a3d120);
    return 1;
}
