// Slice s011a5310 -- source for every function of the slice.
//
// 0x011a5310-0x011a607f: the ssl/s3_enc.c translation unit of the statically
// linked OpenSSL 0.9.8g, compiled verbatim in ssl_s3_enc.cpp:
//   ssl3_change_cipher_state, ssl3_cleanup_key_block, ssl3_enc,
//   ssl3_init_finished_mac, ssl3_finish_mac, ssl3_generate_master_secret,
//   ssl3_setup_key_block, ssl3_mac.
//
// 0x011a6140 (below): a lib_cblock-section function the OpenSSL 0.9.8g
// translation units in this binary have no counterpart for.  Its only caller
// (FUN_011a5120, a targeted OpenSSL routine) passes the caller's own frame,
// and the body walks s->s3->write_sequence[] ... which are not the original's
// offsets.  It is written here as the documented ssl3_record_sequence_update
// source shape rather than as a transcription of the bytes; see partial.txt.
//
// Flags: /O2 /arch:SSE /MD /Gy /TP  (see manifest.txt)
#include "types.h"

// @ 0x011a6140  ssl3_record_sequence_update
void __cdecl ssl3_record_sequence_update(void *seq8)
{
    char *seq = (char *)seq8;
    int i;

    for (i = 7; i >= 0; i--)
    {
        if (++seq[i] != 0)
            break;
    }
}
