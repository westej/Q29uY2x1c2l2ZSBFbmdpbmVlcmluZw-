#!/bin/bash -ex

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd ${SCRIPT_DIR}

source 00-common.sh

SEGGER_VID=1366
if [ ! "$( lsusb | grep ${SEGGER_VID} )" ]; then
    echo "No SEGGER J-Link detected. Exiting."
    exit
fi

create_container

docker start ${CONTAINER}
docker exec --interactive --privileged --workdir /root/zephyrproject ${CONTAINER} \
    west flash -d ${CONTAINER_PROJECT_DIR}/build

popd
