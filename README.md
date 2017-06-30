# Compile-Time Matrix in C++

**Description**

A compile-time matrix application with basic operator overloading and elementary algorithms for functionality, using a dynamic 2D array, and implemented with templates. Suitable for data storage and operations and further numerical algorithm addition.


**Dependencies**

No higher level STL libraries are used, nor 3rd party libraries. 

**Performance**

I used primitive types to build the matrix in order to improve efficiency. Higher-level STL libraries, such as std::vector or std::array, might make the code more neat and comprehensive, but are slightly heavier in performance, as they are classes by themselves. 

As for the matrix multiplication algorithm, is the non-sophisticated O(n^3) version of it. Ideally, you can extend the functionality to use Strassen's algorithm and drop the bound to O(n^2.8) instead. 

**Applications**

Matrices are useful to store and operate on data. For example, you can use the code in an application where you need to store the daily prices of several stocks, the rates of returns, their variances, or even to record sales from stores in several locations. 

The code provided here, however, provides only the basic functionality, and serves as an academic token for STEM students who work on coding. 
