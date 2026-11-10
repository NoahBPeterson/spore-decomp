// Slice s01200010 (VC7.1 part) -- self-relative rebase helpers of the animation-track serializer.
//
// These two helpers only match under the Visual C++ Toolkit 2003 compiler (cl 13.10): cl 15 folds the
// second parameter into the memory operand (`sub ecx,[esp+8]` / `add [eax],ecx`), while retail keeps
// the base in a register (`mov edx,[esp+8]; sub ecx,edx`). They live in their own translation unit
// because the rest of the serializer slice uses intrinsics and __thiscall that cl 13.10 rejects.
//
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE

#include <xmmintrin.h>

// Three int members holding self-relative values.
struct Rel3
{
	int mV0;                         // +0x00
	int mV1;                         // +0x04
	int mV2;                         // +0x08
};

// @ 0x01200860
int CopyVec4(__m128* dst, const __m128* src)
{
	*dst = *src;
	return 1;
}

// @ 0x01200880
void CopyVec4Void(__m128* dst, const __m128* src)
{
	*dst = *src;
}

// @ 0x012008b0
void Rebase3(Rel3* p, void* from)
{
	int d = (int)p - (int)from;
	p->mV2 += d;
	p->mV0 += d;
	p->mV1 += d;
}

// @ 0x01201070
void RebaseTranslated(int* p, int* from)
{
	int d = (int)p - (int)from;
	*p += d;
}
