// Slice s01214320: compiler-generated C++ EH unwind/cleanup funclets plus their
// __ehhandler records. They are emitted by MSVC while compiling their owning
// function (lea ecx,[ebp-N]; jmp dtor / operator_delete__(...,"Tag",0,0,0,0) /
// ??_M vector destructor iterators / mov eax,FuncInfo; jmp __CxxFrameHandler3),
// so no standalone C++ spelling reproduces their bytes. The source below performs
// the identical cleanup sequence on the owning frame; see nonmatching.txt.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS-.
#include "types.h"

// ---- vtables / helpers -----------------------------------------------------
extern "C" char vtbl_cEditorResource;   // 0x013eb938

// EA allocator free: operator_delete__(p, tag, a, b, c, d)
extern "C" void __cdecl operator_delete__(void* p, const char* tag, int a, int b, int c, int d);   // 0x00f47410

// ??_M@YGXPAXIHP6EX0@Z@Z : _eh_vector_destructor_iterator_(ptr, elemSize, count, dtor)
extern "C" void __stdcall eh_vector_destructor_iterator(void* p, unsigned elemSize, int count, void (*dtor)(void*));   // 0x011e0b22

// generic thiscall cleanup targets (one stub class each, for ABI-correct calls)
struct T_7a9610 {
  void d();   // 0x7a9610
};  // 0x007a9610
struct T_576620 {
  void d();   // 0x576620
};  // 0x00576620
struct T_5765e0 {
  void d();   // 0x5765e0
};  // 0x005765e0
struct T_5725f0 {
  void d();   // 0x5725f0
};  // 0x005725f0
struct T_5725a0 {
  void d();   // 0x5725a0
};  // 0x005725a0
struct T_a16a20 {
  void d();   // 0xa16a20
};  // 0x00a16a20
struct T_41eb80 {
  void d();   // 0x41eb80
};  // 0x0041eb80  RefVector::~RefVector
struct T_41e090 {
  void d();   // 0x41e090
};  // 0x0041e090
struct T_41e730 {
  void d();   // 0x41e730
};  // 0x0041e730  Vec24::~Vec24
struct T_7c6190 {
  void d();   // 0x7c6190
};  // 0x007c6190
struct T_7c4000 {
  void d();   // 0x7c4000
};  // 0x007c4000  cViewer::FUN_007c4000
struct T_69d350 {
  void d();   // 0x69d350
};  // 0x0069d350
struct T_6ae110 {
  void d();   // 0x6ae110
};  // 0x006ae110
struct T_6b68f0 {
  void d();   // 0x6b68f0
};  // 0x006b68f0
struct T_721fe0 {
  void d();   // 0x721fe0
};  // 0x00721fe0
struct T_700ed0 {
  void d();   // 0x700ed0
};  // 0x00700ed0  free_holder
struct T_421230 {
  void d();   // 0x421230
};  // 0x00421230  Elem24Vec::~Elem24Vec
struct T_a65a90 {
  void d();   // 0xa65a90
};  // 0x00a65a90  IntrusiveList deleting dtor
struct T_922130 {
  void d();   // 0x922130
};  // 0x00922130  Thread::Mutex::~Mutex
struct T_530670 {
  void d();   // 0x530670
};  // 0x00530670  eastl::basic_string<char>::~basic_string
struct T_4e1bf0 {
  void d();   // 0x4e1bf0
};  // 0x004e1bf0
struct T_571ee0 {
  void d();   // 0x571ee0
};  // 0x00571ee0
struct T_4a9b10 {
  void d();   // 0x4a9b10
};  // 0x004a9b10  AutoRefCount<cVirtualRefCounted>::~AutoRefCount
struct T_ae9670 {
  void d();   // 0xae9670
};  // 0x00ae9670
struct T_933960 {
  void d();   // 0x933960
};  // 0x00933960  WString::DeallocateSelf
struct T_87d260 {
  void d();   // 0x87d260
};  // 0x0087d260
struct T_421cf0 {
  void d();   // 0x421cf0
};  // 0x00421cf0  SlotMessage::Destruct
struct T_6c0fb0 {
  void d();   // 0x6c0fb0
};  // 0x006c0fb0
struct T_7cb390 {
  void d();   // 0x7cb390
};  // 0x007cb390  cOption::~cOption
struct T_7c8490 {
  void d();   // 0x7c8490
};  // 0x007c8490
struct T_5f8910 {
  void d();   // 0x5f8910
};  // 0x005f8910
struct T_7ceda0 {
  void d();   // 0x7ceda0
};  // 0x007ceda0
struct T_7aa660 {
  void d();   // 0x7aa660
};  // 0x007aa660  vector element dtor

// counted reference released through its second/third vtable slot
struct RefObj { virtual void addref(); virtual void release(); };

template <class T> static inline void Clean(void* frame, int off) {
  ((T*)((char*)frame + off))->d();
}
static inline void Del(void* frame, int off, const char* tag) {
  operator_delete__(*(void**)((char*)frame + off), tag, 0, 0, 0, 0);
}
static inline void Rel(void* frame, int off) {
  RefObj* p = *(RefObj**)((char*)frame + off);
  if (p) p->release();
}

// @ 0x1214320
void Unwind_01214320(void* frame) {
  Clean<T_7a9610>(frame, 0x0c);
  Clean<T_7a9610>(frame, 0x0c);
  Del(frame, 0x10, "Graphics");
}

// @ 0x1214420
void Unwind_01214420(void* frame) {
  eh_vector_destructor_iterator((char*)frame + 0x0c, 4, 0x10, 0);   // 0x7aa660
}

// @ 0x12144d0
void Unwind_012144d0(void* frame) {
  Del(frame, 0x0c, "Graphics");
  Clean<T_7a9610>(frame, 0x0c);
}

// @ 0x1214580
void Unwind_01214580(void* frame) {
  Clean<T_576620>(frame, 0x08);
  Clean<T_576620>(frame, 0x04);
}

// @ 0x12145c0
void Unwind_012145c0(void* frame) {
  Rel(frame, 0x04);
  Clean<T_7a9610>(frame, -0x14);
  Clean<T_7a9610>(frame, -0x10);
}

// @ 0x1214650
void Unwind_01214650(void* frame) {
  Rel(frame, -0x24);
  Clean<T_7a9610>(frame, -0x14);
  Del(frame, -0x10, "Graphics");
  Del(frame, -0x10, "Graphics");
  Clean<T_7a9610>(frame, 0x04);
}

// @ 0x1214850
void Unwind_01214850(void* frame) {
  Clean<T_a16a20>(frame, 0x00);
  Clean<T_7c6190>(frame, 0x04);
  Clean<T_5725f0>(frame, 0x08);
  Clean<T_576620>(frame, 0x64);
  Clean<T_576620>(frame, 0x68);
  Clean<T_576620>(frame, 0x6c);
  Clean<T_576620>(frame, 0x70);
  Clean<T_576620>(frame, 0x74);
  Clean<T_7a9610>(frame, 0x10c0);
  Clean<T_7a9610>(frame, 0x10c4);
  Clean<T_5765e0>(frame, 0x10c8);
  Clean<T_7a9610>(frame, 0x10d4);
  Clean<T_7a9610>(frame, 0x10d8);
  Clean<T_7a9610>(frame, 0x10dc);
  Clean<T_7a9610>(frame, 0x10e4);
  Clean<T_7a9610>(frame, 0x10e8);
  Clean<T_7a9610>(frame, 0x10ec);
  Clean<T_7a9610>(frame, 0x10fc);
  eh_vector_destructor_iterator((char*)frame + 0x1100, 4, 0x400, 0);   // 0x7a9610
}

// @ 0x1214970
void Unwind_01214970(void* frame) {
  Clean<T_a16a20>(frame, 0x00);
  Clean<T_7c6190>(frame, 0x04);
  Clean<T_5725f0>(frame, 0x08);
  Clean<T_576620>(frame, 0x64);
  Clean<T_576620>(frame, 0x68);
  Clean<T_576620>(frame, 0x6c);
  Clean<T_576620>(frame, 0x70);
  Clean<T_576620>(frame, 0x74);
  Clean<T_7a9610>(frame, 0x10c0);
  Clean<T_7a9610>(frame, 0x10c4);
  Clean<T_5765e0>(frame, 0x10c8);
  Clean<T_7a9610>(frame, 0x10d4);
  Clean<T_7a9610>(frame, 0x10d8);
  Clean<T_7a9610>(frame, 0x10dc);
  Clean<T_7a9610>(frame, 0x10e4);
  Clean<T_7a9610>(frame, 0x10e8);
  Clean<T_7a9610>(frame, 0x10ec);
  Clean<T_7a9610>(frame, 0x10fc);
  eh_vector_destructor_iterator((char*)frame + 0x1100, 4, 0x400, 0);   // 0x7a9610
}

// @ 0x1214c50
void Unwind_01214c50(void* frame) {
  Del(frame, -0x50, "Graphics");
  Clean<T_7a9610>(frame, -0x54);
  Clean<T_933960>(frame, -0x1c);
}

// @ 0x1214c90
void Unwind_01214c90(void* frame) {
  Del(frame, 0x04, "Graphics");
  Clean<T_41e730>(frame, -0x38);
}

// @ 0x1214cc0
void Unwind_01214cc0(void* frame) {
  Rel(frame, -0x194);
  Clean<T_7c4000>(frame, -0x180);
  Del(frame, -0x20, "Graphics");
}

// @ 0x1214d30
void Unwind_01214d30(void* frame) {
  Rel(frame, -0x48);
  Clean<T_69d350>(frame, -0x44);
  Clean<T_69d350>(frame, 0x04);
}

// @ 0x1214d60
void Unwind_01214d60(void* frame) {
  Clean<T_7a9610>(frame, 0x0c);
  Clean<T_7a9610>(frame, 0x0c);
  Clean<T_7a9610>(frame, -0x54);
  Clean<T_7a9610>(frame, -0x58);
  Clean<T_7a9610>(frame, -0x4c);
  Clean<T_7a9610>(frame, -0x48);
  Clean<T_7a9610>(frame, -0x44);
  Clean<T_7a9610>(frame, 0x0c);
  Clean<T_7a9610>(frame, 0x10);
  Clean<T_7a9610>(frame, 0x04);
  Clean<T_7a9610>(frame, 0x1c);
  Clean<T_7a9610>(frame, -0x34);
  Clean<T_7a9610>(frame, -0x3c);
  Clean<T_7a9610>(frame, 0x10);
  Clean<T_7a9610>(frame, -0x34);
}

// @ 0x1214df0
void Unwind_01214df0(void* frame) {
  Clean<T_7a9610>(frame, -0x28);
  Clean<T_7a9610>(frame, -0x14);
  Clean<T_7a9610>(frame, -0x1c);
  Clean<T_7a9610>(frame, -0x2c);
  Clean<T_7a9610>(frame, -0x20);
  Clean<T_7a9610>(frame, -0x18);
  Clean<T_7a9610>(frame, -0x10);
  Clean<T_7a9610>(frame, -0x24);
  Clean<T_69d350>(frame, -0x88);
}

// @ 0x1214e50
void Unwind_01214e50(void* frame) {
  Clean<T_7a9610>(frame, -0x10);
  Clean<T_7a9610>(frame, -0x38);
  Clean<T_7a9610>(frame, -0x30);
  Clean<T_7a9610>(frame, -0x28);
  Clean<T_7a9610>(frame, -0x20);
  Clean<T_7a9610>(frame, -0x18);
  Clean<T_7a9610>(frame, -0x40);
  Clean<T_7a9610>(frame, -0x24);
  Clean<T_7a9610>(frame, -0x34);
  Clean<T_7a9610>(frame, -0x14);
  Clean<T_7a9610>(frame, -0x2c);
  Clean<T_7a9610>(frame, -0x1c);
  Clean<T_7a9610>(frame, -0x3c);
  Clean<T_4a9b10>(frame, -0xd0);
  Clean<T_69d350>(frame, -0xa4);
}

// @ 0x1214ee0
void Unwind_01214ee0(void* frame) {
  Clean<T_7a9610>(frame, -0x1c);
  Clean<T_7a9610>(frame, -0x14);
  Clean<T_7a9610>(frame, -0x28);
  Clean<T_7a9610>(frame, -0x24);
  Clean<T_7a9610>(frame, -0x20);
  Clean<T_7a9610>(frame, -0x18);
  Clean<T_7a9610>(frame, -0x10);
  Clean<T_69d350>(frame, -0x6c);
}

// @ 0x1214f50
void Unwind_01214f50(void* frame) {
  Clean<T_7a9610>(frame, -0x70);
  Clean<T_7a9610>(frame, -0x6c);
  Clean<T_69d350>(frame, -0x68);
  Del(frame, -0x74, "Graphics");
  Clean<T_69d350>(frame, -0x78);
}

// @ 0x1214fa0
void Unwind_01214fa0(void* frame) {
  Clean<T_7a9610>(frame, -0x4c);
  Clean<T_7a9610>(frame, -0x48);
  Clean<T_69d350>(frame, -0x44);
  Del(frame, -0x54, "Graphics");
  Clean<T_69d350>(frame, -0x50);
}

// @ 0x1214ff0
void Unwind_01214ff0(void* frame) {
  Clean<T_7a9610>(frame, -0x58);
  Clean<T_7a9610>(frame, -0x4c);
  Clean<T_69d350>(frame, -0x48);
  Clean<T_69d350>(frame, 0x0c);
}

// @ 0x1215020
void Unwind_01215020(void* frame) {
  Clean<T_7a9610>(frame, -0x4c);
  Clean<T_7a9610>(frame, -0x48);
  Clean<T_69d350>(frame, -0x44);
  Clean<T_69d350>(frame, -0x50);
}

// @ 0x12150f0
void Unwind_012150f0(void* frame) {
  Clean<T_a16a20>(frame, 0x00);
  Clean<T_5725a0>(frame, 0x04);
  Clean<T_41eb80>(frame, 0x0c);
  Clean<T_41eb80>(frame, 0x20);
  Clean<T_700ed0>(frame, 0x34);
  Clean<T_421230>(frame, 0x4c);
  Clean<T_7a9610>(frame, 0x60);
  Clean<T_41e090>(frame, 0x7c);
}

// @ 0x1215150
void Unwind_01215150(void* frame) {
  for (int i = 0; i < 9; ++i) Del(frame, -0x10, "Graphics");
}

// @ 0x1215230
void Unwind_01215230(void* frame) {
  Clean<T_7a9610>(frame, -0x88);
  Clean<T_7a9610>(frame, -0x80);
  Clean<T_7a9610>(frame, -0x74);
  Clean<T_7a9610>(frame, -0x78);
  Clean<T_7a9610>(frame, -0x84);
  Clean<T_7a9610>(frame, -0x84);
  Clean<T_7a9610>(frame, -0x78);
  Clean<T_7a9610>(frame, -0x74);
  Clean<T_7a9610>(frame, -0x80);
  Clean<T_7a9610>(frame, -0x88);
}

// @ 0x12152a0
void Unwind_012152a0(void* frame) {
  Clean<T_530670>(frame, -0x2ae0);
  Del(frame, -0x2af0, "Graphics/GIFUtils");
  Clean<T_87d260>(frame, -0x2ad0);
  Clean<T_421cf0>(frame, -0x2abc);
}

// @ 0x1215350
void Unwind_01215350(void* frame) {
  Del(frame, 0x04, "App");
  Clean<T_7a9610>(frame, 0x04);
  Clean<T_933960>(frame, -0x1c);
}

// @ 0x1215390
void Unwind_01215390(void* frame) {
  Rel(frame, 0x04);
  Clean<T_933960>(frame, -0x1c);
  Clean<T_933960>(frame, -0x1c);
}

// @ 0x1215450
void Unwind_01215450(void* frame) {
  Del(frame, 0x08, "ArgScript/OptionSetting");
  Del(frame, 0x08, "ArgScript/OptionBoolProperty");
  Del(frame, 0x08, "ArgScript/OptionIntProperty");
  Del(frame, 0x08, "ArgScript/OptionFloatProperty");
  Del(frame, 0x08, "ArgScript/OptionKeyProperty");
  Del(frame, 0x08, "ArgScript/OptionProperties");
}

// @ 0x1215530
void Unwind_01215530(void* frame) {
  Del(frame, -0x10, "ArgScript/OptionBlock");
  Del(frame, 0x04, "ArgScript/Vendor");
  Del(frame, 0x04, "ArgScript/SetVariables");
  Del(frame, 0x04, "ArgScript/SetOption");
  Del(frame, 0x04, "ArgScript/Alert");
  Del(frame, 0x04, "ArgScript/SetResolution");
  Del(frame, 0x04, "ArgScript/BoolProperty");
  Del(frame, 0x04, "ArgScript/IntProperty");
  Del(frame, 0x04, "ArgScript/FloatProperty");
  Del(frame, 0x04, "ArgScript/KeyProperty");
}

// @ 0x1215680
void Unwind_01215680(void* frame) {
  Clean<T_530670>(frame, -0x74);
  Clean<T_4e1bf0>(frame, -0x58);
  Clean<T_4e1bf0>(frame, -0x40);
  Clean<T_4e1bf0>(frame, -0x2c);
  Clean<T_571ee0>(frame, -0xa4);
  Del(frame, -0x7c, "App/ConfigManager");
  Clean<T_571ee0>(frame, -0xa4);
  Clean<T_571ee0>(frame, -0xa4);
  Clean<T_571ee0>(frame, -0xa4);
  Clean<T_4a9b10>(frame, 0x04);
  Clean<T_ae9670>(frame, -0x1c);
}

// @ 0x1215710
void Unwind_01215710(void* frame) {
  Clean<T_4a9b10>(frame, -0x34);
  Clean<T_ae9670>(frame, -0x1c);
  Del(frame, -0x34, "App");
}

// @ 0x1215770
void Unwind_01215770(void* frame) {
  Clean<T_7c8490>(frame, 0x04);
}

// @ 0x1215790
void Unwind_01215790(void* frame) {
  Clean<T_5f8910>(frame, -0x4cc);
  Clean<T_933960>(frame, -0x4e0);
  Clean<T_530670>(frame, -0x4e0);
  Clean<T_530670>(frame, -0x4e0);
}

// @ 0x12158f0
void Unwind_012158f0(void* frame) {
  Clean<T_7cb390>(frame, -0xb8);
  Clean<T_7c8490>(frame, -0xac);
  Del(frame, -0x28, "App/ConfigManager/ResolutionInfo");
  Clean<T_4a9b10>(frame, -0x28);
  Clean<T_571ee0>(frame, -0x20);
}

// @ 0x1215950
void Unwind_01215950(void* frame) {
  Clean<T_6c0fb0>(frame, -0x2c);
  Del(frame, -0x80, "App/ConfigManager/ResolutionInfo");
  Clean<T_4a9b10>(frame, -0x80);
  Clean<T_571ee0>(frame, -0x40);
  Clean<T_571ee0>(frame, -0x40);
  Clean<T_571ee0>(frame, -0x40);
  Del(frame, -0x68, "App/ConfigManager/ResolutionInfo");
  Clean<T_4a9b10>(frame, -0x78);
  Clean<T_571ee0>(frame, -0x40);
  Clean<T_571ee0>(frame, -0x40);
}

// @ 0x1215a80
void Unwind_01215a80(void* frame) {
  Rel(frame, 0x04);
  Clean<T_ae9670>(frame, -0x2c);
  Clean<T_7a9610>(frame, 0x08);
  Rel(frame, 0x04);
  Clean<T_576620>(frame, 0x04);
  Clean<T_7ceda0>(frame, -0x1c);
  Clean<T_4a9b10>(frame, -0x78);
}

// @ 0x1215b60
void Unwind_01215b60(void* frame) {
  Del(frame, 0x08, "ArgScript/GameModelName");
  Del(frame, 0x08, "ArgScript/GameModelSize");
  Del(frame, 0x08, "ArgScript/GameModelColor");
  Del(frame, 0x08, "ArgScript/GameModelAlpha");
  Del(frame, 0x08, "ArgScript/GameModelAnimate");
  Del(frame, 0x08, "ArgScript/GameModelWorld");
  Del(frame, 0x08, "ArgScript/GameModelPersist");
  Del(frame, 0x08, "ArgScript/GameModelGroups");
  Del(frame, 0x08, "ArgScript/GameModelOptions");
  Del(frame, 0x08, "ArgScript/GameModelPickLevel");
  Del(frame, 0x08, "ArgScript/GameModelSplitter");
  Del(frame, 0x08, "ArgScript/GameModelSplit");
}
