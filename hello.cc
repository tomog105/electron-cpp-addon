#include <nan.h>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>

char* MRubyHello() {
  mrb_state* mrb = mrb_open();
  if ( !mrb ) {
    /* handle error */
    printf("ERROR: Unable to open mRuby: %s\n", strerror(errno));
    exit(-1);
  }
  errno = 0;

  mrb_load_string(mrb, "p 'Welcome to the mRuby World!!'");

  mrb_value value = mrb_load_string(mrb, "'world'");

  if ( !mrb_string_p(value) ) {
    printf("ERROR: Returned value is not a String type. mrb_vtype: %u\n", mrb_type(value));
    exit(-1);
  }

  char* str = mrb_str_to_cstr(mrb, value);

  mrb_close( mrb );
  mrb = NULL;

  return str;
}

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  info.GetReturnValue().Set(Nan::New(MRubyHello()).ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("hello").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(hello, Init)
