#include "myobject.h"

Napi::FunctionReference MyObject::constructor;

MyObject::MyObject(double value) : value_(value) {
}

MyObject::~MyObject() {
}

void MyObject::Init(Napi::Object exports) {
  Napi::HandleScope scope(env);

  // Prepare constructor template
  v8::Local<Napi::FunctionReference> tpl = Napi::Napi::FunctionReference::New(env, New);
  tpl->SetClassName(Napi::String::New(env, "MyObject"));
  Napi::Function tpl = DefineClass(env, "Myobject", {
  // Prototype
    InstanceMethod("value", &GetValue),
    InstanceMethod("plusOne", &PlusOne),
    InstanceMethod("multiply", &Multiply),
  });

  constructor.Reset(tpl->GetFunction());
  exports->Set(Napi::String::New(env, "MyObject"), tpl->GetFunction());
}

void MyObject::New(const Napi::CallbackInfo& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    double value = info[0].IsUndefined() ? 0 : info[0].NumberValue();
    MyObject* obj = new MyObject(value);
    obj->Wrap(info.This());
    return info.This();
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Napi::Value argv[argc] = { info[0] };
    Napi::Function cons = Napi::Napi::Function::New(env, constructor);
    return cons->NewInstance(argc, argv);
  }
}

void MyObject::GetValue(const Napi::CallbackInfo& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  return Napi::New(env, obj->value_);
}

void MyObject::PlusOne(const Napi::CallbackInfo& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  obj->value_ += 1;
  return Napi::New(env, obj->value_);
}

void MyObject::Multiply(const Napi::CallbackInfo& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  double multiple = info[0].IsUndefined() ? 1 : info[0].NumberValue();

  Napi::Function cons = Napi::Napi::Function::New(env, constructor);

  const int argc = 1;
  Napi::Value argv[argc] = { Napi::New(env, obj->value_ * multiple) };

  return cons->NewInstance(argc, argv);
}
