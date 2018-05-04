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
#ifndef STACKHEAP_H_INCLUDED
#define STACKHEAP_H_INCLUDED

template<int memory_size>
class StackHeap
{
private:
	// Base assumption - char=1byte
	static char memory[memory_size];
	static char block_directory[memory_size]; // zero = unallocated; TODO: Research strategy that uses less memory
	static char unused_block_id; // currently may overflow

	static unsigned int getBlockSize(void* block) // O(n)
	{
		if(block >= &memory[0] && block < &memory[memory_size])
		{
			const unsigned int start_index = (char*)block - &memory[0];
			
			// Find the end of the block
			int i;
			for (i = start_index; i < memory_size && block_directory[i] == block_directory[start_index]; ++i);
			
			return i - start_index;
		}
		return 0;
	}

public:
	// Base assumption - size_t==1 -> 1char
	static void* malloc(size_t size) // O(n^2)
	{
		if(size <= memory_size)
		{
			unsigned int i = 0;
			
		stackheap_find_free_block: // oh no, you know what this means
			while(i < memory_size && block_directory[i] != 0)
			{
				++i;
			}

			if(i < memory_size) // found free memory
			{
				const unsigned int block_size = StackHeap::getBlockSize(&memory[i]);

				if(block_size >= size)
				{
					for(unsigned int j = 0; j < size; ++j)
					{
						block_directory[i + j] = unused_block_id;
					}
					
					++unused_block_id;
					if(unused_block_id == 0) // overflow
						++unused_block_id; // this may be an issue if you do a lot of allocs

					return &memory[i];
				}
				else
				{
					// find next block
					++i;
					goto stackheap_find_free_block; // yep, eyes bleed
				}
			}
		}

		return nullptr;
	}

	static void* calloc(size_t size) // O(n^2)
	{
		char* bytes = (char*) StackHeap<memory_size>::malloc(size);
		if(bytes != nullptr)
		{
			for (char* cur = bytes; cur < bytes + size; cur++)
				*cur = 0;
		}
		return bytes;
	}

	static void free(void* block) // O(n)
	{
		if (block >= &memory[0] && block < &memory[memory_size])
		{
			const unsigned int start_index = (char*)block - &memory[0];
			const unsigned int length = StackHeap<memory_size>::getBlockSize(block);
			for(unsigned int i = 0; i < length; ++i)
			{
				block_directory[start_index + i] = 0;
			}
		}
	}

	static void init()
	{
		static bool initialized = false;
		if(!initialized)
		{
			unused_block_id = 1;
			
			for(unsigned int i = 0; i < memory_size; ++i)
			{
				block_directory[i] = 0;
			}

			initialized = true;
		}
	}

	StackHeap() = delete;
	~StackHeap() = delete;
};

#endif
