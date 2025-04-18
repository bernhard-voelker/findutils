# Copyright (C) 2001-2025 Free Software Foundation, Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# The 2001 copyright line above was added in 2015 based on James
# Youngman's best estimate of the original publication date of this
# file (it appeared in findutils release 4.1.7 but may have appeared
# in earlier releases which I don't have copies of).

AUTOMAKE_OPTIONS = dejagnu parallel-tests
FIND = ../find
FINDFLAGS =

DEJATOOL = find

EXTRA_DIST_XO = \
find.gnu/access.xo \
find.gnu/comma.xo \
find.gnu/delete.xo \
find.gnu/deletedir.xo \
find.gnu/deletefile.xo \
find.gnu/depth.xo \
find.gnu/depth-d.xo \
find.gnu/empty.xo \
find.gnu/execdir-hier.xo   \
find.gnu/execdir-multiple.xo \
find.gnu/execdir-one.xo   \
find.gnu/execdir-root-only.xo   \
find.gnu/exec-many-rtn-failure.xo   \
find.gnu/exec-many-rtn-success.xo   \
find.gnu/exec-one-rtn-fail.xo       \
find.gnu/exec-one-rtn-success.xo \
find.gnu/false.xo \
find.gnu/follow-arg-parent-symlink.xo \
find.gnu/follow-basic.xo \
find.gnu/fprint0_stdout.xo \
find.gnu/gnuand.xo \
find.gnu/gnunot.xo \
find.gnu/gnu-or.xo \
find.gnu/ilname.xo \
find.gnu/iname.xo \
find.gnu/inum.xo \
find.gnu/ipath.xo \
find.gnu/iregex1.xo \
find.gnu/iwholename.xo \
find.gnu/lname.xo \
find.gnu/mindepth-arg.xo \
find.gnu/name-opt.xo \
find.gnu/name-period.xo \
find.gnu/name-slash.xo \
find.gnu/no-fdleak-test.xo \
find.gnu/path.xo \
find.gnu/print_stdout.xo \
find.gnu/perm.xo \
find.gnu/perm000.xo \
find.gnu/perm-slash.xo \
find.gnu/posix-dflt.xo \
find.gnu/posix-h.xo \
find.gnu/posix-l.xo \
find.gnu/printfHdfl.xo \
find.gnu/printf-nonlocal-symlink.xo \
find.gnu/printf-slash.xo \
find.gnu/printf-symlink.xo \
find.gnu/printf-h.xo \
find.gnu/printf.xo \
find.gnu/print0.xo \
find.gnu/prune-default-print.xo  \
find.gnu/regex1.xo \
find.gnu/regex2.xo \
find.gnu/samefile-copy.xo \
find.gnu/samefile-link.xo \
find.gnu/samefile-p-brokenlink.xo \
find.gnu/samefile-same.xo \
find.gnu/samefile-symlink.xo \
find.gnu/sv-bug-17782.xo \
find.gnu/sv-bug-18222.xo \
find.gnu/sv-bug-27563-execdir.xo \
find.gnu/true.xo \
find.gnu/wholename.xo \
find.gnu/xtype-symlink.xo \
find.gnu/quit.xo \
find.gnu/xtype.xo \
find.posix/and.xo \
find.posix/depth1.xo \
find.posix/dotdotfiles.xo \
find.posix/exec-nogaps.xo \
find.posix/exec-one.xo \
find.posix/files-not-expressions1.xo \
find.posix/files-not-expressions2.xo \
find.posix/files-not-expressions3.xo \
find.posix/grouping.xo \
find.posix/links.xo \
find.posix/sv-bug-11175.xo \
find.posix/sv-bug-12181.xo \
find.posix/sv-bug-25359.xo \
find.posix/sv-bug-27563-exec.xo \
find.posix/mtime0.xo \
find.posix/sizes.xo \
find.posix/name.xo \
find.posix/nameslash.xo \
find.posix/parent.xo \
find.posix/perm-X.xo \
find.posix/perm-vanilla.xo \
find.posix/posixnot.xo \
find.posix/prune.xo \
find.posix/prune-result.xo \
find.posix/prune-stat.xo \
find.posix/sizetype.xo \
find.posix/sv-bug-15235.xo \
find.posix/sv-bug-19613.xo \
find.posix/typesize.xo


EXTRA_DIST_EXP = \
config/unix.exp \
find.gnu/access.exp \
find.gnu/comma.exp \
find.gnu/delete.exp \
find.gnu/deletedir.exp \
find.gnu/deletefile.exp \
find.gnu/depth.exp \
find.gnu/depth-d.exp \
find.gnu/empty.exp \
find.gnu/execdir-hier.exp \
find.gnu/execdir-in-unreadable.exp \
find.gnu/execdir-multiple.exp \
find.gnu/execdir-one.exp \
find.gnu/execdir-pwd.exp \
find.gnu/execdir-pwd1.exp \
find.gnu/execdir-root-only.exp \
find.gnu/exec-many-rtn-failure.exp  \
find.gnu/exec-many-rtn-success.exp  \
find.gnu/exec-one-rtn-fail.exp      \
find.gnu/exec-one-rtn-success.exp   \
find.gnu/false.exp \
find.gnu/follow-arg-parent-symlink.exp \
find.gnu/follow-basic.exp \
find.gnu/fprint0_stdout.exp \
find.gnu/fprintf-samefile.exp \
find.gnu/fprint-unwritable.exp \
find.gnu/gnuand.exp \
find.gnu/gnunot.exp \
find.gnu/gnu-or.exp \
find.gnu/ilname.exp \
find.gnu/iname.exp \
find.gnu/inum.exp \
find.gnu/ipath.exp \
find.gnu/iregex1.exp \
find.gnu/iwholename.exp \
find.gnu/lname.exp \
find.gnu/mindepth-arg.exp \
find.gnu/mindepth-badarg.exp \
find.gnu/name-opt.exp \
find.gnu/name-period.exp \
find.gnu/name-slash.exp \
find.gnu/no-fdleak-test.exp \
find.posix/parent.exp \
find.gnu/path.exp \
find.gnu/print_stdout.exp \
find.gnu/print0.exp \
find.gnu/perm.exp \
find.gnu/perm000.exp \
find.gnu/perm-slash.exp \
find.gnu/posix-dflt.exp \
find.gnu/posix-h.exp \
find.gnu/posix-l.exp \
find.gnu/posix-perminvalid.exp \
find.gnu/printfHdfl.exp \
find.gnu/printf.exp \
find.gnu/printf-nonlocal-symlink.exp \
find.gnu/printf-slash.exp \
find.gnu/printf-symlink.exp \
find.gnu/printf-h.exp \
find.gnu/printf-reserved.exp \
find.gnu/prune-default-print.exp \
find.gnu/regex1.exp \
find.gnu/regex2.exp \
find.gnu/samefile-copy.exp \
find.gnu/samefile-link.exp \
find.gnu/samefile-missing.exp \
find.gnu/samefile-p-brokenlink.exp \
find.gnu/samefile-same.exp \
find.gnu/samefile-symlink.exp \
find.gnu/true.exp \
find.gnu/wholename.exp \
find.gnu/xtype-symlink.exp \
find.gnu/sv-bug-12230.exp \
find.gnu/sv-bug-17477.exp \
find.gnu/sv-bug-17490.exp \
find.gnu/sv-bug-17782.exp \
find.gnu/sv-bug-18222.exp \
find.gnu/sv-bug-24169.exp \
find.gnu/sv-bug-27563-execdir.exp \
find.gnu/quit.exp \
find.gnu/used-invarg.exp \
find.gnu/used-missing.exp \
find.gnu/user-invalid.exp \
find.gnu/xtype.exp \
find.posix/and.exp \
find.posix/bracket-depth.exp \
find.posix/depth1.exp \
find.posix/dotdotfiles.exp \
find.posix/empty-parens.exp \
find.posix/exec-nogaps.exp \
find.posix/exec-one.exp \
find.posix/files-not-expressions1.exp \
find.posix/files-not-expressions2.exp \
find.posix/files-not-expressions3.exp \
find.posix/grouping.exp \
find.posix/group-empty.exp \
find.posix/group-missing.exp \
find.posix/links.exp \
find.posix/mtime0.exp \
find.posix/sv-bug-11175.exp \
find.posix/sv-bug-12181.exp \
find.posix/sv-bug-25359.exp \
find.posix/sv-bug-27563-exec.exp \
find.posix/sv-bug-30777.exp \
find.posix/sizes.exp \
find.posix/name.exp \
find.posix/nameslash.exp \
find.posix/name-missing.exp \
find.posix/perm-X.exp \
find.posix/perm-vanilla.exp \
find.posix/posixnot.exp \
find.posix/prune.exp \
find.posix/prune-result.exp \
find.posix/prune-stat.exp \
find.posix/size-invalid.exp \
find.posix/size-missing.exp \
find.posix/sizetype.exp \
find.posix/typearg.exp \
find.posix/sv-bug-15235.exp \
find.posix/sv-bug-19605.exp \
find.posix/sv-bug-19613.exp \
find.posix/sv-bug-19617.exp \
find.posix/typesize.exp \
find.posix/user-empty.exp \
find.posix/user-missing.exp

EXTRA_DIST = $(EXTRA_DIST_EXP) $(EXTRA_DIST_XO) \
	checklists.py

CLEANFILES = *.log *.sum site.exp site.bak configured-testfiles.txt

#DIST_SUBDIRS = config

TEST_EXTENSIONS = .sh .py

check-local: checklists

configured-testfiles.txt: Makefile
	@echo Generating $@
	@( cd $(srcdir) && ls $(EXTRA_DIST_XO) && ls  $(EXTRA_DIST_EXP) ) >| $@

.PHONY: checklists

checklists: configured-testfiles.txt Makefile
	$(PYTHON) $(srcdir)/checklists.py configured-testfiles.txt $(srcdir) config find.gnu find.posix
