# Chapter 5 - Designing with Classes

## Am I Thinking Procedurally?

In a procedural language, like C, programs are divided into small pieces, each of which (ideally) accomplishes a single task. In procedural programming, we typically "What does the program do?". The answer to this question is a series of steps or procedures which represent the small pieces of tasks the code carries out. For example, suppose we wish to design a stock selection program. The program does the following:
- Obtain stock quotes from the Internet.
- Sorts this data by specific metrics.
- Performs analysis on the sorted data.
- Output list of buy and sell recommendations.
In procedural programming, we will have to implement functions that performs those tasks: `retrieveQuotes()`, `sortQuotes()`, `analyseQuotes()`, `outputRecommendations()`. These functions take appropriate arguments and can again ask what procedures the functions follow to carry out its tasks, thus breaking it again to even smaller pieces of code and so on.

## The Object-Oriented Philosophy

An object-oriented approach asks the question: "What real-world objects am I modelling?". These physical objects can be considered in terms of their classes, components, properties, and behaviours.

### Classes

A class describes objects which share certain characteristics. Classes are analogous, and in many classes equivalent to types. For example, strings are classes of values (or objects) which are made up of characters stored in a contiguous array of memory. Integers are classes of values (or numbers) which have no fractional parts. Similarly, we can have an *animal* class to denote the classes of things which have properties found in animals, and from our previous example, we can have a *stock quote* class which defines the abstract notion of what makes up a quote.

An object is an *instance* of a class. You can think of an instance as examples of things which belong to the class. For example, the numbers 4, -1, 0 belong to the *class* of integers; dog, cat, lion, all belong to the class of animals; and a specific quote, such as "current Microsoft stock quote" is an instance of the stock quote class.

### Components

These real world objects are also made up of other smaller things (or objects) called *components*. Animals have legs, eyes, etc, and a stock quote may have a price. The components, can themselves be classes of others things which can further have subcomponents. All items in this class are expected to have this component.

### Properties

An object, that is the specific instance of a class, differs from another object from the same class. Properties are what distinguish one object from another. For example, even though all animals have legs, the particular leg that a lion has differs from that of a dog. Similarly, while all stock quotes may have a name, the name differs from one stock quote instance to another.

### Behaviours

Behaviours tells us what the object can do or what can be done to it. For example, an animal can move; fruits can be eaten; and a stock quote can be sold or bought. From our previous example in procedural thinking, we can say that a stock quote object can analyse itself. This means that oftentimes, functions from procedural programming, are represented in object-oriented programming as behaviours that an object or class can have. These behaviours are implemented in *class member functions*.

## Class Relationships

### The Has-a Relationship

Classes engaged in a has-a relationship follow the pattern: A has B, or A contains B, where one class, in this case A, is a part of another, B. Components, as you may reason, generally represent a has-a relationships. This relationship can involve containing one object of a class (e.g. a zoo with an officer), or many objects of the same class (e.g. a zoo with monkeys). There are two types of has-a relationships:
- **Aggregation**: Here, the component objects can continue to live when the aggregator is destroyed. For example, imagine a zoo object that contains a bunch of objects. When the zoo is destroyed, perhaps because it went bankruput, the animal objects it contains are ideally not destroyed, rather they are moved to another zoo. The zoo in this case "aggregates" the animal objects, rather than "owning" it.
- **Composition**: In this case, the component objects are destroyed, when the object containing them is destroyed. For example, when a window object containing buttons is destroyed (e.g. closed), the buttons are expected to go (and be destroyed) with it, since the window displaying them is no more.

### The Is-a Relationship (Inheritance)

The is-a relationship follows the pattern: A is a B, or A is really quite a bit like B in cases where the relationship is not very straightforward. This relationship is such a fundamental concept of object-oriented programming (OOP) that it has many names: deriving, subclassing, extending, and inheriting. It is used when classes themselves share common characteristics that allow them to organised in hierachies. For example, we may define an `Animal` class for animals such as dogs, cats, lions, zebras. But we can also identify that the objects in the `Animal` class while they share *animal-like* characteristics also have common properties and behaviours between them. For example, we can have `DomesticAnimal` which have an extra behaviour that they can be petted. In that case, they may also have additional property such as pet name. The others may then be grouped as `WildAnimal` or just be created and referred directly as an `Animal`. Nevertheless, the `DomesticAnimal` is an `Animal`. Alternatively, depending on our problem scenario, we can have the hierarchy as `LandAnimal`, `SeaAnimal` and `AirAnimal` which while *inheriting* the basic properties and behaviours of an `Animal`, can have distinguishing ones such as the ability to `walk`, `swim`, and `fly` respectively, along with different properties that may play apart in their behaviours.

In cases, when it is not clear whether a relationship represents a has-a or an is-a, probably because both of them works, you should prefer has-a over is-a.

#### Inheritance Techniques

- Adding functionality - a derived class can augment its parent by adding additional functionality, such as `fly()`, `swim()`, or `walk()` from the previous example.
- Replacing functionality - we can replace or override the member function of a class entirely. From the same example, instead of introducing new functions, we can replace the `Animal` class `move()` member function with different implementations for the derived classes. So, we can make all animals *walk* by default, and then override them to *jump*, *fly* or *swim*.
- Adding properties - This new properties typically allow it to perform its distinguishing behaviours.
- Replacing properties - The derived class can also override the class properties. While C++ provides ways to do this, it is rarely appropriate as it hides the property from the base class. This means, that the base class can have a specific value for a property with a certain name, while the derived class can have another value for another property but with the same name. The result is that accessing the same property may give different values depending on whether it was accessed from the parent or child class.

### Polymorphism

Polmorhpism is the notion that objects that adhere to a standard set of properties and member functions can be used interchangeably. When we define a class, we describe a contract such that any object from that class is guaranteed to have the specific properties and member functions of that class. This allows different objects from the same class to be passed as argument to a function taking that class as a parameter. 

This idea also extends to base classes as well. As all derived classes still contain the properties and member functions of the parent class, the derived class objects can be used wherever the parent class object is required.

Polymorphism, therefore, allows us to treat objects from the same class, or classes extending from the same base class interchangeably. For example, in a zoo simulation, we can loop through the animals and ask them to move themselves by calling the `Animal` class `move()` member function, and the respective subclasses (`LandAnimal`, `SeaAnimal`, and `AirAnimal`) simply calls their version of the function, preventing us from handling each specific case, since we know that since they all extend from the `Animal` class they must have the `move()` member function.


### The Fine Line Between Has-a and Is-a

There are scenarios where there are no clear distinction between the has-a and is-a relationship.

For example, consider a class that represent associative array `AssociativeArray`. This class may have operations such as: 
- `set()` to assign a given key to a given value; and
- `get()` to get the value for a given key.
Here and as it is usually the case, setting an already existing key overrides the old value. But now we wish to build another version of this that allows us to set multiple values, say `MultiAssociativeArray`.
How do we model the relationship between `AssociativeArray` and `MultiAssociativeArray`? We can begin with inheritance since we can reason that a `MultiAssociativeArray` is indeed some variant of `AssociativeArray`. But the problem is that this variant is fundamentally different from the main feature of an associative array: a mapping of a key to a single value. As another example, we can reason that ice is just solid water, but it lacks some fundamental characteristics of water, such its ability to flow. For this inheritance relationship, we'll have to:
- override `set()` to check if a key already exists and either add it to a new collection, or retrieve the existing collection and add the new value to the collection.
- override `get()` to get the first item in the collection if it exists.
Notice that, we are overriding all the behaviours it inherited, and this is usually a tell-tale sign of bad inheritance: You cannot say you inherit behaviours from a class, and went along to override all the behaviours inherited. Apart from the fact that you did not benefit from the inheritance, it is essentially a totally different class that happens to (or is forced) to have the same function names, especially when you have to override any new method added to the parent function.
In this case, we can make the `MultiAssociativeArray` contain the `AssociativeArray` which it uses for the same implementation. If we really need both of them to be used interchangeably, then they can extend the same base class or implement the same interface. This new base class or interface dictates the common functionality they share.

The Liskov Substitution Principle (LSP), which states that you should be able to use a derived class instead of a base class without altering the behaviour. In this case, setting and getting a value are fundamentally different behaviour in both classes. When you call `get()` do you intend to get the last set value or all the values? When you call `set()` do you intend to set a key to a single value or add the values under a collection for the key. The behaviour in each are different preventing you from using them interchangeably without altering the behaviour, even though you may have succeeded in forcing them under the same interface.

### The Not-a Relationship

In OOP, the relationship between classes are considered from a *functional* point of view. That is, the classes have certain related properites or behaviours. This means that there are cases in which real-world hierarchies may not be applicable as class hierarchies. For example, in a typical company, we have the CEO at the top, the VP of sales and VP of Engineering next. The Sales Associate and Pre-Sales are under the VP of Sales. The Project Lead, on the other hand, answers to the VP of Engineering; and the Engineer, answers to the Project Lead. In code, this hierarchy cannot be useful since a VP of Sales is not a CEO even though in a typical company hierarchy tree, it may be drawn under it. None of the classes are related to each other directly, except maybe, since they are all Employees of the company.

### Hierarchies

Object-oriented hierarchies can model multilevel relationships. This relationship is entirely functional, and may not represent the actual real-world hierarchy that an expert in the field would approve of. For example, in the `Animal` subclasses: `LandAnimal`, `SeaAnimal`, `AirAnimal`. We can further have: `GrassEatingAnimal` and `MeatEatingAnimal` subclasses under `LandAnimal`. This is okay if it is suitable for our problem scenario even though a biologist might be disappointed looking at the hierarchy.

Ideally, a good object-oriented hierarch should accomplish the following:
- organise classes into meaningful functional relationships.
- supports code reuse by factoring common functionality to base classes.
- avoids having derived classes that override much of the parent's functionality, unless the parent is an abstract base class.

### Multiple Inheritance

In multiple inheritance, a class extends from more than one parent class. For example, we could instead, keep the `Animal` class but subdivide it into `BigAnimal` and `SmallAnimal`, and then introduce a `Mover` class which is subdivided into `Jumper`, `Walker`, `Swimmer` and also an `Eater` class subdivided into `Carnivore`, `Herbivore`, `FishEater`. A `Lion` class would then inherit from `Walker`, `Carnivore`, `BigAnimal`.

C++ explicitly supports multiple inheritance even though many languages such as PHP and Java, do not. While they can be useful, they can have many disadvantages. First, it complicates the hierarchy: subclasses have to derive from unrelated parents just to inherit their properties and behaviours. Second, it destroys an otherwise clean hierarchy. In the previous example, the base `Animal` class becomes less meaningful, as the properties and behaviours that an animal should have is now separated into different hierarchies. For example, to add the notion that some animals are `Jumper`s and also `Herbivore`, we will have to derive from both classes as those classes are standalone hierarchies. Third, implementing is complicated. The two base classes you are inheriting might have the same member function names leading in collision. Also, if you wanted to extend from two base classes that are themselves a derived class of a common base class (probably because you don't want the other subclasses of this base class), you need to worry about which implementation of the overriden member functions you inherit.

Many programming languages leave out multiple inheritance because it is usually avoidable. Languages like PHP introduce the concept of *traits* with clear overriding rules, so that a `Lion` class, for exmaple, can still be a `BigAnimal` and then have `Walker` and `Carnivore` traits. This traits are independent of an animal or any hierarchy, for example, a `Robot` class can use the `Walker` trait if it needs the functionality.

### Mixin Classes

A mixin class answers the question, "What else is this class able to do?" and the answer often ends with "-able". For example, if you want to represent the idea that some animals can be owned as a pet, you can introduce a `Pettable` mixin class with the behaviour "be pet". 

They are analogous to the idea of traits in PHP. In C++, one of the ways to implement a mxin class is syntactically just like multiple inheritance, but the semantics are different. You can think of mixin classes as a *shares-with* relationship. Thus, it allows reusing code without becoming the parent of the class. As another example, we can make an `Image` respond to mouse clicks by "mixing in" a `Clickable` mixin class. A `Button` class would also use this class, preventing us from making the `Image` become a `Button` just to inheriting the mouse click behaviours.