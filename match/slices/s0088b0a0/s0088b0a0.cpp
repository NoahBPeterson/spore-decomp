// Slice s0088b0a0: hash-map insert wrapper (UTFSpore manager2.obj family,
// /O2 /MD /Gy /TP /arch=SSE /fp=fast, no /EHsc).
#include "types.h"

struct MapKey {
    int32_t mId;        // +0x00
    int16_t mKind;      // +0x04
    int16_t mPad06;     // +0x06
};

struct MapValue {
    int32_t mWords[5];  // +0x00 .. +0x13
};

struct ValueMap {                  // 0x0088af80: insert(key) -> value slot
    uint32_t pad0000[3];
    MapValue* Insert(MapKey* key);
};

struct Holder {
    uint32_t pad0000[3];           // +0x000
    ValueMap mMap;                 // +0x00c

    bool Add(int32_t id, int16_t kind, const MapValue* value);
};

// @ 0x0088b0a0
bool Holder::Add(int32_t id, int16_t kind, const MapValue* value)
{
    MapKey key;
    key.mId = id;
    key.mKind = kind;
    MapValue tmp = *value;
    MapValue* slot = mMap.Insert(&key);
    *slot = tmp;
    return true;
}
