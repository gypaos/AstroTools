#include "starClusterMC.hpp"

void SLR(int numberOfStars = 5000, int numberOfRealization = 100)
{
   // initialize star cluster monte carlo
   StarClusterMC simu;

   // define star cluster
   simu.addCluster(numberOfStars, 17);
   simu.addCluster(numberOfStars/2, 17);

   // define initial rotational velocities
   // [Fe/H] = 0, Prantzos et al. (2018) Fig. 4
   simu.addInitialVelocity(  0, 0.67);
   simu.addInitialVelocity(150, 0.32);
   simu.addInitialVelocity(300, 0.01);

   // prepare canvas
   simu.prepareCanvasControl();

   // run monte carlo
   simu.run(numberOfRealization);

   // display results
   simu.displayCanvasControl();
}
