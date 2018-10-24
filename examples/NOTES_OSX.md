@ref
https://stackoverflow.com/questions/9412156/how-to-generate-core-dumps-in-mac-os-x

echo "limit core unlimited" | sudo tee -a /etc/launchd.conf
sudo reboot -t now

ls -al /core/
