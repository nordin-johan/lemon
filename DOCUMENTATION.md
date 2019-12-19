# Documentation

This document contains documentation for the Lemon framework.

## App Hooks

##### App::Start()

The App::Start() hook is required. It is automatically called by Lemon after a new virtual machine instance has been created and starts the app inside the virtual machine. In this hook you can perform operations such as handling command line arguments, setting up one or more contexts, threads and execute javascript code.

##### App::SetupEnvironment()

The App::SetupEnvironment() hook is optional. This hook is called before the App::Start() hook and it allows you to bind js >< c++ methods to the global environment before you create a context in the App::Start() hook.

## Methods

Lemon has built in methods you can use for performing common operations.

##### RunJsFromFile(const char* filename)

Reads a file and executes the javascript inside the file. Returns boolean.

##### ReadFile(const char* filename)

Reads the content of a file. Returns a v8 MaybeLocal<String>.
	
##### ExecuteString(Local<String> source, const char* filename) 

Executes a javascript string. Returns boolean.

##### ToCString(const String::Utf8Value& value)

Converts a Utf8Value to a C string. Returns const char.

## Error Handling

Lemon automatically handles all types of javascript errors. All errors that are not related to javascript must be handled by yourself.

## Examples

```c++
static void HelloWorld(const FunctionCallbackInfo<Value>& args) {	
	printf("Hello world");
}

void App::SetupEnvironment() {
	this->CreateGlobalMethod("hello", HelloWorld);
}
```
