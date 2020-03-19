# Caliprint

A Gtk3 bed calibration and testing utility for 3D printers. It just moves the head to the corners of the bed, so it's easier to level the bed. It can also be used as a testing utility for the head.

## Installing

1. Install the necessary dependencies:

### Fedora
```bash
sudo dnf install gtk3-devel gcc cmake
```

### Debian
```bash
sudo apt install libgtk-3-dev build-essential
```

1. Clone the repository:

```bash
git clone https://github.com/TheLastBilly/caliprint
```

1. Build and install it:

```bash
cd caliprint
mkdir build && cd build
cmake ..
make
sudo make install
```