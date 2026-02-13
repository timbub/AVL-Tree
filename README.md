## AVL-Tree vs std::set 

### About project
In this project, I implemented my own AVL tree and a method that allows me to quickly find the number of elements in a given range using the tree. 
I also implemented it using std::set and compared their performance.

### Run
#### Clone repository
```
git clone ...
cd AVL-Tree
```
#### Build
```
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
```
#### Run avl or set
```
cd build/[avl/set]
./[avl/set]
```
#### Run Benchmark
```
cd build/benchmark
./[b_avl/b_set]
```
