// Self-contained tests for the resource layer. With --corpus <Spore/Data>, also
// opens every shipped .package and decompresses every entry.
#include <chrono>
#include <cstdio>
#include <cstring>
#include <filesystem>
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
  const uint8_t badOffset[] = {0x10, 0xFB, 0, 0, 3, 0x04, 0x10, 0xFC};
  CHECK(!RefPackDecompress(badOffset, sizeof badOffset));
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
      if (!e.compressed) {
        if (e.diskSize != e.memSize) ++bad;
        continue;
      }
      ++compressed;
      if (!pkg.Read(e)) ++bad;
    }
    double s = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    std::printf("%-28s v%u.%u entries=%zu compressed=%zu failed=%zu (%.1fs)\n",
                de.path().filename().c_str(), pkg.MajorVersion(), pkg.MinorVersion(),
                pkg.Entries().size(), compressed, bad, s);
    g_failures += static_cast<int>(bad);
  }
  CHECK(packages > 0);
}

int main(int argc, char** argv) {
  TestHash();
  TestRefPack();
  if (argc == 3 && !std::strcmp(argv[1], "--corpus")) TestCorpus(argv[2]);
  std::printf(g_failures ? "FAILED (%d)\n" : "OK\n", g_failures);
  return g_failures ? 1 : 0;
}
