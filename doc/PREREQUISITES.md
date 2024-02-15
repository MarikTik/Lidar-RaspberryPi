# Prerequisites


## G++:
 
```bash
sudo apt-get update
sudo apt-get install g++
```
## CMake:

``` bash
sudo apt-get install cmake
```
## pigpio

```bash
sudo apt install pigpio
sudo systemctl start pigpiod
```

If you want the pigpio daemon to start automatically at boot, enable it with:

```bash
sudo systemctl enable pigpiod
```

# Verifying the Installation

### After installation, you can verify the installations by checking their versions:
 
```bash
g++ --version
cmake --version
pigpiod -v
```
 