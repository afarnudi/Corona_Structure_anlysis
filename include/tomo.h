//
//  tomo.h
//  GPC-code
//
//  Created by Ali Farnudi on 24/12/2012.
/*
 Copyright 2012
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GPC_code__tomo__
#define __GPC_code__tomo__
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <cmath>
#include "Chain.h"
#include <iomanip>
#include <sstream>
#include "Cluster.h"


using namespace std;
//class tomo can read a xxx.vol file, binerize or make any modifications to each voxel of the xxx.vol file, and it will save it as binary file
class tomo{
    string file_name;// stores the file name needed for reading and saving the voxels
    
    int gray_level;
    
//    double* hist;//histogram
    vector<int> hist;
    
    int k_threshold;// the threshold for binerizing the voxels
    
    int x_dim, y_dim, z_dim;//used to initialize the dimentions of the voxel
    
    vector<vector<vector<int> > > voxels;//a 3D vector used to store the voxels
    vector<vector<vector<int> > > accumulator_in_eros;//this accumulator temporarily store the information needed for erosion
    vector<vector<vector<int> > > accumulator;
    vector<vector<vector<int> > > mini_accumulator;//This accumulator is used to store the data from the modified Hough transformation used for detecting chain links in find_chain_3
    vector<vector<vector<int> > > cropped_voxel;
    vector<monomer> position; //this list store all the found monomer positions
    
    
    //members:
    void Hoshen_Kopelman_3D(vector<vector<vector<int> > > &coloured_voxels, vector< int > &Cluster_size);
    void Hoshen_Kopelman_3D(vector<vector<vector<int> > > &coloured_voxels, vector< int > &Cluster_size, int crop_size);
    void HK_initilise_couloured_voxel(vector<vector<vector<int> > > &coloured_voxels);
    void HK_initilise_couloured_voxel(vector<vector<vector<int> > > &coloured_voxels, int crop_size);
    
    void HK_mask(vector<vector<vector<int> > > &coloured_voxels, int cluster_threshold, vector< int > Cluster_size);
    void HK_mask(vector<vector<vector<int> > > &coloured_voxels, int min_cluster_size, int max_cluster_size, vector< int > Cluster_size);
    void write_cluster_info(vector< int > Cluster_size);
    void write_cluster_info(vector<Cluster> Cluster, int crop_size, string cropped_file_name);
    
    
    
public:
    //constructers
    tomo(int x, int y, int z){
        x_dim=x;
        y_dim=y;
        z_dim=z;
        gray_level=65535;
        hist.resize(gray_level,0);
        //creats a voxel with the given dimentions and sets all voxels to zero==================================
        voxels.resize(z_dim);
        for (int k=0; k<z_dim; k++) {
            voxels[k].resize(x_dim);
            for (int i=0; i<x_dim; i++) {
                voxels[k][i].resize(y_dim);
                for (int j=0; j<y_dim; j++) {
                    voxels[k][i][j]=0;
                }
            }
        }
        cout<<"class initialised"<<endl;
    }
    
    tomo(int x, int y, int z, string file_name){
        x_dim=x;
        y_dim=y;
        z_dim=z;
        gray_level=255;
        hist.resize(gray_level,0);
        //creats a voxel with the given dimentions and sets all voxels to zero==================================
        voxels.resize(z_dim);
        for (int k=0; k<z_dim; k++) {
            voxels[k].resize(x_dim);
            for (int i=0; i<x_dim; i++) {
                voxels[k][i].resize(y_dim);
            }
        }
        //now we use the "read_tomo" method to read a xxx.vol file from a the given location
        read_tomo_sequence(file_name);
        cout<<"class initialized"<<endl;
    }
    
    tomo(int x, int y, int z, string file_name, int grey_lev){
        x_dim=x;
        y_dim=y;
        z_dim=z;
        gray_level=grey_lev;
        hist.resize(gray_level,0);
        //creats a voxel with the given dimentions and sets all voxels to zero==================================
        voxels.resize(z_dim);
        for (int k=0; k<z_dim; k++) {
            voxels[k].resize(y_dim);
            for (int j=0; j<y_dim; j++) {
                voxels[k][j].resize(x_dim);
            }
        }
        //now we use the "read_tomo" method to read a xxx.vol file from a the given location
        if (z_dim!=1) {
            read_tomo_sequence(file_name);
        } else {
            read_2D_image(file_name);
        }
        
        cout<<"class initialized"<<endl;
    }
    //copy constructers
    tomo(tomo &o){
        x_dim=o.x_dim;
        y_dim=o.y_dim;
        z_dim=o.z_dim;
        for (int k=0; k<z_dim; k++) {
            for (int i=0; i<x_dim; i++) {
                for (int j=0; j<y_dim; j++) {
                    int voxel_temp=o.voxels[k][i][j];
                    voxels[k][i][j]=voxel_temp;
                }
            }
        }
    }
    
    //reads and stores the voxels from the given location
    void read_tomo_bin(string file_name);
    void read_tomo_sequence(string file_name);
    void read_2D_image(string file_name);
    
    void neighbour_voxel_2D_counter(void);
    void neighbour_voxel_3D_counter(void);
    
    
    
    
    void Hoshen_Kopelman_cluster_mask(int cluster_threshold, bool write_status);
    void Hoshen_Kopelman_cluster_mask(int min_cluster_size, int max_cluster_size, bool write_status);
    
    //saves a file to a given location
    void save_tomo_bin(string file_name);
    void save_tomo_sequence(string file_name);
    void save_tomo_sequence(string file_name, vector<vector<vector<int> > > coloured_voxels);
    void save_tomo_sequence(string file_name, vector<vector<vector<int> > > coloured_voxels, int sphere_radius);
    void save_2D_tomo(string file_name, int sphere_radius);
    void save_2D_tomo(string file_name, vector<vector<vector<int> > > coloured_voxels);
//    void save_image(const ::std::string &name, float img_vals[][512]);
    
    //finds a threshold from the otsu method and binerizes the voxel
    void otsu_binerization(void);
    
    //binerizes the voxel using a user defined threshold
    void threshold_binerization(int threshold);
    
    // returns the value of the specified voxel
    unsigned int get_voxel(int x, int y, int z);
    
    // changes the value of the specified voxel
    void set_voxel(int x, int y, int z, int voxel_value);
    
    // calculates the histogram of the voxel and saves it in "hist[]" difined as a private part of the class
    void histogram (void);
    
    //set x,y,z_dim
    void set_x_dim(int dim_value){
        x_dim=dim_value;
    }
    void set_y_dim(int dim_value){
        y_dim=dim_value;
    }
    void set_z_dim(int dim_value){
        z_dim=dim_value;
    }
    
    void haugh_transformation(int sphere_radius, string name_hough);
    int haugh_transformation_2D(int circle_radius, string name_hough);
//    void haugh_vote(int x, int y, int z);
    void haugh_vote_2(int x, int y, int z, vector<vector<int> > sphere_coordinates);
    void haugh_vote_2D(int x, int y, vector<vector<int> > circle_mask);
    
    void sphere_centre_locator(vector<vector<int> > &sphere_centre_coordinates, int sphere_radius);
    void circle_centre_locator(vector<vector<int> > &circle_centre_coordinates, int circle_radius);
//    void mask_sphere_coordinates(vector<vector<int> > &sphere_centre_coordinates);
    void mask_sphere_coordinates(vector<vector<int> > &sphere_centre_coordinates, int mask_radius_in, int mask_radius_out);
    void mask_circle_coordinates(vector<vector<int> > &circle_centre_coordinates, int mask_radius_in, int mask_radius_out);
    
    void process_cropped_voxel(vector<vector<int> > &sphere_centre_coordinates, int sphere_radius, int crop_size);
    void crop_sphere_coordinates(vector<vector<int> > sphere_centre_coordinates, int crop_size, vector<vector<int> > mask_coordinates, int count);
//    void crop_sphere_coordinates(vector<vector<vector<int> > > costume_voxel, vector<vector<int> > &sphere_centre_coordinates, int crop_size);
    
    void haugh_vote_link(int x, int y, int z ,int R);
    
    void erosion(void);
    void inverse_erosion (void);
    void find_chain (void);
    void links(void);
    void erase(int x, int y, int z, int R);
    
    
    int cluster_detection_prototype (monomer mono_1, monomer mono_2); //Used in find_chain_3; more information in new_chain_detection_method
    
    void find_chains_3 (void);
};


#endif /* defined(__GPC_code__tomo__) */

