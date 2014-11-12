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
# if !defined( __stemmers_h__ )
# define  __stemmers_h__

typedef struct
{
  const unsigned char*  lpdict;
  const unsigned char*  ptable;
  const char*           vowels;
  unsigned              minlen;
} stemScan;

# if !defined( STEMKA_API )
#   if defined( WIN16 )
#     define STEMKA_API __far __pascal
#   elif defined( _WIN32 )
#     define STEMKA_API __stdcall
#   else
#     define STEMKA_API
#   endif
# endif /* STEMKA_API definition */

# if defined( __cplusplus )
extern "C"
{
# endif  // __cplusplus

int   STEMKA_API  GetStemLenString( stemScan*   lpscan,
                                    unsigned*   lplist,
                                    unsigned    mcount,
                                    const char* lpword );

int   STEMKA_API  GetStemLenBuffer( stemScan*   lpscan,
                                    unsigned*   lplist,
                                    unsigned    mcount,
                                    const char* lpword,
                                    unsigned    length );

int   STEMKA_API  GetPubStemLenStr( int*                  outbuf,
                                    int                   nccout,
                                    const unsigned char*  lpdict,
                                    const char*           vowels,
                                    const char*           lpword );

int   STEMKA_API  GetPubStemLenBuf( int*                  outbuf,
                                    int                   nccout,
                                    const unsigned char*  lpdict,
                                    const char*           vowels,
                                    const char*           lpword,
                                    unsigned              ccword );

# if defined( __cplusplus )
}
# endif  // __cplusplus

# endif  // __stemmers_h__
