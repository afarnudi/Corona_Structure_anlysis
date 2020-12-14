//
//  Chain.h
//  test
//
//  Created by Ali Farnudi on 12/07/2013.
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

#ifndef __test__Chain__
#define __test__Chain__

#include <iostream>
#include <vector>
using namespace std;

class monomer{
    int x,y,z;
    int link_end_1_x,link_end_1_y,link_end_1_z,link_end_2_x,link_end_2_y,link_end_2_z;
    
public:
    monomer(){
        x=0;
        y=0;
        z=0;
        set_link_end_1_coor(0,0,0);
        set_link_end_2_coor(0,0,0);
    }
    monomer(int a, int b, int c){
        x=a;
        y=b;
        z=c;
        set_link_end_1_coor(0,0,0);
        set_link_end_2_coor(0,0,0);
    }
    void set_monomer_coor(int a, int b, int c){
        x=a;
        y=b;
        z=c;
    }
    void set_x_coor(int a){
        x=a;
    }
    void set_y_coor(int a){
        y=a;
    }
    void set_z_coor(int a){
        z=a;
    }
    int return_x(void){
        return x;
    }
    int return_y(void){
        return y;
    }
    int return_z(void){
        return z;
    }
    void set_link_end_1_coor (int a, int b, int c){
        link_end_1_x=a;
        link_end_1_y=b;
        link_end_1_z=c;
    }
    void set_link_end_2_coor (int a, int b, int c){
        link_end_2_x=a;
        link_end_2_y=b;
        link_end_2_z=c;
    }
    void set_link_end_1_x (int a){
        link_end_1_x=a;
    }
    void set_link_end_1_y (int a){
        link_end_1_y=a;
    }
    void set_link_end_1_z (int a){
        link_end_1_z=a;
    }
    void set_link_end_2_x (int a){
        link_end_1_x=a;
    }
    void set_link_end_2_y (int a){
        link_end_1_y=a;
    }
    void set_link_end_2_z (int a){
        link_end_1_z=a;
    }
    int return_link_end_1_x (void){
        return link_end_1_x;
    }
    int return_link_end_1_y (void){
        return link_end_1_y;
    }
    int return_link_end_1_z (void){
        return link_end_1_z;
    }
    int return_link_end_2_x (void){
        return link_end_2_x;
    }
    int return_link_end_2_y (void){
        return link_end_2_y;
    }
    int return_link_end_2_z (void){
        return link_end_2_z;
    }
};


class chain{
    
    vector < monomer > monomer_chain;
    int chain_length;
    
public:
    chain(int length){
        chain_length=length;
        monomer_chain.resize(chain_length);
    }
    chain(){
        chain_length=1;
        monomer_chain.resize(chain_length);
    }
    void erase (int pos){
        monomer_chain.erase(monomer_chain.begin()+pos);
    };
    void push (monomer mono){
        monomer_chain.push_back(mono);
    };
    void insert (monomer mono){
        monomer_chain.insert(monomer_chain.begin(), mono);
    };
    
    void chain_resize (int length){
        chain_length=length;
        monomer_chain.resize(chain_length);
    };
    int length(void){
        chain_length=monomer_chain.size();
        return chain_length;
    }
    void set (int element, int x_cor, int y_cor, int z_cor){
        monomer_chain[element].set_monomer_coor(x_cor, y_cor, z_cor);
    }
    int return_x (int element){
        return monomer_chain[element].return_x();
    }
    int return_y (int element){
        return monomer_chain[element].return_y();
    }
    int return_z (int element){
        return monomer_chain[element].return_z();
    }
};


#endif /* defined(__test__Chain__) */

