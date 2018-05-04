# StackHeap

## Description
Dynamic-esque memory allocation, on the stack.

Allows "allocating" memory of unknown size at compile time.

Strategy: Pre-allocate a big array on the stack, and treat it as if it's the heap.

## Usage

### C style allocation (malloc/free)
    #include <stackheap.h>
    
    #define STACKHEAP_SIZE 64
    
    char StackHeap<STACKHEAP_SIZE>::memory[STACKHEAP_SIZE];
    char StackHeap<STACKHEAP_SIZE>::block_directory[STACKHEAP_SIZE];
    char StackHeap<STACKHEAP_SIZE>::unused_block_id;
    
    int main()
    {
    	int size = 8;
        int* arr = (int*) StackHeap<STACKHEAP_SIZE>::malloc(sizeof(int) * size);
        if(arr != nullptr)
        {
        	// Allocated successfully! Use as usual
            StackHeap<STACKHEAP_SIZE>::free(arr);
        }
    	return 0;
    }
### C++ style allocation (new/delete)
    #define STACKCTOR_DEFINEHEAP
	#include <stackctor.h>
    
    class MyClass
    {
    public:
	    MyClass()
	    {
		    // Constructor is automatically called
	    }
	    ~MyClass()
	    {
	    	// Destructor is automatically called
	    }
    };
    
    int main()
    {
    	MyClass* object = static_new<MyClass>();
        if(object != nullptr)
		{
			// The object is now usable
			static_delete<MyClass>(object);
		}
    	return 0;
    }

## License
The software is licensed under the MIT license. See file: [LICENSE](https://github.com/soryy708/StackHeap/blob/master/LICENSE).
