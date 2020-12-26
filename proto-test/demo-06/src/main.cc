#include "proto/foo.pb.h"

void InitFoo(Foo* foo);
void ShowFoo(const Foo& foo);

int main(void) {
  Foo foo;
  InitFoo(&foo);
  ShowFoo(foo);
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

  Family* a_fam = foo->add_family_list();
  a_fam->set_father("Jam");
  a_fam->set_mother("Lilly");

  Family* b_fam = foo->add_family_list();
  b_fam->set_father("Jay");
  b_fam->set_mother("Jolin");
}

void ShowFoo(const Foo& foo) {
  std::cout << "name: " << foo.name()
    << ", grade: " << foo.grade()
    << ", total: " << foo.total() << std::endl;
  std::cout << "father: " << foo.fam().father() << ", mother: " << foo.fam().mother() << std::endl;

  using FamilyList = google::protobuf::RepeatedPtrField<Family>;

  const FamilyList& family_list = foo.family_list();
  for(int i = 0; i < family_list.size(); ++i) {
    std::cout << "father:" << family_list[i].father() << std::endl;
    std::cout << "mother:" << family_list[i].mother() << std::endl;
  }
}
