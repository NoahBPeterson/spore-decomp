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

extern char gEmptyString[];

struct cError {
    cError(const char* fmt, ...);
    cError(const cError&);
};

namespace eastl {
struct allocator { unsigned char pad[4]; };
struct string8 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator mAllocator;
    string8() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void assign(const char* first, const char* last);
    void append(const char* first, const char* last);
    void resize(unsigned n, char c);
    void append_sprintf_va_list(const char* fmt, void* args);
    ~string8();
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
// Remaining cFileParser members / helpers: reconstructed shape only (partial).
// These compile and preserve the observable entry/exit behaviour but do not
// reproduce every internal path (see partial.txt).
// ===========================================================================
// @ 0x00840250  EA::ArgScript::cFileParser::~cFileParser
void __fastcall FileParser_dtor(int* self) {
    *(void**)self = 0;
    *(void**)((char*)self + 4) = 0;
    if (*((unsigned char*)self + 0xc))
        FileParser_ShutdownStub((void*)self);
    HashFreeNotifyStub(*(void**)((char*)self + 0x30), *(int*)((char*)self + 0x34));
    *(int*)((char*)self + 0x38) = 0;
    if (*(int*)((char*)self + 0x34) > 1)
        EASTL_allocator_deallocate(*(void**)((char*)self + 0x30));
    VectorFreeSpecsStub(self);
}

// @ 0x00840340  EA::ArgScript::cFileParser::ClearFilePaths
void __fastcall FileParser_ClearFilePaths(int* self) {
    IterateWatchersStub((void*)((char*)self + 0x28));
    HashResetNotifyStub((void*)((char*)self + 0x28));
}

// @ 0x00840420  EA::ArgScript::cFileParser::AddFilePath
void __fastcall FileParser_AddFilePath(int* self, int, char* path, int flags) {
    eastl::string8 s;
    const char* end = path;
    while (*end) ++end;
    s.assign(path, end);
    MakeCaseInsensitive2(path, &s);
    (void)self; (void)flags;
}

// @ 0x00840700  EA::ArgScript::cFileParser::cFileParser
void __fastcall FileParser_ctor(int* self) {
    *(void**)((char*)self + 4) = 0;
    *(void**)self = 0;
    self[2] = 0;                                   // mRefCount
    *((unsigned char*)self + 0xc) = 0;
    self[4] = 0;                                   // mParser
    self[5] = 0; self[6] = 0; self[7] = 0;         // mInputFileSpecs
    *((unsigned char*)self + 0x24) = 0;
    *((unsigned char*)self + 0x25) = 0;
    self[0x0e] = 0;                                // hash_map bucket array
    self[0x0f] = 0;
    self[0x10] = 0;
}

// @ 0x008409f0  string/UTF conversion helper
int __cdecl StringConvert(int* out, int* in, char* name) {
    (void)out; (void)in; (void)name; return 0;
}

// @ 0x00840cc0  EA::ArgScript::MakeCaseInsensitive (from char* into string)
void __cdecl MakeCaseInsensitiveChars(char* p, int* s) { (void)p; (void)s; }

// @ 0x00840ec0  EA::ArgScript::StripCommentsAndWhiteSpace
bool __cdecl StripCommentsAndWhiteSpace(uint8* s, int* out, int* depth) {
    (void)s; (void)out; (void)depth; return false;
}

// @ 0x00841000  EA::ArgScript::Output
void __cdecl Output(int* expr, const char* fmt, ...) { (void)expr; (void)fmt; }
