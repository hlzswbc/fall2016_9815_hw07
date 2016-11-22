#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <math.h>
#include "SharedMemoryBuffer.h"

using namespace boost::interprocess;

int main() {
	//create a shared memory object
	shared_memory_object sharedobj(open_only, "shmo", read_write);

	//Map the whole shared memory in this process
	mapped_region region(sharedobj, read_write);

	//get the region address
	void * addr = region.get_address();

	//Obtain the shared structure
	shared_memory_buffer * my = static_cast<shared_memory_buffer*>(addr);

	while (true) {
		//wait until a number gets available
		my->reader.wait();

		//print the original value
		std::cout << "Original Value: " << my->value << "\n";

		//create the square of the original value
		my->value = (my->value) * (my->value);

		//writer can print square
		my->writer.post();
	}
	return 0;
}