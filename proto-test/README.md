### 实践

- demo-03

demo-03在demo-02的基础上进行了优化，同样的优化，我们在线上获得10ms+的性能收益。主要是避免了大量的拷贝。尤其是当user define type时提升明显

```cpp
void TruncReq(foo::Req* req) {
  std::cout << "Start to truct req!" << std::endl;

  foo::NewsInfo* news = req->mutable_newsinfo();
  int sz = news->doc_infos_size();

  std::vector<foo::DocInfo> candidates;
  candidates.reserve(sz);
  for(int i = 0; i < sz; ++i) {
    candidates.emplace_back(news->doc_infos(i));
  }

  news->clear_doc_infos();

  for(const auto& doc : candidates) {
    if (doc.doc_type() == 1) {
      foo::DocInfo* a_doc = news->add_doc_infos();
      *a_doc = doc;
    }
  }
}

void TruncReq1(foo::Req* req) {
  std::cout << "Start to truct req!" << std::endl;

  ::google::protobuf::RepeatedPtrField<foo::DocInfo> candidates;
  candidates.Swap(req->mutable_newsinfo()->mutable_doc_infos());

  for (auto& doc : candidates) {
    if (doc.doc_type() == 1) {
      foo::DocInfo* a_doc = req->mutable_newsinfo()->add_doc_infos();
      a_doc->Swap(&doc);
    }
  }
}
```

1. 使用了大量的Swap操作来避免copy
2. copy semantics的标准语义是右值不变，将右值赋值给左值。但是实践中，经常会出现，不care右值的情形，此时move/swap操作可以优化此时拷贝对象的性能