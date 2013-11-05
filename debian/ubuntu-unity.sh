#Simple fix Ubuntu Unity issue (https://github.com/IgnorantGuru/spacefm/issues/49) without patch.
#!/bin/sh
if [ `lsb_release -is` = 'Debian' ]; then
echo "WOW!! Ubuntu detected. Let's fix Unity issue!"
sed -i s/"Exec=spacefm %F"/"Exec=env UBUNTU_MENUPROXY= spacefm %F"/g debian/tmp/gtk2/usr/share/applications/spacefm.desktop
sed -i s/"Exec=spacefm %F"/"Exec=env UBUNTU_MENUPROXY= spacefm %F"/g debian/tmp/gtk3/usr/share/applications/spacefm.desktop
fi

