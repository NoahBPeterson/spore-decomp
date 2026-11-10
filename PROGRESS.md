# Progress

The byte-exact counts are rebuilt after every change to `main` and published with the progress site:

- Charts, modules and contributors: https://noahbpeterson.github.io/spore-decomp/
- Full tables (by function count, bytes and size band): https://noahbpeterson.github.io/spore-decomp/PROGRESS.md

To compute them locally: `.venv/bin/python tools/ci/progress.py --out work/PROGRESS.md`.
