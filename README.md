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

### IntMod

This object simulates the integers module. It overloads most operations used for normal integers and thus can be used as such. In most cases it can be used in conjunction with integers, but this should be avoided. Fos simplicity and ease of use there is way to set the devisor statically. This is useful when you have a whole range of code that would be in the same modulo space.

Furthermode the class has implementations for both power and devision. It can do this using ether of the 2 algorithms (Left-to-Right or Right-to-Left) for power and Eulers Extended Algorithm to get the modular inverse. With these 2 approaches it is easy to calculate both positive and negative powers and also division.

> [NOTE] This function is still in the implementation fase and thus some functionality may be buggy or not implemented as of yet. I am planning on making this object as complete as possible.