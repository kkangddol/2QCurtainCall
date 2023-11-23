#include "GRX.h"
#include <iostream>
#include <string>
#include <windows.h>

int main()
{
	ReactiveProperty<int> a(10);

	a.Where([](int x) {
		return x > 10;
		}).Scan([](int x, int y) {
			return x * y;
		})
		.Subscribe([](int x) {
			std::cout << x<<std::endl;
		});

		a = 10;
		a = 11;
		a = 12;
		a = 13;
		a = 7;
		a = 20;


}