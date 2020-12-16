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

- demo-07

原来测试这个例子是想说明outer pb dtor的问题，即compile time正常，但是run time异常。后来发现也不行，确实需要linking。
但是我也得到了解释之前问题的原因。之前看的的现象是，使用BUILD编译时，发现library编译没有问题，但是run time error.

这个例子也发现了原因

1. cc_library编译为.a，.a的编译过程，没有进行到linking.
2. A static library is basically a set of object files that were copied into a single file with the suffix .a.

进一步来说，.a是一堆独立的.o集合。而.o则是```g++ -c xx.c```形成，所以这部分并没有linking. 而最终的.a则是```ar rcs libxxx.a xxx1.o xxx2.o```，只是简单的利用ar命令进行归档
