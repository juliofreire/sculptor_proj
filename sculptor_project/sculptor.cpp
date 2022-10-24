// @@ Author: Julio Freire
// @@ Created in 21/10/2022
// @@ Methods of Sculptor

#include "sculptor.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <iomanip>

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx = _nx;
    ny = _ny;
    nz = _nz;

    // using 'new' to allocate the position of matrix elements

    v = new Voxel**[nz];
    v[0] = new Voxel*[ny*nz];
    v[0][0] = new Voxel[nx*ny*nz];


    // running into the matrix to store the address of elements

    for (int k=1;k<nz;k++){
        v[k] = v[k-1]+ny;
    }

    for (int k=0;k<nz;k++){
        for (int j=0;j<ny;j++){
            if ((k==0 && j==0)){
            v[k][1] = v[k][0]+nx;
            }
            else v[k][j] = v[k][j-1]+nx;
        }
    }

    for(int k =0; k<nz; k++){
        for(int j =0; j<ny; j++){
            for(int i =0; i<nx; i++){
                v[i][j][k].isOn = false;
            }
        }
    }
}

Sculptor::~Sculptor(){
    // BLOWWW!!!!
    delete[] v[0][0];
    delete[] v[0];
    delete[] v;
}


void Sculptor::setColor(float r, float g, float b, float a){
    // define colors of my draw
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
void Sculptor::putVoxel(int x, int y, int z){
    // just put voxel inside the sculptor shape
    if(x>=0 && y>=0 && z>=0 && x<nx && y <ny && z<nz){
    v[x][y][z].isOn = true;
    v[x][y][z].r= r;
    v[x][y][z].g= g;
    v[x][y][z].b= b;
    v[x][y][z].a= a;
    }
}

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
       for(int k =z0; k<z1; k++){
           for(int j =y0; j<y1; j++){
               for(int i =x0; i<x1; i++){
                   Sculptor::putVoxel(i,j,k);
               }
           }
       }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int k =z0; k<z1; k++){
        for(int j =y0; j<y1; j++){
            for(int i =x0; i<x1; i++){
                Sculptor::cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int k =0; k<zcenter+radius; k++){
        for(int j =0; j<ycenter+radius; j++){
            for(int i =0; i<xcenter+radius; i++){
                if(pow(i-xcenter,2)+pow(j-ycenter,2)+pow(k-zcenter,2)<pow(radius,2)){
                    Sculptor::putVoxel(i,j,k);
                };
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int k =0; k<zcenter+radius; k++){
        for(int j =0; j<ycenter+radius; j++){
            for(int i =0; i<xcenter+radius; i++){
                if(pow(i-xcenter,2)+pow(j-ycenter,2)+pow(k-zcenter,2)<pow(radius,2)){
                    Sculptor::cutVoxel(i,j,k);
                };
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int k =0; k<zcenter+rz; k++){
        for(int j =0; j<ycenter+ry; j++){
            for(int i =0; i<xcenter+rx; i++){
                if( (pow(i-xcenter,2)/pow(rx,2)) + (pow(j-ycenter,2)/pow(ry,2)) + (pow(k-zcenter,2)/pow(rz,2)) < 1){
                    Sculptor::putVoxel(i,j,k);
                };
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int k =0; k<zcenter+rz; k++){
        for(int j =0; j<ycenter+ry; j++){
            for(int i =0; i<xcenter+rx; i++){
                if( (pow(i-xcenter,2)/pow(rx,2)) + (pow(j-ycenter,2)/pow(ry,2)) + (pow(k-zcenter,2)/pow(rz,2)) < 1){
                    Sculptor::cutVoxel(i,j,k);
                };
            }
        }
    }
}

void Sculptor::writeOFF(const char* filename){
    std::ofstream myfile;
    fixed(myfile);

    myfile.open(filename);
    if(myfile.is_open() == false){
        std::cout << "File isn't open";
        exit(1);
    }

    // first line which define the OFF file
    myfile << "OFF" << std::endl;

    // counting vertices and faces of each voxel activated
    int countVertices=0;
    int countFaces=0;

    for(int k =0; k<nz; k++){
        for(int j =0; j<ny; j++){
            for(int i =0; i<nx; i++){
                if(v[i][j][k].isOn){
                    countVertices+=8;
                    countFaces+=6;
                }
            }
        }
    }

    // second line contains numberOfVertices numberOfFaces numberOfEdges
    // which the numberOfEdges doesnt matter, so its values is 0
    myfile << countVertices << " " << countFaces << " " << 0 << std::endl;


    // walking on all matrix and place vertices of each voxel
    // each element of matrix represent the center of a voxel with
    // width, lenght and height equals 1
    for(int k =0; k<nz; k++){
        for(int j =0; j<ny; j++){
            for(int i =0; i<nx; i++){
                if(v[i][j][k].isOn){
                    myfile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    myfile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    myfile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    myfile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    myfile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                    myfile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    myfile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    myfile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                }
            }
        }
    }

    // walking on all matrix selecting the vertices that represent each face
    // enumareting them in counterclockwise for the normal vector to point out
    // of the area by the right hand law.
    int numVoxel = 0;
    for(int k =0; k<nz; k++){
        for(int j =0; j<ny; j++){
            for(int i =0; i<nx; i++){
                if(v[i][j][k].isOn){
                    myfile << 4 << " " << 0+numVoxel << " " << 3+numVoxel << " " << 2+numVoxel << " " << 1+numVoxel << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    myfile << 4 << " " << 4+numVoxel << " " << 5+numVoxel << " " << 6+numVoxel << " " << 7+numVoxel << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    myfile << 4 << " " << 0+numVoxel << " " << 1+numVoxel << " " << 5+numVoxel << " " << 4+numVoxel << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    myfile << 4 << " " << 0+numVoxel << " " << 4+numVoxel << " " << 7+numVoxel << " " << 3+numVoxel << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    myfile << 4 << " " << 3+numVoxel << " " << 7+numVoxel << " " << 6+numVoxel << " " << 2+numVoxel << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    myfile << 4 << " " << 1+numVoxel << " " << 2+numVoxel << " " << 6+numVoxel << " " << 5+numVoxel << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    numVoxel += 8;
                }
            }
        }
    }

    if(myfile.is_open()){
        std::cout << "The file was saved with succesful!" << std::endl;
        myfile.close();
    }
}
