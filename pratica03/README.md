# Grafical Computation

## Using VBO without indexing performance impact


Processing each frame in the CPU and sending its data to be rendered in the GPU is *highly inefficient*

VBO allows the GPU to store the vertices that need to drawn in its own RAM (*VRAM*)

------------------------
## Testing creation of a cylinder with 10000 partitions

Creating a cylinder by instacing each frame its vertices in the CPU, this takes a lot a processing power away from the processor.
![](Screenshot%20from%202022-03-15%2015-50-28.png)

As we can see this method is going to be very performance starving because we are replication a lot of information.

![](Screenshot%20from%202022-03-15%2015-36-24.png)

Getting about 35 FPS and only drawing 5 cylinders

---------------------------------
### VBO Comparison
Using the VBO method to initialize the all vertices needed before the application runs.
Storing them in the VRAM, setting the array buffer active and then running them each frame.
![](Screenshot%20from%202022-03-15%2015-37-28.png)

Drawing 5 cylinders and still getting constant 60 FPS

### Test 26 cilinders
![](Screenshot%20from%202022-03-15%2015-38-18.png)

![](Screenshot%20from%202022-03-15%2015-39-04.png)


As we can see, we are able to draw 26 cilinders with 10000 divisions and still getting *constant* 30 FPS.