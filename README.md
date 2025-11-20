## AVL-Tree vs std::set 

### Project tree

```text
tree
├── avl
|   ├── tests
|   |   ├── test_1.in
|   |   ├── test_1.out
|   |   ├── ...
|   |   ├── ...
│   ├── run_tests.sh
│   ├── CMakeLists.txt
│   ├── tree.hpp
│   └── main.cpp
├── benchmark
|   ├── main.cpp
│   ├── CMakeLists.txt
│   ├── benchmark.hpp
└── set
    ├── CMakeLists.txt
    └── main.cpp
```
### About project
In this project, I implemented my own AVL tree and a method that allows me to quickly find the number of elements in a given range using the tree. 
I also implemented it using std::set and compared their performance.
### Run
#### Clone repository
```
git clone ...
cd tree
```
[TYPE] = avl | set | benchmark

#### Choose folders with type of cache 
```
cd [TYPE]
```
#### Build
```
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
```
#### Run
```
cd build
./[TYPE]
```

