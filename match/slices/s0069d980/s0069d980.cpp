// @ 0x0069d980
#include "game/types.h"

namespace SP {
class cISerializableObject;

// View from cObjectDatabaseOStream's secondary interface at complete-object
// offset 8. The database and status retain their header member names.
struct ObjectDatabaseOStreamInterface {
    void* vtable;
    void* mpRecord;
    void* mpDatabase;
    bool mbOK;

    int WriteSerializableObject(const cISerializableObject* object);
};

int ObjectDatabaseOStreamInterface::WriteSerializableObject(
    const cISerializableObject* object)
{
    if (mbOK) {
        // Conversion through the complete object preserves null adjustment
        // when this interface is reached from a null complete-object pointer.
        void* stream = reinterpret_cast<char*>(this) - 8
            ? this : 0;
        // A live object is never null: this assumption emits no code, but it
        // keeps the base pointer materialised before the virtual call below
        // (otherwise cl sinks the conversion past the call).
        __assume(stream != 0);
        void* writer = ((void* (__thiscall*)(void*))
            (*(void***)mpDatabase)[0x14 / 4])(mpDatabase);
        if (((bool (__thiscall*)(void*, void*, const cISerializableObject*))
            (*(void***)writer)[0x20 / 4])(writer, stream, object)) {
            mbOK = 1;
            return 1;
        }
        mbOK = 0;
        return 0;
    }
    mbOK = 0;
    return 0;
}
}
