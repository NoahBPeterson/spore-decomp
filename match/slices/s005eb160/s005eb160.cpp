// Slice s005eb160: cSPNameGenerator helpers (name-list loading from text records and random name
// generation).  Compiled without /EHsc (no EH frames in the original).
#include "types.h"
#include <string.h>
#include <new>

typedef unsigned int uint;
typedef unsigned short ushort;
#define VSLOT(obj, idx) ((*(void***)(obj))[idx])
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void* operator new(unsigned int, const char*, int, int, const char*, int);   // 0x00f473a0
void  operator delete[](void*);   // 0x00f47380
extern "C" __declspec(dllimport) int __cdecl tolower(int);

extern wchar_t gEmptyW[];               // 0x1667bac: shared empty-string buffer (wchar_t[2] / char[2] overlay)

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<wchar_t> (16 bytes with the 4-byte allocator) and char version
struct WStr {
    wchar_t* b;
    wchar_t* e;
    wchar_t* c;
    int      alloc;
    WStr() { b = e = gEmptyW; c = gEmptyW + 1; }
    ~WStr() { if (((((int)c - (int)b) & ~1) > 2) && b) operator delete[](b); }
    bool empty() const { return b == e; }
    // range initialisation: allocate (len + 1) chars unless the string is empty
    void Init(const wchar_t* sb, const wchar_t* se)
    {
        b = e = c = 0;
        uint n = (uint)(se - sb) + 1;
        if (n > 1) {
            b = (wchar_t*)operator new(n * 2, "Editor", 0, 0, ALLOC_FILE, 0xd1);
            e = b;
            c = b + n;
        } else {
            b = e = gEmptyW;
            c = gEmptyW + 1;
        }
        wchar_t* d = b;
        uint bytes = (uint)(se - sb) * 2;
        memcpy(d, sb, bytes);
        e = (wchar_t*)((char*)d + bytes);
        *e = 0;
    }
    void RangeInitialize(const wchar_t* p);                     // 00579a90
    void assign(const wchar_t* sb, const wchar_t* se);          // 00423650
    void Append(const wchar_t* sb, const wchar_t* se);          // 00429580
    void rtrim();                                               // 005541e0
    void make_lower();                                          // 005e8e80
    void CopyCtor(const WStr* o);                               // 0056e2d0
    void Fixup();                                               // 005e9320
    void clear() { if (b != e) { *b = 0; e = b; } }
    void ltrim(const wchar_t* set, const wchar_t* setEnd);
};
struct NStr {                                                   // eastl::string (char)
    char* b; char* e; char* c; int alloc;
    NStr() { b = e = (char*)gEmptyW; c = (char*)gEmptyW + 1; }
    ~NStr() { if (((int)c - (int)b) > 1 && b) operator delete[](b); }
};
const wchar_t* FindFirstNotOf(const wchar_t* b, const wchar_t* e, const wchar_t* sb, const wchar_t* se);   // 005497e0

void WStr::ltrim(const wchar_t* set, const wchar_t* setEnd)
{
    const wchar_t* p = FindFirstNotOf(b, e, set, setEnd);
    uint idx = (p == e) ? (uint)-1 : (uint)(p - b);
    uint len = (uint)(e - b);
    uint n = len < idx ? len : idx;
    wchar_t* q = b + n;
    if (b != q) {
        memmove(b, q, (uint)(((e - q)) * 2 + 2));
        e = e - n;
    }
}

WStr* WStrCopy(WStr* first, WStr* last, WStr* dest);             // 0084ab40 (eastl::copy)
struct WStrVec {
    WStr* b; WStr* e; WStr* c;
    void DoInsertValue(WStr* pos, const WStr* v);               // 00554c30
    void DoDestroyValues(WStr* first, WStr* last);              // 0084aad0
    void erase(WStr* first, WStr* last)
    {
        WStr* p = WStrCopy(last, e, first);
        DoDestroyValues(p, e);
        e = e - (last - first);
    }
    void clear() { erase(b, e); }
    void push_back(const WStr& s)
    {
        if (e < c) {
            WStr* p = e++;
            if (p) p->CopyCtor(&s);
        } else {
            DoInsertValue(e, &s);
        }
    }
};
struct NameList { WStrVec v; int pad[2]; };                     // stride 0x14

void  WStr_Format(WStr*, const wchar_t*, ...);                  // 0041e050
void  WStr_Format2(WStr*, const wchar_t*, ...);                 // 004e0850
const wchar_t* eastl_search(const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);   // 005e8ff0
void  ConvertToString16(WStr* dst, NStr* src);                  // 0093c6d0

struct RandomLCG {
    uint Uniform(uint n);   // 0x00a68fb0
};
extern RandomLCG gMathRandom;                                   // 01601760
extern WStr gDefaultName;                                       // 015f0a1c (begin) / 015f0a20 (end)

struct ResKey { uint instance, type, group; };
int  OpenRecordAsStream(const ResKey* key, void** stream);      // 00686490
void CloseRecord(int h);                                        // 006861d0
void GetPropertyAsKey(void* props, uint id, ResKey* out);       // 006a1250

struct ByteVec {
    char* b; char* e; char* c;
    ByteVec(uint n, const void* alloc);                         // 005e9f50
    ~ByteVec() { if (b && ((int*)b)[-1]) operator delete[](b); }
};

// rbtree<wstring,...> (set / map<wstring,int>); node value: key at +0x10, int at +0x20
struct StrNode { void* right; void* left; void* parent; int color; WStr key; int value; };
struct StrIter { StrNode* node; };
struct StrTree {
    StrIter* find(StrIter* out, const WStr& key);               // 005e96f0
    int* operator_index(const WStr& key);                       // 005eae50
};

// ---------------------------------------------------------------------------------------------
struct cSPNameGenerator {
    char pad0[0x3c0];
    StrTree mNamesUsed;                 // +0x3c0 (anchor at +0x3c4)
    char pad3c1[0x3f8 - 0x3c1];
    WStrVec mDuplicateSuffixes;         // +0x3f8

    void LoadStringList(const ResKey* key, WStrVec* out, bool lower);
    void LoadStringListEx(void* obj, uint id, WStrVec* out, bool lower);
    void LoadAll(void* obj, void* a1, int a2, int a3, int a4, void* a5, int a6);
    WStr* CreateRandomCompoundName(WStr* ret, void* data, NameList* lists, StrTree* excl, WStrVec* exclSub, int unused, bool allowDup);
    WStr* CreateRandomName(WStr* ret, WStrVec* names, bool allowDup);
    bool  LoadProperty(void* props, uint id, WStrVec* out, bool lower);
    void  LoadPropertyKey(void* props, uint id, WStrVec* out);
};

// @ 0x005eb160 : read a text record (UTF-8, line per entry), trim, optionally lower-case, append to out
void cSPNameGenerator::LoadStringList(const ResKey* keyIn, WStrVec* out, bool lower)
{
    ResKey key;
    key.instance = keyIn->instance;
    key.type = 0x24a0e52;
    key.group = 0x461227d;
    void* stream = 0;
    int h = OpenRecordAsStream(&key, &stream);
    if (h == -1)
        return;

    typedef int  (__thiscall* SizeFn)(void*);
    typedef uint (__thiscall* ReadFn)(void*, void*, uint);
    bool dummyAlloc;
    ByteVec buf(((SizeFn)VSLOT(stream, 7))(stream), &dummyAlloc);
    uint got = ((ReadFn)VSLOT(stream, 12))(stream, buf.b, (uint)(buf.e - buf.b));
    CloseRecord(h);

    char* p = buf.b;
    if (got >= 3 && (unsigned char)buf.b[0] == 0xef && (unsigned char)buf.b[1] == 0xbb && (unsigned char)buf.b[2] == 0xbf)
        p = buf.b + 3;

    if (p != buf.e) {
        wchar_t ws[3];
        ws[0] = 0x20; ws[1] = 9; ws[2] = 0;
        do {
            char* lineBegin = p;
            char* q = p;
            if (q != buf.e) {
                do {
                    if (*q == '\r' || *q == '\n')
                        break;
                    q++;
                } while (q != buf.e);
                p = q;
            }
            char* lineEnd = q;
            if (q != buf.e && (*q == '\r' || *q == '\n'))
                p = q + 1;

            NStr line;
            uint len = (uint)(lineEnd - lineBegin);
            uint n = len + 1;
            if (n > 1) {
                line.b = (char*)operator new(n, "Editor", 0, 0, ALLOC_FILE, 0xd1);
                line.e = line.b;
                line.c = line.b + n;
            }
            memcpy(line.b, lineBegin, len);
            line.e = line.b + len;
            *line.e = 0;

            WStr w;
            w.b = w.e = w.c = 0;
            ConvertToString16(&w, &line);

            const wchar_t* wsEnd = ws;
            while (*wsEnd) wsEnd++;
            w.ltrim(ws, wsEnd);
            w.rtrim();
            if (!w.empty()) {
                if (lower)
                    w.make_lower();
                out->push_back(w);
            }
        } while (p != buf.e);
    }
}

// @ 0x005eb440 : load the three prefix/middle/suffix lists of one name kind and its flags
struct NameFlagsObj { char pad[0x24]; uint flags; };
bool CheckFlag(void* a1, uint id, int a6);                      // 005e8e20
void ReserveLists(void* a1, int a2, int* count, void** data);   // 006a0ae0 (cdecl)

void cSPNameGenerator::LoadAll(void* obj, void* a1, int a2, int a3, int a4, void* a5, int a6)
{
    void* data[3]   = { 0, 0, 0 };
    int   counts[3] = { 0, 0, 0 };
    ReserveLists(a1, a2, &counts[0], &data[0]);
    ReserveLists(a1, a3, &counts[1], &data[1]);
    ReserveLists(a1, a4, &counts[2], &data[2]);
    if (CheckFlag(a1, 0x6664a3f, a6))
        ((NameFlagsObj*)obj)->flags |= 1;
    if (CheckFlag(a1, 0x6664a52, a6))
        ((NameFlagsObj*)obj)->flags |= 2;
    char* dst = (char*)a5;
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < counts[k]; i++)
            LoadStringList((const ResKey*)((char*)data[k] + i * 12), (WStrVec*)dst, false);
        dst += 0x14;
    }
}

// @ 0x005eb540 : SP::cSPNameGenerator::CreateRandomCompoundName
WStr* cSPNameGenerator::CreateRandomCompoundName(WStr* ret, void* data, NameList* lists, StrTree* excl,
                                                 WStrVec* exclSub, int unused, bool allowDup)
{
    WStr name;
    bool done = false;
    int tries = 0;
    for (;;) {
        tries++;
        if (tries > 10)
            break;
        name.clear();
        {
            WStr parts[3];
            NameList* L = lists;
            for (int i = 0; i < 3; i++, L++) {
                if (L->v.b == L->v.e) {
                    if (i < 2) {
                        ret->b = ret->e = ret->c = 0;
                        ret->Init(gDefaultName.b, gDefaultName.e);
                        return ret;
                    }
                } else {
                    uint idx = gMathRandom.Uniform((uint)(L->v.e - L->v.b));
                    WStr* s = &L->v.b[idx];
                    if (s != &parts[i])
                        parts[i].assign(s->b, s->e);
                }
            }
            uint fl = ((NameFlagsObj*)data)->flags;
            const wchar_t* fmt;
            if (fl & 1) fmt = (fl & 2) ? L"%s %s %s" : L"%s %s%s";
            else        fmt = (fl & 2) ? L"%s%s %s"  : L"%s%s%s";
            WStr_Format(&name, fmt, parts[0].b, parts[1].b, parts[2].b);

            WStr lowerName;
            lowerName.Init(name.b, name.e);
            for (wchar_t* q = lowerName.b; q < lowerName.e; q++) {
                ushort ch = *q;
                if (ch <= 0xff)
                    ch = (ushort)tolower(ch & 0xff);
                *q = ch;
            }

            StrIter it;
            if (excl->find(&it, lowerName)->node == (StrNode*)((char*)excl + 4)) {
                bool rejected = false;
                for (WStr* s = exclSub->b; s != exclSub->e; s++) {
                    uint n = (uint)(s->e - s->b);
                    if (n <= (uint)(lowerName.e - lowerName.b)) {
                        const wchar_t* p = eastl_search(lowerName.b, lowerName.e, s->b, s->b + n);
                        if ((p != lowerName.e || n == 0) && (int)(p - lowerName.b) != -1) {
                            rejected = true;
                            break;
                        }
                    }
                }
                if (!rejected) {
                    if (allowDup) {
                        done = true;
                    } else {
                        StrIter it2;
                        if (mNamesUsed.find(&it2, name)->node == (StrNode*)((char*)this + 0x3c4))
                            done = true;
                    }
                }
            }
        }
        if (done)
            break;
    }
    if (done) {
        StrIter it;
        mNamesUsed.find(&it, name);
        if (it.node == (StrNode*)((char*)this + 0x3c4)) {
            *mNamesUsed.operator_index(name) = 1;
        } else if (allowDup) {
            int n = it.node->value;
            if (n - 1 < (int)(mDuplicateSuffixes.e - mDuplicateSuffixes.b)) {
                it.node->value = n + 1;
                WStr* s = &mDuplicateSuffixes.b[n - 1];
                name.Append(s->b, s->e);
            } else {
                it.node->value = n + 1;
                WStr_Format2(&name, L"%c%d", 0x2d, n + 1);
            }
        }
    }
    ret->b = ret->e = ret->c = 0;
    const wchar_t* z = name.b;
    while (*z) z++;
    ret->Init(name.b, z);
    return ret;
}

// @ 0x005eba70 : (re)load one property's string list: clears out, then reads the key list
void cSPNameGenerator::LoadPropertyKey(void* props, uint id, WStrVec* out)
{
    typedef bool (__thiscall* HasFn)(void*, uint);
    if (!((HasFn)VSLOT(props, 7))(props, id))
        return;
    out->clear();
    ResKey key = { 0, 0, 0 };
    GetPropertyAsKey(props, id, &key);
    LoadStringList(&key, out, false);
}

// @ 0x005ebb00 : SP::cSPNameGenerator::CreateRandomName
WStr* cSPNameGenerator::CreateRandomName(WStr* ret, WStrVec* names, bool allowDup)
{
    if (names->b == names->e) {
        ret->b = ret->e = ret->c = 0;
        ret->RangeInitialize(gDefaultName.b);
        return ret;
    }
    int tries = 0;
    WStr* elem;
    StrIter it;
    for (;;) {
        uint idx = gMathRandom.Uniform((uint)(names->e - names->b));
        elem = &names->b[idx];
        mNamesUsed.find(&it, *elem);
        if (it.node == (StrNode*)((char*)this + 0x3c4)) {
            *mNamesUsed.operator_index(*elem) = 1;
            WStr tmp;
            tmp.b = tmp.e = tmp.c = 0;
            tmp.RangeInitialize(elem->b);
            tmp.Fixup();
            ret->CopyCtor(&tmp);
            return ret;
        }
        if (allowDup)
            break;
        tries++;
        if (tries > 100) {
            WStr tmp;
            tmp.b = tmp.e = tmp.c = 0;
            tmp.RangeInitialize(elem->b);
            tmp.Fixup();
            ret->CopyCtor(&tmp);
            return ret;
        }
    }
    WStr tmp;
    tmp.CopyCtor(elem);
    int n = it.node->value;
    if (n - 1 < (int)(mDuplicateSuffixes.e - mDuplicateSuffixes.b)) {
        it.node->value = n + 1;
        WStr* s = &mDuplicateSuffixes.b[n - 1];
        tmp.Append(s->b, s->e);
    } else {
        it.node->value = n + 1;
        WStr_Format2(&tmp, L"%c%d", 0x2d, n + 1);
    }
    tmp.Fixup();
    ret->b = ret->e = ret->c = 0;
    ret->RangeInitialize(tmp.b);
    return ret;
}

// @ 0x005ebe90 : read a property (single resource key or an array of keys) into out
bool cSPNameGenerator::LoadProperty(void* props, uint id, WStrVec* out, bool lower)
{
    struct Prop { char* data; int pad; int count; int pad2; ushort flags; ushort single; };
    typedef Prop* (__thiscall* GetFn)(void*, uint);
    Prop* p = ((GetFn)VSLOT(props, 10))(props, id);
    ushort mode = p->flags & 0x30;
    int count;
    char* first;
    if (mode != 0) {
        count = p->count;
        if (count <= 0)
            return false;
    } else {
        if (p->single == 0)
            return false;
        count = 1;
    }
    if (mode != 0)
        first = p->data;
    else
        first = p->single ? (char*)p : 0;
    if (count > 0) {
        do {
            LoadStringList((const ResKey*)first, out, lower);
            first += 0xc;
            count--;
        } while (count != 0);
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// eastl::map<pair<ushort,ushort>, V> helpers (node = 0x3c bytes: header 0x10, key 4, value 0x28)
struct U16Pair { ushort first, second; };
struct MapVal { char data[0x28]; MapVal(const MapVal&); };       // 005ea8f0
struct MapValueType {
    U16Pair key; MapVal val;
    MapValueType(const MapValueType& o) : key(o.key), val(o.val) {}
};
struct MapNode { MapNode* right; MapNode* left; MapNode* parent; int color; MapValueType value; };
struct MapIter { MapNode* node; MapIter() {} MapIter(MapNode* n) : node(n) {} };
struct InsertResult { MapNode* node; bool inserted; };
struct UniqueKeysTag {};   // eastl::true_type (has_unique_keys)

void RBTreeInsert(MapNode* node, MapNode* parent, MapNode* anchor, int bInsertOnRight);   // 009216a0
MapNode* RBTreeDecrement(MapNode*);                                            // 009215c0
MapNode* RBTreeIncrement(MapNode*);                                            // 00921580

static inline bool KeyLess(const U16Pair& a, const U16Pair& b)
{
    return a.first < b.first || (!(b.first < a.first) && a.second < b.second);
}

struct U16Map {
    char pad0[4];
    MapNode* anchorRight;               // +4  (anchor node starts here)
    MapNode* anchorLeft;                // +8
    MapNode* anchorParent;              // +0xc
    int anchorColor;                    // +0x10
    uint mnSize;                        // +0x14
    MapNode* anchor() { return (MapNode*)((char*)this + 4); }
    bool KeyLessOOL(const U16Pair& a, const U16Pair& b);                       // 005e90f0

    MapNode** DoInsertValueImpl(MapNode** ret, MapNode* parent, const MapValueType* v, bool bForceToLeft);   // 005ebd10
    InsertResult* DoInsertValue(InsertResult* ret, const MapValueType* v, UniqueKeysTag);          // 005ebdb0
    MapNode** insert(MapNode** ret, MapIter pos, const MapValueType* v, UniqueKeysTag);           // 005ebf10
};

// @ 0x005ebd10
MapNode** U16Map::DoInsertValueImpl(MapNode** ret, MapNode* parent, const MapValueType* v, bool bForceToLeft)
{
    int bInsertOnRight = (!bForceToLeft && parent != anchor() && !KeyLess(v->key, parent->value.key)) ? 1 : 0;
    MapNode* n = (MapNode*)operator new(0x3c, "Editor", 0, 0, ALLOC_FILE, 0xd1);
    new (&n->value) MapValueType(*v);
    RBTreeInsert(n, parent, anchor(), bInsertOnRight);
    mnSize++;
    *ret = n;
    return ret;
}

// @ 0x005ebdb0
InsertResult* U16Map::DoInsertValue(InsertResult* ret, const MapValueType* v, UniqueKeysTag)
{
    MapNode* pCurrent = anchorParent;
    MapNode* pLowerBound = anchor();
    bool bValueLessThanNode = true;
    while (pCurrent) {
        bValueLessThanNode = KeyLess(v->key, pCurrent->value.key);
        pLowerBound = pCurrent;
        pCurrent = bValueLessThanNode ? pCurrent->left : pCurrent->right;
    }
    MapNode* pParent = pLowerBound;
    if (bValueLessThanNode) {
        if (pLowerBound != anchorLeft)
            pLowerBound = RBTreeDecrement(pLowerBound);
        else {
            MapNode* n;
            DoInsertValueImpl(&n, pLowerBound, v, false);
            ret->node = n;
            ret->inserted = true;
            return ret;
        }
    }
    if (KeyLess(pLowerBound->value.key, v->key)) {
        MapNode* n;
        DoInsertValueImpl(&n, pParent, v, false);
        ret->node = n;
        ret->inserted = true;
        return ret;
    }
    ret->node = pLowerBound;
    ret->inserted = false;
    return ret;
}

// @ 0x005ebf10 : hinted insert
MapNode** U16Map::insert(MapNode** ret, MapIter position, const MapValueType* v, UniqueKeysTag)
{
    if (position.node != anchorRight && position.node != anchor()) {
        MapIter itNext(position);
        itNext.node = RBTreeIncrement(itNext.node);
        const bool bPositionLessThanValue = KeyLess(position.node->value.key, v->key);
        if (bPositionLessThanValue) {
            const bool bValueLessThanNext = KeyLessOOL(v->key, itNext.node->value.key);
            if (bValueLessThanNext) {
                if (position.node->right)
                    return DoInsertValueImpl(ret, itNext.node, v, true);
                return DoInsertValueImpl(ret, position.node, v, false);
            }
        }
        InsertResult r;
        DoInsertValue(&r, v, UniqueKeysTag());
        *ret = r.node;
        return ret;
    }
    if (mnSize && KeyLess(anchorRight->value.key, v->key))
        return DoInsertValueImpl(ret, anchorRight, v, false);
    InsertResult r;
    DoInsertValue(&r, v, UniqueKeysTag());
    *ret = r.node;
    return ret;
}
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, int, char*, int); // 0x00f473a0
    void operator delete[](void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct RandomLCG {
    void Uniform(unsigned int); // 0x00a68fb0
};
}
