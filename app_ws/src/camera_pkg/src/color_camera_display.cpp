#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>

// 回调函数用于处理color图像数据
void colorImageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try
    {
        // 将ROS图像消息转换为OpenCV图像格式
        cv::Mat color_image = cv_bridge::toCvShare(msg, "bgr8")->image;

        // 显示color图像
        cv::imshow("Color Image", color_image);
        cv::waitKey(1);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}

// 回调函数用于处理depth图像数据
void depthImageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try
    {
        // 将ROS图像消息转换为OpenCV图像格式
        cv::Mat depth_image = cv_bridge::toCvShare(msg)->image;

        // 显示depth图像
        cv::imshow("Depth Image", depth_image);
        cv::waitKey(1);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_display_node");
    ros::NodeHandle nh;

    // 创建一个用于显示color图像的窗口
    cv::namedWindow("Color Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("Color Image", 640, 480);

    // 创建一个用于显示depth图像的窗口
    cv::namedWindow("Depth Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("Depth Image", 640, 480);

    // 创建image_transport对象
    image_transport::ImageTransport it(nh);

    // 订阅color图像话题，指定回调函数
    image_transport::Subscriber color_image_sub = it.subscribe("/camera/color/image_raw", 1, colorImageCallback);

    // 订阅depth图像话题，指定回调函数
    image_transport::Subscriber depth_image_sub = it.subscribe("/camera/depth/image_rect_raw", 1, depthImageCallback);

    // 循环处理ROS消息
    ros::spin();

    // 关闭窗口
    cv::destroyAllWindows();

    return 0;
}

