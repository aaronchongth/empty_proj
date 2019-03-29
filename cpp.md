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

- 
