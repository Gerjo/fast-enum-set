The quest for a set
=============

*This project is still a work in progress, consider this a sneek preview of results yielded thus far.*

A variant of the std::set, but optimized for integer and enum storage. Data is stored internally using bit fields, an approach also seen in the std::vector<bool> specialization. We will be using this set frequently inside our game loop logic, this means that otherwise neglectable figures such as "0.001", actually do bear impact performance.

First we evaluated int64_t and std::bitset, but we found that incompatibility with our existing enums and compile time upper bounds, were not satisfactory.

This left std::set and std::map for evaluation. Having studied their time complexity, it was quickly noted that there was indeed room for improvement. std::set and std::map are general purpose containers, quite possibly they sacrificed performance in favor of features. We are not bound by this constraint.

Below you will find some preliminary benchmarks. Operations within C++ are so fast, that most likely the internal clock isn't accurate enough, so compare these by their "big o", and not by actual time spend. All benchmarks below were run on the same computer, using GCC 4.7 and a performance oriented build. Once the EnumSet is finalized, the benchmark will be made more accurate, and a multiple operating system evaluation will be hold.

The X-axis represents size of the set, Y-axis indicates the time spend. Higher Y values indicate worse performance. 

![logo](https://github.com/Gerjo/fast-enum-set/blob/master/images/e.png?raw=true)

Above: We used a fixed-seed, so each type of collection was presented with the same values to store.

![logo](https://github.com/Gerjo/fast-enum-set/blob/master/images/f.png?raw=true)

Above: Compared with the random numbers insert test, the performance here is so much worse b.c. of the nature of binary trees, we're clearly hitting the "worse case" here. EnumSet itself is not affected by this behaviour.

![logo](https://github.com/Gerjo/fast-enum-set/blob/master/images/a.png?raw=true)

Above: This is what matters. The std containers are already very fast, simply put, EnumSet is even more faster than fast.

![logo](https://github.com/Gerjo/fast-enum-set/blob/master/images/d.png?raw=true)

Above: Emptying the collection, we don't do this frequently, so performence is no issue. Nonetheless, this is still lightning fast.

![logo](https://github.com/Gerjo/fast-enum-set/blob/master/images/b.png?raw=true)

Above: Unless you make a lot of sets on the fly, this isn't too important.

![logo](https://github.com/Gerjo/fast-enum-set/blob/master/images/c.png?raw=true)

Above: Interestingly enough, the destructor is significantly slower than the clear method of the std containers. Unsure what causes this. 

To be continued.
