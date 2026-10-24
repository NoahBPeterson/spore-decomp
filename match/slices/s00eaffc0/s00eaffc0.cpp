// Slice s00eaffc0 : SP::Audio::cPlayerCityMusic::Read -- clears the three per-layer
// note/id vectors and the event list, then runs a cVarListSerializer over itself.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-.
#include "types.h"

// ------------------------------------------------------------------ helpers
void  __cdecl operator_delete(void* p);                                  // 0xf47380
void* __cdecl memcpy_(void* dst, const void* src, unsigned int n);       // 0x11e0744

// SP::cVarListSerializer: ctor at 0x692f90, Serialize (read direction) at 0x693e10.
// Both are __thiscall members (this in ecx), so model them as methods.
struct CVarListSerializer {
    void ctor(void* owner, void* sig, int flags);   // 0x692f90
    bool Serialize(void* stream);                   // 0x693e10
};

// Range-move used by the inlined vector clear: copies the (possibly empty) span
// [first, last) down to dst.  first/last are distinct parameters so cl keeps the
// runtime `last - first` count instead of folding it away.
static void* move_range(void** dst, void** first, void** last)
{
    memcpy_(dst, first, (unsigned int)((char*)last - (char*)first));
    return dst;
}

// The three "layer" vectors are plain 4-byte-element pointer ranges.  clear() is the
// eastl DoClear shape: move the (empty) tail down, then pull mpEnd back onto mpBegin.
struct PtrRange {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCapacity;   // +0x08
    void clear() {
        void** end = mpEnd;
        void** begin = mpBegin;
        move_range(begin, end, end);
        mpEnd += begin - end;
    }
};

// The event list at +0x1b8 is an eastl intrusive circular list: the sentinel holds
// mpNext/mpPrev pointing at itself when empty.
struct EventNode {
    EventNode* mpNext;   // +0x00
    EventNode* mpPrev;   // +0x04
};
struct EventList {
    EventNode mSentinel; // +0x00  mpNext / mpPrev
    void clear() {
        EventNode* sentinel = &mSentinel;
        EventNode* p = sentinel->mpNext;
        while (p != sentinel) {
            EventNode* next = p->mpNext;
            operator_delete(p);
            p = next;
        }
        sentinel->mpNext = sentinel;
        sentinel->mpPrev = sentinel;
    }
};

struct cPlayerCityMusic {
    char       pad0[0x10c];
    int        m10c;         // +0x10c  "loaded" flag gating Reset
    char       pad1[0x198 - 0x110];
    PtrRange   m198;         // +0x198  layer note range  (begin/end/cap)
    char       pad2[0x1b8 - 0x1a4];
    EventList  m1b8;         // +0x1b8  event list sentinel
    char       pad3[0x1cc - 0x1c0];
    PtrRange   m1cc;         // +0x1cc  layer id range
    char       pad4[0x1e0 - 0x1d8];
    PtrRange   m1e0;         // +0x1e0  layer aux range

    void Reset(char full);                                   // 0xead1a0
    void FUN_00eb05a0();                                     // 0xeb05a0
    bool Read(int stream);                                   // 0xeb0a60
};

// @ 0xeb0a60
bool cPlayerCityMusic::Read(int stream)
{
    if (m10c != 0)
        Reset(0);

    m198.clear();
    m1b8.clear();
    m1cc.clear();
    m1e0.clear();

    char buf[0xa14];
    CVarListSerializer* ser = (CVarListSerializer*)buf;
    ser->ctor(this, (void*)0x15a9198, 0x1a80d26);
    bool ok = ser->Serialize((void*)stream);
    FUN_00eb05a0();
    if (m10c != 0)
        Reset(1);
    return ok;
}
