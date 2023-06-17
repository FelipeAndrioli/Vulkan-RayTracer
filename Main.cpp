/*
	TODO list to when the setup is finihed

	- Compile the shaders inside the code instead of using glslc.exe
*/

#include "Application.h"

int main() {

	Engine::ApplicationSpec spec;
	spec.Name = "RayTracer.exe";
	spec.Width = 800;
	spec.Height = 600;

	Engine::Application app = Engine::Application(spec);

	try {
		app.Run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}