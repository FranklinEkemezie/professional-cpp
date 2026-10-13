

class Simple
{
    public:
        Simple() { _intPtr = new int { }; }
        ~Simple() { delete _intPtr; }
        void setValue(int value) { *_intPtr = value; }

    private:
        int* _intPtr;
};

void doSomething(Simple*& outSimplePtr);

int main()
{

    // --- Common Memory Pitfalls

    // -- Underallocating Data Buffers and Out-of-Bounds Memory Access

    // In general, underallocation occurs when the buffer allocated is too
    // small for the data is to meant to store. This can lead to out-of-bounds
    // memory access. Underallocation is common in C-style string where the 
    // trailing '\0' terminator is omitted. C-style functions which assume the
    // prescence of this sentinel would eventually access memory beyond the
    // intended string resulting in buffer overflow errors. Hence, it is 
    // advised to use C++-style strings when dealing with dynamic strings.

    // -- Memory Leaks

    // You can eliminate the possibility of memory leaks by sticking to
    // modern C++. Memory leaks occurs when when you allocate memory and neglect
    // to release it. While this can be avoided by ensuring that every `new`
    // has a corresponding `delete`, things can still go wrong. See example below:

    Simple* simplePtr { new Simple { } }; // allocate memory for `Simple`

    // the function below allocates a new memory without freeing up the old one
    doSomething(simplePtr);

    delete simplePtr; simplePtr = nullptr; // only cleans up the second object.

    // -- Double-Deletion and Invalid Pointers

    // When you release associated with a pointer using `delete`, the memory is
    // available for use by other parts of your program. The pointer is said to
    // be dangling and you should not use it again, unless it reallocated.
    // Double deletion is also a probem, as you could potentially be freeing a
    // legally allocated memory to another object.
    // To avoid double deletion and using already released memory, you should
    // set your pointers to `nullptr` affter deallocating their memory.

}

void doSomething(Simple*& outSimplePtr)
{
    // delete outSimplePtr; // FIX: Delete old object

    outSimplePtr = new Simple { }; // BUG! Overwrite but does not delete original
}
