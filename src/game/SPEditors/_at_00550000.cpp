// src/game/SPEditors/_at_00550000.cpp -- migrated from slice(s) s005580e0 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00550000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/ResourceMan/PFRecordRead.h"
#include "EA/ResourceMan/Key.h"

// ---- items of slice s005580e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
namespace eastl {
struct allocator_tag { allocator_tag() {} };
}
namespace eastl {
class allocator_s0055_80e0 { public:
    allocator_s0055_80e0() {}
    allocator_s0055_80e0(const allocator_tag& tag);
    const char* mpName;
    uint32_t mFlags;
};
}
namespace eastl {
struct sp_vector_allocator_s0055_80e0 : public allocator_s0055_80e0 { sp_vector_allocator_s0055_80e0() {} };
}
namespace eastl {
template<typename T, typename A>
struct VectorBase_s0055_80e0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    VectorBase_s0055_80e0() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator() {}
    VectorBase_s0055_80e0(const allocator_tag& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ~VectorBase_s0055_80e0();
};
}
namespace eastl {
template<typename T, typename A>
class vector_s0055_80e0 : public VectorBase_s0055_80e0<T, A> {
public:
    vector_s0055_80e0() { ScratchSlots<1>(); }
    vector_s0055_80e0(const vector_s0055_80e0& x);
    ~vector_s0055_80e0();
    void push_back(const T& value);
};
}
namespace eastl {
template<typename T>
inline void destruct(T* first, T* last) {
    for (; first < last; ++first)
        first->~T();
}
}
namespace eastl {
template<typename T>
class vector_s0055_80e0<T, allocator_s0055_80e0> : public VectorBase_s0055_80e0<T, allocator_s0055_80e0> {
public:
    typedef VectorBase_s0055_80e0<T, allocator_s0055_80e0> base_type;
    vector_s0055_80e0(const allocator_tag& a = allocator_tag()) : base_type(a) { ScratchSlots<10>(); }
    ~vector_s0055_80e0() { ScratchSlots<2>(); destruct(base_type::mpBegin, base_type::mpEnd); }
    size_t size() const { return (size_t)(base_type::mpEnd - base_type::mpBegin); }
    T& operator[](size_t n) { return *(base_type::mpBegin + n); }
};
}
namespace SP {
namespace FunctionalMatch {
enum eType_s0055_80e0 {
    kInteger_s0055_80e0 = 48342877,
    kFloat_s0055_80e0 = 48343039,
    kTerminal_s0055_80e0 = 48343507,
    kNotEqual_s0055_80e0 = 0xcba453f7
};
}
}
namespace SP {
namespace FunctionalMatch {
enum Sentinel_s0055_80e0 { kEndConstraint_s0055_80e0 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
enum EqualConstraint_s0055_80e0 { kEquals_s0055_80e0 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
enum RangeConstraint_s0055_80e0 { kBetween_s0055_80e0 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
enum ToleranceConstraint { kWithin = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
enum NotEqualConstraint { kNotEquals = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
enum AnyConstraint { kAny = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s0055_80e0 {
    unsigned int mParameter;
    eType_s0055_80e0 mType;
    union {
        struct { int mMin; int mMax; } mIntVal;
        struct { float mMin; float mMax; } mFloatVal;
    };
    eastl::vector_s0055_80e0<Constraint_s0055_80e0, eastl::sp_vector_allocator_s0055_80e0> mConstraints;

    Constraint_s0055_80e0();
    Constraint_s0055_80e0(Sentinel_s0055_80e0);
    Constraint_s0055_80e0(unsigned int param, ToleranceConstraint, float value, float tolerance);
    Constraint_s0055_80e0(unsigned int param, RangeConstraint_s0055_80e0, float minVal, float maxVal);
    Constraint_s0055_80e0(unsigned int param, EqualConstraint_s0055_80e0, int value);
    Constraint_s0055_80e0(unsigned int param, RangeConstraint_s0055_80e0, int minVal, int maxVal);
    Constraint_s0055_80e0(unsigned int param, NotEqualConstraint, int value);
    Constraint_s0055_80e0(AnyConstraint, eastl::vector_s0055_80e0<Constraint_s0055_80e0, eastl::sp_vector_allocator_s0055_80e0> constraints);
    bool IsCompound() const;
};
}
}
namespace SP {
using namespace FunctionalMatch;
}
// ---- items of slice s005580e0 end

// @ 0x005587f0
namespace SP { namespace FunctionalMatch {
Constraint_s0055_80e0::Constraint_s0055_80e0()
: mType(kTerminal_s0055_80e0) {
}
}}  // namespace SP::FunctionalMatch
