#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disjoint-set.h"
#include "timer.h"
#include "sort.h"
#include "papi.h"
#define NUM_EVENTS_1 2
#define NUM_EVENTS_2 4
#define NUM_EVENTS_3 2
#define THRESHOLD  1000000000
//-------------------------------------

static int keycompare ( const void *x, const void *y);
static void  reset_data ( edge *A, int size );

static int total_1 = 0; /* total overflows */
static int total_2 = 0; /* total overflows */
static int total_3 = 0; /* total overflows */
static int total_4 = 0; /* total overflows */
static int total_5 = 0; /* total overflows */
static int total_6 = 0; /* total overflows */
static int total_7 = 0; /* total overflows */

//overflow handler functions
void handler_1(int EventSet, void *address, long_long overflow_vector, void *context)
{
//fprintf(stderr, "handler(%d) Overflow at %p! vector=0x%llx\n", EventSet, address, overflow_vector);
	total_1++;
	
}
void handler_2(int EventSet, void *address, long_long overflow_vector, void *context)
{
//fprintf(stderr, "handler(%d) Overflow at %p! vector=0x%llx\n", EventSet, address, overflow_vector);
	total_2++;
	
}
void handler_3(int EventSet, void *address, long_long overflow_vector, void *context)
{
//fprintf(stderr, "handler(%d) Overflow at %p! vector=0x%llx\n", EventSet, address, overflow_vector);
	total_3++;
	
}
void handler_4(int EventSet, void *address, long_long overflow_vector, void *context)
{
//fprintf(stderr, "handler(%d) Overflow at %p! vector=0x%llx\n", EventSet, address, overflow_vector);
	total_4++;
	
}
void handler_5(int EventSet, void *address, long_long overflow_vector, void *context)
{
//fprintf(stderr, "handler(%d) Overflow at %p! vector=0x%llx\n", EventSet, address, overflow_vector);
	total_5++;
	
}
void handler_6(int EventSet, void *address, long_long overflow_vector, void *context)
{
//fprintf(stderr, "handler(%d) Overflow at %p! vector=0x%llx\n", EventSet, address, overflow_vector);
	total_6++;
	
}
void handler_7(int EventSet, void *address, long_long overflow_vector, void *context)
{
//fprintf(stderr, "handler(%d) Overflow at %p! vector=0x%llx\n", EventSet, address, overflow_vector);
	total_7++;
	
}

int main ( int argc, char ** argv )
{
  edge *A;
  int N;
  int i;
  TimeType t1, t2;
  double timings[5];
  char names[5][12]={"QSORT","HEAPSORT","SHELLSORT","INSORT","QUICKSORT"};
  //------------------------------------------------------------
  
  long long start_time, end_time;
  long long values1[NUM_EVENTS_1];
  long long values2[NUM_EVENTS_2];
  long long values3[NUM_EVENTS_3];
  int Eventset1 = PAPI_NULL;
  int Eventset2 = PAPI_NULL;
  int Eventset3 = PAPI_NULL;
  int retval=0;
  retval = PAPI_library_init(PAPI_VER_CURRENT);
  
  retval = PAPI_create_eventset(&Eventset1);
  if(retval != 0)
     printf("Error in eventset1 %d\n", retval);
  
  retval = PAPI_create_eventset(&Eventset2);
  if(retval != 0)
     printf("Error in Eventset2 %d\n", retval);
  
  retval = PAPI_create_eventset(&Eventset3);
  if(retval != 0)
     printf("Error in eventset3 %d\n", retval);
  
  
  
  if(PAPI_query_event (PAPI_L3_TCM) != PAPI_OK)
     printf("wtf\n");
  
  
  //-------------------------------------  L1 -----------
  retval = PAPI_add_event(Eventset1, PAPI_LD_INS);
  if (retval != 0)
     printf("Error occured in PAPI_add_events, PAPI_LD_INS %d\n", retval);
  
  retval = PAPI_add_event(Eventset1, PAPI_SR_INS);
  if (retval != 0)
     printf("Error occured in PAPI_add_events, PAPI_SR_INS %d\n", retval);
  
  retval = PAPI_add_event(Eventset2, PAPI_L1_TCM);
  if (retval != 0)
     printf("Error occured in PAPI_add_events, PAPI_L1_TCM %d\n", retval);
  
  //-------------------------------------  L2 -----------
  retval = PAPI_add_event(Eventset2, PAPI_L2_TCM);
  if (retval != 0)
     printf("Error occured in PAPI_add_events, PAPI_L2_TCM %d\n", retval);
  retval = PAPI_add_event(Eventset2, PAPI_L2_TCA);
  if (retval != 0)
     printf("Error occured in PAPI_add_events, PAPI_L2_TCA %d\n", retval);
 //-------------------------------------  L3 -----------
  retval = PAPI_add_event(Eventset3, PAPI_L3_TCM);
  if (retval != 0)
     printf("Error occured in PAPI_add_events, PAPI_L3_TCM %d\n", retval);
  retval = PAPI_add_event(Eventset2, PAPI_L3_TCA);
  if (retval != 0)
     printf("Error occured in PAPI_add_events, PAPI_L3_TCA %d\n", retval);
 
  
  //----------------PAPI_overflow(EventSet, EventCode, threshold, flags, handler)  ---------
  retval = PAPI_overflow(Eventset1, PAPI_LD_INS, THRESHOLD, 0, handler_1);
  if (retval <0){
	  printf(" return value of PAPI_overflow  for PAPI_LD_INS is %d\n", retval); 
	  //exit(0);
  }
 
  retval = PAPI_overflow(Eventset1, PAPI_SR_INS, THRESHOLD, 0, handler_2);
  if (retval <0){
	  printf(" return value of PAPI_overflow  for PAPI_SR_INS is %d\n", retval);
	  
  }
  /*retval = PAPI_overflow(Eventset2, PAPI_L1_TCM, THRESHOLD, 0, handler_3);
  if (retval <0){
	  printf(" return value of PAPI_overflow  for PAPI_L1_TCM is %d\n", retval);
  
  }*/
  retval = PAPI_overflow(Eventset2, PAPI_L2_TCM, THRESHOLD, 0, handler_4);
  if (retval <0){
	  printf(" return value of PAPI_overflow  for PAPI_L2_TCM is %d\n", retval);
  
  }
  /*retval = PAPI_overflow(Eventset2, PAPI_L2_TCA, THRESHOLD, 0, handler_5);
  if (retval <0){
	  printf(" return value of PAPI_overflow  for PAPI_L2_TCA is %d\n", retval);
	
  }*/
  retval = PAPI_overflow(Eventset3, PAPI_L3_TCM, THRESHOLD, 0, handler_6);
  if (retval <0){
	  printf(" return value of PAPI_overflow  for PAPI_L3_TCM is %d\n", retval);
	
  }
  retval = PAPI_overflow(Eventset2, PAPI_L3_TCA, THRESHOLD, 0, handler_7);
  if (retval <0){
	  printf(" return value of PAPI_overflow  for PAPI_L3_TCA is %d\n", retval);
	  
  }
  
  //----------------------------------------------------------------------
  
  if ( argc < 2 ) {
    printf("usage: ./sort-test <no elements>\n");
    exit (0);
  }
  
  N = atoi(argv[1]);


  A = (edge *) malloc ( N * sizeof(edge));
  if ( NULL == A ) {
      printf("could not allocate memory\n");
      exit (0);
  }
  
  
  printf("Qsort  %d  \n", N);
  //-------------------------   first run for extracting the total cache accesses for L1 in one Eventset and also the execution time!
  t1 = Wtime();
  reset_data( A, N);
  PAPI_start(Eventset1);
  start_time = PAPI_get_real_usec();
  //-----------------------------------------
  qsort ( A, N, sizeof(edge), keycompare);
  //-----------------------------------------
  end_time = PAPI_get_real_usec();
  PAPI_read(Eventset1, values1);
  PAPI_stop(Eventset1, values1);
  t2 = Wtime();
  timings[0] = t2-t1;
  
  //-------------------------   second run for extracting the total cache misses of L1 and L2 / total accesses for L2 and L3!
  reset_data( A, N);
  PAPI_start(Eventset2);
  //-----------------------------------------
  qsort ( A, N, sizeof(edge), keycompare);
  //-----------------------------------------
  PAPI_read(Eventset2, values2);
  PAPI_stop(Eventset2, values2);
  
  //-------------------------   Third run for extracting the total cache misses of L3!
  reset_data( A, N);
  PAPI_start(Eventset3);
  //-----------------------------------------
  qsort ( A, N, sizeof(edge), keycompare);
  //-----------------------------------------
  PAPI_read(Eventset3, values3);
  PAPI_stop(Eventset3, values3);

  //printf("\nSort_Algorithm\tExecution Time\tL1_Cache_Misses\tL1_Cache_Accesses\tL2_Cache_Misses\tL2_Cache_Accesses\tL3_Cache_Misses\tL3_Cache_Accesses\tL1_MissRate\tL2_MissRate\tL3_MissRate\n");
  //printf("QSORT\t%lli\t%lli\t%lli\t%lli\t%lli\t%lli\t%lli\n", end_time - start_time, values2[0],(values1[0]+values1[1]),values2[1],values2[2], values3[0],values2[3]);
  printf("Execution time = %lli\nL1 cache misses = %lli\nL1 cache accesses = %lli\n", end_time - start_time, values2[0],(values1[0]+values1[1]));
  printf("L2 cache misses = %lli\nL2 cache accesses = %lli\n", values2[1],values2[2]);
  printf("L3 cache misses = %lli\nL3 cache accesses = %lli\n\n", values3[0],values2[3]);
  //printf("Execution time = %lli\n", end_time - start_time);
  PAPI_reset(Eventset1);
  PAPI_reset(Eventset2);
  PAPI_reset(Eventset3);
  

  printf("Heapsort  %d  \n", N);
  //-------------------------   first run for extracting the total cache accesses for L1 in one Eventset and also the execution time!
  t1 = Wtime();
  reset_data( A, N);
  PAPI_start(Eventset1);
  start_time = PAPI_get_real_usec();
  //-----------------------------------------
  heapsort ( A, N );
  //-----------------------------------------
  end_time = PAPI_get_real_usec();
  PAPI_read(Eventset1, values1);
  PAPI_stop(Eventset1, values1);
  t2 = Wtime();
  timings[1] = t2-t1;
  
  //-------------------------   second run for extracting the total cache misses of L1 and L2 / total accesses for L2 and L3!
  reset_data( A, N);
  PAPI_start(Eventset2);
  //-----------------------------------------
  heapsort ( A, N );
  //-----------------------------------------
  PAPI_read(Eventset2, values2);
  PAPI_stop(Eventset2, values2);
  
  //-------------------------   Third run for extracting the total cache misses of L3!
  reset_data( A, N);
  PAPI_start(Eventset3);
  //-----------------------------------------
  heapsort ( A, N );
  //-----------------------------------------
  PAPI_read(Eventset3, values3);
  PAPI_stop(Eventset3, values3);

  //printf("HEAPSORT\t%lli\t%lli\t%lli\t%lli\t%lli\t%lli\t%lli\n", end_time - start_time, values2[0],(values1[0]+values1[1]),values2[1],values2[2], values3[0],values2[3]);
  printf("Execution time  %lli\nL1 cache misses  %lli\nL1 cache accesses  %lli\n", end_time - start_time, values2[0],(values1[0]+values1[1]));
  printf("L2 cache misses  %lli\nL2 cache accesses  %lli\n", values2[1],values2[2]);
  printf("L3 cache misses  %lli\nL3 cache accesses  %lli\n\n", values3[0],values2[3]);
  //printf("Execution time = %lli\n", end_time - start_time);
  PAPI_reset(Eventset1);
  PAPI_reset(Eventset2);
  PAPI_reset(Eventset3);

  
  printf("Shellsort  %d  \n", N);
  //-------------------------   first run for extracting the total cache accesses for L1 in one Eventset and also the execution time!
  t1 = Wtime();
  reset_data( A, N);
  PAPI_start(Eventset1);
  start_time = PAPI_get_real_usec();
  //-----------------------------------------
  shellsort ( A, N );
  //-----------------------------------------
  end_time = PAPI_get_real_usec();
  PAPI_read(Eventset1, values1);
  PAPI_stop(Eventset1, values1);
  t2 = Wtime();
  timings[2] = t2-t1;
  
  //-------------------------   second run for extracting the total cache misses of L1 and L2 / total accesses for L2 and L3!
  reset_data( A, N);
  PAPI_start(Eventset2);
  //-----------------------------------------
  shellsort ( A, N );
  //-----------------------------------------
  PAPI_read(Eventset2, values2);
  PAPI_stop(Eventset2, values2);
  
  //-------------------------   Third run for extracting the total cache misses of L3!
  reset_data( A, N);
  PAPI_start(Eventset3);
  //-----------------------------------------
  shellsort ( A, N );
  //-----------------------------------------
  PAPI_read(Eventset3, values3);
  PAPI_stop(Eventset3, values3);

  //printf("SHELLSORT\t%lli\t%lli\t%lli\t%lli\t%lli\t%lli\t%lli\n", end_time - start_time, values2[0],(values1[0]+values1[1]),values2[1],values2[2], values3[0],values2[3]);
  printf("Execution time = %lli\nL1 cache misses = %lli\nL1 cache accesses = %lli\n", end_time - start_time, values2[0],(values1[0]+values1[1]));
  printf("L2 cache misses = %lli\nL2 cache accesses = %lli\n", values2[1],values2[2]);
  printf("L3 cache misses = %lli\nL3 cache accesses = %lli\n\n", values3[0],values2[3]);
  //printf("Execution time = %lli\n", end_time - start_time);
  PAPI_reset(Eventset1);
  PAPI_reset(Eventset2);
  PAPI_reset(Eventset3);
  
  
  printf("Insort  %d\n", N);
  //-------------------------   first run for extracting the total cache accesses for L1 in one Eventset and also the execution time!
  t1 = Wtime();
  reset_data( A, N);
  PAPI_start(Eventset1);
  start_time = PAPI_get_real_usec();
  //-----------------------------------------
  insort ( A, N );
  //-----------------------------------------
  end_time = PAPI_get_real_usec();
  PAPI_read(Eventset1, values1);
  PAPI_stop(Eventset1, values1);
  t2 = Wtime();
  timings[3] = t2-t1;
  
  //-------------------------   second run for extracting the total cache misses of L1 and L2 / total accesses for L2 and L3!
  reset_data( A, N);
  PAPI_start(Eventset2);
  //-----------------------------------------
  insort ( A, N );
  //-----------------------------------------
  PAPI_read(Eventset2, values2);
  PAPI_stop(Eventset2, values2);
  
  //-------------------------   Third run for extracting the total cache misses of L3!
  reset_data( A, N);
  PAPI_start(Eventset3);
  //-----------------------------------------
  insort ( A, N );
  //-----------------------------------------
  PAPI_read(Eventset3, values3);
  PAPI_stop(Eventset3, values3);

  //printf("INSORT\t%lli\t%lli\t%lli\t%lli\t%lli\t%lli\t%lli\n", end_time - start_time, values2[0],(values1[0]+values1[1]),values2[1],values2[2], values3[0],values2[3]);
  printf("Execution time\t%lli\nL1 cache misses\t%lli\nL1 cache accesses = %lli\n", end_time - start_time, values2[0],(values1[0]+values1[1]));
  printf("L2 cache misses = %lli\nL2 cache accesses = %lli\n", values2[1],values2[2]);
  printf("L3 cache misses = %lli\nL3 cache accesses = %lli\n\n", values3[0],values2[3]);
  //printf("Execution time = %lli\n", end_time - start_time);
  PAPI_reset(Eventset1);
  PAPI_reset(Eventset2);
  PAPI_reset(Eventset3);
  
  
  
  printf(" Quicksort  %d  \n", N);
  //-------------------------   first run for extracting the total cache accesses for L1 in one Eventset and also the execution time!
  t1 = Wtime();
  reset_data( A, N);
  PAPI_start(Eventset1);
  start_time = PAPI_get_real_usec();
  //-----------------------------------------
  quicksort ( A, 0, N-1 );
  //-----------------------------------------
  end_time = PAPI_get_real_usec();
  PAPI_read(Eventset1, values1);
  PAPI_stop(Eventset1, values1);
  t2 = Wtime();
  timings[4] = t2-t1;
  
  //-------------------------   second run for extracting the total cache misses of L1 and L2 / total accesses for L2 and L3!
  reset_data( A, N);
  PAPI_start(Eventset2);
  //-----------------------------------------
  quicksort ( A, 0, N-1 );
  //-----------------------------------------
  PAPI_read(Eventset2, values2);
  PAPI_stop(Eventset2, values2);
  
  //-------------------------   Third run for extracting the total cache misses of L3!
  reset_data( A, N);
  PAPI_start(Eventset3);
  //-----------------------------------------
  quicksort ( A, 0, N-1 );
  //-----------------------------------------
  PAPI_read(Eventset3, values3);
  PAPI_stop(Eventset3, values3);

  //printf("QUICKSORT\t%lli\t%lli\t%lli\t%lli\t%lli\t%lli\t%lli\n", end_time - start_time, values2[0],(values1[0]+values1[1]),values2[1],values2[2], values3[0],values2[3]);
  printf("Execution time = %lli\nL1 cache misses = %lli\nL1 cache accesses = %lli\n", end_time - start_time, values2[0],(values1[0]+values1[1]));
  printf("L2 cache misses = %lli\nL2 cache accesses = %lli\n", values2[1],values2[2]);
  printf("L3 cache misses = %lli\nL3 cache accesses = %lli\n\n", values3[0],values2[3]);
  //printf("Execution time = %lli\n", end_time - start_time);
  PAPI_reset(Eventset1);
  PAPI_reset(Eventset2);
  PAPI_reset(Eventset3);
  
  
  printf("\n\n\nTime to sort array of %d elements\n", N);
  for ( i=0; i<5; i++ ) {
      printf("  %s: %lf seconds\n", names[i], timings[i]);
  }
  



  free (A);
  // printing total number of overflow on each PAPI counter
  printf("\nTotal number of overflow happend on the counter PAPI_LD_INS is:   %d", total_1);
  printf("\nTotal number of overflow happend on the counter PAPI_SR_INS is:   %d", total_2);
  printf("\nTotal number of overflow happend on the counter PAPI_L1_TCM is:   %d", total_3);
  printf("\nTotal number of overflow happend on the counter PAPI_L2_TCM is:   %d", total_4);
  printf("\nTotal number of overflow happend on the counter PAPI_L2_TCA is:   %d", total_5);
  printf("\nTotal number of overflow happend on the counter PAPI_L3_TCM is:   %d", total_6);
  printf("\nTotal number of overflow happend on the counter PAPI_L3_TCA is:   %d\n", total_7);
  return 0;
}


static void  reset_data ( edge *A, int size )
{
    
    for ( int i=0; i<size; i++ ) {
	A[i].a = i;
	A[i].b = i;
	A[i].w = size-i;
    }
 
    return;
}

static int keycompare ( const void *x, const void *y)
{
    edge *a, *b;

    a = (edge *) x;
    b = (edge *) y;
    
    if (a->w < b->w ) {
	return (-1);
    }
    if (a->w > b->w ) {
	return (1);
    }
	
    return 0;
}

TimeType Wtime (void)
{
    struct timeval tp;
    double sec=0.0;
    double psec=0.0;

    gettimeofday( &tp, NULL );
    sec = (double)tp.tv_sec;
    psec = ((double)tp.tv_usec)/((double)1000000.0);

    return (sec+psec);
}


double Wtime_diff ( TimeType endtime, TimeType starttime )
{
    double timediff;
    timediff = endtime - starttime;
    return timediff;
}
