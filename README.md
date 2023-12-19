# GarticClone
  Networking Project

For the GUI, we used [Svelte][svelte] as the JavaScript framework and connect to C++ through [webview][webview] library (uses GTK, WebKit2GTK).

## Prerequisites

Your compiler must support minimum C++11

### 1. Installing GTK and WebKit2GTK on Linux and BSD

The [GTK][gtk] and [WebKit2GTK][webkitgtk] libraries are required for development and distribution.

Debian-based systems:

* Packages:
  * Development: `apt install libgtk-3-dev libwebkit2gtk-4.0-dev`
  * Production: `apt install libgtk-3-0 libwebkit2gtk-4.0-37`

Fedora-based systems:

* Packages:
  * Development: `dnf install gtk3-devel webkit2gtk4.0-devel`
  * Production: `dnf install gtk3 webkit2gtk4.0`

BSD-based systems:

* FreeBSD packages: `pkg install webkit2-gtk3`
* Execution on BSD-based systems may require adding the `wxallowed` option (see [mount(8)](https://man.openbsd.org/mount.8))  to your fstab to bypass [W^X](https://en.wikipedia.org/wiki/W%5EX "write xor execute") memory protection for your executable. Please see if it works without disabling this security feature first.

For building on other operating systems, please refer to the [webview repo][webview]

### 2. Install npm

First, install [nvm][nvm] by either download and run the [install script][https://github.com/nvm-sh/nvm/blob/v0.39.7/install.sh] manually, or use cURL or Wget command:
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
> If you use WSL/WSL2 to build and develop the app, you'll need to install the driver matching your system. More info can be found on [this Microsoft article][wslgui]

To quickly build the app, you may run the `build.sh` script provided at the root of the project.

```
./build.sh
```

### Step-by-step building:

First, use npm to compile Svelte code in `ui`:
```
cd ui
npm run build
cd ..
```

Go to `build` directory and generate build with `cmake`.
Building is required since it imports the HTML file into C++.
```
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
