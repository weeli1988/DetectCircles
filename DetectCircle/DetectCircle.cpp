// DetectCircle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Helper.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    
    const char* filename = "src/circle_pattern.png";

    // load png with any color ? 
    Mat img = imread(samples::findFile(filename), IMREAD_COLOR);
    Mat resizeImg;

    resize(img, resizeImg, Size(900, 900));

    // check if image is loaded
    if (img.empty())
    {
        printf("Load source image failed!");
        return EXIT_FAILURE;
    }

    Mat gray;
    cvtColor(resizeImg, gray, COLOR_BGR2GRAY);

    medianBlur(gray, gray, 5);

    vector<Vec3f> circles;
    // gray.rows / 32
    HoughCircles(gray, circles, HOUGH_GRADIENT, 0.2,
        gray.rows / 10, // change this value to detect circles with different distances to each other
        20, 39, 0, 0 // change the last two parameters
        // (min_radius & max_radius) to detect larger circles
    );

    double pi = 3.142;
    int total_radius{};

    // sum all circle radius
    for (size_t i = 0; i < circles.size(); i++)
        total_radius += circles[i][2];

    // then get average radius
    int average_radius = total_radius/circles.size();

    vector<Vec3f> blackCircle;
    vector<Vec3f> bigCircles;
    vector<Vec3f> smallCircles;

    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle(resizeImg, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(resizeImg, center, radius, Scalar(255, 0, 255), 3, LINE_AA);

        // check if this is a black circle
        if (radius > 50)
        {
            blackCircle.push_back(circles[i]);
        }
        else 
        {
            // check if this is a bigger circle
            if (radius >= average_radius)
            {
                bigCircles.push_back(circles[i]);
            }
            else
            {
                smallCircles.push_back(circles[i]);
            }
        }
    }

    Vec3i black = blackCircle[0];
    Point blackPoint = Point(black[0], black[1]);
    int perimeter = 2 * pi * black[2];

    // show perimeter for each big circle
    cout << "Black circle perimeter: " << perimeter << "\n";
    putText(resizeImg, "Black circle perimeter: " + to_string(perimeter), Point(10, 30),
        cv::FONT_HERSHEY_DUPLEX, 0.8, CV_RGB(0, 0, 0), 0.8);

    // TODO create a class object to store all info
    // create Circle class
    // inheritance:
    // Small Circle : public Circle
    // Big Circle : public Circle
    
    // display info for all big circles
    for (int i = 0; i < bigCircles.size(); i++)
    {
        Vec3i b = bigCircles[i];
        Point bp = Point(b[0], b[1]);
        cout << "Big Circle " << i << " = x: " << b[0] << ", y: " << b[1] << ", r: " << b[2] << "\n";

        int dist = calculateDistance(b[0], b[1], black[0], black[1]);
        // draw line
        line(resizeImg, bp, blackPoint, Scalar(0, 0, 255), 1, LINE_AA);
        // draw text at middle of line
        putText(resizeImg, to_string(dist), (bp + blackPoint) / 2,
            cv::FONT_HERSHEY_DUPLEX, 0.3, CV_RGB(255, 255, 255), 0.3);
    }

    // display info for all small circles
    for (int i = 0; i < smallCircles.size(); i ++)
    {
        Vec3i s = smallCircles[i];
        Point sp = Point(s[0], s[1]);
        cout << "Small Circle " << i << " = x: " << s[0] << ", y: " << s[1] << ", r: " << s[2] << "\n";

        int dist = calculateDistance(s[0], s[1], black[0], black[1]);
        // draw line
        line(resizeImg, sp, blackPoint, Scalar(0, 0, 255), 1, LINE_AA);
        // draw text at middle of line
        putText(resizeImg, to_string(dist), (sp + blackPoint) / 2,
            cv::FONT_HERSHEY_DUPLEX, 0.3, CV_RGB(255, 255, 255), 0.3);
    }

    namedWindow("detected circles", WINDOW_AUTOSIZE);
    imshow("detected circles", resizeImg);
    waitKey();

    return EXIT_SUCCESS;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
