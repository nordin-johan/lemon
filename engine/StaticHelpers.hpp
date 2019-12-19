#ifndef STATICHELPERS
#define STATICHELPERS

#include "libplatform/libplatform.h"
#include <v8.h>

using v8::String;

class StaticHelpers {

	public:

		static const char* ToCString(const String::Utf8Value& value);

};

#endif