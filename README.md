In this project we have created a program that calculates the visible points from a center in a height map
with cuda. ​​​​​​​​​​​​​​This would be possible thanks to the differential digital analyzer (DDA) type algorithm, which performs
a rasterization of the line between the center and the point whose visibility we want to calculate on the image after
having compared the angle between this point and the center with the angle of all the points of the line constructed with DDA,
provided that the angle between this point and the center is greater than the angle of all the other points where the point
is visible.
