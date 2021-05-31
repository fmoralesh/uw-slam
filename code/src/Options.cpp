/**
* This file is part of UW-SLAM.
* 
* Copyright 2018.
* Developed by Fabio Morales,
* Email: fabmoraleshidalgo@gmail.com; GitHub: @fmoralesh
*
* UW-SLAM is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* UW-SLAM is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with UW-SLAM. If not, see <http://www.gnu.org/licenses/>.
*/

#include "uw_slam/Options.h"

const int PYRAMID_LEVELS  =  5;
double GRADIENT_THRESHOLD =  20;
int BLOCK_SIZE            =  32;

Options::Options(ros::NodeHandle nh) : nh_(nh) 
{}

// Loading parameters from config/configuration.yml
void Options::loadConfiguration()
{
    nh_.param<int>("/uw_slam/starting_frame", starting_frame_, 0);
    nh_.param<std::string>("/uw_slam/calibration_path", calibration_path_, "");
    nh_.param<std::string>("/uw_slam/dataset_path", dataset_path_, "");
}

const int Options::getStartingFrame()
{
    return starting_frame_;
}

const std::string Options::getCalibrationPath()
{
    return calibration_path_;
}

const std::string Options::getDatasetPath()
{
    return dataset_path_;
}