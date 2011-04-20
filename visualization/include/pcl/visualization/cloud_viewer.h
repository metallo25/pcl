/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *
 */
#ifndef PCL_CLOUD_VIEWER_H_
#define PCL_CLOUD_VIEWER_H_

#include <pcl/visualization/pcl_visualizer.h> //pcl vis
#include <pcl/point_cloud.h> //basic pcl includes
#include <pcl/point_types.h>

#include <boost/function.hpp>

#include <string>

namespace pcl
{
  namespace visualization
  {
    /** \brief Simple point cloud visualization class
      * \author Ethan Rublee
      * \ingroup visualization
      */
    class CloudViewer
    {
      public:
        typedef pcl::PointCloud<pcl::PointXYZRGB> ColorCloud;
        typedef pcl::PointCloud<pcl::PointXYZ> GrayCloud;

        /** \brief Construct a cloud viewer, with a window name.
         * \param window_name This is displayed at the top of the window
         */
        CloudViewer (const std::string& window_name);

        /** \brief Will quit the window,
         * and release all resources held by the viewer.
         * @return
         */
        ~CloudViewer ();

        /** \brief Show a cloud, with an optional key for multiple clouds.
         * \param cloud RGB point cloud
         * \param cloudname a key for the point cloud, use the same name if you would like to overwrite the existing cloud.
         */
        void
        showCloud (const ColorCloud::ConstPtr &cloud, const std::string& cloudname = "cloud");

        /** \brief Show a cloud, with an optional key for multiple clouds.
         *  \param cloud XYZ point cloud
         *  \param cloudname a key for the point cloud, use the same name if you would like to overwrite the existing cloud.
         */
        void
        showCloud (const GrayCloud::ConstPtr &cloud, const std::string& cloudname = "cloud");


        /** \brief Check if the gui was quit, you should quit also
         * \param millis_to_wait This will request to "spin" for the number of milliseconds, before exiting.
         * \return true if the user signaled the gui to stop
         */
        bool
        wasStopped (int millis_to_wait = 1);

        /** Visualization callable function, may be used for running things on the UI thread.
         */
        typedef boost::function1<void, pcl::visualization::PCLVisualizer&> VizCallable;

        /** \brief Run a callbable object on the UI thread. Will persist until removed
         * @param x Use boost::ref(x) for a function object that you would like to not copy
         * \param key The key for the callable -- use the same key to overwrite.
         */
        void
        runOnVisualizationThread (VizCallable x, const std::string& key = "callable");

        /** \brief Run a callbable object on the UI thread. This will run once and be removed
         * @param x Use boost::ref(x) for a function object that you would like to not copy
         */
        void
        runOnVisualizationThreadOnce (VizCallable x);

        /** \brief Remove a previously added callable object, NOP if it doesn't exist.
         * @param key the key that was registered with the callable object.
         */
        void
        removeVisualizationCallable (const std::string& key = "callable");
      private:

        //these aren't ready for prime time.
        /** \brief Show a cloud, with an optional key for multiple clouds.
          * \param cloud RGB point cloud
          * \param cloudname a key for the point cloud, use the same name if you would like to overwrite the existing cloud.
          */
         void
         showCloudNonBlocking (const ColorCloud::ConstPtr &cloud, const std::string& cloudname = "cloud");

         /** \brief Show a cloud, with an optional key for multiple clouds.
          *  \param cloud XYZ point cloud
          *  \param cloudname a key for the point cloud, use the same name if you would like to overwrite the existing cloud.
          */
         void
         showCloudNonBlocking (const GrayCloud::ConstPtr &cloud, const std::string& cloudname = "cloud");

        CloudViewer (const CloudViewer &rhs);//don't copy me for now!

        void
        operator= (const CloudViewer &rhs);//don't copy me for now!

        /** \brief Private implementation. */
        class CloudViewer_impl;
        boost::shared_ptr<CloudViewer_impl> impl_;
    };
  }
}

#endif /* CLOUD_VIEWER_H_ */
