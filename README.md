# Clock Angle

Have you ever wondered what the angle between the hour hands on a clock is at two different times?  
Me neither, but here it is anyway.

Simply provide two times in the format hh:mm:ss and the program will calculate the angle between the hour hands.

## Running

Compile with

```shell
gcc clockangle.c -o clockangle
```

To debug, use

```shell
gcc clockangle.c -o clockangle -DDEBUG
```

## Hour Hands

To find the **minimum** angle between the hour hands on two superimposed clocks, run the program with:

```shell
./clockangle h1:m1:s1 h2:m2:s2
```

For example:

```shell
./clockangle 2:06:52 19:43:08
```

The program will return the **minimum** angle between the two hour hands.

## Minute/Hour Hands

To find the **minimum** angle between the hour and minute hand on one clock, run the program with:

```shell
./clockangle h:m:s
```

For example:

```shell
./clockangle 06:46:45
```
