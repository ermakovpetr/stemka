/*
 * Copyright (c) 1994-2002
 *	Andrew Kovalenko aka Keva.  All rights reserved.
 *      http://linguist.nm.ru/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Redistributions in any form must be accompanied by information on
 *    how to obtain complete source code for the stemming software and any
 *    accompanying software that uses the stemming software.  The source code
 *    must either be included in the distribution or be available for no
 *    more than the cost of distribution plus a nominal fee, and must be
 *    freely redistributable under reasonable conditions.  For an
 *    executable file, complete source code means the source code for all
 *    modules it contains.  It does not include source code for modules or
 *    files that typically accompany the major components of the operating
 *    system on which the executable file runs.
 *
 * THIS SOFTWARE IS PROVIDED BY ANDREW KOVALENKO ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT, ARE DISCLAIMED.  IN NO EVENT SHALL ANDREW KOVALENKO
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
# if !defined( __flexrule_h__ )
# define  __flexrule_h__
# include "regexapi.h"
# include "flexTree.h"

struct  flexrule
{
  CRegExp   regexp;
# if defined( _DEBUG )
  char      sregex[32];
  char      cutstr[16];     /* the string tu cut from the form tail     */
# endif  // _DEBUG
  char      append[16];     /* the string to concat with selected stem  */
  char      reglen;         /* the regular expression length (chars)    */
  char      cutlen;         /* the length to cut tail                   */
  char      prefix;         /* != 0 if a prefix rule                    */
public:
                flexrule();
  int           GenFlex( const char* lpword, flexTree& rftree );
  int           Matches( const char* lpword );
};

struct  flagrule
{
  flexrule**    prules;
  unsigned      nrules;
  char          prefix; /* != 0 if a prefix rule                    */
public:
                flagrule();
               ~flagrule();
  int           GenFlex( const char* lpword, flexTree& rftree );
  flexrule*     NewRule();
};

struct  rulesbox
{
  flagrule**    prules;
public:
                rulesbox();
               ~rulesbox();
  int           GenFlex( const char*  lpword,
                         const char*  pflags,
                         flexTree&    rftree );
  flagrule*     NewRule( unsigned char chname );
protected:
  flagrule*     GetRule( unsigned char chname );
};

inline  void  InvertString( char* string )
{
  char* strorg = string;
  char* strend = string;

  while ( strend[0] != '\0' )
    ++strend;
  --strend;
  while ( strorg < strend )
  {
    char  chswap = strorg[0];
    *strorg++ = strend[0];
    *strend-- = chswap;
  }
}

# endif  // __flexrule_h__
