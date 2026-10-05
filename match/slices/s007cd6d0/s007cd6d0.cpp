// Slice s007cd6d0: cConfigManager startup/configure + eastl pair copy helpers + draw/animation.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-

#include "../s007ca950/s007ca950.h"

namespace EA { namespace ArgScript {
struct cArguments { void** MainArguments(int n); void** OptionArguments(const char* pName, int n); };
}}
namespace EA { namespace CommandLine {
int FindSwitch(void* pThis, const wchar_t* pName, int a, int b, int c);
}}

typedef eastl::pair<uint64, EA::AutoRefCount<SP::cPropertyList> > PropPair;

// ---------------------------------------------------------------- eastl pair helpers
namespace eastl {
// @ 0x007cd9d0
template PropPair* uninitialized_copy_ptr<PropPair>(const PropPair*, const PropPair*, PropPair*);
// @ 0x007cde80
template PropPair* copy_backward_impl<0, std::random_access_iterator_tag>::do_copy<PropPair*, PropPair*>(PropPair*, PropPair*, PropPair*);
}  // namespace eastl

// ---------------------------------------------------------------- bespoke config startup (partial)
// @ 0x007cd6d0
void cConfigManagerInitialize(void*) {}
// @ 0x007cd7a0
void cConfigManagerSetupParser(void*, void*, bool) {}
// @ 0x007cd8b0
void cConfigManagerTryConfigure(void*) {}
// @ 0x007cd8d0
void cConfigManagerConfigure(void*) {}
// @ 0x007cd960
void cConfigManagerUnnamed960(void*) {}
// @ 0x007cd990
void cConfigManagerUnnamed990(void*) {}
// @ 0x007cd9c0
void cConfigManagerUnnamed9C0(void*) {}
// @ 0x007cda70
void cConfigManagerUnnamedA70(void*) {}
// @ 0x007cdb90
void cConfigManagerUnnamedB90(void*) {}
// @ 0x007cdbe0
void cConfigManagerUnnamedBE0(void*) {}
// @ 0x007cdcd0
void UpdateFromGroundCoverConfig(void*) {}
// @ 0x007cdd80
void cConfigManagerUnnamedD80(void*) {}
// @ 0x007cddc0
void cConfigManagerUnnamedDC0(void*) {}
// @ 0x007cde30
void cConfigManagerUnnamedE30(void*) {}
// @ 0x007cdee0
void TransformVectorByMatrix(void*, float*) {}
// @ 0x007cdff0
void UpdateFloatAnim(void*, void*, float) {}
