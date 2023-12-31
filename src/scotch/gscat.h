/* Copyright 2009,2014,2023 IPB, Universite de Bordeaux, INRIA & CNRS
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
/**   NAME       : gscat.h                                 **/
/**                                                        **/
/**   AUTHOR     : Francois PELLEGRINI                     **/
/**                                                        **/
/**   FUNCTION   : This file contains the data declara-    **/
/**                tions for the sequential graph scatter- **/
/**                ing program.                            **/
/**                                                        **/
/**   DATES      : # Version 5.1  : from : 26 apr 2009     **/
/**                                 to   : 26 apr 2009     **/
/**                # Version 6.0  : from : 12 nov 2014     **/
/**                                 to   : 12 nov 2014     **/
/**                # Version 7.0  : from : 02 aug 2023     **/
/**                                 to   : 04 aug 2023     **/
/**                                                        **/
/************************************************************/

/*
**  The defines.
*/

/*+ File name aliases. +*/

#define C_FILENBR                   2             /* Number of files in list                */
#define C_FILEARGNBR                2             /* Number of files which can be arguments */

#define C_filenamesrcinp            fileBlockName (C_fileTab, 0) /* Centralized source graph input file name  */
#define C_filenamesrcout            fileBlockName (C_fileTab, 1) /* Distributed source graph output file name */

#define C_filepntrsrcinp            fileBlockFile (C_fileTab, 0) /* Centralized source graph input file  */
#define C_filepntrsrcout            fileBlockFile (C_fileTab, 1) /* Distributed source graph output file */

/*
**  The function prototypes.
*/

static int                  C_graphScat (FILE * const, const SCOTCH_Num, char * const, const SCOTCH_Num);
