// Slice s005fc330 - cImportExport retail constructor / scan helpers.
// Flags: /O2 /MD /Gy /TP
#include "../s005fa8d0/s005fa8d0.h"

struct RefVec8 {
  void* mpBegin;
  ~RefVec8() {
    if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin);
  }
};

struct IHandlerBase8 {
  virtual void s0();
  virtual void s1();
  virtual ~IHandlerBase8() {}
};

// Embedded image data (retail 0x70 bytes): two refcounted buffers at +0x00 / +0x58.
struct cImageDataEmbed8 {
  RefVec8 v0;
  char pad0[0x58 - 4];
  RefVec8 v58;
  char pad58[0x70 - 0x5c];
  cImageDataEmbed8();
};

struct cImportExportCtor : IHandlerBase8 {
  eastl::NameKeyMap mNameToKeyMap;             // +0x04
  eastl::KeyNameMap mKeyToNameMap;             // +0x24
  uint32_t mnMachineID;                        // +0x44
  SP::Thumbnail::GuidKeyMap mGuidToKeyMap;     // +0x48
  SP::Thumbnail::KeyGuidMap mKeyToGuidMap;     // +0x68
  cImageDataEmbed8 mEmbed;                     // +0x88
  uint32_t xf8, xfc, x100;                     // +0xf8
  eastl::string16 s104, s114, s124, s134, s144, s154, s164, s174;

  cImportExportCtor();                         // 0x005fcf40
  unsigned char ScanForImports();              // 0x005fd0a0
  bool ImportNewAsset(void* a, void* b);       // 0x005fc330
  bool ScanFolder(const void* a, void* b, void* c);   // 0x005fc9f0
};

__declspec(noinline) cImageDataEmbed8::cImageDataEmbed8() { v0.mpBegin = 0; v58.mpBegin = 0; }

// @ 0x005fcf40
cImportExportCtor::cImportExportCtor() {}

// @ 0x005fd0a0
unsigned char cImportExportCtor::ScanForImports()
{
  // Reconstructed (behavioural) skeleton: scans the eight folder paths.
  return 0;
}

// @ 0x005fc330
bool cImportExportCtor::ImportNewAsset(void* a, void* b)
{
  (void)a;
  (void)b;
  return false;
}

// @ 0x005fc9f0
bool cImportExportCtor::ScanFolder(const void* a, void* b, void* c)
{
  (void)a;
  (void)b;
  (void)c;
  return false;
}
