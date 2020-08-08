
#include <stdio.h> 

void print_array(const char a[], int size)
{
  const char* f = a;
  const char* b = a + size;
  while(f != b)
    printf("%c", *(f++));
}

bool is_palindrome(const char *phrase, int length)
{
	//#ver1
  //int len = length/2;
  //for(int i = 0; i < len; ++i)
  //{
  //  if(*(phrase + i) == *(phrase + (length-1) - i))
  //    continue;
  //  else
  //    return false;
  //}
	
	//#ver2
	const char* f = phrase;
	const char* b = phrase + (length - 1);
  length = length >> 1;
  while(length--)
  {
    if( *(f++) == *(b--))
      continue;
    else
      return false;
  }
  return true;
}

void test_palindrome(const char sentence[], int length, int which_one)
{
  bool pal;
  pal = is_palindrome(sentence, length);

  print_array(sentence, length); 
  if (pal)
    printf(" is a palindrome\n");
  else
    printf(" is not a palindrome\n");
}

int main()
{
	{
  const char a[] = {'a'};
  test_palindrome(a, sizeof(a), 1);
  printf("\n");
	}
	{
  const char a[] = {'a', 'b'};
  test_palindrome(a, sizeof(a), 1);
  printf("\n");
	}
	{
  const char a[] = {'a', 'a'};
  test_palindrome(a, sizeof(a), 1);
  printf("\n");
	}
	{
  const char a[] = {'h', 'e', 'l', 'i', 'v', 'e', 'd', 'a', 's', 'a', 'd', 'e', 'v', 'i', 'l', 'e', 'h'};
  test_palindrome(a, sizeof(a), 1);
  printf("\n");
	}
	{
  const char a[] = {'1', '2', '3', '2', '1'};
  test_palindrome(a, sizeof(a), 1);
  printf("\n");
	}
	{
  const char a[] = {'a', 'B', 'c', 'D', 'E', 'e', 'D', 'c', 'B', 'a'};
  test_palindrome(a, sizeof(a), 1);
  printf("\n");
	}
	return 0;
}
