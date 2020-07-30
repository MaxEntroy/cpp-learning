#include <iostream>

#include "build64_release/proto/doc_info.pb.h"

void MakeDocInfo(foo::DocInfo* docinfo);

void ShowDocInfo(const foo::DocInfo& docinfo);

void TruncDoc(foo::DocInfo* docinfo);

int main(void) {
  foo::DocInfo doc_info;

  MakeDocInfo(&doc_info);
  ShowDocInfo(doc_info);

  TruncDoc(&doc_info);
  ShowDocInfo(doc_info);
  return 0;
}

void MakeDocInfo(foo::DocInfo* docinfo) {
  foo::Doc* doc1 = docinfo->add_doc_list();
  doc1->set_doc_id("20200302A101");
  doc1->set_doc_type(1);

  foo::Doc* doc2 = docinfo->add_doc_list();
  doc2->set_doc_id("20200302V101");
  doc2->set_doc_type(2);
}

void ShowDocInfo(const foo::DocInfo& docinfo) {
  int sz = docinfo.doc_list_size();
  for(int i = 0; i < sz; ++i) {
    const foo::Doc& a_doc =  docinfo.doc_list(i);
    std::cout << "doc id: " << a_doc.doc_id() << ", doc type: " << a_doc.doc_type() << std::endl;
  }
}

void TruncDoc(foo::DocInfo* docinfo) {
  foo::DocInfo docinfo_candidate = *docinfo;

  docinfo->clear_doc_list();
  int sz = docinfo_candidate.doc_list_size();
  for(int i = 0; i < sz; ++i) {
    const foo::Doc& a_doc = docinfo_candidate.doc_list(i);
    if (a_doc.doc_type() == 1) {
      foo::Doc* doc = docinfo->add_doc_list();
      *doc = std::move(a_doc);
    }
  }
}
