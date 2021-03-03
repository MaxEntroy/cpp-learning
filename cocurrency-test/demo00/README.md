### Thread-Safe Initialization of Data

- The function call_once in combination with the once_flag
  - By using the std::call_once function, you can register all callable
  - The std::once_flag ensures, that only one registered function will be invoked

参考<br>
[Thread-Safe Initialization of Data](https://www.modernescpp.com/index.php/thread-safe-initialization-of-data)