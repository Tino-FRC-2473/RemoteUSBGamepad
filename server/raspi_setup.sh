#!/bin/sh

# Hardware setup
sudo raspi-config nonint do_expand_rootfs
sudo raspi-config nonint do_serial 1

# General update
sudo apt update
sudo apt upgrade -y
sudo reboot

# Packages
sudo apt install -y git vim pipenv tmux

# Set timezone
sudo timedatectl set-timezone America/Los_Angeles

# Setup RemoteUSBGamepad
git clone https://github.com/Tino-FRC-2473/RemoteUSBGamepad.git
pushd RemoteUSBGamepad
pipenv install

# Install systemd service
sudo cp server/remoteusbserver.service /etc/systemd/system/remoteusbserver.service
sudo systemctl enable remoteusbserver.service
sudo systemctl start remoteusbserver.service

# Check status with systemctl status remoteusbserver.service
# View logs with journalctl -f -u remoteusbserver.service
