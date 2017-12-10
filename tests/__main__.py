"""
Run the unit tests.

Usage: python tests
"""

# Standard imports
import os
import unittest
import argparse

# Globals
TEST_DIR = os.path.split(os.path.dirname(os.path.realpath(__file__)))[-1]

def _getTestSuite(testFiles):
    """
    Loads unit tests recursively from beneath the current directory.

    Inputs: testFiles - If non-empty, a list of unit tests to selectively run.

    Outputs: A unittest.TestSuite object containing the unit tests to run.
    """

    loader = unittest.TestLoader()

    if testFiles:
        return loader.loadTestsFromNames([".".join(TEST_DIR, testFile) for testFile in testFiles])
    
    return loader.discover(TEST_DIR)

def _runTestSuite(suite, verbosity):
    """
    Runs the unit tests contained within the given test suite.

    Inputs: suite     - A unittest.TestSuite object containing the unit tests to run.
            verbosity - An integer indicating the verbosity level to run the unit tests with.
    """

    runner = unittest.TextTestRunner(verbosity=verbosity)
    runner.run(suite)

def main():
    parser = argparse.ArgumentParser(description="Execute hconf Unit Tests")
    parser.add_argument("testModules", nargs="*")
    parser.add_argument("--verbosity", nargs="?", choices=['1', '2'], default=1)
    args = parser.parse_args()

    tests = _getTestSuite(args.testModules)
    _runTestSuite(tests, args.verbosity)

if __name__ == '__main__':
    main()

