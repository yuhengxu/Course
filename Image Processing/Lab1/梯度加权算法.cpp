#include<opencv2/opencv.hpp>
#include<iostream>
#include<time.h>

using namespace std;
using namespace cv;

char filename[256];
char filename2[256];


/**********************************************

自己写的高斯滤波，处理效果比自带的高斯滤波效果好
但是速度有点慢

**********************************************/
void GaussianSmooth(const Mat&src, Mat &dst, double sigma)
{
	sigma = sigma>0 ? sigma : 0;
	int ksize = cvRound(3 * sigma) * 2 + 1;//保证ksize是奇数
	assert((ksize & 1) == 1);
	if (ksize == 1)
	{
		dst = src.clone();
		return;
	}
	dst.create(src.size(), src.type());
	Mat tmp;
	tmp.create(src.size(), src.type());
	double *kernel = new double[ksize];
	double pscale = -1.0 / (2 * sigma*sigma);
	double c = 1.0 / (sigma*sqrt(2 * CV_PI));
	double sum = 0;
	int kcenter = ksize / 2;
	int i, j, k;
	for (i = 0; i<ksize; i++)
	{
		int x = i - kcenter;
		kernel[i] = c*exp(pscale*x*x);
		sum += kernel[i];
	}
	for (i = 0; i<ksize; i++)
		kernel[i] /= sum;
	//进行x方向上的高斯模糊
	for (i = 0; i<src.rows; i++)
	{
		const uchar *pSrc = src.ptr<uchar>(i);
		uchar *pTmp = tmp.ptr<uchar>(i);
		for (j = 0; j<src.cols; j++)
		{
			double r = 0, g = 0, b = 0, w = 0;
			sum = 0;
			for (k = -kcenter; k <= kcenter; k++)
			{
				if (j + k >= 0 && j + k<src.cols)
				{
					if (src.channels() == 1)
						sum += pSrc[j + k] * kernel[k + kcenter];
					else
					{
						b += pSrc[3 * (j + k)] * kernel[k + kcenter];
						g += pSrc[3 * (j + k) + 1] * kernel[k + kcenter];
						r += pSrc[3 * (j + k) + 2] * kernel[k + kcenter];
					}
					w += kernel[k + kcenter];
				}
			}
			if (src.channels() == 1)
				pTmp[j] = sum / w;
			else
			{
				pTmp[3 * j] = b / w;
				pTmp[3 * j + 1] = g / w;
				pTmp[3 * j + 2] = r / w;
			}
		}
	}
	//y方向上高斯模糊
	for (j = 0; j<src.cols; j++)
	{
		for (i = 0; i<src.rows; i++)
		{
			// Vec3b* rgb=tmp.ptr<Vec3b>(i);
			double r = 0, g = 0, b = 0, w = 0;
			sum = 0;
			for (k = -kcenter; k <= kcenter; k++)
			{
				if (i + k >= 0 && i + k<src.rows)//0填充处理边缘
				{
					if (src.channels() == 1)
						// sum+=*(src.data+i*src.step[0]+j)*kernel[k+kcenter];
						sum += tmp.ptr<uchar>(i + k)[j] * kernel[k + kcenter];
					else
					{
						Vec3b *t = tmp.ptr<Vec3b>(i + k);
						b += t[j][0] * kernel[k + kcenter];
						g += t[j][1] * kernel[k + kcenter];
						r += t[j][2] * kernel[k + kcenter];
					}
					w += kernel[k + kcenter];
				}
			}
			if (src.channels() == 1)
				dst.ptr<uchar>(i)[j] = sum / w;
			else
			{
				Vec3b *rgb = dst.ptr<Vec3b>(i);
				rgb[j][0] = b / w;
				rgb[j][1] = g / w;
				rgb[j][2] = r / w;
			}
		}
	}
	delete[]kernel;
}

/*********************************************

自己写的中值滤波，和库函数给出的基本没啥差别

********************************************/
//求九个数的中值
uchar Median(uchar n1, uchar n2, uchar n3, uchar n4, uchar n5, uchar n6, uchar n7, uchar n8, uchar n9)
{
	uchar arr[9];
	arr[0] = n1;
	arr[1] = n2;
	arr[2] = n3;
	arr[3] = n4;
	arr[4] = n5;
	arr[5] = n6;
	arr[6] = n7;
	arr[7] = n8;
	arr[8] = n9;
	for (int gap = 9 / 2; gap > 0; gap /= 2)//希尔排序
		for (int i = gap; i < 9; ++i)
			for (int j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap)
				swap(arr[j], arr[j + gap]);
	return arr[4];//返回中值
}
void myMedianBlur(const Mat &src, Mat &dst)
{
	if (!src.data)return;
	Mat _dst(src.size(), src.type());
	for (int i = 0; i < src.rows; ++i)
	{
		for (int j = 0; j < src.cols; ++j)
		{
			if ((i - 1) > 0 && (i + 1) < src.rows && (j - 1) > 0 && (j + 1) < src.cols)
			{
				_dst.at<Vec3b>(i, j)[0] = Median(src.at<Vec3b>(i, j)[0], src.at<Vec3b>(i + 1, j + 1)[0],
					src.at<Vec3b>(i + 1, j)[0], src.at<Vec3b>(i, j + 1)[0], src.at<Vec3b>(i + 1, j - 1)[0],
					src.at<Vec3b>(i - 1, j + 1)[0], src.at<Vec3b>(i - 1, j)[0], src.at<Vec3b>(i, j - 1)[0],
					src.at<Vec3b>(i - 1, j - 1)[0]);
				_dst.at<Vec3b>(i, j)[1] = Median(src.at<Vec3b>(i, j)[1], src.at<Vec3b>(i + 1, j + 1)[1],
					src.at<Vec3b>(i + 1, j)[1], src.at<Vec3b>(i, j + 1)[1], src.at<Vec3b>(i + 1, j - 1)[1],
					src.at<Vec3b>(i - 1, j + 1)[1], src.at<Vec3b>(i - 1, j)[1], src.at<Vec3b>(i, j - 1)[1],
					src.at<Vec3b>(i - 1, j - 1)[1]);
				_dst.at<Vec3b>(i, j)[2] = Median(src.at<Vec3b>(i, j)[2], src.at<Vec3b>(i + 1, j + 1)[2],
					src.at<Vec3b>(i + 1, j)[2], src.at<Vec3b>(i, j + 1)[2], src.at<Vec3b>(i + 1, j - 1)[2],
					src.at<Vec3b>(i - 1, j + 1)[2], src.at<Vec3b>(i - 1, j)[2], src.at<Vec3b>(i, j - 1)[2],
					src.at<Vec3b>(i - 1, j - 1)[2]);
			}
			else
				_dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
		}
	}

	_dst.copyTo(dst);//拷贝
}


//矩阵取反
Mat oppo_src(Mat src)
{
	Mat oppo = src.clone();
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			oppo.at<Vec3b>(i, j)[0] = 255 - src.at<Vec3b>(i, j)[0];
			oppo.at<Vec3b>(i, j)[1] = 255 - src.at<Vec3b>(i, j)[1];
			oppo.at<Vec3b>(i, j)[2] = 255 - src.at<Vec3b>(i, j)[2];
		}
	}
	return oppo;
}

/*计算梯度并取反*/
//采用sobel算子
void sobel_grad(int num)
{

	Mat src_gray, src_gauss;
	for (int i = 1; i <= num; i++)
	{
		sprintf(filename, "%s\\%d.jpg", "picture", i);
		Mat src = imread(filename);

		//高斯滤波
		GaussianBlur(src, src_gauss, Size(3, 3), 0, 0, BORDER_DEFAULT);

		//转变成灰度图
		cvtColor(src_gauss, src_gray, COLOR_BGR2GRAY);

		//不进行高斯滤波
		//cvtColor(src, src_gray, COLOR_BGR2GRAY);

		//锐化操作，采用sobel算子。在多个地方加高斯滤波均无法达到预期目标。说明sobel算子计算的梯度并不太好用。下次尝试laplacion和canny算子
		int scale = 1, delta = 0, ddepth = CV_8U;
		Mat grad, grad_x, grad_y, abs_grad_x, abs_grad_y;

		Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
		Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);

		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);

		//计算梯度
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

		//在得到梯度图后就进行高斯滤波，效果很好。有效的去除了在边沿部分的噪声
		GaussianBlur(grad, grad, Size(3, 3), 0, 0, BORDER_DEFAULT);

		//保证大小一致，否则不能正确输出
		cvtColor(grad, grad, CV_GRAY2BGR);

		//梯度取反
		Mat grad_oppo = oppo_src(grad);

		//output
		sprintf(filename2, "%s\\%d.jpg", "output", i);
		imwrite(filename2, grad_oppo);
	}
}

//采用laplacion算子
void laplacion_grad(int num)
{
	Mat src_gray, src_gauss, grad;

	for (int i = 1; i <= num; i++)
	{
		sprintf(filename, "%s\\%d.jpg", "picture", i);
		Mat src = imread(filename);

		//自己写的高斯滤波
		GaussianSmooth(src, src_gauss, 4);

		//高斯滤波
		//GaussianBlur(src, src_gauss, Size(3, 3), 0, 0, BORDER_DEFAULT);

		//转变灰度图
		cvtColor(src_gauss, src_gray, COLOR_BGR2GRAY);

		//不进行高斯去噪
		//cvtColor(src, src_gray, COLOR_BGR2GRAY);

		//采用laplacion算子计算梯度
		int scale = 1, delta = 0, kernel_size = 3, ddepth = CV_8U;
		Laplacian(src_gray, grad, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);

		//在得到梯度图后就进行高斯滤波，效果很好。有效的去除了在边沿部分的噪声
		GaussianBlur(grad, grad, Size(3, 3), 0, 0, BORDER_DEFAULT);

		//保证大小一致，否则不能正确输出
		cvtColor(grad, grad, CV_GRAY2BGR);

		//梯度取反
		Mat grad_oppo = oppo_src(grad);

		//output
		sprintf(filename2, "%s\\%d.jpg", "output", i);
		imwrite(filename2, grad_oppo);
	}
}

//采用canny
void canny_grad(int num)
{
	Mat src_gray, src_gauss, grad;

	for (int i = 1; i <= num; i++)
	{
		sprintf(filename, "%s\\%d.jpg", "picture", i);
		Mat src = imread(filename);

		//高斯滤波
		GaussianBlur(src, src_gauss, Size(3, 3), 0, 0, BORDER_DEFAULT);
		cvtColor(src_gauss, src_gray, COLOR_BGR2GRAY);

		//不进行高斯去噪
		//cvtColor(src, src_gray, COLOR_BGR2GRAY);

		//采用canny算子计算梯度
		Canny(src_gray, grad, 50, 150, 3);

		//在得到梯度图后就进行高斯滤波，效果很好。有效的去除了在边沿部分的噪声
		GaussianBlur(grad, grad, Size(3, 3), 0, 0, BORDER_DEFAULT);

		//高斯滤波和中值滤波做个对比,没有肉眼可见的变化，两种滤波结果相同
		//medianBlur(grad, grad, 3);

		//保证大小一致，否则不能正确输出
		cvtColor(grad, grad, CV_GRAY2BGR);

		//梯度取反
		Mat grad_oppo = oppo_src(grad);

		//output
		sprintf(filename2, "%s\\%d.jpg", "output", i);
		imwrite(filename2, grad_oppo);
	}
}
/*计算梯度并取反*/

//计算梯度总和
void sum_grad(int num)
{
	Mat sum_src;
	for (int i = 1; i <= num; i++)
	{
		sprintf(filename2, "%s\\%d.jpg", "output", i);
		Mat img = imread(filename2);

		if (i == 1)
			sum_src = img.clone();
		else
			for (int i = 0; i < sum_src.rows; i++)
			{
				for (int j = 0; j < sum_src.cols; j++)
				{
					sum_src.at<Vec3b>(i, j)[0] = img.at<Vec3b>(i, j)[0] + sum_src.at<Vec3b>(i, j)[0];
					sum_src.at<Vec3b>(i, j)[1] = img.at<Vec3b>(i, j)[1] + sum_src.at<Vec3b>(i, j)[1];
					sum_src.at<Vec3b>(i, j)[2] = img.at<Vec3b>(i, j)[2] + sum_src.at<Vec3b>(i, j)[2];
				}
			}
	}

	//在这里加高斯滤波比其他地方的效果要好很多
	GaussianBlur(sum_src, sum_src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	imwrite("./output/sum_src.jpg", sum_src);
}

//计算比例
void cul_scale(int num)
{
	Mat sum_src = imread("./output/sum_src.jpg");
	for (int i = 1; i <= num; i++)
	{
		sprintf(filename2, "%s\\%d.jpg", "output", i);
		Mat img = imread(filename2);

		for (int i = 0; i < sum_src.rows; i++)
		{
			for (int j = 0; j < sum_src.cols; j++)
			{
				img.at<Vec3b>(i, j)[0] = img.at<Vec3b>(i, j)[0] / (sum_src.at<Vec3b>(i, j)[0] * 1.0);
				img.at<Vec3b>(i, j)[1] = img.at<Vec3b>(i, j)[1] / (sum_src.at<Vec3b>(i, j)[1] * 1.0);
				img.at<Vec3b>(i, j)[2] = img.at<Vec3b>(i, j)[2] / (sum_src.at<Vec3b>(i, j)[2] * 1.0);
			}
		}

		imwrite(filename2, img);
	}
}

void mul_src(int num)
{
	Mat src, grad_src;

	for (int i = 1; i <= num; i++)
	{
		sprintf(filename, "%s\\%d.jpg", "picture", i);
		sprintf(filename2, "%s\\%d.jpg", "output", i);
		src = imread(filename);
		grad_src = imread(filename2);

		for (int i = 0; i < src.rows; i++)
		{
			for (int j = 0; j < src.cols; j++)
			{
				grad_src.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0] * grad_src.at<Vec3b>(i, j)[0] % 256;
				grad_src.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1] * grad_src.at<Vec3b>(i, j)[1] % 256;
				grad_src.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2] * grad_src.at<Vec3b>(i, j)[2] % 256;
			}
		}

		sprintf(filename2, "%s\\%d.jpg", "output1", i);
		imwrite(filename2, grad_src);
	}
}

void add_img(int num)
{
	double exp = 1.0 / 2.0;
	double ecx = 1.0 - exp;
	Mat finall;

	Mat img1 = imread("./output1/1.jpg", IMREAD_COLOR);
	Mat img2 = imread("./output1/2.jpg", IMREAD_COLOR);
	Mat img3 = imread("./output1/3.jpg", IMREAD_COLOR);

	addWeighted(img1, exp, img2, exp, 0, finall);

	for (int i = 3; i <= num; i++)
	{
		//等比例参数
		exp = 1.0 / i;
		ecx = 1.0 - exp;


		sprintf(filename, "%s\\%d.jpg", "output1", i);
		img3 = imread(filename);
		/*等比例*/
		addWeighted(finall, ecx, img3, exp, 0, finall);
		/*梯度比例*/
		//addWeighted(finall, exp, img3, exp, 0, finall);
	}

	//存在一些类似椒盐噪声的杂质，尝试使用中值滤波,能有效去除一些黑色杂质。但是降低了图像的清晰度。如何把握一个合适的量
	//medianBlur(finall, finall, 3);

	//在采用自己写的高斯滤波之后，中值滤波显得有些多余了，反而使图片不清楚，弃用，
	//不过中值滤波好歹也谢了半天，留在这儿做个纪念。。。
	//myMedianBlur(finall, finall);


	imwrite("./output1/finall.jpg", finall);
}

int main()
{
	clock_t start, stop;
	double s;
	start = clock();


	int num = 0;
	cout << "请输入需要融合的图片数量";
	cin >> num;

	//求梯度
	//sobel_grad(num);		//采用sobel算子
	//canny_grad(num);		//canny把边描的太重了，不好使
	laplacion_grad(num);	//采用laplacion算子,要比sobel稍微好一些

							//计算梯度的和图
	sum_grad(num);

	//计算每一幅梯度图与梯度和图的比例（写回梯度图）
	cul_scale(num);

	//梯度比例与原图的乘积，写回梯度图
	mul_src(num);

	//得到的个图的比例进行融合
	add_img(num);

	stop = clock();
	s = (stop - start) / CLK_TCK;
	cout << "自实现函数运行时间为：" << s <<"s"<< endl;
	return 0;
}