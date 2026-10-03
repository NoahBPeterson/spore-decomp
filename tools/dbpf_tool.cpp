// dbpf_tool list <file.package>
// dbpf_tool extract <file.package> <type> <group> <instance> <out>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "resource/DBPF.h"

using namespace Spore::Resource;

int main(int argc, char** argv) {
  if (argc < 3) {
    std::fprintf(stderr, "usage: %s list|extract <file.package> ...\n", argv[0]);
    return 2;
  }
  DatabasePackedFile pkg;
  if (!pkg.Open(argv[2])) {
    std::fprintf(stderr, "error: %s\n", pkg.Error().c_str());
    return 1;
  }
  if (!std::strcmp(argv[1], "list")) {
    for (const auto& e : pkg.Entries())
      std::printf("%08X %08X %08X off=%08X disk=%u mem=%u %s\n", e.key.type, e.key.group,
                  e.key.instance, e.offset, e.diskSize, e.memSize, e.compressed ? "Z" : "-");
    return 0;
  }
  if (!std::strcmp(argv[1], "extract") && argc == 7) {
    ResourceKey k;
    k.type = std::strtoul(argv[3], nullptr, 16);
    k.group = std::strtoul(argv[4], nullptr, 16);
    k.instance = std::strtoul(argv[5], nullptr, 16);
    const IndexEntry* e = pkg.Find(k);
    if (!e) { std::fprintf(stderr, "not found\n"); return 1; }
    auto data = pkg.Read(*e);
    if (!data) { std::fprintf(stderr, "read/decompress failed\n"); return 1; }
    std::ofstream(argv[6], std::ios::binary).write(reinterpret_cast<const char*>(data->data()),
                                                     data->size());
    return 0;
  }
  std::fprintf(stderr, "bad arguments\n");
  return 2;
}
