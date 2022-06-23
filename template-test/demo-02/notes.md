- 模板通用性
  - 我们通过version5的实现发现，在对模板就行实例化的时候，实例化的模板需要和实际调用参数所推到的类型匹配。
  - 这里一开始我的误解是，模板不通用。其实模板是通用的，只是实例化的时候，实参没有和实例化的模板匹配成功

- 通用模板的实现
  - an rvalue reference to a template type parameter (i.e., T&&) preserves the constness and lvalue/rvalue property of its corresponding argument.
  - we use forward to pass a function parameter that is defined as an rvalue reference to a template type parameter, which preserves the lvalue/rvalue nature of its given argument:
