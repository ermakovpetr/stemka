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
# include "flexrule.h"

// flexrule implementation

flexrule::flexrule(): reglen( 0 ),
                      cutlen( 0 ),
                      prefix( 0 )
{
}

int     flexrule::GenFlex( const char*  lpword,
                           flexTree&    rftree )
{
  char    szform[256];
  int     length = strlen( lpword );

  assert( Matches( lpword ) );

  if ( !prefix && length - cutlen >= 2 )
  {
    memcpy( szform, lpword + length - cutlen - 2, 2 );
    strcpy( szform + 2, append );
    InvertString( szform );
    rftree.AddNode( szform );
  }
  return 1;
}

int     flexrule::Matches( const char* lpword )
{
  unsigned  length = strlen( lpword );

  return length >= (unsigned)reglen && regexp.IsAccept( lpword + length - reglen );
}

// flagrule implementation

flagrule::flagrule(): prules( NULL ),
                      nrules( 0 )
{
}

flagrule::~flagrule()
{
  unsigned  nindex;

  for ( nindex = 0; nindex < nrules; nindex++ )
    if ( prules[nindex] != NULL )
      delete prules[nindex];
  delete prules;
}

int       flagrule::GenFlex( const char* lpword,
                             flexTree&   rftree )
{
  unsigned  nindex;

  for ( nindex = 0; nindex < nrules; nindex++ )
    if ( prules[nindex]->Matches( lpword ) )
      if ( !prules[nindex]->GenFlex( lpword, rftree ) )
        return 0;
  return 1;
}

flexrule* flagrule::NewRule()
{
  if ( (nrules & 0x0f) == 0 )
  {
    unsigned    newcnt = nrules + 0x10;
    flexrule**  palloc = new flexrule* [newcnt];

    if ( nrules )
      memcpy( palloc, prules, nrules * sizeof(flexrule*) );
    memset( palloc + nrules, 0, (newcnt - nrules) * sizeof(flexrule*) );
    if ( prules != NULL )
      delete [] prules;
    prules = palloc;
  }
  return prules[nrules++] = new flexrule;
}

// rulesbox implementation

rulesbox::rulesbox()
{
  prules = new flagrule* [256];
  memset( prules, 0, 256 * sizeof(flagrule*) );
}

rulesbox::~rulesbox()
{
  unsigned  uindex;

  for ( uindex = 0; uindex < 256; uindex++ )
    if ( prules[uindex] != NULL )
      delete prules[uindex];
  delete [] prules;
}

flagrule* rulesbox::GetRule( unsigned char chname )
{
  if ( prules[chname] == NULL )
    fprintf( stderr, "Undefined rule \'%c\'!\n", chname );
  return prules[chname];
}

flagrule* rulesbox::NewRule( unsigned char chname )
{
  if ( prules[chname] == NULL )
    prules[chname] = new flagrule;
  return prules[chname];
}

int   rulesbox::GenFlex( const char* lpword,
                         const char* pflags,
                         flexTree&   rftree )
{
  while ( pflags[0] != '\0' )
  {
    flagrule*     lprule;
    unsigned char chrule = *pflags++;

  // get next form modification rule pointer; check if defined
  // report unsucceeded result
    if ( chrule == '/' )
      continue;
    if ( (lprule = GetRule( chrule )) == NULL )
      return 0;
    if ( !lprule->GenFlex( lpword, rftree ) )
      return 0;
  }
  return 1;
}

