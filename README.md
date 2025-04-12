# Cryptography

## Overview of project  
> The idea behind this project is to showcase what I have learned from my cryptography course.
> I am doing this in conjunction with the Applied Mathematics 314 course at Stellenbosch University.
> The project is not for public use bot rather for personal practice to bothe practice my c/c++ skills and implementing and understading the algorithms in this course.

- Integer Modulo Spaces (implementing a datatype that uses a modulo subspace of the integers)
- Modulo arithmatic (including getting the modular inverse and powers)
- Polynomials 9implementing a simple polynomial datatype
- Polynomial modulo space
- Modulo polynomial arithmatic
- Diffie-Hawman key generation and exchange.
- Diffie-Hawmen code break.

## Compile
```bash
$ make clean # remove current object and executable files

$ make # compiled the project
$ make debug # compiles with DEBUG flag set
$ make verbose # compile with DEBUG and VERBOSE flags set

$ ./crypto # run project as compiled
```

### <IntMod.h\\>

This object simulates the integers module. It overloads most operations used for normal integers and thus can be used as such. In most cases it can be used in conjunction with integers, but this should be avoided. Fos simplicity and ease of use there is way to set the devisor statically. This is useful when you have a whole range of code that would be in the same modulo space.

Furthermode the class has implementations for both power and devision. It can do this using ether of the 2 algorithms (Left-to-Right or Right-to-Left) for power and Eulers Extended Algorithm to get the modular inverse. With these 2 approaches it is easy to calculate both positive and negative powers and also division.

> [NOTE] This function is still in the implementation fase and thus some functionality may be buggy or not implemented as of yet. I am planning on making this object as complete as possible.

#### Use
```cpp
IntMod::setDefaultDivisor(8); // Set default devisor for all default initilizations until default is changed
IntMod a(5); // Initialize with a specified default devisor (devisor must be set beforehand)
IntMod b(5, 7); // Initialize with value 5 and divisor 7, sets default to 7
```

### <Helper.h\\>

This file has some miscelaneous functions used in the project. A brief overview of the functions are given below.

> **<u>euclidAlgo()</u>**
> - this function uses the *Euclidean Algorithm* to determine the gcd between 2 elements. 
> - It is used to find out if 2 values are co prime. 
> - If they are co prime then their gcd would be 1.
> 
> **<u>extendedEuclidAlgo()</u>**
> - This function is an *Extended* version of the *Euclidean Algorithms*. 
> - It not only determines the gcd between 2 numbers but in addition also x, and y such that a\*x + b\*y = d where d is the gcd of a and b. 
> - This is used to get the modular inverse of an element if a and b are co prime.
>
> **<u>isPrim()</u>**
> - This function determines if a number is prime.
> - It makes use of the *Miller Radin* test on a fixed iteration size set in the function.

### Tested

- [x] IntMod operator overloads
- [x] Poly normal implementation with \<int\> and \<IntMod\>
- [x] Euclidean Algorithms
- [x] isPrime
- [x] Modular Inverse, IntMod devisionm overload