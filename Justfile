build:
    #!/bin/bash
    rm -rf ./build
    mkdir -p ./build
    cd ./build && cmake ../ && make

run: build
    #!/bin/bash
    ./build/gobang