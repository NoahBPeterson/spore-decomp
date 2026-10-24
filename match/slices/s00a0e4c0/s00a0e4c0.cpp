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
#include <stdio.h>
#include <wchar.h>

extern void __cdecl operator_delete__(void* p);     // 0x00f47380

typedef unsigned int uint;

struct IFile {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(int, int); virtual void v11();
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
    union { int i14; float f14; };
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
    Entry(const Entry& o);                                // 0x00a0d7a0
    Entry& operator=(const Entry& o);                     // 0x00a0df30
};

// EASTL rbtree node: {right, left, parent, color}
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; char color; };
struct EntryNode : RBNode { Entry value; };               // value at +0x10
struct AnimNode : RBNode { uint key; Entry value; };      // key +0x10, value +0x14

struct EntryMap {
    int pad0;
    RBNode anchor;            // +0x04
    uint size;
    Entry* GetOrInsert(const uint* key);                  // 0x00a0e530 (thiscall, returns &node->value)
    void Insert(void* out, RBNode* hint, const void* pair, int flag); // 0x00a0e180
    void Find(RBNode** out, const uint* key);             // 0x00e5c780
    void DoNukeSubtree(RBNode* root);                     // 0x00a0d9c0
};
extern EntryMap gEntryMap;                                // 0x01551a68

// Value inserted into the map: key followed by the value (rbtree pair<const uint, Entry>).
struct EntryPair {
    uint key;
    Entry value;
    EntryPair(uint k, const Entry& v) : key(k), value(v) {}
};

// Shared animation-parsing state referenced by the anim commands (this+0x30).
struct AnimParseContext {     // 0x58
    uint   mMagic;            // +0x00 (0x02328502)
    float  mF4;               // +0x04
    EntryMap* mpMap;          // +0x08
    Entry  mEntry;            // +0x0c
    float  mF4c;              // +0x4c
    float  mW0;               // +0x50
    float  mW4;               // +0x54
    AnimParseContext(EntryMap* map);                      // 0x00a0e4c0
    ~AnimParseContext();                                  // 0x00a0d420
};

struct AnimCommandA {         // cAnimCommand (vtable 0x1448be4, OnEndBlock at +0x14)
    int mPad[12];             // +0x00..0x2f
    AnimParseContext* mpContext;                          // +0x30
    void OnEndBlock(char flag);                           // 0x00a0e690
};
struct AnimCommandB {         // cAnimCommand variant (vtable 0x1448d10)
    int mPad[12];
    AnimParseContext* mpContext;                          // +0x30
    void OnEndBlock(char flag);                           // 0x00a0e840
};

extern uint __cdecl FNV1_String16(const wchar_t* s, uint seed, int mode); // 0x00932f30
extern void __cdecl PrintError(const char* msg, const char* group);       // 0x00e31100

// ---- ArgScript / resource plumbing used by ReadAnimList ----
struct ArgScriptParser {
    virtual void p0();                                    // +0x00
    virtual void p1();                                    // +0x04
    virtual void p2();                                    // +0x08
    virtual void p3();                                    // +0x0c
    virtual void p4(void* ctx);                           // +0x10
    virtual void p5(const char* name, void* cmd);         // +0x14
    virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9();
    virtual void p10(int a, int b);                       // +0x28
    virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
    virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18();
    virtual void p19(IFile* f);                           // +0x4c
};
extern ArgScriptParser* __cdecl CreateParser();           // 0x008408d0

struct cCommandBase { void Construct(); };                // 0x0083c800
struct AppPropsFields { void Construct(); };              // 0x0083cdd0
extern void* __cdecl AllocCommand(uint size);             // 0x006abeb0

struct ResourceMan {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
    virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7();
    virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11();
    virtual void r12(); virtual void r13();
    virtual int FindList(void* vec, const void* key, int flag); // +0x38
    virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18();
    virtual void r19(); virtual void r20(); virtual void r21();
    virtual void* GetResource(const void* key);           // +0x58
};
extern ResourceMan* __cdecl GetResourceManager();         // 0x0067dcd0

struct IResourceObj {
    virtual void o0(); virtual void o1(); virtual void o2(); virtual void o3();
    virtual void o4(); virtual void o5(); virtual void o6(); virtual void o7();
    virtual void o8(); virtual void o9(); virtual void o10(); virtual void o11();
    virtual void o12();
    virtual bool Load(const void* key, void** out, int a, int b, int c, int d); // +0x34
};
struct ILoadedResource {
    virtual void h0(); virtual void h1();
    virtual void Release();                               // +0x08
    virtual void h3(); virtual void h4(); virtual void h5();
    virtual IFile* GetStream();                           // +0x18
    virtual void h7(); virtual void h8();
    virtual void Close();                                 // +0x24
};
struct ResourceKey { uint mType; uint mInstance; };
struct ResKeyEntry { uint m0, m1, m2; };                  // 0x0c (EA::ResourceMan::Key)
struct KeyVec {
    ResKeyEntry* mpBegin; ResKeyEntry* mpEnd; ResKeyEntry* mpCapacity; int mAlloc[2];
    ~KeyVec() {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};
extern void __cdecl ThreadSleep(const int* ms);           // 0x00921df0

struct cSPCreatureAnimManager {
    bool ReadAnimList(char force);                        // 0x00a0f080
};

extern uint8_t gVtblPriorityCommand[];                    // 0x01448bcc
extern uint8_t gVtblAnimCommand[];                        // 0x01448be4
extern uint8_t gVtblAnim2Command[];                       // 0x01448d10
extern const char* gNamePriority;                         // 0x01551810
extern const char* gNameAnim;                             // 0x01551818
extern const char* gNameAnim2;                            // 0x015517e8
extern uint32_t gAnimListLoaded;                          // 0x01551a7c

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

// @ 0x00a0e4c0
AnimParseContext::AnimParseContext(EntryMap* map)
    : mMagic(0x2328502), mF4(0.0f), mpMap(map), mF4c(0.0f), mW0(1.0f), mW4(-1.0f)
{
}

// @ 0x00a0e530
Entry* EntryMap::GetOrInsert(const uint* key)
{
    RBNode* header = &anchor;
    RBNode* x = header->parent;
    RBNode* y = header;
    while (x) {
        if (((AnimNode*)x)->key < *key) {
            x = x->right;
        } else {
            y = x;
            x = x->left;
        }
    }
    if (y == header || *key < ((AnimNode*)y)->key) {
        Entry e;
        EntryPair pair(*key, e);
        union { AnimNode* node; uint raw; uint8_t byte; } out;
        out.byte = 0;
        Insert(&out.node, y, &pair, out.raw);
        return &out.node->value;
    }
    return &((AnimNode*)y)->value;
}

// @ 0x00a0e690
void AnimCommandA::OnEndBlock(char flag)
{
    if (flag) return;
    if (mpContext->mEntry.subs.mpBegin == mpContext->mEntry.subs.mpEnd) {
        PrintError("AnimList parsing error: no existing mChoices!?\n", "AnimList parsing error!");
        return;
    }
    uint n = (uint)(mpContext->mEntry.subs.mpBegin->items.mpEnd
                  - mpContext->mEntry.subs.mpBegin->items.mpBegin);
    for (uint i = 0; i < n; i++) {
        Item* it = &mpContext->mEntry.subs.mpBegin->items.mpBegin[i];
        wchar_t* full = it->name.mpBegin;
        wchar_t* slash = wcsrchr(full, L'/');
        wchar_t* base = slash ? slash + 1 : full;
        if (i == 0) {
            wchar_t* end = base;
            while (*end) ++end;
            mpContext->mEntry.name.assign(base, end);
        }
        it->w8 = FNV1_String16(base, 0x811c9dc5, 1);
        it->w0 = mpContext->mW0;
        it->w4 = mpContext->mW4;
    }
    if (mpContext->mEntry.i28 == 4) {
        char buf[1024];
        sprintf(buf, "animId 0x%08x : No end mode defined", mpContext->mEntry.key);
        PrintError(buf, "AnimList parsing error!");
        return;
    }
    RBNode* found;
    mpContext->mpMap->Find(&found, &mpContext->mEntry.key);
    if (found == &mpContext->mpMap->anchor || mpContext->mEntry.f14 >= ((AnimNode*)found)->value.f14) {
        Entry* d = mpContext->mpMap->GetOrInsert(&mpContext->mEntry.key);
        *d = mpContext->mEntry;
    }
}

// @ 0x00a0e840
void AnimCommandB::OnEndBlock(char flag)
{
    if (flag) return;
    if (mpContext->mEntry.subs.mpBegin == mpContext->mEntry.subs.mpEnd) return;
    float scale = 1.0f;
    if (mpContext->mF4c > 0.0f) scale = 1.0f / mpContext->mF4c;
    uint n = (uint)(mpContext->mEntry.subs.mpEnd - mpContext->mEntry.subs.mpBegin);
    float prev = 0.0f;
    for (uint i = 0; i < n; i++) {
        float v = mpContext->mEntry.subs.mpBegin[i].f14 * scale + prev;
        mpContext->mEntry.subs.mpBegin[i].f14 = v;
        prev = v;
    }
    mpContext->mEntry.subs.mpEnd[-1].f14 = 1.0f;
    if (mpContext->mEntry.i28 == 4) {
        char buf[1024];
        sprintf(buf, "animId 0x%08x : No end mode defined", mpContext->mEntry.key);
        PrintError(buf, "AnimList parsing error!");
        return;
    }
    RBNode* found;
    mpContext->mpMap->Find(&found, &mpContext->mEntry.key);
    if (found == &mpContext->mpMap->anchor || mpContext->mEntry.f14 >= ((AnimNode*)found)->value.f14) {
        Entry* d = mpContext->mpMap->GetOrInsert(&mpContext->mEntry.key);
        *d = mpContext->mEntry;
    }
}

// @ 0x00a0f080
bool cSPCreatureAnimManager::ReadAnimList(char force)
{
    if (gAnimListLoaded != 0 && !force) return true;

    KeyVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCapacity = 0;
    ResourceKey key;
    key.mType = 0x13eb428;
    key.mInstance = 0x4aeb6bc6;
    ResourceMan* mgr = GetResourceManager();
    if (!mgr->FindList(&vec, &key, 0)) {
        PrintError("No AnimLists found", "AnimList parsing error!");
        return false;
    }

    gEntryMap.DoNukeSubtree(gEntryMap.anchor.parent);
    gEntryMap.anchor.right = &gEntryMap.anchor;
    gEntryMap.anchor.left = &gEntryMap.anchor;
    gEntryMap.anchor.parent = 0;
    gEntryMap.anchor.color = 0;
    gEntryMap.size = 0;
    gAnimListLoaded = 0;

    {
        AnimParseContext ctx(&gEntryMap);
        ArgScriptParser* parser = CreateParser();
        if (parser) parser->p0();
        parser->p2();
        parser->p4(&ctx);
        parser->p10(5, 10);

        cCommandBase* cmd1 = (cCommandBase*)AllocCommand(0x10);
        if (cmd1) { cmd1->Construct(); *(const void**)cmd1 = gVtblPriorityCommand; }
        else cmd1 = 0;
        parser->p5(gNamePriority, cmd1);

        AppPropsFields* cmd2 = (AppPropsFields*)AllocCommand(0x34);
        if (cmd2) { cmd2->Construct(); *(const void**)cmd2 = gVtblAnimCommand; }
        else cmd2 = 0;
        parser->p5(gNameAnim, cmd2);

        AppPropsFields* cmd3 = (AppPropsFields*)AllocCommand(0x34);
        if (cmd3) { cmd3->Construct(); *(const void**)cmd3 = gVtblAnim2Command; }
        else cmd3 = 0;
        parser->p5(gNameAnim2, cmd3);

        for (ResKeyEntry* elem = vec.mpBegin; elem != vec.mpEnd; elem++) {
            int retries = 0;
            for (;;) {
                ResourceMan* rm = GetResourceManager();
                IResourceObj* res = (IResourceObj*)rm->GetResource(elem);
                ILoadedResource* handle = 0;
                if (!res || !res->Load(elem, (void**)&handle, 1, 6, 1, 0)) {
                    if (handle) handle->Release();
                    if (retries >= 5) {
                        PrintError("Failed to open an AnimList", "AnimList parsing error!");
                        break;
                    }
                    retries++;
                    int ms = 200;
                    ThreadSleep(&ms);
                    continue;
                }
                IFile* stream = handle->GetStream();
                int magic;
                ReadInt32(stream, &magic, 1, 0);
                stream->v10(0, 0);
                if (magic == 0x74736c61)
                    ReadAnimTable(stream);
                else
                    parser->p19(stream);
                handle->Close();
                handle->Release();
                break;
            }
        }

        parser->p3();
        parser->p1();
    }

    return false;
}
