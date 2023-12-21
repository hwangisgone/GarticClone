# GarticClone
  Networking Project

For the GUI, we used [Svelte][svelte] as the JavaScript framework and connect to C++ through [webview][webview] library (uses GTK, WebKit2GTK).

## Prerequisites

Your compiler must support minimum C++11

First, update your linux kernel:

Debian-based systems: `sudo apt upgrade`
Fedora-based systems: `sudo dnf upgrade`

### 1. Installing GTK and WebKit2GTK on Linux

The [GTK][gtk] and [WebKit2GTK][webkitgtk] libraries are required for development and distribution.

Debian-based systems:

* Packages:
  * Development: `sudo apt install libgtk-3-dev libwebkit2gtk-4.0-dev`
  * Production: `sudo apt install libgtk-3-0 libwebkit2gtk-4.0-37`

Fedora-based systems:

* Packages:
  * Development: `sudo dnf install gtk3-devel webkit2gtk4.0-devel`
  * Production: `sudo dnf install gtk3 webkit2gtk4.0`

<!-- BSD-based systems:

* FreeBSD packages: `pkg install webkit2-gtk3`
* Execution on BSD-based systems may require adding the `wxallowed` option (see [mount(8)](https://man.openbsd.org/mount.8))  to your fstab to bypass [W^X](https://en.wikipedia.org/wiki/W%5EX "write xor execute") memory protection for your executable. Please see if it works without disabling this security feature first. -->

For building on other operating systems, please refer to the [webview repo][webview]

### 2. Install required packages

Debian-based system:
```
sudo apt-get install pkg-config
```

### 3. Install npm

First, install [nvm][nvm] (Node Version Manager) by either download and run the [install script][nvm-sh] manually, or use cURL or Wget command:

```
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash
```
```
wget -qO- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash
```

Confirm nvm is installed correctly by running:
```
nvm -v
```
This should show the version of nvm installed

Install the most recent LTS version of nodejs and npm:
```
nvm install --lts
```

Test the installation of npm and Nodejs:
```
npm -v
```

## Building

> [!IMPORTANT]
> If you use WSL/WSL2 to build and develop the app, you'll need to install the driver matching your system. Please follow the instructions on [this Microsoft article][wslgui] before proceeding with building the app.

To quickly build the app, you may run the `setup.sh` and `build.sh` script provided at the root of the project.
 
```
./setup.sh
./build.sh
```
In subsequent builds, you only need to run `build.sh`

### Step-by-step building:

First, use npm to compile Svelte code in `ui`:
```
cd ui
npm install
npm run build
cd ..
```

Go to `build` directory and generate build with `cmake`.
Building is required since it imports the HTML file into C++.
```
mkdir build
cd build
cmake ..
```

And then `make` to compile C++ code
```
make
```

Use these to run server/client
```
./CharadeioClient
./CharadeioServer
```

[gtk]:        https://docs.gtk.org/gtk3/
[webkitgtk]:  https://webkitgtk.org/
[webview]:    https://github.com/webview/webview
[svelte]:     https://svelte.dev
[nvm]:        https://github.com/nvm-sh/nvm?tab=readme-ov-file#installing-and-updating
[wslgui]:     https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps
[nvm-sh]:     https://github.com/nvm-sh/nvm/blob/v0.39.7/install.sh
