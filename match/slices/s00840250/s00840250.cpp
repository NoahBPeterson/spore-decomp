// Slice s00840250 (batch w2g7). ArgScript cFileParser ctor/dtor/AddFilePath,
// cParser Release, ranged parsers and misc string/enum helpers.
// /O2 /MD /Gy /EHsc /TP /GS-.

typedef unsigned int   uint32;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef int            int32;
typedef unsigned long  ulong32;

extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line);
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
__declspec(dllimport) int   __cdecl isspace(int);
__declspec(dllimport) int   __cdecl _stricmp(const char* a, const char* b);
__declspec(dllimport) int   __cdecl tolower(int);
__declspec(dllimport) unsigned __cdecl strspn(const char* s, const char* set);
__declspec(dllimport) unsigned __cdecl strcspn(const char* s, const char* set);
unsigned __cdecl strlen(const char* s);
void* __cdecl memcpy(void* dst, const void* src, unsigned n);
void* __cdecl memmove(void* dst, const void* src, unsigned n);
void* __cdecl memchr(const void* s, int c, unsigned n);
int   __cdecl Vsnprintf8(char* buf, unsigned n, const char* fmt, void* args);   // 0x00938400
}
inline void* operator new(unsigned, void* p) { return p; }
inline void  operator delete(void*, void*) {}

static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";

extern char gEmptyString[];     // 0x01667bac
extern char gEmptyStringCap[];  // 0x01667bad (gEmptyString + 1)

struct cError {
    cError(const char* fmt, ...);
    cError(const cError&);
};

struct AllocationHeader { int mOwned; };
static inline bool allocation_owned(void* p) {
    return ((AllocationHeader*)p)[-1].mOwned != 0;
}

namespace eastl {
class allocator { public: unsigned char pad[4]; };
struct string8 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator mAllocator;
    string8() { mpBegin = gEmptyString; mpCapacity = gEmptyStringCap; mpEnd = mpBegin; }
    void assign(const char* first, const char* last);
    void assign(const string8& s);
    void append(const char* first, const char* last);
    void append(unsigned n, char c);
    void resize(unsigned n);
    void resize(unsigned n, char c);
    void erase(unsigned pos, unsigned count);
    int  find(const char* p, unsigned pos) const;
    void append_sprintf_va_list(const char* fmt, void* args);
    ~string8() {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
};
}  // namespace eastl

// helpers from neighbouring slices
struct cExprAccess { void EvalBoolParentheses(const char** p, char c); };  // 0x0083d240
void  __cdecl MakeCaseInsensitive2(const char* p, eastl::string8* s);    // 0x00840cc0
void  __cdecl FileParser_ShutdownStub(void* self);
void  __cdecl HashFreeNotifyStub(void* bucketArray, int bucketCount);
void  __cdecl VectorFreeSpecsStub(int* self);
void  __cdecl IterateWatchersStub(void* map);
void  __cdecl HashResetNotifyStub(void* map);

// ===========================================================================
// 0x008407c0  name table lookup (stride 8, case-insensitive) -> int out
// ===========================================================================
// @ 0x008407c0
unsigned char __cdecl LookupName8(const char* name, int* table, int* out) {
    int key = *table;
    for (;;) {
        if (key == 0)
            return 0;
        if (_stricmp(name, (const char*)key) == 0) {
            *out = table[1];
            return 1;
        }
        table += 2;
        key = *table;
    }
}

// ===========================================================================
// 0x00840810  int table lookup by value (stride 8)
// ===========================================================================
// @ 0x00840810
int __cdecl LookupInt8(int key, int* table) {
    int k = *table;
    while (k) {
        if (key == table[1])
            return *table;
        table += 2;
        k = *table;
    }
    return 0;
}

// ===========================================================================
// 0x00840840  name table lookup (stride 0xc, case-insensitive) -> int out
// ===========================================================================
// @ 0x00840840
unsigned char __cdecl LookupName12(const char* name, int* table, int* out) {
    int key = *table;
    for (;;) {
        if (key == 0)
            return 0;
        if (_stricmp(name, (const char*)key) == 0) {
            *out = table[1];
            return 1;
        }
        table += 3;
        key = *table;
    }
}

// ===========================================================================
// 0x00840890  tokenizer helper (strspn/strcspn)
// ===========================================================================
// @ 0x00840890
const char* __cdecl NextToken(const char* s, int* len, const char* delims) {
    unsigned a = (unsigned)strspn(s, delims);
    unsigned b = (unsigned)strcspn(s + a, delims);
    *len = (int)b;
    return b ? s + a : 0;
}

// ===========================================================================
// 0x008409b0  EA::ArgScript::MakeCaseInsensitive (in place)
// ===========================================================================
// @ 0x008409b0
void __cdecl MakeCaseInsensitive(eastl::string8* s) {
    for (unsigned i = 0; i < (unsigned)(s->mpEnd - s->mpBegin); ++i)
        s->mpBegin[i] = (char)tolower(s->mpBegin[i]);
}

// ===========================================================================
// 0x00840bb0  EA::ArgScript::ParseEnum
// ===========================================================================
// @ 0x00840bb0
int __cdecl ParseEnum(const char* name, int* table) {
    while (*table) {
        if (_stricmp(name, (const char*)*table) == 0)
            return table[1];
        table += 2;
    }
    throw cError("Unknown enum '%s'", name);
}

// ===========================================================================
// 0x00840c20  EA::ArgScript::Sprintf
// ===========================================================================
// @ 0x00840c20
extern char gSprintfBuf[];      // 0x0164f780
void __cdecl Sprintf(eastl::string8* out, const char* fmt, ...) {
    char* args = (char*)&fmt + 4;
    Vsnprintf8(gSprintfBuf, 0x400, fmt, args);
    char* p = gSprintfBuf;
    while (*p) ++p;
    out->assign(gSprintfBuf, p);
}

// ===========================================================================
// 0x00840c70  EA::ArgScript::SprintfAppend
// ===========================================================================
// @ 0x00840c70
extern char gSprintfAppendBuf[];  // 0x0164fb80
void __cdecl SprintfAppend(eastl::string8* out, const char* fmt, ...) {
    char* args = (char*)&fmt + 4;
    Vsnprintf8(gSprintfAppendBuf, 0x400, fmt, args);
    char* p = gSprintfAppendBuf;
    while (*p) ++p;
    out->append(gSprintfAppendBuf, p);
}

// ===========================================================================
// 0x00840d50  EA::ArgScript::ParseRangedFloat
// ===========================================================================
// @ 0x00840d50
float __cdecl ParseRangedFloat(int* expr, float lo, float hi) {
    float v = ((float(__thiscall*)(int*))(*(void***)expr)[0x98 / 4])(expr);
    if (lo <= v && v <= hi)
        return v;
    throw cError("argument out of range: expecting [%g..%g], got %g", (double)lo, (double)hi, (double)v);
}

// ===========================================================================
// 0x00840dc0  EA::ArgScript::ParseRangedInt
// ===========================================================================
// @ 0x00840dc0
int __cdecl ParseRangedInt(int* expr, int lo, int hi) {
    int v = ((int(__thiscall*)(int*))(*(void***)expr)[0x9c / 4])(expr);
    if (lo <= v && v <= hi)
        return v;
    throw cError("argument out of range: expecting [%d..%d], got %d", lo, hi, v);
}

// ===========================================================================
// 0x00840e10  EA::ArgScript::ParseRangedVector3
// ===========================================================================
// @ 0x00840e10
float* __cdecl ParseRangedVector3(float* out, int* expr, int arg, float lo, float hi) {
    ((void(__thiscall*)(int*, float*, int))(*(void***)expr)[0xa8 / 4])(expr, out, arg);
    float x = out[0], y = out[1], z = out[2];
    if (lo <= x && x <= hi && lo <= y && y <= hi && lo <= z && z <= hi)
        return out;
    throw cError("argument out of range: expecting components (%g..%g), got (%g, %g, %g)",
                 (double)lo, (double)hi, (double)x, (double)y, (double)z);
}

// ===========================================================================
// 0x00841220 / 0x00841290 / 0x00841300  parser event dispatch (slots 0x38/0x3c/0x40)
// ===========================================================================
// @ 0x00841220
bool __fastcall ParserEvent38(int* self, int, void* arg) {
    try {
        ((void(__thiscall*)(int*, void*))(*(void***)self)[0x38 / 4])(self, arg);
    } catch (...) {
        return false;
    }
    return true;
}
// @ 0x00841290
bool __fastcall ParserEvent3c(int* self, int, void* arg) {
    try {
        ((void(__thiscall*)(int*, void*))(*(void***)self)[0x3c / 4])(self, arg);
    } catch (...) {
        return false;
    }
    return true;
}
// @ 0x00841300
bool __fastcall ParserEvent40(int* self, int, void* arg) {
    try {
        ((void(__thiscall*)(int*, void*))(*(void***)self)[0x40 / 4])(self, arg);
    } catch (...) {
        return false;
    }
    return true;
}

// ===========================================================================
// 0x008411c0  EA::ArgScript::cParser::Release
// ===========================================================================
// @ 0x008411c0
int __fastcall cParser_Release(int* self) {
    int* rc = self + 2;
    *rc = *rc - 1;
    int r = *rc;
    if (r == 0) {
        ((void(__thiscall*)(int*, int))(*(void***)self)[0xcc / 4])(self, 1);
        r = 0;
    }
    return r;
}

// ===========================================================================
// 0x00841130  double-from-int virtual adaptor (slot 1)
// ===========================================================================
// @ 0x00841130
float __fastcall ParserCall1ToFloat(int* self, int, int a, int b) {
    int r = ((int(__thiscall*)(int*, int, int))(*(void***)self)[1])(self, a, b);
    return (float)r;
}

// ===========================================================================
// 0x00841150 / 0x00841190  parenthesised argument fetch
// ===========================================================================
// @ 0x00841150
int __fastcall ParserArg1c(int* self, int, const char** p, void* expr) {
    ((cExprAccess*)expr)->EvalBoolParentheses(p, '(');
    ((cExprAccess*)expr)->EvalBoolParentheses(p, ')');
    return *(int*)(self[2] + 0x1c);
}
// @ 0x00841190
int __fastcall ParserArg20(int* self, int, const char** p, void* expr) {
    ((cExprAccess*)expr)->EvalBoolParentheses(p, '(');
    ((cExprAccess*)expr)->EvalBoolParentheses(p, ')');
    return *(int*)(self[2] + 0x20);
}

// ===========================================================================
// cFileParser and its containers
// ===========================================================================
extern char gEmptyWatcherBuckets[];  // 0x0154df28 (shared empty bucket array)

struct Watcher;

struct WatcherNode {
    unsigned char pad00[0x10];
    Watcher*      mpWatcher;   // +0x10
    WatcherNode*  mpNext;      // +0x14
};

struct WatcherMap {
    void*         mpAllocator;   // +0x00
    WatcherNode** mpBuckets;     // +0x04
    unsigned      mBucketCount;  // +0x08
    unsigned      mSize;         // +0x0c

    void         Free(WatcherNode** buckets, unsigned count);
    WatcherNode* Find(const eastl::string8& key);
    WatcherNode* Insert(const eastl::string8& key, Watcher** value);
};

struct FileSpec {
    eastl::string8 mPath;    // +0x00
    unsigned short mFlags;   // +0x10
    unsigned short mPad12;   // +0x12
};

struct SpecVector {
    FileSpec* mpBegin;     // +0x00
    FileSpec* mpEnd;       // +0x04
    FileSpec* mpCapacity;  // +0x08

    void Add(const FileSpec* spec);
    void DestroyRange(FileSpec* first, FileSpec* last);
};

struct ParserTimer {
    unsigned mWords[6];  // +0x00..+0x17
    void Init(int mode, bool start);
};

struct Watcher {
    void* mpVtable;                 // +0x00
    unsigned char mPad04[0x23c];
    int   mRefCount;                // +0x240

    void Construct();
    void Setup();
    void SetOwner(void* owner, void* callback);
    void SetPath(const char* path);
    void SetModeA(int value);
    void SetModeB(int value);
    void Start();
};

struct cFileParser {
    void* mpVtable0;          // +0x00
    void* mpVtable4;          // +0x04
    int   mRefCount;          // +0x08
    unsigned char mFlag0c;    // +0x0c
    unsigned char mPad0d[3];
    void* mpParser;           // +0x10
    SpecVector mSpecs;        // +0x14
    unsigned char mPad20[8];  // +0x20..+0x27
    unsigned char mFlag28;    // +0x28
    unsigned char mFlag29;    // +0x29
    unsigned char mPad2a[2];
    WatcherMap mWatchers;     // +0x2c
    float mFloat3c;           // +0x3c
    float mFloat40;           // +0x40
    unsigned mField44;        // +0x44
    unsigned char mPad48[8];  // +0x48..+0x4f
    ParserTimer mTimer;       // +0x50

    void Shutdown();          // 0x0083f680
};

// 0x008428b0  strip a filename, leaving the directory prefix (with separator)
extern "C" void __cdecl GetDirectoryName(const char* fullPath, eastl::string8* out);
// 0x0092f9e0  release the object stored in a watcher-map node
extern "C" void __fastcall WatcherNodeReleaseHelper(Watcher* watcher);

// ===========================================================================
// 0x00840250  EA::ArgScript::cFileParser::~cFileParser
// ===========================================================================
// @ 0x00840250
void __fastcall FileParser_dtor(cFileParser* self) {
    self->mpVtable0 = (void*)0x141b854;
    self->mpVtable4 = (void*)0x141b844;
    if (self->mFlag0c)
        self->Shutdown();

    self->mWatchers.Free(self->mWatchers.mpBuckets, self->mWatchers.mBucketCount);
    self->mWatchers.mSize = 0;
    if (self->mWatchers.mBucketCount > 1)
        EASTL_allocator_deallocate(self->mWatchers.mpBuckets);

    self->mSpecs.DestroyRange(self->mSpecs.mpBegin, self->mSpecs.mpEnd);
    FileSpec* specs = self->mSpecs.mpBegin;
    if (specs && allocation_owned(specs))
        EASTL_allocator_deallocate(specs);

    void* parser = self->mpParser;
    if (parser) {
        void** vt = *(void***)parser;
        ((void(__thiscall*)(void*))vt[1])(parser);
    }
    self->mpVtable4 = (void*)0x13eb394;
}

// ===========================================================================
// 0x00840340  EA::ArgScript::cFileParser::ClearFilePaths
// ===========================================================================
// @ 0x00840340
void __fastcall FileParser_ClearFilePaths(cFileParser* self) {
    WatcherNode** bucket = self->mWatchers.mpBuckets;
    WatcherNode* endNode = bucket[self->mWatchers.mBucketCount];
    WatcherNode* node = *bucket;
    while (!node)
        node = *++bucket;
    while (node != endNode) {
        WatcherNodeReleaseHelper(node->mpWatcher);
        node = node->mpNext;
        if (!node) {
            do {
                node = *++bucket;
            } while (!node);
        }
    }

    self->mWatchers.Free(self->mWatchers.mpBuckets, self->mWatchers.mBucketCount);
    self->mWatchers.mSize = 0;

    FileSpec* begin = self->mSpecs.mpBegin;
    FileSpec* end = self->mSpecs.mpEnd;
    for (FileSpec* spec = begin; spec < end; ++spec)
        spec->~FileSpec();
    self->mSpecs.mpEnd = begin;
}

// ===========================================================================
// 0x00840420  EA::ArgScript::cFileParser::AddFilePath
// ===========================================================================
// @ 0x00840420
void __fastcall FileParser_AddFilePath(cFileParser* self, int, const char* path, unsigned flags) {
    FileSpec spec;
    const char* pathEnd = path;
    while (*pathEnd)
        ++pathEnd;
    spec.mPath.assign(path, pathEnd);
    spec.mFlags = (unsigned short)flags;

    self->mSpecs.Add(&spec);

    unsigned watchFlags = flags & ~4u;
    if (watchFlags & 6u) {
        eastl::string8 dir;
        GetDirectoryName(path, &dir);

        WatcherNode* node = self->mWatchers.Find(dir);
        WatcherNode* endNode = self->mWatchers.mpBuckets[self->mWatchers.mBucketCount];
        if (node == endNode) {
            Watcher* watcher = (Watcher*)EASTL_allocator_allocate(
                0x244, g_allocName, 0, 0, g_allocFile, 0x244);
            if (watcher) {
                watcher->Construct();
                watcher->mpVtable = (void*)0x141b838;
                watcher->mRefCount = 0;
            }
            if (watcher)
                ++watcher->mRefCount;

            if (watcher) {
                watcher->Setup();
                watcher->SetOwner(self, (void*)0x83f580);

                eastl::string8 watchedPath;
                watchedPath.assign(spec.mPath.mpBegin, spec.mPath.mpEnd);
                watcher->SetPath(watchedPath.mpBegin);
                watcher->SetModeA(8);
                watcher->SetModeB(5);
                watcher->Start();

                Watcher* value = watcher;
                self->mWatchers.Insert(dir, &value);

                if (--watcher->mRefCount == 0) {
                    watcher->mRefCount = 1;
                    void** vt = *(void***)watcher;
                    ((void(__thiscall*)(Watcher*, int))vt[0])(watcher, 1);
                }
            }
        }
    }

    self->mFlag28 = 1;
}

// ===========================================================================
// 0x00840700  EA::ArgScript::cFileParser::cFileParser
// ===========================================================================
// @ 0x00840700
cFileParser* __fastcall FileParser_ctor(cFileParser* self) {
    self->mpVtable4 = (void*)0x13eb384;
    self->mpVtable0 = (void*)0x141b854;
    self->mpVtable4 = (void*)0x141b844;
    self->mRefCount = 0;
    self->mFlag0c = 0;
    self->mpParser = 0;
    self->mSpecs.mpBegin = 0;
    self->mSpecs.mpEnd = 0;
    self->mSpecs.mpCapacity = 0;
    self->mFloat3c = 1.0f;
    self->mFlag28 = 0;
    self->mFlag29 = 0;
    self->mFloat40 = 2.0f;
    self->mWatchers.mBucketCount = 1;
    self->mWatchers.mpBuckets = (WatcherNode**)gEmptyWatcherBuckets;
    self->mWatchers.mSize = 0;
    self->mField44 = 0;
    self->mTimer.Init(5, false);
    return self;
}

// ===========================================================================
// 0x008409f0  duplicate/split a string around a separator name
// ===========================================================================
// @ 0x008409f0
eastl::string8* __cdecl StringConvert(eastl::string8* out, eastl::string8* in, const char* name) {
    unsigned len = (unsigned)(in->mpEnd - in->mpBegin);
    unsigned allocSize = len + 1;
    char* buffer;
    char* capacity;
    if (allocSize > 1) {
        buffer = (char*)EASTL_allocator_allocate(allocSize, g_allocName, 0, 0, g_allocFile, 0xd1);
        capacity = buffer + allocSize;
    } else {
        buffer = gEmptyString;
        capacity = gEmptyStringCap;
    }

    memcpy(buffer, in->mpBegin, len);
    buffer[len] = 0;

    eastl::string8 temp;
    temp.mpBegin = buffer;
    temp.mpEnd = buffer + len;
    temp.mpCapacity = capacity;

    if (name && name[0]) {
        int index = temp.find(name, 0);
        if (index == -1) {
            out->assign(temp);
        } else {
            in->erase(0, (unsigned)index + 1);
            temp.erase((unsigned)index, ~0u);
            out->assign(temp);
        }
    } else {
        out->mpBegin = 0;
        out->mpEnd = 0;
        out->mpCapacity = 0;
        out->resize(allocSize);
        memcpy(out->mpBegin, buffer, len);
        out->mpEnd = out->mpBegin + len;
        out->mpEnd[0] = 0;
    }

    temp.~string8();
    return out;
}

// ===========================================================================
// 0x00840cc0  copy a C string into a string8, lower-cased
// ===========================================================================
// @ 0x00840cc0
void __cdecl MakeCaseInsensitive2(const char* p, eastl::string8* s) {
    const char* pEnd = p;
    while (*pEnd)
        ++pEnd;
    unsigned len = (unsigned)(pEnd - p);

    unsigned current = (unsigned)(s->mpEnd - s->mpBegin);
    if (len < current) {
        char* newEnd = s->mpBegin + len;
        if (newEnd != s->mpEnd) {
            memmove(newEnd, s->mpEnd, (unsigned)(s->mpEnd - newEnd) + 1);
            s->mpEnd += newEnd - s->mpEnd;
        }
    } else if (len > current) {
        s->append(len - current, 0);
    }

    for (unsigned i = 0; i < (unsigned)(s->mpEnd - s->mpBegin); ++i, ++p)
        s->mpBegin[i] = (char)tolower(*p);
}

// ===========================================================================
// 0x00840ec0  EA::ArgScript::StripCommentsAndWhiteSpace
// ===========================================================================
// @ 0x00840ec0
bool __cdecl StripCommentsAndWhiteSpace(const char* text, eastl::string8* out, int* depth) {
    if (out->mpBegin != out->mpEnd) {
        out->mpBegin[0] = 0;
        out->mpEnd = out->mpBegin;
    }

    const char* p = text;
    const char* end = text;
    while (*end)
        ++end;

    if (!depth || *depth == 0) {
        while (p < end && isspace((unsigned char)*p))
            ++p;
        while (end > p && isspace((unsigned char)end[-1]))
            --end;
    }

    for (;;) {
        const char* found = (const char*)memchr(p, '#', (unsigned)(end - p));
        if (!found)
            break;

        const char* marker = found + 1;
        if (marker == end) {
            end = found;
            break;
        }

        char kind = *marker;
        if (kind == '<') {
            if ((!depth || *depth == 0) && found > p)
                out->append(p, found);
            if (depth)
                ++*depth;
        } else if (kind == '>') {
            if (depth) {
                if (*depth == 0)
                    throw cError("'#>' without matching '#<'");
                --*depth;
                if (*depth == 0)
                    p = marker + 1;
            }
        } else {
            end = found;
            break;
        }
        p = marker;
    }

    if ((!depth || *depth == 0) && end != p)
        out->append(p, end);

    return out->mpBegin != out->mpEnd;
}

// ===========================================================================
// 0x00841000  EA::ArgScript::Output
// ===========================================================================
extern char gOutputBuf[];  // 0x0164ff80
// @ 0x00841000
void __cdecl Output(int* expr, const char* fmt, ...) {
    if (!expr)
        return;

    void* sink = ((void*(__thiscall*)(int*))(*(void***)expr)[0xc4 / 4])(expr);
    if (!sink)
        return;

    char* args = (char*)&fmt + 4;
    int written = Vsnprintf8(gOutputBuf, 0x400, fmt, args);

    if ((unsigned)written < 0x400u) {
        unsigned len = (unsigned)strlen(gOutputBuf);
        ((void(__thiscall*)(void*, const char*, unsigned))(*(void***)sink)[0x38 / 4])(
            sink, gOutputBuf, len);
    } else {
        eastl::string8 message;
        message.append_sprintf_va_list(fmt, args);
        ((void(__thiscall*)(void*, const char*, unsigned))(*(void***)sink)[0x38 / 4])(
            sink, message.mpBegin, (unsigned)(message.mpEnd - message.mpBegin));
    }
}
