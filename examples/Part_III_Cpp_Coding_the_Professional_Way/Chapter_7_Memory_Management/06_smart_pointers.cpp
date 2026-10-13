#include <format>
#include <iostream>
#include <memory>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')

class Simple
{

    public:

        Simple()    { println("Simple created"); }
        ~Simple()   { println("Simple destroyed"); }

        void go() { println("go! go!! go!!!"); }

};

class Foo
{
    public:
        Foo(std::unique_ptr<int> data) : _data { std::move(data) } { }

    private:
        std::unique_ptr<int> _data;
};

class Bar : public std::enable_shared_from_this<Bar>
{

    public:
        Bar(int value) : _data { value } { }

        std::shared_ptr<Bar> getPointer() { return shared_from_this(); };
        // The implementation below is completely wrong!!! 
        // This creates independent `shared_ptr`s pointing to the same `this` object
        // each time it is invoked, and will lead to double deletion.
        // std::shared_ptr<Bar> getPointer() { return std::shared_ptr<Bar>(this); }


        int _data;
};

void leaky();
void couldBeLeaky();
void notLeaky();
void processData(Simple* simple);

int* my_alloc(int value);
void my_free(int* p);

void useResource(std::weak_ptr<Simple>& weakSimple);
std::unique_ptr<Simple> createUniquePtr();

using errorcode = int;
errorcode my_alloc1(int value, int** data) { *data = new int { value }; return 0; }
errorcode my_free1(int* data) { delete data; return 0; }

int main()
{

    // Smart Pointers

    // When (and if you will ever) you need to manage memory yourself,
    // you should use C++ smart pointers. There are several types of smart pointers.
    
    // - `std::unique_ptr` takes sole/unique ownership of a resource. When this
    //      smart pointer goes out of scope, it can safely free the referenced
    //      resource as it is the single owner of a resource.
    // - `std::shared_ptr` allows several of these smart pointers to partake in a shared
    //      ownership of the same resource. When such a smart pointer goes out of scope
    //      or is reset, it frees the referenced resource only if it's the last smart
    //      pointer referring to that resource.
    // Both standard smart pointers are defined in <memory>. By default, you should go
    // for `unique_ptr`, unless you really need to share the resource.
    // Also, you should never assign the result of a resource allocation to a raw
    // pointer! Always store it immediately in a smart pointer, or use other RAII classes.
    // An RAII (Resource Acquisition is Initialisation - a design technique) class takes 
    // ownership of a certain resource and handles its deallocation at the right time.

    // -- `unique_ptr`

    // This smart pointer has sole ownership of a resource and automatically frees it when 
    // this smart pointer is destroyed (for example when function returns or exceptions are
    // thrown) or reset. This frees the burden of remembering to free the resource.

    // See the function calls below for how to create unique smart pointer

    leaky();
    couldBeLeaky();
    notLeaky();

    // Unique smart pointers cannot be copied since they represent unique ownership.
    // Copying them would result in two unique pointers owning the same resource.
    // They can be moved nonetheless i.e. one unique pointer moves ownership of its
    // resource to another unique pointer.

    auto myIntSmartPtr { std::make_unique<int>(42) };
    Foo f { std::move(myIntSmartPtr) };

    // -- We can also store C-style array:

    auto myVariableSizedArray { std::make_unique<int[]>(10) }; // uses value initialisation

    myVariableSizedArray[1] = 123;  // supports array notation

    // NB: Prefer Standard Library containers anyways

    // -- Custom Deleters: `unique_ptr` uses the standard `new` and `delete` operators
    // to allocate and deallocate memory. You can specify your own allocation
    // and deallocation function using the `unique_ptr` constructor where you specify
    // the type of data to store and the type of the deallocation function as 
    // template argument and the allocated memory and the deallocation (deleter) function 
    // itself as constructor argument. Quite cumbersome!
    
    std::unique_ptr<int, decltype(&my_free)> myIntSmartPtr1 { my_alloc(42), my_free };
    println("myIntSmartPtr data: {}", *myIntSmartPtr1.get());

    // -- `shared_ptr`

    // Here, multiple instances of `shared_ptr` refer to the same resource, and 
    // make use of reference counting to know when to free the resource i.e.
    // when the last reference to the pointer goes out of scope.

    // Create a shared smart pointer using `std::make_shared()`
    // Use `make_shared_for_overwrite()` to use default initialisation instead
    // of the default value initialisation.
    auto mySimpleSmartPtr { std::make_shared<Simple>() };

    // A `shared_ptr` also supports `get()` and `reset()` functions, just like a
    // `unique_ptr` but not `release()`. Get the number of `shared_ptr` instances
    // sharing the same resource using `use_count()`. You can also specify a custom deleter.

    // cleaner syntax compared to `unique_ptr` version.
    std::shared_ptr<int> myIntSmartPtr2 { my_alloc(42), my_free }; 

    // Internally, the `shared_ptr` as implemented by the Standard Library uses
    // reference counting, a technique used to keep track of instances of a class 
    // or particular object (in this case, the smart pointer) in use. A counter is
    // incremented when the smart pointer is copied, and the new instance also
    // points to the same resource. The counter is decremented when a smart pointer
    // goes out of scope or is reset, and the resource is freed when the counter
    // drops to zero (since there are no other owners).
    // This solves the problem of double deletion as can be seen in the code below

    println("-- double deletion");

    Simple* mySimple1 { new Simple { } };
    Simple* mySimple2 { mySimple1 }; // make a copy of the pointer

    delete mySimple2; mySimple2 = nullptr;
    // delete mySimple1; mySimple1 = nullptr;  // double free

    println("-- pointer solves double deletion");

    auto smartPtr1 { std::make_shared<Simple>() };
    auto smartPtr2 { smartPtr1 }; // make a copy of the pointer

    println("-- any untracked raw pointer would cause problems");

    Simple* mySimple { new Simple { } };
    std::shared_ptr<Simple> smartPtr3 { mySimple }; // stores the shared pointer
    // std::shared_ptr<Simple> smartPtr4 { mySimple }; // gets its own pointer directly, not from shared pointer. DOUBLE FREE!!!
    std::shared_ptr<Simple> smartPtr5 { smartPtr3 };    // Fix: copy `shared_ptr`

    // When this scope ends, `smartPtr4` is popped off the stack and frees the `Simple`
    // pointer because it doesn't know that `smartPtr3` also owns it, then `smartPtr3` 
    // goes out of scope and tries to free the same pointer leading to a double free.

    // You can cast a `shared_ptr` (but not `unique_ptr`) using any of the casting
    // functions: `const_pointer_cast()`, `dynamic_pointer_cast()`, `static_pointer_cast()`,
    // `reinterpret_pointer_cast()`.

    // -- Aliasing

    // We can alias a `shared_pointer` where we share ownership over one pointer (the
    // stored pointer), but point to a different object (stored pointer). The owned
    // pointer is used for reference counting, while the stored pointer is returned 
    // when you dereference or call `get()` in it.

    auto bar { std::make_shared<Bar>(42) };
    auto aliasing { std::shared_ptr<int> { 
        bar,            // owns the whole object (used for access, etc.)
        &bar->_data     // points to this member (`Bar` smart pointer is therefore aliased to an `int` pointer)
    } };

    // -- weak_ptr

    // A weak pointer contains reference to a resource managed by a `shared_ptr`
    // but does not own it. So, it is not considered during reference counting and 
    // does prevent deallocating resource when all the shared pointers actually 
    // owning the resources go out of scope.

    // See `useResource()` function definition for usage:

    auto sharedSimple { std::make_shared<Simple>() };
    std::weak_ptr<Simple> weakSimple { sharedSimple }; // constructor requires a `shared_ptr` or `weak_ptr`

    println("<- weak ptr");

    useResource(weakSimple);
    sharedSimple.reset();
    useResource(weakSimple);

    println("->");

    // -- Passing smart pointer to functions

    // Use a smart pointer function parameter only when there is ownership
    // transfer (`unique_ptr`, using "move semantics" because we need to 
    // move the ownership to another owner instead of copying) or sharing 
    // involved (`shared_ptr`). Otherwise, a reference-to-(non)-const
    // parameter is sufficient. There is also no reason to have reference
    // to a smart pointer, `const` or not.

    // -- Returning smart pointers from functions

    // The standard smart pointers can be easily and efficiently be returned
    // from functions by value, thanks to mandatory and non-mandatory copy
    // ellision. See the `createUniquePtr()` function as example:

    std::unique_ptr<Simple> mySmartPtr1 { createUniquePtr() };
    auto mySmartPtr2 { createUniquePtr() };

    // You can make a class to safely return a `shared_ptr` or `weak_ptr` to
    // itself by deriving from `std::enable_shared_from_this` class. You can
    // then call one of `shared_from_this()` or `weak_from_this()` public
    // member function in a (perhaps, better-named) member function to return 
    // the respective pointer to share/track ownership of the object. 
    // Without this class, you would need to have a `weak_ptr` data member 
    // and return copies of it or `shared_ptr`s constructed from.

    auto ptr1 { std::make_shared<Bar>(4) };
    auto ptr2 { ptr1->getPointer() };

    // you can only use `shared_from_this()` if the pointer is already stored
    // in a `shared_ptr`. The following code below compiles (because the
    // member function exists) but throws a `std::bad_weak_ptr`. Calling
    // `weak_from_this()` would work but it returns an empty one
    // (Bar { 4 } ).getPointer(); // no shared pointer exists
    // Also, you shouldn't implement `getPointer()` by making a shared (or weak)
    // pointer from `this`. This creates a distinct shared pointer each time. 
    // Always remember that shared pointers need to be associated with another
    // shared pointer with whom they share a resource with. Doing otherwise
    // would result in double deletion, as we have seen before

    // -- Interoperability of Smart Pointers with C-Style Functions

    // If we have C-style API (commonly functions which return error code but uses
    // function parameters as output from the function using pointers) such as
    // `my_alloc1()` and `my_free1()`, and we want to use them with out smart pointers
    // we can store the result in another variable, call the function, and then
    // reset the pointer with the new value gotten from the function.

    std::unique_ptr<int, decltype(&my_free1)> myIntSmartPtr3 { nullptr, my_free1 }; // init smart pointer
    int* data { nullptr };  // init buffer/placeholder pointer
    my_alloc1(42, &data);   // call function with placeholder pointer; check error code etc.
    myIntSmartPtr3.reset(data); // reset the pointer with the placeholder pointer

    // C++23 introduces a better way to do this using `std::out_ptr()` and
    // `std::inout_ptr()` functions. We simply pass the result of the function
    // invocation taking our smart pointer as argument to the C-style function.
    // Use `inout_ptr()` when you are sure the pointer is `nullptr`, otherwise
    // you can just use `out_ptr()` instead.
    // In the previous example, we replace the next three lines after smart pointer
    // declaration with just one line (skipping the need for a placeholder pointer)
    // my_alloc1(42, std::inout_ptr(myIntSmartPtr3));

    // -- The old and removed `auto_ptr`
    // Pre-C++ Standard Library included a basic implementation of a smart pointer,
    // called `auto_ptr` which has some serious shortcomings. For example, it does
    // not work correctly with Standard Library containers such as `vector`s. It is
    // now removed entirely from the Standard Libary and should never be used.
}

void leaky()
{

    println("");
    println("-- i am leaky");

    Simple* mySimplePtr { new Simple { } };
    mySimplePtr->go();

    // BUG!!: function returns without releasing memory allocated
}

void couldBeLeaky()
{

    println("");
    println("-- i could be leaky");

    Simple* mySimplePtr { new Simple { } };
    mySimplePtr->go(); // could be LEAKY if this function throws an exception 

    delete mySimplePtr;
}

void notLeaky()
{

    println("");
    println("-- def not leaky");

    auto mySimpleSmartPtr { std::make_unique<Simple>() };

    mySimpleSmartPtr->go();
    
    // in the code above, notice no `new`, `std::make_unique` does the 
    // allocation and returns a smart pointer that manages the memory for us.
    // `make_unique()` uses value initialisation which means primitive types
    // are initialised to zero, and objects are default constructed.
    // If you don't need this (probably you will overwrite it) for performance,
    // you can use `std::make_unique_for_overwrite()` function instead which
    // uses default initialisation where primitive types are not initialised at
    // all contain garbage data while objects are still default constructed.

    // You can also allocate the memory and give it to the constructor of
    // `std::unique_ptr` to create unique smart pointer.
    // However, you have to mention the class twice as CTAD (class template 
    // argument deduction) does not work here.

    std::unique_ptr<Simple> mySimpleSmartPtr1 { new Simple { } };

    // Before C++17, you had to use `make_unique()` since it is safer compared
    // to using the `unique_ptr` constructor. For example in the function call below:
    // foo(unique_ptr<Simple> { new Simple { } }, unique_ptr<Bar>  { new Bar { data() } });
    // If either `Bar` constructor or the `data()` invocation throws an exception, there
    // was a possibility that that the `Simple` (or `Bar`) object would be leaked.
    // This would not be the case with `make_unique()`. Since C++17, both are now
    // safe, but `make_unique()` is still recommended as it is more readable


    // can still be dereferenced.
    mySimpleSmartPtr->go();    // (*mySimpleSmartPtr).go() also works

    processData(mySimpleSmartPtr.get()); // use `get()` to access underlying pointer

    mySimpleSmartPtr.reset(); // free resource (if any) and set to `nullptr`
    processData(mySimpleSmartPtr.get()); // BUGGY!!! memory is reset already

    mySimpleSmartPtr.reset(new Simple { }); // free resource (if any) and set to new `Simple` instance
    processData(mySimpleSmartPtr.get()); // OKAY

    // You can disconnect the underlying pointer which means you now have to
    // free it yourself.

    Simple* simple { mySimpleSmartPtr.release() };

    processData(mySimpleSmartPtr.get()); // BUGGY!!! not owner of memory any longer!
    processData(simple);

    delete simple; simple = nullptr;

}

void processData(Simple* simple)
{

    if (simple == nullptr)
    {
        println("hmmm!!! nullptr");
        return;
    }

    println("processing data... ");
    simple->go();
}

int* my_alloc(int value) { return new int { value }; }

void my_free(int* p) { delete p; }

void useResource(std::weak_ptr<Simple>& weakSimple)
{
    // to get access to pointer, you convert it to a `shared_ptr` in one of two ways:
    // - use `lock()` as shown below, which returns a `shared_ptr`. The `shared_ptr`
    //      is `nullptr` if the `shared_ptr` has been deallocated.
    // - create a new `shared_ptr` passing the `weak_ptr` as argument to constructor
    //      this throws `std::bad_weak_ptr` exception if the `shared_ptr` associated
    //      with the `weak_ptr` has been deallocated. 
    auto resource   { weakSimple.lock() }; 

    if (resource)   { println("Resource still alive."); }
    else            { println("Resource has been freed!"); }
}

std::unique_ptr<Simple> createUniquePtr()
{
    auto ptr { std::make_unique<Simple>() };

    // Do something with ptr...

    return ptr;
}

