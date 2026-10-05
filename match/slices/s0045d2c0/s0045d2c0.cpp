// Slice s0045d2c0: Collada float-array / <node> exporter helpers, plus EASTL vector
// (0x40-byte element) and string-sprintf machinery from the same /Od editor module.
// Flags: /Od /Ob1 /MD /Gy /TP; the Matrix44 float copies also want /arch:SSE /fp:fast.
#include "types.h"

// ---- out-of-slice helpers (addresses are relocation-masked by cmpobj) ----
extern "C" void WriterFmt(int out, const char* fmt, ...);   // 0x45cd90 cdecl varargs
extern "C" void WriterStr(int out, const char* s);          // 0x45cd40 cdecl
extern "C" void* RecallocCore(void* m, unsigned int count, unsigned int size,
                              unsigned int align, unsigned int offset,
                              unsigned int a6, unsigned int a7);          // 0x45d3e0
extern "C" void EaDeallocate(void* p);                       // 0xf47380
extern "C" int  Vsnprintf8(char* buf, unsigned int count, const char* fmt, void* args); // 0x938400
extern "C" void FUN_0045df90(int a, int b, void* out);       // 0x45df90
extern char g_sentinel;                                      // 0x01667bac
extern char g_table;                                         // first dword == 0x01667bac

__forceinline void* operator new(unsigned int, void* p) { return p; }

void VecWriterLines(int out, int n);                         // 0x45d6b0 (defined below)

// =====================================================================
// @ 0x45d3b0  __aligned_offset_recalloc
// =====================================================================
extern "C" void* __cdecl __aligned_offset_recalloc(void* m, unsigned int count, unsigned int size,
                                                   unsigned int align, unsigned int offset)
{
    return RecallocCore(m, count, size, align, offset, (unsigned int)-1, 3);
}

// =====================================================================
// @ 0x45d6b0  write `n` indentation lines ("  ")
// =====================================================================
void VecWriterLines(int out, int n)
{
    for (int i = 0; i < n; i = i + 1) {
        WriterStr(out, "  ");
    }
    return;
}

// =====================================================================
// @ 0x45daf0 / 0x45db40  vector deallocation helpers
// =====================================================================
struct RawVec8 {
    char* begin;
    char* end;
    char* cap;
    void dealloc();
};

void RawVec8::dealloc()
{
    if (begin != 0) {
        unsigned int n12 = (unsigned int)(((cap - begin) >> 3) << 3);
        char* n21 = begin;
        if (*(int*)(n21 - 4) != 0) {
            void* t38 = n21;
            EaDeallocate(t38);
        }
    }
    return;
}

struct RawVec64 {
    char* begin;
    char* end;
    char* cap;
    void dealloc();
};

void RawVec64::dealloc()
{
    if (begin != 0) {
        unsigned int n12 = (unsigned int)(((cap - begin) >> 6) << 6);
        char* n21 = begin;
        if (*(int*)(n21 - 4) != 0) {
            void* t38 = n21;
            EaDeallocate(t38);
        }
    }
    return;
}

// =====================================================================
// @ 0x45dac0  init three pointers
// =====================================================================
struct TwoPtr {
    void* vt;
    void* f4;
    void* f8;
    void Init();
};

void TwoPtr::Init()
{
    vt = &g_table;
    f4 = vt;
    f8 = (char*)vt + 2;
    return;
}

// =====================================================================
// @ 0x45dca0  Matrix44 copy ctor
// =====================================================================
struct Matrix44 {
    float m[16];
    Matrix44();
    Matrix44(const Matrix44& o);
};

Matrix44::Matrix44()
{
}

Matrix44::Matrix44(const Matrix44& o)
{
    for (int i = 0; i < 4; i = i + 1) {
        float a = o.m[i * 4 + 0];
        float b = o.m[i * 4 + 1];
        float c = o.m[i * 4 + 2];
        float d = o.m[i * 4 + 3];
        m[i * 4 + 0] = a;
        m[i * 4 + 1] = b;
        m[i * 4 + 2] = c;
        m[i * 4 + 3] = d;
    }
}

// =====================================================================
// @ 0x45dc00  uninitialized copy of a Matrix44 range
// =====================================================================
Matrix44* CopyMatrixRange(char* first, char* last, Matrix44* dest)
{
    Matrix44* d = dest;
    for (char* cur = first; cur != last; cur = cur + 0x40) {
        if (d != 0) {
            new (d) Matrix44(*(const Matrix44*)cur);
        }
        d = d + 1;
    }
    return d;
}

// =====================================================================
// @ 0x45de10  string SprintfCore
// =====================================================================
struct Str {
    char* begin;
    char* end;
    char* cap;
    void grow(unsigned int n);                          // 0x45ebd0
    Str* SprintfCore(const char* fmt, void* args);
    void ResetAndFormat(const char* fmt, void* args);   // 0x45da50
};

Str* Str::SprintfCore(const char* fmt, void* args)
{
    int used = (int)(end - begin);
    int len;
    if (begin == &g_sentinel) {
        len = Vsnprintf8(end, 0, fmt, args);
    } else {
        len = Vsnprintf8(end, (unsigned int)(cap - end), fmt, args);
    }
    if (len < (int)(cap - end)) {
        if (len < 0) {
            unsigned int cap2 = (unsigned int)((end - begin) * 2);
            unsigned int cap7 = 7;
            unsigned int* chosen = cap2 < 8 ? &cap7 : &cap2;
            for (unsigned int c = *chosen; len < 0 && c < 1000000; c = c << 1) {
                grow(c);
                len = Vsnprintf8(begin + used, (c + 1) - used, fmt, args);
            }
        }
    } else {
        grow(used + len);
        len = Vsnprintf8(begin + used, len + 1, fmt, args);
    }
    if (len >= 0) {
        end = begin + used + len;
    }
    return this;
}

void Str::ResetAndFormat(const char* fmt, void* args)
{
    end = begin;
    SprintfCore(fmt, args);
    return;
}

void Str::grow(unsigned int) {}

// =====================================================================
// @ 0x45da80  small wrapper around the big node function
// =====================================================================
int FUN_0045da80(int a, int b)
{
    char local[4];
    FUN_0045df90(a, b, local);
    return a;
}

// =====================================================================
// @ 0x45d6f0  SSO string ctor (buffer at this+0x14, capacity 0x300)
// =====================================================================
struct BigStr {
    char* begin;
    char* end;
    char* cap;
    char  pad[8];
    char  buf[0x300];
    void  InitHelper(void* out);        // 0x422cf0
    BigStr* Ctor();
};

BigStr* BigStr::Ctor()
{
    char* b = (char*)this + 0x14;
    void* tmp;
    InitHelper(&tmp);
    end = (char*)this + 0x14;
    begin = end;
    cap = begin + 0x300;
    *begin = 0;
    return this;
}

// =====================================================================
// @ 0x45d2c0  float-array element writer
// =====================================================================
void WriteFloatArray(int out, const char* name, const float* data, unsigned int count)
{
    WriterFmt(out, "    <source id=\"%s\">\n      <float_array id=\"%s-array\" count=\"%d\">\n        ",
              name, name, count);
    unsigned int i = 0;
    for (; i + 3 < count; i = i + 4) {
        WriterFmt(out, "%f %f %f %f ", data[i], data[i + 1], data[i + 2], data[i + 3]);
    }
    for (; i < count; i = i + 1) {
        WriterFmt(out, "%f ", data[i]);
    }
    WriterFmt(out,
        "\n      </float_array>\n      <technique_common>\n        <accessor source=\"#%s-array\" count=\"%d\" stride=\"1\">\n          <param name=\"WEIGHT\" type=\"float\"/>\n        </accessor>\n      </technique_common>\n    </source>\n",
        name, count);
    return;
}

// =====================================================================
// @ 0x45d3e0  recursive Collada <node> writer
// =====================================================================
void WriteNode(int out, char** names, int* parents, Matrix44* mats,
               unsigned int count, int parentIdx, int depth)
{
    Matrix44 tmp;
    unsigned int i;
    for (i = 0; i < count; i = i + 1) {
        if (parents[i] != parentIdx) {
            continue;
        }
        tmp = mats[i];
        VecWriterLines(out, depth);
        WriterFmt(out, "<node name=\"%s%d\" sid=\"%s%d\" id=\"%s%d\" type=\"JOINT\">\n",
                  names[i], i, names[i], i, names[i], i);
        VecWriterLines(out, depth);
        WriterFmt(out, "  <matrix>%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f</matrix>\n",
                  tmp.m[0], tmp.m[1], tmp.m[2], tmp.m[3],
                  tmp.m[4], tmp.m[5], tmp.m[6], tmp.m[7],
                  tmp.m[8], tmp.m[9], tmp.m[10], tmp.m[11],
                  tmp.m[12], tmp.m[13], tmp.m[14], tmp.m[15]);
        WriteNode(out, names, parents, mats, count, (int)i, depth + 1);
        VecWriterLines(out, depth);
        WriterStr(out, "</node>\n");
    }
    return;
}

// =====================================================================
// @ 0x45d790  vector<Elem(0x40)>::assign
// =====================================================================
struct Elem {
    char b[0x40];
};

struct Vec64 {
    Elem* begin;
    Elem* end;
    Elem* cap;
    void  assign(const Vec64& o);
    Elem* reallocate(unsigned int n, Elem* first, Elem* last);   // 0x45db90
};

void Vec64::assign(const Vec64& o)
{
    if (&o == this) {
        return;
    }
    unsigned int n = (unsigned int)(o.end - o.begin);
    if ((unsigned int)(cap - begin) < n) {
        Elem* newp = reallocate(n, o.begin, o.end);
        for (Elem* p = begin; p < end; p = p + 1) {
        }
        RawVec64 rv;
        rv.begin = (char*)begin;
        rv.end = (char*)end;
        rv.cap = (char*)cap;
        rv.dealloc();
        begin = newp;
        cap = begin + n;
    } else if ((unsigned int)(end - begin) < n) {
        Elem* dst = begin;
        Elem* src = o.begin;
        Elem* stop = o.begin + (end - begin);
        for (; src != stop; src = src + 1, dst = dst + 1) {
            *dst = *src;
        }
        CopyMatrixRange((char*)src, (char*)o.end, (Matrix44*)end);
    } else {
        Elem* dst = begin;
        for (Elem* src = o.begin; src != o.end; src = src + 1, dst = dst + 1) {
            *dst = *src;
        }
        for (Elem* p = dst; p < end; p = p + 1) {
        }
    }
    end = begin + n;
    return;
}
