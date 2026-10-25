// Slice s0080b6b0: cSPUILayoutObjectCollection / atlas-map vector helpers.
// The small vector-teardown and window-lookup helpers are byte-exact; the larger layout and
// scrolling routines are reconstructed to behavioural equivalence.
#include "types.h"

extern "C" void efree(void* p);                    // 0x00f47380

// ================= 0x0080b8a0: find/refresh a window from the layout
struct Layout {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24();
    void* FindWindowByID(int id, int recurse);       // 0x008105b0
};

// ================= layout window handle (slots +0x38 .. +0x7c)
struct Win {
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24(); virtual void w28(); virtual void w2c();
    virtual void w30(); virtual void w34();
    virtual float* rect();                       // +0x38
    virtual const unsigned short* label();       // +0x3c
    virtual void w40(); virtual void w44(); virtual void w48(); virtual void w4c();
    virtual void w50(); virtual void w54(); virtual void w58(); virtual void w5c();
    virtual void w60(); virtual void w64(); virtual void w68();
    virtual void w6c(float* box);                // +0x6c
    virtual void w70(float x, float y);          // +0x70
    virtual void w74(float x, float y);          // +0x74
    virtual void w78();                          // +0x78
    virtual void w7c(int a, int b);              // +0x7c
};

// ================= 0x34-byte atlas-map record
struct VecRec {
    virtual void Destroy(int flag);      // +0x00 (vtable 0x1417cac)
    int f04;                             // +0x04
    int f08;                             // +0x08
    int f0c;                             // +0x0c
    int f10;                             // +0x10
    int f14;                             // +0x14
    float f18;                           // +0x18
    float f1c;                           // +0x1c
    int f20;                             // +0x20
    int f24;                             // +0x24
    int f28;                             // +0x28
    Win* ref;                            // +0x2c
    unsigned int flags;                  // +0x30
    void __thiscall CopyFrom(const VecRec* src);    // 0x80af90
    void __thiscall CopyAssign(const VecRec* src);  // 0x80b240
};

// range helpers used by the vector code
VecRec* __cdecl UninitCopy(const VecRec* first, const VecRec* last, VecRec* dst);   // 0x80b290
VecRec* __cdecl DestroyRange(const VecRec* first, const VecRec* last, VecRec* dst); // 0x80aea0
VecRec* __cdecl CopyBackward(const VecRec* first, const VecRec* last, VecRec* dstEnd); // 0x80b2d0
VecRec* __cdecl CopyForward(const VecRec* first, const VecRec* last, VecRec* dst);  // 0x80b340
void* __cdecl UninitCopyOut(void* out, const VecRec* first, const VecRec* last,
                            VecRec* dst);                                           // 0x80b970
void __cdecl FUN_0080b170(Win* w, char animate, float a, float b, float c);         // 0x80b170
void* __cdecl GameAlloc(unsigned int size, const char* name, int a, int b,
                        const char* file, int line);                                // 0xf473a0

// ================= inline-capacity vector of 0x34-byte records (11 inline)
struct RecVec {
    VecRec* begin;      // +0x00
    VecRec* end;        // +0x04
    VecRec* cap;        // +0x08
    void*   pad0c;      // +0x0c
    VecRec* inlineBuf;  // +0x10
    void*   pad14;      // +0x14
    VecRec  buf[11];    // +0x18 .. 0x254
    int  Count() const { return (int)(end - begin); }
    void Insert(VecRec* pos, const VecRec* value);                         // 0x80baa0
    void Assign(const VecRec* first, VecRec* last, const void* owner);     // 0x80bbe0
    VecRec* AllocCopyRange(int count, const VecRec* first, const VecRec* last); // 0x80ba40
    void __thiscall DestroyRange2(VecRec* first, VecRec* last);            // 0x80ae70
};

// ================= inline vector of pointers (11 inline), layout/menu scratch list
struct PtrVec {
    void** begin;       // +0x00
    void** end;         // +0x04
    void** cap;         // +0x08
    void*  pad0c;       // +0x0c
    void** inlineBuf;   // +0x10
    void*  pad14;       // +0x14
    void*  buf[11];     // +0x18 .. 0x44
    void Init() { inlineBuf = (void**)buf; cap = (void**)buf + 11; end = (void**)buf; begin = (void**)buf; }
    void __thiscall InsertAt(void** pos, void* const* value);              // 0x82f170
    int Count() const { return (int)(end - begin); }
};

struct Big3 {
    void*  vtbl;          // +0x000
    char   pad04[0x1c0];  // +0x004
    RecVec records;       // +0x1c4 .. 0x418
    Layout* layout;       // +0x418
    char   flag;          // +0x41c
    char   pad41d[3];     // +0x41d
    int    state;         // +0x420
    float  f424;          // +0x424
    float  f428;          // +0x428
    void* method(int a);
    void FUN_0080b4d0(int a);
    void FUN_0080b6b0();
    void FUN_0080b000();
    void FUN_0080bd50(float offset);
    bool FUN_0080bfb0(float width);
    Win* FUN_0080c520(float a, float b, int c);
    void* DeletingDtor(char flags);
};

// @ 0x0080b8a0
void* Big3::method(int a)
{
    if (layout != 0 && flag != 0) {
        void* w = layout->FindWindowByID(0x79830aa, 0);
        FUN_0080b4d0(a);
        FUN_0080b6b0();
        FUN_0080b000();
        return w;
    }
    return 0;
}

// ================= 0x0080b8f0: destroy a vector of 0x34-stride elements + free storage
struct E34 { virtual void Fn(int v); char pad[0x30]; };
// @ 0x0080b8f0
void __fastcall Vec34Dtor(int* v)
{
    E34* p = (E34*)v[0];
    E34* e = (E34*)v[1];
    for (; p < e; ++p)
        p->Fn(0);
    int d = v[0];
    if (d != 0 && d != v[4])
        efree((void*)d);
}

// ================= 0x0080b930: same with 0x42c stride
struct E42C { virtual void Fn(int v); char pad[0x428]; };
// @ 0x0080b930
void __fastcall Vec42CDtor(int* v)
{
    E42C* p = (E42C*)v[0];
    E42C* e = (E42C*)v[1];
    for (; p < e; ++p)
        p->Fn(0);
    int d = v[0];
    if (d != 0 && d != v[4])
        efree((void*)d);
}

// ================= 0x0080ba10: initialise an inline-buffered container (complete, non-exact)
struct ObjB {
    void* vtbl;
    int f1, f2, f3, f4, f5, f6, f7;
};
extern char ObjB_vtable[];
// @ 0x0080ba10
ObjB* __fastcall ObjBCtor(ObjB* o)
{
    o->vtbl = (void*)ObjB_vtable;
    o->f1 = 0;
    o->f2 = 0;
    void* p = (char*)o + 0x24;
    o->f7 = (int)p;
    o->f4 = (int)p;
    o->f3 = (int)p;
    p = (char*)p + 0x5370;
    o->f5 = (int)p;
    return o;
}

// ================= 0x0080bcf0: vector erase (complete, non-exact)
struct RecC { virtual void Fn(int v); int w[10]; void* r; int tail; };
RecC* copyFwd(RecC* begin, RecC* end, RecC* dst);
struct Vec {
    RecC* begin;     // +0
    RecC* end;       // +4
    RecC* cap;       // +8
    int pad;         // +0xc
    RecC* inlineBuf; // +0x10
    RecC* erase(RecC* first, RecC* last);
};
// @ 0x0080bcf0
RecC* Vec::erase(RecC* first, RecC* last)
{
    RecC* newEnd = copyFwd(last, end, first);
    RecC* e = end;
    for (RecC* p = newEnd; p < e; ++p)
        p->Fn(0);
    end = end - (last - first);
    return first;
}

// ================= 0x0080b6b0: refresh column widths/heights of the atlas map
// @ 0x0080b6b0
void Big3::FUN_0080b6b0()
{
    float span = 0.0f;
    float height = 0.0f;
    for (int i = 0; i < records.Count(); ++i) {
        VecRec* r = &records.begin[i];
        Win* w = r->ref;
        if (w == 0) {
            w->w7c(1, 0);
            continue;
        }
        if (((r->flags >> 10) & 1) != 0) {
            const unsigned short* nm = w->label();
            if (nm == 0 || nm[0] == 0) {
                w->w7c(1, 0);
                continue;
            }
        }
        if (((r->flags >> 8) & 1) != 0) {
            w->w7c(1, 0);
            continue;
        }
        w->w7c(1, 1);
        w->w70(span, 0.0f);
        if (((r->flags >> 10) & 1) != 0)
            FUN_0080b170(w, 0, 1.0f, 0.0f, 1000000.0f);
        float* rc = w->rect();
        span += rc[2] - rc[0];
        float h = rc[3] - rc[1];
        if (height < h)
            height = h;
    }
    Win* win = (Win*)layout->FindWindowByID(0x79830aa, 0);
    win->w74(span, height);
    f424 = span;
    f428 = height;
    state = 1;
}

// ================= 0x0080b9b0: scalar deleting destructor
// @ 0x0080b9b0
void* Big3::DeletingDtor(char flags)
{
    vtbl = (void*)0x1417cb0;
    Layout* l = layout;
    if (l != 0) {
        layout = 0;
        l->v2();
    }
    if (layout != 0)
        layout->v2();
    Vec34Dtor((int*)&records.begin);
    if (flags & 1)
        efree(this);
    return this;
}

// ================= 0x0080baa0: insert one record at pos
// @ 0x0080baa0
void RecVec::Insert(VecRec* pos, const VecRec* value)
{
    if (end != cap) {
        const VecRec* v = value;
        if (v >= pos && v < end)
            ++v;
        if (end != 0)
            end->CopyFrom(end - 1);
        CopyBackward(pos, end - 1, end);
        pos->CopyAssign(v);
        ++end;
        return;
    }
    int n = (int)(end - begin);
    unsigned int newCap = n != 0 ? (unsigned int)n * 2 : 1;
    VecRec* mem = 0;
    if (newCap != 0)
        mem = (VecRec*)GameAlloc(newCap * 0x34, (const char*)0x13f6b3c, 0, 0,
                                 (const char*)0x13ebb38, 0xd1);
    VecRec* mid = UninitCopy(begin, pos, mem);
    DestroyRange(begin, pos, mem);
    if (mid != 0)
        mid->CopyFrom(value);
    VecRec* e = end;
    VecRec* p2 = UninitCopy(pos, e, mid + 1);
    DestroyRange(pos, e, mid + 1);
    if (begin != 0 && begin != inlineBuf)
        efree(begin);
    begin = mem;
    end = p2;
    cap = mem + newCap;
}

// ================= 0x0080ba40: allocate + copy-construct a record range
// @ 0x0080ba40
VecRec* RecVec::AllocCopyRange(int count, const VecRec* first, const VecRec* last)
{
    VecRec* mem = count != 0
        ? (VecRec*)GameAlloc((unsigned int)count * 0x34, (const char*)0x13f6b3c, 0, 0,
                             (const char*)0x13ebb38, 0xd1)
        : 0;
    UninitCopyOut(&first, first, last, mem);
    return mem;
}

// ================= 0x0080bbe0: assign a record range
// @ 0x0080bbe0
void RecVec::Assign(const VecRec* first, VecRec* last, const void* owner)
{
    int count = (int)(last - first);
    if (count > (int)(cap - begin)) {
        VecRec* mem = AllocCopyRange(count, first, last);
        for (VecRec* p = begin; p < end; ++p)
            p->Destroy(0);
        if (begin != 0 && begin != inlineBuf)
            efree(begin);
        begin = mem;
        end = mem + count;
        cap = end;
        return;
    }
    int cur = (int)(end - begin);
    if (count > cur) {
        CopyForward(first, first + cur, begin);
        UninitCopyOut(&last, first + cur, last, end);
        end = last;
        return;
    }
    VecRec* newEnd = CopyForward(first, last, begin);
    DestroyRange2(newEnd, end);
    end = newEnd;
}

// ================= 0x0080bd50: lay the visible records out along the offset axis
// @ 0x0080bd50
void Big3::FUN_0080bd50(float offset)
{
    PtrVec list;
    list.Init();
    for (int i = 0; i < records.Count(); ++i) {
        VecRec* r = &records.begin[i];
        Win* w = r->ref;
        if (w == 0)
            continue;
        if (((r->flags >> 10) & 1) != 0) {
            const unsigned short* nm = w->label();
            if (nm == 0 || nm[0] == 0)
                continue;
        }
        if (((r->flags >> 8) & 1) != 0)
            continue;
        VecRec* rec = r;
        if (list.end < list.cap) {
            VecRec** slot = (VecRec**)list.end;
            list.end = (void**)(slot + 1);
            if (slot != 0)
                *slot = rec;
        } else {
            list.InsertAt(list.end, (void* const*)&rec);
        }
    }
    Win* win = (Win*)layout->FindWindowByID(0x79830aa, 1);
    f428 = offset;
    win->w74(offset, f424);
    int n = list.Count();
    int limit = n;
    for (int i = 0; i < n; ++i) {
        VecRec* r = (VecRec*)list.begin[i];
        if (((r->flags >> 3) & 1) != 0) {
            limit = i;
            break;
        }
    }
    float acc = offset;
    for (int i = 0; i < limit; ++i) {
        VecRec* r = (VecRec*)list.begin[i];
        float* rc = r->ref->rect();
        r->ref->w70(acc, rc[1]);
        acc += rc[2] - rc[0];
    }
    acc = f428;
    for (int i = n - 1; i >= limit; --i) {
        VecRec* r = (VecRec*)list.begin[i];
        float* rc = r->ref->rect();
        acc -= rc[2] - rc[0];
        r->ref->w70(acc, rc[1]);
    }
    if (list.begin != 0 && list.begin != list.inlineBuf)
        efree(list.begin);
}

static int NameLen(const unsigned short* s)
{
    const unsigned short* p = s;
    while (*p != 0)
        ++p;
    return (int)(p - s);
}

// ================= 0x0080bfb0: distribute leftover width over the flexible records
// @ 0x0080bfb0
bool Big3::FUN_0080bfb0(float width)
{
    PtrVec vis;
    vis.Init();
    for (int i = 0; i < records.Count(); ++i) {
        VecRec* r = &records.begin[i];
        Win* w = r->ref;
        if (w == 0)
            continue;
        if (((r->flags >> 10) & 1) != 0) {
            const unsigned short* nm = w->label();
            if (nm == 0 || nm[0] == 0)
                continue;
        }
        if (((r->flags >> 8) & 1) != 0)
            continue;
        VecRec* rec = r;
        if (vis.end < vis.cap) {
            VecRec** slot = (VecRec**)vis.end;
            vis.end = (void**)(slot + 1);
            if (slot != 0)
                *slot = rec;
        } else {
            vis.InsertAt(vis.end, (void* const*)&rec);
        }
    }

    PtrVec group;
    group.Init();
    float sum = 0.0f;
    int visCount = vis.Count();
    for (int i = 0; i < visCount; ++i) {
        VecRec* r = (VecRec*)vis.begin[i];
        unsigned int u = r->flags;
        if (((u >> 6) & 1) == 0 && (((u >> 10) & 1) == 0 || ((u >> 5) & 1) == 0)) {
            float* rc = r->ref->rect();
            sum += rc[2] - rc[0];
        } else {
            VecRec* rec = r;
            if (group.end < group.cap) {
                VecRec** slot = (VecRec**)group.end;
                group.end = (void**)(slot + 1);
                if (slot != 0)
                    *slot = rec;
            } else {
                group.InsertAt(group.end, (void* const*)&rec);
            }
        }
    }

    float gap = width - sum;
    int nGroup = group.Count();
    int shrunk = 0;
    bool all = false;
    if (gap > 0.0f && nGroup != 0) {
        float avg = sum / (float)(visCount - nGroup);
        for (int i = 0; i < nGroup; ++i) {
            VecRec* r = (VecRec*)group.begin[i];
            if (((r->flags >> 10) & 1) == 0) {
                float box[4];
                float* rc = r->ref->rect();
                box[0] = rc[0];
                box[1] = rc[1];
                box[2] = rc[2];
                box[3] = rc[3];
                if ((box[2] - box[0]) - avg > 0.0f) {
                    group.begin[i] = 0;
                    gap -= box[2] - box[0];
                    r->ref->w6c(box);
                    ++shrunk;
                }
            }
        }
        if (gap > 1.0f && shrunk < group.Count()) {
            float total = 0.0f;
            for (int i = 0; i < nGroup; ++i) {
                VecRec* r = (VecRec*)group.begin[i];
                if (r != 0)
                    total += (float)NameLen(r->ref->label());
            }
            for (int i = 0; i < nGroup; ++i) {
                VecRec* r = (VecRec*)group.begin[i];
                if (r != 0) {
                    float len = (float)NameLen(r->ref->label());
                    float f = (len / total) * gap;
                    FUN_0080b170(r->ref, 1, 1.5f, f, f);
                    float* rc = r->ref->rect();
                    gap -= rc[2] - rc[0];
                    total -= len;
                    group.begin[i] = 0;
                    float h = rc[3] - rc[1];
                    if (f424 < h)
                        f424 = h;
                    ++shrunk;
                }
            }
        }
        f428 = 0.0f;
        FUN_0080bd50(width);
        Win* win = (Win*)layout->FindWindowByID(0x79830aa, 1);
        win->w74(f428, f424);
        FUN_0080b000();
        all = shrunk == group.Count();
    }
    if (group.begin != 0 && group.begin != group.inlineBuf)
        efree(group.begin);
    if (vis.begin != 0 && vis.begin != vis.inlineBuf)
        efree(vis.begin);
    return all;
}

// ================= 0x0080c520: modal scroll dispatch
// @ 0x0080c520
Win* Big3::FUN_0080c520(float a, float b, int c)
{
    Win* win = (Win*)layout->FindWindowByID(0x79830aa, 0);
    if (state == 0)
        win = (Win*)method(c);
    if (win == 0)
        return 0;
    if (state != 1 && state != 2)
        return 0;
    state = 2;
    float* rc = win->rect();
    float w = rc[2] - rc[0];
    if (w < a) {
        FUN_0080bd50(a);
        return win;
    }
    if (w > b) {
        if (!FUN_0080bfb0(b))
            return 0;
    }
    return win;
}
