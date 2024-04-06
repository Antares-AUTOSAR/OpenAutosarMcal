## Install Required packages:
1. sudo pacman -Syu docker
2. sudo pacman -Syu docker-compose

## Build and run the container

Note: If any of the following steps retrieves an docker daemon error try executing: systemctl start docker

1. Move to this directory and run docker-compose up just for the first time to get the initial password and setup Jenkins
2. After finishing the setup, close the terminal with Ctrl+C, the volume of container will keep the imformation for future runs
3. Run again with: docker container start jenkins
4. Stop the container with: docker container stop jenkins


