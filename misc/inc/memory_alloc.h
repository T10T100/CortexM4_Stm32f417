#ifndef __ALLOCATOR
#define __ALLOCATOR

#include <stdint.h>
#include <errno.h>
#include "ArrayListStatic.h"


typedef uint32_t memory_size_t;
typedef uint32_t alloc_addr_t; 

class MemoryChunk : public DefaultArrayListBaseNode <MemoryChunk> {
  public:
	  MemoryChunk () : DefaultArrayListBaseNode() {}
      bool equals (MemoryChunk)   
      {
          return true;
      }
    private:
	  memory_size_t size;
	friend class MemoryAllocator;
};

#define __m sizeof(MemoryChunk)

class MemoryAllocator {
	public:
	  MemoryAllocator () {}
      MemoryAllocator (uint32_t, uint32_t);
	  void operator () (uint32_t, uint32_t);
	  void *New (memory_size_t);
	  int32_t Delete (void *);	
	  int32_t check ();	
      
	private:
	  MemoryChunk *separate (MemoryChunk *P, memory_size_t Size);
	  int32_t sanitize (ArrayListBase <MemoryChunk> &List);
	  ArrayListBase <MemoryChunk> poolFree, poolInUse;
      uint32_t Success, errors, sanitized;
};


#endif /*__ALLOCATOR*/
