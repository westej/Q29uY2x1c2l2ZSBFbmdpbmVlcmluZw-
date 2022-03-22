#!/bin/bash -ex

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd ${SCRIPT_DIR}

source 00-common.sh

docker run --interactive --net=host --privileged --tty --volume "${HOST_PROJECT_DIR}:${CONTAINER_PROJECT_DIR}" ${IMAGE} /bin/bash

popd
