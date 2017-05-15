#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <napi.h>
#include <uv.h>

class MyObject : public Napi::ObjectWrap<MyObject> {
 public:
  static void Init(Napi::Object exports);

 private:
  explicit MyObject(double value = 0);
  ~MyObject();

  static void New(const Napi::CallbackInfo& info);
  static void GetValue(const Napi::CallbackInfo& info);
  static void PlusOne(const Napi::CallbackInfo& info);
  static void Multiply(const Napi::CallbackInfo& info);
  static Napi::FunctionReference constructor;
  double value_;
};

#endif
