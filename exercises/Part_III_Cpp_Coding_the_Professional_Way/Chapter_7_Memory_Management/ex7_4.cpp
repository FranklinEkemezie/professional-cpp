#include <format>
#include <iostream>
#include <memory>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')

void fillWithM(char* text);
void fillWithM(std::shared_ptr<std::string> text);

int main()
{

    std::string str1 { "hello" };
    println("before str1: {}", str1);

    fillWithM(str1.data());
    println("after  str1: {}", str1);

    auto str2 { std::make_shared<std::string>("hello, world") };
    println("before str2: {}", *str2.get());

    fillWithM(str2);
    println("after  str2: {}", *str2.get());
}

void fillWithM(char* text)
{
    int i { 0 };
    while (text[i] != '\0')
    {
        text[i] = 'm';
        ++i;
    }
}

void fillWithM(std::shared_ptr<std::string> text)
{
    for (size_t i { 0 }; i < text->length(); i++) 
    { 
        text->data()[i] = 'm'; 
    }
}



