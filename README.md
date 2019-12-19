# Lemon :lemon:
Lemon is a framework for building Javascript runtime software.

* __C++ bindings__

	Fully integrated support for javascript > c++ bindings and viceversa.

* __Object oriented__

	Lemon lets you build your applications with a simple and scalable object oriented approach.

* __Single and multi threaded__
	
	Lemon runs on a single thread by default but has support for running on multiple threads.
	
Video introduction: https://www.youtube.com/watch?v=5fWIf2A6Z_s

## Example

A simple example of an application written in Lemon looks like this:

```
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

You can find this example in the 'app' folder, in the file App.cpp.

__The example does the following:__
1. Calls the Start method which automatically starts the application inside a virtual machine.
2. Loops each argument given from a command line, each argument is expected to be a javascript file.
3. Creates a new context and enters the context.
4. Calls the RunJsFromFile method which executes the code inside a Javascript file.

_A context is an execution environment that allows Javascript to be executed inside the virtual machine._
	
## Installing Lemon

Lemon currently has build support for Linux only.

__Download the repo__

``` git clone https://github.com/nordin-johan/lemon.git ```

__Navigate to the directory__

```cd lemon```

__Build__

```make```

You can now run ```./lemon App.js``` in your terminal to try it out, it should print the current version of Lemon.

## App Hooks

__App::Start()__

The App::Start() hook is required. It is automatically called by Lemon after a new virtual machine instance has been created and starts the app inside the virtual machine. In this hook you can perform operations such as handling command line arguments, setting up one or more contexts, threads and execute javascript code.

__App::SetupEnvironment()__

The App::SetupEnvironment() hook is optional. This hook is called before the App::Start() hook and it allows you to bind js -> c++ methods to the global environment before you create a context in the App::Start() hook.

You can access the global environment object like this: ```this->GetGlobal()```. 

## Methods

Lemon has built in methods you can use for performing common operations.

##### RunJsFromFile(const char* filename)

Reads a file and executes the javascript inside the file. Returns boolean.

##### ReadFile(const char* filename)

Reads the content of a file. Returns a v8 MaybeLocal<String>.
	
##### ExecuteString(Local<String> source, const char* filename) 

Executes a javascript string. Returns boolean.

## Error Handling

Lemon automatically handles all types of javascript errors. All errors that are not related to javascript must be handled by yourself.
