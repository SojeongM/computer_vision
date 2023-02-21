#include <iostream>
#include <opencv2\opencv.hpp>

cv::Mat problem_a_rotate_forward(cv::Mat img, double angle) {
	cv::Mat output;
	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	int w = img.rows;
	int h = img.cols;
	double r_angle = angle * CV_PI / 180;
	

	//img.copyTo(rotate_image);
	
	cv::Point2f  c_point(w / 2.0, h / 2.0);
	
	int x = abs(h * sin(r_angle)) + abs(w*cos(r_angle));
	int y = abs(h * cos(r_angle))+abs(w *sin(r_angle));
	

//	cv::Mat rotate_image(y, x, CV_32FC3);
	cv::Mat coppy;
	img.copyTo(coppy);

	int i, j, k, a, b;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			for (k = 0; k < coppy.channels(); k++) {
				coppy.at<cv::Vec3b>(i, j)[k] = 0;
			}
		}
	}

	resize(coppy, output, cv::Size(y, x));
	
	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			int c = ((j - c_point.y) * sin(r_angle)) + ((i - c_point.x) * cos(r_angle)) + x / 2;
			int d = ((j - c_point.y) * cos(r_angle)) - ((i - c_point.x) * sin(r_angle)) + y / 2;
			for (k = 0; k < img.channels(); k++) {
				output.at<cv::Vec3b>(c, d)[k] = img.at<cv::Vec3b>(i, j)[k];


			}
		}
	}

	///// hint : refer annotation /////
	// 
	//Calculate Rotation matrix
	//
	//Find (x,y)ranges of output
	//
	//Calculate 'output' size  from range of output
	//
	//Calculate destination coordinates from origin

	

	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////
	cv::imshow("a_output", output); cv::waitKey(0);
	return output;
	
}

cv::Mat problem_b_rotate_backward(cv::Mat img, double angle) {
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	///// hint : refer annotation /////
	// 
	//Calculate Rotation matrix
	// 
	//Calculate Inverse Rotation matrix
	//
	//Find (x,y)ranges of output
	//
	//Calculate 'output' size  from range of output
	//
	//Calculate origin coordinates from destination coordinates
	//
	int w = img.rows;
	int h = img.cols;
	double r_angle = angle * CV_PI / 180;


	//img.copyTo(rotate_image);

	cv::Point2f  c_point(w / 2.0, h / 2.0);

	int x = abs(h * sin(r_angle)) + abs(w*cos(r_angle));
	int y = abs(h * cos(r_angle)) + abs(w *sin(r_angle));
	
	//	cv::Mat rotate_image(y, x, CV_32FC3);
	cv::Mat coppy;
	img.copyTo(coppy);

	int i, j, k, a, b;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			for (k = 0; k < coppy.channels(); k++) {
				coppy.at<cv::Vec3b>(i, j)[k] = 0;
			}
		}
	}

	resize(coppy, output, cv::Size(y, x));

	//printf("%d %d", y, x);

	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			int c = (-1)*((i - x / 2) * sin((-1)*r_angle)) + ((j - y / 2) * cos((-1)*r_angle)) + c_point.y;
			int d = ((i - x / 2) * cos((-1)*r_angle)) + ((j - y / 2) * sin((-1)*r_angle)) + c_point.x;
			for (k = 0; k < img.channels(); k++) {
				if ( (d >= 0 && d < img.rows) && (c >= 0 && c < img.cols)) {
					output.at<cv::Vec3b>(i, j)[k] = img.at<cv::Vec3b>(d, c)[k];

				}
			}
			
		}

	}
	
	cv::imshow("b_output", output); cv::waitKey(0);

	return output;
}

cv::Mat problem_c_rotate_backward_interarea(cv::Mat img, double angle) {
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	///// hint : refer annotation /////
	// 
	//Calculate Rotation matrix
	// 
	//Calculate Inverse Rotation matrix
	//
	//Find (x,y)ranges of output
	//
	//Calculate 'output' size  from range of output
	//
	//Calculate origin coordinates from destination coordinates
	//
	////////INTER_AREA
	int w = img.rows;
	int h = img.cols;
	double r_angle = angle * CV_PI / 180;


	//img.copyTo(rotate_image);

	cv::Point2f  c_point(w / 2.0, h / 2.0);

	double d_x, d_y;
	d_x= fabs(h * sin(r_angle)) + fabs(w*cos(r_angle));
	d_y= fabs(h * cos(r_angle)) + fabs(w *sin(r_angle));

	int x = (int)d_x;
	int y = (int)d_y;

	//	cv::Mat rotate_image(y, x, CV_32FC3);
	cv::Mat coppy;
	img.copyTo(coppy);

	int i, j, k, a, b;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			for (k = 0; k < coppy.channels(); k++) {
				coppy.at<cv::Vec3b>(i, j)[k] = 0;
				
			}
		}
	}

	resize(coppy, output, cv::Size(y, x));

	int r_x, r_y;
	
	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
		/*	for (k = 0; k < img.channels(); k++) {
				
				g = ((i - (double)d_x / 2) * cos((-1)*angle)) - ((j - (double)d_y / 2) * sin((-1)*angle)) + c_point.x;
				r = ((i - (double)d_x / 2) * sin((-1)*angle)) - ((j - (double)d_y / 2) * cos((-1)*angle)) + c_point.y;

			}*/
			r_x = ((i - (double)d_x / 2) * cos((-1)*r_angle)) + ((j - (double)d_y / 2) * sin((-1)*r_angle)) + c_point.x;
			r_y = -((i - (double)d_x / 2) * sin((-1)*r_angle)) + ((j - (double)d_y / 2) * cos((-1)*r_angle)) + c_point.y;

		//	r_y += d_x;
		//	r_x += d_y;

			for (k = 0; k < img.channels(); k++) {
				double aa, bb, cc, dd;
				aa = img.at<cv::Vec3d>((int)r_x, (int)r_y + 1)[k];
				bb = img.at<cv::Vec3b>(r_x, r_y)[k];
				cc = img.at<cv::Vec3d>((int)r_x+1, (int)r_y )[k];
				dd = img.at<cv::Vec3d>((int)r_x+1, (int)r_y + 1)[k];
			

					
			//	printf("1");
				if (r_x >= 0 && r_y >= 0 && r_x + 1 < w && r_y + 1 < h) {
					output.at<cv::Vec3b>(i, j)[k] = bb;
					
				}
				else {
					output.at<cv::Vec3b>(i, j)[k] = 0;
				}
				
			}
			
		}

	}


	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////

	cv::imshow("c_output", output); cv::waitKey(0);

	return output;
}

int main(void) {

	double angle = -15.0f;

	cv::Mat input = cv::imread("lena.jpg");
	cv::imshow("output", input);
	cv::waitKey();
	//Fill problem_a_rotate_forward and show output
	problem_a_rotate_forward(input, angle);
	//Fill problem_b_rotate_backward and show output
	problem_b_rotate_backward(input, angle);
	//Fill problem_c_rotate_backward_interarea and show output
	problem_c_rotate_backward_interarea(input, angle);
}