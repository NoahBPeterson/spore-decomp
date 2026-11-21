// Slice s0085bb90 -- IJG libjpeg 6a jdmarker.c as SporeApp.exe has it: the release plus one line (read_markers sets
// read_dht after a DHT marker), from tools/ci/oss/jpeg-6a-retail.patch, which tools/ci/setup_oss.sh applies.
// Never copy upstream source here (THIRD_PARTY.md).
//
// @ 0x0085bb90
// 0085bb90 get_dac
// @ 0x0085bd10
// 0085bd10 get_dht
// @ 0x0085bff0
// 0085bff0 get_dqt
// @ 0x0085c230
// 0085c230 get_dri
// @ 0x0085c330
// 0085c330 skip_variable
// @ 0x0085c3e0
// 0085c3e0 next_marker
// @ 0x0085c500
// 0085c500 first_marker
// @ 0x0085c5b0
// 0085c5b0 read_markers
// @ 0x0085c9f0
// 0085c9f0 jpeg_resync_to_restart

#include "../../../work/third_party/build/jpeg-6a-retail/jdmarker.c"
