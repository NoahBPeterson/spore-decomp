"""Queue regressions; no game image, compiler, or network access required.

Run: python3 -m unittest discover -s tools/contrib -p 'test_task.py'
"""
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent))
import task  # noqa: E402
import run_all  # noqa: E402


class DiffCountTests(unittest.TestCase):
    def test_measured_counts(self):
        for token in ('12', '~12', '12?', '~12?', ' 12 ', 12):
            with self.subTest(token=token):
                self.assertEqual(task.ndiff(token), 12)

    def test_unknown_or_malformed_counts(self):
        for token in (None, '', '-', '-1', '1480/1510', '12garbage', 'abc12',
                      '12.5', '+12', '0', '~0', '0?', 0):
            with self.subTest(token=token):
                self.assertIsNone(task.ndiff(token))


class QueueTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        files = {
            'symbols/lib_names.txt': '# libraries\n00000001 library # comment\n\n00000006 unstarted_library\n',
            'match/slices/example/nonmatching.txt':
                '00000001 1 library\n00000002 - schedule: pending\n00000003 2 already matched\n00000004 3 large\n',
            'src/game/example/nonmatching.txt': '00000002 - schedule: migrated\n',
        }
        for name, text in files.items():
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text)
        for manager in (
            patch.object(task, 'ROOT', str(self.root)),
            patch.object(task, 'fingerprints', return_value={va: {'size': 16 if va != 4 else 256}
                                                            for va in range(1, 8)}),
            patch.object(run_all, 'manifests', return_value=[]),
            patch.object(run_all, 'read_rows', return_value=[('source', 'symbol', 3, ())]),
        ):
            manager.start()
            self.addCleanup(manager.stop)

    def test_open_queue_excludes_libraries_done_and_oversized(self):
        rows = task.open_work(64)
        self.assertEqual([row[1] for row in rows], [2])
        self.assertEqual(rows[0][3], str(Path('src/game/example')))
        self.assertEqual(rows[0][2], '-')

    def test_size_limit_is_inclusive(self):
        self.assertEqual({row[1] for row in task.open_work(16)}, {2})
        self.assertEqual(task.open_work(15), [])
        self.assertEqual({row[1] for row in task.open_work(256)}, {2, 4})

    def test_unstarted_queue_uses_same_library_exclusion(self):
        self.assertEqual({row[1] for row in task.never_tried(64)}, {5, 7})


if __name__ == '__main__':
    unittest.main()
