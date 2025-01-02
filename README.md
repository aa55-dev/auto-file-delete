#  auto-file-delete
This program allows you to schedule files for automatic deletion at a future date and time. This is particularly useful while working with large temporary files that you will only need for a short while. This program will delete those files once the set time period expires, thereby reducing clutter and saving disk space.

## Usage
Mark file for deletion by running

```bash
afd 5d debian-12.8.0-amd64-netinst.iso
```

The suffix may be one of `d`(days),`h`(hours) or `m`(minutes). After the time has expired, the `afdd` program (which will be run as a systemd timer) will delete the file.

The deletion time is stored as an extended attribute(xattr). Therefore a filesystem supporting xattr is required. When moving files marked for deletion, care must be taken to ensure the xattrs are preserved. For more information about xattrs refer to [archlinux wiki](https://wiki.archlinux.org/title/Extended_attributes)

You may query for the deletion time with the included `afdq` binary

```bash
afdq debian-12.8.0-amd64-netinst.iso
```
>Deletion in 6 days, 23 hours, 58 minutes (2025-01-09 23:56:38.312958744) debian-12.8.0-amd64-netinst.iso


## Installation

This program requires a modern C++ compiler(GCC 14.2.0 or Clang 19.1.6).

Compile and install the program by running
```bash
cd auto-file-delete
mkdir build
cd build
cmake ../
make -j4
sudo make install
```

### Setting up systemd service

Copy the systemd service files with:

`cp -v systemd/* ~/.config/systemd/user/`

By default, the daemon is set to check all files in the home directory. You can change this by modifying the `afd.service` file and pass a list of directories to the `afdd` binary.

The daemon is set to run once a day. You can change this by modifying the `afd.timer` file and replacing the `OnCalendar=daily` line (For instance `OnCalendar=*:0/15` for running every 15 minutes)


Once the required changes are made run `systemctl --user daemon-reload`. You can verify that the timer is setup properly by running `systemctl --user list-timers --all afd.timer`


When deleting a file, the filename will get logged to syslog. You can see this by running 
`journalctl --user -u afd.service`

>afdd[61549]: Deleting: /home/user/debian-12.8.0-amd64-netinst.iso
