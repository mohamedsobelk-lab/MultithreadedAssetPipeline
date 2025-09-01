cmake_minimum_required(VERSION 3.20)
project(MultithreadedAssetPipeline)

set(CMAKE_CXX_STANDARD 20)

add_executable(AssetPipelineDemo
    Main.cpp
    AssetQueue.h
    Asset.h
)

target_compile_features(AssetPipelineDemo PRIVATE cxx_std_20)