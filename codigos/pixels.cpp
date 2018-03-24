#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main(int, char**){
  Mat image,  aux1, aux2;
//int aux1,aux2;
  

  int linha, coluna; //mlinha, mcoluna;
  linha = image.size().height;
  coluna = image.size().width;
//  mlinha = linha/2;
  //mcoluna = coluna/2;

  image= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data){
    cout << "nao abriu biel.png" << endl;}


  imshow("janela", image);
  wait();

  for(int i=0;i<linha/2;i++){
    for(int j=0;j<coluna/2;j++){
   
//image.at<uchar>(i,j)=aux.at<uchar>(i,j);

aux1.at<uchar>(i,j) = image.at<uchar>(i,j);
aux2.at<uchar>(linha/2+i,coluna/2+j)= image.at<uchar>(linha/2+i,coluna/2+j);
 
image.at<uchar>(i,j) = aux2.at<uchar>(linha/2+i,coluna/2+j);
image.at<uchar>(linha/2+i,coluna/2+j) = aux1.at<uchar>(i,j);

aux1.at<uchar>(linha/2+i,j)= image.at<uchar>(linha/2+i,j);
aux2.at<uchar>(i,coluna/2+j)= image.at<uchar>(i,coluna/2+j);

image.at<uchar>(linha/2 +i,j) = aux2.at<uchar>(i,coluna/2+j);
image.at<uchar>(i,coluna/2 +j)= aux1.at<uchar>(linha/2+i,j);





//  aux1= image.at<uchar>(linha/2+i,coluna/2+j);
  //aux2= image.at<uchar>(i,j);
  //image.at<uchar>(i,j) = aux1; 2
  //image.at<uchar>(linha/2+i,coluna/2+j)=aux2;4
  
//aux1= image.at<uchar>(linha/2+i,j);
  //aux2= image.at<uchar>(i,coluna/2+j);
//image.at<uchar>(i,coluna/2 +j)=aux1;
  //image.at<uchar>(linha/2 +i,j) = aux2;  

    }
  }

  imshow("janela-trocada", image);  
waitKey();
  

  return 0;
}
