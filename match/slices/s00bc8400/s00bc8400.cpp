// slice s00bc8400 -- SP::cHierGrid (hierarchical grid), core maintenance functions:
// entry creation, per-object dispatch, level walk, random shuffle and index validation.
//
// Compile: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// Layouts are read off the machine code and cross-checked against the
// neighbouring s00703700 slice (same cGrid level vector).

// ===========================================================================
// IRefCount: only the two slots this slice touches.
// ===========================================================================
struct IRefCount {
    virtual void AddRef();          // vtbl+0x00
    virtual void Release();         // vtbl+0x04
};

// ===========================================================================
// One rectangular level chunk: stride 0x88 (see cHierGrid::Init/Resize).
// ===========================================================================
struct cGrid {
    unsigned mLevel;    // +0x00
    unsigned m04;       // +0x04
    unsigned mSlot;     // +0x08
    float    mCellSize; // +0x0c
    float    mHalf;     // +0x10
    unsigned mInUse;    // +0x14  (bit 30 set => occupied)
    unsigned m18;       // +0x18
    unsigned mCells;    // +0x1c
    unsigned m20;       // +0x20
    unsigned mStamp;    // +0x24
    float    mRadius;   // +0x28
    char     m2c[0x5c];

    unsigned CreateEntry(unsigned a, void* b, float c);
};

// ===========================================================================
// The queue object that cHierGrid+0x00 points at: a vector of 0x3c-stride level
// records at +0x00 and the entry table at +0x1c.
// ===========================================================================
struct cGridQueue {
    char*    mBeg;      // +0x00
    char*    mEnd;      // +0x04
    char*    mCap;      // +0x08
    unsigned m0c;       // +0x0c
    unsigned m10;       // +0x10
    unsigned m14;       // +0x14
    unsigned m18;       // +0x18
    char*    mTable;    // +0x1c

    unsigned Acquire(void* out);    // 0x00bc7e80 (ret 4)
};

// ===========================================================================
// cHierGrid: offsets used in this slice.
//   +0x00  cGridQueue* mQueue
//   +0x3d  cell record table (unsigned index -> 0x10-byte record)
//   +0x41  mask
//   +0x45  pointer to a 2-dword key
//   +0x4d/+0x51/+0x55  swap triple
//   +0x7c/+0x80        slot count / slot array
// ===========================================================================
struct cHierGrid {
    cGridQueue* mQueue;     // +0x00
    char        m04[0x39];  // +0x04 .. +0x3c
    char*       mCellTbl;   // +0x3d
    char        m41;        // +0x41 (mask lives here; byte access in source)
    char        m42[3];     // +0x42 .. +0x44
    unsigned*   mKey;       // +0x45
    char        m49[4];     // +0x49 .. +0x4c
    unsigned    m4d;        // +0x4d
    unsigned    m51;        // +0x51
    unsigned    m55;        // +0x55
    char        m59[0x23];  // +0x59 .. +0x7b
    unsigned    m7c;        // +0x7c
    unsigned    m80;        // +0x80

    unsigned NewEntry(unsigned a2, unsigned* src, unsigned a4, float radius,
                      IRefCount* p1, IRefCount* p2);
};

// The mask operand block FitsMask is written for (the original receiver is at
// cHierGrid + 0x40, i.e. a sub-object starting at its own +0x00).
struct GridMask {
    unsigned m00, m04, m08, m0c;
    char     m10;
    char     m11[3];
    unsigned m14;
    unsigned m18;
    unsigned m1c;
    char     m20;
    char     m21[3];
    unsigned m24;
    unsigned m28;
    unsigned m2c;

    bool FitsMask(unsigned m1, unsigned m2);
};

// ===========================================================================
// Foreign callees (relocations masked: only convention + arity matter).
// ===========================================================================
// @ 0x00f473a0
void* __cdecl EA_new(int size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line);
// @ 0x00f47380
void __cdecl EA_delete(void* p);
// @ 0x009362b0
unsigned __cdecl GenerateUInt32(unsigned n);
// @ 0x011e073e  (operator new[] used as an auditing allocator: (owner, tag, size))
void* __cdecl Grid_NewArray(void* owner, unsigned tag, unsigned size);

// ===========================================================================
// @ 0x00bc8400
unsigned __thiscall cHierGrid::NewEntry(unsigned a2, unsigned* src, unsigned a4, float radius,
                                       IRefCount* p1, IRefCount* p2)
{
    void* tmp1 = 0;
    void* tmp2 = 0;
    unsigned token = mQueue->Acquire(&tmp1);

    if (tmp2 != 0)
        (*(void (***)(void))tmp2)[1]();
    if (tmp1 != 0)
        (*(void (***)(void))tmp1)[1]();

    cGridQueue* q = mQueue;
    unsigned have = (unsigned)((q->mEnd - q->mBeg) / 0x3c);
    if ((token & 0xbfffffff) < have) {
        char* slot = q->mBeg + (token * 0x10 - (token & 0xbfffffff)) * 4;
        if ((int)*(unsigned*)slot >= 0) {
            char* rec = slot + 4;
            if (rec != 0) {
                *(unsigned*)rec = token | 0x40000000;
                *(unsigned*)(rec + 4) =
                    ((cGrid*)q->mTable)->CreateEntry(a4, src, radius);
                *(unsigned*)(rec + 8) = a2;
                *(unsigned*)(rec + 0x14) = *(unsigned*)((char*)src + 4);
                *(unsigned*)(rec + 0x18) = *(unsigned*)((char*)src + 8);
                *(float*)(rec + 0x10) = *(float*)src;
                *(unsigned*)(rec + 0x1c) = *(unsigned*)((char*)src + 0xc);
                *(unsigned*)(rec + 0xc) = *(unsigned*)((char*)src + 0x10);
                IRefCount* old = *(IRefCount**)(rec + 0x20);
                if (p1 != old) {
                    if (p1 != 0)
                        p1->AddRef();
                    *(IRefCount**)(rec + 0x20) = p1;
                    if (old != 0)
                        old->Release();
                }
                IRefCount* old2 = *(IRefCount**)(rec + 0x24);
                if (p2 != old2) {
                    if (p2 != 0)
                        p2->AddRef();
                    *(IRefCount**)(rec + 0x24) = p2;
                    if (old2 != 0)
                        old2->Release();
                }
                *(unsigned*)(rec + 0x28) = 0;
                *(unsigned*)(rec + 0x2c) = 0;
                *(unsigned*)(rec + 0x30) = 0;
                *(unsigned*)(rec + 0x34) = 0;
            }
        }
    }
    return token | 0x40000000;
}

// ===========================================================================
// @ 0x00bc8550  (the self in ecx and the trailing reloc belong to the caller)
void* __fastcall Grid_AllocThunk(void* self)
{
    return Grid_NewArray(self, 0xff, 0x418);
}

// ===========================================================================
// @ 0x00bc8570  (cdecl: caller does add esp,0x18)
void __cdecl Grid_Notify(char flag, char* obj, char* rec, unsigned p4, double d5)
{
    if (flag == 0)
        return;
    void (*fn)(unsigned, double, unsigned, unsigned, char*) =
        *(void (**)(unsigned, double, unsigned, unsigned, char*))(obj + 0xc);
    if (fn == 0)
        return;
    fn(p4, d5, *(unsigned*)(rec + 0x41), *(unsigned*)(rec + 0x4d), obj);
}

// ===========================================================================
// @ 0x00bc85b0  (cdecl: caller does add esp,0x18)
void __cdecl Grid_WalkInsert(void* a1, double a2, void* a3, char* host, char* obj)
{
    bool done = false;
    do {
        switch (*(unsigned*)(host + 4)) {
        case 1: {
            char* owner = *(char**)(host + 0x70);
            if (owner != 0) {
                void (*fn)(void*, double, void*, unsigned, char*) =
                    *(void (**)(void*, double, void*, unsigned, char*))(owner + 0xc);
                if (fn != 0) {
                    unsigned idx = *(unsigned*)(obj + 4);
                    if (idx == 0xffffffff)
                        idx = *(unsigned*)(host + 0x74);
                    fn(a1, a2, a3, idx, obj + 0x2c);
                }
            }
            if (*(unsigned*)(obj + 8) < *(unsigned*)(host + 0x7c))
                host = *(char**)(host + 0x80) + *(unsigned*)(obj + 8) * 0x88;
            break;
        }
        case 2:
            done = true;
            break;
        case 0: {
            char* owner = *(char**)(host + 0x70);
            if (owner != 0) {
                void (*fn)(void*, double, void*, unsigned, char*) =
                    *(void (**)(void*, double, void*, unsigned, char*))(owner + 0xc);
                if (fn != 0) {
                    unsigned idx = *(unsigned*)(obj + 4);
                    if (idx == 0xffffffff)
                        idx = *(unsigned*)(host + 0x74);
                    fn(a1, a2, a3, idx, obj + 0x2c);
                }
            }
            break;
        }
        default:
            break;
        }
        Grid_NewArray(obj, 0xff, 0x2c);
        obj += 0xac;
    } while (!done);
}

// ===========================================================================
// @ 0x00bc8690  (args in ebx/edi: a static register helper)
void __fastcall Grid_Shuffle(unsigned n, unsigned char* buf)
{
    unsigned i = 0;
    while (i < n) {
        buf[i] = (unsigned char)i;
        ++i;
    }
    for (i = 0; i + 1 < n; ++i) {
        unsigned j = GenerateUInt32(n - i);
        unsigned char t = buf[i];
        buf[i] = buf[j + i];
        buf[j + i] = t;
    }
}

// ===========================================================================
// @ 0x00bc86e0  (cdecl: caller does add esp,0x24)
void __cdecl Grid_ResetEntry(double when, char* p1, char* p2, char* p3, unsigned* out, char* p4)
{
    if (*(int*)p3 != -1) {
        Grid_WalkInsert(p2, when, p4, p1, p3 + 0x10);
        Grid_NewArray(p3, 0xff, 0x418);
    }
    unsigned n = *(unsigned*)(p1 + 0x24);
    if (n == 0xffffffff) return;
    if (out == 0) return;
    if (n <= 0) return;
    double zero = 0.0;
    do {
        *(double*)(out + 2) = zero;
        *out = 0xffffffff;
        out += 4;
        --n;
    } while (n != 0);
}

// ===========================================================================
// @ 0x00bc8750
bool __thiscall GridMask::FitsMask(unsigned m1, unsigned m2)
{
    char* b = (char*)this;
    unsigned a = *(unsigned*)(b + 8) & m1;
    unsigned d = *(unsigned*)(b + 0xc) & m2;
    if (a != *(unsigned*)(b + 0) || d != *(unsigned*)(b + 4))
        return false;
    if (*(b + 0x10) != 0) {
        if (((*(unsigned*)(b + 0x18) & m1) | (*(unsigned*)(b + 0x1c) & m2)) == 0)
            return false;
    }
    if (*(b + 0x20) != 0) {
        unsigned c = *(unsigned*)(b + 0x28);
        unsigned e = *(unsigned*)(b + 0x2c);
        if ((c & m1) == c && (e & m2) == e)
            return false;
    }
    return true;
}

// ===========================================================================
// @ 0x00bc87b0  (cdecl: caller does add esp,0x18)
void __cdecl Grid_FlushPending(char flag, unsigned a2, char* obj, unsigned a4, double a5)
{
    char* h = *(char**)(obj + 0x55);
    if (h != 0) {
        void (*fn)(void*, double, unsigned, unsigned, char*) =
            *(void (**)(void*, double, unsigned, unsigned, char*))(h + 0xc);
        if (fn != 0)
            fn((void*)a4, a5, *(unsigned*)(obj + 0x41), *(unsigned*)(obj + 0x51), h);
    }
    *(unsigned*)(obj + 0x55) = 0;
    if (flag) {
        unsigned tmp = *(unsigned*)(obj + 0x4d);
        *(unsigned*)(obj + 0x4d) = *(unsigned*)(obj + 0x51);
        *(unsigned*)(obj + 0x51) = tmp;
        *(unsigned*)(obj + 0x55) = a2;
        return;
    }
    *(unsigned*)(obj + 0x55) = 0;
}

// ===========================================================================
// @ 0x00bc8810  (cdecl: pushes limit, counter, arg -> add esp,0xc)
int __cdecl Grid_VisitNode(void* arg, int* counter, unsigned* limit)
{
    char* node = (char*)arg;
    if (*(float*)(node + 0x1c) != 0.0f && *(int*)(node + 0x24) == -1) {
        *(int*)(node + 0x20) = *counter;
        ++*counter;
    }
    int best = 1;
    if (*(int*)(node + 4) - 1 == 0 && *(unsigned*)(node + 0x80) != 0) {
        int idx = 0;
        unsigned i = 0;
        unsigned n = *(unsigned*)(node + 0x7c);
        if (n != 0) {
            unsigned off = 0;
            do {
                int r = Grid_VisitNode(*(char**)(node + 0x80) + off, counter, limit);
                if (idx < r)
                    idx = r;
                off += 0x88;
                i += 1;
            } while (i < n);
        }
        best = idx + 1;
        if (*(int*)(node + 0x78) == 3 || *(int*)(node + 0x78) == 4) {
            unsigned v = *(unsigned*)(node + 0x7c);
            if (v < *limit)
                v = *limit;
            *limit = v;
        }
    }
    if (*(int*)(node + 0x24) == -1)
        *(int*)(node + 0x24) = *counter;
    return best;
}

// ===========================================================================
// @ 0x00bc88e0  (cdecl: pushes self, then 8 bytes, then 8 bytes)
bool __cdecl Grid_TryNode(char* self, unsigned a2, double a3, cHierGrid* ctx)
{
    (void)a2;
    if (*(char*)(self + 0x18) != 0)
        return true;
    if (*(int*)(self + 0x20) != -1) {
        unsigned* base = *(unsigned**)((char*)ctx + 0x3d);
        if (base == 0)
            return false;
        unsigned idx = *(unsigned*)(self + 0x20);
        base[idx * 4] = *(unsigned*)self;
        double* slot = (double*)(base + idx * 4 + 2);
        if (*slot <= a3)
            *slot = a3 + (double)*(float*)(self + 0x1c);
        else
            return false;
    }
    unsigned m = *(unsigned*)((char*)ctx + 0x41);
    if ((*(unsigned*)(self + 0x2c) & m) != *(unsigned*)(self + 0x28))
        return false;
    if (*(char*)(self + 0x30) != 0 && (*(unsigned*)(self + 0x34) & m) == 0)
        return false;
    if (*(char*)(self + 0x38) != 0 &&
        (*(unsigned*)(self + 0x3c) & m) == *(unsigned*)(self + 0x3c))
        return false;
    unsigned* p = *(unsigned**)((char*)ctx + 0x45);
    GridMask* f = (GridMask*)(self + 0x40);
    return f->FitsMask(p[0], p[1]) != 0;
}

// ===========================================================================
// @ 0x00bc8970  (cdecl: pushes ctx, a3, 8 bytes, a2, a1 -> add esp,0x14)
double __cdecl Grid_DispatchNode(char* node, unsigned a2, unsigned a3, cHierGrid* ctx, double a5)
{
    float r = 0.0f;
    if (Grid_TryNode(node, a2, a5, ctx)) {
        void* fnp = *(void**)(node + 8);
        if (fnp != 0) {
            *(unsigned*)((char*)ctx + 4) = a3;
            *(char**)ctx = node;
            *(char*)((char*)ctx + 8) = 0;
            float (*fn)(unsigned, double, unsigned, unsigned, char*, void*) =
                *(float (**)(unsigned, double, unsigned, unsigned, char*, void*))(node + 8);
            return (double)fn(a2, a5, *(unsigned*)((char*)ctx + 0x41),
                              *(unsigned*)((char*)ctx + 0x4d), node, ctx);
        }
        r = 1.0f;
    }
    return (double)r;
}

// ===========================================================================
// @ 0x00bc8a00
// Level-advance dispatcher: switch on the node's mode (node->m04), walking the
// level chunks and calling either the "accept" or the "reject" continuation.
unsigned __cdecl Grid_AdvanceLevel(char* host, char* node, unsigned a3, double a4)
{
    if (host == 0 || node == 0)
        return 0;
    unsigned slotLimit = *(unsigned*)(node + 0xd);
    unsigned count = *(unsigned*)(host + 0x7c);
    float last = *(float*)(node + 0x29);
    unsigned cursor = *(unsigned*)(node + 0x15);
    int mode = *(int*)(host + 4);
    unsigned chosen = 0xffffffff;
    if (mode == 0 || mode == 2)
        return 0;
    if (*(unsigned*)(host + 0x80) == 0 || count == 0)
        return 0;
    switch (*(int*)(host + 0x78)) {
    case 0: {
        unsigned pick = 0xffffffff;
        unsigned lim = count;
        if (slotLimit < count)
            lim = slotLimit;
        unsigned start = 0;
        if (last != 0.0f)
            start = (unsigned)(((int)last - *(int*)(host + 0x80)) / 0x88 + 1);
        unsigned off = start * 0x88;
        while (start < lim) {
            char* chunk = *(char**)(host + 0x80) + off;
            unsigned out = 0;
            double r = Grid_DispatchNode(chunk, 1, start, (cHierGrid*)node, a4);
            unsigned prevStart = start;
            if (r <= 0.0) {
                Grid_Notify((char)out, chunk, node, a3, a4);
            } else if (r >= 1.0) {
                Grid_FlushPending((char)out, prevStart, node, a3, a4);
                chosen = prevStart;
                if (prevStart != 0xffffffff)
                    goto done;
                break;
            } else {
                if (pick != 0xffffffff) {
                    Grid_Notify((char)out, chunk, node, a3, a4);
                } else {
                    pick = start;
                    Grid_FlushPending((char)out, prevStart, node, a3, a4);
                }
            }
            off += 0x88;
            ++start;
        }
        if (slotLimit == 0xffffffff || pick == 0xffffffff)
            goto done;
        chosen = pick;
        break;
    }
    case 1:
    case 2: {
        chosen = slotLimit;
        if (slotLimit < count)
            goto done;
        unsigned i = *(unsigned*)(node + 9);
        do {
            ++i;
            if (i >= count) {
                if (*(int*)(host + 0x78) != 2)
                    goto usePrev;
                i = 0;
            }
            char* chunk = *(char**)(host + 0x80) + i * 0x88;
            unsigned out = 0;
            double r = Grid_DispatchNode(chunk, 1, i, (cHierGrid*)node, a4);
            if (r > 0.0) {
                Grid_FlushPending((char)out, i, node, a3, a4);
                goto done;
            }
            Grid_Notify((char)out, chunk, node, a3, a4);
            ++cursor;
        } while (cursor < count);
        chosen = 0xffffffff;
        break;
    }
    case 3:
    case 4: {
        chosen = slotLimit;
        if (slotLimit < count)
            goto done;
        unsigned lim = count;
        if (count > 0xf)
            lim = *(unsigned*)0x1466960;
        unsigned keep = lim;
        if (*(int*)(node + 9) == -1)
            Grid_Shuffle(count, (unsigned char*)(node + 0x19));
        do {
            ++cursor;
            if (cursor >= lim) {
                if (*(int*)(host + 0x78) != 4)
                    goto done;
                Grid_Shuffle(count, (unsigned char*)(node + 0x19));
                cursor = 0;
            }
            unsigned idx = *(unsigned char*)(node + 0x19 + cursor);
            char* chunk = *(char**)(host + 0x80) + idx * 0x88;
            unsigned out = 0;
            double r = Grid_DispatchNode(chunk, 1, idx, (cHierGrid*)node, a4);
            if (r > 0.0) {
                Grid_FlushPending((char)out, idx, node, a3, a4);
                goto done;
            }
            Grid_Notify((char)out, chunk, node, a3, a4);
            ++keep;
        } while (keep < count);
        chosen = 0xffffffff;
        break;
    }
    case 5:
    case 6: {
        chosen = slotLimit;
        if (slotLimit < count)
            goto done;
        if (count <= *(unsigned*)(node + 9) && *(int*)(host + 0x78) == 5)
            break;
        do {
            unsigned idx = GenerateUInt32(count);
            char* chunk = *(char**)(host + 0x80) + idx * 0x88;
            if ((float)(unsigned)chunk != last) {
                unsigned out = 0;
                double r = Grid_DispatchNode(chunk, 1, idx, (cHierGrid*)node, a4);
                if (r > 0.0) {
                    Grid_FlushPending((char)out, idx, node, a3, a4);
                    goto done;
                }
                Grid_Notify((char)out, chunk, node, a3, a4);
            }
            ++cursor;
        } while (cursor < count);
        chosen = 0xffffffff;
        break;
    }
    case 7:
    case 8: {
        float best = 0.0f;
        if ((slotLimit == 0xffffffff || *(int*)(host + 0x78) == 8) && count != 0) {
            unsigned i = 0;
            unsigned off = 0;
            do {
                char* chunk = *(char**)(host + 0x80) + off;
                unsigned out = 0;
                double r = Grid_DispatchNode(chunk, 1, i, (cHierGrid*)node, a4);
                if (r <= best) {
                    Grid_Notify((char)out, chunk, node, a3, a4);
                } else {
                    best = (float)r;
                    Grid_FlushPending((char)out, i, node, a3, a4);
                    chosen = i;
                }
                off += 0x88;
                ++i;
            } while (i < count);
        }
        break;
    }
    default:
        break;
    }
    goto store;
usePrev:
    chosen = count;
store:
    *(unsigned*)(node + 0x11) = chosen;
    *(unsigned*)(node + 0x15) = cursor;
    return (unsigned)(chosen < count);
done:
    *(unsigned*)(node + 0x11) = chosen;
    *(unsigned*)(node + 0x15) = cursor;
    return (unsigned)(chosen < count);
}

// ===========================================================================
// @ 0x00bc8fa0
bool __cdecl Grid_HasValidIndex(cGridQueue* q)
{
    int count = 0;
    unsigned limit = 0;
    unsigned n = (unsigned)Grid_VisitNode(q, &count, &limit);
    return n <= 6 && limit <= 0x10;
}
