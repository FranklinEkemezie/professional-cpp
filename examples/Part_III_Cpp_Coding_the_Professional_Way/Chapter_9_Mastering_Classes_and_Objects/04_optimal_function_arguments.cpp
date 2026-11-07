#include <vector>
#include <print>

class DataHolder
{
    public:
        // void setData(const std::vector<int>& data) { data_ = data; }
        // void setData(std::vector<int>&& data) { data_ = std::move(data); }
        void setData(std::vector<int> data) { data_ = std::move(data); }

    private:
        std::vector<int> data_ { };
};

int main()
{

    DataHolder wrapper { };

    // Recall that it is recommended to use reference-to-const parameters for
    // non-primitive functions to avoid unnecessary expensive copying.
    // The `DataHolder` class implements a member function that takes the
    // reference and assigns it to its data member. This triggers one copy
    // (copy assignment) as opposed to two if the member function used
    // pass-by-value in which case it is copied to argument and then 
    // (copy-) assigned to the data member

    std::vector myData { 11, 22, 33 };
    wrapper.setData(myData);

    // We also provide an overload that accepts `rvalue` reference, which are
    // then moved resulting in no copy, as opposed to one copy that would result
    // in (copy-) assigning it to the data member as in the first one.
    // If this overload is not provided, the suboptimal `lvalue` reference would
    // be used.
    wrapper.setData({ 22, 33, 44 });

    // This requires two overload implementation. Surprisingly, we can get the
    // best of both worlds (more like, best of both optimal scenarios), by using
    // the third overload which uses pass-by-value semantics. We can explain why
    // this makes sense:
    // - Recall that, for `lvalue` arguments, the function needs to copy at least once
    //      With the `lvalue` reference overload, the copy is done during assignment.
    //      We could therefore let it make a temporary copy of the argument passed and 
    //      then, move that copied value stored in the argument to the data member. 
    //      The argument would become invalid which is okay, because it's not used again.
    // - For `rvalue`, no copy is made as it is a temporary object (or value), and we
    //      can simply move it.
    // In both scenarios, we arrive at the same optimal behaviour with the first two overloads.

    std::println(
        "The rule to pass object using reference-to-const parameters can be modified by adding that "
        "you should pass by value when: \n"
        "i) the function would inherently copy.\n"
        "ii) the parameter is of a type that supports move semantics.\n"
        "Also, passing polymorphic types by value can result in slicing, so you probably "
        "don't want to use pass-by-value if you need polymorphic behaviour on the parameter\n"
        "In any other case, you should use reference-to-const parameters."
    );
}