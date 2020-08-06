

#include "zgsinglelist.h"
#include <algorithm>
#include <stdio.h>


namespace zg
{
	void ztest_singlelist()
	{
		printf(" ############################## Running ztest_singlelist.cpp... ############################## \n\n");

		printf(" ############################## ctor \n");
		singlelist<int> tmp{};

		printf(" ############################## push_front() \n");
		tmp.push_front(1);	tmp.print();
		tmp.push_front(2);	tmp.print();
		tmp.push_front(3);	tmp.print();
		tmp.push_front(4);	tmp.print();
		
		printf(" ############################## copy ctor \n");
		singlelist<int> tmp2{tmp};
		tmp2.print();

		printf(" ############################## move ctor \n");
		singlelist<int> tmp3{std::move(tmp2)};
		tmp2.print();
		tmp3.print();
		tmp2 = std::move(tmp3);
		tmp2.print();
		tmp3.print();

		printf(" ############################## clear() \n");
		tmp.clear();
		tmp.print();

		printf(" ############################## pop_front() \n");
		tmp2.pop_front();	tmp2.print();
		tmp2.pop_front();	tmp2.print();
		tmp2.pop_front();	tmp2.print();
		tmp2.pop_front();	tmp2.print();

		printf(" ############################## push_back() \n");
		tmp.push_back(1);	tmp.print();
		tmp.push_back(2);	tmp.print();
		tmp.push_back(3);	tmp.print();
		tmp.push_back(4);	tmp.print();

		printf(" ############################## reverse() \n");
		tmp.reverse();
		tmp.print();

		printf(" ############################## insert() \n");
		tmp.insert(2, 5);
		tmp.print();
		tmp.insert(5, 5);
		tmp.print();
		tmp.insert(20, 5);
		tmp.print();
		tmp.insert(0, 5);
		tmp.print();

		printf(" ############################## pop_back() \n");
		tmp.pop_back();	tmp.print();
		tmp.pop_back();	tmp.print();
		tmp.pop_back();	tmp.print();
		tmp.pop_back();	tmp.print();

		printf("\n");
    	printf(" ############################## End ztest_singlelist.cpp ############################## \n");
	}
}

#ifndef _RUN_ALL_TEST_
int main()
{
	zg::ztest_singlelist();
}
#endif
