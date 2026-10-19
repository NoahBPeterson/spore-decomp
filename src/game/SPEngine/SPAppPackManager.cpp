// src/game/SPEngine/SPAppPackManager.cpp -- migrated from slice(s) s007db1b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppPackManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdio.h>
#include <string.h>

// ---- items of slice s007db1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PtrVec {
    void** mpBegin;     // +0x0
    void** mpEnd;       // +0x4
    bool Contains(int key);     // 007db5b0
    void* Find(int key);        // 007db5e0
    void* At(int index);        // 007db620
};
void* PtrVec::Find(int key)
{
    int n = (int)(mpEnd - mpBegin);
    for (int i = 0; i < n; ++i) {
        if (*(int*)mpBegin[i] == key)
            return mpBegin[i];
    }
    return 0;
}
// ---- items of slice s007db1b0 end

// @ 0x007db5b0
bool PtrVec::Contains(int key)
{
    for (void** p = mpBegin; p != mpEnd; ++p) {
        if (*(int*)*p == key)
            return true;
    }
    return false;
}

// @ 0x007db620
void* PtrVec::At(int index)
{
    if (index >= 0 && index < (int)(mpEnd - mpBegin))
        return mpBegin[index];
    return 0;
}
