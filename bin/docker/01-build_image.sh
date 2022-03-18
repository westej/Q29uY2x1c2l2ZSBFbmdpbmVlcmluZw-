#!/bin/bash -ex

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd ${SCRIPT_DIR}

source 00-common.sh

# check if image exists
if [ "$( docker images --quiet ${IMAGE} )" ]; then
    echo "Image exists. Delete and/or rebuild?"
    select option in "Rebuild" "Delete and rebuild" "Leave"; do
        case $option in
            "Rebuild" ) break;;
            "Delete and rebuild" ) DELETE_IMAGE=1; break;;
            "Leave" ) exit;;
        esac
    done

    # check if any containers are started
    if [ "$( docker ps --quiet --filter name=${CONTAINER} )" ]; then
        docker rm --force ${CONTAINER}
    fi
    
    if [ ${DELETE_IMAGE} ]; then
        docker image rm --force ${IMAGE}
    fi
fi

docker build --file Dockerfile --tag ${IMAGE} .

popd
