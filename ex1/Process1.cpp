#include "SharedMemoryBuffer.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream >
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

using namespace boost::interprocess;

int main() {
	srand(time(NULL));

	//use old shared memory if exists else create a new one
	shared_memory_object sharedobj(open_or_create, "shmo", read_write);

	//set the size of the memory object
	sharedobj.truncate(sizeof(shared_memory_buffer));

	//map the whole shared memory in this process
	mapped_region region(sharedobj, read_write);

	//get the region address
	void * addr = region.get_address();

	//create a shared memory buffer in memory
	shared_memory_buffer *my = new (addr) shared_memory_buffer;

	while (true) {
		//wait until the written number gets executed
		my->writer.wait();

		//print the square of the original value
		std::cout << "Square: " << my->value << "\n";

		//create the original value
		my->value = 7;

		//reader can execute written number
		my->reader.post();
	}

	return 0;
}