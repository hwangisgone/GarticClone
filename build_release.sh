set -x ; cd ui && npm run build && cd .. ; cd build ; rm release/src/html_const.cpp ; cmake -S .. -B release/ -DCMAKE_BUILD_TYPE=Release && cmake --build release/