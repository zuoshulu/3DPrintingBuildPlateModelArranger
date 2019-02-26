#include <iostream>
#include <vector>
#include <deque>
#include "BuildPlate.h"
#include "Model.h"

using namespace std;


int main(int argc, char **argv)
{
    if (argc < 5 || argc % 2 != 1)
	{
		cout << "Please provide enough input parameters" << endl;
		cout << "Example:ModelArrange 100 100 50 50 40 40 40 40 40 40" << endl;
		cout << "Arg(1) : Build plate length" << endl;
		cout << "Arg(2) : Build plate width" << endl;
		cout << "Arg(3) : Model one length" << endl;
		cout << "Arg(4) : Model one width" << endl;
		cout << "Arg(5) : Model two length" << endl;
		cout << "Arg(6) : Model two width" << endl << "..." << endl << "Arg(n)" << endl;
		return 0;
	}

    //vector<Model> collectionfModels;
    deque<Model> collectionfModels;
    for(int i = 3; i < argc; i += 2)
	{
        int modelLength = atoi(argv[i]);
		int ModelWidth = atoi(argv[i+1]);
        collectionfModels.push_back(Model(modelLength, ModelWidth));
    }

    int length = atoi(argv[1]);
	int width = atoi(argv[2]);
    BuildPlate bp(length, width);

    cout << "Set build plate size to " << length << " x " << width << endl;
    if (bp.arrangeModel(collectionfModels))
		cout << "Fnished placing all 3D models" << endl;
	else
		cout << "Failed to placing all 3D modles" << endl;

    return 0;
}