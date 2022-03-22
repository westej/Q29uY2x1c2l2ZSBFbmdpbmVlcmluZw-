#!/bin/bash -ex

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd ${SCRIPT_DIR}

source 00-common.sh

create_container

docker start ${CONTAINER}
docker exec --interactive --privileged --workdir /root/zephyrproject ${CONTAINER} \
    west flash -d ${CONTAINER_PROJECT_DIR}/build

popd
