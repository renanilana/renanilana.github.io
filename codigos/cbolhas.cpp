#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  int width, height, nbolhas, nburacos;
  
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;


imshow("imagem original", image);
  waitKey();

//tira bolhas da borda

for (int j=0; j<width; j++){ //bordas de cima e de baixo
  if(image.at<uchar>(0,j) == 255) {
   p.x= j;
   p.y= 0;
   floodFill(image,p,0); //preenche com preto
}

 if(image.at<uchar>(height-1,j) == 255) {
   p.x= j;
   p.y= height-1;
   floodFill(image,p,0);
}
}

for (int i=0; i<height; i++){ //bordas das laterais
  if(image.at<uchar>(i,0) == 255) {
   p.x= 0;
   p.y= i;
   floodFill(image,p,0);
}

 if(image.at<uchar>(i,width-1) == 255) {
   p.x= width-1;
   p.y= i;
   floodFill(image,p,0);
}
}


imshow("imagem sem bordas", image);
waitKey();

//conta todas as bolhas e pinta de tons de cinza

  nbolhas=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
		// achou uma bolha
		nbolhas++;
		p.x=j;
		p.y=i;
		floodFill(image,p, nbolhas);

	  }
	}
  }


imshow("bolhas cinzas", image);
waitKey();


//preenche o fundo com "branco"

p.x=0;
p.y=0;
if (image.at<uchar>(p) == 0)
floodFill(image,p,254);

//conta bolhas com buracos
int bu=0;
nburacos=0;
 for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
	if(image.at<uchar>(i,j) ==0  && (int)image.at<uchar>(i,j-1)>nburacos){
               nburacos++;
                p.x=j-1;
		p.y=i;
		floodFill(image,p,nburacos);}
if  (image.at<uchar>(i,j) ==0)
bu++;

}}

imshow("imagem fim", image);
 // imwrite("labeling.png", image);
  waitKey();

cout << "Total de bolhas: "<<nbolhas << endl<<"Bolhas com buracos: "<<nburacos<<endl <<bu;

  return 0;


}
