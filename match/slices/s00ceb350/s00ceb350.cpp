// Append a default-constructed 0x38-byte element to a three-pointer (begin/end/capacity)
// vector.  The element starts with two 16-bit tags, four scalars taken from .data and a
// 0x24-byte basis block that is copy-constructed from a shared default instance.
#include "types.h"

struct Vec3 {
    float x;
    float y;
    float z;
};

// 0x24 bytes, three vectors; the copy constructor and the copy assignment are out of line
// (0x41cb40) and cannot throw (retail's push_back has no unwind frame for the temporary).
struct Basis {
    Vec3 m0;
    Vec3 m1;
    Vec3 m2;
    Basis(const Basis& other) throw();
    Basis& operator=(const Basis& other) throw();
};

extern const float g_ElemX;        // 0x0169ba50
extern const float g_ElemY;        // 0x0169ba54
extern const float g_ElemZ;        // 0x0169ba58
extern const float g_ElemScale;    // 0x01485720
extern const Basis g_DefaultBasis; // 0x0169c054

struct Elem {
    uint16_t m_Flags;   // +0x00
    uint16_t m_Id;      // +0x02
    float m_X;          // +0x04
    float m_Y;          // +0x08
    float m_Z;          // +0x0c
    float m_Scale;      // +0x10
    Basis m_Basis;      // +0x14 (0x24 bytes)

    __forceinline Elem()
        : m_Flags(0),
          m_Id(0),
          m_X(g_ElemX),
          m_Y(g_ElemY),
          m_Z(g_ElemZ),
          m_Scale(g_ElemScale),
          m_Basis(g_DefaultBasis) {}
};

struct ElemVector {
    Elem* m_Begin;    // +0x00
    Elem* m_End;      // +0x04
    Elem* m_Capacity; // +0x08

    Elem* Insert(Elem* pos, const Elem* value);
    Elem* push_back();
};

// @ 0x00ceb350  ElemVector::push_back
Elem* ElemVector::push_back() {
    Elem* pElem = m_End;
    if (pElem < m_Capacity) {
        m_End = pElem + 1;
        if (pElem) {
            pElem->m_Flags = 0;
            pElem->m_Id = 0;
            pElem->m_X = g_ElemX;
            pElem->m_Y = g_ElemY;
            pElem->m_Z = g_ElemZ;
            pElem->m_Scale = g_ElemScale;
            // The original returns what the basis copy leaves in eax, i.e. the address of
            // the copied block (element + 0x14), not the element itself; no caller of this
            // function in the image looks at the result.
            pElem = reinterpret_cast<Elem*>(&(pElem->m_Basis = g_DefaultBasis));
        }
    } else {
        Elem value;
        pElem = Insert(m_End, &value);
    }
    return pElem;
}
