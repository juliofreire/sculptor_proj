// @@ Author: Julio Freire
// @@ Created in 21/10/2022
// @@ Sculptor's Header

#ifndef SCULPTOR_H
#define SCULPTOR_H

#include "voxel.h"

/**
 * @brief The Sculptor class
 */

class Sculptor {
private:
  Voxel ***v; // 3D matrix
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing colors and transparency
public:
  Sculptor(int _nx, int _ny, int _nz); // default constructor of a vector
  ~Sculptor(); // destructor
  void setColor(float r, float g, float b, float a);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void writeOFF(const char* filename);
};

#endif // SCULPTOR_H
