# Monothone Chain Algorithm
Simple implementation of Monothone Chain algorithm

# Installation
To try this use the following commands:
```bash
mkdir bin build
cmake -E chdir build/ cmake ..
cmake --build build
```

# Run
To run the application use the following command:
```bash
./bin/MonothoneChain
```

Then you can press ```ENTER``` key to advance a step, otherwise it will advance a step every 2 seconds
![MonothonChain](https://user-images.githubusercontent.com/43823259/159196130-8a9f008e-14ca-479f-9116-276542aca26c.gif)

# Bugs
- ⚠️ When the algorithm is working backwards (i.e. calculating the bottom hull) the presentation is a bit off
