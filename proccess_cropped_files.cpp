//
//  proccess_cropped_files.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 11/07/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include "tomo.h"
#include "Cluster.h"
#include "sphere_mask_gen.hpp"

void build_cluster_list(vector<Cluster> &Cluster, vector<vector<vector<int> > > coloured_voxels, int cluster_size);

void tomo::process_cropped_voxel(vector<vector<int> > &sphere_centre_coordinates, int sphere_radius, int crop_size){
    
    vector<vector<int> > mask_coordinates;
    sphere_mask_generator(mask_coordinates, sphere_radius, crop_size);
    
    for (int count=0; count<sphere_centre_coordinates.size(); count++) {
        crop_sphere_coordinates(sphere_centre_coordinates, crop_size, mask_coordinates, count);
        
        string cropped_file_name="cropped_"+to_string(count);
        cout<<cropped_file_name<<endl;
        
        
        vector< int > Cluster_size;
        vector<Cluster> Cluster;
        vector<vector<vector<int> > > coloured_voxels;
        
        Hoshen_Kopelman_3D(coloured_voxels, Cluster_size, crop_size);
        
        build_cluster_list(Cluster, coloured_voxels, Cluster_size.size());
        write_cluster_info(Cluster, crop_size, cropped_file_name);
        
//        save_tomo_sequence(cropped_file_name, cropped_voxel);
        save_tomo_sequence(cropped_file_name, cropped_voxel, sphere_radius);
        
    }
}

void build_cluster_list(vector<Cluster> &Cluster, vector<vector<vector<int> > > coloured_voxels, int cluster_size){
    Cluster.resize(cluster_size);
    for (int k=1; k<coloured_voxels.size(); k++) {
        for (int j=1; j<coloured_voxels[1].size(); j++) {
            for (int i=1; i<coloured_voxels[1][1].size(); i++) {
                Cluster[coloured_voxels[k][j][i]].add_voxel(k, j, i);
            }
        }
    }
    for (int i=0; i<Cluster.size(); i++) {
        if (Cluster[i].return_size()==0) {
            Cluster.erase(Cluster.begin()+i);
            i--;
        }
    }
    
}
