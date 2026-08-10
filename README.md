GAM 415 - Graphics Game Engine


This repository contains my work for GAM 415 as I build my Unreal Engine Project throughout the course.
I've Included short journal entries for each steppingstone to keep track of what I worked on, and what challenges I faced.


Module 2 - Stepping Stone 1

This Module introduced Dynamic Material Instances and how they can be used to change materials at runtime.
I created a splatter decal material with frames and colors set to be randomized. Then I applied the same 
randomized color from the decal to the material color of the projectile, making them match. Once the projectile
hits an object, the decal with 1 of 4 frames will appear on the surface. I added the projectile mesh component in C++
and used BeginPlay to initialize the material before gameplay.

The biggest challenge for me this time, was the game crashing whenever the projectile hit an object. The reason was that
it was not assigned. After fixing the issue the game worked as expected, but I did feel like the colors could be more random.

Module 3 - Stepping Stone 2

In this assignment I learned how to use Niagara particle systems and connect them with the code. The tutorial showed me how to create the particle effect, add user parameters, and pass an randomized color from the code so the particles matched the object they were attached to. While in the stepping stone assignment, I added a paint splatter effect when the projectile hits an object, matching colors with the decal and projectile mesh. I also made it so that the projectile is destroyed once it hits. I had a small issue adding the Niagara system, specifically thr regenerating Visual Studio files, but after making sure to close the project and code, then building the project from VS, helped sync everything correctly
I added.

Module 4 - Stepping Stone 3

For this stepping stone, I created a procedural terrain that is generated using X and Y values and Perlin noise.
I was able to change values such as the noise scale and Z multiplier to control the shape and height of the terrain.

I also added the ability for the projectile to alter the terrain when it hits it.
The impact point is passed to the terrain's AlterMesh function, which finds the vertices within a set radius and moves them down by the depth value to create a digging effect.
I did run into an issue where Unreal completely froze because of a mistake in one of my loops, but after finding and fixing it, the terrain generated correctly and I was able to shoot at it and see it change during runtime.

Module 5 - Stepping Stone 4

I worked on creating a portal system using scene capture components and render targets.
I created two connected portals that teleport the player between locations. 
I also learned how the scene capture component follows the player's camera and displays the captured view through a render target and material, which helps create the illusion that you are actually looking through the portal.

I did run into some issues while compiling because my character class was slightly different from the one used in the tutorial. After comparing the files, I was able to fix the problem and get everything working. 
I also added an arrow component as an adjustable teleport location so the player does not spawn directly in the center of the other portal.












