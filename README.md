vix
===

Vix is an experimental Vi clone.  It probably isn't something in which you are
interested yet.  I am a big fan of Bram Moolenaar's [Vim][vim], and use it for
my day-to-day programming work.  I highly suggest you start there if you are
looking for an excellent Vi clone.

Building
--------

To build vix, you will need a relatively recent version of Clang, Google Test,
Haskell (ghc running under Haskell Platform is best supported), and shake.  The
current build assumes that it is built as part of a Google repo / submodule, and
that Google Test is located under ../gtest.  Since vix is the support library
for the editor, it assumes that it is part of a larger project or tarball.

[vim]: http://www.vim.org
