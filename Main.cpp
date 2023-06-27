/*
	TODO list to when the setup is finihed

	- Compile the shaders inside the code instead of using glslc.exe
	- Integrate ImGui
	- Future Challenges
*/

/*
	Future Challenges

	- Use a different queue family specifically for transfer operations
		It will require the following modifications to the program:

		- Modify QueueFamilyIndices and findQueueFamilies to explicitly look for a queue family with the 
		VK_QUEUE_TRANSFER_BIT bit, but not the VK_QUEUE_GRAPHICS_BIT.
		- Modify createLogicalDevice to request a handle to the transfer queue.
		- Create a second command pool for command buffers that are submitted on the transfer queue family.
		- Submit any transfer commands like vkCmdCopyBuffer to the transfer queue instead of the graphics queue.

	- Proper buffer memory allocation
		In a real world application, we're not supposed to actually call vkAllocateMemory for every individual
		buffer. The maximum number of simultaneous memory allocations is limited by the maxMemoryAllocationCount
		physical device limit, which may be as low as 4096 even on high end hardware. The right way to allocate
		memory for a large number of objects at the same time is to create a custom allocator that splits up a 
		single allocation among many different objects by using the offset parameters that we've seen in many
		functions.
*/

#include "Application.h"

int main() {

	Engine::ApplicationSpec spec;
	spec.Name = "RayTracer.exe";
	spec.Width = 800;
	spec.Height = 600;

	Engine::Application *app = new Engine::Application(spec);

	try {
		app->Run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}