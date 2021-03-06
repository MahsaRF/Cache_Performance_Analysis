/*
 *  (C) Copyright by Ariel Faigon, 1987
 *  Released under the GNU GPL (General Public License) version 2
 *  or any later version (http://www.gnu.org/licenses/licenses.html)
 */
/*---------------            sort.h              --------------*/
/*--------------- sort library customizable file --------------*/

/*
 * This is the key TYPE.
 * Replace this typedef by YOUR key type.
 * e.g. if you're sorting an array of pointers to strings
 * You should do:
 *
 *	typedef char * KEY_T
 *
 * The keys are the items in the array that you're moving
 * around using the SWAP macro.
 * Note: the comparison function may compare any "function"
 * of this key, it doesn't necessarily need to compare the
 * key itself. example: you compare the strings pointed to
 * by the key itself.
 */ 
#include "edge.h"

typedef edge	KEY_T;

/*
 * These are the COMPARISON macros
 * Replace these macros by YOUR comparison operations.
 * e.g. if you are sorting an array of pointers to strings
 * you should define:
 *
 *	GT(x, y)  as   (strcmp((x),(y)) > 0) 	Greater than
 *	LT(x, y)  as   (strcmp((x),(y)) < 0) 	Less than
 *	GE(x, y)  as   (strcmp((x),(y)) >= 0) 	Greater or equal
 *	LE(x, y)  as   (strcmp((x),(y)) <= 0) 	Less or equal
 *	EQ(x, y)  as   (strcmp((x),(y)) == 0) 	Equal
 *	NE(x, y)  as   (strcmp((x),(y)) != 0) 	Not Equal
 */
#define GT(x, y) ((x.w) > (y.w))
#define LT(x, y) ((x.w) < (y.w))
#define GE(x, y) ((x.w) >= (y.w))
#define LE(x, y) ((x.w) <= (y.w))
#define EQ(x, y) ((x.w) == (y.w))
#define NE(x, y) ((x.w) != (y.w))

/*
 * This is the SWAP macro to swap between two keys.
 * Replace these macros by YOUR swap macro.
 * e.g. if you are sorting an array of pointers to strings
 * You can define it as:
 *
 *	#define SWAP(x, y) temp = (x); (x) = (y); (y) = temp
 *
 * Bug: 'insort()' doesn't use the SWAP macro.
 */
#define SWAP(x, y) temp = (x); (x) = (y); (y) = temp

/*-------------------- End of customizable part -----------------------*/
void  heapsort  (KEY_T *array, int len);
void  shellsort (KEY_T *array, int len);
void  sedgesort (KEY_T *array, int len);
void  insort (KEY_T *array, int len);
void  gamasort(KEY_T *array, int lo, int up);
void  quicksort ( KEY_T *array, int lower, int upper);
void  quickersort ( KEY_T *array, int lower, int upper);



/*-------------------- DON'T TOUCH BEYOND THIS POINT ------------------
extern void    insort ();
extern void    quicksort ();
extern void    quickersort ();
extern void    partial_quickersort ();
extern void    sedgesort ();
extern void    shellsort ();
extern void    heapsort ();
extern void    gamasort ();
extern void    siftdown ();
extern int     sorted ();
extern int     array_eq ();
*/

