# Epidemic-Environment-Simulation

This is an Epidemic Environment Simulation. This is a simulation that shows the spread of a
disease with no vaccine on humans over 300 days on a visual grid. All humans start as uninfected
except for 1 human from each age class (Child/Adult/Elder). Humans may move each day and the
infecttion will spread based on age/distance from the infected/if the virus was previosuly had.

Uninfected: Can't spread the virus, suseptibilty to obtaining virus depends on if it was previously had

Incubation: The time between virus contact and symptoms. Capable of spreading the virus, can only turn symptomatic/asymptomatic

Symptomatic/Asympotmatic: Capable of spreading the virus, can die or turn uninfected again

First, The user will set the population of each demographic. Objects of the humans will then be
placed in a 2D vector like a grid. The enter button will allow the user to proceed one day.
At the end of each day a grid will visually appear showing each person's location, then on
the side stats will appear showing how many are infected from each demographic and the entire
population as a whole, and out of those infected it will show how many are asymptomatic,
symptomatic, or dead because of the disease. Each day the objects on the grid will move by
one grid space. An object has a chance of getting infected by another object if it is 1-2 grid
spaces away (the infection chance will decrease with distance and age).

