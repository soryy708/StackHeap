/* StackHeap
 *   Dynamic-esque memory allocation, on the stack.
 *   Allows "allocating" memory of size unknown at compile time.
 *   Strategy: Pre-allocate a big array on the stack, and treat it as if it's the heap.
 *
 * License: MIT
 * Copyright (c) 2018 Ivan Rubinson
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */
#ifndef STACKCTOR_H_INCLUDED
#define STACKCTOR_H_INCLUDED

#include "stackheap.h"

#include <new>

#ifndef STACKCTOR_HEAPSIZE
	#pragma message("stackctor.h included, STACKCTOR_HEAPSIZE undefined. Using default: 512")
	#define STACKCTOR_HEAPSIZE 512
#endif

#ifdef STACKCTOR_DEFINEHEAP
	#pragma message("stackctor.h included, STACKCTOR_DEFINEHEAP undefined. Assuming StackHeap has been defined for the size STACKCTOR_HEAPSIZE elsewhere")
	char StackHeap<STACKCTOR_HEAPSIZE>::memory[STACKCTOR_HEAPSIZE];
	char StackHeap<STACKCTOR_HEAPSIZE>::block_directory[STACKCTOR_HEAPSIZE];
	char StackHeap<STACKCTOR_HEAPSIZE>::unused_block_id;
#endif

template<class T, class ... Params>
T* static_new(Params... params)
{
	StackHeap<STACKCTOR_HEAPSIZE>::init();

	T* object = (T*)StackHeap<STACKCTOR_HEAPSIZE>::malloc(sizeof(T));
	if (object != nullptr)
	{
		new(object) T(params...); // call constructor via <new> library
	}

	return object;
}

template<class T>
void static_delete(T* object)
{
	if(object != nullptr)
	{
		object->~T(); // call destructor
		StackHeap<STACKCTOR_HEAPSIZE>::free(object);
	}
}

#undef STACKCTOR_HEAPSIZE
#undef STACKCTOR_DEFINEHEAP

#endif
