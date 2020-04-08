//
//  New_chain_detection_method.cpp
//  test
//
//  Created by Ali Farnudi on 26/10/2013.
//
//
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
#include "Chain.h"

void tomo::find_chains_3 (void){
    
    vector<monomer> temp_positions;//this list is used to make a copy of the monomer positions, so that it can be edited without the lost of information
    //now we make a copy of the monomer positions
    temp_positions.resize(position.size());
    for (int i=1; i<position.size(); i++) {
        temp_positions[i].set_monomer_coor(position[i].return_x(), position[i].return_y(), position[i].return_z());
    }
    ofstream write;
    write.open("list of chain members.txt");
    vector < chain > chain_list; //list of chains
    monomer chain_push;//We use chain_push, to push chain members at the end/beginning of the chain
    int chain_number=0;
    
    while (temp_positions.size()>1) {
        int end_of_chain=0,  beginning_of_chain=0;; //during each chain detection these two parameters will tell us if the chain has reached the end/beginning member
        chain_number++;
        chain_list.resize(chain_number);
        //we set the first monomer im the temp_pos as a chain member, then we will delete it from the list, because we don't need it in future search for neighbours
        chain_push.set_monomer_coor(temp_positions[1].return_x(), temp_positions[1].return_y(), temp_positions[1].return_z());
        chain_list[chain_list.size()-1].push(chain_push);
        temp_positions.erase(temp_positions.begin()+1);
        chain_list[chain_list.size()-1].erase(0);
        
        while (end_of_chain==0) {//start looking for members in one direction along the chain
            
            monomer mono_1,mono_2;
            mono_1.set_monomer_coor(chain_push.return_x(), chain_push.return_y(), chain_push.return_z());
            for (int count_1=1; count_1<temp_positions.size(); count_1++) {
                
                if (temp_positions.size()==1) {
                    end_of_chain=1;
                    break;
                }
                mono_2.set_monomer_coor(temp_positions[count_1].return_x(), temp_positions[count_1].return_y(), temp_positions[count_1].return_z());
                //search the area for potential neighbours
                int R_2;
                R_2=(mono_2.return_x()-mono_1.return_x())*(mono_2.return_x()-mono_1.return_x())+
                (mono_2.return_y()-mono_1.return_y())*(mono_2.return_y()-mono_1.return_y())+
                (mono_2.return_z()-mono_1.return_z())*(mono_2.return_z()-mono_1.return_z());
                if ((R_2<=2050 && cluster_detection_prototype(mono_1,mono_2)==1) || (R_2<=2050 && cluster_detection_prototype(mono_2,mono_1)==1)) {
                    chain_push.set_monomer_coor(mono_2.return_x(), mono_2.return_y(), mono_2.return_z());
                    chain_list[chain_list.size()-1].push(chain_push);
                    temp_positions.erase(temp_positions.begin()+count_1);
                    
                    //This will make sure that if the temp_positions list is exhasted the program can exit the 'while' loop
                    if (temp_positions.size()==1) {
                        end_of_chain=1;
                        beginning_of_chain=1;
                    }
                    
                    break;
                }
                if (count_1>=temp_positions.size()-1) {
                    end_of_chain=1;
                }
                
                
            }
            
        }
        //now that we have reached the end of the chain we start the detection from the other end (beginning)
        while (beginning_of_chain==0) {
            
            monomer mono_1,mono_2;
            mono_1.set_monomer_coor(chain_list[chain_list.size()-1].return_x(0), chain_list[chain_list.size()-1].return_y(0), chain_list[chain_list.size()-1].return_z(0));
            for (int count_1=1; count_1<temp_positions.size(); count_1++) {
                
                mono_2.set_monomer_coor(temp_positions[count_1].return_x(), temp_positions[count_1].return_y(), temp_positions[count_1].return_z());
                int R_2;
                R_2=(mono_2.return_x()-mono_1.return_x())*(mono_2.return_x()-mono_1.return_x())+
                (mono_2.return_y()-mono_1.return_y())*(mono_2.return_y()-mono_1.return_y())+
                (mono_2.return_z()-mono_1.return_z())*(mono_2.return_z()-mono_1.return_z());
                if ((R_2<=2050 && cluster_detection_prototype(mono_1,mono_2)==1) || (R_2<=2050 && cluster_detection_prototype(mono_2,mono_1)==1)) {
                    chain_push.set_monomer_coor(mono_2.return_x(), mono_2.return_y(), mono_2.return_z());
                    chain_list[chain_list.size()-1].insert(chain_push);
                    temp_positions.erase(temp_positions.begin()+count_1);
                    
                    if (temp_positions.size()==1) {
                        beginning_of_chain=1;
                    }
                    break;
                }
                if (count_1>=temp_positions.size()-1) {
                    beginning_of_chain=1;
                }
                
            }
            
            
        }
        write<<"\nchain size:\t"<<chain_list[chain_list.size()-1].length()<<endl;
        cout<<"\nchain size:\t"<<chain_list[chain_list.size()-1].length()<<endl;
        write<<"Chain begins:\nx:\ty:\tz:\n";
        cout<<"Chain begins:\nx:\ty:\tz:\n";
        for (int i=0; i<chain_list[chain_list.size()-1].length(); i++) {
            write<<chain_list[chain_list.size()-1].return_x(i)<<"\t"<<chain_list[chain_list.size()-1].return_y(i)<<"\t"<<chain_list[chain_list.size()-1].return_z(i)<<"\n";
            cout<<chain_list[chain_list.size()-1].return_x(i)<<"\t"<<chain_list[chain_list.size()-1].return_y(i)<<"\t"<<chain_list[chain_list.size()-1].return_z(i)<<"\n";
        }
        
    }
    
}

int tomo::cluster_detection_prototype (monomer mono_1, monomer mono_2){
    
    vector<vector<vector<unsigned short int > > > mini_accumulator_copy;//We use this accumulator to construct the clusters
    mini_accumulator_copy.resize(z_dim);
    for (int k=0; k<z_dim; k++) {
        mini_accumulator_copy[k].resize(x_dim);
        for (int i=0; i<x_dim; i++) {
            mini_accumulator_copy[k][i].resize(y_dim);
            for (int j=0; j<y_dim; j++) {
                mini_accumulator_copy[k][i][j]=0;
            }
        }
    }
    
    int R_2;
    R_2=(mono_2.return_x()-mono_1.return_x())*(mono_2.return_x()-mono_1.return_x())+
    (mono_2.return_y()-mono_1.return_y())*(mono_2.return_y()-mono_1.return_y())+
    (mono_2.return_z()-mono_1.return_z())*(mono_2.return_z()-mono_1.return_z());
    
    //We use different settings for different distances
    int sweep=10;
    int initial_cluster=20;//20
    int cluster_detection_sweep=10;//10    19
    if (R_2<1300 && R_2>=1100) {
        sweep=10;
        initial_cluster=15;//15
        cluster_detection_sweep=8;//8     19
    } else if (R_2>=1000 && R_2<1100){
        sweep=12;//10
        initial_cluster=13;//13;
        cluster_detection_sweep=8;//8     18  note need to make spheres
    } else if (R_2<1000){
        sweep=10;//10
        initial_cluster=11;//11
        cluster_detection_sweep=7;//7       17
    }
    
    int delta_z=mono_2.return_z()-mono_1.return_z();
    int delta_y=mono_2.return_y()-mono_1.return_y();
    int delta_x=mono_2.return_x()-mono_1.return_x();
    
    int num_points=int(sqrt(delta_x*delta_x+delta_y*delta_y+delta_z*delta_z));//this will determin the length of the connecting line between two monomers
    
    //We shall determin the general angle of the monomers twards each other
    double zx=abs(delta_z)/(abs(delta_x)-0.1),
    zy=abs(delta_z)/(abs(delta_y)-0.1),
    yz=abs(delta_y)/(abs(delta_z)-0.1),
    yx=abs(delta_y)/(abs(delta_x)-0.1);
    int sweep_case=0;
    
    //Depending on the general angle between the monomers the search area between the monomers is 'switched'
    if (zx>1 && zy>1){
        sweep_case=1;//xy
    }else if(yz>1 && yx>1){
        sweep_case=2;//zx
    }
    
    int z,y,x;
    
    //we will copy the first part of the cluster that is inside our monomer. Later we shall build the cluster upon this part
    for (int count=0; count<initial_cluster; count++) {
        
        //we use z,y,x to move between monomers
        z=mono_1.return_z()+int(count*delta_z/num_points)+1;
        y=mono_1.return_y()+int(count*delta_y/num_points)+1;
        x=mono_1.return_x()+int(count*delta_x/num_points)+1;
        
        switch (sweep_case) {
            case 1:
                for (int i=x-sweep; i<=x+sweep; i++) {
                    for (int j=y-sweep; j<=y+sweep; j++) {
                        if (mini_accumulator[z][i][j]==gray_level-1 && ((i-x)*(i-x)+(j-y)*(j-y))<=sweep*sweep) {
                            //check neighbours for any sign of cluster
                            mini_accumulator_copy[z][i][j]=gray_level-1;
                        } //else {mini_accumulator_copy[z][i][j]=15000;};
                    }
                }
                break;
                
            case 2:
                for (int i=z-sweep; i<=z+sweep; i++) {
                    for (int j=x-sweep; j<=x+sweep; j++) {
                        if (mini_accumulator[i][j][y]==gray_level-1 && ((i-z)*(i-z)+(j-x)*(j-x))<=sweep*sweep) {
                            //check neighbours for any sign of cluster
                            mini_accumulator_copy[i][j][y]=gray_level-1;
                        } //else {mini_accumulator_copy[i][j][y]=15000;};
                    }
                }
                break;
                
            default:
                for (int i=z-sweep; i<=z+sweep; i++) {
                    for (int j=y-sweep; j<=y+sweep; j++) {
                        //check neighbours for any sign of cluster
                        if (mini_accumulator[i][x][j]==gray_level-1 && ((i-z)*(i-z)+(j-y)*(j-y))<=sweep*sweep) {
                            mini_accumulator_copy[i][x][j]=gray_level-1;
                        } //else {mini_accumulator_copy[i][x][j]=15000;};
                        
                    }
                }
                break;
        }
    }
    
    //Now we shall start building the cluster from the copied part.
    for (int cluster_buiding_steps=0; cluster_buiding_steps<=50; cluster_buiding_steps++) {
        for (int count=0; count<num_points; count++) {
            z=mono_1.return_z()+int(count*delta_z/num_points)+1;
            y=mono_1.return_y()+int(count*delta_y/num_points)+1;
            x=mono_1.return_x()+int(count*delta_x/num_points)+1;
            switch (sweep_case) {
                case 1:
                    for (int i=x-sweep; i<=x+sweep; i++) {
                        for (int j=y-sweep; j<=y+sweep; j++) {
                            if (mini_accumulator_copy[z][i][j]==gray_level-1) {
                                //check neighbours for any sign of cluster
                                for (int i_local=i-1; i_local<=i+1; i_local++) {
                                    for (int j_local=j-1; j_local<=j+1; j_local++) {
                                        for (int k_local=z-1; k_local<=z+1; k_local++) {
                                            if (mini_accumulator[k_local][i_local][j_local]==gray_level-1) {
                                                mini_accumulator_copy[k_local][i_local][j_local]=gray_level-1;
                                            } //else {mini_accumulator_copy[z][i][j]=30000;};
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                    
                case 2:
                    for (int i=z-sweep; i<=z+sweep; i++) {
                        for (int j=x-sweep; j<=x+sweep; j++) {
                            if (mini_accumulator_copy[i][j][y]==gray_level-1) {
                                //check neighbours for any sign of cluster
                                for (int i_local=i-1; i_local<=i+1; i_local++) {
                                    for (int j_local=j-1; j_local<=j+1; j_local++) {
                                        for (int k_local=y-1; k_local<=y+1; k_local++) {
                                            if (mini_accumulator[i_local][j_local][k_local]==gray_level-1) {
                                                mini_accumulator_copy[i_local][j_local][k_local]=gray_level-1;
                                            } //else {mini_accumulator_copy[i][j][y]=30000;};
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                    
                default:
                    for (int i=z-sweep; i<=z+sweep; i++) {
                        for (int j=y-sweep; j<=y+sweep; j++) {
                            if (mini_accumulator_copy[i][x][j]==gray_level-1) {
                                //check neighbours for any sign of cluster
                                for (int i_local=i-1; i_local<=i+1; i_local++) {
                                    for (int j_local=j-1; j_local<=j+1; j_local++) {
                                        for (int k_local=x-1; k_local<=x+1; k_local++) {
                                            if (mini_accumulator[i_local][k_local][j_local]==gray_level-1) {
                                                mini_accumulator_copy[i_local][k_local][j_local]=gray_level-1;
                                            } //else {mini_accumulator_copy[i][x][j]=30000;};
                                        }
                                    }
                                }
                            }
                            
                        }
                    }
                    break;
            }
        }
    }
    //Now we shall scan the area around the target monomer for any sign of clusters
    int cluster_formation=0;
    for (int k=mono_2.return_z()-cluster_detection_sweep; k<mono_2.return_z()+cluster_detection_sweep; k++) {
        for (int i=mono_2.return_x()-cluster_detection_sweep; i<mono_2.return_x()+cluster_detection_sweep; i++) {
            for (int j=mono_2.return_y()-cluster_detection_sweep; j<mono_2.return_y()+cluster_detection_sweep; j++) {
                if (mini_accumulator_copy[k][i][j]==gray_level-1 /*&& ((k-mono_2.return_z())*(mono_2.return_z())+(i-mono_2.return_x())*(i-mono_2.return_x())+(j-mono_2.return_y())*(j-mono_2.return_y()))<=cluster_detection_sweep*cluster_detection_sweep*/) {
                    cluster_formation=1;
                }
            }
        }
    }
    
    
    return cluster_formation;
}

