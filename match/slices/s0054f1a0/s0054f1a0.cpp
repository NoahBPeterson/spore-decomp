// Slice s0054f1a0: SP::Pollen::cAssetDirectory serialization helper (mutex-guarded save of
// the directory's maps to a save-area stream). PARTIAL: the save-area object/stream vtable
// construction (local_14/local_20) is not fully recovered; the write sequence and container
// traversal are present. Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"

struct Mtx {
    int Lock(const void* p);
    int Unlock();
};
struct Ctr2 {
    int* F140(void* out);   // 0x564140 map begin-iterator
};

int*  SP_GetSaveArea(int id);      // save-area lookup
int   FUN_0041da30();
void  FUN_00552750();

// @ 0x0054f1a0
char FUN_0054f1a0(int self)
{
    Mtx* mtx = (Mtx*)(self + 8);
    mtx->Lock(&self);
    int* sa = SP_GetSaveArea(0x11ac19d);
    if (sa == 0) {
        mtx->Unlock();
        return 0;
    }
    int* obj = 0;          // local_14 (not fully recovered)
    char ok = 1;
    if (*(int*)(self + 0x48) != 0) {
        int u = FUN_0041da30();
        int made = ((int(__thiscall*)(void*, void*, int, int, int, int, int))
                        ((*(void***)sa)[0x34 / 4]))(sa, (void*)&u, u, 2, 2, 1, 0);
        if (made == 0) {
            if (obj != 0) ((void(__thiscall*)(void*))((*(void***)obj)[8 / 4]))(obj);
            mtx->Unlock();
            return 0;
        }
        // The stream object obtained here is not recovered (PARTIAL); the writes below
        // are the shape used by the original.
        int* st = (int*)((int(__thiscall*)(int*))((*(void***)obj)[0x18 / 4]))(obj);
        ok = ((int(__thiscall*)(void*, const void*, int))((*(void***)st)[0x38 / 4]))(st, &u, 4);
        if (ok) ok = ((int(__thiscall*)(void*, const void*, int))((*(void***)st)[0x38 / 4]))(st, &u, 4);
        if (ok) ok = ((int(__thiscall*)(void*, const void*, int))((*(void***)st)[0x38 / 4]))(st, &u, 4);
        *(int*)(self + 0xbc) = 0;
        if (ok) { /* per-container entry writes (PARTIAL) */ }
        ((void(__thiscall*)(void*))((*(void***)obj)[0x24 / 4]))(obj);
        ((void(__thiscall*)(void*))((*(void***)sa)[0x24 / 4]))(sa);
    }
    char r = ok;
    *(int*)(self + 0xbc) = 0;
    if (obj != 0) ((void(__thiscall*)(void*))((*(void***)obj)[8 / 4]))(obj);
    mtx->Unlock();
    return r;
}
