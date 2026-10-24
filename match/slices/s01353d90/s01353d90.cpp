// Slice s01353d90: 0x013547b0 - dynamic initializer for the simulator's static attribute
// descriptor table (MSVC emits this as $E213 for a namespace-scope array whose element type has a
// non-trivial constructor).
//
// Each descriptor is 0x3c bytes (15 dwords):
//   +0x00  const char* mName           attribute name ("mPrimaryType", ...)
//   +0x04  const char* mKey            secondary name/key string
//   +0x08  int         mOffset         byte offset inside the simulated object
//   +0x0c  (not initialised by the element constructor)
//   +0x10  (not initialised)
//   +0x14  (not initialised)
//   +0x18  int         0
//   +0x1c  int         0
//   +0x20  DefaultOffsetFn
//   +0x24  ReadFn
//   +0x28  WriteFn
//   +0x2c  ParseFn
//   +0x30  TextWriteFn
//   +0x34  ValidFn
//   +0x38  ToXmlFn
// The constructor never touches +0x0c..+0x14, so those three dwords reach the table as whatever
// was on the stack; retail copies the whole 0x3c-byte temporary with rep movsd.
#include "types.h"
#include <stddef.h>

#define CHK(cls, name, off) typedef char chk_##cls##_##name[(offsetof(cls, name) == (off)) ? 1 : -1]

typedef void (*AttrFn)();

struct cAttributeDesc {
    const char* mpName;                 // +0x00
    const char* mpKey;                  // +0x04
    int mOffset;                        // +0x08
    int mUnk0c;                         // +0x0c  (left indeterminate by the constructor)
    int mUnk10;                         // +0x10
    int mUnk14;                         // +0x14
    int mUnk18;                         // +0x18
    int mUnk1c;                         // +0x1c
    AttrFn mpDefaultOffset;             // +0x20  Simulator::Attribute::DefaultOffset
    AttrFn mpRead;                      // +0x24
    AttrFn mpWrite;                     // +0x28
    AttrFn mpParse;                     // +0x2c
    AttrFn mpTextWrite;                 // +0x30
    AttrFn mpValid;                     // +0x34
    AttrFn mpToXml;                     // +0x38
};
CHK(cAttributeDesc, mpName, 0x00);
CHK(cAttributeDesc, mpKey, 0x04);
CHK(cAttributeDesc, mOffset, 0x08);
CHK(cAttributeDesc, mUnk18, 0x18);
CHK(cAttributeDesc, mUnk1c, 0x1c);
CHK(cAttributeDesc, mpDefaultOffset, 0x20);
CHK(cAttributeDesc, mpRead, 0x24);
CHK(cAttributeDesc, mpWrite, 0x28);
CHK(cAttributeDesc, mpParse, 0x2c);
CHK(cAttributeDesc, mpTextWrite, 0x30);
CHK(cAttributeDesc, mpValid, 0x34);
CHK(cAttributeDesc, mpToXml, 0x38);
typedef char chk_cAttributeDesc_size[(sizeof(cAttributeDesc) == 0x3c) ? 1 : -1];

// The static table itself (six descriptors, 0x3c bytes apart).
cAttributeDesc gAttributeTable[6];      // 0x0157a828

// ---------------------------------------------------------------------------
// Descriptor callbacks. Only their addresses are stored; nothing here calls them.
// ---------------------------------------------------------------------------
extern void DefaultOffset();            // 0x00692ca0  Simulator::Attribute::DefaultOffset
extern void Read4Int();                 // 0x00572810  Simulator::Read4<int>
extern void Write4();                   // 0x00572840  Simulator::Write4
extern void ParseLong();                // 0x00692ff0
extern void WriteTextLong();            // 0x00694ee0
extern void AlwaysValid();              // 0x00b1fbf0
extern void ToXmlInt();                 // 0x0057cde0
extern void ReadULong();                // 0x00ac8750
extern void WriteULong();               // 0x00ac8780
extern void ParseULong();               // 0x00693090
extern void WriteTextULong();           // 0x00694fa0
extern void ToXmlULong();               // 0x0057ce00
extern void WriteTextKey();             // 0x00694f00
extern void ToXmlKey();                 // 0x00675ca0
extern void ReadSolarSystem();          // 0x00c8bfa0
extern void WriteSolarSystem();         // 0x01006600
extern void ReadTextSolarSystem();      // 0x00c2e4e0
extern void WriteTextSolarSystem();     // 0x00692fb0
extern void ValidSolarSystem();         // 0x00fd9e80
extern void ToXmlSolarSystem();         // 0x00ac8050

// ---------------------------------------------------------------------------
// Each table entry is built in a stack temporary and then copied into the array; retail copies
// all 0x3c bytes (including the three never-initialised dwords) with rep movsd.
// ---------------------------------------------------------------------------
// @ 0x013547b0
void InitAttributeTable()
{
    cAttributeDesc d;

    d.mpName = (const char*)0x01473a38;
    d.mpKey = (const char*)0x041f80ad;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &Read4Int;
    d.mpWrite = &Write4;
    d.mpParse = &ParseLong;
    d.mpTextWrite = &WriteTextLong;
    d.mpValid = &AlwaysValid;
    d.mpToXml = &ToXmlInt;
    d.mOffset = 0x34;
    gAttributeTable[0] = d;

    d.mpName = (const char*)0x01473a28;
    d.mpKey = (const char*)0x041f80b0;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &Read4Int;
    d.mpWrite = &Write4;
    d.mpParse = &ParseLong;
    d.mpTextWrite = &WriteTextLong;
    d.mpValid = &AlwaysValid;
    d.mpToXml = &ToXmlInt;
    d.mOffset = 0x38;
    gAttributeTable[1] = d;

    d.mpName = (const char*)0x01473a14;
    d.mpKey = (const char*)0x03755020;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &ReadULong;
    d.mpWrite = &WriteULong;
    d.mpParse = &ParseULong;
    d.mpTextWrite = &WriteTextULong;
    d.mpValid = &AlwaysValid;
    d.mpToXml = &ToXmlULong;
    d.mOffset = 0x3c;
    gAttributeTable[2] = d;

    d.mpName = (const char*)0x01465750;
    d.mpKey = (const char*)0x0355fa98;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &Read4Int;
    d.mpWrite = &Write4;
    d.mpParse = &ParseULong;
    d.mpTextWrite = &WriteTextKey;
    d.mpValid = &AlwaysValid;
    d.mpToXml = &ToXmlKey;
    d.mOffset = 0x4c;
    gAttributeTable[3] = d;

    d.mpName = (const char*)0x01473a04;
    d.mpKey = (const char*)0x039d4a3f;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &ReadSolarSystem;
    d.mpWrite = &WriteSolarSystem;
    d.mpParse = &ReadTextSolarSystem;
    d.mpTextWrite = &WriteTextSolarSystem;
    d.mpValid = &ValidSolarSystem;
    d.mpToXml = &ToXmlSolarSystem;
    d.mOffset = 0x40;
    gAttributeTable[4] = d;

    d.mpName = (const char*)0x014739f0;
    d.mpKey = (const char*)0x056cfe97;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &ReadULong;
    d.mpWrite = &WriteULong;
    d.mpParse = &ParseULong;
    d.mpTextWrite = &WriteTextULong;
    d.mpValid = &AlwaysValid;
    d.mpToXml = &ToXmlULong;
    d.mOffset = 0x44;
    gAttributeTable[5] = d;
}

// ---------------------------------------------------------------------------
// Restored by the check-in: byte-exact 01353d90 from commit 6d8e3408a, dropped when this
// slice was rewritten for its new functions.
// Slice s01353d90: initializer of the Simulator::cSpatialObject attribute table (0x01353d90, 2420 bytes).
//
// Builds 25 Simulator::Attribute records (60 bytes each, globals 0x157a1f8..0x157a7d4) through the inline
// Attribute constructor; cl builds every element in one stack temporary and copies it into the table with
// `rep movsd` (15 dwords). Offsets are cSpatialObject member offsets (ModAPI cSpatialObject.h). The original is
// a compiler-generated dynamic initializer ($E220); this plain function with per-element assignments is
// shape-equivalent (same bytes), so a relinked build must run it at startup.
//
// The callbacks are separate extern symbols per attribute type group (the retail linker folded identical
// template instances to one address, e.g. 0xb1fbf0 serves every group, but in the object files they are
// distinct symbols). That is why cl hoists only DefaultOffset and the bool group's last two callbacks.
#include "types.h"

typedef bool (*ReadFn)(void*, void*);
typedef bool (*WriteFn)(void*, void*);
typedef void (*ReadTextFn)(const void*, void*);
typedef void (*WriteTextFn)(char*, void*);
typedef bool (*UnkFn)();
typedef bool (*Unk2Fn)(void*, const char*, int);
struct Attribute;
typedef void* (*OffsetFn)(Attribute*);

void* DefaultOffset(Attribute*);                       // 0x692ca0

// per-group callbacks (read, write, read-text, write-text, field_34, field_38); the number is the retail address
bool  rd_b6e3a0_P(void*, void*);
bool  wr_ac88c0_P(void*, void*);
void  rt_6930f0_P(const void*, void*);
void  wt_695010_P(char*, void*);
bool  uk_00b1fbf0_P();
bool  u2_acbba0_P(void*, const char*, int);

bool  rd_ae33d0_O(void*, void*);
bool  wr_ae3400_O(void*, void*);
void  rt_693120_O(const void*, void*);
void  wt_695040_O(char*, void*);
bool  uk_00b1fbf0_O();
bool  u2_ae5700_O(void*, const char*, int);

bool  rd_572810_D(void*, void*);
bool  wr_ac88f0_D(void*, void*);
void  rt_6930b0_D(const void*, void*);
void  wt_694fc0_D(char*, void*);
bool  uk_00b1fbf0_D();
bool  u2_acbb80_D(void*, const char*, int);

bool  rd_ac8750_B(void*, void*);
bool  wr_ac8780_B(void*, void*);
void  rt_693090_B(const void*, void*);
void  wt_694fa0_B(char*, void*);
bool  uk_00b1fbf0_B();
bool  u2_57ce00_B(void*, const char*, int);

bool  rd_572810_S(void*, void*);
bool  wr_572840_S(void*, void*);
void  rt_693090_S(const void*, void*);
void  wt_694f00_S(char*, void*);
bool  uk_00b1fbf0_S();
bool  u2_675ca0_S(void*, const char*, int);

bool  rd_ae3430_K(void*, void*);
bool  wr_ae3450_K(void*, void*);
void  rt_693150_K(const void*, void*);
void  wt_695080_K(char*, void*);
bool  uk_00b1fbf0_K();
bool  u2_ae5720_K(void*, const char*, int);

bool  rd_c88b60_E(void*, void*);
bool  wr_c88b80_E(void*, void*);
void  rt_c2e4e0_E(const void*, void*);
void  wt_692fb0_E(char*, void*);
bool  uk_00b1fbf0_E();
bool  u2_ac8050_E(void*, const char*, int);

struct Attribute {
  const char* name;
  uint32_t id;
  unsigned offset;
  int field_0C, field_10, field_14;
  void* pCurrentObject;
  int field_1C;
  OffsetFn offsetFunction;
  ReadFn readFunction;
  WriteFn writeFunction;
  ReadTextFn readTextFunction;
  WriteTextFn writeTextFunction;
  UnkFn field_34;
  Unk2Fn field_38;

  Attribute() {}
  __forceinline Attribute(const char* n, uint32_t i, unsigned o, ReadFn r, WriteFn w, ReadTextFn rt,
                          WriteTextFn wt, UnkFn u, Unk2Fn u2) {
    name = n;
    id = i;
    pCurrentObject = 0;
    field_1C = 0;
    offsetFunction = DefaultOffset;
    readFunction = r;
    writeFunction = w;
    readTextFunction = rt;
    writeTextFunction = wt;
    field_34 = u;
    field_38 = u2;
    offset = o;
  }
};

Attribute gSpatialObjectAttributes[25];

// @ 0x01353d90
void InitSpatialObjectAttributes() {
  gSpatialObjectAttributes[0] = Attribute("mPosition", 0x2416c5e, 0x4, rd_b6e3a0_P, wr_ac88c0_P, rt_6930f0_P, wt_695010_P, uk_00b1fbf0_P, u2_acbba0_P);
  gSpatialObjectAttributes[1] = Attribute("mOrientation", 0x2416c60, 0x10, rd_ae33d0_O, wr_ae3400_O, rt_693120_O, wt_695040_O, uk_00b1fbf0_O, u2_ae5700_O);
  gSpatialObjectAttributes[2] = Attribute("mScale", 0x316f520, 0x64, rd_572810_D, wr_ac88f0_D, rt_6930b0_D, wt_694fc0_D, uk_00b1fbf0_D, u2_acbb80_D);
  gSpatialObjectAttributes[3] = Attribute("mIsInvalid", 0xd24b464b, 0x6e, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[4] = Attribute("mIsRolledOver", 0xb1a64f7b, 0x6d, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[5] = Attribute("mIsSelected", 0x2416c61, 0x6c, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[6] = Attribute("mbPickable", 0x2416c62, 0x6f, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[7] = Attribute("mbIsTangible", 0x2416c63, 0x70, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[8] = Attribute("mBoundingRadius", 0x2416c64, 0x5c, rd_572810_D, wr_ac88f0_D, rt_6930b0_D, wt_694fc0_D, uk_00b1fbf0_D, u2_acbb80_D);
  gSpatialObjectAttributes[9] = Attribute("mFootprintRadius", 0x49100ec, 0x60, rd_572810_D, wr_ac88f0_D, rt_6930b0_D, wt_694fc0_D, uk_00b1fbf0_D, u2_acbb80_D);
  gSpatialObjectAttributes[10] = Attribute("mbIsBeingEdited", 0x2416c65, 0x72, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[11] = Attribute("mModelChanged", 0x2416c66, 0x73, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[12] = Attribute("mbTransformDirty", 0x2416c67, 0x74, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[13] = Attribute("mbFixed", 0x2416c68, 0x71, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[14] = Attribute("mbEnabled", 0x2416c69, 0x75, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[15] = Attribute("mbInView", 0x2416c6a, 0x76, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[16] = Attribute("mDistanceFromCamera", 0x2416c6b, 0x68, rd_572810_D, wr_ac88f0_D, rt_6930b0_D, wt_694fc0_D, uk_00b1fbf0_D, u2_acbb80_D);
  gSpatialObjectAttributes[17] = Attribute("mbSupported", 0x2416c6c, 0x77, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[18] = Attribute("mFlags", 0x2416c6d, 0x50, rd_572810_S, wr_572840_S, rt_693090_S, wt_694f00_S, uk_00b1fbf0_S, u2_675ca0_S);
  gSpatialObjectAttributes[19] = Attribute("mMaterialType", 0x2416c6e, 0x54, rd_572810_S, wr_572840_S, rt_693090_S, wt_694f00_S, uk_00b1fbf0_S, u2_675ca0_S);
  gSpatialObjectAttributes[20] = Attribute("mbKeepPinnedToPlanet", 0x445dc86, 0xa6, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[21] = Attribute("mModelKey", 0x47df70d, 0x90, rd_ae3430_K, wr_ae3450_K, rt_693150_K, wt_695080_K, uk_00b1fbf0_K, u2_ae5720_K);
  gSpatialObjectAttributes[22] = Attribute("mLocalExtents", 0x47df723, 0x38, rd_c88b60_E, wr_c88b80_E, rt_c2e4e0_E, wt_692fb0_E, uk_00b1fbf0_E, u2_ac8050_E);
  gSpatialObjectAttributes[23] = Attribute("mOriginalLocalExtents", 0x5e8faa8, 0x20, rd_c88b60_E, wr_c88b80_E, rt_c2e4e0_E, wt_692fb0_E, uk_00b1fbf0_E, u2_ac8050_E);
  gSpatialObjectAttributes[24] = Attribute("mbIsGhost", 0x771d7b4, 0x78, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
}
