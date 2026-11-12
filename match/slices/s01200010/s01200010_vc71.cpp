// Slice s01200010 (VC7.1 part) -- self-relative rebase helpers and the fixup wrapper destructor of
// the animation-track serializer.
//
// These helpers only match under the Visual C++ Toolkit 2003 compiler (cl 13.10): cl 15 folds the
// rebase second parameter into the memory operand (`sub ecx,[esp+8]` / `add [eax],ecx`), while retail
// keeps the base in a register (`mov edx,[esp+8]; sub ecx,edx`); and for the fixup destructor cl 15
// tests `cmp [ecx+0x18],0` and loads call targets into registers where retail loads-then-tests and
// calls through memory. They live in their own translation unit because the rest of the serializer
// slice uses intrinsics and __thiscall that cl 13.10 rejects.
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

// Fixup wrapper destructor: releases the wrapped object through its secondary operator table and
// then runs the recorded callback slot. Also a cl 13.10 build: cl 15 tests `cmp [ecx+0x18],0`
// instead of loading the member into eax, and turns both calls through memory (`call [eax+0xc]`,
// `call [esi+4]`) into load-then-`call reg`. cl 13.10 has no usable __thiscall on function
// pointers, so the stored release slot is declared __fastcall (first argument in ecx), which is
// the register routing the original call site uses.
struct RelVt
{
	void* s00;                        // +0x00
	void* s04;                        // +0x04
	void* s08;                        // +0x08
	void (__fastcall* s0c)(void*);    // +0x0c
};
struct RelObj
{
	void*         pad00;              // +0x00
	RelVt*        mpVt;               // +0x04
	unsigned char pad08[0x18 - 8];
	int           mRefs;              // +0x18
};
struct FixupHolder
{
	RelObj* mpObj;                                    // +0x00
	void (__cdecl* mpFn)(int, FixupHolder*);          // +0x04
	void Finish();
};

// @ 0x01200940
void FixupHolder::Finish()
{
	RelObj* obj = mpObj;
	int refs = obj->mRefs;
	if (!refs)
		obj->mpVt->s0c(obj);
	mpFn(0, this);
}
