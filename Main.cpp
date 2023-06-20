/*
	TODO list to when the setup is finihed

	- Compile the shaders inside the code instead of using glslc.exe
	- Integrate ImGui
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