# Light_sensor kernel

The list_sensor kernel detects changing values in a gpio pin. It was used as an example of how to setup a process that polls GPIO values and counts transitions.

Currently it misses transitions, and I assume that it is because writing to the serial connection (which is implemented currently as a busy loop) is a very expensive operation.
