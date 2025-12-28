#!/bin/sh
# Exercise find -mount vs. -xdev behaviour with another file system.

# Copyright (C) 2026 Free Software Foundation, Inc.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

. "${srcdir=.}/tests/init.sh"; fu_path_prepend_
print_ver_ find

# The test setup requires root permissions (while the pure test run would not).
require_root_

cwd=$(pwd)
cleanup_() {
  cd /
  test -s "$cwd/mntf" \
    && umount "$cwd/mntf"
  umount "$cwd/mnt"
}

mkdir d mnt || framework_failure_

# Mount an ext2 loopback file system at 'mnt'.
dd if=/dev/zero of='fs' bs=8192 count=200 2>/dev/null || framework_failure_
mkfs -t ext2 -F 'fs' || skip_ "failed to create ext2 file system"
mount -oloop fs mnt \
  || skip_ 'insufficient mount/ext2 support'

echo test > mnt/file || framework_failure_
echo './mnt/file' > exp || framework_failure_

find              -name 'file' > out || fail=1
find -xdev        -name 'file' > out-x || fail=1
find -mount       -name 'file' > out-m || fail=1
find -mount -xdev -name 'file' > out-mx || fail=1

# Only the run without -mount and/or -xdev found 'mnt/file'.
compare exp out || fail=1
compare /dev/null out-x || fail=1
compare /dev/null out-m || fail=1
compare /dev/null out-mx || fail=1

# Now bind-mount 'mnt/file' back on 'mntf' into the current file system.
> mntf || framework_failure_
mount --bind mnt/file mntf \
  || skip_ "This test requires mount with a working --bind option."


# Only the run without options and pure -xdev should find the file 'mntf',
# and the runs with -mount (with or without -xdev) should ignore it.
echo './mntf' > exp || framework_failure_

find -name mntf > out || fail=1
compare exp out || fail=1

find -xdev -name mntf > out-x || fail=1
compare exp out-x || fail=1

find -mount -name mntf > out-m || fail=1
compare /dev/null out-m || fail=1

find -mount -xdev -name mntf > out-mx || fail=1
compare /dev/null out-mx || fail=1

Exit $fail
