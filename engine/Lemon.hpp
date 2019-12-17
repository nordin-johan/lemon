#ifndef LEMON
#define LEMON

#include "Environment.hpp"

using v8::TryCatch;
using v8::Message;
using v8::Local;
using v8::Value;
using v8::Script;
using v8::ScriptOrigin;
using v8::NewStringType;
using v8::MaybeLocal;

class Lemon : public Environment {

	protected:

		virtual void ReportException(TryCatch* try_catch) final;
		virtual bool ExecuteString(Local<String> source, const char* filename) final;
		virtual MaybeLocal<String> ReadFile(const char* filename) final;
		virtual bool RunJsFromFile(const char* filename);
		
};

#endif