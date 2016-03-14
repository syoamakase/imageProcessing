#include <stdio.h>
#include <stdlib.h>
// Get all OS and signal processing YARP classes
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
int main() {
  Network yarp; // set up yarp
  BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
  imagePort.open("/tutorial/image/in");  // give the port a name
  Network::connect("/icubGazeboSim/cam/left","/tutorial/image/in");
  unsigned int datar = 0;
  unsigned int datag = 0;
  unsigned int datab = 0;
  //while (1) { // repeat forever
	FILE *fpr;
	FILE *fpg;
	FILE *fpb;

	if((fpr = fopen("outr.txt","w")) == NULL){
		//exit(0);
	}
	if((fpg = fopen("outg.txt","w")) == NULL){
		//exit(0);
	}
	if((fpb = fopen("outb.txt","w")) == NULL){
		//exit(0);
	}
    ImageOf<PixelRgb> *image = imagePort.read();  // read an image
    if (image!=NULL) { // check we actually got something
       //printf("We got an image of size %dx%d\n", image->width(), image->height());
       double xMean = 0;
       double yMean = 0;
       int ct = 0;
       //printf("%s\n",image->getRawImage());
       for (int x=0; x<image->width(); x++) {
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
	    	datar = pixel.r;
		    datag = pixel.g;
		    datab = pixel.b;
		    fprintf(fpr,"%d ",datar);	
		    fprintf(fpg,"%d ",datag);
		    fprintf(fpb,"%d ",datab);
           }
         }
       
    fclose(fpr);
    fclose(fpg);
    fclose(fpb); 
  }
  return 0;
}
