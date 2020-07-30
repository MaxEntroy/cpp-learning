#include <iostream>

#include "build64_release/proto/doc_info.pb.h"

void MakeReq(foo::Req* req);

int main(void) {
  foo::Req req;

  MakeReq(&req);

  return 0;
}

void MakeReq(foo::Req* req) {
  req->set_trace(101);

  foo::NewsInfo* news = req->mutable_newsinfo();
  news->set_sequence(101);
}

