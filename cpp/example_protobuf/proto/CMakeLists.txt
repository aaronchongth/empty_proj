include_directories(${PROTOBUF_INCLUDE_DIR})
protobuf_generate_cpp(proto_src proto_header 
  example_msg.proto
)
add_library(proto ${proto_header} ${proto_src})
set_property(TARGET proto PROPERTY CXX_STANDARD_17)

