#!/bin/bash

set -Eeuo pipefail

CURRENT_DIR_PATH="$(pwd)"
DIR_NAME="$(basename ${CURRENT_DIR_PATH})"
MOUNT_DIR_PATH="$(dirname ${CURRENT_DIR_PATH})"
MOUNT_POINT_NAME=/mount-point

imageName=turtlorias-image
containerName=turtlorias-container

msg() {
    echo >&2 -e "${1-}"
}

die() {
    local message=$1
    local code=${2-1} # default exit status 1
    msg "$message"
    exit "$code"
}

usage() {

cat << EOF
Usage: $(basename) [-h] [-v] [-u] [-i] [-c]

This script will run the docker image container

Available options:

-h, --help                  Print this help and exit
-v, --verbose               Print script debug info
EOF

    exit
}

parse_params() {
    POSITIONAL=()
    while [[ $# -gt 0 ]]; do
    key="$1"

    case $key in
        -h | --help)
        usage
        shift # past argument
        ;;
        -v | --verbose)
        set -x
        shift # past argument
        ;;
        --default)
        die "Unknown option: $1"
        shift # past argument
        ;;
        *)    # unknown option
        POSITIONAL+=("$1") # save it in an array for later
        shift # past argument
        ;;
    esac
    done

    set -- "${POSITIONAL[@]}" # restore positional parameters

    return 0
}

parse_params "$@"

if [ "$(docker images -q $imageName 2> /dev/null)" = "" ]; then
    echo Build image...
    docker build -t $imageName -f Dockerfile .
fi

echo Runing new container...

docker run \
--env MOUNT_POINT_NAME=$MOUNT_POINT_NAME \
--name $containerName \
--rm --network=bridge \
--interactive \
--tty --user $(id -u):$(id -g) \
--volume ${MOUNT_DIR_PATH}:${MOUNT_POINT_NAME} \
--workdir ${MOUNT_POINT_NAME}/${DIR_NAME} \
$imageName /bin/bash
