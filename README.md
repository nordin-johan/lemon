# Lemon
Lemon is a framework for building Javascript runtime software, built on the Chrome V8 Javascript Engine.

* __C++ bindings__

	Integrated support for javascript to c++ bindings and viceversa.

* __Object oriented__

	Lemon lets you build your applications with a simple and scalable object oriented approach.

* __Single and multi threaded__
	
	Lemon runs on a single thread by default but has support for running on multiple threads.
	
Video introduction: https://www.youtube.com/watch?v=5fWIf2A6Z_s

## Example

A simple example of an application written in Lemon looks like this:

```c++
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

<a href="https://github.com/nordin-johan/lemon/blob/master/DOCUMENTATION.md">Read the docs</a>
