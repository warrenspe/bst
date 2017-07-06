import os
import distutils.core

DEBUG_COMPILE_ARGS = None
VERSION = "0.0.1"
NAME = "bst"
DESCRIPTION = "Python binary search tree package written in C."
KEYWORDS = ["binary", "search", "tree", "C"]

if "DEBUG" in os.environ:
    DEBUG_COMPILE_ARGS = ['-O0', '-g', '-pedantic-errors', '-Wall', '-Wextra', '-Wmissing-prototypes',
                          '-Wstrict-prototypes', '-Wold-style-definition']

distutils.core.setup(
    name=NAME,
    version=VERSION,
    description=DESCRIPTION,
    author="Warren Spencer",
    author_email="warrenspencer27@gmail.com",
    url="https://github.com/warrenspe/%s" % NAME,
    download_url="https://github.com/warrenspe/%s/tarball/%s" % (NAME, VERSION),
    keywords=KEYWORDS,
    classifiers=[],
    license="https://opensource.org/licenses/MIT",
    platforms=["Linux", "Windows"],
    ext_modules=[
        distutils.core.Extension(
            NAME,
            sources = ['{0}/{0}.c'.format(NAME)],
            include_dirs = [NAME],
            extra_compile_args=DEBUG_COMPILE_ARGS
        )
     ]
)
