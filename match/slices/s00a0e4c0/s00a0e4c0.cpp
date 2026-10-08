// Slice s00a0e4c0: 0x00A0EA10, loader for the viewer animation table (a versioned binary stream of
// "anim entries": key, name, two floats, flags, and per-entry sub-lists of timed items). Each entry
// is read into a stack Entry and merged into the global entry map keyed by Entry::key (replacing an
// older record only when the new one's float f14 is >= the stored f18).
//
// Versions 5..10 are accepted (anything else returns false). Version <= 8 stores one implicit sub-list;
// version >= 9 stores an explicit sub-list count with per-sub-list item lists.
//
// Class / field names are Claude-coined from usage (not from the PDB; the Ghidra "PDB candidate" name
// ReadResourceGameMeshes is a caller-scored guess and is not used).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>

extern void __cdecl operator_delete__(void* p);     // 0x00f47380

typedef unsigned int uint;

struct IFile {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual uint Read(void* buf, uint nBytes);        // +0x30
};
extern int  __cdecl ReadInt32(IFile* f, void* dst, int count, int endian);   // 0x0093a780
extern bool __cdecl ReadBool(IFile* f, void* dst);                           // 0x0093ac80

extern wchar_t gEmptyString16[];                      // 0x01667bac

// eastl::basic_string<wchar_t> (begin, end, capacity, allocator)
struct string16 {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAllocator;
    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16() {
        if (((int)((char*)mpCapacity - (char*)mpBegin) & -2) > 2 && mpBegin)
            operator_delete__(mpBegin);
    }
    uint size() const { return (uint)(mpEnd - mpBegin); }
    void assign(const wchar_t* b, const wchar_t* e);      // 0x00423650
    void append(uint n, wchar_t c);                       // 0x0042d2e0
    void resizeOut(uint n);                               // 0x00429520
    string16& operator=(const string16& x) { if (&x != this) assign(x.mpBegin, x.mpEnd); return *this; }
    void erase(wchar_t* first, wchar_t* last) {
        if (first != last) {
            memmove(first, last, (uint)((mpEnd - last) + 1) * sizeof(wchar_t));
            mpEnd -= (last - first);
        }
    }
    void resize(uint n) {
        const uint s = size();
        if (n < s) erase(mpBegin + n, mpEnd);
        else if (n > s) append(n - s, 0);
    }
};

struct Item {                 // 0x1c
    float w0, w4;             // defaults 1.0f, -1.0f
    int   w8;
    string16 name;            // +0x0c
};

struct SpAlloc { int mData[2]; };

struct Sub;
struct ItemVec {              // eastl::vector<Item, sp_vector_allocator> (0x14)
    Item* mpBegin; Item* mpEnd; Item* mpCapacity; SpAlloc mAllocator;
    void resize(uint n);                                  // 0x00a0d660
};
struct Sub {                  // 0x18
    ItemVec items;            // +0x00
    int i14;                  // +0x14
};
struct SubVec {               // eastl::vector<Sub, sp_vector_allocator> (0x14)
    Sub* mpBegin; Sub* mpEnd; Sub* mpCapacity; SpAlloc mAllocator;
    void resize(uint n);                                  // 0x00a0e0b0
    void DestroyRange(Sub* first, Sub* last);             // 0x00a0aca0 (thiscall, ecx unused)
    void assign(const SubVec& o);                         // 0x00a0dd90
    ~SubVec() {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};

struct Entry {                // 0x40
    uint     key;             // +0x00
    string16 name;            // +0x04
    float    f14;             // +0x14
    float    f18;             // +0x18 (reset value -1.0f)
    bool     b1c, b1d, b1e;   // +0x1c
    int      i20, i24, i28;   // +0x20 (i28 reset value 4)
    SubVec   subs;            // +0x2c
    void Reset();                                         // 0x00a0e250
    Entry() { subs.mpBegin = 0; subs.mpEnd = 0; subs.mpCapacity = 0; Reset(); }
};

// EASTL rbtree node: {right, left, parent, color}
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; char color; };
struct EntryNode : RBNode { Entry value; };               // value at +0x10

struct EntryMap {
    int pad0;
    RBNode anchor;            // +0x04
    uint size;
    Entry* GetOrInsert(const uint* key);                  // 0x00a0e530 (thiscall, returns &node->value)
};
extern EntryMap gEntryMap;                                // 0x01551a68

// @ 0x00a0ea10
bool __stdcall ReadAnimTable(IFile* f)
{
    int magic;
    uint version;
    ReadInt32(f, &magic, 1, 0);
    ReadInt32(f, &version, 1, 0);
    if (version - 5 <= 5) {
    uint count;
    ReadInt32(f, &count, 1, 0);
    for (uint n = 0; n < count; n++) {
        Entry e;
        e.Reset();

        if (version > 8) {
            ReadInt32(f, &e.key, 1, 0);
            uint len = 0;
            ReadInt32(f, &len, 1, 0);
            e.name.resizeOut(len);
            f->Read(e.name.mpBegin, len * 2);
            ReadInt32(f, &e.f14, 1, 0);
            ReadInt32(f, &e.f18, 1, 0);
            ReadBool(f, &e.b1c);
            ReadBool(f, &e.b1d);
            if (version >= 10)
                ReadBool(f, &e.b1e);
            ReadInt32(f, &e.i20, 1, 0);
            ReadInt32(f, &e.i24, 1, 0);
            int tmp;
            ReadInt32(f, &tmp, 1, 0);
            e.i28 = tmp;

            uint nSubs;
            ReadInt32(f, &nSubs, 1, 0);
            e.subs.resize(nSubs);
            for (uint j = 0; j < nSubs; j++) {
                Sub* s = &e.subs.mpBegin[j];
                ReadInt32(f, &s->i14, 1, 0);
                uint m;
                ReadInt32(f, &m, 1, 0);
                s->items.resize(m);
                for (uint k = 0; k < m; k++) {
                    Item* it = &s->items.mpBegin[k];
                    ReadInt32(f, &it->w0, 1, 0);
                    ReadInt32(f, &it->w4, 1, 0);
                    ReadInt32(f, &it->w8, 1, 0);
                    uint l2 = 0;
                    ReadInt32(f, &l2, 1, 0);
                    it->name.resize(l2);
                    f->Read(it->name.mpBegin, l2 * 2);
                }
            }
        
        } else {
            ReadInt32(f, &e.key, 1, 0);
            if (version >= 8)
                ReadInt32(f, &e.f14, 1, 0);
            e.subs.resize(1);

            uint c = 0;
            ReadInt32(f, &c, 1, 0);
            e.subs.mpBegin->items.resize(c);
            for (uint i = 0; i < c; i++) {
                string16& nm = e.subs.mpBegin->items.mpBegin[i].name;
                uint len = 0;
                ReadInt32(f, &len, 1, 0);
                nm.resize(len);
                f->Read(nm.mpBegin, len * 2);
            }
            for (uint i = 0; i < c; i++)
                ReadInt32(f, &e.subs.mpBegin->items.mpBegin[i].w8, 1, 0);

            Sub* s0 = e.subs.mpBegin;
            if (s0->items.mpBegin != s0->items.mpEnd) {
                string16* nm0 = &s0->items.mpBegin->name;
                if (nm0 != &e.name)
                    e.name.assign(nm0->mpBegin, nm0->mpEnd);
            }

            float a, b;
            ReadInt32(f, &a, 1, 0);
            ReadInt32(f, &b, 1, 0);
            for (uint i = 0; i < c; i++) {
                e.subs.mpBegin->items.mpBegin[i].w4 = b;
                e.subs.mpBegin->items.mpBegin[i].w0 = a;
            }
            ReadBool(f, &e.b1c);
            if (version >= 6)
                ReadInt32(f, &e.f18, 1, 0);
            ReadBool(f, &e.b1d);
            ReadInt32(f, &e.i20, 1, 0);
            if (version < 7)
                e.i24 = e.i20;
            else
                ReadInt32(f, &e.i24, 1, 0);
            int tmp;
            ReadInt32(f, &tmp, 1, 0);
            e.i28 = tmp;
        }

        // merge into the global map: insert unless a record with this key and a newer f18 exists
        RBNode* header = &gEntryMap.anchor;
        RBNode* x = header->parent;
        RBNode* y = header;
        while (x) {
            if (!(((EntryNode*)x)->value.key < e.key)) {
                y = x;
                x = x->left;
            } else
                x = x->right;
        }
        if (y == header || e.key < ((EntryNode*)y)->value.key || e.f14 >= ((EntryNode*)y)->value.f18) {
            Entry* d = gEntryMap.GetOrInsert(&e.key);
            d->key = e.key;
            d->name = e.name;
            d->f14 = e.f14;
            d->f18 = e.f18;
            d->b1c = e.b1c;
            d->b1d = e.b1d;
            d->b1e = e.b1e;
            d->i20 = e.i20;
            d->i24 = e.i24;
            d->i28 = e.i28;
            d->subs.assign(e.subs);
        }
    }
    return true;
    }
    return false;
}
