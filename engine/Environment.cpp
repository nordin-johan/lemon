#include "Environment.hpp"

void Environment::Version(const FunctionCallbackInfo<Value>& args) {
	printf("Lemon v1.0.0\n");
}

void Environment::CreatePlatform(char* argv[]) {

	V8::InitializeICUDefaultLocation(argv[0]);
	V8::InitializeExternalStartupData(argv[0]);
	this->platform = v8::platform::NewDefaultPlatform();
	V8::InitializePlatform(platform.get());
	V8::Initialize();

}

void Environment::CreateVM() {

	this->create_params.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
	this->isolate = v8::Isolate::New(this->create_params);

}

void Environment::CreateGlobalEnvironment() {
	this->global = ObjectTemplate::New(this->isolate); 
}

Local<ObjectTemplate> Environment::GetGlobal() {
	return this->global;
}

void Environment::ShutdownVM() {

	this->isolate->Dispose();
	V8::Dispose();
	V8::ShutdownPlatform();
	delete this->create_params.array_buffer_allocator;

}

Local<Context> Environment::CreateLocalContext() {
	return Context::New(this->isolate, NULL, this->global);
}

Isolate * Environment::GetIsolate() {
	return this->isolate;
}

// setup environment for the engine
void Environment::SetupEngineEnvironment() {

	this->GetGlobal()->Set(
		String::NewFromUtf8(this->GetIsolate(), "version", NewStringType::kNormal).ToLocalChecked(),
		FunctionTemplate::New(this->GetIsolate(), Environment::Version)
	);

}

// setup environment for the app
void Environment::SetupEnvironment() {}