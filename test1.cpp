#include "stackheap.h"
#include <iostream>

#define STACKHEAP_SIZE 32

char StackHeap<STACKHEAP_SIZE>::memory[STACKHEAP_SIZE];
char StackHeap<STACKHEAP_SIZE>::block_directory[STACKHEAP_SIZE];
char StackHeap<STACKHEAP_SIZE>::unused_block_id;

void dump(const char* beginning)
{
	std::cout << "Address\t\tValue" << std::endl << std::endl;

	for(unsigned int i = 0; i < STACKHEAP_SIZE; i++)
	{
		const unsigned int* val_as_int = (unsigned int*) *(int*)(beginning + i);

		std::cout << (int*)(beginning + i) << "\t";

		if(val_as_int >= (unsigned int*) beginning && val_as_int < (unsigned int*) (beginning + STACKHEAP_SIZE))
		{
			std::cout << val_as_int << "\t(pointer -> " << (char) *val_as_int << ", " << (int)(char) *val_as_int << ")";
			i += sizeof(int*) - 1; // -1 because the loop will add one back
		}
		else
		{
			std::cout << (char) *(beginning + i) << "\t\t(" << (int) *(beginning + i) << ")";
		}
		
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int test1main(int argc, char* argv[])
{
	StackHeap<STACKHEAP_SIZE>::init();

	char** mat = (char**) StackHeap<STACKHEAP_SIZE>::malloc(sizeof(char*) * 3);
	if(mat != nullptr)
	{
		mat[0] = (char*)StackHeap<STACKHEAP_SIZE>::malloc(sizeof(char) * 6);
		if(mat[0] != nullptr)
		{
			memcpy(mat[0], "Hello", 6);
		}
		mat[1] = (char*)StackHeap<STACKHEAP_SIZE>::malloc(sizeof(char) * 7);
		if (mat[1] != nullptr)
		{
			memcpy(mat[1], "world,", 7);
		}
		mat[2] = (char*)StackHeap<STACKHEAP_SIZE>::malloc(sizeof(char) * 7);
		if (mat[2] != nullptr)
		{
			memcpy(mat[2], "buddy!", 7);
		}
	}

	dump((char*) mat);

	std::cout << " mat = " << (int*)  mat << std::endl;
	std::cout << "*mat = " << (int*) *mat << std::endl;

	return 0;
}
