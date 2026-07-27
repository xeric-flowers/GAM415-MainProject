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
