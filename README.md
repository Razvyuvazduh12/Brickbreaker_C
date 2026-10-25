The current version has 3 bugs:

1. The paddle can go off limits.
2. If timed correctly, the ball can go through the paddle, but this doesnt break the game because the ball quickly comes out.
3. The multiple balls feature is not implemented yet, so the draw function for them is commented.

The code first builds an Raylib window, and draws 3 elements. A grid, which is drawn using the array of structs called table_of_squares. their size is fixed, and if
you want to modify them, youll also have to modify grid_size. Struct square contains 2 things: the x and y of a square and their width and height, and is used to make every square. check lines 67-78 for the grid implementation.

The paddle is composed of two rectangles, pong_left and pong_right, if the ball collides with pong_left, it goes diagonally left, and vice versa for the pong_right, same idea with the screen bounds for the pong, a Velocity vector is used for this: {2,5} or {x and y} which dictates the ball's direction for the next frames.