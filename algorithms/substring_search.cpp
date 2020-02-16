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
  const std::size_t n = concat_str.length();

  std::size_t lbound = 0;
  std::size_t rbound = 0;
  for (size_t i = 1; i < n; ++i)
  {
    // when the index is equal to or outside of the rbound, we will be starting 
    // the comparison phase from here
    if (i > rbound)
    {
      lbound = i;
      rbound = i;

      // comparison and find matches stage, continue adding onto the rbound
      // if rbound is still within the index of the string, and if the prefix 
      // of the string continues to match 
      while (rbound < n && concat_str[rbound-lbound] == concat_str[rbound])
      {
        ++rbound;
      }

      // at this point, we will know how many characters in the string has
      // matched the prefix of the string
      z_array[i] = rbound - lbound;
      --rbound;
    }
    // when the index is within the rbound, we will be copying the past values
    // instead of doing any comparisons
    else
    {
      // we first get the index of the prefix string
      std::size_t prefix_index = i - lbound;
      
      // as long as the past value added to the current index does not overshoot 
      // the rbound index, we can copy the value in straight
      if (i + z_array[prefix_index] < rbound + 1)
      {
        z_array[i] = z_array[prefix_index];
      }
      // when it has overshot, we have to readjust lbound and start the
      // comparison from there again
      else
      {
        lbound = i;

        // comparison and find matches stage, just like before
        while (rbound < n && concat_str[rbound-lbound] == concat_str[rbound])
        {
          ++rbound;
        }

        // same as before, at this point, we know how many characters from
        // lbound onwards is the same as the prefix of the string
        z_array[i] = rbound - lbound;
        --rbound;
      }
    }
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
