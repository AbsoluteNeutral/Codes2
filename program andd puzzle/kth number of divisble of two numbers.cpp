#include <iostream>
#include <vector>

/*

All numbers that are divisible by 2 numbers, (e.g. 3 or 7)

Example:  3, 6, 7, 9, 12, 14, 15, 18, 21, 24 ...

Find the k-th number.
Example: 5th = 12

Input
The only line of the input contains an integer k (1≤k≤100).

Output
Print the k-th positive integer number from the sequence of 3 and/or 7-divisible numbers.
*/

int main()
{
	std::vector<int> con;
	int input = 0;
	std::cin >> input;
	std::cout << input << "-th number: ";
	
	int x3  = 3;
	int x7  = 7;
	int tmp = 3;
	while(input--)
	{
		if(x3 < x7)
		{
			tmp = x3;
			x3 += 3;
		}
		else if(x3 == x7)
		{
			tmp = x3;
			x3 += 3;
			x7 += 7;
		}
		else
		{
			tmp = x7;
			x7 += 7;
		}	
		con.push_back(tmp);
	}
	
	std::cout << tmp << std::endl;
	std::cout << "List:" << std::endl;
	for (auto i : con) 
        std::cout << i << ' '; 
	std::cout << std::endl
}

