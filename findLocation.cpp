#include <stdio.h>
// Get all OS and signal processing YARP classes
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <iostream>
#include <fstream>
using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
int main() {
  Network yarp; // set up yarp
  BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
  imagePort.open("/tutorial/image/in");  // give the port a name
  Network::connect("/icubGazeboSim/cam/left","/tutorial/image/in");
  int data[480][640];
  //while (1) { // repeat forever
    ImageOf<PixelRgb> *image = imagePort.read();  // read an image
    if (image!=NULL) { // check we actually got something
       //printf("We got an image of size %dx%d\n", image->width(), image->height());
       double xMean = 0;
       double yMean = 0;
       int ct = 0;
       ofstream fout;
       fout.open("file.out", ios::out|ios::binary|ios::trunc);
       fout.write(image->getRawImage(),480*640*3);
       fout.close();
       //printf("%s\n",image->getRawImage());

       /*for (int x=0; x<image->width(); x++) {
         for (int y=0; y<image->height(); y++) {
           PixelRgb& pixel = image->pixel(x,y);
           // very simple test for blueishness
           // make sure blue level exceeds red and green by a factor of 2
           //if (pixel.b>pixel.r*1.2+10 && pixel.b>pixel.g*1.2+10) {
            // there's a blueish pixel at (x,y)!
            // let's find the average location of these pixels
            //xMean += x;
            //yMean += y;
            //ct++;i
	    //printf("%d ",pixel.b);
           }
	  printf("\n");
         }
       }*/
       /*if (ct>0) {
         xMean /= ct;
         yMean /= ct;
       }
       if (ct>(image->width()/20)*(image->height()/20)) {
         printf("Best guess at blue target: %g %g\n", xMean, yMean);
       }*/
    
 // }
  return 0;
}
