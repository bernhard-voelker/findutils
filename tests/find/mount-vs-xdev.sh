#!/bin/sh
# Exercise find -mount vs. -xdev behaviour.

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

# Require GNU df in getmntpoint.
for f in df gdf; do
  # Find GNU df.
  $f --version | grep GNU \
    && DF=$f
done
test "$DF" || skip_ "GNU df required."

getmntpoint () {
  # Skip header line and print last field.
  $DF "$1" | awk 'NR==2 {print $NF}'
}

mnt_root=$( getmntpoint '/' ) \
  && test "$mnt_root" \
  || framework_failure_

found=0
# Find a directory entry which is mounted (likely) from a different device
# than the '/' directory.
for m in /dev /home /proc /run /tmp; do
  test -d "$m" \
    && mnt_m=$( getmntpoint "$m" )  \
    && test "$mnt_root" != "$mnt_m" \
    && test "$m" = "$mnt_m" \
    || continue

  found=1
  echo "$m" > exp || framework_failure_

  # Option -mount skips.
  find / -maxdepth 1 -mount -path "$m" -print > out-m   || fail=1
  compare /dev/null out-m || fail=1

  # Option -xdev does not skip (but would skip sub-directories).
  find / -maxdepth 1 -xdev -path "$m" -print > out-x   || fail=1
  compare exp out-x || fail=1

  # Options -mount -xdev shall skip as well (-xdev has no effect).
  find / -maxdepth 1 -mount -xdev -path "$m" -print > out-mx  || fail=1
  compare /dev/null out-m || fail=1
done

test $found -gt 0 \
  || skip_ "cannot determine other device mounts in '/'"

Exit $fail
