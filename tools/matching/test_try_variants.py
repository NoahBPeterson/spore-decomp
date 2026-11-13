"""Scorer and CLI regressions using synthetic bytes; no game or compiler required.

Run: python3 -m unittest tools/matching/test_try_variants.py
"""
import contextlib
import gzip
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import Mock, patch

sys.path.insert(0, str(Path(__file__).resolve().parent))
import try_variants as V  # noqa: E402


def fingerprint(data=b'ABCDEF', mask=()):
    return {'va': '00001000', 'size': len(data), 'mask': V.F.pack_mask(set(mask)),
            'sha256': V.F.mhash(data, set(mask))}


class ScoringTests(unittest.TestCase):
    def score(self, data, relocs=(), mask=()):
        return V.score_candidates([{'data': data, 'relocs': relocs}], {'candidate': (0, 0)},
                                  fingerprint(mask=mask), b'ABCDEF')[0]

    def test_exact(self):
        self.assertEqual(self.score(b'ABCDEF'), (0, 6, 'candidate', 'PASS'))

    def test_short_and_long_candidates_are_not_matches(self):
        for data, distance in ((b'ABC', 3), (b'ABCDEFG', 1)):
            with self.subTest(data=data):
                row = self.score(data)
                self.assertEqual(row[0], distance)
                self.assertTrue(row[3].startswith('size '))

    def test_extra_relocation_can_score_zero_but_must_fail(self):
        row = self.score(b'AxxxxF', [(1, 0, 0x14)])
        self.assertEqual(row[0], 0)
        self.assertTrue(row[3].startswith('relocation at offset'))

    def test_allowed_relocation_and_missing_relocation_follow_canonical_contract(self):
        for relocs in ([], [(1, 0, 0x14)]):
            self.assertEqual(self.score(b'AxxxxF', relocs, {1, 2, 3, 4})[3], 'PASS')

    def test_fixed_bytes_still_matter(self):
        row = self.score(b'ZBCDEF')
        self.assertEqual((row[0], row[3]), (1, 'bytes differ'))

    def test_section_relocation_masks_only_two_bytes(self):
        row = self.score(b'AxxDEF', [(1, 0, 0x0a)], {1, 2})
        self.assertEqual(row[3], 'PASS')
        self.assertEqual(self.score(b'AxxxEF', [(1, 0, 0x0a)], {1, 2})[3], 'bytes differ')

    def test_funclet_and_alignment_padding_use_canonical_extent_and_skip_funclets(self):
        syms = {
            'candidate': (0, 0),
            '$LN1': (0, 2),
            '__unwindfunclet$?candidate@@YAHXZ$0': (0, 3),
            '__ehhandler$?candidate@@YAHXZ': (0, 5),
            'next': (0, 8),
        }
        rows = V.score_candidates([{'data': b'ABCDEF\xcc\xccNEXT\xcc', 'relocs': []}],
                                  syms, fingerprint(), b'ABCDEF')
        self.assertEqual([row[2] for row in rows], ['candidate', 'next'])
        self.assertEqual(rows[0], (0, 6, 'candidate', 'PASS'))

    def test_nonzero_symbol_offset(self):
        rows = V.score_candidates([{'data': b'PREFIXAxxxxF\xcc', 'relocs': [(7, 0, 0x14)]}],
                                  {'candidate': (0, 6)}, fingerprint(mask={1, 2, 3, 4}), b'ABCDEF')
        self.assertEqual(rows[0], (0, 6, 'candidate', 'PASS'))

    def test_incomplete_reference_is_an_error(self):
        with self.assertRaises(ValueError):
            V.score_candidates([], {}, fingerprint(), b'ABC')


class CliTests(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.root = Path(directory.name)
        path = self.root/'tools/ci/fingerprints.jsonl.gz'
        path.parent.mkdir(parents=True)
        with gzip.open(path, 'wt') as stream:
            stream.write(json.dumps(fingerprint())+'\n')
        self.compiler = Mock(returncode=0, stdout='', stderr='')
        def compile_object(command, **kwargs):
            output = next(arg[3:] for arg in command if arg.startswith('/Fo'))
            Path(output[2:].replace('\\', '/')).write_bytes(b'synthetic object')
            return self.compiler
        self.pe = Mock()
        self.pe.OPTIONAL_HEADER.ImageBase = 0x1000
        self.pe.get_data.return_value = b'ABCDEF'
        for manager in (
            patch.object(V, 'ROOT', str(self.root)),
            patch.object(V.subprocess, 'run', side_effect=compile_object),
            patch.object(V.F, 'parse_coff', return_value=([{'data': b'ABCDEF', 'relocs': []}], {'candidate': (0, 0)})),
            patch.object(V.pefile, 'PE', return_value=self.pe),
        ):
            manager.start()
            self.addCleanup(manager.stop)

    def test_verdict_label_and_flag_spellings(self):
        spellings = (
            ['source.cpp', '0x1000', '/vc71', '/O2', '/MD'],
            ['source.cpp', '0x1000', '/vc71 /O2 /MD'],
            ['source.cpp', '0x1000', '--flags', '/vc71 /O2 /MD'],
            ['--flags', '/vc71 /O2 /MD', 'source.cpp', '0x1000'],
        )
        for argv in spellings:
            with self.subTest(argv=argv):
                output = io.StringIO()
                with contextlib.redirect_stdout(output):
                    self.assertEqual(V.main(argv), 0)
                command = V.subprocess.run.call_args.args[0]
                self.assertIn('/vc71', command)
                self.assertIn('/O2', command)
                self.assertNotIn('--flags', command)
                self.assertNotIn('/vc71 /O2 /MD', command)
                self.assertIn('FINGERPRINT_PASS (run contribution gate)', output.getvalue())
                self.assertNotIn('<== MATCH', output.getvalue())
                self.pe.get_data.assert_called_with(0, 6)
                self.pe.close.assert_called()

    def test_missing_fingerprint_stops_before_compilation(self):
        with contextlib.redirect_stderr(io.StringIO()), self.assertRaises(SystemExit) as error:
            V.main(['source.cpp', '0x2000'])
        self.assertEqual(error.exception.code, 2)
        V.subprocess.run.assert_not_called()

    def test_compile_failure_never_scores_stale_object_and_cleans_tempdir(self):
        V.subprocess.run.side_effect = None
        self.compiler.returncode = 1
        V.subprocess.run.return_value = self.compiler
        with contextlib.redirect_stderr(io.StringIO()):
            self.assertEqual(V.main(['source.cpp', '0x1000']), 1)
        V.F.parse_coff.assert_not_called()
        self.assertEqual(list((self.root/'work/match/variants').glob('variant-*')), [])

    def test_success_without_output_cannot_reuse_previous_object_and_cleans_failed_tempdir(self):
        with contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(V.main(['source.cpp', '0x1000']), 0)
        previous = V.F.parse_coff.call_args.args[0]
        self.assertTrue(Path(previous).is_file())
        V.F.parse_coff.reset_mock()
        V.subprocess.run.side_effect = None
        V.subprocess.run.return_value = self.compiler
        with contextlib.redirect_stderr(io.StringIO()), contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(V.main(['source.cpp', '0x1000', '/Zs']), 1)
        V.F.parse_coff.assert_not_called()
        self.assertEqual([p / 'candidate.obj' for p in (self.root/'work/match/variants').glob('variant-*')],
                         [Path(previous)])

    def test_each_invocation_has_a_distinct_retained_object(self):
        outputs = []
        for _ in range(2):
            with contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(V.main(['source.cpp', '0x1000']), 0)
            outputs.append(V.F.parse_coff.call_args.args[0])
        self.assertNotEqual(outputs[0], outputs[1])
        self.assertTrue(all(Path(path).is_file() for path in outputs))

    def test_empty_object_has_no_success_verdict(self):
        V.F.parse_coff.return_value = ([], {})
        with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()), \
                self.assertRaises(SystemExit) as error:
            V.main(['source.cpp', '0x1000'])
        self.assertEqual(error.exception.code, 2)


if __name__ == '__main__':
    unittest.main()
