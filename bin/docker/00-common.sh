#!/bin/bash -ex

IMAGE=zephyr-sdk
CONTAINER=zephyr-build-container

HOST_PROJECT_DIR=${SCRIPT_DIR}/../..
CONTAINER_PROJECT_DIR=/opt/project

function create_container {
    # check if the container exists, but its status is `exited`
    if [ "$( docker ps --all --quiet --filter ancestor=${IMAGE} --filter status=exited )" ]; then
        # clean it up
        docker rm --force $( docker stop $( docker ps --all --quiet --filter ancestor=${IMAGE} --format="{{.ID}}" ) )
    fi
    # check if the container exists and create it if it does not
    if [ ! "$( docker ps --all --quiet --filter ancestor=${IMAGE} )" ]; then
        docker create --interactive --net=host --privileged \
            --mount "type=bind,src=/dev/bus/usb,dst=/dev/bus/usb" \
            --mount "type=bind,src=${HOST_PROJECT_DIR},dst=${CONTAINER_PROJECT_DIR}" \
            --mount "type=bind,src=${HOST_PROJECT_DIR}/build,dst=${CONTAINER_PROJECT_DIR}/build" \
            --name ${CONTAINER} ${IMAGE} /bin/bash
    fi
}