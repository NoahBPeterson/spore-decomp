// Self-contained tests for the resource layer. With --corpus <Spore/Data>, also
// opens every shipped .package and decompresses every entry.
#include <chrono>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>

#include "resource/DBPF.h"
#include "resource/Hash.h"
#include "resource/RefPack.h"

using namespace Spore::Resource;

static int g_failures = 0;
#define CHECK(cond)                                                     \
  do {                                                                  \
    if (!(cond)) {                                                      \
      std::fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #cond); \
      ++g_failures;                                                     \
    }                                                                   \
  } while (0)

static void TestHash() {
  CHECK(HashName("") == 0x811C9DC5u);
  CHECK(HashName("a") == 0x050C5D7Eu);  // FNV-1 32 reference vector
  CHECK(HashName("PROP") == HashName("prop"));
  CHECK(HashName("Prop") == 0x74DA5446u);       // value computed by the original 0x0068C680
  CHECK(HashName("Caf\xE9") == 0xE5B65CE2u);    // high byte sign-extended, as the original
}

static void TestRefPack() {
  const uint8_t stream[] = {0x10, 0xFB, 0x00, 0x00, 0x08,  // header, size 8
                            0xE0, 'a', 'b', 'c', 'd',      // 4 literals
                            0x04, 0x03,                    // copy 4 from distance 4
                            0xFC};                         // stop, 0 literals
  auto out = RefPackDecompress(stream, sizeof stream);
  CHECK(out && std::string(out->begin(), out->end()) == "abcdabcd");

  // Truncated / malformed inputs must fail cleanly.
  CHECK(!RefPackDecompress(stream, 4));
  CHECK(!RefPackDecompress(stream, sizeof stream - 1));
  const uint8_t badMagic[] = {0x10, 0xFA, 0, 0, 0};
  CHECK(!RefPackDecompress(badMagic, sizeof badMagic));
  // 0x0092CAD0 rejects the 0x01 "compressed size present" flag.
  const uint8_t withCompSize[] = {0x11, 0xFB, 0, 0, 13, 0, 0, 8, 0xE0, 'a', 'b', 'c', 'd', 0x04, 0x03, 0xFC};
  CHECK(!RefPackIsValidHeader(withCompSize, sizeof withCompSize));
  CHECK(!RefPackDecompress(withCompSize, sizeof withCompSize));
  const uint8_t bigSize[] = {0x90, 0xFB, 0, 0, 0, 4, 0xFC};  // 0x80: 4-byte size, then 0 literals
  CHECK(RefPackDecompressedSize(bigSize, sizeof bigSize) == 4u);
  const uint8_t badOffset[] = {0x10, 0xFB, 0, 0, 3, 0x04, 0x10, 0xFC};
  CHECK(!RefPackDecompress(badOffset, sizeof badOffset));
}

// ---- DBPF behaviors recovered from the exe ----
static void Put32(std::vector<uint8_t>& v, size_t at, uint32_t x) {
  if (v.size() < at + 4) v.resize(at + 4);
  for (int i = 0; i < 4; ++i) v[at + i] = uint8_t(x >> (8 * i));
}
static void Push32(std::vector<uint8_t>& v, uint32_t x) { Put32(v, v.size(), x); }

static std::vector<uint8_t> MakeHeader(uint32_t major, uint32_t count, uint32_t indexOffset,
                                       uint32_t indexSize, uint32_t indexMinor = 3) {
  std::vector<uint8_t> h(0x60, 0);
  std::memcpy(h.data(), "DBPF", 4);
  Put32(h, 0x04, major);
  Put32(h, 0x24, count);
  Put32(h, 0x2C, indexSize);
  Put32(h, 0x3C, indexMinor);
  Put32(h, 0x40, indexOffset);
  return h;
}

static void TestHeaderVerify() {
  using D = DatabasePackedFile;
  CHECK(D::VerifyHeaderRecordIntegrity(MakeHeader(3, 1, 0x60, 0x10).data(), 0x70));
  CHECK(D::VerifyHeaderRecordIntegrity(MakeHeader(0, 1, 0x60, 0x10).data(), 0x70));  // major<4 ok
  CHECK(!D::VerifyHeaderRecordIntegrity(MakeHeader(4, 1, 0x60, 0x10).data(), 0x70));
  CHECK(!D::VerifyHeaderRecordIntegrity(MakeHeader(3, 1, 0x60, 0x10, 0).data(), 0x70));  // minor 0
  CHECK(!D::VerifyHeaderRecordIntegrity(MakeHeader(3, 1, 0x60, 0x11).data(), 0x70));  // past EOF
  CHECK(!D::VerifyHeaderRecordIntegrity(MakeHeader(3, 0x7FFFFFF, 0x60, 0x10).data(), 0x70));
  auto h = MakeHeader(3, 1, 0x60, 0x10);
  Put32(h, 0x28, 0x61);  // legacy offset disagrees -> invalid
  CHECK(!D::VerifyHeaderRecordIntegrity(h.data(), 0x70));
  Put32(h, 0x28, 0x60);  // agrees -> valid
  CHECK(D::VerifyHeaderRecordIntegrity(h.data(), 0x70));
}

static void TestIndexParse() {
  using D = DatabasePackedFile;
  std::vector<uint8_t> idx;
  Push32(idx, 4 | 1);   // type constant, third field constant
  Push32(idx, 0xAABBCCDD);  // type
  Push32(idx, 0);           // third
  // entry 1: compact form (no extra dword), sizes differ -> compressed
  Push32(idx, 0x11); Push32(idx, 0x22); Push32(idx, 0x100); Push32(idx, 10); Push32(idx, 20);
  // entry 2: extended form with explicit compression 0 and committed bit
  Push32(idx, 0x33); Push32(idx, 0x44); Push32(idx, 0x200); Push32(idx, 0x80000005); Push32(idx, 5);
  Push32(idx, 0x00010000);
  std::vector<IndexEntry> out;
  CHECK(D::ParseIndex(idx.data(), idx.size(), 2, false, out));
  CHECK(out.size() == 2);
  if (out.size() == 2) {
    CHECK(out[0].key.type == 0xAABBCCDD && out[0].key.group == 0x11 && out[0].key.instance == 0x22);
    CHECK(out[0].compression == 0xFFFF && !out[0].committed);
    CHECK(out[1].diskSize == 5 && out[1].compression == 0 && out[1].committed);
  }
  std::vector<uint8_t> noBit2 = idx;
  Put32(noBit2, 0, 1);
  out.clear();
  CHECK(!D::ParseIndex(noBit2.data(), noBit2.size(), 2, false, out));
  std::vector<uint8_t> thirdNonZero = idx;
  Put32(thirdNonZero, 8, 7);
  out.clear();
  CHECK(!D::ParseIndex(thirdNonZero.data(), thirdNonZero.size(), 2, false, out));
  out.clear();
  CHECK(!D::ParseIndex(idx.data(), idx.size() - 1, 2, false, out));  // truncated

  std::vector<IndexEntry> v(1);
  v[0].offset = 0x60; v[0].diskSize = 0x10;
  CHECK(D::VerifyIndexRecordIntegrity(v, 0, 0x70));
  v[0].diskSize = 0x11;
  CHECK(!D::VerifyIndexRecordIntegrity(v, 0, 0x70));
  v[0].diskSize = 0; v[0].offset = 0xFFFF;  // zero-size entries are not checked
  CHECK(D::VerifyIndexRecordIntegrity(v, 0, 0x70));
}

static std::vector<uint8_t> MakePackage(const std::vector<std::pair<ResourceKey, std::string>>& files) {
  std::vector<uint8_t> body(0x60, 0);
  std::vector<uint8_t> idx;
  Push32(idx, 4);
  Push32(idx, 0);
  for (const auto& [k, data] : files) {
    uint32_t off = uint32_t(body.size());
    body.insert(body.end(), data.begin(), data.end());
    Push32(idx, k.type); Push32(idx, k.group); Push32(idx, k.instance);
    Push32(idx, off); Push32(idx, uint32_t(data.size())); Push32(idx, uint32_t(data.size()));
  }
  auto h = MakeHeader(3, uint32_t(files.size()), uint32_t(body.size()), uint32_t(idx.size()));
  std::copy(h.begin(), h.end(), body.begin());
  body.insert(body.end(), idx.begin(), idx.end());
  return body;
}

static std::string WriteTemp(const std::string& name, const std::vector<uint8_t>& bytes) {
  auto path = (std::filesystem::temp_directory_path() / name).string();
  std::ofstream(path, std::ios::binary).write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
  return path;
}

static void TestPackages() {
  ResourceKey a{1, 2, 3};
  auto pkg = MakePackage({{a, "first"}, {a, "second"}, {{9, 2, 3}, "other"}});
  DatabasePackedFile f;
  CHECK(f.Open(WriteTemp("spore_dbpf_dup.package", pkg)));
  CHECK(f.Entries().size() == 3);
  const IndexEntry* e = f.Find(a);
  auto data = e ? f.Read(*e) : std::nullopt;
  CHECK(data && std::string(data->begin(), data->end()) == "first");  // first duplicate wins

  // Embedded: junk prefix, then the 16-byte marker, then a package. The header check
  // still compares offsets with the whole file size, and the index verifier uses absolute
  // offsets, so this small layout stays valid.
  std::vector<uint8_t> emb(37, 0x55);
  const uint8_t marker[16] = {0x80, 0x9D, 0x88, 0xEC, 0x8F, 0x24, 0x03, 0x6C,
                              0xC9, 0xA6, 0x31, 0x56, 0x5B, 0xCF, 0x77, 0x20};
  emb.insert(emb.end(), marker, marker + 16);
  emb.insert(emb.end(), pkg.begin(), pkg.end());
  DatabasePackedFile g;
  CHECK(g.Open(WriteTemp("spore_dbpf_emb.package", emb)));
  CHECK(g.HeaderPosition() == 37 + 16);
  const IndexEntry* ge = g.Find({9, 2, 3});
  auto gd = ge ? g.Read(*ge) : std::nullopt;
  CHECK(gd && std::string(gd->begin(), gd->end()) == "other");
}

static void TestCorpus(const std::string& dir) {
  namespace fs = std::filesystem;
  int packages = 0;
  for (const auto& de : fs::directory_iterator(dir)) {
    if (de.path().extension() != ".package") continue;
    ++packages;
    auto t0 = std::chrono::steady_clock::now();
    DatabasePackedFile pkg;
    if (!pkg.Open(de.path().string())) {
      std::fprintf(stderr, "%s: %s\n", de.path().c_str(), pkg.Error().c_str());
      ++g_failures;
      continue;
    }
    size_t compressed = 0, bad = 0;
    for (const auto& e : pkg.Entries()) {
      if (!e.IsCompressed()) {
        if (e.diskSize != e.memSize) ++bad;
        continue;
      }
      ++compressed;
      if (!pkg.Read(e)) ++bad;
    }
    double s = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    std::printf("%-28s entries=%zu compressed=%zu failed=%zu (%.1fs)\n",
                de.path().filename().c_str(), pkg.Entries().size(), compressed, bad, s);
    g_failures += static_cast<int>(bad);
  }
  CHECK(packages > 0);
}

int main(int argc, char** argv) {
  TestHash();
  TestRefPack();
  TestHeaderVerify();
  TestIndexParse();
  TestPackages();
  if (argc == 3 && !std::strcmp(argv[1], "--corpus")) TestCorpus(argv[2]);
  std::printf(g_failures ? "FAILED (%d)\n" : "OK\n", g_failures);
  return g_failures ? 1 : 0;
}
