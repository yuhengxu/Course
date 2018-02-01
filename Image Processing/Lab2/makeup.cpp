#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

const int sigma = 5;
const double sigmaColor = sigma * 2;
const double sigmaSpace = sigma / 2;

const int kernel = 5;
const int sigmaSp = 30;
const int sigmaRp = 60;

vector<Mat>charnnalI, charnnalE, charnnalR;

//双边滤波
void bilateralBlur(Mat src, Mat dst, int sigmaS, int sigmaR, int kernelSize)
{
	int ksize;
	if (kernelSize % 2 == 0)
	{
		ksize = kernelSize / 2;
	}
	else
	{
		ksize = (kernelSize - 1) / 2;
	}
	if (kernelSize > src.rows || kernelSize > src.cols)
	{
		cout << "核输入过大" << endl;
	}

	double wp = 0.0;   //输出像素加权组合和  
	double wSum = 0.0;  //加权系数和  
	uchar centerPix;
	uchar curPix;
	for (int i = ksize; i<src.rows - ksize; i++)
	{
		uchar* srcdata = src.ptr<uchar>(i);
		uchar* dstdata = dst.ptr<uchar>(i);
		for (int j = ksize; j<src.cols - ksize; j++)
		{
			centerPix = srcdata[j];

			for (int k = i - ksize; k <= i + ksize; k++)
			{
				for (int l = j - ksize; l <= j + ksize; l++)
				{
					curPix = src.at<uchar>(k, l);
					/*加权系数W取决于定义核和值域核*/
					//计算定义核如下：  
					double delta = sqrt(double(k*k + l*l));
					double domain_kernel = exp(-0.5 * pow(delta / sigmaS, 2));
					//计算值域核如下：  
					double intens = double(abs(centerPix - curPix));
					double range_kernel = exp(-0.5 * pow(intens / sigmaR, 2));
					//加权系数  
					double w = domain_kernel*range_kernel;
					wp += w * curPix;
					wSum += w;

				}
			}
			dstdata[j] = wp / wSum;
			wp = 0.0;
			wSum = 0.0;
		}
	}
}


int main()
{
	Mat imgI = imread("./picture/I.bmp");
	Mat imgE = imread("./picture/E.bmp");
	Mat img_labI, img_labE;

	Mat img_face = imread("./picture/face.bmp");
	img_face = ~img_face;
	imgE = imgE - img_face;

	//namedWindow("img_E", 1);
	//imshow("img_E", imgE);
	//waitKey(0);

	cvtColor(imgI, img_labI, CV_BGR2Lab);
	cvtColor(imgE, img_labE, CV_BGR2Lab);

	split(img_labI, charnnalI);
	split(img_labE, charnnalE);

	imwrite("./result/Ia.bmp", charnnalI[1]);
	imwrite("./result/Ea.bmp", charnnalE[1]);


	Mat Is, Id, Es, Ed;
	bilateralFilter(charnnalI[0], Is, sigma, sigmaColor, sigmaSpace);
	bilateralFilter(charnnalE[0], Es, sigma, sigmaColor, sigmaSpace);

	//bilateralBlur(charnnalI[0], Is, sigmaSp, sigmaRp, kernel);
	//bilateralBlur(charnnalE[0], Es, sigmaSp, sigmaRp, kernel);

	Id = charnnalI[0] - Is;
	Ed = charnnalE[0] - Es;

	Mat Rd, Ra, Rb, Rs;
	/*Rd = 0.2*Id + 0.8*Ed;
	Ra = 0.2*charnnalI[1] + 0.8*charnnalE[1];
	Rb = 0.2*charnnalI[2] + 0.8*charnnalE[2];
	Rs = Rd + Is;*/

	Rd = Id.clone();
	Rs = Rd.clone();
	Ra = charnnalI[1].clone();
	Rb = charnnalI[2].clone();
	for (int i = 0; i < Ed.rows; i++)
	{
		for (int j = 0; j < Ed.cols; j++)
		{
			if (Ed.at<uchar>(i, j) <= 150)
				Rd.at<uchar>(i, j) = Id.at<uchar>(i, j);
			else
				Rd.at<uchar>(i, j) = Id.at<uchar>(i, j) + Ed.at<uchar>(i, j);
		}
	}
		
	for (int i = 0; i < charnnalI[1].rows; i++)
	{
		for (int j = 0; j < charnnalI[1].cols; j++)
		{
			if (imgE.at<Vec3b>(i,j)[0]==0&& imgE.at<Vec3b>(i, j)[1] == 0 && imgE.at<Vec3b>(i, j)[2] == 0)
				Ra.at<uchar>(i, j) = charnnalI[1].at<uchar>(i, j);
			else
				Ra.at<uchar>(i, j) = 0.2* charnnalI[1].at<uchar>(i, j) + 0.8* charnnalE[1].at<uchar>(i, j);
		}
	}

	for (int i = 0; i < charnnalI[2].rows; i++)
	{
		for (int j = 0; j < charnnalI[2].cols; j++)
		{
			if (charnnalE[2].at<uchar>(i, j) <= 250)
				Rb.at<uchar>(i, j) = charnnalI[2].at<uchar>(i, j);
			else
				Rb.at<uchar>(i, j) = 0.2*charnnalI[2].at<uchar>(i, j) + 0.8*charnnalE[2].at<uchar>(i, j);
		}
	}
		
	/*for (int i = 0; i < Ra.rows; i++)
		for (int j = 0; j < Ra.cols; j++)
			Rs.at<uchar>(i, j) = Is.at<uchar>(i, j) + Rd.at<uchar>(i, j);*/

	Rs = Rd + Is;

	split(img_labI, charnnalR);
	charnnalR[0] = Rs;
	charnnalR[1] = Ra;
	charnnalR[2] = Rb;

	Mat result_lab, result;
	merge(charnnalR, result_lab);
	cvtColor(result_lab, result, CV_Lab2BGR);

	imwrite("./result/Ed.bmp", Ed);
	imwrite("./result/Es.bmp", Es);
	imwrite("./result/Id.bmp", Id);
	imwrite("./result/Is.bmp", Is);
	imwrite("./result/Rd.bmp", Rd);
	imwrite("./result/Ra.bmp", Ra);
	imwrite("./result/Rb.bmp", Rb);
	imwrite("./result/result.bmp", result);

	namedWindow("result", 1);
	imshow("result", result);
	waitKey(0);

	return 0;
}