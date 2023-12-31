/* Copyright 2004,2007,2011,2012,2016,2018,2023 IPB, Universite de Bordeaux, INRIA & CNRS
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
/**   NAME       : graph_check.c                           **/
/**                                                        **/
/**   AUTHOR     : Francois PELLEGRINI                     **/
/**                                                        **/
/**   FUNCTION   : This module contains the source graph   **/
/**                checking function.                      **/
/**                                                        **/
/**   DATES      : # Version 0.0  : from : 01 dec 1992     **/
/**                                 to   : 18 may 1993     **/
/**                # Version 1.3  : from : 30 apr 1994     **/
/**                                 to   : 18 may 1994     **/
/**                # Version 2.0  : from : 06 jun 1994     **/
/**                                 to   : 31 oct 1994     **/
/**                # Version 3.0  : from : 07 jul 1995     **/
/**                                 to   : 28 sep 1995     **/
/**                # Version 3.1  : from : 28 nov 1995     **/
/**                                 to   : 08 jun 1996     **/
/**                # Version 3.2  : from : 07 sep 1996     **/
/**                                 to   : 15 sep 1998     **/
/**                # Version 3.3  : from : 22 sep 1998     **/
/**                                 to   : 31 dec 1998     **/
/**                # Version 4.0  : from : 24 nov 2001     **/
/**                                 to   : 22 apr 2004     **/
/**                # Version 5.0  : from : 13 dec 2006     **/
/**                                 to   : 02 oct 2007     **/
/**                # Version 6.0  : from : 27 jun 2011     **/
/**                                 to   : 23 feb 2018     **/
/**                # Version 7.0  : from : 19 jan 2023     **/
/**                                 to   : 12 mar 2023     **/
/**                                                        **/
/************************************************************/

/*
**  The defines and includes.
*/

#include "module.h"
#include "common.h"
#include "graph.h"

/****************************************/
/*                                      */
/* These routines handle source graphs. */
/*                                      */
/****************************************/

/* This routine checks the consistency
** of the given graph.
** It returns:
** - 0   : if graph data are consistent.
** - !0  : on error.
*/

int
graphCheck (
const Graph * const         grafptr)
{
  Gnum                vertnum;                    /* Number of current vertex */
  Gnum                velosum;                    /* Sum of vertex loads      */
  Gnum                edlosum;                    /* Sum of edge loads        */
  Gnum                edgenbr;                    /* Number of edges (arcs)   */
  Gnum                edgenum;                    /* Number of current edge   */
  Gnum                degrmax;                    /* Maximum degree           */

  const Gnum                  baseval = grafptr->baseval; /* Fast accesses */
  const Gnum * restrict const verttax = grafptr->verttax;
  const Gnum * restrict const vendtax = grafptr->vendtax;
  const Gnum * restrict const velotax = grafptr->velotax;
  const Gnum * restrict const edgetax = grafptr->edgetax;
  const Gnum * restrict const edlotax = grafptr->edlotax;

  if ((grafptr->vertnbr < 0) ||
      (grafptr->vertnbr != (grafptr->vertnnd - baseval))) {
    errorPrint ("graphCheck: invalid vertex numbers");
    return (1);
  }
  if ((grafptr->edgenbr < 0) ||
      ((grafptr->edgenbr & 1) != 0)) {
    errorPrint ("graphCheck: invalid edge numbers");
    return (1);
  }

  degrmax =
  edgenbr = 0;
  velosum = (velotax == NULL) ? grafptr->vertnbr : 0;
  edlosum = (edlotax == NULL) ? grafptr->edgenbr : 0;
  for (vertnum = baseval; vertnum < grafptr->vertnnd; vertnum ++) {
    Gnum                degrval;

    if ((verttax[vertnum] < baseval) ||
        (vendtax[vertnum] < verttax[vertnum])) {
      errorPrint ("graphCheck: invalid vertex arrays");
      return (1);
    }

    degrval = vendtax[vertnum] - verttax[vertnum];
    if (degrval > degrmax)
      degrmax = degrval;
    edgenbr += degrval;

    for (edgenum = verttax[vertnum]; edgenum < vendtax[vertnum]; edgenum ++) {
      Gnum                vertend;                /* Number of end vertex      */
      Gnum                edgeend;                /* Number of end vertex edge */

      vertend = edgetax[edgenum];
      if (edlotax != NULL) {
        Gnum                edlotmp;

        edlotmp = edlosum + edlotax[edgenum];
        if (edlotmp < edlosum) {                  /* If overflow */
          errorPrint ("graphCheck: edge load sum overflow");
          return (1);
        }
        edlosum = edlotmp;
      }

      if ((vertend < baseval) || (vertend >= grafptr->vertnnd)) { /* If invalid edge end */
        errorPrint ("graphCheck: invalid edge array");
        return (1);
      }
      if (vertend == vertnum) {                   /* Loops not allowed */
        errorPrint ("graphCheck: loops not allowed");
        return (1);
      }
      for (edgeend = verttax[vertend];            /* Search for matching arc */
           (edgeend < vendtax[vertend]) && (edgetax[edgeend] != vertnum);
           edgeend ++) ;
      if ((edgeend >= vendtax[vertend]) ||
          ((edlotax != NULL) && (edlotax[edgenum] != edlotax[edgeend]))) {
        errorPrint ("graphCheck: arc data do not match");
        return (1);
      }
      for (edgeend ++;                            /* Search for duplicate arcs */
           (edgeend < vendtax[vertend]) && (edgetax[edgeend] != vertnum);
           edgeend ++) ;
      if (edgeend < vendtax[vertend]) {
        errorPrint ("graphCheck: duplicate arc");
        return (1);
      }
    }
    if (velotax != NULL) {
      Gnum                velotmp;

      if (velotax[vertnum] < 0) {                 /* If non positive loads */
        errorPrint ("graphCheck: invalid vertex load array");
        return (1);
      }
      velotmp = velosum + velotax[vertnum];
      if (velotmp < velosum) {                    /* If overflow */
        errorPrint ("graphCheck: vertex load sum overflow");
        return (1);
      }
      velosum = velotmp;
    }
  }
  if (grafptr->edgenbr != edgenbr) {
    errorPrint ("graphCheck: invalid number of edges");
    return (1);
  }
  if (grafptr->velosum != velosum) {
    errorPrint ("graphCheck: invalid vertex load sum");
    return (1);
  }
  if (grafptr->edlosum != edlosum) {
    errorPrint ("graphCheck: invalid edge load sum");
    return (1);
  }
  if (grafptr->degrmax < degrmax) {
    errorPrint ("graphCheck: invalid maximum degree");
    return (1);
  }

  return (0);
}
