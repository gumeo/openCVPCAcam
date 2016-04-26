#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using std::cout;

/*--------------- PCA on video stream ---------------*/
int main () {
  VideoCapture cap(0);

	if(!cap.isOpened()){
		cout << "Errore"; return -1;
	}
	Mat3b frame;
	while(cap.read(frame)){

		/* Reshape the frame for PCA*/
		Mat frameLinear = frame.reshape(1,frame.rows*frame.cols);
		frameLinear.convertTo(frameLinear, CV_32FC1);
		
		/* Do the PCA */
		PCA pca(frameLinear, Mat(), PCA::DATA_AS_ROW, 3);
		Mat points = pca.project(frameLinear);
		points = points.reshape(frame.channels(),frame.rows);
		Mat ch1, ch2, ch3, cch1, cch2, cch3;
		vector<Mat> channels(3);
		/* split img:*/
		split(points, channels);
		ch1 = channels[0];
		ch2 = channels[1];
		ch3 = channels[2];
		/* Normalize for visualization*/
		normalize(ch1, cch1, 0, 255, NORM_MINMAX, CV_8UC1);
		normalize(ch2, cch2, 0, 255, NORM_MINMAX, CV_8UC1);
		normalize(ch3, cch3, 0, 255, NORM_MINMAX, CV_8UC1);
		/* Display three images/video feeds of components */
		imshow("Channel 1", cch1);
		imshow("Channel 2", cch2);
		imshow("Channel 3", cch3);
		waitKey(5);
	}
	return(0);
}
