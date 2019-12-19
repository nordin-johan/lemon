#include "Lemon.hpp"

void Lemon::CreateGlobalMethod(const char* methodname, void (*callback)(const FunctionCallbackInfo<Value>& args)) {

    this->GetGlobal()->Set(
        String::NewFromUtf8(this->GetIsolate(), methodname, NewStringType::kNormal).ToLocalChecked(),
        FunctionTemplate::New(this->GetIsolate(), callback)
    );

}

ObjectCreator Lemon::CreateGlobalObject(const char* objectname) {

    ObjectCreator objectCreator(this->GetIsolate(), objectname);
    return objectCreator;

}

MaybeLocal<String> Lemon::ReadFile(const char* filename) {

    FILE* file = fopen(filename, "rb");

    if (file == NULL) 
        return MaybeLocal<String>();

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    char* chars = new char[size + 1];
    chars[size] = '\0';

    for (size_t i = 0; i < size;) {

        i += fread(&chars[i], 1, size - i, file);

        if (ferror(file)) {
            fclose(file);
            return MaybeLocal<String>();
        }

    }

    fclose(file);

    MaybeLocal<String> result = String::NewFromUtf8(
        this->GetIsolate(), chars, NewStringType::kNormal, static_cast<int>(size)
    );

    delete[] chars;
    return result;

}

bool Lemon::ExecuteString(Local<String> source, const char* filename) {

    TryCatch try_catch(this->GetIsolate());

    ScriptOrigin origin(String::NewFromUtf8(this->GetIsolate(), filename, NewStringType::kNormal).ToLocalChecked());
    Local<Script> script;

    if (!Script::Compile(this->GetIsolate()->GetCurrentContext(), source, &origin).ToLocal(&script)) {

        Lemon::ReportException(&try_catch);
        return false;

    } else {

        Local<Value> result;

        if (!script->Run(this->GetIsolate()->GetCurrentContext()).ToLocal(&result)) {

            assert(try_catch.HasCaught());
            Lemon::ReportException(&try_catch);
            return false;

        } else {

            assert(!try_catch.HasCaught());
            return true;

        }

    }

}

bool Lemon::RunJsFromFile(const char* filename) {

    Local<String> source;
    
    if (!Lemon::ReadFile(filename).ToLocal(&source))
        return false;

    if (!Lemon::ExecuteString(source, filename)) 
        return false;

    return true;

}

void Lemon::ReportException(TryCatch* try_catch) {

    String::Utf8Value exception(this->GetIsolate(), try_catch->Exception());

    const char* exception_string = StaticHelpers::ToCString(exception);
    Local<Message> message = try_catch->Message();

    if (message.IsEmpty())
        fprintf(stderr, "%s\n", exception_string);

    else {

        String::Utf8Value filename(this->GetIsolate(),
        message->GetScriptOrigin().ResourceName());

        const char* filename_string = StaticHelpers::ToCString(filename);

        int linenum = message->GetLineNumber(this->GetIsolate()->GetCurrentContext()).FromJust();
        fprintf(stderr, "%s line %i: %s\n", filename_string, linenum, exception_string);

        String::Utf8Value sourceline(
            this->GetIsolate(), 
            message->GetSourceLine(this->GetIsolate()->GetCurrentContext()).ToLocalChecked()
        );

        const char* sourceline_string = StaticHelpers::ToCString(sourceline);
        fprintf(stderr, "%s\n", sourceline_string);

        int start = message->GetStartColumn(this->GetIsolate()->GetCurrentContext()).FromJust();
        for (int i = 0; i < start; i++)
            fprintf(stderr, " ");

        int end = message->GetEndColumn(this->GetIsolate()->GetCurrentContext()).FromJust();
        for (int i = start; i < end; i++)
            fprintf(stderr, "^");

        fprintf(stderr, "\n");

    }

}