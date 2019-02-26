#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/ChannelFloat32.h>

using namespace sensor_msgs;
using namespace message_filters;
CameraInfo str_info;
ros::Publisher image1_pub,can_pub;

void callback(const ImageConstPtr& image1, const CameraInfoConstPtr& image2)
{
  std::cout<<"2\n";
  ROS_INFO("Sync_Callback");

  image1_pub.publish(image1);
  can_pub.publish(image2);

		/*str_info.header.frame_id=std::string("camera");
                str_info.header.stamp = ros::Time::now();
		str_info.P[0]=image2.P[0];
		str_info.K[0]=image2.K[0];
		str_info.K[1]=image2.K[1];
		str_info.K[2]=image2.K[2];
		str_info.K[3]=image2.K[3];
		str_info.K[4]=image2.K[4];
		str_info.K[5]=image2.K[5];*/

}

int main(int argc, char** argv)
{ std::cout<<"\n 1";
  ros::init(argc, argv, "vision_node");

  ros::NodeHandle nh;

  message_filters::Subscriber<Image> image1_sub(nh, "/camera/image_raw", 1);
  message_filters::Subscriber<CameraInfo> image2_sub(nh, "/can_str", 1);
  
  image1_pub = nh.advertise<Image>("/synchronized_image_raw", 1000);
  can_pub = nh.advertise<CameraInfo>("/synchronized_can", 1000);


  typedef sync_policies::ApproximateTime<Image, CameraInfo> MySyncPolicy;
  // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(100), image1_sub, image2_sub);
  std::cout<<"\n 5 \n";
 sync.registerCallback(boost::bind(&callback, _1, _2));
 

   ros::spin();
   std::cout<<"7 \n";

  return 0;
}
