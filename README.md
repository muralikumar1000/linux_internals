#tocheck memory leaks in a program
gcc -g -o memory memory.c
valgrind -s --leak-check=full --track-origins=yes ./memory
##################################################################
#to switch from Wayland to x11 and back
#commenting or true/false the wayland=true/false
#restart is required to work
sudo nano /etc/gdm3/custom.conf
#################################################
#git configuration
git config --global user.name "yourname"
git config --global user.name "yor@email.com"
git config --list (--local/--gloabal)

git init
git add <file name> / git add .
git commit -m "message"
################################################
#CLI vs GUI
sudo systemctl stop lightdm --> CLI
sudo systemctl start lightdm --> GUI

##############################################################
gzip <filename> --> compress
	-k --> keep original
	-v --> verbose
	-r -->recursively compress files in sub directories too
gunzip <filename.tar.gz> --> decompress to <filename.tar>
####################################################################
tar -cf archive.tar files/ -->make archive
tar -xf archive.tar 	   -->pull files out of archive

###################################################################
grep -rn --include="filename" "needle" <~/folder/folder>

grep -rn "text" "needle" <haystack>
#####################################################################

find <~/Downloads/linux-6.16-rc6/*> -type f -name "time.h"
###################################################################
tmux ls -->lists all tmux windows from local terminal/not from tmux terminal

tmux attach -t <tmux window number> -->from local terminal

ctrl+b then (%/") for vertical and horizontal panes
ctrl+b then 'x' --> to close a pane or tmux window
ctrl+b then 's' --> to switch accross windows
ctrl+b then 'd' --> detach from window, still runs in background

ctrl+b then '[' --> to scroll inside the window/pane
ctrl+b then '&' --> to kill the window from tmux

tmux kill-window -t <0:1> --> to kill tmux window from local terminal

#########################################################################
#to increase vbox VM .vdi disk capacity

VBoxManage modifymedium "~/VirtualBox VMs/YourVM/YourVM.vdi" --resize 51200

# 51200 MB = 50 GB

###################################################################################
#to create a bootable drive using DD command in linux environment

sudo fdisk -l  --> find your usb drive

sudo umount /dev/sdb1 --> unmount that drive

sudo dd if=/path/to/your.iso of=/dev/sdb bs=4M status=progress conv=fdatasync

#if- input source  #of- output destination

###################################################################################
#to select the GCC required, replace with g++ for G++ required
sudo update-alternatives --config gcc

#for setting update-alternatives
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 90
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 130
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 130
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 110
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 110

#raspberry pi uses different configuration to load kernel
sudo flash-kernel <6.5.0-1012-raspi/kernel version>
	#this will update the /boot/firmware with all the kernel,.dtb,.src....all other files

root123
anto123



####################################################################################

Frida

🔧 Alternative Option: Use Virtual Environment

If you're building or scripting around Frida (which I suspect you might 😏), use venv:

1️⃣ Install full python support
sudo apt install python3-full python3-venv -y

2️⃣ Create venv
python3 -m venv frida-env

3️⃣ Activate it
source frida-env/bin/activate

4️⃣ Install inside venv
pip install frida-tools


Every time you want to use it:

source frida-env/bin/activate
