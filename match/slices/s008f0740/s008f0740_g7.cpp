// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// gold7 batch, worker 5 / slice s008f0740: four EAWebKit XHTML table-layout helpers.
//
//   0x008f1120  Table_Layout_XHTML_EA constructor - build the base Block/Layout object then
//                                stamp the table vtable (0x1437ed8) and zero the table fields,
//                                including the row/column vectors and the min/max width slots.
//   0x008f11b0  Table_Layout_XHTML_EA deleting destructor - free the rows/cols vectors, tear down
//                                the intrusive child list, reset the vptr to the Block base
//                                (0x1437c00) and delete `this` when the low bit of the flag is set.
//   0x008f1210  Table_Layout_XHTML_EA::ResizeRows - EASTL vector reallocation: assign n rows,
//                                growing the storage (copy the tail into place) or compacting it
//                                when the requested count is smaller than the current one.
//   0x008f13f0  Table_Layout_XHTML_EA::Sizing - run the block/box layout pass, copy the resolved
//                                width/height out of the sizing context, then convert each style
//                                length (border/padding/margin) to pixels with iat_floor.
//
// The struct offsets are the retail ones (checked against the disassembly); the base class carries
// an opaque byte array so the derived field offsets stay right.
#include "types.h"
#include <stddef.h>

typedef unsigned int u32;

// ---- style / sizing ----------------------------------------------------------------
// StyleState (EA::XHTML::Style::StyleState) is 0x3a8 bytes; the height value lives at +0x36c and
// its kind at +0x3a8. The copy constructor is at 0x8fc130, ~StyleState at 0x8e8650.
struct StyleState
{
	char  pad000[0x36c];
	float mHeightValue;   // +0x36c
	char  pad370[0x3a8 - 0x370];
	int   mHeightKind;    // +0x3a8
};

struct StackingContext
{
	char  pad000[0x530];
	float mWidth;       // +0x530
	float mHeight;      // +0x534
	float mLineHeight;  // +0x538
};

struct RectF {
	float l, t, r, b;
	RectF& operator=(const RectF& o) { l = o.l; t = o.t; r = o.r; b = o.b; return *this; }
};

struct TableColumn { float minWidth, maxWidth, percentWidth, xPos, width; };   // 0x14

struct TableCell {
	u32 pad0[0x64 / 4];
	RectF mOuterRect;       // +0x64
	RectF mBorderRect;      // +0x74
	RectF mPaddingRect;     // +0x84
	RectF mContentRect;     // +0x94
	RectF mPickRect;        // +0xa4
	RectF mBorderWidth;     // +0xb4
	int   mColSpan;         // +0xc4
	int   mRowSpan;         // +0xc8
	int   mColPos;          // +0xcc
	int   mRowPos;          // +0xd0
	float mMinWidth;        // +0xd4
	float mMaxWidth;        // +0xd8
	float mPercentWidth;    // +0xdc
	RectF mPadding;         // +0xe0
	int   mVAlign;          // +0xf0
	float mValignPct;       // +0xf4
};

struct TableRow {
	u32 pad0[0x5c / 4];
	TableCell** mCellsBegin;    // +0x5c
	TableCell** mCellsEnd;      // +0x60
	u32 pad64[(0x74 - 0x64) / 4];
	float mTop;                 // +0x74
	float mBottom;              // +0x78
	float mHeight;              // +0x7c
};

// ---- EASTL intrusive list / vector -------------------------------------------------
struct IntrusiveList
{
	void* mAnchor0;     // +0x00
	void* mAnchor1;     // +0x04
	~IntrusiveList();   // out-of-line (0x620230)
};

// The table's row/column vectors are plain {begin,end,cap} triples over 0x14-byte slots.
struct Table_Layout_XHTML_EA
{
	// Base Block::Layout state; opaque here so the derived offsets line up.
	char pad0[0x18];
	IntrusiveList mItems;       // +0x18 (anchor node of the child item list)
	char pad20[0x94 - 0x20];
	RectF mContentRect;         // +0x94
	char padA4[0xc4 - 0xa4];
	int   mColCount;            // +0xc4
	int   mRowIndex;            // +0xc8
	int   mColIndex;            // +0xcc
	float mRowSpacing;          // +0xd0
	float mColSpacing;          // +0xd4
	TableColumn* mColsBegin;    // +0xd8
	TableColumn* mColsEnd;      // +0xdc
	TableColumn* mColsCap;      // +0xe0
	char  padE4[0xec - 0xe4];
	TableRow** mRowsBegin;      // +0xec
	TableRow** mRowsEnd;        // +0xf0
	TableRow** mRowsCap;        // +0xf4
	float mMinWidth;            // +0x100
	float mMaxWidth;            // +0x104
	unsigned char mHasSize;     // +0x108

	void* ResizeRows(char* pos, u32 n, TableColumn* value);   // @ 0x008f1210
	void  Sizing(StackingContext* ctx, StyleState* style);   // @ 0x008f13f0
	void* Table_Layout_XHTML_EA_ctor(void* a, void* b);      // @ 0x008f1120
	void* Table_Layout_XHTML_EA_dtor(unsigned char flags);   // @ 0x008f11b0
};

// ---- free helpers referenced by the binary -----------------------------------------
// FUN_008e7f90 is the base Block::Layout constructor: __thiscall (6 is the item kind).
// Called as ctor(param_3, param_2, 6) with `this` in ecx.
struct LayoutBase
{
	void ctor008e7f90(void* a, void* b, int kind);
};

extern "C" void FUN_008f05f0(void* dst, const void* srcBegin, const void* srcEnd, const void* end);
extern "C" void FUN_008f0640(void* dst, u32 n, const void* src, void* end);
extern "C" void FUN_00c50ad0(void* dst, const void* src, const void* end);
extern "C" char* FUN_00951bb0(const void* first, const void* last, char* dst);   // uninitialized_copy
extern "C" void* FUN_00f96e70(void* dst, void* end, const void* src);
extern "C" void* operator_new(u32 size, const char* name, int a, int b, const char* file, int line);
extern "C" void  operator_delete(void* p);

// ---- EAWebKit style / layout entry points used by Sizing ---------------------------
struct Length { char raw[0x10]; };   // EA::XHTML::Style::Length, passed as a stack temp
struct StyleRule;

// @ 0x008fc130  StyleState::StyleState(const StyleState&)   (__thiscall copy ctor, this = dst)
struct StyleStateOps
{
	void copyCtor(const StyleState* src);
};
// @ 0x08e8650  StyleState::~StyleState
extern "C" void StyleState_dtor(StyleState* self);
// @ 0x08eae80  EA::XHTML::Style::ComputeStyle(void*, StyleRule**, u32, StyleState*)
extern "C" void ComputeStyle(void* host, StyleRule** rules, u32 n, StyleState* st);
// @ 0x08fc670  TextStyle::Update   (__thiscall on the StyleState)
struct TextStyleOps
{
	void update();
};
// @ 0x08eaa20  EA::XHTML::Layout::Block::SetUpBox(SizingContext&, StyleState&)
struct BlockOps
{
	void setUpBox(StackingContext* ctx, StyleState* st);
};
// @ 0x08ef8b0 / 0x08ef900  SizingContext::Clear / Finish  (__thiscall on the ctx)
struct SizingContextOps
{
	void clear();
	void finish();
};
// @ 0x08f9660  EA::XHTML::Style::Length::ToPixelsNonNeg
extern "C" float Length_ToPixelsNonNeg(Length* len, float base);
// @ 0x11e0906  iat_floor(double)
extern "C" double iat_floor(double v);

// Block::Layout base vtable slot used for the block pass (retail vtable +0x20).
struct LayoutVt
{
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();   // +0x20
};

// The SizingContext / Table block carries the style-rule list at +0x20..+0x28.
struct StyleCarrier
{
	char pad000[0x20];
	void*        mpHost;      // +0x20
	StyleRule**  mpRules;     // +0x24
	u32          mRuleCount;  // +0x28
};

// @ 0x008f1120  Table_Layout_XHTML_EA constructor
void* Table_Layout_XHTML_EA::Table_Layout_XHTML_EA_ctor(void* a, void* b)
{
	char* self = (char*)this;
	((LayoutBase*)self)->ctor008e7f90(b, a, 6);

	*(u32*)(self + 0xc4) = 0;          // mColCount
	*(u32*)(self + 0xc8) = 0;          // mRowIndex
	*(u32*)(self + 0xcc) = 0;          // mColIndex
	*(u32*)(self + 0x00) = 0x1437ed8;  // table vtable

	*(float*)(self + 0xd0) = 0.0f;     // mRowSpacing
	*(float*)(self + 0xd4) = 0.0f;     // mColSpacing
	*(u32*)(self + 0xd8) = 0;          // mColsBegin
	*(u32*)(self + 0xdc) = 0;          // mColsEnd
	*(u32*)(self + 0xe0) = 0;          // mColsCap
	*(u32*)(self + 0xec) = 0;          // mRowsBegin
	*(u32*)(self + 0xf0) = 0;          // mRowsEnd
	*(u32*)(self + 0xf4) = 0;          // mRowsCap
	*(unsigned char*)(self + 0x108) = 0;
	*(float*)(self + 0x100) = 0.0f;    // mMinWidth
	*(float*)(self + 0x104) = 0.0f;    // mMaxWidth
	return self;
}

// @ 0x008f11b0  Table_Layout_XHTML_EA deleting destructor
void* Table_Layout_XHTML_EA::Table_Layout_XHTML_EA_dtor(unsigned char flags)
{
	char* self = (char*)this;
	*(u32*)(self + 0x00) = 0x1437ed8;  // table vtable

	void* rows = *(void**)(self + 0xec);
	if (rows != 0 && *(int*)((char*)rows - 4) != 0)
		operator_delete(rows);

	void* cols = *(void**)(self + 0xd8);
	if (cols != 0 && *(int*)((char*)cols - 4) != 0)
		operator_delete(cols);

	((IntrusiveList*)(self + 0x18))->~IntrusiveList();
	*(u32*)(self + 0x00) = 0x1437c00;  // Block base vtable

	if (flags & 1)
		operator_delete(self);

	return self;
}

// @ 0x008f1210  Table_Layout_XHTML_EA::ResizeRows  (EASTL vector-like grow/compact of row slots)
void* Table_Layout_XHTML_EA::ResizeRows(char* pos, u32 n, TableColumn* value)
{
	char* self = (char*)this;
	u32 cap = (u32)((*(char**)(self + 8) - *(char**)(self + 4)) / 0x14);

	if (n > cap)
	{
		u32 have = (u32)((*(char**)(self + 4) - *(char**)(self + 0)) / 0x14);
		u32 grow = have * 2;
		if (have == 0)
			grow = 1;
		u32 want = have + n;
		if (want < grow)
			want = grow;

		char* mem;
		if (want != 0)
			mem = (char*)operator_new(want * 0x14, "EASTL", 0, 0,
			                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
			                          0xd1);
		else
			mem = 0;

		char* mid = FUN_00951bb0(*(char**)(self + 0), pos, mem);
		FUN_008f0640(mid, n, pos, 0);
		char* tail = FUN_00951bb0(pos, *(char**)(self + 4), mid + n * 0x14);

		char* old = *(char**)(self + 0x00);
		if (old != 0 && *(int*)(old - 4) != 0)
			operator_delete(old);

		*(char**)(self + 0x00) = mem;
		*(char**)(self + 4) = tail;
		*(char**)(self + 8) = mem + want * 0x14;
	}
	else if (n != 0)
	{
		TableColumn val = *value;

		char* end = *(char**)(self + 4);
		u32 have2 = (u32)((end - pos) / 0x14);

		if (n < have2)
		{
			char* last = end - n * 0x14;
			FUN_008f05f0(&val, last, end, end);
			end = end + n * 0x14;
			*(char**)(self + 4) = end;
			FUN_00c50ad0(pos, last, end);
			FUN_00f96e70(pos, pos + n * 0x14, &val);
			return 0;
		}

		u32 extra = n - have2;
		FUN_008f0640(end, extra, &val, pos);
		*(char**)(self + 4) = *(char**)(self + 4) + extra * 0x14;
		FUN_008f05f0(pos, pos, end, *(char**)(self + 4));
		*(char**)(self + 4) = *(char**)(self + 4) + have2 * 0x14;
		FUN_00f96e70(pos, end, &val);
		return 0;
	}
	return 0;
}

// @ 0x008f13f0  Table_Layout_XHTML_EA::Sizing  (the Block::Layout box/sizing override)
void Table_Layout_XHTML_EA::Sizing(StackingContext* ctx, StyleState* style)
{
	char* self = (char*)this;

	StyleState local;
	((StyleStateOps*)&local)->copyCtor(style);
	float base = ctx->mLineHeight;
	if (local.mHeightKind != 0)
	{
		StyleCarrier* sc = (StyleCarrier*)self;
		if (sc->mpHost != 0)
			ComputeStyle(sc->mpHost, sc->mpRules, sc->mRuleCount, &local);
		((TextStyleOps*)&local)->update();
		((BlockOps*)self)->setUpBox(ctx, &local);
		((SizingContextOps*)ctx)->clear();
		((LayoutVt*)self)->s8();                 // retail vtable slot +0x20 (block pass)
		((SizingContextOps*)ctx)->finish();

		*(float*)(self + 0xd4) = ctx->mHeight;
		*(float*)(self + 0xd8) = ctx->mWidth;
		*(float*)(self + 0xdc) = 0.0f;
		Length scratch;
		if (local.mHeightKind == 9)
		{
			*(float*)(self + 0xdc) = local.mHeightValue * *(float*)0x13eb960;
		}
		else if (local.mHeightKind != 10)
		{
			*(float*)(self + 0xd8) = (float)iat_floor((double)(Length_ToPixelsNonNeg(&scratch, base) + 0.5f));
		}
		*(float*)(self + 0xb4) = (float)iat_floor((double)(Length_ToPixelsNonNeg(&scratch, base) + 0.5f));
		*(float*)(self + 0xbc) = (float)iat_floor((double)(Length_ToPixelsNonNeg(&scratch, base) + 0.5f));
		*(float*)(self + 0xb8) = (float)iat_floor((double)(Length_ToPixelsNonNeg(&scratch, base) + 0.5f));
		*(float*)(self + 0xc0) = (float)iat_floor((double)(Length_ToPixelsNonNeg(&scratch, base) + 0.5f));
		*(float*)(self + 0xe0) = (float)iat_floor((double)(Length_ToPixelsNonNeg(&scratch, base) + 0.5f));
		*(float*)(self + 0xe8) = (float)iat_floor((double)(Length_ToPixelsNonNeg(&scratch, base) + 0.5f));
		*(float*)(self + 0xe4) = (float)iat_floor((double)(Length_ToPixelsNonNeg(&scratch, base) + 0.5f));
		*(float*)(self + 0xec) = (float)iat_floor((double)(Length_ToPixelsNonNeg(&scratch, base) + 0.5f));
	}
	StyleState_dtor(&local);
}
