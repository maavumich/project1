#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

#include "../src/deps/Simulator.hpp"

using namespace std;

int main()
{
	Simulator sim;
	int counter = 1;
	while(!sim.simulate(0.1))		
	{
		cout << "running simulation\t counter: " << counter << endl;
		++counter;
	}
}