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


#include <internal/System.h>
#include <internal/Tracker.h>

int main (int argc, char *argv[]) 
{
    // Parameters
    int start_index;
    string images_path;
    string calibration_path;
    string ground_truth_dataset;
    string ground_truth_path;
    string depth_path;

    // Create uw-slam system
    System system(argc, argv, start_index);

    // Calibrates system with certain Camera Model (currently only RadTan) 
    system.Calibration(calibration_path);
    
    // Initialize SLAM system
    system.InitializeSystem(images_path, ground_truth_dataset, ground_truth_path, depth_path);
    
    // Start SLAM process
    // Read images one by one from directory provided
    system.AddFrame(start_index);

    for (int i=start_index+1; i<system.num_valid_images_; i++) 
    {
        system.AddFrame(i);
        system.Tracking();
        system.visualizer_->UpdateMessages(system.previous_frame_);

        
        // Delete oldest frame (keeping 10 frames)
        if (system.num_frames_> 10) {
            system.FreeFrames();
        }

        cout << "Matches: " << system.previous_frame_->n_matches_ << endl;
    }

    cout << "Dataset ended..." << endl;
  
    return 0;
}