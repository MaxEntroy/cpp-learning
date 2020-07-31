#include <iostream>
#include <map>
#include <vector>

#include "build64_release/proto/doc_info.pb.h"

void MakeReq(foo::Req* req);

void ShowReq(const foo::Req& req);

void TruncReq(foo::Req* req, std::vector<foo::DocInfo>& doc_list);

void AppendReq(foo::Req* req, const std::vector<foo::DocInfo>& doc_list);

void TestMap(std::map<int, int>* counter, int id);

int main(void) {
  // foo::Req req;

  // MakeReq(&req);

  // ShowReq(req);

  // std::vector<foo::DocInfo> doc_list;
  // TruncReq(&req, doc_list);
  // std::cout << "after TruncReq" << std::endl;

  // ShowReq(req);

  // AppendReq(&req, doc_list);
  // std::cout << "after AppendReq" << std::endl;

  // ShowReq(req);

  std::map<int, int> counter;
  counter[101] = 1;

  TestMap(&counter, 101);
  TestMap(&counter, 102);

  return 0;
}

void MakeReq(foo::Req* req) {
  req->set_trace(101);

  foo::NewsInfo* news = req->mutable_newsinfo();
  news->set_sequence(101);

  foo::DocInfo* doc1 = news->add_doc_infos();
  doc1->set_doc_id("20200203A101");
  doc1->set_doc_type(1);

  foo::DocInfo* doc2 = news->add_doc_infos();
  doc2->set_doc_id("20200203V103");
  doc2->set_doc_type(2);
}

void ShowReq(const foo::Req& req) {
  std::cout << "trace: " << req.trace() << std::endl;
  const foo::NewsInfo& news = req.newsinfo();

  std::cout << "sequence: " << news.sequence() << std::endl;
  int sz = news.doc_infos_size();
  for(int i = 0; i < sz; ++i) {
    const foo::DocInfo& doc = news.doc_infos(i);
    std::cout << "doc id: " << doc.doc_id() << ", doc type: " << doc.doc_type() << std::endl;
  }
}

void TruncReq(foo::Req* req, std::vector<foo::DocInfo>& doc_list) {
  std::cout << "Start to truct req!" << std::endl;

  foo::NewsInfo* news = req->mutable_newsinfo();
  int sz = news->doc_infos_size();

  doc_list.reserve(sz);
  for(int i = 0; i < sz; ++i) {
    doc_list.push_back(news->doc_infos(i));
  }

  news->clear_doc_infos();
}

void AppendReq(foo::Req* req, const std::vector<foo::DocInfo>& doc_list) {
  int sz = doc_list.size();
  for(int i = 0; i < sz; ++i) {
    if (doc_list[i].doc_type() == 1) {
      foo::NewsInfo* news = req->mutable_newsinfo();
      foo::DocInfo* doc = news->add_doc_infos();
      *doc = doc_list[i];
    }
  }
}

void TestMap(std::map<int, int>* counter, int id) {
  int cur = 0;
  if (counter->find(id) == counter->end()) {
    cur = (*counter)[id] = 1;
  }
  else {
    cur = ++(*counter)[id];
  }
  std::cout << cur << std::endl;
}
