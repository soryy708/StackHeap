#define STACKCTOR_DEFINEHEAP
#include "stackctor.h"
#include <iostream>

class MyClass
{
public:
	MyClass()
	{
		std::cout << "The object has been constructed." << std::endl;
	}
	~MyClass()
	{
		std::cout << "The object has been destructed." << std::endl;
	}
};

int test2main(int argc, char* argv[])
{
	MyClass* object = static_new<MyClass>();
	if(object != nullptr)
	{
		std::cout << "The object is now usable." << std::endl;
		static_delete<MyClass>(object);
	}
	else
	{
		std::cout << "Failure allocating object." << std::endl;
	}

	return 0;
}
