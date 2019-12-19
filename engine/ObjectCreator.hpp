#ifndef OBJECTCREATOR
#define OBJECTCREATOR

#include "libplatform/libplatform.h"
#include <v8.h>

using v8::Local;
using v8::String;
using v8::Isolate;
using v8::NewStringType;
using v8::ObjectTemplate;
using v8::FunctionCallbackInfo;
using v8::Value;
using v8::FunctionTemplate;
using v8::Object;

class ObjectCreator {

	private:

		Isolate* isolate;
		Local<String> name;
		Local<ObjectTemplate> ObjectInstance;

	public:

		ObjectCreator(Isolate * isolate, const char* objectname);
		ObjectCreator SetPropertyMethod(const char* propertyname, void (*callback)(const FunctionCallbackInfo<Value>& args));
		void Register();

};

#endif