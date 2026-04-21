PROFILE := "Release" 
# Possible values: Debug, Release

build:
    #!/bin/bash
    rm -rf ./build
    mkdir -p ./build
    cd ./build && cmake -DCMAKE_BUILD_TYPE={{PROFILE}} ../ && make

run: build
    #!/bin/bash
    rm -rf ./run
    mkdir -p ./run
    LOG_FILE="./run/run.log" LOG_DEST="file" LOG_LEVEL="DEBUG" ./build/gobang