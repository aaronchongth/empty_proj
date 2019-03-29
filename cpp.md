# General tips, tricks and good practices

Some of these would be organizationally specific, 

- Adding licences everywhere depending on the company

- Depending on the C++ ISO standards, use normal header guards instead of 

```
#pragma once
```

```
#ifndef NAMESPACE__FILE_HPP
#define NAMEPSACE__FILE_HPP

...

#endif // NAMESPACE__FILE_HPP
```

- keep namespaces consistent, one instance is good enough for an entire project

- **no** declarations in header files,
`
```
using namespace ...;
```
 
- **Styling**, most people use **Google** style guide, but some items are
  questionable. So far, I have found `LLVM` style guides to be more intuitive.

- References and pointers are aligned to the variable or function name, however
  intuitively it should be aligned towards to type as it is a **type
modifier**, hence try to align :point_left:

- **Braces**, just don't cuddle for anything, no one can complain about it.

- For small executables, avoid throwing exceptions, it will probably generate
  lots of noise over directions that will be printed for the user.

- Use `cxxopts` if possible, header-only library for executable options and
  arguments, love it

- Remember to use `override` if the object is written intended for final usage,
  `virtual` if there is a possibility of future child classes

- Generally people prefer `const T` instead of `T const`. `const` applies to
  whatever type is on its left, unless there is none, however `T const` is not
very readable.

 
