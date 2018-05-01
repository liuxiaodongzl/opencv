/*
基于任务3，只对检测到的人脸区域做高斯模糊处理，将结果保存为一个视频文件
*/
#include <opencv2\opencv.hpp>  
using namespace cv;
using namespace std;
void processimageGaosi(Mat &frame);
int main()
{
	Mat frame;
	//读取视频或摄像头
	VideoCapture capture(0);

	//读取人脸数据
	CascadeClassifier stFaceCascade;
	if (!stFaceCascade.load("C:\\Users\\lenovo\\Downloads\\opencv\\opencv\\sources\\data\\lbpcascades\\lbpcascade_frontalface.xml"))
	{
		printf("Loading cascade error\n");
		return -1;
	}
	//视频保存
	VideoWriter writer("D:\\faceblur.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));


	//处理视频
	while (true)
	{

		capture >> frame;

		if (!frame.empty()) {
			//frame经过检测算法 
			IplImage* transIplimage = cvCloneImage(&(IplImage)frame);
			std::vector<Rect> faceRects;//矩形描绘

			stFaceCascade.detectMultiScale(transIplimage,
				faceRects,            //检出结果  
				1.1,                  //缩放步长  
				2,                    //框融合时的最小检出个数  
				0 | CV_HAAR_SCALE_IMAGE,//标志 |CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_DO_ROUGH_SEARCH|CV_HAAR_DO_CANNY_PRUNING  
				Size(100, 100),         //最小人脸尺寸  
				Size(500, 500));     //最大人脸尺寸  
			printf("Face Num[%d]\n", faceRects.size());

			for (unsigned int j = 0; j < faceRects.size(); j++)
			{
				//画矩形图片， 左上角， 右下角， 颜色， 线条粗细， 线条类型，点类型  
				cvRectangle(transIplimage,
					cvPoint(faceRects[j].x, faceRects[j].y),
					cvPoint(faceRects[j].x + faceRects[j].width, faceRects[j].y + faceRects[j].height),
					cvScalar(0, 255, 0),
					2, 8, 0);
				//矩形区域高斯模糊  
				//截取指定区域：
				/*	IplImage* result=NULL;//截取的图像
				CvSize size = cvSize(faceRects[j].width, faceRects[j].height);//区域大小

				//将ROI区域图像保存在result中:左上角x、左上角y、矩形长、宽
				cvSetImageROI(result, cvRect(faceRects[j].width+10, faceRects[j].height+10, size.width, size.height));//设置源图像ROI

				IplImage* pDest = cvCreateImage(size, transIplimage->depth, transIplimage->nChannels);//创建目标图像
				cvCopy(result, pDest); //复制图像 yuan mudi
				cvResetImageROI(pDest);//源图像用完后，清空ROI
				//截取图像进行高斯模糊
				processimageGaosi((Mat)pDest);
				imshow("asd", (Mat)pDest);
				//结果覆盖到源图像上去
				Rect roi_rect = Rect(faceRects[j].x, faceRects[j].y, faceRects[j].width, faceRects[j].height);//源图像的坑*/

				Mat image = (Mat)transIplimage;//整张图
				Rect rect(faceRects[j].x, faceRects[j].y, faceRects[j].width, faceRects[j].height);//选中指定区域
				Mat image_roi = image(rect);//选出感兴趣的区域
											//截取图像高斯处理
				processimageGaosi(image_roi);
				imshow("asdd", image_roi);
				//将感兴趣区域图像处理结果粘贴到原位置
				image_roi.copyTo(image_roi);
				writer << image;
			}
			imshow("window", (Mat)transIplimage);
		}


		if (waitKey(30) == 27)   //延时30
			break;

	}
	return 0;
}
void processimageGaosi(Mat &frame)
{
	//高斯滤波
	GaussianBlur(frame, frame, Size(99, 99), 0, 0);
	/*
	函数原型：  void GaussianBlur( InputArray src, OutputArray dst, Size ksize,
	double sigmaX, double sigmaY = 0,
	int borderType = BORDER_DEFAULT );
	参数详解：
	InputArray src-----源图像
	OutputArray dst-----目标图像
	Size ksize----高斯内核大小，其中ksize.width和ksize.height可以不同，但是必须为正数
	和奇数，也可为零，均有sigma计算而来。
	double sigmaX----表示高斯函数在X方向的标准偏差
	double sigmaY---- 表示高斯函数在Y方向的标准偏差
	若sigma为零，就将它设为sigmaX,如果两者均为零，就由ksize.width
	和ksize.height计算出来。
	int borderType -----用于推断图像外部像素的某种边界模式。
	默认值 BORDER_DEFAULT           *
	*/
}
