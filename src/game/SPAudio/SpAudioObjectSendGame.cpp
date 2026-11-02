// src/game/SPAudio/SpAudioObjectSendGame.cpp -- migrated from slice(s) s00a3ec00 by tools/migrate/rewrite.py
// Object file: SPAudio/SpAudioObjectSendGame.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern char DAT_01453b10[];               // 0x01453b10 "sendgame"
extern int  spSendGameClass;              // 0x0166eeec

// ---- items of slice s00a3ec00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char DAT_01453b10[];               // 0x01453b10 "sendgame"
extern int  spSendGameClass;              // 0x0166eeec
namespace EA {
namespace Audio {
namespace Eapd {
int*  __cdecl gensym(void* out, const void* name);                                   // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   __cdecl class_new(void* a, void* b, void* newfn, void* dtor,
                        int size, int a6, int a7, int a8);                           // 0x00a48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  __cdecl class_addanything(void* cls, void* fn);                                // 0x00a47f90
}
}
}
// ---- items of slice s00a3ec00 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
int sendgame_new(int a, int b);  // 0x00a3eef0 (stays in the slice: not this object's)
void sendgame_anything(int self, int sym, int b, int argc, int* argv);  // 0x00a3ef30 (stays in the slice: not this object's)

// @ 0x00a3f000
bool SendGame_Register(void)
{
    int buf[2];
    int* p = EA::Audio::Eapd::gensym(buf, DAT_01453b10);   // "sendgame"
    int cls = EA::Audio::Eapd::class_new((void*)p[0], (void*)p[1],
                                         (void*)sendgame_new, 0, 0x30, 0, 6, 0);
    bool ok = cls != 0;
    spSendGameClass = cls;
    bool r = EA::Audio::Eapd::class_addanything((void*)cls, (void*)sendgame_anything);
    return r & ok;
}
