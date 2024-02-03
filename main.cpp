
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void regis();
void logFace();
int main()
{
	int inp{}, x=1;
	cout << "Welcome!, please select from following menu.\n";
	cout << "1. Register and take self photos.\n";
	cout << "2. Login using facial identification.\n" << "3. Exit\n";
	cout << "Your input: ";
	cin >> inp;
	while (inp < 1 && inp>3 && x<3)
	{
		cout << "Your input: ";
		cin >> inp;
		++x;
	}
	if (x > 3)
	{
		cout << "You have failed to input proper option for 3 attempts.\n";
		return 0;
	}
	switch (inp)
	{
	case 1:
		regis();
		break;
	case 2:
		logFace();
		break;
	case 3:
		return 0;
	default:
		break;
	}
	return 0;
}