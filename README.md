# JPEGEncoder

 This tool implements the full chain of JPEG compression/decompression
 
 ## Reading a bitmap image
 
 The first step is to read a bitmap image and extract the important information such as the width, length and the pixels value. 
 
 Here's a good documenation : https://www.wikiwand.com/fr/Windows_bitmap
 
 ## RGB to YUV
 
 Each pixel is the combination of 3 values Red, Green, Blue. Usually each value is encoded from 0 to 255. 0 being no color, 255 all the color.
 
 So an image can be split into 3 matrices of size height x width : Red, Green and Blue or RGB. 
 
 This color is not really convenient for the JPEG compression. Indeed there is another color space much more interesting : YUV.

 Y is the luminance matrix, U and V are two matrices for the chrominance. 

The human eye is more sensitive to luminance variation than chrominance variation. So we are going to do some processing to reduce the information on chrominance as it is less important than the luminance. 

## Downsampling

The first processing is called downsampling. It means we will remove some information. We will do it on the chrominance matrices U and V. There are different downsampling. 

Here we use the 4:2:0 downsampling.

Original group of 4 pixels

| Y  |    |   | U  |    |   | V  |    |               
|----|----|---|----|----|---|----|----|      
| Y1 | Y2 |   | U1 | U2 |   | V1 | V2 |                 
| Y3 | Y4 |   | U2 | U3 |   | V3 | V4 |    

With downsampling :
| Y  |    |   | U  |    |   | V  |    |               
|----|----|---|----|----|---|----|----|      
| Y1 | Y2 |   | Ua | Ua |   | Va | Va |                 
| Y3 | Y4 |   | Ua | Ua |   | Va | Va | 




`Ua` and `Ua` stand for U average and V average. 

With `Ua = 1/4 * (U1 + U2 + U3 + U4)`  
With `Va = 1/4 * (V1 + V2 + V3 + V4)`  
