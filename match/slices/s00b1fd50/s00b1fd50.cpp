// Slice s00b1fd50: game-data / noun-manager helpers around the artillery projectile and
// EASTL string (grow/append/resize), feedback rbtree/hashtable lookups, debug UI.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int  uint;
typedef unsigned char uchar;
typedef char          va_list;

// ------------------------------------------------------------------ allocator / runtime
#define ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void* __cdecl opnew(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void  __cdecl opdel(void* p);                                                                     // 0x00f47380
extern "C" void* __cdecl memset(void*, int, unsigned);
extern "C" void* __cdecl memmove(void*, const void*, unsigned);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
#pragma intrinsic(memset, memmove, memcpy)

#define SPORE_NEW(n) opnew((n), "Simulator", 0, 0, ALLOC_FILE, 0xd1)

extern char gEmptyChar;  // 0x01667bac
extern char gSigInfo;    // 0x015685a8

// ------------------------------------------------------------------ polymorphic game-data object
struct cGameData;
struct cGameData {
    virtual int  AddRef();                 // +0x00
    virtual int  Release();                // +0x04
    virtual void gv08();                   // +0x08
    virtual int  Match(unsigned id);       // +0x0c
    virtual void gv10(); virtual void gv14(); virtual void gv18();
    virtual cGameData* gv1c();             // +0x1c
    virtual cGameData* gv20();             // +0x20
    virtual void gv24(); virtual void gv28();
    virtual bool gv2c();                   // +0x2c
    virtual void gv30(); virtual void gv34(); virtual void gv38(); virtual void gv3c();
    virtual void gv40();
    virtual void gv44();                   // +0x44
    virtual void gv48(); virtual void gv4c(); virtual void gv50(); virtual void gv54();
    virtual void gv58(); virtual void gv5c(); virtual void gv60(); virtual void gv64();   // gv64 = +0x64
    virtual void gv68(); virtual void gv6c(); virtual void gv70(); virtual void gv74();
    virtual void gv78(); virtual void gv7c(); virtual void gv80(); virtual void gv84();
    virtual void gv88(); virtual void gv8c(); virtual void gv90(); virtual void gv94();
    virtual void gv98(); virtual void gv9c(); virtual void gva0();
    virtual void gva4();                   // +0xa4
    char      pad_b58[0xb58 - 4];
    unsigned  mFlags;                      // +0xb58
};

struct IRefObject {
    virtual int   AddRef();                // +0x00
    virtual int   Release();               // +0x04
    virtual void  gv08();                  // +0x08
    virtual int   Match(unsigned id);      // +0x0c
};

struct ARCData {
    cGameData* p;
    ARCData(cGameData* q) : p(q) { if (p) p->AddRef(); }
    ARCData(const ARCData& o) : p(o.p) { if (p) p->AddRef(); }
    ~ARCData() { if (p) p->Release(); }
    ARCData& operator=(cGameData* np) {
        cGameData* old = p;
        if (np != old) { if (np) np->AddRef(); p = np; if (old) old->Release(); }
        return *this;
    }
};

struct NounMgr {
    char     pad54[0x54];
    ARCData  mAvatar;                      // +0x54
    void SetAvatar(cGameData* p);          // 0x00b1fd50
};

// @ 0x00b1fd50
void __thiscall NounMgr::SetAvatar(cGameData* p)
{
    cGameData* old = mAvatar.p;
    if (old) old->mFlags &= 0xfffffdff;
    if (p) p->mFlags |= 0x200;
    mAvatar = p;
}

// @ 0x00b1fe40
int __cdecl ClassifyA(IRefObject* p)
{
    if (p) {
        if (p->Match(0x4f396a66)) return 0;
        if (p->Match(0xee9b2232)) return 1;
        if (p->Match(0x901f1362)) return 2;
        if (p->Match(0x1805e75))  return 3;
    }
    return -1;
}

// @ 0x00b1feb0
int __stdcall ClassifyB(IRefObject* p)
{
    if (!p) return 0;
    if (p->Match(0x901f1362)) return 4;
    if (p->Match(0x4f396a66)) return 2;
    int a = p->Match(0xd0036e08);
    int b = p->Match(0x1b92b27);
    if (a || b) return 1;
    return 0;
}

// ------------------------------------------------------------------ byte string (begin/end/capacity)
struct ByteString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    char* mpField0c;    // +0x0c
    char* mpBase;       // +0x10

    void  __thiscall allocate(unsigned n);            // 0xb1ffd0
    void  __thiscall changeCapacity(unsigned n);      // 0xb230b0
    ByteString& __thiscall append(unsigned n, unsigned char c);     // 0xb1ff30
    void  __thiscall resize(unsigned n);              // 0xb20610
    void  Assign(const char* s);                      // 0x006a4380
    void  Assign(const char* b, const char* e);       // 0x00454cb0
};

// @ 0x00b1ffd0
void __thiscall ByteString::allocate(unsigned n)
{
    if (n > 1) {
        char* p = (char*)SPORE_NEW(n);
        mpBegin = p;
        mpEnd   = p;
        mpCapacity = p + n;
    } else {
        mpBegin = &gEmptyChar;
        mpEnd   = &gEmptyChar;
        mpCapacity = &gEmptyChar + 1;
    }
}

// @ 0x00b230b0
void __thiscall ByteString::changeCapacity(unsigned n)
{
    if (n == 0xffffffff) return;
    unsigned size = (unsigned)(mpEnd - mpBegin);
    if (n <= size) return;
    char* p = (char*)SPORE_NEW(n);
    memcpy(p, mpBegin, size);
    p[size] = 0;
    unsigned oldCap = (unsigned)(mpCapacity - mpBegin);
    if (oldCap > 1 && mpBegin && mpBegin != mpBase) opdel(mpBegin);
    mpBegin = p;
    mpEnd = p + size;
    mpCapacity = p + n;
}

// @ 0x00b1ff30
ByteString& __thiscall ByteString::append(unsigned n, unsigned char c)
{
    unsigned size = (unsigned)(mpEnd - mpBegin);
    unsigned cap  = (unsigned)(mpCapacity - mpBegin);
    unsigned newSize = size + n;
    if (newSize > cap - 1) {
        unsigned growth = (cap - 1) <= 8 ? 8 : (cap - 1) * 2;
        unsigned chosen = growth < newSize ? newSize : growth;
        unsigned chosen2 = chosen < size ? size : chosen;
        if (chosen2 + 1 > cap) changeCapacity(chosen2 + 1);
    }
    if (n != 0) {
        memset(mpEnd + 1, c, n - 1);
        *mpEnd = c;
        mpEnd = mpEnd + n;
        *mpEnd = 0;
    }
    return *this;
}

// @ 0x00b20610
void __thiscall ByteString::resize(unsigned n)
{
    unsigned size = (unsigned)(mpEnd - mpBegin);
    if (n < size) {
        char* p = mpBegin + n;
        if (p != mpEnd) {
            memmove(p, mpEnd, 1);
            mpEnd += p - mpEnd;
        }
    } else if (size < n) {
        append(n - size, 0);
    }
}

// ------------------------------------------------------------------ rbtree / hashtable plumbing
struct RBNode {
    RBNode* mpNodeRight;  // +0
    RBNode* mpNodeLeft;   // +4
    RBNode* mpNodeParent; // +8
    char    mColor;       // +0xc
};
extern RBNode* __cdecl RBTreeIncrement(RBNode* p);   // 0x00921580
extern void    __cdecl RBTreeNuke(RBNode* p);        // 0x009a9600
extern void    __cdecl FUN_00a21bf0(void* p);        // 0x00a21bf0

struct RBTreeHeader {
    int     mPad;
    RBNode  mAnchor;   // +4
    uint    mnSize;    // +0x0c
    void** Find(void** out, const void* key);  // 0x00e5c780, returns `out`
};

// ------------------------------------------------------------------ serialization
extern void  __cdecl WriteUint32(void* stream, const void* src, int count, int endian);  // 0x0093aa70
struct cVarListSerializer {
    char data[0xa14];
    cVarListSerializer(void* obj, void* info, unsigned sig);  // 0x00692f90
    void Serialize(void* ser);                                 // 0x00692900
};
struct ISerializer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual void* GetStream();          // +0x18
    virtual void* Slot1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual void SerializeObj(cGameData* o);  // +0x2c
};

// ------------------------------------------------------------------ complex game-data body
struct GameDataBig {
    char     pad00[0x58];
    cGameData** mVecBegin;   // +0x58
    cGameData** mVecEnd;     // +0x5c
    cGameData** mVecCap;     // +0x60
    char     pad64[0x10];
    RBNode   mList;          // +0x74
    RBNode   mList2;         // +0x80
    char     pad88[0x0c];
    RBTreeHeader mFeedback;  // +0x94  (anchor +0x98)
    char     padA4[0x30];
    RBTreeHeader mFeedback2; // +0xd4

    void Write(ISerializer* ser);                    // 0xb20280
    void RemoveVecItem(cGameData* p);                // 0xb203e0
    int  CountList(cGameData* p);                    // 0xb20470
    cGameData* FindList(unsigned key);               // 0xb204d0
    void MarkFeedback(cGameData* p);                 // 0xb201a0
};

// @ 0x00b20280
void __thiscall GameDataBig::Write(ISerializer* ser)
{
    int n = -1;
    RBNode* it = &mList;
    do { it = it->mpNodeRight; n++; } while (it != &mList);

    RBNode* first = mList.mpNodeRight;
    cGameData* last = (cGameData*)(first ? (char*)first - 0xc : 0);

    void* stream = ser->GetStream();
    WriteUint32(stream, &n, 1, 0);

    cGameData* node = last;
    while (node != (cGameData*)((char*)&mList - 0xc)) {
        ser->SerializeObj(node);
        cGameData* nx = node->gv20();
        node = nx ? (cGameData*)((char*)nx - 0xc) : 0;
    }

    for (uint i = 0; i < (uint)(mVecEnd - mVecBegin); ) {
        if (mVecBegin[i]->gv2c()) {
            cGameData* old = mVecBegin[i];
            cGameData* src = mVecEnd[-1];
            if (src != old) {
                if (src) src->AddRef();
                mVecBegin[i] = src;
                if (old) old->Release();
            }
            mVecEnd--;
            if (*mVecEnd) (*mVecEnd)->Release();
        } else {
            i++;
        }
    }

    cVarListSerializer ser2((char*)this - 4, &gSigInfo, 0x1a80d26);
    ser2.Serialize(ser);
}

// @ 0x00b203e0
void __thiscall GameDataBig::RemoveVecItem(cGameData* p)
{
    if (!p) return;
    cGameData** vecBegin = *(cGameData***)((char*)this + 0x5c);
    cGameData** vecEnd = *(cGameData***)((char*)this + 0x60);
    int n = (int)(vecEnd - vecBegin);
    if (n <= 0) return;
    for (int i = 0; i < n; i++) {
        if (vecBegin[i] == p) {
            p->mFlags &= 0xfffffeff;
            cGameData* old = vecBegin[i];
            cGameData* src = vecEnd[-1];
            if (src != old) {
                if (src) src->AddRef();
                vecBegin[i] = src;
                if (old) old->Release();
            }
            vecEnd--;
            *(cGameData***)((char*)this + 0x60) = vecEnd;
            if (*vecEnd) (*vecEnd)->Release();
            return;
        }
    }
}

// @ 0x00b20470
int __thiscall GameDataBig::CountList(cGameData* p)
{
    int n = 0;
    char* head = *(char**)((char*)this + 0x78);
    RBNode* it = head ? (RBNode*)(head - 0xc) : (RBNode*)0;
    RBNode* last = (RBNode*)((char*)this + 0x6c);
    while (it != last) {
        if ((cGameData*)((cGameData*)it)->gv20() == p) n++;
        char* nx = *(char**)((char*)it + 0xc);
        it = nx ? (RBNode*)(nx - 0xc) : (RBNode*)0;
    }
    return n;
}

// @ 0x00b204d0
cGameData* __thiscall GameDataBig::FindList(unsigned key)
{
    char* head = *(char**)((char*)this + 0x78);
    char* it = head ? head - 0xc : 0;
    char* last = (char*)this + 0x6c;
    while (it != last) {
        if (*(unsigned*)(it + 0x24) == key) return (cGameData*)it;
        char* nx = *(char**)(it + 0xc);
        it = nx ? nx - 0xc : 0;
    }
    return 0;
}

// @ 0x00b201a0
void __thiscall GameDataBig::MarkFeedback(cGameData* p)
{
    if (!p) return;
    unsigned id = (unsigned)p->gv20();
    void* found;
    RBNode* node = (RBNode*)*mFeedback.Find(&found, &id);
    if (node != (RBNode*)&mFeedback.mAnchor) {
        *(char*)(*(int*)((char*)node + 0x14)) = 1;
    }
    RBNode* it = mFeedback.mAnchor.mpNodeLeft;
    RBNode* end = (RBNode*)&mFeedback.mAnchor;
    while (it != end) {
        char* flag = *(char**)((char*)it + 0x14);
        if (*flag == 0) {
            if (p->Match(*(unsigned*)((char*)it + 0x10))) *flag = 1;
        }
        it = RBTreeIncrement(it);
    }
}

// ------------------------------------------------------------------ list iteration
struct ListNode2 { ListNode2* next; ListNode2* prev; };
struct ListObj {
    virtual void n0(); virtual void n1(); virtual void n2(); virtual void n3();
    virtual void n4(); virtual void n5(); virtual void n6();
    virtual void n1c(void* arg);       // +0x1c
    char pad08[8];
    ListNode2 node;                    // +0x0c
};

// @ 0x00b20230
bool __cdecl IterateList(void* arg, ListNode2* anchor)
{
    ListObj* it = anchor->next ? (ListObj*)((char*)anchor->next - 0xc) : 0;
    ListObj* last = (ListObj*)((char*)anchor - 0xc);
    while (it != last) {
        it->n1c(arg);
        it = it->node.next ? (ListObj*)((char*)it->node.next - 0xc) : 0;
    }
    return true;
}

// ------------------------------------------------------------------ artillery dtor/factory
struct SerObj { void Set(); void Set2(); void DtorBody(); };
struct GameDataDtor { void DtorBody(); };
extern void __cdecl FUN_00c432e0();               // 0x00c432e0
extern void* gArtilleryVtbl;                      // 0x0145dca8

struct ArtilleryBase {
    virtual void b0();
    char pad[0x524 - 4];
    cGameData* m524;      // +0x524
    char pad528[0x534 - 0x528];
    cGameData* m534;      // +0x534
    char pad538[4];
    cGameData* m53c;      // +0x53c
    void Dtor();          // 0xb20120
};

// @ 0x00b20120
void __thiscall ArtilleryBase::Dtor()
{
    if (m53c) m53c->gv64();
    if (m534) m534->gv08();
    if (m524) m524->gv64();
    *(void**)((char*)this + 0x504) = &gArtilleryVtbl;
    ((SerObj*)((char*)this + 0x34))->Set2();
    ((GameDataDtor*)this)->DtorBody();
}

// @ 0x00b205a0
struct SmallObj {
    char d[0x14];
    cGameData* m14;   // +0x14
    int  m18;         // +0x18
};
SmallObj* __stdcall AllocSmallObj(SmallObj* src)
{
    SmallObj* p = (SmallObj*)SPORE_NEW(0x20);
    if (p) {
        memcpy(p->d, src->d, 0x14);
        p->m14 = src->m14;
        if (p->m14) p->m14->AddRef();
    }
    p->m18 = 0;
    return p;
}

// @ 0x00b20660
struct ArtCtorObj;
struct cArtilleryProjectile {
    virtual void a0(); virtual void a4();
    char pad[0x540 - 8];
    static cArtilleryProjectile* Create();   // 0xb20660
};
struct ArtCtorObj { void Ctor(); };           // 0x00cb6ed0
extern void* gArtVtbl0; extern void* gArtVtbl1; extern void* gArtVtbl2;
extern void* gArtVtbl3; extern void* gArtVtbl4;

// @ 0x00b20660
cArtilleryProjectile* __cdecl cArtilleryProjectile::Create()
{
    cArtilleryProjectile* p = (cArtilleryProjectile*)opnew(0x540, "Simulator/cSpear", 0, 0, 0, 0);
    if (p) {
        ((ArtCtorObj*)p)->Ctor();
        *(void**)((char*)p + 0x00) = &gArtVtbl0;
        *(void**)((char*)p + 0x04) = &gArtVtbl1;
        *(void**)((char*)p + 0x34) = &gArtVtbl2;
        *(void**)((char*)p + 0x108) = &gArtVtbl3;
        *(void**)((char*)p + 0x504) = &gArtVtbl4;
        *(void**)((char*)p + 0x53c) = 0;
        return p;
    }
    return 0;
}

// ------------------------------------------------------------------ manager flush
struct FlushMgr {
    char pad[0xb4];
    RBNode mAnchor;    // +0xb4
    RBNode* mRoot;     // +0xc0
    char   mFlag;      // +0xc4
    void*  mC8;        // +0xc8
    void Flush();      // 0xb206d0
};

// @ 0x00b206d0
void __thiscall FlushMgr::Flush()
{
    RBNode* end = (RBNode*)((char*)this + 0xb8);
    for (RBNode* it = *(RBNode**)((char*)this + 0xbc); it != end; it = RBTreeIncrement(it)) {
        void* p = *(void**)((char*)it + 0x14);
        if (p) opdel(p);
    }
    RBNode* p = *(RBNode**)((char*)this + 0xc0);
    while (p) {
        RBTreeNuke(*(RBNode**)p);
        RBNode* next = *(RBNode**)((char*)p + 4);
        opdel(p);
        p = next;
    }
    char* base = (char*)this + 0xb4;
    *(RBNode**)(base + 8) = (RBNode*)(base + 4);
    *(uint*)(base + 0xc) = 0;
    *(char*)(base + 0x10) = 0;
    *(void**)(base + 0x14) = 0;
    *(RBNode**)(base + 4) = (RBNode*)(base + 4);
}

// ------------------------------------------------------------------ feedback queries
struct FeedbackMgr {
    char pad[0xd0];
    RBTreeHeader mTree;   // +0xd0
    void* GetFeedback(unsigned id);   // 0xb20750
    int   ClassifyById(unsigned id);  // 0xb20790
};

// @ 0x00b20750
void* __thiscall FeedbackMgr::GetFeedback(unsigned id)
{
    void* found;
    RBNode* node = (RBNode*)*mTree.Find(&found, &id);
    if (node != (RBNode*)&mTree.mAnchor) return *(void**)((char*)node + 0x14);
    return 0;
}

extern cGameData* __cdecl StarManager();               // 0x00b3d2a0
struct StarMgrObj { cGameData* GetEmpireByID(unsigned id); };  // 0x00ba9370 (thiscall)

// @ 0x00b20790
int __thiscall FeedbackMgr::ClassifyById(unsigned id)
{
    void* found;
    RBNode* node = (RBNode*)*mTree.Find(&found, &id);
    if (node != (RBNode*)&mTree.mAnchor) {
        void* v = *(void**)((char*)node + 0x14);
        if (v) return ClassifyB((IRefObject*)v);
    }
    unsigned r = (unsigned)((StarMgrObj*)StarManager())->GetEmpireByID(id);
    return r ? 5 : 0;
}

// ------------------------------------------------------------------ hashtable find
struct HashTable {
    char pad0[4];
    void** mBuckets;   // +0x04
    uint   mCount;     // +0x08
    void Find(void** out, uint* key);  // 0xb207f0
};

// @ 0x00b207f0
void __thiscall HashTable::Find(void** out, uint* key)
{
    uint u = *key % mCount;
    void** p = *(void***)((char*)mBuckets + u * 4);
    void** bucket = (void**)((char*)mBuckets + u * 4);
    if (p) {
        do {
            if (key[0] == *(uint*)p && key[1] == *(uint*)((char*)p + 4)) goto done;
            p = (void**)*(void**)((char*)p + 0x18);
        } while (p);
    }
    bucket = (void**)((char*)mBuckets + mCount * 4);
    p = (void**)*bucket;
done:
    out[0] = p;
    out[1] = bucket;
}

// ------------------------------------------------------------------ map<string,int>::find
extern int  __cdecl eastlCompare(const char*, const char*, unsigned n);  // 0x005f7870
extern bool __cdecl StringLess(const void*, const void*);               // 0x00812210

struct MapStrFind {
    int mPad; RBNode mAnchor; uint mSize;
    void Find(void** out, void* key);   // 0xb20930
};

// @ 0x00b20930
void __thiscall MapStrFind::Find(void** out, void* key)
{
    char* node = (char*)*(void**)((char*)this + 0xc);
    char* lower = (char*)this + 4;
    char* result = lower;
    const char* kb = *(const char**)key;
    int kLen = (int)(*(char**)((char*)key + 4) - kb);
    while (node) {
        const char* nb = *(const char**)(node + 0x10);
        int nLen = (int)(*(char**)(node + 0x14) - nb);
        int minLen = nLen < kLen ? nLen : kLen;
        int r = eastlCompare(nb, kb, (unsigned)minLen);
        if (!r) {
            if (nLen < kLen) r = -1;
            else r = nLen > kLen ? 1 : 0;
        }
        if (r < 0) {
            node = *(char**)node;
        } else {
            result = node;
            node = *(char**)(node + 4);
        }
    }
    if (result != lower && !StringLess(key, result + 0x10)) {
        *out = result;
        return;
    }
    *out = lower;
}

// ------------------------------------------------------------------ string construction
extern void __cdecl RangeInitialize(void* self, unsigned n);           // 0x00475ab0
extern void __cdecl DoInsertValueC(void* dst, const void* src, unsigned n);  // 0x011e0744
struct StringBase { void RangeInitialize(unsigned n); };   // 0x00475ab0 (thiscall)

struct String4 {
    void* ctor(void* a, void* b);   // 0xb209f0
};
// @ 0x00b209f0
void* __thiscall String4::ctor(void* a, void* b)
{
    void* self = this;
    *(void**)self = *(void**)a;
    *(void**)((char*)self + 4) = 0;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    int iVar1 = *(int*)((char*)b + 4);
    const char* src = *(const char**)b;
    unsigned size = (unsigned)(iVar1 - (int)src);
    ((StringBase*)((char*)self + 4))->RangeInitialize(size + 1);
    char* dst = *(char**)((char*)self + 4);
    DoInsertValueC(dst, src, size);
    char* end = dst + size;
    *(char**)((char*)self + 8) = end;
    *end = 0;
    return self;
}

// @ 0x00b20a50
struct NodeDtor { void D(); };   // 0x00a21bf0
void __stdcall FreeBucketNodes(void** buckets, uint n)
{
    for (uint i = 0; i < n; i++) {
        char* p = (char*)buckets[i];
        if (p) {
            do {
                char* cur = p;
                p = *(char**)(cur + 0x18);
                ((NodeDtor*)(cur + 8))->D();
                opdel(cur);
            } while (p);
        }
        buckets[i] = 0;
    }
}

// ------------------------------------------------------------------ format append
extern int __cdecl Vsnprintf8(char* buf, unsigned n, const char* fmt, va_list args);  // 0x00938400

extern void __cdecl FormatResize(void* self, unsigned n);  // 0xb20610
#define VA_START(ap, v) ((ap) = (va_list)((char*)&(v) + sizeof(v)))

// @ 0x00b20aa0
void* __cdecl FormatAppend(void* self, const char* fmt, ...)
{
    va_list args;
    int base = *(int*)((char*)self + 4);
    int iVar3 = base - *(int*)self;
    int cap = *(int*)self == (int)&gEmptyChar ? 0
              : *(int*)((char*)self + 8) - base;
    VA_START(args, fmt);
    int n = Vsnprintf8((char*)base, (unsigned)cap, fmt, args);
    if (n < *(int*)((char*)self + 8) - *(int*)((char*)self + 4)) {
        if (n < 0) {
            uint grow = 7;
            uint cur = (uint)((*(int*)((char*)self + 4) - *(int*)self) * 2);
            uint chosen = cur < 8 ? grow : cur;
            for (;;) {
                if (chosen >= 0xf4240) break;
                FormatResize(self, chosen);
                n = Vsnprintf8((char*)(*(int*)self + iVar3),
                               (chosen - (uint)iVar3) + 1, fmt, args);
                chosen *= 2;
                if (n >= 0) break;
            }
        }
    } else {
        FormatResize(self, (unsigned)(n + iVar3));
        n = Vsnprintf8((char*)(*(int*)self + iVar3), (unsigned)(n + 1), fmt, args);
    }
    if (n >= 0) *(int*)((char*)self + 4) = *(int*)self + n + iVar3;
    return self;
}

// @ 0x00b20b90
struct StringC {
    void* ctor(void* a);   // 0xb20b90
};
// @ 0x00b20b90
void* __thiscall StringC::ctor(void* a)
{
    void* self = this;
    *(void**)self = *(void**)a;
    *(void**)((char*)self + 4) = 0;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    int iVar1 = *(int*)((char*)a + 8);
    const char* src = *(const char**)((char*)a + 4);
    unsigned size = (unsigned)(iVar1 - (int)src);
    ((StringBase*)((char*)self + 4))->RangeInitialize(size + 1);
    char* dst = *(char**)((char*)self + 4);
    DoInsertValueC(dst, src, size);
    char* end = dst + size;
    *(char**)((char*)self + 8) = end;
    *end = 0;
    return self;
}

// @ 0x00b20c00
struct StringAlloc {
    void* ctor(void* a);   // 0xb20c00
};
// @ 0x00b20c00
void* __thiscall StringAlloc::ctor(void* a)
{
    void* self = this;
    *(void**)self = 0;
    *(void**)((char*)self + 4) = 0;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0x10) = *(void**)((char*)a + 0x10);
    int iVar1 = *(int*)((char*)a + 4);
    const char* src = *(const char**)a;
    unsigned size = (unsigned)(iVar1 - (int)src);
    ((ByteString*)self)->allocate(size + 1);
    char* dst = *(char**)self;
    DoInsertValueC(dst, src, size);
    char* end = dst + size;
    *(char**)((char*)self + 4) = end;
    *end = 0;
    return self;
}

// ------------------------------------------------------------------ noun manager
struct cDamageDisplay;
struct cGameNounManager {
    char pad[0x10c];
    cDamageDisplay* mDamageDisplay;  // +0x10c
    char* mListHead;                 // +0x110
    void* CreateNoun(unsigned id);   // 0xb20c60
    void  PostRemove(void* n);       // 0xb20d30
    void* CreateDebugNoun(unsigned a, void* b);  // 0xb20e40
};

extern void* __cdecl FUN_00920090();               // 0x00920090
extern unsigned g_InstanceIDGen;                   // 0x0167be28
struct MgrHook { void Mark(void* p); };            // 0x00b201a0

// @ 0x00b20c60
void* __thiscall cGameNounManager::CreateNoun(unsigned id)
{
    ((SerObj*)0x167c988)->Set();
    void* mgr = FUN_00920090();
    IRefObject* obj = (IRefObject*)(*(void*(**)(void*, unsigned, unsigned, unsigned, unsigned))
                                     (*(void***)mgr + 0x20/4))(mgr, id, 0x17f243b, 0, 0);
    if (obj) obj->AddRef();
    char* n = (char*)SPORE_NEW(0xc);
    char* at8 = n + 8;
    if (at8) { *(IRefObject**)at8 = obj; if (obj) obj->AddRef(); }
    *(char**)(n + 0) = (char*)this + 0x10c;
    *(void**)(n + 4) = *(void**)((char*)this + 0x110);
    *(void**)this->mListHead = n;
    if (obj) obj->Release();
    unsigned v = ++g_InstanceIDGen;
    *(unsigned*)((char*)obj + 0x24) = v;
    *(void**)((char*)obj + 0x10) = *(void**)((char*)this + 0x7c);
    void* node = (char*)obj + 0xc;
    *(void**)node = (char*)this + 0x78;
    *(void**)((char*)this + 0x7c) = node;
    *(void**)(*(void**)((char*)obj + 0x10)) = node;
    obj->AddRef();
    ((MgrHook*)this)->Mark(obj);
    return obj;
}

// @ 0x00b20d30
void __thiscall cGameNounManager::PostRemove(void* p)
{
    (void)p;
}

// @ 0x00b20e40
void* __thiscall cGameNounManager::CreateDebugNoun(unsigned a, void* b)
{
    (void)a; (void)b;
    return 0;
}

// ------------------------------------------------------------------ UpdateDebugUI
// @ 0x00b20ee0
ByteString* __stdcall UpdateDebugUI(ByteString* out, unsigned kind)
{
    extern char gEmptyChar;
    out->mpBegin = &gEmptyChar;
    out->mpEnd = &gEmptyChar;
    out->mpCapacity = &gEmptyChar + 1;
    switch (kind) {
    case 0: out->Assign("none"); break;
    case 1: out->Assign("creature"); break;
    case 2: out->Assign("tribe"); break;
    case 3: out->Assign("city"); break;
    case 4: out->Assign("civilization"); break;
    case 5: out->Assign("empire"); break;
    default: out->Assign("unknown", "unknown" + 7); break;
    }
    return out;
}
