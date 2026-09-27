#include <format>
#include <iostream>

enum class PieceType: unsigned short
{
    King = 1,
    Queen,      // has value 2
    Rook = 10,
    Pawn        // has value 11
};

int main()
{

    // even though enumerations are internally represented by integer values,
    // they are not automatically converted to integers; a cast is required
    // from C++23, you can get the value using `std::to_underlying()`
    std::cout << std::format("Pawn: {}", static_cast<int>(PieceType::Pawn)) << std::endl;

    // 'use' enums to prevent using their fully qualified name
    // this may not always be recommended since it may lead to name conflicts

    using enum PieceType;

    PieceType piece { King };
    std::cout << std::format("King: {}", static_cast<int>(piece)) << std::endl;

    // Old style enumerators from C (defined without the 'class') do not posses this scoping feature,
    // are not strongly-type (hence type-unsafe), and always (can be mistakenly) interpreted as integers

    



}