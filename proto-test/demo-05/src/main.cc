#include <iostream>
#include <type_traits>
#include <google/protobuf/message.h>
#include "build64_release/proto/foo.pb.h"

namespace goo_proto = ::google::protobuf;

void InitFoo(Foo* foo);
void ShowFoo(const Foo& foo);

const std::string& GetStringRef(const goo_proto::Message& msg, const std::string& field_name) {
  auto descriptor = msg.GetDescriptor();
  auto field_descriptor = descriptor->FindFieldByName(field_name);
  auto reflection = msg.GetReflection();

  return reflection->GetStringReference(msg, field_descriptor, nullptr);
}

void TestGetStringRef() {
  Foo foo;
  InitFoo(&foo);

  const std::string& name = GetStringRef(foo, "name");
  std::cout << name << std::endl;
}

bool GetStringPtr(const goo_proto::Message& msg, const std::string& field_name, const std::string** ptr) {
  auto descriptor = msg.GetDescriptor();
  auto field_descriptor = descriptor->FindFieldByName(field_name);
  auto reflection = msg.GetReflection();

  *ptr = &(reflection->GetStringReference(msg, field_descriptor, nullptr));
  return true;
}

void TestGetStringPtr() {
  Foo foo;
  InitFoo(&foo);

  const std::string* name = nullptr;
  GetStringPtr(foo, "name", &name);
  std::cout << *name << std::endl;
}

const goo_proto::Message& GetMessageRef(const goo_proto::Message& msg, const std::string& field_name) {
  auto descriptor = msg.GetDescriptor();
  auto field_descriptor = descriptor->FindFieldByName(field_name);
  auto reflection = msg.GetReflection();

  return reflection->GetMessage(msg, field_descriptor);
}

void TestGetMessageRef() {
  Foo foo;
  InitFoo(&foo);

  const goo_proto::Message& msg = GetMessageRef(foo, "fam");
  const std::string* father = nullptr;
  GetStringPtr(msg, "father", &father);
  std::cout << *father << std::endl;
}

bool GetMessagePtr(const goo_proto::Message& msg, const std::string& field_name, const goo_proto::Message** ptr) {
  auto descriptor = msg.GetDescriptor();
  auto field_descriptor = descriptor->FindFieldByName(field_name);
  auto reflection = msg.GetReflection();

  *ptr = &(reflection->GetMessage(msg, field_descriptor));
  return true;
}

void TestGetMessagePtr() {
  Foo foo;
  InitFoo(&foo);

  const goo_proto::Message* msg_ptr = nullptr;
  GetMessagePtr(foo, "fam", &msg_ptr);

  const std::string* father = nullptr;
  GetStringPtr(*msg_ptr, "father", &father);
  std::cout << *father << std::endl;
}

template <typename Param>
struct ProtoFuncRef
{
    static constexpr void* GetFieldFuncRef = nullptr;
};

template <>
struct ProtoFuncRef<std::string>
{
  static constexpr auto GetFieldFuncRef = &goo_proto::Reflection::GetStringReference;
};

template <>
struct ProtoFuncRef<goo_proto::Message>
{
  static constexpr auto GetFieldFuncRef = &goo_proto::Reflection::GetMessage;
};

template<typename ValueType>
bool GetValuePtr(const goo_proto::Message& msg, const std::string& field_name, const ValueType** pptr) {
  auto descriptor = msg.GetDescriptor();
  auto field_descriptor = descriptor->FindFieldByName(field_name);
  auto reflection = msg.GetReflection();

  if (!descriptor || !field_descriptor || !reflection) {
    return nullptr;
  }

  try {
    *pptr = &((reflection->*(ProtoFuncRef<ValueType>::GetFieldFuncRef))(msg, field_descriptor, nullptr));
  } catch(std::exception& e) {
    return false;
  }

  return true;
}

void TestGetValuePtr() {
  Foo foo;
  InitFoo(&foo);

  //const std::string* name = nullptr;
  //if(!GetValuePtr(foo, "fam", &name)) {
  //  std::cerr << "Error" << std::endl;
  //}

  const goo_proto::Message* msg = nullptr;
  GetValuePtr(foo, "fam", &msg);

  const Family* fam = dynamic_cast<const Family*>(msg);
  if (fam) {
    std::cout << fam->father() << std::endl;
  }

  const std::string* id = nullptr;
  GetValuePtr(foo, "id", &id);
  std::cout << *id << std::endl;

  const std::string* reason_flag = nullptr;
  GetValuePtr(foo, "reason_flag", &reason_flag);
  std::cout << *reason_flag << std::endl;

  //const std::string* father = nullptr;
  //GetValuePtr(*msg, "father", &father);
  //std::cout << *father << std::endl;
}

int main(void) {
  //TestGetStringRef();
  //TestGetStringPtr();
  //TestGetMessageRef();
  //TestGetMessagePtr();
  TestGetValuePtr();
  return 0;
}

void InitFoo(Foo* foo) {
  foo->set_grade(98);
  foo->set_name("kang");
  foo->set_total(100);
  foo->set_id("20200802A301");
  foo->set_reason_flag("ICF");

  Family* fam = foo->mutable_fam();
  fam->set_father("dad");
  fam->set_mother("mom");
}

void ShowFoo(const Foo& foo) {
  std::cout << "name: " << foo.name()
    << ", grade: " << foo.grade()
    << ", total: " << foo.total() << std::endl;
  std::cout << "father: " << foo.fam().father() << ", mother: " << foo.fam().mother() << std::endl;
}
