# Chapter 6 - Designing for Reuse

## The Reuse Philosophy

While designing a program, you should keep the following in mind:

- Write once, use often.
- Try to avoid code duplication.
- DRY - Don't Repeat Yourself.

## How to Design Reusable Code

Reusable code should fulfill two main goals:

- It should be general enoguh for slightly different purposes, or in different application.
- It should be easy to use.

The implications that the means by which the library is delivered to the clients is also important. You can deliver it as:
- source form: clients incorporate, compile and/or run them themselves.
- static libraries: clients link into their own applications.
- dynamic libraries: such as Dynamic Link Libraries `.dll` for Windows clients, or shared objects `.so` for Linux clients.

The specific means imposes certain constraints on how you design your code.

We now discuss how to design reusable code

### Use Abstraction

- Always spearate the *interface* from the *implementation*.
- Abstraction allows you to provide upgrades and fixes without requiring clients to change their use.

## Structure Your Code for Optimal Reuse

You should consider reuse from the beginning of your design to all levels (or components), i.e. from a single function, to a class, to entire libaries and frameworks. 

### Avoid combining unrelated or logically separate concepts:
Each component must should only accomplish a single task or group of related tasks. That is, when desigining a component, you must strive for *high cohesion*. This is also known as the **Single Responsibility Principle (SRP)**.

To do this, you should:

#### Divide your programs into logical subsystems: 

By doing this, you keep your subsystems discrete allowing them to be reused independently. This is known as *low coupling* i.e. a subsystem should not be tied with another. If a subsystem needs another subsystem for its functionality, it should be an internal implementation that needs not to be exposed to the client.

#### Use class hierarchies to separate logical concepts:

When your program needs to represent different but related concepts, you should use class hierarchies to represent the relationships between them. For example, assuming we have a `Car` class, and we wish to add a `Truck` class. We could inherit from the `Car`, but if we find ourselves overwriting all the properties and behaviours of the parent class, then a `Truck` might be logically different from a `Car`. We will have to remember to update or override new properties and behaviours added to the `Car` class. We could instead introduce a `Vehicle` class to represent the broad idea of a vehicle and let both `Car` and `Truck` classes to extend it. In the future, we might need to represent a self-driving car, then we could use a mixin class, but that would include self-driving features even when we don't need. We could use a `SelfDriving` template that accepts different `Vehicle` class and subclasses as class template argument to allow the client to represent a `SelfDriving<Car>` or `SelfDriving<Truck>` etc. While doing this introduces extra classes, we are able to represent these different but related ideas separately in a class hierarchy.

#### Use Aggregation to Separate Logical Concepts

As discussed before, when you can choose between a has-a and is-a relationship, go with the has-a relationship. For example, if you want to write a `FamilyTree` class to store members of a family. It makes more sense to let this class store a `Tree` data structure class and use it to store the family tree members, rather than making the `FamilyTree` class extend the `Tree` class. This is because, while a family tree is similar to a tree, it is not really a data structure like a `Tree`. Even though, inheritance (is-a relationship) makes our classes polymorphic, it can couple it with the parent class. With aggregation, we can choose another data structure to store the family members. We cannot do that easily with an is-a relationship as it would break the places where the `FamilyTree` structure was used as a `Tree`. Inheritance should only be used when the derived class is very similar logically to the base class. 

#### Eliminate User Interface Depedencies

When writing a library, you should separate data manipulation from the user interface. Avoid using any of the standard console I/O functionality directly in the application logic. If you need to show any message, you can provide custom classes or use exceptions. You should make little assumptions of which UI your program runs, and leave that responsibility to display data for the client code. If you do have to provide UI functionality that integrates seamlessly with your library, do that as a separate subsystem allowing the client code to opt in.

### Use Templates for Generic Data Structures and Algorithms

When designing data structures or algorithms that can store or operate upon different data types, use templates. A good example is the *The Standard Library Containers* that we have already seen.

There are other mechanism to write generic data structures. Previously, it was common to store `void *` pointers which represent pointers to any type, but these are not *type-safe*. Also you have to know the correct type in order to cast them back when you retrieve them as `void *` pointer from the data structure. Wrong cast can result in catastrophic result. C++17 provides the `std::any` class which uses the `void *` pointer under-the-hood but also keeps track of the stored type for type safety. Another option to write generic data structures is to use polymorphism. You write the data structures for the parent class, allowing derived class to be stored in it. As before, you have to *down cast* to the appropriate, more specific class.

Templates are type safe and are checked during compile times. But they can be complicated to implement and confusing to the unfamiliar. They are also susceptible to code bloat, though this isn't much of a problem nowadays.

Sometimes, templates and inheritance might both be good call for a problem. Use templates when you want to provide *identical* functionality (e.g. sorting algoritms, container structure) for *different* types. Use inheritance when you want to provide *different* behaviours for *related* types. Another difference is that templates provide compile-time polymorphism, while inheritance provides run-time polymorphism. Nonetheless, you can combine both: you can even write a class template that derives from a base class template.

### Provide Appropriate Checks and Safeguards

To design safe code, you must ensure they are used the way it is intended. There are two approaches to these:

- Design by contract: Here, you document the requirements for client code to use the code, and the responsibilities of the code. These are usually stated as:
    - preconditions: conditions the client code must satisfy before calling the function. For example, when using array notation to access an item from `std::vector` container, the index must be valid (since no bound checking is done).
    - postconditions: conditions that must be satisfied by the function when it has finished executing. For example, a sorting algorithms guarantees that after its execution, the input must be sorted.
    - invariants: conditions that must be satisfied during the whole execution of the function. For example, sorting functions typically satisfy some loop invariants, such as some portion of the input being sorted as it executes.
- Defensive programming: Here, yoyu design your code to be as a safe as possible: checking inputs, error checking, etc. For example the `at()` mwthod on the `std::vector` container gets the item at the specified index, but performs bound checking unlike the array notation and throws an exception if the index is invalid.

### Design for Extensibility

You should design your classes in such a way that they their behaviour can be extended without modifying its implementation. This is called the **Open/Closed Principle (OCP)** which states the your interfaces should be open for extension but closed for modification. This can be readily achieved using inheritance which allows the derived class to extend or override the parent class' behaviour without modifying it.

## Design Usable Interfaces

Designing reusable code also implies usable interfaces. This involves choosing what properties and member functions of a class to make `public`.

### Consider the Audience

The audience determines frequently you can iterate on your designs. When desigining for personal or internal use, you could have the freedom to change the interfaces until it reaches a stable one. For external customers, this might not be the case. The interface is expected to be stable, consistent and easy to use.

### Consider the Purpose

#### Application Programming Interface

Generally, APIs should be easy to use sometimes at the expense of flexibility. The external client does not need to be conversant with the internal working of your product to consume your APIs, so learning it should be simple. A good API ideally makes the *common* case easy and the *advanced/unlikely* case possible.

#### Utility Class or Library.

Utility classes or libraries should be more general to allow them to be used in a different application. When building a library e.g. a networking library for a game, for example, it should still be used for different purpose e.g. a web application.

#### Subsystem Interface

Subsytem interfaces should be discrete avoiding tight coupling. Each interface must be separated from the implementation. This allows for *mockability* in testing when you want to replace a certain implementation with a *mock* implementation so that you do not spend time or resources executing the actual implementation. It also allows for *flexibility*, allowing you to swap implementations easily, and sometimes, even at runtimes. Also, by designing the interface, other programmers can start working with it, while you work on the implementation.

#### Component Interface

Component interface typically classes within a subsystem should also follow similar rules as subsystem interfaces, even though they may not be exposed. They should perform only a single task, be discrete, follow the open/closed princple, and have their interfaces separated from the implementation.

### Design Interfaces that are Easy to Use

When designing interfaces, you should follow the KISS principle: keep it simple, stupid. You can do this by:

#### Follow Familiar Ways of Doing Things

Follow popular conventions since it is possible the user is already familiar with it. You should try your best to keep your *innovative solution* in the underlying implementation and expose common interface to the user.

#### Don't Omit Required Functionality

Include functionalities that clients may need even if their future uses might be unclear. For example, suppose you are writing a `Fraction` class, you have provided all the functionalities that is need to operate on this class, using familiar methods such operator overloading to allow them to be used as typical decimal fractions. Even though there are no obvious use case (which you have not handled) where the user might need to access the numerator and denominator differently, you should consider exposing them. However, you should be careful to not fall into speculative generality that might complicate the interface. Additionally, avoid letting client code to specify information that can be derived from the implementation as it might be annoying or open up the possiblity that the user does it incorrectly. For example, if your library requires a temporary file, there's no need making the clients specify it since it temporary, you could instead find a way to determine appropriate temporary file path and use it.

#### Present Uncluttered Interfaces

As you provide required functionality, do not go to the extreme of including every possible piece of functionality imaginable. Cars, for instance, have features that are rarely used, but it would be annoying if the car dashboard looked like an airplace cockpit.

A fat interface can be avoided by breaking the interface into several smaller ones. Also, if the interface is complex with several subsystem dependencies, you could use the *facade design pattern* to provide an easier interface(s) on top of the fat and/or complicated one(s).

#### Provide Documentation

Provide both external documentation as well as comments in the interfaces.

### Design General-Purpose Interfaces

#### Provide Multiple Ways to Perform the Same Functionality

To satisfy different needs, it is sometimes helpful to provide multiple ways perform the same functionality, but without leading to cluttered interfaces. Cars, again for instance, can be unlocked via remote control, or using a key. Similarly, the `std::vector` class provides array notation and `at()` member function to access the item at a specific index.

#### Provide Customisability

While you provide the same basic functionality to every client, you should give clients the ability to tweak slightly, e.g. turn off error logging. This can be done using *Dependency Injection*, an implementation of **Dependency Inversion Principle (DIP)**. For example, you can design your service to use an `ErrorLogger` interface. The implementation of the service can then inject a concrete `ErrorLogger` implementation which can be swapped easily by the client. You can do this through template parameters, and callbacks. For example, you could allow clients to set their own error-handling callbacks.

### Reconciling Generality and Ease of Use

The two goals of ease of use and generality sometimes appear to conflict since they are not mutually exclusive. Designing for one requires a trade-off for another. For example, you might need a graph data structure for two different programs: a map program to store cities; and a network simulator. You could write a generic graph class template, but that can make it clumsier and harder to use.

One way is to use **Interface Segregation Principle (ISP)** where you provde multiple separate interface. That is, from the previous example, you could provide the interface to the map, and another for the networking functionality which utilise this graph template class behind the scenes. This is similar to how the C++ Standard Library provides the `std::string` class which uses the `std::basic_string` class template under the hood. This makes common functionality easy to use, while still providing option for the more advanced general functionality.

## Designing a Successful Abstraction

Designing a successful abstractions requires both *experience* and *iteration*. Thus, you should strive to learn from existing abstractions and incorporate them in your own designs. Do not be afraid to change the abstraction when you realise that there is a way better approach, even when coding has begun. You just have to convince other programmers that this is the best approach. Always seek and respond to feedback on design, changing it when necessary and learning from mistakes.

## The SOLID Principle

Throughout the chapter, we discussed a number of the absic principles of object-oriented design. These are summarised in an easy-to-remember acronymn: SOLID


- S - Single Responsibility (SRP) - A single component should have a single, well-defined responsibilty and should not combine unrelated functionality.

- O - Open/Closed Principle (OCP) - A class should be open to extension, but closed for modification. This can accomplished using inheritance, templates, function overloading, and other customisation mechanisms.

- L - Liskov Substitution Principle (LSP) - You should be able to replace an instance of an object with an instance of a subtype of that object.

- I - Interface Segregation Principle (ISP) - Keep interfaces clean and simple. Prefer many smaller, well-defined single-responsiblity interfaces to broad, general-purpose interfaces.

- D - Dependency Inversion Principle (DIP) - Use interfaces to invert dependency relationships. This can achieved using dependency injection.

