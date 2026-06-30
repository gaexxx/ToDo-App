# My-ToDo
Object-Oriented Programming project.

My-ToDo is a desktop ToDo application developed in C++ using Qt.

## Quickstart
```
git clone https://github.com/gaexxx/ToDo-App
cd ToDo-App
```

## Requirements for Local Build
To build the project locally, make sure the following tools are installed:

- C++ compiler with C++17 support
- Qt 6
- qmake
- make

On Ubuntu/Debian-based systems, you can install the required packages with:

```bash
sudo apt update
sudo apt install -y \
  build-essential \
  qt6-base-dev \
  qt6-tools-dev \
  qt6-tools-dev-tools \
  qt6-base-dev-tools \
  qt6-svg-dev
```

## Build Locally

Generate the Makefile with qmake:
```
/usr/lib/qt6/bin/qmake
```

Compile the project:
```
make
```

Run the application:
```
./My-ToDo
```

## Docker Build

Build the Docker image from the project root:
```
docker build -t mytodo .
```

Before running the container, allow Docker to access the X11 display:
```
xhost +local:docker
```

Run the container:
```bash
docker run --rm -it \
  -e DISPLAY="$DISPLAY" \
  -e QT_X11_NO_MITSHM=1 \
  -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
  mytodo
```