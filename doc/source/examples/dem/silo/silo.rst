==================================
Silo
==================================

This example simulates the filling and discharge of particles in a wedge-shaped silo. We set up this simulation according to the experiments of Golshan *et al.* `[1] <https://doi.org/10.1016/j.powtec.2020.06.093>`_ It is recommended to visit `DEM parameters <../../../parameters/dem/dem.html>`_ for more detailed information on the concepts and physical meanings of the parameters in Lethe-DEM.


----------------------------------
Features
----------------------------------
- Solvers: ``lethe-particles``
- Floating walls
- Gmsh grids
- Checkpointing (restart)


----------------------------
Files Used in This Example
----------------------------
``/examples/dem/3d-silo/silo-Golshan.prm``


-----------------------
Description of the Case
-----------------------

This simulation consists of two stages: filling (0-4 s) and discharge (4-40 s) of particles. During the filling stage, we use a stopper (floating wall) to keep the inserted particles in the hopper region of the silo. When all the particles are inserted and packed in the hopper, we remove the stopper and particles leave the hopper.


--------------
Parameter File
--------------

Mesh
~~~~~

Contrary to previous examples, in this example, we use a mesh generated using `Gmsh <https://gmsh.info/>`_. The Gmsh file (extension .msh) is located inside the example folder. We refine this mesh once by setting ``initial refinement=1`` to ensure that the cells are sufficiently small to enable efficient contact detection. The mesh generated by Gmsh contains diamond cells, which are cells that only share a line with the boundary and not a complete face. ``check diamond cells=true`` enables searching for diamond-shaped boundary cells. Such cells can appear in unstructured grids, but they are detrimental to the stability of DEM simulations. Enabling this option adds these cells to the particle-wall contact search cells and is necessary to ensure stable collisions with the wall in the vicinity of diamond cells.

.. code-block:: text

    subsection mesh
      set type                = gmsh
      set file name           = ./silo-Golshan.msh
      set check diamond cells = true
      set initial refinement  = 1
    end


Insertion Info
~~~~~~~~~~~~~~~~~~~

An insertion box is defined inside and on the top of the silo.

.. code-block:: text

    subsection insertion info
      set insertion method                               = non_uniform
      set inserted number of particles at each time step = 20000
      set insertion frequency                            = 10000
      set insertion box minimum x                        = -0.37
      set insertion box minimum y                        = -0.042
      set insertion box minimum z                        = 0.9
      set insertion box maximum x                        = 0.37
      set insertion box maximum y                        = 0.007
      set insertion box maximum z                        = 1.09
      set insertion distance threshold                   = 1.5
      set insertion random number range                  = 0.1
      set insertion random number seed                   = 19
    end


Lagrangian Physical Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The total number of particles in this simulation is equal to 132300. Considering the ``inserted number of particles at each time step  = 20000``, we expect that all the particles be inserted in 7 insertion steps.

.. code-block:: text

    subsection lagrangian physical properties
      set gx                       = 0.0
      set gy                       = 0.0
      set gz                       = -9.81
      set number of particle types = 1
      subsection particle type 0
        set size distribution type            = uniform
        set diameter                          = 0.005833
        set number                            = 132300
        set density particles                 = 600
        set young modulus particles           = 5000000
        set poisson ratio particles           = 0.5
        set restitution coefficient particles = 0.7
        set friction coefficient particles    = 0.5
      end
      set young modulus wall           = 5000000
      set poisson ratio wall           = 0.5
      set restitution coefficient wall = 0.7
      set friction coefficient wall    = 0.5
    end


Model Parameters
~~~~~~~~~~~~~~~~~

.. code-block:: text

    subsection model parameters
      subsection contact detection
        set contact detection method                = dynamic
        set dynamic contact search size coefficient = 0.9
        set neighborhood threshold                  = 1.3
      end
      subsection load balancing
        set load balance method                     = frequent
        set frequency                               = 10000
      end
      set particle particle contact force method    = hertz_mindlin_limit_overlap
      set particle wall contact force method        = nonlinear
      set integration method                        = velocity_verlet
    end


Simulation Control
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: text

    subsection simulation control
      set time step        = 2e-5
      set time end         = 30
      set log frequency    = 1000
      set output frequency = 1000
    end


Restart
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this subsection, we specify the checkpointing parameters. Checkpoints are very useful in long simulations. If the simulation breaks, we can continue the simulation from the last written checkpoint. First, we enable checkpointing by setting the ``checkpoint`` parameter to true. Then, we choose a ``filename`` for the checkpoint files and specify the checkpointing ``frequency``.

.. code-block:: text

    subsection restart
      set checkpoint = true
      set frequency  = 100000
    end


Floating Walls
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Floating wall is a temporary (its start and end times are defined) flat wall, generally used for holding the particles during the filling and before the discharge stage.

In this subsection, the information on floating walls is defined. First of all, the total ``number of floating walls`` is specified. Then for each floating wall, we should specify its ``normal vector``, a ``point on the wall``, ``start`` and ``end times``.

In this simulation, we need a stopper (floating wall) in the filling stage (0-4 s). Hence, we set ``start time`` and ``end time`` equal to 0 and 4, respectively. The stopper should be in the `xy` plane and be located at the bottom of the silo. We use this information to select the point on the stopper (0, 0, 0) and its normal vector (0, 0, 1).

.. code-block:: text

    subsection floating walls
      set number of floating walls = 1
      subsection wall 0
        subsection point on wall
          set x = 0
          set y = 0
          set z = 0
        end
        subsection normal vector
          set nx = 0
          set ny = 0
          set nz = 1
        end
        set start time = 0
        set end time   = 4
      end
    end


----------------------
Running the Simulation
----------------------
This simulation can be launched in parallel (e.g. using 8 processes) by running:

.. code-block:: text

  mpirun -np 8 lethe-particles silo-Golshan.prm

.. warning::
	This example takes approximately 14 hours on 8 cores. This high computational time is due to the long simulation time (30 s of real-time).

---------
Results
---------

Animation of the silo simulation:

.. raw:: html

    <iframe width="560" height="315" src="https://www.youtube.com/embed/fWzza739UVg" frameborder="0" allowfullscreen></iframe>

Animation of the subdomains distribution throughout the simulation:

.. raw:: html

    <iframe width="560" height="315" src="https://www.youtube.com/embed/uoQG97SO6Zc" frameborder="0" allowfullscreen></iframe>


---------
Reference
---------

`[1] <https://doi.org/10.1016/j.powtec.2020.06.093>`_ S. Golshan, B. Esgandari, R. Zarghami, B. Blais, and K. Saleh, “Experimental and DEM studies of velocity profiles and residence time distribution of non-spherical particles in silos,” *Powder Technol.*, vol. 373, pp. 510–521, Aug. 2020, doi: 10.1016/j.powtec.2020.06.093.