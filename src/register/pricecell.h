/*
 * FILE:
 * pricecell.h
 *
 * FUNCTION:
 * The PriceCell object implements a cell handler that stores
 * a single double-precision value, and has the smarts to 
 * display it as a price/amount as well as accepting monetary 
 * or general numeric input.
 *
 * By default, the PriceCell is an input/output cell.
 *
 * On input, this cell accepts only numeric characters
 * and numeric punctuation.  The punctuation accepted is *not*
 * currently internationalized.  Read the source for details.
 *
 * On output, it will display a numeric value using its current
 * format string.  The default format string prints two decimal 
 * places.  The format string can be set with the 
 * xaccSetPriceCellFormat() method.
 *
 * hack alert -- implement internationalization.
 *
 * On output, it will display negative values in red text.
 * hack alert -- the actual color (red) should be user configurable.
 *
 * The stored amount is stored as a double-precision floating point
 * variable. This should be sufficient precision to store trillions of
 * dollars with penny accuracy.
 *
 * HISTORY:
 * Copyright (c) 1998 Linas Vepstas
 */
/********************************************************************\
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, write to the Free Software      *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.        *
\********************************************************************/

#ifndef __XACC_PRICE_CELL_C__
#define __XACC_PRICE_CELL_C__

#include "basiccell.h"

typedef struct _PriceCell {
   BasicCell cell;
   double amount;      /* the amount associated with this cell */
   short blank_zero;   /* controls printing of zero values */
   char *prt_format;   /* controls display of value; printf format */  
} PriceCell;

/* installs a callback to handle price recording */
PriceCell *  xaccMallocPriceCell (void);
void         xaccInitPriceCell (PriceCell *);
void         xaccDestroyPriceCell (PriceCell *);

/* updates amount, string format is three decimal places */
void         xaccSetPriceCellValue (PriceCell *, double amount);

/* The xaccSetPriceCellFormat() method is used to control how
 *    the cell contents are displayed.   It accepts as an argument
 *    a printf-style format.  The format must control the display
 *    of a double-precision float.  See the printf() command for 
 *    allowed syntax.  The default format is "%.2f".
 */
void         xaccSetPriceCellFormat (PriceCell *, char * fmt);

/* updates two cells; the deb cell if amt is negative,
 * the credit cell if amount is positive, and makes the other cell
 * blank. */
void         xaccSetDebCredCellValue (PriceCell *deb,
                                      PriceCell *cred,  double amount);

#endif /* __XACC_PRICE_CELL_C__ */

/* --------------- end of file ---------------------- */