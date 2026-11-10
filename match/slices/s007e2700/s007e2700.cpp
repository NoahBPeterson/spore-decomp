// Slice s007e2700 -- select the "current" object of a UI owner.
//
//  0x007e2700  Owner::SetCurrent(int id):
//              * ask the object factory (0x838320) for the instance of id (mask 1),
//              * notify the owner's map through its virtual slot +0x38 with the
//                object's first word; the call returns the value to record,
//              * if the owner already has a selection, look it up in the owner's
//                selection map (0x645ed0) and, when the mapped slot is not the
//                built-in one, store the value in that slot's table (the slot's
//                index +4, entries 0xa0 bytes apart, field +0x4c),
//              * record the value as the current selection.
#include "types.h"

// compile with /O2 /MD /Gy /TP /arch:SSE /fp:fast

struct SelMap {
    void** mVt;            // +0x00
    char   pad04[0x7c - 0x04];
    int    mCurrent;       // +0x7c
    char   pad80[0xa4 - 0x80];
    char*  mTable;         // +0xa4
    char   padA8[0xb8 - 0xa8];
    int*   mKeys;          // +0xb8
    int*   mIds;           // +0xbc
    int    mCount;         // +0xc0
};

struct SelTree {
    int* Find(int* out, int* key);     // 0x00645ed0
};

struct SelObj {
    char pad0[0x4c];
    void* mCur;      // +0x4c
};

struct Owner {
    char    pad0[0x0c];
    SelMap* mMap;        // +0x0c
    char    pad10[0x7c - 0x10];
    int     mCurrent;    // +0x7c

    void SetCurrent(int id);
};

// 0x838320 is a __thiscall thunk: ecx = id, one stack argument (the mask).
struct Factory {
    int* Get(int arg);   // 0x00838320
};

// @ 0x007e2700
void Owner::SetCurrent(int id)
{
    volatile int* objp = ((Factory*)id)->Get(1);
    int* obj = (int*)0;
    obj = (int*)objp;
    SelMap* map = mMap;
    void* cur = ((void*(__thiscall*)(void*, void*))map->mVt[0x38 / 4])(map, *(void**)obj);

    int key;
    int* slot = ((SelTree*)map->mKeys)->Find(&key, &map->mCurrent);
    if (map->mCurrent != -1) {
        if (slot != map->mIds + map->mCount) {
            SelObj* e = (SelObj*)(map->mTable + *(int*)((char*)slot + 4) * 0xa0);
            e->mCur = cur;
            map->mCurrent = (int)cur;
            return;
        }
    }
    map->mCurrent = (int)cur;
}
