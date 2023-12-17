#!/bin/bash

# List of libraries to check and install
libraries=("libfreetype6-dev" "libjpeg-dev" "libpng-dev")

# Function to check and install a library
check_and_install_library() {
    local library=$1
    if dpkg -l | grep -q $library; then
        echo "Library $library is already installed."
    else
        echo "Library $library is not installed. Installing..."
        sudo apt-get update
        sudo apt-get install -y $library
        if [ $? -eq 0 ]; then
            echo "Installation of $library successful."
        else
            echo "Error: Unable to install $library. Please install it manually."
            exit 1
        fi
    fi
}

# Loop through the list of libraries
for library in "${libraries[@]}"; do
    check_and_install_library "$library"
done
