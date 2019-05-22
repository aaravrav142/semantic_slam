#include <ps_graph_slam/keyframe.hpp>

#include <boost/filesystem.hpp>

#include <pcl/io/pcd_io.h>
#include <g2o/types/slam3d/vertex_se3.h>

namespace hdl_graph_slam {

KeyFrame::KeyFrame(const ros::Time& stamp,
                   const Eigen::Isometry3d& odom, const Eigen::Isometry3d &robot_pose,
                   const Eigen::MatrixXf& odom_cov,
                   double accum_distance,
                   const sensor_msgs::PointCloud2& cloud_msg,
                   std::vector<semantic_SLAM::ObjectInfo>& obj_info)
    : stamp(stamp),
      odom(odom),
      robot_pose(robot_pose),
      odom_cov(odom_cov),
      accum_distance(accum_distance),
      cloud_msg(cloud_msg),
      obj_info(obj_info),
      node(nullptr)
{}

KeyFrame::~KeyFrame() {

}


void KeyFrame::dump(const std::string& directory) {
    if(!boost::filesystem::is_directory(directory)) {
        boost::filesystem::create_directory(directory);
    }

    std::ofstream ofs(directory + "/data");
    ofs << "stamp " << stamp.sec << " " << stamp.nsec << "\n";

    ofs << "odom\n";
    ofs << odom.matrix() << "\n";

    ofs << "accum_distance " << accum_distance << "\n";

    if(floor_coeffs) {
        ofs << "floor_coeffs " << floor_coeffs->transpose() << "\n";
    }

    if(node) {
        ofs << "id " << node->id() << "\n";
    }

    //pcl::io::savePCDFileBinary(directory + "/cloud.pcd", *cloud);

}


}