#include <cstdlib>
#include <format>
#include <iostream>


[[nodiscard("idk, just use the return value, might be some return code")]] 
int myNoDiscardFunc() { return 42; }

// without this compiler cries.
int myMaybeUnusedFunc(
    [[maybe_unused]] int param1, 
    [[maybe_unused]] int param2
) { return 42; }

// without this, the compiler still demands we return a value after this function
// is invoked even though, we know it is pointless, since calling this function 
// terminates the program. We explicitly tell the compiler that this function never
// returns control the caller, so no need to whine about the caller having to return a value
[[noreturn]] 
void forceProgramTermination() { exit(1); }

bool isDongleAvailable()
{
    bool isAvailable { true };
    // check whether a licensing dongle is available...
    return isAvailable;
}

// `deprecated` means you can still use the function, but its use is discouraged
[[deprecated("Unsafe function, please use xyz")]]
void myDeprecatedFunc() 
{ 
    std::cout << std::format("why thoust callet {}, for the function is deprecated", __func__) << std::endl; 
}


bool isFeatureLicensed(int featureId)
{
    if (! isDongleAvailable())
    {
        // No licensing dongle found, abort program execution!
        forceProgramTermination();
    }
    else
    {
        // Dongle available, perform license check of the given feature...
        bool isLicensed { featureId == 42 };
        return isLicensed;
    }
}


// The likelihood attributes [[likely]] and [[unlikely]] are used to mark that certain
// code branches of `if` and `switch` statements are likely or unlikely to be taken. This
// helps the compiler in optimising code. However, the attribute is not commonly used as 
// compilers and hardwares these days have powerful branch prediction to figure it out for
// themselves. You can still use them in performance critical code, to help the compiler.
// Syntax:
// if statment: if (value > 11) [[unlikely]] { /* Do something... */ }
// switch statement: [[likely]] case 1: /* .. */


int divideBy32(int x)
{
    // lets the compiler know it can make some assumption when producing code.
    // in the example below, the compiler can assume `x` is `signed` (i.e. >= 0)
    // and do not have to worry about handling cases where `x` is negative.
    // in this case, the code can be optimised to just a single instruction:
    // a simple right shift of 5 bits.
    [[assume(x >= 0)]];
    return x / 32;
}

int main()
{
    // myNoDiscardFunc(); // compiler cries
    std::cout << std::format("func() returns: {}", myNoDiscardFunc()) << std::endl;

    bool isLicensed { isFeatureLicensed(42) };
    std::cout << std::format("is licensed? {}", isLicensed) << std::endl;

    // myDeprecatedFunc();

}