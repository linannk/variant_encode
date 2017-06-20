cmake_minimum_required(VERSION 3.0)
project(VariantEncode C CXX)

file(GLOB Src_List *.cpp *.h)
add_executable(variant_encode ${Src_List})
