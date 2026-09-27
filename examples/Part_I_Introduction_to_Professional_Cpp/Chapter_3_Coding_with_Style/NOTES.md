# Chapter 3 - Coding with Style

## Importance

- Writing good code makes it easy to work with some time in the future.
- It makes it easier for others to understand and contribute meaningfully to your projects.

## Elements of Good Style

### Documentation

You should write comments to state in human language such as English what is not immediately obvious from code. 

Reasons to write comments:
- Explain how clients should interact with code: While descriptive names provide good information about the functions and its parameters, it may be useful to add extra information about the functions pre-conditions, post-conditions, and exceptions. This is typically done before the function declaration
- Explain Complicated Code: You can use comments inside the function to explain complex algorithms.
- Convey meta-information: Comments were used in the past to provide details about when the function was created, who created it, changes to the function, todos and unresolved bugs. However, these should not be used in modern codebases as that is the role of a version control system (VCS).
- Copyright comment: Found at the top of every source file to indicate that the writer has copyright of their own code. This is also not common since the Berne Convention in 1886 which does not require such notice to claim copyright of the code.

Commenting Styles:
- Every line: This is verbose and not recommended.
- Prefix comments: Source codes begin with a standard comment usually including copyright information, description of the file/class, bugs and incomplete features.
- Fixed-Format comments: Comments are written in a standard format that can be parsed by external document builders such JavaDoc for Java, Doxygen for C++ etc.
- Ad Hoc Comments: Comments are added when needed.

### Decomposition

Self-documenting code does not need too many comments. One way to write self-documenting code is by decompositions. Large functions, for example, can be broken up into smaller pieces with more descriptive names. Decomposition can achieved in various ways:
- Refactoring: When you have written code that works but it's not well-structured, you can restructure your code to make it more readable. When refactoring, you should employ techniques that provide better abstraction, allows breaking code apart into more smaller logical pieces, and improve names and location of code. You may need to make the code work for a general type, or break functions or even classes into smaller ones with better names and moving the code as needed.
- Design: Making use of a modular approach when design and writing the code for the first time.

### Naming

Choosing a good name is a crucial part of writing stylistically "good" code. In general, you should use names that:
- distinguish between different objects (variables, functions, classes, etc.)
- is simple, accurate, descriptive, easy to read.
- are not widely known abbreviations.

#### Naming Conventions:

- Counters: For counters and indexes, variable names `i`, `j` and `k` are commonly used, though better descriptive names should be preferred when they could potentially be ambiguous.
- Prefix: Others use prefix in the variable name to describe not only what a variable stores, but the type and context (whether it is a class member, static or non-static, constants etc). A popular form of prefix-naming is the Hungarian Notation. 
- Getters and Setters: Class *getters* and *setters* are usually prefixed with `get` and `set`.
- Capitalisation: Different alphabetical casing are used for different names. In C++, it is conventional to use either `snake_case` or `camelCase` for variable; `camelCase` for functions; `PascalCase` for namespaces, classes; and `SCREAMING_SNAKE_CASE` or `PascalCase` for constants.

### Using Language Features with Style

- Write readable code. Avoid writing almost too *fancy* or *clever* code as they may become unreadable or bug-prone.
- Use constants where necessary instead of littering the code around with *magic numbers*
- Use references instead of pointers. References are safer, easier to reason about, and have clearer and neater syntax and usage. They also clarify memory ownership: reference passed to a function is not owned and cannot be freed by the function.
- Use custom exceptions. Prefer exceptions over traditional error handling mechanisims such as returning special values e.g. `1`, `nullptr` or setting error flags. When these are used, you may use the `[[nodiscard]]` attribute to ensure the caller does something with special value returned. Exceptions, however, provide richer mechanisms for error handling and you can extend the built-in exceptions to throw custom exceptions tailoring it to your specific needs.
- Formatting. Use consistent formatting throughtout the code base. Some formatting issues include: curly brace alignment i.e. whether or when to put curly braces on a separate line, spaces or tabs for indentation, platform line breaks, spacing around operators, parentheses and variables. Overall, it is up to the individual(s) involved in a codebase to decide early on which formatting style to use. There are tools for automatic formatting such as `clang-format` that automatically format the code when saving the file or before it is published.

