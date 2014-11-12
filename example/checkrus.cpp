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
# include <stdio.h>
# include <math.h>

# define  min_stem_length 3

# include <string.h>
# include "../include/stemmers.h"
# include "../include/fuzzyrus.h"
# include "../include/fuzzyukr.h"

unsigned char*  fuzzyTab = fuzzyRus;

char  vowels[] = "àåèîóûýþÿ";

unsigned char toLoCaseMatrix1251[256] =
{
/* Characters in range 0 - 31       */
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
/* Space till plus, characters in range 32 - 63 */
  0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
  0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
  0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
/* Characters in range 64 - 127     */
  0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
  0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
  0x78, 0x79, 0x7A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
  0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
  0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
  0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
/* Characters in range 0x80 - 0x9F  */
  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
  0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
  0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
/* Characters in range 0xA0 - 0xA7  */
  0xA0, 0xA2, 0xA2, 0xA3, 0xA4, 0xB4, 0xA6, 0xA7,
  0xB8, 0xA9, 0xBA, 0xAB, 0xAC, 0xAD, 0xAE, 0xBF,
  0xB0, 0xB1, 0xB3, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
  0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
/* Characters in range 0xC0 - 0xDF, cyrillic capitals */
  0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
  0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
  0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
  0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
/* Regular characters in range 0xE0 - 0xFF  */
  0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
  0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
  0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
  0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
};

void  DrawStem( const char* lpsz )
{
  stemScan  stscan = { fuzzyTab, toLoCaseMatrix1251, vowels, (unsigned)-1 };
  unsigned  buffer[5];
  int       length = strlen( lpsz );
  int       lcount = GetStemLenBuffer( &stscan, buffer, 5, lpsz, length );
  char      result[256];
  char*     curpos = result;
  unsigned  cbcopy = 0;
  int       lindex;

  if ( length + lcount >= sizeof(result) )
  {
    printf( "%s\n", lpsz );
    return;
  }
  for ( lindex = 0; lindex < lcount; lindex++ )
  {
    memcpy( curpos, lpsz + cbcopy, buffer[lindex] - cbcopy );
    curpos = result + buffer[lindex] + lindex;
    *curpos++ = '|';
    cbcopy = buffer[lindex];
  }
  strcpy( curpos, lpsz + cbcopy );
  printf( "%s\n", result );
}

int   main( int argc, char* argv[] )
{
  bool  brus = ( argc > 1 && strcmp( argv[1], "rus" ) == 0 );
  bool  bukr = ( argc > 1 && strcmp( argv[1], "ukr" ) == 0 );

  if ( !brus && !bukr )
  {
    fprintf( stderr, "Usage: checkrus rus|ukr\n" );
    return -1;
  }
  if ( bukr )
    fuzzyTab = fuzzyUkr;

  char  buffer[256];

  for ( ; ; )
  {
    char* lpbuff;

    if ( fgets( buffer, sizeof(buffer), stdin ) == NULL || buffer[0] == '\0' )
      break;
    for ( lpbuff = buffer; lpbuff[0] != '\0' && lpbuff[0] != '\r'
      && lpbuff[0] != '\n'; lpbuff++ ) (void)NULL;
    lpbuff[0] = '\0';
    DrawStem( buffer );
  }
  return 0;
}
