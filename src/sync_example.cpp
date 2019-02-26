#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/ChannelFloat32.h>

using namespace sensor_msgs;
using namespace message_filters;

void callback(const ImageConstPtr& image1, const CameraInfoConstPtr& image2)
{
  std::cout<<"2\n";
  std::cout<<image1<<"\n";
}

int main(int argc, char** argv)
{ std::cout<<"\n 1";
  ros::init(argc, argv, "vision_node");

  ros::NodeHandle nh;

  message_filters::Subscriber<Image> image1_sub(nh, "/camera/image_raw", 1);
  message_filters::Subscriber<CameraInfo> image2_sub(nh, "/can_str", 1);

  typedef sync_policies::ApproximateTime<Image, CameraInfo> MySyncPolicy;
  // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(100), image1_sub, image2_sub);
  std::cout<<"\n 5 \n";
 sync.registerCallback(boost::bind(&callback, _1, _2));
 std::cout<<"6 \n";

   ros::spin();
   std::cout<<"7 \n";

  return 0;
}
