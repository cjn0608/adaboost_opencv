#include <ros_node/ros_node_node.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/ml/ml.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace Ros_node;
ros_node::ros_node()
{
    nh_private_ = ros::NodeHandle("~");
}
int main (int argc, char **argv)
{
    ros::init(argc, argv, "ros_node_node");
    float trainingData[42][2]={	{40, 55},{35, 35},{55, 15},{45, 25},{10, 10},{15, 15},{40, 10},
                  {30, 15},{30, 50},{100, 20},{45, 65},{20, 35},{80, 20},{90, 5},
                  {95, 35},{80, 65},{15, 55},{25, 65},{85, 35},{85, 55},{95, 70},
                  {105, 50},{115, 65},{110, 25},{120, 45},{15, 45},
                  {55, 30},{60, 65},{95, 60},{25, 40},{75, 45},{105, 35},{65, 10},
                  {50, 50},{40, 35},{70, 55},{80, 30},{95, 45},{60, 20},{70, 30},
                  {65, 45},{85, 40}	};
      Mat trainingDataMat(42, 2, CV_32FC1, trainingData);
      //训练样本的响应值
      float responses[42] = {'R','R','R','R','R','R','R','R','R','R','R','R','R','R','R','R',
                  'R','R','R','R','R','R','R','R','R','R',
                'B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B'	};
      Mat responsesMat(42, 1, CV_32FC1, responses);

      float priors[2] = {1, 1};    //先验概率
      CvBoostParams params( CvBoost::REAL, // boost_type
                              10, // weak_count,表示弱分类器的数量，即迭代的次数
                              0.95, // weight_trim_rate,表示裁剪率，
                                    //在0～1之间，默认值为0.95，在迭代过程中，那些归一化后的样本权值wi(m)小于该裁剪率的样本将不进入下次迭代
                              15, // max_depth,表示构建决策树的最大深度
                              false, // use_surrogates,表示在构建决策树时，是否使用替代分叉属性
                              priors // priors,样本的先验概率
                              );

      CvBoost boost;
      boost.train (	trainingDataMat,
              CV_ROW_SAMPLE,
              responsesMat,
              Mat(),
              Mat(),
              Mat(),
              Mat(),
              params
                );
      //预测样本
      float myData[2] = {55, 25};
      Mat myDataMat(2, 1, CV_32FC1, myData);
      double r = boost.predict( myDataMat );

      cout<<endl<<"result:  "<<(char)r<<endl;
      return 0;
}


















