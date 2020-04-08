//
//  Cluster_info_analysis.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 25/06/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include "Hoshen_kopelman_functions.hpp"
#include "tomo.h"

void tomo::write_cluster_info(vector< int > Cluster_size){
    ofstream w_cluster;
    w_cluster.open("0cluster_size.txt");
    for (int i=0; i<Cluster_size.size(); i++) {
        w_cluster<<i<<"\t"<<Cluster_size[i]<<"\n";
        //        cout<<i<<"\t"<<Cluster_size[i]<<"\n";
    }
}

void tomo::write_cluster_info(vector<Cluster> Cluster, int crop_size, string cropped_file_name){
    
    ofstream w_cluster;
    cropped_file_name+="_cluster_info.txt";
    w_cluster.open(cropped_file_name.c_str());
    double Radius_of_gyration=0, distance_from_centre=0;
    w_cluster<<"#\tsize\t|r|(p)\t|r|(nm)\tR_G(p)\tR_G(nm)\t(|r|-25)*1.6\tD=2*R_G nm\tlambda_1\tlambda_2\tlambda_3\tanisotrpy\tasphericity\n";
    int counter=0;
    for (int i=0; i<Cluster.size(); i++) {
        if (Cluster[i].return_size()>=4) {
            counter++;
            distance_from_centre=Cluster[i].com_distance_from_a_point(crop_size, crop_size, crop_size);
            Radius_of_gyration=Cluster[i].return_radius_of_gyration();
            Cluster[i].shape_processor(); w_cluster<<counter<<"\t"<<Cluster[i].return_size()<<"\t"<<distance_from_centre<<"\t"<<distance_from_centre*1.6<<"\t"<<Radius_of_gyration<<"\t"<<Radius_of_gyration*1.6<<"\t"<<(distance_from_centre-26)*1.6<<"\t"<<Radius_of_gyration*1.6*2<<"\t"<<Cluster[i].lambda_1()<<"\t"<<Cluster[i].lambda_2()<<"\t"<<Cluster[i].lambda_3()<<"\t"<<Cluster[i].anisotropy()<<"\t"<<Cluster[i].asphericity()<<endl;
        }
    }
}
