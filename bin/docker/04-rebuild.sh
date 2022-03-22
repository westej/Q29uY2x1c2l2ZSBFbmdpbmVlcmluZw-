#!/bin/bash -ex

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd ${SCRIPT_DIR}

source 00-common.sh

mkdir -p ${HOST_PROJECT_DIR}/build
create_container

docker start ${CONTAINER}
docker exec --interactive --privileged --workdir /root/zephyrproject/zephyr ${CONTAINER} \
    west build -p -b nrf52dk_nrf52832 -d ${CONTAINER_PROJECT_DIR}/build samples/basic/blinky -- -DSHIELD=x_nucleo_iks01a2

popd
