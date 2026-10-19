// src/game/UTFSpore_Win32/EAHashCRC.cpp -- migrated from slice(s) s009323c0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAHashCRC.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" uint32_t g_crc32Table[256];   // 0x01669530

// @ 0x00932d00
namespace EA {
namespace Hash {
void InitCRC32Table()
{
    for (int i = 0; i < 256; i++) {
        uint32_t crc = (uint32_t)i << 24;
        for (int j = 0; j < 8; j++) {
            if (crc & 0x80000000)
                crc = (crc << 1) ^ 0x04c11db7;
            else
                crc = crc << 1;
        }
        g_crc32Table[i] = crc;
    }
}
}
}  // namespace EA::Hash
