#include <stdio.h>
#include <iostream>
// Get all OS and signal processing YARP classes
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
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
 	FILE *fpr;
	FILE *fpg;
	FILE *fpb;

	if((fpr = fopen("outr.txt","w")) == NULL){
		std::exit(0);
	}
	if((fpg = fopen("outg.txt","w")) == NULL){
		std::exit(0);
	}
	if((fpb = fopen("outb.txt","w")) == NULL){
		std::exit(0);
	}
    ImageOf<PixelRgb> *image = imagePort.read();  // read an image
    if (image!=NULL) { // check we actually got something
       for (int x=0; x<image->width(); x++) {
         for (int y=0; y<image->height(); y++) {
         	PixelRgb& pixel = image->pixel(x,y);
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
