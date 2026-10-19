// src/game/SPEditors/SPEditorPluginCommands.cpp -- migrated from slice(s) s005cb060 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPluginCommands.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/Message.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "SP/cSPPaletteUI.h"
#include "cSPUILayout.h"
#include "cSPUIPropertyLayout.h"
#include "SP/cString.h"
#include <new>
#include <string.h>

// ---- items of slice s005cb060 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace EA {
namespace Audio {
class IAudioSystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual int GetSystem();  // +0x20
};
}
}
namespace EA {
namespace Audio {
IAudioSystem* GetSystemAT();  // 0x00a206f0
}
}
namespace SP {
void PlayAudio(uint32_t id, int system);         // 0x00435ed0
}
namespace SP {
void GetDirectory(uint32_t id, void* out, int flags);  // 0x00688830
}
namespace SP {
inline int GetAudioSystem() {
  EA::Audio::IAudioSystem* audio = EA::Audio::GetSystemAT();
  return audio ? audio->GetSystem() : 0;
}
}
// ---- items of slice s005cb060 end

// @ 0x005cbb70
namespace SP {
bool EditorCommandHandler(const char* command, void* context, uint32_t* args, int* results)
{
  if (strcmp(command, "EditorTest") == 0)
    return true;
  if (strcmp(command, "PlayAudio") == 0) {
    if (*results == 0)
      PlayAudio(*args, GetAudioSystem());
    else
      PlayAudio(*args, *results);
    return true;
  }
  if (strcmp(command, "GetDirectory") == 0) {
    GetDirectory(*args, results, 0);
    return true;
  }
  return false;
}
}  // namespace SP
