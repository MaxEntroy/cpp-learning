package(default_visibility = ["//visibility:public"]); 

load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
  name = "ad_load_proto",
  srcs = [
    "ad_load.proto"
  ]
)

cc_proto_library(
  name = "ad_load_cc_proto",
  deps = [
    ":ad_load_proto"
  ]
)
