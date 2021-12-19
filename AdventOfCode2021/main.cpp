#include "day_1.h"
#include "day_2.h"
#include "day_3.h"
#include "day_4.h"
#include "day_5.h"
#include "day_6.h"
#include "day_7.h"
#include "day_8.h"
#include "day_9.h"
#include "day_10.h"
#include "day_13.h"
#include "day_14.h"
#include "day_15.h"
#include "day_16.h"
#include "day_17.h"

int main()
{
	/*Day_1{}.run();
	Day_2{}.run();
	Day_3{}.run();
	Day_4{}.run();
	Day_5{}.run();
	Day_6{}.run();*/
	/*Day_7{}.run();
	Day_8{}.run();
	Day_9{}.run();
	Day_10{}.run();
	Day_13{}.run();
	Day_14{}.run();
	Day_15{}.run();*/
	Day_16{}.run();
	Day_17{}.run();


	std::cout << "            2015  2016  2017  2018  2019  2020  2021\n";
	for (int i = 1; i < 26; i++)
	{
		std::cout << "day ";
		if (i < 10) {
			std::cout << " ";
		}
		std::cout << i << "\n";
	}
}
