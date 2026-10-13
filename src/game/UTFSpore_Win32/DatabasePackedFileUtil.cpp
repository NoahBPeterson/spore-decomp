// src/game/UTFSpore_Win32/DatabasePackedFileUtil.cpp -- migrated from slice(s) s008dd0d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DatabasePackedFileUtil.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Database.h"
#include "EA/ResourceMan/Key.h"

namespace EA { namespace ResourceMan { class KeyFilter; } }

// @ 0x008dd250
namespace EA {
namespace ResourceMan {
bool CopyDatabaseRecord(Database * src, Database * dst, Key const & a3, bool a4)
{
    if ((*(int (__thiscall**)(void*))((*(void***)dst)[0x0c / 4]))(dst) != 0x2a43bd44)
        ;
    return 0;
}
}
}  // namespace EA::ResourceMan

// @ 0x008dd430
namespace EA {
namespace ResourceMan {
unsigned int CopyDatabaseRecords(Database * self, Database * other, KeyFilter * a3, bool a4)
{
    (void)self; (void)other; (void)a3;
    return 0;
}
}
}  // namespace EA::ResourceMan
