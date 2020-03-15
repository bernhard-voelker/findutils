#! /bin/sh
# Copyright (C) 2019-2020 Free Software Foundation, Inc.
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

##
## This script updates the online manual for findutils.
##
## When you run it, make sure you are in the "manual" directory.
PACKAGE=findutils
TITLE="Findutils"
TEXIBASE=find

set -e

usage() {
cat <<EOF
usage: $0 location-of-${PACKAGE}-build-directory
EOF
}

checkfiles="CVS dvi ${TEXIBASE}.html html_node html_mono info ps texi text ${TEXIBASE}.pdf"
targets="dvi html info pdf ${TEXIBASE}.ps ${TEXIBASE}.txt ${PACKAGE}.texi_html_node.tar.gz ${TEXIBASE}_mono.html ${TEXIBASE}.texi.tar.gz ${TEXIBASE}-info.tar.gz"

if [ $# -ne 1 ]; then
	usage >&2
	exit 1
fi

BUILDDIR="$1"
DOC_OUTPUT_DIR="`pwd`"

echo Current directory is `pwd`

echo "Are we in the right place?  "
for f in $checkfiles
do
  if test -e "$f"; then
      echo "  $f seems to be there"
  else
      printf "  No, %s is missing.\n" "$f" >&2
      exit 1
  fi
done
echo "Yes, we are in the right place"


printf "Can we see the build directory?  "
if [ -d "$BUILDDIR" ]; then
    echo Yes.
else
    echo "No." >&2 ; exit 1
fi

printf "Does the build directory have a 'doc' subdirectory?  "
if [ -d "$BUILDDIR/doc" ]; then
    echo Yes.
else
    echo "No." >&2 ; exit 1
fi
BUILDDIR="$BUILDDIR"/doc

printf "Does the (doc) build directory have a Makefile?  "
if [ -f "$BUILDDIR"/Makefile ]; then
    echo Yes.
else
    echo "No." >&2 ; exit 1
fi


##
## Figure out where the source code lives by asking Make.
##
REL_SRCDIR="$(cd $BUILDDIR && grep '^srcdir =' Makefile | cut -d= -f2)"
echo Build directory is $BUILDDIR.
echo Relative path to source directory is $REL_SRCDIR

SRCDIR="$(cd $BUILDDIR && cd $REL_SRCDIR && /bin/pwd)"
unset REL_SRCDIR
echo Source directory is $SRCDIR.


if true
then
    ##
    ## Build (most of) the files we need.
    ## We collect them from the build directory afterwards.
    ##
    make -C "$BUILDDIR" $targets
    cp ${BUILDDIR}/${TEXIBASE}.texi.tar.gz texi/${TEXIBASE}.texi.tar.gz
    cp ${BUILDDIR}/${TEXIBASE}-info.tar.gz info/${TEXIBASE}-info.tar.gz

    echo Collecting the PostScript file...
    rm -f ps/${TEXIBASE}.ps.gz
    gzip -9 < ${BUILDDIR}/${TEXIBASE}.ps > ps/${TEXIBASE}.ps.gz

    echo Collecting the DVI file...
    cp  $BUILDDIR/${TEXIBASE}.dvi dvi/
    rm dvi/${TEXIBASE}.dvi.gz
    gzip -9 dvi/${TEXIBASE}.dvi

    echo Collecting the PDF file...
    cp  $BUILDDIR/${TEXIBASE}.pdf .

    echo "Collecting the text files (compressed and uncompressed)..."
    rm -f text/${TEXIBASE}.txt text/${TEXIBASE}.txt.gz
    cp $BUILDDIR/${TEXIBASE}.txt text/
    gzip -9 text/${TEXIBASE}.txt
    cp $BUILDDIR/${TEXIBASE}.txt text/

    echo "Collecting the all-in-one-file HTML (compressed and uncompressed)..."
    rm -f html_mono/${TEXIBASE}.html html_mono/${TEXIBASE}.html.gz
    cp $BUILDDIR/${TEXIBASE}_mono.html html_mono/${TEXIBASE}.html
    gzip -9 html_mono/${TEXIBASE}.html
    cp $BUILDDIR/${TEXIBASE}_mono.html html_mono/${TEXIBASE}.html


    echo "Collecting the file-per-node HTML tar file..."
    rm -f html_node/${PACKAGE}.texi_html_node.tar.gz
    find html_node/${TEXIBASE}_html -name '*.html' -type f -delete
    cp $BUILDDIR/${PACKAGE}.texi_html_node.tar.gz html_node/

    echo "Unpacking the node-per-node HTML tar file..."
    ( cd html_node && tar zxf ${PACKAGE}.texi_html_node.tar.gz && mv ${TEXIBASE}.html/*.html ${TEXIBASE}_html )

fi

size () {
    du -sh --apparent-size "$1" | awk '{print $1;}'
}


linkfor() {
    what="$1"
    type="$2"
    shift 2
    printf '<A HREF="%s">%s (%s %s)</A>' \
	"$what" "$*" "$(size $what)" "$type"
}

##
##
## Now the rather complex bit; generate the index page!
##
##
echo "Generating the index page..."
cat >${TEXIBASE}.html <<EOF
<!--#include virtual="/server/header.html" -->
<TITLE>Finding Files: Table of Contents - GNU Project - Free Software Foundation (FSF)</TITLE>
<LINK REV="made" HREF="mailto:webmasters@www.gnu.org">
<META NAME="keywords" CONTENT="GNU, findutils, xargs, find, locate, finding files, file search, disk search, file name database, expand arguments, free software">
<meta http-equiv="Description" content="Tools for searching file systems" />
<BASE HREF="https://www.gnu.org/software/findutils/manual/find.html">
<!--#include virtual="/server/banner.html" -->
<H2>Findutils: Table of Contents</H2>
<P>
This manual is available in the following formats:

<P>
<UL>
  <LI>
      $(linkfor html_mono/${TEXIBASE}.html "characters" HTML)
      entirely on one web page.
  </LI>
  <LI>
      $(linkfor html_mono/${TEXIBASE}.html.gz "gzipped characters" HTML)
      entirely on one web page.
  </LI>
  <LI> <a href="html_node/${TEXIBASE}_html/index.html">HTML (total size $(size html_node/${TEXIBASE}_html))</a>
    with one web page per node.
  </LI>
  <LI> $(linkfor "html_node/${PACKAGE}.texi_html_node.tar.gz" "gzipped tar file" HTML)
    with one web page per node.
  </LI>
  <LI>
      $(linkfor "info/${TEXIBASE}-info.tar.gz" "gzipped tar file" "Info document")
  </LI>
  <LI>
      $(linkfor "text/${TEXIBASE}.txt" "characters" "ASCII text")
  </LI>
  <LI>
      $(linkfor "text/${TEXIBASE}.txt.gz" "gzipped characters" "ASCII text")
  </LI>
  <LI>
      $(linkfor "dvi/${TEXIBASE}.dvi.gz" "gzipped" "a TeX dvi file")
  </LI>
  <LI>
      $(linkfor "ps/${TEXIBASE}.ps.gz" "gzipped characters" "a PostScript file")
  </LI>
  <LI>
      $(linkfor "${TEXIBASE}.pdf" "PDF file" PDF)
  </LI>
  <LI>the original
      $(linkfor "texi/${TEXIBASE}.texi.tar.gz" "character gzipped tar file" "Texinfo source")
  </LI>
</UL>

</div><!-- for id="content", starts in the include above -->
<!--#include virtual="/server/footer.html" -->
<div id="footer">

<P>
Return to <A HREF="/home.html">GNU's home page</A>.

<P>
Please send FSF &amp; GNU inquiries &amp; questions to
<A HREF="mailto:gnu@gnu.org"><EM>gnu@gnu.org</EM></A>.
Other <A HREF="https://www.fsf.org/about/contact.html">ways to contact</A> the FSF.

<P>
Please send comments on these web pages to
<A HREF="mailto:webmasters@www.gnu.org"><EM>webmasters@www.gnu.org</EM></A>,
send other questions to
<A HREF="mailto:gnu@gnu.org"><EM>gnu@gnu.org</EM></A>.

<P>
Copyright &copy; 1997, 1998, 2003, 2005, 2006, 2008 Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,  USA

<P>
Verbatim copying and distribution of this entire article is
permitted in any medium, provided this notice is preserved.

<!-- This document was updated $(LC_TIME=C date +"%B %d, %Y") by $0 "$@" -->
<P>
Updated:
\$Date: 2019/05/05 15:13:38 $ \$Author: james $

<P>
<HR>

</BODY>
</HTML>

EOF

echo "All done."
