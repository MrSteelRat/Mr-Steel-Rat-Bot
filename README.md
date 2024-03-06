# Mr Steel Rat Bot

Mr Steel Rat Bot is a Telegram bot developed using C/C++ and SQLite Database. It provides various features to users interacting with it on the Telegram platform.

## Dependencies

- C/C++ compiler
- Docker (optional, for running in a containerized environment)
- SQLite Database
- CMake
- Boost
- OpenSSL
- ZLib
- Libcurl
- Docker

## Library installation on Linux

You can install dependencies on Debian-based distibutives with these commands:

```sh
sudo apt-get install g++ make binutils cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev sqlite sqlite-dev 
# Install docker for Ubuntu 22.04 add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update

sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

```

## Build from soucre CMake 

1. Ensure CMake is installed on your machine.
2. Open a terminal and navigate to the root directory of the project.
3. Create a build directory: `mkdir build && cd build`
4. Run CMake to configure the project: `cmake ..`
5. Build the project: `cmake --build .`
6. Run the executable generated in the build directory. 
7. `./telegram-bot` 


## Docker 

### Build from soucre and deploy docker 

1. Install docker 
2. docker build -t <bot_name>:tag .
3. docker run <bot_name>:tag .
4. docker run -d bot_name(run in background)
5. docker run -d --name name_container name_images

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).
