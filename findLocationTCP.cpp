#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

// Get all OS and signal processing YARP classes
#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#define WIDTH 640
#define HEIGHT 480

using namespace yarp::sig;

int main() {
	
  	yarp::os::Network yarp; // set up yarp
  	yarp::os::BufferedPort<yarp::sig::ImageOf< yarp::sig::PixelRgb > > imagePort;  // make a port for reading images
  	imagePort.open("/tutorial/image/in");  // give the port a name
  	yarp::os::Network::connect("/icubGazeboSim/cam/left","/tutorial/image/in");
    char sendData[WIDTH*3*HEIGHT*4+100] = {0};
    yarp::sig::ImageOf< yarp::sig::PixelRgb > *image = imagePort.read();  // read an image
	std::string s;
	///////
	if (image!=NULL) { // check we actually got something
       for (int x=0; x<image->width(); x++) {
		for (int y=0; y<image->height(); y++) {
			PixelRgb& pixel = image->pixel(x,y);
			s+= (std::to_string(pixel.r)+" ");
			s+= (std::to_string(pixel.g)+" ");
			s+= (std::to_string(pixel.b)+" ");
       }
    }
	std::cout << s.size() << std::endl;
	std::string host="127.0.0.1";
	int port = 23333;
	boost::asio::io_service ios;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
    boost::asio::ip::tcp::socket socket(ios);
	socket.connect(endpoint);
	boost::array<char, WIDTH*3*HEIGHT*4+100> buf;
	std::cout << buf.end() << std::endl;
    std::copy(s.begin(),s.end(),buf.begin());
	boost::system::error_code error;
	//socket.write_some(boost::asio::buffer(buf, s.size()), error);
    
	boost::asio::write(socket,boost::asio::buffer(s), error);
	std::cout << error << std::endl;
	socket.close();
  }
  return 0;
}

