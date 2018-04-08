
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath> 

using namespace cv;
using namespace std;

double alfa;

// POSICAO
int center_slider=0;
int center_slider_max=100;
// DECAIMENTO
int alfa_slider = 0;
int alfa_slider_max = 100;
// ALTURA
int top_slider = 0;
int top_slider_max = 100;
Mat image1, image2, blended;
Mat imageTop;

char TrackbarName[50];

void on_trackbar_blend(int, void*){
 alfa = (double) alfa_slider/alfa_slider_max ;
 addWeighted( image2, alfa, imageTop, 1-alfa, 0.0, blended);
 imshow("addweighted", blended);
}

void on_trackbar_line(int, void*){
  image2.copyTo(imageTop);
  
  Size tamanho = image2.size();

  int largura = tamanho.width;
  int altura = tamanho.height;
  int limit = top_slider*altura/100;
  int base = center_slider*altura/100;

 
  if(limit > 0){

    
    if(base >= 0 && base <= altura-limit){
      Mat tmp = image1(Rect(0, base, largura,limit));
      tmp.copyTo(imageTop(Rect(0, base, largura,limit)));
    }

    else{
      Mat tmp = image1(Rect(0, 0, largura,limit));
      tmp.copyTo(imageTop(Rect(0, 0, largura,limit)));
    }
  }

  on_trackbar_blend(alfa_slider,0);
}

int main(int argvc, char** argv){
  image1 = imread("aero.jpg");
  resize(image1,image1,Size(640,480));
  image1.copyTo(image2);
  namedWindow("addweighted", 1);
  image2.convertTo(image2,CV_32F);
  //filtro media--------------------------------------------
  float media[]={1,1,1,
               1,1,1,
               1,1,1};
  Mat mascara;
  mascara = Mat(3,3,CV_32F,media);
  scaleAdd(mascara, 1/9.0, Mat::zeros(3,3,CV_32F), mascara);
  //--------------------------------------------------------

  for (int i = 0; i < 7; i++) {
        filter2D(image2, image2, image2.depth(), mascara, Point(1,1), 0);
  }
  image2.convertTo(image2, CV_8U);
  image2.copyTo(imageTop);
  sprintf( TrackbarName, "Decaimento x %d", alfa_slider_max );
  createTrackbar( TrackbarName, "addweighted",
          &alfa_slider,
          alfa_slider_max,
          on_trackbar_blend );
  on_trackbar_blend(alfa_slider, 0 );
  
  sprintf( TrackbarName, "Altura x %d", top_slider_max );
  createTrackbar( TrackbarName, "addweighted",
          &top_slider,
          top_slider_max,
          on_trackbar_line );
  on_trackbar_line(top_slider, 0 );

  sprintf( TrackbarName, "Posição x %d", top_slider_max );
  createTrackbar( TrackbarName, "addweighted",
          &center_slider,
          center_slider_max,
          on_trackbar_line );
  on_trackbar_line(center_slider, 0 );

  waitKey(0);
  imwrite("tiltshift.png", blended);
  return 0;
}
