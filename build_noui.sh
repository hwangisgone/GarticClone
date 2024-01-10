set -x # 
rootpath=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd) # Deal with \r
rm debug/db/network.db
rm debug/src/html_const.cpp #
cmake -S $rootpath -B debug/ -DCMAKE_BUILD_TYPE=Testing && cmake --build debug/ #