#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <cassert>
#include "Helpers.hpp"

#include "libplatform/libplatform.h"
#include <v8.h>

using v8::V8;
using v8::Platform;
using v8::Isolate;
using v8::Context;
using v8::ArrayBuffer;
using v8::Local;
using v8::ObjectTemplate;
using v8::NewStringType;
using v8::FunctionTemplate;
using v8::FunctionCallbackInfo;
using v8::Value;

class Environment {

	private:

		std::unique_ptr<Platform> platform;
		Isolate::CreateParams create_params;

		Isolate* isolate;
		Local<ObjectTemplate> global;

	public:

		virtual void CreatePlatform(char* argv[]) final;
		virtual void CreateVM() final;
		virtual void ShutdownVM() final;

		virtual void CreateGlobalEnvironment() final;
		virtual Local<Context> CreateLocalContext() final;

		Isolate* GetIsolate();
		virtual Local<ObjectTemplate> GetGlobal() final;

		virtual void SetupEngineEnvironment() final;
		virtual void SetupEnvironment();
		
};

#endif