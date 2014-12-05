/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 *
 *
 *
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Jesus Zarate",
    /* First member's email address */
    "jesus.zarate@utah.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

/* basic constants and macros for manipulating the free list */ 
#define WSIZE       4       /* word size (bytes) */ 
#define DSIZE       8       /* doubleword size (bytes) */
#define CHUNKSIZE  (1<<12)  /* initial heap size (bytes) */ 
#define OVERHEAD    8       /* overhead of header & footer (bytes) */ 

#define MAX(x, y) ((x) > (y) ? (x) : (y))   

/* Pack a size and allocated bit into a word */ 
#define PACK(size, alloc)  ((size) | (alloc))

 /* Read and write a word at address p */ 
#define GET(p)       (*(size_t*)(p))
#define PUT(p, val)  (*(size_t*)(p) = (val))   

/* Read the size and allocated fields from address p */ 
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1) 

/* Given block ptr bp, compute address of its header and footer */ 
#define HDRP(bp)       ((char*)(bp) - WSIZE)  
#define FTRP(bp)       ((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char*)(bp) + GET_SIZE(((char*)(bp) - WSIZE))) 
#define PREV_BLKP(bp)  ((char*)(bp) - GET_SIZE(((char*)(bp) - DSIZE)))
 
#define LIST_BLOCK_SIZE    20       /* The list sizes will be of 20 */

#define TAG          4

//#define NEXT_FREE() 
//#define PREV_FREE() 



/* Segregated free lists  */


static char* heap_listp;

static unsigned int* free_list16;

//static char* free_list0_64; 
//static char* free_list65_128; 
//static char* free_list129_256; 
//static char* free_list257_512; 
//static char* free_list513_1024; 
//static char* free_list1025_2048; 
//static char* free_list2049_4096; 

int mm_check(void) 
{
  char* bp;
  for(bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp))
    {
      /* Make sure header and footer have identical block sizes*/
      if(GET_SIZE(HDRP(bp)) != GET_SIZE(FTRP(bp)))
	{
	  printf("Size of header and footer do not match");
	  return 0;
	}

      if(GET_ALLOC(HDRP(bp)) != GET_ALLOC(FTRP(bp)))
	{
	  printf("Allocated bits are not the same");
	  return 0;
	}

      
      if(!GET_ALLOC(HDRP(bp)))
	{
	  //printf("Previous: %s\t", PREV_BLKP(bp));
	  //printf("Current: %s\t", HDRP(bp));
	  //printf("Next: %s\n", NEXT_BLKP(bp));
	}
      //printf("Header: %lu\t", GET_ALLOC(HDRP(bp)));
      //printf("Footer: %lu\t", GET_ALLOC(FTRP(bp)));
      //printf("Payload: %lu\n", GET_ALLOC(FTRP(bp)));
      
    }
  return 1;
}

void add_to_free(void* bp)
{
  size_t size = GET_SIZE(bp);
  
  if(size > 0 && size <= 64)
    {

    }
  else if(size > 64 && size <= 128)
    {

    }
  else if(size > 128 && size <= 256)
    {

    }
  else if(size > 256 && size <= 512)
    {

    }
  else if(size > 512 && size <= 1024)
    {

    }
  else if(size > 1024 && size <= 2048)
    {

    }
  else
    {
      
    }
}

 void add_to_list(void* bp)
{
  printf("here");
  /* add to the end of the list */
  void* previous_block;
  void* current_block;
  void* next_block = NULL;

  int size = GET_SIZE(HDRP(bp));

  /* Size where the block should go */

  int list_size = size / LIST_BLOCK_SIZE;
  
  /* Get the pointer to the first item on the list that fits */
  current_block = (char*)GET(heap_listp + (list_size * WSIZE));/* TODO: MAKE MACRO */


  //  for (; (int)temp_cur != 0 && GET_SIZE(HDRP(temp_cur)) < size; temp_cur = (char *)GET(temp_cur+WSIZE))
  //temp_prev = temp_cur;

  int csize = 0;



  //if the free list is empty 
  if(current_block == 0){
    //set free list pointer to point to this block.
    PUT(heap_listp + (list_size * WSIZE), (int)bp);	
    //set this blocks previous free block poitner to 0 indicating it is first on the list.
    PUT(bp, 0); 
    //set this blocks next free block pointer to 0 indicating it is last on the list.  
    PUT(bp+WSIZE, 0);
  }

  
  while((csize = GET_SIZE(HDRP(current_block))) > 0)
    {
      printf("csize: %d", csize);
      if(csize != 0 && csize >= size)
	{
	  
	}
      current_block = (char *)GET(current_block + WSIZE);
    }

  /* Walk through the list starting at current block and find a place where the block can fit*/
  //  for(; GET_SIZE(HDRP(bp)) > 0; current_block = NEXT_BLKP(current_block))
  //  {
    /* If the block is greater than the current_block get the block before it*/
    //if(GET_SIZE(current_block) >= size)
  //    {
  //next_block = current_block;
  //  break;
      //}    
      //  }

  /* Save previous block */
      //  previous_block = PREV_BLKP(next_block);

  /* Set next_block's previous block to be bp */
      //  PUT(PREV_BLKP(next_block), (int)(bp));

  /* Set previous_block's next block to be bp */
      //  PUT(NEXT_BLKP(previous_block), (int)(bp));

  /* Set bp's next to be next_block */
      //  PUT(NEXT_BLKP(bp), (int)(next_block));

  /* Set bp's previous to be previous_block */
      //  PUT(PREV_BLKP(bp), (int)(previous_block));
  
}

static void remove_from_free(void* bp)
{
  
  

}

static void* coalesce(void* bp) 
{

  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp))); 
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));   
  size_t size = GET_SIZE(HDRP(bp));    

  if (prev_alloc && next_alloc) 
    {
      printf("here");
      add_to_list(bp);
      //mm_check(); 
      return bp; 
    }  
 
  else if (prev_alloc && !next_alloc) {
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));  
    PUT(HDRP(bp), PACK(size, 0));     
    PUT(FTRP(bp), PACK(size ,0)); 

    add_to_free(bp);
    return(bp);
  }    
  else if (!prev_alloc && next_alloc) 
    {      
      size += GET_SIZE(HDRP(PREV_BLKP(bp)));
      PUT(FTRP(bp), PACK(size, 0));   
      PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));    

      add_to_free(bp);
      return(PREV_BLKP(bp));
    }   
  else
    {                                           
      size += GET_SIZE(HDRP(PREV_BLKP(bp))) +
	GET_SIZE(FTRP(NEXT_BLKP(bp)));  
      PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));   
      PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));   

      add_to_free(bp);
      return(PREV_BLKP(bp));
    } 
}


/*
 * extend_heap - Extends the heap with a new free block
 */
static void *extend_heap(size_t words) 
{
  char *bp;
  size_t size;
  
  /* Allocate an even number of words to maintain alignment */
  size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
  if ((long)(bp = mem_sbrk(size)) == -1)
    return NULL;

  /* Initialize free block header/footer and the epilogue header */
  PUT(HDRP(bp), PACK(size, 0)); /* Free block header */
  PUT(FTRP(bp), PACK(size, 0)); /* Free block footer */
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */

  /* Coalesce if the previous block was free */
  return coalesce(bp);
}

static void* find_fit(size_t asize) 
{   
  void* bp;   

  /* first fit search */ 
  for(bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) 
    {   
      if(!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp))))
	{
	  return bp;
	}  
    } 
  return NULL; /* no fit */ 
}

static void place(void* bp, size_t asize) 
{   
  size_t csize = GET_SIZE(HDRP(bp));   
  if((csize - asize) >= (DSIZE + OVERHEAD)) 
    {  
      /* if new free block */  
      PUT(HDRP(bp), PACK(asize, 1));             /* would be at least */    
      PUT(FTRP(bp), PACK(asize, 1));             /* as big as min */    
      bp = NEXT_BLKP(bp);                        /* block size, split */ 
      PUT(HDRP(bp), PACK(csize-asize, 0)); 
      PUT(FTRP(bp), PACK(csize-asize, 0));   
    }  
  else 
    {                                            /* else, do not split */   
      PUT(HDRP(bp), PACK(csize, 1));  
      PUT(FTRP(bp), PACK(csize, 1)); 
    }
}

void splitList(unsigned int* list_ptr, int splitSize, int blockSize)
{
  /* Make sure block size is divisible by 4 */
  int size = blockSize/(splitSize * 4);

  int i = 0;
  for(; i < size; i++)
    {
      *list_ptr = (int)((char*)list_ptr + size);
    }

}


/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
  //if((free_list16 = mem_sbrk(200)) != (void*)-1)
  //{
  //  splitList(free_list16, 16, 200);
  //}


  /* create the initial empty heap – four words */    
  if ((heap_listp = mem_sbrk(4*WSIZE)) == NULL)
    return -1;

  PUT(heap_listp, 0);                     

  /* alignment padding */     
  PUT(heap_listp+WSIZE, PACK(OVERHEAD, 1));  /* prologue header */    
  PUT(heap_listp+DSIZE, PACK(OVERHEAD, 1));  /* prologue footer */     
  PUT(heap_listp+WSIZE+DSIZE, PACK(0, 1));   /* epilogue header */     
  heap_listp += DSIZE;  /* move heap_listp past prologue's header */    

  /* extend the empty heap with a free block of CHUNKSIZE bytes */    
  if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
    return -1;

  return 0;
}

void* mm_malloc(size_t size) 
{   
  size_t asize;       /* adjusted block size */    
  size_t extendsize;  /* amount to extend heap if no fit */  
  char* bp;           /* Ignore spurious requests */   
  if (size <= 0)
    return NULL;

  /* Adjust block size to include overhead and alignment reqs */  
  if (size <= DSIZE)
    asize = DSIZE + OVERHEAD;
  else
    asize = DSIZE * ((size + (OVERHEAD) + (DSIZE-1)) / DSIZE);

  /* Search the free list for a fit */  
  if ((bp = find_fit(asize)) != NULL) {
    place(bp, asize);     
    return bp;
  }    

  /* No fit found. Get more memory and place the block */   
  extendsize = MAX(asize,CHUNKSIZE);   
  if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
    return NULL;   

  place(bp, asize);   


  return bp;
}

///* 
// * mm_malloc - Allocate a block by incrementing the brk pointer.
// *     Always allocate a block whose size is a multiple of the alignment.
// */
//void *mm_malloc(size_t size)
//{
//    int newsize = ALIGN(size + SIZE_T_SIZE);
//    void *p = mem_sbrk(newsize);
//    if (p == (void *)-1)
//	return NULL;
//    else {
//        *(size_t *)p = size;
//        return (void *)((char *)p + SIZE_T_SIZE);
//    }
//}


/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
  size_t size = GET_SIZE(HDRP(ptr));   
  PUT(HDRP(ptr), PACK(size, 0));    
  PUT(FTRP(ptr), PACK(size, 0));    
  coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    size_t old_size = GET_SIZE(HDRP(ptr));
    void *newptr;
    size_t copySize;
    char* bp;
    size_t extendsize; /* amount to extend heap if no fit */

    if(size == 0)
      {
	mm_free(ptr);
	return NULL;
      }
    if(ptr == NULL)
      {
	newptr = mm_malloc(size);
      }
    else 
      {
	/* Allocate the new larger size */
	size_t asize; /* Adjusted block size */
	
	if(size <= 0)
	  bp = NULL;

	/* Adjust block size to include overhead and alignment requirements */
	if(size <= DSIZE)
	  asize = DSIZE + OVERHEAD;
	else
	  asize = DSIZE * ((size + (OVERHEAD) + (DSIZE-1)) / DSIZE);
	
	/* Search the free list for a fit */
	if((bp = find_fit(asize)) != NULL)
	  {
	    place(bp, asize);
	  }

	/* If no fit found, get more memory and place block there */
	else
	  {
	    extendsize = MAX(asize, CHUNKSIZE);
	   
	    if((bp = extend_heap(extendsize/WSIZE)) == NULL)
	      return NULL;
	    
	    /* bp will be set the address of the new allocated larger block */
	    place(bp, asize);
	  }
	newptr = bp;

	copySize = old_size - SIZE_T_SIZE;
	if (size < copySize)
	  copySize = size;
	memcpy(newptr, oldptr, copySize);

	/* Free the memory from the old block */
	//mm_free(oldptr);
	size_t size = GET_SIZE(HDRP(ptr));
	PUT(HDRP(ptr), PACK(size, 0));
	PUT(FTRP(ptr), PACK(size, 0));
	coalesce(ptr);
      }
    //mm_check();
    return newptr;
}

/*
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    
    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}
*/













