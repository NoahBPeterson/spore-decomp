// Slice s00892ac0: "flush" walk of a segmented container (the object owns a sparse array
// at +0x154 whose elements start at +0x18 of each pointed-to bucket, a count at +0x158
// and an owner at +0x16c).  Every bucket is released in two parts (its element vector
// with the odd element count * 2 through its vtable slot 3, and the 0xc-byte-strided span
// [m04, m10) through m04), and every 0xc-byte entry (next-entry link at +0x8) has its
// +0x4 object released with size 4, up to the end element.  Returns true; returns true
// at once when +0x48 is set.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

struct Elem;

struct Bucket2AC0 {
    char        pad00[0x4];
    int*        m04;    // +0x4 begin (and owner) of the 0xc-strided span
    char        pad08[0x4];
    int*        m0c;    // +0xc the span's own begin
    int*        m10;    // +0x10 end of that span
    char        pad14[0x4];
    Elem*       m18;    // +0x18 begin of the element vector
    char        pad1c[0x4];
    Elem*       m20;    // +0x20 end of the element vector
    void**      m24;    // +0x24 pointer to that vector's capacity word
};

// The array's element header: the first entry names its bucket at +0x4 and links the next
// entry of that bucket at +0x8.
struct Elem {
    char         pad00[0x4];
    Bucket2AC0*  owner;     // +0x4
    Elem*        next;      // +0x8
};

// The array's vector header, used only for its element type and slot-3 releaser.
struct ElemVec {
    Elem*  begin;           // +0x0
    Elem*  end;             // +0x4
    Elem** cap;             // +0x8
    virtual void Release(Elem* begin, int count);   // slot 3 (+0xc), (begin, count)
};

typedef void (__thiscall* RelFn)(void* self, void* begin, int count);

struct Obj2AC0 {
    char         pad00[0x48];
    char         m48;    // +0x48 early-out flag
    char         pad49[0x158 - 0x49];
    int          m158;   // +0x158 end index
    Elem*        m154;   // +0x154 array of (Elem, 4-byte bucket pointer) pairs
    char         pad15c[0x16c - 0x15c];
    ElemVec*     m16c;   // +0x16c the array itself

    bool Flush();        // @ 0x00892ac0
};

// @ 0x00892ac0
bool Obj2AC0::Flush()
{
    if (m48)
        return true;
    ElemVec* owner = m16c;
    int endIdx = m158;
    Elem* ap = m154;
    Elem* e = *(Elem**)ap;
    if (!e) {
        for (;;) {
            ap = (Elem*)((char*)ap + 4);
            if (*(Elem**)ap != 0)
                break;
            ap = (Elem*)((char*)ap + 4);
            if (*(Elem**)ap == 0)
                continue;
            break;
        }
        e = *(Elem**)ap;
    }
    if (e == *(Elem**)((char*)m154 + endIdx * 4))
        return true;

    for (;;) {
        Bucket2AC0* b = e->owner;
        if (b->m18) {
            int odd = (int)(b->m20 - b->m18) & 0x7fffffff;
            odd += odd;
            owner->Release(b->m18, odd);
        }
        if (b->m04) {
            int n = (int)(b->m10 - b->m04);
            n = n / 3;
            n += n;
            n += n;
            n += n;
            ((ElemVec*)b->m04)->Release((Elem*)b->m0c, n);
        }
        owner->Release((Elem*)e->owner, 4);
        e = e->next;
        if (!e) {
            do {
                ap = (Elem*)((char*)ap + 4);
                e = *(Elem**)ap;
            } while (e == 0);
        }
        if (e == *(Elem**)((char*)m154 + endIdx * 4))
            return true;
    }
}
