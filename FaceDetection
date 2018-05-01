/*
使用opencv打开摄像头，将摄像头对准人脸，
学习opencv自带face-detection范例代码，编程实现人脸检测；
在检测到的人脸区域，画一个红色圆圈，将最终结果保存为一个视频文件。
*/
#include <opencv2\opencv.hpp>  
using namespace cv;
using namespace std;
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
	VideoWriter writer("D:\\face.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));


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
				cvRectangle(transIplimage,
					cvPoint(faceRects[j].x, faceRects[j].y),
					cvPoint(faceRects[j].x + faceRects[j].width, faceRects[j].y + faceRects[j].height),
					cvScalar(0, 255, 0),
					2, 8, 0);
				writer << transIplimage;
			}
			imshow("window", (Mat)transIplimage);
		}
		if (waitKey(30) == 27)   //延时30
			break;
	}
	return 0;
}
