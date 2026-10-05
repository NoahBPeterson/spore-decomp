// Slice s00668be0: SP::cSPUIFeedListItem - GetHeaderMessage, feed iteration helpers and
// the asset-list queries (GetAssetList/QueryNumItems wrappers).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void  (__thiscall *FnVoidII)(void*, int, int);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

int __cdecl WStr_Format(wchar_t* dst, const wchar_t* fmt, ...);   // 0x0041e050
void __cdecl EASTL_allocator_deallocate(void* p);                 // 0x00f47380
void* __cdecl FUN_0067de90(void* a);                              // 0x0067de90
void* __cdecl FUN_007eb100(void* a);                              // 0x007eb100
void* __cdecl EA_GetManager();                                    // 0x0067dcd0
void* __cdecl FUN_004aa350(void* self, int count, void* p);       // 0x004aa350
void* __cdecl DoInsertValue0066(void* dst, void* src, int nbytes); // 0x011e0744
void  __cdecl FUN_00642c70(void* self, int n);                    // 0x00642c70
void  __cdecl FUN_006431b0(void* self, void* item, void* end);    // 0x006431b0

extern wchar_t gFmt13f5c04[];   // 0x013f5c04
extern int gVt14002a8;          // 0x014002a8

struct Vec { void* begin; void* end; void* cap; };

struct FeedItem {
    bool FUN_00668be0(wchar_t* dst);
    void FUN_00668c80(void* a1, void* c);
    void FUN_00668d90(Vec* out);
    void FUN_00669410();
};

// -----------------------------------------------------------------------------
// @ 0x00668be0  SP::cSPUIFeedListItem::GetHeaderMessage
// -----------------------------------------------------------------------------
bool FeedItem::FUN_00668be0(wchar_t* dst) {
    const wchar_t* name = *(wchar_t**)((char*)this + 0x18);
    if (name) {
        const wchar_t* author = *(wchar_t**)((char*)this + 0x28);
        if (author) {
            switch (*(int*)((char*)this + 0x13c)) {
            case 1:
                WStr_Format(dst, L"Sporecast \"%s\" by %s", name, author);
                return true;
            case 2:
                WStr_Format(dst, L"Creations by %s", author);
                return true;
            case 3:
                WStr_Format(dst, L"Content tagged \"%s\"", name);
                return true;
            default:
                WStr_Format(dst, gFmt13f5c04, name);
                return true;
            }
        }
    }
    return false;
}

// -----------------------------------------------------------------------------
// @ 0x00668c80  iterate the resource list and append entries to a vector
// -----------------------------------------------------------------------------
struct Item { int a; int b; int c; void* d; };

void FeedItem::FUN_00668c80(void* a1, void* c) {
    (void)a1;
    void* list = FUN_007eb100(c);
    if (!list) return;
    int count = 0;
    void** node = (void**)*(void**)list;
    void** head = (void**)list;
    while (node != head) { ++count; node = (void**)*node; }
    FUN_00642c70(this, count);

    int idx = 1;
    node = (void**)*head;
    while (node != head) {
        void* e = node[5];
        int loc1c = *(int*)((char*)e + 8);
        int loc14 = *(int*)((char*)e + 0xc);
        int loc18 = *(int*)((char*)e + 4);
        void** puVar7 = node + 2;
        int next = idx;
        if (loc1c == 0) {
        use:
            {
                int m28 = *(int*)((char*)(node[5]) + 0x28);
                Item tmp;
                tmp.a = idx;
                tmp.b = m28;
                tmp.c = 0;
                tmp.d = puVar7;
                void* end = *(void**)((char*)this + 4);
                next = idx + 1;
                if (end < *(void**)((char*)this + 8)) {
                    *(void**)((char*)this + 4) = (char*)end + 0x10;
                    if (end) {
                        *(int*)((char*)end + 0) = idx;
                        *(int*)((char*)end + 4) = m28;
                        *(int*)((char*)end + 8) = 0;
                        *(void**)((char*)end + 0xc) = puVar7;
                    }
                } else {
                    FUN_006431b0(this, &tmp, end);
                }
            }
        } else {
            void* mgr = EA_GetManager();
            char ok = ((char(__thiscall*)(void*, void*, int, int, int, int, int))VT(mgr)[3])
                          (mgr, &loc1c, 0, 0, 0, 0, 0);
            next = idx;
            if (ok) goto use;
        }
        idx = next;
        node = (void**)*node;
    }
}

// -----------------------------------------------------------------------------
// @ 0x00668d90  SP::cSPUIFeedListItem::GetAssetList  (PARTIAL - see partial.txt)
// -----------------------------------------------------------------------------
__declspec(noinline) void FeedItem::FUN_00668d90(Vec* out) {
    out->begin = 0;
    out->end = 0;
    out->cap = 0;
    // Skeleton: the real body walks the managed-asset database, filters by the
    // item's feed type/id and pushes 16-byte entries into the output vector.
    (void)this;
}

// -----------------------------------------------------------------------------
// @ 0x00669360  vector-copy constructor helper
// -----------------------------------------------------------------------------
struct Vec4 { void* begin; void* end; void* cap; };

struct Obj9360 {
    void* vt;        // +0x00
    Vec4  v;         // +0x04
    char  pad10[8];  // +0x10
    void* m18;       // +0x18
    Obj9360* init(int p2, Vec* p3);
    void reserve(int count, void* p);   // 0x004aa350
};

Obj9360* Obj9360::init(int p2, Vec* p3) {
    vt = &gVt14002a8;
    int count = (int)((char*)p3->end - (char*)p3->begin) >> 2;
    reserve(count, (char*)p3 + 0xc);
    int nbytes = (int)((char*)p3->end - (char*)p3->begin);
    void* r = DoInsertValue0066(v.begin, p3->begin, nbytes);
    v.end = (char*)r + (nbytes >> 2) * 4;
    m18 = (void*)p2;
    return this;
}

// -----------------------------------------------------------------------------
// @ 0x006693c0  count assets returned by GetAssetList
// -----------------------------------------------------------------------------
__declspec(noinline) int __fastcall FUN_006693c0(void* self) {
    Vec v;
    v.begin = 0;
    v.end = 0;
    v.cap = 0;
    ((FeedItem*)self)->FUN_00668d90(&v);
    int n = (int)((char*)v.end - (char*)v.begin);
    if (v.begin && *(int*)((char*)v.begin - 4) != 0)
        EASTL_allocator_deallocate(v.begin);
    return n >> 4;
}

// -----------------------------------------------------------------------------
// @ 0x00669410  refresh the cached item count
// -----------------------------------------------------------------------------
void __fastcall FUN_00669410(void* self) {
    int n = FUN_006693c0(self);
    *(int*)((char*)self + 0x60) = n;
    if (n != *(int*)((char*)self + 0x64))
        *(uint8_t*)((char*)self + 0x86) = 1;
}
