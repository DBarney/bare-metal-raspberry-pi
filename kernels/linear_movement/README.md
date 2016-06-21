# Linear_movement kernel

The linear_movement kernel is designed to be used with a two linear sensors to detect movement and offset from the original position.

Currently it misses transitions when movement is quick, and I assume that it is because writing to the serial connection (which is implemented currently as a busy loop) is a very expensive operation.
