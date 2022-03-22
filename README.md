# Q29uY2x1c2l2ZSBFbmdpbmVlcmluZw-

Prerequisites:
- Linux with Docker - see https://docs.docker.com/engine/install/ubuntu/

Steps:
1. Run ./bin/01-build_image.sh to setup the Docker image used for building and flashing
2. Run ./bin/03-build.sh or ./bin/04-rebuild.sh (`pristine` build) to build the project
3. Make sure that JLink is connected and fully initialized in the host system
4. Run ./bin/05-flash.sh to upload the binary

Constant advertising with the UUID of D34DB33F-1337-1234-5678-AABBCCDDEEFF can be observed.
A custom service allows for a notification subscription.
"Pressure: x Temperature: y" notifications are sent after each sample is read from the sensor.
