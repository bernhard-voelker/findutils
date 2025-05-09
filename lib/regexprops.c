/* regexprops.c -- document the properties of the regular expressions
   understood by gnulib.

   Copyright (C) 2005-2025 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


/*
  The output of this program is included in the GNU findutils source
  distribution.  The copying conditions for that file are generated
  by the copying() function below.
*/

/* Written by James Youngman, <jay@gnu.org>. */

/* config.h must be included first. */
#include <config.h>

/* system headers */
#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* gnulib headers */
#include "progname.h"

/* find headers */
#include "regextype.h"

static void
output (const char *s, int escape)
{
  (void) escape;

  fputs (s, stdout);
}


static void
newline (void)
{
  output ("\n", 0);
}

static void
content (const char *s)
{
  output (s, 1);
}

static void
literal (const char *s)
{
  output (s, 0);
}

static void
directive (const char *s)
{
  output (s, 0);
}

static void
comment (const char *s)
{
  directive ("@c");
  if (s[0])
    {
      literal (" ");
      literal (s);
    }
  newline ();
}

static void
enum_item (const char *s)
{
  newline ();
  directive ("@item ");
  literal (s);
  newline ();
}

static void
begin_subsection (const char *name,
                  const char *next,
                  const char *prev,
                  const char *up)
{
  (void) next;
  (void) prev;
  (void) up;

  newline ();

  directive ("@node ");
  content (name);
  content (" regular expression syntax");
  newline ();

  directive ("@subsection ");
  output ("@samp{", 0);
  content (name);
  output ("}", 0);
  content (" regular expression syntax");
  newline ();
}

static void
begintable_markup (char const *markup)
{
  newline ();
  directive ("@table ");
  literal (markup);
  newline ();
}

static void
endtable (void)
{
  newline ();
  directive ("@end table");
  newline ();
}

static void
beginenum (void)
{
  newline ();
  directive ("@enumerate");
  newline ();
}

static void
endenum (void)
{
  newline ();
  directive ("@end enumerate");
  newline ();
}

static void
newpara (void)
{
  content ("\n\n");
}


static void
describe_regex_syntax (int options)
{
  newpara ();
  content ("The character @samp{.} matches any single character");
  if ( (options & RE_DOT_NEWLINE)  == 0 )
    {
      content (" except newline");
    }
  if (options & RE_DOT_NOT_NULL)
    {
      if ( (options & RE_DOT_NEWLINE)  == 0 )
        content (" and");
      else
        content (" except");

      content (" the null character");
    }
  content (".");
  newpara ();

  if (!(options & RE_LIMITED_OPS))
    {
      begintable_markup ("@samp");
      if (options & RE_BK_PLUS_QM)
        {
          enum_item ("\\+");
          content ("indicates that the regular expression should match one"
                   " or more occurrences of the previous atom or regexp.");
          enum_item ("\\?");
          content ("indicates that the regular expression should match zero"
                   " or one occurrence of the previous atom or regexp.");
          enum_item ("+ and ?");
          content ("match themselves.\n");
        }
      else
        {
          enum_item ("+");
          content ("indicates that the regular expression should match one"
                   " or more occurrences of the previous atom or regexp.");
          enum_item ("?");
          content ("indicates that the regular expression should match zero"
                   " or one occurrence of the previous atom or regexp.");
          enum_item ("\\+");
          literal ("matches a @samp{+}");
          enum_item ("\\?");
          literal ("matches a @samp{?}.");
        }
      endtable ();
    }

  newpara ();

  content ("Bracket expressions are used to match ranges of characters.  ");
  literal ("Bracket expressions where the range is backward, for example @samp{[z-a]}, are ");
  if (options & RE_NO_EMPTY_RANGES)
    content ("invalid");
  else
    content ("ignored");
  content (".  ");

  if (options &  RE_BACKSLASH_ESCAPE_IN_LISTS)
    literal ("Within square brackets, @samp{\\} can be used to quote "
             "the following character.  ");
  else
    literal ("Within square brackets, @samp{\\} is taken literally.  ");

  if (options & RE_CHAR_CLASSES)
    content ("Character classes are supported; for example "
             "@samp{[[:digit:]]} will match a single decimal digit.\n");
  else
    literal ("Character classes are not supported, so for example "
             "you would need to use @samp{[0-9]} "
             "instead of @samp{[[:digit:]]}.\n");

  if (options & RE_HAT_LISTS_NOT_NEWLINE)
    {
      literal ("Non-matching lists @samp{[^@dots{}]} do not ever match newline.\n");
    }
  newpara ();
  if (options & RE_NO_GNU_OPS)
    {
      content ("GNU extensions are not supported and so "
               "@samp{\\w}, @samp{\\W}, @samp{\\<}, @samp{\\>}, @samp{\\b}, @samp{\\B}, @samp{\\`}, and @samp{\\'} "
               "match "
               "@samp{w}, @samp{W}, @samp{<}, @samp{>}, @samp{b}, @samp{B}, @samp{`}, and @samp{'} respectively.\n");
    }
  else
    {
      content ("GNU extensions are supported:");
      beginenum ();
      enum_item ("@samp{\\w} matches a character within a word");
      enum_item ("@samp{\\W} matches a character which is not within a word");
      enum_item ("@samp{\\<} matches the beginning of a word");
      enum_item ("@samp{\\>} matches the end of a word");
      enum_item ("@samp{\\b} matches a word boundary");
      enum_item ("@samp{\\B} matches characters which are not a word boundary");
      enum_item ("@samp{\\`} matches the beginning of the whole input");
      enum_item ("@samp{\\'} matches the end of the whole input");
      endenum ();
    }

  newpara ();


  if (options & RE_NO_BK_PARENS)
    {
      literal ("Grouping is performed with parentheses @samp{()}.  ");

      if (options & RE_UNMATCHED_RIGHT_PAREN_ORD)
        literal ("An unmatched @samp{)} matches just itself.  ");
    }
  else
    {
      literal ("Grouping is performed with backslashes followed by parentheses @samp{\\(}, @samp{\\)}.  ");
    }

  if (options & RE_NO_BK_REFS)
    {
      content ("A backslash followed by a digit matches that digit.");
    }
  else
    {
      literal ("A backslash followed by a digit acts as a back-reference and matches the same thing as the previous grouped expression indicated by that number.  For example @samp{\\2} matches the second group expression.  The order of group expressions is determined by the position of their opening parenthesis ");
      if (options & RE_NO_BK_PARENS)
        literal ("@samp{(}");
      else
        literal ("@samp{\\(}");
      content (".");
    }


  newpara ();
  if (!(options & RE_LIMITED_OPS))
    {
      if (options & RE_NO_BK_VBAR)
        literal ("The alternation operator is @samp{|}.");
      else
        literal ("The alternation operator is @samp{\\|}.");
    }
  newpara ();

  if (options & RE_CONTEXT_INDEP_ANCHORS)
    {
      literal ("The characters @samp{^} and @samp{$} always represent the beginning and end of a string respectively, except within square brackets.  Within brackets, @samp{^} can be used to invert the membership of the character class being specified.\n");
    }
  else
    {
      literal ("The character @samp{^} only represents the beginning of a string when it appears:");
      beginenum ();
      enum_item ("At the beginning of a regular expression");
      if (options & RE_NO_BK_PARENS)
        {
          enum_item ("After an open-group, signified by @samp{(}");
        }
      else
        {
          enum_item ("After an open-group, signified by @samp{\\(}");
        }
      newline ();
      if (!(options & RE_LIMITED_OPS))
        {
          if (options & RE_NEWLINE_ALT)
            enum_item ("After a newline");

          if (options & RE_NO_BK_VBAR )
            enum_item ("After the alternation operator @samp{|}");
          else
            enum_item ("After the alternation operator @samp{\\|}");
        }
      endenum ();

      newpara ();
      literal ("The character @samp{$} only represents the end of a string when it appears:");
      beginenum ();
      enum_item ("At the end of a regular expression");
      if (options & RE_NO_BK_PARENS)
        {
          enum_item ("Before a close-group, signified by @samp{)}");
        }
      else
        {
          enum_item ("Before a close-group, signified by @samp{\\)}");
        }
      if (!(options & RE_LIMITED_OPS))
        {
          if (options & RE_NEWLINE_ALT)
            enum_item ("Before a newline");

          if (options & RE_NO_BK_VBAR)
            enum_item ("Before the alternation operator @samp{|}");
          else
            enum_item ("Before the alternation operator @samp{\\|}");
        }
      endenum ();
    }
  newpara ();
  if (!(options & RE_LIMITED_OPS) )
    {
      if ((options & RE_CONTEXT_INDEP_OPS)
          && !(options & RE_CONTEXT_INVALID_OPS))
        {
          literal ("The characters @samp{*}, @samp{+} and @samp{?} are special anywhere in a regular expression.\n");
        }
      else
        {
          if (options & RE_BK_PLUS_QM)
            literal ("@samp{\\*}, @samp{\\+} and @samp{\\?} ");
          else
            literal ("@samp{*}, @samp{+} and @samp{?} ");

          if (options & RE_CONTEXT_INVALID_OPS)
            {
              content ("are special at any point in a regular expression except the following places, where they are not allowed:");
            }
          else
            {
              content ("are special at any point in a regular expression except:");
            }

          beginenum ();
          enum_item ("At the beginning of a regular expression");
          if (options & RE_NO_BK_PARENS)
            {
              enum_item ("After an open-group, signified by @samp{(}");
            }
          else
            {
              enum_item ("After an open-group, signified by @samp{\\(}");
            }
          if (!(options & RE_LIMITED_OPS))
            {
              if (options & RE_NEWLINE_ALT)
                enum_item ("After a newline");

              if (options & RE_NO_BK_VBAR)
                enum_item ("After the alternation operator @samp{|}");
              else
                enum_item ("After the alternation operator @samp{\\|}");
            }
          endenum ();
        }
    }


  newpara ();
  if (options & RE_INTERVALS)
    {
      if (options & RE_NO_BK_BRACES)
        {
          literal ("Intervals are specified by @samp{@{} and @samp{@}}.\n");
          if (options & RE_INVALID_INTERVAL_ORD)
            {
              literal ("Invalid intervals are treated as literals, for example @samp{a@{1} is treated as @samp{a\\@{1}");
            }
          else
            {
              literal ("Invalid intervals such as @samp{a@{1z} are not accepted.\n");
            }
        }
      else
        {
          literal ("Intervals are specified by @samp{\\@{} and @samp{\\@}}.\n");
          if (options & RE_INVALID_INTERVAL_ORD)
            {
              literal ("Invalid intervals are treated as literals, for example @samp{a\\@{1} is treated as @samp{a@{1}");
            }
          else
            {
              literal ("Invalid intervals such as @samp{a\\@{1z} are not accepted.\n");
            }
        }
    }

  newpara ();
  if (options & RE_NO_POSIX_BACKTRACKING)
    {
      content ("Matching succeeds as soon as the whole pattern is matched, meaning that the result may not be the longest possible match.");
    }
  else
    {
      content ("The longest possible match is returned; this applies to the regular expression as a whole and (subject to this constraint) to subexpressions within groups.");
    }
  newpara ();
}


static void
copying (void)
{
  static const char *copy_para[]=
    {
      /* The copyright year number range is with "--" in Texinfo files.  */
      "Copyright (C) 1994--2025 Free Software Foundation, Inc."
      ,""
      ,"Permission is granted to copy, distribute and/or modify this document"
      ,"under the terms of the GNU Free Documentation License, Version 1.3 or"
      ,"any later version published by the Free Software Foundation; with no"
      ,"Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts."
      ,"A copy of the license is included in the ``GNU Free"
      ,"Documentation License'' file as part of this distribution."
      ""
      ,NULL
    };
  const char **s = copy_para;
  while (*s)
    comment (*s++);
}

static int
ignore (int ix, const unsigned int context)
{
  return 0 == (get_regex_type_context (ix) & context);
}

static void
menu (unsigned int context)
{
  int i;
  const char *name;

  output ("@menu\n", 0);
  for (i=0;
       get_regex_type_flags (i),
         name=get_regex_type_name (i);
       ++i)
    {
      if (!ignore (i, context))
        {
          output ("* ", 0);
          output (name, 0);
          content (" regular expression syntax");
          output ("::", 0);
          newline ();
        }
    }
  output ("@end menu\n", 0);
}



static const char *
get_next (unsigned int ix, unsigned int context)
{
  const char *next;
  while (get_regex_type_name (ix))
    {
      if (!ignore (ix, context))
        {
          next = get_regex_type_name (ix);
          if (NULL == next)
            return "";
          else
            return next;
        }
      ++ix;
    }
  return "";
}


static void
describe_all (const char *contextname,
              unsigned int context,
              const char *up)
{
  const char *name, *next, *previous;
  int regopts;
  int i, parent;

  copying ();
  newline ();
  literal ("@c this regular expression description is for: ");
  literal (contextname);
  newline ();
  newline ();
  menu (context);

  previous = "";

  for (i=0;
       regopts = get_regex_type_flags (i),
         name=get_regex_type_name (i);
       ++i)
    {
      if (ignore (i, context))
        {
          fprintf (stderr,
                   "Skipping regexp type %s for context %s\n",
                   name, contextname);
          name = previous;
          continue;
        }

      next = get_next (i+1, context);
      if (NULL == next)
        next = "";
      begin_subsection (name, next, previous, up);
      parent = get_regex_type_synonym (i, context);
      if (parent >= 0)
        {
          content ("This is a synonym for ");
          content (get_regex_type_name (parent));
          content (".");
        }
      else
        {
          describe_regex_syntax (regopts);
        }
      previous = name;
    }
}



int
main (int argc, char *argv[])
{
  const char *up = "";
  unsigned int context = CONTEXT_ALL;
  const char *contextname = "all";

  if (argc)
    set_program_name (argv[0]);
  else
    set_program_name ("regexprops");

  if (argc > 1)
    {
      up = argv[1];
    }
  if (argc > 2)
    {
      contextname = argv[2];
      if (0 == strcmp (contextname, "findutils"))
        context = CONTEXT_FINDUTILS;
      else if (0 == strcmp (contextname, "generic"))
        context = CONTEXT_GENERIC;
      else if (0 == strcmp (contextname, "all"))
        context = CONTEXT_ALL;
      else
        {
          fprintf (stderr, "Unexpected context %s",
                   contextname);
          return 1;
        }
    }

  describe_all (contextname, context, up);
  return 0;
}
