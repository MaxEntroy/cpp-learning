#include <iostream>
#include <type_traits>
#include <google/protobuf/message.h>
#include "build64_release/proto/foo.pb.h"

void InitFoo(Foo* foo);
void ShowFoo(const Foo& foo);

namespace goo_proto = ::google::protobuf;

template <typename Param>
struct ProtoFunc
{
    static constexpr void* GetFieldFunc = nullptr;
};

template <>
struct ProtoFunc<goo_proto::int32>
{
  static constexpr auto GetFieldFunc = &goo_proto::Reflection::GetInt32;
};

template <>
struct ProtoFunc<goo_proto::int64>
{
  static constexpr auto GetFieldFunc = &goo_proto::Reflection::GetInt64;
};

template <>
struct ProtoFunc<goo_proto::string>
{
  static constexpr auto GetFieldFunc = &goo_proto::Reflection::GetString;
};

template<typename ValueType>
bool GetValue(const goo_proto::Message& msg, const std::string& field_name, ValueType* out) {
  auto descriptor = msg.GetDescriptor();
  auto field_descriptor = descriptor->FindFieldByName(field_name);
  auto reflection = msg.GetReflection();

  try {
    *out = (reflection->*(ProtoFunc<ValueType>::GetFieldFunc))(msg, field_descriptor);
  } catch (const std::exception& e) {
    return false;
  }
  return true;
}

int main(void) {
  Foo foo;
  InitFoo(&foo);

  goo_proto::int32 val = 0;
  GetValue(foo, "grade", &val);
  std::cout << val << std::endl;

  goo_proto::string str;
  bool ret = GetValue(foo, "name", &str);
  if (!ret) {
    std::cerr << "GetValue failure.";
  }
  std::cout << str << std::endl;

  ShowFoo(foo);
  return 0;
}

void InitFoo(Foo* foo) {
  foo->set_grade(98);
  foo->set_name("kang");
  foo->set_total(100);
}

void ShowFoo(const Foo& foo) {
  std::cout << "name: " << foo.name()
    << ", grade: " << foo.grade()
    << ", total: " << foo.total() << std::endl;
}
