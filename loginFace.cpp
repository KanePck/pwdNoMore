#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

bool faceRecn(string& fn_csv, string& faceLogFn);

void logFace()
{
	// Create a VideoCapture object and open the camera device (0 for the default camera)
	VideoCapture cap(0);

	// Check if the camera is opened successfully
	if (!cap.isOpened())
	{
		// Print an error message and return -1
		cout << "ERROR: Could not open camera" << endl;
		return;
	}
	string userName{}, filePath{}, csvFn{}, faceLogFn{};
	bool unameValid = false;
	int j = 0;
	cout << "You have 3 attempts to log in!\n";
	while (!unameValid)
	{
		cout << "Please input user name: ";
		cin >> userName;
		j++;
		string csvFilename = "C:/Users/k_pic/source/repos/pwdNoMore/Data files/csv/" + userName + ".txt";
		//To check if userName exists?
		std::ifstream file(csvFilename, ios::in);
		if (file.is_open())
		{
			unameValid = true;
			cout << "Your user name exists and is valid.\n";
		}
		else
		{
			cout << "Your user name is not correct or exists.\n";
			if (j == 3)
				return;
		}
	}
	
	filePath = "Photo.jpg";
	// Create a Mat object to store the captured frame
	Mat frame1;
	int n = 0;
	// Create a named window to display the captured frame
	namedWindow("Webcam", WINDOW_AUTOSIZE);
	namedWindow("Photo_show", WINDOW_AUTOSIZE);
	cout << "You have 3 attempts to take self photos for face identification login.\n";
	while (true)
	{
		// Capture a frame from the camera
		cap >> frame1;

		// Check if the frame is empty
		if (frame1.empty())
		{
			// Print an error message and break the loop
			cout << "ERROR: Frame is empty" << endl;
			break;
		}
		//Make a copy of the frame
		Mat frame1_copy = frame1.clone();
		
		// Get the frame size
		int frame_width = frame1.cols;
		int frame_height = frame1.rows;

		// Define the rectangle size
		int rect_width = 260;
		int rect_height = 350;

		// Calculate the top-left and bottom-right points of the rectangle
		Point pt1((frame_width - rect_width) / 2, (frame_height - rect_height) / 2); // Centered on the frame
		Point pt2(pt1.x + rect_width, pt1.y + rect_height);

		// Define the color and thickness of the rectangle
		Scalar color = Scalar(255, 0, 0); // Blue
		int thickness = 2;

		// Draw the rectangle on the frame
		rectangle(frame1, pt1, pt2, color, thickness);
		// Display text on frame
		string texts{ "Please align your face inside the rectangular." };
		Point org(10,30);
		putText(frame1, texts, org, FONT_HERSHEY_PLAIN, 1.0, color, 1, LINE_8, false );
		// Show the frame on the window
		imshow("Webcam", frame1);

		// Wait for a key press
		int key = waitKey(10);
		// If the key is 's', save the frame as a .jpg file using the imwrite function
		if (key == 's')
		{
			// Specify the file name and the compression quality
			//file name path should have user name as folder that store photos of that user
			csvFn = "C:/Users/k_pic/source/repos/pwdNoMore/Data files/csv/" + userName + ".txt";
			faceLogFn = "C:/Users/k_pic/source/repos/pwdNoMore/Data files/loginPhotos/" + userName + filePath;
			std::ofstream outf{ faceLogFn };
			if (!outf)
			{
				cerr << "Could not open file: " << faceLogFn << "\n";
			}
			vector<int> compression_params;
			compression_params.push_back(IMWRITE_JPEG_QUALITY);
			compression_params.push_back(95);
			imshow("Photo_show", frame1_copy);
			// Save the frame as a .jpg file
			bool success = imwrite(faceLogFn, frame1_copy, compression_params);

			// Check if the file is saved successfully
			if (success)
			{
				// Print a success message
				cout << "Photo has been saved as " << faceLogFn << endl;
			}
			else
			{
				// Print an error message
				cout << "ERROR: Could not save photo." << endl<<"Please try again.";
			}
			//To validate face login
			if (!faceRecn(csvFn, faceLogFn))
			{
				++n;
				cout << "Face login failed.\nPlease try again!\n";
				cout <<"You have: "<<(3-n)<<" attempts remaining.\n";
				if (n == 3)
					break;
			}
			else
			{
				cout << "Face login successful.\n";
				break;
			}
		}
		// If the key is ESC, break the loop and exit the program
		if (key == 27)
		{
			break;
		}
	}
	
	// Release the VideoCapture object and destroy the window
	cap.release();
	destroyAllWindows();
	return;
}



