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
/**   NAME       : arch_tleaf.h                            **/
/**                                                        **/
/**   AUTHOR     : Francois PELLEGRINI                     **/
/**                                                        **/
/**   FUNCTION   : These lines are the data declaration    **/
/**                for the tree-leaf pseudo-graph target   **/
/**                architecture functions.                 **/
/**                                                        **/
/**   DATES      : # Version 0.0  : from : 01 dec 1992     **/
/**                                 to   : 24 mar 1993     **/
/**                # Version 1.2  : from : 04 feb 1994     **/
/**                                 to   : 11 feb 1994     **/
/**                # Version 1.3  : from : 20 apr 1994     **/
/**                                 to   : 20 apr 1994     **/
/**                # Version 2.0  : from : 06 jun 1994     **/
/**                                 to   : 12 nov 1994     **/
/**                # Version 2.1  : from : 07 apr 1995     **/
/**                                 to   : 30 jun 1995     **/
/**                # Version 3.0  : from : 01 jul 1995     **/
/**                                 to     16 aug 1995     **/
/**                # Version 3.1  : from : 20 jul 1996     **/
/**                                 to     23 jul 1996     **/
/**                # Version 3.2  : from : 10 oct 1996     **/
/**                                 to     14 may 1998     **/
/**                # Version 3.3  : from : 01 oct 1998     **/
/**                                 to     01 oct 1998     **/
/**                # Version 4.0  : from : 10 dec 2003     **/
/**                                 to     10 dec 2003     **/
/**                # Version 5.1  : from : 21 jan 2008     **/
/**                                 to     21 jan 2008     **/
/**                                                        **/
/************************************************************/

/*
**  The type and structure definitions.
*/

/** The Tree-Leaf graph definitions. **/

typedef struct ArchTleaf_ {
  Anum                      leafdep;              /*+ Maximum leaf depth                      +*/
  Anum                      clusdep;              /*+ Depth before reaching complete clusters +*/
  Anum                      linkval;              /*+ Value of extra-cluster links            +*/
} ArchTleaf;

typedef struct ArchTleafDom_ {
  Anum                      leaflvl;              /*+ Current leaf depth +*/
  Anum                      leafnum;              /*+ Leaf number        +*/
} ArchTleafDom;

/*
**  The function prototypes.
*/

#ifndef ARCH_TLEAF
#define static
#endif

int                         archTleafArchLoad   (ArchTleaf * restrict const, FILE * restrict const);
int                         archTleafArchSave   (const ArchTleaf * const, FILE * restrict const);
#define archTleafArchFree           NULL
ArchDomNum                  archTleafDomNum     (const ArchTleaf * const, const ArchTleafDom * const);
int                         archTleafDomTerm    (const ArchTleaf * const, ArchTleafDom * restrict const, const ArchDomNum);
Anum                        archTleafDomSize    (const ArchTleaf * const, const ArchTleafDom * const);
#define archTleafDomWght            archTleafDomSize
Anum                        archTleafDomDist    (const ArchTleaf * const, const ArchTleafDom * const, const ArchTleafDom * const);
int                         archTleafDomFrst    (const ArchTleaf * const, ArchTleafDom * restrict const);
int                         archTleafDomLoad    (const ArchTleaf * const, ArchTleafDom * restrict const, FILE * restrict const);
int                         archTleafDomSave    (const ArchTleaf * const, const ArchTleafDom * const, FILE * restrict const);
int                         archTleafDomBipart  (const ArchTleaf * const, const ArchTleafDom * const, ArchTleafDom * restrict const, ArchTleafDom * restrict const);
#ifdef SCOTCH_PTSCOTCH
int                         archTleafDomMpiType (const ArchTleaf * const, MPI_Datatype * const);
#endif /* SCOTCH_PTSCOTCH */

#undef static
