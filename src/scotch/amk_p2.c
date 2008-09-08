/* Copyright 2004,2007,2008 ENSEIRB, INRIA & CNRS
**
** This file is part of the Scotch software package for static mapping,
** graph partitioning and sparse matrix ordering.
**
** This software is governed by the CeCILL-C license under French law
** and abiding by the rules of distribution of free software. You can
** use, modify and/or redistribute the software under the terms of the
** CeCILL-C license as circulated by CEA, CNRS and INRIA at the following
** URL: "http://www.cecill.info".
** 
** As a counterpart to the access to the source code and rights to copy,
** modify and redistribute granted by the license, users are provided
** only with a limited warranty and the software's author, the holder of
** the economic rights, and the successive licensors have only limited
** liability.
** 
** In this respect, the user's attention is drawn to the risks associated
** with loading, using, modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean that it is complicated to manipulate, and that also
** therefore means that it is reserved for developers and experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards
** their requirements in conditions enabling the security of their
** systems and/or data to be ensured and, more generally, to use and
** operate it in the same conditions as regards security.
** 
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
*/
/************************************************************/
/**                                                        **/
/**   NAME       : amk_p2.c                                **/
/**                                                        **/
/**   AUTHOR     : Francois PELLEGRINI                     **/
/**                                                        **/
/**   FUNCTION   : Creates the target architecture file    **/
/**                for a weighted path with two vertices   **/
/**                used to bipartition graphs in parts of  **/
/**                different sizes.                        **/
/**                                                        **/
/**   DATES      : # Version 3.0  : from : 17 jul 1995     **/
/**                                 to   : 17 jul 1995     **/
/**                # Version 3.2  : from : 02 jun 1997     **/
/**                                 to   : 02 jun 1997     **/
/**                # Version 3.4  : from : 03 feb 2000     **/
/**                                 to   : 03 feb 2000     **/
/**                # Version 5.1  : from : 16 dec 2007     **/
/**                                 to   : 16 mar 2008     **/
/**                                                        **/
/************************************************************/

/*
**  The defines and includes.
*/

#define AMK_P2

#include "module.h"
#include "common.h"
#include "scotch.h"
#include "amk_p2.h"

/*
**  The static variables.
*/

static int                  C_paraNum = 0;        /* Number of parameters       */
static int                  C_fileNum = 0;        /* Number of file in arg list */
static File                 C_fileTab[C_FILENBR] = { /* File array              */
                              { "-", NULL, "w" } };

static const char *         C_usageList[] = {
  "amk_p2 <wght0> [<wght1> [<output target file>]] <options>",
  "  -h  : Display this help",
  "  -V  : Print program version and copyright",
  NULL };

/************************************/
/*                                  */
/* The main routine, which computes */
/* the decomposition.               */
/*                                  */
/************************************/

int
main (
int                         argc,
char *                      argv[])
{
  int                 wght[2] = {1, 1};           /* Vertex weights */
  int                 i;

  errorProg ("amk_p2");

  if ((argc >= 2) && (argv[1][0] == '?')) {       /* If need for help */
    usagePrint (stdout, C_usageList);
    return     (0);
  }

  for (i = 0; i < C_FILENBR; i ++)                /* Set default stream pointers */
    C_fileTab[i].pntr = (C_fileTab[i].mode[0] == 'r') ? stdin : stdout;
  for (i = 1; i < argc; i ++) {                   /* Loop for all option codes                        */
    if ((argv[i][0] != '-') || (argv[i][1] == '\0') || (argv[i][1] == '.')) { /* If found a file name */
      if (C_paraNum < 2) {                        /* If number of parameters not reached              */
        if ((wght[C_paraNum ++] = atoi (argv[i])) < 1) { /* Get vertex weights                        */
          errorPrint ("main: invalid weight (\"%s\")", argv[i]);
          return     (1);
        }
        continue;                                 /* Process remaining parameters */
      }
      if (C_fileNum < C_FILEARGNBR)               /* File name has been given */
        C_fileTab[C_fileNum ++].name = argv[i];
      else {
        errorPrint ("main: too many file names given");
        return     (1);
      }
    }
    else {                                       /* If found an option name */
      switch (argv[i][1]) {
        case 'H' :                               /* Give the usage message */
        case 'h' :
          usagePrint (stdout, C_usageList);
          return     (0);
        case 'V' :
          fprintf (stderr, "amk_p2, version %s - F. Pellegrini\n", SCOTCH_VERSION);
          fprintf (stderr, "Copyright 2004,2007,2008 ENSEIRB, INRIA & CNRS, France\n");
          fprintf (stderr, "This software is libre/free software under CeCILL-C -- see the user's manual for more information\n");
          return  (0);
        default :
          errorPrint ("main: unprocessed option (\"%s\")", argv[i]);
          return     (1);
      }
    }
  }

  fileBlockOpen (C_fileTab, C_FILENBR);           /* Open all files */

  fprintf (C_filepntrtgtout, "cmpltw\t2\t%ld\t%ld\n", (long) wght[0], (long) wght[1]); /* Print target description */

  fileBlockClose (C_fileTab, C_FILENBR);          /* Always close explicitely to end eventual (un)compression tasks */

#ifdef COMMON_PTHREAD
  pthread_exit ((void *) 0);                      /* Allow potential (un)compression tasks to complete */
#endif /* COMMON_PTHREAD */
  return (0);
}
