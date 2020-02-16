#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

// checking substring with the Z algorithm
bool is_substring(
    const std::string& substr, 
    const std::string& str, 
    const std::string& spacer)
{
  const std::size_t z_length = substr.length() + 1 + str.length();
  std::vector<int> z_array(z_length, 0);

  const std::string concat_str = substr + spacer + str;

  for (size_t i = 1; i < concat_str.length(); ++i)
  {
    size_t lbound = i;
    size_t rbound = i;
    size_t matching_prefix_chars = 0;

    // find matches stage
    while (rbound < concat_str.length())
    {
      if (concat_str[rbound] == concat_str[matching_prefix_chars])
      {
        ++rbound;
        ++matching_prefix_chars;
      }
      else 
      {
        if (matching_prefix_chars == substr.length())
          return true;

        z_array[i] = matching_prefix_chars;
        break;
      }
    }
    
    // shortcut stage
  }
  return false;
}

int main(int argc, char** argv)
{
  // const std::string substr("world");
  // const std::string str("hello_world");

  const std::string substr("world");
  const std::string str("fyvghebfwdsy8hiujergiowgrflbnjesrhello_world");
  const std::string spacer("$");

  if (is_substring(substr, str, spacer))
    printf("it is a substring!\n");
  else
    printf("NOPE\n");

  return 0;
}
