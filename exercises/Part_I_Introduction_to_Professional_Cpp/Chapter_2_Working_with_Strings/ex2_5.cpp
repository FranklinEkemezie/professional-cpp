#include <format>
#include <iostream>
#include <string>
#include <vector>

int main()
{


    std::vector<std::string> words { };
    std::size_t maxWordLength { };

    std::string word;

    std::cout << "Enter words. Press 'Enter' for new word. Enter '*' to exit." << '\n';

    while (true)
    {
        std::cout << ">> ";
        getline(std::cin, word);

        if (word == "*") break;

        words.push_back(word);

        const std::size_t wordLength { word.length() };
        if (wordLength > maxWordLength) maxWordLength = wordLength;
    }


    const unsigned int wordsPerRow { 5 };
    const unsigned int columnWidth { static_cast<unsigned int>(maxWordLength) + 2 };

    std::cout << maxWordLength << std::endl;

    for (unsigned int i = 0; i < words.size(); i++)
    {
        std::cout << std::format("|{1:^{0}}", columnWidth, words[i]);

        if ((i + 1) % wordsPerRow == 0) std::cout << "|" << '\n';
    }

    if (words.size() % wordsPerRow != 0) std::cout << "|" << std::endl;
    


    return 0;
}