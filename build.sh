set -x
cd ui
npm run build
cd ../build
cmake ..
make