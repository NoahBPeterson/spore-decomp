// w1g1 slice s0050c6c0 -- small vector/lane helpers plus vector<float>::operator=.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE where floats are copied with movss.

typedef unsigned int uint32_t;

// @ 0x0050cfb0  (2-component subtract: out = a - b)
float* __cdecl Sub2(float* out, float* a, float* b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    return out;
}

// @ 0x0050d020  (2-component scale: out *= s)
float* __cdecl Scale2(float* out, float* s)
{
    out[0] = out[0] * s[0];
    out[1] = out[1] * s[0];
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x0050cec0  (fixed_vector<float,400> constructor)
// ---------------------------------------------------------------------------
void FixedVecInit(void* p);   // 0x0050e310

int* __fastcall VecConstruct(int* p, int param)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[4] = (int)(p + 6);
    p[1] = (int)(p + 6);
    p[0] = p[1];
    p[2] = p[0] + 0x640;
    FixedVecInit(&param);
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x0050d4e0  eastl::vector<float,sp_vector_allocator>::operator=
// ---------------------------------------------------------------------------
void ea_delete(void* p);
uint32_t GrowCopy(uint32_t n, uint32_t* first, uint32_t* last);   // 0x0042e5b0
void MoveInto(void* dst, void* src, int bytes);                   // vector<bool>::DoInsertValue

uint32_t* __fastcall FloatVec_Assign(uint32_t* self, uint32_t* x)
{
    if (x != self) {
        uint32_t n = (uint32_t)((int)x[1] - (int)*x) >> 2;
        if ((uint32_t)(((int)self[2] - (int)*self) >> 2) < n) {
            uint32_t pNew = GrowCopy(n, (uint32_t*)*x, (uint32_t*)x[1]);
            for (uint32_t p = *self; p < self[1]; p += 4) {}
            if (*self != 0 && *(int*)(*self - 4) != 0)
                ea_delete((void*)*self);
            *self = pNew;
            self[2] = *self + n * 4;
        } else if ((uint32_t)(((int)self[1] - (int)*self) >> 2) < n) {
            MoveInto((void*)*self, (void*)*x, (int)(x[1] - *x));
        } else {
            for (uint32_t d = *self, s = *x; d < self[1]; d += 4, s += 4)
                *(uint32_t*)d = *(uint32_t*)s;
        }
        self[1] = *self + n * 4;
    }
    return self;
}

// EA 6-argument operator new (0x00f473a0)
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);

// ---------------------------------------------------------------------------
// Skin::Append(const Skin& other)  (thiscall, ret 4) -- Claude-coined name.
//
// Appends another skinning mesh ("Skin", see slice s00507670) to this one, rebasing the other's
// indices by the sizes this one had before:  every vector member of `other` is concatenated
// (+0x08 / +0x1c / +0x30 / +0x44 / +0x1a4 / +0xa8 via range inserts, +0x190 likewise), the index
// vectors (+0x58 / +0x6c / +0x80 / +0x94) are grown and filled with other's entries plus the
// old vertex / normal / uv counts, the per-vertex +0xa8 set and the 8-byte pairs at +0x124 are
// shifted, +0x138 is grown and filled with -1, and the Container pieces (+0xe4, owned pointers) are
// deep-copied with their triangle indices and base offset rebased.  Finally the other's +0x110 words
// are appended minus the old piece count.
//
// Flags: /Od /Ob1 /MD /Gy /TP.
// ---------------------------------------------------------------------------
struct AppendTag {};

struct Elem12 { float a, b, c; };
struct Elem8 { unsigned a, b; };
struct Elem20 { unsigned w[5]; };

struct Vec12 {                           // +0x08 / +0x1c
    Elem12* mpBegin; Elem12* mpEnd; Elem12* mpCap; int mAlloc; int pad;
    void insert(Elem12* where, Elem12* first, Elem12* last) { insert(where, first, last, AppendTag()); }
    void insert(Elem12* where, Elem12* first, Elem12* last, AppendTag t);   // 0x0050f180 (ret 0x10)
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
struct Vec8 {                            // +0x30, +0x124
    Elem8* mpBegin; Elem8* mpEnd; Elem8* mpCap; int mAlloc; int pad;
    void insert(Elem8* where, Elem8* first, Elem8* last) { insert(where, first, last, AppendTag()); }
    void insert(Elem8* where, Elem8* first, Elem8* last, AppendTag t);       // 0x0050f1b0 (ret 0x10)
    void resize(unsigned n);                                                 // 0x004cd440 (ret 4)
};
struct Vec20 {                           // +0x44
    Elem20* mpBegin; Elem20* mpEnd; Elem20* mpCap; int mAlloc; int pad;
    void insert(Elem20* where, Elem20* first, Elem20* last) { insert(where, first, last, AppendTag()); }
    void insert(Elem20* where, Elem20* first, Elem20* last, AppendTag t);    // 0x0050f1e0 (ret 0x10)
};
struct VecU32 {                          // uint vectors: +0x58 +0x6c +0x80 +0x94 +0xa8 +0x110 +0x138 +0x1a4
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap; int mAlloc; int pad;
    void insert(unsigned* where, unsigned* first, unsigned* last) { insert(where, first, last, AppendTag()); }
    void insert(unsigned* where, unsigned* first, unsigned* last, AppendTag t);   // 0x004778c0 (ret 0x10)
    void resize(unsigned n);                                                 // 0x004cd3c0 (ret 4)
    void resize(unsigned n, const int& fill);                                // 0x004746c0 (ret 8)
    void push_back(const unsigned& v);                                       // 0x00454860 (ret 4)
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
struct VecAny {                          // +0x190
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap; int mAlloc; int pad;
    void insert(unsigned* where, unsigned* first, unsigned* last);           // 0x0050e5c0 (ret 0xc)
};

struct SmallVec {                        // vector inside a Container piece (+0x08), out-of-line size()
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap; int mAlloc; int pad;
    unsigned size() const;                                                   // 0x004746a0
    unsigned& operator[](unsigned i) { return mpBegin[i]; }
};

struct Container {                       // 0x94-byte piece ("Skinner" allocation)
    int m00, m04;
    SmallVec m08;
    char rest[0x94 - 0x08 - sizeof(SmallVec)];
    Container(const Container& src);                                         // 0x00508320 (ret 4)
};

struct PieceVec {                        // +0xe4: vector of owned Container*
    Container** mpBegin; Container** mpEnd; Container** mpCap; int mAlloc; int pad;
    bool empty() const;                                                      // 0x00526430
    void resize(unsigned n);                                                 // 0x004cd3c0 (ret 4)
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    Container*& operator[](unsigned i) { return mpBegin[i]; }
};

struct Skin {
    char pad0[8];
    Vec12 m08;          // +0x08
    Vec12 m1c;          // +0x1c
    Vec8  m30;          // +0x30
    Vec20 m44;          // +0x44
    VecU32 m58, m6c;    // +0x58 +0x6c
    VecU32 m80, m94;    // +0x80 +0x94
    VecU32 ma8;         // +0xa8
    char padbc[0xe4 - 0xbc];
    PieceVec me4;       // +0xe4
    char padf8[0x110 - 0xf8];
    VecU32 m110;        // +0x110
    Vec8   m124;        // +0x124
    VecU32 m138;        // +0x138
    char pad14c[0x190 - 0x14c];
    VecAny m190;        // +0x190
    VecU32 m1a4;        // +0x1a4

    void Append(const Skin& other);
};

// @ 0x0050c6c0
void Skin::Append(const Skin& other)
{
    int nVerts = (int)(m08.mpEnd - m08.mpBegin);
    int nNorms = (int)(m1c.mpEnd - m1c.mpBegin);
    int nUvs = (int)(m30.mpEnd - m30.mpBegin);
    int nPieces = (int)(me4.mpEnd - me4.mpBegin);
    unsigned nIdx = (unsigned)(m58.mpEnd - m58.mpBegin);
    unsigned nTris = nIdx / 3;
    int oVerts = (int)(other.m08.mpEnd - other.m08.mpBegin);
    int oIdx = (int)(other.m58.mpEnd - other.m58.mpBegin);
    int totalIdx = (int)(m58.mpEnd - m58.mpBegin) + oIdx;

    m08.insert(m08.mpEnd, other.m08.mpBegin, other.m08.mpEnd);
    m1a4.insert(m1a4.mpEnd, other.m1a4.mpBegin, other.m1a4.mpEnd);
    m1c.insert(m1c.mpEnd, other.m1c.mpBegin, other.m1c.mpEnd);
    m30.insert(m30.mpEnd, other.m30.mpBegin, other.m30.mpEnd);
    m44.insert(m44.mpEnd, other.m44.mpBegin, other.m44.mpEnd);
    ma8.insert(ma8.mpEnd, other.ma8.mpBegin, other.ma8.mpEnd);

    m124.resize((unsigned)(m30.mpEnd - m30.mpBegin));
    for (unsigned i = 0, n = (unsigned)(other.m124.mpEnd - other.m124.mpBegin); i < n; i++) {
        m124.mpBegin[nUvs + i].a = other.m124.mpBegin[i].a + nPieces;
        m124.mpBegin[nUvs + i].b = other.m124.mpBegin[i].b + nVerts;
    }

    m58.resize(totalIdx);
    m6c.resize(totalIdx);
    m80.resize(totalIdx);
    m94.resize(totalIdx);
    for (unsigned i = 0; i < (unsigned)oIdx; i++) {
        m58.mpBegin[nIdx + i] = other.m58.mpBegin[i] + nVerts;
        m6c.mpBegin[nIdx + i] = other.m6c.mpBegin[i] + nNorms;
        m80.mpBegin[nIdx + i] = other.m80.mpBegin[i] + nUvs;
        m94.mpBegin[nIdx + i] = nIdx + other.m94.mpBegin[i];
    }

    ma8.resize((unsigned)(int)(m08.mpEnd - m08.mpBegin) + oVerts);
    for (unsigned i = 0; i < (unsigned)oVerts; i++)
        ma8.mpBegin[nVerts + i] = other.ma8.mpBegin[i] + nIdx;

    if (!other.me4.empty()) {
        int minusOne = -1;
        m138.resize(totalIdx, minusOne);
        me4.resize(other.me4.size() + nPieces);
        for (unsigned j = 0, n = other.me4.size(); j < n; j++) {
            Container* c = new("Skinner", 0, 0, 0, 0) Container(*other.me4.mpBegin[j]);
            for (unsigned k = 0; k < c->m08.size(); k++)
                c->m08.mpBegin[k] = c->m08.mpBegin[k] + nTris;
            c->m00 = c->m00 + nPieces;
            me4.mpBegin[nPieces + j] = c;
        }
        for (unsigned m = 0, n = (unsigned)oIdx / 3; m < n; m++) {
            unsigned v = other.m110.mpBegin[m] - nPieces;
            m110.push_back(v);
        }
    }
    m190.insert(m190.mpEnd, other.m190.mpBegin, other.m190.mpEnd);
}

void __fastcall ProcessD(int self) { (void)self; }
