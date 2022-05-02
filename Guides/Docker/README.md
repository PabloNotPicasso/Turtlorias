# Docker

[**Docker**](https://www.docker.com/) is platform to deliver software in packages called containers


To build docker image
```
docker build -t imageName -f Dockerfile .
```

To pull docker image from docker hub
```
docker pull imageName
```

To run docker container
```
docker run \
    --name containerName \
    --interactive \
    --tty \
    --user $(id -u):$(id -g) \
    --rm \
    --volume ${MOUNT_DIR_PATH}:${MOUNT_POINT_NAME} \
    --workdir ${MOUNT_POINT_NAME}/${DIR_NAME} \
    imageName /bin/bash
```

To get image list
```
docker image list
```

To delete image
```
docker rmi imageName
```
