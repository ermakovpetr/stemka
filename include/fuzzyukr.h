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
# if !defined( __fuzzyukr_h__ )
# define __fuzzyukr_h__

# if !defined( EXTERN_C_IF_NEEDED )
#   if defined( __cplusplus )
#     define  EXTERN_C_IF_NEEDED  extern "C"
#   else
#     define  EXTERN_C_IF_NEEDED
#   endif
# endif

# if !defined( STEMKA_API )
#   if defined( WIN16 )
#     define STEMKA_API __far __pascal
#   elif defined( _WIN32 )
#     define STEMKA_API __stdcall
#   else
#     define STEMKA_API
#   endif
# endif /* STEMKA_API definition */

# if !defined( MSC_VER ) || ( defined( MSC_VER ) && !defined( _DLL ) )
 EXTERN_C_IF_NEEDED  unsigned char   fuzzyUkr[];
# endif

EXTERN_C_IF_NEEDED  const unsigned char*  STEMKA_API  GetUkrTables();
EXTERN_C_IF_NEEDED  const char*           STEMKA_API  GetUkrVowels();

# endif
