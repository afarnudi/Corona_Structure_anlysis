//
//  main.cpp
//  GPC
//
//  Created by Ali Farnudi on 17/07/2012.
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

#include "tomo.h"
#include <iostream>
#include <unistd.h>
#include "UI.hpp"
using namespace std;

int main(int argc, char * argv[])
{
    //time
    clock_t tStart = clock();//Time the programme
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    
    
    
    char const * options="?X:Y:Z:bk:ehf";
    char val;
//    int X=512,Y=518,Z=125,bflag=0,kflag=1,k_value=58,errosion=0, haugh_transformation=0, find_chains=0;
//    int X=597,Y=543,Z=131,bflag=0,kflag=1,k_value=58,errosion=0, haugh_transformation=0, find_chains=0;
    
//    int X=1198,Y=1212,Z=1,bflag=0,kflag=1,k_value=58,errosion=0, haugh_transformation=0, find_chains=0;
    int X=4096,Y=4224,Z=1,bflag=0,kflag=1,k_value=58,errosion=0, haugh_transformation=0, find_chains=0;
    string name;
    
    string save_name;
    val = getopt(argc, argv, options);
//    set_flags(val);
//    while ((val = getopt(argc, argv, options))!=-1){
//        switch (val) {
//            case '?' : help();
//                return 0;
//            case 'x' :
//                X=atoi(optarg);
//                break;
//            case 'y' :
//                Y=atoi(optarg);
//                break;
//            case 'z' :
//                Z=atoi(optarg);
//                break;
//            case 'b' :
//                bflag=1;
//                break;
//            case 'k' :
//                kflag=1;
//                k_value=atoi(optarg);
//                break;
//            case 'e' :
//                errosion=1;
//                break;
//            case 'h' :
//                haugh_transformation=1;
//                break;
//            case 'f':
//                find_chains=1;
//                break;
//            default:
//                help();
//                return 0;
//
//        }
//    }
//    if (argc-optind<1) {
//        cout<<"Improper use of class tomo"<<endl;
//        help();
//        return 0;
//    }
//    if (argc-optind==1) {
//        name=argv[optind];
//        save_name="1-"+name;
//    }else if (argc-optind==2) {
//        name=argv[optind];
//        save_name=argv[optind+1];
//    }
//
    
    int sphere_radius, circle_radius;
    string name_hough;
    bool Three_dimensional=false;
    
    if (Three_dimensional) {
        sphere_radius=27;
        //    name="lowcon/Zap_S1_12_20180216_lowConc0";
        name="highcon/ZapS1_1_20171116_HighConc0";
        name_hough="Hough_T_hc"+to_string(sphere_radius);
        //    string name_hough="Hough_T";
        //    save_name="test_lowcon_";
        save_name="test_highcon_";
        
        tomo test(X,Y,Z, name, 255);
        tomo Hough(X,Y,Z, name_hough, 978);//2998//809//The last number is the Max vote of the haugh transformation
        
        if (bflag==1) {
            test.otsu_binerization();
        } else if (kflag==1) {
            test.threshold_binerization(k_value);
            
        }
        if (errosion==1) {
            test.erosion();
            
        }
        if (haugh_transformation==1) {
            test.haugh_transformation(sphere_radius, name_hough);
            
        }
        if (find_chains==1) {
            test.find_chains_3();
        }
        vector<vector<int> > sphere_centre_coordinates;
        Hough.sphere_centre_locator(sphere_centre_coordinates, sphere_radius);
        
        test.mask_sphere_coordinates(sphere_centre_coordinates, sphere_radius, sphere_radius+17);//43
        //    test.Hoshen_Kopelman_cluster_mask(4, 70, true);
        test.process_cropped_voxel(sphere_centre_coordinates, sphere_radius, sphere_radius+17);//43
        
        //    test.Modify_image_2();
        //    test.Hoshen_Kopelman_3D();
        //    test.save_tomo_sequence(save_name);
        //    test.save_tomo(save_name);
    } else {
        circle_radius=360;
        string file_name="1_59kx_3um";
        string path="2D/Exp1-nopp/";
        string hough_path="2D/Exp1-nopp/Hough/1_59kx_3um/";
        name=path+file_name;
//        name_hough=hough_path+file_name+"_"+to_string(circle_radius);
        save_name=path+"test_"+file_name;
        name_hough=hough_path+"1_59kx_3um_360000";
        
        tomo test(X,Y,Z, name, 255);
        
        
        k_value=183;
        test.threshold_binerization(k_value);
        
//        int vote;
//        string new_path=path+"Hough"+file_name+"_hough_vote.txt";
//        ofstream write_hough_radius(new_path.c_str());
//        for (int i=300; i<400; i+=10) {
//            name_hough=hough_path+file_name+"_"+to_string(i);
//            cout<<name_hough<<endl;
//            vote=test.haugh_transformation_2D(i, name_hough);
//            write_hough_radius<<vote<<"\t"<<i<<"\n";
//        }
        
//        test.save_2D_tomo("1_59kx_3um_1", 36);
        
        tomo Hough(X,Y,Z, name_hough, 1616);//The last number is the Max vote of the haugh transformation
        
        
        vector<vector<int> > circle_centre_coordinates;
        Hough.circle_centre_locator(circle_centre_coordinates, circle_radius);
        //1_59kx_3um_360000--> 100 nm->818 px
        vector<int> temp;
        temp.resize(2);
        temp[0]=1419;
        temp[1]=636;
        circle_centre_coordinates.push_back(temp);
        
        
        test.mask_circle_coordinates(circle_centre_coordinates, 0, circle_radius+82);//43
        
        //    test.Hoshen_Kopelman_cluster_mask(4, 70, true);
//        test.process_cropped_voxel(sphere_centre_coordinates, sphere_radius, sphere_radius+17);//43
    }
    
    
   
    
    
    
    cout<<"done"<<endl;
    printf("Time taken: %.2fminutes\n", (double)((clock() - tStart)/CLOCKS_PER_SEC)/60.0);
    return 0;
}

