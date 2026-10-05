// SP::cContentValidationSummarizer — content-validation graph helpers.
// Unoptimized module: /Od /Ob1 /arch:SSE.
#include "types.h"

namespace SP {

struct Triple { uint32_t a, b, c; };
struct TripleVec { Triple* begin; Triple* end; };

// A fixed-capacity index of 12-byte entries: begin/end live at the object
// offsets the disassembly reads as [this+off] / [this+off+4].
struct KeyOwner {
    void GetKey(Triple* out);            // 00440B90
};

// Property container reachable through the summarizer's +0xC field.
struct PropertyList {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual bool HasProperty(uint32_t id);   // vtable +0x1C
};

struct Node {
    bool Check();                        // 004ADC40
};

struct cContentValidationSummarizer;

// Inlined intrusive-pointer assignment; taking `dst` by reference reproduces
// the original's `&member` temporaries.
template<class T>
inline void RefAssign(T*& dst, T* n)
{
    if (dst != n) {
        T* old = dst;
        if (n != 0) n->AddRef();
        dst = n;
        if (old != 0) old->Release();
    }
}

struct LinkRec {
    void*  field0;                       // +0x00
    cContentValidationSummarizer* field4;// +0x04
    char   pad8[0x3C];
    int32_t field44;                     // +0x44
};

struct EntityVec {
    cContentValidationSummarizer** begin;
    cContentValidationSummarizer** end;
    void push_back(cContentValidationSummarizer* const& v);  // 004541F0
    void erase(cContentValidationSummarizer** it);           // 00454330
};

// 60-bit flag set; Get() below is written to expand exactly like the original
// (shr by 5, div by 32 for the bit, bounds-checked).
struct BitSet60 {
    uint32_t data[2];
    bool Get(int i) {
        if (i < 60) return (data[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
    void Set(int i, bool v);             // 00435A10
};

struct cContentValidationSummarizer {
    virtual void slot0();                // vtable +0x00
    virtual void AddRef();               // vtable +0x04
    virtual void Release();              // vtable +0x08

    char            pad04[8];            // +0x04
    PropertyList*   props;               // +0x0C
    char            pad10[0xC];          // +0x10
    uint32_t        keyA;                // +0x1C
    uint32_t        keyB;                // +0x20
    char            pad24[4];            // +0x24
    Node*           node;                // +0x28
    char            pad2c[0x33C - 0x2C];
    cContentValidationSummarizer* link33c;// +0x33C
    EntityVec       entities;            // +0x340
    char            pad348[0x378 - 0x348];
    LinkRec*        linkRec;             // +0x378
    char            pad37c[0x3E0 - 0x37C];
    cContentValidationSummarizer* link3e0;// +0x3E0
    cContentValidationSummarizer* link3e4;// +0x3E4
    char            pad3e8[0x774 - 0x3E8];
    TripleVec       vec774;              // +0x774 (each vector spans 0x78 bytes)
    char            pad77c[0x7EC - 0x77C];
    TripleVec       vec7ec;              // +0x7EC
    char            pad7f4[0x864 - 0x7F4];
    TripleVec       vec864;              // +0x864
    char            pad86c[0x8DC - 0x86C];
    TripleVec       vec8dc;              // +0x8DC
    char            pad8e4[0x954 - 0x8E4];
    TripleVec       vec954;              // +0x954
    char            pad95c[0x9CC - 0x95C];
    TripleVec       vec9cc;              // +0x9CC
    char            pad9d4[0xABC - 0x9D4];
    TripleVec       vecabc;              // +0xABC
    char            padac4[0xDC8 - 0xAC4];
    BitSet60        bits;                // +0xDC8

    bool FindEntry(KeyOwner* owner, int type);   // 00438440
    bool HasZeroKey(int type);                   // 004385E0
    void RefreshLinks(cContentValidationSummarizer* e);      // 00438700
    void Attach(cContentValidationSummarizer* e);            // 004388B0
    void RefreshLinked(cContentValidationSummarizer* e);     // 00438A40
    void Detach(cContentValidationSummarizer* e);            // 00438B10
    void SetLink3e0(cContentValidationSummarizer* p);        // 00438CC0
    void SetLink3e4(cContentValidationSummarizer* p);        // 00438DF0
    Triple GetKey(int type, int sub);                        // 00438F20
    void SetFlag(int index, bool value);                     // 00435A10
    void SetLink(cContentValidationSummarizer* p);           // 00435FD0
    int  GetCount();                                         // 0044F220
};

extern "C" bool Sub_4A7E60(void* p);     // 004A7E60
void SP_GetPropertyAsKey(void* props, uint32_t id, void* out);   // 006A1250

// @ 0x00438440
bool cContentValidationSummarizer::FindEntry(KeyOwner* owner, int type)
{
    TripleVec* v = 0;
    switch (type) {
    case 0x16: v = &vec864; break;
    case 0x17: v = &vec774; break;
    case 0x1A: v = &vec8dc; break;
    case 0x1B: v = &vec954; break;
    case 0x1C:
    case 0x1D: v = &vec7ec; break;
    case 0x2B: v = &vecabc; break;
    case 0x35: v = &vec9cc; break;
    }
    if (v != 0) {
        Triple q;
        owner->GetKey(&q);
        int count = v->end - v->begin;
        for (int i = 0; i < count; i++) {
            Triple* e = &v->begin[i];
            bool mismatch = q.c != e->c;
            if (!mismatch && e->a != 0 && q.a != e->a) mismatch = true;
            if (!mismatch && e->b != 0 && q.b != e->b) mismatch = true;
            if (!mismatch) return true;
        }
    }
    return false;
}

// @ 0x004385e0
bool cContentValidationSummarizer::HasZeroKey(int type)
{
    TripleVec* v = 0;
    switch (type) {
    case 0x16: v = &vec864; break;
    case 0x17: v = &vec774; break;
    case 0x1A: v = &vec8dc; break;
    case 0x1B: v = &vec954; break;
    }
    if (v != 0) {
        Triple want;
        want.a = 0x96B84350;
        want.b = 0;
        want.c = 0;
        Triple* it;
        for (it = v->begin; it != v->end; it++) {
            bool eq = it->a == want.a && it->b == want.b && it->c == want.c;
            if (eq) break;
        }
        if (it == v->end) return true;
    }
    return false;
}

// @ 0x00438700
void cContentValidationSummarizer::RefreshLinks(cContentValidationSummarizer* e)
{
    Attach(e);
    if (node != 0 && node->Check() && !e->bits.Get(7)) {
        if (link3e0 == 0) {
            if (e->link3e0 != 0 && Sub_4A7E60(this)) {
                if (!bits.Get(11)) {
                    Attach(e->link3e0);
                } else if (GetCount() == 0) {
                    Attach(e->link3e0);
                }
            }
        } else if (e->link3e0 != 0) {
            link3e0->Attach(e->link3e0);
        }
    }
}

// @ 0x004388b0
void cContentValidationSummarizer::Attach(cContentValidationSummarizer* e)
{
    if (e == 0) return;
    cContentValidationSummarizer** it = entities.begin;
    while (it != entities.end && *it != e) ++it;
    if (it == entities.end) {
        if (e->link33c != 0) e->link33c->RefreshLinked(e);
        cContentValidationSummarizer* p = e;
        if (p != 0) p->AddRef();
        entities.push_back(p);
        if (p != 0) p->Release();
        e->SetLink(this);
        if (e->bits.Get(11)) SetFlag(9, 1);
    }
    int count = entities.end - entities.begin;
    for (int i = 0; i < count; i++) {
    }
}

// @ 0x00438a40
void cContentValidationSummarizer::RefreshLinked(cContentValidationSummarizer* e)
{
    Detach(e);
    if (node != 0 && node->Check() && !e->bits.Get(7)) {
        cContentValidationSummarizer* l = e->link3e0;
        if (l != 0 && l->link33c != 0) l->link33c->Detach(l);
    }
}

// @ 0x00438b10
void cContentValidationSummarizer::Detach(cContentValidationSummarizer* e)
{
    cContentValidationSummarizer** it = entities.begin;
    while (it != entities.end && *it != e) ++it;
    if (it != entities.end) {
        entities.erase(it);
        if (e->bits.Get(11)) {
            SetFlag(9, 1);
            e->SetFlag(9, 1);
        }
        if (e->link33c != 0) {
            cContentValidationSummarizer* old = e->link33c;
            e->link33c = 0;
            old->Release();
        }
        if (e->linkRec != 0) {
            e->linkRec->field0 = 0;
            if (e->linkRec->field4 != 0) {
                cContentValidationSummarizer* old = e->linkRec->field4;
                e->linkRec->field4 = 0;
                old->Release();
            }
            e->linkRec->field44 = -1;
        }
    }
}

// @ 0x00438cc0
void cContentValidationSummarizer::SetLink3e0(cContentValidationSummarizer* p)
{
    if (link3e0 != p) {
        if (link3e0 != 0 && link3e0->link3e0 != 0) {
            cContentValidationSummarizer* old = link3e0->link3e0;
            link3e0->link3e0 = 0;
            old->Release();
        }
        if (p != link3e0) {
            cContentValidationSummarizer* old = link3e0;
            if (p != 0) p->AddRef();
            link3e0 = p;
            if (old != 0) old->Release();
        }
        if (p != 0 && p->link3e0 != this) {
            cContentValidationSummarizer* old = p->link3e0;
            if (this != 0) this->AddRef();
            p->link3e0 = this;
            if (old != 0) old->Release();
        }
    }
}

// @ 0x00438df0
void cContentValidationSummarizer::SetLink3e4(cContentValidationSummarizer* p)
{
    if (link3e4 != p) {
        if (link3e4 != 0 && link3e4->link3e4 != 0) {
            cContentValidationSummarizer* old = link3e4->link3e4;
            link3e4->link3e4 = 0;
            old->Release();
        }
        if (p != link3e4) {
            cContentValidationSummarizer* old = link3e4;
            if (p != 0) p->AddRef();
            link3e4 = p;
            if (old != 0) old->Release();
        }
        if (p != 0 && p->link3e4 != this) {
            cContentValidationSummarizer* old = p->link3e4;
            if (this != 0) this->AddRef();
            p->link3e4 = this;
            if (old != 0) old->Release();
        }
    }
}

// @ 0x00438f20
Triple cContentValidationSummarizer::GetKey(int type, int sub)
{
    Triple out;
    out.a = 0;
    out.b = 0;
    out.c = 0;
    if (props != 0) {
        if (type == 0) {
            if (props->HasProperty(0x3A3B9D21)) {
                SP_GetPropertyAsKey(props, 0x3A3B9D21, &out);
            } else if (sub != 0) {
                Triple t = GetKey(sub, 0);
                out = t;
            } else if (props->HasProperty(0x18C1DBE0)) {
                SP_GetPropertyAsKey(props, 0x18C1DBE0, &out);
            } else {
                out.a = keyA;
                out.c = keyB;
            }
        } else if (type == -1) {
            if (props->HasProperty(0x18C1DBE0)) {
                SP_GetPropertyAsKey(props, 0x18C1DBE0, &out);
            } else {
                out.a = keyA;
                out.c = keyB;
            }
        } else if (type == 1) {
            if (props->HasProperty(0x0F48EB09)) {
                SP_GetPropertyAsKey(props, 0x0F48EB09, &out);
            } else {
                out.a = keyA;
                out.c = keyB;
            }
        }
    }
    return out;
}

} // namespace SP
