# Chapter 4 - Designing Professional C++ Programs

Before writing a single line of code, you should design your program. A **program design**, also called **software design** is the specification of the architecture that you will implement to fulfill all functional and non-functional requirements of the program. Simply put, it is how you intend to structure and write the program. When starting a new program, the first step is to analyse the requirements. This usually involves discussing with appropriate *stakeholders*, if any. The result of this are *functional* requirements stating exactly what this code *has to do*, without explaining how it has to do it, and *non-functional* requirements which specify how the final system *should be*, for example performance, security, extensibility, and portability requirements.

These requirements guide the design of the program. Generally, you should write your design in the form of a design document. A design documents typically contains two things: gross subdivision of the program into subsystems specifying the communication (interfaces and dependences); and the details of each system specifting the class hierachies, data structures and algorithms. Diagrams and tables are used to visualise class hierarchies as well as the interaction between subsystems. The Unified Modeling Languate (UML) is the industry standard for such diagrams.

As program evolves, the requirements as well as the constraints become even clearer and more concrete. You should always update your design documents to keep it up-to-date with new changes to program structure.

## The Importance of Programming Design

- It allows teams to work on different part of the project since there is a design document for all team members to follow
- It enables newcommers to the project get up to speed with the program structure.
- It helps you to determine how everything fits together before you code. Jumping into programs without a design results in hacky solutions when you hit roadblocks due to a constraint you didn't think of beforehand.

## Designing for C++

The C++ languague provides various features which you must be aware of when design a program that must be written in it:
- *Objec-oriented capabilities*: Allows you to include class hierachies, interfaces and object interactions.
- *Multi-paradigm*: Supports other programming paradigms such as procedural programming.
- *Generic and Reusable code*: C++ provides facilities like templates for generic programming and designing reusable codes.
- *Large Standard Library*: The rich STL prevents you from reinventing the wheels, and allows you to focus on the specific needs of your requirements instead of writing boilerplate codes.
- C++ also accomdates various *design patterns*.

## Two Rules for Your Own C++ Designs

When designing your own C++ programs, there are two fundamental design rules to follow: **abstraction** and **reuse**

### Abstraction

Abstraction is the separation of internal implementation from its external interface. A good example, is how we are able to operate technological devices such as televisions or cars, without understand the details of how these devices work. For example, you only need the ports, remote and screen etc, to use the TV, you don't need to learn how it paints the images on the screen. The internal implemenation of how it receives the signals, translates them and displays them can change, without affecting how use the remote, ports and screens.

Object-oriented programming, allows us to incorporate the same idea of abstraction in our program. We can expose the external behaviours and object can have, and hide the internal implementation of these behaviours. To achieve this, all class data members are made private and *getter* and *setters* are provided to offer controlled access to data members from outside the class.

The benefits of abstractions include:
- It allows you to change the underlying implementation without having to change the public interface.
- With getters and setters, you can implement extra steps such as sanity checks before data member is modified.
- During debugging, we can figure out what data is actually sent to or set from outside the class by putting breakpoints in getters and setters when using a debugger.

###  Reuse

Reuse prevents you from reinventing the wheel. It also implies avoiding duplicating a piece of code or algorithm. C++ provides templates that allow you to write general-purpose code that can be reused. When designing your program, it is recommended to seek out existing *design patterns* that solve a similar problem for your software design and reuse them.

**Reusing Existing Code**: Reusable code comes in form of:
- stand-alone functions or classes which you or a colleague has written in the past.
- libraries - collection of code that accomplish a specific task e.g. parsing XML, or handle a specific domain, such as networking, graphics, cryptography etc.
- frameworks - collection around which you design a program. The difference between a library and a framework is that your program *uses* a library, but *fits into* a framework.
- entire applications such as web-servers.

**NB**: An API (Application Programming Interface) is an interface to a library or body of code for a specific purpose. Thus, a library, or even a web server may expose an API to its functionalities.

#### Advantages

- You may not know how or be able to justify the time to write the code you need.
- Your designs will be simpler, and less robust.
- Libraries have been battle-tested in different platforms on different hardwares, operationg systems, operationg system versoin and so on.
- It is safer to reuse existing code written by experts in the domain e.g. networking or cryptography.
- Library code is constantly improving. You may not have time to update your library.

#### Disadvantages

- It involves an initial learning cost, which appears over and over again when a new person joins the team. For this reason, it is advised to choose widely used libraries when needed.
- Library code may not give you the exact functionality or performance you want.
- It introduces support issues as you may not guarantee the writer is available to fix bug or provide up-to-date features for the library.
- It also presents licensing issues. Before using a library, you should inspect licensing issues such disclosure of your own source code, redistribution fees, credit attribution, and development licenses.
- Upgrade to a new version of the library can cause problems. Similarly, your compiler version must be compatible with the library. Upgrading it might causes if the library does not yet support it.

#### Guidelines for Choosing a Library to Reuse

When choosing a library, you must inpsect the library to understand:
- its capabilities and limitations.
- its learning cost.
- its performance: Performance are usually described in big-O notation which the relative worst-case running time. From fastest to slowest, an algorithm can have the following complexity: constant $O(n)$, logarithmic $O(log n)$, linear $O(n)$, linear logarithmic $O(n log n)$, quadratic $O(n^2)$, polynomial $O(n^a)$, exponential $(2^n)$ time.
- platform limitations
- licensing
- support and where to find help

When you want to adopt a library, it is often a good idea to write a quick prototype to experiment whether the library actually solves your problem. It prevents you from wasting time incorporating the library into your own code. If this *prototype*, however, morphs into your final product, you should reorganise it properly to fit the program design.

### Open-Source Libraries

There are two major movements in the open-source community: 
- *free software* which allows the developers to examine, modify and redistribute the source code. The finished product based on this *free software* is not required to be available free of charge.
- *open-source software* in which the source code is available, and like *free software*, the product or library is not required to available without cost. The difference is that, open-source software is not required to give you freedom to use, modify and redistribute it. There are lot of licensing options available for open-sourcep projects including: GNU Public License (GPL), Boost Software License, Berkeley Software Distribution (BSD) License, MIT License, Apache License, different flavours of the Creative Commons (CC) License etc.