#include <iostream>

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include "build64_release/proto/foo.pb.h"

void InitFoo(Foo* foo);

void ShowFoo(const Foo& foo);

template<class T>
bool GetScalarField(const google::protobuf::Message &message, const std::string& field, T& out);

int main(void) {
  Foo foo;
  InitFoo(&foo);

  int val = 0;
  std::string name;
  GetScalarField(foo, "grade", val);
  std::cout << name << std::endl;

  return 0;
}

void InitFoo(Foo* foo) {
  foo->set_grade(98);
  foo->set_name("kang");
}

void ShowFoo(const Foo& foo) {
  std::cout << "name: " << foo.name()
    << ", grade: " << foo.grade() << std::endl;
}

template<class T>
bool GetScalarField(const google::protobuf::Message &msg, const std::string& field_name, T& out) {
  const google::protobuf::Descriptor* des = msg.GetDescriptor();
  const google::protobuf::Reflection* ref = msg.GetReflection();

  if (!des || !ref) {
    return false;
  }

  const google::protobuf::FieldDescriptor* field = des->FindFieldByName(field_name);
  if (!field) {
    return false;
  }

  ::google::protobuf::FieldDescriptor::CppType type = field->cpp_type();
  switch(type) {
    case ::google::protobuf::FieldDescriptor::CPPTYPE_INT32: {
                                                               out = ref->GetInt32(msg, field);
                                                               break;
                                                             }

    case ::google::protobuf::FieldDescriptor::CPPTYPE_STRING: {
                                                                out = ref->GetString(msg, field);
                                                                break;
                                                              }
  }
  return true;
}
