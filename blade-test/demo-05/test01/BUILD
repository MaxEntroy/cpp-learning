cc_library(
  name = "foo",
  srcs = [
    "foo.cc"
  ],
  deps = [],
  defs = [
  ]
)

cc_binary(
  name = "main",
  srcs = [
    "main.cc"
  ],
  deps = [
    ":foo"
  ],
  defs = [
    "MYTEST"
  ]
)

cc_test(
  name = "foo_test",
  srcs = [
    "foo_test.cc",
  ],
  deps = [
    ":foo"
  ],
  defs = [
    "MYTEST"
  ]
)
