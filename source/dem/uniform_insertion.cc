#include <dem/uniform_insertion.h>

using namespace DEM;

// The constructor of non-uniform insertion class. In the constructor, we
// investigate if the insertion box is adequately large to handle the desired
// number of inserted particles. The number of insertion points in each
// direction (number_of_particles_x_direction, number_of_particles_y_direction
// and number_of_particles_z_direction) are also obtained
template <int dim>
UniformInsertion<dim>::UniformInsertion(
  const DEMSolverParameters<dim> &dem_parameters,
  const double                    maximum_particle_diameter)
  : particles_of_each_type_remaining(
      dem_parameters.lagrangian_physical_properties.number.at(0))
{
  // Inializing current inserting particle type
  current_inserting_particle_type = 0;

  this->inserted_this_step = 0;

  this->maximum_diameter = maximum_particle_diameter;
}

// The main insertion function. Insert_global_function is used to insert the
// particles
template <int dim>
void
UniformInsertion<dim>::insert(
  Particles::ParticleHandler<dim>                 &particle_handler,
  const parallel::distributed::Triangulation<dim> &triangulation,
  const DEMSolverParameters<dim>                  &dem_parameters)
{
  if (particles_of_each_type_remaining == 0 &&
      current_inserting_particle_type !=
        dem_parameters.lagrangian_physical_properties.particle_type_number - 1)
    {
      particles_of_each_type_remaining =
        dem_parameters.lagrangian_physical_properties.number.at(
          ++current_inserting_particle_type);
    }

  // Check to see if the remained uninserted particles is equal to zero or not
  if (particles_of_each_type_remaining != 0)
    {
      MPI_Comm           communicator = triangulation.get_communicator();
      ConditionalOStream pcout(
        std::cout, Utilities::MPI::this_mpi_process(MPI_COMM_WORLD) == 0);

      auto this_mpi_process = Utilities::MPI::this_mpi_process(communicator);
      auto n_mpi_process    = Utilities::MPI::n_mpi_processes(communicator);

      this->calculate_insertion_domain_maximum_particle_number(dem_parameters,
                                                               pcout);

      // The inserted_this_step value is the mimnum of remained_particles and
      // inserted_this_step
      this->inserted_this_step =
        std::min(particles_of_each_type_remaining, this->inserted_this_step);

      // Obtaining global bounding boxes
      const auto my_bounding_box =
        GridTools::compute_mesh_predicate_bounding_box(
          triangulation, IteratorFilters::LocallyOwnedCell());
      const auto global_bounding_boxes =
        Utilities::MPI::all_gather(communicator, my_bounding_box);

      // Distbuting particles between processors
      this->inserted_this_step_this_proc =
        floor(this->inserted_this_step / n_mpi_process);
      if (this_mpi_process == (n_mpi_process - 1))
        this->inserted_this_step_this_proc =
          this->inserted_this_step -
          (n_mpi_process - 1) * floor(this->inserted_this_step / n_mpi_process);

      Point<dim>              insertion_location;
      std::vector<Point<dim>> insertion_points_on_proc;
      insertion_points_on_proc.reserve(this->inserted_this_step_this_proc);

      // Find the first and the last particle id for each process
      // The number of particles on the last process is different
      unsigned int first_id;
      unsigned int last_id;
      if (this_mpi_process == (n_mpi_process - 1))
        {
          first_id =
            this->inserted_this_step - this->inserted_this_step_this_proc;
          last_id = this->inserted_this_step;
        }
      // For the processes 1 : n-1
      else
        {
          first_id = this_mpi_process * this->inserted_this_step_this_proc;
          last_id = (this_mpi_process + 1) * this->inserted_this_step_this_proc;
        }

      // Looping through the particles on each process and finding their
      // insertion location
      for (unsigned int id = first_id; id < last_id; ++id)
        {
          find_insertion_location_uniform(insertion_location,
                                          id,
                                          dem_parameters.insertion_info);
          insertion_points_on_proc.push_back(insertion_location);
        }

      // Assigning inserted particles properties using
      // assign_particle_properties function
      this->assign_particle_properties(dem_parameters,
                                       this->inserted_this_step_this_proc,
                                       current_inserting_particle_type,
                                       this->particle_properties);

      // Insert the particles using the points and assigned properties
      particle_handler.insert_global_particles(insertion_points_on_proc,
                                               global_bounding_boxes,
                                               this->particle_properties);

      // Updating remaining particles
      particles_of_each_type_remaining -= this->inserted_this_step;

      this->print_insertion_info(this->inserted_this_step,
                                 particles_of_each_type_remaining,
                                 current_inserting_particle_type,
                                 pcout);
    }
}

// This function assigns the insertion points of the inserted particles
template <>
void
UniformInsertion<2>::find_insertion_location_uniform(
  Point<2>                                    &insertion_location,
  const unsigned int                          &id,
  const Parameters::Lagrangian::InsertionInfo &insertion_information)
{
  std::vector<int> insertion_index;
  insertion_index.resize(2);

  unsigned int axis_0, axis_1;
  int          number_of_particles_0;

  // First direction (axis) to have particles inserted
  axis_0                  = insertion_information.axis_0;
  number_of_particles_0   = this->number_of_particles_directions[axis_0];
  insertion_index[axis_0] = id % number_of_particles_0;
  insertion_location[axis_0] =
    this->axis_min[axis_0] + ((insertion_index[axis_0] + 0.5) *
                              insertion_information.distance_threshold) *
                               this->maximum_diameter;

  // Second direction (axis) to have particles inserted
  axis_1                  = insertion_information.axis_1;
  insertion_index[axis_1] = static_cast<int>(id) / number_of_particles_0;
  insertion_location[axis_1] =
    this->axis_min[axis_1] + ((insertion_index[axis_1] + 0.5) *
                              insertion_information.distance_threshold) *
                               this->maximum_diameter;
}

template <>
void
UniformInsertion<3>::find_insertion_location_uniform(
  Point<3>                                    &insertion_location,
  const unsigned int                          &id,
  const Parameters::Lagrangian::InsertionInfo &insertion_information)
{
  std::vector<int> insertion_index;
  insertion_index.resize(3);

  unsigned int axis_0, axis_1, axis_2;
  int          number_of_particles_0, number_of_particles_1;

  // First direction (axis) to have particles inserted
  axis_0                  = insertion_information.axis_0;
  number_of_particles_0   = this->number_of_particles_directions[axis_0];
  insertion_index[axis_0] = id % number_of_particles_0;
  insertion_location[axis_0] =
    this->axis_min[axis_0] + ((insertion_index[axis_0] + 0.5) *
                              insertion_information.distance_threshold) *
                               this->maximum_diameter;

  // Second direction (axis) to have particles inserted
  axis_1                = insertion_information.axis_1;
  number_of_particles_1 = this->number_of_particles_directions[axis_1];
  insertion_index[axis_1] =
    static_cast<int>(id % (number_of_particles_0 * number_of_particles_1)) /
    (number_of_particles_0);
  insertion_location[axis_1] =
    this->axis_min[axis_1] + ((insertion_index[axis_1] + 0.5) *
                              insertion_information.distance_threshold) *
                               this->maximum_diameter;

  // Third direction (axis) to have particles inserted
  axis_2 = insertion_information.axis_2;
  insertion_index[axis_2] =
    static_cast<int>(id) / (number_of_particles_0 * number_of_particles_1);

  // Adding an extra distance to even rows of insertion
  if (insertion_index[2] % 2 == 0)
    {
      insertion_location[0] += this->maximum_diameter * 0.5;
      insertion_location[1] += this->maximum_diameter * 0.5;
    }

  insertion_location[axis_2] =
    this->axis_min[axis_2] + ((insertion_index[axis_2] + 0.5) *
                              insertion_information.distance_threshold) *
                               this->maximum_diameter;
}

template class UniformInsertion<2>;
template class UniformInsertion<3>;
