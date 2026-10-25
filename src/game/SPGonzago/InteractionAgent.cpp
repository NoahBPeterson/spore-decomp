// src/game/SPGonzago/InteractionAgent.cpp -- migrated from slice(s) s00401200 by tools/migrate/rewrite.py
// Object file: SPGonzago/InteractionAgent.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// Preamble items the tool's verbatim emission drops for 0x00401930 (see
// work/migrate/report_s00401200_InteractionAgent.md): rewrite.py's needed_items() keeps `struct ArrayElement`
// but not this pointer-to-member typedef, because RS.item_names("typedef", ...) returns [] for
// `typedef ret (Class::*Name)();`.  Both are the slice's own text (s00401200 lines 190-199).
struct ArrayElement { };
typedef void (ArrayElement::*ElementCtorDtor)();

// @ 0x00401930
void __stdcall VectorConstructorIterator(void* p, unsigned int size, int count, ElementCtorDtor ctor)
{
    while (--count >= 0) {
        (((ArrayElement*)p)->*ctor)();
        p = (char*)p + size;
    }
}
