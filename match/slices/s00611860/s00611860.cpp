// SP::cPollinator::HandleMessage: a very large message-id switch (2563 bytes).
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc).
//
// Outline port only: the id dispatch tree and each arm's work are not reconstructed here.
#include "types.h"

typedef unsigned int uint32_t;

// @ 0x611860
int cPollinatorHandleMessage(void* self, void* message) {
    (void)self;
    (void)message;
    return 0;
}
