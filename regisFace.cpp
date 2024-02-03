// Include the OpenCV header files and the iostream library
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <fstream>
#include <direct.h>
#include "globals.h"
#include "Random.h"

// Use the cv and std namespaces
using namespace cv;
using namespace std;

// A simple program to capture a photo from a camera using OpenCV
void regis()
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
	string userName{}, fileType{};
	cout << "Please input user name: ";
	cin >> userName;
	fileType = ".jpg";
	// Create a Mat object to store the captured frame
	Mat frame;

	// Create a named window to display the captured frame
	namedWindow("Webcam", WINDOW_AUTOSIZE);
	namedWindow("Photo_show", WINDOW_AUTOSIZE);

	// Load a face detection model, such as the Haar cascade classifier, using the CascadeClassifier class
	/*CascadeClassifier face_cascade;
	if (!face_cascade.load("C:/Users/k_pic/OpenCV/sources/data/haarcascades/haarcascade_frontalface_default.xml"))
		cout<<"Could not load haarcascade_frontalface_default.xml.\n";
	*/
	cout << "Please take 3 photos.\n";
	int n = 0;
	int label = Random::get(0,100);
	// Use a loop to capture a frame from the camera and show it on the window
	while (n<3)
	{
		// Capture a frame from the camera
		cap >> frame;

		// Check if the frame is empty
		if (frame.empty())
		{
			// Print an error message and break the loop
			cout << "ERROR: Frame is empty" << endl;
			break;
		}
		//Make a copy of the frame
		Mat frame_copy = frame.clone();
		// Use the detectMultiScale function to find the faces in the frame and return a vector of rectangles
		/*vector<Rect> faces;
		face_cascade.detectMultiScale(frame, faces);
		
		// Use the rectangle function to draw a borderline around each face in the frame
		for (int i = 0; i < faces.size(); i++)
		{
			// Define the color and thickness of the borderline
			Scalar color = Scalar(255, 0, 0); // Blue
			int thickness = 2;

			// Draw the borderline
			rectangle(frame, faces[i], color, thickness);
		}*/
		// Get the frame size
		int frame_width = frame.cols;
		int frame_height = frame.rows;

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
		rectangle(frame, pt1, pt2, color, thickness);


		// Show the frame on the window
		imshow("Webcam", frame);

		// Wait for a key press
		int key = waitKey(10);
		// If the key is 's', save the frame as a .jpg file using the imwrite function
		if (key == 's')
		{
			// Specify the file name and the compression quality
			//file name path should have user name as folder that store photos of that user
			string num = "0"+to_string(n);
			string csvFilename = "C:/Users/k_pic/source/repos/pwdNoMore/Data files/csv/"+userName+".txt";
			string filename = "C:/Users/k_pic/source/repos/pwdNoMore/Data files/facePhotos/"+userName+"Photo"+num + fileType;
			std::ofstream outf{ filename };
			if (!outf)
			{
				cerr << "Could not open file: " << filename << "\n";
			}
			vector<int> compression_params;
			compression_params.push_back(IMWRITE_JPEG_QUALITY);
			compression_params.push_back(95);
			imshow("Photo_show", frame_copy);
			// Save the frame as a .jpg file
			bool success = imwrite(filename, frame_copy, compression_params);

			// Check if the file is saved successfully
			if (success)
			{
				// Print a success message
				cout << "Photo no: " << n << " saved as " << filename << endl;
				ofstream csvf;
				csvf.open(csvFilename, ios::app);
				if (csvf.is_open())
				{
					csvf << filename << "; " << label << "\n";
					cout << "The file " << filename << "has been updated.\n";
				}
				else
				{
					cerr << "Could not open file: " << csvFilename << "\n";
				}
				++n;
			}
			else
			{
				// Print an error message
				cout << "ERROR: Could not save photo" << endl;
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
