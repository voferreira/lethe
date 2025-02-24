# Lethe

![Lethe](logo/logo_black.png?raw=true)

[![Build Status](https://github.com/lethe-cfd/lethe/workflows/CI/badge.svg)](https://github.com/lethe-cfd/lethe/workflows/CI/badge.svg)

Lethe (pronounced /ˈliːθiː/) is open-source computational fluid dynamics
(CFD), discrete element method (DEM) and coupled CFD-DEM
software which uses high-order continuous Galerkin formulations to
simulate single and multiphase flows.
Lethe contains a family of solvers that are based on
[deal.II](https://www.dealii.org/), a finite element library.
Through deal.II, Lethe uses [Trilinos](https://trilinos.github.io/) for
its sparse linear algebra routines and [p4est](https://www.p4est.org/)
for its distributed adaptative quadtrees and octrees.

Lethe is named after the river of forgetfulness, which, according to
[Wikipedia](https://en.wikipedia.org/wiki/Lethe),

> is one of the five rivers of the Greek underworld\[,\] the other four
> \[being\] Acheron (the river of sorrow), Cocytus (the river of
> lamentation), Phlegethon (the river of fire) and Styx (the river that
> separates Earth and the Underworld).
> …
> The shades of the dead were required to drink the waters of the Lethe
> in order to forget their earthly life.

Lethe is described [here](https://doi.org/10.1016/j.softx.2020.100579).
It originally began as a weekend project, but slowly grew into CFD, DEM and CFD-DEM
software used in actual research. Lethe is under active development. 


Note: Lethe would not exist without the dedicated work of the deal.II
authors.
The authors of Lethe would like to emphasize that without deal.II,
dedicated solvers like Lethe could not exist.

## Documentation

Documentation, tutorials, and more can be found 
[here](https://lethe-cfd.github.io/lethe/).

## Installation

Follow the instructions in the
[documentation](https://lethe-cfd.github.io/lethe/installation/installation.html).

## Authors

Main developer:

- [Bruno Blais](https://www.polymtl.ca/expertises/en/blais-bruno)

Contributors (in alphabetical order):

- Amishga Alphonius
- Antoine Avrit
- Lucka Barbeau
- Valérie Bibeau
- Bianca Bugeaud
- Audrey Collard-Daigneault
- Carole-Anne Daunais
- Toni El Geitani
- Olivier Gaboriault
- Simon Gauvin
- Shahab Golshan
- Olivier Guévremont
- Marion Hanne
- Jeanne Joachim
- Rajeshwari Kamble
- Martin Kronbichler
- Maxime Landry
- Pierre Laurentin
- Charles Le Pailleur
- Oreste Marquis
- Ghazaleh Mirakhori
- Thomas Monatte
- Peter Munch
- Victor Oliveira Ferreira
- Hélène Papillon-Laroche
- Paul Patience
- Laura Prieto Saavedra
- Catherine Radburn
- Philippe Rivest
- Mikael Vaillant

## License

This project is licensed under the [LGPL-2.1 license](LICENSE).

Unless you explicitly state otherwise, any contribution intentionally
submitted by you for inclusion in this project shall be licensed as
above, without any additional terms or conditions.
