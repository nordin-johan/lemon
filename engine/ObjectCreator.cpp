#include "ObjectCreator.hpp"

ObjectCreator::ObjectCreator(Isolate * isolate, const char* objectname) {

	this->isolate = isolate;
	this->ObjectInstance = ObjectTemplate::New(this->isolate);
	this->name = String::NewFromUtf8(this->isolate, objectname, NewStringType::kNormal).ToLocalChecked();

}

ObjectCreator ObjectCreator::SetPropertyMethod(const char* propertyname, void (*callback)(const FunctionCallbackInfo<Value>& args)) {

	this->ObjectInstance->Set(
		String::NewFromUtf8(this->isolate, propertyname, NewStringType::kNormal).ToLocalChecked(),
		FunctionTemplate::New(this->isolate, callback)
	);

	return *this;

}

void ObjectCreator::Register() {

	Local<Object> Instance = this->ObjectInstance->NewInstance(
		this->isolate->GetCurrentContext()
	).ToLocalChecked();

	this->isolate->GetCurrentContext()->Global()->Set(
		this->isolate->GetCurrentContext(), 
		this->name, 
		Instance
	).FromJust();

}