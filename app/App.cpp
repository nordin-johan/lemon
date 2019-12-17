#include "App.hpp"

void App::Start(int argc, char* argv[]) {

	for (int i = 1; i < argc; ++i) {

		// Get filename of the javascript file to run
		const char* filename = argv[i];

		// Create a new context for executing javascript code
		Local<Context> context = this->CreateLocalContext();

		// Enter the new context
		Context::Scope contextscope(context);

		// Run the javascript file
		this->RunJsFromFile(filename);

	}

}