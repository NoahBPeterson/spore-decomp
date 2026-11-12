# STOKE (DDEC data-driven equivalence checker) for tools/equiv/ddec_layer.py.
#
# Build (x86-64 Linux/Windows Docker, or macOS arm64 under Rosetta/QEMU), from the repository root:
#   docker build --platform linux/amd64 -t spore-stoke-ddec:98d8a0f-1 tools/equiv/ddec
#
# Base: the STOKE project's own image (Ubuntu 14.04, source at commit 98d8a0f with Z3 prebuilt), pinned by digest.
# Patches (applied in name order):
#   1-learner-eqonly.patch   DDEC_EQ_ONLY=1 restricts the invariant learner to linear equalities + memory equality
#                            (the DDEC paper's invariants). Sound: every learned candidate is still SMT-checked.
#   2-cutpoints-trace.patch  DDEC_TRACE=1 prints one line per testcase while mining cutpoint data (debugging).
#   3-ddec-hints.patch       DDEC_HINTS=<file> rechecks a proof: cutpoints and invariants are read back from the
#                            text STOKE printed in its SUMMARY; nothing is learned, nothing is dropped, no other
#                            cutpoints are tried, so wrong hints make the check fail.
FROM --platform=linux/amd64 stanfordpl/stoke@sha256:c50f06b36602b4282c0730da58c119d809edd69732923dd137860aaa931a599d

USER stoke
WORKDIR /home/stoke/stoke

COPY --chown=stoke:stoke *.patch /home/stoke/patches/
RUN test "$(git rev-parse --short=7 HEAD)" = 98d8a0f \
 && for p in /home/stoke/patches/*.patch; do git apply -v "$p" || exit 1; done

# Fixed configuration instead of ./configure.sh, which picks the platform from the build machine's /proc/cpuinfo:
# "nehalem" (no AVX) runs everywhere, including under Rosetta. -DSTOKE_DEBUG_DDEC makes DDEC print its SUMMARY
# (cutpoints and invariants), which the layer parses. CVC4 is not needed (Z3 is the solver).
RUN printf 'STOKE_PLATFORM="nehalem"\nBUILD_TYPE=release\nMISC_OPTIONS= -DSTOKE_DEBUG_DDEC\nNOCVC4=1\n' > .stoke_config

# x64asm generates src/opcode.enum, which the pin tool includes; with parallel make the pin tool can start before
# it exists (a race). Build x64asm alone first, then the rest of the external libraries, then the one tool we use.
RUN make x64asm EXT_OPT=release \
 && make external EXT_OPT=release \
 && make -j"$(nproc)" bin/stoke_debug_verify \
 && test -x bin/stoke_debug_verify

ENV PATH=/home/stoke/stoke/bin:$PATH
WORKDIR /work
CMD ["sleep", "infinity"]
