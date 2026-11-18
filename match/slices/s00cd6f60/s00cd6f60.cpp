// @ 0x00cd6f60
#include "game/types.h"
#include "SP/cIObjectDatabaseOStream.h"

namespace EA { namespace IO {
class IStream;
bool __cdecl WriteUint32(IStream*, const unsigned int*, int, int); // 0x0093aa70
} }

// The generated database-stream header has unnamed virtual methods. These
// calls retain the retail slots until those interface declarations are known.
bool __cdecl WriteTribeObjectArray(SP::cIObjectDatabaseOStream* stream, void* const* objects)
{
    void* record = ((void* (__thiscall*)(void*))(*(void***)stream)[8])(stream);
    void** recordVtable = *(void***)record;
    EA::IO::IStream* output;
    {
        unsigned int count = 20;
        output = ((EA::IO::IStream* (__thiscall*)(void*))recordVtable[6])(record);
        EA::IO::WriteUint32(output, &count, 1, 0);
    }
    unsigned int remaining = 20;
    do {
        void* object = *objects;
        void* serializable = 0;
        if (object)
            serializable = ((void* (__thiscall*)(void*, unsigned int))
                (*(void***)object)[3])(object, 0x0179c807);
        ((bool (__thiscall*)(void*, void*))(*(void***)stream)[11])(stream, serializable);
        ++objects;
    } while (--remaining);
    return true;
}
