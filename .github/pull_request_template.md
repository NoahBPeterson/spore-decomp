## Functions

<!-- One line per function this pull request matches or improves: address, name, and its state now. -->
- `0x________` `Name`: matched / improved (N bytes still differ)

## Model or tool

<!-- What wrote the code: e.g. "Claude Opus 5.5", "DeepSeek V4.1", "by hand". Several are fine. -->

## Other changes

<!-- Everything else is fair game (AGENTS.md): headers, layouts, constructors, other functions, stand-in structs.
     List what you changed outside the matched functions, and for a header or layout change, the evidence. -->

## Checklist

- [ ] `tools/contrib/check.py` prints MATCH for each matched function
- [ ] each matched function has a `manifest.txt` line, and its `nonmatching.txt` / `partial.txt` line is removed
- [ ] this pull request adds at least one new byte-exact function, or changes only `nonmatching.txt` / `partial.txt` notes (the check fails otherwise)
- [ ] no assembly transcription (`naked`, `_emit`, raw bytes; `__asm` only as a short helper the original used, at most 8 instructions); no game files, image or disassembly committed
