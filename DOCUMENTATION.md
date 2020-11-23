# Documentation

This document contains documentation for the Lemon framework.

## App Hooks

### App::Start()

This hook is required.

Called by the Lemon framework after a new virtual machine instance has been created and starts the app inside the virtual machine. In this hook you can perform operations such as reading command line arguments, setting up one or more contexts, threads and execute javascript code.

### App::SetupEnvironment()

This hook is optional.

Called before the App::Start() hook. This hook allows you to bind javascript methods to c++ methods and viceversa to the global environment before you create a context in the App::Start() hook.

## Methods

Lemon has built in methods you can use for performing common operations.

### RunJsFromFile(const char* filename)

Reads a file and executes the javascript inside the file. Returns boolean.

### ReadFile(const char* filename)

Reads the content of a file. Returns a v8 MaybeLocal<String>.
	
### ExecuteString(Local<String> source, const char* filename) 

Executes a javascript string. Returns boolean.

## Error Handling

Lemon automatically handles all types of javascript errors. All errors that are not related to javascript must be handled by yourself.

## Examples

### Hello World

App.cpp

```c++
#include "App.hpp"

static void HelloWorld(const FunctionCallbackInfo<Value>& args) {	
	printf("Hello world");
}

void App::SetupEnvironment() {
	this->CreateGlobalMethod("helloworld", HelloWorld);
}

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
```

App.js

```js
helloworld();
```

### Console

App.cpp

```c++
#include "App.hpp"

using namespace v8;

static void Log(const FunctionCallbackInfo<Value>& args) {

    HandleScope scope(args.GetIsolate());

    String::Utf8Value str(args.GetIsolate(), args[0]);
    const char* cstr = StaticHelpers::ToCString(str);

    fprintf(stdout, "%s", cstr);

    fprintf(stdout, "\n");
    fflush(stdout);

}

void App::Start(int argc, char* argv[]) {

	for (int i = 1; i < argc; ++i) {

		// Get filename of the javascript file to run
		const char* filename = argv[i];

		// Create a new context for executing javascript code
		Local<Context> context = this->CreateLocalContext();

		// Enter the new context
		Context::Scope contextscope(context);
		
		// Create global console object and set log property
		this->CreateGlobalObject("console")
			.SetPropertyMethod("log", Log)
			.Register();

		// Run the javascript file
		this->RunJsFromFile(filename);

	}

}
```

App.js

```js
console.log("Hello world");
```
