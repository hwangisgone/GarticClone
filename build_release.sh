set -x # 
rootpath=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd) # Deal with \r
cd $rootpath/ui && npm run build && cd $rootpath/build # 
rm debug/src/html_const.cpp #
cmake -S $rootpath -B release/ -DCMAKE_BUILD_TYPE=Release && cmake --build release/ #