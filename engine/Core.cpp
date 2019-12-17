#include "../app/App.hpp"

using v8::HandleScope;

int main(int argc, char* argv[]) {

	App app;

	app.CreatePlatform(argv);
	app.CreateVM();

	{

		// Enter isolate scope
		Isolate::Scope isolatescope(app.GetIsolate());

		// Enter handle scope
		HandleScope handlescope(app.GetIsolate());

		// Create global environment object
		app.CreateGlobalEnvironment();

		// Setup engine environment
		app.SetupEngineEnvironment();

		// Call app setup environment hook
		app.SetupEnvironment();

		// Call app start hook
		app.Start(argc, argv);

	}

	// Shutdown
	app.ShutdownVM();

	return 0;
	
}