#include <iostream>
#include <cstdlib>

#include "cmd/Cmd.hpp"

using namespace cmd;

int * generateReverseArray(int number)
{
	int * array = new int[number];

	for(int i = 0; i < number; ++i)
	{
		array[i] = number - i;
	}

	return array;
}

int * generateRandomArray(int number, int rmin, int rmax)
{
	int * array = new int[number];

	for(int i = 0; i < number; ++i)
	{
		array[i] = rand() % (rmax - rmin) + rmin;
	}

	return array;
}

void printArray(int * array, int size)
{
	std::cout << array[0];

	for(int i = 1; i < size; ++i)
	{
		std::cout << "," << array[i];
	}

	std::cout << std::endl;
}

void bubble(int * array, int size, bool verbose)
{
	bool change = true;
	int tmp;

	while(change)
	{
		change = false;

		for(int i = 1; i < size; ++i)
		{
			if(array[i-1] > array[i])
			{
				tmp = array[i-1];
				array[i-1] = array[i];
				array[i] = tmp;
				change = true;

				if(verbose)
					printArray(array, size);
			}
		}
	}
}

int main(int argc, const char *argv[])
{
	Command cmd("Bubble", "Generate and bubble sort an array.", "Author", "1.0");

	cmd.addPossiblePlus("help", "h", "Display this help.");
	cmd.addPossiblePlus("verbose", "v", "Show extra informations.");
	cmd.addPossiblePlus("random", "r", "Generate the array with random integers.");
	cmd.addPossiblePlus("reverse", "R", "Generate the array with values from n to 0.");

	cmd.addPossibleMinus("number", "n", "The number of integers to generate.", new IntegerValidator("min=1;max=512"));
	cmd.addPossibleMinus("random-min", "rmin", "Minimum value of the random generated numbers.", new IntegerValidator());
	cmd.addPossibleMinus("random-max", "rmax", "Maximum value of the random generated numbers.", new IntegerValidator());

	// These two lines are useless here but note that they exist
	// cmd.addPossibleTarget("file", "A useless file target.", new StringValidator());
	// cmd.allowRemainingTargets(true); // by default, no extra targets are allowed.

	cmd.addDependence("", "h | r | R"); // "" means the program itself, so h, r or R are required.
	cmd.addDependence("r", "!R"); // if random is set, reverse can not be set.
	cmd.addDependence("R", "!r"); // if reverse is set, random can not be set.
	cmd.addDependence("rmin", "r"); // if rmin is set, random must be set too.
	cmd.addDependence("rmax", "r"); // if rmax is set, random must be set too.
	// n, v and file are optional.

	try
	{
		cmd.parse(argc, argv);
	}
	catch(const std::string ex)
	{
		std::cout << ex << std::endl;
		return 1;
	}

	if(cmd.get<Plus>("h") != 0)
	{
		std::cout << cmd.help() << std::endl;
		return 0;
	}

	// Set the default values
	bool verbose = false;
	bool random = false; // which mean reverse mode
	int number = 32;
	int rmin = 0;
	int rmax = 100;

	if(cmd.get<Plus>("v") != 0)
	{
		verbose = true;
	}

	if(cmd.get<Plus>("r") != 0)
	{
		random = true;
	}

	Minus * tmpMinus;

	if((tmpMinus = cmd.get<Minus>("n")) != 0)
	{
		tmpMinus->smartCastIn<int>(number);
	}

	if((tmpMinus = cmd.get<Minus>("rmin")) != 0)
	{
		tmpMinus->smartCastIn<int>(rmin);
	}

	if((tmpMinus = cmd.get<Minus>("rmax")) != 0)
	{
		tmpMinus->smartCastIn<int>(rmax);
	}

	if(rmin > rmax)
	{
		std::cout << "rmin is greater than rmax" << std::endl;
		exit(1);
	}

	srand(time(0));
	int * array;

	if(random)
		array = generateRandomArray(number, rmin, rmax);
	else
		array = generateReverseArray(number);

	printArray(array, number);
	bubble(array, number, verbose);
	printArray(array, number);
	delete[] array;

	// useless stuff to show you targets usage
	//if(cmd.get<Target>("file"))
	//{
		//std::string file;
		//cmd.get<Target>("file")->smartCastIn<std::string>(file);
		//std::cout << "filename : " << file << std::endl;
	//}
	
	//std::vector<std::string> remainingTargets = cmd.getRemainingTargets();

	//for(unsigned int i = 0; i < remainingTargets.size(); ++i)
	//{
		//std::cout << "remaining : " << remainingTargets[i] << std::endl;
	//}

	return 0;
}
