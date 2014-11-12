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
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include "flexrule.h"

# if defined( _MSC_VER )
#   define  strcasecmp  strcmpi
#   define  strncasecmp strnicmp
# endif  // _MSC_VER

unsigned char tolocase[256] =
{
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
  0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
  0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
  0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
  0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
  0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
  0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
  0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
  0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
  0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
  0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
  0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
  0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
  0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
  0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
  0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
  0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
  0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
  0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
  0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
  0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
  0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
  0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
  0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
  0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};

void  Charset( char*  buffer )
{
  char* bufptr = buffer;

// Set bufptr to the upper case characters
  while ( bufptr[0] != '\0' && !isspace( (unsigned char)bufptr[0] ) )
    ++bufptr;
  if ( bufptr[0] == '\0' )
    return;
  *bufptr++ = '\0';
  while ( bufptr[0] != '\0' && isspace( (unsigned char)bufptr[0] ) )
    ++bufptr;

// Check if list is defined, else character
  if ( buffer[0] != '[' )
  {
    tolocase[(unsigned char)bufptr[0]] = (unsigned char)buffer[0];
    return;
  }
  ++buffer;
  ++bufptr;

  while ( buffer[0] != ']' && buffer[0] != '\0' && !isspace(
    (unsigned char)buffer[0] ) )
  {
    if ( buffer[0] == '-' )
    {
      unsigned  nindex;
      int       chdiff = (unsigned char)buffer[1] - (unsigned char)bufptr[1];

      for ( nindex = (unsigned char)bufptr[-1]; nindex <= (unsigned char)bufptr[1];
        nindex++ )  tolocase[nindex] = nindex + chdiff;
      buffer += 2;
      bufptr += 2;
    }
      else
    tolocase[(unsigned char)*bufptr++] = (unsigned char)*buffer++;
  }
}

bool  Compile( flagrule& rfrule, const char* string )
{
  flexrule* lprule = rfrule.NewRule();
# if !defined( _DEBUG )
  char      sregex[32];
  char      cutstr[32];
# endif  // !_DEBUG
  char*     bufptr;
  char*     strorg = (char*)string;

// Create a new flexion rule in flag definition
  if ( lprule == NULL )
  {
    fprintf( stderr, "Could not create the rule!\n" );
    return false;
  }
  lprule->prefix = rfrule.prefix;

// Add regular mask
# if defined( _DEBUG )
  bufptr = lprule->sregex;
# else
  bufptr = sregex;
# endif  // _DEBUG

  while ( string[0] != '\0' && string[0] != '>' )
  {
  // Copy one character
    if ( string[0] == '[' )
    {
      while ( string[0] != '\0' && string[0] != ']' )
        *bufptr++ = (char)tolocase[(unsigned char)*string++];
      if ( string[0] == ']' ) *bufptr++ = *string++;
        else
      {
        fprintf( stderr, "Invalid regular expression (%s)!\n", strorg );
        return false;
      }
    }
      else
    *bufptr++ = (char)tolocase[(unsigned char)*string++];
  // Increment length and skip trailing whitespace characters
    while ( string[0] != '\0' && isspace( (unsigned char)string[0] ) )
      ++string;
    ++lprule->reglen;
  }

// Check if a condition is already completed
  if ( string[0] == '>' )
  {
    bufptr[0] = '\0';
    do ++string;
      while ( string[0] != '\0' && isspace( (unsigned char)string[0] ) );
  }
    else
  {
    fprintf( stderr, "Invalid rule expression (%s)!\n", strorg );
    return false;
  }

# if defined( _DEBUG )
  CRegExp  regexp( lprule->sregex );

  lprule->regexp = regexp;
# else
  CRegExp  regexp( sregex );

  lprule->regexp = regexp;
# endif  // _DEBUG

// The synthes instruction may start with '-'; this signals to delete
// some characters at end of a string; set the cut instruction
  if ( string[0] == '-' )
  {
# if defined( _DEBUG )
    bufptr = lprule->cutstr;
# else
    bufptr = cutstr;
# endif  // _DEBUG
    ++string;
    while ( string[0] != '\0' && string[0] != ',' && !isspace(
      (unsigned char)string[0] ) )
    {
      *bufptr++ = (char)tolocase[(unsigned char)*string++];
      ++lprule->cutlen;
    }
    bufptr[0] = '\0';
    while ( string[0] != '\0' && ( string[0] == ',' || isspace(
      (unsigned char)string[0] ) ) )
        ++string;
  }
    else
  {
# if defined( _DEBUG )
    lprule->cutstr[0] = '\0';
# else
    cutstr[0] = '\0';
# endif  // _DEBUG
    lprule->cutlen = 0;
  }

// The least part of a string should be the affix
  bufptr = lprule->append;
  while ( string[0] != '\0' && !isspace( (unsigned char)string[0] ) )
    *bufptr++ = (char)tolocase[(unsigned char)*string++];
  bufptr[0] = '\0';
  return true;
}

bool  Compile( rulesbox& refbox, FILE* infile )
{
  char      buffer[256];
  bool      prefix = false;
  bool      suffix = false;
  flagrule* lprule = NULL;

  while ( !feof( infile ) && fgets( buffer, sizeof(buffer), infile ) != NULL )
  {
    char* bufptr = buffer;
    char* endptr;
    bool  isflag;

  // Truncate read line
    while ( bufptr[0] != '\n' && bufptr[0] != '\0' && isspace(
      (unsigned char)bufptr[0] ) )
        ++bufptr;
    for ( endptr = bufptr; endptr[0] != '\0' && endptr[0] != '\n'
      && endptr[0] != '#'; endptr++ ) (void)NULL;
    endptr[0] = '\0';

  // Check if is not empty
    if ( bufptr[0] == '\0' )
      continue;

  // Check if line presents codepage characters definition
    if ( strncasecmp( bufptr, "wordchars", 9 ) == 0 && isspace(
      (unsigned char)bufptr[9] ) )
    {
      bufptr += 9;
      while ( bufptr[0] != '\0' && isspace( (unsigned char)bufptr[0] ) )
        ++bufptr;
    // Now bufptr points to the characters declaration
      Charset( bufptr );
      continue;
    }

  // Check if suffix or prefix starts
    if ( !prefix && strncasecmp( bufptr, "prefixes", 8 ) == 0 && (
      isspace( (unsigned char)bufptr[8] ) || bufptr[8] == '\0' ) )
    {
      suffix = false;
      prefix = true;
      continue;
    }
    if ( !suffix && strcasecmp( buffer, "suffixes" ) == 0 )
    {
      prefix = false;
      suffix = true;
      continue;
    }
    if ( !( prefix || suffix ) )
      continue;

  // Check if the line defines a flag
    isflag = strncasecmp( bufptr, "flag", 4 ) == 0 && isspace(
      (unsigned char)bufptr[4] );

  // The flag record begins. The existing flag is finished, the new flag
  // would be created
    if ( isflag )
    {
      for ( bufptr += 5; bufptr[0] != '\0' && ( isspace( (unsigned char)
        bufptr[0] ) || bufptr[0] == '*' ); bufptr++ )
          (void)NULL;
      if ( bufptr[0] != '\0' && bufptr[1] == ':' )
      {
        lprule = refbox.NewRule( bufptr[0] );
      }
        else
      {
        fprintf( stderr, "Invalid rule definition \'%s\'!\n", buffer );
        lprule = NULL;
      }
      lprule->prefix = prefix;
      continue;
    }

  // Check if the rule is defined
    if ( lprule == NULL )
      continue;

  // The line contains a new flex rule
    if ( !Compile( *lprule, bufptr ) )
      return false;
  }
  return true;
}

bool  Process( rulesbox& refbox,
               flexTree& rftree,
               FILE*     infile )
{
  char      buffer[256];
  unsigned  cflect = 0;

  while ( !feof( infile ) && fgets( buffer, sizeof(buffer), infile ) != NULL )
  {
    char*   bufptr = buffer;
    char*   pflags;

  // Check if is not empty
    if ( bufptr[0] == '\0' )
      continue;
  // Break word to flective and flags part
  // Convert the word to lower case characters
    while ( bufptr[0] != '\0' && bufptr[0] != '\r' && bufptr[0] != '\n'
      && bufptr[0] != '/' ) *bufptr++ = (char)tolocase[(unsigned char)*bufptr];
    *bufptr++ = '\0';
    pflags = bufptr;
    while ( bufptr[0] != '\0' && bufptr[0] != '\r' && bufptr[0] != '\n' )
      ++bufptr;
    bufptr[0] = '\0';
  // Check if the read word is flective
    if ( pflags[0] == '\0' )
      continue;
  // Increment the number of flective words found
    ++cflect;
  // Generate all the word forms from string
    refbox.GenFlex( buffer, pflags, rftree );
  }
  fprintf( stderr, "%d flective words processed.\n", cflect );
  return true;
}

bool  LoadAffixes( rulesbox& refbox, const char* lpname )
{
  FILE*     infile;
  bool      loaded;

  if ( (infile = fopen( lpname, "rt" )) == NULL )
  {
    fprintf( stderr, "Could not find affixes dictionary \'%s\'!\n", lpname );
    return false;
  }
  loaded = Compile( refbox, infile );
  fclose( infile );
  return loaded;
}

bool  ProcessDict( rulesbox&   refbox,
                   const char* lpname,
                   flexTree&   rftree )
{
  FILE*     infile;
  bool      loaded;

  if ( (infile = fopen( lpname, "rt" )) == NULL )
  {
    fprintf( stderr, "Could not find words dictionary \'%s\'!\n", lpname );
    return false;
  }
  loaded = Process( refbox, rftree, infile );
  fclose( infile );
  return loaded;
}

void  FlushBuffer( FILE*    output,
                   char*    buffer,
                   unsigned length )
{
// Create the flexion table array
  fprintf( output, "{\n" );

  while ( length > 0 )
  {
    unsigned  curlen = ( length < 12 ? length : 12 );

    fprintf( output, "  " );

    while ( curlen > 0 )
    {
      fprintf( output, "0x%02x", (unsigned char)*buffer++ );
      if ( --length > 0 ) fprintf( output, "," );
      if ( --curlen > 0 ) fprintf( output, " " );
    }
    fprintf( output, "\n" );
  }
  fprintf( output, "};\n" );
}

bool  FlushBuffer( const char* output,
                   char*       buffer,
                   unsigned    length )
{
  FILE*   lpfile;

  if ( (lpfile = fopen( output, "wt" )) == NULL )
  {
    fprintf( stderr, "Could not create file %s!\n", output );
    return false;
  }
  FlushBuffer( lpfile, buffer, length );
  fclose( lpfile );
  return true;
}

bool  FlushFxTree( const char* output,
                   flexTree&   rftree )
{
  unsigned  length = rftree.Relocate();
  char*     buffer = (char*)malloc( length );
  bool      bfsave;

  rftree.Create( buffer );

  bfsave = FlushBuffer( output, buffer, length );

  free( buffer );
  return bfsave;
}

char  about[] = "isp2stem - the probability stemmer dictionary creation utility\n"
                "usage: isp2stem affixes wordlist dictfile xlatfile\n"
                "where:\tisp2stem - this program :-);\n"
                      "\taffixes  - ispell-format affixes dictionary name;\n"
                      "\twordlist - ispell-format word list name;\n"
                      "\tdictfile - the generated include file name;\n"
                      "\txlatfile - the generated to-lo-case include file name.\n";

int   main( int argc, char* argv[] )
{
  rulesbox  nrules;
  flexTree  intree;

  if ( argc < 5 )
  {
    fprintf( stderr, about );
    return -1;
  }
  if ( !LoadAffixes( nrules, argv[1] ) )
    return -1;
  if ( !ProcessDict( nrules, argv[2], intree ) )
    return -1;
  if ( !FlushFxTree( argv[3], intree ) )
    return -1;
  if ( !FlushBuffer( argv[4], (char*)tolocase, 256 ) )
    return -1;
  return 0;
}
