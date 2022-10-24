// @@ Author: Julio Freire
// @@ Created in 21/10/2022
// @@

#include <iostream>
#include "sculptor.h"

int main()
{
    Sculptor hollow(200, 200, 200);

    hollow.setColor(.3,.3,.3,1.);
//    hollow.putBox(100, 105, 100, 105, 100, 105);
//    hollow.cutBox(100, 104, 100, 104, 100, 104);
//    hollow.putSphere(100, 100, 100, 10);
//    hollow.cutSphere(100, 100, 100, 9);
    hollow.putEllipsoid(100, 100, 100, 5, 10, 15);
    hollow.cutEllipsoid(100, 100, 100, 3, 8, 13);
    hollow.writeOFF("hollow.off");

    return 0;
}
