#include"CvxText.h"  

int main(int argc, char *argv[])
{\
	IplImage *img = cvLoadImage("C:\\Users\\lenovo\\Pictures\\Camera Roll\\0.jpg");
	{
		CvxText text("C:\\Windows\\Fonts\\simhei.ttf");
		const char *msg = "ÁõÐ¡¶« 631507030118";
		float p = 0.5;
		text.setFont(NULL, NULL, NULL, &p);
		text.putText(img, msg, cvPoint(300, 300), CV_RGB(255,0, 0));
	}
	cvShowImage("test", img); cvWaitKey(-1);
	cvReleaseImage(&img);
	return 0;
}