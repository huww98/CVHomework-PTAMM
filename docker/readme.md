# PTAMM docker build

## Build

Run from root directory of this repository
```shell
docker build -f docker/Dockerfile -t huww98/ptamm .
```

## Run

### drawMarker

```shell
docker run --rm -v $(pwd):/output -w /output huww98/ptamm drawMarker
```
This will generate markers which can be detected by ptamm. 

### CameraCalibrator

```shell
xhost + # disabled X access control
docker run --rm --privileged \
    -v /dev/video0:/dev/video0 \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v ptamm-data:/data \
    -e DISPLAY \
    huww98/ptamm CameraCalibrator
```
Calibration result will be saved in docker volume `ptamm-data`

### Main program

```shell
xhost + # disabled X access control
docker run --rm --privileged \
    -v /dev/video0:/dev/video0 \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v ptamm-data:/data \
    -e DISPLAY \
    huww98/ptamm
```