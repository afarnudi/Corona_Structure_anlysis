//
//  Cluster_detection_with_mask.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 25/06/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include <stdio.h>
#include "tomo.h"
#include "Hoshen_kopelman_functions.hpp"

void tomo::Hoshen_Kopelman_cluster_mask(int cluster_threshold, bool write_status){
    vector< int > Cluster_size;
    vector<vector<vector<int> > > coloured_voxels;
    Hoshen_Kopelman_3D(coloured_voxels, Cluster_size);
    
    write_cluster_info(Cluster_size);
    
    if (cluster_threshold!=0) {
        //        HK_threshold_mask(coloured_voxels, cluster_threshold, Cluster_size);
        HK_mask(coloured_voxels, cluster_threshold, Cluster_size);
    }
    if (write_status) {
        voxels=coloured_voxels;
    }
}

void tomo::Hoshen_Kopelman_cluster_mask(int min_cluster_size, int max_cluster_size, bool write_status){
    vector< int > Cluster_size;
    vector<vector<vector<int> > > coloured_voxels;
    Hoshen_Kopelman_3D(coloured_voxels, Cluster_size);
    
    write_cluster_info(Cluster_size);
    
    HK_mask(coloured_voxels, min_cluster_size, max_cluster_size, Cluster_size);
    
    if (write_status) {
        voxels=coloured_voxels;
    }
}
