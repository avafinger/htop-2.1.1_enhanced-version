# htop-2.1.1_enhanced-version
An enhanced version of htop 2.1.0 to monitor the system health of your big.LITTLE arm64 core.

Monitor the health of your RK3399 board Real-Time and watch CPU Temp, CPU VCore and CPU Freq (big.LITTLE) to find out when throttling occurs and which task is time-consuming.

Screenshot of NanoPi M4 (arm64)

![NanoPi M4 7z benchmark](https://github.com/avafinger/htop-2.1.1_enhanced-version/raw/master/img/nanopi-m4.gif)

# Installing Deb Package
Deb package for Bionic (Ubuntu 18.04) arm64. It may work on Debian, but i have not tested it

* **Install htop-2.1.1 deb package (linux-next)**


		git clone https://github.com/avafinger/htop-2.1.1_enhanced-version
		cd htop-2.1.1_enhanced-version/htop
		sudo dpkg -i htop_2.1.1-5_arm64.deb



# Building the package from source code

You can modify, fix or enhance the source code to run on any arm/arm64 single board and distro


* **Build the package**


		cd htop-2.1.1_enhanced-version/htop/htop-2.1.1/
		sudo dpkg-buildpackage -b -uc -us


* **Deb packages**


		ll ../
		-rw-r--r--  1 root   root   267K Oct 13 20:56 htop-dbgsym_2.1.1-5_arm64.ddeb
		-rw-r--r--  1 root   root   5.3K Oct 13 20:56 htop_2.1.1-5_arm64.buildinfo
		-rw-r--r--  1 ubuntu ubuntu 1.3K Oct 13 20:56 htop_2.1.1-5_arm64.changes
		-rw-r--r--  1 ubuntu ubuntu  74K Oct 13 20:56 htop_2.1.1-5_arm64.deb


* **Install**


		cd ..
		sudo dpkg -i htop_2.1.1-5_arm64.deb



Before you build the package, make sure you install all depencies:


        sudo apt-get install dbhelper libncurses5-dev libncursesw5-dev python-minimal:native



# Running htop-2.1.1

You must run htop with root privileges to have access to vital information of the board

* Run: **sudo htop**

![Htop setup](https://github.com/avafinger/htop-2.1.1_enhanced-version/raw/master/img/vcore.gif)


* To Display CPU Freq, CPU Temp. and CPU VCore (big.LITTLE) you have to enter Configuration setup **F2**
and add the desired info.

![Htop setup](https://github.com/avafinger/htop-2.1.1_enhanced-version/raw/master/img/htop_setup.gif)

