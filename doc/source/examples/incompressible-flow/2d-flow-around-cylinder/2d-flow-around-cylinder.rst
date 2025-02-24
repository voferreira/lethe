======================================
Flow around a Cylinder
======================================

This example corresponds to a flow around a fixed cylinder. This is a classical problem studied in fluid mechanics. This example introduces several important features supported by Lethe.


---------
Features
---------

- Solver: ``lethe-fluid`` (with Q1-Q1) 
- Steady-state problem
- Shows how to import a gmsh file
- Explains how to set a manifold
- Specifies an initial condition
- Displays the use of non-uniform mesh adaptation 


----------------------------
Files Used in This Example
----------------------------

- Geometry file: ``/examples/incompressible-flow/2d-flow-around-cylinder/cylinder-structured.geo``
- Mesh file: ``/examples/incompressible-flow/2d-flow-around-cylinder/cylinder-structured.msh``
- Parameter file: ``/examples/incompressible-flow/2d-flow-around-cylinder/cylinder.prm``


-----------------------
Description of the Case
-----------------------
We simulate the flow around a fixed cylinder with a constant upstream fluid velocity. The following schematic describes the geometry with its relevant quantities (taken from the article by Blais *et al.* `[1] <https://doi.org/10.1016/j.compchemeng.2015.10.019>`_):

.. image:: images/geometry-description.png
    :alt: The geometry
    :align: center
    :name: geometry_description


--------------
Parameter File
--------------

Only the subsections of the parameter file that change significantly in comparison to :doc:`../2d-lid‐driven-cavity-flow/lid‐driven-cavity-flow` and :doc:`../2d-taylor-couette-flow/2d-taylor-couette-flow` examples are explained in this section.

Mesh
~~~~~

Lethe supports the use of imported mesh files:

.. code-block:: text

    subsection mesh
      set type      = gmsh
      set file name = cylinder-structured.msh
    end

The ``type`` specifies the mesh format used, in this case  we have ``gmsh`` which corresponds to a file generated by `Gmsh <https://gmsh.info/#Download>`_. The ``set file name`` command specifies the path to the file. In this case, we assume that the parameter and mesh files are in the same folder.  The ``.geo`` used to generate the gmsh mesh is provided.

Assuming that the ``gmsh`` executable is within your ``$PATH`` variable, you may generate the ``.msh`` file from the example folder by typing:

.. code-block:: text

    gmsh -2 cylinder-structured.geo -o cylinder-structured.msh

Mesh Adaptation
~~~~~~~~~~~~~~~

This example uses a non-uniform mesh adaptation. The parameters used are specified in the ``mesh adaptation`` subsection:

.. code-block:: text

    subsection mesh adaptation
      set type                 = kelly
      set variable             = velocity
      set fraction type        = number
      set max number elements  = 70000
      set max refinement level = 6
      set min refinement level = 0
      set frequency            = 1
      set fraction refinement  = 0.3
      set fraction coarsening  = 0.1
    end

For steady-state simulations, one can enable a fixed number of mesh adaptations in the simulation control subsection. For this example, in the ``simulation control`` subsection (see :doc:`../../../parameters/cfd/simulation_control`), the following line is added: ``set number mesh adapt = 4``. This means that the mesh will be adapted 4 times following the parameters specified in this subsection. In this case the ``type`` is set to ``kelly`` which corresponds to the `Kelly Error Estimator strategy <https://www.dealii.org/current/doxygen/deal.II/classKellyErrorEstimator.html>`_ as implemented in deal.II, and calculated with respect to the ``velocity`` variable. To more details on the different parameters and options refer to the :doc:`../../../parameters/parameters`.

The result of this mesh adaptation can be clearly seen if we compare the initial mesh:

.. image:: images/initial-mesh.png
    :alt: Initial Mesh
    :align: center
    :name: initial_mesh

and the final mesh after being adapted 4 times:

.. image:: images/final-mesh.png
    :alt: Final Mesh
    :align: center
    :name: final_mesh

Manifolds
~~~~~~~~~

All the deal.II meshes supported by Lethe that correspond to the `GridGenerator <https://www.dealii.org/current/doxygen/deal.II/namespaceGridGenerator.html>`_ class, attach by default manifolds to meshes when needed. However, if another type of mesh is used in Lethe, it is possible to attach manifolds adding a section to the parameter file that looks as follows:

.. code-block:: text

    subsection manifolds
      set number = 1
      subsection manifold 0
        set id   = 0
        set type = spherical
        set arg1 = 8
        set arg2 = 8
      end
    end


First the number of manifolds is specified by the ``set number`` command. Then a subsection for each of the manifolds is created starting with the ``manifold 0``. The boundary ``id`` is in this case set to ``0`` as we want to set a cylinder manifold and this is the corresponding id in this example. Then the ``type`` of the manifold is specified. In Lethe, there are two types supported:

* ``spherical`` manifold: The former can be used to describe any sphere, circle, hypesphere or hyperdisc in two or three dimensions and requires as arguments two or three geometrical locations depending on the dimension, that are used to create the circle center where the manifold will be build. In this example we set ``arg1`` and ``arg2`` to ``8``. 

* ``iges`` manifold corresponding to a CAD geometry: the last two lines of the ``manifold 0`` subsection are replaced by the following command ``set cad file = file_name.iges`` where the path to the cad file is specified. 

.. note::
    For more information about manifolds and the reasons behind them, we invite you to read the documentation page of deal.II: `Manifold description for triangulations <https://www.dealii.org/developer/doxygen/deal.II/group__manifold.html>`_.

Initial Conditions
~~~~~~~~~~~~~~~~~~
Despite this problem being a steady-state problem, one known strategy to improve convergence is to set a coherent initial condition. In Lethe, this can be achieved by the ``initial conditions`` subsection:

.. code-block:: text

    subsection initial conditions
      set type = nodal
      subsection uvwp
        set Function expression = 1; 0; 0
      end
    end

In this case we use the ``nodal`` initial condition and the ``subsection uvwp`` allows the description of a velocity-pressure vector-valued function. It can be seen that the individual components of the function are separated by semicolons in the ``set Function expression``. In this case, the velocity in the x-direction is set to ``1``, the velocity in the y-direction is set to ``0``, and the pressure is set to ``0``. If the problem was in three dimensions, four values should be specified, velocity in x, y and z directions and the pressure.


Boundary Conditions
~~~~~~~~~~~~~~~~~~~~
In this section, we specify the boundary conditions taking into account the IDs presented in the following schematic:

.. image:: images/geometry-bc.png
    :alt: The boundary conditions
    :align: center
    :name: geometry_bc


.. code-block:: text
    
    subsection boundary conditions
      set number = 3
      subsection bc 0
        set type = noslip
      end
      subsection bc 1
        set type = function
        subsection u
          set Function expression = 1
        end
        subsection v
          set Function expression = 0
        end
        subsection w
          set Function expression = 0
        end
      end
      subsection bc 2
        set type = slip
      end
    end

* ``bc 0`` identifies the cylinder where we apply ``noslip`` boundary conditions on its walls. This leads to a velocity  :math:`\mathbf{u} = \mathbf{0}` for the fluid directly in contact with the walls of the cylinder.
* ``bc 1`` determines the flow of the fluid from the left wall. As mentioned before, the fluid is moving in the x-direction and therefore its boundary condition is defined with a function having a ``u`` velocity equals to 1. The rest of the velocity components are set to 0.
* ``bc 2`` is applied at the top and bottom walls. This condition allows the simulation to be performed in a finite sized domain. In real life, the cylinder would be placed in a relatively infinite domain. Using ``slip`` condition, we assume that the fluid cannot go out in the normal direction, but that it can still flow from left to right without friction. Thus, the walls have no effect on the flow of the fluid.

.. note::
    An implicit fourth boundary condition is implemented on the right wall which represents the outlet of the flow. We do not specify anything explicitly, because this corresponds to a natural boundary condition where the pressure :math:`p` becomes close to 0 due to the imposed :math:`\int_{\Gamma}(-p\mathcal{I} + \mathbf{\tau}) \cdot \mathbf{n}=0`. For more details, refer to :doc:`../../../parameters/cfd/boundary_conditions_cfd` section.

Forces
~~~~~~

To calculate forces acting on the boundary conditions, for example, the forces acting on the cylinder, we can use the ``forces`` subsection:

.. code-block:: text

    subsection forces
      set verbosity             = verbose
      set calculate force       = true
      set calculate torque      = false
      set force name            = force
      set output precision      = 10
      set calculation frequency = 1
      set output frequency      = 1
    end

To print the values of the forces in the terminal we set ``verbosity`` to ``verbose``. The calculation of the forces in all boundaries is set by the ``set calculate force = true`` line. A ``.dat`` file is created with the corresponding data. Therefore, one can specify the prefix of the file by the ``force name`` parameter, the number of significant digits for the force values by the ``output precision`` and the frequency of calculation and output which are set to ``1``. 


----------------------
Running the Simulation
----------------------
Launching the simulation is as simple as specifying the executable name and the parameter file. Assuming that the ``lethe-fluid`` executable is within your path, the simulation can be launched by typing:

.. code-block:: text

  lethe-fluid cylinder.prm

Lethe will generate a number of files. The most important one bears the extension ``.pvd``. It can be read by visualization programs such as `Paraview <https://www.paraview.org/>`_.


----------------------
Results and Discussion
----------------------

Using Paraview the following steady-state velocity and pressure profiles can be visualized:

.. image:: images/velocity.png
    :alt: Velocity profile
    :align: center
    :name: velocity

.. image:: images/pressure.png
    :alt: Pressure profile
    :align: center
    :name: pressure

From the velocity distribution, we notice how the velocity of the fluid is 0 at the boundaries of the cylinder and how it increases gradually if we move further away from it. In the case of the pressure, the difference between the inlet and outlet is visible and we can see how the pressure is near to 0 close to the outlet.

In addition to these profiles, we also obtain the values of the forces acting on the cylinder. These values can be found on the ``forces.00.dat`` file produced by the simulation and correspond to the forces acting on the ``bc 0`` (cylinder boundary). The force is decomposed in its two components which are the viscous force (``f_v``) due to shear stresses on the boundary, and a pressure force (``f_p``) due to the body shape.

.. code-block:: text

 cells     f_x           f_y          f_z          f_xv         f_yv          f_zv         f_xp         f_yp          f_zp     
  1167 6.6047202908  0.0000000824 0.0000000000 3.0431481836  0.0000000312 0.0000000000 3.5615721072  0.0000000512 0.0000000000 
  2208 6.9680865613 -0.0002186491 0.0000000000 3.2447002611 -0.0000730915 0.0000000000 3.7233863002 -0.0001455576 0.0000000000 
  4197 7.0833998066  0.0025544399 0.0000000000 3.3778679961  0.0020491181 0.0000000000 3.7055318105  0.0005053218 0.0000000000 
  8058 7.1321594705 -0.0000600573 0.0000000000 3.4651119900 -0.0000419133 0.0000000000 3.6670474805 -0.0000181441 0.0000000000 
 15459 7.1121045976  0.0048440122 0.0000000000 3.4730928015  0.0032471187 0.0000000000 3.6390117961  0.0015968935 0.0000000000 

The force in the x direction is the parallel or drag force, while the force in the y direction is the perpendicular or lift force. The drag and lift coefficients can be calculated as follows:

.. math::

 C_D = \frac{2 f_x}{\rho U_\infty^2 D},  C_L = \frac{2 f_y}{\rho U_\infty^2 D}

where :math:`U_\infty` is the upstream velocity and :math:`D` is the diameter of the cylinder. Considering the small values of the lift force, we calculate only the drag coefficients:

.. code-block:: text

  cells     C_D       
   1167    13.20  
   2247    13.93  
   4302    14.15  
   8268    14.23  
  15990    14.24  

We can see that the simulation is mesh convergent, as the last three values of the force in the x-direction and therefore the drag coefficient differ in less than 1%. An experimental value of the drag coefficient as a function of the Reynolds number is available in the `Drag Coefficient Calculator <https://kdusling.github.io/teaching/Applied-Fluids/DragCoefficient.html>`_ , and for a Reynolds number of 1, it corresponds to a value of :math:`C_D = 11.9`. The value calculated by Lethe differs from the theoretical value because of the slip boundary condition at the top and bottom walls, along with the short distance to them from the surface of the cylinder. To obtain a more accurate drag coefficient, the geometry should be enlarged.


----------------------------
Possibilities for Extension
----------------------------
- Play with the size of geometry to observe the effect on the calculation of the drag forces.
- Increase the Reynolds number and perform an unsteady simulation to observe the famous von Kármán vortex street pattern.
- It would be interesting to try the same example in 3D and observe what happens with the drag and lift forces.

----------
Reference
----------

`[1] <https://doi.org/10.1016/j.compchemeng.2015.10.019>`_ 	B. Blais, M. Lassaigne, C. Goniva, L. Fradette, and F. Bertrand, “A semi-implicit immersed boundary method and its application to viscous mixing,” *Comput. Chem. Eng.*, vol. 85, pp. 136–146, Feb. 2016, doi: 10.1016/j.compchemeng.2015.10.019.