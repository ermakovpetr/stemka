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
# if !defined( __regexapi_h__ )
# define  __regexapi_h__

# include <string.h>
# include <stdlib.h>
# include <stdio.h>

extern "C"
{
# include <sys/types.h>
# include <regex.h>
}

class CRegExp
{
public:
              CRegExp(const char* pcszRegExp = NULL)
                {
                  if (pcszRegExp!=NULL)
                  {            
                      r = (regex_t *) malloc(sizeof(regex_t));
                      nloop = 1;
                      memset(r,0,sizeof(regex_t));
                      if ((error = regcomp( r, pcszRegExp, REG_EXTENDED)))
                      {
                          regerror( error, r, errbuff, sizeof(errbuff));
                          fprintf(stderr, "regcomp: %s\n",errbuff);
                          throw;
                      }
                      n = r->re_nsub + 1;
                      m = (regmatch_t *) malloc(sizeof(regmatch_t) * n);
                  }
                }
             ~CRegExp()
                {
                  if ( m != NULL )
                    free(m);
                  if ( r != NULL )
                  {
                    regfree(r);
                    free(r);
                  }
                }
    CRegExp&  operator = ( CRegExp& regexp )
                {
                  r = regexp.r; 
                  m = regexp.m;    
                  nloop = regexp.nloop;
                  error = regexp.error;
                  n = regexp.n;
                  regexp.r = NULL;
                  regexp.m = NULL;
                  return *this;
                }
    bool      IsAccept(const char* pcszData)
                {
                  for (int k = 0; k < nloop; ++k)
                    error = regexec(r, pcszData, n, m, 0);
                  return error == 0;
                }
protected:
    regex_t     *r; 
    regmatch_t  *m;    
    int         nloop, error, n;
    char        errbuff[128];    
};

# endif  // __regexapi_h__
