// Slice s00a290b0 - EA::Audio::System resource/id registry helpers, id pools and
// the texture-LRU / tuning-value maintenance routines.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// External helpers (defined in other slices / the original binary).
// ---------------------------------------------------------------------------
void operator_delete__(void* p);                       // 0x00f47380
void* FUN_008d5d00();                                  // 0x008d5d00
void* FUN_00a16f40(void* self, void* a, void* b, void* c, void* d, void* e);  // 0x00a16f40
void* FUN_00a21d00(void* self, void* key, void* out);  // 0x00a21d00
void  FUN_00a27500(void* out, void* val);              // 0x00a27500
void* FUN_00b5f950(void* self, void* v);               // 0x00b5f950
bool  WideEquals(void* ws, const wchar_t* lit);        // 0x006ab760

// Global ids compared by ReadTuningValues and the wide-string / float constants.
extern unsigned g_keyA;    // 0x01552da0
extern unsigned g_keyB;    // 0x01552da4
extern unsigned g_keyC;    // 0x01552da8
extern const wchar_t g_wMono[];    // 0x01452c80
extern const wchar_t g_wStereo[];  // 0x01452c70
extern const wchar_t g_wQuad[];    // 0x01452c68
extern const wchar_t g_wSurround[];// 0x01452c60
extern const float   g_fQuadVal;   // 0x01470f1c
extern const float   g_fSurroundVal; // 0x013eb95c
extern const float   g_fPow2_32;   // 0x013f4fd0

// ---------------------------------------------------------------------------
// 12-byte resource key and the 16-byte (key + value) pair used by the maps.
// ---------------------------------------------------------------------------
struct Key12 { unsigned a, b, c; };
struct Key16 { unsigned a, b, c, d; };
// 8-byte map pair (key + value) used by the primitive table.
struct PairU { unsigned first; void* second; };

// 1-byte tag passed by value to the eastl hashtable insert helpers (the callee
// only inspects the low byte; the compiler materialises it as a 4-byte stack
// word, exactly like the original).
struct Tag { bool b; };

// find/erase iterator (node + bucket pointer).
struct HNode;
struct HIter { void* node; HNode** bucket; };
// insert result (node + bucket + inserted flag), 12 bytes.
struct InsertRes { void* node; HNode** bucket; bool inserted; };

// node of the unsigned-keyed tables (primitive / unregister / clear): value at
// +4, next at +8.
struct HNode { unsigned key; void* value; HNode* next; };

struct FactoryB;

// ---------------------------------------------------------------------------
// refcounted object interface shared by the key/value objects in the tables.
// ---------------------------------------------------------------------------
struct Obj {
    virtual void AddRef();          // +0x00
    virtual void Release();         // +0x04
    virtual void v02();             // +0x08
    virtual void v03();             // +0x0c
    virtual void v04(FactoryB* f, void* r); // +0x10
    virtual void v05();             // +0x14
    virtual void v06();             // +0x18
    virtual void v07();             // +0x1c
    virtual void v08();             // +0x20
    virtual void v09();             // +0x24
    virtual void v10();             // +0x28
    virtual void v11();             // +0x2c
    virtual void v12();             // +0x30
    virtual void v13();             // +0x34
    virtual void v14();             // +0x38
    virtual void v15();             // +0x3c
};

// key object whose vtable yields the registry id at slot 2 (+0x08) and slot 6
// (+0x18).
struct KeyObj {
    virtual void k0();              // +0x00
    virtual void k1();              // +0x04
    virtual unsigned GetId8();      // +0x08
    virtual void k3();              // +0x0c
    virtual void k4();              // +0x10
    virtual void k5();              // +0x14
    virtual unsigned GetId18();     // +0x18
};

// texture instance object tracked by the LRU (vtable at +0, key at +8, size at
// +0x18, last-touch time at +0x20).
struct TexObj : Obj {
    int     pad4;                   // +0x04
    Key12   key;                    // +0x08
    int     pad14;                  // +0x14
    int     size;                   // +0x18
    int     pad1c;                  // +0x1c
    double  time;                   // +0x20
};

// value object of the database Create call (vtable slots touched at +0x08 and
// +0x24).
struct DbInfo {
    virtual void i0(); virtual void i1();
    virtual void i2();              // +0x08
    virtual void i3(); virtual void i4(); virtual void i5(); virtual void i6();
    virtual void i7(); virtual void i8();
    virtual void i9();              // +0x24
};

// database object returned by System::FindDatabase (vtable slots used at
// +0x24 and +0x34).
struct DbObj {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9();                       // +0x24
    virtual void d10(); virtual void d11(); virtual void d12();
    virtual bool Create(const void* key, void* out, int a, int b, int c, int d);  // +0x34
};

// configuration object (IConfiguration) - only the slots this slice touches.
struct IConfig {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
    virtual void c4(); virtual void c5(); virtual void c6();
    virtual bool GetList1(unsigned hash, void** out);          // +0x1c
    virtual void c8();
    virtual bool GetBool(unsigned hash, bool* out);            // +0x24
    virtual void c10();
    virtual bool GetUint32(unsigned hash, unsigned* out);      // +0x2c
    virtual bool GetFloat(unsigned hash, float* out);          // +0x30
    virtual void c13(); virtual void c14();
    virtual void* GetString(unsigned id);                      // +0x3c
    virtual void c16(); virtual void c17(); virtual void c18();
    virtual bool GetList2(unsigned hash, void** out, void** out2);  // +0x4c
};

// factory reached through System::mpFactoryB.
struct FactoryB {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
    virtual void f4(); virtual void f5(); virtual void f6();
    virtual bool Create(void* info, void* out, int a, unsigned b); // +0x1c
};

// ---------------------------------------------------------------------------
// hashtable: buckets at +4, bucket count at +8, element count at +0xc.
// ---------------------------------------------------------------------------
struct HTable {
    int      pad0;          // +0x00
    HNode**  mpBuckets;     // +0x04
    unsigned mnBuckets;     // +0x08
    unsigned mnElements;    // +0x0c

    void  find(HIter* out, const unsigned* key);                    // 0x00645ed0
    void  findKey12(HIter* out, const void* key);                   // 0x00833840
    void  erase(HIter it, HIter* out);                              // 0x00d2c9f0
    HIter* eraseNode(HIter node, HIter* out);                       // 0x00a27660
    void  FreeBuckets(HNode** buckets, unsigned count);             // 0x00a24480
    void  InsertKey(InsertRes* out, const unsigned* key, Tag t);    // 0x00a26be0
    void  InsertPair(InsertRes* out, const void* pair, Tag t);      // 0x00a26ce0
    void  InsertPair16(InsertRes* out, const void* pair, Tag t);    // 0x00a26b00
};

// node of the Key-keyed tables (active / LRU): key at +0, value at +0xc, next
// at +0x10.
struct TexNode { Key12 key; TexObj* value; TexNode* next; };

// ring buffer of ids (cBegin/cEnd at +0, live range at +0xfbc).
struct IdRing {
    unsigned* cBegin;       // +0x000
    unsigned* cEnd;         // +0x004
    char      pad[0xfbc - 8];
    unsigned* mBegin;       // +0xfbc
    unsigned* mEnd;         // +0xfc0
    int       mSize;        // +0xfc4
};

// a fixed_hash_set (0x3ecc bytes) immediately followed by its id ring (0xfc8).
struct PooledTable {
    HTable table;                       // +0x0000
    char   pad[0x3ecc - sizeof(HTable)];
    IdRing ring;                        // +0x3ecc
};

// stopwatch used by the LRU sweep.
struct Stopwatch {
    char pad[0x14];
    float coeff;                        // +0x14
    Stopwatch(int a, bool b);           // 0x0093a560
    void Restart();                     // 0x00571e80
    __int64 GetElapsedTimeF();          // 0x0093a3a0
};

// wide string (eastl::basic_string<wchar_t>) minimal shape.
struct WString {
    wchar_t* b; wchar_t* e; wchar_t* cap; int alloc;
    void RangeInit(const wchar_t* first);   // 0x00579a90
    ~WString()
    {
        if ((((char*)e - (char*)b) & ~1) > 2 && b)
            operator_delete__(b);
    }
};

// string list returned by IConfiguration::GetList1 (inline-vs-heap tagged).
struct StrList {
    const void*    mpBegin;     // +0x00
    unsigned       mnEnd;       // +0x04
    unsigned       mnSize;      // +0x08
    unsigned       mnCap;       // +0x0c
    unsigned short mFlags;      // +0x10
    unsigned short mInlineLen;  // +0x12
};
struct Str16 { const char* mpStr; int b, c, d; };

// ---------------------------------------------------------------------------
// System singleton; only the fields this slice touches are typed.
// ---------------------------------------------------------------------------
struct Sys {
    virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003();
    virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
    virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
    virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
    virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
    virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
    virtual void v024(); virtual void v025(); virtual void v026(); virtual void v027();
    virtual void v028(); virtual void v029(); virtual void v030(); virtual void v031();
    virtual void v032(); virtual void v033(); virtual void v034(); virtual void v035();
    virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
    virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043();
    virtual void v044(); virtual void v045(); virtual void v046(); virtual void v047();
    virtual void v048(); virtual void v049(); virtual void v050();
    virtual double SystemTime();                                // +0xcc (slot 51)
    virtual void v052(); virtual void v053(); virtual void v054();
    virtual void v055(); virtual void v056(); virtual void v057();
    virtual void v058(unsigned id, const char* name);           // +0xe8 (slot 58)
    virtual void v059(); virtual void v060();
    virtual unsigned SymbolToId(const char* name);              // +0xf4 (slot 61)
    virtual void v062();
    virtual void SetProperty(float value, unsigned hash);       // +0xfc (slot 63)
    virtual void v064(); virtual void v065(); virtual void v066(); virtual void v067();
    virtual void v068(); virtual void v069(); virtual void v070(); virtual void v071();
    virtual void v072(unsigned id);                             // +0x120 (slot 72)
    virtual void v073(); virtual void v074(); virtual void v075(); virtual void v076();
    virtual void v077(); virtual void v078(); virtual void v079(); virtual void v080();
    virtual void v081(); virtual void v082(); virtual void v083(); virtual void v084();
    virtual void v085(); virtual void v086(); virtual void v087(); virtual void v088();
    virtual void v089(); virtual void v090(); virtual void v091(); virtual void v092();
    virtual void v093(); virtual void v094(); virtual void v095(); virtual void v096();
    virtual void v097();
    virtual void* FindDatabase(const void* key);                // +0x188 (slot 98)
    virtual void v099(); virtual void v100(); virtual void v101(); virtual void v102();
    virtual void v103(); virtual void v104(); virtual void v105(); virtual void v106();
    virtual void v107(); virtual void v108(); virtual void v109(); virtual void v110();
    virtual void v111();
    virtual void Slot112();                                     // +0x1c0 (slot 112)

    char     pad_ec[0xec - 8];
    unsigned mStreamPoolNumStreams;    // +0x0ec
    unsigned mStreamPoolBufferSize;    // +0x0f0
    unsigned mStreamPoolMaxRequests;   // +0x0f4
    char     pad_f8[0x1f8 - 0x0f8];
    void*    mpConfiguration;          // +0x1f8
    char     pad_1fc[0x200 - 0x1fc];
    int      mPerformanceLevel;        // +0x200
    unsigned mU204;                    // +0x204
    unsigned mU208;                    // +0x208
    unsigned mU20c;                    // +0x20c
    char     pad_210[0x3fd - 0x210];
    bool     mBool3fd;                 // +0x3fd
    char     pad_3fe[0x400 - 0x3fe];
    float    mFloat400;                // +0x400
    HTable   mPrimTable;               // +0x404
    char     pad_414[0x13f4 - 0x414];
    HTable   mUnregTable;              // +0x13f4
    char     pad_1404[0x23e4 - 0x1404];
    HTable   mClearTable;              // +0x23e4
    char     pad_23f4[0x118a1c - 0x23f4];
    HTable   mActiveTable;             // +0x118a1c
    char     pad_118a2c[0x118a3c - 0x118a2c];
    HTable   mLRUTable;                // +0x118a3c
    char     pad_118a4c[0x128ae0 - 0x118a4c];
    PooledTable mPoolA;                // +0x128ae0
    PooledTable mPoolB;                // +0x12d974
    PooledTable mPoolC;                // +0x132808
    char     pad_1376a0[0x15b750 - (0x132808 + sizeof(PooledTable))];
    TexNode* mLRUIterNode;             // +0x15b750
    TexNode** mLRUIterBucket;          // +0x15b754
    int      mCurrentBytes;            // +0x15b758
    int      mCountMiss;               // +0x15b75c
    int      mCountHit;                // +0x15b760
    int      mTimeSliceUSec;           // +0x15b764
    double   mRemoveOlderThanSec;      // +0x15b768
    int      mCacheSizeLimit;          // +0x15b770
    bool     mbDisableCache;           // +0x15b774
    char     pad_15b775[0x15b778 - 0x15b775];
    FactoryB* mpFactoryB;              // +0x15b778

    void  AddTextureRef(Key12* key);                   // 0x00a28a20
    bool  RegisterKey(void* key);                      // 00a290b0
    bool  UnregisterKey(void* key);                    // 00a29140
    void  ClearUnregTable();                           // 00a291b0
    void  ClearClearTable();                           // 00a29230
    unsigned PopIdA();                                 // 00a292d0
    unsigned PopIdC();                                 // 00a29340
    unsigned PopIdB();                                 // 00a293e0
    bool  GetTexture(Key12* key, void** out);          // 00a29450
    bool  GetTexture2(Key12* key, void** out2, void** out);   // 00a29690
    void  RemoveTexture(TexObj* obj);                  // 00a298f0
    void  SweepLRU();                                  // 00a29a50
    bool  ReadTuningValues(const Key12* key);          // 00a29be0
};

// ===========================================================================
// 00a290b0: register the id of a key object in the primitive table (+0x404).
// ===========================================================================
// @ 0x00a290b0
bool Sys::RegisterKey(void* key)
{
    if (!key)
        return false;
    unsigned id = ((KeyObj*)key)->GetId8();
    HIter it;
    mPrimTable.find(&it, &id);
    if (it.node != mPrimTable.mpBuckets[mPrimTable.mnBuckets])
        return false;
    PairU pair;
    pair.first = ((KeyObj*)key)->GetId8();
    pair.second = key;
    InsertRes out;
    Tag tag;
    tag.b = false;
    mPrimTable.InsertPair(&out, &pair, tag);
    return true;
}

// ===========================================================================
// 00a29140: remove the id of a key object from the table at +0x13f4.
// ===========================================================================
// @ 0x00a29140
bool Sys::UnregisterKey(void* key)
{
    if (!key)
        return false;
    unsigned id = ((KeyObj*)key)->GetId18();
    HIter it;
    mUnregTable.find(&it, &id);
    if (it.node == mUnregTable.mpBuckets[mUnregTable.mnBuckets])
        return false;
    mUnregTable.erase(it, &it);
    return true;
}

// ===========================================================================
// 00a291b0: release every value of the table at +0x13f4, then free its buckets.
// ===========================================================================
// @ 0x00a291b0
void Sys::ClearUnregTable()
{
    HTable* t = &mUnregTable;
    HNode** bucket = (HNode**)t->mpBuckets;
    HNode* node = *bucket;
    if (!node) {
        ++bucket;
        while (!*bucket)
            ++bucket;
        node = *bucket;
    }
    HNode* end = (HNode*)t->mpBuckets[t->mnBuckets];
    while (node != end) {
        ((Obj*)node->value)->v05();
        node = node->next;
        if (!node) {
            ++bucket;
            while (!*bucket)
                ++bucket;
            node = *bucket;
        }
    }
    t->FreeBuckets(t->mpBuckets, t->mnBuckets);
    t->mnElements = 0;
}

// ===========================================================================
// 00a29230: detach and release every value of the table at +0x23e4, then free
// the buckets of the table at +0x13f4.
// ===========================================================================
// @ 0x00a29230
void Sys::ClearClearTable()
{
    HTable* t = &mClearTable;
    HNode** bucket = (HNode**)t->mpBuckets;
    HNode* node = *bucket;
    if (!node) {
        ++bucket;
        while (!*bucket)
            ++bucket;
        node = *bucket;
    }
    HNode* end = (HNode*)t->mpBuckets[t->mnBuckets];
    while (node != end) {
        Obj* obj = (Obj*)node->value;
        node->value = 0;
        obj->v05();
        obj->Release();
        node = node->next;
        if (!node) {
            ++bucket;
            while (!*bucket)
                ++bucket;
            node = *bucket;
        }
    }
    mUnregTable.FreeBuckets(mUnregTable.mpBuckets, mUnregTable.mnBuckets);
    mUnregTable.mnElements = 0;
}

// ===========================================================================
// 00a292d0: take the next id from ring A and register it in table A.
// ===========================================================================
// @ 0x00a292d0
unsigned Sys::PopIdA()
{
    IdRing* r = &mPoolA.ring;
    if (r->mBegin == r->mEnd)
        return 0;
    unsigned v = *r->mBegin;
    r->mBegin += 1;
    if (r->mBegin == r->cEnd)
        r->mBegin = r->cBegin;
    r->mSize -= 1;
    InsertRes out;
    Tag tag;
    tag.b = false;
    mPoolA.table.InsertKey(&out, &v, tag);
    return v;
}

// ===========================================================================
// 00a29340: take the next id from ring C and register it in tables C and A.
// ===========================================================================
// @ 0x00a29340
unsigned Sys::PopIdC()
{
    IdRing* r = &mPoolC.ring;
    if (r->mBegin == r->mEnd)
        return 0;
    unsigned v = *r->mBegin;
    r->mBegin += 1;
    if (r->mBegin == r->cEnd)
        r->mBegin = r->cBegin;
    r->mSize -= 1;
    InsertRes out;
    Tag tag;
    tag.b = false;
    mPoolC.table.InsertKey(&out, &v, tag);
    tag.b = false;
    mPoolA.table.InsertKey(&out, &v, tag);
    return v;
}

// ===========================================================================
// 00a293e0: take the next id from ring B and register it in table B.
// ===========================================================================
// @ 0x00a293e0
unsigned Sys::PopIdB()
{
    IdRing* r = &mPoolB.ring;
    if (r->mBegin == r->mEnd)
        return 0;
    unsigned v = *r->mBegin;
    r->mBegin += 1;
    if (r->mBegin == r->cEnd)
        r->mBegin = r->cBegin;
    r->mSize -= 1;
    InsertRes out;
    Tag tag;
    tag.b = false;
    mPoolB.table.InsertKey(&out, &v, tag);
    return v;
}

// ===========================================================================
// 00a29450: look up (or build) the texture instance for a resource key.
// ===========================================================================
// @ 0x00a29450
bool Sys::GetTexture(Key12* key, void** out)
{
    if (mCacheSizeLimit != 0) {
        HIter it;
        mActiveTable.findKey12(&it, key);
        if (it.node != mActiveTable.mpBuckets[mActiveTable.mnBuckets]) {
            TexObj* obj = ((TexNode*)it.node)->value;
            obj->time = SystemTime();
            if (out) {
                AddTextureRef(key);
                obj->AddRef();
                *out = obj;
            }
            mCountHit += 1;
            return true;
        }
    }
    mCountMiss += 1;
    TexObj* obj = 0;
    void* created = 0;
    DbObj* db = (DbObj*)FindDatabase(key);
    if (db) {
        void* info = 0;
        if (db->Create(key, &info, 1, 6, 1, 0)) {
            if (mpFactoryB->Create(info, &created, 0, key->b)) {
                obj = (TexObj*)created;
                obj->AddRef();
                obj->key = *key;
            }
        }
        if (info)
            ((DbInfo*)info)->i9();
        if (created)
            ((Obj*)created)->Release();
        if (info)
            ((DbInfo*)info)->i2();
    }
    if (!obj)
        return false;
    obj->time = SystemTime();
    if (mCacheSizeLimit != 0) {
        mCurrentBytes += obj->size;
        Key16 pair;
        pair.a = key->a;
        pair.b = key->b;
        pair.c = key->c;
        pair.d = (unsigned)obj;
        obj->AddRef();
        InsertRes out2;
        Tag tag;
        tag.b = false;
        mActiveTable.InsertPair16(&out2, &pair, tag);
        obj->Release();
        mLRUIterNode = (TexNode*)mActiveTable.mpBuckets[mActiveTable.mnBuckets];
        mLRUIterBucket = (TexNode**)&mActiveTable.mpBuckets[mActiveTable.mnBuckets];
    }
    if (out) {
        AddTextureRef(key);
        obj->AddRef();
        *out = obj;
    }
    obj->Release();
    return true;
}

// ===========================================================================
// 00a29690: look up a texture instance (active table then LRU table, building it
// from the database on a miss).
// ===========================================================================
// @ 0x00a29690
bool Sys::GetTexture2(Key12* key, void** out2, void** out)
{
    void* result = 0;
    TexObj* obj = 0;
    if (mCacheSizeLimit != 0) {
        HIter it;
        mActiveTable.findKey12(&it, key);
        if (it.node != mActiveTable.mpBuckets[mActiveTable.mnBuckets]) {
            obj = ((TexNode*)it.node)->value;
            obj->time = SystemTime();
            if (out2)
                *out2 = 0;
            if (out) {
                AddTextureRef(key);
                obj->AddRef();
                *out = obj;
            }
            mCountHit += 1;
            if (result)
                ((Obj*)result)->Release();
            return true;
        }
    }
    {
        HIter jt;
        mLRUTable.findKey12(&jt, key);
        if (jt.node != mLRUTable.mpBuckets[mLRUTable.mnBuckets]) {
            if (out2) {
                void* v = ((TexNode*)jt.node)->value;
                *out2 = v;
                ((Obj*)v)->AddRef();
            }
            if (result)
                ((Obj*)result)->Release();
            return true;
        }
    }
    mCountMiss += 1;
    void* p = FUN_008d5d00();
    if (p) {
        DbObj* db = (DbObj*)FindDatabase(key);
        if (db) {
            void* info = 0;
            if (db->Create(key, &info, 1, 6, 1, 0)) {
                void* holder = 0;
                void* effect = FUN_00a16f40(&holder, 0, info, 0, key, 0);
                ((Obj*)p)->v04(mpFactoryB, effect);
                ((DbInfo*)info)->i9();
                void* holder2 = 0;
                void* r = FUN_00a21d00(&holder2, key, &result);
                void* res[4];
                FUN_00a27500(res, r);
                if (out) {
                    *out = result;
                    ((Obj*)result)->AddRef();
                }
            }
            if (info)
                ((DbInfo*)info)->i2();
        }
    }
    if (result)
        ((Obj*)result)->Release();
    return false;
}

// ===========================================================================
// 00a298f0: re-touch a texture in the active table and drop it from the LRU.
// ===========================================================================
// @ 0x00a298f0
void Sys::RemoveTexture(TexObj* obj)
{
    if (mCacheSizeLimit != 0) {
        HIter it;
        mActiveTable.findKey12(&it, &obj->key);
        if (it.node == mActiveTable.mpBuckets[mActiveTable.mnBuckets]) {
            mCurrentBytes += obj->size;
            obj->AddRef();
            Key16 pair;
            pair.a = obj->key.a;
            pair.b = obj->key.b;
            pair.c = obj->key.c;
            pair.d = (unsigned)obj;
            obj->AddRef();
            InsertRes out;
            Tag tag;
            tag.b = false;
            mActiveTable.InsertPair16(&out, &pair, tag);
            if (pair.d)
                obj->Release();
            obj->Release();
            mLRUIterNode = (TexNode*)mActiveTable.mpBuckets[mActiveTable.mnBuckets];
            mLRUIterBucket = (TexNode**)&mActiveTable.mpBuckets[mActiveTable.mnBuckets];
        }
        HIter jt;
        mLRUTable.findKey12(&jt, &obj->key);
        if (jt.node != mLRUTable.mpBuckets[mLRUTable.mnBuckets])
            mLRUTable.eraseNode(jt, &jt);
    }
}

// ===========================================================================
// 00a29a50: evict least-recently-used textures until the cache fits its budget.
// ===========================================================================
// @ 0x00a29a50
void Sys::SweepLRU()
{
    if (mActiveTable.mnElements == 0)
        return;
    if (mCacheSizeLimit == 0)
        return;
    Stopwatch sw(3, false);
    sw.Restart();
    if ((unsigned)mCurrentBytes <= (unsigned)mCacheSizeLimit)
        return;
    do {
        if (mLRUIterNode == (TexNode*)mActiveTable.mpBuckets[mActiveTable.mnBuckets]) {
            TexNode** b = (TexNode**)mActiveTable.mpBuckets;
            TexNode* n = *b;
            if (!n) {
                ++b;
                while (!*b)
                    ++b;
                n = *b;
            }
            mLRUIterNode = n;
            mLRUIterBucket = (TexNode**)b;
        }
        TexObj* obj = mLRUIterNode->value;
        if (SystemTime() - obj->time <= mRemoveOlderThanSec) {
            TexNode* n = mLRUIterNode->next;
            mLRUIterNode = n;
            while (!n) {
                mLRUIterBucket += 1;
                n = *mLRUIterBucket;
                mLRUIterNode = n;
            }
        } else {
            mCurrentBytes -= obj->size;
            HIter it;
            it.node = mLRUIterNode;
            it.bucket = (HNode**)mLRUIterBucket;
            HIter tmp;
            HIter* res = mActiveTable.eraseNode(it, &tmp);
            mLRUIterNode = (TexNode*)res->node;
            mLRUIterBucket = (TexNode**)res->bucket;
        }
        __int64 elapsed = sw.GetElapsedTimeF();
        if ((double)elapsed * sw.coeff > (double)(unsigned)mTimeSliceUSec)
            break;
    } while ((unsigned)mCurrentBytes > (unsigned)mCacheSizeLimit);
}

// ===========================================================================
// 00a29be0: read the audio tuning values from the configuration object.
// ===========================================================================
// @ 0x00a29be0
bool Sys::ReadTuningValues(const Key12* key)
{
    if (key->a != g_keyA || key->b != g_keyB || key->c != g_keyC)
        return true;
    IConfig* cfg = (IConfig*)mpConfiguration;
    if (!cfg)
        return false;

    cfg->GetBool(0x7188e63e, &mBool3fd);
    cfg->GetFloat(0xe8bc4932, &mFloat400);
    Slot112();

    StrList* strList = 0;
    if (cfg->GetList1(0x4b2a3424, (void**)&strList) && strList) {
        unsigned count;
        const char** base;
        if (strList->mFlags & 0x30) {
            count = strList->mnSize;
            base = (const char**)strList->mpBegin;
        } else {
            count = strList->mInlineLen != 0 ? 1 : 0;
            base = strList->mInlineLen != 0 ? (const char**)strList : 0;
        }
        for (unsigned i = 0; i < count; ++i) {
            const char* s = ((Str16*)base)[i].mpStr;
            v058(SymbolToId(s), s);
        }
    }

    unsigned* list2 = 0;
    unsigned count2 = 0;
    if (cfg->GetList2(0x7cb81a35, (void**)&list2, (void**)&count2)) {
        for (unsigned i = 0; i < count2; ++i)
            v072(list2[i * 3]);
    }

    unsigned modeId = SymbolToId("dacoutputmode");
    void* modeStr = cfg->GetString(modeId);
    if (modeStr) {
        WString ws;
        ws.RangeInit((const wchar_t*)modeStr);
        float v;
        if (WideEquals(&ws, g_wMono))
            v = 0.0f;
        else if (WideEquals(&ws, g_wStereo))
            v = 1.0f;
        else if (WideEquals(&ws, g_wQuad))
            v = g_fQuadVal;
        else if (WideEquals(&ws, g_wSurround))
            v = g_fSurroundVal;
        else
            v = 1.0f;
        SetProperty(v, 0x435b383);
    }

    float fv;
    if (cfg->GetFloat(0x6a371e0, &fv))
        SetProperty(fv, 0x6a371e0);

    SetProperty((float)mPerformanceLevel, 0x6df5822d);

    unsigned u;
    u = SymbolToId("streampoolnumstreams");
    cfg->GetUint32(u, &mStreamPoolNumStreams);
    u = SymbolToId("streampoolbuffersize");
    cfg->GetUint32(u, &mStreamPoolBufferSize);
    u = SymbolToId("streampoolmaxrequests");
    cfg->GetUint32(u, &mStreamPoolMaxRequests);
    u = SymbolToId("RemoveMostFrequentlyUnusedTimeSliceUSec");
    cfg->GetUint32(u, (unsigned*)&mTimeSliceUSec);

    u = SymbolToId("RemoveIfOlderThanSeconds");
    if (cfg->GetFloat(u, &fv))
        mRemoveOlderThanSec = (double)fv;

    u = SymbolToId("BinaryResourceCacheSizeMB");
    unsigned cacheMB;
    if (cfg->GetUint32(u, &cacheMB))
        mCacheSizeLimit = (int)(cacheMB << 20);
    if (mbDisableCache)
        mCacheSizeLimit = 0;

    cfg->GetUint32(0xed9f3a3d, &mU20c);
    cfg->GetUint32(0xdcdf5a2d, &mU204);
    cfg->GetUint32(0xe25ce39d, &mU208);
    return true;
}
